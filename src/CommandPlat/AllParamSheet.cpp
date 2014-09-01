// AllParamSheet.cpp : implementation file
//

#include "stdafx.h"
#include "CommandPlat.h"
#include "AllParamSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAllParamSheet

IMPLEMENT_DYNAMIC(CAllParamSheet, CPropertySheet)

CAllParamSheet::CAllParamSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CAllParamSheet::CAllParamSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_FstPage);
	AddPage(&m_SecPage);
}

CAllParamSheet::~CAllParamSheet()
{
}


BEGIN_MESSAGE_MAP(CAllParamSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CAllParamSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAllParamSheet message handlers

BOOL CAllParamSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
	//设置
	TC_ITEM item;
	item.mask = TCIF_TEXT;
	item.pszText = "我方配置";	
	GetTabControl()->SetItem(0, &item);
	item.mask = TCIF_TEXT;
	item.pszText = "敌方配置";
	GetTabControl()->SetItem(1, &item);

	return bResult;
}
