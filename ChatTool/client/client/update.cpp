// update.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "client.h"
#include "update.h"
#include "afxdialogex.h"
#include "mainBoard.h"
#include "Register.h"




// update �Ի���

IMPLEMENT_DYNAMIC(C_UPDATE, CDialogEx)

C_UPDATE::C_UPDATE(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

C_UPDATE::~C_UPDATE()
{
}

void C_UPDATE::do_data_exchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(C_UPDATE, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &C_UPDATE::on_bn_clicked_button2)
	ON_BN_CLICKED(IDC_BUTTON1, &C_UPDATE::on_bn_clicked_button1)
END_MESSAGE_MAP()


// update ��Ϣ�������


void C_UPDATE::on_bn_clicked_button2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_HIDE);
	C_MAIN_BAORD d;
	d.DoModal();
}


void C_UPDATE::on_bn_clicked_button1()
{
	UpdateData(TRUE);
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}
