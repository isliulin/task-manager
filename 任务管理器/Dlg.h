#pragma once
#include "afxcmn.h"


// Dlg 对话框

class Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg)

public:
	Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_HEAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_heap;
	virtual BOOL OnInitDialog();
};
