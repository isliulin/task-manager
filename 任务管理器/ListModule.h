#pragma once


// CListModule 对话框

class CListModule : public CDialogEx
{
	DECLARE_DYNAMIC(CListModule)

public:
	CListModule(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CListModule();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MODULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
