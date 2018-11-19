// ListModule.cpp : 实现文件
//

#include "stdafx.h"
#include "任务管理器.h"
#include "ListModule.h"
#include "afxdialogex.h"


// CListModule 对话框

IMPLEMENT_DYNAMIC(CListModule, CDialogEx)

CListModule::CListModule(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_MODULE, pParent)
{

}

CListModule::~CListModule()
{
}

void CListModule::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CListModule, CDialogEx)
END_MESSAGE_MAP()


// CListModule 消息处理程序
