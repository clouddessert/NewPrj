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
	DDX_Control(pDX, IDC_LIST_MulESM, m_fusEsm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgSixthPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgSixthPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_MULESM_MSG, OnFusEsmMessage) 
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

		    _T("合批号"),//0

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
		//	_T("信号到达时间"),
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

LRESULT CMsgSixthPage::OnFusEsmMessage(WPARAM wParam, LPARAM lParam)
{
	//VCT_ESM_MSG::reverse_iterator pFusESM_Dat;
	VCT_ESM_MSG::iterator pFusESM_Dat;

	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;

	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetRedraw(FALSE);//关闭重绘
		
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->DeleteAllItems();
		
		//显示数据
	    for (pFusESM_Dat = theApp.m_MulESM.begin(); pFusESM_Dat != theApp.m_MulESM.end(); pFusESM_Dat++,++nTmp)
		//for (pFusESM_Dat = theApp.m_MulESM.rbegin(); pFusESM_Dat != theApp.m_MulESM.rend(); ++pFusESM_Dat,++nTmp)
		{
					strTmp.Format("%s", _T("ESM"));
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->InsertItem(nTmp, strTmp, 9);
					
					strTmp.Format("%d",pFusESM_Dat->lAutonum);//合批号
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 0, strTmp);
					
					fTmp = pFusESM_Dat->lTargetNumber;//目标批号
					strTmp.Format("%d",(int)fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 1, strTmp);
					
					strTmp.Format("%s",pFusESM_Dat->cPlatNumber);//平台编号
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 2, strTmp);
					
					strTmp.Format("%s",pFusESM_Dat->cEquipmentNumber); //设备编号
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 3, strTmp);
					
					strTmp.Format("%s",pFusESM_Dat->cEquipmentType); //设备类型
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 4, strTmp);
					
					strTmp.Format("%s",pFusESM_Dat->sPlatType);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 5, strTmp);
					
					fTmp = pFusESM_Dat->dConfidence;  //置信度
					strTmp.Format("%.2f",fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 6, strTmp);
					
					fTmp = pFusESM_Dat->dReachAzimuth;
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 7, strTmp);
					
					fTmp = pFusESM_Dat->dZaiPin; //载频
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 8, strTmp);
					
					fTmp = pFusESM_Dat->dChongPin; //重频
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 9, strTmp);
					
					fTmp = pFusESM_Dat->dMaiKuan; //脉宽
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 10, strTmp);
					
					// fTmp = pFusESM_Dat->lSignalReachTime;//信号到达时间
					// strTmp.Format("%d",(int)fTmp);
					// 	((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 11, strTmp);
					
					fTmp = pFusESM_Dat->dPulseExtent;//脉冲幅度
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 11, strTmp);
					
					fTmp = pFusESM_Dat->dElevationAngle;//仰角
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 12, strTmp);
					
					fTmp = pFusESM_Dat->dTianXianScan; //天线扫描周期
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 13, strTmp);
					
					fTmp = pFusESM_Dat->dMaiChongFeature;//脉冲特征
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 14, strTmp);
					
					strTmp.Format("%s",pFusESM_Dat->cRadarPurpose);//雷达用途
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 15, strTmp);
					
					strTmp.Format("%s",pFusESM_Dat->cRadarName);//雷达名称
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 16, strTmp);
					
					fTmp = pFusESM_Dat->dThreatLevel; //威胁等级
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 17, strTmp);
					
					fTmp = pFusESM_Dat->dERPower; //有效辐射功率
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 18, strTmp);
					
					strTmp.Format("%s",pFusESM_Dat->cDWAttribute);//敌我属性
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 19, strTmp);
					
					strTmp.Format("%s",pFusESM_Dat->cCountry);//国家/地区
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 20, strTmp);
						
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetRedraw();//启动

	}
	else
	{
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->DeleteAllItems();
	}
	 // m_fusEsm.EnsureVisible(m_fusEsm.GetItemCount()-1,FALSE); //始终显示当前最新信息
	return 0;  
} 
