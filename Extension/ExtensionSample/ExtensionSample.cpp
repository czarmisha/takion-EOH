// ExtensionSample.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "ExtensionSample.h"
#include "MainDialog.h"
#include "ExtensionDerivedConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// The one and only ExtensionSample object
ExtensionSample theApp;

MainDialog* mainDialog = NULL;

TakionPopupWnd* messageWnd = NULL;
TakionMessageBox* messageBox = NULL;

ExtensionDerivedConfig* extensionConfig = NULL;

const char* const configExtension = "ecg";


#ifdef __cplusplus
extern "C"
{
#endif

unsigned int WINAPI GetExtensionCode(){return ClientExtensionDll::validExtensionCode;}
unsigned __int64 WINAPI GetExtensionVersion(){return theApp.GetVersionNum();}
unsigned __int64 WINAPI GetUtilsVersion(){return U_GetModuleVersionNum();}
unsigned __int64 WINAPI GetUtilsHeaderVersion(){return U_VersionStrToNum(UtilsHeaderVersion);}
unsigned __int64 WINAPI GetUtilsGuiVersion(){return UGUI_GetModuleVersionNum();}
unsigned __int64 WINAPI GetUtilsGuiHeaderVersion(){return U_VersionStrToNum(UtilsGuiHeaderVersion);}
unsigned __int64 WINAPI GetTakionUtilsVersion(){return TU_GetModuleVersionNum();}
unsigned __int64 WINAPI GetTakionUtilsHeaderVersion(){return U_VersionStrToNum(TakionUtilsHeaderVersion);}
unsigned __int64 WINAPI GetTakionGuiVersion(){return TGUI_GetModuleVersionNum();}
unsigned __int64 WINAPI GetTakionGuiHeaderVersion(){return U_VersionStrToNum(TakionGuiHeaderVersion);}
unsigned __int64 WINAPI GetTakionDataVersion(){return TD_GetModuleVersionNum();}
unsigned __int64 WINAPI GetTakionDataHeaderVersion(){return U_VersionStrToNum(TakionDataHeaderVersion);}
unsigned __int64 WINAPI GetTakionLogVersion(){return TL_GetModuleVersionNum();}
unsigned __int64 WINAPI GetTakionLogHeaderVersion(){return U_VersionStrToNum(TakionLogHeaderVersion);}
unsigned __int64 WINAPI GetObserverVersion(){return O_GetModuleVersionNum();}
unsigned __int64 WINAPI GetObserverHeaderVersion(){return U_VersionStrToNum(ObserverHeaderVersion);}

//unsigned __int64 WINAPI GetReceiverVersion(){return R_GetModuleVersionNum();}
unsigned __int64 WINAPI GetReceiverHeaderVersion(){return U_VersionStrToNum(ReceiverHeaderVersion);}

bool WINAPI ExtensionIsDebug()
{
#ifdef _DEBUG
	return true;
#else
	return false;
#endif
}

const char* WINAPI GetTakionExtensionDescription(){return theApp.GetFileDescription().c_str();}

void WINAPI MessageReport(unsigned char connectionType, const Message* message, bool outgoing)
{
}

void WINAPI NextDayStarted()//This function is called first thing when the next day starts. After some actions in Takion you also get a message TMsgNextDayStarted = TM_NEXT_DAY_STARTED
{
}

void WINAPI LineDoubleClicked()
{
	if(mainDialog)
	{
		mainDialog->Top();
	}
}

void WINAPI KeyStrokeAndCommand(unsigned char ascii, unsigned char modifier, bool repeat, const char* commandName, unsigned int extensionCode, unsigned int userExtensionCode)//commandName can be NULL;
{
	switch(extensionCode)
	{
		case 1:
//Extension Keystroke command
		break;

		case 0:
//Takion command
		break;

		default:
//Unknown command
		break;
	}
}

void WINAPI SymbolEnteredInMmBox(const char* symbol, unsigned char securityType, bool valid, bool fromKeyboard, unsigned int ordinal)
{
}

void WINAPI SecurityRefreshed(const char* symbol, const Security* security, bool wasLoaded, unsigned int ordinal)//security can be NULL;
{
}

void WINAPI ActiveMmBoxChanged(const char* symbol, const Security* security, bool wasLoaded, unsigned int ordinal)//symbol and security can be NULL;
{
}

void WINAPI CommandWindowRemoved(unsigned int ordinal)
{
}

void WINAPI LayoutChanged()
{
}

void WINAPI AppActivated(bool applicationActive)
{
	if(!applicationActive && mainDialog)mainDialog->OnMouseForcedReleaseCapture();
}

void WINAPI TakionMoveWindows(int dx, int dy)
{
	if(mainDialog)mainDialog->DragWindow(dx, dy);
}

void WINAPI MarketSorterNotifyAdded(HWND hwnd, const char* prefix)
{
}

void WINAPI MarketSorterContents(HWND hwnd, const char* prefix, const Security* security)
{
}

void WINAPI MarketSorterContentsDone(HWND hwnd, const char* prefix)
{
}

void WINAPI MarketSorterNotifyRemoved(HWND hwnd, const char* prefix)
{
}

void WINAPI MarketSorterNotifyPrefixChanged(HWND hwnd, const char* oldPrefix, const char* prefix)
{
}

void WINAPI NotifyMarketSorterSymbol(HWND hwnd, const char* prefix, const Security* security, bool added)
{
}

void WINAPI MarketSorterNotifyAllRowsRemoved(HWND hwnd, const char* prefix)
{
}

void WINAPI MainThreadAvailableDataProcessed()
{
}

bool WINAPI MainThreadIdleState(unsigned int idleCount, bool takionIdleDone)
{
	return mainDialog->MainThreadIdleState(idleCount, takionIdleDone);
}

const char* WINAPI GetExtensionInfo()
{
//	return theApp.GetInfo().c_str();
	TakionSettingDialog* tab = mainDialog->GetCurrentLeaf();
	return tab ? tab->GetLabel() : "";
}

//Format: "<1 ifEnabled, or 0 ifDisabled><1 ifChecked, or 0 ifUnchecked><MenuItemText>|..."
//For a separator: just one char |
void AddMenuItemToString(std::string& menuStr, const char* text = NULL, bool enabled = true, bool checked = false, bool checkable = false)
{
	if(text)
	{
		if(!menuStr.empty())
		{
			menuStr += '|';
		}
		menuStr += enabled ? '1' : '0';
		menuStr += checked ? '1' : checkable ? '2' : '0';
		menuStr += text;
	}
	else//separator
	{
		menuStr += '|';
	}
}

static bool check = true;
void WINAPI GetTakionExtensionMenu(std::string& menuStr)
{
	AddMenuItemToString(menuStr, "First", true, false);
	AddMenuItemToString(menuStr);
	AddMenuItemToString(menuStr, "Second", true, check, true);
	AddMenuItemToString(menuStr, "Third", false, false);
	AddMenuItemToString(menuStr, "Fourth", false, true);
	AddMenuItemToString(menuStr, "Show");
	AddMenuItemToString(menuStr, "Hide");
	AddMenuItemToString(menuStr, "Corner");
	AddMenuItemToString(menuStr, "PopupWnd");
	AddMenuItemToString(menuStr, "MessageBox");
}

void WINAPI ExecuteTakionCommand(unsigned short commandId, CWnd* takionExtensionWindow)
{
	switch(commandId)
	{
		case 0:
		{
			TakionMessageBox mb(TGUI_GetTakionMainWnd());
			mb.AddMessage("Command 1 executed");
			mb.DisplayModal(takionExtensionWindow, "Extension Command", MB_OK|MB_ICONINFORMATION);//, RGB(0, 0, 128), RGB(255, 255, 255));
 		}
		break;

		case 1:
		check = !check;
		{
			TakionMessageBox mb(TGUI_GetTakionMainWnd());
			mb.AddMessage(check ? "Command 2 checked" : "Command 2 unchecked");
			mb.DisplayModal(takionExtensionWindow, "Extension Command", MB_OK|MB_ICONINFORMATION);//, RGB(0, 0, 128), RGB(255, 255, 255));
		}
		break;

		case 2:
		{
			TakionMessageBox mb(TGUI_GetTakionMainWnd());
			mb.AddMessage("Command 3 executed");
			mb.DisplayModal(takionExtensionWindow, "Extension Command", MB_OK|MB_ICONINFORMATION);//, RGB(0, 0, 128), RGB(255, 255, 255));
		}
		break;

		case 3:
		{
			TakionMessageBox mb(TGUI_GetTakionMainWnd());
			mb.AddMessage("Command 4 executed");
			mb.DisplayModal(takionExtensionWindow, "Extension Command", MB_OK|MB_ICONINFORMATION);//, RGB(0, 0, 128), RGB(255, 255, 255));
		}
		break;

		case 4:
		if(mainDialog)
		{
			mainDialog->Top();
		}
		break;

		case 5:
		if(mainDialog)
		{
			mainDialog->OnCancel();
		}
		break;

		case 6:
		if(mainDialog)
		{
			mainDialog->Corner();
		}
		break;

		case 7:
		if(messageWnd)
		{
			messageWnd->ClearMessageList(false);
			messageWnd->AddMessage("Text", false);
			messageWnd->DisplayModeless(mainDialog ? (CWnd*)mainDialog : (CWnd*)TGUI_GetTakionMainWnd(), "TakionExtension", MB_YESNO | MB_ICONQUESTION);
		}
		break;

		case 8:
		if(messageBox)
		{
			messageBox->ClearMessageList(false);
			messageBox->AddMessage("Text", false);
			messageBox->DisplayModeless(mainDialog ? (CWnd*)mainDialog : (CWnd*)TGUI_GetTakionMainWnd(), "TakionExtension", MB_YESNO | MB_ICONQUESTION);
		}
		break;

		default:
		{
			TakionMessageBox mb(TGUI_GetTakionMainWnd());
			std::string info("Unknown Command ");
			char num[33];
			info += U_UnsignedNumberToStrNoDecDigits(commandId, num, sizeof(num));
			mb.AddMessage(info);
			mb.DisplayModal(takionExtensionWindow, "Extension Command", MB_OK|MB_ICONERROR);//, RGB(0, 0, 128), RGB(255, 255, 255));
		}
		break;
	}
}

void WINAPI ExtensionInitialize()
{
	if(!mainDialog)
	{
		const std::string& configPath = theApp.GetConfigFilePath();

		mainDialog = new MainDialog(theApp.GetProductName().c_str(), theApp.GetVersionNum(), configExtension);
//		mainDialog->AddSettingDialog(new DialogMirror(mainDialog->GetMainWnd(), mainDialog));

		extensionConfig = new ExtensionDerivedConfig;
//		initialExtensionConfig = new ExtensionDerivedConfig;

		extensionConfig->SetFileName(configPath.c_str());
		extensionConfig->Serialize(true, configPath.c_str(), theApp.GetVersionStr().c_str(), true, 0);
//		savedConfig = (ExtensionDerivedConfig*)extensionConfig->Clone();

		mainDialog->SetConfig(extensionConfig);
//		mainDialog = new MainDialog();
		TakionMainWnd* mainWnd = TGUI_GetTakionMainWnd();//mainDialog->GetMainWnd()

		mainDialog->ApplyConfig(0);
		mainDialog->CreateModeless(mainWnd);

		messageWnd = new TakionPopupWnd(mainWnd, true);
		messageWnd->AddCheckBox("CheckBox", true, false, false, false);

		messageBox = new TakionMessageBox(mainWnd, true);
		messageBox->AddCheckBox("CheckBox", false, true, false, false);

//		stockPairDialog->UpdateSystemRects();

	}
}

void WINAPI ExtensionTerminate()
{
//Cleanup commands
//
	if(mainDialog)
	{
		if(messageWnd)
		{
			if(messageWnd->m_hWnd)
			{
				messageWnd->DestroyWindow();
//			delete messageWnd;//destruction is done in DestroyWindow by the operating system
			}
			else
			{
				delete messageWnd;
			}
			messageWnd = NULL;
		}

		if(messageBox)
		{
			messageBox->DestroyWindow();
			delete messageBox;
			messageBox = NULL;
		}

		mainDialog->DestroyWindow();
		delete mainDialog;
		mainDialog = NULL;
	}
}

void WINAPI CurrentAccountSet(Account* account)
{
	if(mainDialog)
	{
		mainDialog->CurrentAccountSet(account);
	}
}

void WINAPI OpenLayout()
{
	if(mainDialog)
	{
		mainDialog->OpenDlgLayout();
	}
}

void WINAPI SaveLayout()
{
	if(mainDialog)
	{
		mainDialog->SaveDlgLayout();
	}
}

void WINAPI RestoreLayout()
{
	if(mainDialog)
	{
		mainDialog->RestoreDlgLayout();
	}
}

const char* WINAPI GetLayoutFilePath()
{
	const std::string& configFile = theApp.GetConfigFilePath();
	return configFile.empty() ? NULL : configFile.c_str();
}

void WINAPI SaveLayoutAs()
{
	if(mainDialog)
	{
		mainDialog->SaveDlgLayoutAs();
	}
}

CWnd* WINAPI TakionCreateExtensionTool(const char* id, const CBitmap* bitmap, unsigned int workspace, bool pinned)
{
//	return m_CreateExtensionToolFunction(id, bitmap, workspace, pinned);
	return NULL;
}

#ifdef __cplusplus
}
#endif

// ExtensionSample construction

ExtensionSample::ExtensionSample()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// CExtensionSampleApp initialization

BOOL ExtensionSample::InitInstance()
{
	CWinApp::InitInstance();
	U_InitializeInstanceInfo(m_hInstance, m_filePathAndName, m_fileDescription, m_platform, m_versionNum, m_versionStr);

	U_QueryVersionResourceValue(m_filePathAndName.c_str(), "ProductName", m_productName);

	char path[MAX_PATH];
	strcpy_s(path, sizeof(path), m_filePathAndName.c_str());
	char* p = strrchr(path, '\\');
	if(!p)
	{
		p = path + strlen(path);
		*p = '\0';
	}
	else
	{
		*(p + 1) = '\0';
	}
	m_dllPath = path;

	m_configFilePath = m_dllPath;
	m_configFilePath += "EOH.";//ecg";
	m_configFilePath += configExtension;

	return TRUE;
}

int ExtensionSample::ExitInstance()
{
	int ret = CWinApp::ExitInstance();
	return ret;
}

void ExtensionSample::SetInfo(const char* info)
{
	TGUI_UpdateExtensionRow(m_hInstance);
}
