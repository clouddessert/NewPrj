#if !defined(AFX_PARAMTHIRDPAGE_H__42EF4390_8FBF_4FE8_B52A_3F75DBB070F4__INCLUDED_)
#define AFX_PARAMTHIRDPAGE_H__42EF4390_8FBF_4FE8_B52A_3F75DBB070F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParamThirdPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParamThirdPage dialog

class CParamThirdPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CParamThirdPage)

// Construction
public:
	CParamThirdPage();
	~CParamThirdPage();

// Dialog Data
	//{{AFX_DATA(CParamThirdPage)
	enum { IDD = IDD_PARAM_DLG_THIRD };
	CListBox	m_AddMsgList;
	//}}AFX_DATA

public:
	//void OnAddMsgList(CString strShow);
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CParamThirdPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CParamThirdPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnAddMsgList(WPARAM wParam, LPARAM lParam);
 	//afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMTHIRDPAGE_H__42EF4390_8FBF_4FE8_B52A_3F75DBB070F4__INCLUDED_)
