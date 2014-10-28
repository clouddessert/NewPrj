// DialogFUN.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "DialogFUN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogFUN dialog


CDialogFUN::CDialogFUN(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogFUN::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogFUN)
	m_id = _T("");
	//}}AFX_DATA_INIT
}


void CDialogFUN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogFUN)
	DDX_Control(pDX, IDC_COMBO3, m_fun);
	DDX_Control(pDX, IDC_COMBO2, m_tra);
	DDX_Control(pDX, IDC_COMBO1, m_typ);
	DDX_Control(pDX, IDC_LIST1, m_Grid);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogFUN, CDialog)
	//{{AFX_MSG_MAP(CDialogFUN)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_BN_CLICKED(IDC_BUT_ADD, OnButAdd)
	ON_BN_CLICKED(IDC_BUTMOD, OnButmod)
	ON_BN_CLICKED(IDC_BUT_DEL, OnButDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogFUN message handlers

BOOL CDialogFUN::OnInitDialog() 
{
CDialog::OnInitDialog();
	
// TODO: Add extra initialization here
     m_Grid.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
     m_Grid.InsertColumn(0,"֪ʶ���",LVCFMT_LEFT,80,0);
     m_Grid.InsertColumn(1,"Ⱥ����",LVCFMT_LEFT,110,1);
     m_Grid.InsertColumn(2,"ƽ̨̬��",LVCFMT_LEFT,110,2);
	 m_Grid.InsertColumn(3,"�����¼�",LVCFMT_LEFT,110,3);
	
	 
	 
	 AddToGrid();


	 m_typ.InsertString(0,"Ԥ����");
	 m_typ.InsertString(1,"���Ż�");
	 m_typ.InsertString(2,"������");
//	 m_typ.SetCurSel(0);
	 
	 
	 
	 m_tra.InsertString(0,"����");
	 m_tra.InsertString(1,"Ѳ��");
	 m_tra.InsertString(2,"����");
	 m_tra.InsertString(3,"����");
	 m_tra.InsertString(4,"��ը");
	 m_tra.InsertString(5,"ͻ��");
	 m_tra.InsertString(6,"����");
	 m_tra.InsertString(7,"Ԥ��ָ��");
//	 m_tra.SetCurSel(0);
	 
	 m_fun.InsertString(0,"����");
	 m_fun.InsertString(1,"Ѳ��");
	 m_fun.InsertString(2,"����");
	 m_fun.InsertString(3,"����");
	 m_fun.InsertString(4,"��ը");
	 m_fun.InsertString(5,"ͻ��");
	 m_fun.InsertString(6,"����");
	 m_fun.InsertString(7,"Ԥ��");
	 m_fun.InsertString(8,"���");
//     m_fun.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogFUN::AddToGrid()
{
	ado.OnInitADOConn();
	ado.pRst.CreateInstance(__uuidof(Recordset));
	ado.pRst=ado.pConn->Execute("select * from ����Ⱥ order by ID desc ",NULL,adCmdText);
	int type,trackbaseevent,funbaseevent;
	CString stype,strackbaseevent,sfunbaseevent;
	while(!ado.pRst->adoEOF)
	{
		m_Grid.InsertItem(0,"");
		type=atoi((_bstr_t)ado.pRst->GetCollect("Ⱥ����"));
		trackbaseevent=atoi((_bstr_t)ado.pRst->GetCollect("ƽ̨̬��"));
		funbaseevent=atoi((_bstr_t)ado.pRst->GetCollect("�����¼�"));
		

		if(type==1)
		{
			stype="Ԥ����";
		}
		if(type==2)
		{
			stype="���Ż�";
		}
		if(type==3)
		{
			stype="������";
		}
		//trackevent
		if(trackbaseevent==1)
		{
			strackbaseevent="����";
		}
		if(trackbaseevent==2)
		{
			strackbaseevent="Ѳ��";
		}
		if(trackbaseevent==3)
		{
			strackbaseevent="����";
		}
		if(trackbaseevent==4)
		{
			strackbaseevent="����";
		}
		if(trackbaseevent==5)
		{
			strackbaseevent="��ը";
		}
		if(trackbaseevent==6)
		{
			strackbaseevent="ͻ��";
		}
		if(trackbaseevent==7)
		{
			strackbaseevent="����";
		}
		if(trackbaseevent==8)
		{
			strackbaseevent="Ԥ��ָ��";
		}
		
		//
		if(funbaseevent==1)
		{
			sfunbaseevent="����";
		}
		if(funbaseevent==2)
		{
			sfunbaseevent="Ѳ��";
		}
		if(funbaseevent==3)
		{
			sfunbaseevent="����";
		}
		if(funbaseevent==4)
		{
			sfunbaseevent="����";
		}
		if(funbaseevent==5)
		{
			sfunbaseevent="��ը";
		}
		if(funbaseevent==6)
		{
			sfunbaseevent="ͻ��";
		}
		if(funbaseevent==7)
		{
			sfunbaseevent="����";
		}
		if(funbaseevent==8)
		{
			sfunbaseevent="Ԥ��";
		}	
		if(funbaseevent==9)
		{
			sfunbaseevent="���";
		}
		
		
		m_Grid.SetItemText(0,0,(_bstr_t)ado.pRst->GetCollect("ID"));
		m_Grid.SetItemText(0,1,stype);
		m_Grid.SetItemText(0,2,strackbaseevent);
		m_Grid.SetItemText(0,3,sfunbaseevent);
		ado.pRst->MoveNext();
		
	}
	ado.ExitConnect();
}


void CDialogFUN::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i;
	int pos=m_Grid.GetSelectionMark();
	//id
	m_id=m_Grid.GetItemText(pos,0);
	

	//type
	CString type=m_Grid.GetItemText(pos,1);
	m_typ.InsertString(3,type);

	m_typ.SetCurSel(3);
	
	CString stype;
	for(i=0;;i++)
	{
		m_typ.GetLBText(i,stype);
		if(stype==type)
		{
			m_typ.DeleteString(i);
			break;
		}
	}
	//trackbaseevent
	CString trackbaseevent=m_Grid.GetItemText(pos,2);
	m_tra.InsertString(8,trackbaseevent);
	m_tra.SetCurSel(8);
	CString strackbaseevent;
	for(i=0;;i++)
	{
		m_tra.GetLBText(i,strackbaseevent);
		if(strackbaseevent==trackbaseevent)
		{
			m_tra.DeleteString(i);
			break;
		}
	}
//funbaseevent
	CString funbaseevent=m_Grid.GetItemText(pos,3);
	m_fun.InsertString(9,funbaseevent);
	m_fun.SetCurSel(9);
	CString sfunbaseevent;
	for(i=0;;i++)
	{
		m_fun.GetLBText(i,sfunbaseevent);
		if(sfunbaseevent==funbaseevent)
		{
			m_fun.DeleteString(i);
			break;
		}
	}
	ids=atoi(m_id);
	UpdateData(FALSE);
	*pResult = 0;
}

void CDialogFUN::OnButAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
/*	pConn.CreateInstance("ADODB.Connection");
	pConn->ConnectionString="Provider=Microsoft.ACE.OLEDB.12.0;Data Source=C:\\Users\\Administrator\\Desktop\\Database.accdb;Persist Security Info=False";
	pConn->Open("","","",adConnectUnspecified);
	*/
	ado.OnInitADOConn();
	ado.pRst.CreateInstance(__uuidof(Recordset));
	ado.pRst->Open("select * from ����Ⱥ",ado.pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	int type,trackbaseevent,funbaseevent;
	CString stype,strackbaseevent,sfunbaseevent;
	m_typ.GetLBText(m_typ.GetCurSel(),stype);
	m_tra.GetLBText(m_tra.GetCurSel(),strackbaseevent);
	m_fun.GetLBText(m_fun.GetCurSel(),sfunbaseevent);


	//type
		if(stype=="Ԥ����")
		{
			type=1;
		}
		if(stype=="���Ż�")
		{
			type=2;
		}
		if(stype=="������")
		{
			type=3;
		}

		//
		if(strackbaseevent=="����")
		{
			trackbaseevent=1;
		}
		if(strackbaseevent=="Ѳ��")
		{
			trackbaseevent=2;
		}
		if(strackbaseevent=="����")
		{
			trackbaseevent=3;
		}
		if(strackbaseevent=="����")
		{
			trackbaseevent=4;
		}
		if(strackbaseevent=="��ը")
		{
			trackbaseevent=5;
		}
		if(strackbaseevent=="ͻ��")
		{
			trackbaseevent=6;
		}
		if(strackbaseevent=="����")
		{
			trackbaseevent=7;
		}
		if(strackbaseevent=="Ԥ��ָ��")
		{
			trackbaseevent=8;
		}


		//
		if(sfunbaseevent=="����")
		{
			funbaseevent=1;
		}
		if(sfunbaseevent=="Ѳ��")
		{
			funbaseevent=2;
		}
		if(sfunbaseevent=="����")
		{
			funbaseevent=3;
		}
		if(sfunbaseevent=="����")
		{
			funbaseevent=4;
		}	
		if(sfunbaseevent=="��ը")
		{
			funbaseevent=5;
		}
		if(sfunbaseevent=="ͻ��")
		{
			funbaseevent=6;
		}
		if(sfunbaseevent=="����")
		{
			funbaseevent=7;
		}
		if(sfunbaseevent=="Ԥ��")
		{
			funbaseevent=8;
		}
		if(sfunbaseevent=="���")
		{
			funbaseevent=9;
		}



	try{
		ado.pRst->MoveLast();
		ado.pRst->AddNew();
	ado.pRst->PutCollect("ID",atol(m_id));
	ado.pRst->PutCollect("Ⱥ����",(long)type);
	ado.pRst->PutCollect("ƽ̨̬��",(long)trackbaseevent);
	ado.pRst->PutCollect("�����¼�",(long)funbaseevent);

	ado.pRst->Update();
	ado.ExitConnect();

	}catch(_com_error e)
	{
		e.Description();
	}
	m_Grid.DeleteAllItems();
		AddToGrid();
}

void CDialogFUN::OnButmod() 
{
	// TODO: Add your control notification handler code here
		UpdateData(TRUE);
	//az
	int type;
	CString stype;
	m_typ.GetLBText(m_typ.GetCurSel(),stype);
	if(stype=="Ԥ����")
		{
			type=1;
		}
		if(stype=="���Ż�")
		{
			type=2;
		}
		if(stype=="������")
		{
			type=3;
		}
		
		//pre
		int trackbaseevent;
	CString strackbaseevent;
	m_tra.GetLBText(m_tra.GetCurSel(),strackbaseevent);
		if(strackbaseevent=="����")
		{
			trackbaseevent=1;
		}
		if(strackbaseevent=="Ѳ��")
		{
			trackbaseevent=2;
		}
		if(strackbaseevent=="����")
		{
			trackbaseevent=3;
		}
		if(strackbaseevent=="����")
		{
			trackbaseevent=4;
		}
		if(strackbaseevent=="��ը")
		{
			trackbaseevent=5;
		}
		if(strackbaseevent=="ͻ��")
		{
			trackbaseevent=6;
		}
		if(strackbaseevent=="����")
		{
			trackbaseevent=7;
		}
		if(strackbaseevent=="Ԥ��ָ��")
		{
			trackbaseevent=8;
		}
//paw
	int funbaseevent;
	CString sfunbaseevent;
	m_fun.GetLBText(m_fun.GetCurSel(),sfunbaseevent);
		if(sfunbaseevent=="����")
		{
			funbaseevent=1;
		}
		if(sfunbaseevent=="Ѳ��")
		{
			funbaseevent=2;
		}
		if(sfunbaseevent=="����")
		{
			funbaseevent=3;
		}
		if(sfunbaseevent=="����")
		{
			funbaseevent=4;
		}	
		if(sfunbaseevent=="��ը")
		{
			funbaseevent=5;
		}
		if(sfunbaseevent=="ͻ��")
		{
			funbaseevent=6;
		}
		if(sfunbaseevent=="����")
		{
			funbaseevent=7;
		}
		if(sfunbaseevent=="Ԥ��")
		{
			funbaseevent=8;
		}
		if(sfunbaseevent=="���")
		{
			funbaseevent=9;
		}


	ado.OnInitADOConn();
	CString sql;
	sql.Format("update ����Ⱥ set Ⱥ����=%d,ƽ̨̬��=%d,�����¼�=%d where ID=%d",type,trackbaseevent,funbaseevent,ids);
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

void CDialogFUN::OnButDel() 
{
	// TODO: Add your control notification handler code here
	int id=atoi(m_id);	
	ado.OnInitADOConn();
	CString sql;
	sql.Format("delete from ����Ⱥ where ID=%d",id);
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
