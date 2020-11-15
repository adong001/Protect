// qunliao.cpp : 实现文件
//

#include "stdafx.h"
#include "client.h"
#include "qunliao.h"
#include "afxdialogex.h"
#include "mainBoard.h"


// qunliao 对话框

IMPLEMENT_DYNAMIC(GROUP_CHAT, CDialogEx)

GROUP_CHAT::GROUP_CHAT(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

GROUP_CHAT::~GROUP_CHAT()
{
}

void GROUP_CHAT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GROUP_CHAT, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &GROUP_CHAT::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &GROUP_CHAT::OnBnClickedButton1)
END_MESSAGE_MAP()


// qunliao 消息处理程序


void GROUP_CHAT::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void GROUP_CHAT::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	C_MAIN_BAORD k;
	k.DoModal();
}
