#include "stdafx.h"
#include <WINSOCK2.H>   
#include <stdio.h>     
#include <iostream>
#include <string>
#include "send.h"

using namespace std;
//���������ʹ�õĳ���      
//#define SERVER_ADDRESS "169.254.150.0" //��������g_strSrvIP��ַ      
#pragma comment(lib, "ws2_32.lib")      
#pragma warning(disable:4996)
extern char g_strSrvIP[20];
/*
	
	ͨ���׽��������˷�����Ϣ
*/

void snd_to_srv(CString strMsgToSend)
{
	char *connIP = g_strSrvIP;
	WSADATA wsaData;
	//���������׽���      
	SOCKET uiScktClient;
	//����Զ�̷������ĵ�ַ��Ϣ      
	SOCKADDR_IN oSrvAddrIn;
	//�շ�������      
	char szMessage[MSGSIZE];

	USES_CONVERSION;
	char* pMsg = T2A(strMsgToSend);
	int iMsgLen = strlen(pMsg);
	strncpy_s(szMessage, pMsg, iMsgLen);
	// Initialize Windows socket library      
	WSAStartup(0x0202, &wsaData);

	// �����ͻ����׽���      
	uiScktClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INETָ��ʹ��TCP/g_strSrvIPЭ���壻      
														 //SOCK_STREAM, IPPROTO_TCP����ָ��ʹ��TCPЭ��      
														 // ָ��Զ�̷������ĵ�ַ��Ϣ(�˿ںš�g_strSrvIP��ַ��)      
	memset(&oSrvAddrIn, 0, sizeof(SOCKADDR_IN)); //�Ƚ������ַ��oSrvAddrIn��Ϊȫ0      
	oSrvAddrIn.sin_family = PF_INET; //������ַ��ʽ��TCP/g_strSrvIP��ַ��ʽ      
	oSrvAddrIn.sin_port = htons(PORT); //ָ�����ӷ������Ķ˿ںţ�htons()���� converts values between the host and network byte order      
	oSrvAddrIn.sin_addr.s_addr = inet_addr(connIP); //ָ�����ӷ�������g_strSrvIP��ַ      
														//�ṹSOCKADDR_IN��sin_addr�ֶ����ڱ���g_strSrvIP��ַ��sin_addr�ֶ�Ҳ��һ���ṹ�壬sin_addr.s_addr�������ձ���g_strSrvIP��ַ      
														//inet_addr()���ڽ� �����"127.0.0.1"�ַ���ת��Ϊg_strSrvIP��ַ��ʽ      
														//�����ղ�ָ���ķ�������      
														//���Ӻ������uiScktClient��ʹ���������      
														//oSrvAddrIn������Զ�̷������ĵ�ַ��Ϣ      
	int iRet = connect(uiScktClient, (struct sockaddr *) &oSrvAddrIn, sizeof(SOCKADDR_IN));
	if (iRet >= 0)
	{
		cout << "���ӳɹ�" << endl;
	}
	else
	{
		cout << "����ʧ��" << endl;
	}
	//gets_s(szMessage); //The gets_s() functionreads characters from stdin and loads them into szMessage      

	// �������� 
	size_t iSnd = send(uiScktClient, szMessage, strlen(szMessage), 0);
    if (0 > iSnd)
    {

    }
	//uiScktClientָ�����ĸ����ӷ��ͣ� szMessageָ�����������ݵı����ַ ��strlen(szMessage)ָ�����ݳ���      
	closesocket(uiScktClient);
	WSACleanup();
	// �ͷ����Ӻͽ��н�������      

}
