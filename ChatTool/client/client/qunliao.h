#pragma once


// qunliao �Ի���

class GROUP_CHAT : public CDialogEx
{
	DECLARE_DYNAMIC(GROUP_CHAT)

public:
	GROUP_CHAT(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GROUP_CHAT();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
};
