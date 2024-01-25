#include "stdafx.h"
#include "EOH.h"
#include "TakionDataApi.h"
#include "ExtensionDerivedConfig.h"
#include <iostream>
#include <fstream>
#include <sstream>


extern ExtensionDerivedConfig* extensionConfig;

ofstream outFile;


void WriteToTechLogFile(string line)
{
	static char time[33];
	U_FormatMillisecond(TL_GetCurrentMillisecond(), time, sizeof(time));
	string times(time);

	outFile << times << ": " << line << endl;
	outFile.flush();
}


bool is_number(const std::string& s)
{
	char* end = 0;
	double val = strtod(s.c_str(), &end);
	return end != s.c_str() && val != HUGE_VAL;
}


bool isOpenInGapRange(Price open, Price y_close)
{
	double rangeStart = y_close.toDouble() * 1.03;
	double rangeEnd = y_close.toDouble() * 1.1;

	if (open.toDouble() >= rangeStart && open.toDouble() <= rangeEnd)
	{
		WriteToTechLogFile("Stock open inside 3-10% gap range");
		return true;
	}

	WriteToTechLogFile("Stock do not open inside 3-10% gap range");
	return false;
}

string GetCurrentDate()
{
	string date = TL_GetDay() < 10 ? ("0" + to_string(TL_GetDay()) + "_") : (to_string(TL_GetDay()) + "_");
	date += TL_GetMonth() < 10 ? ("0" + to_string(TL_GetMonth()) + "_") : (to_string(TL_GetMonth()) + "_");
	date += to_string(TL_GetYear());

	return date;
}

Account* GetAccountById(const char* accountId)
{
	Account* account = NULL;

	TakionIterator* iterator = TD_CreateAccountIterator();
	TD_LockAccountStorage();
	iterator->Reset();

	while (account = (Account*)TD_GetNextAccount(iterator))
	{
		if (!std::strcmp(account->GetId(), accountId))
			break;
	}

	TD_UnlockAccountStorage();
	delete iterator;

	if (account)
		account->LoadExecutions();

	return account;
}

// ======================== DEFAULT =================================================================

enum EOHIds
{
	buttonRunId = 1000,
	buttonStopId,

	groupStatusdId,
	staticStatusId,
};

EOH::EOH(TakionMainWnd* mainWnd, TakionSettingTabDialog* parentTab) :
	TakionSettingPageBase(mainWnd, parentTab, "EOH"),
	m_lastNotificationTime(0),
	m_updateFrequency(0),
	isRun(false)
{
	static const int hgap = 4;
	static const int vgap = 1;
	static const int groupOffset = 9;
	static const int staticHeight = 8;
	static const int m_accountWidth = 52;
	static const int comboBoxHeight = 12;

	int xc = hgap;
	int w = m_accountWidth - hgap - hgap;
	int m_bottomControl = vgap;

	const int statusGroupHeight = groupOffset + staticHeight * 3 + 4 * vgap + hgap;//30;

	AddButtonIndirect("Status", WS_VISIBLE | BS_GROUPBOX, WS_EX_TRANSPARENT, xc, m_bottomControl, m_accountWidth * 6, statusGroupHeight, groupStatusdId);
	AddStaticIndirect("Sts:", WS_VISIBLE | SS_NOPREFIX, 0, 2 * xc, m_bottomControl += groupOffset, w * 2, staticHeight, staticStatusId);

	m_bottomControl += 15;

	AddButtonIndirect("Run", WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, 0, xc, m_bottomControl, m_accountWidth / 2, comboBoxHeight, buttonRunId);
	AddButtonIndirect("Stop", WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, 0, xc + m_accountWidth / 2 + 2, m_bottomControl, m_accountWidth / 2, comboBoxHeight, buttonStopId);
}

EOH::~EOH()
{
}

void EOH::Cleanup()
{
	if (m_security)
		SecurityFailed();
}

void EOH::Entering()
{
	DoSubscribe();
	TakionSettingPageBase::Entering();
}

void EOH::Leaving()
{
	Cleanup();
	TakionSettingPageBase::Leaving();
}

void EOH::DoDataExchange(CDataExchange* pDX)
{
	TakionSettingPageBase::DoDataExchange(pDX);
	DDX_Control(pDX, buttonRunId, m_ButtonRun);
	DDX_Control(pDX, buttonStopId, m_ButtonStop);
	DDX_Control(pDX, staticStatusId, m_StatusCheck);
}

void EOH::BeforeDestroy()
{
	Cleanup();
	TakionSettingPageBase::BeforeDestroy();
}


void EOH::EnableSubscribeButton()
{
	EnableControl(m_ButtonRun.m_hWnd, !isRun, m_ButtonRun.m_hWnd);
	EnableControl(m_ButtonStop.m_hWnd, isRun, m_ButtonRun.m_hWnd);
}

BEGIN_MESSAGE_MAP(EOH, TakionSettingPageBase)
	ON_BN_CLICKED(buttonRunId, OnRun)
	ON_BN_CLICKED(buttonStopId, OnStop)
END_MESSAGE_MAP()

void EOH::OnRun()
{
	isRun = true;
	m_symbol = "BAC";
	DoSubscribe();
	EnableSubscribeButton();
}

void EOH::OnStop()
{
	isRun = false;
	m_symbol.clear();
	DoSubscribe();
	m_StatusCheck.SetWindowText("Sts: Off");
	EnableSubscribeButton();
}

void EOH::SecurityFailed()
{
	if (m_security)
	{
		m_security->RemoveObserver(this);
		m_security = NULL;
	}

	m_StatusCheck.SetWindowText("Sts: Off");
}


bool EOH::DoSubscribe()
{
	Security* security;

	if (m_symbol.empty())
		security = NULL;
	else
		security = TD_ObtainStock(m_symbol.c_str(), false);

	if (security != m_security)
	{
		if (m_security)
			m_security->RemoveObserver(this);

		m_security = security;

		if (m_security)
		{
			m_security->AddObserver(this);
			m_security->Subscribe();
			TD_ReleaseStock(m_security);

			m_StatusCheck.SetWindowText("Sts: Active");
		}
		return true;
	}

	return false;
}

BOOL EOH::OnInitDialog()
{
	BOOL ret = TakionSettingPageBase::OnInitDialog();

	EnableSubscribeButton();

	InitializeTickerList();

	m_account = GetAccountById(extensionConfig->m_account.GetValue().c_str());  //TD_GetCurrentAccount();
	m_updateFrequency = extensionConfig->m_updateFrequency.GetValue();
	m_riskRewardRatio = extensionConfig->m_riskRewardRatio.GetValue();
	m_entryTimeLimit = extensionConfig->m_entryTimeLimit.GetValue();
	m_keepPostitionTimeLimit = extensionConfig->m_keepPostitionTimeLimit.GetValue();
	m_positionRisk = extensionConfig->m_positionRisk.GetValue();

	m_account->LoadExecutions();
	m_account->LoadOrders();

	InitializeTriggeredList();

	OnRun();

	return ret;
}

void EOH::Notify(const Message* message, const Observable* from, const Message* info)
{
	unsigned int currentTime = TL_GetCurrentMillisecond();
	if (currentTime >= m_lastNotificationTime + m_updateFrequency)
	{
		if (outFile.is_open())
			outFile.close();
		outFile.open(extensionConfig->m_tickerListFolder.GetValue() + "output.txt");

		WriteToTechLogFile("Notify");
		CheckLogic();
		CheckPosition();
		m_lastNotificationTime = currentTime;
		WriteToTechLogFile("! Notify");
	}
}

//========================================================================================================
//========================================================================================================

void EOH::InitializeTickerList()
{
	WriteToTechLogFile("InitializeTickerList");

	ifstream inputfile;

	inputfile.open(extensionConfig->m_tickerListFolder.GetValue() + GetCurrentDate() + ".txt");

	string ticker;
	m_securityList.clear();

	{
		while (getline(inputfile, ticker))
		{
			if (ticker.length())
			{
				Security* security = TD_FindSortableEquityWithNoIncrementUnsubscribe(ticker.c_str());

				if (security)
				{
					m_securityList.push_back(security);
				}
			}
		}

		inputfile.close();
	}
	WriteToTechLogFile("! InitializeTickerList");
}


void EOH::InitializeTriggeredList()
{
	WriteToTechLogFile("InitializeTriggeredList");

	m_triggeredSecurityList.clear();

	for (unsigned int i = 0; i < m_securityList.size(); ++i)
	{
		Security* security = m_securityList[i];

		positionStruct position_struct = GetStructBySymbol(security->GetSymbol());
		WriteToTechLogFile(security->GetSymbol());

		if (position_struct.security)
		{
			WriteToTechLogFile("security in position struct");
			continue;
		}

		if (!security->isOpen())
		{
			WriteToTechLogFile("security is not open");
			continue;
		}

		if (!isOpenInGapRange(security->GetOpenPrice(), security->GetClosePrice()))
		{
			continue;
		}

		if (security->GetChart()->empty())
		{
			WriteToTechLogFile("empty chart");
			continue;
		}

		unsigned int triggerTime = 0;

		for (unsigned int chartPointMinute = 571; chartPointMinute <= security->GetChart()->back().GetMinute(); ++chartPointMinute)
		{
			const ChartPoint* first_c_point = security->GetChartPointAtMinute(570);
			if (!first_c_point || first_c_point->GetLowPrice().isZero())
			{
				WriteToTechLogFile("first cpoint is zero");
				continue;
			}

			const Price triggerPrice = first_c_point->GetHighPrice();

			const ChartPoint* c_point = security->GetChartPointAtMinute(chartPointMinute);

			if (!c_point || c_point->GetLowPrice().isZero())
			{
				WriteToTechLogFile("cpoint is zero");
				continue;
			}
			//check open time ???
			if (!triggerTime && chartPointMinute < m_entryTimeLimit && c_point->GetHighPrice() > triggerPrice)
			{
				triggerTime = chartPointMinute;
				WriteToTechLogFile("set trigger time");
				continue;
			}

			if (security->GetChart()->back().GetMinute() >= m_entryTimeLimit)
			{
				WriteToTechLogFile("already time >= 9:33");
				break;
			}

			if (triggerTime && chartPointMinute < m_entryTimeLimit)
			{
				WriteToTechLogFile("set risk and size");

				Price entryPrice;
				U_DoubleToPrice(entryPrice, triggerPrice.toDouble() + 0.01, 2);

				Price stopPrice;
				U_DoubleToPrice(stopPrice, triggerPrice.toDouble() * 0.99, 2);

				Price risk = entryPrice - stopPrice;
				unsigned int size = (unsigned int)(m_positionRisk / risk.toDouble());

				if (c_point->GetEndPrice().toDouble() >= 100.00 && size < 10)
					size = 10;

				if (c_point->GetEndPrice().toDouble() < 100.00 && size < 50)
					size = 50;

				Price targetPrice;
				U_DoubleToPrice(targetPrice, entryPrice.toDouble() + (risk.toDouble() * m_riskRewardRatio), 2);

				positionStruct str = { security, security->GetSymbol(), 'B', size, entryPrice, stopPrice, targetPrice, chartPointMinute };
				m_triggeredSecurityList.push_back(str);
				WriteToTechLogFile("add position struct");
				break;
			}
		}
	}
	WriteToTechLogFile("! InitializeTriggeredList");
}


void EOH::CheckLogic()
{

	WriteToTechLogFile("CHECK LOGIC");

	for (unsigned int i = 0; i < m_securityList.size(); ++i)
	{
		Security* security = m_securityList[i];

		positionStruct position_struct = GetStructBySymbol(security->GetSymbol());
		WriteToTechLogFile(security->GetSymbol());

		if (position_struct.security)
		{
			WriteToTechLogFile("security in position struct");
			continue;
		}

		if (!security->isOpen())
		{
			WriteToTechLogFile("security is not open");
			continue;
		}

		if (!isOpenInGapRange(security->GetOpenPrice(), security->GetClosePrice()))
		{
			continue;
		}

		if (security->GetChart()->empty())
		{
			WriteToTechLogFile("empty chart");
			continue;
		}

		unsigned int triggerTime = 0;

		for (unsigned int chartPointMinute = 571; chartPointMinute <= security->GetChart()->back().GetMinute(); ++chartPointMinute)
		{
			const ChartPoint* first_c_point = security->GetChartPointAtMinute(570);
			if (!first_c_point || first_c_point->GetLowPrice().isZero())
			{
				WriteToTechLogFile("first cpoint is zero");
				continue;
			}

			const Price triggerPrice = first_c_point->GetHighPrice();

			if (chartPointMinute == 571 && !triggerPrice.isZero())
			{
				WriteToTechLogFile("First candle min: " + std::to_string(first_c_point->GetLowPrice().toDouble()) + ", max: " + std::to_string(triggerPrice.toDouble()));
			}

			const ChartPoint* c_point = security->GetChartPointAtMinute(chartPointMinute);

			if (!c_point || c_point->GetLowPrice().isZero())
			{
				WriteToTechLogFile("cpoint is zero");
				continue;
			}
			//check open time ???
			if (!triggerTime && chartPointMinute < m_entryTimeLimit && c_point->GetHighPrice() > triggerPrice)
			{
				triggerTime = chartPointMinute;
				WriteToTechLogFile("set trigger time");
				//continue;
			}

			if (security->GetChart()->back().GetMinute() >= m_entryTimeLimit)
			{
				WriteToTechLogFile("already time >= 9:33");
				break;
			}

			if (triggerTime && chartPointMinute < m_entryTimeLimit)
			{
				WriteToTechLogFile("set risk and size");
				WriteToTechLogFile("First candle high Price = " + std::to_string(triggerPrice.toDouble()));

				Price entryPrice;
				U_DoubleToPrice(entryPrice, triggerPrice.toDouble() + 0.01, 2);

				Price stopPrice;
				U_DoubleToPrice(stopPrice, triggerPrice.toDouble() * 0.99, 2);

				Price risk = entryPrice - stopPrice;
				unsigned int size = (unsigned int)(m_positionRisk / risk.toDouble());

				if (c_point->GetEndPrice().toDouble() >= 100.00 && size < 10)
					size = 10;

				if (c_point->GetEndPrice().toDouble() < 100.00 && size < 50)
					size = 50;

				SendOrder(security, 'B', entryPrice, size, ORDER_TYPE_LIMIT);

				Price targetPrice;
				U_DoubleToPrice(targetPrice, entryPrice.toDouble() + (risk.toDouble() * m_riskRewardRatio), 2);

				positionStruct str = { security, security->GetSymbol(), 'B', size, entryPrice, stopPrice, targetPrice, chartPointMinute };
				m_triggeredSecurityList.push_back(str);
				WriteToTechLogFile("sended order and add position struct");
				break;
			}
		}
	}
	WriteToTechLogFile("! CHECK LOGIC");
}

void EOH::SendOrder(Security* security, char side, Price order_price, unsigned int size, unsigned char order_type)
{
	WriteToTechLogFile("SendOrder");
	Price limitPrice = order_price;
	Price stopPrice = Price::priceZero;

	const Destination* destination = TD_GetDestinationArca();
	const DestinationRouting* routing = destination->FindRoutingByNumericName(TD_GetDefaultProActiveRoutingNumericName());

	Price m_level1BidPrice, m_level1AskPrice, m_lastPrintPrice;

	m_level1BidPrice.SetCompactPrice(security->GetL1Bid());
	m_level1AskPrice.SetCompactPrice(security->GetL1Ask());
	m_lastPrintPrice.SetCompactPrice(security->GetLastNbboPrintPrice());

	if (order_type == ORDER_TYPE_STOP)
	{
		WriteToTechLogFile("STOP ORDER");
		limitPrice = Price::priceZero;
		stopPrice = order_price;

		destination = TD_GetDestinationQsmt();
		routing = destination->FindRoutingByNumericName(0);
	}
	else if (order_type == ORDER_TYPE_MARKET) {
		limitPrice = Price::priceZero;
		stopPrice = Price::priceZero;
	}

	unsigned int orderClientId = 0;//output parameter
	m_account->SendOrder(&orderClientId,
		NULL,//orderToReplace
		false,//replaceNative
		0,//replaceSizeOffset
		security,
		PE_NOT_POSTPONED,
		0,//timeToActivate
		destination->GetMainNumericName(),
		destination->GetId(),
		side,//side
		0,//unsigned char repriceFlags
		order_type,//order type
		0,//userOrderType
		nullptr,//userOrderInfo
		nullptr,//commandName
		limitPrice,//limitPrice
		Price::priceZero,//discretionaryPrice
		stopPrice,//stopPrice
		order_type == ORDER_TYPE_STOP ? OST_SYNTHETIC : OST_NONE,//stopOrderType
		OSB_BID,//stopOrderBase
		m_level1BidPrice,
		m_level1AskPrice,
		m_lastPrintPrice,
		size,
		0,//displayQuantity
		0,//dlg->GetEnterReserveQuantity(),
		routing ? routing->GetId() : 0,
		routing ? routing->GetSubType() : 0,
		routing ? routing->GetNumericName() : 0,
		0,//destination->HasMnemonic() ? dlg->GetEnterMnemonic() : 0,
		false,//iso
		PEG_NONE,//pegType
		SignedPrice::signedPriceZero,//pegOffset
		TIF_GTX,//tifType
		0,//tifMilliseconds (for TIF_GTD only)
		WOP_CANCEL,//TD_GetWashOrderPolicy(),
		OOP_RESIZE,//TD_GetOversellSplitPolicy(),
		false,//TD_IsResizeShortToBorrowed(),
		false,//preBorrow
		Price::oneCent,//Price(30, 0 * Price::oneCentFraction),//Price::oneCent,//preBorrow Limit Price
		false,//noRedirect
		false,//closeOnly
		false,//resizeToClose
		false,//syntheticIgnoreFinra
		false,//syntheticWaitNext
		false,//imbalanceOnly,
			  //					false,//proAts
		false,//blockAggressiveOrders
		RLP_ROUND_DOWN,//TD_GetRoundLotPolicy(),
		NULL,//isoAttachment
		0,//userId
		0,//parentId
		0);//ocoId

	WriteToTechLogFile("! SendOrder");
}

positionStruct EOH::GetStructBySymbol(string positionSymbol)
{
	WriteToTechLogFile("GetStructBySymbol");
	for (unsigned int i = 0; i < m_triggeredSecurityList.size(); ++i)
	{
		positionStruct position_struct = m_triggeredSecurityList[i];
		if (position_struct.symbol == positionSymbol)
		{
			WriteToTechLogFile("find position struct");
			WriteToTechLogFile("! GetStructBySymbol");
			return position_struct;
		}
	}

	positionStruct str = { NULL, "", 'B', 0, Price::priceZero, Price::priceZero, Price::priceZero };

	WriteToTechLogFile("do not find position struct");
	WriteToTechLogFile("! GetStructBySymbol");
	return str;

}

void EOH::CheckPosition()
{
	WriteToTechLogFile("CheckPosition");
	PositionMap& positionMap = m_account->GetStockPositionsAll();
	PositionMap::CPair* it = positionMap.PGetFirstAssoc();

	unsigned int current_millisecond = TL_GetCurrentMillisecond();

	while (it)
	{
		Position* position = it->value;
		positionStruct str = GetStructBySymbol(position->GetSymbol());

		if (str.security)
		{
			if (position->GetSharesTraded())
			{
				WriteToTechLogFile("position has shares traded");
				if (position->GetSize()) {
					CheckStopTargetOrders(position, str);
					CheckKeepPositionTimeExpired(position, str);
					CheckOpenPositionTimeExpired(position, str);
				}

				else if (position->GetOrdersPendingCount())
					position->CancelOpeningOrders();
			}
			else if (position->GetOrdersPendingCount())
			{
				WriteToTechLogFile("position has pending shares");
				CheckIsTargetAlreadyReached(position, str);

				if (current_millisecond >= m_entryTimeLimit * 60000)
				{
					WriteToTechLogFile("cancel opening orders cause of EntryTimeLimit");
					position->CancelOpeningOrders();
				}
			}
		}


		it = positionMap.PGetNextAssoc(it);
	}

	WriteToTechLogFile("! CheckPosition");

}

void EOH::CheckStopTargetOrders(Position* position, positionStruct position_struct)
{
	WriteToTechLogFile("CheckStopTargetOrders");
	const OrderMap& orderMap = position->GetOrdersPending();
	const OrderMap::CPair* it = orderMap.PGetFirstAssoc();

	unsigned int abs_position_size = std::abs(position->GetSize());

	bool isTargetOrderExist = false;
	bool isStopOrderExist = false;
	bool canceled = false;

	while (it)
	{
		Order* order = it->value;
		if (order)
		{
			if (order->GetLimitPrice() == position_struct.targetPrice && order->GetPendingQuantity() == abs_position_size && !isTargetOrderExist)
			{
				WriteToTechLogFile("target order exist");
				isTargetOrderExist = true;
			}
			else if (order->GetStopPrice() == position_struct.stopPrice && order->GetPendingQuantity() == abs_position_size && !isStopOrderExist)
			{
				WriteToTechLogFile("stop order exist");
				isStopOrderExist = true;
			}
			else if (order->GetLimitPrice() == position_struct.entryPrice && order->GetQuantity() == position_struct.size)
			{
				WriteToTechLogFile("entry order exist and not executed yet");
			}
			else
			{
				m_account->CancelOrder(order);
				canceled = true;
				WriteToTechLogFile("cancel order");
				break;
			}
		}

		it = orderMap.PGetNextAssoc(it);
	}

	if (!isTargetOrderExist && !canceled)
	{
		WriteToTechLogFile("target order does not exist");
		SendOrder(position_struct.security, position_struct.side == 'B' ? 'S' : 'B', position_struct.targetPrice, abs_position_size, ORDER_TYPE_LIMIT); // Send target order
	}

	if (!isStopOrderExist && !canceled)
	{
		WriteToTechLogFile("stop order does not exist");
		SendOrder(position_struct.security, position_struct.side == 'B' ? 'S' : 'B', position_struct.stopPrice, abs_position_size, ORDER_TYPE_STOP);// Send stop order
	}

	WriteToTechLogFile("! CheckStopTargetOrders");
}

void EOH::CheckKeepPositionTimeExpired(Position* position, positionStruct position_struct)
{
	WriteToTechLogFile("CheckKeepPositionTimeExpired");
	bool isPositionTimeExpired = position_struct.security->GetChart()->back().GetMinute() >= m_keepPostitionTimeLimit ? true : false;

	if (isPositionTimeExpired) {
		const OrderMap& orderMap = position->GetOrdersPending();
		const OrderMap::CPair* it = orderMap.PGetFirstAssoc();

		unsigned int abs_position_size = std::abs(position->GetSize());

		while (it)
		{
			Order* order = it->value;
			if (order)
			{
				m_account->CancelOrder(order);
			}

			it = orderMap.PGetNextAssoc(it);
		}

		SendOrder(position_struct.security, position_struct.side == 'B' ? 'S' : 'B', Price::priceZero, abs_position_size, ORDER_TYPE_MARKET);
	}

	WriteToTechLogFile("! CheckKeepPositionTimeExpired");
}

void EOH::CheckOpenPositionTimeExpired(Position* position, positionStruct position_struct)
{
	WriteToTechLogFile("CheckOpenPositionTimeExpired");
	bool isOpenPositionTimeExpired = position_struct.security->GetChart()->back().GetMinute() >= m_entryTimeLimit ? true : false;

	if (isOpenPositionTimeExpired) {
		position->CancelOpeningOrders();
		WriteToTechLogFile("cancel opening orders");
	}

	WriteToTechLogFile("! CheckOpenPositionTimeExpired");
}

void EOH::CheckIsTargetAlreadyReached(Position* position, positionStruct position_struct)
{
	WriteToTechLogFile("CheckIsTargetAlreadyReached");
	for (unsigned int chartPointMinute = position_struct.triggerMinute; chartPointMinute <= position_struct.security->GetChart()->back().GetMinute(); ++chartPointMinute)
	{
		const ChartPoint* c_point = position_struct.security->GetChartPointAtMinute(chartPointMinute);

		if (!c_point || c_point->GetLowPrice().isZero())
		{
			WriteToTechLogFile("chart point is none or zero");
			continue;
		}

		if (c_point->GetHighPrice() >= position_struct.targetPrice)
		{
			position->CancelOpeningOrders();
			WriteToTechLogFile("cancel opening orders");
			break;
		}
	}

	WriteToTechLogFile("! CheckIsTargetAlreadyReached");
}