// DialogCOM1.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "DialogCOM1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogCOM1 dialog
extern CNodePlatApp theApp;

CDialogCOM1::CDialogCOM1(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogCOM1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogCOM1)
	m_style = _T("");
	m_data1 = _T("");
	m_id = _T("");
	//}}AFX_DATA_INIT


}


void CDialogCOM1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogCOM1)
	DDX_Control(pDX, IDC_LIST1, m_Grid);
	DDX_Text(pDX, IDC_EDIT_STYLE, m_style);
	DDX_Text(pDX, IDC_EDIT_DATA1, m_data1);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogCOM1, CDialog)
	//{{AFX_MSG_MAP(CDialogCOM1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_BN_CLICKED(IDC_BUTMOD, OnButmod)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogCOM1 message handlers

BOOL CDialogCOM1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Grid.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
	m_Grid.InsertColumn(0,"֪ʶ���",LVCFMT_LEFT,80,0);
	m_Grid.InsertColumn(1,"����",LVCFMT_LEFT,150,1);
	m_Grid.InsertColumn(2,"��ֵ�����䣩",LVCFMT_LEFT,130,2);
	
	AddToGrid();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}





void CDialogCOM1::AddToGrid()
{
	theApp.m_DataBase.pRst=theApp.m_DataBase.pConn->Execute("select * from COM1 order by ID desc ",NULL,adCmdText);
	_variant_t str;
	_bstr_t sty;
	while(!theApp.m_DataBase.pRst->adoEOF)
	{

		str=theApp.m_DataBase.pRst->GetCollect("����");
		if(str==(_variant_t)"Pre")
		{sty="��Ƶ��Mz��";}
		if(str==(_variant_t)"Paw")
		{sty="��������ѹ��";}
		if(str==(_variant_t)"Hoop")
		{sty="��Ƶ����";}
		m_Grid.InsertItem(0,"");
		m_Grid.SetItemText(0,0,(_bstr_t)theApp.m_DataBase.pRst->GetCollect("ID"));
		m_Grid.SetItemText(0,1,sty);
		m_Grid.SetItemText(0,2,(_bstr_t)theApp.m_DataBase.pRst->GetCollect("��ֵ"));
	
		theApp.m_DataBase.pRst->MoveNext();
	}
	theApp.m_DataBase.pRst->Close();
}



void CDialogCOM1::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int pos=m_Grid.GetSelectionMark();
	m_id=m_Grid.GetItemText(pos,0);
	m_style=m_Grid.GetItemText(pos,1);
	m_data1=m_Grid.GetItemText(pos,2);
	
	
	ids=atoi(m_id);
	UpdateData(FALSE);
	*pResult = 0;
}

void CDialogCOM1::OnButmod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_style.IsEmpty()||m_data1.IsEmpty())
	{
		MessageBox("������Ϣ����Ϊ��");
		return;
	}
	CString sql;
	sql.Format("update COM1 set ��ֵ=%f where ID=%d",atof(m_data1),ids);
	
	try{
	theApp.m_DataBase.pConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	m_Grid.DeleteAllItems();
	theApp.m_DataBase.GetCOMThd();
	AddToGrid();	
}
