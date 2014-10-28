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
	m_Grid.InsertColumn(0,"知识序号",LVCFMT_LEFT,80,0);
	m_Grid.InsertColumn(1,"航迹基本事件",LVCFMT_LEFT,130,1);
	m_Grid.InsertColumn(2,"径距",LVCFMT_LEFT,80,2);
	m_Grid.InsertColumn(3,"高度",LVCFMT_LEFT,80,3);
	m_Grid.InsertColumn(4,"速度",LVCFMT_LEFT,80,4);
	m_Grid.InsertColumn(5,"加速度",LVCFMT_LEFT,80,5);
	m_Grid.InsertColumn(6,"偏航角",LVCFMT_LEFT,80,6);
	m_Grid.InsertColumn(7,"ESM基本事件",LVCFMT_LEFT,120,7);
	m_Grid.InsertColumn(8,"COM基本事件",LVCFMT_LEFT,120,8);
	m_Grid.InsertColumn(9,"目标类型",LVCFMT_LEFT,150,9);
	m_Grid.InsertColumn(10,"平台态势",LVCFMT_LEFT,120,10);

	
	AddToGrid();
	//trabaseevent
	m_tra.InsertString(0,"--------");
	m_tra.InsertString(1,"匀速直线运动");
	m_tra.InsertString(2,"加速直线运动");
	m_tra.InsertString(3,"俯冲");
	m_tra.InsertString(4,"上升");
	m_tra.InsertString(5,"拐弯");
	m_tra.InsertString(6,"远离本舰");
	m_tra.InsertString(7,"逼近本舰");
	m_tra.InsertString(8,"位置固定");
	m_tra.SetCurSel(0);
	//rd
	m_rd.InsertString(0,"--------");
	m_rd.InsertString(1,"不变");
	m_rd.InsertString(2,"变小");
	m_rd.InsertString(3,"变大");
	m_rd.SetCurSel(0);
	//high
	m_high.InsertString(0,"--------");
	m_high.InsertString(1,"不变");
	m_high.InsertString(2,"变小");
	m_high.InsertString(3,"变大");
	m_high.SetCurSel(0);
	//speed
	m_speed.InsertString(0,"--------");
	m_speed.InsertString(1,"不变");
	m_speed.InsertString(2,"变小");
	m_speed.InsertString(3,"变大");
	m_speed.SetCurSel(0);
	//addspeed
	m_addspeed.InsertString(0,"--------");
	m_addspeed.InsertString(1,"不变");
	m_addspeed.InsertString(2,"变小");
	m_addspeed.InsertString(3,"变大");
	m_addspeed.SetCurSel(0);
	//azimuth
	m_azimuth.InsertString(0,"--------");
	m_azimuth.InsertString(1,"不变");
	m_azimuth.InsertString(2,"变小");
	m_azimuth.InsertString(3,"变大");
	m_azimuth.SetCurSel(0);
	//gogal
	m_gog.InsertString(0,"--------");
	m_gog.InsertString(1,"战斗机");
	m_gog.InsertString(2,"轰炸机");
	m_gog.InsertString(3,"歼击机、攻击机");
	m_gog.InsertString(4,"预警机");
	m_gog.InsertString(5,"侦察机");
	m_gog.InsertString(6,"干扰机");
	m_gog.InsertString(7,"直升机");
	m_gog.InsertString(8,"舰艇");
	m_gog.InsertString(9,"战术导弹");
	m_gog.InsertString(10,"制导武器");
    m_gog.SetCurSel(0);
	//esmbaseevent
	m_esm.InsertString(0,"--------");
	m_esm.InsertString(1,"搜索");
	m_esm.InsertString(2,"跟踪");
	m_esm.InsertString(3,"干扰");
	m_esm.InsertString(4,"火控引导");
	m_esm.SetCurSel(0);
	//combaseevent
	m_com.InsertString(0,"--------");
	m_com.InsertString(1,"联络");
	m_com.InsertString(2,"指挥");
    m_com.SetCurSel(0);
	
	//plat
	m_pla.InsertString(0,"--------");
	m_pla.InsertString(1,"警戒");
	m_pla.InsertString(2,"巡逻");
	m_pla.InsertString(3,"拦截");
	m_pla.InsertString(4,"攻击");
	m_pla.InsertString(5,"轰炸");
	m_pla.InsertString(6,"突防");
	m_pla.InsertString(7,"干扰");
	m_pla.InsertString(8,"预警指挥");
	m_pla.InsertString(9,"不明");
    m_pla.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDialogPLA::AddToGrid()
{
	ado.OnInitADOConn();
	ado.pRst.CreateInstance(__uuidof(Recordset));
	ado.pRst=ado.pConn->Execute("select * from 平台态势 order by ID desc ",NULL,adCmdText);
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
	
		trackbaseevent=atoi((_bstr_t)ado.pRst->GetCollect("Track基本事件"));
		rd=atoi((_bstr_t)ado.pRst->GetCollect("Rd"));
		high=atoi((_bstr_t)ado.pRst->GetCollect("High"));
		speed=atoi((_bstr_t)ado.pRst->GetCollect("Speed"));
		addspeed=atoi((_bstr_t)ado.pRst->GetCollect("AddSpeed"));
		azimuth=atoi((_bstr_t)ado.pRst->GetCollect("Azimuth"));
		esmbaseevent=atoi((_bstr_t)ado.pRst->GetCollect("ESM基本事件"));
		combaseevent=atoi((_bstr_t)ado.pRst->GetCollect("COM基本事件"));
		gogal=atoi((_bstr_t)ado.pRst->GetCollect("目标类型"));
		plat=atoi((_bstr_t)ado.pRst->GetCollect("平台态势"));
		//trackbaseevent
		if(trackbaseevent==0)
		{
			strackbaseevent="--------";
		}
		if(trackbaseevent==1)
		{
			strackbaseevent="匀速直线运动";
		}
		if(trackbaseevent==2)
		{
			strackbaseevent="加速直线运动";
		}
		if(trackbaseevent==3)
		{
			strackbaseevent="俯冲";
		}
		if(trackbaseevent==4)
		{
			strackbaseevent="上升";
		}
		if(trackbaseevent==5)
		{
			strackbaseevent="拐弯";
		}
		if(trackbaseevent==6)
		{
			strackbaseevent="远离本舰";
		}
		if(trackbaseevent==7)
		{
			strackbaseevent="逼近本舰";
		}
		if(trackbaseevent==8)
		{
			strackbaseevent="位置固定";
		}
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
		//esmbaseevent
		if(esmbaseevent==0)
		{
			sesmbaseevent="--------";
		}
		if(esmbaseevent==1)
		{
			sesmbaseevent="搜索";
		}
		if(esmbaseevent==2)
		{
			sesmbaseevent="跟踪";
		}		
		if(esmbaseevent==3)
		{
			sesmbaseevent="干扰";
		}		
		if(esmbaseevent==4)
		{
			sesmbaseevent="火控引导";
		}
		//combaseevent
		if(combaseevent==0)
		{
			scombaseevent="--------";
		}
		if(combaseevent==1)
		{
			scombaseevent="联络";
		}
		if(combaseevent==2)
		{
			scombaseevent="指挥";
		}

	//
		if(gogal==0)
		{
			sgogal="--------";
		}
		if(gogal==1)
		{
			sgogal="战斗机";
		}
		if(gogal==2)
		{
			sgogal="轰炸机";
		}
		if(gogal==3)
		{
			sgogal="歼击机、攻击机";
		}
		if(gogal==4)
		{
			sgogal="预警机";
		}
		if(gogal==5)
		{
			sgogal="侦察机";
		}
		if(gogal==6)
		{
			sgogal="干扰机";
		}
		if(gogal==7)
		{
		    sgogal="直升机";

		}
		if(gogal==8)
		{
			sgogal="舰艇";
		}
		if(gogal==9)
		{
			sgogal="战术导弹";
		}
		if(gogal==10)
		{
			sgogal="制导武器";
		}

		//
		if(plat==0)
		{
			splat="--------";
		}
		if(plat==1)
		{
			splat="警戒";
		}
		if(plat==2)
		{
			splat="巡逻";
		}
		if(plat==3)
		{
			splat="拦截";
		}
		if(plat==4)
		{
			splat="攻击";
		}
		if(plat==5)
		{
			splat="轰炸";
		}
		if(plat==6)
		{
			splat="突防";
		}
		if(plat==7)
		{
			splat="干扰";
		}
		if(plat==8)
		{
			splat="预警指挥";
		}
		if(plat==9)
		{
			splat="不明";
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
	ado.pRst->Open("select * from 平台态势",ado.pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);

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
	if(strackbaseevent=="匀速直线运动")
	{
		trackbaseevent=1;
	}
	if(strackbaseevent=="加速直线运动")
	{
		trackbaseevent=2;
	}
	if(strackbaseevent=="俯冲")
	{
		trackbaseevent=3;
	}
	if(strackbaseevent=="上升")
	{
		trackbaseevent=4;
	}
	if(strackbaseevent=="拐弯")
	{
		trackbaseevent=5;
	}
	if(strackbaseevent=="远离本舰")
	{
		trackbaseevent=6;
	}
	if(strackbaseevent=="逼近本舰")
	{
		trackbaseevent=7;
	}
	if(strackbaseevent=="位置固定")
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
//gogal
	if(sgogal=="战斗机")
	{
		gogal=1;
	}
	if(sgogal=="轰炸机")
	{
		gogal=2;
	}
	if(sgogal=="歼击机、攻击机")
	{
		gogal=3;
	}
	if(sgogal=="预警机")
	{
		gogal=4;
	}
	if(sgogal=="侦察机")
	{
		gogal=5;
	}
	if(sgogal=="干扰机")
	{
		gogal=6;
	}
	if(sgogal=="直升机")
	{
		gogal=7;
	}
	if(sgogal=="舰艇")
	{
		gogal=8;
	}
	if(sgogal=="战术导弹")
	{
		gogal=9;
	}
	if(sgogal=="制导导弹")
	{
		gogal=10;
	}
	if(sgogal=="--------")
	{
		gogal=0;
	}
//esmbaseevent
	if(sesmbaseevent=="搜索")
	{
		esmbaseevent=1;
	}
	if(sesmbaseevent=="跟踪")
	{
		esmbaseevent=2;
	}
	if(sesmbaseevent=="干扰")
	{
		esmbaseevent=3;
	}
	if(sesmbaseevent=="火控引导")
	{
		esmbaseevent=4;
	}
	if(sesmbaseevent=="--------")
	{
		esmbaseevent=0;
	}
//combaseevent
	if(scombaseevent=="联络")
	{
		combaseevent=1;
	}
	if(scombaseevent=="指挥")
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
	if(splat=="警戒")
	{
		plat=1;
	}

	if(splat=="巡逻")
	{
		plat=2;
	}

	if(splat=="拦截")
	{
		plat=3;
	}

	if(splat=="攻击")
	{
		plat=4;
	}

	if(splat=="轰炸")
	{
		plat=5;
	}

	if(splat=="突防")
	{
		plat=6;
	}

	if(splat=="干扰")
	{
		plat=7;
	}

	if(splat=="预警指挥")
	{
		plat=8;
	}

	if(splat=="不明")
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
			MessageBox("ID号重复，请重新添加!");
		}
		ado.pRst->MoveNext();
	}
	//此处可不做判断，由数据库来做唯一性判断
	try{
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
		ado.pRst->MoveLast();
		ado.pRst->AddNew();

	ado.pRst->PutCollect("ID",atol(m_id));
	ado.pRst->PutCollect("Track基本事件",(long)trackbaseevent);
	ado.pRst->PutCollect("Rd",(long)rd);
	ado.pRst->PutCollect("Speed",(long)speed);
	ado.pRst->PutCollect("AddSpeed",(long)addspeed);
	ado.pRst->PutCollect("Azimuth",(long)azimuth);
	ado.pRst->PutCollect("High",(long)high);
	ado.pRst->PutCollect("ESM基本事件",(long)esmbaseevent);
	ado.pRst->PutCollect("COM基本事件",(long)combaseevent);
	ado.pRst->PutCollect("目标类型",(long)gogal);
	ado.pRst->PutCollect("平台态势",(long)plat);
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
	if(strackbaseevent=="匀速直线运动")
	{
		trackbaseevent=1;
	}
	if(strackbaseevent=="加速直线运动")
	{
		trackbaseevent=2;
	}
	if(strackbaseevent=="俯冲")
	{
		trackbaseevent=3;
	}
	if(strackbaseevent=="上升")
	{
		trackbaseevent=4;
	}
	if(strackbaseevent=="拐弯")
	{
		trackbaseevent=5;
	}
	if(strackbaseevent=="远离本舰")
	{
		trackbaseevent=6;
	}
	if(strackbaseevent=="逼近本舰")
	{
		trackbaseevent=7;
	}
	if(strackbaseevent=="位置固定")
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
	//gogal
	int gogal;
	CString sgogal;
	m_gog.GetLBText(m_gog.GetCurSel(),sgogal);
	if(sgogal=="战斗机")
	{
		gogal=1;
	}
	if(sgogal=="轰炸机")
	{
		gogal=2;
	}
	if(sgogal=="歼击机、攻击机")
	{
		gogal=3;
	}
	if(sgogal=="预警机")
	{
		gogal=4;
	}
	if(sgogal=="侦察机")
	{
		gogal=5;
	}
	if(sgogal=="干扰机")
	{
		gogal=6;
	}
	if(sgogal=="直升机")
	{
		gogal=7;
	}
	if(sgogal=="舰艇")
	{
		gogal=8;
	}
	if(sgogal=="战术导弹")
	{
		gogal=9;
	}
	if(sgogal=="制导导弹")
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
	if(sesmbaseevent=="搜索")
	{
		esmbaseevent=1;
	}
	if(sesmbaseevent=="跟踪")
	{
		esmbaseevent=2;
	}
	if(sesmbaseevent=="干扰")
	{
		esmbaseevent=3;
	}
	if(sesmbaseevent=="火控引导")
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
	if(scombaseevent=="联络")
	{
		combaseevent=1;
	}
	if(scombaseevent=="指挥")
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
	if(splat=="警戒")
	{
		plat=1;
	}
	
	if(splat=="巡逻")
	{
		plat=2;
	}
	
	if(splat=="拦截")
	{
		plat=3;
	}
	
	if(splat=="攻击")
	{
		plat=4;
	}
	
	if(splat=="轰炸")
	{
		plat=5;
	}
	
	if(splat=="突防")
	{
		plat=6;
	}
	
	if(splat=="干扰")
	{
		plat=7;
	}
	
	if(splat=="预警指挥")
	{
		plat=8;
	}
	
	if(splat=="不明")
	{
		plat=9;
	}
	
	ado.OnInitADOConn();
	CString sql;
	sql.Format("update 平台态势 set Track基本事件=%d,Rd=%d,High=%d,Speed=%d,AddSpeed=%d,Azimuth=%d,ESM基本事件=%d,COM基本事件=%d,目标类型=%d,平台态势=%d where ID=%d",trackbaseevent,rd,high,speed,addspeed,azimuth,esmbaseevent,combaseevent,gogal,plat,ids);
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
	sql.Format("delete from 平台态势 where ID=%d",id);
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
