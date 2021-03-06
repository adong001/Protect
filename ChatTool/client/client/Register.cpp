// Register.cpp: 实现文件
//

#include "stdafx.h"
#include "client.h"
#include "Register.h"
#include "afxdialogex.h"
#include "clientDlg.h"
#include "Success.h"
#include "windows.h"
#include "send.h"
#include "commDef.h"
#include "cstring"

// Register 对话框
extern string g_mode;
IMPLEMENT_DYNAMIC(C_REGISTER, CDialogEx)

C_REGISTER::C_REGISTER(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_REG, pParent)
	, m_csRegWorkId(_T(""))
	, m_csRegPsswd(_T(""))
	, m_csRegPsswdCfm(_T(""))
	, username(_T(""))
	, error_output(_T(""))
{
}

C_REGISTER::~C_REGISTER()
{
}

void C_REGISTER::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USR_NAME, m_csRegWorkId);
	DDV_MaxChars(pDX, m_csRegWorkId, 20);
	DDX_Text(pDX, IDC_EDIT_PSSWD, m_csRegPsswd);
	DDV_MaxChars(pDX, m_csRegPsswd, 15);
	DDX_Text(pDX, IDC_EDIT_PSSWD_CFM, m_csRegPsswdCfm);
	DDV_MaxChars(pDX, m_csRegPsswdCfm, 15);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Control(pDX, IDC_COMBO2, p_combo);
	//  DDX_Text(pDX, IDC_EDIT2, workID);
	DDX_Text(pDX, IDC_EDIT2, username);
	DDX_Text(pDX, IDC_STATIC_ERROR, error_output);
}

BEGIN_MESSAGE_MAP(C_REGISTER, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_RETURN, &C_REGISTER::on_bn_clicked_buttonreturn)
	ON_BN_CLICKED(IDC_BUTTON_CONFIRM, &C_REGISTER::on_bn_clicked_buttonconfirm)
	ON_EN_CHANGE(IDC_EDIT_USR_NAME, &C_REGISTER::on_en_change_edit_username)
	ON_EN_CHANGE(IDC_EDIT_PSSWD, &C_REGISTER::on_en_change_editpassword)
	ON_EN_CHANGE(IDC_EDIT_PSSWD_CFM, &C_REGISTER::on_en_change_editconfirmpassword)
	ON_CBN_SELCHANGE(IDC_COMBO1, &C_REGISTER::on_cbn_selchange_combo1_apartment)
	ON_CBN_SETFOCUS(IDC_COMBO1, &C_REGISTER::on_cbn_setfocus_combo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &C_REGISTER::on_cbn_selchange_combo_post)
	ON_CBN_SETFOCUS(IDC_COMBO2, &C_REGISTER::on_cbn_setfocus_combo_post)
	ON_EN_CHANGE(IDC_EDIT2, &C_REGISTER::on_en_change_edit2_resign)
//	ON_CBN_KILLFOCUS(IDC_COMBO1, &REGISTER::OnCbnKillfocusCombo1)
//	ON_CBN_KILLFOCUS(IDC_COMBO2, &REGISTER::OnCbnKillfocusCombo2)
END_MESSAGE_MAP()

// Register 消息处理程序
void C_REGISTER::on_bn_clicked_buttonreturn()
{
	this->ShowWindow(SW_HIDE);
	CCLIENTDLG b;
    INT_PTR nRessss = b.DoModal();
	
}


void C_REGISTER::on_bn_clicked_buttonconfirm()
{
	UpdateData(TRUE);
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_COMBO1);
	pBoxOne->GetWindowText(m_paramname);
	pBoxOne = (CEdit*)GetDlgItem(IDC_COMBO2);
	pBoxOne->GetWindowText(p_paramname);
	
	if (m_paramname.GetLength() != 0 && p_paramname.GetLength() != 0 && username.GetLength() != 0 && m_csRegWorkId.GetLength() != 0 && m_csRegPsswd.GetLength() != 0 && m_csRegPsswdCfm.GetLength() != 0)
	{
		m_paramname;
		//判断账号是否过长
		if (m_csRegWorkId.GetLength() <= 16)
		{
			m_csRegWorkId.Trim();
			if (m_csRegPsswd == m_csRegPsswdCfm)
			{
				//替换空格
				m_csRegPsswd.Trim();

				snd_to_srv(CString(REGISTER_SIGN) + m_csRegWorkId + CString(DECOLLATOR) + m_csRegPsswd + CString(DECOLLATOR)
					+ m_paramname + CString(DECOLLATOR) + p_paramname + CString(DECOLLATOR) + CString(username));
				Sleep(1000);
				if (g_mode == REGISTER_FAILURE)
				{
					AfxMessageBox(_T("该账号已被注册！！！"));
					//CFrameWnd *f = new CFrameWnd();
					//	this->m_pMainWnd = f;
					//f->Create(NULL, TEXT("该账号已被注册！！！"));
					//f->ShowWindow(SW_SHOW);

				}
				else if (g_mode == REGISTER_SUCCESS)
				{
					this->ShowWindow(SW_HIDE);
					INT_PTR nResss;
					C_SUCCESS b;
					nResss = b.DoModal();
				}
			 }
			else 
			{
				AfxMessageBox(_T("两次输入的密码不一致！！！"));
			}
		}
	
		else
		{
			AfxMessageBox(_T("账号过长！"));
		}
		
		
	}
	else 
	{
		AfxMessageBox(_T("请完善注册信息"));
	}
}

void C_REGISTER::on_en_change_edit_username()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// TODO:  在此添加控件通知处理程序代码
	//((CEdit*)GetDlgItem(IDC_EDIT_USR_NAME))->SetWindowText("请输入用户名");
}

void C_REGISTER::on_en_change_editpassword()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// TODO:  在此添加控件通知处理程序代码
}

void C_REGISTER::on_en_change_editconfirmpassword()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// TODO:  在此添加控件通知处理程序代码
}


void C_REGISTER::on_cbn_selchange_combo1_apartment()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index, m_paramname);
//	UpdateData(TRUE);
	m_combo.GetWindowText(m_paramname);
	//CBN_SELCHANGE()
	SetDlgItemText(IDC_STATIC_ERROR, _T(""));
}


void C_REGISTER::on_cbn_setfocus_combo1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	m_combo.ResetContent();
	m_combo.AddString(_T("项目部"));
	m_combo.AddString(_T("产品研发部"));
	m_combo.AddString(_T("人事部"));
	m_combo.AddString(_T("综合服务部"));
	m_combo.AddString(_T("软件开发部"));
	m_combo.SetCurSel(-1);
	
}


void C_REGISTER::on_cbn_selchange_combo_post()
{
	UpdateData(TRUE);
	// TODO: 在此添加控件通知处理程序代码
	p_combo.GetLBText(p_combo.GetCurSel(), m_paramname);
	p_combo.GetWindowText(m_paramname);
}

void C_REGISTER::on_cbn_setfocus_combo_post()
{
	// TODO: 在此添加控件通知处理程序代码
	p_combo.ResetContent();
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_COMBO1);
	pBoxOne->GetWindowText(m_paramname);
	if (m_paramname == "项目部") {
		p_combo.AddString(_T("项目经理"));
		p_combo.AddString(_T("项目组长"));
		p_combo.AddString(_T("安全项目经理"));
		p_combo.AddString(_T("质量检查责"));
		p_combo.AddString(_T("安全员"));
	}
	else if (m_paramname == "人事部") 
	{
		p_combo.AddString(_T("人事主管"));
		p_combo.AddString(_T("人事专员"));
		p_combo.AddString(_T("劳资专员"));
		p_combo.AddString(_T("前台"));
		p_combo.AddString(_T("行政后勤专员"));
	}
	else if (m_paramname == "产品研发部")
	{
		p_combo.AddString(_T("产品经理"));
		p_combo.AddString(_T("产品助理"));
		p_combo.AddString(_T("产品总监"));
		p_combo.AddString(_T("产品小组组员"));
		p_combo.AddString(_T("测试工程师"));
	}
	else if (m_paramname == "软件开发部")
	{
		p_combo.AddString(_T("开发组长"));
		p_combo.AddString(_T("PHP开发工程师"));
		p_combo.AddString(_T("Java开发工程师"));
		p_combo.AddString(_T("App开发专员"));
		p_combo.AddString(_T("数据库设计师"));
		p_combo.AddString(_T("系统架构师"));
	}
	else if (m_paramname == "综合服务部")
	{
		p_combo.AddString(_T("技术总监"));
		p_combo.AddString(_T("信息管理员"));
		p_combo.AddString(_T("产品维护员"));
		p_combo.AddString(_T("数据分析师"));
	}
	else {
		//MessageBox(_T("请选择部门"), _T("警告"), MB_OK);
		SetDlgItemText(IDC_STATIC_ERROR, _T("(请选择部门!)"));
	}
	p_combo.SetCurSel(-1);
}

void C_REGISTER::on_en_change_edit2_resign()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
