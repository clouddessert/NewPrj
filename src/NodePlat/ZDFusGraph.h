#if !defined(AFX_ZDFUSGRAPH_H__FB312C83_32B9_4B6D_A337_DB9B9F31663E__INCLUDED_)
#define AFX_ZDFUSGRAPH_H__FB312C83_32B9_4B6D_A337_DB9B9F31663E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZDFusGraph.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// CZDFusGraph dialog

class CZDFusGraph : public CDialog
{
// Construction
public:
// 	void OpenIdentiDb();
// 	void ShowData();
// 	CDatabase m_dbfus;
	int cd_nb;// 与哪个舰协同
	int distant01;
	int distant02;
	int distant12;
	char name_self;
	char name_nb1;
	char name_nb2;
	int num;
	int count_factor;
	int a_factor;//方位
	int e_factor;//仰角
	int r_factor;//径距
	void showDataGraph(int autonum);
	void drawCoordination();
	void AddMsgList(CString strShow); //添加信息于LISTBOX 控件中
	CZDFusGraph(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZDFusGraph)
	enum { IDD = IDD_DIALOG_ZDFUSTU };
	CListBox	m_listWucha;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZDFusGraph)
    public:
	virtual void OnSetFont(CFont* pFont);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZDFusGraph)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDFUSGRAPH_H__FB312C83_32B9_4B6D_A337_DB9B9F31663E__INCLUDED_)
