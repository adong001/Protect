#include "stdafx.h"
#include <WINSOCK2.H>   
#include <stdio.h>     
#include<iostream>
#include<string>
using namespace std;

/*��������������
  ʵ����Ϣ��ת������
    �����ת��ɿͻ���
    ͨ��������Ϣ�ͽ��շ�IP��ַ
*/


//���������ʹ�õĳ���   
#define PORT          5999         //�������Ķ˿ں�      
#define MSGSIZE       1024         //�շ��������Ĵ�С      
#pragma comment(lib, "ws2_32.lib")      
#pragma warning(disable:4996)
void sendToClient(const string &strMsg, const char *ip)//��һ�������Ƿ��͵���Ϣ���ڶ����ǽ��շ�IP��ַ
{
	if (ip == NULL)
	{
		return;
	}
	WSADATA wsaData;
	//���������׽���      
	SOCKET sClient;
	//����Զ�̷������ĵ�ַ��Ϣ      
	SOCKADDR_IN server;
	//�շ�������      
	
	// Initialize Windows socket library      
	WSAStartup(0x0202, &wsaData);

	// �����ͻ����׽���      
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INETָ��ʹ��TCP/IPЭ���壻      
														 //SOCK_STREAM, IPPROTO_TCP����ָ��ʹ��TCPЭ��      
														 // ָ��Զ�̷������ĵ�ַ��Ϣ(�˿ںš�IP��ַ��)      
	memset(&server, 0, sizeof(SOCKADDR_IN)); //�Ƚ������ַ��server��Ϊȫ0      
	server.sin_family = PF_INET; //������ַ��ʽ��TCP/IP��ַ��ʽ      
	server.sin_port = htons(PORT); //ָ�����ӷ������Ķ˿ںţ�htons()���� converts values between the host and network byte order      
	server.sin_addr.s_addr = inet_addr(ip); //ָ�����ӷ�������IP��ַ      
														//�ṹSOCKADDR_IN��sin_addr�ֶ����ڱ���IP��ַ��sin_addr�ֶ�Ҳ��һ���ṹ�壬sin_addr.s_addr�������ձ���IP��ַ      
														//inet_addr()���ڽ� �����"127.0.0.1"�ַ���ת��ΪIP��ַ��ʽ      
														//�����ղ�ָ���ķ�������      
														//���Ӻ������sClient��ʹ���������      
														//server������Զ�̷������ĵ�ַ��Ϣ      
	int iRet = connect(sClient, (struct sockaddr *) &server, sizeof(SOCKADDR_IN));
	//gets_s(szMessage); //The gets_s() functionreads characters from stdin and loads them into szMessage      
	if(iRet < 0)
	{
		return;
	}
	else
	{
		// �������� 
		iRet = send(sClient, strMsg.c_str(), strMsg.length(), 0);
		//sClientָ�����ĸ����ӷ��ͣ� szMessageָ�����������ݵı����ַ ��strlen(szMessage)ָ�����ݳ���      
		closesocket(sClient);
		WSACleanup();
		// �ͷ����Ӻͽ��н�������      
	}
}
