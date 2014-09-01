// MsgAllSheet.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "MsgAllSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgAllSheet

IMPLEMENT_DYNAMIC(CMsgAllSheet, CPropertySheet)

CMsgAllSheet::CMsgAllSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CMsgAllSheet::CMsgAllSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_FstPage);
	AddPage(&m_SecPage);
	AddPage(&m_ThreePage);
	AddPage(&m_FourthPage);
}

CMsgAllSheet::~CMsgAllSheet()
{
}


BEGIN_MESSAGE_MAP(CMsgAllSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CMsgAllSheet)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgAllSheet message handlers

BOOL CMsgAllSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
	//设置
	TC_ITEM item;
	item.mask = TCIF_TEXT;
	item.pszText = "ESM侦查信息";	
	GetTabControl()->SetItem(0, &item);
	item.mask = TCIF_TEXT;
	item.pszText = "通讯信息";
	GetTabControl()->SetItem(1, &item);
	item.mask = TCIF_TEXT;
	item.pszText = "航迹信息";
	GetTabControl()->SetItem(2, &item);
	item.mask = TCIF_TEXT;
	item.pszText = "单舰融合识别信息";
	GetTabControl()->SetItem(3, &item);

	return bResult;
}
