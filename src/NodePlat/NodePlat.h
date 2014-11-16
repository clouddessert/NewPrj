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
	CRITICAL_SECTION g_cs;				// �ٽ����ṹ����

	CDataBase m_DataBase;               //���ݿ����

	void *pTmpDocPt;
	//���������߳̾��;
	HANDLE hSendProc;					
	BOOL bThreadFlag;
	
	VCT_ESM_MSG m_ESM_Dat;
	VCT_COMM_MSG m_Comm_Dat;
	VCT_TRACE_MSG m_Trace_Dat;
	VCT_SHIP_POSITION m_Ship_Position;


	//����ṹ��
	ALL_MSG_INPUT m_RecvMsg;
	VCT_SHIP_POSITION m_SPosition;

	//��Ϣ����
	VCT_SendRequest_Msg m_SendReqMsg_Dat;    //���͵�������Ϣ���ɶ���ṹ����ɵ�����(�Ѿ�ת�ɺ������������)
 	VCT_SendRequest_Msg m_RecvReqMsg_Dat;    //���յ�������Ϣ

 	VCT_SendBack_Msg m_SendBackMsg_Dat;      //���ͷ���ƥ����Ϣ
 	VCT_SendBack_Msg m_RecvBackMsg_Dat;      //���շ���ƥ����Ϣ

	//��Ϣ�����ṹ��
	SendRequest_Msg m_StSendRequest;          //��������Ľṹ��
	SendRequest_Msg tmpRecRequest_Msg;        //�����������ʱ�ṹ��
//	SendRequest_Msg m_StReceiveRequest;       //��������Ľṹ��

// 	SendBack_Msg m_SendBackMsg;               //���ͷ�����Ϣ
// 	SendBack_Msg m_ReceiveBackMsg;            //���շ�����Ϣ
			
	//�����������Ϣ
	int m_iline;                               //�����к�
	vector<int> m_RequestNum_Dat;              //����Эͬ������
	VCT_Request_Cooperative_Msg m_RequestMsg;  //����Эͬ��Ϣ
	//�������ص�����ƥ����Ϣ
	VCT_BACK_Cooperative_Msg m_BackMsg;
	VCT_BACK_Cooperative_Msg::iterator iteBackMsg;
    //�����͸����ĺϲ���Ϣ
	VCT_COOPER_MSG m_CooperMsg;

	int m_ThisNumber;	                     //�������
	CString m_strLocalIP;                    //����IP
	char m_SelfName[3];                         //��������
	map<int, CString> IpMap;                 //��������ڽ�IP��ַ
	map<int, CString> SendToIpMap;           //���Эͬ�ڽ�IP��ַ������ţ�IP��ַ��
	
	//��Ϣ����
	unsigned char cMsgType;	//5 ������Ϣ����Track,Esm,Com

	//���ָ��	//���:����������

	//���:�������
	VCT_ESM_MSG m_ESM;
	VCT_COMM_MSG m_Comm;
	VCT_TRACE_MSG m_Trace;

	//���:������

	VCT_UNINUM_MSG m_ClusterUniMsg;//�к���
	VCT_UNINOTRACE_MSG m_ClusterNoTraceMsg;//�޺���
	
	//���:δ������
	VCT_TRACE_MSG m_SingleTrace;
	VCT_ESM_MSG m_SingleEsm;
	VCT_COMM_MSG m_SingleComm;
	
	//���:����ʶ����
	VCT_IDENTIINFOR_MSG m_IdentifyMsg;
	//���:�རʶ����
	VCT_MIDENTIINFOR_MSG m_MulIdentifyMsg;
	//���:��Ϣ�ںϽ��
	VCT_Cooperative_FUSIDENTIINFOR m_CoopFusIdentify;
	VCT_ESM_MSG m_MulESM;
	VCT_COMM_MSG m_MulComm;
	VCT_TRACE_MSG m_MulTrace;
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteCoFus1;
	VCT_ESM_MSG::iterator iteFusEsm1;
	VCT_COMM_MSG::iterator iteFusCom1;


	/*******************̬�Ʋ��ֱ���******************/
	//�¼��ڰ�
	MAP_EVENT_BLACK m_mapEventBlack; 
	//ƽ̨�ڰ�
	MAP_PLAT_BLACK m_Plat_Black;
	//�ɻ���ڰ�
	SPACE_BLACK m_PlaneSpaceBlack;
	//������ڰ�
	SPACE_BLACK m_ShipSpaceBlack;
	//����Ⱥ�ڰ�
	FUN_GROUP_BLACK m_FunBlack;
	//�໥����Ⱥ�ڰ�
	INTERGROUPBLACK m_InterGBlack;

	

	
	/**********socket communication***************/
	//ͬ���¼���־λ
	HANDLE hEvent;

	//p2p socket������
	CMsgSocket* m_P2PSocket;
	//p2p socket�ͻ���
	CSocket* m_P2PClient[5];

	//�ͻ���
	CMsgSocket* pClient;
	//�ͻ���ָ��
	map<DWORD, CMsgSocket*> m_ClientMap;
	map<DWORD, CMsgSocket*>::iterator m_pClient;

//	vector<CString> m_MsgDisplayVec;
	CString m_MsgDisplay;
	CString m_GpsDisplay;
	CString m_GpsZBDisplay;
	CString m_SelfShipGps;

public:
	//����
	HWND hESM_wmd;
	HWND hCOMM_wmd;
	HWND hTRACE_wmd;
	HWND hSigOut_wnd;
	
	//�ར
	HWND hMulOut_wnd;
	HWND hMulESM_wmd;
	HWND hMulCOMM_wnd;
	HWND hMulTRACE_wnd;

	//��������
	HWND hFus_wnd;
	//ָ��ʶ��(���+ͼ��)
	HWND hZdSb_wnd;
	HWND hZdSbTu_wnd;
	//ȫ��ʶ��(���+ͼ��)
	HWND hQbSb_wnd;
	HWND hQbSbTu_wnd;
	HWND hQbsinSb_wnd;
	//ָ���ں�(���+ͼ��)
	HWND hZdFus_wnd;
	HWND hZdFusTu_wnd;
	//ȫ���ں�(���+ͼ��)
	HWND hQbFus_wnd;
	HWND hQbFusTu_wnd;
	//������ʾ����
	HWND hDISPLAY_wnd;

	//�¼���ʾ����
	HWND hEvent_wnd;
	//ƽ̨��ʾ����
	HWND hPlat_wnd;
	//�ռ�Ⱥ��ʾ����
	HWND hSpace_wnd;
	//����Ⱥ��ʾ����
	HWND hFun_wnd;
	//�໥����Ⱥ��ʾ����
	HWND hInter_wnd;


	//view��ָ��
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
