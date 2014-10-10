// MsgFstPage.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "MsgFstPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////
extern CNodePlatApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMsgFstPage property page

IMPLEMENT_DYNCREATE(CMsgFstPage, CPropertyPage)

CMsgFstPage::CMsgFstPage() : CPropertyPage(CMsgFstPage::IDD)
{
	//{{AFX_DATA_INIT(CMsgFstPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgFstPage::~CMsgFstPage()
{
}

void CMsgFstPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgFstPage)
	DDX_Control(pDX, IDC_LIST_ESM, m_click_esm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgFstPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgFstPage)
	ON_WM_SIZE()
	ON_MESSAGE(WM_ESM_MSG, OnEsmMessage) 
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ESM, OnRclickListEsm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgFstPage message handlers

void CMsgFstPage::OnSize(UINT nType, int cx, int cy) 
{
	this->ShowWindow(SW_MAXIMIZE);

	//�ж��Ƿ���ڶ��㴰��
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_LIST_ESM)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}

BOOL CMsgFstPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hESM_wmd = GetSafeHwnd();

	CString ESM_Columns[]=
	{
// 		_T("ƽ̨���"),
// 		_T("�豸���"),
// 		_T("�豸����"),
 		_T("������"),//0
// 		
// 		_T("��Ƶ��Ϣ"),
// 		_T("��Ƶ��Ϣ"),
// 		_T("������Ϣ"),
// 		_T("�źŵ���ʱ��"),
// 		_T("�������"),
// 		_T("���﷽λ"),
// 		_T("����"),
// 		_T("����ɨ����Ϣ"),
// 		_T("����������Ϣ�ṹ"),
// 		
// 		_T("�״���;"),
// 		_T("�״�����"),
// 		_T("��в�ȼ�"),
// 		_T("��Ч���书��"),
// 		_T("ƽ̨����"),
// 		_T("ƽ̨�ͺ�"),
// 		_T("ƽ̨����"),
// 		_T("��������"),
// 		_T("���Ŷ�"),
// 		_T("����"),	
		    _T("Ŀ������"),//1
			
			_T("ƽ̨���"),//2
			_T("�豸���"),//3
			_T("�豸����"),//4
			
			
			_T("ƽ̨����"),  //5
			_T("���Ŷ�"),   //6
			_T("���﷽λ"), //7
			
			_T("��Ƶ��Ϣ"),
			_T("��Ƶ��Ϣ"),
			_T("������Ϣ"),
			_T("�źŵ���ʱ��"),
			_T("�������"),
			
			_T("����"),
			_T("����ɨ����Ϣ"),
			_T("����������Ϣ�ṹ"),
			
			_T("�״���;"),
			_T("�״�����"),
			_T("��в�ȼ�"),
			_T("��Ч���书��"),
			
//			_T("ƽ̨�ͺ�"),  
//			_T("ƽ̨����"),
			_T("��������"),
			
		    _T("����/����"),		
		
	};

	
	((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(ESM_Columns)/sizeof(ESM_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->InsertColumn(i, ESM_Columns[i], LVCFMT_CENTER, 80);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CMsgFstPage::OnEsmMessage(WPARAM wParam, LPARAM lParam)  
{ 
	VCT_ESM_MSG::iterator pESM_Dat;

	int nTmp = 0;
	int iTmpProp = 0;
	float fTmp = 0.0;
	CString strTmp;

	if (0 == wParam)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetRedraw(FALSE);//�ر��ػ�
		
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->DeleteAllItems();
		
		//��ʾ����
		for (pESM_Dat = theApp.m_ESM/*theApp.m_ESM_Dat*/.begin(); pESM_Dat != theApp.m_ESM/*theApp.m_ESM_Dat*/.end(); pESM_Dat++,++nTmp)
		{
			strTmp.Format("%s", _T("ESM"));
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->InsertItem(nTmp, strTmp, 9);
	// 		
	// 		strTmp.Format("%s", m_pTmpTrackIter->second.strName);
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 1, strTmp);
	// 		
	// 		strTmp.Format("%s", m_pTmpTrackIter->second.strType);
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 2, strTmp);
	// 		
	// 		iTmpProp = m_pTmpTrackIter->second.iTargetProp;
	// 		if (iTmpProp)
	// 		{
	// 			strTmp = _T("��");
	// 		}
	// 		else
	// 		{
	// 			strTmp = _T("��");
	// 		}
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 3, strTmp);
			
			strTmp.Format("%d",pESM_Dat->lAutonum);//������
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 0, strTmp);

			fTmp = pESM_Dat->lTargetNumber;//Ŀ������
			strTmp.Format("%d",(int)fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 1, strTmp);

			strTmp.Format("%s",pESM_Dat->cPlatNumber);//ƽ̨���
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 2, strTmp);
			
			strTmp.Format("%s",pESM_Dat->cEquipmentNumber); //�豸���
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 3, strTmp);
			
			strTmp.Format("%s",pESM_Dat->cEquipmentType); //�豸����
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 4, strTmp);
			
			strTmp.Format("%s",pESM_Dat->sPlatType);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 5, strTmp);
			
			fTmp = pESM_Dat->dConfidence;  //���Ŷ�
			strTmp.Format("%.2f",fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 6, strTmp);
						
			fTmp = pESM_Dat->dReachAzimuth;
			strTmp.Format("%.4f", fTmp);
			((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetItemText(nTmp, 7, strTmp);
			
	// 		fTmp = m_pTmpTrackIter->second.fLati;
	// 		strTmp.Format("%.4f", fTmp);
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 5, strTmp);
	// 		
	// 		fTmp = m_pTmpTrackIter->second.fHeight;
	// 		strTmp.Format("%.4f", fTmp);
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 6, strTmp);
	// 		
	// 		fTmp = m_pTmpTrackIter->second.fSpeed;
	// 		strTmp.Format("%.4f", fTmp);
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 7, strTmp);
	// 		
	// 		fTmp = m_pTmpTrackIter->second.fAngle;
	// 		strTmp.Format("%.4f", fTmp);
	// 		((CListCtrl*)GetDlgItem(IDC_LIST1))->SetItemText(nTmp, 8, strTmp);
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->SetRedraw();//����
	}
	else
	{
		//�����ʾ�б�
		((CListCtrl*)GetDlgItem(IDC_LIST_ESM))->DeleteAllItems();
	}
	
	return 0;  
} 

void CMsgFstPage::OnRclickListEsm(NMHDR* pNMHDR, LRESULT* pResult) 
{
//#if 0
	DWORD dwPos = GetMessagePos(); //���ر�ʾ��Ļ�����¹��λ�õĳ�����ֵ
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) ); 
/*������к�*/
	m_click_esm.ScreenToClient(&point);
	
	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;
	int nItem = m_click_esm.SubItemHitTest(&lvinfo);
	if(nItem != -1)
	{
		//CString strtemp;
		//strtemp.Format("������ǵ�%d�е�%d��", lvinfo.iItem, lvinfo.iSubItem);
		//AfxMessageBox(strtemp);
		theApp.m_iline = lvinfo.iItem;
	}
/*�һ������˵�*/
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_SENDREQUEST));       //IDR_SENDQUEST���½��˵�ID
	CMenu* popup = menu.GetSubMenu(0);        //ȡ�ñ�ָ���˵����������ʽ�˵����Ӳ˵��ľ��
	CPoint oPoint;//����һ������ȷ�����λ�õ�λ��  
    GetCursorPos(&oPoint);//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����
	popup->TrackPopupMenu(TPM_LEFTALIGN, oPoint.x,oPoint.y,this );//TPM_RIGHTBUTTONʹ�Ҽ�����˵�Ҳ������, ��ָ��λ����ʾ�����˵��������ٲ˵����ѡ��

	
	//#endif


	*pResult = 0;
}



// void CMsgFstPage::OnSendmsg() //��Ӧ�����˵�
// {
// 	// TODO: Add your command handler code here
// 
// 	
// }
