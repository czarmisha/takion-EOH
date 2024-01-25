#pragma once

class EOH;

class MainDialog : public ExtensionMainDialog
{
public:
	MainDialog(const char* productName, unsigned __int64 productVersion, const char* configExtension);
	virtual bool CurrentAccountSet(Account* account) override;
	typedef std::map<unsigned int, std::string> UIntStrMap;

	bool MainThreadIdleState(unsigned int idleCount, bool takionIdleDone);
protected:
	virtual BOOL OnInitDialog() override;
	virtual void BeforeDestroy() override;

	EOH* m_eoh;
};
