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
     m_Grid.InsertColumn(0,"ÖªÊ¶ÐòºÅ",LVCFMT_LEFT,80,0);
     m_Grid.InsertColumn(1,"ÈºÀàÐÍ",LVCFMT_LEFT,110,1);
     m_Grid.InsertColumn(2,"Æ½Ì¨Ì¬ÊÆ",LVCFMT_LEFT,110,2);
	 m_Grid.InsertColumn(3,"¹¦ÄÜÊÂ¼þ",LVCFMT_LEFT,110,3);
	
	 
	 
	 AddToGrid();


	 m_typ.InsertString(0,"Ô¤¾¯»ú");
	 m_typ.InsertString(1,"¸ÉÈÅ»ú");
	 m_typ.InsertString(2,"¹¥»÷»ú");
//	 m_typ.SetCurSel(0);
	 
	 
	 
	 m_tra.InsertString(0,"¾¯½ä");
	 m_tra.InsertString(1,"Ñ²Âß");
	 m_tra.InsertString(2,"À¹½Ø");
	 m_tra.InsertString(3,"¹¥»÷");
	 m_tra.InsertString(4,"ºäÕ¨");
	 m_tra.InsertString(5,"Í»·À");
	 m_tra.InsertString(6,"¸ÉÈÅ");
	 m_tra.InsertString(7,"Ô¤¾¯Ö¸»Ó");
//	 m_tra.SetCurSel(0);
	 
	 m_fun.InsertString(0,"¾¯½ä");
	 m_fun.InsertString(1,"Ñ²Âß");
	 m_fun.InsertString(2,"¹¥»÷");
	 m_fun.InsertString(3,"À¹½Ø");
	 m_fun.InsertString(4,"ºäÕ¨");
	 m_fun.InsertString(5,"Í»·À");
	 m_fun.InsertString(6,"¸ÉÈÅ");
	 m_fun.InsertString(7,"Ô¤¾¯");
	 m_fun.InsertString(8,"Õì²ì");
//     m_fun.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogFUN::AddToGrid()
{
	ado.OnInitADOConn();
	ado.pRst.CreateInstance(__uuidof(Recordset));
	ado.pRst=ado.pConn->Execute("select * from ¹¦ÄÜÈº order by ID desc ",NULL,adCmdText);
	int type,trackbaseevent,funbaseevent;
	CString stype,strackbaseevent,sfunbaseevent;
	while(!ado.pRst->adoEOF)
	{
		m_Grid.InsertItem(0,"");
		type=atoi((_bstr_t)ado.pRst->GetCollect("ÈºÀàÐÍ"));
		trackbaseevent=atoi((_bstr_t)ado.pRst->GetCollect("Æ½Ì¨Ì¬ÊÆ"));
		funbaseevent=atoi((_bstr_t)ado.pRst->GetCollect("¹¦ÄÜÊÂ¼þ"));
		

		if(type==1)
		{
			stype="Ô¤¾¯»ú";
		}
		if(type==2)
		{
			stype="¸ÉÈÅ»ú";
		}
		if(type==3)
		{
			stype="¹¥»÷»ú";
		}
		//trackevent
		if(trackbaseevent==1)
		{
			strackbaseevent="¾¯½ä";
		}
		if(trackbaseevent==2)
		{
			strackbaseevent="Ñ²Âß";
		}
		if(trackbaseevent==3)
		{
			strackbaseevent="À¹½Ø";
		}
		if(trackbaseevent==4)
		{
			strackbaseevent="¹¥»÷";
		}
		if(trackbaseevent==5)
		{
			strackbaseevent="ºäÕ¨";
		}
		if(trackbaseevent==6)
		{
			strackbaseevent="Í»·À";
		}
		if(trackbaseevent==7)
		{
			strackbaseevent="¸ÉÈÅ";
		}
		if(trackbaseevent==8)
		{
			strackbaseevent="Ô¤¾¯Ö¸»Ó";
		}
		
		//
		if(funbaseevent==1)
		{
			sfunbaseevent="¾¯½ä";
		}
		if(funbaseevent==2)
		{
			sfunbaseevent="Ñ²Âß";
		}
		if(funbaseevent==3)
		{
			sfunbaseevent="¹¥»÷";
		}
		if(funbaseevent==4)
		{
			sfunbaseevent="À¹½Ø";
		}
		if(funbaseevent==5)
		{
			sfunbaseevent="ºäÕ¨";
		}
		if(funbaseevent==6)
		{
			sfunbaseevent="Í»·À";
		}
		if(funbaseevent==7)
		{
			sfunbaseevent="¸ÉÈÅ";
		}
		if(funbaseevent==8)
		{
			sfunbaseevent="Ô¤¾¯";
		}	
		if(funbaseevent==9)
		{
			sfunbaseevent="Õì²ì";
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
	ado.pRst->Open("select * from ¹¦ÄÜÈº",ado.pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	int type,trackbaseevent,funbaseevent;
	CString stype,strackbaseevent,sfunbaseevent;
	m_typ.GetLBText(m_typ.GetCurSel(),stype);
	m_tra.GetLBText(m_tra.GetCurSel(),strackbaseevent);
	m_fun.GetLBText(m_fun.GetCurSel(),sfunbaseevent);


	//type
		if(stype=="Ô¤¾¯»ú")
		{
			type=1;
		}
		if(stype=="¸ÉÈÅ»ú")
		{
			type=2;
		}
		if(stype=="¹¥»÷»ú")
		{
			type=3;
		}

		//
		if(strackbaseevent=="¾¯½ä")
		{
			trackbaseevent=1;
		}
		if(strackbaseevent=="Ñ²Âß")
		{
			trackbaseevent=2;
		}
		if(strackbaseevent=="À¹½Ø")
		{
			trackbaseevent=3;
		}
		if(strackbaseevent=="¹¥»÷")
		{
			trackbaseevent=4;
		}
		if(strackbaseevent=="ºäÕ¨")
		{
			trackbaseevent=5;
		}
		if(strackbaseevent=="Í»·À")
		{
			trackbaseevent=6;
		}
		if(strackbaseevent=="¸ÉÈÅ")
		{
			trackbaseevent=7;
		}
		if(strackbaseevent=="Ô¤¾¯Ö¸»Ó")
		{
			trackbaseevent=8;
		}


		//
		if(sfunbaseevent=="¾¯½ä")
		{
			funbaseevent=1;
		}
		if(sfunbaseevent=="Ñ²Âß")
		{
			funbaseevent=2;
		}
		if(sfunbaseevent=="¹¥»÷")
		{
			funbaseevent=3;
		}
		if(sfunbaseevent=="À¹½Ø")
		{
			funbaseevent=4;
		}	
		if(sfunbaseevent=="ºäÕ¨")
		{
			funbaseevent=5;
		}
		if(sfunbaseevent=="Í»·À")
		{
			funbaseevent=6;
		}
		if(sfunbaseevent=="¸ÉÈÅ")
		{
			funbaseevent=7;
		}
		if(sfunbaseevent=="Ô¤¾¯")
		{
			funbaseevent=8;
		}
		if(sfunbaseevent=="Õì²ì")
		{
			funbaseevent=9;
		}



	try{
		ado.pRst->MoveLast();
		ado.pRst->AddNew();
	ado.pRst->PutCollect("ID",atol(m_id));
	ado.pRst->PutCollect("ÈºÀàÐÍ",(long)type);
	ado.pRst->PutCollect("Æ½Ì¨Ì¬ÊÆ",(long)trackbaseevent);
	ado.pRst->PutCollect("¹¦ÄÜÊÂ¼þ",(long)funbaseevent);

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
	if(stype=="Ô¤¾¯»ú")
		{
			type=1;
		}
		if(stype=="¸ÉÈÅ»ú")
		{
			type=2;
		}
		if(stype=="¹¥»÷»ú")
		{
			type=3;
		}
		
		//pre
		int trackbaseevent;
	CString strackbaseevent;
	m_tra.GetLBText(m_tra.GetCurSel(),strackbaseevent);
		if(strackbaseevent=="¾¯½ä")
		{
			trackbaseevent=1;
		}
		if(strackbaseevent=="Ñ²Âß")
		{
			trackbaseevent=2;
		}
		if(strackbaseevent=="À¹½Ø")
		{
			trackbaseevent=3;
		}
		if(strackbaseevent=="¹¥»÷")
		{
			trackbaseevent=4;
		}
		if(strackbaseevent=="ºäÕ¨")
		{
			trackbaseevent=5;
		}
		if(strackbaseevent=="Í»·À")
		{
			trackbaseevent=6;
		}
		if(strackbaseevent=="¸ÉÈÅ")
		{
			trackbaseevent=7;
		}
		if(strackbaseevent=="Ô¤¾¯Ö¸»Ó")
		{
			trackbaseevent=8;
		}
//paw
	int funbaseevent;
	CString sfunbaseevent;
	m_fun.GetLBText(m_fun.GetCurSel(),sfunbaseevent);
		if(sfunbaseevent=="¾¯½ä")
		{
			funbaseevent=1;
		}
		if(sfunbaseevent=="Ñ²Âß")
		{
			funbaseevent=2;
		}
		if(sfunbaseevent=="¹¥»÷")
		{
			funbaseevent=3;
		}
		if(sfunbaseevent=="À¹½Ø")
		{
			funbaseevent=4;
		}	
		if(sfunbaseevent=="ºäÕ¨")
		{
			funbaseevent=5;
		}
		if(sfunbaseevent=="Í»·À")
		{
			funbaseevent=6;
		}
		if(sfunbaseevent=="¸ÉÈÅ")
		{
			funbaseevent=7;
		}
		if(sfunbaseevent=="Ô¤¾¯")
		{
			funbaseevent=8;
		}
		if(sfunbaseevent=="Õì²ì")
		{
			funbaseevent=9;
		}


	ado.OnInitADOConn();
	CString sql;
	sql.Format("update ¹¦ÄÜÈº set ÈºÀàÐÍ=%d,Æ½Ì¨Ì¬ÊÆ=%d,¹¦ÄÜÊÂ¼þ=%d where ID=%d",type,trackbaseevent,funbaseevent,ids);
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
	sql.Format("delete from ¹¦ÄÜÈº where ID=%d",id);
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
