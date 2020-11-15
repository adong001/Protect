// ReviseData.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "client.h"
#include "ReviseData.h"
#include "afxdialogex.h"
#include"send.h"
#include"Register.h"
#include"commDef.h"
#include"clientDlg.h"
// ReviseData �Ի���
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


// ReviseData ��Ϣ�������
int C_REVISE_DATA::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return 0;
}

void C_REVISE_DATA::OnEnChangeEditOldP()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void C_REVISE_DATA::OnEnChangeEditNewP()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void C_REVISE_DATA::OnEnChangeEditfirP()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void C_REVISE_DATA::OnCbnSelchangeComboPost()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_post.GetLBText(m_post.GetCurSel(), post);
}




void C_REVISE_DATA::OnCbnSetfocusComboPost()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//UpdateData(TRUE);
	m_post.ResetContent();
	if (sector == "��Ŀ��") {
		m_post.AddString(_T("��Ŀ����"));
		m_post.AddString(_T("��Ŀ�鳤"));
		m_post.AddString(_T("��ȫ��Ŀ����"));
		m_post.AddString(_T("���������"));
		m_post.AddString(_T("��ȫԱ"));
	}
	else if (sector == "���²�")
	{
		m_post.AddString(_T("��������"));
		m_post.AddString(_T("����רԱ"));
		m_post.AddString(_T("����רԱ"));
		m_post.AddString(_T("ǰ̨"));
		m_post.AddString(_T("��������רԱ"));
	}
	else if (sector == "��Ʒ�з���")
	{
		m_post.AddString(_T("��Ʒ����"));
		m_post.AddString(_T("��Ʒ����"));
		m_post.AddString(_T("��Ʒ�ܼ�"));
		m_post.AddString(_T("��ƷС����Ա"));
		m_post.AddString(_T("���Թ���ʦ"));
	}
	else if (sector == "���������")
	{
		m_post.AddString(_T("�����鳤"));
		m_post.AddString(_T("PHP��������ʦ"));
		m_post.AddString(_T("Java��������ʦ"));
		m_post.AddString(_T("App����רԱ"));
		m_post.AddString(_T("���ݿ����ʦ"));
		m_post.AddString(_T("ϵͳ�ܹ�ʦ"));
	}
	else if (sector == "�ۺϷ���")
	{
		m_post.AddString(_T("�����ܼ�"));
		m_post.AddString(_T("��Ϣ����Ա"));
		m_post.AddString(_T("��Ʒά��Ա"));
		m_post.AddString(_T("���ݷ���ʦ"));
	}
	else {
		//MessageBox(_T("��ѡ����"), _T("����"), MB_OK);
		SetDlgItemText(IDC_STATIC_ERROR, _T("(��ѡ����!)"));
	}
	//m_post.SetCurSel(-1);
}


void C_REVISE_DATA::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}


void C_REVISE_DATA::OnBnClickedButtonModUsrInfoCfm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		UpdateData(TRUE);
		CString s();
		if (!newpassword.CompareNoCase(firpassword))
		{
			CString check =CString("NEWPW") +"@"+ username + "@"+ oldpassword+"@"+newpassword+"@";
			snd_to_srv( check );
			MessageBox(_T("�޸ĳɹ���"));
			OnOK();
		}
		else
			MessageBox(_T("�����������벻һ�£�"));
		//OnOK();
}


void C_REVISE_DATA::OnCbnSelchangeComboSector()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//UpdateData(TRUE);
	m_sector.GetLBText(m_sector.GetCurSel(), sector);
	m_sector.GetWindowText(sector);
	SetDlgItemText(IDC_STATIC_ERROR, _T(""));
}


void C_REVISE_DATA::OnCbnSetfocusComboSector()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_sector.ResetContent();
	m_sector.AddString(_T("��Ŀ��"));
	m_sector.AddString(_T("���²�"));
	m_sector.AddString(_T("��Ʒ�з���"));
	m_sector.AddString(_T("���������"));
	m_sector.AddString(_T("�ۺϷ���"));
	m_sector.SetCurSel(0);
}
