#pragma once


// qunliao 对话框

class GROUP_CHAT : public CDialogEx
{
	DECLARE_DYNAMIC(GROUP_CHAT)

public:
	GROUP_CHAT(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~GROUP_CHAT();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
};
