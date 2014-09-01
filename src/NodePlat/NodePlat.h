// NodePlat.h : main header file for the NODEPLAT application
//

#if !defined(AFX_NODEPLAT_H__35ECCD2C_1DA6_4922_A062_1BF67E09DB35__INCLUDED_)
#define AFX_NODEPLAT_H__35ECCD2C_1DA6_4922_A062_1BF67E09DB35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "MsgSocket.h"
#include "MySocket.h"
/////////////////////////////////////////////////////////////////////////////
// CNodePlatApp:
// See NodePlat.cpp for the implementation of this class
//

class CNodePlatApp : public CWinApp
{
public:
	CNodePlatApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNodePlatApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

public:
	CRITICAL_SECTION g_cs;				// 临界区结构对象
	
	VCT_ESM_MSG m_ESM_Dat;
	VCT_COMM_MSG m_Comm_Dat;
	VCT_TRACE_MSG m_Trace_Dat;

	//输入结构体
	ALL_MSG_INPUT m_RecvMsg;

	//输出指针
	VCT_IDENTIINFOR_MSG* pOutPt;

	//p2p socket
	CMsgSocket* m_P2PSocket;

	//客户端
	CMySocket* pClient;
	//客户端指针
	map<DWORD, CMySocket*> m_ClientMap;
	map<DWORD, CMySocket*>::iterator m_pClient;

public:
	HWND hESM_wmd;
	HWND hCOMM_wmd;
	HWND hTRACE_wmd;
	HWND hSigOut_wnd;

	//view的指针
	void* pXview;

private:
	void ServerCreate(void);
	void ServerShutDown(void);

public:
	void ClientAccept(void);
	void ClientClose(void* pContext);

	void ReceiveFromClient(void);
	void SendToClient(void);

// Implementation
	//{{AFX_MSG(CNodePlatApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NODEPLAT_H__35ECCD2C_1DA6_4922_A062_1BF67E09DB35__INCLUDED_)
