// QBsinIdenti.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "QBsinIdenti.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQBsinIdenti dialog
extern CNodePlatApp theApp;

CQBsinIdenti::CQBsinIdenti(CWnd* pParent /*=NULL*/)
	: CDialog(CQBsinIdenti::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQBsinIdenti)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CQBsinIdenti::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQBsinIdenti)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQBsinIdenti, CDialog)
	//{{AFX_MSG_MAP(CQBsinIdenti)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQBsinIdenti message handlers

BOOL CQBsinIdenti::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.hQbsinSb_wnd = GetSafeHwnd();
	
	CString QBsinSB_Columns[]=
	{
		_T("合批号"),//0
			_T("下发平台类型"),//1		
			_T("真实平台类型"),//2
			_T("单舰识别平台类型"),
			_T("单舰识别可信度"),//3
		//	_T("综合识别可信度"),//4
		//	_T("识别率"),//5
			
	};
	((CListCtrl*)GetDlgItem(IDC_LIST_SIN))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	for(int i=0; i<sizeof(QBsinSB_Columns)/sizeof(QBsinSB_Columns[0]); ++i)
		((CListCtrl*)GetDlgItem(IDC_LIST_SIN))->InsertColumn(i, QBsinSB_Columns[i], LVCFMT_CENTER, 110);	
	
	OpenIdentiDb();
	ShowData();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CQBsinIdenti::ShowData()
{
	// 	CString strStatic1;
	// 	CString strStatic2;
	CString dbname;
	CString strSQL;
	
	strSQL.Format("select *from sin_identi");
	CRecordset m_dbset(&m_dbidenti);
	CString tmp;
	int nTmp = 0;
	CString strTmp;
	
	int i(1);
	if(!m_dbset.Open(CRecordset::forwardOnly,strSQL,CRecordset::readOnly))
		AfxMessageBox("No RD!");
	
	((CListCtrl*)GetDlgItem(IDC_LIST_SIN))->SetRedraw(FALSE);//关闭重绘
	//清除显示列表
	((CListCtrl*)GetDlgItem(IDC_LIST_SIN))->DeleteAllItems();
	while(!m_dbset.IsEOF())
	{
		strTmp.Format("%s", _T("QBsinIdenti"));
		((CListCtrl*)GetDlgItem(IDC_LIST_SIN))->InsertItem(nTmp, strTmp, 9);
		
		m_dbset.GetFieldValue("lAutomn",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_SIN))->SetItemText(nTmp, 0, strTmp);
		
		m_dbset.GetFieldValue("xf_ty",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_SIN))->SetItemText(nTmp, 1, strTmp);
		
		m_dbset.GetFieldValue("real_ty",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_SIN))->SetItemText(nTmp, 2, strTmp);
		
		m_dbset.GetFieldValue("sin_ty",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_SIN))->SetItemText(nTmp, 3, strTmp);
		
		m_dbset.GetFieldValue("sin_con",tmp);
		strTmp.Format("%s",tmp);
		((CListCtrl*)GetDlgItem(IDC_LIST_SIN))->SetItemText(nTmp, 4, strTmp);
		
// 		m_dbset.GetFieldValue("sbl",tmp);
// 		strTmp.Format("%s",tmp);
// 		((CListCtrl*)GetDlgItem(IDC_LIST_SIN))->SetItemText(nTmp, 5, strTmp);
		
		
		i++;
		m_dbset.MoveNext();
		if(i > 290)
			i = 1;
		((CListCtrl*)GetDlgItem(IDC_LIST_SIN))->SetRedraw();//启动
	}
	m_dbset.Close();
	
}


void CQBsinIdenti::OpenIdentiDb()  //识别
{
	CString strDriver = "MICROSOFT ACCESS DRIVER (*.mdb)";
	CString strDsn;
	char strFile[1024];
	GetCurrentDirectory(1024, strFile);
	strcat(strFile, "\\DB\\SinIdenti.mdb\0");
	strDsn.Format("ODBC;DRIVER={%s};UID=sa;PWD=;DBQ=%s",strDriver,strFile);
	m_dbidenti.Open(NULL,false,false,strDsn,false);
}
