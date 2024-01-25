#pragma once

#include "ConfigEnums.h"

class ExtensionDerivedConfig : public ExtensionConfig
{
public:
	ExtensionDerivedConfig();
	ExtensionDerivedConfig(const ExtensionDerivedConfig& other);
	virtual void Copy(const ConfigBase& other) override;
	virtual ConfigBase* Clone() const override;

	virtual void Update() override;

	const ExtensionDerivedConfig& operator=(const ExtensionDerivedConfig& other);

	//===============================================================

	UIntSetting m_entryTimeLimit;
	UIntSetting m_keepPostitionTimeLimit;

	UIntSetting m_positionRisk;
	UIntSetting m_riskRewardRatio;

	StringSetting m_tickerListFolder;
	StringSetting m_account;
	UIntSetting m_updateFrequency;

	//==============================================================

protected:
	void AddSettings();
};