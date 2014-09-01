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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgSecPage::~CMsgSecPage()
{
}

void CMsgSecPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgSecPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgSecPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgSecPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_COMM_MSG, OnCommMessage)
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
// 		_T("平台编号"),
// 		_T("设备编号"),
// 		_T("设备类型"),
// 		_T("目标批号"),
// 		
// 		_T("载频信息"),
// 		_T("到达方位"),
// 		_T("信号到达时间"),
// 		_T("脉冲幅度"),
// 		
// 		_T("信号类型"),
// 		_T("调制样式"),
// 		_T("平台类型"),
// 		_T("平台名称"),
// 		_T("敌我属性"),
// 		_T("可信度"),
// 		_T("国家")

	    	_T("平台编号"),  //0
			_T("设备编号"),
			_T("设备类型"),
			
			_T("目标批号"),
			_T("平台类型"), //4
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

	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetRedraw(FALSE);//关闭重绘
		
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->DeleteAllItems();
		
		//显示数据
		for (pComm_Dat = theApp.m_Comm_Dat.begin(); pComm_Dat != theApp.m_Comm_Dat.end(); pComm_Dat++,++nTmp)
		{
			strTmp.Format("%s", _T("Comm"));
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->InsertItem(nTmp, strTmp, 9);
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
		
			strTmp.Format("%s",pComm_Dat->cPlatNumber);//平台编号
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 0, strTmp);
			
			strTmp.Format("%s",pComm_Dat->cEquipmentNumber); //设备编号
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 1, strTmp);
			
			strTmp.Format("%s",pComm_Dat->cEquipmentType); //设备类型
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 2, strTmp);
			
			fTmp = pComm_Dat->lTargetNumber;//目标批号
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 3, strTmp);
			
			
//			fTmp = pComm_Dat->sPlatType;  //短整型  //平台类型
//			strTmp.Format("%d",(int)fTmp);
			strTmp.Format("%s",pComm_Dat->sPlatType);
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 4, strTmp);
			
			fTmp = pComm_Dat->dConfidence;  //置信度
			strTmp.Format("%.2f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 5, strTmp);


			fTmp = pComm_Dat->dReachAzimuth;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 6, strTmp);
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
		((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetRedraw();//启动
	}
	else
	{
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->DeleteAllItems();
	}
	
	return 0;  
} 
