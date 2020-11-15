// Success.cpp: 实现文件
//

#include "stdafx.h"
#include "client.h"
#include "Success.h"
#include "afxdialogex.h"
#include "clientDlg.h"


// Success 对话框

IMPLEMENT_DYNAMIC(C_SUCCESS, CDialogEx)

C_SUCCESS::C_SUCCESS(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_REG_SUCCESS, pParent)
{

}

C_SUCCESS::~C_SUCCESS()
{
}

void C_SUCCESS::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(C_SUCCESS, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REG_CFM, &C_SUCCESS::on_bn_clicked_reg)
END_MESSAGE_MAP()


// Success 消息处理程序

void C_SUCCESS::on_bn_clicked_reg()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	CCLIENTDLG loginDlg;
	loginDlg.DoModal();
	//CDialogEx::OnOK();
}