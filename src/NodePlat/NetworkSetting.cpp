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
	
}


void CNetworkSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetworkSetting)
	DDX_Control(pDX, IDC_IPADDRESS, m_ipaddr);
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
	
	//读取临时路径
	CString strTmp,strTmpA;
	CString	sPath;

	char host_name[255];
	//获取本地主机名称
	if (gethostname(host_name, sizeof(host_name)) == SOCKET_ERROR) 
	{
		//error
	}
	struct hostent *phe = gethostbyname(host_name);
	
	struct in_addr addr;
    memcpy(&addr,phe->h_addr_list[0],sizeof(struct in_addr));
	CString strLocalIP;
	strLocalIP.Format("%s", inet_ntoa(addr));
	
	//获得工程文件夹路径
	::GetCurrentDirectory(_MAX_PATH,sPath.GetBuffer(_MAX_PATH));
	sPath.ReleaseBuffer();
	sPath = sPath+_T("\\NetConfig.ini");
	
	::GetPrivateProfileString(_T("IP地址"), _T("服务器IP地址"), NULL, strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath);
	strTmp.ReleaseBuffer();

	DWORD dwIP; 
	dwIP = inet_addr(strTmp); 
	unsigned char *pIP = (unsigned char*)&dwIP; 
	m_ipaddr.SetAddress(*pIP, *(pIP+1), *(pIP+2), *(pIP+3));//显示服务器IP
	
	//获取IP,如果IP地址和本机IP一致,不添加!
	if (::GetPrivateProfileString(_T("编队IP"), _T("A船IP地址"), _T("127.0.0.1"), strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
	{
		strTmp.ReleaseBuffer();
		if (strTmp.Compare(strLocalIP))
		{
			theApp.IpMap.insert(make_pair(0, strTmp));
		}
		else
		{
			theApp.m_ThisNumber = 0;
			
		}
	}

	if (::GetPrivateProfileString(_T("编队IP"), _T("B船IP地址"), _T("127.0.0.1"), strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
	{
		strTmp.ReleaseBuffer();
		if (strTmp.Compare(strLocalIP))
		{
			theApp.IpMap.insert(make_pair(1, strTmp));
		}
		else
		{
			theApp.m_ThisNumber = 1;
			
		}
	}
	if (::GetPrivateProfileString(_T("编队IP"), _T("C船IP地址"), _T("127.0.0.1"), strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
	{
		strTmp.ReleaseBuffer();
		if (strTmp.Compare(strLocalIP))
		{
			theApp.IpMap.insert(make_pair(2, strTmp));
		}
		else
		{
			theApp.m_ThisNumber = 2;
			
		}
	}
	if (::GetPrivateProfileString(_T("编队IP"), _T("D船IP地址"), NULL, strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
	{
		strTmp.ReleaseBuffer();
		if (strTmp.Compare(strLocalIP))
		{
			theApp.IpMap.insert(make_pair(3, strTmp));
		}
		else
		{
			theApp.m_ThisNumber = 3;
			
		}
	}
	//strTmp.ReleaseBuffer();
	if (::GetPrivateProfileString(_T("编队IP"), _T("E船IP地址"), NULL, strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
	{
		strTmp.ReleaseBuffer();
		if (strTmp.Compare(strLocalIP))
		{
			theApp.IpMap.insert(make_pair(4, strTmp));
		}
		else
		{
			theApp.m_ThisNumber = 4;
			
		}
	}
	//strTmp.ReleaseBuffer();
	
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

	map<int,CString>::iterator pIp_Dat;
	
	int nTmp = 0;
		
	//清除显示列表
	((CListCtrl*)GetDlgItem(IDC_TEAMLIST))->DeleteAllItems();
	
	//显示数据
	for (pIp_Dat = theApp.IpMap.begin(); pIp_Dat != theApp.IpMap.end(); pIp_Dat++,++nTmp)
	{
		strTmp.Format("%d", pIp_Dat->first);
		((CListCtrl*)GetDlgItem(IDC_TEAMLIST))->InsertItem(nTmp, strTmp, 9);
		strTmp.Format("%s", pIp_Dat->second);
		((CListCtrl*)GetDlgItem(IDC_TEAMLIST))->SetItemText(nTmp, 1, strTmp);
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNetworkSetting::OnButtonclose() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
	
}
