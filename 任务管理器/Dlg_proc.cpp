// Dlg_proc.cpp : 实现文件
//

#include "stdafx.h"
#include "任务管理器.h"
#include "Dlg_proc.h"
#include "afxdialogex.h"
#include <TlHelp32.h>
#include "afxdockingpanesrow.h"

// CDlg_proc 对话框

IMPLEMENT_DYNAMIC(CDlg_proc, CDialogEx)

CDlg_proc::CDlg_proc(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_PROC, pParent)
{

}

CDlg_proc::~CDlg_proc()
{
}

void CDlg_proc::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST1, M);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlg_proc, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CDlg_proc::OnRclickListProc)
	ON_COMMAND(ID_SHOW_THREAD, &CDlg_proc::OnShowThread)
	ON_COMMAND(ID_SHOW_MODULE, &CDlg_proc::OnShowModule)
	ON_COMMAND(IDD_DLG_HEAP, &CDlg_proc::OnShowHeap)
	ON_COMMAND(ID_SHOW_HEAP, &CDlg_proc::OnShowHeap)
	ON_COMMAND(ID__OPEN_FILE, &CDlg_proc::openfile)
	ON_COMMAND(ID__END_PROC, &CDlg_proc::closeProc)
END_MESSAGE_MAP()


// CDlg_proc 消息处理程序


BOOL CDlg_proc::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//设置风格
	//添加列标题
	m_ListCtrl.InsertColumn(0, _T("进程名"), LVCFMT_CENTER, 80);
    m_ListCtrl.InsertColumn(1, _T("PID"), LVCFMT_CENTER, 80);
	//创建进程快照
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
	//遍历进程
	Process32First(hSnap,&pe32);
	do 
	{
		m_ListCtrl.InsertItem(0, pe32.szExeFile);
		CString szsz;
		szsz.Format(L"%d", pe32.th32ProcessID);
		m_ListCtrl.SetItemText(0,1, szsz);
	} while (Process32Next(hSnap, &pe32));
	m_th_info.Create(IDD_DLG_THR);//创建窗口
	m_th_info.ShowWindow(SW_HIDE);
	m_module.Create(IDD_DLG_MODULE);
	m_module.ShowWindow(SW_HIDE);
	m_heap.Create(IDD_DLG_HEAP);
	m_heap.ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlg_proc::OnRclickListProc(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	POINT p;
	GetCursorPos(&p);
	CMenu cc;
	cc.LoadMenuW(IDR_MENU2);
	Menu_proc = cc.GetSubMenu(0);
    Menu_proc->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, this);//右键点击弹出窗口
	m_ListCtrl.ScreenToClient(&p); // (Glg.h文件中定义    CListCtrl m_list;)

	LVHITTESTINFO info;
	info.pt = p;
	int Itsub = m_ListCtrl.SubItemHitTest(&info);
	m_nItem = info.iItem;//获得行号
}


void CDlg_proc::OnShowThread()
{
	// TODO: 在此添加命令处理程序代码
	
	CString id = m_ListCtrl.GetItemText(m_nItem, 1);
	DWORD pid;
	swscanf_s(id, L"%d",&pid);
	m_th_info.m_list_thread.DeleteAllItems();
	THREADENTRY32 te = { sizeof(THREADENTRY32) };
	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	Thread32First(hThreadSnap, &te);
	do
	{
		if (te.th32OwnerProcessID == pid)
		{
			CString str1, str2, str3;
			str1.Format(L"%d", te.th32OwnerProcessID);
			str2.Format(L"%d", te.th32ThreadID);
			str3.Format(L"%d", te.tpBasePri);
			m_th_info.m_list_thread.InsertItem(0, str1);
			m_th_info.m_list_thread.SetItemText(0,1,str2);
			m_th_info.m_list_thread.SetItemText(0, 2, str3);
			m_th_info.m_list_thread.SetItemText(0, 3, L"正常运行");
		}
	} while (Thread32Next(hThreadSnap, &te));
	m_th_info.ShowWindow(SW_SHOW);//显示窗口
}


void CDlg_proc::OnShowModule()
{
	// TODO: 在此添加命令处理程序代码
	CString id = m_ListCtrl.GetItemText(m_nItem, 1);
	DWORD pid;
	swscanf_s(id, L"%d", &pid);
	m_module.m_list_module.DeleteAllItems();
	MODULEENTRY32 me = { sizeof(MODULEENTRY32) };
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	Module32First(hSnap, &me);
}


void CDlg_proc::OnShowHeap()
{
	// TODO: 在此添加命令处理程序代码
	m_heap.ShowWindow(SW_SHOW);
}


void CDlg_proc::openfile()
{
	// TODO: 在此添加命令处理程序代码
}


void CDlg_proc::closeProc()
{
	// TODO: 在此添加命令处理程序代码v
	CString id = m_ListCtrl.GetItemText(m_nItem, 1);
	DWORD pid;
	swscanf_s(id, L"%d", &pid);
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (TerminateProcess(hProcess, 0))
	{
		m_ListCtrl.DeleteItem(m_nItem);
	}
}
