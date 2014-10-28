#if !defined(AFX_DIALOGFUN_H__00938C06_887A_4D7D_A58F_ED5A587C4D9C__INCLUDED_)
#define AFX_DIALOGFUN_H__00938C06_887A_4D7D_A58F_ED5A587C4D9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogFUN.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogFUN dialog
#include "ParamFourthPage.h"
class CDialogFUN : public CDialog
{
// Construction
public:
	void AddToGrid();
	CDialogFUN(CWnd* pParent = NULL);   // standard constructor
	int ID;

	int ids;
	CParamFourthPage ado;
// Dialog Data
	//{{AFX_DATA(CDialogFUN)
	enum { IDD = IDD_DB_FUN };
	CComboBox	m_fun;
	CComboBox	m_tra;
	CComboBox	m_typ;
	CListCtrl	m_Grid;
	CString	m_id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogFUN)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogFUN)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButAdd();
	afx_msg void OnButmod();
	afx_msg void OnButDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGFUN_H__00938C06_887A_4D7D_A58F_ED5A587C4D9C__INCLUDED_)
