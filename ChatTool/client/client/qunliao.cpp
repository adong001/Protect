// qunliao.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "client.h"
#include "qunliao.h"
#include "afxdialogex.h"
#include "mainBoard.h"


// qunliao �Ի���

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


// qunliao ��Ϣ�������


void GROUP_CHAT::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void GROUP_CHAT::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	C_MAIN_BAORD k;
	k.DoModal();
}
