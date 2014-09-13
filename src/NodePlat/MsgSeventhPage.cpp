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
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgSeventhPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgSeventhPage)
	ON_WM_SIZE()
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
		// 		_T("ƽ̨���"),
		// 		_T("�豸���"),
		// 		_T("�豸����"),
		_T("������"),//0
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
           	_T("Ŀ������"),//1
			_T("ƽ̨���"),  //0
			_T("�豸���"),
			_T("�豸����"),
			
			
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
	
	
	((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(Communicate_Columns)/sizeof(Communicate_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_MulCOMM))->InsertColumn(i, Communicate_Columns[i], LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
