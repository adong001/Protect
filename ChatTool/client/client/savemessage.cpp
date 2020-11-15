#include "stdafx.h"
#include "savemessage.h"
#include "savemessage.h"
#include <direct.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
using namespace std;

const CString PathNameHead("ClientMessage");//消息日志文件名字头	

C_SAVE_MESSAGE::C_SAVE_MESSAGE()
{
}


C_SAVE_MESSAGE::~C_SAVE_MESSAGE()
{
}

void C_SAVE_MESSAGE::getRootPath(string &path)
{
	wchar_t* wPath = new wchar_t[MAX_PATH];
	if (wPath == NULL)
	{
		cout << "wPath分配内存失败";
		return;
	}
	GetModuleFileName(NULL, wPath, MAX_PATH);//获得程序所在地址

	string sPath = CT2A(wPath);

	//LPCWSTRtoString(sPath, wPath);

	int clientIndex = sPath.find("client\\");
	int PathEndIndex = sPath.find("\\", clientIndex);
	path = sPath.assign(sPath.c_str(), PathEndIndex) + "\\";

	delete[] wPath;

	return;
}

void C_SAVE_MESSAGE::getMessagePath(string & path)
{
	string rootPath;
	getRootPath(rootPath);
	string savePath = "SavePath.txt";
	string rootPathFile = rootPath + savePath;//获得保存地址信息文件的位置

	fstream File(rootPathFile, ios::in);
	char* MessagePath = new char[MAX_PATH];
	if (MessagePath == NULL)
	{
		cout << "MessagePath分配内存失败";
		return;
	}
	File >> MessagePath;
	if (MessagePath == NULL)
	{
		cout << "未成功读取地址";
	}
	else
	{
		if ((string)MessagePath != "")
		{
			
			string sTmp(MessagePath);
			//stringConvert(sTmp);
			path = sTmp;
		}
		else
		{
			path = rootPath;
		}
		
	}
	File.close();

	delete[] MessagePath;

	return;
}

wchar_t* C_SAVE_MESSAGE::StringToLPCWSTR(string str)
{
	DWORD strSize = 0;
	strSize = MultiByteToWideChar(CP_ACP, NULL, str.c_str(), -1, NULL, 0);
	if (0 == strSize)
	{
		cout << "StringToLPCWSTR_dwMinSize长度为0";
	}
	wchar_t* wCharTmp = new wchar_t[strSize];
	if (wCharTmp == NULL)
	{
		cout << "wChar分配内存失败";
	}
	int nRet = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wCharTmp, strSize);

	if (nRet <= 0)
	{
		cout << "StringToLPCWSTR类型转换失败";
	}

	return wCharTmp;
}

void C_SAVE_MESSAGE::LPCWSTRtoString(string & str, LPCWSTR wChar)
{
	DWORD cSize = 0;
	cSize = WideCharToMultiByte(CP_ACP, NULL, wChar, -1, NULL, 0, NULL, FALSE);
	if (0 == cSize)
	{
		cout << "LPCWSTRtoString_dwMinSize长度为0";
		return;
	}
	char* cTmp = new char[cSize];
	if (cTmp == NULL)
	{
		cout << "LPCWSTRtoString_cTmp分配内存失败";
		return;
	}
	//DWORD wPathSize = WideCharToMultiByte(CP_ACP, NULL, wChar, -1, NULL, 0, NULL, FALSE);
	int nRet = WideCharToMultiByte(CP_ACP, 0, wChar, -1, cTmp, cSize, NULL, FALSE);

	if (nRet <= 0)
	{
		cout << "LPCWSTRtoString类型转换失败";
		return;
	}

	str = cTmp;
	
	delete[] cTmp;

	return;
}

void C_SAVE_MESSAGE::stringConvert(string & str)
{
	string sTmp = str;
	int tmpIndex = 0;
	for (int i = 0; i < sTmp.length(); i++)
	{
		tmpIndex = sTmp.find("\\");
		if (tmpIndex != sTmp.find("\\\\"))
		{
			sTmp.insert(tmpIndex, "\\");
		}
	}
	return;
}

void C_SAVE_MESSAGE::getSaveFileName(string & str, CString name)
{
	str += CT2A((PathNameHead + CString("_") + name + CString(".txt")).GetBuffer());
	return;
}

void C_SAVE_MESSAGE::saveMessageToFile(string s, CString name)
{
	const char * c = s.data();
	FILE * pFile;
	string path = "";
	C_SAVE_MESSAGE::getMessagePath(path);
	//根据用户名分别储存聊天记录
	getSaveFileName(path, name);
	int iRet = fopen_s(&pFile, path.c_str(), "a+");
	if (pFile != NULL)
	{
		fputs(c, pFile);
		fclose(pFile);
	}
	else
	{
		AfxMessageBox(_T("保存消息日志失败！"));
	}
	return;
}

