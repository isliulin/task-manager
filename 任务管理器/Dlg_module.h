#pragma once
#include "afxcmn.h"


// Dlg_module �Ի���

class Dlg_module : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_module)

public:
	Dlg_module(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dlg_module();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MODULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_module;
	virtual BOOL OnInitDialog();
};
