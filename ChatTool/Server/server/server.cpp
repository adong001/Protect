#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "wsock32")
#include "stdafx.h"
#include "savemessage.h"
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
char recvBuf[300];
int isrec = 0;
HANDLE bufferMutex;		// �����ܻ���ɹ�����ͨ�ŵ��ź������
SOCKET sockConn;		// �ͻ��˵��׽���
vector <SOCKET> clientSocketGroup;
string A_ip;
string message;

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
	listen(sockSrv, 20);

	cout << "�������ѳɹ����������������뷢����Ϣ���ͻ��ˣ���ֱ���������ݺ󰴻س�.\n";
	// accept()���������ӣ��ȴ��ͻ�������

	bufferMutex = CreateSemaphore(NULL, 1, 1, NULL);

	DWORD WINAPI SendMessageThread(LPVOID IpParameter);
	DWORD WINAPI ReceiveMessageThread(LPVOID IpParameter);

	HANDLE sendThread = CreateThread(NULL, 0, SendMessageThread, NULL, 0, NULL);

	while (true) {	// ���ϵȴ��ͻ�������ĵ���
		sockaddr_in addrClient;
		int addrClientlen = sizeof(addrClient);
		sockConn = accept(sockSrv, (sockaddr FAR*)&addrClient, &addrClientlen);
		if (SOCKET_ERROR != sockConn) {
			clientSocketGroup.push_back(sockConn);
		}
		HANDLE receiveThread = CreateThread(NULL, 0, ReceiveMessageThread, (LPVOID)sockConn, 0, NULL);
		WaitForSingleObject(bufferMutex, INFINITE);		// P����Դδ��ռ�ã� 
		if (NULL == receiveThread) {
			//printf("\nCreatThread AnswerThread() failed.\n");
		}
		else {
			//printf("\nCreate Receive Client Thread OK.\n");
		}

		//��0.0.0.0 ��ʾ�ͻ���IP
		SOCKADDR_IN client_addr;
		int iSize = sizeof(client_addr);
		getpeername(sockConn, (sockaddr *)&client_addr, &iSize);
		//printf(("Client IP is :%s\n"), inet_ntoa(client_addr.sin_addr));


		ReleaseSemaphore(bufferMutex, 1, NULL);		// V����Դռ����ϣ�
		return 0;
	}

	WaitForSingleObject(sendThread, INFINITE);  // �ȴ��߳̽���
	CloseHandle(sendThread);
	CloseHandle(bufferMutex);
	WSACleanup();	// ��ֹ���׽��ֿ��ʹ��
	//printf("\n");
	system("pause");
	return 0;
}


DWORD WINAPI SendMessageThread(LPVOID IpParameter)
{
	while (1) {
		string talk;
		
		if(isrec==1)
		{ 
			talk = recvBuf;
			WaitForSingleObject(bufferMutex, INFINITE);		// P����Դδ��ռ�ã�  
		/*	if("quit" == talk){
				ReleaseSemaphore(bufferMutex, 1, NULL);		// V����Դռ����ϣ�
				return 0;
			}
			else*/
			//{
			//	talk.append("\n");
			//}
			//printf("I Say:(\"quit\"to exit):");
			//cout << talk;

		
			for (int i = 0; i < clientSocketGroup.size(); ++i)
			{
				SOCKADDR_IN client_addr;
				int iSize = sizeof(client_addr);
				getpeername(clientSocketGroup[i], (sockaddr *)&client_addr, &iSize);
				//printf(("Client IP is :%s\n"), inet_ntoa(client_addr.sin_addr));
				
				const char *delim = "@";
				char *ip;
				ip = strtok(recvBuf, delim);
				talk = A_ip+"@"+talk.erase(0,strlen(ip)+1);
				if (strcmp(inet_ntoa(client_addr.sin_addr), ip) == 0)
				{
					send(clientSocketGroup[i], talk.c_str(), 200, 0);	// ������Ϣ
				}
				isrec = 0;
			}
		}
		ReleaseSemaphore(bufferMutex, 1, NULL);		// V����Դռ����ϣ� 
	}
	return 0;
}


DWORD WINAPI ReceiveMessageThread(LPVOID IpParameter)
{
	SOCKET ClientSocket = (SOCKET)(LPVOID)IpParameter;
	while (1) {
		
		recv(ClientSocket, recvBuf, 200, 0);
		WaitForSingleObject(bufferMutex, INFINITE);		// P����Դδ��ռ�ã�  

		if (recvBuf[0] == 'q' && recvBuf[1] == 'u' && recvBuf[2] == 'i' && recvBuf[3] == 't' && recvBuf[4] == '\0') {
			vector<SOCKET>::iterator result = find(clientSocketGroup.begin(), clientSocketGroup.end(), ClientSocket);
			clientSocketGroup.erase(result);
			closesocket(ClientSocket);
			ReleaseSemaphore(bufferMutex, 1, NULL);		// V����Դռ����ϣ� 
			//printf("\nAttention: A Client has leave...\n", 200, 0);
			break;
		}

		//��0.0.0.0 ��ʾ�ͻ���IP
		SOCKADDR_IN client_addr;
		int iSize = sizeof(client_addr);
		getpeername(sockConn, (sockaddr *)&client_addr, &iSize);
		//printf(("Client IP is :%s\n"), inet_ntoa(client_addr.sin_addr));
		A_ip = inet_ntoa(client_addr.sin_addr);
		message = inet_ntoa(client_addr.sin_addr) + ' ' + *recvBuf;
		saveMessage(message);
		isrec = 1;
		ReleaseSemaphore(bufferMutex, 1, NULL);		// V����Դռ����ϣ� 
	}
	return 0;
}