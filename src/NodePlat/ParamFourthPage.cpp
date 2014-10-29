// ParamFourthPage.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "ParamFourthPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include "DialogTRA1.h"
#include "DialogTRA.h"
#include "DialogESM1.h"
#include "DialogESM.h"
#include "DialogCOM.h"
#include "DialogCOM1.h"
#include "DialogPLA.h"
#include "DialogFUN.h"
#include "DialogTIM.h"
#include "DialogSPA.h"
/////////////////////////////////////////////////////////////////////////////
// CParamFourthPage property page

IMPLEMENT_DYNCREATE(CParamFourthPage, CPropertyPage)

CParamFourthPage::CParamFourthPage() : CPropertyPage(CParamFourthPage::IDD)
{
	//{{AFX_DATA_INIT(CParamFourthPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CParamFourthPage::~CParamFourthPage()
{
}

void CParamFourthPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParamFourthPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParamFourthPage, CPropertyPage)
	//{{AFX_MSG_MAP(CParamFourthPage)
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_DB_TREE, OnSelchangedDbTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParamFourthPage message handlers

BOOL CParamFourthPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CTreeCtrl *pOwner = (CTreeCtrl*)(CTreeCtrl*)GetDlgItem(IDC_DB_TREE);
	
	HTREEITEM hTmp =pOwner->InsertItem(_T("规则库"), 0, 0);
	
	
	pOwner->InsertItem(_T("航迹状态设置"), 1, 1, hTmp);
	pOwner->InsertItem(_T("雷达信号状态设置"), 1, 1, hTmp);
	pOwner->InsertItem(_T("通讯信号状态设置"), 1, 1, hTmp);
	pOwner->InsertItem(_T("--------------------------"), 1, 1, hTmp);
	
	pOwner->InsertItem(_T("航迹基本事件设置"), 1, 1, hTmp);
	pOwner->InsertItem(_T("雷达信号基本事件设置"), 1, 1, hTmp);
	pOwner->InsertItem(_T("通讯信号基本事件设置"), 1, 1, hTmp);
	pOwner->InsertItem(_T("--------------------------"), 1, 1, hTmp);
	
	
	
	pOwner->InsertItem(_T("平台态势"), 1, 1, hTmp);
	pOwner->InsertItem(_T("--------------------------"), 1, 1, hTmp);
	
	pOwner->InsertItem(_T("空间群"), 1, 1, hTmp);
	pOwner->InsertItem(_T("功能群"), 1, 1, hTmp);
	pOwner->InsertItem(_T("相互作用群"), 1, 1, hTmp);
	//	pOwner->InsertItem(_T("事件层"), 1, 1, hTmp);
	//	pOwner->InsertItem(_T("特征层"), 1, 1, hTmp);
	
	pOwner->Expand(hTmp, TVE_EXPAND);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CParamFourthPage::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	this->ShowWindow(SW_MAXIMIZE);
	
	//判断是否存在顶层窗口
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		GetDlgItem(IDC_DB_TREE)->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
	
}








void CParamFourthPage::OnSelchangedDbTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	CTreeCtrl *pCtrl=(CTreeCtrl *)GetDlgItem(IDC_DB_TREE);
	CString str=pCtrl->GetItemText(pCtrl->GetSelectedItem());

	if(str=="航迹状态设置")
	{
		CDialogTRA1 *dlg=new CDialogTRA1;
		dlg->DoModal();
	}

	

	if(str=="雷达信号状态设置")
	{
		CDialogESM1 *dlg=new CDialogESM1;
		dlg->DoModal();
	}

	if(str=="通讯信号状态设置")
	{
		CDialogCOM1 *dlg=new CDialogCOM1;
		dlg->DoModal();
	}

	
	if(str=="航迹基本事件设置")
	{
		CDialogTRA *dlg=new CDialogTRA;
		dlg->DoModal();
	}
	if(str=="雷达信号基本事件设置")
	{
		CDialogESM *dlg=new CDialogESM;
		dlg->DoModal();
		
	}
	if(str=="通讯信号基本事件设置")
	{
		
		CDialogCOM *dlg=new CDialogCOM;
		dlg->DoModal();
	}

	if(str=="平台态势")
	{
		
		CDialogPLA *dlg=new CDialogPLA;
		dlg->DoModal();	
	}

	if(str=="空间群")
	{
		
		CDialogSPA *dlg=new CDialogSPA;
		dlg->DoModal();	
	}
	if(str=="功能群")
	{
		
		CDialogFUN *dlg=new CDialogFUN;
		dlg->DoModal();	
	}
	if(str=="相互作用群")
	{
		
		CDialogTIM *dlg=new CDialogTIM;
		dlg->DoModal();	
	}
	pCtrl->DeleteAllItems();
	OnInitDialog();
	*pResult = 0;
}

void CParamFourthPage::OnInitADOConn()
{
	try{
		
		CoInitialize(NULL);
		
		pConn.CreateInstance("ADODB.Connection");
		
	//	pConn->ConnectionString="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=..\\1021 NodePlat\\db\\Database.mdb;Persist Security Info=False";
	//  pConn->ConnectionString="Provider=MSDASQL.1;Persist Security Info=False;User ID=Admin;Data Source=MS Access Database;Initial Catalog=..\\1023 NodePlat 完善命令显示 加库 添加本舰的经纬高\\db\\Database.mdb";
	    pConn->ConnectionString="Provider=MSDASQL.1;Persist Security Info=False;User ID=sa;Data Source=MS Access Database;Initial Catalog=..\\NodePlat\\db\\Database.mdb";
		pConn->Open("","","",adConnectUnspecified);
	}catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
}

void CParamFourthPage::ExitConnect()
{
	if(pRst!=NULL)
		pRst->Close();
	pConn->Close();
	pRst.Release();
	pConn.Release();
	CoUninitialize();
}
