// MsgThreePage.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "MsgThreePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////
extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMsgThreePage property page

IMPLEMENT_DYNCREATE(CMsgThreePage, CPropertyPage)

CMsgThreePage::CMsgThreePage() : CPropertyPage(CMsgThreePage::IDD)
{
	//{{AFX_DATA_INIT(CMsgThreePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgThreePage::~CMsgThreePage()
{
}

void CMsgThreePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgThreePage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgThreePage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgThreePage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_TRACE_MSG, OnTraceMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgThreePage message handlers

BOOL CMsgThreePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hTRACE_wmd = GetSafeHwnd();

	CString Trace_Columns[]=
	{
// 		_T("平台编号"),
// 		_T("设备编号"),
// 		_T("设备类型"),
// 		_T("目标批号"),
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

		_T("平台编号"),
		_T("设备编号"),
		_T("设备类型"),

		_T("目标批号"),  //3
		_T("平台类型"), //4
		_T("可信度"),  //5
		_T("方位"),  //6

		_T("平台名称"), //7
		_T("经度"),     //8
		_T("纬度"),     //9
		
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
		
		
//		_T("平台名称"),  
		
		_T("国家/地区"),
	};
	
	((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(Trace_Columns)/sizeof(Trace_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->InsertColumn(i, Trace_Columns[i], LVCFMT_CENTER, 80);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMsgThreePage::OnSize(UINT nType, int cx, int cy) 
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
		
		GetDlgItem(IDC_LIST_TRACE)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}

LRESULT CMsgThreePage::OnTraceMessage(WPARAM wParam, LPARAM lParam)  
{
	VCT_TRACE_MSG::iterator pTrace_Dat;

	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;

	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetRedraw(FALSE);//关闭重绘
		
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->DeleteAllItems();
		
		//显示数据
		for (pTrace_Dat = theApp.m_Trace_Dat.begin(); pTrace_Dat != theApp.m_Trace_Dat.end(); pTrace_Dat++,++nTmp)
		{
			strTmp.Format("%s", _T("Trace"));
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->InsertItem(nTmp, strTmp, 9);
	// 		
	// 		strTmp.Format("%s", m_pTmpTrackIter->second.strName);
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 1, strTmp);
	// 		
	// 		strTmp.Format("%s", m_pTmpTrackIter->second.strType);
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 2, strTmp);
	// 		
	// 		iTmpProp = m_pTmpTrackIter->second.iTargetProp;
	// 		if (iTmpProp)
	// 		{
	// 			strTmp = _T("我");
	// 		}
	// 		else
	// 		{
	// 			strTmp = _T("敌");
	// 		}
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 3, strTmp);
			
			strTmp.Format("%s",pTrace_Dat->cPlatNumber); //平台编号
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 0, strTmp);
			
			strTmp.Format("%s",pTrace_Dat->cEquipmentNumber); //设备编号
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 1, strTmp);
			
			strTmp.Format("%s",pTrace_Dat->cEquipmentType); //设备类型
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 2, strTmp);

			fTmp = pTrace_Dat->lTargetNumber;//目标批号
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 3, strTmp);
			
			
//			fTmp = pTrace_Dat->sPlatType;  //短整型  //平台类型
//			strTmp.Format("%d",(int)fTmp);
			strTmp.Format("%s",pTrace_Dat->sPlatType);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 4, strTmp);
			
			fTmp = pTrace_Dat->dConfidence;  //置信度
			strTmp.Format("%.2f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 5, strTmp);


			fTmp = pTrace_Dat->dAzimuth;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 6, strTmp);


			strTmp.Format("%s",pTrace_Dat->cPlatName);  //平台名称
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp,7,strTmp);
			
			fTmp = pTrace_Dat->dLonti; //经度
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp,8,strTmp);
			
			fTmp = pTrace_Dat->dLati; //纬度
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp,9,strTmp);
			// 		
	// 		fTmp = m_pTmpTrackIter->second.fLati;
	// 		strTmp.Format("%.4f", fTmp);
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 5, strTmp);
	// 		
	// 		fTmp = m_pTmpTrackIter->second.fHeight;
	// 		strTmp.Format("%.4f", fTmp);
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 6, strTmp);
	// 		
	// 		fTmp = m_pTmpTrackIter->second.fSpeed;
	// 		strTmp.Format("%.4f", fTmp);
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 7, strTmp);
	// 		
	// 		fTmp = m_pTmpTrackIter->second.fAngle;
	// 		strTmp.Format("%.4f", fTmp);
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 8, strTmp);
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetRedraw();//启动
	}
	else
	{
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->DeleteAllItems();
	}
	
	return 0;  
} 