// MsgTenPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgTenPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgTenPage property page
extern CNodePlatApp theApp;
IMPLEMENT_DYNCREATE(CMsgTenPage, CPropertyPage)

CMsgTenPage::CMsgTenPage() : CPropertyPage(CMsgTenPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgTenPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgTenPage::~CMsgTenPage()
{
}

void CMsgTenPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgTenPage)
	DDX_Control(pDX, IDC_LIST_PLAT, m_PlatList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgTenPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgTenPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_PLAT_MSG, OnSigleOutMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgTenPage message handlers

void CMsgTenPage::OnSize(UINT nType, int cx, int cy) 
{
	//CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	this->ShowWindow(SW_MAXIMIZE);
	
	//判断是否存在顶层窗口
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_PLAT)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}

BOOL CMsgTenPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hPlat_wnd = GetSafeHwnd();
	
	CString ESM_Columns[]=
	{
		
		_T("序号"),//0
			
		_T("时戳"),//1
		
		_T("平台批号"),//2
		_T("平台态势"),//3
		_T("ESM编号"),//4
		
		
		_T("COM编号"),  //5
		_T("目标类型"),   //6
		_T("径距"),
		_T("方位"),
		
		_T("仰角"), //4
		_T("高度"),   //5
		_T("速度"), //6
		
		_T("加速度"),
		
		_T("航向"),
		
		_T("平台威胁度"),
					
			
	};
	
	
	((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(ESM_Columns)/sizeof(ESM_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->InsertColumn(i, ESM_Columns[i], LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


LRESULT CMsgTenPage::OnSigleOutMessage(WPARAM wParam, LPARAM lParam)
{
	MAP_PLAT_BLACK::iterator pFusESM_Dat;
	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;

	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetRedraw(FALSE);//关闭重绘
		
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->DeleteAllItems();
		
		//显示数据
	    for (pFusESM_Dat = theApp.m_Plat_Black.begin(); pFusESM_Dat != theApp.m_Plat_Black.end(); pFusESM_Dat++,++nTmp)
		{	
			strTmp.Format("%d",pFusESM_Dat->second.nSerialnum);//序号
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 0, strTmp);

			strTmp.Format("%d",pFusESM_Dat->second.lTimeStamp);//时戳
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 1, strTmp);
			
			fTmp = pFusESM_Dat->second.nPlatHao;//平台批号
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 2, strTmp);

			fTmp = pFusESM_Dat->second.nPlatBasicSituation;//平台态势
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 3, strTmp);

			fTmp = pFusESM_Dat->second.nESMHao;//ESM号
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 4, strTmp);

			fTmp = pFusESM_Dat->second.nCOMHao;//ESM号
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 5, strTmp);

			fTmp = pFusESM_Dat->second.nTrackOBjType;//ESM号
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 6, strTmp);

			fTmp = pFusESM_Dat->second.dRd;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 7, strTmp);

			fTmp = pFusESM_Dat->second.dEz;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 8, strTmp);

			fTmp = pFusESM_Dat->second.dAz;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 9, strTmp);

			fTmp = pFusESM_Dat->second.dHigh;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 10, strTmp);

			fTmp = pFusESM_Dat->second.dSpeed;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 11, strTmp);

			fTmp = pFusESM_Dat->second.dAddSpeed;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 12, strTmp);

			fTmp = pFusESM_Dat->second.dAzimuth;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 13, strTmp);

			fTmp = pFusESM_Dat->second.dThreatDegree;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 14, strTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 7, strTmp);
// 					strTmp.Format("%d",pFusESM_Dat->lTimeStamp);//时戳
// 					((CListCtrl*)GetDlgItem(IDC_LIST_FUN))->SetItemText(nTmp, 0, strTmp);
// 					
// 					fTmp = pFusESM_Dat->nInteGroupSeriNum;//相互作用群编号
// 					strTmp.Format("%d",(int)fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_FUN))->SetItemText(nTmp, 1, strTmp);
// 
// 					fTmp = pFusESM_Dat->nInteractGroupSGN;//功能群数量
// 					strTmp.Format("%d",(int)fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_FUN))->SetItemText(nTmp, 2, strTmp);
// 
// 					fTmp = pFusESM_Dat->dSumThreatDegree;  //威胁度
// 					strTmp.Format("%.2f",fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_FUN))->SetItemText(nTmp, 3, strTmp);
					
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
		((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetRedraw();//启动

	}
	else
	{
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->DeleteAllItems();
	}
	return 0;
}