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
�˳���������Ϣ�Ľ���
���շ���˷�������Ϣ����Ϣ����recvBuf����analyseReceivedMsg��recvBuf���������н���
������ķ��ص������ַ���ݸ�ȫ�ֱ���*g_message
*/

//char recvBuf[300];
HANDLE bufferMutex;		// �����ܻ���ɹ�����ͨ�ŵ��ź������
SOCKET sockConn;		// �ͻ��˵��׽���
vector <SOCKET> clientSocketGroup;
string g_message[2];		//ȫ�ֱ��������ڴ��ݾ�����Ϣ��������ַ�������ĵ�ַ
bool g_bIsRcvMsg = true;	//�����ж��Ƿ���յ�����Ϣ
string g_mode="20";

DWORD WINAPI ReceiveMessageThread(LPVOID IpParameter);

int client_start_up()
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
	addrSrv.sin_port = htons(5999);
	if (SOCKET_ERROR == bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)))  // �ڶ�����Ҫǿ������ת��
    {
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
	WSACleanup();	// ��ֹ���׽��ֿ��ʹ��;
	return 0;
}

DWORD WINAPI ReceiveMessageThread(LPVOID IpParameter)
{
	SOCKET ClientSocket = (SOCKET)(LPVOID)IpParameter;
	sockaddr_in oClntScktAddIn;
	oClntScktAddIn.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // ��INADDR_ANYת��Ϊ�����ֽ��򣬵��� htonl(long��)��htons(����)
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
		ReleaseSemaphore(bufferMutex, 1, NULL);		// V����Դռ����ϣ� 
	}
	return 0;
}