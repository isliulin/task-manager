#pragma once


// CMyTable

class CMyTable : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTable)

public:
	CMyTable();
	virtual ~CMyTable();
	CDialogEx* m_Dia[3];
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


