#pragma once
#include "afxcmn.h"


// CDlg_app �Ի���

class CDlg_app : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_app)

public:
	CDlg_app(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg_app();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_APP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrlApp;
	virtual BOOL OnInitDialog();
};
