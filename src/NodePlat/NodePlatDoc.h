// NodePlatDoc.h : interface of the CNodePlatDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODEPLATDOC_H__D1E6E59A_A44F_4D6E_AD35_CD35332AE50C__INCLUDED_)
#define AFX_NODEPLATDOC_H__D1E6E59A_A44F_4D6E_AD35_CD35332AE50C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParamThirdPage.h"
#include "EvaluDlg.h"

class CNodePlatDoc : public CDocument
{
protected: // create from serialization only
	CNodePlatDoc();
	DECLARE_DYNCREATE(CNodePlatDoc)

// Attributes
public:
	CParamThirdPage Msg;
	CEvaluDlg* pDlg_evalu;		// ÆÀ¹À
//	extern CListBox	m_AddMsgList;

// Operations
public:
	void OnReceiveMsg(void);
	void SendCoopReq(CSocket* pThis);
	void ReceiveData(CSocket* pThis);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNodePlatDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNodePlatDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	//{{AFX_MSG(CNodePlatDoc)
	afx_msg void OnNetworkSetting();
	afx_msg void OnSystemSetting();
	afx_msg void OnConnectService();
	afx_msg void OnTeamServiceStart();
	afx_msg void OnTeamServiceStop();
	afx_msg void OnDisconnectService();
	afx_msg void OnEvaSin();
	afx_msg void OnEvaMul();
	afx_msg void OnEvatuate();
	afx_msg void OnMenuitemA();
	afx_msg void OnMenuitemAll();
	afx_msg void OnMenuitemB();
	afx_msg void OnMenuitemC();
	afx_msg void OnMenuitemD();
	afx_msg void OnMenuitemE();
	afx_msg void OnClose();
	afx_msg void OnUpdateMenuitemb(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuitema(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuitemc(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuitemd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuiteme(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NODEPLATDOC_H__D1E6E59A_A44F_4D6E_AD35_CD35332AE50C__INCLUDED_)
