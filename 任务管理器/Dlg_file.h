#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Dlg_file �Ի���

class Dlg_file : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_file)

public:
	Dlg_file(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dlg_file();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_file;
	virtual BOOL OnInitDialog();
	void printfile(const CStringA& dir);
	void clearfile(const CStringA& dir);
	afx_msg void OnBnClickedButton1();
	CEdit m_edit;
	afx_msg void OnBnClickedButton2();
};
