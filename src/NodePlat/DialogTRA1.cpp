// DialogTRA1.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "DialogTRA1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogTRA1 dialog
extern CNodePlatApp theApp;

CDialogTRA1::CDialogTRA1(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogTRA1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogTRA1)
	m_data1 = _T("");
	m_id = _T("");
	m_style = _T("");
	//}}AFX_DATA_INIT

}


void CDialogTRA1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogTRA1)
	DDX_Control(pDX, IDC_LIST1, m_Grid);
	DDX_Text(pDX, IDC_EDIT_DATA1, m_data1);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
	DDX_Text(pDX, IDC_EDIT_STYLE, m_style);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogTRA1, CDialog)
	//{{AFX_MSG_MAP(CDialogTRA1)
	ON_BN_CLICKED(IDC_BUTMOD, OnButmod)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogTRA1 message handlers

BOOL CDialogTRA1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Grid.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
	m_Grid.InsertColumn(0,"知识序号",LVCFMT_LEFT,110,0);
	m_Grid.InsertColumn(1,"特征",LVCFMT_LEFT,150,1);
	m_Grid.InsertColumn(2,"阈值（不变）",LVCFMT_LEFT,130,2);


	AddToGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogTRA1::AddToGrid()
{
	//theApp.m_DataBase.pRst.CreateInstance(__uuidof(Recordset));
	theApp.m_DataBase.pRst=theApp.m_DataBase.pConn->Execute("select * from Track1 order by ID desc ",NULL,adCmdText);
	_variant_t str;
	_bstr_t sty;
	while(!theApp.m_DataBase.pRst->adoEOF)
	{
		str=theApp.m_DataBase.pRst->GetCollect("类型");
		if(str==(_variant_t)"Rd")
		{sty="径距（米）";}
		if(str==(_variant_t)"Speed")
		{sty="速度（米/秒）";}
		if(str==(_variant_t)"AddSpeed")
		{sty="加速度（米/秒）";}
		if(str==(_variant_t)"Azimuth")
		{sty="航向（度）";}
		if(str==(_variant_t)"High")
		{sty="高度（米）";}
		m_Grid.InsertItem(0,"");
		m_Grid.SetItemText(0,0,(_bstr_t)theApp.m_DataBase.pRst->GetCollect("ID"));
		m_Grid.SetItemText(0,1,sty);
		m_Grid.SetItemText(0,2,(_bstr_t)theApp.m_DataBase.pRst->GetCollect("阈值"));

		theApp.m_DataBase.pRst->MoveNext();
	}
	theApp.m_DataBase.pRst->Close();
}





void CDialogTRA1::OnButmod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_style.IsEmpty()||m_data1.IsEmpty())
	{
		MessageBox("基础信息不能为空");
		return;
	}
	CString sql;
	sql.Format("update Track1 set 阈值=%f where ID=%d",atof(m_data1),ids);
	
	try
	{
		theApp.m_DataBase.pConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	m_Grid.DeleteAllItems();
	theApp.m_DataBase.GetTrackThd();
	AddToGrid();
}

void CDialogTRA1::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
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
