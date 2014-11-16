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

#include "DataBase.h"
#include "Algorithm.h"	

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
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

public:
	CRITICAL_SECTION g_cs;				// 临界区结构对象

	CDataBase m_DataBase;               //数据库对象

	void *pTmpDocPt;
	//发送数据线程句柄;
	HANDLE hSendProc;					
	BOOL bThreadFlag;
	
	VCT_ESM_MSG m_ESM_Dat;
	VCT_COMM_MSG m_Comm_Dat;
	VCT_TRACE_MSG m_Trace_Dat;
	VCT_SHIP_POSITION m_Ship_Position;


	//输入结构体
	ALL_MSG_INPUT m_RecvMsg;
	VCT_SHIP_POSITION m_SPosition;

	//信息交互
	VCT_SendRequest_Msg m_SendReqMsg_Dat;    //发送的请求信息，由多个结构体组成的容器(已经转成含有数组的容器)
 	VCT_SendRequest_Msg m_RecvReqMsg_Dat;    //接收的请求信息

 	VCT_SendBack_Msg m_SendBackMsg_Dat;      //发送返回匹配信息
 	VCT_SendBack_Msg m_RecvBackMsg_Dat;      //接收返回匹配信息

	//信息交互结构体
	SendRequest_Msg m_StSendRequest;          //发送请求的结构体
	SendRequest_Msg tmpRecRequest_Msg;        //接收请求的临时结构体
//	SendRequest_Msg m_StReceiveRequest;       //接收请求的结构体

// 	SendBack_Msg m_SendBackMsg;               //发送返回信息
// 	SendBack_Msg m_ReceiveBackMsg;            //接收返回信息
			
	//本舰请求的信息
	int m_iline;                               //请求行号
	vector<int> m_RequestNum_Dat;              //请求协同的批号
	VCT_Request_Cooperative_Msg m_RequestMsg;  //请求协同信息
	//各舰返回的所有匹配信息
	VCT_BACK_Cooperative_Msg m_BackMsg;
	VCT_BACK_Cooperative_Msg::iterator iteBackMsg;
    //本舰和各舰的合并信息
	VCT_COOPER_MSG m_CooperMsg;

	int m_ThisNumber;	                     //本舰编号
	CString m_strLocalIP;                    //本舰IP
	char m_SelfName[3];                         //本舰名称
	map<int, CString> IpMap;                 //存放所有邻舰IP地址
	map<int, CString> SendToIpMap;           //存放协同邻舰IP地址（舰编号，IP地址）
	
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
	//输出:信息融合结果
	VCT_Cooperative_FUSIDENTIINFOR m_CoopFusIdentify;
	VCT_ESM_MSG m_MulESM;
	VCT_COMM_MSG m_MulComm;
	VCT_TRACE_MSG m_MulTrace;
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteCoFus1;
	VCT_ESM_MSG::iterator iteFusEsm1;
	VCT_COMM_MSG::iterator iteFusCom1;


	/*******************态势部分变量******************/
	//事件黑板
	MAP_EVENT_BLACK m_mapEventBlack; 
	//平台黑板
	MAP_PLAT_BLACK m_Plat_Black;
	//飞机类黑板
	SPACE_BLACK m_PlaneSpaceBlack;
	//舰船类黑板
	SPACE_BLACK m_ShipSpaceBlack;
	//功能群黑板
	FUN_GROUP_BLACK m_FunBlack;
	//相互作用群黑板
	INTERGROUPBLACK m_InterGBlack;

	

	
	/**********socket communication***************/
	//同步事件标志位
	HANDLE hEvent;

	//p2p socket服务器
	CMsgSocket* m_P2PSocket;
	//p2p socket客户端
	CSocket* m_P2PClient[5];

	//客户端
	CMsgSocket* pClient;
	//客户端指针
	map<DWORD, CMsgSocket*> m_ClientMap;
	map<DWORD, CMsgSocket*>::iterator m_pClient;

//	vector<CString> m_MsgDisplayVec;
	CString m_MsgDisplay;
	CString m_GpsDisplay;
	CString m_GpsZBDisplay;
	CString m_SelfShipGps;

public:
	//单舰
	HWND hESM_wmd;
	HWND hCOMM_wmd;
	HWND hTRACE_wmd;
	HWND hSigOut_wnd;
	
	//多舰
	HWND hMulOut_wnd;
	HWND hMulESM_wmd;
	HWND hMulCOMM_wnd;
	HWND hMulTRACE_wnd;

	//性能评估
	HWND hFus_wnd;
	//指定识别(表格+图形)
	HWND hZdSb_wnd;
	HWND hZdSbTu_wnd;
	//全部识别(表格+图形)
	HWND hQbSb_wnd;
	HWND hQbSbTu_wnd;
	HWND hQbsinSb_wnd;
	//指定融合(表格+图形)
	HWND hZdFus_wnd;
	HWND hZdFusTu_wnd;
	//全部融合(表格+图形)
	HWND hQbFus_wnd;
	HWND hQbFusTu_wnd;
	//命令显示窗口
	HWND hDISPLAY_wnd;

	//事件显示窗口
	HWND hEvent_wnd;
	//平台显示窗口
	HWND hPlat_wnd;
	//空间群显示窗口
	HWND hSpace_wnd;
	//功能群显示窗口
	HWND hFun_wnd;
	//相互作用群显示窗口
	HWND hInter_wnd;


	//view的指针
	void* pXview;

private:
//	void SetIPLib(void);

public:
	//common
	void SetIPLib(void);
	void ClientAccept(void);
	void ClientClose(void* pContext);
	void ReceiveFromClient(CMsgSocket* pThis);
	void SendToClient(CMsgSocket* pThis);

	void ServerCreate(void);
	void ServerShutDown(void);

	void SendMsg(map<int, CString> SendToIpMap);

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
