// MsgEighthPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgEighthPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//////////////////////////////
extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMsgEighthPage property page

IMPLEMENT_DYNCREATE(CMsgEighthPage, CPropertyPage)

CMsgEighthPage::CMsgEighthPage() : CPropertyPage(CMsgEighthPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgEighthPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgEighthPage::~CMsgEighthPage()
{
}

void CMsgEighthPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgEighthPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgEighthPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgEighthPage)
	ON_WM_SIZE()
        ON_MESSAGE(WM_MULTRACE_MSG, OnFusTraceMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgEighthPage message handlers

void CMsgEighthPage::OnSize(UINT nType, int cx, int cy) 
{
	this->ShowWindow(SW_MAXIMIZE);
	
	//�ж��Ƿ���ڶ��㴰��
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_MulTRACE)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}

BOOL CMsgEighthPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hMulTRACE_wnd = GetSafeHwnd();
	
	CString Trace_Columns[]=
	{
	    	_T("������"),//0
			_T("Ŀ������"),  //1		
			_T("ƽ̨���"),//2
			_T("�豸���"),//3
			_T("�豸����"),//4	
			_T("ƽ̨����"), //5
			_T("���Ŷ�"),  //6
			_T("��λ"),  //7	
			_T("ƽ̨����"), //8
//			_T("����"),     //9
//			_T("γ��"),     //10		
			_T("����"),  //9		
			_T("����"),//10
			_T("���Ժ���"),//11
//		    _T("�źŵ���ʱ��"),
			_T("Ŀ�귽λ�ǽ��ٶ�"),//12
			_T("Ŀ�����ǽ��ٶ�"),//13
// 			_T("Ŀ��ռ�����X"),
// 			_T("Ŀ��ռ�����Y"),
// 			_T("Ŀ��ռ�����Z"),
			_T("Ŀ������ٶ�X"),//14
			_T("Ŀ������ٶ�Y"),//15
			_T("Ŀ������ٶ�z"), //16		

	};
	
	((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(Trace_Columns)/sizeof(Trace_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->InsertColumn(i, Trace_Columns[i], LVCFMT_CENTER, 80);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
LRESULT CMsgEighthPage:: OnFusTraceMessage(WPARAM wParam, LPARAM lParam)
{
	//VCT_Cooperative_FUSIDENTIINFOR::iterator pCoFusIdentify_Dat;
	VCT_TRACE_MSG::iterator pFusTrace_Dat;
	
	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;
	
	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetRedraw(FALSE);//�ر��ػ�
		
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->DeleteAllItems();
		
		//��ʾ����
		for (pFusTrace_Dat = theApp.m_MulTrace.begin(); pFusTrace_Dat != theApp.m_MulTrace.end(); pFusTrace_Dat++,++nTmp)
		{

		    	strTmp.Format("%s", _T("Trace"));
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->InsertItem(nTmp, strTmp, 9);
				
				strTmp.Format("%d",pFusTrace_Dat->lAutonum); //������
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 0, strTmp);
				
				fTmp = pFusTrace_Dat->lTargetNumber;//Ŀ������
				strTmp.Format("%d",(int)fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 1, strTmp);
				
				strTmp.Format("%s",pFusTrace_Dat->cPlatNumber); //ƽ̨���
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 2, strTmp);
				
				strTmp.Format("%s",pFusTrace_Dat->cEquipmentNumber); //�豸���
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 3, strTmp);
				
				strTmp.Format("%s",pFusTrace_Dat->cEquipmentType); //�豸����
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 4, strTmp);
				
				strTmp.Format("%s",pFusTrace_Dat->sPlatType);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 5, strTmp);
				
				fTmp = pFusTrace_Dat->dConfidence;  //���Ŷ�
				strTmp.Format("%.2f",fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 6, strTmp);			
				
				fTmp = pFusTrace_Dat->dAzimuth;
				strTmp.Format("%.4f", fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 7, strTmp);
				
				strTmp.Format("%s",pFusTrace_Dat->cPlatName);  //ƽ̨����
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 8, strTmp);
				
				// 				fTmp = pCoFusIdentify_Dat->stFusTrack.dLonti; //����
				// 				strTmp.Format("%.4f",fTmp);
				// 				((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 9, strTmp);
				// 				
				// 				fTmp = pCoFusIdentify_Dat->stFusTrack.dLati; //γ��
				// 				strTmp.Format("%.4f",fTmp);
				// 				((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 10, strTmp);
				
				fTmp = pFusTrace_Dat->dRange; //����
				strTmp.Format("%.2f",fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 9, strTmp);	
				
				fTmp = pFusTrace_Dat->dElevationAngle;  //����
				strTmp.Format("%.2f",fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 10, strTmp);	
				
				fTmp = pFusTrace_Dat->dCourse;  //���Ժ���
				strTmp.Format("%.2f",fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 11, strTmp);	
				
				fTmp = pFusTrace_Dat->dTargetAZSpeed;  //Ŀ�귽λ�ǽ��ٶ�
				strTmp.Format("%.2f",fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 12, strTmp);	
				
				fTmp = pFusTrace_Dat->dTargetEAngleSpeed;  //Ŀ�����ǽ��ٶ�
				strTmp.Format("%.2f",fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 13, strTmp);			
				
				fTmp = pFusTrace_Dat->dTSpeedX;  //Ŀ������ٶ�X
				strTmp.Format("%.2f",fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 14, strTmp);			
				
				fTmp = pFusTrace_Dat->dTSpeedY;  //Ŀ������ٶ�Y
				strTmp.Format("%.2f",fTmp);
				((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 15, strTmp);			
				
				fTmp = pFusTrace_Dat->dTSpeedZ;  //Ŀ������ٶ�z
				strTmp.Format("%.2f",fTmp);
			    ((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetItemText(nTmp, 16, strTmp);

		}
    	((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetRedraw();//����
	}
	else
	{
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->DeleteAllItems();
	}
	
	return 0;  
} 



