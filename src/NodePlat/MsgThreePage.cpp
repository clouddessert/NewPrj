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
	//}}AFX_DATA_INIT
}

CMsgThreePage::~CMsgThreePage()
{
}

void CMsgThreePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgThreePage)
	DDX_Control(pDX, IDC_LIST_TRACE, m_click_trace);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgThreePage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgThreePage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_TRACE_MSG, OnTraceMessage)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_TRACE, OnRclickListTrace)
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
		for (pTrace_Dat = theApp.m_Trace.begin(); pTrace_Dat != theApp.m_Trace.end(); pTrace_Dat++,++nTmp)
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
			
			strTmp.Format("%d",pTrace_Dat->lAutonum); //合批号
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 0, strTmp);

			fTmp = pTrace_Dat->lTargetNumber;//目标批号
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 1, strTmp);

			strTmp.Format("%s",pTrace_Dat->cPlatNumber); //平台编号
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 2, strTmp);
			
			strTmp.Format("%s",pTrace_Dat->cEquipmentNumber); //设备编号
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 3, strTmp);
			
			strTmp.Format("%s",pTrace_Dat->cEquipmentType); //设备类型
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 4, strTmp);
			
			
//			fTmp = pTrace_Dat->sPlatType;  //短整型  //平台类型
//			strTmp.Format("%d",(int)fTmp);
			strTmp.Format("%s",pTrace_Dat->sPlatType);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 5, strTmp);
			
			fTmp = pTrace_Dat->dConfidence;  //置信度
			strTmp.Format("%.2f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 6, strTmp);


			fTmp = pTrace_Dat->dAzimuth;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 7, strTmp);


			strTmp.Format("%s",pTrace_Dat->cPlatName);  //平台名称
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 8, strTmp);
			
			fTmp = pTrace_Dat->dLonti; //经度
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 9, strTmp);
			
			fTmp = pTrace_Dat->dLati; //纬度
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 10, strTmp);
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
void CMsgThreePage::OnRclickListTrace(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
//#if 0
	bool num[5] = {TRUE,TRUE,TRUE,TRUE,TRUE};

	DWORD dwPos = GetMessagePos();
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) ); 
	/*获得行列号*/
	m_click_trace.ScreenToClient(&point);
	
	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;
	int nItem = m_click_trace.SubItemHitTest(&lvinfo);
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
	VERIFY(menu.LoadMenu(IDR_SENDREQUEST));    //IDR_SENDQUEST是新建菜单ID
	if (!num[0]) menu.EnableMenuItem(IDM_MATEA, MF_GRAYED);//如果为本舰，则子菜单变灰
	if (!num[1]) menu.EnableMenuItem(IDM_MATEB, MF_GRAYED);
	if (!num[2]) menu.EnableMenuItem(IDM_MATEC, MF_GRAYED);
	if (!num[3]) menu.EnableMenuItem(IDM_MATED, MF_GRAYED);
	if (!num[4]) menu.EnableMenuItem(IDM_MATEE, MF_GRAYED);
	CMenu* popup = menu.GetSubMenu(0);        //取得被指定菜单激活的下拉式菜单或子菜单的句柄
	CPoint oPoint;//定义一个用于确定光标位置的位置  
    GetCursorPos(&oPoint);//获取当前光标的位置，以便使得菜单可以跟随光标
	popup->TrackPopupMenu(TPM_LEFTALIGN, oPoint.x,oPoint.y,this );//TPM_RIGHTBUTTON使右键点击菜单也起作用, 在指定位置显示弹出菜单，并跟踪菜单项的选择
//#endif	
	*pResult = 0;
}
