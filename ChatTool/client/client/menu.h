#pragma once
#include "afxwin.h"


// menu �Ի���

class menu : public CDialogEx
{
	DECLARE_DYNAMIC(menu)

public:
	menu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~menu();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedButton2();
	// ���������б���Ʊ���
	CComboBox m_cmbFriend;
};
