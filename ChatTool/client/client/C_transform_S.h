#pragma once

/*
created by 刘盾
此程序用于string和CString的相互转化
*/

#include "stdafx.h"
#include <string>
using namespace std;

//CString转string
CString toCString(string str) {
#ifdef _UNICODE
	//如果是unicode工程
	USES_CONVERSION; CString s(str.c_str());
	CString ans(str.c_str());
	return ans;
#else
	//如果是多字节工程 
	//string 转 CString
	CString ans;
	ans.Format("%s", str.c_str());
	return ans;
#endif // _UNICODE  
}