// DialogSPA.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "DialogSPA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogSPA dialog
extern CNodePlatApp theApp;

CDialogSPA::CDialogSPA(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogSPA::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogSPA)
	m_id = _T("");
	m_distance = _T("");
	//}}AFX_DATA_INIT
}


void CDialogSPA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogSPA)
	DDX_Control(pDX, IDC_COMBO4, m_objtype);
	DDX_Control(pDX, IDC_LIST1, m_Grid);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_distance);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogSPA, CDialog)
	//{{AFX_MSG_MAP(CDialogSPA)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_BN_CLICKED(IDC_BUT_ADD, OnButadd)
	ON_BN_CLICKED(IDC_BUTMOD, OnButmod)
	ON_BN_CLICKED(IDC_BUT_DEL, OnButdel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogSPA message handlers

BOOL CDialogSPA::OnInitDialog() 
{
     CDialog::OnInitDialog();
	
// TODO: Add extra initialization here
     m_Grid.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
     m_Grid.InsertColumn(0,"知识序号",LVCFMT_LEFT,80,0);
     m_Grid.InsertColumn(1,"目标类型",LVCFMT_LEFT,110,1);
	 m_Grid.InsertColumn(2,"距离（米）",LVCFMT_LEFT,110,1);

	AddToGrid();
	m_objtype.InsertString(0,"舰船");
	m_objtype.InsertString(1,"飞机");
	m_objtype.InsertString(2,"导弹");
	m_objtype.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDialogSPA::AddToGrid()
{
	//theApp.m_DataBase.pRst.CreateInstance(__uuidof(Recordset));
	theApp.m_DataBase.pRst=theApp.m_DataBase.pConn->Execute("select * from 空间群 order by ID desc ",NULL,adCmdText);
	CString sobjtype;
	int objtype;
	while(!theApp.m_DataBase.pRst->adoEOF)
	{
		objtype=atoi((_bstr_t)theApp.m_DataBase.pRst->GetCollect("ObjType"));
		if(objtype==1)
		{
			sobjtype="舰船";
		}
		if(objtype==2)
		{
			sobjtype="飞机";
		}
		if(objtype==3)
		{
			sobjtype="导弹";
		}
		m_Grid.InsertItem(0,"");
		m_Grid.SetItemText(0,0,(_bstr_t)theApp.m_DataBase.pRst->GetCollect("ID"));
		m_Grid.SetItemText(0,1,sobjtype);
		m_Grid.SetItemText(0,2,(_bstr_t)theApp.m_DataBase.pRst->GetCollect("Distance"));
		
		theApp.m_DataBase.pRst->MoveNext();
		
	}
	theApp.m_DataBase.pRst->Close();
}



void CDialogSPA::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i;
	int pos=m_Grid.GetSelectionMark();
	//id
	m_id=m_Grid.GetItemText(pos,0);
	
	//objtype
	CString objtype=m_Grid.GetItemText(pos,1);
	m_objtype.InsertString(3,objtype);
	m_objtype.SetCurSel(3);
	
	CString sobjtype;
	for(i=0;;i++)
	{
		m_objtype.GetLBText(i,sobjtype);
		if(sobjtype==objtype)
		{
			m_objtype.DeleteString(i);
			break;
		}
	}
	m_distance=m_Grid.GetItemText(pos,2);

	ids=atoi(m_id);
	UpdateData(FALSE);
	*pResult = 0;
}

void CDialogSPA::OnButadd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//theApp.m_DataBase.pRst.CreateInstance(__uuidof(Recordset));
	theApp.m_DataBase.pRst->Open("select * from 空间群",theApp.m_DataBase.pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	CString sobjtype;
	int objtype;
	m_objtype.GetLBText(m_objtype.GetCurSel(),sobjtype);
	if(sobjtype=="舰船")
	{
		objtype=1;
	}
	if(sobjtype=="飞机")
	{
		objtype=2;
	}
	if(sobjtype=="导弹")
	{
		objtype=3;
	}
	
	int did=0;
	while(!theApp.m_DataBase.pRst->adoEOF)
	{
		int id=atoi((_bstr_t)theApp.m_DataBase.pRst->GetCollect("ID"));
		if(id==atoi(m_id))
		{
			did=1;
			MessageBox("ID号重复，请重新添加!");
		}
		theApp.m_DataBase.pRst->MoveNext();
	}
	//此处可不做判断，由数据库来做唯一性判断

	try{
		if(m_id==""||m_distance=="")
		{
			MessageBox("知识序号或者距离不可为空!");
		}
		else if(did==1)
		{
			return;
		}
		else
		{	
			theApp.m_DataBase.pRst->MoveLast();
			theApp.m_DataBase.pRst->AddNew();
			
			theApp.m_DataBase.pRst->PutCollect("ID",atol(m_id));
			theApp.m_DataBase.pRst->PutCollect("ObjType",(long)objtype);
			theApp.m_DataBase.pRst->PutCollect("Distance",atol(m_distance));
			theApp.m_DataBase.pRst->Update();
		}
	}
	catch(_com_error e)
	{
		MessageBox(e.Description());
	}
	theApp.m_DataBase.pRst->Close();

	m_Grid.DeleteAllItems();
	theApp.m_DataBase.GetSpaceGroup();
	AddToGrid();
}

void CDialogSPA::OnButmod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//objtype
	int objtype;
	CString sobjtype;
	m_objtype.GetLBText(m_objtype.GetCurSel(),sobjtype);
	if(sobjtype=="舰船")
	{
		objtype=1;
	}
	if(sobjtype=="飞机")
	{
		objtype=2;
	}
	if(sobjtype=="导弹")
	{
		objtype=3;
	}
	CString sql;
	sql.Format("update 空间群 set ObjType=%d,Distance=%d  where ID=%d",objtype,atol(m_distance),ids);
	try{
		theApp.m_DataBase.pConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	m_Grid.DeleteAllItems();
	theApp.m_DataBase.GetSpaceGroup();
	AddToGrid();
}

void CDialogSPA::OnButdel() 
{
	// TODO: Add your control notification handler code here
	int id=atoi(m_id);	
	CString sql;
	sql.Format("delete from 空间群 where ID=%d",id);
	try{
		theApp.m_DataBase.pConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	m_Grid.DeleteAllItems();
	theApp.m_DataBase.GetSpaceGroup();
	AddToGrid();
}
