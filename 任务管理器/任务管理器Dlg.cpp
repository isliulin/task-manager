
// 任务管理器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "任务管理器.h"
#include "任务管理器Dlg.h"
#include "afxdialogex.h"
#include"Dlg_proc.h"
#include"Dlg_app.h"
#include"Dlg_file.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// C任务管理器Dlg 对话框



C任务管理器Dlg::C任务管理器Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C任务管理器Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_mytable);
}

BEGIN_MESSAGE_MAP(C任务管理器Dlg, CDialogEx)
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

// C任务管理器Dlg 消息处理程序

BOOL C任务管理器Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	::RegisterHotKey(m_hWnd,0x1234,MOD_CONTROL|MOD_SHIFT,'H');//注册热键
    //提取开机特权
	HANDLE hToken = NULL;
	HANDLE hProcess = GetCurrentProcess();
	OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	TOKEN_PRIVILEGES tp = { 0 };
	LookupPrivilegeValue(0, SE_SHUTDOWN_NAME, &tp.Privileges[0].Luid);
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken,FALSE,&tp,sizeof(tp),NULL,NULL);


	CMenu Menu;//初始化菜单
	Menu.LoadMenuW(IDR_MENU2);
	SetMenu(&Menu);


	m_mytable.InsertItem(0, L"应用程序");
	m_mytable.InsertItem(1, L"进程");
	m_mytable.InsertItem(2, L"文件");
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
	// TODO: 在此添加额外的初始化代码
	m_mytable.m_Dia[0]->ShowWindow(SW_SHOW);
	m_mytable.m_Dia[1]->ShowWindow(SW_HIDE);
	m_mytable.m_Dia[2]->ShowWindow(SW_HIDE);
	//CMenu Menu;//初始化菜单
	//Menu.LoadMenuW(IDR_MENU1);
	//SetMenu(&Menu);


	m_statusbar.Create(this);
	UINT statusId[4] = { 0x1003,0x1004,0x1005,0x1006 };
	// 设置分栏的个数和每个分栏的id
	m_statusbar.SetIndicators(statusId, _countof(statusId));
	// 设置分栏的宽度
	m_statusbar.SetPaneInfo(0, 0x1003, 0, 120);
	m_statusbar.SetPaneInfo(1, 0x1004, 0, 80);
	m_statusbar.SetPaneInfo(2, 0x1005, 0, 120);
	m_statusbar.SetPaneInfo(3, 0x1006, 0, 80);
	// 设置分栏中的文本
	m_statusbar.SetPaneText(0, _T("CPU使用率"), TRUE);
	m_statusbar.SetPaneText(2, _T("物理内存"), TRUE);
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
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C任务管理器Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C任务管理器Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C任务管理器Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





BOOL C任务管理器Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_HOTKEY&&pMsg->lParam == 0x1234)
	{
		if (IsWindowVisible() == TRUE)
			ShowWindow(SW_HIDE);
		else
			ShowWindow(SW_SHOW);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
