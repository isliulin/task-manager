// Dlg_file.cpp : 实现文件
//

#include "stdafx.h"
#include "任务管理器.h"
#include "Dlg_file.h"
#include "afxdialogex.h"


// Dlg_file 对话框

IMPLEMENT_DYNAMIC(Dlg_file, CDialogEx) 

Dlg_file::Dlg_file(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_FILE, pParent)
{

}

Dlg_file::~Dlg_file()
{
}

void Dlg_file::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_file);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(Dlg_file, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Dlg_file::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Dlg_file::OnBnClickedButton2)
END_MESSAGE_MAP()


// Dlg_file 消息处理程序


BOOL Dlg_file::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list_file.InsertColumn(0, L"文件名",0,180);
	m_list_file.InsertColumn(1, L"文件大小",0, 180);
	m_list_file.InsertColumn(2, L"创建时间",0, 180);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Dlg_file::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFolderPickerDialog dlg;
	dlg.DoModal();//弹出选择文件框
	CString path = dlg.GetFolderPath();//获取文件路径
	m_edit.SetWindowText(path);//在编辑框显示路径
	m_list_file.DeleteAllItems();//清空列表
	printfile((const CStringA)path);
	/*开始遍历文件夹*/
}
void Dlg_file::printfile(const CStringA& dir)//递归遍历文件，不显示文件夹
{
	WIN32_FIND_DATAA fdata = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	hFind = FindFirstFileA(dir + "\\*", &fdata);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}
	//删除所有节点
	DWORD dwIndex = 0;
	CString str;
	do
	{
		if (strcmp(fdata.cFileName, ".") == 0 ||
			strcmp(fdata.cFileName, "..") == 0)
		{
			continue;
		}
		//先插入一个item到列表
		if (fdata.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			printfile(dir + "\\" + fdata.cFileName);
		}
		else
		{
			CString str1, str2;
			m_list_file.InsertItem(dwIndex, L"");
			m_list_file.SetItemText(dwIndex, 0, dir + L"\\" + fdata.cFileName);

			str1.Format(L"%lf kb", fdata.nFileSizeLow / 1024.0);
			m_list_file.SetItemText(dwIndex, 1, str1);//输出文件大小

			FileTimeToLocalFileTime(&fdata.ftCreationTime, &fdata.ftCreationTime);
			//转换为LOCAL时间
			SYSTEMTIME st = { 0 };
			// 将文件时间转换系统时间
			FileTimeToSystemTime(&fdata.ftCreationTime, &st);//转换为系统时间

			str2.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"),
				st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

			m_list_file.SetItemText(dwIndex, 2, str2);//输出文件创建时间
			dwIndex++;
		}
	} while (FindNextFileA(hFind, &fdata));
}

void Dlg_file::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CFolderPickerDialog dlg;
	dlg.DoModal();//弹出选择文件框
	CString path = dlg.GetFolderPath();//获取文件路径
	m_edit.SetWindowText(path);//在编辑框显示路径
	m_list_file.DeleteAllItems();//清空列表
	clearfile((const CStringA)path);
	MessageBox(L"清理成功");
}
void Dlg_file::clearfile(const CStringA& dir)
{

	WIN32_FIND_DATAA fdata = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	hFind = FindFirstFileA(dir + "\\*", &fdata);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}
	//继续遍历并输出到list控件
	DWORD dwIndex = 0;
	do
	{
		if (strcmp(fdata.cFileName, ".") == 0 ||
			strcmp(fdata.cFileName, "..") == 0)
		{
			continue;
		}
		int len = strlen(fdata.cFileName);
		if (fdata.cFileName[len - 4]=='.')
		{
			char buff[5]{};
			buff[0] = fdata.cFileName[len - 4];
			buff[1] = fdata.cFileName[len - 3];
			buff[2] = fdata.cFileName[len - 2];
			buff[3] = fdata.cFileName[len - 1];
			if (strcmp(buff, ".ncb") == 0 || strcmp(buff, ".plg") == 0 || strcmp(buff, ".pch") == 0 ||
				strcmp(buff, ".idb") == 0 || strcmp(buff, ".ilk") == 0 || strcmp(buff, ".pdb") == 0 ||
				strcmp(buff, ".obj") == 0 || strcmp(buff, ".exp") == 0 || strcmp(buff, ".aps") == 0 ||
				strcmp(buff, ".opt") == 0 || strcmp(buff, ".sdf") == 0 || strcmp(buff, ".dep") == 0 || 
				strcmp(buff, ".sbr") == 0)
			{
				CStringA filename = dir + "\\" + fdata.cFileName;
				DeleteFileA(filename);
				continue;
			}
		}
		if (fdata.cFileName[len - 5] == '.')
		{
			char buff[6]{};
			buff[0] = fdata.cFileName[len - 5];
			buff[1] = fdata.cFileName[len - 4];
			buff[2] = fdata.cFileName[len - 3];
			buff[3] = fdata.cFileName[len - 2];
			buff[4] = fdata.cFileName[len - 1];
			if (strcmp(buff, ".ipch") == 0 || strcmp(buff, ".tlog") == 0)
			{
				CStringA filename = dir + "\\" + fdata.cFileName;
				DeleteFileA(filename);
				continue;
			}
		}
		
		//先插入一个item到列表
		if (fdata.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			clearfile(dir + "\\" + fdata.cFileName);
		}
		else
		{
			CString str1, str2;
			m_list_file.InsertItem(dwIndex, L"");
			m_list_file.SetItemText(dwIndex, 0, dir + L"\\" + fdata.cFileName);

			str1.Format(L"%lf kb", fdata.nFileSizeLow / 1024.0);
			m_list_file.SetItemText(dwIndex, 1, str1);//输出文件大小

			FileTimeToLocalFileTime(&fdata.ftCreationTime, &fdata.ftCreationTime);
			//转换为LOCAL时间
			SYSTEMTIME st = { 0 };
			// 将文件时间转换系统时间
			FileTimeToSystemTime(&fdata.ftCreationTime, &st);//转换为系统时间

			str2.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"),
				st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

			m_list_file.SetItemText(dwIndex, 2, str2);//输出文件创建时间
			dwIndex++;
		}
	} while (FindNextFileA(hFind, &fdata));
}
