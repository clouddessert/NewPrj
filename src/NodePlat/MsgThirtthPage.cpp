// MsgThirtthPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgThirtthPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgThirtthPage property page
extern CNodePlatApp theApp;
IMPLEMENT_DYNCREATE(CMsgThirtthPage, CPropertyPage)

CMsgThirtthPage::CMsgThirtthPage() : CPropertyPage(CMsgThirtthPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgThirtthPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgThirtthPage::~CMsgThirtthPage()
{
}

void CMsgThirtthPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgThirtthPage)
	DDX_Control(pDX, IDC_LIST_INTER, m_InterList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgThirtthPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgThirtthPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_INTER_MSG, OnSigleOutMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgThirtthPage message handlers

BOOL CMsgThirtthPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hInter_wnd = GetSafeHwnd();
	
	CString CLUSTER_Columns[]=
	{
		_T("时戳"),
			_T("相互作用群编号"),
			_T("功能群数量"),
			_T("综合威胁度"),
			
			// 			_T("平台编号"),
			// 			_T("设备编号"),
			// 			_T("设备类型"),
			// 			_T("目标批号"),
			// 			_T("设备类型"),
			// 			_T("目标批号"),
			
			
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
	
	((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(CLUSTER_Columns)/sizeof(CLUSTER_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->InsertColumn(i, CLUSTER_Columns[i], LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMsgThirtthPage::OnSize(UINT nType, int cx, int cy) 
{
	this->ShowWindow(SW_MAXIMIZE);
	//CPropertyPage::OnSize(nType, cx, cy);
	
	//判断是否存在顶层窗口
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_INTER)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}


LRESULT CMsgThirtthPage::OnSigleOutMessage(WPARAM wParam, LPARAM lParam)
{
	INTERGROUPBLACK::iterator pFusESM_Dat;

	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;

	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetRedraw(FALSE);//关闭重绘
		
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->DeleteAllItems();
		
		//显示数据
	    for (pFusESM_Dat = theApp.m_InterGBlack.begin(); pFusESM_Dat != theApp.m_InterGBlack.end(); pFusESM_Dat++,++nTmp)
		{	
					strTmp.Format("%d",pFusESM_Dat->lTimeStamp);//时戳
					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 0, strTmp);
					
					fTmp = pFusESM_Dat->nInteGroupSeriNum;//相互作用群编号
					strTmp.Format("%d",(int)fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 1, strTmp);

					fTmp = pFusESM_Dat->nInteractGroupSGN;//功能群数量
					strTmp.Format("%d",(int)fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 2, strTmp);

					fTmp = pFusESM_Dat->dSumThreatDegree;  //威胁度
					strTmp.Format("%.2f",fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 3, strTmp);
					
// 					strTmp.Format("%s",pFusESM_Dat->cPlatNumber);//平台编号
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 2, strTmp);
// 					
// 					strTmp.Format("%s",pFusESM_Dat->cEquipmentNumber); //设备编号
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 3, strTmp);
// 					
// 					strTmp.Format("%s",pFusESM_Dat->cEquipmentType); //设备类型
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 4, strTmp);
// 					
// 					strTmp.Format("%s",pFusESM_Dat->sPlatType);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 5, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dConfidence;  //置信度
// 					strTmp.Format("%.2f",fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 6, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dReachAzimuth;
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 7, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dZaiPin; //载频
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 8, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dChongPin; //重频
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 9, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dMaiKuan; //脉宽
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 10, strTmp);
// 					
// 					// fTmp = pFusESM_Dat->lSignalReachTime;//信号到达时间
// 					// strTmp.Format("%d",(int)fTmp);
// 					// 	((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 11, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dPulseExtent;//脉冲幅度
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 11, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dElevationAngle;//仰角
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 12, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dTianXianScan; //天线扫描周期
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 13, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dMaiChongFeature;//脉冲特征
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 14, strTmp);
// 					
// 					strTmp.Format("%s",pFusESM_Dat->cRadarPurpose);//雷达用途
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 15, strTmp);
// 					
// 					strTmp.Format("%s",pFusESM_Dat->cRadarName);//雷达名称
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 16, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dThreatLevel; //威胁等级
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 17, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dERPower; //有效辐射功率
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 18, strTmp);
// 					
// 					strTmp.Format("%s",pFusESM_Dat->cDWAttribute);//敌我属性
// 					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 19, strTmp);
// 					
// 					strTmp.Format("%s",pFusESM_Dat->cCountry);//国家/地区
// 					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 20, strTmp);
// 						
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetRedraw();//启动

	}
	else
	{
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->DeleteAllItems();
	}
	return 0;  
}