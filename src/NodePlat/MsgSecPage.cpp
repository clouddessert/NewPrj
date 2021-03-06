// MsgSecPage.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "MsgSecPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////
extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMsgSecPage property page

IMPLEMENT_DYNCREATE(CMsgSecPage, CPropertyPage)

CMsgSecPage::CMsgSecPage() : CPropertyPage(CMsgSecPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgSecPage)
	//}}AFX_DATA_INIT
}

CMsgSecPage::~CMsgSecPage()
{
}

void CMsgSecPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgSecPage)
	DDX_Control(pDX, IDC_LIST_COMMUNICATE, m_click_comm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgSecPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgSecPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_COMM_MSG, OnCommMessage)
 	ON_NOTIFY(NM_RCLICK, IDC_LIST_COMMUNICATE, OnRclickListCommunicate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgSecPage message handlers

void CMsgSecPage::OnSize(UINT nType, int cx, int cy) 
{
	this->ShowWindow(SW_MAXIMIZE);
	
	//判断是否存在顶层窗口
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_COMMUNICATE)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}

BOOL CMsgSecPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hCOMM_wmd = GetSafeHwnd();

	CString Communicate_Columns[]=
	{
 
  		    _T("合批号"),//0
			_T("目标批号"),//1
	    	_T("平台编号"),  //0
			_T("设备编号"),
			_T("设备类型"),
			
			_T("平台型号"), //4
			_T("可信度"),   //5
			_T("到达方位"), //6
			
			_T("载频信息"),
			
			_T("信号到达时间"),
			_T("脉冲幅度"),
			
			_T("信号类型"),
			_T("调制样式"),
			
//			_T("平台名称"),
			_T("敌我属性"),
			
	        _T("国家/地区")

	};

	
	((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(Communicate_Columns)/sizeof(Communicate_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->InsertColumn(i, Communicate_Columns[i], LVCFMT_CENTER, 80);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CMsgSecPage::OnCommMessage(WPARAM wParam, LPARAM lParam)  
{
	VCT_COMM_MSG::iterator pComm_Dat;

	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;
 	unsigned long lTmp;

	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetRedraw(FALSE);//关闭重绘
		
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->DeleteAllItems();
		
		//显示数据
		for (pComm_Dat = theApp.m_Comm.begin(); pComm_Dat != theApp.m_Comm.end(); pComm_Dat++,++nTmp)
        {
			strTmp.Format("%s", _T("Comm"));
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->InsertItem(nTmp, strTmp, 9);
			
		    lTmp = pComm_Dat->lAutonum;
			strTmp.Format("%d",(int)lTmp);//合批号
		//	strTmp.Format("%d",pComm_Dat->lAutonum);//合批号
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 0, strTmp);

			fTmp = pComm_Dat->lTargetNumber;//目标批号
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 1, strTmp);
			
			strTmp.Format("%s",pComm_Dat->cPlatNumber);//平台编号
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 2, strTmp);
			
			strTmp.Format("%s",pComm_Dat->cEquipmentNumber); //设备编号
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 3, strTmp);
			
			strTmp.Format("%s",pComm_Dat->cEquipmentType); //设备类型
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 4, strTmp);
			
			strTmp.Format("%s",pComm_Dat->sPlatType); //平台类型
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 5, strTmp);
			
			fTmp = pComm_Dat->dConfidence;  //置信度
			strTmp.Format("%.2f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 6, strTmp);

			fTmp = pComm_Dat->dReachAzimuth;//方位
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 7, strTmp);

			fTmp = pComm_Dat->dComZaiPin;  //载频
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 8, strTmp);
			
			fTmp = pComm_Dat->lSignalReachTime;//信号到达时间
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 9, strTmp);
			
			fTmp = pComm_Dat->dPulseExtent;  //脉冲幅度
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 10, strTmp);
			
			strTmp.Format("%s",pComm_Dat->cSignalType); //信号类型
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 11, strTmp);
			
			strTmp.Format("%s",pComm_Dat->cModulationStyle); //调制样式
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 12, strTmp);
			
			strTmp.Format("%s",pComm_Dat->cDWAttribute); //敌我属性
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 13, strTmp);
			
			strTmp.Format("%s",pComm_Dat->cCountry); //国家/地区
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 14, strTmp);

		}
		((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetRedraw();//启动
	}
	else
	{
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->DeleteAllItems();
	}
	
	return 0;  
} 

void CMsgSecPage::OnRclickListCommunicate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
//#if 0
	bool num[5] = {TRUE,TRUE,TRUE,TRUE,TRUE};

	DWORD dwPos = GetMessagePos();
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) ); 
	/*获得行列号*/
	m_click_comm.ScreenToClient(&point);
	
	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;
	int nItem = m_click_comm.SubItemHitTest(&lvinfo);
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
