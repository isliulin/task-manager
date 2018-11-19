// Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "任务管理器.h"
#include "Dlg.h"
#include "afxdialogex.h"


// Dlg 对话框

IMPLEMENT_DYNAMIC(Dlg, CDialogEx)

Dlg::Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_HEAP, pParent)
{

}

Dlg::~Dlg()
{
}

void Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_heap);
}


BEGIN_MESSAGE_MAP(Dlg, CDialogEx)
END_MESSAGE_MAP()	


// Dlg 消息处理程序


BOOL Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list_heap.InsertColumn(0, _T("获取不了"), LVCFMT_CENTER, 200);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
