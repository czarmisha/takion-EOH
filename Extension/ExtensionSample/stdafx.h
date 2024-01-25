// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
/*
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT
*/
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif


#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

/*
#pragma warning (disable:4244)
#pragma warning (disable:4267)
#pragma warning (disable:4666)
#pragma warning (disable:4786)

#include <afxtempl.h>

#include <list>
#include <set>
#include <map>
#include <vector>
#include <string>

#if (_MSC_VER > 1600)
#include <functional>
#include <unordered_set>
#include <unordered_map>
//#define hash_set unordered_set
//#define hash_map unordered_map
#else
#include <hash_map>
#include <hash_set>
#endif

#include "ObserverApi.h"
#include "TakionLogApi.h"
#include "TakionMemoryApi.h"
#include "TakionUtilsApi.h"
#include "UtilsApi.h"
#include "UtilsGuiApi.h"
*/
#include "ConnectionApi.h"
#include "TakionDataApi.h"
#include "TakionGui.h"
