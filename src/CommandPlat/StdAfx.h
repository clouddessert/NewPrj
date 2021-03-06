// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__8FEC5057_7579_4B5F_8551_DECEBB02C539__INCLUDED_)
#define AFX_STDAFX_H__8FEC5057_7579_4B5F_8551_DECEBB02C539__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//网络
#include <afxsock.h>

//STL
#pragma warning(disable: 4786)
#include <string>
#include <vector>
#include <map>
using namespace std;

//公共头
#include "CommHeader.h"
#include "Comm Struct.h"

//消息
#define WM_ESM_MSG WM_USER+101
#define WM_COMM_MSG WM_USER+102
#define WM_TRACE_MSG WM_USER+103

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__8FEC5057_7579_4B5F_8551_DECEBB02C539__INCLUDED_)
