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
	ON_NOTIFY(NM_CLICK, IDC_LIST_ESM, OnClickListEsm)
	ON_COMMAND(IDM_SENDMSG, OnSendmsg)
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
 		_T("合批号"),//0
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
		for (pESM_Dat = theApp.m_ESM/*theApp.m_ESM_Dat*/.begin(); pESM_Dat != theApp.m_ESM/*theApp.m_ESM_Dat*/.end(); pESM_Dat++,++nTmp)
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
			
			strTmp.Format("%d",pESM_Dat->lAutonum);//合批号
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

void CMsgFstPage::OnRclickListEsm(NMHDR* pNMHDR, LRESULT* pResult) 
{
//#if 0
	DWORD dwPos = GetMessagePos();
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
/*右击弹出菜单*/
	CMenu menu;
	VERIFY( menu.LoadMenu(IDR_MENU2) );       //IDR_MENU2是新建菜单ID
	CMenu* popup = menu.GetSubMenu(0);
	//ASSERT( popup != NULL );
	popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		this );//TPM_RIGHTBUTTON使右键点击菜单也起作用 
//#endif


	*pResult = 0;
}

void CMsgFstPage::OnClickListEsm(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	/*获得行列号*/
// 	DWORD dwPos = GetMessagePos();
// 	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
// 	
// 	m_click_esm.ScreenToClient(&point);
// 	
// 	LVHITTESTINFO lvinfo;
// 	lvinfo.pt = point;
// 	lvinfo.flags = LVHT_ABOVE;
// 	
// 	int nItem = m_click_esm.SubItemHitTest(&lvinfo);
// 	if(nItem != -1)
// 	{
// 		CString strtemp;
// 		strtemp.Format("单击的是第%d行第%d列", lvinfo.iItem, lvinfo.iSubItem);
// 		AfxMessageBox(strtemp);
// 	}
	
	*pResult = 0;
}

void CMsgFstPage::OnSendmsg() //响应弹出菜单
{
	// TODO: Add your command handler code here

//#if 0
	//获取需要联合识别的信息，并转化成发送报文的结构
	VCT_UNINUM_MSG::iterator iteYes;
	VCT_UNINOTRACE_MSG::iterator iteNo;	
	VCT_ESM_MSG::iterator iteEsm;
	VCT_COMM_MSG::iterator iteComm;

	long int lnum;//请求的合批号
// 	Request_Cooperative_Msg StRequest;//保存联合识别前此批号的本舰信息
// 	SendRequest_Msg StSendRequest;//发送请求的结构体

	lnum = theApp.m_ESM_Dat.at(theApp.m_iline).lAutonum;//获取请求协同的批号

	theApp.m_StRequest.vctEsm.clear();
	theApp.m_StRequest.vctComm.clear();
 	memset(&(theApp.m_StRequest.stTrace), 0, sizeof(TRACKSTATUS_MARK));
	memset(&theApp.m_StRequest, 0, sizeof(Request_Cooperative_Msg));//清空保存联合识别前信息的结构体

	memset(&theApp.m_StSendRequest, 0, sizeof(SendRequest_Msg));//清空发送请求的结构体

	if (lnum >= 8000)
	{
		for (iteYes = theApp.m_ClusterUniMsg.begin(); iteYes != theApp.m_ClusterUniMsg.end(); iteYes++)
		{
			if (iteYes->lAutonum == lnum)
			{
				/*取出联合识别前此批号的相关信息并存储*/
				theApp.m_StRequest.lAutonum = lnum;//合批号
				theApp.m_StRequest.stTrace = iteYes->structTrace;//请求协同TRACE信息
				if (iteYes->vctEsm.size())//请求协同ESM信息
				{
					for (iteEsm = iteYes->vctEsm.begin(); iteEsm = iteYes->vctEsm.end(); iteEsm++)
					{
						theApp.m_StRequest.vctEsm.push_back(*iteEsm);
					}
				}
				if (iteYes->vctComm.size())//请求协同COMM信息
				{
					for (iteComm = iteYes->vctComm.begin(); iteComm = iteYes->vctComm.end(); iteComm++)
					{
						theApp.m_StRequest.vctComm.push_back(*iteComm);
					}
				}
				////存放本舰经纬高
				//StRequest.stReqShipPosi.dHeight = iteYes->structTrace.d
				//StRequest.stReqShipPosi.dLati = ;
				//StRequest.stReqShipPosi.dLonti = ;
				theApp.m_StRequest.nCorrFlag = 0;//请求信息的结构体是否找到相关联信息的标志初始化为0


				/*请求结构体*/
				//StSendRequest.num ++;//信息单元序号???????????????
				//long int nStampTime;                     //发送请求信息时的当前时间
				theApp.m_StSendRequest.lAutomn = lnum;//合批号
				theApp.m_StSendRequest.stTrace = iteYes->structTrace;//请求协同TRACE信息
				theApp.m_StSendRequest.nRequestEsmN = iteYes->vctEsm.size();
				theApp.m_StSendRequest.nRequestComN = iteYes->vctComm.size();
				for (int i = 0; i <= iteYes->vctEsm.size();i++)//请求协同ESM信息
				{
					theApp.m_StSendRequest.lEsmTargetNumber[i] = iteYes->vctEsm.at(i).lTargetNumber;//目标esm批号
					theApp.m_StSendRequest.dEsmZaiPin[i] = iteYes->vctEsm.at(i).dZaiPin;//载频
					theApp.m_StSendRequest.dEsmMaiKuan[i] = iteYes->vctEsm.at(i).dMaiKuan;////脉宽
					theApp.m_StSendRequest.dEsmTianXianScan[i] = iteYes->vctEsm.at(i).dTianXianScan;//天线扫描信息
				}
				for (i = 0; i <= iteYes->vctComm.size();i++)//请求协同COMM信息
				{
					theApp.m_StSendRequest.lComTargetNumber[i] = iteYes->vctComm.at(i).lTargetNumber;//目标comm批号
					theApp.m_StSendRequest.dComZaiPin[i] = iteYes->vctComm.at(i).dComZaiPin;//载频信息
					theApp.m_StSendRequest.dComPulseExtent[i] = iteYes->vctComm.at(i).dPulseExtent;//脉冲幅度
				}
				//StSendRequest.stReqShipPosi.dHeight = ;//本舰经纬高
				//StSendRequest.stReqShipPosi.dLati = ;
				//StSendRequest.stReqShipPosi.dLonti = ;
				
				theApp.m_StSendRequest.nCorrFlag = 0;//请求信息的结构体是否找到相关联信息的标志初始化为0

				//theApp.m_SendReqMsg_Dat.push_back(theApp.m_StSendRequest);

				break;
			}
		}
	} 

	else
	{
		for (iteNo = theApp.m_ClusterNoTraceMsg.begin(); iteNo != theApp.m_ClusterNoTraceMsg.end(); iteNo++)
		{
			if (iteNo->lAutonum == lnum)
			{
				/*取出联合识别前此批号的相关信息并存储*/
				theApp.m_StRequest.lAutonum = lnum;//合批号
				//memset(&(StRequest.stTrace), 0, sizeof(TRACKSTATUS_MARK);
				if (iteNo->vctEsm.size())//请求协同ESM信息
				{
					for (iteEsm = iteNo->vctEsm.begin(); iteEsm = iteNo->vctEsm.end(); iteEsm++)
					{
						theApp.m_StRequest.vctEsm.push_back(*iteEsm);
					}
				}
				if (iteNo->vctComm.size())//请求协同COMM信息
				{
					for (iteComm = iteNo->vctComm.begin(); iteComm = iteNo->vctComm.end(); iteComm++)
					{
						theApp.m_StRequest.vctComm.push_back(*iteComm);
					}
				}
				//存放本舰经纬高
// 				StRequest.stReqShipPosi.dHeight = ;
// 				StRequest.stReqShipPosi.dLati = ;
// 				StRequest.stReqShipPosi.dLonti = ;
				theApp.m_StRequest.nCorrFlag = 0;//请求信息的结构体是否找到相关联信息的标志初始化为0

				
				/*请求结构体*/				
				//StSendRequest.num ++;//信息单元序号???????????????
				//long int nStampTime;                     //发送请求信息时的当前时间
				theApp.m_StSendRequest.lAutomn = lnum;//合批号
				//memset(&(StRequest.stTrace), 0, sizeof(TRACKSTATUS_MARK);//请求协同TRACE信息
				theApp.m_StSendRequest.nRequestEsmN = iteNo->vctEsm.size();
				theApp.m_StSendRequest.nRequestComN = iteNo->vctComm.size();
				for (int i = 0; i <= iteNo->vctEsm.size();i++)//请求协同ESM信息
				{
					theApp.m_StSendRequest.lEsmTargetNumber[i] = iteNo->vctEsm.at(i).lTargetNumber;//目标esm批号
					theApp.m_StSendRequest.dEsmZaiPin[i] = iteNo->vctEsm.at(i).dZaiPin;//载频
					theApp.m_StSendRequest.dEsmMaiKuan[i] = iteNo->vctEsm.at(i).dMaiKuan;////脉宽
					theApp.m_StSendRequest.dEsmTianXianScan[i] = iteNo->vctEsm.at(i).dTianXianScan;//天线扫描信息
				}
				for (i = 0; i <= iteNo->vctComm.size();i++)//请求协同COMM信息
				{
					theApp.m_StSendRequest.lComTargetNumber[i] = iteNo->vctComm.at(i).lTargetNumber;//目标comm批号
					theApp.m_StSendRequest.dComZaiPin[i] = iteNo->vctComm.at(i).dComZaiPin;//载频信息
					theApp.m_StSendRequest.dComPulseExtent[i] = iteNo->vctComm.at(i).dPulseExtent;//脉冲幅度
				}
				//StSendRequest.stReqShipPosi.dHeight = ;//本舰经纬高
				//StSendRequest.stReqShipPosi.dLati = ;
				//StSendRequest.stReqShipPosi.dLonti = ;
				
				theApp.m_StSendRequest.nCorrFlag = 0;//请求信息的结构体是否找到相关联信息的标志初始化为0
				//theApp.m_SendReqMsg_Dat.push_back(theApp.m_StSendRequest);

				break;
			}
		}
	}

//#endif	
}
