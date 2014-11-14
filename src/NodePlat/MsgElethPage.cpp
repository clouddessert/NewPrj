// MsgElethPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgElethPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMsgElethPage property page

IMPLEMENT_DYNCREATE(CMsgElethPage, CPropertyPage)

CMsgElethPage::CMsgElethPage() : CPropertyPage(CMsgElethPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgElethPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgElethPage::~CMsgElethPage()
{
}

void CMsgElethPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgElethPage)
	DDX_Control(pDX, IDC_LIST_SPACE, m_SpaceList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgElethPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgElethPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_SPACE_MSG, OnSigleOutMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgElethPage message handlers

BOOL CMsgElethPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hSpace_wnd = GetSafeHwnd();
	
	CString CLUSTER_Columns[]=
	{
		_T("时戳"),
		_T("飞机空间群数量"),
		_T("时戳"),
		_T("舰船空间群数量"),

// 			_T("平台编号"),
// 			_T("设备编号"),
// 			_T("设备类型"),
// 			_T("目标批号"),
// 			_T("设备类型"),
// 			_T("目标批号"),
// 
// 
// 			_T("载频信息"),
// 			_T("重频信息"),
// 			_T("脉宽信息"),
// 			_T("信号到达时间"),
// 			_T("脉冲幅度"),
// 			_T("到达方位"),
// 			_T("仰角"),
// 			_T("天线扫描信息"),
// 			_T("脉冲特征信息结构"),
// 			
// 			_T("雷达用途"),
// 			_T("雷达名称"),
// 			_T("威胁等级"),
// 			_T("有效辐射功率"),
// 			_T("平台类型"),
// 			_T("平台型号"),
// 			_T("平台名称"),
// 			_T("敌我属性"),
// 			_T("可信度"),
// 			_T("国家/地区"),
	};
	
	((CListCtrl*)GetDlgItem(IDC_LIST_SPACE))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(CLUSTER_Columns)/sizeof(CLUSTER_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_SPACE))->InsertColumn(i, CLUSTER_Columns[i], LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMsgElethPage::OnSize(UINT nType, int cx, int cy) 
{
	//CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	this->ShowWindow(SW_MAXIMIZE);
	//CPropertyPage::OnSize(nType, cx, cy);
	
	//判断是否存在顶层窗口
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_SPACE)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}

LRESULT CMsgElethPage::OnSigleOutMessage(WPARAM wParam, LPARAM lParam)
{
//	VCT_SPACE::iterator pFusESM_Dat;
	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;

	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_SPACE))->SetRedraw(FALSE);//关闭重绘
		
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_SPACE))->DeleteAllItems();
		
		//显示数据
		strTmp.Format("%d",theApp.m_PlaneSpaceBlack.lTimeStamp);//时戳
		((CListCtrl*)GetDlgItem(IDC_LIST_SPACE))->SetItemText(nTmp, 0, strTmp);
		
		fTmp = theApp.m_PlaneSpaceBlack.nPlanTypeN;//功能群数量
		strTmp.Format("%d",(int)fTmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_SPACE))->SetItemText(nTmp, 1, strTmp);
	    
		((CListCtrl*)GetDlgItem(IDC_LIST_SPACE))->SetRedraw();//启动

	}
	else
	{
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_SPACE))->DeleteAllItems();
	}
	return 0;
}
