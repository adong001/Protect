#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;
char* path = "D:\\Message.txt";
//#define _CRT_SECURE_NO_WARNINGS

/*
补佳霖
实现消息写入文件功能

*/

void saveMessage(const string &strMsg)
{
	FILE * pFile;

	pFile = fopen(path, "a+");

	if (pFile != NULL)
	{
		fputs(strMsg.c_str(), pFile);
		fclose(pFile);
	}
}