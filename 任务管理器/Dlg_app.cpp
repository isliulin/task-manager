// Dlg_app.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������.h"
#include "Dlg_app.h"
#include "afxdialogex.h"
#include <TlHelp32.h>

// CDlg_app �Ի���

IMPLEMENT_DYNAMIC(CDlg_app, CDialogEx)

CDlg_app::CDlg_app(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_APP, pParent)
{

}

CDlg_app::~CDlg_app()
{
}

void CDlg_app::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrlApp);
}


BEGIN_MESSAGE_MAP(CDlg_app, CDialogEx)
END_MESSAGE_MAP()


// CDlg_app ��Ϣ�������
BOOL CALLBACK EnumWindowProc(HWND hwnd, LPARAM lparam)
{
	TCHAR buff[200];
	GetWindowText(hwnd, buff, 200);
	return TRUE;
}
BOOL CALLBACK  EnumWinproc(HWND hwnd, LPARAM lParam)
{

	CListCtrl *aa = (CListCtrl*)lParam;

	TCHAR buff[200]{};
	::GetWindowText(hwnd,buff, 200);
	if (::IsWindowVisible(hwnd) == TRUE&&wcslen(buff) != 0)
	{
		aa->InsertItem(0, buff);
	}
	return TRUE;
}
BOOL CDlg_app::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ListCtrlApp.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//���÷��
																		 //����б���
	m_ListCtrlApp.InsertColumn(0, _T("����"), LVCFMT_CENTER, 200);
	EnumWindows(EnumWinproc, (LPARAM)&m_ListCtrlApp);
	//m_ListCtrlApp.InsertColumn(1, _T("״̬"), LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


