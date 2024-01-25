#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#ifdef U_EXPORTS
#define U_API __declspec(dllexport)
#else
#define U_API __declspec(dllimport)
#endif

#ifdef _DEBUG
#define VERIFY_QUOTES
/*
#define VERIFY_LOCK 1000000
#ifdef VERIFY_LOCK
#define VERIFY_LOG_DELAY 800
#endif
*/
#endif

//#define USE_SPACE_IN_STOCK_SYMBOLS

#include <afxmt.h>
#include <TakionMemoryApi.h>

#if (_MSC_VER > 1600)
#include <functional>
#include <unordered_set>
#include <unordered_map>
#else
#include <hash_set>
#include <hash_map>
#endif
#include <set>
#include <map>

const char* const UtilsHeaderVersion = "1.0.7.46";

const char fix_soh = '\1';

const unsigned __int64 high64Byte = 0xFF00000000000000ui64;

#ifdef __cplusplus
extern "C"
{
#endif

/*
typedef LONGLONG (*InterlockedExchange64FunctionPtr)(LONGLONG volatile *Target, LONGLONG Value);

InterlockedExchange64FunctionPtr WINAPI U_GetInterlockedExchange64FunctionPtr();
InterlockedExchange64FunctionPtr WINAPI U_GetInterlockedExchangeAdd64FunctionPtr();
*/
typedef LONGLONG (WINAPI *InterlockedCompareExchange64FunctionPtr)(LONGLONG volatile *Destination, LONGLONG Exchange, LONGLONG Comparand);
InterlockedCompareExchange64FunctionPtr WINAPI U_GetInterlockedCompareExchange64FunctionPtr();

void WINAPI U_SetThreadName(DWORD dwThreadID, const char* threadName);
bool WINAPI U_IsInMainThread();
unsigned int WINAPI U_GetMainThreadId();

char* WINAPI U_CopyString(const char* str);
void WINAPI U_AppendPrintableChar(std::string& str, char c, char del = '\0');
bool WINAPI U_AppendPrintableCharIfValid(std::string& str, char c, char del = '\0', char invalidReplacement = '\0');
void WINAPI U_AppendUChar(std::string& str, unsigned char number, char del = '\0');
void WINAPI U_AppendUCharHex(std::string& str, unsigned char number, const char del = '\0', const bool capitals = false, const unsigned char minLength = 0);
void WINAPI U_AppendUShort(std::string& str, unsigned short number, char del = '\0');
void WINAPI U_AppendUShortHex(std::string& str, unsigned short number, const char del = '\0', const bool capitals = false, const unsigned char minLength = 0);
void WINAPI U_AppendBool(std::string& str, bool val, char del = '\0');
void WINAPI U_AppendUInt(std::string& str, unsigned int number, char del = '\0');
void WINAPI U_AppendUIntHex(std::string& str, unsigned int number, const char del = '\0', const bool capitals = false, const unsigned char minLength = 0);
void WINAPI U_AppendUInt64(std::string& str, unsigned __int64 number, char del = '\0');
void WINAPI U_AppendUInt64Hex(std::string& str, unsigned __int64 number, const char del = '\0', const bool capitals = false, const unsigned char minLength = 0);
void WINAPI U_AppendInt(std::string& str, int number, char del = '\0');
void WINAPI U_AppendInt64(std::string& str, __int64 number, char del = '\0');
void WINAPI U_AppendTwoDigits(std::string& str, unsigned int number, char del = '\0');
void WINAPI U_AppendThreeDigits(std::string& str, unsigned int number, char del = '\0');
void WINAPI U_AppendFourDigits(std::string& str, unsigned int number, char del = '\0');
char* WINAPI U_AppendTwoDigitsToBuf(char* buf, unsigned int buflen, unsigned int number, char del = '\0');
char* WINAPI U_AppendTwoDigitsToBufWithNoTerm0(char* buf, unsigned int buflen, unsigned int number);

void WINAPI U_AppendTimeTokens(std::string& str, unsigned int hour, unsigned int minute, unsigned int second, char del = '\0', bool oneDigitLeftmost = false, const char separator = ':');
void WINAPI U_AppendMillisecond(std::string& str, unsigned int millisecond, bool appendMillisecond = true, char del = '\0', bool oneDigitLeftmost = false, const char separator = ':', const char millisecondSeparator = '-');
void WINAPI U_AppendMinute(std::string& str, unsigned short minute, char del = '\0', const char separator = ':', bool oneDigitLeftmost = false);
void WINAPI U_AppendMinuteOutOfMillisecond(std::string& str, unsigned int millisecond, char del = '\0', bool oneDigitLeftmost = false, const char separator = ':');

unsigned __int64 WINAPI U_ConvertStringToVersionAndReturnCursor(const char*& cursor, char delimiter = '\0');
void WINAPI U_VersionNumToStr(unsigned __int64 versionNum, std::string& versionStr);
unsigned __int64 WINAPI U_VersionStrToNum(const char* versionStr);
unsigned int WINAPI U_Version64To32(unsigned __int64 version64);
unsigned __int64 WINAPI U_Version32To64(unsigned int version32);
unsigned __int64 WINAPI U_GetVersionFromResourceFile(HINSTANCE hInstance);
unsigned __int64 WINAPI U_GetFileVersion(const char* fileName);
unsigned __int64 WINAPI U_GetVersionFromTokens(unsigned short t1, unsigned short t2, unsigned short t3, unsigned short t4);

inline unsigned __int64 U_GetVersion64(const unsigned __int64& v1, const unsigned __int64& v2, const unsigned __int64& v3, const unsigned __int64& v4)
{
	return (v1 << 48) | (v2 << 32) | (v3 << 16) | v4;
}

inline bool U_IsAlphaUppercase(const char& c)
{
	return c >= 'A' && c <= 'Z';
}

inline bool U_IsAlphaLowercase(const char& c)
{
	return c >= 'a' && c <= 'z';
}

inline bool U_IsAlpha(const char& c)
{
	return U_IsAlphaUppercase(c) || U_IsAlphaLowercase(c);
}

inline bool U_IsDigit(const char& c)
{
	return c >= '0' && c <= '9';
}

inline bool U_IsAlphaNum(const char& c)
{
	return U_IsAlpha(c) || U_IsDigit(c);
}

inline bool U_IsSpace(const char& c)
{
	switch(c)
	{
		case ' ':
		case '\t':
		case '\n':
		case '\v':
		case '\f':
		case '\r':
		return true;

		default:
		return false;
	}
}

inline bool U_IsCntrl(const char& c)
{
	return c >= '\0' && c <= 0x1f || c == 0x7f;
}

bool WINAPI U_SkipToDelimiter(const char*& str, char del);
bool WINAPI U_SkipToDelimiterUpToLength(const char*& str, unsigned int& length, char del);
bool WINAPI U_SkipDelimiters(const char*& str, char del);
bool WINAPI U_SkipDelimitersUpToLength(const char*& str, unsigned int& length, char del);
bool WINAPI U_ReadStrTokenToMandatoryDel(std::string& token, const char*& str, char del, char terminator);
bool WINAPI U_ReadCharBufferToken(char* buffer, unsigned int size, const char*& str, char del);
bool WINAPI U_ReadStrToken(std::string& token, const char*& str, char del);
bool WINAPI U_ReadStrTokenLeaveDelimiter(std::string& token, const char*& str, char del);
bool WINAPI U_ReadStrTokenUpToLength(std::string& token, const char*& str, unsigned int& length, char del);
bool WINAPI U_ReadStrTokenWith2Delimiters(std::string& token, const char*& str, char del, char otherDel = '\n');
bool WINAPI U_ReadBoolToken(const char*& str, char del, bool defaultValue = false);
int WINAPI U_ReadIntToken(const char*& str, char del, int defaultValue = 0);
unsigned int WINAPI U_ReadUIntToken(const char*& str, char del, unsigned int defaultValue = 0);
unsigned int WINAPI U_ReadUIntHexToken(const char*& str, char del, unsigned int defaultValue = 0, unsigned char* errorPlace = nullptr);
unsigned int WINAPI U_ReadUIntTokenWithDigitCount(const char*& str, unsigned char& decDigits, char del, unsigned int defaultValue = 0);
unsigned __int64 WINAPI U_ReadUInt64Token(const char*& str, char del, unsigned __int64 defaultValue = 0);
unsigned __int64 WINAPI U_ReadUInt64HexToken(const char*& str, char del, unsigned __int64 defaultValue = 0, unsigned char* errorPlace = nullptr);

unsigned int WINAPI U_ReadMillisecondFromStr(const char*& cursor, char del, unsigned int defaultValue = 0, const char timeSeparator = ':', const char millisecondSeparator = '-');
unsigned int WINAPI U_ReadSecondFromStr(const char*& cursor, char del, unsigned int defaultValue = 0, const char separator = ':');

unsigned short WINAPI U_ReadStrAsUShortToken(const char*& str, char del, unsigned short defaultValue = 0);
unsigned int WINAPI U_ReadStrAsUIntToken(const char*& str, char del, unsigned int defaultValue = 0);
unsigned __int64 WINAPI U_ReadStrAsUInt64Token(const char*& str, char del, unsigned __int64 defaultValue = 0);

char WINAPI U_ReadCharToken(const char*& str, char del, char defaultValue = 0);
char WINAPI U_ReadCharTokenAndUpdateLength(const char*& str, unsigned int& length, char defaultValue = 0);
char WINAPI U_ReadCharTokenUpToLength(const char*& str, unsigned int& length, char del, char defaultValue = 0);

unsigned char WINAPI U_ReadUCharToken(const char*& str, char del, unsigned char defaultValue = 0);
unsigned char WINAPI U_ReadUCharHexToken(const char*& str, char del, unsigned char defaultValue = 0, unsigned char* errorPlace = nullptr);
unsigned short WINAPI U_ReadUShortToken(const char*& str, char del, unsigned short defaultValue = 0);
unsigned short WINAPI U_ReadUShortHexToken(const char*& str, char del, unsigned short defaultValue = 0, unsigned char* errorPlace = nullptr);
unsigned short WINAPI U_ReadUShortTokenWith2Delimiters(const char*& str, char del, char otherDel = '\0', unsigned short defaultValue = 0);
unsigned short WINAPI U_ReadUShortTokenWithDigitCount(const char*& str, unsigned char& decDigits, char del, unsigned short defaultValue = 0);
__int64 WINAPI U_ReadInt64Token(const char*& str, char del, __int64 defaultValue = 0);
__int64 WINAPI U_ReadInt64TokenWith2Delimiters(const char*& str, char del, char otherDel = '\0', __int64 defaultValue = 0);
unsigned int WINAPI U_ReadUIntTokenWith2Delimiters(const char*& str, char del, char otherDel = '\0', unsigned int defaultValue = 0);
unsigned __int64 WINAPI U_ReadUInt64TokenWith2Delimiters(const char*& str, char del, char otherDel = '\0', unsigned __int64 defaultValue = 0);
int WINAPI U_ReadIntTokenWith2Delimiters(const char*& str, char del, char otherDel = '\0', int defaultValue = 0);

unsigned int WINAPI U_ReadUIntTokenWith2DelimitersUpToLength(const char*& str, unsigned int& length, char del, char otherDel = '\0', unsigned int defaultValue = 0);
unsigned __int64 WINAPI U_ReadUInt64TokenWith2DelimitersUpToLength(const char*& str, unsigned int& length, char del, char otherDel = '\0', unsigned __int64 defaultValue = 0);

unsigned short WINAPI U_ReadUShortTokenUpToLengthWithDigitCount(const char*& str, unsigned int& length, unsigned char& decDigits, char del, unsigned short defaultValue = 0);
unsigned int WINAPI U_ReadUIntTokenUpToLengthWithDigitCount(const char*& str, unsigned int& length, unsigned char& decDigits, char del, unsigned int defaultValue = 0);

char* WINAPI U_MarkSectionEnd(char* str, char del, bool& changed);
void WINAPI U_CopyAndPad(char* dst, unsigned int len, const char* src, char pad, bool mustPad = false);
void WINAPI U_CopyPlusOneCharAndPad(char* dst, unsigned int len, const char* src, char additionalChar, char pad);
const char* WINAPI U_CopyToDelimiterAndPad(char* dst, unsigned int len, const char* src, char pad, char del = '\0');
const char* WINAPI U_CopyToDelimiterPlusOneCharAndPad(char* dst, unsigned int len, const char* src, char additionalChar, char pad, char del = '\0');
const char* WINAPI U_CopyToDelimiterUpToLengthAndPad(char* dst, unsigned int len, const char* src, unsigned int& length, char pad, char del = '\0');
const char* WINAPI U_CopyToDelimiterUpToLengthPlusOneCharAndPad(char* dst, unsigned int len, const char* src, unsigned int& length, char additionalChar, char pad, char del = '\0');
void WINAPI U_ReplaceCharInStdString(std::string& str, char what, char with);

unsigned int WINAPI U_StringHash(const std::string& str);

bool WINAPI U_GetModulePath(HINSTANCE hInstance, char* path, unsigned int bufsize);
void WINAPI U_GetModuleFileName(HINSTANCE hInstance, std::string& fileName);
void WINAPI U_GetPlatformStr(std::string& platform);
void WINAPI U_AppendVersion(std::string& versionStr, unsigned __int64 versionNum);

void WINAPI U_InitializeInstanceInfo(HINSTANCE hInstance, std::string& filePathAndName, std::string& fileDescription, std::string& platform, unsigned __int64& versionNum, std::string& versionStr);

void WINAPI U_InitializeInstanceInfoAndVersion(HINSTANCE hInstance, std::string& filePathAndName, std::string& fileDescription, std::string& platform,
	const unsigned __int64& version1,
	const unsigned __int64& version2,
	const unsigned __int64& version3,
	const unsigned __int64& version4,
	unsigned __int64& versionNum, std::string& versionStr);
void* WINAPI U_GetVersionBlockHandle(HINSTANCE hInstance);
//bool WINAPI U_QueryVersionResourceValue(HINSTANCE hInstance, const char* name, std::string& value);
bool WINAPI U_QueryVersionResourceValue(const char* fileName, const char* name, std::string& value);

const char* WINAPI U_GetModuleVersionStr();
unsigned __int64 WINAPI U_GetModuleVersionNum();
const char* WINAPI U_GetHeaderVersion();
unsigned __int64 WINAPI U_GetHeaderVersionNum();
const char* WINAPI U_GetFilePathAndName();
const char* WINAPI U_GetPlatform();
const char* WINAPI U_GetFileDescription();
const char* WINAPI U_GetProductName();
void WINAPI U_GetDllBuildDescription(std::string& buildStr);

const char* WINAPI U_GetFileNameFromPath(const char* path);

void WINAPI U_CopyUppercase(char* dest, unsigned short length, const char*& source, char del = '\0', bool pad = false);
void WINAPI U_StringToUpper(char* str, char del = '\0');

bool WINAPI U_IsWinSockInitialized();
const char*  WINAPI U_GetWinSockStatus();
unsigned int WINAPI U_GetIpAddressCount();
const unsigned int* WINAPI U_GetIpAddressesNum();
const char* WINAPI U_GetIpAddressesStr();
unsigned int WINAPI U_GetIpAddressNum();
unsigned int WINAPI U_GetFirstIpAddressNum();
bool WINAPI U_UpdateIpAddresses();
bool WINAPI U_FormatErrorMessage(DWORD errorCode, std::string& errorMessage, const char* unknown = nullptr);
const char* WINAPI U_GetHostName();
bool WINAPI U_UpdateHostName();
const char* WINAPI U_ShellExecute(HWND hwnd, const char* filePath, const char* parameters = nullptr, const char* directory = nullptr);

//unsigned short WINAPI U_GetQuoteDelay(unsigned int millisecond);

const char* WINAPI U_GetValidStockChars();
const char* WINAPI U_GetValidStockFirstChars();
bool WINAPI U_IsStockSymbolValid(const char* symbol);
bool WINAPI U_IsStockCharValid(char c, bool first);

#ifndef TAKION_NO_OPTIONS
const char* WINAPI U_GetValidOptionFirstChars();
const char* WINAPI U_GetValidOptionChars();
bool WINAPI U_IsOptionSymbolValid(const char* symbol);
bool WINAPI U_IsOptionCharValid(char c, bool first);
#endif

const char* WINAPI U_GetValidIndexChars();
const char* WINAPI U_GetValidIndexFirstChars();
bool WINAPI U_IsIndexSymbolValid(const char* symbol);
bool WINAPI U_IsIndexCharValid(char c, bool first);

const char* WINAPI U_GetValidMmidChars();
const char* WINAPI U_GetValidMmidFirstChars();
bool WINAPI U_IsMmidSymbolValid(const char* mmid);
bool WINAPI U_IsMmidCharValid(char c, bool first);

const char* WINAPI U_GetValidBasketChars();
const char* WINAPI U_GetValidBasketFirstChars();
bool WINAPI U_IsBasketSymbolValid(const char* symbol);
bool WINAPI U_IsBasketCharValid(char c, bool first);

unsigned __int64 WINAPI U_StringToUInt64(const char* str);
unsigned int WINAPI U_StringToUInt(const char* str);
unsigned short WINAPI U_StringToUShort(const char* str);

unsigned __int64 WINAPI U_StringOfLengthToUInt64(const char* str, unsigned int length);

unsigned __int64 WINAPI U_StringToUInt64Term0(const char* str);
unsigned __int64 WINAPI U_StringOfLengthToUInt64Term0(const char* str, unsigned int length);

//void WINAPI U_GetRectInCenterRect(const RECT& center, RECT& rect);
//void WINAPI U_GetRectInsideRect(const RECT& outer, RECT& inner);
void WINAPI U_EnumFontFamilies(HDC hdc, BYTE charSet, std::map<std::string, DWORD>& fontMap);
void WINAPI U_EnumFontSizes(HDC hdc, const char* fontName, BYTE charSet, std::set<unsigned int>& sizeSet);
const unsigned int* WINAPI U_GetTrueTypeFontSizes();

bool WINAPI U_GetPrivateProfileSection(std::map<std::string, std::string>& result, const char* sectionName, const char* filePathAndName, unsigned int guessSize = 1024, unsigned int maxSize = 0x10000);
bool WINAPI U_GetPrivateProfileString(std::string& result, const char* sectionName, const char* entryName, const char* defaultValue, const char* filePathAndName, unsigned int guessSize = 1024, unsigned int maxSize = 0x10000);
bool WINAPI U_ConvertIpToString(unsigned int ip, char* str, unsigned int length, unsigned char tokenCount = 4, const char* suffix = nullptr);
void WINAPI U_ConvertIpToStdString(unsigned int ip, std::string& str, unsigned char tokenCount = 4, const char* suffix = nullptr);
unsigned int WINAPI U_ConvertStringToIp(const char* str);
unsigned int WINAPI U_ConvertStringToIpAndReturnCursor(const char*& cursor, char delimiter = '\0');
char* WINAPI U_ConvertIpTokenString(char* cursor, unsigned char ipToken, unsigned int* len = nullptr);
unsigned __int64 WINAPI U_CalculateIpPort(unsigned int ip, unsigned short port);
unsigned int WINAPI U_UIntSwapBytes(unsigned int number);
unsigned __int64 WINAPI U_UInt64Swap2Bytes(unsigned __int64 number);

#ifdef __cplusplus
}
#endif

class TakionIterator
{
public:
	virtual ~TakionIterator(){}
	virtual void Reset() = 0;
	virtual unsigned int GetCount() const = 0;
	virtual void Skip(unsigned int count) = 0;
protected:
	TakionIterator(){}
};

class RingVectorBaseItem
{
public:
	virtual ~RingVectorBaseItem(){}
	virtual void Copy(const RingVectorBaseItem& from){}
	virtual RingVectorBaseItem* CreateCopy() const{return nullptr;}
protected:
	RingVectorBaseItem(){}
};

class U_API TakionRingVectorBase
{
public:
	virtual ~TakionRingVectorBase(){}

	virtual void push_back(RingVectorBaseItem* const& val) = 0;
	virtual void push_front(RingVectorBaseItem* const& val) = 0;
	virtual void pop_back() = 0;
	virtual void pop_front() = 0;
	virtual RingVectorBaseItem*& push_back_empty() = 0;
	virtual RingVectorBaseItem*& push_front_empty() = 0;
	virtual void insert(size_t at, RingVectorBaseItem* const& val) = 0;

	virtual void clear() = 0;

	virtual const RingVectorBaseItem* at(size_t pos) const = 0;
	virtual RingVectorBaseItem* at(size_t pos) = 0;
	const RingVectorBaseItem* operator[](size_t pos) const{return at(pos);}
	RingVectorBaseItem* operator[](size_t pos){return at(pos);}
	virtual const RingVectorBaseItem* fromBack(size_t pos) const = 0;
	virtual RingVectorBaseItem* fromBack(size_t pos) = 0;

	virtual const RingVectorBaseItem* front() const = 0;
	virtual RingVectorBaseItem* front() = 0;
	virtual const RingVectorBaseItem* back() const = 0;
	virtual RingVectorBaseItem* back() = 0;

	virtual void ReserveAdditional(size_t size) = 0;
	virtual void reserve(size_t capacity) = 0;
	virtual size_t capacity() const = 0;
	virtual size_t size() const = 0;
//	virtual void Pad() = 0;
protected:
	TakionRingVectorBase(){}
};

static const LONG modificationBit = 1 << 30;
static const LONG minusModificationBit = -(1 << 30);

class TakionLockBase
{
protected:
	TakionLockBase():m_lock(0){}
	mutable volatile LONG m_lock;
};

//Multiple thread readers; Multiple thread writers
//Allows multiple reads from multiple threads, single write from multiple threads
class U_API TakionLockMultithread : public TakionLockBase
{
public:
	TakionLockMultithread():m_threadId(0){}
	bool LockInquiry() const;
	void LockInquiryWait() const;
	bool LockModification() const;
	void UnlockInquiry() const;
	void UnlockModification() const;
protected:
	mutable DWORD m_threadId;
};

//Multiple thread readers; Single thread writers
//Allows multiple reads from multiple threads, single write from single thread
class U_API TakionLock : public TakionLockBase
{
public:
	TakionLock(){}
	bool LockInquiry() const;
	void LockInquiryWait() const;
	bool LockModification() const;
	void UnlockInquiry() const;
	void UnlockModification() const;
};

//Single thread readers and writers
//Exclusive thread accesss
//Once you lock it in a thread you can't lock it from other threads
class U_API TakionLockSingleThreadAccess : public TakionLockBase
{
public:
	TakionLockSingleThreadAccess():m_count(0){}

	bool Lock() const;
	void LockWait() const;
	bool Unlock() const;

protected:
//	mutable volatile LONG m_threadId;
//	mutable volatile LONG m_count;
	mutable unsigned int m_count;
};

/*Use TakionLockSingleThreadAccess
//exclusive access from multiple threads
class U_API TakionLockReadWrite : public TakionLockBase
{
public:
	TakionLockReadWrite(){}
	void LockWait() const
	{
		while(InterlockedExchange(&m_lock, 1))
		{
			Sleep(0);
		}
	}

	void Unlock() const
	{
		InterlockedExchange(&m_lock, 0);
	}

	bool Lock() const
	{
		return !InterlockedExchange(&m_lock, 1);
	}
};
*/
class FontDescription
{
public:
	FontDescription(const char* name, unsigned int size, bool hasMaxSize, unsigned int maxSize, bool bold, bool italic = false):
		m_fontName(name),
		m_actualFontName(m_fontName),
		m_fontSize(size),
		m_hasMaxSize(hasMaxSize),
		m_fontMaxSize(hasMaxSize ? maxSize : 0),
		m_fontBold(bold),
		m_fontItalic(italic)
	{}
	FontDescription():
		m_fontName(""),
		m_actualFontName(m_fontName),
		m_fontSize(0),
		m_hasMaxSize(false),
		m_fontMaxSize(0),
		m_fontBold(false),
		m_fontItalic(false)
	{}
	const char* GetDesiredFontName() const{return m_fontName.c_str();}
	const std::string& GetDesiredFontNameStr() const{return m_fontName;}
	const char* GetActualFontName() const{return m_actualFontName.c_str();}
	const std::string& GetActualFontNameStr() const{return m_actualFontName;}
	std::string& GetActualFontNameStr(){return m_actualFontName;}
	const unsigned int& GetFontSize() const{return m_fontSize;}
	const unsigned int& GetFontMaxSize() const{return m_fontMaxSize;}
	const bool& isFontBold() const{return m_fontBold;}
	const bool& isFontItalic() const{return m_fontItalic;}

	void SetDesiredFontName(const char* const& name)
	{
		if(strcmp(m_fontName.c_str(), name))
		{
			m_fontName = name;
			m_actualFontName = m_fontName;
		}
	}
	bool SetActualFontName(const char* const& name) const
	{
		if(strcmp(m_actualFontName.c_str(), name))
		{
			m_actualFontName = name;
			return true;
		}
		return false;
	}
	void SetFontSize(const unsigned int& size){m_fontSize = size;}
	void SetFontMaxSize(const unsigned int& size){m_fontMaxSize = size;}
	void SetFontBold(const bool& bold){m_fontBold = bold;}
	void SetFontItalic(const bool& italic){m_fontItalic = italic;}

	bool operator==(const FontDescription& other) const
	{
		return m_fontName == other.m_fontName
			&& m_fontSize == other.m_fontSize
			&& m_fontMaxSize == other.m_fontMaxSize
			&& m_fontBold == other.m_fontBold
			&& m_fontItalic == other.m_fontItalic;
	}
	bool operator!=(const FontDescription& other) const
	{
		return !operator==(other);
	}
	const bool& GetHasMaxSize() const{return m_hasMaxSize;}
	void SetHasMaxSize(const bool& hasMaxSize){m_hasMaxSize = hasMaxSize;}
	void toString(std::string& str, char delimiter) const
	{
		str += m_fontName;
		str += delimiter;
		U_AppendUInt(str, m_fontSize, delimiter);
		if(m_hasMaxSize)
		{
			U_AppendUInt(str, m_fontMaxSize, delimiter);
		}
		else
		{
			str += delimiter;
		}
		U_AppendBool(str, m_fontBold, delimiter);
		U_AppendBool(str, m_fontItalic, delimiter);
	}

	void fromString(const char*& cursor, char delimiter)
	{
		if(*cursor)
		{
			m_fontName.clear();
			U_ReadStrToken(m_fontName, cursor, delimiter);
			m_actualFontName = m_fontName;
			m_fontSize = U_ReadUIntToken(cursor, delimiter);
			m_fontMaxSize = U_ReadUIntToken(cursor, delimiter);
			m_fontBold = U_ReadBoolToken(cursor, delimiter);
			m_fontItalic = U_ReadBoolToken(cursor, delimiter);
		}
	}

protected:
	std::string m_fontName;
	mutable std::string m_actualFontName;
	unsigned int m_fontSize;
	bool m_hasMaxSize;
	unsigned int m_fontMaxSize;
	bool m_fontBold;
	bool m_fontItalic;
};

//IniValue hierarchy

class U_API IniValue
{
public:
	virtual ~IniValue(){}
	const bool& ExtractValue(){m_valid = DoExtractValue(); return m_valid;}
	virtual bool isModified() const{return true;}
	virtual bool isDefault() const{return false;}
	bool SaveValue(std::string* error) const{return !isModified() || (m_eraseIfDefault && isDefault() ? DoEraseValue(error) : DoSaveValue(error));}
	bool SaveValueToIniFile(const char* iniFile, std::string* error) const
	{
		return iniFile ?
			m_eraseIfDefault && isDefault() ? DoEraseValueInIniFile(iniFile, error) : DoSaveValueToIniFile(iniFile, error):
			SaveValue(error);
	}
	const bool& isValid() const{return m_valid;}
	virtual void UpdateInitialValue(){}
	virtual void Reset(){}
	bool SaveValueAndUpdateInitialValue(std::string* error)
	{
		bool ret = SaveValue(error);
		if(ret)UpdateInitialValue();
		return ret;
	}
	void SetSection(const char* section){m_section = section;}
	void SetEntry(const char* entry){m_entry = entry;}
	void SetFile(const char* file){m_file = file;}
	const char* const& GetSection() const{return m_section;}
	const char* const& GetEntry() const{return m_entry;}
	const char* const& GetFile() const{return m_file;}
protected:
	IniValue(const char* section, const char* entry, const char* file, bool eraseIfDefault):
		m_section(section),
		m_entry(entry),
		m_file(file),
		m_eraseIfDefault(eraseIfDefault),
		m_valid(false)
	{}
//	virtual bool DoSaveValue(std::string* error = nullptr) const{return true;}
	virtual bool DoSaveValue(std::string* error = nullptr) const{return DoSaveValueToIniFile(m_file, error);}
	virtual bool DoSaveValueToIniFile(const char* iniFile, std::string* error = nullptr) const{return true;}
	bool DoEraseValue(std::string* error = nullptr) const;
	bool DoEraseValueInIniFile(const char* iniFile, std::string* error = nullptr) const;
	virtual bool DoExtractValue(){return true;}
	bool WriteEntryValue(const char* entry, const char* value, std::string* error) const{return WriteEntryValueToIniFile(m_file, entry, value, error);}
//	bool WriteValue(const char* value, std::string* error) const{return WriteEntryValue(m_entry, value, error);}
	bool WriteEntryValueToIniFile(const char* iniFile, const char* entry, const char* value, std::string* error) const;
	bool WriteValueToIniFile(const char* iniFile, const char* value, std::string* error) const{return WriteEntryValueToIniFile(iniFile, m_entry, value, error);}
	const char* m_section;
	const char* m_entry;
	const char* m_file;
	bool m_eraseIfDefault;
	bool m_valid;
};

template<class V>
class TypeIniValue : public IniValue
{
public:
	typedef V ValueType;
	bool SetValue(const ValueType& value)
	{
		if(value != m_value)
		{
			m_value = value;
			return true;
		}
		return false;
	}
	const ValueType& GetValue() const{return m_value;}
	const ValueType& GetInitialValue() const{return m_initialValue;}
	virtual bool isModified() const override{return !(m_value == m_initialValue);}
	virtual bool isDefault() const override{return m_value == m_defaultValue;}
	virtual void UpdateInitialValue() override{m_initialValue = m_value;}
	virtual void Reset() override{m_value = m_initialValue;}
protected:
	TypeIniValue(const char* section, const char* entry, const char* file, bool eraseIfDefault, const V& value):
		IniValue(section, entry, file, eraseIfDefault),
		m_value(value),
		m_initialValue(value),
		m_defaultValue(value)
	{}
	ValueType m_value;
	ValueType m_initialValue;
	ValueType m_defaultValue;
};

class U_API StringIniValue : public TypeIniValue<std::string>
{
public:
	StringIniValue(const char* section, const char* entry, const char* file, bool eraseIfDefault, const std::string& value, unsigned int guessSize = 1024, unsigned int maxSize = 0x10000):
		TypeIniValue(section, entry, file, eraseIfDefault, value),
		m_guessSize(guessSize < 2 ? 2 : guessSize),
		m_maxSize(maxSize < m_guessSize ? m_guessSize : maxSize)
	{}
protected:
	virtual bool DoExtractValue() override
	{
		if(U_GetPrivateProfileString(m_value, m_section, m_entry, m_defaultValue.c_str(), m_file, m_guessSize, m_maxSize))
		{
			m_initialValue = m_value;
			return true;
		}
		return false;
	}
	virtual bool DoSaveValueToIniFile(const char* iniFile, std::string* error) const override
	{
		return WriteValueToIniFile(iniFile, m_value.c_str(), error);
	}
	unsigned int m_guessSize;
	unsigned int m_maxSize;
};

template<class V>
class SignedNumberIniValue : public TypeIniValue<V>
{
public:
	SignedNumberIniValue(const char* section, const char* entry, const char* file, bool eraseIfDefault, const ValueType& value):TypeIniValue(section, entry, file, eraseIfDefault, value){}
protected:
	virtual bool DoExtractValue() override
	{
//		m_value = m_initialValue = m_section && m_file ? (ValueType)GetPrivateProfileInt(m_section, m_entry, m_defaultValue, m_file) : m_defaultValue;
//		return true;
		std::string value;
		if(U_GetPrivateProfileString(value, m_section, m_entry, "", m_file, 16, 16))
		{
			m_initialValue = m_value = value.empty() ? m_defaultValue : U_GetSignedNumberFromString<V>(value.c_str());//strtoul(value.c_str(), nullptr, 10);
			return true;
		}
		return false;
	}
//	virtual bool DoSaveValue(std::string* error) const override
	virtual bool DoSaveValueToIniFile(const char* iniFile, std::string* error) const override
	{
		char num[33];
		return WriteValueToIniFile(iniFile, U_SignedNumberToStrNoDecDigits(m_value, num, sizeof(num)), error);
	}
};

template<class V>
class UnsignedNumberIniValue : public TypeIniValue<V>
{
public:
	UnsignedNumberIniValue(const char* section, const char* entry, const char* file, bool eraseIfDefault, const unsigned int& value):TypeIniValue(section, entry, file, eraseIfDefault, value){}
protected:
	virtual bool DoExtractValue() override
	{
		std::string value;
		if(U_GetPrivateProfileString(value, m_section, m_entry, "", m_file, 16, 16))
		{
			m_initialValue = m_value = value.empty() ? m_defaultValue : (ValueType)U_GetUnsignedNumberFromString<V>(value.c_str());//strtoul(value.c_str(), nullptr, 10);
			return true;
		}
		return false;
	}
//	virtual bool DoSaveValue(std::string* error) const override
	virtual bool DoSaveValueToIniFile(const char* iniFile, std::string* error) const override
	{
		char num[33];
		return WriteValueToIniFile(iniFile, U_UnsignedNumberToStrNoDecDigits(m_value, num, sizeof(num)), error);
	}
};

template<class V>
class UnsignedNumberHexIniValue : public TypeIniValue<V>
{
public:
	UnsignedNumberHexIniValue(const char* section, const char* entry, const char* file, bool eraseIfDefault, const unsigned int& value):TypeIniValue(section, entry, file, eraseIfDefault, value){}
protected:
	virtual bool DoExtractValue() override
	{
		std::string value;
		if(U_GetPrivateProfileString(value, m_section, m_entry, "", m_file, 16, 16))
		{
			m_initialValue = m_value = U_GetHexUnsignedNumberFromString<V>(value.c_str());//strtoul(value.c_str(), nullptr, 16);
			return true;
		}
		return false;
	}
//	virtual bool DoSaveValue(std::string* error) const override
	virtual bool DoSaveValueToIniFile(const char* iniFile, std::string* error) const override
	{
		char num[33];
		return WriteValueToIniFile(iniFile, U_UnsignedNumberHexToStr(m_value, num, sizeof(num)), error);
	}
};

class U_API IpIniValue : public TypeIniValue<unsigned int>
{
public:
	IpIniValue(const char* section, const char* entry, const char* file, bool eraseIfDefault, const unsigned int& value):TypeIniValue(section, entry, file, eraseIfDefault, value){}
protected:
	virtual bool DoExtractValue() override
	{
		std::string value;
		if(U_GetPrivateProfileString(value, m_section, m_entry, "", m_file, 24, 24))
		{
			m_initialValue = m_value = U_ConvertStringToIp(value.c_str());
			m_valid = m_value != 0;
			return m_valid;
		}
		return false;
	}
//	virtual bool DoSaveValue(std::string* error) const override
	virtual bool DoSaveValueToIniFile(const char* iniFile, std::string* error) const override
	{
		char ip[16];
		if(U_ConvertIpToString(m_value, ip, sizeof(ip)))
		{
			return WriteValueToIniFile(iniFile, ip, error);
		}
		return false;
	}
};

class U_API BoolIniValue : public TypeIniValue<bool>
{
public:
	BoolIniValue(const char* section, const char* entry, const char* file, bool eraseIfDefault, const bool& value):TypeIniValue(section, entry, file, eraseIfDefault, value){}
protected:
	virtual bool DoExtractValue() override
	{
		m_value = m_initialValue =
			m_section && m_file ?
				GetPrivateProfileInt(m_section, m_entry, m_defaultValue ? 1 : 0, m_file) != 0:
				m_defaultValue;
		return true;
	}
//	virtual bool DoSaveValue(std::string* error) const override
	virtual bool DoSaveValueToIniFile(const char* iniFile, std::string* error) const override
	{
		return WriteValueToIniFile(iniFile, m_value ? "1" : "0", error);
	}
};

class U_API MapIniValue : public TypeIniValue<std::map<std::string, std::string> >
{
public:
//	typedef std::map<std::string, std::string> StringMap;
	MapIniValue(const char* section, const char* file, unsigned int guessSize = 1024, unsigned int maxSize = 0x10000):
		TypeIniValue(section, "", file, false, std::map<std::string, std::string>()),
		m_guessSize(guessSize < 3 ? 3 : guessSize),
		m_maxSize(maxSize < m_guessSize ? m_guessSize : maxSize),
		m_valueEnd(m_value.cend()),
		m_initialValueEnd(m_initialValue.cend())
	{}
	bool AddValue(const char* key, const char* value);
	bool RemoveValue(const char* key){return m_value.erase(std::string(key)) > 0;}
	bool RemoveValue(const std::string& key){return m_value.erase(key) > 0;}
	bool ClearValues(){if(m_value.empty())return false; m_value.clear(); return true;}
	unsigned int GetCount() const{return (unsigned int)m_value.size();}
	const ValueType::const_iterator& GetValueEnd() const{return m_valueEnd;}
	const ValueType::const_iterator& GetInitialValueEnd() const{return m_initialValueEnd;}
protected:
	virtual bool DoExtractValue() override;
	virtual bool DoSaveValue(std::string* error = nullptr) const override;
	virtual bool DoSaveValueToIniFile(const char* iniFile, std::string* error) const override;
	unsigned int m_guessSize;
	unsigned int m_maxSize;
	ValueType::const_iterator m_valueEnd;
	ValueType::const_iterator m_initialValueEnd;
};

class ThermographVectorUShort;

class U_API Thermograph
{
public:
	Thermograph(unsigned short capacity);
	~Thermograph();
	void AddValue(unsigned short value);
	void AddValue(unsigned short value, unsigned short count);
	void clear();
	unsigned short capacity() const;
	unsigned short size() const;
	const unsigned short& operator[](unsigned short pos) const;
	unsigned short GetFirstValue() const;
	void ResetIterator() const;
	void ResetIterator(unsigned short skip) const;
	unsigned short GetNextValue() const;
	unsigned int GetSum() const;
//	void InitAllValues(unsigned short value);
	void NullifyAllValues();
protected:
	ThermographVectorUShort* m_vector;
};

template<class T>
class PointLocator
{
public:
	typedef T ValueType;
	PointLocator(const T& start):
		m_start(start),
		m_end(start)
	{}
	PointLocator(const T& start, const T& end):
		m_start(start),
		m_end(end)
	{}
	inline const T& GetStart() const{return m_start;}
	inline const T& GetEnd() const{return m_end;}
	inline void SetStartOnly(const T& start){m_start = start;}
	inline void SetEndOnly(const T& end){m_end = end;}
	inline void SetStartEnd(const T& start, const T& end){m_start = start; m_end = end;}
	inline T GetSize() const{return m_end - m_start;}
	inline void SetSize(const T& size){m_end = m_start + size;}

	inline void SetStart(const T& start)
	{
		if(m_start != start)
		{
			if(m_start < start)
			{
				m_end += (start - m_start);
			}
			else
			{
				m_end -= (m_start - start);
			}
			m_start = start;
		}
	}
	inline void Increment(){++m_start; ++m_end;}
	inline void Decrement(){--m_start; --m_end;}
	inline void Increment(const T& diff){m_start += diff; m_end += diff;}
	inline void Decrement(const T& diff){m_start -= diff; m_end -= diff;}
	inline void IncrementEnd(){++m_end;}
	inline void DecrementEnd(){--m_end;}
	inline void IncrementEnd(const T& diff){m_end += diff;}
	inline void DecrementEnd(const T& diff){m_end -= diff;}
	inline void IncrementStart(){++m_start;}
	inline void DecrementStart(){--m_start;}
	inline void IncrementStart(const T& diff){m_start += diff;}
	inline void DecrementStart(const T& diff){m_start -= diff;}
protected:
	T m_start;
	T m_end;
};
/*
template<class C>//unsigned
struct lessNumberAsString : public std::binary_function<C, C, bool>
{	// functor for operator<
	bool operator()(const C& p1, const C& p2) const
	{	// apply operator< to operands
		const unsigned char* c1 = (const unsigned char*)&p1;
		const unsigned char* c2 = (const unsigned char*)&p2;
		unsigned char a1 = *c1;
		unsigned char a2 = *c2;
		for(unsigned char i = sizeof(C); i; --i, a1 = *++c1, a2 = *++c2)
		{
			if(a1 < a2)
			{
				return true;
			}
			if(a1 > a2 || !a1)
			{
				return false;
			}
		}
		return false;
	}
};
*/
template<class T>
struct lessPointLocator : public std::binary_function<PointLocator<T>, PointLocator<T>, bool>
{	// functor for operator<
	bool operator()(const PointLocator<T>& ra1, const PointLocator<T>& ra2) const
	{	// apply operator< to operands
		return ra1.GetEnd() < ra2.GetStart() || ra1.GetStart() < ra2.GetStart() && ra1.GetEnd() == ra2.GetStart();
	}
};

typedef PointLocator<size_t> PointLocatorSize;
typedef PointLocator<int> PointLocatorInt;

#ifdef _DEBUG
#include <assert.h>
//#define CHECK_CHAIN
#endif

template<class T, unsigned char N>
class TakionId
{
public:
	TakionId(const char* id)
	{
		char* dst = (char*)m_id;
		unsigned char i = 0;
		unsigned char j;
		for(; i < N; ++i)
		{
			if(!*id)
			{
				break;
			}
			for(j = 0; *id && j < sizeof(T); ++j, ++dst, ++id)
			{
				*dst = *id;
			}
			if(j < sizeof(T))
			{
				if(sizeof(T) >= sizeof(unsigned short))
				{
					if(j & 1)
					{
						*dst = 0;
						++dst;
						++j;
					}
					if(sizeof(T) >= sizeof(unsigned int))
					{
						j >>= 1;
						if(j & 1)
						{
							*(unsigned short*)dst = 0;
							dst += sizeof(unsigned short);
							++j;
						}
					}
					if(sizeof(T) >= sizeof(unsigned __int64))
					{
						j >>= 1;
						if(j & 1)
						{
							*(unsigned int*)dst = 0;
//							dst += sizeof(unsigned int);
//							++j;
						}
					}
				}
				++i;
				break;
			}
		}
		if(i < N)
		{
			T* cursor = m_id + i;
			for(; i < N; ++i)
			{
				*cursor = 0;
			}
		}
	}
	TakionId(const T* t)
	{
		T* cursor = m_id;
		for(unsigned char i = 0; i < N; ++i, ++cursor, ++t)
		{
			*cursor = *t;
		}
	}
	TakionId(const T* t, unsigned char length)
	{
		if(length > N)
		{
			length = N;
		}
		T* cursor = m_id;
		unsigned char i = 0;
		for(; i < length; ++i, ++cursor, ++t)
		{
			*cursor = *t;
		}
//		std::memcpy(m_id, t, sizeof(T) * length);
		if(i < N)
		{
			for(; i < N; ++i, ++cursor)
			{
				*cursor = 0;
			}
//			memset(m_id + length, 0, sizeof(T) * (N - length));
		}
	}
	const char* GetId() const{return (const char*)m_id;}
	const T& GetToken(unsigned char ordinal) const{return m_id[ordinal];}
//	operator size_t() const{return *m_id;}
	size_t GetHashValue() const{return *m_id;}
	bool operator<(const TakionId& other) const
	{
		const T* cursor = m_id;
		const T* cursorOther = other. m_id;
		for(unsigned char i = 0; i < N; ++i, ++cursor, ++cursorOther)
		{
			if(*cursor < *cursorOther)
			{
				return true;
			}
			if(*cursor > *cursorOther)
			{
				return false;
			}
		}
		return false;
	}
	bool operator==(const TakionId& other) const
	{
//		return m_first == other.m_first && m_second == other.m_second;
		const T* cursor = m_id;
		const T* cursorOther = other. m_id;
		for(unsigned char i = 0; i < N; ++i, ++cursor, ++cursorOther)
		{
			if(*cursor != *cursorOther)
			{
				return false;
			}
		}
		return true;
	}
	bool operator!=(const TakionId& other) const{return !operator==(other);}
protected:
	T m_id[N];
};

template<class T>
T U_RemoveBitFromMaskAndShift(const T& mask, const unsigned char& bitNumber)//bitNumber is zero based
{
	T removeFlag = 1;
	removeFlag <<= bitNumber;
	return ((mask & ~((removeFlag << 1) - 1)) >> 1) | (mask & (removeFlag - 1));
}

inline char U_CompareStrings(const char* first, const char* second)
{
	char charFirst = *first;
	char charSecond = *second;
	for(; ; charFirst = *++first, charSecond = *++second)
	{
		if(charFirst < charSecond)return -1;
		else if(charFirst > charSecond)return 1;
		else if(!charFirst)return 0;
	}
	return 0;
}

template<class C>
char U_CompareUIntAsString(const C& first, const C& second)
{
	C byteFirst;
	C byteSecond;
	for(C byteValue = 0xFF; ; byteValue <<= 8)
	{
		byteFirst = first & byteValue;
		byteSecond = second & byteValue;
		if(byteFirst < byteSecond)return -1;
		else if(byteFirst > byteSecond)return 1;
		else if(!byteFirst)return 0;
	}
	return 0;
}

template<class C>
bool U_UIntLessAsString(const C& first, const C& second)
{
	C byteFirst;
	C byteSecond;
	for(C byteValue = 0xFF; ; byteValue <<= 8)
	{
		byteFirst = first & byteValue;
		byteSecond = second & byteValue;
		if(byteFirst != byteSecond)return byteFirst < byteSecond;
		if(!byteFirst)return false;
	}
	return false;
}

template<class C>
bool U_UIntGreaterAsString(const C& first, const C& second)
{
	C byteFirst;
	C byteSecond;
	for(C byteValue = 0xFF; ; byteValue <<= 8)
	{
		byteFirst = first & byteValue;
		byteSecond = second & byteValue;
		if(byteFirst != byteSecond)return byteFirst > byteSecond;
		if(!byteFirst)return false;
	}
	return false;
}

template<class T, unsigned short N>//unsigned short, int, __int64, size_t
class StrAsNumberArray
{
public:
	typedef T NumberType;
	StrAsNumberArray()//:m_length(0)
	{
		Initialize();
	}
	explicit StrAsNumberArray(const char* cursor):m_wholeNumberCountPlusOneFraction(N)
	{
		DoSetString(cursor);
//		ClearTail();
	}
	StrAsNumberArray(const char*& cursor, const char& del):m_wholeNumberCountPlusOneFraction(N)
	{
		DoSetStringWithDelimiter(cursor, del);
//		ClearTail();
	}
/*
	StrAsNumberArray(const char* cursor, unsigned short length):m_wholeNumberCountPlusOneFraction(N)//length is how many chars max you want to get from cursor
	{
		DoSetString(cursor, length);
//		ClearTail();
	}
*/
	StrAsNumberArray(const char*& cursor, unsigned short length, const char& del):m_wholeNumberCountPlusOneFraction(N)//length is how many chars max you want to get from cursor
	{
		DoSetStringWithDelimiter(cursor, length, del);
//		ClearTail();
	}
	StrAsNumberArray(const std::string& str):m_wholeNumberCountPlusOneFraction(N)
	{
		DoSetString((const unsigned short&)str.length(), str.c_str());
	}
	StrAsNumberArray(const unsigned short& exactLength, const char* cursor):m_wholeNumberCountPlusOneFraction(N)
	{
		DoSetString(exactLength, cursor);
//		ClearTail();
	}
	StrAsNumberArray(const StrAsNumberArray& other):
		m_length(other.m_length),
		m_wholeNumberCount(other.m_wholeNumberCount),
		m_wholeNumberCountPlusOneFraction(other.m_wholeNumberCountPlusOneFraction)
//		m_wholeLength(other.m_wholeLength)
	{
		CopyArray(other.m_numberArray);
	}
	StrAsNumberArray& operator=(const StrAsNumberArray& other)
	{
		CopyNormalizedArray(other);
		m_length = other.m_length;
		m_wholeNumberCount = other.m_wholeNumberCount;
		m_wholeNumberCountPlusOneFraction = other.m_wholeNumberCountPlusOneFraction;
//		m_wholeLength = other.m_wholeLength;
		return *this;
	}
	void SetString(const char* cursor)
	{
		DoSetString(cursor);
//		ClearNormalizedTail();
	}
	void SetStringWithDelimiter(const char*& cursor, const char& del)
	{
		DoSetStringWithDelimiter(cursor, del);
//		ClearNormalizedTail();
	}
	void AddString(const char* cursor)
	{
		DoAddString(cursor);
	}
	void AddString(const char*& cursor, const char& del)
	{
		DoAddString(cursor, del);
	}
	void AddChar(const char& c)
	{
		DoAddChar(c);
	}
	void AddOrSetCharAt(const char& c, const unsigned short& at)
	{
		DoAddOrSetCharAt(c, at);
	}
	void AddOrSetCharAt(const char& c, const char& altChar, const unsigned short& at)
	{
		DoAddOrSetCharAt(c, altChar, at);
	}
	void Truncate(const unsigned short& length)
	{
		if(length < m_length)
		{
			m_length = length;
			UpdateWholeNumbers();
		}
	}
	void TruncateByLength(const unsigned short& length)
	{
		if(length < m_length)
		{
			m_length -= length;
			UpdateWholeNumbers();
		}
		else
		{
			Clear();
		}
	}
	void SetString(const char* cursor, unsigned short length)
	{
		DoSetString(cursor, length);
//		ClearNormalizedTail();
	}
	void SetString(const char*& cursor, unsigned short length, const char& del)
	{
		DoSetStringWithDelimiter(cursor, length, del);
//		ClearNormalizedTail();
	}
	void SetString(const std::string& str)
	{
		DoSetString((const unsigned short&)str.length(), str.c_str());
	}
	void SetString(const unsigned short& exactLength, const char* cursor)//when the exact length of string is known
	{
		DoSetString(exactLength, cursor);
//		ClearNormalizedTail();
	}
	const unsigned short& GetLength() const{return m_length;}
	bool isEmpty() const{return !m_length;}
	bool operator==(const StrAsNumberArray& other) const{return m_length == other.m_length && isArrayOfLengthEqual(other.m_numberArray);}
	bool operator!=(const StrAsNumberArray& other) const{return !operator==(other);}
	short Compare(const StrAsNumberArray& other) const//{return CompareArrayOfLength(other.m_numberArray);}
	{
		return m_length < other.m_length ? -1:
			m_length > other.m_length ? 1:
			CompareArrayOfLength(other.m_numberArray);
	}
	bool operator<(const StrAsNumberArray& other) const{return Compare(other) < 0;}
	bool operator>(const StrAsNumberArray& other) const{return Compare(other) > 0;}
	bool operator<=(const StrAsNumberArray& other) const{return Compare(other) <= 0;}
	bool operator>=(const StrAsNumberArray& other) const{return Compare(other) >= 0;}

	short CompareAsStrings(const StrAsNumberArray& other) const//, unsigned short length) const
	{
		const NumberType* cursor = m_numberArray;
		const NumberType* cursorOther = other.m_numberArray;
		for(unsigned short length = N; length; --length, ++cursor, ++cursorOther)
		{
			if(*cursor != *cursorOther)
			{
				return U_CompareUIntAsString(*cursor, *cursorOther);
			}
/*
			if(!*cursor)
			{
				break;
			}
*/
		}
		return 0;
	}
//	operator size_t() const{return (size_t)*m_numberArray;}
	size_t GetHashValue() const{return (size_t)*m_numberArray;}
	operator int() const{return (int)*m_numberArray;}
	operator long() const{return (long)*m_numberArray;}
	void Initialize()
	{
		m_length = m_wholeNumberCount = m_wholeNumberCountPlusOneFraction = 0;//m_wholeLength = 0;
		NumberType* cursor = m_numberArray;
		for(unsigned short i = 0; i < N; ++i, ++cursor)
		{
			*cursor = 0;
		}
	}
	void Clear()
	{
		m_length = m_wholeNumberCount = 0;//m_wholeLength = 0;
		NumberType* cursor = m_numberArray;
		for(; m_wholeNumberCountPlusOneFraction; --m_wholeNumberCountPlusOneFraction, ++cursor)
		{
			*cursor = 0;
		}
	}
	const char* GetString() const{return (const char*)m_numberArray;}
protected:
	NumberType m_numberArray[N];
	unsigned short m_length;
	unsigned short m_wholeNumberCount;
	unsigned short m_wholeNumberCountPlusOneFraction;
//	unsigned short m_wholeLength;
	void DoSetString(const unsigned short& exactLength, const char* cursor)
	{
		const NumberType* numberCursorOther = (const NumberType*)cursor;

		m_wholeNumberCount = exactLength / sizeof(NumberType);
		unsigned short wholeNumberCountPlusOneFraction;
		unsigned short fraction = 0;
		char* fractionDst = nullptr;
		if(m_wholeNumberCount > N)
		{
			m_wholeNumberCount = wholeNumberCountPlusOneFraction = N;
			cursor = nullptr;
//			m_length = m_wholeLength = N * sizeof(NumberType);
			m_length = N * sizeof(NumberType);
		}
		else
		{
			wholeNumberCountPlusOneFraction = m_wholeNumberCount;
			m_length = exactLength;
			if(m_wholeNumberCount < N)
			{
				const unsigned short wholeLength = m_wholeNumberCount * sizeof(NumberType);
				if(wholeLength == exactLength)
				{
					cursor = nullptr;
				}
				else
				{
					++wholeNumberCountPlusOneFraction;
					fraction = exactLength - wholeLength;
					cursor += wholeLength;
					fractionDst = (char*)m_numberArray + wholeLength;
				}
			}
			else
			{
				cursor = nullptr;
			}
		}
/*
		else if(m_wholeNumberCount < N)
		{
			wholeNumberCountPlusOneFraction = m_wholeNumberCount;
//			m_wholeLength = m_wholeNumberCount * sizeof(NumberType);
//			if(m_wholeLength == exactLength)
			unsigned short wholeLength = m_wholeNumberCount * sizeof(NumberType);
			if(wholeLength == exactLength)
			{
				cursor = nullptr;
			}
			else
			{
				++wholeNumberCountPlusOneFraction;
				fraction = exactLength - wholeLength;
				cursor += wholeLength;
				fractionDst = (char*)m_numberArray + wholeLength;
			}
			m_length = exactLength;
		}
		else
		{
			wholeNumberCountPlusOneFraction = m_wholeNumberCount;
//			m_wholeLength = m_wholeNumberCount * sizeof(NumberType);
			cursor = nullptr;
			m_length = exactLength;
		}
*/
		if(m_wholeNumberCountPlusOneFraction > m_wholeNumberCount)//m_wholeNumberCount already changed, m_wholeNumberCountPlusOneFraction is old
		{
			NumberType* nc = m_numberArray + m_wholeNumberCount;
			for(unsigned short i = m_wholeNumberCount; i < m_wholeNumberCountPlusOneFraction; ++i, ++nc)
			{
				*nc = 0;
			}
		}
		m_wholeNumberCountPlusOneFraction = wholeNumberCountPlusOneFraction;

		NumberType* numberCursor = m_numberArray;

		for(unsigned short wholeNumberCount = m_wholeNumberCount; wholeNumberCount; --wholeNumberCount, ++numberCursor, ++numberCursorOther)
		{
			*numberCursor = *numberCursorOther;
		}
		if(cursor)
		{
			for(; fraction; --fraction, ++cursor, ++fractionDst)
			{
				*fractionDst = *cursor;
			}
		}
	}
	void DoSetString(const char* cursor)
	{
		m_length = 0;
		char* dst = (char*)m_numberArray;
		char c = *cursor;
		for(unsigned short length = N * sizeof(NumberType); c && length; --length, c = *++cursor, ++dst, ++m_length)
		{
			*dst = c;
		}
		UpdateWholeNumbers();
	}
	void DoSetStringWithDelimiter(const char*& cursor, const char& del)
	{
		m_length = 0;
		char* dst = (char*)m_numberArray;
		char c = *cursor;
		for(unsigned short length = N * sizeof(NumberType); c && c != del && length; --length, c = *++cursor, ++dst, ++m_length)
		{
			*dst = c;
		}
		if(del == c && del)++cursor;

		UpdateWholeNumbers();
	}
	void DoAddChar(const char& c)
	{
		if(c)
		{
			unsigned short length = N * sizeof(NumberType) - m_length;
			if(N * sizeof(NumberType) > m_length)
			{
				char* dst = (char*)m_numberArray + m_length;
				*dst = c;
				++m_length;
				UpdateWholeNumbers();
			}
		}
	}
	void DoAddOrSetCharAt(const char& c, const unsigned short& at)
	{
		if(at < m_length)
		{
			if(c)
			{
				char* dst = (char*)m_numberArray + at;
				*dst = c;
			}
		}
		else
		{
			DoAddChar(c);
		}
	}
	void DoAddOrSetCharAt(const char& c, const char& altChar, const unsigned short& at)
	{
		if(at < m_length)
		{
			if(c)
			{
				char* dst = (char*)m_numberArray + at;
				if(*dst )
				*dst = c == *dst ? altChar : c;
			}
		}
		else
		{
			DoAddChar(c);
		}
	}
	void DoAddString(const char* cursor)
	{
		char c = *cursor;
		if(c)
		{
			unsigned short length = N * sizeof(NumberType) - m_length;
			if(length)
			{
//				char* dst = (char*)m_numberArray + m_length;
				for(char* dst = (char*)m_numberArray + m_length; c && length; --length, c = *++cursor, ++dst, ++m_length)
				{
					*dst = c;
				}
				UpdateWholeNumbers();
			}
		}
	}
	void DoAddString(const char*& cursor, const char& del)
	{
		char c = *cursor;
		if(c)
		{
			unsigned short length = N * sizeof(NumberType) - m_length;
			if(length)
			{
//				char* dst = (char*)m_numberArray + m_length;
				for(char* dst = (char*)m_numberArray + m_length; c && c != del && length; --length, c = *++cursor, ++dst, ++m_length)
				{
					*dst = c;
				}
				if(del == c && del)++cursor;
				UpdateWholeNumbers();
			}
		}
	}
	void DoSetString(const char* cursor, unsigned short length)//length is how many chars max you want to get from cursor
	{
		if(length > N * sizeof(NumberType))
		{
			length = N * sizeof(NumberType);
		}
		m_length = 0;
		char* dst = (char*)m_numberArray;
		char c = *cursor;
		for(; c && length; --length, c = *++cursor, ++dst, ++m_length)
		{
			*dst = c;
		}
		UpdateWholeNumbers();
	}
	void DoSetStringWithDelimiter(const char*& cursor, unsigned short length, const char& del)//length is how many chars max you want to get from cursor
	{
		if(length > N * sizeof(NumberType))
		{
			length = N * sizeof(NumberType);
		}
		m_length = 0;
		char* dst = (char*)m_numberArray;
		char c = *cursor;
		for(; c && c != del && length; --length, c = *++cursor, ++dst, ++m_length)
		{
			*dst = c;
		}
		if(del == c && del)++cursor;
		UpdateWholeNumbers();
	}
	void UpdateWholeNumbers()
	{
		unsigned short wholeNumberCountPlusOneFraction;
		m_wholeNumberCount = wholeNumberCountPlusOneFraction = m_length / sizeof(NumberType);
//		m_wholeLength = m_wholeNumberCount * sizeof(NumberType);
		unsigned short wholeLength = m_wholeNumberCount * sizeof(NumberType);
//		if(m_wholeLength != m_length)
		if(wholeLength != m_length)
		{
			++wholeNumberCountPlusOneFraction;
//			unsigned short count = m_wholeLength + sizeof(NumberType) - m_length;
			unsigned short count = wholeLength + sizeof(NumberType) - m_length;
			for(char* cursor = (char*)m_numberArray + m_length; count; --count, ++cursor)
			{
				*cursor = '\0';
			}
		}

		if(m_wholeNumberCountPlusOneFraction > wholeNumberCountPlusOneFraction)
		{
			NumberType* nc = m_numberArray + wholeNumberCountPlusOneFraction;
			for(unsigned short i = wholeNumberCountPlusOneFraction; i < m_wholeNumberCountPlusOneFraction; ++i, ++nc)
			{
				*nc = 0;
			}
		}

		m_wholeNumberCountPlusOneFraction = wholeNumberCountPlusOneFraction;
	}
/*
	void ClearTail()
	{
		if(m_wholeNumberCount < N)
		{
			if(m_length != m_wholeLength)
			{
				unsigned short fractionLength = m_wholeLength + sizeof(NumberType) - m_length;
				for(char* cursor = (char*)m_numberArray + m_length; fractionLength; --fractionLength, ++cursor)
				{
					*cursor = '\0';
				}
			}
			if(m_wholeNumberCountPlusOneFraction < N)
			{
				unsigned short wholeNumberCount = m_wholeNumberCountPlusOneFraction;
				for(NumberType* numberCursor = m_numberArray + wholeNumberCount; wholeNumberCount < N; ++wholeNumberCount, ++numberCursor)
				{
					*numberCursor = 0;
				}
			}
		}
	}
*/
/*
	void ClearNormalizedTail()
	{
//		if(m_length < N * sizeof(NumberType))
		if(m_wholeNumberCount < N)
		{
			if(m_length != m_wholeLength)
			{
				char* cursor = (char*)m_numberArray + m_length;
				for(unsigned short fractionLength = m_wholeLength + sizeof(NumberType) - m_length; fractionLength; --fractionLength, ++cursor)
				{
					*cursor = '\0';
				}
			}
			if(m_wholeNumberCountPlusOneFraction < N)
			{
				unsigned short wholeNumberCount = m_wholeNumberCountPlusOneFraction;
				for(NumberType* numberCursor = m_numberArray + wholeNumberCount; wholeNumberCount < N; ++wholeNumberCount, ++numberCursor)
				{
					if(*numberCursor)
					{
						*numberCursor = 0;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
*/
private:
	void CopyArray(const NumberType* cursorOther)
	{
		NumberType* cursor = m_numberArray;
		for(unsigned short i = 0; i < N; ++i, ++cursor, ++cursorOther)
		{
			*cursor = *cursorOther;
		}
	}
	void CopyNormalizedArray(const StrAsNumberArray& other)
	{
		NumberType* cursor = m_numberArray;
		const NumberType* cursorOther = other.m_numberArray;
//		unsigned short count = other.m_wholeNumberCountPlusOneFraction;
//		unsigned short i = 0;
		for(unsigned short i = 0, count = other.m_wholeNumberCountPlusOneFraction; i < count; ++i, ++cursor, ++cursorOther)
		{
			if(*cursorOther)
			{
				*cursor = *cursorOther;
			}
			else
			{
				count = m_wholeNumberCountPlusOneFraction;
//				for(; i < m_wholeNumberCountPlusOneFraction; ++i, ++cursor)
				for(; i < count; ++i, ++cursor)
				{
					*cursor = 0;
				}
				break;
			}
		}
	}

	bool isArrayOfLengthEqual(const NumberType* cursorOther) const//, unsigned short length) const
	{
		const NumberType* cursor = m_numberArray;
//		for(unsigned short length = N; length; --length, ++cursor, ++cursorOther)
		for(unsigned short length = m_wholeNumberCountPlusOneFraction; length; --length, ++cursor, ++cursorOther)
		{
			if(*cursor != *cursorOther)return false;
//			if(!*cursor)break;
		}
		return true;
	}

	short CompareArrayOfLength(const NumberType* cursorOther) const//, unsigned short length) const
	{
		const NumberType* cursor = m_numberArray;
//		for(unsigned short length = N; length; --length, ++cursor, ++cursorOther)
		for(unsigned short length = m_wholeNumberCountPlusOneFraction; length; --length, ++cursor, ++cursorOther)
		{
			if(*cursor < *cursorOther)return -1;
			if(*cursor > *cursorOther)return 1;

//			if(!*cursor)break;
		}
		return 0;
	}

};

//template<class T, unsigned short N>//unsigned short, int, __int64, size_t
template<class C>
struct lessStrAsNumberArrayAsStr : public std::binary_function<C, C, bool>
{
//	bool operator()(const StrAsNumberArray& p1, const StrAsNumberArray& p2) const
	bool operator()(const C& p1, const C& p2) const
	{
		return p1.CompareAsStrings(p2) < 0;
	}
};

template<class T>//unsigned short, int, __int64, size_t
class StrAsVarNumberArray
{
public:
	typedef T NumberType;
	StrAsVarNumberArray():m_numberArray(nullptr), m_arraySize(0)//, m_length(0)
	{
		DoSetString("", 0);
//		ClearTail();
	}
	StrAsVarNumberArray(const char* cursor):m_numberArray(nullptr), m_arraySize(0)
	{
		DoSetString(cursor);
//		ClearTail();
	}

	StrAsVarNumberArray(const char*& cursor, const char& del):m_numberArray(nullptr), m_arraySize(0)
	{
		DoSetStringWithDelimiter(cursor, del);
//		ClearTail();
	}
/*
	StrAsVarNumberArray(const char* cursor, const unsigned short& length):m_numberArray(nullptr), m_arraySize(0)//length is how many chars max you want to get from cursor
	{
		DoSetString(cursor, length);
	}
*/
	StrAsVarNumberArray(const char*& cursor, const unsigned short& length, const char& del):m_numberArray(nullptr), m_arraySize(0)//length is how many chars max you want to get from cursor
	{
		DoSetStringWithDelimiter(cursor, length, del);
//		ClearTail();
	}
	StrAsVarNumberArray(const std::string& str):m_numberArray(nullptr), m_arraySize(0)
	{
		DoSetString((const unsigned short&)str.length(), str.c_str());
	}
	StrAsVarNumberArray(const unsigned short& exactLength, const char* cursor):m_numberArray(nullptr), m_arraySize(0)
	{
		DoSetString(exactLength, cursor);
//		ClearTail();
	}
	StrAsVarNumberArray(const StrAsVarNumberArray& other):
		m_numberArray(new NumberType[other.m_arraySize]),
		m_arraySize(other.m_arraySize),
		m_length(other.m_length),
		m_wholeNumberCount(other.m_wholeNumberCount),
		m_wholeNumberCountPlusOneFraction(other.m_wholeNumberCountPlusOneFraction)
//		m_wholeLength(other.m_wholeLength)
	{
		CopyArray(other.m_numberArray);
	}

#if (_MSC_VER > 1600)
// Move constructor.  
	StrAsVarNumberArray(StrAsVarNumberArray&& other):
		m_numberArray(nullptr),
		m_arraySize(other.m_arraySize),
		m_length(other.m_length),
		m_wholeNumberCount(other.m_wholeNumberCount),
		m_wholeNumberCountPlusOneFraction(other.m_wholeNumberCountPlusOneFraction)
	{
		// Copy the data pointer and its length from the   
		// source object.  
		m_numberArray = other.m_numberArray;
//		m_arraySize = other.m_arraySize;

		// Release the data pointer from the source object so that  
		// the destructor does not free the memory multiple times.  
		other.m_numberArray = nullptr;
		other.m_arraySize = 0;
		other.m_length = 0;
		other.m_wholeNumberCount = 0;
		other.m_wholeNumberCountPlusOneFraction = 0;
	}

// Move assignment operator.  
	StrAsVarNumberArray& operator=(StrAsVarNumberArray&& other)
	{
		if(this != &other)
		{
// Free the existing resource.  
			if(m_numberArray)delete[] m_numberArray;

// Copy the data pointer and its length from the   
// source object.  
			m_numberArray = other.m_numberArray;
			m_arraySize = other.m_arraySize;
			m_length = other.m_length ;
			m_wholeNumberCount = other.m_wholeNumberCount ;
			m_wholeNumberCountPlusOneFraction = other.m_wholeNumberCountPlusOneFraction;

			// Release the data pointer from the source object so that  
			// the destructor does not free the memory multiple times.  
			other.m_numberArray = nullptr;
			other.m_arraySize = 0;
			other.m_length = 0;
			other.m_wholeNumberCount = 0;
			other.m_wholeNumberCountPlusOneFraction = 0;
		}
		return *this;
	}  
#endif
	~StrAsVarNumberArray()
	{
		if(m_numberArray)delete[] m_numberArray;
	}
	StrAsVarNumberArray& operator=(const StrAsVarNumberArray& other)
	{
		if(m_arraySize != other.m_arraySize)
		{
			if(m_numberArray)delete[] m_numberArray;
			m_arraySize = other.m_arraySize;
			m_numberArray = new NumberType[m_arraySize];
		}
		m_length = other.m_length;
		m_wholeNumberCount = other.m_wholeNumberCount;
		m_wholeNumberCountPlusOneFraction = other.m_wholeNumberCountPlusOneFraction;
//		m_wholeLength = other.m_wholeLength;
//		CopyNormalizedArray(other.m_numberArray);
		CopyArray(other.m_numberArray);
		return *this;
	}
	void SetString(const char* cursor)
	{
		DoSetString(cursor);
//		ClearTail();
	}
	void SetString(const char* cursor, const unsigned short& length)
	{
		DoSetString(cursor, length);
//		ClearTail();
	}
	void SetString(const std::string& str)
	{
		DoSetString((const unsigned short&)str.length(), str.c_str());
	}
	void SetString(const unsigned short& exactLength, const char* cursor)//when the exact length of string is known
	{
		DoSetString(exactLength, cursor);
//		ClearTail();
	}
	const unsigned short& GetLength() const{return m_length;}
	bool isEmpty() const{return !m_length;}
	bool operator==(const StrAsVarNumberArray& other) const
	{
//		if(m_wholeNumberCountPlusOneFraction == other.m_wholeNumberCountPlusOneFraction)
		if(m_length == other.m_length)
		{
			const NumberType* cursor = m_numberArray;
			const NumberType* cursorOther = other.m_numberArray;
			for(unsigned short length = m_wholeNumberCountPlusOneFraction; length; --length, ++cursor, ++cursorOther)
			{
				if(*cursor != *cursorOther)return false;
			}
			return true;
		}
		return false;
//		return isArrayOfLengthEqual(other.m_numberArray);
	}
	bool operator!=(const StrAsVarNumberArray& other) const{return !operator==(other);}
/*
	short Compare(const StrAsVarNumberArray& other) const
	{
		const NumberType* cursor = m_numberArray;
		const NumberType* cursorOther = other.m_numberArray;
		const bool less = m_wholeNumberCountPlusOneFraction < other.m_wholeNumberCountPlusOneFraction;
//		for(unsigned short length = less ? other.m_wholeNumberCountPlusOneFraction : m_wholeNumberCountPlusOneFraction; length; --length, ++cursor, ++cursorOther)
		for(unsigned short length = less ? m_wholeNumberCountPlusOneFraction : other.m_wholeNumberCountPlusOneFraction; length; --length, ++cursor, ++cursorOther)
		{
			if(*cursor < *cursorOther)return -1;
			if(*cursor > *cursorOther)return 1;
		}
//		return 0;
		return m_wholeNumberCountPlusOneFraction == other.m_wholeNumberCountPlusOneFraction ? 0 : less ? -1 : 1;
	}
*/
	short Compare(const StrAsVarNumberArray& other) const
	{
		return m_length < other.m_length ? -1:
			m_length > other.m_length ? 1:
			CompareArrayOfLength(other.m_numberArray);
/*
		const NumberType* cursor = m_numberArray;
		const NumberType* cursorOther = other.m_numberArray;
		const bool less = m_wholeNumberCountPlusOneFraction < other.m_wholeNumberCountPlusOneFraction;
//		for(unsigned short length = m_wholeNumberCountPlusOneFraction < other.m_wholeNumberCountPlusOneFraction ? m_wholeNumberCountPlusOneFraction : other.m_wholeNumberCountPlusOneFraction; length; --length, ++cursor, ++cursorOther)
		for(unsigned short length = less ? m_wholeNumberCountPlusOneFraction : other.m_wholeNumberCountPlusOneFraction; length; --length, ++cursor, ++cursorOther)
		{
			if(*cursor < *cursorOther)return -1;
			if(*cursor > *cursorOther)return 1;
		}
//		return 0;
		return m_wholeNumberCountPlusOneFraction == other.m_wholeNumberCountPlusOneFraction ? 0 : less ? -1 : 1;
*/
	}
//	bool operator<(const StrAsVarNumberArray& other) const{return CompareArrayOfLength(other.m_numberArray) < 0;}
	bool operator<(const StrAsVarNumberArray& other) const{return Compare(other) < 0;}
	bool operator>(const StrAsVarNumberArray& other) const{return Compare(other) > 0;}
	bool operator<=(const StrAsVarNumberArray& other) const{return Compare(other) <= 0;}
	bool operator>=(const StrAsVarNumberArray& other) const{return Compare(other) >= 0;}
//	operator size_t() const{return (size_t)*m_numberArray + m_length;}
//	operator int() const{return (int)*m_numberArray + m_length;}
//	operator long() const{return (long)*m_numberArray + m_length;}
	size_t GetHashValue() const{return (size_t)*m_numberArray + m_length;}
/*
	void Initialize()
	{
		m_length = m_wholeNumberCount = m_wholeLength = 0;
		if(m_numberArray)
		{
			NumberType* cursor = m_numberArray;
			for(unsigned short i = 0; i < m_arraySize; ++i, ++cursor)
			{
				*cursor = 0;
			}
		}
	}
*/
	short CompareAsStrings(const StrAsVarNumberArray& other) const//, unsigned short length) const
	{
		const NumberType* cursor = m_numberArray;
		const NumberType* cursorOther = other.m_numberArray;
		unsigned short length = other.m_wholeNumberCountPlusOneFraction;
		short defaultRet = 0;
		if(length > m_wholeNumberCountPlusOneFraction)
		{
			length = m_wholeNumberCountPlusOneFraction;
			defaultRet = -1;
		}
		else if(length < m_wholeNumberCountPlusOneFraction)
		{
			defaultRet = 1;
		}
		for(; length; --length, ++cursor, ++cursorOther)
		{
			if(*cursor != *cursorOther)
			{
				return U_CompareUIntAsString(*cursor, *cursorOther);
			}
		}
		return defaultRet;
	}
	void Clear()
	{
		DoSetString(0, "");
/*
		m_length = m_wholeNumberCount = m_wholeLength = 0;
		NumberType* cursor = m_numberArray;
		for(unsigned short i = 0; i < m_arraySize; ++i, ++cursor)
		{
			if(*cursor)
			{
				*cursor = 0;
			}
			else
			{
				break;
			}
		}
*/
	}
	const char* GetString() const{return (const char*)m_numberArray;}
protected:
	NumberType* m_numberArray;
	unsigned short m_arraySize;
	unsigned short m_length;
	unsigned short m_wholeNumberCount;
	unsigned short m_wholeNumberCountPlusOneFraction;
//	unsigned short m_wholeLength;
	void DoSetString(const unsigned short& exactLength, const char* cursor)
	{
		const NumberType* numberCursorOther = (const NumberType*)cursor;
//		m_length = exactLength;
		unsigned short wholeLength;
		unsigned short arraySize = 1;
		unsigned short fraction = 0;
		char* fractionDst = nullptr;
		if(exactLength)
		{
			m_wholeNumberCount = m_wholeNumberCountPlusOneFraction = exactLength / sizeof(NumberType);
			arraySize = m_wholeNumberCount + 1;
			wholeLength = m_wholeNumberCount * sizeof(NumberType);
			if(wholeLength != exactLength)
			{
				++m_wholeNumberCountPlusOneFraction;
			}
//			m_wholeLength = m_wholeNumberCount * sizeof(NumberType);
		}
		else
		{
			m_wholeNumberCount = m_wholeNumberCountPlusOneFraction = wholeLength = 0;//m_wholeLength = 0;
			cursor = nullptr;
		}
		if(m_arraySize != arraySize)
		{
			if(m_numberArray)delete[] m_numberArray;
			m_arraySize = arraySize;
			m_numberArray = new NumberType[m_arraySize];
		}

//		if(m_wholeLength == exactLength)
		if(wholeLength == exactLength)
		{
			cursor = nullptr;
		}
		else
		{
			fraction = exactLength - wholeLength;//m_wholeLength;
			cursor += wholeLength;//m_wholeLength;
			fractionDst = (char*)m_numberArray + wholeLength;//m_wholeLength;
		}

		m_length = exactLength;
////
		if(m_arraySize > m_wholeNumberCount)//should be always true
		{
			*(m_numberArray + m_wholeNumberCount) = 0;
		}
		NumberType* numberCursor = m_numberArray;

		for(unsigned short wholeNumberCount = m_wholeNumberCount; wholeNumberCount; --wholeNumberCount, ++numberCursor, ++numberCursorOther)
		{
			*numberCursor = *numberCursorOther;
		}
		if(cursor)
		{
			for(; fraction; --fraction, ++cursor, ++fractionDst)
			{
				*fractionDst = *cursor;
			}
		}
	}
	void DoSetString(const char* cursor)
	{
		if(cursor)
		{
			DoSetString((unsigned short)strlen(cursor), cursor);
		}
		else
		{
			DoSetString(0, "");
		}
	}
	void DoSetStringWithDelimiter(const char*& cursor, const char& del)
	{
		if(cursor)
		{
			unsigned short len;
			if(del)
			{
				len = 0;
				char c = *cursor;
				for(const char* cur = cursor; c && c != del; c = *++cur, ++len);
			}
			else
			{
				len = (unsigned short)strlen(cursor);
			}
			DoSetString(len, cursor);
			cursor += len;
			if(del && del == *cursor)++cursor;
		}
		else
		{
			DoSetString(0, "");
		}
	}
	void DoSetString(const char* cursor, const unsigned short& length)//length is how many chars max you want to get from cursor
	{
		if(cursor)
		{
			unsigned short len = (unsigned short)strlen(cursor);
			if(len > length)len = length;

			DoSetString(len, cursor);
		}
		else
		{
			DoSetString(0, "");
		}
	}
	void DoSetStringWithDelimiter(const char*& cursor, const unsigned short& length, const char& del)//length is how many chars max you want to get from cursor
	{
		if(cursor)
		{
			unsigned short len;
			if(del)
			{
				len = 0;
				char c = *cursor;
				for(const char* cur = cursor; c && c != del; c = *++cur, ++len);
			}
			else
			{
				len = (unsigned short)strlen(cursor);
			}
			unsigned short lenToDelimiter = len;
			if(len > length)len = length;

			DoSetString(len, cursor);

			cursor += lenToDelimiter;
			if(del && del == *cursor)++cursor;
		}
		else
		{
			DoSetString(0, "");
		}
	}
/*
	void ClearTail()
	{
		if(m_length > m_wholeLength)
		{
			char* cursor = (char*)m_numberArray + m_length;
			for(unsigned short fractionLength = m_wholeLength + sizeof(NumberType) - m_length; fractionLength; --fractionLength, ++cursor)
			{
				*cursor = '\0';
			}
		}
		else if(m_wholeNumberCount < m_arraySize)
		{
			*(m_numberArray + m_wholeNumberCount) = 0;
		}
	}
*/
/*
	void ClearNormalizedTail()
	{
		if(m_length > m_wholeLength)
		{
				char* cursor = (char*)m_numberArray + m_length;
				for(unsigned short fractionLength = m_wholeLength + sizeof(NumberType) - m_length; fractionLength; --fractionLength, ++cursor)
				{
					*cursor = '\0';
				}
			if(wholeNumberCount < N)
			{
				for(NumberType* numberCursor = m_numberArray + wholeNumberCount; wholeNumberCount < N; ++wholeNumberCount, ++numberCursor)
				{
					if(*numberCursor)
					{
						*numberCursor = 0;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
*/
private:
	void CopyArray(const NumberType* cursorOther)
	{
		NumberType* cursor = m_numberArray;
		for(unsigned short i = 0; i < m_arraySize; ++i, ++cursor, ++cursorOther)
		{
			*cursor = *cursorOther;
		}
	}
/*
	void CopyNormalizedArray(const NumberType* cursorOther)
	{
		NumberType* cursor = m_numberArray;
		unsigned short i = 0;
		for(; i < m_arraySize; ++i, ++cursor, ++cursorOther)
		{
			if(*cursorOther)
			{
				*cursor = *cursorOther;
			}
			else
			{
				break;
			}
		}
		for(; i < m_arraySize; ++i, ++cursor)
		{
			if(*cursor)
			{
				*cursor = 0;
			}
			else
			{
				break;
			}
		}
	}
*/
/*
	bool isArrayOfLengthEqual(const NumberType* cursorOther) const//, unsigned short length) const
	{
		const NumberType* cursor = m_numberArray;
		for(unsigned short length = m_wholeNumberCountPlusOneFraction; length; --length, ++cursor, ++cursorOther)
		{
			if(*cursor != *cursorOther)
			{
				return false;
			}
		}
		return true;
	}
*/
	short CompareArrayOfLength(const NumberType* cursorOther) const//, unsigned short length) const
	{
		const NumberType* cursor = m_numberArray;
		for(unsigned short length = m_wholeNumberCountPlusOneFraction; length; --length, ++cursor, ++cursorOther)
		{
			if(*cursor < *cursorOther)return -1;
			if(*cursor > *cursorOther)return 1;
		}
		return 0;
	}
/*
	short CompareArrayOfLength(const NumberType* cursorOther) const//, unsigned short length) const
	{
		const NumberType* cursor = m_numberArray;
		for(unsigned short length = m_wholeNumberCountPlusOneFraction; length; --length, ++cursor, ++cursorOther)
		{
			if(*cursor < *cursorOther)
			{
				return -1;
			}
			else if(*cursor > *cursorOther)
			{
				return 1;
			}

//			if(!*cursor)
//			{
//				break;
//			}

		}
		return 0;
	}
*/
};

class FilterStringAsNumberArray : public StrAsVarNumberArray<size_t>
{
public:
	FilterStringAsNumberArray():StrAsVarNumberArray(){}
	explicit FilterStringAsNumberArray(const char* const& str):StrAsVarNumberArray(str){}
	FilterStringAsNumberArray(const char*& str, const char& del):StrAsVarNumberArray(str, del){}
	FilterStringAsNumberArray(const char*& str, const unsigned short& length, const char& del):StrAsVarNumberArray(str, length, del){}
	FilterStringAsNumberArray(unsigned short exactLength, const char* str):StrAsVarNumberArray(exactLength, str){}
	explicit FilterStringAsNumberArray(const std::string& str):StrAsVarNumberArray(str){}
//	operator size_t() const{return (size_t)*m_numberArray + m_length;}
	DECLARE_NED_NEW
};

class FilterStringAsNumberArrayAndRank : public FilterStringAsNumberArray
{
public:
	FilterStringAsNumberArrayAndRank(const unsigned int& rank = 0):FilterStringAsNumberArray(), m_rank(rank){}
	explicit FilterStringAsNumberArrayAndRank(const char* const& str, const unsigned int& rank = 0):FilterStringAsNumberArray(str), m_rank(rank){}
	FilterStringAsNumberArrayAndRank(const char*& str, const char& del, const unsigned int& rank = 0):FilterStringAsNumberArray(str, del), m_rank(rank){}
	FilterStringAsNumberArrayAndRank(const char*& str, const unsigned short& length, const char& del, const unsigned int& rank = 0):FilterStringAsNumberArray(str, length, del), m_rank(rank){}
	FilterStringAsNumberArrayAndRank(unsigned short exactLength, const char* str, const unsigned int& rank = 0):FilterStringAsNumberArray(exactLength, str), m_rank(rank){}
	explicit FilterStringAsNumberArrayAndRank(const std::string& str, const unsigned int& rank = 0):FilterStringAsNumberArray(str), m_rank(rank){}
	const unsigned int& GetRank() const{return m_rank;}
	void SetRank(const unsigned int& rank){m_rank = rank;}
	bool operator<(const FilterStringAsNumberArrayAndRank& other) const{return m_rank != other.m_rank ? m_rank > other.m_rank : CompareAsStrings(other) < 0;}
	bool operator==(const FilterStringAsNumberArrayAndRank& other) const{return m_rank == other.m_rank && FilterStringAsNumberArray::operator==(other);}
	bool operator!=(const FilterStringAsNumberArrayAndRank& other) const{return !operator==(other);}
	bool operator>(const FilterStringAsNumberArrayAndRank& other) const{return m_rank != other.m_rank ? m_rank < other.m_rank : CompareAsStrings(other) > 0;}
	bool operator<=(const FilterStringAsNumberArrayAndRank& other) const{return !operator>(other);}
	bool operator>=(const FilterStringAsNumberArrayAndRank& other) const{return !operator<(other);}
	DECLARE_NED_NEW
protected:
	unsigned int m_rank;
};

class AccountId
{
public:
//09/16/2021 m_id is removed Sometimes AccountId just needsto be copied into another place in memory. Then m_id will contain garbage
	explicit AccountId(const char* const& id)
//		m_id((const char*)&m_first)
	{
		SetAccountId(id);
	}
	explicit AccountId(const unsigned __int64& first = 0, const unsigned __int64& second = 0):
		m_first(first),
		m_second(second)
//		m_id((const char*)&m_first)
	{}
/*Sometimes AccountId just needsto be copied into another place in memory. Then m_id will contain garbage
	AccountId(const AccountId& other):
		m_first(other.m_first),
		m_second(other.m_second),
		m_id((const char*)&m_first)
	{
	}
	AccountId& operator=(const AccountId& other)
	{
		m_first = other.m_first;
		m_second = other.m_second;
		return *this;
	}
*/
	void SetAccountId(const unsigned __int64& first, const unsigned __int64& second)
	{
		m_first = first;
		m_second = second;
	}
	void Nullify(){m_first = m_second = 0;}
	void SetAccountId(const char* id)
	{
		m_first = m_second = 0;
		if(*id)
		{
			char* dst = (char*)&m_first;
			unsigned int i = 0;
			for(; *id && i < sizeof(m_first); ++i, ++id, ++dst)
			{
				*dst = *id;
			}
			if(*id)
			{
				i = 0;
				for(; *id && i < sizeof(m_second); ++i, ++id, ++dst)
				{
					*dst = *id;
				}
			}
		}
	}
	void SetAccountId(const char* id, const unsigned int& len)
	{
		m_first = m_second = 0;
		if(len && *id)
		{
			char* dst = (char*)&m_first;
			unsigned int i = 0;
			bool big = len > sizeof(m_first);
			unsigned int end = big ? sizeof(m_first) : len;

			for(; *id && i < end; ++i, ++id, ++dst)
			{
				*dst = *id;
			}
			if(*id && big)
			{
				end = len - sizeof(m_first);
				if(end > sizeof(m_second))end = sizeof(m_second);
				i = 0;
				for(; *id && i < end ; ++i, ++id, ++dst)
				{
					*dst = *id;
				}
			}
		}
	}
	const char* GetId() const{return (const char*)&m_first;}
//	const char* const& GetId() const{return m_id;}
	const unsigned __int64& GetFirst() const{return m_first;}
	const unsigned __int64& GetSecond() const{return m_second;}
//	operator size_t() const{return (size_t)m_first;}
	size_t GetHashValue() const{return (size_t)m_first;}
	bool operator<(const AccountId& other) const{return m_first < other.m_first || m_first == other.m_first && m_second < other.m_second;}
	bool operator>(const AccountId& other) const{return m_first > other.m_first || m_first == other.m_first && m_second > other.m_second;}
	bool operator==(const AccountId& other) const{return m_first == other.m_first && m_second == other.m_second;}
	bool operator!=(const AccountId& other) const{return m_first != other.m_first || m_second != other.m_second;}
	bool operator<=(const AccountId& other) const{return !operator>(other);}
	bool operator>=(const AccountId& other) const{return !operator<(other);}

	char CompareAsStrings(const AccountId& other) const
	{
		const char ret = U_CompareUIntAsString(m_first, other.m_first);
		return ret ? ret : U_CompareUIntAsString(m_second, other.m_second);
	}
	bool isZero() const{return !m_first;}
	bool operator!() const{return !m_first;}
protected:
	unsigned __int64 m_first;
	unsigned __int64 m_second;
//Sometimes AccountId just needsto be copied into another place in memory.Then m_id will contain garbage
//	const char* m_id;
};

template<class T>
class AccountNumberId : public AccountId
{
public:
	typedef T ValueType;
	AccountNumberId(const char* const& numberId, const char* const& clearingAccountName):
		AccountId(clearingAccountName),
		m_numberId(U_RepresentStringAsUnsignedNumber<ValueType>(numberId))
	{}
	AccountNumberId(const ValueType& numberId, const char* const& clearingAccountName):
		AccountId(clearingAccountName),
		m_numberId(numberId)
	{}
	AccountNumberId(const ValueType& numberId = 0, const unsigned __int64& first = 0, const unsigned __int64& second = 0):
		AccountId(first, second),
		m_numberId(numberId)
	{}
	AccountNumberId(const ValueType& numberId, const AccountId& accountId):
		AccountId(accountId),
		m_numberId(numberId)
	{}
	AccountNumberId(const char* const& str):
		m_numberId(0)
	{
		fromString(str);
	}
	const ValueType& GetNumberId() const{return m_numberId;}
	void SetNumberId(const ValueType& numberId){m_numberId = numberId;}
	bool operator<(const AccountNumberId& other) const{return m_numberId < other.m_numberId || m_numberId == other.m_numberId && AccountId::operator<(other);}
	bool operator==(const AccountNumberId& other) const{return m_numberId == other.m_numberId && AccountId::operator==(other);}
	bool operator!=(const AccountNumberId& other) const{return m_numberId != other.m_numberId || AccountId::operator!=(other);}
	void SetAccountNumberId(const ValueType& numberId, const unsigned __int64& first, const unsigned __int64& second)
	{
		m_numberId = numberId;
		SetAccountId(first, second);
	}
	void SetAccountNumberId(const ValueType& numberId, const AccountId& accountId)
	{
		m_numberId = numberId;
		AccountId::operator=(accountId);
	}
	void Nullify(){AccountId::Nullify(); m_numberId = 0;}
	void toString(std::string& str) const
	{
		str += GetId();
		str += ' ';
		U_AppendUnsignedNumberAsString(str, m_numberId);
	}
	void fromString(const char* const& str)
	{
		const char* p = strrchr(str, ' ');
		if(p)
		{
			m_numberId = U_RepresentStringAsUnsignedNumber<ValueType>(p + 1);
			SetAccountId(str, (unsigned int)(p - str));
		}
		else
		{
			m_numberId = 0;
			SetAccountId(str);
		}
	}
	size_t GetHashValue() const{return (size_t)m_first + (size_t)m_numberId;}
protected:
	ValueType m_numberId;
};


template<class C>
struct lessPtr : public std::binary_function<C, C, bool>
{	// functor for operator<
	bool operator()(const C& p1, const C& p2) const
	{	// apply operator< to operands
		return *p1 < *p2;
	}
};

// HELPER CLASS IsPtr
// Classic metaprogramming _If statement
template <class T, class TPTR, bool ISPTR>
class IsPtr
{
public:
	inline static TPTR GetReturnValue(T& t){return &t;}
};

template <class T, class TPTR>
class IsPtr<T, TPTR, true>
{
public:
	inline static TPTR GetReturnValue(T& t){return t;}
};
/////////////////////////////

template <class T, class TPTR, bool ISPTR>
class IsConstPtr
{
public:
	inline static const TPTR GetReturnValue(const T& t){return &t;}
};

template <class T, class TPTR>
class IsConstPtr<T, TPTR, true>
{
public:
	inline static const TPTR GetReturnValue(const T& t){return t;}
};

///
template <class T, bool PTRT>
class GetConstPtr
{
public:
	inline static const T* GetReturnValue(const T& t){return &t;}
};

template <class T>
class GetConstPtr<T, true>
{
public:
	inline static const T GetReturnValue(const T& t){return t;}
};

template <class T, bool PTRT>
class GetPtr
{
public:
	inline static T* GetReturnValue(T& t){return &t;}
};

template <class T>
class GetPtr<T, true>
{
public:
	inline static const T GetReturnValue(T& t){return t;}
};

template <class T, bool PTRT, bool OWN>
class GetPtrToDestroy
{
public:
	inline static T* GetReturnValue(const T& t){return nullptr;}
};

template <class T>
class GetPtrToDestroy<T, true, true>
{
public:
	inline static T GetReturnValue(const T& t){return t;}
};

template <class T>
class GetPtrToDestroy<T, true, false>
{
public:
	inline static T GetReturnValue(const T& t){return nullptr;}
};

template <class T, bool ISPTR, bool OWN>
class GetPtrToCreate
{
public:
	inline static const T& GetReturnValue(const T& t){return t;}
};

template <class T>
class GetPtrToCreate<T, true, true>
{
public:
	inline static T GetReturnValue(const T& t){return t->Clone();}
};

template <class T, bool PTRT, class KEY, bool PTRKEY>//false, false
class CastToKey
{
public:
	inline static KEY GetReturnValue(const T& t){return (KEY)t;}
};

template <class T, bool PTRT>
class CastToKey<T, PTRT, T, PTRT>
{
public:
	inline static const T& GetReturnValue(const T& t){return t;}
};

template <class T, class KEY>
class CastToKey<T, false, KEY, true>
{
public:
	inline static KEY GetReturnValue(const T& t){return (KEY)&t;}
};

template <class T, class KEY>
class CastToKey<T, true, KEY, false>
{
public:
	inline static KEY GetReturnValue(const T& t){return (KEY)*t;}
};

template <class T, class KEY>
class CastToKey<T, true, KEY, true>
{
public:
	inline static KEY GetReturnValue(const T& t){return (KEY)t;}
};

template<class T, bool PTRT = false, class KEY = T, bool PTRKEY = PTRT, bool OWN = true>
class Chain
{
public:
#if _MFC_VER > 0x0A00
	typedef typename std::_If<PTRT, T, const T*>::type value_const_ptr_type;
	typedef typename std::_If<PTRT, T, T*>::type value_ptr_type;
	typedef typename std::_If<PTRKEY, lessPtr<KEY>, std::less<KEY>>::type Compare;
#elif _MFC_VER > 0x900
	typedef typename std::_If<PTRT, T, const T*>::_Type value_const_ptr_type;
	typedef typename std::_If<PTRT, T, T*>::_Type value_ptr_type;
	typedef typename std::_If<PTRKEY, lessPtr<KEY>, std::less<KEY>>::_Type Compare;
#else
	typedef typename std::_If<PTRT, T, const T*>::_Result value_const_ptr_type;
	typedef typename std::_If<PTRT, T, T*>::_Result value_ptr_type;
	typedef typename std::_If<PTRKEY, lessPtr<KEY>, std::less<KEY>>::_Result Compare;
#endif
	typedef std::list<T> List;
	typedef typename List::iterator ListIterator;
	typedef typename List::const_iterator ListConstIterator;
	typedef std::map<KEY, ListIterator, Compare> Map;
	typedef typename Map::iterator MapIterator;
	typedef typename Map::const_iterator MapConstIterator;

	static void DestroyValue(const T& v)
	{
		value_ptr_type vptr = GetPtrToDestroy<T, PTRT, OWN>::GetReturnValue(v);
		if(vptr)
		{
			delete vptr;
		}
	}
/*
	static value_ptr_type MakeValue(const T& v)
	{
		return IsPtrCreate<T, T*, PTRT>::GetReturnValue(v);
	}
*/
	Chain(const unsigned int& cap = 0xFFFFFFFF, const bool& rearrangeable = true, const bool& own = true):
		m_mapEnd(m_map.end()),
		m_mapConstEnd(m_map.cend()),
#ifdef CHECK_CHAIN
		m_threadId(0),
#endif
		m_cap(cap),
		m_currentIt(m_list.end()),
		m_frozen(false),
		m_rearrangeable(rearrangeable),
		m_own(own)
	{
	}

	Chain(const Chain& other):
//		m_list(other.m_list),
		m_mapEnd(m_map.end()),
		m_mapConstEnd(m_map.cend()),
#ifdef CHECK_CHAIN
		m_threadId(other.m_threadId),
#endif
		m_cap(other.m_cap),
		m_currentIt(m_list.end()),
		m_frozen(other.m_frozen),
		m_rearrangeable(other.m_rearrangeable),
		m_own(other.m_own)
	{
		if(other.ChainLock())
		{
			for(ListConstIterator it = other.m_list.cbegin(), itend = other.m_list.cend(); it != itend; ++it)
			{
				m_list.push_back(m_own ? GetPtrToCreate<T, PTRT, OWN>::GetReturnValue(*it) : *it);
			}
			RefreshList();
			SetCurrentValue(other.GetCurrentPtr());
			other.ChainUnlock();
		}
	}

	Chain& operator=(const Chain& other)
	{
		if(ChainLock())
		{
			if(other.ChainLock())
			{
#ifdef CHECK_CHAIN
				m_threadId = other.m_threadId;
#endif
				Clear();

				m_cap = other.m_cap;
				m_currentIt = m_list.end();
				m_frozen = other.m_frozen;
				m_rearrangeable = other.m_rearrangeable;
				m_own = other.m_own;
				for(ListConstIterator it = other.m_list.cbegin(), itend = other.m_list.cend(); it != itend; ++it)
				{
					m_list.push_back(m_own ? GetPtrToCreate<T, PTRT, OWN>::GetReturnValue(*it) : *it);
				}
				RefreshList();
				SetCurrentValue(other.GetCurrentPtr());

				other.ChainUnlock();
			}
			ChainUnlock();
		}
		return *this;
	}

	virtual ~Chain(){Clear();}

	bool isAtEnd() const
	{
		bool ret = true;
		if(ChainLock())
		{
			ret = m_currentIt == m_list.end();
			ChainUnlock();
		}
		return ret;
	}
#ifdef CHECK_CHAIN
	void SetThreadId(unsigned int threadId)
	{
		m_threadId = threadId;
	}
	virtual void Verify() const
	{
		if(ChainLock())
		{
			U_CheckUtilsThread(m_threadId, "Chain");
			assert(m_map.size() == m_list.size());
			MapConstIterator found;
			for(ListConstIterator it = m_list.cbegin(), itend = m_list.cend(); it != itend; ++it)
			{
				found = m_map.find(*it);
				if(found == m_mapConstEnd)
				{
					assert(0);
					break;
				}
				else if(found->second != it)
				{
					assert(0);
					break;
				}
			}
			ChainUnlock();
		}
	}
#endif

	bool operator==(const Chain& other) const
	{
		bool ret = false;
		if(ChainLock())
		{
			if(other.ChainLock())
			{
				ret = m_cap == other.m_cap
					&& m_frozen == other.m_frozen
					&& m_rearrangeable == other.m_rearrangeable
					&& m_own == other.m_own
					&& m_list == other.m_list;
				other.ChainUnlock();
			}
			ChainUnlock();
		}
		return ret;
	}

	bool operator!=(const Chain& other) const
	{
		return !operator==(other);
	}

	bool SameList(const Chain& other) const
	{
		bool ret = false;
		if(ChainLock())
		{
			if(other.ChainLock())
			{
				ret = m_list == other.m_list;
				other.ChainUnlock();
			}
			ChainUnlock();
		}
		return ret;
	}
	bool isListIntersect(const Chain& other) const
	{
		bool ret = false;
		if(ChainLock())
		{
			if(other.ChainLock())
			{
				const Map& map1 = m_map.size() <= other.m_map.size() ? m_map : other.m_map;
				const Map& map2 = m_map.size() > other.m_map.size() ? m_map : other.m_map;
				MapConstIterator foundEnd = map2.cend();
				for(Map::const_iterator it = map1.cbegin(), itend = map1.cend(); it != itend; ++it)
				{
					if(map2.find(it->first) != foundEnd)
					{
						ret = true;
						break;
					}
				}
				other.ChainUnlock();
			}
			ChainUnlock();
		}
		return ret;
	}
//	const T* GetPrevious()
	value_const_ptr_type GetPrevious()
	{
		value_const_ptr_type ret = nullptr;
		if(ChainLock())
		{
			if(!isEmpty())
			{
				ListIterator itend = m_list.end();
				if(m_currentIt == itend)
				{
					m_currentIt = m_list.begin();
				}
				else
				{
					++m_currentIt;
					if(m_currentIt == itend)
					{
						m_currentIt = m_list.begin();
					}
				}
//				ret = &(*m_currentIt);
				ret = GetConstPtr<T, PTRT>::GetReturnValue(*m_currentIt);
			}
			ChainUnlock();
		}
		return ret;
	}
	value_const_ptr_type GetNext()
	{
		value_const_ptr_type ret = nullptr;
		if(ChainLock())
		{
			if(!isEmpty())
			{
				ListIterator itbegin = m_list.begin();
				if(m_currentIt == itbegin)
				{
					m_currentIt = m_list.end();
				}
				--m_currentIt;
//				ret = &(*m_currentIt);
				ret = GetConstPtr<T, PTRT>::GetReturnValue(*m_currentIt);
			}
			ChainUnlock();
		}
		return ret;
	}

	value_const_ptr_type GetCurrent() const
	{
		value_const_ptr_type ret = nullptr;
		if(ChainLock())
		{
			ret = m_currentIt == m_list.end() ? nullptr : GetConstPtr<T, PTRT>::GetReturnValue(*m_currentIt);
			ChainUnlock();
		}
		return ret;
	}

	value_ptr_type GetCurrent()
	{
		value_ptr_type ret = nullptr;
		if(ChainLock())
		{
			ret = m_currentIt == m_list.end() ? nullptr : GetPtr<T, PTRT>::GetReturnValue(*m_currentIt);
			ChainUnlock();
		}
		return ret;
	}

	const T* GetCurrentPtr() const
	{
		const T* ret = nullptr;
		if(ChainLock())
		{
			ret = m_currentIt == m_list.end() ? nullptr : &(*m_currentIt);
			ChainUnlock();
		}
		return ret;
	}

	T* GetCurrentPtr()
	{
		T* ret = nullptr;
		if(ChainLock())
		{
			ret = m_currentIt == m_list.end() ? nullptr : &(*m_currentIt);
			ChainUnlock();
		}
		return ret;
	}

	void Reset()
	{
		if(ChainLock())
		{
			if(m_currentIt != m_list.end())
			{
				if(m_rearrangeable)
				{
					ListIterator itLast;
					Map::iterator found;
					for(ListIterator it = m_list.begin(); it != m_currentIt; it = m_list.begin())
					{
						T& t = *it;
						found = m_map.find(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(t));//(KEY)t);
						m_list.push_back(t);
						m_list.pop_front();
						itLast = m_list.end();
						--itLast;
						found->second = itLast;
					}
				}
				m_currentIt = m_list.end();
			}
			ChainUnlock();
		}
	}

	const unsigned int& GetCap() const{return m_cap;}
	void SetCap(const unsigned int& cap)
	{
		if(ChainLock())
		{
			if(cap != m_cap)
			{
				if(cap)
				{
					unsigned int count = GetCount();
					if(count > cap)
					{
						ListIterator it = m_list.end();
						bool currentInitialized = m_currentIt != it;
						ListIterator itBegin = m_list.begin();
						for(--it; count > cap; --count)
						{
							if(currentInitialized)
							{
								if(m_currentIt == it)
								{
									--m_currentIt;
								}
							}

							T& val = *it;
							m_map.erase(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(val));//(KEY)val);
							if(m_own)DestroyValue(val);

							--it;
							m_list.pop_back();
						}
						if(!currentInitialized)
						{
							m_currentIt = m_list.end();
						}
					}
				}
				else
				{
					Clear();
				}
				m_cap = cap;
			}
			ChainUnlock();
		}
	}
	const bool& isFrozen() const{return m_frozen;}
	void SetFrozen(const bool& frozen){m_frozen = frozen;}

	const bool& isRearrangeable() const{return m_rearrangeable;}
	void SetRearrangeable(const bool& rearrangeable){m_rearrangeable = rearrangeable;}

	const bool& isOwn() const{return m_own;}
	void SetOwn(const bool& own){m_own = own;}

	bool SetCurrentValue(const T* const& t)
	{
		bool ret = false;
		if(ChainLock())
		{
			if(t)
			{
				MapIterator found = m_map.find(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(*t));//(KEY)*t);
				if(found != m_mapEnd)
				{
					m_currentIt = found->second;
					ret = true;
				}
			}
			else
			{
				m_currentIt = m_list.end();
				ret = true;
			}
			ChainUnlock();
		}
		return ret;
	}
	value_const_ptr_type PushFrontChainItem(const T& t)
	{
		value_const_ptr_type ret = nullptr;
		if(ChainLock())
		{
			MapIterator found = m_map.find(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(t));//(KEY)t);
			if(found == m_mapEnd)
			{
				if(isFull())
				{
					++m_cap;
				}
				m_list.push_front(t);
				ListIterator lit = m_list.begin();
				m_map.insert(Map::value_type(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(*lit), lit));
//				ret = true;
			}
			else
			{
//				ret = &*found->second;
				ret = GetConstPtr<T, PTRT>::GetReturnValue(*found->second);
			}
			ChainUnlock();
		}
		return ret;
	}
	value_const_ptr_type PushBackChainItem(const T& t)
	{
		value_const_ptr_type ret = nullptr;
		if(ChainLock())
		{
			MapIterator found = m_map.find(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(t));
			if(found == m_mapEnd)
			{
				if(isFull())
				{
					++m_cap;
				}
				m_list.push_back(t);
				ListIterator lit = m_list.end();
				--lit;
				m_map.insert(Map::value_type(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(*lit), lit));
			}
			else
			{
				ret = GetConstPtr<T, PTRT>::GetReturnValue(*found->second);
			}
			ChainUnlock();
		}
		return ret;
	}
	unsigned char InsertChainItem(const T& t, const bool& after = false)//0 - not added because already there; 1 - added, not full; 2 - added, full, existing item removed and destroyed
	{
//		bool ret = false;
		unsigned char ret = 0;
		if(ChainLock())
		{
			if(m_cap)
			{
				MapIterator found = m_map.find(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(t));
				if(m_frozen)
				{
					if(found != m_mapEnd)
					{
						m_currentIt = found->second;
					}
				}
				else
				{
					if(found == m_mapEnd)
					{
						const bool full = isFull();
						if(full)
						{
							if(isEmpty())
							{
								ChainUnlock();
//								return false;
								return 0;
							}
							ListIterator toErase;
							if(after)
							{
								if(m_currentIt == m_list.end())
								{
									toErase = m_list.begin();
								}
								else
								{
									toErase = m_currentIt;
									++toErase;
									if(toErase == m_list.end())
									{
										toErase = m_list.begin();
									}
								}
							}
							else
							{
								if(m_currentIt == m_list.end())
								{
									toErase = m_currentIt;
									--toErase;
								}
								else
								{
									toErase = m_currentIt;
									if(toErase == m_list.begin())
									{
										toErase = m_list.end();
									}
									--toErase;
								}
							}
							bool isAtEnd = m_currentIt == m_list.end() || m_currentIt == toErase;
					
							T& val = *toErase;
							m_map.erase(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(val));
							if(m_own)DestroyValue(val);

							m_list.erase(toErase);
							if(isAtEnd)
							{
								m_currentIt = m_list.end();
							}
							ret = 2;
						}
						else
						{
//							ret = true;
							ret = 1;
						}
					}
					else//found != m_mapEnd
					{

						if(m_currentIt == found->second)
						{
							ChainUnlock();
//							return false;
							return 0;
						}
						if(m_currentIt == m_list.end())
						{
							ListIterator temp = found->second;
							++temp;
							if(temp == m_currentIt)
							{
								ChainUnlock();
//								return false;
								return 0;
							}
						}
						else if(after)
						{
							ListIterator temp = m_currentIt;
							++temp;
							if(found->second == temp)
							{
								ChainUnlock();
//								return false;
								return 0;
							}
						}
						else
						{
							ListIterator temp = found->second;
							++temp;
							if(temp == m_currentIt)
							{
								ChainUnlock();
//								return false;
								return 0;
							}
						}
						m_list.erase(found->second);
					}
					if(after)
					{
						if(m_currentIt == m_list.end())
						{
							m_currentIt = m_list.insert(m_currentIt, t);
						}
						else
						{
							++m_currentIt;
							m_currentIt = m_list.insert(m_currentIt, t);
						}
					}
					else
					{
						m_currentIt = m_list.insert(m_currentIt, t);
					}
					if(found == m_mapEnd)
					{
						m_map.insert(Map::value_type(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(*m_currentIt), m_currentIt));
					}
					else
					{
						found->second = m_currentIt;
					}
				}
			}
		}
		ChainUnlock();
		return ret;
	}

	unsigned char AddChainItem(const T& t, const bool& atEnd = false)//0 - not added because already there; 1 - added, not full; 2 - added, full, existing item removed and destroyed
	{
		if(ChainLock())
		{
			if(m_cap)
			{
				if(m_frozen)
				{
					MapIterator found = m_map.find(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(t));
					if(found != m_mapEnd)
					{
						m_currentIt = found->second;
					}
				}
				else
				{
					if(m_rearrangeable)
					{
						Reset();
					}
					MapIterator found = m_map.find(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(t));
					if(found == m_mapEnd)
					{
						const bool full = isFull();
						if(full)
						{
							if(isEmpty())
							{
								ChainUnlock();
//								return false;
								return 0;
							}
							if(atEnd)
							{
								T& val = m_list.front();
								m_map.erase(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(val));
								if(m_own)DestroyValue(val);
								m_list.pop_front();
							}
							else
							{
								T& val = m_list.back();
								m_map.erase(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(val));
								if(m_own)DestroyValue(val);
								m_list.pop_back();
							}
						}
						ListIterator lit;
						if(atEnd)
						{
							m_list.push_back(t);
							lit = m_list.end();
							--lit;
						}
						else
						{
							m_list.push_front(t);
							lit = m_list.begin();
						}
						m_map.insert(Map::value_type(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(*lit), lit));

						m_currentIt = m_list.end();

						ChainUnlock();
//						return !full;
						return full ? 2 : 1;
					}
					else//found != m_mapEnd
					{
//						m_list.erase(found->second);
						if(m_rearrangeable)
						{
							if(atEnd)
							{
								m_list.push_back(*found->second);//found->first);
								m_list.erase(found->second);
								found->second = m_list.end();
								--found->second;
							}
							else
							{
								m_list.push_front(*found->second);//found->first);
								m_list.erase(found->second);
								found->second = m_list.begin();
							}
						}
						m_currentIt = m_list.end();
					}
				}
			}
			ChainUnlock();
		}
//		return false;
		return 0;
	}
	ListIterator GetListEnd()
	{
#ifdef CHECK_CHAIN
Verify();
#endif
		return m_list.end();
	}
	ListConstIterator GetListEnd() const
	{
#ifdef CHECK_CHAIN
Verify();
#endif
		return m_list.cend();
	}
	ListIterator Remove(const ListIterator& itToRemove)//return next iterator
	{
		ListIterator ret = itToRemove;
		++ret;
		if(ChainLock())
		{
			MapIterator found = m_map.find(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(*itToRemove));//(KEY)t);
			if(found != m_mapEnd)
			{
				if(m_currentIt == found->second)
				{
					++m_currentIt;
					if(m_currentIt == m_list.end())
					{
						m_currentIt = m_list.begin();
						if(m_currentIt == found->second)
						{
							m_currentIt = m_list.end();
						}
					}
				}
				if(m_own)DestroyValue(*found->second);
				ret = m_list.erase(found->second);
//				DestroyValue(found->first);
				m_map.erase(found);
			}
			ChainUnlock();			
		}
		return ret;
	}
	ListIterator Remove(const KEY& t)
	{
		if(ChainLock())
		{
//			Reset();
			ListIterator ret;
			MapIterator found = m_map.find(t);
			if(found != m_mapEnd)
			{
				if(m_currentIt == found->second)
				{
					++m_currentIt;
					if(m_currentIt == m_list.end())
					{
						m_currentIt = m_list.begin();
						if(m_currentIt == found->second)
						{
							m_currentIt = m_list.end();
						}
					}
				}
				if(m_own)DestroyValue(*found->second);
				ret = m_list.erase(found->second);
//				DestroyValue(found->first);
				m_map.erase(found);
			}
			else
			{
				ret = m_list.end();//false;
			}
			ChainUnlock();			
			return ret;
		}
		return m_list.end();
	}
	void Clear()
	{
		if(ChainLock())
		{
			m_map.clear();
			if(m_own)
			{
				for(ListIterator it = m_list.begin(), itend = m_list.end(); it != itend; ++it)
				{
					DestroyValue(*it);
				}
			}
			m_list.clear();
			m_currentIt = m_list.end();
/*
			m_list.clear();
			m_currentIt = m_list.end();

			for(Map::iterator it = m_map.begin(); it != m_mapEnd; ++it)
			{
				DestroyValue(it->first);
			}
			m_map.clear();
*/
			ChainUnlock();			
		}
	}

	unsigned int GetCount() const{return (unsigned int)m_list.size();}
	bool isEmpty() const{return m_list.empty();}
	bool isFull() const{return GetCount() >= m_cap;}
	const List& GetList() const
	{
#ifdef CHECK_CHAIN
Verify();
#endif
		return m_list;
	}
	List& GetList()
	{
#ifdef CHECK_CHAIN
		Verify();
#endif
		return m_list;
	}
	T* GetBorderItem(const bool& back)
	{
		T* ret = nullptr;
		if(ChainLock())
		{
			if(!isEmpty())
			{
				T& t = back ? *m_list.rbegin() : *m_list.begin();
				ret = &t;
			}
			ChainUnlock();
		}
		return ret;
	}
	value_const_ptr_type PeepBack() const
	{
		value_const_ptr_type ret = nullptr;
		if(ChainLock())
		{
			if(!isEmpty())
			{
//				ret = &(*m_list.rbegin());
				ret = GetConstPtr<T, PTRT>::GetReturnValue(*m_list.rbegin());
			}
			ChainUnlock();
		}
		return ret;
	}
	value_const_ptr_type PeepFront() const
	{
		value_const_ptr_type ret = nullptr;
		if(ChainLock())
		{
			if(!isEmpty())
			{
//				ret = &(*m_list.begin());
				ret = GetConstPtr<T, PTRT>::GetReturnValue(*m_list.begin());
			}
			ChainUnlock();
		}
		return ret;
	}
	value_ptr_type PeepBack()
	{
		value_ptr_type ret = nullptr;
		if(ChainLock())
		{
			if(!isEmpty())
			{
//				ret = &(*m_list.rbegin());
				ret = GetPtr<T, PTRT>::GetReturnValue(*m_list.rbegin());
			}
			ChainUnlock();
		}
		return ret;
	}
	value_ptr_type PeepFront()
	{
		value_ptr_type ret = nullptr;
		if(ChainLock())
		{
			if(!isEmpty())
			{
//				ret = &(*m_list.begin());
				ret = GetPtr<T, PTRT>::GetReturnValue(*m_list.begin());
			}
			ChainUnlock();
		}
		return ret;
	}
	bool PopBack(T& t)
	{
		bool ret = false;
		if(ChainLock())
		{
			if(!isEmpty())
			{
				t = *m_list.rbegin();
				Remove(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(t));
				ret = true;
			}
			ChainUnlock();
		}
		return ret;
	}
	bool PopFront(T& t)
	{
		bool ret = false;
		if(ChainLock())
		{
			if(!isEmpty())
			{
				t = *m_list.begin();
				Remove(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(t));
				ret = true;
			}
			ChainUnlock();
		}
		return ret;
	}

	void PopBack(const bool& destroy)
	{
		if(ChainLock())
		{
			if(!isEmpty())
			{
				T& t = *m_list.rbegin();
				Remove(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(t));
				if(destroy && !m_own)DestroyValue(t);
			}
			ChainUnlock();
		}
	}
	void PopFront(const bool& destroy)
	{
		if(ChainLock())
		{
			if(!isEmpty())
			{
				T& t = *m_list.begin();
				Remove(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(t));
				if(destroy && !m_own)DestroyValue(t);
			}
			ChainUnlock();
		}
	}

	value_const_ptr_type GetItemAt(unsigned int at) const
	{
		value_const_ptr_type ret = nullptr;
		if(ChainLock())
		{
			if(at < GetCount())
			{
				List::const_iterator it = m_list.begin();
				for(; at; ++it, --at);

//				ret = &(*it);
				ret = GetConstPtr<T, PTRT>::GetReturnValue(*it);

			}
			ChainUnlock();
		}
		return ret;
	}

	bool Contains(const KEY& t) const
	{
		bool ret = false;
		if(ChainLock())
		{
			ret = m_map.find(t) != m_mapConstEnd;
			ChainUnlock();
		}
		return ret;
	}
	ListIterator Find(const KEY& t)
	{
		if(ChainLock())
		{
			Map::const_iterator found = m_map.find(t);
			ListIterator ret = found == m_mapEnd ? m_list.end() : found->second;
			ChainUnlock();
			return ret;
		}
		return m_list.end();
	}
	value_ptr_type FindObject(const KEY& t)
	{
		ListIterator found = Find(t);
		return found == m_list.end() ? nullptr : GetPtr<T, PTRT>::GetReturnValue(*found);
	}
	void CopyList(List& list) const
	{
		if(ChainLock())
		{
			for(ListConstIterator it = m_list.cbegin(), itend = m_list.cend(); it != itend; ++it)
			{
				list.push_back(*it);
			}
			ChainUnlock();
		}
	}
	virtual bool ChainLock() const{return true;}
	virtual void ChainUnlock() const
	{
#ifdef CHECK_CHAIN
Verify();
#endif
	}
protected:
	List m_list;
	Map m_map;
	MapIterator m_mapEnd;
	MapConstIterator m_mapConstEnd;
#ifdef CHECK_CHAIN
	unsigned int m_threadId;
#endif
	unsigned int m_cap;
	mutable ListIterator m_currentIt;
	bool m_frozen;
	bool m_rearrangeable;
	bool m_own;

	void RefreshList()
	{
		m_map.clear();
		for(ListIterator it = m_list.begin(), itend = m_list.end(); it != itend; ++it)
		{
			m_map.insert(Map::value_type(CastToKey<T, PTRT, KEY, PTRKEY>::GetReturnValue(*it), it));
		}
	}
//private:
//	Chain(const Chain& other);
//	Chain& operator=(const Chain& other);
};

template<class T, bool PTRT = false, class KEY = T, bool PTRKEY = PTRT>
class ThreadSafeChain : public Chain<T, PTRT, KEY, PTRKEY>
{
public:
	ThreadSafeChain(unsigned int cap = 0xFFFFFFFF, bool rearrangeable = true):Chain(cap, rearrangeable){}
	ThreadSafeChain(const ThreadSafeChain& other):Chain(other){}
	ThreadSafeChain& operator=(const ThreadSafeChain& other)
	{
		Chain::operator=(other);
		return *this;
	}
#ifdef CHECK_CHAIN
	virtual void Verify() const{}
#endif
	virtual bool ChainLock() const
	{
		return m_chainLock.Lock() == TRUE;
	}
	virtual void ChainUnlock() const
	{
		m_chainLock.Unlock();
	}
protected:
	mutable CCriticalSection m_chainLock;
};

template <class T>
class DynamicPtrArray
{
public:
	typedef T ValueType;
	DynamicPtrArray(const unsigned int& capacity = 8, const unsigned int& incrementSize = 8):
		m_incrementSize(incrementSize),
		m_capacity(capacity),
		m_size(0),
		m_array(new ValueType*[capacity + 1])
	{
		ValueType** cursor = m_array;
		for(unsigned int i = 0; i <= m_capacity; ++i, ++cursor)
		{
			*cursor = nullptr;
		}
	}
	~DynamicPtrArray(){delete[] m_array;}
	const unsigned int& GetIncrementSize() const{return m_incrementSize;}
	const unsigned int& GetCapacity() const{return m_capacity;}
	const unsigned int& GetSize() const{return m_size;}
	bool empty() const{return !m_size;}

	void SetIncrementSize(const unsigned int& incrementSize)
	{
		if(incrementSize != m_incrementSize)
		{
			m_incrementSize = incrementSize;
		}
	}
	bool SetCapacity(const unsigned int& capacity)
	{
		if(capacity != m_capacity && capacity >= m_size)
		{
			ValueType** newArray = new ValueType*[capacity + 1];
			ValueType** cursor = m_array;
			ValueType** newCursor = newArray;
			const unsigned int end = m_capacity < capacity ? m_capacity : capacity;
			unsigned int i = 0;
			for(; i <= end; ++i, ++cursor, ++newCursor)
			{
				*newCursor = *cursor;
			}
			for(; i <= capacity; ++i, ++newCursor)
			{
				*newCursor = nullptr;
			}
			delete[] m_array;
			m_array = newArray;
			m_capacity = capacity;
			return true;
		}
		return false;
	}

	bool AddValue(ValueType* value)
	{
		if(value)
		{
			for(ValueType** cursor = m_array; *cursor; ++cursor)
			{
				if(*cursor == value)
				{
					return false;
				}
			}
			if(m_size >= m_capacity)
			{
//				const unsigned int capacity = m_incrementSize ? m_capacity + m_incrementSize : m_capacity << 1;
				if(!SetCapacity(m_incrementSize ? m_capacity + m_incrementSize : m_capacity << 1))
				{
					return false;
				}
			}
			m_array[m_size] = value;
			++m_size;
			return true;
		}
		return false;
	}

	bool RemoveValue(ValueType* value)
	{
		if(m_size)
		{
			for(ValueType** cursor = m_array; *cursor; ++cursor)
			{
				if(*cursor == value)
				{
					ValueType** cursorNext = cursor + 1;
					for(; *cursorNext; ++cursor, ++cursorNext)
					{
						*cursor = *cursorNext;
					}
					*cursor = nullptr;
					--m_size;
					return true;
				}
			}
		}
		return false;
	}
	void Clear()
	{
		if(m_size)
		{
			for(ValueType** cursor = m_array; *cursor; ++cursor)
			{
				*cursor = nullptr;
			}
			m_size = 0;
		}
	}
	ValueType** const& GetArray(){return m_array;}
protected:
	unsigned int m_incrementSize;
	unsigned int m_capacity;
	unsigned int m_size;
	ValueType** m_array;
};

template<class T>
class TakionBitField
{
public:
	typedef T SegmentType;
	static const SegmentType one = 1;
	TakionBitField(const unsigned int& length):
		m_length(0),
		m_segmentCount(0),
//		m_bitSetCount(0),
		m_array(nullptr)
	{
		SetLength(length, true);
	}
	TakionBitField(const TakionBitField& other):
		m_length(other.m_length),
		m_segmentCount(other.m_segmentCount),
		m_array(new SegmentType[m_segmentCount])
	{
		const SegmentType* src = other.m_array;
		SegmentType* dst = m_array;
		for(unsigned int i = 0; i < m_segmentCount; ++i, ++src, ++dst)*dst = *src;
	}
	~TakionBitField(){delete[] m_array;}
	TakionBitField& operator=(const TakionBitField& other)
	{
		if(other.m_segmentCount != m_segmentCount)
		{
			m_segmentCount = other.m_segmentCount;
			m_length = other.m_length;
			delete[] m_array;
			m_array = new SegmentType[m_segmentCount];
		}
		else
		{
			m_length = other.m_length;
		}
		
		const SegmentType* src = other.m_array;
		SegmentType* dst = m_array;
		for(unsigned int i = 0; i < m_segmentCount; ++i, ++src, ++dst)*dst = *src;

		return *this;
	}
	const unsigned int& GetLength() const{return m_length;}
	const unsigned int& GetSegmentCount() const{return m_segmentCount;}

	bool isEmpty() const
	{
		if(m_segmentCount < 2)
		{
			return !*m_array;
		}
		else
		{
			const SegmentType* src = m_array;
			for(unsigned int i = 0; i < m_segmentCount; ++i, ++src)
			{
				if(*src)return false;
			}
			return true;
		}
	}

	bool isBitSet(const unsigned int& ordinal) const
	{
		if(ordinal < m_length)
		{
			if(ordinal < sizeof(SegmentType))
			{
				return (*m_array & (one << ordinal)) != 0;
			}
			else
			{
				unsigned int segmentOrdinal = ordinal / sizeof(SegmentType);
				const SegmentType& segment = m_array[segmentOrdinal];
				unsigned int offset = ordinal - segmentOrdinal * sizeof(SegmentType);
				return (segment & (one << offset)) != 0;
			}
		}
		return false;
	}
	bool SetBit(const unsigned int& ordinal, const bool& yes)
	{
		if(ordinal < m_length)
		{
			SegmentType flag;
			unsigned int segmentOrdinal;
			if(ordinal < sizeof(SegmentType))
			{
				segmentOrdinal = 0;
				flag = one << ordinal;
			}
			else
			{
				segmentOrdinal = ordinal / sizeof(SegmentType);
//				unsigned int offset = ordinal - segmentOrdinal * sizeof(SegmentType);
				flag = one << (ordinal - segmentOrdinal * sizeof(SegmentType));//offset;
			}
			SegmentType& segment = *(m_array + segmentOrdinal);
			if(segment & flag)
			{
				if(!yes)
				{
					segment &= ~flag;
					return true;
				}
			}
			else
			{
				if(yes)
				{
					segment |= flag;
					return true;
				}
			}
		}
		return false;
	}

	void SetLength(unsigned int length, const bool& reset)
	{
		if(!length)length = 1;
		if(length != m_length)
		{
			if(length < sizeof(SegmentType))
			{
				SetSegmentCount(1, reset);
			}
			else
			{
				unsigned int segmentCount = length / sizeof(SegmentType);
				if(segmentCount * sizeof(SegmentType) != length)++segmentCount;
				SetSegmentCount(segmentCount, reset);
			}
			m_length = length;
		}
	}
	void Reset()
	{
//		if(m_bitSetCount)
		DoReset();
	}
protected:
	void DoReset()
	{
//		m_bitSetCount = 0;
		SegmentType* cursor = m_array;
		for(unsigned int i = 0; i < m_segmentCount; ++i, ++cursor)*cursor = 0;
	}
	void SetSegmentCount(unsigned int segmentCount, bool reset)
	{
		if(!segmentCount)segmentCount = 1;
		if(segmentCount != m_segmentCount)
		{
			SegmentType* segmentArray = new SegmentType[segmentCount];
			if(reset)
			{
				if(m_array)delete[] m_array;
				m_array = segmentArray;
			}
			else
			{
				if(m_array)
				{
					unsigned int i = 0;
					const SegmentType* src = m_array;
					SegmentType* dst = segmentArray;
					if(segmentCount < m_segmentCount)
					{
						for(; i < segmentCount; ++i, ++src, ++dst)*dst = *src;
					}
					else
					{
						for(; i < m_segmentCount; ++i, ++src, ++dst)*dst = *src;
						for(; i < segmentCount; ++i, ++dst)*dst = 0;
					}
					delete[] m_array;
					m_array = segmentArray;
				}
				else
				{
					m_array = segmentArray;
					reset = true;
				}
			}
			m_segmentCount = segmentCount;
			if(reset)
			{
				DoReset();
			}
		}
		else if(reset)
		{
			Reset();
		}
	}
	unsigned int m_length;
	unsigned int m_segmentCount;
//	unsigned int m_bitSetCount;
	SegmentType* m_array;
};

class U_API LineBuffer
{
public:
	LineBuffer(unsigned int length = 0, const char* buffer = nullptr):m_length(length),m_buffer(buffer){}
	void Reset(){m_length = 0; m_buffer = nullptr;}
	void SetBuffer(unsigned int length, const char* buffer){m_length = length; m_buffer = buffer;}
	bool isEmpty() const{return !m_length;}
	const char* GetLastChar() const{return m_buffer ? m_buffer + m_length : nullptr;}
	unsigned int IncrementCursor(unsigned int length)
	{
		if(length < m_length)
		{
			m_length -= length;
			m_buffer += length;
			return 0;
		}
		else
		{
			unsigned int remaining = length - m_length;
			Reset();
			return remaining;
		}
	}
	unsigned int m_length;
	const char* m_buffer;
};

class LineBufferVector;

class U_API LineBufferArray
{
public:
	LineBufferArray(unsigned int bufferCount);
	LineBufferArray(const LineBufferArray& other);
	~LineBufferArray();
//	const LineBufferArray& operator=(const LineBufferArray& other);
//	void DoubleBufferCount();
//	void SetBufferCount(unsigned int bufferCount);
//	unsigned int GetBufferCount() const{return m_bufferCount;}
	unsigned int GetBufferCount() const;//{return (unsigned int)m_ringVector.capacity();}
//	LineBuffer* GetBufferArray(){return m_bufferArray;}
//	LineBuffer* GetLineBufferAt(unsigned int at){return at < m_bufferCount ? m_bufferArray + at : nullptr;}
//	LineBuffer* GetLastFilledLineBuffer(){return m_filledBufferCount > 1 ? m_bufferArray + (m_filledBufferCount - 1) : m_bufferArray;}
	LineBuffer& GetLastFilledLineBuffer();

	unsigned int GetTotalSize() const{return m_totalSize;}
//	unsigned int GetFilledBufferCount() const{return m_filledBufferCount;}
	unsigned int GetFilledBufferCount() const;//{return (unsigned int)m_ringVector.size();}
	void IncrementLastFilledLineBufferLength(unsigned int length)
	{
//		LineBuffer* lineBuffer = GetLastFilledLineBuffer();
//		lineBuffer->m_length += length;
		LineBuffer& lineBuffer = GetLastFilledLineBuffer();
		lineBuffer.m_length += length;
		m_totalSize += length;
	}
	void IncrementTotalSize(unsigned int length){m_totalSize += length;}
	void DecrementTotalSize(unsigned int length)
	{
		if(m_totalSize >= length)
		{
			m_totalSize -= length;
		}
		else
		{
			m_totalSize = 0;
		}
	}
	void AddLineBuffer(const char* buffer, unsigned int length);
	void Clear();
/*
	{
		m_ringVector.clear();
		m_totalSize = 0;
	}
*/
	void IncrementCursor(unsigned int length);
/*
	{
		LineBuffer* cursor;
		while(!m_ringVector.empty())
		{
			cursor = &m_ringVector.front();
			m_totalSize -= cursor->m_length;
			length = cursor->IncrementCursor(length);
			if(!length)
			{
				if(cursor->isEmpty())
				{
					m_ringVector.pop_front();
				}
				else
				{
					m_totalSize += cursor->m_length;
				}
				break;
			}
		}
	}
*/
	LineBufferVector* GetRingVector(){return m_ringVector;}
	const LineBufferVector* GetRingVector() const{return m_ringVector;}
protected:
//	unsigned int m_bufferCount;
	unsigned int m_totalSize;
//	unsigned int m_filledBufferCount;
//	LineBuffer* m_bufferArray;

//	RingVector<LineBuffer> m_ringVector;
	LineBufferVector* m_ringVector;
};


//template<class L>//unsigned short or unsigned int
//class LineBufferArrayReader
class U_API LineBufferArrayReader
{
public:
	void SetLineBufferArray(const LineBufferArray* bufferArray){m_bufferArray = bufferArray;}
//	virtual bool ProcessDataToken(const char* cursor, L length) const = 0;
	virtual bool ProcessDataToken(const char* cursor, unsigned short length) const = 0;
//	bool ProcessAllData()
	unsigned int ProcessAllData() const;
protected:
	LineBufferArrayReader(const LineBufferArray* bufferArray = nullptr, bool exitOnNoProcess = false):m_bufferArray(bufferArray), m_exitOnNoProcess(exitOnNoProcess){}
	const LineBufferArray* m_bufferArray;
	bool m_exitOnNoProcess;
};

template<class T>
class DividerChoice
{
public:
	DividerChoice():ready(false)
	{
		T value = 1;
		T* cursor = m_choice;
		for(unsigned char i = 0;;)
		{
			*cursor = value;
			++i;
			if(i < size)
			{
				value *= 10;
				++cursor;
			}
			else break;
		}
		ready = true;
	}
	const T& GetDivider(const unsigned char& decDigits) const
	{
		if(ready)return decDigits < size ? m_choice[decDigits] : *m_choice;
		else
		{
			for(; !ready; );
			return decDigits < size ? m_choice[decDigits] : *m_choice;
		}
	}
protected:
	bool ready;
	static const unsigned char size = sizeof(T) == sizeof(unsigned char) ? 3:
		sizeof(T) == sizeof(unsigned short) ? 5:
		sizeof(T) == sizeof(unsigned int) ? 10:
		20;
	T m_choice[size];
};

template<class T>
const T& U_GetDivider(const unsigned char& decDigits)
{
//	static bool ready = false;
	static const DividerChoice<T> dividerChoice;
//	static const DividerChoice<T, sizeof(T) == sizeof(unsigned char) ? 3: sizeof(T) == sizeof(unsigned short) ? 5: 10> dividerChoice;
	return dividerChoice.GetDivider(decDigits);
}


///
/*
template<class Comparable>
class Comparable
{
public:
	virtual ~Comparable(){}
	virtual bool operator<(const Comparable& other) const = 0;
	virtual bool operator==(const Comparable& other) const{return !operator<(other) && !(other < (*this));}
	bool operator!=(const Comparable& other) const{return !operator==(other);}
	bool operator>=(const Comparable& other) const{return !operator<(other);}
	bool operator<=(const Comparable& other) const{return operator<(other) || operator==(other);}
	bool operator>(const Comparable& other) const{return operator<(other) || operator==(other);}
};
*/

template<class F, F N, unsigned char DEC>
struct FPower
{
    enum : F{value = N * FPower<F, N, DEC - 1>::value};
};

template<class F, F N>
struct FPower<F, N, 0>
{
    enum : F{value = 1};
};

template<class F, unsigned char DEC>
struct FPower10 : public FPower<F, 10, DEC>
{
};

template<class D, class F, unsigned char DEC>//, F N>
class Monetary
{
public:
	typedef D DollarType;
	typedef F FractionType;

	typename typedef std::make_unsigned<DollarType>::type UnsignedDollarType;
	typename typedef std::make_unsigned<FractionType>::type UnsignedFractionType;
	typename typedef std::make_signed<DollarType>::type SignedDollarType;
	typename typedef std::make_signed<FractionType>::type SignedFractionType;

	static const unsigned int compactDollarOverflow = 0xFFFF;
	static const unsigned int compactOverflowFlag = 0x40000000;//1 << 30; //1 << 31 is for minus sign
	static const unsigned int compactOverflowDollarMask = 0x3FFFFF80;//0011 1111 1111 1111 1111 1111 1000 0000 = 0x3FFFFF80
	static const unsigned int compactOverflowFractionMask = 0x7F;    //0000 0000 0000 0000 0000 0000 0111 1111 = 0x7F
	static const unsigned int compactDollarMask = 0x3FFFC000;//0011 1111 1111 1111 1100 0000 0000 0000 = 3FFFC000
	static const unsigned int compactFractionMask = 0x3FFF;  //0000 0000 0000 0000 0011 1111 1111 1111 = 0x3FFF
//	static const unsigned int compactPriceMask = 0x3FFFFFFF;  //compactDollarMask | compactFractionMask = 0011 1111 1111 1111 1111 1111 1111 1111 = 0x3FFFFFFF

	static const unsigned char decDigits = DEC;

	static const FractionType divider = FPower10<F, DEC>::value;//10000 for Money; 1000000000 for Price and SignedPrice
	static const UnsignedFractionType unsignedDivider = FPower10<F, DEC>::value;
	static const SignedFractionType signedDivider = FPower10<F, DEC>::value;

	static const FractionType oneCentFraction = divider / 100;
	static const UnsignedFractionType unsignedOneCentFraction = unsignedDivider / 100;
	static const SignedFractionType signedOneCentFraction = signedDivider / 100;

	FractionType GetTruncatedFraction(const unsigned char& digits) const
	{
		return digits >= decDigits ?
			m_dollarFraction:
			m_dollarFraction / U_GetDivider<FractionType>(decDigits - digits);
	}
	DollarType GetNumericValue(const unsigned char& digits) const
	{
		if(sizeof(DollarType) >= sizeof(FractionType))
		{
			return digits >= decDigits ?
				(DollarType)(m_dollars * divider + m_dollarFraction):
				(DollarType)(m_dollars * U_GetDivider<FractionType>(digits) + m_dollarFraction / U_GetDivider<FractionType>(decDigits - digits));
		}
		else
		{
			return digits >= decDigits ?
				(DollarType)(divider * m_dollars + m_dollarFraction):
				(DollarType)(U_GetDivider<FractionType>(digits) * m_dollars + m_dollarFraction / U_GetDivider<FractionType>(decDigits - digits));
		}
	}

	void SetValue(const Monetary& other){operator=(other);}
	void SetValue(const DollarType& dollars, const FractionType& dollarFraction){m_dollars = dollars; m_dollarFraction = dollarFraction;}
	bool operator<(const DollarType& value) const
	{
		return m_dollars < value || m_dollars == value && m_dollarFraction < 0;
	}
	bool operator<=(const DollarType& value) const
	{
		return m_dollars < value || m_dollars == value && m_dollarFraction <= 0;
	}
	bool operator==(const DollarType& value) const{return m_dollars == value && !m_dollarFraction;}
	bool operator!=(const DollarType& value) const{return !operator==(value);}
	bool operator>=(const DollarType& value) const{return !operator<(value);}
	bool operator>(const DollarType& value) const{return !operator<=(value);}

	bool operator<(const Monetary& other) const
	{
		return m_dollars < other.m_dollars || m_dollars == other.m_dollars && m_dollarFraction < other.m_dollarFraction;
	}
	bool operator<=(const Monetary& other) const
	{
		return m_dollars < other.m_dollars || m_dollars == other.m_dollars && m_dollarFraction <= other.m_dollarFraction;
	}
	bool operator==(const Monetary& other) const{return m_dollars == other.m_dollars && m_dollarFraction == other.m_dollarFraction;}
	bool operator!=(const Monetary& other) const{return !operator==(other);}
	bool operator>=(const Monetary& other) const{return !operator<(other);}
	bool operator>(const Monetary& other) const{return !operator<=(other);}
	bool operator!() const{return isZero();}
	const DollarType& GetDollars() const{return m_dollars;}
	const FractionType& GetDollarFraction() const{return m_dollarFraction;}
//	const DollarType& GetDollarsRef() const{return m_dollars;}
//	const FractionType& GetDollarFractionRef() const{return m_dollarFraction;}
	bool isPositive() const{return m_dollars > 0 || m_dollarFraction > 0;}
//	bool isNegative() const{return m_dollars < 0 || m_dollarFraction < 0;}
	bool isZero() const{return !m_dollars && !m_dollarFraction;}
	void SetZero(){m_dollars = 0; m_dollarFraction = 0;}
//	operator double() const{return (double)m_dollars + (double)m_dollarFraction / divider;}
	double toDouble() const{return (double)m_dollars + (double)m_dollarFraction / divider;}
	void SetDoubleValue(const double& value)
	{
		m_dollars = (DollarType)value;
		double v = (value - (double)m_dollars) * divider;
		UnsignedFractionType fraction = (UnsignedFractionType)v;
		if(v - (double)fraction >= 0.5)
		{
			++fraction;
			if(fraction >= unsignedDivider)
			{
				++m_dollars;
				fraction -= unsignedDivider;
			}
		}
		m_dollarFraction = fraction;
	}
	void SetValue1814(const unsigned int& compactValue)//18 high bytes for dollars and 14 low bytes for fraction
	{
		m_dollars = compactValue >> 14;
		m_dollarFraction = (compactValue & compactFractionMask) * (divider / 10000);
	}
	void SetCompactValue(const unsigned int& compactValue)
	{
		if(compactValue & compactOverflowFlag)
		{
			m_dollars = (compactValue & compactOverflowDollarMask) >> 7;
			m_dollarFraction = (compactValue & compactOverflowFractionMask) * (divider / 100);
		}
		else
		{
			m_dollars = compactValue >> 14;
			m_dollarFraction = (compactValue & compactFractionMask) * (divider / 10000);
		}
	}
	void SetDollarsAndCents(const UnsignedDollarType& dollars, const UnsignedFractionType& cents)
	{
		m_dollars = dollars;
		m_dollarFraction = cents;
		if(cents >= 100)
		{
			const UnsignedDollarType additionalDollars = (UnsignedDollarType)(cents / 100);
			m_dollars += additionalDollars;
			m_dollarFraction -= (FractionType)(additionalDollars * 100);
		}
		m_dollarFraction *= oneCentFraction;
	}
	void Canonicalize()
	{
		if(m_dollarFraction >= divider)
		{
			if(m_dollarFraction >= divider + divider)
			{
				CanonicalizeBigFraction();
			}
			else
			{
				FractionMinusDollar();
			}
		}
	}
	void AddDollars(const DollarType& dollars){m_dollars += dollars;}
	void SubtractDollars(const DollarType& dollars){m_dollars -= dollars;}
protected:
	explicit Monetary(const DollarType& dollars = 0, const FractionType& dollarFraction = 0):
		m_dollars(dollars),
		m_dollarFraction(dollarFraction)
	{
	}
	void CanonicalizeBigFraction()
	{
		const DollarType additionalDollars = (DollarType)(m_dollarFraction / divider);
		m_dollars += additionalDollars;
		if(sizeof(DollarType) >= sizeof(FractionType))
		{
			m_dollarFraction -= (FractionType)(additionalDollars * divider);
		}
		else
		{
			m_dollarFraction -= (FractionType)(divider * additionalDollars);
		}
	}
	void HalfPositive()
	{
		if(m_dollars & 1)m_dollarFraction += divider;
		m_dollars >>= 1;
		m_dollarFraction >>= 1;
	}
	void FractionPlusDollar()
	{
		--m_dollars;
		m_dollarFraction += divider;
	}
	void FractionMinusDollar()
	{
		++m_dollars;
		m_dollarFraction -= divider;
	}
	DollarType m_dollars;
	FractionType m_dollarFraction;
};

template<class D, class F, unsigned char DEC>
class SignedMonetary : public Monetary<D, F, DEC>
{
public:
	void Negate(){m_dollars = -m_dollars; m_dollarFraction = -m_dollarFraction;}
	bool isNegative() const{return m_dollars < 0 || m_dollarFraction < 0;}
	void SetAbs(){if(isNegative())Negate();}
	bool Round(const UnsignedFractionType& to, const char& direction)//to = 100 means "Round to cents"; direction -1 - down; +1 - up; 0 - arithmetic
	{
		if(to <= unsignedDivider / 10)
		{
			const bool negativePrice = isNegative();
			const UnsignedFractionType fraction = negativePrice ? -m_dollarFraction : m_dollarFraction;
			if(to)
			{
				const UnsignedFractionType d = unsignedDivider / to;
				UnsignedFractionType f4 = fraction / d;
				const UnsignedFractionType f5 = fraction - f4 * d;

				if(f5)
				{
//					if(negativePrice && direction)direction = -direction;
					switch(direction)
					{
						case 1:
						if(!negativePrice)++f4;
						break;

						case -1:
						if(negativePrice)--f4;
						break;

						case 0:
						if(f5 >= d >> 1)//++f4;
						{
							if(negativePrice)--f4;
							else ++f4;
						}
						break;
					}
					f4 *= d;
					if(f4 >= unsignedDivider)
					{
						f4 -= unsignedDivider;
						if(negativePrice)--m_dollars;
						else ++m_dollars;
					}
					if(negativePrice)m_dollarFraction = -(SignedFractionType)f4;
					else m_dollarFraction = f4;

					return true;
				}
			}
			else if(fraction)
			{
//				if(negativePrice && direction)direction = -direction;
				switch(direction)
				{
					case 1:
					if(!negativePrice)++m_dollars;
					break;

					case -1:
					if(negativePrice)--m_dollars;
					break;

					case 0:
					if(fraction >= unsignedDivider >> 1)
					{
						if(negativePrice)--m_dollars;
						else ++m_dollars;
					}
					break;
				}
				m_dollarFraction = 0;
				return true;
			}
		}
		return false;
	}
	void Half()
	{
		if(isNegative())
		{
			Negate();
			HalfPositive();
			Negate();
		}
		else
		{
			HalfPositive();
		}
	}
	void Canonicalize()
	{
		if(m_dollarFraction > 0)
		{
			Monetary::Canonicalize();

			if(m_dollars < 0)FractionMinusDollar();
		}
		else if(m_dollarFraction < 0)
		{
			if(m_dollarFraction <= -divider - divider)CanonicalizeBigFraction();
			else if(m_dollarFraction <= -divider)FractionPlusDollar();

			if(m_dollars > 0)FractionPlusDollar();
		}
/*
		const int additionalDollars = m_dollarFraction / divider;
		if(additionalDollars)
		{
			m_dollars += additionalDollars;
			m_dollarFraction -= divider * additionalDollars;
		}
		if(m_dollars > 0)
		{
			if(m_dollarFraction < 0)
			{
				--m_dollars;
				m_dollarFraction = divider + m_dollarFraction;
			}
		}
		else if(m_dollars < 0)
		{
			if(m_dollarFraction > 0)
			{
				++m_dollars;
				m_dollarFraction = m_dollarFraction - divider;
			}
		}
*/
	}

	void AddDollars(const DollarType& dollars)
	{
		m_dollars += dollars;
		ReconcileSign();
	}
	void SubtractDollars(const DollarType& dollars)
	{
		m_dollars -= dollars;
		ReconcileSign();
	}
	void SetDoubleValue(const double& value)
	{
		if(value < 0)
		{
			Monetary::SetDoubleValue(-value);
			Negate();
		}
		else Monetary::SetDoubleValue(value);
	}
	void SetDollarsAndCents(const DollarType& dollars, const FractionType& cents)
	{
		m_dollars = dollars;
		if(cents)
		{
			bool centsNegative = cents < 0;
			UnsignedFractionType unsignedCents = centsNegative ? -cents : cents;
			if(unsignedCents >= 100)
			{
				const UnsignedDollarType additionalDollars = (UnsignedDollarType)(unsignedCents / 100);
				if(centsNegative)m_dollars -= additionalDollars;
				else m_dollars += additionalDollars;

				unsignedCents -= (UnsignedFractionType)additionalDollars * 100;
			}
			m_dollarFraction = unsignedCents * unsignedOneCentFraction;
			if(centsNegative)
			{
				m_dollarFraction = -m_dollarFraction;
				if(m_dollars > 0)FractionPlusDollar();
			}
			else if(m_dollars < 0)FractionMinusDollar();
		}
		else
		{
			m_dollarFraction = 0;
		}
	}
	void toPositiveFraction()
	{
		if(m_dollarFraction < 0)FractionPlusDollar();
	}
protected:
	explicit SignedMonetary(const DollarType& dollars = 0, const FractionType& dollarFraction = 0):Monetary(dollars, dollarFraction){}
	explicit SignedMonetary(const double& value){SetDoubleValue(value);}
	void ReconcileSign()
	{
		if(m_dollarFraction > 0)
		{
			if(m_dollars < 0)FractionMinusDollar();
		}
		else if(m_dollarFraction < 0)
		{
			if(m_dollars > 0)FractionPlusDollar();
		}
	}
};

template<class D, class F, unsigned char DEC>
class UnsignedMonetary : public Monetary<D, F, DEC>
{
public:
	void Negate(){}
	bool isNegative() const{return false;}
//	bool Round(const UnsignedMonetary& to, const char& direction)//direction -1 - down; +1 - up; 0 - arithmetic
//	{
//	}
	bool Round(const UnsignedFractionType& to, const char& direction)//to = 100 means "Round to cents"; direction -1 - down; +1 - up; 0 - arithmetic
	{
		if(to <= unsignedDivider / 10)
		{
			if(to)
			{
				const UnsignedFractionType d = unsignedDivider / to;
				UnsignedFractionType f4 = m_dollarFraction / d;
				const UnsignedFractionType f5 = m_dollarFraction - f4 * d;

				if(f5)
				{
					switch(direction)
					{
						case 1:
						++f4;
						break;

						case 0:
						if(f5 >= d >> 1)++f4;
						break;
					}
					f4 *= d;
					if(f4 >= unsignedDivider)
					{
						f4 -= unsignedDivider;
						++m_dollars;
					}
					m_dollarFraction = f4;
					return true;
				}
			}
			else if(m_dollarFraction)
			{
				switch(direction)
				{
					case 1:
					++m_dollars;
					break;

					case 0:
					if(m_dollarFraction >= unsignedDivider >> 1)++m_dollars;
					break;
				}
				m_dollarFraction = 0;
				return true;
			}
		}
		return false;
	}

	void Half()
	{
		HalfPositive();
	}

	unsigned __int64 GetPriceAsUInt64() const{return (unsigned __int64)m_dollars << 32 | m_dollarFraction;}
	void SetPriceAsUInt64(const unsigned __int64& price){m_dollars = price >> 32; m_dollarFraction = price & 0xFFFFFFFF;}
protected:
	explicit UnsignedMonetary(const DollarType& dollars = 0, const FractionType& dollarFraction = 0):Monetary(dollars, dollarFraction){}
	explicit UnsignedMonetary(const double& value){SetDoubleValue(value);}
};

class Price;
class SignedPrice;
class PricePrecise;
class SignedPricePrecise;

//http://www.zeuscmd.com/tutorials/cplusplus/53-OperatorOverloading.php
class U_API Money : public SignedMonetary<__int64, short, 4>//, 10000>
{
public:
	Money():SignedMonetary(0, 0){}
	Money(const __int64& dollars, const short& dollarFraction):SignedMonetary(dollars, dollarFraction){}// To set $10.72 do: Money(10, 72 * oneCentFraction);
	explicit Money(const double& value):SignedMonetary(value){}
	explicit Money(const Price& price);
	explicit Money(const SignedPrice& price);
	explicit Money(const SignedPricePrecise& price);
	explicit Money(const PricePrecise& price);
	explicit Money(const unsigned int& compactPrice)//:SignedMonetary(compactPrice >> 14, compactPrice & 0x3FFF)
	{
		SetCompactValue(compactPrice);
	}
//	explicit
	Money(const int& compactPrice)//:SignedMonetary(compactPrice < 0 ? -((-compactPrice) >> 14) : compactPrice >> 14, compactPrice < 0 ? -((-compactPrice) & 0x3FFF) : compactPrice & 0x3FFF){}
	{
		if(compactPrice < 0)
		{
			SetCompactValue(-compactPrice);
			Negate();
		}
		else
		{
			SetCompactValue(compactPrice);
		}
	}
	operator Price() const;
	operator SignedPrice() const;

	static const Money oneDollar;//(1, 0);
	static const Money oneCent;//(0, oneCentFraction);
	static const Money moneyZero;//(0, 0);

	bool RoundToValue(const Money& to, const char& direction)//direction -1 - down; +1 - up; 0 - arithmetic
	{
		if(to.isPositive())
		{
			const unsigned __int64 moneyTo = to.GetDollars() * divider + to.GetDollarFraction();

			const bool negative = isNegative();
			unsigned __int64 money = negative ? -m_dollars * divider - m_dollarFraction : m_dollars * divider + m_dollarFraction;
			const unsigned __int64 remainder = money % moneyTo;
			if(remainder)
			{
				money -= remainder;
				switch(direction)
				{
					case -1:
					if(negative)money += moneyTo;
					break;

					case 1:
					if(!negative)money += moneyTo;
					break;

					default:
					if(remainder >= divider >> 1)
					{
						money += moneyTo;
					}
					break;
				}
				m_dollars = (DollarType)(money / divider);
				m_dollarFraction = (FractionType)(money - (unsigned __int64)m_dollars * divider);
				if(negative)
				{
					m_dollars = -m_dollars;
					m_dollarFraction = -m_dollarFraction;
				}
				return true;
			}
		}
		return false;
	}
	static bool RoundRangeToValue(Money& low, Money& high, const Money& to, const bool& increaseHighByOneIncrement = false)
	{
		bool ret = false;
		if(to.isPositive())
		{
			const unsigned __int64 moneyTo = (unsigned __int64)to.GetDollars() * divider + to.GetDollarFraction();

			bool negative = low.isNegative();
			unsigned __int64 money = negative ? -low.m_dollars * divider - low.m_dollarFraction : low.m_dollars * divider + low.m_dollarFraction;
			unsigned __int64 remainder = money % moneyTo;
			if(remainder)
			{
				money -= remainder;
				if(negative)money += moneyTo;
				low.m_dollars = (DollarType)(money / divider);
				low.m_dollarFraction = (FractionType)(money - (unsigned __int64)low.m_dollars * divider);
				ret = true;
			}

			negative = high.isNegative();
			money = negative ? -high.m_dollars * divider - high.m_dollarFraction : high.m_dollars * divider + high.m_dollarFraction;
			remainder = money % moneyTo;
			if(remainder)
			{
				money -= remainder;
				if(!negative)money += moneyTo;
				high.m_dollars = (DollarType)(money / divider);
				high.m_dollarFraction = (FractionType)(money - (unsigned __int64)high.m_dollars * divider);
				ret = true;
			}
			if(increaseHighByOneIncrement)
			{
				high += to;
				ret = true;
			}
		}
		return ret;
	}
	void SetValue1814(const unsigned int& compactValue)//18 high bytes for dollars and 14 low bytes for fraction
	{
		m_dollars = compactValue >> 14;
		m_dollarFraction = compactValue & compactFractionMask;
	}
	void SetCompactValue(const unsigned int& compactPrice)
	{
		if(compactPrice & compactOverflowFlag)
		{
			m_dollars = (compactPrice & compactOverflowDollarMask) >> 7;
			m_dollarFraction = (compactPrice & compactOverflowFractionMask) * (divider / 100);
		}
		else
		{
			m_dollars = compactPrice >> 14;
			m_dollarFraction = compactPrice & compactFractionMask;
		}
	}
//	bool Round(unsigned int to, short direction);
	const Money& GetMoneyValue() const{return *this;}
	Money GetPercentChange(const Money& change) const;
	Money operator-() const
	{
		return Money(-m_dollars, -m_dollarFraction);
	}
	Money& operator+=(const Money& other)
	{
		m_dollars += other.m_dollars;
		m_dollarFraction += other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	Money& operator-=(const Money& other)
	{
		m_dollars -= other.m_dollars;
		m_dollarFraction -= other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	Money& operator*=(__int64 quantity)
	{
		m_dollars *= quantity;
		quantity *= m_dollarFraction;
		__int64 additionalDollars = quantity / divider;
		if(additionalDollars)
		{
			m_dollars += additionalDollars;
			m_dollarFraction = (short)(quantity - divider * additionalDollars);
		}
		else
		{
			m_dollarFraction = (short)quantity;
		}
		return *this;
	}
	Money& operator/=(__int64 quantity);

	bool DivideByMoney(const Money& denominator)
	{
		if(isZero())
		{
			return true;
		}
		else if(denominator.isZero())
		{
			SetZero();
			return false;
		}
		else
		{
			SetValue(m_dollars * 10000 + m_dollarFraction, 0);
			operator/=(denominator.GetDollars() * 10000 + denominator.GetDollarFraction());
			return true;
		}
	}
	bool DivideByMoneyPercent(const Money& denominator)
	{
		if(isZero())
		{
			return true;
		}
		else if(denominator.isZero())
		{
			SetZero();
			return false;
		}
		else
		{
			SetValue((m_dollars * 10000 + m_dollarFraction) * 100, 0);
			operator/=(denominator.GetDollars() * 10000 + denominator.GetDollarFraction());
			return true;
		}
	}
	void DividePositiveByDivider()
	{
		const bool toAdd = m_dollarFraction >= (divider >> 1);
		DollarType dollars = m_dollars;
		DollarType whole = dollars / divider;
		FractionType fraction = (FractionType)(dollars - whole * divider);
		if(toAdd)
		{
			++fraction;
			if(fraction >= divider)
			{
				fraction -= divider;
				++whole;
			}
		}
		SetValue(whole, fraction);
	}
	void DivideByDivider()
	{
		const bool negative = isNegative();
		if(negative)
		{
			Negate();
			DividePositiveByDivider();
			Negate();
		}
		else
		{
			DividePositiveByDivider();
		}
	}

//this are done for Constraint template to compile
	Money& operator&=(const Money& other)
	{
		m_dollars &= other.m_dollars;
		m_dollarFraction &= other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	Money& operator|=(const Money& other)
	{
		m_dollars |= other.m_dollars;
		m_dollarFraction |= other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	Money operator&(const Money& other) const{return Money(*this) &= other;}
	Money operator|(const Money& other) const{return Money(*this) |= other;}
///
	Money operator+(const Money& other) const{return Money(*this) += other;}
	Money operator-(const Money& other) const{return Money(*this) -= other;}
	Money operator+(const SignedPrice& other) const{return Money(other) += *this;}
	Money operator-(const SignedPrice& other) const{return Money(*this) -= Money(other);}
	Money operator+(const Price& other) const{return Money(other) += *this;}
	Money operator-(const Price& other) const{return Money(*this) -= Money(other);}
	Money operator*(__int64 quantity) const{return Money(*this) *= quantity;}
	Money operator/(__int64 quantity) const{return Money(*this) /= quantity;}
	int operator/(const Money& other) const;
	int operator/(const Price& other) const;
//	void Canonicalize();
	size_t GetHashValue() const{return (size_t)(m_dollars << 16) | m_dollarFraction;}
};

class U_API SignedPrice : public SignedMonetary<int, int, 9>//, 1000000000
{
public:
	SignedPrice():SignedMonetary(0, 0){}
	SignedPrice(const int& dollars, const int& dollarFraction):SignedMonetary(dollars, dollarFraction){}// To set $10.72 do: SignedPrice(10, 72 * oneCentFraction);
	explicit SignedPrice(const double& value):SignedMonetary(value){}
	explicit SignedPrice(const Price& price);
	explicit SignedPrice(const Money& money);
	explicit SignedPrice(const unsigned int& compactPrice)//:SignedMonetary(compactPrice >> 14, (compactPrice & 0x3FFF) * (divider / 10000)){}
	{
		SetCompactValue(compactPrice);
	}
//	explicit
	SignedPrice(const int& compactPrice)//:SignedMonetary(compactPrice < 0 ? -((-compactPrice) >> 14) : compactPrice >> 14, (compactPrice < 0 ? -((-compactPrice) & 0x3FFF) : compactPrice & 0x3FFF) * (divider / 10000)){}
	{
		SetCompactPrice(compactPrice);
	}

	static const SignedPrice oneDollar;//(1, 0);
	static const SignedPrice oneCent;//(0, oneCentFraction);
	static const SignedPrice signedPriceZero;//(0, 0);

	bool RoundToValue(const Price& to, const char& direction);//direction -1 - down; +1 - up; 0 - arithmetic
	static bool RoundRangeToValue(SignedPrice& low, SignedPrice& high, const Price& to, const bool increaseHighByOneIncrement = false);

	operator Price() const;
	operator Money() const{return Money(*this);}
	const SignedPrice& GetSignedPriceValue() const{return *this;}
	SignedPrice GetPercentChange(const SignedPrice& change) const;
	void SetCompactPrice(const int& compactPrice)
	{
		if(compactPrice < 0)
		{
			SetCompactValue(-compactPrice);
			Negate();
		}
		else
		{
			SetCompactValue(compactPrice);
		}
	}
	static unsigned int CalculatUIntCompactPrice(const unsigned int& uintDollar, const unsigned int& uintFraction)
	{
		return uintDollar > compactDollarOverflow ?
			(uintDollar << 7) | (uintFraction / (divider / 100)) | compactOverflowFlag:
			(uintDollar << 14) | (uintFraction / (divider / 10000));
	}
	static int CalculatIntCompactPrice(const int& intDollar, const int& intFraction)
	{
		return intDollar < 0 || intFraction < 0 ?
			-(int)CalculatUIntCompactPrice(-intDollar, -intFraction):
			CalculatUIntCompactPrice(intDollar, intFraction);
	}
	unsigned int GetUIntCompactPrice() const
	{
		return CalculatUIntCompactPrice(m_dollars, m_dollarFraction);
//		if(m_dollars > 0)
//		{
/*
			const unsigned int uintDollar = m_dollars;
			return uintDollar > compactDollarOverflow ?
				(uintDollar << 7) | ((unsigned int)m_dollarFraction / (divider / 100)) | compactOverflowFlag:
				(uintDollar << 14) | ((unsigned int)m_dollarFraction / (divider / 10000));
*/
/*
			if(uintDollar > compactDollarOverflow)
			{
				return compactOverflowFlag | (uintDollar << 7) | ((unsigned int)m_dollarFraction / (divider / 100));
			}
			else
			{
				return (uintDollar << 14) | ((unsigned int)m_dollarFraction / (divider / 10000));
			}
*/
//		}
//		return 0;
	}
	int GetIntCompactPrice() const
	{
		return CalculatIntCompactPrice(m_dollars, m_dollarFraction);
/*
		if(isNegative())
		{
//			return -CalculatUIntCompactPrice(-m_dollars, -m_dollarFraction);
			const unsigned int uintDollar = -m_dollars;
			const unsigned int uintFraction = -m_dollarFraction;
			return -(int)(uintDollar > compactDollarOverflow ?
				(uintDollar << 7) | (uintFraction / (divider / 100)) | compactOverflowFlag:
				(uintDollar << 14) | (uintFraction / (divider / 10000)));
		}
		else
		{
			return CalculatUIntCompactPrice(m_dollars, m_dollarFraction);
		}
*/
	}
//	void Negate(){m_dollars = -m_dollars; m_dollarFraction = -m_dollarFraction;}
	SignedPrice operator-() const
	{
		return SignedPrice(-m_dollars, -m_dollarFraction);
	}
//	bool Round(unsigned int to, short direction);
	SignedPrice& operator+=(const SignedPrice& other)
	{
		m_dollars += other.m_dollars;
		m_dollarFraction += other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	SignedPrice& operator-=(const SignedPrice& other)
	{
		m_dollars -= other.m_dollars;
		m_dollarFraction -= other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	SignedPrice& operator*=(int quantity)
	{
		m_dollars *= quantity;
		__int64 fraction = (__int64)m_dollarFraction * quantity;
		__int64 additionalDollars = fraction / divider;
		if(additionalDollars)
		{
			m_dollars += (int)additionalDollars;
			m_dollarFraction = (int)(fraction - additionalDollars * divider);
		}
		else
		{
			m_dollarFraction = (int)fraction;
		}
		return *this;
	}
	SignedPrice& operator/=(int quantity);
//this are done for Constraint template to compile
	SignedPrice& operator&=(const SignedPrice& other)
	{
		m_dollars &= other.m_dollars;
		m_dollarFraction &= other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	SignedPrice& operator|=(const SignedPrice& other)
	{
		m_dollars |= other.m_dollars;
		m_dollarFraction |= other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	SignedPrice operator&(const SignedPrice& other) const{return SignedPrice(*this) &= other;}
	SignedPrice operator|(const SignedPrice& other) const{return SignedPrice(*this) |= other;}
///
	SignedPrice operator+(const SignedPrice& other) const{return SignedPrice(*this) += other;}
	SignedPrice operator-(const SignedPrice& other) const{return SignedPrice(*this) -= other;}
	SignedPrice operator+(const Price& other) const{return SignedPrice(other) += *this;}
	SignedPrice operator-(const Price& other) const{return SignedPrice(*this) -= SignedPrice(other);}
	SignedPrice operator+(const Money& other) const{return SignedPrice(other) += *this;}
	SignedPrice operator-(const Money& other) const{return SignedPrice(*this) -= SignedPrice(other);}
	bool isSamePrice(const SignedPrice& other) const{return operator==(other);}
	bool isLessPrice(const SignedPrice& other) const{return operator<(other);}
	bool isGreaterPrice(const SignedPrice& other) const{return !operator<=(other);}
	Money operator*(__int64 quantity) const;
	Money operator/(__int64 quantity) const;
	Money operator*(const SignedPrice& multiplier) const;
//	void Canonicalize();
	SignedPrice ConvertToServerFormat() const
	{
//		if(isNegative() && m_dollarFraction)
		if(m_dollarFraction < 0)
		{
			return SignedPrice(m_dollars - 1, divider + m_dollarFraction);
		}
		else
		{
			return *this;
		}
	}
	void ConvertToServerFormatInPlace()
	{
//		if(isNegative() && m_dollarFraction)
		if(m_dollarFraction < 0)
		{
			--m_dollars;
			m_dollarFraction += divider;
		}
	}
	size_t GetHashValue() const{return ((size_t)m_dollars << 16) | (m_dollarFraction >> 16);}
};

class PricePrecise;

class U_API SignedPricePrecise : public SignedMonetary<int, __int64, 18>//, 1000000000000000000
{
public:
	SignedPricePrecise():SignedMonetary(0, 0){}
	SignedPricePrecise(const int& dollars, const __int64& dollarFraction):SignedMonetary(dollars, dollarFraction){}// To set $10.72 do: SignedPricePrecise(10, 72 * oneCentFraction);
	explicit SignedPricePrecise(const double& value):SignedMonetary(value){}
	explicit SignedPricePrecise(const SignedPrice& price);
	explicit SignedPricePrecise(const PricePrecise& price);
	explicit SignedPricePrecise(const Price& price);
	explicit SignedPricePrecise(const Money& money);
	explicit SignedPricePrecise(const unsigned int& compactPrice)//:SignedMonetary(compactPrice >> 14, (compactPrice & 0x3FFF) * (divider / 10000)){}
	{
		SetCompactValue(compactPrice);
	}
//	explicit
	SignedPricePrecise(const int& compactPrice)//:SignedMonetary(compactPrice < 0 ? -((-compactPrice) >> 14) : compactPrice >> 14, (compactPrice < 0 ? -((-compactPrice) & 0x3FFF) : compactPrice & 0x3FFF) * (divider / 10000)){}
	{
		SetCompactPrice(compactPrice);
	}
	static const SignedPricePrecise oneDollar;//(1, 0);
	static const SignedPricePrecise oneCent;//(0, oneCentFraction);
	static const SignedPricePrecise signedPriceZero;//(0, 0);

	bool RoundToValue(const PricePrecise& to, const char& direction);//direction -1 - down; +1 - up; 0 - arithmetic
	static bool RoundRangeToValue(SignedPricePrecise& low, SignedPricePrecise& high, const PricePrecise& to, const bool increaseHighByOneIncrement = false);

	operator Price() const;
	operator PricePrecise() const;
	operator Money() const{return Money(*this);}
	const SignedPricePrecise& GetSignedPriceValue() const{return *this;}
	SignedPrice GetPercentChange(const SignedPricePrecise& change) const;
	void SetCompactPrice(const int& compactPrice)
	{
		if(compactPrice < 0)
		{
			SetCompactValue(-compactPrice);
			Negate();
		}
		else
		{
			SetCompactValue(compactPrice);
		}
	}
	unsigned int GetUIntCompactPrice() const
	{
//		return (m_dollars << 14) | (unsigned int)(m_dollarFraction / (divider / 10000));
		const unsigned int uintDollar = m_dollars;
		const unsigned __int64 uintDollarFraction = m_dollarFraction;
		return uintDollar > compactDollarOverflow ?
			(uintDollar << 7) | (unsigned int)(uintDollarFraction / (divider / 100)) | compactOverflowFlag:
			(uintDollar << 14) | (unsigned int)(uintDollarFraction / (divider / 10000));
/*
		if(uintDollar > compactDollarOverflow)
		{
			return compactOverflowFlag | (uintDollar << 7) | (unsigned int)(uintDollarFraction / (divider / 100));
		}
		else
		{
			return (uintDollar << 14) | (unsigned int)(uintDollarFraction / (divider / 10000));
		}
*/
	}
	int GetIntCompactPrice() const
	{
		if(isNegative())
		{
			const unsigned int uintDollar = -m_dollars;
			const unsigned __int64 uintFraction = -m_dollarFraction;
			return -(int)(uintDollar > compactDollarOverflow ?
				(uintDollar << 7) | (unsigned int)(uintFraction / (divider / 100)) | compactOverflowFlag:
				(uintDollar << 14) | (unsigned int)(uintFraction / (divider / 10000)));
/*
			if(uintDollar > compactDollarOverflow)
			{
				return -(int)(compactOverflowFlag | (uintDollar << 7) | (unsigned int)(uintFraction / (divider / 100)));
			}
			else
			{
				return -(int)((uintDollar << 14) | (unsigned int)(uintFraction / (divider / 10000)));
			}
*/
		}
		else
		{
			return GetUIntCompactPrice();
		}
//		return isNegative() ? -((-m_dollars << 14) | (int)(-m_dollarFraction / (divider / 10000))):
//			(m_dollars << 14) | (unsigned int)(m_dollarFraction / (divider / 10000));
	}
	SignedPricePrecise operator-() const
	{
		return SignedPricePrecise(-m_dollars, -m_dollarFraction);
	}
//	bool Round(unsigned int to, short direction);
	SignedPricePrecise& operator+=(const SignedPricePrecise& other)
	{
		m_dollars += other.m_dollars;
		m_dollarFraction += other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	SignedPricePrecise& operator-=(const SignedPricePrecise& other)
	{
		m_dollars -= other.m_dollars;
		m_dollarFraction -= other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	SignedPricePrecise& operator*=(int quantity);
	SignedPricePrecise& operator/=(int quantity);
//this are done for Constraint template to compile
	SignedPricePrecise& operator&=(const SignedPricePrecise& other)
	{
		m_dollars &= other.m_dollars;
		m_dollarFraction &= other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	SignedPricePrecise& operator|=(const SignedPricePrecise& other)
	{
		m_dollars |= other.m_dollars;
		m_dollarFraction |= other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	SignedPricePrecise operator&(const SignedPricePrecise& other) const{return SignedPricePrecise(*this) &= other;}
	SignedPricePrecise operator|(const SignedPricePrecise& other) const{return SignedPricePrecise(*this) |= other;}
///
	SignedPricePrecise operator+(const SignedPricePrecise& other) const{return SignedPricePrecise(*this) += other;}
	SignedPricePrecise operator-(const SignedPricePrecise& other) const{return SignedPricePrecise(*this) -= other;}
	SignedPricePrecise operator+(const PricePrecise& other) const{return SignedPricePrecise(other) += *this;}
	SignedPricePrecise operator-(const PricePrecise& other) const{return SignedPricePrecise(*this) -= SignedPricePrecise(other);}
	SignedPricePrecise operator+(const Money& other) const{return SignedPricePrecise(other) += *this;}
	SignedPricePrecise operator-(const Money& other) const{return SignedPricePrecise(*this) -= SignedPricePrecise(other);}
	SignedPricePrecise operator+(const SignedPrice& other) const{return SignedPricePrecise(other) += *this;}
	SignedPricePrecise operator-(const SignedPrice& other) const{return SignedPricePrecise(*this) -= SignedPricePrecise(other);}
	SignedPricePrecise operator+(const Price& other) const{return SignedPricePrecise(other) += *this;}
	SignedPricePrecise operator-(const Price& other) const{return SignedPricePrecise(*this) -= SignedPricePrecise(other);}
	bool isSamePrice(const SignedPricePrecise& other) const{return operator==(other);}
	bool isLessPrice(const SignedPricePrecise& other) const{return operator<(other);}
	bool isGreaterPrice(const SignedPricePrecise& other) const{return !operator<=(other);}
	Money operator*(__int64 quantity) const;
	Money operator/(__int64 quantity) const;
	Money operator*(const SignedPrice& multiplier) const;
	Money operator*(const SignedPricePrecise& multiplier) const;
//	void Canonicalize();
/*
	SignedPrice ConvertToServerFormat() const
	{
//		if(isNegative() && m_dollarFraction)
		if(m_dollarFraction < 0)
		{
			return SignedPrice(m_dollars - 1, divider + m_dollarFraction);
		}
		else
		{
			return *this;
		}
	}
*/
	size_t GetHashValue() const{return ((size_t)m_dollars << 16) | ((size_t)m_dollarFraction >> 16);}
};

class U_API Price : public UnsignedMonetary<unsigned int, unsigned int, 9>//, 1000000000>// : public Comparable<Price>
{
public:
	Price():UnsignedMonetary(0, 0){}
	Price(const unsigned int& dollars, const unsigned int& dollarFraction):UnsignedMonetary(dollars, dollarFraction){}// To set $10.72 do: Price(10, 72 * oneCentFraction);
	explicit Price(const double& value):UnsignedMonetary(value){}
	explicit Price(const SignedPrice& other):UnsignedMonetary(other.isNegative() ? 0 : other.GetDollars(), other.isNegative() ? 0 : other.GetDollarFraction()){}
	explicit Price(const SignedPricePrecise& other):UnsignedMonetary(other.isNegative() ? 0 : other.GetDollars(), other.isNegative() ? 0 : (unsigned int)(other.GetDollarFraction() / (SignedPricePrecise::divider / divider))){}
	explicit Price(const Money& money);
	explicit Price(const PricePrecise& price);
	explicit Price(const unsigned __int64& price):UnsignedMonetary((unsigned int)(price >> 32), (unsigned int)(price & 0xFFFFFFFF)){}
//	explicit
	Price(const unsigned int& compactPrice)//:UnsignedMonetary(compactPrice >> 14, (compactPrice & 0x3FFF) * (divider / 10000)){}
	{
		SetCompactValue(compactPrice);
	}

	static const Price oneDollar;//(1, 0);
	static const Price oneCent;//(0, oneCentFraction);
	static const Price priceZero;//(0, 0);

	operator SignedPrice() const{return SignedPrice(*this);}
	operator Money() const{return Money(*this);}

	bool RoundToValue(const Price& to, const char& direction)//direction -1 - down; +1 - up; 0 - arithmetic
	{
		if(!to.isZero())
		{
			const unsigned __int64 priceTo = (unsigned __int64)to.GetDollars() * divider + to.GetDollarFraction();
			unsigned __int64 price = (unsigned __int64)m_dollars * divider + m_dollarFraction;
			const unsigned __int64 remainder = price % priceTo;
			if(remainder)
			{
				price -= remainder;
				switch(direction)
				{
					case -1:
					break;

					case 1:
					price += priceTo;
					break;

					default:
					if(remainder >= divider >> 1)
					{
						price += priceTo;
					}
					break;
				}
				m_dollars = (DollarType)(price / divider);
				m_dollarFraction = (FractionType)(price - (unsigned __int64)m_dollars * divider);
				return true;
			}
		}
		return false;
	}

	static bool RoundRangeToValue(Price& low, Price& high, const Price& to, const bool& increaseHighByOneIncrement = false)
	{
		bool ret = false;
		const unsigned __int64 priceTo = (unsigned __int64)to.GetDollars() * divider + to.GetDollarFraction();
		if(priceTo)
		{
			unsigned __int64 price = (unsigned __int64)low.m_dollars * divider + low.m_dollarFraction;
			unsigned __int64 remainder = price % priceTo;
			if(remainder)
			{
				price -= remainder;
				low.m_dollars = (DollarType)(price / divider);
				low.m_dollarFraction = (FractionType)(price - (unsigned __int64)low.m_dollars * divider);
				ret = true;
			}
			price = (unsigned __int64)high.m_dollars * divider + high.m_dollarFraction;
			remainder = price % priceTo;
			if(remainder)
			{
				price -= remainder;
				price += priceTo;
				high.m_dollars = (DollarType)(price / divider);
				high.m_dollarFraction = (FractionType)(price - (unsigned __int64)high.m_dollars * divider);
				ret = true;
			}
			if(increaseHighByOneIncrement)
			{
				high += to;
				ret = true;
			}
		}
		return ret;
	}

	unsigned __int64 GetPriceAsUInt64() const{return (unsigned __int64)m_dollars << 32 | m_dollarFraction;}
//	operator unsigned __int64() const{return (unsigned __int64)m_dollars << 32 | m_dollarFraction;}

//	bool Round(unsigned int to, short direction);
	inline static void CalculateCompactPriceComponents(const unsigned int& compactPrice, unsigned int& dollars, unsigned short& fraction)
	{
		if(compactPrice & compactOverflowFlag)
		{
			dollars = (compactPrice & compactOverflowDollarMask) >> 7;
			fraction = (unsigned short)((compactPrice & compactOverflowFractionMask) * 100);
		}
		else
		{
			dollars = compactPrice >> 14;
			fraction = (unsigned short)(compactPrice & compactFractionMask);
		}
	}
	inline static unsigned int CalculateCompactPriceFromStrikePrice(const unsigned int& strikePrice)
	{
		unsigned int dollars = strikePrice / 1000;
		unsigned int fraction1000 = strikePrice - 1000 * dollars;
		return dollars > compactDollarOverflow ?
			(dollars << 7) | (fraction1000 / 10) | compactOverflowFlag:
			(dollars << 14) | (fraction1000 * 10);
/*
		if(dollars > compactDollarOverflow)
		{
			return compactOverflowFlag | (dollars << 7) | (fraction1000 / 10);
		}
		else
		{
			return (dollars << 14) | (fraction1000 * 10);
		}
*/
	}
	inline static unsigned int CalculateStrikePriceFromCompactPrice(const unsigned int& compactPrice)
	{
		return compactPrice & compactOverflowFlag ?
			((compactPrice & compactOverflowDollarMask) >> 7) * 1000 + (compactPrice & compactOverflowFractionMask) * 10:
			(compactPrice >> 14) * 1000 + (compactPrice & compactFractionMask) / 10;
/*
		if(compactPrice & compactOverflowFlag)
		{
			return ((compactPrice & compactOverflowDollarMask) >> 7) * 1000 + (compactPrice & compactOverflowFractionMask) * 10;
		}
		else
		{
			return (compactPrice >> 14) * 1000 + (compactPrice & compactFractionMask) / 10;
		}
*/
	}
	inline static void CalculateCompactPriceComponentsWithBigFraction(const unsigned int& compactPrice, unsigned int& dollars, unsigned int& fraction)
	{
		if(compactPrice & compactOverflowFlag)
		{
			dollars = (compactPrice & compactOverflowDollarMask) >> 7;
			fraction = (compactPrice & compactOverflowFractionMask) * (Price::divider / 100);
		}
		else
		{
			dollars = compactPrice >> 14;
			fraction = (compactPrice & compactFractionMask) * (Price::divider / 10000);
		}
	}
	inline static unsigned int CalculateCompactPrice(const unsigned int& dollars, const unsigned int& fraction)
	{
		return dollars > compactDollarOverflow ?
			(dollars << 7) | (fraction / (divider / 100)) | compactOverflowFlag:
			(dollars << 14) | (fraction / (divider / 10000));
/*
//		return (dollars << 14) | (fraction / (divider / 10000));
		if(dollars > compactDollarOverflow)
		{
			return compactOverflowFlag | (dollars << 7) | (fraction / (divider / 100));
		}
		else
		{
			return (dollars << 14) | (fraction / (divider / 10000));
		}
*/
	}
	inline static unsigned int CalculateCompactPriceFromPrice1814(const unsigned int& price1814)
	{
//	static const unsigned int compactDollarMask = 0x3FFFC000;//0011 1111 1111 1111 1100 0000 0000 0000 = 3FFFC000
//	static const unsigned int compactFractionMask = 0x3FFF;  //0000 0000 0000 0000 0011 1111 1111 1111 = 0x3FFF
		return price1814 > (compactDollarMask | compactFractionMask) ?
			((price1814 >> 14) << 7) | ((price1814 & compactFractionMask) / 100) | compactOverflowFlag:
			price1814;
	}
	void SetCompactPrice(const unsigned int& compactPrice)
	{
		SetCompactValue(compactPrice);
	}
	unsigned int GetCompactPrice() const
	{
		return CalculateCompactPrice(m_dollars, m_dollarFraction);
	}
	SignedPrice operator-() const
	{
		return SignedPrice(-(int)m_dollars, -(int)m_dollarFraction);
	}
	Price& operator+=(const Price& other)
	{
		m_dollars += other.m_dollars;
		m_dollarFraction += other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	Price& operator-=(const Price& other)
	{
		if(operator<(other))
		{
			SetZero();
		}
		else
		{
			SubtractLesserPrice(other);
		}
		return *this;
	}
	Price& operator+=(const SignedPrice& other)
	{
		if(other.isNegative())
		{
			return operator-=(Price(-other.GetDollars(), -other.GetDollarFraction()));
		}
		else
		{
			return operator+=(Price(other.GetDollars(), other.GetDollarFraction()));
		}
	}
	Price& operator-=(const SignedPrice& other)
	{
		if(other.isNegative())
		{
			return operator+=(Price(-other.GetDollars(), -other.GetDollarFraction()));
		}
		else
		{
			return operator-=(Price(other.GetDollars(), other.GetDollarFraction()));
		}
	}
	Price& operator*=(const unsigned int& quantity)
	{
		m_dollars *= quantity;
		unsigned __int64 fraction = (unsigned __int64)m_dollarFraction * quantity;
		unsigned __int64 additionalDollars = fraction / divider;
		if(additionalDollars)
		{
			m_dollars += (unsigned int)additionalDollars;
			m_dollarFraction = (unsigned int)(fraction - additionalDollars * divider);
		}
		else
		{
			m_dollarFraction = (unsigned int)fraction;
		}
		return *this;
	}
	Price& operator/=(unsigned int quantity);
//this are done for Constraint template to compile
	Price& operator&=(const Price& other)
	{
		m_dollars &= other.m_dollars;
		m_dollarFraction &= other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	Price& operator|=(const Price& other)
	{
		m_dollars |= other.m_dollars;
		m_dollarFraction |= other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	Price operator&(const Price& other) const{return Price(*this) &= other;}
	Price operator|(const Price& other) const{return Price(*this) |= other;}
///
	const Price& GetPriceValue() const{return *this;}
	SignedPrice GetPercentChange(const SignedPrice& change) const;
	Price GetPercentChange(const Price& change) const;

	void SubtractLesserPrice(const Price& other)
	{
		m_dollars -= other.m_dollars;
		if(m_dollarFraction < other.m_dollarFraction)
		{
			--m_dollars;
			m_dollarFraction = divider - (other.m_dollarFraction - m_dollarFraction);
		}
		else
		{
			m_dollarFraction -= other.m_dollarFraction;
		}
//		Canonicalize();
	}
	Price GetPositivePriceDiffWithoutVerification(const Price& other) const{Price price(*this); price.SubtractLesserPrice(other); return price;}
//	Price GetAbsDiff(const Price& other) const{return other < *this ? Price(*this) -= other : Price(other) -= *this;}
	Price GetAbsDiff(const Price& other) const{return other < *this ? GetPositivePriceDiffWithoutVerification(other) : other.GetPositivePriceDiffWithoutVerification(*this);}
	Price GetPositivePriceDiff(const Price& other) const{return Price(*this) -= other;}

	Price operator+(const Price& other) const{return Price(*this) += other;}
	SignedPrice operator-(const Price& other) const{return SignedPrice(*this) -= SignedPrice(other);}
//	Price operator-(const Price& other) const{return Price(*this) -= other;}
	SignedPrice operator+(const SignedPrice& other) const{return SignedPrice(*this) += other;}
	SignedPrice operator-(const SignedPrice& other) const{return SignedPrice(*this) -= other;}
	SignedPrice operator+(const Money& other) const{return SignedPrice(other) += *this;}
	SignedPrice operator-(const Money& other) const{return SignedPrice(*this) -= SignedPrice(other);}
	bool isSamePrice(const Price& other) const{return operator==(other);}
	bool isLessPrice(const Price& other) const{return operator<(other);}
	bool isGreaterPrice(const Price& other) const{return !operator<=(other);}
//	void SetUInt64Price(const unsigned __int64& price){*(unsigned __int64*)&m_dollars = price;}
	Money operator*(__int64 quantity) const;
	Money operator/(__int64 quantity) const;
	Price operator*(const Price& multiplier) const;
//	Price operator/(const Price& divider) const;
	unsigned int operator/(const Price& price) const;
	SignedPrice operator*(const SignedPrice& multiplier) const;
//	void Canonicalize();
	size_t GetHashValue() const{return ((size_t)m_dollars << 16) | ((size_t)m_dollarFraction >> 16);}
};

class U_API PricePrecise : public UnsignedMonetary<unsigned int, unsigned __int64, 18>//, 1000000000000000000>// : public Comparable<Price>
{
public:
	PricePrecise():UnsignedMonetary(0, 0){}
	PricePrecise(const unsigned int& dollars, const unsigned __int64& dollarFraction):UnsignedMonetary(dollars, dollarFraction){}// To set $10.72 do: Price(10, 72 * oneCentFraction);
	explicit PricePrecise(const double& value):UnsignedMonetary(value){}
	explicit PricePrecise(const SignedPrice& other):UnsignedMonetary(other.isNegative() ? 0 : other.GetDollars(), other.isNegative() ? 0 : other.GetDollarFraction() * (divider / Price::divider)){}
	explicit PricePrecise(const SignedPricePrecise& other):UnsignedMonetary(other.isNegative() ? 0 : other.GetDollars(), other.isNegative() ? 0 : other.GetDollarFraction()){}
	explicit PricePrecise(const Money& money);
	explicit PricePrecise(const Price& other):UnsignedMonetary(other.GetDollars(), other.GetDollarFraction() * (divider / Price::divider)){}
	explicit PricePrecise(const unsigned __int64& price):UnsignedMonetary((unsigned int)(price >> 32), (unsigned __int64)(price & 0xFFFFFFFF) * (divider / Price::divider)){}
//	explicit
	PricePrecise(const unsigned int& compactPrice)//:UnsignedMonetary(compactPrice >> 14, (unsigned __int64)(compactPrice & 0x3FFF) * (divider / 10000)){}
	{
		SetCompactValue(compactPrice);
	}

	static const PricePrecise oneDollar;//(1, 0);
	static const PricePrecise oneCent;//(0, oneCentFraction);
	static const PricePrecise priceZero;//(0, 0);

	bool RoundToValue(const PricePrecise& to, const char& direction);//direction -1 - down; +1 - up; 0 - arithmetic
	static bool RoundRangeToValue(PricePrecise& low, PricePrecise& high, const PricePrecise& to, const bool increaseHighByOneIncrement = false);

//	operator SignedPrice() const{return SignedPrice(*this);}
//	operator Money() const{return Money(*this);}

//	void SetCompactPrice(const unsigned int& compactPrice){UnsignedMonetary::SetCompactValue(compactPrice);}//m_dollars = compactPrice >> 14; m_dollarFraction = (compactPrice & 0x3FFF) * (divider / 10000);}
//	unsigned int GetCompactPrice() const{return (m_dollars << 14) | (m_dollarFraction / (divider / 10000));}

	SignedPricePrecise operator-() const
	{
		return SignedPricePrecise(-(int)m_dollars, -(int)m_dollarFraction);
	}
	PricePrecise& operator+=(const PricePrecise& other)
	{
		m_dollars += other.m_dollars;
		m_dollarFraction += other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	PricePrecise& operator-=(const PricePrecise& other)
	{
		if(operator<(other))
		{
			SetZero();
		}
		else
		{
			SubtractLesserPrice(other);
		}
		return *this;
	}

	PricePrecise& operator+=(const SignedPricePrecise& other)
	{
		if(other.isNegative())return operator-=(PricePrecise(-other.GetDollars(), -other.GetDollarFraction()));
		else return operator+=(PricePrecise(other.GetDollars(), other.GetDollarFraction()));
	}
	PricePrecise& operator-=(const SignedPricePrecise& other)
	{
		if(other.isNegative())return operator+=(PricePrecise(-other.GetDollars(), -other.GetDollarFraction()));
		else return operator-=(PricePrecise(other.GetDollars(), other.GetDollarFraction()));
	}

	PricePrecise& operator+=(const SignedPrice& other)
	{
		if(other.isNegative())return operator-=(PricePrecise(-other));
		else return operator+=(PricePrecise(other));
	}
	PricePrecise& operator-=(const SignedPrice& other)
	{
		if(other.isNegative())return operator+=(PricePrecise(-other));
		else return operator-=(PricePrecise(other));
	}

	PricePrecise& operator+=(const Price& other)
	{
		return operator+=(PricePrecise(other));
	}
	PricePrecise& operator-=(const Price& other)
	{
		return operator-=(PricePrecise(other));
	}

	PricePrecise& operator*=(unsigned int quantity);
	PricePrecise& operator/=(unsigned int quantity);
//this are done for Constraint template to compile
	PricePrecise& operator&=(const PricePrecise& other)
	{
		m_dollars &= other.m_dollars;
		m_dollarFraction &= other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	PricePrecise& operator|=(const PricePrecise& other)
	{
		m_dollars |= other.m_dollars;
		m_dollarFraction |= other.m_dollarFraction;
		Canonicalize();
		return *this;
	}
	PricePrecise operator&(const PricePrecise& other) const{return PricePrecise(*this) &= other;}
	PricePrecise operator|(const PricePrecise& other) const{return PricePrecise(*this) |= other;}
///
	const PricePrecise& GetPriceValue() const{return *this;}
	SignedPrice GetPercentChange(const SignedPricePrecise& change) const;
	Price GetPercentChange(const PricePrecise& change) const;

	void SubtractLesserPrice(const PricePrecise& other)
	{
		m_dollars -= other.m_dollars;
		if(m_dollarFraction < other.m_dollarFraction)
		{
			--m_dollars;
			m_dollarFraction = divider - (other.m_dollarFraction - m_dollarFraction);
		}
		else
		{
			m_dollarFraction -= other.m_dollarFraction;
		}
		Canonicalize();
	}
	PricePrecise GetPositivePriceDiffWithoutVerification(const PricePrecise& other) const{PricePrecise price(*this); price.SubtractLesserPrice(other); return price;}
//	PricePrecise GetAbsDiff(const PricePrecise& other) const{return other < *this ? PricePrecise(*this) -= other : PricePrecise(other) -= *this;}
	PricePrecise GetAbsDiff(const PricePrecise& other) const{return other < *this ? GetPositivePriceDiffWithoutVerification(other) : other.GetPositivePriceDiffWithoutVerification(*this);}
	PricePrecise GetPositivePriceDiff(const PricePrecise& other) const{return PricePrecise(*this) -= other;}
	PricePrecise operator+(const PricePrecise& other) const{return PricePrecise(other) += *this;}
	PricePrecise operator+(const Price& other) const{return PricePrecise(other) += *this;}

	SignedPricePrecise operator-(const PricePrecise& other) const{return SignedPricePrecise(*this) -= SignedPricePrecise(other);}
	SignedPricePrecise operator-(const SignedPricePrecise& other) const{return SignedPricePrecise(*this) -= other;}
//	SignedPrice operator-(const PricePrecise& other) const{return SignedPrice(*this) -= SignedPrice(other);}
//	SignedPrice operator+(const SignedPrice& other) const{return SignedPrice(*this) += other;}
//	SignedPrice operator-(const SignedPrice& other) const{return SignedPrice(*this) -= other;}
//	SignedPrice operator+(const Money& other) const{return SignedPrice(*this) += SignedPrice(other);}
//	SignedPrice operator-(const Money& other) const{return SignedPrice(*this) -= SignedPrice(other);}

	bool isSamePrice(const PricePrecise& other) const{return operator==(other);}
	bool isLessPrice(const PricePrecise& other) const{return operator<(other);}
	bool isGreaterPrice(const PricePrecise& other) const{return !operator<=(other);}
//	void SetUInt64Price(const unsigned __int64& price){*(unsigned __int64*)&m_dollars = price;}
	Money operator*(__int64 quantity) const;
	Money operator/(__int64 quantity) const;
	PricePrecise operator*(const PricePrecise& multiplier) const;
//	void Canonicalize();
	size_t GetHashValue() const{return ((size_t)m_dollars << 16) | ((size_t)m_dollarFraction >> 16);}
};

template<> struct std::make_signed<Money>{typedef Money type;};
template<> struct std::make_signed<SignedPrice>{typedef SignedPrice type;};
template<> struct std::make_signed<Price>{typedef SignedPrice type;};
template<> struct std::make_unsigned<Money>{typedef Money type;};
template<> struct std::make_unsigned<SignedPrice>{typedef Price type;};
template<> struct std::make_unsigned<Price>{typedef Price type;};
template<> struct std::make_unsigned<PricePrecise>{typedef PricePrecise type;};

template<> struct std::is_signed<Money> : std::true_type{};
template<> struct std::is_signed<SignedPrice> : std::true_type{};
template<> struct std::is_signed<Price> : std::false_type{};
template<> struct std::is_signed<PricePrecise> : std::false_type{};
template<> struct std::is_unsigned<Money> : std::false_type{};
template<> struct std::is_unsigned<SignedPrice> : std::false_type{};
template<> struct std::is_unsigned<Price> : std::true_type{};
template<> struct std::is_unsigned<PricePrecise> : std::true_type{};

class MoneyQuantity : public Money
{
public:
	MoneyQuantity(const __int64& dollars, const short& dollarFraction, const int& quantity):
		Money(dollars, dollarFraction),
		m_quantity(quantity)
	{
	}
	MoneyQuantity(const Money& money, const int& quantity):Money(money),m_quantity(quantity){}
	MoneyQuantity():m_quantity(0){}

//	static const MoneyQuantity moneyQuantityZero;//(0, 0, 0);

	const int& GetQuantity() const{return m_quantity;}
	void SetQuantity(const int& quantity){m_quantity = quantity;}
	void IncrementQuantity(const int& quantity){m_quantity += quantity;}
	void DecrementQuantity(const int& quantity){m_quantity -= quantity;}
	void SetValues(const __int64& dollars, const short& dollarFraction, const int& quantity)
	{
		SetValue(dollars, dollarFraction);
		m_quantity = quantity;
	}
	bool SameQuantity(const MoneyQuantity& other) const{return m_quantity == other.m_quantity;}
	size_t GetHashValue() const{return ((size_t)m_dollars << 16) | (m_dollarFraction + m_quantity);}
protected:
	int m_quantity;
};

class PriceQuantity : public Price
{
public:
	PriceQuantity(const unsigned int& dollars, const unsigned int& dollarFraction, const unsigned int& quantity):
		Price(dollars, dollarFraction),
		m_quantity(quantity)
	{
	}
	PriceQuantity(const Price& price, const unsigned int& quantity):Price(price),m_quantity(quantity){}
	PriceQuantity():m_quantity(0){}

//	static const PriceQuantity priceQuantityZero;//(0, 0, 0);

	const unsigned int& GetQuantity() const{return m_quantity;}
	void SetQuantity(const unsigned int& quantity){m_quantity = quantity;}
	void IncrementQuantity(const unsigned int& quantity){m_quantity += quantity;}
	bool DecrementQuantity(const unsigned int& quantity)
	{
		if(m_quantity > quantity)
		{
			m_quantity -= quantity;
			return true;
		}
		else
		{
			m_quantity = 0;
			return false;
		}
	}
	void SetValues(const unsigned int& dollars, const unsigned int& dollarFraction, const unsigned int& quantity)
	{
		SetValue(dollars, dollarFraction);
		m_quantity = quantity;
	}
	bool SameQuantity(const PriceQuantity& other) const{return m_quantity == other.m_quantity;}
	size_t GetHashValue() const{return ((size_t)m_dollars << 16) | (((size_t)m_dollarFraction >> 16) + m_quantity);}
//	bool operator==(const PriceQuantity& other) const{return Price::operator==(other) && m_quantity == other.m_quantity;}
//	bool operator!=(const PriceQuantity& other) const{return !operator==(other);}
	virtual void Nullify(){SetZero(); m_quantity = 0;}
protected:
	unsigned int m_quantity;
};

inline bool U_RectsIntersectHorizontally(const RECT& rect1, const RECT& rect2)
{
	return rect1.left < rect2.right && rect1.right > rect2.left;
}

inline bool U_RectsIntersectVertically(const RECT& rect1, const RECT& rect2)
{
	return rect1.top < rect2.bottom && rect1.bottom > rect2.top;
}

inline bool U_RectsIntersect(const RECT& rect1, const RECT& rect2)
{
	U_RectsIntersectHorizontally(rect1, rect2) && U_RectsIntersectVertically(rect1, rect2);
}

inline void U_GetRectInCenterRect(const RECT& center, RECT& rect)
{
	int p = (center.left + center.right + rect.left - rect.right) / 2;
	rect.right += p - rect.left;
	rect.left = p;

	p = (center.top + center.bottom + rect.top - rect.bottom) / 2;
	rect.bottom += p - rect.top;
	rect.top = p;
}

inline void U_GetRectInsideRect(const RECT& outer, RECT& inner)
{
	if(inner.right > outer.right)
	{
		inner.left -= inner.right - outer.right;
		inner.right = outer.right;
	}
	if(inner.bottom > outer.bottom)
	{
		inner.top -= inner.bottom - outer.bottom;
		inner.bottom = outer.bottom;
	}
	if(inner.left < outer.left)
	{
		inner.right += outer.left - inner.left;
		inner.left = outer.left;
	}
	if(inner.top < outer.top)
	{
		inner.bottom += outer.top - inner.top;
		inner.top = outer.top;
	}
}

template<class T>
unsigned char U_CountFlags(T flags, unsigned char maxFlags)
{
	unsigned char flagCount = 0;
	if(!maxFlags || maxFlags > sizeof(T) * 8)
	maxFlags = sizeof(T) * 8;

	for(; maxFlags; --maxFlags, flags >>= 1)
	{
		if(!flags)
		break;

		if(flags & 1)
		++flagCount;
	}

	return flagCount;
}


///
template<class T>
//void U_ToStringAsWholePercent(const T& value, std::string& text)
void U_ToStringAsWholePercent(T val, std::string& text)
{
	char num[33];
//	T val = value;
	if(val > 100)
	{
		const T whole = val / 100;
		text += U_UnsignedNumberToStrNoDecDigits(whole, num, sizeof(num));
		val -= whole * 100;
	}
	else if(val == 100)
	{
		text += '1';
		val = 0;
	}
	else text += '0';

	text += '.';
	if(val < 10)
	{
		text += '0';
	}
	else
	{
		const T whole = val / 10;
		text += '0' + whole;
		val -= whole * 10;
//		text += U_UnsignedNumberToStrNoDecDigits(val, num, sizeof(num));
	}
	text += '0' + val;
}



template <class T>
unsigned int U_GetUnsignedNumberStrLength(const T& str)
{
	unsigned int i = 0;
	for(T flag = 0xFF; str & flag; flag <<= 8, ++i);

	return i;
/*
	const unsigned char* cursor = (const unsigned char*)&str;
	unsigned int i = 0;
	for(;;)
	{
		if(*cursor)
		{
			++i;
			if(i < sizeof(T))
			{
				++cursor;
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
	return i;
*/
}

template<class T>
void U_AppendUnsignedNumberAsString(std::string& text, T str)
{
	for(; str; str >>= 8)text += (char)str;
}

template<class T>
void U_AppendUnsignedNumberAsStringLowercase(std::string& text, T str)
{
	char c;
	for(; str; str >>= 8)
	{
		c = (char)str;
		if(c >= 'A' && c <= 'Z')c += 0x20;
		text += c;
	}
}

template<class T>
void U_AppendUnsignedNumberAsStringUppercase(std::string& text, T str)
{
	char c;
	for(; str; str >>= 8)
	{
		c = (char)str;
		if(c >= 'a' && c <= 'z')c -= 0x20;
		text += c;
	}
}

template<class T>
void U_AppendUnsignedNumberAsStringTerm0(std::string& text, T str)
{
	str &= (T)-1 >> 8;
	for(; str; str >>= 8)text += (char)str;
}

template<class T>
void U_AppendUnsignedNumberAsStringWithDelimiter(std::string& text, T str, const char& del)
{
	for(; str; str >>= 8)text += (char)str;
	if(del)text += del;
}

template<class T>
void U_AppendUnsignedNumberAsStringWithDelimiterTerm0(std::string& text, T str, const char& del)//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	str &= (T)-1 >> 8;
	for(; str; str >>= 8)text += (char)str;
	if(del)text += del;
}

template<class T>
T U_RepresentStringAsUnsignedNumber(const char* str, unsigned char length = sizeof(T))
{
	T ret = 0;
	char* dst = (char*)&ret;
	if(length > sizeof(ret))length = sizeof(ret);
	for(char c = *str; c && length; --length, ++dst, c = *++str)
	{
		*dst = c;
	}
	return ret;
}

template<class T>
T U_RepresentStringAsUnsignedNumberToDelimiter(const char*& str, const char& delimiter, const char& delimiter2, unsigned char length = sizeof(T))
{
	T ret = 0;
	char* dst = (char*)&ret;
	if(length > sizeof(ret))length = sizeof(ret);
	for(char c = *str; c; c = *++str)
	{
		if(delimiter == c || delimiter2 == c)
		{
			++str;
			break;
		}
		if(length)
		{
			*dst = c;
			--length;
			++dst;
		}
	}
	return ret;
}

template<class Collection>
void U_RepresentStringSetAsUnsignedNumberToDelimiter(const char*& cursor, Collection& collection, const char& delimiter, const char& delimiterEnd, unsigned char length = sizeof(Collection::value_type))
{
	Collection::value_type ret = 0;
	char* dst = (char*)&ret;
	if(length > sizeof(Collection::value_type))length = sizeof(Collection::value_type);
	unsigned char len = length;
	for(char c = *cursor; ; c = *++cursor)
	{
		if(delimiterEnd == c)
		{
			if(ret)collection.insert(ret);
			++cursor;
			break;
		}
		else if(!c)
		{
			if(ret)collection.insert(ret);
			break;
		}
		else if(delimiter == c)
		{
			if(ret)collection.insert(ret);
			++cursor;
			dst = (char*)&ret;
			ret = 0;
			len = length;
		}
		else if(len)
		{
			*dst = c;
			--len;
			++dst;
		}
	}
}

template<class Collection>
void U_CollectionToString(std::string& info, const Collection& collection, const char& delimiter, const char& delimiterEnd)
{
	if(!collection.empty())
	{
		char buf[sizeof(Collection::value_type) + 1];
		buf[sizeof(Collection::value_type)] = '\0';
		Collection::value_type& numVenue = *(Collection::value_type*)buf;
		bool first = true;
		Collection::const_iterator it;
		Collection::const_iterator itend = collection.cend();
		for(it = collection.cbegin(); it != itend; ++it)
		{
			if(first)
			{
				first = false;
			}
			else
			{
				info += delimiter;
			}
			numVenue = *it;
			info += buf;
		}
	}
	info += delimiterEnd;
}
/*
template<class F, F N, unsigned char DEC>
struct FPower
{
    enum : F{value = N * FPower<F, N, DEC - 1>::value};
};

template<class F, F N>
struct FPower<F, N, 0>
{
    enum : F{value = 1};
};

template<class F, unsigned char DEC>
struct FPower10 : public FPower<F, 10, DEC>
{
};
*/

template<class T>
inline unsigned char U_GetDecDigits(const T& divider)//char or unsigned char
{
	switch(divider)
	{
		case 1:
		return 0;

		case 10:
		return 1;

		case 100:
		return 2;

		default:
		return 0xFF;
	}
}

template<>
inline unsigned char U_GetDecDigits(const unsigned short& divider)//short or unsigned short
{
	switch(divider)
	{
		case 1:
		return 0;

		case 10:
		return 1;

		case 100:
		return 2;

		case 1000:
		return 3;

		case 10000:
		return 4;

		default:
		return 0xFF;
	}
}

template<>
inline unsigned char U_GetDecDigits(const unsigned int& divider)//int or unsigned int
{
	switch(divider)
	{
		case 1:
		return 0;

		case 10:
		return 1;

		case 100:
		return 2;

		case 1000:
		return 3;

		case 10000:
		return 4;

		case 100000:
		return 5;

		case 1000000:
		return 6;

		case 10000000:
		return 7;

		case 100000000:
		return 8;

		case 1000000000:
		return 9;

		default:
		return 0xFF;
	}
}

template<>
inline unsigned char U_GetDecDigits<unsigned __int64>(const unsigned __int64& divider)
{
/*
	switch(sizeof(T))
	{
		case sizeof(unsigned char):
		switch(divider)
		{
			case 1:
			return 0;

			case 10:
			return 1;

			case 100:
			return 2;

			default:
			return 0xFF;
		}
		break;

		case sizeof(unsigned short):
		switch(divider)
		{
			case 1:
			return 0;

			case 10:
			return 1;

			case 100:
			return 2;

			case 1000:
			return 3;

			case 10000:
			return 4;

			default:
			return 0xFF;
		}
		break;

		case sizeof(unsigned int):
		switch(divider)
		{
			case 1:
			return 0;

			case 10:
			return 1;

			case 100:
			return 2;

			case 1000:
			return 3;

			case 10000:
			return 4;

			case 100000:
			return 5;

			case 1000000:
			return 6;

			case 10000000:
			return 7;

			case 100000000:
			return 8;

			case 1000000000:
			return 9;

			default:
			return 0xFF;
		}
		break;

		case sizeof(unsigned __int64):
*/
		switch(divider)
		{
			case 1ui64:
			return 0;

			case 10ui64:
			return 1;

			case 100ui64:
			return 2;

			case 1000ui64:
			return 3;

			case 10000ui64:
			return 4;

			case 100000ui64:
			return 5;

			case 1000000ui64:
			return 6;

			case 10000000ui64:
			return 7;

			case 100000000ui64:
			return 8;

			case 1000000000ui64:
			return 9;

			case 10000000000ui64:
			return 10;

			case 100000000000ui64:
			return 11;

			case 1000000000000ui64:
			return 12;

			case 10000000000000ui64:
			return 13;

			case 100000000000000ui64:
			return 14;

			case 1000000000000000ui64:
			return 15;

			case 10000000000000000ui64:
			return 16;

			case 100000000000000000ui64:
			return 17;

			case 1000000000000000000ui64:
			return 18;

			default:
			return 0xFF;
		}
/*
		break;

		default:
		return 0xFF;
	}
*/
}

template<>
inline unsigned char U_GetDecDigits(const short& divider)//short or unsigned short
{
	return U_GetDecDigits((unsigned short)divider);
}

template<>
inline unsigned char U_GetDecDigits(const int& divider)//short or unsigned short
{
	return U_GetDecDigits((unsigned int)divider);
}

template<>
inline unsigned char U_GetDecDigits(const __int64& divider)//short or unsigned short
{
	return U_GetDecDigits((unsigned __int64)divider);
}

template<class T>
char* U_UnsignedNumberToStrWithZeroTruncated(T n, char* num, unsigned int size, unsigned char decDigits, unsigned char minDecDigits, char del = '\0')
{
	if(minDecDigits >= decDigits)
	{
		char* cursor = U_UnsignedNumberToStrNoDecDigits(n, num, size, del);
		unsigned int bufsize1 = (unsigned int)(cursor - num);
		unsigned char fractionSize = (unsigned char)(size - bufsize1);
		if(del)--fractionSize;
		if(fractionSize <= minDecDigits)
		{
			unsigned int zeroSize = minDecDigits - fractionSize + 1;
			if(zeroSize > bufsize1)zeroSize = bufsize1;
			for(; zeroSize; --zeroSize)
			{
				--cursor;
				*cursor = '0';
			}
		}
		return cursor;
	}
	else if(size)
	{
		--size;
		char* cursor = num + size;
		*cursor = '\0';
		if(!size)return cursor;
		if(del)
		{
			--cursor;
			*cursor = del;
			if(!--size)return cursor;
		}
		if(n)
		{
			T n0;

			T minN = U_GetDivider<T>(minDecDigits);

			unsigned char additionalZeros = 0;
			T n10 = U_GetDivider<T>(--decDigits);
			if(n < n10)
			{
				T nt = n;
				T nt10;
				for(; n < n10; n10 = U_GetDivider<T>(--decDigits), ++additionalZeros)
				{
					nt10 = nt / 10;
					if(nt10 * 10 == nt)
					{
						minN /= 10;
//						nt /= 10;
						nt = nt10;
					}
					if(!decDigits)
					{
						break;
					}
				}
				n = nt;
			}
			bool truncateMode = true;
			for(;;)
			{
				n10 = n / 10;
				if(truncateMode)
				{
					n0 = n10 * 10;
					if(n0 != n || n < minN)
					{
						--cursor;
						*cursor = '0' + (char)(n - n0);
						truncateMode = false;
						--size;
					}
				}
				else
				{
					--cursor;
					*cursor = '0' + (char)(n - n10 * 10);
					--size;
				}
				n = n10;
				if(n)
				{
					if(!size)return cursor;
				}
				else
				{
					break;
				}
			}
//			if(minDecDigits < additionalZeros)additionalZeros = minDecDigits;
			for(; additionalZeros && size; --additionalZeros, --size)
			{
				--cursor;
				*cursor = '0';
				if(!--size)return cursor;
			}
		}
		else
		{
			unsigned int zeroSize = minDecDigits;
			if(zeroSize > size)zeroSize = size;
			for(; zeroSize; --zeroSize)
			{
				--cursor;
				*cursor = '0';
				if(!--size)return cursor;
			}
		}
		return cursor;
	}
	return num;
}

template<class T>
char* U_AppendTwoUIntDigits(T number, char* num, unsigned int size, char del = '\0', bool terminatingZero = true)
{
	if(size)
	{
		--size;
		char* cursor = num + size;
		if(terminatingZero)
		{
			*cursor = '\0';
			if(!size)return cursor;
			--cursor;
		}
		if(del)
		{
			*cursor = del;
			if(!--size)return cursor;
			--cursor;
		}
		if(number < 10)
		{
			*cursor = '0' + number;
			if(!--size)return cursor;
			*--cursor = '0';
		}
		else
		{
			T digit = number / 10;
			*cursor = '0' + (number - digit * 10);
			if (!--size)return cursor;
			*--cursor = '0' + digit;
		}
		return cursor;
	}
	return num;
}

template<class T>
char* U_UnsignedNumber64ToStr(T n, char* num, unsigned int size, const char del = '\0', const unsigned char minLength = 0)//'a' or 'A'
{
	if(size)
	{
		--size;
		char* cursor = num + size;
		*cursor = '\0';
		if(!size)return cursor;
		if(del)
		{
			--cursor;
			*cursor = del;
			if(!--size)return cursor;
		}

		unsigned char len = 0;
		char b;
		do
		{
			--cursor;
			++len;

			b = (char)(n & 63);
			switch(b)
			{
				case 62:
				*cursor = '{';
				break;

				case 63:
				*cursor = '}';
				break;

				default:
				*cursor = (b < 10 ? '0' : b < 36 ? 'A' - 10 : 'a' - 36) + b;
				break;
			}
			if(!--size)return cursor;
			n >>= 6;
		}
		while(n);
		if(len < minLength)
		{
			for(; len < minLength; ++len)
			{
				*--cursor = '0';
				if(!--size)return cursor;
			}
		}
		return cursor;
	}
	return num;
}

template<class T>
const char* U_Read64UnsignedNumberFromString(T& number, const char* str, const char& del = '\0', const T& defaultValue = 0, unsigned char* errorPlace = nullptr)
{
	if(errorPlace)*errorPlace = 0xFF;
	if(*str)
	{
		if(del == *str)
		{
			++str;
			number = defaultValue;
		}
		else
		{
			unsigned char i = 0;
			number = 0;
			for(char c = *str; c; c = *++str)
			{
				if(del == c)
				{
					++str;
					break;
				}
				if(i < sizeof(T) * 8 / 6)
				{
					number <<= 6;

					if(c >= '0' && c <= '9')
					{
						number += c - '0';
					}
					else if(c >= 'A' && c <= 'F')
					{
						number += c - ('A' - 10);
					}
					else if(c >= 'a' && c <= 'f')
					{
						number += c - ('a' - 36);
					}
					else if(c == '{')
					{
						number += 62;
					}
					else if(c == '}')
					{
						number += 63;
					}
					else if(errorPlace && *errorPlace == 0xFF)
					{
						*errorPlace = i;
					}
					++i;
				}
				else if(errorPlace && *errorPlace == 0xFF)
				{
					*errorPlace = i;
				}
			}
		}
	}
	else
	{
		number = defaultValue;
	}
	return str;
}

inline char* U_UnsignedCharHexToStr(unsigned char n, char* num, unsigned int size, const char del = '\0', const bool capitals = false)
{
	if(size)
	{
		--size;
		char* cursor = num + size;
		*cursor = '\0';
		if(!size)return cursor;
		if(del)
		{
			--cursor;
			*cursor = del;
			if(!--size)return cursor;
		}

		const char startChar = (capitals ? 'A' : 'a') - 10;

		unsigned char b = (char)(n & 0xF);
		--cursor;
		*cursor = (b < 10 ? '0' : startChar) + b;
		if (!--size)return cursor;

		n >>= 4;

		b = (char)(n & 0xF);
		--cursor;
		*cursor = (b < 10 ? '0' : startChar) + b;
		if (!--size)return cursor;

		return cursor;
	}
	return num;
}

template<class T>
char* U_UnsignedNumberHexToStr(T n, char* num, unsigned int size, const char del = '\0', const bool capitals = false, const unsigned char minLength = 0)//'a' or 'A'
{
	if(size)
	{
		--size;
		char* cursor = num + size;
		*cursor = '\0';
		if(!size)return cursor;
		if(del)
		{
			--cursor;
			*cursor = del;
			if(!--size)return cursor;
		}

//		T n16;
		unsigned char len = 0;
		char b;
		const char startChar = (capitals ? 'A' : 'a') - 10;
		do
		{
			--cursor;
			++len;

			b = (char)(n & 0xF);
			*cursor = (b < 10 ? '0' : startChar) + b;
			if(!--size)return cursor;
			n >>= 4;
/*
			n16 = n >> 4;
			n -= n16 << 4;
			*cursor = (n < 10 ? '0' : 'a' - 10) + (char)n;
			if(!--size)return cursor;
			n = n16;
*/

		}
		while(n);
		if(len < minLength)
		{
			for(; len < minLength; ++len)
			{
				*--cursor = '0';
				if(!--size)return cursor;
			}
		}
		return cursor;
	}
	return num;
}

template<class T>
char* U_UnsignedNumberHexToStrNoTerm0(T n, char* num, unsigned int size, const char del = '\0', const bool capitals = false)// 'a' or 'A'
{
	if(size)
	{
		char* cursor = num + (size - 1);
		if(del)
		{
			--cursor;
			*cursor = del;
			if(!--size)return cursor;
		}

//		T n16;
		char b;
		const char startChar = (capitals ? 'A' : 'a') - 10;
		do
		{
			--cursor;

			b = (char)(n & 0xF);
			*cursor = (b < 10 ? '0' : startChar) + b;
			if(!--size)return cursor;
			n >>= 4;
/*
			n16 = n >> 4;
			n -= n16 << 4;
			*cursor = (n < 10 ? '0' : 'a' - 10) + (char)n;
			if(!--size)return cursor;
			n = n16;
*/
		}
		while(n);
		return cursor;
	}
	return num;
}

template<class T>
char* U_UnsignedNumberToStrNoTerm0(T n, char* num, unsigned int size, char del = '\0')
{
	if(size)
	{
		char* cursor = num + (size - 1);
		if(del)
		{
			*cursor = del;
			if(!--size)return cursor;
			--cursor;
		}
		T n10;
		for(;;)
		{
			n10 = n / 10;
			*cursor = '0' + (char)(n - 10 * n10);
			--size;
			n = n10;
			if(n)
			{
				if(!size)return cursor;
				--cursor;
			}
			else
			{
				break;
			}
		}

		return cursor;
	}
	return num;
}

template<class T>
char* U_UnsignedNumberToStr(T n, char* num, unsigned int size, unsigned char decDigits = 0, const char& del = '\0', const char& decChar = '.')
{
	if(size)
	{
		--size;
		char* cursor = num + size;
		*cursor = '\0';
		if(!size)return cursor;
		if(del)
		{
			--cursor;
			*cursor = del;
			if(!--size)return cursor;
		}
		T n10;
		if(decDigits)
		{
			do
			{
				--cursor;
				--decDigits;
				n10 = n / 10;
				*cursor = '0' + (char)(n - 10 * n10);
				if(!--size)return cursor;
				n = n10;
			}
			while(decDigits);
			--cursor;
			*cursor = decChar;
			if(!--size)return cursor;
		}
		do
		{
			--cursor;
			n10 = n / 10;
			*cursor = '0' + (char)(n - 10 * n10);
			if(!--size)return cursor;
			n = n10;
		}
		while(n);
		return cursor;
	}
	return num;
}

template<class T>
char* U_UnsignedNumberToStrNoDecDigits(T n, char* num, unsigned int size, char del = '\0')
{
	if(size)
	{
		--size;
		char* cursor = num + size;
		*cursor = '\0';
		if(!size)return cursor;
		if(del)
		{
			--cursor;
			*cursor = del;
			if(!--size)return cursor;
		}
		T n10;
		do
		{
			--cursor;
			n10 = n / 10;
			*cursor = '0' + (char)(n - 10 * n10);
			if(!--size)return cursor;
			n = n10;
		}
		while(n);
		return cursor;
	}
	return num;
}

template<class T>
char* U_SignedNumberToStr(T n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0', const char& decChar = '.')
{
	if(n < 0)
	{
		num = U_UnsignedNumberToStr(-n, num, size, decDigits, del, decChar);
		--num;
		*num = '-';
		return num;
	}
	else
	{
		return U_UnsignedNumberToStr(n, num, size, decDigits, del, decChar);
	}
}

template<class T>
char* U_SignedNumberToStrNoDecDigits(T n, char* num, unsigned int size, char del = '\0')
{
	if(n < 0)
	{
		num = U_UnsignedNumberToStrNoDecDigits(-n, num, size, del);
		--num;
		*num = '-';
		return num;
	}
	else
	{
		return U_UnsignedNumberToStrNoDecDigits(n, num, size, del);
	}
}

template<class T>
char* U_UnsignedNumberToStrWithCommas(T n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0', const char& decChar = '.')
{
	if(size)
	{
		--size;
		char* cursor = num + size;
		*cursor = '\0';
		if(!size)return cursor;
		if(del)
		{
			--cursor;
			*cursor = del;
			if(!--size)return cursor;
		}
		T n10;
		if(decDigits)
		{
			do
			{
				--cursor;
				--decDigits;
				n10 = n / 10;
				*cursor = '0' + (char)(n - 10 * n10);
				if(!--size)return cursor;
				n = n10;
			}
			while(decDigits);
			--cursor;
			*cursor = decChar;
			if(!--size)return cursor;
		}
		unsigned char three = 0;
		do
		{
			if(three == 3)
			{
				three = 1;
				--cursor;
				*cursor = ',';
				if(!--size)return cursor;
			}
			else
			{
				++three;
			}
			--cursor;
			n10 = n / 10;
			*cursor = '0' + (char)(n - 10 * n10);
			if(!--size)return cursor;
			n = n10;
		}
		while(n);
		return cursor;
	}
	return num;
}

template<class T>
char* U_UnsignedNumberToStrWithCommasNoDecDigits(T n, char* num, unsigned int size, bool commas, char del = '\0')
{
	if(size)
	{
		--size;
		char* cursor = num + size;
		*cursor = '\0';
		if(!size)return cursor;
		if(del)
		{
			--cursor;
			*cursor = del;
			if(!--size)return cursor;
		}
		T n10;
		if(commas)
		{
			unsigned char three = 0;
			do
			{
				if(three == 3)
				{
					three = 1;
					--cursor;
					*cursor = ',';
					if(!--size)return cursor;
				}
				else
				{
					++three;
				}
				--cursor;
				n10 = n / 10;
				*cursor = '0' + (char)(n - 10 * n10);
				if(!--size)return cursor;
				n = n10;
			}
			while(n);
		}
		else
		{
			do
			{
				--cursor;
				n10 = n / 10;
				*cursor = '0' + (char)(n - 10 * n10);
				if(!--size)return cursor;
				n = n10;
			}
			while(n);
		}
		return cursor;
	}
	return num;
}

template<class T>
char* U_SignedNumberToStrWithCommas(T n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0', const char& decChar = '.')
{
	if(n < 0)
	{
		char* cursor = U_UnsignedNumberToStrWithCommas(-n, num, size, decDigits, del, decChar);
		if(num != cursor)
		{
			--cursor;
			*cursor = '-';
		}
		return cursor;
	}
	else
	{
		return U_UnsignedNumberToStrWithCommas(n, num, size, decDigits, del, decChar);
	}
}

template<class T>
char* U_SignedNumberToStrWithCommasNoDecDigits(T n, char* num, unsigned int size, bool commas, char del = '\0')
{
	if(n < 0)
	{
		char* cursor = U_UnsignedNumberToStrWithCommasNoDecDigits(-n, num, size, commas, del);
		if(num != cursor)
		{
			--cursor;
			*cursor = '-';
		}
		return cursor;
	}
	else
	{
		return U_UnsignedNumberToStrWithCommasNoDecDigits(n, num, size, commas, del);
	}
}

template<class T>
char* U_UnsignedNumberToStrWithCommasNoTerm0(T n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0', const char& decChar = '.')
{
	if(size)
	{
		char* cursor = num + (size - 1);
		if(del)
		{
			*cursor = del;
			if(!--size)return cursor;
			--cursor;
		}
		T n10;
		if(decDigits)
		{
			for(; decDigits; --decDigits, --cursor)
			{
				n10 = n / 10;
				*cursor = '0' + (char)(n - 10 * n10);
				if(!--size)return cursor;
				n = n10;
			}
			*cursor = decChar;
			if(!--size)return cursor;
			--cursor;
		}
		unsigned char three = 0;
		for(;;)
		{
			if(three == 3)
			{
				three = 1;
				*cursor = ',';
				if(!--size)return cursor;
				--cursor;
			}
			else
			{
				++three;
			}
			n10 = n / 10;
			*cursor = '0' + (char)(n - 10 * n10);
			n = n10;
			if(!--size)return cursor;
			if(n)--cursor;
			else break;
		}
		return cursor;
	}
	return num;
}

template<class T>
char* U_SignedNumberToStrWithCommasNoTerm0(T n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0', const char& decChar = '.')
{
	if(n < 0)
	{
		char* cursor = U_UnsignedNumberToStrWithCommasNoTerm0(-n, num, size, decDigits, del, decChar);
		if(num != cursor)
		{
			--cursor;
			*cursor = '-';
		}
		return cursor;
	}
	else
	{
		return U_UnsignedNumberToStrWithCommasNoTerm0(n, num, size, decDigits, del, decChar);
	}
}

template<class T>
T U_GetUnsignedNumberPrintable(const T& n)
{
	T ret = 0;
	T mask = 0;
	T slot = 0xFF;
	unsigned char shift = 0;
	unsigned char c;
	for(unsigned char i = 0; i < sizeof(T); ++i, slot <<= 8, shift += 8)
	{
		mask = (n & slot);
		c = (unsigned char)(mask >> shift);
		if(c > 32 && c < 127)
		ret |= mask;
		else
		break;
	}
	return ret;
}

//Use U_AppendUnsignedNumberAsString
/*
template<class T>
void U_AppendNumberAsString(std::string& str, const T& number, const char& del = '\0')//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	const char* cursor = (const char*)&number;
	char c = *cursor;
	for(unsigned char i = sizeof(number); c && i; --i, c = *++cursor)
	{
		str += c;
	}
	if(del)str += del;
}

template<class T>
void U_AppendNumberAsStringTerm0(std::string& str, const T& number, const char& del = '\0')//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	const char* cursor = (const char*)&number;
	char c = *cursor;
	for(unsigned char i = sizeof(number) - 1; c && i; --i, c = *++cursor)
	{
		str += c;
	}
	if(del)str += del;
}
*/

template <class T>
static void U_CopyUnsignedNumberAsStringToClipboard(const T& number, HWND owner, unsigned char* errorCode = nullptr)
{
	char num[33];
	const char* ptr = U_UnsignedNumberToStrNoDecDigits(number, num, sizeof(num));
	U_CopyStringBufferToClipboard(ptr, owner, (unsigned int)(sizeof(num) - (ptr - num) - 1), errorCode);
}

template <class T>
static void U_CopySignedNumberAsStringToClipboard(const T& number, HWND owner, unsigned char* errorCode = nullptr)
{
	char num[33];
	const char* ptr = U_SignedNumberToStrNoDecDigits(number, num, sizeof(num));
	U_CopyStringBufferToClipboard(ptr, owner, (unsigned int)(sizeof(num) - (ptr - num) - 1), errorCode);
}

template<class T>
const char* U_GetStrFromNumber(const T& number, const char& del = '\0')//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	static std::string str;
	str.clear();
	U_AppendUnsignedNumberAsStringWithDelimiter(str, number, del);
	return str.c_str();
}

template<class T>
const char* U_GetStrFromNumberTerm0(const T& number, const char& del = '\0')//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	static std::string str;
	str.clear();
	U_AppendUnsignedNumberAsStringWithDelimiterTerm0(str, number, del);
	return str.c_str();
}

template<class T>
const std::string& U_GetStringFromNumber(const T& number, const char& del = '\0')//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	static std::string str;
	str.clear();
	U_AppendUnsignedNumberAsStringWithDelimiter(str, number, del);
	return str;
}

template<class T>
const std::string& U_GetStringFromNumberTerm0(const T& number, const char& del = '\0')//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	static std::string str;
	str.clear();
	U_AppendUnsignedNumberAsStringWithDelimiterTerm0(str, number, del);
	return str;
}

template<class T>
const char* U_ReadUnsignedNumberFromString(T& number, const char* str, const char& del = '\0', const T& defaultValue = 0)
{
	if(*str)
	{
		if(del == *str)
		{
			++str;
			number = defaultValue;
		}
		else
		{
			number = 0;
			for(char c = *str; c; c = *++str)
			{
				if(del == c)
				{
					++str;
					break;
				}
				number *= 10;
				number += c - '0';
			}
		}
	}
	else
	{
		number = defaultValue;
	}
	return str;
}

template<class T>
const char* U_ReadUnsignedNumberFromStringAndVerify(T& number, const char* str, bool& valid, const char& del = '\0', const T& defaultValue = 0)
{
	if(*str)
	{
		if(del == *str)
		{
			++str;
			valid = defaultValue != (T)-1;
			number = defaultValue;
		}
		else
		{
			number = 0;
			for(char c = *str; c; c = *++str)
			{
				if(del == c)
				{
					++str;
					break;
				}
				if(c >= '0' && c <= '9')
				{
					number *= 10;
					number += c - '0';
				}
				else
				{
					U_SkipToDelimiter(str, del);
					valid = false;
					break;
				}
			}
		}
	}
	else
	{
		valid = defaultValue != (T)-1;
		number = defaultValue;
	}
	return str;
}

template<class T>
const char* U_ReadUnsignedNumberFromStringUpToLength(T& number, const char* str, unsigned int& length, const char& del = '\0', const T& defaultValue = 0)
{
	if(*str && length)
	{
		if(del == *str)
		{
			++str;
			--length;
			number = defaultValue;
		}
		else
		{
			number = 0;
			for(char c = *str; c && length; c = *++str, --length)
			{
				if(del == c)
				{
					++str;
					--length;
					break;
				}
				number *= 10;
				number += c - '0';
			}
		}
	}
	else
	{
		number = defaultValue;
	}
	return str;
}

template<class ST>
const char* U_ReadSignedNumberFromString(ST& number, const char* str, const char& del = '\0', const ST& defaultValue = 0)
{
	if(*str)
	{
		bool negative = *str == '-';
		if(negative || *str == '+')
		{
			++str;
			if(!*str)
			{
				number = negative ? -defaultValue : defaultValue;
				return str;
			}
		}
		std::make_unsigned<ST>::type positiveValue;
		str = U_ReadUnsignedNumberFromString(positiveValue, str, del);//, (unsigned int)0);
		number = negative ? -(ST)positiveValue : (ST)positiveValue;
	}
	else
	{
		number = defaultValue;
	}
	return str;
}

template<class T>
T U_GetUnsignedNumberFromString(const char* str, const char& del = '\0', const T& defaultValue = 0)
{
	T number;
	U_ReadUnsignedNumberFromString(number, str, del, defaultValue);
	return number;
}

template<class ST>
ST U_GetSignedNumberFromString(const char* str, const char& del = '\0', const ST& defaultValue = 0)
{
	ST number;
	U_ReadSignedNumberFromString(number, str, del, defaultValue);
	return number;
}

template<class T>
const char* U_ReadStrAsUnsignedNumberToken(T& number, const char*& str, char del = '\0', const T& defaultValue = 0)
{
	if(*str)
	{
		if(*str == del)
		{
			++str;
			number = defaultValue;
		}
		else
		{
			number = 0;
			char* dst = (char*)&number;
			char c = *str;
			for(unsigned int i = 0; c && c != del && i < sizeof(T); ++i, c = *++str, ++dst)
			{
				*dst = c;
			}

			for(; c; c = *++str)
			{
				if(c == del)
				{
					++str;
					break;
				}
			}
		}
	}
	else
	{
		number = defaultValue;
	}
	return str;
}

//Hex
template<class T>
const char* U_ReadHexUnsignedNumberFromString(T& number, const char* str, const char& del = '\0', const T& defaultValue = 0, unsigned char* errorPlace = nullptr)
{
	if(errorPlace)*errorPlace = 0xFF;
	if(*str)
	{
		if(del == *str)
		{
			++str;
			number = defaultValue;
		}
		else
		{
			unsigned char i = 0;
			number = 0;
			for(char c = *str; c; c = *++str)
			{
				if(del == c)
				{
					++str;
					break;
				}
				if(i < sizeof(T) * 2)
				{
					number <<= 4;
					if(c >= '0' && c <= '9')
					{
						number += c - '0';
					}
					else if(c >= 'A' && c <= 'F')
					{
						number += c - ('A' - 10);
					}
					else if(c >= 'a' && c <= 'f')
					{
						number += c - ('a' - 10);
					}
					else if(errorPlace && *errorPlace == 0xFF)
					{
						*errorPlace = i;
					}
					++i;
				}
				else if(errorPlace && *errorPlace == 0xFF)
				{
					*errorPlace = i;
				}
			}
		}
	}
	else
	{
		number = defaultValue;
	}
	return str;
}

template<class T>
const char* U_ReadHexUnsignedNumberFromStringUpToLength(T& number, const char* str, unsigned char& length, const char& del = '\0', const T& defaultValue = 0, unsigned char* errorPlace = nullptr)
{
	if(errorPlace)*errorPlace = 0xFF;
	if(*str && length)
	{
		if(del == *str)
		{
			++str;
			--length;
			number = defaultValue;
		}
		else
		{
			number = 0;
			unsigned char i = 0;
			for(char c = *str; c && length; c = *++str, --length)
			{
				if(del == c)
				{
					++str;
					--length;
					break;
				}
				if(i < sizeof(T) * 2)
				{
					number <<= 4;
					if(c >= '0' && c <= '9')
					{
						number += c - '0';
					}
					else if(c >= 'A' && c <= 'F')
					{
						number += c - ('A' - 10);
					}
					else if(c >= 'a' && c <= 'f')
					{
						number += c - ('a' - 10);
					}
					else if(errorPlace && *errorPlace == 0xFF)
					{
						*errorPlace = i;
					}
					++i;
				}
				else if(errorPlace && *errorPlace == 0xFF)
				{
					*errorPlace = i;
				}
			}
		}
	}
	else
	{
		number = defaultValue;
	}
	return str;
}

template<class ST>
const char* U_ReadHexSignedNumberFromString(ST& number, const char* str, const char& del = '\0', const ST& defaultValue = 0, unsigned char* errorPlace = nullptr)
{
	if(*str)
	{
		bool negative = *str == '-';
		if(negative || *str == '+')
		{
			++str;
			if(!*str)
			{
				number = negative ? -defaultValue : defaultValue;
				return str;
			}
		}
		std::make_unsigned<ST>::type positiveValue;
		str = U_ReadHexUnsignedNumberFromString(positiveValue, str, del, errorPlace);//, (unsigned int)0);
		number = negative ? -(ST)positiveValue : (ST)positiveValue;
	}
	else
	{
		number = defaultValue;
	}
	return str;
}

template<class T>
T U_GetHexUnsignedNumberFromString(const char* str, const char& del = '\0', const T& defaultValue = 0, unsigned char* errorPlace = nullptr)
{
	T number;
	U_ReadHexUnsignedNumberFromString(number, str, del, defaultValue, errorPlace);
	return number;
}

template<class ST>
ST U_GetHexSignedNumberFromString(const char* str, const char& del = '\0', const ST& defaultValue = 0, unsigned char* errorPlace = nullptr)
{
	ST number;
	U_ReadHexSignedNumberFromString(number, str, del, defaultValue, errorPlace);
	return number;
}
//
template<class T>
T U_ConvertNumberHexToDec(T number)
{
	T retValue = 0;
	T multiplier = 1;
	for(; number; number >>= 4)
	{
		retValue += (number & 0xF) * multiplier;
		multiplier *= 10;
	}
	return retValue;
}

template<class T>
void U_UIntToBitCharArray(const T& value, char* buf, unsigned int bufsize)//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	unsigned int bitCount = sizeof(T) << 3;
	if(bufsize < bitCount + 1)
	{
		for(T flag = (T)1 << (bitCount - 1); flag; flag >>= 1, ++buf)
		{
			*buf = value & flag ? '1' : '0';
		}
	}
	*buf = '\0';
}

template<class T>
void U_UIntToBitStr(const T& value, std::string& str)//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	for(T flag = (T)1 << ((sizeof(T) << 3) - 1); flag; flag >>= 1)
	{
		str += value & flag ? '1' : '0';
	}
}

template<class T>
void U_UIntToBitCharArrayReverse(const T& value, char* buf, unsigned int bufsize)//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	unsigned int bitCount = sizeof(T) << 3;
	if(bufsize < bitCount + 1)
	{
		for(T flag = 1; flag; flag <<= 1, ++buf)
		{
			*buf = value & flag ? '1' : '0';
		}
	}
	*buf = '\0';
}

template<class T>
void U_UIntToBitStrReverse(const T& value, std::string& str)//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	for(T flag = 1; flag; flag <<= 1)
	{
		str += value & flag ? '1' : '0';
	}
}

template<class T>
void U_BitStrUInt(T& value, const char*& cursor, char delimiter = '\0')//T should be unsigned char, unsigned short, unsigned int, unsigned __int64
{
	value = 0;
	T flag = (T)1 << ((sizeof(T) << 3) - 1);
	for(; flag && *cursor && *cursor != delimiter; flag >>= 1, ++cursor)
	{
		if(*cursor != '0')
		{
			value |= flag;
		}
	}
}

template<class T>
void U_AdjustCurrentConstraintValue(T& value, const T& adjustTo, const bool& zeroMeansUnlimited = true)
{
	if(!value || value > adjustTo && (!!adjustTo || !zeroMeansUnlimited))value = adjustTo;
}

template<class C>
void U_CopyCMap(C& mapTo, const C& mapFrom)
{
	mapTo.RemoveAll();
	const C::CPair* p;
	for(p = mapFrom.PGetFirstAssoc(); p; p = mapFrom.PGetNextAssoc(p))
	{
		mapTo[p->key] = p->value;
	}
}

template<class C1, class C2>
void U_AddSet(C1& c1, const C2& c2)
{
	c1.insert(c2.begin(), c2.end());
}

template<class C1, class C2>
void U_RemoveSet(C1& c1, const C2& c2)
{
	for(C2::iterator it = c2.begin(), itend = c2.end(); it != itend; ++it)
	{
		if(c1.erase(*it) && c1.empty())
		{
			break;
		}
	}
}

template<class C>//std collections
typename C::const_iterator U_GetCollectionItemAt(const C& c, const unsigned int& at)
{
	C::const_iterator it = c.cbegin(), itend = c.cend();
	for(unsigned int count = 0; it != itend && count < at; ++it, ++count);
	return it;
}

template<class C>//Sorted Sets
short U_CompareSets(const C& c1, const C& c2)
{
	for(C::const_iterator it1 = c1.cbegin(), it2 = c2.cbegin(), it1end = c1.cend(), it2end = c2.cend(); ; ++it1, ++it2)
	{
		if(it1 == it1end)return it2 == it2end ? 0 : -1;
		else if(it2 == it2end)return 1;
		else if(*it1 < *it2)return -1;
		else if(*it2 < *it1)return 1;
	}
	return 0;
}

template<class C>//Sorted Sets
bool U_SetsEqual(const C& c1, const C& c2)
{
	if(c1.size() == c2.size())
	{
		for(C::const_iterator it1 = c1.cbegin(), it2 = c2.cbegin(), it1end = c1.cend(), it2end = c2.cend(); ; ++it1, ++it2)
		{
			if(it1 == it1end)return it2 == it2end;
			else if(it2 == it2end || *it1 != *it2)return false;
		}
		return true;
	}
	return false;
}

template<class C>
bool HashSetsEqual(const C& c1, const C& c2)//Unordered sets, not multisets
{
	if(c1.size() != c2.size())
	{
		return false;
	}
	C::const_iterator foundEnd = c2.cend();
	C::const_iterator it = c1.cbegin();
	C::const_iterator itend = c1.cend();
	for(; it != itend; ++it)
	{
		if(c2.find(*it) == foundEnd)
		{
			return false;
		}
	}
/*
	for(it = c2.cbegin(); it != foundEnd; ++it)
	{
		if(c1.find(*it) == itend)
		{
			return false;
		}
	}
*/
	return true;
}

template<class C>
short U_CompareMaps(const C& c1, const C& c2)
{
	for(C::const_iterator it1 = c1.cbegin(), it2 = c2.cbegin(), it1end = c1.cend(), it2end = c2.cend(); ; ++it1, ++it2)
	{
		if(it1 == it1end)return it2 == it2end ? 0 : -1;
		else if(it2 == it2end)return 1;
		else if(it1->first < it2->first)return -1;
		else if(it2->first < it1->first)return 1;
		else if(it1->second < it2->second)return -1;
		else if(it2->second < it1->second)return 1;
	}
	return 0;
}

template<class C>
short U_MapsEqual(const C& c1, const C& c2)
{
	if(c1.size() == c2.size())
	{	
		for(C::const_iterator it1 = c1.cbegin(), it2 = c2.cbegin(), it1end = c1.cend(), it2end = c2.cend(); ; ++it1, ++it2)
		{
			if(it1 == it1end)return it2 == it2end;
			else if(it2 == it2end || it1->first != it2->first || it1->second != it2->second)return false;
		}
		return true;
	}
	return false;
}

template<class C>
struct lessUIntAsStr : public std::binary_function<C, C, bool>
{
	bool operator()(const C& p1, const C& p2) const
	{
		return U_UIntLessAsString(p1, p2);
/*
		C byteFirst;
		C byteSecond;
//		for(C byteValue = 0xFF; byteValue; byteValue <<= 8)
		for(C byteValue = 0xFF; ; byteValue <<= 8)
		{
			byteFirst = p1 & byteValue;
			byteSecond = p2 & byteValue;
			if(byteFirst < byteSecond)return true;
			else if(byteFirst > byteSecond || !byteFirst)return false;
		}
		return false;
*/
/*
		const unsigned char* c1 = (const unsigned char*)&p1;
		const unsigned char* c2 = (const unsigned char*)&p2;
		unsigned char a1 = *c1;
		unsigned char a2 = *c2;
		for(unsigned char i = sizeof(C); i; --i, a1 = *++c1, a2 = *++c2)
		{
			if(a1 < a2)
			{
				return true;
			}
			if(a1 > a2 || !a1)
			{
				return false;
			}
		}
		return false;
*/
	}
};

template<class C>
struct greaterUIntAsStr : public std::binary_function<C, C, bool>
{
	bool operator()(const C& p1, const C& p2) const
	{
		return U_UIntGreaterAsString(p1, p2);
	}
};

struct lessAccountIdAsStr : public std::binary_function<AccountId, AccountId, bool>
{
	bool operator()(const AccountId& p1, const AccountId& p2) const
	{
		return p1.CompareAsStrings(p2) < 0;
/*
		return p1.GetFirst() == p2.GetFirst() ?
			U_CompareUIntAsString(p1.GetSecond(), p2.GetSecond()) < 0:
			U_CompareUIntAsString(p1.GetFirst(), p2.GetFirst()) < 0;
*/
	}
};

template<class T>
void U_DoDecrementNumber(T& number, const T& by)
{
	if(number > by)number -= by;
	else number -= number;
}

template<class T>
void U_DoDecrementNumberToZero(T& number, const T& by)
{
	if(number > by)number -= by;
	else number = 0;
}

template<class T>
void U_DoVerifyAndDecrementNumberToZero(T& number, const T& by)
{
	if(by)U_DoDecrementNumberToZero(number, by);
}

template<class T>
void U_DoDecrementNumberToZero(T& number)
{
	if(number)--number;
}

template<class T>
bool U_AdjustValueByDifference(T& oldValue, const T& newValue, T& valueToAdjust)
{
	if(newValue != oldValue)
	{
		valueToAdjust += newValue;
		valueToAdjust -= oldValue;
		oldValue = newValue;
		return true;
	}
	return false;
}

template<class T>
bool U_UpdateValueByDifference(const T& oldValue, const T& newValue, T& valueToAdjust)
{
	if(newValue != oldValue)
	{
		valueToAdjust += newValue;
		valueToAdjust -= oldValue;
		return true;
	}
	return false;
}

template<class T>
bool U_IsOddNumberPrime(const T& number)
{
	for(T n = 3, q = number / n; q >= n; n += 2, q = number / n)
	{
		if(n * q == number)return false;
	}
	return true;
}

template<class T>
bool U_IsNumberPrime(const T& number)
{
	return (number & 1) && U_IsOddNumberPrime(number);
}

template<class T>
T U_GetNextPrimeNumber(T number)
{
	if(number < 3)return 3;

	if(!(number % 2))++number;

	for(; number > 1; number += 2)
	{
		if(U_IsOddNumberPrime(number))
		{
			return number;
		}
	}
	return 0;
}

template<class T>
void U_RoundUnsignedMonetaryValue(T& value, const T& denominator, const unsigned __int64& multiplier, bool up)
{
	if(!value.isZero())
	{
//		const __int64 multiplier = m_multiplier;//1000;
		const unsigned __int64 div = T::divider / multiplier;
		unsigned __int64 val = (unsigned __int64)value.GetDollars() * multiplier + (unsigned __int64)value.GetDollarFraction() / div;
		const unsigned __int64 den = (unsigned __int64)denominator.GetDollars() * multiplier + (unsigned __int64)denominator.GetDollarFraction() / div;
		if(den > 1)// || den < -1)
		{
			val /= den;
			val *= den;
		}
		const unsigned __int64 dollar = val / multiplier;
		T ret((T::DollarType)dollar, (T::FractionType)((val - dollar * multiplier) * div));
//		if(up != value.isNegative() && ret != value && (!ret.isZero() || value.isPositive() == (up ? (ret + denominator).isPositive() : (ret - denominator).isPositive())))
		if(up && ret != value)// && (!ret.isZero() || (up ? (ret + denominator).isPositive() : (ret - denominator).isPositive())))
		{
			ret += denominator;
		}
		value = ret;
	}
}

template<class T>
void U_RoundSignedMonetaryValue(T& value, const T& denominator, const __int64& multiplier, bool up)
{
	if(!value.isZero())
	{
//		const __int64 multiplier = m_multiplier;//1000;
		const __int64 div = T::divider / multiplier;
		__int64 val = (__int64)value.GetDollars() * multiplier + (__int64)value.GetDollarFraction() / div;
		const __int64 den = (__int64)denominator.GetDollars() * multiplier + (__int64)denominator.GetDollarFraction() / m_divider;
		if(den > 1 || den < -1)
		{
			val /= den;
			val *= den;
		}
		const __int64 dollar = val / multiplier;
		T ret((T::DollarType)dollar, (T::FractionType)((val - dollar * multiplier) * div));
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
	}
}

template<class DollarType, class FractionType>//both must be unsigned
void U_RoundUnsignedMonetaryFraction(DollarType& dollars, FractionType& fraction, unsigned char& decDigits, const unsigned char& maxDecDigits, const char& direction)
{
	if(decDigits > maxDecDigits)decDigits = maxDecDigits;
	else if(decDigits < maxDecDigits)
	{
		FractionType divider = U_GetDivider<FractionType>(maxDecDigits - decDigits);
		const FractionType fr = fraction;
		fraction /= divider;
		if(!direction && (fr - fraction * divider) << 1 >= divider || direction > 0 && fr > fraction * divider)
		{
			++fraction;
			divider = U_GetDivider<FractionType>(decDigits);
			if(fraction >= divider)
			{
				fraction -= divider;
				++dollars;
			}
		}
	}
}

template<> AFX_INLINE UINT AFXAPI HashKey<const Money&>(const Money& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//(key.GetDollars() << 16) | key.GetDollarFraction();
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<const Price&>(const Price& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}
////
template<> AFX_INLINE UINT AFXAPI HashKey<const SignedPrice&>(const SignedPrice& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<const MoneyQuantity&>(const MoneyQuantity& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//(key.GetDollars() << 16) | key.GetDollarFraction();
									// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<const PriceQuantity&>(const PriceQuantity& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//(key.GetDollars() << 16) | key.GetDollarFraction();
									// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<const AccountId&>(const AccountId& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<const FilterStringAsNumberArray&>(const FilterStringAsNumberArray& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

/*
template<> AFX_INLINE UINT AFXAPI HashKey<Money>(Money key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//(key.GetDollars() << 16) | key.GetDollarFraction();
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<Price>(Price key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<SignedPrice>(SignedPrice key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<Money&>(Money& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//(key.GetDollars() << 16) | key.GetDollarFraction();
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<Price&>(Price& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<SignedPrice&>(SignedPrice& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16);
	// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<MoneyQuantity>(MoneyQuantity key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//(key.GetDollars() << 16) | key.GetDollarFraction();
									// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<MoneyQuantity&>(MoneyQuantity& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//(key.GetDollars() << 16) | key.GetDollarFraction();
									// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<PriceQuantity>(PriceQuantity key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//(key.GetDollars() << 16) | key.GetDollarFraction();
									// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

template<> AFX_INLINE UINT AFXAPI HashKey<PriceQuantity&>(PriceQuantity& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//(key.GetDollars() << 16) | key.GetDollarFraction();
									// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}
*/

/*
template<> AFX_INLINE UINT AFXAPI HashKey<const std::string>(const std::string& key)
{
	return U_StringHash(key);
}

template<> AFX_INLINE UINT AFXAPI HashKey<std::string>(const std::string& key)
{
	return U_StringHash(key);
}
*/

#if (_MSC_VER > 1600)

template <class T>
struct TakionHashValue
{
	size_t operator()(const T &key) const
	{
		return key.GetHashValue() ^ _HASH_SEED; //std::hash<int>()(x.i) ^ std::hash<int>()(x.j) ^ std::hash<int>()(x.k);
	}
};

template<>
struct TakionHashValue<std::string>
{
	size_t operator()(const std::string &key) const
	{
		return U_StringHash(key) ^ _HASH_SEED; //std::hash<int>()(x.i) ^ std::hash<int>()(x.j) ^ std::hash<int>()(x.k);
	}
};

#else

template<> inline size_t std::hash_value(const AccountId& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashValue() ^ _HASH_SEED;//(((key.GetDollars() << 16) | key.GetDollarFraction()) ^ _HASH_SEED);
}

template<> inline size_t std::hash_value(const Money& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashValue() ^ _HASH_SEED;//(((key.GetDollars() << 16) | key.GetDollarFraction()) ^ _HASH_SEED);
}

template<> inline size_t std::hash_value(const Price& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashValue() ^ _HASH_SEED;//((((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16)) ^ _HASH_SEED);
}

template<> inline size_t std::hash_value(const MoneyQuantity& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashValue() ^ _HASH_SEED;//(((key.GetDollars() << 16) | key.GetDollarFraction()) ^ _HASH_SEED);
}

template<> inline size_t std::hash_value(const PriceQuantity& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashValue() ^ _HASH_SEED;//((((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16)) ^ _HASH_SEED);
}

template<> inline size_t std::hash_value(const SignedPrice& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashValue() ^ _HASH_SEED;//((((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16)) ^ _HASH_SEED);
}

template<> inline size_t std::hash_value(const PricePrecise& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashValue() ^ _HASH_SEED;//((((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16)) ^ _HASH_SEED);
}

template<> inline size_t std::hash_value(const SignedPricePrecise& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashValue() ^ _HASH_SEED;//((((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16)) ^ _HASH_SEED);
}

template<> inline size_t std::hash_value(const FilterStringAsNumberArray& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashValue() ^ _HASH_SEED;//((((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16)) ^ _HASH_SEED);
}

template<> inline size_t std::hash_value(const std::string& key)
{	// hash _Keyval to size_t value one-to-one
	return U_StringHash(key) ^ _HASH_SEED;//((((size_t)key.GetDollars() << 16) | (key.GetDollarFraction() >> 16)) ^ _HASH_SEED);
}

#endif

template <class T>
char* U_UnsignedMonetaryToBuffer(const T& price, char* num, unsigned int bufsize, unsigned char decDigits, bool comma, char del = '\0', unsigned char minDecDigits = 2)
{
	T::UnsignedFractionType fraction = price.GetTruncatedFraction(decDigits < minDecDigits ? minDecDigits : decDigits);

//	char* cursor = minDecDigits < decDigits ? U_UnsignedNumberToStrWithZeroTruncated(fraction, num, bufsize, decDigits, minDecDigits, del) : U_UnsignedNumberToStr(fraction, num, bufsize, 0, del);
	char* cursor = U_UnsignedNumberToStrWithZeroTruncated(fraction, num, bufsize, decDigits, minDecDigits, del);

	unsigned int bufsize1 = (unsigned int)(cursor - num);
	if(!bufsize1)return cursor;
	--cursor;
	*cursor = '.';
	--bufsize1;
//	if(!size1)return cursor;

	return comma ? U_UnsignedNumberToStrWithCommasNoTerm0(price.GetDollars(), num, bufsize1) : U_UnsignedNumberToStrNoTerm0(price.GetDollars(), num, bufsize1);
}

template <class T>
char* U_SignedMonetaryToBuffer(const T& money, char* num, unsigned int size, unsigned char decDigits, bool comma, char del, bool removeTrailingZeros)
{
	if(money.isNegative())
	{
		char* cursor = U_UnsignedMonetaryToBuffer(-money, num, size, decDigits, comma, del, removeTrailingZeros);
		if(cursor != num)
		{
			--cursor;
			*cursor = '-';
		}
		return cursor;
	}
	else
	{
		return U_UnsignedMonetaryToBuffer(money, num, size, decDigits, comma, del, removeTrailingZeros);
	}
}

#ifdef __cplusplus
extern "C"
{
#endif
//
char* WINAPI U_DollarFractionToStr(unsigned int fraction, unsigned char decDigits, char* cursor, bool truncate = true, char del = '\0');
void WINAPI U_DollarFractionToStdStr(unsigned int fraction, unsigned char decDigits, std::string& str, char del = '\0', bool removeTrailingZeros = false);
//void WINAPI U_CompactDollarFractionToStdStr(unsigned int fraction, unsigned char decDigits, std::string& str, char del = '\0', bool removeTrailingZeros = false);
void WINAPI U_MoneyFractionToStdStr(unsigned short fraction, unsigned char decDigits, std::string& str, char del, bool removeTrailingZeros = false);

void WINAPI U_CompactPriceToStr(std::string& str, unsigned int compactPrice, unsigned char decDigits, char roundDirection = '\0', bool comma = true, char del = '\0', bool removeTrailingZeros = false);
void WINAPI U_CompactSignedPriceToStr(std::string& str, int compactPrice, unsigned char decDigits, char roundDirection = '\0', bool comma = true, char del = '\0', bool removeTrailingZeros = false);
void WINAPI U_PriceToStr(std::string& str, const Price& price, unsigned char decDigits, char roundDirection = '\0', bool comma = true, char del = '\0', bool removeTrailingZeros = false);
void WINAPI U_SignedPriceToStr(std::string& str, const SignedPrice& price, unsigned char decDigits, char roundDirection = '\0', bool comma = true, char del = '\0', bool removeTrailingZeros = false);
void WINAPI U_MoneyToStr(std::string& str, const Money& money, unsigned char decDigits, char roundDirection = '\0', bool comma = true, char del = '\0', bool removeTrailingZeros = false);
void WINAPI U_PriceOrWholeDollarsToStr(std::string& str, const Price& price, unsigned char decDigits, char roundDirection, bool comma, char del, bool removeTrailingZeros);

void WINAPI U_PriceDollarsAndFractionToStr(std::string& str, unsigned int dollars, unsigned int fraction, unsigned char decDigits, char roundDirection = '\0', bool comma = true, char del = '\0', bool removeTrailingZeros = false);
void WINAPI U_SignedPriceDollarsAndFractionToStr(std::string& str, int dollars, int fraction, unsigned char decDigits, char roundDirection = '\0', bool comma = true, char del = '\0', bool removeTrailingZeros = false);
void WINAPI U_MoneyDollarsAndFractionToStr(std::string& str, __int64 dollars, short fraction, unsigned char decDigits, char roundDirection = '\0', bool comma = true, char del = '\0', bool removeTrailingZeros = false);

void WINAPI U_StrToPrice(Price& price, const char*& cursor, unsigned char decDigits, char del = '\0');
void WINAPI U_StrToSignedPrice(SignedPrice& price, const char*& cursor, unsigned char decDigits, char del = '\0');
void WINAPI U_StrToMoney(Money& money, const char*& cursor, unsigned char decDigits, char del = '\0');

void WINAPI U_StrToPriceDollarsAndFraction(unsigned int& dollars, unsigned int& fraction, const char*& cursor, unsigned char decDigits, char del = '\0');
void WINAPI U_StrToSignedPriceDollarsAndFraction(int& dollars, int& fraction, const char*& cursor, unsigned char decDigits, char del = '\0');
void WINAPI U_StrToMoneyDollarsAndFraction(__int64& dollars, short& fraction, const char*& cursor, unsigned char decDigits, char del = '\0');

void WINAPI U_StrToPriceDollarsAndFractionUpToLength(unsigned int& dollars, unsigned int& fraction, const char*& cursor, unsigned int& length, unsigned char decDigits, char del = '\0');
void WINAPI U_StrToSignedPriceDollarsAndFractionUpToLength(int& dollars, int& fraction, const char*& cursor, unsigned int& length, unsigned char decDigits, char del = '\0');
void WINAPI U_StrToMoneyDollarsAndFractionUpToLength(__int64& dollars, short& fraction, const char*& cursor, unsigned int& length, unsigned char decDigits, char del = '\0');

void WINAPI U_DoubleToPrice(Price& price, double value, unsigned char decDigits);
void WINAPI U_DoubleToSignedPrice(SignedPrice& price, double value, unsigned char decDigits);
void WINAPI U_DoubleToMoney(Money& money, double value, unsigned char decDigits);

double WINAPI U_PriceToDouble(const Price& price);
double WINAPI U_SignedPriceToDouble(const SignedPrice& price);
double WINAPI U_MoneyToDouble(const Money& money);

void WINAPI U_GetPriceByDifferencePercentage(Price& price, const Price& basePrice, const Price& otherPrice, const Price& otherBasePrice);
void WINAPI U_GetPriceByChangePercentage(Price& price, const Price& basePrice, const SignedPrice& change, const Price& otherBasePrice);
//

TakionRingVectorBase* WINAPI U_CreateTakionRingVector(size_t capacity, bool overwrite = true, bool keepLast = false);
TakionIterator* WINAPI U_CreateTakionRingVectorIterator(TakionRingVectorBase* ringVector);
RingVectorBaseItem* WINAPI U_GetNextTakionRingVectorItem(TakionIterator* iterator);
TakionIterator* WINAPI U_CreateReverseTakionRingVectorIterator(TakionRingVectorBase* ringVector);
RingVectorBaseItem* WINAPI U_GetNextReverseTakionRingVectorItem(TakionIterator* iterator);
/*
enum EcnBookId
{
	ECNBOOK_NSDQ = 1,
	ECNBOOK_ARCA,
	ECNBOOK_BATS,
	ECNBOOK_EDGA,
	ECNBOOK_EDGX,
	BOOK_LEVEL2,
	ECNBOOK_NQBX,
	ECNBOOK_CBSX,

	ECNBOOK_COUNT
};

void WINAPI U_ResetIterator(void* iterator);
void WINAPI U_DeleteIterator(void* iterator);
const Quote* WINAPI U_GetNextExpandedQuote(void* iterator);
const Quote* WINAPI U_GetNextAggregatedQuote(void* iterator);
const char* const* WINAPI U_GetEcnNames();
const char* WINAPI U_GetEcnName(unsigned char ecnId);
*/
void WINAPI U_CheckUtilsThread(unsigned int threadId, const char* text);

void WINAPI U_GetCrashDescription(std::string& crashDescription, const struct _EXCEPTION_RECORD* exceptionRecord);

char* WINAPI U_IntToStr(int n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');
char* WINAPI U_UIntToStr(unsigned int n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');
char* WINAPI U_UInt64ToStr(unsigned __int64 n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');
char* WINAPI U_Int64ToStr(__int64 n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');

char* WINAPI U_UIntToStrPad(unsigned int n, char* num, unsigned int size, unsigned int totalLength, bool removeTrailingZeros, char del = '\0');
//char* WINAPI U_UIntToStrWithDelimiter(unsigned int n, char* num, unsigned int size, char delimiter, unsigned char decDigits = 0);
char* WINAPI U_UIntHexToStr(unsigned int n, char* num, unsigned int size, const char del = '\0', const bool capitals = false, const unsigned char minLength = 0);
char* WINAPI U_UInt64HexToStr(unsigned __int64 n, char* num, unsigned int size, const char del = '\0', const bool capitals = false, const unsigned char minLength = 0);

char* WINAPI U_IntToStrWithCommas(int n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');
char* WINAPI U_UIntToStrWithCommas(unsigned int n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');
char* WINAPI U_Int64ToStrWithCommas(__int64 n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');
char* WINAPI U_UInt64ToStrWithCommas(unsigned __int64 n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');

char* WINAPI U_UIntToStrPrepended(unsigned int n, char* num, unsigned int size, char prepend, char del = '\0');
char* WINAPI U_UInt64ToStrPrepended(unsigned __int64 n, char* num, unsigned int size, char prepend, char del = '\0');
char* WINAPI U_UIntHexToStrPrepended(unsigned int n, char* num, unsigned int size, char prepend, const char del = '\0', const bool capitals = false);
char* WINAPI U_UInt64HexToStrPrepended(unsigned __int64 n, char* num, unsigned int size, char prepend, const char del = '\0', const bool capitals = false);

char* WINAPI U_UShortToStr(unsigned short n, char* num, unsigned int size, char del = '\0');
char* WINAPI U_UShortHexToStr(unsigned short n, char* num, unsigned int size, const char del = '\0', const bool capitals = false, const unsigned char minLength = 0);
char* WINAPI U_ShortToStr(short n, char* num, unsigned int size, char del = '\0');
char* WINAPI U_UShortToStrWithCommas(unsigned short n, char* num, unsigned int size, unsigned char decDigits = 0, char del = '\0');

char* WINAPI U_UCharToStr(unsigned char n, char* num, unsigned int size, char del = '\0');
char* WINAPI U_UCharHexToStr(unsigned char n, char* num, unsigned int size, const char del = '\0', const bool capitals = false, const unsigned char minLength = 0);
char* WINAPI U_CharAsIntToStr(char n, char* num, unsigned int size, char del = '\0');

unsigned int WINAPI U_GetTimeTokensFromMillisecond(unsigned int currentMillisecond, unsigned int& hour, unsigned int& minute, unsigned int& second);
unsigned int WINAPI U_GetHourAndMinuteFromMillisecond(unsigned int currentMillisecond, unsigned int& hour);//returns minute
unsigned int WINAPI U_GetTimeDigitTokensFromMillisecond(unsigned int currentMillisecond, unsigned char& hour1, unsigned char& hour2, unsigned char& minute1, unsigned char& minute2, unsigned char& second1, unsigned char& second2);
char* WINAPI U_FormatMillisecond(unsigned int millisecond, char* cursor, unsigned int buflen, char del = '\0', bool appendMillisecond = true, char timeSeparator = ':', char millisecondSeparator = '-');
char* WINAPI U_FormatSecond(unsigned int second, char* cursor, unsigned int buflen, char del = '\0', char separator = ':');
char* WINAPI U_FormatTimeTokens(unsigned int hour, unsigned int minute, unsigned int second, char* cursor, unsigned int buflen, char del = '\0', const char separator = ':');
char* WINAPI U_FormatTimeTokensAndMillisecond(unsigned int hour, unsigned int minute, unsigned int second, unsigned int millisecond, char* cursor, unsigned int buflen, char del = '\0', char timeSeparator = ':', char millisecondSeparator = '-');
char* WINAPI U_FormatMinute(unsigned short minute, char* cursor, unsigned int buflen, char del = '\0', char separator = ':');
void WINAPI U_FormatDateAndTime(std::string& str, unsigned short year, unsigned char month, unsigned char day, unsigned int millisecond, bool appendMillisecond, bool monthName, bool fullYear, char dateTimeSeparator = ' ', char dateSeparator = '-', char timeSeparator = ':', char millisecondSeparator = '-', char del = '\0');
unsigned short WINAPI U_StringToMinute(const char*& cursor, char del, const char separator = ':');
unsigned int WINAPI U_StringToMillisecond(const char*& cursor, char del, const char separator = ':', const char millisecondSeparator = '-');

const char* WINAPI U_GetMonthName(unsigned short month);
void WINAPI U_GetDateTokens(unsigned int date, unsigned short& year, unsigned short& month, unsigned short& day);
unsigned int WINAPI U_CombineTokensIntoDate(unsigned short year, unsigned short month, unsigned short day);
char* WINAPI U_FormatDate(unsigned int date, char* cursor, unsigned int buflen, char tokenDel, char del, bool monthName, bool fullYear);
void WINAPI U_FormatDateStr(unsigned int date, std::string& str, char tokenDel, char del, bool monthName, bool fullYear);

char* WINAPI U_FormatDateTokens(unsigned short month, unsigned short day, unsigned short year, char* cursor, unsigned int buflen, char tokenDel, char del, bool monthName, bool fullYear);
void WINAPI U_FormatDateTokensStr(unsigned short month, unsigned short day, unsigned short year, std::string& str, char tokenDel, char del, bool monthName, bool fullYear);
bool WINAPI U_ReadDateTokensFromStr(const char*& cursor, char delimiter, char tokenDel, unsigned short& year, unsigned short& month, unsigned short& day, bool fullYear = true);
bool WINAPI U_ReadTimeTokensFromStr(const char*& cursor, unsigned short& hour, unsigned short& minute, unsigned short& second, unsigned short& millisecond, char delimiter, char tokenDel = ':', char millisecondDel = '-');
unsigned int WINAPI U_ReadShiftFormatDateFromStr(const char*& str, char del, char tokenDel, unsigned int defaultValue, bool fullYear);

void WINAPI U_GetDateTimeTokensDateOnly(unsigned int date, unsigned short& year, unsigned char& month, unsigned char& day);
void WINAPI U_GetDateTimeTokensTimeOnly(unsigned int time, unsigned char& hour, unsigned char& minute, unsigned char& second, unsigned short& millisecond);
void WINAPI U_GetDateTimeTokens(unsigned __int64 dateTime, unsigned short& year, unsigned char& month, unsigned char& day, unsigned char& hour, unsigned char& minute, unsigned char& second, unsigned short& millisecond);
unsigned int WINAPI U_ConvertDateTokensToDateInFullShiftFormat(unsigned short year, unsigned char month, unsigned char day);//((unsigned int)year << 16) | ((unsigned int)(month) << 8) | (unsigned int)day;
unsigned int WINAPI U_ConvertDateTokensToDateInShiftFormat(unsigned short year, unsigned char month, unsigned char day);//((unsigned int)year << 9) | ((unsigned int)(month) << 5) | (unsigned int)day;
unsigned int WINAPI U_ConvertTimeTokensToTimeInShiftFormat(unsigned char hour, unsigned char minute, unsigned char second, unsigned short millisecond);
unsigned __int64 WINAPI U_ConvertDateTimeTokensToDate(unsigned short year, unsigned char month, unsigned char day, unsigned char hour, unsigned char minute, unsigned char second, unsigned short millisecond);
void WINAPI U_AppendDateTime(std::string& str, const unsigned __int64& dateTime, bool timeOnly, bool appendMillisecond, char tokenDel, char del, bool oneDigitLeftmost, bool monthName, bool fullYear);
void WINAPI U_AppendThreeCharDateToStr(std::string& text, const unsigned int& date, char tokenDel, char del, bool monthName, bool fullYear);
void WINAPI U_AppendThreeCharDateFullYearToStr(std::string& text, const unsigned int& date, char tokenDel, char del, bool monthName, bool fullYear);
char* WINAPI U_AppendThreeCharDateFullYearToBuf(char* cursor, unsigned int buflen, const unsigned int& date, char tokenDel, char del, bool monthName, bool fullYear);

void WINAPI U_AppendDateInShiftFormatToStr(std::string& str, const unsigned int& date, char tokenDel, char del, bool monthName, bool fullYear);
void WINAPI U_AppendDateInShiftFormatFullYearToStr(std::string& str, const unsigned int& date, char tokenDel, char del, bool monthName, bool fullYear);
char* WINAPI U_AppendDateInShiftFormatFullYearToBuf(char* cursor, unsigned int buflen, const unsigned int& date, char tokenDel, char del, bool monthName, bool fullYear);

unsigned int WINAPI U_ConvertShiftDateToUIntYYMMDD(unsigned int date);
unsigned int WINAPI U_ConvertUIntYYMMDDtoShiftDate(unsigned int yymmdd);

unsigned int WINAPI U_ConvertStringDateToUInt(const char* cursor);//"Oct 29 2020" year << 9 | month << 5 | day;
unsigned int WINAPI U_ConvertStringTimeToUInt(const char* cursor);//"16:35:34" hour << 22 | minute << 16 | second << 10;
unsigned __int64 WINAPI U_ConvertStringDateTimeToUInt64(const char* cursorDate, const char* cursorTime);//date << 32 | time

int WINAPI U_GetLogPixelsY();

void WINAPI U_CalculateMaxDelay(unsigned int sentTime, unsigned int receivedTime, short& delay);

const OSVERSIONINFOEX& WINAPI U_GetOsVersionInfo();
const SYSTEM_INFO& WINAPI U_GetSystemInfo();
void WINAPI U_GetSystemInfoAsString(std::string& info);
void WINAPI U_GetOsVersionStr(std::string& os);
void WINAPI U_GetServicePackVersionStr(std::string& os);
void WINAPI U_GetProcessorArchitectureStr(std::string& info);
unsigned int WINAPI U_GetMemoryPageSize();
unsigned int WINAPI U_GetMemoryAllocationGranularity();
unsigned __int64 WINAPI U_GetPhysicalMemorySize();
unsigned int WINAPI U_GetProcessorCount();
void WINAPI U_GetActiveProcessorMask(std::string& info);

void WINAPI U_ReplaceSubstring(const char* original, const char* what, const char* with, std::string& result);

enum ClipboardError : unsigned char
{
	CLIPBOARD_OK,
	CLIPBOARD_CLOSE,
	CLIPBOARD_SETDATA,
	CLIPBOARD_EMPTY,
	CLIPBOARD_OPEN,
	CLIPBOARD_MEMORY,

	CLIPBOARD_COUNT
};

unsigned int WINAPI U_CopyStringVectorToClipboard(const std::vector<std::string>& strings, HWND owner, unsigned char* errorCode = nullptr);
unsigned int WINAPI U_CopyStringToClipboard(const std::string& info, HWND owner, unsigned char* errorCode = nullptr);
unsigned int WINAPI U_CopyStringBufferToClipboard(const char* info, HWND owner, unsigned int infoLength = 0, unsigned char* errorCode = nullptr);
unsigned int WINAPI U_CopyClipboardToString(std::string& str, HWND owner, unsigned char* errorCode = nullptr);
unsigned int WINAPI U_CopyClipboardToStringList(std::list<std::string>& stringList, HWND owner, unsigned int* emptyCount = nullptr, unsigned char* errorCode = nullptr, bool emptyIsValid = false);
unsigned int WINAPI U_CopyClipboardToStringMap(std::map<std::string, std::string>& stringMap, HWND owner, char delimiter, unsigned int* duplicateCount = nullptr, unsigned int* emptyCount = nullptr, unsigned char* errorCode = nullptr, bool emptyIsValid = false);
unsigned int WINAPI U_CopyClipboardToStringMapWithAnyDelimiter(std::map<std::string, std::string>& stringMap, HWND owner, unsigned int* duplicateCount = nullptr, unsigned int* emptyCount = nullptr, unsigned char* errorCode = nullptr, bool emptyIsValid = false);
void WINAPI U_ParseStringToMap(const char* cursor, size_t size, std::map<std::string, std::string>& stringMap, char delimiter, unsigned int* duplicateCount, unsigned int* emptyCount, bool emptyIsValid = false);
void WINAPI U_ParseStringToMapWithAnyDelimiter(const char* cursor, size_t size, std::map<std::string, std::string>& stringMap, unsigned int* duplicateCount, unsigned int* emptyCount, bool emptyIsValid = false);
void WINAPI U_ParseStringToList(const char* cursor, size_t size, std::list<std::string>& stringList, unsigned int* emptyCount, bool emptyIsValid = false);
bool WINAPI U_FileExists(const char* filePath);
bool WINAPI U_ReadFileToStringMap(const char* filePath, std::map<std::string, std::string>& stringMap, char delimiter, char commentChar, bool keyUpperCase, unsigned int* duplicateCount, unsigned int* emptyCount, bool emptyIsValid = false);

unsigned char WINAPI U_CopyClipboardToStringAndGetError(std::string& str, HWND owner, std::string* errorName = nullptr, std::string* errorDescription = nullptr);
unsigned int WINAPI U_CopyClipboardToStringListAndGetError(std::list<std::string>& stringList, HWND owner, std::string* errorName = nullptr, std::string* errorDescription = nullptr);
unsigned int WINAPI U_CopyClipboardToStringMapAndGetError(std::map<std::string, std::string>& stringMap, HWND owner, char delimiter, unsigned int* duplicateCount = nullptr, std::string* errorName = nullptr, std::string* errorDescription = nullptr);
unsigned char WINAPI U_CopyStringToClipboardAndGetError(const std::string& info, HWND owner, std::string* errorName = nullptr, std::string* errorDescription = nullptr);

char WINAPI U_GetStringLastChar(const char* str);

//COLORREF WINAPI U_GetOppositeBlacAndWhiteColor(COLORREF color);

void WINAPI U_ConvertValueToPrintableString(const BYTE* cursor, unsigned int length, std::string& result);
BYTE* WINAPI U_RestoreValueFromPrintable(const char* cursor, DWORD& length);

bool WINAPI U_EncryptString(bool useIp, const char* traderId, const std::string& text, std::string& encryptedText, std::string& errorMessage, std::string& errorTitle);
bool WINAPI U_DecryptString(bool useIp, const char* traderId, const std::string& encryptedText, std::string& text, std::string& errorMessage, std::string& errorTitle);
/*
short WINAPI U_CompareUIntStrs(unsigned int str1, unsigned int str2);
short WINAPI U_CompareUInt64Strs(unsigned __int64 str1, unsigned __int64 str2);

unsigned int WINAPI U_GetUIntStrLength(unsigned int str);
unsigned int WINAPI U_GetUInt64StrLength(unsigned __int64 str);
*/
#if (_MSC_VER > 1600)
typedef std::unordered_map<std::string, std::string> StringHashMap;
#else
typedef std::hash_map<std::string, std::string> StringHashMap;
#endif

const char* WINAPI U_GetArgLine();
const StringHashMap& WINAPI U_GetLineArgs();
void WINAPI U_Initialize(unsigned __int64 exeVersion, const char* argLine);
unsigned __int64 WINAPI U_GetExeVersion();

bool WINAPI U_PatternMatch(const char *str, const char *pattern);
bool WINAPI U_HasWildCards(const char *str);
void WINAPI U_BreakStringIntoTokensBy2Chars(const char* originalString, const char c1, const char c2, std::list<std::string>& tokenList);//c1 + c2
void WINAPI U_CombineTokensIntoString(const char* insertion, const std::list<std::string>& tokenList, std::string& result);
void WINAPI U_BreakStringIntoTokens(const char* cursor, const char c1, std::list<std::string>& tokenList);//c1 + any char but c1

unsigned int WINAPI U_FindCharPosInLine(HDC dc, const unsigned int x, const std::string& text, unsigned int& posX);//returns char position at pixel x
void WINAPI U_TextBreakLines(const std::string& text, std::vector<std::string>& result);

unsigned int WINAPI U_TextBreakWords(HDC dc,
	const unsigned int width,
	const std::string& text,
	std::vector<std::string>& result,
	unsigned int& maxWidth,
	unsigned int& maxBreakWidth,
	unsigned int spaceWidth = 0,
	unsigned int tabWidth = 0,
	unsigned int lineFeedWidth = 0);

unsigned int WINAPI U_TextBreakIntoWords(const std::string& text, std::vector<std::string>& result);
unsigned int WINAPI U_StringBreakIntoWords(const char* cursor, unsigned int length, std::vector<std::string>& result);

const char* WINAPI U_StringEndsWith(const char* str, const char* endsWith);
const char* WINAPI U_StringStartsWith(const char* str, const char* startsWith);
const char* WINAPI U_StringStartsWithUpToLength(const char* str, unsigned int& length, const char* startsWith);
const char* WINAPI U_StringStartsWithPlusChar(const char* str, const char* startsWith, const char additionalChar);

bool WINAPI U_ReadFileToString(const char* filePath, std::string& str);
bool WINAPI U_WriteStringToFile(const char* filePath, const std::string& str);

char WINAPI U_CompareText(const char* const text1, const char* const text2);//-1 if text1 < text2; 0 if text1 == text2; +1 if text1 > text2;
bool WINAPI U_IsTextDifferent(const char* const text1, const char* const text2);
bool WINAPI U_ReplaceText(char*& what, const char* const with);

char WINAPI U_CompareTextCaseInsensitive(const char* const text1, const char* const text2);//-1 if text1 < text2; 0 if text1 == text2; +1 if text1 > text2;
bool WINAPI U_IsTextDifferentCaseInsensitive(const char* const text1, const char* const text2);

const char* WINAPI U_StriStr(const char* str, const char* substr);//substr must be uppercase
const char* WINAPI U_StriStrUpToLength(const char* str, unsigned int length, const char* substr);//substr must be uppercase
const char* WINAPI U_StriStrFromBack(const char* str, unsigned int length, const char* substr);//substr must be uppercase

const char* WINAPI U_StrStr(const char* str, const char* substr);
const char* WINAPI U_StrStrUpToLength(const char* str, unsigned int length, const char* substr);
const char* WINAPI U_StrStrFromBack(const char* str, unsigned int length, const char* substr);

const char* WINAPI U_StriStrEnd(const char* str, const char* substr);//substr must be uppercase
const char* WINAPI U_StriStrEndUpToLength(const char* str, unsigned int& length, const char* substr);//substr must be uppercase

const char* WINAPI U_StrStrEnd(const char* str, const char* substr);
const char* WINAPI U_StrStrEndUpToLength(const char* str, unsigned int& length, const char* substr);

void WINAPI U_GetProcessesWithName(const char* exeFileName, std::map<DWORD, std::string>& processMap);
unsigned char WINAPI U_GetProcessPath(DWORD processId, std::string& path);

unsigned int WINAPI U_GetProcessIntegrityLevel(DWORD processId, std::string& integrityLevelStr);

unsigned int WINAPI U_CalculateControlSum(const char* cursor, unsigned int length);

void WINAPI U_EnumFontFamiliesByNumberArray(HDC hdc, BYTE charSet, std::map<FilterStringAsNumberArray, DWORD>& fontMap);

unsigned int WINAPI U_GetIpFromDns(const char* dns, std::string* errorStr = nullptr);

bool WINAPI U_BackupFile(const char* filePath, const char* suffix, std::string& backupFilePath, std::string* errorStr);

enum ParseFixError : unsigned char
{
	PFE_OK,
	PFE_TAG_NUMBER_TOO_BIG,
	PFE_TAG_NON_NUMERIC,
	PFE_NO_VALUE,
	PFE_INVALID_VALUE,
	PFE_DUPLICATE_TAG,
	PFE_NO_TAG,
	PFE_MISSING_TAG,

	PFE_Count
};

unsigned char WINAPI U_ParseFix(
#if (_MSC_VER > 1600)
	std::unordered_map<unsigned short, std::string>& fixMap,
#else
	std::hash_map<unsigned short, std::string>& fixMap,
#endif
	const char* cursor, unsigned int length, unsigned short& errorKey, unsigned short& errorOrdinal);

bool WINAPI U_ParseFixUtc(const char* cursor, unsigned int& year, unsigned int& month, unsigned int& day, unsigned int& hour, unsigned int& minute, unsigned int& second, unsigned int& millisecond);

enum FixRejectReason : unsigned char
{
	FRR_INVALID_TAG_NUMBER,
	FRR_REQUIRED_TAG_MISSING,
	FRR_TAG_NOT_DEFINED_FOR_THIS_MESSAGE_TYPE,
	FRR_UNDEFINED_TAG,
	FRR_TAG_SPECIFIED_WITHOUT_VALUE,
	FRR_VALUE_INCORRECT_FOR_THIS_TAG,
	FRR_INCORRECT_DATA_FORMAT_FOR_VALUE,
	FRR_DECRIPTION_PROBLEM,
	FRR_SIGNATURE_PROBLEM,
	FRR_COMPID_PROBLEM,
	FRR_SENDING_TIME_ACCURACY_PROBLEM,
	FRR_INVALID_MSG_TYPE,
	FRR_XML_VALIDATION_ERROR,
	FRR_DUPLICATE_TAG,
	FRR_TAG_OUT_OF_ORDER,
	FRR_REPEATING_GROUP_FIELDS_OUT_OF_ORDER,
	FRR_INCORRECT_NumInGroup_COUNT_FOR_REPEATING_GROUP,
	FRR_NON_DATA_VALUE_INCLUDES_SOH,

	FRR_Count,

	FRR_OTHER = 99
};

const char* WINAPI U_GetParseFixErrorDescription(const unsigned char errorCode, unsigned char& fixRejectReason);

void WINAPI U_AppendFixMessageContents(std::string& info, const char* fixSrc, unsigned short fixLength, const char* prefix = nullptr, const char del = '|');

bool WINAPI U_AppendSohIfNecessary(std::string& text);//appends SOH if the std::string is not empty and if the last char is not SOH; returns true if appended SOH;

enum TakionFixError : unsigned char
{
	TFE_OK,
	TFE_BEGIN,
	TFE_LENGTH,
	TFE_TYPE,
	TFE_END,
	TFE_CONTROL_SUM,

	TFE_Count
};

unsigned char WINAPI U_CheckFixIntegrity(const char* partialMessageStart,
	const unsigned int& partialMessageLength,
	const char*& additionalMessageInfo,
	unsigned int& additionalMessageLength,
	unsigned int& charCount,
	unsigned __int64& fixProtocol,
	unsigned int& fixVersion,
	unsigned short& fixVersionNameOffset,
	unsigned short& fixProtocolOffset,
	unsigned short& fixVersionOffset,
	unsigned short& msgLength,
	unsigned short& msgLengthNameOffset,
	unsigned short& msgLengthOffset,
	unsigned short& fixType,
	unsigned short& fixTypeNameOffset,
	unsigned short& fixTypeOffset,
	unsigned short& controlSum,
	unsigned short& controlSumNameOffset,
	unsigned short& controlSumOffset,
	bool& fixMessageReady,
	char& lastChar,
	char& prevChar);

bool WINAPI U_TruncateStringDownToLengthAndDelimiter(std::string& str,
	const unsigned int stringLengthLimit,
	const unsigned int startTruncatingOverLimit,
	const char delimiter,
	const char delimiter2);

#ifdef __cplusplus
}
#endif
/*Use lessUIntAsStr
struct lessUIntStr : public std::binary_function<unsigned int, unsigned int, bool>
{
	bool operator()(const unsigned int& p1, const unsigned int& p2) const
	{
		return U_CompareUnsignedNumberStrs(p1, p2) < 0;
	}
};

struct lessUInt64Str : public std::binary_function<unsigned __int64, unsigned __int64, bool>
{
	bool operator()(const unsigned int& p1, const unsigned int& p2) const
	{
		return U_CompareUnsignedNumberStrs(p1, p2) < 0;
	}
};
*/

class StrBuffer
{
public:
	StrBuffer():
		m_string(nullptr),
		m_own(false)
	{
	}
	StrBuffer(const char* const& str, const unsigned char& own)://0 - does not own; 1 - do not create, only delete; 2 - create and delete.
		m_string(nullptr),
		m_own(own != 0)
	{
		if(str && *str)
		{
			if(own > 1)
			{
				U_ReplaceText(m_string, str);
			}
			else
			{
				m_string = (char*)str;
			}
		}
	}
	StrBuffer(const std::string& str):
		m_string(nullptr),//str.empty() ? nullptr : new char[str.length() + 1]),
		m_own(!str.empty())
	{
		if(m_own)
		{
			U_ReplaceText(m_string, str.c_str());
		}
	}
	void SetBuffer(const std::string& str)
	{
		if(!str.empty())
		{
			if(m_own)
			{
				U_ReplaceText(m_string, str.c_str());
			}
			else
			{
				m_string = nullptr;
				U_ReplaceText(m_string, str.c_str());
				m_own = true;
			}
		}
		else
		{
			U_ReplaceText(m_string, nullptr);
			m_own = false;
		}
	}
	StrBuffer(const StrBuffer& other):
		m_string(nullptr),
		m_own(other.m_own)
	{
		if(m_own)
		{
			U_ReplaceText(m_string, other.m_string);
		}
		else
		{
			m_string = other.m_string;
		}
	}
	~StrBuffer()
	{
		if(m_own)
		{
			U_ReplaceText(m_string, nullptr);
		}
	}
	void SetBuffer(const char* const& str, const unsigned char& own)
	{
		if(str && *str)
		{
			if(m_own)
			{
				if(own > 1)
				{
					U_ReplaceText(m_string, str);
				}
				else
				{
					U_ReplaceText(m_string, nullptr);
					m_string = (char*)str;
					m_own = own != 0;
				}
			}
			else
			{
				if(own > 1)
				{
					m_string = nullptr;
					U_ReplaceText(m_string, str);
					m_own = true;
				}
				else
				{
					m_string = (char*)str;
					m_own = own != 0;
				}
			}
		}
		else
		{
			U_ReplaceText(m_string, nullptr);
			m_own = own != 0;
		}
	}
	StrBuffer& operator=(const StrBuffer& other)
	{
		SetBuffer(other.m_string, other.m_own ? 2 : 0);
	}
	const char* const& GetStr() const{return m_string;}
protected:
	char* m_string;
	bool m_own;
};

class U_API WsaCollection
{
public:
	WsaCollection(const unsigned short& maxCount);
	virtual ~WsaCollection();
	const unsigned short& GetMaxCount() const{return m_maxCount;}
	const unsigned short& GetCount() const{return m_count;}
	const unsigned int& GetTotalLength() const{return m_totalLength;}

#if (_MSC_VER > 1600)
	typedef std::unordered_set<const char*> CharPtrSet;
#else
	typedef std::hash_set<const char*> CharPtrSet;
#endif
	const WSABUF* const& GetWsaBuf() const{return m_wsaBuf;}
	const WSABUF* GetWsaBufAt(const unsigned short& at) const{return at < m_count ? m_wsaBuf + at : nullptr;}

	unsigned short Append(const char* buf, unsigned int len, const char* additionalChar, unsigned char own);
	virtual bool SetTagAt(unsigned int at, const char* buf, unsigned int len, const char* additionalChar, unsigned char own);
//protected:
	virtual void Reset();
	static unsigned int CalculateItemControlSum(const WSABUF* const& wsaBuf)
	{
		unsigned int controlSum = 0;
		unsigned int length = wsaBuf->len;
		for(const char* cursor = wsaBuf->buf; length; --length, ++cursor)
		{
			controlSum += *cursor;
		}
		return controlSum;
	}
	unsigned int CalculateControlSumAt(const unsigned short& at) const
	{
		return at < m_count ? CalculateItemControlSum(m_wsaBuf + at) : 0;
	}
	unsigned int CalculateControlSum() const
	{
		unsigned int controlSum = 0;
		const WSABUF* wsaBuf = m_wsaBuf;
		for(unsigned short i = 0; i < m_count; ++i, ++wsaBuf)
		{
			controlSum += CalculateItemControlSum(wsaBuf);
		}
		return controlSum;
	}
protected:
//private:
	unsigned short m_maxCount;
	unsigned short m_count;
	unsigned int m_totalLength;
	WSABUF* m_wsaBuf;
	bool AllocateMore();
private:
	void DestroyOwn();
	void ClearWSABUF();
	CharPtrSet m_toDelete;
	CharPtrSet::const_iterator m_toDeleteEnd;
};

/*
#define U_FIX_STR(value) #value
#define U_FIX_STRINGIZE(value) U_FIX_STR(value)

#define U_FIX_TAG_STR(X) U_FIX_STRINGIZE(X=)
*/
class U_API FixTagCollection : public WsaCollection
{
public:
	static const char* const sohStr;
	static const unsigned short maxMsgLength = 65000;
	FixTagCollection(const unsigned short& maxCount = 50, const unsigned int& fixVersion = (4 << 8) | 2, const char* fixProtocol = "FIX");//fixProtocol will not accept more than 7 chars, usually should be "FIX"; fixVersion 4.2 can be passed as (4 << 8) | 2
	virtual ~FixTagCollection();
	const unsigned __int64& GetFixProtocolNum() const{return m_fixProtocol;}
	const char* GetFixProtocol() const{return (const char*)&m_fixProtocol;}
	const unsigned int& GetFixVersion() const{return m_fixVersion;}
	const unsigned int& GetMessageLength() const{return m_messageLength;}
	const unsigned int& GetControlSum() const{return m_controlSum;}

	unsigned short Append(const char* tagNameAndValue, unsigned int len = 0, bool appendSoh = true, unsigned char own = 0);
	unsigned short AppendTag(const char* tagNameIncludingEqual, const char* tagValue, unsigned int lenName = 0, unsigned int lenValue = 0, unsigned char own = 0, bool appendSoh = true);//Do not append the last tag 10. Call Finalize() to fix tags 9 and 10. //own = 0 - use the original; own = 1 - use the original and delete it when resetting; own = 2 - use a copy and delete it when resetting
	unsigned short AppendUInt64Tag(const char* tagNameIncludingEqual, unsigned __int64 tagValue, unsigned int lenName = 0);
	unsigned short AppendUIntTag(const char* tagNameIncludingEqual, unsigned int tagValue, unsigned int lenName = 0);
	unsigned short AppendUIntTagAsString(const char* tagNameIncludingEqual, unsigned int tagValue, unsigned int lenName = 0);
	unsigned short AppendUShortTagAsString(const char* tagNameIncludingEqual, unsigned short tagValue, unsigned int lenName = 0);

	virtual bool SetTagAt(unsigned int at, const char* tagValue, unsigned int lenValue, const char* additionalChar, unsigned char own);//own = 0 - use the original; own = 1 - use the original and delete it when resetting; own = 2 - use a copy and delete it when resetting

	unsigned short AppendMsgSeqNumValue(unsigned int msgSeqNum);
	bool UpdateMsgSeqNumValue(unsigned int msgSeqNum);

	unsigned short AppendTagTestReqId(const char* testReqId = nullptr, unsigned int lenValue = 0, unsigned char own = 0);
	bool UpdateTagTestReqId(const char* testReqId, unsigned int lenValue = 0, unsigned char own = 0);

	unsigned short AppendTagTargetCompId(const char* targetCompId = nullptr, unsigned int lenValue = 0, unsigned char own = 0);
	bool UpdateTagTargetCompId(const char* targetCompId, unsigned int lenValue = 0, unsigned char own = 0);

	unsigned short AppendTagSenderCompId(const char* senderCompId = nullptr, unsigned int lenValue = 0, unsigned char own = 0);
	bool UpdateTagSenderCompId(const char* senderCompId, unsigned int lenValue = 0, unsigned char own = 0);

	unsigned short AppendTagUtc(unsigned short month = 0, unsigned short day = 0, unsigned short year = 0, unsigned int millisecond = 0xFFFFFFFF);
	unsigned short AppendTagUtc(const char* date, unsigned int millisecond);
	bool UpdateTagUtcTime(unsigned int millisecond);
	bool UpdateTagUtcDate(unsigned short month, unsigned short day, unsigned short year);
	bool UpdateTagUtcDate(const char* date);

	const bool& isFinalized() const{return m_finalized;}

	const unsigned int& GetMsgSeqNum() const{return m_msgSeqNum;}
	const unsigned short& GetTagMsgSeqNumOrdinal() const{return m_tagMsgSeqNumOrdinal;}
	const WSABUF* GetTagMsgSeqNum() const{return m_tagMsgSeqNumOrdinal ? GetWsaBufAt(m_tagMsgSeqNumOrdinal) : nullptr;}
	const char* GetTagMsgSeqNumValue() const
	{
		if(m_tagMsgSeqNumOrdinal)
		{
			const WSABUF* wsaBuf = GetWsaBufAt(m_tagMsgSeqNumOrdinal);
			return wsaBuf ? wsaBuf->buf : nullptr;
		}
		return nullptr;
	}

	virtual void Reset();
	bool Finalize(char type1, char type2);//"A" = 'A','\0'; "AB" = 'A', 'B';

	bool Finalize(const unsigned short& type){return Finalize((char)(type & 0xFF), (char)(type >> 8));}

	bool Finalize(const char* type){return Finalize(*(unsigned short*)type);}//2 chars at most

	void toString(std::string& str, const char* tagDelimiter) const
	{
		const WSABUF* cursor = m_wsaBuf;
		char c;
		unsigned int j;
		const char* cur;
		for(unsigned short i = m_count; i; --i, ++cursor)
		{
			cur = cursor->buf;
			if(cur)
			{
				for(c = *cur, j = cursor->len; j; --j, c = *++cur)
				{
					if(c == fix_soh)
					{
						if(tagDelimiter)str += tagDelimiter;
					}
					else str += c;
				}
			}
		}
	}
protected:
	unsigned short DoAppendTagUtc();
private:
	unsigned __int64 m_fixProtocol;
	unsigned int m_fixVersion;
	unsigned int m_messageLength;
	unsigned int m_controlSum;
	unsigned int m_versionAndLengthTitleControlSum;
	unsigned int m_lengthVersionAndLengthTitle;
	unsigned int m_lengthTypeTitleAndValue;

	char* m_tagVersionAndLengthTitle;
	char m_tagLengthValue[5];
	char m_tagTypeTitleAndValue[7];
	char m_tagControlSumTitleAndValue[7];

	char m_tagMsgSeqNumValue[11];
	unsigned short m_tagMsgSeqNumOrdinal;

	unsigned short m_tagTargetCompIdOrdinal;

	unsigned short m_tagSenderCompIdOrdinal;

	unsigned short m_tagTestReqIdOrdinal;

	char m_tagUtc[25];
	unsigned short m_tagUtcOrdinal;

	unsigned int m_msgSeqNum;

	bool m_finalized;
};

////////////////////
/*
class TMsgExitMessageThread : public Message
{
public:
	TMsgExitMessageThread():Message(0, sizeof(TMsgExitMessageThread)){}
};
*/
class U_API TakionThreadBase
{
public:
	virtual ~TakionThreadBase(){}
	DWORD Start() const{return ResumeThread(m_threadHandle);}
	DWORD Suspend() const{return SuspendThread(m_threadHandle);}
	HANDLE GetThreadHandle() const{return m_threadHandle;}
	const unsigned int& GetThreadId() const{return m_threadId;}

	const bool& isDataOk() const{return m_dataOk;}
	const std::string& GetName() const{return m_name;}
	const int& GetPriority() const{return m_priority;}

	virtual void ThreadInfoToString(std::string& info) const
	{
		info += m_name;
	}
	void LogThreadInfo(const char* prefix) const
	{
		std::string info;
		ThreadInfoToString(info);
		Log(info.c_str(), prefix);
	//	takionUtils.Log(info.c_str(), prefix);
	}
	virtual void Log(const char* info, const char* prefix) const{}
protected:
	TakionThreadBase(const char* name, int priority = 0, unsigned int waitToTerminate = INFINITE, unsigned int padSize = 0);
	virtual void OnThreadFunctionStarted(){}
	virtual void OnThreadFunctionExiting(unsigned int code){}
	virtual bool InvalidateData()
	{
		if(m_dataOk)
		{
			m_dataOk = false;
			return true;
		}
		return false;
	}

	virtual bool DoIdle(unsigned int idleCount){return false;}

	void FlushIdle(){for(unsigned int idleCount = 0; DoIdle(idleCount); ++idleCount);}

	HANDLE m_threadHandle;
	unsigned int m_threadId;
//	HANDLE m_threadReadyEvent;
	int m_priority;
	unsigned int m_waitToTerminate;
	bool m_dataOk;
	std::string m_name;
};

//class RingBufferListEventNotification;

class U_API ThreadNotifyIpChangeBase : public TakionThreadBase
{
friend unsigned int __stdcall NotifyIpChangeThreadFunction(void* data);
public:
	virtual ~ThreadNotifyIpChangeBase()
	{
		Terminate();
		if(m_overlap.hEvent)
		{
			CloseHandle(m_overlap.hEvent);
		}
	}
protected:
/*
	virtual void OnThreadFunctionStarted(){}
	virtual bool ProcessDataMessage(const Message* message) = 0;
	virtual bool DoIdle(unsigned int idleCount){return false;}
	virtual void NotifyOverflow(){}
	virtual void Log(const char* info, const char* prefix) const{}
	void InvalidateData();
*/
	ThreadNotifyIpChangeBase(const char* name, int priority = 0, unsigned int waitToTerminate = INFINITE, unsigned int padSize = 0);

	virtual void NotifyIpChange() = 0;

	void Terminate()//Call this function in the derived class Destructor to finish all data processing
	{
		m_dataOk = false;
		if(m_overlap.hEvent)
		{
			SetEvent(m_overlap.hEvent);
		}
		WaitForSingleObject(m_threadHandle, m_waitToTerminate);
	}
	OVERLAPPED m_overlap;
};
////////////////////

class U_API TokenExpressionBase
{
friend class TokenExpressionCollection;
public:
	virtual ~TokenExpressionBase(){}
//	typedef std::hash_set<TokenExpressionBase*> ExpressionSet;
	virtual TokenExpressionBase* Clone() const = 0;
	TokenExpressionBase* CloneIfSimple(){return isSimple() ? Clone() : this;}
//	TokenExpressionBase* CreateDeepCopy() const{return CreateDeepCopyRecursive();}
	virtual const std::string& GetName() const = 0;
	virtual bool SetName(const char* const& name){return false;}
	virtual bool isSimple() const{return false;}
	bool isTrue(const char* text) const
	{
		return isTrueRecursive(text, 0, 0);
	}
	typedef std::map<std::string, bool> StringBoolMap;//true - WholeWordsOnly
	void CollectTokens(StringBoolMap& caseInsensitiveTokens, StringBoolMap& caseSensitiveTokens) const
	{
		CollectTokensRecursive(caseInsensitiveTokens, caseSensitiveTokens, 0, 0);
	}
	virtual void AddUsedBy(TokenExpressionCollection* expression){}
	virtual void RemoveUsedBy(TokenExpressionCollection* expression){}
	virtual bool isUsed() const{return false;}
	virtual void ClearUsedBy(){}

	virtual TokenExpressionBase* RemoveExpression(TokenExpressionBase* expression, bool unlink = true){return nullptr;}
	virtual bool RemoveAndDestroyExpression(TokenExpressionBase* expression, bool unlink = true){return false;}
	virtual bool RenameExpression(const char* oldName, const char* newName){return false;}

	const bool& isInvoked() const{return m_invoked;}

	inline int CompareParams(const char* const& name, const bool& simple) const
	{
		const int result = strcmp(GetName().c_str(), name);
		return result < 0 ? -1:
			result > 0 ? 1:
			isSimple() ?
				simple ? 0 : 1:
				simple ? -1 : 0;
	}
	inline int Compare(const TokenExpressionBase& other) const{return CompareParams(other.GetName().c_str(), other.isSimple());}
	virtual bool operator==(const TokenExpressionBase& other) const{return isSimple() == other.isSimple() && !strcmp(GetName().c_str(), other.GetName().c_str());}
	bool operator!=(const TokenExpressionBase& other) const{return !operator==(other);}
	bool operator<(const TokenExpressionBase& other) const{return Compare(other) < 0;}
	bool operator>(const TokenExpressionBase& other) const{return Compare(other) > 0;}
	bool operator<=(const TokenExpressionBase& other) const{return Compare(other) <= 0;}
	bool operator>=(const TokenExpressionBase& other) const{return Compare(other) >= 0;}

	virtual bool DeepEqual(const TokenExpressionBase& other) const{return operator==(other);}

protected:
	TokenExpressionBase():m_invoked(false){}
	virtual bool isTrueRecursive(const char* text, const unsigned char caseSensitive, const unsigned char wholeWord) const = 0;
	virtual void CollectTokensRecursive(StringBoolMap& caseInsensitiveTokens, StringBoolMap& caseSensitiveTokens, const unsigned char caseSensitive, const unsigned char wholeWord) const = 0;
//	virtual TokenExpressionBase* CreateDeepCopyRecursive() const{return Clone();}
private:
	mutable bool m_invoked;
};

class U_API TokenExpressionSimple : public TokenExpressionBase
{
public:
	TokenExpressionSimple(const char* const& token):m_token(token), m_tokenUppercase(token)
	{
		NormalizeTokenUppercase();
	}
	TokenExpressionSimple(const std::string& token):m_token(token), m_tokenUppercase(token.c_str())
	{
		NormalizeTokenUppercase();
	}
	virtual const std::string& GetName() const override{return m_token;}
	virtual TokenExpressionBase* Clone() const override;
	const std::string& GetToken() const{return m_token;}
	const std::string& GetTokenUppercase() const{return m_tokenUppercase;}
	bool SetToken(const char* const& token)
	{
		if(strcmp(token, m_token.c_str()))
		{
			m_token = token;
			m_tokenUppercase = token;
			NormalizeTokenUppercase();
			return true;
		}
		return false;
	}
	virtual bool isSimple() const{return true;}
protected:
	virtual bool isTrueRecursive(const char* text, const unsigned char caseSensitive, const unsigned char wholeWord) const override;
	virtual void CollectTokensRecursive(StringBoolMap& caseInsensitiveTokens, StringBoolMap& caseSensitiveTokens, const unsigned char caseSensitive, const unsigned char wholeWord) const override;
	std::string m_token;
	std::string m_tokenUppercase;
private:
	void NormalizeTokenUppercase()
	{
		char* cursor = (char*)m_tokenUppercase.c_str();
		for(char c = *cursor; c; c = *++cursor)
		{
			if(c >= 'a' && c <= 'z')*cursor -= 0x20;
		}
	}
};

class TokenExpressionCollection;

typedef std::map<std::string, TokenExpressionCollection*> TokenExpressionMap;

enum ExpressionFlags : unsigned char
{
	EF_NOT,
	EF_CASE_SENSITIVE,
	EF_WHOLE_WORD,

	EF_Count
};

class StrUCharKey : public FilterStringAsNumberArray
{
public:
	explicit StrUCharKey(const char* const& str, const unsigned char& type):FilterStringAsNumberArray(str), m_type(type){}
	StrUCharKey(const char*& str, const char& del, const unsigned char& type):FilterStringAsNumberArray(str, del), m_type(type){}
	StrUCharKey(const char*& str, const unsigned short& length, const char& del, const unsigned char& type):FilterStringAsNumberArray(str, length, del), m_type(type){}
	StrUCharKey(unsigned short exactLength, const char* str, const unsigned char& type):FilterStringAsNumberArray(exactLength, str), m_type(type){}
	explicit StrUCharKey(const std::string& str, const unsigned char& type):FilterStringAsNumberArray(str), m_type(type){}
	StrUCharKey():m_type(0){}
	const unsigned char& GetType() const{return m_type;}
	void SetType(const unsigned char& type){m_type = type;}
	void SetStringAndType(const std::string& str, const unsigned char& type){SetString(str); m_type = type;}
	DECLARE_NED_NEW

	bool operator==(const StrUCharKey& other) const{return FilterStringAsNumberArray::operator==(other) && m_type == other.m_type;}
	bool operator!=(const StrUCharKey& other) const{return !operator==(other);}
	short Compare(const StrUCharKey& other) const
	{
		return m_type == other.m_type ? FilterStringAsNumberArray::Compare(other):
			m_type < other.m_type ? -1 :
			m_type > other.m_type ? 1 :
			0;
	}
	short CompareAsStrings(const StrUCharKey& other) const
	{
		const short result = FilterStringAsNumberArray::CompareAsStrings(other);
		return result != 0 ? result:
			m_type < other.m_type ? -1:
			m_type > other.m_type ? 1:
			0;
	}
	bool operator<(const StrUCharKey& other) const{return CompareAsStrings(other) < 0;}
	bool operator>(const StrUCharKey& other) const{return CompareAsStrings(other) > 0;}
	bool operator<=(const StrUCharKey& other) const{return CompareAsStrings(other) <= 0;}
	bool operator>=(const StrUCharKey& other) const{return CompareAsStrings(other) >= 0;}
protected:
	unsigned char m_type;
};

class U_API TokenExpressionCollection : public TokenExpressionBase
{
public:
	TokenExpressionCollection(const char* const& name, const bool& and):
		m_name(name),
		m_and(and),
		m_expressionMapEnd(m_expressionMap.cend()),
		m_expressionCollectionEnd(m_expressionCollection.cend()),
		m_usedByEnd(m_usedBy.cend())
	{}
	TokenExpressionCollection(const std::string& name, const bool& and):
		m_name(name),
		m_and(and),
		m_expressionMapEnd(m_expressionMap.cend()),
		m_expressionCollectionEnd(m_expressionCollection.cend()),
		m_usedByEnd(m_usedBy.cend())
	{}
	TokenExpressionCollection(const TokenExpressionCollection& other);
	virtual ~TokenExpressionCollection(){UnlinkUsedBy(); ClearExpressions();}
	TokenExpressionCollection& operator=(const TokenExpressionCollection& other);

#if (_MSC_VER > 1600)
	typedef std::unordered_set<TokenExpressionCollection*> ExpressionSet;
	typedef std::unordered_map<TokenExpressionBase*, unsigned char> ExpressionCollection;//ExpressionFlags
#else
	typedef std::hash_set<TokenExpressionCollection*> ExpressionSet;
	typedef std::hash_map<TokenExpressionBase*, unsigned char> ExpressionCollection;//ExpressionFlags
#endif
//	typedef std::map<std::string, TokenExpressionBase*> ExpressionMap;
	typedef std::map<StrUCharKey, TokenExpressionBase*> ExpressionMap;

	bool ClearExpressions();
//	void Link(const std::map<std::string, TokenExpressionCollection*>& expressionMap);
	void Link(const TokenExpressionMap& expressionMap);
	const bool& isAnd() const{return m_and;}
	bool SetAnd(const bool& and)
	{
		if(and != m_and)
		{
			m_and = and;
			return true;
		}
		return false;
	}
	virtual TokenExpressionBase* Clone() const override;
	virtual const std::string& GetName() const override{return m_name;}
	virtual bool SetName(const char* const& name) override
	{
		if(strcmp(name, m_name.c_str()))
		{
			m_name = name;
			return true;
		}
		return false;
	}
	ExpressionMap& GetExpressionMap(){return m_expressionMap;}
	const ExpressionMap& GetExpressionMap() const{return m_expressionMap;}
	
	TokenExpressionBase* FindExpressionByName(const StrUCharKey& key)
	{
		ExpressionMap::iterator found = m_expressionMap.find(key);
		return found == m_expressionMapEnd ? nullptr : found->second;
	}
	const TokenExpressionBase* FindExpressionByName(const StrUCharKey& key) const
	{
		ExpressionMap::const_iterator found = m_expressionMap.find(key);
		return found == m_expressionMapEnd ? nullptr : found->second;
	}
	TokenExpressionBase* FindExpressionByName(const std::string& name, const bool& simple){return FindExpressionByName(StrUCharKey(name, simple ? 1 : 0));}
	const TokenExpressionBase* FindExpressionByName(const std::string& name, const bool& simple) const{return FindExpressionByName(StrUCharKey(name, simple ? 1 : 0));}
	const unsigned char* FindExpression(TokenExpressionBase* const& expression) const
	{
		ExpressionCollection::const_iterator found = m_expressionCollection.find(expression);
		return found == m_expressionCollectionEnd ? nullptr : &found->second;
	}
	unsigned char* FindExpression(TokenExpressionBase* const& expression)
	{
		ExpressionCollection::iterator found = m_expressionCollection.find(expression);
		return found == m_expressionCollectionEnd ? nullptr : &found->second;
	}
	bool AddExpression(TokenExpressionBase* expression, const unsigned char& flags)//1 - negative, 2 - caseSensitive
	{
		unsigned char* found = FindExpression(expression);
		if(found)
		{
			if(flags != *found)
			{
				*found = flags;
				return true;
			}
			return false;
		}
		else
		{
			TokenExpressionBase* expressionFound = FindExpressionByName(expression->GetName(), expression->isSimple());
			if(expressionFound)
			{
				found = FindExpression(expressionFound);
				if(found)
				{
					if(flags != *found)
					{
						*found = flags;
						return true;
					}
				}
				return false;
			}
			else
			{
				m_expressionMap.insert(ExpressionMap::value_type(StrUCharKey(expression->GetName(), expression->isSimple() ? 1 : 0), expression));
				return m_expressionCollection.insert(ExpressionCollection::value_type(expression, flags)).second;
			}
		}
	}
	virtual TokenExpressionBase* RemoveExpression(TokenExpressionBase* expression, bool unlink = true) override;
	virtual bool RemoveAndDestroyExpression(TokenExpressionBase* expression, bool unlink = true) override;
	virtual bool RenameExpression(const char* oldName, const char* newName) override;

	virtual void AddUsedBy(TokenExpressionCollection* expression) override{m_usedBy.insert(expression);}
	virtual void RemoveUsedBy(TokenExpressionCollection* expression) override{m_usedBy.erase(expression);}
	virtual bool isUsed() const override{return !m_usedBy.empty();}
	virtual void ClearUsedBy() override{m_usedBy.clear();}
	ExpressionSet& GetUsedBy(){return m_usedBy;}
	const ExpressionSet& GetUsedBy() const{return m_usedBy;}
	void UnlinkUsedBy();
	bool isUsedBy(const TokenExpressionCollection* expression) const;
	virtual bool operator==(const TokenExpressionBase& other) const;
	virtual bool DeepEqual(const TokenExpressionBase& other) const;
	void CopyContents(const ExpressionCollection& expressionCollection);
	void CopyContents(const TokenExpressionCollection& other)
	{
		CopyContents(other.m_expressionCollection);
	}
	ExpressionCollection& GetExpressionCollection(){return m_expressionCollection;}
	const ExpressionCollection& GetExpressionCollection() const{return m_expressionCollection;}

protected:
	ExpressionCollection::iterator Erase(ExpressionCollection::iterator found, bool unlink);
	virtual bool isTrueRecursive(const char* text, const unsigned char caseSensitive, const unsigned char wholeWord) const override;
	virtual void CollectTokensRecursive(StringBoolMap& caseInsensitiveTokens, StringBoolMap& caseSensitiveTokens, const unsigned char caseSensitive, const unsigned char wholeWord) const override;
	std::string m_name;
	bool m_and;
	ExpressionMap m_expressionMap;
	ExpressionMap::const_iterator m_expressionMapEnd;
	ExpressionCollection m_expressionCollection;
	ExpressionCollection::const_iterator m_expressionCollectionEnd;
	ExpressionSet m_usedBy;
	ExpressionSet::const_iterator m_usedByEnd;
};
