#pragma once

#define DLG_LIST_TEST ((CIHListBox*)(GetDlgItem(IDC_EDIT_SHOW)))
#define IDC_EDIT_SHOW 1000
#define DECOLLATOR "@"
#define SEND_MESSAGE_SIGN "2"
#define TIMER1 1

// cSendmessage 对话框

class C_SEND_MESSAGE : public CDialogEx
{
	DECLARE_DYNAMIC(C_SEND_MESSAGE)



public:
	C_SEND_MESSAGE(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~C_SEND_MESSAGE();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHAT_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    //DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	bool is_recv;//=true;
	CString m_show;
	CString m_message;
	CString m_oppositeName;	
	CString m_frndNm;
	afx_msg
	void OnBnClickedButtonsend();
//	UINT Thread(void * param);
	afx_msg void OnEnChangeEditshow();

	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void On_en_change_edit_ip();
	afx_msg void On_en_change_edit_message();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonMessage();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);


	//change
	CString defaults_name;
};
