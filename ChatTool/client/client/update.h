#pragma once


// update �Ի���

class C_UPDATE : public CDialogEx
{
	DECLARE_DYNAMIC(C_UPDATE)

public:
	C_UPDATE(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~C_UPDATE();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void do_data_exchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void on_bn_clicked_button2();
	afx_msg void on_bn_clicked_button1();
};
