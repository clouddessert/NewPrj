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
        ON_MESSAGE(WM_MULTRACE_MSG, OnFusTraceMessage)
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
	    	_T("合批号"),//0
			_T("目标批号"),  //1		
			_T("平台编号"),//2
			_T("设备编号"),//3
			_T("设备类型"),//4	
			_T("平台类型"), //5
			_T("可信度"),  //6
			_T("方位"),  //7	
			_T("平台名称"), //8
//			_T("经度"),     //9
//			_T("纬度"),     //10		
			_T("距离"),  //9		
			_T("仰角"),//10
			_T("绝对航向"),//11
//		    _T("信号到达时间"),
			_T("目标方位角角速度"),//12
			_T("目标仰角角速度"),//13
// 			_T("目标空间坐标X"),
// 			_T("目标空间坐标Y"),
// 			_T("目标空间坐标Z"),
			_T("目标绝对速度X"),//14
			_T("目标绝对速度Y"),//15
			_T("目标绝对速度z"), //16		

	};
	
	((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(Trace_Columns)/sizeof(Trace_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->InsertColumn(i, Trace_Columns[i], LVCFMT_CENTER, 80);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
LRESULT CMsgEighthPage:: OnFusTraceMessage(WPARAM wParam, LPARAM lParam)
{
	//VCT_Cooperative_FUSIDENTIINFOR::iterator pCoFusIdentify_Dat;
	VCT_TRACE_MSG::iterator pFusTrace_Dat;
	
	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;
	
	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetRedraw(FALSE);//关闭重绘
		
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->DeleteAllItems();
		
		//显示数据
		for (pFusTrace_Dat = theApp.m_MulTrace.begin(); pFusTrace_Dat != theApp.m_MulTrace.end(); pFusTrace_Dat++,++nTmp)
		{

		    	strTmp.Format("%s", _T("Trace"));
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->InsertItem(nTmp, strTmp, 9);
				
				strTmp.Format("%d",pFusTrace_Dat->lAutonum); //合批号
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 0, strTmp);
				
				fTmp = pFusTrace_Dat->lTargetNumber;//目标批号
				strTmp.Format("%d",(int)fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 1, strTmp);
				
				strTmp.Format("%s",pFusTrace_Dat->cPlatNumber); //平台编号
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 2, strTmp);
				
				strTmp.Format("%s",pFusTrace_Dat->cEquipmentNumber); //设备编号
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 3, strTmp);
				
				strTmp.Format("%s",pFusTrace_Dat->cEquipmentType); //设备类型
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 4, strTmp);
				
				strTmp.Format("%s",pFusTrace_Dat->sPlatType);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 5, strTmp);
				
				fTmp = pFusTrace_Dat->dConfidence;  //置信度
				strTmp.Format("%.2f",fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 6, strTmp);			
				
				fTmp = pFusTrace_Dat->dAzimuth;
				strTmp.Format("%.4f", fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 7, strTmp);
				
				strTmp.Format("%s",pFusTrace_Dat->cPlatName);  //平台名称
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 8, strTmp);
				
				// 				fTmp = pCoFusIdentify_Dat->stFusTrack.dLonti; //经度
				// 				strTmp.Format("%.4f",fTmp);
				// 				((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 9, strTmp);
				// 				
				// 				fTmp = pCoFusIdentify_Dat->stFusTrack.dLati; //纬度
				// 				strTmp.Format("%.4f",fTmp);
				// 				((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 10, strTmp);
				
				fTmp = pFusTrace_Dat->dRange; //距离
				strTmp.Format("%.2f",fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 9, strTmp);	
				
				fTmp = pFusTrace_Dat->dElevationAngle;  //仰角
				strTmp.Format("%.2f",fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 10, strTmp);	
				
				fTmp = pFusTrace_Dat->dCourse;  //绝对航向
				strTmp.Format("%.2f",fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 11, strTmp);	
				
				fTmp = pFusTrace_Dat->dTargetAZSpeed;  //目标方位角角速度
				strTmp.Format("%.2f",fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 12, strTmp);	
				
				fTmp = pFusTrace_Dat->dTargetEAngleSpeed;  //目标仰角角速度
				strTmp.Format("%.2f",fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 13, strTmp);			
				
				fTmp = pFusTrace_Dat->dTSpeedX;  //目标绝对速度X
				strTmp.Format("%.2f",fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 14, strTmp);			
				
				fTmp = pFusTrace_Dat->dTSpeedY;  //目标绝对速度Y
				strTmp.Format("%.2f",fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 15, strTmp);			
				
				fTmp = pFusTrace_Dat->dTSpeedZ;  //目标绝对速度z
				strTmp.Format("%.2f",fTmp);
			    ((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 16, strTmp);

		}
    	((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetRedraw();//启动
	}
	else
	{
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->DeleteAllItems();
	}
	
	return 0;  
} 



