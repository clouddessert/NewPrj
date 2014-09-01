// NodePlatDoc.h : interface of the CNodePlatDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODEPLATDOC_H__D1E6E59A_A44F_4D6E_AD35_CD35332AE50C__INCLUDED_)
#define AFX_NODEPLATDOC_H__D1E6E59A_A44F_4D6E_AD35_CD35332AE50C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNodePlatDoc : public CDocument
{
protected: // create from serialization only
	CNodePlatDoc();
	DECLARE_DYNCREATE(CNodePlatDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNodePlatDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnReceiveMsg();
	virtual ~CNodePlatDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	//{{AFX_MSG(CNodePlatDoc)
	afx_msg void OnConnectsvr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NODEPLATDOC_H__D1E6E59A_A44F_4D6E_AD35_CD35332AE50C__INCLUDED_)
