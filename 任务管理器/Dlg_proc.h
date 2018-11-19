#pragma once
#include "afxcmn.h"
#include "DlgThreadInfo.h"
#include "Dlg_module.h"
#include "Dlg.h"

// CDlg_proc 对话框

class CDlg_proc : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_proc)

public:
	CDlg_proc(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_proc();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PROC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nItem;
	CDlgThreadInfo m_th_info;
	Dlg_module m_module;
	Dlg m_heap;
	CMenu* Menu_proc;
	CListCtrl m_ListCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickListProc(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnShowThread();
	afx_msg void OnShowModule();
	afx_msg void OnShowHeap();
	afx_msg void openfile();
	afx_msg void closeProc();
};
