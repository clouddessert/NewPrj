// QBFusGraph.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "QBFusGraph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQBFusGraph dialog
extern CNodePlatApp theApp;

CQBFusGraph::CQBFusGraph(CWnd* pParent /*=NULL*/)
	: CDialog(CQBFusGraph::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQBFusGraph)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CQBFusGraph::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQBFusGraph)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQBFusGraph, CDialog)
	//{{AFX_MSG_MAP(CQBFusGraph)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQBFusGraph message handlers

BOOL CQBFusGraph::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here

	theApp.hQbFusTu_wnd = GetSafeHwnd();	
	CString QBFUSTU_Columns[]=
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
	
	((CListCtrl*)GetDlgItem(IDC_LIST_QBFUSTU))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(QBFUSTU_Columns)/sizeof(QBFUSTU_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_QBFUSTU))->InsertColumn(i, QBFUSTU_Columns[i], LVCFMT_CENTER, 80);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
