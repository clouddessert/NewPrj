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
		_T("时  戳"),//0
		//_T("合批号"),//1
		
			_T("下发方位"),//3
			_T("下发仰角"),//4
			_T("下发径距"),//2	

				
			_T("融合方位"),//6
			_T("融合仰角"),//7
			_T("融合径距"),//5
			
			
			_T("方位真值"),//9
			_T("仰角真值"),//10
			_T("径距真值"),//8	
			
		
			_T("方位误差"),//12
			_T("仰角误差"),//13	
			_T("径距误差"),//11	
	};
	CString str;
	//if (num>8199)
	//{
	//	str.Format("指定信号%d定位结果评估",num);
	//}
    //	else
		//if (num<8200&&num>7999)
		//{
	str.Format("指定目标%d融合结果评估",num);
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

	((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetRedraw(FALSE);//关闭重绘
	//清除显示列表
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

		m_dbset.GetFieldValue("xf_ea",str); //下发仰角
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
	    ((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUS))->SetRedraw();//启动
	//	m_zdFus.EnsureVisible(m_zdFus.GetItemCount()-1,FALSE); //始终显示当前最新信息
	}
	m_dbset.Close();
	m_db.Close();
}


// BOOL CZDFus::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
// {
// 	// TODO: Add your message handler code here and/or call default
// 	int nPos = m_msfg_zdloc.GetScrollPos(SB_VERT);         //获得当前垂直滚动条位置
// 	int nMax = m_msfg_zdloc.GetScrollLimit(SB_VERT);      //获得当前垂直滚动条位置范围的最大值
// 	CRect rc;
// 	m_msfg_zdloc.GetWindowRect(rc);
// 	if (rc.PtInRect(pt))
// 	{
// 		
// 		if(zDelta < 0)         //判断滚动方向为向下滚动		
// 		{		
// 			nPos += 3;		
// 			(nPos >= nMax) ? (nPos = nMax-1) : NULL;		
// 		}	
// 		else		
// 		{		
// 			nPos -= 3;		
// 			(nPos <= 1) ? (nPos = 1) : NULL;		
// 		}
// 		m_msfg_zdloc.SetTopRow(nPos);            //设定网格控件显示的第一行	
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