#pragma once


// CListModule �Ի���

class CListModule : public CDialogEx
{
	DECLARE_DYNAMIC(CListModule)

public:
	CListModule(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CListModule();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MODULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
