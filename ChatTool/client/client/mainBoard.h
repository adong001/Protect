#pragma once
#include <iostream>
#include "afxwin.h"

// C_MAIN_BAORD 对话框
//void set_zero_zero(std::string &zero_remain_string);


class C_MAIN_BAORD : public CDialogEx
{
	DECLARE_DYNAMIC(C_MAIN_BAORD);

public:
	C_MAIN_BAORD(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~C_MAIN_BAORD();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN_BOARD };
#endif

protected:
	DECLARE_MESSAGE_MAP();
	afx_msg void  OnPaint();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:
	afx_msg void OnBnClickedButtonModPersonalInfo();
	afx_msg void OnBnClickedButtonCrtGrp();
	afx_msg void OnCbnSelchangeCombo();
	afx_msg void OnCbnsetfocusFriends();
	afx_msg void OnCbnSelchangeComboMyGrp();
	static void set_zero_zero(std::string &zero_remain_string);
	afx_msg char* choce_out_the_name(std::string &at_remain_string);
	char get_named(char * the_name);
	afx_msg char get_named(char);
	CComboBox m_cmbFriend;
	CString m_friends;
	CString my_friends[10];
	//CStringArray the_used_friend[10];
	char the_newest_friend[100];
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();

//	const char *c_m_mode();


private:
	CStatic u_name;
};
