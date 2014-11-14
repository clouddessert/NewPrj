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
//初始化数据库，打开conn
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

//关闭数据库
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
//***********            读取数据库中航迹各变量的阈值                                              *****//
//********                    (2014-18-17  Liuyian)                                           **********//
//********     输入：记录集pRst用来存储得到的数据库数据,pConn表示指向的连接                   **********//
//********     输出：m_DataBaseData，存储数据库中获取到的数据                                 **********//
void CDataBase::GetTrackThd()
{
	_bstr_t nTemp;
	m_DataBaseData.TrackThd.clear();
	pRst = pConn->Execute("select * from Track1 order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		nTemp = (_bstr_t)pRst->GetCollect("阈值");
		m_DataBaseData.TrackThd.push_back(atoi((const char*)nTemp));	
		pRst->MoveNext();
	}
	pRst->Close();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//***********            读取数据库中ESM各变量的阈值                                              *****//
//********                    (2014-18-17  Liuyian)                                           **********//
//********     输入：记录集pRst用来存储得到的数据库数据,pConn表示指向的连接                   **********//
//********     输出：m_DataBaseData，存储数据库中获取到的数据                                 **********//
void CDataBase::GetESMThd()
{
	_bstr_t nTemp;
	m_DataBaseData.ESMThd.clear();
	pRst = pConn->Execute("select * from ESM1 order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		nTemp = (_bstr_t)pRst->GetCollect("阈值");
		m_DataBaseData.ESMThd.push_back(atoi((const char*)nTemp));	
		pRst->MoveNext();
	}
	pRst->Close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//***********            读取数据库中COM各变量的阈值                                              *****//
//********                    (2014-18-17  Liuyian)                                           **********//
//********     输入：记录集pRst用来存储得到的数据库数据,pConn表示指向的连接                   **********//
//********     输出：m_DataBaseData，存储数据库中获取到的数据                                 **********//
void CDataBase::GetCOMThd()
{
	_bstr_t nTemp;
	m_DataBaseData.COMThd.clear();
	pRst = pConn->Execute("select * from COM1 order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		nTemp = (_bstr_t)pRst->GetCollect("阈值");
		m_DataBaseData.COMThd.push_back(atoi((const char*)nTemp));	
		pRst->MoveNext();
	}
	pRst->Close();
}


////////////////////////////////////////////////////////////////////////////////// ////////////////////////
//***********            读取数据库中航迹事件的值                                                   *****//
//********                    (2014-10-31  houtongzhang)                                       **********//
//********     输入：记录集pRst用来存储得到的数据库数据,pConn表示指向的连接                    **********//
//********     输出：m_DataBaseData，存储数据库中获取到的数据                                  **********//
void CDataBase::GetTrackEvent()
{
	_bstr_t nTemp;
	VCT_INT vctTemp;
	VV_INT::iterator iteEvent;
	//清空数据
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
		//知识
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
		//事件编号
		nTemp = (_bstr_t)pRst->GetCollect("ID");
		m_DataBaseData.ESMEventID.push_back(atoi((const char*)nTemp));
		//模板号
		nTemp = (_bstr_t)pRst->GetCollect("BaseEvent");
		m_DataBaseData.ESMModelID.push_back(atoi((const char*)nTemp));
		
		pRst->MoveNext();
	}
	pRst->Close();
}


////////////////////////////////////////////////////////////////////////////////// ////////////////////////
//***********            读取数据库中ESM事件的值                                                   *****//
//********                    (2014-10-31  houtongzhang)                                       **********//
//********     输入：记录集pRst用来存储得到的数据库数据,pConn表示指向的连接                    **********//
//********     输出：m_DataBaseData，存储数据库中获取到的数据                                  **********//
void CDataBase::GetESMEvent()
{
	_bstr_t nTemp;
	VCT_INT vctTemp;
	VV_INT::iterator iteEvent;
	//清空数据
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
		//知识
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
		//事件编号
		nTemp = (_bstr_t)pRst->GetCollect("ID");
		m_DataBaseData.ESMEventID.push_back(atoi((const char*)nTemp));
		//模板号
		nTemp = (_bstr_t)pRst->GetCollect("BaseEvent");
		m_DataBaseData.ESMModelID.push_back(atoi((const char*)nTemp));
		pRst->MoveNext();
	}
	pRst->Close();
}

////////////////////////////////////////////////////////////////////////////////// ////////////////////////
//***********            读取数据库中COM事件的值                                                   *****//
//********                    (2014-10-31  houtongzhang)                                       **********//
//********     输入：记录集pRst用来存储得到的数据库数据,pConn表示指向的连接                    **********//
//********     输出：m_DataBaseData，存储数据库中获取到的数据                                  **********//
void CDataBase::GetCOMEvent()
{
	_bstr_t nTemp;
	VCT_INT vctTemp;
	VV_INT::iterator iteEvent;
	//清空数据
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
		//知识
		nTemp = (_bstr_t)pRst->GetCollect("Pre");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("PAw");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("Hoop");
		vctTemp.push_back(atoi((const char*)nTemp));

		m_DataBaseData.vctDbCOMKng.push_back(vctTemp);
		//事件编号
		nTemp = (_bstr_t)pRst->GetCollect("ID");
		m_DataBaseData.ESMEventID.push_back(atoi((const char*)nTemp));
		//模板号
		nTemp = (_bstr_t)pRst->GetCollect("BaseEvent");
		m_DataBaseData.ESMModelID.push_back(atoi((const char*)nTemp));
		pRst->MoveNext();
	}
	pRst->Close();
}


//读取数据库中的平台知识
void CDataBase::GetPlatEvent()
{
	_bstr_t nTemp;
	VCT_INT vctTemp;
	VV_INT::iterator iteEvent;
	//清空数据
	for (iteEvent = m_DataBaseData.vctDbPlatKng.begin(); iteEvent != m_DataBaseData.vctDbPlatKng.end(); ++iteEvent)
	{
		iteEvent->clear();
	}
	m_DataBaseData.vctDbPlatKng.clear();
	
	iteEvent = m_DataBaseData.vctDbPlatKng.begin();
	pRst = pConn->Execute("select * from 平台态势 order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		vctTemp.clear();
		//知识
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
		nTemp = (_bstr_t)pRst->GetCollect("Track基本事件");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("ESM基本事件");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("COM基本事件");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("目标类型");
		vctTemp.push_back(atoi((const char*)nTemp));

		
		m_DataBaseData.vctDbPlatKng.push_back(vctTemp);
		//事件编号
		nTemp = (_bstr_t)pRst->GetCollect("ID");
		m_DataBaseData.PlatEventID.push_back(atoi((const char*)nTemp));
		//模板号
		nTemp = (_bstr_t)pRst->GetCollect("平台态势");
		m_DataBaseData.PlatModelID.push_back(atoi((const char*)nTemp));
		pRst->MoveNext();
	}
	pRst->Close();
}


//读取数据库中的空间群知识
void CDataBase::GetSpaceGroup()
{
	_bstr_t nTemp;
	VCT_INT vctTemp;
	VV_INT::iterator iteEvent;
	//清空数据
	for (iteEvent = m_DataBaseData.vctDbSpaceKng.begin(); iteEvent != m_DataBaseData.vctDbSpaceKng.end(); ++iteEvent)
	{
		iteEvent->clear();
	}
	m_DataBaseData.vctDbSpaceKng.clear();
	
	iteEvent = m_DataBaseData.vctDbSpaceKng.begin();
	pRst = pConn->Execute("select * from 空间群 order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		vctTemp.clear();
		//知识
		nTemp = (_bstr_t)pRst->GetCollect("ObjType");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("Distance");
		vctTemp.push_back(atoi((const char*)nTemp));
		m_DataBaseData.vctDbSpaceKng.push_back(vctTemp);
		//事件编号
		nTemp = (_bstr_t)pRst->GetCollect("ID");
		m_DataBaseData.SpaceGrpID.push_back(atoi((const char*)nTemp));
		pRst->MoveNext();
	}
	pRst->Close();
}

//读取数据库中的功能群知识
void CDataBase::GetFuncGroup()
{
	_bstr_t nTemp;
	VCT_INT vctTemp;
	VV_INT::iterator iteEvent;
	//清空数据
	for (iteEvent = m_DataBaseData.vctDbFunKng.begin(); iteEvent != m_DataBaseData.vctDbFunKng.end(); ++iteEvent)
	{
		iteEvent->clear();
	}
	m_DataBaseData.vctDbFunKng.clear();
	
	iteEvent = m_DataBaseData.vctDbFunKng.begin();
	pRst = pConn->Execute("select * from 功能群 order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		vctTemp.clear();
		//知识
		nTemp = (_bstr_t)pRst->GetCollect("群类型");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("平台态势");
		vctTemp.push_back(atoi((const char*)nTemp));
		m_DataBaseData.vctDbFunKng.push_back(vctTemp);
		//事件编号
		nTemp = (_bstr_t)pRst->GetCollect("ID");
		m_DataBaseData.FunEventID.push_back(atoi((const char*)nTemp));
		//模板号
		nTemp = (_bstr_t)pRst->GetCollect("功能事件");
		m_DataBaseData.FunModelID.push_back(atoi((const char*)nTemp));
		pRst->MoveNext();
	}
	pRst->Close();
}


//读取数据库中的相互作用群知识
void CDataBase::GetInterGroup()
{
	_bstr_t nTemp;
	VCT_INT vctTemp;
	VV_INT::iterator iteEvent;
	//清空数据
	for (iteEvent = m_DataBaseData.vctDbInterKng.begin(); iteEvent != m_DataBaseData.vctDbInterKng.end(); ++iteEvent)
	{
		iteEvent->clear();
	}
	m_DataBaseData.vctDbInterKng.clear();
	
	iteEvent = m_DataBaseData.vctDbInterKng.begin();
	pRst = pConn->Execute("select * from 相互作用群 order by ID desc ",NULL,adCmdText);
	while(!pRst->adoEOF)
	{
		vctTemp.clear();
		//知识
		nTemp = (_bstr_t)pRst->GetCollect("警戒");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("巡逻");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("攻击");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("拦截");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("轰炸");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("突防");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("干扰");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("预警");
		vctTemp.push_back(atoi((const char*)nTemp));
		nTemp = (_bstr_t)pRst->GetCollect("侦查");
		vctTemp.push_back(atoi((const char*)nTemp));
		m_DataBaseData.vctDbInterKng.push_back(vctTemp);
		//事件编号
		nTemp = (_bstr_t)pRst->GetCollect("ID");
		m_DataBaseData.InterModelID.push_back(atoi((const char*)nTemp));

		pRst->MoveNext();
	}
	pRst->Close();
}