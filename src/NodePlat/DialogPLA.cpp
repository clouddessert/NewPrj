// DialogPLA.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "DialogPLA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogPLA dialog


CDialogPLA::CDialogPLA(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogPLA::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogPLA)
	m_id = _T("");
	//}}AFX_DATA_INIT
}


void CDialogPLA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogPLA)
	DDX_Control(pDX, IDC_COMBO8, m_high);
	DDX_Control(pDX, IDC_COMBO9, m_addspeed);
	DDX_Control(pDX, IDC_COMBO7, m_speed);
	DDX_Control(pDX, IDC_COMBO10, m_azimuth);
	DDX_Control(pDX, IDC_COMBO6, m_rd);
	DDX_Control(pDX, IDC_COMBO2, m_gog);
	DDX_Control(pDX, IDC_COMBO5, m_pla);
	DDX_Control(pDX, IDC_COMBO4, m_com);
	DDX_Control(pDX, IDC_COMBO3, m_esm);
	DDX_Control(pDX, IDC_COMBO1, m_tra);
	DDX_Control(pDX, IDC_LIST1, m_Grid);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogPLA, CDialog)
	//{{AFX_MSG_MAP(CDialogPLA)
	ON_BN_CLICKED(IDC_BUT_ADD, OnButadd)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_BN_CLICKED(IDC_BUTMOD, OnButmod)
	ON_BN_CLICKED(IDC_BUT_DEL, OnButdel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogPLA message handlers

BOOL CDialogPLA::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Grid.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
	m_Grid.InsertColumn(0,"֪ʶ���",LVCFMT_LEFT,80,0);
	m_Grid.InsertColumn(1,"���������¼�",LVCFMT_LEFT,130,1);
	m_Grid.InsertColumn(2,"����",LVCFMT_LEFT,80,2);
	m_Grid.InsertColumn(3,"�߶�",LVCFMT_LEFT,80,3);
	m_Grid.InsertColumn(4,"�ٶ�",LVCFMT_LEFT,80,4);
	m_Grid.InsertColumn(5,"���ٶ�",LVCFMT_LEFT,80,5);
	m_Grid.InsertColumn(6,"ƫ����",LVCFMT_LEFT,80,6);
	m_Grid.InsertColumn(7,"ESM�����¼�",LVCFMT_LEFT,120,7);
	m_Grid.InsertColumn(8,"COM�����¼�",LVCFMT_LEFT,120,8);
	m_Grid.InsertColumn(9,"Ŀ������",LVCFMT_LEFT,150,9);
	m_Grid.InsertColumn(10,"ƽ̨̬��",LVCFMT_LEFT,120,10);

	
	AddToGrid();
	//trabaseevent
	m_tra.InsertString(0,"--------");
	m_tra.InsertString(1,"����ֱ���˶�");
	m_tra.InsertString(2,"����ֱ���˶�");
	m_tra.InsertString(3,"����");
	m_tra.InsertString(4,"����");
	m_tra.InsertString(5,"����");
	m_tra.InsertString(6,"Զ�뱾��");
	m_tra.InsertString(7,"�ƽ�����");
	m_tra.InsertString(8,"λ�ù̶�");
	m_tra.SetCurSel(0);
	//rd
	m_rd.InsertString(0,"--------");
	m_rd.InsertString(1,"����");
	m_rd.InsertString(2,"��С");
	m_rd.InsertString(3,"���");
	m_rd.SetCurSel(0);
	//high
	m_high.InsertString(0,"--------");
	m_high.InsertString(1,"����");
	m_high.InsertString(2,"��С");
	m_high.InsertString(3,"���");
	m_high.SetCurSel(0);
	//speed
	m_speed.InsertString(0,"--------");
	m_speed.InsertString(1,"����");
	m_speed.InsertString(2,"��С");
	m_speed.InsertString(3,"���");
	m_speed.SetCurSel(0);
	//addspeed
	m_addspeed.InsertString(0,"--------");
	m_addspeed.InsertString(1,"����");
	m_addspeed.InsertString(2,"��С");
	m_addspeed.InsertString(3,"���");
	m_addspeed.SetCurSel(0);
	//azimuth
	m_azimuth.InsertString(0,"--------");
	m_azimuth.InsertString(1,"����");
	m_azimuth.InsertString(2,"��С");
	m_azimuth.InsertString(3,"���");
	m_azimuth.SetCurSel(0);
	//gogal
	m_gog.InsertString(0,"--------");
	m_gog.InsertString(1,"ս����");
	m_gog.InsertString(2,"��ը��");
	m_gog.InsertString(3,"�߻�����������");
	m_gog.InsertString(4,"Ԥ����");
	m_gog.InsertString(5,"����");
	m_gog.InsertString(6,"���Ż�");
	m_gog.InsertString(7,"ֱ����");
	m_gog.InsertString(8,"��ͧ");
	m_gog.InsertString(9,"ս������");
	m_gog.InsertString(10,"�Ƶ�����");
    m_gog.SetCurSel(0);
	//esmbaseevent
	m_esm.InsertString(0,"--------");
	m_esm.InsertString(1,"����");
	m_esm.InsertString(2,"����");
	m_esm.InsertString(3,"����");
	m_esm.InsertString(4,"�������");
	m_esm.SetCurSel(0);
	//combaseevent
	m_com.InsertString(0,"--------");
	m_com.InsertString(1,"����");
	m_com.InsertString(2,"ָ��");
    m_com.SetCurSel(0);
	
	//plat
	m_pla.InsertString(0,"--------");
	m_pla.InsertString(1,"����");
	m_pla.InsertString(2,"Ѳ��");
	m_pla.InsertString(3,"����");
	m_pla.InsertString(4,"����");
	m_pla.InsertString(5,"��ը");
	m_pla.InsertString(6,"ͻ��");
	m_pla.InsertString(7,"����");
	m_pla.InsertString(8,"Ԥ��ָ��");
	m_pla.InsertString(9,"����");
    m_pla.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDialogPLA::AddToGrid()
{
	ado.OnInitADOConn();
	ado.pRst.CreateInstance(__uuidof(Recordset));
	ado.pRst=ado.pConn->Execute("select * from ƽ̨̬�� order by ID desc ",NULL,adCmdText);
//	int uniform,accele,dive,rose,turn,away,approach,fix,search,track,interference,guide,contact,command;
//	CString suniform,saccele,sdive,srose,sturn,saway,sapproach,sfix,ssearch,strack,sinterference,sguide,scontact,scommand;

	int trackbaseevent=0;
	int rd=0;
	int high=0;
	int speed=0;
	int addspeed=0;
	int azimuth=0;
	int esmbaseevent=0;
	int combaseevent=0;
	int gogal=0;
	int plat=0;

	CString strackbaseevent,srd,shigh,sspeed,saddspeed,sazimuth,sesmbaseevent,scombaseevent,sgogal,splat;
	while(!ado.pRst->adoEOF)
	{
		m_Grid.InsertItem(0,"");
	
		trackbaseevent=atoi((_bstr_t)ado.pRst->GetCollect("Track�����¼�"));
		rd=atoi((_bstr_t)ado.pRst->GetCollect("Rd"));
		high=atoi((_bstr_t)ado.pRst->GetCollect("High"));
		speed=atoi((_bstr_t)ado.pRst->GetCollect("Speed"));
		addspeed=atoi((_bstr_t)ado.pRst->GetCollect("AddSpeed"));
		azimuth=atoi((_bstr_t)ado.pRst->GetCollect("Azimuth"));
		esmbaseevent=atoi((_bstr_t)ado.pRst->GetCollect("ESM�����¼�"));
		combaseevent=atoi((_bstr_t)ado.pRst->GetCollect("COM�����¼�"));
		gogal=atoi((_bstr_t)ado.pRst->GetCollect("Ŀ������"));
		plat=atoi((_bstr_t)ado.pRst->GetCollect("ƽ̨̬��"));
		//trackbaseevent
		if(trackbaseevent==0)
		{
			strackbaseevent="--------";
		}
		if(trackbaseevent==1)
		{
			strackbaseevent="����ֱ���˶�";
		}
		if(trackbaseevent==2)
		{
			strackbaseevent="����ֱ���˶�";
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
			strackbaseevent="����";
		}
		if(trackbaseevent==6)
		{
			strackbaseevent="Զ�뱾��";
		}
		if(trackbaseevent==7)
		{
			strackbaseevent="�ƽ�����";
		}
		if(trackbaseevent==8)
		{
			strackbaseevent="λ�ù̶�";
		}
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
		//esmbaseevent
		if(esmbaseevent==0)
		{
			sesmbaseevent="--------";
		}
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
		//combaseevent
		if(combaseevent==0)
		{
			scombaseevent="--------";
		}
		if(combaseevent==1)
		{
			scombaseevent="����";
		}
		if(combaseevent==2)
		{
			scombaseevent="ָ��";
		}

	//
		if(gogal==0)
		{
			sgogal="--------";
		}
		if(gogal==1)
		{
			sgogal="ս����";
		}
		if(gogal==2)
		{
			sgogal="��ը��";
		}
		if(gogal==3)
		{
			sgogal="�߻�����������";
		}
		if(gogal==4)
		{
			sgogal="Ԥ����";
		}
		if(gogal==5)
		{
			sgogal="����";
		}
		if(gogal==6)
		{
			sgogal="���Ż�";
		}
		if(gogal==7)
		{
		    sgogal="ֱ����";

		}
		if(gogal==8)
		{
			sgogal="��ͧ";
		}
		if(gogal==9)
		{
			sgogal="ս������";
		}
		if(gogal==10)
		{
			sgogal="�Ƶ�����";
		}

		//
		if(plat==0)
		{
			splat="--------";
		}
		if(plat==1)
		{
			splat="����";
		}
		if(plat==2)
		{
			splat="Ѳ��";
		}
		if(plat==3)
		{
			splat="����";
		}
		if(plat==4)
		{
			splat="����";
		}
		if(plat==5)
		{
			splat="��ը";
		}
		if(plat==6)
		{
			splat="ͻ��";
		}
		if(plat==7)
		{
			splat="����";
		}
		if(plat==8)
		{
			splat="Ԥ��ָ��";
		}
		if(plat==9)
		{
			splat="����";
		}
		

		m_Grid.SetItemText(0,0,(_bstr_t)ado.pRst->GetCollect("ID"));
		m_Grid.SetItemText(0,1,strackbaseevent);
		m_Grid.SetItemText(0,2,srd);
		m_Grid.SetItemText(0,3,shigh);
		m_Grid.SetItemText(0,4,sspeed);
		m_Grid.SetItemText(0,5,saddspeed);
		m_Grid.SetItemText(0,6,sazimuth);
		m_Grid.SetItemText(0,7,sesmbaseevent);
		m_Grid.SetItemText(0,8,scombaseevent);
		m_Grid.SetItemText(0,9,sgogal);
		m_Grid.SetItemText(0,10,splat);
		
		
		ado.pRst->MoveNext();
		
	}
	ado.ExitConnect();
}



void CDialogPLA::OnButadd() 
{
	// TODO: Add your control notification handler code here
			UpdateData(TRUE);
	ado.OnInitADOConn();
	ado.pRst.CreateInstance(__uuidof(Recordset));
	ado.pRst->Open("select * from ƽ̨̬��",ado.pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);

	int trackbaseevent=0;
	int rd=0;
	int high=0;
	int speed=0;
	int addspeed=0;
	int azimuth=0;
	int esmbaseevent=0;
	int combaseevent=0;
	int gogal=0;
	int plat=0;
	CString strackbaseevent,srd,shigh,sspeed,saddspeed,sazimuth,sesmbaseevent,scombaseevent,sgogal,splat;
	m_tra.GetLBText(m_tra.GetCurSel(),strackbaseevent);
	m_rd.GetLBText(m_rd.GetCurSel(),srd);
	m_speed.GetLBText(m_speed.GetCurSel(),sspeed);
	m_addspeed.GetLBText(m_addspeed.GetCurSel(),saddspeed);
	m_azimuth.GetLBText(m_azimuth.GetCurSel(),sazimuth);
	m_high.GetLBText(m_high.GetCurSel(),shigh);
	m_gog.GetLBText(m_gog.GetCurSel(),sgogal);
	m_esm.GetLBText(m_esm.GetCurSel(),sesmbaseevent);
	m_com.GetLBText(m_com.GetCurSel(),scombaseevent);
	m_pla.GetLBText(m_pla.GetCurSel(),splat);

	//trackbaseevent
	if(strackbaseevent=="����ֱ���˶�")
	{
		trackbaseevent=1;
	}
	if(strackbaseevent=="����ֱ���˶�")
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
	if(strackbaseevent=="����")
	{
		trackbaseevent=5;
	}
	if(strackbaseevent=="Զ�뱾��")
	{
		trackbaseevent=6;
	}
	if(strackbaseevent=="�ƽ�����")
	{
		trackbaseevent=7;
	}
	if(strackbaseevent=="λ�ù̶�")
	{
		trackbaseevent=8;
	}
	if(strackbaseevent=="--------")
	{
		trackbaseevent=0;
	}
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
//gogal
	if(sgogal=="ս����")
	{
		gogal=1;
	}
	if(sgogal=="��ը��")
	{
		gogal=2;
	}
	if(sgogal=="�߻�����������")
	{
		gogal=3;
	}
	if(sgogal=="Ԥ����")
	{
		gogal=4;
	}
	if(sgogal=="����")
	{
		gogal=5;
	}
	if(sgogal=="���Ż�")
	{
		gogal=6;
	}
	if(sgogal=="ֱ����")
	{
		gogal=7;
	}
	if(sgogal=="��ͧ")
	{
		gogal=8;
	}
	if(sgogal=="ս������")
	{
		gogal=9;
	}
	if(sgogal=="�Ƶ�����")
	{
		gogal=10;
	}
	if(sgogal=="--------")
	{
		gogal=0;
	}
//esmbaseevent
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
	if(sesmbaseevent=="--------")
	{
		esmbaseevent=0;
	}
//combaseevent
	if(scombaseevent=="����")
	{
		combaseevent=1;
	}
	if(scombaseevent=="ָ��")
	{
		combaseevent=2;
	}

	
	if(scombaseevent=="--------")
	{
		combaseevent=0;
	}
//plat
	if(splat=="--------")
	{
		plat=0;
	}
	if(splat=="����")
	{
		plat=1;
	}

	if(splat=="Ѳ��")
	{
		plat=2;
	}

	if(splat=="����")
	{
		plat=3;
	}

	if(splat=="����")
	{
		plat=4;
	}

	if(splat=="��ը")
	{
		plat=5;
	}

	if(splat=="ͻ��")
	{
		plat=6;
	}

	if(splat=="����")
	{
		plat=7;
	}

	if(splat=="Ԥ��ָ��")
	{
		plat=8;
	}

	if(splat=="����")
	{
		plat=9;
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
	//�˴��ɲ����жϣ������ݿ�����Ψһ���ж�
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
	ado.pRst->PutCollect("Track�����¼�",(long)trackbaseevent);
	ado.pRst->PutCollect("Rd",(long)rd);
	ado.pRst->PutCollect("Speed",(long)speed);
	ado.pRst->PutCollect("AddSpeed",(long)addspeed);
	ado.pRst->PutCollect("Azimuth",(long)azimuth);
	ado.pRst->PutCollect("High",(long)high);
	ado.pRst->PutCollect("ESM�����¼�",(long)esmbaseevent);
	ado.pRst->PutCollect("COM�����¼�",(long)combaseevent);
	ado.pRst->PutCollect("Ŀ������",(long)gogal);
	ado.pRst->PutCollect("ƽ̨̬��",(long)plat);
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

void CDialogPLA::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i;
	int pos=m_Grid.GetSelectionMark();
	//id
	m_id=m_Grid.GetItemText(pos,0);
	
	//trackbaseevent
	CString trackbaseevent=m_Grid.GetItemText(pos,1);
	m_tra.InsertString(9,trackbaseevent);
	m_tra.SetCurSel(9);
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

	//rd
	CString rd=m_Grid.GetItemText(pos,2);
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
	//high
	CString high=m_Grid.GetItemText(pos,3);
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
	//speed
	CString speed=m_Grid.GetItemText(pos,4);
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
	CString addspeed=m_Grid.GetItemText(pos,5);
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
	CString azimuth=m_Grid.GetItemText(pos,6);
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


	//esmbaseevent
	CString esmbaseevent=m_Grid.GetItemText(pos,7);
	m_esm.InsertString(5,esmbaseevent);
	m_esm.SetCurSel(5);
	CString sesmbaseevent;
	for(i=0;;i++)
	{
		m_esm.GetLBText(i,sesmbaseevent);
		if(sesmbaseevent==esmbaseevent)
		{
			m_esm.DeleteString(i);
			break;
		}
	}

	//combaseevent
  CString combaseevent=m_Grid.GetItemText(pos,8);
  m_com.InsertString(3,combaseevent);
  m_com.SetCurSel(3);
  CString scombaseevent;
  for(i=0;;i++)
  {
	  m_com.GetLBText(i,scombaseevent);
	  if(scombaseevent==combaseevent)
	  {
		  m_com.DeleteString(i);
		  break;
	  }
  }
  //gogal
  CString gogal=m_Grid.GetItemText(pos,9);
  m_gog.InsertString(11,gogal);
  m_gog.SetCurSel(11);
  CString sgogal;
  for(i=0;;i++)
  {
	  m_gog.GetLBText(i,sgogal);
	  if(sgogal==gogal)
	  {
		  m_gog.DeleteString(i);
		  break;
	  }
  }

	//plat

  CString plat=m_Grid.GetItemText(pos,10);
  m_pla.InsertString(10,plat);
  m_pla.SetCurSel(10);
  CString splat;
  for(i=0;;i++)
  {
	  m_pla.GetLBText(i,splat);
	  if(splat==plat)
	  {
		  m_pla.DeleteString(i);
		  break;
	  }
  }
	ids=atoi(m_id);
	UpdateData(FALSE);
	*pResult = 0;
}

void CDialogPLA::OnButmod() 
{
	// TODO: Add your control notification handler code here
		UpdateData(TRUE);
	//trackbaseevent
	int trackbaseevent;
	CString strackbaseevent;
	m_tra.GetLBText(m_tra.GetCurSel(),strackbaseevent);
	if(strackbaseevent=="����ֱ���˶�")
	{
		trackbaseevent=1;
	}
	if(strackbaseevent=="����ֱ���˶�")
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
	if(strackbaseevent=="����")
	{
		trackbaseevent=5;
	}
	if(strackbaseevent=="Զ�뱾��")
	{
		trackbaseevent=6;
	}
	if(strackbaseevent=="�ƽ�����")
	{
		trackbaseevent=7;
	}
	if(strackbaseevent=="λ�ù̶�")
	{
		trackbaseevent=8;
	}
	if(strackbaseevent=="--------")
	{
		trackbaseevent=0;
	}
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
	//gogal
	int gogal;
	CString sgogal;
	m_gog.GetLBText(m_gog.GetCurSel(),sgogal);
	if(sgogal=="ս����")
	{
		gogal=1;
	}
	if(sgogal=="��ը��")
	{
		gogal=2;
	}
	if(sgogal=="�߻�����������")
	{
		gogal=3;
	}
	if(sgogal=="Ԥ����")
	{
		gogal=4;
	}
	if(sgogal=="����")
	{
		gogal=5;
	}
	if(sgogal=="���Ż�")
	{
		gogal=6;
	}
	if(sgogal=="ֱ����")
	{
		gogal=7;
	}
	if(sgogal=="��ͧ")
	{
		gogal=8;
	}
	if(sgogal=="ս������")
	{
		gogal=9;
	}
	if(sgogal=="�Ƶ�����")
	{
		gogal=10;
	}
	if(sgogal=="--------")
	{
		gogal=0;
	}
//esmbaseevent
	int esmbaseevent;
	CString sesmbaseevent;
	m_esm.GetLBText(m_esm.GetCurSel(),sesmbaseevent);
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
	if(sesmbaseevent=="--------")
	{
		esmbaseevent=0;
	}
	//combaseevent
	int combaseevent;
	CString scombaseevent;
	m_com.GetLBText(m_com.GetCurSel(),scombaseevent);
	if(scombaseevent=="����")
	{
		combaseevent=1;
	}
	if(scombaseevent=="ָ��")
	{
		combaseevent=2;
	}
	
	
	if(scombaseevent=="--------")
	{
		combaseevent=0;
	}
	//plat
	int plat;
	CString splat;
	m_pla.GetLBText(m_pla.GetCurSel(),splat);
	if(splat=="--------")
	{
		plat=0;
	}
	if(splat=="����")
	{
		plat=1;
	}
	
	if(splat=="Ѳ��")
	{
		plat=2;
	}
	
	if(splat=="����")
	{
		plat=3;
	}
	
	if(splat=="����")
	{
		plat=4;
	}
	
	if(splat=="��ը")
	{
		plat=5;
	}
	
	if(splat=="ͻ��")
	{
		plat=6;
	}
	
	if(splat=="����")
	{
		plat=7;
	}
	
	if(splat=="Ԥ��ָ��")
	{
		plat=8;
	}
	
	if(splat=="����")
	{
		plat=9;
	}
	
	ado.OnInitADOConn();
	CString sql;
	sql.Format("update ƽ̨̬�� set Track�����¼�=%d,Rd=%d,High=%d,Speed=%d,AddSpeed=%d,Azimuth=%d,ESM�����¼�=%d,COM�����¼�=%d,Ŀ������=%d,ƽ̨̬��=%d where ID=%d",trackbaseevent,rd,high,speed,addspeed,azimuth,esmbaseevent,combaseevent,gogal,plat,ids);
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

void CDialogPLA::OnButdel() 
{
	// TODO: Add your control notification handler code here
	int id=atoi(m_id);	
	ado.OnInitADOConn();
	CString sql;
	sql.Format("delete from ƽ̨̬�� where ID=%d",id);
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
