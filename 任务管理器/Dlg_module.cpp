// Dlg_module.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������.h"
#include "Dlg_module.h"
#include "afxdialogex.h"


// Dlg_module �Ի���

IMPLEMENT_DYNAMIC(Dlg_module, CDialogEx)

Dlg_module::Dlg_module(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_MODULE, pParent)
{

}

Dlg_module::~Dlg_module()
{
}

void Dlg_module::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_module);
}


BEGIN_MESSAGE_MAP(Dlg_module, CDialogEx)
END_MESSAGE_MAP()


// Dlg_module ��Ϣ�������


BOOL Dlg_module::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list_module.InsertColumn(0, _T("����ID"), LVCFMT_CENTER, 80);
	m_list_module.InsertColumn(1, _T("ģ��ID"), LVCFMT_CENTER, 80);
	m_list_module.InsertColumn(2, _T("ģ����"), LVCFMT_CENTER, 80);
	m_list_module.InsertColumn(3, _T("ģ��·��"), LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
