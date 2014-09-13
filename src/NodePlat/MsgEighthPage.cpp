// MsgEighthPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgEighthPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//////////////////////////////
extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMsgEighthPage property page

IMPLEMENT_DYNCREATE(CMsgEighthPage, CPropertyPage)

CMsgEighthPage::CMsgEighthPage() : CPropertyPage(CMsgEighthPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgEighthPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgEighthPage::~CMsgEighthPage()
{
}

void CMsgEighthPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgEighthPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgEighthPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgEighthPage)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgEighthPage message handlers

void CMsgEighthPage::OnSize(UINT nType, int cx, int cy) 
{
	this->ShowWindow(SW_MAXIMIZE);
	
	//判断是否存在顶层窗口
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_MulTRACE)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}

BOOL CMsgEighthPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hMulTRACE_wnd = GetSafeHwnd();
	
	CString Trace_Columns[]=
	{
		// 		_T("平台编号"),
		// 		_T("设备编号"),
		// 		_T("设备类型"),
		_T("合批号"),//0
			// 
			// 		_T("距离"),
			// 		_T("方位"),
			// 		_T("仰角"),
			// 		_T("绝对航向"),
			// 		_T("信号到达时间"),
			// 		_T("目标方位角角速度"),
			// 		_T("目标仰角角速度"),
			// 		_T("目标空间坐标X"),
			// 		_T("目标空间坐标Y"),
			// 		_T("目标空间坐标Z"),
			// 		_T("目标绝对速度X"),
			// 		_T("目标绝对速度Y"),
			// 		_T("目标绝对速度z"),
			// 		
			// 		_T("平台类型"),
			// 		_T("平台名称"),
			// 		_T("可信度"),
			// 		_T("国家/地区"),
			
			_T("目标批号"),  //1
			
			_T("平台编号"),//2
			_T("设备编号"),//3
			_T("设备类型"),//4
			
			
			_T("平台类型"), //5
			_T("可信度"),  //6
			_T("方位"),  //7
			
			_T("平台名称"), //8
			_T("经度"),     //9
			_T("纬度"),     //10
			
			_T("距离"),
			
			_T("仰角"),
			_T("绝对航向"),
			_T("信号到达时间"),
			_T("目标方位角角速度"),
			_T("目标仰角角速度"),
			_T("目标空间坐标X"),
			_T("目标空间坐标Y"),
			_T("目标空间坐标Z"),
			_T("目标绝对速度X"),
			_T("目标绝对速度Y"),
			_T("目标绝对速度z"),
			_T("国家/地区"),
	};
	
	((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(Trace_Columns)/sizeof(Trace_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->InsertColumn(i, Trace_Columns[i], LVCFMT_CENTER, 80);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
