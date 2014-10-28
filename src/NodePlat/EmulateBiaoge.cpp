// EmulateBiaoge.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "EmulateBiaoge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CEmulateBiaoge dialog


CEmulateBiaoge::CEmulateBiaoge(CWnd* pParent /*=NULL*/)
	: CDialog(CEmulateBiaoge::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmulateBiaoge)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEmulateBiaoge::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmulateBiaoge)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmulateBiaoge, CDialog)
	//{{AFX_MSG_MAP(CEmulateBiaoge)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmulateBiaoge message handlers

BOOL CEmulateBiaoge::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hFus_wnd = GetSafeHwnd();
	
	CString FUS_Columns[]=
	{
		    _T("合批号"),//0
			_T("下发类型"),//1		
			_T("真实类型"),//2
			_T("识别类型"),//3
			_T("识别率"),//4		
	};
	
	
	((CListCtrl*)GetDlgItem(IDC_LIST_FUS))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(FUS_Columns)/sizeof(FUS_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_FUS))->InsertColumn(i, FUS_Columns[i], LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
