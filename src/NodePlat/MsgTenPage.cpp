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
	
	//�ж��Ƿ���ڶ��㴰��
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
		
		_T("���"),//0
			
		_T("ʱ��"),//1
		
		_T("ƽ̨����"),//2
		_T("ƽ̨̬��"),//3
		_T("ESM���"),//4
		
		
		_T("COM���"),  //5
		_T("Ŀ������"),   //6
		_T("����"),
		_T("��λ"),
		
		_T("����"), //4
		_T("�߶�"),   //5
		_T("�ٶ�"), //6
		
		_T("���ٶ�"),
		
		_T("����"),
		
		_T("ƽ̨��в��"),
					
			
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
		((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetRedraw(FALSE);//�ر��ػ�
		
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->DeleteAllItems();
		
		//��ʾ����
	    for (pFusESM_Dat = theApp.m_Plat_Black.begin(); pFusESM_Dat != theApp.m_Plat_Black.end(); pFusESM_Dat++,++nTmp)
		{	
			strTmp.Format("%d",pFusESM_Dat->second.nSerialnum);//���
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 0, strTmp);

			strTmp.Format("%d",pFusESM_Dat->second.lTimeStamp);//ʱ��
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 1, strTmp);
			
			fTmp = pFusESM_Dat->second.nPlatHao;//ƽ̨����
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 2, strTmp);

			fTmp = pFusESM_Dat->second.nPlatBasicSituation;//ƽ̨̬��
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 3, strTmp);

			fTmp = pFusESM_Dat->second.nESMHao;//ESM��
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 4, strTmp);

			fTmp = pFusESM_Dat->second.nCOMHao;//ESM��
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetItemText(nTmp, 5, strTmp);

			fTmp = pFusESM_Dat->second.nTrackOBjType;//ESM��
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
// 					strTmp.Format("%d",pFusESM_Dat->lTimeStamp);//ʱ��
// 					((CListCtrl*)GetDlgItem(IDC_LIST_FUN))->SetItemText(nTmp, 0, strTmp);
// 					
// 					fTmp = pFusESM_Dat->nInteGroupSeriNum;//�໥����Ⱥ���
// 					strTmp.Format("%d",(int)fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_FUN))->SetItemText(nTmp, 1, strTmp);
// 
// 					fTmp = pFusESM_Dat->nInteractGroupSGN;//����Ⱥ����
// 					strTmp.Format("%d",(int)fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_FUN))->SetItemText(nTmp, 2, strTmp);
// 
// 					fTmp = pFusESM_Dat->dSumThreatDegree;  //��в��
// 					strTmp.Format("%.2f",fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_FUN))->SetItemText(nTmp, 3, strTmp);
					
// 					strTmp.Format("%s",pFusESM_Dat->cPlatNumber);//ƽ̨���
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 2, strTmp);
// 					
// 					strTmp.Format("%s",pFusESM_Dat->cEquipmentNumber); //�豸���
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 3, strTmp);
// 					
// 					strTmp.Format("%s",pFusESM_Dat->cEquipmentType); //�豸����
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 4, strTmp);
// 					
// 					strTmp.Format("%s",pFusESM_Dat->sPlatType);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 5, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dConfidence;  //���Ŷ�
// 					strTmp.Format("%.2f",fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 6, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dReachAzimuth;
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 7, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dZaiPin; //��Ƶ
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 8, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dChongPin; //��Ƶ
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 9, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dMaiKuan; //����
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 10, strTmp);
// 					
// 					// fTmp = pFusESM_Dat->lSignalReachTime;//�źŵ���ʱ��
// 					// strTmp.Format("%d",(int)fTmp);
// 					// 	((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 11, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dPulseExtent;//�������
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 11, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dElevationAngle;//����
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 12, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dTianXianScan; //����ɨ������
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 13, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dMaiChongFeature;//��������
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 14, strTmp);
// 					
// 					strTmp.Format("%s",pFusESM_Dat->cRadarPurpose);//�״���;
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 15, strTmp);
// 					
// 					strTmp.Format("%s",pFusESM_Dat->cRadarName);//�״�����
// 					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 16, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dThreatLevel; //��в�ȼ�
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 17, strTmp);
// 					
// 					fTmp = pFusESM_Dat->dERPower; //��Ч���书��
// 					strTmp.Format("%.4f", fTmp);
// 					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 18, strTmp);
// 					
// 					strTmp.Format("%s",pFusESM_Dat->cDWAttribute);//��������
// 					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 19, strTmp);
// 					
// 					strTmp.Format("%s",pFusESM_Dat->cCountry);//����/����
// 					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 20, strTmp);
// 						
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->SetRedraw();//����

	}
	else
	{
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_PLAT))->DeleteAllItems();
	}
	return 0;
}