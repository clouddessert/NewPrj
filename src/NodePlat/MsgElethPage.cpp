// MsgElethPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgElethPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMsgElethPage property page

IMPLEMENT_DYNCREATE(CMsgElethPage, CPropertyPage)

CMsgElethPage::CMsgElethPage() : CPropertyPage(CMsgElethPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgElethPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgElethPage::~CMsgElethPage()
{
}

void CMsgElethPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgElethPage)
	DDX_Control(pDX, IDC_LIST_SPACE, m_SpaceList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgElethPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgElethPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_SPACE_MSG, OnSigleOutMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgElethPage message handlers

BOOL CMsgElethPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hSpace_wnd = GetSafeHwnd();
	
	CString CLUSTER_Columns[]=
	{
		_T("ʱ��"),
		_T("�ɻ��ռ�Ⱥ����"),
		_T("ʱ��"),
		_T("�����ռ�Ⱥ����"),

// 			_T("ƽ̨���"),
// 			_T("�豸���"),
// 			_T("�豸����"),
// 			_T("Ŀ������"),
// 			_T("�豸����"),
// 			_T("Ŀ������"),
// 
// 
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
	
	((CListCtrl*)GetDlgItem(IDC_LIST_SPACE))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(CLUSTER_Columns)/sizeof(CLUSTER_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_SPACE))->InsertColumn(i, CLUSTER_Columns[i], LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMsgElethPage::OnSize(UINT nType, int cx, int cy) 
{
	//CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	this->ShowWindow(SW_MAXIMIZE);
	//CPropertyPage::OnSize(nType, cx, cy);
	
	//�ж��Ƿ���ڶ��㴰��
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_SPACE)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}

LRESULT CMsgElethPage::OnSigleOutMessage(WPARAM wParam, LPARAM lParam)
{
//	VCT_SPACE::iterator pFusESM_Dat;
	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;

	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_SPACE))->SetRedraw(FALSE);//�ر��ػ�
		
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_SPACE))->DeleteAllItems();
		
		//��ʾ����
		strTmp.Format("%d",theApp.m_PlaneSpaceBlack.lTimeStamp);//ʱ��
		((CListCtrl*)GetDlgItem(IDC_LIST_SPACE))->SetItemText(nTmp, 0, strTmp);
		
		fTmp = theApp.m_PlaneSpaceBlack.nPlanTypeN;//����Ⱥ����
		strTmp.Format("%d",(int)fTmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_SPACE))->SetItemText(nTmp, 1, strTmp);
	    
		((CListCtrl*)GetDlgItem(IDC_LIST_SPACE))->SetRedraw();//����

	}
	else
	{
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_SPACE))->DeleteAllItems();
	}
	return 0;
}
