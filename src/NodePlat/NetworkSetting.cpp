// NetworkSetting.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "NetworkSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CNetworkSetting dialog


CNetworkSetting::CNetworkSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CNetworkSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetworkSetting)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	//读取临时路径
	CString strTmp,strTmpA;
	CString	sPath;
	
	//获得工程文件夹路径
	::GetCurrentDirectory(_MAX_PATH,sPath.GetBuffer(_MAX_PATH));
	sPath.ReleaseBuffer();
	sPath = sPath+_T("\\NetConfig.ini");
	
	::GetPrivateProfileString(_T("IP地址"), _T("服务器IP地址"), _T("127.0.0.1"), strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath);
	strTmp.ReleaseBuffer();
	
// 	//保存当前IP
// 	::WritePrivateProfileString(_T("IP地址"), _T("服务器IP地址"), strTmp, sPath);

// 	::GetPrivateProfileString(_T("编队IP"), _T("A船IP"), _T("127.0.0.1"), strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath);
// 	strTmp.ReleaseBuffer();


// 	theApp.hIp_wnd = GetSafeHwnd();
// 	
// 	CString Team_Columns[]=
// 	{
// 		_T("编号"),
// 			_T("IP"),
// 			
// 	};
// 	
// 	
// 	((CListCtrl*)GetDlgItem(IDC_TEAMLIST))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
// 	
// 	for(int i=0; i<sizeof(Team_Columns)/sizeof(Team_Columns[0]); ++i)
// 		((CListCtrl*)GetDlgItem(IDC_TEAMLIST))->InsertColumn(i, Team_Columns[i], LVCFMT_CENTER, 100);


	
	
}


void CNetworkSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetworkSetting)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetworkSetting, CDialog)
	//{{AFX_MSG_MAP(CNetworkSetting)
	ON_BN_CLICKED(IDC_BUTTONCLOSE, OnButtonclose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetworkSetting message handlers



BOOL CNetworkSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
//	theApp.hIp_wnd = GetSafeHwnd();
	
	CString Team_Columns[]=
	{
		_T("编号"),
		_T("IP"),			
	};
		
	((CListCtrl*)GetDlgItem(IDC_TEAMLIST))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
//	for(int i=0; i<sizeof(Team_Columns)/sizeof(Team_Columns[0]); ++i)
//		((CListCtrl*)GetDlgItem(IDC_TEAMLIST))->InsertColumn(i, Team_Columns[i], LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_TEAMLIST))->InsertColumn(0, Team_Columns[0], LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_TEAMLIST))->InsertColumn(1, Team_Columns[1], LVCFMT_CENTER, 200);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNetworkSetting::OnButtonclose() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
	
}
