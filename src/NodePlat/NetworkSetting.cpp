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
	
	//��ȡ��ʱ·��
	CString strTmp,strTmpA;
	CString	sPath;

	char host_name[255];
	//��ȡ������������
	if (gethostname(host_name, sizeof(host_name)) == SOCKET_ERROR) 
	{
		//error
	}
	struct hostent *phe = gethostbyname(host_name);
	
	struct in_addr addr;
    memcpy(&addr,phe->h_addr_list[0],sizeof(struct in_addr));
	CString strLocalIP;
	strLocalIP.Format("%s", inet_ntoa(addr));
	
	//��ù����ļ���·��
	::GetCurrentDirectory(_MAX_PATH,sPath.GetBuffer(_MAX_PATH));
	sPath.ReleaseBuffer();
	sPath = sPath+_T("\\NetConfig.ini");
	
	::GetPrivateProfileString(_T("IP��ַ"), _T("������IP��ַ"), NULL, strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath);
	strTmp.ReleaseBuffer();

	DWORD dwIP; 
	dwIP = inet_addr(strTmp); 
	unsigned char *pIP = (unsigned char*)&dwIP; 
	m_ipaddr.SetAddress(*pIP, *(pIP+1), *(pIP+2), *(pIP+3));//��ʾ������IP
	
	//��ȡIP,���IP��ַ�ͱ���IPһ��,�����!
	if (::GetPrivateProfileString(_T("���IP"), _T("A��IP��ַ"), _T("127.0.0.1"), strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
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

	if (::GetPrivateProfileString(_T("���IP"), _T("B��IP��ַ"), _T("127.0.0.1"), strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
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
	if (::GetPrivateProfileString(_T("���IP"), _T("C��IP��ַ"), _T("127.0.0.1"), strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
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
	if (::GetPrivateProfileString(_T("���IP"), _T("D��IP��ַ"), NULL, strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
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
	if (::GetPrivateProfileString(_T("���IP"), _T("E��IP��ַ"), NULL, strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
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
		_T("���"),
		_T("IP"),			
	};
		
	((CListCtrl*)GetDlgItem(IDC_TEAMLIST))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
//	for(int i=0; i<sizeof(Team_Columns)/sizeof(Team_Columns[0]); ++i)
//		((CListCtrl*)GetDlgItem(IDC_TEAMLIST))->InsertColumn(i, Team_Columns[i], LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_TEAMLIST))->InsertColumn(0, Team_Columns[0], LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_TEAMLIST))->InsertColumn(1, Team_Columns[1], LVCFMT_CENTER, 200);

	map<int,CString>::iterator pIp_Dat;
	
	int nTmp = 0;
		
	//�����ʾ�б�
	((CListCtrl*)GetDlgItem(IDC_TEAMLIST))->DeleteAllItems();
	
	//��ʾ����
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
