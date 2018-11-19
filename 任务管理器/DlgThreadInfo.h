#pragma once
#include "afxcmn.h"


// CDlgThreadInfo �Ի���

class CDlgThreadInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgThreadInfo)

public:
	CDlgThreadInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgThreadInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_THR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_nItem;
	CMenu* cmenu;
	CListCtrl m_list_thread;
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnThreadSuspend();
	afx_msg void OnThreadResume();
	afx_msg void OnCloseThread();
};
