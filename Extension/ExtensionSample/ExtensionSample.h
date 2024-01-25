// ExtensionSample.h : main header file for the ExtensionSample DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

//#include "Resource.h"		// main symbols


// CExtensionSampleApp
// See ExtensionSample.cpp for the implementation of this class
//
enum ExtensionSampleCustomMessageIds : unsigned short
{
	POSITION_VALUES = 100,
	POSITION_OPEN_PRINT_PNL_DIFF,
	POSITION_OPEN_LEVEL1_PNL_DIFF,
	POSITION_CLOSED_PNL_DIFF,

	NEW_ORDER_CREATED,
	ORDER_TOTALS_CHANGED,
	NEW_ORDER_SEND_ORDER_DONE,
	ORDER_DELETED,

	NEW_POSITION_CREATED,
	POSITION_TOTALS_CHANGED,

	CustomMessageEnd
};

class TMsgSamplePositionId : public TMsgCustomExternal
{
public:
	unsigned __int64 m_numericSymbol;
#ifndef TAKION_NO_OPTIONS
	unsigned __int64 m_optionBlock;
	unsigned char m_securityType;
#endif
protected:
	TMsgSamplePositionId(const unsigned __int64& numericSymbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
		const unsigned char& securityType,
#endif
		const unsigned short& tipe, const unsigned short& length):
		TMsgCustomExternal(tipe, length),
		m_numericSymbol(numericSymbol)
#ifndef TAKION_NO_OPTIONS
		,m_optionBlock(optionBlock)
		,m_securityType(securityType)
#endif
	{}
};

class TMsgSampleNewPositionCreated : public TMsgSamplePositionId
{
public:
	TMsgSampleNewPositionCreated(const unsigned __int64& numericSymbol
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& optionBlock
		,const unsigned char& securityType
#endif
		):
		TMsgSamplePositionId(numericSymbol,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
			securityType,
#endif
			NEW_POSITION_CREATED, sizeof(TMsgSampleNewPositionCreated))
	{}
};

class ExtensionSample : public CWinApp
{
public:
	ExtensionSample();
	virtual BOOL InitInstance() override;
	virtual int ExitInstance() override;
	const std::string& GetDllPath() const{return m_dllPath;}
	const std::string& GetConfigFilePath() const{return m_configFilePath;}
	void SetConfigFilePath(const char* path){m_configFilePath = path;}
	const std::string& GetFilePathAndName() const{return m_filePathAndName;}
	const std::string& GetFileDescription() const{return m_fileDescription;}
	const std::string& GetProductName() const{return m_productName;}
	const std::string& GetPlatform() const{return m_platform;}
	const std::string& GetVersionStr() const{return m_versionStr;}
	const unsigned __int64& GetVersionNum() const{return m_versionNum;}
//	void SaveLayout();
//	const std::string& GetInfo() const{return m_info;}
	void SetInfo(const char* info);
protected:
//	DECLARE_MESSAGE_MAP()
	std::string m_info;
	std::string m_productName;
	std::string m_dllPath;
	std::string m_configFilePath;
	std::string m_filePathAndName;
	std::string m_fileDescription;
	std::string m_platform;
	std::string m_versionStr;
	unsigned __int64 m_versionNum;
};
