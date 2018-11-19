#pragma once
#include "afxcmn.h"


// CDlg_app 对话框

class CDlg_app : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_app)

public:
	CDlg_app(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_app();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_APP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrlApp;
	virtual BOOL OnInitDialog();
};
