#pragma once


// CServerCfg 对话框

class C_SERVER_CFG : public CDialogEx
{
	DECLARE_DYNAMIC(C_SERVER_CFG)

public:
	C_SERVER_CFG(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~C_SERVER_CFG();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SERVER_CFG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg
	void OnClose();
	void On_bn_clicked_ok_ipwindow();
	CString serverIP;
	CIPAddressCtrl m_ip;
//	afx_msg void OnEnChangeEdit1();
	afx_msg void On_ipn_fieldchanged_ipaddress(NMHDR *pNMHDR, LRESULT *pResult);
};
