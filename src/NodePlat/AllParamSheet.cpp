// AllParamSheet.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
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
	AddPage(&m_ThirdPage);
	AddPage(&m_FourthPage);
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
	//����
	TC_ITEM item;
	item.mask = TCIF_TEXT;
	item.pszText = "�ҷ�����";	
	GetTabControl()->SetItem(0, &item);
	item.mask = TCIF_TEXT;
	item.pszText = "�з�����";
	GetTabControl()->SetItem(1, &item);
	item.mask = TCIF_TEXT;
	item.pszText = "������Ϣ��ʾ";
	GetTabControl()->SetItem(2, &item);
	item.mask = TCIF_TEXT;
	item.pszText = "�����";
	GetTabControl()->SetItem(3, &item);
	return bResult;
}
