#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>
#include "savemessage.h"
#include "receive.h"
using namespace std;
extern string g_message[2];
/*
created by 
�˳������ڽ������յ���Ϣ
�Դ�����ַ������н��������ip��ַ��ϵͳʱ�䣬��Ϣ
ip��ʱ�����g_message[0]
��Ϣ����g_message[1]
*/

const string SaveMessagefileName = "Receive_From_server.txt";
void analyse_received_msg(const string &strRcvMessage)
{
	string timeIp = "0", message = "0";
	string buff = strRcvMessage;
	size_t index = buff.find("@");
	if (std::string::npos != index)
	{
		message = buff.substr(index + 1);
		timeIp = buff.assign(buff.c_str(), index);
		g_message[0] = timeIp;
		g_message[1] = message;
	}
}

