#include "stdafx.h"
#include "MainDialog.h"
#include "EOH.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

std::string CreateTitle(const char* const& productName, const unsigned __int64& productVersion)
{
	std::string title(productName);
	title += ' ';
	U_VersionNumToStr(productVersion, title);
	return title;
}

MainDialog::MainDialog(const char* productName, unsigned __int64 productVersion, const char* configExtension):
	ExtensionMainDialog(280, 164, CreateTitle(productName, productVersion).c_str(), productName, productVersion, configExtension),
	m_eoh(NULL)
{
}

BOOL MainDialog::OnInitDialog()
{
	TakionMainWnd* frame = TGUI_GetTakionMainWnd();

	TakionSettingTabDialog* tabDlg = new TakionSettingTabDialog(m_mainWnd, this, "");//, 437, 152);
	AddSettingDialog(tabDlg);
	m_eoh = new EOH(frame, tabDlg);
	tabDlg->AddSettingDialog(m_eoh);

	BOOL ret = ExtensionMainDialog::OnInitDialog();

	return ret;
}

void MainDialog::BeforeDestroy()
{
	m_eoh = NULL;
	ExtensionMainDialog::BeforeDestroy();
}

bool MainDialog::MainThreadIdleState(unsigned int idleCount, bool takionIdleDone)
{
	return false;
}

bool MainDialog::CurrentAccountSet(Account* account)
{
	return false;
}

