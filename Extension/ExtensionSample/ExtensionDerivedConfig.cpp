#include "stdafx.h"
#include "ExtensionDerivedConfig.h"
#include "MainDialog.h"
#include "ConfigEnums.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern MainDialog* mainDialog;

ExtensionDerivedConfig::ExtensionDerivedConfig():
	ExtensionConfig(mainDialog)
{
	AddSettings();
}

ExtensionDerivedConfig::ExtensionDerivedConfig(const ExtensionDerivedConfig& other):
	ExtensionConfig(other),
	m_riskRewardRatio(other.m_riskRewardRatio),
	m_entryTimeLimit(other.m_entryTimeLimit),
	m_keepPostitionTimeLimit(other.m_keepPostitionTimeLimit),

	m_tickerListFolder(other.m_tickerListFolder),
	m_account(other.m_account),
	m_updateFrequency(other.m_updateFrequency),
	m_positionRisk(other.m_positionRisk)
{
	AddSettings();
}

void ExtensionDerivedConfig::AddSettings()
{
	AddSetting("RiskRewardRatio", m_riskRewardRatio);
	AddSetting("EntryTimeLimit", m_entryTimeLimit);
	AddSetting("KeepPostitionTimeLimit", m_keepPostitionTimeLimit);

	AddSetting("TickerListFolder", m_tickerListFolder);
	AddSetting("Account", m_account);
	AddSetting("UpdateFrequency", m_updateFrequency);
	AddSetting("PositionRisk", m_positionRisk);
}

ConfigBase* ExtensionDerivedConfig::Clone() const
{
	ExtensionDerivedConfig* clone = new ExtensionDerivedConfig;
	clone->Copy(*this);
	return clone;
}

void ExtensionDerivedConfig::Copy(const ConfigBase& other)
{
//	TakionConfig::Copy(other);
	operator=((const ExtensionDerivedConfig&)other);
}

const ExtensionDerivedConfig& ExtensionDerivedConfig::operator=(const ExtensionDerivedConfig& other)
{
	ExtensionConfig::operator=(other);
//	m_orderReplaceTemplateVersion = other.m_orderReplaceTemplateVersion;
	return *this;
}

void ExtensionDerivedConfig::Update()
{
	ExtensionConfig::Update();
}
