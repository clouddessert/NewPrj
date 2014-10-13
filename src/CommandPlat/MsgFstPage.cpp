// MsgFstPage.cpp : implementation file
//

#include "stdafx.h"
#include "CommandPlat.h"
#include "MsgFstPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////
extern CCommandPlatApp theApp;

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

	//�ж��Ƿ���ڶ��㴰��
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
		_T("ƽ̨���"),//0
		_T("�豸���"),//1
		_T("�豸����"),//2

		_T("Ŀ������"),  //3
		_T("ƽ̨����"),  //4
		_T("���Ŷ�"),    //5
		_T("���﷽λ"),  //6
	
		_T("ƽ̨����"),  //7

		_T("��Ƶ��Ϣ"),  
		_T("��Ƶ��Ϣ"),  //9 
		_T("������Ϣ"),  //10
		_T("�źŵ���ʱ��"),  //11 
		_T("�������"),   
	
		_T("����"),   
		_T("����ɨ����Ϣ"),  //14
		_T("����������Ϣ�ṹ"),
		
		_T("�״���;"),  //16
		_T("�״�����"),  //17
		_T("��в�ȼ�"),   //18
		_T("��Ч���书��"),//19
		
// 		_T("ƽ̨�ͺ�"),  
// 		_T("ƽ̨����"),
		_T("��������"), //20
	
		_T("����/����"), //21		
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
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetRedraw(FALSE);//�ر��ػ�
		
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->DeleteAllItems();
		
		//��ʾ����
		for (pESM_Dat = theApp.m_ESM_Dat.begin(); pESM_Dat != theApp.m_ESM_Dat.end(); pESM_Dat++,++nTmp)
		{
			strTmp.Format("%s", _T("ESM"));
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->InsertItem(nTmp, strTmp, 9); 
	
	// 		strTmp.Format("%s", m_pTmpTrackIter->second.strName);
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 1, strTmp);
	// 		
	// 		strTmp.Format("%s", m_pTmpTrackIter->second.strType);
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 2, strTmp);
	// 		
	// 		iTmpProp = m_pTmpTrackIter->second.iTargetProp;
	// 		if (iTmpProp)
	// 		{
	// 			strTmp = _T("��");
	// 		}
	// 		else
	// 		{
	// 			strTmp = _T("��");
	// 		}
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 3, strTmp);

			strTmp.Format("%s",pESM_Dat->cPlatNumber);//ƽ̨���
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 0, strTmp);

			strTmp.Format("%s",pESM_Dat->cEquipmentNumber); //�豸���
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 1, strTmp);

			strTmp.Format("%s",pESM_Dat->cEquipmentType); //�豸����
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 2, strTmp);

			fTmp = pESM_Dat->lTargetNumber;////Ŀ������
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 3, strTmp);

//			fTmp = pESM_Dat->sPlatType;  //������  //ƽ̨����
//			strTmp.Format("%d",(int)fTmp);
            strTmp.Format("%s",pESM_Dat->sPlatType);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 4, strTmp);

			fTmp = pESM_Dat->dConfidence;  //���Ŷ�
			strTmp.Format("%.2f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 5, strTmp);
			
			fTmp = pESM_Dat->dReachAzimuth;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 6, strTmp);

			strTmp.Format("%s",pESM_Dat->cPlatName); //ƽ̨����
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 7, strTmp);

			fTmp = pESM_Dat->dZaiPin; //��Ƶ
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 8, strTmp);

			fTmp = pESM_Dat->dChongPin; //��Ƶ
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 9, strTmp);

			fTmp = pESM_Dat->dMaiKuan; //����
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 10, strTmp);

			fTmp = pESM_Dat->lSignalReachTime;//�źŵ���ʱ��
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 11, strTmp);

			fTmp = pESM_Dat->dPulseExtent;//�������
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 12, strTmp);

			fTmp = pESM_Dat->dElevationAngle;//����
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 13, strTmp);

			fTmp = pESM_Dat->dTianXianScan; //����ɨ������
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 14, strTmp);

			fTmp = pESM_Dat->dMaiChongFeature;//��������
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 15, strTmp);

			strTmp.Format("%s",pESM_Dat->cRadarPurpose);//�״���;
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 16, strTmp);

			strTmp.Format("%s",pESM_Dat->cRadarName);//�״�����
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 17, strTmp);

			fTmp = pESM_Dat->dThreatLevel; //��в�ȼ�
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 18, strTmp);

			fTmp = pESM_Dat->dERPower; //��Ч���书��
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 19, strTmp);
			
			strTmp.Format("%s",pESM_Dat->cDWAttribute);//��������
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 20, strTmp);
		
			strTmp.Format("%s",pESM_Dat->cCountry);//����/����
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 21, strTmp);

		}
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetRedraw();//����
	}
	else
	{
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->DeleteAllItems();
	}
	
	return 0;  
} 
