
// clientDlg.h: 头文件
//

#pragma once

// CclientDlg 对话框
class CCLIENTDLG : public CDialogEx
{
// 构造
public:
	CCLIENTDLG(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;


	void OnClose();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On_bn_clicked_log_in();
	CString m_usrnameLogin;
	CString m_psswrdLogin;

	afx_msg void OnBnClickedReg();
	afx_msg void On_en_ehange_work_num();
	afx_msg void On_en_change_password();
    afx_msg void On_bn_clicked_button_sign_in();
    afx_msg void OnBnClickedButtonReg();

};
