#if !defined(AFX_MSGSOCKET_H__6C27E3E3_39F4_44FE_9548_EC8A0AE70E2C__INCLUDED_)
#define AFX_MSGSOCKET_H__6C27E3E3_39F4_44FE_9548_EC8A0AE70E2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CMsgSocket command target

class CMsgSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CMsgSocket();
	virtual ~CMsgSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMsgSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGSOCKET_H__6C27E3E3_39F4_44FE_9548_EC8A0AE70E2C__INCLUDED_)
