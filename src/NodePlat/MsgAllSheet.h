#if !defined(AFX_MSGALLSHEET_H__84F16356_7E96_425E_8B17_E3C2B615A287__INCLUDED_)
#define AFX_MSGALLSHEET_H__84F16356_7E96_425E_8B17_E3C2B615A287__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgAllSheet.h : header file
//
#include "MsgFstPage.h"
#include "MsgSecPage.h"
#include "MsgThreePage.h"
#include "MsgFourthPage.h"
/////////////////////////////////////////////////////////////////////////////
// CMsgAllSheet

class CMsgAllSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMsgAllSheet)

// Construction
public:
	CMsgAllSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMsgAllSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
private:
	CMsgFstPage m_FstPage;
	CMsgSecPage m_SecPage;
	CMsgThreePage m_ThreePage;
	CMsgFourthPage m_FourthPage;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgAllSheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMsgAllSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMsgAllSheet)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGALLSHEET_H__84F16356_7E96_425E_8B17_E3C2B615A287__INCLUDED_)
