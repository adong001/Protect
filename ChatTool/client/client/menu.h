#pragma once
#include "afxwin.h"


// menu 对话框

class menu : public CDialogEx
{
	DECLARE_DYNAMIC(menu)

public:
	menu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~menu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedButton2();
	// 好友下拉列表控制变量
	CComboBox m_cmbFriend;
};
