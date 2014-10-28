// EvaluDlg.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "EvaluDlg.h"
#include "ZDIdenti.h"
#include "QBIdenti.h"
#include "ZDIdentiGraph.h"
#include "QBIdentiGraph.h"
#include "ZDFus.h"
#include "QBFus.h"
#include "ZDFusGraph.h"
#include "QBFusGraph.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEvaluDlg dialog


CEvaluDlg::CEvaluDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEvaluDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEvaluDlg)
	m_pihao = 0;
	//}}AFX_DATA_INIT
	l = 0;
	f = 0;
}


void CEvaluDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEvaluDlg)
	DDX_Control(pDX, IDC_COMBO_LEIBIE, m_ctrLB);
	DDX_Control(pDX, IDC_COMBO_FANGSHI, m_ctrFS);
	DDX_Text(pDX, IDC_EDIT_PIHAO, m_pihao);
	DDV_MinMaxLong(pDX, m_pihao, 0, 10000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEvaluDlg, CDialog)
	//{{AFX_MSG_MAP(CEvaluDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_FANGSHI, OnSelchangeComboFangshi)
	ON_BN_CLICKED(IDC_RADIO_BIAOGE, OnRadioBiaoge)
	ON_BN_CLICKED(IDC_RADIO_TUXING, OnRadioTuxing)
	ON_CBN_SELCHANGE(IDC_COMBO_LEIBIE, OnSelchangeComboLeibie)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEvaluDlg message handlers
BOOL CEvaluDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctrLB.SetCurSel(0);
	m_ctrFS.SetCurSel(0);
	CButton *pBtn1=(CButton *)GetDlgItem(IDC_RADIO_TUXING);
	pBtn1->SetCheck(true);
	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEvaluDlg::FindLocData(int autonum, int &count, double &l_bzc, double &b_bzc)
{
// 	if (autonum>8199&&autonum<8500)	// esm
// 	{
// 		for(int i=0;i<count_esm;i++)
// 		{
// 			if ((int)p[i][32]==autonum) 
// 			{
// 				count = (int)p[i][40];
// 				l_bzc = p[i][43];
// 				b_bzc = p[i][44];
// 			}
// 		}
// 	}
// 	if (autonum>8499&&autonum<8800)	// com
// 	{
// 		for(int i=0;i<count_com;i++)
// 		{
// 			if ((int)c[i][48]==autonum) 
// 			{
// 				count = (int)c[i][50];
// 				l_bzc = c[i][53];
// 				b_bzc = c[i][54];
// 			}
// 		}
// 	}		
}

void CEvaluDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	l = m_ctrLB.GetCurSel();
	f = m_ctrFS.GetCurSel();

	
	CButton *pBtn1=(CButton *)GetDlgItem(IDC_RADIO_BIAOGE);
	CButton *pBtn2=(CButton *)GetDlgItem(IDC_RADIO_TUXING);
	
	{
		if(l==0&&f==0)  //ʶ�𾫶�+ָ������ (����ͼ����ʾ)
		{  
 			if(!checkDB(m_pihao,0)) //���źͱ�־ flag=0 ����ʶ��
 			{
				AfxMessageBox("ָ�����Ų�����!"); 		
				return;
			}
			if (pBtn2->GetCheck())
			{
				//ָ��ʶ�𾫶�ͼ����ʾ ͼ����
				CString strUnum;
                CString real_ty;
				CString real_platt;
				CString p_query;
				CString tmp;
				OpenIdentiDb();
				CRecordset mrd(&m_dbidenti);
				strUnum.Format("%d",m_pihao);
				p_query.Format("select * from %s",strUnum);
				if(!mrd.Open(CRecordset::forwardOnly,p_query,CRecordset::readOnly))
					AfxMessageBox("No RD!");
				while(!mrd.IsEOF())
				{
					mrd.GetFieldValue("real_ty",tmp);
					real_ty=tmp;					
					// mrd.GetFieldValue("Real_platt",tmp);
					// real_platt=tmp;
					mrd.MoveNext();
				}
				mrd.Close();
				m_dbidenti.Close();
				CZDIdentiGraph dlg;
				CDialog::OnOK();
				dlg.num = m_pihao;
				dlg.real_plattye = real_ty;
				dlg.DoModal();
			}
			else
			{   //ָ��ʶ�𾫶ȱ����ʾ
				CString strUnum;
                CString real_ty;
				CString real_platt;
				CString p_query;
				CString tmp;
				OpenIdentiDb();
				CRecordset mrd(&m_dbidenti);
				strUnum.Format("%d",m_pihao);
				p_query.Format("select * from %s",strUnum);
				if(!mrd.Open(CRecordset::forwardOnly,p_query,CRecordset::readOnly))
					AfxMessageBox("No RD!");
				while(!mrd.IsEOF())
				{
					mrd.GetFieldValue("real_ty",tmp);
					real_ty=tmp;					
                   // mrd.GetFieldValue("Real_platt",tmp);
                   // real_platt=tmp;
					mrd.MoveNext();
				}
				mrd.Close();
				m_dbidenti.Close();
				
				CZDIdenti dlg; 
				CDialog::OnOK();
				dlg.num = m_pihao;
				dlg.real_plattye = real_ty;
				dlg.DoModal();
			}

		}
		if (l==0&&f==1) //ʶ�𾫶�+ȫ������ (����ͼ����ʾ)
		{
			if (pBtn2->GetCheck())
			{
				//ȫ��ʶ�𾫶�ͼ����ʾ ͼ����
				CQBIdentiGraph dlg;
				CDialog::OnOK();
				dlg.DoModal();
			}
			else
			{   //ȫ��ʶ�𾫶ȱ����ʾ
				CQBIdenti dlg; 
				CDialog::OnOK();
				dlg.DoModal();
			}

		}
		if(l==1&&f==0)//�ںϾ���+ָ������(����ͼ����ʾ)
		{
			if (pBtn2->GetCheck())
			{
				//ָ���ںϾ���ͼ����ʾ ͼ����
				CZDFusGraph dlg;
				if(!checkDB(m_pihao,0)) //���źͱ�־ flag=0 ����ʶ��
				{
					AfxMessageBox("ָ�����Ų�����!"); 		
					return;
				}
//				int count_loc(0);
//				double a_bzc(0.0),e_bzc(0.0);
			//	((CEvaluDlg*)GetParent())->FindLocData(m_pihao,count_loc,a_bzc,e_bzc);
// 				if (count_loc>330)
// 				{
// 					dlg.count_factor =3;
// 				}
// 				if (a_bzc>0.12)
// 				{
// 					dlg.a_factor = 2;
// 				}
// 				if (a_bzc>0.24)
// 				{
// 					dlg.a_factor = 4;
// 				}
// 				if (e_bzc>0.12) 
// 				{
// 					dlg.e_factor = 2;
// 				}
// 				if (e_bzc>0.24) 
// 				{
// 					dlg.e_factor = 4;
// 				}
				dlg.num = m_pihao;
				CDialog::OnOK();
				dlg.DoModal();
			}
			else
			{   //ָ���ںϾ��ȱ����ʾ
				CZDFus dlg; 
				if(!checkDB(m_pihao,0)) //���źͱ�־ flag=0 ����ʶ��
				{
					AfxMessageBox("ָ�����Ų�����!"); 		
					return;
				}
				dlg.num = m_pihao;
				CDialog::OnOK();
				dlg.DoModal();
			}

		}
		if(l==1&&f==1)//�ںϾ���+ȫ������(����ͼ����ʾ)
		{
			if (pBtn2->GetCheck())
			{
				//ȫ���ںϾ���ͼ����ʾ ͼ����
				CQBFusGraph dlg;
				CDialog::OnOK();
				dlg.DoModal();
			}
			else
			{   //ȫ���ںϾ��ȱ����ʾ
				CQBFus dlg; 
				CDialog::OnOK();
				dlg.DoModal();
			}
		}
	}
	CDialog::OnOK();
}

void CEvaluDlg::OnSelchangeComboFangshi() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	l = m_ctrLB.GetCurSel();
	f = m_ctrFS.GetCurSel();
	if(l==0&&f==0) // ʶ������,ָ������
	{
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PIHAO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_BIAOGE)->ShowWindow(SW_SHOW);  //�����ʾ
		GetDlgItem(IDC_RADIO_TUXING)->ShowWindow(SW_SHOW);  //����ʾͼ��
	}
	if (l==0&&f==1) //ʶ������,ȫ������
	{
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PIHAO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO_BIAOGE)->ShowWindow(SW_SHOW); //�����ʾ
		GetDlgItem(IDC_RADIO_TUXING)->ShowWindow(SW_SHOW); //����ʾͼ��	
	}
	if (l==1&&f==1) //�ں�����,ȫ������
	{
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PIHAO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO_BIAOGE)->ShowWindow(SW_HIDE); //����ʾ���
		GetDlgItem(IDC_RADIO_TUXING)->ShowWindow(SW_HIDE); //����ʾͼ��
	}
	if (l==1&&f==0) //�ں�����,ָ������
	{
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PIHAO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_BIAOGE)->ShowWindow(SW_HIDE); //����ʾ���
		GetDlgItem(IDC_RADIO_TUXING)->ShowWindow(SW_SHOW); //ͼ����ʾ
	}		
}

void CEvaluDlg::OnRadioBiaoge() 
{
	// TODO: Add your control notification handler code here
	
}

void CEvaluDlg::OnRadioTuxing() 
{
	// TODO: Add your control notification handler code here
	
}

bool CEvaluDlg::checkDB(int num,int flag)  //�����ݿ�, �ۺ�����num, flag = 0 ����ʶ��,flag = 1�����ں�
{
	if (flag == 0) //ʶ��
	{
		OpenIdentiDb();
		CString p_query;
		CString str;
		str.Format("%d",num);
		p_query.Format("select Name from MSysObjects where Name = \'%s\'",str);
		CRecordset m_dbset(&m_dbidenti);
		CString strSQL;
		if(!m_dbset.Open(CRecordset::dynaset,p_query,CRecordset::readOnly))
			AfxMessageBox("No RD!");
		if (!m_dbset.GetRecordCount()) 
		{
			m_dbset.Close();
			m_dbidenti.Close();
			return 0;
		}
		else
		{
			m_dbset.Close();
			m_dbidenti.Close();
			return 1;
		}
	}
	else //if (flag == 1) //�ں�
	{
		OpenFusDb();
		CString p_query;
		CString str;
		str.Format("%d",num);
		p_query.Format("select Name from MSysObjects where Name = \'%s\'",str);
		CRecordset m_dbset(&m_dbfus);
		CString strSQL;
		if(!m_dbset.Open(CRecordset::dynaset,p_query,CRecordset::readOnly))
			AfxMessageBox("No RD!");
		if (!m_dbset.GetRecordCount()) 
		{
			m_dbset.Close();
			m_dbfus.Close();
			return 0;
		}
		else
		{
			m_dbset.Close();
			m_dbfus.Close();
			return 1;
		}
	}	
	return 0;
}

void CEvaluDlg::OnSelchangeComboLeibie() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	l = m_ctrLB.GetCurSel();
	f = m_ctrFS.GetCurSel();
	if(l==0&&f==0)
	{
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PIHAO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_BIAOGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_TUXING)->ShowWindow(SW_SHOW);
	}
	if (l==0&&f==1)
	{
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PIHAO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO_BIAOGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_TUXING)->ShowWindow(SW_SHOW);	
	}
	if (l==1&&f==1)
	{
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PIHAO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO_BIAOGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO_TUXING)->ShowWindow(SW_HIDE);
	}
	if (l==1&&f==0)
	{
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PIHAO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_BIAOGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO_TUXING)->ShowWindow(SW_SHOW);
	}		
}

void CEvaluDlg::OpenFusDb()
{
	CString strDriver = "MICROSOFT ACCESS DRIVER (*.mdb)";
	CString strDsn;
	char strFile[1024];
	GetCurrentDirectory(1024, strFile);
	strcat(strFile, "\\DB\\Fusion.mdb\0");
	strDsn.Format("ODBC;DRIVER={%s};UID=sa;PWD=;DBQ=%s",strDriver,strFile);
	m_dbfus.Open(NULL,false,false,strDsn,false);
				
}

void CEvaluDlg::OpenIdentiDb()  //ʶ��
{
	CString strDriver = "MICROSOFT ACCESS DRIVER (*.mdb)";
	CString strDsn;
	char strFile[1024];
	GetCurrentDirectory(1024, strFile);
	strcat(strFile, "\\DB\\Identi.mdb\0");
	strDsn.Format("ODBC;DRIVER={%s};UID=sa;PWD=;DBQ=%s",strDriver,strFile);
	m_dbidenti.Open(NULL,false,false,strDsn,false);

}

