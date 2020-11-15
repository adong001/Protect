// menu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "client.h"
#include "menu.h"
#include "afxdialogex.h"
#include "cSendmessage.h"
#include "update.h"
#include "groupChat.h"
#include "qunliao.h"


// menu �Ի���

IMPLEMENT_DYNAMIC(menu, CDialogEx)

menu::menu(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

menu::~menu()
{
}

void menu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO3, m_cmbFriend);
}


BEGIN_MESSAGE_MAP(menu, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &menu::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &menu::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &menu::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_BUTTON2, &menu::OnBnClickedButton2)
END_MESSAGE_MAP()


// menu ��Ϣ�������


void menu::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	update c;
	c.DoModal();
}


void menu::OnCbnSelchangeCombo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	qunliao h;
	h.DoModal();
}


void menu::OnCbnSelchangeCombo3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	cSendmessage b;
	int iSelPos = m_cmbFriend.GetCurSel();
	m_cmbFriend.GetLBText(iSelPos, b.m_frndNm);
	b.DoModal();
}


void menu::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	groupChat e;
	e.DoModal();
}
