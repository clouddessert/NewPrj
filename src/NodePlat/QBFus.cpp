// QBFus.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "QBFus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQBFus dialog
extern CNodePlatApp theApp;

CQBFus::CQBFus(CWnd* pParent /*=NULL*/)
	: CDialog(CQBFus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQBFus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CQBFus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQBFus)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQBFus, CDialog)
	//{{AFX_MSG_MAP(CQBFus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQBFus message handlers

BOOL CQBFus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hQbFus_wnd = GetSafeHwnd();
	
	CString QBFUS_Columns[]=
	{   
		_T("ʱ  ��"),//0
			_T("������"),//1
			_T("�·�����"),//2	
			_T("�·���λ"),//3
			_T("�·�����"),//4

			_T("�ںϾ���"),//8	
			_T("�ںϷ�λ"),//9
			_T("�ں�����"),//10

			_T("������ֵ"),//5	
			_T("��λ��ֵ"),//6
			_T("������ֵ"),//7

			_T("�������"),//11	
			_T("��λ���"),//12
			_T("�������"),//13			
	};
	
	((CListCtrl*)GetDlgItem(IDC_LIST_QBFUS))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(QBFUS_Columns)/sizeof(QBFUS_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_QBFUS))->InsertColumn(i, QBFUS_Columns[i], LVCFMT_CENTER, 80);


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
