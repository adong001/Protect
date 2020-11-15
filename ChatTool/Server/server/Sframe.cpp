#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "wsock32")
#include "stdafx.h"
#include "sql.h"
#include "analyseMode.h"
#include "SEND.h"
#include "saveMsg.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <Winsock2.h>
#include <Windows.h>
#include <iterator>
#include <algorithm>
const string REGISTER_SIGN = "0";
const string REGISTER_FAILURE = "01";
const string REGISTER_SUCCESS = "00";
const string LOGIN_SIGN = "1";
const string LOGIN_FAILURE = "11";
const string LOGIN_SUCCESS = "10";
const string SEND_MESSAGE_SIGN = "2";
const string DECOLLATOR = "@";
const string GET_USER_LIST_SIGN = "GetUserList";

using namespace std;
/*
    张永吉
	服务端实现消息接收，转发
	接收线程建立socket监听，当客户端请求连接通信，接收发送的消息
	当接收线程接收到消息，解析出接收方ip，服务端转变为客户端，主动请求接收方连接

*/

char recvBuf[1024];
int isrec = 0;          //接收到消息置1,启动转发功能
HANDLE bufferMutex;		// 令其能互斥成功正常通信的信号量句柄
SOCKET sockConn;		// 客户端的套接字
vector <SOCKET> clientSocketGroup;
string A_ip;            //消息发送方IP
string g_message[2];         //发送的消息
//DWORD WINAPI SendMessageThread(LPVOID IpParameter);//发送线程
DWORD WINAPI ReceiveMessageThread(LPVOID IpParameter);//接收线程

int server_start()
{
	// 加载socket动态链接库(dll)
	WORD wVersionRequested;
	WSADATA wsaData;	// 这结构是用于接收Wjndows Socket的结构信息的
	wVersionRequested = MAKEWORD(2, 2);	// 请求2.2版本的WinSock库
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return -1;			// 返回值为零的时候是表示成功申请WSAStartup
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) { // 检测是否2.2版本的socket库
		WSACleanup();
		return -1;
	}

	// 创建socket操作，建立流式套接字，返回套接字号sockSrv
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	// 套接字sockSrv与本地地址相连
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // 将INADDR_ANY转换为网络字节序，调用 htonl(long型)或htons(整型)
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	if (SOCKET_ERROR == bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR))) { // 第二参数要强制类型转换
		return -1;
	}

	// 将套接字设置为监听模式（连接请求）， listen()通知TCP服务器准备好接收连接
	int iRet = listen(sockSrv, 20);
	if (iRet >= 0)
	{
		cout << "设置监听成功" << endl;
	}
	else
	{
		cout << "设置监听失败" << endl;
	}
	bufferMutex = CreateSemaphore(NULL, 1, 1, NULL);
	HANDLE receiveThread = CreateThread(NULL, 0, ReceiveMessageThread, (LPVOID)sockSrv, 0, NULL);
	CloseHandle(bufferMutex);
	WSACleanup();	// 终止对套接字库的使用
	return 0;
}

string getTime()
{
	time_t timep;
	time(&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	return tmp;
}

DWORD WINAPI ReceiveMessageThread(LPVOID IpParameter)
{
	SOCKET ClientSocket = (SOCKET)(LPVOID)IpParameter;
	sockaddr_in addrClient;
	addrClient.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // 将INADDR_ANY转换为网络字节序，调用 htonl(long型)或htons(整型)
	addrClient.sin_family = AF_INET;
	addrClient.sin_port = htons(6000);
	int addrClientlen = sizeof(addrClient);
	string talk;
	char ip[20];//发送方ip地址
	bool judge_name;//判断用户名是否存在
	bool judge_password;//判断用户名和密码是否匹配
	string string_ip;//接收方的ip地址，string型
	char char_ip[20];//接收方的ip地址，char型
	string workid;//发送对象的用户名
	string name;
	string sendMess;//发送消息
	string saveMess ;//保存消息

	while (1) {
		sockConn = accept(ClientSocket, (sockaddr FAR*)&addrClient, &addrClientlen);
		if (SOCKET_ERROR != sockConn) {
			clientSocketGroup.push_back(sockConn);
		}
		memset(recvBuf, 0, 300);
		int iRet = recv(sockConn, recvBuf, 1024, 0);
		if(iRet<0)
		{
			continue;
		}
		//WaitForSingleObject(bufferMutex, INFINITE);		// P（资源未被占用）  
		//以0.0.0.0 显示客户端IP
		//SOCKADDR_IN client_addr;
	    int iSize = sizeof(addrClient);	
		getpeername(sockConn, (sockaddr *)&addrClient, &iSize);//取当前连接的客户端的IP地址和端口号。，如果函数调用成功，则返回0，如果调用出错，则返回-1。
		A_ip = inet_ntoa(addrClient.sin_addr);
		strcpy(ip, A_ip.c_str());
		string time = getTime();
		analyse(recvBuf);
		if (g_message[0]==REGISTER_SIGN)//注册
		{
			analyse(g_message[1]);
			string id = g_message[0];
			analyse(g_message[1]);
			string password = g_message[0];
			analyse(g_message[1]);
			string dept = g_message[0];
			analyse(g_message[1]);
			string post = g_message[0];
			string name = g_message[1];
			judge_name = userNameIsExist(id);//判断用户名是否存在
			if (judge_name)
			{
				talk = REGISTER_SUCCESS;
			}
			else
			{
				talk = REGISTER_FAILURE;
				addUser(id, password, A_ip,dept,post,name);
				//addUser(id, password, A_ip);
			}
			
			sendToClient(talk, ip);
		}
		else if (g_message[0]== LOGIN_SIGN)//登录
		{
			analyse(g_message[1]);
			string id = g_message[0];
			string password = g_message[1];
			judge_password = loginCheck(id,password);//判断用户名是否存在
			if (judge_password)
			{
				talk = LOGIN_SUCCESS;
				updateIpZero(A_ip);
				updateIp(id, A_ip);
			}
			else
			{
				talk = LOGIN_FAILURE;
			}
			sendToClient(talk, ip);
		}
		else if (g_message[0] == SEND_MESSAGE_SIGN)//发送消息
		{
			analyse(g_message[1]);//g_message[0]为用户名,g_message[1]为消息
			string_ip = getIp(g_message[0]);
			name = getUsername(A_ip);
			saveMess= time + " " + name +"-" + g_message[0] + " " + g_message[1] + "\n\r";
			if (!g_message[1].empty())
			{
				saveMessage(saveMess);
			}
			sendMess = SEND_MESSAGE_SIGN + DECOLLATOR + time + DECOLLATOR + name + DECOLLATOR + g_message[1];
			strcpy(char_ip, string_ip.c_str());
			sendToClient(sendMess, char_ip);
		}
		else if (g_message[0] == "NEWPW")
		{
			analyse(g_message[1]);
			string workid = g_message[0];
			analyse(g_message[1]);
			string opw = g_message[0];
			analyse(g_message[1]);
			string npw = g_message[0];
			newpw(workid,opw,npw);
		}
		/*else if (g_message[0] == FIND)
		{
			//GetALLUsername;
			FILE * pFile;
			char * path = "D:\\Message2.txt";
			string str = "aaaa0";

			pFile = fopen(path, "a+");

			if (pFile != NULL)
			{
				fputs(str.c_str(), pFile);
				fclose(pFile);
			}
		}*/
		else if (g_message[0] == GET_USER_LIST_SIGN)
		{
			string buf = GetALLUsername();
			string sendMessage = GET_USER_LIST_SIGN + DECOLLATOR + buf;
			sendToClient(sendMessage, ip);
		}
		//ReleaseSemaphore(bufferMutex, 1, NULL);		// V（资源占用完毕） 
	}
	return 0;
}

