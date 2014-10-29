// CommandPlat.h : main header file for the COMMANDPLAT application
//

#if !defined(AFX_COMMANDPLAT_H__C6C8D05C_A37A_42A2_B4FE_39A5E132D4E8__INCLUDED_)
#define AFX_COMMANDPLAT_H__C6C8D05C_A37A_42A2_B4FE_39A5E132D4E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "MySocket.h"

typedef struct _ST_ALL_MSG
{
	VCT_ESM_MSG m_ESM_Dat;
	VCT_COMM_MSG m_Comm_Dat;
	VCT_TRACE_MSG m_Trace_Dat;	
}ST_ALL_MSG;

/////////////////////////////////////////////////////////////////////////////
// CCommandPlatApp:
// See CommandPlat.cpp for the implementation of this class
//

class CCommandPlatApp : public CWinApp
{
public:
	CCommandPlatApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommandPlatApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

public:
	//线程运行标志
	BOOL bThreadRun;

	//客户端
	CMySocket* pClient;
	//Listen端
	CMySocket* pSvr;
	//客户端指针
	map<DWORD, CMySocket*> m_ClientMap;
	map<DWORD, CMySocket*>::iterator m_pClient;
	
	// 临界区结构对象
	CRITICAL_SECTION g_cs;
	//数据更新事件
	HANDLE hUpdateDataEvent;

	//消息类型
	unsigned char cMsgType;	//1、ESM，后面继续

	//新增加的事件
	vector<CString> m_NewMessage;

	//信息指针
	void* pMsgFm;

	//数据
	VCT_ESM_MSG m_ESM_Dat;
	VCT_COMM_MSG m_Comm_Dat;
	VCT_TRACE_MSG m_Trace_Dat;
	VCT_SHIP_POSITION m_Ship_Position;
	VCT_SHIP_POSITION::iterator p_CurrentShip;

	std::map<DWORD, SHIP_POSITION>	m_ShipRelatePlat;

	std::map<DWORD, ST_ALL_MSG>	m_AllShipMsg;

public:
	HWND hESM_wmd;
	HWND hCOMM_wmd;
	HWND hTRACE_wmd;

public:
	void ServerCreate(void);
	void ServerShutDown(void);
	void ClientAccept(void);
	void ClientMsgReceive(void);
	void ClientClose(void* pContext);

// Implementation
	//{{AFX_MSG(CCommandPlatApp)
	afx_msg void OnAppAbout();
	afx_msg void OnShowMsg();
	afx_msg void OnStartJq();
	afx_msg void OnStopJq();
	afx_msg void OnRadarLib();
	afx_msg void OnTargetLib();
	afx_msg void OnCreateSt();
	afx_msg void OnChioseSt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDPLAT_H__C6C8D05C_A37A_42A2_B4FE_39A5E132D4E8__INCLUDED_)
