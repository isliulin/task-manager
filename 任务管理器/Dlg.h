#pragma once
#include "afxcmn.h"


// Dlg �Ի���

class Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg)

public:
	Dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_HEAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_heap;
	virtual BOOL OnInitDialog();
};
