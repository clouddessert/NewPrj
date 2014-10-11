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

	//本舰编号
	int m_ThisNumber;

	//输入结构体
	ALL_MSG_INPUT m_RecvMsg;
	VCT_SHIP_POSITION m_SPosition;

	//输入请求信息
// 	Request_Cooperative_Msg m_RecvReqMsg;  //结构体 报文头中的信息长度就是容器的大小,即结构体的个数
// 
//    VCT_SendRequest_Msg m_SendReqMsg_Dat;    //请求信息，由多个结构体组成的容器(已经转成含有数组的容器)
 	VCT_SendRequest_Msg m_RecvReqMsg_Dat;    //接收请求信息
// 
// 	VCT_SendBack_Msg m_SendBackMsg_Dat;      //返回匹配信息
 	VCT_SendBack_Msg m_RecvBackMsg_Dat;      //接收返回信息

	//信息交互结构体
	SendRequest_Msg m_StSendRequest;          //发送请求的结构体
	SendRequest_Msg m_StReceiveRequest;       //接收请求的结构体

	SendBack_Msg m_SendBackMsg;               //发送返回信息
	SendBack_Msg m_ReceiveBackMsg;               //接收返回信息

	
	map<int, CString> IpMap;                //存放所有邻舰IP地址
	
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
	//输出:多舰识别结果
	VCT_MIDENTIINFOR_MSG m_MulIdentifyMsg;

	//请求行号
	int m_iline;
 
	//本舰请求的信息
	VCT_Request_Cooperative_Msg m_RequestMsg;
	//各舰返回的所有匹配信息
	VCT_BACK_Cooperative_Msg m_BackMsg;
	VCT_BACK_Cooperative_Msg::iterator iteBackMsg;
    //本舰和各舰的合并信息
	VCT_COOPER_MSG m_CooperMsg;

	//接收请求的临时数据
	SendRequest_Msg tmpRecRequest_Msg;
	
	/**********socket communication***************/
	//同步事件标志位
	HANDLE hEvent;

	//p2p socket服务器
	CMsgSocket* m_P2PSocket;
	//p2p socket客户端
	CSocket* m_P2PClient;

	//客户端
	CMsgSocket* pClient;
	//客户端指针
	map<DWORD, CMsgSocket*> m_ClientMap;
	map<DWORD, CMsgSocket*>::iterator m_pClient;

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
	void SetIPLib(void);

public:
	//common
	void ClientAccept(void);
	void ClientClose(void* pContext);
	void ReceiveFromClient(CMsgSocket* pThis);
	void SendToClient(CMsgSocket* pThis);

	void ServerCreate(void);
	void ServerShutDown(void);

// Implementation
	//{{AFX_MSG(CNodePlatApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NODEPLAT_H__35ECCD2C_1DA6_4922_A062_1BF67E09DB35__INCLUDED_)
