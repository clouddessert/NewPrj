// DialogCOM.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "DialogCOM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include <IOSTREAM>
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CDialogCOM dialog
extern CNodePlatApp theApp;

CDialogCOM::CDialogCOM(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogCOM::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogCOM)
	m_id = _T("");
	//}}AFX_DATA_INIT
}


void CDialogCOM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogCOM)
	DDX_Control(pDX, IDC_COMBO5, m_baseevent);
	DDX_Control(pDX, IDC_COMBO4, m_hoop);
	DDX_Control(pDX, IDC_COMBO3, m_paw);
	DDX_Control(pDX, IDC_COMBO2, m_pre);
	DDX_Control(pDX, IDC_LIST1, m_Grid);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogCOM, CDialog)
	//{{AFX_MSG_MAP(CDialogCOM)
	ON_BN_CLICKED(IDC_BUT_ADD, OnButAdd)
	ON_BN_CLICKED(IDC_BUTMOD, OnButmod)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_BN_CLICKED(IDC_BUT_DEL, OnButDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogCOM message handlers

BOOL CDialogCOM::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Grid.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
	m_Grid.InsertColumn(0,"知识序号",LVCFMT_LEFT,90,0);
	m_Grid.InsertColumn(1,"载频",LVCFMT_LEFT,80,1);
	m_Grid.InsertColumn(2,"脉幅",LVCFMT_LEFT,80,2);
	m_Grid.InsertColumn(3,"跳频次数",LVCFMT_LEFT,90,3);
	m_Grid.InsertColumn(4,"基本事件",LVCFMT_LEFT,110,4);
	AddToGrid();
	
	m_pre.InsertString(0,"--------");
	m_pre.InsertString(1,"不变");
	m_pre.InsertString(2,"变大");
	m_pre.InsertString(3,"变小");
	m_pre.SetCurSel(0);

	m_paw.InsertString(0,"--------");
	m_paw.InsertString(1,"不变");
	m_paw.InsertString(2,"变大");
	m_paw.InsertString(3,"变小");
	m_paw.SetCurSel(0);

	m_hoop.InsertString(0,"--------");
	m_hoop.InsertString(1,"不变");
	m_hoop.InsertString(2,"变大");
	m_hoop.InsertString(3,"变小");
	m_hoop.SetCurSel(0);

	
	m_baseevent.InsertString(0,"联络");
	m_baseevent.InsertString(1,"指挥");
	
	
	m_baseevent.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogCOM::AddToGrid()
{
	theApp.m_DataBase.pRst=theApp.m_DataBase.pConn->Execute("select * from COM order by ID desc ",NULL,adCmdText);
	int pre,paw,hoop,baseevent;
	CString spre,spaw,shoop;
	CString sbaseevent;
	while(!theApp.m_DataBase.pRst->adoEOF)
	{
		m_Grid.InsertItem(0,"");
		pre=atoi((_bstr_t)theApp.m_DataBase.pRst->GetCollect("Pre"));
		paw=atoi((_bstr_t)theApp.m_DataBase.pRst->GetCollect("PAw"));
		hoop=atoi((_bstr_t)theApp.m_DataBase.pRst->GetCollect("Hoop"));
		baseevent=atoi((_bstr_t)theApp.m_DataBase.pRst->GetCollect("BaseEvent"));

		//pre
		if(pre==1)
		{
			spre="不变";
		}
		if(pre==3)
		{
			spre="变大";
		}
		if(pre==5)
		{
			spre="变小";
		}
		if(pre==0)
		{
			spre="--------";
		}
		//paw
		if(paw==1)
		{
			spaw="不变";
		}
		if(paw==3)
		{
			spaw="变大";
		}
		if(paw==5)
		{
			spaw="变小";
		}
		if(paw==0)
		{
			spaw="--------";
		}
		//hoop
		if(hoop==1)
		{
			shoop="不变";
		}
		if(hoop==3)
		{
			shoop="变大";
		}
		if(hoop==5)
		{
			shoop="变小";
		}
		if(hoop==0)
		{
			shoop="--------";
		}

	
		if(baseevent==1)
		{
			sbaseevent="联络";
		}
		if(baseevent==2)
		{
			sbaseevent="指挥";
		}
		m_Grid.SetItemText(0,0,(_bstr_t)theApp.m_DataBase.pRst->GetCollect("ID"));
		m_Grid.SetItemText(0,1,spre);
		m_Grid.SetItemText(0,2,spaw);
		m_Grid.SetItemText(0,3,shoop);
		m_Grid.SetItemText(0,4,sbaseevent);
		theApp.m_DataBase.pRst->MoveNext();
		
	}
	theApp.m_DataBase.pRst->Close();
}



void CDialogCOM::OnButAdd() 
{
	UpdateData(TRUE);
	theApp.m_DataBase.pRst->Open("select * from COM",theApp.m_DataBase.pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);

	CString spre,spaw,shoop,sbaseevent;
	int pre,paw,hoop,baseevent;

	m_pre.GetLBText(m_pre.GetCurSel(),spre);
	m_paw.GetLBText(m_paw.GetCurSel(),spaw);
	m_hoop.GetLBText(m_hoop.GetCurSel(),shoop);
	m_baseevent.GetLBText(m_baseevent.GetCurSel(),sbaseevent);


//pre
	if(spre=="不变")
	{
		pre=1;
	}
	if(spre=="变大")
	{
		pre=3;
	}
	if(spre=="变小")
	{
		pre=5;
	}
	if(spre=="--------")
	{
		pre=0;
	}
//paw
	if(spaw=="不变")
	{
		paw=1;
	}
	if(spaw=="变大")
	{
		paw=3;
	}
	if(spaw=="变小")
	{
		paw=5;
	}
	if(spaw=="--------")
	{
		paw=0;
	}
//hoop
	if(shoop=="不变")
	{
		hoop=1;
	}
	if(shoop=="变大")
	{
		hoop=3;
	}
	if(shoop=="变小")
	{
		hoop=5;
	}
	if(shoop=="--------")
	{
		hoop=0;
	}
//baseevent
	if(sbaseevent=="联络")
	{
		baseevent=1;
	}
	if(sbaseevent=="指挥")
	{
		baseevent=2;
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
	try
	{
		if(m_id=="")
		{
			MessageBox("ID号不可为空!");
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
			theApp.m_DataBase.pRst->PutCollect("Pre",(long)pre);
			theApp.m_DataBase.pRst->PutCollect("PAw",(long)paw);
			theApp.m_DataBase.pRst->PutCollect("Hoop",(long)hoop);
			theApp.m_DataBase.pRst->PutCollect("BaseEvent",(long)baseevent);
			theApp.m_DataBase.pRst->Update();
		}	
	}
	catch(_com_error e)
	{
		e.Description();
	}
	theApp.m_DataBase.pRst->Close();

	m_Grid.DeleteAllItems();
	theApp.m_DataBase.GetCOMEvent();
	AddToGrid();
}

void CDialogCOM::OnButmod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);


	//pre
	int pre;
	CString spre;
	m_pre.GetLBText(m_pre.GetCurSel(),spre);
	if(spre=="--------")
	{
		pre=0;
	}
	if(spre=="不变")
	{
		pre=1;
	}
	if(spre=="变小")
	{
		pre=5;
	}
	if(spre=="变大")
	{
		pre=3;
	}
//paw
	int paw;
	CString spaw;
	m_paw.GetLBText(m_paw.GetCurSel(),spaw);
	if(spaw=="--------")
	{
		paw=0;
	}
	if(spaw=="不变")
	{
		paw=1;
	}
	if(spaw=="变小")
	{
		paw=5;
	}
	if(spaw=="变大")
	{
		paw=3;
	}
//hoop
	int hoop;
	CString shoop;
	m_hoop.GetLBText(m_hoop.GetCurSel(),shoop);
	if(shoop=="--------")
	{
		hoop=0;
	}
	if(shoop=="不变")
	{
		hoop=1;
	}
	if(shoop=="变小")
	{
		hoop=5;
	}
	if(shoop=="变大")
	{
		hoop=3;
	}
	//baseevent
	int baseevent;
	CString sbaseevent;
	m_baseevent.GetLBText(m_baseevent.GetCurSel(),sbaseevent);

	if(sbaseevent=="联络")
	{
		baseevent=1;
	}
	if(sbaseevent=="指挥")
	{
		baseevent=2;
	}
	

	CString sql;
	sql.Format("update COM set Pre=%d,PAw=%d,Hoop=%d,BaseEvent=%d where ID=%d",pre,paw,hoop,baseevent,ids);
	try{
		theApp.m_DataBase.pConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	m_Grid.DeleteAllItems();
	theApp.m_DataBase.GetCOMEvent();
	AddToGrid();
}

void CDialogCOM::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i;
	int pos=m_Grid.GetSelectionMark();
	//id
	m_id=m_Grid.GetItemText(pos,0);
	
	//Pre
	CString pre=m_Grid.GetItemText(pos,1);
	m_pre.InsertString(4,pre);
	m_pre.SetCurSel(4);
	CString spre;
	for(i=0;;i++)
	{
		m_pre.GetLBText(i,spre);
		if(spre==pre)
		{
			m_pre.DeleteString(i);
			break;
		}
	}
//	m_pre.DeleteString(4);
	//PAw
	CString paw=m_Grid.GetItemText(pos,2);
	m_paw.InsertString(4,paw);
	m_paw.SetCurSel(4);
	CString spaw;
	for(i=0;;i++)
	{
		m_paw.GetLBText(i,spaw);
		if(spaw==paw)
		{
			m_paw.DeleteString(i);
			break;
		}
	}
//	m_paw.DeleteString(4);
	//Hoop
	CString hoop=m_Grid.GetItemText(pos,3);
	m_hoop.InsertString(4,hoop);
	m_hoop.SetCurSel(4);
	CString shoop;
	for(i=0;;i++)
	{
		m_hoop.GetLBText(i,shoop);
		if(shoop==hoop)
		{
			m_hoop.DeleteString(i);
			break;
		}
	}
//	m_hoop.DeleteString(4);
	//BaseEvent
	CString baseevent=m_Grid.GetItemText(pos,4);
	m_baseevent.InsertString(2,baseevent);
	m_baseevent.SetCurSel(2);
	CString sbaseevent;
	for(i=0;;i++)
	{
		m_baseevent.GetLBText(i,sbaseevent);
		if(sbaseevent==baseevent)
		{
			m_baseevent.DeleteString(i);
			break;
		}
	}

	ids=atoi(m_id);
	UpdateData(FALSE);
	*pResult = 0;
}



void CDialogCOM::OnButDel() 
{
	// TODO: Add your control notification handler code here
	int id=atoi(m_id);	
	CString sql;
	sql.Format("delete from COM where ID=%d",id);
	try
	{
		theApp.m_DataBase.pConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	m_Grid.DeleteAllItems();
	theApp.m_DataBase.GetCOMEvent();
	AddToGrid();
}
