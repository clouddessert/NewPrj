// QBIdentiGraph.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "QBIdentiGraph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQBIdentiGraph dialog
extern CNodePlatApp theApp;

CQBIdentiGraph::CQBIdentiGraph(CWnd* pParent /*=NULL*/)
	: CDialog(CQBIdentiGraph::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQBIdentiGraph)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CQBIdentiGraph::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQBIdentiGraph)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQBIdentiGraph, CDialog)
	//{{AFX_MSG_MAP(CQBIdentiGraph)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQBIdentiGraph message handlers

BOOL CQBIdentiGraph::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hQbSbTu_wnd = GetSafeHwnd();
	
	CString QBSBTU_Columns[]=
	{
		_T("合批号"),//0
			_T("下发类型"),//1		
			_T("实际类型"),//2
			_T("综合识别类型"),//3
			_T("综合识别可信度"),//4
			_T("识别率"),//5
			
	};
	((CListCtrl*)GetDlgItem(IDC_LIST_QBSBTU))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(QBSBTU_Columns)/sizeof(QBSBTU_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSBTU))->InsertColumn(i, QBSBTU_Columns[i], LVCFMT_CENTER, 100);	
	
	OpenIdentiDb();
	ShowData();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CQBIdentiGraph::ShowData()
{
	// 	CString strStatic1;
	// 	CString strStatic2;
	CString dbname;
	CString strSQL;
	
	// 	dbname.Format("%d",num);
	// 	strStatic1.Format("第%d批号目标平台类型识别率统计",num);
	// 	GetDlgItem(IDC_S1)->SetWindowText(strStatic1);
	// 	strStatic2.Format("真实平台型号:%s",real_plattye);
	// 	GetDlgItem(IDC_S2)->SetWindowText(strStatic2);
	
	strSQL.Format("select *from temp1");
	CRecordset m_dbset(&m_dbidenti);
	CString tmp;
	int nTmp = 0;
	unsigned long lTmp =0;
	float fTmp = 0.0;
	CString strTmp;
	
	int i(1);
	if(!m_dbset.Open(CRecordset::forwardOnly,strSQL,CRecordset::readOnly))
		AfxMessageBox("No RD!");
	
	((CListCtrl*)GetDlgItem(IDC_LIST_QBSBTU))->SetRedraw(FALSE);//关闭重绘
	//清除显示列表
	((CListCtrl*)GetDlgItem(IDC_LIST_QBSBTU))->DeleteAllItems();
	while(!m_dbset.IsEOF())
	{
		strTmp.Format("%s", _T("QBIdentiGraph"));
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSBTU))->InsertItem(nTmp, strTmp, 9);
		
		m_dbset.GetFieldValue("lAutomn",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSBTU))->SetItemText(nTmp, 0, strTmp);
		
		m_dbset.GetFieldValue("sb_ty",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSBTU))->SetItemText(nTmp, 1, strTmp);
		
		m_dbset.GetFieldValue("real_ty",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSBTU))->SetItemText(nTmp, 2, strTmp);
		
		m_dbset.GetFieldValue("zh_ty",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSBTU))->SetItemText(nTmp, 3, strTmp);
		
		m_dbset.GetFieldValue("zh_con",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSBTU))->SetItemText(nTmp, 4, strTmp);
		
		m_dbset.GetFieldValue("sbl",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSBTU))->SetItemText(nTmp, 5, strTmp);
		
		i++;
		m_dbset.MoveNext();
		if(i > 290)
			i = 1;
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSBTU))->SetRedraw();//启动
	}
	m_dbset.Close();
	
}


void CQBIdentiGraph::OpenIdentiDb()  //识别
{
	CString strDriver = "MICROSOFT ACCESS DRIVER (*.mdb)";
	CString strDsn;
	char strFile[1024];
	GetCurrentDirectory(1024, strFile);
	strcat(strFile, "\\DB\\Identi.mdb\0");
	strDsn.Format("ODBC;DRIVER={%s};UID=sa;PWD=;DBQ=%s",strDriver,strFile);
	m_dbidenti.Open(NULL,false,false,strDsn,false);
}
