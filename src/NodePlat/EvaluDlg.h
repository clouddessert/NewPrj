#if !defined(AFX_EVALUDLG_H__78965C3B_B99B_42B7_BF5B_2D208B014B4C__INCLUDED_)
#define AFX_EVALUDLG_H__78965C3B_B99B_42B7_BF5B_2D208B014B4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EvaluDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEvaluDlg dialog
#include "afxdb.h"
class CEvaluDlg : public CDialog
{
// Construction
public:
	int nmulFlag; //0时为单舰识别,1时为多舰识别
	CDatabase m_dbfus;
	CDatabase m_dbidenti;
	void OpenIdentiDb();
	void OpenFusDb();
	bool checkDB(int num,int flag);
	void FindLocData(int autonum, int &count, double &l_bzc, double &b_bzc);
	CEvaluDlg(CWnd* pParent = NULL);   // standard constructor
	int l;
	int f;
// Dialog Data
	//{{AFX_DATA(CEvaluDlg)
	enum { IDD = IDD_DIALOG_EVALU };
	CComboBox	m_ctrLB;
	CComboBox	m_ctrFS;
	long	m_pihao;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEvaluDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEvaluDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeComboFangshi();
	afx_msg void OnRadioBiaoge();
	afx_msg void OnRadioTuxing();
	afx_msg void OnSelchangeComboLeibie();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVALUDLG_H__78965C3B_B99B_42B7_BF5B_2D208B014B4C__INCLUDED_)
