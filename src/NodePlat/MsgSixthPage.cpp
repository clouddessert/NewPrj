// MsgSixthPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgSixthPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//////////////////////////////
extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMsgSixthPage property page

IMPLEMENT_DYNCREATE(CMsgSixthPage, CPropertyPage)

CMsgSixthPage::CMsgSixthPage() : CPropertyPage(CMsgSixthPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgSixthPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgSixthPage::~CMsgSixthPage()
{
}

void CMsgSixthPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgSixthPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgSixthPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgSixthPage)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgSixthPage message handlers

void CMsgSixthPage::OnSize(UINT nType, int cx, int cy) 
{
	this->ShowWindow(SW_MAXIMIZE);
	
	//判断是否存在顶层窗口
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_MulESM)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
	
}

BOOL CMsgSixthPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hMulESM_wmd = GetSafeHwnd();
	
	CString ESM_Columns[]=
	{
		// 		_T("平台编号"),
		// 		_T("设备编号"),
		// 		_T("设备类型"),
		_T("合批号"),//0
			// 		
			// 		_T("载频信息"),
			// 		_T("重频信息"),
			// 		_T("脉宽信息"),
			// 		_T("信号到达时间"),
			// 		_T("脉冲幅度"),
			// 		_T("到达方位"),
			// 		_T("仰角"),
			// 		_T("天线扫描信息"),
			// 		_T("脉冲特征信息结构"),
			// 		
			// 		_T("雷达用途"),
			// 		_T("雷达名称"),
			// 		_T("威胁等级"),
			// 		_T("有效辐射功率"),
			// 		_T("平台类型"),
			// 		_T("平台型号"),
			// 		_T("平台名称"),
			// 		_T("敌我属性"),
			// 		_T("可信度"),
			// 		_T("国家"),	
			_T("目标批号"),//1
			
			_T("平台编号"),//2
			_T("设备编号"),//3
			_T("设备类型"),//4
			
			
			_T("平台类型"),  //5
			_T("可信度"),   //6
			_T("到达方位"), //7
			
			_T("载频信息"),
			_T("重频信息"),
			_T("脉宽信息"),
			_T("信号到达时间"),
			_T("脉冲幅度"),
			
			_T("仰角"),
			_T("天线扫描信息"),
			_T("脉冲特征信息结构"),
			
			_T("雷达用途"),
			_T("雷达名称"),
			_T("威胁等级"),
			_T("有效辐射功率"),
			_T("敌我属性"),		
			_T("国家/地区"),		
			
	};
	
	
	((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(ESM_Columns)/sizeof(ESM_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->InsertColumn(i, ESM_Columns[i], LVCFMT_CENTER, 80);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

