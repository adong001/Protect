#pragma comment(lib,"ws2_32.lib")
#include "stdafx.h"
#include"receive.h"
#include <iostream>
#include <cstdio>
#include <string>
#include "cSendmessage.h"
#include <cstring>
#include <winsock2.h>
#include <Windows.h>

using namespace std;

extern string give_server;
SOCKET sockClient;		// ���ӳɹ�����׽���
HANDLE bufferMutex;		// �����ܻ���ɹ�����ͨ�ŵ��ź������
bool rec_show = true;    //show�༭���״̬
string text;
string *transferMessage;//��Ϣ���ݱ���

int MFCTest()
{
	// ����socket��̬���ӿ�(dll)
	WORD wVersionRequested;
	WSADATA wsaData;	// ��ṹ�����ڽ���Wjndows Socket�Ľṹ��Ϣ��
	wVersionRequested = MAKEWORD(2, 2);	// ����2.2�汾��WinSock��
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {	// ����ֵΪ���ʱ���Ǳ�ʾ�ɹ�����WSAStartup
		return -1;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) { // ���汾���Ƿ���ȷ
		WSACleanup();
		return -1;
	}

	// ����socket������������ʽ�׽��֣������׽��ֺ�sockClient
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (sockClient == INVALID_SOCKET) {
		printf("Error at socket():%ld\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	// ���׽���sockClient��Զ����������
	// int connect( SOCKET s,  const struct sockaddr* name,  int namelen);
	// ��һ����������Ҫ�������Ӳ������׽���
	// �ڶ����������趨����Ҫ���ӵĵ�ַ��Ϣ
	// ��������������ַ�ĳ���
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("169.254.150.0");		// ���ػ�·��ַ; 
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	//cout << "���ͻ�����׼���������û���ֱ�����������������������Ϣ��\n";

	//	send(sockClient, "\nAttention: A Client has enter...\n", strlen("Attention: A Client has enter...\n")+1, 0);
	send(sockClient, "\nAttention: A Client has enter...\n", 200, 0);

	bufferMutex = CreateSemaphore(NULL, 1, 1, NULL);

	DWORD WINAPI SendMessageThread(LPVOID IpParameter);
	DWORD WINAPI ReceiveMessageThread(LPVOID IpParameter);

	HANDLE sendThread = CreateThread(NULL, 0, SendMessageThread, NULL, 0, NULL);
	HANDLE receiveThread = CreateThread(NULL, 0, ReceiveMessageThread, NULL, 0, NULL);


	//WaitForSingleObject(sendThread, INFINITE);  // �ȴ��߳̽���
	//closesocket(sockClient);
	//CloseHandle(sendThread);
	//CloseHandle(receiveThread);
	//CloseHandle(bufferMutex);
	//WSACleanup();	// ��ֹ���׽��ֿ��ʹ��
	//
	//printf("End linking...\n");
	//printf("\n");
	//system("pause");
	return 0;
}


DWORD WINAPI SendMessageThread(LPVOID IpParameter)
{
	while (1) {
		//string t = "169.254.234.79@";
		//string t = "169.254.226.242@";
		//string talk;
		//getline(cin, talk);
		 //text = t + text;
		WaitForSingleObject(bufferMutex, INFINITE);		// P����Դδ��ռ�ã�  
		/*if ("quit" == text) {
			text.push_back('\0');
			//			send(sockClient, talk.c_str(), talk.size(), 0);
			send(sockClient,text.c_str(), 200, 0);
			break;
		}
		else {
			text.append("\n");
		}
		printf("\nI Say:(\"quit\"to exit):");
		cout << text;
		//	send(sockClient, talk.c_str(), talk.size(), 0);	// ������Ϣ
		*/
		give_server = "Client send test!";
		int iRet = send(sockClient, give_server.c_str(), 200, 0);	// ������Ϣ
		ReleaseSemaphore(bufferMutex, 1, NULL);		// V����Դռ����ϣ� 
	}
	return 0;
}


DWORD WINAPI ReceiveMessageThread(LPVOID IpParameter)
{
	while (1) {
		char recvBuf[300] = { 0 };
		recv(sockClient, recvBuf, 200, 0);
		transferMessage = analyse(recvBuf);
		WaitForSingleObject(bufferMutex, INFINITE);		// P����Դδ��ռ�ã�  
		//printf("%s Says: %s\n", "Server", recvBuf);		// ������Ϣ
		ReleaseSemaphore(bufferMutex, 1, NULL);		// V����Դռ����ϣ� 
		rec_show = !rec_show;
	}
	return 0;
}
