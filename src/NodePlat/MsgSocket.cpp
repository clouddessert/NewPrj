// MsgSocket.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgSocket
extern CNodePlatApp theApp;

CMsgSocket::CMsgSocket()
{
}

CMsgSocket::~CMsgSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CMsgSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CMsgSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CMsgSocket member functions

void CMsgSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	theApp.ClientAccept();

	CAsyncSocket::OnAccept(nErrorCode);
}

void CMsgSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	theApp.ReceiveFromClient(this);
	//立刻发送写请求
	AsyncSelect(FD_WRITE);
	
	CAsyncSocket::OnReceive(nErrorCode);
}

void CMsgSocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	//数据处理，并且发送
	theApp.SendToClient(this);
	//继续等待读消息
	AsyncSelect(FD_READ);

	CAsyncSocket::OnSend(nErrorCode);
}

void CMsgSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	theApp.ClientClose(this);
	
	CAsyncSocket::OnClose(nErrorCode);
}
