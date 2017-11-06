// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__9DB0C2EA_9A8F_4258_82BD_6CE1242A64D5__INCLUDED_)
#define AFX_STDAFX_H__9DB0C2EA_9A8F_4258_82BD_6CE1242A64D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//ÊÇ·ñ¾²Ì¬Áª±à
#define STATIC_LINK		

#ifdef STATIC_LINK
#pragma warning(disable: 4273)
#pragma warning(disable: 4786)
#endif
#define USE_REBAR

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "LApiInterface.h"
#include <afxsock.h>		// MFC socket extensions

static CFont m_fontDefault;
extern CFont* m_pDefaultFont;
#ifdef USE_REBAR
#define m_style_toolbar WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP
#else
#define m_style_toolbar WS_CHILD | WS_VISIBLE | CBRS_TOP\
        | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC
#endif
//CBRS_BORDER_3D
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__9DB0C2EA_9A8F_4258_82BD_6CE1242A64D5__INCLUDED_)
