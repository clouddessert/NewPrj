// ParamSecondPage.cpp : implementation file
//

#include "stdafx.h"
#include "CommandPlat.h"
#include "ParamSecondPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParamSecondPage property page

IMPLEMENT_DYNCREATE(CParamSecondPage, CPropertyPage)

CParamSecondPage::CParamSecondPage() : CPropertyPage(CParamSecondPage::IDD)
{
	//{{AFX_DATA_INIT(CParamSecondPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CParamSecondPage::~CParamSecondPage()
{
}

void CParamSecondPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParamSecondPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParamSecondPage, CPropertyPage)
	//{{AFX_MSG_MAP(CParamSecondPage)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParamSecondPage message handlers

void CParamSecondPage::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	this->ShowWindow(SW_MAXIMIZE);
	
	//ÅÐ¶ÏÊÇ·ñ´æÔÚ¶¥²ã´°¿Ú
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_ENEMY_TREE)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}

BOOL CParamSecondPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CTreeCtrl *pOwner = (CTreeCtrl*)(CTreeCtrl*)GetDlgItem(IDC_ENEMY_TREE);
	
	HTREEITEM hTmp =pOwner->InsertItem(_T("µÐ·½ÅäÖÃ"), 0, 0);
	
	pOwner->InsertItem(_T("º½Ä¸"), 1, 1, hTmp);
	pOwner->InsertItem(_T("·É»ú"), 1, 1, hTmp);
	
	pOwner->Expand(hTmp, TVE_EXPAND);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
