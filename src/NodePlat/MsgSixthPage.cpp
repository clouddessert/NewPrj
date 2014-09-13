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
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgSixthPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgSixthPage)
	ON_WM_SIZE()
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
		// 		_T("ƽ̨���"),
		// 		_T("�豸���"),
		// 		_T("�豸����"),
		_T("������"),//0
			// 		
			// 		_T("��Ƶ��Ϣ"),
			// 		_T("��Ƶ��Ϣ"),
			// 		_T("������Ϣ"),
			// 		_T("�źŵ���ʱ��"),
			// 		_T("�������"),
			// 		_T("���﷽λ"),
			// 		_T("����"),
			// 		_T("����ɨ����Ϣ"),
			// 		_T("����������Ϣ�ṹ"),
			// 		
			// 		_T("�״���;"),
			// 		_T("�״�����"),
			// 		_T("��в�ȼ�"),
			// 		_T("��Ч���书��"),
			// 		_T("ƽ̨����"),
			// 		_T("ƽ̨�ͺ�"),
			// 		_T("ƽ̨����"),
			// 		_T("��������"),
			// 		_T("���Ŷ�"),
			// 		_T("����"),	
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
			_T("�źŵ���ʱ��"),
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

