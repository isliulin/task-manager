// MyTable.cpp : 实现文件
//

#include "stdafx.h"
#include "任务管理器.h"
#include "MyTable.h"


// CMyTable

IMPLEMENT_DYNAMIC(CMyTable, CTabCtrl)

CMyTable::CMyTable()
{

}

CMyTable::~CMyTable()
{
}


BEGIN_MESSAGE_MAP(CMyTable, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CMyTable::OnTcnSelchange)
END_MESSAGE_MAP()



// CMyTable 消息处理程序




void CMyTable::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int num = GetCurSel();
	switch (num)
	{
	case 0:
	{
		m_Dia[0]->ShowWindow(SW_SHOW);
		m_Dia[1]->ShowWindow(SW_HIDE);
		m_Dia[2]->ShowWindow(SW_HIDE);
	}
	break;
	case 1:
	{
		m_Dia[0]->ShowWindow(SW_HIDE);
		m_Dia[1]->ShowWindow(SW_SHOW);
		m_Dia[2]->ShowWindow(SW_HIDE);
	}
	break;
	case 2:
	{
		m_Dia[0]->ShowWindow(SW_HIDE);
		m_Dia[1]->ShowWindow(SW_HIDE);
		m_Dia[2]->ShowWindow(SW_SHOW);
	}
	break;
	default: break;
	}
}
