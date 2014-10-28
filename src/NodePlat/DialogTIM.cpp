// DialogTIM.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "DialogTIM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogTIM dialog


CDialogTIM::CDialogTIM(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogTIM::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogTIM)
	m_id = _T("");
	m_ale = FALSE;
	m_pat = FALSE;
	m_att = FALSE;
	m_int = FALSE;
	m_bom = FALSE;
	m_pen = FALSE;
	m_fev = FALSE;
	m_war = FALSE;
	m_rec = FALSE;
	//}}AFX_DATA_INIT
}


void CDialogTIM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogTIM)
	DDX_Control(pDX, IDC_LIST1, m_Grid);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Check(pDX, IDC_CHECK1, m_ale);
	DDX_Check(pDX, IDC_CHECK2, m_pat);
	DDX_Check(pDX, IDC_CHECK3, m_att);
	DDX_Check(pDX, IDC_CHECK4, m_int);
	DDX_Check(pDX, IDC_CHECK5, m_bom);
	DDX_Check(pDX, IDC_CHECK6, m_pen);
	DDX_Check(pDX, IDC_CHECK7, m_fev);
	DDX_Check(pDX, IDC_CHECK8, m_war);
	DDX_Check(pDX, IDC_CHECK9, m_rec);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogTIM, CDialog)
	//{{AFX_MSG_MAP(CDialogTIM)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_BN_CLICKED(IDC_BUT_ADD, OnButadd)
	ON_BN_CLICKED(IDC_BUTMOD, OnButmod)
	ON_BN_CLICKED(IDC_BUT_DEL, OnButdel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogTIM message handlers

BOOL CDialogTIM::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Grid.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
	m_Grid.InsertColumn(0,"֪ʶ���",LVCFMT_LEFT,80,0);
	m_Grid.InsertColumn(1,"����",LVCFMT_LEFT,50,1);
	m_Grid.InsertColumn(2,"Ѳ��",LVCFMT_LEFT,50,2);
	m_Grid.InsertColumn(3,"����",LVCFMT_LEFT,50,3);
	m_Grid.InsertColumn(4,"����",LVCFMT_LEFT,50,4);
	m_Grid.InsertColumn(5,"��ը",LVCFMT_LEFT,50,5);
	m_Grid.InsertColumn(6,"ͻ��",LVCFMT_LEFT,50,6);
	m_Grid.InsertColumn(7,"����",LVCFMT_LEFT,50,7);
	m_Grid.InsertColumn(8,"Ԥ��",LVCFMT_LEFT,50,8);
	m_Grid.InsertColumn(9,"���",LVCFMT_LEFT,50,9);
	AddToGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogTIM::AddToGrid()
{
	ado.OnInitADOConn();
	ado.pRst.CreateInstance(__uuidof(Recordset));
	ado.pRst=ado.pConn->Execute("select * from �໥����Ⱥ order by ID desc ",NULL,adCmdText);
	int alert,patrol,attact,intercept,bomb,penetrate,interference,warm,reconnoitre;
	CString salert,spatrol,sattact,sintercept,sbomb,spenetrate,sinterference,swarm,sreconnoitre;
	while(!ado.pRst->adoEOF)
	{
		alert=atoi((_bstr_t)ado.pRst->GetCollect("����"));
		patrol=atoi((_bstr_t)ado.pRst->GetCollect("Ѳ��"));
		attact=atoi((_bstr_t)ado.pRst->GetCollect("����"));
		intercept=atoi((_bstr_t)ado.pRst->GetCollect("����"));
		bomb=atoi((_bstr_t)ado.pRst->GetCollect("��ը"));
		penetrate=atoi((_bstr_t)ado.pRst->GetCollect("ͻ��"));
		interference=atoi((_bstr_t)ado.pRst->GetCollect("����"));
		warm=atoi((_bstr_t)ado.pRst->GetCollect("Ԥ��"));
		reconnoitre=atoi((_bstr_t)ado.pRst->GetCollect("���"));
		//alert
		if(alert==1)
		{
			salert="��";
		}
		if(alert==0)
		{
			salert="  ";
		}
		//patrol
		if(patrol==1)
		{
			spatrol="��";
		}
		if(patrol==0)
		{
			spatrol="  ";
		}
		//attact
		if(attact==1)
		{
			sattact="��";
		}
		if(attact==0)
		{
			sattact="  ";
		}
		if(intercept==1)
		{
			sintercept="��";
		}
		if(intercept==0)
		{
		    sintercept="  ";
		}				
			
		if(bomb==1)
		{
			sbomb="��";
		}		
		if(bomb==0)
		{
			sbomb="  ";
		}
			
		if(penetrate==1)
		{
			spenetrate="��";
		}			
		if(penetrate==0)
		{
			spenetrate="  ";
		}
		if(interference==1)
		{
			sinterference="��";
		}			
		if(interference==0)
		{
			sinterference="  ";
		}
			
		if(warm==1)
		{
			swarm="��";
		}			
		if(warm==0)
		{
			swarm="  ";
		}
		if(reconnoitre==1)
		{
			sreconnoitre="��";
		}			
		if(reconnoitre==0)
		{
			sreconnoitre="  ";
		}
		m_Grid.InsertItem(0,"");
		m_Grid.SetItemText(0,0,(_bstr_t)ado.pRst->GetCollect("ID"));
		m_Grid.SetItemText(0,1,salert);
		m_Grid.SetItemText(0,2,spatrol);
		m_Grid.SetItemText(0,3,sattact);
		m_Grid.SetItemText(0,4,sintercept);
		m_Grid.SetItemText(0,5,sbomb);
		m_Grid.SetItemText(0,6,spenetrate);
		m_Grid.SetItemText(0,7,sinterference);
		m_Grid.SetItemText(0,8,swarm);
		m_Grid.SetItemText(0,9,sreconnoitre);
		
		
		ado.pRst->MoveNext();

	}
	ado.ExitConnect();
}



//DEL void CDialogTIM::OnInitADOConn()
//DEL {
//DEL 	try{
//DEL 		
//DEL 		CoInitialize(NULL);
//DEL 		
//DEL 		pConn.CreateInstance("ADODB.Connection");
//DEL 		
//DEL 		pConn->ConnectionString="Provider=Microsoft.ACE.OLEDB.12.0;Data Source=..\\1021 NodePlat\\db\\Database.mdb;Persist Security Info=False";
//DEL 		pConn->Open("","","",adConnectUnspecified);
//DEL 	}catch(_com_error e)
//DEL 	{
//DEL 		AfxMessageBox(e.Description());
//DEL 	}
//DEL }

//DEL void CDialogTIM::ExitConnect()
//DEL {
//DEL 	if(pRst!=NULL)
//DEL 		pRst->Close();
//DEL 	pConn->Close();
//DEL 	pRst.Release();
//DEL 	pConn.Release();
//DEL 	CoUninitialize();
//DEL }

void CDialogTIM::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	int pos=m_Grid.GetSelectionMark();
	m_id=m_Grid.GetItemText(pos,0);
	
	//ale
	CString ale;
	ale=m_Grid.GetItemText(pos,1);
	if(ale=="��")
	{
		m_ale=TRUE;
	}
	else
	{
		m_ale=FALSE;
	}

	//pat
	CString pat;
	pat=m_Grid.GetItemText(pos,2);
	if(pat=="��")
	{
		m_pat=TRUE;
	}
	else
	{
		m_pat=FALSE;
	}

	//att
	CString att;
	att=m_Grid.GetItemText(pos,3);
	if(att=="��")
	{
		m_att=TRUE;
	}
	else
	{
		m_att=FALSE;
	}
	//intt
	CString intt;
	intt=m_Grid.GetItemText(pos,4);
	if(intt=="��")
	{
		m_int=TRUE;
	}
	else
	{
		m_int=FALSE;
	}
	//bom
	CString bom;
	bom=m_Grid.GetItemText(pos,5);
	if(bom=="��")
	{
		m_bom=TRUE;
	}
	else
	{
		m_bom=FALSE;
	}

	//pen
	CString pen;
	pen=m_Grid.GetItemText(pos,6);
	if(pen=="��")
	{
		m_pen=TRUE;
	}
	else
	{
		m_pen=FALSE;
	}
	//fev
	CString fev;
	fev=m_Grid.GetItemText(pos,7);
	if(fev=="��")
	{
		m_fev=TRUE;
	}
	else
	{
		m_fev=FALSE;
	}
	//war
	CString war;
	war=m_Grid.GetItemText(pos,8);
	if(war=="��")
	{
		m_war=TRUE;
	}
	else
	{
		m_war=FALSE;
	}
	//rec
	CString rec;
	rec=m_Grid.GetItemText(pos,9);
	if(rec=="��")
	{
		m_rec=TRUE;
	}
	else
	{
		m_rec=FALSE;
	}
ids=atoi(m_id);
	UpdateData(FALSE);
	*pResult = 0;
}

void CDialogTIM::OnButadd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ado.OnInitADOConn();
	ado.pRst.CreateInstance(__uuidof(Recordset));
	ado.pRst->Open("select * from �໥����Ⱥ",ado.pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);

	int ale,pat,att,inte,bom,pen,fev,war,rec;

	if(m_ale==TRUE)
	{
		ale=1;
	}
	else
	{
		ale=0;
	}
	
	if(m_pat==TRUE)
	{
		pat=1;
	}
	else
	{
		pat=0;
	}

	if(m_att==TRUE)
	{
		att=1;
	}
	else
	{
		att=0;
	}

	if(m_int==TRUE)
	{
		inte=1;
	}
	else
	{
		inte=0;
	}

	if(m_bom==TRUE)
	{
		bom=1;
	}
	else
	{
		bom=0;
	}

	if(m_pen==TRUE)
	{
		pen=1;
	}
	else
	{
		pen=0;
	}

	if(m_fev==TRUE)
	{
		fev=1;
	}
	else
	{
		fev=0;
	}

	if(m_war==TRUE)
	{
		war=1;
	}
	else
	{
		war=0;
	}

	if(m_rec==TRUE)
	{
		rec=1;
	}
	else
	{
		rec=0;
	}

	try{
		ado.pRst->MoveLast();
		ado.pRst->AddNew();
		ado.pRst->PutCollect("ID",atol(m_id));
		ado.pRst->PutCollect("����",(long)ale);
		ado.pRst->PutCollect("Ѳ��",(long)pat);
		ado.pRst->PutCollect("����",(long)att);
		ado.pRst->PutCollect("����",(long)inte);
		ado.pRst->PutCollect("��ը",(long)bom);
		ado.pRst->PutCollect("ͻ��",(long)pen);
		ado.pRst->PutCollect("����",(long)fev);
		ado.pRst->PutCollect("Ԥ��",(long)war);
		ado.pRst->PutCollect("���",(long)rec);
		ado.pRst->Update();
		ado.ExitConnect();
	}catch(_com_error e)
	{
		e.Description();
	}
	m_Grid.DeleteAllItems();
		AddToGrid();

}

void CDialogTIM::OnButmod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int ale,pat,att,inte,bom,pen,fev,war,rec;
	
	if(m_ale==TRUE)
	{
		ale=1;
	}
	else
	{
		ale=0;
	}
	
	if(m_pat==TRUE)
	{
		pat=1;
	}
	else
	{
		pat=0;
	}
	
	if(m_att==TRUE)
	{
		att=1;
	}
	else
	{
		att=0;
	}
	
	if(m_int==TRUE)
	{
		inte=1;
	}
	else
	{
		inte=0;
	}
	
	if(m_bom==TRUE)
	{
		bom=1;
	}
	else
	{
		bom=0;
	}
	
	if(m_pen==TRUE)
	{
		pen=1;
	}
	else
	{
		pen=0;
	}
	
	if(m_fev==TRUE)
	{
		fev=1;
	}
	else
	{
		fev=0;
	}
	
	if(m_war==TRUE)
	{
		war=1;
	}
	else
	{
		war=0;
	}
	
	if(m_rec==TRUE)
	{
		rec=1;
	}
	else
	{
		rec=0;
	}
	ado.OnInitADOConn();
	CString sql;
	sql.Format("update �໥����Ⱥ set ����=%d,Ѳ��=%d,����=%d,����=%d,��ը=%d,ͻ��=%d,����=%d,Ԥ��=%d,���=%d where ID=%d",ale,pat,att,inte,bom,pen,fev,war,rec,ids);
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

void CDialogTIM::OnButdel() 
{
	// TODO: Add your control notification handler code here
	int id=atoi(m_id);	
	ado.OnInitADOConn();
	CString sql;
	sql.Format("delete from �໥����Ⱥ where ID=%d",id);
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
