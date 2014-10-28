#if !defined(AFX_ZDSHIBIETU_H__2A588482_8459_4A51_A58D_FB88909336A6__INCLUDED_)
#define AFX_ZDSHIBIETU_H__2A588482_8459_4A51_A58D_FB88909336A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZDSHIBIETU.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZDSHIBIETU dialog

class CZDSHIBIETU : public CDialog
{
// Construction
public:
	CZDSHIBIETU(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZDSHIBIETU)
	enum { IDD = IDD_DIALOG_ZDSHIBIETU };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZDSHIBIETU)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZDSHIBIETU)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDSHIBIETU_H__2A588482_8459_4A51_A58D_FB88909336A6__INCLUDED_)
