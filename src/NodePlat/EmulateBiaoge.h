#if !defined(AFX_EMULATEBIAOGE_H__05997B87_909F_43E5_A6FF_3B44A2669952__INCLUDED_)
#define AFX_EMULATEBIAOGE_H__05997B87_909F_43E5_A6FF_3B44A2669952__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EmulateBiaoge.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEmulateBiaoge dialog

class CEmulateBiaoge : public CDialog
{
// Construction
public:
	CEmulateBiaoge(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEmulateBiaoge)
	enum { IDD = IDD_DIG_FUSEMULATE_BIAOGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmulateBiaoge)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEmulateBiaoge)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMULATEBIAOGE_H__05997B87_909F_43E5_A6FF_3B44A2669952__INCLUDED_)
