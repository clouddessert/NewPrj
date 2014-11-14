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
    m_Grid.InsertColumn(0,"֪ʶ���",LVCFMT_LEFT,80,0);
	m_Grid.InsertColumn(1,"����",LVCFMT_LEFT,80,1);
	m_Grid.InsertColumn(2,"�ٶ�",LVCFMT_LEFT,80,2);
	m_Grid.InsertColumn(3,"���ٶ�",LVCFMT_LEFT,80,3);
	m_Grid.InsertColumn(4,"ƫ����",LVCFMT_LEFT,80,4);
	m_Grid.InsertColumn(5,"�߶�",LVCFMT_LEFT,80,5);
	m_Grid.InsertColumn(6,"�����¼�",LVCFMT_LEFT,110,6);

	m_rd.InsertString(0,"--------");
	m_rd.InsertString(1,"����");
	m_rd.InsertString(2,"���");
	m_rd.InsertString(3,"��С");
	m_rd.SetCurSel(0);
	
	m_speed.InsertString(0,"--------");
	m_speed.InsertString(1,"����");
	m_speed.InsertString(2,"���");
	m_speed.InsertString(3,"��С");
	m_speed.SetCurSel(0);
	
	m_addspeed.InsertString(0,"--------");
	m_addspeed.InsertString(1,"����");
	m_addspeed.InsertString(2,"���");
	m_addspeed.InsertString(3,"��С");
	m_addspeed.SetCurSel(0);
	
	m_azimuth.InsertString(0,"--------");
	m_azimuth.InsertString(1,"����");
	m_azimuth.InsertString(2,"���");
	m_azimuth.InsertString(3,"��С");
	m_azimuth.SetCurSel(0);
	
	m_high.InsertString(0,"--------");
	m_high.InsertString(1,"����");
	m_high.InsertString(2,"���");
	m_high.InsertString(3,"��С");
	m_high.SetCurSel(0);
	
	
	
	m_baseevent.InsertString(0,"����ֱ���˶�");
	m_baseevent.InsertString(1,"����ֱ���˶�");
	m_baseevent.InsertString(2,"����");
	m_baseevent.InsertString(3,"����");
	m_baseevent.InsertString(4,"����");
	m_baseevent.InsertString(5,"Զ�뱾��");
	m_baseevent.InsertString(6,"�ƽ�����");
	m_baseevent.InsertString(7,"λ�ù̶�");
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
			srd="����";
		}
		if(rd==3)
		{
			srd="���";
		}
		if(rd==5)
		{
			srd="��С";
		}
		//speed
		if(speed==0)
		{
			sspeed="--------";
		}
		if(speed==1)
		{
			sspeed="����";
		}
		if(speed==3)
		{
			sspeed="���";
		}
		if(speed==5)
		{
			sspeed="��С";
		}
		//addspeed
		if(addspeed==0)
		{
			saddspeed="--------";
		}
		if(addspeed==1)
		{
			saddspeed="����";
		}
		if(addspeed==3)
		{
			saddspeed="���";
		}
		if(addspeed==5)
		{
			saddspeed="��С";
		}
		//azimuth
		if(azimuth==0)
		{
			sazimuth="--------";
		}
		if(azimuth==1)
		{
			sazimuth="����";
		}
		if(azimuth==3)
		{
			sazimuth="���";
		}
		if(azimuth==5)
		{
			sazimuth="��С";
		}
		//high
		if(high==0)
		{
			shigh="--------";
		}
		if(high==1)
		{
			shigh="����";
		}
		if(high==3)
		{
			shigh="���";
		}
		if(high==5)
		{
			shigh="��С";
		}
		//baseevent
		if(baseevent==1)
		{
			sbaseevent="����ֱ���˶�";
		}
		if(baseevent==2)
		{
			sbaseevent="����ֱ���˶�";
		}
		if(baseevent==3)
		{
			sbaseevent="����";
		}
		if(baseevent==4)
		{
			sbaseevent="����";
		}
		if(baseevent==5)
		{
			sbaseevent="����";
		}
		if(baseevent==6)
		{
			sbaseevent="Զ�뱾��";
		}
		if(baseevent==7)
		{
			sbaseevent="�ƽ�����";
		}
		if(baseevent==8)
		{
			sbaseevent="λ�ù̶�";
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
	if(srd=="����")
	{
		rd=1;
	}
	if(srd=="���")
	{
		rd=3;
	}
	if(srd=="��С")
	{
		rd=5;
	}
//speed
	if(sspeed=="--------")
	{
		speed=0;
	}
	if(sspeed=="����")
	{
		speed=1;
	}
	if(sspeed=="���")
	{
		speed=3;
	}
	if(sspeed=="��С")
	{
		speed=5;
	}
//addspeed
	if(saddspeed=="--------")
	{
		addspeed=0;
	}
	if(saddspeed=="����")
	{
		addspeed=1;
	}
	if(saddspeed=="���")
	{
		addspeed=3;
	}
	if(saddspeed=="��С")
	{
		addspeed=5;
	}
//azimuth
	if(sazimuth=="--------")
	{
		azimuth=0;
	}
	if(sazimuth=="����")
	{
		azimuth=1;
	}
	if(sazimuth=="���")
	{
		azimuth=3;
	}
	if(sazimuth=="��С")
	{
		azimuth=5;
	}
	//high
	if(shigh=="--------")
	{
		high=0;
	}
	if(shigh=="����")
	{
		high=1;
	}
	if(shigh=="���")
	{
		high=3;
	}
	if(shigh=="��С")
	{
		high=5;
	}

	if(sbaseevent=="����ֱ���˶�")
	{
	  baseevent=1;
	}
	if(sbaseevent=="����ֱ���˶�")
	{
		baseevent=2;
	}
	if(sbaseevent=="����")
	{
		baseevent=3;
	}
	if(sbaseevent=="����")
	{
		baseevent=4;
	}

	if(sbaseevent=="����")
	{
		baseevent=5;
	}
	if(sbaseevent=="Զ�뱾��")
	{
		baseevent=6;
	}
	if(sbaseevent=="�ƽ�����")
	{
		baseevent=7;
	}
	if(sbaseevent=="λ�ù̶�")
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
			MessageBox("ID���ظ������������!");
		}
		theApp.m_DataBase.pRst->MoveNext();
	}
	//�˴��ɲ����жϣ������ݿ�����Ψһ���ж�
	try
	{
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
	if(srd=="����")
	{
		rd=1;
	}
	if(srd=="��С")
	{
		rd=5;
	}
	if(srd=="���")
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
	if(sspeed=="����")
	{
		speed=1;
	}
	if(sspeed=="��С")
	{
		speed=5;
	}
	if(sspeed=="���")
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
	if(saddspeed=="����")
	{
		addspeed=1;
	}
	if(saddspeed=="��С")
	{
		addspeed=5;
	}
	if(saddspeed=="���")
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
	if(sazimuth=="����")
	{
		azimuth=1;
	}
	if(sazimuth=="��С")
	{
		azimuth=5;
	}
	if(sazimuth=="���")
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
	if(shigh=="����")
	{
		high=1;
	}
	if(shigh=="��С")
	{
		high=5;
	}
	if(shigh=="���")
	{
		high=3;
	}
	//baseevent
	int baseevent;
	CString sbaseevent;
	m_baseevent.GetLBText(m_baseevent.GetCurSel(),sbaseevent);

	if(sbaseevent=="����ֱ���˶�")
	{
		baseevent=1;
	}
	if(sbaseevent=="����ֱ���˶�")
	{
		baseevent=2;
	}
	if(sbaseevent=="����")
	{
		baseevent=3;
	}	
	if(sbaseevent=="����")
	{
		baseevent=4;
	}	
	if(sbaseevent=="����")
	{
		baseevent=5;
	}	
	if(sbaseevent=="Զ�뱾��")
	{
		baseevent=6;
	}
	if(sbaseevent=="�ƽ�����")
	{
		baseevent=7;
	}
	if(sbaseevent=="λ�ù̶�")
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
