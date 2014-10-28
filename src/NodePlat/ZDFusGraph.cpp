// ZDFusGraph.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "ZDFusGraph.h"
#include "Afxdb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZDFusGraph dialog
extern CNodePlatApp theApp;

CZDFusGraph::CZDFusGraph(CWnd* pParent /*=NULL*/)
	: CDialog(CZDFusGraph::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZDFusGraph)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	count_factor=1;
	a_factor = 1;
	e_factor = 1;
	r_factor = 1;
	num = 0;
	cd_nb=0;
	distant01=0;
	distant02=0;
	distant12=0;
	name_self=' ';
}


void CZDFusGraph::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZDFusGraph)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_LIST_WUCHA, m_listWucha);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZDFusGraph, CDialog)
	//{{AFX_MSG_MAP(CZDFusGraph)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZDFusGraph message handlers

BOOL CZDFusGraph::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString str;
//	if (num>7999&&num<8200)
//	{
		str.Format("目标%d 融合结果各步误差显示框",num);
//	}
// 	else
// 	if (num>=8000) 
// 	{
// 		str.Format("信号%d各步误差显示框",num);
// 	}
		
	this->SetWindowText(str);
// 	if (count_factor==1)
// 	{
			GetDlgItem(IDC_STATIC1)->SetWindowText("0    30   60   90   120  150  180  210  240  270  300  330  360  390  420");
			GetDlgItem(IDC_STATIC2)->SetWindowText("0    30   60   90   120  150  180  210  240  270  300  330  360  390  420");
			GetDlgItem(IDC_STATIC3)->SetWindowText("0    30   60   90   120  150  180  210  240  270  300  330  360  390  420");
//	}else
// 	if (count_factor==3)
// 	{
// 				GetDlgItem(IDC_STATIC1)->SetWindowText("0    90   180  270  360  450  540  630  720  810  900  990  1080 1170 1260");
// 				GetDlgItem(IDC_STATIC2)->SetWindowText("0    90   180  270  360  450  540  630  720  810  900  990  1080 1170 1260");
// 				GetDlgItem(IDC_STATIC3)->SetWindowText("0    90   180  270  360  450  540  630  720  810  900  990  1080 1170 1260");
// 	}
	CString strshow;
	strshow.Format("步数|方位误差(度)|仰角误差(度)|径距误差(米)");
	AddMsgList(strshow);
// 			if (cd_nb==1)
// 			{
// 				CString strDistant;
// 				strDistant.Format("%c、%c两舰协同定位",name_self,name_nb1);
// 				GetDlgItem(IDC_STATIC_NB)->SetWindowText(strDistant);
// 				strDistant.Format("%c、%c基线长度：%d千米",name_self,name_nb1,distant01);
// 				strDistant.MakeUpper();
// 				GetDlgItem(IDC_STATIC01)->SetWindowText(strDistant);		
// 			}
// 			if (cd_nb==2)
// 			{
// 				CString strDistant;
// 				strDistant.Format("%c、%c两舰协同定位",name_self,name_nb2);
// 				GetDlgItem(IDC_STATIC_NB)->SetWindowText(strDistant);
// 				strDistant.Format("%c、%c基线长度：%d千米",name_self,name_nb2,distant02);
// 				strDistant.MakeUpper();
// 				GetDlgItem(IDC_STATIC01)->SetWindowText(strDistant);		
// 			}
// 			if (cd_nb==3)
// 			{
// 				CString strDistant;
// 				strDistant.Format("三舰协同定位");
// 				GetDlgItem(IDC_STATIC_NB)->SetWindowText(strDistant);
// 				strDistant.Format("%c、%c基线长度：%d千米",name_self,name_nb1,distant01);
// 				strDistant.MakeUpper();
// 				GetDlgItem(IDC_STATIC01)->SetWindowText(strDistant);
// 				strDistant.Format("%c、%c基线长度：%d千米",name_self,name_nb2,distant02);
// 				strDistant.MakeUpper();
// 				GetDlgItem(IDC_STATIC02)->SetWindowText(strDistant);
// 				strDistant.Format("%c、%c基线长度：%d千米",name_nb1,name_nb2,distant12);
// 				strDistant.MakeUpper();
// 				GetDlgItem(IDC_STATIC12)->SetWindowText(strDistant);
//			}


// 	theApp.hZdFusTu_wnd = GetSafeHwnd();
// 	
// 	CString ZDFUSTu_Columns[]=
// 	{   
// 		_T("时  戳"),//0
// 			_T("合批号"),//1
// 			_T("下发径距"),//2	
// 			_T("下发方位"),//3
// 			_T("下发仰角"),//4
// 
// 			_T("融合径距"),//8	
// 			_T("融合方位"),//9
// 			_T("融合仰角"),//10
// 
// 			_T("径距真值"),//5	
// 			_T("方位真值"),//6
// 			_T("仰角真值"),//7
// 
// 			_T("径距误差"),//11	
// 			_T("方位误差"),//12
// 			_T("仰角误差"),//13			
// 	};
// 	
// 	((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUSTU))->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
// 	
// 	for(int i=0; i<sizeof(ZDFUSTu_Columns)/sizeof(ZDFUSTu_Columns[0]); ++i)
// 		((CListCtrl*)GetDlgItem(IDC_LIST_ZDFUSTU))->InsertColumn(i, ZDFUSTu_Columns[i], LVCFMT_CENTER, 80);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CZDFusGraph::drawCoordination()
{
	CDC* pDC;
 	CWnd* pWnd = this;
 	pDC = pWnd->GetDC();
	CPen penl;
	penl.CreatePen(PS_SOLID,1,RGB(255,0,0));
	CPen* pOldPen=pDC->SelectObject(&penl);

	//画第一个坐标系
	CPoint p0(320,196),px(320,16),py(790,196);
	pDC->MoveTo(p0);
	pDC->LineTo(px);
	pDC->LineTo(CPoint(315,24));
	pDC->MoveTo(px);
	pDC->LineTo(CPoint(325,24));
	pDC->MoveTo(p0);
	pDC->LineTo(py);
	pDC->LineTo(CPoint(782,191));
	pDC->MoveTo(py);
	pDC->LineTo(CPoint(782,201));
//	pDC->TextOut(255,201,"0");

	// 画第二个坐标系
	CSize dp(0,205);
	pDC->MoveTo(p0+dp);
	pDC->LineTo(px+dp);
	pDC->LineTo(CPoint(315,24)+dp);
	pDC->MoveTo(px+dp);
	pDC->LineTo(CPoint(325,24)+dp);
	pDC->MoveTo(p0+dp);
	pDC->LineTo(py+dp);
	pDC->LineTo(CPoint(782,191)+dp);
	pDC->MoveTo(py+dp);
	pDC->LineTo(CPoint(782,201)+dp);

	// 画第三个坐标系
	CSize dpp(0,410);
	pDC->MoveTo(p0+dpp);
	pDC->LineTo(px+dpp);
	pDC->LineTo(CPoint(315,24)+dpp);
	pDC->MoveTo(px+dpp);
	pDC->LineTo(CPoint(325,24)+dpp);
	pDC->MoveTo(p0+dpp);
	pDC->LineTo(py+dpp);
	pDC->LineTo(CPoint(782,191)+dpp);
	pDC->MoveTo(py+dpp);
	pDC->LineTo(CPoint(782,201)+dpp);

	CFont m_font;
	m_font.CreateFont(12,6,0,0,FW_THIN,   
		FALSE,FALSE,FALSE,   
		DEFAULT_CHARSET,   
		OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,   
		DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"宋体"); 
    
	pDC->SelectObject(&m_font);
	pDC->SetBkMode(TRANSPARENT);

	CPoint ppy(294,190);
	CString str;
	float x = 0.0;
	float y = 0.0;
	int r=0;
	// 画纵轴刻度线
	for(int i=1;i<12;i++)
	{		
		CSize dyx(3,(-1)*i*16);
		CSize dyy(0,i*16);
		pDC->MoveTo(p0-dyy);
		pDC->LineTo(p0+dyx);
		x += (float)0.01*(float)a_factor;
		str.Format("%0.2f",x);
		pDC->TextOut((ppy-dyy).x, (ppy-dyy).y,str);
		
		pDC->MoveTo(p0+dp-dyy);
		pDC->LineTo(p0+dp+dyx);
		y += (float)0.01*(float)e_factor;
		str.Format("%0.2f",y);
		pDC->TextOut((ppy+dp-dyy).x,(ppy+dp-dyy).y,str);

		pDC->MoveTo(p0+dpp-dyy);
		pDC->LineTo(p0+dpp+dyx);
		r += (int)100*(int)r_factor;
		str.Format("%d",r);
		pDC->TextOut((ppy+dpp-dyy).x,(ppy+dpp-dyy).y,str);
	}
	// 画横轴刻度线
	for(i=1;i<16;i++)
	{
		CSize dxx(i*30,0);
		CSize dxy((-1)*i*30,3);
		pDC->MoveTo(p0+dxx);
		pDC->LineTo(p0-dxy);

		pDC->MoveTo(p0+dp+dxx);
		pDC->LineTo(p0+dp-dxy);

		pDC->MoveTo(p0+dpp+dxx);
		pDC->LineTo(p0+dpp-dxy);
	}	

	pDC->SelectObject(pOldPen);	
	ReleaseDC(pDC);
}

void CZDFusGraph::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	drawCoordination();
	showDataGraph(num);
	// Do not call CDialog::OnPaint() for painting messages
}

void CZDFusGraph::OnSetFont(CFont* pFont) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::OnSetFont(pFont);
}


void CZDFusGraph::showDataGraph(int autonum)
{
	CDatabase m_db;
	CString strDriver = "MICROSOFT ACCESS DRIVER (*.mdb)";
	CString strDsn;
	char strFile[1024];
	//CDatabase m_dbesm;
	GetCurrentDirectory(1024, strFile);
	strcat(strFile, "\\DB\\Fusion.mdb\0");
	strDsn.Format("ODBC;DRIVER={%s};UID=sa;PWD=;DBQ=%s",strDriver,strFile);
	m_db.Open(NULL,false,false,strDsn,false);
	CString p_query;
//	int num(8200);
	p_query.Format("select * from %dFus",autonum);
    CRecordset m_dbset(&m_db);
	CString strSQL;
	if(!m_dbset.Open(CRecordset::dynaset,p_query,CRecordset::readOnly))
		AfxMessageBox("No RD!");
	
	m_dbset.MoveFirst();
	int i(1);
	int buchang(0);
	double Abzc(0.0),Ebzc(0.0),Rbzc(0.0);
	CDC* pDC;
 	CWnd* pWnd = this;
 	pDC = pWnd->GetDC();
	CPen penl;
	penl.CreatePen(PS_SOLID,1,RGB(255,0,0));
	CPen* pOldPen=pDC->SelectObject(&penl);
	CPoint p0(320,196),px(320,16),py(690,196);
//	Invalidate(false);
//	m_listWucha.ResetContent();//	clearListbox();
	while(!m_dbset.IsEOF()&&i<=330*count_factor)
	{
		CDBVariant varValue;
		m_dbset.GetFieldValue("buchang",varValue);  
        buchang = varValue.m_iVal;
		
		m_dbset.GetFieldValue("AG_bzc",varValue);          
		Abzc = varValue.m_dblVal;

		m_dbset.GetFieldValue("EA_bzc",varValue);          
		Ebzc = varValue.m_dblVal;

		m_dbset.GetFieldValue("RG_deta",varValue);
		Rbzc = varValue.m_dblVal;
		CString strshow;
	                //  步数|方位误差(度)|仰角误差(度)|径距误差(米)
		strshow.Format("%3d:|%.4f      |%.4f      |%.1f",buchang,Abzc,Ebzc,Rbzc);
		int count = m_listWucha.GetCount();
		if(buchang>count)
		{
			AddMsgList(strshow);
		}
		
		int x = 320+buchang/count_factor;
		int y = 196-(int)(Abzc*1600/(float)a_factor);
		
	//	pDC->MoveTo(x,196);
		if (y>=16) 
		{
			pDC->SetPixel(x,y,RGB(0,0,255));
		}		
		
		y = 401-(int)(Ebzc*1600/(float)e_factor);
		if (y>=221)
		{
			pDC->SetPixel(x,y,RGB(2,0,255));
		}
		int r = 606-(int)(Rbzc*16/(100*r_factor));
		if (r>=426)
		{
			pDC->SetPixel(x,r,RGB(2,0,255));
		}
		m_dbset.MoveNext();
		i++;
	}

	m_dbset.Close();
	m_db.Close();

	pDC->SelectObject(pOldPen);	
	ReleaseDC(pDC);

}
void CZDFusGraph::AddMsgList(CString strShow) //添加信息于LISTBOX 控件中
{
	m_listWucha.AddString(strShow);
	int numList=m_listWucha.GetCount()-1;
//	GetDlgItem(IDC_BUTTON_CLEAR)->EnableWindow(true);
	m_listWucha.SetTopIndex(numList);
	m_listWucha.SetCurSel(numList);
	//水平滚动
	int max_width=0;
	CSize sz;
	CClientDC dc(this);
	for(int i=0;i<m_listWucha.GetCount();i++)
	{
		m_listWucha.GetText(i,strShow);
		sz=dc.GetTextExtent(strShow);
		if(max_width<sz.cx)
			max_width=sz.cx;
	}
	m_listWucha.SendMessage(LB_SETHORIZONTALEXTENT,max_width,0);
}
