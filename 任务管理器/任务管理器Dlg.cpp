
// ���������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������.h"
#include "���������Dlg.h"
#include "afxdialogex.h"
#include"Dlg_proc.h"
#include"Dlg_app.h"
#include"Dlg_file.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C���������Dlg �Ի���



C���������Dlg::C���������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C���������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_mytable);
}

BEGIN_MESSAGE_MAP(C���������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

double FILETIME2Double(const _FILETIME& filetime)
{
	return double(filetime.dwHighDateTime*4.294967296e9) + double(filetime.dwLowDateTime);
}
int GetCpuUsage()
{
	_FILETIME idleTime, kernelTime, userTime;
	GetSystemTimes(&idleTime, &kernelTime, &userTime);
	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	WaitForSingleObject(hEvent, 1000);
	_FILETIME newidleTime, newkernelTime, newuserTime;
	GetSystemTimes(&newidleTime, &newkernelTime, &newuserTime);
	double OidleTime = FILETIME2Double(idleTime);
	double NidleTime = FILETIME2Double(newidleTime);
	double OkernerTime = FILETIME2Double(kernelTime);
	double NkernelTime = FILETIME2Double(newkernelTime);
	double OuserTime = FILETIME2Double(userTime);
	double NuserTime = FILETIME2Double(newuserTime);
	return (int)(100.0 - (NidleTime - OidleTime) / 
		(NkernelTime - OkernerTime + NuserTime - OuserTime)*100.0);
}

// C���������Dlg ��Ϣ�������

BOOL C���������Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	::RegisterHotKey(m_hWnd,0x1234,MOD_CONTROL|MOD_SHIFT,'H');//ע���ȼ�
    //��ȡ������Ȩ
	HANDLE hToken = NULL;
	HANDLE hProcess = GetCurrentProcess();
	OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	TOKEN_PRIVILEGES tp = { 0 };
	LookupPrivilegeValue(0, SE_SHUTDOWN_NAME, &tp.Privileges[0].Luid);
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken,FALSE,&tp,sizeof(tp),NULL,NULL);


	CMenu Menu;//��ʼ���˵�
	Menu.LoadMenuW(IDR_MENU2);
	SetMenu(&Menu);


	m_mytable.InsertItem(0, L"Ӧ�ó���");
	m_mytable.InsertItem(1, L"����");
	m_mytable.InsertItem(2, L"�ļ�");
	m_mytable.m_Dia[0] = new CDlg_app();
	m_mytable.m_Dia[1] = new CDlg_proc();
	m_mytable.m_Dia[2] = new Dlg_file();
	m_mytable.m_Dia[0]->Create(IDD_DLG_APP, &m_mytable);
	m_mytable.m_Dia[1]->Create(IDD_DLG_PROC, &m_mytable);
	m_mytable.m_Dia[2]->Create(IDD_DLG_FILE, &m_mytable);	
	CRect rc;
	m_mytable.GetClientRect(rc);
	rc.DeflateRect(2, 23, 2, 2);
	m_mytable.m_Dia[0]->MoveWindow(rc);
	m_mytable.m_Dia[1]->MoveWindow(rc);
	m_mytable.m_Dia[2]->MoveWindow(rc);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_mytable.m_Dia[0]->ShowWindow(SW_SHOW);
	m_mytable.m_Dia[1]->ShowWindow(SW_HIDE);
	m_mytable.m_Dia[2]->ShowWindow(SW_HIDE);
	//CMenu Menu;//��ʼ���˵�
	//Menu.LoadMenuW(IDR_MENU1);
	//SetMenu(&Menu);


	m_statusbar.Create(this);
	UINT statusId[4] = { 0x1003,0x1004,0x1005,0x1006 };
	// ���÷����ĸ�����ÿ��������id
	m_statusbar.SetIndicators(statusId, _countof(statusId));
	// ���÷����Ŀ��
	m_statusbar.SetPaneInfo(0, 0x1003, 0, 120);
	m_statusbar.SetPaneInfo(1, 0x1004, 0, 80);
	m_statusbar.SetPaneInfo(2, 0x1005, 0, 120);
	m_statusbar.SetPaneInfo(3, 0x1006, 0, 80);
	// ���÷����е��ı�
	m_statusbar.SetPaneText(0, _T("CPUʹ����"), TRUE);
	m_statusbar.SetPaneText(2, _T("�����ڴ�"), TRUE);
	MEMORYSTATUS memst;
	GlobalMemoryStatus(&memst);
	CString str1;
	//str.Format(L"%d", memst.dwTotalPhys - memst.dwAvailPhys);
	str1.Format(L"%d", memst.dwMemoryLoad);
	m_statusbar.SetPaneText(3, str1+"%",TRUE);
	CString str2;
	str2.Format(L"%d", GetCpuUsage());
	m_statusbar.SetPaneText(1, str2 + "%", TRUE);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C���������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C���������Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C���������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





BOOL C���������Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_HOTKEY&&pMsg->lParam == 0x1234)
	{
		if (IsWindowVisible() == TRUE)
			ShowWindow(SW_HIDE);
		else
			ShowWindow(SW_SHOW);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
