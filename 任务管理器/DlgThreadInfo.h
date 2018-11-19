#pragma once
#include "afxcmn.h"


// CDlgThreadInfo 对话框

class CDlgThreadInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgThreadInfo)

public:
	CDlgThreadInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgThreadInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_THR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
