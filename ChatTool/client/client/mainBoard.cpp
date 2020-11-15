// mainBoard.cpp: 实现文件
//
#include "stdafx.h"
#include "client.h"
#include "mainBoard.h"
#include "cSendmessage.h"
#include "qunliao.h"
#include "groupChat.h"
#include "afxdialogex.h"
#include "ReviseData.h"
#include <iostream>
#include "commDef.h"
#include "send.h"
#include <cstdio>
#include <string.h>
#include <vector>
extern string g_mode;
// C_MAIN_BAORD 对话框
extern CString username;
using namespace std;
extern string g_message[2];

IMPLEMENT_DYNAMIC(C_MAIN_BAORD, CDialogEx)

C_MAIN_BAORD::C_MAIN_BAORD(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MAIN_BOARD, pParent)
{

}

C_MAIN_BAORD::~C_MAIN_BAORD()
{
}

void C_MAIN_BAORD::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO__MY_FRIEND, m_cmbFriend);
	DDX_Control(pDX, IDC_STATIC3, u_name);
}


BEGIN_MESSAGE_MAP(C_MAIN_BAORD, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MOD_PERSONAL_INFO, &C_MAIN_BAORD::OnBnClickedButtonModPersonalInfo)
	ON_BN_CLICKED(IDC_BUTTON_CRT_GRP, &C_MAIN_BAORD::OnBnClickedButtonCrtGrp)
	ON_CBN_SELCHANGE(IDC_COMBO__MY_FRIEND, &C_MAIN_BAORD::OnCbnSelchangeCombo)
	ON_CBN_SETFOCUS(IDC_COMBO__MY_FRIEND, &C_MAIN_BAORD::OnCbnsetfocusFriends)
	ON_CBN_SELCHANGE(IDC_COMBO_MY_GRP, &C_MAIN_BAORD::OnCbnSelchangeComboMyGrp)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &C_MAIN_BAORD::OnBnClickedButton1)
END_MESSAGE_MAP()
void C_MAIN_BAORD::OnPaint()//处理绘制消息
{
	CPaintDC dc(this);
	//dc.Ellipse(40, 40, 150, 150);
	CRect rect;
	this->GetClientRect(&rect);
	dc.DrawText(TEXT("在线"), -1, &rect,DT_SINGLELINE| DT_CENTER);
}

// C_MAIN_BAORD 消息处理程序


void C_MAIN_BAORD::OnBnClickedButtonModPersonalInfo()
{
	// TODO: 在此添加控件通知处理程序代码
	C_REVISE_DATA c;
	c.DoModal();
}


void C_MAIN_BAORD::OnBnClickedButtonCrtGrp()
{
	// TODO: 在此添加控件通知处理程序代码
	C_GROUP_CHAT h;
	h.DoModal();
}


void C_MAIN_BAORD::OnCbnSelchangeCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	C_SEND_MESSAGE b;
	
	// TODO: 在此添加控件通知处理程序代码
	int iSelPos = m_cmbFriend.GetCurSel();
	m_cmbFriend.GetLBText(iSelPos, b.m_frndNm);

	b.DoModal();
}

void C_MAIN_BAORD::OnCbnsetfocusFriends()
{
	
}


void C_MAIN_BAORD::OnCbnSelchangeComboMyGrp()
{
	// TODO: 在此添加控件通知处理程序代码
	GROUP_CHAT e;
	e.DoModal();
}

void C_MAIN_BAORD::set_zero_zero(std::string & zero_remain_string)
{
int index = 0;
	if (!zero_remain_string.empty())
	{
		while ((index = zero_remain_string.find(' ', index)) != string::npos)
		{
			zero_remain_string.erase(index, 1);
		}
	}
}

char* C_MAIN_BAORD::choce_out_the_name(std::string & at_remain_string)
{
	int index = 0;
	int the_further_room = 0;
	char saving_room[100];
	char replacing_room[128];
	if (!at_remain_string.empty())
	{
		for(int i=0;(index = at_remain_string.find('@', index)) != string::npos;i++)
		{
//			replacing_room = & at_remain_string.c_str;
			the_further_room = index;
			at_remain_string.erase(index, 1);
		}
	}
	return saving_room;
}

char C_MAIN_BAORD::get_named(char * the_name)
{

	
	my_friends[0] = the_name;
	return 0;
	//return 0;
}

char C_MAIN_BAORD::get_named(char)
{
	
	return 0;
}

//char C_MAIN_BAORD::get_named(char)
//{
//	return 0;
//}


//void set_zero_zero(string &zero_remain_string)
//{
//	
//	if (!zero_remain_string.empty())
//	{
//		zero_remain_string.erase(0, zero_remain_string.find_first_not_of(" "));
//		zero_remain_string.erase(zero_remain_string.find_last_not_of(" ")+1);
//	}
//	
//	int index = 0;
//	if (!zero_remain_string.empty())
//	{
//		while ((index=zero_remain_string.find(' ',index))!=string::npos)
//		{
//			zero_remain_string.erase(index,1);
//		}
//	}
//}





void C_MAIN_BAORD::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	snd_to_srv((CString(MAINBOARD_FIND)) + CString(DECOLLATOR) + (CString(MAINBOARD_FIND)));
	Sleep(1000);
	if (g_message[0] == MAINBOARD_FIND)
	{
		set_zero_zero(g_message[1]);
		//size_type find(const basic_string &str, size_type index);


		int n = g_message[1].length();
		if (n > 0)
		{
			AfxMessageBox(_T("刷新列表成功"));
		}
		else
		{
			AfxMessageBox(_T("未能成功刷新列表"));
		}

		vector<string> Name;
		int index = 0;
		int i = 0;
		if (!g_message[1].empty())
		{
			m_cmbFriend.ResetContent();
			while ((index = g_message[1].find('@', index)) != string::npos)
			{

				string temp = g_message[1].substr(i, (index - i));
				Name.push_back(temp);
				m_cmbFriend.AddString(CA2T(temp.c_str()));
				m_cmbFriend.SetCurSel(0);
				index += 1;
				i = index;
			}
		}
	}
	else
	{
		AfxMessageBox(_T("未能成功刷新列表"));
	}
}


BOOL C_MAIN_BAORD::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemText(IDC_STATIC3, username);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
