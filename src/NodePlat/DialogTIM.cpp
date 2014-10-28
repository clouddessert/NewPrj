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
	m_Grid.InsertColumn(0,"ÖªÊ¶ÐòºÅ",LVCFMT_LEFT,80,0);
	m_Grid.InsertColumn(1,"¾¯½ä",LVCFMT_LEFT,50,1);
	m_Grid.InsertColumn(2,"Ñ²Âß",LVCFMT_LEFT,50,2);
	m_Grid.InsertColumn(3,"¹¥»÷",LVCFMT_LEFT,50,3);
	m_Grid.InsertColumn(4,"À¹½Ø",LVCFMT_LEFT,50,4);
	m_Grid.InsertColumn(5,"ºäÕ¨",LVCFMT_LEFT,50,5);
	m_Grid.InsertColumn(6,"Í»·À",LVCFMT_LEFT,50,6);
	m_Grid.InsertColumn(7,"¸ÉÈÅ",LVCFMT_LEFT,50,7);
	m_Grid.InsertColumn(8,"Ô¤¾¯",LVCFMT_LEFT,50,8);
	m_Grid.InsertColumn(9,"Õì²ì",LVCFMT_LEFT,50,9);
	AddToGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogTIM::AddToGrid()
{
	ado.OnInitADOConn();
	ado.pRst.CreateInstance(__uuidof(Recordset));
	ado.pRst=ado.pConn->Execute("select * from Ïà»¥×÷ÓÃÈº order by ID desc ",NULL,adCmdText);
	int alert,patrol,attact,intercept,bomb,penetrate,interference,warm,reconnoitre;
	CString salert,spatrol,sattact,sintercept,sbomb,spenetrate,sinterference,swarm,sreconnoitre;
	while(!ado.pRst->adoEOF)
	{
		alert=atoi((_bstr_t)ado.pRst->GetCollect("¾¯½ä"));
		patrol=atoi((_bstr_t)ado.pRst->GetCollect("Ñ²Âß"));
		attact=atoi((_bstr_t)ado.pRst->GetCollect("¹¥»÷"));
		intercept=atoi((_bstr_t)ado.pRst->GetCollect("À¹½Ø"));
		bomb=atoi((_bstr_t)ado.pRst->GetCollect("ºäÕ¨"));
		penetrate=atoi((_bstr_t)ado.pRst->GetCollect("Í»·À"));
		interference=atoi((_bstr_t)ado.pRst->GetCollect("¸ÉÈÅ"));
		warm=atoi((_bstr_t)ado.pRst->GetCollect("Ô¤¾¯"));
		reconnoitre=atoi((_bstr_t)ado.pRst->GetCollect("Õì²ì"));
		//alert
		if(alert==1)
		{
			salert="¡Ì";
		}
		if(alert==0)
		{
			salert="  ";
		}
		//patrol
		if(patrol==1)
		{
			spatrol="¡Ì";
		}
		if(patrol==0)
		{
			spatrol="  ";
		}
		//attact
		if(attact==1)
		{
			sattact="¡Ì";
		}
		if(attact==0)
		{
			sattact="  ";
		}
		if(intercept==1)
		{
			sintercept="¡Ì";
		}
		if(intercept==0)
		{
		    sintercept="  ";
		}				
			
		if(bomb==1)
		{
			sbomb="¡Ì";
		}		
		if(bomb==0)
		{
			sbomb="  ";
		}
			
		if(penetrate==1)
		{
			spenetrate="¡Ì";
		}			
		if(penetrate==0)
		{
			spenetrate="  ";
		}
		if(interference==1)
		{
			sinterference="¡Ì";
		}			
		if(interference==0)
		{
			sinterference="  ";
		}
			
		if(warm==1)
		{
			swarm="¡Ì";
		}			
		if(warm==0)
		{
			swarm="  ";
		}
		if(reconnoitre==1)
		{
			sreconnoitre="¡Ì";
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
	if(ale=="¡Ì")
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
	if(pat=="¡Ì")
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
	if(att=="¡Ì")
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
	if(intt=="¡Ì")
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
	if(bom=="¡Ì")
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
	if(pen=="¡Ì")
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
	if(fev=="¡Ì")
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
	if(war=="¡Ì")
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
	if(rec=="¡Ì")
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
	ado.pRst->Open("select * from Ïà»¥×÷ÓÃÈº",ado.pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);

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
		ado.pRst->PutCollect("¾¯½ä",(long)ale);
		ado.pRst->PutCollect("Ñ²Âß",(long)pat);
		ado.pRst->PutCollect("¹¥»÷",(long)att);
		ado.pRst->PutCollect("À¹½Ø",(long)inte);
		ado.pRst->PutCollect("ºäÕ¨",(long)bom);
		ado.pRst->PutCollect("Í»·À",(long)pen);
		ado.pRst->PutCollect("¸ÉÈÅ",(long)fev);
		ado.pRst->PutCollect("Ô¤¾¯",(long)war);
		ado.pRst->PutCollect("Õì²ì",(long)rec);
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
	sql.Format("update Ïà»¥×÷ÓÃÈº set ¾¯½ä=%d,Ñ²Âß=%d,¹¥»÷=%d,À¹½Ø=%d,ºäÕ¨=%d,Í»·À=%d,¸ÉÈÅ=%d,Ô¤¾¯=%d,Õì²ì=%d where ID=%d",ale,pat,att,inte,bom,pen,fev,war,rec,ids);
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
	sql.Format("delete from Ïà»¥×÷ÓÃÈº where ID=%d",id);
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
