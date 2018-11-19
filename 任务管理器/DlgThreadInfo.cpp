// DlgThreadInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������.h"
#include "DlgThreadInfo.h"
#include "afxdialogex.h"


// CDlgThreadInfo �Ի���

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


// CDlgThreadInfo ��Ϣ�������


BOOL CDlgThreadInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list_thread.InsertColumn(0, _T("��������ID"), LVCFMT_CENTER, 130);
	m_list_thread.InsertColumn(1, _T("�߳�ID"), LVCFMT_CENTER, 80);
	m_list_thread.InsertColumn(2, _T("���ȼ�"), LVCFMT_CENTER, 80);
	m_list_thread.InsertColumn(3, _T("�߳�״̬"), LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}



void CDlgThreadInfo::OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	m_nItem = info.iItem;//����к�
}




void CDlgThreadInfo::OnThreadSuspend()
{
	// TODO: �ڴ���������������
	CString id = m_list_thread.GetItemText(m_nItem, 1);
	DWORD tid;
	swscanf_s(id, L"%d", &tid);
	HANDLE hThread=OpenThread(THREAD_ALL_ACCESS, FALSE, tid);
	SuspendThread(hThread);
	m_list_thread.SetItemText(m_nItem, 3, L"�̹߳���");
}


void CDlgThreadInfo::OnThreadResume()
{
	// TODO: �ڴ���������������
	CString id = m_list_thread.GetItemText(m_nItem, 1);
	DWORD tid;
	swscanf_s(id, L"%d", &tid);
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, tid);
	ResumeThread(hThread);
	m_list_thread.SetItemText(m_nItem, 3, L"��������");
}


void CDlgThreadInfo::OnCloseThread()
{
	// TODO: �ڴ���������������
	CString id = m_list_thread.GetItemText(m_nItem, 1);
	DWORD tid;
	swscanf_s(id, L"%d", &tid);
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, tid);
	m_list_thread.DeleteItem(m_nItem);//ɾ����
	TerminateThread(hThread, 0);
}
