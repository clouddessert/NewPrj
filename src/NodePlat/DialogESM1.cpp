// DialogESM1.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "DialogESM1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogESM1 dialog


CDialogESM1::CDialogESM1(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogESM1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogESM1)
	m_data1 = _T("");
	m_style = _T("");
	m_id = _T("");
	//}}AFX_DATA_INIT

}


void CDialogESM1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogESM1)
	DDX_Control(pDX, IDC_LIST1, m_Grid);
	DDX_Text(pDX, IDC_EDIT_DATA1, m_data1);
	DDX_Text(pDX, IDC_EDIT_STYLE, m_style);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogESM1, CDialog)
	//{{AFX_MSG_MAP(CDialogESM1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BUTMOD, OnButmod)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogESM1 message handlers

BOOL CDialogESM1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Grid.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
	m_Grid.InsertColumn(0,"知识序号",LVCFMT_LEFT,110,0);
	m_Grid.InsertColumn(1,"类型",LVCFMT_LEFT,150,1);
	m_Grid.InsertColumn(2,"阈值（不变）",LVCFMT_LEFT,120,2);

	
	AddToGrid();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}





void CDialogESM1::AddToGrid()
{
	ado.OnInitADOConn();
	ado.pRst.CreateInstance(__uuidof(Recordset));
	ado.pRst=ado.pConn->Execute("select * from ESM1 order by ID desc ",NULL,adCmdText);
	_variant_t str;
	_bstr_t sty;
	while(!ado.pRst->adoEOF)
	{		
		str=ado.pRst->GetCollect("类型");
		if(str==(_variant_t)"ESMPre")
		{sty="载频（GHz）";}
		if(str==(_variant_t)"ESMPAw")
		{sty="脉幅（电压）";}
		if(str==(_variant_t)"ESMPwz")
		{sty="脉宽（us）";}
		if(str==(_variant_t)"ESMPRIt")
		{sty="重频（KHz）";}
		if(str==(_variant_t)"ESMScan")
		{sty="天线扫描周期（s）";}
		m_Grid.InsertItem(0,"");
		m_Grid.SetItemText(0,0,(_bstr_t)ado.pRst->GetCollect("ID"));
		m_Grid.SetItemText(0,1,sty);

			m_Grid.SetItemText(0,2,(_bstr_t)ado.pRst->GetCollect("阈值"));


		

		ado.pRst->MoveNext();
	}
	ado.ExitConnect();
}

void CDialogESM1::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CDialogESM1::OnButmod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_style.IsEmpty()||m_data1.IsEmpty())
	{
		MessageBox("基础信息不能为空");
		return;
	}
	ado.OnInitADOConn();
	CString sql;

	sql.Format("update ESM1 set 阈值=%f where ID=%d",atof(m_data1),ids);
	
	try{
		ado.pConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	m_Grid.DeleteAllItems();
		AddToGrid();
}
