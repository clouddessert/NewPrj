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
	VCT_SHIP_POSITION m_Ship_Position;

	//输入结构体
	ALL_MSG_INPUT m_RecvMsg;
	VCT_SHIP_POSITION m_SPosition;

	//输入请求信息
// 	Request_Cooperative_Msg m_RecvReqMsg;  //结构体 报文头中的信息长度就是容器的大小,即结构体的个数
// 
//     VCT_SendRequest_Msg m_SendReqMsg_Dat;    //请求信息，由多个结构体组成的容器(已经转成含有数组的容器)
// 	VCT_SendRequest_Msg m_RecvReqMsg_Dat;    //接收请求信息
// 
// 	VCT_SendBack_Msg m_SendBackMsg_Dat;      //返回信息
// 	VCT_SendBack_Msg m_RecvBackMsg_Dat;      //接收返回信息

	//信息交互结构体
	Request_Cooperative_Msg m_StRequest;      //保存联合识别前此批号的本舰信息

	SendRequest_Msg m_StSendRequest;          //发送请求的结构体
	SendRequest_Msg m_StReceiveRequest;       //接收请求的结构体

	SendBack_Msg m_SendBackMsg;               //发送返回信息
	SendBack_Msg m_ReceiveBackMsg;               //接收返回信息
	
	//消息类型
	unsigned char cMsgType;	//5 所有信息请求，Track,Esm,Com

	//输出指针	//输出:聚类编批结果

	//输出:编批结果
	VCT_ESM_MSG m_ESM;
	VCT_COMM_MSG m_Comm;
	VCT_TRACE_MSG m_Trace;

	//输出:聚类结果

	VCT_UNINUM_MSG m_ClusterUniMsg;//有航迹
	VCT_UNINOTRACE_MSG m_ClusterNoTraceMsg;//无航迹
	
	//输出:未聚类结果
	VCT_TRACE_MSG m_SingleTrace;
	VCT_ESM_MSG m_SingleEsm;
	VCT_COMM_MSG m_SingleComm;
	
	//输出:单舰识别结果
	VCT_IDENTIINFOR_MSG m_IdentifyMsg;

	//请求行号
	int m_iline;

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
	HWND hMulOut_wnd;
	//多舰
	HWND hMulESM_wmd;
	HWND hMulCOMM_wnd;
	HWND hMulTRACE_wnd;


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
