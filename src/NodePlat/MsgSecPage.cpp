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
	
	//�ж��Ƿ���ڶ��㴰��
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
// 		_T("ƽ̨���"),
// 		_T("�豸���"),
// 		_T("�豸����"),
// 		_T("Ŀ������"),
// 		
// 		_T("��Ƶ��Ϣ"),
// 		_T("���﷽λ"),
// 		_T("�źŵ���ʱ��"),
// 		_T("�������"),
// 		
// 		_T("�ź�����"),
// 		_T("������ʽ"),
// 		_T("ƽ̨����"),
// 		_T("ƽ̨����"),
// 		_T("��������"),
// 		_T("���Ŷ�"),
// 		_T("����")

	    	_T("ƽ̨���"),  //0
			_T("�豸���"),
			_T("�豸����"),
			
			_T("Ŀ������"),
			_T("ƽ̨����"), //4
			_T("���Ŷ�"),   //5
			_T("���﷽λ"), //6
			
			_T("��Ƶ��Ϣ"),
			
			_T("�źŵ���ʱ��"),
			_T("�������"),
			
			_T("�ź�����"),
			_T("������ʽ"),
			
//			_T("ƽ̨����"),
			_T("��������"),
			
	        _T("����/����")

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
		((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetRedraw(FALSE);//�ر��ػ�
		
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->DeleteAllItems();
		
		//��ʾ����
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
	// 			strTmp = _T("��");
	// 		}
	// 		else
	// 		{
	// 			strTmp = _T("��");
	// 		}
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 3, strTmp);
		
			strTmp.Format("%s",pComm_Dat->cPlatNumber);//ƽ̨���
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 0, strTmp);
			
			strTmp.Format("%s",pComm_Dat->cEquipmentNumber); //�豸���
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 1, strTmp);
			
			strTmp.Format("%s",pComm_Dat->cEquipmentType); //�豸����
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 2, strTmp);
			
			fTmp = pComm_Dat->lTargetNumber;//Ŀ������
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 3, strTmp);
			
			
//			fTmp = pComm_Dat->sPlatType;  //������  //ƽ̨����
//			strTmp.Format("%d",(int)fTmp);
			strTmp.Format("%s",pComm_Dat->sPlatType);
			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 4, strTmp);
			
			fTmp = pComm_Dat->dConfidence;  //���Ŷ�
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
		((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetRedraw();//����
	}
	else
	{
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->DeleteAllItems();
	}
	
	return 0;  
} 
