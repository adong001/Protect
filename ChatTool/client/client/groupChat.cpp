// groupChat.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "client.h"
#include "groupChat.h"
#include "afxdialogex.h"


// groupChat �Ի���

IMPLEMENT_DYNAMIC(C_GROUP_CHAT, CDialogEx)

C_GROUP_CHAT::C_GROUP_CHAT(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

C_GROUP_CHAT::~C_GROUP_CHAT()
{
}

void C_GROUP_CHAT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(C_GROUP_CHAT, CDialogEx)
END_MESSAGE_MAP()


// groupChat ��Ϣ�������
