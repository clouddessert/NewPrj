// MsgNinthPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgNinthPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgNinthPage property page
extern CNodePlatApp theApp;
IMPLEMENT_DYNCREATE(CMsgNinthPage, CPropertyPage)

CMsgNinthPage::CMsgNinthPage() : CPropertyPage(CMsgNinthPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgNinthPage)
	//}}AFX_DATA_INIT
}

CMsgNinthPage::~CMsgNinthPage()
{
}

void CMsgNinthPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgNinthPage)
	DDX_Control(pDX, IDC_LIST_EVENT, m_EventList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgNinthPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgNinthPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_EVENT_MSG, OnSigleOutMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgNinthPage message handlers

BOOL CMsgNinthPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hEvent_wnd = GetSafeHwnd();
	
	CString Communicate_Columns[]=
	{
		
  		    _T("���"),//0
				_T("ʱ��"),//1
				_T("��������"),  //0
				_T("����"),
				_T("��λ"),
				
				_T("����"), //4
				_T("�߶�"),   //5
				_T("�ٶ�"), //6
				
				_T("���ٶ�"),
				
				_T("����"),
				_T("�����¼�"),
				
				_T("�ۺ���в��"),
				_T("Ŀ������"),
				
				//			_T("ƽ̨����"),
				_T("ESM����"),
				
				_T("COM����")
				
	};
	
	
	((CListCtrl*)GetDlgItem(IDC_LIST_EVENT))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(Communicate_Columns)/sizeof(Communicate_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_EVENT))->InsertColumn(i, Communicate_Columns[i], LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMsgNinthPage::OnSize(UINT nType, int cx, int cy) 
{
	//CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	this->ShowWindow(SW_MAXIMIZE);
	
	//�ж��Ƿ���ڶ��㴰��
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_EVENT)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}
//����Ҫ��
LRESULT CMsgNinthPage::OnSigleOutMessage(WPARAM wParam, LPARAM lParam)
{
	//����ʹ��iterator��ʾ
	MAP_EVENT_BLACK::iterator pFusESM_Dat;
	// 	VCT_ESM_MSG::iterator iteEsm;
	// 	VCT_COMM_MSG::iterator iteComm;
	
	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;
	
	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_EVENT))->SetRedraw(FALSE);//�ر��ػ�
		
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_EVENT))->DeleteAllItems();
		
		//��ʾ����
		for (pFusESM_Dat = theApp.m_mapEventBlack.begin(); pFusESM_Dat != theApp.m_mapEventBlack.end(); pFusESM_Dat++)
		{



			strTmp.Format("%d",pFusESM_Dat->second.nSeriaN);//���
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 0, strTmp);
			
			strTmp.Format("%d",pFusESM_Dat->second.lTimeStamp);//ʱ��
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 1, strTmp);
			
			fTmp = pFusESM_Dat->second.nTrackHao;//��������
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 2, strTmp);
			

			
			fTmp = pFusESM_Dat->second.dRd;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 3, strTmp);
			
			fTmp = pFusESM_Dat->second.dEz;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 4, strTmp);
			
			fTmp = pFusESM_Dat->second.dAz;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 5, strTmp);
			
			fTmp = pFusESM_Dat->second.dHigh;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 6, strTmp);
			
			fTmp = pFusESM_Dat->second.dSpeed;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 7, strTmp);
			
			fTmp = pFusESM_Dat->second.dAddSpeed;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 8, strTmp);
			
			fTmp = pFusESM_Dat->second.dAzimuth;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 9, strTmp);


			fTmp = pFusESM_Dat->second.nTrackEvent;//
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 10, strTmp);

			fTmp = pFusESM_Dat->second.dThreatDegree;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 11, strTmp);

			fTmp = pFusESM_Dat->second.nTrackType;//
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 12, strTmp);
			
			fTmp = pFusESM_Dat->second.nESMCount;//
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 13, strTmp);
			
			fTmp = pFusESM_Dat->second.nCOMCount;//
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 14, strTmp);
				
			
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_EVENT))->SetRedraw();//����
	}
	else
	{
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_EVENT))->DeleteAllItems();
	}
     return 0;	
}
