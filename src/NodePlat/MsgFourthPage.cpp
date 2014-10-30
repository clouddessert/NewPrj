// MsgFourthPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgFourthPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////
extern CNodePlatApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMsgFourthPage property page

IMPLEMENT_DYNCREATE(CMsgFourthPage, CPropertyPage)

CMsgFourthPage::CMsgFourthPage() : CPropertyPage(CMsgFourthPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgFourthPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgFourthPage::~CMsgFourthPage()
{
}

void CMsgFourthPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgFourthPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgFourthPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgFourthPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_SIG_OUT_MSG, OnSigleOutMessage) 
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgFourthPage message handlers


BOOL CMsgFourthPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	theApp.hSigOut_wnd = GetSafeHwnd();

	CString IDENTIFY_Columns[]=
	{
	 	    _T("�ۺ�����"),
			_T("ƽ̨����"),
			_T("���Ŷ�"),

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

	((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(IDENTIFY_Columns)/sizeof(IDENTIFY_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->InsertColumn(i, IDENTIFY_Columns[i], LVCFMT_CENTER, 80);

	return TRUE;  // return TRUE unless you set the focus to a control	        
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CMsgFourthPage::OnSize(UINT nType, int cx, int cy) 
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
		
		GetDlgItem(IDC_LIST_FUSIONMSG)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}


//���������������Ľṹ��������!!!!!!!!!!!!!!!!!
LRESULT CMsgFourthPage::OnSigleOutMessage(WPARAM wParam, LPARAM lParam) 
{
	//����ʹ��iteratorȥ��ʾ
	//VCT_IDENTIINFOR_MSG::reverse_iterator iterator;
	VCT_IDENTIINFOR_MSG::iterator iterator;
	
	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;
	
	
	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->SetRedraw(FALSE);//�ر��ػ�
		
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->DeleteAllItems();
		
		//��ʾ����
        //int m = theApp.m_IdentifyMsg.size();
		
        for (iterator = theApp.m_IdentifyMsg.begin(); iterator != theApp.m_IdentifyMsg.end(); iterator++,++nTmp)
	 	//������ʾ
		//for (iterator = theApp.m_IdentifyMsg.rbegin(); iterator != theApp.m_IdentifyMsg.rend(); ++iterator,++nTmp)
		{
			//strTmp.Format("%s", _T("8000"));
			//((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->InsertItem(nTmp, strTmp, 9);				
			fTmp = iterator->lAutonum;//�ۺ�����
			strTmp.Format("%d", (int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_FIRSTIDENTMSG))->InsertItem(nTmp, strTmp, 9);
			
            //fTmp = iterator->sPlatType;  //������  //ƽ̨����
            //strTmp.Format("%d", (int)fTmp);
			strTmp.Format("%s", iterator->sPlatType);
			((CListCtrl*)GetDlgItem(IDC_LIST_FIRSTIDENTMSG))->SetItemText(nTmp, 1, strTmp);
			
			fTmp = iterator->dConfidence;  //���Ŷ�
			strTmp.Format("%.2f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_FIRSTIDENTMSG))->SetItemText(nTmp, 2, strTmp);	
			
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->SetRedraw();//����
	}
	else
	{
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_FUSIONMSG))->DeleteAllItems();
	}



	return 0;
}
