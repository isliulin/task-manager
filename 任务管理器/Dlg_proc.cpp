// Dlg_proc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������.h"
#include "Dlg_proc.h"
#include "afxdialogex.h"
#include <TlHelp32.h>
#include "afxdockingpanesrow.h"

// CDlg_proc �Ի���

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


// CDlg_proc ��Ϣ�������


BOOL CDlg_proc::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//���÷��
	//����б���
	m_ListCtrl.InsertColumn(0, _T("������"), LVCFMT_CENTER, 80);
    m_ListCtrl.InsertColumn(1, _T("PID"), LVCFMT_CENTER, 80);
	//�������̿���
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
	//��������
	Process32First(hSnap,&pe32);
	do 
	{
		m_ListCtrl.InsertItem(0, pe32.szExeFile);
		CString szsz;
		szsz.Format(L"%d", pe32.th32ProcessID);
		m_ListCtrl.SetItemText(0,1, szsz);
	} while (Process32Next(hSnap, &pe32));
	m_th_info.Create(IDD_DLG_THR);//��������
	m_th_info.ShowWindow(SW_HIDE);
	m_module.Create(IDD_DLG_MODULE);
	m_module.ShowWindow(SW_HIDE);
	m_heap.Create(IDD_DLG_HEAP);
	m_heap.ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDlg_proc::OnRclickListProc(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	POINT p;
	GetCursorPos(&p);
	CMenu cc;
	cc.LoadMenuW(IDR_MENU2);
	Menu_proc = cc.GetSubMenu(0);
    Menu_proc->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, this);//�Ҽ������������
	m_ListCtrl.ScreenToClient(&p); // (Glg.h�ļ��ж���    CListCtrl m_list;)

	LVHITTESTINFO info;
	info.pt = p;
	int Itsub = m_ListCtrl.SubItemHitTest(&info);
	m_nItem = info.iItem;//����к�
}


void CDlg_proc::OnShowThread()
{
	// TODO: �ڴ���������������
	
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
			m_th_info.m_list_thread.SetItemText(0, 3, L"��������");
		}
	} while (Thread32Next(hThreadSnap, &te));
	m_th_info.ShowWindow(SW_SHOW);//��ʾ����
}


void CDlg_proc::OnShowModule()
{
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
	m_heap.ShowWindow(SW_SHOW);
}


void CDlg_proc::openfile()
{
	// TODO: �ڴ���������������
}


void CDlg_proc::closeProc()
{
	// TODO: �ڴ���������������v
	CString id = m_ListCtrl.GetItemText(m_nItem, 1);
	DWORD pid;
	swscanf_s(id, L"%d", &pid);
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (TerminateProcess(hProcess, 0))
	{
		m_ListCtrl.DeleteItem(m_nItem);
	}
}
