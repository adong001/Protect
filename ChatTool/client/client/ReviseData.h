#pragma once
#include "afxwin.h"


// ReviseData 对话框

class C_REVISE_DATA : public CDialogEx
{
	DECLARE_DYNAMIC(C_REVISE_DATA)

public:
	C_REVISE_DATA(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~C_REVISE_DATA();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_USR_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnInitDialog();
	void OnEnChangeEditOldP();
	afx_msg void OnEnChangeEditNewP();
	afx_msg void OnEnChangeEditfirP();
	afx_msg void OnCbnSelchangeComboPost();
	afx_msg void OnCbnSetfocusComboPost();
	CString oldpassword;
	CString newpassword;
	CString firpassword;
	CString sector;
	CString post;
	CComboBox m_sector;
	CComboBox m_post;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonModUsrInfoCfm();
	afx_msg void OnCbnSelchangeComboSector();
	afx_msg void OnCbnSetfocusComboSector();
	
private:
	CString r_error_post;
};
