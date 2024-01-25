#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include <UtilsApi.h>
#include <TakionMemoryApi.h>
#include <TakionLogApi.h>
#include <afxtempl.h>
#include <list>
#include <vector>

#ifdef UGUI_EXPORTS
#define UGUI_API __declspec(dllexport)
#else
#define UGUI_API __declspec(dllimport)
#endif

const char* const UtilsGuiHeaderVersion = "1.0.7.71";
const unsigned short highBit = 1 << 15;
const unsigned int repeatBit = 1 << 30;
const char settingDel = '|';
const char settingSubdel = '`';
const char sectionDel = '/';
const char groupDel = '\'';

#define PARTIAL_PAINT_ON_RESIZE
#define TOOLS_ARE_CHILDREN

//#define WATCH_ACTIVATE_AFTER_MARKET

#ifdef __cplusplus
extern "C"
{
#endif

COLORREF WINAPI UGUI_GetMiddleColor(COLORREF color1, COLORREF color2);
COLORREF WINAPI UGUI_GetOppositeColor(COLORREF color);

enum BaseButtonIDs : unsigned int
{
	IDB_APPLY = 2001,
	IDB_HELP,
	IDB_RESET,
	IDB_CLEAR,
	IDB_ON_TOP,
	IDB_TOOLTIP,
	IDS_TITLE,

	BaseButtonIDsLast
};

#ifdef __cplusplus
} //extern "C"
#endif

class TLogFont : public LOGFONT
{
public:
	TLogFont()
	{
		memset(this, 0, sizeof(TLogFont));
	}

	TLogFont::TLogFont(const LOGFONT& other)
	{
		operator=(other);
	}

	TLogFont& operator=(const LOGFONT& other)
	{
		lfHeight = other.lfHeight;
		lfWidth = other.lfWidth;
		lfEscapement = other.lfEscapement;
		lfOrientation = other.lfOrientation;
		lfWeight = other.lfWeight;
		lfItalic = other.lfItalic;
		lfUnderline = other.lfUnderline;
		lfStrikeOut = other.lfStrikeOut;
		lfCharSet = other.lfCharSet;
		lfOutPrecision = other.lfOutPrecision;
		lfClipPrecision = other.lfClipPrecision;
		lfQuality = other.lfQuality;
		lfPitchAndFamily = other.lfPitchAndFamily;
		U_CopyAndPad(lfFaceName, sizeof(lfFaceName), other.lfFaceName, '\0');
		return *this;
	}
/*
	TLogFont(const LOGFONT& other);

	TLogFont& operator=(const LOGFONT& other);
*/
	bool operator==(const LOGFONT& other) const
	{
		return lfHeight == other.lfHeight
			&& lfWidth == other.lfWidth
			&& lfEscapement == other.lfEscapement
			&& lfOrientation == other.lfOrientation
			&& lfWeight == other.lfWeight
			&& lfItalic == other.lfItalic
			&& lfUnderline == other.lfUnderline
			&& lfStrikeOut == other.lfStrikeOut
			&& lfCharSet == other.lfCharSet
			&& lfOutPrecision == other.lfOutPrecision
			&& lfClipPrecision == other.lfClipPrecision
			&& lfQuality == other.lfQuality
			&& lfPitchAndFamily == other.lfPitchAndFamily
			&& !strcmp(lfFaceName, other.lfFaceName);
	}
	bool operator<(const LOGFONT& other) const
	{
		return lfHeight != other.lfHeight ? lfHeight < other.lfHeight:
			lfWidth != other.lfWidth ? lfWidth < other.lfWidth:
			lfEscapement != other.lfEscapement ? lfEscapement < other.lfEscapement:
			lfOrientation != other.lfOrientation ? lfOrientation < other.lfOrientation:
			lfWeight != other.lfWeight ? lfWeight < other.lfWeight:
			lfItalic != other.lfItalic ? lfItalic < other.lfItalic:
			lfUnderline != other.lfUnderline ? lfUnderline < other.lfUnderline:
			lfStrikeOut != other.lfStrikeOut ? lfStrikeOut < other.lfStrikeOut:
			lfCharSet != other.lfCharSet ? lfCharSet < other.lfCharSet:
			lfOutPrecision != other.lfOutPrecision ? lfOutPrecision < other.lfOutPrecision:
			lfClipPrecision != other.lfClipPrecision ? lfClipPrecision < other.lfClipPrecision:
			lfQuality != other.lfQuality ? lfQuality < other.lfQuality:
			lfPitchAndFamily != other.lfPitchAndFamily ? lfPitchAndFamily < other.lfPitchAndFamily:
			strcmp(lfFaceName, other.lfFaceName) < 0;
	}
	operator DWORD_PTR()
	{
#ifdef _WIN64
		return (DWORD_PTR)*(DWORD*)lfFaceName << 32 | (DWORD_PTR)(DWORD)lfHeight;
#else
		return (DWORD_PTR)*(WORD*)lfFaceName << 16 | (DWORD_PTR)(WORD)lfHeight;
#endif
	}
	size_t GetHashValue() const
	{
		return lfHeight | (lfWidth << 4) | (*lfFaceName << 8) | (*(lfFaceName + 1) << 8);
	}
};

template<> AFX_INLINE UINT AFXAPI HashKey<const TLogFont&>(const TLogFont& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

//DragDrop
//http://msdn.microsoft.com/en-us/magazine/cc163915.aspx

class UGUI_API CDragDropData
{
public:
	virtual ~CDragDropData(){}
	virtual void* OnGetData() = 0;
	virtual unsigned int GetOrdinal() const{return 0xFFFFFFFF;}
	virtual bool CanDragOut() const{return true;}

protected:
	CDragDropData(){}
};

//////////////////
// Concrete class for drag-drop text data.
//
class UGUI_API CDragDropText : public CDragDropData
{
public:
//	CDragDropText(const char* text, int maxWidth = 64):m_text(text){}//, m_maxWidth(maxWidth){}
	CDragDropText(const char* text):m_text(text){}//, m_maxWidth(maxWidth){}
//	virtual void* OnGetData(){return (void*)(LPCTSTR)m_text;}
	virtual void* OnGetData(){return (void*)m_text.c_str();}
protected:
	std::string m_text;
//	CString m_text;
//	unsigned int m_maxWidth;
};

/*
//////////////////
// registered message sent by drag-drop manager
//
extern const UINT WM_DD_DRAGENTER; // start dragging
extern const UINT WM_DD_DRAGOVER;  // dragging
extern const UINT WM_DD_DRAGLEAVE;  // dragging
extern const UINT WM_DD_DRAGDROP;  // drop
extern const UINT WM_DD_DRAGABORT; // abort dragging
*/
// flags used for window type in window map
enum DragWindowType : unsigned char
{
	DDW_SOURCE = 0x01, // window is drag-drop source
	DDW_TARGET = 0x02	// window is drag-dtop target
};

// Used to create drag-drop window map. Map is an array of these structs,
// each entry specifies a child window ID and whether the window is a source,
// target, or both.
struct DRAGDROPWND
{
	UINT id;					// window ID
	UINT type;				// DDW_ flags above
};

//////////////////
// Drag-drop structure passed as LPARAM in WM_DD_ messages.
//
struct DRAGDROPINFO
{
	DRAGDROPINFO() : hwndSource(nullptr), hwndTarget(nullptr), m_target(false), data(nullptr)
	{
		pt.x = 0;
		pt.y = 0;
	}
	HWND hwndSource;		// source window
	HWND hwndTarget;		// target window
	bool m_target;
	CDragDropData* data;	// data to drag/drop
	POINT pt;				// current point (cursor) in client coords of whatever window is identified by WPARAM
};

//////////////////
// Inter-app drag-drop manager. To use this, instantiate one instance in your
// main window class and call Install from your OnCreate or OnInitDialog
// method. You must also override your main window's PreTranslateMessage to
// call CDragDropMgr::PreTranslateMessage.
//
class UGUI_API CDragDropMgr
{
public:
	CDragDropMgr(CWnd* parent, HCURSOR hCursorDrop, HCURSOR hCursorNo, HCURSOR hCursorThrow, HCURSOR hCursorMove,
		UINT mouseDownMessage = WM_RBUTTONDOWN, UINT mouseUpMessage = WM_RBUTTONUP, UINT mouseEscapeMessage = WM_LBUTTONDOWN);
//	virtual ~CDragDropMgr();
#if(_MSC_VER > 1600)
	typedef std::unordered_map<HWND, UINT> HWNDMAP;
#else
	typedef std::hash_map<HWND, UINT> HWNDMAP;
#endif
	// Call this to initialize. 2nd arg is array of DRAGDROPWND's, one for
	// each source/target child window.
	//
	BOOL Install(CWnd *pMainWnd, DRAGDROPWND* pWnds);

	// You must call this from your main window's PreTranslateMessage.
	BOOL PreTranslateMessage(MSG* pMsg);

	// Call this if you want non-standard cursors.
	void SetCursors(HCURSOR hCursorDrop, HCURSOR hCursorNo, HCURSOR hCursorThrow, HCURSOR hCursorMove)
	{
		m_hCursorDrop = hCursorDrop;
		m_hCursorNo = hCursorNo;
		m_hCursorThrow = hCursorThrow;
		m_hCursorMove = hCursorMove;
	}

	// Call these to add/remove source/target windows dynamically.
	void AddWindow(HWND hwnd, int type);
	void RemoveWindow(HWND hwnd);
	void ClearWindows();

	bool IsCaptured() const{return m_iState >= CAPTURED;}
	bool IsDragging() const{return m_iState >= DRAGGING;}
	bool IsSourceWnd(HWND hwnd) const{return (GetWindowType(hwnd) & DDW_SOURCE) != 0;}
	bool IsTargetWnd(HWND hwnd) const{return (GetWindowType(hwnd) & DDW_TARGET) != 0;}
	UINT GetWindowType(HWND hwnd) const;
	bool isSourceTarget() const{return m_sourceIsTarget;}
	bool Abort();

#if(_MSC_VER > 1600)
	typedef std::unordered_set<HWND> HwndSet;
	typedef std::unordered_map<HWND, HwndSet> TargetSourceMap;
#else
	typedef std::hash_set<HWND> HwndSet;
	typedef std::hash_map<HWND, HwndSet> TargetSourceMap;
#endif
	bool isSourceValidForTarget(HWND target, HWND source) const;
	void AddTargetSource(HWND target, HWND source);
	void RemoveTargetSource(HWND target, HWND source);
	void RemoveTarget(HWND target){m_targetSourceMap.erase(target);}
	void ClearTargets(){m_targetSourceMap.clear();}
protected:
	enum : unsigned char{NONE=0, CAPTURED, DRAGGING}; // internal states

// static stuff 
	CWnd*			m_pMainWnd;				 // main window
	HWNDMAP			m_mapHwnd;				 // map of source/target windows
	HWNDMAP::const_iterator m_mapHwndEnd;

	TargetSourceMap m_targetSourceMap;
	TargetSourceMap::const_iterator m_targetSourceMapEnd;

	HCURSOR			m_hCursorDrop;			 // ok-to-drop cursor
	HCURSOR			m_hCursorNo;			 // no-drop cursor
	HCURSOR			m_hCursorThrow;			 // throw away cursor
	HCURSOR			m_hCursorMove;

	// dyanmic stuff used during dragging
	DRAGDROPINFO	m_info;					 // data during drag/drop
	UINT			m_iState;				 // current state: CAPTURED/DRAGGING
	HWND			m_hwndTracking;		 // window w/mouse capture
	CPoint			m_ptOrg;					 // original point start of drag
//	CImageList*		m_pDragImage;			 // imagelist for dragging
	HCURSOR			m_hCursorSave;			 // save cursor

	// mouse input handlers: can override if you derive
	virtual BOOL OnMouseButtonDown(const MSG& msg);
	virtual BOOL OnMouseMove(const MSG& msg);
	virtual BOOL OnMouseButtonUp(const MSG& msg);
//	virtual BOOL OnMouseLeave(const MSG& msg);

	// internal helper functions
	void SetState(const UINT iState);
	UINT m_mouseDownMessage;
	UINT m_mouseUpMessage;
	UINT m_mouseEscapeMessage;
/*
	extern const UINT WM_DD_DRAGENTER; // start dragging
	extern const UINT WM_DD_DRAGOVER;  // dragging
	extern const UINT WM_DD_DRAGLEAVE;  // dragging
	extern const UINT WM_DD_DRAGDROP;  // drop
	extern const UINT WM_DD_DRAGABORT; // abort dragging
*/
	const UINT& m_dragEnterMessage;
	const UINT& m_dragOverMessage;
	const UINT& m_dragLeaveMessage;
	const UINT& m_dragDropMessage;
	const UINT& m_dragAbortMessage;

	bool m_sourceIsTarget;

	void ClearData();
};

//End Drag Drop
class UGUI_API VisualBase
{
public:
	VisualBase(HINSTANCE exeHinstance, unsigned __int64 exeVersion);
	virtual ~VisualBase();

	HINSTANCE GetExeHInstance() const{return m_exeHinstance;}
	const unsigned __int64& GetExeVersion() const{return m_exeVersion;}

	typedef CMap<TLogFont, const TLogFont&, CFont*, CFont* const&> FontMap;
//	typedef std::hash_map<TLogFont, CFont*> FontMap;
	CFont* GetFont(const LOGFONT& logfont, LOGFONT* actualLogFont = nullptr) const;
	CFont* GetFont(CFont* font, unsigned char bold = 0, unsigned char italic = 0, unsigned char underline = 0, unsigned char strikeout = 0, LOGFONT* actualLogFont = nullptr) const;//0 - leave as is, 1 - no, 2 - yes
	CFont* GetFont(const char* name, int height, bool bold = false, bool italic = false, bool underline = false, bool strikeout = false, LOGFONT* actualLogFont = nullptr) const;
	CFont* GetFont(const FontDescription& fontDescription, int height) const;
	CFont* GetFont(bool maxSize, const FontDescription& fontDescription) const;
	CFont* GetFontDifferentSize(CFont* font, HDC hdc, int notch) const;//notch < 0 - smaller
	void ClearFonts();

	typedef CMap<unsigned int, const unsigned int&, HICON, const HICON&> IconMap;
	HICON GetIcon(unsigned int id, HINSTANCE hInstance) const;
	void ClearIcons();

#if(_MSC_VER > 1600)
	typedef std::unordered_map<const FilterStringAsNumberArray, WSABUF, TakionHashValue<FilterStringAsNumberArray> > FileMemoryMap;
#else
	typedef std::hash_map<const FilterStringAsNumberArray, WSABUF> FileMemoryMap;
#endif
		
	const char* GetWav(const std::string& fileName);//called from sound thread only
	const char* LoadWav(const std::string& fileName);//called from sound thread only
	void ClearWavs();//called from sound thread only

	typedef CMap<unsigned int, const unsigned int&, CBitmap*, CBitmap* const&> BitmapMap;
	CBitmap* GetBitmap(unsigned int id, HINSTANCE hInstance = nullptr, CBitmap** mask = nullptr);
	void ClearBitmaps();
	static void PrepareMask(CBitmap* pBmpSource,
		CBitmap* pBmpMask,
		COLORREF clrpTransColor = 0,
		int iTransPixelX = 0,
		int iTransPixelY = 0);

	typedef CMap<COLORREF, const COLORREF&, CBrush*, CBrush* const&> SolidBrushMap;
	CBrush* GetSolidBrush(COLORREF color);
	void ClearSolidBrushes();

	HICON GetIconError() const{return m_iconError;}
	HICON GetIconWarning() const{return m_iconWarning;}
	HICON GetIconQuestion() const{return m_iconQuestion;}
	HICON GetIconInfo() const{return m_iconInfo;}
/*
	CBitmap* GetCheckCheckedBitmap(){return &m_checkCheckedBitmap;}
	CBitmap* GetCheckUncheckedBitmap(){return &m_checkUncheckedBitmap;}
	CBitmap* GetRadioCheckedBitmap(){return &m_radioCheckedBitmap;}
	CBitmap* GetRadioUncheckedBitmap(){return &m_radioUncheckedBitmap;}
*/
	const COLORREF& GetWarningColor() const{return m_warningColor;}
	const COLORREF& GetLoadColor() const{return m_loadColor;}
	const COLORREF& GetPendingColor() const{return m_pendingColor;}
	const COLORREF& GetOkColor() const{return m_okColor;}
	const COLORREF& GetBlueColor() const{return m_blueColor;}
	const COLORREF& GetLightBlueColor() const{return m_lightBlueColor;}
	const COLORREF& GetWarningTextColor() const{return m_warningTextColor;}
	const COLORREF& GetPendingTextColor() const{return m_pendingTextColor;}
	const COLORREF& GetOkTextColor() const{return m_okTextColor;}
	const COLORREF& GetBlueTextColor() const{return m_blueTextColor;}
	const COLORREF& GetGrayColor() const{return m_grayColor;}
	const COLORREF& GetLightGrayColor() const{return m_lightGrayColor;}
	const COLORREF& GetSystemGrayTextColor() const{return m_systemGrayTextColor;}
	const COLORREF& GetSystemGrayColor() const{return m_systemGrayColor;}
	const COLORREF& GetCheckHighlightColor() const{return m_checkHighlightColor;}

	CBrush* GetWarningBrush() const{return m_warningBrush;}
	CBrush* GetLoadBrush() const{return m_loadBrush;}
	CBrush* GetPendingBrush() const{return m_pendingBrush;}
	CBrush* GetOkBrush() const{return m_okBrush;}
	CBrush* GetGrayBrush() const{return m_grayBrush;}
	CBrush* GetLightGrayBrush() const{return m_lightGrayBrush;}
	CBrush* GetSystemGrayBrush() const{return m_systemGrayBrush;}
	CBrush* GetBlueBrush() const{return m_blueBrush;}
	CBrush* GetLightBlueBrush() const{return m_lightBlueBrush;}

	HCURSOR GetArrowCursor() const{return m_arrowCursor;}
	HCURSOR GetHourglassCursor() const{return m_hourglassCursor;}
	HCURSOR GetNoCursor() const{return m_noCursor;}
	HCURSOR GetCursorResizeVertical() const{return m_cursorResizeVertical;}
	HCURSOR GetCursorResizeVerticalUp() const{return m_cursorResizeVerticalUp;}
	HCURSOR GetCursorResizeVerticalDown() const{return m_cursorResizeVerticalDown;}
	HCURSOR GetCursorResizeHorizontal() const{return m_cursorResizeHorizontal;}
	HCURSOR GetCursorResizeHorizontalLeft() const{return m_cursorResizeHorizontalLeft;}
	HCURSOR GetCursorResizeHorizontalRight() const{return m_cursorResizeHorizontalRight;}
	HCURSOR GetCursorResizeVertical1() const{return m_cursorResizeVertical1;}
	HCURSOR GetCursorResizeVertical1Up() const{return m_cursorResizeVertical1Up;}
	HCURSOR GetCursorResizeVertical1Down() const{return m_cursorResizeVertical1Down;}
	HCURSOR GetCursorResizeVertical1White() const{return m_cursorResizeVertical1White;}
	HCURSOR GetCursorResizeVertical1WhiteUp() const{return m_cursorResizeVertical1WhiteUp;}
	HCURSOR GetCursorResizeVertical1WhiteDown() const{return m_cursorResizeVertical1WhiteDown;}
	HCURSOR GetCursorResizeHorizontal1() const{return m_cursorResizeHorizontal1;}
	HCURSOR GetCursorResizeHorizontal1Left() const{return m_cursorResizeHorizontal1Left;}
	HCURSOR GetCursorResizeHorizontal1Right() const{return m_cursorResizeHorizontal1Right;}
	HCURSOR GetCursorMoveOne() const{return m_cursorMoveOne;}
	HCURSOR GetCursorMoveAll() const{return m_cursorMoveAll;}
	HCURSOR GetCursorDragOne() const{return m_cursorDragOne;}
	HCURSOR GetCursorDragAll() const{return m_cursorDragAll;}
	HCURSOR GetCursorFinger() const{return m_cursorFinger;}
	HCURSOR GetCursorFingerTransparent() const{return m_cursorFingerTransparent;}

	HCURSOR GetCursorCrosshair() const{return m_cursorCrosshair;}
	HCURSOR GetCursorCrosshairGreen() const{return m_cursorCrosshairGreen;}
	HCURSOR GetCursorCrosshairRed() const{return m_cursorCrosshairRed;}

	HCURSOR GetCursorCopy() const{return m_cursorCopy;}
	HCURSOR GetCursorCopyGreen() const{return m_cursorCopyGreen;}
	HCURSOR GetCursorCopyRed() const{return m_cursorCopyRed;}

	HCURSOR GetCursorMoveObject() const{return m_cursorMoveObject;}
	HCURSOR GetCursorThrow() const{return m_cursorThrow;}

	HCURSOR GetCursorPlus() const{return m_cursorPlus;}
	HCURSOR GetCursorPlusGreen() const{return m_cursorPlusGreen;}
	HCURSOR GetCursorPlusRed() const{return m_cursorPlusRed;}

	HCURSOR GetCursorMinus() const{return m_cursorMinus;}

	CFont* GetMenuFont(){return &m_menuFont;}
	CFont* GetMenuFontBold(){return &m_menuFontBold;}
	CFont* GetMenuSmallFont(){return &m_menuSmallFont;}
	CFont* GetMenuSmallFontBold(){return &m_menuSmallFontBold;}
	CFont* GetCaptionFont(){return &m_captionFont;}
	CFont* GetSmallCaptionFont(){return &m_smallCaptionFont;}
	CFont* GetStatusFont(){return &m_statusFont;}
	CFont* GetMessageFont(){return &m_messageFont;}

	static const char* DoLoadWav(const std::string& fileName, unsigned long& wavSize);
protected:
	void InsertWavFile(const std::string& fileName, const char* wavePtr, unsigned long size);

	HINSTANCE m_exeHinstance;
	HINSTANCE m_baseHinstance;
	unsigned __int64 m_exeVersion;
	HICON m_iconError;
	HICON m_iconWarning;
	HICON m_iconQuestion;
	HICON m_iconInfo;
/*
	CBitmap m_checkCheckedBitmap;
	CBitmap m_checkUncheckedBitmap;
	CBitmap m_radioCheckedBitmap;
	CBitmap m_radioUncheckedBitmap;
*/
	COLORREF m_warningColor;
	COLORREF m_loadColor;
	COLORREF m_pendingColor;
	COLORREF m_okColor;
	COLORREF m_blueColor;
	COLORREF m_lightBlueColor;
	COLORREF m_warningTextColor;
	COLORREF m_pendingTextColor;
	COLORREF m_okTextColor;
	COLORREF m_blueTextColor;
	COLORREF m_grayColor;
	COLORREF m_lightGrayColor;
	COLORREF m_systemGrayTextColor;
	COLORREF m_systemGrayColor;
	COLORREF m_checkHighlightColor;

	HCURSOR m_arrowCursor;
	HCURSOR m_hourglassCursor;
	HCURSOR m_noCursor;
	HCURSOR m_cursorResizeVertical;
	HCURSOR m_cursorResizeVerticalUp;
	HCURSOR m_cursorResizeVerticalDown;
	HCURSOR m_cursorResizeHorizontal;
	HCURSOR m_cursorResizeHorizontalLeft;
	HCURSOR m_cursorResizeHorizontalRight;
	HCURSOR m_cursorResizeVertical1;
	HCURSOR m_cursorResizeVertical1Up;
	HCURSOR m_cursorResizeVertical1Down;
	HCURSOR m_cursorResizeVertical1White;
	HCURSOR m_cursorResizeVertical1WhiteUp;
	HCURSOR m_cursorResizeVertical1WhiteDown;
	HCURSOR m_cursorResizeHorizontal1;
	HCURSOR m_cursorResizeHorizontal1Left;
	HCURSOR m_cursorResizeHorizontal1Right;
	HCURSOR m_cursorMoveOne;
	HCURSOR m_cursorMoveAll;
	HCURSOR m_cursorDragOne;
	HCURSOR m_cursorDragAll;
	HCURSOR m_cursorFinger;
	HCURSOR m_cursorFingerTransparent;

	HCURSOR m_cursorCrosshair;
	HCURSOR m_cursorCrosshairGreen;
	HCURSOR m_cursorCrosshairRed;

//http://weblogs.java.net/blog/shan_man/archive/2006.09.15/spots_copy.PNG

	HCURSOR m_cursorCopy;
	HCURSOR m_cursorCopyGreen;
	HCURSOR m_cursorCopyRed;

	HCURSOR m_cursorMoveObject;
	HCURSOR m_cursorThrow;
	HCURSOR m_cursorPlus;
	HCURSOR m_cursorPlusGreen;
	HCURSOR m_cursorPlusRed;
	HCURSOR m_cursorMinus;
//	HCURSOR m_cursorScroll;

	CFont m_captionFont;
	CFont m_smallCaptionFont;
	CFont m_menuFont;
	CFont m_menuFontBold;
	CFont m_menuSmallFont;
	CFont m_menuSmallFontBold;
	CFont m_statusFont;
	CFont m_messageFont;

	mutable IconMap m_iconMap;
	mutable FontMap m_fontMap;
	mutable BitmapMap m_bitmapMap;
	mutable BitmapMap m_maskMap;
	mutable SolidBrushMap m_solidBrushMap;

	mutable FileMemoryMap m_fileMemoryMap;

	CBrush* m_warningBrush;
	CBrush* m_loadBrush;
	CBrush* m_pendingBrush;
	CBrush* m_okBrush;
	CBrush* m_grayBrush;
	CBrush* m_lightGrayBrush;
	CBrush* m_systemGrayBrush;
	CBrush* m_blueBrush;
	CBrush* m_lightBlueBrush;
private:
	VisualBase(const VisualBase& other);//{}
	VisualBase& operator=(const VisualBase& other);//{return *this;}
};

//class ifstream;

class UGUI_API Setting
{
public:
	virtual ~Setting(){}
//	const char* GetName() const{return m_name.c_str();}
//	const std::string& GetNameStr() const{return m_name;}
	virtual unsigned int GetItemCount() const{return 1;}
//	virtual void AppendAggregateDelimiter(std::string& str) const{str += settingDel;}
	virtual void toString(std::string& str) const = 0;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) = 0;
	virtual bool operator==(const Setting& other) const = 0;
	virtual bool operator<(const Setting& other) const = 0;
	bool operator!=(const Setting& other) const{return !operator==(other);}
	bool operator<=(const Setting& other) const{return operator<(other) || operator==(other);}
	bool operator>(const Setting& other) const{return !operator<=(other);}
	bool operator>=(const Setting& other) const{return !operator<(other);}
	virtual void CopySetting(const Setting& other) = 0;
	virtual void ReadFromStreamAsString(std::ifstream& istr, std::string& result);
	static void SkipToNewLine(std::ifstream& istr);
	bool isInitializedFromFile() const{return m_initializedFromFile;}
	void SetInitializedFromFile(bool yes){m_initializedFromFile = yes;}
	virtual bool isDefaultValue() const{return false;}
	virtual void UpdateDefaultValue() const{}
	virtual void Uninitialize(){m_initializedFromFile = false;}
	virtual bool isDelimiterAtEnd() const{return false;}
	virtual bool ToSkipDelimiterAtEnd() const{return isDelimiterAtEnd();}
	void CopySettingWithChecking(const Setting& other)
	{
		if(operator==(other))
		{
			m_initializedFromFile = other.m_initializedFromFile;
		}
		else
		{
			CopySetting(other);
		}
	}
protected:
	Setting():m_initializedFromFile(false){}
//	Setting(const char* name):m_name(name){}
//	std::string m_name;
	bool m_initializedFromFile;
};

class UGUI_API EmptySetting : public Setting
{
public:
	EmptySetting(){}//const char* name):Setting(name){}
	virtual void toString(std::string& str) const{}
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel){}
	virtual bool operator==(const Setting& other) const{return true;}
	virtual bool operator<(const Setting& other) const{return false;}
	virtual void CopySetting(const Setting& other){}
};

template<class T>
class TypeSetting : public Setting
{
public:
	typedef T SettingValueType;
	const SettingValueType& GetValue() const{return m_value;}
	bool SetValue(const SettingValueType& value)
	{
		if(m_value != value)
		{
			m_value = value;
			return true;
		}
		return false;
	}
	const SettingValueType& GetDefaultValue() const{return m_defaultValue;}
	virtual bool operator==(const Setting& other) const{return m_value == ((const TypeSetting&)other).m_value;}
	virtual bool operator<(const Setting& other) const{return m_value < ((const TypeSetting&)other).m_value;}
	virtual void CopySetting(const Setting& other) override
	{
//		operator=((const TypeSetting&)other)
		m_value = ((const TypeSetting&)other).m_value;
//		m_defaultValue = ((const TypeSetting&)other).m_defaultValue;
		m_initializedFromFile = other.isInitializedFromFile();
	}
	virtual bool isDefaultValue() const override{return m_defaultValue == m_value;}
	virtual void UpdateDefaultValue() const override{m_defaultValue = m_value;}
	virtual void Uninitialize() override{m_value = m_defaultValue; m_initializedFromFile = false;}
protected:
//	TypeSetting(const char* name, const T& value):Setting(name),m_value(value),m_defaultValue(value){}
	TypeSetting(const SettingValueType& value):m_value(value),m_defaultValue(value){}
	SettingValueType m_value;
	mutable SettingValueType m_defaultValue;
};

template<class T>
class MonetarySetting : public TypeSetting<T>
{
public:
	typedef T MonetaryType;
	static const unsigned char maxDecDigits = MonetaryType::decDigits;
//	operator size_t() const{return m_value.GetHashValue();}
	const unsigned char& GetDecDigits() const{return m_decDigits;}
	void SetDecDigits(const unsigned char& decDigits){m_decDigits = decDigits;}
protected:
	MonetarySetting(unsigned char decDigits, const T& value):TypeSetting(value), m_decDigits(decDigits){}
	unsigned char m_decDigits;
};

class UGUI_API MoneySetting : public MonetarySetting<Money>
{
public:
	MoneySetting(unsigned char decDigits = maxDecDigits, const Money& value = Money::moneyZero):MonetarySetting(decDigits, value){}
//protected:
	virtual void toString(std::string& str) const;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel);
};

class UGUI_API PriceSetting : public MonetarySetting<Price>
{
public:
	PriceSetting(unsigned char decDigits = maxDecDigits, const Price& value = Price::priceZero):MonetarySetting(decDigits, value){}
//protected:
	virtual void toString(std::string& str) const;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel);
};

class UGUI_API SignedPriceSetting : public MonetarySetting<SignedPrice>
{
public:
	SignedPriceSetting(unsigned char decDigits = maxDecDigits, const SignedPrice& value = SignedPrice::signedPriceZero):MonetarySetting(decDigits, value){}
//protected:
	virtual void toString(std::string& str) const;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel);
};

template<class T>
class NumericSetting : public TypeSetting<T>
{
public:
//	operator size_t() const{return (size_t)m_value;}
protected:
	NumericSetting(const T& value = 0):TypeSetting(value){}
};

class UGUI_API BoolSetting : public TypeSetting<bool>
{
public:
	BoolSetting(const bool& value = false):TypeSetting(value){}
	virtual void toString(std::string& str) const;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel);
};

template<class T>
class IncrementalSetting : public NumericSetting<T>
{
public:
	void Increment(const T& t = 1){m_value += t;}
	void Decrement(const T& t = 1){m_value -= t;}
protected:
	IncrementalSetting(const T& value = 0):NumericSetting(value){}
};

template<class T>
class SignedSetting : public IncrementalSetting<T>
{
public:
	SignedSetting(const T& value = 0):IncrementalSetting(value){}
};

class UGUI_API IntSetting : public SignedSetting<int>
{
public:
	IntSetting(const int& value = 0):SignedSetting(value){}
	virtual void toString(std::string& str) const;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel);
};

class UGUI_API Int64Setting : public SignedSetting<__int64>
{
public:
	Int64Setting(const __int64& value = 0):SignedSetting(value){}
	virtual void toString(std::string& str) const;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel);
};

template<class T>
class UnsignedSetting : public IncrementalSetting<T>
{
public:
//	typedef T ValueType;
	UnsignedSetting(const SettingValueType& value = 0):IncrementalSetting(value){}
};

template<class T>
class MaskSetting : public UnsignedSetting<T>
{
public:
	MaskSetting(const SettingValueType& value = 0):UnsignedSetting(value){}
	virtual void toString(std::string& str) const
	{
		U_UIntToBitStr(m_value, str);
	}

	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel)
	{
		U_BitStrUInt(m_value, cursor, delimiter);
	}
};

class UGUI_API IpSetting : public UnsignedSetting<unsigned int>
{
public:
	IpSetting(const SettingValueType& value = 0):UnsignedSetting(value){}
	virtual void toString(std::string& str) const;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel);
};

class UGUI_API VersionSetting : public UnsignedSetting<unsigned __int64>
{
public:
	VersionSetting(const SettingValueType& value = 0) :UnsignedSetting(value){}
	virtual void toString(std::string& str) const;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel);
};

template<class T>
class StringAsUnsignedNumberSetting : public UnsignedSetting<T>
{
public:
	StringAsUnsignedNumberSetting(const SettingValueType& value = 0):UnsignedSetting(value){}
	virtual void toString(std::string& str) const override
	{
		U_AppendUnsignedNumberAsString(str, m_value);
	}
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override
	{
		std::string token;
		U_ReadStrToken(token, cursor, delimiter);
		m_value = U_RepresentStringAsUnsignedNumber<T>(token.c_str(), sizeof(T));
	}
	virtual bool operator<(const Setting& other) const{return U_CompareUIntAsString(m_value, ((const StringAsUnsignedNumberSetting&)other).m_value) < 0;}
};

template<class T>
class StringAsUnsignedNumberSettingTerm0 : public UnsignedSetting<T>
{
public:
	StringAsUnsignedNumberSettingTerm0(const SettingValueType& value = 0):UnsignedSetting(value){}
	virtual void toString(std::string& str) const override
	{
		U_AppendUnsignedNumberAsStringTerm0(str, m_value);
	}
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override
	{
		std::string token;
		U_ReadStrToken(token, cursor, delimiter);
		m_value = U_RepresentStringAsUnsignedNumber<T>(token.c_str(), sizeof(T) - 1);
	}
	virtual bool operator<(const Setting& other) const{return U_CompareUIntAsString(m_value, ((const StringAsUnsignedNumberSettingTerm0&)other).m_value) < 0;}
};

class UGUI_API StringAsUIntSetting : public StringAsUnsignedNumberSetting<unsigned int>
{
public:
	StringAsUIntSetting(const SettingValueType& value = 0):StringAsUnsignedNumberSetting(value){}
//	virtual void toString(std::string& str) const;
//	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel);
};

class UGUI_API StringAsUInt64Setting : public StringAsUnsignedNumberSettingTerm0<unsigned __int64>
{
public:
	StringAsUInt64Setting(const SettingValueType& value = 0):StringAsUnsignedNumberSettingTerm0(value){}
//	virtual void toString(std::string& str) const;
//	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel);
};

class UGUI_API UIntSetting : public UnsignedSetting<unsigned int>
{
public:
	UIntSetting(const unsigned int& value = 0):UnsignedSetting(value){}
	virtual void toString(std::string& str) const override;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override;
};

class UGUI_API DateSetting : public UnsignedSetting<unsigned int>
{
public:
	DateSetting(const unsigned int& value = 0):UnsignedSetting(value){}
	virtual void toString(std::string& str) const override;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override;
};

class UGUI_API FullYearDateSetting : public UnsignedSetting<unsigned int>
{
public:
	FullYearDateSetting(const unsigned int& value = 0):UnsignedSetting(value){}
	virtual void toString(std::string& str) const override;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override;
};

class UGUI_API UMillisecondSetting : public UnsignedSetting<unsigned int>
{
public:
	UMillisecondSetting(const unsigned int& value = 0):UnsignedSetting(value){}
	virtual void toString(std::string& str) const override;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override;
};

class UGUI_API USecondSetting : public UnsignedSetting<unsigned int>
{
public:
	USecondSetting(const unsigned int& value = 0):UnsignedSetting(value){}
	virtual void toString(std::string& str) const override;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override;
};

class UGUI_API UIntHexSetting : public UnsignedSetting<unsigned int>
{
public:
	UIntHexSetting(const unsigned int& value = 0):UnsignedSetting(value){}
	virtual void toString(std::string& str) const override;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override;
};

class UGUI_API UShortHexSetting : public UnsignedSetting<unsigned short>
{
public:
	UShortHexSetting(const unsigned short& value = 0):UnsignedSetting(value){}
	virtual void toString(std::string& str) const override;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override;
};

class UGUI_API UCharHexSetting : public UnsignedSetting<unsigned char>
{
public:
	UCharHexSetting(const unsigned char& value = 0):UnsignedSetting(value){}
	virtual void toString(std::string& str) const override;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override;
};

class UGUI_API UInt64Setting : public UnsignedSetting<unsigned __int64>
{
public:
	UInt64Setting(const unsigned __int64& value = 0):UnsignedSetting(value){}
	virtual void toString(std::string& str) const override;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override;
};

class UGUI_API UInt64HexSetting : public UnsignedSetting<unsigned __int64>
{
public:
	UInt64HexSetting(const unsigned __int64& value = 0):UnsignedSetting(value){}
	virtual void toString(std::string& str) const override;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override;
};

class UGUI_API UCharSetting : public UnsignedSetting<unsigned char>
{
public:
	UCharSetting(const unsigned char& value = 0):UnsignedSetting(value){}
	virtual void toString(std::string& str) const override;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override;
};

class UGUI_API CharSetting : public SignedSetting<char>
{
public:
	CharSetting(const char& value = 0):SignedSetting(value){}
	virtual void toString(std::string& str) const override;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override;
};

class UGUI_API UCharAsCharSetting : public UCharSetting
{
public:
	UCharAsCharSetting(const unsigned char& value = 0):UCharSetting(value){}
	virtual void toString(std::string& str) const override;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override;
};

class UGUI_API UShortSetting : public UnsignedSetting<unsigned short>
{
public:
	UShortSetting(const unsigned short& value = 0):UnsignedSetting(value){}
	virtual void toString(std::string& str) const override;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override;
};

class UGUI_API StringSetting : public TypeSetting<std::string>
{
public:
//	StringSetting(const char* name, const std::string& value = std::string("")):TypeSetting<std::string>(name, value){}
	StringSetting(const std::string& value = std::string("")):TypeSetting(value){}
	StringSetting(const char* const& value):TypeSetting(std::string(value)){}
	StringSetting(const unsigned short& value):TypeSetting(U_GetStringFromNumber(value)){}
	StringSetting(const unsigned int& value):TypeSetting(U_GetStringFromNumber(value)){}
	StringSetting(const unsigned __int64& value):TypeSetting(U_GetStringFromNumber(value)){}
	virtual void toString(std::string& str) const override{str += m_value;}
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override;//{U_ReadStrToken(m_value, cursor, settingDel);}
//	operator size_t() const;
	bool SetStrValue(const char* const& value)
	{
		if(strcmp(m_value.c_str(), value))
		{
			m_value = value;
			return true;
		}
		return false;
	}
/*Use SetValue(const std::string& value)
	bool SetStrValue(const std::string& value)
	{
		if(value != m_value)
		{
			m_value = value;
			return true;
		}
		return false;
	}
*/
	bool AppendStrValue(const char* const& value)
	{
		if(value && *value)
		{
			m_value += value;
			return true;
		}
		return false;
	}
	bool AppendCharValue(const char& value)
	{
		if(value)
		{
			m_value += value;
			return true;
		}
		return false;
	}
};

class UGUI_API StringSettingRest : public StringSetting
{
public:
	StringSettingRest(const std::string& value = std::string("")):StringSetting(value){}
	StringSettingRest(const char* const& value):StringSetting(value){}
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override{m_value = cursor;}
};

class UGUI_API AggregateSetting : public Setting
{
public:
	typedef std::list<Setting*> SettingList;
	const SettingList& GetSettingList() const{return m_settingList;}
	SettingList& GetSettingList(){return m_settingList;}
	AggregateSetting& operator=(const AggregateSetting& other);
//	virtual void AppendAggregateDelimiter(std::string& str) const{str += sectionDel}
	virtual void toString(std::string& str) const override;
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel) override;
	virtual bool operator==(const Setting& other) const;
	virtual bool operator<(const Setting& other) const;
	virtual void CopySetting(const Setting& other) override;
	virtual unsigned int GetItemCount() const override;
	virtual bool isDefaultValue() const override;
	virtual void UpdateDefaultValue() const override;
	virtual void Uninitialize();
protected:
	void AddSetting(Setting& setting){m_settingList.push_back(&setting);}
	AggregateSetting(const char& delimiter = settingDel, const char& lastDelimiter = '\0'):m_delimiter(delimiter), m_lastDelimiter(lastDelimiter){}
	AggregateSetting(const AggregateSetting& other):Setting(other),m_delimiter(other.m_delimiter), m_lastDelimiter(other.m_lastDelimiter){}
	SettingList m_settingList;
	char m_delimiter;
	char m_lastDelimiter;
};

template<class S1, class S2>
class PairSetting : public AggregateSetting
{
public:
	PairSetting()
	{
		AddSettings();
	}
	PairSetting(const S1& s1, const S2& s2):
		m_first(s1),
		m_second(s2)
	{
		AddSettings();
	}
	PairSetting(const PairSetting& other):
		AggregateSetting(other),
		m_first(other.m_first),
		m_second(other.m_second)
	{
		AddSettings();
	}
	S1 m_first;
	S2 m_second;
protected:
	void AddSettings()
	{
		AddSetting(m_first);
		AddSetting(m_second);
	}
};

class UGUI_API ColumnSetting : public AggregateSetting
{
public:
	ColumnSetting(unsigned short id = 0,
		int defaultWidth = 1,
		unsigned char alignment = 0,
		bool ascendingSort = false,
		unsigned short secondarySort = 0,
		bool follows = false,
		bool use = true,
		bool globalUse = true):
		AggregateSetting('\\'),
		m_id(id),
		m_defaultWidth(defaultWidth),
		m_alignment(alignment),
		m_ascendingSort(ascendingSort),
		m_secondarySort(secondarySort),
		m_follows(follows),
		m_use(use),
		m_globalUse(globalUse)
	{
		AddSettings();
	}

	ColumnSetting(const ColumnSetting& other):
		AggregateSetting(other),
		m_id(other.m_id),
		m_defaultWidth(other.m_defaultWidth),
		m_alignment(other.m_alignment),
		m_ascendingSort(other.m_ascendingSort),
		m_secondarySort(other.m_secondarySort),
		m_follows(other.m_follows),
		m_use(other.m_use),
		m_globalUse(other.m_globalUse)
	{
		AddSettings();
	}

	UShortSetting m_id;
	IntSetting m_defaultWidth;
	UCharSetting m_alignment;
	BoolSetting m_ascendingSort;
	UShortSetting m_secondarySort;
	BoolSetting m_use;
	BoolSetting m_globalUse;
	BoolSetting m_follows;
protected:
	void AddSettings()
	{
		AddSetting(m_id);
		AddSetting(m_defaultWidth);
		AddSetting(m_alignment);
		AddSetting(m_ascendingSort);
		AddSetting(m_secondarySort);
		AddSetting(m_use);
		AddSetting(m_globalUse);
		AddSetting(m_follows);
	}
};

enum Spacing : unsigned char
{
	SPACING_EXTRA_SMALL,
	SPACING_SMALL,
	SPACING_MEDIUM,
	SPACING_LARGE,
	SPACING_EXTRA_LARGE,

	SPACING_COUNT
};

const char* const SpacingNames[] =
{
	"X Small",
	"Small",
	"Medium",
	"Large",
	"X Large",
	nullptr
};

class StringName
{
public:
	virtual ~StringName(){}
	const char* GetName() const{return m_name.c_str();}
	const std::string& GetNameStr() const{return m_name;}
	bool SetName(const char* const& name)
	{
		if(strcmp(name, m_name.c_str()))
		{
			m_name = name;
			return true;
		}
		return false;
	}
	bool SetName(const std::string& name)
	{
		if(name != m_name)
		{
			m_name = name;
			return true;
		}
		return false;
	}
//	bool operator<(const StringName& other) const{return m_name < other.m_name;}
//	bool operator==(const StringName& other) const{return m_name == other.m_name;}
//	bool operator!=(const Graphics& other) const{return !operator==(other);}
protected:
	StringName(const char* const& name):m_name(name){}
	StringName(const std::string& name):m_name(name){}
	std::string m_name;
};

class NamedColor : public StringName
{
public:
	NamedColor(const char* name = "", COLORREF color = 0xFFFFFFFF):StringName(name),m_color(color),m_defaultColor(color),m_oppositeColor(UGUI_GetOppositeColor(color)){}
	NamedColor(const std::string& name, COLORREF color = 0xFFFFFFFF):StringName(name),m_color(color),m_defaultColor(color),m_oppositeColor(UGUI_GetOppositeColor(color)){}
//	const char* GetName() const{return m_name.c_str();}
//	const std::string& GetNameStr() const{return m_name;}
	const COLORREF& GetColor() const{return m_color;}
	bool SetColor(const COLORREF& color)
	{
		if(color != m_color)
		{
			m_color = color;
			m_oppositeColor = UGUI_GetOppositeColor(color);
			return true;
		}
		return false;
	}
	const COLORREF& GetDefaultColor() const{return m_defaultColor;}
	bool SetDefaultColor(){return SetColor(m_defaultColor);}
	bool isDefaultColor() const{return m_color == m_defaultColor;}
	const COLORREF& GetOppositeColor() const{return m_oppositeColor;}
protected:
//	std::string m_name;
	COLORREF m_color;
	COLORREF m_defaultColor;
	COLORREF m_oppositeColor;
};

class UGUI_API SettingCollection : public Setting
{
public:
	virtual void ReadFromStreamAsString(std::ifstream& istr, std::string& result);
protected:
//	SettingCollection(const char* name):Setting(name){}
	SettingCollection(const unsigned int& reserveValueStr = 1024):
#ifdef _DEBUG
		m_maxReserveValueStr(0),
#endif
		m_reserveValueStr(reserveValueStr)
	{}
#ifdef _DEBUG
	unsigned int m_maxReserveValueStr;
#endif
	unsigned int m_reserveValueStr;
};

template<class C>
class TypeSettingCollection : public SettingCollection
{
public:
	typedef C CollectionType;
	typedef typename C::const_iterator ConstIterator;
	typedef typename C::iterator Iterator;
	ConstIterator GetConstBegin() const{return m_value.cbegin();}
	ConstIterator GetConstEnd() const{return m_value.cend();}
	Iterator GetBegin(){return m_value.begin();}
	Iterator GetEnd(){return m_value.end();}
	Iterator EraseValue(Iterator& it){return m_value.erase(it);}
	Iterator EraseValues(Iterator& it, Iterator& to){return m_value.erase(it, to);}
	bool isEmpty() const{return m_value.empty();}
	bool Clear()
	{
		if(m_value.empty())return false;
		m_value.clear();
		return true;
	}
	unsigned int GetCount() const{return (unsigned int)m_value.size();}
	bool SetValue(const C& value)
	{
		if(m_value != value)
		{
			m_value = value;
			return true;
		}
		return false;
	}
	void RemoveValues(Iterator& start, Iterator& end)
	{
		m_value.erase(start, end);
	}
	Iterator RemoveIterator(Iterator& it)
	{
		return m_value.erase(it);
	}
	void Truncate(const unsigned int& size)
	{
		if(size < (unsigned int)m_value.size())
		{
			m_value.resize(size);
		}
	}
	const C& GetValue() const{return m_value;}
	C& GetValue(){return m_value;}
	const C& GetDefaultValue() const{return m_defaultValue;}
	virtual bool isDefaultValue() const override{return m_defaultValue == m_value;}
	virtual void UpdateDefaultValue() const override
	{
		for(ConstIterator it = m_value.cbegin(), itend = m_value.cend(); it != itend; ++it)
		{
			UpdateDefaultElement(it);
		}
		m_defaultValue = m_value;
	}
	virtual void Uninitialize() override
	{
		m_value = m_defaultValue;
		m_initializedFromFile = false;
	}
	virtual bool operator==(const Setting& other) const
	{
//		const MapSetting<K, V, C>& otherMap = (const MapSetting<K, V, C>&)other;
		const TypeSettingCollection& otherMap = (const TypeSettingCollection&)other;
		if(m_value.size() != otherMap.m_value.size())
		{
			return false;
		}
		ConstIterator it = m_value.cbegin();
		ConstIterator itend = m_value.cend();
		ConstIterator itOther = otherMap.m_value.cbegin();
		ConstIterator itendOther = otherMap.m_value.cend();
		for(; it != itend && itOther != itendOther; ++it, ++itOther)
		{
			if(*it != *itOther)
//			if(it->first != itOther->first || it->second != itOther->second)
			{
				return false;
			}
		}
		return true;
	}

	virtual bool operator<(const Setting& other) const
	{
//		const MapSetting<K, V, C>& otherMap = (const MapSetting<K, V, C>&)other;
		const TypeSettingCollection& otherMap = (const TypeSettingCollection&)other;
		if(m_value.size() < otherMap.m_value.size())
		{
			return true;
		}
		if(m_value.size() > otherMap.m_value.size())
		{
			return false;
		}
		ConstIterator it = m_value.cbegin();
		ConstIterator itend = m_value.cend();
		ConstIterator itOther = otherMap.m_value.cbegin();
		ConstIterator itendOther = otherMap.m_value.cend();
		for(; it != itend && itOther != itendOther; ++it, ++itOther)
		{
			switch(CompareElement(it, itOther))
			{
				case -1:
				return true;

				case 1:
				return false;
			}
		}
		return false;
	}

	virtual void CopySetting(const Setting& other)
	{
		m_value = ((const TypeSettingCollection&)other).m_value;
		m_initializedFromFile = other.isInitializedFromFile();
	}
	virtual int CompareElement(ConstIterator& it, ConstIterator& itOther) const = 0;
	virtual bool isDelimiterAtEnd() const override{return m_delimiterAtEnd;}
	virtual bool ToSkipDelimiterAtEnd() const override{return isDelimiterAtEnd() && !m_value.empty();}
protected:
	TypeSettingCollection(const char& delimiter = '\n', const char& delimiter2 = '\n', const bool& delimiterAtEnd = false, const unsigned int& reserveValueStr = 1024):
		SettingCollection(reserveValueStr),
		m_delimiter(delimiter),
		m_delimiter2(delimiter2),
		m_delimiterAtEnd(delimiterAtEnd)
	{}
	virtual void UpdateDefaultElement(ConstIterator& it) const = 0;
	C m_value;
	mutable C m_defaultValue;
	char m_delimiter;
	char m_delimiter2;
	bool m_delimiterAtEnd;
};

template<class K, class V, class C, char DEL = '\n'>
class PairIteratorCollection : public TypeSettingCollection<C>
{
public:
	typedef K KeyType;
	typedef V ValueType;
	V* AddValue(const KeyType& key, const ValueType& val)
	{
#if(_MSC_VER > 1600)
		return &m_value.insert_or_assign(key, val).first->second;
#else
		Iterator found = m_value.find(key);
		if(found == m_valueEnd)//m_value.end())
		{
			return &m_value.insert(C::value_type(key, val)).first->second;
		}
		else
		{
			found->second = val;
			return &found->second;
		}
#endif
	}
	V* AddDefaultValue(const KeyType& key, const ValueType& val)
	{
#if(_MSC_VER > 1600)
		std::pair<Iterator, bool> ret = m_value.insert_or_assign(key, value);
		if(ret.second)m_defaultValue.insert(C::value_type(key, val));
		return &ret.first->second;
#else
		if(found == m_valueEnd)//m_value.end())
		{
			C::value_type value(key, val);
			Iterator found = m_value.find(key);
			m_defaultValue.insert(value);
			return &m_value.insert(value).first->second;
		}
		else
		{
			found->second = val;
			return &found->second;
		}
#endif
	}
	Iterator DoInsertValue(const KeyType& key, const ValueType& val)
	{
		return m_value.insert(C::value_type(key, val)).first;
	}
	bool RemoveValue(const KeyType& key)
	{
		return m_value.erase(key) != 0;
	}

	ConstIterator FindIterator(const KeyType& key) const{return m_value.find(key);}
	Iterator FindIterator(const KeyType& key){return m_value.find(key);}
	const V* FindValue(const KeyType& key) const
	{
		ConstIterator found = m_value.find(key);
//		return found == m_value.cend() ? nullptr : &found->second;
		return found == m_constValueEnd ? nullptr : &found->second;
	}
	V* FindValue(const K& key)
	{
		Iterator found = m_value.find(key);
//		return found == m_value.end() ? nullptr : &found->second;
		return found == m_valueEnd ? nullptr : &found->second;
	}

/*
	virtual void CopySetting(const Setting& other)
	{
		m_value.clear();
		const PairIteratorCollection& otherMap = (const PairIteratorCollection&)other;
		ConstIterator itOther = otherMap.m_value.cbegin();
		ConstIterator itendOther = otherMap.m_value.cend();
		for(; itOther != itendOther; ++itOther)
		{
			m_value.insert(C::value_type(itOther->first, itOther->second));
		}
		m_initializedFromFile = other.isInitializedFromFile();
	}
*/
	virtual int CompareElement(ConstIterator& it, ConstIterator& itOther) const
	{
		return it->first < itOther->first ? -1:
			itOther->first < it->first ? 1:
			it->second < itOther->second ? -1:
			itOther->second < it->second ? 1:
			0;
	}
	const Iterator& GetMyEnd() const{return m_valueEnd;}
	const ConstIterator& GetMyConstEnd() const{return m_constValueEnd;}
	PairIteratorCollection& operator=(const PairIteratorCollection& other)//because of Iterator m_valueEnd;
	{
		TypeSettingCollection::operator=(other);
		return *this;
	}
protected:
	PairIteratorCollection(const char& delimiter = '\n', const char& delimiter2 = '\n', const bool& delimiterAtEnd = false, const unsigned int& reserveValueStr = 1024):
		TypeSettingCollection(delimiter, delimiter2, delimiterAtEnd, reserveValueStr),
		m_valueEnd(m_value.end()),
		m_constValueEnd(m_value.cend())
	{}
	PairIteratorCollection(const PairIteratorCollection& other)://because of Iterator m_valueEnd;
		TypeSettingCollection(other),
		m_valueEnd(m_value.end()),
		m_constValueEnd(m_value.cend())
	{}
	virtual void UpdateDefaultElement(ConstIterator& it) const override
	{
//		((K&)it->first).UpdateDefaultValue();
		it->first.UpdateDefaultValue();
		it->second.UpdateDefaultValue();
	}
	Iterator m_valueEnd;
	ConstIterator m_constValueEnd;
};

template<class K, class V, class C, char DEL = '\n'>
class MapSetting : public PairIteratorCollection<K, V, C, DEL>
{
public:
	MapSetting(const char& delimiter = DEL, const char& delimiter2 = '\n', const bool& delimiterAtEnd = false, const bool& emptyKeyOK = false, const unsigned int& reserveValueStr = 1024):
		PairIteratorCollection(delimiter, delimiter2, delimiterAtEnd, reserveValueStr),
		m_emptyKeyOK(emptyKeyOK)
	{}
	virtual void toString(std::string& str) const
	{
		ConstIterator it = m_value.cbegin();
		ConstIterator itend = m_value.cend();
		if(it != itend)
		{
			while(true)// it != itend; ++it)
			{
				str += settingSubdel;
				it->first.toString(str);
				str += settingSubdel;
				it->second.toString(str);
	//			str += '\r';
				++it;
				if(it == itend)
				{
					if(m_delimiterAtEnd)//09/13/2020
					{
						str += m_delimiter;
					}
					break;
				}
				str += m_delimiter;//'\n';
			}
		}
//09/13/2020
//		if(m_delimiterAtEnd)
//		{
//			str += m_delimiter;
//		}
//		str += settingSubdel;
	}
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel)
	{
		m_value.clear();
		if(*cursor == settingSubdel)
		{
			std::string keyStr;
			std::string valueStr;
			valueStr.reserve(m_reserveValueStr);
#ifdef _DEBUG
			if((unsigned int)valueStr.capacity() > m_maxReserveValueStr)
			{
				m_maxReserveValueStr = (unsigned int)valueStr.capacity();
			}
#endif
			const char* cur;
			while(true)
			{
				if(*cursor == settingSubdel)
				{
					++cursor;
					keyStr.clear();
					if(U_ReadStrTokenToMandatoryDel(keyStr, cursor, settingSubdel, '\n'))
					{
						if(!keyStr.empty() || m_emptyKeyOK)
						{
							valueStr.clear();
							if(U_ReadStrTokenWith2Delimiters(valueStr, cursor, m_delimiter, m_delimiter2))//'\n'))
							{
								K key;
								cur = keyStr.c_str();
								key.fromString(cur, version);
								V val;
								cur = valueStr.c_str();
	//							val.fromString(cur, version);
								val.fromString(cur, version, m_delimiter);
								m_value.insert(C::value_type(key, val));
							}
						}
					}
				}
				else
				{
					break;
				}
			}
#ifdef _DEBUG
			if((unsigned int)valueStr.capacity() > m_maxReserveValueStr)
			{
				m_maxReserveValueStr = (unsigned int)valueStr.capacity();
			}
#endif
		}
//Added 05/03/2011
		else if(*cursor)
		{
			++cursor;
		}
	}

protected:
	bool m_emptyKeyOK;
};

template<class V, class C, char DEL = '\n'>
class SingleIteratorCollection : public TypeSettingCollection<C>
{
public:
	typedef V ValueType;
/*
	virtual void CopySetting(const Setting& other)
	{
		m_value.clear();
		const SingleIteratorCollection& otherMap = (const SingleIteratorCollection&)other;
		ConstIterator itOther = otherMap.m_value.cbegin();
		ConstIterator itendOther = otherMap.m_value.cend();
		for(; itOther != itendOther; ++itOther)
		{
			m_value.insert(*itOther);
		}
		m_initializedFromFile = other.isInitializedFromFile();
	}
*/
	virtual int CompareElement(ConstIterator& it, ConstIterator& itOther) const
	{
		return *it < *itOther ? -1 :
			*itOther < *it ? 1 :
			0;
	}
protected:
	SingleIteratorCollection(const char& delimiter = '\n', const char& delimiter2 = '\n', const bool& delimiterAtEnd = false, const unsigned int& reserveValueStr = 1024) :
		TypeSettingCollection(delimiter, delimiter2, delimiterAtEnd, reserveValueStr)
	{}
	virtual void UpdateDefaultElement(ConstIterator& it) const override
	{
//		((V&)*it).UpdateDefaultValue();
		it->UpdateDefaultValue();
	}
};

template<class V, class C, char DEL = '\n'>
class SetSetting : public SingleIteratorCollection<V, C, DEL>
{
public:
	SetSetting(char delimiter = DEL, char delimiter2 = '\n', bool delimiterAtEnd = false, const unsigned int& reserveValueStr = 1024):
		SingleIteratorCollection(delimiter, delimiter2, delimiterAtEnd, reserveValueStr)
	{}
	const V* AddValue(const V& val)//return const, because you might not be able to modify the value without breaking the sorting; cast to non const if you want to modify it and there will be no sort violation
	{
		Iterator found = m_value.find(val);
		if(found == m_value.end())
		{
			return &*m_value.insert(val).first;
		}
		else
		{
			return &*found;
		}
	}
	const V* AddDefaultValue(const V& val)//return const, because you might not be able to modify the value without breaking the sorting; cast to non const if you want to modify it and there will be no sort violation
	{
		Iterator found = m_value.find(val);
		if(found == m_value.end())
		{
			m_defaultValue.insert(val);
			return &*m_value.insert(val).first;
		}
		else
		{
			return &*found;
		}
	}
	Iterator DoInsertValue(const V& val)
	{
		return m_value.insert(val).first;
	}
	bool RemoveValue(const V& val)
	{
		return m_value.erase(val) != 0;
	}

	ConstIterator FindIterator(const V& value) const{return m_value.find(value);}
	Iterator FindIterator(const V& value){return m_value.find(value);}
	const V* FindValue(const V& value) const
	{
		ConstIterator found = m_value.find(value);
		return found == m_value.cend() ? nullptr : &*found;
	}
/*
	V* FindValue(const V& value)
	{
		Iterator found = m_value.find(value);
		return found == m_value.end() ? nullptr : &*found;
	}
*/
	virtual void toString(std::string& str) const
	{
		ConstIterator it = m_value.cbegin();
		ConstIterator itend = m_value.cend();
		if(it != itend)
		{
			while(true)// it != itend; ++it)
			{
				str += settingSubdel;
				it->toString(str);
	//			str += '\r';
				++it;
				if(it == itend)
				{
					if(m_delimiterAtEnd)//09/13/2020
					{
						str += m_delimiter;
					}
					break;
				}
				str += m_delimiter;//'\n';
			}
		}
//09/13/2020
//		if(m_delimiterAtEnd)
//		{
//			str += m_delimiter;
//		}

//		str += settingSubdel;
	}
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel)
	{
		m_value.clear();
		if(*cursor == settingSubdel)
		{
			std::string valueStr;
			valueStr.reserve(m_reserveValueStr);
#ifdef _DEBUG
			if((unsigned int)valueStr.capacity() > m_maxReserveValueStr)
			{
				m_maxReserveValueStr = (unsigned int)valueStr.capacity();
			}
#endif
			const char* cur;
			while(true)
			{
				if(*cursor == settingSubdel)
				{
					++cursor;
					valueStr.clear();
					if(U_ReadStrTokenWith2Delimiters(valueStr, cursor, m_delimiter, m_delimiter2))//'\n'))
					{
						V val;
						cur = valueStr.c_str();
						val.fromString(cur, version, m_delimiter);
						m_value.insert(val);
					}
				}
				else
				{
					break;
				}
			}
#ifdef _DEBUG
			if((unsigned int)valueStr.capacity() > m_maxReserveValueStr)
			{
				m_maxReserveValueStr = (unsigned int)valueStr.capacity();
			}
#endif
		}
//Added 05/03/2011
		else if(*cursor)
		{
			++cursor;
		}
	}
/*
	virtual void CopySetting(const Setting& other)
	{
		m_value.clear();
		const SetSetting& otherMap = (const SetSetting&)other;
		ConstIterator itOther = otherMap.m_value.cbegin();
		ConstIterator itendOther = otherMap.m_value.cend();
		for(; itOther != itendOther; ++itOther)
		{
			m_value.insert(*itOther);
		}
		m_initializedFromFile = other.isInitializedFromFile();
	}
	virtual int CompareElement(ConstIterator& it, ConstIterator& itOther) const
	{
		return *it < *itOther ? -1:
			*itOther < *it ? 1:
			0;
	}
*/
};

template<class V, char DEL = settingDel>//, class C>
class VectorSetting : public SingleIteratorCollection<V, std::vector<V>, DEL>//<C>
{
public:
//	VectorSetting(char delimiter = '\n', char delimiter2 = '\n'):SingleIteratorCollection(delimiter, delimiter2){}
	VectorSetting(const char& delimiter = DEL, const char& delimiter2 = '\n', const bool& delimiterAtEnd = false, const char& terminator = '\0', const unsigned int& reserveValueStr = 1024):
		SingleIteratorCollection(delimiter, delimiter2, delimiterAtEnd, reserveValueStr),
		m_terminator(terminator)
	{}
	V* AddValue(const V& val)
	{
		m_value.push_back(val);
		return &m_value.back();
	}
	V* AddDefaultValue(const V& val)
	{
		m_defaultValue.push_back(val);
		return AddValue(val);
	}
	bool SetValueAt(const V& val, unsigned int i)
	{
		const unsigned int size = (unsigned int)m_value.size();
		if(i < size)
		{
			if(!(m_value[i] == val))
			{
				m_value[i] = val;
				return true;
			}
		}
		return false;
	}
	bool ForceSetValueAt(const V& val, unsigned int i, const V& defaultValue)
	{
		unsigned int size = (unsigned int)m_value.size();
		if(i < size)
		{
			if(!(m_value[i] == val))
			{
				m_value[i] = val;
				return true;
			}
			return false;
		}
		else
		{
			for(; size < i; ++size)
			{
				m_value.push_back(defaultValue);
			}
			m_value.push_back(val);
			return true;
		}
	}
	V* GetValueAt(const unsigned int& i){return i < (unsigned int)m_value.size() ? &m_value[i] : nullptr;}
	const V* GetValueAt(const unsigned int& i) const{return i < (unsigned int)m_value.size() ? &m_value[i] : nullptr;}
/*
	void Truncate(const unsigned int& size)
	{
		if(size < (unsigned int)m_value.size())
		{
			m_value.resize(size);
		}
	}
*/
	void InsertValue(const V& val, const unsigned int& i)
	{
		const unsigned int size = (unsigned int)m_value.size();
		AddValue(val);
		if(i < size)
		{
			Iterator it = m_value.begin();
			it += i;
			m_value.insert(it, val);
/*
			for(; i < size; --size)
			{
				m_value[size] = m_value[size - 1];
			}
			m_value[i] = val;
*/
		}
	}
	bool RemoveValue(const unsigned int& i)
	{
		const unsigned int size = (unsigned int)m_value.size();
		if(i < size)
		{
			Iterator it = m_value.begin();
			it += i;
			m_value.erase(it);
/*
			for(; i < size; ++i)
			{
				m_value[i] = m_value[i + 1];
			}
*/
			return true;
		}
		return false;
	}
	bool RemoveLastValue()
	{
		if(m_value.empty())
		{
			return false;
		}
		m_value.pop_back();
		return true;
	}
	virtual void toString(std::string& str) const
	{
		ConstIterator it = m_value.cbegin();
		ConstIterator itend = m_value.cend();
		if(it != itend)
		{
			while(true)// it != itend; ++it)
			{
				str += settingSubdel;
				it->toString(str);
	//			str += '\r';
				++it;
				if(it == itend)
				{
					if(m_delimiterAtEnd)//09/13/2020
					{
						str += m_delimiter;
					}
					break;
				}
				str += m_delimiter;//'\n';
			}
		}
//09/13/2020
//		if(m_delimiterAtEnd)
//		{
//			str += m_delimiter;
//		}

//		str += settingSubdel;
	}
	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel)
	{
		m_value.clear();
		if(*cursor == settingSubdel)
		{
			std::string valueStr;
			valueStr.reserve(m_reserveValueStr);
#ifdef _DEBUG
			if((unsigned int)valueStr.capacity() > m_maxReserveValueStr)
			{
				m_maxReserveValueStr = (unsigned int)valueStr.capacity();
			}
#endif
//03/03/2018
			if(m_terminator)
			{
				std::string allStr;
				U_ReadStrToken(allStr, cursor, m_delimiter2);//delimiter);
				const char* allCursor = allStr.c_str();
//
				const char* cur;
				while(true)
				{
					if(*allCursor == settingSubdel)
					{
						++allCursor;
						valueStr.clear();
						if(U_ReadStrTokenWith2Delimiters(valueStr, allCursor, m_delimiter, m_delimiter2))//'\n'))
						{
							V val;
							cur = valueStr.c_str();
							val.fromString(cur, version, m_delimiter);
							m_value.push_back(val);
						}
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				const char* cur;
				while(true)
				{
					if(*cursor == settingSubdel)
					{
						++cursor;
						valueStr.clear();
						if(U_ReadStrTokenWith2Delimiters(valueStr, cursor, m_delimiter, m_delimiter2))//'\n'))
						{
							V val;
							cur = valueStr.c_str();
							val.fromString(cur, version, m_delimiter);
							m_value.push_back(val);
						}
					}
					else
					{
						break;
					}
				}
			}
#ifdef _DEBUG
			if((unsigned int)valueStr.capacity() > m_maxReserveValueStr)
			{
				m_maxReserveValueStr = (unsigned int)valueStr.capacity();
			}
#endif
		}
//Added 05/03/2011
		else if(*cursor)
		{
			++cursor;
		}
	}
/*
	virtual void CopySetting(const Setting& other)
	{
		m_value = ((const VectorSetting&)other).m_value;
		m_initializedFromFile = other.isInitializedFromFile();
	}
	virtual int CompareElement(ConstIterator& it, ConstIterator& itOther) const
	{
		return *it < *itOther ? -1:
			*itOther < *it ? 1:
			0;
	}
*/
protected:
	char m_terminator;
};

enum LayoutFlags : unsigned char
{
	LF_COMMANDS,
	LF_COMMAND_MAP,
	LF_WINDOWS,
	LF_COLUMNS,
	LF_ALERTS,
	LF_PHANTOMS,
	LF_GRAPHICS,
	LF_BASKETS,
	LF_NEWS_FILTER,
	LF_CALC_INDEX,
	LF_SECURITY_NOTES,
	LF_NAMED_FILTERS,
	LF_OTHER,

	LF_COUNT
};

class Graphics;

class UGUI_API GraphicsSetting : public AggregateSetting
{
public:
	GraphicsSetting():
		m_horizontalSpacing(SPACING_MEDIUM),
		m_verticalSpacing(SPACING_MEDIUM),
		m_colorMap('\\', settingDel, false, false)//, true)
	{
		AddSettings();
	}
	GraphicsSetting(const GraphicsSetting& other):
		AggregateSetting(other),
		m_fontName(other.m_fontName),
		m_fontSize(other.m_fontSize),
		m_fontMaxSize(other.m_fontMaxSize),
		m_fontBold(other.m_fontBold),
		m_fontItalic(other.m_fontItalic),

		m_horizontalSpacing(other.m_horizontalSpacing),
		m_verticalSpacing(other.m_verticalSpacing),
		m_colorMap(other.m_colorMap)
	{
		AddSettings();
	}

	void Init(const Graphics& graphics);

//	virtual void toString(std::string& str) const;
//	virtual void fromString(const char*& cursor, unsigned __int64 version, char delimiter = settingDel);

	StringSetting m_fontName;
	UIntSetting m_fontSize;
	UIntSetting m_fontMaxSize;
	BoolSetting m_fontBold;
	BoolSetting m_fontItalic;

	UCharSetting m_horizontalSpacing;
	UCharSetting m_verticalSpacing;

	typedef MapSetting<StringSetting, UIntSetting, std::map<StringSetting, UIntSetting> > ColorMap;
	ColorMap m_colorMap;
protected:
	void AddSettings()
	{
		AddSetting(m_fontName);
		AddSetting(m_fontSize);
		AddSetting(m_fontMaxSize);
		AddSetting(m_fontBold);
		AddSetting(m_colorMap);
		AddSetting(m_horizontalSpacing);
		AddSetting(m_verticalSpacing);
		AddSetting(m_fontItalic);
	}
};

class UGUI_API Graphics : public FontDescription, public StringName
{
public:
	Graphics(const char* name,
		const char* fontName,
		unsigned int fontSize,
		bool hasMaxSize,
		unsigned int fontMaxSize,
		bool fontBold,
		unsigned char horizontalSpacing,
		unsigned char verticalSpacing,
		const char* horizontalSpacingName = "Horizontal",
		const char* verticalSpacingName = "Vertical"):
		FontDescription(fontName ? fontName : "", fontSize, hasMaxSize, fontMaxSize, fontBold),
		StringName(name),
		m_horizontalSpacing(horizontalSpacing),
		m_verticalSpacing(verticalSpacing),
		m_colorMapBegin(m_colorMap.cbegin()),
		m_colorMapEnd(m_colorMap.cend()),
		m_colorVectorConstBegin(m_colorVector.cbegin()),
		m_colorVectorConstEnd(m_colorVector.cend()),
		m_colorVectorBegin(m_colorVector.begin()),
//		m_colorVectorEnd(m_colorVector.end()),
		m_hasFont(fontName != nullptr),
		m_horizontalSpacingName(horizontalSpacingName),
		m_verticalSpacingName(verticalSpacingName)
	{
	}
//	static const unsigned int colorCount = 20;
//	const char* GetName() const{return m_name.c_str();}
//	const std::string& GetNameStr() const{return m_name;}
	bool operator<(const Graphics& other) const{return m_name < other.m_name;}
	bool operator==(const Graphics& other) const
	{
		return FontDescription::operator==(other)
			&& m_horizontalSpacing == other.m_horizontalSpacing
			&& m_verticalSpacing == other.m_verticalSpacing
			&& SameColors(other);
	}
	bool operator!=(const Graphics& other) const
	{
		return !operator==(other);
	}
	void Copy(const Graphics& other)
	{
		FontDescription::operator=(other);
		m_horizontalSpacing = other.m_horizontalSpacing;
		m_verticalSpacing = other.m_verticalSpacing;
//??
		m_colorMap = other.m_colorMap;
		m_colorMapBegin = m_colorMap.cbegin();
//
		m_colorVector = other.m_colorVector;
		m_colorVectorBegin = m_colorVector.begin();
//		m_colorVectorEnd = m_colorVector.end();
		m_colorVectorConstBegin = m_colorVector.cbegin();
		m_colorVectorConstEnd = m_colorVector.cend();
	}

	unsigned char GetHorizontalSpacing() const{return m_horizontalSpacing;}
	unsigned char GetVerticalSpacing() const{return m_verticalSpacing;}

	void SetHorizontalSpacing(unsigned char spacing){m_horizontalSpacing = spacing;}
	void SetVerticalSpacing(unsigned char spacing){m_verticalSpacing = spacing;}

#if(_MSC_VER > 1600)
	typedef std::unordered_map<FilterStringAsNumberArray, unsigned short, TakionHashValue<FilterStringAsNumberArray> > ColorMap;
#else
	typedef std::hash_map<FilterStringAsNumberArray, unsigned short> ColorMap;
#endif
	typedef std::vector<NamedColor> ColorVector;
	typedef ColorVector::const_iterator ColorConstIterator;
	typedef ColorVector::iterator ColorIterator;

	unsigned short GetColorCount() const{return (unsigned short)m_colorVector.size();}

	const ColorVector& GetColorVector() const{return m_colorVector;}
	ColorConstIterator GetColorVectorBegin() const{return m_colorVectorConstBegin;}
	ColorConstIterator GetColorVectorEnd() const{return m_colorVectorConstEnd;}

	NamedColor* FindColor(const std::string& name)
	{
		ColorMap::iterator found = m_colorMap.find(FilterStringAsNumberArray(name));
		return found == m_colorMapEnd ? nullptr : &m_colorVector[found->second];
	}
	const NamedColor* FindColor(const std::string& name) const
	{
		ColorMap::const_iterator found = m_colorMap.find(FilterStringAsNumberArray(name));
		return found == m_colorMapEnd ? nullptr : &m_colorVector[found->second];
	}

	const NamedColor* GetColor(const unsigned short& ordinal) const{return ordinal < (unsigned short)m_colorVector.size() ? &m_colorVector[ordinal] : nullptr;}
	void SetColor(const unsigned short& ordinal, COLORREF color){if(ordinal < (unsigned short)m_colorVector.size())m_colorVector[ordinal].SetColor(color);}
	bool InitColor(COLORREF& color, const unsigned short& ordinal) const
	{
		if(ordinal < (unsigned short)m_colorVector.size())
		{
			const COLORREF c = m_colorVector[ordinal].GetColor();
			if(c != color)
			{
				color = c;
				return true;
			}
		}
		return false;
	}
	bool AddColor(const char* const& name, const COLORREF& color)
	{
		std::string nameString(name);
		FilterStringAsNumberArray nameStr(nameString);
		if(m_colorMap.find(nameStr) == m_colorMapEnd)
		{
			m_colorMap.insert(ColorMap::value_type(nameStr, (unsigned short)m_colorVector.size()));
			m_colorVector.push_back(NamedColor(nameString, color));
			m_colorMapBegin = m_colorMap.cbegin();
//			m_colorMapEnd = m_colorMap.end();
			m_colorVectorBegin = m_colorVector.begin();
//			m_colorVectorEnd = m_colorVector.end();
			m_colorVectorConstBegin = m_colorVector.cbegin();
			m_colorVectorConstEnd = m_colorVector.cend();
			return true;
		}
		return false;
	}
	bool SameColors(const Graphics& other) const
	{
		for(ColorConstIterator it = m_colorVectorConstBegin, itOther = other.m_colorVector.cbegin(), itOtherEnd = other.m_colorVector.cend(); it != m_colorVectorConstEnd && itOther != itOtherEnd; ++it, ++itOther)
		{
			if(it->GetColor() != itOther->GetColor())
			{
				return false;
			}
		}
		return true;
	}
	void Init(const GraphicsSetting& graphicsSetting);
	void SetDefaultColors()
	{
		for(ColorIterator it = m_colorVectorBegin; it != m_colorVectorConstEnd; ++it)
		{
			it->SetDefaultColor();
		}
	}
	bool hasFont() const{return m_hasFont;}
	const char* GetHorizontalSpacingName() const{return m_horizontalSpacingName;}
	const char* GetVerticalSpacingName() const{return m_verticalSpacingName;}
protected:
//	std::string m_name;
	unsigned char m_horizontalSpacing;
	unsigned char m_verticalSpacing;
	ColorMap m_colorMap;
	ColorMap::const_iterator m_colorMapBegin;
	ColorMap::const_iterator m_colorMapEnd;

	ColorVector m_colorVector;
	ColorConstIterator m_colorVectorConstBegin;
	ColorConstIterator m_colorVectorConstEnd;
	ColorIterator m_colorVectorBegin;
//	ColorIterator m_colorVectorEnd;

	bool m_hasFont;
	const char* m_horizontalSpacingName;
	const char* m_verticalSpacingName;
};

class UGUI_API ConfigBase
{
public:
	virtual ~ConfigBase(){}
	const std::string& GetOpenErrorMessage() const{return m_openErrorMessage;}
	const std::string& GetSaveErrorMessage() const{return m_saveErrorMessage;}
	const std::string& GetOpenFileName() const{return m_openFileName;}
	const std::string& GetSaveFileName() const{return m_saveFileName;}
	const std::string& GetValidFileName() const{return m_openFileName.empty() ? m_saveFileName : m_openFileName;}

	bool SetFileName(const char* fileName)
	{
		if(strcmp(m_openFileName.c_str(), fileName))
		{
			m_openFileName = m_saveFileName = fileName;
			return true;
		}
		return false;
	}

	bool Serialize(bool in, const char* fileName, const char* exeVersion, bool rememberFileName, unsigned int flags);
	const unsigned __int64& GetSavedVersion() const{return m_savedVersion;}
	const unsigned __int64& GetExtensionVersion() const{return m_extensionVersion;}

	const unsigned int& GetSavedDate() const{return m_savedDate;}
	const int& GetTotalScreenLeft() const{return m_totalScreenLeft;}
	const int& GetTotalScreenTop() const{return m_totalScreenTop;}
	bool isTotalScreenCornerValid() const{return m_totalScreenCornerValid;}

	bool isOptionVersion() const{return m_optionVersion;}
	bool isOpenFromFile() const{return m_openFromFile;}

	typedef std::map<std::string, Setting*> SettingMap;
	const SettingMap& GetSettingMap() const{return m_settingMap;}
	const Setting* FindSetting(const std::string& name) const
	{
		SettingMap::const_iterator found = m_settingMap.find(name);
		return found == m_settingMap.cend() ? nullptr : found->second;
	}
	Setting* FindSetting(const std::string& name)
	{
		SettingMap::iterator found = m_settingMap.find(name);
		return found == m_settingMap.end() ? nullptr : found->second;
	}
	ConfigBase& operator=(const ConfigBase& other);

	bool operator==(const ConfigBase& other) const;
	bool operator!=(const ConfigBase& other) const{return !operator==(other);}
	static void SkipValue(std::ifstream& istr);
	virtual const char* GetIniFileName() const{return "";}
	virtual const char* GetLogFileName() const{return "";}
	virtual const char* GetPosFileName() const{return "";}

	void Uninitialize(unsigned int flags);
	virtual bool isSettingNameToRead(unsigned int flags, const std::string& name) const{return true;}
	virtual ConfigBase* Clone() const = 0;
	virtual void Copy(const ConfigBase& other){operator=(other);}
	virtual unsigned char GetFlagCount() const{return 0;}
/*
	virtual unsigned __int64 GetSavedDateVersion() const{return 0;}
	virtual unsigned __int64 GetTotalScreenVersion() const{return 0;}
	virtual unsigned __int64 GetOptionVersion() const{return 0;}
*/
	unsigned __int64 GetSavedDateVersion() const{return U_GetVersion64(1, 0, 0, 135);}
	unsigned __int64 GetTotalScreenVersion() const{return U_GetVersion64(1, 0, 0, 147);}
	unsigned __int64 GetOptionVersion() const{return U_GetVersion64(1, 0, 1, 107);}
	unsigned __int64 GetSavedExtensionVersion() const{return U_GetVersion64(1, 0, 1, 114);}
	virtual void Update(){}

	BoolSetting m_closeDialogsOnEscape;
	BoolSetting m_confirmExit;
	BoolSetting m_saveLayoutOnExit;
	BoolSetting m_showTooltips;
	BoolSetting m_toolTipsInSettings;
	PairSetting<IntSetting, IntSetting> m_settingDlgPosition;
	PairSetting<IntSetting, IntSetting> m_fontDlgSize;
	PairSetting<IntSetting, IntSetting> m_colorDlgSize;
	BoolSetting m_settingDialogOnTop;
//	BoolSetting m_settingDialogToolTips;//same as m_toolTipsInSettings

	BoolSetting m_sortDllsCaseInsensitive;
	BoolSetting m_sortDllsByFileName;

	typedef MapSetting<StringSetting, GraphicsSetting, std::map<StringSetting, GraphicsSetting> > GraphicsMap;
	GraphicsMap m_graphics;

	typedef VectorSetting<StringSetting> StringVector;
	typedef VectorSetting<StringVector> StringVectorVector;

protected:
	ConfigBase();
	ConfigBase(const ConfigBase& other);
	void AddSettings();
	void AddSetting(const char* name, Setting& setting);
	Setting* RemoveSetting(const std::string& name);
	void ClearSettings()
	{
		m_settingMap.clear();
	}
	virtual void AdjustOldVersion(){}
	virtual bool PreReadSetting(Setting* setting, const std::string& name, const char* cursor){return true;}

#ifdef _DEBUG
	virtual void DebugConfig(const std::string& settingName, const Setting& currentSetting, const Setting& savedSetting) const{}
#endif

	SettingMap m_settingMap;
	std::string m_openFileName;
	std::string m_saveFileName;
	std::string m_openErrorMessage;
	std::string m_saveErrorMessage;
	unsigned __int64 m_savedVersion;
	unsigned __int64 m_extensionVersion;
	unsigned int m_savedDate;
	int m_totalScreenLeft;
	int m_totalScreenTop;
	bool m_totalScreenCornerValid;

	bool m_optionVersion;
	bool m_openFromFile;
};

class UGUI_API TakionFilter
{
public:
	virtual ~TakionFilter(){}
	virtual void Copy(const TakionFilter& other){}
	virtual void CopyFilterOfOtherKind(const TakionFilter& other, unsigned int doNotCopyFlags){}
	virtual bool isIntersectionEqual(const TakionFilter& other) const{return true;}// , unsigned int doNotCopyFlags) const{return true; }
	virtual void toString(std::string& str) const{}
	virtual void fromString(const char*& cursor, unsigned __int64 version, bool clone, unsigned int contentModifier){}
	virtual bool operator==(const TakionFilter& other) const{return true;}
	virtual unsigned char isPotentialFilterSame(const TakionFilter& filter) const{return 0;}//0 - same; 1 - to add; 2 - to remove; 3 - to add and remove
	virtual bool isFilterSame(const TakionFilter& filter) const{return true;}
	virtual bool isFiltering() const{return false;}
	virtual bool isEmpty() const{return true;}
	bool operator!=(const TakionFilter& other) const{return !operator==(other);}
	virtual void Reset(){}
	virtual void GetTimeFrameAsString(std::string& str, unsigned short msTimeFrame, bool timeFrameInMinutes) const{}
	virtual TakionFilter* CreateFilterCopy() const = 0;
protected:
	TakionFilter()
	{}
};

class StringOrderedSet;

#ifdef __cplusplus
extern "C"
{
#endif

typedef bool (WINAPI *FEmpty)();
//typedef void (WINAPI *FBool)(bool yes, unsigned short source);
typedef bool (WINAPI *FLong)(LONG count);

void WINAPI UGUI_Initialize(bool versionValid, const char* exepath, const char* product, const char* company, const char* copyright, HICON icon, HICON icon16x16, VisualBase* visual,
	HANDLE processDataEvent, FEmpty processData, FLong processMainThreadIdleTasks);//, FLong onIdle, FBool fInterrupt);
ConfigBase* WINAPI UGUI_InitializeConfig(ConfigBase* config, ConfigBase* defaultConfig);
void WINAPI UGUI_Terminate();
void WINAPI UGUI_IdleInterrupt(bool interrupt, unsigned short source);

const char* WINAPI UGUI_GetHeaderVersion();
unsigned __int64 WINAPI UGUI_GetHeaderVersionNum();
const char* WINAPI UGUI_GetFilePathAndName();
const char* WINAPI UGUI_GetPlatform();
const char* WINAPI UGUI_GetModuleVersionStr();
unsigned __int64 WINAPI UGUI_GetModuleVersionNum();
const char* WINAPI UGUI_GetFileDescription();
const char* WINAPI UGUI_GetProductName();
void WINAPI UGUI_GetDllBuildDescription(std::string& buildStr);

unsigned int WINAPI UGUI_GetKeyboardRepeatDelay();
unsigned int WINAPI UGUI_GetKeyboardRepeatInterval();
bool WINAPI UGUI_UpdateKeyboardRepeatValues();

int WINAPI UGUI_GetDoubleClickWidth();
int WINAPI UGUI_GetDoubleClickHeight();
void WINAPI UGUI_UpdateMouseDoubleClickRect();

void WINAPI UGUI_FillSolidRect(HDC hdc, const RECT& rect, COLORREF color);
int WINAPI UGUI_GetPaintIpAddressWidth(int tokenWidth);
void WINAPI UGUI_PaintIpOrVersion(HDC dc, const RECT& rect, unsigned int version);

void WINAPI UGUI_DrawMenuItem(HDC hdc,
	const RECT& rect,
	const char* str,
	COLORREF selectedColor,
	bool selected,
	COLORREF textColor,
	CFont* font,
	bool checkable,
	bool checked,
	bool radio,
	COLORREF bkColor = 0xFFFFFFFF,
	COLORREF highlightTextColor = 0xFFFFFFFF,
	const RECT* selectionRect = nullptr,
	int textWidth = -1,
	bool alignTextRight = false,
	int bitmapWidth = -1,//Menu Height
	int bitmapDeflate = 2,
	int prefixWidth = 0,
	const char* prefix = nullptr,
	UINT prefixAlignment = DT_CENTER,
	int indentation = 0);

void WINAPI UGUI_DrawTwoLineMenuItem(HDC hdc,
	const char* str2,
	const RECT& rect,
	const char* str,
	COLORREF selectedColor,
	bool selected,
	COLORREF textColor,
	CFont* font,
	bool checkable,
	bool checked,
	bool radio,
	COLORREF bkColor = 0xFFFFFFFF,
	COLORREF highlightTextColor = 0xFFFFFFFF,
	const RECT* selectionRect = nullptr,
	int textWidth = -1,
	bool alignTextRight = false,
	int bitmapWidth = -1,//Menu Height
	int bitmapDeflate = 2,
	int prefixWidth = 0,
	const char* prefix = nullptr,
	UINT prefixAlignment = DT_CENTER,
	int indentation = 0);

void WINAPI UGUI_DrawPinMenuItem(HDC hdc,
	const RECT& rect,
	const char* str,
	COLORREF selectedColor,
	bool selected,
	COLORREF textColor,
	CFont* font,
	bool pinned,
	COLORREF bkColor = 0xFFFFFFFF,
	COLORREF highlightTextColor = 0xFFFFFFFF,
	const RECT* selectionRect = nullptr,
	int pinWidth = -1,
	int bitmapDeflate = 2,
	int textWidth = -1,
	bool alignTextRight = false);

void WINAPI UGUI_DrawMenuItemWithIcon(HDC hdc,
	HICON icon,
	int iconWidth,
	int iconHeight,
	const RECT& rect,
	const char* str,
	COLORREF selectedColor,
	bool selected,
	COLORREF textColor,
	CFont* font,
	bool checkable,
	bool checked,
	bool radio,
	COLORREF bkColor = 0xFFFFFFFF,
	COLORREF highlightTextColor = 0xFFFFFFFF,
	const RECT* selectionRect = nullptr,
	int textWidth = -1,
	bool alignTextRight = false,
	int bitmapWidth = -1,
	int bitmapDeflate = 2,
	int indentation = 0);

void WINAPI UGUI_DrawOwnerDrawStringMenuItem(const DRAWITEMSTRUCT* lpDrawItemStruct,
	bool checkable,
	bool radio = false,
	COLORREF color = 0xFFFFFFFF,
	CFont* font = nullptr,
	const char* text = nullptr,
	COLORREF bkColor = 0xFFFFFFFF,
	COLORREF highlightTextColor = 0xFFFFFFFF,
	const RECT* selectionRect = nullptr,
	const bool* checked = nullptr,
	int bitmapWidth = -1,//menu height
	int bitmapDeflate = 2,
	int prefixWidth = 0,
	const char* prefix = nullptr,
	UINT prefixAlignment = DT_CENTER,
	int indentation = 0);

void WINAPI UGUI_DrawOwnerDrawStringAndNumberMenuItem(const DRAWITEMSTRUCT* lpDrawItemStruct,
	unsigned int number,
	bool commas,
	bool checkable,
	bool radio = false,
	COLORREF color = 0xFFFFFFFF,
	CFont* font = nullptr,
	const char* text = nullptr,
	COLORREF bkColor = 0xFFFFFFFF,
	COLORREF highlightTextColor = 0xFFFFFFFF,
	const RECT* selectionRect = nullptr,
	const bool* checked = nullptr,
	int bitmapWidth = -1,//menu height
	int bitmapDeflate = 2,
	int prefixWidth = 0,
	const char* prefix = nullptr,
	UINT prefixAlignment = DT_CENTER,
	int indentation = 0);

void WINAPI UGUI_DrawOwnerDrawTwoStringsMenuItem(const DRAWITEMSTRUCT* lpDrawItemStruct,
	const char* text2,
	bool checkable,
	bool radio = false,
	COLORREF color = 0xFFFFFFFF,
	CFont* font = nullptr,
	const char* text = nullptr,
	COLORREF bkColor = 0xFFFFFFFF,
	COLORREF highlightTextColor = 0xFFFFFFFF,
	const RECT* selectionRect = nullptr,
	const bool* checked = nullptr,
	int bitmapWidth = -1,//menu height
	int bitmapDeflate = 2,
	int prefixWidth = 0,
	const char* prefix = nullptr,
	UINT prefixAlignment = DT_CENTER,
	int indentation = 0);

void WINAPI UGUI_DrawOwnerDrawStringPinMenuItem(const DRAWITEMSTRUCT* lpDrawItemStruct,
	const bool* pinned = nullptr,
	int pinWidth = -1,//menu height
	int bitmapDeflate = 2,
	COLORREF color = 0xFFFFFFFF,
	CFont* font = nullptr,
	const char* text = nullptr,
	COLORREF bkColor = 0xFFFFFFFF,
	COLORREF highlightTextColor = 0xFFFFFFFF,
	const RECT* selectionRect = nullptr);

void WINAPI UGUI_DrawColorMenuItem(HDC hdc,
	const RECT& rect,
	const char* str,
	int textWidth,
	bool alignTextRight,
	COLORREF itemColor,
	COLORREF selectedColor,
	bool selected,
	COLORREF textColor,
	CFont* font,
	bool checkable,
	bool checked,
	bool radio,
	COLORREF bkColor = 0xFFFFFFFF,
	COLORREF highlightTextColor = 0xFFFFFFFF);

void WINAPI UGUI_DrawMultiColorMenuItem(HDC hdc,
	const RECT& rect,
	const char* str,
	int textWidth,
	bool alignTextRight,
	const COLORREF* itemColors,
	unsigned int colorCount,
	COLORREF selectedColor,
	bool selected,
	COLORREF textColor,
	CFont* font,
	bool checkable,
	bool checked,
	bool radio,
	COLORREF bkColor = 0xFFFFFFFF,
	COLORREF highlightTextColor = 0xFFFFFFFF);

void WINAPI UGUI_DrawVersionMenuItem(HDC hdc, const RECT& rect, unsigned __int64 version, bool selected, COLORREF textColor, CFont* font);

void WINAPI UGUI_DrawThermograph(HDC hdc,
	const RECT& rect,
	const RECT& rcPaint,
	bool left,
	const Thermograph& thermograph,
	unsigned short thermosecond,
	const COLORREF* colors,
	unsigned short colorCount);//COLORREF light, COLORREF dark);

void WINAPI UGUI_DrawTwoThermographs(HDC hdc,
	const RECT& rect,
	const RECT& rcPaint,
	const Thermograph& thermographRed,
	const Thermograph& thermographGreen,
	const COLORREF* colorsRed,
	const COLORREF* colorsGreen,
	unsigned short colorCount);//, COLORREF red, COLORREF grren, COLORREF dark);

void WINAPI UGUI_DrawInsideMarket(HDC hdc, const CRect& rect, int xHeight, bool bottomBase, const std::string& bid, const std::string& ask);

void WINAPI UGUI_FillThermoColors(COLORREF lightColor, COLORREF darkColor, COLORREF* colorCursor, unsigned short colorCount);

void WINAPI UGUI_GetFileSet(StringOrderedSet& fileSet, const char* extension);
//const char* WINAPI TGUI_LoadSoundEventFile(const char* fn, bool reload);
void WINAPI UGUI_GetWavFileSet(StringOrderedSet& fileSet);

const unsigned __int64& WINAPI UGUI_GetExeVersion();
const char* WINAPI UGUI_GetExeVersionStr();

void WINAPI UGUI_DrawRadio(HDC dc, const CRect& rect, unsigned char borderSize, COLORREF borderColor, bool highlight, COLORREF highlightColor, bool checked, COLORREF checkColor, COLORREF bkColor = 0xFFFFFFFF);
void WINAPI UGUI_DrawCheck(HDC dc, const CRect& rect, unsigned char borderSize, COLORREF borderColor, bool highlight, COLORREF highlightColor, bool checked, COLORREF checkColor, COLORREF bkColor = 0xFFFFFFFF);
void WINAPI UGUI_DrawTriangle(HDC dc, const CRect& rect, int minSize, COLORREF color, bool vertical, bool down);
void WINAPI UGUI_DrawRoof(HDC dc, const CRect& rect, COLORREF color, bool vertical, bool down, int thick);
void WINAPI UGUI_DrawHalfTriangle(HDC dc, int xBase, int yBase, int size, COLORREF color, bool right, bool down);

void WINAPI UGUI_DrawLeftTopHalfRectBorder(HDC dc, const RECT& rcPaint, const CRect& borderRect, COLORREF borderColor, int borderWidth);
void WINAPI UGUI_DrawRightBottomHalfRectBorder(HDC dc, const RECT& rcPaint, const CRect& borderRect, COLORREF borderColor, int borderWidth);
void WINAPI UGUI_DrawRectBorder(HDC dc, const RECT& rcPaint, const CRect& rect, COLORREF lightColor, COLORREF darkColor, int borderWidth, bool recessed = false);

void WINAPI UGUI_DrawLeftTopHalfRectBorderWithInsertion(HDC dc, const RECT& rcPaint, const CRect& borderRect, int insertionLeft, int insertionRight, COLORREF borderColor, int borderWidth);
void WINAPI UGUI_DrawRectBorderWithInsertion(HDC dc, const RECT& rcPaint, const CRect& borderRect, int insertionLeft, int insertionRight, COLORREF borderColor, int borderWidth);

void WINAPI UGUI_DrawPlusMinusBox(HDC dc, const RECT& rcPaint, const CRect& rect, int thick, int shrink, bool plus, bool bottomBased, COLORREF color, COLORREF bkColor = 0xFFFFFFFF);
COLORREF WINAPI UGUI_CalculateLightColor(COLORREF color, unsigned int percentDiff);
COLORREF WINAPI UGUI_CalculateDarkColor(COLORREF color, unsigned int percentDiff);

void WINAPI UGUI_DrawPin(HDC dc, const CRect& rect, COLORREF color);
void WINAPI UGUI_DrawUnpin(HDC dc, const CRect& rect, COLORREF color);

void WINAPI UGUI_DrawLetterT(HDC dc, const CRect& rect, COLORREF color);
void WINAPI UGUI_DrawTrueType(HDC dc, const CRect& rect, COLORREF color1, COLORREF color2);

bool WINAPI UGUI_IsRectInside(const RECT& rectOutside, const RECT& rectInside);

void WINAPI UGUI_DrawTransparentBitmap(HDC dc,
	const CBitmap* bitmap,
	int xStart,
	int yStart,
	int wWidth, 
	int wHeight,
	int xSource = 0,
	int ySource = 0,
	CBitmap* mask = nullptr);

const UINT& WINAPI UGUI_GetDragEnterMessage();//WM_DD_DRAGENTER; // start dragging
const UINT& WINAPI UGUI_GetDragOverMessage();//WM_DD_DRAGOVER;  // dragging
const UINT& WINAPI UGUI_GetDragLeaveMessage();//WM_DD_DRAGLEAVE;  // dragging
const UINT& WINAPI UGUI_GetDragDropMessage();//WM_DD_DRAGDROP;  // drop
const UINT& WINAPI UGUI_GetDragAbortMessage();//WM_DD_DRAGABORT; // abort dragging

void WINAPI UGUI_GetAsciiKeyAsString(unsigned char ascii, std::string& result);
unsigned char WINAPI UGUI_GetStringAsAsciiKey(const char* str);
unsigned char WINAPI UGUI_GetKeyModifier();
void WINAPI UGUI_GetKeyAsString(unsigned char ascii, unsigned char modifier, std::string& result);
unsigned short WINAPI UGUI_GetStringAsKey(const char* str);

unsigned char WINAPI UGUI_CopyClipboardToString(std::string& str, HWND owner);
unsigned int WINAPI UGUI_CopyClipboardToStringList(std::list<std::string>& stringList, HWND owner);
unsigned int WINAPI UGUI_CopyClipboardToStringMap(std::map<std::string, std::string>& stringMap, HWND owner, char delimiter, unsigned int* duplicateCount = nullptr);
unsigned char WINAPI UGUI_CopyStringToClipboard(const std::string& info, HWND owner);

ConfigBase* WINAPI UGUI_GetSavedConfig();

INT_PTR WINAPI UGUI_MessageBox(CWnd* parent, const char* text, const char* caption, unsigned int type, COLORREF bkColor = RGB(0, 0, 128), COLORREF textColor = RGB(255, 255, 255), COLORREF captionColor = 0xFFFFFFFF);

void WINAPI UGUI_SetLogFile(void* logFile);
void* WINAPI UGUI_GetLogFile();

#ifdef __cplusplus
} //extern "C"
#endif

class UGUI_API RectArea
{
public:
	virtual ~RectArea(){}
	const CRect& GetRect() const{return m_rectArea;}
	bool SetRect(const CRect& rect)
	{
		if(m_rectArea != rect)
		{
			if(m_wnd && m_wnd->m_hWnd)
			{
				m_wnd->InvalidateRect(&m_rectArea, FALSE);
				m_wnd->InvalidateRect(&rect, FALSE);
			}
			m_rectArea = rect;
			RectChanged();
			return true;
		}
		return false;
	}
	void Invalidate() const{if(m_wnd && m_wnd->m_hWnd)InvalidateRect(m_wnd->m_hWnd, &m_rectArea, FALSE);}
	virtual void Draw(HDC hdc, const RECT& rcPaint) const{}
	CWnd* GetWnd(){return m_wnd;}
	const CWnd* GetWnd() const{return m_wnd;}
	void SetWnd(CWnd* wnd){m_wnd = wnd;}
	void SetVisible(bool visible);//{m_visible = visible;}
	bool isVisible() const{return m_visible;}
protected:
	RectArea(CWnd* wnd):
		m_wnd(wnd),
		m_rectArea(0, 0, 0, 0),
		m_visible(true)
	{}
	RectArea(CWnd* wnd, const CRect& rect):
		m_wnd(wnd),
		m_rectArea(rect),
		m_visible(true)
	{}
	virtual void RectChanged(){}
	CWnd* m_wnd;
	CRect m_rectArea;
	bool m_visible;
};

class UGUI_API TextAreaBase : public RectArea
{
public:
	const COLORREF& GetFgColor() const{return m_textColor;}
	const std::string& GetText() const{return m_text;}
	const COLORREF& GetBkColor() const{return m_bkColor;}

	void SetBkColor(const COLORREF& color)
	{
		if(color != m_bkColor)
		{
			m_bkColor = color;
			BkColorSet();
		}
	}
	void InvalidateText() const{if(m_wnd && m_wnd->m_hWnd)InvalidateRect(m_wnd->m_hWnd, &m_drawRect, FALSE);}
	void SetFgColor(const COLORREF& color)
	{
		if(color != m_textColor)
		{
			m_textColor = color;
			InvalidateText();
		}
	}
	bool SetTextInRect(const char* text)
	{
		if(!text)text = "";
		if(strcmp(m_text.c_str(), text))
		{
			m_text = text;
//			UpdateTextRects();
			InvalidateText();
			return true;
		}
		return false;
	}
protected:
	TextAreaBase(CWnd* wnd = nullptr, COLORREF textColor = 0xFFFFFFFF, COLORREF bkColor = RGB(255, 255, 255), CRect* rect = nullptr, CRect* drawRect = nullptr, const char* text = nullptr):
		RectArea(wnd, rect ? *rect : CRect(0, 0, 0, 0)),
		m_textColor(textColor),
		m_bkColor(bkColor),
		m_text(text ? text : ""),
		m_drawRect(drawRect ? *drawRect : m_rectArea)
	{}
	virtual void BkColorSet(){}
//	virtual void UpdateTextRects(){}
	COLORREF m_textColor;
	COLORREF m_bkColor;
	std::string m_text;
	CRect m_drawRect;
};

class UGUI_API CustomGroupBox : public TextAreaBase
{
public:
	CustomGroupBox(CWnd* wnd = nullptr, COLORREF textColor = 0xFFFFFFFF, COLORREF bkColor = RGB(255, 255, 255), CRect* rect = nullptr, const char* text = nullptr, int textLeftOffset = 20, int borderWidth = 1, unsigned int borderColorPercentDiff = 36):
		TextAreaBase(wnd, textColor, bkColor, rect, nullptr, text),
		m_borderColorPercentDiff(borderColorPercentDiff),
		m_textLeftOffset(textLeftOffset),
		m_borderWidth(borderWidth),
		m_frameRect(m_rectArea),
		m_textWidth(0)
	{
		m_drawRect.left = m_rectArea.left + m_textLeftOffset;
		m_drawRect.top = m_rectArea.top;
		CalculateColors();
	}
	virtual void Draw(HDC hdc, const RECT& rcPaint) const override;
//	void MeasureText(HDC hdc);
	void UpdateTextRects(HDC hdc);
	void SetTotalRect(const CRect& rect, HDC hdc = nullptr)
	{
		if(RectArea::SetRect(rect))
		{
//			InitDrawRect(hdc);
			UpdateTextRects(hdc);
		}
	}
	virtual void Adjust(){}
protected:
	void CalculateColors()
	{
		m_lightColor = UGUI_CalculateLightColor(m_bkColor, m_borderColorPercentDiff);
		m_darkColor = UGUI_CalculateDarkColor(m_bkColor, m_borderColorPercentDiff);
	}
	virtual void BkColorSet() override
	{
		CalculateColors();
		Invalidate();
	}
	virtual void RectChanged() override
	{
		const int height = m_drawRect.Height();
		m_drawRect.left = m_rectArea.left + m_textLeftOffset;
		m_drawRect.top = m_rectArea.top;
		m_drawRect.right = m_drawRect.left + m_textWidth;
		if(m_drawRect.right >= m_rectArea.right)m_drawRect.right = m_rectArea.right - 1;
		m_drawRect.bottom = m_drawRect.top + height;
		m_frameRect = m_rectArea;
		m_frameRect.top += height / 2;
	}
	COLORREF m_lightColor;
	COLORREF m_darkColor;
	unsigned int m_borderColorPercentDiff;
	int m_textLeftOffset;
	int m_borderWidth;
	int m_textWidth;
	CRect m_frameRect;
};

class UGUI_API CustomGroupBoxAdjustable : public CustomGroupBox
{
public:
	CustomGroupBoxAdjustable(
		int leftMargin,
		int topMargin,
		int rightMargin,
		int bottomMargin,

		CWnd* leftWnd = nullptr,
		CWnd* topWnd = nullptr,
		CWnd* rightWnd = nullptr,
		CWnd* bottomWnd = nullptr,

		CWnd* wnd = nullptr,
		COLORREF textColor = 0xFFFFFFFF,
		COLORREF bkColor = RGB(255, 255, 255),
		CRect* rect = nullptr,
		const char* text = nullptr,
		int textLeftOffset = 20,
		int borderWidth = 1,
		unsigned int borderColorPercentDiff = 36):

		CustomGroupBox(wnd, textColor, bkColor, rect, text, textLeftOffset, borderWidth, borderColorPercentDiff),

		m_leftMargin(leftMargin),
		m_topMargin(topMargin),
		m_rightMargin(rightMargin),
		m_bottomMargin(bottomMargin),

		m_leftWnd(leftWnd),
		m_topWnd(topWnd),
		m_rightWnd(rightWnd),
		m_bottomWnd(bottomWnd)
	{
	}
	void SetWindows(CWnd* leftWnd,
		CWnd* topWnd,
		CWnd* rightWnd,
		CWnd* bottomWnd)
	{
		m_leftWnd = leftWnd;
		m_topWnd = topWnd;
		m_rightWnd = rightWnd;
		m_bottomWnd = bottomWnd;
	}
	void SetLeftWindow(CWnd* wnd){m_leftWnd = wnd;}
	void SetTopWindow(CWnd* wnd){m_topWnd = wnd;}
	void SetRightWindow(CWnd* wnd){m_rightWnd = wnd;}
	void SetBottomWindow(CWnd* wnd){m_bottomWnd = wnd;}
	virtual void Adjust() override;
protected:
	int m_leftMargin;
	int m_topMargin;
	int m_rightMargin;
	int m_bottomMargin;

	CWnd* m_leftWnd;
	CWnd* m_topWnd;
	CWnd* m_rightWnd;
	CWnd* m_bottomWnd;
};

class UGUI_API TextArea : public TextAreaBase
{
public:
	virtual void Draw(HDC hdc, const RECT& rcPaint) const override;
	const UINT& GetHorizontalAlignment() const{return m_horizontalAlignment;}
	const COLORREF& GetBorderColor() const{return m_borderColor;}
	CFont* GetFont() const{return m_font;}
/*
	const COLORREF& GetFgColor() const{return m_textColor;}
	const std::string& GetText() const{return m_text;}
	void InvalidateText() const{if(m_wnd && m_wnd->m_hWnd)InvalidateRect(m_wnd->m_hWnd, &m_drawRect, FALSE);}
	void SetFgColor(const COLORREF& color)
	{
		if(color != m_textColor)
		{
			m_textColor = color;
			InvalidateText();
		}
	}
	void SetBkColor(const COLORREF& color)
	{
		if(color != m_bkColor)
		{
			m_bkColor = color;
			BkColorSet();
		}
	}
*/
	void SetBorderColor(const COLORREF& color)
	{
		if(color != m_borderColor)
		{
			m_borderColor = color;
			if(m_drawBorder)Invalidate();
		}
	}

	void SetHorizontalAlignment(UINT alignment, HDC hdc = nullptr);
	void SetFont(CFont* font, HDC hdc = nullptr);
	void SetRect(const CRect& rect, HDC hdc = nullptr)
	{
		if(RectArea::SetRect(rect))
		{
			InitDrawRect(hdc);
			m_drawRect.right = rect.right;
			m_drawRect.bottom = rect.bottom;
		}
	}
	virtual void InitDrawRect(HDC hdc = nullptr, CFont* font = nullptr);

	void SetDrawBorder(const bool drawBorder)
	{
		if(drawBorder != m_drawBorder)
		{
			m_drawBorder = drawBorder;
			Invalidate();
		}
	}

	void ToggleDrawBorder(){SetDrawBorder(!m_drawBorder);}
	const bool& isDrawBorder() const{return m_drawBorder;}

	const int& GetTextWidth() const{return m_textWidth;}
	const int& GetTextHeight() const{return m_textHeight;}

protected:
	TextArea(CWnd* wnd, UINT horizontalAlignment = DT_LEFT, COLORREF textColor = 0xFFFFFFFF, COLORREF bkColor = 0xFFFFFFFF, CFont* font = nullptr, CRect* rect = nullptr, const char* text = nullptr, bool drawRectSame = false):
		TextAreaBase(wnd, textColor, bkColor, rect, nullptr, text),
//		RectArea(wnd, rect ? *rect : CRect(0, 0, 0, 0)),
		m_horizontalAlignment(horizontalAlignment),
//		m_textColor(textColor),
		m_borderColor(0xFFFFFFFF),
		m_font(font),
//		m_text(text ? text : ""),
//		m_drawRect(m_rectArea),
		m_textWidth(m_rectArea.Width()),
		m_textHeight(m_rectArea.Height()),
		m_drawRectSame(drawRectSame),
		m_drawBorder(false)
	{}
	virtual void BkColorSet() override
	{
		if(m_drawBorder)InvalidateText();
		else Invalidate();
	}

	virtual void RectChanged() override
	{
//		const int height = m_drawRect.Height();
//		const int width = m_drawRect.Width();

		const int maxHeight = m_rectArea.Height();

		m_drawRect.top = m_rectArea.top;
		m_drawRect.bottom = m_rectArea.bottom;

		if(m_textHeight < maxHeight)
		{
			m_drawRect.top += (maxHeight - m_textHeight) / 2;
		}
		const int maxWidth = m_rectArea.Width();
		if(m_horizontalAlignment != DT_LEFT)
		{
			if(m_textWidth < maxWidth)
			{
				m_drawRect.right = m_rectArea.left;
				if(m_horizontalAlignment == DT_RIGHT)
				{
					m_drawRect.right = m_rectArea.right;
					m_drawRect.left = m_rectArea.right - m_textWidth;
				}
				else
				{
					m_drawRect.left = m_rectArea.left + (maxWidth - m_textWidth) / 2;
					m_drawRect.right = m_drawRect.left + m_textWidth;
				}
			}
			else
			{
				m_drawRect.left = m_rectArea.left;
				m_drawRect.right = m_rectArea.right;
			}
		}
		else
		{
			m_drawRect.left = m_rectArea.left;
			if(m_textWidth < maxWidth)
			{
				m_drawRect.right = m_drawRect.left + m_textWidth;
			}
			else
			{
				m_drawRect.right = m_rectArea.right;
			}
		}
	}
	bool SetText(const char* text, HDC hdc = nullptr);
	UINT m_horizontalAlignment;
//	COLORREF m_textColor;
//	COLORREF m_bkColor;
	COLORREF m_borderColor;
	CFont* m_font;
//	std::string m_text;

//	CRect m_drawRect;
	int m_textWidth;
	int m_textHeight;
	bool m_drawRectSame;
	bool m_drawBorder;
};

class UGUI_API StringArea : public TextArea
{
public:
	StringArea(CWnd* wnd, UINT horizontalAlignment = DT_LEFT, COLORREF textColor = 0xFFFFFFFF, COLORREF bkColor = 0xFFFFFFFF, CFont* font = nullptr, CRect* rect = nullptr, const char* text = nullptr, bool drawRectSame = false):
		TextArea(wnd, horizontalAlignment, textColor, bkColor, font, rect, text, drawRectSame)
	{}
	void SetString(const char* text, HDC hdc = nullptr){SetText(text, hdc);}
};

template<class T>//, class ST = T>
class ValueArea : public TextArea
{
public:
	typedef T ValueType;

	virtual void AppendValueToText(){}
	virtual void toString()
	{
//		char num[33];
		m_text.clear();
		if(isValuePositive())
		{
			if(m_showPlus)m_text += '+';
		}
		else if(isZero())
		{
			if(m_showMinusForZero)m_text += '-';
		}
		if(m_prefix)m_text += m_prefix;
		AppendValueToText();
//		m_text += U_IntToStrWithCommas(m_value, num, sizeof(num));
		if(m_suffix)m_text += m_suffix;
	}

//	virtual bool isNegative(const ST& value) = 0;
	const T& GetValue() const{return m_value;}
	const T& GetMinValue() const{return m_minValue;}
	const T& GetMaxValue() const{return m_maxValue;}

	bool SetMinMaxValue(const T& minValue, const T& maxValue, HDC hdc = nullptr)
	{
		bool ret = false;
		if(minValue <= maxValue)
		{
			if(minValue != m_minValue)
			{
				m_minValue = minValue;
				ret = true;
			}
			if(maxValue != m_maxValue)
			{
				m_maxValue = maxValue;
				ret = true;
			}
			if(m_value < m_minValue)
			{
				DoSetValue(m_minValue, hdc);
			}
			else if(m_value > m_maxValue)
			{
				DoSetValue(m_maxValue, hdc);
			}
		}
		return ret;
	}

	bool SetMinValue(const T& minValue, HDC hdc = nullptr)
	{
		return SetMinMaxValue(minValue, m_maxValue, hdc);
	}
	bool SetMaxValue(const T& maxValue, HDC hdc = nullptr)
	{
		return SetMinMaxValue(m_minValue, maxValue, hdc);
	}
	void ReInitValue(HDC hdc = nullptr)
	{
		toString();
		InitDrawRect(hdc);
	}
	bool SetValue(const T& value, HDC hdc = nullptr)
	{
		return DoSetValue(value < m_minValue ? m_minValue : value > m_maxValue ? m_maxValue : value, hdc);
	}
	virtual bool isValuePositive() const{return !isZero();}
	bool isZero() const{return isValueZero(m_value);}
	bool isValueZero(const T& value) const{return !value;}
	virtual bool isDeltaBigEnough(const T& delta) const{return !isValueZero(delta);}
	bool Increment(const T& value, const bool& round, HDC hdc = nullptr)
	{
		return isDeltaBigEnough(value) && DoSetIncrementedValue(m_value + value, value, false, round, hdc);
	}
	bool Decrement(const T& value, const bool& round, HDC hdc = nullptr)
	{
		if(isDeltaBigEnough(value))
		{
//			typedef std::make_unsigned<ValueType>::type UnsignedType;		
//			return std::is_same<std::make_unsigned<ValueType>::type, ValueType>::value ?
			return std::is_unsigned<ValueType>::value ?
				!isZero() && DoSetIncrementedValue(m_value > value ? m_value - value : m_value - m_value, value, true, round, hdc):
				DoSetIncrementedValue(m_value - value, value, true, round, hdc);
		}
		return false;
	}
	virtual T RoundValue(const T& value, const T& denominator, bool up) const{return value;}
//	void SetRoundWhenIncrementing(const bool& yes){m_roundWhenIncrementing = yes;}
	void SetOverincrement(const bool& yes){m_overIncrement = yes;}
	void SetOverdecrement(const bool yes){m_overDecrement = yes;}
	bool SetShowPlus(const bool& show, HDC hdc = nullptr)
	{
		if(show != m_showPlus)
		{
			m_showPlus = show;
			if(hdc)
			{
				ReInitValue(hdc);
			}
			return true;
		}
		return false;
	}
	const bool& isShowPlus() const{return m_showPlus;}
	bool SetShowMinusForZero(const bool& show, HDC hdc = nullptr)
	{
		if(show != m_showMinusForZero)
		{
			m_showMinusForZero = show;
			if(hdc)
			{
				ReInitValue(hdc);
			}
			return true;
		}
		return false;
	}
	const bool& isShowMinusForZero() const{return m_showMinusForZero;}
	bool SetPrefix(const char& prefix, HDC hdc = nullptr)
	{
		if(prefix != m_prefix)
		{
			m_prefix = prefix;
			if(hdc)
			{
				ReInitValue(hdc);
			}
			return true;
		}
		return false;
	}
	const char& GetPrefix() const{return m_prefix;}
	bool SetSuffix(const char& suffix, HDC hdc = nullptr)
	{
		if(suffix != m_suffix)
		{
			m_suffix = suffix;
			if(hdc)
			{
				ReInitValue(hdc);
			}
			return true;
		}
		return false;
	}
	const char& GetSuffix() const{return m_suffix;}
protected:
	ValueArea(CWnd* wnd, const T& minValue, const T& maxValue, const T& value, const char* text, UINT horizontalAlignment = DT_LEFT, COLORREF textColor = 0xFFFFFFFF, COLORREF bkColor = 0xFFFFFFFF, CFont* font = nullptr, CRect* rect = nullptr, bool drawRectSame = false):
		TextArea(wnd, horizontalAlignment, textColor, bkColor, font, rect, text, drawRectSame),
		m_minValue(minValue),
		m_maxValue(maxValue),
		m_value(value),
//		m_roundWhenIncrementing(false),
		m_overIncrement(true),
		m_overDecrement(true),
		m_showPlus(false),
		m_showMinusForZero(false),
		m_prefix('\0'),
		m_suffix('\0')
	{}
	bool DoSetIncrementedValue(T v, const T& value, const bool& decremented, const bool& round, HDC hdc)
	{
		if(round)//m_roundWhenIncrementing)
		{
			T roundedValue = RoundValue(v, value, decremented);
			if(decremented)
			{
				if(roundedValue >= m_value)
				{
					if(m_overDecrement)
					{
						if(roundedValue > m_value)
						{
							return DoSetValue(m_minValue, hdc);
						}
					}
					return false;
				}
			}
			else
			{
				if(roundedValue <= m_value)
				{
					if(m_overIncrement)
					{
						if(roundedValue < m_value)
						{
							return DoSetValue(m_maxValue, hdc);
						}
					}
					return false;
				}
			}
			v = roundedValue;
		}
		if(v > m_value)
		{
			if(v <= m_maxValue)
			{
				return DoSetValue(v, hdc);
			}
			else if(m_overIncrement)
			{
				return DoSetValue(m_maxValue, hdc);
			}
		}
		else
		{
			if(v >= m_minValue)
			{
				return DoSetValue(v, hdc);
			}
			else if(m_overDecrement)
			{
				return DoSetValue(m_minValue, hdc);
			}
		}
		return false;
	}
	bool DoSetValue(const T& v, HDC hdc = nullptr)
	{
		if(m_value != v)
		{
			m_value = v;
			ReInitValue(hdc);
			return true;
		}
		return false;
	}
	T m_minValue;
	T m_maxValue;
	T m_value;
//	bool m_roundWhenIncrementing;
	bool m_overIncrement;
	bool m_overDecrement;
	bool m_showPlus;
	bool m_showMinusForZero;
	char m_prefix;
	char m_suffix;
};

template<class T>
class NumericArea : public ValueArea<T>
{
public:
	virtual T RoundValue(const T& value, const T& denominator, bool up) const
	{
		if(denominator)
		{
			T ret = value / denominator * denominator;
			if(up != (ret < 0) && ret != value && (ret != 0 || (value > 0) == (ret + denominator > 0)))
			{
				ret += denominator;
			}
			return ret;
		}
		return value;
	}
	virtual bool isValuePositive() const{return m_value > 0;}
protected:
	NumericArea(CWnd* wnd, const T& minValue, const T& maxValue, const T& value, const char* text, UINT horizontalAlignment = DT_RIGHT, COLORREF textColor = 0xFFFFFFFF, COLORREF bkColor = 0xFFFFFFFF, CFont* font = nullptr, CRect* rect = nullptr, bool drawRectSame = false):
		ValueArea(wnd, minValue, maxValue, value, text, horizontalAlignment, textColor, bkColor, font, rect, drawRectSame)
	{}
};

class UGUI_API IntArea : public NumericArea<int>
{
public:
	IntArea(CWnd* wnd, const int& minValue, const int& maxValue, const int& value, const char* text, UINT horizontalAlignment = DT_RIGHT, COLORREF textColor = 0xFFFFFFFF, COLORREF bkColor = 0xFFFFFFFF, CFont* font = nullptr, CRect* rect = nullptr, bool drawRectSame = false):
		NumericArea(wnd, minValue, maxValue, value, text, horizontalAlignment, textColor, bkColor, font, rect, drawRectSame)
	{}
//	virtual void toString();
	virtual void AppendValueToText();
};

class UGUI_API UIntArea : public NumericArea<unsigned int>//IntArea
{
public:
	UIntArea(CWnd* wnd, const int& minValue, const int& maxValue, const int& value, const char* text, UINT horizontalAlignment = DT_RIGHT, COLORREF textColor = 0xFFFFFFFF, COLORREF bkColor = 0xFFFFFFFF, CFont* font = nullptr, CRect* rect = nullptr, bool drawRectSame = false):
		NumericArea(wnd, minValue, maxValue, value, text, horizontalAlignment, textColor, bkColor, font, rect, drawRectSame)
	{}
//	virtual void toString();
	virtual void AppendValueToText();
};

class UGUI_API TimeTokenArea : public UIntArea
{
public:
	TimeTokenArea(CWnd* wnd, const int& minValue, const int& maxValue, const int& value, const char* text, UINT horizontalAlignment = DT_RIGHT, COLORREF textColor = 0xFFFFFFFF, COLORREF bkColor = 0xFFFFFFFF, CFont* font = nullptr, CRect* rect = nullptr, bool drawRectSame = false):
		UIntArea(wnd, minValue, maxValue, value, text, horizontalAlignment, textColor, bkColor, font, rect, drawRectSame)
	{}
	virtual void AppendValueToText();
};

class UGUI_API MillisecondArea : public UIntArea
{
public:
	MillisecondArea(CWnd* wnd, const int& minValue, const int& maxValue, const int& value, const char* text, UINT horizontalAlignment = DT_RIGHT, COLORREF textColor = 0xFFFFFFFF, COLORREF bkColor = 0xFFFFFFFF, CFont* font = nullptr, CRect* rect = nullptr, bool drawRectSame = false):
		UIntArea(wnd, minValue, maxValue, value, text, horizontalAlignment, textColor, bkColor, font, rect, drawRectSame)
	{}
	virtual void AppendValueToText();
};

template<class T>
class MonetaryArea : public ValueArea<T>
{
public:
	typedef typename T::DollarType DollarType;
	typedef typename T::FractionType FractionType;
	virtual bool isValuePositive() const{return m_value.isPositive();}
	virtual T RoundValue(const T& value, const T& denominator, bool up) const
	{
		if(value.isZero())
		{
			return value;
		}
		const __int64 multiplier = m_multiplier;//1000;
		__int64 val = (__int64)value.GetDollars() * multiplier + (__int64)value.GetDollarFraction() / m_divider;
		const __int64 den = (__int64)denominator.GetDollars() * multiplier + (__int64)denominator.GetDollarFraction() / m_divider;
		if(den > 1 || den < -1)
		{
			val /= den;
			val *= den;
		}
		const __int64 dollar = val / multiplier;
		T ret((DollarType)dollar, (FractionType)((val - dollar * multiplier) * m_divider));
//		if(up != ret.isNegative() && ret != value && (!ret.isZero() || value.isPositive() == (up ? (ret + denominator).isPositive() : (ret - denominator).isPositive()))
		if(up != value.isNegative() && ret != value && (!ret.isZero() || value.isPositive() == (up ? (ret + denominator).isPositive() : (ret - denominator).isPositive())))
		{
			if(up)
			{
				ret += denominator;
			}
			else
			{
				ret -= denominator;
			}
		}
		return ret;
	}
	const unsigned char& GetDecDigits() const{return m_decDigits;}
	void SetDecDigits(unsigned char decDigits, HDC hdc = nullptr)
	{
		if(m_decDigits != decDigits)
		{
			m_multiplier = 1;
			for(unsigned char i = 0; i < decDigits; ++i)
			{
				m_multiplier *= 10;
				if(m_multiplier >= T::divider)
				{
					m_multiplier = T::divider;
					decDigits = i;
					break;
				}
			}

			if(m_decDigits != decDigits)
			{
				bool lessGranularity = m_decDigits > decDigits;
				m_decDigits = decDigits;

				m_divider = T::divider / (FractionType)m_multiplier;
				m_minIncrement.SetValue(0, m_divider);
				if(m_wnd && m_wnd->m_hWnd)
				{
					InvalidateRect(m_wnd->m_hWnd, &m_rectArea, FALSE);
				}
				if(lessGranularity)
				{
					m_value = RoundValue(m_value, m_minIncrement, m_value.isNegative());
				}
				ReInitValue(hdc);
				if(m_wnd && m_wnd->m_hWnd)
				{
					InvalidateRect(m_wnd->m_hWnd, &m_rectArea, FALSE);
				}
			}
		}
	}
	const bool& isCommas() const{return m_commas;}
	void SetCommas(const bool& commas, HDC hdc = nullptr)
	{
		if(commas != m_commas)
		{
			m_commas = commas;
			InitDrawRect(hdc);
		}
	}
	void SetFractionFont(CFont* const& font, HDC hdc = nullptr)
	{
		if(font != m_fractionFont)
		{
			m_fractionFont = font;
			InitDrawRect(hdc);
		}
	}
	virtual bool isDeltaBigEnough(const T& delta) const{return delta >= m_minIncrement;}
protected:
	MonetaryArea(CWnd* wnd, unsigned char decDigits, bool commas, const T& minValue, const T& maxValue, const T& value, const char* text, UINT horizontalAlignment = DT_RIGHT, COLORREF textColor = 0xFFFFFFFF, COLORREF bkColor = 0xFFFFFFFF, CFont* font = nullptr, CRect* rect = nullptr, bool drawRectSame = false):
		ValueArea(wnd, minValue, maxValue, value, text, horizontalAlignment, textColor, bkColor, font, rect, drawRectSame),
		m_decDigits(decDigits > 9 ? 9 : decDigits),
		m_multiplier(1),
		m_divider(1),
		m_drawFractionRect(0, 0, 0, 0),
		m_fractionFont(nullptr),
		m_commas(commas)
	{
		for(unsigned char i = 0; i < m_decDigits; ++i)
		{
			m_multiplier *= 10;
			if(m_multiplier >= T::divider)
			{
				m_multiplier = T::divider;
				m_decDigits = i;
				break;
			}
		}
		m_divider = T::divider / (FractionType)m_multiplier;
		m_minIncrement.SetValue(0, m_divider);
	}
	unsigned char m_decDigits;
	DollarType m_multiplier;
	FractionType m_divider;
	T m_minIncrement;
	CRect m_drawFractionRect;
	CFont* m_fractionFont;
	bool m_commas;
	std::string m_wholeText;
	std::string m_fractionText;
};

class UGUI_API SignedPriceArea : public MonetaryArea<SignedPrice>
{
public:
	SignedPriceArea(CWnd* wnd, unsigned char decDigits, bool commas, const SignedPrice& minValue, const SignedPrice& maxValue, const SignedPrice& value, const char* text, UINT horizontalAlignment = DT_RIGHT, COLORREF textColor = 0xFFFFFFFF, COLORREF bkColor = 0xFFFFFFFF, CFont* font = nullptr, CRect* rect = nullptr, bool drawRectSame = false):
		MonetaryArea(wnd, decDigits, commas, minValue, maxValue, value, text, horizontalAlignment, textColor, bkColor, font, rect, drawRectSame)
	{}
	virtual void toString();
//	virtual void AppendValueToText(){}
	virtual void InitDrawRect(HDC hdc = nullptr, CFont* font = nullptr);
	virtual void Draw(HDC hdc, const RECT& rcPaint) const override;
};

class UGUI_API MoneyArea : public MonetaryArea<Money>
{
public:
	MoneyArea(CWnd* wnd, unsigned char decDigits, bool commas, const Money& minValue, const Money& maxValue, const Money& value, const char* text, UINT horizontalAlignment = DT_RIGHT, COLORREF textColor = 0xFFFFFFFF, COLORREF bkColor = 0xFFFFFFFF, CFont* font = nullptr, CRect* rect = nullptr, bool drawRectSame = false):
		MonetaryArea(wnd, decDigits, commas, minValue, maxValue, value, text, horizontalAlignment, textColor, bkColor, font, rect, drawRectSame)
	{}
	virtual void toString();
//	virtual void AppendValueToText();
};

class UGUI_API MouseArea : public RectArea
{
public:
//	virtual ~MouseArea(){}
//	const CRect& GetRect() const{return m_rectArea;}
	const CRect& GetRectCursor() const{return m_rectCursor;}
	bool isPointInside(const CPoint& point) const{return m_rectCursor.PtInRect(point) == TRUE;}
	const bool& isMouseInside() const{return m_mouseInside;}
	bool UpdateMouseInside(const CPoint& point);
	bool SetMouseInside(bool inside);
	virtual HCURSOR GetCursor() const{return m_cursor;}
protected:
	MouseArea(CWnd* wnd, HCURSOR cursor):
		RectArea(wnd),
//		m_wnd(wnd),
		m_cursor(cursor),
//		m_rectArea(0, 0, 0, 0),
		m_rectCursor(0, 0, 0, 0),
		m_mouseInside(false)
	{}
	MouseArea(CWnd* wnd, HCURSOR cursor, const CRect& rect):
		RectArea(wnd, rect),
//		m_wnd(wnd),
		m_cursor(cursor),
//		m_rectArea(rect),
		m_rectCursor(rect),
		m_mouseInside(false)
	{}
	virtual void MouseInsideChanged(){}
//	CWnd* m_wnd;
	HCURSOR m_cursor;
//	CRect m_rectArea;
	CRect m_rectCursor;
	bool m_mouseInside;
};

class UGUI_API ActiveRect : public MouseArea
{
public:
	ActiveRect(CWnd* wnd,
		HCURSOR cursor,
		const CRect& rect,
		COLORREF pictureColor,
		COLORREF bkColor,
		unsigned int borderColorPercentDiff,
		unsigned int borderWidth,
		int leftMargin,
		int topMargin,
		int rightMargin,
		int bottomMargin,
		bool drawBorderAlways,
		bool drawFrame,
		COLORREF disabledPictureColor,
		COLORREF borderColor = 0xFFFFFFFF)://0xFFFFFFFF - draw border using light and dark color
		MouseArea(wnd, cursor, rect),
		m_pictureColor(pictureColor),
		m_disabledPictureColor(disabledPictureColor),
		m_bkColor(bkColor),
		m_borderColor(borderColor),
		m_lightColor(borderColor == 0xFFFFFFFF ? UGUI_CalculateLightColor(m_bkColor, borderColorPercentDiff) : borderColor),
		m_darkColor(borderColor == 0xFFFFFFFF ? UGUI_CalculateDarkColor(m_bkColor, borderColorPercentDiff) : borderColor),
		m_borderWidth(borderWidth),
		m_borderColorPercentDiff(borderColorPercentDiff),
		m_leftMargin(leftMargin),
		m_topMargin(topMargin),
		m_rightMargin(rightMargin),
		m_bottomMargin(bottomMargin),
		m_pressed(false),
		m_drawBorderAlways(drawBorderAlways),
		m_drawFrame(drawFrame),
		m_enabled(true),
		m_grayed(false)
	{
		CalculatePictureRect();
	}
	virtual void Draw(HDC hdc, const RECT& rcPaint) const override;
	void SetPressed(const bool pressed);
	const bool& isPressed() const{return m_pressed;}
	void SetBkColor(COLORREF bkColor);
	void SetBorderColor(COLORREF bkColor);
	virtual void SetRect(const CRect& rect);
	const unsigned int& GetBorderWidth() const{return m_borderWidth;}

	const int& GetLeftMargin() const{return m_leftMargin;}
	const int& GetTopMargin() const{return m_topMargin;}
	const int& GetRightMargin() const{return m_rightMargin;}
	const int& GetBottomMargin() const{return m_bottomMargin;}

	int GetLeftRightMargin() const{return m_leftMargin + m_rightMargin;}
	int GetTopBottomMargin() const{return m_topMargin + m_bottomMargin;}

	void SetLeftMargin(const int& margin){m_leftMargin = margin;}
	void SetTopMargin(const int& margin){m_topMargin = margin;}
	void SetRightMargin(const int& margin){m_rightMargin = margin;}
	void SetBottomMargin(const int& margin){m_bottomMargin = margin;}
	const bool& isEnabled() const{return m_enabled;}
	bool SetEnabled(const bool& enabled)
	{
		if(enabled != m_enabled)
		{
			m_enabled = enabled;
			if(m_wnd->m_hWnd)InvalidateRect(m_wnd->m_hWnd, &m_rectArea, FALSE);
			return true;
		}
		return false;
	}
	const bool& isGrayed() const{return m_grayed;}
	bool SetGrayed(const bool& grayed)
	{
		if(grayed != m_grayed)
		{
			m_grayed = grayed;
			if(m_wnd->m_hWnd)InvalidateRect(m_wnd->m_hWnd, &m_rectArea, FALSE);
			return true;
		}
		return false;
	}
	void SetDrawBorderAlways(const bool& drawBorderAlways)
	{
		if(drawBorderAlways != m_drawBorderAlways)
		{
			m_drawBorderAlways = drawBorderAlways;
			if(m_wnd->m_hWnd)InvalidateRect(m_wnd->m_hWnd, &m_rectArea, FALSE);
		}
	}
	void SetDrawFrame(const bool& drawFrame)
	{
		if(drawFrame != m_drawFrame)
		{
			m_drawFrame = drawFrame;
			if(m_wnd->m_hWnd)InvalidateRect(m_wnd->m_hWnd, &m_rectArea, FALSE);
		}
	}
	void SetPictureColor(const COLORREF& color)
	{
		if(color != m_pictureColor)
		{
			m_pictureColor = color;
			if(m_wnd->m_hWnd && m_enabled && !m_grayed)InvalidateRect(m_wnd->m_hWnd, &m_rectArea, FALSE);
		}
	}
	const COLORREF& GetPictureColor() const{return m_pictureColor;}
	void SetDisabledPictureColor(const COLORREF& color)
	{
		if(color != m_disabledPictureColor)
		{
			m_disabledPictureColor = color;
			if(m_wnd->m_hWnd && (!m_enabled || m_grayed))InvalidateRect(m_wnd->m_hWnd, &m_rectArea, FALSE);
		}
	}
	const COLORREF& GetDisabledPictureColor() const{return m_disabledPictureColor;}
	virtual COLORREF GetFgColor() const{return m_enabled && !m_grayed || m_disabledPictureColor == 0xFFFFFFFF ? m_pictureColor : m_disabledPictureColor;}
protected:
	virtual void MouseInsideChanged();
	virtual void DoDraw(HDC hdc, const RECT& rcPaint) const{}
	void CalculatePictureRect();
	COLORREF m_pictureColor;
	COLORREF m_disabledPictureColor;
	COLORREF m_bkColor;
	COLORREF m_borderColor;
	COLORREF m_lightColor;
	COLORREF m_darkColor;
	unsigned int m_borderWidth;
	unsigned int m_borderColorPercentDiff;
	int m_leftMargin;
	int m_topMargin;
	int m_rightMargin;
	int m_bottomMargin;
	CRect m_pictureRect;
	bool m_pressed;
	bool m_drawBorderAlways;
	bool m_drawFrame;
	bool m_enabled;
	bool m_grayed;
};

class UGUI_API ActiveRectXButton : public ActiveRect
{
public:
	ActiveRectXButton(CWnd* wnd,
		HCURSOR cursor,
		const CRect& rect,
		COLORREF bkColor,
		unsigned int borderColorPercentDiff,
		unsigned int borderWidth,
		COLORREF pictureColor,
		int leftMargin = 0,
		int topMargin = 0,
		int rightMargin = 0,
		int bottomMargin = 0,
		bool drawBorderAlways = false,
		bool drawFrame = false,
		COLORREF disabledPictureColor = 0xFFFFFFFF,
		COLORREF borderColor = 0xFFFFFFFF):
		ActiveRect(wnd,
			cursor,
			rect,
			pictureColor,
			bkColor,
			borderColorPercentDiff,
			borderWidth,
			leftMargin,
			topMargin,
			rightMargin,
			bottomMargin,
			drawBorderAlways,
			drawFrame,
			disabledPictureColor,
			borderColor)
		{
		}
protected:
	virtual void DoDraw(HDC hdc, const RECT& rcPaint) const override;
	CRect m_xRect;
};

class UGUI_API UrlLink : public ActiveRect
{
public:
	UrlLink(CWnd* wnd,
		HCURSOR cursor,
		const char* text,
		bool drawBorderAlways = false,
		const char* url = nullptr,
		COLORREF colorUnvisited = GetSysColor(COLOR_HOTLIGHT),
		COLORREF colorVisited = RGB(0, 0, 128),
		COLORREF disabledColor = 0xFFFFFFFF);
	void SetFont(CFont* font);
	void Init(int x, int y, HDC dc = nullptr);
	void Visit();
//	COLORREF GetColorUnvisited() const{return m_colorUnvisited;}
	COLORREF GetColorVisited() const{return m_colorVisited;}
	void SetColorVisited(const COLORREF& color)
	{
		if(color != m_colorVisited)
		{
			m_colorVisited = color;
			if(m_wnd->m_hWnd && m_enabled && m_bVisited)InvalidateRect(m_wnd->m_hWnd, &m_rectArea, FALSE);
		}
	}
	virtual COLORREF GetFgColor() const{return m_enabled || m_disabledPictureColor == 0xFFFFFFFF ? m_bVisited ? m_colorVisited : m_pictureColor : m_disabledPictureColor;}
	const bool& isVisited() const{return m_bVisited;}
	void SetUrl(const char* url);
	void SetText(const char* text);
	virtual void Draw(HDC hdc, const RECT& rcPaint) const override;
protected:
	std::string m_text;
	std::string m_link;
	COLORREF m_colorVisited;
	bool m_bVisited;
	CFont m_font;
};

class UGUI_API ActiveRectText : public ActiveRect
{
public:
	ActiveRectText(CWnd* wnd,
		HCURSOR cursor,
		const CRect& rect,
		const char* text,
		COLORREF bkColor,
		unsigned int borderColorPercentDiff,
		unsigned int borderWidth,
		COLORREF textColor,
		unsigned int textMargin,
		CFont* font = nullptr,
		int leftMargin = 0,
		int topMargin = 0,
		int rightMargin = 0,
		int bottomMargin = 0,
		bool drawBorderAlways = false,
		const char* templateText = nullptr,
		const char* disabledText = nullptr,
		bool drawFrame = false,
		COLORREF disabledPictureColor = 0xFFFFFFFF,
		COLORREF borderColor = 0xFFFFFFFF);
	virtual void SetRect(const CRect& rect)
	{
		ActiveRect::SetRect(rect);
		CalculateTextRect();
	}

	void Init(int x, int y, HDC dc = nullptr);
	void SetFont(CFont* font, bool updateRect, HDC dc);
	void SetText(const char* text, bool updateRect, HDC dc);
	void SetDisabledText(const char* text, bool updateRect, HDC dc);
	void SetTemplateText(const char* text, bool updateRect, HDC dc);
	void SetTextInRect(const char* text, HDC dcExisting = nullptr);
//	virtual void Draw(HDC hdc, const RECT& rcPaint);
	const std::string& GetText() const{return m_text;}
	const std::string& GetTemplateText() const{return m_templateText;}
	const std::string& GetTemplate() const{return m_templateText.empty() ? m_text : m_templateText;}
	const CRect& GetTextRect() const{return m_textRect;}
	const CRect& GetTextPressedRect() const{return m_textPressedRect;}
	const int& GetTextMargin() const{return m_textMargin;}
	CFont* GetFont(){return m_font;}
	virtual bool hasArrow() const{return false;}
protected:
	virtual void CalculateTextRect();
	void CalculatePressedTextRect();
	virtual void DoDraw(HDC hdc, const RECT& rcPaint) const override;
//	void UpdateDimensions(const char* text);
	std::string m_text;
	std::string m_templateText;
	std::string m_disabledText;
	CRect m_textRect;
	CRect m_textPressedRect;
	int m_textMargin;
	CFont* m_font;
};

class UGUI_API ActiveRectTextAndArrow : public ActiveRectText
{
public:
	ActiveRectTextAndArrow(CWnd* wnd,
		HCURSOR cursor,
		const CRect& rect,
		const char* text,
		COLORREF bkColor,
		unsigned int borderColorPercentDiff,
		unsigned int borderWidth,
		COLORREF textColor,
		unsigned int textMargin,
		CFont* font = nullptr,
		int leftMargin = 0,
		int topMargin = 0,
		int rightMargin = 0,
		int bottomMargin = 0,
		bool drawBorderAlways = false,
		const char* templateText = nullptr,
		const char* disabledText = nullptr,
		bool arrowOnTop = false,
		bool arrowOnLeft = false,
		bool drawFrame = false,
		COLORREF disabledPictureColor = 0xFFFFFFFF,
		bool doNotDrawArrowWhenDisabled = false,
		COLORREF borderColor = 0xFFFFFFFF);
	virtual bool hasArrow() const{return !m_arrowOnTop;}
protected:
	virtual void CalculateTextRect();
	virtual void CalculateArrowRect();
	virtual void DoDraw(HDC hdc, const RECT& rcPaint) const override;
	virtual void DoDrawArrow(HDC hdc, const RECT& rcPaint) const;
	CRect m_arrowRect;
	bool m_arrowOnTop;
	bool m_arrowOnLeft;
	bool m_doNotDrawArrowWhenDisabled;
};

class UGUI_API ActiveRectCheckBox : public ActiveRectTextAndArrow
{
public:
	ActiveRectCheckBox(CWnd* wnd,
		HCURSOR cursor,
		const CRect& rect,
		const char* text,
		COLORREF bkColor,
		unsigned int borderColorPercentDiff,
		unsigned int borderWidth,
		COLORREF textColor,
		unsigned int textMargin,
		CFont* font = nullptr,
		int leftMargin = 0,
		int topMargin = 0,
		int rightMargin = 0,
		int bottomMargin = 0,
		bool drawBorderAlways = false,
		const char* templateText = nullptr,
		const char* disabledText = nullptr,
		bool checked = false,
		bool checkOnLeft = false,
		COLORREF disabledPictureColor = 0xFFFFFFFF,
		bool doNotDrawArrowWhenDisabled = false,
		COLORREF borderColor = 0xFFFFFFFF);
//	virtual bool hasArrow() const{return !m_arrowOnTop;}
	const bool& isChecked() const{return m_checked;}
	void SetCheck(const bool& checked)
	{
		if(checked != m_checked)
		{
			m_checked = checked;
			if(m_wnd->m_hWnd)InvalidateRect(m_wnd->m_hWnd, &m_arrowRect, FALSE);
		}
	}
	void ToggleCheck()
	{
		SetCheck(!m_checked);
	}
protected:
	virtual void CalculateArrowRect();
	virtual void DoDrawArrow(HDC hdc, const RECT& rcPaint) const override;
	bool m_checked;
};

class UGUI_API ActiveRectDirection : public ActiveRect
{
public:
	virtual void SetRect(const CRect& rect);
	void SetOrientation(bool vertical, bool down);
	void SetArrowMargin(unsigned int margin);
protected:
	ActiveRectDirection(CWnd* wnd,
		HCURSOR cursor,
		const CRect& rect,
		COLORREF bkColor,
		unsigned int borderColorPercentDiff,
		unsigned int borderWidth,
		COLORREF arrowColor,
		unsigned int arrowMargin,
		bool vertical,
		bool down,
		bool drawBorderAlways,
		bool drawFrame,
		COLORREF disabledPictureColor,
		COLORREF borderColor = 0xFFFFFFFF):
		ActiveRect(wnd,
			cursor,
			rect,
			arrowColor,
			bkColor,
			borderColorPercentDiff,
			borderWidth,
			0, 0, 0, 0,
			drawBorderAlways,
			drawFrame,
			disabledPictureColor,
			borderColor),
		m_arrowMargin(arrowMargin),
		m_vertical(vertical),
		m_down(down)
	{
	}
	virtual void CalculateArrowRect(){}
	CRect m_arrowRect;
	int m_arrowMargin;
	bool m_vertical;
	bool m_down;
};

class UGUI_API ActiveRectTriangle : public ActiveRectDirection
{
protected:
	ActiveRectTriangle(CWnd* wnd,
		HCURSOR cursor,
		const CRect& rect,
		COLORREF bkColor,
		unsigned int borderColorPercentDiff,
		unsigned int borderWidth,
		COLORREF arrowColor,
		unsigned int arrowMargin,
		bool vertical,
		bool down,
		bool drawBorderAlways,
		bool drawFrame,
		COLORREF disabledPictureColor):
		ActiveRectDirection(wnd,
			cursor,
			rect,
			bkColor,
			borderColorPercentDiff,
			borderWidth,
			arrowColor,
			arrowMargin, vertical,
			down,
			drawBorderAlways,
			drawFrame,
			disabledPictureColor)
	{
	}
	virtual int CalculateSmallerDimension(int biggerDimension) const = 0;//{return (biggerDimension >> 1) + 1;}
	virtual int CalculateBiggerDimension(int smallerDimension) const = 0;//{return (smallerDimension << 1) - 1;}
	virtual void CalculateArrowRect();
};

class UGUI_API ActiveRectSolidTriangle : public ActiveRectTriangle
{
public:
	ActiveRectSolidTriangle(CWnd* wnd,
		HCURSOR cursor,
		const CRect& rect,
		COLORREF bkColor,
		unsigned int borderColorPercentDiff,
		unsigned int borderWidth,
		COLORREF arrowColor,
		unsigned int arrowMargin,
		bool vertical,
		bool down,
		bool drawBorderAlways = false,
		bool drawFrame = false,
		COLORREF disabledPictureColor = 0xFFFFFFFF):
		ActiveRectTriangle(wnd,
			cursor,
			rect,
			bkColor,
			borderColorPercentDiff,
			borderWidth,
			arrowColor,
			arrowMargin,
			vertical,
			down,
			drawBorderAlways,
			drawFrame,
			disabledPictureColor)
	{
		CalculateArrowRect();
	}
	virtual int CalculateSmallerDimension(int biggerDimension) const{return (biggerDimension >> 1) + 1;}
	virtual int CalculateBiggerDimension(int smallerDimension) const{return (smallerDimension << 1) - 1;}
protected:
	virtual void DoDraw(HDC hdc, const RECT& rcPaint) const override;
};

class UGUI_API ActiveRectRoof : public ActiveRectTriangle
{
public:
	ActiveRectRoof(CWnd* wnd,
		HCURSOR cursor,
		const CRect& rect,
		COLORREF bkColor,
		unsigned int borderColorPercentDiff,
		unsigned int borderWidth,
		COLORREF arrowColor,
		unsigned int arrowMargin,
		bool vertical,
		bool down,
		int thick,
		int gap = 0,
		bool drawBorderAlways = false,
		bool drawFrame = false,
		COLORREF disabledPictureColor = 0xFFFFFFFF):
		ActiveRectTriangle(wnd,
			cursor,
			rect,
			bkColor,
			borderColorPercentDiff,
			borderWidth,
			arrowColor,
			arrowMargin,
			vertical,
			down,
			drawBorderAlways,
			drawFrame,
			disabledPictureColor),
		m_thick(thick),
		m_gap(gap),
		m_arrowRect2(0, 0, 0, 0),
		m_gapPlusThick(m_gap > 0 ? m_gap + m_thick : 0)
	{
		CalculateArrowRect();
	}
	virtual int CalculateSmallerDimension(int biggerDimension) const{return (biggerDimension >> 1) + 1 + m_thick + m_gapPlusThick;}
	virtual int CalculateBiggerDimension(int smallerDimension) const{return ((smallerDimension - m_thick - m_gapPlusThick) << 1) - 1;}
protected:
	virtual void CalculateArrowRect();
	virtual void DoDraw(HDC hdc, const RECT& rcPaint) const override;
	int m_thick;
	int m_gap;
	int m_gapPlusThick;
	CRect m_arrowRect2;
};

class UGUI_API Resizor : public MouseArea
{
public:
	void Draw(HDC hdc);
	void SetColor(COLORREF color);
	void SetLimits(int minLimit, int maxLimit);
	bool SetPositions(int minPos, int maxPos);
	bool InflatePositions(int diff);

	void SetMinBorder(int minBorder);
	void SetMaxBorder(int maxBorder);

	void Offset(int offset);
	void Offset(int offset, bool minPos);

	const int& GetMinBorder() const{return m_minBorder;}
	const int& GetMaxBorder() const{return m_maxBorder;}
	const int& GetMinLimit() const{return m_minLimit;}
	const int& GetMaxLimit() const{return m_maxLimit;}

//	const CRect& GetRect() const{return m_rect;}
//	const CRect& GetRectCursor() const{return m_rectCursor;}
//	bool isPointInside(const CPoint& point) const{return m_rectCursor.PtInRect(point) == TRUE;}
//	bool isMouseInside() const{return m_mouseInside;}
//	bool UpdateMouseInside(const CPoint& point);
//	void SetMouseInside(bool inside){m_mouseInside = inside;}
	const bool& isResizing() const{return m_resizing;}
	void SetResizing(const CPoint* point);
	void Drag(const CPoint& point);
	bool SetPos(int pos);
	void IncrementPos(int diff);
	const int& GetPos() const{return m_pos;}
	int GetPosPlusWidth() const{return m_pos + m_width;}
	const int& GetWidth() const{return m_width;}
	virtual HCURSOR GetCursor() const
	{
		if(m_pos <= m_minPos)
		{
			return m_minCursor;
		}
		else if(m_pos + m_width >= m_maxPos)
		{
			return m_maxCursor;
		}
		return m_cursor;
	}
protected:
	Resizor(CWnd* wnd,
		HCURSOR cursor,
		HCURSOR minCursor,
		HCURSOR maxCursor,
		int width,
		int minPos,
		int maxPos,
		int pos,
		int minBorder,
		int maxBorder,
		int minLimit,
		int maxLimit,
		int cursorOffsetTop,
		int cursorOffsetBottom,
		COLORREF color):

		MouseArea(wnd, cursor),
		m_width(width),
		m_minPos(minPos),
		m_maxPos(maxPos),
		m_pos(pos),
		m_minBorder(minBorder),
		m_maxBorder(maxBorder),
		m_minLimit(minLimit),
		m_maxLimit(maxLimit),
		m_color(color),
		m_cursorOffsetTop(cursorOffsetTop),
		m_cursorOffsetBottom(cursorOffsetBottom),
		m_resizing(false),
		m_offset(0),
		m_minCursor(minCursor),
		m_maxCursor(maxCursor)
	{
	}
	bool AdjustPos();
	virtual void UpdateOffset(const CPoint& point) = 0;
	virtual void UpdatePos(const CPoint& point) = 0;
	virtual void UpdateRectByPos() = 0;
	virtual void UpdateMinBorder() = 0;
	virtual void UpdateMaxBorder() = 0;
	int m_width;
	int m_minPos;
	int m_maxPos;
	int m_pos;
	int m_minBorder;
	int m_maxBorder;
	int m_minLimit;
	int m_maxLimit;
	COLORREF m_color;
	int m_cursorOffsetTop;
	int m_cursorOffsetBottom;
	bool m_resizing;
	int m_offset;
	HCURSOR m_minCursor;
	HCURSOR m_maxCursor;
};

class UGUI_API VerticalResizor : public Resizor
{
public:
	VerticalResizor(CWnd* wnd,
		HCURSOR cursor,
		HCURSOR minCursor,
		HCURSOR maxCursor,
		int width,
		int minPos,
		int maxPos,
		int pos,
		int minBorder,
		int maxBorder,
		int minLimit,
		int maxLimit,
		int cursorOffsetTop,
		int cursorOffsetBottom,
		COLORREF color):

		Resizor(wnd,
			cursor,
			minCursor,
			maxCursor,
			width,
			minPos,
			maxPos,
			pos,
			minBorder,
			maxBorder,
			minLimit,
			maxLimit,
			cursorOffsetTop,
			cursorOffsetBottom,
			color)
	{
		m_rectArea.top = m_pos;
		m_rectCursor.top = m_rectArea.top - m_cursorOffsetTop;
		m_rectArea.bottom = m_rectArea.top + m_width;
		m_rectCursor.bottom = m_rectArea.bottom + m_cursorOffsetBottom;
		m_rectArea.left = m_rectCursor.left = m_minBorder;
		m_rectArea.right = m_rectCursor.right = m_maxBorder;
	}
protected:
	virtual void UpdateOffset(const CPoint& point)
	{
		m_offset = point.y - m_rectArea.top;
	}
	virtual void UpdatePos(const CPoint& point)
	{
		SetPos(point.y - m_offset);
	}
	virtual void UpdateRectByPos()
	{
		m_rectArea.top = m_pos;
		m_rectCursor.top = m_rectArea.top - m_cursorOffsetTop;
		m_rectArea.bottom = m_rectArea.top + m_width;
		m_rectCursor.bottom = m_rectArea.bottom + m_cursorOffsetBottom;
	}
	virtual void UpdateMinBorder()
	{
		m_rectArea.left = m_rectCursor.left = m_minBorder;
	}

	virtual void UpdateMaxBorder()
	{
		m_rectArea.right = m_rectCursor.right = m_maxBorder;
	}
};

class UGUI_API HorizontalResizor : public Resizor
{
public:
	HorizontalResizor(CWnd* wnd,
		HCURSOR cursor,
		HCURSOR minCursor,
		HCURSOR maxCursor,
		int width,
		int minPos,
		int maxPos,
		int pos,
		int minBorder,
		int maxBorder,
		int minLimit,
		int maxLimit,
		int cursorOffsetTop,
		int cursorOffsetBottom,
		COLORREF color):

		Resizor(wnd,
			cursor,
			minCursor,
			maxCursor,
			width,
			minPos,
			maxPos,
			pos,
			minBorder,
			maxBorder,
			minLimit,
			maxLimit,
			cursorOffsetTop,
			cursorOffsetBottom,
			color)
	{
		m_rectArea.left = m_pos;
		m_rectCursor.left = m_rectArea.left - m_cursorOffsetTop;
		m_rectArea.right = m_rectArea.left + m_width;
		m_rectCursor.right = m_rectArea.right + m_cursorOffsetBottom;
		m_rectArea.top = m_rectCursor.top = m_minBorder;
		m_rectArea.bottom = m_rectCursor.bottom = m_maxBorder;
	}
protected:
	virtual void UpdateOffset(const CPoint& point)
	{
		m_offset = point.x - m_rectArea.left;
	}
	virtual void UpdatePos(const CPoint& point)
	{
		SetPos(point.x - m_offset);
	}
	virtual void UpdateRectByPos()
	{
		m_rectArea.left = m_pos;
		m_rectCursor.left = m_rectArea.left - m_cursorOffsetTop;
		m_rectArea.right = m_rectArea.left + m_width;
		m_rectCursor.right = m_rectArea.right + m_cursorOffsetBottom;
	}
	virtual void UpdateMinBorder()
	{
		m_rectArea.top = m_rectCursor.top = m_minBorder;
	}

	virtual void UpdateMaxBorder()
	{
		m_rectArea.bottom = m_rectCursor.bottom = m_maxBorder;
	}
};

class UGUI_API ButtonItem
{
public:
	ButtonItem(int x, int y, int width, int height, int deflatePixelCount, int borderSize,
		COLORREF bkColor,
		COLORREF lightColor,
		COLORREF darkColor,
		unsigned int ordinal):
		m_borderSize(borderSize),
		m_deflatePixelCount(deflatePixelCount),
		m_itemRect(x, y, x + width, y + height),
		m_clientRect(m_itemRect),
		m_pressed(false),
		m_bkColor(bkColor),
		m_originalBkColor(bkColor),
		m_lightColor(lightColor),
		m_darkColor(darkColor),
		m_mouseHover(false),
		m_ordinal(ordinal)
	{
		if(deflatePixelCount)
		{
			m_itemRect.DeflateRect(deflatePixelCount, deflatePixelCount);
			m_clientRect.DeflateRect(deflatePixelCount, deflatePixelCount);
		}
		m_clientRect.DeflateRect(borderSize, borderSize);
	}
	virtual ~ButtonItem(){}

	const int& GetDeflatePixelCount() const{return m_deflatePixelCount;}
	bool SetDeflatePixelCount(const int& deflatPixelCount)
	{
		if(deflatPixelCount != m_deflatePixelCount)
		{
			m_deflatePixelCount = deflatPixelCount;
			return true;
		}
		return false;
	}

	void Draw(HDC dc, const RECT& rcPaint) const;
//	void DrawFocusRect(CDC* dc, COLORREF textColor);
	const CRect& GetItemRect() const{return m_itemRect;}
	const CRect& GetClientRect() const{return m_clientRect;}
	void SetItemRect(const int& left, const int& top, const int& width, const int& height)
	{
		m_itemRect.left = left + m_deflatePixelCount;
		m_itemRect.top = top + m_deflatePixelCount;
		m_itemRect.right = left + width - m_deflatePixelCount;
		m_itemRect.bottom = top + height - m_deflatePixelCount;

		m_clientRect.left = m_itemRect.left + m_borderSize;
		m_clientRect.top = m_itemRect.top + m_borderSize;
		m_clientRect.right = m_itemRect.right - m_borderSize;
		m_clientRect.bottom = m_itemRect.bottom - m_borderSize;
	}
	void SetItemWidth(const int& width)
	{
		m_itemRect.right = m_itemRect.left + width - m_deflatePixelCount - m_deflatePixelCount;
		m_clientRect.right = m_itemRect.right - m_borderSize;
	}
	void SetItemLeftAndWidth(const int& left, const int& width, const CRect* rowRect)
	{
		m_itemRect.left = left + m_deflatePixelCount;
		m_clientRect.left = m_itemRect.left + m_borderSize;
		SetItemWidth(width);

		if(rowRect)
		{
			m_itemRect.top = rowRect->top + m_deflatePixelCount;
			m_clientRect.top = m_itemRect.top + m_borderSize;
			SetItemHeight(rowRect->Height());
		}
	}
	void SetItemHeight(const int& height)
	{
		m_itemRect.bottom = m_itemRect.top + height - m_deflatePixelCount - m_deflatePixelCount;
		m_clientRect.bottom = m_itemRect.bottom - m_borderSize;
	}
	void SetItemTopAndHeight(const int& top, const int& height, const CRect* rowRect)
	{
		m_itemRect.top = top + m_deflatePixelCount;
		m_clientRect.top = m_itemRect.top + m_borderSize;
		SetItemHeight(height);

		if(rowRect)
		{
			m_itemRect.left = rowRect->left + m_deflatePixelCount;
			m_clientRect.left = m_itemRect.left + m_borderSize;
			SetItemWidth(rowRect->Width());
		}
	}
	virtual bool shouldDrawPressed() const{return m_pressed;}
	const bool& isPressed() const{return m_pressed;}
	virtual bool SetPressed(const bool& pressed)
	{
		if(pressed != m_pressed)
		{
			m_pressed = pressed;
			return true;
		}
		return false;
	}
	virtual void DoDraw(HDC dc, const RECT& rcPaint) const{}

	const unsigned int& GetOrdinal() const{return m_ordinal;}
	void SetOrdinal(const unsigned int& ordinal){m_ordinal = ordinal;}

	bool SetLightColor(const COLORREF& color)
	{
		if(color != m_lightColor)
		{
			m_lightColor = color;
			return true;
		}
		return false;
	}
	bool SetDarkColor(const COLORREF& color)
	{
		if(color != m_darkColor)
		{
			m_darkColor = color;
			return true;
		}
		return false;
	}
	bool SetBkColor(const COLORREF& color)
	{
		if(color != m_bkColor)
		{
			m_bkColor = color;
			return true;
		}
		return false;
	}
	void SetOriginalBkColor(const COLORREF& color){m_originalBkColor = color;}

	void SetMouseHover(const bool& hover){m_mouseHover = hover;}
	const bool& isMouseHover() const{return m_mouseHover;}
	virtual bool isActive() const{return false;}
	virtual bool isDefaultTextColor() const{return true;}
	virtual bool isDefaultBkColor() const{return true;}
	virtual bool SetTextFont(CFont* const& font){return false;}
	virtual bool SetTextColor(const COLORREF& textColor){return false;}
	virtual bool SetActiveBkColor(const COLORREF& color){return false;}
	virtual bool SetActiveTextColor(const COLORREF& color){return false;}
protected:
	int m_borderSize;
	int m_deflatePixelCount;
	CRect m_itemRect;
	CRect m_clientRect;
	bool m_pressed;
	COLORREF m_bkColor;
	COLORREF m_originalBkColor;
	COLORREF m_lightColor;
	COLORREF m_darkColor;
	bool m_mouseHover;
	unsigned int m_ordinal;
};

class UGUI_API ButtonTab : public ButtonItem
{
public:
	ButtonTab(int x, int y, int width, int height, int deflatePixelCount,// int borderSize,
		bool vertical,
		bool rightJustified,
		COLORREF bkColor,
		COLORREF lightColor,
		COLORREF darkColor,
		unsigned int ordinal,
		const char* text,
		CFont* font = nullptr,
		CFont* fontBold = nullptr,
		COLORREF textColor = 0xFFFFFFFF,
		COLORREF activeBkColor = 0xFFFFFFFF,
		COLORREF activeTextColor = 0xFFFFFFFF);
	virtual void DoDraw(HDC dc, const RECT& rcPaint) const override;
	const char* GetText() const{return m_text.c_str();}
	virtual bool isActive() const{return m_active;}
	bool SetActive(bool active);
	virtual bool SetPressed(const bool& pressed) override
	{
		return !m_active && ButtonItem::SetPressed(pressed);
	}
	virtual bool shouldDrawPressed() const{return m_pressed || m_active;}
	virtual bool SetTextColor(const COLORREF& textColor) override
	{
		if(textColor != m_textColor)
		{
			m_textColor = textColor;
			return true;
		}
		return false;
	}
	virtual bool SetActiveBkColor(const COLORREF& color)
	{
		if(color != m_activeBkColor)
		{
			m_activeBkColor = color;
			return true;
		}
		return false;
	}
	virtual bool SetActiveTextColor(const COLORREF& color)
	{
		if(color != m_activeTextColor)
		{
			m_activeTextColor = color;
			return true;
		}
		return false;
	}
	virtual bool SetTextFont(CFont* const& font) override
	{
		if(font != m_font)
		{
			m_font = font;
		}
		return false;
	}
	CFont* const& GetFontBold() const{return m_fontBold;}
protected:
	bool m_vertical;
	bool m_rightJustified;
	bool m_active;
	std::string m_text;
	CFont* m_font;
	CFont* m_fontBold;
	COLORREF m_textColor;
	COLORREF m_activeBkColor;
	COLORREF m_activeTextColor;
};

class UGUI_API ButtonSquareImage : public ButtonItem
{
public:
	ButtonSquareImage(int x, int y, int width, int height, int deflatePixelCount, int borderSize,
		COLORREF bkColor,
		COLORREF lightColor,
		COLORREF darkColor,
		unsigned int ordinal,
		CBitmap* bitmap);
	virtual void DoDraw(HDC dc, const RECT& rcPaint) const override;
	const CBitmap* const& GetBitmap() const{return m_bitmap;}
	CBitmap* const& GetBitmap(){return m_bitmap;}
protected:
	CBitmap* m_bitmap;
};

class UGUI_API ToolCreationButton : public ButtonSquareImage
{
public:
	ToolCreationButton(int x, int y, int width, int height, int deflatePixelCount, int borderSize,
		COLORREF bkColor,
		COLORREF lightColor,
		COLORREF darkColor,
		unsigned int ordinal,
		CBitmap* bitmap,
		const char* toolName):
		ButtonSquareImage(x, y, width, height, deflatePixelCount, borderSize, bkColor, lightColor, darkColor, ordinal, bitmap),
		m_toolName(toolName)
	{
	}

	const std::string& GetToolNameString() const{return m_toolName;}
	const char* GetToolName() const{return m_toolName.c_str();}
protected:
	std::string m_toolName;
};

class UGUI_API ButtonRow : public MouseArea
{
public:
	virtual ~ButtonRow();
	virtual void ClearButtons();
	virtual void Draw(HDC dc, const RECT& rcPaint) const override;
	const int& GetWidth() const{return m_width;}
	bool SetWidth(int width);
	void AddButton(ButtonItem* item);
	typedef std::vector<ButtonItem*> ButtonVector;
	const bool& isVertical() const{return m_vertical;}
	const bool& isRightJustified() const{return m_rightJustified;}

	void SetRowRect(const int& left, const int& top, const int& right, const int& bottom)
	{
		m_rectArea.left = left;
		m_rectArea.top = top;
		m_rectArea.right = right;
		m_rectArea.bottom = bottom;
		UpdateClipRgn();
	}
/*
	void SetRowLeft(int left){m_rectArea.left = left; UpdateClipRgn();}
	void SetRowTop(int top){m_rectArea.top = top; UpdateClipRgn();}
	void SetRowRight(int right){m_rectArea.right = right; UpdateClipRgn();}
	void SetRowBottom(int bottom){m_rectArea.bottom = bottom; UpdateClipRgn();}
	void SetRowLeftRight(int left, int right){m_rectArea.left = left; m_rectArea.right = right; UpdateClipRgn();}
	void SetRowTopBottom(int top, int bottom){m_rectArea.top = top; m_rectArea.bottom = bottom; UpdateClipRgn();}
*/
	void SetRowLeft(const int& left)
	{
		if(left !=m_rectArea.left)
		{
			m_rectArea.left = left;
			UpdateClipRgn();
		}
	}
	void SetRowTop(const int& top)
	{
		if(top != m_rectArea.top)
		{
			m_rectArea.top = top;
			UpdateClipRgn();
		}
	}
	void SetRowRight(const int& right)
	{
		if(right != m_rectArea.right)
		{
			m_rectArea.right = right;
			UpdateClipRgn();
		}
	}
	void SetRowBottom(const int& bottom)
	{
		if(bottom != m_rectArea.bottom)
		{
			m_rectArea.bottom = bottom;
			UpdateClipRgn();
		}
	}
	void SetRowLeftRight(const int& left, const int& right)
	{
		if(left != m_rectArea.left || right !=m_rectArea.right)
		{
			m_rectArea.left = left;
			m_rectArea.right = right;
			UpdateClipRgn();
		}
	}
	void SetRowTopBottom(const int& top, const int& bottom)
	{
		if(top != m_rectArea.top || bottom != m_rectArea.bottom)
		{
			m_rectArea.top = top;
			m_rectArea.bottom = bottom;
			UpdateClipRgn();
		}
	}

	bool SetBkColor(COLORREF color);
	bool SetLightColor(COLORREF color);
	bool SetDarkColor(COLORREF color);

	ButtonItem* GetButtonAt(const int& i){return i >= 0 && i < (int)m_buttonVector.size() ? m_buttonVector[i] : nullptr;}
	const ButtonItem* GetButtonAt(const int& i) const{return i >= 0 && i < (int)m_buttonVector.size() ? m_buttonVector[i] : nullptr;}
	const ButtonVector& GetButtonVector() const{return m_buttonVector;}
	ButtonVector& GetButtonVector(){return m_buttonVector;}
	unsigned int GetButtonCount() const{return (unsigned int)m_buttonVector.size();}

	virtual void UpdateRects()
	{
	}
	virtual int CalculateButtonUnderMouse(const CPoint& point) const{return -1;}
	virtual bool SetButtonUnderMouse(int buttonUnderMouse){return false;}
	virtual int GetButtonUnderMouse() const{return -1;}
	bool UpdateButtonUnderMouse(const CPoint& point);
	ButtonItem* Press(bool pressed);
	virtual ButtonItem* SetPressed(bool pressed){return nullptr;}
protected:
	ButtonRow(CWnd* wnd,
		HCURSOR cursor,
		int left,
		int top,
		int right,
		int bottom,
		bool vertical,
		bool rightJustified,
		int width,
		int borderSize,
		int cursorOffsetLeft,
		int cursorOffsetTop,
		int cursorOffsetRight,
		int cursorOffsetBottom,
		COLORREF bkColor,
		COLORREF lightColor,
		COLORREF darkColor):

		MouseArea(wnd, cursor),
		m_vertical(vertical),
		m_rightJustified(rightJustified),
		m_width(width),
		m_borderSize(borderSize),
		m_cursorOffsetLeft(cursorOffsetLeft),
		m_cursorOffsetTop(cursorOffsetTop),
		m_cursorOffsetRight(cursorOffsetRight),
		m_cursorOffsetBottom(cursorOffsetBottom),
		m_bkColor(bkColor),
		m_lightColor(lightColor),
		m_darkColor(darkColor),
		m_pressed(false)
	{
		SetRowRect(left, top, right, bottom);
	}
/*
	void SetRowBoundary(LONG& boundary, int value)
	{
		if(boundary != value)
		{
			boundary = value;
		}
	}
*/
	void UpdateClipRgn()
	{
		m_rectCursor.left = m_rectArea.left + m_cursorOffsetLeft;
		m_rectCursor.top = m_rectArea.top + m_cursorOffsetTop;
		m_rectCursor.right = m_rectArea.right - m_cursorOffsetRight;
		m_rectCursor.bottom = m_rectArea.bottom - m_cursorOffsetBottom;
//		m_clipRgn.DeleteObject();
//		m_clipRgn.CreateRectRgnIndirect(&m_rectArea);
//Here
		UpdateRects();
		DoUpdateClipRgn();
	}
	virtual void SetClipRgn(HDC dc) const{}
	virtual void ReleaseClipRgn(HDC dc) const{}
	virtual void DoUpdateClipRgn() const{}
	ButtonVector m_buttonVector;
//	CRgn m_clipRgn;
	bool m_vertical;
	bool m_rightJustified;
	int m_width;
	int m_borderSize;
	int m_cursorOffsetLeft;
	int m_cursorOffsetTop;
	int m_cursorOffsetRight;
	int m_cursorOffsetBottom;
	COLORREF m_bkColor;
	COLORREF m_lightColor;
	COLORREF m_darkColor;
	bool m_pressed;
};

class UGUI_API ButtonRowSameSize : public ButtonRow
{
public:
	ButtonRowSameSize(CWnd* wnd,
		HCURSOR cursor,
		int left,
		int top,
		int right,
		int bottom,
		bool vertical,
		bool rightJustified,
		int width,
		int borderSize,
		int cursorOffsetLeft,
		int cursorOffsetTop,
		int cursorOffsetRight,
		int cursorOffsetBottom,
		COLORREF bkColor,
		COLORREF lightColor,
		COLORREF darkColor,
		int buttonHeight,
		int gapPixelCount,
		int deflatePixelCount):
		ButtonRow(wnd, cursor,
			left,
			top,
			right,
			bottom,
			vertical, rightJustified, width, borderSize,
			cursorOffsetLeft,
			cursorOffsetTop,
			cursorOffsetRight,
			cursorOffsetBottom,
			bkColor,
			lightColor,
			darkColor),
		m_buttonHeight(buttonHeight),
		m_gapPixelCount(gapPixelCount),
		m_deflatePixelCount(deflatePixelCount),
		m_buttonUnderMouse(-1)
	{
	}
//	virtual ~ButtonRowSameSize();
	const int& GetButtonHeight() const{return m_buttonHeight;}
	const int& GetGapPixelCount() const{return m_gapPixelCount;}
	const int& GetDeflatePixelCount() const{return m_deflatePixelCount;}
	bool SetButtonHeight(int buttonHeight);
	bool SetGapPixelCount(int gapPixelCount);
	bool SetDeflatePixelCount(int deflatePixelCount);
	bool SetButtonHeightAndGapPixelCount(int buttonHeight, int gapPixelCount, int deflatePixelCount);
//	virtual void AppendButton() = 0;
	virtual void UpdateRects();
	virtual void Draw(HDC dc, const RECT& rcPaint) const override;
//	virtual bool UpdateButtonUnderMouse(const CPoint& point);
	virtual int CalculateButtonUnderMouse(const CPoint& point) const;
	virtual int GetButtonUnderMouse() const{return m_buttonUnderMouse;}
	virtual bool SetButtonUnderMouse(int buttonUnderMouse);
	virtual ButtonItem* SetPressed(bool pressed);
protected:
	void UpadteHeightAndGap(bool deflationChanged);
	int m_buttonHeight;
	int m_gapPixelCount;
	int m_deflatePixelCount;
	int m_buttonUnderMouse;
};

class UGUI_API ButtonRowClipRgn : public ButtonRowSameSize
{
public:
	bool SetTextColor(const COLORREF& textColor);
	bool SetFont(CFont* const& font);
protected:
	ButtonRowClipRgn(CWnd* wnd,
		HCURSOR cursor,
		int left,
		int top,
		int right,
		int bottom,
		bool vertical,
		bool rightJustified,
		int width,
		int borderSize,
		int cursorOffsetLeft,
		int cursorOffsetTop,
		int cursorOffsetRight,
		int cursorOffsetBottom,
		COLORREF bkColor,
		COLORREF lightColor,
		COLORREF darkColor,
		COLORREF textColor,
		int buttonHeight,
		int gapPixelCount,
		int deflatePixelCount,
		CFont* font):
		ButtonRowSameSize(wnd, cursor,
			left,
			top,
			right,
			bottom,
			vertical, rightJustified, width, borderSize,
			cursorOffsetLeft,
			cursorOffsetTop,
			cursorOffsetRight,
			cursorOffsetBottom,
			bkColor,
			lightColor,
			darkColor,
			buttonHeight,
			gapPixelCount,
			deflatePixelCount),
		m_font(font),
		m_textColor(textColor)
	{
	}

	virtual void DoUpdateClipRgn() const override
	{
		m_clipRgn.DeleteObject();
		m_clipRgn.CreateRectRgnIndirect(&m_rectArea);
	}
	virtual void SetClipRgn(HDC dc) const override
	{
		SelectClipRgn(dc, m_clipRgn);
	}
	virtual void ReleaseClipRgn(HDC dc) const override
	{
		SelectClipRgn(dc, nullptr);
	}
	mutable CRgn m_clipRgn;
	CFont* m_font;
	COLORREF m_textColor;
};

class UGUI_API ButtonRowSquareImage : public ButtonRowSameSize
{
public:
	ButtonRowSquareImage(CWnd* wnd,
		HCURSOR cursor,
		int left,
		int top,
		int right,
		int bottom,
		bool vertical,
		bool rightJustified,
		int width,
		int borderSize,
		int cursorOffsetLeft,
		int cursorOffsetTop,
		int cursorOffsetRight,
		int cursorOffsetBottom,
		COLORREF bkColor,
		COLORREF lightColor,
		COLORREF darkColor,
		int buttonHeight,
		int gapPixelCount,
		int deflatePixelCount):
		ButtonRowSameSize(wnd, cursor,
			left,
			top,
			right,
			bottom,
			vertical, rightJustified, width, borderSize,
			cursorOffsetLeft,
			cursorOffsetTop,
			cursorOffsetRight,
			cursorOffsetBottom,
			bkColor,
			lightColor,
			darkColor,
			buttonHeight,
			gapPixelCount,
			deflatePixelCount)
	{
	}
	ButtonSquareImage* AppendButton(CBitmap* bitmap);
};

class UGUI_API ToolBar : public ButtonRowSquareImage
{
public:
	ToolBar(CWnd* wnd,
		HCURSOR cursor,
		int left,
		int top,
		int right,
		int bottom,
		bool vertical,
		bool rightJustified,
		int width,
		int borderSize,
		int cursorOffsetLeft,
		int cursorOffsetTop,
		int cursorOffsetRight,
		int cursorOffsetBottom,
		COLORREF bkColor,
		COLORREF lightColor,
		COLORREF darkColor,
		int buttonHeight,
		int gapPixelCount,
		int deflatePixelCount):
		ButtonRowSquareImage(wnd, cursor,
			left,
			top,
			right,
			bottom,
			vertical, rightJustified, width, borderSize,
			cursorOffsetLeft,
			cursorOffsetTop,
			cursorOffsetRight,
			cursorOffsetBottom,
			bkColor,
			lightColor,
			darkColor,
			buttonHeight,
			gapPixelCount,
			deflatePixelCount)
	{
	}
	ToolCreationButton* AppendButton(CBitmap* bitmap, const char* toolName);
	virtual void ClearButtons();
	typedef std::map<std::string, ToolCreationButton*> ButtonMap;
	const ToolCreationButton* FindButton(const std::string& toolName) const{ButtonMap::const_iterator found = m_buttonMap.find(toolName); return found == m_buttonMap.cend() ? nullptr : found->second;}
protected:
	ButtonMap m_buttonMap;
};

class UGUI_API TabRowSameSize : public ButtonRowClipRgn
{
public:
	TabRowSameSize(CWnd* wnd,
		HCURSOR cursor,
		int left,
		int top,
		int right,
		int bottom,
		bool vertical,
		bool rightJustified,
		int width,
		int borderSize,
		int cursorOffsetLeft,
		int cursorOffsetTop,
		int cursorOffsetRight,
		int cursorOffsetBottom,
		COLORREF bkColor,
		COLORREF lightColor,
		COLORREF darkColor,
		int buttonHeight,
		int gapPixelCount,
		int deflatePixelCount,
		CFont* font,
		CFont* fontBold,
		COLORREF textColor = 0xFFFFFFFF,
		COLORREF activeBkColor = 0xFFFFFFFF,
		COLORREF activeTextColor = 0xFFFFFFFF);
	virtual ~TabRowSameSize();
	ButtonTab* AppendButton(const char* text);
	const int& GetActive() const{return m_active;}
	void SetActive(int active);
	void SetTabTextColor(unsigned int i, const COLORREF textColor);
	void SetTabTextFont(unsigned int i, CFont* const font);
	const COLORREF& GetActiveBkColor() const{return m_activeBkColor;}
	const COLORREF& GetActiveTextColor() const{return m_activeTextColor;}
	void InvalidateActiveItem()
	{
		if(m_wnd->m_hWnd)
		{
			const ButtonItem* tab = GetButtonAt(m_active);
			if(tab)m_wnd->InvalidateRect(tab->GetClientRect(), FALSE);
		}
	}
	void SetActiveBkColor(COLORREF color)
	{
		if(0xFFFFFFFF == color)color = m_bkColor;
		if(color != m_activeBkColor)
		{
			m_activeBkColor = color;
			for(ButtonVector::iterator it = m_buttonVector.begin(), itend = m_buttonVector.end(); it != itend; ++it)
			{
				(*it)->SetActiveBkColor(color);
			}

			InvalidateActiveItem();
		}
	}
	void SetActiveTextColor(COLORREF color)
	{
		if(0xFFFFFFFF == color)color = m_textColor;
		if(color != m_activeTextColor)
		{
			m_activeTextColor = color;
			for(ButtonVector::iterator it = m_buttonVector.begin(), itend = m_buttonVector.end(); it != itend; ++it)
			{
				(*it)->SetActiveTextColor(color);
			}
			InvalidateActiveItem();
		}
	}
protected:
	CFont* m_fontBold;
	COLORREF m_activeBkColor;
	COLORREF m_activeTextColor;
	int m_active;
};

class UGUI_API ControlToolTipHelper
{
public:
	virtual ~ControlToolTipHelper()
	{
		DestroyToolTip(nullptr);
		U_ReplaceText(m_tooltipText, nullptr);
	}

	virtual bool isToDestroyToolTipIfNoText() const{return true;}

	const char* const& GetTooltipText() const{return m_tooltipText;}
	bool SetTooltipText(const char* const& tooltipText)
	{
		const bool oldNull = !m_tooltipText;
		if(U_ReplaceText(m_tooltipText, tooltipText))
		{
			if(m_tooltipsEnabled)
			{
				if(oldNull)
				{
					DoInitialize(m_externalToolTip);
				}
				else if(!tooltipText && isToDestroyToolTipIfNoText())
				{
					DestroyToolTip(m_externalToolTip);
				}
				else if(m_toolTip && m_toolTip->m_hWnd)
				{
//					m_toolTip->Activate(FALSE);
					UpdateTooltipText();
				}
				else
				{
					DoInitialize(m_externalToolTip);
				}
			}
			return true;
		}
		return false;
	}
	const CRect& GetControlRect() const{return m_controlRect;}
	virtual const CRect& GetToolTipRect() const{return m_controlRect;}
	bool ObtainControlRect(CRect& rect) const
	{
		if(m_wnd->m_hWnd)
		{
			GetClientRect(m_wnd->m_hWnd, &rect);
//			DoGetControlRect(rect);
			return true;
		}
		else
		{
			rect.left = rect.top = rect.right = rect.bottom = 0;
			return false;
		}
	}

	bool UpdateToolTipToContents()
	{
		if(m_wnd->m_hWnd)
		{
			CString text;
			m_wnd->GetWindowText(text);
			return SetTooltipText(text);
		}
		return false;
	}

	virtual bool CanCreateToolTip() const{return GetToolTipText() != nullptr;}

	const bool& isTooltipsEnabled() const{return m_tooltipsEnabled;}
	bool EnableTooltips(const bool& enable, CToolTipCtrl* externalToolTip)
	{
		if(enable != m_tooltipsEnabled)
		{
			m_tooltipsEnabled = enable;
			if(enable)
			{
//				if(GetToolTipText())
				if(CanCreateToolTip())
				{
					DoInitialize(externalToolTip);
				}
				else
				{
					m_externalToolTip = externalToolTip;
				}
				return true;
			}
			else
			{
				DestroyToolTip(externalToolTip);
			}
		}
		return false;
	}
	virtual const char* GetToolTipText() const{return m_tooltipText;}
	const unsigned int& GetCtrlId() const{return m_ctrlId;}
	bool UpdateToolTipRect()
	{
		if(m_toolTip)
		{
			m_toolTip->SetToolRect(m_wnd, m_ctrlId, &GetToolTipRect());
			return true;
		}
		return false;
	}
protected:
	ControlToolTipHelper(CWnd* const& wnd, const char* const& tooltipText = nullptr, CToolTipCtrl* externalToolTip = nullptr):
		m_wnd(wnd),
		m_ctrlId(0),
		m_tooltipText(nullptr),//tooltipText ? tooltipText : ""),
		m_controlRect(0, 0, 0, 0),
		m_toolTip(nullptr),
		m_externalToolTip(externalToolTip),
		m_tooltipsEnabled(false),
		m_menuHasSeparator(false),
		m_menuDisplayed(false),
		m_mouseInside(false)
	{
		U_ReplaceText(m_tooltipText, tooltipText);
	}
	virtual void ToolTipCreated();
	void AddMenuSeparator(CMenu& menu) const
	{
		if(menu.GetMenuItemCount())
		{
			menu.AppendMenu(MF_SEPARATOR);
			m_menuHasSeparator = true;
		}
	}

	BOOL ProcessShowToolTip(const LPARAM& lParam, LRESULT* const& pResult);

	void PreTranslateMessage(MSG* pMsg)
	{
		if(m_toolTip && m_toolTip->m_hWnd)m_toolTip->RelayEvent(pMsg);
	}
	void Initialize()
	{
		m_ctrlId = (unsigned int)::GetDlgCtrlID(m_wnd->m_hWnd);
		m_menuDisplayed = false;
		m_mouseInside = false;
		ObtainControlRect(m_controlRect);
		if(m_tooltipsEnabled && GetToolTipText())
		{
			DoInitialize(m_externalToolTip);
		}
	}

	void DoInitialize(CToolTipCtrl* externalToolTip);
/*
	void DoGetControlRect(CRect& rect) const
	{
		m_wnd->GetWindowRect(&rect);
		rect.right -= rect.left;
		rect.bottom -= rect.top;
		rect.left = rect.top = 0;
	}
*/
	bool SizeToolTip()
	{
		GetClientRect(m_wnd->m_hWnd, &m_controlRect);
		return UpdateToolTipRect();
	}
	
	void DestroyToolTip(CToolTipCtrl* externalToolTip);

	virtual void UpdateTooltipText()
	{
		if(m_toolTip && m_toolTip->m_hWnd)
		{
			const char* tooltipText = GetToolTipText();
			m_toolTip->UpdateTipText(tooltipText ? tooltipText : "", m_wnd, m_ctrlId);
//			m_toolTip->Activate(TRUE);
			m_toolTip->Update();
/*
			TOOLINFO toolInfo;
			toolInfo.cbSize = sizeof(TOOLINFO);
			toolInfo.hinst = nullptr;
			toolInfo.uFlags = TTF_SUBCLASS|TTF_TRANSPARENT;
			toolInfo.hwnd = m_wnd->m_hWnd;
			toolInfo.lParam = nullptr;
			toolInfo.lpReserved = nullptr;

//			toolInfo.lpszText = (char*)m_tooltipText.c_str();
			toolInfo.lpszText = m_tooltipText ? m_tooltipText : "";

//			CRect rect;
//			DoGetControlRect(rect);

			toolInfo.rect = m_controlRect;//rect;
			toolInfo.uId = m_ctrlId;// GetCtrlId();

			m_toolTip->SetToolInfo(&toolInfo);

			m_toolTip->Activate(TRUE);
*/
		}
	}
	bool SetMouseInside(const bool& mouseInside)
	{
		if(mouseInside != m_mouseInside)
		{
			m_mouseInside = mouseInside;
			if(mouseInside)MouseEntered();
			else MouseLeft();
//			SendMessageToParent(mouseInside ? WM_USER + 16 : WM_USER + 36, GetDlgCtrlID(), (LPARAM)m_hWnd);//this);
			return true;
		}
		return false;
	}

	virtual void MouseEntered(){}
	virtual void MouseLeft(){}

	CWnd* m_wnd;
	CRect m_controlRect;
	char* m_tooltipText;
	CToolTipCtrl* m_toolTip;
	CToolTipCtrl* m_externalToolTip;
	unsigned int m_ctrlId;
	void CreateOwnToolTip();
//	bool m_tooltipOwner;
	bool m_tooltipsEnabled;
	virtual void BeforeDestroy()
	{
		m_menuHasSeparator = false;
		m_menuDisplayed = false;
		m_mouseInside = false;
		DestroyToolTip(nullptr);
		m_ctrlId = 0;
		m_tooltipsEnabled = false;
	}
	mutable bool m_menuHasSeparator;
	bool m_menuDisplayed;
	bool m_mouseInside;
};

class UGUI_API EditNoContext : public CEdit, public ControlToolTipHelper
{
public:
	enum CaseStyle : unsigned char
	{
		ECS_NONE,
		ECS_UPPER,
		ECS_LOWER,
	};
	EditNoContext(const bool& readOnly = false, const char* const& tooltipText = nullptr, const bool& letParentProcessUpdate = false, CToolTipCtrl* externalToolTip = nullptr):
		ControlToolTipHelper(this, tooltipText, externalToolTip),
		m_letParentProcessUpdate(letParentProcessUpdate),
		m_readOnly(readOnly),
		m_caseStyle(ECS_NONE),
		m_multiline(false),
		m_lastSel(0),
		m_rejectingChange(false),
//		m_mouseInside(false),
		m_accumulatedWheel(0),
		m_formattingRect(0, 0, 0, 0),
		m_copyMenuWidth(0),
		m_pasteMenuWidth(0),
		m_insertMenuWidth(0),
		m_clearMenuWidth(0)
	{}
/*
	EditNoContext(const EditNoContext& other) :
		CEdit(other),
		ControlToolTipHelper(other),
		m_letParentProcessUpdate(other.m_letParentProcessUpdate),
		m_readOnly(other.m_readOnly),
		m_caseStyle(other.m_caseStyle),//1 - upper; 2 - lower; 0 - none
		m_multiline(other.m_multiline),

		m_lastValidValue(other.m_lastValidValue),
		m_lastSel(other.m_lastSel),
		m_rejectingChange(other.m_rejectingChange),
		m_accumulatedWheel(other.m_accumulatedWheel),
		m_formattingRect(other.m_formattingRect),
		m_copyMenuWidth(other.m_copyMenuWidth),
		m_pasteMenuWidth(other.m_pasteMenuWidth),
		m_insertMenuWidth(other.m_insertMenuWidth),
		m_clearMenuWidth(other.m_clearMenuWidth)
	{}
	EditNoContext& operator=(const EditNoContext& other)
	{
		CEdit::operator=(other);
		ControlToolTipHelper::operator=(other);
		m_letParentProcessUpdate = other.m_letParentProcessUpdate;
		m_readOnly = other.m_readOnly;
		m_caseStyle = other.m_caseStyle;//1 - upper; 2 - lower; 0 - none
		m_multiline = other.m_multiline;

		m_lastValidValue = other.m_lastValidValue;
		m_lastSel = other.m_lastSel;
		m_rejectingChange = other.m_rejectingChange;
		m_accumulatedWheel = other.m_accumulatedWheel;
		m_formattingRect = other.m_formattingRect;
		m_copyMenuWidth = other.m_copyMenuWidth;
		m_pasteMenuWidth = other.m_pasteMenuWidth;
		m_insertMenuWidth = other.m_insertMenuWidth;
		m_clearMenuWidth = other.m_clearMenuWidth;
		return *this;
	}
*/
//	virtual unsigned int GetCtrlId() const override{return m_hWnd ? ::GetDlgCtrlID(m_hWnd) : 0;}
	const CRect& GetFormattingRect() const{return m_formattingRect;}
	inline void InvalidateRectIfValid(const RECT* rect) const{if(m_hWnd)::InvalidateRect(m_hWnd, rect, FALSE);}
	inline void InvalidateRectIfValidWithErase(const RECT* rect) const{if(m_hWnd)::InvalidateRect(m_hWnd, rect, TRUE);}

	void UpdateToolTipToContentsIfDoesNotFit(CString& text, const char* firstLine = nullptr, const char* lastLine = nullptr);

	void SetTextAsUInt64(const unsigned __int64 text);
	void SetTextAsUInt(const unsigned int text);
	void SendMessageToParent(const UINT& message, const WPARAM& w, const LPARAM& l) const
	{
		if(m_hWnd)
		{
			HWND parentWnd = ::GetParent(m_hWnd);
			if(parentWnd)
			{
				::SendMessage(parentWnd, message, w, l);
			}
		}
	}
	void ReverseValue();
	bool TryUpdate();
	virtual bool isTextValid(const char* cursor) const{return true;}
	virtual bool isValidChar(char c) const{return true;}
	virtual bool isValidFirstChar(char c) const{return true;}

	const bool& isReadOnly() const{return m_readOnly;}
	const unsigned char& GetCaseStyle() const{return m_caseStyle;}//1 - upper; 2 - lower; 0 - none
	const bool& isMultiline() const{return m_multiline;}
	void SendNotificationToParent(unsigned short notification, bool post) const;
	const bool& isLetParentProcessUpdate() const{return m_letParentProcessUpdate;}
	void SetLetParentProcessUpdate(const bool& let){m_letParentProcessUpdate = let;}
protected:
	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	void Set2LineToolTip(const char* firstLine, const char* lastLine);
	void Set3LineToolTip(const char* firstLine, const char* middleLine, const char* lastLine);
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnTextUpdate();
	afx_msg BOOL OnEnChange();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnterMenuLoop(BOOL bIsTrackPopupMenu);
	afx_msg void OnExitMenuLoop(BOOL bIsTrackPopupMenu);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy)
	{
		CEdit::OnSize(nType, cx, cy);
		SizeToolTip();
		GetRect(&m_formattingRect);
	}
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnSetReadOnly(WPARAM w, LPARAM l);
	afx_msg LRESULT OnSetText(WPARAM w, LPARAM l);
	virtual void PreSubclassWindow() override;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	
	virtual void AddMenuItems(CMenu& menu);
	void DisplayClientMenu(UINT nFlags, CPoint point);

	virtual void MeasurAdditionalMenuItems(HDC hdc, CRect& rect){}

	virtual BOOL PreTranslateMessage(MSG* pMsg) override
	{
		ControlToolTipHelper::PreTranslateMessage(pMsg);
		return CEdit::PreTranslateMessage(pMsg);
	}

	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override
	{
		return ProcessShowToolTip(lParam, pResult) || CEdit::OnNotify(wParam, lParam, pResult);
	}

	virtual bool TextChanged(){return false;}

//	virtual void BeforeDestroy() override{ControlToolTipHelper::BeforeDestroy();}
	virtual void Wheel(short steps, UINT nFlags, CPoint pt){}

	void DoReverseValue();

	bool m_letParentProcessUpdate;
	bool m_readOnly;
	unsigned char m_caseStyle;//1 - upper; 2 - lower; 0 - none
	bool m_multiline;

	CString m_lastValidValue;
	unsigned int m_lastSel;
	bool m_rejectingChange;
/*
	bool SetMouseInside(const bool& mouseInside)
	{
		if(mouseInside != m_mouseInside)
		{
			m_mouseInside = mouseInside;
			m_accumulatedWheel = 0;
			SendMessageToParent(mouseInside ? WM_USER + 16 : WM_USER + 36, GetDlgCtrlID(), (LPARAM)m_hWnd);//this);
			return true;
		}
		return false;
	}
*/
	virtual void MouseEntered() override
	{
		m_accumulatedWheel = 0;
		SendMessageToParent(WM_USER + 16, m_ctrlId, (LPARAM)m_hWnd);//this);
	}
	virtual void MouseLeft() override
	{
		m_accumulatedWheel = 0;
//		SendMessageToParent(WM_USER + 36, GetDlgCtrlID(), (LPARAM)m_hWnd);//this);
		SendMessageToParent(WM_USER + 36, m_ctrlId, (LPARAM)m_hWnd);//this);
	}

//	bool m_mouseInside;
	short m_accumulatedWheel;

	CRect m_formattingRect;

	int m_copyMenuWidth;
	int m_pasteMenuWidth;
	int m_insertMenuWidth;
	int m_clearMenuWidth;
private:
	EditNoContext(const EditNoContext& other);
	EditNoContext& operator=(const EditNoContext& other);
};

class UGUI_API EditFile : public EditNoContext
{
public:
	EditFile(const char* const& fileExtension,
		const char* const& filterString,
		const char* const& fileDialogCaption,
		const char* const& initialFilePath = nullptr,
		const bool& viewInNotepadMenuItem = false,
		const bool& readOnly = false,
		const char* const& tooltipText = nullptr,
		const bool& letParentProcessUpdate = false,
		CToolTipCtrl* externalToolTip = nullptr):
		EditNoContext(readOnly, tooltipText, letParentProcessUpdate, externalToolTip),
		m_fileExtension(fileExtension),
		m_filterString(filterString),
		m_fileDialogCaption(fileDialogCaption),
		m_initialFilePath(initialFilePath ? initialFilePath : ""),
		m_browseMenuWidth(0),
		m_viewInNotepadMenuWidth(0),
		m_viewInNotepadMenuItem(viewInNotepadMenuItem)
	{}
	const std::string& GetControlFilePath() const{return m_controlFilePath;}
	const std::string& GetFileExtension() const{return m_fileExtension;}
	const std::string& GetFilterString() const{return m_filterString;}
	void Browse();
	const bool& hasViewInNotepadMenuItem() const{return m_viewInNotepadMenuItem;}
protected:
	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	virtual void AddMenuItems(CMenu& menu);
	virtual void BeforeDestroy() override;
	virtual bool TextChanged() override;
	virtual bool FilePathChanged(){return false;}
	virtual void MeasurAdditionalMenuItems(HDC hdc, CRect& rect) override;
	std::string m_fileExtension;
	std::string m_filterString;
	std::string m_fileDialogCaption;
	std::string m_initialFilePath;
	std::string m_controlFilePath;
	int m_browseMenuWidth;
	int m_viewInNotepadMenuWidth;
	bool m_viewInNotepadMenuItem;
};

//http://www.codeguru.com/cpp/controls/editctrl/maskededitcontrols/article.php/c3915/Creating-a-Numeric-Edit-Box.htm
class UGUI_API ValidEdit : public EditNoContext
{
public:
#if(_MSC_VER > 1600)
	typedef std::unordered_set<char> CharSet;
#else
	typedef std::hash_set<char> CharSet;
#endif
	ValidEdit(const char* const& charSet, const bool& exclude, const bool& firstCharDifferent = false, const char* const& firstCharSet = nullptr, const bool& firstCharExclude = true, const bool& readOnly = false, const char* const& tooltipText = nullptr, const bool& letParentProcessUpdate = false, CToolTipCtrl* externalToolTip = nullptr):
		EditNoContext(readOnly, tooltipText, letParentProcessUpdate, externalToolTip),
		m_itBegin(m_charSet.begin()),
		m_itEnd(m_charSet.end()),
		m_itFirstCharBegin(m_firstCharSet.begin()),
		m_itFirstCharEnd(m_firstCharSet.end()),
		m_exclude(exclude),
		m_firstCharDifferent(firstCharDifferent),
		m_firstCharExclude(firstCharExclude)
	{
		if(charSet)
		{
			for(const char* cursor = charSet; *cursor; ++cursor)
			{
				m_charSet.insert(*cursor);
			}
		}
		UpdateIterators();
		if(firstCharSet)
		{
			for(const char* cursor = firstCharSet; *cursor; ++cursor)
			{
				m_firstCharSet.insert(*cursor);
			}
		}
		UpdateFirstCharIterators();
	}
/*
	ValidEdit(const ValidEdit& other):
		EditNoContext(other),
		m_charSet(other.m_charSet),
		m_firstCharSet(other.m_firstCharSet),
		m_exclude(other.m_exclude),
		m_firstCharDifferent(other.m_firstCharDifferent),
		m_firstCharExclude(other.m_firstCharExclude)
	{
		UpdateIterators();
		UpdateFirstCharIterators();
	}
	ValidEdit& operator=(const ValidEdit& other)
	{
		EditNoContext::operator==(other);
		m_charSet = other.m_charSet;
		m_firstCharSet = other.m_firstCharSet;
		m_exclude = other.m_exclude;
		m_firstCharDifferent = other.m_firstCharDifferent;
		m_firstCharExclude = other.m_firstCharExclude;
		UpdateIterators();
		UpdateFirstCharIterators();
		return *this;
	}
*/
	inline char AdjustChar(const char& c) const
	{
		switch(m_caseStyle)
		{
			case ECS_UPPER:
			return toupper(c);

			case ECS_LOWER:
			return tolower(c);
			break;

			default:
			return c;
		}
	}
	virtual bool isValidChar(char c) const override{return (m_charSet.find(AdjustChar(c)) == m_itEnd) == m_exclude;}
	virtual bool isValidFirstChar(char c) const override{return (m_firstCharSet.find(AdjustChar(c)) == m_itFirstCharEnd) == m_firstCharExclude;}
	virtual bool isTextValid(const char* cursor) const override
	{
		if(*cursor)
		{
			if(m_firstCharDifferent)
			{
				if(!isValidFirstChar(*cursor))
				{
					return false;
				}
				++cursor;
			}
			for(; *cursor; ++cursor)
			{
				if(!isValidChar(*cursor))
				{
					return false;
				}
			}
		}
		return true;
	}
	void SetValid(const char* cursor, bool exclude)
	{
		m_exclude = exclude;
		m_charSet.clear();
		if(cursor)
		{
			for(; *cursor; ++cursor)
			{
				m_charSet.insert(*cursor);
			}
		}
		UpdateIterators();
	}
	void AddValidChar(char v, bool exclude)
	{
		if(m_exclude == exclude)
		{
			m_charSet.insert(v);
		}
		else
		{
			m_charSet.erase(v);
		}
		UpdateIterators();
	}
	void AddValidChars(const char* cursor, bool exclude)
	{
		if(m_exclude == exclude)
		{
			for(; *cursor; ++cursor)
			{
				m_charSet.insert(*cursor);
			}
		}
		else
		{
			for(; *cursor; ++cursor)
			{
				m_charSet.erase(*cursor);
			}
		}
		UpdateIterators();
	}

	void SetFirstCharValid(bool firstCharDifferent, const char* cursor, bool exclude)
	{
		m_firstCharDifferent = firstCharDifferent;
		m_firstCharExclude = exclude;
		m_firstCharSet.clear();
		if(cursor)
		{
			for(; *cursor; ++cursor)
			{
				m_firstCharSet.insert(*cursor);
			}
		}
		UpdateFirstCharIterators();
	}
	void AddValidFirstChar(char v, bool exclude)
	{
		if(m_firstCharExclude == exclude)
		{
			m_firstCharSet.insert(v);
		}
		else
		{
			m_firstCharSet.erase(v);
		}
		UpdateFirstCharIterators();
	}
	void AddValidFirstChars(const char* cursor, bool exclude)
	{
		if(m_firstCharExclude == exclude)
		{
			for(; *cursor; ++cursor)
			{
				m_firstCharSet.insert(*cursor);
			}
		}
		else
		{
			for(; *cursor; ++cursor)
			{
				m_firstCharSet.erase(*cursor);
			}
		}
		UpdateFirstCharIterators();
	}
//	virtual bool TryUpdate() override;
protected:
	void UpdateIterators()
	{
		m_itBegin = m_charSet.begin();
//		m_itEnd = m_charSet.end();
	}
	void UpdateFirstCharIterators()
	{
		m_itFirstCharBegin = m_firstCharSet.begin();
//		m_itFirstCharEnd = m_firstCharSet.end();
	}
//	afx_msg void OnUpdate();

//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
//	DECLARE_MESSAGE_MAP()

	CharSet m_charSet;
	CharSet::iterator m_itBegin;
	CharSet::iterator m_itEnd;

	bool m_exclude;
	
	bool m_firstCharDifferent;
	CharSet m_firstCharSet;
	CharSet::iterator m_itFirstCharBegin;
	CharSet::iterator m_itFirstCharEnd;
	bool m_firstCharExclude;
private:
	ValidEdit(const ValidEdit& other);
	ValidEdit& operator=(const ValidEdit& other);
};

class UGUI_API EditSelection : public ValidEdit
{
public:
	typedef std::vector<std::string> StringVector;
	EditSelection(const StringVector& menuVector, const char* menuTemplate, const char* const& charSet, const bool& exclude, const bool& firstCharDifferent = false, const char* const& firstCharSet = nullptr, const bool& firstCharExclude = true, const bool& readOnly = false, const char* const& tooltipText = nullptr, CToolTipCtrl* externalToolTip = nullptr):
//		ValidEdit(const char* const& charSet, const bool& exclude, const bool& firstCharDifferent = false, const char* const& firstCharSet = nullptr, const bool& firstCharExclude = true, const bool& readOnly = false, const char* const& tooltipText = nullptr, const bool& letParentProcessUpdate = false, CToolTipCtrl* externalToolTip = nullptr) :
		ValidEdit(charSet, exclude, firstCharDifferent, firstCharSet, firstCharExclude, readOnly, tooltipText, false, externalToolTip),
		m_menuVector(menuVector),
		m_selectionMenuWidth(0)
	{
		if(menuTemplate && *menuTemplate)m_menuTemplate = menuTemplate;
	}
	bool SetMenuTemplate(const char* menuTemplate)
	{
		bool ret = false;
		if(menuTemplate && *menuTemplate)
		{
			if(strcmp(m_menuTemplate.c_str(), menuTemplate))
			{
				m_menuTemplate = menuTemplate;
				ret = true;
			}
		}
		else if(!m_menuTemplate.empty())
		{
			m_menuTemplate.clear();
			ret = true;
		}
		if(ret)
		{
			UpdateSelectionMenuWidth();
		}
		return ret;
	}
protected:
	void UpdateSelectionMenuWidth();

	const StringVector& m_menuVector;
	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void AddMenuItems(CMenu& menu) override;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
//	void ReplaceText(const char* insertion);
	virtual void PreSubclassWindow() override;
	std::string m_menuTemplate;
	int m_selectionMenuWidth;
};


class UGUI_API ValidStockEdit : public ValidEdit
{
public:
	ValidStockEdit(const char* const& tooltipText = nullptr, CToolTipCtrl* externalToolTip = nullptr):
		ValidEdit(U_GetValidStockChars(), false, false, nullptr, true, false, tooltipText, false, externalToolTip)
	{}
	virtual bool isTextValid(const char* cursor) const override
	{
		if(*cursor)
		{
			if(*cursor < 'A' || *cursor > 'Z')
			{
				return false;
			}
			return ValidEdit::isTextValid(cursor + 1);
		}
		return true;
	}
};

class UGUI_API IPAddrCtrlToolTip : public CIPAddressCtrl, public ControlToolTipHelper
{
friend class EditIpToken;
public:
	IPAddrCtrlToolTip(const char* const& tooltipText = nullptr, CToolTipCtrl* externalToolTip = nullptr);// : ControlToolTipHelper(this, tooltipText){}
	virtual ~IPAddrCtrlToolTip(){}
//	virtual unsigned int GetCtrlId() const override{return m_hWnd ? ::GetDlgCtrlID(m_hWnd) : 0;}
	EditIpToken* GetCurrentEditIpToken(const unsigned char& ordinal){return ordinal < 4 ? m_ipEdit[ordinal] : nullptr;}
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override
	{
		return ProcessShowToolTip(lParam, pResult) || CIPAddressCtrl::OnNotify(wParam, lParam, pResult);
	}
	virtual BOOL PreTranslateMessage(MSG* pMsg) override
	{
		ControlToolTipHelper::PreTranslateMessage(pMsg);
		return CIPAddressCtrl::PreTranslateMessage(pMsg);
	}
	virtual void PreSubclassWindow() override;
/*
	{
		CIPAddressCtrl::PreSubclassWindow();
		Initialize();
	}
*/
	virtual void BeforeDestroy() override;
	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	afx_msg void OnSize(UINT nType, int cx, int cy)
	{
		CIPAddressCtrl::OnSize(nType, cx, cy);
		SizeToolTip();
	}
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		const int ret = CIPAddressCtrl::OnCreate(lpCreateStruct);
		if(ret != -1 && !m_ctrlId)Initialize();
		return ret;
	}
	afx_msg void OnDestroy()
	{
		BeforeDestroy();
//		DestroyToolTip();
		m_copyMenuWidth = m_pasteMenuWidth = m_clearMenuWidth = 0;
		CIPAddressCtrl::OnDestroy();
	}
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnEnterMenuLoop(BOOL bIsTrackPopupMenu);
	afx_msg void OnExitMenuLoop(BOOL bIsTrackPopupMenu);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void DisplayClientMenu(UINT nFlags, CPoint point);

	bool m_topRectsEmpty;
	bool m_bottomRectsEmpty;
	EditIpToken* m_ipEdit[4];
	CRect m_dotRect[3];
	CRect m_gapRect[5];
	CRect m_topRect[4];
	CRect m_bottomRect[4];
	CRect m_clientRect;

	int m_copyMenuWidth;
	int m_pasteMenuWidth;
	int m_clearMenuWidth;
};

//http://computer-programming-forum.com/82-mfc/1e7bb97adfaa2400.htm
//http://www.codeguru.com/forum/showthread.php?t=158774
class UGUI_API ColorIPAddrCtrl : public IPAddrCtrlToolTip
{
public:
	ColorIPAddrCtrl(COLORREF bkColor = 0xFFFFFFFF, COLORREF textColor = 0xFFFFFFFF, const char* const& tooltipText = nullptr, CToolTipCtrl* externalToolTip = nullptr);
	virtual ~ColorIPAddrCtrl();
	bool SetBkColor(const COLORREF& bkColor);
	bool SetTextColor(const COLORREF& textColor);
	COLORREF GetBkColor() const{return m_bkColor;}
	CBrush* GetBkBrush() const{return m_brush;}//Can be nullptr
	COLORREF GetTextColor() const{return m_textColor;}
protected:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnable(BOOL bEnable);
//	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
	virtual void BeforeDestroy() override;
//	virtual void PreSubclassWindow();

	COLORREF m_bkColor;
	COLORREF m_textColor;
	COLORREF m_realBkColor;
	COLORREF m_realTextColor;
	CBrush* m_brush;
	bool m_enabled;
};

class UGUI_API DateTimeCtrlToolTip : public CDateTimeCtrl, public ControlToolTipHelper
{
public:
	DateTimeCtrlToolTip(const unsigned short& idleCode, const char* const& tooltipText = nullptr, CToolTipCtrl* externalToolTip = nullptr):
		ControlToolTipHelper(this, tooltipText, externalToolTip),
		m_idleCode(idleCode)
	{}
	const unsigned short& GetIdleCode() const{return m_idleCode;}
//	virtual unsigned int GetCtrlId() const override{return m_hWnd ? ::GetDlgCtrlID(m_hWnd) : 0;}
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override
	{
		return ProcessShowToolTip(lParam, pResult) || CDateTimeCtrl::OnNotify(wParam, lParam, pResult);
	}
	virtual BOOL PreTranslateMessage(MSG* pMsg) override
	{
		ControlToolTipHelper::PreTranslateMessage(pMsg);
		return CDateTimeCtrl::PreTranslateMessage(pMsg);
	}
	virtual void PreSubclassWindow() override;
	afx_msg void OnSize(UINT nType, int cx, int cy)
	{
		CDateTimeCtrl::OnSize(nType, cx, cy);
		SizeToolTip();
	}
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		const int ret = CDateTimeCtrl::OnCreate(lpCreateStruct);
		if(ret != -1 && !m_ctrlId)Initialize();
		return ret;
	}
	afx_msg void OnDestroy()
	{
		BeforeDestroy();
//		DestroyToolTip();
	}
	afx_msg BOOL OnDropdown(NMHDR* pNotifyStruct, LRESULT* result); 
	afx_msg BOOL OnCloseup(NMHDR* pNotifyStruct, LRESULT* result); 
	DECLARE_MESSAGE_MAP()
	unsigned short m_idleCode;
};

//http://forums.codeguru.com/showthread.php?148381-CDateTimeCtrl-background-color
class UGUI_API ColorDateTimeCtrl : public DateTimeCtrlToolTip
{
public:
	ColorDateTimeCtrl(unsigned short idleCode, COLORREF bkColor, const char* tooltipText = nullptr, CToolTipCtrl* externalToolTip = nullptr);// = 0xFFFFFFFF);//, COLORREF textColor = 0xFFFFFFFF);
	bool SetBkColor(const COLORREF bkColor);
//	bool SetTextColor(COLORREF textColor);
	const COLORREF& GetBkColor() const{return m_bkColor;}
//	COLORREF GetTextColor() const{return m_textColor;}
protected:
	DECLARE_MESSAGE_MAP()
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	COLORREF m_bkColor;
//	COLORREF m_textColor;
	CBrush* m_brush;
};

class UGUI_API ButtonToolTip : public CButton, public ControlToolTipHelper
{
public:
	ButtonToolTip(const char* const& tooltipText = nullptr, const bool& notifyPress = false, CToolTipCtrl* externalToolTip = nullptr):
		ControlToolTipHelper(this, tooltipText, externalToolTip),
		m_notifyPress(notifyPress),
		m_leftButtonPressed(false),
		m_doubleClicked(false)
	{}
	inline void InvalidateRectIfValid(const RECT* rect) const{if(m_hWnd)::InvalidateRect(m_hWnd, rect, FALSE);}
//	virtual unsigned int GetCtrlId() const override{return m_hWnd ? ::GetDlgCtrlID(m_hWnd) : 0;}
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
	virtual BOOL PreTranslateMessage(MSG* pMsg) override;
	virtual void ButtonCreated(){}
	virtual void PreSubclassWindow() override
	{
//		m_mouseInside = false;
		m_leftButtonPressed = false;
		m_doubleClicked = false;
		CButton::PreSubclassWindow();
		Initialize();//tooltip
		ButtonCreated();
	}
/*
	virtual void BeforeDestroy()
	{
		ControlToolTipHelper::BeforeDestroy();
	}
*/
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		const int ret = CButton::OnCreate(lpCreateStruct);
		if(ret != -1 && !m_ctrlId)Initialize();
		return ret;
	}
	afx_msg void OnDestroy()
	{
		BeforeDestroy();
//		DestroyToolTip();
//		m_mouseInside = false;
		m_leftButtonPressed = false;
		m_doubleClicked = false;
	}
	DECLARE_MESSAGE_MAP()

	bool m_notifyPress;
	bool m_leftButtonPressed;
	bool m_doubleClicked;
};

//http://www.codeproject.com/kb/miscctrl/subclassdemo.aspx
class UGUI_API ButtonOwnerDraw : public ButtonToolTip
{
public:
	virtual COLORREF GetForegroundColor() const{return 0;}
	const COLORREF& GetBackgroundColor() const{return m_bkColor;}
	bool SetBackgroundColor(const COLORREF& color)
	{
		if(m_bkColor != color)
		{
			m_bkColor = color;
			CalculateBkShades();
			BackgroundColorSet();
			InvalidateRectIfValid(nullptr);
//			if(m_hWnd)::InvalidateRect(m_hWnd, nullptr, FALSE);
			return true;
		}
		return false;
	}
	void SetColorShadePercent(const unsigned int& percent)
	{
		if(percent != m_colorShadePercent)
		{
			m_colorShadePercent = percent;
			CalculateBkShades();
			CalculateGrayShades();
			InvalidateRectIfValid(nullptr);
//			if(m_hWnd)::InvalidateRect(m_hWnd, nullptr, FALSE);
		}
	}
	void SetUseTextOppositeColor(const bool& useTextOppositeColor)
	{
		if(useTextOppositeColor != m_useTextOppositeColor)
		{
			m_useTextOppositeColor = useTextOppositeColor;
			InvalidateRectIfValid(nullptr);
		}
	}
	virtual void GetDrawRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawRect) const{drawRect = lpDrawItemStruct->rcItem;}
	virtual bool FocusShrinksOnPress() const{return true;}
	virtual bool CanHaveDisabledBackground() const{return true;}
protected:
	ButtonOwnerDraw(const COLORREF& bkColor = GetSysColor(COLOR_BTNFACE),
		const bool& notifyPress = false,
		const char* const& tooltipText = nullptr,
		CToolTipCtrl* const& externalToolTip = nullptr,
		const bool& useTextOppositeColor = true):
		ButtonToolTip(tooltipText, notifyPress, externalToolTip),
		m_bkColor(bkColor),
		m_grayColor(GetSysColor(COLOR_BTNFACE)),
		m_colorShadePercent(50),
		m_bkOppositeColor(0xFFFFFFFF),
		m_useTextOppositeColor(useTextOppositeColor)
	{
		CalculateBkShades();
		CalculateGrayShades();
	}
//	virtual void PreSubclassWindow();
	virtual void ButtonCreated() override;
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
	virtual void PaintBackground(const DRAWITEMSTRUCT* lpDrawItemStruct, COLORREF bkColor);
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& faceRect){}
	virtual void DrawBorder(const DRAWITEMSTRUCT* lpDrawItemStruct, COLORREF bkColorLight, COLORREF bkColorDark){}
	virtual void BackgroundColorSet(){}
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
	void DrawFocus(LPDRAWITEMSTRUCT lpDrawItemStruct, CRect& rect);
	void CalculateBkShades()
	{
		if(0xFFFFFFFF == m_bkColor)
		{
			m_bkColorLight = RGB(255, 255, 255);
			m_bkColorDark = 0;
		}
		else
		{
			m_bkColorLight = UGUI_CalculateLightColor(m_bkColor, m_colorShadePercent);
			m_bkColorDark = UGUI_CalculateDarkColor(m_bkColor, m_colorShadePercent);
		}
	}
	void CalculateGrayShades()
	{
		if(0xFFFFFFFF == m_grayColor)
		{
			m_grayColorLight = RGB(255, 255, 255);
			m_grayColorDark = 0;
		}
		else
		{
			m_grayColorLight = UGUI_CalculateLightColor(m_grayColor, m_colorShadePercent);
			m_grayColorDark = UGUI_CalculateDarkColor(m_grayColor, m_colorShadePercent);
		}
	}
	COLORREF m_bkColor;
	COLORREF m_bkColorLight;
	COLORREF m_bkColorDark;
	COLORREF m_grayColor;
	COLORREF m_grayColorLight;
	COLORREF m_grayColorDark;
	unsigned int m_colorShadePercent;
	COLORREF m_bkOppositeColor;
	bool m_useTextOppositeColor;
};

class UGUI_API ButtonTextBase : public ButtonOwnerDraw
{
public:
	virtual COLORREF GetForegroundColor() const override{return m_textColor;}
	bool SetForegroundColor(const COLORREF& color)
	{
		if(color != m_textColor)
		{
			m_textColor = color;
			ForegroundColorSet();
			InvalidateRectIfValid(nullptr);
//			if(m_hWnd)::InvalidateRect(m_hWnd, nullptr, FALSE);
			return true;
		}
		return false;
	}
	void SetGrayTextColor(const COLORREF& color)
	{
		if(color != m_grayTextColor)
		{
			m_grayTextColor = color;
			GrayTextColorSet();
			if(m_invalid)InvalidateRectIfValid(nullptr);
//			if(m_invalid && m_hWnd)::InvalidateRect(m_hWnd, nullptr, FALSE);
		}
	}
	const bool& isInvalid() const{return m_invalid;}
	void SetInvalid(const bool& invalid, const bool& updateTextColor = true)
	{
		if(invalid != m_invalid)
		{
			m_invalid = invalid;

			if(m_hWnd)::InvalidateRect(m_hWnd, nullptr, FALSE);
			else m_initialInvalid = invalid;

//			if(updateTextColor && UpdateBWTextColor())
//			InvalidateRectIfValid(nullptr);
		}
	}
	void SetText(const char* text);
	const std::string& GetText() const{return m_text;}
/*
	virtual bool SetBackgroundColor(COLORREF color) override
	{
		if(ButtonOwnerDraw::SetBackgroundColor(color))
		{
			if(m_arrow)
			{
				CalculateArrowColor();
			}
			return true;
		}
		return false;
	}
*/
	bool SetBackgroundColorAndBWTextColor(const COLORREF& color)
	{
		if(SetBackgroundColor(color))
		{
			UpdateBWTextColor();
			return true;
		}
		return false;
	}
protected:
	ButtonTextBase(const COLORREF& bkColor = GetSysColor(COLOR_BTNFACE),
		const COLORREF& textColor = 0xFFFFFFFF,
		const bool& invalid = false,
		const char* const& text = nullptr,
		const bool& notifyPress = false,
		const char* const& tooltipText = nullptr,
		CToolTipCtrl* const& externalToolTip = nullptr,
		const bool& useTextOppositeColor = true,
		const COLORREF& grayTextColor = 0xFFFFFFFF):
		ButtonOwnerDraw(bkColor, notifyPress, tooltipText, externalToolTip, useTextOppositeColor),
		m_text(text ? text : ""),
		m_textColor(textColor),
		m_grayTextColor(grayTextColor == 0xFFFFFFFF ? GetSysColor(COLOR_GRAYTEXT) : grayTextColor),
		m_invalid(invalid),
		m_initialInvalid(invalid)
	{
	}
	virtual void ForegroundColorSet(){}
	virtual void GrayTextColorSet(){}
	virtual void BackgroundColorSet() override
	{
		UpdateBWTextColor();
	}

//	virtual bool UpdateBWTextColor(){return true;}
	virtual bool UpdateBWTextColor()
	{
		COLORREF textColor = UGUI_GetOppositeColor(m_bkColor);

//		if(m_invalid)
//		textColor = UGUI_GetMiddleColor(m_bkColor, textColor);

		return SetForegroundColor(textColor);
/*
		if(textColor != m_textColor)
		{
			m_textColor = textColor;
			if(m_arrow)
			{
				CalculateArrowColor();
			}
			return true;
		}
		return false;
*/
	}
	virtual void ButtonCreated() override;
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& faceRect) override;
	virtual void DoDrawText(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& faceRect){}

	afx_msg LRESULT OnSetText(WPARAM w, LPARAM l);
	DECLARE_MESSAGE_MAP()

	std::string m_text;
	COLORREF m_textColor;
	COLORREF m_grayTextColor;
	bool m_invalid;
	bool m_initialInvalid;
};

class UGUI_API ButtonText : public ButtonTextBase
{
public:
	ButtonText(const COLORREF& bkColor = GetSysColor(COLOR_BTNFACE),
		const COLORREF& textColor = 0xFFFFFFFF,
		const bool& invalid = false,
		const bool& arrow = false,
		const char* const& text = nullptr,
		const bool& notifyPress = false,
		const char* const& tooltipText = nullptr,
		CToolTipCtrl* const& externalToolTip = nullptr,
		const bool& useTextOppositeColor = true,
		const COLORREF& grayTextColor = 0xFFFFFFFF):
		ButtonTextBase(bkColor, textColor, invalid, text, notifyPress, tooltipText, externalToolTip, useTextOppositeColor, grayTextColor),
		m_arrowColor(0),
		m_arrow(arrow)
	{
		if(textColor == 0xFFFFFFFF)UpdateBWTextColor();
		else if(m_arrow)CalculateArrowColor();
	}
	virtual void GetDrawRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawRect) const override
	{
		drawRect = lpDrawItemStruct->rcItem;
		drawRect.DeflateRect(CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));
	}
	void SetArrow(const bool& arrow)
	{
		if(arrow != m_arrow)
		{
			m_arrow = arrow;
			if(m_arrow)CalculateArrowColor();
			InvalidateRectIfValid(nullptr);
//			if(m_hWnd)::InvalidateRect(m_hWnd, nullptr, FALSE);
		}
	}
protected:
	virtual void DrawBorder(const DRAWITEMSTRUCT* lpDrawItemStruct, COLORREF bkColorLight, COLORREF bkColorDark) override;
	virtual void ForegroundColorSet() override{if(m_arrow)CalculateArrowColor();}
	virtual void GrayTextColorSet() override{if(m_arrow)CalculateArrowColor();}
	virtual void BackgroundColorSet() override{if(m_arrow)CalculateArrowColor();}

	void CalculateArrowColor();
	virtual void DoDrawText(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& faceRect) override;
	COLORREF m_arrowColor;
	bool m_arrow;
};

class UGUI_API CheckBoxOwnerDraw : public ButtonTextBase
{
public:
	CheckBoxOwnerDraw(const char* const& tooltipText = nullptr,
		const COLORREF& bkColor = 0xFFFFFFFF,//GetSysColor(COLOR_BTNFACE),
		const COLORREF& textColor = 0xFFFFFFFF,
		const COLORREF& boxColor = GetSysColor(COLOR_WINDOW),//0xFFFFFFFF,
		const COLORREF& checkedTextColor = 0xFFFFFFFF,
		const COLORREF& pressedBkColor = 0xFFFFFFFF,
		const int& boxDeflation = 2,
		const int& textOffset = 0,
		const bool& invalid = false,
//		const bool& arrow = false,
		const char* const& text = nullptr,
		const bool& notifyPress = false,
		CToolTipCtrl* externalToolTip = nullptr,
		const bool& useTextOppositeColor = false,
		const COLORREF& grayTextColor = 0xFFFFFFFF):
		ButtonTextBase(bkColor, textColor, invalid, text, notifyPress, tooltipText, externalToolTip, useTextOppositeColor, grayTextColor),
		m_checkAreaRect(0, 0, 0, 0),
		m_checkRect(m_checkAreaRect),
		m_textRect(0, 0, 0, 0),
		m_checkedTextColor(checkedTextColor),
		m_pressedBkColor(pressedBkColor),
		m_boxColor(boxColor),
		m_borderColor(0),
		m_boxDeflation(boxDeflation),
		m_textOffset(textOffset),
//		m_radioStyle(false),
		m_checked(false),
		m_leftText(false)
	{
//		if(m_bkColor == 0xFFFFFFFF)m_bkColor = GetSysColor(COLOR_BTNFACE);
		if(0xFFFFFFFF == textColor && 0xFFFFFFFF != m_bkColor)UpdateBWTextColor();
		if(0xFFFFFFFF == m_boxColor)m_boxColor = GetSysColor(COLOR_WINDOW);
		UpdateBorderColor();
	}
	const bool& isChecked() const{return m_checked;}
	virtual void GetDrawRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawRect) const override;
	const COLORREF& GetCheckedTextColor() const{return m_checkedTextColor;}
	const COLORREF& GetBoxColor() const{return m_boxColor;}
	void SetCheckedTextColor(const COLORREF& color)
	{
		if(color != m_checkedTextColor)
		{
			m_checkedTextColor = color;
			InvalidateRectIfValid(&m_textRect);
//			if(m_hWnd)::InvalidateRect(m_hWnd, &m_textRect, FALSE);
		}
	}
	void SetPressedBkColor(const COLORREF& color)
	{
		if(color != m_pressedBkColor)
		{
			m_pressedBkColor = color;
			InvalidateRectIfValid(&m_textRect);
		}
	}
	bool UpdateBorderColor()
	{
		const COLORREF borderColor = UGUI_GetOppositeColor(m_boxColor);
		if(borderColor != m_borderColor)
		{
			m_borderColor = borderColor;
			return true;
		}
		return false;
	}

	void SetBoxColor(const COLORREF& color)
	{
		if(color != m_boxColor)
		{
			m_boxColor = color;
			UpdateBorderColor();
			InvalidateRectIfValid(&m_checkRect);
//			if(m_hWnd)::InvalidateRect(m_hWnd, &m_checkRect, FALSE);
		}
	}
	void SetBoxDeflation(const int& deflation)
	{
		if(deflation != m_boxDeflation)
		{
			m_boxDeflation = deflation;
//			UpdateCheckRect();
			UpdateRects();
			InvalidateRectIfValid(&m_checkAreaRect);
//			if(m_hWnd)::InvalidateRect(m_hWnd, &m_checkAreaRect, FALSE);
		}
	}
	void SetBoxColorAndDeflation(const COLORREF& color, const int& deflation)
	{
		SetBoxDeflation(deflation);
		SetBoxColor(color);
	}
	void SetTextOffset(int textOffset)
	{
		if(textOffset < 0 && m_boxDeflation < -textOffset)textOffset = -m_boxDeflation;
		if(textOffset != m_textOffset)
		{
			InvalidateRectIfValid(&m_textRect);
//			if(m_hWnd)::InvalidateRect(m_hWnd, &m_textRect, FALSE);
			m_textOffset = textOffset;
//			UpdateTextRect();
			UpdateRects();
			InvalidateRectIfValid(&m_textRect);
//			if(m_hWnd)::InvalidateRect(m_hWnd, &m_textRect, FALSE);
		}
	}

	int GetCheck() const{return m_checked ? BST_CHECKED : BST_UNCHECKED;}

	void SetCheck(int nCheck)
	{
		const bool checked = BST_CHECKED == nCheck;
		if(checked != m_checked)
		{
			m_checked = checked;
			CheckSet();
			InvalidateRectIfValid(m_checkedTextColor == 0xFFFFFFFF || m_textColor == m_checkedTextColor ? &m_checkAreaRect : nullptr);
//			if(m_hWnd)::InvalidateRect(m_hWnd, m_checkedTextColor == 0xFFFFFFFF || m_textColor == m_checkedTextColor ? &m_checkAreaRect : nullptr, FALSE);
		}
	}
	void ResizeToFitText(const int maxWidth, bool rightAlign = false);

	virtual bool CanChangeOnClick() const{return true;}
	virtual bool CanHaveDisabledBackground() const override{return false;}
protected:
	virtual void CheckSet(){}
	virtual void ButtonCreated() override;
	virtual void PaintBackground(const DRAWITEMSTRUCT* lpDrawItemStruct, COLORREF bkColor) override;
	virtual void DoDrawText(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& faceRect) override;
	virtual void DoDrawCheck(const DRAWITEMSTRUCT* lpDrawItemStruct);
	virtual void ReverseCheckOnMouseUp(){m_checked = !m_checked;}
//	virtual void ReverseCheckOnSetCheck(){m_checked = !m_checked;}
	virtual void HandleDoubleClick()
	{
		HWND parent = ::GetParent(m_hWnd);
		if(parent)::SendMessage(parent, WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
		::InvalidateRect(m_hWnd, nullptr, FALSE);
	}

//	afx_msg BOOL OnClicked();
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg LRESULT OnGetCheck(WPARAM w, LPARAM l);
	afx_msg LRESULT OnSetCheck(WPARAM w, LPARAM l);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	DECLARE_MESSAGE_MAP()

	void InitRects(const int& cx, const int& cy)
	{
		m_checkAreaRect.bottom = m_textRect.bottom = cy;
		if(m_leftText)
		{
			m_checkAreaRect.right = cx;
			m_checkAreaRect.left = m_checkAreaRect.right - m_checkAreaRect.bottom;
			if(m_textOffset < 0)m_checkAreaRect.left -= m_textOffset;

//			m_textRect.left = 0;
			m_textRect.right = m_checkAreaRect.left;
			if(m_textOffset > 0)m_textRect.right -= m_textOffset;

			UpdateRects();
		}
		else
		{
			m_textRect.right = cx;
		}
	}
	void UpdateCheckRect()
	{
		m_checkRect.top = m_boxDeflation;
		m_checkRect.bottom = m_checkAreaRect.bottom - m_boxDeflation;
		if(m_leftText)
		{
			m_checkRect.right = m_checkAreaRect.right;// m_controlRect.Width();
			m_checkRect.left = m_checkRect.right - (m_checkRect.bottom - m_checkRect.top);
		}
		else
		{
			m_checkRect.right = m_checkRect.bottom - m_checkRect.top;
		}
	}
	void UpdateTextRect()
	{
		if(m_leftText)
		{
			m_checkAreaRect.right = m_controlRect.Width();
			m_checkAreaRect.left = m_checkAreaRect.right - m_checkAreaRect.bottom;
			if(m_textOffset < 0)m_checkAreaRect.left -= m_textOffset;
			if(m_checkAreaRect.left < 0)m_checkAreaRect.left = 0;

//			m_textRect.left = 0;
			m_textRect.right = m_checkAreaRect.left;
//			if(m_textOffset > 0)
			if(m_textRect.right > m_textOffset)
			{
				m_textRect.right -= m_textOffset;
			}
			else
			{
				m_textRect.right = 0;
			}
		}
		else
		{
			m_checkAreaRect.right = m_checkAreaRect.bottom;
			if(m_textOffset < 0)
			{
				if(m_checkAreaRect.right > -m_textOffset)
				{
					m_checkAreaRect.right += m_textOffset;
				}
				else
				{
					m_checkAreaRect.right = 0;
				}
			}

			m_textRect.left = m_checkAreaRect.right;
//			if(m_textOffset > 0)
			if(m_textRect.left > -m_textOffset)
			{
				m_textRect.left += m_textOffset;
			}
			else
			{
				m_textRect.left = 0;
			}
		}
	}
	void UpdateRects()
	{
		UpdateCheckRect();
		UpdateTextRect();
	}

	virtual void MouseEntered() override
	{
		InvalidateRectIfValid(&m_checkRect);
//		if(m_hWnd)::InvalidateRect(m_hWnd, &m_checkRect, FALSE);
	}
	virtual void MouseLeft() override
	{
		InvalidateRectIfValid(&m_checkRect);
//		if(m_hWnd)::InvalidateRect(m_hWnd, &m_checkRect, FALSE);
	}
	virtual void BeforeDestroy()
	{
		ButtonTextBase::BeforeDestroy();
//		m_radioStyle = false;
		m_checked = false;
	}

	CRect m_checkAreaRect;
	CRect m_checkRect;
	CRect m_textRect;
	COLORREF m_checkedTextColor;
	COLORREF m_pressedBkColor;
	COLORREF m_boxColor;
	COLORREF m_borderColor;
	int m_boxDeflation;
	int m_textOffset;
//	bool m_radioStyle;
	bool m_checked;
	bool m_leftText;
};

class UGUI_API RadioGroup
{
friend class RadioOwnerDraw;
public:
	RadioGroup():
		m_radioMapEnd(m_radioMap.end()),
		m_checkedOrdinal(0xFFFFFFFF)
	{
	}
	virtual ~RadioGroup(){}
	typedef std::vector<RadioOwnerDraw*> RadioVector;
	typedef std::map<RadioOwnerDraw*, unsigned int> RadioMap;
	void UncheckAll();
	virtual bool isUncheckable() const{return false;}
	const unsigned int& GetCheckedOrdinal() const{return m_checkedOrdinal;}
protected:
	bool AddRadio(RadioOwnerDraw* radio);
	void SetChecked(RadioOwnerDraw* radio);
	void SetUnchecked(RadioOwnerDraw* radio);
	bool RemoveRadio(RadioOwnerDraw* radio);
	void SetNextChecked();
	void SetPreviousChecked();
	RadioVector m_radioVector;
	RadioMap m_radioMap;
	RadioMap::iterator m_radioMapEnd;
	unsigned int m_checkedOrdinal;
private:
	RadioGroup(const RadioGroup& other);//do not implement
	RadioGroup& operator=(const RadioGroup& other);//do not implement
};

class UGUI_API RadioGroupUncheckable : public RadioGroup
{
//friend class RadioOwnerDraw;
public:
	RadioGroupUncheckable()
	{
	}
	virtual bool isUncheckable() const{return true;}
};

class UGUI_API RadioOwnerDraw : public CheckBoxOwnerDraw
{
friend class RadioGroup;
public:
	RadioOwnerDraw(const char* const& tooltipText = nullptr,
		const COLORREF& bkColor = 0xFFFFFFFF,//GetSysColor(COLOR_BTNFACE),
		const COLORREF& textColor = 0xFFFFFFFF,
		const COLORREF& boxColor = GetSysColor(COLOR_WINDOW),//0xFFFFFFFF,
		const COLORREF& checkedTextColor = 0xFFFFFFFF,
		const COLORREF& pressedBkColor = 0xFFFFFFFF,
		const int boxDeflation = 2,
		const int textOffset = 0,
		const bool& invalid = false,
//		const bool& arrow = false,
		const char* const& text = nullptr,
		const bool& notifyPress = false,
		CToolTipCtrl* externalToolTip = nullptr,
		const bool& useTextOppositeColor = false,
		const COLORREF& grayTextColor = 0xFFFFFFFF):
		CheckBoxOwnerDraw(tooltipText,
			bkColor,
			textColor,
			boxColor,
			checkedTextColor,
			pressedBkColor,
			boxDeflation,
			textOffset,
			invalid,
			text,
			notifyPress,
			externalToolTip,
			useTextOppositeColor,
			grayTextColor),
		m_radioGroupOwner(nullptr)
	{
	}
	void SetRadioGroupOwner(RadioGroup* const& radioGroupOwner)
	{
		if(radioGroupOwner != m_radioGroupOwner)
		{
			if(m_radioGroupOwner)
			{
				m_radioGroupOwner->RemoveRadio(this);
			}
			m_radioGroupOwner = radioGroupOwner;
			if(m_radioGroupOwner)
			{
				m_radioGroupOwner->AddRadio(this);
			}
		}
	}
	virtual bool CanChangeOnClick() const override{return !m_checked;}
	virtual bool FocusShrinksOnPress() const override{return !m_checked;}

/*
	void SetCheck(int nCheck)
	{
		const bool checked = BST_CHECKED == nCheck;
		if(checked != m_checked)
		{
			m_checked = checked;
			CheckSet();
			if(m_hWnd)::InvalidateRect(m_hWnd, m_checkedTextColor == 0xFFFFFFFF || m_textColor == m_checkedTextColor ? &m_checkAreaRect : nullptr, FALSE);
		}
	}
*/
protected:
//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	DECLARE_MESSAGE_MAP()
//	virtual void DoDrawText(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& faceRect) override;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDrawCheck(const DRAWITEMSTRUCT* lpDrawItemStruct) override;
	virtual void ButtonCreated() override;
	virtual void CheckSet() override
	{
		if(m_checked)
		{
			if(m_radioGroupOwner)m_radioGroupOwner->SetChecked(this);
		}
	}
	virtual void ReverseCheckOnMouseUp() override
	{
//		if(!m_checked)
//		{
//			m_checked = true;
//			if(m_radioGroupOwner)m_radioGroupOwner->SetChecked(this);
//		}

		if(m_radioGroupOwner)
		{
			if(m_checked)
			{
				if(m_radioGroupOwner->isUncheckable())
				{
					m_checked = false;
					m_radioGroupOwner->SetUnchecked(this);
				}
			}
			else
			{
				m_checked = true;
				m_radioGroupOwner->SetChecked(this);
			}
		}
		else
		{
			m_checked = !m_checked;
		}
	}
/*
	virtual void ReverseCheckOnSetCheck()
	{
		m_checked = !m_checked;
		if(m_radioGroupOwner)m_radioGroupOwner->SetChecked(this);
	}
*/
	afx_msg UINT OnGetDlgCode();
	DECLARE_MESSAGE_MAP()

	virtual void HandleDoubleClick() override{}
	RadioGroup* m_radioGroupOwner;
};
//Key

enum KeyModifiers : unsigned char
{
	KM_SHIFT_LEFT = 1 << 0,
	KM_CTRL_LEFT = 1 << 1,
	KM_ALT_LEFT = 1 << 2,
	KM_CAPS_LOCK = 1 << 3, 
	KM_NUM_LOCK = 1 << 4, 
	KM_SHIFT_RIGHT = 1 << 5,
	KM_CTRL_RIGHT = 1 << 6,
	KM_ALT_RIGHT = 1 << 7,

	KM_LAST
};

enum KeyCategory : unsigned char
{
	KC_NONE,
	KC_SHIFT,
	KC_CTRL,
	KC_ALT,
	KC_SHIFT_CTRL,
	KC_SHIFT_ALT,
	KC_CTRL_ALT,
	KC_SHIFT_CTRL_ALT,

	KC_COUNT
};

enum KeyLockCategory : unsigned char
{
	KLC_NONE,
	KLC_CAPS,
	KLC_NUM,
	KLC_CAPS_NUM,

	KLC_COUNT
};

enum SideCategory : unsigned char
{
	SC_LEFT,
	SC_RIGHT,

	SC_COUNT
};

class UGUI_API Key
{
public:
//	Key():m_ascii(0),m_modifier(0),m_key(0){}
//	Key():m_ascii(0){}
//	Key(unsigned short key):m_ascii((unsigned char)(key >> 8)), m_modifier((unsigned char)(key & 0xFF)), m_key(key){}
	Key(const unsigned short& key = 0):m_key(key){}
//	Key(unsigned char ascii, unsigned char modifier):m_ascii(ascii),m_modifier(modifier),m_key(((unsigned short)m_ascii << 8) | (unsigned short)m_modifier){}
	Key(const unsigned char& ascii, const unsigned char& modifier):m_ascii(ascii),m_modifier(modifier){}
	Key(const unsigned char& ascii,
		const bool& leftShift,
		const bool& leftCtrl,
		const bool& leftAlt,
		const bool& rightShift,
		const bool& rightCtrl,
		const bool& rightAlt,
		const bool& capsLock,
		const bool& numLock):
		m_ascii(ascii),
		m_modifier((leftShift ? KM_SHIFT_LEFT : 0)
			| (leftCtrl ? KM_CTRL_LEFT : 0)
			| (leftAlt ? KM_ALT_LEFT : 0)
			| (rightShift ? KM_SHIFT_RIGHT : 0)
			| (rightCtrl ? KM_CTRL_RIGHT : 0)
			| (rightAlt ? KM_ALT_RIGHT : 0)
			| (capsLock ? KM_CAPS_LOCK : 0)
			| (numLock ? KM_NUM_LOCK : 0))
//		m_key(((unsigned short)m_ascii << 8) | (unsigned short)m_modifier)
	{}
	const unsigned char& GetAscii() const{return m_ascii;}
	const unsigned char& GetModifier() const{return m_modifier;}
	const unsigned short& GetKey() const{return m_key;}

	bool isModifier(unsigned short flag) const{return (m_modifier & flag) != 0;}

	bool isShiftLeft() const{return isModifier(KM_SHIFT_LEFT);}
	bool isCtrlLeft() const{return isModifier(KM_CTRL_LEFT);}
	bool isAltLeft() const{return isModifier(KM_ALT_LEFT);}
	bool isShiftRight() const{return isModifier(KM_SHIFT_RIGHT);}
	bool isCtrlRight() const{return isModifier(KM_CTRL_RIGHT);}
	bool isAltRight() const{return isModifier(KM_ALT_RIGHT);}
	bool isCapsLock() const{return isModifier(KM_CAPS_LOCK);}
	bool isNumLock() const{return isModifier(KM_NUM_LOCK);}

	bool isRight() const{return isModifier(KM_SHIFT_RIGHT | KM_CTRL_RIGHT | KM_ALT_RIGHT);}

	bool isShift() const{return isModifier(KM_SHIFT_LEFT | KM_SHIFT_RIGHT);}
	bool isCtrl() const{return isModifier(KM_CTRL_LEFT | KM_CTRL_RIGHT);}
	bool isAlt() const{return isModifier(KM_ALT_LEFT | KM_ALT_RIGHT);}

	KeyCategory GetKeyCategory() const
	{
		return isShift() && isCtrl() && isAlt() ? KC_SHIFT_CTRL_ALT:
			isShift() && isCtrl() ? KC_SHIFT_CTRL:
			isShift() && isAlt() ? KC_SHIFT_ALT:
			isCtrl() && isAlt() ? KC_CTRL_ALT:
			isShift() ? KC_SHIFT:
			isCtrl() ? KC_CTRL:
			isAlt() ? KC_ALT:
			KC_NONE;
	}

	KeyLockCategory GetKeyLockCategory() const
	{
		return isCapsLock() && isNumLock() ? KLC_CAPS_NUM :
			isCapsLock() ? KLC_CAPS :
			isNumLock() ? KLC_NUM :
			KLC_NONE;
	}

	SideCategory GetSideCategory() const
	{
		return isRight() ? SC_RIGHT : SC_LEFT;
	}

	static bool isModifierExactStatic(unsigned char modifier, unsigned char flag, unsigned char exclusiveSubset){return (modifier & flag) == flag && (modifier & exclusiveSubset) == flag;}
	static bool iShiftCtrlAltExactStatic(unsigned char modifier, unsigned char flag){return isModifierExactStatic(modifier, flag, KM_SHIFT_LEFT | KM_CTRL_LEFT | KM_ALT_LEFT | KM_SHIFT_RIGHT | KM_CTRL_RIGHT | KM_ALT_RIGHT);}
	bool isModifierExact(unsigned char flag, unsigned char exclusiveSubset = 0xFF) const{return isModifierExactStatic(m_modifier, flag, exclusiveSubset);}
	bool isShiftCtrlAltExact(unsigned char flag) const{return isModifierExact(flag, KM_SHIFT_LEFT | KM_CTRL_LEFT | KM_ALT_LEFT | KM_SHIFT_RIGHT | KM_CTRL_RIGHT | KM_ALT_RIGHT);}

//	void Nullify(){m_ascii = m_modifier = 0; m_key = 0;}
	void Nullify(){m_key = 0;}
	bool isNull() const{return !m_key;}
//	operator size_t() const{return m_key;}
	size_t GetHashValue() const{return m_key;}
	bool operator==(const Key& other) const{return m_key == other.m_key;}
	bool operator!=(const Key& other) const{return m_key != other.m_key;}
	bool operator<(const Key& other) const{return m_key < other.m_key;}
	bool operator>(const Key& other) const{return m_key > other.m_key;}
	bool operator<=(const Key& other) const{return m_key <= other.m_key;}
	bool operator>=(const Key& other) const{return m_key >= other.m_key;}

	std::string GetAsciiKeyString() const
	{
		std::string result;
		UGUI_GetAsciiKeyAsString(m_ascii, result);
		return result;
	}
	std::string toString() const
	{
		std::string result;
		UGUI_GetKeyAsString(m_ascii, m_modifier, result);
		return result;
	}
	void fromString(const char* cursor)
	{
		m_key = UGUI_GetStringAsKey(cursor);
		m_ascii = (unsigned char)(m_key >> 8);
		m_modifier = (unsigned char)(m_key & 0xFF);
	}
protected:
//	unsigned char m_ascii;
//	unsigned char m_modifier;
//	unsigned short m_key;
	union
	{
		unsigned short m_key;
		struct
		{
			unsigned char m_modifier;
			unsigned char m_ascii;
		};
	};
};

template<> inline size_t std::hash_value(const Key& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashValue();// ^ _HASH_SEED;//(((key.GetDollars() << 16) | key.GetDollarFraction()) ^ _HASH_SEED);
}

//End Key

//class LbSpinCell;
class LbSpinCellCollection;

class LbColumn : public StringName
{
public:
	LbColumn(const char* name,
		unsigned short id,
		int defaultWidth,
		unsigned int ordinal,
		unsigned int dataAlignment,
		unsigned int titleAlignment,
		unsigned int totalAlignment,
		const char* tooltip,
		COLORREF titleColor = 0xFFFFFFFF,
		COLORREF totalColor = 0xFFFFFFFF,
		int dataOffset = 0,
		int titleOffset = 0,
		int totalOffset = 0):
		StringName(name),
		m_id(id),
		m_defaultWidth(defaultWidth),
		m_ordinal(ordinal),
//		m_textWidth(0),
		m_dataAlignment(dataAlignment),
		m_titleAlignment(titleAlignment),
		m_totalAlignment(totalAlignment),
		m_dataOffset(dataOffset),
		m_titleOffset(titleOffset),
		m_totalOffset(totalOffset),
		m_titleColor(titleColor),
		m_totalColor(totalColor),
		m_tooltip(tooltip ? tooltip : name)
	{}
//	const std::string& GetNameStr() const{return m_name;}
//	const char* GetName() const{return m_name.c_str();}
//	void SetName(const char* name){m_name = name;}
//	void SetName(const std::string& name){m_name = name;}
	const std::string& GetTooltipStr() const{return m_tooltip;}
	const char* GetTooltip() const{return m_tooltip.c_str();}
	void SetTooltip(const char* tooltip){m_tooltip = tooltip;}
	void SetTooltip(const std::string& tooltip){m_tooltip = tooltip;}
	const unsigned short& GetId() const{return m_id;}
//	void SetDefaultWidth(int width){m_defaultWidth = width;}
	const int& GetDefaultWidth() const{return m_defaultWidth;}
/*
	void SetTextWidth(int width){m_textWidth = width;}
	int GetTextWidth() const{return m_textWidth;}
*/
	const COLORREF& GetTitleColor() const{return m_titleColor;}
	void SetTitleColor(COLORREF color){m_titleColor = color;}

	const COLORREF& GetTotalColor() const{return m_totalColor;}
	void SetTotalColor(COLORREF color){m_totalColor = color;}

	const unsigned int& GetOrdinal() const{return m_ordinal;}
	void SetOrdinal(unsigned int ordinal){m_ordinal = ordinal;}
	void IncrementOrdinal(){++m_ordinal;}
	void DecrementOrdinal(){--m_ordinal;}

	const unsigned int& GetDataAlignment() const{return m_dataAlignment;}
	void SetDataAlignment(unsigned int alignment){m_dataAlignment = alignment;}
	const unsigned int& GetTitleAlignment() const{return m_titleAlignment;}
	void SetTitleAlignment(unsigned int alignment){m_titleAlignment = alignment;}
	const unsigned int& GetTotalAlignment() const{return m_totalAlignment;}
	void SetTotalAlignment(unsigned int alignment){m_totalAlignment = alignment;}

	const int& GetDataOffset() const{return m_dataOffset;}
	void SetDataOffset(int offset){m_dataOffset = offset;}
	const int& GetTitleOffset() const{return m_titleOffset;}
	void SetTitleOffset(int offset){m_titleOffset = offset;}
	const int& GetTotalOffset() const{return m_totalOffset;}
	void SetTotalOffset(int offset){m_totalOffset = offset;}

	DECLARE_NED_NEW
protected:
//	std::string m_name;
	unsigned short m_id;
	int m_defaultWidth;
//	int m_textWidth;
	unsigned int m_ordinal;
	unsigned int m_dataAlignment;
	unsigned int m_titleAlignment;
	unsigned int m_totalAlignment;
	int m_dataOffset;
	int m_titleOffset;
	int m_totalOffset;
	COLORREF m_titleColor;
	COLORREF m_totalColor;
	std::string m_tooltip;
};

//class ListBoxOwnerDraw;

class UGUI_API LbHorizontalScroller
{
friend class ListBoxOwnerDraw;
public:
	virtual ~LbHorizontalScroller(){DestroyColumns();}

	typedef std::map<PointLocatorInt, LbColumn*, lessPointLocator<PointLocatorInt::ValueType> > ColumnMap;
	typedef ColumnMap::iterator ColumnIterator;
	typedef ColumnMap::const_iterator ColumnConstIterator;
	typedef std::vector<ColumnIterator> ColumnIteratorVector;

	const unsigned short& GetColumnCount() const{return m_columnCount;}
	const unsigned short& GetTotalColumnCount() const{return m_totalColumnCount;}
	const int& GetColumnLeftOffset() const{return m_columnLeftOffset;}
	const int& GetColumnScrollOffset() const{return m_columnScrollOffset;}
	unsigned short GetColumnVectorCount() const{return (unsigned short)m_columnVector.size();}
	int GetTotalColumnWidth() const{return m_columnLast == m_columnEnd ? 0 : m_columnLast->first.GetEnd();}
	ColumnIterator FindColumn(int x){return m_columnMap.find(PointLocatorInt(x));}
	ColumnConstIterator FindColumn(int x) const{return m_columnMap.find(PointLocatorInt(x));}
//	ColumnIterator GetColumnAtPoint(const CPoint& point){return point.y >= m_columnRect.top && point.y < m_columnRect.bottom ? m_columnMap.find(PointLocatorInt(point.x)) : m_columnEnd;}
//	ColumnIterator GetColumnAtPoint(const CPoint& point){return m_columnMap.find(PointLocatorInt(point.x));}
	ColumnIterator GetColumnAtPoint(int x){return m_columnMap.find(PointLocatorInt(x));}
	ColumnIterator GetColumnBegin(){return m_columnBegin;}
	ColumnIterator GetColumnEnd(){return m_columnEnd;}
	ColumnConstIterator GetColumnBegin() const{return m_columnBegin;}
	ColumnConstIterator GetColumnEnd() const{return m_columnEnd;}
	LbColumn* GetColumnById(unsigned short id) const{return id < m_columnCount && m_columnVector[id] != m_columnEnd ? m_columnVector[id]->second : nullptr;}
	void InvalidateItemColumn(int index, unsigned short id) const;
	void InvalidateItemColumnRange(int index, unsigned short idFrom, unsigned short idTo) const;
	void InvalidateItemColumnsFrom(int index, unsigned short idFrom) const;
	void InvalidateColumn(unsigned short id) const;
	void InvalidateColumnRange(unsigned short idFrom, unsigned short idTo) const;
	void InvalidateColumnsFrom(unsigned short idFrom) const;
	const ColumnIterator& GetColumnIteratorById(unsigned short id) const{return id < m_columnCount ? m_columnVector[id] : m_columnEnd;}
	const ColumnIterator& GetColumnIteratorEnd() const{return m_columnEnd;}

	bool GetColumnBounds(unsigned short id, int& left, int& right) const;
	bool GetColumnBounds(unsigned short id, RECT& rect) const;

	void GetScrollBounds(int& left, int& right) const;
	void GetScrollBounds(RECT& rect) const;

	bool SetFirstVisibleColumn(ColumnIterator firstVisible, UINT nCode = SB_LINELEFT);
	void UpdateHorizontalScroll();
	void CreateColumnToolTips();
	void UpdateColumnToolTipsHorizontalBoundsOnScroll();

	void OnHScroll(UINT nCode, UINT nPos);
	bool CanScrollColumnsRight() const;
protected:
	LbHorizontalScroller(ListBoxOwnerDraw* listBox):
		m_listBox(listBox),
		m_columnConstEnd(m_columnMap.cend()),
		m_columnBegin(m_columnMap.begin()),
		m_columnEnd(m_columnMap.end()),
		m_columnLast(m_columnEnd),
		m_columnFirstVisible(m_columnBegin),
		m_columnCount(0),
//		m_columnRect(0, 0, 0, 0),
		m_totalColumnCount(0),
//		m_focusItemRect(0, 0, 0, 0),
		m_columnLeftOffset(0),
		m_columnScrollOffset(0)
	{
		memset(&m_horizontalScrollInfo, 0, sizeof(SCROLLINFO));
		m_horizontalScrollInfo.cbSize = sizeof(SCROLLINFO);
		m_horizontalScrollInfo.nMax = -1;

		int left, right;
		GetScrollBounds(left, right);
		m_columnLeftOffset = left;//m_columnRect.left;
	}

	virtual void AddColumns() = 0;
	void UpdateScrollRange();
/*
	void UpdateTotalColumnWidth()
	{
		m_totalColumnWidth = m_columnLast == m_columnEnd ? 0 : m_columnLast->first.GetEnd();
	}
*/
	void UpdateColumnIterators()
	{
		m_columnBegin = m_columnMap.begin();
		m_columnLast = m_columnEnd;
		if(m_columnBegin != m_columnEnd)
		{
			--m_columnLast;
		}
	}
	bool AddColumn(const char* name,
		unsigned short id,
		int defaultWidth,
//		unsigned int ordinal,
		unsigned int dataAlignment,
		unsigned int titleAlignment,
		unsigned int totalAlignment,
		const char* tooltip,
		COLORREF titleColor = 0xFFFFFFFF,
		COLORREF totalColor = 0xFFFFFFFF,
		int dataOffset = 0,
		int titleOffset = 0,
		int totalOffset = 0);
	void DestroyColumns();

	ListBoxOwnerDraw* m_listBox;
	ColumnIteratorVector m_columnVector;
	ColumnIteratorVector m_columnIteratorVector;
	ColumnMap m_columnMap;
	SCROLLINFO m_horizontalScrollInfo;
	ColumnConstIterator m_columnConstEnd;
	ColumnIterator m_columnBegin;
	ColumnIterator m_columnEnd;
	ColumnIterator m_columnLast;
	ColumnIterator m_columnFirstVisible;
	unsigned short m_columnCount;
	unsigned short m_totalColumnCount;
//	CRect m_columnRect;
//	CRect m_focusItemRect;
	int m_columnLeftOffset;
	int m_columnScrollOffset;
//	int m_totalColumnWidth;
private:
	LbHorizontalScroller(const LbHorizontalScroller& other);
	LbHorizontalScroller& operator=(const LbHorizontalScroller& other);
};

enum TopItemChangeCause : unsigned char
{
	TICC_ADD_ITEM,
	TICC_INSERT_ITEM,
	TICC_REMOVE_ITEM,
	TICC_CLEAR_ITEMS,
	TICC_SCROLL,
	TICC_WHEEL,
	TICC_RESIZE,
	TICC_SET_TOP_ITEM,
	TICC_SET_CURRENT_ITEM,
	TICC_DESTROY,

	TICC_Count
};

//http://www.ucancode.net/Visual_C_Control/CListBox-DrawFrameControl-DrawFocusRect-VC-Tutorial.htm
class UGUI_API ListBoxOwnerDraw : public CListBox, public ControlToolTipHelper
{
public:
	virtual ~ListBoxOwnerDraw();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	virtual CBrush* GetBkBrush() const{return m_bkBrush;}
	void SetBkBrush(CBrush* const& brush)//ListBox is not an owner of the CBrush* m_bkBrush; should not delete.
	{
		if(brush != m_bkBrush)
		{
			m_bkBrush = brush;
			InvalidateClient();
		}
	}
	virtual int GetMaxWidth() const{return 0;}
	virtual bool isRadio() const{return false;}
	virtual void SetRadio(bool radio){}
	virtual COLORREF GetBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const;
	virtual COLORREF GetSelectedBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const;
	virtual void DestroyItem(const void* item) const{}
	virtual void* CloneItem(const void* item) const{return (void*)item;}
	virtual void* CreateItemFromString(const char* str) const{return nullptr;}
	virtual int AddCreatedItem(void* item, bool checked)
	{
		int ret = AddString((const char*)item);
		if(m_checkable && ret >= 0 && isItemChecked(item) != checked)// && checked)
		{
			SetItemChecked(item, ret, checked);
		}
		return ret;
	}
	virtual void ItemToString(const void* item, std::string& itemStr) const{itemStr = GetItemName(item);}
	virtual void ItemValueToString(const void* item, std::string& itemStr) const{}
    virtual int Compare(const void* item1, const void* item2) const;
	bool DeleteItemIfFound(const void* item);
	unsigned char DeleteItemAtAndSelectNext(int sel);//0 - not deleted; 1 - deleted the last item; 2 - deleted and there are items left.
	unsigned char DeleteSelectedItemAtAndSelectNext(){return DeleteItemAtAndSelectNext(m_itemSelected);}//;//0 - not deleted; 1 - deleted the last item; 2 - deleted and there are items left.
	int InsertOrMoveItem(void* item, int& ordinalWhere);//returns old position of the iytem (-1 if it was not there). ordinalWhere tells where to insert and receives the new position oif the item
	int FindItem(const void* toFind, int exact = 0) const;
	int FindItemByName(const char* name) const;
	virtual bool isSortedByName() const{return (GetStyle() & LBS_SORT) != 0 && !m_doNotSort;}
	virtual bool isSorted() const{return isSortedByName();}
	const void* GetSelectedItem() const//returns nullptr if no selection
	{
		return m_itemSelected >= 0 ? GetItemDataPtr(m_itemSelected) : nullptr;
	}
	const char* GetSelectedItemName() const//returns nullptr if no no selection
	{
		return m_itemSelected >= 0 ? GetItemNameAt(m_itemSelected) : nullptr;
	}
	int SetTopItemAtName(const char* const& name, const int& altTop);
	const char* GetTopItemName() const//returns nullptr if no item
	{
//		int top = GetTopIndex();
//		return top < GetCount() ? GetItemName(GetItemDataPtr(top)) : nullptr;
		return m_topItem < m_itemCount ? GetItemNameAt(m_topItem) : nullptr;
	}
	bool AdjustTopItem();//adjust top item so that there is as little unfilled space at the bottom as possible
	void SetItemAtTop(unsigned int index);
	void SetItemAtTopIfOutOfView(unsigned int index){if(!isItemVisible(index))SetItemAtTop(index);}
	virtual const char* GetItemName(const void* item) const{return "";}
	const char* GetItemNameAt(const unsigned int& at) const
	{
		const void* item = GetItemDataPtr(at);
		return item ? GetItemName(item) : nullptr;
	}
	virtual COLORREF GetUnselectedStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const{return m_selectable ? GetSysColor(COLOR_WINDOWTEXT) : GetSelectedBkColor(lpDrawItemStruct);}
	virtual COLORREF GetStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const;
	virtual COLORREF GetCheckColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const{return GetSysColor(COLOR_WINDOWTEXT);}

	CFont* GetMenuFont() const;
	CFont* GetMenuFontBold() const;
	CFont* GetTakionFont(const LOGFONT& logfont) const;
	CFont* GetTakionFont(CFont* font, unsigned char bold = 0, unsigned char italic = 0, unsigned char underline = 0, unsigned char strikeout = 0) const;//0 - leave as is, 1 - no, 2 - yes
	CFont* GetTakionBoldFont(CFont* font) const
	{
		return GetTakionFont(font, 2);
/*
		LOGFONT logfont;
		font->GetLogFont(&logfont);
		logfont.lfWeight = FW_BOLD;
		return GetTakionFont(logfont);
*/
	}

	CFont* const& GetFontNormal() const{return m_font;}
	virtual CFont* GetFontBold() const{return nullptr;}

	typedef std::list<std::string> StringList;
	static void TokenizeString(StringList& tokenList, const char* searchStr);
	static bool HasSearchRank(const StringList& tokenList, const char* name)
	{
		for(StringList::const_iterator it = tokenList.cbegin(), itend = tokenList.cend(); it != itend; ++it)
		{
			if(!it->empty() && U_StriStr(name, it->c_str()))
			{
				return true;
			}
		}
		return false;
	}
	inline void InvalidateRectIfValid(const RECT* rect) const{if(m_hWnd)::InvalidateRect(m_hWnd, rect, FALSE);}
	static unsigned int GetStringRank(const StringList& tokenList, const char* name);
	const std::string& GetSearchString() const{return m_searchString;}
	void SetSearchString(const char* searchString)
	{
		if(strcmp(m_searchString.c_str(), searchString))
		{
			m_searchString = searchString;
			SearchItems();
		}
	}
	virtual void SearchItems()
	{
		m_searchTokens.clear();
		TokenizeString(m_searchTokens, m_searchString.c_str());
		InvalidateRectIfValid(nullptr);
//		if(m_hWnd)::InvalidateRect(m_hWnd, nullptr, FALSE);
	}
	virtual bool isItemHighlighted(const void* item) const
	{
		return !m_searchTokens.empty() && isItemHighlightedBySearchTokens(item);
	}
	virtual bool isItemHighlightedBySearchTokens(const void* item) const
	{
		return HasSearchRank(m_searchTokens, GetItemName(item));
	}
	const COLORREF& GetItemHighlightColor() const{return m_itemHighlightColor;}
	void SetItemHighlightColor(const COLORREF& color)
	{
		if(m_itemHighlightColor != color)
		{
			m_itemHighlightColor = color;
			if(!m_searchTokens.empty())InvalidateClient(false);
		}
	}
	int isHighlightedItemVisible() const;//returns the index of the first highlighted item from top, -1 if none.
	int MakeHighlightedItemVisible(unsigned int startFrom);
	int MakeHighlightedItemVisibleIfNoneVisible();
	int MakeNextHighlightedItemVisible();

//	unsigned int GetItemUnderMouse() const{return m_itemUnderMouse;}
	COLORREF GetGrayColor() const;
	COLORREF GetBkGrayColor() const;
	COLORREF GetLoadColor() const;
	COLORREF GetPendingColor() const;
	COLORREF GetWarningColor() const;
	COLORREF GetBlueColor() const;

	CBrush* GetGrayBrush() const;
	CBrush* GetLoadBrush() const;
	CBrush* GetPendingBrush() const;
	CBrush* GetWarningBrush() const;
	CBrush* GetBlueBrush() const;

	virtual CBrush* GetPartialCheckedBrush() const;
	virtual COLORREF GetPartialCheckedColor() const;

	virtual CBrush* GetInvalidBrush() const{return GetGrayBrush();}
	virtual COLORREF GetInvalidColor() const{return GetBkGrayColor();} 
	bool SetInvalid(const bool& invalid)
	{
		if(invalid != m_invalid)
		{
			m_invalid = invalid;
			InvalidateClient();
			return true;
		}
		return false;
	}
	const bool& isInvalid() const{return m_invalid;}
	virtual bool isColorWhenInvalid() const{return false;}//When invalid, color GetDrawItemRect with GetBkColor
	void SetScrollSelectionByWheel(const bool& scrollSelectionByWheel)
	{
		if(scrollSelectionByWheel != m_scrollSelectionByWheel)
		{
			m_scrollSelectionByWheel = scrollSelectionByWheel;
			m_accumulatedWheel = 0;
		}
	}
	const bool& isScrollSelectionByWheel() const{return m_scrollSelectionByWheel;}

	const int& GetMyItemHeight() const{return m_itemHeight;}
	const int& GetOriginalItemHeight() const{return m_originalItemHeight;}
	const int& GetListBoxWidth() const{return m_listBoxWidth;}
	const int& GetListBoxHeight() const{return m_listBoxHeight;}
	const int& GetVerticalBorderSize() const{return m_verticalBorderSize;}
	const int& GetHorizontalBorderSize() const{return m_horizontalBorderSize;}

	bool GetColumnBounds(const unsigned short& id, int& left, int& right) const{return m_horizontalScroller && m_horizontalScroller->GetColumnBounds(id, left, right);}
	bool GetColumnBounds(const unsigned short& id, RECT& rect) const{return m_horizontalScroller && m_horizontalScroller->GetColumnBounds(id, rect);}

	int GetItemTop(const int& index) const{return (index - (int)m_topItem) * m_itemHeight;}
	void InvalidateItem(int index, int left = -1, int right = -1) const;
	void InvalidateClient(const bool& bErase = true) const
	{
		if(m_hWnd)::InvalidateRect(m_hWnd, &CRect(0, 0, m_listBoxWidth, m_listBoxHeight), bErase ? TRUE : FALSE);
	}
	void InvalidateCheckBoxRange(const unsigned int& firstItem, const unsigned int& lastItem) const
	{
		if(lastItem >= firstItem)InvalidateRectIfValid(&CRect(0, GetItemTop(firstItem), m_itemHeight, GetItemTop(lastItem) + m_itemHeight));
//		if(lastItem >= firstItem)::InvalidateRect(m_hWnd, &CRect(0, GetItemTop(firstItem), m_itemHeight, GetItemTop(lastItem) + m_itemHeight), FALSE);
	}
	void PostMessageToParent(UINT msg, LPARAM lParam);//WPARAM is GetDlgCtrlID()

	void SetRButtonSelection(const bool& rbuttonSelection){m_rbuttonSelection = rbuttonSelection;}
	void SetMButtonSelection(const bool& mbuttonSelection){m_mbuttonSelection = mbuttonSelection;}

	virtual bool isNullItemOk() const{return false;}//Can you pass a nullptr in the FindItem function ?
	virtual bool CanDragItemOut(unsigned int item) const{return true;}
	const bool& isDraggable() const{return m_draggable;}
	void SetDraggable(bool draggable);
	const bool& isDragging() const{return m_dragging;}
	int ItemFromPointInt(CPoint point) const;
	int ItemFromPointExt(CPoint point) const;
	int ItemFromPointInside(CPoint point) const;
	int ItemFromLButtonUpInside() const;
	int GetLBItemUnderPt(CPoint pt) const;
	bool MoveItem(int nSrcIndex, int nDestIndex, bool notifyParent);

	void AssignCursor(HCURSOR cursor);

	virtual bool isPointForRButtonMenuOk(UINT nFlags, CPoint point) const{return true;}

	virtual bool isCheckItemEnabled(const void* item) const{return true;}
//	virtual bool isCheckItemAtEnabled(unsigned int i) const{return i < (unsigned int)GetCount() && isCheckItemEnabled(GetItemDataPtr(i));}
	virtual bool isCheckItemAtEnabled(unsigned int i) const{return i < m_itemCount && isCheckItemEnabled(GetItemDataPtr(i));}
	virtual void SetCheckItemEnabled(void* item, bool enabled){}
	virtual bool SetCheckItemAtEnabled(unsigned int i, bool enabled);
	virtual bool isItemChecked(const void* item) const{return false;}
//	virtual bool isItemAtChecked(unsigned int i) const{return i < (unsigned int)GetCount() && isItemChecked(GetItemDataPtr(i));}
	virtual bool isItemAtChecked(unsigned int i) const{return i < m_itemCount && isItemChecked(GetItemDataPtr(i));}
//	virtual void SetItemChecked(void* item, unsigned int i, bool checked){}
//	virtual bool SetItemAtChecked(unsigned int i, bool checked);

//	bool SetItemAtChecked(unsigned int i, bool checked);
	short ToggleCheckSelected();
	virtual short ToggleCheckAt(unsigned int i);
	void ToggleCheckSelectedAndInvalidate(bool notify = true);
	void ToggleCheckAndInvalidate(unsigned int i, bool notify = true);
	bool SetCheckAndInvalidate(unsigned int i, bool checked, bool notify);
	void InvalidateItemChecked(unsigned int i, short checked, bool notify);
	
	virtual unsigned char AreAllItemsChecked() const//0 - none; 1 - not all; 2 - all
	{
		return !m_checkCount ? 0:
			m_checkCount == m_itemCount ? 2:
			1;
	}

	virtual unsigned char isRangeChecked(unsigned int start, unsigned int end) const;//0 - none; 1 - not all; 2 - all

	const bool& isSelectable() const{return m_selectable;}
	void SetSelectable(const bool& selectable)
	{
		if(selectable != m_selectable)
		{
			m_selectable = selectable;
			InvalidateClient(false);
		}
	}

	const COLORREF& GetSelectionBkColor() const{return m_selectionBkColor;}
	void SetSelectionBkColor(const COLORREF& color){SetSomeColor(m_selectionBkColor, color);}

	const COLORREF& GetNotSelectionBkColor() const{return m_notSelectionBkColor;}
	void SetNotSelectionBkColor(const COLORREF& color){SetSomeColor(m_notSelectionBkColor, color);}

	const COLORREF& GetSelectionTextColor() const{return m_selectionTextColor;}
	void SetSelectionTextColor(const COLORREF& color){SetSomeColor(m_selectionTextColor, color);}

	const COLORREF& GetNotSelectionTextColor() const{return m_notSelectionTextColor;}
	void SetNotSelectionTextColor(const COLORREF& color){SetSomeColor(m_notSelectionTextColor, color);}

	const unsigned char& isCheckable() const{return m_checkable;}
	void SetCheckable(const unsigned char& checkable){m_checkable = checkable;}

	const bool& isCheckOnDoubleClick() const{return m_checkOnDoubleClick;}
	void SetCheckOnDoubleClick(const bool& checkOnDoubleClick){m_checkOnDoubleClick = checkOnDoubleClick;}

	const COLORREF& GetCheckHighlightColor() const{return m_checkHighlightColor;}
	void SetCheckHighlightColor(const COLORREF& color){SetSomeColor(m_checkHighlightColor, color);}//{m_checkHighlightColor = color;}

	const COLORREF& GetCheckColor() const{return m_checkColor;}
	void SetCheckColor(const COLORREF& color){SetSomeColor(m_checkColor, color);}//{m_checkColor = color;}
	
	const int& GetCheckUnderMouse() const{return m_checkUnderMouse;}
	const int& GetCheckPressed() const{return m_checkPressed;}
	const unsigned int& GetCheckCount() const{return m_checkCount;}
	void SetCheckedAll(bool checked, bool notify);
	void SetCheckedRange(unsigned int start, unsigned int end, bool checked, bool notify);

//	void IncrementCheckCount(const unsigned int& count){m_checkCount += count;}
//	void DecrementCheckCount(const unsigned int& count){if(m_checkCount <= count)m_checkCount = 0; else m_checkCount -= count;}
//	void SetCheckCount(const unsigned int& count){m_checkCount = count;}

	const unsigned int& GetItemCount() const{return m_itemCount;}
	const unsigned int& GetTopItem() const{return m_topItem;}
	const int& GetItemSelected() const{return m_itemSelected;}
//Override the CListBox::GetCurSel
	const int& GetCurSel() const{return m_itemSelected;}

	bool isItemVisible(const unsigned int& at) const
	{
//05/13/2021
		return at >= m_topItem && at < m_topItem + m_visibleCount;
//		const int topY = GetItemTop(at);
//		return topY <= m_listBoxHeight && topY + m_itemHeight > 0;
	}
	void MakeItemVisible(const unsigned int at);

	void AddSpinCell(bool left, unsigned int increment);//LbSpinCell* cell);
	bool UpdateSpinRects();
	virtual bool SpinItem(unsigned int at, bool increment, unsigned int value, bool leftSideSpin, unsigned char ordinalSpin){return false;}
	virtual unsigned char GetLeftVisibleSpinCellCount(unsigned int i) const{return 0xFF;}
	virtual unsigned char GetRightVisibleSpinCellCount(unsigned int i) const{return 0xFF;}

	virtual CDragDropData* CreateDragDropData(CPoint point, int& itemOrdinal) const;
	virtual bool toCloneItemOnDrop() const{return false;}
	virtual bool CanDropDuplicates() const{return false;}
//	virtual
//	void SetFont(CFont* font);

	const bool& isDoNotSort() const{return m_doNotSort;}
	void SetDoNotSort(const bool& doNotSort){m_doNotSort = doNotSort;}

	int GetSpinCollectionTotalLeftWidth() const;
	int GetSpinCollectionTotalRightWidth() const;
	virtual void GetDrawItemRectOffsets(int& left, int& right, int itemHeight = 0) const;
	virtual bool isSpinValueMin(unsigned int at, bool leftSideSpin, unsigned char ordinalSpin) const{return false;}
	virtual bool isSpinValueMax(unsigned int at, bool leftSideSpin, unsigned char ordinalSpin) const{return false;}
	virtual int GetCheckInvalidateWidth() const{return 0;}
	const unsigned int& GetVisibleCount() const{return m_visibleCount;}
	const bool& isPartialVisible() const{return m_partialVisible;}
	unsigned int GetFullyVisibleCount() const
	{
		return m_partialVisible && m_visibleCount ? m_visibleCount - 1 : m_visibleCount;
	}
	unsigned int GetMaxTopItem() const;

	virtual bool HasItemToolTips() const{return m_itemToolTips;}
	virtual bool isToDestroyToolTipIfNoText() const override{return !HasItemToolTips();}
	virtual bool CanCreateToolTip() const override{return true;}

//	virtual const char* GetToolTipText() const override{return m_tooltipText;}

/*
	const bool& isTooltipsEnabled() const{return m_tooltipsEnabled;}
	bool EnableTooltips(const bool& enable)
	{
		if(enable != m_tooltipsEnabled)
		{
			m_tooltipsEnabled = enable;
			if(enable)return CreateToolTip();
			else
			{
				DestroyToolTip();
//				return false;
			}
		}
		return false;
	}
*/
	void UpdateToolTipTexts();
	void UpdateToolTipRects();
	void SetToolTipHorizontalBounds(int left, int right);
	void UpdateToolTips();
	static const unsigned int itemTooltipStartId = 1000;
//	void SetGeneralToolTip(const char* text);//Use ControlToolTipHelper::SetTooltipText
	void AddColumnToolTip(unsigned int id, int left, int right, const char* text);
	void RemoveColumnToolTip(unsigned int id);
	void SetColumnToolTipText(unsigned int id, const char* text);
	void SetColumnToolTipsHorizontalBounds(int left, int right);
	void UpdateColumnToolTipsVerticalBounds();
	virtual void UpdateColumnToolTipsHorizontalBounds(){}
	void ClearColumnToolTips();
	virtual bool GetToolTipInfo(unsigned int ordinal, const void* item, std::string& tooltipText, int& left, int& right) const{return false;}
	virtual bool isOneTooltipPerItem() const{return true;}

	const CPoint& GetMousePos() const{return m_mousePos;}
	void UpdateCheckable(){UpdateCheckable(m_mousePos);}
	void OnDialogFinish(){ScrollIdle(SB_ENDSCROLL);}
	virtual int FindDroppedItem(const void* toFind) const{return FindItem(toFind, 0);}
	virtual void OnMouseForcedReleaseCapture();
	void SetToolRect(unsigned int id, const RECT& rect);
	void ScrollHorizontally(int diff);
	LbHorizontalScroller* GetHorizontalScroller(){return m_horizontalScroller;}
	const LbHorizontalScroller* GetHorizontalScroller() const{return m_horizontalScroller;}
	int GetTotalColumnWidth() const{const LbHorizontalScroller* hs = GetHorizontalScroller(); return hs ? hs->GetTotalColumnWidth() : 0;}
	virtual void GetHorizontalScrollBounds(int& left, int& right) const;

	void InvalidateItemColumn(int index, unsigned short id) const{if(m_horizontalScroller)m_horizontalScroller->InvalidateItemColumn(index, id);}
	void InvalidateItemColumnRange(int index, unsigned short idFrom, unsigned short idTo) const{if(m_horizontalScroller)m_horizontalScroller->InvalidateItemColumnRange(index, idFrom, idTo);}
	void InvalidateItemColumnsFrom(int index, unsigned short idFrom) const{if(m_horizontalScroller)m_horizontalScroller->InvalidateItemColumnsFrom(index, idFrom);}
	void InvalidateColumn(unsigned short id) const{if(m_horizontalScroller)m_horizontalScroller->InvalidateColumn(id);}
	void InvalidateColumnRange(unsigned short idFrom, unsigned short idTo) const{if(m_horizontalScroller)m_horizontalScroller->InvalidateColumnRange(idFrom, idTo);}
	void InvalidateColumnsFrom(unsigned short idFrom) const{if(m_horizontalScroller)m_horizontalScroller->InvalidateColumnsFrom(idFrom);}

	bool ClearItemsWithRedraw();
	virtual void GetDrawItemRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawItemRect) const;
	virtual void GetFocusItemRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawItemRect) const
	{
		GetDrawItemRect(lpDrawItemStruct, drawItemRect);
	}
	virtual void GetSelectionItemRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawItemRect) const
	{
		GetDrawItemRect(lpDrawItemStruct, drawItemRect);
	}
	virtual void GetHighlightItemRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawItemRect) const
	{
		GetSelectionItemRect(lpDrawItemStruct, drawItemRect);
	}
	void DrawInsert(const int nItem);

	void CopyContentsToClipboard() const;
	virtual bool ContentsToString(std::string& contents) const;//returns true if successful
	void PasteContentsFromClipboard(const bool replace);
	virtual void ClearBeforeReplace(){ResetContent();}
	virtual bool StringToContents(const char* contents, size_t contentsLength);// const std::string& contents);//returns true if successful
	virtual bool AllowDuplicates() const{return false;}
	virtual bool AllowEmptyName() const{return false;}
//	const unsigned int& GetCtrlId() const{return m_ctrlId;}

	void SendMessageToParent(const UINT& message, const WPARAM& w, const LPARAM& l) const
	{
		if(m_hWnd)
		{
			HWND parentWnd = ::GetParent(m_hWnd);
			if(parentWnd)
			{
				::SendMessage(parentWnd, message, w, l);
			}
		}
	}
/*
	void DeleteItemAndSelectNextItem(unsigned int sel)
	{
		DeleteString(sel);
		if(m_itemCount > 0)SetCurSel(m_itemCount > sel ? sel : m_itemCount - 1);
	}
*/
	bool UpdateSelectedItem()//const unsigned char& cause)
	{
		return DoSetSelectedItem(CListBox::GetCurSel());
	}
	int MeasureText(const char* text, CFont* font, int charCount = -1) const;
	int MeasureTextHeight(const char* text, CFont* font, int charCount = -1) const;
	bool RemoveAllButFirstItem();
	bool RemoveItemsFromEnd(unsigned int startFrom);

protected:
	ListBoxOwnerDraw(int itemHeight = 0, bool rbuttonSelection = false, bool rbuttonMenu = false, bool draggable = false, const char* tooltipText = nullptr, CToolTipCtrl* externalToolTip = nullptr);
	
	void SetSomeColor(COLORREF& what, const COLORREF& color)//{m_selectionBkColor = color;}
	{
		if(color != what)
		{
			what = color;
			InvalidateClient(false);
		}
	}

	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;

//	bool CreateToolTip();
//	bool DestroyToolTip();

	void InitializeFont(CFont* font);

	virtual void SetItemChecked(void* item, unsigned int i, bool checked){}
	virtual void ItemChecked(unsigned int i, bool checked){}

	virtual void OnFontSet(CFont* font, HDC hdc){}

	virtual LbHorizontalScroller* CreateHorizontalScroller(){return nullptr;}
	virtual void HorizontalScrollingDone(int diff){}

	virtual void SizeChanged(bool horizontalChange, bool verticalChange){}
/*
	virtual BOOL BeginDrag(CPoint pt) override;
	virtual void CancelDrag(CPoint pt) override;
	virtual UINT Dragging(CPoint pt) override;//DL_MOVECURSOR, DL_COPYCURSOR, DL_STOPCURSOR
	virtual void Dropped(int nSrcIndex, CPoint pt);
*/
//OwnDrag
	bool BeginDrag(CPoint pt);
	bool CancelDrag();//CPoint pt);
	void Dragging(CPoint pt);
	bool Dropped();//CPoint pt);

	void DrawSingle(const int nIndex);
	void DrawInsertionLine(HDC hdc, const RECT& rect);

	virtual void ItemMoved(unsigned int from, unsigned int to){}

	void DrawFocus(LPDRAWITEMSTRUCT lpDrawItemStruct);

	void UpdateCheckable(CPoint point);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
/*ControlToolTipHelper
	void AddMenuSeparator(CMenu& menu)
	{
		if(menu.GetMenuItemCount())
		{
			menu.AppendMenu(MF_SEPARATOR);
			m_menuHasSeparator = true;
		}
	}
*/
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEnterMenuLoop(BOOL bIsTrackPopupMenu);
	afx_msg void OnExitMenuLoop(BOOL bIsTrackPopupMenu);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
//	afx_msg BOOL HandleNotifyReflect(NMHDR* pNotifyStruct, LRESULT* result);

	afx_msg LRESULT OnSetFont(WPARAM w, LPARAM l);
	afx_msg LRESULT OnAddString(WPARAM w, LPARAM l);
	afx_msg LRESULT OnInsertString(WPARAM w, LPARAM l);
	afx_msg LRESULT OnDeleteString(WPARAM w, LPARAM l);
	afx_msg LRESULT OnResetContent(WPARAM w, LPARAM l);
	afx_msg LRESULT OnSetCurSel(WPARAM w, LPARAM l);
	afx_msg LRESULT OnSetTopIndex(WPARAM w, LPARAM l);
	afx_msg LRESULT OnSetItemHeight(WPARAM index, LPARAM itemHeight);
	afx_msg BOOL OnSelchange();

	DECLARE_MESSAGE_MAP()

	virtual void OnItemSelected(){}

	virtual void OnItemAdded(void* item, unsigned int at, bool checked){}
	virtual void BeforeItemDeleted(unsigned int at, bool checked)
	{
		if(checked && m_checkCount)--m_checkCount;
	}
	virtual void AfterItemDeleted(unsigned int at, bool failed, bool checked)
	{
		if(checked && failed)++m_checkCount;
	}
	virtual void BeforeItemsCleared(){}
	virtual void AfterItemsCleared(){m_checkCount = 0;}

	virtual void OnItemHeightSet(unsigned int index, unsigned int itemHeight){}

	void RecalculateCheckCount();

	virtual void PreSubclassWindow();
	virtual void ListBoxCreated();//Called before m_itemCount is initialized
	virtual void FinishPreSubclassWindow(){}//Called after m_itemCount is initialized

//	virtual void BeforeDestroy(){}//ControlToolTipHelper
	virtual void Resize(int cx, int cy);
//	virtual void MouseEntered(){}
//	virtual void MouseLeft(){}
	virtual void HorizontalScrollDone(){}
	virtual void VerticalScrollDone(){}

	virtual void TopItemChanged(unsigned int prevTop, unsigned char cause){}
	bool DoSetTopItem(const unsigned int& topItem, const unsigned char& cause)
	{
		if(topItem != m_topItem)
		{
			const unsigned int prevTop = m_topItem;
			m_topItem = topItem;
			TopItemChanged(prevTop, cause);
			return true;
		}
		return false;
	}
	bool UpdateTopItem(const unsigned char& cause)
	{
		return DoSetTopItem((unsigned int)CListBox::GetTopIndex(), cause);
	}
	bool NullifyTopItem(const unsigned char& cause)
	{
		return DoSetTopItem(0, cause);
	}
	bool DoSetSelectedItem(const int& itemSelected)
	{
		if(itemSelected != m_itemSelected)
		{
			m_itemSelected = itemSelected;
			OnItemSelected();
			return true;
		}
		return false;
	}
	bool NullifySelectedItem()//const unsigned char& cause)
	{
		return DoSetSelectedItem(-1);
	}

	virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect);
	virtual void DrawNumber(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& r){}
	virtual void DrawPrefix(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& r){}
	virtual void DrawSuffix(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& r){}

	virtual void PreAddMenuItems(CMenu& menu){}
	virtual void AddMenuItems(CMenu& menu){}
	virtual void PostAddMenuItems(CMenu& menu){}

	bool AddSelectionMenuItems(CMenu& menu);

	void AddClipboardMenuItems(CMenu& menu);
	virtual bool CanPaste() const{return IsClipboardFormatAvailable(CF_TEXT) == TRUE;}
	virtual bool CanCopy() const{return true;}//Can copy even an empty List Box - clear the clipboard.

	void AddInOutMenuItems(CMenu& menu, bool find = true);
	virtual bool CanAddItem() const{return true;}
	virtual int AddItemOnMenuCommand(int before){return -1;}
	virtual bool CanFindItem() const{return m_itemCount > 0 && CanAddItem();}
	virtual int FindItemOnMenuCommand(){return -2;}
	virtual bool CanRemoveSelectedItem() const{return GetCurSel() >= 0;}
	virtual bool CanClearItems() const{return m_itemCount > 0;}

	virtual bool RemoveSelectedItemOnMenuCommand(int sel){return DeleteItemAtAndSelectNext(sel) != 0;}
	virtual bool ClearItemsOnMenuCommand(){return ClearItemsWithRedraw();}

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	void ScrollIdle(UINT nSBCode);
	bool m_scroll;
//	unsigned int m_itemUnderMouse;
	int m_itemHeight;
	int m_originalItemHeight;
//OwnDrag
	int m_itemDragged;
	int m_dragInsert;
	int m_insertionHalfHeight;

//	unsigned int m_ctrlId;
	short m_accumulatedWheel;

	bool m_itemHeightInitialized;
//	bool m_fontInitialized;
	CFont* m_font;

	virtual void MouseEntered() override
	{
		m_accumulatedWheel = 0;
		SendMessageToParent(WM_USER + 16, m_ctrlId, (LPARAM)m_hWnd);//this);
	}
	virtual void MouseLeft() override
	{
		m_accumulatedWheel = 0;
		SendMessageToParent(WM_USER + 36, m_ctrlId, (LPARAM)m_hWnd);//this);
	}
/*
	bool SetMouseInside(const bool& mouseInside)
	{
		if(mouseInside != m_mouseInside)
		{
			m_mouseInside = mouseInside;
			m_accumulatedWheel = 0;
			SendMessageToParent(mouseInside ? WM_USER + 16 : WM_USER + 36, GetDlgCtrlID(), (LPARAM)m_hWnd);//this);
			return true;
		}
		return false;
	}
	bool m_mouseInside;
*/
	bool m_checkOnDoubleClick;
	int m_listBoxWidth;
	int m_listBoxHeight;
	int m_verticalBorderSize;
	int m_horizontalBorderSize;
	CPoint m_pointLButtonUp;
	bool m_mbuttonSelection;
	bool m_rbuttonSelection;
	bool m_rbuttonMenu;
	bool m_draggable;
	bool m_dragging;
	bool m_lButtonDown;
	bool m_doNotSort;

	bool m_invalid;

	virtual void UpdateTooltipText() override;//ControlToolTipHelper

//	void CreateToolTips();
	void DestroyToolTips();
	void DoCreateToolTips();
	void DoDestroyToolTips();
	void AddLastAddedItemToolTips(unsigned int at);

	virtual void DoCreateColumnToolTips(){}

	virtual void ToolTipCreated() override;

//	bool m_tooltipsEnabled;
	bool m_itemToolTips;

	bool m_scrollSelectionByWheel;

	bool m_selectable;
	unsigned char m_checkable;
	COLORREF m_checkColor;
	COLORREF m_checkHighlightColor;
	COLORREF m_selectionBkColor;
	COLORREF m_notSelectionBkColor;
	COLORREF m_selectionTextColor;
	COLORREF m_notSelectionTextColor;
	COLORREF m_itemHighlightColor;
	void SetCheckUnderMouse(int i);
	int m_checkUnderMouse;
	int m_checkPressed;
	int m_spacePressedItem;
	unsigned int m_checkCount;

	unsigned int m_itemCount;
	unsigned int m_topItem;
	int m_itemSelected;

	std::string m_searchString;
	StringList m_searchTokens;

	UINT m_hAlignment;

	HCURSOR m_cursor;
	HCURSOR m_dragCursor;

	void MoveRangeToTop(bool notify);
	void SelectRange(bool checked, bool notify);
	CPoint m_rbuttonPoint;

	LbSpinCellCollection* m_spinCollection;

	CBrush* m_bkBrush;

	unsigned int m_visibleCount;
	bool m_partialVisible;

//	CToolTipCtrl* m_toolTip;
	unsigned int m_tooltipCount;
//	bool DoAddGeneralToolTip();
//	char* m_generalToolTip;//ControlToolTipHelper::m_tooltipText

	CPoint m_mousePos;

	LbHorizontalScroller* m_horizontalScroller;
private:
	int GetTopIndex() const{return CListBox::GetTopIndex();}//Use GetTopItem();
	int GetCount() const{return CListBox::GetCount();}//Use GetItemCount();
//	bool m_menuHasSeparator;
};

//#define COMBOBOX_OWN_TOP_ITEM

class UGUI_API ComboBoxOwnerDraw : public CComboBox, public ControlToolTipHelper
{
public:
	virtual ~ComboBoxOwnerDraw();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual COLORREF GetBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const;
	virtual COLORREF GetSelectedBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const;

//	void SetFont(CFont* font);

	bool SetInvalid(const bool& invalid)
	{
		if(invalid != m_invalid)
		{
			m_invalid = invalid;
			if(m_hWnd)Invalidate(TRUE);
			return true;
		}
		return false;
	}
	const bool& isInvalid() const{return m_invalid;}
	const COLORREF& GetColorInvalid() const{return m_colorInvalid;}
	void SetColorInvalid(const COLORREF& color)
	{
		if(color != m_colorInvalid)
		{
			m_colorInvalid = color;
			if(m_invalid && m_hWnd)
			{
				Invalidate(TRUE);
			}
		}
	}

	CFont* GetMenuFont() const;
	CFont* GetMenuFontBold() const;
	CFont* GetTakionFont(const LOGFONT& logfont) const;
	CFont* GetTakionFont(CFont* font, unsigned char bold = 0, unsigned char italic = 0, unsigned char underline = 0, unsigned char strikeout = 0) const;//0 - leave as is, 1 - no, 2 - yes
	CFont* GetTakionBoldFont(CFont* font) const
	{
		return GetTakionFont(font, 2);
/*
		LOGFONT logfont;
		font->GetLogFont(&logfont);
		logfont.lfWeight = FW_BOLD;
		return GetTakionFont(logfont);
*/
	}

//	const unsigned int& GetCtrlId() const{return m_ctrlId;}

	CFont* const& GetFontNormal() const{return m_font;}
	virtual CFont* GetFontBold() const{return nullptr;}

	bool DeleteItemIfFound(const void* item);
	unsigned char DeleteItemAtAndSelectNext(int sel);//0 - not deleted; 1 - deleted the last item; 2 - deleted and there are items left.
	unsigned char DeleteSelectedItemAtAndSelectNext(){return DeleteItemAtAndSelectNext(m_itemSelected);}//;//0 - not deleted; 1 - deleted the last item; 2 - deleted and there are items left.

	virtual void DestroyItem(const void* item) const{}
    virtual int Compare(const void* item1, const void* item2) const;
    int FindItem(const void* toFind, int exact = 0) const;
	int FindItemByName(const char* name) const;
	virtual bool isSortedByName() const{return (GetStyle() & CBS_SORT) != 0 && !m_doNotSort;}
	virtual bool isSorted() const{return isSortedByName();}
	virtual COLORREF GetUnselectedStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const{return GetSysColor(COLOR_WINDOWTEXT);}
//	virtual COLORREF GetUnselectedStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const{return m_selectable ? GetSysColor(COLOR_WINDOWTEXT) : GetSelectedBkColor(lpDrawItemStruct);}
	virtual COLORREF GetStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const{return (lpDrawItemStruct->itemState & ODS_SELECTED) == 0 || m_invalid ? GetUnselectedStringColor(lpDrawItemStruct) : GetSysColor(COLOR_HIGHLIGHTTEXT);}
	virtual const char* GetItemName(const void* item) const{return "";}
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	void SetHeight(const int& height){m_itemHeight = height;}
	void SetDisabledColor(COLORREF disabledColor);
	const int& GetMyItemHeight() const{return m_itemHeight;}
	const int& GetComboBoxWidth() const{return m_comboBoxWidth;}
	const int& GetComboBoxHeight() const{return m_comboBoxHeight;}
	const int& GetButtonWidth() const{return m_buttonWidth;}
	const int& GetButtonHeight() const{return m_buttonHeight;}
	const int& GetOriginalItemHeight() const{return m_originalItemHeight;}
	const COLORREF& GetNoSelectionColor() const{return m_noSelectionColor;}
	void SetNoSelectionColor(const COLORREF& color){m_noSelectionColor = color;}

	const bool& isDoNotSort() const{return m_doNotSort;}
	void SetDoNotSort(const bool& doNotSort){m_doNotSort = doNotSort;}
/*
	const bool& isSmallerDropDown() const{return m_smallerDropDown;}
	void SetSmallerDropDown(const bool& smallerDropDown)
	{
		m_smallerDropDown = smallerDropDown;
		if(m_hWnd)SetDroppedWidth(smallerDropDown ? m_comboBoxWidth - m_buttonWidth : m_comboBoxWidth);
	}
*/
	virtual void GetDrawItemRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawItemRect) const{drawItemRect = lpDrawItemStruct->rcItem;}
	virtual void GetFocusItemRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawItemRect) const
	{
		GetDrawItemRect(lpDrawItemStruct, drawItemRect);
	}
	virtual void GetSelectionItemRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawItemRect) const
	{
		GetDrawItemRect(lpDrawItemStruct, drawItemRect);
	}
	const bool& isRButtonMenu() const{return m_rbuttonMenu;}
	void SetRButtonMenu(const bool& rbuttonMenu){m_rbuttonMenu = rbuttonMenu;}
////
//	void SetToolTipText(const char* tooltipText);//ControlToolTipHelper

	const bool& HasItemToolTips() const{return m_itemToolTips;}
	void SetItemToolTips(const bool itemToolTips);
	virtual bool isToDestroyToolTipIfNoText() const override{return !HasItemToolTips();}

//	const bool& isTooltipsEnabled() const{return m_tooltipsEnabled;}//ControlToolTipHelper
//	void EnableTooltips(const bool enable);

	virtual const char* GetToolTipText() const override{return GetSelectedItemToolTip();}
	virtual const char* GetItemToolTip(int sel, const void* item) const
	{
		return m_itemToolTipArray && sel >= 0 && (unsigned int)sel < m_itemToolTipCount ? m_itemToolTipArray[sel].GetStr() : m_tooltipText;
	}
	void CreateItemToolTipArray(unsigned int count);
	void CreateItemToolTipArray(){CreateItemToolTipArray(m_itemCount);}
	void DestroyItemToolTipArray();
	void SetItemToolTip(const unsigned int& ordinal, const char* const& str, const unsigned char& own)//0 - does not own; 1 - do not create, only delete; 2 - create and delete.
	{
		if(m_itemToolTipArray && ordinal < m_itemToolTipCount)m_itemToolTipArray[ordinal].SetBuffer(str, own);
	}
	void SetItemToolTip(const unsigned int& ordinal, const std::string& str)
	{
		if(m_itemToolTipArray && ordinal < m_itemToolTipCount)m_itemToolTipArray[ordinal].SetBuffer(str);
	}
	const StrBuffer* const& GetItemToolTipArray() const{return m_itemToolTipArray;}
	const unsigned int& GetItemToolTipCount() const{return m_itemToolTipCount;}

	const char* GetSelectedItemToolTip() const{return m_hWnd ? DoGetSelectedItemToolTip() : nullptr;}

	virtual const CRect& GetToolTipRect() const override{return m_editRect;}

////

//	int SetCurSel(int nSelect);//redefined CComboBox's SetCurSel
	void SendMessageToParent(const UINT& message, const WPARAM& w, const LPARAM& l) const
	{
		if(m_hWnd)
		{
			HWND parentWnd = ::GetParent(m_hWnd);
			if(parentWnd)
			{
				::SendMessage(parentWnd, message, w, l);
			}
		}
	}

	const unsigned int& GetItemCount() const{return m_itemCount;}
	const int& GetItemSelected() const{return m_itemSelected;}
//Override the CComboBox::GetCurSel
	const int& GetCurSel() const{return m_itemSelected;}

	const char* GetSelectedItemName() const//returns nullptr if no no selection
	{
		return m_itemSelected >= 0 ? GetItemNameAt(m_itemSelected) : nullptr;
	}

#ifdef COMBOBOX_OWN_TOP_ITEM
	const unsigned int& GetTopItem() const{return m_topItem;}
	const char* GetTopItemName() const//returns nullptr if no item
	{
		return m_topItem < m_itemCount ? GetItemNameAt(m_topItem) : nullptr;
	}
	int GetItemTop(const int& index) const{return (index - (int)m_topItem) * m_itemHeight;}
#endif
/*
	int SetTopItemAtName(const char* const& name, const int& altTop);
	bool AdjustTopItem();//adjust top item so that there is as little unfilled space at the bottom as possible
	void SetItemAtTop(unsigned int index);
	void SetItemAtTopIfOutOfView(unsigned int index){if(!isItemVisible(index))SetItemAtTop(index);}
*/
	const char* GetItemNameAt(const unsigned int& at) const
	{
		const void* item = GetItemDataPtr(at);
		return item ? GetItemName(item) : nullptr;
	}

	bool RemoveAllButFirstItem();
	bool RemoveItemsFromEnd(unsigned int startFrom);
protected:
	ComboBoxOwnerDraw(COLORREF disabledColor = 0xFFFFFFFF, int itemHeight = 0, bool rbuttonMenu = false, const char* tooltipText = nullptr, CToolTipCtrl* externalToolTip = nullptr);
	void InitializeFont(CFont* font);
	void DrawFocus(LPDRAWITEMSTRUCT lpDrawItemStruct);

	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
	virtual void PreSubclassWindow() override;
	virtual void ComboBoxCreated();
//	virtual void BeforeDestroy(){}//ControlToolTipHelper
	virtual void Resize(int cx, int cy);
	virtual void SizeChanged(bool horizontalChange, bool verticalChange){}
	virtual void PreAddMenuItems(CMenu& menu){}
	virtual void AddMenuItems(CMenu& menu){}
	virtual void PostAddMenuItems(CMenu& menu){}
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
/*ControlToolTipHelper
	void AddMenuSeparator(CMenu& menu)
	{
		if(menu.GetMenuItemCount())
		{
			menu.AppendMenu(MF_SEPARATOR);
			m_menuHasSeparator = true;
		}
	}
*/
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);

//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnSelchange();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEnterMenuLoop(BOOL bIsTrackPopupMenu);
	afx_msg void OnExitMenuLoop(BOOL bIsTrackPopupMenu);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	afx_msg LRESULT OnSetFont(WPARAM w, LPARAM l);
	afx_msg LRESULT OnAddString(WPARAM w, LPARAM l);
	afx_msg LRESULT OnInsertString(WPARAM w, LPARAM l);
	afx_msg LRESULT OnDeleteString(WPARAM w, LPARAM l);
	afx_msg LRESULT OnResetContent(WPARAM w, LPARAM l);
	afx_msg LRESULT OnSetCurSel(WPARAM w, LPARAM l);
#ifdef COMBOBOX_OWN_TOP_ITEM
	afx_msg BOOL OnDropdown();
	afx_msg BOOL OnCloseup();
	afx_msg LRESULT OnSetTopIndex(WPARAM w, LPARAM l);
#endif
	afx_msg LRESULT OnSetItemHeight(WPARAM index, LPARAM itemHeight);

	DECLARE_MESSAGE_MAP()

	virtual void OnItemSelected(){}
	virtual void OnItemAdded(void* item, unsigned int at){}
	virtual void BeforeItemDeleted(unsigned int at){}
	virtual void AfterItemDeleted(unsigned int at, bool failed){}
	virtual void BeforeItemsCleared(){}
	virtual void AfterItemsCleared(){}

	virtual void OnItemHeightSet(unsigned int index, unsigned int itemHeight){}

	virtual void FinishPreSubclassWindow(){}

	virtual void MouseEntered() override{SendMessageToParent(WM_USER + 16, m_ctrlId, (LPARAM)m_hWnd);}
	virtual void MouseLeft() override{SendMessageToParent(WM_USER + 36, m_ctrlId, (LPARAM)m_hWnd);}
	virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct) override;
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect);
	virtual void DrawNumber(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& r){}
	virtual void DrawPrefix(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& r){}
	virtual void DrawSuffix(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& r){}
	void ScrollIdle(UINT nSBCode);
	COLORREF m_disabledColor;
	COLORREF m_noSelectionColor;

	bool m_rbuttonMenu;

	bool m_doNotSort;

//	bool m_smallerDropDown;

	bool m_scroll;
	bool m_itemHeightInitialized;

//	unsigned int m_ctrlId;

//	bool m_fontInitialized;
	CFont* m_font;
	virtual void OnFontSet(CFont* font, HDC hdc){}
/*ControlToolTipHelper
	bool SetMouseInside(const bool& mouseInside)
	{
		if(mouseInside != m_mouseInside)
		{
			m_mouseInside = mouseInside;
			SendMessageToParent(mouseInside ? WM_USER + 16 : WM_USER + 36, GetDlgCtrlID(), (LPARAM)m_hWnd);//this);
			return true;
		}
		return false;
	}
	bool m_mouseInside;
*/
//	void UpdateEnableTooltips();
	bool m_itemToolTips;
//	bool m_tooltipsEnabled;

	bool m_invalid;
	COLORREF m_colorInvalid;

	CRect m_editRect;

	int m_itemHeight;
	int m_originalItemHeight;
	int m_comboBoxWidth;
	int m_comboBoxHeight;
	int m_buttonWidth;
	int m_buttonHeight;
	UINT m_hAlignment;

//	virtual void ToolTipCreated() override;//ControlToolTipHelper

//	void UpdateToolTipRects();
//	bool CreateToolTip();
//	void DestroyToolTip();
//	void UpdateToolTipText();
//	CToolTipCtrl* m_toolTip;
//	void DoSetToolTipInfo(const char* text);
	const char* DoGetSelectedItemToolTip() const
	{
		int sel = GetCurSel();
		const void* item = sel >= 0 ? GetItemDataPtr(sel) : nullptr;
		const char* tooltip = GetItemToolTip(sel, item);
		if(!tooltip)tooltip = "";
		return tooltip;
	}

//	char* m_tooltipText;

	StrBuffer* m_itemToolTipArray;
	unsigned int m_itemToolTipCount;
//
#ifdef COMBOBOX_OWN_TOP_ITEM
	virtual void TopItemChanged(unsigned int prevTop, unsigned char cause){}
	bool DoSetTopItem(const unsigned int& topItem, const unsigned char& cause)
	{
		if(topItem != m_topItem)
		{
			const unsigned int prevTop = m_topItem;
			m_topItem = topItem;
			TopItemChanged(prevTop, cause);
			return true;
		}
		return false;
	}
	bool UpdateTopItem(const unsigned char& cause)
	{
		return DoSetTopItem((unsigned int)CComboBox::GetTopIndex(), cause);
	}
	bool NullifyTopItem(const unsigned char& cause)
	{
		return DoSetTopItem(0, cause);
	}
#endif
	bool DoSetSelectedItem(const int& itemSelected)
	{
		if(itemSelected != m_itemSelected)
		{
			m_itemSelected = itemSelected;
			OnItemSelected();
			return true;
		}
		return false;
	}
	bool NullifySelectedItem()//const unsigned char& cause)
	{
		return DoSetSelectedItem(-1);
	}
	bool UpdateSelectedItem()//const unsigned char& cause)
	{
		return DoSetSelectedItem(CComboBox::GetCurSel());
	}
	unsigned int m_itemCount;
#ifdef COMBOBOX_OWN_TOP_ITEM
	unsigned int m_topItem;
#endif
	int m_itemSelected;

	bool m_initCompleted;
private:
#ifdef COMBOBOX_OWN_TOP_ITEM
	int GetTopIndex() const{return CComboBox::GetTopIndex();}//Use GetTopItem();
#endif
	int GetCount() const{return CComboBox::GetCount();}//Use GetItemCount();

//	bool m_menuHasSeparator;//ControlToolTipHelper

//	void CompleteInit();
};

template <class N, unsigned char M = sizeof(N) * 8>
class ListBoxSimpleFilter : public ListBoxOwnerDraw
{
public:
	typedef N FilterType;
	static const unsigned char m = M;
	bool isItemOrdinalChecked(const unsigned char& ordinal) const
	{
		return (m_filter & ((FilterType)1 << ordinal)) != 0;
	}
	virtual bool isItemChecked(const void* item) const override
	{
		return isItemOrdinalChecked((unsigned char)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			item);
	}
/*
	virtual unsigned char AreAllItemsChecked() const override//0 - none; 1 - not all; 2 - all
	{
		return !m_filter ? 0:
			m_filter < m_allItemsMask ? 1:
			2;
	}
*/
//	virtual CBrush* GetZeroBrush() const{return m_zeroFilterValid ? nullptr : GetWarningBrush();}
	virtual CBrush* GetZeroBrush() const{return m_reverseColor ? ListBoxOwnerDraw::GetBkBrush() : GetWarningBrush();}
	virtual CBrush* GetPartialBrush() const{return GetPartialCheckedBrush();}
	virtual CBrush* GetAllBrush() const{return m_reverseColor ? GetWarningBrush() : ListBoxOwnerDraw::GetBkBrush();}//nullptr;}

	virtual COLORREF GetZeroColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const{return m_reverseColor ? ListBoxOwnerDraw::GetBkColor(lpDrawItemStruct) : GetWarningColor();}
	virtual COLORREF GetPartialColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const{return GetPartialCheckedColor();}
	virtual COLORREF GetAllColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const{return m_reverseColor ? GetWarningColor() : ListBoxOwnerDraw::GetBkColor(lpDrawItemStruct);}

	virtual CBrush* GetOneBrush() const
	{
		return ListBoxOwnerDraw::GetBkBrush();
	}
	virtual CBrush* GetBkBrush() const override
	{
		if(m_oneColor)
		{
			return GetOneBrush();
		}
		else
		{
			CBrush* defaultBrush = ListBoxOwnerDraw::GetBkBrush();
			if(defaultBrush)return defaultBrush;
			switch(AreAllItemsChecked())
			{
				case 0:
				return GetZeroBrush();

				case 1:
				return GetPartialBrush();

				default:
				return defaultBrush;// GetAllBrush();
			}
		}
/*
		return 
			m_filter ?
				m_partialFilterSameAsAll || AreAllItemsChecked() > 1 ? nullptr : GetPartialCheckedBrush() :
				m_zeroFilterValid ? nullptr : GetWarningBrush();
*/
	}
	virtual COLORREF GetOneColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const
	{
		return ListBoxOwnerDraw::GetBkColor(lpDrawItemStruct);
	}
	virtual COLORREF GetBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override
	{
		if(m_oneColor)
		{
			return GetOneColor(lpDrawItemStruct);
		}
		switch(AreAllItemsChecked())
		{
			case 0:
			return GetZeroColor(lpDrawItemStruct);

			case 1:
			return GetPartialColor(lpDrawItemStruct);

			default:
			return GetAllColor(lpDrawItemStruct);
		}
/*
		return
			m_filter ?
				m_partialFilterSameAsAll || AreAllItemsChecked() > 1 ? ListBoxOwnerDraw::GetBkColor(lpDrawItemStruct) : GetPartialCheckedColor() :
				m_zeroFilterValid ? ListBoxOwnerDraw::GetBkColor(lpDrawItemStruct) : GetWarningColor();
*/
	}
    virtual int Compare(const void* item1, const void* item2) const override
	{
		const unsigned char i1 = (const unsigned char)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			item1;
		const unsigned char i2 = (const unsigned char)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			item2;
		return i1 < i2 ? -1:
			i2 < i1 ? 1:
			0;
	}
	int AddItem(const unsigned char& i, const int& at = -1)
	{
		int ret = -1;
		if(i < m_cap)
		{
			if(m_hWnd)
			{
				int sel = FindItem((const void*)i);
				if(sel < 0)
				{
//					if(at > 0 && (unsigned int)at < (unsigned int)GetCount())
					if(at > 0 && (unsigned int)at < m_itemCount)
					{
						ret = InsertString(at, (const char*)i);
					}
					else
					{
						ret = AddString((const char*)i);
					}
				}
			}
			if(!(m_allItemsMask & ((FilterType)1 << i)))
			{
				m_allItemsMask |= ((FilterType)1 << i);
				ret = at >= 0 ? at : i;
			}
		}
		return ret;
	}
	const unsigned char& GetCap() const{return m_cap;}
	const unsigned char& GetLaetItem() const{return m_lastItem;}
	void SetCap(const unsigned char& cap)
	{
		if(cap != m_cap)
		{
			m_cap = cap;
			if(m_cap > sizeof(FilterType) * 8)m_cap = sizeof(FilterType) * 8;
			else if(m_cap < sizeof(FilterType) * 8)
			{
				m_maxFilter = ((FilterType)1 << m_cap) - 1;
				m_colorFilter = m_maxFilter;
			}
		}
	}
	bool RemoveItem(const unsigned char& i)
	{
		bool ret = false;
		const bool checked = isItemOrdinalChecked(i);
		if(m_hWnd)
		{
			int sel = FindItem((const void*)i);
			if(sel >= 0)
			{
				DeleteString(sel);
			}
			ret = true;
		}
		if(m_allItemsMask & ((FilterType)1 << i))
		{
			m_allItemsMask &= ~((FilterType)1 << i);
			ret = true;
		}
		m_filter &= ~((FilterType)1 << i);
		return ret;
	}
/*
	void ResetContent()
	{
		if(m_hWnd)
		{
			ListBoxOwnerDraw::ResetContent();
		}
//		m_allItemsMask = m_filter = 0;
//		m_checkCount = 0;
		OnContentReset();
	}
	virtual void OnContentReset(){}
*/
	bool SetFilter(FilterType filter)
	{
//		if(m_cap < sizeof(N) * 8)filter &= ((FilterType)1 << m_cap) - 1;
		filter &= m_maxFilter;
		if(m_filter != filter)
		{
			const bool wasAll = AreAllItemsChecked() > 1;
			const FilterType oldFilter = m_filter;

			m_filter = filter;
//			const bool invalidateAll = !m_zeroFilterValid && (!m_filter || !oldFilter);// || isAll != wasAll;
			const bool invalidateAll = !m_filter || !oldFilter;
			const bool invalidateSingle = !invalidateAll && m_hWnd;
			const int left = GetSpinCollectionTotalLeftWidth();
			const int right = left + m_itemHeight + GetCheckInvalidateWidth();
			FilterType flags;// = 1;
			void* item;
			for(unsigned char i = 0, end = m_cap < m_itemCount ? m_cap : m_itemCount; i < end; ++i)//, flags <<= 1)
			{
				item = GetItemDataPtr(i);
				flags = (FilterType)1 << (unsigned char)
#if(_MSC_VER > 1600)
					(size_t)
#endif
					item;
				if(oldFilter & flags)
				{
					if(!(filter & flags))
					{
						if(invalidateSingle)InvalidateItem(i, left, right);
						if(m_checkCount)--m_checkCount;
					}
				}
				else
				{
					if(filter & flags)
					{
						if(invalidateSingle)InvalidateItem(i, left, right);
						++m_checkCount;
					}
				}
			}
			if(m_hWnd)
			{
				if(invalidateAll || (AreAllItemsChecked() > 1) != wasAll)// && !m_partialFilterSameAsAll)
				{
					InvalidateClient();
				}
/*
				else
				{
					InvalidateRect(&CRect(0, 0, m_itemHeight, m_listBoxHeight), FALSE);
				}
*/
			}
			return true;
		}
		return false;
	}
	bool SetColorFilter(FilterType filter)
	{
		filter &= m_maxFilter;
		if(m_colorFilter != filter)
		{
			const bool wasAll = AreAllItemsChecked() > 1;
			const FilterType oldFilter = m_colorFilter;

			m_colorFilter = filter;
			const bool invalidateAll = !m_colorFilter || !oldFilter;
			const bool invalidateSingle = !invalidateAll && m_hWnd;
			const int left = GetSpinCollectionTotalLeftWidth() + m_itemHeight + GetCheckInvalidateWidth();
			const int right = -1;
			FilterType flags;// = 1;
			void* item;
			for(unsigned char i = 0, end = m_cap < m_itemCount ? m_cap : m_itemCount; i < end; ++i)//, flags <<= 1)
			{
				item = GetItemDataPtr(i);
				flags = (FilterType)1 << (unsigned char)
#if(_MSC_VER > 1600)
					(size_t)
#endif
					item;
				if(oldFilter & flags)
				{
					if(!(filter & flags))
					{
						if(invalidateSingle)InvalidateItem(i, left, right);
					}
				}
				else
				{
					if(filter & flags)
					{
						if(invalidateSingle)InvalidateItem(i, left, right);
					}
				}
			}
			if(m_hWnd)
			{
				if(invalidateAll)// || (AreAllItemsChecked() > 1) != wasAll)// && !m_partialFilterSameAsAll)
				{
					InvalidateClient();
				}
			}
			return true;
		}
		return false;
	}

	const FilterType& GetFilter() const{return m_filter;}
	const FilterType& GetAllItemsMask() const{return m_allItemsMask;}
	const FilterType& GetColorFilter() const{return m_colorFilter;}
	bool SetFilterAll()
	{
		return SetFilter(m_allItemsMask);
	}
	virtual COLORREF GetStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override
	{
		const unsigned char ordinal = (unsigned char)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			lpDrawItemStruct->itemData;
		return !(m_colorFilter & ((FilterType)1 << ordinal)) ? m_grayColor : ListBoxOwnerDraw::GetStringColor(lpDrawItemStruct);
	}
	void SetGrayColor(const COLORREF& color)
	{
		if(color != m_grayColor)
		{
			m_grayColor = color;
			if((m_colorFilter & m_maxFilter) != m_maxFilter && m_hWnd)
			{
				FilterType flags;// = 1;
				void* item;
				const int left = GetSpinCollectionTotalLeftWidth() + m_itemHeight + GetCheckInvalidateWidth();
				const int right = -1;
				for(unsigned char i = 0, end = m_cap < m_itemCount ? m_cap : m_itemCount; i < end; ++i)//, flags <<= 1)
				{
					item = GetItemDataPtr(i);
					flags = (FilterType)1 << (unsigned char)
	#if(_MSC_VER > 1600)
						(size_t)
	#endif
						item;

					if(flags & m_colorFilter)
					{
						InvalidateItem(i, left, right);
					}
				}
			}
		}
	}
protected:
	ListBoxSimpleFilter(const FilterType& allItemsMask = 0,
		const unsigned char& cap = M,
		const unsigned char& lastItem = M - 1,
		const char* const& tooltipText = nullptr,
		const bool& oneColor = false,
		const bool& reverseColor = false):
		ListBoxOwnerDraw(0, false, true, false, tooltipText),
		m_allItemsMask(allItemsMask),
		m_maxFilter((FilterType)-1),
		m_filter((FilterType)-1),
		m_colorFilter(m_maxFilter),
		m_cap(cap < M ? cap : M),
		m_lastItem(lastItem < m_cap ? lastItem : m_cap - 1),
		m_oneColor(oneColor),
		m_reverseColor(reverseColor),
		m_grayColor(RGB(128, 128, 128))
	{
		if(m_cap > sizeof(FilterType) * 8)m_cap = sizeof(FilterType) * 8;
		else if(m_cap < sizeof(FilterType) * 8)
		{
			m_maxFilter = ((FilterType)1 << m_cap) - 1;
			m_colorFilter = m_maxFilter;
		}
		m_checkable = 1;
	}
	virtual void BeforeDestroy()
	{
		ListBoxOwnerDraw::BeforeDestroy();
		m_filter = 0;
		m_colorFilter = m_maxFilter;
	}
	virtual void AfterItemsCleared() override
	{
	}
	virtual void BeforeItemDeleted(unsigned int at, bool checked) override
	{
	}
	virtual void AfterItemDeleted(unsigned int at, bool failed, bool checked) override
	{
	}
	virtual void SetItemChecked(void* item, unsigned int i, bool checked) override
	{
		const bool allChecked = AreAllItemsChecked() > 1;
		const bool invalidateAll = !m_filter;
		const FilterType flag = (FilterType)1 << (unsigned char)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			item;
		if(checked)
		{
			if(!(m_filter & flag))
			{
				m_filter |= flag;
//				++m_checkCount;
			}
		}
		else
		{
			if(m_filter & flag)
			{
				m_filter &= ~flag;
//				if(m_checkCount)--m_checkCount;
			}
		}
/*
		if(m_hWnd && (!m_zeroFilterValid && (invalidateAll != !m_filter) || allChecked != (AreAllItemsChecked() > 1)))
		{
			InvalidateClient();
		}
*/
	}
	virtual void ItemChecked(unsigned int i, bool checked) override
	{
		if(checked)
		{
//			if(1 == m_checkCount && !m_zeroFilterValid || m_itemCount == m_checkCount && !m_partialFilterSameAsAll)
			if(1 == m_checkCount || m_itemCount == m_checkCount)
			{
				InvalidateClient();
			}
		}
//		else if(!m_checkCount && !m_zeroFilterValid || m_itemCount == (m_checkCount + 1) && !m_partialFilterSameAsAll)
		else if(!m_checkCount || m_itemCount == (m_checkCount + 1))
		{
			InvalidateClient();
		}
	}
	virtual void AddMenuItems(CMenu& menu) override{AddSelectionMenuItems(menu);}
	virtual void ListBoxCreated() override
	{
		ListBoxOwnerDraw::ListBoxCreated();
		if(m_allItemsMask)
		{
			FilterType flags = 1;
			unsigned char i = 0;
			for(; i < m_lastItem; ++i, flags <<= 1)
			{
				if(m_allItemsMask & flags)
				{
					AddItem(i);
				}
			}
			for(++i, flags <<= 1; i < m_cap; ++i, flags <<= 1)
			{
				if(m_allItemsMask & flags)
				{
					AddItem(i);
				}
			}
			if(m_lastItem < m_cap)
			{
				if(m_allItemsMask & ((FilterType)1 << m_lastItem))
				{
					AddItem(m_lastItem);
				}
			}
//			m_itemCount = CListBox::GetCount();
//			UpdateTopItem(TICC_ADD_ITEM);
		}
	}
	FilterType m_allItemsMask;
	FilterType m_maxFilter;
	FilterType m_filter;
	FilterType m_colorFilter;
	unsigned char m_cap;
	unsigned char m_lastItem;
	bool m_oneColor;
	bool m_reverseColor;
//	bool m_zeroFilterValid;
//	bool m_partialFilterSameAsAll;
	COLORREF m_grayColor;
private:
	int AddString(const char* item){return ListBoxOwnerDraw::AddString(item);}
	int InsertString(int i, const char* item){return ListBoxOwnerDraw::InsertString(i, item);}
	int DeleteString(int i){return ListBoxOwnerDraw::DeleteString(i);}
//	void ResetContent(){ListBoxOwnerDraw::ResetContent();}
	bool ClearItemsWithRedraw(){return ListBoxOwnerDraw::ClearItemsWithRedraw();}
};

class UGUI_API ListBoxYesNo : public ListBoxSimpleFilter<unsigned char, 2>
{
public:
	ListBoxYesNo(const char* yes ="Yes", const char* no = "No", const char* const& tooltipText = nullptr, const bool& oneColor = false, const bool& reverseColor = false):
		ListBoxSimpleFilter(((unsigned char)1 << m) - 1, m, m - 1, tooltipText, oneColor, reverseColor),//3, 2, 1
		m_yes(yes),
		m_no(no)
	{
	}
	virtual const char* GetItemName(const void* item) const override
	{
		switch((unsigned char)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			item)
		{
			case 0:
			return m_yes;

			case 1:
			return m_no;

			default:
			return "ERR";
		}
	}
	virtual bool GetToolTipInfo(unsigned int ordinal, const void* item, std::string& tooltipText, int& left, int& right) const override
	{
		const char* tip = nullptr;
		switch((unsigned char)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			item)
		{
			case 0:
			tip = GetYesToolTip();
			break;

			case 1:
			tip = GetNoToolTip();;
			break;
		}
		if(tip)
		{
			tooltipText = tip;
			return true;
		}
		else
		{
			tooltipText.clear();
			return false;
		}
	}
	virtual const char* GetYesToolTip() const{return nullptr;}
	virtual const char* GetNoToolTip() const{return nullptr;}
protected:
	const char* m_yes;
	const char* m_no;
};

template <class N, unsigned char M = sizeof(N) * 8>
class ListBoxSimpleFilterSameColor : public ListBoxSimpleFilter<N, M>
{
//public:
//	virtual CBrush* GetBkBrush() const override{return ListBoxOwnerDraw::GetBkBrush();}
//	virtual COLORREF GetBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override{return ListBoxOwnerDraw::GetBkColor(lpDrawItemStruct);}
protected:
	ListBoxSimpleFilterSameColor(const FilterType& allItemsMask = 0,
		const unsigned char& cap = M,
		const unsigned char& lastItem = M - 1,
		const char* const& tooltipText = nullptr,
		const bool& oneColor = false,
		const bool& reverseColor = false):
		ListBoxSimpleFilter(allItemsMask, cap, lastItem, tooltipText, oneColor, reverseColor)
	{
	}
};

template <class N, unsigned char M = sizeof(N) * 8>
class ListBoxFilterString : public ListBoxSimpleFilter<N, M>
{
public:
	static const unsigned char maxCap = M;
	typedef std::vector<std::string> StringVector;
	typedef std::set<std::string> StringSet;
//	ListBoxFilterString(const unsigned char& cap = M, const bool& zeroFilterValid = false, const bool& useToolTips = false,	const char* const& tooltipText = nullptr):
//		ListBoxSimpleFilter(0, cap <= M ? cap : M, cap ? cap <= M ? cap - 1 : M - 1 : 0, zeroFilterValid, tooltipText),
	ListBoxFilterString(const unsigned char& cap = M,
		const bool& useToolTips = false,
		const char* const& tooltipText = nullptr,
		const bool& oneColor = false,
		const bool& reverseColor = false):
		ListBoxSimpleFilter(0,
			cap <= M ? cap : M,
			cap ? cap <= M ? cap - 1 : M - 1 : 0,
			tooltipText,
			oneColor, reverseColor),
		m_setEnd(m_stringSet.end()),
		m_useToolTips(useToolTips)
	{
	}
	int AddStringItem(const char& c, const unsigned char& i, const char* const& tooltip = nullptr, const int& at = -1)
	{
		char buf[2];
		*buf = c;
		*(buf + 1) = '\0';
		return AddStringItem(buf, i, tooltip, at);
	}

	int AddStringItem(const char* const& str, const unsigned char& i, const char* const& tooltip = nullptr, const int& at = -1)
	{
		int ret = -1;
		unsigned char size = (unsigned char)m_stringVector.size();
		if(size < m_cap)
		{
			std::string strStr(str);
			if(m_stringSet.find(strStr) == m_setEnd)
			{
				ret = AddItem(i, at);
				if(ret >= 0)
				{
					m_stringSet.insert(strStr);
					if(i < size)
					{
						m_stringVector[i] = std::string(str);
					}
					else
					{
						for(; size < i; ++size)
						{
							m_stringVector.push_back(std::string());
						}
						m_stringVector.push_back(std::string(str));
					}

					if(m_useToolTips)
					{
						size = (unsigned char)m_tooltipVector.size();
						if(i < size)
						{
							if(tooltip)m_tooltipVector[i] = std::string(tooltip);
							else m_tooltipVector[i].clear();
						}
						else
						{
							std::string emptyString;
							for(; size < i; ++size)
							{
								m_tooltipVector.push_back(emptyString);
							}
							m_tooltipVector.push_back(tooltip ? std::string(tooltip) : emptyString);
						}
					}
				}
			}
		}
		return ret;
	}
	int AddStringItemSameToolTip(const char* const& str, const unsigned char& i, const int& at = -1)
	{
		return AddStringItem(str, i, str, at);
	}
	virtual const char* GetItemName(const void* item) const
	{
		unsigned char i = (unsigned char)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			item;
		return i < (unsigned char)m_stringVector.size() ? m_stringVector[i].c_str() : "ERR";
	}
	unsigned char GetStringItemCount() const{return (unsigned char)m_stringSet.size();}
//	virtual void OnContentReset(){m_stringVector.clear(); m_stringSet.clear();m_tooltipVector.clear();}
protected:
	virtual void AfterItemsCleared() override
	{
		ListBoxSimpleFilter::AfterItemsCleared();
		m_stringVector.clear();
		m_stringSet.clear();
		m_tooltipVector.clear();
	}
	virtual bool GetToolTipInfo(unsigned int ordinal, const void* item, std::string& tooltipText, int& left, int& right) const
	{
		if(m_useToolTips)
		{
			unsigned char i = (unsigned char)
#if(_MSC_VER > 1600)
				(size_t)
#endif
				item;
			if(i < (unsigned char)m_stringVector.size())
			{
				if(i < (unsigned char)m_tooltipVector.size())
				{
					tooltipText = m_tooltipVector[i];
				}
				else
				{
					tooltipText.clear();
				}
				left = right = -1;
				return true;
			}
		}
		return false;
	}
	StringVector m_tooltipVector;
	StringVector m_stringVector;
	StringSet m_stringSet;
	StringSet::iterator m_setEnd;
	bool m_useToolTips;
private:
	bool RemoveItem(unsigned char i){return false;}
	int AddItem(unsigned char i, int at = -1){return ListBoxSimpleFilter::AddItem(i, at);}
};

template <class N, unsigned char M = sizeof(N) * 8>
class ListBoxFilterStringSameColor : public ListBoxFilterString<N, M>
{
public:
	ListBoxFilterStringSameColor(const unsigned char& cap = M, const bool& useToolTips = false, const char* const& tooltipText = nullptr) :
		ListBoxFilterString(cap, useToolTips, tooltipText)
	{}
	virtual CBrush* GetBkBrush() const override{return ListBoxOwnerDraw::GetBkBrush();}
	virtual COLORREF GetBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override{return ListBoxOwnerDraw::GetBkColor(lpDrawItemStruct);}
};

class UGUI_API ListBoxNamedColor : public ListBoxOwnerDraw
{
public:
	ListBoxNamedColor(const bool& own = true, const bool& rbuttonSelection = true, const bool& rbuttonMenu = true):ListBoxOwnerDraw(0, rbuttonSelection, rbuttonMenu), m_own(own){}
//	virtual int Compare(const void* item1, const void* item2) const;
	virtual const char* GetItemName(const void* item) const;
	virtual COLORREF GetStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const;//{return GetSysColor((lpDrawItemStruct->itemState & ODS_SELECTED) == 0 ? COLOR_WINDOWTEXT : COLOR_HIGHLIGHTTEXT);}
	virtual COLORREF GetBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const{return ((const NamedColor*)lpDrawItemStruct->itemData)->GetColor();}
	virtual COLORREF GetSelectedBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const{return ((const NamedColor*)lpDrawItemStruct->itemData)->GetColor();}
	virtual void DestroyItem(const void* item) const;
	virtual void* CloneItem(const void* item) const;
	virtual void ItemToString(const void* item, std::string& itemStr) const;
	bool AreAllColorsDefault() const;
	bool ShowColorDialogForSelectedColor();
	bool ShowColorDialog(unsigned int uintSel);
protected:
//	virtual void ListBoxCreated();
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect);
	virtual void AddMenuItems(CMenu& menu);
//	virtual void PostAddMenuItems(CMenu& menu);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void BeforeColorDialogShow(){}
	virtual void AfterColorDialogShow(){}
	bool m_own;
};

class UGUI_API ListBoxGraphics : public ListBoxOwnerDraw
{
public:
	ListBoxGraphics(){}
//    virtual int Compare(const void* item1, const void* item2) const;
//	int FindItemByGraphicsName(const char* name) const;
	virtual const char* GetItemName(const void* item) const override;
	virtual void DestroyItem(const void* item) const override;
//	virtual void* CloneItem(const void* item) const;
//protected:
//	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect);
};

class SymbolCheckedItem
{
public:
	SymbolCheckedItem(const unsigned __int64& symbol, const bool& checked = false):m_symbol(symbol),m_checked(checked){}
	const unsigned __int64& GetSymbol() const{return m_symbol;}
	const bool& isChecked() const{return m_checked;}
	void SetChecked(const bool& checked){m_checked = checked;}
	void ToggleCheck(){m_checked = !m_checked;}
protected:
	unsigned __int64 m_symbol;
	bool m_checked;
};

class UGUI_API ListBoxSymbolCheckedSimple : public ListBoxOwnerDraw
{
public:
	ListBoxSymbolCheckedSimple(const bool& checkable = true, const bool& rbuttonSelection = false, const bool& rbuttonMenu = false, const char* const& tooltipText = nullptr):
		ListBoxOwnerDraw(0, rbuttonSelection, rbuttonMenu, false, tooltipText),
		m_exclude(true)
	{
		if(checkable)m_checkable = 1;
	}
	virtual const char* GetItemName(const void* item) const override{return (const char*)&((const SymbolCheckedItem*)item)->GetSymbol();}
	virtual void DestroyItem(const void* item) const override;
	virtual void* CloneItem(const void* item) const override;

	virtual bool HasItemToolTips() const{return false;}

	virtual int Compare(const void* item1, const void* item2) const override;
	virtual bool isItemChecked(const void* item) const override{return ((const SymbolCheckedItem*)item)->isChecked();}
	const bool& isExclude() const{return m_exclude;}
	bool SetExclude(const bool& exclude)
	{
		if(exclude != m_exclude)
		{
			m_exclude = exclude;
			if(!m_checkCount && m_hWnd)
			{
				Invalidate(TRUE);
			}
			return true;
		}
		return false;
	}
	virtual CBrush* GetBkBrush() const override;
	virtual COLORREF GetBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override;
protected:
	virtual void BeforeItemDeleted(unsigned int at, bool checked)
	{
		ListBoxOwnerDraw::BeforeItemDeleted(at, checked);
		if(!m_exclude && checked && !m_checkCount)
		{
			Invalidate(TRUE);
		}
	}
	virtual void AfterItemsCleared() override
	{
		const bool checked = m_checkCount != 0;
		ListBoxOwnerDraw::AfterItemsCleared();
		if(!m_exclude && checked)
		{
			Invalidate(TRUE);
		}
	}
	virtual void ItemChecked(unsigned int i, bool checked) override
	{
		if(!m_exclude)
		{
			if(checked)
			{
				if(1 == m_checkCount)
				{
					Invalidate(TRUE);
				}
			}
			else if(!m_checkCount)
			{
				Invalidate(TRUE);
			}
		}
	}
	virtual void SetItemChecked(void* item, unsigned int i, bool checked) override
	{
		((SymbolCheckedItem*)item)->SetChecked(checked);
	}
	virtual void AddMenuItems(CMenu& menu) override;
	bool m_exclude;
};

class UGUI_API ListBoxSymbolChecked : public ListBoxSymbolCheckedSimple
{
public:
	ListBoxSymbolChecked(EditNoContext* const& edit = nullptr, const bool& checkable = true, const bool& appendOnly = false, const bool& rbuttonSelection = false, const bool& rbuttonMenu = false, const char* const& tooltipText = nullptr):
		ListBoxSymbolCheckedSimple(checkable, rbuttonSelection, rbuttonMenu, tooltipText),
		m_edit(edit),
		m_symbolEditMenuWidth(0),
		m_symbolSelectedMenuWidth(0),
		m_appendOnly(appendOnly)
	{
//		if(checkable)m_checkable = 1;
		m_mbuttonSelection = true;//(rbuttonSelection),
		m_rbuttonSelection = true;//(rbuttonSelection),
		m_rbuttonMenu = true;
	}
	EditNoContext* GetEdit(){return m_edit;}
	void SetEdit(EditNoContext* edit){m_edit = edit;}
protected:
	virtual void PreAddMenuItems(CMenu& menu) override;
	virtual void AddMenuItems(CMenu& menu) override;
	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) override;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	EditNoContext* m_edit;
	bool m_appendOnly;
	int m_symbolEditMenuWidth;
	int m_symbolSelectedMenuWidth;
	std::string m_symbolEdit;
	std::string m_symbolSelected;
#ifdef _DEBUG
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
#endif
	std::string m_includeMenuItem;
	std::string m_excludeMenuItem;
	std::string m_findMenuItem;
	std::string m_removeMenuItem;
};

class UGUI_API ColumnedListBox : public ListBoxOwnerDraw
{
public:
	ColumnedListBox(int itemHeight = 0, bool rbuttonSelection = false, bool rbuttonMenu = false, bool draggable = false):
		ListBoxOwnerDraw(itemHeight, rbuttonSelection, rbuttonMenu, draggable)
	{
	}
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect);

	virtual void PreDrawLine(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect){}
	virtual void DrawLine(unsigned short columnId, const void* item, UINT itemOrdinal, HDC hDC, CRect& r, unsigned int alignment) = 0;
};

class UGUI_API CDragDropListPtr : public CDragDropText
{
public:
	CDragDropListPtr(ListBoxOwnerDraw* listBox, unsigned int i):
		CDragDropText(""),
//		m_listBox(listBox),
		m_ptr(listBox->GetItemDataPtr(i)),
		m_ordinal(i),
		m_canDragOut(listBox->CanDragItemOut(i))
	{
		std::string itemStr;
		listBox->ItemToString(m_ptr, itemStr);
		m_text = itemStr.c_str();
	}
	virtual unsigned int GetOrdinal() const{return m_ordinal;}
	virtual bool CanDragOut() const{return m_canDragOut;}
	virtual void* OnGetData(){return m_ptr;}//(void*)(LPCTSTR)m_text;}
protected:
//	ListBoxOwnerDraw* m_listBox;
	void* m_ptr;
	unsigned int m_ordinal;
	bool m_canDragOut;
};


template <class V>
class StringNumber : public StringName
{
public:
	typedef V ValueType;
	StringNumber(const char* const& name, const ValueType& number):StringName(name), m_number(number){}
	StringNumber(const std::string& name, const ValueType& number):StringName(name), m_number(number){}
//	virtual ~StringNumber(){}
	const ValueType& GetNumber() const{return m_number;}
	bool SetNumber(const ValueType& number)
	{
		if(number != m_number)
		{
			m_number = number;
			return true;
		}
		return false;
	}
	void IncrementNumber(const ValueType& number){m_number += number;}
	virtual bool DecrementNumber(const ValueType& number)
	{
		m_number -= number;
		return true;
	}
protected:
//	std::string m_name;
	ValueType m_number;
};

class StringInt : public StringNumber<int>
{
public:
	StringInt(const char* const& name, const ValueType& number):StringNumber(name, number){}
	StringInt(const std::string& name, const ValueType& number):StringNumber(name, number){}
};

class UGUI_API ListBoxStringName : public ListBoxOwnerDraw
{
public:
	virtual void DestroyItem(const void* item) const override;
//	virtual void* CloneItem(const void* item) const override;
	virtual void ItemToString(const void* item, std::string& itemStr) const override{itemStr = ((const StringName*)item)->GetNameStr();}
	virtual const char* GetItemName(const void* item) const override{return ((const StringName*)item)->GetName();}
protected:
	ListBoxStringName(int itemHeight = 0, bool rbuttonSelection = false, bool rbuttonMenu = false, bool draggable = false, const char* tooltipText = nullptr) :
		ListBoxOwnerDraw(itemHeight, rbuttonSelection, rbuttonMenu, draggable, tooltipText)
	{}
//	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect);
};


class UGUI_API ListBoxStringInt : public ListBoxStringName
{
public:
	ListBoxStringInt(int itemHeight = 0, bool rbuttonSelection = false, bool rbuttonMenu = false, bool draggable = false, const char* tooltipText = nullptr):
		ListBoxStringName(itemHeight, rbuttonSelection, rbuttonMenu, draggable, tooltipText)
	{}
//	virtual void DestroyItem(const void* item) const override;
	virtual void* CloneItem(const void* item) const override;
//	virtual void ItemToString(const void* item, std::string& itemStr) const override{itemStr = ((const StringInt*)item)->GetNameStr();}
//	virtual const char* GetItemName(const void* item) const override{return ((const StringInt*)item)->GetName();}
	virtual bool SpinItem(unsigned int at, bool increment, unsigned int value, bool leftSideSpin, unsigned char ordinalSpin) override;
protected:
//	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect);
	virtual void DrawNumber(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& r) override;
};

template <class V>
class StringUnsignedNumber : public StringNumber<V>
{
public:
	StringUnsignedNumber(const char* const& name, const ValueType& number):StringNumber(name, number){}
	StringUnsignedNumber(const std::string& name, const ValueType& number):StringNumber(name, number){}
	virtual bool DecrementNumber(const ValueType& number) override
	{
		if(m_number > number)
		{
			m_number -= number;
			return true;
		}
		else if(m_number)
		{
			m_number = 0;
			return true;
		}
		return false;
	}
};

class StringUInt : public StringUnsignedNumber<unsigned int>
{
public:
	StringUInt(const char* const& name, const ValueType& number):StringUnsignedNumber(name, number){}
	StringUInt(const std::string& name, const ValueType& number):StringUnsignedNumber(name, number){}
};

class StringUChar : public StringUnsignedNumber<unsigned char>
{
public:
	StringUChar(const char* const& name, const ValueType& number):StringUnsignedNumber(name, number){}
	StringUChar(const std::string& name, const ValueType& number):StringUnsignedNumber(name, number){}
};

class UGUI_API ListBoxStringUInt : public ListBoxStringName
{
public:
	ListBoxStringUInt(int itemHeight = 0, bool rbuttonSelection = false, bool rbuttonMenu = false, bool draggable = false, const char* tooltipText = nullptr):
		ListBoxStringName(itemHeight, rbuttonSelection, rbuttonMenu, draggable, tooltipText)
	{}
//	virtual void DestroyItem(const void* item) const override;
	virtual void* CloneItem(const void* item) const override;
//	virtual void ItemToString(const void* item, std::string& itemStr) const override{itemStr = ((const StringUInt*)item)->GetNameStr();}
//	virtual const char* GetItemName(const void* item) const override{return ((const StringUInt*)item)->GetName();}
	virtual bool SpinItem(unsigned int at, bool increment, unsigned int value, bool leftSideSpin, unsigned char ordinalSpin) override;
protected:
//	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect);
	virtual void DrawNumber(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& r) override;
};

class UGUI_API ListBoxStringDate : public ListBoxStringUInt
{
public:
	ListBoxStringDate(int itemHeight = 0, bool rbuttonSelection = false, bool rbuttonMenu = false, bool draggable = false, const char* tooltipText = nullptr):
		ListBoxStringUInt(itemHeight, rbuttonSelection, rbuttonMenu, draggable, tooltipText),
		m_colorFuture(0),
		m_colorToday(RGB(96, 96, 0)),
		m_colorPast(RGB(128, 0, 0))
	{}
//	virtual void* CloneItem(const void* item) const override;
	virtual bool SpinItem(unsigned int at, bool increment, unsigned int value, bool leftSideSpin, unsigned char ordinalSpin) override;
	const COLORREF& GetColorFutue() const{return m_colorFuture;}
	const COLORREF& GetColorToday() const{return m_colorToday;}
	const COLORREF& GetColorPast() const{return m_colorPast;}
	void SetColorFuture(const COLORREF& color){SetColor(m_colorFuture, color);}
	void SetColorToday(const COLORREF& color){SetColor(m_colorToday, color);}
	void SetColorPast(const COLORREF& color){SetColor(m_colorPast, color);}
/*
	virtual COLORREF GetStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override
	{
		return (lpDrawItemStruct->itemState & ODS_SELECTED) == 0 ? GetSelectedBkColor(lpDrawItemStruct) : GetSysColor(COLOR_HIGHLIGHTTEXT);
	}

	virtual COLORREF GetUnselectedStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override
	{
		return GetSelectedBkColor(lpDrawItemStruct);
	}
*/
	virtual COLORREF GetSelectedBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override
	{
		const StringUInt* str = (const StringUInt*)lpDrawItemStruct->itemData;
		const unsigned int date = str->GetNumber();
		const unsigned int todaysDate = TL_GetTodaysDateInFullShiftFormat();
		return !date ? 0:
			date > todaysDate ? m_colorFuture :
			date < todaysDate ? m_colorPast :
			m_colorToday;
	}
protected:
	void SetColor(COLORREF& colorToSet, const COLORREF& color)
	{
		if(color != colorToSet)
		{
			colorToSet = color;
			InvalidateRectIfValid(nullptr);
//			if(m_hWnd)InvalidateRect(nullptr, FALSE);
		}
	}
	virtual void DrawNumber(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& r) override;
	COLORREF m_colorFuture;
	COLORREF m_colorToday;
	COLORREF m_colorPast;
};

class StringUInt64 : public StringUnsignedNumber<unsigned __int64>
{
public:
	StringUInt64(const char* const& name, const ValueType& number):StringUnsignedNumber(name, number){}
	StringUInt64(const std::string& name, const ValueType& number):StringUnsignedNumber(name, number){}
};

class UGUI_API ListBoxStringPrice : public ListBoxStringName
{
public:
	ListBoxStringPrice(int itemHeight = 0, bool rbuttonSelection = false, bool rbuttonMenu = false, bool draggable = false, const char* tooltipText = nullptr):
		ListBoxStringName(itemHeight, rbuttonSelection, rbuttonMenu, draggable, tooltipText)
	{}
//	virtual void DestroyItem(const void* item) const override;
	virtual void* CloneItem(const void* item) const override;
//	virtual void ItemToString(const void* item, std::string& itemStr) const override{itemStr = ((const StringUInt64*)item)->GetNameStr();}
//	virtual const char* GetItemName(const void* item) const override{return ((const StringUInt64*)item)->GetName();}
	virtual bool SpinItem(unsigned int at, bool increment, unsigned int value, bool leftSideSpin, unsigned char ordinalSpin) override;
protected:
	virtual void DrawNumber(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& r) override;
};

class StringStringItem : public StringName//item for ListBoxStringString
{
public:
	StringStringItem(const char* const& name, const char* const& value):StringName(name), m_value(value){}
	StringStringItem(const std::string& name, const std::string& value):StringName(name), m_value(value){}
	StringStringItem():StringName(""){}
	const std::string& GetValue() const{return m_value;}
/*
	const std::string& GetName() const{return m_name;}
	bool SetName(const std::string& name)
	{
		if(name != m_name)
		{
			m_name = name;
			return true;
		}
		return false;
	}
	bool SetName(const char* const& name){return SetName(std::string(name));}
*/
	bool SetValue(const std::string& value)
	{
		if(value != m_value)
		{
			m_value = value;
			return true;
		}
		return false;
	}
	bool SetValue(const char* const& value){return SetValue(std::string(value));}
	void Clear()
	{
		m_name.clear();
		m_value.clear();
	}
protected:
//	std::string m_name;
	std::string m_value;
};

class UGUI_API ListBoxStringString : public ListBoxStringName
{
public:
	ListBoxStringString(const int& itemHeight = 0, const bool& rbuttonSelection = false, const bool& rbuttonMenu = false, const bool& draggable = false, const char* tooltipText = nullptr):
		ListBoxStringName(itemHeight, rbuttonSelection, rbuttonMenu, draggable, tooltipText)
	{}
//	virtual void DestroyItem(const void* item) const override;
	virtual void* CloneItem(const void* item) const override;
//	virtual void ItemToString(const void* item, std::string& itemStr) const override{itemStr = ((const StringStringItem*)item)->GetName();}
//	virtual const char* GetItemName(const void* item) const override{return ((const StringStringItem*)item)->GetName().c_str();}
	const char* GetItemValue(const void* item) const{return ((const StringStringItem*)item)->GetValue().c_str();}
	int AddItem(const char* name, const char* value);
	int AddItem(const std::string& name, const std::string& value);
protected:
	virtual void DrawNumber(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& r) override;
};

class UGUI_API ListBoxNamePassword : public ListBoxStringString
{
public:
	ListBoxNamePassword(const char* const& passwordRepresentation = nullptr, const bool& showPassword = false, const int& itemHeight = 0, const bool& rbuttonSelection = true, const bool& rbuttonMenu = true, const bool& draggable = false, const char* tooltipText = nullptr):
		ListBoxStringString(itemHeight, rbuttonSelection, rbuttonMenu, draggable, tooltipText),
		m_passwordRepresentation(passwordRepresentation ? passwordRepresentation : ""),
		m_showPassword(showPassword)
	{}
	const bool& isShowPassword() const{return m_showPassword;}
	void SetShowPassword(const bool& showPassword)
	{
		if(showPassword != m_showPassword)
		{
			m_showPassword = showPassword;
			if(m_hWnd)
			{
				Invalidate(FALSE);
			}
		}
	}
	const std::string& GetPasswordRepresentation() const{return m_passwordRepresentation;}
	void SetPasswordRepresentation(const char* passwordRepresentation)
	{
		if(!passwordRepresentation)
		{
			passwordRepresentation = "";
		}
		if(strcmp(m_passwordRepresentation.c_str(), passwordRepresentation))
		{
			m_passwordRepresentation = passwordRepresentation;
			if(!m_showPassword && m_hWnd)
			{
				Invalidate(FALSE);
			}
		}
	}
protected:
	virtual void DrawNumber(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& r) override
	{
		if(m_showPassword)ListBoxStringString::DrawNumber(lpDrawItemStruct, r);
		else if(!m_passwordRepresentation.empty())
		{
			const StringStringItem* str = (const StringStringItem*)lpDrawItemStruct->itemData;
			if(!str->GetValue().empty())DrawText(lpDrawItemStruct->hDC, m_passwordRepresentation.c_str(), -1, &(RECT&)r, DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_NOCLIP|DT_NOPREFIX);
		}
	}
	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) override;
	virtual void AddMenuItems(CMenu& menu) override;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	std::string m_passwordRepresentation;
	bool m_showPassword;
};

class UGUI_API ColorStringItem : public StringName
{
public:
	ColorStringItem(const char* const& name = "", const COLORREF& color = 0):StringName(name), m_color(color){}
//	virtual ~ColorStringItem(){}

//	const std::string& GetName() const{return m_name;}
//	void SetName(const char* const& name){m_name = name;}
//	void SetName(const std::string& name){m_name = name;}
	const COLORREF& GetColor() const{return m_color;}
	bool SetColor(const COLORREF& color)
	{
		if(color != m_color)
		{
			m_color = color;
			return true;
		}
		return false;
	}
protected:
//	std::string m_name;
	COLORREF m_color;
};

class UGUI_API ListBoxNamedFile : public ListBoxStringName
{
public:
	virtual ~ListBoxNamedFile();
//	virtual void DestroyItem(const void* item) const override;
//	virtual const char* GetItemName(const void* item) const override;
	bool GetFileNameAt(unsigned int at, std::string& fileName, bool& fileExists) const;
	bool isFileExistsAt(unsigned int at) const;
	bool isFileExistsFromItem(const void* item) const;
	const std::string& GetFileNameFromItem(const void* item, bool& fileExists) const;
	virtual void GetFileSet(StringOrderedSet& fileSet) const = 0;
	virtual bool isRadio() const override{return m_radio;}
	bool isFileNameEmptyAt(unsigned int at) const;
	bool isFileNameEmpty(const void* item) const;
protected:
//	ListBoxNamedFile(CBitmap* unchecked, CBitmap* checked);
	ListBoxNamedFile(bool radio, const char* tooltipText = nullptr);

	int AddItem(const char* name, const char* fileName, bool fileExists);
	virtual void DrawNumber(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& r) override;
	virtual void AddMenuItems(CMenu& menu) override;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) override;
//	virtual void ListBoxCreated();
	COLORREF m_greenColor;
	COLORREF m_redColor;
//	CBitmap* m_unchecked;
//	CBitmap* m_checked;
	StringOrderedSet* m_fileSet;
	int m_maxFileNameWidth;
	bool m_radio;
private:
	void DoGetFileNameAt(unsigned int at, std::string& fileName, bool& fileExists) const;
	int AddString(const char* item){return ListBoxOwnerDraw::AddString(item);}
	int InsertString(int i, const char* item){return ListBoxOwnerDraw::InsertString(i, item);}
};

class UGUI_API ListBoxFont : public ListBoxOwnerDraw
{
public:
	ListBoxFont(BYTE charSet = ANSI_CHARSET, const char* tooltipText = nullptr);
	typedef std::map<std::string, DWORD> FontMap;
	virtual const char* GetItemName(const void* item) const override;
	BYTE GetCharSet() const{return m_charSet;}
	virtual void DestroyItem(const void* item) const override;
	virtual void* CloneItem(const void* item) const override;
	virtual void GetSelectionItemRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawItemRect) const override
	{
		GetDrawItemRect(lpDrawItemStruct, drawItemRect);
		drawItemRect.left += drawItemRect.Height() + 1;
	}
	virtual void GetHighlightItemRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawItemRect) const override
	{
		GetDrawItemRect(lpDrawItemStruct, drawItemRect);
	}
protected:
	virtual void ListBoxCreated() override;
	virtual void FinishPreSubclassWindow() override;//Called after m_itemCount is initialized
	virtual bool GetToolTipInfo(unsigned int ordinal, const void* item, std::string& tooltipText, int& left, int& right) const override;
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect) override;
	virtual void OnFontSet(CFont* font, HDC hdc) override;
	virtual void SizeChanged(bool horizontalChange, bool verticalChange) override;
	virtual void OnItemAdded(void* item, unsigned int at, bool checked) override;
	void UpdateFit();
	void UpdateFitByWidth();
	FontMap m_fontMap;
	BYTE m_charSet;
//	CBitmap* m_trueTypeBitmap;
//	CBitmap* m_trueTypeMask;
};

template <class T>
class ListBoxUInt : public ListBoxOwnerDraw
{
public:
	typedef T ValueType;
	ListBoxUInt(const bool& rbuttonSelection = false, const bool& rbuttonMenu = false, const bool& draggable = false, const char* tooltipText = nullptr):
		ListBoxOwnerDraw(0, rbuttonSelection, rbuttonMenu, draggable, tooltipText)
	{
		m_hAlignment = DT_RIGHT;
	}
	ValueType GetNumericValue(const void* const& item) const
	{
		return (ValueType)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			item;
	}

	ValueType GetNumericValueAt(const int& at) const
	{
		return GetNumericValue(GetItemDataPtr(at));
	}

	virtual int Compare(const void* item1, const void* item2) const override
	{
		const ValueType n1 = GetNumericValue(item1);
		const ValueType n2 = GetNumericValue(item2);
		return n1 < n2 ? -1 : n1 > n2 ? 1 : 0;
	}
	virtual const char* GetItemName(const void* item) const override
	{
		static char num[33];
		return U_UnsignedNumberToStrNoDecDigits(GetNumericValue(item), num, sizeof(num));
	}
	int FindItemByNumber(const ValueType& number) const
	{
		const ValueType count = m_itemCount;//GetCount();
		if(count == 0)
		{
			return -1;
		}

		if((GetStyle() & LBS_SORT) == 0 || m_doNotSort)//unsorted
		{
			for(unsigned int i = 0; i < count; ++i)
			{
				if(number == GetNumericValueAt(i))
				{
					return (int)i;
				}
			}
		}
		else
		{
			int low = 0;
			int high = count - 1;
			int middle;
			ValueType value;
			while(high >= low)
			{
			    middle = (low + high) >> 1;
				value = GetNumericValueAt(middle);
				if(number < value)
				{
					high = middle - 1;
				}
				else if(number > value)
				{
					low = middle + 1;
				}
				else
				{
					if(middle > 0)
					{
						for(--middle; middle >= 0; --middle)
						{
							if(number != GetNumericValueAt(middle))
							{
								break;
							}
						}
						return middle + 1;
					}
					return middle;
				}
			}
		}
		return -1;
	}
	int FindClosestItemByNumber(const ValueType& number) const
	{
		const unsigned int count = m_itemCount;//GetCount();
		if(count == 0)
		{
			return -1;
		}
		unsigned int closestItem = 0xFFFFFFFF;
		ValueType smallestDiff = 0xFFFFFFFF;
		ValueType diff;
		ValueType itemNumber;
		if((GetStyle() & LBS_SORT) == 0 || m_doNotSort)//unsorted
		{
			for(unsigned int i = 0; i < count; ++i)
			{
				itemNumber = GetNumericValueAt(i);
				if(itemNumber < number)
				{
					diff = number - itemNumber;
					if(diff < smallestDiff)
					{
						smallestDiff = diff;
						closestItem = i;
					}
					else if(diff == smallestDiff)
					{
						closestItem = i;
					}
				}
				else if(itemNumber > number)
				{
					diff = itemNumber - number;
					if(diff < smallestDiff)
					{
						smallestDiff = diff;
						closestItem = i;
					}
				}
				else
				{
					return (int)i;
				}
			}
		}
		else
		{
			int low = 0;
			int high = count - 1;
			int middle;
			while(high >= low)
			{
				middle = (low + high) >> 1;
				itemNumber = GetNumericValueAt(middle);
//				itemNumber = (unsigned int)
//#if(_MSC_VER > 1600)
//					(size_t)
//#endif
//					GetItemDataPtr(middle);
				if(number < itemNumber)
				{
					high = middle - 1;
					diff = itemNumber - number;
					if(diff < smallestDiff)
					{
						smallestDiff = diff;
						closestItem = middle;
					}
				}
				else if(number > itemNumber)
				{
					low = middle + 1;
					diff = number - itemNumber;
					if(diff < smallestDiff)
					{
						smallestDiff = diff;
						closestItem = middle;
					}
					else if(diff == smallestDiff)
					{
						closestItem = middle;
					}
				}
				else
				{
					if(middle > 0)
					{
						for(--middle; middle >= 0; --middle)
						{
							if(number != GetNumericValueAt(middle))
							{
								break;
							}
						}
						return middle + 1;
					}
					return middle;
				}
			}
		}
		return closestItem == 0xFFFFFFFF ? -1 : (int)closestItem;
	}
	void SelectClosestNumber(const ValueType& number, const ValueType& altNumber)
	{
		int selSize = -1;
		if(number)
		{
			selSize = FindItemByNumber(number);
		}
		if(selSize < 0)
		{
			if(altNumber)
			{
				selSize = FindItemByNumber(altNumber);
			}
			if(selSize < 0 && number)
			{
				selSize = FindClosestItemByNumber(number);
			}
		}
		if(selSize >= 0)
		{
			SetCurSel(selSize);
		}
	}

	void SetNumericValueAt(unsigned int at, const ValueType& numericValue)
	{
		if(m_hWnd && at < m_itemCount)
		{
			DoSetNumericValueAt(at, numericValue);
		}
	}

protected:
	void DoSetNumericValueAt(unsigned int at, const ValueType& numericValue)
	{
		SetItemDataPtr(at, (void*)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			numericValue);
	}
//	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect);
};

template <class T>
class ListBoxUIntHex : public ListBoxUInt<T>
{
public:
	ListBoxUIntHex(const bool& rbuttonSelection = false, const bool& rbuttonMenu = false, const bool& draggable = false):
		ListBoxUInt(rbuttonSelection, rbuttonMenu, draggable)
	{}
	virtual const char* GetItemName(const void* item) const
	{
		static char num[33];
		return U_UnsignedNumberHexToStr(GetNumericValue(item), num, sizeof(num));
	}
};

class UGUI_API ListBoxTime : public ListBoxUInt<unsigned int>
{
public:
	ListBoxTime(const bool& milliseconds = false, const bool& rbuttonSelection = false, const bool& rbuttonMenu = false, const bool& draggable = false, const char* tooltipText = nullptr):
		ListBoxUInt(rbuttonSelection, rbuttonMenu, draggable, tooltipText),
		m_milliseconds(milliseconds)
	{}
	virtual const char* GetItemName(const void* item) const;
	const bool& isMilliseconds() const{return m_milliseconds;}
	void SetMilliseconds(const bool& milliseconds)
	{
		if(milliseconds != m_milliseconds)
		{
			m_milliseconds = milliseconds;
			if(m_hWnd)Invalidate(FALSE);
		}
	}
/*
	virtual CBrush* GetBkBrush() const;
	virtual COLORREF GetBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const;
	const bool& isRelevant() const{return m_relevant;}
	void SetRelevant(const bool& relevant)
	{
		if(relevant != m_relevant)
		{
			m_relevant = relevant;
			if(m_hWnd)Invalidate(TRUE);
		}
	}
*/
protected:
	bool m_milliseconds;
};


class UGUI_API ListBoxColor : public ListBoxUInt<COLORREF>
{
public:
	ListBoxColor(const char* const& name, const bool& rbuttonSelection = true, const bool& rbuttonMenu = true, const bool& addremove = true, const bool& draggable = true, const char* tooltipText = nullptr):
		ListBoxUInt(rbuttonSelection, rbuttonMenu, draggable, tooltipText),
		m_selectionLightColor(RGB(255, 255, 255)),
		m_invalidSelectionLightColor(RGB(128, 128, 128)),
		m_addremove(addremove),
//		m_use(true),
		m_name(name)
	{
		m_selectable = false;
		m_hAlignment = DT_LEFT;
	}
	virtual COLORREF GetBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override{return (COLORREF)lpDrawItemStruct->itemData;}
	virtual bool isColorWhenInvalid() const{return true;}//When invalid, color GetDrawItemRect with GetBkColor
//	virtual COLORREF GetSelectedBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override{return (COLORREF)lpDrawItemStruct->itemData;}
//	virtual COLORREF GetInvalidColor() const override;
	/*
	virtual CBrush* GetBkBrush() const override;
	const bool& isUse() const{return m_use;}
	bool SetUse(const bool& use)
	{
		if(use != m_use)
		{
			m_use = use;
			m_selectionLightColor = use ? RGB(255, 255, 255) : RGB(128, 128, 128);
			if(m_hWnd)Invalidate(TRUE);
			return true;
		}
		return false;
	}
*/
	void SetAddRemove(const bool& addremove){m_addremove = addremove;}
	unsigned int GetColorArray(COLORREF* buf, unsigned int len, unsigned int firstColor = 0xFFFFFFFF) const;
	COLORREF GetColorAt(unsigned int at) const;
	virtual COLORREF GetColorFromItem(const void* item) const{return GetNumericValue(item);}
	void SetColorAt(unsigned int at, COLORREF color);
//	virtual void SetColorToItem(void*& item, COLORREF color) const;
	virtual int InsertColor(unsigned int at, COLORREF color){return InsertString(at, (const char*)
#if(_MSC_VER > 1600)
		(size_t)
#endif
		color);}
	virtual int AddColor(COLORREF color){return AddString((const char*)
#if(_MSC_VER > 1600)
		(size_t)
#endif
		color);}

	bool ShowColorDialogForSelectedColor();
	bool ShowColorDialog(unsigned int uintSel);
	const COLORREF& GetSelectionLightColor() const{return m_selectionLightColor;}
	void SetSelectionLightColor(const COLORREF& color)
	{
		SetSelectionColor(m_selectionLightColor, color, false);
	}
	const COLORREF& GetInvalidSelectionLightColor() const{return m_invalidSelectionLightColor;}
	void SetInvalidSelectionLightColor(const COLORREF& color)
	{
		SetSelectionColor(m_invalidSelectionLightColor, color, true);
	}
	void SetSelectionColor(COLORREF& colorToSet, const COLORREF& color, const bool& invalid)
	{
		if(color != m_invalidSelectionLightColor)
		{
			m_invalidSelectionLightColor = color;
			if(invalid == m_invalid && m_hWnd)
			{
				CRect r(0, 0, m_itemHeight / 2, m_listBoxHeight);
				::InvalidateRect(m_hWnd, &r, FALSE);
			}
		}
	}
protected:
	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) override;
	virtual void DoSetColorAt(unsigned int at, COLORREF color)
	{
		DoSetNumericValueAt(at, color);
	}
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect) override;
	virtual void AddMenuItems(CMenu& menu) override;
//	virtual void PostAddMenuItems(CMenu& menu);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	COLORREF m_selectionLightColor;
	COLORREF m_invalidSelectionLightColor;
	bool m_addremove;
//	bool m_use;
	std::string m_name;
};

template <class T>
class UGUI_API ValueColor
{
public:
	typedef T ValueType;

	ValueColor(const ValueType& value, const COLORREF& color):m_value(value),m_color(color){}
	virtual ~ValueColor(){}
	const ValueType& GetValue() const{return m_value;}
	void SetValue(const ValueType& value){m_value = value;}
	const COLORREF& GetColor() const{return m_color;}
	virtual void SetColor(COLORREF color){m_color = color;}
	virtual unsigned char GetFlags() const{return 0;}
	virtual void SetFlags(unsigned char flags){}
	virtual bool isFlagSet(unsigned char flag) const{return false;}
	virtual void SetFlag(unsigned char flag){}
	virtual void UnsetFlag(unsigned char flag){}
	void ToggleFlag(unsigned char flag)
	{
		if(isFlagSet(flag))UnsetFlag(flag);
		else SetFlag(flag);
	}
	void ToggleChecked(){ToggleFlag(1);}
	bool isChecked() const{return isFlagSet(1);}
	void SetChecked(bool checked)
	{
		if(checked)SetFlag(1);
		else UnsetFlag(1);
	}
protected:
	ValueType m_value;
	COLORREF m_color;
};

template <class T>
class UGUI_API ValueColorFlags : public ValueColor<T>
{
public:
	ValueColorFlags(const ValueType& value, const COLORREF& color):ValueColor(value, color & 0xFFFFFF), m_flags((unsigned char)(color >> 24)){}
	virtual unsigned char GetFlags() const override{return m_flags;}
	virtual void SetFlags(unsigned char flags) override{m_flags = flags;}
	virtual bool isFlagSet(unsigned char flag) const override{return (m_flags & flag) == flag;}
	virtual void SetFlag(unsigned char flag) override{m_flags |= flag;}
	virtual void UnsetFlag(unsigned char flag) override{m_flags &= ~flag;}
	virtual void SetColor(COLORREF color) override{m_color = color & 0xFFFFFF; m_flags = (unsigned char)(color >> 24);}
protected:
	unsigned char m_flags;
};

template <class T>
class ListBoxColorValue : public ListBoxColor
{
public:
	typedef T ValueType;

	ListBoxColorValue(const bool& checkable, const char* const& name, const bool& rbuttonSelection = true, const bool& rbuttonMenu = true, const char* tooltipText = nullptr):
		ListBoxColor(name, rbuttonSelection, rbuttonMenu, false, false, tooltipText)
//		m_milliseconds(milliseconds)
	{
		if(checkable)m_checkable = 1;
		m_hAlignment = DT_RIGHT;
//		m_notSelectionTextColor = GetSysColor(COLOR_WINDOWTEXT);
	}
	int AddItem(ValueType value, COLORREF color, bool forceColor)
	{
		ValueColor<T>* item = m_checkable ?
			new ValueColorFlags<T>(value, color):
			new ValueColor<T>(value, color);
		int found = FindItem(item);
		if(found < 0)
		{
			found = AddString((const char*)item);
		}
		else
		{
			delete item;
			if(forceColor)
			{
				((ValueColor<T>*)GetItemDataPtr(found))->SetColor(color);
				InvalidateItem(found);
			}
		}
		return found;
	}

	int FindValue(ValueType value) const
	{
		return FindItem(&ValueColor<T>(value, 0));
	}
	bool GetColorValueAt(unsigned int at, ValueType& value, COLORREF& color) const
	{
		if(m_hWnd && at < m_itemCount)
		{
			DoGetColorValueAt(at, value, color);
			return true;
		}
		return false;
	}
	unsigned char GetFlagsAt(unsigned int at) const
	{
		return m_hWnd && at < m_itemCount ? ((const ValueColor<T>*)GetItemDataPtr(at))->GetFlags() : 0;
	}
	void SetFlagsAt(unsigned int at, unsigned char flags)
	{
		if(m_hWnd && at < m_itemCount)//(unsigned int)GetCount())
		{
			((ValueColor<T>*)GetItemDataPtr(at))->SetFlags(flags);
		}
	}
	void AddFlagAt(unsigned int at, unsigned char flag)
	{
		if(m_hWnd && at < m_itemCount)//(unsigned int)GetCount())
		{
			((ValueColor<T>*)GetItemDataPtr(at))->SetFlag(flag);
		}
	}
	void RemoveFlagAt(unsigned int at, unsigned char flag)
	{
		if(m_hWnd && at < m_itemCount)//(unsigned int)GetCount())
		{
			((ValueColor<T>*)GetItemDataPtr(at))->UnsetFlag(flag);
		}
	}
	void ToggleFlagAt(unsigned int at, unsigned char flag)
	{
		if(m_hWnd && at < m_itemCount)//(unsigned int)GetCount())
		{
			((ValueColor<T>*)GetItemDataPtr(at))->ToggleFlag(flag);
		}
	}
	virtual COLORREF GetColorFromItem(const void* item) const override
	{
		return ((const ValueColor<T>*)item)->GetColor();
	}
	bool GetSelectedColorValue(ValueType& value, COLORREF& color) const
	{
		if(m_hWnd)
		{
			const int sel = GetCurSel();
			if(sel >= 0)
			{
				DoGetColorValueAt((unsigned int)sel, value, color);
				return true;
			}
		}
		return false;
	}
	virtual COLORREF GetStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override
	{
		return UGUI_GetOppositeColor(GetBkColor(lpDrawItemStruct));
	}
	virtual COLORREF GetBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override
	{
		return ((ValueColor<T>*)lpDrawItemStruct->itemData)->GetColor();
	}
	virtual COLORREF GetSelectedBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override
	{
		return ((ValueColor<T>*)lpDrawItemStruct->itemData)->GetColor();
	}

	virtual void DestroyItem(const void* item) const override
	{
		delete (ValueColor<T>*)item;
	}
	virtual int Compare(const void* item1, const void* item2) const override
	{
		ValueType v1 = ((ValueColor<T>*)item1)->GetValue();
		ValueType v2 = ((ValueColor<T>*)item2)->GetValue();
		return v1 < v2 ? -1 : v1 > v2 ? 1 : 0;
	}
//	virtual const char* GetItemName(const void* item) const override;
/*
	const bool& isMilliseconds() const{return m_milliseconds;}
	void SetMilliseconds(const bool& milliseconds)
	{
		if(milliseconds != m_milliseconds)
		{
			m_milliseconds = milliseconds;
			if(m_hWnd)
			{
				Invalidate(FALSE);
			}
		}
	}
*/
	virtual int InsertColor(unsigned int at, COLORREF color) override
	{
		ValueColor<T>* item = m_checkable ?
			new ValueColorFlags<T>(0, color) :
			new ValueColor<T>(0, color);
		return InsertString(at, (const char*)item);
	}
	virtual int AddColor(COLORREF color) override
	{
		ValueColor<T>* item = m_checkable ?
			new ValueColorFlags<T>(0, color) :
			new ValueColor<T>(0, color);
		return AddString((const char*)item);
	}
	virtual bool isItemChecked(const void* item) const override
	{
		return ((const ValueColor<T>*)item)->isChecked();
	}
	unsigned char GetItemFlags(const void* item) const
	{
		return ((const ValueColor<T>*)item)->GetFlags();
	}
	void SetItemFlags(void* item, unsigned char flags)
	{
		((ValueColor<T>*)item)->SetFlags(flags);
	}
	bool isItemFlagSet(const void* item, unsigned char flag) const
	{
		return ((const ValueColor<T>*)item)->isFlagSet(flag);
	}
	void SetItemFlag(void* item, unsigned char flag)
	{
		((ValueColor<T>*)item)->SetFlag(flag);
	}
	void ToggleItemFlag(void* item, unsigned char flag)
	{
		((ValueColor<T>*)item)->ToggleFlag(flag);
	}
protected:
	virtual void SetItemChecked(void* item, unsigned int i, bool checked) override
	{
		((ValueColor<T>*)item)->SetChecked(checked);
	}
	virtual void DoSetColorAt(unsigned int at, COLORREF color) override
	{
		((ValueColor<T>*)GetItemDataPtr(at))->SetColor(color);
	}
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect) override
	{
		ListBoxOwnerDraw::DoDrawItem(lpDrawItemStruct, drawItemRect);
		ListBoxColor::DoDrawItem(lpDrawItemStruct, drawItemRect);
	}
	virtual void AddMenuItems(CMenu& menu) override
	{
		ListBoxColor::AddMenuItems(menu);
		AddSelectionMenuItems(menu);
	}
	//	bool m_milliseconds;
private:
	void DoGetColorValueAt(unsigned int at, ValueType& value, COLORREF& color) const
	{
		const ValueColor<T>* item = (const ValueColor<T>*)GetItemDataPtr(at);
		value = item->GetValue();
		color = item->GetColor();
	}
	int AddString(const char* item){return ListBoxOwnerDraw::AddString(item);}
	int InsertString(int i, const char* item){return ListBoxOwnerDraw::InsertString(i, item);}
};


class UGUI_API ListBoxColorTime : public ListBoxColorValue<unsigned int>//ListBoxColor
{
public:
	ListBoxColorTime(const bool& checkable, const bool& milliseconds, const char* const& name, const bool& rbuttonSelection = true, const bool& rbuttonMenu = true, const char* tooltipText = nullptr):
		ListBoxColorValue(checkable, name, rbuttonSelection, rbuttonMenu, tooltipText),
		m_milliseconds(milliseconds)
	{
//		if(checkable)m_checkable = 1;
//		m_hAlignment = DT_RIGHT;
	}
/*
	int AddItem(unsigned int millisecond, COLORREF color, bool forceColor);
	int FindTime(unsigned int millisecond) const;
	bool GetColorTimeAt(unsigned int at, unsigned int& millisecond, COLORREF& color) const;
	unsigned char GetFlagsAt(unsigned int at) const;
	void SetFlagsAt(unsigned int at, unsigned char flags);
	void AddFlagAt(unsigned int at, unsigned char flag);
	void RemoveFlagAt(unsigned int at, unsigned char flag);
	void ToggleFlagAt(unsigned int at, unsigned char flag);
	virtual COLORREF GetColorFromItem(const void* item) const override;
	bool GetSelectedColorTime(unsigned int& millisecond, COLORREF& color) const;
	virtual COLORREF GetStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override;
	virtual COLORREF GetBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override;
	virtual COLORREF GetSelectedBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override;

	virtual void DestroyItem(const void* item) const override;
	virtual int Compare(const void* item1, const void* item2) const override;
*/
	virtual const char* GetItemName(const void* item) const override
	{
		static char num[33];
		U_FormatMillisecond(((const ValueColor<ValueType>*)item)->GetValue(), num, sizeof(num), '\0', m_milliseconds);
		return num;
	}

	const bool& isMilliseconds() const{return m_milliseconds;}
	void SetMilliseconds(const bool& milliseconds)
	{
		if(milliseconds != m_milliseconds)
		{
			m_milliseconds = milliseconds;
			if(m_hWnd)
			{
				Invalidate(FALSE);
			}
		}
	}
/*
	virtual int InsertColor(unsigned int at, COLORREF color) override;
	virtual int AddColor(COLORREF color) override;
	virtual bool isItemChecked(const void* item) const override;
	unsigned char GetItemFlags(const void* item) const;
	void SetItemFlags(void* item, unsigned char flags);
	bool isItemFlagSet(const void* item, unsigned char flag) const;
	void SetItemFlag(void* item, unsigned char flag);
	void ToggleItemFlag(void* item, unsigned char flag);
*/
protected:
//	virtual void SetItemChecked(void* item, unsigned int i, bool checked) override;
//	virtual void DoSetColorAt(unsigned int at, COLORREF color) override;
//	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect) override;
//	virtual void AddMenuItems(CMenu& menu) override;
	bool m_milliseconds;
//private:
//	void DoGetColorTimeAt(unsigned int at, unsigned int& millisecond, COLORREF& color) const;
//	int AddString(const char* item){return ListBoxOwnerDraw::AddString(item);}
//	int InsertString(int i, const char* item){return ListBoxOwnerDraw::InsertString(i, item);}
};

class UGUI_API ListBoxColorMoney : public ListBoxColorValue<Money>
{
public:
	ListBoxColorMoney(const bool& checkable, const bool& milliseconds, const char* const& name, const bool& rbuttonSelection = true, const bool& rbuttonMenu = true, const char* tooltipText = nullptr):
		ListBoxColorValue(checkable, name, rbuttonSelection, rbuttonMenu, tooltipText)
	{
//		if(checkable)m_checkable = 1;
//		m_hAlignment = DT_RIGHT;
	}
	virtual const char* GetItemName(const void* item) const override
	{
		static std::string str;
		U_MoneyToStr(str, ((const ValueColor<ValueType>*)item)->GetValue(), 2);// , '\0', true, '\0', false);
		return str.c_str();
	}
};

class UGUI_API ListBoxColorString : public ListBoxStringName
{
public:
	ListBoxColorString(COLORREF* customColors = nullptr, unsigned int customColorCount = 0, COLORREF bkColor = 0xFFFFFFFF, int itemHeight = 0, bool rbuttonSelection = false, bool rbuttonMenu = false, bool draggable = false, const char* tooltipText = nullptr);
	virtual ~ListBoxColorString(){SetBkColor(0xFFFFFFFF);}
	virtual COLORREF GetStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override{return ((const ColorStringItem*)lpDrawItemStruct->itemData)->GetColor();}
//	virtual void DestroyItem(const void* item) const override;
//	virtual void* CloneItem(const void* item) const;
//	virtual void ItemToString(const void* item, std::string& itemStr) const;
//	virtual const char* GetItemName(const void* item) const override{return ((const ColorStringItem*)item)->GetName().c_str();}
	virtual CBrush* GetBkBrush() const override{return m_brush;}
	virtual COLORREF GetBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override{return m_bkColor == 0xFFFFFFFF ? ListBoxOwnerDraw::GetBkColor(lpDrawItemStruct) : m_bkColor;}
	virtual COLORREF GetSelectedBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override{return m_bkColorSelected;}
	virtual void GetDrawItemRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawItemRect) const override
	{
		ListBoxOwnerDraw::GetDrawItemRect(lpDrawItemStruct, drawItemRect);
		drawItemRect.left += drawItemRect.Height();
	}
	virtual void GetFocusItemRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawItemRect) const override
	{
		ListBoxOwnerDraw::GetDrawItemRect(lpDrawItemStruct, drawItemRect);
	}
	virtual void GetSelectionItemRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawItemRect) const override
	{
		ListBoxOwnerDraw::GetDrawItemRect(lpDrawItemStruct, drawItemRect);
		drawItemRect.right = drawItemRect.left + drawItemRect.Height();
	}
	virtual bool isPointForRButtonMenuOk(UINT nFlags, CPoint point) const override;
	void SetBkColor(COLORREF color);
	COLORREF* GetColorArray(unsigned int& custCount) const{custCount = m_customColorCount; return m_customColors;}
protected:
	virtual void AddMenuItems(CMenu& menu);
	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) override;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	COLORREF m_bkColor;
	COLORREF m_bkColorSelected;
	CBrush* m_brush;
	COLORREF* m_customColors;
	unsigned int m_customColorCount;
};

class UGUI_API ListBoxOrdinal : public ListBoxOwnerDraw
{
protected:
	ListBoxOrdinal(const int& itemHeight = 0, const bool& rbuttonSelection = false, const bool& rbuttonMenu = false, const bool& draggable = false, const char* tooltipText = nullptr):
		ListBoxOwnerDraw(itemHeight, rbuttonSelection, rbuttonMenu, draggable, tooltipText)
	{}
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect) override;
};

class UGUI_API ListBoxIp : public ListBoxUInt<unsigned int>
{
public:
	ListBoxIp(const char* tooltipText = nullptr):
		ListBoxUInt(false, false, false, tooltipText)
	{
		m_hAlignment = DT_LEFT;
	}
protected:
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect) override;
};

class UGUI_API ListBoxString : public ListBoxOwnerDraw
{
public:
	ListBoxString(const bool& own = true, const int& itemHeight = 0, const bool& rbuttonSelection = false, const bool& rbuttonMenu = false, const bool& draggable = false, const char* tooltipText = nullptr):
		ListBoxOwnerDraw(itemHeight, rbuttonSelection, rbuttonMenu, draggable, tooltipText),
		m_own(own)
	{}
//	typedef std::set<unsigned int> UIntSet;
//	virtual int Compare(const void* item1, const void* item2) const;
//	virtual COLORREF GetStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const{return GetSysColor((lpDrawItemStruct->itemState & ODS_SELECTED) == 0 ? COLOR_WINDOWTEXT : COLOR_HIGHLIGHTTEXT);}
	virtual void DestroyItem(const void* item) const override;
	virtual void* CloneItem(const void* item) const override;
	virtual void* CreateItemFromString(const char* str) const override{return U_CopyString(str);}
	virtual void ItemToString(const void* item, std::string& itemStr) const override;
	virtual const char* GetItemName(const void* item) const override{return (const char*)item;}
	int AddStringItem(const char* item);
	int InsertStringItem(int at, const char* item);
//	static char* CopyString(const char* str);
protected:
//	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct);
	bool m_own;
};

template <class T>
class ListBoxStringAsUInt : public ListBoxString
{
public:
	typedef T ValueType;
	ListBoxStringAsUInt(const bool& zeroValid,
		const bool& supportClipboard,// = false,
		const int& itemHeight,// = 0,
		const bool& rbuttonSelection,// = false,
		const bool& rbuttonMenu,// = false,
		const bool& draggable,// = false,
		const bool& zeroAlways,// = true,
		const char* tooltipText):// = nullptr):

		ListBoxString(false, itemHeight, rbuttonSelection, rbuttonMenu, draggable, tooltipText),
		m_numRef(*(ValueType*)m_num),
		m_zeroValid(zeroValid),
		m_supportClipboard(supportClipboard),
		m_zeroAlways(zeroAlways)
	{
		m_num[sizeof(ValueType)] = '\0';
	}

	const bool& isZeroAlways() const{return m_zeroAlways;}
	int SetZeroAlways(const bool& zeroAlways)
	{
		if(zeroAlways != m_zeroAlways)
		{
			m_zeroAlways = zeroAlways;
			if(zeroAlways)
			{
				bool added;
				int ret = AddUniqueItem(0, added);
				return added ? ret : -1;
			}
			return -1;
		}
		return -2;
	}
	virtual int Compare(const void* item1, const void* item2) const override
	{
		return U_CompareUIntAsString((const ValueType&)item1, (const ValueType&)item2);
	}

	virtual void DestroyItem(const void* item) const override{}
//	virtual void* CloneItem(const void* item) const{return (void*)item;}
	virtual void ItemToString(const void* item, std::string& itemStr) const override
	{
		U_AppendUnsignedNumberAsString(itemStr, (const ValueType&)item);
	}
	virtual const char* GetItemName(const void* item) const override
	{
		m_numRef = GetNumericValue(item);
		return m_num;
	}

	ValueType GetNumericValue(const void* const& item) const
	{
		return (ValueType)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			item;
	}

	ValueType GetNumericValueAt(const int& at) const
	{
		return GetNumericValue(GetItemDataPtr(at));
	}

	int InsertNumericValue(const int& i, const ValueType& item)
	{
		unsigned char added;
		return InsertItem(i, item, true, added);
	}
	virtual int InsertItem(const int& i, const ValueType& item, const bool move, unsigned char& added)
	{
		if(i < 0 || (unsigned int)i >= m_itemCount || (GetStyle() & LBS_SORT) != 0 && !m_doNotSort)//sorted
		{
			return AddItem(item, move, added);//AddItem(item);
		}
		else//unsorted
		{
			int ret = FindItem((const void*)
#if(_MSC_VER > 1600)
				(size_t)
#endif
				item);
			if(ret < 0)
			{
				ret = ListBoxString::InsertString(i, (const char*)
#if(_MSC_VER > 1600)
					(size_t)
#endif
					item);
				added = ret < 0 ? 0 : 1;
			}
			else if(move && MoveItem(ret, i, false))
			{
				added = 2;
				ret = i;
			}
			else
			{
				added = 0;
			}
			return ret;
		}
	}
	int AddNumericValue(const ValueType& item)
	{
		unsigned char added;
		return AddItem(item, false, added);
	}
	virtual int AddItem(const ValueType& item, const bool move, unsigned char& added)//unique = 1 - unique item, 2 - move existing
	{
		int ret = FindItem((const void*)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			item);
		if(ret < 0)
		{
			ret = ListBoxString::AddString((const char*)
#if(_MSC_VER > 1600)
				(size_t)
#endif
				item);
			added = ret < 0 ? 0 : 1;
		}
		else if(move && MoveItem(ret, m_itemCount, false))
		{
			added = 2;
			ret = m_itemCount - 1;
		}
		else
		{
			added = 0;
		}
		return ret;
	}

	virtual bool CanRemoveSelectedItem() const override
	{
		const int sel = GetCurSel();
		return sel >= 0 && (!m_zeroAlways || GetNumericValueAt(sel) != 0);
	}
	virtual bool CanClearItems() const override
	{
		return m_zeroAlways ? m_itemCount > 1 : m_itemCount > 0;
	}
	int RemoveItemAt(const int& i)
	{
//		if(i >= 0 && (unsigned int)i < (unsigned int)GetCount())
		if(i >= 0 && (unsigned int)i < m_itemCount)
		{
			DoRemoveItemAt(i);
			return i;
		}
		return -1;
	}
	int RemoveItem(const ValueType& item)
	{
		int found = FindItem((const void*)item);
		if(found >= 0)
		{
			DoRemoveItem(item, found);
			return found;
		}
		return -1;
	}
	bool RemoveAll()
	{
		return ClearItems(true);
	}
	bool ClearItems(bool useRedraw)
	{
		if(m_hWnd && m_itemCount)
		{
			if(m_zeroAlways)
			{
				if(m_itemCount > 1)
				{
					return DoClearItemsExceptZeroItem(useRedraw);
				}
			}
			else
			{
				DoClearItems(useRedraw);
				return true;
			}
		}
		return false;
	}
	virtual void* CreateItemFromString(const char* str) const override
	{
		return (void*)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			U_RepresentStringAsUnsignedNumber<ValueType>(str, sizeof(ValueType));
	}
	virtual int AddCreatedItem(void* item, bool checked) override
	{
		unsigned char added;
		int ret = AddItem((const ValueType&)item, false, added);
		if(m_checkable && ret >= 0 && isItemChecked(item) != checked)// && checked)
		{
			SetItemChecked(item, ret, checked);
		}
		return ret;
	}
	virtual bool AllowEmptyName() const override{return m_zeroValid;}
	virtual void ClearBeforeReplace() override{ClearItems(false);}
protected:
	virtual bool RemoveSelectedItemOnMenuCommand(int sel) override
	{
		return RemoveItemAt(sel) >= 0;
	}
	virtual bool ClearItemsOnMenuCommand() override
	{
		return ClearItems(true);
	}
	virtual void ListBoxCreated() override
	{
		ListBoxString::ListBoxCreated();
		if(m_zeroAlways)
		{
			unsigned char added;
			AddItem(0, false, added);
		}
	}
	bool DoRemoveItemAt(const int& i)
	{
		return DoRemoveItem(GetNumericValueAt(i), i);
	}
	virtual bool DoRemoveItem(const ValueType& item, const int& i)
	{
		if(!m_zeroAlways || item != 0)
		{
			DeleteString(i);
			return true;
		}
		return false;
	}
	virtual void DoClearItems(bool useRedraw)
	{
		if(useRedraw)
		ClearItemsWithRedraw();
		else
		ResetContent();
	}

	virtual bool DoClearItemsExceptZeroItem(bool useRedraw)
	{
		bool ret = false;
		ValueType value;

		if(useRedraw)SetRedraw(FALSE);
		if(isSortedByName())
		{
			for(unsigned int i = m_itemCount - 1; i; --i)
			{
				value = GetNumericValueAt(i);
				if(value)
				{
					DeleteString(i);
					ret = true;
				}
			}
		}
		else
		{
			for(unsigned int i = 0; i < m_itemCount;)
			{
				value = GetNumericValueAt(i);
				if(value)
				{
					DeleteString(i);
					ret = true;
				}
				else
				{
					++i;
				}
			}
		}
		if(useRedraw)
		{
			SetRedraw(TRUE);
			Invalidate(FALSE);
		}
		return ret;
	}

	virtual void AddMenuItems(CMenu& menu) override
	{
		ListBoxString::AddMenuItems(menu);
		AddInOutMenuItems(menu);
	}
	virtual void PostAddMenuItems(CMenu& menu) override
	{
		ListBoxString::PostAddMenuItems(menu);
		if(m_supportClipboard)
		{
//			if(menu.GetMenuItemCount() > 0)menu.AppendMenu(MF_SEPARATOR);
			AddClipboardMenuItems(menu);
		}
	}
	char m_num[sizeof(ValueType) + 1];
	ValueType& m_numRef;
	bool m_zeroValid;
	bool m_supportClipboard;
	bool m_zeroAlways;
//private:
	int AddString(const char* item){return ListBoxString::AddString(item);}
	int InsertString(int i, const char* item){return ListBoxString::InsertString(i, item);}
	int DeleteString(int i){return ListBoxString::DeleteString(i);}
	void ResetContent(){ListBoxString::ResetContent();}
};

template <class T>
class ListBoxStringAsUIntChecked : public ListBoxStringAsUInt<T>
{
public:
	ListBoxStringAsUIntChecked(const bool& zeroAlways,// = false,
		const bool& zeroValid,// = false,
		const bool& initialZeroChecked,// = true,
		const bool& supportClipboard,// = false,
		const int& itemHeight,// = 0,
		const bool& rbuttonSelection,// = false,
		const bool& rbuttonMenu,// = false,
		const bool& draggable,// = false,
		const char* const& tooltipText):// = nullptr):
		ListBoxStringAsUInt(zeroValid, supportClipboard, itemHeight, rbuttonSelection, rbuttonMenu, draggable, zeroAlways, tooltipText),
		m_checkedSetEnd(m_checkedSet.cend()),
		m_checkedMapEnd(m_checkedMap.cend()),
		m_initialZeroChecked(initialZeroChecked)
	{
		m_checkable = 1;
	}
	typedef std::map<ValueType, bool, lessUIntAsStr<ValueType> > SortedStringMap;
	typedef std::set<ValueType> StringSet;
	const SortedStringMap& GetCheckedMap() const{return m_checkedMap;}
	const StringSet& GetCheckedSet() const{return m_checkedSet;}
	virtual bool isItemChecked(const void* item) const
	{
		return m_checkedSet.find(GetNumericValue(item)) != m_checkedSetEnd;
	}
	int AddItemChecked(const ValueType& item, const bool& checked, const bool& move, unsigned char& added)//added = 1 - unique item, 2 - move existing, 4 - checked changed
	{
		const bool insertedChecked = checked && m_checkedSet.insert(item).second;
		int ret = ListBoxStringAsUInt::AddItem(item, move, added);
		if(ret >= 0)
		{
			if(insertedChecked)added |= 4;
			SortedStringMap::iterator it = m_checkedMap.insert(SortedStringMap::value_type(item, checked)).first;
			if(checked != it->second)
			{
				it->second = checked;
			}
		}
		else if(insertedChecked)
		{
			m_checkedSet.erase(item);
		}
		return ret;
	}
	int InsertItemChecked(const int& i, const ValueType& item, const bool& checked, const bool& move, unsigned char& added)//added = 1 - added unique item, 2 - move existing, 4 - checked changed
	{
		int ret = ListBoxStringAsUInt::InsertItem(i, item, move, added);
		if(ret >= 0)
		{
			if(checked && m_checkedSet.insert(item).second)added |= 4;
			SortedStringMap::iterator it = m_checkedMap.insert(SortedStringMap::value_type(item, checked)).first;
			it->second = checked;
		}
		return ret;
	}

	virtual int AddItem(const ValueType& item, const bool move, unsigned char& added) override//added = 1 - unique item, 2 - move existing, 4 - checked changed
	{
		return AddItemChecked(item, true, move, added);
	}
	virtual int InsertItem(const int& i, const ValueType& item, const bool move, unsigned char& added) override//added = 1 - unique item, 2 - move existing, 4 - checked changed
	{
		return InsertItemChecked(i, item, true, move, added);
	}

	virtual int AddCreatedItem(void* item, bool checked) override
	{
		unsigned char added;
		return AddItemChecked((const ValueType&)item, checked, false, added);
	}
/*
	virtual unsigned char AreAllItemsChecked() const override//0 - none; 1 - not all; 2 - all
	{
		unsigned int checkedCount = (unsigned int)m_checkedSet.size();
		return !checkedCount ? 0:
			checkedCount < (unsigned int)m_checkedMap.size() ? 1:
			2;
	}
*/
protected:
	virtual void SetItemChecked(void* item, unsigned int i, bool checked) override
	{
		const ValueType val = GetNumericValue(item);
		if(checked)
		{
			if(m_checkedSet.insert(val).second)
			{
				SortedStringMap::iterator found = m_checkedMap.find(val);
				if(found != m_checkedMapEnd)found->second = checked;
			}
		}
		else
		{
			if(m_checkedSet.erase(val))
			{
				SortedStringMap::iterator found = m_checkedMap.find(val);
				if(found != m_checkedMapEnd)found->second = checked;
			}
		}
	}
//	virtual bool CanAddItem() const override{return true;}
//	virtual int AddItemOnMenuCommand() override{return -1;}
	virtual bool RemoveSelectedItemOnMenuCommand(int sel) override{return RemoveItemAt(sel) >= 0;}
	virtual bool ClearItemsOnMenuCommand() override{return RemoveAll();}
/*
	virtual bool DoRemoveItemAt(const int& i) override
	{
		return DoRemoveItem((ValueType)GetItemDataPtr(i), i);
	}
*/
	virtual bool DoRemoveItem(const ValueType& item, const int& i) override
	{
		if(ListBoxStringAsUInt::DoRemoveItem(item, i))
		{
			m_checkedSet.erase(item);
			m_checkedMap.erase(item);
			return true;
		}
		return false;
	}
	virtual void DoClearItems(bool useRedraw) override
	{
		ListBoxStringAsUInt::DoClearItems(useRedraw);
		m_checkedSet.clear();
		m_checkedMap.clear();
	}

	virtual bool DoClearItemsExceptZeroItem(bool useRedraw) override
	{
		if(ListBoxStringAsUInt::DoClearItemsExceptZeroItem(useRedraw))
		{
			const SortedStringMap::const_iterator found = m_checkedMap.find(0);
			m_checkedSet.clear();
			if(found == m_checkedMapEnd)
			{
				m_checkedMap.clear();
			}
			else
			{
				const SortedStringMap::value_type valueZero = *found;
				m_checkedMap.clear();

				m_checkedMap.insert(valueZero);
				if(valueZero.second)
				m_checkedSet.insert(valueZero.first);
			}
			return true;
		}
		return false;
	}
	virtual void AddMenuItems(CMenu& menu) override
	{
//		if(AddSelectionMenuItems(menu))menu.AppendMenu(MF_SEPARATOR);
		AddSelectionMenuItems(menu);
		ListBoxStringAsUInt::AddMenuItems(menu);
	}
	virtual void ListBoxCreated() override
	{
		m_checkedSet.clear();
		m_checkedMap.clear();
//		ListBoxStringAsUInt::ListBoxCreated();
		ListBoxString::ListBoxCreated();
		if(m_zeroAlways)
		{
			AddCreatedItem(nullptr, m_initialZeroChecked);
//			unsigned char added;
//			AddItem(0, false, added);
		}
	}
	StringSet m_checkedSet;
	typename StringSet::const_iterator m_checkedSetEnd;

	SortedStringMap m_checkedMap;
	typename SortedStringMap::const_iterator m_checkedMapEnd;

	bool m_initialZeroChecked;
private:
	void ResetContent(){return ListBoxStringAsUInt::ResetContent();}
};

class UGUI_API ListBoxStringBold : public ListBoxString
{
public:
	ListBoxStringBold(const bool& own = true,
		const int& itemHeight = 0,
		const bool& rbuttonSelection = false,
		const bool& rbuttonMenu = false,
		const bool& draggable = false,
		const bool& useBoldFont = true,
		const char* const& tooltipText = nullptr,
		const bool& radio = false):
		ListBoxString(own, itemHeight, rbuttonSelection, rbuttonMenu, draggable, tooltipText),
//		m_font(nullptr),
		m_fontBold(nullptr),
		m_itemBold(-1),
		m_useBoldFont(useBoldFont),
		m_radio(radio)
	{}
//	void SetFontBold(CFont* font){m_fontBold = font;}
	void SetItemBold(const int& itemBold){m_itemBold = itemBold;}
	void SetItemBold(const void* const& itemBold){m_itemBold = itemBold ? FindItem(itemBold) : -1;}
//	CFont* const& GetFontNormal() const{return m_font;}
	virtual CFont* GetFontBold() const override{return m_fontBold;}
	const int& GetItemBold() const{return m_itemBold;}
//	virtual void SetFont(CFont* font);
	virtual bool isRadio() const override{return m_radio;}
	virtual void SetRadio(bool radio) override
	{
		if(radio != m_radio)
		{
			m_radio = radio;
		}
	}
protected:
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect)
	{
		HGDIOBJ oldFont = lpDrawItemStruct->itemID == m_itemBold && m_fontBold ? SelectObject(lpDrawItemStruct->hDC, *m_fontBold) : nullptr;
		ListBoxString::DoDrawItem(lpDrawItemStruct, drawItemRect);
		if(oldFont)SelectObject(lpDrawItemStruct->hDC, oldFont);
	}
	virtual void GetDrawItemRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawItemRect) const override
	{
		ListBoxString::GetDrawItemRect(lpDrawItemStruct, drawItemRect);
		if(m_radio)
		{
			drawItemRect.left += lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top;
		}
	}
	virtual void DrawNumber(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& r) override
	{
		if(m_radio)
		{
			CRect rect(3, r.top + 1, r.Height(), r.bottom - 1);
			const COLORREF stringColor = GetCheckColor(lpDrawItemStruct);
			UGUI_DrawRadio(lpDrawItemStruct->hDC, rect, 1, stringColor, false, m_checkHighlightColor, lpDrawItemStruct->itemID == m_itemBold, stringColor, 0xFFFFFFFF);
		}
	}
	void InitFont()
	{
		m_fontBold = m_useBoldFont && m_font ? GetTakionBoldFont(m_font) : nullptr;
	}
	virtual void ListBoxCreated() override
	{
		ListBoxOwnerDraw::ListBoxCreated();
		InitFont();
	}
	virtual void OnFontSet(CFont* font, HDC hdc) override
	{
		ListBoxString::OnFontSet(font, hdc);
		InitFont();
	}
//	CFont* m_font;
	CFont* m_fontBold;
	int m_itemBold;
	bool m_useBoldFont;
	bool m_radio;
};

class UGUI_API ListBoxProperty : public ListBoxOwnerDraw
{
public:
	ListBoxProperty(const int& nameWidth,
		const int& nameValueGap,
		const int& valuePad,
		CFont* const& nameFont,
		CFont* const& valueFont,
		CFont* const& valueBoldFont,
		const COLORREF& nameColor,
		const COLORREF& bkColor,
		const int& itemHeight = 0,
		const char* const& tooltipText = nullptr):
		ListBoxOwnerDraw(itemHeight, false, false, false, tooltipText),
		m_nameWidth(nameWidth),
		m_nameValueGap(nameValueGap),
		m_valuePad(valuePad),
		m_valueWidth(0),
		m_nameFont(nameFont),
		m_valueFont(valueFont),
		m_valueBoldFont(valueBoldFont),
		m_nameColor(nameColor),
		m_bkColor(bkColor)
	{
		m_selectable = false;
	}
	virtual COLORREF GetBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const;
//	virtual COLORREF GetSelectedBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const;
	virtual const char* GetItemName(const void* item) const;
	const char* GetItemValue(const void* item) const;
	int AddProperty(const char* name, const char* value, COLORREF valueColor, bool bold);
	int InsertProperty(unsigned int at, const char* name, const char* value, COLORREF valueColor, bool bold);
	bool InsertBeforeProperty(const char* beforeName, bool after, const char* name, const char* value, COLORREF valueColor, bool bold);
	virtual void DestroyItem(const void* item) const;
	virtual void* CloneItem(const void* item) const;
	bool SetPropertyValue(const char* name, const char* value, COLORREF valueColor, char bold);
	bool SetPropertyValueAt(int at, const char* value, COLORREF valueColor, char bold);
	bool SetPropertyValueColorAt(int at, COLORREF valueColor);
	bool SetPropertyValueBoldAt(int at, char bold);
	virtual bool isItemHighlightedBySearchTokens(const void* item) const{return HasSearchRank(m_searchTokens, GetItemName(item)) || HasSearchRank(m_searchTokens, GetItemValue(item));}
protected:
	void UpdateFit();
	void UpdateFitByWidth();
	bool DoSetPropertyValueAt(int at, const char* value, COLORREF valueColor, char bold);
	virtual void OnItemAdded(void* item, unsigned int at, bool checked);
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect);
//	virtual void Resize(int cx, int cy);
	virtual void OnFontSet(CFont* font, HDC hdc) override;
	virtual void SizeChanged(bool horizontalChange, bool verticalChange) override;
	virtual bool GetToolTipInfo(unsigned int ordinal, const void* item, std::string& tooltipText, int& left, int& right) const;
	int m_nameWidth;
	int m_nameValueGap;
	int m_valuePad;
	int m_valueWidth;
	CFont* m_nameFont;
	CFont* m_valueFont;
	CFont* m_valueBoldFont;
	COLORREF m_nameColor;
	COLORREF m_bkColor;
};

class UGUI_API ListBoxBoldItem : public ListBoxOwnerDraw
{
public:
//	void SetFontBold(CFont* font){m_fontBold = font;}
	void SetItemBold(const int& itemBold){m_itemBold = itemBold;}
	void SetItemBold(const void* const& itemBold){m_itemBold = itemBold ? FindItem(itemBold) : -1;}
//	CFont* const& GetFontNormal() const{return m_font;}
	virtual CFont* GetFontBold() const override{return m_fontBold;}
	const int& GetItemBold() const{return m_itemBold;}
	void SelectItemBold()
	{
		if(m_hWnd)SetCurSel(m_itemBold >= 0 ? m_itemBold : -1);
	}
	virtual bool isRadio() const override{return m_radio;}
	virtual void SetRadio(bool radio) override
	{
		if(radio != m_radio)
		{
			m_radio = radio;
		}
	}
	const bool& isUseBoldFont() const{return m_useBoldFont;}
	void SetUseBoldFont(const bool& useBoldFont)
	{
		if(!useBoldFont != m_useBoldFont)
		{
			m_useBoldFont = useBoldFont;
		}
	}
protected:
	ListBoxBoldItem(const int& itemHeight = 0,
		const bool& rbuttonSelection = false,
		const bool& rbuttonMenu = false,
		const bool& draggable = false,
		const bool& useBoldFont = true,
		const char* const& tooltipText = nullptr,
		const bool& radio = false):
		ListBoxOwnerDraw(itemHeight, rbuttonSelection, rbuttonMenu, draggable, tooltipText),
//		m_font(nullptr),
		m_fontBold(nullptr),
		m_itemBold(-1),
		m_useBoldFont(useBoldFont),
		m_radio(radio)
	{
	}
	void InitFont()
	{
		m_fontBold = m_useBoldFont && m_font ? GetTakionBoldFont(m_font) : nullptr;
/*
		if(font)
		{
			LOGFONT logfont;
			font->GetLogFont(&logfont);
			m_font = GetTakionFont(logfont);
			if(m_useBoldFont)
			{
				logfont.lfWeight = FW_BOLD;
				m_fontBold = GetTakionFont(logfont);
			}
			else
			{
				m_fontBold = nullptr;
			}
		}
		else
		{
			m_font = nullptr;
			m_fontBold = nullptr;
		}
*/
	}
	virtual void ListBoxCreated() override
	{
		ListBoxOwnerDraw::ListBoxCreated();
		InitFont();
	}
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect) override
	{
		HGDIOBJ oldFont = lpDrawItemStruct->itemID == m_itemBold && m_fontBold ? SelectObject(lpDrawItemStruct->hDC, *m_fontBold) : nullptr;
		ListBoxOwnerDraw::DoDrawItem(lpDrawItemStruct, drawItemRect);
		if(oldFont)SelectObject(lpDrawItemStruct->hDC, oldFont);
	}
	virtual void GetDrawItemRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawItemRect) const override
	{
		ListBoxOwnerDraw::GetDrawItemRect(lpDrawItemStruct, drawItemRect);
		if(m_radio)
		{
			drawItemRect.left += lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top;
		}
	}
	virtual void DrawNumber(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& r) override
	{
		if(m_radio)
		{
			CRect rect(3, r.top + 1, r.Height(), r.bottom - 1);
			const COLORREF stringColor = GetCheckColor(lpDrawItemStruct);
			UGUI_DrawRadio(lpDrawItemStruct->hDC, rect, 1, stringColor, false, m_checkHighlightColor, lpDrawItemStruct->itemID == m_itemBold, stringColor, 0xFFFFFFFF);
		}
	}
	virtual void OnFontSet(CFont* font, HDC hdc) override
	{
		ListBoxOwnerDraw::OnFontSet(font, hdc);
		InitFont();
	}
	virtual void AfterItemDeleted(unsigned int at, bool failed, bool checked) override
	{
		if(!failed && m_itemBold >= 0)
		{
			const unsigned int uItemBold = (unsigned int)m_itemBold;
			if(at == uItemBold)
			{
				m_itemBold = -1;
			}
			else if(at < uItemBold)
			{
				--m_itemBold;
			}
		}
	}
	virtual void AfterItemsCleared() override
	{
		m_itemBold = -1;
	}

//	CFont* m_font;
	CFont* m_fontBold;
	int m_itemBold;
	bool m_useBoldFont;
	bool m_radio;
};

class UGUI_API ListBoxFit : public ListBoxBoldItem
{
public:
	const int& GetMaxTextWidth() const{return m_maxWidth;}
	virtual int GetMaxWidth() const{return m_radio ? m_maxWidth + m_itemHeight : m_maxWidth;}
	virtual void GetItemText(const void* item, std::string& text) const
	{
		text = GetItemName(item);
	}
protected:
	ListBoxFit(const int& itemHeight = 0, const bool& rbuttonSelection = false, const bool& rbuttonMenu = false, const bool& draggable = false, const bool& useBoldFont = true, const char* const& tooltipText = nullptr, bool radio = false):
		ListBoxBoldItem(itemHeight, rbuttonSelection, rbuttonMenu, draggable, useBoldFont, tooltipText, radio),
		m_maxWidth(0)
	{}
	virtual void OnItemAdded(void* item, unsigned int at, bool checked) override;
	virtual void BeforeItemDeleted(unsigned int at, bool checked) override;
	virtual void AfterItemDeleted(unsigned int at, bool failed, bool checked) override;
//	virtual void BeforeItemsCleared();
	virtual void AfterItemsCleared() override;
	virtual void OnFontSet(CFont* font, HDC hdc) override;
	virtual void OnItemHeightSet(unsigned int index, unsigned int itemHeight) override;
	bool BeforeCurrentItemSet(const void* currentItem, const void* itemToBeCurrent);
	int m_maxWidth;
};

class UGUI_API ListBoxMenu : public ListBoxFit
{
public:
	ListBoxMenu(bool rbuttonSelection = false, bool rbuttonMenu = false, bool draggable = false, bool useBoldFont = true, const char* tooltipText = nullptr, bool radio = false):
		ListBoxFit(0, rbuttonSelection, rbuttonMenu, draggable, useBoldFont, tooltipText, radio)
	{
	}
	virtual COLORREF GetStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override
	{
		if(lpDrawItemStruct->itemState & ODS_SELECTED)return GetSysColor(COLOR_HIGHLIGHTTEXT);
		return GetSysColor(COLOR_MENUTEXT);
	}
	virtual COLORREF GetSelectedBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override{return GetSysColor(COLOR_MENUHILIGHT);}
	virtual COLORREF GetBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override{return GetSysColor(COLOR_MENU);}
//protected:
//	virtual void ListBoxCreated() override;
};

class UGUI_API ListBoxFitString : public ListBoxFit
{
public:
friend class DialogListFitString;
	ListBoxFitString(DialogListFitString* parentDlg,
		const bool& own = true,
		const int& itemHeight = 0,
		const bool& rbuttonSelection = false,
		const bool& rbuttonMenu = false,
		const bool& draggable = false,
		const bool& useBoldFont = true,
		const char* const& tooltipText = nullptr) :
		ListBoxFit(itemHeight, rbuttonSelection, rbuttonMenu, draggable, useBoldFont, tooltipText),
		m_parentDlg(parentDlg),
		m_own(own)
	{
	}
//	virtual const char* GetItemName(const void* item) const override;
	virtual int Compare(const void* item1, const void* item2) const override;
	virtual void DestroyItem(const void* item) const override;
	virtual void* CloneItem(const void* item) const override;
	virtual void* CreateItemFromString(const char* str) const override{return U_CopyString(str);}
	virtual void ItemToString(const void* item, std::string& itemStr) const override;
	virtual const char* GetItemName(const void* item) const override{return (const char*)item;}
	int AddStringItem(const char* item);
	int InsertStringItem(int at, const char* item);
//	static char* CopyString(const char* str);
	void PretendNotDisplayed() const;
	void UnpretendNotDisplayed() const;
//	void UpdateBoldItem(bool resize);
	const bool& isOwner() const{return m_own;}
	void SetOwner(const bool& owner){m_own = owner;}
protected:
	virtual void OnItemAdded(void* item, unsigned int at, bool checked) override;
	virtual void BeforeItemDeleted(unsigned int at, bool checked) override;
	virtual void AfterItemsCleared() override;
	virtual void AfterItemDeleted(unsigned int at, bool failed, bool checked) override;
	void UpdateDimensions();

	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) override;
	virtual void AddMenuItems(CMenu& menu) override;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;

	DialogListFitString* m_parentDlg;
	bool m_own;
};

class FileItem//items in ListBoxFile
{
public:
	FileItem(const char* name, const FILETIME& timeWrite):
		m_name(name),
		m_timeWrite(timeWrite)
	{
		SYSTEMTIME sysTime;
		SYSTEMTIME localTime;
		FileTimeToSystemTime(&m_timeWrite, &sysTime);
//		SystemTimeToTzSpecificLocalTime(&m_NewYorkTimeZone, &sysTime, &nyTime);
		SystemTimeToTzSpecificLocalTime(nullptr, &sysTime, &localTime);
		char num[33];
		
		U_AppendTwoDigits(m_dateWriteStr, localTime.wMonth, '-');
		U_AppendTwoDigits(m_dateWriteStr, localTime.wDay, '-');
		m_dateWriteStr += U_UnsignedNumberToStr(localTime.wYear, num, sizeof(num));

		U_AppendTwoDigits(m_timeWriteStr, localTime.wHour, ':');
		U_AppendTwoDigits(m_timeWriteStr, localTime.wMinute, ':');
		U_AppendTwoDigits(m_timeWriteStr, localTime.wSecond, '-');
		U_AppendThreeDigits(m_timeWriteStr, localTime.wMilliseconds);
	}
	FileItem(const char* name):
		m_name(name)
	{
		m_timeWrite.dwLowDateTime = 0;
		m_timeWrite.dwHighDateTime = 0;
	}
	const std::string& GetName() const{return m_name;}
	const char* GetNameStr() const{return m_name.c_str();}
	const FILETIME& GetTimeWrite() const{return m_timeWrite;}
	const std::string& GetDateWriteStr() const{return m_dateWriteStr;}
	const std::string& GetTimeWriteStr() const{return m_timeWriteStr;}
	bool hasTimeStamp() const{return m_timeWrite.dwLowDateTime != 0 || m_timeWrite.dwHighDateTime != 0;}
protected:
	std::string m_name;
	std::string m_dateWriteStr;
	std::string m_timeWriteStr;
	FILETIME m_timeWrite;
};

class UGUI_API ListBoxFile : public ListBoxBoldItem
{
public:
	ListBoxFile(bool sortByTime = false, int itemHeight = 0, bool rbuttonSelection = false, bool rbuttonMenu = false, bool draggable = false, bool useBoldFont = true, const char* tooltipText = nullptr)://:m_invalid(false), m_colorInvalid(RGB(128, 128, 128)){}
		ListBoxBoldItem(itemHeight, rbuttonSelection, rbuttonMenu, draggable, useBoldFont, tooltipText),
		m_timeWidth(0),
		m_sortByTime(sortByTime),
		m_keepItems(false)
	{}
	virtual const char* GetItemName(const void* item) const override;
	virtual void* CloneItem(const void* item) const override;
	virtual void* CreateItemFromString(const char* str) const override;
	virtual int Compare(const void* item1, const void* item2) const override;
	virtual void DestroyItem(const void* item) const override;
	const bool& isSortByTime() const{return m_sortByTime;}
	void SetSortByTime(const bool& sortByTime);
	virtual bool isSortedByName() const override{return ListBoxBoldItem::isSortedByName() && !m_sortByTime;}
	virtual bool isSorted() const{return ListBoxBoldItem::isSorted() || m_sortByTime;}
	const int& GetTimeWidth() const{return m_timeWidth;}
	void SetTimeWidth(const int& timeWidth)
	{
		if(timeWidth != m_timeWidth)
		{
			m_timeWidth = timeWidth;
			if(m_hWnd)Invalidate(FALSE);
		}
	}
protected:
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect) override;
//	virtual void ListBoxCreated();
	int m_timeWidth;
	bool m_sortByTime;
	bool m_keepItems;
};

template <class T>
class ComboBoxUInt : public ComboBoxOwnerDraw
{
public:
	typedef T ValueType;
	ComboBoxUInt(COLORREF disabledColor = 0xFFFFFFFF, const char* tooltipText = nullptr):ComboBoxOwnerDraw(disabledColor, 0, false, tooltipText){}
	ValueType GetNumericValue(const void* const& item) const
	{
		return (ValueType)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			item;
	}

	ValueType GetNumericValueAt(const int& at) const
	{
		return GetNumericValue(GetItemDataPtr(at));
	}
	virtual int Compare(const void* item1, const void* item2) const override
	{
		const ValueType n1 = GetNumericValue(item1);
		const ValueType n2 = GetNumericValue(item2);
		return n1 < n2 ? -1 : n1 > n2 ? 1 : 0;
	}
	virtual const char* GetItemName(const void* item) const override
	{
		static char num[33];
		return U_UnsignedNumberToStrNoDecDigits(GetNumericValue(item), num, sizeof(num));
	}
//protected:
//	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect);
};

template <class T>
class ComboBoxUIntHex : public ComboBoxUInt<T>
{
public:
	ComboBoxUIntHex(COLORREF disabledColor = 0xFFFFFFFF, const char* tooltipText = nullptr):ComboBoxUInt(disabledColor, tooltipText){}
	virtual const char* GetItemName(const void* item) const override
	{
		static char num[33];
		return U_UnsignedNumberHexToStr(GetNumericValue(item), num, sizeof(num));
	}
};

class UGUI_API ComboBoxIp : public ComboBoxUInt<unsigned int>
{
public:
	ComboBoxIp(COLORREF disabledColor = 0xFFFFFFFF, const char* tooltipText = nullptr):ComboBoxUInt(disabledColor, tooltipText){}
	bool UpdateIPs(const unsigned int* ipAddresses, unsigned int startFrom);
protected:
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect) override;
};

class UGUI_API ComboBoxIpChosen : public ComboBoxIp
{
public:
	ComboBoxIpChosen(const COLORREF& chosenColor, const COLORREF& disabledColor = 0xFFFFFFFF, const char* tooltipText = nullptr):
		ComboBoxIp(disabledColor, tooltipText),
		m_chosenColor(chosenColor),
		m_chosenItem(0),
		m_chosen(false)
	{}
	bool ChooseSelectedItem()
	{
		if(m_hWnd)
		{
			const int sel = GetCurSel();
			return sel >= 0 ? SetChosenItem((unsigned int)
#if(_MSC_VER > 1600)
				(size_t)
#endif
				GetItemDataPtr(sel)) : Unchoose();
		}
		return false;
	}
	bool SelectChosenItem()
	{
		if(m_hWnd)
		{
			const int sel = GetCurSel();
			if(m_chosen)
			{
				const int found = FindItem((const void*)
#if(_MSC_VER > 1600)
					(size_t)
#endif
					m_chosenItem);
				if(found >= 0)
				{
					if(found != sel)
					{
						SetCurSel(found);
						return true;
					}
				}
				else if(sel >= 0)
				{
					SetCurSel(-1);
					return true;
				}
			}
			else if(sel >= 0)
			{
				SetCurSel(-1);
				return true;
			}
		}
		return false;
	}
	bool isItemChosen(const unsigned int& item) const
	{
		return m_chosen && item == m_chosenItem;
	}
	bool isItemChosenSelected() const
	{
		if(m_hWnd && m_chosen)
		{
			const int sel = GetCurSel();
			return sel >= 0 && sel == FindItem((const void*)
#if(_MSC_VER > 1600)
				(size_t)
#endif
				m_chosenItem);
		}
		return false;
	}
	const COLORREF GetChosenColor() const{return m_chosenColor;}
	void SetChosenColor(const COLORREF& chosenColor)
	{
		if(chosenColor != m_chosenColor)
		{
			m_chosenColor = chosenColor;
			if(m_hWnd)Invalidate(FALSE);
		}
	}
	const unsigned int& GetChosenItem() const{return m_chosenItem;}
	const bool & isChosen() const{return m_chosen;}
	bool SetChosenItem(const unsigned int& chosenItem)
	{
		if(chosenItem != m_chosenItem || !m_chosen)
		{
			m_chosenItem = chosenItem;
			m_chosen = true;
			if(m_hWnd)Invalidate(FALSE);
			return true;
		}
		return false;
	}
	bool Unchoose()
	{
		m_chosenItem = 0;
		if(m_chosen)
		{
			m_chosen = false;
			if(m_hWnd)Invalidate(FALSE);
			return true;
		}
		return false;
	}
	COLORREF GetItemColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const
	{
		return m_chosen && lpDrawItemStruct->itemData == m_chosenItem ? m_chosenColor : GetSysColor(COLOR_WINDOWTEXT);
	}
	virtual COLORREF GetBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override;
	virtual COLORREF GetSelectedBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override;
	virtual COLORREF GetStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override;
protected:
	COLORREF m_chosenColor;
	unsigned int m_chosenItem;
	bool m_chosen;
};

class UGUI_API ComboBoxString : public ComboBoxOwnerDraw
{
public:
	ComboBoxString(bool own = true, const char* tooltipText = nullptr):ComboBoxOwnerDraw(0xFFFFFFFF, 0, false, tooltipText), m_own(own){}
//	virtual int Compare(const void* item1, const void* item2) const;
//	virtual COLORREF GetStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const{return GetSysColor((lpDrawItemStruct->itemState & ODS_SELECTED) == 0 ? COLOR_WINDOWTEXT : COLOR_HIGHLIGHTTEXT);}
	virtual const char* GetItemName(const void* item) const override{return (const char*)item;}
	virtual void DestroyItem(const void* item) const override;
protected:
//	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect);
	bool m_own;
};

class UGUI_API ComboBoxStringCurrentItem : public ComboBoxString
{
public:
	ComboBoxStringCurrentItem(
		const COLORREF& colorInvalid = 0xFFFFFFFF,
		const COLORREF& colorCurrent = 0xFFFFFFFF,
		const unsigned int& invalidItemOrdinal = 0xFFFFFFFF,
		const unsigned int& currentItemOrdinal = 0xFFFFFFFF,
		bool own = true,
		const char* tooltipText = nullptr):
		ComboBoxString(own, tooltipText),
		m_colorInvalid(colorInvalid),
		m_colorCurrent(colorCurrent),
		m_invalidItemOrdinal(invalidItemOrdinal),
		m_currentItemOrdinal(currentItemOrdinal)
	{}

	virtual COLORREF GetBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const;
	virtual COLORREF GetSelectedBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const;

	void RepaintInvalid(){if(m_hWnd && GetCurSel() == m_invalidItemOrdinal && m_invalidItemOrdinal != 0xFFFFFFFF)Invalidate(FALSE);}
	void RepaintCurrent(){if(m_hWnd && GetCurSel() == m_currentItemOrdinal && m_currentItemOrdinal != 0xFFFFFFFF)Invalidate(FALSE);}

	const COLORREF& GetColorInvalid() const{return m_colorInvalid;}
	const COLORREF& GetColorCurrent() const{return m_colorCurrent;}
	void SetColorInvalid(const COLORREF& colorInvalid)
	{
		if(colorInvalid != m_colorInvalid)
		{
			m_colorInvalid = colorInvalid;
			RepaintInvalid();
		}
	}
	void SetColorCurrent(const COLORREF& colorCurrent)
	{
		if(colorCurrent != m_colorCurrent)
		{
			m_colorCurrent = colorCurrent;
			RepaintCurrent();
		}
	}

	const unsigned int& GetInvalidItemOrdinal() const{return m_invalidItemOrdinal;}
	const unsigned int& GetCurrentItemOrdinal() const{return m_currentItemOrdinal;}
	void SetInvalidItemOrdinal(const unsigned int& invalidItemOrdinal)
	{
		if(invalidItemOrdinal != m_invalidItemOrdinal)
		{
			RepaintInvalid();
			m_invalidItemOrdinal = invalidItemOrdinal;
			RepaintInvalid();
		}
	}
	void SetCurrentItemOrdinal(const unsigned int& currentItemOrdinal)
	{
		if(currentItemOrdinal != m_currentItemOrdinal)
		{
			RepaintCurrent();
			m_currentItemOrdinal = currentItemOrdinal;
			RepaintCurrent();
		}
	}
	virtual void GetSelectionItemRect(const DRAWITEMSTRUCT* lpDrawItemStruct, CRect& drawItemRect) const
	{
		GetDrawItemRect(lpDrawItemStruct, drawItemRect);
		int left = drawItemRect.right - drawItemRect.Height();
		if(drawItemRect.left < left)drawItemRect.left = left;
	}
	virtual COLORREF GetStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const{return GetSysColor(COLOR_WINDOWTEXT);}
protected:
	unsigned int m_invalidItemOrdinal;
	unsigned int m_currentItemOrdinal;
	COLORREF m_colorInvalid;
	COLORREF m_colorCurrent;
};

template <class N>
class ComboBoxStringUnsignedNumber : public ComboBoxOwnerDraw
{
public:
	typedef N NumberType;
	typedef StringUnsignedNumber<N> ItemType;
	ComboBoxStringUnsignedNumber(bool numberVisible = false, bool comma = true, COLORREF disabledColor = 0xFFFFFFFF, int itemHeight = 0, const char* tooltipText = nullptr):
		ComboBoxOwnerDraw(disabledColor, itemHeight, false, tooltipText),
		m_numberVisible(numberVisible),
		m_comma(comma)
		{}
	virtual void DestroyItem(const void* item) const{delete (StringUnsignedNumber<N>*)item;}
	virtual const char* GetItemName(const void* item) const{return ((const ItemType*)item)->GetName();}
	int AddItem(const char* name, const NumberType& number){return AddString((const char*)new ItemType(name, number));}
	const char* GetSelectedName() const
	{
		int sel = GetCurSel();
		return sel >= 0 ? ((const ItemType*)GetItemDataPtr(sel))->GetName() : nullptr;
	}
	NumberType GetSelectedNumber() const
	{
		int sel = GetCurSel();
		return sel >= 0 ? ((const ItemType*)GetItemDataPtr(sel))->GetNumber() : 0;
	}
protected:
	virtual void DrawNumber(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& r)
	{
		if(m_numberVisible)
		{
			const ItemType* item = (const ItemType*)lpDrawItemStruct->itemData;
			char num[33];
			DrawText(lpDrawItemStruct->hDC, U_UnsignedNumberToStrWithCommasNoDecDigits(item->GetNumber(), num, sizeof(num), m_comma),
//				m_comma ? U_UnsignedNumberToStrWithCommas(item->GetNumber(), num, sizeof(num)):
//					U_UnsignedNumberToStr(item->GetNumber(), num, sizeof(num)),
				-1, &(RECT&)r, DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_NOCLIP|DT_NOPREFIX);
		}
	}
	bool m_numberVisible;
	bool m_comma;
};

class UGUI_API ListBoxChar : public ListBoxBoldItem//ListBoxOwnerDraw
{
public:
	ListBoxChar(bool useBoldFont = false, const char* tooltipText = nullptr);
	virtual const char* GetItemName(const void* item) const override;
    virtual int Compare(const void* item1, const void* item2) const override;

	virtual bool isNullItemOk() const{return true;}//Can you pass a nullptr in the FindItem function ?

	void FillCharRange(char from, char to, bool replace)
	{
		if(replace)
		{
			ResetContent();
		}
		for(char c = from; c <= to; ++c)
		{
			AddString((const char*)c);
		}
	}

	void FillAllChars(bool replace = true){FillCharRange(33, 126, replace);}
	void FillAlphabet(bool replace = true){FillCharRange('A', 'Z', replace);}
	void FillDigits(bool replace = true){FillCharRange('0', '9', replace);}
	int SelectChar(char c);
	char GetSelectedChar() const
	{
		int sel = GetCurSel();
		return sel >= 0 ? (char)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			GetItemDataPtr(sel) : '\0';
	}
protected:
	mutable char m_charBuf[2];
};
/*
class UGUI_API ListBoxCharBold : public ListBoxChar
{
public:
	ListBoxCharBold()://int itemHeight = 0, bool rbuttonSelection = false, bool rbuttonMenu = false, bool draggable = false):
//		ListBoxChar(),//own, itemHeight, rbuttonSelection, rbuttonMenu, draggable),
		m_font(nullptr),
		m_fontBold(nullptr),
		m_itemBold(-1)
		{}
	void SetFontBold(CFont* font){m_fontBold = font;}
	void SetItemBold(int itemBold){m_itemBold = itemBold;}
	virtual CFont* GetFontBold() const override{return m_fontBold;}
	int GetItemBold() const{return m_itemBold;}
//	virtual void SetFont(CFont* font);
protected:
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect)
	{
		HGDIOBJ oldFont = lpDrawItemStruct->itemID == m_itemBold && m_fontBold ? SelectObject(lpDrawItemStruct->hDC, *m_fontBold) : nullptr;
		ListBoxChar::DoDrawItem(lpDrawItemStruct, drawItemRect);
		if(oldFont)SelectObject(lpDrawItemStruct->hDC, oldFont);
	}
	virtual void OnFontSet(CFont* font, HDC hdc) override
	{
		ListBoxOwnerDraw::OnFontSet(font, hdc);
		m_fontBold = GetTakionBoldFont(font);
	}
	CFont* m_font;
	CFont* m_fontBold;
	int m_itemBold;
};
*/
class UGUI_API ComboBoxChar : public ComboBoxOwnerDraw
{
public:
	ComboBoxChar(COLORREF disabledColor = 0xFFFFFFFF, int itemHeight = 0, const char* tooltipText = nullptr);
	virtual const char* GetItemName(const void* item) const override;
    virtual int Compare(const void* item1, const void* item2) const override;

	void FillCharRange(char from, const char& to, const bool& replace)
	{
		if(replace)
		{
			ResetContent();
		}
		for(; from <= to; ++from)
		{
			AddString((const char*)from);
		}
	}

	void FillAllChars(const bool& replace = true){FillCharRange(33, 126, replace);}
	void FillAlphabet(const bool& replace = true){FillCharRange('A', 'Z', replace);}
	void FillDigits(const bool& replace = true){FillCharRange('0', '9', replace);}
	int SelectChar(const char c);
	char GetSelectedChar() const
	{
		const int sel = GetCurSel();
		return sel >= 0 ? (char)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			GetItemDataPtr(sel) : '\0';
	}
	int FindChar(const char item) const;
protected:
	mutable char m_charBuf[2];
};

class UGUI_API ComboBoxBoldItem : public ComboBoxOwnerDraw
{
public:
//	void SetFontBold(CFont* font){m_fontBold = font;}
	void SetItemBold(int itemBold){m_itemBold = itemBold;}
	void SetItemBold(const void* const& itemBold){m_itemBold = itemBold ? FindItem(itemBold) : -1;}
//	CFont* const& GetFontNormal() const{return m_font;}
	virtual CFont* GetFontBold() const override{return m_fontBold;}
	int GetItemBold() const{return m_itemBold;}
	void SelectItemBold(){if(m_hWnd)SetCurSel(m_itemBold >= 0 ? m_itemBold : -1);}
protected:
	ComboBoxBoldItem(COLORREF disabledColor = 0xFFFFFFFF, bool useBoldFont = true, const char* tooltipText = nullptr):
		ComboBoxOwnerDraw(disabledColor, 0, false, tooltipText),
//		m_font(nullptr),
		m_fontBold(nullptr),
		m_itemBold(-1),
		m_useBoldFont(useBoldFont)
	{}
	void InitFont()
	{
		m_fontBold = m_useBoldFont && m_font ? GetTakionBoldFont(m_font) : nullptr;
/*
		if(font)
		{
			LOGFONT logfont;
			font->GetLogFont(&logfont);
			m_font = GetTakionFont(logfont);
			if(m_useBoldFont)
			{
				logfont.lfWeight = FW_BOLD;
				m_fontBold = GetTakionFont(logfont);
			}
			else
			{
				m_fontBold = nullptr;
			}
		}
		else
		{
			m_font = nullptr;
			m_fontBold = nullptr;
		}
*/
	}
	virtual void ComboBoxCreated() override
	{
		if(!m_initCompleted)
		{
			ComboBoxOwnerDraw::ComboBoxCreated();
			InitFont();
		}
	}
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect)
	{
		HGDIOBJ oldFont = lpDrawItemStruct->itemID == m_itemBold && m_fontBold ? SelectObject(lpDrawItemStruct->hDC, *m_fontBold) : nullptr;
		ComboBoxOwnerDraw::DoDrawItem(lpDrawItemStruct, drawItemRect);
		if(oldFont)SelectObject(lpDrawItemStruct->hDC, oldFont);
	}
	virtual void OnFontSet(CFont* font, HDC hdc)
	{
		ComboBoxOwnerDraw::OnFontSet(font, hdc);
		InitFont();
	}
//	CFont* m_font;
	CFont* m_fontBold;
	int m_itemBold;
	bool m_useBoldFont;
};
/*
class UGUI_API ConnectionItem
{
public:
	typedef StrAsNumberArray<size_t, 64 / sizeof(size_t)> CompIdType;
	ConnectionItem(unsigned short port,
		const char* memo = "",
		const char* name = "",
		unsigned char dataType = 0xFF,
		bool connected = false,
		bool connecting = false,
		bool tryingToConnect = false,
		bool logged = false)://, CFont* font = nullptr):
//		m_ip(ip),
		m_port(port),
		m_memo(memo),
		m_name(name),
		m_dataType(dataType),
		m_connected(connected),
		m_connecting(connecting),
		m_tryingToConnect(tryingToConnect),
		m_logged(logged)
	{}
	virtual ~ConnectionItem(){}
	inline const unsigned short& GetPort() const{return m_port;}
	bool SetPort(const unsigned short& port)
	{
		if(port != m_port)
		{
			m_port = port;
			return true;
		}
		return false;
	}

	const std::string& GetMemoStr() const{return m_memo;}
	const char* GetMemo() const{return m_memo.c_str();}
	bool SetMemoStr(const std::string& memo)
	{
		if(m_memo != memo)
		{
			m_memo = memo;
			return true;
		}
		return false;
	}
	bool SetMemo(const char* memo)
	{
		if(strcmp(m_memo.c_str(), memo))
		{
			m_memo = memo;
			return true;
		}
		return false;
	}

	const CompIdType& GetName() const{return m_name;}
	const char* GetNameAsString() const{return m_name.GetString();}
	bool SetNameStr(const std::string& name)
	{
		return SetName(name.c_str());
	}
	bool SetName(const char* name)
	{
		if(strcmp(m_name.GetString(), name))
		{
			m_name.SetString(name);
			return true;
		}
		return false;
	}
	const unsigned char& GetDataType() const{return m_dataType;}
	bool SetDataType(const unsigned char& dataType)
	{
		if(dataType != m_dataType)
		{
			m_dataType = dataType;
			return true;
		}
		return false;
	}

	const bool& isConnected() const{return m_connected;}
	bool SetConnected(bool connected);

	const bool& isConnecting() const{return m_connecting;}
	bool SetConnecting(bool connecting);

	bool isDisconnected() const{return !m_connecting && !m_connected;}
	bool SetDisconnected();

	const bool& isLogged() const{return m_logged;}
	bool SetLogged(bool logged);

	const bool& isTryingToConnect() const{return m_tryingToConnect;}
	bool SetTryingToConnect(bool tryingToConnect);
	virtual void ConnectedStatusChanged(bool connected){}

	virtual unsigned int GetIp() const{return 0;}
	virtual bool SetIp(unsigned int ip){return false;}
	virtual short CompareIpPort(unsigned int ip, unsigned short port) const
	{
		return m_port < port ? -1:
			m_port > port ? 1:
			0;
	}
	virtual short CompareIpPort(const ConnectionItem& other) const
	{
		return m_port < other.m_port ? -1 :
			m_port > other.m_port ? 1 :
			0;
	}
	virtual bool isIpPortEqual(const unsigned int& ip, const unsigned short& port) const
	{
		return m_port == port;
	}
protected:
//	unsigned int m_ip;
	unsigned short m_port;
	CompIdType m_name;
	std::string m_memo;
	unsigned char m_dataType;
	bool m_connected;
	bool m_connecting;
	bool m_tryingToConnect;
	bool m_logged;
};



class UGUI_API ConnectionItemIp : public ConnectionItem
{
public:
	typedef StrAsNumberArray<size_t, 64 / sizeof(size_t)> CompIdType;
	ConnectionItemIp(unsigned int ip,
		unsigned short port,
		const char* memo = "",
		const char* name = "",
		unsigned char dataType = 0xFF,
		bool connected = false,
		bool connecting = false,
		bool tryingToConnect = false,
		bool logged = false)://, CFont* font = nullptr):
		ConnectionItem(port, memo, name, dataType, connected, connecting, tryingToConnect, logged),
		m_ip(ip)
	{}
//	virtual ~ConnectionItemIp(){}
	virtual unsigned int GetIp() const override{return m_ip;}

	virtual bool SetIp(unsigned int ip) override
	{
		if(ip != m_ip)
		{
			m_ip = ip;
			return true;
		}
		return false;
	}

	virtual short CompareIpPort(unsigned int ip, unsigned short port) const override
	{
		return m_ip < ip ? -1:
			m_ip > ip ? 1:
			m_port < port ? -1:
			m_port > port ? 1:
			0;
	}

	virtual short CompareIpPort(const ConnectionItem& other) const override
	{
		const unsigned int otherIp = other.GetIp();
		return m_ip < otherIp ? -1:
			m_ip > otherIp ? 1:
			m_port < other.GetPort() ? -1:
			m_port > other.GetPort() ? 1:
			0;
	}
	virtual bool isIpPortEqual(const unsigned int& ip, const unsigned short& port) const override
	{
		return m_ip == ip && m_port == port;
	}

protected:
	unsigned int m_ip;
};
*/

class UGUI_API ConnectionItem
{
public:
	typedef StrAsNumberArray<size_t, 64 / sizeof(size_t)> CompIdType;
	ConnectionItem(const char* const& dns, const unsigned int& ip,
		const unsigned short& port,
//		const char* const& dns = nullptr,
		const char* const& memo = "",
		const char* const& name = "",
		const unsigned char& dataType = 0xFF,
		const bool& connected = false,
		const bool& connecting = false,
		const bool& tryingToConnect = false,
		const bool& logged = false):
		m_dns(dns ? dns : ""),
		m_ip(ip),
		m_port(port),
		m_memo(memo),
		m_name(name),
		m_dataType(dataType),
		m_connected(connected),
		m_connecting(connecting),
		m_tryingToConnect(tryingToConnect),
		m_logged(logged)
	{}
	virtual ~ConnectionItem(){}

	const std::string& GetDns() const{return m_dns;}
	bool SetDns(const char* dns)
	{
		if(dns)
		{
			if(strcmp(dns, m_dns.c_str()))
			{
				m_dns = dns;
				return true;
			}
		}
		else if(!m_dns.empty())
		{
			m_dns.clear();
			return true;
		}
		return false;
	}
	bool SetDns(const std::string& dns)
	{
		if(dns != m_dns)
		{
			m_dns = dns;
			return true;
		}
		return false;
	}
	const unsigned int& GetIp() const{return m_ip;}
	bool SetIp(const unsigned int& ip)
	{
		if(ip != m_ip)
		{
			m_ip = ip;
			return true;
		}
		return false;
	}

	const unsigned short& GetPort() const{return m_port;}
	bool SetPort(const unsigned short& port)
	{
		if(port != m_port)
		{
			m_port = port;
			return true;
		}
		return false;
	}

	bool isIpPortEqual(const unsigned int& ip, const unsigned short& port, const char* dns) const
	{
		if (!dns)dns = "";
		return m_port == port && !strcmp(dns, m_dns.c_str()) && (*dns || m_ip == ip);
//		return m_ip == ip && m_port == port;
	}

	short CompareIpPort(const unsigned int& ip, const unsigned short& port, const char* dns) const
	{
		if(!dns)dns = "";
		const int res = strcmp(m_dns.c_str(), dns);
		return res > 0 ? -1 :
			res < 0 ? 1 :
			m_ip < ip ? -1:
			m_ip > ip ? 1:
			m_port < port ? -1:
			m_port > port ? 1:
			0;
	}
	short CompareIpPort(const ConnectionItem& other) const
	{
		const int res = strcmp(m_dns.c_str(), other.m_dns.c_str());
		return res > 0 ? -1:
			res < 0 ? 1:
			m_ip < other.m_ip ? -1:
			m_ip > other.m_ip ? 1:
			m_port < other.m_port ? -1:
			m_port > other.m_port ? 1:
			0;
	}
	const std::string& GetMemoStr() const{return m_memo;}
	const char* GetMemo() const{return m_memo.c_str();}
	bool SetMemoStr(const std::string& memo)
	{
		if(m_memo != memo)
		{
			m_memo = memo;
			return true;
		}
		return false;
	}
	bool SetMemo(const char* memo)
	{
		if(strcmp(m_memo.c_str(), memo))
		{
			m_memo = memo;
			return true;
		}
		return false;
	}

	const CompIdType& GetName() const{return m_name;}
	const char* GetNameAsString() const{return m_name.GetString();}
	bool SetNameStr(const std::string& name)
	{
		return SetName(name.c_str());
	}
	bool SetName(const char* name)
	{
		if(strcmp(m_name.GetString(), name))
		{
			m_name.SetString(name);
			return true;
		}
		return false;
	}
	const unsigned char& GetDataType() const{return m_dataType;}
	bool SetDataType(const unsigned char& dataType)
	{
		if(dataType != m_dataType)
		{
			m_dataType = dataType;
			return true;
		}
		return false;
	}

	const bool& isConnected() const{return m_connected;}
	bool SetConnected(bool connected);

	const bool& isConnecting() const{return m_connecting;}
	bool SetConnecting(bool connecting);

	bool isDisconnected() const{return !m_connecting && !m_connected;}
	bool SetDisconnected();

	const bool& isLogged() const{return m_logged;}
	bool SetLogged(bool logged);

	const bool& isTryingToConnect() const{return m_tryingToConnect;}
	bool SetTryingToConnect(bool tryingToConnect);
	virtual void ConnectedStatusChanged(bool connected){}
protected:
	std::string m_dns;
	unsigned int m_ip;
	unsigned short m_port;
	CompIdType m_name;
	std::string m_memo;
	unsigned char m_dataType;
	bool m_connected;
	bool m_connecting;
	bool m_tryingToConnect;
	bool m_logged;
};


class UGUI_API ListBoxConnection : public ListBoxBoldItem
{
public:
	ListBoxConnection(bool showName = false, int itemHeight = 0, bool rbuttonSelection = true, bool rbuttonMenu = true, bool draggable = false, bool useBoldFont = true, const char* tooltipText = nullptr):
		ListBoxBoldItem(itemHeight, rbuttonSelection, rbuttonMenu, draggable, useBoldFont, tooltipText),
		m_colorConnected(RGB(0, 128, 0)),
		m_colorDisconnected(RGB(128, 0, 0)),
		m_showName(showName),

		m_ipLeft(0),
		m_ipRight(0),
		m_portSeparatorRight(0),
		m_portLeft(0),
		m_portRight(0),
		m_nameLeft(0),
		m_nameRight(0),
		m_memoLeft(0),
		m_memoRight(0)
	{}
	virtual int Compare(const void* item1, const void* item2) const override;
	virtual void DestroyItem(const void* item) const override;
	virtual void* CloneItem(const void* item) const override;
	virtual void ItemToString(const void* item, std::string& itemStr) const override;
	virtual void ItemValueToString(const void* item, std::string& itemStr) const override;
//	void SetFontBold(CFont* font){m_fontBold = font;}
//	void SetItemBold(int itemBold){m_itemBold = itemBold;}
	virtual COLORREF GetStringColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override;
	virtual COLORREF GetSelectedBkColor(const DRAWITEMSTRUCT* lpDrawItemStruct) const override;
	int FindItemByIpPort(unsigned int ip, unsigned short port, const char* dns) const;

	virtual bool GetToolTipInfo(unsigned int ordinal, const void* item, std::string& tooltipText, int& left, int& right) const override;
	virtual bool isOneTooltipPerItem() const override{return false;}
protected:
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect) override;
	virtual void SizeChanged(bool horizontalChange, bool verticalChange) override;
	COLORREF m_colorConnected;
	COLORREF m_colorDisconnected;
	bool m_showName;

	void CalculateSections();
	int m_ipLeft;
	int m_ipRight;
	int m_portSeparatorRight;
	int m_portLeft;
	int m_portRight;
	int m_nameLeft;
	int m_nameRight;
	int m_memoLeft;
	int m_memoRight;
};

class UGUI_API ComboBoxNameDescriptionBase : public ComboBoxOwnerDraw
{
public:
	virtual const char* GetDescription(const void* item) const = 0;
    int CompareByDescription(const void* item1, const void* item2) const
	{
		int result = strcmp(GetDescription(item1), GetDescription(item2));
		return result < 0 ? -1 : result > 0 ? 1 : 0;
	}
	virtual const char* GetItemToolTip(int sel, const void* item) const override{return GetDescription(item);}
protected:
	ComboBoxNameDescriptionBase(const UINT& alignment = DT_LEFT, const char* const& tooltipText = nullptr):
		ComboBoxOwnerDraw(0xFFFFFFFF, 0, false, tooltipText),
		m_descriptionLeft(0),
		m_descriptionWidth(0)
//		m_widthMultiplier(widthMultiplier)
	{
		m_hAlignment = alignment;
	}
	virtual void OnItemAdded(void* item, unsigned int at) override;
	virtual void BeforeItemDeleted(unsigned int at) override;
	virtual void AfterItemsCleared() override;

//	virtual void Resize(int cx, int cy) override;
	virtual void SizeChanged(bool horizontalChange, bool verticalChange) override;
	virtual void DoDrawItem(const DRAWITEMSTRUCT* lpDrawItemStruct, const CRect& drawItemRect) override;
	int m_descriptionLeft;
///	unsigned int m_widthMultiplier;
	void UpdateDescriptionWidth(HDC hdc, unsigned int except = 0xFFFFFFFF);
	void UpdateDescriptionWidth(unsigned int except = 0xFFFFFFFF);
	void SetDescriptionWidth(const int width);
	void UpdateDroppedWidth();
	int m_descriptionWidth;
};

class NameDescriptionItem
{
public:
	NameDescriptionItem(const char* const& name, const char* const& description):m_name(name), m_description(description){}
	NameDescriptionItem(const char& name, const char* const& description):m_description(description){if(name >= ' ' && name < 128)m_name += name;}
	const std::string& GetName() const{return m_name;}
	const std::string& GetDescription() const{return m_description;}
protected:
	std::string m_name;
	std::string m_description;
};

class UGUI_API ComboBoxNameDescription : public ComboBoxNameDescriptionBase
{
public:
	ComboBoxNameDescription(const UINT& alignment = DT_LEFT, const char* const& tooltipText = nullptr):ComboBoxNameDescriptionBase(alignment, tooltipText){}
	virtual const char* GetItemName(const void* item) const;
	virtual const char* GetDescription(const void* item) const;
	virtual void DestroyItem(const void* item) const;
	int AddItem(const char* name, const char* description);
	int AddItem(char name, const char* description);
	int FindItemByCharName(const char& name)
	{
		char buf[2];
		*buf = name;
		*(buf + 1) = '\0';
		return FindItemByName(buf);
	}
//protected:
};

//#define CUSTON_CONTROL_OWN_DC

class UGUI_API TakionCustomControl : public CWnd, public ControlToolTipHelper
{
public:
	virtual ~TakionCustomControl(){}//{DestroyToolTipInfo();}
	const bool& isMouseInside() const{return m_mouseInside;}
	BOOL Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle /*=WS_VISIBLE*/);
	virtual const char* GetCustomClassName() const = 0;
	virtual CFont* GetMyFont(){return nullptr;}
	void SetMyFont(CFont* font);
	const CRect& GetControlClientRect() const{return m_clientRect;}
	const bool& hasFocus() const{return m_hasFocus;}
	const bool& isEnabled() const{return m_enabled;}
	const bool& isDeactivated() const{return m_deactivated;}//Used to recognize the situation when the parent was not active when the control got the focus
	void SetDeactivated(const bool& deactivated){m_deactivated = deactivated;}
	bool SetBkColorEnabled(COLORREF color);
	bool SetBkColorDisabled(COLORREF color);
	const COLORREF& GetBorderColor() const{return m_borderColor;}
	const COLORREF& GetBkColorEnabled() const{return m_bkColorEnabled;}
	const COLORREF& GetBkColorDisabled() const{return m_bkColorDisabled;}
	const COLORREF& GetBkColor() const{return m_bkColor;}
	const int& GetBorderWidth() const{return m_borderWidth;}
	void SetBorderColor(const COLORREF& color)
	{
		if(color != m_borderColor)
		{
			m_borderColor = color;
			BorderColorChanged();
			if(m_hWnd)Invalidate(FALSE);
		}
	}
	void SendMessageToParent(const UINT& message, const WPARAM& w, const LPARAM& l) const
	{
		if(m_hWnd)
		{
			HWND parentWnd = ::GetParent(m_hWnd);
			if(parentWnd)
			{
				::SendMessage(parentWnd, message, w, l);
			}
		}
	}
	const bool& isUseWheel() const{return m_useWheel;}
	void SetUseWheel(const bool& use)
	{
		if(use != m_useWheel)
		{
			m_useWheel = use;
			m_accumulatedWheel = 0;
			if(m_mouseInside && m_hWnd)
			{
				SendMessageToParent(use ? WM_USER + 16 : WM_USER + 36, GetDlgCtrlID(), (LPARAM)m_hWnd);
			}
		}
	}
//	void SetToolTipText(const char* text);
//	void EnableTooltips(bool enable);
//	virtual unsigned int GetCtrlId() const override{return GetDlgCtrlID();}
	inline void InvalidateRectIfValid(const RECT* rect) const{if(m_hWnd)::InvalidateRect(m_hWnd, rect, FALSE);}
	inline void InvalidateRectIfValidWithErase(const RECT* rect) const{if(m_hWnd)::InvalidateRect(m_hWnd, rect, TRUE);}
	virtual bool HasDisabledColor() const{return true;}

	virtual bool HasMenu() const{return false;}
protected:
	TakionCustomControl(int borderWidth = 1, COLORREF borderColor = 0, bool useWheel = false, const char* tootTipText = nullptr, CToolTipCtrl* externalToolTip = nullptr);

//	void DestroyToolTipInfo();
	virtual void PreSubclassWindow() override;
	virtual BOOL PreTranslateMessage(MSG* pMsg) override;
	virtual bool ProcessKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){return false;}
	virtual bool ProcessKeyUp(UINT nChar, UINT nFlags){return false;}
	virtual void DcCreated(){}
//	virtual void BeforeDestroy(){}
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnEnable(BOOL bEnable);

	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnEnterMenuLoop(BOOL bIsTrackPopupMenu);
	afx_msg void OnExitMenuLoop(BOOL bIsTrackPopupMenu);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override
	{
		return ProcessShowToolTip(lParam, pResult) || CWnd::OnNotify(wParam, lParam, pResult);
	}
	virtual void OnEnabledStatusChange(){}
	virtual void Resize(UINT nType, int cx, int cy);
	virtual void DoSize(UINT nType, int cx, int cy, int oldX, int oldY){}

	virtual void PaintBackground(const RECT& rcPaint, CDC& dc)
	{
		dc.FillSolidRect(&rcPaint, m_bkColor);
	}

	virtual void DoPaint(const RECT& rcPaint, CDC& dc)
	{
		CRect interRect;
		if(interRect.IntersectRect(&rcPaint, &m_clientRect))
		{
//			dc.FillSolidRect(&interRect, m_bkColor);
			PaintBackground(interRect, dc);

			DoPaintClient(interRect, dc);
		}
		DoAdditionalPaint(rcPaint, dc);
	}
	virtual void DoPaintClient(const RECT& interRect, CDC& dc){}
	virtual void DoAdditionalPaint(const RECT& interRect, CDC& dc){}

	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct){}
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct){return false;}


	virtual void DisplayClientMenu(UINT nFlags, CPoint point);
	virtual void AddMenuItems(CMenu& menu){}
	virtual bool SetClientCursor(){return false;}

	virtual void MouseEntered(){}
	virtual void MouseLeft(){}
	virtual void Wheel(short steps, UINT nFlags, CPoint pt){}
	virtual void FocusGained(){m_deactivated = false;}
	virtual void FocusLost(){}
	virtual void OnFontChange(CDC* dc){}
	virtual bool UpdateTextRectsHeight(){return false;}

	virtual void BorderColorChanged(){}

	virtual void PreSetMouseFocus(){}

	void SetMouseFocus();

	int m_borderWidth;
#ifdef CUSTON_CONTROL_OWN_DC
	void CreateDcBitmap(CDC* dc, int width, int height);
	int m_dcBitmapWidth;
	int m_dcBitmapHeight;
	CBitmap m_dcBitmap;
    CDC m_dc;
#endif
	CRect m_winRect;
	CRect m_clientRect;
	bool SetMouseInside(const bool& mouseInside)
	{
		if(mouseInside != m_mouseInside)
		{
			m_mouseInside = mouseInside;
			m_accumulatedWheel = 0;
			if(m_useWheel)
			{
				SendMessageToParent(mouseInside ? WM_USER + 16 : WM_USER + 36, GetDlgCtrlID(), (LPARAM)m_hWnd);//this);
			}
			return true;
		}
		return false;
	}
	short m_accumulatedWheel;
	bool m_mouseInside;
	bool m_useWheel;
	bool m_hasFocus;
	bool m_focusSetWithMouse;
	bool m_enabled;
	bool m_deactivated;//Used to recognize the situation when the parent was not active when the control got the focus
	COLORREF m_borderColor;
	COLORREF m_bkColorEnabled;
	COLORREF m_bkColorDisabled;
	COLORREF m_bkColor;
};

class UGUI_API TakionCaretCustomControl : public TakionCustomControl
{
public:
	const int& GetCaretMargin() const{return m_caretMargin;}
	virtual CFont* GetMyFont() override{return &m_font;}
protected:
	TakionCaretCustomControl(int borderWidth = 1,
		COLORREF borderColor = 0,
		bool useWheel = false,
		const char* tootTipText = nullptr,
		CToolTipCtrl* externalToolTip = nullptr):
		TakionCustomControl(borderWidth, borderColor, useWheel, tootTipText, externalToolTip),

		m_caretWidth(GetSystemMetrics(SM_CXBORDER)),
		m_caretMargin(2),
		m_caretHeight(0),
		m_caretPosY(0)
	{}
	virtual void FocusGained() override
	{
		BuildCaret();
		TakionCustomControl::FocusGained();
	}
	virtual void FocusLost() override
	{
		DestroyCaret();
	}
	virtual void DoUpdateCaretPosition(){}
	void UpdateCaretPosition()
	{
		if(m_hasFocus)
		{
			DoUpdateCaretPosition();
		}
	}
	virtual void OnBuildCaret(){}
	void BuildCaret()
	{
		CreateSolidCaret(m_caretWidth, m_caretHeight);
		UpdateCaretPosition();
		ShowCaret();
		OnBuildCaret();// Highlight();
	}
	void RebuildCaret(const bool& caretHeightChanged, const bool& caretPosChanged)
	{
		if(m_hasFocus)
		{
			if(caretHeightChanged)
			{
				DestroyCaret();
				BuildCaret();
			}
			else if(caretPosChanged)
			{
				UpdateCaretPosition();
			}
		}
	}
	virtual void DoSize(UINT nType, int cx, int cy, int oldX, int oldY) override
	{
		TakionCustomControl::DoSize(nType, cx, cy, oldX, oldY);
//		const int height = m_clientRect.Height();

//		const int caretHeight = m_clientRect.Height() - m_caretMargin - m_caretMargin;
//		const bool caretHeightChanged = m_caretHeight != caretHeight;
//		if(caretHeightChanged)
//		m_caretHeight = caretHeight;
		m_caretHeight = m_clientRect.Height() - m_caretMargin - m_caretMargin;

//		const int caretPosY = m_clientRect.top + m_caretMargin;
//		const bool caretPosChanged = m_caretPosY != caretPosY;
//		if(caretPosChanged)
//		m_caretPosY = caretPosY;
		m_caretPosY = m_clientRect.top + m_caretMargin;
	}
	CFont m_font;
	int m_caretWidth;
	int m_caretMargin;
	int m_caretHeight;
	int m_caretPosY;
};

class UGUI_API TakionTextCustomControl : public TakionCaretCustomControl
{
public:
	int GetTextRectRight() const{return m_textRect.right;}
	const int& GetTextHeight() const{return m_textHeight;}
	const CRect& GetEditRect() const{return m_editRect;}
	const CRect& GetTextRect() const{return m_textRect;}
	const COLORREF& GetTextColor() const{return m_textColor;}
	const COLORREF& GetSelectionColor() const{return m_selectionColor;}
	const COLORREF& GetSelectionTextColor() const{return m_selectionTextColor;}
	void SetTextColor(const COLORREF& color)
	{
		if(color != m_textColor)
		{
			m_textColor = color;
			InvalidateRectIfValid(&m_editRect);
		}
	}
	void SetSelectionColor(const COLORREF& color)
	{
		if(color != m_selectionColor)
		{
			m_selectionColor = color;
			InvalidateRectIfValid(&m_editRect);
		}
	}
	void SetSelectionTextColor(const COLORREF& color)
	{
		if(color != m_selectionTextColor)
		{
			m_selectionTextColor = color;
			InvalidateRectIfValid(&m_editRect);
		}
	}
	virtual int CalculateEditRectLeft() const{return m_clientRect.left;}
	virtual int CalculateEditRectRight() const{return m_clientRect.right;}

	virtual bool isContentValid() const{return true;}
	virtual bool isContentEmpty() const{return false;}
	virtual bool isPasteAvailable() const{return true;}
	virtual HCURSOR GetInEditCursor() const{return m_beamCursor;}
	virtual HCURSOR GetOutEditCursor() const{return m_arrowCursor;}
	virtual bool WantChars() const{return true;}
protected:
	TakionTextCustomControl(int borderWidth = 1,
		COLORREF borderColor = 0,
		bool useWheel = false,
		const char* tootTipText = nullptr,
		CToolTipCtrl* externalToolTip = nullptr):
		TakionCaretCustomControl(borderWidth, borderColor, useWheel, tootTipText, externalToolTip),
		m_beamCursor(LoadCursor(nullptr, IDC_IBEAM)),
		m_arrowCursor(LoadCursor(nullptr, IDC_ARROW)),
		m_editRect(0, 0, 0, 0),
		m_highlightColor(GetSysColor(COLOR_3DSHADOW)),
		m_selectionColor(GetSysColor(COLOR_HIGHLIGHT)),
		m_selectionTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT)),
		m_textColor(GetSysColor(COLOR_WINDOWTEXT)),
		m_disabledTextColor(GetSysColor(COLOR_GRAYTEXT)),
		m_textHeight(0),
		m_inEdit(false),
		m_copyMenuWidth(0),
		m_pasteMenuWidth(0),
		m_clearMenuWidth(0)
	{}
	virtual void PreSubclassWindow() override;
	virtual void BeforeDestroy() override
	{
		TakionCaretCustomControl::BeforeDestroy();
		m_copyMenuWidth = m_pasteMenuWidth = m_clearMenuWidth = 0;
	}

	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) override;
//	virtual void DisplayClientMenu(UINT nFlags, CPoint point) override;
	virtual void AddMenuItems(CMenu& menu) override;

	virtual bool SetClientCursor() override
	{
		if(m_inEdit)
		{
			SetCursor(GetInEditCursor());
			return true;
		}
		return false;
	}

	virtual void DoSize(UINT nType, int cx, int cy, int oldX, int oldY) override
	{
		TakionCaretCustomControl::DoSize(nType, cx, cy, oldX, oldY);
		m_editRect.top = m_clientRect.top;
		m_editRect.bottom = m_clientRect.bottom;
		UpdateLeft();
		UpdateRight();
		UpdateTextRectsHeight();

//		m_editRect.left = m_leftSpinList.empty() ? m_clientRect.left : m_leftSpinList.back()->GetRight();
//		m_editRect.right = m_rightSpinList.empty() ? m_clientRect.right : m_rightSpinList.back()->GetLeft();
	}
	void UpdateLeft()
	{
		m_editRect.left = CalculateEditRectLeft();
		m_textRect.left = m_editRect.left + m_caretMargin;
	}
	void UpdateRight()
	{
		m_editRect.right = CalculateEditRectRight();
		m_textRect.right = m_editRect.right - m_caretMargin;
	}
	virtual bool UpdateTextRectsHeight() override
	{
		TakionCaretCustomControl::UpdateTextRectsHeight();
		int height = m_editRect.Height();
		if(height > 0)
		{
			int textTop = m_editRect.top + (height - m_textHeight) / 2;
			int textBottom;
			if(textTop < m_editRect.top)
			{
				textTop = m_editRect.top;
				textBottom = m_editRect.bottom;
			}
			else
			{
				textBottom = textTop + m_textHeight;
			}
			m_textRect.top = m_highlightRect.top = m_selectionRect.top = m_invalidateRect.top = textTop;
			m_textRect.bottom = m_highlightRect.bottom = m_selectionRect.bottom = m_invalidateRect.bottom = textBottom;
			return true;
		}
		return false;
	}

	afx_msg UINT OnGetDlgCode();
	DECLARE_MESSAGE_MAP()

//	virtual void DoAdditionalPaint(const RECT& interRect, CDC& dc){}
/*
	void TakionCustomControl::DoPaint(const RECT& rcPaint, CDC& dc)
	{
		CRect interRect;
		if(interRect.IntersectRect(&rcPaint, &m_clientRect))
		{
			dc.FillSolidRect(&interRect, m_bkColor);
			DoPaintClient(interRect, dc);
		}
	}
*/
	virtual void DoPaint(const RECT& rcPaint, CDC& dc) override
	{
		CRect interRect;
		if(interRect.IntersectRect(&rcPaint, &m_editRect))
		{
//			dc.FillSolidRect(&interRect, m_bkColor);
			PaintBackground(interRect, dc);

			DoPaintClient(interRect, dc);
		}
		DoAdditionalPaint(rcPaint, dc);
	}

	HCURSOR m_beamCursor;
	HCURSOR m_arrowCursor;

	CRect m_editRect;
	CRect m_textRect;
	CRect m_invalidateRect;
	CRect m_selectionRect;
	CRect m_highlightRect;
	COLORREF m_highlightColor;
	COLORREF m_selectionColor;
	COLORREF m_selectionTextColor;
	COLORREF m_textColor;
	COLORREF m_disabledTextColor;
	int m_textHeight;
	bool SetInEdit(const bool& inEdit)
	{
		if(inEdit != m_inEdit)
		{
			m_inEdit = inEdit;
//			SetCursor(inEdit ? GetInEditCursor() : GetOutEditCursor);

//			SendMessageToParent(inEdit ? WM_USER + 16 : WM_USER + 36, GetDlgCtrlID(), (LPARAM)m_hWnd);//this);
			return true;
		}
		return false;
	}
	bool m_inEdit;

	int m_copyMenuWidth;
	int m_pasteMenuWidth;
	int m_clearMenuWidth;
};

class UGUI_API SpinCell
{
public:
	const bool& isLeftJustified() const{return m_leftJustified;}
	void UpdateRects(int location, int width, int top, int bottom, int borderSize);
	int GetBorder() const{return m_leftJustified ? m_rectBorder.right : m_rectBorder.left;}
	int GetLeft() const{return m_rectBorder.left;}
	int GetRight() const{return m_rectBorder.right;}
	void Paint(const RECT& rcPaint, CDC& dc);
	const CRect& GetRectUp() const{return m_rectUp;}
	const CRect& GetRectMiddle() const{return m_rectMiddle;}
	const CRect& GetRectDown() const{return m_rectDown;}
	void SetScrollingDirection(const unsigned char& scrollingDirection){m_scrollingDirection = scrollingDirection;}
	void SetScrolling(const bool& scrolling){m_scrolling = scrolling;}
	const bool& isUpperBoundMax() const{return m_upperBoundMax;}
	const bool& isLowerBoundMin() const{return m_lowerBoundMin;}
//	void SetArrowColor(COLORREF color){m_arrowColor = color;}
	const bool& isEnabled() const{return m_enabled;}
	bool SetEnabled(const bool enabled);
	const unsigned char& GetDecDigits() const{return m_decDigits;}
	void SetBorderColor(const COLORREF& color){m_borderColor = color;}
	void SetArrowColor(const COLORREF& color){m_arrowColorEnabled = color;}
	bool SetButtonColor(COLORREF color)
	{
		if(0xFFFFFFFF == color)
		{
			color = GetSysColor(COLOR_3DFACE);
			if(color != m_buttonColor)
			{
				m_buttonColor = color;
				m_buttonLightColor = GetSysColor(COLOR_3DHIGHLIGHT);
				m_buttonDarkColor = GetSysColor(COLOR_3DSHADOW);
				return true;
			}
		}
		else if(color != m_buttonColor)
		{
			m_buttonColor = color;
			m_buttonLightColor = UGUI_CalculateLightColor(color, 50);
			m_buttonDarkColor = UGUI_CalculateDarkColor(color, 50);
			return true;
		}
		return false;
	}
protected:
	SpinCell(const bool leftJustified, const bool enabled, const COLORREF borderColor, const COLORREF arrowColor);
	bool m_leftJustified;
	bool m_enabled;

	CRect m_rectUp;
	CRect m_rectUpFace;
	CRect m_rectUpArrow;
	CRect m_rectUpArrowScrolling;
	CRect m_rectMiddle;
	CRect m_rectDown;
	CRect m_rectDownFace;
	CRect m_rectDownArrow;
	CRect m_rectDownArrowScrolling;
	CRect m_rectBorder;

	int m_buttonBorderSize;
	COLORREF m_buttonColor;
	COLORREF m_buttonLightColor;
	COLORREF m_buttonDarkColor;
	COLORREF m_arrowColorEnabled;
	COLORREF m_arrowColorDisabled;
	COLORREF m_arrowColor;
	COLORREF m_borderColor;

	unsigned char m_decDigits;

	unsigned char m_scrollingDirection;
	bool m_scrolling;

	bool m_upperBoundMax;
	bool m_lowerBoundMin;
};

template <class V>
class TypedSpinCell : public SpinCell
{
public:
	TypedSpinCell(const V& multiplier, const bool& leftJustified, const bool& enabled, const COLORREF& borderColor, const COLORREF& arrowColor, const V& upperBoundMultiplier = 0):
		SpinCell(leftJustified, enabled, borderColor, arrowColor),
		m_multiplier(multiplier),
		m_upperBoundMultiplier(1),
		m_upperBound(0),
		m_lowerBound(0)
	{
		m_decDigits = U_GetDecDigits(m_multiplier);
		SetUpperBoundMultiplier(upperBoundMultiplier);
/*
		if(upperBoundMultiplier)
		{
			if(upperBoundMultiplier == 1)
			{
				m_upperBoundMultiplier = 10;
			}
			else 
			{
				m_upperBoundMultiplier = 1;
				for(--upperBoundMultiplier; upperBoundMultiplier; upperBoundMultiplier /= 10, m_upperBoundMultiplier *= 10);
			}
			if(m_upperBoundMultiplier <= m_multiplier)
			{
				m_upperBoundMultiplier = 0;
			}
		}
*/
	}
	void SetMultipliers(const V& multiplier, V upperBoundMultiplier)
	{
		SetMultiplier(multiplier);
		SetUpperBoundMultiplier(upperBoundMultiplier);
	}
	void SetMultiplier(const V& multiplier)
	{
		m_multiplier = multiplier;
		m_decDigits = U_GetDecDigits(m_multiplier);
	}
	void SetUpperBoundMultiplier(V upperBoundMultiplier)
	{
		if(upperBoundMultiplier)
		{
			if(upperBoundMultiplier == 1)
			{
				m_upperBoundMultiplier = 10;
			}
			else 
			{
				m_upperBoundMultiplier = 1;
				for(--upperBoundMultiplier; upperBoundMultiplier; upperBoundMultiplier /= 10, m_upperBoundMultiplier *= 10);
			}
			if(m_upperBoundMultiplier <= m_multiplier)
			{
				m_upperBoundMultiplier = 0;
			}
		}
		else
		{
			m_upperBoundMultiplier = 1;
		}
	}

	const V& GetMultiplier() const{return m_multiplier;}
	const V& GetUpperBoundMultiplier() const{return m_upperBoundMultiplier;}
	void SetBounds(bool increment, const V& currentValue, const V& maxValue, const V& minValue)
	{
		if(m_upperBoundMultiplier)
		{
			m_upperBoundMax = false;
			m_lowerBoundMin = false;
			V remainder = currentValue % m_upperBoundMultiplier;
//			if(remainder || currentValue >= 0)
//			{
				if(currentValue < 0 || currentValue == 0 && !increment)
				{
					m_upperBound = currentValue - remainder;
					if(m_upperBound > maxValue || m_upperBound < currentValue)
					{
						m_upperBound = maxValue;
						m_upperBoundMax = true;
					}

					m_lowerBound = currentValue - (m_upperBoundMultiplier + remainder);
					if(m_lowerBound < minValue || m_lowerBound > currentValue || m_lowerBound > 0)
					{
						m_lowerBound = minValue;
						m_lowerBoundMin = true;
						V upper = m_lowerBound + m_upperBoundMultiplier;
						remainder = upper % m_upperBoundMultiplier;
						upper -= remainder;
						if(upper > m_upperBound)// && upper > m_upperBound)
						{
							m_upperBound = upper < maxValue ? upper : maxValue;
						}
					}
				}
				else
				{
					m_lowerBound = currentValue - remainder;
					if(m_lowerBound < minValue || m_lowerBound > currentValue)
					{
						m_lowerBound = minValue;
						m_lowerBoundMin = true;
					}
					m_upperBound = currentValue + (m_upperBoundMultiplier - remainder);
					if(m_upperBound > maxValue || m_upperBound < currentValue || m_upperBound < 0)
					{
						m_upperBound = maxValue;
						m_upperBoundMax = true;
						if(m_upperBound >= m_upperBoundMultiplier)
						{
							if(m_lowerBound >= m_upperBound)//02/11/2015
							{
								m_lowerBound = m_upperBound - m_upperBoundMultiplier;
								remainder = m_lowerBound % m_upperBoundMultiplier;
								m_lowerBound -= remainder;
							}
						}
					}
				}
//			}
/*
			else if(increment)
			{
				m_lowerBound = currentValue;
				m_upperBound = currentValue + m_upperBoundMultiplier;
				if(m_upperBound > maxValue || m_upperBound < currentValue || maxValue > 0 && m_upperBound < 0)
				{
					m_upperBound = maxValue;
				}
			}
*/
/*
			else
			{
				m_upperBound = currentValue;
				m_lowerBound = currentValue - m_upperBoundMultiplier;
				if(m_lowerBound < minValue || m_lowerBound > currentValue || minValue < 0 && m_lowerBound > 0)
				{
					m_lowerBound = minValue;
				}
			}
*/
		}
		else
		{
			m_upperBoundMax = false;
			m_lowerBoundMin = false;
			m_upperBound = 0;
			m_lowerBound = 0;
		}
	}
	const V& GetUpperBound() const{return m_upperBound;}
	const V& GetLowerBound() const{return m_lowerBound;}
protected:
	V m_multiplier;
	V m_upperBoundMultiplier;
	V m_upperBound;
	V m_lowerBound;
};

class CharCellBase
{
public:
	CharCellBase(const char& mainChar = '\0', const unsigned char& ord = 0, const bool& visible = true):
		m_ord(ord),
		m_char(mainChar),
		m_visible(visible)
	{}
	const char& GetChar() const{return m_char;}
	bool SetChar(const char& mainChar)
	{
		if(mainChar != m_char)
		{
			m_char = mainChar;
			return true;
		}
		return false;
	}
/*
	bool isDigit() const{return m_char >= '0' && m_char <= '9';}
	bool isSign() const
	{
		switch(m_char)
		{
			case '-':
			case '+':
			return true;

			default:
			return false;
		}
	}
*/
	const bool& isVisible() const{return m_visible;}
	bool SetVisible(const bool& visible)
	{
		if(visible != m_visible)
		{
			m_visible = visible;
			return true;
		}
		return false;
	}
	const unsigned char& GetOrd() const{return m_ord;}
	void SetOrd(const unsigned char& ord){m_ord = ord;}
	void IncrementOrd(){++m_ord;}
	void DecrementOrd(){--m_ord;}
	void IncrementOrd(const unsigned char& o){m_ord += o;}
	void DecrementOrd(const unsigned char& o){m_ord -= o;}
protected:
	bool m_visible;
	unsigned char m_ord;
	char m_char;
};

class CharCell : public CharCellBase
{
public:
//	CharCell(char mainChar, unsigned char ord = 0, char suffix = '\0', int suffixWidth = 0, bool visible = true):
	CharCell(const char& mainChar, const unsigned char& ord, const char& suffix, const int& suffixWidth, const bool& visible):
		CharCellBase(mainChar, ord, visible),
		m_suffix(suffix),
		m_suffixWidth(suffixWidth)
	{}
	const char& GetSuffix() const{return m_suffix;}
	void SetSuffix(const char& suffix, const int& suffixWidth){m_suffix = suffix; m_suffixWidth = suffixWidth;}
	const int& GetSuffixWidth() const{return m_suffixWidth;}
protected:
	char m_suffix;
	int m_suffixWidth;
};

class UGUI_API TakionSpin : public TakionTextCustomControl
{
friend class CharCellMap;
friend class TakionDialog;
public:
	virtual ~TakionSpin();
	static const char* const takionSpinClassName;
	virtual const char* GetCustomClassName() const override{return takionSpinClassName;}
	static const char charComma = ',';
	static const char charDot = '.';
	static const char charSlash = '/';
	static const char charMinus = '-';
	static const char charPlus = '+';
	static const char charColon = ':';

	typedef std::list<SpinCell*> SpinList;
	typedef SpinList::iterator SpinIterator;
	typedef SpinList::const_iterator SpinConstIterator;
	static void DestroySpinList(SpinList& spinList, SpinIterator& spinEnd);

	const unsigned char& GetDecDigits() const{return m_decDigits;}
	virtual bool SetDecDigits(unsigned char dec)
	{
		if(m_decDigits != dec)
		{
			m_decDigits = dec;
			return true;
		}
		return false;
	}

	void AddSpinCell(SpinCell* spinCell);
	void InsertSpinCell(SpinCell* spinCell, unsigned char at);
	SpinCell* RemoveSpinCell(bool left, unsigned char at);
	void RemoveAndDestroySpinCell(bool left, unsigned char at);
	void ClearAndDestroySpinCells(bool left);
	SpinCell* GetSpinCell(bool left, unsigned char at);
	void Unselect();
	void Unhighlight();
	void Highlight();
	void HighlightUnderMouse();
	bool DeleteSelection(bool refreshValue);
	int GetDigitWidth(const unsigned char& digit) const{return digit < 10 ? m_digitWidth[digit] : 0;}
	const int& GetMaxDigitWidth() const{return m_maxDigitWidth;}
	const int& GetSpinButtonWidth() const{return m_spinButtonWidth;}
	const int& GetHalfHeight() const{return m_halfHeight;}

//	bool Spin(UINT nFlags, bool rightButton, bool increment)
	bool Spin(const UINT& nFlags, const unsigned char& button, const bool& increment)//0 - left, 1 - right, 2 - middle
	{
		if(UpdateValueNum(true) == 2)
		{
			UpdateValueStr();
			return true;
		}
		else if(DoSpin(nFlags, button, increment))
		{
			UpdateValueStr();
			return true;
		}
		return false;
	}
	unsigned char UpdateValueNum(bool adjustToMinMax = true) const//0 - did not change, 1 - changed, 2 -  exceeded limits
	{
		if(!m_numericValueValid)
		{
			m_numericValueValid = true;
			return DoUpdateValueNum(adjustToMinMax);
		}
		return 0;//false;
	}

//	const CRect& GetEditRect() const{return m_editRect;}
//	const CRect& GetTextRect() const{return m_textRect;}
	bool isStringValueValid() const;
	void UpdateCaretLocation(unsigned char pos);
	virtual bool isSigned() const{return false;}
	char GetFirstChar() const;
	char GetNextChar() const;
	unsigned char GetCellCount() const;//m_cellCount;
	virtual int GetEditLeftOffset() const{return 0;}
	virtual int GetEditRightOffset() const{return 0;}

	const unsigned char& GetMaxLength() const{return m_maxLength;}
	const unsigned char& GetMaxFirstDigit() const{return m_maxFirstDigit;}

	unsigned char GetMinDigitValue(const unsigned char& ord) const{return m_minDigitValues && ord < m_maxLength ? m_minDigitValues[ord] : 0;}
	unsigned char GetMaxDigitValue(const unsigned char& ord) const{return m_maxDigitValues && ord < m_maxLength ? m_maxDigitValues[ord] : 0;}
	void SetMinDigitValue(const unsigned char& ord, const unsigned char& value){if(m_minDigitValues && ord < m_maxLength)m_minDigitValues[ord] = value;}
	void SetMaxDigitValue(const unsigned char& ord, const unsigned char& value){if(m_maxDigitValues && ord < m_maxLength)m_maxDigitValues[ord] = value;}
	unsigned char GetLeftmostMinDigitValue() const{return m_minDigitValues && m_maxLength ? m_minDigitValues[m_maxLength - 1] : 0;}
	unsigned char GetLeftmostMaxDigitValue() const{return m_maxDigitValues && m_maxLength ? m_maxDigitValues[m_maxLength - 1] : 0;}
	void SetLeftmostMinDigitValue(const unsigned char& value){if(m_minDigitValues && m_maxLength)m_minDigitValues[m_maxLength - 1] = value;}
	void SetLeftmostMaxDigitValue(const unsigned char& value){if(m_maxDigitValues && m_maxLength)m_maxDigitValues[m_maxLength - 1] = value;}

	void SelectAll();

	void Clear();
	void ValidateNumericValue();
	virtual short CompareMultipliers(const SpinCell& first, const SpinCell& second) const{return 0;}

	virtual bool ProcessDigit(unsigned char digit, bool repeat, bool force = false);
	virtual bool ProcessCtrlChar(unsigned char ctrlChar, bool repeat, bool force = false);
	const bool& isProcessCtrlChars() const{return m_processCtrlChars;}
	const bool& isProcessDigits() const{return m_processDigits;}
	void SetProcessCtrlChars(const bool& processCtrlChars){m_processCtrlChars = processCtrlChars;}
	void SetProcessDigits(const bool& processDigits){m_processDigits = processDigits;}


	const COLORREF& GetButtonColor() const{return m_buttonColor;}//if 0xFFFFFFFF then GetSysColor(COLOR_3DFACE);
	void SetButtonColor(const COLORREF& color)
	{
		if(color != m_buttonColor)
		{
			m_buttonColor = color;
			SetSpinsColor(color);
//			RepaintSpins();
		}
	}
	bool EnableNotification(const bool& enable)
	{
		if(enable == m_initializing)
		{
			m_initializing = !enable;
			return true;
		}
		return false;
	}
	const bool& isInitializing() const{return m_initializing;}
	virtual bool isShowPlus() const{return false;}
//	virtual unsigned char GetCellOrdinalAtSpinCell(const SpinCell* spinCell) const{return 0xFF;}
	virtual bool AllVisible() const{return false;}
//	virtual unsigned char GetMinusCount() const{return 0;}
//	unsigned char GetSignCount() const;//{return m_cellMap->isFirstCharSign() ? 1 : 0;}
	virtual bool isValueNegative() const{return false;}
	virtual bool isValuePositive() const{return !isZero();}
	virtual bool isNegative() const{return false;}
	virtual bool isZero() const{return true;}
	virtual bool SetNegative(const bool& negative, const bool& notifyParent = true){return false;}
	virtual bool ToggleNegative(const bool& notifyParent = true){return false;}
	virtual bool SetValueZero(const bool& notifyParent = true){return false;}
	virtual bool SetValueExtreme(const bool& notifyParent = true){return false;}

	bool SetPrefix(const char prefix, const int prefixWidth);
	const int& GetPrefixWidth() const{return m_prefixWidth;}
	unsigned char GetLeftSpinCount() const{return (unsigned char)m_leftSpinList.size();}
	unsigned char GetRightSpinCount() const{return (unsigned char)m_rightSpinList.size();}

	virtual int CalculateEditRectLeft() const override{return m_leftSpinList.empty() ? m_clientRect.left : m_leftSpinList.back()->GetRight();}
	virtual int CalculateEditRectRight() const override{return m_rightSpinList.empty() ? m_clientRect.right : m_rightSpinList.back()->GetLeft();}
protected:
	TakionSpin(unsigned char groupLength = 0,
		char groupChar = '\0',
		unsigned char decDigits = 0,
		char decimalChar = charDot,
		int borderWidth = 1,
		bool processCtrlChars = true,
		bool processDigits = true,
		COLORREF borderColor = 0,
		const char* toolTipText = nullptr,
		CToolTipCtrl* externalToolTip = nullptr);
	void DestroyDigitValues();
//	void BuildCaret();
	virtual void OnBuildCaret() override{Highlight();}
	virtual bool CalculateMaxLength(){return false;}
	virtual bool CalculateMaxFirstDigit(){return false;}
	BOOL RegisterWindowClass();
	virtual void PreSubclassWindow() override;
	virtual void SpinCreated(){}
	virtual void DoSize(UINT nType, int cx, int cy, int oldX, int oldY) override;
	virtual void DoPaint(const RECT& rcPaint, CDC& dc) override;
	virtual bool ProcessKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) override;
	virtual bool ProcessKeyUp(UINT nChar, UINT nFlags) override;

	virtual bool DoSpin(UINT nFlags, unsigned char button, bool increment){return false;}//0 - left, 1 - right, 2 - middle
	virtual unsigned char DoUpdateValueNum(bool adjustToMinMax) const = 0;//0 - did not change, 1 - changed, 2 -  exceeded limits

	virtual void ResetSpinRate(){}
	virtual bool IncreaseSpinRate(){return false;}
	virtual void MouseLeft() override;
	virtual void Wheel(short steps, UINT nFlags, CPoint pt) override;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	DECLARE_MESSAGE_MAP()
	virtual void FocusGained() override;
	virtual void FocusLost() override;
	virtual void OnEnabledStatusChange() override;

	virtual void UpdateNegative(const bool notifyParent){}

//	virtual void PreSetMouseFocus() override;

	bool Pad(const bool& realValueModified);
	void UpdateDigitValues(const unsigned char oldMaxLength, unsigned char*& digitValues, const bool preserveOldValues, const unsigned char value, const unsigned char firstValue);

	void OnButtonUp(bool& buttonDown, const CPoint& point)//OnLButtonUp
	{
		StopScrolling();
		m_scrollingDisabled = false;
		if(buttonDown)
		{
			buttonDown = false;
			ReleaseCapture();
			m_mousePointX = point.x;
			HighlightUnderMouse();
		}
	}

	void RefreshValue(bool force = false, bool adjustToMinMax = true);

	void HighlightAtSpinCell();
	void UnhighlightAtSpinCell(bool nullifySpinCellUnderMouse = true);
	bool SetSpinCellUnderMouse(SpinCell* const& spinCellUnderMouse)
	{
		if(spinCellUnderMouse != m_spinCellUnderMouse)
		{
			m_spinCellUnderMouse = spinCellUnderMouse;
			HighlightAtSpinCell();
			return true;
		}
		return false;
	}
//	void IncrementCell(const CharCell& cell, short zDelta);

	void StartScrolling(UINT nFlags, CPoint point, unsigned char button);//0 - left, 1 - right, 2 - middle

	bool InitScrolling(SpinCell* spinScrolling, UINT nFlags, const CPoint& point, unsigned char button);//0 - left, 1 - right, 2 - middle//bool rightButton);
	virtual void InitScrolling(SpinCell* spinScrolling, UINT nFlags, unsigned char button, bool up);//0 - left, 1 - right, 2 - middle
	void StopScrolling();

	unsigned char m_scrollingDirection;
	bool m_scrolling;
	bool SetScrolling(bool scrolling);
	bool m_scrollingDisabled;

	void InvalidateNumericValue(bool realValueModified = true);
	virtual void NotifyParentAboutValueChange(bool realValueModified);
	mutable bool m_numericValueValid;
	int m_mousePointX;

	unsigned int m_keyboardRepeatDelay;
	unsigned int m_keyboardRepeatInterval;
	unsigned int m_repeatCount;
	unsigned int m_repeatCountCycle;
	unsigned int m_repeatCountTrigger;
	void DoUnselect();
	virtual void DoUpdateCaretPosition() override;
	virtual void BeforeDestroy() override;
	virtual void DoPaintClient(const RECT& interRect, CDC& dc) override;
//	virtual void DoAdditionalPaint(const RECT& interRect, CDC& dc){}
	virtual void OnFontChange(CDC* dc) override;
	virtual bool UpdateTextRectsHeight() override;
	virtual void UpdateValueStr(bool realValueModified = true);
	virtual void DoUpdateValueStr(bool realValueModified = true) = 0;

	CharCellMap* m_cellMap;

	void SetSpinsColor(COLORREF color);
//	void RepaintSpins();

//	void InsertDigitAtBegin(unsigned char digit, bool realValueModified = true);
	void InsertDigitAtBegin(unsigned char digit, bool realValueModified, bool visible);
//	void InsertCellAtBegin(char c, int width, bool realValueModified = true);
	void InsertCellAtBegin(char c, int width, bool realValueModified, bool visible);
	void RemoveCellAtBegin();
	void AdjustCaretAtNotVisible();
	unsigned char m_caretPos;
	unsigned char m_selectionStartPos;
	unsigned char m_selectionEndPos;
	char m_prefix;
	bool UpdatePrefixRect();
	CRect m_prefixRect;
	CRect m_highlightAtSpinCellRect;

	COLORREF m_buttonColor;
	unsigned char m_maxLength;
	unsigned char m_maxFirstDigit;
	bool m_lButtonDown;
	bool m_mButtonDown;
	bool m_rButtonDown;
	bool m_focusSetFirstTime;
	unsigned char m_buttonScrolling;//0 - left, 1 - right, 2 - middle
	unsigned char m_decDigits;
	unsigned char m_groupLength;
	unsigned char m_groupLengthMinusOne;
	char m_groupChar;
	int m_groupCharWidth;
//	int m_dotWidth;
//	int m_slashWidth;
//	bool m_decimalFraction;
	char m_fractionSeparator;
	int m_fractionSeparatorWidth;
	int m_digitWidth[10];
	int m_maxDigitWidth;
	int m_spinButtonWidth;
	int m_halfHeight;

	unsigned int m_lButtonDownMillisecond;
	unsigned int m_doubleClickMillisecond;
	CPoint m_lButtonDownPoint;
	CPoint m_doubleClickPoint;

	virtual void BorderColorChanged() override
	{
		SpinCell* spinCell;
		SpinIterator it = m_leftSpinList.begin();
		for(; it != m_leftSpinEnd; ++it)
		{
			spinCell = *it;
			spinCell->SetBorderColor(m_borderColor);
			spinCell->SetArrowColor(m_borderColor);
		}
	}
	void UpdateSpinCellSizes();
	SpinList m_leftSpinList;
	SpinList m_rightSpinList;
	SpinIterator m_leftSpinEnd;
	SpinIterator m_rightSpinEnd;
	SpinCell* m_spinScrolling;
	SpinCell* m_spinLowest;
	SpinCell* m_spinHighest;
	SpinCell* m_spinCellUnderMouse;
	bool m_keyScrolling;
	void SetOverwriteMode();
	bool m_overwriteMode;
	bool m_wholeMode;

	int m_minusWidth;
	int m_plusWidth;
	int m_prefixWidth;
	unsigned char* m_minDigitValues;
	unsigned char* m_maxDigitValues;

	bool m_initializing;

	bool m_processCtrlChars;
	bool m_processDigits;
};

template <class T>
class DefaultMaxSpinRate
{
public:
	static const T defaultMaxSpinRate = sizeof(T) > 1 ? 1000 : 100;
};
//const V& maxSpinRate = DefaultMaxSpinRate<ValueType>::defaultMaxSpinRate,//GetDefaultMaxSpinRate<V>(),//1000,//MaxSpin,

template<class V>//, V MaxSpin = 1000>//class UV = V, UV MaxSpin = 1000>
class NumberTypeSpin : public TakionSpin
{
public:
	typedef V ValueType;
	typename typedef std::make_unsigned<V>::type UV;
	static const ValueType defaultMaxSpinRate = DefaultMaxSpinRate<ValueType>::defaultMaxSpinRate;
	virtual short CompareMultipliers(const SpinCell& first, const SpinCell& second) const
	{
		V m1 = ((const TypedSpinCell<V>&)first).GetMultiplier();
		V m2 = ((const TypedSpinCell<V>&)second).GetMultiplier();
		return m1 < m2 ? -1:
			m1 > m2 ? 1:
			0;
	}
	void SetUpperBoundMultiplier(const bool& leftJustified, const unsigned char& at, const V& multiplier)
	{
		TypedSpinCell<V>* cell = (TypedSpinCell<V>*)GetSpinCell(leftJustified, at);
		if(cell)
		{
			cell->SetUpperBoundMultiplier(multiplier);
		}
	}
	V GetUpperBoundMultiplier(const bool& leftJustified, const unsigned char& at)
	{
		TypedSpinCell<V>* cell = (TypedSpinCell<V>*)GetSpinCell(leftJustified, at);
		return cell ? cell->GetUpperBoundMultiplier() : 0;
	}
	void SetSpinCellMultiplier(const V& multiplier, const bool& leftJustified, const unsigned char& at, const V& upperBoundMultiplier = 0)
	{
		TypedSpinCell<V>* cell = (TypedSpinCell<V>*)GetSpinCell(leftJustified, at);
		if(cell)
		{
			cell->SetMultipliers(multiplier, upperBoundMultiplier);
		}
	}
	void AddSpinCell(const V& multiplier, const bool& leftJustified, const V& upperBoundMultiplier = 0)
	{
		TypedSpinCell<V>* spinCell = new TypedSpinCell<V>(multiplier, leftJustified, m_enabled, m_borderColor, m_borderColor, upperBoundMultiplier);
		TakionSpin::AddSpinCell(spinCell);
		OnSpinCellAdded(spinCell);
	}
	void InsertSpinCell(const V& multiplier, const bool& leftJustified, const unsigned char& at, const V& upperBoundMultiplier = 0)
	{
		TypedSpinCell<V>* spinCell = new TypedSpinCell<V>(multiplier, leftJustified, m_enabled, m_borderColor, m_borderColor, upperBoundMultiplier);
		TakionSpin::InsertSpinCell(spinCell, at);
		OnSpinCellAdded(spinCell);
	}
	const V& GetMinValue() const{return m_minValue;}
	const V& GetMaxValue() const{return m_maxValue;}
	V GetRange() const{return m_maxValue > m_minValue ? m_maxValue - m_minValue : 0;}
	bool hasRange() const{return m_maxValue > m_minValue;}

	void SetMinMaxValue(const V& minValue, const V& maxValue, const bool preserveOldDigitLimits = false)
	{
		if(minValue <= maxValue)
		{
			bool changed = false;
			if(minValue != m_minValue)
			{
				m_minValue = minValue;
				m_uminValue10 = (UV)m_minValue / 10;
				m_uminValue1 = (unsigned char)((UV)m_minValue - 10 * m_uminValue10);
				changed = true;
			}
			if(maxValue != m_maxValue)
			{
				m_maxValue = maxValue;
				m_umaxValue10 = (UV)m_maxValue / 10;
				m_umaxValue1 = (unsigned char)((UV)m_maxValue - 10 * m_umaxValue10);
				changed = true;
			}

			if(changed)
			{
				const unsigned char oldMaxLength = m_maxLength;

				bool changed = CalculateMaxLength();
				CalculateMaxFirstDigit();
				bool realValueModified = false;
				if(m_value < m_minValue)
				{
					realValueModified = SetValue(m_minValue);
				}
				if(m_value > m_maxValue)
				{
					realValueModified = SetValue(m_maxValue);
				}
				if(changed)
				{
					const unsigned char v1 = m_uminValue1 > m_umaxValue1 ? m_uminValue1 : m_umaxValue1;
//					UpdateDigitValues(oldMaxLength, m_minDigitValues, true, 0, 0);
//					UpdateDigitValues(oldMaxLength, m_maxDigitValues, true, 9, m_maxFirstDigit);
					UpdateDigitValues(oldMaxLength, m_minDigitValues, preserveOldDigitLimits, 0, 0);
					UpdateDigitValues(oldMaxLength, m_maxDigitValues, preserveOldDigitLimits, 9, m_maxFirstDigit);
					if(Pad(realValueModified))
					{
						UpdatePrefixRect();
					}
				}
			}
		}
	}
	void SetMinValue(const V& minValue)
	{
		SetMinMaxValue(minValue, m_maxValue);
	}
	void SetMaxValue(const V& maxValue)
	{
		SetMinMaxValue(m_minValue, maxValue);
	}

	const V& GetValue() const{UpdateValueNum(true); return m_value;}
	bool SetValue(const V& v, bool updateValueStr = false, bool realValueModified = true, bool notifyParent = true)
	{
		bool ret = false;
		notifyParent = !notifyParent && EnableNotification(false);
		V value = v;
		AdjustValue(value);
		if(DoSetValue(value))
//		if(m_value != value)
		{
//			m_value = value;
			if(m_hWnd)
			{
				UpdateValueStr(realValueModified);
				m_numericValueValid = true;
			}
			ret = true;
		}
/*10/09/2020
		else if(updateValueStr && m_hWnd)
		{
			UpdateValueStr(realValueModified);
			m_numericValueValid = true;
		}
*/
		else if(m_hWnd)//10/09/2020
		{
			if(updateValueStr)
			{
				UpdateValueStr(realValueModified);
			}
			m_numericValueValid = true;
		}
		if(notifyParent)EnableNotification(true);
		return ret;
	}
	virtual bool SetValueZero(const bool& notifyParent = true) override
	{
		return SetValue(0, false, true, notifyParent);
	}
	virtual bool SetValueExtreme(const bool& notifyParent = true) override
	{
		return SetValue(m_maxValue, false, true, notifyParent);
	}
	inline bool AdjustValue(V& value)
	{
		if(value < m_minValue)
		{
			value = m_minValue;
			return true;
		}
		else if(value > m_maxValue)
		{
			value = m_maxValue;
			return true;
		}
		return false;
	}
	inline static unsigned char GetLastDigit(UV& number)
	{
		V n10 = number / 10;
		unsigned char digit = (unsigned char)(number - 10 * n10);
		number = n10;
		return digit;
	}
	inline static bool AppendDigit(V& value, V& prevValue, unsigned char digit)
	{
		value *= 10;
		value += digit;
		if(value < prevValue)
		{
			return false;
		}
		prevValue = value;
		return true;
	}
	static inline V CalculateRoundedSpinRate(const V& rate)
	{
		V divider = 1;
		V roundedRate = rate / 10;
		for(; roundedRate; divider *= 10, roundedRate /= 10)
		{
		}
		return divider;
	}
	virtual void InitScrolling(SpinCell* spinScrolling, UINT nFlags, unsigned char button, bool up) override//0 - left, 1 - right, 2 - middle
	{
		((TypedSpinCell<V>*)spinScrolling)->SetBounds(up, m_value, m_maxValue, m_minValue);
		TakionSpin::InitScrolling(spinScrolling, nFlags, button, up);
	}
	const V& GetMaxSpinRate() const{return m_maxSpinRate;}
	void SetMaxSpinRate(const V& spinRate){m_maxSpinRate = spinRate;}

	virtual bool isZero() const override{return !m_value;}

	virtual bool SetDecDigits(unsigned char dec) override
	{
		unsigned char prev = m_decDigits;
		if(TakionSpin::SetDecDigits(dec))
		{
			V value = m_value;
			if(prev < m_decDigits)
			{
				for(unsigned char diff = m_decDigits - prev; diff; --diff)
				{
					value *= 10;
				}
			}
			else
			{
				for(unsigned char diff = prev - m_decDigits; diff; --diff)
				{
					value /= 10;
				}
			}
			SetValue(value, true, false);
			return true;
		}
		return false;
	}
	virtual bool isShowPlus() const override{return m_showPlus;}
	const bool& isCycle() const{return m_cycle;}

protected:
	NumberTypeSpin(const V& maxValue,
		const V& minValue = 0,
		const V& value = 0,
		const V& maxSpinRate = defaultMaxSpinRate,//DefaultMaxSpinRate<ValueType>::defaultMaxSpinRate,//GetDefaultMaxSpinRate<V>(),//1000,//MaxSpin,
		const unsigned char& groupLength = 0,
		const char& groupChar = '\0',
		const unsigned char& decDigits = 0,
		const char& decimalChar = charDot,
		const int& borderWidth = 1,
		const bool& processCtrlChars = true,
		const bool& processDigits = true,
		const bool& showPlus = false,
		const COLORREF& borderColor = 0,
		const bool& cycle = true,
		const char* const& toolTipText = nullptr,
		CToolTipCtrl* externalToolTip = nullptr):

		TakionSpin(groupLength, groupChar, decDigits, decimalChar, borderWidth, processCtrlChars, processDigits, borderColor, toolTipText, externalToolTip),
		m_maxValue(maxValue),
		m_minValue(minValue < maxValue ? minValue : maxValue),
		m_umaxValue10((UV)m_maxValue / 10),
		m_umaxValue1((unsigned char)((UV)m_maxValue - 10 * m_umaxValue10)),
		m_uminValue10((UV)m_minValue / 10),
		m_uminValue1((unsigned char)((UV)m_minValue - 10 * m_uminValue10)),
		m_initialValue(value),
		m_value(m_initialValue),
		m_spinRate(1),
		m_roundedSpinRate(CalculateRoundedSpinRate(m_spinRate)),
		m_maxSpinRate(maxSpinRate),
		m_spinRateChanged(false),
		m_showPlus(showPlus),
		m_cycle(cycle)
	{
		if(AdjustValue(m_initialValue))
		{
			m_value = m_initialValue;
		}
	}
	void OnSpinCellAdded(TypedSpinCell<V>* spinCell)
	{
		if(m_spinLowest)
		{
			if(((const TypedSpinCell<V>*)m_spinLowest)->GetMultiplier() > spinCell->GetMultiplier())
			{
				m_spinLowest = spinCell;
			}
		}
		else
		{
			m_spinLowest = spinCell;
		}
		if(m_spinHighest)
		{
			if(((const TypedSpinCell<V>*)m_spinHighest)->GetMultiplier() < spinCell->GetMultiplier())
			{
				m_spinHighest = spinCell;
			}
		}
		else
		{
			m_spinHighest = spinCell;
		}
	}
	virtual void ResetSpinRate()
	{
		m_spinRate = 1;
		m_roundedSpinRate = CalculateRoundedSpinRate(m_spinRate);
		m_spinRateChanged = false;
	}
	virtual bool IncreaseSpinRate()
	{
		if(m_spinRate < m_maxSpinRate)
		{
			m_spinRate <<= 1;//+= m_spinRateIncrement;
			if(m_spinRate > m_maxSpinRate)
			{
				 m_spinRate = m_maxSpinRate;
			}
			V roundedSpinRate = CalculateRoundedSpinRate(m_spinRate);
			if(m_roundedSpinRate != roundedSpinRate)
			{
				m_roundedSpinRate = roundedSpinRate;
				m_spinRateChanged = true;
				return true;
			}
		}
		return false;
	}
/*
	virtual unsigned char GetCellOrdinalAtSpinCell(const SpinCell* spinCell) const override
	{
		return U_GetDecDigits(((const TypedSpinCell<V>*)m_spinScrolling)->GetMultiplier());
	}
*/
//	virtual bool DoSpin(UINT nFlags, bool rightButton, bool increment) override
	virtual bool DoSpin(UINT nFlags, unsigned char button, bool increment) override//0 - left, 1 - right, 2 - middle
	{
//		const V& multiplier = ((const TypedSpinCell<V>*)m_spinScrolling)->GetMultiplier();
		V multiplier = ((const TypedSpinCell<V>*)m_spinScrolling)->GetMultiplier();
		if(nFlags & MK_CONTROL)
		{
			multiplier *= 100;
		}
		switch(button)
		{
			case 0://left
			break;

			case 1://right
			multiplier *= 10;
			break;

			default://2: middle
			multiplier *= 100;
			break;
		}
/*
		if(rightButton)
		{
			multiplier *= 10;
		}
*/
		const V& upperBoundMultiplier = ((const TypedSpinCell<V>*)m_spinScrolling)->GetUpperBoundMultiplier();
		bool useBound = m_cycle && upperBoundMultiplier > multiplier;
		V upperBound;
		V lowerBound;
		V upperBoundMultiplier10;
		if(useBound)
		{
			upperBound = ((const TypedSpinCell<V>*)m_spinScrolling)->GetUpperBound();
			lowerBound = ((const TypedSpinCell<V>*)m_spinScrolling)->GetLowerBound();
			upperBoundMultiplier10 = upperBoundMultiplier / 10;
		}
		bool changed = false;
		if(increment)
		{
			if(m_value < m_maxValue || useBound)
			{
				V delta = m_roundedSpinRate * multiplier;
				if(useBound && delta > upperBoundMultiplier10)
				{
					delta = upperBoundMultiplier10;
				}
				V value = m_value + delta;
				if(value > m_maxValue || value < m_value)
				{
					if(useBound && m_value >= upperBound)
					{
						m_value = lowerBound;

						if(m_value < 0 && !m_spinScrolling->isLowerBoundMin())
						{
							m_value += multiplier;
						}
						ValueChanged();
						value = m_value;
						if(m_spinRateChanged)
						{
							m_spinRateChanged = false;
						}
						changed = true;
					}
					else
					{
						ResetSpinRate();
						value = m_value + m_roundedSpinRate * multiplier;
						if(value > m_maxValue || value < m_value)
						{
							m_spinRateChanged = false;
//							if(multiplier == 1)
//							{
								value = m_maxValue;
								changed = true;
//							}
						}
						else
						{
							if(m_spinRateChanged)
							{
								m_spinRateChanged = false;
							}
							changed = true;
						}
					}
				}
				else
				{
					if(m_spinRateChanged)
					{
//						value -= value % m_roundedSpinRate;
						m_spinRateChanged = false;
					}
					changed = true;
				}
				if(changed)
				{
					if(useBound && (m_value < 0 ? value > upperBound : value >= upperBound) && value != m_maxValue)
					{
						m_value = lowerBound;
						if(m_value < 0 && !m_spinScrolling->isLowerBoundMin())
						{
							m_value += multiplier;
						}
					}
					else
					{
						m_value = value;
					}
					ValueChanged();
				}
			}
		}
		else
		{
			if(m_value > m_minValue || useBound)
			{
				V delta = m_roundedSpinRate * multiplier;
				if(useBound && delta > upperBoundMultiplier10)
				{
					delta = upperBoundMultiplier10;
				}
				V value = m_value - delta;
				if(value < m_minValue || value > m_value)
				{
					if(useBound && m_value <= lowerBound)
					{
						m_value = upperBound;
						if(m_value > 0 && !m_spinScrolling->isUpperBoundMax() && m_spinScrolling != m_spinHighest)
						{
							m_value -= multiplier;
						}
						ValueChanged();
						value = m_value;
						if(m_spinRateChanged)
						{
							m_spinRateChanged = false;
						}
						changed = true;
					}
					else
					{
						ResetSpinRate();
						value = m_value - m_roundedSpinRate * multiplier;
						if(value < m_minValue || value > m_value)
						{
							m_spinRateChanged = false;
//							if(multiplier == 1)
//							{
								value = m_minValue;
								changed = true;
//							}
						}
						else
						{
							if(m_spinRateChanged)
							{
								m_spinRateChanged = false;
							}
							changed = true;
						}
					}
				}
				else
				{
					if(m_spinRateChanged)
					{
						m_spinRateChanged = false;
					}
					changed = true;
				}
				if(changed)
				{
					if(useBound && (m_value < 0 ? value <= lowerBound : value < lowerBound) && value != m_minValue)
//					if(useBound && (value < 0 ? value <= lowerBound : value < lowerBound) && value != m_minValue)
//					if(useBound && value < lowerBound && value != m_minValue)
					{
						m_value = upperBound;
//						if(value < 0)
						if(m_value > 0 && !m_spinScrolling->isUpperBoundMax() && m_spinScrolling != m_spinHighest)
						{
							m_value -= multiplier;
						}
					}
					else
					{
						m_value = value;
					}
					ValueChanged();
				}
			}
		}
		return changed;
	}
	virtual void SpinCreated() override
	{
//		m_value = m_initialValue;
		DoSetValue(m_initialValue);
		UpdateValueStr();
		m_numericValueValid = true;
	}

	void DoUpdateUnsignedValueStr(UV value, const char& prefix, const int& prefixWidth, const bool& realValueModified)//works for unsigned types. Redefine for signed
	{
		InsertDigitAtBegin(GetLastDigit(value), realValueModified, true);
		while(value)
		{
			InsertDigitAtBegin(GetLastDigit(value), realValueModified, true);
		}
		if(m_decDigits)
		{
			for(unsigned char i = GetCellCount(); i <= m_decDigits; ++i)
			{
				InsertDigitAtBegin(0, realValueModified, true);
			}
		}
		Pad(realValueModified);

		if(!SetPrefix(prefix, prefixWidth))
		{
			UpdatePrefixRect();
		}
	}

	V m_maxValue;
	V m_minValue;
	UV m_umaxValue10;
	unsigned char m_umaxValue1;
	UV m_uminValue10;
	unsigned char m_uminValue1;
	V m_initialValue;
	virtual void ValueChanged() const{}
	bool DoSetValue(const V& value) const
	{
		if(value != m_value)
		{
			m_value = value;
			ValueChanged();
			return true;
		}
		return false;
	}
	mutable V m_value;
	V m_spinRate;
	V m_roundedSpinRate;
	V m_maxSpinRate;
	bool m_spinRateChanged;

	bool m_showPlus;
	bool m_cycle;
};

template<class V>//, V MaxSpin = 1000>
class UnsignedNumberTypeSpin : public NumberTypeSpin<V>//, MaxSpin>//V, MaxSpin>
{
public:
	UnsignedNumberTypeSpin(const V& maxValue,
		const V& minValue = 0,
		const V& value = 0,
		const V& maxSpinRate = defaultMaxSpinRate,//DefaultMaxSpinRate<ValueType>::defaultMaxSpinRate,//1000,//MaxSpin,
		const unsigned char& groupLength = 0,
		const char& groupChar = '\0',
		const unsigned char& decDigits = 0,
		const char& decimalChar = charDot,
		const int& borderWidth = 1,
		const bool& processCtrlChars = true,
		const bool& processDigits = true,
		const bool& showPlus = false,
		const COLORREF& borderColor = 0,
		const bool& cycle = true,
		const char* const& toolTipText = nullptr,
		CToolTipCtrl* const& externalToolTip = nullptr):
		NumberTypeSpin(maxValue,
			minValue,
			value,
			maxSpinRate,
			groupLength,
			groupChar,
			decDigits,
			decimalChar,
			borderWidth,
			processCtrlChars,
			processDigits,
			showPlus,
			borderColor,
			cycle,
			toolTipText,
			externalToolTip)
	{
		CalculateMaxLength();
		CalculateMaxFirstDigit();
	}
protected:
	virtual bool CalculateMaxLength() override//
	{
		unsigned char maxLength = 0;
		V maxValue = m_maxValue;
		for(; maxValue; maxValue /= 10, ++maxLength);
		if(!maxLength)
		{
			maxLength = 1;
		}
		if(maxLength != m_maxLength)
		{
			m_maxLength = maxLength;
			return true;
		}
		return false;
	}
	virtual bool CalculateMaxFirstDigit() override
	{
		UV biggestValue = m_maxValue;
		for(; biggestValue >= 10; biggestValue /= 10);

		const unsigned char maxFirstDigit = (unsigned char)biggestValue;
		if(maxFirstDigit != m_maxFirstDigit)
		{
			m_maxFirstDigit = maxFirstDigit;
			return true;
		}
		return false;
	}
	virtual unsigned char DoUpdateValueNum(bool adjustToMinMax) const override//0 - did not change, 1 - changed, 2 -  exceeded limits//works for unsigned types. Redefine for signed
	{
		V value = 0;
		V prevValue = 0;
		unsigned char digit;

		V oldValue = m_value;
		
		char c = GetFirstChar();
		if(m_showPlus && c == charPlus)c = GetNextChar();

//		for(CellConstIterator it = m_cellMap.begin(); it != m_cellEnd; ++it)
		for(; c; c = GetNextChar())
		{
			digit = c - '0';
			if(adjustToMinMax && (value > m_umaxValue10 || value == m_umaxValue10 && digit > m_umaxValue1))
			{
				m_value = m_maxValue;
				return 2;
			}
/*
			if(value == m_umaxValue10)
			{
				if(digit > m_umaxValue1)
				{
					m_value = m_maxValue;
					return 2;
				}
			}
*/
			value *= 10;
			value += digit;
			if(value < prevValue)
			{
				m_value = m_maxValue;
				return 2;
			}
			prevValue = value;
		}
		m_value = (V)value;
		if(adjustToMinMax)
		{
			if(m_value > m_maxValue)
			{
				m_value = m_maxValue;
				return 2;
			}
			else if(m_value < m_minValue)
			{
				m_value = m_minValue;
				return 2;
			}
		}
		return m_value == oldValue ? 0 : 1;
	}
	virtual void DoUpdateValueStr(bool realValueModified = true) override//works for unsigned types. Redefine for signed
	{
//		DoUpdateUnsignedValueStr(m_value, m_showPlus && m_value ? charPlus : '\0', m_plusWidth, realValueModified);
		DoUpdateUnsignedValueStr(m_value, m_showPlus ? charPlus : '\0', m_plusWidth, realValueModified);
	}
};

template<class V>//, class UV>
class SignedNumberTypeSpin : public NumberTypeSpin<V>//, typename std::make_unsigned<V>::type>//UV>
{
public:
	SignedNumberTypeSpin(const V& maxValue,
		const V& minValue = 0,
		const V& value = 0,
		const V& maxSpinRate = defaultMaxSpinRate,//DefaultMaxSpinRate<ValueType>::defaultMaxSpinRate,//1000,
		const unsigned char& groupLength = 0,
		const char& groupChar = '\0',
		const unsigned char& decDigits = 0,
		const char& decimalChar = charDot,
		const int& borderWidth = 1,
		const bool& processCtrlChars = true,
		const bool& processDigits = true,
		const bool& showPlus = false,
		const COLORREF& borderColor = 0,
		const bool& cycle = true,
		const char* const& toolTipText = nullptr,
		CToolTipCtrl* const& externalToolTip = nullptr):
		NumberTypeSpin(maxValue,
			minValue,
			value,
			maxSpinRate,
			groupLength,
			groupChar,
			decDigits,
			decimalChar,
			borderWidth,
			processCtrlChars,
			processDigits,
			showPlus,
			borderColor,
			cycle,
			toolTipText,
			externalToolTip),
		m_negative(m_value < 0)
	{
		CalculateMaxLength();
		CalculateMaxFirstDigit();
	}
	virtual bool isSigned() const override{return true;}
	virtual bool isNegative() const override{return m_negative;}//m_value < 0;}
	virtual bool isValueNegative() const override{return m_value < 0;}
	virtual bool isValuePositive() const override{return m_value > 0;}
	virtual bool SetNegative(const bool& negative, const bool& notifyParent = true) override
	{
		if(!m_value)
		{
			if(negative != m_negative)
			{
				m_negative = negative;
				DoUpdateNegative(notifyParent);
//				DoSetNegative(negative, notifyParent);
				return true;
			}
		}
		else if(negative == (m_value > 0))// : m_value < 0)
		{
			SetValue(-m_value, true, true, notifyParent);
			return true;
		}
		return false;
	}
	virtual bool ToggleNegative(const bool& notifyParent = true) override
	{
		if(m_value)
		{
			SetValue(-m_value, true, true, notifyParent);
//			return true;
		}
		else
		{
			m_negative = !m_negative;
//			DoSetNegative(m_negative, notifyParent);
			DoUpdateNegative(notifyParent);
		}
//		return false;
		return true;
	}
	virtual bool SetValueExtreme(const bool& notifyParent = true) override
	{
		return SetValue(m_negative ? m_minValue : m_maxValue, false, true, notifyParent);
	}

//	virtual bool isValueNegative() const override{return m_value < 0;}
protected:
	virtual void UpdateNegative(const bool notifyParent) override
	{
		DoUpdateNegative(notifyParent);
	}
	void DoUpdateNegative(const bool notifyParent)
	{
		char prefix = '\0';
		int prefixWidth = 0;
		if(m_negative)
		{
			prefix = charMinus;
			prefixWidth = m_minusWidth;
		}
//		else if(!isZero() && isShowPlus())
		else if(isShowPlus())
		{
			prefix = charPlus;
			prefixWidth = m_plusWidth;
		}
		if(!SetPrefix(prefix, prefixWidth))
		{
			UpdatePrefixRect();
		}
		if(notifyParent)NotifyParentAboutValueChange(false);
	}
	virtual void ValueChanged() const override
	{
		if(m_value)
		{
			m_negative = m_value < 0;
		}
		else if(m_minValue >= 0)
		{
			m_negative = false;
		}
		else if(m_maxValue <= 0)
		{
			m_negative = true;
		}
	}
	virtual bool CalculateMaxLength() override
	{
		UV umax = m_maxValue < 0 ? (UV)-m_maxValue : (UV)m_maxValue;
		UV umin = m_minValue < 0 ? (UV)-m_minValue : (UV)m_minValue;
		m_umaxValue10 = umax / 10;
		m_umaxValue1 = (unsigned char)(umax - 10 * m_umaxValue10);
		m_uminValue10 = umin / 10;
		m_uminValue1 = (unsigned char)(umin - 10 * m_uminValue10);
		if(umax < umin)
		{
			umax = umin;
		}
		unsigned char maxLength = 0;
		for(; umax; umax /= 10, ++maxLength);
		if(!maxLength)
		{
			maxLength = 1;
		}
		if(maxLength != m_maxLength)
		{
			m_maxLength = maxLength;
			return true;
		}
		return false;
	}
	virtual bool CalculateMaxFirstDigit() override
	{
		UV biggestValue;
		if(m_maxValue < 0)
		{
			biggestValue = (UV)-m_minValue;
		}
		else if(m_minValue < 0)
		{
			biggestValue = (UV)-m_minValue;
			if(biggestValue < (UV)m_maxValue)biggestValue = (UV)m_maxValue;
		}
		else
		{
			biggestValue = (UV)m_maxValue;
		}

		for(; biggestValue >= 10; biggestValue /= 10);

		const unsigned char maxFirstDigit = (unsigned char)biggestValue;
		if(maxFirstDigit != m_maxFirstDigit)
		{
			m_maxFirstDigit = maxFirstDigit;
			return true;
		}
		return false;
	}

	virtual unsigned char DoUpdateValueNum(bool adjustToMinMax) const override//0 - did not change, 1 - changed, 2 -  exceeded limits
	{
		UV value = 0;
		UV prevValue = 0;
		V oldValue = m_value;
		char c = GetFirstChar();
//		bool negative = false;
		unsigned char digit;
		if(c)
		{
//			negative = c == charMinus;
			UV umax10;
			unsigned char umax1;
			if(m_negative)
			{
//				c = GetNextChar();
				umax10 = m_uminValue10;
				umax1 = m_uminValue1;
			}
			else
			{
//				if(m_showPlus && c == charPlus)c = GetNextChar();
				umax10 = m_umaxValue10;
				umax1 = m_umaxValue1;
			}
			for(; c; c = GetNextChar())
			{
				digit = c - '0';
				if(adjustToMinMax && (value > umax10 || value == umax10 && digit > umax1))
				{
					DoSetValue(m_negative ? m_minValue : m_maxValue);
					return 2;
				}

				value *= 10;
				value += digit;
				if(value < prevValue)
				{
					DoSetValue(m_negative ? m_minValue : m_maxValue);
					return 2;
				}
				prevValue = value;
			}
		}
		if(m_negative)
		{
			DoSetValue(-(V)prevValue);
			if(adjustToMinMax && m_value > 0)
			{
				DoSetValue(m_minValue);
				return 2;
			}
		}
		else
		{
			DoSetValue((V)prevValue);
			if(adjustToMinMax && m_value < 0)
			{
				DoSetValue(m_maxValue);
				return 2;
			}
		}
		if(adjustToMinMax)
		{
			if(m_value > m_maxValue)
			{
				DoSetValue(m_maxValue);
				return 2;
			}
			else if(m_value < m_minValue)
			{
				DoSetValue(m_minValue);
				return 2;
			}
		}
		return m_value == oldValue ? 0 : 1;//false;//m_value == 0 && negative;
	}
	virtual void DoUpdateValueStr(bool realValueModified = true) override
	{
//		if(m_value < 0)
		if(m_negative)
		{
			if(m_minValue >= 0)
			{
				m_negative = false;
				DoUpdateUnsignedValueStr((UV)-m_value, m_showPlus ? charPlus : '\0', m_plusWidth, realValueModified);
			}
			else
			{
				DoUpdateUnsignedValueStr((UV)-m_value, charMinus, m_minusWidth, realValueModified);
			}
		}
		else
		{
			if(m_maxValue <= 0)
			{
				m_negative = true;
				DoUpdateUnsignedValueStr((UV)m_value, charMinus, m_minusWidth, realValueModified);
			}
			else
			{
				DoUpdateUnsignedValueStr((UV)m_value, m_showPlus ? charPlus : '\0', m_plusWidth, realValueModified);
			}
		}
	}
/*
	virtual unsigned char GetMinusCount() const
	{
		return GetFirstChar() == charMinus ? 1 : 0;
	}
*/
	mutable bool m_negative;
};

class UGUI_API MinuteSpin : public UnsignedNumberTypeSpin<unsigned short>
{
public:
	MinuteSpin(const unsigned short& maxValue,
		const unsigned short& minValue = 0,
		const unsigned short& value = 0,
		const unsigned int& maxSpinRate = defaultMaxSpinRate,//DefaultMaxSpinRate<ValueType>::defaultMaxSpinRate,//1000,
		int borderWidth = 1,
		bool processCtrlChars = true,
		bool processDigits = true,
		COLORREF borderColor = 0,
		bool cycle = true,
		const char* toolTipText = nullptr,
		CToolTipCtrl* externalToolTip = nullptr);
	static unsigned int GetStaticValue(unsigned int minute)
	{
		unsigned int hour = minute / 60;
		return minute + 40 * hour;
	}

	static unsigned short GetStaticMinute(const unsigned short& value)
	{
		unsigned short hour = value / 100;
		return value - hour * 40;
	}

	unsigned short GetMinute() const;
	bool SetMinute(unsigned short minute, bool notifyParent = true);
	bool SetValueMode(bool valueMode, bool notifyParent = true);
	const bool& isValueMode() const{return m_valueMode;}
	virtual bool AllVisible() const override{return !m_valueMode;}
protected:
//	virtual void DoUpdateValueStr(bool realValueModified = true);
	virtual void SpinCreated() override;
	virtual unsigned char DoUpdateValueNum(bool adjustToMinMax) const override;//0 - did not change, 1 - changed, 2 -  exceeded limits
	virtual bool DoSpin(UINT nFlags, unsigned char button, bool increment) override;//0 - left, 1 - right, 2 - middle
	bool VerifyTokens(bool* maxMinutes = nullptr) const;
	bool m_valueMode;
};

//#define TIME_SPIN_TEMPLATE

#ifdef TIME_SPIN_TEMPLATE

template<class T, class SpinType>
class TimeSpinTemplate : public SpinType //UnsignedNumberTypeSpin<unsigned int>
{
public:
	TimeSpinTemplate(const bool& milliseconds,
		const T& maxValue,
		const T& minValue,
		const T& value = 0,
		const T& maxSpinRate = defaultMaxSpinRate,//DefaultMaxSpinRate<T>::defaultMaxSpinRate,// = 1000,
		const char& groupLength = 2,
		const char& groupChar = ':',
		const unsigned char& decDigits = 0,
		const char& decimalChar = charMinus,
		const int& borderWidth = 1,
		const bool& processCtrlChars = true,
		const bool& processDigits = true,
		const COLORREF& borderColor = 0,
		const bool& cycle = true,
		const char* const& toolTipText = nullptr,
		CToolTipCtrl* externalToolTip = nullptr):
		SpinType(maxValue,
			minValue,
			value,
			maxSpinRate,
			groupLength,
			groupChar,
			decDigits,//milliseconds ? 3 : 0,
			decimalChar,
			borderWidth,
			processCtrlChars,
			processDigits,
			false,//showPlus
			borderColor,
			cycle,
			toolTipText,
			externalToolTip),
		m_milliseconds(milliseconds)
	{
	}
	TimeSpinTemplate(const T& maxValue,
		const T& minValue = 0,
		const T& value = 0,
		const T& maxSpinRate = defaultMaxSpinRate,//DefaultMaxSpinRate<T>::defaultMaxSpinRate,//1000,//MaxSpin,
		const unsigned char& groupLength = 2,
		const char& groupChar = ':',
		const unsigned char& decDigits = 0,
		const char& decimalChar = charMinus,
		const int& borderWidth = 1,
		const bool& processCtrlChars = true,
		const bool& processDigits = true,
		const bool& showPlus = false,
		const COLORREF& borderColor = 0,
		const bool& cycle = true,
		const char* const& toolTipText = nullptr,
		CToolTipCtrl* const& externalToolTip = nullptr) :
		SpinType(maxValue,
			minValue,
			value,
			maxSpinRate,
			groupLength,
			groupChar,
			decDigits,
			decimalChar,
			borderWidth,
			processCtrlChars,
			processDigits,
			showPlus,
			borderColor,
			cycle,
			toolTipText,
			externalToolTip),
		m_milliseconds(false)
	{
	}
	static T GetStaticValueMillisecond(T millisecond, bool useMilliseconds)
	{
		T minutes = millisecond / 60000;
		millisecond -= minutes * 60000;
		T hours = minutes / 60;
		return useMilliseconds ?
			millisecond + minutes * 100000 + hours * 4000000:
			millisecond / 1000 + minutes * 100 + hours * 4000;
	}

	static T GetStaticTotalSecond(T value, bool useMilliseconds)
	{
		if(useMilliseconds)value /= 1000;
		T minutes = value / 100;
		value -= minutes * 100;
		T hours = minutes / 100;
		minutes -= hours * 100;
		return value + minutes * 60 + hours * 3600;
	}

	static T GetStaticTotalMillisecond(T value, bool useMilliseconds)
	{
		if(!useMilliseconds)value *= 1000;
		T minutes = value / 100000;
		value -= minutes * 100000;
		T hours = minutes / 100;
		minutes -= hours * 100;
		return value + minutes * 60000 + hours * 3600000;
	}

	static T GetStaticMillisecond(T value, bool useMilliseconds)
	{
		T minutes = value / (useMilliseconds ? 100000 : 100);
		T hours = minutes / 100;
		if(!useMilliseconds)
		{
			value *= 1000;
		}
		return value - minutes * 40000 - hours * 2400000;
	}

	static T GetStaticSecond(T value, bool useMilliseconds)
	{
		T minutes = value / (useMilliseconds ? 100000 : 100);
		T hours = minutes / 100;
		if(useMilliseconds)
		{
			value /= 1000;
		}
		return value - minutes * 40 - hours * 2400;
	}

	static T GetStaticValueSecond(T second, bool useMilliseconds)
	{
		T minutes = second / 60;
		second -= minutes * 60;
		T hours = minutes / 60;
		return useMilliseconds ?
			second * 1000 + minutes * 100000 + hours * 4000000:
			second + minutes * 100 + hours * 4000;
	}

	T GetMillisecond() const
	{
		return GetStaticMillisecond(GetValue(), m_milliseconds);
	}

	bool SetMillisecond(T millisecond, bool notifyParent = true)
	{
		return SetValue(GetStaticValueMillisecond(millisecond, m_milliseconds), false, true, notifyParent);
	}

	T GetSecond() const
	{
		return GetStaticSecond(GetValue(), m_milliseconds);
	}
	bool SetSecond(T second, bool notifyParent = true)
	{
		return SetValue(GetStaticValueSecond(second, m_milliseconds), false, true, notifyParent);
	}

	const bool& isMilliseconds() const{return m_milliseconds;}
	virtual bool SetMilliseconds(bool milliseconds, bool notifyParent = true)
	{
		if(m_milliseconds != milliseconds)
		{
			const T millisecond = GetMillisecond();
			m_milliseconds = milliseconds;

			if(m_milliseconds)
			{
				SetMaxValue(GetMaxValue() * 1000);
				SetMillisecond(millisecond);
			}
			else
			{
				SetMillisecond(millisecond);
				SetMaxValue(GetMaxValue() / 1000);
			}

			return true;
		}
		return false;
	}

	virtual bool AllVisible() const override{return true;}
protected:
//	virtual void DoUpdateValueStr(bool realValueModified = true);
	virtual void SpinCreated() override
	{
		unsigned char i = m_milliseconds ? 4 : 1;
		if(i < m_maxLength)m_maxDigitValues[i] = 5;
		i += 2;
		if(i < m_maxLength)m_maxDigitValues[i] = 5;

		SpinType::SpinCreated();
	}
	virtual unsigned char DoUpdateValueNum(bool adjustToMinMax) const override//0 - did not change, 1 - changed, 2 -  exceeded limits
	{
		::InvalidateRect(m_hWnd, &m_clientRect, FALSE);
		unsigned char ret = SpinType::DoUpdateValueNum(adjustToMinMax);
		return ret == 2 ? 2 : VerifyTokens() || ret ? 1 : 0;
	}
	virtual bool DoSpin(UINT nFlags, unsigned char button, bool increment) override//0 - left, 1 - right, 2 - middle
	{
		T prevValue = m_value;
		if(!SpinType::DoSpin(nFlags, button, increment))
		{
			return false;
		}
		bool maxMinutes;
		if(VerifyTokens(&maxMinutes))
		{
			if(increment)
			{
				if(maxMinutes)
				{
					m_value -= m_milliseconds ? 5900000 : 5900;
				}
				else
				{
					m_value -= m_milliseconds ? 59000 : 59;
				}
			}
			if(m_value < m_minValue)
			{
				m_value = m_minValue;
			}
			return true;
		}
		return prevValue != m_value;
	}
	bool VerifyTokens(bool* maxMinutes = nullptr) const
	{
		T seconds = m_milliseconds ? m_value / 1000 : m_value;
		T milliseconds = m_milliseconds ? m_value - seconds * 1000 : 0;
		T hours = seconds / 10000;
		seconds -= hours * 10000;
		T minutes = seconds / 100;
		seconds -= minutes * 100;
		bool ret = false;
		if(minutes > 59)
		{
			minutes = 59;
			if(maxMinutes)
			{
				*maxMinutes = true;
			}
			ret = true;
		}
		if(seconds > 59)
		{
			seconds = 59;
			if(maxMinutes)
			{
				*maxMinutes = false;
			}
			ret = true;
		}
		if(ret)
		{
			m_value = hours * 10000 + minutes * 100 + seconds;
			if(m_milliseconds)
			{
				m_value *= 1000;
				m_value += milliseconds;
			}
			return true;
		}
		return false;
	}

	bool m_milliseconds;
};

class TimeSpin : public TimeSpinTemplate<unsigned int, UnsignedNumberTypeSpin<unsigned int> >//UnsignedNumberTypeSpin<unsigned int>
{
public:
	TimeSpin(const bool& milliseconds,
		const unsigned int& maxValue,
		const unsigned int&	minValue = 0,
		const unsigned int& value = 0,
		const unsigned int& maxSpinRate = defaultMaxSpinRate,//DefaultMaxSpinRate<ValueType>::defaultMaxSpinRate,// = 1000,
		const int& borderWidth = 1,
		const bool& processCtrlChars = true,
		const bool& processDigits = true,
		const COLORREF& borderColor = 0,
		const bool& cycle = true,
		const char* const& toolTipText = nullptr,
		CToolTipCtrl* externalToolTip = nullptr) :
		TimeSpinTemplate(milliseconds,
			maxValue,
			minValue,
			value,
			maxSpinRate,
			2,
			':',
			milliseconds ? 3 : 0,
			charMinus,
			borderWidth,
			processCtrlChars,
			processDigits,
			borderColor,
			cycle,
			toolTipText,
			externalToolTip)
	{
	}
/*
	TimeSpin(const unsigned int& maxValue,
		const unsigned int& minValue = 0,
		const unsigned int& value = 0,
		const unsigned int& maxSpinRate = defaultMaxSpinRate,//DefaultMaxSpinRate<ValueType>::defaultMaxSpinRate,//1000,//MaxSpin,
		const unsigned char& groupLength = 2,
		const char& groupChar = ':',
		const unsigned char& decDigits = 0,
		const char& decimalChar = charMinus,
		const int& borderWidth = 1,
		const bool& processCtrlChars = true,
		const bool& processDigits = true,
		const bool& showPlus = false,
		const COLORREF& borderColor = 0,
		const bool& cycle = true,
		const char* const& toolTipText = nullptr,
		CToolTipCtrl* const& externalToolTip = nullptr) :
		TimeSpinTemplate(maxValue,
			minValue,
			value,
			maxSpinRate,
			groupLength,
			groupChar,
			decDigits,
			decimalChar,
			borderWidth,
			processCtrlChars,
			processDigits,
			showPlus,
			borderColor,
			cycle,
			toolTipText,
			externalToolTip)
	{
	}
*/
};

class SignedTimeSpin : public TimeSpinTemplate<int, SignedNumberTypeSpin<int> >//UnsignedNumberTypeSpin<unsigned int>
{
public:
	SignedTimeSpin(const bool& milliseconds,
		const int& maxValue,
		const int& minValue = 0,
		const int& value = 0,
		const int& maxSpinRate = defaultMaxSpinRate,//DefaultMaxSpinRate<ValueType>::defaultMaxSpinRate,// = 1000,
		const int& borderWidth = 1,
		const bool& processCtrlChars = true,
		const bool& processDigits = true,
		const COLORREF& borderColor = 0,
		const bool& cycle = true,
		const char* const& toolTipText = nullptr,
		CToolTipCtrl* externalToolTip = nullptr) :
		TimeSpinTemplate(milliseconds,
			maxValue,
			minValue,
			value,
			maxSpinRate,
			2,
			':',
			milliseconds ? 3 : 0,
			charMinus,
			borderWidth,
			processCtrlChars,
			processDigits,
			borderColor,
			cycle,
			toolTipText,
			externalToolTip)
	{
	}
	SignedTimeSpin(const int& maxValue,
		const int& minValue = 0,
		const int& value = 0,
		const int& maxSpinRate = defaultMaxSpinRate,//DefaultMaxSpinRate<ValueType>::defaultMaxSpinRate,//1000,//MaxSpin,
		const char& groupLength = 2,
		const char& groupChar = ':',
		const unsigned char& decDigits = 0,
		const char& decimalChar = charMinus,
		const int& borderWidth = 1,
		const bool& processCtrlChars = true,
		const bool& processDigits = true,
		const bool& showPlus = false,
		const COLORREF& borderColor = 0,
		const bool& cycle = true,
		const char* const& toolTipText = nullptr,
		CToolTipCtrl* const& externalToolTip = nullptr) :
		TimeSpinTemplate(false,
			maxValue,
			minValue,
			value,
			maxSpinRate,
			groupLength,
			groupChar,
			decDigits,
			decimalChar,
			borderWidth,
			processCtrlChars,
			processDigits,
//			showPlus,
			borderColor,
			cycle,
			toolTipText,
			externalToolTip)
	{
	}
};

#else

class UGUI_API TimeSpin : public UnsignedNumberTypeSpin<unsigned int>
{
public:
	TimeSpin(const bool& milliseconds,
		const unsigned int& maxValue,
		const unsigned int&	minValue = 0,
		const unsigned int& value = 0,
		const unsigned int& maxSpinRate = defaultMaxSpinRate,//DefaultMaxSpinRate<ValueType>::defaultMaxSpinRate,// = 1000,
		const int& borderWidth = 1,
		const bool& processCtrlChars = true,
		const bool& processDigits = true,
		const COLORREF& borderColor = 0,
		const bool& cycle = true,
		const char* const& toolTipText = nullptr,
		CToolTipCtrl* externalToolTip = nullptr):
		UnsignedNumberTypeSpin(maxValue,
			minValue,
			value,
			maxSpinRate,
			2,
			':',
			milliseconds ? 3 : 0,
			charMinus,
			borderWidth,
			processCtrlChars,
			processDigits,
			false,//showPlus
			borderColor,
			cycle,
			toolTipText,
			externalToolTip),
		m_milliseconds(milliseconds)
	{
	}
	static unsigned int GetStaticValueMillisecond(unsigned int millisecond, bool useMilliseconds)
	{
		unsigned int minutes = millisecond / 60000;
		millisecond -= minutes * 60000;
		unsigned int hours = minutes / 60;
		return useMilliseconds ?
			millisecond + minutes * 100000 + hours * 4000000:
			millisecond / 1000 + minutes * 100 + hours * 4000;
	}

	static unsigned int GetStaticTotalSecond(unsigned int value, bool useMilliseconds)
	{
		if(useMilliseconds)value /= 1000;
		unsigned int minutes = value / 100;
		value -= minutes * 100;
		unsigned int hours = minutes / 100;
		minutes -= hours * 100;
		return value + minutes * 60 + hours * 3600;
	}

	static unsigned int GetStaticTotalMillisecond(unsigned int value, bool useMilliseconds)
	{
		if(!useMilliseconds)value *= 1000;
		unsigned int minutes = value / 100000;
		value -= minutes * 100000;
		unsigned int hours = minutes / 100;
		minutes -= hours * 100;
		return value + minutes * 60000 + hours * 3600000;
	}

	static unsigned int GetStaticMillisecond(unsigned int value, bool useMilliseconds)
	{
		unsigned int minutes = value / (useMilliseconds ? 100000 : 100);
		unsigned int hours = minutes / 100;
		if(!useMilliseconds)
		{
			value *= 1000;
		}
		return value - minutes * 40000 - hours * 2400000;
	}

	static unsigned int GetStaticSecond(unsigned int value, bool useMilliseconds)
	{
		unsigned int minutes = value / (useMilliseconds ? 100000 : 100);
		unsigned int hours = minutes / 100;
		if(useMilliseconds)
		{
			value /= 1000;
		}
		return value - minutes * 40 - hours * 2400;
	}

	static unsigned int GetStaticValueSecond(unsigned int second, bool useMilliseconds)
	{
		unsigned int minutes = second / 60;
		second -= minutes * 60;
		unsigned int hours = minutes / 60;
		return useMilliseconds ?
			second * 1000 + minutes * 100000 + hours * 4000000:
			second + minutes * 100 + hours * 4000;
	}

	unsigned int GetMillisecond() const;
	bool SetMillisecond(unsigned int millisecond, bool notifyParent = true);

	unsigned int GetSecond() const;
	bool SetSecond(unsigned int second, bool notifyParent = true);

	const bool& isMilliseconds() const{return m_milliseconds;}
	virtual bool SetMilliseconds(bool milliseconds, bool notifyParent = true);

	virtual bool AllVisible() const{return true;}
protected:
//	virtual void DoUpdateValueStr(bool realValueModified = true);
	virtual void SpinCreated() override;
	virtual unsigned char DoUpdateValueNum(bool adjustToMinMax) const override;//0 - did not change, 1 - changed, 2 -  exceeded limits
//	virtual bool DoSpin(UINT nFlags, bool rightButton, bool increment) override;
	virtual bool DoSpin(UINT nFlags, unsigned char button, bool increment) override;//0 - left, 1 - right, 2 - middle
	bool VerifyTokens(bool* maxMinutes = nullptr) const;
	bool m_milliseconds;
};

#endif

class UGUI_API TifSpin : public TimeSpin
{
public:
	static const char* const dayTifStr;
	static const char* const iocTifStr;
	static const char* const extendedTifStr;
//	static const unsigned int dayValueMilliseconds = 80000000;
	static const unsigned int dayValueSeconds = 80000;
	static const unsigned int extendedValueSeconds = 90000;
	static const unsigned int fullDaySeconds = 235959;
	static const unsigned int fullDayMilliseconds = 235959999;

	TifSpin(const bool& milliseconds,
		const bool& prefix,
		const unsigned char& type = 0,//0 = dayValueSeconds, 1 = extendedValueSeconds, 2 - full day
		const unsigned int& value = 0,
		const int& borderWidth = 1,
		const bool& processCtrlChars = true,
		const bool& processDigits = true,
		const char* const& toolTipText = nullptr,
		CToolTipCtrl* externalToolTip = nullptr):
		TimeSpin(milliseconds,
			type == 2 ?
				milliseconds ? fullDayMilliseconds : fullDaySeconds:
			type == 1 ?
				milliseconds ? extendedValueSeconds * 1000 : extendedValueSeconds:
				milliseconds ? dayValueSeconds * 1000 : dayValueSeconds,
			0,
			value,
			1000,
			borderWidth,
			processCtrlChars,
			processDigits,
			0,
			true,
			toolTipText,
			externalToolTip),
		m_tifPrefix(prefix),
		m_type(type),
		m_dayValue(milliseconds ? dayValueSeconds * 1000 : dayValueSeconds),
		m_extendedValue(milliseconds ? extendedValueSeconds * 1000 : extendedValueSeconds),
		m_prefixHeight(0),
		m_tifPrefixWidth(0),
		m_prefixOffset(1),
		m_tifPrefixRect(0, 0, 0, 0),
		m_prefixTextRect(0, 0, 0, 0)
	{
		if(m_milliseconds)
		{
			AddSpinCell(1, false, 1000);
			AddSpinCell(1000, false, 100000);
			AddSpinCell(10000000, true, type == 2 ? 0 : 100000000);
			AddSpinCell(100000, true, 10000000);
		}
		else
		{
//			AddSpinCell(1, false, 1000);
			AddSpinCell(1, false, 100);
			AddSpinCell(10000, true, type == 2 ? 0 : 100000);
			AddSpinCell(100, true, 10000);
		}
	}
	virtual int GetEditLeftOffset() const{return m_tifPrefixRect.right;}
//	virtual int GetEditRightOffset() const{return 0;}
	unsigned int GetDayValue() const{return m_dayValue;}
	unsigned int GetExtendedValue() const{return m_extendedValue;}
	virtual bool SetMilliseconds(bool milliseconds, bool notifyParent = true) override;
//	virtual bool AllVisible() const{return true;}
protected:
	virtual bool UpdateTextRectsHeight() override;
	virtual void DoSize(UINT nType, int cx, int cy, int oldX, int oldY) override;
	virtual void OnFontChange(CDC* dc) override;
//	virtual void DoPaintClient(const RECT& interRect, CDC& dc);
	virtual void DoAdditionalPaint(const RECT& interRect, CDC& dc) override;
	bool m_tifPrefix;
	unsigned char m_type;
	unsigned int m_dayValue;
	unsigned int m_extendedValue;
	int m_prefixHeight;
	int m_tifPrefixWidth;
	int m_prefixOffset;
	CRect m_tifPrefixRect;
	CRect m_prefixTextRect;
//	virtual void SpinCreated();
};


///////////
class CharCellIp : public CharCellBase
{
friend class TakionIpField;
public:
	CharCellIp():
		m_rect(0, 0, 0, 0)
	{}
	const CRect& GetRect() const{return m_rect;}
	void Nullify()
	{
		m_visible = true;
		m_ord = 0;
		m_char = '\0';
		m_rect.left = m_rect.top = m_rect.right = m_rect.bottom = 0;
	}
	bool IncrementValue(unsigned char val)
	{
		if(!m_char)
		{
			m_char = '0';
			return true;
		}
		else if(m_char < '9' && m_char >= '0')
		{
			if(!val)val = 1;
			else if (val > 9)val = 9;
			m_char += val;
			if(m_char > '9')m_char = '9';
			return true;
		}
		return false;
	}
	bool DecrementValue(unsigned char val)
	{
/*
		if(!m_char)
		{
			m_char = '9';
			return true;
		}
		else
*/
		if(m_char <= '9' && m_char > '0')
		{
			if(!val)val = 1;
			else if(val > 9)val = 9;
			m_char -= val;
			if(m_char < '0')m_char = '0';
			return true;
		}
		return false;
	}
protected:
	CRect m_rect;
};

class UGUI_API TakionIpField
{
friend class TakionIpControl;
public:
	TakionIpField():
		m_parent(nullptr),
		m_charCell(nullptr),
		m_rect(0, 0, 0, 0),
		m_count(0),
		m_caretLocation(0)
	{
	}
	TakionIpField(const TakionIpField& other):
		m_parent(other.m_parent),
		m_charCell(nullptr),
		m_rect(other.m_rect),
		m_count(0),
		m_caretLocation(other.m_caretLocation)
	{
		CopyCells(other);
	}
	virtual ~TakionIpField(){Cleanup();}
	TakionIpField& operator=(const TakionIpField& other)
	{
		m_parent = other.m_parent;
		m_rect = other.m_rect;
		m_caretLocation = other.m_caretLocation;
		CopyCells(other);
		return *this;
	}
	const CRect& GetRect() const{return m_rect;}
	CRect& GetRect(){return m_rect;}
	const unsigned char& GetCaretLocation() const{return m_caretLocation;}
	const CharCellIp* GetCellAt(const unsigned char& at) const{return m_charCell && at < m_count ? m_charCell + at : nullptr;}
	CharCellIp* GetCellAt(const unsigned char& at){return m_charCell && at < m_count ? m_charCell + at : nullptr;}
	const CharCellIp* GetCellWithCaret() const{return GetCellAt(m_caretLocation);}
	CharCellIp* GetCellWithCaret(){return GetCellAt(m_caretLocation);}
	bool TypeDigit(unsigned char digit);
	bool IncrementValue(unsigned char val)
	{
		return IncrementValueAt(m_caretLocation, val);
	}
	bool DecrementValue(unsigned char val)
	{
		return DecrementValueAt(m_caretLocation, val);
	}
	bool IncrementValueAt(unsigned char at, unsigned char val);
	bool DecrementValueAt(unsigned char at, unsigned char val);
	bool DeleteCharNext();
	bool DeleteChar();
	void InvalidateRect(const RECT& rect) const;
	bool DeleteSelection(const CRect& selectionRect);
	void Normalize();
	virtual unsigned int GetMaxValue() const{return 0xFF;}
	virtual unsigned char GetLeftmostMaxDigit() const{return 2;}
	virtual unsigned int GetChangeMessageId() const{return WM_USER + 278;}
	bool isFilled() const
	{
		if(m_charCell && m_count)
		{
			switch(m_charCell[m_count - 1].GetChar())
			{
				case '\0':
				return false;

				case '0':
				if(m_count > 1)
				{
					return false;
				}
				break;
			}
		}
		return true;
//		return !m_charCell || !m_count || m_charCell[m_count - 1].GetChar();
	}
	bool isEmpty() const
	{
		return !m_charCell || !m_count || !m_charCell->GetChar();
	}
	bool DecrementCaretLocation()
	{
		if(m_caretLocation)
		{
			--m_caretLocation;
			return true;
		}
		return false;
	}
	bool IncrementCaretLocation()
	{
		if(m_caretLocation < m_count)
		{
			++m_caretLocation;
			return true;
		}
		return false;
	}
	bool SetCaretLocation(unsigned char location)
	{
		if(location > m_count)location = m_count;
		if(location != m_caretLocation)
		{
			m_caretLocation = location;
			return true;
		}
		return false;
	}
	bool SetCaretLocationToLast()
	{
		if(m_count != m_caretLocation)
		{
			m_caretLocation = m_count;
			return true;
		}
		return false;
	}
	unsigned char CalculateLocationByX(int x) const;

	unsigned char CalculateCaretLocationByX(int x) const;

	void SetCaretLocationByX(int x)
	{
		m_caretLocation = CalculateCaretLocationByX(x);
	}
	const unsigned char& GetCount() const{return m_count;}
	void NullifyAll()
	{
		if(m_count)
		{
			CharCellIp* cursor = m_charCell;
			for(unsigned char i = 0; i < m_count; ++i, ++cursor)
			{
				cursor->Nullify();
			}
		}
	}
	void SetRects(int right, const int& width, const int& top, const int& bottom)
	{
		CharCellIp* cursor = m_charCell;
		for(unsigned char i = 0; i < m_count; ++i, ++cursor)
		{
			CRect& rect = cursor->m_rect;

			rect.right = right;
			right -= width;
			rect.left = right;

			rect.top = top;
			rect.bottom = bottom;
		}
	}
	bool GetSelectionRect(CRect& rect) const
	{
		if(m_charCell && m_count)
		{
			rect = m_rect;
			CharCellIp* cursor = m_charCell + (m_count - 1);
			for(unsigned char i = 0; i < m_count; ++i, --cursor)
			{
				if(cursor->GetChar())
				{
					rect.left = cursor->GetRect().left;
					return true;
				}
			}
			rect.left = rect.top = rect.right = rect.bottom = 0;
			return true;
		}
		return false;
	}
	void SetRectsTopBottom(const int& top, const int& bottom)
	{
		CharCellIp* cursor = m_charCell;
		for(unsigned char i = 0; i < m_count; ++i, ++cursor)
		{
			CRect& rect = cursor->m_rect;
			rect.top = top;
			rect.bottom = bottom;
		}
	}
	void Draw(const RECT& interRect, CDC& dc, const CRect& selectionRect, const COLORREF& textColor, const COLORREF& selectionTextColor) const;
	unsigned int GetValue() const;
	void SetValue(unsigned int value);
	unsigned int GetSelectedNumber(const CRect& selectionRect) const;
	unsigned int GetSelectedNumber(unsigned char locationLeft, unsigned char locationRight) const;
	void Clear();
	CharCellIp* GetZeroCell()
	{
		if(m_charCell)
		{
			CharCellIp* cursor = m_charCell;
			for(unsigned char i = 0; i < m_count; ++i, ++cursor)
			{
				if(!cursor->GetChar())
				{
					return cursor;
				}
			}
		}
		return nullptr;
	}
	const CharCellIp* GetZeroCell() const
	{
		if(m_charCell)
		{
			const CharCellIp* cursor = m_charCell;
			for(unsigned char i = 0; i < m_count; ++i, ++cursor)
			{
				if(!cursor->GetChar())
				{
					return cursor;
				}
			}
		}
		return nullptr;
	}
	int GetXOfLocation(const unsigned char& location) const
	{
		return !location ? m_rect.right:
			location >= m_count ? m_rect.left:
			m_rect.right - GetDigitWidth() * location;
	}
	int GetXOfCaretLocation() const
	{
		return GetXOfLocation(m_caretLocation);
	}
	int GetDigitWidth() const;
protected:
	void Initialize(TakionIpControl* parent, unsigned char count);
	void CopyCells(const TakionIpField& other)
	{
		Initialize(other.m_parent, other.m_count);
		if(m_charCell)
		{
			CharCellIp* cursor = m_charCell;
			const CharCellIp* cursorOther = other.m_charCell;
			for(unsigned char i = 0; i < m_count; ++i, ++cursor, ++cursorOther)
			{
				*cursor = *cursorOther;
			}
		}
	}
	void Cleanup();
	TakionIpControl* m_parent;
	CharCellIp* m_charCell;
	CRect m_rect;
	unsigned char m_count;
	unsigned char m_caretLocation;
};

class UGUI_API TakionIpControl : public TakionTextCustomControl
{
public:
	static const unsigned char IP_FIELD_COUNT = 4;
	static const unsigned char IP_FIELD_CHAR_COUNT = 3;

	TakionIpControl(CWnd* parent,
		const int& maxGap = 3,
		const int& borderWidth = 1,
		const COLORREF& borderColor = 0,

		const char* const& toolTipText = nullptr,
		CToolTipCtrl* const& externalToolTip = nullptr,
		const bool& useCopyAccelerator = true):

		TakionTextCustomControl(borderWidth, borderColor, true, toolTipText, externalToolTip),
		m_parent(parent),
		m_maxDigitWidth(0),
		m_digitWidth(0),
		m_groupWidth(0),
		m_maxGap(maxGap),
		m_gap(maxGap),
		m_ipRectWidth(0),
		m_ipRect(0, 0, 0, 0),
		m_caretLocation(0),
		m_lButtonDownMillisecond(0),
		m_doubleClickMillisecond(GetDoubleClickTime()),
		m_lButtonDownPoint(0, 0),
		m_doubleClickPoint(GetSystemMetrics(SM_CXDOUBLECLK), GetSystemMetrics(SM_CYDOUBLECLK)),
		m_mousePointX(-1),
		m_beamCursor(LoadCursor(nullptr, IDC_IBEAM)),
		m_arrowCursor(LoadCursor(nullptr, IDC_ARROW)),
		m_lButtonDown(false),
		m_mButtonDown(false),
		m_rButtonDown(false),
		m_focusSetFirstTime(true),
		m_useCopyAccelerator(useCopyAccelerator),
		m_rightButtonDownPoint(0, 0)
	{
		RegisterWindowClass();
		memset(&m_digitWidths, 0, sizeof(m_digitWidths));

		TakionIpField* cursor = m_ipField;
		for(unsigned char i = 0; i < sizeof(m_ipField) / sizeof(TakionIpField); ++i, ++cursor)
		{
			cursor->Initialize(this, 3);
		}
	}

//	virtual ~TakionIpControl();
	static const char* const takionIpClassName;
	virtual const char* GetCustomClassName() const override{return takionIpClassName;}

	int GetDigitWidth(const unsigned char& digit) const{return digit < 10 ? m_digitWidths[digit] : 0;}
	const int& GetMaxDigitWidth() const{return m_maxDigitWidth;}
	const int& GetDigitWidth() const{return m_digitWidth;}
	const unsigned char& GetCaretLocation() const{return m_caretLocation;}
	virtual const TakionIpField* GetFieldAt(const unsigned char& at) const{return at < sizeof(m_ipField) / sizeof(TakionIpField) ? m_ipField + at : nullptr;}
	virtual TakionIpField* GetFieldAt(const unsigned char& at){return at < sizeof(m_ipField) / sizeof(TakionIpField) ? m_ipField + at : nullptr;}
	const TakionIpField* GetFieldWithCaret() const{return GetFieldAt(m_caretLocation);}
	TakionIpField* GetFieldWithCaret(){return GetFieldAt(m_caretLocation);}

	void Clear();

	unsigned char GetAddress(DWORD& dwAddress) const;
	bool SetAddress(DWORD dwAddress);

	unsigned char GetNetwork(DWORD& dwNetwork) const;
	bool SetNetwork(DWORD dwNetwork);

	void PostChangeMessage(const unsigned int messageId)
	{
//		if(m_parent->m_hWnd)::SendMessage(m_parent->m_hWnd, WM_USER + 278, GetCtrlId(), 0);
		if(m_parent->m_hWnd)::SendMessage(m_parent->m_hWnd, messageId, GetCtrlId(), 0);
	}
	virtual bool HasDisabledColor() const override{return false;}
	void NormalizeCurrentField()
	{
		TakionIpField* field = GetFieldWithCaret();
		if(field)
		{
			field->Normalize();
		}
	}
	virtual unsigned char GetMaxCaretLocation() const{return sizeof(m_ipField) / sizeof(TakionIpField) - 1;}
	void SetCaretLocation(unsigned char location)
	{
		const unsigned char maxLocation = GetMaxCaretLocation();
		if(location > maxLocation)
		{
			location = maxLocation;
		}
		if(location != m_caretLocation)
		{
			NormalizeCurrentField();
			m_caretLocation = location;
		}
	}
	TakionIpField* FindFieldAtPoint(int x);
	const TakionIpField* FindFieldAtPoint(int x) const;
	virtual unsigned char FindCaretLocationAtPoint(int x) const;
	void Unselect();
//	virtual void SelectAllAtCaret();
	virtual void SelectAllAtCaret();
	void SetSelectionRect(const CRect& rect);
	virtual void Unhighlight();
	virtual void HighlightUnderMouse();
	virtual bool HasMenu() const override{return true;}
	virtual bool isContentValid() const override
	{
		DWORD ipAddress = 0;
		return GetAddress(ipAddress) == 4;
	}
	virtual bool isPasteAvailable() const override{return IsClipboardFormatAvailable(CF_TEXT) == TRUE;}
	virtual bool isContentEmpty() const
	{
		DWORD ipAddress = 0;
		GetAddress(ipAddress);
		return !ipAddress;
	}
	bool CopySelectionToClipboard() const
	{
		return m_selectionRect.left < m_selectionRect.right && DoCopySelectionToClipboard();
	}
	virtual void CopyValueToClipboard() const{CopyIpToClipboard();}
	virtual void CopyIpToClipboard() const
	{
		DWORD ipAddress;
		GetAddress(ipAddress);
		std::string ipStr;
		U_ConvertIpToStdString(ipAddress, ipStr);
		U_CopyStringToClipboard(ipStr, m_hWnd);//, unsigned char* errorCode);
	}
	virtual bool PasteSelectionFromClipboard()//??
	{
		return false;
	}
	virtual void PasteValueFromClipboard(){PasteIpFromClipboard();}

	virtual void PasteString(const char* str)
	{
		const unsigned int ip = U_ConvertStringToIp(str);
		if(ip)SetAddress(ip);
	}
	void PasteIpFromClipboard()
	{
		std::string ipStr;
		if(U_CopyClipboardToString(ipStr, m_hWnd) == CLIPBOARD_OK)
		{
			PasteString(ipStr.c_str());
		}
	}
	virtual void ClearContent()
	{
		SetAddress(0);
	}

protected:
	virtual void PreSubclassWindow() override;

	virtual void DoSize(UINT nType, int cx, int cy, int oldX, int oldY) override;

	virtual bool ProcessKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) override;
//	virtual bool ProcessKeyUp(UINT nChar, UINT nFlags) override;

	virtual bool ProcessDigit(unsigned char digit, bool repeat, bool force = false);
	virtual bool ProcessCtrlChar(unsigned char ctrlChar, bool repeat, bool force = false);

	virtual void DoUpdateCaretPosition() override;
	virtual void BeforeDestroy() override;
	virtual void DoPaintClient(const RECT& interRect, CDC& dc) override;

	void SetCaretPositionToTheRight();

	virtual void AdditionalOnFontChangeCalculations(CDC* dc){}
	virtual void OnFontChange(CDC* dc) override;
	virtual bool UpdateTextRectsHeight() override;

	virtual void FocusGained() override;
	virtual void FocusLost() override;
	virtual bool SetClientCursor() override
	{
		if(m_inEdit)
		{
			SetCursor(GetInEditCursor());
			return true;
		}
		return false;
	}
	virtual bool DoCopySelectionToClipboard() const;

	virtual void UpdateSelectionOnMouseMove(int x);

	virtual void SetCaretLocationOnButtonDown(int x);
	virtual void SetCaretLocationOnButtonUp(int x);

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	virtual BOOL PreTranslateMessage(MSG* pMsg) override;

	virtual void Wheel(short steps, UINT nFlags, CPoint pt) override;
	virtual void MouseLeft() override;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	DECLARE_MESSAGE_MAP()

	BOOL RegisterWindowClass();
	void CalculateDigitWidth(CDC* dc);

	void OnButtonDown(bool& buttonDown, UINT nFlags, const CPoint& point, unsigned char button);//0 - left, 1 - right, 2 - middle
	void OnButtonUp(bool& buttonDown, const CPoint& point);

	CWnd* m_parent;

	int m_digitWidths[10];
	int m_maxDigitWidth;
	int m_digitWidth;
	int m_groupWidth;
	int m_maxGap;
	int m_gap;
	int m_ipRectWidth;

	void InitializeField(TakionIpField& field, const unsigned char& count)
	{
		field.Initialize(this, count);
	}

	TakionIpField m_ipField[IP_FIELD_COUNT];
	CRect m_rectDelimiter[IP_FIELD_COUNT - 1];

	CRect m_ipRect;
	void NullifyAllDelimiterRects()
	{
		CRect* cursor = m_rectDelimiter;
		for(unsigned char i = 0; i < sizeof(m_rectDelimiter) / sizeof(CRect); ++i, ++cursor)
		{
			cursor->left = cursor->top = cursor->right = cursor->bottom = 0;
		}
	}
	unsigned char m_caretLocation;

	unsigned int m_lButtonDownMillisecond;
	unsigned int m_doubleClickMillisecond;
	CPoint m_lButtonDownPoint;
	CPoint m_doubleClickPoint;
	int m_mousePointX;
	HCURSOR m_beamCursor;
	HCURSOR m_arrowCursor;
	bool m_lButtonDown;
	bool m_mButtonDown;
	bool m_rButtonDown;
	bool m_focusSetFirstTime;

	bool m_useCopyAccelerator;
	CPoint m_rightButtonDownPoint;

	void DoUnselect();
};

class UGUI_API TakionPortField : public TakionIpField
{
friend class TakionIpPortControl;
public:
	TakionPortField():TakionIpField()
	{
	}
	virtual unsigned int GetMaxValue() const override{return 0xFFFF;}
	virtual unsigned char GetLeftmostMaxDigit() const override{return 6;}
	virtual unsigned int GetChangeMessageId() const override{return WM_USER + 279;}
};

class UGUI_API TakionIpPortControl : public TakionIpControl
{
public:
	static const unsigned char PORT_CHAR_COUNT = 5;

	TakionIpPortControl(CWnd* parent,
		const int& maxGap = 3,
		const int& borderWidth = 1,
		const COLORREF& borderColor = 0,

		const char* const& toolTipText = nullptr,
		CToolTipCtrl* const& externalToolTip = nullptr):

		TakionIpControl(parent, maxGap, borderWidth, borderColor, toolTipText, externalToolTip),
		m_dividerWidth(borderWidth),
		m_rectDivider(0, 0, 0, 0),
		m_portRect(0, 0, 0, 0),
		m_clientIpRect(0, 0, 0, 0),
		m_clientPortRect(0, 0, 0, 0),
		m_bkPortColor(GetSysColor(COLOR_WINDOW))
	{
		InitializeField(m_portField, 5);
	}
	unsigned short GetPort() const
	{
		const unsigned int port = m_portField.GetValue();
		return port == 0xFFFFFFFF ? 0 : (unsigned short)port;
	}
	void SetPort(const unsigned short& port)
	{
		const unsigned short oldPort = GetPort();
		if(oldPort != port)
		{
			m_portField.SetValue(port);
			PostChangeMessage(m_portField.GetChangeMessageId());
		}
	}
	virtual unsigned char FindCaretLocationAtPoint(int x) const override;

	virtual const TakionIpField* GetFieldAt(const unsigned char& at) const override
	{
		return at == sizeof(m_ipField) / sizeof(TakionIpField) ? &m_portField : TakionIpControl::GetFieldAt(at);
	}
	virtual TakionIpField* GetFieldAt(const unsigned char& at) override
	{
		return at == sizeof(m_ipField) / sizeof(TakionIpField) ? &m_portField : TakionIpControl::GetFieldAt(at);
	}
	virtual unsigned char GetMaxCaretLocation() const override{return sizeof(m_ipField) / sizeof(TakionIpField);}
	virtual void CopyValueToClipboard() const override
	{
		if(m_caretLocation >= sizeof(m_ipField) / sizeof(TakionIpField))
		{
			CopyPortToClipboard();
		}
		else
		{
			TakionIpControl::CopyValueToClipboard();
		}
	}
	bool isCaretLocationInPort() const{return m_caretLocation == sizeof(m_ipField) / sizeof(TakionIpField);}
	void CopyPortToClipboard() const
	{
		const unsigned int port = m_portField.GetValue();
		if(port == 0xFFFFFFFF)
		{
			U_CopyStringToClipboard("", m_hWnd);
		}
		else
		{
			char num[33];
			U_CopyStringToClipboard(U_UnsignedNumberToStrNoDecDigits(port, num, sizeof(num)), m_hWnd);
		}
	}
	virtual void PasteValueFromClipboard() override
	{
		if(m_caretLocation >= sizeof(m_ipField) / sizeof(TakionIpField))
		{
			PastePortFromClipboard();
		}
		else
		{
			TakionIpControl::PasteValueFromClipboard();
		}
	}
	void PastePortFromClipboard()
	{
		std::string portStr;
		if(U_CopyClipboardToString(portStr, m_hWnd) == CLIPBOARD_OK)
		{
			const unsigned int port = U_GetUnsignedNumberFromString<unsigned int>(portStr.c_str(), '\0', 0xFFFFFFFF);
			if(port <= 0xFFFF)
			{
				SetPort((unsigned short)port);
			}
		}
	}
	virtual void ClearContent() override;
	virtual bool isContentEmpty() const
	{
		return isCaretLocationInPort() ? m_portField.isEmpty() : TakionIpControl::isContentEmpty();
	}

	const COLORREF& GetBkPortColor() const{return m_bkPortColor;}
	bool SetBkPortColor(COLORREF color)
	{
		if(0xFFFFFFFF == color)color = GetSysColor(COLOR_WINDOW);
		if(color != m_bkPortColor)
		{
			m_bkPortColor = color;
			InvalidateRectIfValid(&m_clientPortRect);
			return true;
		}
		return false;
	}
protected:
	virtual void DoSize(UINT nType, int cx, int cy, int oldX, int oldY) override;
	virtual bool UpdateTextRectsHeight() override;
	virtual void DoPaintClient(const RECT& interRect, CDC& dc) override;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;

	virtual bool ProcessCtrlChar(unsigned char ctrlChar, bool repeat, bool force = false) override;
	virtual void FocusGained() override;

	virtual BOOL PreTranslateMessage(MSG* pMsg) override;

	void PaintPort(const RECT& interRect, CDC& dc);
	virtual void PaintBackground(const RECT& rcPaint, CDC& dc) override
	{
/*
		if(m_enabled)
		{
			CRect interRect;
			if(interRect.IntersectRect(&rcPaint, &m_clientIpRect))
			{
				dc.FillSolidRect(&interRect, m_bkColor);
			}
			if(interRect.IntersectRect(&rcPaint, &m_clientPortRect))
			{
				dc.FillSolidRect(&interRect, m_bkPortColor);
			}
		}
		else
*/
		TakionIpControl::PaintBackground(rcPaint, dc);
	}

	TakionPortField m_portField;

	int m_dividerWidth;
	CRect m_rectDivider;
	CRect m_portRect;

	CRect m_clientIpRect;
	CRect m_clientPortRect;

	COLORREF m_bkPortColor;
};

class PointLocatorCharOrderedMap;

class UGUI_API TakionDnsIpPortControl : public TakionIpPortControl
{
public:
	TakionDnsIpPortControl(CWnd* parent,
		const int& maxGap = 3,
		const int& borderWidth = 1,
		const COLORREF& borderColor = 0,
		const char* const& toolTipDnsText = nullptr,
		const char* const& toolTipIpText = nullptr,
		CToolTipCtrl* const& externalToolTip = nullptr);
	virtual ~TakionDnsIpPortControl();
	const bool& isDnsMode() const{return m_dnsMode;}
	void SetDnsMode(bool dnsMode);
	virtual void Unhighlight() override;
	virtual void HighlightUnderMouse() override;
	virtual void SelectAllAtCaret() override;

//	const std::string& GetDnsString() const{return m_dnsString;}
//	void UpdateCharPosSet();
	void AppendDnsString(std::string& str) const;
	void SetDnsString(const char* dnsString);
	void InsertString(const char* str);
	bool isDnsEmpty() const{return !m_dnsStringWidth;}
	int GetDnsStringWidth() const{return m_dnsStringWidth;}

	const unsigned int& GetCaretPositionInDnsString() const{return m_caretPositionInDnsString;}
	unsigned int GetValidCaretPosition() const;
	const int& GetMaxCharWidth() const{return m_maxCharWidth;}
	int GetCharacterWidth(const char& c) const
	{
		return c >= ' ' && c < sizeof(m_charWidths) / sizeof(int) ? m_charWidths[c] : m_maxCharWidth;
	}
	virtual bool WantChars() const override;
	bool DeleteSelection();
	virtual void CopyIpToClipboard() const override
	{
		if(m_dnsMode)
		{
			std::string dnsString;
			AppendDnsString(dnsString);
			U_CopyStringToClipboard(dnsString, m_hWnd);//, unsigned char* errorCode);
		}
		else
		{
			TakionIpPortControl::CopyIpToClipboard();
		}
	}
	virtual void PasteString(const char* str) override
	{
		if(m_dnsMode)
		{
			InsertString(str);
//			SetDnsString(str);
		}
		else
		{
			TakionIpPortControl::PasteString(str);
		}
	}
	virtual void ClearContent() override;
	void ClearDnsString();
	void DoClearDnsString();//without repainting

	virtual bool isContentEmpty() const
	{
		return isCaretLocationInPort() ? m_portField.isEmpty() : m_dnsMode ? isDnsEmpty() : TakionIpPortControl::isContentEmpty();
	}
	void SetShowTooltipsAlways(const bool& always)
	{
		if(always != m_showTooltipsAlways)
		{
			m_showTooltipsAlways = always;
			UpdateToolTipToContentsIfDoesNotFit();
		}
	}
	void UpdateToolTipToContentsIfDoesNotFit();
	virtual bool isToDestroyToolTipIfNoText() const override{return false;}
protected:
	virtual void PreSubclassWindow() override;
	virtual void AddMenuItems(CMenu& menu) override;
	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) override;
	virtual void DoSize(UINT nType, int cx, int cy, int oldX, int oldY) override;
	virtual void DoPaintClient(const RECT& interRect, CDC& dc) override;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	virtual bool ProcessKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) override;
	virtual void Wheel(short steps, UINT nFlags, CPoint pt) override;
	virtual void DoUpdateCaretPosition() override;
	virtual void UpdateSelectionOnMouseMove(int x) override;
	virtual void SetCaretLocationOnButtonDown(int x) override;
	virtual void SetCaretLocationOnButtonUp(int x) override{}
	virtual void OnFontChange(CDC* dc) override;
	virtual void AdditionalOnFontChangeCalculations(CDC* dc) override{CalculateCharWidth(dc);}
	virtual void FocusGained() override;

	virtual bool DoCopySelectionToClipboard() const override;

//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg UINT OnGetDlgCode();
	DECLARE_MESSAGE_MAP()

//	PointLocatorOrderedSet* m_charPosSet;
	PointLocatorCharOrderedMap* m_charPosMap;

	void OnDnsChange();

	void UpdateDnsMode();
	bool m_dnsMode;
	int m_ipMenuWidth;
	int m_dnsMenuWidth;
	const char* m_dnsModeTooltip;
	const char* m_ipModeTooltip;

	bool TypeChar(UINT nChar);
//	std::string m_dnsString;
	unsigned int m_caretPositionInDnsString;
	int m_dnsStringWidth;
	void SetCaretX(int x);
	int AdjustCaretPosX(int toX);//m_ipRect.left or m_ipRect.right
	int AdjustCaretPosXatRight(){return m_caretPosX >= m_ipRect.right ? AdjustCaretPosX(m_ipRect.right) : 0;}//if it goes beyond the right boundary, scroll the string
	int AdjustCaretPosXatLeft(){return m_caretPosX < m_ipRect.left - 1 ? AdjustCaretPosX(m_ipRect.left) : 0;}//if it goes beyond the left boundary, scroll the string
	int m_caretPosX;
	int m_buttonDownCaretPosX;
//	int m_scrollAmount;//??
	int m_scrollOffset;

	bool m_showTooltipsAlways;

	void CalculateCharWidth(CDC* dc);
	int m_maxCharWidth;
	int m_charWidths[129];

	void DoUpdateClipRgn() const
	{
		m_clipRgn.DeleteObject();
		if(m_dnsMode)
		{
			m_clipRgn.CreateRectRgnIndirect(&m_ipRect);
		}
	}
	void SetClipRgn(HDC dc) const
	{
		SelectClipRgn(dc, m_clipRgn);
	}
	void ReleaseClipRgn(HDC dc) const
	{
		SelectClipRgn(dc, nullptr);
	}
	mutable CRgn m_clipRgn;
};

///////////

class MainMessageLoopWnd;

class UGUI_API TakionDialogInterface
{
public:
	const bool& isModal() const{return m_modal;}
	virtual bool isExecuteCommands() const{return false;}
	virtual bool isCloseOnCommandExecution() const{return false;}
	virtual void CloseDialog() = 0;
	virtual void AdjustFrameRect() = 0;
	virtual void OffsetFrameRectAndMove(int x, int y) = 0;
	virtual void DragWindow(int dx, int dy) = 0;
    virtual void SetFrameRect(const CRect& rect) = 0;
	virtual void MoveToFrameRect() = 0;
	virtual void UpdateSystemRects();
	virtual bool GetInsideScreen(CRect& rect) const;
	virtual void OnMouseForcedReleaseCapture(){}
	bool GetTotalInsideScreen(CRect& rect) const;
	MainMessageLoopWnd* GetMainWnd(){return m_mainWnd;}
//	static VisualBase* GetVisualBase(){return m_visualBase;}
//	static ConfigBase* GetConfigBase(){return m_takionConfig;}
	static VisualBase* m_visualBase;
	static ConfigBase* m_configBase;
	const CRect& GetTotalScreenRect() const{return m_totalScreenRect;}
	const CRect& GetScreenRect() const{return m_screenRect;}
	const CRect& GetDesktopRect() const{return m_desktopRect;}
	const CRect& GetDialogFrameRect() const{return m_dialogFrameRect;}

	const CRect& GetDialogClientRect() const{return m_clientRect;}
	const CRect& GetOriginalRect() const{return m_originalRect;}
	const CRect& GetOriginalClientRect() const{return m_originalClientRect;}
	const int& GetDialogBorder() const{return m_dialogBorder;}
	const int& GetMinVisibleSize() const{return m_minVisibleSize;}
	const bool& isSizeMove() const{return m_sizemove;}

	void InitMainWnd();
	const CRect& GetRectClient() const{return m_clientRect;}
	virtual HWND GetHwnd() const = 0;
	bool isWindowValid() const
	{
		HWND hwnd = GetHwnd();
		return hwnd && IsWindow(hwnd);
	}
//	bool MouseClickedOutsideModal(const MSLLHOOKSTRUCT* mouseHookStruct);
protected:
	TakionDialogInterface(MainMessageLoopWnd* mainWnd);
/*
	virtual bool DoMouseClickedOutsideModal()
	{
		CloseDialog();
		return true;
	}
*/
	void OnDialogDestroy();

	MainMessageLoopWnd* m_mainWnd;
	CRect m_desktopRect;
	CRect m_screenRect;
	CRect m_totalScreenRect;
	CRect m_dialogFrameRect;
	CRect m_originalDialogFrameRect;
	CRect m_clientRect;
	CRect m_originalRect;
	CRect m_originalClientRect;
	int m_dialogBorder;
	int m_minVisibleSize;
	bool m_sizemove;
	bool m_modal;
};

enum TakionWindowInfo : unsigned int
{
	TWT_BK_COLOR,

	TWT_Count
};

//class TakionFrame;
class TakionSettingDialog;

class DialogTemplate;

class UGUI_API TakionDialog : public CDialog, public TakionDialogInterface
{
friend class ResizeControl;
public:
	virtual ~TakionDialog();

	bool CreateModeless(CWnd* parent);

	bool CreateModal(CWnd* parent);

	int RunModalLoop(DWORD dwFlags = 0);

	unsigned int GetId() const{return m_id;}

	virtual COLORREF GetBkColor() const{return GetSysColor(COLOR_BTNFACE);}
//	virtual CBrush* GetBkBrush() const{return nullptr;}
	virtual CBrush* GetBkBrush() const{return m_bkBrush;}

	virtual HWND GetHwnd() const{return m_hWnd;}

//	void SetMenuItemBitmapsCheck(CMenu& menu, unsigned int id);
//	void SetMenuItemBitmapsRadio(CMenu& menu, unsigned int id);

	void GetRectIndirect(RECT& rect);
	void SetRectIndirect(const RECT& rect);
	void SetRectIndirect(int x, int y, int w, int h);
	DWORD GetStyleIndirect() const;
	void SetStyleIndirect(DWORD style);
	void AddStyleIndirect(DWORD style);
	void RemoveStyleIndirect(DWORD style);
	DWORD GetExtendedStyleIndirect() const;
	void SetExtendedStyleIndirect(DWORD style);
	void AddExtendedStyleIndirect(DWORD style);
	void RemoveExtendedStyleIndirect(DWORD style);

	void AddComponentIndirect(LPCSTR type, LPCSTR caption, DWORD style, DWORD exStyle, int x, int y, int w, int h, WORD id, WORD insertBeforeId = 0);
	void AddButtonIndirect(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y, int w, int h, WORD id, WORD insertBeforeId = 0);
	void AddEditBoxIndirect(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y, int w, int h, WORD id, WORD insertBeforeId = 0);
	void AddStaticIndirect(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y, int w, int h, WORD id, WORD insertBeforeId = 0);
    void AddListBoxIndirect(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y, int w, int h, WORD id, WORD insertBeforeId = 0);
    void AddScrollBarIndirect(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y, int w, int h, WORD id, WORD insertBeforeId = 0);
	void AddComboBoxIndirect(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y, int w, int h, WORD id, WORD insertBeforeId = 0);

	static const int checkBoxDeflation;//1
	static const int checkBoxTextOffset;//-2

	static unsigned int GetBindIp(const ComboBoxIp& comboBox);

	static void FillSpinControlFromTif(const unsigned int& millisecond, TimeSpin& spinControl, bool notifyParent);
	static void FillSpinControlFromMillisecond(const unsigned int& millisecond, TimeSpin& spinControl, bool notifyParent);

	static void FillSpinControlFromUChar(const unsigned char& value, UnsignedNumberTypeSpin<unsigned char>& spinControl, bool notifyParent);
	static void FillSpinControlFromChar(const char& value, SignedNumberTypeSpin<char>& spinControl, bool notifyParent);

	static void FillSpinControlFromUShort(const unsigned short& value, UnsignedNumberTypeSpin<unsigned short>& spinControl, bool notifyParent);
	static void FillSpinControlFromShort(const short& value, SignedNumberTypeSpin<short>& spinControl, bool notifyParent);

	static void FillSpinControlFromUInt(const unsigned int& value, UnsignedNumberTypeSpin<unsigned int>& spinControl, bool notifyParent);
	static void FillSpinControlFromInt(const int& value, SignedNumberTypeSpin<int>& spinControl, bool notifyParent);

	static void FillSpinControlFromUInt64(const unsigned __int64& value, UnsignedNumberTypeSpin<unsigned __int64>& spinControl, bool notifyParent);
	static void FillSpinControlFromInt64(const __int64& value, SignedNumberTypeSpin<__int64>& spinControl, bool notifyParent);

	static void FillPriceFromSpinControl(Price& price, const UnsignedNumberTypeSpin<unsigned int>& spinPriceControl, const unsigned int divider);
	static void FillSpinControlFromPrice(const Price& price, UnsignedNumberTypeSpin<unsigned int>& spinPriceControl, const unsigned int divider, bool notifyParent);
	static void FillSignedPriceFromSpinControl(SignedPrice& price, const SignedNumberTypeSpin<int>& spinPriceControl, const unsigned int divider);
	static void FillSpinControlFromSignedPrice(const SignedPrice& price, SignedNumberTypeSpin<int>& spinPriceControl, const unsigned int divider, bool notifyParent);

	static void FillPriceFromSpinControl(Price& price, const UnsignedNumberTypeSpin<unsigned __int64>& spinPriceControl, const unsigned int divider);
	static void FillSpinControlFromPrice(const Price& price, UnsignedNumberTypeSpin<unsigned __int64>& spinPriceControl, const unsigned int divider, bool notifyParent);
	static void FillSignedPriceFromSpinControl(SignedPrice& price, const SignedNumberTypeSpin<__int64>& spinPriceControl, const unsigned int divider);
	static void FillSpinControlFromSignedPrice(const SignedPrice& price, SignedNumberTypeSpin<__int64>& spinPriceControl, const unsigned int divider, bool notifyParent);

	static void FillMoneyFromSpinControl(Money& money, const SignedNumberTypeSpin<__int64>& spinPriceControl, const unsigned int divider);
	static void FillSpinControlFromMoney(const Money& money, SignedNumberTypeSpin<__int64>& spinPriceControl, const unsigned int divider, bool notifyParent);

	static void FillMoneyFromUnsignedSpinControl(Money& money, const UnsignedNumberTypeSpin<unsigned __int64>& spinPriceControl, const unsigned int divider);
	static void FillUnsignedSpinControlFromMoney(const Money& money, UnsignedNumberTypeSpin<unsigned __int64>& spinPriceControl, const unsigned int divider, bool notifyParent);

	static int RemoveItemFromListBox(ListBoxOwnerDraw& listBox, const void* item);

	bool SetEditTextWithoutNotification(EditNoContext& edit, const char* text, bool notify);

	virtual bool isOrderDialog() const{return false;}
	virtual bool isToDestroyOnFocus() const{return false;}

    virtual void SetFrameRect(const CRect& rect);

	virtual void MoveToFrameRect();
	virtual void AdjustFrameRect();
	virtual void OffsetFrameRectAndMove(int x, int y);

	virtual TakionSettingDialog* GetCurrentLeaf(){return nullptr;}
	virtual const TakionSettingDialog* GetCurrentLeaf() const{return nullptr;}

	virtual INT_PTR DoModal();

	virtual void CloseDialog();

	virtual HWND GetFirstTabControl() const{return nullptr;}
	void SetFocusOnFirstControl();

	virtual void DragWindow(int dx, int dy);
	void RepaintChildren(bool all = false);

	virtual void Apply(){}
	virtual void Help();
	virtual std::string GetHelpUrl() const;
	virtual void OnOK() override;
	virtual void OnCancel() override;

	const bool& isMouseInside() const{return m_mouseInside;}
	const bool& isMouseNcInside() const{return m_ncMouseInside;}

	static bool EnableControl(HWND control, bool enable, HWND alternateControl);
	const bool& isRightBase() const{return m_rightBase;}
	const bool& isBottomBase() const{return m_bottomBase;}
	void SetRightBase(bool rightBase){m_rightBase = rightBase;}
	void SetBottomBase(bool bottomBase){m_bottomBase = bottomBase;}

	const bool& isDialogDisplayed() const{return m_dialogDisplayed;}
	const bool& isActive() const{return m_active;}
	const bool& isCreating() const{return m_creating;}
	const bool& isInitiallyVisible() const{return m_initiallyVisible;}
	void SetInitiallyVisible(bool visible);//should be called before the dialog is created;
	void UpdateDimensions();
	void SetNcCursor();
	const bool& isOnTop() const{return m_onTop;}
	void SetOnTop(bool onTop);
	unsigned char UpdateMouseArea(MouseArea& mouseArea, const CPoint& point);
	virtual void OnMouseForcedReleaseCapture();
	class TitleInfo
	{
	friend class TakionDialog;
	public:
		TitleInfo(const ListBoxOwnerDraw* listBox, const CRect& titleRect, const CRect& totalRect):
			m_listBox(listBox),
			m_horizontalScroller(m_listBox->GetHorizontalScroller()),
			m_titleRect(0, 0, 0, 0),
			m_totalRect(0, 0, 0, 0),
			m_clipRgnTitle(nullptr),
			m_clipRgnTotal(nullptr),
			m_listBoxId((unsigned int)listBox->GetDlgCtrlID())
		{
			SetTitleRect(titleRect);
			SetTotalRect(totalRect);
		}
		TitleInfo(const TitleInfo& other):
			m_listBox(other.m_listBox),
			m_horizontalScroller(other.m_horizontalScroller),
			m_titleRect(0, 0, 0, 0),
			m_totalRect(0, 0, 0, 0),
			m_clipRgnTitle(nullptr),
			m_clipRgnTotal(nullptr),
			m_listBoxId(other.m_listBoxId)
		{
			SetTitleRect(other.m_titleRect);
			SetTotalRect(other.m_totalRect);
		}
		TitleInfo& operator=(const TitleInfo& other)
		{
			m_listBox = other.m_listBox;
			m_horizontalScroller = other.m_horizontalScroller;
			m_listBoxId = other.m_listBoxId;

			SetTitleRect(other.m_titleRect);
			SetTotalRect(other.m_totalRect);

			return *this;
		}
		~TitleInfo()
		{
			if(m_clipRgnTitle)DeleteObject(m_clipRgnTitle);
			if(m_clipRgnTotal)DeleteObject(m_clipRgnTotal);
		}
		const ListBoxOwnerDraw* const& GetListBox() const{return m_listBox;}
		const unsigned int& GetListBoxId() const{return m_listBoxId;}
		const LbHorizontalScroller* GetHorizontalScroller() const{return m_horizontalScroller;}
		static void SetRectAndClipRgn(CRect& rectToSet, const CRect& rect, HRGN& clipRgn);

		const CRect& GetTitleRect() const{return m_titleRect;}
		void SetTitleRect(const CRect& rect){SetRectAndClipRgn(m_titleRect, rect, m_clipRgnTitle);}

		const CRect& GetTotalRect() const{return m_totalRect;}
		void SetTotalRect(const CRect& rect){SetRectAndClipRgn(m_totalRect, rect, m_clipRgnTotal);}

		int SetClipRgnTitle(CDC& dc) const{return SelectClipRgn(dc, m_clipRgnTitle);}
		int SetClipRgnTotal(CDC& dc) const{return SelectClipRgn(dc, m_clipRgnTotal);}
		void ReleaseClipRgn(CDC& dc) const{SelectClipRgn(dc, nullptr);}
	protected:
		const ListBoxOwnerDraw* m_listBox;
		const LbHorizontalScroller* m_horizontalScroller;
		CRect m_titleRect;
		CRect m_totalRect;
		HRGN m_clipRgnTitle;
		HRGN m_clipRgnTotal;

		unsigned int m_listBoxId;
	};
#if(_MSC_VER > 1600)
	typedef std::unordered_map<unsigned int, TitleInfo> TitleMap;
#else
	typedef std::hash_map<unsigned int, TitleInfo> TitleMap;
#endif
	bool AddTitle(const ListBoxOwnerDraw* listBox);
	bool RemoveTitle(unsigned int listBoxId);
	bool ClearTitles();
	const TitleInfo* FindTitleInfo(unsigned int listBoxId) const;
	inline void InvalidateRectIfValid(const RECT* rect) const{if(m_hWnd)::InvalidateRect(m_hWnd, rect, FALSE);}
	void InvalidateAllTotalValueRects(const unsigned int& listBoxId) const
	{
		if(m_hWnd)
		{
			const TitleInfo* titleInfo = FindTitleInfo(listBoxId);
			if(titleInfo)
			{
//				InvalidateRectIfValid(titleInfo->GetTotalRect());
				::InvalidateRect(m_hWnd, titleInfo->GetTotalRect(), FALSE);
			}
		}
	}
	void InvalidateTotalValueRect(const unsigned int& listBoxId, const unsigned short& columnId) const
	{
		if(m_hWnd)
		{
			const TitleInfo* titleInfo = FindTitleInfo(listBoxId);
			if(titleInfo)
			{
				const LbHorizontalScroller* scroller = titleInfo->GetHorizontalScroller();
				if(scroller)
				{
					CRect columnRect = titleInfo->GetTotalRect();
					if(scroller->GetColumnBounds(columnId, columnRect))
					{
						::InvalidateRect(m_hWnd, columnRect, FALSE);
					}
				}
			}
		}
	}
	virtual const char* GetTotalValue(unsigned int listBoxId, unsigned short columnId, char* buf, unsigned int buflen) const{return nullptr;}
	LbColumn* GetColumnRects(unsigned int listBoxId, unsigned short id, CRect& titleRect, CRect& totalRect) const;
	virtual void GetTitleRect(const ListBoxOwnerDraw* listBox, CRect& titleRect, CRect& totalRect) const
	{
		titleRect.left =
			titleRect.top =
			titleRect.right =
			titleRect.bottom =
		totalRect.left =
			totalRect.top =
			totalRect.right =
			totalRect.bottom =

			0;
	}
	void ScrollTitle(unsigned int listBoxId, int diff);

	void Corner();
	void Top();

	void AddListBox(ListBoxOwnerDraw* lb){m_listBoxSet.insert(lb);}
	void RemoveListBox(ListBoxOwnerDraw* lb){m_listBoxSet.erase(lb);}
	void ClearListBoxes(){m_listBoxSet.clear();}

	const bool& isResizable() const{return m_resizable;}
	const bool& isDraggable() const{return m_draggable;}

//	typedef std::list<ActiveRect*> ActiveRectList;//Mouse LeftClick and Hover Interactive Contros
	void AddActiveRect(ActiveRect* activeRect, COLORREF bkColor = 0xFFFFFFFF);
	void RemoveActiveRect(ActiveRect* activeRect);
	void SetActiveRectBkColor(const COLORREF color);
	void SetActiveRectFgColor(const COLORREF color);
	void SetActiveRectBorderColor(const COLORREF color);
	void InitActiveRectWnd();

//	typedef std::list<CustomGroupBox*> CustomGroupBoxList;//replaces GroupBox
	void AddCustomGroupBox(CustomGroupBox* groupBox);
	void RemoveCustomGroupBox(CustomGroupBox* groupBox);
	void InitCustomGroupBoxWnd();
	void InitCustomGroupBoxRects(HDC hdc);

//	typedef std::list<StringArea*> StringAreaList;
	void AddStringArea(StringArea* stringArea);//replaces CStatic
	void RemoveStringArea(StringArea* stringArea);//replaces CStatic
	void InitStringAreaWnd();
	void InitStringAreaRects(HDC hdc);
	void SetStringAreaBkColor(const COLORREF color);

	static bool SearchItemsStatic(CEdit& editSearch, CString& searchStr, ListBoxOwnerDraw& lbPickFrom, ListBoxOwnerDraw* lbPickTo, CButton& buttonSearch, bool& searchDone);
	static unsigned char SearchOnKeyTyped(MSG* pMsg, CEdit& editSearch, CString& searchStr, ListBoxOwnerDraw& lbPickFrom, ListBoxOwnerDraw* lbPickTo, CButton& buttonSearch, bool& searchDone);
	static void SearchChangeStatic(CEdit& editSearch, const char* searchStr, CButton& buttonSearch, bool& searchDone);

	typedef std::map<unsigned short, ResizeControl*> ResizeControlMap;
	typedef std::list<ResizeControl*> ResizeControlList;
	const ResizeControl* FindResizeControl(const unsigned short& id) const{ResizeControlMap::const_iterator found = m_resizeControlMap.find(id); return found == m_resizeControlMapEnd ? nullptr : found->second;}
	ResizeControl* AddResizeControl(ResizeControl* const& resizeControl);

	void MeasureComboBoxItemByFont(LPMEASUREITEMSTRUCT lpMeasureItemStruct, const ComboBoxOwnerDraw* comboBox, int additionalHeight);

	void ResizeToFrame(const bool& move) const
	{
		if(m_hWnd)::SetWindowPos(m_hWnd, HWND_TOP, m_dialogFrameRect.left, m_dialogFrameRect.top, m_dialogFrameRect.Width(), m_dialogFrameRect.Height(), SWP_NOZORDER|(move ? 0 : SWP_NOMOVE));
	}
	virtual bool isPointForRButtonMenuOk(UINT nFlags, CPoint point) const{return false;}
	virtual bool isPointForNcRButtonMenuOk(UINT nFlags, CPoint point) const{return false;}
	virtual bool UpdateFrameBottom(){return false;}
	virtual bool UpdateFrameRight(){return false;}

	int MeasureText(const char* text, CFont* font, int charCount = -1, int* textHeight = nullptr) const;
	int MeasureTextHeight(const char* text, CFont* font, int charCount = -1) const;

	const bool& isTooltipsEnabled() const{return m_tooltipsEnabled;}
	bool SetToolTipsEnabled(const bool& enabled)
	{
		if(enabled != m_tooltipsEnabled)
		{
			m_tooltipsEnabled = enabled;
			if(m_hWnd)
//			if(m_dialogDisplayed)
			{
				EnableTooltips(enabled);
			}
			return true;
		}
		return false;
	}
	static bool useToolTipsByDefault;//= false; //used in TakionDialog::InitializeToolTips()

	const void* GetDialogTemplateCopy() const;//You have to delete the copy when you no longer need it.
	static void DestroyDialogTemplateCopy(const void* other);
	bool CompareDialogTemplate(const void* other) const;

	virtual bool HasActiveRectMenu(const ActiveRect* activeRect) const{return false;}

	virtual bool isTooltipConfigValid() const{return m_configBase != nullptr;}
	virtual bool isToolTipsEnabledAdditional() const{return true;}
	virtual bool isToolTipsEnabled() const{return m_configBase->m_showTooltips.GetValue();}
protected:
	TakionDialog(MainMessageLoopWnd* mainWnd, bool draggable, LPCSTR caption = nullptr, DWORD style = 0, DWORD exstendedStyle = 0, int x = 0, int y = 0, int w = 0, int h = 0,
        LPCSTR font = nullptr, WORD fontSize = 8);
	TakionDialog(MainMessageLoopWnd* mainWnd, bool draggable, CWnd* par, unsigned int id);

	virtual void InitControls(){}

//	void DisplayMenu(const CPoint& point);
	virtual void DisplayMenu(const CPoint& point);
	virtual void PreAddMenuItems(CMenu& menu){}
	virtual void AddMenuItems(CMenu& menu){}
	virtual void PostAddMenuItems(CMenu& menu){}
	void AddMenuSeparator(CMenu& menu) const
	{
		if(menu.GetMenuItemCount())
		{
			menu.AppendMenu(MF_SEPARATOR);
//			menu.m_hMenu;
//			m_menuHasSeparator = true;
		}
	}
	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct){}
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct){return false;}

	virtual void DialogCancelled(){}

	virtual void ResizeControlsInitialized();
	void ClearAndDestroyResizeControls();

	virtual void OnResizeToFrame(){}

	virtual bool isCloseOnEnter() const;
	virtual void TitleScrolledHorizontally(unsigned int listBoxId, const CRect& titleRect, int diff){}
	virtual void TotalScrolledHorizontally(unsigned int listBoxId, const CRect& titleRect, int diff){}

	virtual void BeforeDestroy(){}
	virtual BOOL OnInitDialog() override;
	virtual BOOL PreTranslateMessage(MSG* pMsg) override;

	virtual bool PreWheel(UINT nFlags, short zDelta, CPoint pt){return false;}

	void CreateDcBitmap(CDC* dc, int width, int height);

	virtual void Entering();
	virtual void Leaving(){}

	virtual void FinishDialog(int result);
	virtual void AfterClose();

	virtual void MouseEntered(){}
	virtual void MouseLeft(){}
	virtual void NcMouseEntered(){}
	virtual void NcMouseLeft(){}

	virtual void DCCreated(){}

	virtual LRESULT LBDragEnter(DRAGDROPINFO& ddi, unsigned int ctrlId, ListBoxOwnerDraw* plb);
//	virtual void LBItemDraggedAndDropped(unsigned int ctrlId, unsigned int itemOrdinal){}
	virtual void LBItemDraggedAndDropped(unsigned int ctrlId, unsigned short from, unsigned short to){}
	virtual void LBDragDropDone(unsigned int ctrlId, int itemOrdinalOld, int itemOrdinalNew){}
	virtual void LBDragDropAbort(unsigned int ctrlId, int itemOrdinal){}

	virtual int ItemDropped(HWND hwndSource, ListBoxOwnerDraw* lb, unsigned int lbId, void* dataPtr, int& ordinalWhere);

	virtual bool ResizeMouseArea(const CPoint& point){return false;}
	virtual unsigned char UpdateResizeCursor(const CPoint& point, bool locked);//{return 0;}

	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg LRESULT OnKickIdle(WPARAM w, LPARAM l);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnterSizeMove();
	afx_msg void OnExitSizeMove();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);
	afx_msg void OnEnterMenuLoop(BOOL bIsTrackPopupMenu);
	afx_msg void OnExitMenuLoop(BOOL bIsTrackPopupMenu);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDestroy();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg LRESULT OnNcHitTest(CPoint point);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnApply();
	afx_msg void OnHelp();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcMouseLeave();

	afx_msg LRESULT OnDragEnter(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnDragOver(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnDragLeave(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnDragDrop(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnDragAbort(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnValueDraggedAndDropped(WPARAM w, LPARAM l);

	afx_msg LRESULT OnListBoxScrollColumns(WPARAM w, LPARAM l);

	afx_msg LRESULT OnInCtrlUnderMouseToWheel(WPARAM spinId, LPARAM spinPtr);
	afx_msg LRESULT OnOutCtrlUnderMouseToWheel(WPARAM spinId, LPARAM spinPtr);

	afx_msg LRESULT OnGetTakionDialogInfo(WPARAM infoType, LPARAM lparam);
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);//Intercepted in PreTranslateMessage

	DECLARE_MESSAGE_MAP()

	virtual void DoActivate(UINT state, bool minimized){}//, CWnd* pWndOther){}
    virtual void DoPaint(const RECT& rcPaint, CDC& dc);
    virtual void DoAdditionalPaint(const RECT& rcPaint, CDC& dc);
	void ScrollIdle(UINT nSBCode);
    
	virtual void Resize(bool widthChanged = true, bool heightChanged = true);
	virtual void AfterControlsResized(bool widthChanged, bool heightChanged){}

	unsigned int m_id;

	int m_dcBitmapWidth;
	int m_dcBitmapHeight;
    int m_initialWidth;
    int m_initialHeight;

	DialogTemplate* m_dialogTemplate;

	CDC m_dc;
	CBitmap m_dcBitmap;

	CBrush* m_bkBrush;

	virtual bool CreateToolTip();
	virtual bool DestroyToolTip();
//	virtual bool EnableToolTips(bool enable)
	virtual void ToolTipsEnabled(bool enable){}

//	virtual bool isTooltipConfigValid() const{return m_configBase != nullptr;}
//	virtual bool isToolTipsEnabledAdditional() const{return true;}
//	virtual bool isToolTipsEnabled() const{return m_configBase->m_showTooltips.GetValue();}
	virtual bool InitializeToolTips()
	{
//		return SetToolTipsEnabled(isTooltipConfigValid() ? isToolTipsEnabled() && isToolTipsEnabledAdditional() : useToolTipsByDefault);
		return PropagateToolTipsEnabled(isTooltipConfigValid() ? isToolTipsEnabled() && isToolTipsEnabledAdditional() : useToolTipsByDefault);
	}
	virtual bool PropagateToolTipsEnabled(bool enabled){return SetToolTipsEnabled(enabled);}

	void AddDialogToolTip(const unsigned int& tooltipId, const RECT& tooltipRect, const char* const& tooltipText)
	{
		if(m_toolTip && m_hWnd)
		{
			TOOLINFO toolInfo;
			toolInfo.cbSize = sizeof(TOOLINFO);
			toolInfo.hinst = nullptr;
			toolInfo.uFlags = TTF_SUBCLASS | TTF_TRANSPARENT;
			toolInfo.hwnd = m_hWnd;
			toolInfo.lParam = 0;
			toolInfo.lpReserved = nullptr;

			toolInfo.lpszText = (char*)tooltipText;// "Remove all items";
			toolInfo.uId = tooltipId;// 1;
			toolInfo.rect = tooltipRect;// m_clearItemsBox.GetRect();

			m_toolTip->AddTool(this, toolInfo.lpszText, &toolInfo.rect, toolInfo.uId);
			m_toolTip->SetToolInfo(&toolInfo);
//			m_toolTip->Activate(TRUE);
		}
	}
	void RemoveDialogToolTip(const unsigned int& tooltipId)
	{
		if(m_toolTip && m_hWnd)
		{
			m_toolTip->DelTool(this, tooltipId);
		}
	}
	
	CToolTipCtrl* m_toolTip;
	bool m_tooltipsEnabled;

//	CWnd* m_ctrlNoFocusToWheel;
	void NullifyCtrlNoFocusToWheel();
	HWND m_ctrlNoFocusToWheel;
	unsigned short m_ctrlNoFocusToWheelId;

	bool m_scroll;
	bool m_mouseActivated;
	bool m_active;
	bool m_dialogDisplayed;
	bool m_creating;
	bool m_initiallyVisible;
	HCURSOR m_cursorMove;
	HCURSOR m_cursorDrag;
	HCURSOR m_arrowCursor;

	bool m_mouseInside;
	bool m_ncMouseInside;

	bool m_menuDisplayed;

	bool m_rightBase;
	bool m_bottomBase;

	bool m_onTop;

	bool m_closeOnEnter;

	bool m_resizable;
	bool m_draggable;

//	bool m_rbuttonMenu;

	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
#if(_MSC_VER > 1600)
	typedef std::unordered_set<unsigned int> UIntSet;
	typedef std::unordered_set<ListBoxOwnerDraw*> ListBoxSet;
#else
	typedef std::hash_set<unsigned int> UIntSet;
	typedef std::hash_set<ListBoxOwnerDraw*> ListBoxSet;
#endif
	UIntSet m_editNoNotificationSet;
	UIntSet::iterator m_editNoNotificationSetEnd;

	CDragDropMgr m_ddm;						 // drag-drop manager

	ListBoxSet m_listBoxSet;
	ListBoxSet::const_iterator m_listBoxSetEnd;

	TitleMap* m_titleMap;
	ActiveRect* m_activeRect;

	bool SetActiveRect(ActiveRect* const& activeRect)
	{
		if(activeRect != m_activeRect)
		{
			m_activeRect = activeRect;
			ActiveRectChanged();
//			m_accumulatedWheel = 0;
			return true;
		}
		return false;
	}
	virtual void ActiveRectChanged(){}
	virtual void AddActiveRectMenuItems(CMenu& menu, const ActiveRect* activeRect){}

	bool DisplaySelection(bool rightButton, bool fastSelection, UINT nFlags, CPoint point);
	virtual bool DoDisplaySelection(const CRect& rect, bool rightButton, bool fastSelection){return false;}
	virtual bool NoActiveRectPressed(){return false;}
	bool MakeSelection(CPoint point);
	virtual void OnMakeSelection(){}

	ResizeControlMap m_resizeControlMap;
	ResizeControlMap::iterator m_resizeControlMapBegin;
	ResizeControlMap::const_iterator m_resizeControlMapEnd;
	ResizeControlList m_resizeControlList;
	ResizeControlList::iterator m_resizeControlListBegin;
	ResizeControlList::const_iterator m_resizeControlListEnd;
	bool m_resizeControlsInitialized;
private:
	bool EnableTooltips(bool enable)
	{
		const bool ret = enable ? CreateToolTip() : DestroyToolTip();
		if(ret)
		{
			ToolTipsEnabled(enable);
		}
		return ret;
	}

	DynamicPtrArray<ActiveRect> m_activeRectArray;
	DynamicPtrArray<CustomGroupBox> m_customGroupBoxArray;
	DynamicPtrArray<StringArea> m_stringAreaArray;
/*
	ActiveRectList m_activeRectList;
	ActiveRectList::const_iterator m_activeRectListBegin;
	ActiveRectList::const_iterator m_activeRectListEnd;

	CustomGroupBoxList m_customGroupBoxList;
	CustomGroupBoxList::const_iterator m_customGroupBoxListBegin;
	CustomGroupBoxList::const_iterator m_customGroupBoxListEnd;

	StringAreaList m_stringAreaList;
	StringAreaList::const_iterator m_stringAreaListBegin;
	StringAreaList::const_iterator m_stringAreaListEnd;
*/
	TakionDialog(const TakionDialog& other);
	TakionDialog& operator=(const TakionDialog& other);
};

class UGUI_API ResizeControl
{
friend class TakionDialog;
public:
	static const int zero;
	virtual ~ResizeControl(){}
	const unsigned short& GetId() const{return m_id;}
	HWND GetHwnd() const{return m_hWnd;}
	const int& GetLeftOffset() const{return m_leftOffset;}
	const int& GetTopOffset() const{return m_topOffset;}
	const int& GetWidth() const{return m_width;}
	const int& GetHeight() const{return m_height;}
	int GetRight() const{return m_leftOffset + m_width;}
	int GetBottom() const{return m_topOffset + m_height;}
//	virtual const int& GetWidth() const{return zero;}
	TakionDialog* GetDlg(){return m_dlg;}

protected:
	ResizeControl(TakionDialog* dlg, const unsigned short& id):m_dlg(dlg), m_id(id), m_hWnd(nullptr), m_leftOffset(0), m_topOffset(0), m_width(0), m_height(0){}
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect)
	{
		m_leftOffset = controlRect.left - originalClientRect.left;
		m_topOffset = controlRect.top - originalClientRect.top;
		m_width = controlRect.Width();
		m_height = controlRect.Height();
	}
	bool Initialize()
	{
		if(m_hWnd)
		{
			return true;
		}
		else if(m_dlg->m_hWnd)
		{
			m_hWnd = GetDlgItem(m_dlg->m_hWnd, m_id);
			if(m_hWnd)
			{
				const CRect& originalClientRect = m_dlg->GetOriginalClientRect();

				CRect controlRect;
				GetWindowRect(m_hWnd, &controlRect);
#ifdef _DEBUG
				if(controlRect.left > 32000 || controlRect.top > 32000)
				{
					printf("X");
				}
#endif
				m_dlg->ScreenToClient(&controlRect);

				DoInitialize(originalClientRect, controlRect);

				return true;
			}
		}
		return false;
	}

	virtual void Reset()
	{
		m_hWnd = nullptr;
		m_leftOffset = 0;
		m_topOffset = 0;
		m_width = 0;
		m_height = 0;
	}
	virtual void Resize(const CRect& clientRect, bool widthChanged, bool heightChanged)
	{
		if(m_hWnd)
		{
			DoResize(clientRect, widthChanged, heightChanged);
		}
	}
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) = 0;
	TakionDialog* m_dlg;
	unsigned short m_id;
	HWND m_hWnd;
	int m_leftOffset;
	int m_topOffset;
	int m_width;
	int m_height;
};

class UGUI_API ResizeControlVertical : public ResizeControl
{
protected:
	ResizeControlVertical(TakionDialog* dlg, const unsigned short& id):ResizeControl(dlg, id){}
/*
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect)
	{
		m_leftOffset = controlRect.left - originalClientRect.left;
	}
*/
};

class UGUI_API ResizeControlHorizontal : public ResizeControl
{
protected:
	ResizeControlHorizontal(TakionDialog* dlg, const unsigned short& id):ResizeControl(dlg, id){}
/*
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect)
	{
		m_topOffset = controlRect.top - originalClientRect.top;
	}
*/
};

class UGUI_API HorizontalMoveControl : public ResizeControlHorizontal
{
public:
	HorizontalMoveControl(TakionDialog* dlg, const unsigned short& id):ResizeControlHorizontal(dlg, id){}
protected:
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		ResizeControlHorizontal::DoInitialize(originalClientRect, controlRect);
		m_leftOffset = originalClientRect.right - controlRect.left;
	}
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(heightChanged)
		{
			::SetWindowPos(m_hWnd, HWND_TOP, clientRect.right - m_leftOffset, m_topOffset, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		}
	}
};

class UGUI_API HorizontalMoveControlRelativeControl : public ResizeControlHorizontal
{
public:
	const unsigned short& GetRelativeId() const{return m_relativeId;}
	HWND GetRelativeControl() const{return m_relativeControl;}
	const int& GetRelativeLeft() const{return m_relativeLeft;}
	const int& GetRelativeRight() const{return m_relativeRight;}
	const int& GetHorizontalGap() const{return m_horizontalGap;}
	virtual int CalculateGap(const CRect& relativeControlRect) const = 0;
	bool SetHorizontalGap(const int& horizontalGap)
	{
		if(m_useHorizontalGap && horizontalGap != m_horizontalGap)
		{
			m_horizontalGap = horizontalGap;
			return true;
		}
		return false;
	}
protected:
	HorizontalMoveControlRelativeControl(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& relativeId,
		const bool& useHorizontalGap,
		const int& horizontalGap):
		ResizeControlHorizontal(dlg, id),
		m_relativeId(relativeId),
		m_relativeControl(nullptr),
		m_relativeLeft(0),
		m_relativeRight(0),
//		m_relativeWidth(0),
		m_useHorizontalGap(useHorizontalGap),
		m_horizontalGap(useHorizontalGap ? horizontalGap : 0)//horizontalGap)
	{}
	virtual void Reset() override
	{
		ResizeControlHorizontal::Reset();
		m_relativeControl = nullptr;
		m_relativeLeft = 0;
		m_relativeRight = 0;
//		m_relativeWidth = 0;
//		m_horizontalGap = 0;
	}
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		ResizeControlHorizontal::DoInitialize(originalClientRect, controlRect);
//		m_leftOffset = originalClientRect.right - controlRect.left;
		if(!m_relativeControl)
		{
			m_relativeControl = m_relativeId ? GetDlgItem(m_dlg->m_hWnd, m_relativeId) : nullptr;
			if(m_relativeControl)
			{
				CRect relativeControlRect;
				GetWindowRect(m_relativeControl, &relativeControlRect);
				m_dlg->ScreenToClient(&relativeControlRect);

				if(!m_useHorizontalGap)
				{
					m_horizontalGap = CalculateGap(relativeControlRect);//m_leftOffset - relativeControlRect.right;
				}

				m_relativeLeft = relativeControlRect.left;
				m_relativeRight = relativeControlRect.right;
//				m_relativeWidth = controlRect.Width();
			}
			else
			{
				m_relativeLeft = m_leftOffset;
				m_relativeRight = m_leftOffset;
//				m_relativeWidth = 0;
			}
		}
	}
/*
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(widthChanged)
		{
//			::SetWindowPos(m_hWnd, HWND_TOP, clientRect.right - m_leftOffset, m_topOffset, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
			::SetWindowPos(m_hWnd, HWND_TOP, m_relativeRight + m_horizontalGap, m_topOffset, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		}
	}
*/
	unsigned short m_relativeId;
	HWND m_relativeControl;
	int m_relativeLeft;
	int m_relativeRight;
	bool m_useHorizontalGap;
	int m_horizontalGap;
};

class UGUI_API HorizontalMoveControlAfterControl : public HorizontalMoveControlRelativeControl
{
public:
	HorizontalMoveControlAfterControl(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& relativeId,
		const bool& useHorizontalGap,
		const int& horizontalGap):
		HorizontalMoveControlRelativeControl(dlg, id, relativeId, useHorizontalGap, horizontalGap)
	{}
	virtual int CalculateGap(const CRect& relativeControlRect) const{return m_leftOffset - relativeControlRect.right;}
protected:
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(widthChanged)
		{
			::SetWindowPos(m_hWnd, HWND_TOP, m_relativeRight + m_horizontalGap, m_topOffset, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		}
	}
};

class UGUI_API HorizontalMoveControlAfterControlDynamic : public HorizontalMoveControlAfterControl
{
public:
	HorizontalMoveControlAfterControlDynamic(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& relativeId,
		const bool& useHorizontalGap,
		const int& horizontalGap):
		HorizontalMoveControlAfterControl(dlg, id, relativeId, useHorizontalGap, horizontalGap)
	{}
protected:
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(widthChanged)
		{
			CRect r;
			GetWindowRect(m_relativeControl, &r);
			m_dlg->ScreenToClient(&r);
			m_relativeLeft = r.left;
			m_relativeRight = r.right;
			::SetWindowPos(m_hWnd, HWND_TOP, m_relativeRight + m_horizontalGap, m_topOffset, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		}
	}
};

class UGUI_API HorizontalMoveControlBeforeControl : public HorizontalMoveControlRelativeControl
{
public:
	HorizontalMoveControlBeforeControl(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& relativeId,
		const bool& useHorizontalGap,
		const int& horizontalGap)://should be negative
		HorizontalMoveControlRelativeControl(dlg, id, relativeId, useHorizontalGap, horizontalGap)
	{}
	virtual int CalculateGap(const CRect& relativeControlRect) const{return m_leftOffset - relativeControlRect.left;}
protected:
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(widthChanged)
		{
//			::SetWindowPos(m_hWnd, HWND_TOP, clientRect.right - m_leftOffset, m_topOffset, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
			::SetWindowPos(m_hWnd, HWND_TOP, m_relativeLeft - m_width + m_horizontalGap, m_topOffset, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		}
	}
};

class UGUI_API HorizontalMoveControlBeforeControlDynamic : public HorizontalMoveControlBeforeControl
{
public:
	HorizontalMoveControlBeforeControlDynamic(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& relativeId,
		const bool& useHorizontalGap,
		const int& horizontalGap)://should be negative
		HorizontalMoveControlBeforeControl(dlg, id, relativeId, useHorizontalGap, horizontalGap)
	{}
protected:
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(widthChanged)
		{
			CRect r;
			GetWindowRect(m_relativeControl, &r);
			m_dlg->ScreenToClient(&r);
			m_relativeLeft = r.left;
			m_relativeRight = r.right;
			::SetWindowPos(m_hWnd, HWND_TOP, m_relativeLeft - m_width + m_horizontalGap, m_topOffset, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		}
	}
};

class UGUI_API VerticalMoveControl : public ResizeControlVertical
{
public:
	VerticalMoveControl(TakionDialog* dlg, const unsigned short& id):ResizeControlVertical(dlg, id){}
protected:
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		ResizeControlVertical::DoInitialize(originalClientRect, controlRect);
		m_topOffset = originalClientRect.bottom - controlRect.top;
	}
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(heightChanged)
		{
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, clientRect.bottom - m_topOffset, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		}
	}
};

class UGUI_API VerticalMoveControlRelativeControl : public ResizeControlVertical
{
public:
	const unsigned short& GetRelativeId() const{return m_relativeId;}
	HWND GetRelativeControl() const{return m_relativeControl;}
	const int& GetRelativeTop() const{return m_relativeTop;}
	const int& GetRelativeBottom() const{return m_relativeBottom;}
	const int& GetVerticalGap() const{return m_verticalGap;}
	virtual int CalculateGap(const CRect& relativeControlRect) const = 0;
	bool SetVerticalGap(const int& verticalGap)
	{
		if(m_useVerticalGap && verticalGap != m_verticalGap)
		{
			m_verticalGap = verticalGap;
			return true;
		}
		return false;
	}
protected:
	VerticalMoveControlRelativeControl(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& relativeId,
		const bool& useVerticalGap,
		const int& verticalGap):
		ResizeControlVertical(dlg, id),
		m_relativeId(relativeId),
		m_relativeControl(nullptr),
		m_relativeTop(0),
		m_relativeBottom(0),
//		m_relativeWidth(0),
		m_useVerticalGap(useVerticalGap),
		m_verticalGap(useVerticalGap ? verticalGap : 0)//horizontalGap)
	{}
	virtual void Reset() override
	{
		ResizeControlVertical::Reset();
		m_relativeControl = nullptr;
		m_relativeTop = 0;
		m_relativeBottom = 0;
//		m_relativeWidth = 0;
//		m_horizontalGap = 0;
	}
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		ResizeControlVertical::DoInitialize(originalClientRect, controlRect);
//		m_leftOffset = originalClientRect.right - controlRect.left;
		if(!m_relativeControl)
		{
			m_relativeControl = m_relativeId ? GetDlgItem(m_dlg->m_hWnd, m_relativeId) : nullptr;
			if(m_relativeControl)
			{
				CRect relativeControlRect;
				GetWindowRect(m_relativeControl, &relativeControlRect);
				m_dlg->ScreenToClient(&relativeControlRect);

				if(!m_useVerticalGap)
				{
					m_verticalGap = CalculateGap(relativeControlRect);//m_leftOffset - relativeControlRect.right;
				}

				m_relativeTop = relativeControlRect.left;
				m_relativeBottom = relativeControlRect.right;
//				m_relativeWidth = controlRect.Width();
			}
			else
			{
				m_relativeTop = m_topOffset;
				m_relativeBottom = m_topOffset;
//				m_relativeWidth = 0;
			}
		}
	}
/*
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(widthChanged)
		{
//			::SetWindowPos(m_hWnd, HWND_TOP, clientRect.right - m_leftOffset, m_topOffset, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
			::SetWindowPos(m_hWnd, HWND_TOP, m_relativeRight + m_horizontalGap, m_topOffset, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		}
	}
*/
	unsigned short m_relativeId;
	HWND m_relativeControl;
	int m_relativeTop;
	int m_relativeBottom;
	bool m_useVerticalGap;
	int m_verticalGap;
};

class UGUI_API VerticalMoveControlAfterControl : public VerticalMoveControlRelativeControl
{
public:
	VerticalMoveControlAfterControl(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& relativeId,
		const bool& useVerticalGap,
		const int& verticalGap):
		VerticalMoveControlRelativeControl(dlg, id, relativeId, useVerticalGap, verticalGap)
	{}
	virtual int CalculateGap(const CRect& relativeControlRect) const{return m_topOffset - relativeControlRect.bottom;}
protected:
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(heightChanged)
		{
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_relativeBottom + m_verticalGap, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		}
	}
};

class UGUI_API VerticalMoveControlAfterControlDynamic : public VerticalMoveControlAfterControl
{
public:
	VerticalMoveControlAfterControlDynamic(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& relativeId,
		const bool& useVerticalGap,
		const int& verticalGap):
		VerticalMoveControlAfterControl(dlg, id, relativeId, useVerticalGap, verticalGap)
	{}
protected:
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(heightChanged)
		{
			CRect r;
			GetWindowRect(m_relativeControl, &r);
			m_dlg->ScreenToClient(&r);
			m_relativeTop = r.top;
			m_relativeBottom = r.bottom;
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_relativeBottom + m_verticalGap, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		}
	}
};

class UGUI_API VerticalMoveControlBeforeControl : public VerticalMoveControlRelativeControl
{
public:
	VerticalMoveControlBeforeControl(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& relativeId,
		const bool& useVerticalGap,
		const int& verticalGap)://should be negative
		VerticalMoveControlRelativeControl(dlg, id, relativeId, useVerticalGap, verticalGap)
	{}
	virtual int CalculateGap(const CRect& relativeControlRect) const{return m_topOffset - relativeControlRect.top;}
protected:
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(heightChanged)
		{
//			::SetWindowPos(m_hWnd, HWND_TOP, clientRect.right - m_leftOffset, m_topOffset, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_relativeTop - m_height + m_verticalGap, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		}
	}
};

class UGUI_API VerticalMoveControlBeforeControlDynamic : public VerticalMoveControlBeforeControl
{
public:
	VerticalMoveControlBeforeControlDynamic(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& relativeId,
		const bool& useVerticalGap,
		const int& verticalGap)://should be negative
		VerticalMoveControlBeforeControl(dlg, id, relativeId, useVerticalGap, verticalGap)
	{}
protected:
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(heightChanged)
		{
			CRect r;
			GetWindowRect(m_relativeControl, &r);
			m_dlg->ScreenToClient(&r);
			m_relativeTop = r.top;
			m_relativeBottom = r.bottom;
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_relativeTop - m_height + m_verticalGap, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		}
	}
};
///
class UGUI_API VHResizeControl : public ResizeControlVertical
{
public:
	VHResizeControl(TakionDialog* dlg, const unsigned short& id):ResizeControlVertical(dlg, id){}
protected:
/*
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		ResizeControlVertical::DoInitialize(originalClientRect, controlRect);
		m_topOffset = controlRect.top - originalClientRect.top;
	}
*/
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(widthChanged || heightChanged)
		{
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_topOffset, clientRect.right - m_leftOffset, clientRect.bottom - m_topOffset, SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
		}
	}
};

class UGUI_API VHResizeControlVerticalOffset : public VHResizeControl
{
public:
	VHResizeControlVerticalOffset(TakionDialog* dlg, const unsigned short& id, const bool& useBottomOffset):
		VHResizeControl(dlg, id),
		m_bottomOffset(0),
		m_useBottomOffset(useBottomOffset)
	{}
	const int& GetBottomOffset() const{return m_bottomOffset;}
protected:
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		VHResizeControl::DoInitialize(originalClientRect, controlRect);
		m_bottomOffset = m_useBottomOffset ? originalClientRect.bottom - controlRect.bottom : 0;
	}
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(widthChanged || heightChanged)
		{
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_topOffset, clientRect.right - m_leftOffset, clientRect.bottom - m_topOffset - m_bottomOffset, SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
		}
	}
	int m_bottomOffset;
	bool m_useBottomOffset;
};

class UGUI_API VHResizeControlHorizontalFraction : public VHResizeControlVerticalOffset
{
public:
	VHResizeControlHorizontalFraction(TakionDialog* dlg,
		const unsigned short& id,
		const bool& useBottomOffset,
		const int& enumerator,
		const int& denominator):
		VHResizeControlVerticalOffset(dlg, id, useBottomOffset),
		m_enumerator(enumerator > 0 ? enumerator : 1),
		m_denominator(denominator)
	{
		if(m_denominator < m_enumerator)m_denominator = m_enumerator;
	}
	const int& GetEnumerator() const{return m_enumerator;}
	const int& GetDenominator() const{return m_denominator;}
protected:
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(widthChanged || heightChanged)
		{
			if(widthChanged)
			{
				m_width = clientRect.right > m_leftOffset ? (clientRect.right - m_leftOffset) * m_enumerator / m_denominator : 0;
			}
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_topOffset, m_width, clientRect.bottom - m_topOffset - m_bottomOffset, SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
		}
	}
	int m_enumerator;
	int m_denominator;
};

class UGUI_API VHResizeControlOffset : public VHResizeControlVerticalOffset
{
public:
	VHResizeControlOffset(TakionDialog* dlg, const unsigned short& id, const bool& useRightOffset, const bool& useBottomOffset):
		VHResizeControlVerticalOffset(dlg, id, useBottomOffset),
		m_rightOffset(0),
		m_useRightOffset(useRightOffset)
	{}
	const int& GetRightOffset() const{return m_rightOffset;}
protected:
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		VHResizeControlVerticalOffset::DoInitialize(originalClientRect, controlRect);
		m_rightOffset = m_useRightOffset ? originalClientRect.right - controlRect.right : 0;
	}
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(widthChanged || heightChanged)
		{
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_topOffset, clientRect.right - m_leftOffset - m_rightOffset, clientRect.bottom - m_topOffset - m_bottomOffset, SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
		}
	}
	int m_rightOffset;
	bool m_useRightOffset;
};

class UGUI_API VerticalResizeControl : public VHResizeControl
{
public:
	VerticalResizeControl(TakionDialog* dlg, const unsigned short& id):VHResizeControl(dlg, id){}//, m_width(0){}
protected:
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(heightChanged)
		{
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_topOffset, m_width, clientRect.bottom - m_topOffset, SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
		}
	}
};

class UGUI_API VerticalResizeControlBottomOffset : public VerticalResizeControl
{
public:
	VerticalResizeControlBottomOffset(TakionDialog* dlg, const unsigned short& id):VerticalResizeControl(dlg, id), m_bottomOffset(0){}
	const int GetBottomOffset() const{return m_bottomOffset;}
protected:
	virtual void Reset() override
	{
		VerticalResizeControl::Reset();
		m_bottomOffset = 0;
	}
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		VerticalResizeControl::DoInitialize(originalClientRect, controlRect);
		m_bottomOffset = originalClientRect.bottom - controlRect.bottom;
	}
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(heightChanged)
		{
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_topOffset, m_width, clientRect.bottom - m_topOffset - m_bottomOffset, SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
		}
	}
	int m_bottomOffset;
};
//horizontal
class UGUI_API HorizontalResizeControl : public VHResizeControl
{
public:
	HorizontalResizeControl(TakionDialog* dlg, const unsigned short& id):VHResizeControl(dlg, id){}//, m_width(0){}
protected:
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(widthChanged)
		{
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_topOffset, clientRect.right - m_leftOffset, m_height, SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
		}
	}
};

class UGUI_API HorizontalResizeControlRightOffset : public HorizontalResizeControl
{
public:
	HorizontalResizeControlRightOffset(TakionDialog* dlg, const unsigned short& id):HorizontalResizeControl(dlg, id), m_rightOffset(0){}
	const int GetRightOffset() const{return m_rightOffset;}
protected:
	virtual void Reset() override
	{
		HorizontalResizeControl::Reset();
		m_rightOffset = 0;
	}
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		HorizontalResizeControl::DoInitialize(originalClientRect, controlRect);
		m_rightOffset = originalClientRect.right - controlRect.right;
	}
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(heightChanged)
		{
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_topOffset, clientRect.right - m_leftOffset - m_rightOffset, m_height, SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
		}
	}
	int m_rightOffset;
};
///

class UGUI_API VerticalResizeControlBelowControl : public VerticalResizeControl
{
public:
	VerticalResizeControlBelowControl(TakionDialog* dlg, const unsigned short& id, const unsigned short& aboveId, const int& verticalGap):
		VerticalResizeControl(dlg, id),
		m_aboveId(aboveId),
		m_aboveControl(nullptr),
		m_aboveTop(0),
		m_aboveBottom(0),
		m_aboveWidth(0),
		m_verticalGap(verticalGap)
	{}
	const unsigned short& GetAboveId() const{return m_aboveId;}
	HWND GetAboveControl() const{return m_aboveControl;}
	const int& GetAboveTop() const{return m_aboveTop;}
	const int& GetAboveBottom() const{return m_aboveBottom;}
	const int& GetAboveWidth() const{return m_aboveWidth;}
	const int& GetVerticalGap() const{return m_verticalGap;}
protected:
	virtual void Reset() override
	{
		VerticalResizeControl::Reset();
		m_aboveControl = nullptr;
		m_aboveTop = 0;
		m_aboveBottom = 0;
		m_aboveWidth = 0;
	}
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		VerticalResizeControl::DoInitialize(originalClientRect, controlRect);
		if(!m_aboveControl)
		{
			m_aboveControl = m_aboveId ? GetDlgItem(m_dlg->m_hWnd, m_aboveId) : nullptr;
			if(m_aboveControl)
			{
				CRect controlRect;
				GetWindowRect(m_aboveControl, &controlRect);
				m_dlg->ScreenToClient(&controlRect);

				m_aboveTop = controlRect.top;
				m_aboveBottom = controlRect.bottom + m_verticalGap;
				m_aboveWidth = controlRect.Width();
			}
			else
			{
				m_aboveTop = m_topOffset;
				m_aboveBottom = m_topOffset + m_verticalGap;
				m_aboveWidth = 0;
			}
		}
	}

	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(heightChanged)
		{
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_aboveBottom, m_width, clientRect.bottom - m_aboveBottom, SWP_NOZORDER|SWP_NOACTIVATE);
		}
	}

	unsigned short m_aboveId;
	HWND m_aboveControl;
	int m_aboveTop;
	int m_aboveBottom;
	int m_aboveWidth;
	int m_verticalGap;
};

class UGUI_API VerticalResizeControlBelowControlAlignRight : public VerticalResizeControlBelowControl//above control aligns right
{
public:
	VerticalResizeControlBelowControlAlignRight(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& aboveId,
		const int& verticalGap,
		const int& alignmentOffset):
		VerticalResizeControlBelowControl(dlg, id, aboveId, verticalGap),
		m_alignmentOffset(alignmentOffset)
	{}
/*
	virtual void Reset() override
	{
		VerticalResizeControlBelowControl::Reset();
		m_alignmentOffset = 0;
	}
*/
protected:
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		VerticalResizeControlBelowControl::DoInitialize(originalClientRect, controlRect);
		if(m_aboveControl)
		{
			::SetWindowPos(m_aboveControl, HWND_TOP, m_leftOffset + m_width - m_aboveWidth - m_alignmentOffset, m_aboveTop, m_aboveWidth, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		}
	}
/*
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(heightChanged)
		{
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_aboveBottom, m_width, clientRect.bottom - m_aboveBottom, SWP_NOZORDER|SWP_NOACTIVATE);
		}
	}
*/
	int m_alignmentOffset;
};

class UGUI_API VerticalResizeControlBelowControlAlignLeft : public VerticalResizeControlBelowControl//above control aligns right
{
public:
	VerticalResizeControlBelowControlAlignLeft(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& aboveId,
		const int& verticalGap,
		const int& alignmentOffset):
		VerticalResizeControlBelowControl(dlg, id, aboveId, verticalGap),
		m_alignmentOffset(alignmentOffset)
	{}
protected:
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		VerticalResizeControlBelowControl::DoInitialize(originalClientRect, controlRect);
		if(m_aboveControl)
		{
			::SetWindowPos(m_aboveControl, HWND_TOP, m_leftOffset + m_alignmentOffset, m_aboveTop, m_aboveWidth, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		}
	}
	int m_alignmentOffset;
};

class UGUI_API VerticalResizeControlBelowControlFromMiddle : public VerticalResizeControlBelowControl
{
public:
	VerticalResizeControlBelowControlFromMiddle(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& aboveId,
		const int& verticalGap,
		const int& middleOffset):
		VerticalResizeControlBelowControl(dlg, id, aboveId, verticalGap),
		m_middle(0),
		m_middleOffset(middleOffset),
		m_aboveLeftOffset(0)
	{}
	const int& GetMiddle() const{return m_middle;}
	const int& GetMiddleOffset() const{return m_middleOffset;}
	const int& GetAboveLeftOffset() const{return m_aboveLeftOffset;}
protected:
	virtual void Reset() override
	{
		VerticalResizeControlBelowControl::Reset();
		m_middle = 0;
	}
	virtual void Resize(const CRect& clientRect, bool widthChanged, bool heightChanged)
	{
		if(m_hWnd)
		{
			CRect controlRect(0, 0, 0, 0);
			GetWindowRect(m_hWnd, &controlRect);
			m_dlg->ScreenToClient(&controlRect);

			DoInitialize(clientRect, controlRect);
			DoResize(clientRect, widthChanged, heightChanged);
		}
	}
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		VerticalResizeControlBelowControl::DoInitialize(originalClientRect, controlRect);
		m_middle = (originalClientRect.left + originalClientRect.right) / 2;
	}
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(widthChanged)
		{
			if(m_aboveControl)
			{
				::SetWindowPos(m_aboveControl, HWND_TOP, m_aboveLeftOffset, m_aboveTop, m_aboveWidth, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
			}
		}
		if(widthChanged || heightChanged)
		{
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_aboveBottom, m_width, clientRect.bottom - m_aboveBottom, SWP_NOZORDER|SWP_NOACTIVATE);
		}
	}
	int m_middle;
	int m_middleOffset;
	int m_aboveLeftOffset;
//	int m_alignmentOffset;
};

class UGUI_API VerticalResizeControlBelowControlFromMiddleLeft : public VerticalResizeControlBelowControlFromMiddle
{
public:
	VerticalResizeControlBelowControlFromMiddleLeft(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& aboveId,
		const int& verticalGap,
		const int& middleOffset,
		const int& alignmentOffset):
		VerticalResizeControlBelowControlFromMiddle(dlg, id, aboveId, verticalGap, middleOffset),
		m_alignmentOffset(alignmentOffset)
	{}
protected:
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		VerticalResizeControlBelowControlFromMiddle::DoInitialize(originalClientRect, controlRect);
		m_leftOffset = m_middle - m_middleOffset - m_width;
		m_aboveLeftOffset = m_middle - m_middleOffset - m_aboveWidth - m_alignmentOffset;//GetSystemMetrics(SM_CXEDGE);
		if(m_aboveControl)
		{
			::SetWindowPos(m_aboveControl, HWND_TOP, m_aboveLeftOffset, m_aboveTop, m_aboveWidth, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		}
		::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_aboveBottom, m_width, originalClientRect.bottom - m_aboveBottom, SWP_NOZORDER|SWP_NOACTIVATE);
	}
	int m_alignmentOffset;
};

class UGUI_API VerticalResizeControlBelowControlFromMiddleRight : public VerticalResizeControlBelowControlFromMiddle
{
public:
	VerticalResizeControlBelowControlFromMiddleRight(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& aboveId,
		const int& verticalGap,
		const int& middleOffset,
		const int& alignmentOffset):
		VerticalResizeControlBelowControlFromMiddle(dlg, id, aboveId, verticalGap, middleOffset),
		m_alignmentOffset(alignmentOffset)
	{}
protected:
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		VerticalResizeControlBelowControlFromMiddle::DoInitialize(originalClientRect, controlRect);
		m_leftOffset = m_aboveLeftOffset = m_middle + m_middleOffset;
		m_aboveLeftOffset += m_alignmentOffset;//GetSystemMetrics(SM_CXEDGE);
		if(m_aboveControl)
		{
			::SetWindowPos(m_aboveControl, HWND_TOP, m_aboveLeftOffset, m_aboveTop, m_aboveWidth, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		}
		::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_aboveBottom, m_width, originalClientRect.bottom - m_aboveBottom, SWP_NOZORDER|SWP_NOACTIVATE);
	}
	int m_alignmentOffset;
};
//
class UGUI_API HorizontalMoveControlAfterControlDynamicAndResize : public HorizontalMoveControlAfterControlDynamic
{
public:
	HorizontalMoveControlAfterControlDynamicAndResize(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& relativeId,
		const bool& useHorizontalGap,
		const int& horizontalGap):
		HorizontalMoveControlAfterControlDynamic(dlg, id, relativeId, useHorizontalGap, horizontalGap),
		m_bottomOffset(0)
	{}
	const int& GetBottomOffset() const{return m_bottomOffset;}
protected:
	virtual void Reset() override
	{
		HorizontalMoveControlAfterControlDynamic::Reset();
		m_bottomOffset = 0;
	}
	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		HorizontalMoveControlAfterControlDynamic::DoInitialize(originalClientRect, controlRect);
		m_bottomOffset = originalClientRect.bottom - controlRect.bottom;
	}
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(heightChanged)
		{
			m_height = clientRect.bottom - m_topOffset - m_bottomOffset;
		}
		if(widthChanged)
		{
			CRect r;
			GetWindowRect(m_relativeControl, &r);
			m_dlg->ScreenToClient(&r);
			m_relativeLeft = r.left;
			m_relativeRight = r.right;

			m_leftOffset = m_relativeRight + m_horizontalGap;
			m_width = clientRect.right > m_leftOffset ? clientRect.right - m_leftOffset : 0;
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_topOffset, m_width, m_height, SWP_NOZORDER|SWP_NOACTIVATE);
		}
		else
		{
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_topOffset, m_width, m_height, SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
		}
	}
	int m_bottomOffset;
};

class UGUI_API VerticalMoveControlAfterControlDynamicAndResize : public VerticalMoveControlAfterControlDynamic
{
public:
	VerticalMoveControlAfterControlDynamicAndResize(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& relativeId,
		const bool& useVerticalGap,
		const int& verticalGap):
		VerticalMoveControlAfterControlDynamic(dlg, id, relativeId, useVerticalGap, verticalGap),
		m_bottomOffset(0)
	{}
	const int& GetBottomOffset() const{return m_bottomOffset;}
protected:

	virtual void Reset() override
	{
		VerticalMoveControlAfterControlDynamic::Reset();
		m_bottomOffset = 0;
	}

	virtual void DoInitialize(const CRect& originalClientRect, const CRect& controlRect) override
	{
		VerticalMoveControlAfterControlDynamic::DoInitialize(originalClientRect, controlRect);
		m_bottomOffset = originalClientRect.bottom - controlRect.bottom;
	}

	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(heightChanged)
		{
			CRect r;
			GetWindowRect(m_relativeControl, &r);
			m_dlg->ScreenToClient(&r);
			m_relativeTop = r.top;
			m_relativeBottom = r.bottom;

			m_topOffset = m_relativeBottom + m_verticalGap;
			int h = m_topOffset + m_bottomOffset;
			m_height = clientRect.bottom > h ? clientRect.bottom - h : 0;
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_topOffset, m_width, m_height, SWP_NOZORDER|SWP_NOACTIVATE);
		}
		else
		{
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_topOffset, m_width, m_height, SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
		}
	}
	int m_bottomOffset;
};

class UGUI_API VHResizeControlHorizontalFractionMaxWidth : public VHResizeControlHorizontalFraction
{
public:
	VHResizeControlHorizontalFractionMaxWidth(TakionDialog* dlg,
		const unsigned short& id,
		const bool& useBottomOffset,
		const int& enumerator,
		const int& denominator,
		const int& maxWidth):
		VHResizeControlHorizontalFraction(dlg, id, useBottomOffset, enumerator, denominator),
		m_maxWidth(maxWidth)
	{
	}
	const int& GetMaxWidth() const{return m_maxWidth;}
	bool SetMaxWidth(const int& maxWidth)
	{
		if(maxWidth != m_maxWidth)
		{
			m_maxWidth = maxWidth;
			return true;
		}
		return false;
	}
protected:
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(widthChanged || heightChanged)
		{
			if(widthChanged)
			{
				if(clientRect.right > m_leftOffset)
				{
					m_width = (clientRect.right - m_leftOffset) * m_enumerator / m_denominator;
					if(m_maxWidth && m_width > m_maxWidth)m_width = m_maxWidth;
				}
				else
				{
					m_width = 0;
				}
			}
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_topOffset, m_width, clientRect.bottom - m_topOffset - m_bottomOffset, SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
		}
	}
	int m_maxWidth;
};

class UGUI_API VHResizeControlVerticalFraction : public VHResizeControlVerticalOffset
{
public:
	VHResizeControlVerticalFraction(TakionDialog* dlg,
		const unsigned short& id,
		const int& enumerator,
		const int& denominator):
		VHResizeControlVerticalOffset(dlg, id, false),//useBottomOffset),
		m_enumerator(enumerator > 0 ? enumerator : 1),
		m_denominator(denominator),
		m_additionalOffset(0)
	{
		if(m_denominator < m_enumerator)m_denominator = m_enumerator;
	}
	const int& GetEnumerator() const{return m_enumerator;}
	const int& GetDenominator() const{return m_denominator;}

	const int& GetAdditionalOffset() const{return m_additionalOffset;}
	bool SetAdditionalOffset(const int& additionalOffset)
	{
		if(additionalOffset != m_additionalOffset)
		{
			m_additionalOffset = additionalOffset;
			return true;
		}
		return false;
	}
protected:
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(heightChanged)
		{
			const int offset = m_topOffset + m_additionalOffset;// + m_bottomOffset;
			m_height = clientRect.bottom > offset ? (clientRect.bottom - offset) * m_enumerator / m_denominator : 0;
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_topOffset, m_width, m_height, SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
		}
	}
	int m_enumerator;
	int m_denominator;
	int m_additionalOffset;
};

class UGUI_API VerticalMoveControlAfterControlDynamicFraction : public VerticalMoveControlAfterControlDynamic
{
public:
	VerticalMoveControlAfterControlDynamicFraction(TakionDialog* dlg,
		const unsigned short& id,
		const unsigned short& relativeId,
		const int& enumerator,
		const int& denominator,
		const bool& useVerticalGap,
		const int& verticalGap):
		VerticalMoveControlAfterControlDynamic(dlg, id, relativeId, useVerticalGap, verticalGap),
		m_enumerator(enumerator),
		m_denominator(denominator),
		m_additionalOffset(0)
	{}
	const int& GetAdditionalOffset() const{return m_additionalOffset;}
	bool SetAdditionalOffset(const int& additionalOffset)
	{
		if(additionalOffset != m_additionalOffset)
		{
			m_additionalOffset = additionalOffset;
			return true;
		}
		return false;
	}
protected:
	virtual void Reset() override
	{
		VerticalMoveControlAfterControlDynamic::Reset();
		m_additionalOffset = 0;
	}
	virtual void DoResize(const CRect& clientRect, bool widthChanged, bool heightChanged) override
	{
		if(heightChanged)
		{
			CRect r;
			GetWindowRect(m_relativeControl, &r);
			m_dlg->ScreenToClient(&r);
			m_relativeTop = r.top;
			m_relativeBottom = r.bottom;

			m_topOffset = m_relativeBottom + m_verticalGap;

			const int offset = m_topOffset + m_additionalOffset;// + m_bottomOffset;
			m_height = clientRect.bottom > offset ? (clientRect.bottom - offset) * m_enumerator / m_denominator : 0;
			::SetWindowPos(m_hWnd, HWND_TOP, m_leftOffset, m_topOffset, m_width, m_height, SWP_NOZORDER|SWP_NOACTIVATE);
		}
	}
	int m_enumerator;
	int m_denominator;
	int m_additionalOffset;
};
////

class UGUI_API TakionColorDialog : public CColorDialog, public TakionDialogInterface
{
public:
	TakionColorDialog(MainMessageLoopWnd* mainWnd, const char* caption, COLORREF color, DWORD flags, CWnd* parent, COLORREF* customColors = nullptr, unsigned int customColorCount = 16);
	virtual INT_PTR DoModal();
	virtual void CloseDialog();
	virtual void AdjustFrameRect();
	virtual void OffsetFrameRectAndMove(int x, int y);
	virtual void DragWindow(int dx, int dy);
    virtual void SetFrameRect(const CRect& rect);
	virtual void MoveToFrameRect();
	virtual HWND GetHwnd() const{return m_hWnd;}
//	int RunModalLoop(DWORD dwFlags = 0);
protected:
	virtual BOOL OnInitDialog();
	virtual void PreSubclassWindow() override;
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnKickIdle(WPARAM w, LPARAM l);
	afx_msg void OnEnterSizeMove();
	afx_msg void OnExitSizeMove();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	std::string m_caption;
};

class UGUI_API TakionFileDialog : public CFileDialog, public TakionDialogInterface
{
friend class TakionFileDialogParentWnd;
public:
	TakionFileDialog(MainMessageLoopWnd* mainWnd, bool open, const char* defExt, const char* fileName, DWORD flags, const char* filter, const char* caption, CWnd* parent);
	virtual ~TakionFileDialog();
	virtual INT_PTR DoModal();
	virtual void CloseDialog();
	virtual void AdjustFrameRect();
	virtual void OffsetFrameRectAndMove(int x, int y);
	virtual void DragWindow(int dx, int dy);
    virtual void SetFrameRect(const CRect& rect);
	virtual void MoveToFrameRect();
	virtual HWND GetHwnd() const{return m_hWnd;}
//	int RunModalLoop(DWORD dwFlags = 0);
	bool isOpen() const{return m_open;}
protected:
	virtual BOOL OnInitDialog() override;
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
	virtual void OnInitDone();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnKickIdle(WPARAM w, LPARAM l);
	afx_msg void OnEnterSizeMove();
	afx_msg void OnExitSizeMove();
	afx_msg void OnDestroy();
	void EnterSizeMove();
	void ExitSizeMove();
	LRESULT KickIdle(WPARAM wp, LPARAM lp);
	std::string m_caption;
	std::string m_initialPath;
	TakionFileDialogParentWnd* m_fdParent;
	bool m_open;
};

class TakionFileDialogCheckBoxParentWnd;

class UGUI_API TakionCheckBoxFileDialog : public TakionFileDialog
{
public:
	unsigned int GetFlags() const;
	virtual const char* GetNameFlag(unsigned int i, unsigned char& flag) const{return nullptr;}
protected:
	TakionCheckBoxFileDialog(MainMessageLoopWnd* mainWnd,
		bool open,
		const char* defExt,
		const char* fileName,
		DWORD flags,
		bool createLbFlags,
		const char* filter,
		const char* caption,
		CWnd* parent);
	virtual BOOL OnInitDialog() override;
//	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
//	DECLARE_MESSAGE_MAP()
//	afx_msg void OnSize(UINT nType, int cx, int cy);
	TakionFileDialogCheckBoxParentWnd* m_fileDialogParent;
};
/*
class UGUI_API DraggableDialog : public TakionDialog
{
protected:
	DraggableDialog(MainMessageLoopWnd* mainWnd, CWnd* par, unsigned int id);
	DraggableDialog(MainMessageLoopWnd* mainWnd, LPCSTR caption = nullptr, DWORD style = 0, DWORD exstendedStyle = 0, int x = 0, int y = 0, int w = 0, int h = 0, LPCSTR font = nullptr, WORD fontSize = 8);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	DECLARE_MESSAGE_MAP()
};
*/
class UGUI_API ColoredDraggableDialog : public TakionDialog
{
public:
	ColoredDraggableDialog(MainMessageLoopWnd* mainWnd, CWnd* par, unsigned int id, COLORREF bkColor = GetSysColor(COLOR_BTNFACE)):
		TakionDialog(mainWnd, true, par, id),
		m_bkColor(bkColor),
		m_blinkColor(0xFFFFFFFF),
		m_blinkBrush(m_bkBrush),
		m_blinkState(false)
	{}
	ColoredDraggableDialog(MainMessageLoopWnd* mainWnd, COLORREF bkColor = GetSysColor(COLOR_BTNFACE), LPCSTR caption = nullptr, DWORD style = 0, DWORD exstendedStyle = 0, int x = 0, int y = 0, int w = 0, int h = 0, LPCSTR font = nullptr, WORD fontSize = 8):
		TakionDialog(mainWnd, true, caption, style, exstendedStyle, x, y, w, h, font, fontSize),
		m_bkColor(bkColor),
		m_blinkColor(0xFFFFFFFF),
		m_blinkBrush(m_bkBrush),
		m_blinkState(false)
	{}

	virtual void SetBkColor(COLORREF bkColor);

	virtual COLORREF GetBkColor() const{return m_blinkState ? m_blinkColor : m_bkColor;}
	virtual CBrush* GetBkBrush() const{return m_blinkState ? m_blinkBrush : m_bkBrush;}
	const COLORREF& GetBlinkColor() const{return m_blinkColor;}
	void SetBlinkColor(COLORREF color);
	void Blink();
protected:
	virtual void OnBlink(){}
	virtual BOOL OnInitDialog();
	virtual void AfterClose();
	COLORREF m_bkColor;
	COLORREF m_blinkColor;
	CBrush* m_blinkBrush;
	bool m_blinkState;
};

class MessageRect
{
public:
	MessageRect(const char* message):m_message(message),m_rect(0, 0, 0, 0){}
	MessageRect(const std::string& message):m_message(message),m_rect(0, 0, 0, 0){}
	bool SetMessage(const std::string& message, HDC hdc)
	{
		if(m_message!= message)
		{
			m_message = message;
			CalculateRect(m_rect.left, m_rect.top, hdc);
			return true;
		}
		return false;
	}
	bool SetMessage(const char* message, HDC hdc){return SetMessage(std::string(message), hdc);}
	const char* GetMessage() const{return m_message.c_str();}
	const CRect& GetRect() const{return m_rect;}
	void CalculateRect(int left, int top, HDC hdc)
	{
		m_rect.left = m_rect.right = left;
		m_rect.top = m_rect.bottom = top;
		DrawText(hdc, m_message.c_str(), -1, &m_rect, DT_LEFT|DT_TOP|DT_CALCRECT);
	}
protected:
	std::string m_message;
	CRect m_rect;
};

class UGUI_API TakionMessageBox : public ColoredDraggableDialog
{
public:
	TakionMessageBox(MainMessageLoopWnd* mainWnd, bool reusable = false, COLORREF bkColor = GetSysColor(COLOR_BTNFACE), unsigned int messageCap = 0xFFFFFFFF);
	virtual ~TakionMessageBox(){ClearCheckBoxes();}
	INT_PTR DisplayModal(CWnd* parent, const char* caption, unsigned int flags, COLORREF bkColor = RGB(0, 0, 128), COLORREF textColor = RGB(255, 255, 255), COLORREF captionColor = 0xFFFFFFFF, COLORREF blinkBkColor = 0xFFFFFFFF, COLORREF blinkTextColor = 0xFFFFFFFF, COLORREF blinkCaptionColor = 0xFFFFFFFF, unsigned int focusButton = 0, const char* thirdButtonName = nullptr, const char* secondButtonName = nullptr, const char* firstButtonName = nullptr);
	bool DisplayModeless(CWnd* parent, const char* caption, unsigned int flags, COLORREF bkColor = RGB(0, 0, 128), COLORREF textColor = RGB(255, 255, 255), COLORREF captionColor = 0xFFFFFFFF, COLORREF blinkBkColor = 0xFFFFFFFF, COLORREF blinkTextColor = 0xFFFFFFFF, COLORREF blinkCaptionColor = 0xFFFFFFFF, bool visible = true, unsigned int focusButton = 0, const char* thirdButtonName = nullptr, const char* secondButtonName = nullptr, const char* firstButtonName = nullptr);
	typedef std::list<MessageRect> MessageList;
	void ClearMessageList(bool adjustSize = true);
	bool AddMessage(const char* message, bool adjustSize = true, bool force = false);
	bool AddMessage(const std::string& message, bool adjustSize = true, bool force = false);
	void AddCheckBox(const char* text, bool checked, bool enabled, bool indented, bool adjustSize);
	void AdjustSize();
	bool GetCheckBoxState(unsigned short i) const;
	virtual bool GetInsideScreen(CRect& rect) const;
	virtual void OnOK() override;
	virtual void OnCancel() override;
	unsigned int GetMessageCap() const{return m_messageCap;}
	void SetMessageCap(unsigned int messageCap){m_messageCap = messageCap;}
	unsigned int GetMessageCount() const{return (unsigned int)m_messageList.size();}
	virtual void UpdateColors()
	{
		m_textColor = m_blinkColor;
		m_captionColor = m_textColor;//captionColor == 0xFFFFFFFF ? textColor : captionColor;
		m_blinkTextColor = m_bkColor;
		m_blinkCaptionColor = m_blinkTextColor;
	}
protected:
	CButton* AdjustPushButtons();
	virtual void OnBlink();
	virtual INT_PTR PrepareToDisplay(CWnd* parent, const char* caption, unsigned int flags, COLORREF bkColor, COLORREF textColor, COLORREF captionColor, COLORREF blinkBkColor = 0xFFFFFFFF, COLORREF blinkTextColor = 0xFFFFFFFF, COLORREF blinkCaptionColor = 0xFFFFFFFF, unsigned int focusButton = 0, const char* thirdButtonName = nullptr, const char* secondButtonName = nullptr, const char* firstButtonName = nullptr);
	virtual void FillControls(){}
	virtual void CalculateSize();
	virtual void BeforeDestroy() override;
	virtual void Resize(bool widthChanged = true, bool heightChanged = true) override;
	virtual void DoDataExchange(CDataExchange* pDX);
    virtual void DoPaint(const RECT& rcPaint, CDC& dc) override;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnYes();
	afx_msg void OnNo();
	afx_msg LRESULT OnKickIdle(WPARAM w, LPARAM l);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
	void CloseMessageBox(int result);
	CButton m_ButtonOk;
	CButton m_ButtonCancel;
	CButton m_ButtonYes;
	CButton m_ButtonNo;
	MessageList m_messageList;
	std::string m_caption;
	unsigned int m_flags;
	HICON m_icon;
	CRect m_iconRect;
	CFont* m_captionFont;
	CFont* m_font;
	CRect m_captionRect;
	COLORREF m_textColor;
	COLORREF m_captionColor;
	COLORREF m_blinkTextColor;
	COLORREF m_blinkCaptionColor;
	int m_doubleBorder;
	int m_horOffset;
	int m_verOffset;
	int m_verGap;
	int m_controlVerOffset;
	int m_textWidth;
	typedef std::list<CButton*> ButtonList;
	ButtonList m_buttonList;
	unsigned int m_buttonCount;
	int m_buttonWidth;
	int m_buttonHeight;
	int m_controlWidth;
	int m_controlHeight;
	int m_buttonYOffset;
	void ClearCheckBoxes();
	typedef std::vector<CheckBoxOwnerDraw*> ButtonVector;
	typedef std::vector<bool> BoolVector;
	ButtonVector m_checkBoxVector;
	BoolVector m_checkBoxState;
	typedef std::vector<CWnd*> WndVector;
	WndVector m_wndVector;
	int m_checkBoxHeight;
	int m_maxCheckBoxWidth;
	unsigned int m_checkBoxCount;

	int m_maxWndWidth;
	int m_wndHeight;

	unsigned int m_focusButton;

	CSize m_dimensions;

	unsigned int m_messageCap;
	bool m_reusable;

	std::string m_firstButtonName;
	std::string m_secondButtonName;
	std::string m_thirdButtonName;
};

class UGUI_API DialogCloseCommand : public TakionMessageBox
{
protected:
	DialogCloseCommand(MainMessageLoopWnd* mainWnd, COLORREF bkColor = GetSysColor(COLOR_BTNFACE));
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

class UGUI_API DialogPassword : public DialogCloseCommand
{
public:
	DialogPassword(MainMessageLoopWnd* mainWnd, COLORREF bkColor = GetSysColor(COLOR_BTNFACE));
	const std::string& GetPassword() const{return m_password;}
	INT_PTR DisplayModal(const char* password, CWnd* parent, const char* caption, unsigned int flags, COLORREF bkColor = RGB(0, 0, 128), COLORREF textColor = RGB(255, 255, 255), COLORREF captionColor = 0xFFFFFFFF, COLORREF blinkBkColor = 0xFFFFFFFF, COLORREF blinkTextColor = 0xFFFFFFFF, COLORREF blinkCaptionColor = 0xFFFFFFFF, unsigned int focusButton = 0);
protected:
	virtual INT_PTR PrepareToDisplay(CWnd* parent, const char* caption, unsigned int flags, COLORREF bkColor, COLORREF textColor, COLORREF captionColor, COLORREF blinkBkColor = 0xFFFFFFFF, COLORREF blinkTextColor = 0xFFFFFFFF, COLORREF blinkCaptionColor = 0xFFFFFFFF, unsigned int focusButton = 0, const char* thirdButtonName = nullptr, const char* secondButtonName = nullptr, const char* firstButtonName = nullptr) override;
	virtual void BeforeDestroy() override;
	virtual BOOL OnInitDialog() override;
	virtual void OnOK() override;
	virtual void DoDataExchange(CDataExchange* pDX);
//	virtual void OnCancel();
	afx_msg void OnTextChange();
	DECLARE_MESSAGE_MAP()

	EditNoContext m_EditPassword;
	std::string m_password;
	std::string m_myPassword;
};

class UGUI_API DialogStockWarning : public DialogCloseCommand
{
public:
	DialogStockWarning(const unsigned int maxVisibleStockCount, MainMessageLoopWnd* mainWnd, const COLORREF bkColor = GetSysColor(COLOR_BTNFACE));
	typedef std::set<unsigned __int64, lessUIntAsStr<unsigned __int64> > SortedSymbolSet;
	INT_PTR DisplayModal(bool disableOkIfNoneSelected, CWnd* parent, const char* caption, unsigned int flags, COLORREF bkColor = RGB(0, 0, 128), COLORREF textColor = RGB(255, 255, 255), COLORREF captionColor = 0xFFFFFFFF, COLORREF blinkBkColor = 0xFFFFFFFF, COLORREF blinkTextColor = 0xFFFFFFFF, COLORREF blinkCaptionColor = 0xFFFFFFFF, unsigned int focusButton = 0);
	void SetSymbols(const SortedSymbolSet& symbolSet)
	{
		m_symbolsUnselected.clear();
		m_symbolsAll = symbolSet;
		m_symbolsSelected = symbolSet;
	}
	bool AddSymbol(const unsigned __int64& symbol)
	{
//		return m_symbolsAll.insert(symbol).second;
		if(m_symbolsAll.insert(symbol).second)
		{
			m_symbolsSelected.insert(symbol);
			return true;
		}
		return false;
	}
	void Clear()
	{
		m_symbolsSelected.clear();
		m_symbolsUnselected.clear();
	}
	void ClearAll()
	{
		Clear();
		m_symbolsAll.clear();
	}
	bool isSymbolSelected(const unsigned __int64& symbol) const{return m_symbolsSelected.find(symbol) != m_symbolsSelectedEnd;}
	const SortedSymbolSet& GetSymbolsAll() const{return m_symbolsAll;}
	const SortedSymbolSet& GetSymbolsSelected() const{return m_symbolsSelected;}
	const SortedSymbolSet& GetSymbolsUnselected() const{return m_symbolsUnselected;}
protected:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void FillControls();
	virtual INT_PTR PrepareToDisplay(CWnd* parent, const char* caption, unsigned int flags, COLORREF bkColor, COLORREF textColor, COLORREF captionColor, COLORREF blinkBkColor = 0xFFFFFFFF, COLORREF blinkTextColor = 0xFFFFFFFF, COLORREF blinkCaptionColor = 0xFFFFFFFF, unsigned int focusButton = 0, const char* thirdButtonName = nullptr, const char* secondButtonName = nullptr, const char* firstButtonName = nullptr) override;
	virtual void BeforeDestroy() override;
	virtual BOOL OnInitDialog() override;
	virtual void OnOK() override;
	virtual void DoDataExchange(CDataExchange* pDX);
//	virtual void OnCancel();
	afx_msg LRESULT OnListBoxItemChecked(WPARAM w, LPARAM l);
	afx_msg LRESULT OnListBoxItemsChecked(WPARAM w, LPARAM l);
	DECLARE_MESSAGE_MAP()

	bool ListBoxItemsCheckedChanged();

	ListBoxSymbolCheckedSimple m_ListBoxSymbol;

	unsigned int m_maxVisibleStockCount;
	bool m_disableOkIfNoneSelected;

	SortedSymbolSet m_symbolsAll;
	SortedSymbolSet m_symbolsSelected;
	SortedSymbolSet m_symbolsUnselected;
	SortedSymbolSet::const_iterator m_symbolsAllEnd;
	SortedSymbolSet::const_iterator m_symbolsSelectedEnd;
};

class UGUI_API FocusDialog : public TakionDialog
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual bool GetInsideScreen(CRect& rect) const;
	virtual bool isExecuteCommands() const{return m_executeCommands;}
	void SetExecuteCommand(const bool& execute){m_executeCommands = execute;}
	void Display(CWnd* parent, int x, int y, int w, int h, bool show = true);
	const bool& isDisplayed() const{return m_displayed;}
	const bool& isCancelPosted() const{return m_cancelPosted;}
	virtual bool isCloseOnCommandExecution() const{return m_closeOnCommandExecution;}
	void SetCloseOnCommandExecution(const bool& close){m_closeOnCommandExecution = close;}
	bool PretendNotDisplayed() const
	{
		if(m_displayed)
		{
			m_displayed = false;
			return true;
		}
		return false;
	}
	void UnpretendNotDisplayed() const
	{
		m_displayed = true;
	}
	void IncrementIgnoreCancelCount(){++m_ignoreCancelCount;}
	void DecrementIgnoreCancelCount(){if(m_ignoreCancelCount)--m_ignoreCancelCount;}
	void SetIgnoreCancelCount(const unsigned int& count){m_ignoreCancelCount = count;}
	const unsigned int& GetIgnoreCancelCount() const{return m_ignoreCancelCount;}
//	virtual void OnOK();
	virtual void OnCancel() override;
	void SetToDestroyOnFocus(const bool& toDestroyOnFocus){m_toDestroyOnFocus = toDestroyOnFocus;}
	virtual bool isToDestroyOnFocus() const override{return m_toDestroyOnFocus;}
//	virtual bool UpdateFrameBottom(){return false;}
//	virtual bool UpdateFrameRight(){return false;}

	virtual bool CanShow() const{return true;}
/*Used in DialogList
	virtual const void* GetCurrentItem() const{return nullptr;}//Used in DialogList
	virtual bool SetCurrentItem(const void* currentItem, unsigned char resize){return false;}//Used in DialogList
	bool UpdateCurrentItem(const void* const& currentItem, const unsigned char& resize)//1 - resize, 2 - resize and move
	{
		return SetCurrentItem(currentItem, resize);
	}
	virtual void ItemDeleted(unsigned int at){}
	virtual void ItemsCleared(){}
*/
protected:
	FocusDialog(MainMessageLoopWnd* mainWnd, bool draggable, bool toDestroyOnFocus = false, CWnd* parent = nullptr, LPCSTR caption = nullptr, DWORD style = 0, DWORD exstendedStyle = 0, int x = 0, int y = 0, int w = 0, int h = 0,
		LPCSTR font = nullptr, WORD fontSize = 8, bool executeCommands = true, bool closeOnCommandExecution = true):
		TakionDialog(mainWnd, draggable, caption, style, exstendedStyle, x, y, w, h, font, fontSize),
		m_parent(parent),
		m_toDestroyOnFocus(toDestroyOnFocus),
		m_displayed(false),
		m_executeCommands(executeCommands),
		m_closeOnCommandExecution(closeOnCommandExecution),
		m_ignoreCancelCount(0),
		m_cancelPosted(false)
	{}
	FocusDialog(MainMessageLoopWnd* mainWnd, bool draggable, CWnd* parent, unsigned int id, bool toDestroyOnFocus = false, bool executeCommands = true, bool closeOnCommandExecution = true):
		TakionDialog(mainWnd, draggable, parent, id),
		m_parent(parent),
		m_toDestroyOnFocus(toDestroyOnFocus),
		m_displayed(false),
		m_executeCommands(executeCommands),
		m_closeOnCommandExecution(closeOnCommandExecution),
		m_ignoreCancelCount(0),
		m_cancelPosted(false)
	{}
	virtual void BeforeShow(){}
	virtual void FinishDialog(int result);
	virtual void AfterClose();
//	virtual void DoFinishDialog(int result);
	virtual void OnDeactivate(){}
//	afx_msg void OnKillFocus(CWnd* pNewWnd);
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	virtual void DoActivate(UINT state, bool minimized) override;//, CWnd* pWndOther) override;
//	afx_msg LRESULT OnCloseDialog(WPARAM wParam, LPARAM lParam);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	DECLARE_MESSAGE_MAP()
	CWnd* m_parent;
	bool m_toDestroyOnFocus;
	mutable bool m_displayed;
	bool m_executeCommands;
	bool m_closeOnCommandExecution;
	unsigned int m_ignoreCancelCount;
	bool m_cancelPosted;
//private:
//	FocusDialog(TakionMainWnd* mainWnd, CWnd* parent, unsigned int id, bool toDestroyOnFocus = false):DraggableDialog(mainWnd, parent, id){}
};

class UGUI_API DialogList : public FocusDialog
{
public:
	void Display(unsigned int code,
		bool rightButton,
		const void* item,
		CWnd* parent,
		int x, int y, int w, int h,
		const int* exceptTop,//if not nullptr, should be less than y, and the Dialog will try to not cover a horizontal stripe from *exceptTop to y.
		bool fastSelection,
		unsigned int maxVisibleItemCount = 0,
		CWnd* receipient = nullptr,
		COLORREF bkColor = 0xFFFFFFFF,
		COLORREF selectionBkColor = 0xFFFFFFFF,
		COLORREF textColor = 0xFFFFFFFF,
		COLORREF selectionTextColor = 0xFFFFFFFF,
		const char* title = nullptr);
	const void* GetSelectedItem() const;
	const void* GetItemAt(int i) const;
	int GetCurSel() const;
	void ClearList();
	int AddItem(const void* item);
	int InsertItem(int at, const void* item);
	void RemoveItem(const void* item);
	void RemoveItemAt(unsigned int at);
	virtual bool ResetContent();
	bool ResetContentExceptNullItem();
	void SetFont(CFont* font);
	virtual HWND GetFirstTabControl() const override;//{return m_listBox->m_hWnd; }

//	virtual const void* GetCurrentItem() const override{return m_item;}
	const void* GetInitialItem() const{return m_initialItem;}

	const void* GetCurrentItem() const{return m_item;}
//	virtual bool SetCurrentItem(const void* currentItem, unsigned char resize) override
	bool SetCurrentItem(const void* currentItem, unsigned char resize)
	{
		if(currentItem != m_item)
		{
			if(!currentItem || m_listBox->FindItem(currentItem) >= 0)
			{
				BeforeCurrentItemSet(currentItem, resize);
				m_item = currentItem;
				return true;
			}
		}
		return false;
	}
/*
	bool UpdateCurrentItem(const void* const& currentItem, const unsigned char& resize)//1 - resize, 2 - resize and move
	{
		return SetCurrentItem(currentItem, resize);
	}
*/
//	virtual void ItemDeleted(unsigned int at) override{}
//	virtual void ItemsCleared() override{m_item = nullptr;}
	virtual void ItemDeleted(unsigned int at){}
	virtual void ItemsCleared(){m_item = nullptr;}
////
	const unsigned int& GetCode() const{return m_code;}
	const bool& isRightButtonUsed() const{return m_rightButtonUsed;}
	const bool& isCtrlDown() const{return m_ctrlDown;}
	const bool& isCtrlDownSelectionOnly() const{return m_ctrlDownSelectionOnly;}
	const bool& isRButtonSelectionOnly() const{return m_rButtonSelectionOnly;}
	void SetSortable(bool sortable);
	virtual bool NullItemOk() const{return false;}
	virtual bool hasAddButton() const{return false;}
	virtual bool GetInsideScreen(CRect& rect) const;
	void SetSelectionBkColor(COLORREF color);
//	unsigned int GetItemCount() const{return (unsigned int)m_listBox->GetCount();}
	const int& GetListBoxItemHeight() const{return m_listBox->GetMyItemHeight();}
	const unsigned int& GetItemCount() const{return (unsigned int)m_listBox->GetItemCount();}
	int FindItem(const void* item) const{return m_listBox->FindItem(item);}
	int FindItemIndexByName(const char* name) const{return m_listBox->FindItemByName(name);}
	void* FindItemByName(const char* name) const
	{
		int found = FindItemIndexByName(name);
		return found >= 0 ? m_listBox->GetItemDataPtr(found) : nullptr;
	}

//	const int& GetSelectedOrdinal() const{return m_selectedOrdinal;}

	enum DialogListIds : unsigned int
	{
		choiceListBoxId = BaseButtonIDsLast,//1000,//IDL_CHOOSE,//2005,//1000,//IDL_CHOOSE,//1000,
		choiceTitleId,

		dialogListIdsEnd,
	};
	static const int staticHeight = 8;
	static const int editHeight = 12;

	virtual bool UpdateFrameBottom() override;
//	virtual bool UpdateFrameRight() override
	virtual int CalculateItemWidth(const void* item);
	int GetListBoxItemWidth() const{return m_listBox->GetMaxWidth();}
	int GetMaxWidth() const{return GetListBoxItemWidth() + m_extraWidth;}
	bool isRadio() const{return m_listBox->isRadio();}
	void SetRadio(bool radio){m_listBox->SetRadio(radio);}
protected:
//	DialogList(MainMessageLoopWnd* mainWnd, CWnd* parent, unsigned int id, ListBoxOwnerDraw* lb, unsigned int maxVisibleItemCount);
	DialogList(MainMessageLoopWnd* mainWnd,
		CWnd* parent,
		ListBoxOwnerDraw* lb,
		unsigned int maxVisibleItemCount,
		bool sort,
		int listBoxTopOffset = -1,
		bool ctrlDownSelectionOnly = true,
		bool rButtonSelectionOnly = false,
		const char* title = nullptr,
		DWORD style = WS_BORDER | WS_POPUP | WS_CLIPCHILDREN,
		bool toDestroyOnFocus = false);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void Resize(bool widthChanged = true, bool heightChanged = true) override;

	virtual void FinishDialog(int result) override;
//	virtual void PropagateSelchangeItem(){}
	virtual void BeforeDestroy() override;
	virtual void BeforeShow() override;

	virtual void ExistingItemAttemptedToAdd(const void* item)
	{
		m_listBox->DestroyItem(item);
	}

	virtual void ToolTipsEnabled(bool enable) override;

//	virtual void OnDisplay(){}
	virtual void EnableAddButton(bool enable){}
	virtual void DoDataExchange(CDataExchange* pDX);

	virtual void BeforeItemDeleted(const void* item){}
	afx_msg void OnEnterMenuLoop(BOOL bIsTrackPopupMenu);
    afx_msg void OnExitMenuLoop(BOOL bIsTrackPopupMenu);
	afx_msg void OnDblclkItem();
	afx_msg void OnSelchangeItem();
	afx_msg LRESULT OnRSelChange(WPARAM ctrlId, LPARAM itemNumber);
	afx_msg LRESULT OnRSelConfirm(WPARAM ctrlId, LPARAM itemNumber);
	DECLARE_MESSAGE_MAP()

	virtual void ItemSelected();
	virtual void ItemDoubleClicked();//Just calls OnOK

	virtual void ItemSelectedWithRightClick(unsigned int itemOrdinal){}

	virtual void BeforeCurrentItemSet(const void* currentItem, unsigned char resize){}

	void MeasureTitle();
	void ResetTitleText();

	CWnd* m_dialogOwner;
	HWND m_titleHwnd;
	ListBoxOwnerDraw* m_listBox;
	const void* m_item;
	const void* m_initialItem;
	unsigned int m_maxVisibleItemCount;
	void InitPoint(CWnd* wnd, CRect& rect, int& bottomOffset);
	std::string m_titleText;
	int m_titleHeight;
	int m_titleWidth;
	int m_lbTop;
	int m_lbBottom;
	int m_listBoxBorder;
	bool m_offsetsInitialized;
	bool m_fastSelection;
	bool m_rightButtonUsed;

	bool m_rButtonSelectionOnly;

	bool m_ctrlDown;
	bool m_ctrlDownSelectionOnly;

	bool m_locationBottomBased;

//	int m_selectedOrdinal;
//	CFont* m_fontBold;
	unsigned int m_code;
	CRect m_displayRect;

	int m_extraWidth;//GetSystemMetrics(SM_CXVSCROLL) + (GetSystemMetrics(SM_CXEDGE) + GetSystemMetrics(SM_CXBORDER)) * 2
};

class UGUI_API DialogListFitString : public DialogList
{
friend class ListBoxFitString;
public:
	DialogListFitString(MainMessageLoopWnd* mainWnd,
		CWnd* parent,
		unsigned int maxVisibleItemtCount,
		bool sort = true,
		bool toDestroyOnFocus = false,
		bool owner = false,
		bool sortCaseInsensitive = false,
		bool rButtonSelection = true,
		bool rbuttonMenu = true,
		bool useBoldFont = true);//, bool sortAlphabetically);//, bool ownItems);// = 0, CWnd* receipient = nullptr);
	const char* GetStringAt(int i) const;
	const char* GetSelectedString() const;
	void Display(unsigned int code,
		bool rightButton,
//		bool sortAlphabetically,
		const void* item,
		CWnd* parent,
		int x,
		int y,
		int w,
		int h,
		const int* exceptTop,//if not nullptr, should be less than y, and the Dialog will try to not cover a horizontal stripe from *exceptTop to y.
		bool fastSelection,
		unsigned int maxVisibleItemCount = 0,
		CWnd* receipient = nullptr,
		COLORREF bkColor = 0xFFFFFFFF,
		COLORREF selectionBkColor = 0xFFFFFFFF,
		COLORREF textColor = 0xFFFFFFFF,
		COLORREF selectionTextColor = 0xFFFFFFFF);

//	int GetListBoxItemWidth() const{return m_ListBoxFitString.GetMaxWidth();}
//	const bool& isSortAlphabetically() const{return m_sortAlphabetically;}
//	void SetSortAlphabetically(const bool& sortAlphabetically){m_sortAlphabetically = sortAlphabetically;}
	virtual bool UpdateFrameRight() override;
	virtual void ItemDeleted(unsigned int at) override
	{
		if((unsigned int)m_ListBoxFitString.GetItemBold() == at)
		{
			m_item = nullptr;
			m_ListBoxFitString.SetItemBold(-1);
		}
	}
	virtual bool CanShow() const override{return m_ListBoxFitString.GetItemCount() > 0;}
	void SetOwner(const bool& owner){m_ListBoxFitString.SetOwner(owner);}
	const bool& isOwner() const{return m_ListBoxFitString.isOwner();}
	virtual int CompareListBoxItems(const void* item1, const void* item2) const;
	const bool& isSortCaseInsensitive() const{return m_sortCaseInsensitive;}
	void SetSortCaseInsensitive(bool sortCaseInsensitive);
	virtual bool HasItemToolTips() const{return true;}
protected:
	virtual BOOL OnInitDialog();
	virtual void BeforeShow() override;
	virtual void FinishDialog(int result) override;
	virtual void Resize(bool widthChanged = true, bool heightChanged = true) override;

	virtual void AddListBoxMenuItems(CMenu& menu);
	virtual bool DrawListBoxMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual bool MeasureListBoxMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual bool ExecuteListBoxCommand(WPARAM wParam, LPARAM lParam);

	virtual void SortCaseInsensitiveSet(){}

	void ReSortStrings();

	virtual void FillStrings(){}

	virtual void BeforeCurrentItemSet(const void* itemToBeCurrent, unsigned char resize) override;
//	virtual void OnDisplay();
	ListBoxFitString m_ListBoxFitString;
//	bool m_sortAlphabetically;
//	afx_msg void OnSelchangeItem();
//	DECLARE_MESSAGE_MAP()
	bool m_sortCaseInsensitive;
};

class UGUI_API DialogListInfo : public DialogListFitString
{
protected:
	DialogListInfo(MainMessageLoopWnd* mainWnd,
		CWnd* parent,
		unsigned int maxVisibleItemtCount,
		bool sort = true,
		bool toDestroyOnFocus = false,
		bool sortCaseInsensitive = false,
		bool rButtonSelection = true,
		bool rbuttonMenu = true,
		bool useBoldFont = true);//, bool sortAlphabetically);//, bool ownItems);// = 0, CWnd* receipient = nullptr);
	virtual BOOL OnInitDialog();
//	virtual void FillStrings() override;
};

class UGUI_API DialogListDLL : public DialogListInfo
{
public:
	DialogListDLL(MainMessageLoopWnd* mainWnd,
		CWnd* parent,
		unsigned int maxVisibleItemtCount,
		bool sort = true,
		bool toDestroyOnFocus = false,
		bool sortCaseInsensitive = true,
		bool sortByFileName = false);//, bool sortAlphabetically);//, bool ownItems);// = 0, CWnd* receipient = nullptr);
/*
	void Display(unsigned int code,
		bool rightButton,
		bool sortAlphabetically,
		const void* item,
		CWnd* parent,
		int x,
		int y,
		int w,
		int h,
		bool fastSelection,
		unsigned int maxVisibleItemCount = 0,
		CWnd* receipient = nullptr,
		COLORREF bkColor = 0xFFFFFFFF,
		COLORREF selectionBkColor = 0xFFFFFFFF,
		COLORREF textColor = 0xFFFFFFFF,
		COLORREF selectionTextColor = 0xFFFFFFFF);
*/
//	virtual bool CanShow() const override{return m_ListBoxFitString.GetItemCount() > 0;}
	virtual int CompareListBoxItems(const void* item1, const void* item2) const override;
	const bool& isSortByFileName() const{return m_sortByFileName;}
	void SetSortByFileName(bool sortByFileName);
	virtual bool HasItemToolTips() const{return false;}
protected:
//	virtual BOOL OnInitDialog();
	virtual void AddListBoxMenuItems(CMenu& menu) override;
	virtual bool DrawListBoxMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
	virtual bool MeasureListBoxMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) override;
	virtual bool ExecuteListBoxCommand(WPARAM wParam, LPARAM lParam) override;

	virtual void SortCaseInsensitiveSet() override;

	virtual void FillStrings() override;
	bool m_sortByFileName;
};

class UGUI_API DialogListOkCancel : public DialogList
{
public:
/*
	enum DialogListOkCancelIds
	{
		buttonAddId = dialogListIdsEnd,
		buttonRemoveId,

		dialogChooseIdsEnd,
	};
*/
	static const int smallWidth = 26;
	static const int bigWidth = 33;
	static const int hOffset = 1;
	virtual bool isOkButtonEnabled() const{return m_listBox->GetCurSel() >= 0;}
	void EnableOkButton();
	void InvalidateOkButton() const{if(m_ButtonOK.m_hWnd)::InvalidateRect(m_ButtonOK.m_hWnd, nullptr, TRUE);}
	void InvalidateCancelButton() const{if(m_ButtonCancel.m_hWnd)::InvalidateRect(m_ButtonCancel.m_hWnd, nullptr, TRUE);}
protected:
	DialogListOkCancel(MainMessageLoopWnd* mainWnd,
		CWnd* parent,
		ListBoxOwnerDraw* lb,
		int xOk, int yOk, int wOk, int xCancel, int yCancel, int wCancel,
		unsigned int maxVisibleItemtCount,
		bool sort,
		int listBoxTopOffset = 0,
		bool ctrlDownSelectionOnly = true,
		bool rButtonSelectionOnly = false,
		const char* title = nullptr,
		DWORD style = WS_BORDER | WS_POPUP | WS_CLIPCHILDREN,
		unsigned int additionalButtonRowCount = 0);
	virtual BOOL OnInitDialog();
	virtual void Resize(bool widthChanged = true, bool heightChanged = true) override;
//	virtual void FinishDialog(int result);
//	virtual void PropagateSelchangeItem(){}
	virtual void BeforeShow() override;
//	virtual void AfterClose() override;
//	virtual void EnableAddButton(bool enable);
	virtual void DoDataExchange(CDataExchange* pDX) override;

	virtual void BeforeDestroy() override;

	virtual void OkButtonEnabled(bool enabled){}


//	afx_msg void OnSelchangeItem();
//	afx_msg LRESULT OnRSelChange(WPARAM ctrlId, LPARAM itemNumber);
//	afx_msg void OnAdd();
//	afx_msg void OnRemove();
//	DECLARE_MESSAGE_MAP()

	CButton m_ButtonOK;
	CButton m_ButtonCancel;

	CRect m_rectOk;
	CRect m_rectCancel;

//	int m_bottomOffsetOk;
//	int m_bottomOffsetCancel;

	int m_okCancelButtonWidth;

	unsigned int m_additionalButtonRowCount;
};

class UGUI_API DialogListEditOkCancel : public DialogListOkCancel
{
public:

	enum DialogListEditOkCancelIds : unsigned int
	{
		editId = dialogListIdsEnd,

		dialogListEditOkCancelIdsEnd,
	};
	virtual HWND GetFirstTabControl() const override{return m_Edit.m_hWnd;}
//	virtual void GetItemTextToPopulateEdit(const void* item, std::string& itemStr) const;
	virtual bool isOkButtonEnabled() const override;
	const std::string& GetEditText() const{return m_editText;}
//	void InvalidateEdit() const{if(m_Edit.m_hWnd)::InvalidateRect(m_Edit.m_hWnd, nullptr, TRUE);}
	void InvalidateEdit() const{m_Edit.InvalidateRectIfValid(nullptr);}
protected:
	DialogListEditOkCancel(MainMessageLoopWnd* mainWnd,
		CWnd* parent,
		ListBoxOwnerDraw* lb,
		int xOk, int yOk, int wOk, int xCancel, int yCancel, int wCancel,
		unsigned int maxVisibleItemtCount,
		bool sort,
		int listBoxTopOffset = 0,
		bool ctrlDownSelectionOnly = true,
		bool rButtonSelectionOnly = false,
		DWORD caseStype = 0,
		const char* title = nullptr,
		DWORD style = WS_BORDER | WS_POPUP | WS_CLIPCHILDREN,
		unsigned int additionalButtonRowCount = 0);
	virtual BOOL OnInitDialog();
	virtual void Resize(bool widthChanged = true, bool heightChanged = true);
//	virtual void FinishDialog(int result);
//	virtual void PropagateSelchangeItem(){}
	virtual void BeforeShow() override;
//	virtual void AfterClose() override;
//	virtual void EnableAddButton(bool enable);
	virtual void DoDataExchange(CDataExchange* pDX);

	virtual void BeforeDestroy() override;
	virtual void ItemSelected() override;
	virtual void ItemSelectedWithRightClick(unsigned int itemOrdinal) override;

	virtual void ToolTipsEnabled(bool enable) override;

//	afx_msg void OnSelchangeItem();
//	afx_msg LRESULT OnRSelChange(WPARAM ctrlId, LPARAM itemNumber);
	afx_msg void OnEditChange();
//	afx_msg void OnAdd();
//	afx_msg void OnRemove();
	DECLARE_MESSAGE_MAP()

	ValidEdit m_Edit;

	int m_editHeight;

	std::string m_editText;

//	int m_bottomOffsetEdit;
};

class UGUI_API DialogChoose : public DialogListOkCancel
{
public:
	void Display(bool rightButton,
		const void* item,
		bool toolTipsEnabled,
		const CWnd* ownerControl,
		CWnd* parent,
		int x,
		int y,
		int w,
		int h,
		const int* exceptTop,//if not nullptr, should be less than y, and the Dialog will try to not cover a horizontal stripe from *exceptTop to y.
		bool fastSelection);
//	void* GetCurrentSelection() const;
	virtual bool hasAddButton() const{return true;}
	virtual int AddItemByName(const void* item);
//	virtual int CalculateItemWidth(const void* item);
	enum DialogChooseIds : unsigned int
	{
		buttonAddId = dialogListIdsEnd,
		buttonRemoveId,

		dialogChooseIdsEnd,
	};
	const bool& isModified() const{return m_modified;}
	virtual bool isTooltipConfigValid() const{return true;}//m_configBase != nullptr;}
	virtual bool isToolTipsEnabled() const override{return m_chooseTooltipsEnabled;}
	virtual void FillListBoxFromMap(){}
protected:
//	DialogChoose(MapIniValue& mapIniValue, TakionMainWnd* mainWnd, CWnd* parent, unsigned int id, ListBoxOwnerDraw* lb, unsigned int maxVisibleItemtCount);
	DialogChoose(MapIniValue& mapIniValue, MainMessageLoopWnd* mainWnd, CWnd* parent, ListBoxOwnerDraw* lb, unsigned int maxVisibleItemtCount, bool sort);
	virtual BOOL OnInitDialog();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void Resize(bool widthChanged = true, bool heightChanged = true);
	virtual void FinishDialog(int result);
	virtual void PropagateSelchangeItem(){}
	virtual void BeforeShow() override;
	virtual void AfterClose() override;
	virtual void ItemSelected() override;
	virtual void ItemSelectedWithRightClick(unsigned int itemOrdinal) override;

//	virtual void OnDisplay(){}
	virtual void EnableAddButton(bool enable);
	virtual void DoDataExchange(CDataExchange* pDX);

	virtual void BeforeDestroy() override;

//	afx_msg void OnSelchangeItem();
//	afx_msg LRESULT OnRSelChange(WPARAM ctrlId, LPARAM itemNumber);
//	afx_msg void OnDblclkItem();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	DECLARE_MESSAGE_MAP()

//	CButton m_ButtonOK;
//	CButton m_ButtonCancel;
	CButton m_ButtonAdd;
	CButton m_ButtonRemove;

//	CRect m_rectOk;
//	CRect m_rectCancel;
	CRect m_rectAdd;
	CRect m_rectRemove;

//	int m_bottomOffsetOk;
//	int m_bottomOffsetCancel;
	int m_bottomOffsetAdd;
	int m_bottomOffsetRemove;

	MapIniValue& m_mapIniValue;
	bool m_modified;

	bool m_chooseTooltipsEnabled;

	const CWnd* m_ownerControl;
	bool m_ownerControlHasFocus;

	virtual void OnCancel() override;
	bool m_chooseFinished;
};

class UGUI_API DialogChooseName : public DialogChoose
{
public:
	DialogChooseName(MapIniValue& mapIniValue, MainMessageLoopWnd* mainWnd, CWnd* parent, bool wide = false);
	void Display(bool rightButton,
		const void* item,
		bool toolTipsEnabled,
		const CWnd* ownerControl,
		CWnd* parent,
		int x,
		int y,
		int w,
		int h,
		const int* exceptTop,//if not nullptr, should be less than y, and the Dialog will try to not cover a horizontal stripe from *exceptTop to y.
		bool fastSelection);
	virtual void FillListBoxFromMap() override;
protected:
	virtual BOOL OnInitDialog();
	virtual void BeforeShow() override;
	virtual void Resize(bool widthChanged = true, bool heightChanged = true) override;
	virtual void BeforeDestroy() override;
//	virtual void OnDisplay();
	ListBoxStringBold m_ListBoxName;
	int m_frameWidth;
	bool m_wide;
};

class UGUI_API DialogChooseConnectionBase : public DialogChoose
{
public:
	DialogChooseConnectionBase(MapIniValue& mapIniValue, MainMessageLoopWnd* mainWnd, CWnd* parent);
	enum DialogChooseConnectionIds : unsigned int
	{
		editMemoId = dialogChooseIdsEnd,
		buttonMemoId,

		dialogChooseConnectionIdsEnd,
	};
	virtual void GetConnectionState(unsigned int ip, unsigned short port, bool& connected, bool& connecting) const{connected = connecting = false;}
	bool AddConnection(unsigned int ip, unsigned short port, const char* dns, const char* memo, const char* name, unsigned char dataType);
	void UpdateConnectionStatus();
//	const bool& isMemoModified() const{return m_memoModified;}
	virtual void FillListBoxFromMap() override;
protected:
//	virtual void OnOK() override;
	virtual BOOL OnInitDialog() override;
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void Resize(bool widthChanged, bool heightChanged) override;
	virtual void PropagateSelchangeItem() override;
	virtual void BeforeShow() override;
	virtual void BeforeDestroy() override;
	virtual void AfterClose() override;
	afx_msg void OnMemo();
	DECLARE_MESSAGE_MAP()

	void EnableMemoButton();

	EditNoContext m_EditMemo;
	CButton m_ButtonMemo;
	ListBoxConnection m_ListBoxConnection;

//	CPoint m_pointMemoEdit;
//	CPoint m_pointMemo;

	CRect m_rectMemoEdit;
	CRect m_rectMemo;
	int m_bottomOffsetMemoEdit;
	int m_bottomOffsetMemo;

	bool m_memoModified;
};

class UGUI_API DialogChooseFile : public DialogChoose
{
public:
	DialogChooseFile(MapIniValue& mapIniValue, MainMessageLoopWnd* mainWnd, CWnd* parent);
	void Display(bool rightButton,
		const char* filePath,
		const char* fileExtension,
		const void* item,
		bool toolTipsEnabled,
		const CWnd* ownerControl,
		CWnd* parent,
		int x,
		int y,
		int w,
		int h,
		const int* exceptTop,//if not nullptr, should be less than y, and the Dialog will try to not cover a horizontal stripe from *exceptTop to y.
		bool fastSelection);
	virtual int AddItemByName(const void* item) override;
	int AddFile(const char* itemStr);
protected:
	virtual BOOL OnInitDialog();
	virtual void FinishDialog(int result) override;
	virtual void BeforeShow() override;
	virtual void BeforeItemDeleted(const void* item) override;
	virtual void Resize(bool widthChanged, bool heightChanged) override;
//	virtual void OnDisplay();
	ListBoxFile m_ListBoxFile;
	std::string m_filePath;
	std::string m_fileExtension;
	std::string m_filePathWild;
	unsigned int m_fileExtensionLen;
	int m_maxWidth;
	int m_maxDateWidth;
	int m_maxTimeWidth;
};

class UGUI_API DialogTimeList : public DialogListOkCancel
{
public:
	DialogTimeList(MapIniValue& mapIniValue, unsigned int maxTimeValue, MainMessageLoopWnd* mainWnd, CWnd* parent);//, unsigned int id);//, ListBoxOwnerDraw* lb, unsigned int maxVisibleItemtCount);
	void Display(bool rightButton,
		void* item,
		bool relevant,
		CWnd* parent,
		int x,
		int y,
		int w,
		int h,
		const int* exceptTop,//if not nullptr, should be less than y, and the Dialog will try to not cover a horizontal stripe from *exceptTop to y.
		bool fastSelection);
	virtual bool hasAddButton() const{return true;}
	typedef std::set<unsigned int> UIntSet;
	bool GetTimeSet(UIntSet& timeSet) const;
	void SelectValue(unsigned int selVal);
	unsigned int GetSelectedValue() const;
	unsigned int GetMaxTimeValue() const{return m_SpinTime.GetMaxValue();}
	unsigned int GetMaxSecond() const{return m_maxSecond;}
	void UpdateMapIniValue();
	const UIntSet& GetInitialSet() const{return m_initialSet;}
	const UIntSet& GetCurrentSet() const{return m_currentSet;}
	unsigned int GetCurrentSetCount() const{return (unsigned int)m_currentSet.size();}
	void Setup(){Read();m_initialSet = m_currentSet;}
	enum DialogChooseIds : unsigned int
	{
		buttonAddId = dialogListIdsEnd,
		buttonRemoveId,
		buttonFindId,
		buttonClearId,
		buttonResetId,
		buttonReadId,

		spinTimeId,

		dialogChooseIdsEnd,
	};
	virtual bool isOkButtonEnabled() const override;
protected:
	virtual BOOL OnInitDialog();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void BeforeDestroy() override;
	virtual void Resize(bool widthChanged = true, bool heightChanged = true) override;
	virtual void FinishDialog(int result) override;
	virtual void ItemSelected() override;
	virtual void ItemDoubleClicked() override;
	virtual void BeforeShow() override;
	virtual void EnableAddButton(bool enable) override;
	virtual void DoDataExchange(CDataExchange* pDX) override;
	virtual void Apply() override;

//	afx_msg void OnSelchangeItem();
//	afx_msg void OnDblclkItem();
	afx_msg LRESULT OnSpinChange(WPARAM w, LPARAM l);
	afx_msg void OnAdd();
	afx_msg void OnFind();
	afx_msg void OnRemove();
	afx_msg void OnReset();
	afx_msg void OnRead();
	afx_msg void OnClear();
	DECLARE_MESSAGE_MAP()

	ListBoxTime m_ListBoxTime;
	TimeSpin m_SpinTime;//(bool milliseconds, unsigned int maxValue, const unsigned int& minValue = 0, const unsigned int& value = 0, const unsigned int& maxSpinRate = 1000, int borderWidth = 1, bool processCtrlChars = true, bool processDigits = true):
//	CButton m_ButtonOK;
//	CButton m_ButtonCancel;
	CButton m_ButtonAdd;
	CButton m_ButtonFind;
	CButton m_ButtonRemove;
	CButton m_ButtonReset;
	CButton m_ButtonRead;
	CButton m_ButtonClear;

	CRect m_rectListBox;
	CRect m_rectSpin;
//	CRect m_rectOk;
//	CRect m_rectCancel;
	CRect m_rectAdd;
	CRect m_rectFind;
	CRect m_rectRemove;
	CRect m_rectReset;
	CRect m_rectRead;
	CRect m_rectClear;
/*
	CPoint m_pointOk;
	CPoint m_pointCancel;
	CPoint m_pointAdd;
	CPoint m_pointRemove;
*/
	MapIniValue& m_mapIniValue;
	bool m_modified;
	bool Read();
	void FillListBox();

	void UpdateButtonEnableStatus();
	void UpdateAddButtonEnableStatus();

	unsigned int m_currentSecond;
	unsigned int m_maxSecond;
	UIntSet m_initialSet;
	UIntSet m_currentSet;
	UIntSet::const_iterator m_currentSetEnd;
};

class UGUI_API DialogListFile : public DialogList
{
public:
	DialogListFile(MainMessageLoopWnd* mainWnd, CWnd* parent, unsigned int maxVisibleItemtCount);//, bool ownItems);// = 0, CWnd* receipient = nullptr);
	const FileItem* GetFileAt(int i) const;
	const FileItem* GetSelectedFile() const;
	void Display(unsigned int code,
		bool rightButton,
		const char* filePath,
		const char* fileExtension,
		bool sortByTime,
		const void* item,
		CWnd* parent,
		int x, int y, int w, int h,
		const int* exceptTop,//if not nullptr, should be less than y, and the Dialog will try to not cover a horizontal stripe from *exceptTop to y.
		bool fastSelection,
		unsigned int maxVisibleItemCount = 0,
		CWnd* receipient = nullptr,
		COLORREF bkColor = 0xFFFFFFFF,
		COLORREF selectionBkColor = 0xFFFFFFFF,
		COLORREF textColor = 0xFFFFFFFF,
		COLORREF selectionTextColor = 0xFFFFFFFF);
//	void SetFile(const std::string* fileName);
//	const std::string* GetDestination() const{return m_destination;}
	void* FindItemByName(const char* name) const;
	const bool& isSortByTime() const{return m_sortByTime;}
	void SetSortByTime(const bool& sortByTime)
	{
		if(sortByTime != m_sortByTime)
		{
			m_sortByTime = sortByTime;
			m_ListBoxFile.SetSortByTime(m_sortByTime);
		}
	}
protected:
//	virtual BOOL OnInitDialog();
	virtual void FinishDialog(int result);
	virtual void BeforeShow();
	ListBoxFile m_ListBoxFile;
	std::string m_filePath;
	std::string m_fileExtension;
	bool m_sortByTime;
};

class UGUI_API DialogListString : public DialogList
{
public:
	DialogListString(MainMessageLoopWnd* mainWnd, CWnd* parent, unsigned int maxVisibleItemCount, bool ownItems, bool adjustWidth = true);// = 0, CWnd* receipient = nullptr);
	const char* GetStringAt(int i) const;
	const char* GetSelectedString() const;
//	void Display(unsigned int code, const void* item, CWnd* parent, int x, int y, int w, int h, bool fastSelection, unsigned int maxVisibleItemCount = 0, CWnd* receipient = nullptr, COLORREF bkColor = 0xFFFFFFFF, COLORREF selectionBkColor = 0xFFFFFFFF, COLORREF textColor = 0xFFFFFFFF, COLORREF selectionTextColor = 0xFFFFFFFF);
protected:
//	virtual BOOL OnInitDialog();
	virtual void BeforeShow();
//	virtual void OnDisplay();
	ListBoxStringBold m_ListBoxString;
	bool m_adjustWidth;
//	afx_msg void OnSelchangeItem();
//	DECLARE_MESSAGE_MAP()
};

class UGUI_API DialogListChar : public DialogList
{
public:
	DialogListChar(MainMessageLoopWnd* mainWnd, CWnd* parent, unsigned int maxVisibleItemCount, bool adjustWidth = true);// = 0, CWnd* receipient = nullptr);
	char GetCharAt(int i) const;
	char GetSelectedChar() const;
//	void Display(unsigned int code, const void* item, CWnd* parent, int x, int y, int w, int h, bool fastSelection, unsigned int maxVisibleItemCount = 0, CWnd* receipient = nullptr, COLORREF bkColor = 0xFFFFFFFF, COLORREF selectionBkColor = 0xFFFFFFFF, COLORREF textColor = 0xFFFFFFFF, COLORREF selectionTextColor = 0xFFFFFFFF);
	void FillAllChars(bool replace = true){m_ListBoxChar.FillCharRange(33, 126, replace);}
	void FillAlphabet(bool replace = true){m_ListBoxChar.FillCharRange('A', 'Z', replace);}
	void FillDigits(bool replace = true){m_ListBoxChar.FillCharRange('0', '9', replace);}
protected:
//	virtual BOOL OnInitDialog();
	virtual void BeforeShow();
//	ListBoxCharBold m_ListBoxChar;
	ListBoxChar m_ListBoxChar;
	bool m_adjustWidth;
};

class UGUI_API ListBoxUIntDerivedBold : public ListBoxBoldItem
{
public:
	virtual int Compare(const void* item1, const void* item2) const override
	{
		const unsigned int n1 = (unsigned int)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			item1;
		const unsigned int n2 = (unsigned int)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			item2;
		return n1 < n2 ? -1 : n1 > n2 ? 1 : 0;
	}

	int FindItemByUInt(const unsigned int& uintItem) const
	{
		const unsigned int count = m_itemCount;//GetCount();
		if(count == 0)
		{
			return -1;
		}

		if((GetStyle() & LBS_SORT) == 0 || m_doNotSort)//unsorted
		{
			for(unsigned int i = 0; i < count; ++i)
			{
				if(uintItem == (unsigned int)
#if(_MSC_VER > 1600)
					(size_t)
#endif
					GetItemDataPtr(i))
				{
					return (int)i;
				}
			}
		}
		else
		{
			int low = 0;
			int high = count - 1;
			int middle;
			unsigned int value;
			while(high >= low)
			{
				middle = (low + high) >> 1;
				value = (unsigned int)
#if(_MSC_VER > 1600)
					(size_t)
#endif
					GetItemDataPtr(middle);
				if(uintItem < value)
				{
					high = middle - 1;
				}
				else if(uintItem > value)
				{
					low = middle + 1;
				}
				else
				{
					if(middle > 0)
					{
						for(--middle; middle >= 0; --middle)
						{
							if(uintItem != (unsigned int)
#if(_MSC_VER > 1600)
								(size_t)
#endif
								GetItemDataPtr(middle))
							{
								break;
							}
						}
						return middle + 1;
					}
					return middle;
				}
			}
		}
		return -1;
	}

	virtual const char* GetItemNameByUInt(const unsigned int uintItem) const = 0;

	virtual const char* GetItemName(const void* item) const override
	{
		return GetItemNameByUInt((unsigned int)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			item);
	}
protected:
	ListBoxUIntDerivedBold(const int& itemHeight = 0, const bool& rbuttonSelection = false, const bool& rbuttonMenu = false, const bool& draggable = false, const bool& useBoldFont = true, const char* const& tooltipText = nullptr):
		ListBoxBoldItem(itemHeight, rbuttonSelection, rbuttonMenu, draggable, useBoldFont, tooltipText)
	{
	}
};


class UGUI_API ListBoxDate : public ListBoxUIntDerivedBold
{
public:
	ListBoxDate(const int& itemHeight = 0, const bool& rbuttonSelection = false, const bool& rbuttonMenu = false, const bool& draggable = false, const bool& useBoldFont = true, const char* const& tooltipText = nullptr, const bool& showDayOfWeek = false):
		ListBoxUIntDerivedBold(itemHeight, rbuttonSelection, rbuttonMenu, draggable, useBoldFont, tooltipText),
		m_showDayOfWeek(showDayOfWeek)
	{
		m_num[sizeof(m_num) - 1] = '\0';
		if(!showDayOfWeek)m_num[8] = '\0';
	}

	inline static void AppendTwoDigits(char*& cursor, unsigned char number)
	{
		unsigned char digit = number / 10;
		*cursor = '0' + digit;
		*++cursor = '0' + (number - digit * 10);
	}

	virtual const char* GetItemNameByUInt(const unsigned int date) const override
	{
		const unsigned char month = (unsigned char)((date >> 8) & 0xFF);
		const unsigned char day = (unsigned char)(date & 0xFF);
		const unsigned char year = (unsigned char)((date >> 16) & 0xFF);
		char* cursor = m_num;
		AppendTwoDigits(cursor, month);
		*++cursor = '/';
		AppendTwoDigits(++cursor, day);
		*++cursor = '/';
		AppendTwoDigits(++cursor, year);

		if(m_showDayOfWeek)
		{
			*++cursor = ' ';
			++cursor;
			const char* dayOfWeek = TL_GetDayOfWeekShortName((unsigned char)TL_GetDayOfWeek(2000 + year, month, day));
			char c = *dayOfWeek;
			for(unsigned char i = 0; i < 3 && c; ++i, ++cursor, c = *++dayOfWeek)
			{
				*cursor = c;
			}
		}

		return m_num;
	}
	const bool& isShowDayOfWeek() const{return m_showDayOfWeek;}
	void SetShowDayOfWeek(const bool& showDayOfWeek)
	{
		if(showDayOfWeek != m_showDayOfWeek)
		{
			m_showDayOfWeek = showDayOfWeek;
			if(!showDayOfWeek)m_num[8] = '\0';
			InvalidateRectIfValid(nullptr);
//			if(m_hWnd)::InvalidateRect(m_hWnd, nullptr, FALSE);
		}
	}
protected:
	mutable char m_num[13];
	bool m_showDayOfWeek;
};

class UGUI_API ListBoxPrice : public ListBoxUIntDerivedBold
{
public:
	ListBoxPrice(const int& itemHeight = 0, const bool& rbuttonSelection = false, const bool& rbuttonMenu = false, const bool& draggable = false, const bool& useBoldFont = true, const char* const& tooltipText = nullptr) :
		ListBoxUIntDerivedBold(itemHeight, rbuttonSelection, rbuttonMenu, draggable, useBoldFont, tooltipText)
	{}
	virtual const char* GetItemNameByUInt(const unsigned int compactPrice) const override
	{
		m_priceStr.clear();
		U_PriceToStr(m_priceStr, Price(compactPrice), 2, -1, true);
		return m_priceStr.c_str();
	}
protected:
	mutable std::string m_priceStr;
};


class UGUI_API DialogListUIntDerived : public DialogList
{
public:
	unsigned int GetUIntAt(int i) const
	{
		return (unsigned int)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			GetItemAt(i);
	}
	unsigned int GetSelectedUInt() const
	{
		return (unsigned int)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			GetSelectedItem();
	}
	void Display(const unsigned int& code,
		bool rightButton,
		const unsigned int& number,
		CWnd* const& parent,
		const int& x,
		const int& y,
		const int& w,
		const int& h,
		const int* exceptTop,//if not nullptr, should be less than y, and the Dialog will try to not cover a horizontal stripe from *exceptTop to y.
		const bool& fastSelection,
		const unsigned int& maxVisibleItemCount = 0,
		CWnd* const& receipient = nullptr,
		const COLORREF& bkColor = 0xFFFFFFFF,
		const COLORREF& selectionBkColor = 0xFFFFFFFF,
		const COLORREF& textColor = 0xFFFFFFFF,
		const COLORREF& selectionTextColor = 0xFFFFFFFF)
	{
		const void* item = (const void*)
#if(_MSC_VER > 1600)
			(size_t)
#endif
			number;
		DialogList::Display(code,
			rightButton,
			item,
			parent,
			x,
			y,
			w,
			h,
			exceptTop,
			fastSelection,
			maxVisibleItemCount,
			receipient,
			bkColor,
			selectionBkColor,
			textColor,
			selectionTextColor);
	}
	void* FindItemByUInt(const unsigned int& date) const
	{
		const int found = m_listBoxDerivedBold->FindItemByUInt(date);
		return found >= 0 ? m_listBoxDerivedBold->GetItemDataPtr(found) : nullptr;
	}
protected:
	DialogListUIntDerived(MainMessageLoopWnd* const& mainWnd, CWnd* const& parent, ListBoxUIntDerivedBold* const& listBoxDerivedBold, const unsigned int& maxVisibleItemtCount)://, bool ownItems);// = 0, CWnd* receipient = nullptr);
		DialogList(mainWnd, parent, listBoxDerivedBold, maxVisibleItemtCount, true),
		m_listBoxDerivedBold(listBoxDerivedBold)
	{
	}
/*
	virtual void ToolTipsEnabled(bool enable) override// done in DialogList
	{
		DialogList::ToolTipsEnabled(enable);
		m_listBoxDerivedBold->EnableTooltips(enable, m_toolTip);
	}
*/
	virtual void FinishDialog(int result) override
	{
		DialogList::FinishDialog(result);
		ClearList();
	}

	virtual void FillNumbers() = 0;

	virtual void BeforeShow() override
	{
		ClearList();
		FillNumbers();
		if(m_item)
		{
			m_listBoxDerivedBold->SetItemBold(m_listBoxDerivedBold->FindItemByUInt((unsigned int)
#if(_MSC_VER > 1600)
				(size_t)
#endif
				m_item));
		}
		else
		{
			m_listBoxDerivedBold->SetItemBold(-1);
		}

		DialogList::BeforeShow();
	}
	ListBoxUIntDerivedBold* m_listBoxDerivedBold;
};

class UGUI_API DialogListDate : public DialogListUIntDerived
{
//public:
/*
	void Display(const unsigned int& code, const unsigned int& compactPrice, CWnd* const& parent, const int& x, const int& y, const int& w, const int& h, const bool& fastSelection, const unsigned int& maxVisibleItemCount = 0, CWnd* const& receipient = nullptr, const COLORREF& bkColor = 0xFFFFFFFF, const COLORREF& selectionBkColor = 0xFFFFFFFF, const COLORREF& textColor = 0xFFFFFFFF, const COLORREF& selectionTextColor = 0xFFFFFFFF)
	{
		DialogListUIntDerived::Display(code, date, parent, x, y, w, h, fastSelection, maxVisibleItemCount, receipient, bkColor, selectionBkColor, textColor, selectionTextColor);
	}
*/
protected:
	DialogListDate(MainMessageLoopWnd* const& mainWnd, CWnd* const& parent, const unsigned int& maxVisibleItemtCount):
		DialogListUIntDerived(mainWnd, parent, &m_ListBoxDate, maxVisibleItemtCount),
		m_ListBoxDate(0, true)//, false, false)
	{
	}
//	virtual void FillNumbers() = 0;
	ListBoxDate m_ListBoxDate;
};

class UGUI_API DialogListPrice : public DialogListUIntDerived
{
//public:
/*
	void Display(const unsigned int& code, const unsigned int& compactPrice, CWnd* const& parent, const int& x, const int& y, const int& w, const int& h, const bool& fastSelection, const unsigned int& maxVisibleItemCount = 0, CWnd* const& receipient = nullptr, const COLORREF& bkColor = 0xFFFFFFFF, const COLORREF& selectionBkColor = 0xFFFFFFFF, const COLORREF& textColor = 0xFFFFFFFF, const COLORREF& selectionTextColor = 0xFFFFFFFF)
	{
		DialogListUIntDerived::Display(code, compactPrice, parent, x, y, w, h, fastSelection, maxVisibleItemCount, receipient, bkColor, selectionBkColor, textColor, selectionTextColor);
	}
*/
protected:
	DialogListPrice(MainMessageLoopWnd* const& mainWnd, CWnd* const& parent, const unsigned int& maxVisibleItemtCount):
		DialogListUIntDerived(mainWnd, parent, &m_ListBoxPrice, maxVisibleItemtCount),
		m_ListBoxPrice(0, true)//, false, false)
	{
	}
//	virtual void FillNumbers() = 0;
	ListBoxPrice m_ListBoxPrice;
};


class UGUI_API TakionSettingDialog : public TakionDialog
{
friend class TakionSettingTabDialog;
friend class TakionSettingTopDialog;
public:
//	virtual bool isModified() const{return true;}
//	virtual void SetModified(bool modified){}
	virtual bool isModified() const{return m_modified;}
	void SetModified(const bool& modified){m_modified = modified;}
//	virtual ~TakionSettingDialog();
//	static const int defaultHeight = 152;
	static const int tabHeight = 12;
//	static const int settingHeight = 164;
//	static const int settingWidth = 437;
	static const int commonControlsWidth = 35;
	const std::string& GetLabelString() const{return m_label;}
	const char* GetLabel() const{return m_label.c_str();}
	virtual bool isForceApply() const{return false;}
	virtual void Apply();
	virtual void PrepareForSavingLayout(){UpdateSettings();}
	virtual void UpdateSettings(){}
	virtual void UpdateControls(){}
	virtual void PostInitDialog(){}
	virtual void UpdateLeafControls(){UpdateControls();}
	virtual bool isActiveTab() const{return true;}
//	virtual HWND GetFirstTabControl() = 0;

	typedef std::vector<TakionSettingDialog*> SettingDialogVector;
	virtual SettingDialogVector* GetSettingDialogs(){return nullptr;}

	virtual bool isLeaf() const{return false;}
	bool GetTabPath(std::string& tabPath, const char* prependWith) const;
	virtual void CloseDialog();
	virtual bool SetTabToOpen(const char* tabToOpen, const void* initInfo = nullptr);
	virtual void SetInitialTab(){}
	virtual unsigned int GetLevel() const = 0;
	const int& GetWidth() const{return m_width;}
	const int& GetHeight() const{return m_height;}
	virtual TakionSettingDialog* GetCurrentLeaf() = 0;
	virtual const TakionSettingDialog* GetCurrentLeaf() const = 0;
	bool CreateSettingDialog(bool setInitialTab);
	void UpdateCurrentLeafSettings();
	const unsigned int& GetTabOrdinal() const{return m_tabOrdinal;}
	virtual int GetCurrentTab() const{return -1;}
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	TakionSettingTabDialog* GetParentTab(){return m_parentTab;}
	virtual TakionSettingTabDialog* GetMainTabDialog();
	virtual const TakionSettingTabDialog* GetMainTabDialog() const;
	virtual int GetTopDialogWidth() const;
	virtual int GetTopDialogHeight() const;
	const bool& isCurrent() const{return m_current;}
	virtual void RestoreLayout(){}
	virtual void SameLayoutOnRestore(){}
	virtual CButton& GetOkButton();
	virtual CButton& GetApplyButton();
	virtual CButton& GetOnTopCheckBox();
	virtual CButton& GetToolTipsCheckBox();
	virtual CButton& GetCancelButton();
	virtual CButton& GetHelpButton();
	virtual void EnableApplyButton(bool enable);
	virtual void EnableOkButton(bool enable);
	void EnableOkAndApplyButton(bool enable)
	{
		EnableOkButton(enable);
		EnableApplyButton(enable);
	}
	virtual void OnOK() override;
	void ApplyInitInfo();
	virtual bool isAlarm() const{return false;}
	virtual void SetAlarm(bool alarm, unsigned int tabOrdinal = 0xFFFFFFFF){}

//	typedef std::set<unsigned int> UIntSet;
	void AddNoShiftCommandCtrlId(const unsigned int& ctrlId){m_noShiftCommandCtrlIds.insert(ctrlId);}
	bool HasNoShiftCommandCtrlId(const unsigned int& ctrlId) const{return m_noShiftCommandCtrlIds.find(ctrlId) != m_noShiftCommandCtrlIdsEnd;}
	bool isInNoShiftCommandCtrlId() const{return HasNoShiftCommandCtrlId((unsigned int)::GetDlgCtrlID(::GetFocus()));}
	void RemoveNoShiftCommandCtrlId(const unsigned int& ctrlId){m_noShiftCommandCtrlIds.erase(ctrlId);}
	void ClearNoShiftCommandCtrlId(){m_noShiftCommandCtrlIds.clear();}

	virtual bool OnPageCommand(DWORD loword){return false;}
	virtual void AddPageMenuItems(CMenu& menu, const CPoint& point) const{}
	virtual bool DrawPageMenuItems(const DRAWITEMSTRUCT* lpDrawItemStruct) const{return false;}
	virtual bool MeasurePageMenuItems(LPMEASUREITEMSTRUCT lpMeasureItemStruct) const{return false;}
protected:
	TakionSettingDialog(MainMessageLoopWnd* mainWnd, TakionSettingTabDialog* parentTab, const char* label, CWnd* par, unsigned int id):
		TakionDialog(mainWnd, true, par, id),
		m_parentTab(parentTab),
		m_label(label),
		m_width(0),
		m_height(0),
		m_initInfo(nullptr),
		m_current(false),
		m_modified(false),
		m_tabOrdinal(0),
		m_noShiftCommandCtrlIdsEnd(m_noShiftCommandCtrlIds.cend())
	{}
	TakionSettingDialog(MainMessageLoopWnd* mainWnd, TakionSettingTabDialog* parentTab, LPCSTR label, DWORD style = 0, DWORD exstendedStyle = 0, int x = 0, int y = 0, int w = 0, int h = 0, LPCSTR font = nullptr, WORD fontSize = 8):
		TakionDialog(mainWnd, true, nullptr, style, exstendedStyle, x, y, w, h, font, fontSize),
		m_parentTab(parentTab),
		m_label(label),
		m_width(w),
		m_height(h),
		m_initInfo(nullptr),
		m_current(false),
		m_modified(false),
		m_tabOrdinal(0),
		m_noShiftCommandCtrlIdsEnd(m_noShiftCommandCtrlIds.cend())
	{}

//	virtual bool isToolTipsEnabledAdditional() const override{return !m_parentTab || m_parentTab->isToolTipsEnabledAdditional();}
//	virtual bool isToolTipsEnabledAdditional() const override{return m_configBase->m_toolTipsInSettings.GetValue();}

//	virtual bool PropagateToolTipsEnabled(bool enabled){return SetToolTipsEnabled(enabled);}

	virtual bool isTooltipConfigValid() const override;
	virtual bool isToolTipsEnabledAdditional() const override;
	virtual bool isToolTipsEnabled() const override;

	virtual void SetupControls(){}//RestoreLayout();}//called after the dialog is created
	virtual void NullifyInitInfo();
	virtual void DoApplyInitInfo(){}
	virtual void DestroyInitInfo(const void* initInfo){}
//	virtual void Entering(){}
//	virtual void Leaving(){}
	afx_msg void OnDestroy();
	afx_msg void OnModified();
	afx_msg LRESULT OnWmUserModified(WPARAM w, LPARAM l);
	DECLARE_MESSAGE_MAP()
	virtual bool isCloseOnEnter() const;
	virtual void SetActiveTab(bool activeTab){}
	TakionSettingTabDialog* m_parentTab;
	std::string m_label;
	int m_width;
	int m_height;
	const void* m_initInfo;
	bool m_current;
	bool m_modified;
	unsigned int m_tabOrdinal;

	UIntSet m_noShiftCommandCtrlIds;
	UIntSet::const_iterator m_noShiftCommandCtrlIdsEnd;
};

//class TakionSettingTabDialog;

class PointLocatorUShortOrderedMap;

//http://www.codeproject.com/Articles/1786/Ownerdraw-Tab-Controls-Borders-and-All
class UGUI_API TakionTab : public CTabCtrl
{
friend class TakionSettingTabDialog;
public:
//	typedef std::map<PointLocatorInt, unsigned short, lessPointLocator<PointLocatorInt::ValueType> > TabMap;
//	typedef TabMap::iterator TabIterator;
//	typedef TabMap::const_iterator TabConstIterator;

	TakionTab(TakionSettingTabDialog* tabDialog,
		const char* const& title = nullptr,
		const COLORREF& titleColor = RGB(0, 0, 128),
		bool showTime = false,
		const COLORREF& selectedBkColor = RGB(196, 196, 255),
		const COLORREF& alarmBkColor = RGB(255, 0, 0));
	virtual ~TakionTab();
	void CurrentTabChanged();
	const CRect& GetTotalTabRect() const{return m_totalTabRect;}
	const CRect& GetTitleRect() const{return m_titleRect;}
	const CSize& GetDimensions() const{return m_dimensions;}
	const std::string& GetTitle() const{return m_title;}
	inline void InvalidateRectIfValid(const RECT* rect) const{if(m_hWnd)::InvalidateRect(m_hWnd, rect, FALSE);}

	void SetTitle(const char* const& title)
	{
		if(title)
		{
			if(strcmp(m_title.c_str(), title))
			{
				m_title = title;
				CalculateCaptionRect();
				InvalidateRectIfValid(&m_titleRect);
//				if(m_hWnd)::InvalidateRect(m_hWnd, &m_titleRect, TRUE);
			}
		}
		else if(!m_title.empty())
		{
			m_title.clear();
			m_captionWidth = 0;
			m_captionHeight = m_titleRect.Height();
			m_captionRect.top = m_titleRect.top;
			m_captionRect.bottom = m_titleRect.bottom;
			m_captionRect.left = m_captionRect.right = m_titleRect.left;
			InvalidateRectIfValid(&m_titleRect);
//			if(m_hWnd)::InvalidateRect(m_hWnd, &m_titleRect, TRUE);
		}
	}
	const COLORREF& GetTitleColor() const{return m_titleColor;}
	void SetTitleColor(const COLORREF& color)
	{
		if(color != m_titleColor)
		{
			m_titleColor = color;
			if(m_hWnd)::InvalidateRect(m_hWnd, &m_titleRect, TRUE);
		}
	}
	const COLORREF& GetSelectedBkColor() const{return m_selectedBkColor;}
	void SetSelectedBkColor(const COLORREF& color)
	{
		if(color != m_selectedBkColor)
		{
			m_selectedBkColor = color;
			InvalidateRectIfValid(&m_titleRect);
//			if(m_hWnd)::InvalidateRect(m_hWnd, &m_titleRect, TRUE);
		}
	}
	const COLORREF& GetAlarmBkColor() const{return m_alarmBkColor;}
	void SetAlarmBkColor(const COLORREF& color)
	{
		if(color != m_alarmBkColor)
		{
			m_alarmBkColor = color;
			InvalidateRectIfValid(&m_titleRect);
//			if(m_hWnd)::InvalidateRect(m_hWnd, &m_titleRect, TRUE);
		}
	}
	void InvalidateTitle();
	const bool& isShowTime() const{return m_showTime;}
	void SetShowTime(const bool& showTime);
	const bool& isAlarm() const{return m_alarm;}
	void SetAlarm(const bool& alarm);

	const unsigned short& GetTabCount() const{return m_tabCount;}
	const short& GetTabCurrent() const{return m_tabCurrent;}
	const unsigned short& GetTabScrollPos() const{return m_tabScrollPos;}
	const int& GetTabLeftOffset() const{return m_tabLeftOffset;}
	const int& GetTabScrollOffset() const{return m_tabScrollOffset;}
	const int& GetTotalTabWidth() const{return m_totalTabWidth;}
	const int& GetTotalTabHeight() const{return m_totalTabHeight;}
protected:
	void SetIdUnderMouse(int id);
	virtual void PreSubclassWindow() override;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcMouseLeave();
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
	TakionSettingTabDialog* m_tabDialog;
	CRect m_currentTabRect;
	int m_idUnderMouse;
	bool m_mouseInside;
	bool m_ncMouseInside;
	CRect m_totalTabRect;
	CRect m_titleRect;
	CSize m_dimensions;
	COLORREF m_titleColor;
	COLORREF m_selectedBkColor;
	COLORREF m_alarmBkColor;
	std::string m_title;
	CRect m_captionRect;
	int m_captionHeight;
	int m_captionWidth;
	void CalculateCaptionRect();
	void DoCalculateCaptionRect(CDC* dc);
	void UpdateCaptionHeight(int h);
	void UpdateCaptionWidth(int width);

	inline void UpdateTimeToken(unsigned char& myToken, const unsigned char& token, const CRect& rect)
	{
		if(token != myToken)
		{
			myToken = token;
//			InvalidateRectIfValidWithErase(&rect);
			::InvalidateRect(m_hWnd, &rect, TRUE);
		}
	}
	void UpdateShowTime();
	void UpdateAlarm();
	void CalculateTimeRectWidth();
	void CalculateTimeRectHeight();
	void AdjustTimeRectWidth();
	int m_timeHeight;
	int m_timeTokenWidth;
	int m_colonWidth;
	CRect m_hourRect1;
	CRect m_hourRect2;
	CRect m_colon1Rect;
	CRect m_minuteRect1;
	CRect m_minuteRect2;
	CRect m_colon2Rect;
	CRect m_secondRect1;
	CRect m_secondRect2;
	CRect m_secondRect;//union of m_secondRect1 and m_secondRect2
	CRect m_timeRect;
	bool m_showTime;
	void InvalidateAlarmedTabs();
	bool m_alarm;
	bool m_alarmBlinkState;
	unsigned char m_currentHour1;
	unsigned char m_currentHour2;
	unsigned char m_currentMinute1;
	unsigned char m_currentMinute2;
	unsigned char m_currentSecond1;
	unsigned char m_currentSecond2;

	void TabsCreated();
	void DoCurrentTabChanged();
/*
	void UpdateTabIterators()
	{
		m_tabBegin = m_tabMap.begin();
		m_tabLast = m_tabEnd;
		if(m_tabBegin != m_tabEnd)
		{
			--m_tabLast;
		}
	}
*/
	PointLocatorUShortOrderedMap* m_tabMap;
//	SCROLLINFO m_horizontalScrollInfo;
//	TabConstIterator m_tabConstEnd;
//	TabIterator m_tabBegin;
//	TabIterator m_tabEnd;
//	TabIterator m_tabLast;
//	TabIterator m_tabFirstVisible;
	unsigned short m_tabCount;
	short m_tabCurrent;
	unsigned short m_tabScrollPos;
//	unsigned short m_totalTabCount;
	int m_tabLeftOffset;
	int m_tabScrollOffset;
	int m_totalTabWidth;
	int m_totalTabHeight;
private:
	TakionTab(const TakionTab& other);
	TakionTab& operator=(const TakionTab& other);
};

class UGUI_API TakionSettingTabDialog : public TakionSettingDialog
{
friend class TakionSettingDialog;
friend class TakionSettingPageBase;
public:
	virtual ~TakionSettingTabDialog();
//	TakionSettingTabDialog(CWnd* par, unsigned int id):TakionSettingDialog(par, id){}
	TakionSettingTabDialog(MainMessageLoopWnd* mainWnd, TakionSettingTabDialog* parentTab, const char* label, int width = 0, int height = 0, const char* title = nullptr, COLORREF titleColor = RGB(0, 0, 128), int topOffset = 0, bool showTime = false, COLORREF selectedBkColor = RGB(196, 196, 255), COLORREF alarmBkColor = RGB(255, 0, 0));
	virtual SettingDialogVector* GetSettingDialogs() override{return &m_settingDialogs;}
	void AddSettingDialog(TakionSettingDialog* dlg);
	void InsertSettingDialog(int index, TakionSettingDialog* dlg);
	TakionSettingDialog* GetSettingDialogAt(unsigned int i){return i < (unsigned int)m_settingDialogs.size() ? m_settingDialogs[i] : nullptr;}
	TakionSettingDialog* GetCurrentSettingDialog(){return m_currentTab >= 0 && m_currentTab < (int)m_settingDialogs.size() ? m_settingDialogs[m_currentTab] : nullptr;}
	const TakionSettingDialog* GetSettingDialogAt(unsigned int i) const{return i < (unsigned int)m_settingDialogs.size() ? m_settingDialogs[i] : nullptr;}
	const TakionSettingDialog* GetCurrentSettingDialog() const{return m_currentTab >= 0 && m_currentTab < (int)m_settingDialogs.size() ? m_settingDialogs[m_currentTab] : nullptr;}
	virtual TakionSettingDialog* GetCurrentLeaf() override{return m_currentTab >= 0 && m_currentTab < (int)m_settingDialogs.size() ? m_settingDialogs[m_currentTab]->GetCurrentLeaf() : nullptr;}
	virtual const TakionSettingDialog* GetCurrentLeaf() const override{return m_currentTab >= 0 && m_currentTab < (int)m_settingDialogs.size() ? m_settingDialogs[m_currentTab]->GetCurrentLeaf() : nullptr;}
	void SetCurrentTab(int tabOrdinal);
	virtual int GetRightMargin() const{return 0;}
	virtual void PrepareForSavingLayout() override;
	virtual void UpdateSettings() override;
	virtual void UpdateControls() override;
	virtual void UpdateLeafControls() override{}
	virtual HWND GetFirstTabControl() const override;
	virtual bool SetTabToOpen(const char* tabToOpen, const void* initInfo = nullptr);
	virtual void SetInitialTab();
	virtual unsigned int GetLevel() const override{return m_level;}
	const unsigned int& GetLevelsCountUnder() const{return m_levelsCountUnder;}
	virtual int GetCurrentTab() const{return m_currentTab;}
	virtual TakionSettingTabDialog* GetMainTabDialog(){return m_parentTab ? m_parentTab->GetMainTabDialog() : this;}
	virtual const TakionSettingTabDialog* GetMainTabDialog() const{return m_parentTab ? m_parentTab->GetMainTabDialog() : this;}
	virtual int GetTopDialogWidth() const{return m_parentTab ? m_parentTab->GetTopDialogWidth() : m_width;}
	virtual int GetTopDialogHeight() const{return m_parentTab ? m_parentTab->GetTopDialogHeight() : m_height;}
//	static const int rightMargin;
	virtual void RestoreLayout();
	virtual void SameLayoutOnRestore();
	virtual void OnMouseForcedReleaseCapture();
	virtual void TabNcDoubleClicked(){}
//	virtual bool CreateSettingDialog();
	const CRect& GetDisplayArea() const{return m_displayArea;}
	void InvalidateTabTitle();
	const int& GetTopOffset() const{return m_topOffset;}
	const int& GetTopOffsetPixel() const{return m_topOffsetPixel;}
	void SetTabTopOffsetPixel(int offsetPixel);

	virtual bool isExtensionMainDialog() const{return false;}
	virtual bool isAlarm() const override{return !m_alarmSet.isEmpty();}
	virtual void SetAlarm(bool alarm, unsigned int tabOrdinal) override
	{
		const bool wasAlarm = !m_alarmSet.isEmpty();
		m_alarmSet.SetBit(tabOrdinal, alarm);
		if(wasAlarm == m_alarmSet.isEmpty())
		{
			m_Tab.SetAlarm(alarm);
			if(m_parentTab)m_parentTab->SetAlarm(alarm, m_tabOrdinal);
		}
	}
	unsigned int GetSettingCount() const{return (unsigned int)m_settingDialogs.size();}
	const unsigned int& GetTabCount() const{return m_alarmSet.GetLength();}
	bool isTabAlarmed(const unsigned int& tabOrdinal) const{return m_alarmSet.isBitSet(tabOrdinal);}
	virtual bool isLeafRButtonMenuOk() const{return false;}
	virtual bool isLeafNcRButtonMenuOk() const{return false;}
protected:
	TakionTab m_Tab;
	virtual void DisplayPageMenu(TakionSettingPageBase* leaf, const CPoint& point){}
	virtual void NullifyInitInfo() override;
	virtual void DoApplyInitInfo() override;
	virtual BOOL OnInitDialog() override;
	virtual void DoDataExchange(CDataExchange* pDX) override;
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
	virtual void Resize(bool widthChanged = true, bool heightChanged = true) override;
	virtual void Entering() override;
	virtual void Leaving() override;
	virtual void FinishDialog(int result) override;
	virtual void SetActiveTab(bool activeTab) override;
	virtual void SettingTabDestroyed(){}
	virtual bool PropagateToolTipsEnabled(bool enabled) override
	{
		bool ret = TakionSettingDialog::PropagateToolTipsEnabled(enabled);
		TakionSettingDialog* settingDialog;
		for(SettingDialogVector::iterator it = m_settingDialogs.begin(), itend = m_settingDialogs.end(); it != itend; ++it)
		{
			settingDialog = *it;
			settingDialog->PropagateToolTipsEnabled(enabled);
		}
		return ret;
	}
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void CreateTabs();
//	afx_msg void OnExitSizeMove();
	afx_msg void OnDestroy();
//	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
	SettingDialogVector m_settingDialogs;
	int m_currentTab;
	CRect m_aboveArea;
	CRect m_displayArea;
//	COLORREF m_tabColor;
//	CBrush* m_tabBrush;
	std::string m_tabToOpen;
	unsigned int m_level;
	void SetLevelsCountUnder(const unsigned int& levelsCount)
	{
		if(levelsCount > m_levelsCountUnder)
		{
			m_levelsCountUnder = levelsCount;
			if(m_parentTab)m_parentTab->SetLevelsCountUnder(levelsCount + 1);
		}
	}
	unsigned int m_levelsCountUnder;
	int m_topOffset;
	int m_topOffsetPixel;
	bool m_setInitialTab;
	TakionBitField<size_t> m_alarmSet;
};

class UGUI_API TakionSettingPageBase : public TakionSettingDialog
{
public:
	virtual bool isActiveTab() const override{return m_activeTab;}
	virtual bool isLeaf() const override{return true;}
	virtual bool isAlarm() const override{return m_alarm;}
	virtual void SetAlarm(bool alarm, unsigned int tabOrdinal = 0xFFFFFFFF) override
	{
		if(alarm != m_alarm)
		{
			m_alarm = alarm;
			if(m_parentTab)m_parentTab->SetAlarm(alarm, m_tabOrdinal);
		}
	}
	virtual unsigned int GetLevel() const override{return m_parentTab->GetLevel();}
	virtual TakionSettingDialog* GetCurrentLeaf() override{return this;}
	virtual const TakionSettingDialog* GetCurrentLeaf() const override{return this;}
//	virtual bool CreateSettingDialog();
	virtual bool isPointForRButtonMenuOk(UINT nFlags, CPoint point) const override;
	virtual bool isPointForNcRButtonMenuOk(UINT nFlags, CPoint point) const override;
protected:
	TakionSettingPageBase(MainMessageLoopWnd* mainWnd, TakionSettingTabDialog* parentTab, LPCSTR label);//, int height = defaultHeight);
	TakionSettingPageBase(MainMessageLoopWnd* mainWnd, TakionSettingTabDialog* parentTab, const char* label, CWnd* par, unsigned int id);
	virtual void SettingPageDestroyed(){}
	virtual void SetActiveTab(bool activeTab){m_activeTab = activeTab;}
	virtual void DisplayMenu(const CPoint& point) override;
	bool m_activeTab;
	bool m_alarm;
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
};

class UGUI_API TakionSettingAboutBase : public TakionSettingPageBase
{
public:
	TakionSettingAboutBase(MainMessageLoopWnd* mainWnd, TakionSettingTabDialog* parentTab,
		const char* releaseNotesLink,
		int listBoxLeft,
		int listBoxTop,
		HICON productIcon,
		const char* productName,
		const char* legalCopyright);
	virtual HWND GetFirstTabControl() const override;
	virtual void UpdateControls();
	int AddProperty(const char* name, const char* value, COLORREF valueColor, bool bold);
	int InsertProperty(unsigned int at, const char* name, const char* value, COLORREF valueColor, bool bold);
	int FindItemByPropertyName(const char* name) const;
	bool InsertBeforeProperty(const char* beforeName, bool after, const char* name, const char* value, COLORREF valueColor, bool bold);
	bool SetPropertyValue(const char* name, const char* value, COLORREF valueColor, char bold)
	{
		return m_ListBoxAbout.SetPropertyValue(name, value, valueColor, bold);
	}
	bool SetPropertyValueAt(int at, const char* value, COLORREF valueColor, char bold)
	{
		return m_ListBoxAbout.SetPropertyValueAt(at, value, valueColor, bold);
	}
	
	virtual bool isVersionValid() const;

	bool InsertDllProperty(unsigned int at,
		const char* productName,//"Utils"//fileDescription,
		const char* filePathAndName,

		const unsigned __int64& moduleVersionNum,

		const unsigned __int64& expectedModuleVersion1,
		const unsigned __int64& expectedModuleVersion2,
		const unsigned __int64& expectedModuleVersion3,
		const unsigned __int64& expectedModuleVersion4,

		const char* dllHeaderVersion,
		const char* expectedHeaderVersion)
	{
		return DoInsertDllProperty(at,
			productName,//fileDescription,
			filePathAndName,
			moduleVersionNum,
			U_GetVersion64(expectedModuleVersion1, expectedModuleVersion2, expectedModuleVersion3, expectedModuleVersion4),
			dllHeaderVersion,
			expectedHeaderVersion);
	}

	virtual bool DoInsertDllProperty(unsigned int at,
		const char* productName,//fileDescription,
		const char* filePathAndName,
		const unsigned __int64& moduleVersionNum,
		const unsigned __int64& expectedModuleVersionNum,
		const char* dllHeaderVersion,
		const char* expectedHeaderVersion);

	void UpdateIpAddresses();

	static const char* const warning;
protected:
	virtual void FillProperties();
	EditNoContext m_EditSearch;
	ButtonToolTip m_ButtonSearch;
	ListBoxProperty m_ListBoxAbout;
	UrlLink m_versionLink;
    virtual void DoPaint(const RECT& rcPaint, CDC& dc) override;
	virtual void Resize(bool widthChanged = true, bool heightChanged = true) override;

//	virtual void Entering() override;
	virtual void ToolTipsEnabled(bool enable) override;

//	virtual void SettingPageDestroyed();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void MouseLeft();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
//	afx_msg void OnSelchangeAbout();
	afx_msg void OnSearchChange();
	afx_msg void OnSearch();
	DECLARE_MESSAGE_MAP()
//	CRect m_listBoxRect;
	CFont* m_versionFont;
	CFont* m_copyrightFont;
	CFont* m_warningFont;
	CRect m_iconRect;
	CRect m_productRect;
	CRect m_copyrightRect;
	CRect m_warningRect;
	unsigned char ProcessKeyInSearch(MSG* pMsg);
	bool SearchItems();
	CString m_searchStr;
	bool m_searchDone;
//	int m_listBoxLeft;
//	int m_listBoxTop;
	HICON m_productIcon;
	std::string m_productName;
	std::string m_legalCopyright;

	VHResizeControl* m_lbControl;
};

class UGUI_API TakionSettingGraphics : public TakionSettingPageBase
{
public:
	TakionSettingGraphics(MainMessageLoopWnd* mainWnd, TakionSettingTabDialog* parentTab);
	virtual HWND GetFirstTabControl() const override{return m_ListBoxGraphics.m_hWnd;}
	virtual void UpdateSettings();
protected:
	virtual void DoApplyInitInfo() override;
	virtual void ToolTipsEnabled(bool enable) override;
	ListBoxGraphics m_ListBoxGraphics;
	ListBoxNamedColor m_ListBoxColor;

	ListBoxFont m_ListBoxFont;
	ListBoxUInt<unsigned int> m_ListBoxSize;
	ListBoxUInt<unsigned int> m_ListBoxMaxSize;
	CStatic m_StaticFontName;
	CStatic m_StaticSizeName;
	CStatic m_StaticMaxSizeName;
	EditNoContext m_EditFontSample;
	CButton m_CheckBoxBold;
	CButton m_CheckBoxItalic;
	
	EditNoContext m_EditSearch;
	CButton m_ButtonSearch;
	
	CStatic m_StaticHorizontalSpacing;
	CStatic m_StaticVerticalSpacing;
	ComboBoxString m_ComboBoxHSpacing;
	ComboBoxString m_ComboBoxVSpacing;

	void SetInitialFontParams(const char* name, const char* actualName, unsigned int size, unsigned int maxSize, bool bold, bool italic);//, bool italic, bool custom)
//	CButton m_colorButton[Graphics::colorCount];
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void SettingPageDestroyed();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnSelchangeGraphics();
//	afx_msg LRESULT OnColorChange(WPARAM w, LPARAM l);

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnSelchangeFont();
	afx_msg void OnSelchangeFontSize();
	afx_msg void OnSelchangeFontMaxSize();
	afx_msg void OnBold();
	afx_msg void OnItalic();

	afx_msg void OnSearchChange();
	afx_msg void OnSearch();

//	afx_msg void OnSampleChange();
//	afx_msg void OnSampleUpdate();

	afx_msg void OnSelchangeHSpacing();
	afx_msg void OnSelchangeVSpacing();
	afx_msg void OnDblClkColor();

	DECLARE_MESSAGE_MAP()

	bool UpdateFontSize();
	bool UpdateFontMaxSize();

	void DrawSmallFont();

	Graphics* m_currentGraphics;

	void SetShowMaxSize(bool maxSize);
	void SetShowFont(bool showFont);
	void SetHorizontalSpacingName(const char* name);
	void SetVerticalSpacingName(const char* name);
	int m_currentFontSelection;

	unsigned int m_currentSizeSelection;
	unsigned int m_currentMaxSizeSelection;

	unsigned int m_selectedSize;
	unsigned int m_selectedMaxSize;

	bool m_showMaxSize;
	bool m_showFont;
	const char* m_horizontalSpacingName;
	const char* m_verticalSpacingName;

	bool SearchItems();
	unsigned char ProcessKeyInSearch(MSG* pMsg);
	CString m_searchStr;
	bool m_searchDone;
};

class UGUI_API TakionSettingPickItems : public TakionSettingPageBase
{
public:
	virtual ~TakionSettingPickItems();
//	virtual HWND GetFirstTabControl() const{return m_lbPickFrom->m_hWnd;}
	virtual HWND GetFirstTabControl() const override{return m_EditSearch.m_hWnd;}
	virtual void UpdateSettings();
	virtual void UpdateControls();
	virtual bool ClearItems();

	enum TakionSettingPickIds : unsigned int
	{
		valueListBoxAllId = 10000,
		valueListBoxSelectedId,
		infoStaticId,
		searchEditId,
		searchButtonId,

		takionSettingPickIdsCount
	};

	const int& GetAllSelection() const{return m_allSelection;}
protected:
	TakionSettingPickItems(MainMessageLoopWnd* mainWnd, TakionSettingTabDialog* parentTab, const char* label, ListBoxOwnerDraw* lbPickFrom, ListBoxOwnerDraw* lbPickTo, int lbWidth, int hOffset, bool tooltips, bool removeByDragging, bool pickToSorted = false);//, int height = defaultHeight);

	CStatic m_StaticInfo;
	EditNoContext m_EditSearch;
	CButton m_ButtonSearch;
	ListBoxOwnerDraw* m_lbPickFrom;
	ListBoxOwnerDraw* m_lbPickTo;
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void SettingPageDestroyed() override;

//	virtual void Entering() override;
	virtual void ToolTipsEnabled(bool enable) override;

    virtual void DoPaint(const RECT& rcPaint, CDC& dc) override;
	virtual void OnMouseForcedReleaseCapture() override;
//	virtual void MouseEntered();
	virtual void MouseLeft() override;
//	virtual bool ResizeMouseArea(const CPoint& point, bool locked);
	virtual unsigned char UpdateResizeCursor(const CPoint& point, bool locked) override;

	virtual void Resize(bool widthChanged = true, bool heightChanged = true) override;

//	virtual void LBItemDraggedAndDropped(unsigned int ctrlId, unsigned int itemOrdinal);
	virtual void LBItemDraggedAndDropped(unsigned int ctrlId, unsigned short from, unsigned short to) override;
	virtual void LBDragDropDone(unsigned int ctrlId, int itemOrdinalOld, int itemOrdinalNew) override;
	virtual void LBDragDropAbort(unsigned int ctrlId, int itemOrdinal) override;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnDblClkAll();
	afx_msg void OnDblClkSelected();
	afx_msg void OnSelchangeAll();
//	afx_msg void OnSelchangeSelected();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSearchChange();
	afx_msg void OnSearch();
	afx_msg LRESULT OnListBoxRightButtonSelection(WPARAM ctrlId, LPARAM l);
	DECLARE_MESSAGE_MAP()

	virtual void AllSelectionChanged(){}
	int m_allSelection;

//Dialog Unit values
	int m_lbWidth;
	int m_hOffset;

	int m_staticHeight;
	int m_checkBoxHeight;
	int m_editWidth;
	int m_editHeight;
	int m_buttonWidth;
	int m_buttonHeight;
	int m_searchHeight;

	bool m_valuesModified;

	bool m_tooltips;
	bool m_removeByDragging;

	ActiveRectXButton m_clearItemsBox;
	ActiveRect* m_activeRect;
/*
//Pixel values
	int m_fromOffsetLeft;
	int m_fromOffsetTop;
	int m_fromWidth;

	int m_toOffsetLeft;
	int m_toOffsetTop;
	int m_toWidth;
*/
	virtual bool UpdateOnLButtonUp(UINT nFlags, CPoint point){return false;}
	virtual unsigned char ProcessKeyInSearch(MSG* pMsg);
	bool SearchItems();
	CString m_searchStr;
	bool m_searchDone;

//	virtual bool CreateToolTip() override;
//	virtual bool DestroyToolTip() override;
//	CToolTipCtrl* m_toolTip;
};

class UGUI_API TakionSettingColorArray : public TakionSettingPageBase
{
public:
	TakionSettingColorArray(MainMessageLoopWnd* mainWnd,
		TakionSettingTabDialog* parentTab,
		VectorSetting<UIntSetting>& configColors,
		BoolSetting& recycleColorsSetting,
		const char* label);
	virtual void UpdateSettings();
	virtual HWND GetFirstTabControl() const override;
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
	virtual void UpdateUpdateColorArray(){}
	VectorSetting<UIntSetting>& m_configColors;
	BoolSetting& m_recycleColorsSetting;
	ListBoxColor m_ListBoxColors;
	CButton m_CheckBoxRecycleColors;
};

class UGUI_API TakionSettingTopDialog : public TakionSettingTabDialog
{
public:
	TakionSettingTopDialog(MainMessageLoopWnd* mainWnd, int width, int height, const char* title = nullptr, COLORREF titleColor = RGB(0, 0, 128), int topOffset = 0, bool showTime = false, COLORREF selectedBkColor = RGB(196, 196, 255), COLORREF alarmBkColor = RGB(255, 0, 0), int buttonWidth = 30, const char* cancelButtonLabel = nullptr, const char* okButtonLabel = nullptr);
	virtual int GetRightMargin() const;
//	void AddAllTabs();
	virtual void OnOK() override;
	virtual void Apply() override;
//	TakionSettingCommands* GetTakionSettingCommands(){return m_takionSettingCommands;}
//	virtual std::string GetHelpUrl() const;
	virtual TakionSettingTabDialog* GetMainTabDialog() override{return this;}
	virtual const TakionSettingTabDialog* GetMainTabDialog() const override{return this;}
	virtual int GetTopDialogWidth() const override{return m_width;}
	virtual int GetTopDialogHeight() const override{return m_height;}
//	virtual void OnOK();
	virtual bool isInitializedFromFile() const;
	virtual void GetPosRect(CRect& r);
	virtual bool ExtractIsAlwaysOnTop() const;
	virtual bool ExtractIsShowToolTips() const;
//	static const unsigned int buttonWidth = 30;//28;
	static const unsigned int buttonHeight = 12;//14;
	static const unsigned int checkBoxHeight = 10;
	static const unsigned int buttonGap = 2;//18;//20;
	virtual void EnableApplyButton(bool enable) override;
	virtual void EnableOkButton(bool enable) override;
	virtual CButton& GetOkButton() override{return m_ButtonOk;}
	virtual CButton& GetApplyButton() override{return m_ButtonApply;}
	virtual CButton& GetOnTopCheckBox() override{return m_CheckBoxOnTop;}
	virtual CButton& GetToolTipsCheckBox() override{return m_CheckBoxToolTips;}
	virtual CButton& GetCancelButton() override{return m_ButtonCancel;}
	virtual CButton& GetHelpButton() override{return m_ButtonHelp;}
	virtual void SetAlarm(bool alarm, unsigned int tabOrdinal) override
	{
		const bool wasAlarm = !m_alarmSet.isEmpty();
		m_alarmSet.SetBit(tabOrdinal, alarm);
		if(wasAlarm == m_alarmSet.isEmpty())
		{
			m_Tab.SetAlarm(alarm);
//			if(m_parentTab)m_parentTab->SetAlarm(alarm, m_tabOrdinal);
			InvalidateRectIfValid(&m_dividerRect);
//			if(m_hWnd)::InvalidateRect(m_hWnd, &m_dividerRect, FALSE);
		}
	}
	virtual bool isTooltipConfigValid() const override{return m_configBase != nullptr;}
	virtual bool isToolTipsEnabledAdditional() const override{return m_configBase->m_toolTipsInSettings.GetValue();}
	virtual bool isToolTipsEnabled() const override{return m_configBase->m_showTooltips.GetValue();}
protected:

	virtual bool isCloseOnEnter() const override{return m_closeOnEnter;}
	virtual void SaveAlwaysOnTop(bool onTop);
	virtual void SaveShowToolTips(bool showToolTips);
	CButton m_ButtonOk;
	CButton m_ButtonApply;
	CheckBoxOwnerDraw m_CheckBoxOnTop;
	CButton m_ButtonCancel;
	CheckBoxOwnerDraw m_CheckBoxToolTips;
	CButton m_ButtonHelp;

	virtual bool PlaceButtons();
	virtual void Resize(bool widthChanged = true, bool heightChanged = true) override;
	virtual void BeforeDestroy() override;

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	virtual void FinishDialog(int result);

	virtual void DoDataExchange(CDataExchange* pDX);
    virtual void DoPaint(const RECT& rcPaint, CDC& dc) override;

	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnOnTop();
	afx_msg void OnToolTips();
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	DECLARE_MESSAGE_MAP()

	CRect m_dividerRect;
	COLORREF m_dividerColor;

	void InitializeButtonPlacement();

	bool m_displayOnCreate;
	int m_buttonWidthInPixels;
	int m_buttonHeightInPixels;
	int m_checkBoxHeightInPixels;
	int m_buttonTop;
	int m_buttonBottom;
	int m_buttonLeft;
	int m_buttonLeftOffset;
	int m_rightMargin;
	int m_helpButtonTop;

	void SetCorner(const bool& corner){m_corner = corner;}
	bool m_corner;
};

//class ExtensionMainDialog;

class UGUI_API ExtensionConfig : public ConfigBase
{
public:
	virtual void Copy(const ConfigBase& other);
//	virtual ConfigBase* Clone() const;

	virtual void Update();

	ExtensionConfig& operator=(const ExtensionConfig& other);

	TakionDialog* GetDialog(){return m_dlg;}
	const TakionDialog* GetDialog() const{return m_dlg;}

	IntSetting m_x;
	IntSetting m_y;
	UIntSetting m_w;
	UIntSetting m_h;
	BoolSetting m_alwaysOnTop;
//	BoolSetting m_showToolTips;//ConfigBase has m_showToolTips
	StringSetting m_tab;
	BoolSetting m_visible;

protected:
	ExtensionConfig(TakionDialog* dlg);
	ExtensionConfig(const ExtensionConfig& other);
	void AddSettings();

	TakionDialog* m_dlg;
};

class UGUI_API ExtensionMainDialogBase : public TakionSettingTopDialog
{
public:
	ExtensionMainDialogBase(int width, int height,
		const char* title,
		const char* productName,
		unsigned __int64 productVersion,
		const char* configExtension,
		COLORREF titleColor = RGB(0, 0, 128),
		int topOffset = 0,
		bool showTime = false,
		COLORREF selectedBkColor = RGB(196, 196, 255),
		COLORREF alarmBkColor = RGB(255, 0, 0),
		int buttonWidth = 30,
		const char* cancelButtonLabel = nullptr,
		const char* okButtonLabel = nullptr);
//		const HMODULE dllModule = nullptr);
	virtual ~ExtensionMainDialogBase();

	enum ExtensionMainDialogIds : unsigned int
	{
		buttonOpenId = 3600,

		buttonSaveId,
		buttonSaveAsId,
		buttonRestoreId,
		buttonConfigId,

		mainDialogIdsCount,
	};

//	virtual bool CurrentAccountSet(const Account* account);
//	const Account* GetCurrentAccount() const{return m_currentAccount;}
	void ApplyConfig(unsigned int flags);
	virtual bool isInitializedFromFile() const override;
	virtual void GetPosRect(CRect& r) override;
	virtual bool ExtractIsAlwaysOnTop() const override;
	virtual bool ExtractIsShowToolTips() const override;

	const std::string& GetProductName() const{return m_productName;}
	const char* GetConfigExtension() const{return m_configExtension;}

	void SaveDlgLayout();
	void OpenDlgLayout();
	void SaveDlgLayoutAs();
	void RestoreDlgLayout();
	void SetConfig(ExtensionConfig* config);//{m_extensionConfig = config;}
	virtual const char* GetExtensionFilePathAndName() const{return nullptr;}
	virtual bool isExtensionMainDialog() const{return true;}
	virtual bool isTooltipConfigValid() const override{return m_extensionConfig != nullptr;}
	virtual bool isToolTipsEnabledAdditional() const override;//{return m_extensionConfig->m_showTooltips.GetValue(); }
	virtual bool isToolTipsEnabled() const override{return true;}
protected:
//	virtual bool InitializeToolTips() override
//	{
//		return SetToolTipsEnabled(isTooltipConfigValid() ? isToolTipsEnabled() && isToolTipsEnabledAdditional() : useToolTipsByDefault);
//	}
	virtual void SaveAlwaysOnTop(bool onTop) override;
	virtual void SaveShowToolTips(bool showToolTips) override;
	virtual void DoDataExchange(CDataExchange* pDX);
//	virtual void Resize(bool widthChanged = true, bool heightChanged = true);
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	virtual void DoActivate(UINT state, bool minimized) override;//, CWnd* pWndOther) override;
	virtual void FinishDialog(int result);
	virtual bool PlaceButtons();

	CButton m_ButtonOpenConfig;
	CButton m_ButtonSaveConfig;
	CButton m_ButtonSaveAsConfig;
	CButton m_ButtonRestoreConfig;
	CButton m_ButtonViewConfig;

	afx_msg void OnOpenConfig();
	afx_msg void OnSaveConfig();
	afx_msg void OnSaveAsConfig();
	afx_msg void OnRestoreConfig();
	afx_msg void OnViewConfig();

	DECLARE_MESSAGE_MAP()
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void BeforeDestroy() override;

	ExtensionConfig* m_extensionConfig;
	ExtensionConfig* m_savedConfig;

	unsigned __int64 m_productVersion;
	std::string m_productVersionStr;
	std::string m_productName;
	const char* m_configExtension;

	int m_myWidth;

//	HMODULE m_dllModule;
};

enum WindowToStringContent : unsigned char
{
	WTSC_NONAME,
	WTSC_NOLOCATION,
	WTSC_NODIMENSION,
	WTSC_NOPOPULATION,
	WTSC_NOSTOCKCHAIN,
	WTSC_NOBASKET,

	WTSC_NO_FILTER_STOCK_LIST,
	WTSC_NO_BASKET_CONTENT,

	WTSC_Count
};

class UGUI_API TakionBaseWnd : public
#ifdef BASE_IS_FRAME
CFrameWnd
#else
CWnd
#endif
{
public:
	virtual bool isChild() const{return false;}
	const char* GetClassName() const{return m_className.c_str();}
	static const char* GetDefaultClassName(){return defaultClassName.c_str();}
//	TakionMainWnd* GetMainWnd(){return m_mainWnd;}
	static MainMessageLoopWnd* GetMainWnd(){return m_mainWnd;}
	static VisualBase* GetTakionVisual(){return m_visualBase;}
	static ConfigBase* GetTakionConfig(){return m_configBase;}
	static MainMessageLoopWnd* m_mainWnd;
	static VisualBase* m_visualBase;
	static ConfigBase* m_configBase;
//	void SetMenuItemBitmapsCheck(CMenu& menu, unsigned int id);
//	void SetMenuItemBitmapsRadio(CMenu& menu, unsigned int id);
	const bool& isMenuDisplayed() const{return m_menuDisplayed;}
	const bool& isMouseNcInside() const{return m_ncMouseInside;}
	const bool& isSizeMove() const{return m_sizemove;}
	virtual const char* GetToolId() const{return "";}
	virtual std::string GetDefaultGraphicsId() const{return std::string(GetToolId());}
/*
	static void CalculateTextWidth(CRect& rect, CDC* dc, const char* text, int& width);
	static int CalculateTextWidthAndHeight(CRect& rect, CDC* dc, const char* text, int& width);
	static void AdjustTextWidth(CRect& rect, CDC* dc, const char* text, int& width);
	static void AdjustTextWidthAndHeight(CRect& rect, CDC* dc, const char* text, int& width, int& height);
	static void CalculateCharWidth(CRect& rect, CDC* dc, const char letter, int& width);
	static int CalculateCharWidthAndHeight(CRect& rect, CDC* dc, const char letter, int& width);
	static void AdjustCharWidth(CRect& rect, CDC* dc, const char letter, int& width);
	static void AdjustCharWidthAndHeight(CRect& rect, CDC* dc, const char letter, int& width, int& height);
*/
	static void CalculateTextWidth(CRect& rect, HDC dc, const char* text, int& width);
	static int CalculateTextWidthAndHeight(CRect& rect, HDC dc, const char* text, int& width);
	static void AdjustTextWidth(CRect& rect, HDC dc, const char* text, int& width);
	static void AdjustTextWidthAndHeight(CRect& rect, HDC dc, const char* text, int& width, int& height);
	static void CalculateCharWidth(CRect& rect, HDC dc, const char letter, int& width);
	static int CalculateCharWidthAndHeight(CRect& rect, HDC dc, const char letter, int& width);
	static void AdjustCharWidth(CRect& rect, HDC dc, const char letter, int& width);
	static void AdjustCharWidthAndHeight(CRect& rect, HDC dc, const char letter, int& width, int& height);

	virtual HINSTANCE GetTakionInstanceHandle() const{return AfxGetInstanceHandle();}
protected:
//	TakionBaseWnd(TakionMainWnd* mainWnd, const char* className);
	TakionBaseWnd(MainMessageLoopWnd* mainWnd, const char* className);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct){}
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct){return false;}
	void AddMenuSeparator(CMenu& menu) const
	{
		if(menu.GetMenuItemCount())
		{
			menu.AppendMenu(MF_SEPARATOR);
//			menu.m_hMenu;
//			m_menuHasSeparator = true;
		}
	}
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcMouseLeave();
	afx_msg void OnEnterMenuLoop(BOOL bIsTrackPopupMenu);
    afx_msg void OnExitMenuLoop(BOOL bIsTrackPopupMenu);
	afx_msg void OnEnterSizeMove();
	afx_msg void OnExitSizeMove();
	afx_msg void OnCaptureChanged(CWnd* wnd);
	DECLARE_MESSAGE_MAP()
	std::string m_className;
	static const std::string defaultClassName;
	virtual void OnMouseForcedReleaseCapture();
	virtual void NcMouseEntered(){}
	virtual void NcMouseLeft(){}
//	TakionMainWnd* m_mainWnd;
//	static MainMessageLoopWnd* m_mainWnd;
//	static VisualBase* m_visualBase;
//	static ConfigBase* m_configBase;

	bool m_ncLButtonDown;
	bool m_ncMouseInside;
	bool m_menuDisplayed;
	bool m_sizemove;
};

class UGUI_API GraphicsColorCollection
{
public:
	GraphicsColorCollection(const unsigned int& ordinal, const unsigned short& count = 0):
		m_color(nullptr),
		m_ordinal(ordinal),
		m_count(0),
		m_custom(false)
	{
		SetCount(count);
	}
	~GraphicsColorCollection(){Cleanup();}
	const COLORREF* GetColorArray() const{return m_color;}
	COLORREF* GetColorArray(){return m_color;}
	const COLORREF* GetColorAt(const unsigned int& at) const{return at < m_count ? m_color + at : nullptr;}
	bool SetColorAt(const unsigned int& at, const COLORREF& color)
	{
		if(at < m_count)
		{
			m_color[at] = color;
			return true;
		}
		return false;
	}
	void SetColors(const COLORREF* color, unsigned short count)
	{
		if(m_color)
		{
			COLORREF* dst = m_color;
			if(count > m_count)count = m_count;
			for(; count; --count, ++dst, ++color)
			{
				*dst = *color;
			}
		}
	}
	bool InitColor(COLORREF& color, const unsigned short& ordinal) const
	{
		if(m_color && ordinal < m_count)
		{
			const COLORREF c = m_color[ordinal];
			if(c != color)
			{
				color = c;
				return true;
			}
		}
		return false;
	}
	const unsigned short& GetCount() const{return m_count;}
	void SetCount(const unsigned short& count);
	const bool& isCustom() const{return m_custom;}
	bool SetCustom(const bool& custom)
	{
		if(custom != m_custom)
		{
			m_custom = custom;
			return true;
		}
		return false;
	}
	const unsigned int& GetOrdinal() const{return m_ordinal;}
protected:
	void Cleanup();
	COLORREF* m_color;
	unsigned int m_ordinal;
	unsigned short m_count;
	bool m_custom;
};

class UGUI_API TakionFrame : public TakionBaseWnd
{
friend class MainMessageLoopWnd;
public:
	static const unsigned int maxUInt;//=0xFFFFFFFF
	virtual ~TakionFrame();
	virtual COLORREF GetBkColor() const{return m_backgroundColor;}//m_bkColor;}

	virtual COLORREF GetTitleColorActive() const{return m_titleColorActive;}
	virtual COLORREF GetTitleColorInactive() const{return m_titleColorInactive;}
	virtual COLORREF GetTitleColorTextActive() const{return m_titleColorTextActive;}
	virtual COLORREF GetTitleColorTextInactive() const{return m_titleColorTextInactive;}

	const COLORREF& GetTitleColorActiveScrolled() const{return m_titleColorActiveScrolled;}
	const COLORREF& GetTitleColorInactiveScrolled() const{return m_titleColorInactiveScrolled;}
	const COLORREF& GetTitleColorTextActiveScrolled() const{return m_titleColorTextActiveScrolled;}
	const COLORREF& GetTitleColorTextInactiveScrolled() const{return m_titleColorTextInactiveScrolled;}

	virtual const char* GetWindowName() const{return "";}
	virtual std::string GetHelpUrl() const;
	virtual void Help();

	static const int toolBitmapSize = 22;

	static void CalculateSystemRects(CRect& totalRect, CRect& primaryScreenRect, CRect& primaryDesktopRect);
	static void GetMonitorFromPoint(RECT& rect, const CPoint& point);

	virtual bool GetCurrentFontParams(std::string& title, FontDescription& fontDescription, FontDescription& fontDescriptionCustom, bool& custom, unsigned int& id) const;
	virtual void SetCustomFont(const FontDescription& fontDescription, bool custom, unsigned int id);
	virtual void SetCustomColors(const Graphics* graphics, GraphicsColorCollection* colorCollection, const COLORREF* colors, unsigned short colorCount, bool custom, const FilterStringAsNumberArray& title);//, const FilterStringAsNumberArray& title, unsigned int colorId) override;

//	virtual bool isScrollable() const{return false;}

	void SetBkColor(COLORREF color);

	const int& GetMinVisibleSize() const{return m_minVisibleSize;}
	const int& GetMinWidth() const{return m_minWidth;}
	const int& GetMaxWidth() const{return m_maxWidth;}
	const int& GetMinHeight() const{return m_minHeight;}
	const int& GetMaxHeight() const{return m_maxHeight;}

	const CRect& GetWindowClientRect() const{return m_clientRect;}

	virtual void toString(std::string& str, unsigned int contentModifier) const;
	virtual void fromString(const char*& cursor, unsigned __int64 version, bool clone, unsigned int contentModifier);
	virtual void fromScratch(){}

	virtual bool CreateTakionWnd(const CRect* rect, bool adjustToScreen);

	virtual const char* GetSettingsTabPath(const CPoint& point) const{return nullptr;}
	virtual const void* GetSettingsTabInitInfo(const CPoint& point) const{return nullptr;}
	virtual const void* GetGraphicsTabInitInfo(const CPoint& point) const{return nullptr;}

	virtual void SetTakionNamedFilter(TakionFilter* filter, const std::string& name){}
	virtual void NullifyNamedFilter(){}
	void ApplyFilter(const TakionFilter& filter, bool forceFilterChanged = false)//, unsigned int doNotCopyFlags)
	{
		const TakionFilter* currentFilter = GetFilter();
		if(!currentFilter || filter != *currentFilter)
		{
			const TakionFilter* namedFilter = GetTakionNamedFilter();
			if(namedFilter && !namedFilter->isIntersectionEqual(filter))//, doNotCopyFlags))
			{
				NullifyNamedFilter();
			}
			DoApplyFilter(filter, forceFilterChanged);
		}
		else if(forceFilterChanged)
		{
			DoApplyFilter(filter, forceFilterChanged);
		}
	}
	virtual void LeaveFilter(){}
	virtual const TakionFilter* GetFilter() const{return nullptr;}
	virtual const TakionFilter* GetTakionNamedFilter() const{return nullptr;}

	virtual void SetCommandToolOrdinal(unsigned int ordinal){}
//	void IdleInterrupted();
//	void IdleResumed();

	const CRect& GetScreenRect() const{return m_screenRect;}
	const CRect& GetDesktopRect() const{return m_desktopRect;}
	const CRect& GetTotalScreenRect() const{return m_totalScreenRect;}
	const CRect& GetFrameRect() const{return m_frameRect;}
	virtual const CRect& GetNormalRect() const{return m_frameRect;}

	virtual void UpdateSystemRects();
	virtual void AdjustFrameRect();
	virtual LRESULT GetHitTest(const CPoint& point) const{return HTCAPTION;}
	virtual int GetInitialLeft() const;
	virtual int GetInitialTop() const;
	virtual int GetInitialWidth() const;
	virtual int GetInitialHeight() const;
	virtual CMenu* GetSysMenu() const{return nullptr;}

	virtual void AcceptText(const char* text, unsigned int code){}
	virtual void AcceptPrice(const Price& price, unsigned int code){}
	virtual void AcceptDate(const unsigned int& date, unsigned int code){}

	const bool& isActive() const{return m_active;}
	const bool& isMinimized() const{return m_minimized;}
	const bool& isMouseLeftButtonDown() const{return m_mouseLeftButtonDown;}
	virtual bool ProcessKeyDown(unsigned char key, unsigned char modifier, bool repeat, TakionFrame* fromWindow);
	virtual bool ProcessKeyUp(unsigned char key, unsigned char modifier, TakionFrame* fromWindow){return false;}

	bool isPointInBorder(const CPoint& point) const;
	void InvalidateBorder();

	COLORREF GetLightColor() const{return m_lightColor;}
	COLORREF GetDarkColor() const{return m_darkColor;}

	const bool& isMouseInside() const{return m_mouseInside;}
	const bool& isMouseInClientRect() const{return m_mouseInClientRect;}
//	bool isMouseNcInside() const{return m_ncMouseInside;}
//	bool isSizeMove() const{return m_sizemove;}

	void MoveToFrameRect(bool adjustToInsideScreen, bool newWindow);

//	virtual void SetCustomFont(const FontDescription& fontDescription, bool custom, unsigned int id){}
//	virtual void SetCustomColors(const Graphics* graphics, GraphicsColorCollection* colorCollection, const COLORREF* colors, unsigned short colorCount, bool custom, const FilterStringAsNumberArray& title){}//, unsigned int colorId){}
	void GetPopupDlgRectFromDimensions(int w, int h, RECT& r) const;
	virtual int GetScrollHorizontalOffset() const{return 0;}
	virtual int GetScrollVerticalOffset() const{return 0;}
//	virtual void OnMouseForcedReleaseCapture(){}

	virtual bool ToggleMaximized(){return false;}//returns true if maximized; false if restored

	const CPoint& GetRButtonDownPoint() const{return m_rButtonDownPoint;}

	typedef std::set<unsigned int> UIntSet;
	static void CalculateStartFontSize(const UIntSet& sizeSet, UIntSet::const_iterator& it, const UIntSet::const_iterator& sizeSetBegin, const UIntSet::const_iterator& sizeSetEnd, unsigned int& result, short direction);

	virtual bool isRemoved() const{return false;}

	void Corner();

	virtual bool isInRectForClientMenu(const CPoint& point) const;
	CDC& GetOwnDc(){return m_dc;}
	unsigned char UpdateMouseArea(MouseArea& mouseArea, const CPoint& point);
	inline void InvalidateRectIfValid(const RECT* rect) const{if(m_hWnd)::InvalidateRect(m_hWnd, rect, FALSE);}
	void InvalidateClientRect() const{InvalidateRectIfValid(&m_clientRect);}

	const bool& isCreatedSuccessfully() const{return m_createdSuccessfully;}
	virtual bool isTool() const{return false;}
	virtual const unsigned int& GetToolOrdinal() const{return maxUInt;}
	virtual bool isCommandTool() const{return false;}
	virtual const unsigned int& GetCommandToolOrdinal() const{return maxUInt;}
	virtual bool isHidden() const{return false;}
	virtual unsigned int GetWorkspace() const{return 0xFFFFFFFF;}
	virtual unsigned int GetLayer() const{return 0xFFFFFFFF;}
	void RepaintTitle() const{InvalidateRectIfValid(&m_titleRect);}//if(m_hWnd)::InvalidateRect(m_hWnd, &m_titleRect, FALSE);}
	int MeasureText(const char* text, CFont* font, int charCount = -1) const;
	int MeasureTextHeight(const char* text, CFont* font, int charCount = -1) const;
	const bool& isLocked() const{return m_locked;}
	virtual void SetLocked(const bool& locked){m_locked = locked;}
	bool isWindowLocked() const;
	virtual int CalculateLeft() const{return m_clientRect.left;}
	virtual int CalculateTop() const{return m_clientRect.top;}
	virtual int CalculateRight() const{return m_clientRect.right;}
	virtual int CalculateBottom() const{return m_clientRect.bottom;}
	virtual int GetLeft() const{return m_clientRect.left;}
	virtual int GetTop() const{return m_clientRect.top;}
	virtual int GetRight() const{return m_clientRect.right;}
	virtual int GetBottom() const{return m_clientRect.bottom;}
protected:
	TakionFrame(MainMessageLoopWnd* mainWnd,
		int minVisibleSize,
		int minWidth,
		int maxWidth,
		int minHeight,
		int maxHeight,
		int borderWidth,
		const char* className,
		COLORREF bkColor = 0);

	virtual void SetFrameRect(const CRect& rect)
	{
		m_frameRect = rect;
	}
	virtual void AfterCloning(){}
	virtual void AfterPasting(){}
	virtual bool AddToToolCollection(){return false;}

	virtual void DoApplyFilter(const TakionFilter& filter, bool forceFilterChanged){}

	int CalculateFont(CFont*& font,
		unsigned int& fontSize,
		const int width,
		const int reserveHeightCount,
		const FontDescription& fontDescription,
		const char* templateStr,
		const UIntSet& sizeSet,
		const UIntSet::const_iterator& sizeSetBegin,
		const UIntSet::const_iterator& sizeSetEnd,
		short direction,
		bool* fit = nullptr);

	int CalculateFontVertically(CFont*& font,
		unsigned int& fontSize,
		const int height,
		const FontDescription& fontDescription,
	//	const char* templateStr,
		const UIntSet& sizeSet,
		const UIntSet::const_iterator& sizeSetBegin,
		const UIntSet::const_iterator& sizeSetEnd,
		short direction,
		bool* fit);

	virtual void OnMouseForcedReleaseCapture();

	virtual void DisplayClientMenu(UINT nFlags, CPoint point);

	virtual void OffsetFrameRectAndMove(int x, int y);

	virtual void PreAddMenuItems(CMenu& menu){}
	virtual void AddMenuItems(CMenu& menu);
	virtual void PostAddMenuItems(CMenu& menu);

	virtual void OnSetBkColor(){}

	virtual bool ResizeMouseArea(const CPoint& point, bool locked){return false;}
	virtual unsigned char UpdateResizeCursor(const CPoint& point, bool locked){return 0;}

	void CreateDcBitmap(CDC* dc, int width, int height);
	void CalculateClientRect(int cx, int cy);

	virtual void DCCreated(){}

	virtual void DisplaySystemMenu(const CPoint& point);

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void BeforeDestroy(){}
	virtual void AfterDestroy(){}
	virtual void BeforeNcDestroy(){}
	virtual void DoActivate(UINT state, bool minimized){}//, CWnd* pWndOther){}
	virtual void MouseEntered(){}
	virtual void MouseLeft(){}
	virtual void MouseEnteredClientRect(){}
	virtual void MouseLeftClientRect(){}
	virtual bool ClientSetCursor(){return false;}
//	virtual void NcMouseEntered(){}
//	virtual void NcMouseLeft(){}
	virtual void DoPaint(const RECT& rcPaint, CDC& dc){}
//	void PreSize(int cx, int cy, int oldX, int oldY);
	virtual void DoSize(UINT nType, int cx, int cy, int oldX, int oldY){}
	virtual void CalculateWindowRect(int x, int y, int width, int height);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSuccessfulCreate(){}
	virtual void OnSuccessfulCreate(){m_createdSuccessfully = true;}
	virtual void DoMinimize(UINT nID, LPARAM lParam){}
	virtual void DoRestore(UINT nID, LPARAM lParam){}
#ifndef BASE_IS_FRAME
	virtual void PostNcDestroy() override;
#endif
	virtual bool RemoveFromVisibleTools(){return true;}
	virtual void AddToVisibleTools(){}
	virtual void OnTitleResize(){}
	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) override;

	DECLARE_MESSAGE_MAP()
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
//	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nCode, UINT nPos, CScrollBar* pScrollBar);
//	afx_msg void OnEnterMenuLoop(BOOL bIsTrackPopupMenu);
//    afx_msg void OnExitMenuLoop(BOOL bIsTrackPopupMenu);
//	afx_msg void OnEnterSizeMove();
	afx_msg void OnExitSizeMove();
	afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);
	afx_msg LRESULT OnKickIdle(WPARAM w, LPARAM l);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
//	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
//	afx_msg void OnNcMouseLeave();
	afx_msg void OnDestroy();
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	afx_msg LRESULT OnDelayedCreation(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnDelayedApplyLayout(WPARAM wparam, LPARAM lparam);

	afx_msg LRESULT OnGetTakionFrameInfo(WPARAM infoType, LPARAM lparam);

	virtual void DelayedCreationDone(){}

	virtual bool GetInsideScreen(CRect& rect) const;

	CBitmap m_dcBitmap;
    CDC m_dc;
//	HMENU m_sysMenu;

	COLORREF m_backgroundColor;

	void SetTakionFrameRect(int x, int y, int width, int height);
	CRect m_frameRect;
	CRect m_winRect;
	CRect m_clientRect;
	CRect m_titleRect;
	CRect m_screenRect;
	CRect m_desktopRect;
	CRect m_totalScreenRect;

	int m_borderWidth;
	int m_systemBorderWidth;
	int m_cornerSize;

	bool m_mouseActivated;
	bool m_active;
//	bool m_sizemove;

	void OnScroll(UINT nCode);
	bool m_scrolling;
	bool m_mouseInside;
	bool m_mouseInClientRect;

	int m_minVisibleSize;
    int m_minWidth;
    int m_maxWidth;
	int m_minHeight;
	int m_maxHeight;

	int m_dcBitmapWidth;
	int m_dcBitmapHeight;

//	bool m_ncMouseInside;
	HCURSOR m_arrowCursor;
	HCURSOR m_cursorMoveOne;
	HCURSOR m_cursorDragOne;

	COLORREF m_titleColorActive;
	COLORREF m_titleColorInactive;
	COLORREF m_titleColorTextActive;
	COLORREF m_titleColorTextInactive;

	COLORREF m_titleColorActiveScrolled;
	COLORREF m_titleColorInactiveScrolled;
	COLORREF m_titleColorTextActiveScrolled;
	COLORREF m_titleColorTextInactiveScrolled;

	bool SetFontTitle(const FontDescription& fontDescription);
	virtual void TitleFontChanged(){}
	bool SetCustomTitleFont(const FontDescription& fontDescription, bool custom);
	FontDescription m_fontDescriptionTitle;
	FontDescription m_fontDescriptionTitleCustom;
	CFont* m_fontTitle;
	bool m_fontTitleCustom;

	COLORREF m_lightColor;
	COLORREF m_darkColor;

	bool m_minimized;
	bool m_mouseLeftButtonDown;
	bool m_createdSuccessfully;

	bool m_locked;

	CPoint m_rButtonDownPoint;

private:
	void ApplyLayout(const char* info, unsigned int contentModifier, bool clone, unsigned __int64 version, const CRect* rect);
};

//#define BASE_IS_FRAME

class UGUI_API TakionPopupWnd : public TakionFrame
{
public:
	TakionPopupWnd(MainMessageLoopWnd* mainWnd, bool reusable, COLORREF bkColor = GetSysColor(COLOR_BTNFACE), unsigned int messageCap = 0xFFFFFFFF, int defaultResult = IDCANCEL);
	virtual bool CreateTakionWnd(const CRect* rect, bool adjustToScreen);

	virtual ~TakionPopupWnd(){ClearCheckBoxes();}
	bool DisplayModeless(CWnd* parent, const char* caption, unsigned int flags, COLORREF bkColor = RGB(0, 0, 128), COLORREF textColor = RGB(255, 255, 255), COLORREF captionColor = 0xFFFFFFFF, COLORREF blinkBkColor = 0xFFFFFFFF, COLORREF blinkTextColor = 0xFFFFFFFF, COLORREF blinkCaptionColor = 0xFFFFFFFF, bool visible = true, unsigned int focusButton = 0, const char* thirdButtonName = nullptr, const char* secondButtonName = nullptr, const char* firstButtonName = nullptr);
	typedef std::list<MessageRect> MessageList;
	void ClearMessageList(bool adjustSize = true);
	bool AddMessage(const char* message, bool adjustSize = true, bool force = false);
	bool AddMessage(const std::string& message, bool adjustSize = true, bool force = false);
	bool SetMessage(unsigned short at, const char* message, bool adjustSize = true);
	bool SetMessage(unsigned short at, const std::string& message, bool adjustSize = true);
	void AddCheckBox(const char* text, bool checked, bool enabled, bool indented, bool adjustSize);// = false);
	bool GetCheckBoxState(unsigned short i) const;
	virtual bool GetInsideScreen(CRect& rect) const;

	void AdjustSize();

	const int& GetResult() const{return m_result;}
	const int& GetDefaultResult() const{return m_defaultResult;}

	void SetBkColor(COLORREF bkColor);

	virtual COLORREF GetBkColor() const{return m_blinkState ? m_blinkBkColor : m_bkColor;}
	COLORREF GetBlinkColor() const{return m_blinkBkColor;}
	void SetBlinkColor(COLORREF color);

	CBrush* GetBkBrush() const{return m_blinkState ? m_blinkBrush : m_brush;}
	void Blink();
	bool GetTotalInsideScreen(CRect& rect) const;
	virtual void Renew(){}
//	virtual void AccountRemoved(const Account* account){}
//	virtual void AllAccountsRemoved(){}
	unsigned int GetMessageCap() const{return m_messageCap;}
	void SetMessageCap(unsigned int messageCap){m_messageCap = messageCap;}
	virtual HINSTANCE GetTakionInstanceHandle() const override;
	virtual void BeforeDestroy() override;
	virtual void UpdateColors()
	{
		m_textColor = m_blinkBkColor;
		m_captionColor = m_textColor;//captionColor == 0xFFFFFFFF ? textColor : captionColor;
		m_blinkTextColor = m_bkColor;
		m_blinkCaptionColor = m_blinkTextColor;
	}
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;
	virtual void OnBlink(){}
	void AddButton(const char* text, unsigned short id);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	HCURSOR m_cursorMove;
	HCURSOR m_cursorDrag;
	virtual INT_PTR PrepareToDisplay(CWnd* parent,
		const char* caption,
		unsigned int flags,
		COLORREF bkColor,
		COLORREF textColor,
		COLORREF captionColor,
		COLORREF blinkBkColor = 0xFFFFFFFF,
		COLORREF blinkTextColor = 0xFFFFFFFF,
		COLORREF blinkCaptionColor = 0xFFFFFFFF,
		unsigned int focusButton = 0,
		const char* thirdButtonName = nullptr,
		const char* secondButtonName = nullptr,
		const char* firstButtonName = nullptr);
	virtual void CalculateSize();
	virtual void MoveFrameRectToInitialPos();
	virtual void DoSize(UINT nType, int cx, int cy, int oldX, int oldY) override;
    virtual void DoPaint(const RECT& rcPaint, CDC& dc) override;
	virtual void DoActivate(UINT state, bool minimized) override;

	virtual void OnSuccessfulCreate() override;

	afx_msg void OnYes();
	afx_msg void OnNo();
	afx_msg void OnOK();
	afx_msg void OnCancel();
//	afx_msg LRESULT OnKickIdle(WPARAM w, LPARAM l);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
	void CloseMessageBox(int result);
	void DestroyWithButton(int result);
	MessageList m_messageList;
	std::string m_caption;
	unsigned int m_flags;
	HICON m_icon;
	CRect m_iconRect;
	CFont* m_captionFont;
	CFont* m_font;
	CFont* m_controlFont;
	CRect m_captionRect;
	COLORREF m_bkColor;
	COLORREF m_textColor;
	COLORREF m_captionColor;
	COLORREF m_blinkBkColor;
	COLORREF m_blinkTextColor;
	COLORREF m_blinkCaptionColor;
	CBrush* m_brush;
	CBrush* m_blinkBrush;
	int m_doubleBorder;
	int m_horOffset;
	int m_verOffset;
	int m_verGap;
	int m_controlVerOffset;
	int m_textWidth;
	typedef std::list<CButton*> ButtonList;
	ButtonList m_buttonList;
	typedef std::list<std::string> StringList;
	StringList m_buttonLabel;
	typedef std::list<unsigned short> UShortList;
	UShortList m_buttonId;
	unsigned int m_buttonCount;
	int m_buttonWidth;
	int m_buttonHeight;
	int m_controlWidth;
	int m_controlHeight;
	int m_buttonYOffset;
	void ClearCheckBoxes();
	typedef std::vector<CheckBoxOwnerDraw*> ButtonVector;
	typedef std::vector<std::string> StringVector;
	typedef std::vector<bool> BoolVector;
	ButtonVector m_checkBoxVector;
	StringVector m_checkBoxLabel;
	BoolVector m_checkBoxState;
	BoolVector m_checkBoxEnabled;
	BoolVector m_checkBoxIndented;

	int m_checkBoxHeight;
	int m_maxCheckBoxWidth;
	unsigned int m_checkBoxCount;
	CSize m_dimensions;
	int m_defaultResult;
	int m_result;
	bool m_destroyedWithButton;
	bool m_blinkState;

	unsigned int m_messageCap;
	bool m_reusable;

	bool m_wasActive;
};

class UGUI_API DialogEntry : public FocusDialog
{
public:
//	virtual void OnOK();
//	virtual void OnCancel();
	void Display(TakionFrame* receipient, CWnd* wndReceipient, unsigned int code, CWnd* parent, int x, int y, int w, int h, bool show = true);
	void SetReceipient(TakionFrame* receipient){m_receipient = receipient;}
	void SetWndReceipient(CWnd* receipient){m_wndReceipient = receipient;}
	unsigned int GetCode() const{return m_code;}
protected:
	DialogEntry(MainMessageLoopWnd* mainWnd, bool toDestroyOnFocus = false, TakionFrame* receipient = nullptr, CWnd* parent = nullptr, LPCSTR caption = nullptr, DWORD style = 0, DWORD exstendedStyle = 0, int x = 0, int y = 0, int w = 0, int h = 0,
		LPCSTR font = nullptr, WORD fontSize = 8, bool executeCommands = true, bool closeOnCommandExecution = true):
		FocusDialog(mainWnd, true, toDestroyOnFocus, parent, caption, style, exstendedStyle, x, y, w, h, font, fontSize, executeCommands, closeOnCommandExecution),
		m_receipient(receipient),
		m_wndReceipient(nullptr),
		m_code(0)
	{
	}
	DialogEntry(MainMessageLoopWnd* mainWnd, TakionFrame* receipient = nullptr, CWnd* parent = nullptr, unsigned int id = 0, bool toDestroyOnFocus = false, bool executeCommands = true, bool closeOnCommandExecution = true):
		FocusDialog(mainWnd, true, parent, id, toDestroyOnFocus, executeCommands, closeOnCommandExecution),
		m_receipient(receipient),
		m_wndReceipient(nullptr),
		m_code(0)
	{}
	virtual bool HandleCommand(const Key& key, bool ctrlChar, bool repeatKey){return false;}
	TakionFrame* m_receipient;
	CWnd* m_wndReceipient;
	unsigned int m_code;
};

class UGUI_API DialogDateEntry : public DialogEntry
{
public:
	static const WORD dateId = 1000;
	DialogDateEntry(MainMessageLoopWnd* const& mainWnd,
		const COLORREF& bkColor,
		const bool& toDestroyOnFocus = false,
		TakionFrame* const& receipient = nullptr,
		CWnd* const& parent = nullptr,
		const bool& executeCommands = true,
		const bool& closeOnCommandExecution = true);

	virtual void OnDeactivate() override
	{
		NullifyValue();
	}
	void NullifyValue();
	void Display(TakionFrame* const& receipient,
		CWnd* const& wndReceipient,
		const unsigned int& code,
		const unsigned int& date,
//		const bool& selectAll,
		CWnd* const& parent,
		const COLORREF& bkColor,
		//		const COLORREF& textColor,
		CFont* const& font,
		const int& x,
		const int& y,
		const int& w,
		const int& h);
	void SetDate(const unsigned int& date);
	unsigned int GetControlDate() const;

	ColorDateTimeCtrl& GetDateCtrl(){return m_DateCtrl;}
	const ColorDateTimeCtrl& GetDateCtrl() const{return m_DateCtrl;}
	const unsigned int& GetValueResult() const{return m_valueResult;}
	virtual HWND GetFirstTabControl() const override{return m_DateCtrl.m_hWnd;}
protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg) override;
	virtual void DoDataExchange(CDataExchange* pDX) override
	{
		DialogEntry::DoDataExchange(pDX);
		DDX_Control(pDX, dateId, m_DateCtrl);
	}

	DECLARE_MESSAGE_MAP()


//	afx_msg void OnDateChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCalendarDropdown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCalendarCloseup(NMHDR* pNMHDR, LRESULT* pResult);

	virtual void BeforeShow() override;
	virtual void Apply() override;
	virtual void Resize(bool widthChanged = true, bool heightChanged = true) override;

	virtual void ToolTipsEnabled(bool enable) override
	{
		DialogEntry::ToolTipsEnabled(enable);
		m_DateCtrl.EnableTooltips(enable, m_toolTip);
	}
	ColorDateTimeCtrl m_DateCtrl;// (unsigned short idleCode, COLORREF bkColor, const char* tooltipText = nullptr);

//	COLORREF m_spinBkColor;
//	COLORREF m_spinTextColor;
	unsigned int m_valueResult;
	CFont* m_font;
};



template<class V>
class DialogSpinEntry : public DialogEntry
{
public:
	static const WORD spinId = 1000;
	typedef V ValueType;
	DialogSpinEntry(MainMessageLoopWnd* const& mainWnd,
		NumberTypeSpin<ValueType>* const& spin,
		const bool& toDestroyOnFocus = false,
		TakionFrame* const& receipient = nullptr,
		CWnd* const& parent = nullptr,
		const bool& executeCommands = true,
		const bool& closeOnCommandExecution = true):

		DialogEntry(mainWnd,
			toDestroyOnFocus,
			receipient,
			parent,
			nullptr,
			WS_POPUP | WS_CLIPCHILDREN, WS_EX_TRANSPARENT, 0, 0, 0, 0, nullptr, 0,
			executeCommands,
			closeOnCommandExecution),
		m_Spin(spin),
		m_spinBkColor(GetSysColor(COLOR_WINDOW)),
		m_spinTextColor(GetSysColor(COLOR_WINDOWTEXT)),
		m_font(nullptr)
	{
		AddComponentIndirect(TakionSpin::takionSpinClassName, nullptr,
			WS_CHILD | WS_VISIBLE | WS_TABSTOP, WS_EX_TRANSPARENT,
			0, 0, 0, 0, spinId);
	}
	virtual void OnDeactivate() override
	{
		NullifyValue();
	}
	void NullifyValue()
	{
		if(m_Spin->m_hWnd)
		{
			m_Spin->SetValue(0, false, true, false);
		}
		m_valueResult = 0;
	}
	void Display(TakionFrame* const& receipient,
		CWnd* const& wndReceipient,
		const unsigned int& code,
		const ValueType& value,
		const bool& selectAll,
		CWnd* const& parent,
		const COLORREF& bkColor,
		const COLORREF& textColor,
		CFont* const& font,
		const int& x,
		const int& y,
		const int& w,
		const int& h)
	{
		m_Spin->SetBkColorEnabled(bkColor);
		m_font = font ? font : m_visualBase->GetFont(GetFont());

		DialogEntry::Display(receipient, wndReceipient, code, parent, x, y, w, h);
		if(m_hWnd)
		{
			if(m_font)
			{
				SetFont(m_font, false);
				m_Spin->SetMyFont(m_font);
			}
			SetValue(value);
			if(selectAll)m_Spin->SelectAll();
		}
	}
	virtual HWND GetFirstTabControl() const override{return m_Spin->m_hWnd;}
	void SetValue(const ValueType& value)
	{
		m_Spin->SetValue(value, true, true, false);
	}
	void SelectAll()
	{
		m_Spin->SelectAll();
	}
	NumberTypeSpin<ValueType>* GetSpin(){return m_Spin;}
	const NumberTypeSpin<ValueType>* GetSpin() const{return m_Spin;}
	const ValueType& GetValueResult() const{return m_valueResult;}
protected:
//	virtual bool HandleCommand(const Key& key, bool ctrlChar, bool repeatKey){return false;}
	virtual BOOL PreTranslateMessage(MSG* pMsg) override
	{
		if(pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN)
		{
			unsigned char key = (unsigned char)pMsg->wParam;
			switch(key)
			{
				case VK_RETURN:
				return DialogEntry::PreTranslateMessage(pMsg);

				case VK_ESCAPE:
				case VK_LWIN:
				case VK_RWIN:
				case VK_APPS:
				return CDialog::PreTranslateMessage(pMsg);

				case VK_CAPITAL:
				case VK_SHIFT:
				case VK_CONTROL:
				case VK_MENU:
				case VK_NUMLOCK:
				case VK_SCROLL:
				break;

				default:
				{
					const unsigned char modifier = UGUI_GetKeyModifier();
					bool ctrlChar = false;
					if(HandleCommand(Key(key, modifier), ctrlChar, (pMsg->lParam & repeatBit) != 0))
					{
						return TRUE;
					}
					else if(ctrlChar || (modifier & (KM_CTRL_LEFT | KM_CTRL_RIGHT | KM_ALT_LEFT | KM_ALT_RIGHT)) != 0)
					{
						OnCancel();
						return TRUE;
					}
				}
				break;
			}
			return CDialog::PreTranslateMessage(pMsg);
		}
		return DialogEntry::PreTranslateMessage(pMsg);
	}
	virtual void DoDataExchange(CDataExchange* pDX) override
	{
		DialogEntry::DoDataExchange(pDX);
		DDX_Control(pDX, spinId, *m_Spin);
	}

	virtual void Apply() override
	{
		m_valueResult = m_Spin->GetValue();
/*
		if(m_receipient)
		{
			m_receipient->AcceptNumber(m_valueResult, m_code);//We don't know which type of number it is
		}
*/
		if(m_wndReceipient)
		{
			m_wndReceipient->PostMessage(WM_USER + 999, m_code, 0);
		}
	}
	virtual void Resize(bool widthChanged = true, bool heightChanged = true) override
	{
		DialogEntry::Resize(widthChanged, heightChanged);
		if(m_Spin->m_hWnd)
		{
			::SetWindowPos(m_Spin->m_hWnd, HWND_TOP, 0, 0, m_clientRect.right, m_clientRect.bottom, SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOOWNERZORDER|SWP_DEFERERASE);
		}
	}
	virtual void ToolTipsEnabled(bool enable) override
	{
		DialogEntry::ToolTipsEnabled(enable);
		m_Spin->EnableTooltips(enable, m_toolTip);
	}

	NumberTypeSpin<ValueType>* m_Spin;

	COLORREF m_spinBkColor;
	COLORREF m_spinTextColor;
	ValueType m_valueResult;
	CFont* m_font;
};

class UGUI_API DialogSpinPriceEntry : public DialogSpinEntry<unsigned __int64>
{
public:
	DialogSpinPriceEntry(MainMessageLoopWnd* const& mainWnd,
		const ValueType& maxValue,
		const ValueType& minValue,
//		NumberTypeSpin<V>* spin,
		const bool& toDestroyOnFocus = false,
		TakionFrame* const& receipient = nullptr,
		CWnd* const& parent = nullptr,
		const bool& executeCommands = true,
		const bool& closeOnCommandExecution = true):

		DialogSpinEntry(mainWnd,
			&m_SpinControl,
			toDestroyOnFocus,
			receipient,
			parent,
			executeCommands,
			closeOnCommandExecution),
		m_SpinControl(maxValue, minValue, minValue <= 0 ? 0 : minValue, 1000, 3, TakionSpin::charComma, 4)
	{
		AddPriceSpinCells(m_SpinControl);
	}
	static void AddPriceSpinCells(UnsignedNumberTypeSpin<ValueType>& spin)
	{
		spin.AddSpinCell(1, false);
		spin.AddSpinCell(100, false);
		spin.AddSpinCell(10000, false);
		spin.AddSpinCell(100000000, true);
		spin.AddSpinCell(1000000, true);
	}
	static Price GetPriceFromNumber(unsigned __int64 number)
	{
		unsigned __int64 dollars = number / 10000;
		number -= dollars * 10000;
		return Price((unsigned int)dollars, (unsigned int)number * (Price::divider / 10000));
	}

	static unsigned __int64 GetNumberFromPrice(const Price& price)
	{
		return (unsigned __int64)price.GetDollars() * 10000 + price.GetDollarFraction() / (Price::divider / 10000);
	}
	void Display(TakionFrame* const& receipient, CWnd* const& wndReceipient, const unsigned int& code, const Price& price, const bool& selectAll, CWnd* const& parent,
		const COLORREF& bkColor, const COLORREF& textColor, CFont* const& font, const int& x, const int& y, const int& w, const int& h)
	{
		DialogSpinEntry::Display(receipient, wndReceipient, code, GetNumberFromPrice(price), selectAll, parent, bkColor, textColor, font, x, y, w, h);
	}
protected:
	virtual void Apply() override
	{
		DialogSpinEntry::Apply();
		if(m_receipient)
		{
			m_receipient->AcceptPrice(GetPriceFromNumber(m_valueResult), m_code);
		}
	}
	UnsignedNumberTypeSpin<ValueType> m_SpinControl;
};

class UGUI_API DialogTextEntry : public DialogEntry
{
public:
	DialogTextEntry(MainMessageLoopWnd* mainWnd,
		bool toDestroyOnFocus = false,
		TakionFrame* receipient = nullptr,
		CWnd* parent = nullptr,
		const char* charSet = nullptr,
		bool exclude = true,
		bool uppercase = true,
		bool lowercase = false,
		bool scroll = true,
		bool readonly = false,
		bool multiline = false,
		bool executeCommands = true,
		bool closeOnCommandExecution = true);
//	virtual void OnOK();
	void AddChar(unsigned char key, bool setFocus = true);
	virtual void OnDeactivate();
//	virtual COLORREF GetBkColor() const{return RGB(255, 0, 0);}
	void Display(bool variableSize, bool alwaysUseShiftForTyping, TakionFrame* receipient, CWnd* wndReceipient, unsigned int code, CWnd* parent,
		const char* charSet, bool exclude, bool firstCharDifferent, const char* firstCharSet, bool firstCharExclude, const char* additionalFirstCharSet,
		COLORREF bkColor, COLORREF textColor, unsigned int textLen, CFont* font, int x, int y, int w, int h, bool uppercase = true, bool lowercase = false);
	void ExpandForChar(char c);
	void AddValidChar(char v, bool exclude){m_EditText.AddValidChar(v, exclude);}
	void AddValidChars(const char* v, bool exclude){m_EditText.AddValidChars(v, exclude);}
	void SetText(const char* text);
	void SelectAll();
	ValidEdit& GetEditText(){return m_EditText;}
//	virtual void OnOK();
//	virtual void OnCancel();
	const std::string& GetTextResult() const{return m_textResult;}
protected:
//	virtual bool HandleCommand(const Key& key, bool ctrlChar, bool repeatKey){return false;}
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void Apply() override;
//	virtual void BeforeDestroy() override;
//	virtual void DoFinishDialog(int result);
	ValidEdit m_EditText;
//	unsigned short m_editId;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTextUpdate();
//	afx_msg void OnChar(UINT, UINT, UINT); // for character validation
//	afx_msg void OnTextChange();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
//	int m_result;
	bool m_variableSize;
	bool m_useShiftForTyping;
	bool m_alwaysUseShiftForTyping;
	COLORREF m_editBkColor;
	COLORREF m_editTextColor;
	unsigned int m_textLen;
	std::string m_textResult;
	CBrush* m_editBrush;
	CFont* m_font;
};

class UGUI_API DialogReset : public DialogEntry
{
public:
	void Display(TakionFrame* receipient, unsigned int code, CWnd* parent, int x, int y, int w, int h, bool show = true);
	virtual bool DoReset(){return false;}
	virtual bool isChanged() const{return false;}
	virtual bool isValid() const{return true;}
	int GetMinWidth() const{return m_minWidth;}
	int GetMinHeight() const{return m_minHeight;}
	int GetMaxWidth() const{return m_maxWidth;}
	int GetMaxHeight() const{return m_maxHeight;}
	virtual HWND GetFirstTabControl() const override{return m_ButtonCancel.m_hWnd;}
protected:
	DialogReset(MainMessageLoopWnd* mainWnd,
		bool toDestroyOnFocus = false,
		TakionFrame* receipient = nullptr,
		CWnd* parent = nullptr,
		LPCSTR caption = nullptr,
		DWORD style = 0,
		DWORD exstendedStyle = 0,
		int x = 0,
		int y = 0,
		int w = 0,
		int h = 0,
		LPCSTR font = nullptr,
		WORD fontSize = 8,
		bool executeCommands = true,
		bool closeOnCommandExecution = true);

	DialogReset(MainMessageLoopWnd* mainWnd,
		TakionFrame* receipient = nullptr,
		CWnd* parent = nullptr,
		unsigned int id = 0,
		bool toDestroyOnFocus = false,
		bool executeCommands = true,
		bool closeOnCommandExecution = true):
		DialogEntry(mainWnd,
			receipient,
			parent,
			id,
			toDestroyOnFocus,
			executeCommands,
			closeOnCommandExecution),
		m_minWidth(0),
		m_minHeight(0),
		m_maxWidth(0),
		m_maxHeight(0)
	{
	}

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void InitializeValues(){ResetAndEnableOkButton();}
	void ResetAndEnableOkButton();
	void AddButtons(int y, int buttonWidth, int buttonHeight, int buttonGapH, int buttonGapV, const char* okButtonLabel = nullptr, const char* applyButtonLabel = nullptr, const char* cancelButtonLabel = nullptr);
	CButton m_ButtonOk;
	CButton m_ButtonApply;
	CButton m_ButtonCancel;
	CButton m_ButtonReset;
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnReset();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	DECLARE_MESSAGE_MAP()
	virtual void FinishDialog(int result);
	virtual void BeforeShow();
	virtual void Apply();
	virtual void DoApply();
	virtual void EnableOkButton();
	virtual void DoEnableOkButton(bool enable);
	int m_minWidth;
	int m_minHeight;
	int m_maxWidth;
	int m_maxHeight;
};

class UGUI_API DialogResetTitle : public DialogReset
{
//public:
//	void Display(TakionFrame* receipient, unsigned int code, CWnd* parent, int x, int y, int w, int h, bool show = true);
protected:
	DialogResetTitle(MainMessageLoopWnd* mainWnd,
		const char* title,
		int titleWidth,
		int xOffset,
		int yOffset,
		bool toDestroyOnFocus = false,
		TakionFrame* receipient = nullptr,
		CWnd* parent = nullptr,
		LPCSTR caption = nullptr,
		DWORD style = 0,
		DWORD exstendedStyle = 0,
		int x = 0,
		int y = 0,
		int w = 0,
		int h = 0,
		LPCSTR font = nullptr,
		WORD fontSize = 8,
		bool executeCommands = true,
		bool closeOnCommandExecution = true,
		WORD titleId = IDS_TITLE,
		int titleHeight = 8);
/*
	DialogResetTitle(MainMessageLoopWnd* mainWnd,
		TakionFrame* receipient = nullptr,
		CWnd* parent = nullptr,
		unsigned int id = 0,
		bool toDestroyOnFocus = false,
		bool executeCommands = true,
		bool closeOnCommandExecution = true):
		DialogReset(mainWnd,
			receipient,
			parent,
			id,
			toDestroyOnFocus,
			executeCommands,
			closeOnCommandExecution)
	{
	}
*/
	virtual BOOL OnInitDialog();

	CStatic m_StaticTitle;
	virtual void DoDataExchange(CDataExchange* pDX);

	int m_xOffset;
	int m_yOffset;
	int m_bottomY;
	int m_rightWidth;//in dialog units
	int m_titleRight;//in pixels
	int m_titleBottom;//in pixels
	int m_titleHeight;//in pixels
//	DECLARE_MESSAGE_MAP()
};


class UGUI_API DialogResetClear : public DialogReset
{
public:
	void Display(TakionFrame* receipient, unsigned int code, CWnd* parent, int x, int y, int w, int h, bool show = true);
	virtual bool DoClear(){return false;}
	void EnableClearButton();
	virtual bool isClear() const{return true;}
protected:
	DialogResetClear(MainMessageLoopWnd* mainWnd,
		bool toDestroyOnFocus = false,
		TakionFrame* receipient = nullptr,
		CWnd* parent = nullptr,
		LPCSTR caption = nullptr,
		DWORD style = 0,
		DWORD exstendedStyle = 0,
		int x = 0,
		int y = 0,
		int w = 0,
		int h = 0,
		LPCSTR font = nullptr,
		WORD fontSize = 8,
		bool executeCommands = true,
		bool closeOnCommandExecution = true);
/*
	DialogResetClear(MainMessageLoopWnd* mainWnd, TakionFrame* receipient = nullptr, CWnd* parent = nullptr, unsigned int id = 0, bool toDestroyOnFocus = false, bool executeCommands = true, bool closeOnCommandExecution = true):
		DialogReset(mainWnd, receipient, parent, id, toDestroyOnFocus, executeCommands, closeOnCommandExecution)
	{
	}
*/
	CButton m_ButtonClear;
	virtual void DoDataExchange(CDataExchange* pDX);
	void DoEnableClearButton(bool enable);

	afx_msg void OnClear();
	DECLARE_MESSAGE_MAP()
};

class UGUI_API DialogFilter : public DialogResetClear
{
public:
	virtual ~DialogFilter();
	void Display(const TakionFilter& filter, TakionFrame* receipient, unsigned int code, CWnd* parent, int x, int y, int w, int h, bool show = true);
	const TakionFilter* GetFilter() const{return m_filter;}
	virtual bool isFilterChanged() const{return false;}
	virtual bool isFilterValid() const{return true;}
	virtual bool isFilterEmpty() const{return true;}
	virtual void SetFilterEmpty(){}

	virtual bool DoReset();
	virtual bool isChanged() const{return isFilterChanged();}

	virtual bool DoClear();
	virtual bool isClear() const{return isFilterEmpty();}
	const int& GetLeftHandSideButtonEnd() const{return m_leftHandSideButtonEnd;}
	const int& GetRightHandSideButtonStart() const{return m_rightHandSideButtonStart;}
	const int& GetButtonTop() const{return m_buttonTop;}

	static const int okButtonWidth = 25;
	static const int buttonWidth = 32;
	static const int buttonHeight = 14;
	static const int buttonGapV = 4;
	static const int buttonGapH = 2;

	TakionFilter* CreateFilterCopy() const{return m_filter ? m_filter->CreateFilterCopy() : nullptr;}
	virtual void UpdateFilterOfOtherKind(TakionFilter& other) const{}
	virtual bool isFilterOfOtherKindIntersectionDifferent(const TakionFilter& other) const{return false;}
	virtual void CopyFilterOfOtherKindToControls(const TakionFilter& filter){}
protected:
	DialogFilter(MainMessageLoopWnd* mainWnd, bool toDestroyOnFocus = false, TakionFrame* receipient = nullptr, CWnd* parent = nullptr, LPCSTR caption = nullptr, DWORD style = 0, DWORD exstendedStyle = 0, int x = 0, int y = 0, int w = 0, int h = 0,
		LPCSTR font = nullptr, WORD fontSize = 8, bool executeCommands = true, bool closeOnCommandExecution = true);
//	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void BeforeShow(){}
	virtual void DoApply();
	virtual void DialogCancelled();
	virtual BOOL OnInitDialog();
//	virtual void Resize(bool widthChanged = true, bool heightChanged = true);
	virtual void FinishDialog(int result);

//	virtual void BeforeShow();
//	void EnableOkButton();
//	void DoEnableOkButton();
	virtual void UpdateFilterValues(){}

	TakionFilter* m_filter;
	int m_leftHandSideButtonEnd;
	int m_rightHandSideButtonStart;
	int m_buttonTop;

//	bool m_tooltipsEnabled;

//	afx_msg void OnClear();
//	DECLARE_MESSAGE_MAP()

//	CButton m_ButtonClear;
};

class UGUI_API DialogValueReset : public DialogReset
{
public:
	void Display(TakionFrame* receipient, unsigned int code, CWnd* parent, const CPoint& mousePoint, int w, int h);//, bool show = true);
protected:
	DialogValueReset(MainMessageLoopWnd* mainWnd,
		CWnd* rightmostControl,
		bool toDestroyOnFocus = false,
		TakionFrame* receipient = nullptr,
		CWnd* parent = nullptr,
		LPCSTR caption = nullptr,
		DWORD style = 0,
		DWORD exstendedStyle = 0,
		int x = 0,
		int y = 0,
		int w = 0,
		int h = 0,
		LPCSTR font = nullptr,
		WORD fontSize = 8,
		bool executeCommands = true,
		bool closeOnCommandExecution = true);
//	DialogValueReset(MainMessageLoopWnd* mainWnd, CWnd* rightmostControl, TakionFrame* receipient = nullptr, CWnd* parent = nullptr, unsigned int id = 0, bool toDestroyOnFocus = false, bool executeCommands = true, bool closeOnCommandExecution = true);
	virtual BOOL OnInitDialog();
	virtual void FinishDialog(int result);
	virtual void Resize(bool widthChanged = true, bool heightChanged = true);
	virtual void MoveControls(bool moveDialog);
	CWnd* m_rightmostControl;
	int m_valuesHeight;
	int m_valuesWidth;
	int m_controlHeight;
	int m_controlWidth;
	int m_clientWidth;
	int m_buttonWidth;
	int m_buttonHeight;
	int m_gapV;

	static const int buttonWidth = 32;
	static const int buttonHeight = 14;
	static const int buttonGapV = 2;
	static const int buttonGapH = 2;

	static const int spinHeight = 12;
	static const int checkBoxHeight = 8;
	static const int staticHeight = 8;
};

/////
class UGUI_API DialogDuration : public DialogValueReset
{
public:
	DialogDuration(MainMessageLoopWnd* mainWnd, bool toDestroyOnFocus = false, TakionFrame* receipient = nullptr, CWnd* parent = nullptr);
	void Display(TakionFrame* receipient, unsigned int code, unsigned short startMinute, unsigned short durationMinute, CWnd* parent, const CPoint& mousePoint);//, int x, int y, int w, int h);
	unsigned short GetStart() const{return m_start;}
	unsigned short GetDuration() const{return m_duration;}
	enum TakionDurationDialogIds : unsigned int
	{
		staticStartId = 1000,
		staticDurationId,
		spinStartId,
		spinDurationId,

		takionDurationDialogIdCount
	};
	virtual bool DoReset();
	virtual bool isChanged() const;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void DoApply();
//	virtual BOOL OnInitDialog();
//	virtual void Resize(bool widthChanged = true, bool heightChanged = true);
//	virtual void FinishDialog(int result);
	afx_msg LRESULT OnSpinChange(WPARAM spinId, LPARAM l);
	DECLARE_MESSAGE_MAP()

	CStatic m_StaticStart;
	CStatic m_StaticDuration;
	MinuteSpin m_SpinStart;
	MinuteSpin m_SpinDuration;
	unsigned short m_start;
	unsigned short m_duration;
	unsigned short m_currentStart;
	unsigned short m_currentDuration;
/*
	int m_spinHeight;
	int m_spinWidth;
	int m_controlHeight;
	int m_controlWidth;
	int m_clientWidth;
	int m_buttonWidth;
	int m_buttonHeight;
	int m_gapV;
	void MoveControls(bool moveDialog);

	static const int buttonWidth = 32;
	static const int buttonHeight = 14;
	static const int buttonGapV = 2;
	static const int buttonGapH = 2;
*/
	static const int staticWidth = 28;
	static const int spinWidth = 40;
};

class UGUI_API DialogUIntBase : public DialogValueReset
{
public:
	void Display(TakionFrame* const receipient,
		const unsigned int& code,
		bool zeroValid,
		CWnd* const& parent,
		const CPoint& mousePoint,
		const char* const& title,// = nullptr,
		const char* const& caption,// = nullptr,
		const unsigned int& notificationId,
		const char* spinToolTip);// = 0)
protected:
	DialogUIntBase(MainMessageLoopWnd* mainWnd, TakionSpin* spinControl, int w, int h, int spinWidth,
		int titleWidth, const char* title, int captonHeight, const char* caption,
		bool toDestroyOnFocus = false, TakionFrame* receipient = nullptr, CWnd* parent = nullptr, const unsigned int& defaultNotificationId = 44);
	virtual void ToolTipsEnabled(bool enable) override;
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnSpinChange(WPARAM spinId, LPARAM l);
	DECLARE_MESSAGE_MAP()
	TakionSpin* m_spinControl;
	CStatic m_StaticTitle;
	CStatic m_StaticCaption;
	virtual void ValueSpinned(){}
	std::string m_title;
	std::string m_caption;
	int m_w;
	int m_h;
	unsigned int m_defaultNotificationId;
	unsigned int m_notificationId;
	int m_captionWidth;
	int m_captionHeight;
	int m_captionX;
	bool m_zeroValid;
};

template<class V>//, V MaxSpin = 1000>
class DialogNumber : public DialogUIntBase
{
public:
	typedef V ValueType;
	void Display(TakionFrame* const receipient,
		const unsigned int& code,
		const bool& zeroValid,
		CWnd* const& parent,
		const ValueType& value,
		const ValueType& maxValue,
		const ValueType& minValue,
		const CPoint& mousePoint,
		const char* const& title = nullptr,
		const char* const& caption = nullptr,
		const unsigned int& notificationId = 0,
		const char* spinToolTip = nullptr)
	{
//		m_StaticTitle.SetWindowText(title ? title : m_title.c_str());
//		m_StaticCaption.SetWindowText(caption ? caption : m_caption.c_str());
//		m_SpinValue.SetMinMaxValue(minValue, maxValue);
		m_value = value;
		m_maxValue = maxValue;
		m_minValue = minValue;
//		m_notificationId = notificationId ? notificationId : m_defaultNotificationId;
		DialogUIntBase::Display(receipient, code, zeroValid, parent, mousePoint, title, caption, notificationId, spinToolTip);

		m_spinControl->SetBkColorEnabled(!m_zeroValid && !value ? m_visualBase->GetGrayColor() : 0xFFFFFFFF);
	}
	const ValueType& GetValue() const{return m_value;}
	const ValueType& GetCurrentValue() const{return m_currentValue;}
	
	virtual bool isChanged() const
	{
		return m_currentValue != m_value;
	}
	virtual bool DoReset()
	{
		bool ret = false;
		if(m_currentValue != m_value)
		{
			ret = true;
			m_currentValue = m_value;
		}
		if(DoUpdateSpinValue())
		{
			ret = true;
		}
		return ret;
	}
	virtual const ValueType& GetSpinValue() const = 0;
protected:
	DialogNumber(MainMessageLoopWnd* const& mainWnd, TakionSpin* spinControl, const ValueType& maxValue, const ValueType& minValue, const int& w, const int& h, const int& spinWidth,
		const int& titleWidth, const char* const& title, const int& captonHeight, const char* const& caption,
		const bool& toDestroyOnFocus = false, TakionFrame* const& receipient = nullptr, CWnd* const& parent = nullptr, const unsigned char& decDigits = 0, const unsigned int& defaultNotificationId = 44):
		DialogUIntBase(mainWnd, spinControl, w, h, spinWidth,
			titleWidth, title, captonHeight, caption,
			toDestroyOnFocus, receipient, parent, defaultNotificationId),
		m_value(0),
		m_currentValue(0),
		m_maxValue(maxValue),
		m_minValue(minValue)
	{
	} 
	virtual bool DoUpdateSpinValue() = 0;
	virtual void ValueSpinned()
	{
		const ValueType prevValue = m_currentValue;
		m_currentValue = GetSpinValue();//m_SpinValue.GetValue();
		if(m_currentValue != m_value)DoEnableOkButton(true);
		else EnableOkButton();
		if(!m_zeroValid && !m_currentValue != !prevValue)
		{
			m_spinControl->SetBkColorEnabled(!m_currentValue ? m_visualBase->GetGrayColor() : 0xFFFFFFFF);
		}
	}
	virtual void DoApply()
	{
		m_value = m_currentValue;
		if(m_receipient && m_notificationId)
		{
//			m_receipient->PostMessage(WM_USER + 44, m_value, 0);
			m_receipient->PostMessage(WM_USER + m_notificationId, m_value, m_code);
		}
	}
//	UnsignedNumberTypeSpin<V> m_SpinValue;
	ValueType m_value;
	ValueType m_currentValue;
	ValueType m_maxValue;
	ValueType m_minValue;
//	unsigned int m_defaultNotificationId;
//	unsigned int m_notificationId;
};

template<class V>//, V MaxSpin = 1000>
class DialogInt : public DialogNumber<V>//, MaxSpin>
{
public:
	typedef V ValueType;
	DialogInt(MainMessageLoopWnd* const& mainWnd, const ValueType& maxValue, const ValueType& minValue, const int& w, const int& h, const int& spinWidth,
		const int& titleWidth, const char* const& title, const int& captonHeight, const char* const& caption,
		const bool& toDestroyOnFocus = false, TakionFrame* const& receipient = nullptr, CWnd* const& parent = nullptr, const unsigned char& decDigits = 0, const unsigned int& defaultNotificationId = 44):
		DialogNumber(mainWnd, &m_SpinValue, maxValue, minValue, w, h, spinWidth,
			titleWidth, title, captonHeight, caption,
			toDestroyOnFocus, receipient, parent, defaultNotificationId),
//		m_SpinValue(maxValue, minValue, 0, MaxSpin, 3, TakionSpin::charComma, decDigits)
		m_SpinValue(maxValue, minValue, 0, 1000, 3, TakionSpin::charComma, decDigits)
	{
	}
	void Display(TakionFrame* const receipient,
		const unsigned int& code,
		const bool& zeroValid,
		CWnd* const& parent,
		const ValueType& value,
		const ValueType& maxValue,
		const ValueType& minValue,
		const CPoint& mousePoint,
		const char* const& title = nullptr,
		const char* const& caption = nullptr,
		const unsigned int& notificationId = 0,
		const char* spinToolTip = nullptr)
	{
		m_SpinValue.SetMinMaxValue(minValue, maxValue);
		DialogNumber::Display(receipient, code, zeroValid, parent, value, maxValue, minValue, mousePoint, title, caption, notificationId, spinToolTip);
	}
	virtual const ValueType& GetSpinValue() const{return m_SpinValue.GetValue();}
protected:
	virtual bool DoUpdateSpinValue()
	{
		if(m_SpinValue.SetValue(m_value))
		{
			m_SpinValue.UpdateValueNum();
			return true;
		}
		return false;
	}
	SignedNumberTypeSpin<V> m_SpinValue;
};

template<class V>//, V MaxSpin = 1000>
class DialogUInt : public DialogNumber<V>//, MaxSpin>
{
public:
	typedef V ValueType;
	DialogUInt(MainMessageLoopWnd* const& mainWnd, const ValueType& maxValue, const ValueType& minValue, const int& w, const int& h, const int& spinWidth,
		const int& titleWidth, const char* const& title, const int& captonHeight, const char* const& caption,
		const bool& toDestroyOnFocus = false, TakionFrame* const& receipient = nullptr, CWnd* const& parent = nullptr, const unsigned char& decDigits = 0, const unsigned int& defaultNotificationId = 44):
		DialogNumber(mainWnd, &m_SpinValue, maxValue, minValue, w, h, spinWidth,
			titleWidth, title, captonHeight, caption,
			toDestroyOnFocus, receipient, parent, defaultNotificationId),
//		m_SpinValue(maxValue, minValue, 0, MaxSpin, 3, TakionSpin::charComma, decDigits)
		m_SpinValue(maxValue, minValue, 0, 1000, 3, TakionSpin::charComma, decDigits)
	{
	}
	void Display(TakionFrame* const receipient,
		const unsigned int& code,
		const bool& zeroValid,
		CWnd* const& parent,
		const ValueType& value,
		const ValueType& maxValue,
		const ValueType& minValue,
		const CPoint& mousePoint,
		const char* const& title = nullptr,
		const char* const& caption = nullptr,
		const unsigned int& notificationId = 0,
		const char* spinToolTip = nullptr)
	{
		m_SpinValue.SetMinMaxValue(minValue, maxValue);
		DialogNumber::Display(receipient, code, zeroValid, parent, value, maxValue, minValue, mousePoint, title, caption, notificationId, spinToolTip);
	}
	virtual const ValueType& GetSpinValue() const{return m_SpinValue.GetValue();}
protected:
	virtual bool DoUpdateSpinValue()
	{
		if(m_SpinValue.SetValue(m_value))
		{
			m_SpinValue.UpdateValueNum();
			return true;
		}
		return false;
	}
	UnsignedNumberTypeSpin<V> m_SpinValue;
};

class UGUI_API DialogTime : public DialogValueReset
{
public:
	DialogTime(MainMessageLoopWnd* mainWnd, bool showMilliseconds, unsigned int maxValue, const unsigned int& minValue, bool toDestroyOnFocus = false, TakionFrame* receipient = nullptr, CWnd* parent = nullptr);
	void Display(TakionFrame* receipient, unsigned int code, unsigned int millisecond, CWnd* parent, const CPoint& mousePoint);//, int x, int y, int w, int h);
	unsigned int GetMillisecond() const{return m_millisecond;}
	
	virtual bool isChanged() const;
	virtual bool DoReset();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void DoApply();
//	virtual BOOL OnInitDialog();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	virtual void Resize(bool widthChanged = true, bool heightChanged = true);
//	virtual void FinishDialog(int result);
//	virtual void BeforeShow();
//	afx_msg void OnReset();
	afx_msg LRESULT OnSpinChange(WPARAM spinId, LPARAM l);
	DECLARE_MESSAGE_MAP()
//	void EnableOkButton();
//	void DoEnableOkButton(bool enable);
	TimeSpin m_SpinTime;
	unsigned int m_millisecond;
	unsigned int m_currentMillisecond;
/*
	int m_spinHeight;
	int m_spinWidth;
	int m_controlHeight;
	int m_controlWidth;
	int m_clientWidth;
	int m_buttonWidth;
	int m_buttonHeight;
	int m_gapV;
	void MoveControls(bool moveDialog);
*/
};

class UGUI_API DialogFilterHighlightSize : public DialogValueReset
{
public:
//	DialogFilterHighlightSize(TakionMainWnd* mainWnd, bool toDestroyOnFocus = false, TakionFrame* receipient = nullptr, CWnd* parent = nullptr);
/*
	unsigned short GetMinDimension() const{return m_minDimension;}
	unsigned short GetMaxDimension() const{return m_maxDimension;}
	unsigned int GetVolumePerPixel() const{return m_volumePerPixel;}
*/
	const bool& isUseFilter() const{return m_useFilter;}
	const bool& isUseHighlight() const{return m_useHighlight;}
	const unsigned int& GetFilterSize() const{return m_filterSize;}
	const unsigned int& GetHighlightSize() const{return m_highlightSize;}

	const bool& isCurrentUseFilter() const{return m_currentUseFilter;}
	const bool& isCurrentUseHighlight() const{return m_currentUseHighlight;}
	const unsigned int& GetCurrentFilterSize() const{return m_currentFilterSize;}
	const unsigned int& GetCurrentHighlightSize() const{return m_currentHighlightSize;}

	void Display(TakionFrame* receipient,
		unsigned int code,
		unsigned int filterSize,
		unsigned int highlightSize,
		bool useFilter,
		bool useHighlight,
		unsigned char filterHighlightSizeMask,
		CWnd* parent,
		const CPoint& mousePoint);

	enum TakionFilterHighlightSizeIds : unsigned int
	{
		checkBoxUseFilterId = 1000,
		spinFilterId,

		checkBoxUseHighlightId,
		spinHighlightId,

		takionFilterHighlightSizeIdCount
	};
	virtual bool DoReset() override;
	virtual bool isChanged() const override;
protected:
	DialogFilterHighlightSize(MainMessageLoopWnd* mainWnd, const char* filterLabel, const char* highlightLabel, bool toDestroyOnFocus = false, TakionFrame* receipient = nullptr, CWnd* parent = nullptr);
//	void Display(TakionFrame* receipient, unsigned int code, unsigned short startMinute, unsigned short durationMinute, CWnd* parent, const CPoint& mousePoint);//, int x, int y, int w, int h);

	virtual void ToolTipsEnabled(bool enable) override;

	virtual BOOL OnInitDialog() override;
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void DoApply() override;
	afx_msg void OnUseFilter();
	afx_msg void OnUseHighlight();
	afx_msg LRESULT OnSpinChange(WPARAM spinId, LPARAM l);
	DECLARE_MESSAGE_MAP()
/*
	UnsignedNumberTypeSpin<unsigned short> m_SpinMinDimension;
	UnsignedNumberTypeSpin<unsigned int> m_SpinVolumePerPixel;
	UnsignedNumberTypeSpin<unsigned short> m_SpinMaxDimension;

	unsigned short m_minDimension;
	unsigned short m_maxDimension;
	unsigned int m_volumePerPixel;

	unsigned short m_currentMinDimension;
	unsigned short m_currentMaxDimension;
	unsigned int m_currentVolumePerPixel;
*/
	CheckBoxOwnerDraw m_CheckBoxUseFilter;
	CheckBoxOwnerDraw m_CheckBoxUseHighlight;
	UnsignedNumberTypeSpin<unsigned int> m_SpinFilter;
	UnsignedNumberTypeSpin<unsigned int> m_SpinHighlight;

	bool m_useFilter;
	bool m_useHighlight;
	unsigned int m_filterSize;
	unsigned int m_highlightSize;

	bool m_currentUseFilter;
	bool m_currentUseHighlight;
	unsigned int m_currentFilterSize;
	unsigned int m_currentHighlightSize;

//	void CurrentFilterSizeChanged(unsigned int prevSize);
//	void CurrentHighlightSizeChanged(unsigned int prevSize);
//	static const int staticWidth = 30;
};

/////

class UGUI_API DialogFourSeconds : public DialogValueReset
{
public:
	const unsigned int& GetSecond1() const{return m_second1;}
	const unsigned int& GetSecond2() const{return m_second2;}
	const unsigned int& GetSecond3() const{return m_second3;}
	const unsigned int& GetSecond4() const{return m_second4;}

	const unsigned int& GetCurrentSecond1() const{return m_currentSecond1;}
	const unsigned int& GetCurrentSecond2() const{return m_currentSecond2;}
	const unsigned int& GetCurrentSecond3() const{return m_currentSecond3;}
	const unsigned int& GetCurrentSecond4() const{return m_currentSecond4;}

	void Display(TakionFrame* receipient,
		unsigned int code,
		unsigned int second1,
		unsigned int second2,
		unsigned int second3,
		unsigned int second4,
		CWnd* parent,
		const CPoint& mousePoint,
		const char* label1 = nullptr,
		const char* label2 = nullptr,
		const char* label3 = nullptr,
		const char* label4 = nullptr);

	enum TakionFilterHighlightSizeIds : unsigned int
	{
		staticSecond1Id = 1000,
		spinSecond1Id,

		staticSecond2Id,
		spinSecond2Id,

		staticSecond3Id,
		spinSecond3Id,

		staticSecond4Id,
		spinSecond4Id,

		takionDialogFourSecondsIdCount
	};
	virtual bool DoReset() override;
	virtual bool isChanged() const override;
protected:
	DialogFourSeconds(MainMessageLoopWnd* mainWnd,
		const char* label1,
		const char* label2,
		const char* label3,
		const char* label4,
		bool toDestroyOnFocus = false,
		TakionFrame* receipient = nullptr,
		CWnd* parent = nullptr);

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void DoApply() override;
	afx_msg LRESULT OnSpinChange(WPARAM spinId, LPARAM l);
	DECLARE_MESSAGE_MAP()
	CStatic m_StaticSecond1;
	CStatic m_StaticSecond2;
	CStatic m_StaticSecond3;
	CStatic m_StaticSecond4;
	TimeSpin m_SpinSecond1;
	TimeSpin m_SpinSecond2;
	TimeSpin m_SpinSecond3;
	TimeSpin m_SpinSecond4;

	const char* m_label1;
	const char* m_label2;
	const char* m_label3;
	const char* m_label4;

	bool UpdateCurrentSecond(const TimeSpin& spin, unsigned int& currentSecond, const unsigned int& second);

	virtual void Second1Changed(){}
	virtual void Second2Changed(){}
	virtual void Second3Changed(){}
	virtual void Second4Changed(){}

	unsigned int m_second1;
	unsigned int m_second2;
	unsigned int m_second3;
	unsigned int m_second4;

	unsigned int m_currentSecond1;
	unsigned int m_currentSecond2;
	unsigned int m_currentSecond3;
	unsigned int m_currentSecond4;
};


class UGUI_API DialogStringSelection : public DialogReset
{
public:
	void Display(TakionFrame* receipient, unsigned int code, CWnd* parent, int x, int y, int w, int h,
		const char* title,
		const char* editString,
		unsigned int windowsMessage,
		bool uppercase,
		bool lowercase,
		bool selectionOnly,
		bool okOnDblClk,
		bool clearBox);
	virtual bool DoReset();
	virtual bool isChanged() const;
	enum DialogStringSelectionIds : unsigned int
	{
		staticTitleId = 1000,
		editStringId,
		listBoxStringId,

		DialogStringSelectionIdCount
	};
	bool ResetContent();
	bool RemoveString(const char* str);
	bool AddString(const char* str, bool select = false);
	const std::string& GetTitle() const{return m_title;}
	const std::string& GetEditInitialString() const{return m_editInitialString;}
	const std::string& GetEditString() const{return m_editString;}
	virtual bool isValid() const{return !m_editString.empty() && !m_alreadyApplied;}
#if(_MSC_VER > 1600)
	typedef std::unordered_set<FilterStringAsNumberArray, TakionHashValue<FilterStringAsNumberArray> > StringSet;
#else
	typedef std::hash_set<FilterStringAsNumberArray> StringSet;
#endif
protected:
	DialogStringSelection(MainMessageLoopWnd* mainWnd,
		unsigned int windowsMessage,
		bool toDestroyOnFocus = false,
		TakionFrame* receipient = nullptr,
		CWnd* parent = nullptr,
		LPCSTR caption = nullptr,
		DWORD style = 0,
		DWORD exstendedStyle = 0,
		int x = 0,
		int y = 0,
		int w = 0,
		int h = 0,
		LPCSTR font = nullptr,
		WORD fontSize = 8,
		bool executeCommands = true,
		bool closeOnCommandExecution = true);
/*
	DialogStringSelection(MainMessageLoopWnd* mainWnd, unsigned int windowsMessage, TakionFrame* receipient = nullptr, CWnd* parent = nullptr, unsigned int id = 0, bool toDestroyOnFocus = false, bool executeCommands = true, bool closeOnCommandExecution = true):
		DialogReset(mainWnd, receipient, parent, id, toDestroyOnFocus, executeCommands, closeOnCommandExecution),
		m_windowsMessage(windowsMessage),
		m_uppercase(false),
		m_lowercase(false),
		m_selectionOnly(false),
		m_okOnDblClk(false),
		m_clearBox(false),
		m_setTitle(false),
		m_alreadyApplied(false),
		m_lbTop(0),
		m_buttonWidth(0),
		m_buttonHeight(0),
		m_gapH(0),
		m_gapV(0),
		m_staticHeight(0),
		m_editHeight(0),
		m_appliedStringsEnd(m_appliedStrings.cend())
	{
	}
*/
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void BeforeShow();
	virtual void DoApply();
	virtual BOOL OnInitDialog();
	virtual void Resize(bool widthChanged = true, bool heightChanged = true);
	virtual void FinishDialog(int result);
	virtual void EnableOkButton();
	virtual void DoEnableOkButton(bool enable);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEditStringChange();
	afx_msg void OnSelchangeString();
	afx_msg void OnDblClkString();
	DECLARE_MESSAGE_MAP()

	CStatic m_StaticTitle;
	EditNoContext m_EditString;
	ListBoxString m_ListBoxString;
	CButton m_ButtonHelp;

	std::string m_title;
	std::string m_editInitialString;
	std::string m_editString;

	unsigned int m_windowsMessage;

	bool m_uppercase;
	bool m_lowercase;
	bool m_selectionOnly;
	bool m_okOnDblClk;
	bool m_clearBox;
	bool m_setTitle;

	bool m_alreadyApplied;
/*
	int m_minWidth;
	int m_minHeight;
	int m_maxWidth;
	int m_maxHeight;
*/
	int m_lbTop;
	int m_buttonWidth;
	int m_buttonHeight;
	int m_gapH;
	int m_gapV;
	int m_staticHeight;
	int m_editHeight;

	StringSet m_appliedStrings;
	StringSet::const_iterator m_appliedStringsEnd;
};

class UGUI_API DialogResetCustom : public DialogReset
{
public:
	enum TakionDialogResetCustomIds : unsigned int
	{
		customCheckBoxId = 1000,
		DialogResetCustomIdCount,
	};
	const bool& isCustom() const{return m_custom;}
	const bool& isCurrentCustom() const{return m_currentCustom;}
	void Display(TakionFrame* receipient, bool custom, unsigned int code, CWnd* parent, int x, int y, int w, int h, bool show);
	virtual bool isChanged() const override{return m_currentCustom != m_custom;}
	virtual bool DoReset(){return SetCustom(m_custom);}
	bool SetCustom(const bool custom);
protected:
	DialogResetCustom(MainMessageLoopWnd* mainWnd,
		bool toDestroyOnFocus = false,
		TakionFrame* receipient = nullptr,
		CWnd* parent = nullptr,
		LPCSTR caption = nullptr,
		DWORD style = 0,
		DWORD exstendedStyle = 0,
		int x = 0,
		int y = 0,
		int w = 0,
		int h = 0,
		LPCSTR font = nullptr,
		WORD fontSize = 8,
		bool executeCommands = true,
		bool closeOnCommandExecution = true,
		const char* checkBoxCustomToolTip = nullptr):
		DialogReset(mainWnd,
			toDestroyOnFocus,
			receipient,
			parent,
			caption,
			style,
			exstendedStyle,
			x,
			y,
			w,
			h,
			font,
			fontSize,
			executeCommands,
			closeOnCommandExecution),
		m_CheckBoxCustom(checkBoxCustomToolTip),
		m_currentCustom(false),
		m_custom(false),
		m_checkBoxHeight(0)
	{
	}
/*
	DialogResetCustom(MainMessageLoopWnd* mainWnd, TakionFrame* receipient = nullptr, CWnd* parent = nullptr, unsigned int id = 0, bool toDestroyOnFocus = false,
		bool executeCommands = true, bool closeOnCommandExecution = true, const char* checkBoxCustomToolTip = nullptr):
		DialogReset(mainWnd, receipient, parent, id, toDestroyOnFocus, executeCommands, closeOnCommandExecution),
		m_CheckBoxCustom(checkBoxCustomToolTip),
		m_currentCustom(false),
		m_custom(false),
		m_checkBoxHeight(0)
	{
	}
*/
	virtual BOOL OnInitDialog();
	virtual void CustomModified() = 0;
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void ToolTipsEnabled(bool enable) override;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCustom();
	ButtonToolTip m_CheckBoxCustom;
	CButton m_ButtonHelp;
	DECLARE_MESSAGE_MAP()
	bool m_currentCustom;
	bool m_custom;
	int m_checkBoxHeight;
};

class UGUI_API DialogResetCustomDefault : public DialogResetCustom
{
public:
	enum TakionDialogResetCustomDefaultIds : unsigned int
	{
		buttonDefaultId = DialogResetCustom::DialogResetCustomIdCount,
		DialogResetCustomDefaultIdCount,
	};
//	void Display(TakionFrame* receipient, unsigned int code, const char* title, CWnd* parent, int x, int y, int w, int h, bool custom, unsigned int id);
	void Display(TakionFrame* receipient, bool custom, unsigned int code, CWnd* parent, int x, int y, int w, int h, bool show);

	virtual bool isDefaultChanged() const{return false;}
protected:
	DialogResetCustomDefault(MainMessageLoopWnd* mainWnd,
		int width,
		int okVOffset,
		bool toDestroyOnFocus = false, TakionFrame* receipient = nullptr, CWnd* parent = nullptr, LPCSTR caption = nullptr, DWORD style = 0, DWORD exstendedStyle = 0,
		const char* checkBoxCustomToolTip = nullptr, const char* buttonDefaultToolTip = nullptr):
		DialogResetCustom(mainWnd, toDestroyOnFocus, receipient, parent, caption, style, exstendedStyle, 0, 0, 0, 0, nullptr, 0, true, true, checkBoxCustomToolTip),
		m_ButtonDefault(buttonDefaultToolTip),
		m_modified(false)
	{
	}
	virtual void ToolTipsEnabled(bool enable) override;

	virtual void DoDataExchange(CDataExchange* pDX);
//	virtual BOOL OnInitDialog() override;
	afx_msg void OnDefault();
	DECLARE_MESSAGE_MAP()

	virtual void FinishDialog(int result) override;

	virtual void DoDefault();

	virtual void DoEnableOkButton(bool enable);

	void EnableDefaultButton()
	{
		EnableControl(m_ButtonDefault.m_hWnd, isDefaultChanged(), m_ButtonCancel.m_hWnd);
	}
//	void DoEnableDefaultButton(bool enable){}

	ButtonToolTip m_ButtonDefault;
/*
	int m_titleHeight;
	int m_buttonWidth;
	int m_buttonHeight;
	int m_buttonGapV;

	int m_x;
	int m_y;
*/
	bool m_modified;
};

class UGUI_API DialogResetCustomGraphics : public DialogResetCustomDefault
{
public:
	enum TakionDialogResetCustomGraphicsIds : unsigned int
	{
		titleStaticId = DialogResetCustomDefault::DialogResetCustomDefaultIdCount,
//		buttonDefaultId,
		DialogResetCustomGraphicsIdCount,
	};
	static const int buttonHeight = 12;//14;
	static const int buttonWidth = 30;//28;
	static const int buttonGapV = 2;//4;
	static const int buttonGapH = 2;
	static const int checkBoxHeight = 8;//10
	static const int staticHeight = 8;
	static const int gapv = 2;
	static const int lbGap = 1;
//	virtual bool isChanged() const override{return m_modified;}
	void Display(TakionFrame* receipient, unsigned int code, const char* title, CWnd* parent, int x, int y, int w, int h, bool custom, unsigned int id);

//	virtual bool isDefaultChanged() const{return false;}
protected:
	DialogResetCustomGraphics(MainMessageLoopWnd* mainWnd,
		int width,
		int okVOffset,
		bool toDestroyOnFocus = false, TakionFrame* receipient = nullptr, CWnd* parent = nullptr, LPCSTR caption = nullptr, DWORD style = 0, DWORD exstendedStyle = 0, int xcOffset = 1);
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog() override;
//	afx_msg void OnDefault();
	DECLARE_MESSAGE_MAP()

/*
	virtual void FinishDialog(int result) override;
	virtual void DoDefault();
	virtual void DoEnableOkButton(bool enable);
	void EnableDefaultButton()
	{
		EnableControl(m_ButtonDefault.m_hWnd, isDefaultChanged(), m_ButtonCancel.m_hWnd);
	}
*/
//	void DoEnableDefaultButton(bool enable){}

	CStatic m_StaticTitle;
//	CButton m_ButtonDefault;

	int m_titleHeight;
	int m_buttonWidth;
	int m_buttonHeight;
	int m_buttonGapV;

	int m_x;
	int m_y;
	int m_xc;//left offset of leftmost controls
//	bool m_modified;
};

class UGUI_API DialogFont : public DialogResetCustomGraphics
{
public:
	DialogFont(MainMessageLoopWnd* mainWnd, bool toDestroyOnFocus = false, TakionFrame* receipient = nullptr, CWnd* parent = nullptr);

	static const int fontLbWidth = 100;
	static const int fontSizeLbWidth = 25;

	void Display(TakionFrame* receipient, unsigned int code, const char* title, CWnd* parent, int x, int y, int w, int h, const FontDescription& fontDescription, const FontDescription& fontDescriptionCustom, bool custom, unsigned int id);
	static const char* const sampleText;
	void GetCurrentFontDescription(FontDescription& fontDescription) const;
//	void SetCustomFont();
	void SetDefaultFont();
//	void ResetFont();

	virtual bool DoReset() override;
	virtual bool isChanged() const override;
	virtual bool isValid() const override;

	virtual bool isDefaultChanged() const override;
protected:
	virtual void ToolTipsEnabled(bool enable) override;
	virtual void CustomModified();
	virtual void DoDataExchange(CDataExchange* pDX) override;
	virtual void BeforeShow() override;
	virtual void DoApply() override;
	virtual BOOL OnInitDialog() override;
	virtual void Resize(bool widthChanged = true, bool heightChanged = true) override;
	virtual void FinishDialog(int result) override;
	void SetInitialParams(const char* name, unsigned int size, unsigned int maxSize, bool bold, bool italic, bool custom);//, bool setCustomCheckBox);
//	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSelchangeFont();
	afx_msg void OnSelchangeFontSize();
	afx_msg void OnSelchangeFontMaxSize();
	afx_msg void OnBold();
	afx_msg void OnItalic();
//	afx_msg void OnSampleUpdate();
//	afx_msg void OnCustom();
//	afx_msg void OnReset();
	DECLARE_MESSAGE_MAP()

	virtual void DoDefault() override;

	bool UpdateFontSize();
	bool UpdateFontMaxSize();

	void DrawSmallFont();
//	void DrawBigFont();

//	bool m_showMaxSize;
//	void RememberCustomFont();
	FontDescription m_fontDescription;//from Graphic
	FontDescription m_fontDescriptionCustom;
//	FontDescription m_fontDescriptionCurrent;
	FontDescription m_fontDescriptionInitial;
	unsigned int m_fontId;

	ListBoxFont m_ListBoxFont;
	ListBoxUInt<unsigned int> m_ListBoxSize;
	ListBoxUInt<unsigned int> m_ListBoxMaxSize;
	CStatic m_StaticFontName;
	CStatic m_StaticSizeName;
	CStatic m_StaticMaxSizeName;
	EditNoContext m_EditFontSample;
//	EditNoContext m_EditBigFontSample;
	CButton m_CheckBoxBold;
	CButton m_CheckBoxItalic;
//	CButton m_CheckBoxCustom;
//	CButton m_ButtonHelp;

	int m_currentFontSelection;
	unsigned int m_currentSizeSelection;
	unsigned int m_currentMaxSizeSelection;

	unsigned int m_selectedSize;
	unsigned int m_selectedMaxSize;
/*
	unsigned int m_minWidth;
	unsigned int m_minHeight;
	unsigned int m_maxHeight;
*/
	unsigned int m_eohHeight;
	unsigned int m_eohOrigBottom;

//	int m_fontWidth;
	int m_sizeWidth;
	int m_maxSizeWidth;
	int m_lbLeft;
	int m_lbTop;

	int m_fontOffset;
	int m_sizeOffset;
	int m_maxSizeOffset;
};

class UGUI_API ListBoxNamedColorCustom : public ListBoxNamedColor
{
public:
	ListBoxNamedColorCustom(FocusDialog* parentDlg, bool own = true, bool rbuttonSelection = true, bool rbuttonMenu = true):
		ListBoxNamedColor(own, rbuttonSelection, rbuttonMenu),
		m_parentDlg(parentDlg)
	{
	}
protected:
	virtual void BeforeColorDialogShow()
	{
		m_parentDlg->PretendNotDisplayed();
	}
	virtual void AfterColorDialogShow()
	{
		m_parentDlg->UnpretendNotDisplayed();
	}
	FocusDialog* m_parentDlg;
};

class UGUI_API DialogGraphicsColor : public DialogResetCustomGraphics
{
public:
	DialogGraphicsColor(MainMessageLoopWnd* mainWnd, bool toDestroyOnFocus = false, TakionFrame* receipient = nullptr, CWnd* parent = nullptr);
	virtual ~DialogGraphicsColor(){ClearColors();}
	static const int colorLbWidth;
	void Display(TakionFrame* receipient,
		unsigned int code,
		const FilterStringAsNumberArray& title,
		CWnd* parent,
		int x, int y, int w, int h,
		const Graphics* graphics,
		GraphicsColorCollection* colorCollection);

	const FilterStringAsNumberArray& GetTitle() const{return m_title;}
	const unsigned int& GetColorId() const{return m_colorId;}

	void SetDefaultColors();
	virtual bool isDefaultChanged() const override;
	virtual bool DoReset() override;
	virtual bool isChanged() const override;

protected:
	virtual void CustomModified();
	virtual void DoDataExchange(CDataExchange* pDX) override;
	virtual void BeforeShow() override;
	virtual void DoApply() override;
	virtual BOOL OnInitDialog() override;
	virtual void Resize(bool widthChanged = true, bool heightChanged = true) override;
	virtual void FinishDialog(int result) override;
	void SetInitialParams(const COLORREF* m_color, unsigned short count, bool custom, bool setCustomCheckBox);

	afx_msg void OnSelchangeColor();
	afx_msg void OnDoubleClickColor();
	afx_msg LRESULT OnColorChange(WPARAM w, LPARAM l);
	DECLARE_MESSAGE_MAP()

	virtual void DoDefault() override;

	ListBoxNamedColorCustom m_ListBoxColor;

	FilterStringAsNumberArray m_title;

	const Graphics* m_graphics;
	GraphicsColorCollection* m_colorCollection;

	unsigned int m_colorId;

	void ClearColors();
	const Graphics::ColorVector* m_colors;
//	COLORREF* m_colorsCustom;
	COLORREF* m_colorsInitial;
	unsigned short m_colorCount;

	int m_currentColorSelection;
	int m_lbTop;
	int m_lbLeft;
};

/*
class UGUI_API ListBoxTitleLine : public ListBoxOrdinal
{
public:
	ListBoxTitleLine():ListBoxOrdinal(0, true, true, true){}
//	virtual const char* GetItemName(const void* item) const;
protected:
	virtual void DestroyItem(const void* item) const override;
	virtual void AddMenuItems(CMenu& menu) override;
	virtual void DrawMenuItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
	virtual bool MeasureMenuItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) override;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
};
*/
/*
class UGUI_API TakionSettingSecurityTitle : public TakionSettingNamedValue
{
public:
	virtual void UpdateSettings();
	virtual bool ClearItems();
protected:
	TakionSettingSecurityTitle(MainMessageLoopWnd* mainWnd,
		TakionSettingTabDialog* parentTab,
		ConfigBase::StringVectorVector& valuesSetting,
		BoolSetting& alignSetting,
		const char* label,
		int lbWidth,
		int hOffset,
		bool tooltips,
		bool removeByDragging);
	virtual void Entering() override;
	virtual void DoApplyInitInfo() override;
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void LBItemDraggedAndDropped(unsigned int ctrlId, unsigned short from, unsigned short to) override;// unsigned int itemOrdinal);
	virtual void LBDragDropDone(unsigned int ctrlId, int itemOrdinalOld, int itemOrdinalNew) override;
	virtual void LBDragDropAbort(unsigned int ctrlId, int itemOrdinal) override;
	afx_msg void OnSelchangeLine();
	afx_msg LRESULT OnTitleLinesAdded(WPARAM w, LPARAM l);
	afx_msg LRESULT OnTitleLinesRemoved(WPARAM w, LPARAM l);
	afx_msg LRESULT OnTitleLineMove(WPARAM w, LPARAM l);
	afx_msg LRESULT OnRSelChange(WPARAM ctrlId, LPARAM itemNumber);
//	afx_msg void OnAlign();
	DECLARE_MESSAGE_MAP()
	void UpdateCurrentLine();
//	void UpdateSelection(int sel);
	void DoSelchangeLine(int sel);
	virtual void UpdateTitleValueCollection(){}
	virtual void UpdateAlignTitleValues(){}
	ConfigBase::StringVectorVector& m_valuesSetting;
	BoolSetting& m_alignSetting;
	ListBoxTitleLine m_ListBoxTitleLine;
	ButtonToolTip m_CheckBoxAlign;
	int m_currentLineSelection;
	void* m_currentItemSelection;
	bool m_currentLineModified;
};
*/
////

class UGUI_API DialogPickItems : public DialogResetCustomDefault
{
public:
	enum DialogPickIds : unsigned int
	{
		valueListBoxAllId = DialogResetCustomDefault::DialogResetCustomDefaultIdCount,
		valueListBoxSelectedId,
		infoStaticId,
		searchEditId,
		searchButtonId,

		dialogPickIdsCount
	};

	static const int buttonWidth = 28;
	static const int buttonHeight = 14;
	static const int buttonGapV = 4;
	static const int buttonGapH = 2;
	static const int checkBoxHeight = 10;
	static const int staticHeight = 8;

	virtual ~DialogPickItems();
	void Display(TakionFrame* receipient, unsigned int code, CWnd* parent, int x, int y, int w, int h, bool custom);
//	void SetCustomFilter();
//	void SetDefaultFilter();

	virtual bool ClearItems();

	const bool& isModifiedCustom() const{return m_modifiedCustom;}
	const bool& isModifiedDefault() const{return m_modifiedDefault;}

	virtual unsigned int GetApplyMessageId() const = 0;
	virtual bool ShouldRefillOnDefault() const{return true;}

	virtual int GetAdditionalLbWidth() const{return 0;}

//	virtual TakionTool::NamedValueIdVector* GetValueVector(){return nullptr;}

	virtual void UpdateCurrentValueVector(unsigned int ctrlId, int itemOrdinalOld, int itemOrdinalNew){}// , TakionTool::NamedValueIdVector& valueVector);

//	const unsigned int* GetExchangeFilterMaskCustomOpen() const{return m_exchangeFilterMaskCustomOpen;}
//	const unsigned int* GetExchangeFilterMaskDefaultOpen() const{return m_exchangeFilterMaskDefaultOpen;}

	void UpdateModifiedCustom(){m_modifiedCustom = CheckModifiedCustom();}
	void UpdateModifiedDefault(){m_modifiedDefault = CheckModifiedDefault();}
	void UpdateModified()
	{
		if(m_currentCustom)UpdateModifiedCustom();
		else UpdateModifiedDefault();
	}

	virtual bool isChanged() const override
	{
		return DialogResetCustomDefault::isChanged()
			|| m_modifiedCustom
			|| m_modifiedDefault
			|| isAdditionalChanged();
	}
	virtual bool isAdditionalChanged() const{return false;}
/*
	static bool AreVectorsSame(const TakionTool::NamedValueIdVector& valueVector, const TakionTool::NamedValueIdVector& valueVectorOther)
	{
		return U_SetsEqual(valueVector, valueVectorOther);
	}
*/
	bool CheckModified() const{return CheckModifiedCustom() || CheckModifiedDefault();}
	virtual bool CheckModifiedCustom() const{return false;}
	virtual bool CheckModifiedDefault() const{return false;}
//	virtual bool isDefaultChanged() const override;
//	void FillVectorFromListBoxTo(TakionTool::NamedValueIdVector& valueVector) const;
protected:
	DialogPickItems(MainMessageLoopWnd* mainWnd,
//		const char* label,
		ListBoxOwnerDraw* lbPickFrom,
		ListBoxOwnerDraw* lbPickTo,

		int lbWidth, int hOffset, bool tooltips, bool removeByDragging, bool pickToSorted = false,
		bool toDestroyOnFocus = false,
		TakionFrame* receipient = nullptr,
		CWnd* parent = nullptr,
		const char* checkBoxCustomToolTip = nullptr,
		const char* buttonDefaultToolTip = nullptr);

	virtual void ClearCustomValues(){}
	virtual void ClearDefaultValues(){}
	virtual void ResetCustomValues(){}
	virtual void ResetDefaultValues(){}
	virtual void ApplyCustomValues(){}
	virtual void ApplyDefaultValues(){}
	virtual void MakeDefaultCustomValues(){}
	void ResetModified()
	{
		m_modifiedCustom = false;
		m_modifiedDefault = false;
	}
	//	virtual void BeforeShow() override;
	virtual bool DoReset() override;
	virtual void DoApply() override;
	virtual BOOL OnInitDialog() override;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void Resize(bool widthChanged = true, bool heightChanged = true) override;
//	virtual void BeforeDestroy() override;

	virtual void ToolTipsEnabled(bool enable) override;

	virtual void DoFillListBoxFrom(){}
	virtual void DoFillListBoxTo(){}

	void FillListBoxFrom()
	{
		DoFillListBoxFrom();
		m_lbPickFrom->UpdateToolTips();
	}
	void FillListBoxTo()
	{
		DoFillListBoxTo();
		m_lbPickTo->UpdateToolTips();
	}
//	void FillListBoxToFromVector(const TakionTool::NamedValueIdVector& valueVector);

	virtual void DoDefault() override;
	virtual void CustomModified() override;
	virtual void DoDataExchange(CDataExchange* pDX) override;

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnDblClkAll();
	afx_msg void OnDblClkSelected();
	afx_msg void OnSelchangeAll();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSearchChange();
	afx_msg void OnSearch();
	afx_msg LRESULT OnListBoxRightButtonSelection(WPARAM ctrlId, LPARAM l);
	DECLARE_MESSAGE_MAP()

	virtual void DoPaint(const RECT& rcPaint, CDC& dc) override;
	virtual void OnMouseForcedReleaseCapture() override;
	virtual void MouseLeft() override;
	virtual unsigned char UpdateResizeCursor(const CPoint& point, bool locked) override;

	virtual void LBItemDraggedAndDropped(unsigned int ctrlId, unsigned short from, unsigned short to) override;// unsigned int itemOrdinal) override;
	virtual void LBDragDropDone(unsigned int ctrlId, int itemOrdinalOld, int itemOrdinalNew) override;
	virtual void LBDragDropAbort(unsigned int ctrlId, int itemOrdinal) override;

	CStatic m_StaticInfo;
	EditNoContext m_EditSearch;
	CButton m_ButtonSearch;
	ListBoxOwnerDraw* m_lbPickFrom;
	ListBoxOwnerDraw* m_lbPickTo;

	int m_xc;
	int m_lbLeft;
	int m_lbTop;
	int m_lbRight;
	int m_lbHeight;
	int m_buttonLeft;
//	int m_lbWidth;
	int m_buttonWidthInPixels;
	int m_buttonHeightInPixels;
	int m_gapH;
	int m_gapV;
	int m_staticHeightInPixels;
	int m_staticBottomInPixels;
	int m_editHeightInPixels;
	int m_searchButtonTopInPixels;
	int m_searchButtonWidthInPixels;

////
	virtual void AllSelectionChanged(){}
	int m_allSelection;

	int m_lbWidth;
	int m_hOffset;

	int m_staticHeight;
	int m_checkBoxHeight;
//	int m_editWidth;
	int m_editHeight;
	int m_buttonWidth;
	int m_buttonHeight;
	int m_searchHeight;

	bool m_valuesModified;

	bool m_tooltips;
	bool m_removeByDragging;
////
	bool m_modifiedCustom;
	bool m_modifiedDefault;
////
	ActiveRectXButton m_clearItemsBox;
	ActiveRect* m_activeRect;

	virtual bool UpdateOnLButtonUp(UINT nFlags, CPoint point){return false;}
	virtual unsigned char ProcessKeyInSearch(MSG* pMsg);
	bool SearchItems();
	CString m_searchStr;
	bool m_searchDone;

//	virtual bool CreateToolTip() override;
//	virtual bool DestroyToolTip() override;
//	CToolTipCtrl* m_toolTip;
};

//template<class T, class Comp = std::less<T*> >
template<class T, class PtrSetType>
class PtrCollection
{
public:
//	typedef std::set<T*, Comp> PtrSet;
	typedef PtrSetType PtrSet;
	PtrCollection():m_itBegin(m_ptrs.begin()), m_itEnd(m_ptrs.end()){}
//	PtrCollection(const PtrCollection& other):m_itBegin(m_ptrs.begin()), m_itEnd(m_ptrs.end()){}
	virtual ~PtrCollection(){}
/*
	bool DestroyPtrs()
	{
		if(!m_ptrs.empty())
		{
			PtrSet copy(m_ptrs);
			Clear();
			for(PtrSet::iterator it = copy.begin(), itend = copy.end(); it != itend; ++it)
			{
				delete *it;
			}
			return true;
		}
		return false;
	}
*/
	bool Clear()
	{
		BeforeObjectsCleared();
		if(!m_ptrs.empty())
		{
			m_ptrs.clear();
			UpdateIterators();
			ObjectsCleared();
			return true;
		}
		return false;
	}
	bool AddObject(T* t)
	{
		if(m_ptrs.insert(t).second)
		{
			UpdateIterators();
			return true;
		}
		return false;
	}
	bool RemoveObject(T* t)
	{
		BeforeObjectRemoved(t);
		if(m_ptrs.erase(t))
		{
			UpdateIterators();
			ObjectRemoved(t);
			return true;
		}
		return false;
	}

	bool contains(const T* t) const{return m_ptrs.find((T*)t) != m_itEnd;}
	typename PtrSet::iterator Find(const T* t){return m_ptrs.find((T*)t);}
	typename PtrSet::const_iterator Find(const T* t) const{return m_ptrs.find((T*)t);}

	typename PtrSet::iterator Begin(){return m_itBegin;}
	typename PtrSet::const_iterator Begin() const{return m_itBegin;}

	typename PtrSet::iterator End(){return m_itEnd;}
	typename PtrSet::const_iterator End() const{return m_itEnd;}

	const PtrSet& GetPtrSet() const{return m_ptrs;}
	PtrSet& GetPtrSet(){return m_ptrs;}
	unsigned int GetCount() const{return (unsigned int)m_ptrs.size();}
	bool isEmpty() const{return m_ptrs.empty();}
	T* GetNextPtr(T* ptr, bool reverse)
	{
		if(m_ptrs.empty())
		{
			return nullptr;
		}
		if(ptr)
		{
			PtrSet::iterator found = m_ptrs.find(ptr);
			if(reverse)
			{
				if(found == m_itBegin)
				{
					found = m_itEnd;
				}
				--found;
			}
			else
			{
				if(found == m_itEnd)
				{
					found = m_itBegin;
				}
				else
				{
					++found;
					if(found == m_itEnd)
					{
						found = m_itBegin;
					}
				}
			}
			return *found;
		}
		else
		{
			if(reverse)
			{
				PtrSet::iterator found = m_itEnd;
				return *--found;
			}
			else
			{
				return *m_itBegin;
			}
		}
	}
protected:
	virtual void BeforeObjectRemoved(T* t){}
	virtual void BeforeObjectsCleared(){}
	virtual void ObjectRemoved(T* t){}
	virtual void ObjectsCleared(){}
	void UpdateIterators()
	{
		m_itBegin = m_ptrs.begin();
		m_itEnd = m_ptrs.end();
	}
	PtrSet m_ptrs;
	typename PtrSet::iterator m_itBegin;
	typename PtrSet::iterator m_itEnd;
	PtrCollection(const PtrCollection& other):m_itBegin(m_ptrs.begin()), m_itEnd(m_ptrs.end()){}
private:
	PtrCollection& operator=(const PtrCollection& other){return *this;}
};

template<typename T>
struct ToolPtrCollection
{
	typedef PtrCollection<T,
#if(_MSC_VER > 1600)
		std::unordered_set<T*>
#else
		std::hash_set<T*>
#endif
		> HashSet;
};

class UGUI_API MainMessageLoopWnd : public TakionFrame
{
friend class TakionFrame;
friend class TakionDialog;
friend class TakionMessageBox;
friend class VisualBase;
public:
	virtual ~MainMessageLoopWnd();
	const unsigned int& GetIdleInterruptCount() const{return m_idleInterruptCount;}
	const unsigned int& GetIdleCount() const{return m_idleCount;}
	virtual void AlternateMessageLoopEntered(bool interrupt, unsigned short source) = 0;
/*
	void AddHtmlViewer(TakionHtmlViewer* tool){m_htmlViewers.AddObject(tool);}
	void RemoveHtmlViewer(TakionHtmlViewer* tool){m_htmlViewers.RemoveObject(tool);}
	bool AddHelpHtmlViewer(TakionHtmlViewer* tool);
	bool RemoveHelpHtmlViewer(TakionHtmlViewer* tool);
*/
	virtual bool ShowHelp(const std::string& url) const;
	virtual void ShowSettingDialog(const char* tabToOpen, const void* initInfo = nullptr, bool corner = false){}

	virtual void OnKeyMenu(){}
	unsigned int GetNextOrdinal(){return ++m_nextOrdinal;}

	virtual const char* GetPasswordStr() const{return nullptr;}

	virtual unsigned int GetCommandToolCount() const{return 0;}
	virtual void RefreshTopMostWindows(){}//TBD
	virtual void PassMainThreadAvailableDataProcessedToExtensions(){}
	virtual void CloseOrderBoxIfDisplayed(){}
	virtual void UpdateShowTooltips(){}

	virtual bool CanUseTakionFileDialog() const{return true;}

	virtual bool FindKeyInSettings(const Key& key){return false;}
	virtual bool isVersionValid() const{return true;}

	typedef std::list<TakionDialogInterface*> DialogCollection;
	bool AddModalDialog(TakionDialogInterface* dlg);
	bool RemoveModalDialog(TakionDialogInterface* dlg);
	bool CloseModalDialogs();

#if(_MSC_VER > 1600)
	typedef std::unordered_set<ColoredDraggableDialog*> ColoredDraggableDialogSet;
	typedef std::unordered_set<TakionPopupWnd*> PopupWndSet;
#else
	typedef std::hash_set<ColoredDraggableDialog*> ColoredDraggableDialogSet;
	typedef std::hash_set<TakionPopupWnd*> PopupWndSet;
#endif
	void AddBlinkingDialog(ColoredDraggableDialog* dlg){m_blinkingDialogs.insert(dlg);}
	void RemoveBlinkingDialog(ColoredDraggableDialog* dlg){m_blinkingDialogs.erase(dlg);}

	void AddBlinkingPopup(TakionPopupWnd* wnd){m_blinkingPopups.insert(wnd);}
	void RemoveBlinkingPopup(TakionPopupWnd* wnd){m_blinkingPopups.erase(wnd);}
	virtual bool ProcessKeyFromDialog(TakionDialogInterface* dlg, const Key& key, bool repeat){return false;}
	virtual bool ProcessKeyFromSettingDialog(TakionSettingDialog* dlg, const Key& key, bool repeat){return false;}
	virtual bool ProcessKeyFromExtension(const Key& key, bool repeat){return false;}

//	virtual bool isSortDllsCaseInsensitive() const{return true;}
//	virtual bool isSortDllsByFileName() const{return false;}
//	virtual void SetSortDllsCaseInsensitive(bool sortDllsCaseInsensitive){}
//	virtual void SetSortDllsByFileName(bool sortDllsByFileName){}
	void SetSortDllsCaseInsensitive(bool sortDllsCaseInsensitive);
	void SetSortDllsByFileName(bool sortDllsByFileName);

//	typedef std::map<std::string, Graphics*> GraphicsMap;
	typedef std::map<FilterStringAsNumberArray, Graphics*> GraphicsMap;
	const GraphicsMap& GetGraphicsMap() const{return m_graphicsMap;}
	GraphicsMap& GetGraphicsMap(){return m_graphicsMap;}
	bool AddGraphics(Graphics* graphics);
	Graphics* FindGraphics(const FilterStringAsNumberArray& name)
	{
		GraphicsMap::iterator found = m_graphicsMap.find(name);
		return found == m_graphicsMapEnd ? nullptr : found->second;
	}
	const Graphics* FindGraphics(const FilterStringAsNumberArray& name) const
	{
		GraphicsMap::const_iterator found = m_graphicsMap.find(name);
		return found == m_graphicsMapEnd ? nullptr : found->second;
	}
	Graphics* FindGraphics(const std::string& name)
	{
		return FindGraphics(FilterStringAsNumberArray(name));
	}
	const Graphics* FindGraphics(const std::string& name) const
	{
		return FindGraphics(FilterStringAsNumberArray(name));
	}
	Graphics* FindGraphics(const char* const& name){return name ? FindGraphics(FilterStringAsNumberArray(name)) : nullptr;}
	const Graphics* FindGraphics(const char* const& name) const{return name ? FindGraphics(FilterStringAsNumberArray(name)) : nullptr;}
	void SaveGraphics();
	virtual bool UpdateGraphics(const Graphics* graphics){return false;}

	typedef std::map<FilterStringAsNumberArray, DWORD> FontMap;
	const FontMap& GetInstalledFontMap() const{return m_installedFontMap;}
	unsigned int GetInstalledFontMapCount() const{return (unsigned int)m_installedFontMap.size();}
	const DWORD* FindInstalledFontByName(const FilterStringAsNumberArray& fontName) const
	{
		FontMap::const_iterator found = m_installedFontMap.find(fontName);
		return found == m_installedFontMapEnd ? nullptr : &found->second;
	}
	const DWORD* FindInstalledFontByName(const std::string& fontName) const
	{
		return FindInstalledFontByName(FilterStringAsNumberArray(fontName));
	}

	const FontMap& GetMissingFontMap() const{return m_missingFontMap;}
	unsigned int GetMissingFontMapCount() const{return (unsigned int)m_missingFontMap.size();}
	const DWORD* FindMissingFontByName(const FilterStringAsNumberArray& fontName) const
	{
		FontMap::const_iterator found = m_missingFontMap.find(fontName);
		return found == m_missingFontMapEnd ? nullptr : &found->second;
	}
	const DWORD* FindMissingFontByName(const std::string& fontName) const
	{
		return FindMissingFontByName(FilterStringAsNumberArray(fontName));
	}

	const int& GetClearMenuWidth() const{return m_clearMenuWidth;}
	const int& GetRemoveMenuWidth() const{return m_removeMenuWidth;}
	const int& GetRemoveAllMenuWidth() const{return m_removeAllMenuWidth;}
	const int& GetRemoveLineMenuWidth() const{return m_removeLineMenuWidth;}
	const int& GetCopyMenuWidth() const{return m_copyMenuWidth;}
	const int& GetPasteMenuWidth() const{return m_pasteMenuWidth;}
	const int& GetUnPasteMenuWidth() const{return m_unPasteMenuWidth;}
	const int& GetDetachMenuWidth() const{return m_detachMenuWidth;}
	const int& GetEmptyMenuWidth() const{return m_emptyMenuWidth;}
	const int& GetNoneMenuWidth() const{return m_noneMenuWidth;}
	const int& GetAddMenuWidth() const{return m_addMenuWidth;}
	const int& GetAppendMenuWidth() const{return m_appendMenuWidth;}
	const int& GetInsertMenuWidth() const{return m_insertMenuWidth;}
	const int& GetCancelMenuWidth() const{return m_cancelMenuWidth;}
	const int& GetReplaceMenuWidth() const{return m_replaceMenuWidth;}
	const int& GetFindMenuWidth() const{return m_findMenuWidth;}
	const int& GetCloseMenuWidth() const{return m_closeMenuWidth;}
	const int& GetPinMenuWidth() const{return m_pinMenuWidth;}
	const int& GetUnpinMenuWidth() const{return m_unpinMenuWidth;}
	const int& GetShowMenuWidth() const{return m_showMenuWidth;}
	const int& GetHideMenuWidth() const{return m_hideMenuWidth;}
	const int& GetShowAllMenuWidth() const{return m_showAllMenuWidth;}
	const int& GetHideAllMenuWidth() const{return m_hideAllMenuWidth;}
	const int& GetTemplateMenuWidth() const{return m_templateMenuWidth;}
	const int& GetReloadMenuWidth() const{return m_reloadMenuWidth;}
	const int& GetReloadAllMenuWidth() const{return m_reloadAllMenuWidth;}

	const int& GetIncludeMenuWidth() const{return m_includeMenuWidth;}
	const int& GetExcludeMenuWidth() const{return m_excludeMenuWidth;}
	const int& GetTripleDotMenuWidth() const{return m_tripleDotMenuWidth;}
	const int& GetTestMenuWidth() const{return m_testMenuWidth;}
	const int& GetSelectionMenuWidth() const{return m_selectionMenuWidth;}
	const int& GetRangeSelectionMenuWidth() const{return m_rangeSelectionMenuWidth;}
	const int& GetUpdateMenuWidth() const{return m_updateMenuWidth;}
	const int& GetClipboardMenuWidth() const{return m_clipboardMenuWidth;}
	const int& GetSettingsMenuWidth() const{return m_settingsMenuWidth;}
	const int& GetGraphicsMenuWidth() const{return m_graphicsMenuWidth;}
	const int& GetShowPasswordMenuWidth() const{return m_showPasswordMenuWidth;}
	const int& GetCaseSensitiveMenuWidth() const{return m_caseSensitiveMenuWidth;}
	const int& GetSortByFileNameMenuWidth() const{return m_sortByFileNameMenuWidth;}

	const int& GetSpaceMenuWidth() const{return m_spaceMenuWidth;}
	const int& GetDoubleQuoteMenuWidth() const{return m_doubleQuoteMenuWidth;}

	static const char* GetNetworkMenuLabel(){return "Network";}
	const int& GetNetworkMenuWidth() const{return m_networkMenuWidth;}
	virtual HINSTANCE GetUiHInstance() const;
	DialogListDLL* GetListDllDialog();
protected:
	MainMessageLoopWnd(int minVisibleSize,
		int minWidth,
		int maxWidth,
		int minHeight,
		int maxHeight,
		int borderWidth,
		const char* className,
		COLORREF bkColor = 0);
	virtual void OnSuccessfulCreate();
	virtual bool DoIdleTasks(LONG lCount);

	virtual void AfterDialogClose(TakionDialog* dlg);

	virtual void BeforeDestroy() override;

	virtual void BeforeClearTools();

	virtual void EnableAllWindows(BOOL enable){}
	virtual void RepaintActiveTitle(){}

	bool AddMissingFontByName(const FilterStringAsNumberArray& fontName) const
	{
		return m_missingFontMap.insert(FontMap::value_type(fontName, 0)).second;
	}
	bool AddMissingFontByName(const std::string& fontName) const
	{
		return AddMissingFontByName(FilterStringAsNumberArray(fontName));
	}

	void OffsetTakionWndFrameRectAndMove(TakionFrame* const& wnd, const int& x, const int& y)
	{
		wnd->OffsetFrameRectAndMove(x, y);
	}
	void OffsetTakionDlgFrameRectAndMove(TakionDialogInterface* const& dlg, const int& x, const int& y)
	{
		dlg->OffsetFrameRectAndMove(x, y);
	}

	void ApplyTakionWndLayout(TakionFrame* const& wnd, const char* const& info, const unsigned int& contentModifier, const bool& clone, const unsigned __int64& version, const CRect* const& rect)
	{
		wnd->ApplyLayout(info, contentModifier, clone, version, rect);
	}

	unsigned int m_nextOrdinal;

	unsigned int m_idleInterruptCount;
	unsigned int m_idleCount;

	int m_clearMenuWidth;
	int m_removeMenuWidth;
	int m_removeAllMenuWidth;
	int m_removeLineMenuWidth;
	int m_copyMenuWidth;
//	int m_copyAllMenuWidth;
	int m_pasteMenuWidth;
	int m_unPasteMenuWidth;
	int m_detachMenuWidth;
	int m_emptyMenuWidth;
	int m_noneMenuWidth;
	int m_addMenuWidth;
	int m_appendMenuWidth;
	int m_insertMenuWidth;
	int m_cancelMenuWidth;
	int m_replaceMenuWidth;
	int m_findMenuWidth;
	int m_closeMenuWidth;
	int m_pinMenuWidth;
	int m_unpinMenuWidth;
	int m_showMenuWidth;
	int m_hideMenuWidth;
	int m_showAllMenuWidth;
	int m_hideAllMenuWidth;
	int m_templateMenuWidth;
	int m_reloadMenuWidth;
	int m_reloadAllMenuWidth;
	int m_includeMenuWidth;
	int m_excludeMenuWidth;
	int m_tripleDotMenuWidth;
	int m_testMenuWidth;
	int m_selectionMenuWidth;
	int m_rangeSelectionMenuWidth;
	int m_updateMenuWidth;
	int m_clipboardMenuWidth;
	int m_settingsMenuWidth;
	int m_graphicsMenuWidth;
	int m_showPasswordMenuWidth;
	int m_caseSensitiveMenuWidth;
	int m_sortByFileNameMenuWidth;
	int m_spaceMenuWidth;
	int m_doubleQuoteMenuWidth;

	int m_networkMenuWidth;

	DialogCollection m_modalList;
	ColoredDraggableDialogSet m_blinkingDialogs;
	PopupWndSet m_blinkingPopups;

	void ApplyGraphics();
	void ClearGraphics();
	void FactoryGraphicsColors();

	GraphicsMap m_graphicsMap;
	GraphicsMap::iterator m_graphicsMapBegin;
	GraphicsMap::const_iterator m_graphicsMapEnd;

	FontMap m_installedFontMap;
	FontMap::const_iterator m_installedFontMapEnd;

	mutable FontMap m_missingFontMap;
	FontMap::const_iterator m_missingFontMapEnd;

	void DeleteListDllDialog();
	DialogListDLL* m_listDllDialog;
};

class UGUI_API TakionResizableWnd : public TakionFrame
{
public:
	virtual LRESULT GetHitTest(const CPoint& point) const;
	virtual std::string GetBorderGraphicsName() const{return std::string("Border");}
protected:
	TakionResizableWnd(MainMessageLoopWnd* mainWnd,
		int minVisibleSize,
		int minWidth,
		int maxWidth,
		int minHeight,
		int maxHeight,
		int borderWidth,
		const char* className);
//	virtual bool ClientSetCursor(){return false;}
	virtual bool ResizeBorder(int borderWidth);
	virtual void UpdateTitleRects(){}
	virtual void OnBorderResize(int diff){UpdateTitleRects();}
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	DECLARE_MESSAGE_MAP()
	HCURSOR m_cursorMove;
	HCURSOR m_cursorDrag;
};

template<class T>
T UGUI_GetUIntNumberFromEdit(const CEdit& edit, const T& defaultValue = 0)
{
	CString str;
	edit.GetWindowText(str);
	T number;
	U_ReadUnsignedNumberFromString(number, str, '\0', defaultValue);
	return number;
}

template<class T>
T UGUI_GetUIntHexNumberFromEdit(const CEdit& edit, const T& defaultValue = 0)
{
	CString str;
	edit.GetWindowText(str);
	T number;
	U_ReadHexUnsignedNumberFromString(number, str, '\0', defaultValue);
	return number;
}

template<class T>
void UGUI_SetTextAsUIntToEdit(CEdit& edit, const T& text)
{
	if(text & ((T)0xFF << (sizeof(text) * 8 - 8)))//not terminated by zero
	{
		char buf[sizeof(text) + 1];
		*(unsigned __int64*)buf = text;
		buf[sizeof(text)] = '\0';
		edit.SetWindowText(buf);
	}
	else
	{
		edit.SetWindowText((const char*)&text);
	}
}

template<class T>
T UGUI_GetTextAsUIntFromEdit(const CEdit& edit, const bool term0)
{
	CString str;
	edit.GetWindowText(str);
	return U_RepresentStringAsUnsignedNumber<T>(str, term0 ? sizeof(T) - 1 : sizeof(T));
}

#ifdef __cplusplus
extern "C"
{
#endif

enum BaseMenuIDs : unsigned int
{
	TMID_CUT = 75535,
	TMID_COPY,
	TMID_PASTE,
	TMID_UPDATE,
	TMID_ADD,
	TMID_INSERT,
	TMID_REMOVE,
	TMID_CLEAR,
	TMID_REPLACE,
	TMID_RENAME,
	TMID_RESET,
	TMID_APPLY,
	TMID_VIEW,
	TMID_INITIALIZE,
	TMID_UNPASTE,

	TMID_EMPTY,
	TMID_NONE,
	TMID_ALL,

	TMID_COPY_ALL,
	TMID_REMOVE_ALL,
	TMID_REMOVE_LINE,

	TMID_BROWSE,

	TMID_IP,
	TMID_DNS,

	TMID_MOVE_UP,
	TMID_MOVE_DOWN,

	TMID_DEFAULT,
	TMID_DEFAULT_ALL,
	TMID_SELECT_ALL,
	TMID_UNSELECT_ALL,
	TMID_SELECT_RANGE,
	TMID_UNSELECT_RANGE,
	TMID_MOVE_RANGE_TO_TOP,
	TMID_CLIPBOARD,

	TMID_TITLE_GRAPHICS,
	TMID_GRAPHICS,
	TMID_SETTINGS,
	TMID_HELP,

	TMID_LOCK,
	TMID_UNLOCK,

	TMID_FIND,
	TMID_FIND_ALT,
	TMID_INCLUDE,
	TMID_UNINCLUDE,
	TMID_EXCLUDE,
	TMID_UNEXCLUDE,
	TMID_CAP,
	TMID_ROWS,
	TMID_VALUE,
	TMID_MOVE,
	TMID_SORT,
	TMID_SHOW,
	TMID_HIDE,
	TMID_CLOSE,
	TMID_SHOW_ALL,
	TMID_HIDE_ALL,

	TMID_NETWORK,

	TMID_SET_SHOW_PASSWORD,

	TMID_CASE_SENSITIVE,
	TMID_SORT_ALT,

	BaseMenuIDsLast
};

#ifdef __cplusplus
}
#endif
