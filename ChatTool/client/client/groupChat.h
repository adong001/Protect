#pragma once


// groupChat �Ի���

class C_GROUP_CHAT : public CDialogEx
{
	DECLARE_DYNAMIC(C_GROUP_CHAT)

public:
	C_GROUP_CHAT(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~C_GROUP_CHAT();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
