// CommandPlatDoc.h : interface of the CCommandPlatDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMANDPLATDOC_H__842F6B14_B8FB_40E4_B54D_8144D6530AAB__INCLUDED_)
#define AFX_COMMANDPLATDOC_H__842F6B14_B8FB_40E4_B54D_8144D6530AAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCommandPlatDoc : public CDocument
{
protected: // create from serialization only
	CCommandPlatDoc();
	DECLARE_DYNCREATE(CCommandPlatDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommandPlatDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCommandPlatDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCommandPlatDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDPLATDOC_H__842F6B14_B8FB_40E4_B54D_8144D6530AAB__INCLUDED_)
