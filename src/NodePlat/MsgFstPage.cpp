// MsgFstPage.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "MsgFstPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////
extern CNodePlatApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMsgFstPage property page

IMPLEMENT_DYNCREATE(CMsgFstPage, CPropertyPage)

CMsgFstPage::CMsgFstPage() : CPropertyPage(CMsgFstPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgFstPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgFstPage::~CMsgFstPage()
{
}

void CMsgFstPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgFstPage)
	DDX_Control(pDX, IDC_LIST_ESM, m_click_esm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgFstPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgFstPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_ESM_MSG, OnEsmMessage) 
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ESM, OnRclickListEsm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgFstPage message handlers

void CMsgFstPage::OnSize(UINT nType, int cx, int cy) 
{
	this->ShowWindow(SW_MAXIMIZE);

	//判断是否存在顶层窗口
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_ESM)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}

BOOL CMsgFstPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hESM_wmd = GetSafeHwnd();

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

	
	((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(ESM_Columns)/sizeof(ESM_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->InsertColumn(i, ESM_Columns[i], LVCFMT_CENTER, 80);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CMsgFstPage::OnEsmMessage(WPARAM wParam, LPARAM lParam)  
{ 
	//VCT_ESM_MSG::reverse_iterator pESM_Dat;
	VCT_ESM_MSG::iterator pESM_Dat;


	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;
    int nesm=1;

	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetRedraw(FALSE);//关闭重绘
		
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->DeleteAllItems();
		
		//显示数据
		for (pESM_Dat = theApp.m_ESM/*theApp.m_ESM_Dat*/.begin(); pESM_Dat != theApp.m_ESM/*theApp.m_ESM_Dat*/.end(); pESM_Dat++,++nTmp)
		//逆序显示
		//for (pESM_Dat = theApp.m_ESM.rbegin(), nesm=1; pESM_Dat != theApp.m_ESM.rend(), nesm<7; ++pESM_Dat,++nTmp,++nesm)
		{

			strTmp.Format("%s", _T("ESM"));
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->InsertItem(nTmp, strTmp, 9);

			fTmp = pESM_Dat->lAutonum;
			strTmp.Format("%d",(int)fTmp);//合批号
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 0, strTmp);

			fTmp = pESM_Dat->lTargetNumber;//目标批号
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 1, strTmp);

			strTmp.Format("%s",pESM_Dat->cPlatNumber);//平台编号
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 2, strTmp);
			
			strTmp.Format("%s",pESM_Dat->cEquipmentNumber); //设备编号
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 3, strTmp);
			
			strTmp.Format("%s",pESM_Dat->cEquipmentType); //设备类型
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 4, strTmp);
			
			strTmp.Format("%s",pESM_Dat->sPlatType);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 5, strTmp);
			
			fTmp = pESM_Dat->dConfidence;  //置信度
			strTmp.Format("%.2f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 6, strTmp);
						
			fTmp = pESM_Dat->dReachAzimuth;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 7, strTmp);
			
			fTmp = pESM_Dat->dZaiPin; //载频
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 8, strTmp);
			
			fTmp = pESM_Dat->dChongPin; //重频
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 9, strTmp);
			
			fTmp = pESM_Dat->dMaiKuan; //脉宽
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 10, strTmp);
			
			fTmp = pESM_Dat->lSignalReachTime;//信号到达时间
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 11, strTmp);
			
			fTmp = pESM_Dat->dPulseExtent;//脉冲幅度
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 12, strTmp);
			
			fTmp = pESM_Dat->dElevationAngle;//仰角
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 13, strTmp);
			
			fTmp = pESM_Dat->dTianXianScan; //天线扫描周期
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 14, strTmp);
			
			fTmp = pESM_Dat->dMaiChongFeature;//脉冲特征
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 15, strTmp);
			
			strTmp.Format("%s",pESM_Dat->cRadarPurpose);//雷达用途
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 16, strTmp);
			
			strTmp.Format("%s",pESM_Dat->cRadarName);//雷达名称
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 17, strTmp);
			
			fTmp = pESM_Dat->dThreatLevel; //威胁等级
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 18, strTmp);
			
			fTmp = pESM_Dat->dERPower; //有效辐射功率
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 19, strTmp);
			
			strTmp.Format("%s",pESM_Dat->cDWAttribute);//敌我属性
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 20, strTmp);
			
			strTmp.Format("%s",pESM_Dat->cCountry);//国家/地区
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 21, strTmp);
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetRedraw();//启动
	}
	else
	{
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->DeleteAllItems();

	}
	//m_click_esm.EnsureVisible(m_click_esm.GetItemCount()-1,FALSE); //始终显示当前最新信息
	
	return 0;  
} 

void CMsgFstPage::OnRclickListEsm(NMHDR* pNMHDR, LRESULT* pResult) 
{
	bool num[5] = {TRUE,TRUE,TRUE,TRUE,TRUE};
//#if 0
	DWORD dwPos = GetMessagePos(); //返回表示屏幕坐标下光标位置的长整数值
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) ); 
/*获得行列号*/
	m_click_esm.ScreenToClient(&point);
	
	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;
	int nItem = m_click_esm.SubItemHitTest(&lvinfo);
	if(nItem != -1)
	{
		//CString strtemp;
		//strtemp.Format("点击的是第%d行第%d列", lvinfo.iItem, lvinfo.iSubItem);
		//AfxMessageBox(strtemp);
		theApp.m_iline = lvinfo.iItem;
	}
/*获取本舰*/
	switch (theApp.m_ThisNumber)
	{
	case 0:
		{
			num[0] = FALSE;
			break;
		}
	case 1:
		{
			num[1] = FALSE;
			break;
		}
	case 2:
		{
			num[2] = FALSE;
			break;
		}
	case 3:
		{
			num[3] = FALSE;
			break;
		}
	case 4:
		{
			num[4] = FALSE;
			break;
		}
	default:
		break;
	}
	
/*右击弹出菜单*/
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_SENDREQUEST));       //IDR_SENDQUEST是新建菜单ID
// 	if (!num[0]) menu.EnableMenuItem(IDM_MATEA, MF_GRAYED);//如果为本舰，则子菜单变灰
// 	if (!num[1]) menu.EnableMenuItem(IDM_MATEB, MF_GRAYED);
// 	if (!num[2]) menu.EnableMenuItem(IDM_MATEC, MF_GRAYED);
// 	if (!num[3]) menu.EnableMenuItem(IDM_MATED, MF_GRAYED);
// 	if (!num[4]) menu.EnableMenuItem(IDM_MATEE, MF_GRAYED);
	if (!num[0]) 
	{
		menu.EnableMenuItem(IDM_SENDA, MF_GRAYED);//如果为本舰，则子菜单变灰
		menu.EnableMenuItem(IDM_CLOSEA, MF_GRAYED);
	}
	if (!num[1]) 
	{
		menu.EnableMenuItem(IDM_SENDB, MF_GRAYED);
		menu.EnableMenuItem(IDM_CLOSEB, MF_GRAYED);
	}
	if (!num[2]) 
	{
		menu.EnableMenuItem(IDM_SENDC, MF_GRAYED);
		menu.EnableMenuItem(IDM_CLOSEC, MF_GRAYED);
	}
	if (!num[3])
	{
		menu.EnableMenuItem(IDM_SENDD, MF_GRAYED);
		menu.EnableMenuItem(IDM_CLOSED, MF_GRAYED);
	}
	if (!num[4]) 
	{
		menu.EnableMenuItem(IDM_SENDE, MF_GRAYED);
		menu.EnableMenuItem(IDM_CLOSEE, MF_GRAYED);
	}
	CMenu* popup = menu.GetSubMenu(0);        //取得被指定菜单激活的下拉式菜单或子菜单的句柄
	CPoint oPoint;//定义一个用于确定光标位置的位置  
    GetCursorPos(&oPoint);//获取当前光标的位置，以便使得菜单可以跟随光标
	popup->TrackPopupMenu(TPM_LEFTALIGN, oPoint.x,oPoint.y,this );//TPM_RIGHTBUTTON使右键点击菜单也起作用, 在指定位置显示弹出菜单，并跟踪菜单项的选择

	
	//#endif


	*pResult = 0;
}



// void CMsgFstPage::OnSendmsg() //响应弹出菜单
// {
// 	// TODO: Add your command handler code here
// 
// 	
// }

