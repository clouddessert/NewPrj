// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "ClientSocket.h"

#include "NodePlatDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSocket
extern CNodePlatApp theApp;
extern CNodePlatDoc* pDoc;

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////

void CClientSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	pDoc->ReceiveData(this);
	//等待读的事件
	AsyncSelect(FD_READ);

	CAsyncSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	//等待读的事件
	AsyncSelect(FD_READ);

	CAsyncSocket::OnSend(nErrorCode);
}
