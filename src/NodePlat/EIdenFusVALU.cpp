// EIdenFusVALU.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "EIdenFusVALU.h"
#include "EmulateBiaoge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEIdenFusVALU dialog


CEIdenFusVALU::CEIdenFusVALU(CWnd* pParent /*=NULL*/)
	: CDialog(CEIdenFusVALU::IDD, pParent)
{
	maxcode_all=0;
	//{{AFX_DATA_INIT(CEIdenFusVALU)
		// NOTE: the ClassWizard will add member initialization here
	m_radio = -1;
	//}}AFX_DATA_INIT
}


void CEIdenFusVALU::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEIdenFusVALU)
	DDX_Control(pDX, IDC_COMBOTARGETCODE, m_TargetCode);
	DDX_Control(pDX, IDC_COMBOSORT, m_EIdenFusSort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEIdenFusVALU, CDialog)
	//{{AFX_MSG_MAP(CEIdenFusVALU)
	ON_BN_CLICKED(IDC_QUEDING, OnQueding)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_GRID, IDC_RADIO_GRAPH, OnRadioClicked)
	ON_CBN_SELCHANGE(IDC_COMBOSORT, OnSelchangeCombosort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEIdenFusVALU message handlers

BOOL CEIdenFusVALU::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_EIdenFusSort.SetCurSel(0);

    
    //��ȡ��ʾ���ۺ�����
  	m_TargetCode.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEIdenFusVALU::OnQueding()
{
	int sort;
	int code;
	CString msg,temp;
	sort=m_EIdenFusSort.GetCurSel();
	code=m_TargetCode.GetCurSel()+1;
	CString S_Tn;
	m_TargetCode.GetWindowText(S_Tn);
	if(sort==1)// Ŀ��ʶ��������  //Эͬ��������
	{
		if(m_radio==0) //�����ʽ
		{
		}
		else if(m_radio==1)//ͼ��
		{
		}
		else
			MessageBox("��ѡ����ʾ��ʽ","����",MB_OK+MB_DEFBUTTON1);


// 		CAssociateGrid *dlg0;
// 		dlg0 = new CAssociateGrid;
// 		dlg0->m_tn=atoi(S_Tn);
// 		dlg0->Create(IDD_DLGRSASSOCIATEGRID,this);	
// 		dlg0->ShowWindow(SW_SHOW);	
// 		dlg0->MoveWindow(200,200,670,380,true);
// 		dlg0->UpdateWindow(); 

		
	}
	if(sort==0) // �ںϾ�������   //��λ��������
	{
		if(m_radio==0) //�����ʽ
		{
// 			CEMULATEGRID *dlg1;
// 			dlg1 = new CEMULATEGRID;
// 			dlg1->m_tn=atoi(S_Tn);
// 			dlg1->Create(IDD_DLGEMULATE_GRID,this);	
// 			dlg1->ShowWindow(SW_SHOW);	
// 			dlg1->MoveWindow(200,200,670,380,true);
// 			dlg1->UpdateWindow(); 
			CEmulateBiaoge *dlg1;
			dlg1 = new CEmulateBiaoge;
			//dlg1->m_tn=atoi(S_Tn);
			dlg1->Create(IDD_DIG_FUSEMULATE_BIAOGE,this);	
			dlg1->ShowWindow(SW_SHOW);	
			dlg1->MoveWindow(200,200,670,380,true);
			dlg1->UpdateWindow(); 

			
		}
		else if(m_radio==1)//ͼ��
		{
// 			CPrecisionEmulate *dlg2;
// 			dlg2 = new CPrecisionEmulate;
// 			
// 			dlg2->m_tn=atoi(S_Tn);
// 			
// 			dlg2->Create(IDD_DLGPRECISION_EMULATE,this);	
// 			dlg2->ShowWindow(SW_SHOW);	
// 			dlg2->MoveWindow(200,200,670,380,true);
// 			dlg2->UpdateWindow(); 
		}
		else
			MessageBox("��ѡ����ʾ��ʽ","����",MB_OK+MB_DEFBUTTON1);		
	}

}

void CEIdenFusVALU::OnRadioClicked(UINT nID)
{
	if(nID==IDC_RADIO_GRID)
		m_radio=0;
	else
		m_radio=1;
}

void CEIdenFusVALU::OnSelchangeCombosort() 
{
	// TODO: Add your control notification handler code here
// 	// ������ʾ��ʽ
// 	if(((CComboBox*)GetDlgItem(IDC_COMBOSORT))->GetCurSel()==1)
// 		GetDlgItem(IDC_RADIO_GRAPH)->EnableWindow(false);  //��ѡ���ںϾ�������,ֻ�б����ʾ
// 	else
// 		GetDlgItem(IDC_RADIO_GRAPH)->EnableWindow(true);
	if(((CComboBox*)GetDlgItem(IDC_COMBOSORT))->GetCurSel()==1)
		GetDlgItem(IDC_RADIO_GRAPH)->EnableWindow(true);
	else
		GetDlgItem(IDC_RADIO_GRAPH)->EnableWindow(true);
}
