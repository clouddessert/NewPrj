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
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgFstPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgFstPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_ESM_MSG, OnEsmMessage) 
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
// 		_T("平台编号"),
// 		_T("设备编号"),
// 		_T("设备类型"),
// 		_T("目标批号"),
// 		
// 		_T("载频信息"),
// 		_T("重频信息"),
// 		_T("脉宽信息"),
// 		_T("信号到达时间"),
// 		_T("脉冲幅度"),
// 		_T("到达方位"),
// 		_T("仰角"),
// 		_T("天线扫描信息"),
// 		_T("脉冲特征信息结构"),
// 		
// 		_T("雷达用途"),
// 		_T("雷达名称"),
// 		_T("威胁等级"),
// 		_T("有效辐射功率"),
// 		_T("平台类型"),
// 		_T("平台型号"),
// 		_T("平台名称"),
// 		_T("敌我属性"),
// 		_T("可信度"),
// 		_T("国家"),	
		    _T("平台编号"),//0
			_T("设备编号"),//1
			_T("设备类型"),//2
			
			_T("目标批号"),//3
			_T("平台类型"),  //4
			_T("可信度"),   //5
			_T("到达方位"), //6
			
			_T("载频信息"),//6
			_T("重频信息"),
			_T("脉宽信息"),
			_T("信号到达时间"),//7
			_T("脉冲幅度"),
			
			_T("仰角"),
			_T("天线扫描信息"),
			_T("脉冲特征信息结构"),
			
			_T("雷达用途"),
			_T("雷达名称"),
			_T("威胁等级"),
			_T("有效辐射功率"),
			
//			_T("平台型号"),  
//			_T("平台名称"),
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
	VCT_ESM_MSG::iterator pESM_Dat;

	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;

	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetRedraw(FALSE);//关闭重绘
		
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->DeleteAllItems();
		
		//显示数据
		for (pESM_Dat = theApp.m_ESM_Dat.begin(); pESM_Dat != theApp.m_ESM_Dat.end(); pESM_Dat++,++nTmp)
		{
			strTmp.Format("%s", _T("ESM"));
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->InsertItem(nTmp, strTmp, 9);
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
			
			strTmp.Format("%s",pESM_Dat->cPlatNumber);//平台编号
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 0, strTmp);
			
			strTmp.Format("%s",pESM_Dat->cEquipmentNumber); //设备编号
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 1, strTmp);
			
			strTmp.Format("%s",pESM_Dat->cEquipmentType); //设备类型
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 2, strTmp);


			fTmp = pESM_Dat->lTargetNumber;//目标批号
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 3, strTmp);
			
			
			fTmp = pESM_Dat->sPlatType;  //短整型  //平台类型
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 4, strTmp);
			
			fTmp = pESM_Dat->dConfidence;  //置信度
			strTmp.Format("%.2f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 5, strTmp);
			
			
			fTmp = pESM_Dat->fReachAzimuth;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 6, strTmp);
			
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
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetRedraw();//启动
	}
	else
	{
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->DeleteAllItems();
	}
	
	return 0;  
} 
