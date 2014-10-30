// MsgFifthPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgFifthPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////
extern CNodePlatApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMsgFifthPage property page

IMPLEMENT_DYNCREATE(CMsgFifthPage, CPropertyPage)

CMsgFifthPage::CMsgFifthPage() : CPropertyPage(CMsgFifthPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgFifthPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgFifthPage::~CMsgFifthPage()
{
}

void CMsgFifthPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgFifthPage)
	DDX_Control(pDX, IDC_LIST_UNICLUSTERMSG, m_mulidentify);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgFifthPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgFifthPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_MUL_OUT_MSG, OnSigleOutMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgFifthPage message handlers

BOOL CMsgFifthPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	theApp.hMulOut_wnd = GetSafeHwnd();

	CString CLUSTER_Columns[]=
	{
	 	    _T("�ۺ�����"),
			_T("ƽ̨����"),
			_T("���Ŷ�"),
//			_T("Ŀ����"),

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

	((CListCtrl*)GetDlgItem(IDC_LIST_UNICLUSTERMSG))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(CLUSTER_Columns)/sizeof(CLUSTER_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_UNICLUSTERMSG))->InsertColumn(i, CLUSTER_Columns[i], LVCFMT_CENTER, 80);

	return TRUE;  // return TRUE unless you set the focus to a control	        
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CMsgFifthPage::OnSize(UINT nType, int cx, int cy) 
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
		
		GetDlgItem(IDC_LIST_UNICLUSTERMSG)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}



LRESULT CMsgFifthPage::OnSigleOutMessage(WPARAM wParam, LPARAM lParam) 
{
	//����ʹ��iterator��ʾ
	VCT_MIDENTIINFOR_MSG::iterator iterator;
// 	VCT_ESM_MSG::iterator iteEsm;
// 	VCT_COMM_MSG::iterator iteComm;
	
	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;
	
	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_UNICLUSTERMSG))->SetRedraw(FALSE);//�ر��ػ�
		
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_UNICLUSTERMSG))->DeleteAllItems();
		
		//��ʾ����
		for (iterator = theApp.m_MulIdentifyMsg.begin(); iterator != theApp.m_MulIdentifyMsg.end(); iterator++,++nTmp)
	    {
			//strTmp.Format("%s", _T("8000"));
			//((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->InsertItem(nTmp, strTmp, 9);				
			fTmp = iterator->lAutonum;//�ۺ�����
			strTmp.Format("%d", (int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_UNICLUSTERMSG))->InsertItem(nTmp, strTmp, 9);
			
            //fTmp = iterator->sPlatType;  //������  //ƽ̨����
            //strTmp.Format("%d", (int)fTmp);
			strTmp.Format("%s", iterator->sPlatType);
			((CListCtrl*)GetDlgItem(IDC_LIST_UNICLUSTERMSG))->SetItemText(nTmp, 1, strTmp);
			
			fTmp = iterator->dConfidence;  //���Ŷ�
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_UNICLUSTERMSG))->SetItemText(nTmp, 2, strTmp);	
		
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_UNICLUSTERMSG))->SetRedraw();//����
	}
	else
	{
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_UNICLUSTERMSG))->DeleteAllItems();
	}
     return 0;
}


