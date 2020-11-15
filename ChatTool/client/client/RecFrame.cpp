#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "wsock32")

#include "stdafx.h"
#include "SEND.h"
#include "cSendmessage.h"
#include "receive.h"
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <iterator>
#include <algorithm>
#include <Winsock2.h>
#include <Windows.h>
using namespace std;

/*
created by 
此程序用于消息的接收
接收服务端发来的消息，消息存入recvBuf并用analyseReceivedMsg（recvBuf）函数进行解析
解析后的返回的数组地址传递给全局变量*g_message
*/

//char recvBuf[300];
HANDLE bufferMutex;		// 令其能互斥成功正常通信的信号量句柄
SOCKET sockConn;		// 客户端的套接字
vector <SOCKET> clientSocketGroup;
string g_message[2];		//全局变量，用于传递经过消息解析后的字符串数组的地址
bool g_bIsRcvMsg = true;	//用于判断是否接收到新消息
string g_mode="20";

DWORD WINAPI ReceiveMessageThread(LPVOID IpParameter);

int client_start_up()
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
	addrSrv.sin_port = htons(5999);
	if (SOCKET_ERROR == bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)))  // 第二参数要强制类型转换
    {
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
	WSACleanup();	// 终止对套接字库的使用;
	return 0;
}

DWORD WINAPI ReceiveMessageThread(LPVOID IpParameter)
{
	SOCKET ClientSocket = (SOCKET)(LPVOID)IpParameter;
	sockaddr_in oClntScktAddIn;
	oClntScktAddIn.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // 将INADDR_ANY转换为网络字节序，调用 htonl(long型)或htons(整型)
	oClntScktAddIn.sin_family = AF_INET;
	oClntScktAddIn.sin_port = htons(5999);
	int addrClientlen = sizeof(oClntScktAddIn);
	char recvBuf[1024] = { "20" };
	while (1) {
		sockConn = accept(ClientSocket, (sockaddr FAR*)&oClntScktAddIn, &addrClientlen);
		memset(recvBuf, 0, 1024);

		int iRet = recv(sockConn, recvBuf, sizeof(recvBuf), 0);
		if(iRet < 0)
		{
			continue;
		}  
		g_mode = recvBuf;
		
		analyse_received_msg(g_mode);
		
		g_bIsRcvMsg = !g_bIsRcvMsg;
		ReleaseSemaphore(bufferMutex, 1, NULL);		// V（资源占用完毕） 
	}
	return 0;
}