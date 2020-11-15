#include "stdafx.h"
#include <WINSOCK2.H>   
#include <stdio.h>     
#include <iostream>
#include <string>
#include "send.h"

using namespace std;
//定义程序中使用的常量      
//#define SERVER_ADDRESS "169.254.150.0" //服务器端g_strSrvIP地址      
#pragma comment(lib, "ws2_32.lib")      
#pragma warning(disable:4996)
extern char g_strSrvIP[20];
/*
	
	通过套接字向服务端发送消息
*/

void snd_to_srv(CString strMsgToSend)
{
	char *connIP = g_strSrvIP;
	WSADATA wsaData;
	//连接所用套节字      
	SOCKET uiScktClient;
	//保存远程服务器的地址信息      
	SOCKADDR_IN oSrvAddrIn;
	//收发缓冲区      
	char szMessage[MSGSIZE];

	USES_CONVERSION;
	char* pMsg = T2A(strMsgToSend);
	int iMsgLen = strlen(pMsg);
	strncpy_s(szMessage, pMsg, iMsgLen);
	// Initialize Windows socket library      
	WSAStartup(0x0202, &wsaData);

	// 创建客户端套节字      
	uiScktClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INET指明使用TCP/g_strSrvIP协议族；      
														 //SOCK_STREAM, IPPROTO_TCP具体指明使用TCP协议      
														 // 指明远程服务器的地址信息(端口号、g_strSrvIP地址等)      
	memset(&oSrvAddrIn, 0, sizeof(SOCKADDR_IN)); //先将保存地址的oSrvAddrIn置为全0      
	oSrvAddrIn.sin_family = PF_INET; //声明地址格式是TCP/g_strSrvIP地址格式      
	oSrvAddrIn.sin_port = htons(PORT); //指明连接服务器的端口号，htons()用于 converts values between the host and network byte order      
	oSrvAddrIn.sin_addr.s_addr = inet_addr(connIP); //指明连接服务器的g_strSrvIP地址      
														//结构SOCKADDR_IN的sin_addr字段用于保存g_strSrvIP地址，sin_addr字段也是一个结构体，sin_addr.s_addr用于最终保存g_strSrvIP地址      
														//inet_addr()用于将 形如的"127.0.0.1"字符串转换为g_strSrvIP地址格式      
														//连到刚才指明的服务器上      
														//连接后可以用uiScktClient来使用这个连接      
														//oSrvAddrIn保存了远程服务器的地址信息      
	int iRet = connect(uiScktClient, (struct sockaddr *) &oSrvAddrIn, sizeof(SOCKADDR_IN));
	if (iRet >= 0)
	{
		cout << "连接成功" << endl;
	}
	else
	{
		cout << "连接失败" << endl;
	}
	//gets_s(szMessage); //The gets_s() functionreads characters from stdin and loads them into szMessage      

	// 发送数据 
	size_t iSnd = send(uiScktClient, szMessage, strlen(szMessage), 0);
    if (0 > iSnd)
    {

    }
	//uiScktClient指明用哪个连接发送； szMessage指明待发送数据的保存地址 ；strlen(szMessage)指明数据长度      
	closesocket(uiScktClient);
	WSACleanup();
	// 释放连接和进行结束工作      

}
