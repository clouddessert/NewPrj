// CommandPlatDoc.cpp : implementation of the CCommandPlatDoc class
//

#include "stdafx.h"
#include "CommandPlat.h"

#include "CommandPlatDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommandPlatDoc

IMPLEMENT_DYNCREATE(CCommandPlatDoc, CDocument)

BEGIN_MESSAGE_MAP(CCommandPlatDoc, CDocument)
	//{{AFX_MSG_MAP(CCommandPlatDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandPlatDoc construction/destruction

CCommandPlatDoc::CCommandPlatDoc()
{
	// TODO: add one-time construction code here

}

CCommandPlatDoc::~CCommandPlatDoc()
{
}

BOOL CCommandPlatDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCommandPlatDoc serialization

void CCommandPlatDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCommandPlatDoc diagnostics

#ifdef _DEBUG
void CCommandPlatDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCommandPlatDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCommandPlatDoc commands
