// DataBase.cpp: implementation of the CDataBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "nodeplat.h"
#include "DataBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataBase::CDataBase()
{

}

CDataBase::~CDataBase()
{

}
//��ʼ�����ݿ⣬��conn
void CDataBase::InitDataBase()
{
	try
	{
		
		CoInitialize(NULL);		
		pConn.CreateInstance("ADODB.Connection");		
		pConn->ConnectionString="Provider=MSDASQL.1;Persist Security Info=False;User ID=sa;Data Source=MS Access Database;Initial Catalog=db\\Database.mdb";
		pConn->Open("","","",adConnectUnspecified);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	
	pRst.CreateInstance(__uuidof(Recordset));
}

//�ر����ݿ�
void CDataBase::ExitDataBase()
{
// 	if(pRst!=NULL)
// 		pRst->Close();
	if (pRst->GetState() == adStateOpen)
	{
		pRst->Close();
	}
	if (pRst)
	{
		pRst.Release();
		pRst = NULL;
	}
	if (pConn->GetState() == adStateOpen)
	{
		pConn->Close();
	}
	if (pConn)
	{
		pConn.Release();
		pConn = NULL;
	}
	CoUninitialize();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//***********            ��ȡ���ݿ��к�������������ֵ                                              *****//
//********                    (2014-18-17  Liuyian)                                           **********//
//********     ���룺��¼��pRst�����洢�õ������ݿ�����,pConn��ʾָ�������                   **********//
//********     �����m_DataBaseData���洢���ݿ��л�ȡ��������                                 **********//
void CDataBase::GetTrackThd()
{
	_bstr_t nTemp;
	m_DataBaseData.TrackThd.clear();
	pRst = pConn->Execute("select * from Track1 order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		nTemp = (_bstr_t)pRst->GetCollect("��ֵ");
		m_DataBaseData.TrackThd.push_back(atoi((const char*)nTemp));	
		pRst->MoveNext();
	}
	pRst->Close();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//***********            ��ȡ���ݿ���ESM����������ֵ                                              *****//
//********                    (2014-18-17  Liuyian)                                           **********//
//********     ���룺��¼��pRst�����洢�õ������ݿ�����,pConn��ʾָ�������                   **********//
//********     �����m_DataBaseData���洢���ݿ��л�ȡ��������                                 **********//
void CDataBase::GetESMThd()
{
	_bstr_t nTemp;
	m_DataBaseData.ESMThd.clear();
	pRst = pConn->Execute("select * from ESM1 order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		nTemp = (_bstr_t)pRst->GetCollect("��ֵ");
		m_DataBaseData.ESMThd.push_back(atoi((const char*)nTemp));	
		pRst->MoveNext();
	}
	pRst->Close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//***********            ��ȡ���ݿ���COM����������ֵ                                              *****//
//********                    (2014-18-17  Liuyian)                                           **********//
//********     ���룺��¼��pRst�����洢�õ������ݿ�����,pConn��ʾָ�������                   **********//
//********     �����m_DataBaseData���洢���ݿ��л�ȡ��������                                 **********//
void CDataBase::GetCOMThd()
{
	_bstr_t nTemp;
	m_DataBaseData.COMThd.clear();
	pRst = pConn->Execute("select * from COM1 order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		nTemp = (_bstr_t)pRst->GetCollect("��ֵ");
		m_DataBaseData.COMThd.push_back(atoi((const char*)nTemp));	
		pRst->MoveNext();
	}
	pRst->Close();
}


////////////////////////////////////////////////////////////////////////////////// ////////////////////////
//***********            ��ȡ���ݿ��к����¼���ֵ                                                   *****//
//********                    (2014-10-31  houtongzhang)                                       **********//
//********     ���룺��¼��pRst�����洢�õ������ݿ�����,pConn��ʾָ�������                    **********//
//********     �����m_DataBaseData���洢���ݿ��л�ȡ��������                                  **********//
void CDataBase::GetTrackEvent()
{
	_bstr_t nTemp;
	VCT_INT vctTemp;
	VV_INT::iterator iteEvent;
	//�������
	for (iteEvent = m_DataBaseData.vctDbTrackKng.begin(); iteEvent != m_DataBaseData.vctDbTrackKng.end(); ++iteEvent)
	{
		iteEvent->clear();
	}
	m_DataBaseData.vctDbTrackKng.clear();
//	iteEvent = m_DataBaseData.vctDbTrackKng.begin();
	pRst = pConn->Execute("select * from Track order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		vctTemp.clear();
		//֪ʶ
		nTemp = (_bstr_t)pRst->GetCollect("Rd");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("High");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("Speed");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("AddSpeed");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("Azimuth");
		vctTemp.push_back(atoi((const char*)nTemp));
		
		m_DataBaseData.vctDbTrackKng.push_back(vctTemp);
		//�¼����
		nTemp = (_bstr_t)pRst->GetCollect("ID");
		m_DataBaseData.ESMEventID.push_back(atoi((const char*)nTemp));
		//ģ���
		nTemp = (_bstr_t)pRst->GetCollect("BaseEvent");
		m_DataBaseData.ESMModelID.push_back(atoi((const char*)nTemp));
		
		pRst->MoveNext();
	}
	pRst->Close();
}


////////////////////////////////////////////////////////////////////////////////// ////////////////////////
//***********            ��ȡ���ݿ���ESM�¼���ֵ                                                   *****//
//********                    (2014-10-31  houtongzhang)                                       **********//
//********     ���룺��¼��pRst�����洢�õ������ݿ�����,pConn��ʾָ�������                    **********//
//********     �����m_DataBaseData���洢���ݿ��л�ȡ��������                                  **********//
void CDataBase::GetESMEvent()
{
	_bstr_t nTemp;
	VCT_INT vctTemp;
	VV_INT::iterator iteEvent;
	//�������
	vctTemp.clear();
	for (iteEvent = m_DataBaseData.vctDbESMKng.begin(); iteEvent != m_DataBaseData.vctDbESMKng.end(); ++iteEvent)
	{
		iteEvent->clear();
	}
	m_DataBaseData.vctDbESMKng.clear();

	iteEvent = m_DataBaseData.vctDbESMKng.begin();
	pRst = pConn->Execute("select * from ESM order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		vctTemp.clear();
		//֪ʶ
		nTemp = (_bstr_t)pRst->GetCollect("ESMPre");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("ESMPaw");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("ESMPwz");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("ESMPRIt");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("ESMScan");
		vctTemp.push_back(atoi((const char*)nTemp));

		m_DataBaseData.vctDbESMKng.push_back(vctTemp);
		//�¼����
		nTemp = (_bstr_t)pRst->GetCollect("ID");
		m_DataBaseData.ESMEventID.push_back(atoi((const char*)nTemp));
		//ģ���
		nTemp = (_bstr_t)pRst->GetCollect("BaseEvent");
		m_DataBaseData.ESMModelID.push_back(atoi((const char*)nTemp));
		pRst->MoveNext();
	}
	pRst->Close();
}

////////////////////////////////////////////////////////////////////////////////// ////////////////////////
//***********            ��ȡ���ݿ���COM�¼���ֵ                                                   *****//
//********                    (2014-10-31  houtongzhang)                                       **********//
//********     ���룺��¼��pRst�����洢�õ������ݿ�����,pConn��ʾָ�������                    **********//
//********     �����m_DataBaseData���洢���ݿ��л�ȡ��������                                  **********//
void CDataBase::GetCOMEvent()
{
	_bstr_t nTemp;
	VCT_INT vctTemp;
	VV_INT::iterator iteEvent;
	//�������
	for (iteEvent = m_DataBaseData.vctDbCOMKng.begin(); iteEvent != m_DataBaseData.vctDbCOMKng.end(); ++iteEvent)
	{
		iteEvent->clear();
	}
	m_DataBaseData.vctDbCOMKng.clear();

	iteEvent = m_DataBaseData.vctDbCOMKng.begin();
	pRst = pConn->Execute("select * from COM order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		vctTemp.clear();
		//֪ʶ
		nTemp = (_bstr_t)pRst->GetCollect("Pre");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("PAw");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("Hoop");
		vctTemp.push_back(atoi((const char*)nTemp));

		m_DataBaseData.vctDbCOMKng.push_back(vctTemp);
		//�¼����
		nTemp = (_bstr_t)pRst->GetCollect("ID");
		m_DataBaseData.ESMEventID.push_back(atoi((const char*)nTemp));
		//ģ���
		nTemp = (_bstr_t)pRst->GetCollect("BaseEvent");
		m_DataBaseData.ESMModelID.push_back(atoi((const char*)nTemp));
		pRst->MoveNext();
	}
	pRst->Close();
}


//��ȡ���ݿ��е�ƽ̨֪ʶ
void CDataBase::GetPlatEvent()
{
	_bstr_t nTemp;
	VCT_INT vctTemp;
	VV_INT::iterator iteEvent;
	//�������
	for (iteEvent = m_DataBaseData.vctDbPlatKng.begin(); iteEvent != m_DataBaseData.vctDbPlatKng.end(); ++iteEvent)
	{
		iteEvent->clear();
	}
	m_DataBaseData.vctDbPlatKng.clear();
	
	iteEvent = m_DataBaseData.vctDbPlatKng.begin();
	pRst = pConn->Execute("select * from ƽ̨̬�� order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		vctTemp.clear();
		//֪ʶ
		nTemp = (_bstr_t)pRst->GetCollect("Rd");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("High");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("Speed");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("AddSpeed");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("Azimuth");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("Track�����¼�");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("ESM�����¼�");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("COM�����¼�");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("Ŀ������");
		vctTemp.push_back(atoi((const char*)nTemp));

		
		m_DataBaseData.vctDbPlatKng.push_back(vctTemp);
		//�¼����
		nTemp = (_bstr_t)pRst->GetCollect("ID");
		m_DataBaseData.PlatEventID.push_back(atoi((const char*)nTemp));
		//ģ���
		nTemp = (_bstr_t)pRst->GetCollect("ƽ̨̬��");
		m_DataBaseData.PlatModelID.push_back(atoi((const char*)nTemp));
		pRst->MoveNext();
	}
	pRst->Close();
}


//��ȡ���ݿ��еĿռ�Ⱥ֪ʶ
void CDataBase::GetSpaceGroup()
{
	_bstr_t nTemp;
	VCT_INT vctTemp;
	VV_INT::iterator iteEvent;
	//�������
	for (iteEvent = m_DataBaseData.vctDbSpaceKng.begin(); iteEvent != m_DataBaseData.vctDbSpaceKng.end(); ++iteEvent)
	{
		iteEvent->clear();
	}
	m_DataBaseData.vctDbSpaceKng.clear();
	
	iteEvent = m_DataBaseData.vctDbSpaceKng.begin();
	pRst = pConn->Execute("select * from �ռ�Ⱥ order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		vctTemp.clear();
		//֪ʶ
		nTemp = (_bstr_t)pRst->GetCollect("ObjType");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("Distance");
		vctTemp.push_back(atoi((const char*)nTemp));
		m_DataBaseData.vctDbSpaceKng.push_back(vctTemp);
		//�¼����
		nTemp = (_bstr_t)pRst->GetCollect("ID");
		m_DataBaseData.SpaceGrpID.push_back(atoi((const char*)nTemp));
		pRst->MoveNext();
	}
	pRst->Close();
}

//��ȡ���ݿ��еĹ���Ⱥ֪ʶ
void CDataBase::GetFuncGroup()
{
	_bstr_t nTemp;
	VCT_INT vctTemp;
	VV_INT::iterator iteEvent;
	//�������
	for (iteEvent = m_DataBaseData.vctDbFunKng.begin(); iteEvent != m_DataBaseData.vctDbFunKng.end(); ++iteEvent)
	{
		iteEvent->clear();
	}
	m_DataBaseData.vctDbFunKng.clear();
	
	iteEvent = m_DataBaseData.vctDbFunKng.begin();
	pRst = pConn->Execute("select * from ����Ⱥ order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		vctTemp.clear();
		//֪ʶ
		nTemp = (_bstr_t)pRst->GetCollect("Ⱥ����");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("ƽ̨̬��");
		vctTemp.push_back(atoi((const char*)nTemp));
		m_DataBaseData.vctDbFunKng.push_back(vctTemp);
		//�¼����
		nTemp = (_bstr_t)pRst->GetCollect("ID");
		m_DataBaseData.FunEventID.push_back(atoi((const char*)nTemp));
		//ģ���
		nTemp = (_bstr_t)pRst->GetCollect("�����¼�");
		m_DataBaseData.FunModelID.push_back(atoi((const char*)nTemp));
		pRst->MoveNext();
	}
	pRst->Close();
}


//��ȡ���ݿ��е��໥����Ⱥ֪ʶ
void CDataBase::GetInterGroup()
{
	_bstr_t nTemp;
	VCT_INT vctTemp;
	VV_INT::iterator iteEvent;
	//�������
	for (iteEvent = m_DataBaseData.vctDbInterKng.begin(); iteEvent != m_DataBaseData.vctDbInterKng.end(); ++iteEvent)
	{
		iteEvent->clear();
	}
	m_DataBaseData.vctDbInterKng.clear();
	
	iteEvent = m_DataBaseData.vctDbInterKng.begin();
	pRst = pConn->Execute("select * from �໥����Ⱥ order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		vctTemp.clear();
		//֪ʶ
		nTemp = (_bstr_t)pRst->GetCollect("����");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("Ѳ��");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("����");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("����");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("��ը");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("ͻ��");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("����");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("Ԥ��");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("���");
		vctTemp.push_back(atoi((const char*)nTemp));
		m_DataBaseData.vctDbInterKng.push_back(vctTemp);
		//�¼����
		nTemp = (_bstr_t)pRst->GetCollect("ID");
		m_DataBaseData.InterModelID.push_back(atoi((const char*)nTemp));

		pRst->MoveNext();
	}
	pRst->Close();
}