// Dlg_app.cpp : 实现文件
//

#include "stdafx.h"
#include "任务管理器.h"
#include "Dlg_app.h"
#include "afxdialogex.h"
#include <TlHelp32.h>

// CDlg_app 对话框

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


// CDlg_app 消息处理程序
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

	// TODO:  在此添加额外的初始化
	m_ListCtrlApp.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//设置风格
																		 //添加列标题
	m_ListCtrlApp.InsertColumn(0, _T("任务"), LVCFMT_CENTER, 200);
	EnumWindows(EnumWinproc, (LPARAM)&m_ListCtrlApp);
	//m_ListCtrlApp.InsertColumn(1, _T("状态"), LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


