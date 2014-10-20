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

/////////////////////////////////////////////////////////////////////////////
// CParamThirdPage property page

IMPLEMENT_DYNCREATE(CParamThirdPage, CPropertyPage)

CParamThirdPage::CParamThirdPage() : CPropertyPage(CParamThirdPage::IDD)
{
	//{{AFX_DATA_INIT(CParamThirdPage)
		// NOTE: the ClassWizard will add member initialization here
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParamThirdPage message handlers

BOOL CParamThirdPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	CString str1,str2;
	str1.Format("辐射源消失");
	str2.Format("");
  	AddMsgList(str1,str2);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CParamThirdPage::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	this->ShowWindow(SW_MAXIMIZE);
	
	//判断是否存在顶层窗口
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_MSGDISPLAY)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}


void CParamThirdPage::AddMsgList(CString IP,CString str) //添加信息于LISTBOX 控件中
{
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	CString time;
	time.Format(_T(" %d:%02d"), tm.wHour, tm.wMinute);
	CString strShow;
	strShow = IP+"于"+time+str;
	if (IP=="邻舰")
	{
		
	}else
	{
		
		m_AddMsgList.AddString(strShow);
	}
	
	int numList=m_AddMsgList.GetCount()-1;
	//	GetDlgItem(IDC_BUTTON_CLEAR)->EnableWindow(true);
	m_AddMsgList.SetTopIndex(numList);
	m_AddMsgList.SetCurSel(numList);
	//水平滚动
	int max_width=0;
	CSize sz;
	CClientDC dc(this);
	for(int i=0;i<m_AddMsgList.GetCount();i++)
	{
		m_AddMsgList.GetText(i,str);
		sz=dc.GetTextExtent(str);
		if(max_width<sz.cx)
			max_width=sz.cx;
	}
	m_AddMsgList.SendMessage(LB_SETHORIZONTALEXTENT,max_width,0);
}