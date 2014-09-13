// MsgSeventhPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgSeventhPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////
extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMsgSeventhPage property page

IMPLEMENT_DYNCREATE(CMsgSeventhPage, CPropertyPage)

CMsgSeventhPage::CMsgSeventhPage() : CPropertyPage(CMsgSeventhPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgSeventhPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgSeventhPage::~CMsgSeventhPage()
{
}

void CMsgSeventhPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgSeventhPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgSeventhPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgSeventhPage)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgSeventhPage message handlers

void CMsgSeventhPage::OnSize(UINT nType, int cx, int cy) 
{
	this->ShowWindow(SW_MAXIMIZE);
	
	//判断是否存在顶层窗口
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_MulCOMM)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
	
}

BOOL CMsgSeventhPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	theApp.hMulCOMM_wnd = GetSafeHwnd();
	
	CString Communicate_Columns[]=
	{
		// 		_T("平台编号"),
		// 		_T("设备编号"),
		// 		_T("设备类型"),
		_T("合批号"),//0
			// 		
			// 		_T("载频信息"),
			// 		_T("到达方位"),
			// 		_T("信号到达时间"),
			// 		_T("脉冲幅度"),
			// 		
			// 		_T("信号类型"),
			// 		_T("调制样式"),
			// 		_T("平台类型"),
			// 		_T("平台名称"),
			// 		_T("敌我属性"),
			// 		_T("可信度"),
			// 		_T("国家")
           	_T("目标批号"),//1
			_T("平台编号"),  //0
			_T("设备编号"),
			_T("设备类型"),
			
			
			_T("平台类型"), //4
			_T("可信度"),   //5
			_T("到达方位"), //6
			
			_T("载频信息"),
			
			_T("信号到达时间"),
			_T("脉冲幅度"),
			
			_T("信号类型"),
			_T("调制样式"),
			
			//			_T("平台名称"),
			_T("敌我属性"),
			
			_T("国家/地区")
			
	};
	
	
	((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(Communicate_Columns)/sizeof(Communicate_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->InsertColumn(i, Communicate_Columns[i], LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
