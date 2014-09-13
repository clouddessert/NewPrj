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
	CRITICAL_SECTION g_cs;				// �ٽ����ṹ����
	
	VCT_ESM_MSG m_ESM_Dat;
	VCT_COMM_MSG m_Comm_Dat;
	VCT_TRACE_MSG m_Trace_Dat;
	VCT_SHIP_POSITION m_Ship_Position;

	//����ṹ��
	ALL_MSG_INPUT m_RecvMsg;
	VCT_SHIP_POSITION m_SPosition;

	//����������Ϣ
// 	Request_Cooperative_Msg m_RecvReqMsg;  //�ṹ�� ����ͷ�е���Ϣ���Ⱦ��������Ĵ�С,���ṹ��ĸ���
// 
//     VCT_SendRequest_Msg m_SendReqMsg_Dat;    //������Ϣ���ɶ���ṹ����ɵ�����(�Ѿ�ת�ɺ������������)
// 	VCT_SendRequest_Msg m_RecvReqMsg_Dat;    //����������Ϣ
// 
// 	VCT_SendBack_Msg m_SendBackMsg_Dat;      //������Ϣ
// 	VCT_SendBack_Msg m_RecvBackMsg_Dat;      //���շ�����Ϣ

	//��Ϣ�����ṹ��
	Request_Cooperative_Msg m_StRequest;      //��������ʶ��ǰ�����ŵı�����Ϣ

	SendRequest_Msg m_StSendRequest;          //��������Ľṹ��
	SendRequest_Msg m_StReceiveRequest;       //��������Ľṹ��

	SendBack_Msg m_SendBackMsg;               //���ͷ�����Ϣ
	SendBack_Msg m_ReceiveBackMsg;               //���շ�����Ϣ
	
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

	//�����к�
	int m_iline;

	//p2p socket
	CMsgSocket* m_P2PSocket;

	//�ͻ���
	CMySocket* pClient;
	//�ͻ���ָ��
	map<DWORD, CMySocket*> m_ClientMap;
	map<DWORD, CMySocket*>::iterator m_pClient;

public:
	HWND hESM_wmd;
	HWND hCOMM_wmd;
	HWND hTRACE_wmd;
	HWND hSigOut_wnd;
	HWND hMulOut_wnd;
	//�ར
	HWND hMulESM_wmd;
	HWND hMulCOMM_wnd;
	HWND hMulTRACE_wnd;


	//view��ָ��
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
