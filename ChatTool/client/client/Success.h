#pragma once


// Success 对话框

class C_SUCCESS : public CDialogEx
{
	DECLARE_DYNAMIC(C_SUCCESS)

public:
	C_SUCCESS(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~C_SUCCESS();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REG_SUCCESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void on_bn_clicked_reg();
};
