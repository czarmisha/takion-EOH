using namespace std;

#pragma once

struct positionStruct
{
	Security* security;
	string symbol;
	char side;
	unsigned int size;
	Price entryPrice;
	Price stopPrice;
	Price targetPrice;
	unsigned int triggerMinute;
};


class EOH : public TakionSettingPageBase, public Observer
{
public:
	EOH(TakionMainWnd* mainWnd, TakionSettingTabDialog* parentTab);
	~EOH();

protected:
	// ================== default =======================
	void Cleanup();

	virtual void Entering() override;
	virtual void Leaving() override;

	virtual void DoDataExchange(CDataExchange* pDX) override;
	virtual BOOL OnInitDialog() override;
	virtual void BeforeDestroy() override;

	void EnableSubscribeButton();

	bool DoSubscribe();
	void SecurityFailed();

	afx_msg void OnRun();
	afx_msg void OnStop();

	DECLARE_MESSAGE_MAP();

	virtual void Notify(const Message* message, const Observable* from, const Message* info) override;

	CButton m_ButtonRun;
	CButton m_ButtonStop;
	CStatic m_StatusCheck;

	bool isRun;
	string m_symbol;
	Account* m_account;
	Security* m_security;

	unsigned int m_updateFrequency;
	unsigned int m_lastNotificationTime;

	// ==========================================
	// ==========================================

	void InitializeTickerList();
	void CheckLogic();
	void CheckPosition();
	void InitializeTriggeredList();

	positionStruct GetStructBySymbol(string positionSymbol);
	void CheckStopTargetOrders(Position* position, positionStruct position_struct);
	void CheckIsTargetAlreadyReached(Position* position, positionStruct position_struct);
	void CheckKeepPositionTimeExpired(Position* position, positionStruct position_struct);
	void CheckOpenPositionTimeExpired(Position* position, positionStruct position_struct);
	void SendOrder(Security* security, char side, Price order_price, unsigned int size, unsigned char order_type);

	double m_minBreakout;
	double m_maxBreakout;
	unsigned int m_riskRewardRatio;
	unsigned int m_entryTimeLimit;
	unsigned int m_keepPostitionTimeLimit;
	unsigned int m_positionRisk;

	std::vector<Security*> m_securityList;
	std::vector<positionStruct> m_triggeredSecurityList;
};
