// DialogTRA.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "DialogTRA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogTRA dialog
extern CNodePlatApp theApp;

CDialogTRA::CDialogTRA(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogTRA::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogTRA)
	m_id = _T("");
	//}}AFX_DATA_INIT
}


void CDialogTRA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogTRA)
	DDX_Control(pDX, IDC_COMBO6, m_baseevent);
	DDX_Control(pDX, IDC_COMBO5, m_high);
	DDX_Control(pDX, IDC_COMBO4, m_azimuth);
	DDX_Control(pDX, IDC_COMBO3, m_addspeed);
	DDX_Control(pDX, IDC_COMBO2, m_speed);
	DDX_Control(pDX, IDC_COMBO1, m_rd);
	DDX_Control(pDX, IDC_LIST1, m_Grid);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogTRA, CDialog)
	//{{AFX_MSG_MAP(CDialogTRA)
	ON_BN_CLICKED(IDC_BUT_ADD, OnButAdd)
	ON_BN_CLICKED(IDC_BUTMOD, OnButmod)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_BN_CLICKED(IDC_BUT_DEL, OnButdel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogTRA message handlers

BOOL CDialogTRA::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Grid.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
    m_Grid.InsertColumn(0,"知识序号",LVCFMT_LEFT,80,0);
	m_Grid.InsertColumn(1,"径距",LVCFMT_LEFT,80,1);
	m_Grid.InsertColumn(2,"速度",LVCFMT_LEFT,80,2);
	m_Grid.InsertColumn(3,"加速度",LVCFMT_LEFT,80,3);
	m_Grid.InsertColumn(4,"偏航角",LVCFMT_LEFT,80,4);
	m_Grid.InsertColumn(5,"高度",LVCFMT_LEFT,80,5);
	m_Grid.InsertColumn(6,"基本事件",LVCFMT_LEFT,110,6);

	m_rd.InsertString(0,"--------");
	m_rd.InsertString(1,"不变");
	m_rd.InsertString(2,"变大");
	m_rd.InsertString(3,"变小");
	m_rd.SetCurSel(0);
	
	m_speed.InsertString(0,"--------");
	m_speed.InsertString(1,"不变");
	m_speed.InsertString(2,"变大");
	m_speed.InsertString(3,"变小");
	m_speed.SetCurSel(0);
	
	m_addspeed.InsertString(0,"--------");
	m_addspeed.InsertString(1,"不变");
	m_addspeed.InsertString(2,"变大");
	m_addspeed.InsertString(3,"变小");
	m_addspeed.SetCurSel(0);
	
	m_azimuth.InsertString(0,"--------");
	m_azimuth.InsertString(1,"不变");
	m_azimuth.InsertString(2,"变大");
	m_azimuth.InsertString(3,"变小");
	m_azimuth.SetCurSel(0);
	
	m_high.InsertString(0,"--------");
	m_high.InsertString(1,"不变");
	m_high.InsertString(2,"变大");
	m_high.InsertString(3,"变小");
	m_high.SetCurSel(0);
	
	
	
	m_baseevent.InsertString(0,"匀速直线运动");
	m_baseevent.InsertString(1,"加速直线运动");
	m_baseevent.InsertString(2,"俯冲");
	m_baseevent.InsertString(3,"上升");
	m_baseevent.InsertString(4,"拐弯");
	m_baseevent.InsertString(5,"远离本舰");
	m_baseevent.InsertString(6,"逼近本舰");
	m_baseevent.InsertString(7,"位置固定");
	m_baseevent.SetCurSel(0);
	AddToGrid();
	
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogTRA::AddToGrid()
{
	//theApp.m_DataBase.pRst.CreateInstance(__uuidof(Recordset));
	theApp.m_DataBase.pRst=theApp.m_DataBase.pConn->Execute("select * from Track order by ID desc ",NULL,adCmdText);
	int rd,speed,addspeed,azimuth,high,baseevent;
	CString srd,sspeed,saddspeed,sazimuth,shigh,sbaseevent;
	while(!theApp.m_DataBase.pRst->adoEOF)
	{
		m_Grid.InsertItem(0,"");
		
		rd=atoi((_bstr_t)theApp.m_DataBase.pRst->GetCollect("Rd"));
		speed=atoi((_bstr_t)theApp.m_DataBase.pRst->GetCollect("Speed"));
		addspeed=atoi((_bstr_t)theApp.m_DataBase.pRst->GetCollect("AddSpeed"));
		azimuth=atoi((_bstr_t)theApp.m_DataBase.pRst->GetCollect("Azimuth"));
		high=atoi((_bstr_t)theApp.m_DataBase.pRst->GetCollect("High"));
		baseevent=atoi((_bstr_t)theApp.m_DataBase.pRst->GetCollect("BaseEvent"));
		//rd
		if(rd==0)
		{
			srd="--------";
		}
		if(rd==1)
		{
			srd="不变";
		}
		if(rd==3)
		{
			srd="变大";
		}
		if(rd==5)
		{
			srd="变小";
		}
		//speed
		if(speed==0)
		{
			sspeed="--------";
		}
		if(speed==1)
		{
			sspeed="不变";
		}
		if(speed==3)
		{
			sspeed="变大";
		}
		if(speed==5)
		{
			sspeed="变小";
		}
		//addspeed
		if(addspeed==0)
		{
			saddspeed="--------";
		}
		if(addspeed==1)
		{
			saddspeed="不变";
		}
		if(addspeed==3)
		{
			saddspeed="变大";
		}
		if(addspeed==5)
		{
			saddspeed="变小";
		}
		//azimuth
		if(azimuth==0)
		{
			sazimuth="--------";
		}
		if(azimuth==1)
		{
			sazimuth="不变";
		}
		if(azimuth==3)
		{
			sazimuth="变大";
		}
		if(azimuth==5)
		{
			sazimuth="变小";
		}
		//high
		if(high==0)
		{
			shigh="--------";
		}
		if(high==1)
		{
			shigh="不变";
		}
		if(high==3)
		{
			shigh="变大";
		}
		if(high==5)
		{
			shigh="变小";
		}
		//baseevent
		if(baseevent==1)
		{
			sbaseevent="匀速直线运动";
		}
		if(baseevent==2)
		{
			sbaseevent="加速直线运动";
		}
		if(baseevent==3)
		{
			sbaseevent="俯冲";
		}
		if(baseevent==4)
		{
			sbaseevent="上升";
		}
		if(baseevent==5)
		{
			sbaseevent="拐弯";
		}
		if(baseevent==6)
		{
			sbaseevent="远离本舰";
		}
		if(baseevent==7)
		{
			sbaseevent="逼近本舰";
		}
		if(baseevent==8)
		{
			sbaseevent="位置固定";
		}
		m_Grid.SetItemText(0,0,(_bstr_t)theApp.m_DataBase.pRst->GetCollect("ID"));
		m_Grid.SetItemText(0,1,srd);
		m_Grid.SetItemText(0,2,sspeed);
		m_Grid.SetItemText(0,3,saddspeed);
		m_Grid.SetItemText(0,4,sazimuth);
		m_Grid.SetItemText(0,5,shigh);
		m_Grid.SetItemText(0,6,sbaseevent);
		
		theApp.m_DataBase.pRst->MoveNext();
		
	}
	theApp.m_DataBase.pRst->Close();
}



//DEL void CDialogTRA::OnInitADOConn()
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

void CDialogTRA::OnButAdd() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//theApp.m_DataBase.pRst.CreateInstance(__uuidof(Recordset));
	theApp.m_DataBase.pRst->Open("select * from Track",theApp.m_DataBase.pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);

	CString srd,sspeed,saddspeed,sazimuth,shigh,sbaseevent;
	int rd,speed,addspeed,azimuth,high,baseevent;
	m_rd.GetLBText(m_rd.GetCurSel(),srd);
	m_speed.GetLBText(m_speed.GetCurSel(),sspeed);
	m_addspeed.GetLBText(m_addspeed.GetCurSel(),saddspeed);
	m_azimuth.GetLBText(m_azimuth.GetCurSel(),sazimuth);
	m_high.GetLBText(m_high.GetCurSel(),shigh);

	m_baseevent.GetLBText(m_baseevent.GetCurSel(),sbaseevent);
	//rd
	if(srd=="--------")
	{
		rd=0;
	}
	if(srd=="不变")
	{
		rd=1;
	}
	if(srd=="变大")
	{
		rd=3;
	}
	if(srd=="变小")
	{
		rd=5;
	}
//speed
	if(sspeed=="--------")
	{
		speed=0;
	}
	if(sspeed=="不变")
	{
		speed=1;
	}
	if(sspeed=="变大")
	{
		speed=3;
	}
	if(sspeed=="变小")
	{
		speed=5;
	}
//addspeed
	if(saddspeed=="--------")
	{
		addspeed=0;
	}
	if(saddspeed=="不变")
	{
		addspeed=1;
	}
	if(saddspeed=="变大")
	{
		addspeed=3;
	}
	if(saddspeed=="变小")
	{
		addspeed=5;
	}
//azimuth
	if(sazimuth=="--------")
	{
		azimuth=0;
	}
	if(sazimuth=="不变")
	{
		azimuth=1;
	}
	if(sazimuth=="变大")
	{
		azimuth=3;
	}
	if(sazimuth=="变小")
	{
		azimuth=5;
	}
	//high
	if(shigh=="--------")
	{
		high=0;
	}
	if(shigh=="不变")
	{
		high=1;
	}
	if(shigh=="变大")
	{
		high=3;
	}
	if(shigh=="变小")
	{
		high=5;
	}

	if(sbaseevent=="匀速直线运动")
	{
	  baseevent=1;
	}
	if(sbaseevent=="加速直线运动")
	{
		baseevent=2;
	}
	if(sbaseevent=="俯冲")
	{
		baseevent=3;
	}
	if(sbaseevent=="上升")
	{
		baseevent=4;
	}

	if(sbaseevent=="拐弯")
	{
		baseevent=5;
	}
	if(sbaseevent=="远离本舰")
	{
		baseevent=6;
	}
	if(sbaseevent=="逼近本舰")
	{
		baseevent=7;
	}
	if(sbaseevent=="位置固定")
	{
		baseevent=8;
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
			theApp.m_DataBase.pRst->PutCollect("Rd",(long)rd);
			theApp.m_DataBase.pRst->PutCollect("Speed",(long)speed);
			theApp.m_DataBase.pRst->PutCollect("AddSpeed",(long)addspeed);
			theApp.m_DataBase.pRst->PutCollect("Azimuth",(long)azimuth);
			theApp.m_DataBase.pRst->PutCollect("High",(long)high);

			theApp.m_DataBase.pRst->PutCollect("BaseEvent",(long)baseevent);
			theApp.m_DataBase.pRst->Update();
		}
	}
	catch(_com_error e)
	{
		MessageBox(e.Description());
	}

	theApp.m_DataBase.pRst->Close();

	m_Grid.DeleteAllItems();
	theApp.m_DataBase.GetTrackEvent();
	AddToGrid();
}

void CDialogTRA::OnButmod() 
{
	// TODO: Add your control notification handler code here
		UpdateData(TRUE);
	//rd
	int rd;
	CString srd;
	m_rd.GetLBText(m_rd.GetCurSel(),srd);
	if(srd=="--------")
	{
		rd=0;
	}
	if(srd=="不变")
	{
		rd=1;
	}
	if(srd=="变小")
	{
		rd=5;
	}
	if(srd=="变大")
	{
		rd=3;
	}

	//speed
	int speed;
	CString sspeed;
	m_speed.GetLBText(m_speed.GetCurSel(),sspeed);
	if(sspeed=="--------")
	{
		speed=0;
	}
	if(sspeed=="不变")
	{
		speed=1;
	}
	if(sspeed=="变小")
	{
		speed=5;
	}
	if(sspeed=="变大")
	{
		speed=3;
	}
//addspeed
	int addspeed;
	CString saddspeed;
	m_addspeed.GetLBText(m_addspeed.GetCurSel(),saddspeed);
	if(saddspeed=="--------")
	{
		addspeed=0;
	}
	if(saddspeed=="不变")
	{
		addspeed=1;
	}
	if(saddspeed=="变小")
	{
		addspeed=5;
	}
	if(saddspeed=="变大")
	{
		addspeed=3;
	}
//azimuth
	int azimuth;
	CString sazimuth;
	m_azimuth.GetLBText(m_azimuth.GetCurSel(),sazimuth);
	if(sazimuth=="--------")
	{
		azimuth=0;
	}
	if(sazimuth=="不变")
	{
		azimuth=1;
	}
	if(sazimuth=="变小")
	{
		azimuth=5;
	}
	if(sazimuth=="变大")
	{
		azimuth=3;
	}
	//high
	int high;
	CString shigh;
	m_high.GetLBText(m_high.GetCurSel(),shigh);
	if(shigh=="--------")
	{
		high=0;
	}
	if(shigh=="不变")
	{
		high=1;
	}
	if(shigh=="变小")
	{
		high=5;
	}
	if(shigh=="变大")
	{
		high=3;
	}
	//baseevent
	int baseevent;
	CString sbaseevent;
	m_baseevent.GetLBText(m_baseevent.GetCurSel(),sbaseevent);

	if(sbaseevent=="匀速直线运动")
	{
		baseevent=1;
	}
	if(sbaseevent=="加速直线运动")
	{
		baseevent=2;
	}
	if(sbaseevent=="俯冲")
	{
		baseevent=3;
	}	
	if(sbaseevent=="上升")
	{
		baseevent=4;
	}	
	if(sbaseevent=="拐弯")
	{
		baseevent=5;
	}	
	if(sbaseevent=="远离本舰")
	{
		baseevent=6;
	}
	if(sbaseevent=="逼近本舰")
	{
		baseevent=7;
	}
	if(sbaseevent=="位置固定")
	{
		baseevent=8;
	}
	CString sql;
	sql.Format("update Track set Rd=%d,Speed=%d,AddSpeed=%d,Azimuth=%d,High=%d,BaseEvent=%d where ID=%d",rd,speed,addspeed,azimuth,high,baseevent,ids);
	try
	{
		theApp.m_DataBase.pConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	m_Grid.DeleteAllItems();
	theApp.m_DataBase.GetTrackEvent();
	AddToGrid();
}

void CDialogTRA::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i;
	int pos=m_Grid.GetSelectionMark();
	//id
	m_id=m_Grid.GetItemText(pos,0);
	
	//rd
	CString rd=m_Grid.GetItemText(pos,1);
	m_rd.InsertString(4,rd);
	m_rd.SetCurSel(4);
	
	CString srd;
	for(i=0;;i++)
	{
		m_rd.GetLBText(i,srd);
		if(srd==rd)
		{
			m_rd.DeleteString(i);
			break;
		}
	}
	//speed
	CString speed=m_Grid.GetItemText(pos,2);
	m_speed.InsertString(4,speed);
	m_speed.SetCurSel(4);
	CString sspeed;
	for(i=0;;i++)
	{
		m_speed.GetLBText(i,sspeed);
		if(sspeed==speed)
		{
			m_speed.DeleteString(i);
			break;
		}
	}
	//addspeed
	CString addspeed=m_Grid.GetItemText(pos,3);
	m_addspeed.InsertString(4,addspeed);
	m_addspeed.SetCurSel(4);
	CString saddspeed;
	for(i=0;;i++)
	{
		m_addspeed.GetLBText(i,saddspeed);
		if(saddspeed==addspeed)
		{
			m_addspeed.DeleteString(i);
			break;
		}
	}
	//azimuth
	CString azimuth=m_Grid.GetItemText(pos,4);
	m_azimuth.InsertString(4,azimuth);
	m_azimuth.SetCurSel(4);
	CString sazimuth;
	for(i=0;;i++)
	{
		m_azimuth.GetLBText(i,sazimuth);
		if(sazimuth==azimuth)
		{
			m_azimuth.DeleteString(i);
			break;
		}
	}
//high
	CString high=m_Grid.GetItemText(pos,5);
	m_high.InsertString(4,high);
	m_high.SetCurSel(4);
	CString shigh;
	for(i=0;;i++)
	{
		m_high.GetLBText(i,shigh);
		if(shigh==high)
		{
			m_high.DeleteString(i);
			break;
		}
	}
	//BaseEvent
	CString baseevent=m_Grid.GetItemText(pos,6);
	m_baseevent.InsertString(8,baseevent);
	m_baseevent.SetCurSel(8);
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

void CDialogTRA::OnButdel() 
{
	// TODO: Add your control notification handler code here
	int id=atoi(m_id);	
	CString sql;
	sql.Format("delete from Track where ID=%d",id);
	try
	{
		theApp.m_DataBase.pConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	m_Grid.DeleteAllItems();
	theApp.m_DataBase.GetTrackEvent();
	AddToGrid();	
	
}
