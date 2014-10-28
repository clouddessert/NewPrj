#if !defined(AFX_EIDENFUSVALU_H__E5F1CDFD_BE21_4525_9207_2FC49F092E1E__INCLUDED_)
#define AFX_EIDENFUSVALU_H__E5F1CDFD_BE21_4525_9207_2FC49F092E1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EIdenFusVALU.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEIdenFusVALU dialog

class CEIdenFusVALU : public CDialog
{
// Construction
public:
	int m_radio;
	int maxcode;
	int maxcode_all;

	CEIdenFusVALU(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEIdenFusVALU)
	enum { IDD = IDD_DIALOG_IdenFus_EVALU };
	CComboBox	m_TargetCode;
	CComboBox	m_EIdenFusSort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEIdenFusVALU)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEIdenFusVALU)
	virtual BOOL OnInitDialog();
	afx_msg void OnQueding();
	afx_msg void OnRadioClicked(UINT nID);
	afx_msg void OnSelchangeCombosort();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EIDENFUSVALU_H__E5F1CDFD_BE21_4525_9207_2FC49F092E1E__INCLUDED_)
