// MsgThreePage.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "MsgThreePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////
extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMsgThreePage property page

IMPLEMENT_DYNCREATE(CMsgThreePage, CPropertyPage)

CMsgThreePage::CMsgThreePage() : CPropertyPage(CMsgThreePage::IDD)
{
	//{{AFX_DATA_INIT(CMsgThreePage)
	//}}AFX_DATA_INIT
}

CMsgThreePage::~CMsgThreePage()
{
}

void CMsgThreePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgThreePage)
	DDX_Control(pDX, IDC_LIST_TRACE, m_click_trace);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgThreePage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgThreePage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_TRACE_MSG, OnTraceMessage)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_TRACE, OnRclickListTrace)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgThreePage message handlers

BOOL CMsgThreePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hTRACE_wmd = GetSafeHwnd();

	CString Trace_Columns[]=
	{
 		_T("������"),//0
		_T("Ŀ������"),  //1

		_T("ƽ̨���"),//2
		_T("�豸���"),//3
		_T("�豸����"),//4
		
		_T("ƽ̨����"), //5
		_T("���Ŷ�"),  //6
		_T("��λ"),  //7

		_T("ƽ̨����"), //8
		_T("����"),     //9
		_T("γ��"),     //10
		
		_T("����"),
		_T("����"),
		_T("���Ժ���"),
		_T("�źŵ���ʱ��"),
		_T("Ŀ�귽λ�ǽ��ٶ�"),
		_T("Ŀ�����ǽ��ٶ�"),
		_T("Ŀ��ռ�����X"),
		_T("Ŀ��ռ�����Y"),
		_T("Ŀ��ռ�����Z"),
		_T("Ŀ������ٶ�X"),
		_T("Ŀ������ٶ�Y"),
		_T("Ŀ������ٶ�z"),
	};
	
	((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(Trace_Columns)/sizeof(Trace_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->InsertColumn(i, Trace_Columns[i], LVCFMT_CENTER, 80);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMsgThreePage::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	this->ShowWindow(SW_MAXIMIZE);
	
	//�ж��Ƿ���ڶ��㴰��
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_TRACE)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}

LRESULT CMsgThreePage::OnTraceMessage(WPARAM wParam, LPARAM lParam)  
{
	VCT_TRACE_MSG::reverse_iterator pTrace_Dat;

	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;
	int ntrace = 1;

	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetRedraw(FALSE);//�ر��ػ�
		
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->DeleteAllItems();
		
		//��ʾ����
		//for (pTrace_Dat = theApp.m_Trace.begin(); pTrace_Dat != theApp.m_Trace.end(); pTrace_Dat++,++nTmp)
		//������ʾ
		for (pTrace_Dat = theApp.m_Trace.rbegin(),ntrace =1; pTrace_Dat != theApp.m_Trace.rend(),ntrace <= 2; ++pTrace_Dat,++nTmp, ++ntrace)
		{
			strTmp.Format("%s", _T("Trace"));
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->InsertItem(nTmp, strTmp, 9);
			
			strTmp.Format("%d",pTrace_Dat->lAutonum); //������
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 0, strTmp);

		    fTmp = pTrace_Dat->lTargetNumber;//Ŀ������
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 1, strTmp);

			strTmp.Format("%s",pTrace_Dat->cPlatNumber); //ƽ̨���
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 2, strTmp);
			
			strTmp.Format("%s",pTrace_Dat->cEquipmentNumber); //�豸���
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 3, strTmp);
			
			strTmp.Format("%s",pTrace_Dat->cEquipmentType); //�豸����
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 4, strTmp);
			
			
//			fTmp = pTrace_Dat->sPlatType;  //������  //ƽ̨����
//			strTmp.Format("%d",(int)fTmp);
			strTmp.Format("%s",pTrace_Dat->sPlatType);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 5, strTmp);
			
			fTmp = pTrace_Dat->dConfidence;  //���Ŷ�
			strTmp.Format("%.2f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 6, strTmp);


			fTmp = pTrace_Dat->dAzimuth;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 7, strTmp);


			strTmp.Format("%s",pTrace_Dat->cPlatName);  //ƽ̨����
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 8, strTmp);
			
			fTmp = pTrace_Dat->dLonti; //����
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 9, strTmp);
			
			fTmp = pTrace_Dat->dLati; //γ��
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp, 10, strTmp);

			fTmp = pTrace_Dat->dRange; //����
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp,11,strTmp);
			
			fTmp = pTrace_Dat->dElevationAngle; //����
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp,12,strTmp);
			fTmp = pTrace_Dat->dCourse; //���Ժ���
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp,13,strTmp);
			fTmp = pTrace_Dat->lSignalReachTime; //�źŵ���ʱ��
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp,14,strTmp);
			fTmp = pTrace_Dat->dTargetAZSpeed; //Ŀ�귽λ�ǽ��ٶ�
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp,15,strTmp);
			fTmp = pTrace_Dat->dTargetEAngleSpeed; //Ŀ�����ǽ��ٶ�
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp,16,strTmp);
			fTmp = pTrace_Dat->dTX; //Ŀ��ռ�����X
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp,17,strTmp);
			fTmp = pTrace_Dat->dTY; //Ŀ��ռ�����Y
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp,18,strTmp);
			fTmp = pTrace_Dat->dTZ; //Ŀ��ռ�����Z
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp,19,strTmp);
			fTmp = pTrace_Dat->dTSpeedX; //Ŀ������ٶ�X
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp,20,strTmp);
			fTmp = pTrace_Dat->dTSpeedY; //Ŀ������ٶ�Y
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp,21,strTmp);
			fTmp = pTrace_Dat->dTSpeedZ; //Ŀ������ٶ�z
			strTmp.Format("%.4f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetItemText(nTmp,22,strTmp);
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->SetRedraw();//����
	}
	else
	{
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_TRACE))->DeleteAllItems();
	}
	
	return 0;  
} 
void CMsgThreePage::OnRclickListTrace(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
//#if 0
	bool num[5] = {TRUE,TRUE,TRUE,TRUE,TRUE};

	DWORD dwPos = GetMessagePos();
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) ); 
	/*������к�*/
	m_click_trace.ScreenToClient(&point);
	
	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;
	int nItem = m_click_trace.SubItemHitTest(&lvinfo);
	if(nItem != -1)
	{
		//CString strtemp;
		//strtemp.Format("������ǵ�%d�е�%d��", lvinfo.iItem, lvinfo.iSubItem);
		//AfxMessageBox(strtemp);
		theApp.m_iline = lvinfo.iItem;
	}
	/*��ȡ����*/
	switch (theApp.m_ThisNumber)
	{
	case 0:
		{
			num[0] = FALSE;
			break;
		}
	case 1:
		{
			num[1] = FALSE;
			break;
		}
	case 2:
		{
			num[2] = FALSE;
			break;
		}
	case 3:
		{
			num[3] = FALSE;
			break;
		}
	case 4:
		{
			num[4] = FALSE;
			break;
		}
	default:
		break;
	}
	/*�һ������˵�*/
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_SENDREQUEST));    //IDR_SENDQUEST���½��˵�ID
// 	if (!num[0]) menu.EnableMenuItem(IDM_MATEA, MF_GRAYED);//���Ϊ���������Ӳ˵����
// 	if (!num[1]) menu.EnableMenuItem(IDM_MATEB, MF_GRAYED);
// 	if (!num[2]) menu.EnableMenuItem(IDM_MATEC, MF_GRAYED);
// 	if (!num[3]) menu.EnableMenuItem(IDM_MATED, MF_GRAYED);
// 	if (!num[4]) menu.EnableMenuItem(IDM_MATEE, MF_GRAYED);
	if (!num[0]) 
	{
		menu.EnableMenuItem(IDM_SENDA, MF_GRAYED);//���Ϊ���������Ӳ˵����
		menu.EnableMenuItem(IDM_CLOSEA, MF_GRAYED);
	}
	if (!num[1]) 
	{
		menu.EnableMenuItem(IDM_SENDB, MF_GRAYED);
		menu.EnableMenuItem(IDM_CLOSEB, MF_GRAYED);
	}
	if (!num[2]) 
	{
		menu.EnableMenuItem(IDM_SENDC, MF_GRAYED);
		menu.EnableMenuItem(IDM_CLOSEC, MF_GRAYED);
	}
	if (!num[3])
	{
		menu.EnableMenuItem(IDM_SENDD, MF_GRAYED);
		menu.EnableMenuItem(IDM_CLOSED, MF_GRAYED);
	}
	if (!num[4]) 
	{
		menu.EnableMenuItem(IDM_SENDE, MF_GRAYED);
		menu.EnableMenuItem(IDM_CLOSEE, MF_GRAYED);
	}
	CMenu* popup = menu.GetSubMenu(0);        //ȡ�ñ�ָ���˵����������ʽ�˵����Ӳ˵��ľ��
	CPoint oPoint;//����һ������ȷ�����λ�õ�λ��  
    GetCursorPos(&oPoint);//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����
	popup->TrackPopupMenu(TPM_LEFTALIGN, oPoint.x,oPoint.y,this );//TPM_RIGHTBUTTONʹ�Ҽ�����˵�Ҳ������, ��ָ��λ����ʾ�����˵��������ٲ˵����ѡ��
//#endif	
	*pResult = 0;
}
