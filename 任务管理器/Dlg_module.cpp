// Dlg_module.cpp : 实现文件
//

#include "stdafx.h"
#include "任务管理器.h"
#include "Dlg_module.h"
#include "afxdialogex.h"


// Dlg_module 对话框

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


// Dlg_module 消息处理程序


BOOL Dlg_module::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list_module.InsertColumn(0, _T("进程ID"), LVCFMT_CENTER, 80);
	m_list_module.InsertColumn(1, _T("模块ID"), LVCFMT_CENTER, 80);
	m_list_module.InsertColumn(2, _T("模块名"), LVCFMT_CENTER, 80);
	m_list_module.InsertColumn(3, _T("模块路径"), LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
