// Dlg_file.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������.h"
#include "Dlg_file.h"
#include "afxdialogex.h"


// Dlg_file �Ի���

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


// Dlg_file ��Ϣ�������


BOOL Dlg_file::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list_file.InsertColumn(0, L"�ļ���",0,180);
	m_list_file.InsertColumn(1, L"�ļ���С",0, 180);
	m_list_file.InsertColumn(2, L"����ʱ��",0, 180);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void Dlg_file::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFolderPickerDialog dlg;
	dlg.DoModal();//����ѡ���ļ���
	CString path = dlg.GetFolderPath();//��ȡ�ļ�·��
	m_edit.SetWindowText(path);//�ڱ༭����ʾ·��
	m_list_file.DeleteAllItems();//����б�
	printfile((const CStringA)path);
	/*��ʼ�����ļ���*/
}
void Dlg_file::printfile(const CStringA& dir)//�ݹ�����ļ�������ʾ�ļ���
{
	WIN32_FIND_DATAA fdata = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	hFind = FindFirstFileA(dir + "\\*", &fdata);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}
	//ɾ�����нڵ�
	DWORD dwIndex = 0;
	CString str;
	do
	{
		if (strcmp(fdata.cFileName, ".") == 0 ||
			strcmp(fdata.cFileName, "..") == 0)
		{
			continue;
		}
		//�Ȳ���һ��item���б�
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
			m_list_file.SetItemText(dwIndex, 1, str1);//����ļ���С

			FileTimeToLocalFileTime(&fdata.ftCreationTime, &fdata.ftCreationTime);
			//ת��ΪLOCALʱ��
			SYSTEMTIME st = { 0 };
			// ���ļ�ʱ��ת��ϵͳʱ��
			FileTimeToSystemTime(&fdata.ftCreationTime, &st);//ת��Ϊϵͳʱ��

			str2.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"),
				st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

			m_list_file.SetItemText(dwIndex, 2, str2);//����ļ�����ʱ��
			dwIndex++;
		}
	} while (FindNextFileA(hFind, &fdata));
}

void Dlg_file::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFolderPickerDialog dlg;
	dlg.DoModal();//����ѡ���ļ���
	CString path = dlg.GetFolderPath();//��ȡ�ļ�·��
	m_edit.SetWindowText(path);//�ڱ༭����ʾ·��
	m_list_file.DeleteAllItems();//����б�
	clearfile((const CStringA)path);
	MessageBox(L"����ɹ�");
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
	//���������������list�ؼ�
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
		
		//�Ȳ���һ��item���б�
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
			m_list_file.SetItemText(dwIndex, 1, str1);//����ļ���С

			FileTimeToLocalFileTime(&fdata.ftCreationTime, &fdata.ftCreationTime);
			//ת��ΪLOCALʱ��
			SYSTEMTIME st = { 0 };
			// ���ļ�ʱ��ת��ϵͳʱ��
			FileTimeToSystemTime(&fdata.ftCreationTime, &st);//ת��Ϊϵͳʱ��

			str2.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"),
				st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

			m_list_file.SetItemText(dwIndex, 2, str2);//����ļ�����ʱ��
			dwIndex++;
		}
	} while (FindNextFileA(hFind, &fdata));
}
