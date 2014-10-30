// MsgSixthPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgSixthPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//////////////////////////////
extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMsgSixthPage property page

IMPLEMENT_DYNCREATE(CMsgSixthPage, CPropertyPage)

CMsgSixthPage::CMsgSixthPage() : CPropertyPage(CMsgSixthPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgSixthPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgSixthPage::~CMsgSixthPage()
{
}

void CMsgSixthPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgSixthPage)
	DDX_Control(pDX, IDC_LIST_MulESM, m_fusEsm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgSixthPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgSixthPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_MULESM_MSG, OnFusEsmMessage) 
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgSixthPage message handlers

void CMsgSixthPage::OnSize(UINT nType, int cx, int cy) 
{
	this->ShowWindow(SW_MAXIMIZE);
	
	//�ж��Ƿ���ڶ��㴰��
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_MulESM)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
	
}

BOOL CMsgSixthPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hMulESM_wmd = GetSafeHwnd();
	
	CString ESM_Columns[]=
	{

		    _T("������"),//0

			_T("Ŀ������"),//1
			
			_T("ƽ̨���"),//2
			_T("�豸���"),//3
			_T("�豸����"),//4
			
			
			_T("ƽ̨����"),  //5
			_T("���Ŷ�"),   //6
			_T("���﷽λ"), //7
			
			_T("��Ƶ��Ϣ"),
			_T("��Ƶ��Ϣ"),
			_T("������Ϣ"),
		//	_T("�źŵ���ʱ��"),
			_T("�������"),
			
			_T("����"),
			_T("����ɨ����Ϣ"),
			_T("����������Ϣ�ṹ"),
			
			_T("�״���;"),
			_T("�״�����"),
			_T("��в�ȼ�"),
			_T("��Ч���书��"),
			_T("��������"),		
			_T("����/����"),		
			
	};
	
	
	((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(ESM_Columns)/sizeof(ESM_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->InsertColumn(i, ESM_Columns[i], LVCFMT_CENTER, 80);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CMsgSixthPage::OnFusEsmMessage(WPARAM wParam, LPARAM lParam)
{
	//VCT_ESM_MSG::reverse_iterator pFusESM_Dat;
	VCT_ESM_MSG::iterator pFusESM_Dat;

	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;

	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetRedraw(FALSE);//�ر��ػ�
		
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->DeleteAllItems();
		
		//��ʾ����
	    for (pFusESM_Dat = theApp.m_MulESM.begin(); pFusESM_Dat != theApp.m_MulESM.end(); pFusESM_Dat++,++nTmp)
		//for (pFusESM_Dat = theApp.m_MulESM.rbegin(); pFusESM_Dat != theApp.m_MulESM.rend(); ++pFusESM_Dat,++nTmp)
		{
					strTmp.Format("%s", _T("ESM"));
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->InsertItem(nTmp, strTmp, 9);
					
					strTmp.Format("%d",pFusESM_Dat->lAutonum);//������
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 0, strTmp);
					
					fTmp = pFusESM_Dat->lTargetNumber;//Ŀ������
					strTmp.Format("%d",(int)fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 1, strTmp);
					
					strTmp.Format("%s",pFusESM_Dat->cPlatNumber);//ƽ̨���
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 2, strTmp);
					
					strTmp.Format("%s",pFusESM_Dat->cEquipmentNumber); //�豸���
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 3, strTmp);
					
					strTmp.Format("%s",pFusESM_Dat->cEquipmentType); //�豸����
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 4, strTmp);
					
					strTmp.Format("%s",pFusESM_Dat->sPlatType);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 5, strTmp);
					
					fTmp = pFusESM_Dat->dConfidence;  //���Ŷ�
					strTmp.Format("%.2f",fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 6, strTmp);
					
					fTmp = pFusESM_Dat->dReachAzimuth;
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 7, strTmp);
					
					fTmp = pFusESM_Dat->dZaiPin; //��Ƶ
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 8, strTmp);
					
					fTmp = pFusESM_Dat->dChongPin; //��Ƶ
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 9, strTmp);
					
					fTmp = pFusESM_Dat->dMaiKuan; //����
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 10, strTmp);
					
					// fTmp = pFusESM_Dat->lSignalReachTime;//�źŵ���ʱ��
					// strTmp.Format("%d",(int)fTmp);
					// 	((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 11, strTmp);
					
					fTmp = pFusESM_Dat->dPulseExtent;//�������
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 11, strTmp);
					
					fTmp = pFusESM_Dat->dElevationAngle;//����
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 12, strTmp);
					
					fTmp = pFusESM_Dat->dTianXianScan; //����ɨ������
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 13, strTmp);
					
					fTmp = pFusESM_Dat->dMaiChongFeature;//��������
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 14, strTmp);
					
					strTmp.Format("%s",pFusESM_Dat->cRadarPurpose);//�״���;
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 15, strTmp);
					
					strTmp.Format("%s",pFusESM_Dat->cRadarName);//�״�����
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 16, strTmp);
					
					fTmp = pFusESM_Dat->dThreatLevel; //��в�ȼ�
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 17, strTmp);
					
					fTmp = pFusESM_Dat->dERPower; //��Ч���书��
					strTmp.Format("%.4f", fTmp);
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 18, strTmp);
					
					strTmp.Format("%s",pFusESM_Dat->cDWAttribute);//��������
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 19, strTmp);
					
					strTmp.Format("%s",pFusESM_Dat->cCountry);//����/����
					((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetItemText(nTmp, 20, strTmp);
						
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->SetRedraw();//����

	}
	else
	{
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_MulESM))->DeleteAllItems();
	}
	 // m_fusEsm.EnsureVisible(m_fusEsm.GetItemCount()-1,FALSE); //ʼ����ʾ��ǰ������Ϣ
	return 0;  
} 
