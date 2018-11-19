#pragma once
#include "afxcmn.h"


// Dlg_module 对话框

class Dlg_module : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_module)

public:
	Dlg_module(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg_module();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MODULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_module;
	virtual BOOL OnInitDialog();
};
