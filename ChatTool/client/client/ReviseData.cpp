// ReviseData.cpp : 实现文件
//

#include "stdafx.h"
#include "client.h"
#include "ReviseData.h"
#include "afxdialogex.h"
#include"send.h"
#include"Register.h"
#include"commDef.h"
#include"clientDlg.h"
// ReviseData 对话框
extern CString username;

IMPLEMENT_DYNAMIC(C_REVISE_DATA, CDialogEx)

C_REVISE_DATA::C_REVISE_DATA(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_UPDATE_USR_INFO, pParent)
	, oldpassword(_T(""))
	, newpassword(_T(""))
	, firpassword(_T(""))
	, r_error_post(_T(""))
{

}

C_REVISE_DATA::~C_REVISE_DATA()
{
}

void C_REVISE_DATA::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, oldpassword);
	DDV_MaxChars(pDX, oldpassword, 15);
	DDX_Text(pDX, IDC_EDIT1, newpassword);
	DDV_MaxChars(pDX, newpassword, 15);
	DDX_Text(pDX, IDC_EDIT3, firpassword);
	DDV_MaxChars(pDX, firpassword, 15);
	DDX_Control(pDX, IDC_COMBO2, m_post);
	DDX_Control(pDX, IDC_COMBO_SECTOR, m_sector);
	DDX_Text(pDX, IDC_STATIC_ERROR, r_error_post);
}


BEGIN_MESSAGE_MAP(C_REVISE_DATA, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT2, &C_REVISE_DATA::OnEnChangeEditOldP)
	ON_EN_CHANGE(IDC_EDIT1, &C_REVISE_DATA::OnEnChangeEditNewP)
	ON_EN_CHANGE(IDC_EDIT3, &C_REVISE_DATA::OnEnChangeEditfirP)
	ON_CBN_SELCHANGE(IDC_COMBO2, &C_REVISE_DATA::OnCbnSelchangeComboPost)
	ON_CBN_SETFOCUS(IDC_COMBO2, &C_REVISE_DATA::OnCbnSetfocusComboPost)
	ON_BN_CLICKED(IDC_BUTTON2, &C_REVISE_DATA::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_MOD_USR_INFO_CFM, &C_REVISE_DATA::OnBnClickedButtonModUsrInfoCfm)
	ON_CBN_SELCHANGE(IDC_COMBO_SECTOR, &C_REVISE_DATA::OnCbnSelchangeComboSector)
	ON_CBN_SETFOCUS(IDC_COMBO_SECTOR, &C_REVISE_DATA::OnCbnSetfocusComboSector)
END_MESSAGE_MAP()


// ReviseData 消息处理程序
int C_REVISE_DATA::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return 0;
}

void C_REVISE_DATA::OnEnChangeEditOldP()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// TODO:  在此添加控件通知处理程序代码
}


void C_REVISE_DATA::OnEnChangeEditNewP()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// TODO:  在此添加控件通知处理程序代码
}


void C_REVISE_DATA::OnEnChangeEditfirP()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// TODO:  在此添加控件通知处理程序代码
}

void C_REVISE_DATA::OnCbnSelchangeComboPost()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// TODO: 在此添加控件通知处理程序代码
	m_post.GetLBText(m_post.GetCurSel(), post);
}




void C_REVISE_DATA::OnCbnSetfocusComboPost()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(TRUE);
	m_post.ResetContent();
	if (sector == "项目部") {
		m_post.AddString(_T("项目经理"));
		m_post.AddString(_T("项目组长"));
		m_post.AddString(_T("安全项目经理"));
		m_post.AddString(_T("质量检查责"));
		m_post.AddString(_T("安全员"));
	}
	else if (sector == "人事部")
	{
		m_post.AddString(_T("人事主管"));
		m_post.AddString(_T("人事专员"));
		m_post.AddString(_T("劳资专员"));
		m_post.AddString(_T("前台"));
		m_post.AddString(_T("行政后勤专员"));
	}
	else if (sector == "产品研发部")
	{
		m_post.AddString(_T("产品经理"));
		m_post.AddString(_T("产品助理"));
		m_post.AddString(_T("产品总监"));
		m_post.AddString(_T("产品小组组员"));
		m_post.AddString(_T("测试工程师"));
	}
	else if (sector == "软件开发部")
	{
		m_post.AddString(_T("开发组长"));
		m_post.AddString(_T("PHP开发工程师"));
		m_post.AddString(_T("Java开发工程师"));
		m_post.AddString(_T("App开发专员"));
		m_post.AddString(_T("数据库设计师"));
		m_post.AddString(_T("系统架构师"));
	}
	else if (sector == "综合服务部")
	{
		m_post.AddString(_T("技术总监"));
		m_post.AddString(_T("信息管理员"));
		m_post.AddString(_T("产品维护员"));
		m_post.AddString(_T("数据分析师"));
	}
	else {
		//MessageBox(_T("请选择部门"), _T("警告"), MB_OK);
		SetDlgItemText(IDC_STATIC_ERROR, _T("(请选择部门!)"));
	}
	//m_post.SetCurSel(-1);
}


void C_REVISE_DATA::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}


void C_REVISE_DATA::OnBnClickedButtonModUsrInfoCfm()
{
	// TODO: 在此添加控件通知处理程序代码
		UpdateData(TRUE);
		CString s();
		if (!newpassword.CompareNoCase(firpassword))
		{
			CString check =CString("NEWPW") +"@"+ username + "@"+ oldpassword+"@"+newpassword+"@";
			snd_to_srv( check );
			MessageBox(_T("修改成功！"));
			OnOK();
		}
		else
			MessageBox(_T("两次输入密码不一致！"));
		//OnOK();
}


void C_REVISE_DATA::OnCbnSelchangeComboSector()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(TRUE);
	m_sector.GetLBText(m_sector.GetCurSel(), sector);
	m_sector.GetWindowText(sector);
	SetDlgItemText(IDC_STATIC_ERROR, _T(""));
}


void C_REVISE_DATA::OnCbnSetfocusComboSector()
{
	// TODO: 在此添加控件通知处理程序代码
	m_sector.ResetContent();
	m_sector.AddString(_T("项目部"));
	m_sector.AddString(_T("人事部"));
	m_sector.AddString(_T("产品研发部"));
	m_sector.AddString(_T("软件开发部"));
	m_sector.AddString(_T("综合服务部"));
	m_sector.SetCurSel(0);
}
