// ZDFus.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "ZDFus.h"
#include "Afxdb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZDFus dialog
extern CNodePlatApp theApp;

CZDFus::CZDFus(CWnd* pParent /*=NULL*/)
	: CDialog(CZDFus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZDFus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	num=0;
}


void CZDFus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZDFus)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZDFus, CDialog)
	//{{AFX_MSG_MAP(CZDFus)
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZDFus message handlers

BOOL CZDFus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hZdFus_wnd = GetSafeHwnd();
	
	CString ZDFUS_Columns[]=
	{   
		_T("ʱ  ��"),//0
		//_T("������"),//1
		
			_T("�·���λ"),//3
			_T("�·�����"),//4
			_T("�·�����"),//2	

				
			_T("�ںϷ�λ"),//6
			_T("�ں�����"),//7
			_T("�ںϾ���"),//5
			
			
			_T("��λ��ֵ"),//9
			_T("������ֵ"),//10
			_T("������ֵ"),//8	
			
		
			_T("��λ���"),//12
			_T("�������"),//13	
			_T("�������"),//11	
	};
	CString str;
	//if (num>8199)
	//{
	//	str.Format("ָ���ź�%d��λ�������",num);
	//}
    //	else
		//if (num<8200&&num>7999)
		//{
	str.Format("ָ��Ŀ��%d�ںϽ������",num);
		//}
			
	GetDlgItem(IDC_STATIC1)->SetWindowText(str);
	ShowData(num);
	((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(ZDFUS_Columns)/sizeof(ZDFUS_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->InsertColumn(i, ZDFUS_Columns[i], LVCFMT_CENTER, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CZDFus::ShowData(int number)
{
	CDatabase m_db;
	CString strDriver = "MICROSOFT ACCESS DRIVER (*.mdb)";
	CString strDsn;
	char strFile[1024];

//	CString tmp;
	int nTmp = 0;
	unsigned long lTmp =0;
	float fTmp = 0.0;
	CString strTmp;

	//CDatabase m_dbesm;
	GetCurrentDirectory(1024, strFile);
	strcat(strFile, "\\DB\\Location.mdb\0");
	strDsn.Format("ODBC;DRIVER={%s};UID=sa;PWD=;DBQ=%s",strDriver,strFile);
	m_db.Open(NULL,false,false,strDsn,false);
	CString p_query;
//	int num(8200);
	p_query.Format("select* from %dLoc",num);
    CRecordset m_dbset(&m_db);
	CString strSQL;
	if(!m_dbset.Open(CRecordset::dynaset,p_query,CRecordset::readOnly))
		AfxMessageBox("No RD!");

	m_dbset.MoveLast();
	int i(1);

	((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetRedraw(FALSE);//�ر��ػ�
	//�����ʾ�б�
	((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->DeleteAllItems();

	while(!m_dbset.IsBOF()&&i<=100)
	{
		CString str;
		strTmp.Format("%s", _T("ZDFus"));
		((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->InsertItem(nTmp, strTmp, 9);


//  		m_dbset.GetFieldValue("Sc",str);  
//          UNIFY ut = IntToTime(atoi(str));
//  		str.Format("%d:%02d:%02d",ut.h,ut.m,ut.s);
 //	    	((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetItemText(nTmp, 0, strTmp);
		
		m_dbset.GetFieldValue("xf_ag",str); 
		str.Format("%.2f",atof(str));
		((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetItemText(nTmp, 1, strTmp);

		m_dbset.GetFieldValue("xf_ea",str); //�·�����
		str.Format("%.2f",atof(str));
		((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetItemText(nTmp, 2, strTmp);

		m_dbset.GetFieldValue("xf_rg",str);  
		str.Format("%.3f",atof(str));
		((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetItemText(nTmp, 3, strTmp);

		m_dbset.GetFieldValue("rh_ag",str);   
		str.Format("%.3f",atof(str));  
		((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetItemText(nTmp, 4, strTmp);
		
		m_dbset.GetFieldValue("rh_ea",str);          
		str.Format("%.3f",atof(str));
		((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetItemText(nTmp, 5, strTmp);

		m_dbset.GetFieldValue("rh_rg",str);          
		str.Format("%.3f",atof(str));
		((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetItemText(nTmp, 6, strTmp);

		m_dbset.GetFieldValue("true_ag",str);   
		str.Format("%.3f",atof(str));
		((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetItemText(nTmp, 7, strTmp);
		
		m_dbset.GetFieldValue("true_ea",str);          
		str.Format("%.3f",atof(str));
		((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetItemText(nTmp, 8, strTmp);
		
		m_dbset.GetFieldValue("true_rg",str);          
		str.Format("%.3f",atof(str));
		((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetItemText(nTmp, 9, strTmp);

		m_dbset.GetFieldValue("AG_bzc",str);   
		str.Format("%.2f",atof(str));
		((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetItemText(nTmp, 10, strTmp);

		m_dbset.GetFieldValue("EA_bzc",str);          
		str.Format("%.2f",atof(str));
		((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetItemText(nTmp, 11, strTmp);

		m_dbset.GetFieldValue("RG_deta",str);  
		str.Format("%.2f",atof(str));
		((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetItemText(nTmp, 12, strTmp);
				
		m_dbset.MovePrev();
		i++;
	    ((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetRedraw();//����
	//	m_zdFus.EnsureVisible(m_zdFus.GetItemCount()-1,FALSE); //ʼ����ʾ��ǰ������Ϣ
	}
	m_dbset.Close();
	m_db.Close();
}


// BOOL CZDFus::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
// {
// 	// TODO: Add your message handler code here and/or call default
// 	int nPos = m_msfg_zdloc.GetScrollPos(SB_VERT);         //��õ�ǰ��ֱ������λ��
// 	int nMax = m_msfg_zdloc.GetScrollLimit(SB_VERT);      //��õ�ǰ��ֱ������λ�÷�Χ�����ֵ
// 	CRect rc;
// 	m_msfg_zdloc.GetWindowRect(rc);
// 	if (rc.PtInRect(pt))
// 	{
// 		
// 		if(zDelta < 0)         //�жϹ�������Ϊ���¹���		
// 		{		
// 			nPos += 3;		
// 			(nPos >= nMax) ? (nPos = nMax-1) : NULL;		
// 		}	
// 		else		
// 		{		
// 			nPos -= 3;		
// 			(nPos <= 1) ? (nPos = 1) : NULL;		
// 		}
// 		m_msfg_zdloc.SetTopRow(nPos);            //�趨����ؼ���ʾ�ĵ�һ��	
// 	}
// 	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
// }
// 

// UNIFY CZDFus::IntToTime(int t)
// {
// 	UNIFY ret;
// 	ret.ms = t%1000;
// 	ret.s = t%60000/1000;
// 	ret.m = t%3600000/60000;
// 	ret.h = t/3600000;	
// 	return ret;
// }