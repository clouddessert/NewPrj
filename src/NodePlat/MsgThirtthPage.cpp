// MsgThirtthPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgThirtthPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgThirtthPage property page
extern CNodePlatApp theApp;
IMPLEMENT_DYNCREATE(CMsgThirtthPage, CPropertyPage)

CMsgThirtthPage::CMsgThirtthPage() : CPropertyPage(CMsgThirtthPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgThirtthPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgThirtthPage::~CMsgThirtthPage()
{
}

void CMsgThirtthPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgThirtthPage)
	DDX_Control(pDX, IDC_LIST_INTER, m_InterList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgThirtthPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgThirtthPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_INTER_MSG, OnSigleOutMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgThirtthPage message handlers

BOOL CMsgThirtthPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hInter_wnd = GetSafeHwnd();
	
	CString CLUSTER_Columns[]=
	{
		_T("ʱ��"),
			_T("�໥����Ⱥ���"),
			_T("����Ⱥ����"),
			_T("�ۺ���в��"),
			
			// 			_T("ƽ̨���"),
			// 			_T("�豸���"),
			// 			_T("�豸����"),
			// 			_T("Ŀ������"),
			// 			_T("�豸����"),
			// 			_T("Ŀ������"),
			
			
			// 			_T("��Ƶ��Ϣ"),
			// 			_T("��Ƶ��Ϣ"),
			// 			_T("������Ϣ"),
			// 			_T("�źŵ���ʱ��"),
			// 			_T("�������"),
			// 			_T("���﷽λ"),
			// 			_T("����"),
			// 			_T("����ɨ����Ϣ"),
			// 			_T("����������Ϣ�ṹ"),
			// 			
			// 			_T("�״���;"),
			// 			_T("�״�����"),
			// 			_T("��в�ȼ�"),
			// 			_T("��Ч���书��"),
			// 			_T("ƽ̨����"),
			// 			_T("ƽ̨�ͺ�"),
			// 			_T("ƽ̨����"),
			// 			_T("��������"),
			// 			_T("���Ŷ�"),
			// 			_T("����/����"),
	};
	
	((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(CLUSTER_Columns)/sizeof(CLUSTER_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->InsertColumn(i, CLUSTER_Columns[i], LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMsgThirtthPage::OnSize(UINT nType, int cx, int cy) 
{
	this->ShowWindow(SW_MAXIMIZE);
	//CPropertyPage::OnSize(nType, cx, cy);
	
	//�ж��Ƿ���ڶ��㴰��
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_INTER)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}


LRESULT CMsgThirtthPage::OnSigleOutMessage(WPARAM wParam, LPARAM lParam)
{
	INTERGROUPBLACK::iterator pFusESM_Dat;

	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;

	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetRedraw(FALSE);//�ر��ػ�
		
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->DeleteAllItems();
		
		//��ʾ����
	    for (pFusESM_Dat = theApp.m_InterGBlack.begin(); pFusESM_Dat != theApp.m_InterGBlack.end(); pFusESM_Dat++,++nTmp)
		{	
					strTmp.Format("%d",pFusESM_Dat->lTimeStamp);//ʱ��
					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 0, strTmp);
					
					fTmp = pFusESM_Dat->nInteGroupSeriNum;//�໥����Ⱥ���
					strTmp.Format("%d",(int)fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 1, strTmp);

					fTmp = pFusESM_Dat->nInteractGroupSGN;//����Ⱥ����
					strTmp.Format("%d",(int)fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 2, strTmp);

					fTmp = pFusESM_Dat->dSumThreatDegree;  //��в��
					strTmp.Format("%.2f",fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_INTER))->SetItemText(nTmp, 3, strTmp);
					
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
		((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetRedraw();//����

	}
	else
	{
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->DeleteAllItems();
	}
	return 0;  
}