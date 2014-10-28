// DialogESM.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "DialogESM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogESM dialog


CDialogESM::CDialogESM(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogESM::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogESM)
	m_id = _T("");
	//}}AFX_DATA_INIT
}


void CDialogESM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogESM)
	DDX_Control(pDX, IDC_COMBO7, m_baseevent);
	DDX_Control(pDX, IDC_COMBO6, m_esmscan);
	DDX_Control(pDX, IDC_COMBO5, m_esmprit);
	DDX_Control(pDX, IDC_COMBO4, m_esmpwz);
	DDX_Control(pDX, IDC_COMBO3, m_esmpaw);
	DDX_Control(pDX, IDC_COMBO2, m_esmpre);
	DDX_Control(pDX, IDC_LIST1, m_Grid);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogESM, CDialog)
	//{{AFX_MSG_MAP(CDialogESM)
	ON_BN_CLICKED(IDC_BUT_ADD, OnButAdd)
	ON_BN_CLICKED(IDC_BUTMOD, OnButMod)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_BN_CLICKED(IDC_BUT_DEL, OnButdel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogESM message handlers

BOOL CDialogESM::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Grid.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
	m_Grid.InsertColumn(0,"ID",LVCFMT_LEFT,50,0);
	m_Grid.InsertColumn(1,"��Ƶ",LVCFMT_LEFT,80,2);
	m_Grid.InsertColumn(2,"����",LVCFMT_LEFT,80,3);
	m_Grid.InsertColumn(3,"����",LVCFMT_LEFT,80,4);
	m_Grid.InsertColumn(4,"��Ƶ",LVCFMT_LEFT,80,5);
	m_Grid.InsertColumn(5,"ɨ������",LVCFMT_LEFT,80,6);
	m_Grid.InsertColumn(6,"�����¼�",LVCFMT_LEFT,80,7);

	AddToGrid();
	
	
	m_esmpre.InsertString(0,"--------");
	m_esmpre.InsertString(1,"����");
	m_esmpre.InsertString(2,"���");
	m_esmpre.InsertString(3,"��С");
	m_esmpre.SetCurSel(0);
	
	m_esmpaw.InsertString(0,"--------");
	m_esmpaw.InsertString(1,"����");
	m_esmpaw.InsertString(2,"���");
	m_esmpaw.InsertString(3,"��С");
	m_esmpaw.SetCurSel(0);
	
	m_esmpwz.InsertString(0,"--------");
	m_esmpwz.InsertString(1,"����");
	m_esmpwz.InsertString(2,"���");
	m_esmpwz.InsertString(3,"��С");
	m_esmpwz.SetCurSel(0);
	
	m_esmprit.InsertString(0,"--------");
	m_esmprit.InsertString(1,"����");
	m_esmprit.InsertString(2,"���");
	m_esmprit.InsertString(3,"��С");
	m_esmprit.SetCurSel(0);
	
	m_esmscan.InsertString(0,"--------");
	m_esmscan.InsertString(1,"����");
	m_esmscan.InsertString(2,"���");
	m_esmscan.InsertString(3,"��С");
	m_esmscan.SetCurSel(0);
	
	m_baseevent.InsertString(0,"����");
	m_baseevent.InsertString(1,"����");
	m_baseevent.InsertString(2,"����");
	m_baseevent.InsertString(3,"�������");
	m_baseevent.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogESM::AddToGrid()
{
	ado.OnInitADOConn();
	ado.pRst.CreateInstance(__uuidof(Recordset));
	ado.pRst=ado.pConn->Execute("select * from ESM order by ID desc ",NULL,adCmdText);
	int esmpre,esmpaw,esmpwz,esmprit,esmscan,esmbaseevent;
	CString sesmpre,sesmpaw,sesmpwz,sesmprit,sesmscan,sesmbaseevent;
	while(!ado.pRst->adoEOF)
	{
		m_Grid.InsertItem(0,"");
		
	
		esmpre=atoi((_bstr_t)ado.pRst->GetCollect("ESMPre"));
		esmpaw=atoi((_bstr_t)ado.pRst->GetCollect("ESMPAw"));
		esmpwz=atoi((_bstr_t)ado.pRst->GetCollect("ESMPwz"));
		esmprit=atoi((_bstr_t)ado.pRst->GetCollect("ESMPRIt"));
		esmscan=atoi((_bstr_t)ado.pRst->GetCollect("ESMScan"));
		esmbaseevent=atoi((_bstr_t)ado.pRst->GetCollect("BaseEvent"));
		


		//esmpre
		if(esmpre==0)
		{
			sesmpre="--------";
		}
		if(esmpre==1)
		{
			sesmpre="����";
		}
		if(esmpre==3)
		{
			sesmpre="���";
		}
		if(esmpre==5)
		{
			sesmpre="��С";
		}

		//esmpaw
		if(esmpaw==0)
		{
			sesmpaw="--------";
		}
		if(esmpaw==1)
		{
			sesmpaw="����";
		}
		if(esmpaw==3)
		{
			sesmpaw="���";
		}
		if(esmpaw==5)
		{
			sesmpaw="��С";
		}

		//esmpwz
		if(esmpwz==0)
		{
			sesmpwz="--------";
		}
		if(esmpwz==1)
		{
			sesmpwz="����";
		}
		if(esmpwz==3)
		{
			sesmpwz="���";
		}
		if(esmpwz==5)
		{
			sesmpwz="��С";
		}

		//esmprit
		if(esmprit==0)
		{
			sesmprit="--------";
		}
		if(esmprit==1)
		{
			sesmprit="����";
		}
		if(esmprit==3)
		{
			sesmprit="���";
		}
		if(esmprit==5)
		{
			sesmprit="��С";
		}

		//esmscan
		if(esmscan==0)
		{
			sesmscan="--------";
		}
		if(esmscan==1)
		{
			sesmscan="����";
		}
		if(esmscan==3)
		{
			sesmscan="���";
		}
		if(esmscan==5)
		{
			sesmscan="��С";
		}
		//baseevent
		if(esmbaseevent==1)
		{
			sesmbaseevent="����";
		}

		if(esmbaseevent==2)
		{
			sesmbaseevent="����";
		}
		if(esmbaseevent==3)
		{
			sesmbaseevent="����";
		}
		if(esmbaseevent==4)
		{
			sesmbaseevent="�������";
		}
		m_Grid.SetItemText(0,0,(_bstr_t)ado.pRst->GetCollect("ID"));
		m_Grid.SetItemText(0,1,sesmpre);
		m_Grid.SetItemText(0,2,sesmpaw);
		m_Grid.SetItemText(0,3,sesmpwz);
		m_Grid.SetItemText(0,4,sesmprit);
		m_Grid.SetItemText(0,5,sesmscan);
		m_Grid.SetItemText(0,6,sesmbaseevent);
		ado.pRst->MoveNext();
		
	}
	ado.ExitConnect();
}

void CDialogESM::OnButAdd() 
{
// TODO: Add your control notification handler code here
		UpdateData(TRUE);

	ado.OnInitADOConn();
	ado.pRst.CreateInstance(__uuidof(Recordset));
	ado.pRst->Open("select * from ESM",ado.pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);

	CString sesmpre,sesmpaw,sesmpwz,sesmprit,sesmscan,sesmbaseevent;
	int esmpre,esmpaw,esmpwz,esmprit,esmscan,esmbaseevent;
	m_esmpre.GetLBText(m_esmpre.GetCurSel(),sesmpre);
	m_esmpaw.GetLBText(m_esmpaw.GetCurSel(),sesmpaw);
	m_esmpwz.GetLBText(m_esmpwz.GetCurSel(),sesmpwz);
	m_esmprit.GetLBText(m_esmprit.GetCurSel(),sesmprit);
	m_esmscan.GetLBText(m_esmscan.GetCurSel(),sesmscan);
	m_baseevent.GetLBText(m_baseevent.GetCurSel(),sesmbaseevent);

//pre
	if(sesmpre=="--------")
	{
		esmpre=0;
	}
	if(sesmpre=="����")
	{
		esmpre=1;
	}
	if(sesmpre=="���")
	{
		esmpre=3;
	}
	if(sesmpre=="��С")
	{
		esmpre=5;
	}
//paw
	if(sesmpaw=="--------")
	{
		esmpaw=0;
	}
	if(sesmpaw=="����")
	{
		esmpaw=1;
	}
	if(sesmpaw=="���")
	{
		esmpaw=3;
	}
	if(sesmpaw=="��С")
	{
		esmpaw=5;
	}
//hoop
	if(sesmpwz=="--------")
	{
		esmpwz=0;
	}
	if(sesmpwz=="����")
	{
		esmpwz=1;
	}
	if(sesmpwz=="���")
	{
		esmpwz=3;
	}
	if(sesmpwz=="��С")
	{
		esmpwz=5;
	}
//esmprit
	if(sesmprit=="--------")
	{
		esmprit=0;
	}
	if(sesmprit=="����")
	{
		esmprit=1;
	}
	if(sesmprit=="���")
	{
		esmprit=3;
	}
	if(sesmprit=="��С")
	{
		esmprit=5;
	}
//
	if(sesmscan=="--------")
	{
		esmscan=0;
	}
	if(sesmscan=="����")
	{
		esmscan=1;
	}
	if(sesmscan=="���")
	{
		esmscan=3;
	}
	if(sesmscan=="��С")
	{
		esmscan=5;
	}
//baseevent
	if(sesmbaseevent=="����")
	{
		esmbaseevent=1;
	}
	if(sesmbaseevent=="����")
	{
		esmbaseevent=2;
	}
	if(sesmbaseevent=="����")
	{
		esmbaseevent=3;
	}
	if(sesmbaseevent=="�������")
	{
		esmbaseevent=4;
	}

	int did=0;
	while(!ado.pRst->adoEOF)
	{
		int id=atoi((_bstr_t)ado.pRst->GetCollect("ID"));
		if(id==atoi(m_id))
		{
			did=1;
			MessageBox("ID���ظ������������!");
		}
		ado.pRst->MoveNext();
	}
	try{
		if(m_id=="")
		{
			MessageBox("ID�Ų���Ϊ��!");
		}
		else if(did==1)
		{
			return;
		}
		else
		{
			ado.pRst->MoveLast();
			ado.pRst->AddNew();
			
			ado.pRst->PutCollect("ID",atol(m_id));
			ado.pRst->PutCollect("ESMPre",(long)esmpre);
			ado.pRst->PutCollect("ESMPAw",(long)esmpaw);
			ado.pRst->PutCollect("ESMPwz",(long)esmpwz);
			ado.pRst->PutCollect("ESMPRIt",(long)esmprit);
			ado.pRst->PutCollect("ESMScan",(long)esmscan);
			ado.pRst->PutCollect("BaseEvent",(long)esmbaseevent);
			ado.pRst->Update();
			ado.ExitConnect();
		}

	}catch(_com_error e)
	{
		MessageBox(e.Description());
	}
	m_Grid.DeleteAllItems();
		AddToGrid();
	
}

void CDialogESM::OnButMod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);


	//esmpre
	int esmpre;
	CString sesmpre;
	m_esmpre.GetLBText(m_esmpre.GetCurSel(),sesmpre);
	if(sesmpre=="--------")
	{
		esmpre=0;
	}
	if(sesmpre=="����")
	{
		esmpre=1;
	}
	if(sesmpre=="��С")
	{
		esmpre=5;
	}
	if(sesmpre=="���")
	{
		esmpre=3;
	}
//esmpaw
	int esmpaw;
	CString sesmpaw;
	m_esmpaw.GetLBText(m_esmpaw.GetCurSel(),sesmpaw);
	if(sesmpaw=="--------")
	{
		esmpaw=0;
	}
	if(sesmpaw=="����")
	{
		esmpaw=1;
	}
	if(sesmpaw=="��С")
	{
		esmpaw=5;
	}
	if(sesmpaw=="���")
	{
		esmpaw=3;
	}
//esmpwz
	int esmpwz;
	CString sesmpwz;
	m_esmpwz.GetLBText(m_esmpwz.GetCurSel(),sesmpwz);
	if(sesmpwz=="--------")
	{
		esmpwz=0;
	}
	if(sesmpwz=="����")
	{
		esmpwz=1;
	}
	if(sesmpwz=="��С")
	{
		esmpwz=5;
	}
	if(sesmpwz=="���")
	{
		esmpwz=3;
	}
	//esmprit
	int esmprit;
	CString sesmprit;
	m_esmprit.GetLBText(m_esmprit.GetCurSel(),sesmprit);
	if(sesmprit=="--------")
	{
		esmprit=0;
	}
	if(sesmprit=="����")
	{
		esmprit=1;
	}
	if(sesmprit=="��С")
	{
		esmprit=5;
	}
	if(sesmprit=="���")
	{
		esmprit=3;
	}
	//esmscan
	int esmscan;
	CString sesmscan;
	m_esmscan.GetLBText(m_esmscan.GetCurSel(),sesmscan);
	if(sesmscan=="--------")
	{
		esmscan=0;
	}
	if(sesmscan=="����")
	{
		esmscan=1;
	}
	if(sesmscan=="��С")
	{
		esmscan=5;
	}
	if(sesmscan=="���")
	{
		esmscan=3;
	}
	//baseevent
	int baseevent;
	CString sbaseevent;
	m_baseevent.GetLBText(m_baseevent.GetCurSel(),sbaseevent);
	if(sbaseevent=="--------")
	{
		baseevent=0;
	}
	if(sbaseevent=="����")
	{
		baseevent=1;
	}
	if(sbaseevent=="����")
	{
		baseevent=2;
	}
	if(sbaseevent=="����")
	{
		baseevent=3;
	}
	if(sbaseevent=="�������")
	{
		baseevent=4;
	}

	ado.OnInitADOConn();
	CString sql;
	sql.Format("update ESM set ESMPre=%d,ESMPAw=%d,ESMPwz=%d,ESMPRIt=%d,ESMScan=%d,BaseEvent=%d where ID=%d",esmpre,esmpaw,esmpwz,esmprit,esmscan,baseevent,ids);
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

void CDialogESM::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i;
	int pos=m_Grid.GetSelectionMark();
	//id
	m_id=m_Grid.GetItemText(pos,0);
	

	
	//esmpre
	CString esmpre=m_Grid.GetItemText(pos,1);
	m_esmpre.InsertString(4,esmpre);
	m_esmpre.SetCurSel(4);
	CString sesmpre;
	for(i=0;;i++)
	{
		m_esmpre.GetLBText(i,sesmpre);
		if(sesmpre==esmpre)
		{
			m_esmpre.DeleteString(i);
			break;
		}
	}
	//m_esmpre.DeleteString(4);

	//ESMPAw
	CString esmpaw=m_Grid.GetItemText(pos,2);
	m_esmpaw.InsertString(4,esmpaw);
	m_esmpaw.SetCurSel(4);
	CString sesmpaw;
	for(i=0;;i++)
	{
		m_esmpaw.GetLBText(i,sesmpaw);
		if(sesmpaw==esmpaw)
		{
			m_esmpaw.DeleteString(i);
			break;
		}
	}
//	m_esmpaw.DeleteString(4);
	//ESMPwz
	CString esmpwz=m_Grid.GetItemText(pos,3);
	m_esmpwz.InsertString(4,esmpwz);
	m_esmpwz.SetCurSel(4);
	CString sesmpwz;
	for(i=0;;i++)
	{
		m_esmpwz.GetLBText(i,sesmpwz);
		if(sesmpwz==esmpwz)
		{
			m_esmpwz.DeleteString(i);
			break;
		}
	}
//	m_esmpwz.DeleteString(4);
	//esmprit
CString esmprit=m_Grid.GetItemText(pos,4);
m_esmprit.InsertString(4,esmprit);
m_esmprit.SetCurSel(4);
CString sesmprit;
for(i=0;;i++)
{
	m_esmprit.GetLBText(i,sesmprit);
	if(sesmprit==esmprit)
	{
		m_esmprit.DeleteString(i);
			break;
	}
}
//	m_esmprit.DeleteString(4);
	//esmscan
	CString esmscan=m_Grid.GetItemText(pos,5);
	m_esmscan.InsertString(4,esmscan);
	m_esmscan.SetCurSel(4);
	CString sesmscan;
	for(i=0;;i++)
	{
		m_esmscan.GetLBText(i,sesmscan);
		if(sesmscan==esmscan)
		{
			m_esmscan.DeleteString(i);
			break;
		}
	}
//	m_esmscan.DeleteString(4);
	//BaseEvent
	CString baseevent=m_Grid.GetItemText(pos,6);
	m_baseevent.InsertString(4,baseevent);
	m_baseevent.SetCurSel(4);
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

void CDialogESM::OnButdel() 
{
	// TODO: Add your control notification handler code here
	int id=atoi(m_id);	
	ado.OnInitADOConn();
	CString sql;
	sql.Format("delete from ESM where ID=%d",id);
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
