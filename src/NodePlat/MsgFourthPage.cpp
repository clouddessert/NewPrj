// MsgFourthPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgFourthPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////
extern CNodePlatApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMsgFourthPage property page

IMPLEMENT_DYNCREATE(CMsgFourthPage, CPropertyPage)

CMsgFourthPage::CMsgFourthPage() : CPropertyPage(CMsgFourthPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgFourthPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgFourthPage::~CMsgFourthPage()
{
}

void CMsgFourthPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgFourthPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgFourthPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgFourthPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_SIG_OUT_MSG, OnSigleOutMessage) 
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgFourthPage message handlers


BOOL CMsgFourthPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	theApp.hSigOut_wnd = GetSafeHwnd();

	CString IDENTIFY_Columns[]=
	{
	 	    _T("综合批号"),
			_T("平台类型"),
			_T("可信度"),

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

	((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(IDENTIFY_Columns)/sizeof(IDENTIFY_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->InsertColumn(i, IDENTIFY_Columns[i], LVCFMT_CENTER, 80);

	return TRUE;  // return TRUE unless you set the focus to a control	        
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CMsgFourthPage::OnSize(UINT nType, int cx, int cy) 
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
		
		GetDlgItem(IDC_LIST_FUSIONMSG)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}


//这个函数根据输出的结构体来更新!!!!!!!!!!!!!!!!!
LRESULT CMsgFourthPage::OnSigleOutMessage(WPARAM wParam, LPARAM lParam) 
{
	//这里使用pOutPt去显示


	VCT_ESM_MSG::iterator pOutPt;
	
	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;
	
	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->SetRedraw(FALSE);//关闭重绘
		
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->DeleteAllItems();
		
		//显示数据
		for (pOutPt = theApp.m_ESM_Dat.begin(); pOutPt != theApp.m_ESM_Dat.end(); pOutPt++,++nTmp)
		{
			strTmp.Format("%s", _T("ESM"));
			((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->InsertItem(nTmp, strTmp, 9);
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
			
			fTmp = pOutPt->lTargetNumber;//目标批号
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->SetItemText(nTmp, 3, strTmp);
			
			
			fTmp = pOutPt->sPlatType;  //短整型  //平台类型
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->SetItemText(nTmp, 4, strTmp);
			
			fTmp = pOutPt->dConfidence;  //置信度
			strTmp.Format("%.2f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->SetItemText(nTmp, 5, strTmp);
			
			
             // 	fTmp = pESM_Dat->fReachAzimuth;
             // 	strTmp.Format("%.4f", fTmp);
             // 	((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->SetItemText(nTmp, 6, strTmp);
			
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
		((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->SetRedraw();//启动
	}
	else
	{
		//清除显示列表
		((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->DeleteAllItems();
	}


	return 0;
}
