#pragma once
#include <iostream>
#include "string.h"
using namespace std;

class C_SAVE_MESSAGE
{
public:
	C_SAVE_MESSAGE();
	~C_SAVE_MESSAGE();

	static void getRootPath(string &path);//��ó������ڸ�Ŀ¼,pathΪ���ڴ�����ַ���
	static void getMessagePath(string &path);//��õ�ַ�ļ����Ŀ¼
	static wchar_t* StringToLPCWSTR(string str);//��stringת����wchar_t
	static void LPCWSTRtoString(string &str, LPCWSTR wChar);//LPCWSTRת����string
	static void stringConvert(string &str);//����ַ�е�'\'���'\\'
	static void getSaveFileName(string &str, CString name);//�õ������ļ�������
	static void saveMessageToFile(string s, CString name);//����Ϣ���浽�����ļ�
};
