#if !defined(AFX_DIALOGPLA_H__72C06BCE_DEB0_42FB_8F4A_73303BC8501C__INCLUDED_)
#define AFX_DIALOGPLA_H__72C06BCE_DEB0_42FB_8F4A_73303BC8501C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogPLA.h : header file
//
#include "ParamFourthPage.h"
/////////////////////////////////////////////////////////////////////////////
// CDialogPLA dialog

class CDialogPLA : public CDialog
{
// Construction
public:
	void AddToGrid();
	CDialogPLA(CWnd* pParent = NULL);   // standard constructor
	int ID;
	
	int ids;
	CParamFourthPage ado;
// Dialog Data
	//{{AFX_DATA(CDialogPLA)
	enum { IDD = IDD_DB_PLA };
	CComboBox	m_high;
	CComboBox	m_addspeed;
	CComboBox	m_speed;
	CComboBox	m_azimuth;
	CComboBox	m_rd;
	CComboBox	m_gog;
	CComboBox	m_pla;
	CComboBox	m_com;
	CComboBox	m_esm;
	CComboBox	m_tra;
	CListCtrl	m_Grid;
	CString	m_id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogPLA)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogPLA)
	virtual BOOL OnInitDialog();
	afx_msg void OnButadd();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButmod();
	afx_msg void OnButdel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGPLA_H__72C06BCE_DEB0_42FB_8F4A_73303BC8501C__INCLUDED_)
