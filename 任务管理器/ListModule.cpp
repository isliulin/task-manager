// ListModule.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������.h"
#include "ListModule.h"
#include "afxdialogex.h"


// CListModule �Ի���

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


// CListModule ��Ϣ�������
