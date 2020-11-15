#include "stdafx.h"
#include <WINSOCK2.H>   
#include <stdio.h>     
#include<iostream>
#include<string>
using namespace std;

/*张永吉，补佳霖
  实现消息的转发功能
    服务端转变成客户端
    通过传入消息和接收方IP地址
*/


//定义程序中使用的常量   
#define PORT          5999         //服务器的端口号      
#define MSGSIZE       1024         //收发缓冲区的大小      
#pragma comment(lib, "ws2_32.lib")      
#pragma warning(disable:4996)
void sendToClient(const string &strMsg, const char *ip)//第一个参数是发送的消息，第二个是接收方IP地址
{
	if (ip == NULL)
	{
		return;
	}
	WSADATA wsaData;
	//连接所用套节字      
	SOCKET sClient;
	//保存远程服务器的地址信息      
	SOCKADDR_IN server;
	//收发缓冲区      
	
	// Initialize Windows socket library      
	WSAStartup(0x0202, &wsaData);

	// 创建客户端套节字      
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INET指明使用TCP/IP协议族；      
														 //SOCK_STREAM, IPPROTO_TCP具体指明使用TCP协议      
														 // 指明远程服务器的地址信息(端口号、IP地址等)      
	memset(&server, 0, sizeof(SOCKADDR_IN)); //先将保存地址的server置为全0      
	server.sin_family = PF_INET; //声明地址格式是TCP/IP地址格式      
	server.sin_port = htons(PORT); //指明连接服务器的端口号，htons()用于 converts values between the host and network byte order      
	server.sin_addr.s_addr = inet_addr(ip); //指明连接服务器的IP地址      
														//结构SOCKADDR_IN的sin_addr字段用于保存IP地址，sin_addr字段也是一个结构体，sin_addr.s_addr用于最终保存IP地址      
														//inet_addr()用于将 形如的"127.0.0.1"字符串转换为IP地址格式      
														//连到刚才指明的服务器上      
														//连接后可以用sClient来使用这个连接      
														//server保存了远程服务器的地址信息      
	int iRet = connect(sClient, (struct sockaddr *) &server, sizeof(SOCKADDR_IN));
	//gets_s(szMessage); //The gets_s() functionreads characters from stdin and loads them into szMessage      
	if(iRet < 0)
	{
		return;
	}
	else
	{
		// 发送数据 
		iRet = send(sClient, strMsg.c_str(), strMsg.length(), 0);
		//sClient指明用哪个连接发送； szMessage指明待发送数据的保存地址 ；strlen(szMessage)指明数据长度      
		closesocket(sClient);
		WSACleanup();
		// 释放连接和进行结束工作      
	}
}
