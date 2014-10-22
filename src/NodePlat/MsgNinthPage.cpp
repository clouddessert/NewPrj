// MsgNinthPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgNinthPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgNinthPage property page

IMPLEMENT_DYNCREATE(CMsgNinthPage, CPropertyPage)

CMsgNinthPage::CMsgNinthPage() : CPropertyPage(CMsgNinthPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgNinthPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgNinthPage::~CMsgNinthPage()
{
}

void CMsgNinthPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgNinthPage)
	DDX_Control(pDX, IDC_LIST_TAISHI, m_taishi);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgNinthPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgNinthPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgNinthPage message handlers
