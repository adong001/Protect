#include "stdafx.h"
#include <iostream>
#include <string.h>
#define DECOLLATOR "@"
using namespace std;

extern string g_message[2];


//将str以@为界分割为两部分，分别存在g_message[0]和g_message[1]中
void analyse(string str)
{
	string message0, message1;
	string buff = str;
	//static string temp[2];
	size_t index = buff.find(DECOLLATOR);
	if (std::string::npos != index)
	{
		message1 = buff.substr(index + 1);
		message0 = buff.assign(buff.c_str(), index);
		g_message[0] = message0;
		g_message[1] = message1;
		
	}
}