// DlgThreadInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "任务管理器.h"
#include "DlgThreadInfo.h"
#include "afxdialogex.h"


// CDlgThreadInfo 对话框

IMPLEMENT_DYNAMIC(CDlgThreadInfo, CDialogEx)

CDlgThreadInfo::CDlgThreadInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_THR, pParent)
{

}

CDlgThreadInfo::~CDlgThreadInfo()
{
}

void CDlgThreadInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_thread);
}


BEGIN_MESSAGE_MAP(CDlgThreadInfo, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CDlgThreadInfo::OnRclickList1)
	ON_COMMAND(ID_222_32795, &CDlgThreadInfo::OnThreadSuspend)
	ON_COMMAND(ID_222_32796, &CDlgThreadInfo::OnThreadResume)
	ON_COMMAND(ID_222_32797, &CDlgThreadInfo::OnCloseThread)
END_MESSAGE_MAP()


// CDlgThreadInfo 消息处理程序


BOOL CDlgThreadInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list_thread.InsertColumn(0, _T("所属进程ID"), LVCFMT_CENTER, 130);
	m_list_thread.InsertColumn(1, _T("线程ID"), LVCFMT_CENTER, 80);
	m_list_thread.InsertColumn(2, _T("优先级"), LVCFMT_CENTER, 80);
	m_list_thread.InsertColumn(3, _T("线程状态"), LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void CDlgThreadInfo::OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	POINT p;
	GetCursorPos(&p);
	CMenu cc;
	cc.LoadMenuW(IDR_MENU2);
	cmenu = cc.GetSubMenu(1);
	cmenu->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, this);

	m_list_thread.ScreenToClient(&p);
	LVHITTESTINFO info;
	info.pt = p;
	int Itsub = m_list_thread.SubItemHitTest(&info);
	m_nItem = info.iItem;//获得行号
}




void CDlgThreadInfo::OnThreadSuspend()
{
	// TODO: 在此添加命令处理程序代码
	CString id = m_list_thread.GetItemText(m_nItem, 1);
	DWORD tid;
	swscanf_s(id, L"%d", &tid);
	HANDLE hThread=OpenThread(THREAD_ALL_ACCESS, FALSE, tid);
	SuspendThread(hThread);
	m_list_thread.SetItemText(m_nItem, 3, L"线程挂起");
}


void CDlgThreadInfo::OnThreadResume()
{
	// TODO: 在此添加命令处理程序代码
	CString id = m_list_thread.GetItemText(m_nItem, 1);
	DWORD tid;
	swscanf_s(id, L"%d", &tid);
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, tid);
	ResumeThread(hThread);
	m_list_thread.SetItemText(m_nItem, 3, L"正常运行");
}


void CDlgThreadInfo::OnCloseThread()
{
	// TODO: 在此添加命令处理程序代码
	CString id = m_list_thread.GetItemText(m_nItem, 1);
	DWORD tid;
	swscanf_s(id, L"%d", &tid);
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, tid);
	m_list_thread.DeleteItem(m_nItem);//删除行
	TerminateThread(hThread, 0);
}
