#if !defined(AFX_NETWORKSETTING_H__ACE7964D_DF91_48DB_B44A_278A15561DBF__INCLUDED_)
#define AFX_NETWORKSETTING_H__ACE7964D_DF91_48DB_B44A_278A15561DBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetworkSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetworkSetting dialog

class CNetworkSetting : public CDialog
{
// Construction
public:
	CNetworkSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetworkSetting)
	enum { IDD = IDD_NETWORKDLG };
	CIPAddressCtrl	m_ipaddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetworkSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetworkSetting)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonclose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETWORKSETTING_H__ACE7964D_DF91_48DB_B44A_278A15561DBF__INCLUDED_)
