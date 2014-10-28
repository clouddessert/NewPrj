// QBIdenti.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "QBIdenti.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQBIdenti dialog
extern CNodePlatApp theApp;

CQBIdenti::CQBIdenti(CWnd* pParent /*=NULL*/)
	: CDialog(CQBIdenti::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQBIdenti)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CQBIdenti::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQBIdenti)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQBIdenti, CDialog)
	//{{AFX_MSG_MAP(CQBIdenti)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQBIdenti message handlers

BOOL CQBIdenti::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hQbSb_wnd = GetSafeHwnd();
	
	CString QBSB_Columns[]=
	{
		_T("合批号"),//0
			_T("下发类型"),//1		
			_T("实际类型"),//2
			_T("综合识别类型"),//3
			_T("综合识别可信度"),//4
			_T("识别率"),//5
			
	};
	((CListCtrl*)GetDlgItem(IDC_LIST_QBSB))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(QBSB_Columns)/sizeof(QBSB_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSB))->InsertColumn(i, QBSB_Columns[i], LVCFMT_CENTER, 100);	
	
	OpenIdentiDb();
	ShowData();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CQBIdenti::ShowData()
{
	// 	CString strStatic1;
	// 	CString strStatic2;
	CString dbname;
	CString strSQL;
	
	strSQL.Format("select *from temp1");
	CRecordset m_dbset(&m_dbidenti);
	CString tmp;
	int nTmp = 0;
	CString strTmp;
	
	int i(1);
	if(!m_dbset.Open(CRecordset::forwardOnly,strSQL,CRecordset::readOnly))
		AfxMessageBox("No RD!");
	
	((CListCtrl*)GetDlgItem(IDC_LIST_QBSB))->SetRedraw(FALSE);//关闭重绘
	//清除显示列表
	((CListCtrl*)GetDlgItem(IDC_LIST_QBSB))->DeleteAllItems();
	while(!m_dbset.IsEOF())
	{
		strTmp.Format("%s", _T("QBIdenti"));
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSB))->InsertItem(nTmp, strTmp, 9);
		
		m_dbset.GetFieldValue("lAutomn",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSB))->SetItemText(nTmp, 0, strTmp);
		
		m_dbset.GetFieldValue("sb_ty",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSB))->SetItemText(nTmp, 1, strTmp);
		
		m_dbset.GetFieldValue("real_ty",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSB))->SetItemText(nTmp, 2, strTmp);
		
		m_dbset.GetFieldValue("zh_ty",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSB))->SetItemText(nTmp, 3, strTmp);
		
		m_dbset.GetFieldValue("zh_con",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSB))->SetItemText(nTmp, 4, strTmp);
		
		m_dbset.GetFieldValue("sbl",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSB))->SetItemText(nTmp, 5, strTmp);
		
		
		i++;
		m_dbset.MoveNext();
		if(i > 290)
			i = 1;
		((CListCtrl*)GetDlgItem(IDC_LIST_QBSB))->SetRedraw();//启动
	}
	m_dbset.Close();
	
}


void CQBIdenti::OpenIdentiDb()  //识别
{
	CString strDriver = "MICROSOFT ACCESS DRIVER (*.mdb)";
	CString strDsn;
	char strFile[1024];
	GetCurrentDirectory(1024, strFile);
	strcat(strFile, "\\DB\\Identi.mdb\0");
	strDsn.Format("ODBC;DRIVER={%s};UID=sa;PWD=;DBQ=%s",strDriver,strFile);
	m_dbidenti.Open(NULL,false,false,strDsn,false);
}

