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
    ������
	�����ʵ����Ϣ���գ�ת��
	�����߳̽���socket���������ͻ�����������ͨ�ţ����շ��͵���Ϣ
	�������߳̽��յ���Ϣ�����������շ�ip�������ת��Ϊ�ͻ��ˣ�����������շ�����

*/

char recvBuf[1024];
int isrec = 0;          //���յ���Ϣ��1,����ת������
HANDLE bufferMutex;		// �����ܻ���ɹ�����ͨ�ŵ��ź������
SOCKET sockConn;		// �ͻ��˵��׽���
vector <SOCKET> clientSocketGroup;
string A_ip;            //��Ϣ���ͷ�IP
string g_message[2];         //���͵���Ϣ
//DWORD WINAPI SendMessageThread(LPVOID IpParameter);//�����߳�
DWORD WINAPI ReceiveMessageThread(LPVOID IpParameter);//�����߳�

int server_start()
{
	// ����socket��̬���ӿ�(dll)
	WORD wVersionRequested;
	WSADATA wsaData;	// ��ṹ�����ڽ���Wjndows Socket�Ľṹ��Ϣ��
	wVersionRequested = MAKEWORD(2, 2);	// ����2.2�汾��WinSock��
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return -1;			// ����ֵΪ���ʱ���Ǳ�ʾ�ɹ�����WSAStartup
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) { // ����Ƿ�2.2�汾��socket��
		WSACleanup();
		return -1;
	}

	// ����socket������������ʽ�׽��֣������׽��ֺ�sockSrv
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	// �׽���sockSrv�뱾�ص�ַ����
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // ��INADDR_ANYת��Ϊ�����ֽ��򣬵��� htonl(long��)��htons(����)
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	if (SOCKET_ERROR == bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR))) { // �ڶ�����Ҫǿ������ת��
		return -1;
	}

	// ���׽�������Ϊ����ģʽ���������󣩣� listen()֪ͨTCP������׼���ý�������
	int iRet = listen(sockSrv, 20);
	if (iRet >= 0)
	{
		cout << "���ü����ɹ�" << endl;
	}
	else
	{
		cout << "���ü���ʧ��" << endl;
	}
	bufferMutex = CreateSemaphore(NULL, 1, 1, NULL);
	HANDLE receiveThread = CreateThread(NULL, 0, ReceiveMessageThread, (LPVOID)sockSrv, 0, NULL);
	CloseHandle(bufferMutex);
	WSACleanup();	// ��ֹ���׽��ֿ��ʹ��
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
	addrClient.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // ��INADDR_ANYת��Ϊ�����ֽ��򣬵��� htonl(long��)��htons(����)
	addrClient.sin_family = AF_INET;
	addrClient.sin_port = htons(6000);
	int addrClientlen = sizeof(addrClient);
	string talk;
	char ip[20];//���ͷ�ip��ַ
	bool judge_name;//�ж��û����Ƿ����
	bool judge_password;//�ж��û����������Ƿ�ƥ��
	string string_ip;//���շ���ip��ַ��string��
	char char_ip[20];//���շ���ip��ַ��char��
	string workid;//���Ͷ�����û���
	string name;
	string sendMess;//������Ϣ
	string saveMess ;//������Ϣ

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
		//WaitForSingleObject(bufferMutex, INFINITE);		// P����Դδ��ռ�ã�  
		//��0.0.0.0 ��ʾ�ͻ���IP
		//SOCKADDR_IN client_addr;
	    int iSize = sizeof(addrClient);	
		getpeername(sockConn, (sockaddr *)&addrClient, &iSize);//ȡ��ǰ���ӵĿͻ��˵�IP��ַ�Ͷ˿ںš�������������óɹ����򷵻�0��������ó����򷵻�-1��
		A_ip = inet_ntoa(addrClient.sin_addr);
		strcpy(ip, A_ip.c_str());
		string time = getTime();
		analyse(recvBuf);
		if (g_message[0]==REGISTER_SIGN)//ע��
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
			judge_name = userNameIsExist(id);//�ж��û����Ƿ����
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
		else if (g_message[0]== LOGIN_SIGN)//��¼
		{
			analyse(g_message[1]);
			string id = g_message[0];
			string password = g_message[1];
			judge_password = loginCheck(id,password);//�ж��û����Ƿ����
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
		else if (g_message[0] == SEND_MESSAGE_SIGN)//������Ϣ
		{
			analyse(g_message[1]);//g_message[0]Ϊ�û���,g_message[1]Ϊ��Ϣ
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
		//ReleaseSemaphore(bufferMutex, 1, NULL);		// V����Դռ����ϣ� 
	}
	return 0;
}

