#if !defined(AFX_ALLPARAMSHEET_H__AE04CE4D_2A74_4072_AFF6_E7448D514219__INCLUDED_)
#define AFX_ALLPARAMSHEET_H__AE04CE4D_2A74_4072_AFF6_E7448D514219__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AllParamSheet.h : header file
//

#include "ParamFstPage.h"
#include "ParamSecondPage.h"
#include "ParamThirdPage.h"
#include "ParamFourthPage.h"
/////////////////////////////////////////////////////////////////////////////
// CAllParamSheet

class CAllParamSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CAllParamSheet)

// Construction
public:
	CAllParamSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CAllParamSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
private:
	CParamFstPage m_FstPage;
	CParamSecondPage m_SecPage;
	CParamThirdPage m_ThirdPage;
	CParamFourthPage m_FourthPage;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAllParamSheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAllParamSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAllParamSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALLPARAMSHEET_H__AE04CE4D_2A74_4072_AFF6_E7448D514219__INCLUDED_)
