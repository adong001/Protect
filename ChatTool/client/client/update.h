#pragma once


// update 对话框

class C_UPDATE : public CDialogEx
{
	DECLARE_DYNAMIC(C_UPDATE)

public:
	C_UPDATE(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~C_UPDATE();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void do_data_exchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void on_bn_clicked_button2();
	afx_msg void on_bn_clicked_button1();
};
