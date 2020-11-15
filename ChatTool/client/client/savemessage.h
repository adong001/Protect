#pragma once
#include <iostream>
#include "string.h"
using namespace std;

class C_SAVE_MESSAGE
{
public:
	C_SAVE_MESSAGE();
	~C_SAVE_MESSAGE();

	static void getRootPath(string &path);//获得程序所在根目录,path为用于储存的字符串
	static void getMessagePath(string &path);//获得地址文件存放目录
	static wchar_t* StringToLPCWSTR(string str);//把string转换成wchar_t
	static void LPCWSTRtoString(string &str, LPCWSTR wChar);//LPCWSTR转换成string
	static void stringConvert(string &str);//将地址中的'\'变成'\\'
	static void getSaveFileName(string &str, CString name);//得到保存文件的名字
	static void saveMessageToFile(string s, CString name);//将消息保存到本地文件
};
