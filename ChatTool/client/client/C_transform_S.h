#pragma once

/*
created by ����
�˳�������string��CString���໥ת��
*/

#include "stdafx.h"
#include <string>
using namespace std;

//CStringתstring
CString toCString(string str) {
#ifdef _UNICODE
	//�����unicode����
	USES_CONVERSION; CString s(str.c_str());
	CString ans(str.c_str());
	return ans;
#else
	//����Ƕ��ֽڹ��� 
	//string ת CString
	CString ans;
	ans.Format("%s", str.c_str());
	return ans;
#endif // _UNICODE  
}