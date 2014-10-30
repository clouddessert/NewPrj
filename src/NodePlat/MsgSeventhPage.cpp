// MsgSeventhPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgSeventhPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////
extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMsgSeventhPage property page

IMPLEMENT_DYNCREATE(CMsgSeventhPage, CPropertyPage)

CMsgSeventhPage::CMsgSeventhPage() : CPropertyPage(CMsgSeventhPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgSeventhPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgSeventhPage::~CMsgSeventhPage()
{
}

void CMsgSeventhPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgSeventhPage)
	DDX_Control(pDX, IDC_LIST_MulCOMM, m_fusCom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgSeventhPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgSeventhPage)
	ON_WM_SIZE()
    ON_MESSAGE(WM_MULCOMM_MSG, OnFusCommMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgSeventhPage message handlers

void CMsgSeventhPage::OnSize(UINT nType, int cx, int cy) 
{
	this->ShowWindow(SW_MAXIMIZE);
	
	//�ж��Ƿ���ڶ��㴰��
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_MulCOMM)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
	
}

BOOL CMsgSeventhPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	theApp.hMulCOMM_wnd = GetSafeHwnd();
	
	CString Communicate_Columns[]=
	{
	    	_T("������"),//0
           	_T("Ŀ������"),//1
			_T("ƽ̨���"),  //0
			_T("�豸���"),
			_T("�豸����"),
			
			
			_T("ƽ̨����"), //4
			_T("���Ŷ�"),   //5
			_T("���﷽λ"), //6
			
			_T("��Ƶ��Ϣ"),
			
//			_T("�źŵ���ʱ��"),
			_T("�������"),
			
			_T("�ź�����"),
			_T("������ʽ"),
			
			//			_T("ƽ̨����"),
			_T("��������"),
			
			_T("����/����")
			
	};
	
	
	((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(Communicate_Columns)/sizeof(Communicate_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->InsertColumn(i, Communicate_Columns[i], LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CMsgSeventhPage::OnFusCommMessage(WPARAM wParam, LPARAM lParam)  
{
	//VCT_COMM_MSG::reverse_iterator pFusComm_Dat;
	VCT_COMM_MSG::iterator pFusComm_Dat;
	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;
	
	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetRedraw(FALSE);//�ر��ػ�
		
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->DeleteAllItems();
		
		//��ʾ����
		for (pFusComm_Dat = theApp.m_MulComm.begin(); pFusComm_Dat != theApp.m_MulComm.end(); pFusComm_Dat++,++nTmp)
		//������ʾ	
		//for (pFusComm_Dat = theApp.m_MulComm.rbegin(); pFusComm_Dat != theApp.m_MulComm.rend(); pFusComm_Dat++,++nTmp)
		{					
			strTmp.Format("%s", _T("Comm"));
			((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->InsertItem(nTmp, strTmp, 9);
			
			strTmp.Format("%d",pFusComm_Dat->lAutonum);//������
			((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetItemText(nTmp, 0, strTmp);
			
			fTmp = pFusComm_Dat->lTargetNumber;//Ŀ������
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetItemText(nTmp, 1, strTmp);
			
			strTmp.Format("%s",pFusComm_Dat->cPlatNumber);//ƽ̨���
			((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetItemText(nTmp, 2, strTmp);
			
			strTmp.Format("%s",pFusComm_Dat->cEquipmentNumber); //�豸���
			((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetItemText(nTmp, 3, strTmp);
			
			strTmp.Format("%s",pFusComm_Dat->cEquipmentType); //�豸����
			((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetItemText(nTmp, 4, strTmp);
			
			strTmp.Format("%s",pFusComm_Dat->sPlatType); //ƽ̨����
			((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetItemText(nTmp, 5, strTmp);
			
			fTmp = pFusComm_Dat->dConfidence;  //���Ŷ�
			strTmp.Format("%.2f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetItemText(nTmp, 6, strTmp);
			
			fTmp = pFusComm_Dat->dReachAzimuth;//��λ
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetItemText(nTmp, 7, strTmp);
			
			fTmp = pFusComm_Dat->dComZaiPin;  //��Ƶ
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetItemText(nTmp, 8, strTmp);
			
			// 			fTmp = pFusComm_Dat->lSignalReachTime;//�źŵ���ʱ��
			// 			strTmp.Format("%d",(int)fTmp);
			// 			((CListCtrl*)GetDlgItem(IDC_LIST_COMMUNICATE))->SetItemText(nTmp, 9, strTmp);
			
			fTmp = pFusComm_Dat->dPulseExtent;  //�������
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetItemText(nTmp, 9, strTmp);
			
			strTmp.Format("%s",pFusComm_Dat->cSignalType); //�ź�����
			((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetItemText(nTmp, 10, strTmp);
			
			strTmp.Format("%s",pFusComm_Dat->cModulationStyle); //������ʽ
			((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetItemText(nTmp, 11, strTmp);
			
			strTmp.Format("%s",pFusComm_Dat->cDWAttribute); //��������
			((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetItemText(nTmp, 12, strTmp);
			
			strTmp.Format("%s",pFusComm_Dat->cCountry); //����/����
			((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetItemText(nTmp, 13, strTmp);
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetRedraw();//����
	}
	else
	{
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->DeleteAllItems();
	}
	//m_fusCom.EnsureVisible(m_fusCom.GetItemCount()-1,FALSE); //ʼ����ʾ��ǰ������Ϣ 
	return 0;  
} 
