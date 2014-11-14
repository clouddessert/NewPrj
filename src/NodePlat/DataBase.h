// DataBase.h: interface for the CDataBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASE_H__3F2BE357_C6E9_4683_A0FF_0FA618E9692C__INCLUDED_)
#define AFX_DATABASE_H__3F2BE357_C6E9_4683_A0FF_0FA618E9692C__INCLUDED_
#include "stdafx.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "StdAfx.h"
class CDataBase  
{
public:
	//���ݿ�
	DB_DATA m_DataBaseData;             //������������ݿ��ȡ������
	_RecordsetPtr pRst;					//��ʱ�����ݼ�
	_ConnectionPtr pConn;				//���ݿ�����
	
public:
	
	CDataBase();
	virtual ~CDataBase();
	void InitDataBase();
	void ExitDataBase();
	void GetTrackThd();
	void GetESMThd();
	void GetCOMThd();
	void GetTrackEvent();
	void GetESMEvent();
	void GetCOMEvent();
	void GetPlatEvent();
	void GetSpaceGroup();
	void GetFuncGroup();
	void GetInterGroup();
};

#endif // !defined(AFX_DATABASE_H__3F2BE357_C6E9_4683_A0FF_0FA618E9692C__INCLUDED_)
