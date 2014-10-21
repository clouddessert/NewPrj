// ParamThirdPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "ParamThirdPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////
extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CParamThirdPage property page

IMPLEMENT_DYNCREATE(CParamThirdPage, CPropertyPage)

CParamThirdPage::CParamThirdPage() : CPropertyPage(CParamThirdPage::IDD)
{
	//{{AFX_DATA_INIT(CParamThirdPage)
	//}}AFX_DATA_INIT
}

CParamThirdPage::~CParamThirdPage()
{
}

void CParamThirdPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParamThirdPage)
	DDX_Control(pDX, IDC_LIST_MSGDISPLAY, m_AddMsgList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParamThirdPage, CPropertyPage)
	//{{AFX_MSG_MAP(CParamThirdPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_DISPLAY_MSG, OnAddMsgList)
 
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParamThirdPage message handlers

void CParamThirdPage::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	this->ShowWindow(SW_MAXIMIZE);
	
	//�ж��Ƿ���ڶ��㴰��
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_MSGDISPLAY)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}

	
}

BOOL CParamThirdPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	theApp.hDISPLAY_wnd = GetSafeHwnd();

// 	CString str1,str2;
// 	theApp.m_MsgDisplay.Format("����Դ��ʧ");
// 	//str2.Format("");
//   	AddMsgList(theApp.m_MsgDisplay);
// 	str1.Format("����Դ����");
// 	//str2.Format("");
//   	AddMsgList(str1);

//    SetTimer(100,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




// void CParamThirdPage::AddMsgList(CString IP,CString str) //�����Ϣ��LISTBOX �ؼ���
// {
// 	SYSTEMTIME tm;
// 	GetLocalTime(&tm);
// 	CString time;
// 	time.Format(_T(" %d:%02d"), tm.wHour, tm.wMinute);
// 	CString strShow;
// 	strShow = IP+"��"+time+str;
// // 	if (IP=="�ڽ�")
// // 	{
// // 		
// // 	}else
// // 	{
// 		
//  		m_AddMsgList.AddString(strShow);
// //	}
// 	
// 	int numList=m_AddMsgList.GetCount()-1;
// 	//	GetDlgItem(IDC_BUTTON_CLEAR)->EnableWindow(true);
// 	m_AddMsgList.SetTopIndex(numList);
// 	m_AddMsgList.SetCurSel(numList);
// 	//ˮƽ����
// 	int max_width=0;
// 	CSize sz;
// 	CClientDC dc(this);
// 	for(int i=0;i<m_AddMsgList.GetCount();i++)
// 	{
// 		m_AddMsgList.GetText(i,str);
// 		sz=dc.GetTextExtent(str);
// 		if(max_width<sz.cx)
// 			max_width=sz.cx;
// 	}
// 	m_AddMsgList.SendMessage(LB_SETHORIZONTALEXTENT,max_width,0);
// }
LRESULT CParamThirdPage::OnAddMsgList(WPARAM wParam, LPARAM lParam)
//void CParamThirdPage::OnAddMsgList(CString strShow) //�����Ϣ��LISTBOX �ؼ���
{
	if (0 == wParam)
	{
		m_AddMsgList.AddString(theApp.m_MsgDisplay);
		
		
		int numList=m_AddMsgList.GetCount()-1;
		//	GetDlgItem(IDC_BUTTON_CLEAR)->EnableWindow(true);
		m_AddMsgList.SetTopIndex(numList);
		m_AddMsgList.SetCurSel(numList);
		//ˮƽ����
		int max_width=0;
		CSize sz;
		CClientDC dc(this);
		for(int i=0;i<m_AddMsgList.GetCount();i++)
		{
			m_AddMsgList.GetText(i,theApp.m_MsgDisplay);
			sz=dc.GetTextExtent(theApp.m_MsgDisplay);
			if(max_width<sz.cx)
				max_width=sz.cx;
		}
		m_AddMsgList.SendMessage(LB_SETHORIZONTALEXTENT,max_width,0);

	}
	


	return 0;  
}

// void CParamThirdPage::OnTimer(UINT nIDEvent)
// {
// 	if (nIDEvent ==1)
// 	{
// 		AddMsgList(theApp.m_MsgDisplay);
// 	}
// 	
// 
//  	CPropertyPage::OnTimer(nIDEvent);
// }


	
