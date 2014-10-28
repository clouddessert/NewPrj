// ZDSHIBIETU.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "ZDSHIBIETU.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZDSHIBIETU dialog


CZDSHIBIETU::CZDSHIBIETU(CWnd* pParent /*=NULL*/)
	: CDialog(CZDSHIBIETU::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZDSHIBIETU)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CZDSHIBIETU::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZDSHIBIETU)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZDSHIBIETU, CDialog)
	//{{AFX_MSG_MAP(CZDSHIBIETU)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZDSHIBIETU message handlers

BOOL CZDSHIBIETU::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
