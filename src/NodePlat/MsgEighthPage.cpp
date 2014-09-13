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
		// 		_T("ƽ̨���"),
		// 		_T("�豸���"),
		// 		_T("�豸����"),
		_T("������"),//0
			// 
			// 		_T("����"),
			// 		_T("��λ"),
			// 		_T("����"),
			// 		_T("���Ժ���"),
			// 		_T("�źŵ���ʱ��"),
			// 		_T("Ŀ�귽λ�ǽ��ٶ�"),
			// 		_T("Ŀ�����ǽ��ٶ�"),
			// 		_T("Ŀ��ռ�����X"),
			// 		_T("Ŀ��ռ�����Y"),
			// 		_T("Ŀ��ռ�����Z"),
			// 		_T("Ŀ������ٶ�X"),
			// 		_T("Ŀ������ٶ�Y"),
			// 		_T("Ŀ������ٶ�z"),
			// 		
			// 		_T("ƽ̨����"),
			// 		_T("ƽ̨����"),
			// 		_T("���Ŷ�"),
			// 		_T("����/����"),
			
			_T("Ŀ������"),  //1
			
			_T("ƽ̨���"),//2
			_T("�豸���"),//3
			_T("�豸����"),//4
			
			
			_T("ƽ̨����"), //5
			_T("���Ŷ�"),  //6
			_T("��λ"),  //7
			
			_T("ƽ̨����"), //8
			_T("����"),     //9
			_T("γ��"),     //10
			
			_T("����"),
			
			_T("����"),
			_T("���Ժ���"),
			_T("�źŵ���ʱ��"),
			_T("Ŀ�귽λ�ǽ��ٶ�"),
			_T("Ŀ�����ǽ��ٶ�"),
			_T("Ŀ��ռ�����X"),
			_T("Ŀ��ռ�����Y"),
			_T("Ŀ��ռ�����Z"),
			_T("Ŀ������ٶ�X"),
			_T("Ŀ������ٶ�Y"),
			_T("Ŀ������ٶ�z"),
			_T("����/����"),
	};
	
	((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(Trace_Columns)/sizeof(Trace_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_MulTRACE))->InsertColumn(i, Trace_Columns[i], LVCFMT_CENTER, 80);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
