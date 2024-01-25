#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#ifdef TD_EXPORTS
#define TD_API __declspec(dllexport)
#else
#define TD_API __declspec(dllimport)
#endif

//#define TAKION_EXCEPTION

#include <TakionUtilsApi.h>
#include <wincrypt.h>

//#define UPDATE_PRINT_MESSAGE

#if defined(T_RELEASED) || defined(_DEBUG)
#define WATCH_UNSUBSCRIBABLE
#endif

const char* const TakionDataHeaderVersion = "1.0.7.82";

class TD_API TakionDataStaticValues
{
public:
	static bool calculateL2Top;
};


const unsigned int qstkNum = Chars4ToUInt('Q', 'S', 'T', 'K');//0x4B545351;//*(unsigned int*)"QSTK";
const unsigned int bdrgNum = Chars4ToUInt('B', 'D', 'R', 'G');

enum MessageIds : unsigned short
{
    M_SYSTEM_EVENT = 1,//MARKET_DATA_START + 1,

    // Book related messages
    M_BOOK_NEW_QUOTE,
    M_BOOK_MODIFY_QUOTE,
    M_BOOK_DELETE_QUOTE,
    M_BOOK_ORDER_EXECUTED,
    M_BOOK_ORDER_EXECUTED_WITH_PRICE,
    M_BOOK_ORDER_CANCELED,
    M_BOOK_TRADE,
    M_BOOK_CROSS_TRADE,

    // Stock related messages
    M_STOCK_DIRECTORY,
    M_STOCK_TRADING_ACTION,
    M_STOCK_IMBALANCE_INDICATOR,

    // Refresh request and response
    M_REQ_REFRESH_SYMBOL,
    M_RESP_REFRESH_SYMBOL,

    // Used internaly to notify Aggregated Book
//    M_QUOTE_SIZE_CHANGE,
    M_RESET_BOOK = 16,

    // Level1
    M_LEVEL1,

    // Trades
    M_TRADE_REPORT,
    M_TRADE_CANCEL_ERROR,
    M_TRADE_CORRECTION,

    // HACK for Blizzard
//    M_TRADE_BLIZZARD,
    
	M_REQ_UNSUBSCRIBE_SYMBOL = 22,

	M_RESET_SYMBOL,

	M_EOD_SUMMARY_REPORT,
	M_SHORT_SALE_INDICATORS,
	M_DIVIDENDS_AND_SPLITS,
	M_PREVIOUS_DAY_CLOSE,
	M_RESET_IMBALANCES,

	M_PMI,
#ifdef LRPS
	M_LRP,
#endif
	M_T_TIME = 31,
	M_RPI,

	M_AGGREGATED_PRINT,

	M_LULD,
//	M_REQ_KICK,

	M_AVERAGE_DAILY_VOLUME,
	M_PREVIOUS_DAY_HIGH_LOW,
	
	M_SECURITY_TYPE,

	M_TICK_PILOT,

	M_SNAPSHOT,

	M_52WEEK_30DAY_HIGH_LOW,

	M_TOP_10,

// Should be last enum member
    MARKET_DATA_END,

    SM_M_SYSTEM_EVENT = 201,//MARKET_DATA_START + 1,

    // Book related messages
    SM_M_BOOK_NEW_QUOTE = 202,
    SM_M_BOOK_MODIFY_QUOTE,
    SM_M_BOOK_DELETE_QUOTE,
    SM_M_BOOK_ORDER_EXECUTED,
    SM_M_BOOK_ORDER_EXECUTED_WITH_PRICE,
    SM_M_BOOK_ORDER_CANCELED,
    SM_M_BOOK_TRADE,
    SM_M_BOOK_CROSS_TRADE,

    // Stock related messages
    SM_M_STOCK_DIRECTORY,
    SM_M_STOCK_TRADING_ACTION,
    SM_M_STOCK_IMBALANCE_INDICATOR,

    // Refresh request and response
//    M_REQ_REFRESH_SYMBOL,
    SM_M_RESP_REFRESH_SYMBOL = 214,

    // Used internaly to notify Aggregated Book
//    SM_M_QUOTE_SIZE_CHANGE,
    SM_M_RESET_BOOK = 216,

    // Level1
    SM_M_LEVEL1 = 217,

    // Trades
    SM_M_TRADE_REPORT,
    SM_M_TRADE_CANCEL_ERROR,
    SM_M_TRADE_CORRECTION,

    // HACK for Blizzard
//    M_TRADE_BLIZZARD,
    
//	SM_M_REQ_UNSUBSCRIBE_SYMBOL = 222,

	SM_M_RESET_SYMBOL = 223,

	SM_M_EOD_SUMMARY_REPORT,
	SM_M_SHORT_SALE_INDICATORS,
	SM_M_DIVIDENDS_AND_SPLITS,
	SM_M_PREVIOUS_DAY_CLOSE,
	SM_M_RESET_IMBALANCES,

	SM_M_PMI,
#ifdef LRPS
	SM_M_LRP,
#endif
	SM_M_T_TIME = 231,
	SM_M_RPI,

	SM_M_AGGREGATED_PRINT,

	SM_M_LULD,

	SM_M_AVERAGE_DAILY_VOLUME,
	SM_M_PREVIOUS_DAY_HIGH_LOW,

	SM_M_SECURITY_TYPE,

	SM_M_TICK_PILOT,

	SM_M_SNAPSHOT,

	SM_M_52WEEK_30DAY_HIGH_LOW,

	SM_M_TOP_10,

// Should be last enum member
    SYMBOL_MAPPING_MD_END,

//MarketSorter messages
	M_MS_LEVEL1_SHORT = 501,
	M_MS_LEVEL1_LONG,
	M_MS_TRADE_REPORT_SHORT,
	M_MS_TRADE_REPORT_LONG,
	M_MS_IMBALANCE_SHORT,
	M_MS_IMBALANCE_LONG,
	M_MS_TRADE_CORRECTION,
	M_MS_TRADE_CANCEL_ERROR,
	M_MS_EOD_SUMMARY_REPORT,
	M_MS_SHORT_SALE_INDICATORS,
	M_MS_DIVIDENDS_AND_SPLITS,
	M_MS_PREVIOUS_DAY_CLOSE,
	M_MS_STOCK_TRADING_ACTION,
	M_MS_RESET_IMBALANCES,

	M_MS_PMI,
#ifdef LRPS
	M_MS_LRP,
#endif
	M_MS_T_TIME = 517,
	M_MS_RPI,	// Should be last enum member
	M_MS_AGGREGATED_PRINT_SHORT,
	M_MS_AGGREGATED_PRINT_LONG,

	M_MS_LULD,

	M_MS_AVERAGE_DAILY_VOLUME,
	M_MS_PREVIOUS_DAY_HIGH_LOW,

	M_MS_SECURITY_TYPE,

	M_MS_TICK_PILOT,

	M_MS_52WEEK_30DAY_HIGH_LOW,

	M_MS_TOP_10,

	MARKET_SORTER_END,
/////////////////////////
//MarketSorter messages
	SM_MS_LEVEL1_SHORT = 601,
	SM_MS_LEVEL1_LONG,
	SM_MS_TRADE_REPORT_SHORT,
	SM_MS_TRADE_REPORT_LONG,
	SM_MS_IMBALANCE_SHORT,
	SM_MS_IMBALANCE_LONG,
	SM_MS_TRADE_CORRECTION,
	SM_MS_TRADE_CANCEL_ERROR,
	SM_MS_EOD_SUMMARY_REPORT,
	SM_MS_SHORT_SALE_INDICATORS,
	SM_MS_DIVIDENDS_AND_SPLITS,
	SM_MS_PREVIOUS_DAY_CLOSE,
	SM_MS_STOCK_TRADING_ACTION,
	SM_MS_RESET_IMBALANCES,

	SM_MS_PMI,
#ifdef LRPS
	SM_MS_LRP,
#endif
	SM_MS_T_TIME = 617,
	SM_MS_RPI,

	SM_MS_AGGREGATED_PRINT_SHORT,
	SM_MS_AGGREGATED_PRINT_LONG,

	SM_MS_LULD,

	SM_MS_AVERAGE_DAILY_VOLUME,
	SM_MS_PREVIOUS_DAY_HIGH_LOW,

	SM_MS_SECURITY_TYPE,

	SM_MS_TICK_PILOT,

	SM_MS_52WEEK_30DAY_HIGH_LOW,

	SM_MS_TOP_10,

	SYMBOL_MAPPING_MS_END,// Should be last enum member
/////////////////////////
	M_REQ_CHART = 701,
	M_RESP_CHART,
	M_NEW_TICK,
	M_TICK_CORRECTION,
		
	SM_REQ_CHART = 751,
	SM_RESP_CHART = 752,
	SM_NEW_TICK,
	SM_TICK_CORRECTION,

	M_INDEX = 802,// Index Update, includes only last
	M_REQ_REFRESH_INDEX,// Refresh request and response
	M_RESP_REFRESH_INDEX,
	M_REQ_INDEX_CHART,// Index Chart Messages
	M_RESP_INDEX_CHART,

	// Should be last enum member
//	CHARTS_END,
	M_INDEX_NEW_TICK,

	M_REQ_MD_LOGON = 1001,
	M_RESP_MD_LOGON,
	M_REQ_PUBLIC_KEY,
	M_RESP_PUBLIC_KEY,
	M_REQ_REPORT_EXTENSION_INFO,

	M_HEARTBEAT = 2001,
	M_DISCONNECT,
	M_TEXT,

//#define TS_MESSAGE_START				10000
	TS_LOGIN_REQ						= 10001,
	TS_LOGIN_REJECT,
	TS_LOGIN_RESP,
	TS_LOGOUT_REQ,
	TS_ACCOUNT_RISK_PROFILE,
	TS_NEW_ACCOUNT,
	TS_ACCOUNT_POSITION_REQ,
	TS_ACCOUNT_POSITION,
	TS_ACCOUNT_POSITION_RESP,
	TS_ACCOUNT_RECOVERY_FULL_REQ,
	TS_ACCOUNT_RECOVERY_QUICK_REQ,
	TS_ACCOUNT_RECOVERY_RESP,
	TS_ORDER,
	TS_ORDER_ACK,
	TS_ORDER_UPDATE,
	TS_ORDER_REJECT,
	TS_ORDER_REPORT,
	TS_ORDER_CANCEL_REQ,
	TS_ORDER_REPLACE_REQ,
	TS_ORDER_CANCEL_ACK,
	TS_ORDER_KILL,
	TS_ORDER_REPLACE_ACK,
	TS_ORDER_REPLACED,
	TS_CANCEL_REJECT,
	TS_ACCOUNT_EXEC_HISTORY_REQ,
	TS_ACCOUNT_EXEC_HISTORY_COMPLETE,
	TS_ACCOUNT_ORDER_HISTORY_REQ,
	TS_ACCOUNT_ORDER_HISTORY_COMPLETE,

//#ifdef FIRM_VALUES
	TS_FIRM_POSITION_SUBSCRIBE_REQ,
	TS_FIRM_POSITION_UPDATE,
	TS_FIRM_POSITION_UNSUBSCRIBE_REQ,
	TS_FIRM_ENFORCEMENT,
	TS_FIRM_POSITION_REJECT,
	TS_SET_UNTRADEABLE_STATUS,
	TS_UNTRADEABLE_STATUS_UPDATE,
	TS_ADV_INFO_UPDATE,
//#endif
	TS_REMOVE_ACCOUNT,//not used
	TS_BORROW_ACCEPT_REQ,
	TS_BORROW_ACCEPT_RESP,

	TS_AUTHENTICATE_TRADER_REQ,
	TS_AUTHENTICATE_TRADER_RESP,
	TS_UNLOAD_ACCOUNT_REQ,
	TS_SUPERVISOR_ACCOUNT_CONTROL,

	M_TR_HTB_LOCATE_INFO				= 12001,
	M_TR_HTB_REQ_SYMBOL_LIST,//			= 12002,
	M_TR_HTB_RESP_SYMBOL_LIST,//			= 12003,
	M_TR_ETB_REQ_SYMBOL_LIST,//			= 12004,
	M_TR_ETB_RESP_SYMBOL_LIST,
	M_TR_HTB_REQ_LOCATE_INFO,
	M_TR_HTB_RESP_LOCATE_INFO,
	M_TR_RESTR_REQ_SYMBOL_LIST,
	M_TR_RESTR_RESP_SYMBOL_LIST,
	M_TR_BETA_INFO,

	M_REQ_PRINTS = 14001,
	M_RESP_PRINTS,
	M_REQ_CANDLE_HISTORICAL_DATA,
	M_RESP_CANDLE_HISTORICAL_DATA,
	M_REQ_CANDLE_INTRADAY_DATA,
	M_RESP_CANDLE_INTRADAY_DATA,
#ifndef TAKION_NO_OPTIONS
//Options
	M_OPT_LEVEL2 = 15001,
	M_OPT_LEVEL1,
	M_OPT_TRADE_REPORT,
	M_OPT_OPEN_INTEREST,
	M_REQ_OPT_REFRESH_SYMBOL,
	M_RESP_OPT_REFRESH_SYMBOL,
	M_REQ_OPT_UNSUBSCRIBE_SYMBOL,
	M_OPT_RESET_SYMBOL,
	M_OPT_EOD_SUMMARY_REPORT,
	M_OPT_PREVIOUS_DAY_CLOSE,
//Single Option
	M_REQ_REFRESH_OPTION,
	M_RESP_REFRESH_OPTION,
	M_REQ_UNSUBSCRIBE_OPTION,

	MARKET_DATA_OPTIONS_END,
//Futures
	M_FUT_BOOK_MODIFY_QUOTE	= 19001,
	M_FUT_BOOK_DELETE_QUOTE,
	M_FUT_LEVEL1,
	M_FUT_TRADE_REPORT,
	M_FUT_OPEN_INTEREST,
	M_REQ_FUT_REFRESH_SYMBOL,
	M_RESP_FUT_REFRESH_SYMBOL,
	M_REQ_FUT_UNSUBSCRIBE_SYMBOL,
	M_FUT_RESET_SYMBOL,
// Summary reports
	M_FUT_EOD_SUMMARY_REPORT,
	M_FUT_PREVIOUS_DAY_CLOSE,
// Trading Action
	M_FUT_TRADING_ACTION,
// LULD
	M_FUT_LULD_PRICE_BAND,

	M_REQ_FUT_CHART,
	M_RESP_FUT_CHART,
	M_RESP_FUT_PRICE_VOLUME,

	M_FUT_SETTLEMENT_PRICE,

	M_REQ_FUT_PRINTS,
	M_RESP_FUT_PRINTS,
	M_REQ_FUT_HISTORICAL_DATA,
	M_RESP_FUT_HISTORICAL_DATA,
	M_REQ_FUT_INTRADAY_DATA,
	M_RESP_FUT_INTRADAY_DATA,
	M_REQ_FUT_HISTORICAL_PRICE_VOLUME,
	M_RESP_FUT_HISTORICAL_PRICE_VOLUME,

	MARKET_DATA_FUTURES_END,

#endif
	TM_TAKION_CLIENT_TEXT_ERROR = 63989,
	TM_TAKION_CLIENT_TEXT_MESSAGE,
//	TM_TAKION_SERVER_TEXT_ERROR,
//	TM_TAKION_SERVER_TEXT_MESSAGE,

//	TM_TAKION_FIX_MESSAGE = 63996,
	TM_TAKION_CLIENT_FIX_ERROR,// = 63993,
	TM_TAKION_CLIENT_FIX_CONTROL_SUM_ERROR,
	TM_TAKION_CLIENT_FIX_MESSAGE,
	TM_TAKION_SERVER_FIX_ERROR,
	TM_TAKION_SERVER_FIX_CONTROL_SUM_ERROR,
	TM_TAKION_SERVER_FIX_MESSAGE,
	TM_TAKION_SERVER_MESSAGE,

	TM_CONNECTED						= 64001,
	TM_DISCONNECTED,
	TM_STARTED_TO_CONNECT,
	TM_FAILED_TO_CONNECT,
	TM_CONNECTION_DESTROYED,
	TM_RECONNECT,

//	TM_EXIT_THREAD,

	TM_THREAD_MD_ENTITLEMENTS_CHANGED,
	TM_THREAD_BOOK_CLEANUP,
	TM_THREAD_MARKET_STATUS,//sent to all stocks' threads when market closes or opens

	TM_NEW_STOCK,//notification in main thread with the stock object
	TM_STOCK_NEW,//message sent to the main thread with the stock symbol
	TM_STOCK_INVALID,
	TM_STOCK_REFRESHED,
	TM_EQUITY_REFRESHED,
	TM_EQUITY_UPDATE,
	TM_EQUITY_IMBALANCE_UPDATE,
//	TM_EQUITY_ADD_PRINT_LONG,
//	TM_EQUITY_ADD_PRINT_SHORT,
	TM_STOCK_OPENED,
	TM_STOCK_CLOSED,

	TM_STOCK_UPDATE_LEVEL2,
	TM_STOCK_UPDATE_LEVEL1,
//#ifdef UPDATE_PRINT_MESSAGE
	TM_STOCK_ADD_PRINT,
	TM_STOCK_ADD_BOOK_EXECUTION,
//#endif
	TM_STOCK_DELETE,

	TM_POSITION_UPDATE,
	TM_POSITION_NEW,

	TM_POSITION_DELETE,

	TM_POSITION_OPEN_PNL_LEVEL1,
	TM_POSITION_OPEN_PNL_PRINT,
	TM_POSITION_OPEN_PNL_TCLOSE,

	TM_EQUITY_NEW,

	TM_DELETE_ALL_ACCOUNTS,
	TM_ACCOUNT_DELETE,

	TM_NEW_EQUITY,
	TM_NEW_ACCOUNT,
	TM_NEW_POSITION,
	TM_NEW_ORDER,
	TM_NEW_EXECUTION,
	TM_DEAD_ORDER,

//	TM_ADD_POSITION_TO_SECURITY,

	TM_UPDATED_POSITION,
	TM_EXECUTED_POSITION,
	TM_UPDATED_ORDER,
	TM_UPDATED_ACCOUNT,
	TM_UPDATED_ACCOUNT_AND_POSITION,
	TM_UPDATED_EQUITY,
	TM_REFRESHED_EQUITY,

	TM_ORDER_UPDATE,
	TM_ORDER_NEW,
	TM_ORDER_ERROR,
	TM_ORDER_DELETE,

	TM_EXECUTION_NEW,

	TM_ACCOUNT_UPDATE,

	TM_SEND_SWIPE_ORDER,
	TM_SEND_ORDER_ALGORITHM,
	TM_ORDER_ALGORITHM_CANCEL,

	TM_ORDER_TO_CANCEL,
	TM_CANCEL_ERROR,

	TM_ORDER_STUCK,

	TM_TIER_SIZE_CHANGED_OBSOLETE,

	TM_CONNECTION_OBJECT,

	TM_MARKET_SORTER_LOADED,
	TM_MARKET_SORTER_CHUNK_LOADED,

	TM_STOCK_RESET_IMBALANCES,
	TM_EQUITY_RESET_IMBALANCES,

	TM_MS_TRADE_LONG_INTERNAL,
	TM_MS_TRADE_SHORT_INTERNAL,

	TM_EQUITY_CHART_LOADED,
	TM_EQUITY_NEW_MINUTE,

//	TM_EQUITY_HISTORICAL_CHART_LOADED,
//	TM_EQUITY_HISTORICAL_INTRADAY_CHART_LOADED,

	TM_STOCK_HTB,
	TM_EQUITY_HTB,

	TM_STOCK_BORROW_PRICE,
	TM_EQUITY_BORROW_PRICE,

	TM_MARKET_STATUS,

	TM_QUOTE_MOVE,

//	TM_CUSTOM_INTERNAL,

//	TM_CUSTOM_EXTERNAL,

	TM_NEXT_DAY_STARTED,
	TM_NEXT_UTC_DAY_STARTED,

	TM_DEFAULT_COMMISSION_FEE,
	TM_ACCOUNT_CONSTRAINTS,

	TM_MARKET_SORTER_CLEANUP,

	TM_DATA_THREAD_BUFFER_OVERFLOW,

	TM_INDEX_NEW,
	TM_INDEX_REFRESHED,
	TM_INDEX_UPDATE,
	TM_INDEX_CHART_LOADED,
	TM_NEW_INDEX,
	TM_UPDATED_INDEX,
	TM_REFRESHED_INDEX,
	TM_MARKET_SORTER_INDEXES_LOADED,
	TM_MARKET_SORTER_INDEX_CHUNK_LOADED,
	TM_INDEX_NEW_MINUTE,

	TM_EQUITY_NEW_DAY,
	TM_INDEX_NEW_DAY,

	TM_INDEX_NEW_SERVER_MINUTE,

	TM_MARKET_SORTER_STOCK_CHARTS_LOADED,
	TM_MARKET_SORTER_INDEX_CHARTS_LOADED,

	TM_ACCOUNT_COMMAND_DESTROY_CANCELED_ORDER,

	TM_ACCOUNT_COMMAND_PHANTOM_SHARES,
	TM_ACCOUNT_COMMAND_ALL_PHANTOM,

	TM_POSITION_SORTABLE_SECURITY_INITIALIZED,
	TM_POSITION_SECURITY_INITIALIZED,
	TM_POSITION_SECURITY_UPDATED,
	TM_POSITION_PHANTOM_SHARES_CHANGED,

	TM_CHART_CANDLE_UPDATED,

	M_HISTORICAL_CHART_PACK_LOADED,
	M_HISTORICAL_CHART_DELETE,

	TM_SYMBOL_TYPED,

	TM_POSITION_BORROW_PRICE,
	TM_POSITION_HTB,

	TM_SET_STOCK_TIER_SIZE,
	TM_SET_EQUITY_TIER_SIZE,

	TM_ACCOUNT_CHECK_LOSS,

	TM_AUTO_ACTION,

	TM_ACCOUNT_SECURITY_UPDATE_FOR_ALGO,
	TM_ACCOUNT_ALGO_MAIN_THREAD_NOTIFICATION,

	TM_POSITION_COST,
	TM_ACCOUNT_COMMAND_INVENTORY,

	TM_REMOVE_QUOTE,

	TM_POSITION_REMOVE_DELAYED_ORDERS,

	TM_ACCOUNT_BORROW_TO_COVER_OVERNIGHT,
	TM_POSITION_BORROW_TO_COVER_OVERNIGHT,
	TM_POSITION_CANCEL_DELAYED_ILLEGAL_ORDERS,
	TM_POSITION_RESTRICTED,

	TM_SYSTEM_TIME_CHANGED,

	TM_STOCK_UPDATE_HEADLINES,
	TM_STRING_UPDATE_HEADLINES,
	TM_HEADLINE,
//	TM_NEWS_STORY,
	TM_UPDATE_LAST_NEWS_STORY,
	TM_NEWS_STORY_CONTENTS,

	TM_NEWS_PROFILES_LOADED,

	TM_STOCK_NEWS_HISTORIC_SEARCH_DONE,
	TM_STRING_NEWS_HISTORIC_SEARCH_DONE,

	TM_ACCOUNT_REMOVE_DELAYED_ORDERS,
	TM_ACCOUNT_CANCEL_STOP_ORDERS,

	TM_ACCOUNT_WAIT_MS_CLEANUP,

	TM_DATA_CORRUPTION,

	TM_HARD_BP_HIT,

	TM_EQUITY_OPENED,
	TM_EQUITY_CLOSED,//sent from stock thread to main thread when the stock's close price is set
	TM_EQUITY_YEST_CLOSE_PRICE_CHANGED,

	TM_EQUITY_NEW_TIME_FRAME,

	TM_CLIENT_CONNECTED,
	TM_CLIENT_DISCONNECTED,
#ifdef FIRM_VALUES
	TM_ACCOUNT_UPDATE_FIRM_ENFORCEMENT,
	TM_NEW_FIRM_POSITION,
	TM_FIRM_POSITION_NEW,
	TM_UPDATED_FIRM_POSITION,
	TM_FIRM_POSITION_UPDATE,
	TM_POSITION_FIRM_LOADED,
	TM_SYMBOL_CHECK_UNTRADEABLE,
	TM_UNTRADEABLE_LIST_LOADED,
	TM_ALL_UNTRADEABLE_LISTS_LOADED,
#endif
#ifndef TAKION_NO_OPTIONS
	TM_UNDERLIER_INVALID,
	TM_UNDERLIER_REFRESHED,
	TM_OPTION_UPDATE_LEVEL2,
	TM_OPTION_UPDATE_LEVEL1,
	TM_OPTION_REFRESHED,
	TM_OPTION_INVALID,

	TM_UNDERLIER_DELETE,
	TM_UNDERLIER_NEW_DAY,
	TM_OPTION_ADD_TO_UNDERLIER,
	TM_OPTION_SET_UNDERLIER_POSITION,
	TM_OPTION_POSITION_UPDATE_CONTRACT_SIZE,

	TM_OPTION_ADD,
	TM_OPTION_REMOVE,
	TM_OPTION_L2_ADD,
	TM_OPTION_L2_REMOVE,
	TM_OPTION_ADD_IDLE,
	TM_OPTION_REMOVE_IDLE,

	TM_UNDERLIER_ADD,
	TM_UNDERLIER_REMOVE,
	TM_UNDERLIER_ADD_IDLE,
	TM_UNDERLIER_REMOVE_IDLE,
	TM_UNDERLIER_ADD_REMOVABLE,
	TM_UNDERLIER_REMOVE_REMOVABLE,

	TM_POSITION_INIT_INVALID_OPTION,//sent to account thread to initialize positions PNL as updated when a "failed" option snapshot is received
	TM_OPTION_NEW_DAY,
#endif
	TM_CANCEL_REJECTED,
	TM_ACCOUNT_RESTRICTED_SYMBOL_LIST_LOADED,

	TM_POSITION_CLOSING_PRICE,

	TM_ACCOUNT_ADD_OCO_ORDERS,
	TM_ACCOUNT_REMOVE_OCO_ORDERS,
	TM_ACCOUNT_CLEAR_OCO_ORDERS,
	TM_ACCOUNT_CLEAR_ALL_OCO_ORDERS,
	TM_ACCOUNT_SET_CURRENT_OCO_ID,
	TM_ACCOUNT_RESET_CURRENT_OCO_ID,

	TM_ACCOUNT_DESTROY_UNTRADED_POSITIONS,
	TM_ACCOUNT_DESTROY_UNTRADED_POSITION,

	TM_POSITION_AUTO_CLOSE_ON_STOCK_OPEN,

	TM_STOCK_ADD_IDLE,
	TM_STOCK_REMOVE_IDLE,

	TM_POSITION_INIT_SORTABLE_SECURITY,//sent to main thread to initialize positions' MS security when MS security snapshot is received
	TM_POSITION_INIT_SECURITY,//sent to main thread to initialize positions' stock when stock snapshot is received
	TM_POSITION_INIT_INVALID_SECURITY,//sent to account thread to initialize positions PNL as updated when a "failed" stock snapshot is received

	TM_THREAD_NEW_DAY,
	TM_STOCK_NEW_DAY,

	TM_INDEX_DELETE,

	TM_REPLACE_PRICE_AND_SIZE,
	TM_ACCOUNT_SIMULATION,

	TM_IP_CHANGE,

	TM_ACCOUNT_ALGO_ACCOUNT_THREAD_NOTIFICATION,

	TM_RSI_MH_CHART_LOADED,
	TM_RSI_MH_CHART_REQUESTED,
	TM_RSI_MH_CHART_FAILED,
	TM_RSI_MH_CHARTS_CLEARED,
	TM_RSI_MH_ALL_CHARTS_LOADED,

	TM_RSI_MH_SECURITY_DATA_LOADED,

	TM_RSI_DAYS_CHART_LOADED,
	TM_RSI_DAYS_CHART_REQUESTED,
	TM_RSI_DAYS_CHART_FAILED,
	TM_RSI_DAYS_CHARTS_CLEARED,
	TM_RSI_DAYS_ALL_CHARTS_LOADED,

	TM_RSI_DAYS_SECURITY_DATA_LOADED,

	TM_POSITION_TRAILING_ORDERS_PRINT,
	TM_POSITION_TRAILING_ORDERS_LEVEL1,

	TM_QUOTE_INFO,//used as additional info when notifying InThread observers about Level2 changes

	TM_SORTABLE_SECURITY_ADD_IDLE,
	TM_SORTABLE_SECURITY_REMOVE_IDLE,
	TM_SORTABLE_SECURITY_INVALID,
	TM_SORTABLE_SECURITY_DELETE,

	TM_SORTABLE_SECURITY_SYMBOL_MAPPING_CHANGED,

	TM_STOCK_LIGHT_SNAPSHOT,

	TM_POSITION_OPEN_PNL_IMBEXNEAR,

	TM_EQUITY_MINUTE_EVENT,
	TM_TIME_NBBO_PRINT,

	TM_SEND_ORDER_DONE, //Posted to the Observers of Position and Account in worker and main thread when all the orders resulting from SendOrder or ReplacePriceAndSize function are sent.

	TM_SORTABLE_SECURITY_NEWS_HEADLINE_COUNT, //Posted to worker thread of MarketSorter stock from main thread
	TM_SECURITY_NEWS_HEADLINE_COUNT, //Posted to worker thread of MarketData stock from main thread

	TM_ACCOUNT_COMMAND_DESTROY_BLOCKED_ORDER,
	TM_ACCOUNT_RETAIL_IN_SIMULATION,

	TM_SORTABLE_SECURITY_ENTITLEMENTS_CHANGED,
	TM_STOCK_ENTITLEMENTS_CHANGED,
#ifndef TAKION_NO_OPTIONS
	TM_OPTION_ENTITLEMENTS_CHANGED,
	TM_UNDERLIER_UNSUBSCRIBED,
#endif

	TM_ADDITIONAL_DATA_UCHAR,
	TM_EQUITY_RESET,

	TM_EQUITY_USED_COUNT_UPDATE,
	TM_STOCK_USED_COUNT_UPDATE,

	TM_THREAD_EXT_MD_ENTITLEMENTS_CHANGED,

	TM_SORTABLE_SECURITY_EXT_ENTITLEMENTS_CHANGED,
	TM_STOCK_EXT_ENTITLEMENTS_CHANGED,
	
//	TM_OTHER_ORDER_EXECUTED,//Looks like this message is not used

	TM_ALL_ACCOUNTS_LOADED,

	TM_SET_EQUITY_TEMPORARY_TIER_SIZE,
	TM_SET_STOCK_TEMPORARY_TIER_SIZE,

//	TM_STOCK_YEST_CLOSE_PRICE_CHANGED,
	TM_POSITION_TODAYS_CLOSING_PRICE,

	TM_SET_STOCK_CUSTOM_PRICE_BASE,
	TM_SET_EQUITY_CUSTOM_PRICE_BASE,

	TM_CLEARING_FIRM_UPDATE,
	TM_CLEARING_FIRM_CONSTRAINTS_UPDATE,
	TM_NEW_CLEARING_FIRM,
	TM_UPDATED_CLEARING_FIRM,
	TM_UPDATED_CLEARING_FIRM_CONSTRAINTS,
	TM_DELETE_ALL_CLEARING_FIRMS,

	TM_ACCOUNT_LOSS_90_PERCENT,

	TM_ENTITLEMENTS_CHANGED,
	TM_EXT_ENTITLEMENTS_CHANGED,

	TM_SET_STOCK_CUSTOM_DATE,
	TM_SET_EQUITY_CUSTOM_DATE,

	TM_STOCK_BORROW_INFO,
	TM_EQUITY_BORROW_INFO,
	TM_POSITION_BORROW_INFO,

	TM_STOCK_BETA_AND_RETAIL_INFO,
	TM_EQUITY_BETA_AND_RETAIL_INFO,
	TM_POSITION_BETA_AND_RETAIL_INFO,

	TM_CLEARING_FIRM_RETAIL_UPDATE,
	TM_UPDATED_CLEARING_FIRM_RETAIL,

	TM_POSITION_UPDATE_LEVERAGE,
	TM_THREAD_CALCULATE_POSITION_LEVERAGE,//sent to all worker threads when the need to calculate Position Leverage changes

	TM_HARD_ME_HIT,//obsolete

	TM_BOOKTOP_INFO,//used (as primary, not additional, info) for notification of InThread Observers if there are no Book Depth Entitlements, instead of TM_QUOTE_INFO

	TM_STOCK_ECHO,
	TM_SORTABLE_STOCK_ECHO,

	TM_CONFIRM_BORROW,
	TM_SIMULATE_EXECUTION,

	TM_EXPIRATION_TIMER,

	TM_NASDAQ_MARKET_STATUS_CHANGED,

	TM_ACCOUNT_HIGHEST_OCO_ID,

	TM_THREAD_UNLOAD_TODAYS_CHARTS,
	TM_MARKET_SORTER_CHARTS_UNLOADED,

	TM_MAKET_SORTER_EXPECTED_SECURITY_COUNT,
	TM_MAKET_SORTER_EXPECTED_INDEX_COUNT,

	TM_REPLACE_ABSOLUTE_PRICE_AND_SIZE,

	TM_ORDER_DELAYED_CANCEL,
		
	TM_THREAD_UPDATE_IMBALANCE_CHANGE,

	TM_ALL_ACCOUNTS_INVESTMENT,
	TM_ALL_ACCOUNTS_INVESTMENT_MAX,

	TM_THREAD_PRINT_AND_LEVEL1_REPORTING_PRICE_GRANULARITY,

	TM_MARKET_SORTER_DELAY,

	TM_OBJECT_ECHO,
	TM_ORDER_USER_DATA_NULLIFIED,

	TM_INFO_UCHAR,
	TM_INFO_CHAR,

	TM_RESEND_ORDER,
	TM_ACCOUNT_RESEND_BAML_ORDERS,

	TM_SECURITY_TRADING_STATE,
//	TM_STOCK_PREV_TRADING_ACTION,
	TM_EQUITY_PREV_TRADING_ACTION,

	TM_STOCK_YEST_CLOSE_PRICE_CHANGED,//Includes Futures

	TM_PING_WORKER_THREAD,
	TM_PONG_WORKER_THREAD,
	TM_ADDITIONAL_DATA_UINT,

	TM_INDEX_RESET,

	TM_POSITION_REPRICE_ORDERS_ON_LULD,
	TM_REPLACE_ABSOLUTE_PRICE,

	TM_MARKET_STATE_INCONSISTENT_WITH_TIME,
	TM_MARKET_STATE_TIME_FRAME,

	TM_POSITION_TEST,

#ifndef TAKION_NO_OPTIONS
	TM_OPTION_OPEN_INTEREST_CHANGED,
	TM_FUTURE_OPEN_INTEREST_CHANGED,

	TM_OPTION_ECHO,
	TM_FUTURE_ECHO,
#endif
#ifdef CLEARING_FIRM_IN_WORKER_THREAD
	TM_CLEARING_FIRM_INCREMENT_BETA_BP_USED,
	TM_CLEARING_FIRM_INCREMENT_BETA_INVESTMENT,
	TM_CLEARING_FIRM_ADD_ACCOUNT,
	TM_CLEARING_FIRM_REMOVE_ACCOUNT,
	TM_CLEARING_FIRM_DELETE_ALL_ACCOUNTS,
	TM_CLEARING_FIRM_SET_BOOL_PARAMS,
	TM_CLEARING_FIRM_SET_BETA_PARAMS,
	TM_CLEARING_FIRM_SET_RETAIL_PARAMS,
	TM_CLEARING_FIRM_ACCOUNT_UPDATE_FIRM_ENFORCEMENT,
#endif
#ifndef TAKION_NO_OPTIONS
	TM_POSITION_UNDERLIER_SORTABLE_SECURITY_INITIALIZED,
	TM_POSITION_UNDERLIER_SECURITY_INITIALIZED,
	TM_OPTION_OPENED,
	TM_OPTION_CLOSED,
	TM_OPTION_EXT_ENTITLEMENTS_CHANGED,
	TM_UNDERLIER_OBJECT,//For additionalInfo only

	TM_UNDERLIER_SUBSCRIPTION_QUEUED,
	TM_OPTION_SUBSCRIPTION_QUEUED,
	TM_UNDERLIER_SUBSCRIPTION_UNQUEUED,
	TM_OPTION_SUBSCRIPTION_UNQUEUED,
	TM_OPTION_SUBSCRIPTION_QUEUE_CLEARED,
	TM_OPTION_SUBSCRIPTION_STUCK,

	TM_POSITION_UNDERLIER_PRINT,
//	TM_LONG_POSITION_UNDERLIER_PRINT,
//	TM_SHORT_POSITION_UNDERLIER_PRINT,
	TM_OPTION_USED_COUNT_UPDATE,

	TM_FUTURE_UPDATE_LEVEL1,
	TM_FUTURE_UPDATE_LEVEL2,
	TM_FUTURE_USED_COUNT_UPDATE,
	TM_FUTURE_ENTITLEMENTS_CHANGED,
	TM_FUTURE_EXT_ENTITLEMENTS_CHANGED,
	TM_FUTURE_REFRESHED,
	TM_FUTURE_CLOSED,
	TM_FUTURE_OPENED,
	TM_FUTURE_INVALID,
	TM_FUTURE_DELETE,
//	TM_FUTURE_ADD,
//	TM_FUTURE_REMOVE,
//	TM_FUTURE_L2_ADD,
//	TM_FUTURE_L2_REMOVE,
	TM_FUTURE_ADD_IDLE,
	TM_FUTURE_REMOVE_IDLE,
	TM_NEW_FUTURE,
	TM_FUTURE_NEW,
	TM_POSITION_INIT_INVALID_FUTURE,
	TM_ALL_FUTURE_ACCOUNTS_LOADED,
	TM_DELETE_ALL_FUTURE_ACCOUNTS,
	TM_FUTURE_POSITION_UPDATE_CONTRACT_SIZE,
	TM_FUTURE_CHART_LOADED,
	TM_FUTURE_PRICE_VOLUME_LOADED,
	TM_FUTURE_TIME_NBBO_PRINT,
	TM_FUTURE_DEFAULT_COMMISSION_FEE,
	TM_THREAD_NEW_FUTURE_SESSION,
	TM_FUTURE_NEW_SESSION,
	TM_NEXT_FUTURE_SESSION_STARTED,
	M_HISTORICAL_CHART_PRICE_VOLUME_PACK_LOADED,

	TM_OPTION_LEVEL1_REFRESHED,
	TM_POSITION_INIT_OPTION,
	TM_POSITION_OPTION_INITIALIZED
#endif
};

//#define LYNX_REROUTING

enum DmaFlags : unsigned char
{
	FLAG_DMA = 1,
	FLAG_DMA_PLUS,
	FLAG_APEX,
#ifdef LYNX_REROUTING
	FLAG_LYNX,// = 4
#endif
	FLAG_DMA_Count,
};

class TMsgRemoveQuote : public Message
{
public:
	TMsgRemoveQuote(const unsigned __int64& symbol = 0,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock = 0,
#endif
		const bool& side = false,
		const unsigned char& bookId = BOOK_LEVEL2,
		const unsigned int& mmid = 0,
		const unsigned int& dollarsFrom = 0,
		const unsigned int& dollarFractionFrom = 0,
		const unsigned int& dollarsTo = 0,
		const unsigned int& dollarFractionTo = 0):
		Message(TM_REMOVE_QUOTE, sizeof(TMsgRemoveQuote)),
		m_symbol(symbol),
#ifndef TAKION_NO_OPTIONS
		m_optionBlock(optionBlock),
#endif
		m_mmid(mmid),
		m_dollarsFrom(dollarsFrom),
		m_dollarFractionFrom(dollarFractionFrom),
		m_dollarsTo(dollarsTo),
		m_dollarFractionTo(dollarFractionTo),
		m_side(side),
		m_bookId(bookId)
	{
	}
	unsigned __int64 m_symbol;
#ifndef TAKION_NO_OPTIONS
	unsigned __int64 m_optionBlock;
#endif
	unsigned int m_mmid;
	unsigned int m_dollarsFrom;
	unsigned int m_dollarFractionFrom;
	unsigned int m_dollarsTo;
	unsigned int m_dollarFractionTo;
	bool m_side;
	unsigned char m_bookId;
};

class TMessageTime : public Message
{
public:
	unsigned int m_time;
protected:
	TMessageTime(const unsigned int& time, const unsigned short& type, const unsigned short& length):
		Message(type, length),
		m_time(time ? time : TL_GetCurrentMillisecond())
	{
	}
};

class TSmMessageSymbol : public Message
{
public:
	unsigned short m_symbol;
protected:
	TSmMessageSymbol(const unsigned short& symbol, const unsigned short& type, const unsigned short& length):
		Message(type, length),
		m_symbol(symbol)
	{
	}
};
/*
class TSmMessageTimeSymbol : public TMessageTime
{
public:
	unsigned short m_symbol;
protected:
	TSmMessageTimeSymbol(const unsigned short& symbol, const unsigned int& time, const unsigned short& type, const unsigned short& length):
		TMessageTime(time, type, length),
		m_symbol(symbol)
	{
	}
};
*/
enum TradeReportFlags : unsigned char
{
	NoPriceChanges		= 0,
	LastPriceChanged	= 1,
	LowPriceChanged		= 2,
	HighPriceChanged	= 4,
	TradeThroughExempt	= 8,
};

//#define MAX_SRORDID_SIZE		16
#define MAX_ACCOUNT_SIZE		16
#define MAX_IP_ADDRESS_SIZE		16			// *AK*
#define MAX_FIRM_ID_SIZE		5			// *AK*
#define MAX_TRADER_ID_SIZE		5			// *AK*
#define MAX_MMID_SIZE			5			// *AK*
//#define MAX_MARKET_REFERENCE_ID	24			// *AK* //Moved to TakionUtilsApi.h
#define MAX_USERNAME_SIZE		12
#define MAX_PASSWORD_SIZE		12
#define MAX_USER_TITLE_SIZE		16
#define	MAX_TRADER_SIZE			16
#define MAX_SYMBOL_SIZE			8
#define MAX_RESULT_TEXT_SIZE	256
#define MAX_EMAILADDRESS_SIZE	61
#define MAX_PHONENUMBER_SIZE	21
#define MAX_PASSWORDHASH_SIZE	64

typedef char Symbol[MAX_SYMBOL_SIZE];

class TMsgQuoteInfo : public Message//used as additional info when notifying InThread observers about Level2 changes
{
public:
	TMsgQuoteInfo(const unsigned int& oldPriceDollars,
		const unsigned int& oldPriceFraction,
		const unsigned int& oldSize,
		const unsigned int& newPriceDollars,
		const unsigned int& newPriceFraction,
		const unsigned int& newSize,
		const unsigned int& mmid,
		const unsigned int& oldMillisecond,
		const unsigned int& newMillisecond,
		const unsigned char& bookId,
		const unsigned char& oldQuoteCondition = 0,
		const unsigned char& newQuoteCondition = 0,
		const bool& oldRetailLiquidity = false,
		const bool& newRetailLiquidity = false):
		Message(TM_QUOTE_INFO, sizeof(TMsgQuoteInfo)),
//		m_oldPriceDollars(oldPriceDollars),
//		m_oldPriceFraction(oldPriceFraction),
		m_oldPrice(oldPriceDollars, oldPriceFraction),
		m_oldSize(oldSize),
//		m_newPriceDollars(newPriceDollars),
//		m_newPriceFraction(newPriceFraction),
		m_newPrice(newPriceDollars, newPriceFraction),
		m_newSize(newSize),
		m_mmid(mmid),
		m_oldMillisecond(oldMillisecond),
		m_newMillisecond(newMillisecond),
		m_bookId(bookId),
		m_oldQuoteCondition(oldQuoteCondition),
		m_newQuoteCondition(newQuoteCondition),
		m_oldRetailLiquidity(oldRetailLiquidity),
		m_newRetailLiquidity(newRetailLiquidity)
	{
	}
	TMsgQuoteInfo(const Price& oldPrice,
		const unsigned int& oldSize,
		const Price& newPrice,
		const unsigned int& newSize,
		const unsigned int& mmid,
		const unsigned int& oldMillisecond,
		const unsigned int& newMillisecond,
		const unsigned char& bookId,
		const unsigned char& oldQuoteCondition = 0,
		const unsigned char& newQuoteCondition = 0,
		const bool& oldRetailLiquidity = false,
		const bool& newRetailLiquidity = false):
		Message(TM_QUOTE_INFO, sizeof(TMsgQuoteInfo)),
		m_oldPrice(oldPrice),
		m_oldSize(oldSize),
		m_newPrice(newPrice),
		m_newSize(newSize),
		m_mmid(mmid),
		m_oldMillisecond(oldMillisecond),
		m_newMillisecond(newMillisecond),
		m_bookId(bookId),
		m_oldQuoteCondition(oldQuoteCondition),
		m_newQuoteCondition(newQuoteCondition),
		m_oldRetailLiquidity(oldRetailLiquidity),
		m_newRetailLiquidity(newRetailLiquidity)
	{
	}
/*
	TMsgQuoteInfo(const MsgQuote& quote):
		m_oldPrice(quote.m_priceDollars, quote.m_priceFraction),
		m_oldSize(quote.m_size),
		m_newPrice(quote.m_priceDollars, quote.m_priceFraction),
		m_newSize(quote.m_size),
		m_mmid(quote.m_mmid),
		m_oldMillisecond(quote.m_millisecond),
		m_newMillisecond(quote.m_millisecond),
		m_bookId(quote.m_bookID),
		m_oldQuoteCondition(quote.m_quoteCondition),
		m_newQuoteCondition(quote.m_quoteCondition),
		m_oldRetailLiquidity((quote.m_flags & MsgQuote::RetailInterest) != 0),
		m_newRetailLiquidity((quote.m_flags & MsgQuote::RetailInterest) != 0)
	{
	}
*/

//	unsigned int m_oldPriceDollars;
//	unsigned int m_oldPriceFraction;
	Price m_oldPrice;
	unsigned int m_oldSize;
//	unsigned int m_newPriceDollars;
//	unsigned int m_newPriceFraction;
	Price m_newPrice;
	unsigned int m_newSize;
	unsigned int m_mmid;
	unsigned int m_oldMillisecond;
	unsigned int m_newMillisecond;
	unsigned char m_bookId;
	unsigned char m_oldQuoteCondition;
	unsigned char m_newQuoteCondition;
	bool m_oldRetailLiquidity;
	bool m_newRetailLiquidity;
};

class TMsgBookTopInfo : public Message//This Message is used (as primary, not additional, info) for notification of InThread Observers if there are no Book Depth Entitlements, instead of TMsgQuoteInfo as additional info
{
public:
	TMsgBookTopInfo(const Price& oldPrice,
		const unsigned int& oldSize,
		const Price& newPrice,
		const unsigned int& newSize,
		const unsigned int& mmid,
		const unsigned char& bookId,
		const bool& bid):
		Message(TM_BOOKTOP_INFO, sizeof(TMsgQuoteInfo)),
		m_oldPrice(oldPrice),
		m_oldSize(oldSize),
		m_newPrice(newPrice),
		m_newSize(newSize),
		m_mmid(mmid),
		m_bookId(bookId),
		m_bid(bid)
	{
	}
	Price m_oldPrice;
	unsigned int m_oldSize;
	Price m_newPrice;
	unsigned int m_newSize;
	unsigned int m_mmid;
	unsigned char m_bookId;
	bool m_bid;
};

class MsgQuote
{
public:
	MsgQuote(const unsigned __int64& referenceNumber,
		const unsigned int& priceDollars,
		const unsigned int& priceFraction,
		const unsigned int& size,
		const unsigned int& mmid,
		const unsigned int& millisecond,
		const unsigned char& bookID,//	: 8;
		const unsigned char& quoteCondition,//	: 8;
		const unsigned short& flags)://		: 24;
		m_referenceNumber(referenceNumber),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_size(size),
		m_mmid(mmid),
		m_millisecond(millisecond),
		m_bookID(bookID),
		m_quoteCondition(quoteCondition),
		m_flags(flags)
	{
	}

	unsigned __int64	m_referenceNumber;
	unsigned int		m_priceDollars;
	unsigned int		m_priceFraction;
	unsigned int		m_size;
	unsigned int		m_mmid;
	unsigned int		m_millisecond;
	unsigned char		m_bookID;//	: 8;
	unsigned char		m_quoteCondition;//	: 8;
	unsigned short		m_flags;//		: 24;

	enum Flags : unsigned short
	{
		SizeChanged			= 0x01,
		PriceChanged		= 0x02,
		ConditionChanged	= 0x04,
		RetailInterest		= 0x08,
		LULDNonExecutable	= 0x10,
	};
};

enum TradeSide : unsigned char
{
	Buy				= 0x00,
	Sell			= 0x01,
	ShortSell		= 0x02,
	ShortSellExempt	= 0x03,
};

////////////////
class TSmMsgBookNewQuote : public TSmMessageSymbol
{
public:
	TSmMsgBookNewQuote(const unsigned short& symbol = 0,
		const unsigned char& side = Buy,
		const unsigned __int64& referenceNumber = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned int& size = 0,
		const unsigned int& mmid = 0,
		const unsigned int& millisecond = 0,
		const unsigned char& bookID = 0,//	: 8;
		const unsigned char& quoteCondition = 0,//	: 8;
		const unsigned short& flags = 0)://		: 24;
		TSmMessageSymbol(symbol, SM_M_BOOK_NEW_QUOTE, sizeof(TSmMsgBookNewQuote)),
		m_side(side),
		m_quote(referenceNumber, priceDollars, priceFraction, size, mmid, millisecond, bookID, quoteCondition, flags)
	{
	}
	unsigned char m_side;
	MsgQuote m_quote;
};

class TSmMsgBookModifyQuote : public TSmMessageSymbol
{
public:
	TSmMsgBookModifyQuote(const unsigned short& symbol = 0,
		const unsigned char& side = Buy,
		const unsigned __int64& referenceNumber = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned int& size = 0,
		const unsigned int& mmid = 0,
		const unsigned int& millisecond = 0,
		const unsigned char& bookID = 0,//	: 8;
		const unsigned char& quoteCondition = 0,//	: 8;
		const unsigned short& flags = 0)://		: 24;
		TSmMessageSymbol(symbol, SM_M_BOOK_MODIFY_QUOTE, sizeof(TSmMsgBookModifyQuote)),
		m_side(side),
		m_quote(referenceNumber, priceDollars, priceFraction, size, mmid, millisecond, bookID, quoteCondition, flags)
	{
	}
	unsigned char m_side;
	MsgQuote m_quote;
};

class TSmMsgBookDeleteQuote : public TMessageTime
{
public:
	TSmMsgBookDeleteQuote(const unsigned short& symbol = 0,
		const unsigned int& millisecond = 0,
		const unsigned __int64& referenceNumber = 0,
		const unsigned char& side = Buy,
		const unsigned char& bookID = 0):
		TMessageTime(millisecond, SM_M_BOOK_DELETE_QUOTE, sizeof(TSmMsgBookDeleteQuote)),
		m_referenceNumber(referenceNumber),
		m_symbol(symbol),
		m_side(side),
		m_bookID(bookID)
	{
	}
	unsigned __int64 m_referenceNumber;
	unsigned short m_symbol;
	unsigned char m_side;
	unsigned char m_bookID;
};

class TSmMsgBookOrderExecuted : public TMessageTime
{
public:
	TSmMsgBookOrderExecuted(const unsigned short& symbol = 0,
		const unsigned int& millisecond = 0,
		const unsigned __int64& referenceNumber = 0,
		const unsigned __int64& matchNumber = 0,
		const unsigned int& shares = 0,
		const unsigned char& side = Buy,
		const unsigned char& bookID = 0):
		TMessageTime(millisecond, SM_M_BOOK_ORDER_EXECUTED, sizeof(TSmMsgBookOrderExecuted)),
		m_referenceNumber(referenceNumber),
		m_matchNumber(matchNumber),
		m_shares(shares),
		m_symbol(symbol),
		m_side(side),
		m_bookID(bookID)
	{
	}
	unsigned __int64 m_referenceNumber;
	unsigned __int64 m_matchNumber;
	unsigned int m_shares;
	unsigned short m_symbol;
	unsigned char m_side;
	unsigned char m_bookID;
};

class TSmMsgBookOrderExecutedWithPrice : public TMessageTime
{
public:
	TSmMsgBookOrderExecutedWithPrice(const unsigned short& symbol = 0,
		const unsigned int& millisecond = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned __int64& referenceNumber = 0,
		const unsigned __int64& matchNumber = 0,
		const unsigned int& shares = 0,
		const unsigned int& remainingShares = 0,
		const unsigned char& side = Buy,
		const unsigned char& bookID = 0,
		const bool& bPrintable = false):
		TMessageTime(millisecond, SM_M_BOOK_ORDER_EXECUTED_WITH_PRICE, sizeof(TSmMsgBookOrderExecutedWithPrice)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_referenceNumber(referenceNumber),
		m_matchNumber(matchNumber),
		m_shares(shares),
		m_remainingShares(remainingShares),
		m_symbol(symbol),
		m_side(side),
		m_bookID(bookID),
		m_bPrintable(bPrintable)
	{
	}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned __int64 m_referenceNumber;
	unsigned __int64 m_matchNumber;
	unsigned int m_shares;
	unsigned int m_remainingShares;
	unsigned short m_symbol;
	unsigned char m_side;
	unsigned char m_bookID;
	bool m_bPrintable;
};

class TSmMsgBookOrderCanceled : public TMessageTime
{
public:
	TSmMsgBookOrderCanceled(const unsigned short& symbol = 0,
		const unsigned int& millisecond = 0,
		const unsigned __int64& referenceNumber = 0,
		const unsigned int& shares = 0,
		const unsigned char& side = Buy,
		const unsigned char& bookID = 0):
		TMessageTime(millisecond, SM_M_BOOK_ORDER_CANCELED, sizeof(TSmMsgBookOrderCanceled)),
		m_referenceNumber(referenceNumber),
		m_shares(shares),
		m_symbol(symbol),
		m_side(side),
		m_bookID(bookID)
	{
	}
	unsigned __int64 m_referenceNumber;
	unsigned int m_shares;
	unsigned short m_symbol;
	unsigned char m_side;
	unsigned char m_bookID;
};

class TSmMsgBookTrade : public TMessageTime
{
public:
	TSmMsgBookTrade(const unsigned short& symbol = 0,
		const unsigned int& millisecond = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned __int64& matchNumber = 0,
		const unsigned int& shares = 0,
		const unsigned char& side = Buy,
		const unsigned char& bookID = 0):
		TMessageTime(millisecond, SM_M_BOOK_TRADE, sizeof(TSmMsgBookTrade)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_matchNumber(matchNumber),
		m_shares(shares),
		m_symbol(symbol),
		m_side(side),
		m_bookID(bookID)
	{
	}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
//	unsigned __int64 m_referenceNumber;//??
	unsigned __int64 m_matchNumber;
	unsigned int m_shares;
	unsigned short m_symbol;
	unsigned char m_side;
	unsigned char m_bookID;
};

class TSmMsgBookCrossTrade : public TMessageTime
{
public:
	TSmMsgBookCrossTrade(const unsigned short& symbol = 0,
		const unsigned int& millisecond = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned __int64& matchNumber = 0,
		const unsigned int& shares = 0,
		const char& crossType = 0,
		const unsigned char& bookID = 0):
		TMessageTime(millisecond, SM_M_BOOK_CROSS_TRADE, sizeof(TSmMsgBookCrossTrade)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_matchNumber(matchNumber),
		m_shares(shares),
		m_symbol(symbol),
		m_crossType(crossType),
		m_bookID(bookID)
	{
	}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned __int64 m_matchNumber;
	unsigned int m_shares;
	unsigned short m_symbol;
	char m_crossType;
	unsigned char m_bookID;
};

class TSmMsgStockDirectory : public TMessageTime
{
public:
	TSmMsgStockDirectory(const unsigned short& symbol,
		const unsigned int& time,
		const unsigned int& roundLotSize,
		const bool& roundLotsOnly,
		const char& marketCategory,
		const char& financialStatusIndicator):
		TMessageTime(time, SM_M_STOCK_DIRECTORY, sizeof(TSmMsgStockDirectory)),
		m_roundLotSize(roundLotSize),
		m_symbol(symbol),
		m_roundLotsOnly(roundLotsOnly),
		m_marketCategory(marketCategory),
		m_financialStatusIndicator(financialStatusIndicator)
	{
	}
	unsigned int m_roundLotSize;
	unsigned short m_symbol;
	bool m_roundLotsOnly;
	char m_marketCategory;
	char m_financialStatusIndicator;
};

class TSmMsgStockTradingActionBase : public TMessageTime//TSmMessageTimeSymbol
{
public:
	unsigned short m_symbol;
	char m_tradingState;
	char m_tradingActionReason[4];
protected:
	TSmMsgStockTradingActionBase(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const char& tradingState = 0,
		const unsigned int& tradingActionReason = 0,
		const unsigned short& type = 0,
		const unsigned short& length = 0):
//		TSmMessageTimeSymbol(symbol, time, type, length),
		TMessageTime(time, type, length),
		m_symbol(symbol),
		m_tradingState(tradingState)
	{
		*(unsigned int*)m_tradingActionReason = tradingActionReason;
	}
};

class TSmMsgStockPreviousTradingStateBase : public TSmMsgStockTradingActionBase
{
public:
	char m_prevTradingState;
protected:
	TSmMsgStockPreviousTradingStateBase(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const char& prevTradingState = 0,
		const char& tradingState = 0,
		const unsigned int& tradingActionReason = 0,
		const unsigned short& type = 0,
		const unsigned short& length = 0):
		TSmMsgStockTradingActionBase(symbol, time, tradingState, tradingActionReason, type, length),
		m_prevTradingState(prevTradingState)
	{
	}
};

class TSmMsgStockTradingAction : public TSmMsgStockTradingActionBase
{
public:
	TSmMsgStockTradingAction(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const char& tradingState = 0,
		const unsigned int& tradingActionReason = 0):
		TSmMsgStockTradingActionBase(symbol,
			time,
			tradingState,
			tradingActionReason,
			SM_M_STOCK_TRADING_ACTION,
			sizeof(TSmMsgStockTradingAction))
	{
	}
};

//To notify windows
/*
class TMsgStockPreviousTradingState : public TSmMsgStockPreviousTradingStateBase
{
public:
	TMsgStockPreviousTradingState(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const char& prevTradingState = 0,
		const char& tradingState = 0,
		const unsigned int& tradingActionReason = 0):
		TSmMsgStockPreviousTradingStateBase(symbol, time, prevTradingState, tradingState, tradingActionReason, TM_STOCK_PREV_TRADING_ACTION, sizeof(TMsgStockPreviousTradingState))
	{
	}
};
*/
class TMsgEquityPreviousTradingState : public TSmMsgStockPreviousTradingStateBase
{
public:
	TMsgEquityPreviousTradingState(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const char& prevTradingState = 0,
		const char& tradingState = 0,
		const unsigned int& tradingActionReason = 0) :
		TSmMsgStockPreviousTradingStateBase(symbol, time, prevTradingState, tradingState, tradingActionReason, TM_EQUITY_PREV_TRADING_ACTION, sizeof(TMsgEquityPreviousTradingState))
	{
	}
};
/////

class TSmMsgResetSymbol: public TSmMessageSymbol
{
public:
	TSmMsgResetSymbol(const unsigned short& symbol = 0, const unsigned char& bookId = AllBooks):TSmMessageSymbol(symbol, SM_M_RESET_SYMBOL, sizeof(TSmMsgResetSymbol)), m_bookId(bookId){}
    unsigned char m_bookId;
};

class TSmMsgResetBook: public Message
{
public:
	TSmMsgResetBook(const unsigned char& bookId = AllBooks):Message(SM_M_RESET_BOOK, sizeof(TSmMsgResetBook)),m_bookId(bookId){}
    unsigned char m_bookId;
};

class TSmMsgImbalance : public TSmMessageSymbol
{
public:
	TSmMsgImbalance(const unsigned short& symbol = 0,
		const unsigned int& farPriceDollar = 0,
		const unsigned int& farPriceFraction = 0,
		const unsigned int& nearPriceDollar = 0,
		const unsigned int& nearPriceFraction = 0,
		const unsigned int& currentReferencePriceDollar = 0,
		const unsigned int& currentReferencePriceFraction = 0,
		const unsigned int& pairedShares = 0,
		const unsigned int& imbalanceShares = 0,
		const unsigned int& marketImbalanceShares = 0,
		const unsigned int& time = 0,
		const unsigned int& auctionTime = 0,
		const char& imbalanceDirection = 0,
		const char& crossType = 0,
		const char& priceVariationIndicator = 0,
		const unsigned char& bookId = 0,
		const bool& regulatory = false,
		const bool& freezeStatus = false):
	
		TSmMessageSymbol(symbol, SM_M_STOCK_IMBALANCE_INDICATOR, sizeof(TSmMsgImbalance)),
		m_farPriceDollar(farPriceDollar),
		m_farPriceFraction(farPriceFraction),
		m_nearPriceDollar(nearPriceDollar),
		m_nearPriceFraction(nearPriceFraction),
		m_currentReferencePriceDollar(currentReferencePriceDollar),
		m_currentReferencePriceFraction(currentReferencePriceFraction),
		m_pairedShares(pairedShares),
		m_imbalanceShares(imbalanceShares),
		m_marketImbalanceShares(marketImbalanceShares),
		m_time(time),
		m_auctionTime(auctionTime),
		m_imbalanceDirection(imbalanceDirection),
		m_crossType(crossType),
		m_priceVariationIndicator(priceVariationIndicator),
		m_bookID(bookId),
		m_regulatoryImbalance_StockOpen(regulatory ? 1 : 0),
		m_freezeStatus(freezeStatus ? 1 : 0)
	{
	}
	unsigned int m_farPriceDollar;
	unsigned int m_farPriceFraction;
	unsigned int m_nearPriceDollar;
	unsigned int m_nearPriceFraction;
	unsigned int m_currentReferencePriceDollar;
	unsigned int m_currentReferencePriceFraction;
	unsigned int m_pairedShares;
	unsigned int m_imbalanceShares;
	unsigned int m_marketImbalanceShares;
	unsigned int m_time;
	unsigned int m_auctionTime;
	char m_imbalanceDirection;
	char m_crossType;
	char m_priceVariationIndicator;
	unsigned char m_bookID : 4;
	unsigned char m_regulatoryImbalance_StockOpen : 1;
	unsigned char m_freezeStatus : 1;
};

class TSmMsgLevel1: public TMessageTime
{
public:
	TSmMsgLevel1(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& bidDollars = 0,
		const unsigned int& bidFraction = 0,
		const unsigned int& askDollars = 0,
		const unsigned int& askFraction = 0,
		const unsigned int& bidSize = 0,
		const unsigned int& askSize = 0,
		const char& primaryListingMarket = 0,
		const char& bidMarketCenter = 0,
		const char& askMarketCenter = 0,
		const char& quoteCondition = 0):
		TMessageTime(time, SM_M_LEVEL1, sizeof(TSmMsgLevel1)),
		m_bidDollars(bidDollars),
		m_bidFraction(bidFraction),
		m_askDollars(askDollars),
		m_askFraction(askFraction),
		m_bidSize(bidSize),
		m_askSize(askSize),
		m_symbol(symbol),
		m_primaryListingMarket(primaryListingMarket),
		m_bidMarketCenter(bidMarketCenter),
		m_askMarketCenter(askMarketCenter),
		m_quoteCondition(quoteCondition)
	{
	}
	unsigned int m_bidDollars;
	unsigned int m_bidFraction;
	unsigned int m_askDollars;
	unsigned int m_askFraction;
	unsigned int m_bidSize;
	unsigned int m_askSize;
	unsigned short m_symbol;
	char m_primaryListingMarket;
	char m_bidMarketCenter;
	char m_askMarketCenter;
	char m_quoteCondition;
};

class TSmMsgTrade: public TMessageTime
{
public:
	TSmMsgTrade(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned __int64& referenceNumber = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned int& size = 0,
		const char& saleCondition1 = 0,
		const char& saleCondition2 = 0,
		const char& saleCondition3 = 0,
		const char& saleCondition4 = 0,
		const char& marketCenterID = 0,
		const char& primaryListingMarket = 0,
		const unsigned char& flags = 0):
		TMessageTime(time, SM_M_TRADE_REPORT, sizeof(TSmMsgTrade)),
		m_referenceNumber(referenceNumber),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_size(size),
		m_symbol(symbol),
		m_marketCenterID(marketCenterID),
		m_primaryListingMarket(primaryListingMarket),
		m_flags(flags)
	{
		char* cursor = m_saleConditions;
		*cursor = saleCondition1;
		*++cursor = saleCondition2;
		*++cursor = saleCondition3;
		*++cursor = saleCondition4;
	}
	unsigned __int64 m_referenceNumber;
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_size;
	unsigned short m_symbol;
	char m_saleConditions[4];
	char m_marketCenterID;
	char m_primaryListingMarket;
	unsigned char m_flags;
};

class TSmMsgTradeErrorBase: public TMessageTime
{
public:
	unsigned __int64 m_originalReferenceNumber;
	unsigned int m_originalPriceDollars;
	unsigned int m_originalPriceFraction;
	unsigned int m_originalSize;
	char m_originalSaleConditions[4];

	unsigned int m_lastPriceDollars;
	unsigned int m_lastPriceFraction;
	unsigned int m_highPriceDollars;
	unsigned int m_highPriceFraction;
	unsigned int m_lowPriceDollars;
	unsigned int m_lowPriceFraction;
	unsigned __int64 m_volume;

	unsigned short m_symbol;
	char m_marketCenterID;
	char m_primaryListingMarket;
	unsigned char m_flags;
protected:
	TSmMsgTradeErrorBase(const unsigned short& symbol,
		const unsigned int& time,
		const unsigned __int64& originalReferenceNumber,
		const unsigned int& originalPriceDollars,
		const unsigned int& originalPriceFraction,
		const unsigned int& originalSize,
		const char& originalSaleCondition1,
		const char& originalSaleCondition2,
		const char& originalSaleCondition3,
		const char& originalSaleCondition4,

		const unsigned int& lastPriceDollars,
		const unsigned int& lastPriceFraction,
		const unsigned int& highPriceDollars,
		const unsigned int& highPriceFraction,
		const unsigned int& lowPriceDollars,
		const unsigned int& lowPriceFraction,
		const unsigned __int64& volume,

		const char& marketCenterID,
		const char& primaryListingMarket,
		const unsigned char& flags,

		const unsigned short& type,
		const unsigned short& length):
		TMessageTime(time, type, length),
		m_originalReferenceNumber(originalReferenceNumber),
		m_originalPriceDollars(originalPriceDollars),
		m_originalPriceFraction(originalPriceFraction),
		m_originalSize(originalSize),
		m_lastPriceDollars(lastPriceDollars),
		m_lastPriceFraction(lastPriceFraction),
		m_highPriceDollars(highPriceDollars),
		m_highPriceFraction(highPriceFraction),
		m_lowPriceDollars(lowPriceDollars),
		m_lowPriceFraction(lowPriceFraction),
		m_volume(volume),
		m_symbol(symbol),
		m_marketCenterID(marketCenterID),
		m_primaryListingMarket(primaryListingMarket),
		m_flags(flags)
	{
		char* cursor = m_originalSaleConditions;
		*cursor = originalSaleCondition1;
		*++cursor = originalSaleCondition2;
		*++cursor = originalSaleCondition3;
		*++cursor = originalSaleCondition4;
	}
};

class TSmMsgTradeError: public TSmMsgTradeErrorBase
{
public:
	TSmMsgTradeError(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned __int64& originalReferenceNumber = 0,
		const unsigned int& originalPriceDollars = 0,
		const unsigned int& originalPriceFraction = 0,
		const unsigned int& originalSize = 0,
		const char& originalSaleCondition1 = 0,
		const char& originalSaleCondition2 = 0,
		const char& originalSaleCondition3 = 0,
		const char& originalSaleCondition4 = 0,

		const unsigned int& lastPriceDollars = 0,
		const unsigned int& lastPriceFraction = 0,
		const unsigned int& highPriceDollars = 0,
		const unsigned int& highPriceFraction = 0,
		const unsigned int& lowPriceDollars = 0,
		const unsigned int& lowPriceFraction = 0,
		const unsigned __int64& volume = 0,

		const char& marketCenterID = 0,
		const char& primaryListingMarket = 0,
		const unsigned char& flags = 0):
		TSmMsgTradeErrorBase(symbol,
			time,
			originalReferenceNumber,
			originalPriceDollars,
			originalPriceFraction,
			originalSize,
			originalSaleCondition1,
			originalSaleCondition2,
			originalSaleCondition3,
			originalSaleCondition4,

			lastPriceDollars,
			lastPriceFraction,
			highPriceDollars,
			highPriceFraction,
			lowPriceDollars,
			lowPriceFraction,
			volume,

			marketCenterID,
			primaryListingMarket,
			flags,
			SM_M_TRADE_CANCEL_ERROR,
			sizeof(TSmMsgTradeError))
	{
	}
};

class TSmMsgTradeCorrectionBase: public TMessageTime
{
public:
	unsigned int m_originalPriceDollars;
	unsigned int m_originalPriceFraction;
	unsigned int m_correctedPriceDollars;
	unsigned int m_correctedPriceFraction;
	unsigned int m_originalSize;
	unsigned int m_correctedSize;
	unsigned __int64 m_originalReferenceNumber;
	unsigned __int64 m_correctedReferenceNumber;
	char m_originalSaleConditions[4];
	char m_correctedSaleConditions[4];
	unsigned int m_lastPriceDollars;
	unsigned int m_lastPriceFraction;
	unsigned int m_highPriceDollars;
	unsigned int m_highPriceFraction;
	unsigned int m_lowPriceDollars;
	unsigned int m_lowPriceFraction;
	unsigned __int64 m_volume;
	unsigned short m_symbol;
	char m_marketCenterID;
	char m_primaryListingMarket;
	char m_flags;
protected:
	TSmMsgTradeCorrectionBase(const unsigned short& symbol,
		const unsigned int& time,
		const unsigned int& originalPriceDollars,
		const unsigned int& originalPriceFraction,
		const unsigned int& correctedPriceDollars,
		const unsigned int& correctedPriceFraction,
		const unsigned int& originalSize,
		const unsigned int& correctedSize,
		const unsigned __int64& originalReferenceNumber,
		const unsigned __int64& correctedReferenceNumber,
		const char& originalSaleCondition1,
		const char& originalSaleCondition2,
		const char& originalSaleCondition3,
		const char& originalSaleCondition4,
		const char& correctedSaleCondition1,
		const char& correctedSaleCondition2,
		const char& correctedSaleCondition3,
		const char& correctedSaleCondition4,

		const unsigned int& lastPriceDollars,
		const unsigned int& lastPriceFraction,
		const unsigned int& highPriceDollars,
		const unsigned int& highPriceFraction,
		const unsigned int& lowPriceDollars,
		const unsigned int& lowPriceFraction,
		const unsigned __int64& volume,

		const char& marketCenterID,
		const char& primaryListingMarket,
		const char& flags,

		const unsigned short& type,
		const unsigned short& length):
		TMessageTime(time, type, length),
		m_originalPriceDollars(originalPriceDollars),
		m_originalPriceFraction(originalPriceFraction),
		m_correctedPriceDollars(correctedPriceDollars),
		m_correctedPriceFraction(correctedPriceFraction),
		m_originalSize(originalSize),
		m_correctedSize(correctedSize),
		m_originalReferenceNumber(originalReferenceNumber),
		m_correctedReferenceNumber(correctedReferenceNumber),
		m_lastPriceDollars(lastPriceDollars),
		m_lastPriceFraction(lastPriceFraction),
		m_highPriceDollars(highPriceDollars),
		m_highPriceFraction(highPriceFraction),
		m_lowPriceDollars(lowPriceDollars),
		m_lowPriceFraction(lowPriceFraction),
		m_volume(volume),
		m_symbol(symbol),
		m_marketCenterID(marketCenterID),
		m_primaryListingMarket(primaryListingMarket),
		m_flags(flags)
	{
		char* cursor = m_originalSaleConditions;
		*cursor = originalSaleCondition1;
		*++cursor = originalSaleCondition2;
		*++cursor = originalSaleCondition3;
		*++cursor = originalSaleCondition4;

		cursor = m_correctedSaleConditions;
		*cursor = correctedSaleCondition1;
		*++cursor = correctedSaleCondition2;
		*++cursor = correctedSaleCondition3;
		*++cursor = correctedSaleCondition4;
	}
};

class TSmMsgTradeCorrection: public TSmMsgTradeCorrectionBase
{
public:
	TSmMsgTradeCorrection(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& originalPriceDollars = 0,
		const unsigned int& originalPriceFraction = 0,
		const unsigned int& correctedPriceDollars = 0,
		const unsigned int& correctedPriceFraction = 0,
		const unsigned int& originalSize = 0,
		const unsigned int& correctedSize = 0,
		const unsigned __int64& originalReferenceNumber = 0,
		const unsigned __int64& correctedReferenceNumber = 0,
		const char& originalSaleCondition1 = 0,
		const char& originalSaleCondition2 = 0,
		const char& originalSaleCondition3 = 0,
		const char& originalSaleCondition4 = 0,
		const char& correctedSaleCondition1 = 0,
		const char& correctedSaleCondition2 = 0,
		const char& correctedSaleCondition3 = 0,
		const char& correctedSaleCondition4 = 0,

		const unsigned int& lastPriceDollars = 0,
		const unsigned int& lastPriceFraction = 0,
		const unsigned int& highPriceDollars = 0,
		const unsigned int& highPriceFraction = 0,
		const unsigned int& lowPriceDollars = 0,
		const unsigned int& lowPriceFraction = 0,
		const unsigned __int64& volume = 0,

		const char& marketCenterID = 0,
		const char& primaryListingMarket = 0,
		const char& flags = 0):
		TSmMsgTradeCorrectionBase(symbol,
			time,
			originalPriceDollars,
			originalPriceFraction,
			correctedPriceDollars,
			correctedPriceFraction,
			originalSize,
			correctedSize,
			originalReferenceNumber,
			correctedReferenceNumber,
			originalSaleCondition1,
			originalSaleCondition2,
			originalSaleCondition3,
			originalSaleCondition4,
			correctedSaleCondition1,
			correctedSaleCondition2,
			correctedSaleCondition3,
			correctedSaleCondition4,

			lastPriceDollars,
			lastPriceFraction,
			highPriceDollars,
			highPriceFraction,
			lowPriceDollars,
			lowPriceFraction,
			volume,

			marketCenterID,
			primaryListingMarket,
			flags,
			SM_M_TRADE_CORRECTION,
			sizeof(TSmMsgTradeCorrection))
	{
	}
};

class TSmMsgEndOfDaySummaryReportBase : public TMessageTime
{
public:
	unsigned int m_todaysClosePriceDollar;
	unsigned int m_todaysClosePriceFraction;
    unsigned __int64 m_volume;
	unsigned short m_symbol;
protected:
    TSmMsgEndOfDaySummaryReportBase(const unsigned short& symbol,
		const unsigned int& time,
		const unsigned int& todaysClosePriceDollar,
		const unsigned int& todaysClosePriceFraction,
		const unsigned __int64& volume,
		const unsigned short& type,
		const unsigned short& length):
		
		TMessageTime(time, type, length),
		m_todaysClosePriceDollar(todaysClosePriceDollar),
		m_todaysClosePriceFraction(todaysClosePriceFraction),
		m_volume(volume),
		m_symbol(symbol)
	{
	}
};

class TSmMsgEndOfDaySummaryReport : public TSmMsgEndOfDaySummaryReportBase
{
public:
    TSmMsgEndOfDaySummaryReport(const unsigned short& symbol,
		const unsigned int& time,
		const unsigned int& todaysClosePriceDollar,
		const unsigned int& todaysClosePriceFraction,
		const unsigned __int64& volume):
		
		TSmMsgEndOfDaySummaryReportBase(symbol,
			time,
			todaysClosePriceDollar,
			todaysClosePriceFraction,
			volume,
			SM_M_EOD_SUMMARY_REPORT,
			sizeof(TSmMsgEndOfDaySummaryReport))
	{
	}
};

class TSmMsgShortSaleIndicatorsBase : public TMessageTime//TSmMessageTimeSymbol
{
public:
	unsigned short m_symbol;
	char m_shortSaleThresholdIndicator;//'Y', 'N'
	char m_regSHOTestIndicator;//'0', '1', '2'
protected:
    TSmMsgShortSaleIndicatorsBase(const unsigned short& symbol,
		const unsigned int& time,
		const char& shortSaleThresholdIndicator,
		const char& regSHOTestIndicator,
		const unsigned short& type,
		const unsigned short& length):

//		TSmMessageTimeSymbol(symbol, time, type, length),
		TMessageTime(time, type, length),
		m_symbol(symbol),
        m_shortSaleThresholdIndicator(shortSaleThresholdIndicator),
        m_regSHOTestIndicator(regSHOTestIndicator)
	{
	}

};

class TSmMsgShortSaleIndicators : public TSmMsgShortSaleIndicatorsBase
{
public:
    TSmMsgShortSaleIndicators(const unsigned short& symbol,
		const unsigned int& time,
		const char& shortSaleThresholdIndicator,
		const char& regSHOTestIndicator):

		TSmMsgShortSaleIndicatorsBase(symbol, time, shortSaleThresholdIndicator, regSHOTestIndicator, SM_M_SHORT_SALE_INDICATORS, sizeof(TSmMsgShortSaleIndicators))
	{
	}
};

class TSmMsgHighLowBase : public TMessageTime
{
public:
	unsigned int m_lowDollar;
	unsigned int m_lowFraction;
	unsigned int m_highDollar;
	unsigned int m_highFraction;
protected:
	TSmMsgHighLowBase(const unsigned int& time,
		const unsigned int& lowDollar,
		const unsigned int& lowFraction,
		const unsigned int& highDollar,
		const unsigned int& highFraction,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTime(time, type, length),
		m_lowDollar(lowDollar),
		m_lowFraction(lowFraction),
		m_highDollar(highDollar),
		m_highFraction(highFraction)
	{
	}
};

class TSmMsgHighLow2Base : public TSmMsgHighLowBase
{
public:
	unsigned int m_lowDollar2;
	unsigned int m_lowFraction2;
	unsigned int m_highDollar2;
	unsigned int m_highFraction2;
protected:
	TSmMsgHighLow2Base(const unsigned int& time,
		const unsigned int& lowDollar,
		const unsigned int& lowFraction,
		const unsigned int& highDollar,
		const unsigned int& highFraction,
		const unsigned int& lowDollar2,
		const unsigned int& lowFraction2,
		const unsigned int& highDollar2,
		const unsigned int& highFraction2,
		const unsigned short& type,
		const unsigned short& length):
		TSmMsgHighLowBase(time,
			lowDollar,
			lowFraction,
			highDollar,
			highFraction,
			type,
			length),
		m_lowDollar2(lowDollar2),
		m_lowFraction2(lowFraction2),
		m_highDollar2(highDollar2),
		m_highFraction2(highFraction2)
	{
	}
};

class TSmMsg52Week30DayHighLow : public TSmMsgHighLow2Base
{
public:
	TSmMsg52Week30DayHighLow(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0,
		const unsigned int& lowDollar2 = 0,
		const unsigned int& lowFraction2 = 0,
		const unsigned int& highDollar2 = 0,
		const unsigned int& highFraction2 = 0):
		TSmMsgHighLow2Base(time,
			lowDollar,
			lowFraction,
			highDollar,
			highFraction,
			lowDollar2,
			lowFraction2,
			highDollar2,
			highFraction2,
			SM_M_52WEEK_30DAY_HIGH_LOW,
			sizeof(TSmMsg52Week30DayHighLow)),
		m_symbol(symbol)
	{
	}
	unsigned short m_symbol;
};

class TSmMsgMs52Week30DayHighLow : public TSmMsgHighLow2Base
{
public:
	TSmMsgMs52Week30DayHighLow(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0,
		const unsigned int& lowDollar2 = 0,
		const unsigned int& lowFraction2 = 0,
		const unsigned int& highDollar2 = 0,
		const unsigned int& highFraction2 = 0):
		TSmMsgHighLow2Base(time,
			lowDollar,
			lowFraction,
			highDollar,
			highFraction,
			lowDollar2,
			lowFraction2,
			highDollar2,
			highFraction2,
			SM_MS_52WEEK_30DAY_HIGH_LOW,
			sizeof(TSmMsgMs52Week30DayHighLow)),
		m_symbol(symbol)
	{
	}
	unsigned short m_symbol;
};

class TSmMsgPmiBase : public TSmMsgHighLowBase
{
public:
	unsigned short m_symbol;
	unsigned char m_securityStatus;
	unsigned char m_adjustment;
protected:
	TSmMsgPmiBase(const unsigned short& symbol,
		const unsigned int& time,
		const unsigned int& bidDollar,
		const unsigned int& bidFraction,
		const unsigned int& askDollar,
		const unsigned int& askFraction,
		const unsigned char& securityStatus,
		const unsigned char& adjustment,
		const unsigned short& type,
		const unsigned short& length):
		TSmMsgHighLowBase(time, bidDollar, bidFraction, askDollar, askFraction, type, length),
		m_symbol(symbol),
        m_securityStatus(securityStatus),
        m_adjustment(adjustment)
	{
	}
};

class TSmMsgPmi : public TSmMsgPmiBase
{
public:
    TSmMsgPmi(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& bidDollar = 0,
		const unsigned int& bidFraction = 0,
		const unsigned int& askDollar = 0,
		const unsigned int& askFraction = 0,
		const unsigned char& securityStatus = 0,
		const unsigned char& adjustment = 0):
		TSmMsgPmiBase(symbol,
			time,
			bidDollar,
			bidFraction,
			askDollar,
			askFraction,
			securityStatus,
			adjustment,
			SM_M_PMI,
			sizeof(TSmMsgPmi))
	{
	}
};

class TSmMsgLrpBase : public TSmMsgHighLowBase
{
public:
	unsigned short m_symbol;
	unsigned char m_changeIndicator;
protected:
	TSmMsgLrpBase(const unsigned short& symbol,
		const unsigned int& time,
		const unsigned int& lowDollar,
		const unsigned int& lowFraction,
		const unsigned int& highDollar,
		const unsigned int& highFraction,
		const unsigned char& changeIndicator,
		const unsigned short& type,
		const unsigned short& length):
		TSmMsgHighLowBase(time, lowDollar, lowFraction, highDollar, highFraction, type, length),
		m_symbol(symbol),
        m_changeIndicator(changeIndicator)
	{
	}
};

#ifdef LRPS
class TSmMsgLrp : public TSmMsgLrpBase
{
public:
    TSmMsgLrp(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0,
		const unsigned char& changeIndicator = 0):
		TSmMsgLrpBase(symbol,
			time,
			lowDollar,
			lowFraction,
			highDollar,
			highFraction,
			changeIndicator,
			SM_M_LRP,
			sizeof(TSmMsgLrp))
	{
	}
};
#endif

class TSmMsgLuld : public TSmMsgLrpBase
{
public:
    TSmMsgLuld(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0,
		const unsigned char& changeIndicator = 0):
		TSmMsgLrpBase(symbol,
			time,
			lowDollar,
			lowFraction,
			highDollar,
			highFraction,
			changeIndicator,
			SM_M_LULD,
			sizeof(TSmMsgLuld))
	{
	}
};

class TSmMsgTradeTimeBase : public TMessageTime
{
public:
	unsigned int m_tradeTime;
	unsigned short m_symbol;
protected:
	TSmMsgTradeTimeBase(const unsigned short& symbol,
		const unsigned int& time,
		const unsigned int& tradeTime,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTime(time, type, length),
		m_symbol(symbol),
		m_tradeTime(tradeTime)
	{
	}
};

class TSmMsgTradeTime : public TSmMsgTradeTimeBase
{
public:
    TSmMsgTradeTime(const unsigned short& symbol,
		const unsigned int& time,
		const unsigned int& tradeTime):
		TSmMsgTradeTimeBase(symbol, time, tradeTime, SM_M_T_TIME, sizeof(TSmMsgTradeTime))
	{
	}
};


class TSmMsgRpiBase : public TMessageTime//TSmMessageTimeSymbol
{
public:
	unsigned short m_symbol;
	char m_indicator;
protected:
	TSmMsgRpiBase(const unsigned short& symbol,
		const unsigned int& time,
		const char& indicator,
		const unsigned short& type,
		const unsigned short& length):
//		TSmMessageTimeSymbol(symbol, time, type, length),
		TMessageTime(time, type, length),
		m_symbol(symbol),
		m_indicator(indicator)
	{
	}
};

class TSmMsgRpi : public TSmMsgRpiBase
{
public:
    TSmMsgRpi(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const char& indicator = 0):
		TSmMsgRpiBase(symbol, time, indicator, SM_M_RPI, sizeof(TSmMsgRpi))
	{
	}
};

class TSmMsgSecurityType : public TSmMsgRpiBase
{
public:
    TSmMsgSecurityType(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const char& securityType = 0):
		TSmMsgRpiBase(symbol, time, securityType, SM_M_SECURITY_TYPE, sizeof(TSmMsgSecurityType))
	{
	}
};

class TSmMsgDividendsAndSplitsBase : public TMessageTime
{
public:
	unsigned int m_dividendDollar;
	unsigned int m_dividendFraction;
	unsigned short m_symbol;
    unsigned short m_splitNumerator;
    unsigned short m_splitDenominator;
	char m_exDivDate[sizeof(unsigned int) + 1];
protected:
    TSmMsgDividendsAndSplitsBase(const unsigned short& symbol,
		const unsigned int& time,
		const unsigned int& dividendDollar,
		const unsigned int& dividendFraction,
	    const unsigned short& splitNumerator,
		const unsigned short& splitDenominator,
		const unsigned int& exDivDate,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTime(time, type, length),
		m_dividendDollar(dividendDollar),
		m_dividendFraction(dividendFraction),
		m_symbol(symbol),
        m_splitNumerator(splitNumerator),
        m_splitDenominator(splitDenominator)
	{
		*(unsigned int*)m_exDivDate = exDivDate;
		m_exDivDate[sizeof(unsigned int)] = '\0';
	}
};

class TSmMsgDividendsAndSplits : public TSmMsgDividendsAndSplitsBase
{
public:
    TSmMsgDividendsAndSplits(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& dividendDollar = 0,
		const unsigned int& dividendFraction = 0,
	    const unsigned short& splitNumerator = 0,
		const unsigned short& splitDenominator = 0,
		const unsigned int& exDivDate = 0):
		TSmMsgDividendsAndSplitsBase(symbol,
			time,
			dividendDollar,
			dividendFraction,
			splitNumerator,
			splitDenominator,
			exDivDate,
			SM_M_DIVIDENDS_AND_SPLITS,
			sizeof(TSmMsgDividendsAndSplits))
	{
	}
};

class TSmMsgPreviousDayCloseBase : public TMessageTime
{
public:
	unsigned int m_closePriceDollar;
	unsigned int m_closePriceFraction;
	unsigned short m_symbol;
protected:
    TSmMsgPreviousDayCloseBase(const unsigned short& symbol,
		const unsigned int& time,
		const unsigned int& closePriceDollar,
		const unsigned int& closePriceFraction,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTime(time, type, length),
		m_closePriceDollar(closePriceDollar),
		m_closePriceFraction(closePriceFraction),
		m_symbol(symbol)
	{
	}
};

class TSmMsgPreviousDayClose : public TSmMsgPreviousDayCloseBase
{
public:
    TSmMsgPreviousDayClose(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& closePriceDollar = 0,
		const unsigned int& closePriceFraction = 0):
		TSmMsgPreviousDayCloseBase(symbol,
			time,
			closePriceDollar,
			closePriceFraction,
			SM_M_PREVIOUS_DAY_CLOSE,
			sizeof(TSmMsgPreviousDayClose))
	{
	}
};

class TMessageRequest : public Message
{
public:
	unsigned int m_requestId;
protected:
	TMessageRequest(const unsigned int& requestId, const unsigned short& type, const unsigned short& length):
		Message(type, length),
		m_requestId(requestId)
	{
	}
};



class TSmMsgRespRefreshSymbol : public TMessageRequest
{
public:
	TSmMsgRespRefreshSymbol(const unsigned short& dataSize = 0,
		const unsigned int& requestId = 0,
		const char* const& symbol = "",
		const unsigned short& symbolIndex = 0,
		const unsigned char& steps = 0,
		const unsigned char& flags = 0,
		const unsigned char& bookID = 0,
		const char& marketStatus = 0):
		TMessageRequest(requestId, SM_M_RESP_REFRESH_SYMBOL, dataSize),
//		m_requestID(requestId),
		m_symbolIndex(symbolIndex),
		m_steps(steps),
		m_flags(flags),
		m_bookID(bookID),
		m_marketStatus(marketStatus)
	{
		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}

//	unsigned int m_requestID;
	Symbol m_symbol;
	unsigned short m_symbolIndex;
	unsigned char m_steps;
	unsigned char m_flags;
	unsigned char m_bookID;
	char m_marketStatus;
};

class SnapshotQuote
{
public:
	SnapshotQuote(const unsigned int& priceDollar,
		const unsigned int& priceFraction,
		const unsigned int& size,
		const unsigned int& mmid,
		const unsigned int& timeStamp,
		const unsigned char& bookId,
		const unsigned char& quoteCondition,
		const unsigned char& flags,
		const unsigned char& reserved):
		m_priceDollar(priceDollar),
		m_priceFraction(priceFraction),
		m_size(size),
		m_mmid(mmid),
		m_timeStamp(timeStamp),
		m_bookId(bookId),
		m_quoteCondition(quoteCondition),
		m_flags(flags),
		m_reserved(reserved)
	{
	}

	unsigned int m_priceDollar;
	unsigned int m_priceFraction;
	unsigned int m_size;
	unsigned int m_mmid;
	unsigned int m_timeStamp;
	unsigned char m_bookId;
	unsigned char m_quoteCondition;
	unsigned char m_flags;
	unsigned char m_reserved;
};

class SnapshotPrint
{
public:
	SnapshotPrint(const unsigned int priceDollar,
		const unsigned int priceFraction,
		const unsigned int timeStamp,
		const unsigned int size,
		const char saleCondition1,
		const char saleCondition2,
		const char saleCondition3,
		const char saleCondition4,
		const char marketCenterId,
		const unsigned char printFlags)://TradeLevel1

		m_priceDollar(priceDollar),
		m_priceFraction(priceFraction),
		m_timeStamp(timeStamp),
		m_size(size),
		m_saleCondition1(saleCondition1),
		m_saleCondition2(saleCondition2),
		m_saleCondition3(saleCondition3),
		m_saleCondition4(saleCondition4),
		m_marketCenterId(marketCenterId),
		m_printFlags(printFlags)
	{
	}

	unsigned int m_priceDollar;
	unsigned int m_priceFraction;
	unsigned int m_timeStamp;
	unsigned int m_size;
	char m_saleCondition1;
	char m_saleCondition2;
	char m_saleCondition3;
	char m_saleCondition4;
	char m_marketCenterId;
	unsigned char m_printFlags;//TradeLevel1
};

class TSmMsgSnapshot : public TMessageTime
{
public:
	TSmMsgSnapshot(const unsigned short& symbol = 0,
		const unsigned int& time = 0,

		const unsigned int& bidDollar = 0,
		const unsigned int& bidFraction = 0,
		const unsigned int& askDollar = 0,
		const unsigned int& askFraction = 0,
/*
		const unsigned int& lastDollar = 0,
		const unsigned int& lastFraction = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0,
		const unsigned __int64& volume = 0,
*/
		const unsigned long& bidSize = 0,
		const unsigned long& askSize = 0,
//		const unsigned long& lastSize = 0,
//		const unsigned int& lastTime = 0,

		const char& bidMarketCenter = 0,
		const char& askMarketCenter = 0,
//		const char& lastMarketCenter = 0,
		const char& quoteCondition = 0,

		const unsigned char& quoteNodeSize = 0,
//		const unsigned char& printNodeSize = 0,
		const unsigned char& bidQuoteCount = 0,
		const unsigned char& askQuoteCount = 0):
//		const unsigned char& printCount = 0):

		TMessageTime(time, SM_M_SNAPSHOT, sizeof(TSmMsgSnapshot) + ((unsigned short)bidQuoteCount + (unsigned short)askQuoteCount) * quoteNodeSize),// + (unsigned short)printCount * printNodeSize),

		m_bidDollar(bidDollar),
		m_bidFraction(bidFraction),
		m_askDollar(askDollar),
		m_askFraction(askFraction),
/*
		m_lastDollar(lastDollar),
		m_lastFraction(lastFraction),
		m_lowDollar(lowDollar),
		m_lowFraction(lowFraction),
		m_highDollar(highDollar),
		m_highFraction(highFraction),
		m_volume(volume),
*/
		m_bidSize(bidSize),
		m_askSize(askSize),
//		m_lastSize(lastSize),
//		m_lastTime(lastTime),

		m_symbol(symbol),

		m_bidMarketCenter(bidMarketCenter),
		m_askMarketCenter(askMarketCenter),
//		m_lastMarketCenter(lastMarketCenter),
		m_quoteCondition(quoteCondition),

		m_quoteNodeSize(quoteNodeSize),
//		m_printNodeSize(printNodeSize),
		m_bidQuoteCount(bidQuoteCount),
		m_askQuoteCount(askQuoteCount),
//		m_printCount(printCount),
		m_reserved1(0),
		m_reserved2(0),
		m_reserved3(0),
		m_quotesOffset(sizeof(TSmMsgSnapshot))
	{
	}

	unsigned int m_bidDollar;
	unsigned int m_bidFraction;
	unsigned int m_askDollar;
	unsigned int m_askFraction;
/*
	unsigned int m_lastDollar;
	unsigned int m_lastFraction;
	unsigned int m_lowDollar;
	unsigned int m_lowFraction;
	unsigned int m_highDollar;
	unsigned int m_highFraction;
	unsigned __int64 m_volume;
*/
	unsigned long m_bidSize;
	unsigned long m_askSize;
//	unsigned long m_lastSize;
//	unsigned int m_lastTime;

	unsigned short m_symbol;

	char m_bidMarketCenter;
	char m_askMarketCenter;
//	char m_lastMarketCenter;
	char m_quoteCondition;

	unsigned char m_quoteNodeSize;//BYTE
//	unsigned char m_printNodeSize;//BYTE
	unsigned char m_bidQuoteCount;//BYTE
	unsigned char m_askQuoteCount;//BYTE
//	unsigned char m_printCount;

	unsigned char m_reserved1;//char
	unsigned char m_reserved2;//char
	unsigned char m_reserved3;//char

	unsigned char m_quotesOffset;
};

class TSmMsgSystemEventBase : public Message
{
public:
	unsigned char m_eventCode;
	unsigned char m_source;
protected:
	TSmMsgSystemEventBase(const unsigned char& eventCode,
		const unsigned char& source,
		const unsigned short& type,
		const unsigned short& length):
		Message(type, length), m_eventCode(eventCode), m_source(source)
	{
	}
};

class TSmMsgSystemEvent : public TSmMsgSystemEventBase
{
public:
	TSmMsgSystemEvent(const unsigned char& eventCode, const unsigned char& source):TSmMsgSystemEventBase(eventCode, source, SM_M_SYSTEM_EVENT, sizeof(TSmMsgSystemEvent)){}
};

class TMsgSystemEvent : public TSmMsgSystemEventBase
{
public:
	TMsgSystemEvent(const unsigned char& eventCode, const unsigned char& source):TSmMsgSystemEventBase(eventCode, source, M_SYSTEM_EVENT, sizeof(TMsgSystemEvent)){}
};

class TSmMsgResetImbalances : public Message
{
public:
	TSmMsgResetImbalances():Message(SM_M_RESET_IMBALANCES, sizeof(TSmMsgResetImbalances)){}
};

////////////////
class TSmMsgMsLevel1Short: public Message
{
public:
	TSmMsgMsLevel1Short(const unsigned short& symbol = 0,
		const unsigned int& price = 0,
		const unsigned char& side = 0,
		const char& quoteCondition = 0):
		Message(SM_MS_LEVEL1_SHORT, sizeof(TSmMsgMsLevel1Short)),
		m_price(price),
		m_symbol(symbol),
		m_side(side),
		m_quoteCondition(quoteCondition)
	{
	}
	unsigned int m_price;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned short m_symbol;
	unsigned char m_side;//'B' and 'S'
	char m_quoteCondition;
};

class TSmMsgMsLevel1Long: public Message
{
public:
	TSmMsgMsLevel1Long(const unsigned short& symbol = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned char& side = 0,
		const char& quoteCondition = 0):
		Message(SM_MS_LEVEL1_LONG, sizeof(TSmMsgMsLevel1Long)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_symbol(symbol),
		m_side(side),
		m_quoteCondition(quoteCondition)
	{
	}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned short m_symbol;
	unsigned char m_side;//'B' and 'S'
	char m_quoteCondition;
};

class TSmMsgMsImbalanceLong : public Message
{
public:
	TSmMsgMsImbalanceLong(const unsigned short& symbol = 0,
		const unsigned int& farPriceDollar = 0,
		const unsigned int& farPriceFraction = 0,
		const unsigned int& nearPriceDollar = 0,
		const unsigned int& nearPriceFraction = 0,
		const unsigned int& currentReferencePriceDollar = 0,
		const unsigned int& currentReferencePriceFraction = 0,
		const unsigned int& pairedShares = 0,
		const unsigned int& imbalanceShares = 0,
		const unsigned int& marketImbalanceShares = 0,
		const unsigned int& time = 0,
		const unsigned int& auctionTime = 0,
		const char& imbalanceDirection = 0,
		const char& crossType = 0,
		const char& priceVariationIndicator = 0,
		const unsigned char& bookId = 0,
		const bool& regulatory = false,
		const bool& freezeStatus = false):
	
		Message(SM_MS_IMBALANCE_LONG, sizeof(TSmMsgMsImbalanceLong)),
		m_farPriceDollar(farPriceDollar),
		m_farPriceFraction(farPriceFraction),
		m_nearPriceDollar(nearPriceDollar),
		m_nearPriceFraction(nearPriceFraction),
		m_currentReferencePriceDollar(currentReferencePriceDollar),
		m_currentReferencePriceFraction(currentReferencePriceFraction),
		m_pairedShares(pairedShares),
		m_imbalanceShares(imbalanceShares),
		m_marketImbalanceShares(marketImbalanceShares),
		m_time(time),
		m_auctionTime(auctionTime),
		m_symbol(symbol),
		m_imbalanceDirection(imbalanceDirection),
		m_crossType(crossType),
		m_priceVariationIndicator(priceVariationIndicator),
		m_bookID(bookId),
		m_regulatoryImbalance_StockOpen(regulatory ? 1 : 0),
		m_freezeStatus(freezeStatus ? 1 : 0)
	{
	}
	unsigned int m_farPriceDollar;
	unsigned int m_farPriceFraction;
	unsigned int m_nearPriceDollar;
	unsigned int m_nearPriceFraction;
	unsigned int m_currentReferencePriceDollar;
	unsigned int m_currentReferencePriceFraction;
	unsigned int m_pairedShares;
	unsigned int m_imbalanceShares;
	unsigned int m_marketImbalanceShares;
	unsigned int m_time;
	unsigned int m_auctionTime;
	unsigned short m_symbol;
	char m_imbalanceDirection;
	char m_crossType;
	char m_priceVariationIndicator;
	unsigned char m_bookID : 4;
	unsigned char m_regulatoryImbalance_StockOpen : 1;//for ARCA : 1 if market imbalance, 0 if non market imbalance
	unsigned char m_freezeStatus : 1;
};

class TSmMsgMsImbalanceShort : public Message
{
public:
	TSmMsgMsImbalanceShort(const unsigned short& symbol = 0,
		const unsigned int& farPrice = 0,//18 bits for dollar and 14 bits for 4 digits of fraction
		const unsigned int& nearPrice = 0,//18 bits for dollar and 14 bits for 4 digits of fraction
		const unsigned int& currentReferencePrice = 0,//18 bits for dollar and 14 bits for 4 digits of fraction
		const unsigned int& pairedShares = 0,
		const unsigned int& imbalanceShares = 0,
		const unsigned int& marketImbalanceShares = 0,
		const unsigned int& time = 0,
		const unsigned int& auctionTime = 0,
		const char& imbalanceDirection = 0,
		const char& crossType = 0,
		const char& priceVariationIndicator = 0,
		const unsigned char& bookId = 0,
		const bool& regulatory = false,
		const bool& freezeStatus = false):
	
		Message(SM_MS_IMBALANCE_SHORT, sizeof(TSmMsgMsImbalanceShort)),
		m_farPrice(farPrice),
		m_nearPrice(nearPrice),
		m_currentReferencePrice(currentReferencePrice),
		m_pairedShares(pairedShares),
		m_imbalanceShares(imbalanceShares),
		m_marketImbalanceShares(marketImbalanceShares),
		m_time(time),
		m_auctionTime(auctionTime),
		m_symbol(symbol),
		m_imbalanceDirection(imbalanceDirection),
		m_crossType(crossType),
		m_priceVariationIndicator(priceVariationIndicator),
		m_bookID(bookId),
		m_regulatoryImbalance_StockOpen(regulatory ? 1 : 0),//for ARCA : 1 if market imbalance, 0 if non market imbalance
		m_freezeStatus(freezeStatus ? 1 : 0)
	{
	}
	unsigned int m_farPrice;
	unsigned int m_nearPrice;
	unsigned int m_currentReferencePrice;
	unsigned int m_pairedShares;
	unsigned int m_imbalanceShares;
	unsigned int m_marketImbalanceShares;
	unsigned int m_time;
	unsigned int m_auctionTime;
	unsigned short m_symbol;
	char m_imbalanceDirection;
	char m_crossType;
	char m_priceVariationIndicator;
	unsigned char m_bookID : 4;
	unsigned char m_regulatoryImbalance_StockOpen : 1;//for ARCA : 1 if market imbalance, 0 if non market imbalance
	unsigned char m_freezeStatus : 1;
};

class TSmMsgMsTradeLong: public Message
{
public:
	TSmMsgMsTradeLong(const unsigned short& symbol = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned int& size = 0,
		const unsigned int& saleCondition = 0,
		const char& marketCenter = 0):
		Message(SM_MS_TRADE_REPORT_LONG, sizeof(TSmMsgMsTradeLong)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_size(size),
		m_symbol(symbol),
		m_marketCenterID(marketCenter)
	{
		*(unsigned int*)m_saleCondition = saleCondition;
	}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_size;
	char m_saleCondition[4];
	unsigned short m_symbol;
	char m_marketCenterID;
};

class TSmMsgMsTradeShort: public Message
{
public:
	TSmMsgMsTradeShort(const unsigned short& symbol = 0,
		const unsigned int& price = 0,
		const unsigned short& size = 0,
		const char& saleCondition = 0,
		const char& marketCenter = 0):
		Message(SM_MS_TRADE_REPORT_SHORT, sizeof(TSmMsgMsTradeShort)),
		m_symbol(symbol),
		m_price(price),
		m_size(size),
		m_saleCondition(saleCondition),
		m_marketCenterID(marketCenter)
	{
	}
	unsigned int m_price;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned short m_symbol;
	unsigned short m_size;
	char m_saleCondition;
	char m_marketCenterID;
};

class TSmMsgMsTradeError: public TSmMsgTradeErrorBase
{
public:
	TSmMsgMsTradeError(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned __int64& originalReferenceNumber = 0,
		const unsigned int& originalPriceDollars = 0,
		const unsigned int& originalPriceFraction = 0,
		const unsigned int& originalSize = 0,
		const char& originalSaleCondition1 = 0,
		const char& originalSaleCondition2 = 0,
		const char& originalSaleCondition3 = 0,
		const char& originalSaleCondition4 = 0,

		const unsigned int& lastPriceDollars = 0,
		const unsigned int& lastPriceFraction = 0,
		const unsigned int& highPriceDollars = 0,
		const unsigned int& highPriceFraction = 0,
		const unsigned int& lowPriceDollars = 0,
		const unsigned int& lowPriceFraction = 0,
		const unsigned __int64& volume = 0,

		const char& marketCenterID = 0,
		const char& primaryListingMarket = 0,
		const unsigned char& flags = 0):
		TSmMsgTradeErrorBase(symbol,
			time,
			originalReferenceNumber,
			originalPriceDollars,
			originalPriceFraction,
			originalSize,
			originalSaleCondition1,
			originalSaleCondition2,
			originalSaleCondition3,
			originalSaleCondition4,

			lastPriceDollars,
			lastPriceFraction,
			highPriceDollars,
			highPriceFraction,
			lowPriceDollars,
			lowPriceFraction,
			volume,

			marketCenterID,
			primaryListingMarket,
			flags,
			SM_MS_TRADE_CANCEL_ERROR,
			sizeof(TSmMsgMsTradeError))
	{
	}
};

class TSmMsgMsTradeCorrection: public TSmMsgTradeCorrectionBase
{
public:
	TSmMsgMsTradeCorrection(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& originalPriceDollars = 0,
		const unsigned int& originalPriceFraction = 0,
		const unsigned int& correctedPriceDollars = 0,
		const unsigned int& correctedPriceFraction = 0,
		const unsigned int& originalSize = 0,
		const unsigned int& correctedSize = 0,
		const unsigned __int64& originalReferenceNumber = 0,
		const unsigned __int64& correctedReferenceNumber = 0,
		const char& originalSaleCondition1 = 0,
		const char& originalSaleCondition2 = 0,
		const char& originalSaleCondition3 = 0,
		const char& originalSaleCondition4 = 0,
		const char& correctedSaleCondition1 = 0,
		const char& correctedSaleCondition2 = 0,
		const char& correctedSaleCondition3 = 0,
		const char& correctedSaleCondition4 = 0,

		const unsigned int& lastPriceDollars = 0,
		const unsigned int& lastPriceFraction = 0,
		const unsigned int& highPriceDollars = 0,
		const unsigned int& highPriceFraction = 0,
		const unsigned int& lowPriceDollars = 0,
		const unsigned int& lowPriceFraction = 0,
		const unsigned __int64& volume = 0,

		const char& marketCenterID = 0,
		const char& primaryListingMarket = 0,
		const unsigned char& flags = 0):
		TSmMsgTradeCorrectionBase(symbol,
			time,
			originalPriceDollars,
			originalPriceFraction,
			correctedPriceDollars,
			correctedPriceFraction,
			originalSize,
			correctedSize,
			originalReferenceNumber,
			correctedReferenceNumber,
			originalSaleCondition1,
			originalSaleCondition2,
			originalSaleCondition3,
			originalSaleCondition4,
			correctedSaleCondition1,
			correctedSaleCondition2,
			correctedSaleCondition3,
			correctedSaleCondition4,

			lastPriceDollars,
			lastPriceFraction,
			highPriceDollars,
			highPriceFraction,
			lowPriceDollars,
			lowPriceFraction,
			volume,

			marketCenterID,
			primaryListingMarket,
			flags,
			SM_MS_TRADE_CORRECTION,
			sizeof(TSmMsgMsTradeCorrection))
	{
	}
};

class TSmMsgMsEndOfDaySummaryReport : public TSmMsgEndOfDaySummaryReportBase
{
public:
    TSmMsgMsEndOfDaySummaryReport(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& todaysClosePriceDollar = 0,
		const unsigned int& todaysClosePriceFraction = 0,
		const unsigned __int64& volume = 0):
		
		TSmMsgEndOfDaySummaryReportBase(symbol,
			time,
			todaysClosePriceDollar,
			todaysClosePriceFraction,
			volume,
			SM_MS_EOD_SUMMARY_REPORT,
			sizeof(TSmMsgMsEndOfDaySummaryReport))
	{
	}
};

class TSmMsgMsShortSaleIndicators : public TSmMsgShortSaleIndicatorsBase
{
public:
    TSmMsgMsShortSaleIndicators(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const char& shortSaleThresholdIndicator = 0,
		const char& regSHOTestIndicator = 0):

		TSmMsgShortSaleIndicatorsBase(symbol,
			time,
			shortSaleThresholdIndicator,
			regSHOTestIndicator,
			SM_MS_SHORT_SALE_INDICATORS,
			sizeof(TSmMsgMsShortSaleIndicators))
	{
	}
};

class TSmMsgMsPmi : public TSmMsgPmiBase
{
public:
    TSmMsgMsPmi(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& bidDollar = 0,
		const unsigned int& bidFraction = 0,
		const unsigned int& askDollar = 0,
		const unsigned int& askFraction = 0,
		const unsigned char& securityStatus = 0,
		const unsigned char& adjustment = 0):
		TSmMsgPmiBase(symbol,
			time,
			bidDollar,
			bidFraction,
			askDollar,
			askFraction,
			securityStatus,
			adjustment,
			SM_MS_PMI,
			sizeof(TSmMsgMsPmi))
	{
	}
};

#ifdef LRPS
class TSmMsgMsLrp : public TSmMsgLrpBase
{
public:
    TSmMsgMsLrp(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0,
		const unsigned char& changeIndicator = 0):
		TSmMsgLrpBase(symbol,
			time,
			lowDollar,
			lowFraction,
			highDollar,
			highFraction,
			changeIndicator,
			SM_MS_LRP,
			sizeof(TSmMsgMsLrp))
	{
	}
};
#endif

class TSmMsgMsLuld : public TSmMsgLrpBase
{
public:
    TSmMsgMsLuld(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0,
		const unsigned char& changeIndicator = 0):
		TSmMsgLrpBase(symbol,
			time,
			lowDollar,
			lowFraction,
			highDollar,
			highFraction,
			changeIndicator,
			SM_MS_LULD,
			sizeof(TSmMsgMsLuld))
	{
	}
};

class TSmMsgMsTradeTime : public TSmMsgTradeTimeBase
{
public:
    TSmMsgMsTradeTime(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& tradeTime = 0):
		TSmMsgTradeTimeBase(symbol,
			time,
			tradeTime,
			SM_MS_T_TIME,
			sizeof(TSmMsgMsTradeTime))
	{
	}
};

class TSmMsgMsRpi : public TSmMsgRpiBase
{
public:
    TSmMsgMsRpi(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const char& indicator = 0):
		TSmMsgRpiBase(symbol,
			time,
			indicator,
			SM_MS_RPI,
			sizeof(TSmMsgMsRpi))
	{
	}
};

class TSmMsgMsSecurityType : public TSmMsgRpiBase
{
public:
    TSmMsgMsSecurityType(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const char& securityType = 0):
		TSmMsgRpiBase(symbol,
			time,
			securityType,
			SM_MS_SECURITY_TYPE,
			sizeof(TSmMsgMsSecurityType))
	{
	}
};

class TSmMsgMsDividendsAndSplits : public TSmMsgDividendsAndSplitsBase
{
public:
    TSmMsgMsDividendsAndSplits(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& dividendDollar = 0,
		const unsigned int& dividendFraction = 0,
	    const unsigned short& splitNumerator = 0,
		const unsigned short& splitDenominator = 0,
		const unsigned int& exDivDate = 0):
		TSmMsgDividendsAndSplitsBase(symbol,
			time,
			dividendDollar,
			dividendFraction,
			splitNumerator,
			splitDenominator,
			exDivDate,
			SM_MS_DIVIDENDS_AND_SPLITS,
			sizeof(TSmMsgMsDividendsAndSplits))
	{
	}
};

class TSmMsgMsPreviousDayClose : public TSmMsgPreviousDayCloseBase
{
public:
    TSmMsgMsPreviousDayClose(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& closePriceDollar = 0,
		const unsigned int& closePriceFraction = 0):
		TSmMsgPreviousDayCloseBase(symbol,
			time,
			closePriceDollar,
			closePriceFraction,
			SM_MS_PREVIOUS_DAY_CLOSE,
			sizeof(TSmMsgMsPreviousDayClose))
	{
	}
};

class TSmMsgMsStockTradingAction : public TSmMsgStockTradingActionBase
{
public:
	TSmMsgMsStockTradingAction(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const char& tradingState = 0,
		const unsigned int& tradingActionReason = 0):
		TSmMsgStockTradingActionBase(symbol,
			time,
			tradingState,
			tradingActionReason,
			SM_MS_STOCK_TRADING_ACTION,
			sizeof(TSmMsgMsStockTradingAction))
	{
	}
};

class TSmMsgMsResetImbalances : public Message
{
public:
	TSmMsgMsResetImbalances():Message(SM_MS_RESET_IMBALANCES, sizeof(TSmMsgMsResetImbalances)){}
};

//////////////////

class MsgChartPoint
{
public:
	MsgChartPoint():
		m_volume(0),
		m_firstPrice(0),
		m_lastPrice(0),
		m_highPrice(0),
		m_lowPrice(0)
	{
	}
	Price m_moneySpent;
	unsigned int m_volume;
	unsigned int m_firstPrice;//18 bytes for dollars, 14 bytes for 4 digits
	unsigned int m_lastPrice;//18 bytes for dollars, 14 bytes for 4 digits
	unsigned int m_highPrice;//18 bytes for dollars, 14 bytes for 4 digits
	unsigned int m_lowPrice;//18 bytes for dollars, 14 bytes for 4 digits
};


class TSmMsgRespChart : public TMessageRequest
{
public:
	TSmMsgRespChart(const unsigned short& symbol = 0,
		const unsigned int& requestId = 0,
		const unsigned short& minute = 0,
		const unsigned char& tickSize = sizeof(MsgChartPoint),
		const unsigned short& ticks = 0,
		const bool& done = false):
		TMessageRequest(requestId, SM_RESP_CHART, sizeof(TSmMsgRespChart) + ticks * tickSize),
//		m_requestId(requestId),
		m_symbol(symbol),
		m_minute(minute),
		m_tickSize(tickSize),
		m_done(done)
	{
	}
//	unsigned int m_requestId;
	unsigned short	m_symbol;
	unsigned short m_minute;
	unsigned char m_tickSize;
	unsigned char m_done;
};

class TSmMsgNewTick : public TSmMessageSymbol
{
public:
//	unsigned short	m_symbol;
	unsigned short m_minute;
protected:
	TSmMsgNewTick(const unsigned short& symbol,
		const unsigned short& minute,
		const unsigned short& type,
		const unsigned short& length):
		TSmMessageSymbol(symbol, type, length),
		m_minute(minute)
	{
	}
};

class TSmMsgEquityNewTick : public TSmMsgNewTick
{
public:
	TSmMsgEquityNewTick(const unsigned short& symbol = 0, const unsigned short& minute = 0):
		TSmMsgNewTick(symbol, minute, SM_NEW_TICK, sizeof(TSmMsgEquityNewTick))
	{
	}
};

class TMsgEquityMinuteEvent : public TSmMsgNewTick
{
public:
	TMsgEquityMinuteEvent(const unsigned short& symbol = 0, const unsigned short& minute = 0):
		TSmMsgNewTick(symbol, minute, TM_EQUITY_MINUTE_EVENT, sizeof(TMsgEquityMinuteEvent))
	{
	}
};

class TMsgEquityTimeNbboPrint : public TSmMsgNewTick
{
public:
	TMsgEquityTimeNbboPrint(const unsigned short& symbol = 0, const unsigned char& change = 0):
		TSmMsgNewTick(symbol, change, TM_TIME_NBBO_PRINT, sizeof(TMsgEquityTimeNbboPrint))
	{
	}
};

class TSmMsgTickCorrection : public Message
{
public:
	TSmMsgTickCorrection(const unsigned short& symbol = 0,
		const unsigned int& volume = 0,
		const unsigned int& moneyDollars = 0,
		const unsigned int& moneyFraction = 0,
		const unsigned int& first = 0,
		const unsigned int& last = 0,
		const unsigned int& high = 0,
		const unsigned int& low = 0,
		const unsigned short& minute = 0):
		Message(SM_TICK_CORRECTION, sizeof(TSmMsgTickCorrection)),
		m_volume(volume),
		m_moneyDollars(moneyDollars),
		m_moneyFraction(moneyFraction),
		m_first(first),
		m_last(last),
		m_high(high),
		m_low(low),
		m_symbol(symbol),
		m_minute(minute)
	{
	}
	unsigned int m_volume;
	unsigned int m_moneyDollars;
	unsigned int m_moneyFraction;
	unsigned int m_first;
	unsigned int m_last;
	unsigned int m_high;
	unsigned int m_low;
	unsigned short m_symbol;
	unsigned short m_minute;
};

//////////////////
class TMsgHeartbeat : public Message
{
public:
	TMsgHeartbeat(const unsigned __int64& serverTime = 0) : Message(M_HEARTBEAT, sizeof(TMsgHeartbeat)), m_reserved(0), m_serverTime(serverTime){}
 	unsigned int		m_reserved;
	unsigned __int64	m_serverTime;
};

class TMsgDisconnectServerCommand : public Message
{
public:
	TMsgDisconnectServerCommand():Message(M_DISCONNECT, sizeof(TMsgDisconnectServerCommand)), m_reserved(0), m_reserved2(0){}
	unsigned int m_reserved;
	unsigned __int64 m_reserved2;
};

class TMsgText : public Message
{
public:
/*
	TMsgText(const char* const& text = ""):
		Message(M_TEXT, (unsigned short)(sizeof(TMsgText) + __min(strlen( text ), 1000 ) + 1)),
		m_reserved(0)
	{
		strncpy_s((char*)this + sizeof(TMsgText), 1001, text, 1000 );
		((char*)this)[m_length-1] = 0;
	}
*/
	TMsgText(const unsigned short& textLength):
		Message(M_TEXT, sizeof(TMsgText) + textLength),
		m_reserved(0)
	{
	}
 	unsigned int m_reserved;
};

class TMsgDataThreadBufferOverflow : public Message
{
public:
	TMsgDataThreadBufferOverflow(const unsigned int& threadId = 0, const unsigned int& ordinal = 0):Message(TM_DATA_THREAD_BUFFER_OVERFLOW, sizeof(TMsgDataThreadBufferOverflow)), m_threadId(threadId), m_ordinal(ordinal){}
	unsigned int m_threadId;
	unsigned int m_ordinal;
};

class TMsgEntitlementsChanged : public Message//Notified from TD_GetAdminObservable()
{
public:
	TMsgEntitlementsChanged():Message(TM_ENTITLEMENTS_CHANGED, sizeof(TMsgEntitlementsChanged)){}
};

class TMsgExtEntitlementsChanged : public Message//Notified from TD_GetAdminObservable()
{
public:
	TMsgExtEntitlementsChanged():Message(TM_EXT_ENTITLEMENTS_CHANGED, sizeof(TMsgExtEntitlementsChanged)){}
};

class TMsgMarketSorterCleanup : public Message
{
public:
	TMsgMarketSorterCleanup():Message(TM_MARKET_SORTER_CLEANUP, sizeof(TMsgMarketSorterCleanup)){}
};

class TMsgDayStarted : public Message
{
public:
	unsigned int m_date;
protected:
	TMsgDayStarted(const unsigned int& date, const unsigned short& type, const unsigned short& length):Message(type, length), m_date(date){}
};

class TMsgNextDayStarted : public TMsgDayStarted
{
public:
	TMsgNextDayStarted(const unsigned int& date = 0):TMsgDayStarted(date, TM_NEXT_DAY_STARTED, sizeof(TMsgNextDayStarted)){}
};

class TMsgNextUtcDayStarted : public TMsgDayStarted
{
public:
	TMsgNextUtcDayStarted(const unsigned int& date = 0):TMsgDayStarted(date, TM_NEXT_UTC_DAY_STARTED, sizeof(TMsgNextUtcDayStarted)){}
};

class TMsgSystemTimeChanged : public Message
{
public:
	TMsgSystemTimeChanged(const unsigned int& prevMillisecond = 0, const unsigned int& currentMillisecond = 0, const unsigned int& prevDate = 0):Message(TM_SYSTEM_TIME_CHANGED, sizeof(TMsgSystemTimeChanged)), m_prevMillisecond(prevMillisecond), m_currentMillisecond(currentMillisecond), m_prevDate(prevDate){}
	unsigned int m_prevMillisecond;
	unsigned int m_currentMillisecond;
	unsigned int m_prevDate;
};

class TMsgMarketOpen : public Message//Admin Observable
{
public:
	TMsgMarketOpen(const bool& open = false):Message(TM_MARKET_STATUS, sizeof(TMsgMarketOpen)), m_open(open){}
	bool m_open;
};

class TMsgNasdaqMarketStatusChanged : public Message//Admin Observable
{
public:
	TMsgNasdaqMarketStatusChanged(const unsigned char& status = '\0'):Message(TM_NASDAQ_MARKET_STATUS_CHANGED, sizeof(TMsgNasdaqMarketStatusChanged)), m_status(status){}
	unsigned char m_status;//O - MessagesOpen; S - SystemOpen; Q - MarketOpen; M - MarketClosed; E - SystemClosed; C - MessagesClosed
};

class TMessageSymbol : public Message
{
public:
	Symbol m_symbol;
protected:
	TMessageSymbol(const char* const& symbol, const unsigned short& type, const unsigned short& length):
		Message(type, length)
	{
		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}
	TMessageSymbol(const unsigned __int64& symbol, const unsigned short& type, const unsigned short& length):
		Message(type, length)
	{
		*(unsigned __int64*)m_symbol = symbol;
	}
	TMessageSymbol(const unsigned short& type, const unsigned short& length):
		Message(type, length)
	{
		*(unsigned __int64*)m_symbol = 0;
	}
};

class TMessageSymbolChar : public TMessageSymbol
{
public:
	char m_charValue;
protected:
	TMessageSymbolChar(const char* const& symbol, const char& value, const unsigned short& type, const unsigned short& length):
		TMessageSymbol(symbol, type, length),
		m_charValue(value)
	{
	}
	TMessageSymbolChar(const unsigned __int64& symbol, const char& value, const unsigned short& type, const unsigned short& length):
		TMessageSymbol(symbol, type, length),
		m_charValue(value)
	{
	}
};

class TSmMessageSymbolChar : public TSmMessageSymbol
{
public:
	char m_charValue;
protected:
	TSmMessageSymbolChar(const unsigned short& symbol, const char& value, const unsigned short& type, const unsigned short& length):
		TSmMessageSymbol(symbol, type, length),
		m_charValue(value)
	{
	}
};


class TMsgSecurityTickPilot : public TMessageSymbolChar
{
public:
	TMsgSecurityTickPilot(const char* const& symbol, const char& pilotGroup = 0):
		TMessageSymbolChar(symbol, pilotGroup, M_TICK_PILOT, sizeof(TMsgSecurityTickPilot))
	{
	}
	TMsgSecurityTickPilot(const unsigned __int64& symbol = 0, const char& pilotGroup = 0):
		TMessageSymbolChar(symbol, pilotGroup, M_TICK_PILOT, sizeof(TMsgSecurityTickPilot))
	{
	}
};

class TMsgMsSecurityTickPilot : public TMessageSymbolChar
{
public:
	TMsgMsSecurityTickPilot(const char* const& symbol, const char& pilotGroup = 0):
		TMessageSymbolChar(symbol, pilotGroup, M_MS_TICK_PILOT, sizeof(TMsgMsSecurityTickPilot))
	{
	}
	TMsgMsSecurityTickPilot(const unsigned __int64& symbol = 0, const char& pilotGroup = 0):
		TMessageSymbolChar(symbol, pilotGroup, M_MS_TICK_PILOT, sizeof(TMsgMsSecurityTickPilot))
	{
	}
};

class TSmMsgSecurityTickPilot : public TSmMessageSymbolChar
{
public:
    TSmMsgSecurityTickPilot(const unsigned short& symbol = 0, const char& pilotGroup = 0):
		TSmMessageSymbolChar(symbol, pilotGroup, SM_M_TICK_PILOT, sizeof(TSmMsgSecurityTickPilot))
	{
	}
};

class TSmMsgMsSecurityTickPilot : public TSmMessageSymbolChar
{
public:
    TSmMsgMsSecurityTickPilot(const unsigned short& symbol = 0, const char& pilotGroup = 0):
		TSmMessageSymbolChar(symbol, pilotGroup, SM_MS_TICK_PILOT, sizeof(TSmMsgMsSecurityTickPilot))
	{
	}
};

class TMessageOptionBlock : public TMessageSymbol
{
public:
#ifndef TAKION_NO_OPTIONS
	unsigned __int64 m_optionBlock;
#endif
protected:
	TMessageOptionBlock(const char* const& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
#endif
		const unsigned short& type, const unsigned short& length):
		TMessageSymbol(symbol, type, length)
#ifndef TAKION_NO_OPTIONS
		, m_optionBlock(optionBlock)
#endif
	{
	}
	TMessageOptionBlock(const unsigned __int64& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
#endif
		const unsigned short& type, const unsigned short& length):
		TMessageSymbol(symbol, type, length)
#ifndef TAKION_NO_OPTIONS
		, m_optionBlock(optionBlock)
#endif
	{
	}
	TMessageOptionBlock(const unsigned short& type, const unsigned short& length):
		TMessageSymbol(type, length)
#ifndef TAKION_NO_OPTIONS
		, m_optionBlock(0)
#endif
	{
	}
};

//Used in Extensions. When you call function TD_NotifyAllObjectsInThread, all the objects defined by the "unsigned int echoNotificationObjectMask", will be notified in their worker thread with this Message.
//echoNotificationObjectMask is composed of the flags from enum EchoNotificationObjectId.
//m_echoId must be >= TU_GetSecurityMinCustomEchoId()
class TMessageObjectEcho : public Message
{
public:
	TMessageObjectEcho(const unsigned int& echoId):
		Message(TM_OBJECT_ECHO, sizeof(TMessageObjectEcho)), m_echoId(echoId)
	{
	}
	unsigned int m_echoId;
};

class TMessageSecurityEcho : public TMessageSymbol
{
public:
	unsigned int m_echoId;
protected:
	TMessageSecurityEcho(const char* const& symbol, const unsigned int& echoId, const unsigned short& type, const unsigned short& length):
		TMessageSymbol(symbol, type, length),
		m_echoId(echoId)
	{
	}
	TMessageSecurityEcho(const unsigned __int64& symbol, const unsigned int& echoId, const unsigned short& type, const unsigned short& length):
		TMessageSymbol(symbol, type, length),
		m_echoId(echoId)
	{
	}
};

//The following 3 messages can be sent to the Security/Option thread, using function Security::WriteEchoMessageToSecurityThread, and the InThread Observers will be notified.
//Use function GetMinCustomEchoId() to get the min echoId that Takion will accept from an Extension.
//These can be used for initializing some custom data structures from the Worker Thread, so that there is no disparity with the incoming updates.
//AddInThreadObserver should be called before WriteEchoMessageToSecurityThread for guaranteed notification.
class TMessageStockEcho : public TMessageSecurityEcho
{
public:
	TMessageStockEcho(const char* const& symbol, const unsigned int& echoId):
		TMessageSecurityEcho(symbol, echoId, TM_STOCK_ECHO, sizeof(TMessageStockEcho))
	{
	}
	TMessageStockEcho(const unsigned __int64& symbol, const unsigned int& echoId):
		TMessageSecurityEcho(symbol, echoId, TM_STOCK_ECHO, sizeof(TMessageStockEcho))
	{
	}
};

class TMessageSortableStockEcho : public TMessageSecurityEcho
{
public:
	TMessageSortableStockEcho(const char* const& symbol, const unsigned int& echoId):
		TMessageSecurityEcho(symbol, echoId, TM_SORTABLE_STOCK_ECHO, sizeof(TMessageSortableStockEcho))
	{
	}
	TMessageSortableStockEcho(const unsigned __int64& symbol, const unsigned int& echoId):
		TMessageSecurityEcho(symbol, echoId, TM_SORTABLE_STOCK_ECHO, sizeof(TMessageSortableStockEcho))
	{
	}
};

class TMessageExpirationTimer : public Message //From TD_GetExpirationObservable
{
public:
	TMessageExpirationTimer(const unsigned int& currentMillisecond = 0):
		Message(TM_EXPIRATION_TIMER, sizeof(TMessageExpirationTimer)),
		m_currentMillisecond(currentMillisecond)
	{
	}
	unsigned int m_currentMillisecond;
};

#ifndef TAKION_NO_OPTIONS
class TMessageOptionEcho : public TMessageOptionBlock
{
public:
	TMessageOptionEcho(const char* const& symbol, const unsigned __int64& optionBlock, const unsigned int& echoId):
		TMessageOptionBlock(symbol, optionBlock, TM_OPTION_ECHO, sizeof(TMessageOptionBlock)),
		m_echoId(echoId)
	{
	}
	TMessageOptionEcho(const unsigned __int64& symbol, const unsigned __int64& optionBlock, const unsigned int& echoId):
		TMessageOptionBlock(symbol, optionBlock, TM_OPTION_ECHO, sizeof(TMessageOptionBlock)),
		m_echoId(echoId)
	{
	}
	unsigned int m_echoId;
};

class TMessageFutureEcho : public TMessageSecurityEcho
{
public:
	TMessageFutureEcho(const char* const& symbol, const unsigned int& echoId) :
		TMessageSecurityEcho(symbol, echoId, TM_FUTURE_ECHO, sizeof(TMessageFutureEcho))
	{
	}
	TMessageFutureEcho(const unsigned __int64& symbol, const unsigned int& echoId) :
		TMessageSecurityEcho(symbol, echoId, TM_FUTURE_ECHO, sizeof(TMessageFutureEcho))
	{
	}
};

#endif

enum QuoteMoveCode : unsigned char
{
	QMC_NEW,
	QMC_JOIN,
	QMC_LEAVE,
	QMC_DROP,

	QMC_PRINT_HIGH,
	QMC_PRINT_LOW,
//	QMC_PRINT_SAME,

	QMC_PRINT_ODD_HIGH,
	QMC_PRINT_ODD_LOW,
//	QMC_PRINT_ODD_SAME,

	QMC_LEVEL1_HIGH,
	QMC_LEVEL1_LOW,

	QMC_COUNT
};

class TMsgQuoteMove : public TMessageOptionBlock
{
public:
	TMsgQuoteMove(const unsigned __int64& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
#endif
		const unsigned int& currentMillisecond,
		const unsigned int& bid,
		const unsigned int& ask,
		const unsigned int& todaysClosePrice,
		const unsigned int& bidSize,
		const unsigned int& askSize,
		const unsigned int& printPrice,
		const unsigned int& printSize,
		const unsigned int& posPrice,
		const unsigned int& posInventoryPrice,
		const int& posSize,
		const int& posInventorySize,
		const unsigned int& lastExecPrice,
		const int& lastExecSize,
		const unsigned int& mmid,
		const unsigned short& roundLot,
		const unsigned char& code,
		const bool& side,
		const unsigned char& positionStatus,
		const unsigned char& inventoryPositionStatus):
		TMessageOptionBlock(symbol,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
#endif
			TM_QUOTE_MOVE, sizeof(TMsgQuoteMove)),
		m_currentMillisecond(currentMillisecond),
		m_bid(bid),
		m_ask(ask),
		m_todaysClosePrice(todaysClosePrice),
		m_bidSize(bidSize),
		m_askSize(askSize),
		m_printPrice(printPrice),
		m_printSize(printSize),
		m_posPrice(posPrice),
		m_posInventoryPrice(posInventoryPrice),
		m_posSize(posSize),
		m_posInventorySize(posInventorySize),
		m_lastExecPrice(lastExecPrice),
		m_lastExecSize(lastExecSize),
		m_mmid(mmid),
		m_roundLot(roundLot),
		m_code(code),
		m_side(side),
		m_positionStatus(positionStatus),
		m_inventoryPositionStatus(inventoryPositionStatus)
	{
	}
	unsigned int m_currentMillisecond;
	unsigned int m_bid;
	unsigned int m_ask;
	unsigned int m_todaysClosePrice;
	unsigned int m_bidSize;
	unsigned int m_askSize;
	unsigned int m_printPrice;
	unsigned int m_printSize;
	unsigned int m_posPrice;
	unsigned int m_posInventoryPrice;
	int m_posSize;
	int m_posInventorySize;
	unsigned int m_lastExecPrice;
	int m_lastExecSize;
	unsigned int m_mmid;
	unsigned short m_roundLot;
	unsigned char m_code;
	bool m_side;
	unsigned char m_positionStatus;
	unsigned char m_inventoryPositionStatus;
};

class TMessageSymbolMap : public Message
{
public:
	unsigned short m_symbolMap;
protected:
	TMessageSymbolMap(const unsigned short& symbolMap, const unsigned short& type, const unsigned short& length):Message(type, length),m_symbolMap(symbolMap){}
};

class TMessageTimeSymbol : public TMessageTime
{
public:
	Symbol m_symbol;
protected:
	TMessageTimeSymbol(const char* const& symbol, const unsigned int& time, const unsigned short& type, const unsigned short& length):
		TMessageTime(time, type, length)
	{
		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}
	TMessageTimeSymbol(const unsigned __int64& symbol, const unsigned int& time, const unsigned short& type, const unsigned short& length):
		TMessageTime(time, type, length)
	{
		*(unsigned __int64*)m_symbol = symbol;
	}
};

class TMsgAverageDailyVolume : public TMessageTimeSymbol
{
public:
	TMsgAverageDailyVolume(const char* const& symbol,
		const unsigned int& time = 0,
		const unsigned __int64& volume = 0):
		TMessageTimeSymbol(symbol, time, M_AVERAGE_DAILY_VOLUME, sizeof(TMsgAverageDailyVolume)),
		m_volume(volume)
	{
	}
	TMsgAverageDailyVolume(const unsigned __int64& symbol = 0,
		const unsigned int& time = 0,
		const unsigned __int64& volume = 0):
		TMessageTimeSymbol(symbol, time, M_AVERAGE_DAILY_VOLUME, sizeof(TMsgAverageDailyVolume)),
		m_volume(volume)
	{
	}
	unsigned __int64 m_volume;
};

class TMsgHighLowBase : public TMessageTimeSymbol
{
public:
	unsigned int m_lowDollar;
	unsigned int m_lowFraction;
	unsigned int m_highDollar;
	unsigned int m_highFraction;
protected:
	TMsgHighLowBase(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& lowDollar,
		const unsigned int& lowFraction,
		const unsigned int& highDollar,
		const unsigned int& highFraction,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_lowDollar(lowDollar),
		m_lowFraction(lowFraction),
		m_highDollar(highDollar),
		m_highFraction(highFraction)
	{
	}
	TMsgHighLowBase(const unsigned __int64& symbol,
		const unsigned int& time,
		const unsigned int& lowDollar,
		const unsigned int& lowFraction,
		const unsigned int& highDollar,
		const unsigned int& highFraction,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_lowDollar(lowDollar),
		m_lowFraction(lowFraction),
		m_highDollar(highDollar),
		m_highFraction(highFraction)
	{
	}
};

class TMsgHighLow2Base : public TMsgHighLowBase
{
public:
	unsigned int m_lowDollar2;
	unsigned int m_lowFraction2;
	unsigned int m_highDollar2;
	unsigned int m_highFraction2;
protected:
	TMsgHighLow2Base(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& lowDollar,
		const unsigned int& lowFraction,
		const unsigned int& highDollar,
		const unsigned int& highFraction,
		const unsigned int& lowDollar2,
		const unsigned int& lowFraction2,
		const unsigned int& highDollar2,
		const unsigned int& highFraction2,
		const unsigned short& type,
		const unsigned short& length):
		TMsgHighLowBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction,type, length),
		m_lowDollar2(lowDollar2),
		m_lowFraction2(lowFraction2),
		m_highDollar2(highDollar2),
		m_highFraction2(highFraction2)
	{
	}
	TMsgHighLow2Base(const unsigned __int64& symbol,
		const unsigned int& time,
		const unsigned int& lowDollar,
		const unsigned int& lowFraction,
		const unsigned int& highDollar,
		const unsigned int& highFraction,
		const unsigned int& lowDollar2,
		const unsigned int& lowFraction2,
		const unsigned int& highDollar2,
		const unsigned int& highFraction2,
		const unsigned short& type,
		const unsigned short& length):
		TMsgHighLowBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction, type, length),
		m_lowDollar2(lowDollar2),
		m_lowFraction2(lowFraction2),
		m_highDollar2(highDollar2),
		m_highFraction2(highFraction2)
	{
	}
};

class TMsg52Week30DayHighLow : public TMsgHighLow2Base
{
public:
	TMsg52Week30DayHighLow(const char* const& symbol,
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0,
		const unsigned int& lowDollar2 = 0,
		const unsigned int& lowFraction2 = 0,
		const unsigned int& highDollar2 = 0,
		const unsigned int& highFraction2 = 0):
		TMsgHighLow2Base(symbol,
			time,
			lowDollar,
			lowFraction,
			highDollar,
			highFraction,
			lowDollar2,
			lowFraction2,
			highDollar2,
			highFraction2,
			M_52WEEK_30DAY_HIGH_LOW,
			sizeof(TMsg52Week30DayHighLow))
	{
	}
	TMsg52Week30DayHighLow(const unsigned __int64& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0,
		const unsigned int& lowDollar2 = 0,
		const unsigned int& lowFraction2 = 0,
		const unsigned int& highDollar2 = 0,
		const unsigned int& highFraction2 = 0):
		TMsgHighLow2Base(symbol,
			time,
			lowDollar,
			lowFraction,
			highDollar,
			highFraction,
			lowDollar2,
			lowFraction2,
			highDollar2,
			highFraction2,
			M_52WEEK_30DAY_HIGH_LOW,
			sizeof(TMsg52Week30DayHighLow))
	{
	}
};

class TMsgMs52Week30DayHighLow : public TMsgHighLow2Base
{
public:
	TMsgMs52Week30DayHighLow(const char* const& symbol,
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0,
		const unsigned int& lowDollar2 = 0,
		const unsigned int& lowFraction2 = 0,
		const unsigned int& highDollar2 = 0,
		const unsigned int& highFraction2 = 0):
		TMsgHighLow2Base(symbol,
			time,
			lowDollar,
			lowFraction,
			highDollar,
			highFraction,
			lowDollar2,
			lowFraction2,
			highDollar2,
			highFraction2,
			M_MS_52WEEK_30DAY_HIGH_LOW,
			sizeof(TMsgMs52Week30DayHighLow))
	{
	}
	TMsgMs52Week30DayHighLow(const unsigned __int64& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0,
		const unsigned int& lowDollar2 = 0,
		const unsigned int& lowFraction2 = 0,
		const unsigned int& highDollar2 = 0,
		const unsigned int& highFraction2 = 0):
		TMsgHighLow2Base(symbol,
			time,
			lowDollar,
			lowFraction,
			highDollar,
			highFraction,
			lowDollar2,
			lowFraction2,
			highDollar2,
			highFraction2,
			M_MS_52WEEK_30DAY_HIGH_LOW,
			sizeof(TMsgMs52Week30DayHighLow))
	{
	}
};
/*
enum Top10Type : unsigned char
{
	Top10_Volume,
	Top10_NetGainers,
	Top10_NetLosers,
	Top10_NetGainersPercent,
	Top10_NetLosersPercent,

	Top10_Count
};
*/
struct Top10Node
{
//public:
	Top10Node(const unsigned __int64& symbol = 0, const unsigned int& value = 0, const unsigned int& lastPrice = 0):
		m_value(value),
		m_lastPrice(lastPrice)
	{
		*(unsigned __int64*)m_symbol = symbol;
	}
	Symbol m_symbol;
	int m_value;
	unsigned int m_lastPrice;
};

//M_MS_TOP_10
class TMsgTop10Base : public TMessageTime
{
public:
	unsigned char m_top10Type;
	Top10Node m_nodes[10];
protected:
	TMsgTop10Base(const unsigned int& time,
		const unsigned char& top10Type,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTime(time, type, length),
		m_top10Type(top10Type)
	{
	}
};

//MD Top 10
class TMsgTop10 : public TMsgTop10Base
{
public:
	TMsgTop10(const unsigned int& time = 0,
		const unsigned char& top10Type = 0):
		TMsgTop10Base(time, top10Type, M_TOP_10, sizeof(TMsgTop10))
	{
	}
};

class TSmMsgTop10 : public TMsgTop10Base
{
public:
	TSmMsgTop10(const unsigned int& time = 0,
		const unsigned char& top10Type = 0) :
		TMsgTop10Base(time, top10Type, SM_M_TOP_10, sizeof(TSmMsgTop10))
	{
	}
};

//MS Top 10
class TMsgMsTop10 : public TMsgTop10Base
{
public:
	TMsgMsTop10(const unsigned int& time = 0,
		const unsigned char& top10Type = 0) :
		TMsgTop10Base(time, top10Type, M_MS_TOP_10, sizeof(TMsgMsTop10))
	{
	}
};

class TSmMsgMsTop10 : public TMsgTop10Base
{
public:
	TSmMsgMsTop10(const unsigned int& time = 0,
		const unsigned char& top10Type = 0) :
		TMsgTop10Base(time, top10Type, SM_MS_TOP_10, sizeof(TSmMsgMsTop10))
	{
	}
};

class TMsgPreviousDayHighLow : public TMsgHighLowBase
{
public:
	TMsgPreviousDayHighLow(const char* const& symbol,
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0):
		TMsgHighLowBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction, M_PREVIOUS_DAY_HIGH_LOW, sizeof(TMsgPreviousDayHighLow))
	{
	}
	TMsgPreviousDayHighLow(const unsigned __int64& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0):
		TMsgHighLowBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction, M_PREVIOUS_DAY_HIGH_LOW, sizeof(TMsgPreviousDayHighLow))
	{
	}
};

class TSmMsgAverageDailyVolumeBase : public TMessageTime
{
public:
	unsigned __int64 m_volume;
	unsigned short m_symbol;
protected:
	TSmMsgAverageDailyVolumeBase(const unsigned short& symbol,
		const unsigned int& time,
		const unsigned __int64& volume,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTime(time, type, length),
		m_volume(volume),
		m_symbol(symbol)
	{
	}
};

class TSmMsgAverageDailyVolume : public TSmMsgAverageDailyVolumeBase
{
public:
	TSmMsgAverageDailyVolume(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned __int64& volume = 0):
		TSmMsgAverageDailyVolumeBase(symbol, time, volume, SM_M_AVERAGE_DAILY_VOLUME, sizeof(TSmMsgAverageDailyVolume))
	{
	}
};

class TSmMsgPreviousDayHighLowBase : public TSmMsgHighLowBase
{
public:
	unsigned short m_symbol;
protected:
	TSmMsgPreviousDayHighLowBase(const unsigned short& symbol,
		const unsigned int& time,
		const unsigned int& lowDollar,
		const unsigned int& lowFraction,
		const unsigned int& highDollar,
		const unsigned int& highFraction,
		const unsigned short& type,
		const unsigned short& length):
		TSmMsgHighLowBase(time, lowDollar, lowFraction, highDollar, highFraction, type, length),
		m_symbol(symbol)
	{
	}
};

class TSmMsgPreviousDayHighLow : public TSmMsgPreviousDayHighLowBase
{
public:
	TSmMsgPreviousDayHighLow(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0):
		TSmMsgPreviousDayHighLowBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction, SM_M_PREVIOUS_DAY_HIGH_LOW, sizeof(TSmMsgPreviousDayHighLow))
	{
	}
};

class TMsgMsAverageDailyVolume : public TMessageTimeSymbol
{
public:
	TMsgMsAverageDailyVolume(const char* const& symbol,
		const unsigned int& time = 0,
		const unsigned __int64& volume = 0):
		TMessageTimeSymbol(symbol, time, M_MS_AVERAGE_DAILY_VOLUME, sizeof(TMsgMsAverageDailyVolume)),
		m_volume(volume)
	{
	}
	TMsgMsAverageDailyVolume(const unsigned __int64& symbol = 0,
		const unsigned int& time = 0,
		const unsigned __int64& volume = 0):
		TMessageTimeSymbol(symbol, time, M_MS_AVERAGE_DAILY_VOLUME, sizeof(TMsgMsAverageDailyVolume)),
		m_volume(volume)
	{
	}
	unsigned __int64 m_volume;
};

class TMsgMsPreviousDayHighLow : public TMsgHighLowBase
{
public:
	TMsgMsPreviousDayHighLow(const char* const& symbol,
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0):
		TMsgHighLowBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction, M_MS_PREVIOUS_DAY_HIGH_LOW, sizeof(TMsgMsPreviousDayHighLow))
	{
	}
	TMsgMsPreviousDayHighLow(const unsigned __int64& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0):
		TMsgHighLowBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction, M_MS_PREVIOUS_DAY_HIGH_LOW, sizeof(TMsgMsPreviousDayHighLow))
	{
	}
};

class TSmMsgMsAverageDailyVolume : public TSmMsgAverageDailyVolumeBase
{
public:
	TSmMsgMsAverageDailyVolume(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned __int64& volume = 0):
		TSmMsgAverageDailyVolumeBase(symbol, time, volume, SM_MS_AVERAGE_DAILY_VOLUME, sizeof(TSmMsgMsAverageDailyVolume))
	{
	}
};

class TSmMsgMsPreviousDayHighLow : public TSmMsgPreviousDayHighLowBase
{
public:
	TSmMsgMsPreviousDayHighLow(const unsigned short& symbol = 0,
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0):
		TSmMsgPreviousDayHighLowBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction, SM_MS_PREVIOUS_DAY_HIGH_LOW, sizeof(TSmMsgMsPreviousDayHighLow))
	{
	}
};

class TMessageStockAddTrade : public TMessageTimeSymbol
{
public:
	unsigned int m_l1Bid;
	unsigned int m_l1Ask;
	unsigned int m_dollars;
	unsigned int m_dollarFraction;
	unsigned int m_quantity;
	unsigned int m_roundLot;
	unsigned int m_mmid;
	unsigned short m_shortMmid;
	short m_delay;
	unsigned char m_source;
	unsigned char m_level1;
protected:
	TMessageStockAddTrade(
		const char* const& symbol,
		const Trade& trade,
		const unsigned int& l1Bid,	
		const unsigned int& l1Ask,
		const unsigned int& roundLot,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTimeSymbol(symbol, trade.GetMillisecond(), type, length),
		m_l1Bid(l1Bid),
		m_l1Ask(l1Ask),
		m_dollars(trade.GetDollars()),
		m_dollarFraction(trade.GetDollarFraction()),
		m_quantity(trade.GetQuantity()),
		m_roundLot(roundLot),
		m_mmid(trade.GetMmid()),
		m_shortMmid(trade.GetShortMmid()),
		m_delay(trade.GetDelay()),
		m_source(trade.GetSource()),
		m_level1(trade.GetLevel1())
	{
	}
#ifdef UPDATE_PRINT_MESSAGE
	TMessageStockAddTrade(const unsigned __int64& symbol,
		const Trade& trade,
		const unsigned int& roundLot,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTimeSymbol(symbol, trade.GetMillisecond(), type, length),
		m_dollars(trade.GetDollars()),
		m_dollarFraction(trade.GetDollarFraction()),
		m_quantity(trade.GetQuantity()),
		m_roundLot(roundLot),
		m_mmid(trade.GetMmid()),
		m_delay(trade.GetDelay()),
		m_source(trade.GetSource()),
		m_level1(trade.GetLevel1())
	{
	}
#endif
};

class TMsgStockAddPrint : public TMessageStockAddTrade
{
public:
	TMsgStockAddPrint(
		const char* const& symbol,
		const NamedPrint& np,
		const unsigned int& l1Bid,
		const unsigned int& l1Ask,
		const unsigned int& roundLot,
		const unsigned int& volumeAtPrice,
		const unsigned int& maxVolumeAtPrice,
		const unsigned int& totalVolume):
		TMessageStockAddTrade(
			symbol,
			np,
			l1Bid,	
			l1Ask,
			roundLot,
			TM_STOCK_ADD_PRINT, sizeof(TMsgStockAddPrint)),
		m_saleCondition1(np.GetSaleCondition1()),
		m_saleCondition2(np.GetSaleCondition2()),
		m_saleCondition3(np.GetSaleCondition3()),
		m_saleCondition4(np.GetSaleCondition4()),
		m_volumeAtPrice(volumeAtPrice),
		m_maxVolumeAtPrice(maxVolumeAtPrice),
		m_totalVolume(totalVolume)
	{
	}
#ifdef UPDATE_PRINT_MESSAGE
	TMsgStockAddPrint(const unsigned __int64& symbol, const NamedPrint& np, const unsigned int& roundLot):
		TMessageStockAddTrade(symbol, np, roundLot, TM_STOCK_ADD_PRINT, sizeof(TMsgStockAddPrint)),
		m_saleCondition1(np.GetSaleCondition1()),
		m_saleCondition2(np.GetSaleCondition2()),
		m_saleCondition3(np.GetSaleCondition3()),
		m_saleCondition4(np.GetSaleCondition4())
	{
	}
#endif
	char m_saleCondition1;
	char m_saleCondition2;
	char m_saleCondition3;
	char m_saleCondition4;
	unsigned int m_volumeAtPrice;
	unsigned int m_maxVolumeAtPrice;
	unsigned int m_totalVolume;
};

class TMsgStockAddBookExecution : public TMessageStockAddTrade
{
public:
	TMsgStockAddBookExecution(
		const char* const& symbol,
		const NamedBookExecution& nbe,
		const unsigned int& l1Bid,	
		const unsigned int& l1Ask,
		const unsigned int& roundLot):
		TMessageStockAddTrade(
			symbol,
			nbe,
			l1Bid,	
			l1Ask,
			roundLot,
			TM_STOCK_ADD_BOOK_EXECUTION, sizeof(TMsgStockAddBookExecution)),
		m_label(nbe.GetLabel()),
		m_side(nbe.GetSide()),
		m_hidden(nbe.isHidden())
	{
	}
#ifdef UPDATE_PRINT_MESSAGE
	TMsgStockAddBookExecution(const unsigned __int64& symbol, const NamedBookExecution& nbe, const unsigned int& roundLot):
		TMessageStockAddTrade(symbol, roundLot, nbe, TM_STOCK_ADD_BOOK_EXECUTION, sizeof(TMsgStockAddBookExecution)),
		m_label(nbe.GetLabel()),
		m_side(nbe.GetSide()),
		m_hidden(nbe.isHidden())
	{
	}
#endif
	char m_label;
	unsigned char m_side;
	bool m_hidden;
};
//#endif

class TMessageSymbolMapUpdate : public TMessageSymbolMap
{
public:
	unsigned int m_updateOrdinal;
protected:
	TMessageSymbolMapUpdate(const unsigned short& code, const unsigned int& updateOrdinal, const unsigned short& type, const unsigned short& length):TMessageSymbolMap(code, type, length), m_updateOrdinal(updateOrdinal){}
};


class TMessageStockUpdate : public TMessageSymbol
{
public:
	unsigned int m_updateOrdinal;
protected:
	TMessageStockUpdate(const char* const& symbol, const unsigned int& updateOrdinal, const unsigned short& type, const unsigned short& length):TMessageSymbol(symbol, type, length), m_updateOrdinal(updateOrdinal){}
	TMessageStockUpdate(const unsigned __int64& symbol, const unsigned int& updateOrdinal, const unsigned short& type, const unsigned short& length):TMessageSymbol(symbol, type, length), m_updateOrdinal(updateOrdinal){}
};

class TMsgStockUpdateLevel2 : public TMessageStockUpdate
{
public:
	TMsgStockUpdateLevel2(const char* const& symbol, const unsigned int& updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_STOCK_UPDATE_LEVEL2, sizeof(TMsgStockUpdateLevel2)){}
	TMsgStockUpdateLevel2(const unsigned __int64& symbol, const unsigned int& updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_STOCK_UPDATE_LEVEL2, sizeof(TMsgStockUpdateLevel2)){}
};

class TMsgStockRefreshed : public TMessageStockUpdate
{
public:
	TMsgStockRefreshed(const char* const& symbol, const unsigned int& updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_STOCK_REFRESHED, sizeof(TMsgStockRefreshed)){}
	TMsgStockRefreshed(const unsigned __int64& symbol, const unsigned int& updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_STOCK_REFRESHED, sizeof(TMsgStockRefreshed)){}
};

class TMsgStockClosed : public TMessageSymbol
{
public:
	TMsgStockClosed(const char* const& symbol):TMessageSymbol(symbol, TM_STOCK_CLOSED, sizeof(TMsgStockClosed)){}
	TMsgStockClosed(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_STOCK_CLOSED, sizeof(TMsgStockClosed)){}
};

class TMsgStockOpened : public TMessageSymbol
{
public:
	TMsgStockOpened(const char* const& symbol):TMessageSymbol(symbol, TM_STOCK_OPENED, sizeof(TMsgStockOpened)){}
	TMsgStockOpened(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_STOCK_OPENED, sizeof(TMsgStockOpened)){}
};

class TMsgNewsHeadlineCount : public TMessageSymbolMap //Posted to worker thread from main thread
{
public:
	unsigned int m_headlineCount;
	bool m_historical;
	unsigned __int64 m_dateTime;
protected:
	TMsgNewsHeadlineCount(const unsigned short& code,
		const unsigned int& headlineCount,
		const bool& historical,
		const unsigned __int64& dateTime,
		const unsigned short& type,
		const unsigned short& length):
		TMessageSymbolMap(code, type, length),
		m_headlineCount(headlineCount),
		m_historical(historical),
		m_dateTime(dateTime)
	{
	}
};

class TMsgEquityNewsHeadlineCount : public TMsgNewsHeadlineCount //Posted to worker thread from main thread
{
public:
	TMsgEquityNewsHeadlineCount(const unsigned short& code,
		const unsigned int& headlineCount,
		const bool& historical,
		const unsigned __int64& dateTime):
		TMsgNewsHeadlineCount(code, headlineCount, historical, dateTime, TM_SORTABLE_SECURITY_NEWS_HEADLINE_COUNT, sizeof(TMsgEquityNewsHeadlineCount))
	{
	}
};

class TMsgStockNewsHeadlineCount : public TMsgNewsHeadlineCount //Posted to worker thread from main thread
{
public:
	TMsgStockNewsHeadlineCount(const unsigned short& code,
		const unsigned int& headlineCount,
		const bool& historical,
		const unsigned __int64& dateTime):
		TMsgNewsHeadlineCount(code, headlineCount, historical, dateTime, TM_SECURITY_NEWS_HEADLINE_COUNT, sizeof(TMsgStockNewsHeadlineCount))
	{
	}
};

class TMsgEquityClosed : public TMessageSymbolMap
{
public:
	TMsgEquityClosed(const unsigned short& code):TMessageSymbolMap(code, TM_EQUITY_CLOSED, sizeof(TMsgEquityClosed)){}
};

class TMsgEquityYesterdaysClosePriceChanged : public TMessageSymbolMap
{
public:
	TMsgEquityYesterdaysClosePriceChanged(const unsigned short& code):TMessageSymbolMap(code, TM_EQUITY_YEST_CLOSE_PRICE_CHANGED, sizeof(TMsgEquityYesterdaysClosePriceChanged)){}
};

class TMsgStockYesterdaysClosePriceChanged : public TMessageSymbolMap
{
public:
	TMsgStockYesterdaysClosePriceChanged(const unsigned short& code):
		TMessageSymbolMap(code, TM_STOCK_YEST_CLOSE_PRICE_CHANGED, sizeof(TMsgStockYesterdaysClosePriceChanged))
	{
	}
};

#ifndef TAKION_NO_OPTIONS
class TMsgOptionOpenIterestChanged : public TMessageOptionBlock
{
public:
	TMsgOptionOpenIterestChanged(const char* const& symbol, const unsigned __int64& optionBlock):
		TMessageOptionBlock(symbol, optionBlock, TM_OPTION_OPEN_INTEREST_CHANGED, sizeof(TMsgOptionOpenIterestChanged))
	{
	}
	TMsgOptionOpenIterestChanged(const unsigned __int64& symbol, const unsigned __int64& optionBlock) :
		TMessageOptionBlock(symbol, optionBlock, TM_OPTION_OPEN_INTEREST_CHANGED, sizeof(TMsgOptionOpenIterestChanged))
	{
	}
};

class TMsgFutureOpenIterestChanged : public TMessageSymbolMap//TMessageSymbol
{
public:
	TMsgFutureOpenIterestChanged(const unsigned short& code):
		TMessageSymbolMap(code, TM_FUTURE_OPEN_INTEREST_CHANGED, sizeof(TMsgFutureOpenIterestChanged))
	{
	}
/*
	TMsgFutureOpenIterestChanged(const char* const& symbol):
		TMessageSymbol(symbol, TM_FUTURE_OPEN_INTEREST_CHANGED, sizeof(TMsgFutureOpenIterestChanged))
	{
	}
	TMsgFutureOpenIterestChanged(const unsigned __int64& symbol) :
		TMessageSymbol(symbol, TM_FUTURE_OPEN_INTEREST_CHANGED, sizeof(TMsgFutureOpenIterestChanged))
	{
	}
*/
};
#endif

class TMsgEquityOpened : public TMessageSymbolMap
{
public:
	TMsgEquityOpened(const unsigned short& code):
		TMessageSymbolMap(code, TM_EQUITY_OPENED, sizeof(TMsgEquityOpened))
	{
	}
};

/*in TakionUtils.h
enum SymbolType : unsigned char
{
	EST_UNKNOWN,
	EST_STOCK,
	EST_BASKET,
};
*/
class TMsgSymbolTypedInActiveCommandWindow : public TMessageSymbol
{
public:
	TMsgSymbolTypedInActiveCommandWindow(const char* const& symbol, const unsigned char& basket):
		TMessageSymbol(symbol, TM_SYMBOL_TYPED, sizeof(TMsgSymbolTypedInActiveCommandWindow)),
		m_basket(basket)
	{
	}
	TMsgSymbolTypedInActiveCommandWindow(const unsigned __int64& symbol, const unsigned char& basket):
		TMessageSymbol(symbol, TM_SYMBOL_TYPED, sizeof(TMsgSymbolTypedInActiveCommandWindow)),
		m_basket(basket)
	{
	}
	unsigned char m_basket;
};

class TMsgNewIndex : public TMessageSymbol
{
public:
	TMsgNewIndex(const char* const& symbol):
		TMessageSymbol(symbol, TM_INDEX_NEW, sizeof(TMsgNewIndex)){}
	TMsgNewIndex(const unsigned __int64& symbol):
		TMessageSymbol(symbol, TM_INDEX_NEW, sizeof(TMsgNewIndex))
	{
	}
};

class TMsgIndexRefreshed : public TMessageStockUpdate
{
public:
	TMsgIndexRefreshed(const char* const& symbol, const unsigned int& updateOrdinal, const bool& newIndex, const bool& subscribeToChart):
		TMessageStockUpdate(symbol, updateOrdinal, TM_INDEX_REFRESHED, sizeof(TMsgIndexRefreshed)),
		m_newIndex(newIndex),
		m_subscribeToChart(subscribeToChart)
	{
	}
	TMsgIndexRefreshed(const unsigned __int64& symbol, const unsigned int& updateOrdinal, const bool& newIndex, const bool& subscribeToChart):TMessageStockUpdate(symbol, updateOrdinal, TM_INDEX_REFRESHED, sizeof(TMsgIndexRefreshed)), m_newIndex(newIndex), m_subscribeToChart(subscribeToChart){}
	bool m_newIndex;
	bool m_subscribeToChart;
};

class TMsgIndexUpdate : public TMessageSymbolMapUpdate
{
public:
	TMsgIndexUpdate(const unsigned short& code, const unsigned int& updateOrdinal):
		TMessageSymbolMapUpdate(code, updateOrdinal, TM_INDEX_UPDATE, sizeof(TMsgIndexUpdate))
	{
	}
};

class TMsgIndexNewServerMinute : public TMessageSymbolMap
{
public:
	TMsgIndexNewServerMinute(const unsigned short& code, const unsigned short& minute):
		TMessageSymbolMap(code, TM_INDEX_NEW_SERVER_MINUTE, sizeof(TMsgIndexNewServerMinute)),
		m_minute(minute)
	{
	}
	unsigned short m_minute;
};

class TMsgIndex : public Message
{
public:
	const Index* m_index;
protected:
	TMsgIndex(const Index* const& index, const unsigned short& type, const unsigned short& length):
		Message(type, length),
		m_index(index)
	{
	}
};

class TMsgIndexObjectUpdated : public TMsgIndex
{
public:
	TMsgIndexObjectUpdated(const Index* const& index):
		TMsgIndex(index, TM_UPDATED_INDEX, sizeof(TMsgIndexObjectUpdated))
	{
	}
};

class TMsgIndexObjectNew : public TMsgIndex
{
public:
	TMsgIndexObjectNew(const Index* const& index, const bool& loaded):
		TMsgIndex(index, TM_NEW_INDEX, sizeof(TMsgIndexObjectNew)),
		m_loaded(loaded)
	{
	}
	bool m_loaded;
};

class TMsgIndexObjectDelete : public TMsgIndex
{
public:
	TMsgIndexObjectDelete(const Index* const& index):
		TMsgIndex(index, TM_INDEX_DELETE, sizeof(TMsgIndexObjectDelete))
	{
	}
};

class TMsgIndexObjectRefreshed : public TMsgIndex
{
public:
	TMsgIndexObjectRefreshed(const Index* const& index):
		TMsgIndex(index, TM_REFRESHED_INDEX, sizeof(TMsgIndexObjectRefreshed))
	{
	}
};

class TMsgIndexChartLoaded : public TMessageSymbol
{
public:
//	TMsgIndexChartLoaded(const char* const& symbol):TMessageSymbol(symbol, TM_INDEX_CHART_LOADED, sizeof(TMsgIndexChartLoaded)){}
	TMsgIndexChartLoaded(const unsigned __int64& symbol):
		TMessageSymbol(symbol, TM_INDEX_CHART_LOADED, sizeof(TMsgIndexChartLoaded))
	{
	}
};


class TMsgNewEquity : public TMessageSymbol
{
public:
	TMsgNewEquity(const char* const& symbol):
		TMessageSymbol(symbol, TM_EQUITY_NEW, sizeof(TMsgNewEquity))
	{
	}
	TMsgNewEquity(const unsigned __int64& symbol):
		TMessageSymbol(symbol, TM_EQUITY_NEW, sizeof(TMsgNewEquity))
	{
	}
};

class TMsgNewStock : public TMessageSymbol
{
public:
	TMsgNewStock(const char* const& symbol):
		TMessageSymbol(symbol, TM_STOCK_NEW, sizeof(TMsgNewStock))
	{
	}
	TMsgNewStock(const unsigned __int64& symbol):
		TMessageSymbol(symbol, TM_STOCK_NEW, sizeof(TMsgNewStock))
	{
	}
};

class TMsgEquityRefreshed : public TMessageStockUpdate
{
public:
	TMsgEquityRefreshed(const char* const& symbol, const unsigned int& updateOrdinal, const bool& newEquity, const bool& subscribeToChart, const bool& symbolMapping):
		TMessageStockUpdate(symbol, updateOrdinal, TM_EQUITY_REFRESHED, sizeof(TMsgEquityRefreshed)),
		m_newEquity(newEquity),
		m_subscribeToChart(subscribeToChart),
		m_symbolMapping(symbolMapping)
	{
	}
	TMsgEquityRefreshed(const unsigned __int64& symbol, const unsigned int& updateOrdinal, const bool& newEquity, const bool& subscribeToChart, const bool& symbolMapping):
		TMessageStockUpdate(symbol, updateOrdinal, TM_EQUITY_REFRESHED, sizeof(TMsgEquityRefreshed)),
		m_newEquity(newEquity),
		m_subscribeToChart(subscribeToChart),
		m_symbolMapping(symbolMapping)
	{
	}
	bool m_newEquity;
	bool m_subscribeToChart;
	bool m_symbolMapping;
};

class TMsgEquitySymbolMappingChanged : public TMessageSymbol
{
public:
	TMsgEquitySymbolMappingChanged(const char* const& symbol, const unsigned short& newSymbolMapping, const unsigned short& prevSymbolMapping):
		TMessageSymbol(symbol, TM_SORTABLE_SECURITY_SYMBOL_MAPPING_CHANGED, sizeof(TMsgEquitySymbolMappingChanged)),
		m_newSymbolMapping(newSymbolMapping),
		m_prevSymbolMapping(prevSymbolMapping)
	{
	}
	TMsgEquitySymbolMappingChanged(const unsigned __int64& symbol, const unsigned short& newSymbolMapping, const unsigned short& prevSymbolMapping):
		TMessageSymbol(symbol, TM_SORTABLE_SECURITY_SYMBOL_MAPPING_CHANGED, sizeof(TMsgEquitySymbolMappingChanged)),
		m_newSymbolMapping(newSymbolMapping),
		m_prevSymbolMapping(prevSymbolMapping)
	{
	}
	unsigned short m_newSymbolMapping;
	unsigned short m_prevSymbolMapping;
};

/*
class TMsgEquityUpdate : public TMessageStockUpdate
{
public:
	TMsgEquityUpdate(const char* symbol, unsigned int updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_EQUITY_UPDATE, sizeof(TMsgEquityUpdate)){}
	TMsgEquityUpdate(const unsigned __int64& symbol, unsigned int updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_EQUITY_UPDATE, sizeof(TMsgEquityUpdate)){}
};
*/
class TMsgEquityUpdate : public TMessageSymbolMapUpdate
{
public:
	TMsgEquityUpdate(const unsigned short& code, const bool& hasPrints, const unsigned int& updateOrdinal):
		TMessageSymbolMapUpdate(code, updateOrdinal, TM_EQUITY_UPDATE, sizeof(TMsgEquityUpdate)),
		m_hasPrints(hasPrints)
	{
	}
	bool m_hasPrints;
};

class TMsgEquityUsedCountUpdate : public TMessageSymbol
{
public:
	TMsgEquityUsedCountUpdate(const char* const& symbol):
		TMessageSymbol(symbol, TM_EQUITY_USED_COUNT_UPDATE, sizeof(TMsgEquityUsedCountUpdate))
	{
	}
	TMsgEquityUsedCountUpdate(const unsigned __int64& symbol):
		TMessageSymbol(symbol, TM_EQUITY_USED_COUNT_UPDATE, sizeof(TMsgEquityUsedCountUpdate))
	{
	}
};

//used instead of TMsgEquityUpdate to smooth processing of imbalance spikes in IdleProcessing
class TMsgEquityImbalanceUpdate : public TMessageSymbolMap
{
public:
	TMsgEquityImbalanceUpdate(const unsigned short& code):
		TMessageSymbolMap(code, TM_EQUITY_IMBALANCE_UPDATE, sizeof(TMsgEquityImbalanceUpdate))
	{
	}
};

class TMsgEquityChartCandleUpdated : public TMessageSymbolMap
{
public:
	TMsgEquityChartCandleUpdated(const unsigned short& code, const unsigned short& minute):
		TMessageSymbolMap(code, TM_CHART_CANDLE_UPDATED, sizeof(TMsgEquityChartCandleUpdated)),
		m_minute(minute)
	{
	}
	unsigned short m_minute;
};

class TMsgEquityNewDay : public TMessageSymbolMap
{
public:
	TMsgEquityNewDay(const unsigned short& code):
		TMessageSymbolMap(code, TM_EQUITY_NEW_DAY, sizeof(TMsgEquityNewDay))
	{
	}
};

class TMsgEquityReset : public TMessageSymbolMap
{
public:
	TMsgEquityReset(const unsigned short& code):
		TMessageSymbolMap(code, TM_EQUITY_RESET, sizeof(TMsgEquityReset))
	{
	}
};

class TMsgIndexNewDay : public TMessageSymbolMap
{
public:
	TMsgIndexNewDay(const unsigned short& code):
		TMessageSymbolMap(code, TM_INDEX_NEW_DAY, sizeof(TMsgIndexNewDay))
	{
	}
};

class TMsgIndexReset : public TMessageSymbolMap
{
public:
	TMsgIndexReset(const unsigned short& code):
		TMessageSymbolMap(code, TM_INDEX_RESET, sizeof(TMsgIndexReset))
	{
	}
};

class TMsgStockNewDay : public TMessageSymbol
{
public:
	TMsgStockNewDay(const char* const& symbol):
		TMessageSymbol(symbol, TM_STOCK_NEW_DAY, sizeof(TMsgStockNewDay))
	{
	}
	TMsgStockNewDay(const unsigned __int64& symbol = 0):
		TMessageSymbol(symbol, TM_STOCK_NEW_DAY, sizeof(TMsgStockNewDay))
	{
	}
};

#ifndef TAKION_NO_OPTIONS
class TMsgNextFutureSessionStarted : public TMsgDayStarted
{
public:
	TMsgNextFutureSessionStarted(const unsigned int& date = 0):
		TMsgDayStarted(date, TM_NEXT_FUTURE_SESSION_STARTED, sizeof(TMsgNextFutureSessionStarted))
	{
	}
};

class TMsgFutureNewSession : public TMessageSymbol
{
public:
	TMsgFutureNewSession(const char* const& symbol):
		TMessageSymbol(symbol, TM_FUTURE_NEW_SESSION, sizeof(TMsgFutureNewSession))
	{
	}
	TMsgFutureNewSession(const unsigned __int64& symbol = 0):
		TMessageSymbol(symbol, TM_FUTURE_NEW_SESSION, sizeof(TMsgFutureNewSession))
	{
	}
};

class TMsgOptionNewDay : public TMessageSymbol
{
public:
	TMsgOptionNewDay(const char* const& symbol, const unsigned __int64& optionBlock):
		TMessageSymbol(symbol, TM_OPTION_NEW_DAY, sizeof(TMsgOptionNewDay)), m_optionBlock(optionBlock)
	{
	}
	TMsgOptionNewDay(const unsigned __int64& symbol = 0, const unsigned __int64& optionBlock = 0):
		TMessageSymbol(symbol, TM_OPTION_NEW_DAY, sizeof(TMsgOptionNewDay)), m_optionBlock(optionBlock)
	{
	}
	unsigned __int64 m_optionBlock;
};
#endif

class TMsgSecurity : public Message//Usually for Message* additionalInfo
{
public:
	const Security* m_security;
protected:
	TMsgSecurity(const Security* const& security, const unsigned short& type, const unsigned short& length):
		Message(type, length), m_security(security)
	{
	}
};
/*
class TMsgEquity : public Message
{
public:
	const Security* m_security;
protected:
	TMsgEquity(const Security* const& security, const unsigned short& type, const unsigned short& length):Message(type, length), m_security(security){}
};
*/
/*
class TMsgRsi : public TMsgEquity
{
public:
	const RsiData* m_rsiData;
protected:
	TMsgRsi(const Security* const& security, const RsiData* const& rsiData, const unsigned short& type, const unsigned short& length):TMsgEquity(security, type, length), m_rsiData(rsiData){}
};

class TMsgRsiObjectNew : public TMsgRsi
{
public:
	TMsgRsiObjectNew(const Security* const& security, const RsiData* const& rsiData):TMsgRsi(security, rsiData, TM_RSI_MH_CHART_LOADED, sizeof(TMsgRsiObjectNew)){}
};

class TMsgRsiObjectFailed : public TMsgRsi
{
public:
	TMsgRsiObjectFailed(const Security* const& security, const RsiData* const& rsiData):TMsgRsi(security, rsiData, TM_RSI_MH_CHART_FAILED, sizeof(TMsgRsiObjectFailed)){}
};

class TMsgRsiObjectRequested : public TMsgRsi
{
public:
	TMsgRsiObjectRequested(const Security* const& security, const RsiData* const& rsiData):TMsgRsi(security, rsiData, TM_RSI_MH_CHART_REQUESTED, sizeof(TMsgRsiObjectRequested)){}
};
*/

class TMsgMhRsiSecurityDataLoaded : public TMsgSecurity//security observers are notified
{
public:
	TMsgMhRsiSecurityDataLoaded(const Security* const& security, const Price* priceArray, const unsigned short arraySize):
		TMsgSecurity(security, TM_RSI_MH_SECURITY_DATA_LOADED, sizeof(TMsgMhRsiSecurityDataLoaded)),
		m_priceArray(priceArray),
		m_arraySize(arraySize)
	{
	}
	const Price* m_priceArray;
	unsigned short m_arraySize;
};

class TMsgMhRsiObjectNew : public TMsgSecurity//observers of m_newRsiObservable are notified
{
public:
	TMsgMhRsiObjectNew(const Security* const& security):TMsgSecurity(security, TM_RSI_MH_CHART_LOADED, sizeof(TMsgMhRsiObjectNew)){}
};

class TMsgMhRsiObjectFailed : public TMsgSecurity
{
public:
	TMsgMhRsiObjectFailed(const Security* const& security):
		TMsgSecurity(security, TM_RSI_MH_CHART_FAILED, sizeof(TMsgMhRsiObjectFailed))
	{
	}
};

class TMsgMhRsiObjectRequested : public Message
{
public:
	TMsgMhRsiObjectRequested():
		Message(TM_RSI_MH_CHART_REQUESTED, sizeof(TMsgMhRsiObjectRequested))
	{
	}
};

class TMsgMhRsiObjectsCleared : public Message
{
public:
	TMsgMhRsiObjectsCleared():
		Message(TM_RSI_MH_CHARTS_CLEARED, sizeof(TMsgMhRsiObjectsCleared))
	{
	}
};

class TMsgMhRsiAllObjectsLoaded : public Message
{
public:
	TMsgMhRsiAllObjectsLoaded():
		Message(TM_RSI_MH_ALL_CHARTS_LOADED, sizeof(TMsgMhRsiAllObjectsLoaded))
	{
	}
};
//RSI Days
class TMsgDaysRsiSecurityDataLoaded : public TMsgSecurity//security observers are notified
{
public:
	TMsgDaysRsiSecurityDataLoaded(const Security* const& security, const Price* priceArray, const unsigned short arraySize):
		TMsgSecurity(security, TM_RSI_DAYS_SECURITY_DATA_LOADED, sizeof(TMsgDaysRsiSecurityDataLoaded)),
		m_priceArray(priceArray),
		m_arraySize(arraySize)
	{
	}
	const Price* m_priceArray;
	unsigned short m_arraySize;
};

class TMsgDaysRsiObjectNew : public TMsgSecurity//observers of m_newRsiObservable are notified
{
public:
	TMsgDaysRsiObjectNew(const Security* const& security):
		TMsgSecurity(security, TM_RSI_DAYS_CHART_LOADED, sizeof(TMsgDaysRsiObjectNew))
	{
	}
};

class TMsgDaysRsiObjectFailed : public TMsgSecurity
{
public:
	TMsgDaysRsiObjectFailed(const Security* const& security):
		TMsgSecurity(security, TM_RSI_DAYS_CHART_FAILED, sizeof(TMsgDaysRsiObjectFailed))
	{
	}
};

class TMsgDaysRsiObjectRequested : public Message
{
public:
	TMsgDaysRsiObjectRequested():
		Message(TM_RSI_DAYS_CHART_REQUESTED, sizeof(TMsgDaysRsiObjectRequested))
	{
	}
};

class TMsgDaysRsiObjectsCleared : public Message
{
public:
	TMsgDaysRsiObjectsCleared():
		Message(TM_RSI_DAYS_CHARTS_CLEARED, sizeof(TMsgDaysRsiObjectsCleared))
	{
	}
};

class TMsgDaysRsiAllObjectsLoaded : public Message
{
public:
	TMsgDaysRsiAllObjectsLoaded():
		Message(TM_RSI_DAYS_ALL_CHARTS_LOADED, sizeof(TMsgDaysRsiAllObjectsLoaded))
	{
	}
};
//
class TMsgEquityObjectNew : public TMsgSecurity
{
public:
	TMsgEquityObjectNew(const Security* const& security, const bool& loaded):
		TMsgSecurity(security, TM_NEW_EQUITY, sizeof(TMsgEquityObjectNew)),
		m_loaded(loaded)
	{
	}
	bool m_loaded;
};

class TMsgStockObjectNew : public TMsgSecurity
{
public:
	TMsgStockObjectNew(const Security* const& security):
		TMsgSecurity(security, TM_NEW_STOCK, sizeof(TMsgStockObjectNew))
	{
	}
};

class TMsgEquityObjectRefreshed : public TMsgSecurity
{
public:
	TMsgEquityObjectRefreshed(const Security* const& security):
		TMsgSecurity(security, TM_REFRESHED_EQUITY, sizeof(TMsgEquityObjectRefreshed))
	{
	}
};

class TMsgEquityObjectUpdated : public TMsgSecurity
{
public:
	TMsgEquityObjectUpdated(const Security* const& security):
		TMsgSecurity(security, TM_UPDATED_EQUITY, sizeof(TMsgEquityObjectUpdated))
	{
	}
};

class TMsgSecurityTradingState : public TMsgSecurity
{
public:
	TMsgSecurityTradingState(const Security* const& security, const char& prevTradingState, const char& tradingState):
		TMsgSecurity(security, TM_SECURITY_TRADING_STATE, sizeof(TMsgSecurityTradingState)),
		m_prevTradingState(prevTradingState),
		m_tradingState(tradingState)
	{
	}
	char m_prevTradingState;
	char m_tradingState;
};

class TMsgStockInvalid : public TMessageSymbol
{
public:
	TMsgStockInvalid(const char* const& symbol):
		TMessageSymbol(symbol, TM_STOCK_INVALID, sizeof(TMsgStockInvalid))
	{
	}
	TMsgStockInvalid(const unsigned __int64& symbol = 0):
		TMessageSymbol(symbol, TM_STOCK_INVALID, sizeof(TMsgStockInvalid))
	{
	}
};

class TMsgSortableSecurityInvalid : public TMessageSymbol
{
public:
	TMsgSortableSecurityInvalid(const char* const& symbol):
		TMessageSymbol(symbol, TM_SORTABLE_SECURITY_INVALID, sizeof(TMsgSortableSecurityInvalid))
	{
	}
	TMsgSortableSecurityInvalid(const unsigned __int64& symbol = 0):
		TMessageSymbol(symbol, TM_SORTABLE_SECURITY_INVALID, sizeof(TMsgSortableSecurityInvalid))
	{
	}
};


class TMsgAccountObject : public Message
{
public:
	char m_accountId[MAX_ACCOUNT_SIZE];
protected:
	TMsgAccountObject(const char* const& accountName, const unsigned short& type, const unsigned short& length):
		Message(type, length)
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountName, '\0', true);
	}
};

class TMsgAccountObjectAndUInt : public TMsgAccountObject
{
public:
	unsigned int m_clientId;
protected:
	TMsgAccountObjectAndUInt(const char* const& accountName, const unsigned int& id, const unsigned short& type, const unsigned short& length):
		TMsgAccountObject(accountName, type, length), m_clientId(id)
	{
	}
};



class TMsgAccountLoss90Percent : public TMsgAccountObject
{
public:
	TMsgAccountLoss90Percent(const char* const& accountName):
		TMsgAccountObject(accountName, TM_ACCOUNT_LOSS_90_PERCENT, sizeof(TMsgAccountLoss90Percent))
	{
	}
};

//////////////

class TMsgAccountStockPositionObject : public TMsgAccountObject
{
public:
	unsigned __int64 m_symbol;
protected:
	TMsgAccountStockPositionObject(const char* const& accountName, const unsigned __int64& symbol,
		const unsigned short& type, const unsigned short& length):
		TMsgAccountObject(accountName, type, length),
		m_symbol(symbol)
	{
//		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}
};

class TMsgAccountPositionObject : public TMsgAccountStockPositionObject
{
public:
#ifndef TAKION_NO_OPTIONS
	unsigned __int64 m_optionBlock;
	unsigned char m_securityType;
#endif
protected:
	TMsgAccountPositionObject(const char* const& accountName, const unsigned __int64& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
		const unsigned char& securityType,
#endif
		const unsigned short& type, const unsigned short& length):
		TMsgAccountStockPositionObject(accountName, symbol, type, length)
#ifndef TAKION_NO_OPTIONS
		,m_optionBlock(optionBlock)
		,m_securityType(securityType)
#endif
	{
	}
};

class TMsgSendOrderDone : public TMsgAccountPositionObject
{
public:
	TMsgSendOrderDone(const char* const& accountName = "",
		const unsigned __int64& symbol = 0,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock = 0,
		const unsigned char& securityType = 0,
#endif
		const unsigned int& sendId = 0,
		const unsigned int& clientId = 0,
		const unsigned __int64& userId = 0,
		const void* const& userData = nullptr):
		TMsgAccountPositionObject(accountName, symbol,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
			securityType,
#endif
			TM_SEND_ORDER_DONE, sizeof(TMsgSendOrderDone)),
		m_sendId(sendId),
		m_clientId(clientId),
		m_userId(userId),
		m_userData(userData)
	{
	}
/*
	TMsgSendOrderDone(const char* const& accountName, const unsigned int& sendId, const unsigned int& clientId, const unsigned __int64& userId):
		TMsgAccountPositionObject(accountName, 0,
#ifndef TAKION_NO_OPTIONS
			0,
			ST_STOCK,
#endif
			TM_SEND_ORDER_DONE, sizeof(TMsgSendOrderDone)),
		m_sendId(sendId),
		m_clientId(clientId),
		m_userId(userId)
	{
	}
*/
	unsigned int m_sendId;
	unsigned int m_clientId;
	unsigned __int64 m_userId;
	const void* m_userData;
};

class TMsgPositionOpenPnlUpdate : public TMsgAccountPositionObject
{
public:
	Price m_price;
protected:
	TMsgPositionOpenPnlUpdate(const char* const& accountName, const unsigned __int64& symbol,//const char* symbol,
		const Price& level1Price,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
		const unsigned char& securityType,
#endif
		const unsigned short& type, const unsigned short& length):
		TMsgAccountPositionObject(accountName, symbol,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
			securityType,
#endif
			type, length),
		m_price(level1Price)
	{
//		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}
};

class TMsgPositionTCloseOpenPnlUpdate : public TMsgPositionOpenPnlUpdate
{
public:
	TMsgPositionTCloseOpenPnlUpdate(const char* const& accountName, const unsigned __int64& symbol,//const char* symbol,
		const Price& price
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& optionBlock
		,const unsigned char& securityType
#endif
		):
		TMsgPositionOpenPnlUpdate(accountName, symbol, price,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
			securityType,
#endif
			TM_POSITION_OPEN_PNL_TCLOSE, sizeof(TMsgPositionTCloseOpenPnlUpdate))
	{
	}
};

class TMsgPositionPrintOpenPnlUpdate : public TMsgPositionOpenPnlUpdate
{
public:
	TMsgPositionPrintOpenPnlUpdate(const char* const& accountName,
		const unsigned __int64& symbol,//const char* symbol,
		const Price& price,
		const bool& nbboPrint,
		const bool& actionPrint,
		const bool& fromSnapshot,
		const unsigned char& stockState
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& optionBlock
		,const unsigned char& securityType
#endif
		):
		TMsgPositionOpenPnlUpdate(accountName, symbol, price,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
			securityType,
#endif
			TM_POSITION_OPEN_PNL_PRINT, sizeof(TMsgPositionPrintOpenPnlUpdate)),
		m_nbboPrint(nbboPrint),
		m_actionPrint(actionPrint),
		m_fromSnapshot(fromSnapshot),
		m_stockState(stockState)
	{
	}
	bool m_nbboPrint;
	bool m_actionPrint;
	bool m_fromSnapshot;
	unsigned char m_stockState;//MSTATE_PREMARKET, MSTATE_MARKET, MSTATE_POSTMARKET
};

class TMsgPositionPrintTrailingOrdersUpdate : public TMsgPositionOpenPnlUpdate
{
public:
	TMsgPositionPrintTrailingOrdersUpdate(const char* const& accountName, const unsigned __int64& symbol,//const char* symbol,
		const Price& price//, bool nbboPrint
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& optionBlock
		,const unsigned char& securityType
#endif
		):
		TMsgPositionOpenPnlUpdate(accountName, symbol, price,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
			securityType,
#endif
			TM_POSITION_TRAILING_ORDERS_PRINT, sizeof(TMsgPositionPrintTrailingOrdersUpdate))
//		m_nbboPrint(nbboPrint)
	{
	}
//	bool m_nbboPrint;
};

class TMsgPositionLevel1TrailingOrdersUpdate : public TMsgPositionOpenPnlUpdate
{
public:
	TMsgPositionLevel1TrailingOrdersUpdate(const char* const& accountName, const unsigned __int64& symbol,//const char* symbol,
		const Price& bid,
		const Price& ask,
		unsigned char bidask//1 bid, 2 ask, 3 both
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& optionBlock
		,const unsigned char& securityType
#endif
		):
		TMsgPositionOpenPnlUpdate(accountName, symbol, bid,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
			securityType,
#endif
			TM_POSITION_TRAILING_ORDERS_LEVEL1, sizeof(TMsgPositionLevel1TrailingOrdersUpdate)),
		m_ask(ask),
		m_bidask(bidask)
	{
	}
	Price m_ask;
	unsigned char m_bidask;
};

class TMsgPositionClosingPriceUpdate : public TMsgPositionOpenPnlUpdate
{
public:
	TMsgPositionClosingPriceUpdate(const char* const& accountName, const unsigned __int64& symbol,//const char* symbol,
		const Price& price,
		const unsigned int& todaysClosingPriceCompact
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& optionBlock
		,const unsigned char& securityType
#endif
		):
		TMsgPositionOpenPnlUpdate(accountName, symbol, price,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
			securityType,
#endif
			TM_POSITION_CLOSING_PRICE, sizeof(TMsgPositionClosingPriceUpdate)),
		m_todaysClosingPriceCompact(todaysClosingPriceCompact)
	{
	}
	unsigned int m_todaysClosingPriceCompact;
};

class TMsgPositionTodaysClosingPriceUpdate : public TMsgPositionOpenPnlUpdate
{
public:
	TMsgPositionTodaysClosingPriceUpdate(const char* const& accountName, const unsigned __int64& symbol,//const char* symbol,
		const Price& price
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& optionBlock
		,const unsigned char& securityType
#endif
		):
		TMsgPositionOpenPnlUpdate(accountName, symbol, price,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
			securityType,
#endif
			TM_POSITION_TODAYS_CLOSING_PRICE, sizeof(TMsgPositionTodaysClosingPriceUpdate))
	{
	}
};

class TMsgPositionLevel1OpenPnlUpdate : public TMsgPositionOpenPnlUpdate
{
public:
	TMsgPositionLevel1OpenPnlUpdate(const char* const& accountName, const unsigned __int64& symbol,//const char* symbol,
		const Price& price,
		const bool& bid,
		const bool& fromSnapshot
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& optionBlock
		,const unsigned char& securityType
#endif
		):
		TMsgPositionOpenPnlUpdate(accountName, symbol, price,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
			securityType,
#endif
			TM_POSITION_OPEN_PNL_LEVEL1, sizeof(TMsgPositionLevel1OpenPnlUpdate)),
//		m_priceAsk(priceAsk)
		m_bid(bid),
		m_fromSnapshot(fromSnapshot)
	{
	}
//	Price m_priceAsk;
	bool m_bid;
	bool m_fromSnapshot;
};

class TMsgPositionImbExNearOpenPnlUpdate : public TMsgPositionOpenPnlUpdate
{
public:
	TMsgPositionImbExNearOpenPnlUpdate(const char* const& accountName, const unsigned __int64& symbol,
		const Price& price
/*
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& optionBlock
#endif
*/
		):
		TMsgPositionOpenPnlUpdate(accountName, symbol, price,
#ifndef TAKION_NO_OPTIONS
			0,//optionBlock,
			0,//securityType
#endif
			TM_POSITION_OPEN_PNL_IMBEXNEAR, sizeof(TMsgPositionImbExNearOpenPnlUpdate))
	{
	}
};

class TMsgAutoAction : public TMsgAccountPositionObject
{
public:
	TMsgAutoAction(const char* const& accountName, const unsigned __int64& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
		const unsigned char& securityType,
#endif
		const Money& loss, const Money& constraint, const bool& close):
		TMsgAccountPositionObject(accountName, symbol,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
			securityType,
#endif
			TM_AUTO_ACTION, sizeof(TMsgAutoAction)),
		m_loss(loss),
		m_constraint(constraint),
		m_close(close)
	{
//		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}

//	Symbol m_symbol;
	Money m_loss;
	Money m_constraint;
	bool m_close;
};

class TMsgExecutionNew : public TMsgAccountObject
{
public:
	TMsgExecutionNew(const unsigned int& remainingQuantity,
		const unsigned int& cumulativeFilledQuantity,
		const unsigned int& executionId,
		const unsigned char& side,
		const char* const& accountName):
		TMsgAccountObject(accountName, TM_EXECUTION_NEW, sizeof(TMsgExecutionNew)),
		m_remainingQuantity(remainingQuantity),
		m_cumulativeFilledQuantity(cumulativeFilledQuantity),
		m_executionId(executionId),
		m_side(side)
	{
	}
	unsigned int m_remainingQuantity;
	unsigned int m_cumulativeFilledQuantity;
	unsigned int m_executionId;
	unsigned char m_side;
};

enum NewOrderType : unsigned char
{
	NOT_SENT,
	NOT_ACKNOWLEDGED,
	NOT_UPDATED,
	NOT_REPLACING,
	NOT_HISTORICAL,

	NOT_Count
};

class TMsgOrderNew : public TMsgAccountObjectAndUInt
{
public:
	TMsgOrderNew(const unsigned int& clientId,
		const unsigned int& serverId,
		const unsigned int& msgClientId,
		const unsigned int& msgServerId,
		const unsigned int& msgParentClientId,
		const unsigned int& pendingShares,
		const char* const& accountName,
		const unsigned char& newOrderType):
		TMsgAccountObjectAndUInt(accountName, clientId, TM_ORDER_NEW, sizeof(TMsgOrderNew)),
//		m_clientId(clientId),
		m_serverId(serverId),
		m_msgClientId(msgClientId),
		m_msgServerId(msgServerId),
		m_parentClientId(msgParentClientId),
		m_pendingShares(pendingShares),
		m_newOrderType(newOrderType)
	{
	}
//	unsigned int m_clientId;
	unsigned int m_serverId;
	unsigned int m_msgClientId;
	unsigned int m_msgServerId;
	unsigned int m_parentClientId;
	unsigned int m_pendingShares;
	unsigned char m_newOrderType;
};

class TMsgStuckOrder : public TMsgAccountObjectAndUInt
{
public:
	TMsgStuckOrder(const char* const& accountName = "", const unsigned int& clientId = 0, const bool& stuck = false):
		TMsgAccountObjectAndUInt(accountName, clientId, TM_ORDER_STUCK, sizeof(TMsgStuckOrder)), m_stuck(stuck)
	{
	}
//	unsigned int m_clientId;
	bool m_stuck;
};

class TMsgOrderAlgorithmCancel : public Message
{
public:
	TMsgOrderAlgorithmCancel(const char* const& accountName, const unsigned int& orderClientId):
		Message(TM_ORDER_ALGORITHM_CANCEL, sizeof(TMsgOrderAlgorithmCancel)),
		m_orderClientId(orderClientId)
	{
		U_CopyAndPad(m_accountName, sizeof(m_accountName), accountName, '\0', true);
	}
	char m_accountName[MAX_ACCOUNT_SIZE];
	unsigned int m_orderClientId;
};

class TMsgPositionNew : public TMsgAccountObject
{
public:
	TMsgPositionNew(const unsigned __int64& symbol
#ifndef TAKION_NO_OPTIONS
		, const unsigned __int64& optionBlock
#endif
		, const char* const& accountName):
		TMsgAccountObject(accountName, TM_POSITION_NEW, sizeof(TMsgPositionNew)), m_symbol(symbol)
#ifndef TAKION_NO_OPTIONS
		, m_optionBlock(optionBlock)
#endif
	{
	}
	unsigned __int64 m_symbol;
#ifndef TAKION_NO_OPTIONS
	unsigned __int64 m_optionBlock;
#endif
};

class TMsgStockUpdateHasPrints : public TMessageStockUpdate
{
public:
	bool m_hasPrints;
protected:
	TMsgStockUpdateHasPrints(const char* const& symbol,
		const bool& hasPrints,
		const unsigned int& updateOrdinal,
		const unsigned short& type,
		const unsigned short& length):
		TMessageStockUpdate(symbol, updateOrdinal, type, length),
		m_hasPrints(hasPrints)
	{
	}
	TMsgStockUpdateHasPrints(const unsigned __int64& symbol,
		const bool& hasPrints,
		const unsigned int& updateOrdinal,
		const unsigned short& type,
		const unsigned short& length):
		TMessageStockUpdate(symbol, updateOrdinal, type, length),
		m_hasPrints(hasPrints)
	{
	}
};

class TMsgStockUpdateLevel1 : public TMsgStockUpdateHasPrints
{
public:
	TMsgStockUpdateLevel1(const char* const& symbol, const bool& hasPrints, const unsigned int& updateOrdinal):
		TMsgStockUpdateHasPrints(symbol, hasPrints, updateOrdinal, TM_STOCK_UPDATE_LEVEL1, sizeof(TMsgStockUpdateLevel1))
	{
	}
	TMsgStockUpdateLevel1(const unsigned __int64& symbol, const bool& hasPrints, const unsigned int& updateOrdinal):
		TMsgStockUpdateHasPrints(symbol, hasPrints, updateOrdinal, TM_STOCK_UPDATE_LEVEL1, sizeof(TMsgStockUpdateLevel1))
	{
	}
};

class TMsgStockUsedCountUpdate : public TMessageSymbol
{
public:
	TMsgStockUsedCountUpdate(const char* const& symbol):TMessageSymbol(symbol, TM_STOCK_USED_COUNT_UPDATE, sizeof(TMsgStockUsedCountUpdate)){}
	TMsgStockUsedCountUpdate(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_STOCK_USED_COUNT_UPDATE, sizeof(TMsgStockUsedCountUpdate)){}
};

class TMsgStockLightSnapshot : public TMessageSymbol//For Light server
{
public:
	TMsgStockLightSnapshot(const char* const& symbol):TMessageSymbol(symbol, TM_STOCK_LIGHT_SNAPSHOT, sizeof(TMsgStockLightSnapshot)){}
	TMsgStockLightSnapshot(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_STOCK_LIGHT_SNAPSHOT, sizeof(TMsgStockLightSnapshot)){}
};

class TMsgStockNewsHistoricSearchDone : public TMessageSymbol
{
public:
	TMsgStockNewsHistoricSearchDone(const char* const& symbol, const unsigned int& newsCollectionId):TMessageSymbol(symbol, TM_STOCK_NEWS_HISTORIC_SEARCH_DONE, sizeof(TMsgStockNewsHistoricSearchDone)), m_newsCollectionId(newsCollectionId){}
	TMsgStockNewsHistoricSearchDone(const unsigned __int64& symbol, const unsigned int& newsCollectionId):TMessageSymbol(symbol, TM_STOCK_NEWS_HISTORIC_SEARCH_DONE, sizeof(TMsgStockNewsHistoricSearchDone)), m_newsCollectionId(newsCollectionId){}
	unsigned int m_newsCollectionId;
};

class TMsgStringNewsHistoricSearchDone : public Message
{
public:
	TMsgStringNewsHistoricSearchDone(const char* const& str, const unsigned short& strLength, const unsigned int& newsCollectionId):Message(TM_STRING_NEWS_HISTORIC_SEARCH_DONE, sizeof(TMsgStringNewsHistoricSearchDone) + strLength), m_newsCollectionId(newsCollectionId){}
	unsigned int m_newsCollectionId;
};

class TMsgStockUpdateHeadlines : public TMessageStockUpdate
{
public:
	TMsgStockUpdateHeadlines(const char* const& symbol, const unsigned int& newsCollectionId, const unsigned int& updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_STOCK_UPDATE_HEADLINES, sizeof(TMsgStockUpdateHeadlines)), m_newsCollectionId(newsCollectionId){}
	TMsgStockUpdateHeadlines(const unsigned __int64& symbol, const unsigned int& newsCollectionId, const unsigned int& updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_STOCK_UPDATE_HEADLINES, sizeof(TMsgStockUpdateHeadlines)), m_newsCollectionId(newsCollectionId){}
	unsigned int m_newsCollectionId;
};

class TMsgStringUpdateHeadlines : public Message
{
public:
	TMsgStringUpdateHeadlines(const char* const& str, const unsigned short& strLength, const unsigned int& newsCollectionId, const unsigned int& updateOrdinal):Message(TM_STRING_UPDATE_HEADLINES, sizeof(TMsgStringUpdateHeadlines) + strLength), m_updateOrdinal(updateOrdinal), m_newsCollectionId(newsCollectionId){}
	unsigned int m_updateOrdinal;
	unsigned int m_newsCollectionId;
};

class TMsgHeadline : public Message
{
public:
	TMsgHeadline(const unsigned short& additionalLength, const bool& historical, const unsigned __int64& dateTime):
		Message(TM_HEADLINE, sizeof(TMsgHeadline) + additionalLength),
		m_historical(historical),
		m_dateTime(dateTime)
	{
	}
	bool m_historical;
	unsigned __int64 m_dateTime;
};

/*
class TMsgNewsStory : public Message
{
public:
	TMsgNewsStory(unsigned int updateOrdinal, unsigned short additionalLength):Message(TM_NEWS_STORY, sizeof(TMsgNewsStory) + additionalLength), m_updateOrdinal(updateOrdinal){}
	unsigned int m_updateOrdinal;
};
*/

class TMsgUpdateLastNewsStory : public Message
{
public:
	TMsgUpdateLastNewsStory(const unsigned int& updateOrdinal, const bool& displayHyperlink):
		Message(TM_UPDATE_LAST_NEWS_STORY, sizeof(TMsgUpdateLastNewsStory)),
		m_updateOrdinal(updateOrdinal),
		m_displayHyperlink(displayHyperlink)
	{
	}
	unsigned int m_updateOrdinal;
	bool m_displayHyperlink;
};

class TMsgNewsProfilesLoaded : public Message
{
public:
	TMsgNewsProfilesLoaded():Message(TM_NEWS_PROFILES_LOADED, sizeof(TMsgNewsProfilesLoaded)){}
};

class NewsResourceAsNumberArray : public StrAsNumberArray<size_t, 128 / sizeof(size_t)>
{
public:
	NewsResourceAsNumberArray():StrAsNumberArray(){}
	explicit NewsResourceAsNumberArray(const char* const& str):StrAsNumberArray(str){}
	NewsResourceAsNumberArray(const char*& str, const char& del):StrAsNumberArray(str, del){}
	NewsResourceAsNumberArray(const char*& str, const unsigned short& length, const char& del):StrAsNumberArray(str, length, del){}
	NewsResourceAsNumberArray(const unsigned short& exactLength, const char* const& str):StrAsNumberArray(exactLength, str){}
	explicit NewsResourceAsNumberArray(const std::string& str):StrAsNumberArray(str){}
//	operator size_t() const{return m_numberArray[16 / sizeof(size_t) - 1];}
	size_t GetHashValue() const{return m_numberArray[16 / sizeof(size_t) - 1];}
	DECLARE_NED_NEW
};

template<> inline size_t std::hash_value(const NewsResourceAsNumberArray& key)
{	// hash _Keyval to size_t value one-to-one
	return key.GetHashValue();// ^ _HASH_SEED;//(((key.GetDollars() << 16) | key.GetDollarFraction()) ^ _HASH_SEED);
}

class NewsStory
{
public:
	NewsStory(const std::string& story, const NewsResourceAsNumberArray& resourceId, const bool& showChain, const bool& storyError):
		m_story(story),
		m_resourceId(resourceId),
		m_showChain(showChain),
		m_storyError(storyError)
	{
	}
	const std::string& GetStory() const{return m_story;}
	const NewsResourceAsNumberArray& GetResourceId() const{return m_resourceId;}
	const char* GetResourceIdStr() const{return m_resourceId.GetString();}
	bool isShowChain() const{return m_showChain;}
	bool isStoryError() const{return m_storyError;}
	void SetStory(const std::string& story, const std::string& resourceId, const bool& showChain, const bool& storyError)
	{
		m_story = story;
		m_showChain = showChain;
		m_storyError = storyError;
	}
	DECLARE_NED_NEW
protected:
	std::string m_story;
	NewsResourceAsNumberArray m_resourceId;
	bool m_showChain;
	bool m_storyError;
};

class TMsgNewsStoryContents : public Message
{
public:
	TMsgNewsStoryContents(const NewsStory* const& newsStory, const bool& displayHyperlink):
		Message(TM_NEWS_STORY_CONTENTS, sizeof(TMsgNewsStoryContents)),
		m_newsStory(newsStory),
		m_displayHyperlink(displayHyperlink)
	{
	}
	const NewsStory* m_newsStory;
	bool m_displayHyperlink;
};

enum SubscriptionTypes : unsigned char
{
    UpdatesOnly	= 0,
    SubscribeSymbol	= 1,
	SnapshotSymbol	= 2,
	UpdatesOnlyAll    = 0xfe,
    RefreshAll        = 0xff,
};
/*
class TMsgReqKick : public Message
{
public:
	TMsgReqKick(const char* traderId):Message(M_REQ_KICK, sizeof(TMsgReqKick))
	{
		U_CopyAndPad(m_traderId, sizeof(m_traderId), traderId, '\0');
	}
	char m_traderId[MAX_TRADER_ID_SIZE];
};
*/
class TMsgReqRefreshSymbol : public TMessageSymbol
{
public:
	TMsgReqRefreshSymbol(const char* const& symbol, const unsigned char& flags = SubscribeSymbol, const unsigned char& blockSize = 1, const unsigned int& requestID = 0):
		TMessageSymbol(symbol, M_REQ_REFRESH_SYMBOL, sizeof(TMsgReqRefreshSymbol)),
		m_flags(flags),
		m_blockSize(blockSize),
		m_requestID(requestID)
	{
	}
    unsigned char m_flags;
    unsigned char m_blockSize;
    unsigned int m_requestID;
};

class TMsgReqUnsubscribeSymbol : public TMessageSymbol
{
public:
	TMsgReqUnsubscribeSymbol(const char* const& symbol):TMessageSymbol(symbol, M_REQ_UNSUBSCRIBE_SYMBOL, sizeof(TMsgReqUnsubscribeSymbol)){}
};

class TMsgEndOfDaySummaryReportBase : public TMessageTimeSymbol
{
public:
	unsigned int m_todaysClosePriceDollar;
	unsigned int m_todaysClosePriceFraction;
    unsigned __int64 m_volume;
protected:
    TMsgEndOfDaySummaryReportBase(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& todaysClosePriceDollar,
		const unsigned int& todaysClosePriceFraction,
		const unsigned __int64& volume,
		const unsigned short& type,
		const unsigned short& length):
		
		TMessageTimeSymbol(symbol, time, type, length),
		m_todaysClosePriceDollar(todaysClosePriceDollar),
		m_todaysClosePriceFraction(todaysClosePriceFraction),
		m_volume(volume)
	{
	}
};

class TMsgEndOfDaySummaryReport : public TMsgEndOfDaySummaryReportBase
{
public:
    TMsgEndOfDaySummaryReport(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& todaysClosePriceDollar,
		const unsigned int& todaysClosePriceFraction,
		const unsigned __int64& volume):
		
		TMsgEndOfDaySummaryReportBase(symbol, time, todaysClosePriceDollar, todaysClosePriceFraction, volume, M_EOD_SUMMARY_REPORT, sizeof(TMsgEndOfDaySummaryReport))
	{
	}
};

class TMsgMsEndOfDaySummaryReport : public TMsgEndOfDaySummaryReportBase
{
public:
    TMsgMsEndOfDaySummaryReport(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& todaysClosePriceDollar,
		const unsigned int& todaysClosePriceFraction,
		const unsigned __int64& volume):
		
		TMsgEndOfDaySummaryReportBase(symbol, time, todaysClosePriceDollar, todaysClosePriceFraction, volume, M_MS_EOD_SUMMARY_REPORT, sizeof(TMsgMsEndOfDaySummaryReport))
	{
	}
};

class TMsgShortSaleIndicatorsBase : public TMessageTimeSymbol
{
public:
	char m_shortSaleThresholdIndicator;//'Y', 'N'
	char m_regSHOTestIndicator;//'0', '1', '2'
protected:
    TMsgShortSaleIndicatorsBase(const char* const& symbol,
		const unsigned int& time,
		const char& shortSaleThresholdIndicator,
		const char& regSHOTestIndicator,
		const unsigned short& type,
		const unsigned short& length):

		TMessageTimeSymbol(symbol, time, type, length),
        m_shortSaleThresholdIndicator(shortSaleThresholdIndicator),
        m_regSHOTestIndicator(regSHOTestIndicator)
	{
	}

};

class TMsgShortSaleIndicators : public TMsgShortSaleIndicatorsBase
{
public:
    TMsgShortSaleIndicators(const char* const& symbol,
		const unsigned int& time,
		const char& shortSaleThresholdIndicator,
		const char& regSHOTestIndicator):

		TMsgShortSaleIndicatorsBase(symbol, time, shortSaleThresholdIndicator, regSHOTestIndicator, M_SHORT_SALE_INDICATORS, sizeof(TMsgShortSaleIndicators))
	{
	}
};

class TMsgMsShortSaleIndicators : public TMsgShortSaleIndicatorsBase
{
public:
    TMsgMsShortSaleIndicators(const char* const& symbol,
		const unsigned int& time,
		const char& shortSaleThresholdIndicator,
		const char& regSHOTestIndicator):

		TMsgShortSaleIndicatorsBase(symbol, time, shortSaleThresholdIndicator, regSHOTestIndicator, M_MS_SHORT_SALE_INDICATORS, sizeof(TMsgMsShortSaleIndicators))
	{
	}
};

class TMsgPmiBase : public TMsgHighLowBase
{
public:
	unsigned char m_securityStatus;
	unsigned char m_adjustment;
protected:
	TMsgPmiBase(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& bidDollar,
		const unsigned int& bidFraction,
		const unsigned int& askDollar,
		const unsigned int& askFraction,
		const unsigned char& securityStatus,
		const unsigned char& adjustment,
		const unsigned short& type,
		const unsigned short& length):
		TMsgHighLowBase(symbol, time, bidDollar, bidFraction, askDollar, askFraction, type, length),
        m_securityStatus(securityStatus),
        m_adjustment(adjustment)
	{
	}
	TMsgPmiBase(const unsigned __int64& symbol,
		const unsigned int& time,
		const unsigned int& bidDollar,
		const unsigned int& bidFraction,
		const unsigned int& askDollar,
		const unsigned int& askFraction,
		const unsigned char& securityStatus,
		const unsigned char& adjustment,
		const unsigned short& type,
		const unsigned short& length):
		TMsgHighLowBase(symbol, time, bidDollar, bidFraction, askDollar, askFraction, type, length),
        m_securityStatus(securityStatus),
        m_adjustment(adjustment)
	{
	}
};

class TMsgPmi : public TMsgPmiBase
{
public:
    TMsgPmi(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned int& bidDollar = 0,
		const unsigned int& bidFraction = 0,
		const unsigned int& askDollar = 0,
		const unsigned int& askFraction = 0,
		const unsigned char& securityStatus = 0,
		const unsigned char& adjustment = 0):
		TMsgPmiBase(symbol, time, bidDollar, bidFraction, askDollar, askFraction, securityStatus, adjustment, M_PMI, sizeof(TMsgPmi))
	{
	}
};

class TMsgMsPmi : public TMsgPmiBase
{
public:
    TMsgMsPmi(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned int& bidDollar = 0,
		const unsigned int& bidFraction = 0,
		const unsigned int& askDollar = 0,
		const unsigned int& askFraction = 0,
		const unsigned char& securityStatus = 0,
		const unsigned char& adjustment = 0):
		TMsgPmiBase(symbol, time, bidDollar, bidFraction, askDollar, askFraction, securityStatus, adjustment, M_MS_PMI, sizeof(TMsgMsPmi))
	{
	}
};

class TMsgLrpBase : public TMsgHighLowBase
{
public:
	unsigned char m_changeIndicator;
protected:
	TMsgLrpBase(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& lowDollar,
		const unsigned int& lowFraction,
		const unsigned int& highDollar,
		const unsigned int& highFraction,
		const unsigned char& changeIndicator,
		const unsigned short& type,
		const unsigned short& length):
		TMsgHighLowBase(symbol, time, lowDollar, lowFraction, highDollar, m_highFraction, type, length),
        m_changeIndicator(changeIndicator)
	{
	}
	TMsgLrpBase(const unsigned __int64& symbol,
		const unsigned int& time,
		const unsigned int& lowDollar,
		const unsigned int& lowFraction,
		const unsigned int& highDollar,
		const unsigned int& highFraction,
		const unsigned char& changeIndicator,
		const unsigned short& type,
		const unsigned short& length):
		TMsgHighLowBase(symbol, time, lowDollar, lowFraction, highDollar, m_highFraction, type, length),
        m_changeIndicator(changeIndicator)
	{
	}
};

#ifdef LRPS
class TMsgLrp : public TMsgLrpBase
{
public:
    TMsgLrp(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0,
		const unsigned char& changeIndicator = 0):
		TMsgLrpBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction, changeIndicator, M_LRP, sizeof(TMsgLrp))
	{
	}
};
#endif

class TMsgLuld : public TMsgLrpBase
{
public:
    TMsgLuld(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0,
		const unsigned char& changeIndicator = 0):
		TMsgLrpBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction, changeIndicator, M_LULD, sizeof(TMsgLuld))
	{
	}
};

#ifdef LRPS
class TMsgMsLrp : public TMsgLrpBase
{
public:
    TMsgMsLrp(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0,
		const unsigned char& changeIndicator = 0):
		TMsgLrpBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction, changeIndicator, M_MS_LRP, sizeof(TMsgMsLrp))
	{
	}
};
#endif

class TMsgMsLuld : public TMsgLrpBase
{
public:
    TMsgMsLuld(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0,
		const unsigned char& changeIndicator = 0):
		TMsgLrpBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction, changeIndicator, M_MS_LULD, sizeof(TMsgMsLuld))
	{
	}
};

class TMsgTradeTimeBase : public TMessageTimeSymbol
{
public:
	unsigned int m_tradeTime;
protected:
	TMsgTradeTimeBase(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& tradeTime,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_tradeTime(tradeTime)
	{
	}
};

class TMsgTradeTime : public TMsgTradeTimeBase
{
public:
    TMsgTradeTime(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& tradeTime):
		TMsgTradeTimeBase(symbol, time, tradeTime, M_T_TIME, sizeof(TMsgTradeTime))
	{
	}
};

class TMsgMsTradeTime : public TMsgTradeTimeBase
{
public:
    TMsgMsTradeTime(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& tradeTime):
		TMsgTradeTimeBase(symbol, time, tradeTime, M_MS_T_TIME, sizeof(TMsgMsTradeTime))
	{
	}
};

class TMsgRpiBase : public TMessageTimeSymbol
{
public:
	char m_indicator;
protected:
	TMsgRpiBase(const char* const& symbol,
		const unsigned int& time,
		const char& indicator,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_indicator(indicator)
	{
	}
	TMsgRpiBase(const unsigned __int64& symbol,
		const unsigned int& time,
		const char& indicator,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_indicator(indicator)
	{
	}
};

class TMsgRpi : public TMsgRpiBase
{
public:
    TMsgRpi(const char* const& symbol,
		const unsigned int& time,
		const char& indicator):
		TMsgRpiBase(symbol, time, indicator, M_RPI, sizeof(TMsgRpi))
	{
	}
    TMsgRpi(const unsigned __int64& symbol,
		const unsigned int& time,
		const char& indicator):
		TMsgRpiBase(symbol, time, indicator, M_RPI, sizeof(TMsgRpi))
	{
	}
};

class TMsgMsRpi : public TMsgRpiBase
{
public:
    TMsgMsRpi(const char* const& symbol,
		const unsigned int& time,
		const char& indicator):
		TMsgRpiBase(symbol, time, indicator, M_MS_RPI, sizeof(TMsgMsRpi))
	{
	}
    TMsgMsRpi(const unsigned __int64& symbol,
		const unsigned int& time,
		const char& indicator):
		TMsgRpiBase(symbol, time, indicator, M_MS_RPI, sizeof(TMsgMsRpi))
	{
	}
};

class TMsgSecurityType : public TMsgRpiBase
{
public:
	TMsgSecurityType(const char* const& symbol,
		const unsigned int& time = 0,
		const char& securityType = 0):
		TMsgRpiBase(symbol, time, securityType, M_SECURITY_TYPE, sizeof(TMsgSecurityType))
	{
	}
	TMsgSecurityType(const unsigned __int64& symbol = 0,
		const unsigned int& time = 0,
		const char& securityType = 0):
		TMsgRpiBase(symbol, time, securityType, M_SECURITY_TYPE, sizeof(TMsgSecurityType))
	{
	}
};

class TMsgMsSecurityType : public TMsgRpiBase
{
public:
	TMsgMsSecurityType(const char* const& symbol,
		const unsigned int& time = 0,
		const char& securityType = 0):
		TMsgRpiBase(symbol, time, securityType, M_MS_SECURITY_TYPE, sizeof(TMsgMsSecurityType))
	{
	}
	TMsgMsSecurityType(const unsigned __int64& symbol = 0,
		const unsigned int& time = 0,
		const char& securityType = 0):
		TMsgRpiBase(symbol, time, securityType, M_MS_SECURITY_TYPE, sizeof(TMsgMsSecurityType))
	{
	}
};

enum AggregatePrintFlags : unsigned char
{
	APF_NoPriceChanges		= 0,
	APF_LastPriceChanged	= 1,
	APF_LowPriceChanged		= 2,
	APF_HighPriceChanged	= 4,
	APF_OpeningPrice		= 8,
	APF_ClosingPrice		= 0x10,
	APF_PrimaryOpeningPrice	= 0x20,
	APF_NewIntraDayTick		= 0x80,
};

class TMsgAggregatedPrint : public TMessageTimeSymbol
{
public:
	TMsgAggregatedPrint(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& priceDollar,
		const unsigned int& priceFraction,
		const unsigned int& size,
		const unsigned char& flags,
		const unsigned char& flagsL1):
		TMessageTimeSymbol(symbol, time, M_AGGREGATED_PRINT, sizeof(TMsgAggregatedPrint)),
		m_priceDollar(priceDollar),
		m_priceFraction(priceFraction),
		m_size(size),
		m_flags(flags),
		m_flagsL1(flagsL1)
	{
	}
 
	unsigned int m_priceDollar;
	unsigned int m_priceFraction;
	unsigned int m_size;
	unsigned char m_flags;
	unsigned char m_flagsL1;
};

class TSmMsgAggregatedPrint : public TMessageTime
{
public:
	TSmMsgAggregatedPrint(const unsigned short& symbol,
		const unsigned int& time,
		const unsigned int& priceDollar,
		const unsigned int& priceFraction,
		const unsigned int& size,
		const unsigned char& flags,
		const unsigned char& flagsL1):
		TMessageTime(time, SM_M_AGGREGATED_PRINT, sizeof(TSmMsgAggregatedPrint)),
		m_priceDollar(priceDollar),
		m_priceFraction(priceFraction),
		m_size(size),
		m_symbol(symbol),
		m_flags(flags),
		m_flagsL1(flagsL1)
	{
	}
 
	unsigned int m_priceDollar;
	unsigned int m_priceFraction;
	unsigned int m_size;
	unsigned short m_symbol;
	unsigned char m_flags;
	unsigned char m_flagsL1;
};

//	TMessageSymbol(const char* symbol, unsigned short type, unsigned short length):
class TMsgMsAggregatedPrintShort : public TMessageSymbol
{
public:
	TMsgMsAggregatedPrintShort(const char* const& symbol,
		const unsigned int& price,
		const unsigned short& size,
		const unsigned char& flags):
		TMessageSymbol(symbol, M_MS_AGGREGATED_PRINT_SHORT, sizeof(TMsgMsAggregatedPrintShort)),
		m_price(price),
		m_size(size),
		m_flags(flags)
	{
	}

	unsigned int m_price;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned short m_size;//Up to 65535
	unsigned char m_flags;
};

class TMsgMsAggregatedPrintLong : public TMessageSymbol
{
public:
	TMsgMsAggregatedPrintLong(const char* const& symbol,
		const unsigned int& priceDollar,
		const unsigned int& priceFraction,
		const unsigned int& size,
		const unsigned char& flags):
		TMessageSymbol(symbol, M_MS_AGGREGATED_PRINT_LONG, sizeof(TMsgMsAggregatedPrintLong)),
		m_priceDollar(priceDollar),
		m_priceFraction(priceFraction),
		m_size(size),
		m_flags(flags)
	{
	}

	unsigned int m_priceDollar;
	unsigned int m_priceFraction;
	unsigned int m_size;
	unsigned char m_flags;
};

class TSmMsgMsAggregatedPrintShort : public Message
{
public:
	TSmMsgMsAggregatedPrintShort(const unsigned short& symbol, 
		const unsigned int& price,
		const unsigned short& size,
		const unsigned char& flags):
		Message(SM_MS_AGGREGATED_PRINT_SHORT, sizeof(TSmMsgMsAggregatedPrintShort)),
		m_price(price),
		m_size(size),
		m_symbol(symbol),
		m_flags(flags)
	{
	}

	unsigned int m_price;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned short m_size;//Up to 65535
	unsigned short m_symbol;
	unsigned char m_flags;
};

class TSmMsgMsAggregatedPrintLong : public Message
{
public:
	TSmMsgMsAggregatedPrintLong(const unsigned short& symbol, 
		const unsigned int& priceDollar,
		const unsigned int& priceFraction,
		const unsigned int& size,
		const unsigned char& flags):
		Message(SM_MS_AGGREGATED_PRINT_LONG, sizeof(TSmMsgMsAggregatedPrintLong)),
		m_priceDollar(priceDollar),
		m_priceFraction(priceFraction),
		m_size(size),
		m_symbol(symbol),
		m_flags(flags)
	{
	}

	unsigned int m_priceDollar;
	unsigned int m_priceFraction;
	unsigned int m_size;
	unsigned short m_symbol;
	unsigned char m_flags;
};

class TMsgDividendsAndSplitsBase : public TMessageTimeSymbol
{
public:
	unsigned int m_dividendDollar;
	unsigned int m_dividendFraction;
    unsigned short m_splitNumerator;
    unsigned short m_splitDenominator;
	char m_exDivDate[sizeof(unsigned int) + 1];
protected:
    TMsgDividendsAndSplitsBase(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& dividendDollar,
		const unsigned int& dividendFraction,
	    const unsigned short& splitNumerator,
		const unsigned short& splitDenominator,
		const unsigned int& exDivDate,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_dividendDollar(dividendDollar),
		m_dividendFraction(dividendFraction),
        m_splitNumerator(splitNumerator),
        m_splitDenominator(splitDenominator)
	{
		*(unsigned int*)m_exDivDate = exDivDate;
		m_exDivDate[sizeof(unsigned int)] = '\0';
	}
};

class TMsgDividendsAndSplits : public TMsgDividendsAndSplitsBase
{
public:
    TMsgDividendsAndSplits(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& dividendDollar,
		const unsigned int& dividendFraction,
	    const unsigned short& splitNumerator,
		const unsigned short& splitDenominator,
		const unsigned int& exDivDate):
		TMsgDividendsAndSplitsBase(symbol,
			time,
			dividendDollar,
			dividendFraction,
			splitNumerator,
			splitDenominator,
			exDivDate,
			M_DIVIDENDS_AND_SPLITS,
			sizeof(TMsgDividendsAndSplits))
	{
	}
};

class TMsgMsDividendsAndSplits : public TMsgDividendsAndSplitsBase
{
public:
    TMsgMsDividendsAndSplits(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& dividendDollar,
		const unsigned int& dividendFraction,
	    const unsigned short& splitNumerator,
		const unsigned short& splitDenominator,
		const unsigned int& exDivDate):
		TMsgDividendsAndSplitsBase(symbol,
			time,
			dividendDollar,
			dividendFraction,
			splitNumerator,
			splitDenominator,
			exDivDate,
			M_MS_DIVIDENDS_AND_SPLITS,
			sizeof(TMsgMsDividendsAndSplits))
	{
	}
};

class TMsgPreviousDayCloseBase : public TMessageTimeSymbol
{
public:
	unsigned int m_closePriceDollar;
	unsigned int m_closePriceFraction;
protected:
    TMsgPreviousDayCloseBase(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& closePriceDollar,
		const unsigned int& closePriceFraction,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_closePriceDollar(closePriceDollar),
		m_closePriceFraction(closePriceFraction)
	{
	}
};

class TMsgPreviousDayClose : public TMsgPreviousDayCloseBase
{
public:
    TMsgPreviousDayClose(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned int& closePriceDollar = 0,
		const unsigned int& closePriceFraction = 0):
		TMsgPreviousDayCloseBase(symbol,
			time,
			closePriceDollar,
			closePriceFraction,
			M_PREVIOUS_DAY_CLOSE,
			sizeof(TMsgPreviousDayClose))
	{
	}
};

class TMsgMsPreviousDayClose : public TMsgPreviousDayCloseBase
{
public:
    TMsgMsPreviousDayClose(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned int& closePriceDollar = 0,
		const unsigned int& closePriceFraction = 0):
		TMsgPreviousDayCloseBase(symbol,
			time,
			closePriceDollar,
			closePriceFraction,
			M_MS_PREVIOUS_DAY_CLOSE,
			sizeof(TMsgMsPreviousDayClose))
	{
	}
};

class TMsgResetImbalances : public Message
{
public:
	TMsgResetImbalances():Message(M_RESET_IMBALANCES, sizeof(TMsgResetImbalances)){}
};

class TMsgMsResetImbalances : public Message
{
public:
	TMsgMsResetImbalances():Message(M_MS_RESET_IMBALANCES, sizeof(TMsgMsResetImbalances)){}
};


////////
class TMsgSymbolOrdinalValue : public TMessageSymbol
{
public:
	unsigned char m_ordinal;
protected:
	TMsgSymbolOrdinalValue(const char* const& symbol, const unsigned char& ordinal, const unsigned short& type, const unsigned short& length):TMessageSymbol(symbol, type, length), m_ordinal(ordinal){}
	TMsgSymbolOrdinalValue(const unsigned __int64& symbol, const unsigned char& ordinal, const unsigned short& type, const unsigned short& length):TMessageSymbol(symbol, type, length), m_ordinal(ordinal){}
};

class TMsgSymbolOrdinalHtb : public TMsgSymbolOrdinalValue
{
public:
	unsigned char m_htb;
protected:
	TMsgSymbolOrdinalHtb(const char* const& symbol, const unsigned char& ordinal, const unsigned char& htb, const unsigned short& type, const unsigned short& length):TMsgSymbolOrdinalValue(symbol, ordinal, type, length), m_htb(htb){}
	TMsgSymbolOrdinalHtb(const unsigned __int64& symbol, const unsigned char& ordinal, const unsigned char& htb, const unsigned short& type, const unsigned short& length):TMsgSymbolOrdinalValue(symbol, ordinal, type, length), m_htb(htb){}
};

class TMsgStockHtb : public TMsgSymbolOrdinalHtb
{
public:
	TMsgStockHtb(const char* const& symbol, const unsigned char& ordinal, const unsigned char& htb):TMsgSymbolOrdinalHtb(symbol, ordinal, htb, TM_STOCK_HTB, sizeof(TMsgStockHtb)){}
	TMsgStockHtb(const unsigned __int64& symbol, const unsigned char& ordinal, const unsigned char& htb):TMsgSymbolOrdinalHtb(symbol, ordinal, htb, TM_STOCK_HTB, sizeof(TMsgStockHtb)){}
};

class TMsgEquityHtb : public TMsgSymbolOrdinalHtb
{
public:
	TMsgEquityHtb(const char* const& symbol, const unsigned char& ordinal, const unsigned char& htb):TMsgSymbolOrdinalHtb(symbol, ordinal, htb, TM_EQUITY_HTB, sizeof(TMsgEquityHtb)){}
	TMsgEquityHtb(const unsigned __int64& symbol, const unsigned char& ordinal, const unsigned char& htb):TMsgSymbolOrdinalHtb(symbol, ordinal, htb, TM_EQUITY_HTB, sizeof(TMsgEquityHtb)){}
};
/*
class TMsgSymbolOrdinalPrice : public TMsgSymbolOrdinalValue
{
public:
	unsigned int m_compactPrice;
protected:
	TMsgSymbolOrdinalPrice(const char* const& symbol, const unsigned char& ordinal, const unsigned int& price, const unsigned short& type, const unsigned short& length) :TMsgSymbolOrdinalValue(symbol, ordinal, type, length), m_compactPrice(price){}
	TMsgSymbolOrdinalPrice(const unsigned __int64& symbol, const unsigned char& ordinal, const unsigned int& price, const unsigned short& type, const unsigned short& length) :TMsgSymbolOrdinalValue(symbol, ordinal, type, length), m_compactPrice(price){}
};
*/

class TMsgSymbolOrdinalBetaAndRetailInfo : public TMsgSymbolOrdinalValue//TMsgSymbolOrdinalPrice
{
public:
//07/02/2019
	unsigned char m_PM_EL_Rate;
	unsigned char m_PM_ES_Rate;
	unsigned char m_PM_HL_Rate;
	unsigned char m_PM_HS_Rate;
	unsigned char m_EL_Rate;
	unsigned char m_ES_Rate;
	unsigned char m_HL_Rate;
	unsigned char m_HS_Rate;
//	unsigned char m_Fed_Req;
//	unsigned char m_Asset_Type;
//	bool m_Marginable;
//	unsigned char m_Sec_Type;
//	unsigned char m_Status;

//	unsigned char m_margin;
//	int m_compactBeta;

	void SetStockLoanInfo(const StockLoanInfo& price)
	{
		m_PM_EL_Rate = price.GetPmElRate();
		m_PM_ES_Rate = price.GetPmEsRate();
		m_PM_HL_Rate = price.GetPmHlRate();
		m_PM_HS_Rate = price.GetPmHsRate();
		m_EL_Rate = price.GetElRate();
		m_ES_Rate = price.GetEsRate();
		m_HL_Rate = price.GetHlRate();
		m_HS_Rate = price.GetHsRate();
	}

protected:
	TMsgSymbolOrdinalBetaAndRetailInfo(const char* const& symbol,
		const unsigned char& ordinal,

		const unsigned char& PM_EL_Rate,
		const unsigned char& PM_ES_Rate,
		const unsigned char& PM_HL_Rate,
		const unsigned char& PM_HS_Rate,
		const unsigned char& EL_Rate,
		const unsigned char& ES_Rate,
		const unsigned char& HL_Rate,
		const unsigned char& HS_Rate,
//		const unsigned char& Fed_Req,
//		const unsigned char& Asset_Type,
//		const bool& Marginable,
//		const unsigned char& Sec_Type,
//		const unsigned char& Status,

//		const unsigned char& margin,
//		const int& compactBeta,

		const unsigned short& type,
		const unsigned short& length):
		TMsgSymbolOrdinalValue(symbol, ordinal, type, length),
		m_PM_EL_Rate(PM_EL_Rate),
		m_PM_ES_Rate(PM_ES_Rate),
		m_PM_HL_Rate(PM_HL_Rate),
		m_PM_HS_Rate(PM_HS_Rate),
		m_EL_Rate(EL_Rate),
		m_ES_Rate(ES_Rate),
		m_HL_Rate(HL_Rate),
		m_HS_Rate(HS_Rate)
//		m_Fed_Req(Fed_Req),
//		m_Asset_Type(Asset_Type),
//		m_Marginable(Marginable),
//		m_Sec_Type(Sec_Type),
//		m_Status(Status),
//		m_margin(margin)
//		m_compactBeta(compactBeta)
	{
	}
	TMsgSymbolOrdinalBetaAndRetailInfo(const unsigned __int64& symbol,
		const unsigned char& ordinal,

		const unsigned char& PM_EL_Rate,
		const unsigned char& PM_ES_Rate,
		const unsigned char& PM_HL_Rate,
		const unsigned char& PM_HS_Rate,
		const unsigned char& EL_Rate,
		const unsigned char& ES_Rate,
		const unsigned char& HL_Rate,
		const unsigned char& HS_Rate,
//		const unsigned char& Fed_Req,
//		const unsigned char& Asset_Type,
//		const bool& Marginable,
//		const unsigned char& Sec_Type,
//		const unsigned char& Status,

//		const unsigned char& margin,
//		const int& compactBeta,

		const unsigned short& type,
		const unsigned short& length):
		TMsgSymbolOrdinalValue(symbol, ordinal, type, length),
//		TMsgSymbolOrdinalPrice(symbol, ordinal, price, type, length),
		m_PM_EL_Rate(PM_EL_Rate),
		m_PM_ES_Rate(PM_ES_Rate),
		m_PM_HL_Rate(PM_HL_Rate),
		m_PM_HS_Rate(PM_HS_Rate),
		m_EL_Rate(EL_Rate),
		m_ES_Rate(ES_Rate),
		m_HL_Rate(HL_Rate),
		m_HS_Rate(HS_Rate)
//		m_Fed_Req(Fed_Req),
//		m_Asset_Type(Asset_Type),
//		m_Marginable(Marginable),
//		m_Sec_Type(Sec_Type),
//		m_Status(Status),
//		m_margin(margin)
//		m_compactBeta(compactBeta)
	{
	}
};

//////
class TMsgStockBetaAndRetailInfo : public TMsgSymbolOrdinalBetaAndRetailInfo
{
public:
	TMsgStockBetaAndRetailInfo(const char* const& symbol,
		const unsigned char& ordinal,
		const unsigned char& PM_EL_Rate,
		const unsigned char& PM_ES_Rate,
		const unsigned char& PM_HL_Rate,
		const unsigned char& PM_HS_Rate,
		const unsigned char& EL_Rate,
		const unsigned char& ES_Rate,
		const unsigned char& HL_Rate,
		const unsigned char& HS_Rate):
//		const unsigned char& Fed_Req,
//		const unsigned char& Asset_Type,
//		const bool& Marginable,
//		const unsigned char& Sec_Type,
//		const unsigned char& Status,
//		const unsigned char& margin):
//		const int& compactBeta):
		TMsgSymbolOrdinalBetaAndRetailInfo(symbol,
			ordinal,
			PM_EL_Rate,
			PM_ES_Rate,
			PM_HL_Rate,
			PM_HS_Rate,
			EL_Rate,
			ES_Rate,
			HL_Rate,
			HS_Rate,
//			Fed_Req,
//			Asset_Type,
//			Marginable,
//			Sec_Type,
//			Status,
//			margin,
//			compactBeta,
			TM_STOCK_BETA_AND_RETAIL_INFO,
			sizeof(TMsgStockBetaAndRetailInfo))
	{
	}
	TMsgStockBetaAndRetailInfo(const unsigned __int64& symbol,
		const unsigned char& ordinal,
		const unsigned char& PM_EL_Rate,
		const unsigned char& PM_ES_Rate,
		const unsigned char& PM_HL_Rate,
		const unsigned char& PM_HS_Rate,
		const unsigned char& EL_Rate,
		const unsigned char& ES_Rate,
		const unsigned char& HL_Rate,
		const unsigned char& HS_Rate):
//		const unsigned char& Fed_Req,
//		const unsigned char& Asset_Type,
//		const bool& Marginable,
//		const unsigned char& Sec_Type,
//		const unsigned char& Status,
//		const unsigned char& margin):
//		const int& compactBeta):
		TMsgSymbolOrdinalBetaAndRetailInfo(symbol,
			ordinal,
			PM_EL_Rate,
			PM_ES_Rate,
			PM_HL_Rate,
			PM_HS_Rate,
			EL_Rate,
			ES_Rate,
			HL_Rate,
			HS_Rate,
//			Fed_Req,
//			Asset_Type,
//			Marginable,
//			Sec_Type,
//			Status,
//			margin,
//			compactBeta,
			TM_STOCK_BETA_AND_RETAIL_INFO,
			sizeof(TMsgStockBetaAndRetailInfo))
	{
	}
};

class TMsgEquityBetaAndRetailInfo : public TMsgSymbolOrdinalBetaAndRetailInfo
{
public:
	TMsgEquityBetaAndRetailInfo(const char* const& symbol,
		const unsigned char& ordinal,
		const unsigned char& PM_EL_Rate,
		const unsigned char& PM_ES_Rate,
		const unsigned char& PM_HL_Rate,
		const unsigned char& PM_HS_Rate,
		const unsigned char& EL_Rate,
		const unsigned char& ES_Rate,
		const unsigned char& HL_Rate,
		const unsigned char& HS_Rate):
//		const unsigned char& Fed_Req,
//		const unsigned char& Asset_Type,
//		const bool& Marginable,
//		const unsigned char& Sec_Type,
//		const unsigned char& Status,
//		const unsigned char& margin):
//		const int& compactBeta):
		TMsgSymbolOrdinalBetaAndRetailInfo(symbol,
			ordinal,
			PM_EL_Rate,
			PM_ES_Rate,
			PM_HL_Rate,
			PM_HS_Rate,
			EL_Rate,
			ES_Rate,
			HL_Rate,
			HS_Rate,
//			Fed_Req,
//			Asset_Type,
//			Marginable,
//			Sec_Type,
//			Status,
//			margin,
//			compactBeta,
			TM_EQUITY_BETA_AND_RETAIL_INFO,
			sizeof(TMsgEquityBetaAndRetailInfo))
	{
	}
	TMsgEquityBetaAndRetailInfo(const unsigned __int64& symbol,
		const unsigned char& ordinal,
		const unsigned char& PM_EL_Rate,
		const unsigned char& PM_ES_Rate,
		const unsigned char& PM_HL_Rate,
		const unsigned char& PM_HS_Rate,
		const unsigned char& EL_Rate,
		const unsigned char& ES_Rate,
		const unsigned char& HL_Rate,
		const unsigned char& HS_Rate):
//		const unsigned char& Fed_Req,
//		const unsigned char& Asset_Type,
//		const bool& Marginable,
//		const unsigned char& Sec_Type,
//		const unsigned char& Status,
//		const unsigned char& margin):
//		const int& compactBeta):
		TMsgSymbolOrdinalBetaAndRetailInfo(symbol,
			ordinal,
			PM_EL_Rate,
			PM_ES_Rate,
			PM_HL_Rate,
			PM_HS_Rate,
			EL_Rate,
			ES_Rate,
			HL_Rate,
			HS_Rate,
//			Fed_Req,
//			Asset_Type,
//			Marginable,
//			Sec_Type,
//			Status,
//			margin,
//			compactBeta,
			TM_EQUITY_BETA_AND_RETAIL_INFO,
			sizeof(TMsgEquityBetaAndRetailInfo))
	{
	}
};

class TMsgPositionBetaAndRetailInfo : public TMsgSymbolOrdinalBetaAndRetailInfo
{
public:
	TMsgPositionBetaAndRetailInfo(const char* const& accountId,
		const char* const& symbol,
		const unsigned char& ordinal,
		const unsigned char& PM_EL_Rate,
		const unsigned char& PM_ES_Rate,
		const unsigned char& PM_HL_Rate,
		const unsigned char& PM_HS_Rate,
		const unsigned char& EL_Rate,
		const unsigned char& ES_Rate,
		const unsigned char& HL_Rate,
		const unsigned char& HS_Rate):
//		const unsigned char& Fed_Req,
//		const unsigned char& Asset_Type,
//		const bool& Marginable,
//		const unsigned char& Sec_Type,
//		const unsigned char& Status,
//		const unsigned char& margin):
//		const int& compactBeta):
		TMsgSymbolOrdinalBetaAndRetailInfo(symbol,
			ordinal,
			PM_EL_Rate,
			PM_ES_Rate,
			PM_HL_Rate,
			PM_HS_Rate,
			EL_Rate,
			ES_Rate,
			HL_Rate,
			HS_Rate,
//			Fed_Req,
//			Asset_Type,
//			Marginable,
//			Sec_Type,
//			Status,
//			margin,
//			compactBeta,
			TM_POSITION_BETA_AND_RETAIL_INFO,
			sizeof(TMsgPositionBetaAndRetailInfo))
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountId, '\0', true);
	}
	TMsgPositionBetaAndRetailInfo(const char* const& accountId,
		const unsigned __int64& symbol,
		const unsigned char& ordinal,
		const unsigned char& PM_EL_Rate,
		const unsigned char& PM_ES_Rate,
		const unsigned char& PM_HL_Rate,
		const unsigned char& PM_HS_Rate,
		const unsigned char& EL_Rate,
		const unsigned char& ES_Rate,
		const unsigned char& HL_Rate,
		const unsigned char& HS_Rate):
//		const unsigned char& Fed_Req,
//		const unsigned char& Asset_Type,
//		const bool& Marginable,
//		const unsigned char& Sec_Type,
//		const unsigned char& Status,
//		const unsigned char& margin):
//		const int& compactBeta):
		TMsgSymbolOrdinalBetaAndRetailInfo(symbol,
			ordinal,
			PM_EL_Rate,
			PM_ES_Rate,
			PM_HL_Rate,
			PM_HS_Rate,
			EL_Rate,
			ES_Rate,
			HL_Rate,
			HS_Rate,
//			Fed_Req,
//			Asset_Type,
//			Marginable,
//			Sec_Type,
//			Status,
//			margin,
//			compactBeta,
			TM_POSITION_BETA_AND_RETAIL_INFO,
			sizeof(TMsgPositionBetaAndRetailInfo))
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountId, '\0', true);
	}
	char m_accountId[MAX_ACCOUNT_SIZE];
};

//////

class TMsgSymbolOrdinalBorrowInfo : public TMsgSymbolOrdinalValue//07/02/2019
{
public:
//	unsigned char m_htb;
#ifdef BORROW_PRICE_DISCOUNT
	unsigned char m_discountFlag;
#endif
	unsigned int m_compactPrice;
	unsigned int m_quantity;
protected:
	TMsgSymbolOrdinalBorrowInfo(const char* const& symbol,
		const unsigned char& ordinal,
//		const unsigned char& htb,
#ifdef BORROW_PRICE_DISCOUNT
		const unsigned char& discountFlag,
#endif
		const unsigned int& price,
		const unsigned int& quantity,
		const unsigned short& type,
		const unsigned short& length):
		TMsgSymbolOrdinalValue(symbol, ordinal, type, length),
//		m_htb(htb),
#ifdef BORROW_PRICE_DISCOUNT
		m_discountFlag(discountFlag),
#endif
		m_compactPrice(price),
		m_quantity(quantity)
	{
	}
	TMsgSymbolOrdinalBorrowInfo(const unsigned __int64& symbol,
		const unsigned char& ordinal,
//		const unsigned char& htb,
#ifdef BORROW_PRICE_DISCOUNT
		const unsigned char& discountFlag,
#endif
		const unsigned int& price,
		const unsigned int& quantity,
		const unsigned short& type,
		const unsigned short& length):
		TMsgSymbolOrdinalValue(symbol, ordinal, type, length),
//		m_htb(htb),
#ifdef BORROW_PRICE_DISCOUNT
		m_discountFlag(discountFlag),
#endif
		m_compactPrice(price),
		m_quantity(quantity)
	{
	}
};
////
class TMsgStockBorrowInfo : public TMsgSymbolOrdinalBorrowInfo
{
public:
	TMsgStockBorrowInfo(const char* const& symbol,
		const unsigned char& ordinal,
//		const unsigned char& htb,
#ifdef BORROW_PRICE_DISCOUNT
		const unsigned char& discountFlag,
#endif
		const unsigned int& price,
		const unsigned int& quantity):
		TMsgSymbolOrdinalBorrowInfo(symbol,
			ordinal,
//			htb,
#ifdef BORROW_PRICE_DISCOUNT
			discountFlag,
#endif
			price,
			quantity,
			TM_STOCK_BORROW_INFO,
			sizeof(TMsgStockBorrowInfo))
	{
	}
	TMsgStockBorrowInfo(const unsigned __int64& symbol,
		const unsigned char& ordinal,
//		const unsigned char& htb,
#ifdef BORROW_PRICE_DISCOUNT
		const unsigned char& discountFlag,
#endif
		const unsigned int& price,
		const unsigned int& quantity):
		TMsgSymbolOrdinalBorrowInfo(symbol,
			ordinal,
//			htb,
#ifdef BORROW_PRICE_DISCOUNT
			discountFlag,
#endif
			price,
			quantity,
			TM_STOCK_BORROW_INFO,
			sizeof(TMsgStockBorrowInfo))
	{
	}
};

class TMsgEquityBorrowInfo : public TMsgSymbolOrdinalBorrowInfo
{
public:
	TMsgEquityBorrowInfo(const char* const& symbol,
		const unsigned char& ordinal,
//		const unsigned char& htb,
#ifdef BORROW_PRICE_DISCOUNT
		const unsigned char& discountFlag,
#endif
		const unsigned int& price,
		const unsigned int& quantity):
		TMsgSymbolOrdinalBorrowInfo(symbol,
			ordinal,
//			htb,
#ifdef BORROW_PRICE_DISCOUNT
			discountFlag,
#endif
			price,
			quantity,
			TM_EQUITY_BORROW_INFO,
			sizeof(TMsgEquityBorrowInfo))
	{
	}
	TMsgEquityBorrowInfo(const unsigned __int64& symbol,
		const unsigned char& ordinal,
//		const unsigned char& htb,
#ifdef BORROW_PRICE_DISCOUNT
		const unsigned char& discountFlag,
#endif
		const unsigned int& price,
		const unsigned int& quantity):
		TMsgSymbolOrdinalBorrowInfo(symbol,
			ordinal,
//			htb,
#ifdef BORROW_PRICE_DISCOUNT
			discountFlag,
#endif
			price,
			quantity,
			TM_EQUITY_BORROW_INFO,
			sizeof(TMsgEquityBorrowInfo))
	{
	}
};

class TMsgPositionBorrowInfo : public TMsgSymbolOrdinalBorrowInfo
{
public:
	TMsgPositionBorrowInfo(const char* const& accountId,
		const char* const& symbol,
		const unsigned char& ordinal,
//		const unsigned char& htb,
#ifdef BORROW_PRICE_DISCOUNT
		const unsigned char& discountFlag,
#endif
		const unsigned int& price,
		const unsigned int& quantity):
		TMsgSymbolOrdinalBorrowInfo(symbol,
			ordinal,
//			htb,
#ifdef BORROW_PRICE_DISCOUNT
			discountFlag,
#endif
			price,
			quantity,
			TM_POSITION_BORROW_INFO,
			sizeof(TMsgPositionBorrowInfo))
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountId, '\0', true);
	}
	TMsgPositionBorrowInfo(const char* const& accountId,
		const unsigned __int64& symbol,
		const unsigned char& ordinal,
//		const unsigned char& htb,
#ifdef BORROW_PRICE_DISCOUNT
		const unsigned char& discountFlag,
#endif
		const unsigned int& price,
		const unsigned int& quantity):
		TMsgSymbolOrdinalBorrowInfo(symbol,
			ordinal,
//			htb,
#ifdef BORROW_PRICE_DISCOUNT
			discountFlag,
#endif
			price,
			quantity,
			TM_POSITION_BORROW_INFO,
			sizeof(TMsgPositionBorrowInfo))
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountId, '\0', true);
	}
	char m_accountId[MAX_ACCOUNT_SIZE];
};

////
class TMsgSymbolOrdinalStockLoanInfo : public TMsgSymbolOrdinalBetaAndRetailInfo//TMsgSymbolOrdinalPrice//07/02/2019
{
public:
	unsigned char m_htb;
#ifdef BORROW_PRICE_DISCOUNT
	unsigned char m_discountFlag;
#endif
	unsigned int m_compactPrice;
	unsigned int m_quantity;
	void SetStockLoanInfo(const StockLoanInfo& price)
	{
		TMsgSymbolOrdinalBetaAndRetailInfo::SetStockLoanInfo(price);
		m_htb = price.GetHTB();
#ifdef BORROW_PRICE_DISCOUNT
		m_discountFlag = price.GetDiscountFlag();
#endif
		m_compactPrice = price.GetCompactBorrowPrice();
		m_quantity = price.GetAvailableQuantity();
	}
protected:
	TMsgSymbolOrdinalStockLoanInfo(const char* const& symbol,
		const unsigned char& ordinal,
		const unsigned int& price,
		const unsigned int& quantity,
#ifdef BORROW_PRICE_DISCOUNT
		const unsigned char& discountFlag,
#endif
//		const int& compactBeta,
//		const unsigned char& margin,
		const unsigned char& htb,

		const unsigned char& PM_EL_Rate,
		const unsigned char& PM_ES_Rate,
		const unsigned char& PM_HL_Rate,
		const unsigned char& PM_HS_Rate,
		const unsigned char& EL_Rate,
		const unsigned char& ES_Rate,
		const unsigned char& HL_Rate,
		const unsigned char& HS_Rate,
//		const unsigned char& Fed_Req,
//		const unsigned char& Asset_Type,
//		const bool& Marginable,
//		const unsigned char& Sec_Type,
//		const unsigned char& Status,

		const unsigned short& type,
		const unsigned short& length):
		TMsgSymbolOrdinalBetaAndRetailInfo(symbol, ordinal,
			PM_EL_Rate,
			PM_ES_Rate,
			PM_HL_Rate,
			PM_HS_Rate,
			EL_Rate,
			ES_Rate,
			HL_Rate,
			HS_Rate,
//			Fed_Req,
//			Asset_Type,
//			Marginable,
//			Sec_Type,
//			Status,
//			margin,
//			compactBeta,
			type, length),
//		TMsgSymbolOrdinalPrice(symbol, ordinal, price, type, length),
		m_htb(htb),
#ifdef BORROW_PRICE_DISCOUNT
		m_discountFlag(discountFlag),
#endif
		m_compactPrice(price),
		m_quantity(quantity)
	{
	}
	TMsgSymbolOrdinalStockLoanInfo(const unsigned __int64& symbol,
		const unsigned char& ordinal,
		const unsigned int& price,
		const unsigned int& quantity,
#ifdef BORROW_PRICE_DISCOUNT
		const unsigned char& discountFlag,
#endif
//		const int& compactBeta,
//		const unsigned char& margin,
		const unsigned char& htb,

		const unsigned char& PM_EL_Rate,
		const unsigned char& PM_ES_Rate,
		const unsigned char& PM_HL_Rate,
		const unsigned char& PM_HS_Rate,
		const unsigned char& EL_Rate,
		const unsigned char& ES_Rate,
		const unsigned char& HL_Rate,
		const unsigned char& HS_Rate,
//		const unsigned char& Fed_Req,
//		const unsigned char& Asset_Type,
//		const bool& Marginable,
//		const unsigned char& Sec_Type,
//		const unsigned char& Status,

		const unsigned short& type,
		const unsigned short& length):
		TMsgSymbolOrdinalBetaAndRetailInfo(symbol, ordinal,
			PM_EL_Rate,
			PM_ES_Rate,
			PM_HL_Rate,
			PM_HS_Rate,
			EL_Rate,
			ES_Rate,
			HL_Rate,
			HS_Rate,
//			Fed_Req,
//			Asset_Type,
//			Marginable,
//			Sec_Type,
//			Status,
//			margin,
//			compactBeta,
			type, length),
//		TMsgSymbolOrdinalPrice(symbol, ordinal, price, type, length),
		m_htb(htb),
#ifdef BORROW_PRICE_DISCOUNT
		m_discountFlag(discountFlag),
#endif
		m_compactPrice(price),
		m_quantity(quantity)
	{
	}
};

class TMsgStockBorrowPrice : public TMsgSymbolOrdinalStockLoanInfo
{
public:
	TMsgStockBorrowPrice(const char* const& symbol, const unsigned char& ordinal, const StockLoanInfo& price) :
		TMsgSymbolOrdinalStockLoanInfo(symbol,
			ordinal,
			price.GetCompactBorrowPrice(),
			price.GetAvailableQuantity(),
#ifdef BORROW_PRICE_DISCOUNT
			price.GetDiscountFlag(),
#endif
//			price.GetMargin(),
			price.GetHTB(),
			price.GetPmElRate(),
			price.GetPmEsRate(),
			price.GetPmHlRate(),
			price.GetPmHsRate(),
			price.GetElRate(),
			price.GetEsRate(),
			price.GetHlRate(),
			price.GetHsRate(),
//			price.GetFedReq(),
//			price.GetAssetType(),
//			price.isMarginable(),
//			price.GetSecType(),
//			price.GetStatus(),

			TM_STOCK_BORROW_PRICE,
			sizeof(TMsgStockBorrowPrice))
	{
	}
	TMsgStockBorrowPrice(const unsigned __int64& symbol, const unsigned char& ordinal, const StockLoanInfo& price):
		TMsgSymbolOrdinalStockLoanInfo(symbol,
			ordinal,
			price.GetCompactBorrowPrice(),
			price.GetAvailableQuantity(),
#ifdef BORROW_PRICE_DISCOUNT
			price.GetDiscountFlag(),
#endif
//			price.GetCompactBeta(),
//			price.GetMargin(),
			price.GetHTB(),
			price.GetPmElRate(),
			price.GetPmEsRate(),
			price.GetPmHlRate(),
			price.GetPmHsRate(),
			price.GetElRate(),
			price.GetEsRate(),
			price.GetHlRate(),
			price.GetHsRate(),
//			price.GetFedReq(),
//			price.GetAssetType(),
//			price.isMarginable(),
//			price.GetSecType(),
//			price.GetStatus(),

			TM_STOCK_BORROW_PRICE,
			sizeof(TMsgStockBorrowPrice))
	{
	}
};

class TMsgEquityBorrowPrice : public TMsgSymbolOrdinalStockLoanInfo
{
public:
	TMsgEquityBorrowPrice(const char* const& symbol, const unsigned char& ordinal, const StockLoanInfo& price):
		TMsgSymbolOrdinalStockLoanInfo(symbol,
			ordinal,
			price.GetCompactBorrowPrice(),
			price.GetAvailableQuantity(),
#ifdef BORROW_PRICE_DISCOUNT
			price.GetDiscountFlag(),
#endif
//			price.GetCompactBeta(),
//			price.GetMargin(),
			price.GetHTB(),

			price.GetPmElRate(),
			price.GetPmEsRate(),
			price.GetPmHlRate(),
			price.GetPmHsRate(),
			price.GetElRate(),
			price.GetEsRate(),
			price.GetHlRate(),
			price.GetHsRate(),
//			price.GetFedReq(),
//			price.GetAssetType(),
//			price.isMarginable(),
//			price.GetSecType(),
//			price.GetStatus(),

			TM_EQUITY_BORROW_PRICE,
			sizeof(TMsgEquityBorrowPrice))
	{
	}
	TMsgEquityBorrowPrice(const unsigned __int64& symbol, const unsigned char& ordinal, const StockLoanInfo& price):
		TMsgSymbolOrdinalStockLoanInfo(symbol,
			ordinal,
			price.GetCompactBorrowPrice(),
			price.GetAvailableQuantity(),
#ifdef BORROW_PRICE_DISCOUNT
			price.GetDiscountFlag(),
#endif
//			price.GetCompactBeta(),
//			price.GetMargin(),
			price.GetHTB(),

			price.GetPmElRate(),
			price.GetPmEsRate(),
			price.GetPmHlRate(),
			price.GetPmHsRate(),
			price.GetElRate(),
			price.GetEsRate(),
			price.GetHlRate(),
			price.GetHsRate(),
//			price.GetFedReq(),
//			price.GetAssetType(),
//			price.isMarginable(),
//			price.GetSecType(),
//			price.GetStatus(),

			TM_EQUITY_BORROW_PRICE,
			sizeof(TMsgEquityBorrowPrice))
	{
	}
};

class TMsgPositionBorrowPrice : public TMsgSymbolOrdinalStockLoanInfo
{
public:
	TMsgPositionBorrowPrice(const char* const& accountId, const char* const& symbol, const unsigned char& ordinal, const StockLoanInfo& price):
		TMsgSymbolOrdinalStockLoanInfo(symbol,
			ordinal,
			price.GetCompactBorrowPrice(),
			price.GetAvailableQuantity(),
#ifdef BORROW_PRICE_DISCOUNT
			price.GetDiscountFlag(),
#endif
//			price.GetCompactBeta(),
//			price.GetMargin(),
			price.GetHTB(),

			price.GetPmElRate(),
			price.GetPmEsRate(),
			price.GetPmHlRate(),
			price.GetPmHsRate(),
			price.GetElRate(),
			price.GetEsRate(),
			price.GetHlRate(),
			price.GetHsRate(),
//			price.GetFedReq(),
//			price.GetAssetType(),
//			price.isMarginable(),
//			price.GetSecType(),
//			price.GetStatus(),

			TM_POSITION_BORROW_PRICE,
			sizeof(TMsgPositionBorrowPrice))
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountId, '\0', true);
	}
	TMsgPositionBorrowPrice(const char* const& accountId, const unsigned __int64& symbol, const unsigned char& ordinal, const StockLoanInfo& price):
		TMsgSymbolOrdinalStockLoanInfo(symbol,
			ordinal,
			price.GetCompactBorrowPrice(),
			price.GetAvailableQuantity(),
#ifdef BORROW_PRICE_DISCOUNT
			price.GetDiscountFlag(),
#endif
//			price.GetCompactBeta(),
//			price.GetMargin(),
			price.GetHTB(),

			price.GetPmElRate(),
			price.GetPmEsRate(),
			price.GetPmHlRate(),
			price.GetPmHsRate(),
			price.GetElRate(),
			price.GetEsRate(),
			price.GetHlRate(),
			price.GetHsRate(),
//			price.GetFedReq(),
//			price.GetAssetType(),
//			price.isMarginable(),
//			price.GetSecType(),
//			price.GetStatus(),

			TM_POSITION_BORROW_PRICE,
			sizeof(TMsgPositionBorrowPrice))
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountId, '\0', true);
	}
	char m_accountId[MAX_ACCOUNT_SIZE];
};

class TMsgPositionHtb : public TMsgSymbolOrdinalHtb
{
public:
	TMsgPositionHtb(const char* const& accountId, const char* const& symbol, const unsigned char& ordinal, const unsigned char& htb):
		TMsgSymbolOrdinalHtb(symbol, ordinal, htb, TM_POSITION_HTB, sizeof(TMsgPositionHtb))
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountId, '\0', true);
	}
	TMsgPositionHtb(const char* const& accountId, const unsigned __int64& symbol, const unsigned char& ordinal, const unsigned char& htb):
		TMsgSymbolOrdinalHtb(symbol, ordinal, htb, TM_POSITION_HTB, sizeof(TMsgPositionHtb))
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountId, '\0', true);
	}
	char m_accountId[MAX_ACCOUNT_SIZE];
};
////////

enum InventoryNotify : unsigned char
{
	IN_NONE,
	IN_NOTIFY,
	IN_NOTIFY_AND_LEAVE,
};

class InventoryNode
{
public:
	InventoryNode(const unsigned __int64& symbol,// = 0,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,// = 0,
		const unsigned char& suffix,// = 0,
//		const unsigned char& securityType = 0,
//		const unsigned int& contractSize,// = 0,
#endif
		const bool& inventoryFloating,// = false,
		const int& inventorySize,// = 0,
		const Price& inventoryCost):// = Price::priceZero):
		m_symbol(symbol),
#ifndef TAKION_NO_OPTIONS
		m_optionBlock(optionBlock),
//		m_contractSize(contractSize),
		m_suffix(suffix),
//		m_securityType(securityType),
#endif
		m_inventoryFloating(inventoryFloating),
		m_inventorySize(inventorySize),
		m_inventoryCost(inventoryCost)
	{
	}
	InventoryNode():// = Price::priceZero):
		m_symbol(0),
#ifndef TAKION_NO_OPTIONS
		m_optionBlock(0),
//		m_contractSize(0),
		m_suffix(0),
//		m_securityType(securityType),
#endif
		m_inventoryFloating(false),
		m_inventorySize(0)
//		m_inventoryCost(inventoryCost)
	{
	}
	unsigned __int64 m_symbol;
#ifndef TAKION_NO_OPTIONS
	unsigned __int64 m_optionBlock;
//	unsigned int m_contractSize;
	unsigned char m_suffix;
//	unsigned char m_securityType;
#endif
	bool m_inventoryFloating;
	int m_inventorySize;
	Price m_inventoryCost;
};

class TMsgInventory : public TMsgAccountObject
{
public:
	TMsgInventory(const char* const& accountName = "",
		const unsigned char& notifyLayout = 0,
		const unsigned char& securityTypeHidden = 0,
		const bool allPositions = false,
		const int& size = 0,
		const unsigned short& nodes = 0):
		TMsgAccountObject(accountName, TM_ACCOUNT_COMMAND_INVENTORY, sizeof(TMsgInventory) + nodes * sizeof(InventoryNode)),
		m_notifyLayout(notifyLayout),
		m_securityTypeHidden(securityTypeHidden),
		m_allPositions(allPositions),
		m_size(size)
	{
	}
	unsigned char m_notifyLayout;
	unsigned char m_securityTypeHidden;
	bool m_allPositions;
//	bool m_remove;//has a meaning only if it is applied to the whole account - no InventoryNode's follow.
	int m_size;//has a meaning only if it is applied to the whole account - no InventoryNode's follow.
// Followed by InventoryNode's.
};

class TMsgPositionCost : public TMsgAccountPositionObject
{
public:
	TMsgPositionCost(const char* const& accountName = "", const unsigned __int64& symbol = 0,//const char* symbol,
		const Price& cost = Price::priceZero
//		unsigned char securityType
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& optionBlock = 0
		,const unsigned char& securityType = 0
#endif
		):
		TMsgAccountPositionObject(accountName, symbol,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
			securityType,
#endif
			TM_POSITION_COST, sizeof(TMsgPositionCost)),
		m_price(cost)
	{
	}
	Price m_price;
};


class TMsgStockResetImbalances : public TMessageSymbol
{
public:
	TMsgStockResetImbalances(const char* const& symbol):TMessageSymbol(symbol, TM_STOCK_RESET_IMBALANCES, sizeof(TMsgStockResetImbalances)){}
	TMsgStockResetImbalances(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_STOCK_RESET_IMBALANCES, sizeof(TMsgStockResetImbalances)){}
};

class TMsgEquityResetImbalances : public TMessageSymbol
{
public:
	TMsgEquityResetImbalances(const char* const& symbol):TMessageSymbol(symbol, TM_EQUITY_RESET_IMBALANCES, sizeof(TMsgEquityResetImbalances)){}
	TMsgEquityResetImbalances(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_EQUITY_RESET_IMBALANCES, sizeof(TMsgEquityResetImbalances)){}
};


class TMessageChartLoaded : public TMessageSymbol
{
public:
	bool m_chartReloaded;
protected:
	TMessageChartLoaded(const unsigned __int64& symbol, const bool& chartReloaded, const unsigned short& type, const unsigned short& length):
		TMessageSymbol(symbol, type, length),
		m_chartReloaded(chartReloaded)
	{
	}
};

class TMsgEquityChartLoaded : public TMessageChartLoaded
{
public:
	TMsgEquityChartLoaded(const unsigned __int64& symbol, const bool& chartReloaded):
		TMessageChartLoaded(symbol, chartReloaded, TM_EQUITY_CHART_LOADED, sizeof(TMsgEquityChartLoaded))
	{
	}
};

class TMessageSymbolRequest : public TMessageSymbol
{
public:
	unsigned int m_requestId;
protected:
	TMessageSymbolRequest(const char* const& symbol,
		const unsigned int& requestId,
		const unsigned short& type,
		const unsigned short& length):
		TMessageSymbol(symbol, type, length),
		m_requestId(requestId)
	{
	}
	TMessageSymbolRequest(const unsigned __int64& symbol,
		const unsigned int& requestId,
		const unsigned short& type,
		const unsigned short& length):
		TMessageSymbol(symbol, type, length),
		m_requestId(requestId)
	{
	}
};

/*
class TMsgSymbolRequestDone : public TMessageSymbol
{
public:
	unsigned int m_requestId;
	bool m_failed;
protected:
	TMsgSymbolRequestDone(const char* const& symbol, const unsigned int& requestId, const bool& failed, const unsigned short& type, const unsigned short& length):TMessageSymbol(symbol, type, length), m_requestId(requestId), m_failed(failed){}
	TMsgSymbolRequestDone(const unsigned __int64& symbol, const unsigned int& requestId, const bool& failed, const unsigned short& type, const unsigned short& length):TMessageSymbol(symbol, type, length), m_requestId(requestId), m_failed(failed){}
};
*/
enum StockRefreshSteps : unsigned char
{
	SRS_DESCRIPTION = 1 << 0,
	SRS_ATTRIBUTES = 1 << 1,
	SRS_LEVEL1 = 1 << 2,
	SRS_LEVEL2 = 1 << 3,
	SRS_ADDITIONAL = 1 << 4,
	SRS_PRINTS = 1 << 5,
};

enum StockRefreshStatus : unsigned char
{
	REFRESH_EndOfBlock		= 0x20,
	REFRESH_EndOfRefresh	= 0x40,
	REFRESH_RefreshFailed	= 0x80,
};

class TMsgRespRefreshSymbol : public Message
{
public:
	TMsgRespRefreshSymbol(const unsigned short& dataSize = 0,
		const unsigned int& requestId = 0,
		const char* const& symbol = "",
		const unsigned char& steps = 0,
		const unsigned char& flags = 0,
		const unsigned char& bookID = 0,
		const char& marketStatus = 0):
		Message(M_RESP_REFRESH_SYMBOL, dataSize),
		m_requestID(requestId),
		m_steps(steps),
		m_flags(flags),
		m_bookID(bookID),
		m_marketStatus(marketStatus)
	{
		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}
	unsigned int	m_requestID;
	Symbol			m_symbol;
	unsigned char	m_steps;
	unsigned char	m_flags;
	unsigned char	m_bookID;
	char m_marketStatus;
};

class TMsgSnapshot : public TMessageTimeSymbol
{
public:
	TMsgSnapshot(const char* const& symbol,
		const unsigned int& time = 0,

		const unsigned int& bidDollar = 0,
		const unsigned int& bidFraction = 0,
		const unsigned int& askDollar = 0,
		const unsigned int& askFraction = 0,
/*
		const unsigned int& lastDollar = 0,
		const unsigned int& lastFraction = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0,
		const unsigned __int64& volume = 0,
*/
		const unsigned long& bidSize = 0,
		const unsigned long& askSize = 0,
//		const unsigned long& lastSize = 0,
//		const unsigned int& lastTime = 0,

		const char& bidMarketCenter = 0,
		const char& askMarketCenter = 0,
//		const char& lastMarketCenter = 0,
		const char& quoteCondition = 0,

		const unsigned char& quoteNodeSize = 0,
//		const unsigned char& printNodeSize = 0,
		const unsigned char& bidQuoteCount = 0,
		const unsigned char& askQuoteCount = 0):
//		const unsigned char& printCount = 0):

		TMessageTimeSymbol(symbol, time, M_SNAPSHOT, sizeof(TMsgSnapshot) + ((unsigned short)bidQuoteCount + (unsigned short)askQuoteCount) * quoteNodeSize),// + (unsigned short)printCount * printNodeSize),

		m_bidDollar(bidDollar),
		m_bidFraction(bidFraction),
		m_askDollar(askDollar),
		m_askFraction(askFraction),
/*
		m_lastDollar(lastDollar),
		m_lastFraction(lastFraction),
		m_lowDollar(lowDollar),
		m_lowFraction(lowFraction),
		m_highDollar(highDollar),
		m_highFraction(highFraction),
		m_volume(volume),
*/
		m_bidSize(bidSize),
		m_askSize(askSize),
//		m_lastSize(lastSize),
//		m_lastTime(lastTime),

		m_bidMarketCenter(bidMarketCenter),
		m_askMarketCenter(askMarketCenter),
//		m_lastMarketCenter(lastMarketCenter),
		m_quoteCondition(quoteCondition),

		m_quoteNodeSize(quoteNodeSize),
//		m_printNodeSize(printNodeSize),
		m_bidQuoteCount(bidQuoteCount),
		m_askQuoteCount(askQuoteCount),
//		m_printCount(printCount),
		m_reserved1(0),
		m_quotesOffset(sizeof(TMsgSnapshot))
	{
	}

//	unsigned int					m_time;
//	Symbol							m_symbol;

	unsigned int m_bidDollar;
	unsigned int m_bidFraction;
	unsigned int m_askDollar;
	unsigned int m_askFraction;
/*
	unsigned int m_lastDollar;
	unsigned int m_lastFraction;
	unsigned int m_lowDollar;
	unsigned int m_lowFraction;
	unsigned int m_highDollar;
	unsigned int m_highFraction;

	unsigned __int64 m_volume;
*/
	unsigned long m_bidSize;
	unsigned long m_askSize;
//	unsigned long m_lastSize;
//	unsigned int m_lastTime;

	char m_bidMarketCenter;
	char m_askMarketCenter;
//	char m_lastMarketCenter;
	char m_quoteCondition;

	unsigned char m_quoteNodeSize;//BYTE
//	unsigned char m_printNodeSize;//BYTE
	unsigned char m_bidQuoteCount;//BYTE
	unsigned char m_askQuoteCount;//BYTE
//	unsigned char m_printCount;

	unsigned char m_reserved1;//char
	unsigned char m_quotesOffset;//uint16_t
};

class TMsgIndexValue : public TMessageSymbol
{
public:
	TMsgIndexValue(const char* const& symbol = "",
		const int& whole = 0,
		const int& fraction = 0):
		TMessageSymbol(symbol, M_INDEX, sizeof(TMsgIndexValue)),
		m_whole(whole),
		m_fraction(fraction)
	{
	}
	int m_whole;
	int m_fraction;
};

class TMsgReqRefreshIndex : public TMessageSymbol
{
public:
	TMsgReqRefreshIndex(const char* const& symbol = "",
		const unsigned char& flags = SubscribeSymbol,
		const unsigned char& blockSize = 1,
		const unsigned int& requestID = 0):
		TMessageSymbol(symbol, M_REQ_REFRESH_INDEX, sizeof(TMsgReqRefreshIndex)),
		m_flags(flags),
		m_blockSize(blockSize),
		m_requestID(requestID)
	{
	}
    unsigned char m_flags;
    unsigned char m_blockSize;
    unsigned int m_requestID;
};

class TMsgRespRefreshIndex : public TMessageRequest
{
public:
	TMsgRespRefreshIndex(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const unsigned char& steps = 0,
		const unsigned char& flags = 0,
		const unsigned short& dataSize = 0):
		TMessageRequest(requestId, M_RESP_REFRESH_INDEX, dataSize),
//		m_requestID(requestId),
		m_steps(steps),
		m_flags(flags)
	{
		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}

//	unsigned int m_requestID;
	Symbol m_symbol;
	unsigned char m_steps;
	unsigned char m_flags;
};

class TMsgReqIndexChart : public TMessageSymbolRequest//TMessageSymbol
{
public:
	TMsgReqIndexChart(const char* const& symbol, const unsigned int& requestId = 0):
		TMessageSymbolRequest(symbol, requestId, M_REQ_INDEX_CHART, sizeof(TMsgReqIndexChart))//, m_requestId(requestId)
	{
	}
//	unsigned int m_requestId;
};

class TMessageRespChartBase : public TMessageSymbolRequest//TMessageSymbol
{
public:
//	unsigned int m_requestId;
	unsigned short m_minute;
	unsigned char m_tickSize;
	unsigned char m_done;
protected:
	TMessageRespChartBase(const char* const& symbol,
		const unsigned int& requestId,
		const unsigned short& minute,
		const unsigned char& tickSize,
		const unsigned short& ticks,
		const bool& done,
		const unsigned short& type,
		const unsigned short& length):
		TMessageSymbolRequest(symbol, requestId, type, length + ticks * tickSize),
//		m_requestId(requestId),
		m_minute(minute),
		m_tickSize(tickSize),
		m_done(done)
	{
	}
};

class MsgIndexChartPoint
{
public:
	SignedPrice m_firstPrice;
	SignedPrice m_lastPrice;
	SignedPrice m_highPrice;
	SignedPrice m_lowPrice;
};

class TMsgRespIndexChart : public TMessageRespChartBase//TMessageSymbolRequest//TMessageSymbol
{
public:
	TMsgRespIndexChart(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const unsigned short& minute = 0,
		const unsigned char& tickSize = sizeof(MsgIndexChartPoint),
		const unsigned short& ticks = 0,
		const bool& done = false):
		TMessageRespChartBase(symbol, requestId, minute, tickSize, ticks, done, M_RESP_INDEX_CHART, sizeof(TMsgRespIndexChart))
	{
	}
};

class TMsgStockDirectory : public TMessageTimeSymbol
{
public:
	TMsgStockDirectory(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned int& roundLotSize = 0,
		const bool& roundLotsOnly = false,
		const char& marketCategory = '\0',
		const char& financialStatusIndicator = '\0'):
		TMessageTimeSymbol(symbol, time, M_STOCK_DIRECTORY, sizeof(TMsgStockDirectory)),
		m_roundLotSize(roundLotSize),
		m_roundLotsOnly(roundLotsOnly),
		m_marketCategory(marketCategory),
		m_financialStatusIndicator(financialStatusIndicator)
	{
	}
	unsigned int m_roundLotSize;
	bool m_roundLotsOnly;
	char m_marketCategory;
	char m_financialStatusIndicator;
};

class TMsgStockTradingActionBase : public TMessageTimeSymbol
{
public:
	char m_tradingState;
	char m_tradingActionReason[4];
protected:
	TMsgStockTradingActionBase(const char* const& symbol,
		const unsigned int& time,
		const char& tradingState,
		const unsigned int& tradingActionReason,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_tradingState(tradingState)
	{
		*(unsigned int*)m_tradingActionReason = tradingActionReason;
	}
};

class TMsgStockTradingAction : public TMsgStockTradingActionBase
{
public:
	TMsgStockTradingAction(const char* const& symbol = "",
		const unsigned int& time = 0,
		const char& tradingState = 0,
		const unsigned int& tradingActionReason = 0):
		TMsgStockTradingActionBase(symbol,
			time,
			tradingState,
			tradingActionReason,
			M_STOCK_TRADING_ACTION,
			sizeof(TMsgStockTradingAction))
	{
	}
};

class TMsgMsStockTradingAction : public TMsgStockTradingActionBase
{
public:
	TMsgMsStockTradingAction(const char* const& symbol = "",
		const unsigned int& time = 0,
		const char& tradingState = 0,
		const unsigned int& tradingActionReason = 0):
		TMsgStockTradingActionBase(symbol,
			time,
			tradingState,
			tradingActionReason,
			M_MS_STOCK_TRADING_ACTION,
			sizeof(TMsgMsStockTradingAction))
	{
	}
};
/*Use TMessageSymbolRequest
class ReqChartBase : public TMessageSymbol
{
public:
	unsigned int m_requestId;
	ReqChartBase(const char* const& symbol, const unsigned short& type, const unsigned short& length, const unsigned int& requestId = 0):TMessageSymbol(symbol, type, length), m_requestId(requestId){}
};
*/
class TMsgReqChart : public TMessageSymbolRequest//ReqChartBase
{
public:
	TMsgReqChart(const char* const& symbol = "", const unsigned int& requestId = 0):
//		ReqChartBase(symbol, M_REQ_CHART, sizeof(TMsgReqChart), requestId)
		TMessageSymbolRequest(symbol, requestId, M_REQ_CHART, sizeof(TMsgReqChart))
	{
	}
};

class TSmMsgReqChart : public TMessageRequest
{
public:
	TSmMsgReqChart(const unsigned short& symbol = 0, const unsigned int& requestId = 0):
		TMessageRequest(requestId, SM_REQ_CHART, sizeof(TSmMsgReqChart)),
//		m_requestId(requestId),
		m_symbol(symbol)
	{
	}
//	unsigned int m_requestId;
	unsigned short m_symbol;
};

class TMsgRespChart : public TMessageRespChartBase
{
public:
	TMsgRespChart(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const unsigned short& minute = 0,
		const unsigned char& tickSize = sizeof(MsgChartPoint),
		const unsigned short& ticks = 0,
		const bool& done = false):
		TMessageRespChartBase(symbol, requestId, minute, tickSize, ticks, done, M_RESP_CHART, sizeof(TMsgRespChart))
	{
	}
};

class TMsgNewTick : public TMessageSymbol
{
public:
	unsigned short m_minute;
protected:
	TMsgNewTick(const char* const& symbol, const unsigned short& minute, const unsigned short& type, const unsigned short& size):
		TMessageSymbol(symbol, type, size),
		m_minute(minute)
	{
	}
};

class TMsgEquityNewTick : public TMsgNewTick
{
public:
	TMsgEquityNewTick(const char* const& symbol = "", const unsigned short& minute = 0):
		TMsgNewTick(symbol, minute, M_NEW_TICK, sizeof(TMsgEquityNewTick))
	{
	}
};

class TMsgIndexNewTick : public TMsgNewTick
{
public:
	TMsgIndexNewTick(const char* const& symbol = "", const unsigned short& minute = 0):
		TMsgNewTick(symbol, minute, M_INDEX_NEW_TICK, sizeof(TMsgIndexNewTick))
	{
	}
};

class TMsgTickCorrection : public TMessageSymbol
{
public:
	TMsgTickCorrection(const char* const& symbol = "",
		const unsigned int& volume = 0,
		const unsigned int& moneyDollars = 0,
		const unsigned int& moneyFraction = 0,
		const unsigned int& first = 0,
		const unsigned int& last = 0,
		const unsigned int& high = 0,
		const unsigned int& low = 0,
		const unsigned short& minute = 0):
		TMessageSymbol(symbol, M_TICK_CORRECTION, sizeof(TMsgTickCorrection)),
		m_volume(volume),
		m_moneyDollars(moneyDollars),
		m_moneyFraction(moneyFraction),
		m_first(first),
		m_last(last),
		m_high(high),
		m_low(low),
		m_minute(minute)
	{
	}
	unsigned int m_volume;
	unsigned int m_moneyDollars;
	unsigned int m_moneyFraction;
	unsigned int m_first;
	unsigned int m_last;
	unsigned int m_high;
	unsigned int m_low;
	unsigned short m_minute;
};

class TMsgImbalance : public TMessageSymbol
{
public:
	TMsgImbalance(const char* const& symbol = "",
		const unsigned int& farPriceDollar = 0,
		const unsigned int& farPriceFraction = 0,
		const unsigned int& nearPriceDollar = 0,
		const unsigned int& nearPriceFraction = 0,
		const unsigned int& currentReferencePriceDollar = 0,
		const unsigned int& currentReferencePriceFraction = 0,
		const unsigned int& pairedShares = 0,
		const unsigned int& imbalanceShares = 0,
		const unsigned int& marketImbalanceShares = 0,
		const unsigned int& time = 0,
		const unsigned int& auctionTime = 0,
		const char& imbalanceDirection = 0,
		const char& crossType = 0,
		const char& priceVariationIndicator = 0,
		const unsigned char& bookId = 0,
		const bool& regulatory = false,
		const bool& freezeStatus = false):
	
		TMessageSymbol(symbol, M_STOCK_IMBALANCE_INDICATOR, sizeof(TMsgImbalance)),
		m_farPriceDollar(farPriceDollar),
		m_farPriceFraction(farPriceFraction),
		m_nearPriceDollar(nearPriceDollar),
		m_nearPriceFraction(nearPriceFraction),
		m_currentReferencePriceDollar(currentReferencePriceDollar),
		m_currentReferencePriceFraction(currentReferencePriceFraction),
		m_pairedShares(pairedShares),
		m_imbalanceShares(imbalanceShares),
		m_marketImbalanceShares(marketImbalanceShares),
		m_time(time),
		m_auctionTime(auctionTime),
		m_imbalanceDirection(imbalanceDirection),
		m_crossType(crossType),
		m_priceVariationIndicator(priceVariationIndicator),
		m_bookID(bookId),
		m_regulatoryImbalance_StockOpen(regulatory ? 1 : 0),
		m_freezeStatus(freezeStatus ? 1 : 0)
	{
	}
	unsigned int m_farPriceDollar;
	unsigned int m_farPriceFraction;
	unsigned int m_nearPriceDollar;
	unsigned int m_nearPriceFraction;
	unsigned int m_currentReferencePriceDollar;
	unsigned int m_currentReferencePriceFraction;
	unsigned int m_pairedShares;
	unsigned int m_imbalanceShares;
	unsigned int m_marketImbalanceShares;
	unsigned int m_time;
	unsigned int m_auctionTime;
	char m_imbalanceDirection;
	char m_crossType;
	char m_priceVariationIndicator;
	unsigned char m_bookID : 4;
	unsigned char m_regulatoryImbalance_StockOpen : 1;
	unsigned char m_freezeStatus : 1;
};

class TMsgBookNewQuote : public TMessageSymbol
{
public:
	TMsgBookNewQuote(const char* const& symbol = "",
		const unsigned char& side = Buy,
		const unsigned __int64& referenceNumber = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned int& size = 0,
		const unsigned int& mmid = 0,
		const unsigned int& millisecond = 0,
		const unsigned char& bookID = 0,//	: 8;
		const unsigned char& quoteCondition = 0,//	: 8;
		const unsigned short& flags = 0)://		: 24;
		TMessageSymbol(symbol, M_BOOK_NEW_QUOTE, sizeof(TMsgBookNewQuote)),
		m_side(side),
		m_quote(referenceNumber, priceDollars, priceFraction, size, mmid, millisecond, bookID, quoteCondition, flags)
	{
	}
	unsigned char m_side;
	MsgQuote m_quote;
};

class TMsgBookModifyQuote : public TMessageSymbol
{
public:
	TMsgBookModifyQuote(const char* const& symbol = "",
		const unsigned char& side = Buy,
		const unsigned __int64& referenceNumber = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned int& size = 0,
		const unsigned int& mmid = 0,
		const unsigned int& millisecond = 0,
		const unsigned char& bookID = 0,//	: 8;
		const unsigned char& quoteCondition = 0,//	: 8;
		const unsigned short& flags = 0)://		: 24;
		TMessageSymbol(symbol, M_BOOK_MODIFY_QUOTE, sizeof(TMsgBookModifyQuote)),
		m_side(side),
		m_quote(referenceNumber, priceDollars, priceFraction, size, mmid, millisecond, bookID, quoteCondition, flags)
	{
	}
	unsigned char m_side;
	MsgQuote m_quote;
};

class TMsgBookDeleteQuote : public TMessageTimeSymbol
{
public:
	TMsgBookDeleteQuote(const char* const& symbol = "",
		const unsigned int& millisecond = 0,
		const unsigned __int64& referenceNumber = 0,
		const unsigned char& side = Buy,
		const unsigned char& bookID = 0):
		TMessageTimeSymbol(symbol, millisecond, M_BOOK_DELETE_QUOTE, sizeof(TMsgBookDeleteQuote)),
		m_referenceNumber(referenceNumber),
		m_side(side),
		m_bookID(bookID)
	{
	}
	unsigned __int64	m_referenceNumber;
	unsigned char		m_side;
	unsigned char		m_bookID;
};

class TMsgBookOrderExecuted : public TMessageTimeSymbol
{
public:
	TMsgBookOrderExecuted(const char* const& symbol = "",
		const unsigned int& millisecond = 0,
		const unsigned __int64& referenceNumber = 0,
		const unsigned __int64& matchNumber = 0,
		const unsigned int& shares = 0,
		const unsigned char& side = Buy,
		const unsigned char& bookID = 0):
		TMessageTimeSymbol(symbol, millisecond, M_BOOK_ORDER_EXECUTED, sizeof(TMsgBookOrderExecuted)),
		m_referenceNumber(referenceNumber),
		m_matchNumber(matchNumber),
		m_shares(shares),
		m_side(side),
		m_bookID(bookID)
	{
	}
	unsigned __int64 m_referenceNumber;
	unsigned __int64 m_matchNumber;
	unsigned int m_shares;
	unsigned char m_side;
	unsigned char m_bookID;
};

class TMsgBookOrderExecutedWithPrice : public TMessageTimeSymbol
{
public:
	TMsgBookOrderExecutedWithPrice(const char* const& symbol = "",
		const unsigned int& millisecond = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned __int64& referenceNumber = 0,
		const unsigned __int64& matchNumber = 0,
		const unsigned int& shares = 0,
		const unsigned int& remainingShares = 0,
		const unsigned char& side = Buy,
		const unsigned char& bookID = 0,
		const bool& bPrintable = false):
		TMessageTimeSymbol(symbol, millisecond, M_BOOK_ORDER_EXECUTED_WITH_PRICE, sizeof(TMsgBookOrderExecutedWithPrice)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_referenceNumber(referenceNumber),
		m_matchNumber(matchNumber),
		m_shares(shares),
		m_remainingShares(remainingShares),
		m_side(side),
		m_bookID(bookID),
		m_bPrintable(bPrintable)
	{
	}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned __int64 m_referenceNumber;
	unsigned __int64 m_matchNumber;
	unsigned int m_shares;
	unsigned int m_remainingShares;
	unsigned char m_side;
	unsigned char m_bookID;
	bool m_bPrintable;
};

class TMsgBookTrade : public TMessageTimeSymbol
{
public:
	TMsgBookTrade(const char* const& symbol = "",
		const unsigned int& millisecond = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned __int64& matchNumber = 0,
		const unsigned int& shares = 0,
		const unsigned char& side = Buy,
		const unsigned char& bookID = 0):
		TMessageTimeSymbol(symbol, millisecond, M_BOOK_TRADE, sizeof(TMsgBookTrade)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_matchNumber(matchNumber),
		m_shares(shares),
		m_side(side),
		m_bookID(bookID)
	{
	}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
//	unsigned __int64 m_referenceNumber;//??
	unsigned __int64 m_matchNumber;
	unsigned int m_shares;
	unsigned char m_side;
	unsigned char m_bookID;
};

class TMsgBookCrossTrade : public TMessageTimeSymbol
{
public:
	TMsgBookCrossTrade(const char* const& symbol = "",
		const unsigned int& millisecond = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned __int64& matchNumber = 0,
		const unsigned int& shares = 0,
		const char& crossType = 0,
		const unsigned char& bookID = 0):
		TMessageTimeSymbol(symbol, millisecond, M_BOOK_CROSS_TRADE, sizeof(TMsgBookCrossTrade)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_matchNumber(matchNumber),
		m_shares(shares),
		m_crossType(crossType),
		m_bookID(bookID)
	{
	}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned __int64 m_matchNumber;
	unsigned int m_shares;
	char m_crossType;
	unsigned char m_bookID;
};

class TMsgBookOrderCanceled : public TMessageTimeSymbol
{
public:
	TMsgBookOrderCanceled(const char* const& symbol = "",
		const unsigned int& millisecond = 0,
		const unsigned __int64& referenceNumber = 0,
		const unsigned int& shares = 0,
		const unsigned char& side = Buy,
		const unsigned char& bookID = 0):
		TMessageTimeSymbol(symbol, millisecond, M_BOOK_ORDER_CANCELED, sizeof(TMsgBookOrderCanceled)),
		m_referenceNumber(referenceNumber),
		m_shares(shares),
		m_side(side),
		m_bookID(bookID)
	{
	}
	unsigned __int64 m_referenceNumber;
	unsigned int m_shares;
	unsigned char m_side;
	unsigned char m_bookID;
};

class TMsgResetBook: public Message
{
public:
	TMsgResetBook(const unsigned char& bookId = AllBooks):Message(M_RESET_BOOK, sizeof(TMsgResetBook)),m_bookId(bookId){}
    unsigned char m_bookId;
};

class TMsgResetSymbol: public TMessageSymbol
{
public:
	TMsgResetSymbol(const char* const& symbol, const unsigned char& bookId = AllBooks):TMessageSymbol(symbol, M_RESET_SYMBOL, sizeof(TMsgResetSymbol)), m_bookId(bookId){}
	TMsgResetSymbol(const unsigned __int64& symbol = 0, const unsigned char& bookId = AllBooks):TMessageSymbol(symbol, M_RESET_SYMBOL, sizeof(TMsgResetSymbol)), m_bookId(bookId){}
    unsigned char m_bookId;
};

class TMsgLevel1: public TMessageTimeSymbol
{
public:
	TMsgLevel1(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned int& bidDollars = 0,
		const unsigned int& bidFraction = 0,
		const unsigned int& askDollars = 0,
		const unsigned int& askFraction = 0,
		const unsigned int& bidSize = 0,
		const unsigned int& askSize = 0,
		const char& primaryListingMarket = 0,
		const char& bidMarketCenter = 0,
		const char& askMarketCenter = 0,
		const char& quoteCondition = 0):
		TMessageTimeSymbol(symbol, time, M_LEVEL1, sizeof(TMsgLevel1)),
		m_bidDollars(bidDollars),
		m_bidFraction(bidFraction),
		m_askDollars(askDollars),
		m_askFraction(askFraction),
		m_bidSize(bidSize),
		m_askSize(askSize),
		m_primaryListingMarket(primaryListingMarket),
		m_bidMarketCenter(bidMarketCenter),
		m_askMarketCenter(askMarketCenter),
		m_quoteCondition(quoteCondition)
	{
	}
	unsigned int m_bidDollars;
	unsigned int m_bidFraction;
	unsigned int m_askDollars;
	unsigned int m_askFraction;
	unsigned int m_bidSize;
	unsigned int m_askSize;
	char m_primaryListingMarket;
	char m_bidMarketCenter;
	char m_askMarketCenter;
	char m_quoteCondition;
};

class TMsgTrade: public TMessageTimeSymbol
{
public:
	TMsgTrade(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned __int64& referenceNumber = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned int& size = 0,
		const char& saleCondition1 = 0,
		const char& saleCondition2 = 0,
		const char& saleCondition3 = 0,
		const char& saleCondition4 = 0,
		const char& marketCenterID = 0,
		const char& primaryListingMarket = 0,
		const unsigned char& flags = 0):
		TMessageTimeSymbol(symbol, time, M_TRADE_REPORT, sizeof(TMsgTrade)),
		m_referenceNumber(referenceNumber),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_size(size),
		m_marketCenterID(marketCenterID),
		m_primaryListingMarket(primaryListingMarket),
		m_flags(flags)
	{
		char* cursor = m_saleConditions;
		*cursor = saleCondition1;
		*++cursor = saleCondition2;
		*++cursor = saleCondition3;
		*++cursor = saleCondition4;
	}
	unsigned __int64 m_referenceNumber;
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_size;
	char m_saleConditions[4];
	char m_marketCenterID;
	char m_primaryListingMarket;
	unsigned char m_flags;
};

class TMsgMsTradeShort: public TMessageSymbol
{
public:
	TMsgMsTradeShort(const char* const& symbol = "",
		const unsigned int& price = 0,
		const unsigned short& size = 0,
		const char& saleCondition = 0,
		const char& marketCenter = 0):
		TMessageSymbol(symbol, M_MS_TRADE_REPORT_SHORT, sizeof(TMsgMsTradeShort)),
		m_price(price),
		m_size(size),
		m_saleCondition(saleCondition),
		m_marketCenterID(marketCenter)
	{
	}
	unsigned int m_price;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned short m_size;
	char m_saleCondition;
	char m_marketCenterID;
};

class TMsgMsTradeLong: public TMessageSymbol
{
public:
	TMsgMsTradeLong(const char* const& symbol = "",
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned int& size = 0,
		const unsigned int& saleCondition = 0,
		const char& marketCenter = 0):
		TMessageSymbol(symbol, M_MS_TRADE_REPORT_LONG, sizeof(TMsgMsTradeLong)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_size(size),
		m_marketCenterID(marketCenter)
	{
		*(unsigned int*)m_saleCondition = saleCondition;
	}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_size;
	char m_saleCondition[4];
	char m_marketCenterID;
};

class TMsgMsTradeLongInternal: public Message
{
public:
	TMsgMsTradeLongInternal(const unsigned int& bid,
		const unsigned int& ask,
		const unsigned int& priceDollars,
		const unsigned int& priceFraction,
		const unsigned int& size,
		const unsigned int& saleCondition,
		const char& marketCenter,
		const unsigned char& printFlags,
		const bool& priceApplicableToChart,
		const unsigned char& roundLot,
		const unsigned char& level1):
		Message(TM_MS_TRADE_LONG_INTERNAL, sizeof(TMsgMsTradeLongInternal)),
		m_l1Bid(bid),
		m_l1Ask(ask),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_size(size),
		m_marketCenterID(marketCenter),
		m_printFlags(printFlags),
		m_priceApplicableToChart(priceApplicableToChart),
		m_roundLot(roundLot),
		m_level1(level1)
	{
		*(unsigned int*)m_saleCondition = saleCondition;
	}
	unsigned int m_l1Bid;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned int m_l1Ask;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_size;
	char m_saleCondition[4];
	char m_marketCenterID;
	unsigned char m_printFlags;
	bool m_priceApplicableToChart;
	unsigned char m_roundLot;
	unsigned char m_level1;//TradeLevel1
};

class TMsgMsTradeShortInternal: public Message
{
public:
	TMsgMsTradeShortInternal(const unsigned int& bid,
		const unsigned int& ask,
		const unsigned int& price,
		const unsigned short& size,
		const char& saleCondition,
		const char& marketCenter,
		const unsigned char& printFlags,
		const bool& priceApplicableToChart,
		const unsigned char& roundLot,
		const unsigned char& level1):
		Message(TM_MS_TRADE_SHORT_INTERNAL, sizeof(TMsgMsTradeShortInternal)),
		m_l1Bid(bid),
		m_l1Ask(ask),
		m_price(price),
		m_size(size),
		m_saleCondition(saleCondition),
		m_marketCenterID(marketCenter),
		m_printFlags(printFlags),
		m_priceApplicableToChart(priceApplicableToChart),
		m_roundLot(roundLot),
		m_level1(level1)
	{
	}
	unsigned int m_l1Bid;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned int m_l1Ask;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned int m_price;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned short m_size;
	char m_saleCondition;
	char m_marketCenterID;
	unsigned char m_printFlags;
	bool m_priceApplicableToChart;
	unsigned char m_roundLot;
	unsigned char m_level1;
};

class HistoricalTrade
{
public:
	HistoricalTrade(const unsigned int& priceDollar,
		const unsigned int& priceFraction,
		const unsigned int& time,
		const unsigned int& size,
		const unsigned int& saleCondition,
		const char& marketCenter,
		const unsigned char& printFlags):
//		Message(TM_MS_TRADE_SHORT_INTERNAL, sizeof(TMsgMsTradeShortInternal)),
		m_priceDollar(priceDollar),
		m_priceFraction(priceFraction),
		m_time(time),
		m_size(size),
		m_marketCenterID(marketCenter),
		m_printFlags(printFlags)
	{
		*(unsigned int*)m_saleCondition = saleCondition;
	}
	unsigned int m_priceDollar;
	unsigned int m_priceFraction;
	unsigned int m_time;
	unsigned int m_size;
	char m_saleCondition[4];
	char m_marketCenterID;
	unsigned char m_printFlags;
};

class TMsgNewMinute: public Message
{
public:
	unsigned short m_minute;
protected:
	TMsgNewMinute(const unsigned short& minute, const unsigned short& type, const unsigned short& size): Message(type, size), m_minute(minute){}
};

class TMsgEquityNewMinute: public TMsgNewMinute
{
public:
	TMsgEquityNewMinute(const unsigned short& minute, const bool& fromServer):TMsgNewMinute(minute, TM_EQUITY_NEW_MINUTE, sizeof(TMsgEquityNewMinute)), m_fromServer(fromServer){}
	bool m_fromServer;
};

class TMsgEquityNewTimeFrame: public TMsgNewMinute
{
public:
	TMsgEquityNewTimeFrame(const unsigned short& timeFrame):TMsgNewMinute(timeFrame, TM_EQUITY_NEW_TIME_FRAME, sizeof(TMsgEquityNewTimeFrame)){}
//	unsigned int m_timeFrame;
};

class TMsgIndexNewMinute: public TMsgNewMinute
{
public:
	TMsgIndexNewMinute(const unsigned short& minute):TMsgNewMinute(minute, TM_INDEX_NEW_MINUTE, sizeof(TMsgIndexNewMinute)){}
};

class TMsgMsLevel1Short: public TMessageSymbol
{
public:
	TMsgMsLevel1Short(const char* const& symbol = "",
		const unsigned int& price = 0,
		const unsigned char& side = 0,
		const char& quoteCondition = 0):
		TMessageSymbol(symbol, M_MS_LEVEL1_SHORT, sizeof(TMsgMsLevel1Short)),
		m_price(price),
		m_side(side),
		m_quoteCondition(quoteCondition)
	{
	}
	unsigned int m_price;//18 bits for dollar and 14 bits for 4 digits of fraction
	unsigned char m_side;//'B' and 'S'
	char m_quoteCondition;
};

class TMsgMsLevel1Long: public TMessageSymbol
{
public:
	TMsgMsLevel1Long(const char* const& symbol = "",
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned char& side = 0,
		const char& quoteCondition = 0):
		TMessageSymbol(symbol, M_MS_LEVEL1_LONG, sizeof(TMsgMsLevel1Long)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_side(side),
		m_quoteCondition(quoteCondition)
	{
	}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned char m_side;//'B' and 'S'
	char m_quoteCondition;
};

class TMsgMsImbalanceLong : public TMessageSymbol
{
public:
	TMsgMsImbalanceLong(const char* const& symbol = "",
		const unsigned int& farPriceDollar = 0,
		const unsigned int& farPriceFraction = 0,
		const unsigned int& nearPriceDollar = 0,
		const unsigned int& nearPriceFraction = 0,
		const unsigned int& currentReferencePriceDollar = 0,
		const unsigned int& currentReferencePriceFraction = 0,
		const unsigned int& pairedShares = 0,
		const unsigned int& imbalanceShares = 0,
		const unsigned int& marketImbalanceShares = 0,
		const unsigned int& time = 0,
		const unsigned int& auctionTime = 0,
		const char& imbalanceDirection = 0,
		const char& crossType = 0,
		const char& priceVariationIndicator = 0,
		const unsigned char& bookId = 0,
		const bool& regulatory = false,
		const bool& freezeStatus = false):
	
		TMessageSymbol(symbol, M_MS_IMBALANCE_LONG, sizeof(TMsgMsImbalanceLong)),
		m_farPriceDollar(farPriceDollar),
		m_farPriceFraction(farPriceFraction),
		m_nearPriceDollar(nearPriceDollar),
		m_nearPriceFraction(nearPriceFraction),
		m_currentReferencePriceDollar(currentReferencePriceDollar),
		m_currentReferencePriceFraction(currentReferencePriceFraction),
		m_pairedShares(pairedShares),
		m_imbalanceShares(imbalanceShares),
		m_marketImbalanceShares(marketImbalanceShares),
		m_time(time),
		m_auctionTime(auctionTime),
		m_imbalanceDirection(imbalanceDirection),
		m_crossType(crossType),
		m_priceVariationIndicator(priceVariationIndicator),
		m_bookID(bookId),
		m_regulatoryImbalance_StockOpen(regulatory ? 1 : 0),
		m_freezeStatus(freezeStatus ? 1 : 0)
	{
	}
	unsigned int m_farPriceDollar;
	unsigned int m_farPriceFraction;
	unsigned int m_nearPriceDollar;
	unsigned int m_nearPriceFraction;
	unsigned int m_currentReferencePriceDollar;
	unsigned int m_currentReferencePriceFraction;
	unsigned int m_pairedShares;
	unsigned int m_imbalanceShares;
	unsigned int m_marketImbalanceShares;
	unsigned int m_time;
	unsigned int m_auctionTime;
	char m_imbalanceDirection;
	char m_crossType;
	char m_priceVariationIndicator;
	unsigned char m_bookID : 4;
	unsigned char m_regulatoryImbalance_StockOpen : 1;//for ARCA : 1 if market imbalance, 0 if non market imbalance
	unsigned char m_freezeStatus : 1;
};

class TMsgMsImbalanceShort : public TMessageSymbol
{
public:
	TMsgMsImbalanceShort(const char* const& symbol = "",
		const unsigned int& farPrice = 0,//18 bits for dollar and 14 bits for 4 digits of fraction
		const unsigned int& nearPrice = 0,//18 bits for dollar and 14 bits for 4 digits of fraction
		const unsigned int& currentReferencePrice = 0,//18 bits for dollar and 14 bits for 4 digits of fraction
		const unsigned int& pairedShares = 0,
		const unsigned int& imbalanceShares = 0,
		const unsigned int& marketImbalanceShares = 0,
		const unsigned int& time = 0,
		const unsigned int& auctionTime = 0,
		const char& imbalanceDirection = 0,
		const char& crossType = 0,
		const char& priceVariationIndicator = 0,
		const unsigned char& bookId = 0,
		const bool& regulatory = false,
		const bool& freezeStatus = false):
	
		TMessageSymbol(symbol, M_MS_IMBALANCE_SHORT, sizeof(TMsgMsImbalanceShort)),
		m_farPrice(farPrice),
		m_nearPrice(nearPrice),
		m_currentReferencePrice(currentReferencePrice),
		m_pairedShares(pairedShares),
		m_imbalanceShares(imbalanceShares),
		m_marketImbalanceShares(marketImbalanceShares),
		m_time(time),
		m_auctionTime(auctionTime),
		m_imbalanceDirection(imbalanceDirection),
		m_crossType(crossType),
		m_priceVariationIndicator(priceVariationIndicator),
		m_bookID(bookId),
		m_regulatoryImbalance_StockOpen(regulatory ? 1 : 0),//for ARCA : 1 if market imbalance, 0 if non market imbalance
		m_freezeStatus(freezeStatus ? 1 : 0)
	{
	}
	unsigned int m_farPrice;
	unsigned int m_nearPrice;
	unsigned int m_currentReferencePrice;
	unsigned int m_pairedShares;
	unsigned int m_imbalanceShares;
	unsigned int m_marketImbalanceShares;
	unsigned int m_time;
	unsigned int m_auctionTime;
	char m_imbalanceDirection;
	char m_crossType;
	char m_priceVariationIndicator;
	unsigned char m_bookID : 4;
	unsigned char m_regulatoryImbalance_StockOpen : 1;//for ARCA : 1 if market imbalance, 0 if non market imbalance
	unsigned char m_freezeStatus : 1;
};

class TMsgTradeErrorBase: public TMessageTimeSymbol
{
public:
	unsigned __int64 m_originalReferenceNumber;
	unsigned int m_originalPriceDollars;
	unsigned int m_originalPriceFraction;
	unsigned int m_originalSize;
	char m_originalSaleConditions[4];

	unsigned int m_lastPriceDollars;
	unsigned int m_lastPriceFraction;
	unsigned int m_highPriceDollars;
	unsigned int m_highPriceFraction;
	unsigned int m_lowPriceDollars;
	unsigned int m_lowPriceFraction;
	unsigned __int64 m_volume;

	char m_marketCenterID;
	char m_primaryListingMarket;
	unsigned char m_flags;
protected:
	TMsgTradeErrorBase(const char* const& symbol,
		const unsigned int& time,
		const unsigned __int64& originalReferenceNumber,
		const unsigned int& originalPriceDollars,
		const unsigned int& originalPriceFraction,
		const unsigned int& originalSize,
		const char& originalSaleCondition1,
		const char& originalSaleCondition2,
		const char& originalSaleCondition3,
		const char& originalSaleCondition4,

		const unsigned int& lastPriceDollars,
		const unsigned int& lastPriceFraction,
		const unsigned int& highPriceDollars,
		const unsigned int& highPriceFraction,
		const unsigned int& lowPriceDollars,
		const unsigned int& lowPriceFraction,
		const unsigned __int64& volume,

		const char& marketCenterID,
		const char& primaryListingMarket,
		const unsigned char& flags,

		const unsigned short& type,
		const unsigned short& length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_originalReferenceNumber(originalReferenceNumber),
		m_originalPriceDollars(originalPriceDollars),
		m_originalPriceFraction(originalPriceFraction),
		m_originalSize(originalSize),
		m_lastPriceDollars(lastPriceDollars),
		m_lastPriceFraction(lastPriceFraction),
		m_highPriceDollars(highPriceDollars),
		m_highPriceFraction(highPriceFraction),
		m_lowPriceDollars(lowPriceDollars),
		m_lowPriceFraction(lowPriceFraction),
		m_volume(volume),
		m_marketCenterID(marketCenterID),
		m_primaryListingMarket(primaryListingMarket),
		m_flags(flags)
	{
		char* cursor = m_originalSaleConditions;
		*cursor = originalSaleCondition1;
		*++cursor = originalSaleCondition2;
		*++cursor = originalSaleCondition3;
		*++cursor = originalSaleCondition4;
	}
};

class TMsgTradeError: public TMsgTradeErrorBase
{
public:
	TMsgTradeError(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned __int64& originalReferenceNumber = 0,
		const unsigned int& originalPriceDollars = 0,
		const unsigned int& originalPriceFraction = 0,
		const unsigned int& originalSize = 0,
		const char& originalSaleCondition1 = 0,
		const char& originalSaleCondition2 = 0,
		const char& originalSaleCondition3 = 0,
		const char& originalSaleCondition4 = 0,

		const unsigned int& lastPriceDollars = 0,
		const unsigned int& lastPriceFraction = 0,
		const unsigned int& highPriceDollars = 0,
		const unsigned int& highPriceFraction = 0,
		const unsigned int& lowPriceDollars = 0,
		const unsigned int& lowPriceFraction = 0,
		const unsigned __int64& volume = 0,

		const char& marketCenterID = 0,
		const char& primaryListingMarket = 0,
		const unsigned char& flags = 0):
		TMsgTradeErrorBase(symbol,
			time,
			originalReferenceNumber,
			originalPriceDollars,
			originalPriceFraction,
			originalSize,
			originalSaleCondition1,
			originalSaleCondition2,
			originalSaleCondition3,
			originalSaleCondition4,

			lastPriceDollars,
			lastPriceFraction,
			highPriceDollars,
			highPriceFraction,
			lowPriceDollars,
			lowPriceFraction,
			volume,

			marketCenterID,
			primaryListingMarket,
			flags,
			M_TRADE_CANCEL_ERROR,
			sizeof(TMsgTradeError))
	{
	}
};

class TMsgMsTradeError: public TMsgTradeErrorBase
{
public:
	TMsgMsTradeError(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned __int64& originalReferenceNumber = 0,
		const unsigned int& originalPriceDollars = 0,
		const unsigned int& originalPriceFraction = 0,
		const unsigned int& originalSize = 0,
		const char& originalSaleCondition1 = 0,
		const char& originalSaleCondition2 = 0,
		const char& originalSaleCondition3 = 0,
		const char& originalSaleCondition4 = 0,

		const unsigned int& lastPriceDollars = 0,
		const unsigned int& lastPriceFraction = 0,
		const unsigned int& highPriceDollars = 0,
		const unsigned int& highPriceFraction = 0,
		const unsigned int& lowPriceDollars = 0,
		const unsigned int& lowPriceFraction = 0,
		const unsigned __int64& volume = 0,

		const char& marketCenterID = 0,
		const char& primaryListingMarket = 0,
		const unsigned char& flags = 0):
		TMsgTradeErrorBase(symbol,
			time,
			originalReferenceNumber,
			originalPriceDollars,
			originalPriceFraction,
			originalSize,
			originalSaleCondition1,
			originalSaleCondition2,
			originalSaleCondition3,
			originalSaleCondition4,

			lastPriceDollars,
			lastPriceFraction,
			highPriceDollars,
			highPriceFraction,
			lowPriceDollars,
			lowPriceFraction,
			volume,

			marketCenterID,
			primaryListingMarket,
			flags,
			M_MS_TRADE_CANCEL_ERROR,
			sizeof(TMsgMsTradeError))
	{
	}
};

class TMsgTradeCorrectionBase: public TMessageTimeSymbol
{
public:
	unsigned int m_originalPriceDollars;
	unsigned int m_originalPriceFraction;
	unsigned int m_correctedPriceDollars;
	unsigned int m_correctedPriceFraction;
	unsigned int m_originalSize;
	unsigned int m_correctedSize;
	unsigned __int64 m_originalReferenceNumber;
	unsigned __int64 m_correctedReferenceNumber;
	char m_originalSaleConditions[4];
	char m_correctedSaleConditions[4];
	unsigned int m_lastPriceDollars;
	unsigned int m_lastPriceFraction;
	unsigned int m_highPriceDollars;
	unsigned int m_highPriceFraction;
	unsigned int m_lowPriceDollars;
	unsigned int m_lowPriceFraction;
	unsigned __int64 m_volume;
	char m_marketCenterID;
	char m_primaryListingMarket;
	char m_flags;
protected:
//	TMsgTradeCorrectionBase(const char* symbol, unsigned int time, unsigned short type, unsigned short length):TMessageTimeSymbol(symbol, time, type, length){}
	TMsgTradeCorrectionBase(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& originalPriceDollars,
		const unsigned int& originalPriceFraction,
		const unsigned int& correctedPriceDollars,
		const unsigned int& correctedPriceFraction,
		const unsigned int& originalSize,
		const unsigned int& correctedSize,
		const unsigned __int64& originalReferenceNumber,
		const unsigned __int64& correctedReferenceNumber,
		const char& originalSaleCondition1,
		const char& originalSaleCondition2,
		const char& originalSaleCondition3,
		const char& originalSaleCondition4,
		const char& correctedSaleCondition1,
		const char& correctedSaleCondition2,
		const char& correctedSaleCondition3,
		const char& correctedSaleCondition4,

		const unsigned int& lastPriceDollars,
		const unsigned int& lastPriceFraction,
		const unsigned int& highPriceDollars,
		const unsigned int& highPriceFraction,
		const unsigned int& lowPriceDollars,
		const unsigned int& lowPriceFraction,
		const unsigned __int64& volume,

		const char& marketCenterID,
		const char& primaryListingMarket,
		const unsigned char& flags,

		const unsigned short& type,
		const unsigned short& length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_originalPriceDollars(originalPriceDollars),
		m_originalPriceFraction(originalPriceFraction),
		m_correctedPriceDollars(correctedPriceDollars),
		m_correctedPriceFraction(correctedPriceFraction),
		m_originalSize(originalSize),
		m_correctedSize(correctedSize),
		m_originalReferenceNumber(originalReferenceNumber),
		m_correctedReferenceNumber(correctedReferenceNumber),
		m_lastPriceDollars(lastPriceDollars),
		m_lastPriceFraction(lastPriceFraction),
		m_highPriceDollars(highPriceDollars),
		m_highPriceFraction(highPriceFraction),
		m_lowPriceDollars(lowPriceDollars),
		m_lowPriceFraction(lowPriceFraction),
		m_volume(volume),
		m_marketCenterID(marketCenterID),
		m_primaryListingMarket(primaryListingMarket),
		m_flags(flags)
	{
		char* cursor = m_originalSaleConditions;
		*cursor = originalSaleCondition1;
		*++cursor = originalSaleCondition2;
		*++cursor = originalSaleCondition3;
		*++cursor = originalSaleCondition4;

		cursor = m_correctedSaleConditions;
		*cursor = correctedSaleCondition1;
		*++cursor = correctedSaleCondition2;
		*++cursor = correctedSaleCondition3;
		*++cursor = correctedSaleCondition4;
	}
};

class TMsgTradeCorrection: public TMsgTradeCorrectionBase
{
public:
	TMsgTradeCorrection(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned int& originalPriceDollars = 0,
		const unsigned int& originalPriceFraction = 0,
		const unsigned int& correctedPriceDollars = 0,
		const unsigned int& correctedPriceFraction = 0,
		const unsigned int& originalSize = 0,
		const unsigned int& correctedSize = 0,
		const unsigned __int64& originalReferenceNumber = 0,
		const unsigned __int64& correctedReferenceNumber = 0,
		const char& originalSaleCondition1 = 0,
		const char& originalSaleCondition2 = 0,
		const char& originalSaleCondition3 = 0,
		const char& originalSaleCondition4 = 0,
		const char& correctedSaleCondition1 = 0,
		const char& correctedSaleCondition2 = 0,
		const char& correctedSaleCondition3 = 0,
		const char& correctedSaleCondition4 = 0,

		const unsigned int& lastPriceDollars = 0,
		const unsigned int& lastPriceFraction = 0,
		const unsigned int& highPriceDollars = 0,
		const unsigned int& highPriceFraction = 0,
		const unsigned int& lowPriceDollars = 0,
		const unsigned int& lowPriceFraction = 0,
		const unsigned __int64& volume = 0,

		const char& marketCenterID = 0,
		const char& primaryListingMarket = 0,
		const unsigned char& flags = 0):
		TMsgTradeCorrectionBase(symbol,
			time,
			originalPriceDollars,
			originalPriceFraction,
			correctedPriceDollars,
			correctedPriceFraction,
			originalSize,
			correctedSize,
			originalReferenceNumber,
			correctedReferenceNumber,
			originalSaleCondition1,
			originalSaleCondition2,
			originalSaleCondition3,
			originalSaleCondition4,
			correctedSaleCondition1,
			correctedSaleCondition2,
			correctedSaleCondition3,
			correctedSaleCondition4,

			lastPriceDollars,
			lastPriceFraction,
			highPriceDollars,
			highPriceFraction,
			lowPriceDollars,
			lowPriceFraction,
			volume,

			marketCenterID,
			primaryListingMarket,
			flags,
			M_TRADE_CORRECTION,
			sizeof(TMsgTradeCorrection))
	{
	}
};

class TMsgMsTradeCorrection: public TMsgTradeCorrectionBase
{
public:
	TMsgMsTradeCorrection(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned int& originalPriceDollars = 0,
		const unsigned int& originalPriceFraction = 0,
		const unsigned int& correctedPriceDollars = 0,
		const unsigned int& correctedPriceFraction = 0,
		const unsigned int& originalSize = 0,
		const unsigned int& correctedSize = 0,
		const unsigned __int64& originalReferenceNumber = 0,
		const unsigned __int64& correctedReferenceNumber = 0,
		const char& originalSaleCondition1 = 0,
		const char& originalSaleCondition2 = 0,
		const char& originalSaleCondition3 = 0,
		const char& originalSaleCondition4 = 0,
		const char& correctedSaleCondition1 = 0,
		const char& correctedSaleCondition2 = 0,
		const char& correctedSaleCondition3 = 0,
		const char& correctedSaleCondition4 = 0,

		const unsigned int& lastPriceDollars = 0,
		const unsigned int& lastPriceFraction = 0,
		const unsigned int& highPriceDollars = 0,
		const unsigned int& highPriceFraction = 0,
		const unsigned int& lowPriceDollars = 0,
		const unsigned int& lowPriceFraction = 0,
		const unsigned __int64& volume = 0,

		const char& marketCenterID = 0,
		const char& primaryListingMarket = 0,
		const unsigned char& flags = 0):
		TMsgTradeCorrectionBase(symbol,
			time,
			originalPriceDollars,
			originalPriceFraction,
			correctedPriceDollars,
			correctedPriceFraction,
			originalSize,
			correctedSize,
			originalReferenceNumber,
			correctedReferenceNumber,
			originalSaleCondition1,
			originalSaleCondition2,
			originalSaleCondition3,
			originalSaleCondition4,
			correctedSaleCondition1,
			correctedSaleCondition2,
			correctedSaleCondition3,
			correctedSaleCondition4,

			lastPriceDollars,
			lastPriceFraction,
			highPriceDollars,
			highPriceFraction,
			lowPriceDollars,
			lowPriceFraction,
			volume,

			marketCenterID,
			primaryListingMarket,
			flags,
			M_MS_TRADE_CORRECTION,
			sizeof(TMsgMsTradeCorrection))
	{
	}
};

class TMsgMarketSorterLoaded : public Message
{
public:
	TMsgMarketSorterLoaded():
		Message(TM_MARKET_SORTER_LOADED, sizeof(TMsgMarketSorterLoaded))
	{
	}
//	bool m_loaded;
};

class TMsgMarketSorterChunkLoaded : public TMessageRequest
{
public:
	TMsgMarketSorterChunkLoaded(const unsigned int& requestId):
		TMessageRequest(requestId, TM_MARKET_SORTER_CHUNK_LOADED, sizeof(TMsgMarketSorterChunkLoaded))
//		m_requestId(requestId)
	{
	}
//	unsigned int m_requestId;
};

class TMsgMarketSorterIndexesLoaded : public Message
{
public:
	TMsgMarketSorterIndexesLoaded():
		Message(TM_MARKET_SORTER_INDEXES_LOADED, sizeof(TMsgMarketSorterIndexesLoaded))
	{
	}
};

class TMsgMarketSorterIndexChunkLoaded : public TMessageRequest
{
public:
	TMsgMarketSorterIndexChunkLoaded(const unsigned int& requestId):
		TMessageRequest(requestId, TM_MARKET_SORTER_INDEX_CHUNK_LOADED, sizeof(TMsgMarketSorterIndexChunkLoaded))
//		m_requestId(requestId)
	{
	}
//	unsigned int m_requestId;
};

class TMsgMarketSorterStockChartsLoaded : public Message
{
public:
	TMsgMarketSorterStockChartsLoaded():
		Message(TM_MARKET_SORTER_STOCK_CHARTS_LOADED, sizeof(TMsgMarketSorterStockChartsLoaded))
	{
	}
};

class TMsgMarketSorterIndexChartsLoaded : public Message
{
public:
	TMsgMarketSorterIndexChartsLoaded():Message(TM_MARKET_SORTER_INDEX_CHARTS_LOADED, sizeof(TMsgMarketSorterIndexChartsLoaded)){}
};

//All Charts unloaded, both Stock and Index
class TMsgMarketSorterChartsUnloaded : public Message
{
public:
	TMsgMarketSorterChartsUnloaded():Message(TM_MARKET_SORTER_CHARTS_UNLOADED, sizeof(TMsgMarketSorterChartsUnloaded)){}
};

//Sent to main thread from an IO thread to figure out when the loding of the sortable stocks is completed
class TMsgMarketSorterExpectedSecurityCount : public Message
{
public:
	TMsgMarketSorterExpectedSecurityCount(const unsigned int& securityCount):
		Message(TM_MAKET_SORTER_EXPECTED_SECURITY_COUNT, sizeof(TMsgMarketSorterExpectedSecurityCount)),
		m_securityCount(securityCount)
	{
	}
	unsigned int m_securityCount;
};

//Sent to main thread from an IO thread to figure out when the loding of the sortable stocks is completed
class TMsgMarketSorterExpectedIndexCount : public Message
{
public:
	TMsgMarketSorterExpectedIndexCount(const unsigned int& indexCount):
		Message(TM_MAKET_SORTER_EXPECTED_INDEX_COUNT, sizeof(TMsgMarketSorterExpectedIndexCount)),
		m_indexCount(indexCount)
	{
	}
	unsigned int m_indexCount;
};

class MsgAllAccountsMoney : public Message //total for all Accounts
{
public:
	Money m_money;
protected:
	MsgAllAccountsMoney(const Money& money, const unsigned short& type, const unsigned short& length):
		Message(type, length),
		m_money(money)
	{
	}
};

class MsgAllAccountsInvestment : public MsgAllAccountsMoney
{
public:
	MsgAllAccountsInvestment(const Money& totalInvestment):
		MsgAllAccountsMoney(totalInvestment, TM_ALL_ACCOUNTS_INVESTMENT, sizeof(MsgAllAccountsInvestment))
	{
	}
};

class MsgAllAccountsInvestmentMax : public MsgAllAccountsMoney //total for all Accounts
{
public:
	MsgAllAccountsInvestmentMax(const Money& totalInvestmentMax):
		MsgAllAccountsMoney(totalInvestmentMax, TM_ALL_ACCOUNTS_INVESTMENT_MAX, sizeof(MsgAllAccountsInvestmentMax))
	{
	}
};

class TMsgMarketSorterDelay : public Message
{
public:
	TMsgMarketSorterDelay(const short& delay):
		Message(TM_MARKET_SORTER_DELAY, sizeof(TMsgMarketSorterDelay)),
		m_delay(delay)
	{
	}
	short m_delay;
};

///////////////////
//HistoricalPrint
class PrintData
{
public:
	PrintData(
		const unsigned __int64& referenceNumber = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned int& time = 0,
		const unsigned int& size = 0,
		const char& saleCondition1 = 0,
		const char& saleCondition2 = 0,
		const char& saleCondition3 = 0,
		const char& saleCondition4 = 0,
		const char& marketCenterId = 0,
		const unsigned char& flags = 0,
		const char& primaryListingMarket = 0):
		m_referenceNumber(referenceNumber),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_time(time),
		m_size(size),
		m_saleCondition1(saleCondition1),
		m_saleCondition2(saleCondition2),
		m_saleCondition3(saleCondition3),
		m_saleCondition4(saleCondition4),
		m_marketCenterID(marketCenterId),
		m_primaryListingMarket(primaryListingMarket),
		m_flags(flags)
	{
	}

	unsigned __int64 m_referenceNumber;
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_time;
	unsigned int m_size;
	char m_saleCondition1;
	char m_saleCondition2;
	char m_saleCondition3;
	char m_saleCondition4;
	char m_marketCenterID;
	unsigned char m_flags;
	char m_primaryListingMarket;
};

//////////////////////
enum HistoricalPrintResponseFlags : unsigned char
{
	More	= 0x01,
	Failed	= 0x80,
};

enum HistoricalPrintRequestFlags : unsigned char
{
	ExcludeReferencedPrint = 0x01,
};

class TMsgReqPrintsBase : public TMessageSymbolRequest
{
public:
	unsigned __int64 m_referenceNumber;
	unsigned short m_minute;
	unsigned char m_flags;
protected:
	TMsgReqPrintsBase(const char* const& symbol,
		const unsigned int& requestId,
		const unsigned short& minute,
		const unsigned __int64& referenceNumber,
		const unsigned char& flags,
		const unsigned short& type,
		const unsigned short& length):
		TMessageSymbolRequest(symbol, requestId, type, length),
		m_minute(minute),
		m_referenceNumber(referenceNumber),
		m_flags(flags)
	{
	}
	TMsgReqPrintsBase(const unsigned __int64& symbol,
		const unsigned int& requestId,
		const unsigned short& minute,
		const unsigned __int64& referenceNumber,
		const unsigned char& flags,
		const unsigned short& type,
		const unsigned short& length):
		TMessageSymbolRequest(symbol, requestId, type, length),
		m_minute(minute),
		m_referenceNumber(referenceNumber),
		m_flags(flags)
	{
	}
};

class TMsgReqPrints : public TMsgReqPrintsBase
{
public:
	TMsgReqPrints(const char* const& symbol,
		const unsigned int& requestId,
		const unsigned short& minute,
		const unsigned __int64& referenceNumber,
		const unsigned char& flags):
		TMsgReqPrintsBase(symbol, requestId, minute, referenceNumber, flags, M_REQ_PRINTS, sizeof(TMsgReqPrints))
	{
	}
};

class TMsgPrintsBase : public TMessageSymbolRequest
{
public:
	unsigned __int64 m_nextReferenceNumber;
	unsigned short m_minute;
	unsigned char m_tickSize;
	unsigned char m_flags;
protected:
	TMsgPrintsBase(const char* const& symbol,
		const unsigned int& requestId,
		const unsigned __int64& nextReferenceNumber,
		const unsigned short& minute,
		const unsigned char& tickSize,// = sizeof(PrintData),
//		const unsigned short& ticks,
		const unsigned char& flags,
		const unsigned short& type,
		const unsigned short& length):
		TMessageSymbolRequest(symbol, requestId, type, length),
		m_nextReferenceNumber(nextReferenceNumber),
		m_minute(minute),
		m_tickSize(tickSize),
		m_flags(flags)
	{
	}
};

class TMsgPrints : public TMsgPrintsBase
{
public:
	TMsgPrints(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const unsigned __int64& nextReferenceNumber = 0,
		const unsigned short& minute = 0,
		const unsigned char& tickSize = sizeof(PrintData),
		const unsigned short& ticks = 0,
		const unsigned char& flags = 0):
		TMsgPrintsBase(symbol, requestId, nextReferenceNumber, minute, tickSize, flags, M_RESP_PRINTS, sizeof(TMsgPrints) + ticks * tickSize)
	{
	}
};

enum ChartHistoryFrequency : unsigned char
{
	CHF_INVALID = '\0',
	CHF_MONTH = 'm',
	CHF_WEEK = 'w',
	CHF_DAY = 'd',
	CHF_HOUR = '5',
	CHF_30MIN = '4',
	CHF_15MIN = '3',
	CHF_5MIN = '2',
	CHF_1MIN = '1',
};

class TMsgReqDated : public TMessageSymbolRequest
{
public:
	unsigned int m_startDate;
	unsigned int m_endDate;
protected:
	TMsgReqDated(const char* const& symbol,
		const unsigned int& requestId,
		const unsigned int& startDate,
		const unsigned int& endDate,
		const unsigned short& type,
		const unsigned short& length):
		TMessageSymbolRequest(symbol, requestId, type, length),
		m_startDate(startDate),
		m_endDate(endDate)
	{
	}
};

class TMsgReqCandleData : public TMsgReqDated
{
public:
	unsigned char m_frequency;
protected:
	TMsgReqCandleData(const char* const& symbol,
		const unsigned int& requestId,
		const unsigned int& startDate,
		const unsigned int& endDate,
		const unsigned char& frequency,
		const unsigned short& type,
		const unsigned short& length):
		TMsgReqDated(symbol, requestId, startDate, endDate, type, length),
		m_frequency(frequency)
	{
	}
};

class TMsgReqHistoricalData : public TMsgReqCandleData
{
public:
	TMsgReqHistoricalData(const char* const& symbol,
		const unsigned int& requestId,
		const unsigned int& startDate,
		const unsigned int& endDate,
		const unsigned char& frequency):// 'd' - daily, 'w' - weekly, 'm' - monthly
		TMsgReqCandleData(symbol, requestId, startDate, endDate, frequency, M_REQ_CANDLE_HISTORICAL_DATA, sizeof(TMsgReqHistoricalData))
	{
	}
};

/*Use TMessageSymbolRequest
class TMsgCandleRequestId : public TMessageSymbol
{
public:
	unsigned int m_requestId;
protected:
	TMsgCandleRequestId(const char* const& symbol,
		const unsigned int& requestId,
		const unsigned short& type,
		const unsigned short& length):
		TMessageSymbol(symbol, type, length),
		m_requestId(requestId)
	{
	}
};
*/

class HistoricalTick
{
public:
	HistoricalTick(const unsigned int& volume = 0,
		const unsigned int& open = 0,
		const unsigned int& close = 0,
		const unsigned int& high = 0,
		const unsigned int& low = 0,
		const unsigned int& adjustedClose = 0,
		const unsigned int& date = 0):

		m_volume(volume),
		m_open(open),
		m_close(close),
		m_high(high),
		m_low(low),
		m_adjustedClose(adjustedClose),
		m_date(date)
	{
	}

	unsigned int m_volume;
	unsigned int m_open;
	unsigned int m_close;
	unsigned int m_high;
	unsigned int m_low;
	unsigned int m_adjustedClose;
	unsigned int m_date;
};

class TMsgCandleHistoricalData : public TMessageSymbolRequest//TMsgCandleRequestId
{
public:
	TMsgCandleHistoricalData(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const unsigned char& tickSize = sizeof(HistoricalTick),
		const unsigned short& ticks = 0,
		const unsigned char& primaryExchange = 0,
		const unsigned char& flags = 0):
//		TMsgCandleRequestId(symbol, requestId, M_RESP_CANDLE_HISTORICAL_DATA, sizeof(TMsgCandleHistoricalData) + (unsigned int)tickSize * ticks),
		TMessageSymbolRequest(symbol, requestId, M_RESP_CANDLE_HISTORICAL_DATA, sizeof(TMsgCandleHistoricalData) + ticks * tickSize),
		m_tickSize(tickSize),
		m_flags(flags),
		m_primaryExchange(primaryExchange)
	{
	}

	unsigned char m_tickSize;
	unsigned char m_flags;
	unsigned char m_primaryExchange;
};

class TMsgReqIntradayData : public TMsgReqCandleData
{
public:
	TMsgReqIntradayData(const char* const& symbol,
		const unsigned int& requestId,
		const unsigned int& startDate,
		const unsigned int& endDate,
		const unsigned char& frequency)://'1' - 1 minute, '2' - 5 minutes, '3' - 15 minutes, '4' - 30 minutes, '5' - 1 hour
		TMsgReqCandleData(symbol, requestId, startDate, endDate, frequency, M_REQ_CANDLE_INTRADAY_DATA, sizeof(TMsgReqIntradayData))
	{
	}
};

class HistoricalIntraDayTick
{
public:
	HistoricalIntraDayTick(const unsigned int& moneyDollar = 0,
		const unsigned int& moneyFraction = 0,
		const unsigned int& volume = 0,
		const unsigned int& first = 0,
		const unsigned int& last = 0,
		const unsigned int& high = 0,
		const unsigned int& low = 0,
		const unsigned int& minute = 0):
		
		m_moneyDollar(moneyDollar),
		m_moneyFraction(moneyFraction),
		m_volume(volume),
		m_first(first),
		m_last(last),
		m_high(high),
		m_low(low),
		m_minute(minute)
	{
	}

	unsigned int m_moneyDollar;
	unsigned int m_moneyFraction;
	unsigned int m_volume;
	unsigned int m_first;
	unsigned int m_last;
	unsigned int m_high;
	unsigned int m_low;
	unsigned short m_minute;
};

class TMsgCandleIntradayData : public TMessageSymbolRequest//TMsgCandleRequestId
{
public:
	TMsgCandleIntradayData(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const unsigned int& date = 0,
		const unsigned char& tickSize = sizeof(HistoricalIntraDayTick),
		const unsigned short& ticks = 0,
		const unsigned char& flags = 0):
//		TMsgCandleRequestId(symbol, requestId, M_RESP_CANDLE_INTRADAY_DATA, sizeof(TMsgCandleIntradayData) + (unsigned int)tickSize * ticks),
		TMessageSymbolRequest(symbol, requestId, M_RESP_CANDLE_INTRADAY_DATA, sizeof(TMsgCandleIntradayData) + ticks * tickSize),
		m_date(date),
		m_tickSize(tickSize),
		m_flags(flags)
//		m_primaryExchange(primaryExchange)
	{
	}

	unsigned int m_date;
	unsigned char m_tickSize;
	unsigned char m_flags;
};

class TMsgAccountOcoOrders : public TMsgAccountObject
{
public:
	unsigned int m_ocoId;
protected:
	TMsgAccountOcoOrders(const char* const& accountName, const unsigned int& ocoId, const unsigned short& type, const unsigned short& length):
		TMsgAccountObject(accountName, type, length),
		m_ocoId(ocoId)
	{
	}
};

class TMsgAccountSetCurrentOcoId : public TMsgAccountOcoOrders
{
public:
	TMsgAccountSetCurrentOcoId(const char* const& accountName, const unsigned int& ocoId, const unsigned int& previousOcoId):
		TMsgAccountOcoOrders(accountName, ocoId, TM_ACCOUNT_SET_CURRENT_OCO_ID, sizeof(TMsgAccountSetCurrentOcoId)),
		m_previousOcoId(previousOcoId)
	{
	}
	unsigned int m_previousOcoId;
};

class TMsgAccountResetCurrentOcoId : public TMsgAccountObject
{
public:
	TMsgAccountResetCurrentOcoId(const char* const& accountName):
		TMsgAccountObject(accountName, TM_ACCOUNT_RESET_CURRENT_OCO_ID, sizeof(TMsgAccountResetCurrentOcoId))
	{
	}
};

class TMsgAccountHighestOcoId : public TMsgAccountOcoOrders
{
public:
	TMsgAccountHighestOcoId(const char* const& accountName, const unsigned int& highestOcoId):
		TMsgAccountOcoOrders(accountName, highestOcoId, TM_ACCOUNT_HIGHEST_OCO_ID, sizeof(TMsgAccountHighestOcoId))
	{
	}
};

#ifndef TAKION_NO_OPTIONS

class TMessageOptionBlockUnderlierSymbol : public TMessageOptionBlock
{
public:
	unsigned __int64 m_underlierSymbol;
protected:
	TMessageOptionBlockUnderlierSymbol(const char* const& underlierSymbol, const char* const& symbol, const unsigned __int64& optionBlock, const unsigned short& type, const unsigned short& length):
		TMessageOptionBlock(symbol, optionBlock, type, length),
		m_underlierSymbol(U_RepresentStringAsUnsignedNumber<unsigned __int64>(underlierSymbol, sizeof(unsigned __int64) - 1))
	{
	}
	TMessageOptionBlockUnderlierSymbol(const unsigned __int64& underlierSymbol, const unsigned __int64& symbol, const unsigned __int64& optionBlock, const unsigned short& type, const unsigned short& length):
		TMessageOptionBlock(symbol, optionBlock, type, length),
		m_underlierSymbol(underlierSymbol)
	{
	}
	TMessageOptionBlockUnderlierSymbol(const unsigned short& type, const unsigned short& length):
		TMessageOptionBlock(type, length),
		m_underlierSymbol(0)
	{
	}
};

class TMsgOptionAdd : public TMessageOptionBlockUnderlierSymbol
{
public:
	TMsgOptionAdd(const char* const& underlierSymbol, const char* const& symbol, const unsigned __int64& optionBlock):
		TMessageOptionBlockUnderlierSymbol(underlierSymbol, symbol, optionBlock, TM_OPTION_ADD, sizeof(TMsgOptionAdd))
	{
	}
	TMsgOptionAdd(const unsigned __int64& underlierSymbol, const unsigned __int64& symbol, const unsigned __int64& optionBlock):
		TMessageOptionBlockUnderlierSymbol(underlierSymbol, symbol, optionBlock, TM_OPTION_ADD, sizeof(TMsgOptionAdd))
	{
	}
	TMsgOptionAdd():
		TMessageOptionBlockUnderlierSymbol(TM_OPTION_ADD, sizeof(TMsgOptionAdd))
	{
	}
};

class TMsgOptionLevel1Refreshed : public TMessageOptionBlockUnderlierSymbol
{
public:
	TMsgOptionLevel1Refreshed(const char* const& underlierSymbol, const char* const& symbol, const unsigned __int64& optionBlock):
		TMessageOptionBlockUnderlierSymbol(underlierSymbol, symbol, optionBlock, TM_OPTION_LEVEL1_REFRESHED, sizeof(TMsgOptionLevel1Refreshed))
	{
	}
	TMsgOptionLevel1Refreshed(const unsigned __int64& underlierSymbol, const unsigned __int64& symbol, const unsigned __int64& optionBlock):
		TMessageOptionBlockUnderlierSymbol(underlierSymbol, symbol, optionBlock, TM_OPTION_LEVEL1_REFRESHED, sizeof(TMsgOptionLevel1Refreshed))
	{
	}
	TMsgOptionLevel1Refreshed():
		TMessageOptionBlockUnderlierSymbol(TM_OPTION_LEVEL1_REFRESHED, sizeof(TMsgOptionLevel1Refreshed))
	{
	}
};

class TMsgOptionRemove : public TMessageOptionBlock
{
public:
	TMsgOptionRemove(const char* const& symbol, const unsigned __int64& optionBlock):TMessageOptionBlock(symbol, optionBlock, TM_OPTION_REMOVE, sizeof(TMsgOptionRemove))
	{
	}
	TMsgOptionRemove(const unsigned __int64& symbol, const unsigned __int64& optionBlock):TMessageOptionBlock(symbol, optionBlock, TM_OPTION_REMOVE, sizeof(TMsgOptionRemove))
	{
	}
	TMsgOptionRemove():TMessageOptionBlock(TM_OPTION_REMOVE, sizeof(TMsgOptionRemove))
	{
	}
};

class TMsgOptionL2Add : public TMessageOptionBlock
{
public:
	TMsgOptionL2Add(const char* const& symbol, const unsigned __int64& optionBlock):TMessageOptionBlock(symbol, optionBlock, TM_OPTION_L2_ADD, sizeof(TMsgOptionL2Add))
	{
	}
	TMsgOptionL2Add(const unsigned __int64& symbol, const unsigned __int64& optionBlock):TMessageOptionBlock(symbol, optionBlock, TM_OPTION_L2_ADD, sizeof(TMsgOptionL2Add))
	{
	}
	TMsgOptionL2Add():TMessageOptionBlock(TM_OPTION_L2_ADD, sizeof(TMsgOptionL2Add))
	{
	}
};

class TMsgOptionL2Remove : public TMessageOptionBlock
{
public:
	TMsgOptionL2Remove(const char* const& symbol, const unsigned __int64& optionBlock):TMessageOptionBlock(symbol, optionBlock, TM_OPTION_L2_REMOVE, sizeof(TMsgOptionL2Remove))
	{
	}
	TMsgOptionL2Remove(const unsigned __int64& symbol, const unsigned __int64& optionBlock):TMessageOptionBlock(symbol, optionBlock, TM_OPTION_L2_REMOVE, sizeof(TMsgOptionL2Remove))
	{
	}
	TMsgOptionL2Remove():TMessageOptionBlock(TM_OPTION_L2_REMOVE, sizeof(TMsgOptionL2Remove))
	{
	}
};

class TMsgOptionAddIdle : public TMessageOptionBlock
{
public:
	TMsgOptionAddIdle(const char* const& symbol, const unsigned __int64& optionBlock):TMessageOptionBlock(symbol, optionBlock, TM_OPTION_ADD_IDLE, sizeof(TMsgOptionAddIdle))
	{
	}
	TMsgOptionAddIdle(const unsigned __int64& symbol, const unsigned __int64& optionBlock):TMessageOptionBlock(symbol, optionBlock, TM_OPTION_ADD_IDLE, sizeof(TMsgOptionAddIdle))
	{
	}
	TMsgOptionAddIdle():TMessageOptionBlock(TM_OPTION_ADD_IDLE, sizeof(TMsgOptionAddIdle))
	{
	}
};

class TMsgOptionRemoveIdle : public TMessageOptionBlock
{
public:
	TMsgOptionRemoveIdle(const char* const& symbol, const unsigned __int64& optionBlock):TMessageOptionBlock(symbol, optionBlock, TM_OPTION_REMOVE_IDLE, sizeof(TMsgOptionRemoveIdle))
	{
	}
	TMsgOptionRemoveIdle(const unsigned __int64& symbol, const unsigned __int64& optionBlock):TMessageOptionBlock(symbol, optionBlock, TM_OPTION_REMOVE_IDLE, sizeof(TMsgOptionRemoveIdle))
	{
	}
	TMsgOptionRemoveIdle():TMessageOptionBlock(TM_OPTION_REMOVE_IDLE, sizeof(TMsgOptionRemoveIdle))
	{
	}
};

class TMsgUnderlierAdd : public TMessageSymbol
{
public:
	TMsgUnderlierAdd(const char* const& symbol):TMessageSymbol(symbol, TM_UNDERLIER_ADD, sizeof(TMsgUnderlierAdd)){}
	TMsgUnderlierAdd(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_UNDERLIER_ADD, sizeof(TMsgUnderlierAdd)){}
	TMsgUnderlierAdd():TMessageSymbol(TM_UNDERLIER_ADD, sizeof(TMsgUnderlierAdd)){}
};

class TMsgUnderlierRemove : public TMessageSymbol
{
public:
	TMsgUnderlierRemove(const char* const& symbol):TMessageSymbol(symbol, TM_UNDERLIER_REMOVE, sizeof(TMsgUnderlierRemove)){}
	TMsgUnderlierRemove(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_UNDERLIER_REMOVE, sizeof(TMsgUnderlierRemove)){}
	TMsgUnderlierRemove():TMessageSymbol(TM_UNDERLIER_REMOVE, sizeof(TMsgUnderlierRemove)){}
};

class TMsgUnderlierAddIdle : public TMessageSymbol
{
public:
	TMsgUnderlierAddIdle(const char* const& symbol):TMessageSymbol(symbol, TM_UNDERLIER_ADD_IDLE, sizeof(TMsgUnderlierAddIdle)){}
	TMsgUnderlierAddIdle(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_UNDERLIER_ADD_IDLE, sizeof(TMsgUnderlierAddIdle)){}
	TMsgUnderlierAddIdle():TMessageSymbol(TM_UNDERLIER_ADD_IDLE, sizeof(TMsgUnderlierAddIdle)){}
};

class TMsgUnderlierRemoveIdle : public TMessageSymbol
{
public:
	TMsgUnderlierRemoveIdle(const char* const& symbol):TMessageSymbol(symbol, TM_UNDERLIER_REMOVE_IDLE, sizeof(TMsgUnderlierRemoveIdle)){}
	TMsgUnderlierRemoveIdle(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_UNDERLIER_REMOVE_IDLE, sizeof(TMsgUnderlierRemoveIdle)){}
	TMsgUnderlierRemoveIdle():TMessageSymbol(TM_UNDERLIER_REMOVE_IDLE, sizeof(TMsgUnderlierRemoveIdle)){}
};

class TMsgUnderlierAddRemovable : public TMessageSymbol
{
public:
	TMsgUnderlierAddRemovable(const char* const& symbol):TMessageSymbol(symbol, TM_UNDERLIER_ADD_REMOVABLE, sizeof(TMsgUnderlierAddRemovable)){}
	TMsgUnderlierAddRemovable(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_UNDERLIER_ADD_REMOVABLE, sizeof(TMsgUnderlierAddRemovable)){}
	TMsgUnderlierAddRemovable():TMessageSymbol(TM_UNDERLIER_ADD_REMOVABLE, sizeof(TMsgUnderlierAddRemovable)){}
};

class TMsgUnderlierRemoveRemovable : public TMessageSymbol
{
public:
	TMsgUnderlierRemoveRemovable(const char* const& symbol):TMessageSymbol(symbol, TM_UNDERLIER_REMOVE_REMOVABLE, sizeof(TMsgUnderlierRemoveRemovable)){}
	TMsgUnderlierRemoveRemovable(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_UNDERLIER_REMOVE_REMOVABLE, sizeof(TMsgUnderlierRemoveRemovable)){}
	TMsgUnderlierRemoveRemovable():TMessageSymbol(TM_UNDERLIER_REMOVE_REMOVABLE, sizeof(TMsgUnderlierRemoveRemovable)){}
};

class TMsgUnderlierUnsubscribed : public TMessageSymbol
{
public:
	TMsgUnderlierUnsubscribed(const char* const& symbol):TMessageSymbol(symbol, TM_UNDERLIER_UNSUBSCRIBED, sizeof(TMsgUnderlierUnsubscribed)){}
	TMsgUnderlierUnsubscribed(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_UNDERLIER_UNSUBSCRIBED, sizeof(TMsgUnderlierUnsubscribed)){}
	TMsgUnderlierUnsubscribed():TMessageSymbol(TM_UNDERLIER_UNSUBSCRIBED, sizeof(TMsgUnderlierUnsubscribed)){}
};

class TMsgUnderlierSubscriptionQueued : public TMessageSymbol
{
public:
	TMsgUnderlierSubscriptionQueued(const char* const& symbol):TMessageSymbol(symbol, TM_UNDERLIER_SUBSCRIPTION_QUEUED, sizeof(TMsgUnderlierSubscriptionQueued)){}
	TMsgUnderlierSubscriptionQueued(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_UNDERLIER_SUBSCRIPTION_QUEUED, sizeof(TMsgUnderlierSubscriptionQueued)){}
	TMsgUnderlierSubscriptionQueued():TMessageSymbol(TM_UNDERLIER_SUBSCRIPTION_QUEUED, sizeof(TMsgUnderlierSubscriptionQueued)){}
};

class TMsgOptionSubscriptionQueued : public TMessageOptionBlock
{
public:
	TMsgOptionSubscriptionQueued(const char* const& symbol, const unsigned __int64& optionBlock):TMessageOptionBlock(symbol, optionBlock, TM_OPTION_SUBSCRIPTION_QUEUED, sizeof(TMsgOptionSubscriptionQueued)){}
	TMsgOptionSubscriptionQueued(const unsigned __int64& symbol, const unsigned __int64& optionBlock):TMessageOptionBlock(symbol, optionBlock, TM_OPTION_SUBSCRIPTION_QUEUED, sizeof(TMsgOptionSubscriptionQueued)){}
	TMsgOptionSubscriptionQueued():TMessageOptionBlock(TM_OPTION_SUBSCRIPTION_QUEUED, sizeof(TMsgOptionSubscriptionQueued)){}
};

class TMsgUnderlierSubscriptionUnQueued : public TMessageSymbol
{
public:
	TMsgUnderlierSubscriptionUnQueued(const char* const& symbol):TMessageSymbol(symbol, TM_UNDERLIER_SUBSCRIPTION_UNQUEUED, sizeof(TMsgUnderlierSubscriptionUnQueued)){}
	TMsgUnderlierSubscriptionUnQueued(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_UNDERLIER_SUBSCRIPTION_UNQUEUED, sizeof(TMsgUnderlierSubscriptionUnQueued)){}
	TMsgUnderlierSubscriptionUnQueued():TMessageSymbol(TM_UNDERLIER_SUBSCRIPTION_UNQUEUED, sizeof(TMsgUnderlierSubscriptionUnQueued)){}
};

class TMsgOptionSubscriptionUnQueued : public TMessageOptionBlock
{
public:
	TMsgOptionSubscriptionUnQueued(const char* const& symbol, const unsigned __int64& optionBlock):TMessageOptionBlock(symbol, optionBlock, TM_OPTION_SUBSCRIPTION_UNQUEUED, sizeof(TMsgOptionSubscriptionUnQueued)){}
	TMsgOptionSubscriptionUnQueued(const unsigned __int64& symbol, const unsigned __int64& optionBlock):TMessageOptionBlock(symbol, optionBlock, TM_OPTION_SUBSCRIPTION_UNQUEUED, sizeof(TMsgOptionSubscriptionUnQueued)){}
	TMsgOptionSubscriptionUnQueued():TMessageOptionBlock(TM_OPTION_SUBSCRIPTION_UNQUEUED, sizeof(TMsgOptionSubscriptionUnQueued)){}
};

class TMsgOptionSubscriptionStuck : public TMessageOptionBlock
{
public:
	TMsgOptionSubscriptionStuck(const char* const& symbol, const unsigned __int64& optionBlock):TMessageOptionBlock(symbol, optionBlock, TM_OPTION_SUBSCRIPTION_STUCK, sizeof(TMsgOptionSubscriptionStuck)){}
	TMsgOptionSubscriptionStuck(const unsigned __int64& symbol, const unsigned __int64& optionBlock):TMessageOptionBlock(symbol, optionBlock, TM_OPTION_SUBSCRIPTION_STUCK, sizeof(TMsgOptionSubscriptionStuck)){}
	TMsgOptionSubscriptionStuck():TMessageOptionBlock(TM_OPTION_SUBSCRIPTION_STUCK, sizeof(TMsgOptionSubscriptionStuck)){}
};

class TMsgOptionSubscriptionQueueCleared : public Message
{
public:
	TMsgOptionSubscriptionQueueCleared():Message(TM_OPTION_SUBSCRIPTION_QUEUE_CLEARED, sizeof(TMsgOptionSubscriptionQueueCleared)){}
};

class TMsgUnderlier : public Message
{
public:
	Underlier* m_underlier;
protected:
	TMsgUnderlier(Underlier* const& underlier, const unsigned short& type, const unsigned short& length):Message(type, length), m_underlier(underlier){}
};

class TMsgUnderlierDelete : public TMsgUnderlier
{
public:
	TMsgUnderlierDelete(Underlier* const& underlier):TMsgUnderlier(underlier, TM_UNDERLIER_DELETE, sizeof(TMsgUnderlierDelete)){}
};

class TMsgUnderlierObject : public TMsgUnderlier//For additionalInfo only
{
public:
	TMsgUnderlierObject(Underlier* const& underlier) :TMsgUnderlier(underlier, TM_UNDERLIER_OBJECT, sizeof(TMsgUnderlierObject)){}
};

class TMsgUnderlierNewDay : public TMessageSymbol
{
public:
	TMsgUnderlierNewDay(const char* const& symbol):TMessageSymbol(symbol, TM_UNDERLIER_NEW_DAY, sizeof(TMsgUnderlierNewDay)){}
	TMsgUnderlierNewDay(const unsigned __int64& symbol = 0):TMessageSymbol(symbol, TM_UNDERLIER_NEW_DAY, sizeof(TMsgUnderlierNewDay)){}
};

class OptionBlock
{
public:
	OptionBlock(const unsigned __int64& optionBlock = 0):
		m_optionBlock(optionBlock)
	{
	}

	OptionBlock(unsigned int strikePrice,
		unsigned char reserved,
		unsigned char expirationDay,
		unsigned char expirationMonth,
		unsigned char expirationYear):
		m_strikePrice(strikePrice),
		m_reserved(reserved),
		m_expirationDay(expirationDay),
		m_expirationMonth(expirationMonth),
		m_expirationYear(expirationYear)
	{
	}

	OptionBlock(const OptionBlock& other):m_optionBlock(other.m_optionBlock)
	{
	}

	OptionBlock& operator=(const OptionBlock& other)
	{
		m_optionBlock = other.m_optionBlock;
		return *this;
	}

	bool IsEmpty() const{return !m_optionBlock;}
	bool IsAny() const{return 0xffffffffffffffff == m_optionBlock;}
	void Reset(){m_optionBlock = 0;}
	void SetAny(){m_optionBlock = 0xffffffffffffffff;}
	unsigned __int64 GetExpirationBlock() const{return m_optionBlock & 0xffffff0000000000;}
	unsigned __int64 GetStrikePriceBlock() const{return m_optionBlock & 0x000000ffffffffff;}
//	bool IsCall() const{return m_expirationMonth >= 'A' && m_expirationMonth <= 'L';}
	bool IsCall() const{return m_expirationMonth < 'M';}
	bool IsPut() const{return m_expirationMonth > 'L';}

	operator unsigned __int64() const{return m_optionBlock;}
	const unsigned __int64& GetOptionBlock() const{return m_optionBlock;}
	void SetOptionBlock(const unsigned __int64& optionBlock){m_optionBlock = optionBlock;}

	bool operator==(const OptionBlock& other) const{return m_optionBlock == other.m_optionBlock;}
	bool operator!=(const OptionBlock& other) const{return m_optionBlock != other.m_optionBlock;}
	bool operator<(const OptionBlock& other) const{return m_optionBlock < other.m_optionBlock;}
	bool operator<=(const OptionBlock& other) const{return m_optionBlock <= other.m_optionBlock;}
	bool operator>(const OptionBlock& other) const{return m_optionBlock > other.m_optionBlock;}
	bool operator>=(const OptionBlock& other) const{return m_optionBlock >= other.m_optionBlock;}

	void SetStrikePrice(const unsigned int& price){m_strikePrice = price;}
	void SetReserved(const unsigned char& reserved){m_reserved = reserved;}
	void SetExpirationDay(const unsigned char& expirationDay){m_expirationDay = expirationDay;}
	void SetExpirationMonth(const unsigned char& expirationMonth){m_expirationMonth = expirationMonth;}
	void SetExpirationYear(const unsigned char& expirationYear){m_expirationYear = expirationYear;}

	const unsigned int& GetStrikePrice() const{return m_strikePrice;}
	const unsigned char& GetReserved() const{return m_reserved;}
	const unsigned char& GetExpirationDay() const{return m_expirationDay;}
	const unsigned char& GetExpirationMonthCode() const{return m_expirationMonth;}
	const unsigned char& GetExpirationYear() const{return m_expirationYear;}
	unsigned char GetExpirationMonth() const{return m_expirationMonth < 'M' ? m_expirationMonth - ('A' - 1) : m_expirationMonth - 'L';}
	static unsigned int GetNormalizedStrikePriceStatic(const unsigned int& strikePrice)
	{
//		unsigned int dollars = strikePrice / 1000;
//		return (dollars << 14) | (strikePrice * 10 - 10000 * dollars);
//		return Price::CalculateCompactPrice(dollars, strikePrice * 10 - 10000 * dollars);
		return Price::CalculateCompactPriceFromStrikePrice(strikePrice);
	}
	unsigned int GetNormalizedStrikePrice() const{return GetNormalizedStrikePriceStatic(m_strikePrice);}
private:
	union
	{
		unsigned __int64 m_optionBlock;
		struct
		{
			unsigned int m_strikePrice;
			unsigned char m_reserved;
			unsigned char m_expirationDay;
			unsigned char m_expirationMonth;
			unsigned char m_expirationYear;
		};
	};
};

class TMessageOption : public TMessageTimeSymbol
{
public:
	OptionBlock	m_optionBlock;
protected:
	TMessageOption(const char* const& symbol,
		const unsigned int& time,
		const OptionBlock& optionBlock,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTimeSymbol(symbol, time, type, length),
		m_optionBlock(optionBlock)
	{
	}
};

class TMsgOptLevel2 : public TMessageOption
{
public:
	TMsgOptLevel2(const char* const& symbol = "",
		const unsigned int& time = 0,
		const OptionBlock& optionBlock = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned int& size = 0,
		const unsigned char& side = Buy,
		const unsigned char& marketCenterID = 0,
		const unsigned char& quoteCondition = 0,
		const unsigned char& flags = 0):
		TMessageOption(symbol, time, optionBlock, M_OPT_LEVEL2, sizeof(TMsgOptLevel2)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_size(size),
		m_side(side),
		m_marketCenterID(marketCenterID),
		m_quoteCondition(quoteCondition),
		m_flags(flags)
	{
	}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_size;
	unsigned char m_side;
	unsigned char m_marketCenterID;
	unsigned char m_quoteCondition;
	unsigned char m_flags;
};

class TMsgOptLevel1 : public TMessageOption
{
public:
	TMsgOptLevel1(const char* const& symbol = "",
		const unsigned int& time = 0,
		const OptionBlock& optionBlock = OptionBlock(0),
		const unsigned int& bidPriceDollars = 0,
		const unsigned int& bidPriceFraction = 0,
		const unsigned int& askPriceDollars = 0,
		const unsigned int& askPriceFraction = 0,
		const unsigned int& bidSize = 0,
		const unsigned int& askSize = 0,
		const unsigned char& bidMarketCenter = 0,
		const unsigned char& askMarketCenter = 0,
		const unsigned char& quoteCondition = 0,
		const unsigned char& flags = 0):
		TMessageOption(symbol, time, optionBlock, M_OPT_LEVEL1, sizeof(TMsgOptLevel1)),
		m_bidPriceDollars(bidPriceDollars),
		m_bidPriceFraction(bidPriceFraction),
		m_askPriceDollars(askPriceDollars),
		m_askPriceFraction(askPriceFraction),
		m_bidSize(bidSize),
		m_askSize(askSize),
		m_bidMarketCenter(bidMarketCenter),
		m_askMarketCenter(askMarketCenter),
		m_quoteCondition(quoteCondition),
		m_flags(flags)
	{
	}
	unsigned int m_bidPriceDollars;
	unsigned int m_bidPriceFraction;
	unsigned int m_askPriceDollars;
	unsigned int m_askPriceFraction;
	unsigned int m_bidSize;
	unsigned int m_askSize;
	unsigned char m_bidMarketCenter;
	unsigned char m_askMarketCenter;
	unsigned char m_quoteCondition;
	unsigned char m_flags;
};

/*Same as for stocks
enum OptTradeReportFlags : unsigned char
{
	NoPriceChanges		= 0,
	LastPriceChanged	= 1,
	LowPriceChanged		= 2,
	HighPriceChanged	= 4,
	TradeThroughExempt	= 8,
};
*/
class TMsgOptTrade : public TMessageOption
{
public:
	TMsgOptTrade(const char* const& symbol = "",
		const unsigned int& time = 0,
		const OptionBlock& optionBlock = OptionBlock(0),
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned int& size = 0,
		const unsigned int& tradeId = 0,
		const unsigned char& marketCenterId = 0,
		const unsigned char& tradeCondition = 0):
		TMessageOption(symbol, time, optionBlock, M_OPT_TRADE_REPORT, sizeof(TMsgOptTrade)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_size(size),
		m_tradeId(tradeId),
		m_marketCenterId(marketCenterId),
		m_saleCondition(tradeCondition)
	{
	}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_size;
	unsigned int m_tradeId;
	unsigned char m_marketCenterId;
	unsigned char m_saleCondition;
};

class TMsgOptOpenInterest : public TMessageOption
{
public:
	TMsgOptOpenInterest(const char* const& symbol,
		const unsigned int& time,
		const OptionBlock& optionBlock,
		const unsigned int& openInterestVolume):
		TMessageOption(symbol, time, optionBlock, M_OPT_OPEN_INTEREST, sizeof(TMsgOptOpenInterest)),
		m_openInterestVolume(openInterestVolume)
	{
	}
	unsigned int m_openInterestVolume;
};

/*
enum SubscriptionTypes : unsigned char
{
    UpdatesOnly        = 0,
    SubscribeSymbol    = 1,
    UpdatesOnlyAll    = 0xfe,
    RefreshAll        = 0xff,
};
*/
class TMsgReqOptRefreshSymbol : public TMessageSymbol
{
public:
	TMsgReqOptRefreshSymbol(const char* const& symbol, const unsigned char& flags, const unsigned char& blockSize, const unsigned int& requestId):
		TMessageSymbol(symbol, M_REQ_OPT_REFRESH_SYMBOL, sizeof(TMsgReqOptRefreshSymbol)),
		m_flags(flags),
		m_blockSize(blockSize),
		m_requestId(requestId)
	{
	}
	TMsgReqOptRefreshSymbol(const unsigned __int64& symbol, const unsigned char& flags, const unsigned char& blockSize, const unsigned int& requestId):
		TMessageSymbol(symbol, M_REQ_OPT_REFRESH_SYMBOL, sizeof(TMsgReqOptRefreshSymbol)),
		m_flags(flags),
		m_blockSize(blockSize),
		m_requestId(requestId)
	{
	}
	unsigned char m_flags;
	unsigned char m_blockSize;
	unsigned int m_requestId;
};

class TMsgOptionSymbol : public TMessageSymbol
{
public:
	OptionBlock m_optionBlock;
protected:
	TMsgOptionSymbol(const char* const& symbol, const unsigned __int64& optionBlock, const unsigned short& type, const unsigned short& length):
		TMessageSymbol(symbol, type, length),
		m_optionBlock(optionBlock)
	{
	}
	TMsgOptionSymbol(const unsigned __int64& symbol, const unsigned __int64& optionBlock, const unsigned short& type, const unsigned short& length):
		TMessageSymbol(symbol, type, length),
		m_optionBlock(optionBlock)
	{
	}
	TMsgOptionSymbol(const unsigned __int64& symbol, const OptionBlock& optionBlock, const unsigned short& type, const unsigned short& length):
		TMessageSymbol(symbol, type, length),
		m_optionBlock(optionBlock)
	{
	}
};

class TMsgOptionSymbolRoot : public TMsgOptionSymbol
{
public:
	Symbol m_rootSymbol;
protected:
	TMsgOptionSymbolRoot(const char* const& symbol, const unsigned __int64& optionBlock, const char* const& rootSymbol, const unsigned short& type, const unsigned short& length):
		TMsgOptionSymbol(symbol, optionBlock, type, length)
	{
		U_CopyAndPad(m_rootSymbol, sizeof(m_rootSymbol), rootSymbol, '\0');
	}
	TMsgOptionSymbolRoot(const unsigned __int64& symbolNum, const unsigned __int64& optionBlock, const unsigned __int64& rootSymbolNum, const unsigned short& type, const unsigned short& length):
		TMsgOptionSymbol(symbolNum, optionBlock, type, length)
	{
		*(unsigned __int64*)m_rootSymbol = rootSymbolNum;
	}
	TMsgOptionSymbolRoot(const unsigned __int64& symbolNum, const OptionBlock& optionBlock, const unsigned __int64& rootSymbolNum, const unsigned short& type, const unsigned short& length):
		TMsgOptionSymbol(symbolNum, optionBlock, type, length)
	{
		*(unsigned __int64*)m_rootSymbol = rootSymbolNum;
	}
};

class TMsgReqRefreshOption : public TMsgOptionSymbolRoot
{
public:
	TMsgReqRefreshOption(const unsigned __int64& symbolNum, const unsigned __int64& optionBlock, const unsigned __int64& rootSymbolNum, const unsigned int& requestID = 0):
		TMsgOptionSymbolRoot(symbolNum, optionBlock, rootSymbolNum, M_REQ_REFRESH_OPTION, sizeof(TMsgReqRefreshOption)),
		m_requestID(requestID)
	{
	}
    unsigned int m_requestID;
};

class TMsgRespRefreshOption : public TMessageOption//m_time is m_requestId
{
public:
	TMsgRespRefreshOption(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const OptionBlock& optionBlock = OptionBlock(0),
		const char* const& rootSymbol = "",
		const unsigned short& dataSize = 0,
		const unsigned char& steps = 0,
		const unsigned char& flags = 0,
		const unsigned short& optionType = eoNum)://*(unsigned short*)"EU")://"EU" - equity option, "IU" - index option
		TMessageOption(symbol, requestId, optionBlock, M_RESP_REFRESH_OPTION, dataSize),
		m_steps(steps),
		m_flags(flags),
		m_optionType(optionType)
	{
		U_CopyAndPad(m_rootSymbol, sizeof(m_rootSymbol), rootSymbol, '\0');
	}
	Symbol m_rootSymbol;
	unsigned char m_steps;
	unsigned char m_flags;
	unsigned short m_optionType;//"EU" - equity option, "IU" - index option
};

class TMsgReqUnsubscribeOption : public TMsgOptionSymbolRoot
{
public:
	TMsgReqUnsubscribeOption(const unsigned __int64& symbolNum, const unsigned __int64& optionBlock, const unsigned __int64& rootSymbolNum):
		TMsgOptionSymbolRoot(symbolNum, optionBlock, rootSymbolNum, M_REQ_UNSUBSCRIBE_OPTION, sizeof(TMsgReqUnsubscribeOption))
	{
	}
	TMsgReqUnsubscribeOption(const unsigned __int64& symbolNum, const OptionBlock& optionBlock, const unsigned __int64& rootSymbolNum):
		TMsgOptionSymbolRoot(symbolNum, optionBlock, rootSymbolNum, M_REQ_UNSUBSCRIBE_OPTION, sizeof(TMsgReqUnsubscribeOption))
	{
	}
};


/*
enum StockRefreshStatus : unsigned char
{
	REFRESH_EndOfBlock		= 0x20,
	REFRESH_EndOfRefresh	= 0x40,
	REFRESH_RefreshFailed	= 0x80,
};
*/
class TMsgRespOptRefreshSymbol : public TMessageTimeSymbol//m_time is m_requestId
{
public:
	TMsgRespOptRefreshSymbol(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const unsigned short& dataSize = 0,
		const unsigned char& steps = 0,
		const unsigned char& flags = 0,
		const unsigned short& optionType = eoNum)://*(unsigned short*)"EU")://"EU" - equity option, "IU" - index option
		TMessageTimeSymbol(symbol, requestId, M_RESP_OPT_REFRESH_SYMBOL, dataSize),
		m_steps(steps),
		m_flags(flags),
		m_optionType(optionType)
	{
	}
	unsigned char m_steps;
	unsigned char m_flags;
	unsigned short m_optionType;//"EU" - equity option, "IU" - index option
};

class TMsgReqOptUnsubscribeSymbol : public TMessageSymbol
{
public:
	TMsgReqOptUnsubscribeSymbol(const char* const& symbol):TMessageSymbol(symbol, M_REQ_OPT_UNSUBSCRIBE_SYMBOL, sizeof(TMsgReqUnsubscribeSymbol)){}
	TMsgReqOptUnsubscribeSymbol(const unsigned __int64& symbol):TMessageSymbol(symbol, M_REQ_OPT_UNSUBSCRIBE_SYMBOL, sizeof(TMsgReqUnsubscribeSymbol)){}
};

class TMsgOptResetSymbol : public TMsgOptionSymbol
{
public:
	TMsgOptResetSymbol(const char* const& symbol, const unsigned __int64& optionBlock):
		TMsgOptionSymbol(symbol, optionBlock, M_OPT_RESET_SYMBOL, sizeof(TMsgOptResetSymbol))
	{
	}
	TMsgOptResetSymbol(const unsigned __int64& symbol, const unsigned __int64& optionBlock):
		TMsgOptionSymbol(symbol, optionBlock, M_OPT_RESET_SYMBOL, sizeof(TMsgOptResetSymbol))
	{
	}
};

class TMsgOptEndOfDaySummaryReport : public TMessageOption
{
public:
	TMsgOptEndOfDaySummaryReport(const char* const& symbol,
		const unsigned int& time,
		const OptionBlock& optionBlock,
		const unsigned int& openPriceDollars,
		const unsigned int& openPriceFraction,
		const unsigned int& highPriceDollars,
		const unsigned int& highPriceFraction,
		const unsigned int& lowPriceDollars,
		const unsigned int& lowPriceFraction,
		const unsigned int& lastPriceDollars,
		const unsigned int& lastPriceFraction,

		const int& netChangeDollars,
		const int& netChangeFraction,
		const unsigned int& underlyingPriceDollars,
		const unsigned int& underlyingPriceFraction,
		const unsigned int& bidPriceDollars,
		const unsigned int& bidPriceFraction,
		const unsigned int& askPriceDollars,
		const unsigned int& askPriceFraction,
		const unsigned int& volume,
		const unsigned int& openInterestVolume):
		TMessageOption(symbol, time, optionBlock, M_OPT_EOD_SUMMARY_REPORT, sizeof(TMsgEndOfDaySummaryReport)),
		m_openPriceDollars(openPriceDollars),
		m_openPriceFraction(openPriceFraction),
		m_highPriceDollars(highPriceDollars),
		m_highPriceFraction(highPriceFraction),
		m_lowPriceDollars(lowPriceDollars),
		m_lowPriceFraction(lowPriceFraction),
		m_lastPriceDollars(lastPriceDollars),
		m_lastPriceFraction(lastPriceFraction),

		m_netChangeDollars(netChangeDollars),
		m_netChangeFraction(netChangeFraction),
		m_underlyingPriceDollars(underlyingPriceDollars),
		m_underlyingPriceFraction(underlyingPriceFraction),
		m_bidPriceDollars(bidPriceDollars),
		m_bidPriceFraction(bidPriceFraction),
		m_askPriceDollars(askPriceDollars),
		m_askPriceFraction(askPriceFraction),
		m_volume(volume),
		m_openInterestVolume(openInterestVolume)
	{
	}

	unsigned int m_openPriceDollars;
	unsigned int m_openPriceFraction;
	unsigned int m_highPriceDollars;
	unsigned int m_highPriceFraction;
	unsigned int m_lowPriceDollars;
	unsigned int m_lowPriceFraction;
	unsigned int m_lastPriceDollars;
	unsigned int m_lastPriceFraction;

	int m_netChangeDollars;
	int m_netChangeFraction;
	unsigned int m_underlyingPriceDollars;
	unsigned int m_underlyingPriceFraction;
	unsigned int m_bidPriceDollars;
	unsigned int m_bidPriceFraction;
	unsigned int m_askPriceDollars;
	unsigned int m_askPriceFraction;
	unsigned int m_volume;
	unsigned int m_openInterestVolume;
};

class TMsgOptPreviousDayClose : public TMessageOption
{
public:
	TMsgOptPreviousDayClose(const char* const& symbol = "",
		const unsigned int& time = 0,
		const OptionBlock& optionBlock = OptionBlock(0),
		const unsigned int& closePriceDollar = 0,
		const unsigned int& closePriceFraction = 0):
		TMessageOption(symbol, time, optionBlock, M_OPT_PREVIOUS_DAY_CLOSE, sizeof(TMsgOptPreviousDayClose)),
		m_closePriceDollar(closePriceDollar),
		m_closePriceFraction(closePriceFraction)
	{
	}
	unsigned int m_closePriceDollar;
	unsigned int m_closePriceFraction;
};

class TMsgUnderlierInvalid : public TMessageSymbol
{
public:
	TMsgUnderlierInvalid(const char* const& symbol):TMessageSymbol(symbol, TM_UNDERLIER_INVALID, sizeof(TMsgUnderlierInvalid)){}
	TMsgUnderlierInvalid(const unsigned __int64& symbol = 0):TMessageSymbol(symbol, TM_UNDERLIER_INVALID, sizeof(TMsgUnderlierInvalid)){}
};

class TMsgUnderlierRefreshed : public TMessageSymbol
{
public:
	TMsgUnderlierRefreshed(const char* const& symbol):TMessageSymbol(symbol, TM_UNDERLIER_REFRESHED, sizeof(TMsgUnderlierRefreshed)){}
	TMsgUnderlierRefreshed(const unsigned __int64& symbol = 0):TMessageSymbol(symbol, TM_UNDERLIER_REFRESHED, sizeof(TMsgUnderlierRefreshed)){}
};

class TMsgOptionUpdate : public TMessageStockUpdate
{
public:
//	OptionKey m_optionKey;
	unsigned __int64 m_optionBlock;
protected:
//	TMsgOptionUpdate(const char* symbol, const OptionKey& optionKey, unsigned int updateOrdinal, unsigned short type, unsigned short length):TMessageStockUpdate(symbol, updateOrdinal, type, length), m_optionKey(optionKey){}
//	TMsgOptionUpdate(const unsigned __int64& symbol, const OptionKey& optionKey, unsigned int updateOrdinal, unsigned short type, unsigned short length):TMessageStockUpdate(symbol, updateOrdinal, type, length), m_optionKey(optionKey){}
	TMsgOptionUpdate(const char* const& symbol, const unsigned __int64& optionBlock, const unsigned int& updateOrdinal, const unsigned short& type, const unsigned short& length):TMessageStockUpdate(symbol, updateOrdinal, type, length), m_optionBlock(optionBlock){}
	TMsgOptionUpdate(const unsigned __int64& symbol, const unsigned __int64& optionBlock, const unsigned int& updateOrdinal, const unsigned short& type, const unsigned short& length):TMessageStockUpdate(symbol, updateOrdinal, type, length), m_optionBlock(optionBlock){}
};

class TMsgOptionUpdateLevel2 : public TMsgOptionUpdate
{
public:
//	TMsgOptionUpdateLevel2(const char* symbol, const OptionKey& optionKey, unsigned int updateOrdinal):TMsgOptionUpdate(symbol, optionKey, updateOrdinal, TM_OPTION_UPDATE_LEVEL2, sizeof(TMsgOptionUpdateLevel2)){}
//	TMsgOptionUpdateLevel2(const unsigned __int64& symbol, const OptionKey& optionKey, unsigned int updateOrdinal):TMsgOptionUpdate(symbol, optionKey, updateOrdinal, TM_OPTION_UPDATE_LEVEL2, sizeof(TMsgOptionUpdateLevel2)){}
	TMsgOptionUpdateLevel2(const char* const& symbol, const unsigned __int64& optionBlock, const unsigned int& updateOrdinal):TMsgOptionUpdate(symbol, optionBlock, updateOrdinal, TM_OPTION_UPDATE_LEVEL2, sizeof(TMsgOptionUpdateLevel2)){}
	TMsgOptionUpdateLevel2(const unsigned __int64& symbol = 0, const unsigned __int64& optionBlock = 0, const unsigned int& updateOrdinal = 0):TMsgOptionUpdate(symbol, optionBlock, updateOrdinal, TM_OPTION_UPDATE_LEVEL2, sizeof(TMsgOptionUpdateLevel2)){}
};

class TMsgOptionUpdateLevel1 : public TMsgOptionUpdate
{
public:
//	TMsgOptionUpdateLevel1(const char* symbol, const OptionKey& optionKey, bool hasPrints, unsigned int updateOrdinal):TMsgOptionUpdate(symbol, optionKey, updateOrdinal, TM_OPTION_UPDATE_LEVEL1, sizeof(TMsgOptionUpdateLevel1)), m_hasPrints(hasPrints){}
//	TMsgOptionUpdateLevel1(const unsigned __int64& symbol, const OptionKey& optionKey, bool hasPrints, unsigned int updateOrdinal):TMsgOptionUpdate(symbol, optionKey, updateOrdinal, TM_OPTION_UPDATE_LEVEL1, sizeof(TMsgOptionUpdateLevel1)), m_hasPrints(hasPrints){}
	TMsgOptionUpdateLevel1(const char* const& symbol, const unsigned __int64& optionBlock, const bool& hasPrints, const unsigned int& updateOrdinal):TMsgOptionUpdate(symbol, optionBlock, updateOrdinal, TM_OPTION_UPDATE_LEVEL1, sizeof(TMsgOptionUpdateLevel1)), m_hasPrints(hasPrints){}
	TMsgOptionUpdateLevel1(const unsigned __int64& symbol = 0, const unsigned __int64& optionBlock = 0, const bool& hasPrints = false, const unsigned int& updateOrdinal = 0):TMsgOptionUpdate(symbol, optionBlock, updateOrdinal, TM_OPTION_UPDATE_LEVEL1, sizeof(TMsgOptionUpdateLevel1)), m_hasPrints(hasPrints){}
	bool m_hasPrints;
};

class TMsgOptionUsedCountUpdate : public TMessageSymbol
{
public:
	TMsgOptionUsedCountUpdate(const char* const& symbol, const unsigned __int64& optionBlock):TMessageSymbol(symbol, TM_OPTION_USED_COUNT_UPDATE, sizeof(TMsgOptionUsedCountUpdate)), m_optionBlock(optionBlock){}
	TMsgOptionUsedCountUpdate(const unsigned __int64& symbol, const unsigned __int64& optionBlock):TMessageSymbol(symbol, TM_OPTION_USED_COUNT_UPDATE, sizeof(TMsgOptionUsedCountUpdate)), m_optionBlock(optionBlock){}
	unsigned __int64 m_optionBlock;
};

class TMsgOptionRefreshed : public TMsgOptionUpdate
{
public:
//	TMsgOptionRefreshed(const char* symbol, const OptionKey& optionKey, unsigned int updateOrdinal):TMsgOptionUpdate(symbol, optionKey, updateOrdinal, TM_OPTION_REFRESHED, sizeof(TMsgOptionRefreshed)){}
//	TMsgOptionRefreshed(const unsigned __int64& symbol, const OptionKey& optionKey, unsigned int updateOrdinal):TMsgOptionUpdate(symbol, optionKey, updateOrdinal, TM_OPTION_REFRESHED, sizeof(TMsgOptionRefreshed)){}
	TMsgOptionRefreshed(const char* const& symbol, const unsigned __int64& optionBlock, const unsigned int& updateOrdinal):TMsgOptionUpdate(symbol, optionBlock, updateOrdinal, TM_OPTION_REFRESHED, sizeof(TMsgOptionRefreshed)){}
	TMsgOptionRefreshed(const unsigned __int64& symbol = 0, const unsigned __int64& optionBlock = 0, const unsigned int& updateOrdinal = 0):TMsgOptionUpdate(symbol, optionBlock, updateOrdinal, TM_OPTION_REFRESHED, sizeof(TMsgOptionRefreshed)){}
};

class TMsgOptionInvalid : public TMsgOptionSymbol
{
public:
	TMsgOptionInvalid(const char* const& symbol, const unsigned __int64& optionBlock, const bool& subscribeNextOption = true):
		TMsgOptionSymbol(symbol, optionBlock, TM_OPTION_INVALID, sizeof(TMsgOptionInvalid)),
		m_subscribeNextOption(subscribeNextOption)
	{
	}
	TMsgOptionInvalid(const unsigned __int64& symbol = 0, const unsigned __int64& optionBlock = 0, const bool& subscribeNextOption = true):
		TMsgOptionSymbol(symbol, optionBlock, TM_OPTION_INVALID, sizeof(TMsgOptionInvalid)),
		m_subscribeNextOption(subscribeNextOption)
	{
	}
	bool m_subscribeNextOption;
};

class TMsgOptionClosed : public TMsgOptionSymbol
{
public:
	TMsgOptionClosed(const char* const& symbol, const unsigned __int64& optionBlock) :TMsgOptionSymbol(symbol, optionBlock, TM_OPTION_CLOSED, sizeof(TMsgOptionClosed)){}
	TMsgOptionClosed(const unsigned __int64& symbol, const unsigned __int64& optionBlock) :TMsgOptionSymbol(symbol, optionBlock, TM_OPTION_CLOSED, sizeof(TMsgOptionClosed)){}
};

class TMsgOptionOpened : public TMsgOptionSymbol
{
public:
	TMsgOptionOpened(const char* const& symbol, const unsigned __int64& optionBlock) :TMsgOptionSymbol(symbol, optionBlock, TM_OPTION_OPENED, sizeof(TMsgOptionOpened)){}
	TMsgOptionOpened(const unsigned __int64& symbol, const unsigned __int64& optionBlock) :TMsgOptionSymbol(symbol, optionBlock, TM_OPTION_OPENED, sizeof(TMsgOptionOpened)){}
};
/*
class TMsgPositionUnderlierPrintUpdate : public TMsgPositionOpenPnlUpdate//TMsgAccountStockPositionObject//TMsgPositionOpenPnlUpdate
{
public:
protected:
	TMsgPositionUnderlierPrintUpdate(const char* const& accountName, const unsigned __int64& symbol, const Price& price, const unsigned __int64& optionBlock, const unsigned short& type, const unsigned short& length):
		TMsgPositionOpenPnlUpdate(accountName, symbol, price, optionBlock, type, length)
	{
	}
};
*/
class TMsgPositionUnderlierPrintUpdate : public TMsgPositionOpenPnlUpdate
{
public:
	TMsgPositionUnderlierPrintUpdate(const char* const& accountName = "",
		const unsigned __int64& symbol = 0,
		const Price& price = Price::priceZero,
		const unsigned __int64& optionBlock = 0,
		const unsigned char& securityType = 0) :
		TMsgPositionOpenPnlUpdate(accountName, symbol, price, optionBlock, securityType, TM_POSITION_UNDERLIER_PRINT, sizeof(TMsgPositionUnderlierPrintUpdate))
	{
	}
};

/*
class TMsgLongPositionUnderlierPrintUpdate : public TMsgPositionOpenPnlUpdate
{
public:
	TMsgLongPositionUnderlierPrintUpdate(const char* const& accountName = "", const unsigned __int64& symbol = 0, const Price& price = Price::priceZero, const unsigned __int64& optionBlock = 0):
		TMsgPositionOpenPnlUpdate(accountName, symbol, price, optionBlock, TM_LONG_POSITION_UNDERLIER_PRINT, sizeof(TMsgLongPositionUnderlierPrintUpdate))
	{
	}
};

class TMsgShortPositionUnderlierPrintUpdate : public TMsgPositionOpenPnlUpdate
{
public:
	TMsgShortPositionUnderlierPrintUpdate(const char* const& accountName = "", const unsigned __int64& symbol = 0, const Price& price = Price::priceZero, const unsigned __int64& optionBlock = 0):
		TMsgPositionOpenPnlUpdate(accountName, symbol, price, optionBlock, TM_SHORT_POSITION_UNDERLIER_PRINT, sizeof(TMsgShortPositionUnderlierPrintUpdate))
	{
	}
};
*/

class TMsgReqFutRefreshSymbol : public TMessageSymbol
{
public:
	TMsgReqFutRefreshSymbol(const char* const& symbol, const unsigned char& flags, const unsigned char& blockSize, const unsigned int& requestId):
		TMessageSymbol(symbol, M_REQ_FUT_REFRESH_SYMBOL, sizeof(TMsgReqFutRefreshSymbol)),
		m_flags(flags),
		m_blockSize(blockSize),
		m_requestId(requestId)
	{
	}
	TMsgReqFutRefreshSymbol(const unsigned __int64& symbol, const unsigned char& flags, const unsigned char& blockSize, const unsigned int& requestId):
		TMessageSymbol(symbol, M_REQ_FUT_REFRESH_SYMBOL, sizeof(TMsgReqFutRefreshSymbol)),
		m_flags(flags),
		m_blockSize(blockSize),
		m_requestId(requestId)
	{
	}
/*
	enum : unsigned char
	{
		UpdatesOnly = 0,
		SubscribeSymbol = 1,
		RefreshAll = 0xff,
	};
*/
	unsigned char m_flags;
	unsigned char m_blockSize;
	unsigned int m_requestId;
};

class TMsgReqFutUnsubscribeSymbol : public TMessageSymbol
{
public:
	TMsgReqFutUnsubscribeSymbol(const char* const& symbol):TMessageSymbol(symbol, M_REQ_FUT_UNSUBSCRIBE_SYMBOL, sizeof(TMsgReqFutUnsubscribeSymbol)){}
	TMsgReqFutUnsubscribeSymbol(const unsigned __int64& symbol):TMessageSymbol(symbol, M_REQ_FUT_UNSUBSCRIBE_SYMBOL, sizeof(TMsgReqFutUnsubscribeSymbol)){}
};

class TMsgFutureUsedCountUpdate : public TMessageSymbol
{
public:
	TMsgFutureUsedCountUpdate(const char* const& symbol):TMessageSymbol(symbol, TM_FUTURE_USED_COUNT_UPDATE, sizeof(TMsgFutureUsedCountUpdate)){}
	TMsgFutureUsedCountUpdate(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_FUTURE_USED_COUNT_UPDATE, sizeof(TMsgFutureUsedCountUpdate)){}
};
/*
class TMsgFutureUpdateLevel1 : public TMessageStockUpdate
{
public:
	TMsgFutureUpdateLevel1(const char* const& symbol, const bool& hasPrints, const unsigned int& updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_FUTURE_UPDATE_LEVEL1, sizeof(TMsgFutureUpdateLevel1)), m_hasPrints(hasPrints){}
	TMsgFutureUpdateLevel1(const unsigned __int64& symbol, const bool& hasPrints, const unsigned int& updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_FUTURE_UPDATE_LEVEL1, sizeof(TMsgFutureUpdateLevel1)), m_hasPrints(hasPrints){}
	bool m_hasPrints;
};
*/
class TMsgFutureUpdateLevel1 : public TMsgStockUpdateHasPrints
{
public:
	TMsgFutureUpdateLevel1(const char* const& symbol, const bool& hasPrints, const unsigned int& updateOrdinal):
		TMsgStockUpdateHasPrints(symbol, hasPrints, updateOrdinal, TM_FUTURE_UPDATE_LEVEL1, sizeof(TMsgFutureUpdateLevel1))
	{
	}
	TMsgFutureUpdateLevel1(const unsigned __int64& symbol, const bool& hasPrints, const unsigned int& updateOrdinal):
		TMsgStockUpdateHasPrints(symbol, hasPrints, updateOrdinal, TM_FUTURE_UPDATE_LEVEL1, sizeof(TMsgFutureUpdateLevel1))
	{
	}
};

class TMsgFutureUpdateLevel2 : public TMessageStockUpdate
{
public:
	TMsgFutureUpdateLevel2(const char* const& symbol, const unsigned int& updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_FUTURE_UPDATE_LEVEL2, sizeof(TMsgFutureUpdateLevel2)){}
	TMsgFutureUpdateLevel2(const unsigned __int64& symbol, const unsigned int& updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_FUTURE_UPDATE_LEVEL2, sizeof(TMsgFutureUpdateLevel2)){}
};

class TMsgFutureRefreshed : public TMessageStockUpdate
{
public:
	TMsgFutureRefreshed(const char* const& symbol, const unsigned int& updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_FUTURE_REFRESHED, sizeof(TMsgFutureRefreshed)){}
	TMsgFutureRefreshed(const unsigned __int64& symbol, const unsigned int& updateOrdinal):TMessageStockUpdate(symbol, updateOrdinal, TM_FUTURE_REFRESHED, sizeof(TMsgFutureRefreshed)){}
};

class TMsgFutureClosed : public TMessageSymbol
{
public:
	TMsgFutureClosed(const char* const& symbol):TMessageSymbol(symbol, TM_FUTURE_CLOSED, sizeof(TMsgFutureClosed)){}
	TMsgFutureClosed(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_FUTURE_CLOSED, sizeof(TMsgFutureClosed)){}
};

class TMsgFutureOpened : public TMessageSymbol
{
public:
	TMsgFutureOpened(const char* const& symbol):TMessageSymbol(symbol, TM_FUTURE_OPENED, sizeof(TMsgFutureOpened)){}
	TMsgFutureOpened(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_FUTURE_OPENED, sizeof(TMsgFutureOpened)){}
};

class TMsgFutureInvalid : public TMessageSymbol
{
public:
	TMsgFutureInvalid(const char* const& symbol):TMessageSymbol(symbol, TM_FUTURE_INVALID, sizeof(TMsgFutureInvalid)){}
	TMsgFutureInvalid(const unsigned __int64& symbol = 0):TMessageSymbol(symbol, TM_FUTURE_INVALID, sizeof(TMsgFutureInvalid)){}
};

class TMsgFutureDelete : public TMsgSecurity
{
public:
	TMsgFutureDelete(const Security* const& security):TMsgSecurity(security, TM_FUTURE_DELETE, sizeof(TMsgFutureDelete)){}
};
/*
class TMsgFutureAdd : public TMessageSymbol
{
public:
	TMsgFutureAdd(const char* const& symbol):TMessageSymbol(symbol, TM_FUTURE_ADD, sizeof(TMsgFutureAdd)){}
	TMsgFutureAdd(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_FUTURE_ADD, sizeof(TMsgFutureAdd)){}
	TMsgFutureAdd():TMessageSymbol(TM_FUTURE_ADD, sizeof(TMsgFutureAdd)){}
};

class TMsgFutureRemove : public TMessageSymbol
{
public:
	TMsgFutureRemove(const char* const& symbol):TMessageSymbol(symbol, TM_FUTURE_REMOVE, sizeof(TMsgFutureRemove)){}
	TMsgFutureRemove(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_FUTURE_REMOVE, sizeof(TMsgFutureRemove)){}
	TMsgFutureRemove():TMessageSymbol(TM_FUTURE_REMOVE, sizeof(TMsgFutureRemove)){}
};
*/
class TMsgFutureAddIdle : public TMessageSymbol
{
public:
	TMsgFutureAddIdle(const char* const& symbol):TMessageSymbol(symbol, TM_FUTURE_ADD_IDLE, sizeof(TMsgFutureAddIdle)){}
	TMsgFutureAddIdle(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_FUTURE_ADD_IDLE, sizeof(TMsgFutureAddIdle)){}
	TMsgFutureAddIdle():TMessageSymbol(TM_FUTURE_ADD_IDLE, sizeof(TMsgFutureAddIdle)){}
};

class TMsgFutureRemoveIdle : public TMessageSymbol
{
public:
	TMsgFutureRemoveIdle(const char* const& symbol):TMessageSymbol(symbol, TM_FUTURE_REMOVE_IDLE, sizeof(TMsgFutureRemoveIdle)){}
	TMsgFutureRemoveIdle(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_FUTURE_REMOVE_IDLE, sizeof(TMsgFutureRemoveIdle)){}
	TMsgFutureRemoveIdle():TMessageSymbol(TM_FUTURE_REMOVE_IDLE, sizeof(TMsgFutureRemoveIdle)){}
};

class TMsgFutureObjectNew : public TMsgSecurity
{
public:
	TMsgFutureObjectNew(const Security* const& security):TMsgSecurity(security, TM_NEW_FUTURE, sizeof(TMsgFutureObjectNew)){}
};

class TMsgNewFuture : public TMessageSymbol
{
public:
	TMsgNewFuture(const char* const& symbol):TMessageSymbol(symbol, TM_FUTURE_NEW, sizeof(TMsgNewFuture)){}
	TMsgNewFuture(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_FUTURE_NEW, sizeof(TMsgNewFuture)){}
};

class TMsgAllFutureAccountsLoaded : public Message
{
public:
	TMsgAllFutureAccountsLoaded():Message(TM_ALL_FUTURE_ACCOUNTS_LOADED, sizeof(TMsgAllFutureAccountsLoaded)){}
};

class TMsgDeleteAllFutureAccounts : public Message
{
public:
	TMsgDeleteAllFutureAccounts():Message(TM_DELETE_ALL_FUTURE_ACCOUNTS, sizeof(TMsgDeleteAllFutureAccounts)){}
};


////////////////////////
class TMsgFutBookModifyQuote : public TMessageSymbol
{
public:
	TMsgFutBookModifyQuote(const char* const& symbol = "",
		const unsigned char& side = Buy,
		const unsigned __int64& referenceNumber = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned int& size = 0,
		const unsigned int& mmid = 0,
		const unsigned int& millisecond = 0,
		const unsigned char& bookID = 0,//	: 8;
		const unsigned char& quoteCondition = 0,//	: 8;
		const unsigned short& flags = 0):
		TMessageSymbol(symbol, M_FUT_BOOK_MODIFY_QUOTE, sizeof(TMsgFutBookModifyQuote)),
		m_side(side),
		m_quote(referenceNumber, priceDollars, priceFraction, size, mmid, millisecond, bookID, quoteCondition, flags)
	{
	}
	unsigned char m_side;
	MsgQuote m_quote;

};

class TMsgFutBookDeleteQuote : public TMessageTimeSymbol
{
public:
	TMsgFutBookDeleteQuote(const char* const& symbol = "",
		const unsigned int& millisecond = 0,
		const unsigned int priceDollars = 0,
		const unsigned int priceFraction = 0,
		const unsigned __int64& referenceNumber = 0,
		const unsigned char& side = Buy,
		const unsigned char& bookID = 0):
		TMessageTimeSymbol(symbol, millisecond, M_FUT_BOOK_DELETE_QUOTE, sizeof(TMsgFutBookDeleteQuote)),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_referenceNumber(referenceNumber),
		m_side(side),
		m_bookID(bookID)
	{
	}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned __int64 m_referenceNumber;
	unsigned char m_side;
	unsigned char m_bookID;
};
/*
class CMsgFutBookDeleteQuote : public ASKSoft::Framework::CMessage
{
public:
	CMsgFutBookDeleteQuote( ASKSoft::Framework::CTimeOfDay time, const Symbol& symbol, const Price& price, ULONGLONG referenceNumber, Side side, BookID bookID )
		: ASKSoft::Framework::CMessage( M_FUT_BOOK_DELETE_QUOTE, sizeof( CMsgFutBookDeleteQuote ) )
		, m_time( time )
		, m_symbol( symbol )
		, m_price( price )
		, m_referenceNumber( referenceNumber )
		, m_side( side )
		, m_bookID( bookID )
	{
	}

	ASKSoft::Framework::CTimeOfDay	m_time;
	Symbol							m_symbol;
	Price							m_price;
	ULONGLONG						m_referenceNumber;
	Side							m_side;
	BookID							m_bookID;
};
*/

class TMsgFutLevel1 : public TMessageTimeSymbol
{
public:
	TMsgFutLevel1(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned int& bidPriceDollars = 0,
		const unsigned int& bidPriceFraction = 0,
		const unsigned int& askPriceDollars = 0,
		const unsigned int& askPriceFraction = 0,
		const unsigned int& bidSize = 0,
		const unsigned int& askSize = 0,
		const unsigned char& bidMarketCenter = 0,
		const unsigned char& askMarketCenter = 0,
		const unsigned char& quoteCondition = 0,
		const unsigned char& flags = 0):
		TMessageTimeSymbol(symbol, time, M_FUT_LEVEL1, sizeof(TMsgFutLevel1)),
		m_bidPriceDollars(bidPriceDollars),
		m_bidPriceFraction(bidPriceFraction),
		m_askPriceDollars(askPriceDollars),
		m_askPriceFraction(askPriceFraction),
		m_bidSize(bidSize),
		m_askSize(askSize),
		m_bidMarketCenter(bidMarketCenter),
		m_askMarketCenter(askMarketCenter),
		m_quoteCondition(quoteCondition),
		m_flags(flags)
	{
	}
	unsigned int m_bidPriceDollars;
	unsigned int m_bidPriceFraction;
	unsigned int m_askPriceDollars;
	unsigned int m_askPriceFraction;
	unsigned int m_bidSize;
	unsigned int m_askSize;
	unsigned char m_bidMarketCenter;
	unsigned char m_askMarketCenter;
	unsigned char m_quoteCondition;
	unsigned char m_flags;
};

class HistoricalFuturePrint
{
public:
	HistoricalFuturePrint(const unsigned int& priceDollar,
		const unsigned int& priceFraction,
		const unsigned int& vwapDollar,
		const unsigned int& vwapFraction,
		const unsigned int& time,
		const unsigned int& size,
		const unsigned char& saleCondition,
		const unsigned char& marketCenter,
		const unsigned char& printFlags):
		m_priceDollar(priceDollar),
		m_priceFraction(priceFraction),
		m_vwapDollar(vwapDollar),
		m_vwapFraction(vwapFraction),
		m_size(size),
		m_time(time),
		m_marketCenterID(marketCenter),
		m_saleCondition(saleCondition),
		m_printFlags(printFlags)
	{
	}
	unsigned int m_priceDollar;
	unsigned int m_priceFraction;
	unsigned int m_vwapDollar;
	unsigned int m_vwapFraction;
	unsigned __int64 m_referenceNumber;
	unsigned int m_size;
	unsigned int m_time;
	unsigned char m_marketCenterID;
	unsigned char m_saleCondition;//m_tradeCondition
	unsigned char m_printFlags;
};



enum FutureTradeReportFlags : unsigned char
{
	FutNoPriceChanges = 0,
	FutLastPriceChanged = 1,
	FutLowPriceChanged = 2,
	FutHighPriceChanged = 4,
	FutOpeningTrade = 8,
	FutNewIntraDayTick = 0x80,
};

class TMsgFutTrade : public TMessageTimeSymbol
{
public:
	TMsgFutTrade(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned __int64& referenceNumber = 0,
		const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned int& vwapDollars = 0,
		const unsigned int& vwapFraction = 0,
		const unsigned int& size = 0,
		const unsigned char& marketCenterID = 0,
		const char& saleCondition = 0,
		const char& primaryListingMarket = 0,
		const unsigned char& flags = 0) :
		TMessageTimeSymbol(symbol, time, M_FUT_TRADE_REPORT, sizeof(TMsgFutTrade)),
		m_referenceNumber(referenceNumber),
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_vwapDollars(vwapDollars),
		m_vwapFraction(vwapFraction),
		m_size(size),
		m_marketCenterID(marketCenterID),
		m_saleCondition(saleCondition),
		m_flags(flags)
	{
	}
	unsigned __int64 m_referenceNumber;
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_vwapDollars;
	unsigned int m_vwapFraction;
	unsigned int m_size;
	unsigned char m_marketCenterID;
	unsigned char m_saleCondition;
	unsigned char m_flags;
};

class TMsgFutOpenInterest : public TMessageTimeSymbol
{
public:
	TMsgFutOpenInterest(const char* const& symbol,
		const unsigned int& time,
//		const unsigned __int64& openInterestVolume):
		const unsigned int& openInterestVolume):
		TMessageTimeSymbol(symbol, time, M_FUT_OPEN_INTEREST, sizeof(TMsgFutOpenInterest)),
		m_openInterestVolume(openInterestVolume)
	{
	}
	unsigned int m_openInterestVolume;
};
/*
enum FutureRefreshStatus : unsigned char
{
	REFRESH_Snapshot = 0x10,
	REFRESH_EndOfBlock = 0x20,
	REFRESH_EndOfRefresh = 0x40,
	REFRESH_RefreshFailed = 0x80,
};
*/
class TMsgRespFutRefreshSymbol : public Message
{
public:
	TMsgRespFutRefreshSymbol(const unsigned short& dataSize = 0,
		const unsigned int& requestId = 0,
		const char* const& symbol = "",
		const unsigned char& steps = 0,
		const unsigned char& flags = 0,
		const unsigned char& bookID = 0,
		const char& marketStatus = 0) :
		Message(M_RESP_FUT_REFRESH_SYMBOL, dataSize),
		m_requestID(requestId),
		m_steps(steps),
		m_flags(flags)
	{
		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}
	unsigned int	m_requestID;
	Symbol			m_symbol;
	unsigned char	m_steps;
	unsigned char	m_flags;
};

class TMsgFutResetSymbol : public TMessageSymbol
{
public:
	TMsgFutResetSymbol(const char* const& symbol, const bool& level2 = false) :TMessageSymbol(symbol, M_FUT_RESET_SYMBOL, sizeof(TMsgFutResetSymbol)), m_level2(level2){}
	TMsgFutResetSymbol(const unsigned __int64& symbol = 0, const bool& level2 = false) :TMessageSymbol(symbol, M_FUT_RESET_SYMBOL, sizeof(TMsgFutResetSymbol)), m_level2(level2){}
//	unsigned char m_bookId;
	bool m_level2;
};

class TMsgFutEndOfDaySummaryReport : public TMessageTimeSymbol
{
public:
	TMsgFutEndOfDaySummaryReport(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& todaysClosePriceDollar,
		const unsigned int& todaysClosePriceFraction,
		const unsigned __int64& volume,
		const unsigned short& type,
		const unsigned short& length):
		
		TMessageTimeSymbol(symbol, time, M_FUT_EOD_SUMMARY_REPORT, sizeof(TMsgFutEndOfDaySummaryReport)),
		m_todaysClosePriceDollar(todaysClosePriceDollar),
		m_todaysClosePriceFraction(todaysClosePriceFraction),
		m_volume(volume)
	{
	}
	unsigned int m_todaysClosePriceDollar;
	unsigned int m_todaysClosePriceFraction;
    unsigned __int64 m_volume;
};

class TMsgFutPreviousDayClose : public TMsgPreviousDayCloseBase
{
public:
	TMsgFutPreviousDayClose(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned int& closePriceDollar = 0,
		const unsigned int& closePriceFraction = 0):
		TMsgPreviousDayCloseBase(symbol,
			time,
			closePriceDollar,
			closePriceFraction,
			M_FUT_PREVIOUS_DAY_CLOSE,
			sizeof(TMsgFutPreviousDayClose))
	{
	}
};

class TMsgFutTradingAction : public TMessageTimeSymbol
{
public:
	TMsgFutTradingAction(const char* const& symbol = "",
		const unsigned int& time = 0,
		unsigned char instrumentStatus = 0,
		unsigned char instrumentStatus2 = 0,
		unsigned char instrumentEvent = 0,
		unsigned char reasonCode = 0,
		unsigned char tradableStatus = 0,
		unsigned char marketPhase = 0):
		TMessageTimeSymbol(symbol, time, M_FUT_TRADING_ACTION, sizeof(TMsgFutTradingAction)),
		m_instrumentStatus(instrumentStatus),
		m_instrumentStatus2(instrumentStatus2),
		m_instrumentEvent(instrumentEvent),
		m_reasonCode(reasonCode),
		m_tradableStatus(tradableStatus),
		m_marketPhase(marketPhase)
	{
	}
	unsigned char m_instrumentStatus;
	unsigned char m_instrumentStatus2;
	unsigned char m_instrumentEvent;
	unsigned char m_reasonCode;
	unsigned char m_tradableStatus;
	unsigned char m_marketPhase;
};

class TMsgFutLuld : public TMsgHighLowBase
{
public:
	TMsgFutLuld(const char* const& symbol = "",
		const unsigned int& time = 0,
		const unsigned int& lowDollar = 0,
		const unsigned int& lowFraction = 0,
		const unsigned int& highDollar = 0,
		const unsigned int& highFraction = 0):
		TMsgHighLowBase(symbol, time, lowDollar, lowFraction, highDollar, highFraction, M_FUT_LULD_PRICE_BAND, sizeof(TMsgFutLuld))
	{
	}
};


class TMsgReqFutChart : public TMessageSymbolRequest
{
public:
	TMsgReqFutChart(const char* const& symbol, const unsigned int& requestId = 0):
		TMessageSymbolRequest(symbol, requestId, M_REQ_FUT_CHART, sizeof(TMsgReqFutChart))
	{
	}
	TMsgReqFutChart(const unsigned __int64& symbol = 0, const DWORD& requestId = 0):
		TMessageSymbolRequest(symbol, requestId, M_REQ_FUT_CHART, sizeof(TMsgReqFutChart))
	{
	}
};

class MsgFutChartPoint
{
public:
	MsgFutChartPoint():
		m_volume(0)
	{
	}
	Price m_first;
	Price m_last;
	Price m_high;
	Price m_low;
	unsigned int m_volume;
};

class TMsgRespFutChart : public TMessageRespChartBase
{
public:
	TMsgRespFutChart(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const unsigned short& minute = 0,
		const unsigned char& tickSize = sizeof(MsgFutChartPoint),
		const unsigned short& ticks = 0,
		const bool& done = false):
		TMessageRespChartBase(symbol, requestId, minute, tickSize, ticks, done, M_RESP_FUT_CHART, sizeof(TMsgRespFutChart))
	{
	}
};

class MsgFutPriceVolumePoint
{
public:
	MsgFutPriceVolumePoint():
		m_volume(0)
	{
	}
	Price m_price;
	unsigned int m_volume;
};

class TMsgRespFutPriceVolume : public TMessageSymbolRequest
{
public:
	TMsgRespFutPriceVolume(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const unsigned char& tickSize = sizeof(MsgFutPriceVolumePoint),
		const unsigned short& ticks = 0,
		const bool& done = true) :
		TMessageSymbolRequest(symbol, requestId, M_RESP_FUT_PRICE_VOLUME, sizeof(TMsgRespFutPriceVolume) + ticks * tickSize),
		m_tickSize(tickSize),
		m_done(done)
	{
	}
//	unsigned int m_requestId;
	unsigned char m_tickSize;
	bool m_done;
};

class TMsgFutSettlementPrice : public TMessageTimeSymbol
{
public:
	TMsgFutSettlementPrice(const char* const& symbol,
		const unsigned int& time,
		const unsigned int& settlementPriceDollars,
		const unsigned int& settlementPriceFraction):
		TMessageTimeSymbol(symbol, time, M_FUT_SETTLEMENT_PRICE, sizeof(TMsgFutSettlementPrice)),
		m_settlementPriceDollars(settlementPriceDollars),
		m_settlementPriceFraction(settlementPriceFraction)
	{
	}
	TMsgFutSettlementPrice(const unsigned __int64& symbol,
		const unsigned int& time,
		const unsigned int& settlementPriceDollars,
		const unsigned int& settlementPriceFraction):
		TMessageTimeSymbol(symbol, time, M_FUT_SETTLEMENT_PRICE, sizeof(TMsgFutSettlementPrice)),
		m_settlementPriceDollars(settlementPriceDollars),
		m_settlementPriceFraction(settlementPriceFraction)
	{
	}
	unsigned int m_settlementPriceDollars;
	unsigned int m_settlementPriceFraction;
};

class TMsgReqFutPrints : public TMsgReqPrintsBase
{
public:
	TMsgReqFutPrints(const char* const& symbol,
		const unsigned int& requestId,
		const unsigned short& minute,
		const unsigned __int64& referenceNumber,
		const unsigned char& flags):
		TMsgReqPrintsBase(symbol, requestId, minute, referenceNumber, flags, M_REQ_FUT_PRINTS, sizeof(TMsgReqFutPrints))
	{
	}
};

class FuturePrintData
{
public:
	FuturePrintData(const unsigned int& priceDollars = 0,
		const unsigned int& priceFraction = 0,
		const unsigned int& vwapDollars = 0,
		const unsigned int& vwapFraction = 0,
		const unsigned __int64& referenceNumber = 0,
		const unsigned int& size = 0,
		const unsigned int& time = 0,
		const unsigned char& marketCenterId = 0,
		const unsigned char& tradeCondition = 0,
		const unsigned char& flags = 0):
		m_priceDollars(priceDollars),
		m_priceFraction(priceFraction),
		m_vwapDollars(vwapDollars),
		m_vwapFraction(vwapFraction),
		m_referenceNumber(referenceNumber),
		m_size(size),
		m_time(time),
		m_marketCenterID(marketCenterId),
		m_tradeCondition(tradeCondition),
		m_flags(flags)
	{
	}
	unsigned int m_priceDollars;
	unsigned int m_priceFraction;
	unsigned int m_vwapDollars;
	unsigned int m_vwapFraction;
	unsigned __int64 m_referenceNumber;
	unsigned int m_size;
	unsigned int m_time;
	unsigned char m_marketCenterID;
	unsigned char m_tradeCondition;
	unsigned char m_flags;
};

class TMsgFutPrints : public TMsgPrintsBase
{
public:
	TMsgFutPrints(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const unsigned __int64& nextReferenceNumber = 0,
		const unsigned short& minute = 0,
		const unsigned char& tickSize = sizeof(FuturePrintData),
		const unsigned short& ticks = 0,
		const unsigned char& flags = 0):
		TMsgPrintsBase(symbol, requestId, nextReferenceNumber, minute, tickSize, flags, M_RESP_FUT_PRINTS, sizeof(TMsgFutPrints) + ticks * tickSize)
	{
	}
};

class TMsgReqFutHistoricalData : public TMsgReqCandleData
{
public:
	TMsgReqFutHistoricalData(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const unsigned int& startDate = 0,
		const unsigned int& endDate = 0,
		const unsigned char& frequency = 0) :// 'd' - daily, 'w' - weekly, 'm' - monthly
		TMsgReqCandleData(symbol, requestId, startDate, endDate, frequency, M_REQ_FUT_HISTORICAL_DATA, sizeof(TMsgReqFutHistoricalData))
	{
	}
};

class TMsgFutCandleHistoricalData : public TMessageSymbolRequest
{
public:
	TMsgFutCandleHistoricalData(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const unsigned char& tickSize = sizeof(FutureHistoricalTick),
		const unsigned short& ticks = 0,
		const unsigned char& flags = 0):
		TMessageSymbolRequest(symbol, requestId, M_RESP_FUT_HISTORICAL_DATA, sizeof(TMsgFutCandleHistoricalData) + ticks * tickSize),
		m_tickSize(tickSize),
		m_flags(flags)
	{
	}

	unsigned char m_tickSize;
	unsigned char m_flags;
};

class TMsgReqFutIntradayData : public TMsgReqCandleData
{
public:
	TMsgReqFutIntradayData(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const unsigned int& startDate = 0,
		const unsigned int& endDate = 0,
		const unsigned char& frequency = 0)://'1' - 1 minute, '2' - 5 minutes, '3' - 15 minutes, '4' - 30 minutes, '5' - 1 hour
		TMsgReqCandleData(symbol, requestId, startDate, endDate, frequency, M_REQ_FUT_INTRADAY_DATA, sizeof(TMsgReqFutIntradayData))
	{
	}
};

class TMsgFutCandleIntradayData : public TMessageSymbolRequest
{
public:
	TMsgFutCandleIntradayData(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const unsigned int& date = 0,
		const unsigned char& tickSize = sizeof(FutureHistoricalIntraDayTick),
		const unsigned short& ticks = 0,
		const unsigned char& flags = 0):
		TMessageSymbolRequest(symbol, requestId, M_RESP_FUT_INTRADAY_DATA, sizeof(TMsgFutCandleIntradayData) + ticks * tickSize),
		m_date(date),
		m_tickSize(tickSize),
		m_flags(flags)
	{
	}

	unsigned int m_date;
	unsigned char m_tickSize;
	unsigned char m_flags;
};


class TMsgReqFutHistoricalPriceVolume : public TMsgReqDated
{
public:
	TMsgReqFutHistoricalPriceVolume(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const unsigned int& startDate = 0,
		const unsigned int& endDate = 0):
		TMsgReqDated(symbol, requestId, startDate, endDate, M_REQ_FUT_HISTORICAL_PRICE_VOLUME, sizeof(TMsgReqFutHistoricalPriceVolume))
	{
	}
};

class TMsgRespFutHistoricalPriceVolume : public TMessageSymbolRequest
{
public:
	TMsgRespFutHistoricalPriceVolume(const char* const& symbol = "",
		const unsigned int& requestId = 0,
		const unsigned char& tickSize = sizeof(FutureHistoricalPriceVolumeTick),
		const unsigned short& ticks = 0,
		const unsigned char& flags = 0):
		TMessageSymbolRequest(symbol, requestId, M_RESP_FUT_HISTORICAL_PRICE_VOLUME, sizeof(TMsgRespFutHistoricalPriceVolume) + ticks * tickSize),
		m_tickSize(tickSize),
		m_flags(flags)
	{
	}
/*
	enum Flags : BYTE
	{
		More	= 0x01,
		Failed	= 0x80,
	};
*/
	unsigned char m_tickSize;
	unsigned char m_flags;
};

///////////////
class TMsgFutureChartLoaded : public TMessageChartLoaded
{
public:
	TMsgFutureChartLoaded(const unsigned __int64& symbol, const bool& chartReloaded):
		TMessageChartLoaded(symbol, chartReloaded, TM_FUTURE_CHART_LOADED, sizeof(TMsgFutureChartLoaded))
	{
	}
};

class TMsgFuturePriceVolumeLoaded : public TMessageChartLoaded
{
public:
	TMsgFuturePriceVolumeLoaded(const unsigned __int64& symbol, const bool& chartReloaded):
		TMessageChartLoaded(symbol, chartReloaded, TM_FUTURE_PRICE_VOLUME_LOADED, sizeof(TMsgFutureChartLoaded))
	{
	}
};

class TMsgFutureTimeNbboPrint : public TSmMsgNewTick
{
public:
	TMsgFutureTimeNbboPrint(const unsigned short& symbol = 0, const unsigned char& change = 0):
		TSmMsgNewTick(symbol, change, TM_FUTURE_TIME_NBBO_PRINT, sizeof(TMsgEquityTimeNbboPrint))
	{
	}
};

////////////////////////
#endif
//////////////////////

class TMessageConnection : public Message
{
public:
	unsigned int m_ipAddress;
	unsigned int m_ipBindAddress;
	unsigned short m_port;
	unsigned short m_bindPort;
	unsigned int m_reconnectSeconds;
	bool m_reconnectable;
	unsigned char m_connectionDataType;
	char m_connectionName[24];
protected:
	TMessageConnection(const unsigned short& type, const unsigned short& length,
		const unsigned int& ipAddress,
		const unsigned short& port,
		const unsigned int& ipBindAddress,
		const unsigned short& bindPort,
		const unsigned int& reconnectSeconds,
		const bool& reconnectable,
		const unsigned char& connectionDataType,
		const char* const& connectionName):

		Message(type, length),
		m_ipAddress(ipAddress),
		m_ipBindAddress(ipBindAddress),
		m_port(port),
		m_bindPort(bindPort),
		m_reconnectSeconds(reconnectSeconds),
		m_reconnectable(reconnectable),
		m_connectionDataType(connectionDataType)
	{
		U_CopyAndPad(m_connectionName, sizeof(m_connectionName), connectionName, '\0', true);
	}
};

class TMsgConnected : public TMessageConnection
{
public:
	TMsgConnected(const unsigned int& ipAddress,
		const unsigned short& port,
		const unsigned int& ipBindAddress,
		const unsigned short& bindPort,
		const unsigned int& reconnectSeconds,
		const bool& reconnectable,
		const unsigned char connectionDataType,
		const char* const& connectionName):

		TMessageConnection(TM_CONNECTED, sizeof(TMsgConnected),
			ipAddress,
			port,
			ipBindAddress,
			bindPort,
			reconnectSeconds,
			reconnectable,
			connectionDataType,
			connectionName)
	{
	}
};

class TMsgDisconnected : public TMessageConnection
{
public:
	TMsgDisconnected(const unsigned int& ipAddress,
		const unsigned short& port,
		const unsigned int& ipBindAddress,
		const unsigned short& bindPort,
		const unsigned int& reconnectSeconds,
		const bool& reconnectable,
		const unsigned char& connectionDataType,
		const char* const& connectionName,
		const bool& finalDisconnect = false):

		TMessageConnection(TM_DISCONNECTED, sizeof(TMsgDisconnected),
			ipAddress,
			port,
			ipBindAddress,
			bindPort,
			reconnectSeconds,
			reconnectable,
			connectionDataType,
			connectionName),
		m_finalDisconnect(finalDisconnect)
	{
	}
	bool m_finalDisconnect;
};

class TMsgStartedToConnect : public TMessageConnection
{
public:
	TMsgStartedToConnect(const unsigned int& ipAddress,
		const unsigned short& port,
		const unsigned int& ipBindAddress,
		const unsigned short& bindPort,
		const unsigned int& reconnectSeconds,
		const bool& reconnectable,
		const unsigned char& connectionDataType,
		const char* const& connectionName):

		TMessageConnection(TM_STARTED_TO_CONNECT, sizeof(TMsgStartedToConnect),
			ipAddress,
			port,
			ipBindAddress,
			bindPort,
			reconnectSeconds,
			reconnectable,
			connectionDataType,
			connectionName)
	{
	}
};

class TMsgFailedToConnect : public TMessageConnection
{
public:
	TMsgFailedToConnect(const unsigned int& ipAddress,
		const unsigned short& port,
		const unsigned int& ipBindAddress,
		const unsigned short& bindPort,
		const unsigned int& reconnectSeconds,
		const bool& reconnectable,
		const unsigned char& connectionDataType,
		const char* const& connectionName):

		TMessageConnection(TM_FAILED_TO_CONNECT, sizeof(TMsgFailedToConnect),
			ipAddress,
			port,
			ipBindAddress,
			bindPort,
			reconnectSeconds,
			reconnectable,
			connectionDataType,
			connectionName)
	{
	}
};

class TMsgConnectionDestroyed : public TMessageConnection
{
public:
	TMsgConnectionDestroyed(const unsigned int& ipAddress,
		const unsigned short& port,
		const unsigned int& ipBindAddress,
		const unsigned short& bindPort,
		const unsigned int& reconnectSeconds,
		const bool& reconnectable,
		const unsigned char& connectionDataType,
		const char* const& connectionName,
		const bool& disconnecting):

		TMessageConnection(TM_CONNECTION_DESTROYED, sizeof(TMsgConnectionDestroyed),
			ipAddress,
			port,
			ipBindAddress,
			bindPort,
			reconnectSeconds,
			reconnectable,
			connectionDataType,
			connectionName),
		m_disconnecting(disconnecting)
	{
	}
	bool m_disconnecting;
};

class TMsgClientConnection : public Message
{
public:
	unsigned int m_ip;
	unsigned short m_port;
	unsigned short m_serverPort;
protected:
	TMsgClientConnection(const unsigned int& ip,
		const unsigned short& port,
		const unsigned short& serverPort,
		const unsigned short& type,
		const unsigned short& length):
		Message(type, length),
		m_ip(ip),
		m_port(port),
		m_serverPort(serverPort)
	{
	}
};

class TMsgClientConnected : public TMsgClientConnection
{
public:
	TMsgClientConnected(const unsigned int& ip, const unsigned short& port, const unsigned short& serverPort):
		TMsgClientConnection(ip, port, serverPort, TM_CLIENT_CONNECTED, sizeof(TMsgClientConnected))
	{
	}
};

class TMsgClientDisconnected : public TMsgClientConnection
{
public:
	TMsgClientDisconnected(const unsigned int& ip,
		const unsigned short& port,
		const unsigned short& serverPort,
		const unsigned int& millisecondToSendHeartbeat,
		const unsigned int& millisecondToSendTest):
		TMsgClientConnection(ip, port, serverPort, TM_CLIENT_DISCONNECTED, sizeof(TMsgClientDisconnected)),
		m_millisecondToSendHeartbeat(millisecondToSendHeartbeat),
		m_millisecondToSendTest(millisecondToSendTest)
	{
	}
	unsigned int m_millisecondToSendHeartbeat;
	unsigned int m_millisecondToSendTest;
};

//#define TS_STRUCTURES_MAJOR_VERSION			1
//#define TS_STRUCTURES_MINOR_VERSION			0
/*
#define ENVIRONMENT_TYPE_PRODUCTION		1
#define ENVIRONMENT_TYPE_SIMULATION		2
#define ENVIRONMENT_TYPE_STAGING		3
#define ENVIRONMENT_TYPE_DEVELOPMENT	4
*/
enum ExecutorLogonRequestEnvironment : unsigned int
{
	ENVIRONMENT_TYPE_PRODUCTION =		1,
	ENVIRONMENT_TYPE_SIMULATION =		2,
	ENVIRONMENT_TYPE_STAGING =			3,
	ENVIRONMENT_TYPE_DEVELOPMENT =		4
};

//#define APPLICATION_TYPE_BLAZER			1
//#define APPLICATION_TYPE_API			2

enum ExecutorLogonRequestApplicationType : unsigned int
{
	APPLICATION_TYPE_BLAZER =			1,
	APPLICATION_TYPE_API =				2
};

// *AK*  FLAGS
//#define FLAGS_TCPNoDelay					0x10000
//#define FLAGS_CancelAllOrdersOnDisconnect	0x20000

enum ExecutorLogonRequestFlags : unsigned int
{
	FLAGS_TCPNoDelay = 0x10000,
	FLAGS_CancelAllOrdersOnDisconnect = 0x20000,
	FLAGS_FuturesTSServerLogin = 0x40000,
};

// *AK* 

enum Compression : unsigned int
{
	NoCompression		= 0x00,
	FromClientToServer	= 0x01,
	FromServerToClient	= 0x02,
	FullCompression		= 0x03
};

enum ServerConnectionId : unsigned int
{
	MDLR_MARKET_DATA_STOCK,// = 0,
	MDLR_EXECUTOR_STOCK,// = 1,
	MDLR_MARKET_DATA_OPTION,// = 2,
	MDLR_MARKET_SORTER_STOCK,// = 3,
	MDLR_MARKET_DATA_FUTURE,// = 4,
	MDLR_EXECUTOR_FUTURE,// = 5,
	MDLR_HISTORICAL_PRINT,// = 6,

	MDLR_Count
};

class TMsgMdReqLogon : public Message
{
public:
	
	TMsgMdReqLogon(const char* const& userId,//4 chars max
		const char* const& password, 
		const char* const& ipAddress,
		const char* const& appVersion, 
		const char* const& loginId,//60 chars max
		const unsigned char* const& passwordHash,
		const unsigned short& passwordHashLength,
		const unsigned int& flags = 0,
		const bool& simulation = true, 
		const unsigned int& compression = NoCompression,
		const unsigned int& requestId = 0):
		Message(M_REQ_MD_LOGON, sizeof(TMsgMdReqLogon)),
		m_flags(flags),
		m_simulation(simulation),
		m_compression(compression),
		m_requestId(requestId),
		m_passwordHashLength(passwordHashLength)
	{
		if(userId)
		U_CopyAndPad(m_userId, sizeof(m_userId), userId, '\0', true);
		else
		memset(m_userId, 0, sizeof(m_userId));

		if(password)
		U_CopyAndPad(m_password, sizeof(m_password), password, '\0', true);
		else
		memset(m_password, 0, sizeof(m_password));

		U_CopyAndPad(m_ipAddress, sizeof(m_ipAddress), ipAddress, '\0', true);
		U_CopyAndPad(m_appVersion, sizeof(m_appVersion), appVersion, '\0', true);

		if(loginId)
		U_CopyAndPad(m_loginId, sizeof(m_loginId), loginId, '\0', true);
		else
		memset(m_loginId, 0, sizeof(m_loginId));
		if(passwordHash)
		{
			if(passwordHashLength < sizeof(m_passwordHash))
			{
				memcpy_s(m_passwordHash, sizeof(m_passwordHash), passwordHash, passwordHashLength);
				memset(m_passwordHash + passwordHashLength, 0, sizeof(m_passwordHash) - passwordHashLength);
			}
			else
			{
				memcpy_s(m_passwordHash, sizeof(m_passwordHash), passwordHash, sizeof(m_passwordHash));
			}
		}
		else
		{
			memset(m_passwordHash, 0, sizeof(m_passwordHash));
		}
	}

	char			m_userId[5];
	char			m_password[33];
	char			m_ipAddress[33];
	char			m_appVersion[25];
	unsigned int	m_flags;
	bool			m_simulation;
	unsigned int	m_compression;
	unsigned int	m_requestId;

	char			m_loginId[MAX_EMAILADDRESS_SIZE];
	unsigned char	m_passwordHash[MAX_PASSWORDHASH_SIZE];
	unsigned short m_passwordHashLength;
};

/* 
enum MdEntitlements : unsigned __int64
{
	MDE_NSDQ = 0x0000000000000001,
	MDE_ARCA = 0x0000000000000002,
	MDE_BATS = 0x0000000000000004,
	MDE_BATY = 0x0000000000000008,
	MDE_EDGA = 0x0000000000000010,
	MDE_EDGX = 0x0000000000000020,
	MDE_UQDF = 0x0000000000000040,
	MDE_UTDF = 0x0000000000000080,
	MDE_CQS  = 0x0000000000000100,
	MDE_CTS  = 0x0000000000000200,
	MDE_NYSE = 0x0000000000000400,
	MDE_AMEX = 0x0000000000000800,
};
*/
class TMsgMdLogonResponse : public Message
{
public:
	
	TMsgMdLogonResponse(const char* const& userId = "",
		const char* const& serverVersion = "",
		const unsigned int& flags = SUCCEEDED,
		const bool& reserved = true,
		const unsigned int& compression = NoCompression,
		const unsigned int& requestId = 0,
		const unsigned __int64& marketDataEntitlements = 0,
		const unsigned __int64& extMarketDataEntitlements = 0,
		const unsigned int& userType = 0,
		const unsigned short& rejectReason = 0):
		Message(M_RESP_MD_LOGON, sizeof(TMsgMdLogonResponse)),
		m_flags(flags),
		m_reserved(reserved),
		m_compression(compression),
		m_requestId(requestId),
		m_marketDataEntitlements(marketDataEntitlements),
		m_extMarketDataEntitlements(extMarketDataEntitlements),
		m_userType(userType),
		m_rejectReason(rejectReason)
	{
		U_CopyAndPad(m_userId, sizeof(m_userId), userId, '\0', true);
		U_CopyAndPad(m_serverVersion, sizeof(m_serverVersion), serverVersion, '\0', true);
	}

	enum : unsigned int
	{
		SUCCEEDED	= 0,
		TIMED_OUT,
		DISABLE_EXTENSIONS = 0x10000000,
		FORCE_MS_SUBSCRIPTION_ONLY = 0x20000000,
		SUBSCRIPTION_ONLY = 0x40000000,
		FAILED		= 0x80000000,
		ERROR_MASK	= FAILED | 0xFF,
	};
	
	char				m_userId[5];
	char				m_serverVersion[25];
	unsigned int		m_flags;
	bool				m_reserved;
	unsigned int		m_compression;
	unsigned int		m_requestId;
	unsigned __int64	m_marketDataEntitlements;
	unsigned __int64	m_extMarketDataEntitlements;
	unsigned int		m_userType;
	unsigned short		m_rejectReason;
	char				m_emailAddress[MAX_EMAILADDRESS_SIZE];
	char				m_phoneNumber[MAX_PHONENUMBER_SIZE];
};

class TReqPublicKey : public TMessageRequest
{
public:
	TReqPublicKey(const unsigned int& requestId):
		TMessageRequest(requestId, M_REQ_PUBLIC_KEY, sizeof(TReqPublicKey))
//		m_requestId(requestId)
	{
	}
//	unsigned int m_requestId;
};

class TMsgPublicKey : public TMessageRequest
{
public:
	TMsgPublicKey(const unsigned int& requestId, const unsigned short& blobSize):
		TMessageRequest(requestId, M_RESP_PUBLIC_KEY, sizeof(TMsgPublicKey) + blobSize)
//		m_requestId(requestId)
	{
	}
//	unsigned int m_requestId;
};

class TMsgReqLogonBase : public TMessageTime//Executor logon
{
public:
	WORD			MajorVersion;
	WORD			MinorVersion;
	WORD			Environment;
	WORD			ApplicationType;
	unsigned int	Flags;
	unsigned int	CompressionType;
	char			IPAddress[MAX_IP_ADDRESS_SIZE];
	char			FirmID[MAX_FIRM_ID_SIZE];
	char			UserName[MAX_USERNAME_SIZE];
	char			Password[MAX_PASSWORD_SIZE];
// Support for new login
	char			m_loginId[MAX_EMAILADDRESS_SIZE];
	unsigned char	m_passwordHash[MAX_PASSWORDHASH_SIZE];
	unsigned short m_passwordHashLength;
protected:
	TMsgReqLogonBase(const unsigned int& flags,
		const unsigned int& compressionType,
		const char* const& ipAddress,
		const char* const& firmId,
		const char* const& userName,//4 chars max
		const char* const& password,
		const char* const& loginId,//60 chars max
		const unsigned char* const& passwordHash,
		const unsigned short& passwordHashLength,
		const WORD& applicationType,// = APPLICATION_TYPE_BLAZER,
		const WORD& environment,// = ENVIRONMENT_TYPE_PRODUCTION,
		const WORD& majorVersion,// = TS_STRUCTURES_MAJOR_VERSION,
		const WORD& minorVersion,// = TS_STRUCTURES_MINOR_VERSION):
		const unsigned short& type,
		const unsigned short& length):
		TMessageTime(0, type, length),
		MajorVersion(majorVersion),
		MinorVersion(minorVersion),
		Environment(environment),
		ApplicationType(applicationType),
		Flags(flags),
		CompressionType(compressionType),
		m_passwordHashLength(passwordHashLength)
	{
		U_CopyAndPad(IPAddress, sizeof(IPAddress), ipAddress, '\0', true);
		U_CopyAndPad(FirmID, sizeof(FirmID), firmId, '\0', true);

		memset(UserName, 0, sizeof(UserName));
		if(userName)
		{
			unsigned int userNameLen = MAX_TRADER_ID_SIZE;
			if(userNameLen > sizeof(UserName))userNameLen = sizeof(UserName);
			U_CopyAndPad(UserName, userNameLen, userName, '\0', true);
		}
		if(password)
		U_CopyAndPad(Password, sizeof(Password), password, '\0', true);
		else
		memset(Password, 0, sizeof(Password));

		if(loginId)
		U_CopyAndPad(m_loginId, sizeof(m_loginId), loginId, '\0', true);
		else
		memset(m_loginId, 0, sizeof(m_loginId));

		if(passwordHash)
		{
			if(passwordHashLength < sizeof(m_passwordHash))
			{
				memcpy_s(m_passwordHash, sizeof(m_passwordHash), passwordHash, passwordHashLength);
				memset(m_passwordHash + passwordHashLength, 0, sizeof(m_passwordHash) - passwordHashLength);
			}
			else
			{
				memcpy_s(m_passwordHash, sizeof(m_passwordHash), passwordHash, sizeof(m_passwordHash));
			}
		}
		else
		{
			memset(m_passwordHash, 0, sizeof(m_passwordHash));
		}
	}
};

class TMsgReqLogon : public TMsgReqLogonBase//Executor logon
{
public:
	TMsgReqLogon(const unsigned int& flags,
		const unsigned int& compressionType,
		const char* const& ipAddress,
		const char* const& firmId,
		const char* const& userName,
		const char* const& password,
		const char* const& loginId,//60 chars max
		const unsigned char* const& passwordHash,
		const unsigned short& passwordHashLength,
		const WORD& applicationType,// = APPLICATION_TYPE_BLAZER,
		const WORD& environment,// = ENVIRONMENT_TYPE_PRODUCTION,
		const WORD& majorVersion,// = TS_STRUCTURES_MAJOR_VERSION,
		const WORD& minorVersion):// = TS_STRUCTURES_MINOR_VERSION):
		TMsgReqLogonBase(flags,
			compressionType,
			ipAddress,
			firmId,
			userName,
			password,
			loginId,//60 chars max
			passwordHash,
			passwordHashLength,
			applicationType,
			environment,
			majorVersion,
			minorVersion,
			TS_LOGIN_REQ,
			sizeof(TMsgReqLogon))
	{
	}
};

enum ExecutorLogonRejectReason : unsigned short
{
	LOGIN_REJECT_REASON_INVALID_USERNAME = 1,
	LOGIN_REJECT_REASON_INVALID_PASSWORD,// = 2,
	LOGIN_REJECT_REASON_INVALID_VERSION,// = 3,
	LOGIN_REJECT_REASON_ALREADY_LOGGED_IN,// = 4,
	LOGIN_CAN_ONLY_LOGIN_TO_SUBSCRIPTION_ONLY,
};
/*
#define LOGIN_REJECT_REASON_INVALID_USERNAME	1
#define LOGIN_REJECT_REASON_INVALID_PASSWORD	2
#define LOGIN_REJECT_REASON_INVALID_VERSION		3
#define LOGIN_REJECT_REASON_ALREADY_LOGGED_IN	4
*/
//TS->TSClient, Sent in response to TS_LOGIN_MESSAGE request if the login is rejected

class TMsgReason : public TMessageTime
{
public:
	WORD	Reason;
	char	ReasonText[1];
protected:
	TMsgReason(const WORD& reason, const unsigned short& type, const unsigned short& length):TMessageTime(0, type, length), Reason(reason){*ReasonText = '\0';}
};


class TMsgLogonReject : public TMsgReason
{
public:
	TMsgLogonReject(const WORD& reason):TMsgReason(reason, TS_LOGIN_REJECT, sizeof(TMsgLogonReject)){}
};





//TS sends this message to TSClient in response to TS_LOGIN_MESSAGE
//Logged in user type
enum TakionUserType : unsigned int
{
	USER_TYPE_TRADER = 0x00000001,
	USER_TYPE_OPERATIONS = 0x00000002,
	USER_TYPE_SUPERVISOR = 0x00000004,
	USER_TYPE_FIRM_MANAGER = 0x00000008,
	USER_TYPE_AGGRESSIVE_ODD_LOTS = 0x00000010,
	USER_TYPE_WATCHER = 0x00000020,

	USER_TYPE_ALL = USER_TYPE_TRADER|USER_TYPE_OPERATIONS|USER_TYPE_SUPERVISOR|USER_TYPE_FIRM_MANAGER|USER_TYPE_AGGRESSIVE_ODD_LOTS|USER_TYPE_WATCHER
};
/*
#define	USER_TYPE_TRADER					0x00000001		// Trader
#define	USER_TYPE_OPERATIONS				0x00000002		// Operations
#define	USER_TYPE_SUPERVISOR				0x00000004		// Supervisor
#define	USER_TYPE_FIRM_MANAGER				0x00000008		// Firm Manager
#define	USER_TYPE_AGGRESSIVE_ODD_LOTS		0x00000010
#define	USER_TYPE_WATCHER					0x00000020
*/

enum TraderMiscFlags : unsigned char
{
	TMF_QVV_QSMT,
	TMF_QVV_QADD,
	TMF_QVV_QTAK,

	TMF_QSMT_SMART_SWIPE_DMA,
	TMF_QSMT_AGGRESSIVE_DMA,
	TMF_QSMT_DUMB_SWIPE_DMA,

	TMF_QSMT_ON_OPEN_CLOSE_DMAPLUS,

	TMF_QSMT_SMART_SWIPE_DMAPLUS,
	TMF_QSMT_AGGRESSIVE_DMAPLUS,
	TMF_QSMT_DUMB_SWIPE_DMAPLUS,

	TMF_QSMT_PASSIVE_DMA = 11,

	TMF_APEX_AGGRESSIVE,

#ifdef LYNX_REROUTING
	TMF_LYNX_SMART,
	TMF_LYNX_ON_OPEN_CLOSE,
	TMF_LYNX_PASSIVE,//15
#endif

	TMF_REROUTE_HALTED_THROUGH_BAML,

	TMF_REROUTE_THROUGH_LYNX,//			0x00004000		// Will be performed rerouting through LYNX by BE
	TMF_REROUTE_THROUGH_INSTINET,//		0x00008000		// Will be performed rerouting through INSTINET by BE
	TMF_INSTINET_AGRESSIVE_SCRAPE,//		0x00010000		// Used by BE. Causing prepending tag100 with SOR_

	TMF_REROUTE_THROUGH_VELOCITY_CS,//		0x00020000		// Will be performed stocks rerouting through VELOCITY by BE
	TMF_REROUTE_THROUGH_JPM,//				0x00040000		// Will be performed rerouting through JPM by BE
	TMF_REROUTE_THROUGH_VELOCITY_OPT,//	0x00080000		// Will be performed options rerouting through VELOCITY by BE
	TMF_VELOCITY_AGRESSIVE_SCRAPE,// 0x00100000		// Used by BE. Causing appending tag100 with SOR

	TMF_Count
};

enum AccountProcFlags : unsigned char
{
	APF_TREAT_PASSIVE_ORDERS_AS_AGGRESSIVE,
	APF_ALLOW_ODD_LOT_BORROW,

	APF_Count
};

enum LogonResponseSettings : unsigned __int64//MiscSettings
{
	ForceMSSubscriptionOnly = 0x01,
	DisableExtensions = 0x02,
	FuturesTSServer = 0x8000000000000000,

};
class TMsgLogonResponseBase : public TMessageTime
{
public:
	WORD				NumberOfAccounts;						//This many account messages follow
	DWORD				UserType;								//Specifies the logged in user type
	unsigned __int64	MDEntitlements;							// *AK* Market Data entitlements - DWORD may not be sufficient
	unsigned int		MulticastIP;							// *AK* We can use it if we are going to offer multicast for market data
	unsigned int		MulticastPort;							// *AK*
	char				TraderID[MAX_TRADER_ID_SIZE];			// Should be used in all transactions, should be 4 Capital letters
// *AK* end
	char				Title[MAX_USER_TITLE_SIZE];				//Not sure if we need this, but can be used to give a title to the GUI
//	char				LogonId[MAX_USER_TITLE_SIZE];				//Not sure if we need this, but can be used to give a title to the GUI
	char				DefaultAccount[MAX_ACCOUNT_SIZE];		//Default account for this user
	bool				TradingAllowed;							//m_traderIdEnabled;
	unsigned __int64	MiscSettings;							//Might contain various bit-flags for any random settings we can come up with
	unsigned __int64	ServerVersion;							//1.2.3.4 will be coded as ( (unsigned __int64)1 << 48 ) + ( (unsigned __int64)2 << 32 ) + ( 3 << 16 ) + ( 4 << 0 )
	char				EmailAddress[MAX_EMAILADDRESS_SIZE];	// User's email
	char				PhoneNumber[MAX_PHONENUMBER_SIZE];		// User's Phone number
	char				LoginID[MAX_EMAILADDRESS_SIZE];			// LoginID (long Trader Id)
protected:
	TMsgLogonResponseBase(const unsigned int& time,
		const WORD& numberOfAccounts,
		const DWORD& userType,
		const unsigned __int64& entitlements,
		const unsigned int& multicastIp,
		const unsigned short& multicastPort,
		const char* const& traderId,
		const char* const& title,
		const char* const& defaultAccount,
		const char* const& loginId,//long Trader Id
		const bool& tradingAllowed,//m_traderIdEnabled
		const unsigned __int64& miscSettings,
		const unsigned __int64& serverVersion,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTime(time, type, length),
		NumberOfAccounts(numberOfAccounts),
		UserType(userType),
		MDEntitlements(entitlements),
		MulticastIP(multicastIp),
		MulticastPort(multicastPort),
		TradingAllowed(tradingAllowed),//m_traderIdEnabled
		MiscSettings(miscSettings),
		ServerVersion(serverVersion)
	{
		unsigned int traderIdLen = MAX_TRADER_ID_SIZE;// - 1;
		if(traderIdLen > sizeof(TraderID))traderIdLen = sizeof(TraderID);
		U_CopyAndPad(TraderID, traderIdLen, traderId, '\0', true);

//		U_CopyAndPad(LogonId, sizeof(LogonId), title, '\0');
		U_CopyAndPad(Title, sizeof(Title), title, '\0');

		U_CopyAndPad(DefaultAccount, sizeof(DefaultAccount), defaultAccount, '\0', true);

		U_CopyAndPad(LoginID, sizeof(LoginID), loginId, '\0', true);
	}
};


//TS->TSClient, Sent in response to TS_LOGIN_MESSAGE request if the login is successful
class TMsgLogonResponse : public TMsgLogonResponseBase
{
public:
	TMsgLogonResponse(const unsigned int& time,
		const WORD& numberOfAccounts,
		const DWORD& userType,
		const unsigned __int64& entitlements,
		const unsigned int& multicastIp,
		const unsigned short& multicastPort,
		const char* const& traderId,
		const char* const& title,
		const char* const& defaultAccount,
		const char* const& loginId,//long Trader Id
		const bool& tradingAllowed,//m_traderIdEnabled
		const unsigned __int64& miscSettings,
		const unsigned __int64& serverVersion):
		TMsgLogonResponseBase(time,
			numberOfAccounts,
			userType,
			entitlements,
			multicastIp,
			multicastPort,
			traderId,
			title,
			defaultAccount,
			loginId,
			tradingAllowed,//m_traderIdEnabled
			miscSettings,
			serverVersion,
			TS_LOGIN_RESP,
			sizeof(TMsgLogonResponse))
	{
	}
};

class TMsgReqLogout : public TMsgReason
{
public:
	TMsgReqLogout(const WORD& reason):TMsgReason(reason, TS_LOGOUT_REQ, sizeof(TMsgReqLogout)){}
};

//TS->TSClient, RM->TS, This message may be sent by either TS or a Risk Manager to TSClient upon account profile change or as a part of initally account message
class TMsgAccountRiskProfile : public TMessageTime
{
public:
	TMsgAccountRiskProfile(const unsigned int& time = 0,
		const char* const& accountName = "",
		const char* const& userName = "",
		const double& initialMemberContribution = 0,
		const double& fixedBP = 0,
		const double& overnightMaxValue = 0,//OvernightEquityMultiplier;
		const double& intradayEquityMultiplier = 0,
		const double& dailyPLLimit = 0,
		const double& minEquityAmountAllowed = 0,
		const double& percentEquityLossLimit = 0,
		const double& threshold = 0,
		const DWORD& intradayMaxPosShares = 0,
		const double& intradayMaxPosValue = 0,
		const double& intradayMaxLongValue = 0,
		const double& intradayMaxShortValue = 0,
		const DWORD& overnightMaxPosShares = 0,
		const double& overnightMaxPosValue = 0,
		const double& overnightMaxLongValue = 0,
		const double& overnightMaxShortValue = 0,
		const DWORD& orderProcessingFlags = 0,
		const DWORD& acctProcessingFlags = 0,
		const DWORD& maxOpenPositions = 0,
		const double& maxSharePrice = 0,

//		const double& maxLoss = 0,
		const unsigned optionBlockAggrPricePercent = 0,

		const double& maxLossPerPosition = 0,
		const double& maxOpenLossPerPosition = 0,
		const double& maxLossMarked = 0,
		const double& maxTradedMoney = 0,
		const double& minShortPrice = 0,
		const unsigned int& maxOrderSize = 0,
		const unsigned int& maxPendingOrdersPerPosition = 0,
		const unsigned int& maxSharesTotal = 0,
		const unsigned int& maxSharesTraded = 0,
		const char* const& firmID = "",
		const char& accountType = 0,
		const char& firmType = 0,
		const char* const& groupID_LSTK = "",
		const double& displayMultiplier_LSTK = 0,
		const double& maxOrderValue = 0,
		const double& estBeginningDayEquity = 0,
		const char* const& clearingAccountName = "",//[MAX_ACCOUNT_SIZE];

		const double& maxLossPerPositionClose = 0,
		const double& maxLossPerAccountClose = 0,
		const double& maxLossPerPositionSlack = 0,
		const double& maxLossPerAccountSlack = 0,

		const double& optionBuyingPower = 0,
		const unsigned int& maxOptionSharesTraded = 0,
		const unsigned int& maxOptionOrderSize = 0,
		const double& maxOptionOrderValue = 0,
		const bool& nakedOptionSellAllowed = false,
		const bool& enforceClearingAccountAggregation = false,
		const unsigned int& maxOptionContractsOpen = 0,
		const unsigned int& optionVenue = 0,
		const bool& isoAllowed = false,
		const unsigned int& spoofingOrderCountRatio = 0,
		const unsigned int& spoofingOrderSizeRatio = 0,

		const double& minSharePrice = 0,
		const unsigned int& advOrderCount = 0,
		const unsigned int& advOrderSizePercent = 0,
		const unsigned int& advValue = 0,//2 values above are enforced only if the stock's ADV is lower or equal to ADVValue.
		const unsigned int& forceHiddenBelowADV = 0,
		const unsigned int& rejectBelowADV = 0,
		const unsigned int& blockAggrPricePercent = 0,
		
		const DWORD& maxOrderVenues = 0,
		const unsigned int& maxOrderVenuesTime = 0,
		const DWORD& maxOrderSizeVenues = 0,
		const unsigned int& maxOrderSizeVenuesMultiplier = 0,

		const unsigned int& maxOptionOpenPositions = 0,

		const bool& htbThreshold = false,
		
		const double& niteMaxLoss = 0,
		const double& niteMaxLossExit = 0,
		const double& niteMaxLossSymbolClose = 0,
		const double& niteMaxLossSymbol = 0,
		const double& morningMaxTotalInvestment = 0,
		const double& morningLongInv = 0,
		const double& morningShortInv = 0,
		const double& morningPosInv = 0,
		const DWORD& morningPosShares = 0,
		const double& morningMaxLoss = 0,
		const double& morningMaxLossExit = 0,
		const double& morningMaxLossSymbolClose = 0,
		const double& morningMaxLossSymbol = 0,
		const unsigned int& forceHiddenCloseBelowADV = 0,
		const bool& conservativeOrderMarking = false,
		const bool& localSideMarking = false,
		const bool& poolLocates = false,
		const unsigned int& locateVenue = 0,
		const unsigned int& estBegPctClosePositions = 0,
		const unsigned int& estBegPctCancelOpeningOrders = 0,
		
		const DWORD& futuresVenue = 0,
		const double& futuresEstBeg = 0,					// Futures EstBeginningDayEquity
		const double& futuresBuyingPower = 0,
		const DWORD& maxFuturesPos = 0,
		const double& maxFutureOrderValue = 0,
		const DWORD& maxFutureOrderSize = 0,
		const unsigned int&	maxFuturesContractsOpen = 0,
		const unsigned int& maxFuturesContractsTraded = 0,
		const double& maxFuturesLoss = 0,
		const double& maxFuturesLoss_Fixed = 0,
		const double& maxFuturesLossClose = 0,
		const double& maxFuturesLossClose_Fixed = 0,
		const double& posFuturesLossClose = 0,
		const double& posFuturesLossClose_Fixed = 0,

//		const double& posFuturesLoss_Fixed = 0,
//		const double& maxFuturesLossSymbClose = 0,
//		const double& maxFuturesLossSymbClose_Fixed = 0,
		const DWORD& futuresEstBegPctClosePositions = 0,
		const DWORD& futuresEstBegPctCancelOpeningOrders = 0,

		const bool& forceCancelAndWait = false,
		const bool& disabledBySupervisor = false,
			
		const DWORD& maxOrderVenuesHigh = 0,
		const DWORD& maxOrderSizeVenuesHigh = 0,

		const double& maxHouseMargin = 0,
		const double& maxHouseMarginPerPosition = 0,

		const double& accountBalance = 0
		):

		TMessageTime(time, TS_ACCOUNT_RISK_PROFILE, sizeof(TMsgAccountRiskProfile)),
		InitialMemberContribution(initialMemberContribution),
		FixedBP(fixedBP),
		OvernightMaxValue(overnightMaxValue),//OvernightEquityMultiplier;
		IntradayEquityMultiplier(intradayEquityMultiplier),
		DailyPLLimit(dailyPLLimit),
		MinEquityAmountAllowed(minEquityAmountAllowed),
		PercentEquityLossLimit(percentEquityLossLimit),
		Threshold(threshold),
		IntradayMaxPosShares(intradayMaxPosShares),
		IntradayMaxPosValue(intradayMaxPosValue),
		IntradayMaxLongValue(intradayMaxLongValue),
		IntradayMaxShortValue(intradayMaxShortValue),
		OvernightMaxPosShares(overnightMaxPosShares),
		OvernightMaxPosValue(overnightMaxPosValue),
		OvernightMaxLongValue(overnightMaxLongValue),
		OvernightMaxShortValue(overnightMaxShortValue),
		OrderProcessingFlags(orderProcessingFlags),
		AcctProcessingFlags(acctProcessingFlags),
		MaxOpenPositions(maxOpenPositions),
		MaxSharePrice(maxSharePrice),

//		MaxLoss(maxLoss),
		OptionBlockAggrPricePercent(optionBlockAggrPricePercent),
		Reserved1(0),

		MaxLossPerPosition(maxLossPerPosition),
		MaxOpenLossPerPosition(maxOpenLossPerPosition),
		MaxLossMarked(maxLossMarked),
		MaxTradedMoney(maxTradedMoney),
		MinShortPrice(minShortPrice),
		MaxOrderSize(maxOrderSize),
		MaxPendingOrdersPerPosition(maxPendingOrdersPerPosition),
		MaxSharesTotal(maxSharesTotal),
		MaxSharesTraded(maxSharesTraded),
		AccountType(accountType),
		FirmType(firmType),
		DisplayMultiplier_LSTK(displayMultiplier_LSTK),
		MaxOrderValue(maxOrderValue),
		EstBeginningDayEquity(estBeginningDayEquity),

		MaxLossPerPositionClose(maxLossPerPositionClose),
		MaxLossPerAccountClose(maxLossPerAccountClose),
		MaxLossPerPositionSlack(maxLossPerPositionSlack),
		MaxLossPerAccountSlack(maxLossPerAccountSlack),

		OptionBuyingPower(optionBuyingPower),
		MaxOptionSharesTraded(maxOptionSharesTraded),
		MaxOptionOrderSize(maxOptionOrderSize),
		MaxOptionOrderValue(maxOptionOrderValue),
		NakedOptionSellAllowed(nakedOptionSellAllowed),
		EnforceClearingAccountAggregation(enforceClearingAccountAggregation),
		MaxOptionContractsOpen(maxOptionContractsOpen),
		OptionVenue(optionVenue),
		ISOAllowed(isoAllowed),
		SpoofingOrderCountRatio(spoofingOrderCountRatio),
		SpoofingOrderSizeRatio(spoofingOrderSizeRatio),

		MinSharePrice(minSharePrice),
		ADVOrderCount(advOrderCount),
		ADVOrderSizePercent(advOrderSizePercent),
		ADVValue(advValue),//2 values above are enforced only if the stock's ADV is lower or equal to ADVValue.
		ForceHiddenBelowADV(forceHiddenBelowADV),
		RejectBelowADV(rejectBelowADV),
		BlockAggrPricePercent(blockAggrPricePercent),

		MaxOrderVenues(maxOrderVenues),
		MaxOrderVenuesTime(maxOrderVenuesTime),
		MaxOrderSizeVenues(maxOrderSizeVenues),
		MaxOrderSizeVenuesMultiplier(maxOrderSizeVenuesMultiplier),

		MaxOptionOpenPositions(maxOptionOpenPositions),
		HTBThreshold(htbThreshold),

		NiteMaxLoss(niteMaxLoss),
		NiteMaxLossExit(niteMaxLossExit),
		NiteMaxLossSymbolClose(niteMaxLossSymbolClose),
		NiteMaxLossSymbol(niteMaxLossSymbol),
		MorningMaxTotalInvestment(morningMaxTotalInvestment),
		MorningLongInv(morningLongInv),
		MorningShortInv(morningShortInv),
		MorningPosInv(morningPosInv),
		MorningPosShares(morningPosShares),
		MorningMaxLoss(morningMaxLoss),
		MorningMaxLossExit(morningMaxLossExit),
		MorningMaxLossSymbolClose(morningMaxLossSymbolClose),
		MorningMaxLossSymbol(morningMaxLossSymbol),
		ForceHiddenCloseBelowADV(forceHiddenCloseBelowADV),
		ConservativeOrderMarking(conservativeOrderMarking),
		LocalSideMarking(localSideMarking),
		PoolLocates(poolLocates),
		LocateVenue(locateVenue),
		EstBegPctClosePositions(estBegPctClosePositions),
		EstBegPctCancelOpeningOrders(estBegPctCancelOpeningOrders),

		FuturesVenue(futuresVenue),
		FuturesEstBeg(futuresEstBeg),					// Futures EstBeginningDayEquity
		FuturesBuyingPower(futuresBuyingPower),
		MaxFuturesPos(maxFuturesPos),
		MaxFutureOrderValue(maxFutureOrderValue),
		MaxFutureOrderSize(maxFutureOrderSize),
		MaxFuturesContractsOpen(maxFuturesContractsOpen),
		MaxFuturesContractsTraded(maxFuturesContractsTraded),
		MaxFuturesLoss(maxFuturesLoss),
		MaxFuturesLoss_Fixed(maxFuturesLoss_Fixed),
		MaxFuturesLossClose(maxFuturesLossClose),
		MaxFuturesLossClose_Fixed(maxFuturesLossClose_Fixed),
		PosFuturesLossClose(posFuturesLossClose),
		PosFuturesLossClose_Fixed(posFuturesLossClose_Fixed),

//		PosFuturesLoss_Fixed(posFuturesLoss_Fixed),
//		MaxFuturesLossSymbClose(maxFuturesLossSymbClose),
//		MaxFuturesLossSymbClose_Fixed(maxFuturesLossSymbClose_Fixed),

		FuturesEstBegPctClosePositions(futuresEstBegPctClosePositions),
		FuturesEstBegPctCancelOpeningOrders(futuresEstBegPctCancelOpeningOrders),

		ForceCancelAndWait(forceCancelAndWait),
		DisabledBySupervisor(disabledBySupervisor),

		MaxOrderVenuesHigh(maxOrderVenuesHigh),
		MaxOrderSizeVenuesHigh(maxOrderSizeVenuesHigh),

		MaxHouseMargin(maxHouseMargin),
		MaxHouseMarginPerPosition(maxHouseMarginPerPosition),

		AccountBalance(accountBalance)
	{
		U_CopyAndPad(AccountName, sizeof(AccountName), accountName, '\0', true);

		unsigned int traderIdLen = MAX_TRADER_ID_SIZE;// - 1;
		if(traderIdLen > sizeof(UserName))traderIdLen = sizeof(UserName);
		U_CopyAndPad(UserName, traderIdLen, userName, '\0', true);

		U_CopyAndPad(FirmID, sizeof(FirmID), firmID, '\0', true);
		U_CopyAndPad(GroupID_LSTK, sizeof(GroupID_LSTK), groupID_LSTK, '\0', true);
		U_CopyAndPad(ClearingAccountName, sizeof(ClearingAccountName), clearingAccountName, '\0', true);
	}
	char				AccountName[MAX_ACCOUNT_SIZE];
	char				UserName[MAX_TRADER_SIZE];		//The Risk Manager who might have generated this, or empty if it comes from TS intially
	double				InitialMemberContribution;
	double				FixedBP;
	double				OvernightMaxValue;//OvernightEquityMultiplier;
	double				IntradayEquityMultiplier;
	double				DailyPLLimit;
	double				MinEquityAmountAllowed;
	double				PercentEquityLossLimit;
	double				Threshold;
	DWORD				IntradayMaxPosShares;
	double				IntradayMaxPosValue;
	double				IntradayMaxLongValue;
	double				IntradayMaxShortValue;
	DWORD				OvernightMaxPosShares;
	double				OvernightMaxPosValue;
	double				OvernightMaxLongValue;
	double				OvernightMaxShortValue;
	DWORD				OrderProcessingFlags;
	DWORD				AcctProcessingFlags;
	DWORD				MaxOpenPositions;
	double				MaxSharePrice;

//	double				MaxLoss;
	unsigned int		OptionBlockAggrPricePercent;
	unsigned int		Reserved1;

	double				MaxLossPerPosition;
	double				MaxOpenLossPerPosition;
	double				MaxLossMarked;
	double				MaxTradedMoney;
	double				MinShortPrice;
	unsigned int		MaxOrderSize;
	unsigned int		MaxPendingOrdersPerPosition;
	unsigned int		MaxSharesTotal;
	unsigned int		MaxSharesTraded;
	char				FirmID[MAX_FIRM_ID_SIZE];
	char				AccountType;
	char				FirmType;
	char				GroupID_LSTK[MAX_MMID_SIZE];
	double				DisplayMultiplier_LSTK;
	double				MaxOrderValue;
	double				EstBeginningDayEquity;
	char                ClearingAccountName[MAX_ACCOUNT_SIZE];

	double				MaxLossPerPositionClose;
	double				MaxLossPerAccountClose;
	double				MaxLossPerPositionSlack;
	double				MaxLossPerAccountSlack;

	double				OptionBuyingPower;
	unsigned int		MaxOptionSharesTraded;
	unsigned int		MaxOptionOrderSize;
	double				MaxOptionOrderValue;
	bool				NakedOptionSellAllowed;
	bool				EnforceClearingAccountAggregation;
	unsigned int		MaxOptionContractsOpen;
	unsigned int		OptionVenue;
	bool				ISOAllowed;
	unsigned int		SpoofingOrderCountRatio;
	unsigned int		SpoofingOrderSizeRatio;

	double				MinSharePrice;
	unsigned int		ADVOrderCount;
	unsigned int		ADVOrderSizePercent;
	unsigned int		ADVValue;//2 values above are enforced only if the stock's ADV is lower or equal to ADVValue.
	unsigned int		ForceHiddenBelowADV;
	unsigned int		RejectBelowADV;
	unsigned int		BlockAggrPricePercent;

	DWORD				MaxOrderVenues;
	unsigned int		MaxOrderVenuesTime;
	DWORD				MaxOrderSizeVenues;
	unsigned int		MaxOrderSizeVenuesMultiplier;

	unsigned int		MaxOptionOpenPositions;

	bool				HTBThreshold;

	double				NiteMaxLoss;
	double				NiteMaxLossExit;
	double				NiteMaxLossSymbolClose;
	double				NiteMaxLossSymbol;
	double				MorningMaxTotalInvestment;
	double				MorningLongInv;
	double				MorningShortInv;
	double				MorningPosInv;
	DWORD				MorningPosShares;
	double				MorningMaxLoss;
	double				MorningMaxLossExit;
	double				MorningMaxLossSymbolClose;
	double				MorningMaxLossSymbol;

	unsigned int		ForceHiddenCloseBelowADV;
	bool				ConservativeOrderMarking;
	bool				LocalSideMarking;
	bool				PoolLocates;
	unsigned int		LocateVenue;
	unsigned int		EstBegPctClosePositions;
	unsigned int		EstBegPctCancelOpeningOrders;

	DWORD				FuturesVenue;
	double				FuturesEstBeg;					// Futures EstBeginningDayEquity
	double				FuturesBuyingPower;
	DWORD				MaxFuturesPos;
	double				MaxFutureOrderValue;
	DWORD				MaxFutureOrderSize;
	unsigned int		MaxFuturesContractsOpen;
	unsigned int		MaxFuturesContractsTraded;
	double				MaxFuturesLoss;
	double				MaxFuturesLoss_Fixed;
	double				MaxFuturesLossClose;
	double				MaxFuturesLossClose_Fixed;

//	double				MaxFuturesLossSymbClose;
//	double				MaxFuturesLossSymbClose_Fixed;
	double				PosFuturesLossClose;
	double				PosFuturesLossClose_Fixed;

	DWORD				FuturesEstBegPctClosePositions;
	DWORD				FuturesEstBegPctCancelOpeningOrders;

	bool				ForceCancelAndWait;
	bool				DisabledBySupervisor;

	DWORD				MaxOrderVenuesHigh;
	DWORD				MaxOrderSizeVenuesHigh;

	double				MaxHouseMargin;//Options (TotalHouseMargin)
	double				MaxHouseMarginPerPosition;//Options (PositionHouseMargin)

	double				AccountBalance;
};
//End Transaction Server messages

class TMsgNewAccount : public TMessageTime
{
public:
	TMsgNewAccount(const unsigned int& time = 0,
		const char* const& accountName = "",
		const double& buyingPower = 0,
		const DWORD& executionEntitlementsLow = 0,				//Exchange ECN execution entitlements
		const DWORD& securityEntitlements = 0,				//Security entitlements

//		const DWORD& defaultRoute = 0,						//Defualt route for orders
		const DWORD& executionEntitlementsHigh = 0,						//Defualt route for orders

		const bool& tradingAllowed = 0,						//Flag, whether trading on this account is allowed for specific trader, can be used for view only
		const TMsgAccountRiskProfile& accountRiskProfile = TMsgAccountRiskProfile()):					//Risk Profiles, this message may be passed around in future to control risk during the day between Risk Manager-TS and Front end

		TMessageTime(time, TS_NEW_ACCOUNT, sizeof(TMsgNewAccount)),
		BuyingPower(buyingPower),
		ExecutionEntitlementsLow(executionEntitlementsLow),
		SecurityEntitlements(securityEntitlements),
		
//		DefaultRoute(defaultRoute),
		ExecutionEntitlementsHigh(executionEntitlementsHigh),

		TradingAllowed(tradingAllowed),
		AccountRiskProfile(accountRiskProfile)
	{
		U_CopyAndPad(AccountName, sizeof(AccountName), accountName, '\0', true);
	}
	char							AccountName[MAX_ACCOUNT_SIZE];
	double							BuyingPower;
	DWORD							ExecutionEntitlementsLow;				//Exchange ECN execution entitlements
	DWORD							SecurityEntitlements;				//Security entitlements

//	DWORD							DefaultRoute;						//Defualt route for orders
	DWORD							ExecutionEntitlementsHigh;				//Exchange ECN execution entitlements

	bool							TradingAllowed;						//Flag, whether trading on this account is allowed for specific trader, can be used for view only
	TMsgAccountRiskProfile			AccountRiskProfile;					//Risk Profiles, this message may be passed around in future to control risk during the day between Risk Manager-TS and Front end
};


class TMessageAccountRecoveryBase : public TMessageTime
{
public:
	DWORD						RequestID;
	char						AccountName[MAX_ACCOUNT_SIZE];
protected:
	TMessageAccountRecoveryBase(const unsigned int& time, const DWORD& requestID, const char* const& accountName, const unsigned short& type, const unsigned short& length):
		TMessageTime(time, type, length),
		RequestID(requestID)
	{
		U_CopyAndPad(AccountName, sizeof(AccountName), accountName, '\0', true);
	}
};

//TSClient -> TS, Request for overnight positions
class TMsgReqOvernightPosition : public TMessageAccountRecoveryBase
{
public:
	TMsgReqOvernightPosition(const unsigned int& time, const DWORD& requestID, const char* const& accountName):
		TMessageAccountRecoveryBase(time, requestID, accountName, TS_ACCOUNT_POSITION_REQ, sizeof(TMsgReqOvernightPosition))
	{
	}
};

//TS -> TSClient, TS send a stream of overnight position for the requested account in response to TS_ACCOUNT_OVERNIGHT_POSITION_REQUEST_MESSAGE
// *AK* Message with zero Symbol, InstrumentType, Quantity and AveragePrice can be used to indicate end of transmission instead of
// *AK* TS_ACCOUNT_OVERNIGHT_POSITION_RESPONSE_MESSAGE

class TMsgOvernightPosition : public TMessageAccountRecoveryBase
{
public:
	TMsgOvernightPosition(const unsigned int& time = 0,
		const DWORD& requestID = 0,
		const char* const& accountName = "",
		const char* const& symbol = "",
		const UCHAR& instrumentType = 0,
		const int& quantity = 0,
		const double& averagePrice = 0,

		const unsigned int& borrowedQuantity = 0,
		const double& borrowedAveragePrice = 0,

		const unsigned __int64 optionBlock = 0,
		const char* const& lastLocateExecutionID = ""):

		TMessageAccountRecoveryBase(time, requestID, accountName, TS_ACCOUNT_POSITION, sizeof(TMsgOvernightPosition)),
		InstrumentType(instrumentType),
		Quantity(quantity),
		AveragePrice(averagePrice),
		m_borrowedQuantity(borrowedQuantity),
		m_borrowedAvgPrice(borrowedAveragePrice),
		m_optionBlock(optionBlock)
	{
		U_CopyAndPad(Symbol, sizeof(Symbol), symbol, '\0');
		U_CopyAndPad(m_lastLocateExecutionID, sizeof(m_lastLocateExecutionID), lastLocateExecutionID, '\0');
	}

	char	Symbol[MAX_SYMBOL_SIZE];
	UCHAR	InstrumentType;

	int	Quantity;
	double AveragePrice;

	unsigned int m_borrowedQuantity;
	double	m_borrowedAvgPrice;

	unsigned __int64 m_optionBlock;
	char m_lastLocateExecutionID[MAX_MARKET_REFERENCE_ID];
};

enum AccountRecoveryReason : unsigned int
{
	RECOVERY_REASON_STARTING =					1,
	RECOVERY_REASON_DISCONNECTED =				2
};

//#define RECOVERY_REASON_STARTING					1
//#define RECOVERY_REASON_DISCONNECTED				2

class TMessageReqAccountRecovery : public TMessageAccountRecoveryBase
{
public:
	WORD RecoveryReason;						//The reason for full recovery
protected:
	TMessageReqAccountRecovery(const unsigned int& time,
		const DWORD& requestID,
		const char* const& accountName,
		const WORD& recoveryReason,
		const unsigned short& type,
		const unsigned short& length):
		TMessageAccountRecoveryBase(time, requestID, accountName, type, length),
		RecoveryReason(recoveryReason)
	{
	}
};

//TSClient->TS sent to recover the entire stream of account messages starting from the given sequenced number
class TMsgReqAccountFullRecovery : public TMessageReqAccountRecovery
{
public:
	TMsgReqAccountFullRecovery(const unsigned int& time = 0,
		const DWORD& requestID = 0,
		const char* const& accountName = "",
		const WORD& recoveryReason = 0,
		const DWORD& lastAccountMessageSequenuenceNumber = 0):
		TMessageReqAccountRecovery(time, requestID, accountName, recoveryReason, TS_ACCOUNT_RECOVERY_FULL_REQ, sizeof(TMsgReqAccountFullRecovery)),
		LastAccountMessageSequenuenceNumber(lastAccountMessageSequenuenceNumber)
	{
	}
	DWORD LastAccountMessageSequenuenceNumber;
};

//TSClient -> TS Sent to recover the current open orders and open positions
class TMsgReqAccountQuickRecovery : public TMessageReqAccountRecovery
{
public:
	TMsgReqAccountQuickRecovery(const unsigned int& time = 0,
		const DWORD& requestID = 0,
		const char* const& accountName = "",
		const WORD& recoveryReason = 0):
		TMessageReqAccountRecovery(time, requestID, accountName, recoveryReason, TS_ACCOUNT_RECOVERY_QUICK_REQ, sizeof(TMsgReqAccountQuickRecovery))
	{
	}
};

class TMsgReqExecutionHistory : public TMessageReqAccountRecovery
{
public:
	TMsgReqExecutionHistory(const unsigned int& time = 0,
		const DWORD& requestID = 0,
		const char* const& accountName = "",
		const WORD& recoveryReason = 0):
		TMessageReqAccountRecovery(time, requestID, accountName, recoveryReason, TS_ACCOUNT_EXEC_HISTORY_REQ, sizeof(TMsgReqExecutionHistory))
	{
	}
};

class TMsgHistoryComplete : public TMessageAccountRecoveryBase
{
public:
	DWORD	m_objectCount;
	WORD	m_resultCode;								//Filled in case of error
	char	m_resultText[MAX_RESULT_TEXT_SIZE];		//Filled in case of error
protected:
	TMsgHistoryComplete(const unsigned int& time,
		const DWORD& requestID,
		const char* const& accountName,
		const DWORD& objectCount,
		const WORD& resultCode,
		const char* const& resultText,
		const unsigned short& type,
		const unsigned short& length):
		TMessageAccountRecoveryBase(time,
			requestID,
			accountName,
			type,
			length),
		m_objectCount(objectCount),
		m_resultCode(resultCode)
	{
		U_CopyAndPad(m_resultText, sizeof(m_resultText), resultText, '\0', true);
	}
};

//TS->TSClient Sent as the last message to TS_ACCOUNT_OVERNIGHT_POSITION_REQUEST_MESSAGE to indicate either an error condition or successful completion of download
class TMsgOvernightPositionLoadComplete : public TMsgHistoryComplete
{
public:
	TMsgOvernightPositionLoadComplete(const unsigned int& time = 0,
		const DWORD& requestID = 0,
		const char* const& accountName = "",
		const DWORD& positionCount = 0,
		const WORD& resultCode = 0,								//Filled in case of error
		const char* const& resultText = ""):
		TMsgHistoryComplete(time,
			requestID,
			accountName,
			positionCount,
			resultCode,
			resultText,
			TS_ACCOUNT_POSITION_RESP, sizeof(TMsgOvernightPositionLoadComplete))
//		PositionCount(positionCount),
//		ResultCode(resultCode)
	{
//		U_CopyAndPad(ResultText, sizeof(ResultText), resultText, '\0');
	}
//	DWORD	PositionCount;
//	WORD	ResultCode;								//Filled in case of error
//	char	ResultText[MAX_RESULT_TEXT_SIZE];		//Filled in case of error
};

class TMsgExecutionHistoryComplete : public TMsgHistoryComplete
{
public:
	TMsgExecutionHistoryComplete(const unsigned int& time = 0,
		const DWORD& requestID = 0,
		const char* const& accountName = "",
		const DWORD& objectCount = 0,
		const WORD& resultCode = 0,
		const char* const& resultText = ""):
		TMsgHistoryComplete(time,
			requestID,
			accountName,
			objectCount,
			resultCode,
			resultText,
			TS_ACCOUNT_EXEC_HISTORY_COMPLETE,
			sizeof(TMsgExecutionHistoryComplete))
	{
	}
};

class TMsgReqOrderHistory : public TMessageReqAccountRecovery
{
public:
	TMsgReqOrderHistory(const unsigned int& time = 0,
		const DWORD& requestID = 0,
		const char* const& accountName = "",
		const WORD& recoveryReason = 0):
		TMessageReqAccountRecovery(time,
			requestID,
			accountName,
			recoveryReason,
			TS_ACCOUNT_ORDER_HISTORY_REQ,
			sizeof(TMsgReqOrderHistory))
	{
	}
};

class TMsgOrderHistoryComplete : public TMsgHistoryComplete
{
public:
	TMsgOrderHistoryComplete(const unsigned int& time = 0,
		const DWORD& requestID = 0,
		const char* const& accountName = "",
		const DWORD& objectCount = 0,
		const WORD& resultCode = 0,
		const char* const& resultText = ""):
		TMsgHistoryComplete(time,
			requestID,
			accountName,
			objectCount,
			resultCode,
			resultText,
			TS_ACCOUNT_ORDER_HISTORY_COMPLETE,
			sizeof(TMsgOrderHistoryComplete))
	{
	}
};

//TS->TSClient, sent in response to TS_ACCOUNT_RECOVERY_QUICK_REQUEST_MESSAGE
class TMsgPosition : public TMessageAccountRecoveryBase
{
public:
	TMsgPosition(const unsigned int& time = 0,
		const DWORD& requestID = 0,
		const char* const& accountName = "",
		const char* const& symbol = "",
		const unsigned char& instrumentType = 0,
		const int& quantity = 0,
		const Price& price = Price::priceZero,
		const int& overnightQuantity = 0,
		const Price& overnightPrice = Price::priceZero,
		const int& currentQuantity = 0,		//Includes overnight positions too
		const Price& currentPrice = Price::priceZero,
		const unsigned int& closedLongQuantity = 0,
		const Money& closedLongCost = Money::moneyZero,
		const Money& closedLongValue = Money::moneyZero,

		const unsigned int& closedShortQuantity = 0,
		const Money& closedShortCost = Money::moneyZero,
		const Money& closedShortValue = Money::moneyZero,

		const unsigned int& borrowedQuantity = 0,
		const Price& borrowedPrice = Price::priceZero,

		const unsigned __int64& optionBlock = 0,

		const char* const& lastLocateExecutionID = "",

		const int& openOvernightQuantity = 0,
		const double& currentPositionAvgPriceMargin = 0,

		const double& overnightRealPositionPrice = 0):

		TMessageAccountRecoveryBase(time,
			requestID,
			accountName,
			TS_ACCOUNT_RECOVERY_RESP,
			sizeof(TMsgPosition)),
		InstrumentType(instrumentType),
		Quantity(quantity),
		AveragePrice(price.toDouble()),
		OvernightPositionQuantity(overnightQuantity),
		OvernightPositionAvgPrice(overnightPrice.toDouble()),
		CurrentPositionQuantity(currentQuantity),
		CurrentPositionAvgPrice(currentPrice.toDouble()),
		ClosedLongPositionQuantity(closedLongQuantity),
		ClosedLongPositionCost(closedLongCost.toDouble()),
		ClosedLongPositionValue(closedLongValue.toDouble()),
		ClosedShortPositionQuantity(closedShortQuantity),
		ClosedShortPositionCost(closedShortCost.toDouble()),
		ClosedShortPositionValue(closedShortValue.toDouble()),
		m_borrowedQuantity(borrowedQuantity),
		m_borrowedAvgPrice(borrowedPrice.toDouble()),

		m_optionBlock(optionBlock),

		OpenOvernightPositionQuantity(openOvernightQuantity),
		CurrentPositionAvgPriceMargin(currentPositionAvgPriceMargin),

		OvernightRealPositionPrice(overnightRealPositionPrice)
	{
		U_CopyAndPad(Symbol, sizeof(Symbol), symbol, '\0');
		U_CopyAndPad(m_lastLocateExecutionID, sizeof(m_lastLocateExecutionID), lastLocateExecutionID ? lastLocateExecutionID : "", '\0');
	}

	char	Symbol[MAX_SYMBOL_SIZE];
	UCHAR	InstrumentType;

	int	Quantity;
	double	AveragePrice;

	int	OvernightPositionQuantity;
	double	OvernightPositionAvgPrice;

	int	CurrentPositionQuantity;		//Includes overnight positions too
	double	CurrentPositionAvgPrice;

	DWORD	ClosedLongPositionQuantity;
	double	ClosedLongPositionCost;
	double	ClosedLongPositionValue;

	DWORD	ClosedShortPositionQuantity;
	double	ClosedShortPositionCost;
	double	ClosedShortPositionValue;

	unsigned int m_borrowedQuantity;
	double m_borrowedAvgPrice;

	unsigned __int64 m_optionBlock;

	char m_lastLocateExecutionID[MAX_MARKET_REFERENCE_ID];

	int OpenOvernightPositionQuantity;

	double CurrentPositionAvgPriceMargin;

	double OvernightRealPositionPrice;
};

//Order sides - match with FIX
enum OrderSideEnum : unsigned char
{
	ORDER_SIDE_BUY =					'1',		// = Buy
	ORDER_SIDE_SELL =					'2',		// = Sell
	ORDER_SIDE__BUY_MINUS =				'3',		// = Buy minus
	ORDER_SIDE_SELL_PLUS =				'4',		// = Sell plus
	ORDER_SIDE_SELL_SHORT =				'5',		// = Sell short
	ORDER_SIDE_SELL_SHORT_EXEMPT =		'6',		// = Sell short exempt
	ORDER_SIDE_UNDISCLOSED =			'7',		// = Undisclosed (valid for IOI and List Order messages only)
	ORDER_SIDE_CROSS =					'8',		// = Cross (orders where counterparty is an exchange, valid for all messages except IOIs)
	ORDER_SIDE_CROSS_SHORT =			'9',		// = Cross short
	ORDER_SIDE_SHORT_EXEMPT =			'A',		//= Cross short exxmpt
	ORDER_SIDE_AS_DEFINED =				'B',		//"As Defined" (for use with multileg instruments)
	ORDER_SIDE_OPPOSITE =				'C'		// = "Opposite" (for use with multileg instruments)
};
/*
#define ORDER_SIDE_BUY					'1'		// = Buy
#define ORDER_SIDE_SELL					'2'		// = Sell
#define ORDER_SIDE__BUY_MINUS			'3'		// = Buy minus
#define ORDER_SIDE_SELL_PLUS			'4'		// = Sell plus
#define ORDER_SIDE_SELL_SHORT			'5'		// = Sell short
#define ORDER_SIDE_SELL_SHORT_EXEMPT	'6'		// = Sell short exempt
#define ORDER_SIDE_UNDISCLOSED			'7'		// = Undisclosed (valid for IOI and List Order messages only)
#define ORDER_SIDE_CROSS				'8'		// = Cross (orders where counterparty is an exchange, valid for all messages except IOIs)
#define ORDER_SIDE_CROSS_SHORT			'9'		// = Cross short
#define ORDER_SIDE_SHORT_EXEMPT			'A'		//= Cross short exxmpt
#define ORDER_SIDE_AS_DEFINED			'B'		//"As Defined" (for use with multileg instruments)
#define ORDER_SIDE_OPPOSITE				'C'		// = "Opposite" (for use with multileg instruments)
*/


// Order types - match with FIX
enum OrderTypeEnum : unsigned char
{
	ORDER_TYPE_NULL =						'0',	// Invalid or illegal order type
	ORDER_TYPE_MARKET =						'1',
	ORDER_TYPE_LIMIT =						'2',
	ORDER_TYPE_STOP =						'3',
	ORDER_TYPE_STOP_LIMIT =					'4',
	ORDER_TYPE_MARKET_ON_CLOSE =			'5',//Deprecated (Use ORDER_TYPE_MARKET and TIF_ATC )
	ORDER_TYPE_WITH_OR_WITHOUT =			'6',
	ORDER_TYPE_LIMIT_OR_BETTER =			'7',//Deprecated
	ORDER_TYPE_LIMIT_WITH_OR_WITHOUT =		'8',
	ORDER_TYPE_ON_BASIS =					'9',
	ORDER_TYPE_LIMIT_ON_CLOSE =				'B', // Deprecated (Use ORDER_TYPE_LIMIT and TIF_ATC )
	ORDER_TYPE_FUNARI =						'I',	// Deprecated - LeveL wants this order type sent instead of ORDER_TYPE_LIMIT
	ORDER_TYPE_MARKET_LEFTOVER_AS_LIMIT =	'K',           // Supported by iLink
	ORDER_TYPE_PEGGED =						'P'
};
/*
#define ORDER_TYPE_NULL							'0'	// Invalid or illegal order type
#define ORDER_TYPE_MARKET						'1'
#define ORDER_TYPE_LIMIT						'2'
#define ORDER_TYPE_STOP							'3'
#define ORDER_TYPE_STOP_LIMIT					'4'
#define	ORDER_TYPE_MARKET_ON_CLOSE				'5'//Deprecated (Use ORDER_TYPE_MARKET and TIF_ATC )
#define	ORDER_TYPE_WITH_OR_WITHOUT				'6'
#define	ORDER_TYPE_LIMIT_OR_BETTER				'7'//Deprecated
#define	ORDER_TYPE_LIMIT_WITH_OR_WITHOUT		'8'
#define	ORDER_TYPE_ON_BASIS						'9'
#define ORDER_TYPE_LIMIT_ON_CLOSE				'B' // Deprecated (Use ORDER_TYPE_LIMIT and TIF_ATC )
#define ORDER_TYPE_FUNARI						'I'	// Deprecated - LeveL wants this order type sent instead of ORDER_TYPE_LIMIT
#define	ORDER_TYPE_PEGGED						'P'
*/
/*
//Order TIFS - match with FIX
#define TIF_DAY						'0'		//Day (or session)
#define TIF_GTC						'1'		//Good Till Cancel (GTC)
#define TIF_OPG						'2'		//At the Opening (OPG)
#define TIF_IOC						'3'		//Immediate Or Cancel (IOC)
#define TIF_FOK						'4'		//Fill Or Kill (FOK)
#define TIF_GTX						'5'		//Good Till Crossing (GTX)
#define TIF_GTD						'6'		//Good Till Date (GTD)
#define TIF_ATC						'7'		//At the Close
//Non FIX TIFs
#define	GT_XPR						'X'	// Express
#define	GT_DAY_PLUS					'P'	// Day Plus (Day+)	//-> Added 07/26/2004.
*/

enum Subtype : unsigned short
{
	ST_REGULAR_STOP,
	ST_TRAILING_STOP_BID = 1,
	ST_TRAILING_STOP_ASK,
	ST_TRAILING_STOP_MIDPOINT,
	ST_TRAILING_STOP_LAST,
	ST_SYNTHETIC_STOP_BID,
	ST_SYNTHETIC_STOP_ASK,
	ST_SYNTHETIC_STOP_MIDPOINT,
	ST_SYNTHETIC_STOP_LAST,

	ST_URGENCY_DARK    = 100,
	ST_URGENCY_LOW,
	ST_URGENCY_MEDIUM,
	ST_URGENCY_HIGH,
	ST_URGENCY_GETDONE,

	ST_CLOSE = 0x100,

	ST_HALTED_STOCK = 0x200,
	ST_DMA = 0x400,
	ST_OTCBB = 0x800,
	ST_ETB = 0x1000,
	ST_STOPTRIGGER_IGNORE_FINRA_PRINTS = 0x2000,
	ST_STOPTRIGGER_WAIT_NEXT = 0x4000,

	ST_ALL_FLAGS = ST_CLOSE | ST_HALTED_STOCK | ST_DMA | ST_OTCBB | ST_ETB | ST_STOPTRIGGER_IGNORE_FINRA_PRINTS | ST_STOPTRIGGER_WAIT_NEXT
};

enum VenueEnum : unsigned __int64
{
	NULL_ROUTE =			0x0,			// Invalid or illegal system type
	NSDQ_FIX_ROUTE =		0x00000001,	// NASDAQ FIX
	IEX_ROUTE =				0x00000002,
	CVGX_ROUTE =			0x00000004,  // ConvergEx
//	SPEED_MID_DARK_ROUTE =	0x00000004,	// NASDAQ RUSH ROUTE
	AMEX_ROUTE =			0x00000008,	// AMEX ROUTE
	BATS_ROUTE =			0x00000010,	// BATS ROUTE
	EDGX_ROUTE =			0x00000020,	// Direct Edge
	NYSE_ROUTE =			0x00000040,  // NYSE ROUTE
	ARCA_ROUTE =			0x00000080,  // ARCA ROUTE
//	BTRD_ROUTE =			0x00000100,  // BTRD ROUTE
//	BARX_ROUTE =			0x00000100,  // BARX ROUTE
//	SPEED_FREE_DARK_ROUTE =	0x00000100,
//	TRAC_ROUTE =			0x00000200,  // TRAC ROUTE
//	CITADEL_ROUTE =			0x00000100,  // Citadel ROUTE

//	LYNX_ROUTE =			0x00000100,  // Lynx Route
	BAML_ROUTE =			0x00000100,	// BAML Route, no orders are sent with this route, but it can come in Route in the order response if redirected to BAML

	UBS_ROUTE =				0x00000200,  // UBS ROUTE
//	NITE_ROUTE =			0x00000400,  // Knight route
	VIRT_ROUTE =			0x00000400,  // Virtu route
//	GSCO_SIGMA_X_ROUTE =	0x00000800,//dark pool
	CSFB_CROSSFINDER =		0x00001000,//dark pool
	BATY_ROUTE =			0x00002000,	// BATY ROUTE

	EDGA_ROUTE =			0x00004000,	// Direct EdgeA
//	NSEX_ROUTE =			0x00008000,	// NSX
	DASH_ROUTE =			0x00008000,	// DASH
	CHSX_ROUTE =			0x00010000,	// MWSE (Chicago Stock Exchange)
	APEX_ROUTE =			0x00020000,	// APEX
//	CBOE_ROUTE =			0x00020000,	// CBOE (Chicago Board of Options Exchange) (CBSX)
	PHLX_ROUTE =			0x00040000,	// NASDAQ PHLX
	BOSX_ROUTE =			0x00080000,	// NASDAQ BOSX
//	FLOW_ROUTE =			0x00100000,	// LAVA FLOW Dark Pool
	CLEARPOOL_ROUTE =		0x00100000,	// ClearPool (Was LAVA FLOW Dark Pool)
	PDQ_ROUTE =				0x00200000,	// BNY ConvergEx - VortEx Dark Pool
	LEVEL_ROUTE =			0x00400000,	// NYFIX Millennium Dark Pool
//	NYFX_ROUTE =			0x00800000,	// NYFIX Broker Routing
//	ITG_ROUTE =				0x00800000,
//	NEXA_ROUTE =			0x01000000,  // NEXA - PTSI( Penson )
	JPM_ROUTE =				0x01000000,
	SPEED_ROUTE =			0x02000000,
	LSTK_ROUTE =			0x04000000,	// LOCATE STOCK
//	FI_SMART_ROUTE =		0x08000000,	// MANTARA Smart Routes (XWAY)
	NSEX_ROUTE =			0x08000000,	// NSX
//	QED_ROUTE =				0x10000000,  // QED Route (internal use) - MatchServer
	CUTTONE_ROUTE =			0x10000000,	// Cuttone through Raptor
	COWEN_ROUTE	=			0x20000000,	// Cowen
	TRAFIX_ROUTE =			0x40000000,	// Lamp through Trafix
	BARX_ROUTE =			0x80000000,	// Barclays
	BROADRIDGE_ROUTE =		0x100000000,	// Broadridge locates
	INSTINET_ROUTE =		0x200000000,	// Instinet Route
	IQX_ROUTE =				0x400000000,	// IQX (IntelligentCross) Route
	LTSE_ROUTE =			0x800000000,	// LTSE Route
	MEMX_ROUTE =			0x1000000000,	// MEMX Route
	MIAX_ROUTE =			0x2000000000,	// MIAX Route
	OTCX_ROUTE =			0x4000000000,	// OTCX Route (OTC Markets)
	LYNX_ROUTE =			0x8000000000,  // Lynx Route

	ILINK_ROUTE =			0x10000000000,     // CME iLink Route

	VOLANT_ROUTE =			0x20000000000,

	VELOCITY_ROUTE =		0x40000000000,	// Velocity Route
	
	Route_Last

//	RISK_ROUTE =			0x10000000,  // Risk Management Server (internal use)
//	DROP_COPY_ROUTE =		0x20000000,  // DROP COPY (internal use)
//	DB_LOGGER_ROUTE =		0x40000000,  // DB Logger (internal use)
//	AUTO_ROUTE =			0x80000000,  // AUTO ROUTE
};

inline bool isDestinationBorrow(const unsigned __int64& destinationId)
{
	switch(destinationId)
	{
		case LSTK_ROUTE:
		case BROADRIDGE_ROUTE:
		return true;

		default:
		return false;
	}
}


#ifndef TAKION_NO_OPTIONS
enum OptionMMID : unsigned int
{
	ISEX_ROUTE =			0x00000101,
	MISE_ROUTE =			0x00000102,
	C2_ROUTE =				0x00000103,
	BOX_ROUTE =				0x00000104,
	GEM_ROUTE =				0x00000105,
	CBOE_ROUTE_OPT =		0x00000106,	// CBOE - for Options Only
	PERL_ROUTE =			0x00000107,
};
#endif


// Order Status
enum OrderStatusEnum : unsigned char
{
	OS_NONPENDING = 0x0,// No longer pending (canceled, filled, rejected)
	OS_NEW = 0x1,// New Order
	OS_PENDING_CANCEL = 0x2,
	OS_PENDING_ACCEPT = 0x04,// Pending Accept (used for confirmation logic of locate orders)
	OS_PENDING_INTERNAL_CROSS = 0x08,// Either waiting on other orders to be canceled/replaced or being canceled/replaced for internal cross
	OS_PENDING_INTERNAL_CROSS_CANCEL = 0x10,// Being canceled for internal cross
	OS_TRIGGERED = 0x40,// Stop was triggered
	OS_REROUTED = 0x80,// Rerouted
};

// Tracking
enum OrderTrackingEnum : unsigned char
{
	TR_ON_CLIENT =			0x0,			// Order is on client
	TR_ON_SERVER =			0x1,			// Order is on server
	TR_ON_DRIVER =			0x2,			// Order is on venue driver
	TR_ON_MARKET =			0x3,			// Order is on market
};

// ExecInst bit field, should be mapped to FIX values in FIX driver
enum ExecutionInstructions : unsigned int
{
	EI_STAY_ON_OFFERSIDE =				0x00000001,	// '0' = Stay on offerside
	EI_NOT_HELD =						0x00000002,	// '1' = Not held
	EI_WORK =							0x00000004,	// '2' = Work
	EI_GO_ALONG =						0x00000008,	// '3' = Go along
	EI_OVER_THE_DAY =					0x00000010,	// '4' = Over the day
	EI_HELD =							0x00000020,	// '5' = Held
	EI_PARTICIPATE_DONT_INITIATE =		0x00000040,	// '6' = Participate don't initiate
	EI_STRICT_SCALE =					0x00000080,	// '7' = Strict scale
	EI_TRY_TO_SCALE =					0x00000100,	// '8' = Try to scale
	EI_STAY_ON_BIDSIDE =				0x00000200,	// '9' = Stay on bidside
	EI_NO_CROSS =						0x00000400,	// 'A' = No cross (cross is forbidden)
	EI_OK_TO_CROSS =					0x00000800,	// 'B' = OK to cross
	EI_CALL_FIRST =						0x00001000,	// 'C' = Call first
	EI_PERCENT_OF_VOLUME =				0x00002000,	// 'D' = Percent of volume (indicates that the sender does not want to be all of the volume on the floor vs. a specific percentage)
	EI_DNI =							0x00004000,	// 'E' = Do not increase - DNI
	EI_DNR =							0x00008000,	// 'F' = Do not reduce - DNR
	EI_AON =							0x00010000,	// 'G' = All or none - AON
	EI_INSTITUTIONS_ONLY =				0x00020000,	// 'I' = Institutions only
	EI_LAST_PEG =						0x00040000,	// 'L' = Last peg (last sale)
	EI_MIDPRICE_PEG =					0x00080000,	// 'M' = Mid-price peg (midprice of inside quote)
	EI_NON_NEGOTIABLE =					0x00100000,	// 'N' = Non-negotiable
	EI_OPENING_PEG =					0x00200000,	// 'O' = Opening peg
	EI_MARKET_PEG =						0x00400000,	// 'P' = Market peg
	EI_PRIMARY_PEG =					0x00800000,	// 'R' = Primary peg (primary market - buy at bid/sell at offer)
	EI_SUSPEND =						0x01000000,	// 'S' = Suspend
	EI_INTERMARKET_SWEEP =				0x02000000,	// 'f' = Intermarket Sweep (BATS)
	EI_FIXED_PEG =						0x04000000,	// 'T' = Fixed Peg to Local best bid or offer at time of order
	EI_CUSTOMER_DISPLAY_INSTRUCTION	=	0x08000000,	// 'U' = Customer Display Instruction (Rule11Ac1-1/4)
	EI_NETTING =						0x10000000,	// 'V' = Netting (for Forex)
	EI_PEG_TO_VWAP =					0x20000000,	// 'W' = Peg to VWAP
	EI_IMBALANCE_ONLY =					0x40000000,  // 'i' = NASDAQ Imbalance Only Orders
//	EI_PEG_TO_LIMIT_PRICE =				0x80000000,	// 'd' = PegToLimitPrice (used by ARCA for Tracking Orders)
	EI_MIDPOINT_DISCRETIONARY_PEG =		0x80000000,	// 'd' = Midpoint Discretionary Order (EDGA)

	EI_PEG_MASK =						EI_LAST_PEG | EI_MIDPRICE_PEG | EI_OPENING_PEG | EI_MARKET_PEG | EI_PRIMARY_PEG | EI_FIXED_PEG | EI_PEG_TO_VWAP | EI_MIDPOINT_DISCRETIONARY_PEG
};
/*
#define EI_STAY_ON_OFFERSIDE			0x00000001	// '0' = Stay on offerside
#define EI_NOT_HELD						0x00000002	// '1' = Not held
#define EI_WORK							0x00000004	// '2' = Work
#define EI_GO_ALONG						0x00000008	// '3' = Go along
#define EI_OVER_THE_DAY					0x00000010	// '4' = Over the day
#define EI_HELD							0x00000020	// '5' = Held
#define EI_PARTICIPATE_DONT_INITIATE	0x00000040	// '6' = Participate don't initiate
#define EI_STRICT_SCALE					0x00000080	// '7' = Strict scale
#define EI_TRY_TO_SCALE					0x00000100	// '8' = Try to scale
#define EI_STAY_ON_BIDSIDE				0x00000200	// '9' = Stay on bidside
#define EI_NO_CROSS						0x00000400	// 'A' = No cross (cross is forbidden)
#define EI_OK_TO_CROSS					0x00000800	// 'B' = OK to cross
#define EI_CALL_FIRST					0x00001000	// 'C' = Call first
#define EI_PERCENT_OF_VOLUME			0x00002000	// 'D' = Percent of volume (indicates that the sender does not want to be all of the volume on the floor vs. a specific percentage)
#define EI_DNI							0x00004000	// 'E' = Do not increase - DNI
#define EI_DNR							0x00008000	// 'F' = Do not reduce - DNR
#define EI_AON							0x00010000	// 'G' = All or none - AON
#define EI_INSTITUTIONS_ONLY			0x00020000	// 'I' = Institutions only
#define EI_LAST_PEG						0x00040000	// 'L' = Last peg (last sale)
#define EI_MIDPRICE_PEG					0x00080000	// 'M' = Mid-price peg (midprice of inside quote)
#define EI_NON_NEGOTIABLE				0x00100000	// 'N' = Non-negotiable
#define EI_OPENING_PEG					0x00200000	// 'O' = Opening peg
#define EI_MARKET_PEG					0x00400000	// 'P' = Market peg
#define EI_PRIMARY_PEG					0x00800000	// 'R' = Primary peg (primary market - buy at bid/sell at offer)
#define EI_SUSPEND						0x01000000	// 'S' = Suspend
#define EI_INTERMARKET_SWEEP			0x02000000	// 'f' = Intermarket Sweep (BATS)
#define EI_FIXED_PEG					0x04000000	// 'T' = Fixed Peg to Local best bid or offer at time of order
#define EI_CUSTOMER_DISPLAY_INSTRUCTION	0x08000000	// 'U' = Customer Display Instruction (Rule11Ac1-1/4)
#define EI_NETTING						0x10000000	// 'V' = Netting (for Forex)
#define EI_PEG_TO_VWAP					0x20000000	// 'W' = Peg to VWAP
#define EI_IMBALANCE_ONLY				0x40000000  // 'i' = NASDAQ Imbalance Only Orders
//#define EI_PEG_TO_LIMIT_PRICE			0x80000000	// 'd' = PegToLimitPrice (used by ARCA for Tracking Orders)
#define EI_MIDPOINT_DISCRETIONARY_PEG	0x80000000	// 'd' = Midpoint Discretionary Order (EDGA)

#define EI_PEG_MASK						( EI_LAST_PEG | EI_MIDPRICE_PEG | EI_OPENING_PEG | EI_MARKET_PEG | EI_PRIMARY_PEG | EI_FIXED_PEG | EI_PEG_TO_VWAP | EI_MIDPOINT_DISCRETIONARY_PEG)
*/
/*
// Subtype: additional ExecInst flags
#define ST_BATS_DART					0x00000001	// 'u' = BATS+DART (BATS)
#define ST_BATS_FORCE_DART				0x00000002	// 'v' = Force DART (BATS)
#define ST_BATS_DONT_DART				0x00000004	// 'w' = Do Not DART (BATS)
*/
//RoutingInstructions
enum Routing : unsigned short
{
	RI_NONE					= 0,
	
	RI_PROACTIVE,
//	RI_PROACTIVE_DMA,

	RI_BATS_ADD_LIQUIDITY_ONLY = 20,
	RI_BATS_DART,
	RI_BATS_FORCE_DART,
	RI_BATS_CYCLE,
	RI_BATS_PARALLEL_D,
	RI_BATS_TRIM,
	RI_BATS_TRIM_MINUS,
	RI_BATS_SLIM,
	RI_BATS_SLIM_PLUS,
	RI_BATS_PARALLEL_T,
	RI_BATS_PARALLEL_2D,

	RI_BATS_TRIM2,
	RI_BATS_TRIM2_MINUS,
	RI_BATS_TRIM3,
	RI_BATS_TRIM3_MINUS,

	RI_EDGE_ADD_LIQUIDITY_ONLY = 40,
	RI_EDGE_RDOT,
	RI_EDGE_RDOX,
	RI_EDGE_ROBA,
	RI_EDGE_ROBX,
	RI_EDGE_ROPA,
	RI_EDGE_ROLF,
	RI_EDGE_INET,
	RI_EDGE_ROUT,
	RI_EDGE_ROUD,
	RI_EDGE_ROUC,
	RI_EDGE_ROUE,
	RI_EDGE_ROUX,
	RI_EDGE_ROUQ,
	RI_EDGE_ROUZ,

	RI_EDGE_ROBY,
	RI_EDGE_ROBB,
	RI_EDGE_ROCO,
	RI_EDGE_ROOC,
	RI_EDGE_SWPA,
	RI_EDGE_SWPB,
	RI_EDGE_SWPC_DEPRECATED,					// Deprecated
	RI_EDGE_IOCT,
	RI_EDGE_IOCX,
	RI_EDGE_IOCM,
	RI_EDGE_ICMT,
	RI_EDGE_RMPT,								// Should be used ONLY on BATY/EDGA orders

	RI_ARCA_ADD_LIQUIDITY_ONLY = 70,
	RI_ARCA_PASSIVE_LIQUIDITY,
	RI_ARCA_PRIMARY_SWEEP_NON_ROUTABLE,
	RI_ARCA_PRIMARY_SWEEP_ROUTABLE,
	RI_ARCA_PRIMARY_ON_OPEN,
	RI_ARCA_PRIMARY_ON_OPEN_PLUS,
	RI_ARCA_PRIMARY_ON_OPEN_PLUS_SHIP,
	RI_ARCA_PASSIVE_LIQUIDITY_SELECT,

	RI_NSDQ_ADD_LIQUIDITY_ONLY = 100,
	RI_NSDQ_SCAN,
	RI_NSDQ_STGY,
	RI_NSDQ_SKIP,
	RI_NSDQ_SKNY,
	RI_NSDQ_LIST,
	RI_NSDQ_CART,
	RI_NSDQ_SAVE,
	RI_NSDQ_QSAV,
	RI_NSDQ_SOLV,
	RI_NSDQ_TFTY,
	RI_NSDQ_QTFY,
	RI_NSDQ_DOTA,
	RI_NSDQ_DOTM,
	RI_NSDQ_DOTI,
	RI_NSDQ_DOTZ,
	RI_NSDQ_MOPP,
	RI_NSDQ_DOTD,
	RI_NSDQ_DARK,
	RI_NSDQ_COST,
	RI_NSDQ_MIDPOINT_EXTENDED_LIFE,

//	RI_NYSE_CLOSING_OFFSET = 130,
	RI_NYSE_ADD_LIQUIDITY_ONLY = 131,

	RI_VIRT_FAN = 160,
	RI_VIRT_FAN_AGGRESSIVE,
	RI_VIRT_FAN_AGGRESSIVE_PLUS,
	RI_VIRT_FAN_PASSIVE,
	RI_VIRT_RESERVED,
	RI_VIRT_COVERT,
	RI_VIRT_COVERT_AGGRESSIVE,
	RI_VIRT_RESERVED1,
	RI_VIRT_COVERT_PASSIVE,
	RI_VIRT_RESERVED2,
	RI_VIRT_OASIS,
	RI_VIRT_RESERVED3,
	RI_VIRT_RESERVED4,
	RI_VIRT_RESERVED5,
	RI_VIRT_RESERVED6,
	RI_VIRT_RESERVED7,
	RI_VIRT_RESERVED8,
	RI_VIRT_RESERVED9,
	RI_VIRT_RESERVED10,
	RI_VIRT_RESERVED11,
	RI_VIRT_RESERVED12,
	RI_VIRT_RESERVED13,
	RI_VIRT_RESERVED14,
	RI_VIRT_OASIS_AGGRESSIVE,
	RI_VIRT_OASIS_PASSIVE,
	RI_VIRT_VWAP,
	RI_VIRT_TWAP,
	RI_VIRT_CATCH,
	RI_VIRT_CATCH_AGGRESSIVE,
	RI_VIRT_CATCH_PASSIVE,
	RI_VIRT_OPPORTUNISTIC,
	RI_VIRT_OPPORTUNISTIC_AGGRESSIVE,
	RI_VIRT_OPPORTUNISTIC_PASSIVE,
	RI_VIRT_CASH_NOT_HELD,
	RI_VIRT_CASH_HELD,
	RI_VIRT_LAST,								// Must be last for VIRTU ALGOS

/*
	RI_NITE_FAN = 160,
	RI_NITE_FAN_AGGRESSIVE,
	RI_NITE_FAN_AGGRESSIVE_PLUS,
	RI_NITE_FAN_PASSIVE,
	RI_NITE_FAN_PASSIVE_PLUS,
	RI_NITE_COVERT,
	RI_NITE_COVERT_AGGRESSIVE,
	RI_NITE_COVERT_AGGRESSIVE_PLUS,
	RI_NITE_COVERT_PASSIVE,
	RI_NITE_COVERT_PASSIVE_PLUS,
	RI_NITE_OASIS,
	RI_NITE_SUMO_AGGRESSIVE,
	RI_NITE_SUMO_MORE_AGGRESSIVE,
	RI_NITE_SUMO_AGGRESSIVE_PLUS,
	RI_NITE_PRIMARY,
	RI_NITE_FAN_R,
	RI_NITE_FAN_R_AGGRESSIVE,
	RI_NITE_FAN_R_AGGRESSIVE_PLUS,
	RI_NITE_FAN_R_PASSIVE,
	RI_NITE_FAN_R_PASSIVE_PLUS,
	RI_NITE_ARCA_DMA,
	RI_NITE_GETCO,
	RI_NITE_FAN_ISO,
*/
	RI_NSX_ADD_LIQUIDITY_ONLY = 200,

//	RI_NEXA_MNGD = 230,
	RI_JPM_AQUA = 230,
	RI_JPM_CLOSE,
	RI_JPM_CUSTOM,
	RI_JPM_IS,
	RI_JPM_POV,
	RI_JPM_TWAP,
	RI_JPM_VWAP,

	RI_BARX_VWAP = 300,
	RI_BARX_WITH_VOLUME,
	RI_BARX_TWAP,
	RI_BARX_SMARTX,
	RI_BARX_HYDRA,
	RI_BARX_RAPID,
	RI_BARX_LX,
	RI_BARX_CUSTOM,

	RI_UBS_TAPNOW = 400,

	RI_CSFB_NEUTRAL    = 500, // Peg to Midpoint (default)
	RI_CSFB_AGGRESSIVE,     // Peg to Market
	RI_CSFB_PASSIVE,     // Peg to Primary
	RI_CSFB_PATHFINDER,
	RI_CSFB_BLAST,
	RI_CSFB_OTCBB,
	RI_CSFB_VWAP,

//	RI_SIGMA_ATS    = 600,
//	RI_SIGMA_X_PING,

	RI_PDQ_MIDPOINT_GET = 700,
	RI_PDQ_ARCA_VALUE,
	RI_PDQ_BATS_VALUE,
	RI_PDQ_EDGX_VALUE,
	RI_PDQ_NSDQ_VALUE,
 	RI_PDQ_SAVE1,
	RI_PDQ_SAVE2,
	RI_PDQ_SAVEWORK,
	RI_PDQ_FREE,
	RI_PDQ_ZAPP,
	RI_PDQ_DARKALL,
	RI_PDQ_FREEPAIR,
	RI_PDQ_PCBSX,
	RI_PDQ_BATY_VALUE,
	RI_PDQ_RESERVED1,
	RI_PDQ_CRUSH = 715,
//	RI_PDQ_PNSX,
	RI_PDQ_RESERVED2,//RI_PDQ_CBLOCK,
	RI_PDQ_SCRAPE,
//	RI_PDQ_NYSE_VALUE,
	RI_PDQ_CODASOR,
	RI_PDQ_IEX,
	RI_PDQ_VWAP,
	RI_PDQ_CODAMM,
	RI_PDQ_MIDPOINT_PLUS_FAR_TOUCH,
	RI_PDQ_MIDPOINT_PLUS_LIT,
	RI_PDQ_GMSP,
	RI_PDQ_BEST,
	RI_PDQ_ZEUS,

	RI_SPEEDROUTE_FREE_DARK = 800,
	RI_SPEEDROUTE_MIDPOINT_DARK,
	RI_SPEEDROUTE_FAN_AGGRESSIVE,
	RI_SPEEDROUTE_SPDRM,
	RI_SPEEDROUTE_SPDRX,

	RI_SPEEDROUTE_KROUTE = 807,
	RI_SPEEDROUTE_SPDRF,
	RI_SPEEDROUTE_ARCAEDGE,
	RI_SPEEDROUTE_PINKBB1,
	RI_SPEEDROUTE_PROP,
	RI_SPEEDROUTE_ARCA_IPO,
	RI_SPEEDROUTE_NSDQ_IPO,
	RI_SPEEDROUTE_NYSE_IPO,

	RI_SPEEDROUTE_ATDARK,
	RI_SPEEDROUTE_ATMID,
	RI_SPEEDROUTE_DARKVPS,
	RI_SPEEDROUTE_DARKVP,
	RI_SPEEDROUTE_NTCOVERT,
	RI_SPEEDROUTE_SMARTEDGE,
	RI_SPEEDROUTE_SMARTDARK,
	RI_SPEEDROUTE_XFINDER,
	RI_SPEEDROUTE_XFINDERMID,
	RI_SPEEDROUTE_BAODARK,
	RI_SPEEDROUTE_BAODARKS,
	RI_SPEEDROUTE_BAOMID,
	RI_SPEEDROUTE_BAOMIDXTRA,
	RI_SPEEDROUTE_BAOPOST,
	RI_SPEEDROUTE_SORPOST,
	RI_SPEEDROUTE_VWAP,
	RI_SPEEDROUTE_TWAP,

	RI_SPEEDROUTE_EDARK,
	RI_SPEEDROUTE_ESTLT,
	RI_SPEEDROUTE_ESENS,
	RI_SPEEDROUTE_NYSE_DF,
	RI_SPEEDROUTE_SRSMART,

/*
	RI_CITADEL_MERCURY_DARK	= 900,
	RI_CITADEL_MARKET_ACCESS,
	RI_CITADEL_MARKET_ACCESS_GET,
*/
	RI_CONVERGEX_NIX = 1000,	// Can be DAY, IOC, MOO, LOO, MOC, LOC, GTX, Market, Limit
	RI_CONVERGEX_VORTEX,		// Can be DAY, IOC, Market, Limit, Peg (Mid, Market, Primary)
	RI_CONVERGEX_PBOX,			// Can be IOC, Market, Limit
	RI_CONVERGEX_MILLENNIUM,	// Day orders only, Market, Limit, Peg (Open, Last, Mid, Market, Primary)
		
	RI_APEX_MNGD				= 1200,

	RI_DASH_SENSOR				= 1300,
	RI_DASH_SMOKE,
	RI_DASH_STRIKE,
	RI_DASH_OPTWAP,
	RI_DASH_RETAIL,

	RI_CLEARPOOL_SOR			= 1400,
	RI_CLEARPOOL_DARKAGG,
	RI_CLEARPOOL_AP,
	RI_CLEARPOOL_EDGXAH,
	RI_CLEARPOOL_ARCAAH,
	RI_CLEARPOOL_NSDQAH,

	RI_CLEARPOOL_RSOR,
	RI_CLEARPOOL_PSOR,
	RI_CLEARPOOL_MSOR,
	RI_CLEARPOOL_ASOR,

	RI_CLEARPOOL_SORP,
	RI_CLEARPOOL_SORM,
	RI_CLEARPOOL_SOR1,
	RI_CLEARPOOL_SOR2,
	RI_CLEARPOOL_SOR3,
	RI_CLEARPOOL_DARKAGG1,
	RI_CLEARPOOL_DARKAGG2,
	RI_CLEARPOOL_DARKAGG3,
//For Firm TAIQ only
	RI_CLEARPOOL_VWAP,
	RI_CLEARPOOL_TWAP,
	RI_CLEARPOOL_TWAP2,
	RI_CLEARPOOL_TWAP5,
	RI_CLEARPOOL_TWAP10,
	RI_CLEARPOOL_TWAP15,
	RI_CLEARPOOL_TWAP60,
////

//	RI_IEX_ROUTE_TO_REST		= 1500,
	RI_IEX_ROUTE_TO_REST_RESWEEP= 1501,
//	RI_IEX_ROUTE_TO_TAKE,
	RI_IEX_ROUTE_TO_TAKE_RESWEEP,
//	RI_IEX_ROUTE_TO_REST_AWAY,
	RI_IEX_D_LIMIT				= 1505,
/*
	RI_ITG_SMRTDUAL				= 1600,
	RI_ITG_ITGDP,
	RI_ITG_POSIT,
	RI_ITG_DARK,
*/
	RI_LYNX_BAOFREE				= 1700,
	RI_LYNX_BAOMID,
	RI_LYNX_BAOEXTRA,
	RI_LYNX_BAOPOST,
	RI_LYNX_BAOSMART,
	RI_LYNX_BAODARK,
	RI_LYNX_BAOLIT,
	RI_LYNX_BAOCHEAP,

	RI_LYNX_BAOREBATE,

	RI_LYNX_LONG,
	RI_LYNX_BAOPEG,

	RI_LYNX_ATDARK,
	RI_LYNX_ATMID,
	RI_LYNX_DARKVPS,
	RI_LYNX_DARKVP,
	RI_LYNX_NITECOVERT,
	RI_LYNX_SMARTEDGE,
	RI_LYNX_SMARTDARK,
	RI_LYNX_XFINDER,
	RI_LYNX_XFINDERMID,
	RI_LYNX_BAODARKS,
	RI_LYNX_BAOMIDXTRA,
	RI_LYNX_SORPOST,
//STDR
	RI_LYNX_AGP,
	RI_LYNX_ALLIN,
	RI_LYNX_ALSWEEP,
	RI_LYNX_ATCHEAP,
	RI_LYNX_ATMIDN,
	RI_LYNX_ATSAVE,
	RI_LYNX_BAOEXTHRS,
	RI_LYNX_BAOINST,
	RI_LYNX_BAOMAX,
	RI_LYNX_BAOPHIT,
	RI_LYNX_BAOSSR,
	RI_LYNX_DAGR,
	RI_LYNX_DALM,
	RI_LYNX_DARKPOST,
	RI_LYNX_DARKVPSF,
	RI_LYNX_FAST,
	RI_LYNX_GDARK,
	RI_LYNX_GEILI,
	RI_LYNX_GSOR,
	RI_LYNX_HIT10,
	RI_LYNX_IWDARK,
	RI_LYNX_JPADRKMP,
	RI_LYNX_JPMAGGDARK,
	RI_LYNX_JPMBOXDARK,
	RI_LYNX_JPMMIDDARK,
	RI_LYNX_JPMPSTDARK,
	RI_LYNX_LAMP,
	RI_LYNX_LNITE,
	RI_LYNX_LOCD,
	RI_LYNX_LOOD,
	RI_LYNX_MDARKCOP,
	RI_LYNX_MID88,
	RI_LYNX_MIDP,
	RI_LYNX_MIDPLS,
	RI_LYNX_MLNM,
	RI_LYNX_MOCD,
	RI_LYNX_MOOD,
	RI_LYNX_NIARCA,
	RI_LYNX_NIBATS,
	RI_LYNX_NIEDGX,
	RI_LYNX_NINQPX,
	RI_LYNX_NINSDQ,
	RI_LYNX_NINYSE,
	RI_LYNX_NIX2,
	RI_LYNX_OESDARK,
	RI_LYNX_PDQMMID,
	RI_LYNX_PINKS,
	RI_LYNX_SLAM,
	RI_LYNX_SMARTEDGEP,
	RI_LYNX_SMARTMID,
	RI_LYNX_TONGSHA,
	RI_LYNX_UNDARK,
	RI_LYNX_UNMID,
	RI_LYNX_WANTS,
	RI_LYNX_XALL,
	RI_LYNX_XPOST,
	RI_LYNX_ZACHUAN,
	RI_LYNX_BATSX,
	RI_LYNX_EDGXS,
	RI_LYNX_MEAN,
	RI_LYNX_POOL,
	RI_LYNX_GMID,
	RI_LYNX_GSTOP,
	RI_LYNX_VTRD,
	RI_LYNX_UBER,
	RI_LYNX_CODATST,
	RI_LYNX_LITSWEEP,
	RI_LYNX_ARCA1,
	RI_LYNX_TPROSOR,
	RI_LYNX_TPROMID,
	RI_LYNX_TPROFREE,
	RI_LYNX_TPRODARK,

//END STDR
/*
#ifdef LYNX_REROUTING
	RI_LYNX_NYSEMOO,
	RI_LYNX_NYSEMOC,
	RI_LYNX_NYSELOO,
	RI_LYNX_NYSELOC,
	RI_LYNX_ARCAMOO,
	RI_LYNX_ARCAMOC,
	RI_LYNX_ARCALOO,
	RI_LYNX_ARCALOC,
	RI_LYNX_NSDQMOO,
	RI_LYNX_NSDQMOC,
	RI_LYNX_NSDQLOO,
	RI_LYNX_NSDQLOC,//1722//1720
#endif
*/
	RI_CHSX_SNAP_AUCTION  = 1800,
	RI_CHSX_SNAP_AUCTION_ONLY,

	RI_CUTTONE_CUTP				= 1900,
	RI_CUTTONE_CUTD,
	RI_CUTTONE_CUTR,
	RI_CUTTONE_CUTS,
	RI_CUTTONE_CUTZ,
	RI_CUTTONE_CUTX,
	RI_CUTTONE_CUTC,
	RI_COWEN_SEEK				= 2000,
	RI_COWEN_SWEEP,

	RI_TRAFIX_LAMP_LAMP				= 2100,
	RI_TRAFIX_LAMP_POST,
	RI_TRAFIX_LAMP_PSFL,
	RI_TRAFIX_LAMP_NYSE,
	RI_TRAFIX_LAMP_NSDQ,
	RI_TRAFIX_NSDQ,
	RI_TRAFIX_NYSE,
	RI_TRAFIX_ARCA,
	RI_TRAFIX_SMARTCODA,
	RI_TRAFIX_SMARTLAMP,
	RI_TRAFIX_ARCAPROA,

	RI_TRAFIX_AMEX,
	RI_TRAFIX_AMEXDMA,
	RI_TRAFIX_ARCADMA,
	RI_TRAFIX_ARCAPL,
	RI_TRAFIX_ATMID,
	RI_TRAFIX_BATS,
	RI_TRAFIX_BATSDMA,
	RI_TRAFIX_BYX,
	RI_TRAFIX_BYXDMA,
	RI_TRAFIX_CFINDERP,
	RI_TRAFIX_CHX,
	RI_TRAFIX_DARKALL,
	RI_TRAFIX_DARKMID,
	RI_TRAFIX_DARKVPS,
	RI_TRAFIX_EDGA,
	RI_TRAFIX_EDGADMA,
	RI_TRAFIX_EDGX,
	RI_TRAFIX_EDGXDMA,
	RI_TRAFIX_FREE,
	RI_TRAFIX_HIDS,
	RI_TRAFIX_IEX,
	RI_TRAFIX_IEXDMA,
	RI_TRAFIX_JPMA,
	RI_TRAFIX_MEMX,
	RI_TRAFIX_MIAX,
	RI_TRAFIX_NQBX,
	RI_TRAFIX_NQBXDMA,
	RI_TRAFIX_NQPX,
	RI_TRAFIX_NQPXDMA,
	RI_TRAFIX_NSDQDMA,
	RI_TRAFIX_NSX,
	RI_TRAFIX_NYSEDMA,
	RI_TRAFIX_PDQD,
	RI_TRAFIX_PDQDARK,
	RI_TRAFIX_SMARTMID,
	RI_TRAFIX_SORPOST,
	RI_TRAFIX_SPDREDGA,
	RI_TRAFIX_SPDREDGX,
	RI_TRAFIX_SPDRX,
	RI_TRAFIX_SWRK,
	RI_TRAFIX_ZAPP,
	RI_TRAFIX_CSCX,
	RI_TRAFIX_VCVT,

	RI_INSTINET_CBX	= 2200,			
	RI_INSTINET_COBRA,			
	RI_INSTINET_IS,			
	RI_INSTINET_MAKE,			
	RI_INSTINET_NIGHTHAWK,			
	RI_INSTINET_VWAP,			
	RI_INSTINET_TWAP,			
	RI_INSTINET_LSET_SAVER,
	RI_INSTINET_LSET_SMART,
	RI_INSTINET_AGGRESSIVE,
	RI_INSTINET_TAKESES,
	RI_INSTINET_CDG1KNM1,
	RI_INSTINET_CSCROSS,
	RI_INSTINET_CDELIOC,
	RI_INSTINET_DARKPING,
	RI_INSTINET_SMRTIL,
	RI_INSTINET_BLOCKX,
	RI_INSTINET_VWAPX,
	RI_INSTINET_KNKI,

	RI_PDQ_AGG					= 2300,
	RI_PDQ_AGP,
	RI_PDQ_ALLINWT,
	RI_PDQ_ALLPLUS,
	RI_PDQ_AMEX,
	RI_PDQ_AMEXOPG,
	RI_PDQ_ARCA,
	RI_PDQ_ARCA_EQ,		// Should be shown as ARCA= in pulldown
	RI_PDQ_ARCAALO,
	RI_PDQ_ARCAMPL,
	RI_PDQ_ARCAMPLA,
	RI_PDQ_ARCAONLY,
	RI_PDQ_ARCAOPG,
	RI_PDQ_ARCAPL,
	RI_PDQ_ARCAPOP,
	RI_PDQ_ARCAZ,
	RI_PDQ_ARDOX,
	RI_PDQ_AROUC,
	RI_PDQ_AROUT,
	RI_PDQ_AROUZ,
	RI_PDQ_ASRDOT,
	RI_PDQ_ASROUT,
	RI_PDQ_ASROUX,
	RI_PDQ_ASURDOX,
	RI_PDQ_ASUROUT,
	RI_PDQ_ASUROUX,
	RI_PDQ_ATDARK,
	RI_PDQ_ATMID,
	RI_PDQ_AXFINDER,
	RI_PDQ_BANG10,
	RI_PDQ_BATS,
	RI_PDQ_BATSALIQ,
	RI_PDQ_BATSDS,
	RI_PDQ_BATSONLY,
	RI_PDQ_BATSX,
	RI_PDQ_BATSZ,
	RI_PDQ_BATY,
	RI_PDQ_BATYONLY,
	RI_PDQ_BAYS,
	RI_PDQ_BYX,
	RI_PDQ_BYXMPL,
	RI_PDQ_BYXONLY,
	RI_PDQ_BYXONLY2,
	RI_PDQ_CHEAP,
	RI_PDQ_CPDARK1,
	RI_PDQ_CPDARK2,
	RI_PDQ_CPMID1,
	RI_PDQ_CPMID2,
	RI_PDQ_CPSOR,
	RI_PDQ_CSN,
	RI_PDQ_DAGR,
	RI_PDQ_DARKPLUS,
	RI_PDQ_DARKVPS,
	RI_PDQ_DARKVPSZ,
	RI_PDQ_DPASS,
	RI_PDQ_EDGA,
	RI_PDQ_EDGAALIQ,
	RI_PDQ_EDGAMPL,
	RI_PDQ_EDGAONLY,
	RI_PDQ_EDGAS,
	RI_PDQ_EDGX,
	RI_PDQ_EDGXHNS,
	RI_PDQ_EDGXMPL,
	RI_PDQ_EDGXMPLA,
	RI_PDQ_EDGXS,
	RI_PDQ_EDGXZ,
	RI_PDQ_FAST,
	RI_PDQ_HALF,
	RI_PDQ_ICOB,
	RI_PDQ_IDARK,
	RI_PDQ_PERO_IEX,	// Should be shown as IEX in pulldown. It has preffix _PERO_ to distinguish it from existing RI_PDQ_IEX
	RI_PDQ_IEXMID,
	RI_PDQ_IHAWK,
	RI_PDQ_INET,
	RI_PDQ_MIDPLUS,
	RI_PDQ_NIGHTVSN,
	RI_PDQ_NITECOVRTZ,
	RI_PDQ_NITEPASS,
	RI_PDQ_NQBXMPL,
	RI_PDQ_NQPX,
	RI_PDQ_NQPXMPLA,
	RI_PDQ_NSDQ,
	RI_PDQ_NSDQ2,
	RI_PDQ_NSDQADOT,
	RI_PDQ_NSDQALIQ,
	RI_PDQ_NSDQBX,
	RI_PDQ_NSDQBX2,
	RI_PDQ_NSDQBXALIQ,
	RI_PDQ_NSDQDDOT,
	RI_PDQ_NSDQIO,
	RI_PDQ_NSDQMPLA,
	RI_PDQ_NSDQONLY,
	RI_PDQ_NSDQOPG,
	RI_PDQ_NSDQPX,
	RI_PDQ_NSDQPXALIQ,
	RI_PDQ_NSDQSCAN,
	RI_PDQ_NSDQSMART,
	RI_PDQ_NSDQSTGY,
	RI_PDQ_NSDQZ,
	RI_PDQ_NSX,
	RI_PDQ_NYFB,
	RI_PDQ_NYSE,
	RI_PDQ_NYSEMPL,
	RI_PDQ_NYSEOPG,
	RI_PDQ_NYSEZ,
	RI_PDQ_PASP,
	RI_PDQ_PASS,
	RI_PDQ_POSTPLUS,
	RI_PDQ_PXFINDER,
	RI_PDQ_RAVENDQN,
	RI_PDQ_RDOT,
	RI_PDQ_RDOX,
	RI_PDQ_ROUC,
	RI_PDQ_ROUT,
	RI_PDQ_ROUZ,
	RI_PDQ_SDOT,
	RI_PDQ_SMART,
	RI_PDQ_SMARTCHEAP,
	RI_PDQ_SMARTDARK,
	RI_PDQ_SMARTDARKP,
	RI_PDQ_SMARTEDGE,
	RI_PDQ_SMARTEDGEP,
	RI_PDQ_SMARTMID,
	RI_PDQ_SMRTMID,
	RI_PDQ_SRDOT,
	RI_PDQ_SRDOX,
	RI_PDQ_SROUT,
	RI_PDQ_SROUX,
	RI_PDQ_STOP,
	RI_PDQ_STOPLMT,
	RI_PDQ_STOPMKT,
	RI_PDQ_SUPERMID,
	RI_PDQ_SURDOX,
	RI_PDQ_SUROUT,
	RI_PDQ_SUROUX,
	RI_PDQ_XFINDER,

	RI_PDQ_NASDAQ,
	RI_PDQ_SORPOST,
	RI_PDQ_SMAT,
	RI_PDQ_LAMP,

	RI_IQX_INCR = 2500,
	RI_IQX_ASPN,
	RI_IQX_ASMT,
	RI_IQX_ASPI,
	RI_IQX_ASPN_ALO,
	RI_IQX_ASMT_ALO,
	RI_IQX_ASPI_ALO,

	RI_OTCX_ROUTE_IOC_TO_OTCLINKATS_ONLY = 2600,
	RI_OTCX_POOE,

	RI_VOLANT_SMART = 2700,

	RI_VELOCITY_IEXV = 2800,
	RI_VELOCITY_VMID,
	RI_VELOCITY_LED,
	RI_VELOCITY_LEDL,
	RI_VELOCITY_FLASHLIGHT,
	RI_VELOCITY_DARKSWEEP,
	RI_VELOCITY_TWAP,
	RI_VELOCITY_VWAP,
	RI_VELOCITY_VTRD,
	RI_VELOCITY_VPOST,

	RI_VELOCITY_SMART,
	RI_VELOCITY_AGGRESSIVE,
	RI_VELOCITY_DARK1,
	RI_VELOCITY_DARKPING,
	RI_VELOCITY_DARKPING_MID,
	RI_VELOCITY_DRK1,
	RI_VELOCITY_LSET_DQOPG,
	RI_VELOCITY_LSET_DQT,
	RI_VELOCITY_LSET_SAVER,
	RI_VELOCITY_LSET_PINK,
	RI_VELOCITY_TACTIC2,
	RI_VELOCITY_TAKESE,

	RI_VELOCITY_CODA_ARCA,
	RI_VELOCITY_CODA_BATS,
	RI_VELOCITY_CODA_CDMM,
	RI_VELOCITY_CODA_CDSR,
	RI_VELOCITY_CODA_DKAL,
	RI_VELOCITY_CODA_EDGX,
	RI_VELOCITY_CODA_IEX,
	RI_VELOCITY_CODA_MIDP,
	RI_VELOCITY_CODA_MPFT,
	RI_VELOCITY_CODA_MPPL,
	RI_VELOCITY_CODA_NSDQ,
	RI_VELOCITY_CODA_CRSH,
	RI_VELOCITY_CODA_SCRP,
	RI_VELOCITY_CODA_SONE,
	RI_VELOCITY_CODA_STOW,
	RI_VELOCITY_CODA_SWRK,
	RI_VELOCITY_CODA_VAP,
	RI_VELOCITY_VTRDOPT,//For Options only

	RI_VELOCITY_CODA_AMEX,
	RI_VELOCITY_CODA_AMEXLOO,
	RI_VELOCITY_CODA_AMEXMOC,
	RI_VELOCITY_CODA_AMEXMOO,
	RI_VELOCITY_CODA_ARCAMPLA,
	RI_VELOCITY_CODA_AROUC,
	RI_VELOCITY_CODA_AROUZ,
	RI_VELOCITY_CODA_ASRDOT,
	RI_VELOCITY_CODA_ASROUT,
	RI_VELOCITY_CODA_ASUROUT,
	RI_VELOCITY_CODA_ATMID,
	RI_VELOCITY_CODA_BAOREBATE,
	RI_VELOCITY_CODA_BATSMPLA,
	RI_VELOCITY_CODA_LTSE,
	RI_VELOCITY_CODA_MIAX,
	RI_VELOCITY_CODA_MID88,
	RI_VELOCITY_CODA_MOCD,
	RI_VELOCITY_CODA_NSDQLOC,
	RI_VELOCITY_CODA_NSDQLOO,
	RI_VELOCITY_CODA_NSDQMOC,
	RI_VELOCITY_CODA_NSDQMOO,
	RI_VELOCITY_CODA_NSDQMPLA,
	RI_VELOCITY_CODA_POOL,
	RI_VELOCITY_CODA_ROUZ,
	RI_VELOCITY_CODA_SPDRX,
	RI_VELOCITY_CODA_SRDOT,
	RI_VELOCITY_CODA_SUROUT,
	RI_VELOCITY_CODA_TONGSHA,
	RI_VELOCITY_CODA_TSTUGT,
	RI_VELOCITY_CODA_UBER,
	RI_VELOCITY_CODA_WANTS,
	RI_VELOCITY_CODA_CHX,
	RI_VELOCITY_CODA_DARKVPS,
	RI_VELOCITY_CODA_EDGXALIQ,
	RI_VELOCITY_CODA_EDGXMPLA,
	RI_VELOCITY_CODA_NSX,
	RI_VELOCITY_CODA_NYSE,
	RI_VELOCITY_CODA_NYSELOC,
	RI_VELOCITY_CODA_NYSELOO,
	RI_VELOCITY_CODA_NYSEMOC,
	RI_VELOCITY_CODA_NYSEMOO,
	RI_VELOCITY_CODA_NYSEMPLA,
	RI_VELOCITY_CODA_ARCALOC,
	RI_VELOCITY_CODA_ARCALOO,
	RI_VELOCITY_CODA_ARCAMOC,
	RI_VELOCITY_CODA_ARCAMOO,
	RI_VELOCITY_CODA_MEMXDMA,
	RI_VELOCITY_CODA_NQPX,

	RI_VELOCITY_DARK_BARX,
	RI_VELOCITY_DARK_BNPX,
	RI_VELOCITY_DARK_CDGO,
	RI_VELOCITY_DARK_CSCF,
	RI_VELOCITY_DARK_DRK1,
	RI_VELOCITY_DARK_INCR,
	RI_VELOCITY_DARK_JPMX,
	RI_VELOCITY_DARK_JSJX,
	RI_VELOCITY_DARK_KNKI,
	RI_VELOCITY_DARK_KNMX,
	RI_VELOCITY_DARK_LELV,
	RI_VELOCITY_DARK_MLIX,
	RI_VELOCITY_DARK_MSPL,
	RI_VELOCITY_DARK_NFSC,
	RI_VELOCITY_DARK_PDQX,
	RI_VELOCITY_DARK_SGMA,
//For Firm VCTP Only
	RI_VELOCITY_CODA_HIDS,
	RI_VELOCITY_CODA_CSCX,
	RI_VELOCITY_CODA_SMARTTV,
	RI_VELOCITY_CODA_PDQD,
	RI_VELOCITY_CODA_PDQDARKTV,
///////////
	RI_VELOCITY_LEVL,
	RI_VELOCITY_XTRD,

	RI_Count,

	RI_LYNX_MEMX = 65001,
	RI_LYNX_MIAX,
	RI_LYNX_LTSE,
	RI_LYNX_CHSX,
};


//#define ORDER_STRUCTURE_MEMBER
#define ORDER_RESPONSE_FULL

#ifdef ORDER_STRUCTURE_MEMBER
class TMessageOrderHeader
#else
class TMessageOrderHeader : public TMessageTime
#endif
{
public:
	DWORD		MessageSequenceNumber;
	DWORD		ClOrdID;							//Client assigned order id, I think it is ok to have this as a number instead of string for faster search
	DWORD		ParentClOrdID;
	DWORD		SrOrdID;							// Server assigned order id, server will use a number as well
	char		AccountName[MAX_ACCOUNT_SIZE];		//Order Account Name

// *AK* start
	char		TraderID[MAX_TRADER_ID_SIZE];
	char		FirmID[MAX_FIRM_ID_SIZE];
	DWORD		AcceptedTime;						// When order was accepted by market
	DWORD		CanceledTime;						// When order has been canceled if any
	char		MarketReferenceID[MAX_MARKET_REFERENCE_ID];		// Will be filled with Venue's OrderID
	unsigned char		Tracking;							// Where order is, on server, on market, etc.
	unsigned char		Status;								// New, Partially filled, Canceled, Filled
	char		ConfirmationID[16];					// can be used for short sells. ID from liquidity finder
	unsigned int Quantity;							// Order quantity ( moved from order )
	unsigned int RemainingQuantity;					// Remaining size of the order ( moved from order )
	unsigned int CanceledQuantity;					// Canceled size of the order
// *AK* end

	char		Symbol[MAX_SYMBOL_SIZE];
	unsigned char RealTimeOrRecovered;				//Weather this a current message or recovered message
	DWORD		Time;								//Milliseconds since midnight, when this message is generated
	DWORD		Ip;									//For Compliance

	unsigned char Side;
	unsigned char InstrumentType;

#ifndef ORDER_STRUCTURE_MEMBER
protected:
#endif
	TMessageOrderHeader(const DWORD& clientOrdID,
		const TraderIdType& traderId,
//		const char* const& traderId,
		const char* const& accountName,
		const char* const& firmId,
		const char* const& symbol,
		const unsigned char& side,
		const unsigned int& quantity,
		const DWORD& ip,
#ifndef ORDER_STRUCTURE_MEMBER
		const unsigned short& type,
		const unsigned short& length,
#endif
		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_CLIENT,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,//const char* confirmationID = "",
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0
		):
	#ifndef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, type, length),
	#endif
		MessageSequenceNumber(messageSequenceNumber),
		ClOrdID(clientOrdID),
		ParentClOrdID(parentClOrdID),
		SrOrdID(serverOrdID),
		AcceptedTime(acceptedTime),
		CanceledTime(canceledTime),
		Tracking(tracking),
		Status(status),
		Quantity(quantity),
		RemainingQuantity(remainingQuantity),
		CanceledQuantity(canceledQuantity),
		RealTimeOrRecovered(realTimeOrRecovered),
	#ifndef ORDER_STRUCTURE_MEMBER
		Time(m_time),
	#endif
		Ip(ip),
		Side(side),
		InstrumentType(instrumentType)
	{
	#ifdef ORDER_STRUCTURE_MEMBER
		Time = TL_GetCurrentMillisecond();
	#endif
		U_CopyAndPad(AccountName, sizeof(AccountName), accountName, '\0', true);

//		U_CopyAndPad(TraderID, sizeof(TraderID), traderId, '\0', true);
		*(TraderIdType*)TraderID = traderId;
		TraderID[sizeof(TraderID) - 1] = '\0';

		U_CopyAndPad(FirmID, sizeof(FirmID), firmId, '\0', true);
		U_CopyAndPad(MarketReferenceID, sizeof(MarketReferenceID), marketReferenceID, '\0');
//		U_CopyAndPad(ConfirmationID, sizeof(ConfirmationID), confirmationID, '\0');
		*(unsigned __int64*)ConfirmationID = optionBlock;
		*((unsigned __int64*)ConfirmationID + 1) = 0;
		U_CopyAndPad(Symbol, sizeof(Symbol), symbol, '\0');
	}
};

class TMessageBorrowAcceptRequest : public TMessageOrderHeader
{
public:
	TMessageBorrowAcceptRequest(const DWORD& clientOrdID = 0,
//		const char* const& traderId = "",
		const TraderIdType& traderId = 0,
		const char* const& accountName = "",
		const char* const& firmId = "",
		const char* const& symbol = "",
		const unsigned char& side = '\0',
		const unsigned int& quantity = 0,
		//		const DWORD& route,							// Routes to send order to 
		const ULONGLONG& route = 0,							// Routes to send order to 
		const DWORD& ip = 0,

		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_CLIENT,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0,
		const unsigned int& priceDollar = 0,
		const unsigned int& priceFraction = 0,
		const unsigned int& availableQuantity = 0,
		const char* const& orderId = ""):

		TMessageOrderHeader(clientOrdID,
			traderId,
			accountName,
			firmId, 
			symbol,
			side,
			quantity,
			ip,
			
			TS_BORROW_ACCEPT_REQ,
			sizeof(TMessageBorrowAcceptRequest),

			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType),
		PriceDollar(priceDollar),
		PriceFraction(priceFraction),
		m_availableQuantity(availableQuantity)
	{
		U_CopyAndPad(OrderID, sizeof(OrderID), orderId, '\0');
		*ReasonText = '\0';
	}

	unsigned int PriceDollar;
	unsigned int PriceFraction;
	unsigned int m_availableQuantity;

	char OrderID[MAX_MARKET_REFERENCE_ID];// ID assigned to execution by venue
	char ReasonText[1];
};

class TMessageBorrowAcceptResponse : public TMessageOrderHeader
{
public:
	TMessageBorrowAcceptResponse(const DWORD& clientOrdID = 0,
		const TraderIdType& traderId = 0,
//		const char* const& traderId = "",
		const char* const& accountName = "",
		const char* const& firmId = "",
		const char* const& symbol = "",
		const unsigned char& side = '\0',
		const unsigned int& quantity = 0,
//		const DWORD& route,							// Routes to send order to 
		const ULONGLONG& route = 0,							// Routes to send order to 
		const DWORD& ip = 0,

		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_CLIENT,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0,
		const char* const& orderId = "",
		const bool accepted = false):

		TMessageOrderHeader(clientOrdID,
			traderId,
			accountName,
			firmId, 
			symbol,
			side,
			quantity,
			ip,
			
			TS_BORROW_ACCEPT_RESP,
			sizeof(TMessageBorrowAcceptResponse),

			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType),
		Accepted(accepted)
	{
		U_CopyAndPad(OrderID, sizeof(OrderID), orderId, '\0');
	}
	TMessageBorrowAcceptResponse(const TMessageBorrowAcceptRequest& request, const bool& accepted):
		TMessageOrderHeader(request),
		Accepted(accepted)
	{
		m_type = TS_BORROW_ACCEPT_RESP;
		m_length = sizeof(TMessageBorrowAcceptResponse);
		m_time = TL_GetCurrentMillisecond();
		U_CopyAndPad(OrderID, sizeof(OrderID), request.OrderID, '\0');
	}
	char OrderID[MAX_MARKET_REFERENCE_ID];// ID assigned to execution by venue
	bool Accepted;
};

#ifdef ORDER_STRUCTURE_MEMBER
class TMessageOrderBase : public TMessageTime
#else
class TMessageOrderBase : public TMessageOrderHeader
#endif
//class TMsgReqOrder : public TMessageOrderHeader
{
public:
#ifdef ORDER_STRUCTURE_MEMBER
	TMessageOrderHeader m_header;
#endif
//	DWORD		Date;							// Date for good till date orders
	DWORD		DefaultRoutesHigh;				// High DWORD - for 64 bit Routes (Single ROUTE to default to for execution).

	unsigned char Type;							// Order type, market, limit, etc
	unsigned char TIF;							// TIF or Order duration 

	unsigned int MinQuantity;					// Minimum quantity to process order
												// if equals quantity, then all or nothing
	unsigned int DisplayQuantity;				// Reserve order display quantity

	unsigned char QuantityType;					// Quantity type that generated the above qty
	unsigned char PriceType;						// Price type that generated the above price

//	DWORD		Route;							// Routes to send order to 
//	DWORD		ExcludeRoutes;					// Routes to exclude when executing order.
//	DWORD		DefaultRoutes;					// Single ROUTE to default to for execution.

	ULONGLONG Route;							// Routes to send order to 
	DWORD DefaultRoutesLow;					// Single ROUTE to default to for execution.

	unsigned char TicketCount;					// Number of orders that is part of the
												// same ticket counted down.
	unsigned char CroxRetryCounter;					// Counter for CROX retries to stop retries in case something goes wrong with the cancel/repalce

	unsigned short TicketID;						// Ticket ID assigned by client.

	unsigned int LastPriceDollar;						// Last bid/ask price 
	unsigned int LastPriceFraction;						// Last bid/ask price

	unsigned int BidPriceDollar;						// Latest bid price
	unsigned int BidPriceFraction;						// Latest bid price

	unsigned int AskPriceDollar;						// Latest ask price
	unsigned int AskPriceFraction;						// Latest ask price

	unsigned int LimitPriceDollar;						// Limit price
	unsigned int LimitPriceFraction;						// Limit price

	int StopPriceDollar;						// Stop price 
	int StopPriceFraction;						// Stop price 

	unsigned int AuxPriceDollar;						// For discretionary and scaled orders
	unsigned int AuxPriceFraction;						// For discretionary and scaled orders
// *AK* start
	DWORD		SubType;						// Additional Flags for Order, like type of peg...
	DWORD		ExecInst;						// Execution Instructions
	DWORD		RoutingInstructions;			// Routing Instructions to direct venue whether to route order out and where

	unsigned int DisplayPriceDollar;					// Also can be used for discretionary orders
	unsigned int DisplayPriceFraction;					// Also can be used for discretionary orders
	
	unsigned int ReserveQuantity;				// Reserve size
	unsigned int RefreshQuantity;				// Refresh size
	unsigned int DiscretionQuantity;				// Discretion size
	DWORD		ExpireTime;						// Number of milliseconds before order should expire (for TIF = '6')
	DWORD		EffectiveTime;					// When order should become active
	char		Capacity;						// Agency, principal, etc.
// *AK* end
	char		market_maker[MAX_MMID_SIZE];	// Market maker ID string, don't know whether we need it...
protected:
//	TS_ORDER_MSG_HEADER		Header;
	TMessageOrderBase(const DWORD& clientOrdID,
		const TraderIdType& traderId,
//		const char* const& traderId,
		const char* const& accountName,
		const char* const& firmId,
		const char* const& symbol,
		const unsigned char& side,
		const unsigned int& quantity,
//		const DWORD& route,							// Routes to send order to 
		const ULONGLONG& route,							// Routes to send order to 
		const DWORD& ip,

		const unsigned short& type,
		const unsigned short& length,

		const unsigned char& orderType = ORDER_TYPE_MARKET,
		const unsigned int& limitPriceDollar = 0,						// Limit price
		const unsigned int& limitPriceFraction = 0,					// Limit price

		const unsigned char& tifType = TIF_DAY,

		const unsigned int& expireTime = 0,						// Number of milliseconds before order should expire (for TIF = '6')
		const unsigned int& effectiveTime = 0,					// When order should become active
//?
		const char& capacity = 0,						// Agency, principal, etc.

		const char* const& mm = "",	// Market maker ID string, don't know whether we need it...

		const int& stopPriceDollar = 0,						// Stop price 
		const int& stopPriceFraction = 0,						// Stop price 

		const unsigned int& minQuantity = 0,
		const unsigned int& displayQuantity = 0,				// Reserve order display quantity
		const unsigned char& quantityType = 0,					// Quantity type that generated the above qty
		const unsigned int& reserveQuantity = 0,				// Reserve size
		const unsigned int& refreshQuantity = 0,				// Refresh size
		const unsigned int& discretionQuantity = 0,				// Discretion size


		const unsigned char& priceType = 0,						// Price type that generated the above price

		const unsigned int& displayPriceDollar = 0,					// Also can be used for discretionary orders
		const unsigned int& displayPriceFraction = 0,					// Also can be used for discretionary orders

		const unsigned int& lastPriceDollar = 0,						// Last bid/ask price 
		const unsigned int& lastPriceFraction = 0,						// Last bid/ask price

		const unsigned int& bidPriceDollar = 0,						// Latest bid price
		const unsigned int& bidPriceFraction = 0,						// Latest bid price

		const unsigned int& askPriceDollar = 0,						// Latest ask price
		const unsigned int& askPriceFraction = 0,						// Latest ask price

		const unsigned int& auxPriceDollar = 0,						// For discretionary and scaled orders
		const unsigned int& auxPriceFraction = 0,						// For discretionary and scaled orders

//		const unsigned int& date = 0,
		const DWORD& defaultRoutesHigh = NULL_ROUTE,					// Single ROUTE to default to for execution.

//		const DWORD& excludeRoutes = NULL_ROUTE,					// Routes to exclude when executing order.
		const DWORD& defaultRoutesLow = NULL_ROUTE,					// Single ROUTE to default to for execution.
		const unsigned char& ticketCount = 0,					// Number of orders that is part of the
												// same ticket counted down.
		const unsigned short& ticketID = 0,						// Ticket ID assigned by client.

		const DWORD& subType = 0,						// Additional Flags for Order, like type of peg...
		const DWORD& execInst = 0,						// Execution Instructions
		const DWORD& routingInstructions = 0,			// Routing Instructions to direct venue whether to route order out and where

		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_CLIENT,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0
		):
#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, TS_ORDER, sizeof(TMsgReqOrder)),
		m_header(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip),
#else
		TMessageOrderHeader(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip,
			
			type,
			length,

			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType),
#endif
//		Date(date),
		DefaultRoutesHigh(defaultRoutesHigh),
		Type(orderType),
		TIF(tifType),
		MinQuantity(minQuantity),
		DisplayQuantity(displayQuantity),
		QuantityType(quantityType),
		PriceType(priceType),
		Route(route),
//		ExcludeRoutes(excludeRoutes),
		DefaultRoutesLow(defaultRoutesLow),
		TicketCount(ticketCount),
		TicketID(ticketID),
		LastPriceDollar(lastPriceDollar),
		LastPriceFraction(lastPriceFraction),
		BidPriceDollar(bidPriceDollar),
		BidPriceFraction(bidPriceFraction),
		AskPriceDollar(askPriceDollar),
		AskPriceFraction(askPriceFraction),
		LimitPriceDollar(limitPriceDollar),
		LimitPriceFraction(limitPriceFraction),
		StopPriceDollar(stopPriceDollar),
		StopPriceFraction(stopPriceFraction),
		AuxPriceDollar(auxPriceDollar),
		AuxPriceFraction(auxPriceFraction),
		SubType(subType),
		ExecInst(execInst),
		RoutingInstructions(routingInstructions),
		DisplayPriceDollar(displayPriceDollar),
		DisplayPriceFraction(displayPriceFraction),
		ReserveQuantity(reserveQuantity),
		RefreshQuantity(refreshQuantity),
		DiscretionQuantity(discretionQuantity),
		ExpireTime(expireTime),
		EffectiveTime(effectiveTime),
		Capacity(capacity)
	{
//		U_CopyAndPad(market_maker, sizeof(market_maker) - 1, mm ? mm : "", '\0');
//		market_maker[sizeof(market_maker) - 1] = '\0';
		U_CopyAndPad(market_maker, sizeof(market_maker), mm ? mm : "", '\0', true);
	}
};

class TMsgReqOrder : public TMessageOrderBase
{
public:
//	TS_ORDER_MSG_HEADER		Header;
	TMsgReqOrder(const DWORD& clientOrdID,
		const TraderIdType& traderId,
//		const char* const& traderId,
		const char* const& accountName,
		const char* const& firmId,
		const char* const& symbol,
		const unsigned char& side,
		const unsigned int& quantity,

//		const DWORD& route,							// Routes to send order to 
		const ULONGLONG& route,							// Routes to send order to 

		const DWORD& ip,

		const unsigned char& orderType = ORDER_TYPE_MARKET,
		const unsigned int& limitPriceDollar = 0,						// Limit price
		const unsigned int& limitPriceFraction = 0,					// Limit price

		const unsigned char& tifType = TIF_DAY,

		const unsigned int& expireTime = 0,						// Number of milliseconds before order should expire (for TIF = '6')
		const unsigned int& effectiveTime = 0,					// When order should become active
//?
		const char& capacity = 0,						// Agency, principal, etc.

		const char* const& mm = "",	// Market maker ID string, don't know whether we need it...

		const int& stopPriceDollar = 0,						// Stop price 
		const int& stopPriceFraction = 0,						// Stop price 

		const unsigned int& minQuantity = 0,
		const unsigned int& displayQuantity = 0,				// Reserve order display quantity
		const unsigned char& quantityType = 0,					// Quantity type that generated the above qty
		const unsigned int& reserveQuantity = 0,				// Reserve size
		const unsigned int& refreshQuantity = 0,				// Refresh size
		const unsigned int& discretionQuantity = 0,				// Discretion size

		const unsigned char& priceType = 0,						// Price type that generated the above price

		const unsigned int& displayPriceDollar = 0,					// Also can be used for discretionary orders
		const unsigned int& displayPriceFraction = 0,					// Also can be used for discretionary orders

		const unsigned int& lastPriceDollar = 0,						// Last bid/ask price 
		const unsigned int lastPriceFraction = 0,						// Last bid/ask price

		const unsigned int& bidPriceDollar = 0,						// Latest bid price
		const unsigned int& bidPriceFraction = 0,						// Latest bid price

		const unsigned int& askPriceDollar = 0,						// Latest ask price
		const unsigned int& askPriceFraction = 0,						// Latest ask price

		const unsigned int& auxPriceDollar = 0,						// For discretionary and scaled orders
		const unsigned int& auxPriceFraction = 0,						// For discretionary and scaled orders

//		const unsigned int& date = 0,
		const DWORD& defaultRoutesHigh = NULL_ROUTE,					// Single ROUTE to default to for execution.

//		const DWORD& excludeRoutes = NULL_ROUTE,					// Routes to exclude when executing order.
//		const DWORD& defaultRoutes = NULL_ROUTE,					// Single ROUTE to default to for execution.
		const DWORD& defaultRoutesLow = NULL_ROUTE,					// Single ROUTE to default to for execution.

		const unsigned char& ticketCount = 0,					// Number of orders that is part of the
												// same ticket counted down.
		const unsigned short& ticketID = 0,						// Ticket ID assigned by client.

		const DWORD& subType = 0,						// Additional Flags for Order, like type of peg...
		const DWORD& execInst = 0,						// Execution Instructions
		const DWORD& routingInstructions = 0,			// Routing Instructions to direct venue whether to route order out and where

		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_CLIENT,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0
		):
	TMessageOrderBase(clientOrdID,
		traderId,
		accountName,
		firmId,
		symbol,
		side,
		quantity,
		route,							// Routes to send order to 
		ip,
		TS_ORDER, sizeof(TMsgReqOrder),

		orderType,
		limitPriceDollar,						// Limit price
		limitPriceFraction,					// Limit price

		tifType,

		expireTime,						// Number of milliseconds before order should expire (for TIF = '6')
		effectiveTime,					// When order should become active
//?
		capacity,						// Agency, principal, etc.

		mm,	// Market maker ID string, don't know whether we need it...

		stopPriceDollar,						// Stop price 
		stopPriceFraction,						// Stop price 

		minQuantity,
		displayQuantity,				// Reserve order display quantity
		quantityType,					// Quantity type that generated the above qty
		reserveQuantity,				// Reserve size
		refreshQuantity,				// Refresh size
		discretionQuantity,				// Discretion size


		priceType,						// Price type that generated the above price

		displayPriceDollar,					// Also can be used for discretionary orders
		displayPriceFraction,					// Also can be used for discretionary orders

		lastPriceDollar,						// Last bid/ask price 
		lastPriceFraction,						// Last bid/ask price

		bidPriceDollar,						// Latest bid price
		bidPriceFraction,						// Latest bid price

		askPriceDollar,						// Latest ask price
		askPriceFraction,						// Latest ask price

		auxPriceDollar,						// For discretionary and scaled orders
		auxPriceFraction,						// For discretionary and scaled orders

//		date,
		defaultRoutesHigh,

//		excludeRoutes,					// Routes to exclude when executing order.
//		defaultRoutes,					// Single ROUTE to default to for execution.
		defaultRoutesLow,

		ticketCount,					// Number of orders that is part of the
												// same ticket counted down.
		ticketID,						// Ticket ID assigned by client.

// *AK* start
		subType,						// Additional Flags for Order, like type of peg...
		execInst,						// Execution Instructions
		routingInstructions,			// Routing Instructions to direct venue whether to route order out and where

		messageSequenceNumber,
		serverOrdID,
		parentClOrdID,
		acceptedTime,
		canceledTime,
		marketReferenceID,
		tracking,
		status,
		optionBlock,//confirmationID,
		remainingQuantity,
		canceledQuantity,
		realTimeOrRecovered,
		instrumentType
	)
	{
	}
};

class TMsgOrderError : public TMessageOrderBase
{
public:
	TMsgOrderError(const TMessageOrderBase& orderBase,
		const unsigned char& errorCode = 0,
		const char& side = 0,
		const unsigned short& userOrderType = 0,
		const unsigned __int64& userOrderId = 0,
		const void* userData = nullptr,
		const unsigned int& parentId = 0,
		const unsigned int& splitParentClientId = 0,
		const unsigned int& splitChildClientId = 0,
		const unsigned int& sendId = 0,
		const unsigned int& orderBeingReplacedClientId = 0,
		const unsigned __int64& orderBeingReplacedUserId = 0,
		const Money& moneyValue = Money::moneyZero,
		const Money& moneyConstraint = Money::moneyZero,
		const unsigned int& uintValue = 0,
		const unsigned int& uintConstraint = 0,
		const bool& alert = false):
		TMessageOrderBase(orderBase),
		m_errorCode(errorCode),
		m_side(side),
		m_alert(alert),
		m_userOrderType(userOrderType),
		m_userOrderId(userOrderId),
		m_userData(userData),
		m_parentId(parentId),
		m_splitParentId(splitParentClientId),
		m_splitChildId(splitChildClientId),
		m_sendId(sendId),
		m_orderBeingReplacedClientId(orderBeingReplacedClientId),
		m_orderBeingReplacedUserId(orderBeingReplacedUserId),
		m_moneyValue(moneyValue),
		m_moneyConstraint(moneyConstraint),
		m_uintValue(uintValue),
		m_uintConstraint(uintConstraint)
	{
		m_type = TM_ORDER_ERROR;
		m_length = sizeof(TMsgOrderError);
	}
	unsigned char m_errorCode;
	char m_side;
	bool m_alert;
	unsigned short m_userOrderType;
	unsigned __int64 m_userOrderId;
	const void* m_userData;
	unsigned int m_parentId;
	unsigned int m_splitParentId;
	unsigned int m_splitChildId;
	unsigned int m_sendId;
	unsigned int m_orderBeingReplacedClientId;
	unsigned __int64 m_orderBeingReplacedUserId;
	Money m_moneyValue;
	Money m_moneyConstraint;
	unsigned int m_uintValue;
	unsigned int m_uintConstraint;
};

class TMsgCancelError : public TMessageOrderHeader
{
public:
	TMsgCancelError(const TMessageOrderHeader& orderHeader,
		const unsigned char& errorCode = 0,
		const char& side = 0,
		const Money& moneyValue = Money::moneyZero,
		const Money& moneyConstraint = Money::moneyZero,
		const unsigned int& uintValue = 0,
		const unsigned int& uintConstraint = 0):
		TMessageOrderHeader(orderHeader),
		m_errorCode(errorCode),
		m_side(side),
		m_moneyValue(moneyValue),
		m_moneyConstraint(moneyConstraint),
		m_uintValue(uintValue),
		m_uintConstraint(uintConstraint)
	{
		m_type = TM_CANCEL_ERROR;
		m_length = sizeof(TMsgCancelError);
	}
	unsigned char m_errorCode;
	char m_side;
	Money m_moneyValue;
	Money m_moneyConstraint;
	unsigned int m_uintValue;
	unsigned int m_uintConstraint;
};



#ifdef ORDER_STRUCTURE_MEMBER
class TMsgOrderAck : public TMessageTime
#else
#ifdef ORDER_RESPONSE_FULL
class TMsgOrderAck : public TMessageOrderBase
#else
class TMsgOrderAck : public TMessageOrderHeader
#endif
#endif
{
public:
	TMsgOrderAck(const DWORD& clientOrdID = 0,
		const TraderIdType& traderId = 0,
//		const char* const& traderId = "",
		const char* const& accountName = "",
		const char* const& firmId = "",
		const char* const& symbol = "",
		const unsigned char& side = 0,
		const unsigned int& quantity = 0,

#ifdef ORDER_RESPONSE_FULL
//		const DWORD& route = 0,							// Routes to send order to 
		const ULONGLONG& route = 0,							// Routes to send order to 
#endif
		const DWORD& ip = 0,

#ifdef ORDER_RESPONSE_FULL
		const unsigned char& orderType = ORDER_TYPE_MARKET,
		const unsigned int& limitPriceDollar = 0,						// Limit price
		const unsigned int& limitPriceFraction = 0,					// Limit price

		const unsigned char& tifType = TIF_DAY,

		const unsigned int& expireTime = 0,						// Number of milliseconds before order should expire (for TIF = '6')
		const unsigned int& effectiveTime = 0,					// When order should become active
//?
		const char& capacity = 0,						// Agency, principal, etc.

		const char* const& mm = "",	// Market maker ID string, don't know whether we need it...

		const int& stopPriceDollar = 0,						// Stop price 
		const int& stopPriceFraction = 0,						// Stop price 

		const unsigned int& minQuantity = 0,
		const unsigned int& displayQuantity = 0,				// Reserve order display quantity
		const unsigned char& quantityType = 0,					// Quantity type that generated the above qty
		const unsigned int& reserveQuantity = 0,				// Reserve size
		const unsigned int& refreshQuantity = 0,				// Refresh size
		const unsigned int& discretionQuantity = 0,				// Discretion size

		const unsigned char& priceType = 0,						// Price type that generated the above price

		const unsigned int& displayPriceDollar = 0,					// Also can be used for discretionary orders
		const unsigned int& displayPriceFraction = 0,					// Also can be used for discretionary orders

		const unsigned int& lastPriceDollar = 0,						// Last bid/ask price 
		const unsigned int& lastPriceFraction = 0,						// Last bid/ask price

		const unsigned int& bidPriceDollar = 0,						// Latest bid price
		const unsigned int& bidPriceFraction = 0,						// Latest bid price

		const unsigned int& askPriceDollar = 0,						// Latest ask price
		const unsigned int& askPriceFraction = 0,						// Latest ask price

		const unsigned int& auxPriceDollar = 0,						// For discretionary and scaled orders
		const unsigned int& auxPriceFraction = 0,						// For discretionary and scaled orders

//		const unsigned int& date = 0,
		const DWORD& defaultRoutesHigh = NULL_ROUTE,					// Single ROUTE to default to for execution.

//		const DWORD& excludeRoutes = NULL_ROUTE,					// Routes to exclude when executing order.
//		const DWORD& defaultRoutes = NULL_ROUTE,					// Single ROUTE to default to for execution.
		const DWORD& defaultRoutesLow = NULL_ROUTE,					// Single ROUTE to default to for execution.

		const unsigned char& ticketCount = 0,					// Number of orders that is part of the
												// same ticket counted down.
		const unsigned short& ticketID = 0,						// Ticket ID assigned by client.

		const DWORD& subType = 0,						// Additional Flags for Order, like type of peg...
		const DWORD& execInst = 0,						// Execution Instructions
		const DWORD& routingInstructions = 0,			// Routing Instructions to direct venue whether to route order out and where
#endif
		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_SERVER,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0
		):
#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, TS_ORDER_ACK, sizeof(TMsgOrderAck)),
		m_header(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip)
#else
#ifdef ORDER_RESPONSE_FULL
		TMessageOrderBase(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			route,							// Routes to send order to 
			ip,
			TS_ORDER_ACK, sizeof(TMsgOrderAck),

			orderType,
			limitPriceDollar,						// Limit price
			limitPriceFraction,					// Limit price

			tifType,

			expireTime,						// Number of milliseconds before order should expire (for TIF = '6')
			effectiveTime,					// When order should become active
	//?
			capacity,						// Agency, principal, etc.

			mm,	// Market maker ID string, don't know whether we need it...

			stopPriceDollar,						// Stop price 
			stopPriceFraction,						// Stop price 

			minQuantity,
			displayQuantity,				// Reserve order display quantity
			quantityType,					// Quantity type that generated the above qty
			reserveQuantity,				// Reserve size
			refreshQuantity,				// Refresh size
			discretionQuantity,				// Discretion size


			priceType,						// Price type that generated the above price

			displayPriceDollar,					// Also can be used for discretionary orders
			displayPriceFraction,					// Also can be used for discretionary orders

			lastPriceDollar,						// Last bid/ask price 
			lastPriceFraction,						// Last bid/ask price

			bidPriceDollar,						// Latest bid price
			bidPriceFraction,						// Latest bid price

			askPriceDollar,						// Latest ask price
			askPriceFraction,						// Latest ask price

			auxPriceDollar,						// For discretionary and scaled orders
			auxPriceFraction,						// For discretionary and scaled orders

//			date,
			defaultRoutesHigh,

//			excludeRoutes,					// Routes to exclude when executing order.
//			defaultRoutes,					// Single ROUTE to default to for execution.
			defaultRoutesLow,					// Single ROUTE to default to for execution.

			ticketCount,					// Number of orders that is part of the
													// same ticket counted down.
			ticketID,						// Ticket ID assigned by client.

	// *AK* start
			subType,						// Additional Flags for Order, like type of peg...
			execInst,						// Execution Instructions
			routingInstructions,			// Routing Instructions to direct venue whether to route order out and where

			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
#else
		TMessageOrderHeader(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip,
			TS_ORDER_ACK, sizeof(TMsgOrderAck),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
#endif
#endif
	{
	}
#ifdef ORDER_STRUCTURE_MEMBER
#ifdef ORDER_RESPONSE_FULL
	TMessageOrderBase m_header;
#else
	TMessageOrderHeader m_header;
#endif
#endif
};

// *AK* start
//TS->TSClient, Sent by TS upon accepting the new order TS_ORDER_MESSAGE or any updates to old order
#ifdef ORDER_STRUCTURE_MEMBER
class TMsgOrderUpdate : public TMessageTime
#else
#ifdef ORDER_RESPONSE_FULL
class TMsgOrderUpdate : public TMessageOrderBase
#else
class TMsgOrderUpdate : public TMessageOrderHeader
#endif
#endif
{
public:
	TMsgOrderUpdate(const DWORD& clientOrdID = 0,
		const TraderIdType& traderId = 0,
//		const char* const& traderId = "",
		const char* const& accountName = "",
		const char* const& firmId = "",
		const char* const& symbol = "",
		const unsigned char& side = 0,
		const unsigned int& quantity = 0,
#ifdef ORDER_RESPONSE_FULL
//		const DWORD& route = 0,							// Routes to send order to 
		const ULONGLONG& route = 0,							// Routes to send order to 
#endif
		const DWORD& ip = 0,

#ifdef ORDER_RESPONSE_FULL
		const unsigned char& orderType = ORDER_TYPE_MARKET,
		const unsigned int& limitPriceDollar = 0,						// Limit price
		const unsigned int& limitPriceFraction = 0,					// Limit price

		const unsigned char& tifType = TIF_DAY,

		const unsigned int& expireTime = 0,						// Number of milliseconds before order should expire (for TIF = '6')
		const unsigned int& effectiveTime = 0,					// When order should become active
//?
		const char& capacity = 0,						// Agency, principal, etc.

		const char* const& mm = "",	// Market maker ID string, don't know whether we need it...

		const int& stopPriceDollar = 0,						// Stop price 
		const int& stopPriceFraction = 0,						// Stop price 

		const unsigned int& minQuantity = 0,
		const unsigned int& displayQuantity = 0,				// Reserve order display quantity
		const unsigned char& quantityType = 0,					// Quantity type that generated the above qty
		const unsigned int& reserveQuantity = 0,				// Reserve size
		const unsigned int& refreshQuantity = 0,				// Refresh size
		const unsigned int& discretionQuantity = 0,				// Discretion size

		const unsigned char& priceType = 0,						// Price type that generated the above price

		const unsigned int& displayPriceDollar = 0,					// Also can be used for discretionary orders
		const unsigned int& displayPriceFraction = 0,					// Also can be used for discretionary orders

		const unsigned int& lastPriceDollar = 0,						// Last bid/ask price 
		const unsigned int& lastPriceFraction = 0,						// Last bid/ask price

		const unsigned int& bidPriceDollar = 0,						// Latest bid price
		const unsigned int& bidPriceFraction = 0,						// Latest bid price

		const unsigned int& askPriceDollar = 0,						// Latest ask price
		const unsigned int& askPriceFraction = 0,						// Latest ask price

		const unsigned int& auxPriceDollar = 0,						// For discretionary and scaled orders
		const unsigned int& auxPriceFraction = 0,						// For discretionary and scaled orders

//		const unsigned int& date = 0,
		const DWORD& defaultRoutesHigh = NULL_ROUTE,					// Single ROUTE to default to for execution.

//		const DWORD& excludeRoutes = NULL_ROUTE,					// Routes to exclude when executing order.
//		const DWORD& defaultRoutes = NULL_ROUTE,					// Single ROUTE to default to for execution.
		const DWORD& defaultRoutesLow = NULL_ROUTE,					// Single ROUTE to default to for execution.

		const unsigned char& ticketCount = 0,					// Number of orders that is part of the
												// same ticket counted down.
		const unsigned short& ticketID = 0,						// Ticket ID assigned by client.

		const DWORD& subType = 0,						// Additional Flags for Order, like type of peg...
		const DWORD& execInst = 0,						// Execution Instructions
		const DWORD& routingInstructions = 0,			// Routing Instructions to direct venue whether to route order out and where
#endif
		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_MARKET,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0
		):
#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, TS_ORDER_UPDATE, sizeof(TMsgOrderUpdate)),
		m_header(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip)
#else
#ifdef ORDER_RESPONSE_FULL
		TMessageOrderBase(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			route,							// Routes to send order to 
			ip,
			TS_ORDER_UPDATE, sizeof(TMsgOrderUpdate),

			orderType,
			limitPriceDollar,						// Limit price
			limitPriceFraction,					// Limit price

			tifType,

			expireTime,						// Number of milliseconds before order should expire (for TIF = '6')
			effectiveTime,					// When order should become active
	//?
			capacity,						// Agency, principal, etc.

			mm,	// Market maker ID string, don't know whether we need it...

			stopPriceDollar,						// Stop price 
			stopPriceFraction,						// Stop price 

			minQuantity,
			displayQuantity,				// Reserve order display quantity
			quantityType,					// Quantity type that generated the above qty
			reserveQuantity,				// Reserve size
			refreshQuantity,				// Refresh size
			discretionQuantity,				// Discretion size


			priceType,						// Price type that generated the above price

			displayPriceDollar,					// Also can be used for discretionary orders
			displayPriceFraction,					// Also can be used for discretionary orders

			lastPriceDollar,						// Last bid/ask price 
			lastPriceFraction,						// Last bid/ask price

			bidPriceDollar,						// Latest bid price
			bidPriceFraction,						// Latest bid price

			askPriceDollar,						// Latest ask price
			askPriceFraction,						// Latest ask price

			auxPriceDollar,						// For discretionary and scaled orders
			auxPriceFraction,						// For discretionary and scaled orders

//			date,
			defaultRoutesHigh,					// Single ROUTE to default to for execution.

//			excludeRoutes,					// Routes to exclude when executing order.
//			defaultRoutes,					// Single ROUTE to default to for execution.
			defaultRoutesLow,					// Single ROUTE to default to for execution.

			ticketCount,					// Number of orders that is part of the
													// same ticket counted down.
			ticketID,						// Ticket ID assigned by client.

	// *AK* start
			subType,						// Additional Flags for Order, like type of peg...
			execInst,						// Execution Instructions
			routingInstructions,			// Routing Instructions to direct venue whether to route order out and where

			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
#else
		TMessageOrderHeader(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip,
			TS_ORDER_UPDATE, sizeof(TMsgOrderUpdate),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
#endif
#endif
	{
	}
#ifdef ORDER_STRUCTURE_MEMBER
#ifdef ORDER_RESPONSE_FULL
	TMessageOrderBase m_header;
#else
	TMessageOrderHeader m_header;
#endif
#endif
};

//Order reject codes 
enum OrderRejectCodes : WORD
{
	ORDER_REJECT_CODE_BAD_SYMBOL = 1,
	ORDER_REJECT_CODE_NO_OWN,// =				2,
	ORDER_REJECT_CODE_SMALL_OWN,// =			3,
	ORDER_REJECT_CODE_ROUTE_UNAVAILABLE,// =	4,
	ORDER_REJECT_CODE_REJECTED_BY_ROUTE,// =	5,
	ORDER_REJECT_CODE_VALIDATION_FAILED,// =	6,
	ORDER_REJECT_CODE_BAD_TRADER_ID,// =		7,
	ORDER_REJECT_CODE_BAD_ACCOUNT,// =			8,
	ORDER_REJECT_CODE_CIRCUIT_BREAKER,//				9
	ORDER_REJECT_CODE_ORIGINAL_ORDER_NOT_FOUND,//		10
	ORDER_REJECT_CODE_REPL_ORDER_PARAM_CONFLICT,//		11
	ORDER_REJECT_CODE_FIRM_NOT_FOUND,//				12
	ORDER_REJECT_CODE_ALGO_NOT_FOUND,//				13
	ORDER_REJECT_CODE_ORDER_SENDER_NOT_REGISTERED,//	14
	ORDER_REJECT_CODE_SOR_UNABLE_TO_REQ_SNAPSHOT,//	15
	ORDER_REJECT_CODE_SOR_UNABLE_TO_CREATE_STEPS,//	16
	ORDER_REJECT_CODE_MALFORMED_ALGO_TEMPLATE,//		17
	ORDER_REJECT_CODE_INVALID_MNEMONIC,//				18
	ORDER_REJECT_CODE_ROUTING_INSTRUCTIONS_NOT_SUPPORTED,//19
	ORDER_REJECT_CODE_NATIVE_STOP_ORDER_NOT_SUPPORTED,//20
	ORDER_REJECT_CODE_CANCEL_REPLACE_DISABLED_FOR_THIS_ROUTE,//	21
	ORDER_REJECT_CODE_POSSIBLE_WASH_TRADE,//			22
	ORDER_REJECT_CODE_BAD_CLEARING_ACCOUNT,//			23

	ORDER_REJECT_CODE_Count
};
//TS->TSClient, Sent by TS if the new order TS_ORDER_MESSAGE is rejected


#ifdef ORDER_STRUCTURE_MEMBER
class TMsgOrderReason : public TMessageTime
#else
class TMsgOrderReason : public TMessageOrderHeader
#endif
{
public:
#ifdef ORDER_STRUCTURE_MEMBER
	TMessageOrderHeader m_header;
#endif
	WORD					ReasonCode;			// Reject code
	char					ReasonText[1];		//	Reject String
protected:
	TMsgOrderReason(const DWORD& clientOrdID,
		const TraderIdType& traderId,
//		const char* const& traderId,
		const char* const& accountName,
		const char* const& firmId,
		const char* const& symbol,
		const unsigned char& side,
		const unsigned int& quantity,
		const DWORD& ip,

		const WORD& reasonCode,

		const unsigned short& type,
		const unsigned short& length,

		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_CLIENT,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0
		):
#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, type, length),
		m_header(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip),
#else
		TMessageOrderHeader(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip,
			type, length,
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType),
#endif
		ReasonCode(reasonCode)
	{
		*ReasonText = '\0';
	}
};

class TMsgOrderReject : public TMsgOrderReason
{
public:
	TMsgOrderReject(const DWORD& clientOrdID = 0,
		const TraderIdType& traderId = 0,
//		const char* const& traderId = "",
		const char* const& accountName = "",
		const char* const& firmId = "",
		const char* const& symbol = "",
		const unsigned char& side = 0,
		const unsigned int& quantity = 0,
		const DWORD& ip = 0,

		const WORD& rejectCode = 0,

		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_SERVER,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0):
		TMsgOrderReason(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip,
			rejectCode,
			TS_ORDER_REJECT, sizeof(TMsgOrderReject),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
	{
	}
};

enum CancelRejectCodes : WORD
{
	CANCEL_REJECT_CODE_ROUTE_UNAVAILABLE =	1,
	CANCEL_REJECT_TOO_LATE_TO_CANCEL =		'0',
	CANCEL_REJECT_UNKNOWN_ORDER =			'1',
	CANCEL_REJECT_BROKER_OPTION =			'2',
	CANCEL_REJECT_ALREADY_PENDING_CANCEL =	'3',

	CANCEL_REJECT_CODE_ZERO = 0xFFFF
};

class TMsgCancelReject : public TMsgOrderReason
{
public:
	TMsgCancelReject(const DWORD& clientOrdID = 0,
		const TraderIdType& traderId = 0,
//		const char* const& traderId = "",
		const char* const& accountName = "",
		const char* const& firmId = "",
		const char* const& symbol = "",
		const unsigned char& side = 0,
		const unsigned int& quantity = 0,
		const DWORD& ip = 0,

		const WORD& rejectCode = 0,

		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_SERVER,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0):
		TMsgOrderReason(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip,
			rejectCode,
			TS_CANCEL_REJECT, sizeof(TMsgCancelReject),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
	{
	}
};



enum ReportTypeFlags : WORD
{
	REPORT_FILLED = 0x01,	// Part or all of order filled
	REPORT_CANCELED = 0x02,	// Part or all of order canceled
	REPORT_NOFILLED = 0x04,	// Part or all of order not filled
	REPORT_REJECTED = 0x08,	// Part or all of order was rejected
	REPORT_TIMEOUT = 0x10,	// Order timed out
	REPORT_CANCEL_SOLICITED = 0x20,	// Part or all of order canceled due to trader request
	REPORT_BUSTED = 0x40,	// Execution busted
	REPORT_FOREIGN = 0x80,	// Execution foreign
	REPORT_REJECTED_NO_OATS = 0x100,
};

#ifdef ORDER_STRUCTURE_MEMBER
class TMsgOrderReport : public TMessageTime
#else
class TMsgOrderReport : public TMessageOrderHeader
#endif
{
public:
	TMsgOrderReport(const DWORD& clientOrdID = 0,
		const TraderIdType& traderId = 0,
//		const char* const& traderId = "",
		const char* const& accountName = "",
		const char* const& firmId = "",
		const char* const& symbol = "",
		const unsigned char& side = 0,
		const unsigned int& quantity = 0,
		const DWORD& ip = 0,

		const WORD& reportType = 0,

		const unsigned char& liquidityFlag = 0,			// 0 or 1 
		const unsigned char& billableFlag = 0,			// 0 or 1 

		const DWORD& fillQuantity = 0,			// # of shares filled
//		const DWORD& nofillQuantity = 0,			// # of shares not filled
		const DWORD& liquidity = 0,
		const DWORD& cancelQuantity = 0,			// # of shares cancelled
		const DWORD& remainingQuantity = 0,		// # of shares remaining in order
								
		const unsigned int& fillPriceDollar = 0,				// Filled price	
		const unsigned int& fillPriceFraction = 0,				// Filled price	
		const char* const& mmid = "",	// Market maker ID string - 5 bytes
		const char* const& executionReferenceID = "",	// ID assigned to execution by venue
		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_MARKET,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0,
		const ULONGLONG& route = 0):
#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, TS_ORDER_REPORT, sizeof(TMsgOrderReport)),
		m_header(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip),
#else
		TMessageOrderHeader(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip,
			TS_ORDER_REPORT, sizeof(TMsgOrderReport),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID ,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType),
#endif
		ReportType(reportType),

		LiquidityFlag(liquidityFlag),			// 0 or 1 
		BillableFlag(billableFlag),			// 0 or 1 

		FillQuantity(fillQuantity),			// # of shares filled
		Liquidity(liquidity),//NofillQuantity(nofillQuantity),			// # of shares not filled
		CancelQuantity(cancelQuantity),			// # of shares cancelled
		m_orderRemainingQuantity(remainingQuantity),		// # of shares remaining in order
								
		FillPriceDollar(fillPriceDollar),				// Filled price
		FillPriceFraction(fillPriceFraction),				// Filled price
		Route(route)
	{
		U_CopyAndPad(MMID, sizeof(MMID), mmid, '\0', true);
		U_CopyAndPad(ExecutionReferenceID, sizeof(ExecutionReferenceID), executionReferenceID, '\0');
		*ReasonText = '\0';
	}
#ifdef ORDER_STRUCTURE_MEMBER
	TMessageOrderHeader m_header;
#endif
	WORD					ReportType;

	UCHAR					LiquidityFlag;			// 0 or 1 
	UCHAR					BillableFlag;			// 0 or 1 

	DWORD					FillQuantity;			// # of shares filled
	DWORD					Liquidity;// NofillQuantity;			// # of shares not filled
	DWORD					CancelQuantity;			// # of shares cancelled
	DWORD					m_orderRemainingQuantity;		// # of shares remaining in order
								
	unsigned int			FillPriceDollar;				// Filled price	
	unsigned int			FillPriceFraction;				// Filled price	
	char					MMID[MAX_MMID_SIZE];	// Market maker ID string - 5 bytes
	char					ExecutionReferenceID[MAX_MARKET_REFERENCE_ID];	// ID assigned to execution by venue
//	DWORD					Route;
	ULONGLONG				Route;
	char					ReasonText[1];			// Reason msg string for rejections
};

#ifdef ORDER_STRUCTURE_MEMBER
class TMsgReqOrderCancel : public TMessageTime
#else
class TMsgReqOrderCancel : public TMessageOrderHeader
#endif
{
public:
	TMsgReqOrderCancel(const DWORD& clientOrdID = 0,
		const TraderIdType& traderId = 0,
//		const char* const& traderId = "",
		const char* const& accountName = "",
		const char* const& firmId = "",
		const char* const& symbol = "",
		const unsigned char& side = 0,
		const unsigned int& quantity = 0,
		const DWORD& ip = 0,
		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_MARKET,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0
		):
#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, TS_ORDER_CANCEL_REQ, sizeof(TMsgReqOrderCancel)),
		m_header(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip)
#else
		TMessageOrderHeader(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip,
			TS_ORDER_CANCEL_REQ, sizeof(TMsgReqOrderCancel),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
#endif
	{
	}
#ifdef ORDER_STRUCTURE_MEMBER
	TMessageOrderHeader m_header;
#endif
};

//TSClient->TS, Sent to replace an order
#ifdef ORDER_STRUCTURE_MEMBER
class TMsgReqOrderReplace : public TMessageTime
#else
class TMsgReqOrderReplace : public TMessageOrderHeader
#endif
{
public:
	TMsgReqOrderReplace(const DWORD& clientOrdID = 0,
		const TraderIdType& traderId = 0,
//		const char* const& traderId = "",
		const char* const& accountName = "",
		const char* const& firmId = "",
		const char* const& symbol = "",
		const unsigned char& side = 0,
		const unsigned int& oldQuantity = 0,
		const DWORD& newClOrdID = 0,
		const unsigned int& newQuantity = 0,
		const DWORD& ip = 0,

		const unsigned char& orderType = ORDER_TYPE_MARKET,

		const unsigned int& limitPriceDollar = 0,						// Limit price
		const unsigned int& limitPriceFraction = 0,					// Limit price

		const int& stopPriceDollar = 0,						// Stop price
		const int& stopPriceFraction = 0,						// Stop price

		const unsigned int& auxPriceDollar = 0,						// For discretionary and scaled orders
		const unsigned int& auxPriceFraction = 0,						// For discretionary and scaled orders

		const unsigned int& lastPriceDollar = 0,						// Last bid/ask price 
		const unsigned int& lastPriceFraction = 0,						// Last bid/ask price

		const unsigned int& bidPriceDollar = 0,						// Latest bid price
		const unsigned int& bidPriceFraction = 0,						// Latest bid price

		const unsigned int& askPriceDollar = 0,						// Latest ask price
		const unsigned int& askPriceFraction = 0,						// Latest ask price

		const unsigned char& tifType = TIF_DAY,

		const unsigned int& minQuantity = 0,
		const unsigned int& displayQuantity = 0,				// Reserve order display quantity

//		const DWORD& date = 0,
		const unsigned short& ticketID = 0,
		const unsigned char& ticketCount = 0,

		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_MARKET,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0
		):
#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, TS_ORDER_REPLACE_REQ, sizeof(TMsgReqOrderReplace)),
		m_header(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			oldQuantity,
			ip)
#else
		TMessageOrderHeader(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			oldQuantity,
			ip,
			TS_ORDER_REPLACE_REQ, sizeof(TMsgReqOrderReplace),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType),
		NewClOrdID(newClOrdID),
//		Date(date),
		TicketCount(ticketCount),
		Reserved(0),
		TicketID(ticketID),
		m_newType(orderType),
		m_newTIF(tifType),
		m_newQuantity(newQuantity),
		m_newMinQuantity(minQuantity),
		m_newDisplayQuantity(displayQuantity),
		m_newLimitPriceDollar(limitPriceDollar),
		m_newLimitPriceFraction(limitPriceFraction),
		m_newStopPriceDollar(stopPriceDollar),
		m_newStopPriceFraction(stopPriceFraction),
		m_newAuxPriceDollar(auxPriceDollar),
		m_newAuxPriceFraction(auxPriceFraction),
		LastPriceDollar(lastPriceDollar),
		LastPriceFraction(lastPriceFraction),
		BidPriceDollar(bidPriceDollar),
		BidPriceFraction(bidPriceFraction),
		AskPriceDollar(askPriceDollar),
		AskPriceFraction(askPriceFraction)
#endif
	{
	}
#ifdef ORDER_STRUCTURE_MEMBER
	TMessageOrderHeader m_header;
#endif
	DWORD NewClOrdID;

//	DWORD Date;							// Date for good till date orders
	unsigned short TicketID;
	unsigned char Reserved;
	unsigned char TicketCount;

	UCHAR m_newType;							// Order type, market, limit, etc
	UCHAR m_newTIF;							// TIF or Order duration 

	DWORD m_newQuantity;						// Order quantity
	ULONG m_newMinQuantity;					// Minimum quantity to process order
															// if equals quantity, then all or nothing
	ULONG m_newDisplayQuantity;				// Reserve order display quantity

	unsigned int m_newLimitPriceDollar;						// Limit price
	unsigned int m_newLimitPriceFraction;						// Limit price

	int m_newStopPriceDollar;						// Stop price 
	int m_newStopPriceFraction;						// Stop price 

	unsigned int m_newAuxPriceDollar;						// For discretionary and scaled orders
	unsigned int m_newAuxPriceFraction;						// For discretionary and scaled orders

	unsigned int LastPriceDollar;						// Last bid/ask price 
	unsigned int LastPriceFraction;						// Last bid/ask price

	unsigned int BidPriceDollar;						// Latest bid price
	unsigned int BidPriceFraction;						// Latest bid price

	unsigned int AskPriceDollar;						// Latest ask price
	unsigned int AskPriceFraction;						// Latest ask price
};

#ifdef ORDER_STRUCTURE_MEMBER
class TMsgOrderCancelAck : public TMessageTime
#else
class TMsgOrderCancelAck : public TMessageOrderHeader
#endif
{
public:
	TMsgOrderCancelAck(const DWORD& clientOrdID = 0,
		const TraderIdType& traderId = 0,
//		const char* const& traderId = "",
		const char* const& accountName = "",
		const char* const& firmId = "",
		const char* const& symbol = "",
		const unsigned char& side = 0,
		const unsigned int& quantity = 0,
		const DWORD& ip = 0,
		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_MARKET,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0
		):
#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, TS_ORDER_CANCEL_ACK, sizeof(TMsgOrderCancelAck)),
		m_header(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip)
#else
		TMessageOrderHeader(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip,
			TS_ORDER_CANCEL_ACK, sizeof(TMsgOrderCancelAck),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
#endif
	{
	}
#ifdef ORDER_STRUCTURE_MEMBER
	TMessageOrderHeader m_header;
#endif
};

class TMsgOrderKill : public TMsgOrderReason
{
public:
	TMsgOrderKill(const DWORD& clientOrdID = 0,
		const TraderIdType& traderId = 0,
//		const char* const& traderId = "",
		const char* const& accountName = "",
		const char* const& firmId = "",
		const char* const& symbol = "",
		const unsigned char& side = 0,
		const unsigned int& quantity = 0,
		const DWORD& ip = 0,

		const WORD& rejectCode = 0,

		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_MARKET,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0
		):
		TMsgOrderReason(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip,
			rejectCode,
			TS_ORDER_KILL, sizeof(TMsgOrderKill),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
	{
	}
};

#ifdef ORDER_STRUCTURE_MEMBER
class TMsgOrderReplace : public TMessageTime
#else
class TMsgOrderReplace : public TMessageOrderHeader
#endif
{
public:
#ifdef ORDER_STRUCTURE_MEMBER
	TMessageOrderHeader m_header;
#endif
	DWORD NewClOrdID;
protected:
	TMsgOrderReplace(const DWORD& clientOrdID,
		const TraderIdType& traderId,
//		const char* const& traderId,
		const char* const& accountName,
		const char* const& firmId,
		const char* const& symbol,
		const unsigned char& side,
		const unsigned int& quantity,
		const DWORD& ip,

		const DWORD& newClOrdID,

		const unsigned short& type,
		const unsigned short& length,

		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_MARKET,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0
		):
#ifdef ORDER_STRUCTURE_MEMBER
		TMessageTime(0, type, length),
		m_header(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip),
#else
		TMessageOrderHeader(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip,
			type, length,
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType),
#endif
		NewClOrdID(newClOrdID)
	{
	}
};

class TMsgOrderReplaceAck : public TMsgOrderReplace
{
public:
	TMsgOrderReplaceAck(const DWORD& clientOrdID = 0,
		const TraderIdType& traderId = 0,
//		const char* const& traderId = "",
		const char* const& accountName = "",
		const char* const& firmId = "",
		const char* const& symbol = "",
		const unsigned char& side = 0,
		const unsigned int& quantity = 0,
		const DWORD& ip = 0,

		const DWORD& newClOrdID = 0,

		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_MARKET,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0
		):
		TMsgOrderReplace(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			ip,
			newClOrdID,
			TS_ORDER_REPLACE_ACK, sizeof(TMsgOrderReplaceAck),
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType)
	{
	}
};

class TMsgOrderReplaceDone : public TMessageOrderBase//TMsgOrderReplace
{
public:
	TMsgOrderReplaceDone(const DWORD& clientOrdID = 0,
		const TraderIdType& traderId = 0,
//		const char* const& traderId = "",
		const char* const& accountName = "",
		const char* const& firmId = "",
		const char* const& symbol = "",
		const unsigned char& side = 0,
		const unsigned int& quantity = 0,

//		const DWORD& route = 0,
		const ULONGLONG& route = 0,

		const DWORD& ip = 0,

//		DWORD newClOrdID,
////
		const unsigned char& orderType = ORDER_TYPE_MARKET,
		const unsigned int& limitPriceDollar = 0,						// Limit price
		const unsigned int& limitPriceFraction = 0,					// Limit price

		const unsigned char& tifType = TIF_DAY,

		const unsigned int& expireTime = 0,						// Number of milliseconds before order should expire (for TIF = '6')
		const unsigned int& effectiveTime = 0,					// When order should become active
//?
		const char& capacity = 0,						// Agency, principal, etc.

		const char* const& mm = "",	// Market maker ID string, don't know whether we need it...

		const int& stopPriceDollar = 0,						// Stop price 
		const int& stopPriceFraction = 0,						// Stop price 

		const unsigned int& minQuantity = 0,
		const unsigned int& displayQuantity = 0,				// Reserve order display quantity
		const unsigned char& quantityType = 0,					// Quantity type that generated the above qty
		const unsigned int& reserveQuantity = 0,				// Reserve size
		const unsigned int& refreshQuantity = 0,				// Refresh size
		const unsigned int& discretionQuantity = 0,				// Discretion size

		const unsigned char& priceType = 0,						// Price type that generated the above price

		const unsigned int& displayPriceDollar = 0,					// Also can be used for discretionary orders
		const unsigned int& displayPriceFraction = 0,					// Also can be used for discretionary orders

		const unsigned int& lastPriceDollar = 0,						// Last bid/ask price 
		const unsigned int& lastPriceFraction = 0,						// Last bid/ask price

		const unsigned int& bidPriceDollar = 0,						// Latest bid price
		const unsigned int& bidPriceFraction = 0,						// Latest bid price

		const unsigned int& askPriceDollar = 0,						// Latest ask price
		const unsigned int& askPriceFraction = 0,						// Latest ask price

		const unsigned int& auxPriceDollar = 0,						// For discretionary and scaled orders
		const unsigned int& auxPriceFraction = 0,						// For discretionary and scaled orders

//		const unsigned int& date = 0,
		const DWORD& defaultRoutesHigh = NULL_ROUTE,					// Single ROUTE to default to for execution.

//		const DWORD& excludeRoutes = NULL_ROUTE,					// Routes to exclude when executing order.
//		const DWORD& defaultRoutes = NULL_ROUTE,					// Single ROUTE to default to for execution.
		const DWORD& defaultRoutesLow = NULL_ROUTE,					// Single ROUTE to default to for execution.

		const unsigned char& ticketCount = 0,					// Number of orders that is part of the
												// same ticket counted down.
		const unsigned short& ticketID = 0,						// Ticket ID assigned by client.

		const DWORD& subType = 0,						// Additional Flags for Order, like type of peg...
		const DWORD& execInst = 0,						// Execution Instructions
		const DWORD& routingInstructions = 0,			// Routing Instructions to direct venue whether to route order out and where
////
		const DWORD& messageSequenceNumber = 0,
		const DWORD& serverOrdID = 0,
		const DWORD& parentClOrdID = 0,
		const DWORD& acceptedTime = 0,
		const DWORD& canceledTime = 0,
		const char* const& marketReferenceID = "",
		const unsigned char& tracking = TR_ON_MARKET,
		const unsigned char& status = OS_NEW,
		const unsigned __int64& optionBlock = 0,
		const unsigned int& remainingQuantity = 0,
		const unsigned int& canceledQuantity = 0,
		const unsigned char& realTimeOrRecovered = 0,
		const unsigned char& instrumentType = 0,

		const DWORD& oldClOrdID = 0,
		const TraderIdType& oldTraderId = 0,
//		const char* const& oldTraderId = "",
		const char* const& oldAccountName = "",
		const char* const& oldFirmId = "",
		const char* const& oldSymbol = "",
		const unsigned char& oldSide = 0,
		const unsigned int& oldQuantity = 0,
		const DWORD& oldIp = 0,

		const DWORD& oldMessageSequenceNumber = 0,
		const DWORD& oldServerOrdID = 0,
		const DWORD& oldParentClOrdID = 0,
		const DWORD& oldAcceptedTime = 0,
		const DWORD& oldCanceledTime = 0,
		const char* const& oldMarketReferenceId = "",
		const unsigned char& oldTracking = TR_ON_MARKET,
		const unsigned char& oldStatus = OS_NEW,
		const unsigned __int64& oldOptionBlock = 0,
		const unsigned int& oldRemainingQuantity = 0,
		const unsigned int& oldCanceledQuantity = 0,
		const unsigned char& oldRealTimeOrRecovered = 0,
		const unsigned char& oldInstrumentType = 0
		):
		TMessageOrderBase(clientOrdID,
			traderId,
			accountName,
			firmId,
			symbol,
			side,
			quantity,
			route,
			ip,
//			newClOrdID,
			TS_ORDER_REPLACED, sizeof(TMsgOrderReplaceDone),
////
			orderType,
			limitPriceDollar,
			limitPriceFraction,

			tifType,
			expireTime,
			effectiveTime,
			capacity,
			mm,
			stopPriceDollar,
			stopPriceFraction,

			minQuantity,
			displayQuantity,
			quantityType,
			reserveQuantity,
			refreshQuantity,
			discretionQuantity,

			priceType,

			displayPriceDollar,
			displayPriceFraction,

			lastPriceDollar,
			lastPriceFraction,

			bidPriceDollar,
			bidPriceFraction,

			askPriceDollar,
			askPriceFraction,

			auxPriceDollar,
			auxPriceFraction,

//			date,
			defaultRoutesHigh,

//			excludeRoutes,
//			defaultRoutes,
			defaultRoutesLow,

			ticketCount,
			ticketID,

			subType,
			execInst,
			routingInstructions,
////
			messageSequenceNumber,
			serverOrdID,
			parentClOrdID,
			acceptedTime,
			canceledTime,
			marketReferenceID,
			tracking,
			status,
			optionBlock,//confirmationID,
			remainingQuantity,
			canceledQuantity,
			realTimeOrRecovered,
			instrumentType),
		m_oldMessageSequenceNumber(oldMessageSequenceNumber),
		m_oldClOrdID(oldClOrdID),							//Client assigned order id, I think it is ok to have this as a number instead of string for faster search
		m_oldParentClOrdID(oldParentClOrdID),
		m_oldSrOrdID(oldServerOrdID),						// Server assigned order id, server will use a number as well
		m_oldAcceptedTime(oldAcceptedTime),						// When order was accepted by market
		m_oldCanceledTime(oldCanceledTime),						// When order has been canceled if any
		m_oldTracking(oldTracking),							// Where order is, on server, on market, etc.,
		m_oldStatus(oldStatus),								// New, Partially filled, Canceled, Filled
		m_oldQuantity(oldQuantity),							// Order quantity ( moved from order )
		m_oldRemainingQuantity(oldRemainingQuantity),					// Remaining size of the order ( moved from order )
		m_oldCanceledQuantity(oldCanceledQuantity),					// Canceled size of the order
		m_oldRealTimeOrRecovered(oldRealTimeOrRecovered),				//Weather this a current message or recovered message
		m_oldTime(oldInstrumentType),								//Milliseconds since midnight, when this message is generated
		m_oldIp(oldIp ? oldIp : ip),									//For Compliance

		m_oldSide(oldSide ? oldSide : side),
		m_oldInstrumentType(oldInstrumentType)
	{
		U_CopyAndPad(m_oldAccountName, sizeof(m_oldAccountName), *oldAccountName ? oldAccountName : accountName, '\0', true);

//		U_CopyAndPad(m_oldTraderID, sizeof(m_oldTraderID), *oldTraderId ? oldTraderId : traderId, '\0', true);
		*(TraderIdType*)m_oldTraderID = oldTraderId ? oldTraderId : traderId;
		m_oldTraderID[sizeof(m_oldTraderID) - 1] = '\0';

		U_CopyAndPad(m_oldFirmID, sizeof(m_oldFirmID), *oldFirmId ? oldFirmId : firmId, '\0', true);
		U_CopyAndPad(m_oldMarketReferenceID, sizeof(m_oldMarketReferenceID), *oldMarketReferenceId ? oldMarketReferenceId : marketReferenceID, '\0');
		*(unsigned __int64*)m_oldConfirmationID = oldOptionBlock ? oldOptionBlock : optionBlock;
		*((unsigned __int64*)m_oldConfirmationID + 1) = 0;
		U_CopyAndPad(m_oldSymbol, sizeof(m_oldSymbol), *oldSymbol ? oldSymbol : symbol, '\0');
	}
	DWORD		m_oldMessageSequenceNumber;
	DWORD		m_oldClOrdID;							//Client assigned order id, I think it is ok to have this as a number instead of string for faster search
	DWORD		m_oldParentClOrdID;
	DWORD		m_oldSrOrdID;							// Server assigned order id, server will use a number as well
	char		m_oldAccountName[MAX_ACCOUNT_SIZE];		//Order Account Name

// *AK* start
	char		m_oldTraderID[MAX_TRADER_ID_SIZE];
	char		m_oldFirmID[MAX_FIRM_ID_SIZE];
	DWORD		m_oldAcceptedTime;						// When order was accepted by market
	DWORD		m_oldCanceledTime;						// When order has been canceled if any
	char		m_oldMarketReferenceID[MAX_MARKET_REFERENCE_ID];		// Will be filled with Venue's OrderID
	UCHAR		m_oldTracking;							// Where order is, on server, on market, etc.
	UCHAR		m_oldStatus;								// New, Partially filled, Canceled, Filled
	char		m_oldConfirmationID[16];					// can be used for short sells. ID from liquidity finder
	ULONG		m_oldQuantity;							// Order quantity ( moved from order )
	ULONG		m_oldRemainingQuantity;					// Remaining size of the order ( moved from order )
	ULONG		m_oldCanceledQuantity;					// Canceled size of the order
// *AK* end

	char		m_oldSymbol[MAX_SYMBOL_SIZE];
	UCHAR		m_oldRealTimeOrRecovered;				//Weather this a current message or recovered message
	DWORD		m_oldTime;								//Milliseconds since midnight, when this message is generated
	DWORD		m_oldIp;									//For Compliance

	UCHAR		m_oldSide;
	UCHAR		m_oldInstrumentType;
};

#ifdef FIRM_VALUES

class TMsgFirmPosition : public TMessageTime//Message
{
public:
	char m_clearingAccountName[MAX_ACCOUNT_SIZE];
	char m_symbol[MAX_SYMBOL_SIZE];
	char m_firmId[MAX_FIRM_ID_SIZE];
protected:
//	TMsgFirmPosition(const char* clearingAccountName, const char* symbol, const char* firmId, unsigned short type, unsigned short length):Message(type, length)
	TMsgFirmPosition(const char* const& clearingAccountName,
		const char* const& symbol,
		const char* const& firmId,
		const unsigned int& timestamp,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTime(timestamp, type, length)
	{
		U_CopyAndPad(m_clearingAccountName, sizeof(m_clearingAccountName), clearingAccountName, '\0', true);
		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
		U_CopyAndPad(m_firmId, sizeof(m_firmId), firmId, '\0', true);
	}
//	TMsgFirmPosition(const unsigned __int64& clearingNamePart1, const unsigned __int64& clearingNamePart2, const unsigned __int64& symbol, const unsigned int& firmId, unsigned short type, unsigned short length):Message(type, length)
	TMsgFirmPosition(const unsigned __int64& clearingNamePart1,
		const unsigned __int64& clearingNamePart2,
		const unsigned __int64& symbol,
		const unsigned int& firmId,
		const unsigned int& timestamp,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTime(timestamp, type, length)
	{
		*(unsigned __int64*)m_clearingAccountName = clearingNamePart1;
		*(unsigned __int64*)(m_clearingAccountName + sizeof(unsigned __int64)) = clearingNamePart2;
		*(unsigned __int64*)m_symbol = symbol;
		*(unsigned int*)m_firmId = firmId;
		m_firmId[sizeof(unsigned int)] = '\0';
	}
};

class TMsgUpdateFirmPosition : public TMsgFirmPosition
{
public:
	TMsgUpdateFirmPosition(const char* const& clearingAccountName,
		const char* const& symbol = "",
		const char* const& firmId = "",
		const int& firmPosition = 0,
		const unsigned int& firmPendingSellSharesPassive = 0,
		const unsigned int& firmPendingSellSharesNonPassive = 0,
		const unsigned int& firmPendingShortSharesPassive = 0,
		const unsigned int& firmPendingShortSharesNonPassive = 0,
		const double& aggregatedAvgPriceMargin = 0,
		const unsigned int& availableBorrowedShares = 0,
		const unsigned int& timestamp = 0):

		TMsgFirmPosition(clearingAccountName,
			symbol,
			firmId,
			timestamp,
			TS_FIRM_POSITION_UPDATE,
			sizeof(TMsgUpdateFirmPosition)),
		m_firmPosition(firmPosition),
		m_firmPendingSellSharesPassive(firmPendingSellSharesPassive),
		m_firmPendingSellSharesNonPassive(firmPendingSellSharesNonPassive),
		m_firmPendingShortSharesPassive(firmPendingShortSharesPassive),
		m_firmPendingShortSharesNonPassive(firmPendingShortSharesNonPassive),
		m_aggregatedAvgPriceMargin(aggregatedAvgPriceMargin),
		m_availableBorrowedShares(availableBorrowedShares)
	{
	}
	TMsgUpdateFirmPosition(const unsigned __int64& clearingNamePart1 = 0,
		const unsigned __int64& clearingNamePart2 = 0,
		const unsigned __int64& symbol = 0,
		const unsigned int& firmId = 0,
		const int& firmPosition = 0,
		const unsigned int& firmPendingSellSharesPassive = 0,
		const unsigned int& firmPendingSellSharesNonPassive = 0,
		const unsigned int& firmPendingShortSharesPassive = 0,
		const unsigned int& firmPendingShortSharesNonPassive = 0,
		const double& aggregatedAvgPriceMargin = 0,
		const unsigned int& availableBorrowedShares = 0,
		const unsigned int& timestamp = 0):

		TMsgFirmPosition(clearingNamePart1,
			clearingNamePart2,
			symbol,
			firmId,
			timestamp,
			TS_FIRM_POSITION_UPDATE,
			sizeof(TMsgUpdateFirmPosition)),
		m_firmPosition(firmPosition),
		m_firmPendingSellSharesPassive(firmPendingSellSharesPassive),
		m_firmPendingSellSharesNonPassive(firmPendingSellSharesNonPassive),
		m_firmPendingShortSharesPassive(firmPendingShortSharesPassive),
		m_firmPendingShortSharesNonPassive(firmPendingShortSharesNonPassive),
		m_aggregatedAvgPriceMargin(aggregatedAvgPriceMargin),
		m_availableBorrowedShares(availableBorrowedShares)
	{
	}
	int m_firmPosition;
	unsigned int m_firmPendingSellSharesPassive;
	unsigned int m_firmPendingSellSharesNonPassive;
	unsigned int m_firmPendingShortSharesPassive;
	unsigned int m_firmPendingShortSharesNonPassive;
//07/02/2019
	double m_aggregatedAvgPriceMargin;
//03/04/2020
	unsigned int m_availableBorrowedShares;
};

class TMsgFirmEnforcement : public TMessageTime
{
public:
	TMsgFirmEnforcement(const char* const& clearingAccountName,
		const bool& enforceFirm = false,
		const bool& conservativeOrderMarking = false,
		const bool& localSideMarking = false,
		const DWORD& niteBetaEnforcementStartTime = 0,//In Milliseconds since midnight
		const double& niteBetaGroupBuyingPower = 0,
		const double& marginExcessMultiplier = 0,
		const double& marginExcess = 0,
		const double& totalEquity = 0,
		const unsigned int& timestamp = 0):
		TMessageTime(timestamp, TS_FIRM_ENFORCEMENT, sizeof(TMsgFirmEnforcement)),
		m_enforceFirm(enforceFirm),
		m_conservativeOrderMarking(conservativeOrderMarking),
		m_localSideMarking(localSideMarking),
		m_niteBetaEnforcementStartTime(niteBetaEnforcementStartTime),
		m_niteBetaGroupBuyingPower(niteBetaGroupBuyingPower),
		m_marginExcessMultiplier(marginExcessMultiplier),
		m_marginExcess(marginExcess),
		m_totalEquity(totalEquity)
	{
		U_CopyAndPad(m_clearingAccountName, sizeof(m_clearingAccountName), clearingAccountName, '\0', true);
	}
	TMsgFirmEnforcement(const unsigned __int64& clearingNamePart1 = 0,
		const unsigned __int64& clearingNamePart2 = 0,
		const bool& enforceFirm = false,
		const bool& conservativeOrderMarking = false,
		const bool& localSideMarking = false,
		const DWORD& niteBetaEnforcementStartTime = 0,//In Milliseconds since midnight
		const double& niteBetaGroupBuyingPower = 0,
		const double& marginExcessMultiplier = 0,
		const double& marginExcess = 0,
		const double& totalEquity = 0,
		const unsigned int& timestamp = 0):
		TMessageTime(timestamp, TS_FIRM_ENFORCEMENT, sizeof(TMsgFirmEnforcement)),
		m_enforceFirm(enforceFirm),
		m_conservativeOrderMarking(conservativeOrderMarking),
		m_localSideMarking(localSideMarking),
		m_niteBetaEnforcementStartTime(niteBetaEnforcementStartTime),
		m_niteBetaGroupBuyingPower(niteBetaGroupBuyingPower),
		m_marginExcessMultiplier(marginExcessMultiplier),
		m_marginExcess(marginExcess),
		m_totalEquity(totalEquity)
	{
		*(unsigned __int64*)m_clearingAccountName = clearingNamePart1;
		*(unsigned __int64*)(m_clearingAccountName + sizeof(unsigned __int64)) = clearingNamePart2;
	}
	char m_clearingAccountName[MAX_ACCOUNT_SIZE];
	bool m_enforceFirm;
	bool m_conservativeOrderMarking;
	bool m_localSideMarking;
	DWORD m_niteBetaEnforcementStartTime;//In Milliseconds since midnight
	double m_niteBetaGroupBuyingPower;
//07/02/2019
	double m_marginExcessMultiplier;
	double m_marginExcess;
	double m_totalEquity;
};
#endif

class HtbNode
{
public:
	HtbNode(const unsigned __int64& symbol = 0,
		const unsigned int& priceToBorrowDollar = 0,
		const unsigned int& priceToBorrowFraction = 0,
		const unsigned int& quantity = 0,
		const unsigned char& discountFlag = 0,
		const unsigned char& htbType = 0):
		m_priceToBorrowDollar(priceToBorrowDollar),
		m_priceToBorrowFraction(priceToBorrowFraction),
		m_quantity(quantity),
		m_discountFlag(discountFlag),
		m_htbType(htbType)
	{
		*(unsigned __int64*)m_symbol = symbol;
	}
	Symbol m_symbol;
	unsigned int m_priceToBorrowDollar;
	unsigned int m_priceToBorrowFraction;
	unsigned int m_quantity;
	unsigned char m_discountFlag;
//02/19/2014
	unsigned char m_htbType;
};

class TMsgRespHtbSymbolList : public TMessageTime
{
public:
	TMsgRespHtbSymbolList(const unsigned int& firmId = 0,
		const unsigned int& requestId = 0,
		const unsigned short& nodeSize = sizeof(HtbNode),
		const unsigned short& nodes = 1,
		const bool& done = true):
		TMessageTime(0, M_TR_HTB_RESP_SYMBOL_LIST, sizeof(TMsgRespHtbSymbolList) + nodeSize * nodes),
		m_firmId(firmId),
		m_requestId(requestId),
		m_nodeSize(nodeSize),
		m_nodes(nodes),
		m_done(done)
	{
	}

	unsigned int m_firmId;
	unsigned int m_requestId;
	unsigned short m_nodeSize;
	unsigned short m_nodes;
	bool m_done;
	// Followed by m_nodes of CHTBNode points
};


class TMsgReqList : public TMessageTime
{
public:
	unsigned int m_firmId;
	unsigned int m_requestId;
protected:
	TMsgReqList(const unsigned int& firmId,
		const unsigned int& requestId,
		const unsigned int& time,
		const unsigned short& type,
		const unsigned short& length):
		TMessageTime(time, type, length),
		m_firmId(firmId),
		m_requestId(requestId)
	{
	}
};

class TMsgRespList : public TMsgReqList
{
public:
//	unsigned int m_firmId;
//	unsigned int m_requestId;
	unsigned short m_nodeSize;
	unsigned short m_nodes;
//	bool m_done;
	// Followed by m_nodes of EtbNode points
protected:
	TMsgRespList(const unsigned int& firmId,
		const unsigned int& requestId,
		const unsigned int& time,
		const unsigned short& nodeSize,
		const unsigned short& nodes,
		const unsigned short& type,
		const unsigned short& length):
		TMsgReqList(firmId, requestId, time, type, length + nodeSize * nodes),
//		m_firmId(firmId),
//		m_requestId(requestId),
		m_nodeSize(nodeSize),
		m_nodes(nodes)
	{
	}
};

class TMsgRespListWithDone : public TMsgRespList
{
public:
	bool m_done;
	// Followed by m_nodes of EtbNode points
protected:
	TMsgRespListWithDone(const unsigned int& firmId,
		const unsigned int& requestId,
		const unsigned int& time,
		const unsigned short& nodeSize,
		const unsigned short& nodes,
		const bool& done,
		const unsigned short& type,
		const unsigned short& length):
		TMsgRespList(firmId, requestId, time, nodeSize, nodes, type, length),
		m_done(done)
	{
	}
};

class TMsgReqHtbSymbolList : public TMsgReqList
{
public:
	TMsgReqHtbSymbolList(const unsigned int& firmId = 0,
		const unsigned int& requestId = 0,
		const unsigned int& time = 0):
		TMsgReqList(firmId, requestId, time, M_TR_HTB_REQ_SYMBOL_LIST, sizeof(TMsgReqHtbSymbolList))
	{
	}
};

class TMsgReqEtbSymbolList : public TMsgReqList
{
public:
	TMsgReqEtbSymbolList(const unsigned int& firmId = 0,
		const unsigned int& requestId = 0,
		const unsigned int& time = 0):
		TMsgReqList(firmId, requestId, time, M_TR_ETB_REQ_SYMBOL_LIST, sizeof(TMsgReqEtbSymbolList))
	{
	}
};

class EtbNode
{
public:
	Symbol m_symbol;
};

enum EtbSymbolListFlags : unsigned char
{
	EtbFirst	= 0x01,
	EtbReload	= 0x02,
};

class TMsgRespEtbSymbolList : public TMsgRespList
{
public:
	TMsgRespEtbSymbolList(const unsigned int& firmId = 0,
		const unsigned int& requestId = 0,
		const unsigned int& time = 0,
		const unsigned short& nodeSize = 0,
		const unsigned short& nodes = 0,
		const bool& done = false,
		const unsigned char& flags = 0):
		TMsgRespList(firmId, requestId, time, nodeSize, nodes, M_TR_ETB_RESP_SYMBOL_LIST, sizeof(TMsgRespEtbSymbolList)),
		m_done(done),
		m_flags(flags)
	{
	}
	bool m_done;
	unsigned char m_flags;
};

class TMsgReqLocateInfo : public TMsgReqList
{
public:
	TMsgReqLocateInfo(const unsigned int& firmId = 0,
		const unsigned int& requestId = 0,
		const unsigned int& time = 0):
		TMsgReqList(firmId, requestId, time, M_TR_HTB_REQ_LOCATE_INFO, sizeof(TMsgReqLocateInfo))
	{
	}
};

class BorrowNode
{
public:
	BorrowNode(const char* const& symbol = "",
		const unsigned int& priceToBorrowDollar = 0,
		const unsigned int& priceToBorrowFraction = 0,
		const unsigned int& quantity = 0,
		const unsigned char& discountFlag = 0,
		const unsigned char& htbType = 0,
		const unsigned char& margin = 0,
		const double& beta = 0,
		const unsigned char& PM_EL_Rate = 15,
		const unsigned char& PM_ES_Rate = 15,
		const unsigned char& PM_HL_Rate = 15,
		const unsigned char& PM_HS_Rate = 15,
		const unsigned char& EL_Rate = 25,
		const unsigned char& ES_Rate = 30,
		const unsigned char& HL_Rate = 30,
		const unsigned char& HS_Rate = 30,
//Obsolete
		const unsigned char& Fed_Req = 50,
		const unsigned char& Asset_Type = 'E',
		const bool& Marginable = true,
		const unsigned char& Sec_Type = 'C',
		const unsigned char& Status = 0):

		m_priceToBorrowDollar(priceToBorrowDollar),
		m_priceToBorrowFraction(priceToBorrowFraction),
		m_quantity(quantity),
		m_discountFlag(discountFlag),
		m_htbType(htbType),
		m_margin(margin),
		m_beta(beta),

		m_PM_EL_Rate(PM_EL_Rate),
		m_PM_ES_Rate(PM_ES_Rate),
		m_PM_HL_Rate(PM_HL_Rate),
		m_PM_HS_Rate(PM_HS_Rate),
		m_EL_Rate(EL_Rate),
		m_ES_Rate(ES_Rate),
		m_HL_Rate(HL_Rate),
		m_HS_Rate(HS_Rate),
//Obsolete
		m_Fed_Req(Fed_Req),
		m_Asset_Type(Asset_Type),
		m_Marginable(Marginable),
		m_Sec_Type(Sec_Type),
		m_Status(Status)
	{
		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
	}
	Symbol m_symbol;
	unsigned int m_priceToBorrowDollar;
	unsigned int m_priceToBorrowFraction;
	unsigned int m_quantity;
	unsigned char m_discountFlag;
//02/19/2014
	unsigned char m_htbType;

//10/26/2018
	unsigned char	m_margin;
	double			m_beta;
//07/02/2019
	unsigned char m_PM_EL_Rate;
	unsigned char m_PM_ES_Rate;
	unsigned char m_PM_HL_Rate;
	unsigned char m_PM_HS_Rate;
	unsigned char m_EL_Rate;
	unsigned char m_ES_Rate;
	unsigned char m_HL_Rate;
	unsigned char m_HS_Rate;
//Obsolete
	unsigned char m_Fed_Req;
	unsigned char m_Asset_Type;
	bool m_Marginable;
	unsigned char m_Sec_Type;
	unsigned char m_Status;
};

class TMsgRespLocateInfo : public TMsgRespListWithDone
{
public:
	TMsgRespLocateInfo(const unsigned int& firmId = 0,
		const unsigned int& requestId = 0,
		const unsigned int& time = 0,
		const unsigned short& nodeSize = 0,
		const unsigned short& nodes = 0,
		const bool& done = false):
		TMsgRespListWithDone(firmId, requestId, time, nodeSize, nodes, done, M_TR_HTB_RESP_LOCATE_INFO, sizeof(TMsgRespLocateInfo))
	{
	}
};

class TMsgBetaInfo : public TMessageTimeSymbol
{
public:
	TMsgBetaInfo(const unsigned __int64& symbol = 0,
		const unsigned int& time = 0,
//		const char* const& firmId = "",
		const unsigned int& firmId = 0,
		const unsigned char& margin = 0,
		const double& beta = 0,
		const unsigned char& PM_EL_Rate = 15,
		const unsigned char& PM_ES_Rate = 15,
		const unsigned char& PM_HL_Rate = 15,
		const unsigned char& PM_HS_Rate = 15,
		const unsigned char& EL_Rate = 25,
		const unsigned char& ES_Rate = 30,
		const unsigned char& HL_Rate = 30,
		const unsigned char& HS_Rate = 30,
//Obsolete
		const unsigned char& Fed_Req = 50,
		const unsigned char& Asset_Type = 'E',
		const bool& Marginable = true,
		const unsigned char& Sec_Type = 'C',
		const unsigned char& Status = 0):
		TMessageTimeSymbol(symbol, time, M_TR_BETA_INFO, sizeof(TMsgBetaInfo)),

		m_beta(beta),
		m_firmId(firmId),
		m_margin(margin),
		m_PM_EL_Rate(PM_EL_Rate),
		m_PM_ES_Rate(PM_ES_Rate),
		m_PM_HL_Rate(PM_HL_Rate),
		m_PM_HS_Rate(PM_HS_Rate),
		m_EL_Rate(EL_Rate),
		m_ES_Rate(ES_Rate),
		m_HL_Rate(HL_Rate),
		m_HS_Rate(HS_Rate),
//Obsolete
		m_Fed_Req(Fed_Req),
		m_Asset_Type(Asset_Type),
		m_Marginable(Marginable),
		m_Sec_Type(Sec_Type),
		m_Status(Status)
	{
//		*(unsigned int*)m_firmId = firmId;
//		m_firmId[sizeof(unsigned int)] = '\0';
	}
	
	double m_beta;
//	char m_firmId[MAX_MMID_SIZE];
	unsigned int m_firmId;
	unsigned char m_margin;

	unsigned char m_PM_EL_Rate;
	unsigned char m_PM_ES_Rate;
	unsigned char m_PM_HL_Rate;
	unsigned char m_PM_HS_Rate;
	unsigned char m_EL_Rate;
	unsigned char m_ES_Rate;
	unsigned char m_HL_Rate;
	unsigned char m_HS_Rate;
//Obsolete
	unsigned char m_Fed_Req;
	unsigned char m_Asset_Type;
	bool m_Marginable;
	unsigned char m_Sec_Type;
	unsigned char m_Status;
};

class TMsgLocateInfo : public TMessageTimeSymbol
{
public:
	TMsgLocateInfo(const char* const& symbol = "",
		const unsigned int& priceDollar = 0,
		const unsigned int& priceFraction = 0,
		const unsigned int& size = 0,
		const unsigned int& mmid = 0,
		const unsigned char& discountFlag = 0,
		const unsigned int& firmId = 0,
		const unsigned int& time = 0):
		TMessageTimeSymbol(symbol, time, M_TR_HTB_LOCATE_INFO, sizeof(TMsgLocateInfo)),
		m_priceDollar(priceDollar),
		m_priceFraction(priceFraction),
		m_size(size),
		m_locateMPID(mmid),
		m_discountFlag(discountFlag),
		m_firmId(firmId)
	{
//		*(unsigned int*)m_locateMPID = mmid;
//		m_locateMPID[sizeof(unsigned int)] = '\0';
	}
	
	unsigned int m_priceDollar;
	unsigned int m_priceFraction;
	unsigned int m_size;
	unsigned int m_locateMPID;
//	char m_locateMPID[sizeof(unsigned int) + 1];
	unsigned char m_discountFlag;
	unsigned int m_firmId;
};

class TMsgReqRestrictedSymbolList : public TMsgReqList
{
public:
	TMsgReqRestrictedSymbolList(const char* const& accountName = "",
		const unsigned int& firmId = 0,
		const unsigned int& requestId = 0,
		const unsigned int& time = 0):
		TMsgReqList(firmId, requestId, time, M_TR_RESTR_REQ_SYMBOL_LIST, sizeof(TMsgReqRestrictedSymbolList))
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountName, '\0', true);
	}
	char m_accountId[MAX_ACCOUNT_SIZE];
};

class RestrictedNode
{
public:
	Symbol m_symbol;
	unsigned __int64 m_venues;
};

class TMsgRespRestrictedSymbolList : public TMsgRespList
{
public:
	TMsgRespRestrictedSymbolList(const char* const& accountName = "",
		const unsigned int& firmId = 0,
		const unsigned int& requestId = 0,
		const unsigned int& time = 0,
		const unsigned short& nodeSize = 0,
		const unsigned short& nodes = 0,
		const bool& done = false,
		const unsigned char& flags = 0):
		TMsgRespList(firmId, requestId, time, nodeSize, nodes, M_TR_RESTR_RESP_SYMBOL_LIST, sizeof(TMsgRespRestrictedSymbolList)),
		m_done(done),
		m_flags(flags)
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountName, '\0', true);
	}
	bool m_done;
//Flags Same as EtbSymbolListFlags
	unsigned char m_flags;
	char m_accountId[MAX_ACCOUNT_SIZE];
// Followed by m_nodes of RestrictedNode points
};


class TMsgAccountRestrictedSymbolListLoaded : public TMsgAccountObject
{
public:
	TMsgAccountRestrictedSymbolListLoaded(const char* const& accountName = ""):
		TMsgAccountObject(accountName, TM_ACCOUNT_RESTRICTED_SYMBOL_LIST_LOADED, sizeof(TMsgAccountRestrictedSymbolListLoaded))
	{
	}
};

class TMsgPositionRestricted : public TMsgAccountStockPositionObject
{
public:
	TMsgPositionRestricted(const char* const& accountName, const bool& restricted, const unsigned __int64& symbol):
		TMsgAccountStockPositionObject(accountName, symbol, TM_POSITION_RESTRICTED, sizeof(TMsgPositionRestricted)),
		m_restricted(restricted)
	{
	}
	bool m_restricted;
};

class TMsgPositionTest : public TMsgAccountStockPositionObject
{
public:
	TMsgPositionTest(const char* const& accountName, const bool& test, const unsigned __int64& symbol):
		TMsgAccountStockPositionObject(accountName, symbol, TM_POSITION_TEST, sizeof(TMsgPositionTest)),
		m_test(test)
	{
	}
	bool m_test;
};

class TMsgCommissionFeeBase : public TMsgAccountObject
{
public:
	Money m_fee;
protected:
	TMsgCommissionFeeBase(const char* const& accountName, const Money& fee, const unsigned short& type, const unsigned short& length):
		TMsgAccountObject(accountName, type, length),
		m_fee(fee)
	{
	}
};

class TMsgCommissionFee : public TMsgCommissionFeeBase
{
public:
	TMsgCommissionFee(const char* const& accountName, const Money& fee):
		TMsgCommissionFeeBase(accountName, fee, TM_DEFAULT_COMMISSION_FEE, sizeof(TMsgCommissionFee))
	{
	}
};

#ifndef TAKION_NO_OPTIONS
class TMsgFutureCommissionFee: public TMsgCommissionFeeBase
{
public:
	TMsgFutureCommissionFee(const char* const& accountName, const Money& fee):
		TMsgCommissionFeeBase(accountName, fee, TM_FUTURE_DEFAULT_COMMISSION_FEE, sizeof(TMsgFutureCommissionFee))
	{
	}
};
#endif

class TMsgUpdateAccountSimulation : public TMsgAccountObject
{
public:
	TMsgUpdateAccountSimulation(const char* const& accountName):
		TMsgAccountObject(accountName, TM_ACCOUNT_SIMULATION, sizeof(TMsgUpdateAccountSimulation))
	{
	}
};

class TMsgUpdateAccountRetailInSimulation : public TMsgAccountObject
{
public:
	TMsgUpdateAccountRetailInSimulation(const char* const& accountName, const bool& retail):
		TMsgAccountObject(accountName, TM_ACCOUNT_RETAIL_IN_SIMULATION, sizeof(TMsgUpdateAccountRetailInSimulation)),
		m_retail(retail)
	{
	}
	bool m_retail;
};

class TMsgCustomAccountConstraints : public Message
{
public:
	TMsgCustomAccountConstraints(const ConstraintCollection& constraints):Message(TM_ACCOUNT_CONSTRAINTS, sizeof(TMsgCustomAccountConstraints)), m_constraintCollection(constraints){}
	ConstraintCollection m_constraintCollection;
};

class TMsgIpChange : public Message
{
public:
	TMsgIpChange():Message(TM_IP_CHANGE, sizeof(TMsgIpChange)){}
};

enum NewsStoryFilter : unsigned char
{
	NSF_CHILD,
	NSF_HEADLINE_ONLY,
	NSF_TEMPORARY,

	NSF_Count
};

enum NewsMetaFilter : unsigned char
{
	NMF_SYMBOLS,
	NMF_CODES,

	NMF_Count
};

class NewsHeadline// : public Observable
{
public:
#if (_MSC_VER > 1600)
	typedef std::unordered_set<unsigned __int64> SymbolSet;
#else
	typedef std::hash_set<unsigned __int64> SymbolSet;
#endif

	NewsHeadline(const SymbolSet& symbolSet,
		const unsigned __int64& dateTime,
		const unsigned __int64& dateTimePublished,
		const unsigned __int64& numericSymbol,

		const unsigned int& timeArrived,
		const unsigned int& ordinal,
		const unsigned int& alertTakeNumber,
		const unsigned int& relevance,
		const unsigned int& extDisplayWireId,
		const unsigned short& subWireId,
		const unsigned short& baseWireId,
		const unsigned char& headlineType,
		const bool& update,
//		const std::string& resourceId,
		const NewsResourceAsNumberArray& resourceId,
		const std::string& text,
		const std::string& tickerSymbols,
//		const std::string& symbol,
		const std::string& valuedStoryCodes,
//		const std::string& storyCodes,
		const std::string& providerService,
		const std::string& synopsis):

		m_symbolSet(symbolSet),
		m_symbolSetEnd(m_symbolSet.end()),
		m_dateTime(dateTime),
		m_dateTimePublished(dateTimePublished),
		m_numericSymbol(numericSymbol),
		m_timeArrived(timeArrived),
		m_ordinal(ordinal),
		m_alertTakeNumber(alertTakeNumber),
		m_relevance(relevance),
		m_extDisplayWireId(extDisplayWireId),
		m_subWireId(subWireId),
		m_baseWireId(baseWireId),
		m_headlineType(headlineType),
		m_update(update),
		m_resourceId(resourceId),
		m_text(text),
		m_tickerSymbols(tickerSymbols),
		m_symbol((const char*)&m_numericSymbol),//symbol),
		m_valuedStoryCodes(valuedStoryCodes),
//		m_storyCodes(storyCodes),
		m_providerService(providerService),
		m_synopsis(synopsis)
	{
	}

#ifdef _DEBUG
	~NewsHeadline(){}
#endif
	const SymbolSet& GetSymbolSet() const{return m_symbolSet;}
	bool SymbolBelongs(const unsigned __int64& symbol) const{return m_symbolSet.find(symbol) != m_symbolSetEnd;}
	bool SymbolBelongs(const char* symbol) const{return m_symbolSet.find(U_RepresentStringAsUnsignedNumber<unsigned __int64>(symbol, sizeof(unsigned __int64) - 1)) != m_symbolSetEnd;}
	const unsigned __int64& GetDateTime() const{return m_dateTime;}
	const unsigned __int64& GetDateTimePublished() const{return m_dateTimePublished;}
	const unsigned __int64& GetNumericSymbol() const{return m_numericSymbol;}
	const unsigned int& GetTimeArrived() const{return m_timeArrived;}
	const unsigned int& GetOrdinal() const{return m_ordinal;}
	const unsigned int& GetAlertTakeNumber() const{return m_alertTakeNumber;}
	const unsigned int& GetRelevance() const{return m_relevance;}
	const unsigned int& GetExtDisplayWireId() const{return m_extDisplayWireId;}
	const unsigned short& GetSubWireId() const{return m_subWireId;}
	const unsigned short& GetBaseWireId() const{return m_baseWireId;}
	const unsigned char& GetHeadlineType() const{return m_headlineType;}
	const bool& isUpdate() const{return m_update;}
	const NewsResourceAsNumberArray& GetResourceId() const{return m_resourceId;}
	const char* GetResourceIdStr() const{return m_resourceId.GetString();}
	const std::string& GetText() const{return m_text;}
	const std::string& GetTickerSymbols() const{return m_tickerSymbols;}
	const std::string& GetSymbol() const{return m_symbol;}
//	const std::string& GetStoryCodes() const{return m_storyCodes;}
	const std::string& GetValuedStoryCodes() const{return m_valuedStoryCodes;}
	const std::string& GetProviderService() const{return m_providerService;}
	const std::string& GetSynopsis() const{return m_synopsis;}

	void SetSymbolSet(const SymbolSet& symbolSet){m_symbolSet = symbolSet;}
	void SetDateTime(const unsigned __int64& dateTime){m_dateTime = dateTime;}
	void SetDateTimePublished(const unsigned __int64& dateTimePublished){m_dateTimePublished = dateTimePublished;}
	void SetNumericSymbol(const unsigned __int64& numericSymbol){m_numericSymbol = numericSymbol; m_symbol = (const char*)&m_numericSymbol;}
	void SetAlertTakeNumber(const unsigned int& alertTakeNumber){m_alertTakeNumber = alertTakeNumber;}
	void SetRelevance(const unsigned int& relevance){m_relevance = relevance;}
	void SetExtDisplayWireId(const unsigned int& extDisplayWireId){m_extDisplayWireId = extDisplayWireId;}
	void SetSubWireId(const unsigned short& subWireId){m_subWireId = subWireId;}
	void SetBaseWireId(const unsigned short& baseWireId){m_baseWireId = baseWireId;}
	void SetHeadlineType(const unsigned char& headlineType){m_headlineType = headlineType;}
	void SetUpdate(const bool& update){m_update = update;}
//	void SetResourceId(const std::string& resourceId){m_resourceId = resourceId;}
	void SetText(const std::string& text){m_text = text;}
	void SetTickerSymbols(const std::string& tickerSymbols){m_tickerSymbols = tickerSymbols;}
//	void SetSymbol(const std::string& symbol){m_symbol = symbol;}
	void SetValuedStoryCodes(const std::string& storyCodes){m_valuedStoryCodes = storyCodes;}
//	void SetStoryCodes(const std::string& storyCodes){m_storyCodes = storyCodes;}
	void SetProviderService(const std::string& providerService){m_providerService = providerService;}
	void SetSynopsis(const std::string& synopsis){m_synopsis = synopsis;}

	const std::string& GetStoryText() const{return m_storyText;}
	bool isShowChain() const{return m_showChain;}
	bool isStoryError() const{return m_storyError;}

	void SetStoryText(const std::string& text, bool showChain, bool storyError){m_storyText = text; m_showChain = showChain; m_storyError = storyError;}

	bool LockInquiry() const{return m_lock.LockInquiry();}
	void LockInquiryWait() const{m_lock.LockInquiryWait();}
	void UnlockInquiry() const{m_lock.UnlockInquiry();}
	bool LockModification() const{return m_lock.LockModification();}
	void UnlockModification() const{m_lock.UnlockModification();}

	bool LockStoryInquiry() const{return m_lockStory.LockInquiry();}
	void LockStoryInquiryWait() const{m_lockStory.LockInquiryWait();}
	void UnlockStoryInquiry() const{m_lockStory.UnlockInquiry();}
	bool LockStoryModification() const{return m_lockStory.LockModification();}
	void UnlockStoryModification() const{m_lockStory.UnlockModification();}

	bool isTodays() const{return (m_dateTimePublished >> 32) >= TL_GetTodaysDateInShiftFormat();}
	bool isYestAfterMarket() const
	{
		const unsigned int date = (unsigned int)(m_dateTimePublished >> 32);
		if(date < TL_GetTodaysDateInShiftFormat())
		{
			const unsigned int prevDate = TL_GetPreviousBusinessDateInShiftFormat();
			if(date > prevDate)
			{
				return true;
			}
			else
			{
				const unsigned int yestTime = (unsigned int)m_dateTimePublished;
				return yestTime >= TL_GetPreviousMarketCloseTimeInShiftFormat();
			}
		}
		return false;
	}

	DECLARE_NED_NEW
protected:
	SymbolSet m_symbolSet;
	SymbolSet::const_iterator m_symbolSetEnd;
	unsigned __int64 m_dateTime;
	unsigned __int64 m_dateTimePublished;
	unsigned __int64 m_numericSymbol;
	unsigned int m_timeArrived;
	unsigned int m_ordinal;
	unsigned int m_alertTakeNumber;
	unsigned int m_relevance;
	unsigned int m_extDisplayWireId;
	unsigned short m_subWireId;
	unsigned short m_baseWireId;
	unsigned char m_headlineType;
	bool m_update;
	NewsResourceAsNumberArray m_resourceId;
//	std::string m_resourceId;
	std::string m_text;
	std::string m_tickerSymbols;
	std::string m_symbol;
	std::string m_valuedStoryCodes;
//	std::string m_storyCodes;
	std::string m_providerService;
	std::string m_synopsis;
	std::string m_storyText;
	bool m_showChain;
	bool m_storyError;
	TakionLock m_lock;
	TakionLock m_lockStory;
};

typedef std::set<unsigned __int64> WireSet;

#ifdef __cplusplus
extern "C"
{
#endif

//News API
typedef unsigned char (WINAPI* ApiNewsConnect)(const char* hostName,
	unsigned short port,
	const char* userName,
	const char* password,
	const char* appName,
	const char* appVersion,
	const char* companyName,
	const char* sessionData,
	const char* proxyIpAddress,
	unsigned short proxyPort,
	const char* proxyProtocolName,
	const char* proxyUserName,
	const char* proxyPassword,
	const char* newPassword);

typedef void (WINAPI* ApiNewsDisplayFilterDialog)(CWnd* receipient,
	unsigned int code,
	const WireSet& wireSet,
	unsigned int storyFilter,
	unsigned int metaFilter,
	unsigned int relevance,
	CWnd* parent,
	const CPoint& mousePoint);
typedef bool (WINAPI* ApiGetFilterDialogValues)(WireSet& wireSet,
	unsigned int& storyFilter,
	unsigned int& metaFilter,
	unsigned int& relevance);

typedef void (WINAPI* ApiNewsDisplayLimitsDialog)(CWnd* receipient,
	unsigned int code,
	unsigned short daysBack,
	unsigned int headlineCount,
	bool afterMarket,
	CWnd* parent,
	const CPoint& mousePoint);
typedef bool (WINAPI* ApiGetLimitsDialogValues)(unsigned short& daysBack,
	unsigned int& headlineCount,
	bool& afterMarket);
/*
typedef Observable* (WINAPI* ApiGetStockNewsByUInt64)(Observable* oldStockNews, const Observable* newsCollection, const unsigned __int64& symbol);
typedef Observable* (WINAPI* ApiGetStockNewsByCharPtr)(Observable* oldStockNews, const Observable* newsCollection, const char* symbol);
typedef Observable* (WINAPI* ApiGetStockNewsByString)(Observable* oldStockNews, const Observable* newsCollection, const FilterStringAsNumberArray& symbol, const std::hash_set<unsigned __int64>* stockSet);
*/
typedef Observable* (WINAPI* ApiGetStockNewsByUInt64)(const Observable* newsCollection, const unsigned __int64& symbol);
typedef Observable* (WINAPI* ApiGetStockNewsByCharPtr)(const Observable* newsCollection, const char* symbol);
typedef Observable* (WINAPI* ApiGetStockNewsByString)(const Observable* newsCollection, const FilterStringAsNumberArray& symbol,
#if (_MSC_VER > 1600)
	const std::unordered_set<unsigned __int64>* stockSet
#else
	const std::hash_set<unsigned __int64>* stockSet
#endif
	);

typedef Observable* (WINAPI* ApiFindStockNewsByString)(const Observable* newsCollection, const FilterStringAsNumberArray& symbol);

typedef unsigned char (WINAPI* ApiReleaseNewsCollection)(Observable* newsCollection, Observer* observer);
typedef Observable* (WINAPI* ApiUpdateNewsCollectionFilter)(Observable* newsCollection, Observer* observer, const WireSet& wireSet, unsigned int storyFilter, unsigned int metaFilter, unsigned int relevance, bool& oldCollectionDeleted);
typedef bool (WINAPI* ApiGetWireInfoAt)(unsigned int at, std::string& description, unsigned int& id, unsigned short& subid, unsigned short& baseId, bool& subwire, bool& entitled);
typedef bool (WINAPI* ApiGetNextWireInfo)(TakionIterator* iterator, std::string& description, unsigned int& id, unsigned short& subid, unsigned short& baseId, bool& subwire, bool& entitled);
typedef const std::string* (WINAPI* ApiGetNextTopicInfo)(TakionIterator* iterator, std::string* description);
typedef bool (WINAPI* ApiRequestHeadlines)(Observable* stockNews, unsigned short daysBack, unsigned int headlineCount, bool afterMarket);
typedef bool (WINAPI* ApiRequestStory)(const NewsHeadline* headline, bool showChain, bool displayHyperlink);
typedef const LineBufferArray* (WINAPI* ApiGetUnappliedHeadlines)(Observable* stockNews);
typedef Observable* (WINAPI* ApiFindNewsCollectionById)(unsigned int id);
typedef const NewsHeadline* (WINAPI* ApiFindHeadline)(const Observable* stockNews, const NewsResourceAsNumberArray& resourceId);

typedef bool (WINAPI* ApiBoolObservable)(const Observable* observable);
typedef bool (WINAPI* ApiBoolString)(std::string& str);

typedef unsigned int (WINAPI* ApiGetUIntByUInt64)(const unsigned __int64& numericSymbol);
typedef unsigned int (WINAPI* ApiGetUIntAndUInt64ByUInt64)(const unsigned __int64& numericSymbol, unsigned __int64& latestHeadlineDateTime);

typedef unsigned int (WINAPI* ApiGetHeadlineCount)(const Observable* stockNews);
typedef TakionIterator* (WINAPI* ApiCreateHeadlineIterator)(const Observable* stockNews);
typedef const NewsHeadline* (WINAPI* ApiGetNextHeadline)(TakionIterator* iterator);
typedef const NewsStory* (WINAPI* ApiFindStoryByResourceId)(const NewsResourceAsNumberArray& resourceId);
typedef const NewsStory* (WINAPI* ApiGetStory)();

//////////////////////////////////////////////////////////////////
	
bool WINAPI TN_IsTakionNewsConnected();
Observable* WINAPI TN_GetTakionNewsObservable();
void WINAPI TN_SetTakionNewsLogFile(void* logFileHandle);
/*
Observable* WINAPI TN_ObtainStockNewsByNum(Observable* oldStockNews, const Observable* newsCollection, const unsigned __int64& symbol);
Observable* WINAPI TN_ObtainStockNews(Observable* oldStockNews, const Observable* newsCollection, const char* symbol);
Observable* WINAPI TN_ObtainStringNews(Observable* oldStockNews, const Observable* newsCollection, const FilterStringAsNumberArray& symbol, const std::hash_set<unsigned __int64>* stockSet);
*/
Observable* WINAPI TN_ObtainStockNewsByNum(const Observable* newsCollection, const unsigned __int64& symbol);
Observable* WINAPI TN_ObtainStockNews(const Observable* newsCollection, const char* symbol);
Observable* WINAPI TN_ObtainStringNews(const Observable* newsCollection, const FilterStringAsNumberArray& symbol,
#if (_MSC_VER > 1600)
	const std::unordered_set<unsigned __int64>*
#else
	const std::hash_set<unsigned __int64>*
#endif
	stockSet);

Observable* WINAPI TN_FindStockNewsByNum(const Observable* newsCollection, const unsigned __int64& symbol);
Observable* WINAPI TN_FindStringNews(const Observable* newsCollection, const FilterStringAsNumberArray& symbol);

bool WINAPI TN_IsNewsCollectionInvalid(const Observable* newsCollection);
bool WINAPI TN_IsStringNewsInvalid(const Observable* stringNews);

bool WINAPI TN_DoMainThreadIdleTasks(LONG lCount);

unsigned char WINAPI TN_ReleaseNewsCollection(Observable* newsCollection, Observer* observer);
Observable* WINAPI TN_UpdateNewsCollectionFilter(Observable* newsCollection, Observer* observer, const WireSet& wireSet, unsigned int storyFilter, unsigned int metaFilter, unsigned int relevance, bool& oldCollectionDeleted);

unsigned int WINAPI TN_GetStockHeadlineCount(const unsigned __int64& numericSymbol);//ApiGetUIntByUInt64
unsigned int WINAPI TN_GetStockHeadlineCountAndLatestDateTime(const unsigned __int64& numericSymbol, unsigned __int64& latestHeadlineDateTime);//ApiGetUIntAndUInt64ByUInt64

unsigned int WINAPI TN_GetStockTodaysHeadlineCount(const unsigned __int64& numericSymbol);//ApiGetUIntByUInt64
unsigned int WINAPI TN_GetStockTodaysHeadlineCountAndLatestDateTime(const unsigned __int64& numericSymbol, unsigned __int64& latestHeadlineDateTime);//ApiGetUIntAndUInt64ByUInt64

unsigned int WINAPI TN_GetStockYestAfterMarketHeadlineCount(const unsigned __int64& numericSymbol);//ApiGetUIntByUInt64
unsigned int WINAPI TN_GetStockYestAfterMarketHeadlineCountAndLatestDateTime(const unsigned __int64& numericSymbol, unsigned __int64& latestHeadlineDateTime);//ApiGetUIntAndUInt64ByUInt64

unsigned int WINAPI TN_GetFilterStringLengthLimit();//ApiGetUInt
unsigned int WINAPI TN_GetFilterStringTokenLimit();//ApiGetUInt
bool WINAPI TN_TruncateSearchStringDownToTokens(std::string& str);

unsigned int WINAPI TN_GetWireCount();//ApiGetUInt
bool WINAPI TN_GetWireInfoAt(unsigned int at, std::string& description, unsigned int& id, unsigned short& subid, unsigned short& baseId, bool& subwire, bool& entitled);
TakionIterator* WINAPI TN_CreateWireIterator();//ApiCreateIterator
bool WINAPI TN_GetNextWireInfo(TakionIterator* iterator, std::string& description, unsigned int& id, unsigned short& subid, unsigned short& baseId, bool& subwire, bool& entitled);

const char* WINAPI TN_GetConnectionStatusInfo();
unsigned int WINAPI TN_GetAllWireCount();//ApiGetUInt
TakionIterator* WINAPI TN_CreateAllWireIterator();//ApiCreateIterator
bool WINAPI TN_GetNextAllWireInfo(TakionIterator* iterator, std::string& description, unsigned int& id, unsigned short& subid, unsigned short& baseId, bool& subwire, bool& entitled);

unsigned int WINAPI TN_GetTopicCount();
TakionIterator* WINAPI TN_CreateTopicIterator();
const std::string* WINAPI TN_GetNextTopicInfo(TakionIterator* iterator, std::string* description);

void WINAPI TN_AdjustToChangedScreen(int dx, int dy);
void WINAPI TN_NewsDisplayFilterDialog(CWnd* receipient,
	unsigned int code,
	const WireSet& wireSet,
	unsigned int storyFilter,
	unsigned int metaFilter,
	unsigned int relevance,
	CWnd* parent,
	const CPoint& mousePoint);

bool WINAPI TN_NewsGetFilterDialogValues(WireSet& wireSet,
	unsigned int& storyFilter,
	unsigned int& metaFilter,
	unsigned int& relevance);

void WINAPI TN_NewsDisplayLimitsDialog(CWnd* receipient,
	unsigned int code,
	unsigned short daysBack,
	unsigned int headlineCount,
	bool afterMarket,
	CWnd* parent,
	const CPoint& mousePoint);

bool WINAPI TN_NewsGetLimitsDialogValues(unsigned short& daysBack,
	unsigned int& headlineCount,
	bool& afterMarket);

unsigned char WINAPI TN_TakionNewsConnect(const char* hostName,
	unsigned short port,
	const char* userName,
	const char* password,
	const char* appName,
	const char* appVersion,
	const char* companyName,
	const char* sessionData,
	const char* proxyIpAddress,
	unsigned short proxyPort,
	const char* proxyProtocolName,
	const char* proxyUserName,
	const char* proxyPassword,
	const char* newPassword);

bool WINAPI TN_RequestHeadlines(Observable* stockNews, unsigned short daysBack, unsigned int headlineCount, bool afterMarket);
bool WINAPI TN_RequestStory(const NewsHeadline* headline, bool showChain, bool displayHyperlink);
const LineBufferArray* WINAPI TN_GetUnappliedHeadlines(Observable* stockNews);
Observable* WINAPI TN_FindNewsCollectionById(unsigned int id);
bool WINAPI TN_IsUpdatedHeadline(const Observable* stockNews, unsigned int updateOrdinal);
void WINAPI TN_SetUpdatedHeadline(Observable* stockNews);
void WINAPI TN_ReadNewHeadlines(Observable* stockNews);
void WINAPI TN_ReleaseNewHeadlines(Observable* stockNews);
const NewsHeadline* WINAPI TN_FindHeadline(const Observable* stockNews, const NewsResourceAsNumberArray& resourceId);
unsigned int WINAPI TN_GetHeadlineCount(const Observable* stockNews);
TakionIterator* WINAPI TN_CreateHeadlineIterator(const Observable* stockNews);
const NewsHeadline* WINAPI TN_GetNextHeadline(TakionIterator* iterator);
bool WINAPI TN_LockInquiryHeadlines(Observable* stockNews);
void WINAPI TN_LockInquiryWaitHeadlines(Observable* stockNews);
void WINAPI TN_UnlockInquiryHeadlines(Observable* stockNews);
bool WINAPI TN_IsStockNewsRequested(const Observable* stockNews);

const std::string* WINAPI TN_GetSearchStringUnfiltered();
const std::string* WINAPI TN_GetSearchStringAll();
const std::string* WINAPI TN_GetSearchStringAllUs();

const NewsStory* WINAPI TN_FindStoryByResourceId(const NewsResourceAsNumberArray& resourceId);
const NewsStory* WINAPI TN_GetLastStory();
bool WINAPI TN_LockInquiryStory();
void WINAPI TN_LockInquiryWaitStory();
void WINAPI TN_UnlockInquiryStory();
bool WINAPI TN_IsUpdatedStory(unsigned int updateOrdinal);
void WINAPI TN_SetUpdatedStory();
Observable* WINAPI TN_GetStoryObservable();

bool WINAPI TN_LockInquiryWireNameStorage();
void WINAPI TN_LockInquiryWaitWireNameStorage();
void WINAPI TN_UnlockInquiryWireNameStorage();

bool WINAPI TN_LockInquiryAllWireNameStorage();
void WINAPI TN_LockInquiryWaitAllWireNameStorage();
void WINAPI TN_UnlockInquiryAllWireNameStorage();

bool WINAPI TN_LockInquiryTopicNameStorage();
void WINAPI TN_LockInquiryWaitTopicNameStorage();
void WINAPI TN_UnlockInquiryTopicNameStorage();

void WINAPI TN_ProcessConnectionInMainThread(bool connected);

bool WINAPI TN_NewsCollectionHasProfile(const Observable* newsCollection);

///////////////////////////////////
const char* WINAPI TD_GetModuleVersionStr();
unsigned __int64 WINAPI TD_GetModuleVersionNum();
const char* WINAPI TD_GetHeaderVersion();
unsigned __int64 WINAPI TD_GetHeaderVersionNum();
const char* WINAPI TD_GetFilePathAndName();
const char* WINAPI TD_GetPlatform();
const char* WINAPI TD_GetFileDescription();
const char* WINAPI TD_GetProductName();
void WINAPI TD_GetDllBuildDescription(std::string& buildStr);

int WINAPI TD_GetMainThreadPriority();
bool WINAPI TD_SetMainThreadPriority(const int& priority);

void WINAPI TD_Initialize(const unsigned __int64& exeVersion, const unsigned __int64& guiVersion, const unsigned __int64& utilsGuiVersion);
bool WINAPI TD_Terminate();
const unsigned __int64& WINAPI TD_GetExeVersion();
unsigned int WINAPI TD_GetExeVersion32();

unsigned int WINAPI TD_GetMinImbalanceChangeSecond();
unsigned int WINAPI TD_GetMaxImbalanceChangeSecond();

unsigned int WINAPI TD_GetTifAuctionSwitchMillisecond();

bool WINAPI TD_WriteCustomExternalMessageToMainThread(const TMsgCustomExternal* message);
//The first WSABUF in data should be castable to TMsgCustomExternal
bool WINAPI TD_WriteCustomExternalBuffersToMainThread(WSABUF* data, unsigned int count, unsigned int totalLength);

bool WINAPI TD_WriteExternalCommandMessageToMainThread(const Message* message);//message->m_type is 63000 to 63900

void WINAPI TD_WriteDataThreadBufferOverflowMessageToMainThread(const unsigned int& threadId, const unsigned int& ordinal);

Observable& WINAPI TD_GetCustomInternalObservable();
Observable& WINAPI TD_GetCustomExternalObservable();
Observable& WINAPI TD_GetAdminObservable();
Observable& WINAPI TD_GetAllAccountsTotalsObservable();
Observable& WINAPI TD_GetTopTenObservable();
Observable& WINAPI TD_GetExpirationObservable();
Observable& WINAPI TD_GetExternalCommandObservable();
Observable& WINAPI TD_GetNewClearingFirmObservable();
Observable& WINAPI TD_GetNewAccountObservable();
Observable& WINAPI TD_GetNewPositionObservable();
Observable& WINAPI TD_GetPositionExecutedObservable();
Observable& WINAPI TD_GetNewOrderObservable();
Observable& WINAPI TD_GetOrderErrorObservable();
Observable& WINAPI TD_GetExecutionObservable();
Observable& WINAPI TD_GetNewIndexObservable();
Observable& WINAPI TD_GetNewEquityObservable();
Observable& WINAPI TD_GetNewRsiObservable();
Observable& WINAPI TD_GetNewSubscribedStockObservable();
Observable& WINAPI TD_GetExtensionObservable();
Observable& WINAPI TD_GetHistoricalPrintObservable();
Observable& WINAPI TD_GetHistoricalChartObservable();
Observable& WINAPI TD_GetWorkerThreadPingObservable();

#ifndef TAKION_NO_OPTIONS
Observable* WINAPI TD_GetNewSubscribedOptionObservable();
#endif
//const LineBufferArray* WINAPI TD_GetUnappliedMessages();

//const char* WINAPI TD_GetDefaultTraderId();

void WINAPI TD_Log(const char* message, const char* prefix = nullptr, unsigned int level = 0);
void WINAPI TD_LogUpToLength(const char* message, unsigned int length, const char* prefix = nullptr, unsigned int level = 0);
void WINAPI TD_ForceLogOutput();

#ifdef __cplusplus
}
#endif

enum ConnectionDataType : unsigned char
{
	CDT_MARKET_DATA,
	CDT_EXECUTOR,
	CDT_MARKET_SORTER,
	CDT_HISTORICAL_PRINT,
	CDT_OPTION_MARKET_DATA,
	CDT_FUTURE_MARKET_DATA,
	CDT_FUTURE_EXECUTOR,

	CDT_NEWS,

	CDT_Count,
};

class TMsgSecurityDelete : public TMsgSecurity
{
public:
	TMsgSecurityDelete(const Security* const& security):TMsgSecurity(security, TM_STOCK_DELETE, sizeof(TMsgSecurityDelete)){}
};

class TMsgSortableSecurityDelete : public TMsgSecurity
{
public:
	TMsgSortableSecurityDelete(const Security* const& security):TMsgSecurity(security, TM_SORTABLE_SECURITY_DELETE, sizeof(TMsgSortableSecurityDelete)){}
};
/*
class TMsgSecurityAddIdle : public TMsgSecurity
{
public:
	TMsgSecurityAddIdle(Security* security):TMsgSecurity(security, TM_STOCK_ADD_IDLE, sizeof(TMsgSecurityAddIdle)){}
};

class TMsgSecurityRemoveIdle : public TMsgSecurity
{
public:
	TMsgSecurityRemoveIdle(Security* security):TMsgSecurity(security, TM_STOCK_REMOVE_IDLE, sizeof(TMsgSecurityRemoveIdle)){}
};
*/

class TMsgL1EntitlementsChanged : public TMessageSymbolMap
{
public:
	bool m_entitledPrintChanged;
	bool m_entitledL1Changed;
protected:
	TMsgL1EntitlementsChanged(const unsigned short& symbolMap,
		const bool& entitledPrintChanged,
		const bool& entitledL1Changed,
		const unsigned short& type,
		const unsigned short& length):
		TMessageSymbolMap(symbolMap, type, length),
		m_entitledPrintChanged(entitledPrintChanged),
		m_entitledL1Changed(entitledL1Changed)
	{
	}
};

class TMsgSortableSecurityEntitlementsChanged : public TMsgL1EntitlementsChanged
{
public:
	TMsgSortableSecurityEntitlementsChanged(const unsigned short& symbolMap,
		const bool& entitledPrintChanged,
		const bool& entitledL1Changed):
		TMsgL1EntitlementsChanged(symbolMap,
			entitledPrintChanged,
			entitledL1Changed,
			TM_SORTABLE_SECURITY_ENTITLEMENTS_CHANGED, 
			sizeof(TMsgSortableSecurityEntitlementsChanged))
	{
	}
};

class TMsgSortableSecurityExtEntitlementsChanged : public TMsgL1EntitlementsChanged
{
public:
	TMsgSortableSecurityExtEntitlementsChanged(const unsigned short& symbolMap,
		const bool& entitledPrintChanged,
		const bool& entitledL1Changed) :
		TMsgL1EntitlementsChanged(symbolMap,
			entitledPrintChanged,
			entitledL1Changed,
			TM_SORTABLE_SECURITY_EXT_ENTITLEMENTS_CHANGED,
			sizeof(TMsgSortableSecurityExtEntitlementsChanged))
	{
	}
};

class TMsgStockEntitlements : public TMsgL1EntitlementsChanged
{
public:
	bool m_entitledL2Changed;
protected:
	TMsgStockEntitlements(const unsigned short& symbolMap,
		const bool& entitledPrintChanged,
		const bool& entitledL1Changed,
		const bool& entitledL2Changed,
		const unsigned short& type,
		const unsigned short& length):
		TMsgL1EntitlementsChanged(symbolMap,
			entitledPrintChanged,
			entitledL1Changed,
			type,
			length),
		m_entitledL2Changed(entitledL2Changed)
	{
	}
};

class TMsgStockEntitlementsChanged : public TMsgStockEntitlements
{
public:
	TMsgStockEntitlementsChanged(const unsigned short& symbolMap,
		const bool& entitledPrintChanged,
		const bool& entitledL1Changed,
		const bool& entitledL2Changed):
		TMsgStockEntitlements(symbolMap,
			entitledPrintChanged,
			entitledL1Changed,
			entitledL2Changed,
			TM_STOCK_ENTITLEMENTS_CHANGED, 
			sizeof(TMsgStockEntitlementsChanged))
	{
	}
};

class TMsgStockExtEntitlementsChanged : public TMsgStockEntitlements
{
public:
	TMsgStockExtEntitlementsChanged(const unsigned short& symbolMap,
		const bool& entitledPrintChanged,
		const bool& entitledL1Changed,
		const bool& entitledL2Changed) :
		TMsgStockEntitlements(symbolMap,
			entitledPrintChanged,
			entitledL1Changed,
			entitledL2Changed,
			TM_STOCK_EXT_ENTITLEMENTS_CHANGED,
			sizeof(TMsgStockExtEntitlementsChanged))
	{
	}
};

#ifndef TAKION_NO_OPTIONS
class TMsgOptionEntitlements : public TMessageOptionBlock
{
public:
	bool m_entitledPrintChanged;
	bool m_entitledL1Changed;
	bool m_entitledL2Changed;
protected:
	TMsgOptionEntitlements(const char* const& symbol,
		const unsigned __int64& optionBlock,
		const bool& entitledPrintChanged,
		const bool& entitledL1Changed,
		const bool& entitledL2Changed,
		const unsigned short& type,
		const unsigned short& length):
		TMessageOptionBlock(symbol,
			optionBlock,
			type,
			length),
		m_entitledPrintChanged(entitledPrintChanged),
		m_entitledL1Changed(entitledL1Changed),
		m_entitledL2Changed(entitledL2Changed)
	{
	}
	TMsgOptionEntitlements(const unsigned __int64& symbol,
		const unsigned __int64& optionBlock,
		const bool& entitledPrintChanged,
		const bool& entitledL1Changed,
		const bool& entitledL2Changed,
		const unsigned short& type,
		const unsigned short& length):
		TMessageOptionBlock(symbol,
			optionBlock,
			type,
			length),
		m_entitledPrintChanged(entitledPrintChanged),
		m_entitledL1Changed(entitledL1Changed),
		m_entitledL2Changed(entitledL2Changed)
	{
	}
};


class TMsgOptionEntitlementsChanged : public TMsgOptionEntitlements
{
public:
	TMsgOptionEntitlementsChanged(const char* const& symbol,
		const unsigned __int64& optionBlock,
		const bool& entitledPrintChanged,
		const bool& entitledL1Changed,
		const bool& entitledL2Changed):
		TMsgOptionEntitlements(symbol,
			optionBlock,
			entitledPrintChanged,
			entitledL1Changed,
			entitledL2Changed,
			TM_OPTION_ENTITLEMENTS_CHANGED,
			sizeof(TMsgOptionEntitlementsChanged))
	{
	}
	TMsgOptionEntitlementsChanged(const unsigned __int64& symbol,
		const unsigned __int64& optionBlock,
		const bool& entitledPrintChanged,
		const bool& entitledL1Changed,
		const bool& entitledL2Changed):
		TMsgOptionEntitlements(symbol,
			optionBlock,
			entitledPrintChanged,
			entitledL1Changed,
			entitledL2Changed,
			TM_OPTION_ENTITLEMENTS_CHANGED,
			sizeof(TMsgOptionEntitlementsChanged))
	{
	}
};

class TMsgOptionExtEntitlementsChanged : public TMsgOptionEntitlements
{
public:
	TMsgOptionExtEntitlementsChanged(const char* const& symbol,
		const unsigned __int64& optionBlock,
		const bool& entitledPrintChanged,
		const bool& entitledL1Changed,
		const bool& entitledL2Changed) :
		TMsgOptionEntitlements(symbol,
			optionBlock,
			entitledPrintChanged,
			entitledL1Changed,
			entitledL2Changed,
			TM_OPTION_EXT_ENTITLEMENTS_CHANGED,
			sizeof(TMsgOptionExtEntitlementsChanged))
	{
	}
	TMsgOptionExtEntitlementsChanged(const unsigned __int64& symbol,
		const unsigned __int64& optionBlock,
		const bool& entitledPrintChanged,
		const bool& entitledL1Changed,
		const bool& entitledL2Changed) :
		TMsgOptionEntitlements(symbol,
			optionBlock,
			entitledPrintChanged,
			entitledL1Changed,
			entitledL2Changed,
			TM_OPTION_EXT_ENTITLEMENTS_CHANGED,
			sizeof(TMsgOptionExtEntitlementsChanged))
	{
	}
};

class TMsgFutureEntitlementsChanged : public TMsgStockEntitlements
{
public:
	TMsgFutureEntitlementsChanged(const unsigned short& symbolMap,
		const bool& entitledPrintChanged,
		const bool& entitledL1Changed,
		const bool& entitledL2Changed):
		TMsgStockEntitlements(symbolMap,
			entitledPrintChanged,
			entitledL1Changed,
			entitledL2Changed,
			TM_FUTURE_ENTITLEMENTS_CHANGED, 
			sizeof(TMsgFutureEntitlementsChanged))
	{
	}
};

class TMsgFutureExtEntitlementsChanged : public TMsgStockEntitlements
{
public:
	TMsgFutureExtEntitlementsChanged(const unsigned short& symbolMap,
		const bool& entitledPrintChanged,
		const bool& entitledL1Changed,
		const bool& entitledL2Changed) :
		TMsgStockEntitlements(symbolMap,
			entitledPrintChanged,
			entitledL1Changed,
			entitledL2Changed,
			TM_FUTURE_EXT_ENTITLEMENTS_CHANGED,
			sizeof(TMsgFutureExtEntitlementsChanged))
	{
	}
};

#endif

class TMsgSecurityAddIdle : public TMessageSymbol
{
public:
	TMsgSecurityAddIdle(const char* symbol):TMessageSymbol(symbol, TM_STOCK_ADD_IDLE, sizeof(TMsgSecurityAddIdle)){}
	TMsgSecurityAddIdle(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_STOCK_ADD_IDLE, sizeof(TMsgSecurityAddIdle)){}
	TMsgSecurityAddIdle():TMessageSymbol(TM_STOCK_ADD_IDLE, sizeof(TMsgSecurityAddIdle)){}
};

class TMsgSecurityRemoveIdle : public TMessageSymbol
{
public:
	TMsgSecurityRemoveIdle(const char* symbol):TMessageSymbol(symbol, TM_STOCK_REMOVE_IDLE, sizeof(TMsgSecurityRemoveIdle)){}
	TMsgSecurityRemoveIdle(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_STOCK_REMOVE_IDLE, sizeof(TMsgSecurityRemoveIdle)){}
	TMsgSecurityRemoveIdle():TMessageSymbol(TM_STOCK_REMOVE_IDLE, sizeof(TMsgSecurityRemoveIdle)){}
};

class TMsgSortableSecurityAddIdle : public TMessageSymbol
{
public:
	TMsgSortableSecurityAddIdle(const char* symbol):TMessageSymbol(symbol, TM_SORTABLE_SECURITY_ADD_IDLE, sizeof(TMsgSortableSecurityAddIdle)){}
	TMsgSortableSecurityAddIdle(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_SORTABLE_SECURITY_ADD_IDLE, sizeof(TMsgSortableSecurityAddIdle)){}
	TMsgSortableSecurityAddIdle():TMessageSymbol(TM_SORTABLE_SECURITY_ADD_IDLE, sizeof(TMsgSortableSecurityAddIdle)){}
};

class TMsgSortableSecurityRemoveIdle : public TMessageSymbol
{
public:
	TMsgSortableSecurityRemoveIdle(const char* symbol):TMessageSymbol(symbol, TM_SORTABLE_SECURITY_REMOVE_IDLE, sizeof(TMsgSortableSecurityRemoveIdle)){}
	TMsgSortableSecurityRemoveIdle(const unsigned __int64& symbol):TMessageSymbol(symbol, TM_SORTABLE_SECURITY_REMOVE_IDLE, sizeof(TMsgSortableSecurityRemoveIdle)){}
	TMsgSortableSecurityRemoveIdle():TMessageSymbol(TM_SORTABLE_SECURITY_REMOVE_IDLE, sizeof(TMsgSortableSecurityRemoveIdle)){}
};

class TMsgPositionSortableSecurityInitialized : public TMsgSecurity
{
public:
	TMsgPositionSortableSecurityInitialized(const Security* const& security):
		TMsgSecurity(security, TM_POSITION_SORTABLE_SECURITY_INITIALIZED, sizeof(TMsgPositionSortableSecurityInitialized))
	{
	}
};

class TMsgPositionSecurityInitialized : public TMsgSecurity
{
public:
	TMsgPositionSecurityInitialized(const Security* const& security):
		TMsgSecurity(security, TM_POSITION_SECURITY_INITIALIZED, sizeof(TMsgPositionSecurityInitialized))
	{
	}
};

#ifndef TAKION_NO_OPTIONS
class TMsgPositionOptionInitialized : public TMsgSecurity
{
public:
	TMsgPositionOptionInitialized(const Security* const& security):
		TMsgSecurity(security, TM_POSITION_OPTION_INITIALIZED, sizeof(TMsgPositionOptionInitialized))
	{
	}
};

class TMsgPositionUnderlierSortableSecurityInitialized : public TMsgSecurity
{
public:
	TMsgPositionUnderlierSortableSecurityInitialized(const Security* const& security):
		TMsgSecurity(security, TM_POSITION_UNDERLIER_SORTABLE_SECURITY_INITIALIZED, sizeof(TMsgPositionUnderlierSortableSecurityInitialized))
	{
	}
};

class TMsgPositionUnderlierSecurityInitialized : public TMsgSecurity
{
public:
	TMsgPositionUnderlierSecurityInitialized(const Security* const& security):
		TMsgSecurity(security, TM_POSITION_UNDERLIER_SECURITY_INITIALIZED, sizeof(TMsgPositionUnderlierSecurityInitialized))
	{
	}
};
#endif

class TMsgPositionSecurityUpdated : public TMsgSecurity
{
public:
	TMsgPositionSecurityUpdated(const Security* const& security, const bool& hasPrints):
		TMsgSecurity(security, TM_POSITION_SECURITY_UPDATED, sizeof(TMsgPositionSecurityUpdated)),
		m_hasPrints(hasPrints)
	{
	}
	bool m_hasPrints;
};

class PositionPhantomSharesChanged : public Message
{
public:
	PositionPhantomSharesChanged(const char& phantomShares):Message(TM_POSITION_PHANTOM_SHARES_CHANGED, sizeof(PositionPhantomSharesChanged)), m_phantomShares(phantomShares){}
	char m_phantomShares;
};

class TMsgOrderObject : public Message
{
public:
	Order* m_order;
protected:
	TMsgOrderObject(Order* const& order, const unsigned short& type, const unsigned short& length):
		Message(type, length),
		m_order(order)
	{
	}
};

class TMsgOrderUserDataNullified : public TMsgOrderObject
{
public:
	TMsgOrderUserDataNullified(Order* const& order):TMsgOrderObject(order, TM_ORDER_USER_DATA_NULLIFIED, sizeof(TMsgOrderUserDataNullified)){}
};
/*
class TMsgOrderUserDataNullified : public TMsgOrderObject
{
public:
	TMsgOrderUserDataNullified(Order* const& order):TMsgOrderObject(order, TM_ORDER_USER_DATA_NULLIFIED, sizeof(TMsgOrderUserDataNullified)){}
};
*/
class TMsgOrder : public TMsgOrderObject
{
public:
	unsigned int m_pendingShares;
protected:
	TMsgOrder(Order* const& order, const unsigned int& pendingShares, const unsigned short& type, const unsigned short& length):
		TMsgOrderObject(order, type, length),
		m_pendingShares(pendingShares)
	{
	}
};

class TMsgNewOrder : public TMsgOrder
{
public:
	TMsgNewOrder(Order* const& order, const unsigned int& pendingShares)://, const bool& newOcoId):
		TMsgOrder(order, pendingShares, TM_NEW_ORDER, sizeof(TMsgNewOrder))
//		m_newOcoId(newOcoId)
	{
	}
//	bool m_newOcoId;
};

class TMsgDeadOrder : public TMsgOrder
{
public:
	TMsgDeadOrder(Order* const& order, const unsigned int& pendingShares):TMsgOrder(order, pendingShares, TM_DEAD_ORDER, sizeof(TMsgDeadOrder)){}
};

class TMsgCancelRejected : public TMsgOrder
{
public:
	TMsgCancelRejected(Order* const& order, const unsigned int& pendingShares):TMsgOrder(order, pendingShares, TM_CANCEL_REJECTED, sizeof(TMsgCancelRejected)){}
};


class TMsgOrderDelete : public TMsgOrder
{
public:
	TMsgOrderDelete(Order* const& order):TMsgOrder(order, 0, TM_ORDER_DELETE, sizeof(TMsgOrderDelete)){}
};

class TMsgUpdatedOrder : public TMsgOrder
{
public:
	TMsgUpdatedOrder(Order* const& order, const unsigned int& pendingShares, const unsigned char& orderState)://, const unsigned char& flags):
		TMsgOrder(order, pendingShares, TM_UPDATED_ORDER, sizeof(TMsgUpdatedOrder)),
		m_orderState(orderState)
//		m_flags(flags)
	{
	}
//	unsigned char m_flags;
	unsigned char m_orderState;//enum OrderState
};

class TMsgExecution : public Message
{
public:
	Execution* m_execution;
protected:
	TMsgExecution(Execution* const& execution, const unsigned short& type, const unsigned short& length):Message(type, length), m_execution(execution){}
};

class TMsgNewExecution : public TMsgExecution
{
public:
	TMsgNewExecution(Execution* const& execution,
		const unsigned int& remainingQuantity,
		const unsigned int& cumulativeFilledQuantity):
		
		TMsgExecution(execution, TM_NEW_EXECUTION, sizeof(TMsgNewExecution)),
		m_remainingQuantity(remainingQuantity),
		m_cumulativeFilledQuantity(cumulativeFilledQuantity)
	{
	}
	unsigned int m_remainingQuantity;
	unsigned int m_cumulativeFilledQuantity;
};
/*Looks like this message is not used
class TMsgOtherOrderExecuted : public TMsgExecution
{
public:
	TMsgOtherOrderExecuted(Execution* const& execution):
		TMsgExecution(execution, TM_OTHER_ORDER_EXECUTED, sizeof(TMsgOtherOrderExecuted))
	{
	}
};
*/
class TMsgPositionDataObject : public Message
{
public:
	const PositionData* m_position;
protected:
	TMsgPositionDataObject(const PositionData* const& position, const unsigned short& type, const unsigned short& length):Message(type, length), m_position(position){}
};

class TMsgPositionObject : public Message
{
public:
	const Position* m_position;
protected:
	TMsgPositionObject(const Position* const& position, const unsigned short& type, const unsigned short& length):Message(type, length), m_position(position){}
};

class TMsgNewPosition : public TMsgPositionObject
{
public:
	TMsgNewPosition(const Position* const& position):TMsgPositionObject(position, TM_NEW_POSITION, sizeof(TMsgNewPosition)){}
};
/*
class TMsgAddPositionToSecurity : public TMsgPositionObject
{
public:
	TMsgAddPositionToSecurity(Position* position, Security* security):TMsgPositionObject(position, TM_ADD_POSITION_TO_SECURITY, sizeof(TMsgAddPositionToSecurity)), m_security(security){}
	Security* m_security;
};
*/
class TMsgUpdatedPosition : public TMsgPositionDataObject
{
public:
	TMsgUpdatedPosition(const PositionData* const& position):TMsgPositionDataObject(position, TM_UPDATED_POSITION, sizeof(TMsgUpdatedPosition)){}
};

class TMsgPositionDelete : public TMsgPositionObject
{
public:
	TMsgPositionDelete(const Position* const& position):TMsgPositionObject(position, TM_POSITION_DELETE, sizeof(TMsgPositionDelete)){}
};

class TMsgExecutedPosition : public TMsgPositionObject
{
public:
	TMsgExecutedPosition(const Position* const& position, const unsigned char& positionUpdateFlags):TMsgPositionObject(position, TM_EXECUTED_POSITION, sizeof(TMsgExecutedPosition)), m_positionUpdateFlags(positionUpdateFlags){}
	unsigned char m_positionUpdateFlags;
};

class TMsgOrdinal : public Message
{
public:
	unsigned short m_ordinal;
protected:
	TMsgOrdinal(const unsigned short& ordinal, const unsigned short& type, const unsigned short& length) :Message(type, length), m_ordinal(ordinal){}
};

class TMsgClearingFirmUpdate : public TMsgOrdinal
{
public:
	TMsgClearingFirmUpdate(const unsigned short& clearingFirmOrdinal):TMsgOrdinal(clearingFirmOrdinal, TM_CLEARING_FIRM_UPDATE, sizeof(TMsgClearingFirmUpdate)){}
};

class TMsgClearingFirmConstraintsUpdate : public TMsgOrdinal
{
public:
	TMsgClearingFirmConstraintsUpdate(const unsigned short& clearingFirmOrdinal):TMsgOrdinal(clearingFirmOrdinal, TM_CLEARING_FIRM_CONSTRAINTS_UPDATE, sizeof(TMsgClearingFirmConstraintsUpdate)){}
};

class TMsgClearingFirmRetailUpdate : public TMsgOrdinal
{
public:
	TMsgClearingFirmRetailUpdate(const unsigned short& clearingFirmOrdinal):TMsgOrdinal(clearingFirmOrdinal, TM_CLEARING_FIRM_RETAIL_UPDATE, sizeof(TMsgClearingFirmRetailUpdate)){}
};

class TMsgClearingFirm : public Message
{
public:
	ClearingFirm* m_clearingFirm;
protected:
	TMsgClearingFirm(ClearingFirm* const& clearingFirm, const unsigned short& type, const unsigned short& length):Message(type, length), m_clearingFirm(clearingFirm){}
};

class TMsgNewClearingFirm : public TMsgClearingFirm
{
public:
	TMsgNewClearingFirm(ClearingFirm* const& clearingFirm):TMsgClearingFirm(clearingFirm, TM_NEW_CLEARING_FIRM, sizeof(TMsgNewClearingFirm)){}
};

class TMsgUpdatedClearingFirm : public TMsgClearingFirm
{
public:
	TMsgUpdatedClearingFirm(ClearingFirm* const& clearingFirm):TMsgClearingFirm(clearingFirm, TM_UPDATED_CLEARING_FIRM, sizeof(TMsgUpdatedClearingFirm)){}
};

class TMsgUpdatedClearingFirmConstraints : public TMsgClearingFirm
{
public:
	TMsgUpdatedClearingFirmConstraints(ClearingFirm* const& clearingFirm):TMsgClearingFirm(clearingFirm, TM_UPDATED_CLEARING_FIRM_CONSTRAINTS, sizeof(TMsgUpdatedClearingFirmConstraints)){}
};

class TMsgUpdatedClearingFirmRetail : public TMsgClearingFirm
{
public:
	TMsgUpdatedClearingFirmRetail(ClearingFirm* const& clearingFirm):TMsgClearingFirm(clearingFirm, TM_UPDATED_CLEARING_FIRM_RETAIL, sizeof(TMsgUpdatedClearingFirmRetail)){}
};

class TMsgDeleteAllClearingFirms : public Message
{
public:
	TMsgDeleteAllClearingFirms():Message(TM_DELETE_ALL_CLEARING_FIRMS, sizeof(TMsgDeleteAllClearingFirms)){}
};

class TMsgDeleteAllAccounts : public Message
{
public:
	TMsgDeleteAllAccounts():Message(TM_DELETE_ALL_ACCOUNTS, sizeof(TMsgDeleteAllAccounts)){}
};

class TMsgAllAccountsLoaded : public Message
{
public:
	TMsgAllAccountsLoaded():Message(TM_ALL_ACCOUNTS_LOADED, sizeof(TMsgAllAccountsLoaded)){}
};

class TMsgAccount : public Message
{
public:
	Account* m_account;
protected:
	TMsgAccount(Account* const& account, const unsigned short& type, const unsigned short& length):Message(type, length), m_account(account){}
};
/*
class TMsgAccountObject : public Message
{
public:
	char m_accountId[MAX_ACCOUNT_SIZE];
protected:
	TMsgAccountObject(const char* accountName, unsigned short type, unsigned short length):
		Message(type, length)
	{
		U_CopyAndPad(m_accountId, sizeof(m_accountId), accountName, '\0');
	}
};
*/

class TMsgHardBuyingPowerHit : public TMsgAccountObject
{
public:
	TMsgHardBuyingPowerHit(const char* const& accountName,
		const Money& hardBpUsed,
		const Money& hardBuyingPower,
#ifndef TAKION_NO_OPTIONS
		const unsigned char& securityMask,
#endif
		const bool& marginExcess,
		const bool& hardBpHit):
		TMsgAccountObject(accountName, TM_HARD_BP_HIT, sizeof(TMsgHardBuyingPowerHit)),
		m_hardBpUsed(hardBpUsed),
		m_hardBuyingPower(hardBuyingPower),
#ifndef TAKION_NO_OPTIONS
		m_securityMask(securityMask),
#endif
		m_marginExcess(marginExcess),
		m_hardBpHit(hardBpHit)
	{
	}
	Money m_hardBpUsed;
	Money m_hardBuyingPower;
#ifndef TAKION_NO_OPTIONS
	unsigned char m_securityMask;
#endif
	bool m_marginExcess;
	bool m_hardBpHit;
};
/*
class TMsgHardMarginExcessHit : public TMsgAccountObject
{
public:
	TMsgHardMarginExcessHit(const char* const& accountName, const Money& hardMeUsed, const Money& hardMarginExcess, const bool& hardMeHit):
		TMsgAccountObject(accountName, TM_HARD_ME_HIT, sizeof(TMsgHardMarginExcessHit)),
		m_hardMeUsed(hardMeUsed),
		m_hardMarginExcess(hardMarginExcess),
		m_hardMeHit(hardMeHit)
	{
	}
	Money m_hardMeUsed;
	Money m_hardMarginExcess;
	bool m_hardMeHit;
};
*/
class TMsgAccountDelete : public TMsgAccount
{
public:
	TMsgAccountDelete(Account* const& account):TMsgAccount(account, TM_ACCOUNT_DELETE, sizeof(TMsgAccountDelete)){}
};

class TMsgUpdatedAccountBase : public TMsgAccount
{
public:
	bool m_constraintsChanged;
protected:
	TMsgUpdatedAccountBase(Account* const& account, const bool& constraintsChanged, const unsigned short& type, const unsigned short& length):TMsgAccount(account, type, length), m_constraintsChanged(constraintsChanged){}
};

class TMsgUpdatedAccount : public TMsgUpdatedAccountBase
{
public:
	TMsgUpdatedAccount(Account* const& account, const bool& constraintsChanged):TMsgUpdatedAccountBase(account, constraintsChanged, TM_UPDATED_ACCOUNT, sizeof(TMsgUpdatedAccount)){}
};

class TMsgUpdatedAccountAndPositionBase : public TMsgUpdatedAccountBase
{
public:
	const Position* m_position;
protected:
	TMsgUpdatedAccountAndPositionBase(Account* const& account, const bool& constraintsChanged, const Position* const& position, const unsigned short& type, const unsigned short& length):TMsgUpdatedAccountBase(account, constraintsChanged, type, length), m_position(position){}
};

class TMsgUpdatedAccountAndPosition : public TMsgUpdatedAccountAndPositionBase//used for providing "info" to the Notify function
{
public:
	TMsgUpdatedAccountAndPosition(Account* const& account, const bool& constraintsChanged, const Position* const& position, const unsigned int& level1Bid, const unsigned int& level1Ask):
		TMsgUpdatedAccountAndPositionBase(account, constraintsChanged, position, TM_UPDATED_ACCOUNT_AND_POSITION, sizeof(TMsgUpdatedAccountAndPosition)),
		m_level1Bid(level1Bid),
		m_level1Ask(level1Ask)
	{
	}
	unsigned int m_level1Bid;//Use Price(m_level1Bid) to create a Price object
	unsigned int m_level1Ask;//Use Price(m_level1Ask) to create a Price object
};

class TMsgNewAccountObject : public TMsgAccount
{
public:
	TMsgNewAccountObject(Account* const& account):TMsgAccount(account, TM_NEW_ACCOUNT, sizeof(TMsgNewAccountObject)){}
};

class Connection;

class TMsgConnectionObject : public Message
{
public:
	TMsgConnectionObject(Connection* const& connection):Message(TM_CONNECTION_OBJECT, sizeof(TMsgConnectionObject)), m_connection(connection){}
	Connection* m_connection;
};

class TMsgSetTierSize : public TMessageSymbol//sent internally to threads
{
public:
	unsigned int m_newTierSize;
protected:
	TMsgSetTierSize(const char* const& symbol, const unsigned int& newTierSize, const unsigned short& type, const unsigned short& length):TMessageSymbol(symbol, type, length),m_newTierSize(newTierSize){}
	TMsgSetTierSize(const unsigned __int64& symbol, const unsigned int& newTierSize, const unsigned short& type, const unsigned short& length):TMessageSymbol(symbol, type, length),m_newTierSize(newTierSize){}
};

class TMsgSetStockTierSize : public TMsgSetTierSize
{
public:
	TMsgSetStockTierSize(const char* const& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionKey,
#endif
		const unsigned int& newTierSize):
		TMsgSetTierSize(symbol, newTierSize, TM_SET_STOCK_TIER_SIZE, sizeof(TMsgSetStockTierSize))
#ifndef TAKION_NO_OPTIONS
		,m_optionKey(optionKey)
#endif
	{
	}
	TMsgSetStockTierSize(const unsigned __int64& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionKey,
#endif
		const unsigned int& newTierSize):
		TMsgSetTierSize(symbol, newTierSize, TM_SET_STOCK_TIER_SIZE, sizeof(TMsgSetStockTierSize))
#ifndef TAKION_NO_OPTIONS
		,m_optionKey(optionKey)
#endif
	{
	}
	unsigned __int64 m_optionKey;
};

class TMsgSetEquityTierSize : public TMsgSetTierSize
{
public:
	TMsgSetEquityTierSize(const char* const& symbol, const unsigned int& newTierSize):TMsgSetTierSize(symbol, newTierSize, TM_SET_EQUITY_TIER_SIZE, sizeof(TMsgSetEquityTierSize)){}
	TMsgSetEquityTierSize(const unsigned __int64& symbol, const unsigned int& newTierSize):TMsgSetTierSize(symbol, newTierSize, TM_SET_EQUITY_TIER_SIZE, sizeof(TMsgSetEquityTierSize)){}
};

////
class TMsgSetStockCustomPriceBase : public TMsgSetTierSize
{
public:
	TMsgSetStockCustomPriceBase(const char* const& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionKey,
#endif
		const unsigned int& newCustomPriceBaseCompact):
		TMsgSetTierSize(symbol, newCustomPriceBaseCompact, TM_SET_STOCK_CUSTOM_PRICE_BASE, sizeof(TMsgSetStockCustomPriceBase))
#ifndef TAKION_NO_OPTIONS
		,m_optionKey(optionKey)
#endif
	{
	}
	TMsgSetStockCustomPriceBase(const unsigned __int64& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionKey,
#endif
		const unsigned int& newCustomPriceBaseCompact):
		TMsgSetTierSize(symbol, newCustomPriceBaseCompact, TM_SET_STOCK_CUSTOM_PRICE_BASE, sizeof(TMsgSetStockCustomPriceBase))
#ifndef TAKION_NO_OPTIONS
		,m_optionKey(optionKey)
#endif
	{
	}
	unsigned __int64 m_optionKey;
};

class TMsgSetEquityCustomPriceBase : public TMsgSetTierSize
{
public:
	TMsgSetEquityCustomPriceBase(const char* const& symbol, const unsigned int& newCustomPriceBaseCompact):TMsgSetTierSize(symbol, newCustomPriceBaseCompact, TM_SET_EQUITY_CUSTOM_PRICE_BASE, sizeof(TMsgSetEquityCustomPriceBase)){}
	TMsgSetEquityCustomPriceBase(const unsigned __int64& symbol, const unsigned int& newCustomPriceBaseCompact):TMsgSetTierSize(symbol, newCustomPriceBaseCompact, TM_SET_EQUITY_CUSTOM_PRICE_BASE, sizeof(TMsgSetEquityCustomPriceBase)){}
};

////
class TMsgSetStockCustomDate : public TMsgSetTierSize
{
public:
	TMsgSetStockCustomDate(const char* const& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionKey,
#endif
		const unsigned int& newCustomDate):
		TMsgSetTierSize(symbol, newCustomDate, TM_SET_STOCK_CUSTOM_DATE, sizeof(TMsgSetStockCustomDate))
#ifndef TAKION_NO_OPTIONS
		,m_optionKey(optionKey)
#endif
	{
	}
	TMsgSetStockCustomDate(const unsigned __int64& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionKey,
#endif
		const unsigned int& newCustomDateCompact):
		TMsgSetTierSize(symbol, newCustomDateCompact, TM_SET_STOCK_CUSTOM_DATE, sizeof(TMsgSetStockCustomDate))
#ifndef TAKION_NO_OPTIONS
		,m_optionKey(optionKey)
#endif
	{
	}
	unsigned __int64 m_optionKey;
};

class TMsgSetEquityCustomDate : public TMsgSetTierSize
{
public:
	TMsgSetEquityCustomDate(const char* const& symbol, const unsigned int& newCustomDateCompact):TMsgSetTierSize(symbol, newCustomDateCompact, TM_SET_EQUITY_CUSTOM_DATE, sizeof(TMsgSetEquityCustomDate)){}
	TMsgSetEquityCustomDate(const unsigned __int64& symbol, const unsigned int& newCustomDateCompact):TMsgSetTierSize(symbol, newCustomDateCompact, TM_SET_EQUITY_CUSTOM_DATE, sizeof(TMsgSetEquityCustomDate)){}
};

////

class TMsgSetStockTemporaryTierSize : public TMsgSetTierSize
{
public:
	TMsgSetStockTemporaryTierSize(const char* const& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionKey,
#endif
		const unsigned int& newTierSize):
		TMsgSetTierSize(symbol, newTierSize, TM_SET_STOCK_TEMPORARY_TIER_SIZE, sizeof(TMsgSetStockTemporaryTierSize))
#ifndef TAKION_NO_OPTIONS
		,m_optionKey(optionKey)
#endif
	{
	}
	TMsgSetStockTemporaryTierSize(const unsigned __int64& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionKey,
#endif
		const unsigned int& newTierSize):
		TMsgSetTierSize(symbol, newTierSize, TM_SET_STOCK_TEMPORARY_TIER_SIZE, sizeof(TMsgSetStockTemporaryTierSize))
#ifndef TAKION_NO_OPTIONS
		,m_optionKey(optionKey)
#endif
	{
	}
	unsigned __int64 m_optionKey;
};

class TMsgSetEquityTemporaryTierSize : public TMsgSetTierSize//Observers notified in main thread
{
public:
	TMsgSetEquityTemporaryTierSize(const char* const& symbol, const unsigned int& newTierSize):TMsgSetTierSize(symbol, newTierSize, TM_SET_EQUITY_TEMPORARY_TIER_SIZE, sizeof(TMsgSetEquityTemporaryTierSize)){}
	TMsgSetEquityTemporaryTierSize(const unsigned __int64& symbol, const unsigned int& newTierSize):TMsgSetTierSize(symbol, newTierSize, TM_SET_EQUITY_TEMPORARY_TIER_SIZE, sizeof(TMsgSetEquityTemporaryTierSize)){}
};

class TMsgSendOrderAlgorithm : public
#ifndef TAKION_NO_OPTIONS
	TMsgOptionSymbol
#else
	TMessageSymbol
#endif
{
public:
	TMsgSendOrderAlgorithm(const char* const& symbol,
#ifndef TAKION_NO_OPTIONS
		const unsigned __int64& optionBlock,
#endif
		const char* const& accountName,
		const OrderAlgorithm* const& orderAlgorithm,
		const char& tradingState,
		const char& shortable,
		const char& regSho,
		const unsigned char& htb,
		const unsigned char& primaryExchangeEntitlementFlag,
		const bool& fromExtension):

#ifndef TAKION_NO_OPTIONS
		TMsgOptionSymbol(symbol, optionBlock,
#else
		TMessageSymbol(symbol,
#endif
			TM_SEND_ORDER_ALGORITHM, sizeof(TMsgSendOrderAlgorithm) + orderAlgorithm->GetAlgorithmSize()),
//		m_compactOpenPrice(compactOpenPrice),
//		m_ipo(ipo),
		m_tradingState(tradingState),
		m_shortable(shortable),
		m_regSho(regSho),
		m_htb(htb),
		m_primaryExchangeEntitlementFlag(primaryExchangeEntitlementFlag),
		m_fromExtension(fromExtension)
	{
		U_CopyAndPad(m_accountName, sizeof(m_accountName), accountName, '\0', true);
	}

	char m_accountName[MAX_ACCOUNT_SIZE];
	char m_tradingState;
	char m_shortable;
	char m_regSho;
	unsigned char m_htb;
	unsigned char m_primaryExchangeEntitlementFlag;
	bool m_fromExtension;
};

class TMsgPositionRemoveDelayedOrders : public TMsgAccountPositionObject
{
public:
	TMsgPositionRemoveDelayedOrders(const char* const& accountName = "", const unsigned __int64& symbol = 0
#ifndef TAKION_NO_OPTIONS
		,const unsigned __int64& optionBlock = 0
		,const unsigned char& securityType = 0
#endif
//		unsigned char securityType
		):
		TMsgAccountPositionObject(accountName, symbol,
//			securityType,
#ifndef TAKION_NO_OPTIONS
			optionBlock,
			securityType,
#endif
			TM_POSITION_REMOVE_DELAYED_ORDERS, sizeof(TMsgPositionRemoveDelayedOrders))
	{
	}
};

class TMsgInfoUChar : public Message
{
public:
	TMsgInfoUChar(const unsigned char& c):Message(TM_INFO_UCHAR, sizeof(TMsgInfoUChar)),m_uchar(c){}
	unsigned char m_uchar;
};

class TMsgInfoChar : public Message
{
public:
	TMsgInfoChar(const char& c):Message(TM_INFO_CHAR, sizeof(TMsgInfoChar)),m_char(c){}
	char m_char;
};

/*
class TMsgTierSizeChanged : public Message//notification
{
public:
	TMsgTierSizeChanged(unsigned int oldTierSize, unsigned int newTierSize):Message(TM_TIER_SIZE_CHANGED, sizeof(TMsgTierSizeChanged)),m_oldTierSize(oldTierSize),m_newTierSize(newTierSize){}
	unsigned int m_oldTierSize;
	unsigned int m_newTierSize;
};
*/
enum TakionOrderAlgorithmId : unsigned int
{
	TOA_SMART_SWIPE = OA_COUNT,
	TOA_SPIDER_SWIPE,
	TOA_TRIGGER,
	TOA_PRE_BORROW,
	TOA_PRE_FIRM_SUBSCRIBE,
	TOA_DUMB_SWIPE,
	TOA_MEGA_SWIPE,
	TOA_POSTPONED,

	TOA_GTC,
	TOA_GTC_ALGO_SPIDER,

	TOA_WAIT_WASH,
	TOA_MULTIPLE_REPLACER,
	TOA_MULTIPLE_MOVER,
//	TOA_MULTIPLE_REPRICER_BY_COMMAND,
#ifndef TAKION_NO_OPTIONS
	TOA_PLUS_OPTION,
#endif
	TOA_COUNT
};

class TD_API AlgorithmSendOrder : public SecurityAlgorithm
{
public:
	void SetUpdated(){m_updateOrdinalOrderAlgorithm = m_invalidateOrdinalOrderAlgorithm;}
//	bool isUpdated(unsigned int updateOrdinal) const{return m_invalidateOrdinalOrderAlgorithm <= m_updateOrdinalOrderAlgorithm;}
	bool isUpdated() const{return m_invalidateOrdinalOrderAlgorithm <= m_updateOrdinalOrderAlgorithm;}
	unsigned int GetInvalidateOrdinalOrderAlgorithm() const{return m_invalidateOrdinalOrderAlgorithm;}
	unsigned int GetUpdateOrdinalOrderAlgorithm() const{return m_updateOrdinalOrderAlgorithm;}

	virtual void WriteOrderCancelToMainThread(bool deleteUntradedPosition = false) override;
	void DoSendOrder(unsigned int orderSize, bool finalOrder);
	void DoSendOrder(unsigned int orderSize);

	void WriteUpdateMessageToMainThread();
//	virtual void WriteOrderUpdateMessageToMainThread(unsigned int pendingShares, bool killed, bool rejected, unsigned char flags, unsigned char orderState) override;//OrderUpdateFlags; 1 - OUF_CANCEL_ACKNOWLEDGED, 2 - OUF_EXECUTION_LOADED:loaded order updated with an execution
	virtual void WriteOrderUpdateMessageToMainThread(unsigned int pendingShares, bool rejected, unsigned char flags, unsigned char orderState) const override;//OrderUpdateFlags; 1 - OUF_CANCEL_ACKNOWLEDGED, 2 - OUF_EXECUTION_LOADED:loaded order updated with an execution

	virtual char* toString(char* buf) const override;
	virtual unsigned short GetAlgorithmSize() const override;
	virtual bool isQuoteOrder() const override{return !isBorrow() && m_postponed;}
	const bool& isPreBorrow() const{return m_preBorrow;}
//	void SetPreBorrow(const bool& preBorrow){m_preBorrow = preBorrow;}
//	const Price& GetPreBorrowPrice() const{return m_preBorrowPrice;}//price in cents
//	void SetPreBorrowPrice(const Price& preBorrowPrice){m_preBorrowPrice = preBorrowPrice;}//price in cents
	bool GetBorrowPrice(Price& loanPrice) const;
	virtual bool isMarketOrder() const override
	{
		switch(m_orderType)
		{
			case ORDER_TYPE_MARKET:
			case ORDER_TYPE_STOP:
			return true;

			default:
			return false;
		}
	}
	virtual const char* GetIsoAttachment() const{return nullptr;}
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position) override;
	virtual void EndAlgorithm() override;
	virtual void EndAlgorithmInThread() override;
	static void InsertLiveOrder(OrderSet& orderSet, Order* const& order)
	{
		if(order && !order->isDead())
		{
			orderSet.insert(order);
		}
	}
	virtual void GetAlgoLiveOrders(OrderSet& orderSet) const override
	{
		InsertLiveOrder(orderSet, m_order);
		InsertLiveOrder(orderSet, m_firmSplitOrder);
		InsertLiveOrder(orderSet, m_splitOrder);
	}
	static void InsertOrder(OrderSet& orderSet, Order* const& order)
	{
		if(order)
		{
			orderSet.insert(order);
		}
	}
	virtual void GetAlgoOrders(OrderSet& orderSet) const override
	{
		InsertOrder(orderSet, m_order);
		InsertOrder(orderSet, m_firmSplitOrder);
		InsertOrder(orderSet, m_splitOrder);
	}
/*
	virtual const Order* GetAlgoSentOrder() const override{return m_order;}
	virtual const Order* GetAlgoFirmSplitOrder() const override{return m_firmSplitOrder;}
	virtual const Order* GetAlgoSplitOrder() const override{return m_splitOrder;}
*/
protected:
	AlgorithmSendOrder(const Position* position,
		bool postponed,
		unsigned int timeToActivate,
		unsigned int orderTimeToActivate,
		unsigned int gtcDateCreated,
		unsigned int gtcTimeCreated,
		TraderIdType traderId,
		unsigned int sendId,
		unsigned int ocoId,
		unsigned int clientId,
		unsigned int clientIdBeingReplaced,
//		unsigned int clientIdOriginal,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,
		const unsigned __int64& destinationId,
		unsigned int destinationName,

		char side,
#ifdef FIRM_VALUES
		char firmSide,
#endif

		unsigned char repriceFlags,
		unsigned char orderType,
		unsigned short userOrderType,//usually should be 0
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr
		const char* commandName,//usually should be nullptr

		unsigned int maxPositionSize,

		const Price& limitPrice,

		const Price& discretionaryPrice,

		unsigned char stopOrderType,
		unsigned char stopOrderBase,
		const Price& stopPrice,

		const Price& level1Price,
		const Price& level1SameSidePrice,
		const Price& lastPrintPrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

//		bool proactive,
		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,
		unsigned int mnemonic,
		bool dma,
		bool syntheticIgnoreFinra,
		bool syntheticWaitNext,
		bool imbalanceOnly,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		bool borrow,
		unsigned char borrowConfirmMask,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT, OOP_SHORT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool openOnly,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		unsigned char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,
		unsigned int extensionId,
		const unsigned __int64& userId,
		bool useSecurityNotification);
	AlgorithmSendOrder(const char*& fromString, bool useSecurityNotification);
	void DoWriteCancel(unsigned char errorCode, const Money& moneyValue, const Money& moneyConstraint, unsigned int uintValue, unsigned int uintConstraint);//from account thread
	void CancelAndReportErrorInMainThread(unsigned char errorCode, const Money& moneyValue, const Money& moneyConstraint, unsigned int uintValue, unsigned int uintConstraint);//from main thread
	virtual void Notify(const Message* message, const Observable* from, const Message* info = nullptr) override;
	virtual void NullifySecurity();
	virtual void OnMyOrderDead(const Order* order){}

	unsigned int m_maxPositionSize;

	bool m_blockAggressiveOrders;
//	bool m_preBorrow;
//	Price m_preBorrowPrice;
	void InitOrders();
	void NullifyOrders();
	Order* m_order;
	Order* m_firmSplitOrder;
	Order* m_splitOrder;
	mutable unsigned int m_invalidateOrdinalOrderAlgorithm;
	unsigned int m_updateOrdinalOrderAlgorithm;
	unsigned int m_clientIdBeingReplaced;
	unsigned int m_orderTimeToActivate;
	bool m_algoCancelSentToMainThread;
};

class TD_API AlgorithmPostponed : public AlgorithmSendOrder
{
public:
	AlgorithmPostponed(const Position* position,
		unsigned int timeToActivate,
		unsigned int gtcDateCreated,
		unsigned int gtcTimeCreated,
		TraderIdType traderId,
		unsigned int sendId,
		unsigned int ocoId,//0 - none; ocoId to be used in the generated order(s)
		unsigned int clientId,
		unsigned int clientIdBeingReplaced,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,
		const unsigned __int64& destinationId,
		unsigned int destinationName,

		char side,
/*
#ifdef FIRM_VALUES
		char firmSide,
#endif
*/
		unsigned char repriceFlags,
		unsigned char orderType,

		unsigned short userOrderType,
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr
		const char* commandName,//usually should be nullptr

		unsigned int maxPositionSize,

		const Price& limitPrice,
		
		const Price& discretionaryPrice,
		unsigned char stopOrderType,
		unsigned char stopOrderBase,
		const Price& stopPrice,
		
		const Price& level1Price,
		const Price& level1SameSidePrice,
		const Price& lastPrintPrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

//		bool proactive,
		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,
		unsigned int mnemonic,
		bool dma,
		bool syntheticIgnoreFinra,
		bool syntheticWaitNext,
		bool imbalanceOnly,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		bool borrow,
		unsigned char borrowConfirmMask,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool openOnly,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,// = 0,
		unsigned int extensionId,
		const unsigned __int64& userId);
//		const char* isoAttachment);
//	AlgorithmPostponed(const AlgorithmPostponed& other);
	AlgorithmPostponed(const char*& fromString);
//	virtual ~AlgorithmPostponed();
//	AlgorithmPostponed& operator=(const AlgorithmPostponed& other);
//	virtual char* toString(char* buf) const;
//	virtual unsigned short GetAlgorithmSize() const;
//	virtual const char* GetIsoAttachment() const override{return m_isoAttachment;}
	virtual OrderAlgorithm* CloneAlgorithm() const override;
	virtual unsigned int GetAlgorithmId() const override{return TOA_POSTPONED;}
	virtual bool isOrderVariation() const override{return true;}
	virtual const char* GetAlgorithmName() const override{return "Post";}
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position) override;
	virtual void EndAlgorithm() override;
	virtual void EndAlgorithmInThread() override;
	virtual bool isNotifyCancel() const override{return false;}
	DECLARE_NED_NEW
	virtual bool CanBeWashOrder() const override{return false;}
	virtual void InThreadUpdate(unsigned short code, unsigned short eventCode) override;
	virtual bool CanBeMadeGtc() const override{return Order::CanBeMadeGtc();}
	virtual bool isGtc() const override{return Order::isGtc();}
protected:
//	virtual bool DoMakeGtc(bool gtc);
//	virtual void Notify(const Message* message, const Observable* from, const Message* info = nullptr);
//	virtual void DoSecurityUpdate();
	void DoSendOrder();
};

class TD_API AlgorithmGtc : public AlgorithmSendOrder
{
public:
//	virtual ~AlgorithmGtc();
//	AlgorithmGtc& operator=(const AlgorithmGtc& other);
	virtual char* toString(char* buf) const override;
	virtual unsigned short GetAlgorithmSize() const override;
//	virtual const char* GetIsoAttachment() const override{return m_isoAttachment;}
//	virtual OrderAlgorithm* CloneAlgorithm() const override;
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position) override;
	virtual void EndAlgorithm() override;
	virtual void EndAlgorithmInThread() override;
	virtual bool isNotifyCancel() const override{return false;}
//	virtual bool CanBeMadeGtc() const{return false;}
	virtual bool isGtc() const override{return true;}
	virtual bool CanBeFired() const override;
	virtual void Fire() override;//enum TifType
	DECLARE_NED_NEW
	virtual bool CanBeWashOrder() const override{return false;}
	virtual void InThreadUpdate(unsigned short code, unsigned short eventCode) override;
	virtual unsigned int GetGtcAlgoId() const override{return m_gtcAlgoId;}
	virtual bool isWaiting() const override{return true;}
	virtual bool isAlgorithmToWait() const override{return true;}
	bool isPreBorrowDone() const;
	virtual bool CanLimitPriceBeZero() const{return false;}
	virtual bool CanBeReplaced() const override{return m_postponed;}
	virtual bool CanBeRePriced() const override{return m_commandName && *m_commandName && m_postponed;}
	virtual unsigned char ReplacePriceAndSize(unsigned int* sendId,//output parameter; can be nullptr
		bool replaceNative,
		bool marketOrder,
		const SignedPrice& replacePriceOffset,
		bool replacePriceOffsetPercent,
		int replaceSizeOffset,
		bool replaceSizeOffsetPercent,
		bool preBorrow,
		const Price& preBorrowPrice,
		const unsigned __int64& userId,
		unsigned char displaySizeMode,//0 - size fraction, 1 - round lot, 2 - no change
		unsigned int displaySize,
		unsigned int displaySizeFraction,
		unsigned int remainingSize,
		bool swapLimitStop = false) override;
	virtual unsigned char ReplaceAbsolutePrice(unsigned int* sendId,//output parameter; can be nullptr
		const Security* security,
		bool replaceNative,
		const Price& limitPrice,
		const Price& stopPrice,
		Price& l1Bid,
		Price& l1Ask,
		Price& lastPrice,
		const unsigned __int64& userId) override;
	virtual bool CanBeOco() const override{return true;}
protected:
	AlgorithmGtc(const Position* position,
		bool postponed,
		bool initialized,
		unsigned int timeToActivate,
		unsigned int gtcAlgoId,
		unsigned int gtcDateCreated,
		unsigned int gtcTimeCreated,
		TraderIdType traderId,
		unsigned int sendId,
		unsigned int ocoId,//0 - none; ocoId to be used in the generated order(s)
		unsigned int clientId,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,
//		unsigned int clientIdOriginal,
		const unsigned __int64& destinationId,
		unsigned int destinationName,

		char side,
/*
#ifdef FIRM_VALUES
		char firmSide,
#endif
*/
		unsigned char repriceFlags,
		unsigned char orderType,

		unsigned short userOrderType,
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr
		const char* commandName,//usually should be nullptr

		unsigned int maxPositionSize,

		const Price& limitPrice,
		
		const Price& discretionaryPrice,
		unsigned char stopOrderType,
		unsigned char stopOrderBase,
		const Price& stopPrice,
		
		const Price& level1Price,
		const Price& level1SameSidePrice,
		const Price& lastPrintPrice,

		unsigned int quantity,
		unsigned int pendingQuantity,
		unsigned int filledQuantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

//		bool proactive,
		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,
		unsigned int mnemonic,
		bool dma,
		bool syntheticIgnoreFinra,
		bool syntheticWaitNext,
		bool imbalanceOnly,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		bool borrow,
		unsigned char borrowConfirmMask,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool openOnly,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,// = 0,
		unsigned int extensionId,
		const unsigned __int64& userId);
//		const char* isoAttachment);
//	AlgorithmGtc(const AlgorithmGtc& other);
	AlgorithmGtc(const char*& fromString);

	virtual bool DoMakeGtc(bool gtc) override;
	virtual void Notify(const Message* message, const Observable* from, const Message* info = nullptr) override;
	virtual bool PreProcessSecurityNotification(const Message* message, const Message* info) override;//in thread
//	virtual void DoSecurityUpdate();
	void StockRefreshed();
	void AttemptSendingOrder();
	void DoAttemptSendingOrder();

	void SendOrder();
	virtual void DoSendOrder() = 0;

	void ProcessPreBorrowOrder();
	void ProcessGtcOrder();
	void ProcessGtcSplitOrder();
	void ProcessGtcFirmSplitOrder();

	void FireOrder()
	{
		if(m_pendingQuantity)DoFireOrder();
	}

	virtual void DoFireOrder() = 0;

	virtual void GtcAlgoReplaced() = 0;

	bool SendBorrow();

	void PreBorrowDone();

	Order* m_preBorrowOrder;
//	Order* m_order;

	unsigned int m_sizeToBorrow;
	unsigned int m_sizeBorrowed;

	bool m_borrowFailed;
	bool m_stockLoaded;
	bool m_initialized;

	unsigned int m_gtcAlgoId;
};

class TD_API AlgorithmGtcOrder : public AlgorithmGtc
{
public:
	AlgorithmGtcOrder(const Position* position,
		bool postponed,
		bool initialized,
		unsigned int timeToActivate,
		unsigned int gtcAlgoId,
		unsigned int gtcDateCreated,
		unsigned int gtcTimeCreated,
		TraderIdType traderId,
		unsigned int sendId,
		unsigned int ocoId,//0 - none; ocoId to be used in the generated order(s)
		unsigned int clientId,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,
//		unsigned int clientIdOriginal,
		const unsigned __int64& destinationId,
		unsigned int destinationName,

		char side,
/*
#ifdef FIRM_VALUES
		char firmSide,
#endif
*/
		unsigned char repriceFlags,
		unsigned char orderType,

		unsigned short userOrderType,
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr
		const char* commandName,//usually should be nullptr

		unsigned int maxPositionSize,

		const Price& limitPrice,
		
		const Price& discretionaryPrice,
		unsigned char stopOrderType,
		unsigned char stopOrderBase,
		const Price& stopPrice,
		
		const Price& level1Price,
		const Price& level1SameSidePrice,
		const Price& lastPrintPrice,

		unsigned int quantity,
		unsigned int pendingQuantity,
		unsigned int filledQuantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

//		bool proactive,
		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,
		unsigned int mnemonic,
		bool dma,
		bool syntheticIgnoreFinra,
		bool syntheticWaitNext,
		bool imbalanceOnly,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		bool borrow,
		unsigned char borrowConfirmMask,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool openOnly,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,// = 0,
		unsigned int extensionId,
		const unsigned __int64& userId);
//		const char* isoAttachment);
//	AlgorithmGtc(const AlgorithmGtc& other);
	AlgorithmGtcOrder(const char*& fromString);
	virtual OrderAlgorithm* CloneAlgorithm() const override;
	virtual unsigned int GetAlgorithmId() const override{return TOA_GTC;}
	virtual const char* GetAlgorithmName() const override{return "GTC";}
protected:
	virtual void DoFireOrder() override;
	virtual void DoSendOrder() override;
	virtual void GtcAlgoReplaced() override;
};

class TD_API AlgorithmGtcAlgoSpider : public AlgorithmGtc
{
public:
	typedef std::set<unsigned int> UIntSet;
	AlgorithmGtcAlgoSpider(const Position* position,
		bool postponed,
		bool initialized,
		unsigned int timeToActivate,
		unsigned int gtcAlgoId,
		unsigned int gtcDateCreated,
		unsigned int gtcTimeCreated,
		TraderIdType traderId,
		unsigned int sendId,
		unsigned int ocoId,//0 - none; ocoId to be used in the generated order(s)
		unsigned int clientId,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,

//		const unsigned __int64& destinationId,
//		unsigned int destinationName,

		char side,
/*
#ifdef FIRM_VALUES
		char firmSide,
#endif
*/
		unsigned char repriceFlags,

//		unsigned char orderType,
		unsigned short userOrderType,
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr
		const char* commandName,//usually should be nullptr

		unsigned int maxPositionSize,

		const Price& limitPrice,
		
//		const Price& discretionaryPrice,
//		unsigned char stopOrderType,
//		unsigned char stopOrderBase,
//		const Price& stopPrice,
		
//		const Price& level1Price,
//		const Price& level1SameSidePrice,
//		const Price& lastPrintPrice,

		unsigned int quantity,
		unsigned int pendingQuantity,
		unsigned int filledQuantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

		bool proactive,

		bool hideSlowQuotes,
		unsigned int hideClosedQuotes,//ClosedQuotesSourceFlags
		bool excludeDestinations,
		const UIntSet& destinationSet,
		const UIntSet& filterSet,

/*
		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,
		unsigned int mnemonic,
		bool dma,
*/
//		bool imbalanceOnly,
//		bool iso,//!proactive
//		bool aggressive,
		unsigned int roundLot,
//		bool borrow,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool openOnly,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		bool skimOddLot,
		bool postRemainder,
		const unsigned __int64& postDestinationId,
		unsigned int postDestinationName,
		unsigned int postRoutingName,
		unsigned short postRoutingId,
		unsigned short postRoutingSubType,
		unsigned int postMnemonic,
		unsigned char postTifType,
		unsigned int postTif,

		unsigned char postPegType,
		const SignedPrice& postPegOffset,
		unsigned int postDisplayQuantity,
		const SignedPrice& postPriceOffset,
		bool postPriceOffsetPercent,

//		char tifType,
//		unsigned int tifMillisecond,
		unsigned int parentId,// = 0,
		unsigned int extensionId,
		const unsigned __int64& userId);
//	AlgorithmGtcAlgoSpider(const AlgorithmGtcAlgoSpider& other);
	AlgorithmGtcAlgoSpider(const char*& fromString);
	virtual OrderAlgorithm* CloneAlgorithm() const override;
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position) override;
	virtual void EndAlgorithm() override;
	virtual void EndAlgorithmInThread() override;
	virtual unsigned int GetAlgorithmId() const override{return TOA_GTC_ALGO_SPIDER;}
	virtual const char* GetAlgorithmName() const override{return "GTCspdr";}
	virtual char* toString(char* buf) const override;
	virtual unsigned short GetAlgorithmSize() const override;
	const bool& isHideSlowQuotes() const{return m_hideSlowQuotes;}
	const unsigned int& GetHideClosedQuotes() const{return m_hideClosedQuotes;}
	const bool& isExcludeDestinations() const{return m_excludeDestinations;}

	const bool& isSkimOddLot() const{return m_skimOddLot;}
	const bool& isPostRemainder() const{return m_postRemainder;}
	const unsigned __int64& GetPostDestinationId() const{return m_postDestinationId;}
	const unsigned int& GetPostDestinationName() const{return m_postDestinationName;}
	const unsigned int& GetPostRoutingName() const{return m_postRoutingName;}
	const unsigned short& GetPostRoutingId() const{return m_postRoutingId;}
	const unsigned short& GetPostRoutingSubType() const{return m_postRoutingSubType;}
	const unsigned int& GetPostMnemonic() const{return m_postMnemonic;}
	const unsigned char& GetPostTifType() const{return m_postTifType;}
	const unsigned int& GetPostTif() const{return m_postTif;}

	const unsigned char& GetPostPegType() const{return m_postPegType;}
	const SignedPrice& GetPostPegOffset() const{return m_postPegOffset;}
	const unsigned int& GetPostDisplayQuantity() const{return m_postDisplayQuantity;}
	const SignedPrice& GetPostPriceOffset() const{return m_postPriceOffset;}
	const bool& isPostPriceOffsetPercent() const{return m_postPriceOffsetPercent;}

	const UIntSet& GetDestinationSet() const{return m_destinationSet;}
	const UIntSet& GetFilterSet() const{return m_filterSet;}
	virtual bool CanLimitPriceBeZero() const{return true;}
protected:
	virtual void DoSendOrder() override;
	virtual void DoFireOrder() override;
	virtual void GtcAlgoReplaced() override;
	bool m_hideSlowQuotes;
	unsigned int m_hideClosedQuotes;//ClosedQuotesSourceFlags
	bool m_excludeDestinations;
//SpreadCatcher
	bool m_skimOddLot;
	bool m_postRemainder;
	unsigned __int64 m_postDestinationId;
	unsigned int m_postDestinationName;
	unsigned int m_postRoutingName;
	unsigned short m_postRoutingId;
	unsigned short m_postRoutingSubType;
	unsigned int m_postMnemonic;
	unsigned char m_postTifType;
	unsigned int m_postTif;

	unsigned char m_postPegType;
	SignedPrice m_postPegOffset;
	unsigned int m_postDisplayQuantity;
	SignedPrice m_postPriceOffset;
	bool m_postPriceOffsetPercent;
////
	bool m_spiderSent;

	UIntSet m_destinationSet;
	UIntSet m_filterSet;
};

class TD_API TakionAlgorithm : public AlgorithmSendOrder
{
public:
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position);
	virtual void EndAlgorithm();
	virtual void EndAlgorithmInThread();
	virtual char* toString(char* buf) const;
	virtual unsigned short GetAlgorithmSize() const;
//	virtual void WriteOrderCancelToMainThread(bool deleteUntradedPosition = false) override;

	const unsigned int& GetSizeToBorrow() const{return m_sizeToBorrow;}
	void SetSizeToBorrow(const unsigned int& size){m_sizeToBorrow = size;}
	virtual bool isPreBorrowDone() const;
protected:
	TakionAlgorithm(const Position* position,
		bool postponed,
		unsigned int timeToActivate,
		unsigned int orderTimeToActivate,
		unsigned int gtcDateCreated,
		unsigned int gtcTimeCreated,
		TraderIdType traderId,
		unsigned int sendId,
		unsigned int ocoId,
		unsigned int clientId,
		unsigned int clientIdBeingReplaced,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,
		const unsigned __int64& destinationId,
		unsigned int destinationName,

		char side,
#ifdef FIRM_VALUES
		char firmSide,
#endif

		unsigned char repriceFlags,
		unsigned char orderType,

		unsigned short userOrderType,
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr
		const char* commandName,//usually should be nullptr

		unsigned int maxPositionSize,

		const Price& limitPrice,

		const Price& discretionaryPrice,

		unsigned char stopOrderType,
		unsigned char stopOrderBase,
		const Price& stopPrice,

		const Price& level1Price,
		const Price& level1SameSidePrice,
		const Price& lastPrintPrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,
		unsigned int mnemonic,

		bool syntheticIgnoreFinra,
		bool syntheticWaitNext,
		bool imbalanceOnly,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,//XX
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool openonly,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,

		unsigned char pegType,
		const SignedPrice& pegOffset,

		char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,// = 0,
		unsigned int extensionId,
		const unsigned __int64& userId,// = 0);
		bool useSecurityNotification,//XX
		unsigned int preBorrowSize,
		bool observePosition = true);

	TakionAlgorithm(const char*& fromString, bool useSecurityNotification);
//	virtual void DoSendOrder(){}

//	bool GetBorrowPrice(Price& loanPrice) const;
//	void DoWriteCancel(unsigned char errorCode, const Money& moneyValue, const Money& moneyConstraint, unsigned int uintValue, unsigned int uintConstraint);//from account thread
//	void CancelAndReportErrorInMainThread(unsigned char errorCode, const Money& moneyValue, const Money& moneyConstraint, unsigned int uintValue, unsigned int uintConstraint);//from main thread

	virtual void Notify(const Message* message, const Observable* from, const Message* info = nullptr);

	bool SendBorrow();

	void ProcessPreBorrowOrder();

	virtual void PreBorrowDone(){}

	virtual void AllOrdersCanceled() override;

//	bool m_blockAggressiveOrders;
	Order* m_preBorrowOrder;
//	bool m_preBorrow;
//	Price m_preBorrowPrice;
	unsigned int m_sizeToBorrow;
	unsigned int m_sizeBorrowed;
	bool m_borrowFailed;

	bool m_observePosition;
};

class TD_API AlgorithmPreBorrow : public TakionAlgorithm
{
public:
	AlgorithmPreBorrow(const Position* position,
//		bool postponed,
		unsigned int orderTimeToActivate,//for the order to be sent, not for algo
		TraderIdType traderId,
		unsigned int sendId,
		unsigned int ocoId,//0 - none; ocoId to be used in the generated order(s)
		unsigned int clientId,
		unsigned int clientIdBeingReplaced,
//		unsigned int clientIdOriginal,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,
		const unsigned __int64& destinationId,
		unsigned int destinationName,

		char side,
#ifdef FIRM_VALUES
		char firmSide,
#endif

		unsigned char repriceFlags,
		unsigned char orderType,

		unsigned short userOrderType,
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr
		const char* commandName,//usually should be nullptr

		unsigned int maxPositionSize,

		const Price& limitPrice,
		
		const Price& discretionaryPrice,
		unsigned char stopOrderType,
		unsigned char stopOrderBase,
		const Price& stopPrice,
		
		const Price& level1Price,
		const Price& level1SameSidePrice,
		const Price& lastPrintPrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

//		bool proactive,
		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,
		unsigned int mnemonic,
		bool syntheticIgnoreFinra,
		bool syntheticWaitNext,
		bool imbalanceOnly,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool openOnly,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,// = 0,
		unsigned int extensionId,
		const unsigned __int64& userId,
		unsigned int preBorrowSize,
		const char* isoAttachment);// = 0);
	AlgorithmPreBorrow(const AlgorithmPreBorrow& other);
	AlgorithmPreBorrow(const char*& fromString);
	virtual ~AlgorithmPreBorrow();
	AlgorithmPreBorrow& operator=(const AlgorithmPreBorrow& other);
	virtual bool isAlgorithmToWait() const override{return true;}
	virtual OrderAlgorithm* CloneAlgorithm() const override;
	virtual unsigned int GetAlgorithmId() const override{return TOA_PRE_BORROW;}
	virtual const char* GetAlgorithmName() const override{return "PreBorrow";}
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position) override;
	virtual void EndAlgorithm() override;
	virtual void EndAlgorithmInThread() override;
	virtual bool CanShowInPosMan() const override{return false;}
	DECLARE_NED_NEW
	virtual bool CanBeWashOrder() const override{return false;}
	virtual char* toString(char* buf) const override;
	virtual unsigned short GetAlgorithmSize() const override;
//	virtual void WriteOrderCancelToMainThread();
	virtual const char* GetIsoAttachment() const override{return m_isoAttachment;}
//	const unsigned short& GetIsoAttachmentLength() const{return m_isoAttachmentLength;}
//	const unsigned int& GetOco() const{return m_oco;}
	virtual void InThreadUpdate(unsigned short code, unsigned short eventCode) override;
	virtual bool isPreBorrowDone() const override;
protected:
	virtual void Notify(const Message* message, const Observable* from, const Message* info = nullptr) override;
	void DoSendOrder();
	virtual void PreBorrowDone() override;
//	virtual void StockRefreshed override();
/*
	Order* m_preBorrowOrder;
	Price m_preBorrowPrice;
	unsigned int m_sizeToBorrow;
	unsigned int m_sizeBorrowed;
*/
	char* m_isoAttachment;
//	unsigned short m_isoAttachmentLength;
//	unsigned int m_oco;
//	bool m_preborrowDone;
};

class TD_API TakionOrderAlgorithm : public TakionAlgorithm
{
public:
//	virtual void WriteOrderCancelToMainThread();
	unsigned int GetLastExecutionMillisecond() const{return m_lastExecutionMillisecond;}
	virtual char* toString(char* buf) const;
	virtual unsigned short GetAlgorithmSize() const;
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position);
	virtual void EndAlgorithm();
	virtual void EndAlgorithmInThread();
//	virtual unsigned int GetTotalSize() const{return m_quantity;}
protected:
	TakionOrderAlgorithm(const Position* position,
#ifndef TAKION_NO_OPTIONS
		unsigned char accountSecurityType,
#endif
		bool postponed,
		unsigned int timeToActivate,

		unsigned int gtcDateCreated,
		unsigned int gtcTimeCreated,

		TraderIdType traderId,
		unsigned int sendId,
//		unsigned int clientId,
		unsigned int ocoId,
		unsigned int clientIdBeingReplaced,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,
		const unsigned __int64& destinationId,
		unsigned int destinationName,

		char side,
#ifdef FIRM_VALUES
		char firmSide,
#endif

		unsigned char repriceFlags,
		unsigned char orderType,

		unsigned short userOrderType,
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr
		const char* commandName,//usually should be nullptr

		unsigned int maxPositionSize,

		const Price& limitPrice,

		const Price& discretionaryPrice,

		unsigned char stopOrderType,
		unsigned char stopOrderBase,
		const Price& stopPrice,

		const Price& level1Price,
		const Price& level1SameSidePrice,
		const Price& lastPrintPrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,
		unsigned int mnemonic,

//		bool proactive,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool openOnly,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,

		unsigned char pegType,
		const SignedPrice& pegOffset,

		char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,// = 0,
		unsigned int extensionId,
		const unsigned __int64& userId,// = 0);
		bool useSecurityNotification,
		unsigned int preBorrowSize);

	TakionOrderAlgorithm(const char*& fromString, bool useSecurityNotification);
	virtual void NullifySecurity();
	virtual void StockRefreshed();
	bool OrderExecuted(const Order* order, unsigned int executionFilledQuantity, const Price& price, unsigned int lastExecutionMillisecond);
	unsigned int m_lastExecutionMillisecond;
/*
	bool m_preBorrow;
	Price m_preBorrowPrice;
	Order* m_preBorrowOrder;
	unsigned int m_sizeToBorrow;
	unsigned int m_sizeBorrowed;
*/
	unsigned int m_realQuantity;
	bool m_stockLoaded;

//	virtual void Notify(const Message* message, const Observable* from, const Message* info = nullptr);
	virtual bool PreProcessSecurityNotification(const Message* message, const Message* info);//in thread

//	void DoSendOrder();
	virtual void PreBorrowDone() override;
};

class TD_API AlgorithmSwipe : public TakionOrderAlgorithm
{
public:
	typedef std::set<unsigned int> UIntSet;
#if (_MSC_VER > 1600)
	typedef std::unordered_map<TradedQuote, unsigned int, TakionHashValue<TradedQuote> > TradedQuoteMap;
	typedef std::unordered_set<unsigned int> MmidSet;
	typedef std::unordered_map<Order*, TradedQuote> OrderTradedQuoteMap;
#else
	typedef std::hash_map<TradedQuote, unsigned int> TradedQuoteMap;
	typedef std::hash_set<unsigned int> MmidSet;
	typedef std::hash_map<Order*, TradedQuote> OrderTradedQuoteMap;
#endif
	virtual ~AlgorithmSwipe();
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position) override;
	virtual void EndAlgorithm() override;
	virtual void EndAlgorithmInThread() override;
	unsigned int CalculateFloatingLimitPrice() const;
	virtual char* toString(char* buf) const override;
	virtual unsigned short GetAlgorithmSize() const override;
	virtual bool SecurityMustBeLoaded() const override{return true;}
	virtual bool isQuoteOrder() const override{return m_useSecurityNotification || m_postponed;}
	virtual void InThreadUpdate(unsigned short code, unsigned short eventCode) override;
	virtual unsigned char GetAlgorithmMask() const override{return 1 << ALGORITHMMASK_LIMIT;}
	OrderTradedQuoteMap::const_iterator FindLiveOrder(const Observable* from) const;
	OrderSet::const_iterator FindSpreadCatcherOrder(const Observable* from) const;
	const bool& isHideSlowQuotes() const{return m_hideSlowQuotes;}
	const unsigned int& GetHideClosedQuotes() const{return m_hideClosedQuotes;}
	const bool& isExcludeDestinations() const{return m_excludeDestinations;}
	const UIntSet& GetDestinationSet() const{return m_destinationSet;}
	const UIntSet& GetFilterSet() const{return m_filterSet;}
	virtual bool CanBeReplaced() const override{return m_useSecurityNotification;}
	virtual bool CanBeOco() const override{return true;}

	const bool& isSkimOddLot() const{return m_skimOddLot;}
	const bool& isPostRemainder() const{return m_postRemainder;}
	const unsigned __int64& GetPostDestinationId() const{return m_postDestinationId;}
	const unsigned int& GetPostDestinationName() const{return m_postDestinationName;}
	const unsigned int& GetPostRoutingName() const{return m_postRoutingName;}
	const unsigned short& GetPostRoutingId() const{return m_postRoutingId;}
	const unsigned short& GetPostRoutingSubType() const{return m_postRoutingSubType;}
	const unsigned int& GetPostMnemonic() const{return m_postMnemonic;}
	const unsigned char& GetPostTifType() const{return m_postTifType;}
	const unsigned int& GetPostTif() const{return m_postTif;}

	const unsigned char& GetPostPegType() const{return m_postPegType;}
	const SignedPrice& GetPostPegOffset() const{return m_postPegOffset;}
	const unsigned int& GetPostDisplayQuantity() const{return m_postDisplayQuantity;}
	const SignedPrice& GetPostPriceOffset() const{return m_postPriceOffset;}
	const bool& isPostPriceOffsetPercent() const{return m_postPriceOffsetPercent;}

protected:
	AlgorithmSwipe(const Position* position,
#ifndef TAKION_NO_OPTIONS
		unsigned char accountSecurityType,
#endif
		bool postponed,
		unsigned int timeToActivate,

		unsigned int gtcDateCreated,
		unsigned int gtcTimeCreated,

		TraderIdType traderId,
		unsigned int sendId,
		unsigned int ocoId,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,
		unsigned int destinationName,

		char side,

		unsigned char repriceFlags,
		unsigned short userOrderType,
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr
		const char* commandName,//usually should be nullptr

		const Price& limitPrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

		bool excludeDestinations,
		const UIntSet& destinationSet,
		const UIntSet& filterSet,

		unsigned short routingId,
		unsigned int routingName,

		unsigned int roundLot,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool openOnly,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,

		unsigned char pegType,
		const SignedPrice& pegOffset,

		bool hideSlowQuotes,
		unsigned int hideClosedQuotes,

		char tifType,
		unsigned int tifMillisecond,

		bool skimOddLot,
		bool postRemainder,
		const unsigned __int64& postDestinationId,
		unsigned int postDestinationName,
		unsigned int postRoutingName,
		unsigned short postRoutingId,
		unsigned short postRoutingSubType,
		unsigned int postMnemonic,
		unsigned char postTifType,
		unsigned int postTif,

		unsigned char postPegType,
		const SignedPrice& postPegOffset,
		unsigned int postDisplayQuantity,
		const SignedPrice& postPriceOffset,
		bool postPriceOffsetPercent,

		bool postRemainderOnIsoViolation,

		unsigned int parentId,// = 0,
		unsigned int extensionId,
		const unsigned __int64& userId,
//		bool spider,
		bool useSecurityNotification,
		unsigned int preBorrowSize);// = 0);

	AlgorithmSwipe(const char*& fromString, bool spider);
	AlgorithmSwipe(const AlgorithmSwipe& other);

	void UpdateStockOpen();

	virtual void UpdateMarketDataEntitlements() override;//Called only from account thread
	virtual void StockRefreshed() override;
//	void DoWriteCancel(unsigned char errorCode, const Money& moneyValue, const Money& moneyConstraint, unsigned int uintValue, unsigned int uintConstraint);
	virtual void Notify(const Message* message, const Observable* from, const Message* info = nullptr) override;
//	bool CanGrabQuote(const MsgQuote& quote, bool bidQuote) const;
	bool CanGrabQuote(unsigned char source, unsigned char bookId, const Price& price, unsigned int mmid, unsigned char quoteCondition, bool bidQuote) const;
	virtual bool ShouldSecurityNotify(const Message* message, const Message* info = nullptr) const override;
	virtual void DoSecurityUpdate() override;
	virtual bool PreProcessSecurityNotification(const Message* message, const Message* info = nullptr) override;
	void InitializeFloatingLimitPrice();
	virtual void StartSwiping();
	virtual void Swipe(){}
	virtual void PreBorrowDone() override;
	TakionIterator* m_quoteIterator;
	bool m_preborrowDone;
	bool m_bypassedQuote;
	bool m_nasdaq;
	bool m_hideSlowQuotes;
	unsigned int m_hideClosedQuotes;//ClosedQuotesSourceFlags
//	bool m_blockAggressiveOrders;
	bool m_excludeDestinations;
	UIntSet m_destinationSet;
	UIntSet m_filterSet;
	TradedQuoteMap m_tradedQuotes;
	TradedQuoteMap m_currentOrderQuotes;
	MmidSet m_rejectedMmids;

	bool m_stockOpen;

	bool m_skimOddLot;
	bool m_postRemainder;

	unsigned __int64 m_postDestinationId;
	unsigned int m_postDestinationName;
	unsigned int m_postRoutingName;
	unsigned short m_postRoutingId;
	unsigned short m_postRoutingSubType;
	unsigned int m_postMnemonic;
	unsigned char m_postTifType;
	unsigned int m_postTif;

	unsigned char m_postPegType;
	SignedPrice m_postPegOffset;
	unsigned int m_postDisplayQuantity;
	SignedPrice m_postPriceOffset;
	bool m_postPriceOffsetPercent;

	bool m_postRemainderOnIsoViolation;
	unsigned int m_floatingLimitPriceCompact;

	unsigned int CancelLiveOrders() const;
	unsigned int CancelSpreadCatcherOrders() const;
	unsigned int CancelAllLiveOrders() const;

//	Order* m_orderSpreadCatcher;
	bool m_cancelSentSpreadCatcher;
	bool m_noSpreadCatcher;
	Price m_spreadCatcherLimitPrice;
	OrderSet m_ordersSpreadCatcher;
	OrderSet::const_iterator m_ordersSpreadCatcherEnd;

//07/28/2021
//	OrderSet m_liveOrders;
//	OrderSet::const_iterator m_liveOrdersEnd;
	OrderTradedQuoteMap m_liveOrders;
	OrderTradedQuoteMap::const_iterator m_liveOrdersEnd;
private:
	AlgorithmSwipe& operator=(const AlgorithmSwipe& other);
};

class TD_API AlgorithmSmartSwipe : public AlgorithmSwipe//TakionOrderAlgorithm
{
public:
//	typedef std::set<unsigned int> UIntSet;
//	typedef std::hash_map<TradedQuote, unsigned int> TradedQuoteMap;
	AlgorithmSmartSwipe(const Position* position,
#ifndef TAKION_NO_OPTIONS
		unsigned char accountSecurityType,
#endif
		bool postponed,
		unsigned int timeToActivate,
		unsigned int gtcDateCreated,
		unsigned int gtcTimeCreated,

		TraderIdType traderId,
		unsigned int sendId,
		unsigned int ocoId,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,

		char side,

		unsigned char repriceFlags,
		unsigned short userOrderType,
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr
		const char* commandName,//usually should be nullptr

//		unsigned char orderType,
		const Price& limitPrice,
//		const Price& level1Price,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

		bool excludeDestinations,
		const UIntSet& destinationSet,
		const UIntSet& filterSet,

		unsigned short routingId,
		unsigned int routingName,

//		bool proactive,
//		bool iso,
		unsigned int roundLot,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool openOnly,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,

		unsigned char pegType,
		const SignedPrice& pegOffset,

		bool hideSlowQuotes,
		unsigned int hideClosedQuotes,

		char tifType,
		unsigned int tifMillisecond,

		bool skimOddLot,
		bool postRemainder,

		const unsigned __int64& postDestinationId,
		unsigned int postDestinationName,
		unsigned int postRoutingName,
		unsigned short postRoutingId,
		unsigned short postRoutingSubType,
		unsigned int postMnemonic,
		unsigned char postTifType,
		unsigned int postTif,

		unsigned char postPegType,
		const SignedPrice& postPegOffset,
		unsigned int postDisplayQuantity,
		const SignedPrice& postPriceOffset,
		bool postPriceOffsetPercent,

		bool postRemainderOnIsoViolation,

		unsigned int parentId,// = 0,
		unsigned int extensionId,
		const unsigned __int64& userId,
		bool spider,
		unsigned int preBorrowSize);// = 0);
	AlgorithmSmartSwipe(const char*& fromString, bool spider);
//	virtual ~AlgorithmSmartSwipe();
	virtual OrderAlgorithm* CloneAlgorithm() const override;
	virtual const char* GetAlgorithmName() const override{return m_useSecurityNotification ? "Spider" : "SmartSwipe";}
	virtual unsigned int GetAlgorithmMaxTheoreticalQuantity(unsigned int quantity) const override
	{
		return m_useSecurityNotification && m_postRemainder ? quantity << 1 : quantity;//double for spider with SpreadCatcher
	}
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position) override;
	virtual void EndAlgorithm() override;
	virtual void EndAlgorithmInThread() override;
	DECLARE_NED_NEW
//	unsigned int CalculateFloatingLimitPrice() const;
	virtual char* toString(char* buf) const override;
	virtual unsigned short GetAlgorithmSize() const override;
	virtual unsigned int GetAlgorithmId() const override{return m_useSecurityNotification ? TOA_SPIDER_SWIPE : TOA_SMART_SWIPE;}
	virtual bool isGtc() const override{return m_useSecurityNotification && TIF_GTC == m_tifType;}
	virtual bool CanBeMadeGtc() const override{return m_useSecurityNotification && TIF_GTC != m_tifType;}
//	virtual bool CanBeReplaced() const override{return m_useSecurityNotification;}
	virtual bool CanBeRePriced() const override{return m_commandName && *m_commandName && m_useSecurityNotification;}
	virtual unsigned char ReplacePriceAndSize(unsigned int* sendId,//output parameter; can be nullptr
		bool replaceNative,
		bool marketOrder,
		const SignedPrice& replacePriceOffset,
		bool replacePriceOffsetPercent,
		int replaceSizeOffset,
		bool replaceSizeOffsetPercent,
		bool preBorrow,
		const Price& preBorrowPrice,
		const unsigned __int64& userId,
		unsigned char displaySizeMode,//0 - size fraction, 1 - round lot, 2 - no change
		unsigned int displaySize,
		unsigned int displaySizeFraction,
		unsigned int remainingSize,
		bool swapLimitStop = false) override;
	virtual unsigned char ReplaceAbsolutePrice(unsigned int* sendId,//output parameter; can be nullptr
		const Security* security,
		bool replaceNative,
		const Price& limitPrice,
		const Price& stopPrice,
		Price& l1Bid,
		Price& l1Ask,
		Price& lastPrice,
		const unsigned __int64& userId) override;
protected:
	virtual void Swipe() override;

//	virtual void Notify(const Message* message, const Observable* from, const Message* info = nullptr) override;
	bool m_spiderWaitingForQuotes;
};

class TD_API AlgorithmDumbSwipe : public AlgorithmSwipe//TakionOrderAlgorithm
{
public:
	AlgorithmDumbSwipe(const Position* position,
#ifndef TAKION_NO_OPTIONS
		unsigned char accountSecurityType,
#endif
		bool postponed,
		unsigned int timeToActivate,
		TraderIdType traderId,
		unsigned int sendId,
		unsigned int ocoId,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,

		char side,

		unsigned char repriceFlags,
		unsigned short userOrderType,
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr
		const char* commandName,//usually should be nullptr

		const Price& limitPrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

		bool excludeDestinations,
		const UIntSet& destinationSet,
		const UIntSet& filterSet,

		unsigned short routingId,
		unsigned int routingName,

		unsigned int roundLot,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool openOnly,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,

		unsigned char pegType,
		const SignedPrice& pegOffset,

		bool hideSlowQuotes,
		unsigned int hideClosedQuotes,

		char tifType,
		unsigned int tifMillisecond,

		bool skimOddLot,
		bool postRemainder,
		const unsigned __int64& postDestinationId,
		unsigned int postDestinationName,
		unsigned int postRoutingName,
		unsigned short postRoutingId,
		unsigned short postRoutingSubType,
		unsigned int postMnemonic,
		unsigned char postTifType,
		unsigned int postTif,

		unsigned char postPegType,
		const SignedPrice& postPegOffset,
		unsigned int postDisplayQuantity,
		const SignedPrice& postPriceOffset,
		bool postPriceOffsetPercent,

		bool postRemainderOnIsoViolation,

		unsigned int parentId,// = 0,
		unsigned int extensionId,
		const unsigned __int64& userId,
		bool spider,
		unsigned int preBorrowSize);// = 0);
	AlgorithmDumbSwipe(const char*& fromString, bool spider);
	virtual OrderAlgorithm* CloneAlgorithm() const override;
//	virtual const char* GetAlgorithmName() const{return m_useSecurityNotification ? "Spider" : "SmartSwipe";}
	virtual const char* GetAlgorithmName() const override{return m_reiterate ? "DumbSwipeRE" : "DumbSwipe";}
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position) override;
	virtual void EndAlgorithm() override;
	virtual void EndAlgorithmInThread() override;
	DECLARE_NED_NEW
	virtual char* toString(char* buf) const override;
	virtual unsigned short GetAlgorithmSize() const override;
//	virtual unsigned int GetAlgorithmId() const{return m_useSecurityNotification ? TOA_SPIDER_SWIPE : TOA_SMART_SWIPE;}
	virtual unsigned int GetAlgorithmId() const override{return TOA_DUMB_SWIPE;}
	const bool& isReiterate() const{return m_reiterate;}
	void SetReiterate(const bool& reiterate){m_reiterate = reiterate;}
protected:
	virtual void Swipe() override;
	bool m_reiterate;
};

class TD_API AlgorithmMegaSwipe : public AlgorithmSwipe//TakionOrderAlgorithm
{
public:
	AlgorithmMegaSwipe(const Position* position,
#ifndef TAKION_NO_OPTIONS
		unsigned char accountSecurityType,
#endif
		bool postponed,
		unsigned int timeToActivate,
		TraderIdType traderId,
		unsigned int sendId,
		unsigned int ocoId,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,

		char side,

		unsigned char repriceFlags,
		unsigned short userOrderType,
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr
		const char* commandName,//usually should be nullptr

		const Price& limitPrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

		bool excludeDestinations,
		const UIntSet& destinationSet,
		const UIntSet& filterSet,

		unsigned short routingId,
		unsigned int routingName,

		unsigned int roundLot,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool openOnly,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,

		unsigned char pegType,
		const SignedPrice& pegOffset,

		bool hideSlowQuotes,
		unsigned int hideClosedQuotes,

		char tifType,
		unsigned int tifMillisecond,

		bool postRemainder,
		const unsigned __int64& postDestinationId,
		unsigned int postDestinationName,
		unsigned int postRoutingName,
		unsigned short postRoutingId,
		unsigned short postRoutingSubType,
		unsigned int postMnemonic,
		unsigned char postTifType,
		unsigned int postTif,

		unsigned char postPegType,
		const SignedPrice& postPegOffset,
		unsigned int postDisplayQuantity,
		const SignedPrice& postPriceOffset,
		bool postPriceOffsetPercent,

		bool postRemainderOnIsoViolation,

		unsigned int parentId,// = 0,
		unsigned int extensionId,
		const unsigned __int64& userId,
		bool spider,
		unsigned int preBorrowSize);// = 0);
	AlgorithmMegaSwipe(const char*& fromString, bool spider);
	virtual OrderAlgorithm* CloneAlgorithm() const override;
	virtual const char* GetAlgorithmName() const override{return "MegaSwipe";}
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position) override;
	virtual void EndAlgorithm() override;
	virtual void EndAlgorithmInThread() override;
	DECLARE_NED_NEW
	virtual char* toString(char* buf) const override;
	virtual unsigned short GetAlgorithmSize() const override;
	virtual unsigned int GetAlgorithmId() const override{return TOA_MEGA_SWIPE;}
	virtual unsigned int GetAlgorithmQuantity() const override{return m_quantity * m_orderToSendCount;}
protected:
	virtual void Swipe() override;
	unsigned int m_orderToSendCount;
};

#ifndef TAKION_NO_OPTIONS

class TD_API AlgorithmMultipleOptionsBase : public UnderlierAlgorithm//TakionOrderAlgorithm
{
public:
	virtual bool isMarketOrder() const
	{
		switch(m_orderType)
		{
			case ORDER_TYPE_MARKET:
			case ORDER_TYPE_STOP:
			return true;

			default:
			return false;
		}
	}
	virtual bool CanBeWashOrder() const override{return false;}

	virtual char* toString(char* buf) const override;
	virtual unsigned short GetAlgorithmSize() const override;

	virtual const char* GetSymbol() const override{return (const char*)&m_numericSymbol;}
	virtual const unsigned __int64& GetNumericSymbol() const override{return m_numericSymbol;}
	virtual SecurityType GetSecurityType() const override{return ST_OPTION;}
	virtual const unsigned __int64& GetUnderlierNumericSymbol() const override{return m_underlier ? m_underlier->GetNumericSymbol() : uint64Zero;}
	bool isInventoryView() const{return m_inventoryView;}
	virtual void WriteOrderCancelToMainThread(bool deleteUntradedPosition = false) override;
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position) override;
protected:
	AlgorithmMultipleOptionsBase(char side,
		int positionSize,
		unsigned int quantity,
		const Price& orderBasePrice,
		const Price& orderPrice,
		const Price& limitPrice,
		const Price& stopPrice,
		const Price& discretionaryPrice,

		const unsigned __int64& destinationId,
		unsigned int destinationName,

		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,

		unsigned int mnemonic,

		unsigned int sprayCount,
		int spraySizeOffset,
		const SignedPrice& sprayPriceOffset,

		unsigned char repriceFlags,
		unsigned short userOrderType,
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr
		const char* commandName,//usually should be nullptr

		TraderIdType traderId,
		unsigned int sendId,
		unsigned int parentId,// = 0,
		unsigned int ocoId,// = 0,
		unsigned int extensionId,
		const unsigned __int64& userId,

		const unsigned __int64& numericSymbol,
		unsigned int expirationDate,
		unsigned int strikePrice,

		unsigned int optionStrikeCountUp,
		unsigned int optionStrikeCountDown,
		unsigned int optionExpirationCountUp,
		unsigned int optionExpirationCountDown,

		bool call,

		bool sprayPriceOffsetPercent,
		bool inventoryView,
		bool useNoPrintPrice,
		unsigned char priceBase,
		unsigned char priceBaseIfNoPrint,
		unsigned char stopOrderType,
		unsigned char stopOrderBase,
		bool blockAggressiveOrders);
	AlgorithmMultipleOptionsBase(const char*& fromString);

	virtual bool PreProcessUnderlierNotification(const Message* message, const Message* info = nullptr) override;

	unsigned __int64 m_numericSymbol;
	unsigned int m_expirationDate;
	unsigned int m_strikePrice;

	int m_positionSize;
	Price m_orderBasePrice;
	Price m_orderPrice;
//	Price m_discretionaryPrice;

	unsigned int m_sprayCount;
	int m_spraySizeOffset;
	SignedPrice m_sprayPriceOffset;

	unsigned int m_optionStrikeCountUp;
	unsigned int m_optionStrikeCountDown;
	unsigned int m_optionExpirationCountUp;
	unsigned int m_optionExpirationCountDown;

	bool m_call;

	bool m_sprayPriceOffsetPercent;
	bool m_inventoryView;
	bool m_useNoPrintPrice;
	unsigned char m_priceBase;
	unsigned char m_priceBaseIfNoPrint;
	bool m_blockAggressiveOrders;
};

class TD_API AlgorithmMultipleOptions : public AlgorithmMultipleOptionsBase//UnderlierAlgorithm//TakionOrderAlgorithm
{
public:
	AlgorithmMultipleOptions(char side,
		int positionSize,
		unsigned int quantity,
		const Price& orderBasePrice,
		const Price& orderPrice,
		const Price& limitPrice,
		const Price& stopPrice,
		const Price& discretionaryPrice,

		const unsigned __int64& destinationId,
		unsigned int destinationName,

		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,

		unsigned int mnemonic,

		unsigned int sprayCount,
		int spraySizeOffset,
		const SignedPrice& sprayPriceOffset,

		unsigned char repriceFlags,
		unsigned short userOrderType,
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr
		const char* commandName,//usually should be nullptr

		TraderIdType traderId,
		unsigned int sendId,
		unsigned int parentId,// = 0,
		unsigned int ocoId,// = 0,
		unsigned int extensionId,
		const unsigned __int64& userId,

		const unsigned __int64& numericSymbol,
		unsigned int expirationDate,
		unsigned int strikePrice,

		unsigned int optionStrikeCountUp,
		unsigned int optionStrikeCountDown,
		unsigned int optionExpirationCountUp,
		unsigned int optionExpirationCountDown,

		bool call,

		bool sprayPriceOffsetPercent,
		bool inventoryView,
		bool useNoPrintPrice,
		unsigned char priceBase,
		unsigned char priceBaseIfNoPrint,
		unsigned char stopOrderType,
		unsigned char stopOrderBase,
		bool blockAggressiveOrders);
	AlgorithmMultipleOptions(const char*& fromString);
	virtual OrderAlgorithm* CloneAlgorithm() const override;
	virtual const char* GetAlgorithmName() const override{return "+Option";}
//	virtual void EndAlgorithm() override;
//	virtual void EndAlgorithmInThread() override;
	DECLARE_NED_NEW
//	virtual bool isQuoteOrder() const{return HasPrice();}
	virtual char* toString(char* buf) const override;
	virtual unsigned short GetAlgorithmSize() const override;
	virtual unsigned int GetAlgorithmId() const override{return TOA_PLUS_OPTION;}

protected:
//	virtual void NullifySecurity();
//	virtual void Notify(const Message* message, const Observable* from, const Message* info = nullptr);
//	virtual bool ShouldSecurityNotify(const Message* message, const Message* info = nullptr) const;
//	virtual void DoSecurityUpdate();
//	virtual bool PreProcessSecurityNotification(const Message* message, const Message* info = nullptr);

//	void DoSendOrder();
	virtual void OnUnderlierLoaded() override;

	void SendOneOptionOrder(const Security* const option,
		const char fixSide,
		const unsigned int absPositionSize,
		const unsigned int closePositionSize,
		const unsigned int openPositionSize,
		std::string& isoAttachment);

//	const Underlier* m_underlier;
};
/*
class TD_API AlgorithmSwipeMultipleOptions : public AlgorithmMultipleOptionsBase
{
public:
	typedef std::set<unsigned int> UIntSet;
	AlgorithmSwipeMultipleOptions(const Position* position,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,

		char side,

		unsigned char repriceFlags,
		unsigned short userOrderType,
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr

		const Price& limitPrice,

		unsigned int quantity,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

		bool excludeDestinations,
		const UIntSet& destinationSet,
		const UIntSet& filterSet,

		unsigned short routingId,
		unsigned int routingName,

		unsigned int roundLot,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool preBorrow,
		const Price& preBorrowPrice,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
//		bool proAts,
		bool blockAggressiveOrders,
		unsigned char roundLotPolicy,

		unsigned char pegType,
		const SignedPrice& pegOffset,

		bool hideSlowQuotes,

		char tifType,
		unsigned int tifMillisecond,

		bool postRemainder,
		unsigned int postDestination,
		unsigned int postDestinationName,
		unsigned int postRoutingName,
		unsigned short postRoutingId,
		unsigned short postRoutingSubType,
		unsigned int postMnemonic,
		unsigned char postTifType,
		unsigned int postTif,
		bool postRemainderOnIsoViolation,

		unsigned int parentId,// = 0,
		const unsigned __int64& userId,
		bool spider,
		unsigned int preBorrowSize);// = 0);
	AlgorithmSwipeMultipleOptions(const char*& fromString, bool spider);
//	virtual ~AlgorithmSmartSwipe();
	virtual OrderAlgorithm* CloneAlgorithm() const;
	virtual const char* GetAlgorithmName() const{return m_spider ? "+OpSpider" : "+OpSmartSwipe";}
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position);
	virtual void EndAlgorithm();
	virtual void EndAlgorithmInThread();
	DECLARE_NED_NEW
//	unsigned int CalculateFloatingLimitPrice() const;
	virtual char* toString(char* buf) const;
	virtual unsigned short GetAlgorithmSize() const;
	virtual unsigned int GetAlgorithmId() const{return TOA_PLUS_OPTION_SWIPE;}//m_spider ? TOA_SPIDER_SWIPE : TOA_SMART_SWIPE;}
//	virtual bool SecurityMustBeLoaded() const{return true;}
//	typedef std::hash_set<unsigned int> MmidSet;
protected:
//	void DoWriteCancel(unsigned char errorCode, const Money& moneyValue, const Money& moneyConstraint, unsigned int uintValue, unsigned int uintConstraint);
//	bool CanGrabQuote(const MsgQuote& quote, bool bidQuote) const;
//	virtual bool ShouldSecurityNotify(const Message* message, const Message* info = nullptr) const;
//	virtual void DoSecurityUpdate();
//	virtual bool PreProcessSecurityNotification(const Message* message, const Message* info = nullptr);
//	void InitializeFloatingLimitPrice();
//	virtual void StartSwiping();

//	virtual void Swipe();

//	virtual void PreBorrowDone();
//	Order* m_order;
//	Order* m_orderSplit;
//	TakionIterator* m_quoteIterator;

//	bool m_bypassedQuote;
//	bool m_nasdaq;
//	bool m_hideSlowQuotes;
//	bool m_blockAggressiveOrders;
//	bool m_excludeDestinations;
//	UIntSet m_destinationSet;
//	UIntSet m_filterSet;
//	TradedQuoteMap m_tradedQuotes;
//	TradedQuoteMap m_currentOrderQuotes;
//	MmidSet m_rejectedMmids;

//	unsigned int m_floatingLimitPriceCompact;
	bool m_spider;
};
*/
#endif

class TD_API AlgorithmTrigger : public TakionOrderAlgorithm
{
public:
	AlgorithmTrigger(const Position* position,
#ifndef TAKION_NO_OPTIONS
		unsigned char accountSecurityType,
#endif
		bool postponed,
		unsigned int timeToActivate,
		unsigned int timeToExpire,
		TraderIdType traderId,
		unsigned int sendId,
		unsigned int ocoId,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,
		char side,

		unsigned char repriceFlags,
		unsigned short userOrderType,
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr
		const char* triggerCommandName,//usually should be nullptr

		unsigned int maxPositionSize,

//		unsigned char orderType,
		const SignedPrice& priceDifference,
		bool priceDifferencePercent,
		const Price& stopPrice,
		char tifType,
		unsigned int tifMillisecond,
		unsigned int tierSize,
		unsigned int parentId,// = 0,
		unsigned int extensionId,
		const unsigned __int64& userId,
		unsigned char triggerType,
		bool triggerWhenNoLiveOrders,
		bool mustSubscribe,
		bool resetPrintSize,
		const unsigned __int64& printSize,
		bool trailing,
		bool closeOnly,
		bool openOnly,
		bool passiveOnly,
		bool blockAggressiveOrders,
		bool triggerOnConditionPreMet,
		bool inventoryView,
		int count,

		bool displayNote,
		COLORREF noteColor,
		const char* note,

		unsigned char exchImbalanceFlags,
		unsigned int exchImbalanceMin,
		unsigned int exchImbalanceMax,

		unsigned int printSourceFilter,//ignore prints

		bool useCommandCopy,
		const char* commandName,
		void* commandCopy);

	AlgorithmTrigger(const char*& fromString);
	virtual ~AlgorithmTrigger();
	static const char* const triggerVenue;
	virtual OrderAlgorithm* CloneAlgorithm() const override;
	virtual const char* GetAlgorithmName() const override{return "Trigger";}
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position) override;
	virtual void EndAlgorithm() override;
	virtual void EndAlgorithmInThread() override;
	DECLARE_NED_NEW
	virtual bool CanBeWashOrder() const override{return false;}
	virtual bool isQuoteOrder() const override{return HasPrice();}//isPriceValid();}
	virtual bool HasDirection() const override{return false;}
	virtual char* toString(char* buf) const override;
	virtual unsigned short GetAlgorithmSize() const override;
	virtual unsigned int GetAlgorithmId() const override{return TOA_TRIGGER;}
	virtual bool SecurityMustBeLoaded() const override{return true;}
	virtual bool isQuantityValid() const override{return true;}
	virtual bool isPriceValid() const override;
	virtual void ProcessMainThreadNotification(unsigned short code) override;
	bool isConditionAlreadyMet(Money& condition) const;
	virtual bool HasPrice() const override;
	virtual bool HasSize() const override;
	virtual bool isDone() const override{return false;}
	bool MustWatchLevel2() const;
	bool QuoteGreaterApplies(unsigned char bookId, const Price& quotePrice, bool bid) const;
	bool QuoteLessApplies(unsigned char bookId, const Price& quotePrice, bool bid) const;//for Modify messages only, when the quote price is available in the message
//	bool QuoteLessApplies(unsigned char bookId, bool bid) const;//when the quote price is not available in the message

	bool EcnQuoteGreaterApplies(unsigned char bookId, const Price& quotePrice, bool bid) const;
	bool EcnQuoteLessApplies(unsigned char bookId, const Price& quotePrice, bool bid) const;//for Modify messages only, when the quote price is available in the message
//	bool EcnQuoteLessApplies(unsigned char bookId, bool bid) const;//when the quote price is not available in the message

//	bool EcnHasSizeForPrice(const Price& price, unsigned int size, bool bid) const;//bool includePrice)

	bool isFollowPosition() const;
	bool PositionApplies(int executionSize) const;
	unsigned char CalculateRiPercent(Money& percent) const;//0 - condition already met; 1 - not met; 2: check value 'percent' to find out if met.
	unsigned char CalculateNyseImbalance(int& imbalance) const;//0 - condition already met; 1 - not met; 2: check value 'percent' to find out if met.
	unsigned char CalculateNsdqImbalance(int& imbalance) const;//0 - condition already met; 1 - not met; 2: check value 'percent' to find out if met.
	unsigned char isRiPercentAlreadyMet(Money& percent) const;//0 - not the right type; 1 - not met; 2 - met; 3 - not applicable
	unsigned char isImbalanceAlreadyMet(int& imbalance) const;//0 - not the right type; 1 - not met; 2 - met; 3 - not applicable
//	virtual unsigned int GetTotalSize() const{return m_printSize > 0xFFFFFFFF ? 0xFFFFFFFF : (unsigned int)m_printSize;}
	virtual const std::string& GetStopOrderTypeStr() const override;
	virtual const std::string& GetStopOrderBaseStr() const override;
	virtual unsigned int GetAlgorithmQuantity() const override{return m_printSize > 0xFFFFFFFF ? 0xFFFFFFFF : (unsigned int)m_printSize;}
	const bool& isInventoryView() const{return m_inventoryView;}
	virtual void InThreadUpdate(unsigned short code, unsigned short eventCode) override;

	const bool& isDisplayNote() const{return m_displayNote;}
	const COLORREF& GetNoteColor() const{return m_noteColor;}
	const std::string& GetNote() const{return m_note;}
//	unsigned char isToTriggerByPrice(const Price& price) const{return price == m_priceTo || (m_priceFrom < m_priceTo ? m_priceTo < price : price < m_priceTo);}
	bool isToTriggerByPrice(const Price& price) const{return price == m_priceTo || (m_priceFrom < m_priceTo ? m_priceTo < price : price < m_priceTo);}

	const bool& isUseCommandCopy() const{return m_useCommandCopy;}
	void* GetCommandCopy() const{return m_commandCopy;}
	void SetCommandCopy(void* commandCopy){m_commandCopy = commandCopy;}
	virtual bool CanBeOco() const override{return true;}

	bool isFirableByExchImbalance() const;

protected:
	void StartTrigger();

	void Fire(bool conditionPreMet);

	virtual void NullifySecurity() override;
	virtual void Notify(const Message* message, const Observable* from, const Message* info = nullptr) override;
	virtual bool ShouldSecurityNotify(const Message* message, const Message* info = nullptr) const override;
	virtual void DoSecurityUpdate() override;
	virtual bool PreProcessSecurityNotification(const Message* message, const Message* info = nullptr) override;

	void HandleNewQuote(const unsigned char bookId, const Price& quotePrice, const bool bid);
	void HandleModifyQuote(const unsigned char bookId, const Price& oldPrice, const Price& newPrice, const unsigned int oldSize, const unsigned int newSize, const bool bid);
	void HandleDeleteQuote(const unsigned char bookId, const Price& quotePrice, const bool bid);
	void HandleDecrementQuote(const unsigned char bookId, const Price& quotePrice, const unsigned int oldSize, const unsigned int newSize, const bool bid);

	void HandleSecurityRefresh(bool failed, bool done);

	void HandleConditionPreMet(const Money& cond);
	void HandleConditionPreMetException();

//	bool TriggerByLastNbboPrint();
	bool InitializeSubtractionComponents();
	bool TriggerByPriceDifference(unsigned int printSize, bool greaterThan);
	bool TriggerByPrice(const Price& price, unsigned int printSize);
	void TrailPriceLess(const Price& price);
	void TrailPriceGreater(const Price& price);
	void TrailPriceFrom(const Price& price);

//	bool Done(const Price& price, unsigned printSize);
	bool Done(const unsigned __int64& printSize);

	void SendFireNotification();
	void StartFiring();

	unsigned char m_triggerType;
	bool m_triggerWhenNoLiveOrders;
	bool m_mustSubscribe;

	int m_count;

	bool m_trailing;
//	bool m_closeOnly;
	bool m_passiveOnly;
//	bool m_blockAggressiveOrders;

	bool m_triggerOnConditionPreMet;

	bool m_inventoryView;

	bool m_useCommandCopy;

	bool m_displayNote;
	COLORREF m_noteColor;
	std::string m_note;

	unsigned char m_exchImbalanceFlags;
	unsigned int m_exchImbalanceMin;
	unsigned int m_exchImbalanceMax;

	void AdjustPrintApplicable(char mcid, bool& printApplicable) const;
	unsigned int m_printSourceFilter;

	std::string m_commandName;

	void* m_commandCopy;

//	std::string m_symbol;
	unsigned __int64 m_numericSymbol;
#ifndef TAKION_NO_OPTIONS
	unsigned __int64 m_optionBlock;
#endif
	Price m_priceSubtrahend;
	Price m_priceMinuend;
	SignedPrice m_priceDifference;
	SignedPrice m_priceDifferenceCalculated;
	bool m_priceChangeAbsolute;
	bool m_priceDifferencePercent;
	bool m_priceDifferenceInitialized;
	void InitializePriceDifferencePercent();
	static bool isPriceChangeAbsolute(unsigned char triggerType);

	Price m_priceTo;
	Price m_priceFrom;
	bool m_initialized;
	bool m_done;
	bool m_fired;
	bool m_heldByExchImbalance;

	bool m_inPrice;

	bool m_resetPrintSize;
	unsigned __int64 m_printSize;
	unsigned __int64 m_accumulatedPrintSize;

	mutable int m_prevIntValue;//for imbalnces
	mutable Money m_prevMoneyValue;//for imbalnce percentages

//	Position* m_position;
	const Book* m_book;

	void DeleteEcnBookIterator();
	TakionIterator* m_ecnBidBookIterator;
	TakionIterator* m_ecnAskBookIterator;

	Observable* m_newEquityObservable;
};

class TD_API AlgorithmOrderReplacer : public OrderReplacer
{
public:
	AlgorithmOrderReplacer(const Position* position,
		unsigned int orderToReplaceClientId,
		unsigned int gtcDateCreated,
		unsigned int gtcTimeCreated,
		TraderIdType traderId,
		unsigned int sendId,
		unsigned int ocoId,
		unsigned int clientId,
//		unsigned int clientIdOriginal,
		const unsigned __int64& averageDailyVolume,
		const unsigned __int64& yesterdaysVolume,
		const unsigned __int64& todaysVolume,
		const unsigned __int64& destinationId,
		unsigned int destinationName,

		char side,

		unsigned char repriceFlags,
		unsigned char orderType,

		unsigned short userOrderType,
		const char* userOrderInfo,//usually should be nullptr
		const void* userData,//usually should be nullptr
		const char* commandName,

		const Price& limitPrice,
		
		const Price& discretionaryPrice,
		unsigned char stopOrderType,
		unsigned char stopOrderBase,
		const Price& stopPrice,
		
		const Price& level1Price,
		const Price& level1SameSidePrice,
		const Price& lastPrintPrice,

		int replaceSizeOffset,
		unsigned int quantity,
		unsigned int estimatedQuantityToSend,
		unsigned int displayQuantity,
		unsigned int reserveQuantity,

//		bool proactive,
		unsigned short routingId,
		unsigned short routingSubType,
		unsigned int routingName,
		unsigned int mnemonic,

		bool noReplaceIfRejected,

		bool dma,
		bool syntheticIgnoreFinra,
		bool syntheticWaitNext,
		bool imbalanceOnly,
		bool iso,
		bool aggressive,
		unsigned int roundLot,
		unsigned char washOrderPolicy,//WOP_KEEP, WOP_CANCEL, WOP_CANCEL_AND_WAIT
		unsigned char oversellSplitPolicy,//OOP_RESIZE, OOP_SPLIT, OOP_REJECT
		bool resizeShortToBorrowed,
		bool noRedirect,
		bool closeOnly,
		bool resizeToClose,
		bool openOnly,
		unsigned char roundLotPolicy,
		unsigned char pegType,
		const SignedPrice& pegOffset,

		bool preBorrow,
		const Price& preBorrowPrice,

		char tifType,
		unsigned int tifMillisecond,
		unsigned int parentId,// = 0,
		unsigned int extensionId,
		const unsigned __int64& userId,
		bool nativeReplace = false);
//	AlgorithmSmartSwipe(const AlgorithmSmartSwipe& other):OrderAlgorithm(other){}
	AlgorithmOrderReplacer(const char*& fromString);
//	virtual ~AlgorithmOrderReplacer();
	virtual OrderAlgorithm* CloneAlgorithm() const override;
//	virtual const char* GetAlgorithmName() const{return "Replacer";}
	virtual void StartAlgorithm(const Security* security, Account* account, const Position* position) override;
	virtual void EndAlgorithm() override;
	virtual void EndAlgorithmInThread() override;
	DECLARE_NED_NEW
	virtual char* toString(char* buf) const override;
	virtual unsigned short GetAlgorithmSize() const override;
//	virtual unsigned int GetAlgorithmId() const{return OA_ORDER_REPLACER;}
//	typedef std::hash_set<unsigned int> MmidSet;
	virtual void WriteOrderCancelToMainThread(bool deleteUntradedPosition = false) override;
protected:
	virtual void Notify(const Message* message, const Observable* from, const Message* info = nullptr) override;
	virtual void DoSendReplacement(Order* orderToReplace) override;
	virtual unsigned int GetNextClientId() const override;
};

class TD_API ClientExtensionDll : public ExtensionDll
{
public:
	static const unsigned int validExtensionCode = 1;
	ClientExtensionDll(const char* absolutePath, const unsigned __int64& takionGuiHeaderVersion, const unsigned __int64& utilsGuiHeaderVersion):
		ExtensionDll(absolutePath,
			U_VersionStrToNum(UtilsHeaderVersion),
			U_VersionStrToNum(TakionUtilsHeaderVersion),
			takionGuiHeaderVersion,
			utilsGuiHeaderVersion,
			U_VersionStrToNum(TakionDataHeaderVersion),
			U_VersionStrToNum(TakionLogHeaderVersion),
			U_VersionStrToNum(ObserverHeaderVersion))
	{}
	ClientExtensionDll(const char* name, const char* path, const unsigned __int64& takionGuiHeaderVersion, const unsigned __int64& utilsGuiHeaderVersion):
		ExtensionDll(name, path,
			U_VersionStrToNum(UtilsHeaderVersion),
			U_VersionStrToNum(TakionUtilsHeaderVersion),
			takionGuiHeaderVersion,
			utilsGuiHeaderVersion,
			U_VersionStrToNum(TakionDataHeaderVersion),
			U_VersionStrToNum(TakionLogHeaderVersion),
			U_VersionStrToNum(ObserverHeaderVersion))
	{}
	virtual unsigned int GetValidExtensionCode() const{return validExtensionCode;}
//protected:
};

class TD_API NewsDll : public BaseExtensionDll//, public Observable
{
public:
	virtual ~NewsDll();
	virtual bool Unload();
	virtual bool Load();
	unsigned char Connect(const char* hostName,
		unsigned short port,
		const char* userName,
		const char* password,
		const char* appName,
		const char* appVersion,
		const char* companyName,
		const char* sessionData,
		const char* proxyIpAddress,
		unsigned short proxyPort,
		const char* proxyProtocolName,
		const char* proxyUserName,
		const char* proxyPassword,
		const char* newPassword) const;
	bool isConnected() const{return m_IsNewsConnectedFunction && m_IsNewsConnectedFunction();}
//	void AddObserver(Observer* observer);
	Observable* GetObservable() const{return m_NewsGetObservableFunction ? m_NewsGetObservableFunction() : nullptr;}
	void SetLogFile(void* logFileHandle) const{if(m_NewsSetLogFileFunction)m_NewsSetLogFileFunction(logFileHandle);}
/*
	Observable* GetStockNews(Observable* oldStockNews, const Observable* newsCollection, const unsigned __int64& symbol) const{return m_NewsGetStockNewsByNum ? m_NewsGetStockNewsByNum(oldStockNews, newsCollection, symbol) : nullptr;}
	Observable* GetStockNews(Observable* oldStockNews, const Observable* newsCollection, const char* symbol) const{return m_NewsGetStockNewsByCharPtr ? m_NewsGetStockNewsByCharPtr(oldStockNews, newsCollection, symbol) : nullptr;}
	Observable* GetStringNews(Observable* oldStockNews, const Observable* newsCollection, const FilterStringAsNumberArray& str, const std::hash_set<unsigned __int64>* stockSet) const{return m_NewsGetStringNews ? m_NewsGetStringNews(oldStockNews, newsCollection, str, stockSet) : nullptr;}
*/
	Observable* GetStockNews(const Observable* newsCollection, const unsigned __int64& symbol) const{return m_NewsGetStockNewsByNum ? m_NewsGetStockNewsByNum(newsCollection, symbol) : nullptr;}
	Observable* GetStockNews(const Observable* newsCollection, const char* symbol) const{return m_NewsGetStockNewsByCharPtr ? m_NewsGetStockNewsByCharPtr(newsCollection, symbol) : nullptr;}
	Observable* GetStringNews(const Observable* newsCollection, const FilterStringAsNumberArray& str,
#if (_MSC_VER > 1600)
		const std::unordered_set<unsigned __int64>*
#else
		const std::hash_set<unsigned __int64>*
#endif
		stockSet) const{return m_NewsGetStringNews ? m_NewsGetStringNews(newsCollection, str, stockSet) : nullptr;}

	Observable* FindStockNews(const Observable* newsCollection, const unsigned __int64& symbol) const{return m_NewsFindStockNewsByNum ? m_NewsFindStockNewsByNum(newsCollection, symbol) : nullptr;}
	Observable* FindStringNews(const Observable* newsCollection, const FilterStringAsNumberArray& str) const{return m_NewsFindStringNews ? m_NewsFindStringNews(newsCollection, str) : nullptr;}

	bool isNewsCollectionInvalid(const Observable* newsCollection) const{return m_NewsIsNewsCollectionInvalid && m_NewsIsNewsCollectionInvalid(newsCollection);}
	bool isStringNewsInvalid(const Observable* stringNews) const{return m_NewsIsStringNewsInvalid && m_NewsIsStringNewsInvalid(stringNews);}

	bool DoIdle(LONG count) const{return m_NewsDoIdle && m_NewsDoIdle(count);}
	unsigned char ReleaseNewsCollection(Observable* newsCollection, Observer* observer) const{return m_NewsReleaseNewsCollection ? m_NewsReleaseNewsCollection(newsCollection, observer) : 0;}
	Observable* UpdateNewsCollectionFilter(Observable* newsCollection, Observer* observer, const WireSet& wireSet, unsigned int storyFilter, unsigned int metaFilter, unsigned int relevance, bool& oldCollectionDeleted) const
	{
		if(m_NewsUpdateNewsCollectionFilter)
		{
			return m_NewsUpdateNewsCollectionFilter(newsCollection, observer, wireSet, storyFilter, metaFilter, relevance, oldCollectionDeleted);
		}
		else
		{
			oldCollectionDeleted = false;
			return nullptr;
		}
	}

	unsigned int GetStockHeadlineCount(const unsigned __int64& numericSymbol) const{return m_NewsGetStockHeadlineCount ? m_NewsGetStockHeadlineCount(numericSymbol) : 0;}
	unsigned int GetStockHeadlineCountAndLatestDateTime(const unsigned __int64& numericSymbol, unsigned __int64& latestDateTime) const
	{
		if(m_NewsGetStockHeadlineCountAndLatestDateTime)
		{
			return m_NewsGetStockHeadlineCountAndLatestDateTime(numericSymbol, latestDateTime);
		}
		else
		{
			latestDateTime = 0;
			return 0;
		}
	}

	unsigned int GetStockTodaysHeadlineCount(const unsigned __int64& numericSymbol) const{return m_NewsGetStockTodaysHeadlineCount ? m_NewsGetStockTodaysHeadlineCount(numericSymbol) : 0;}
	unsigned int GetStockTodaysHeadlineCountAndLatestDateTime(const unsigned __int64& numericSymbol, unsigned __int64& latestDateTime) const
	{
		if(m_NewsGetStockTodaysHeadlineCountAndLatestDateTime)
		{
			return m_NewsGetStockTodaysHeadlineCountAndLatestDateTime(numericSymbol, latestDateTime);
		}
		else
		{
			latestDateTime = 0;
			return 0;
		}
	}

	unsigned int GetStockYestAfterMarketHeadlineCount(const unsigned __int64& numericSymbol) const{return m_NewsGetStockYestAfterMarketHeadlineCount ? m_NewsGetStockYestAfterMarketHeadlineCount(numericSymbol) : 0;}
	unsigned int GetStockYestAfterMarketHeadlineCountAndLatestDateTime(const unsigned __int64& numericSymbol, unsigned __int64& latestDateTime) const
	{
		if(m_NewsGetStockYestAfterMarketHeadlineCountAndLatestDateTime)
		{
			return m_NewsGetStockYestAfterMarketHeadlineCountAndLatestDateTime(numericSymbol, latestDateTime);
		}
		else
		{
			latestDateTime = 0;
			return 0;
		}
	}

	unsigned int GetFilterStringLengthLimit() const{return m_NewsGetFilterStringLengthLimit ? m_NewsGetFilterStringLengthLimit() : 0xFFFFFFFF;}
	unsigned int GetFilterStringTokenLimit() const{return m_NewsGetFilterStringTokenLimit ? m_NewsGetFilterStringTokenLimit() : 0xFFFFFFFF;}
	bool TruncateSearchStringDownToTokens(std::string& str){return m_NewsTruncateSearchStringDownToTokens && m_NewsTruncateSearchStringDownToTokens(str);}

	unsigned int GetWireCount() const{return m_NewsGetWireCount ? m_NewsGetWireCount() : 0;}
	bool GetWireInfoAt(unsigned int at, std::string& description, unsigned int& id, unsigned short& subid, unsigned short& baseId, bool& subwire, bool& entitled) const{return m_NewsGetWireInfoAt && m_NewsGetWireInfoAt(at, description, id, subid, baseId, subwire, entitled);}
	TakionIterator* CreateWireIterator() const{return m_NewsCreateWireIterator ? m_NewsCreateWireIterator() : nullptr;}
	bool GetNextWireInfo(TakionIterator* iterator, std::string& description, unsigned int& id, unsigned short& subid, unsigned short& baseId, bool& subwire, bool& entitled) const{return m_NewsGetNextWireInfo && m_NewsGetNextWireInfo(iterator, description, id, subid, baseId, subwire, entitled);}

	const char* GetConnectionStatusInfo() const{return m_NewsGetConnectionStatusInfo ? m_NewsGetConnectionStatusInfo() : "";}
	unsigned int GetAllWireCount() const{return m_NewsGetAllWireCount ? m_NewsGetAllWireCount() : 0;}
	TakionIterator* CreateAllWireIterator() const{return m_NewsCreateAllWireIterator ? m_NewsCreateAllWireIterator() : nullptr;}
	bool GetNextAllWireInfo(TakionIterator* iterator, std::string& description, unsigned int& id, unsigned short& subid, unsigned short& baseId, bool& subwire, bool& entitled) const{return m_NewsGetNextAllWireInfo && m_NewsGetNextAllWireInfo(iterator, description, id, subid, baseId, subwire, entitled);}

	unsigned int GetTopicCount() const{return m_NewsGetTopicCount ? m_NewsGetTopicCount() : 0;}
	TakionIterator* CreateTopicIterator() const{return m_NewsCreateTopicIterator ? m_NewsCreateTopicIterator() : nullptr;}
	const std::string* GetNextTopicInfo(TakionIterator* iterator, std::string* description) const{return m_NewsGetNextTopicInfo ? m_NewsGetNextTopicInfo(iterator, description) : nullptr;}

	void AdjustToChangedScreen(int dx, int dy) const{if(m_NewsAdjustToChangedScreen)m_NewsAdjustToChangedScreen(dx, dy);}

	bool CanDisplayFilterDialog() const{return m_NewsDisplayFilterDialog != nullptr;}
	bool CanDisplayLimitsDialog() const{return m_NewsDisplayLimitsDialog != nullptr;}

	void DisplayFilterDialog(CWnd* receipient,
		unsigned int code,
		const WireSet& wireSet,
		unsigned int storyFilter,
		unsigned int metaFilter,
		unsigned int relevance,
		CWnd* parent,
		const CPoint& mousePoint) const;
	bool GetFilterDialogValues(WireSet& wireSet,
		unsigned int& storyFilter,
		unsigned int& metaFilter,
		unsigned int& relevance) const;
	
	void DisplayLimitsDialog(CWnd* receipient,
		unsigned int code,
		unsigned short daysBack,
		unsigned int headlineCount,
		bool afterMarket,
		CWnd* parent,
		const CPoint& mousePoint) const;
	bool GetLimitsDialogValues(unsigned short& daysBack,
		unsigned int& headlineCount,
		bool& afterMarket) const;
	
	bool RequestHeadlines(Observable* stockNews, unsigned short daysBack, unsigned int headlineCount, bool afterMarket) const{return m_NewsRequestHeadlines && m_NewsRequestHeadlines(stockNews, daysBack, headlineCount, afterMarket);}
	bool RequestStory(const NewsHeadline* headline, bool showChain, bool displayHyperlink) const{return m_NewsRequestStory && m_NewsRequestStory(headline, showChain, displayHyperlink);}

	const LineBufferArray* GetUnappliedHeadlines(Observable* stockNews) const{return m_NewsGetUnappliedHeadlines ? m_NewsGetUnappliedHeadlines(stockNews) : nullptr;}
	Observable* FindNewsCollectionById(unsigned int id) const{return m_NewsFindNewsCollectionById ? m_NewsFindNewsCollectionById(id) : nullptr;}
	bool isUpdatedHeadline(Observable* stockNews, unsigned int updateOrdinal) const{return m_NewsIsUpdatedHeadline && m_NewsIsUpdatedHeadline(stockNews, updateOrdinal);}
	void SetUpdatedHeadline(Observable* stockNews) const{if(m_NewsSetUpdatedHeadline)m_NewsSetUpdatedHeadline(stockNews);}
	void ReadNewHeadlines(Observable* stockNews) const{if(m_NewsReadNewHeadlines)m_NewsReadNewHeadlines(stockNews);}
	void ReleaseNewHeadlines(Observable* stockNews) const{if(m_NewsReleaseNewHeadlines)m_NewsReleaseNewHeadlines(stockNews);}
	const NewsHeadline* FindHeadline(const Observable* stockNews, const NewsResourceAsNumberArray& resourceId) const{return m_NewsFindHeadline ? m_NewsFindHeadline(stockNews, resourceId) : nullptr;}

	unsigned int GetHeadlineCount(const Observable* stockNews) const{return m_NewsGetHeadlineCount ? m_NewsGetHeadlineCount(stockNews) : 0;}
	TakionIterator* CreateHeadlineIterator(const Observable* stockNews) const{return m_NewsCreateHeadlineIterator ? m_NewsCreateHeadlineIterator(stockNews) : nullptr;}
	const NewsHeadline* GetNextHeadline(TakionIterator* iterator) const{return m_NewsGetNextHeadline ? m_NewsGetNextHeadline(iterator) : nullptr;}

	bool LockInquiryHeadlines(Observable* stockNews)const{return m_NewsLockInquiryHeadlines && m_NewsLockInquiryHeadlines(stockNews);}
	void LockInquiryWaitHeadlines(Observable* stockNews)const{if(m_NewsLockInquiryWaitHeadlines)m_NewsLockInquiryWaitHeadlines(stockNews);}
	void UnlockInquiryHeadlines(Observable* stockNews)const{if(m_NewsUnlockInquiryHeadlines)m_NewsUnlockInquiryHeadlines(stockNews);}

	bool isStockNewsRequested(const Observable* stockNews) const{return !m_NewsIsStockNewsRequested || m_NewsIsStockNewsRequested(stockNews);}
	const std::string* GetSearchStringUnfiltered() const{return m_NewsGetSearchStringUnfiltered ? m_NewsGetSearchStringUnfiltered() : nullptr;}
	const std::string* GetSearchStringAll() const{return m_NewsGetSearchStringAll ? m_NewsGetSearchStringAll() : nullptr;}
	const std::string* GetSearchStringAllUs() const{return m_NewsGetSearchStringAllUs ? m_NewsGetSearchStringAllUs() : nullptr;}

	const NewsStory* FindStoryByResourceId(const NewsResourceAsNumberArray& resourceId) const{return m_NewsFindStoryByResourceId ? m_NewsFindStoryByResourceId(resourceId) : nullptr;}
	const NewsStory* GetLastStory() const{return m_NewsGetLastStory ? m_NewsGetLastStory() : nullptr;}
	bool LockInquiryStory()const{return m_NewsLockInquiryStory && m_NewsLockInquiryStory();}
	void LockInquiryWaitStory()const{if(m_NewsLockInquiryWaitStory)m_NewsLockInquiryWaitStory();}
	void UnlockInquiryStory()const{if(m_NewsUnlockInquiryStory)m_NewsUnlockInquiryStory();}
	bool isUpdatedStory(unsigned int updateOrdinal) const{return m_NewsIsUpdatedStory && m_NewsIsUpdatedStory(updateOrdinal);}
	void SetUpdatedStory() const{if(m_NewsSetUpdatedStory)m_NewsSetUpdatedStory();}
	Observable* GetStoryObservable() const{return m_NewsGetStoryObservable ? m_NewsGetStoryObservable() : nullptr;}

	bool LockInquiryWireNameStorage()const{return m_NewsLockInquiryWireNameStorage && m_NewsLockInquiryWireNameStorage();}
	void LockInquiryWaitWireNameStorage()const{if(m_NewsLockInquiryWaitWireNameStorage)m_NewsLockInquiryWaitWireNameStorage();}
	void UnlockInquiryWireNameStorage()const{if(m_NewsUnlockInquiryWireNameStorage)m_NewsUnlockInquiryWireNameStorage();}

	bool LockInquiryAllWireNameStorage()const{return m_NewsLockInquiryAllWireNameStorage && m_NewsLockInquiryAllWireNameStorage();}
	void LockInquiryWaitAllWireNameStorage()const{if(m_NewsLockInquiryWaitAllWireNameStorage)m_NewsLockInquiryWaitAllWireNameStorage();}
	void UnlockInquiryAllWireNameStorage()const{if(m_NewsUnlockInquiryAllWireNameStorage)m_NewsUnlockInquiryAllWireNameStorage();}

	bool LockInquiryTopicNameStorage()const{return m_NewsLockInquiryTopicNameStorage && m_NewsLockInquiryTopicNameStorage();}
	void LockInquiryWaitTopicNameStorage()const{if(m_NewsLockInquiryWaitTopicNameStorage)m_NewsLockInquiryWaitTopicNameStorage();}
	void UnlockInquiryTopicNameStorage()const{if(m_NewsUnlockInquiryTopicNameStorage)m_NewsUnlockInquiryTopicNameStorage();}

	void ProcessConnectionInMainThread(bool connected) const{if(m_NewsProcessConnectionInMainThread)m_NewsProcessConnectionInMainThread(connected);}
	bool NewsCollectionHasProfile(const Observable* newsCollection) const{return !m_NewsCollectionHasProfile || m_NewsCollectionHasProfile(newsCollection);}
protected:
	NewsDll(const char* absolutePath, const unsigned __int64& takionGuiHeaderVersion, const unsigned __int64& utilsGuiHeaderVersion);
	NewsDll(const char* name, const char* path, const unsigned __int64& takionGuiHeaderVersion, const unsigned __int64& utilsGuiHeaderVersion);
	virtual bool DoLoad();
	virtual void Reset()
	{
		BaseExtensionDll::Reset();
		NullifyFunctions();
	}
	void NullifyFunctions();
	bool AdditionalUnload();
	ApiNewsConnect m_NewsConnectFunction;
	ApiIs m_IsNewsConnectedFunction;
	ApiGetObservable m_NewsGetObservableFunction;
	ApiVoidPtr m_NewsSetLogFileFunction;
	ApiGetStockNewsByUInt64 m_NewsGetStockNewsByNum;
	ApiGetStockNewsByCharPtr m_NewsGetStockNewsByCharPtr;
	ApiGetObservableUInt64 m_NewsFindStockNewsByNum;
	ApiGetStockNewsByString m_NewsGetStringNews;
	ApiFindStockNewsByString m_NewsFindStringNews;

	ApiBoolObservable m_NewsIsNewsCollectionInvalid;
	ApiBoolObservable m_NewsIsStringNewsInvalid;

	ApiIsLong m_NewsDoIdle;
//	ApiObtainNewsCollection m_NewsObtainNewsCollection;
	ApiReleaseNewsCollection m_NewsReleaseNewsCollection;
	ApiUpdateNewsCollectionFilter m_NewsUpdateNewsCollectionFilter;

	ApiGetUIntByUInt64 m_NewsGetStockHeadlineCount;
	ApiGetUIntAndUInt64ByUInt64 m_NewsGetStockHeadlineCountAndLatestDateTime;

	ApiGetUIntByUInt64 m_NewsGetStockTodaysHeadlineCount;
	ApiGetUIntAndUInt64ByUInt64 m_NewsGetStockTodaysHeadlineCountAndLatestDateTime;

	ApiGetUIntByUInt64 m_NewsGetStockYestAfterMarketHeadlineCount;
	ApiGetUIntAndUInt64ByUInt64 m_NewsGetStockYestAfterMarketHeadlineCountAndLatestDateTime;

	ApiGetUInt m_NewsGetFilterStringLengthLimit;
	ApiGetUInt m_NewsGetFilterStringTokenLimit;
	ApiBoolString m_NewsTruncateSearchStringDownToTokens;

	ApiGetUInt m_NewsGetWireCount;
	ApiGetWireInfoAt m_NewsGetWireInfoAt;
	ApiCreateIterator m_NewsCreateWireIterator;
	ApiGetNextWireInfo m_NewsGetNextWireInfo;

	ApiGetString m_NewsGetConnectionStatusInfo;
	ApiGetUInt m_NewsGetAllWireCount;
//	ApiGetWireInfoAt m_NewsGetAllWireInfoAt;
	ApiCreateIterator m_NewsCreateAllWireIterator;
	ApiGetNextWireInfo m_NewsGetNextAllWireInfo;

	ApiGetUInt m_NewsGetTopicCount;
	ApiCreateIterator m_NewsCreateTopicIterator;
	ApiGetNextTopicInfo m_NewsGetNextTopicInfo;
	ApiIntInt m_NewsAdjustToChangedScreen;
	ApiNewsDisplayFilterDialog m_NewsDisplayFilterDialog;
	ApiGetFilterDialogValues m_NewsGetFilterDialogValues;
	ApiNewsDisplayLimitsDialog m_NewsDisplayLimitsDialog;
	ApiGetLimitsDialogValues m_NewsGetLimitsDialogValues;
	ApiRequestHeadlines m_NewsRequestHeadlines;
	ApiRequestStory m_NewsRequestStory;
	ApiGetUnappliedHeadlines m_NewsGetUnappliedHeadlines;
	ApiFindNewsCollectionById m_NewsFindNewsCollectionById;
	ApiIsObservableUInt m_NewsIsUpdatedHeadline;
	ApiObservable m_NewsSetUpdatedHeadline;
	ApiObservable m_NewsReadNewHeadlines;
	ApiObservable m_NewsReleaseNewHeadlines;
	ApiFindHeadline m_NewsFindHeadline;
	ApiGetHeadlineCount m_NewsGetHeadlineCount;
	ApiCreateHeadlineIterator m_NewsCreateHeadlineIterator;
	ApiGetNextHeadline m_NewsGetNextHeadline;
	ApiIsObservable m_NewsLockInquiryHeadlines;
	ApiObservable m_NewsLockInquiryWaitHeadlines;
	ApiObservable m_NewsUnlockInquiryHeadlines;
	ApiIsObservableConst m_NewsIsStockNewsRequested;
	ApiGetStdString m_NewsGetSearchStringUnfiltered;
	ApiGetStdString m_NewsGetSearchStringAll;
	ApiGetStdString m_NewsGetSearchStringAllUs;

	ApiFindStoryByResourceId m_NewsFindStoryByResourceId;
	ApiGetStory m_NewsGetLastStory;
	ApiIs m_NewsLockInquiryStory;
	ApiVoid m_NewsLockInquiryWaitStory;
	ApiVoid m_NewsUnlockInquiryStory;
	ApiIsUInt m_NewsIsUpdatedStory;
	ApiVoid m_NewsSetUpdatedStory;
	ApiGetObservable m_NewsGetStoryObservable;

	ApiIs m_NewsLockInquiryWireNameStorage;
	ApiVoid m_NewsLockInquiryWaitWireNameStorage;
	ApiVoid m_NewsUnlockInquiryWireNameStorage;

	ApiIs m_NewsLockInquiryAllWireNameStorage;
	ApiVoid m_NewsLockInquiryWaitAllWireNameStorage;
	ApiVoid m_NewsUnlockInquiryAllWireNameStorage;

	ApiIs m_NewsLockInquiryTopicNameStorage;
	ApiVoid m_NewsLockInquiryWaitTopicNameStorage;
	ApiVoid m_NewsUnlockInquiryTopicNameStorage;

	ApiBool m_NewsProcessConnectionInMainThread;
	ApiIsObservableConst m_NewsCollectionHasProfile;
};

class TD_API IndexDescription
{
public:
	IndexDescription(const char* symbol, const char* description, const char* valueTemplate, const char* netTemplate):
		m_symbol(symbol),
		m_description(description ? description : ""),
		m_valueTemplate(valueTemplate),
		m_netTemplate(netTemplate),
		m_numericSymbol(U_RepresentStringAsUnsignedNumber<unsigned __int64>(symbol, sizeof(unsigned __int64) - 1))
	{
	}
	IndexDescription():m_numericSymbol(0){}
	const std::string& GetSymbol() const{return m_symbol;}
	const std::string& GetDescription() const{return m_description;}
	const std::string& GetValueTemplate() const{return m_valueTemplate;}
	const std::string& GetNetTemplate() const{return m_netTemplate;}
	const unsigned __int64& GetNumericSymbol() const{return m_numericSymbol;}
protected:
	std::string m_symbol;
	std::string m_description;
	std::string m_valueTemplate;
	std::string m_netTemplate;
	unsigned __int64 m_numericSymbol;
};

class TD_API TierPriceRange
{
public:
	TierPriceRange(const Price& from, const Price& to, unsigned int tierSize):
		m_from(from),
		m_to(to),
		m_tierSize(tierSize)
	{}
	const Price& GetFrom() const{return m_from;}
	const Price& GetTo() const{return m_to;}
	const unsigned int& GetTierSize() const{return m_tierSize;}
	
	bool operator==(const TierPriceRange& other) const
	{
		return m_from == other.m_from && m_to == other.m_to && m_tierSize == other.m_tierSize;
	}
	bool operator!=(const TierPriceRange& other) const{return !operator==(other);}
	bool Belongs(const Price& price) const{return m_from < price && price <= m_to;}
protected:
	Price m_from;
	Price m_to;
	unsigned int m_tierSize;
};

class TD_API TierPriceRangeCollection
{
public:
	typedef std::vector<TierPriceRange> TierPriceRangeVector;
	TierPriceRangeCollection(unsigned int defaultTierSize = 0):
		m_defaultTierSize(defaultTierSize)
	{}
	const unsigned int& GetDefaultTierSize() const{return m_defaultTierSize;}
	const TierPriceRangeVector& GetTierPriceRangeVector() const{return m_tierPriceRangeVector;}

	void SetDefaultTierSize(unsigned int defaultTierSize){m_defaultTierSize = defaultTierSize;}
	void AddTierPriceRange(const Price& from, const Price& to, unsigned int tierSize)
	{
		m_tierPriceRangeVector.push_back(TierPriceRange(from, to, tierSize));
	}
	void ClearPriceRanges(){m_tierPriceRangeVector.clear();}
	bool operator==(const TierPriceRangeCollection& other) const
	{
		if(m_defaultTierSize != other.m_defaultTierSize || m_tierPriceRangeVector.size() != other.m_tierPriceRangeVector.size())
		{
			return false;
		}
		if(!m_tierPriceRangeVector.empty())
		{
			TierPriceRangeVector::const_iterator it = m_tierPriceRangeVector.begin(), itend = m_tierPriceRangeVector.end(), itOther = other.m_tierPriceRangeVector.begin(), itOtherEnd = other.m_tierPriceRangeVector.end();
			for(; it != itend && itOther != itOtherEnd; ++it, ++itOther)
			{
				if(*it != *itOther)
				{
					return false;
				}
			}
			return it == itend && itOther == itOtherEnd;
		}
		return true;
	}
	bool operator!=(const TierPriceRangeCollection& other) const{return !operator==(other);}
	const unsigned int& GetTierSize(const Price& price) const
	{
		if(!m_tierPriceRangeVector.empty())
		{
			for(TierPriceRangeVector::const_iterator it = m_tierPriceRangeVector.begin(), itend = m_tierPriceRangeVector.end(); it != itend; ++it)
			{
				if(it->Belongs(price))
				{
					return it->GetTierSize();
				}
			}
		}
		return m_defaultTierSize;
	}
protected:
	TierPriceRangeVector m_tierPriceRangeVector;
	unsigned int m_defaultTierSize;
};

enum HistoricalChartUnit : unsigned char
{
	HCU_DATE,
	HCU_BUSINESS_DAY,
	HCU_CALENDAR_DAY,
	HCU_WEEK,
	HCU_MONTH,
	HCU_YEAR,

	HCU_Count
};

class TD_API HistoricalChartParams
{
public:
//	HistoricalChartParams(const unsigned int& todaysDate, bool dayCount = false, const unsigned int& historyDate = 0, const unsigned char& historyFrequency = CHF_INVALID):
	HistoricalChartParams(const unsigned int& todaysDate,
#ifndef TAKION_NO_OPTIONS
		const bool& future,
#endif
		const unsigned int& historyDate = 0, const unsigned char& unit = HCU_DATE, const unsigned char& historyFrequency = CHF_INVALID):
		m_todaysDate(0),//20130315
//		m_dayCount(dayCount ? historyDate ? historyDate : 1 : 0),
		m_dayCount(unit ? historyDate ? historyDate : 1 : 0),
		m_calculatedDayCount(m_dayCount ? m_dayCount : 0),
//		m_historyDate(dayCount ? 0 : historyDate),
		m_historyDate(unit ? 0 : historyDate),
		m_historyLastLoadedDate(0),
		m_unit(unit),
		m_historyFrequency(CHF_INVALID),
		m_historyFrequencyToUse(CHF_INVALID),
		m_newWeek(false),
		m_newMonth(false),
#ifndef TAKION_NO_OPTIONS
		m_future(future),
#endif
		m_minuteDelta(0),
		m_minuteDeltaToUse(0),
		m_nodesPerDate(0),
		m_nodesPerDateToUse(0),
		m_marketNodesPerDate(0),
		m_marketNodesPerDateToUse(0),
		m_todayNodesPerDate(0),
		m_todayNodesPerDateToUse(0),
		m_todayMarketNodesPerDate(0),
		m_todayMarketNodesPerDateToUse(0)
	{
		SetTodaysDate(todaysDate);
		if(m_dayCount)
		{
			SetHistoryDateByDayCount();
		}
		else if(historyDate && historyDate < m_todaysDate)
		{
			m_calculatedDayCount = TL_BusinessDateDiffByFormattedDates(historyDate, m_todaysDate);
		}
		SetHistoryFrequency(historyFrequency);
	}
	const unsigned char& GetUnit() const{return m_unit;}
	const unsigned int& GetTodaysDate() const{return m_todaysDate;}
//	const unsigned int& GetTodaysHistoryFormatDate() const{return m_todaysHistoryFormatDate;}
	const unsigned int& GetDayCount() const{return m_dayCount;}
	const unsigned int& GetCalculatedDayCount() const{return m_calculatedDayCount;}
	const unsigned int& GetHistoryDate() const{return m_historyDate;}
	const unsigned int& GetHistoryLastLoadedDate() const{return m_historyLastLoadedDate;}
	const unsigned char& GetHistoryFrequency() const{return m_historyFrequency;}
	const unsigned char& GetHistoryFrequencyToUse() const{return m_historyFrequencyToUse;}
	bool SetTodaysDate(const unsigned int& todaysDate)
	{
		if(m_todaysDate != todaysDate)//20130315
		{
			m_todaysDate = todaysDate;
			if(m_dayCount)
			{
				SetHistoryDateByDayCount();
			}
			UpdateNewMonthWeek();
			return true;
		}
		return false;
	}

	bool SetHistoryLastLoadedDate(const unsigned int& historyLastLoadedDate)
	{
		if(m_historyLastLoadedDate != historyLastLoadedDate)
		{
			m_historyLastLoadedDate = historyLastLoadedDate;
			UpdateNewMonthWeek();
			return true;
		}
		return false;
	}

	bool SetHistoryDateByDayCount();
//	bool SetDayCount(const bool& dayCount, const unsigned int& historyDate)
	bool SetDayCount(const unsigned int& historyDate, const unsigned char& unit);
	bool SetHistoryDate(const unsigned int& historyDate)
	{
		if(m_historyDate != historyDate)
		{
			m_historyDate = historyDate;
			return true;
		}
		return false;
	}

	bool SetHistoryFrequency(const unsigned char& historyFrequency);
	const unsigned short& GetMinuteDelta() const{return m_minuteDelta;}
	const unsigned short& GetMinuteDeltaToUse() const{return m_minuteDeltaToUse;}
	const unsigned short& GetNodesPerDate() const{return m_nodesPerDate;}
	const unsigned short& GetNodesPerDateToUse() const{return m_nodesPerDateToUse;}
	const unsigned short& GetMarketNodesPerDate() const{return m_marketNodesPerDate;}
	const unsigned short& GetMarketNodesPerDateToUse() const{return m_marketNodesPerDateToUse;}
	const unsigned short& GetTodayNodesPerDate() const{return m_todayNodesPerDate;}
	const unsigned short& GetTodayNodesPerDateToUse() const{return m_todayNodesPerDateToUse;}
	const unsigned short& GetTodayMarketNodesPerDate() const{return m_todayMarketNodesPerDate;}
	const unsigned short& GetTodayMarketNodesPerDateToUse() const{return m_todayMarketNodesPerDateToUse;}
//	bool SetParams(bool dayCount, const unsigned int& historyDate, const unsigned char& historyFrequency)
	bool SetHistoryParams(const unsigned int& historyDate, const unsigned char& unit, const unsigned char& historyFrequency)
	{
//		const bool ret = SetDayCount(dayCount, historyDate);
		const bool ret = SetDayCount(historyDate, unit);
		return SetHistoryFrequency(historyFrequency) || ret;
	}
//	bool SetParams(const unsigned int& todaysDate, bool dayCount, const unsigned int& historyDate, const unsigned char& historyFrequency)
	bool SetHistoryParams(const unsigned int& todaysDate, const unsigned int& historyDate, const unsigned char& unit, const unsigned char& historyFrequency)
	{
		const bool ret = SetTodaysDate(todaysDate);
//		return SetParams(dayCount, historyDate, historyFrequency) || ret;
		return SetHistoryParams(historyDate, unit, historyFrequency) || ret;
	}
	bool isValid() const
	{
		switch(m_historyFrequency)
		{
			case CHF_MONTH:
			case CHF_WEEK:
			case CHF_DAY:
			case CHF_HOUR:
			case CHF_30MIN:
			case CHF_15MIN:
			case CHF_5MIN:
			case CHF_1MIN:
			return true;

			default:
			return false;
		}
	}
	bool operator==(const HistoricalChartParams& other) const
	{
		return m_historyDate == other.m_historyDate
			&& m_unit == other.m_unit
			&& m_todaysDate == other.m_todaysDate
			&& m_dayCount == other.m_dayCount
			&& m_historyFrequency == other.m_historyFrequency;
	}
	bool operator!=(const HistoricalChartParams& other) const{return !operator==(other);}
	char compare(const HistoricalChartParams& other) const
	{
		return m_dayCount < other.m_dayCount ? -1:
			m_dayCount > other.m_dayCount ? 1:
			m_unit < other.m_unit ? -1:
			m_unit > other.m_unit ? 1:
			m_historyDate < other.m_historyDate ? -1:
			m_historyDate > other.m_historyDate ? 1:
			m_historyFrequency < other.m_historyFrequency ? -1:
			m_historyFrequency > other.m_historyFrequency ? 1:
			m_todaysDate < other.m_todaysDate ? -1:
			m_todaysDate > other.m_todaysDate ? 1:
			0;
	}
	bool operator<(const HistoricalChartParams& other) const
	{
		return m_dayCount != other.m_dayCount ? m_dayCount < other.m_dayCount:
			m_unit != other.m_unit ? m_unit < other.m_unit:
			m_historyDate != other.m_historyDate ? m_historyDate < other.m_historyDate:
			m_historyFrequency != other.m_historyFrequency ? m_historyFrequency < other.m_historyFrequency:
			m_todaysDate < other.m_todaysDate;
	}
	void Reset()
	{
		m_dayCount = 0;
		m_calculatedDayCount = 0;
		m_historyDate = 0;
		m_unit = HCU_DATE;
		m_historyFrequencyToUse = m_historyFrequency = CHF_INVALID;
		m_minuteDeltaToUse = m_minuteDelta = 0;
		m_marketNodesPerDateToUse = m_marketNodesPerDate = m_nodesPerDateToUse = m_nodesPerDate = 0;
		m_todayNodesPerDate =
		m_todayNodesPerDateToUse =
		m_todayMarketNodesPerDate =
		m_todayMarketNodesPerDateToUse = 0;
	}
#ifndef TAKION_NO_OPTIONS
	const bool& isFuture() const{return m_future;}
	void SetFuture(const bool& future)
	{
		if(future != m_future)
		{
			m_future = future;
			UpdateNodesCalculation();
		}
	}
#endif
protected:
	void UpdateNodesCalculation();
	void UpdateTodaysNodes()
	{
		switch(m_historyFrequency)
		{
			case CHF_MONTH:
			m_todayNodesPerDate =
			m_todayNodesPerDateToUse =
			m_todayMarketNodesPerDate =
			m_todayMarketNodesPerDateToUse = m_newMonth ? 1 : 0;
			break;

			case CHF_WEEK:
			m_todayNodesPerDate =
			m_todayNodesPerDateToUse =
			m_todayMarketNodesPerDate =
			m_todayMarketNodesPerDateToUse = m_newWeek ? 1 : 0;
			break;

			case CHF_DAY:
			m_todayNodesPerDate =
			m_todayNodesPerDateToUse =
			m_todayMarketNodesPerDate =
			m_todayMarketNodesPerDateToUse = 1;
			break;


			default:
			m_todayNodesPerDate = m_nodesPerDate;
			m_todayNodesPerDateToUse = m_nodesPerDateToUse;
			m_todayMarketNodesPerDate = m_marketNodesPerDate;
			m_todayMarketNodesPerDateToUse = m_marketNodesPerDateToUse;
			break;
		}
	}
	void UpdateNewMonthWeek()
	{
		if(m_historyLastLoadedDate)
		{
			unsigned short year, month, day;
			U_GetDateTokens(m_historyLastLoadedDate, year, month, day);
			unsigned short todayYear, todayMonth, todayDay;
			U_GetDateTokens(m_todaysDate, todayYear, todayMonth, todayDay);
			if(m_historyLastLoadedDate < m_todaysDate)
			{
				m_newMonth = month != todayMonth;
				unsigned int todayWeekDay = TL_GetDayOfWeek(todayYear, todayMonth, todayDay);
				m_newWeek = TL_GetDayOfWeek(year, month, day) >= todayWeekDay && todayWeekDay > 0 && todayWeekDay < 6; 
			}
			else
			{
				m_newMonth = m_newWeek = false;
			}
		}
		else
		{
			m_newMonth = m_newWeek = false;
		}
		UpdateTodaysNodes();
	}
	unsigned int m_todaysDate;
//	unsigned int m_todaysHistoryFormatDate;
	unsigned int m_dayCount;
	unsigned int m_calculatedDayCount;
	unsigned int m_historyDate;
	unsigned int m_historyLastLoadedDate;
	unsigned char m_unit;
	unsigned char m_historyFrequency;
	unsigned char m_historyFrequencyToUse;
	bool m_newWeek;
	bool m_newMonth;
#ifndef TAKION_NO_OPTIONS
	bool m_future;
#endif
	unsigned short m_minuteDelta;
	unsigned short m_minuteDeltaToUse;
	unsigned short m_nodesPerDate;
	unsigned short m_nodesPerDateToUse;
	unsigned short m_marketNodesPerDate;
	unsigned short m_marketNodesPerDateToUse;

	unsigned short m_todayNodesPerDate;
	unsigned short m_todayNodesPerDateToUse;
	unsigned short m_todayMarketNodesPerDate;
	unsigned short m_todayMarketNodesPerDateToUse;
};

class TD_API HistoricalChart
{
public:
	HistoricalChart(const unsigned __int64& numericSymbol, const unsigned int& todaysDate, const bool& histPrePostMarket):
#ifndef TAKION_NO_OPTIONS
		m_future(TU_IsFutureNumericSymbol(numericSymbol) != 0),
#endif
		m_historicalChartParams(todaysDate
#ifndef TAKION_NO_OPTIONS
			,m_future
#endif
		),
		m_numericSymbol(numericSymbol),
		m_historicalChartRequest(0),
#ifndef TAKION_NO_OPTIONS
		m_priceVolumeRequest(0),
		m_priceVolumeLoaded(false),
		m_priceVolumeMap(nullptr),
#endif
		m_historicalChartLoaded(false),
		m_histPrePostMarket(histPrePostMarket),
		m_packCount(0),
		m_currentMinute(0),
		m_todaysCurrentNode(0xFFFF),
		m_todayAppended(false),
		m_historicalChartTemp(nullptr),
		m_historicalChartIntradayTemp(nullptr),
		m_historicalChartStartDate(0),
		m_prevHistoricalChartStartDate(0),
		m_dateLoading(0),
		m_currentLoadingMinute(0),
		m_dateCount(0)
	{
	}
	~HistoricalChart()
	{
		DestroyHistoricalChartTemp();//DestroyHistoricalChartIntradayTemp();}
#ifndef TAKION_NO_OPTIONS
		DestroyPriceVolumeMap();
#endif
	}
	unsigned int RequestHistoricalChart(const char* symbol, const HistoricalChartParams& historicalChartParams);//, unsigned int dateFrom, char frequency);
//	const unsigned int& GetHistoricalChartRequest() const{return m_historicalChartRequest;}
	const bool& isHistoricalChartLoaded() const{return m_historicalChartLoaded;}
//10/15/2021
	void SetHistoricalChartLoaded(const bool& loaded) const{m_historicalChartLoaded = loaded;}

	const bool& isPrePostMarket() const{return m_histPrePostMarket;}
	bool SetPrePostMarket(bool prePostMarket);

	void AppendTodaysEmptyNodes();
	void RemoveTodaysNodes();
	void ResetTodaysNodes();
	bool FillTodaysChart(const Security* stock);

	void NextDayStarted(
#ifndef TAKION_NO_OPTIONS
		const FutureHistoricalIntraDayTick* yesterdayHistoricalChart, unsigned short pointCount, unsigned short mergedMinutes, unsigned int date
#endif
	);

	void ClearChart()
	{
		m_historicalChart.clear();
		m_historicalChart.reserve(0);
		m_historicalChartStartDate = 0;
		m_prevHistoricalChartStartDate = 0;
		m_packCount = 0;
		m_historicalChartRequest = 0;
		m_historicalChartLoaded = false;
#ifndef TAKION_NO_OPTIONS
		m_priceVolumeRequest = 0;
//		m_priceVolumeLoaded = false;//Done in DestroyPriceVolumeMap
		DestroyPriceVolumeMap();
#endif
		m_currentMinute = 0;
		m_todaysCurrentNode = 0xFFFF;
		m_lastHistoricalPoint.Reset();
		m_dateLoading = 0;
		m_currentLoadingMinute = 0;
		m_dateCount = 0;

		DestroyHistoricalChartTemp();
	}
	void SetHistoricalChartRequestId(const unsigned int& requesId) const
	{
		m_historicalChartRequest = requesId;
		if(m_historicalChartRequest)
		{
			m_historicalChartLoaded = false;
			m_packCount = 0;
		}
	}
#ifndef TAKION_NO_OPTIONS
	typedef std::map<Price, unsigned __int64> PriceVolumeMap;
	unsigned int RequestFutureHistoricalPriceVolume();
	const unsigned int& GetPriceVolumeRequestId() const{return m_priceVolumeRequest;}
	void SetPriceVolumeRequestId(const unsigned int& requesId) const
	{
		m_priceVolumeRequest = requesId;
		if(m_priceVolumeRequest)
		{
			m_priceVolumeLoaded = false;
//			m_packCount = 0;
		}
	}
	const bool& isPriceVolumeLoaded() const{return m_priceVolumeLoaded;}
	void SetPriceVolumeLoaded(const bool& loaded) const{m_priceVolumeLoaded = loaded;}
	const PriceVolumeMap* GetPriceVolumeMap() const{return m_priceVolumeMap;}
	void DestroyPriceVolumeMap();
	void ClearPriceVolumeMap();
	void FutureMarketDataDisconnected();
#endif

	unsigned short GetHistoricalChartSize() const{return (unsigned short)m_historicalChart.size();}
//	unsigned short GetHistoricalChartSizePlusDateCount() const{return (unsigned short)m_historicalChart.size() + m_dateCount;}
	const Security::ChartPointVector& GetHistoricalChart() const{return m_historicalChart;}

	const unsigned int& GetHistoricalChartRequestId() const{return m_historicalChartRequest;}
	const unsigned short& GetPackCount()const{return m_packCount;}

	const unsigned __int64& GetNumericSymbol() const{return m_numericSymbol;}
	const char* GetSymbol() const{return (const char*)&m_numericSymbol;}
	const HistoricalChartParams& GetHistoricalChartParams() const{return m_historicalChartParams;}
	const unsigned short& GetNodesPerDate() const{return m_historicalChartParams.GetNodesPerDate();}
	const unsigned short& GetNodesPerDateToUse() const{return m_historicalChartParams.GetNodesPerDateToUse();}
	const unsigned short& GetMarketNodesPerDate() const{return m_historicalChartParams.GetMarketNodesPerDate();}
	const unsigned short& GetMarketNodesPerDateToUse() const{return m_historicalChartParams.GetMarketNodesPerDateToUse();}
	bool SetHistoricalChartParams(const HistoricalChartParams& other)
	{
		if(m_historicalChartParams != other)
		{
			m_historicalChartParams = other;
			return true;
		}
		return false;
	}

	void SetHistoryFrequency(const unsigned char& historyFrequency);
	void PrintServerDisconnected();
	void ProcessHistoricalChartSnapshot(const unsigned char pointSize, const unsigned short pointCount, const HistoricalTick* chartPoint, const unsigned int requestId, const unsigned char more);
	void ProcessHistoricalIntradayChartSnapshot(const unsigned char pointSize, const unsigned short pointCount, const unsigned int date, const HistoricalIntraDayTick* chartPoint, const unsigned int requestId, const unsigned char more);
	const unsigned int& GetHistoricalChartStartDate() const{return m_historicalChartStartDate;}
	const unsigned int& GetPrevHistoricalChartStartDate() const{return m_prevHistoricalChartStartDate;}
	const unsigned int& GetDayCount() const{return m_historicalChartParams.GetDayCount();}
	const unsigned int& GetCalculatedDayCount() const{return m_historicalChartParams.GetCalculatedDayCount();}
	const unsigned short& GetDateCount() const{return m_dateCount;}
	const unsigned int& GetHistoryDate() const{return m_historicalChartParams.GetHistoryDate();}
	const unsigned int& GetTodaysDate() const{return m_historicalChartParams.GetTodaysDate();}
	void DoFinalizeHistoricalChart();
	bool SetCurrentMinute(const unsigned short& currentMinute)//, bool force)
	{
		if(m_currentMinute != currentMinute)// || force)
		{
			m_currentMinute = currentMinute;
			UpdateTodayAppended();
			return true;
		}
		return false;
	}
	bool SetTodayAppended(const bool& appended)
	{
		if(m_todayAppended != appended)
		{
			m_todayAppended = appended;
			UpdateTodayAppended();
			return true;
		}
		return false;
	}
	const unsigned short& GetCurrentMinute() const{return m_currentMinute;}
	const unsigned short& GetTodaysCurrentNode() const{return m_todaysCurrentNode;}
	const bool& isTodayAppended() const{return m_todayAppended;}
	bool AddPrint(const Price& price, unsigned int size, unsigned char printFlags)
	{
		if(m_todaysCurrentNode && m_todaysCurrentNode < (unsigned short)m_historicalChart.size())
		{
			m_historicalChart[m_todaysCurrentNode].AddPrint(price, size, printFlags);
			return true;
		}
		return false;
	}
/*
	void SetTodaysCurrentNode(unsigned short todaysCurrentNode)
	{
		m_todaysCurrentNode = todaysCurrentNode;
	}
*/
//	bool SetParams(bool dayCount, const unsigned int& historyDate, const unsigned char& historyFrequency)
	bool SetHistoryParams(const unsigned int& historyDate, const unsigned char& unit, const unsigned char& historyFrequency)
	{
//		return m_historicalChartParams.SetParams(dayCount, historyDate, historyFrequency);
		return m_historicalChartParams.SetHistoryParams(historyDate, unit, historyFrequency);
	}
//	bool SetParams(const unsigned int& todaysDate, bool dayCount, const unsigned int& historyDate, const unsigned char& historyFrequency)
	bool SetHistoryParams(const unsigned int& todaysDate, const unsigned int& historyDate, const unsigned char& unit, const unsigned char& historyFrequency)
	{
//		return m_historicalChartParams.SetParams(todaysDate, dayCount, historyDate, historyFrequency);
		return m_historicalChartParams.SetHistoryParams(todaysDate, historyDate, unit, historyFrequency);
	}
	const unsigned char& GetFrequency() const{return m_historicalChartParams.GetHistoryFrequency();}
	bool operator==(const HistoricalChart& other) const{return m_historicalChartParams == other.m_historicalChartParams;}
	bool operator!=(const HistoricalChart& other) const{return !operator==(other);}
	bool operator<(const HistoricalChart& other) const{return m_historicalChartParams < other.m_historicalChartParams;}
	char compare(const HistoricalChart& other) const
	{
		char ret = U_CompareUIntAsString(m_numericSymbol, other.m_numericSymbol);
		return ret ? ret : m_historicalChartParams.compare(other.m_historicalChartParams);
	}

	static const unsigned short dayStartMinute;//240 = 4AM or 0 for Futures
	static const unsigned short dayEndMinute;//1200 = 8PM or 1440 for Futures
	static const unsigned short marketStartMinute;//570 = 9:30AM;
	static const unsigned short marketEndMinute;//960 = 4PM;
#ifndef TAKION_NO_OPTIONS
	static const unsigned short dayStockStartMinute;//240 = 4AM
	static const unsigned short dayStockEndMinute;//1200 = 8PM

	const bool& isFuture() const{return m_future;}
	const unsigned short& GetDayStartMinute() const{return m_future ? dayStartMinute : dayStockStartMinute;}
	const unsigned short& GetDayEndMinute() const{return m_future ? dayEndMinute : dayStockEndMinute;}
	const unsigned short& GetStartMinute() const{return m_future ? dayStartMinute : m_histPrePostMarket ? dayStockStartMinute : marketStartMinute;}
	const unsigned short& GetEndMinute() const{return m_future ? dayEndMinute : m_histPrePostMarket ? dayStockEndMinute : marketEndMinute;}
	void AppendYesterdayChart(const FutureHistoricalIntraDayTick* yesterdayChart, unsigned short pointCount, unsigned short mergedMinutes, unsigned int date);//dates in decimal format yyyymmdd

	void ProcessFutureHistoricalChartSnapshot(const unsigned char pointSize, const unsigned short pointCount, const FutureHistoricalTick* chartPoint, const unsigned int requestId, const unsigned char more);
	void ProcessFutureHistoricalIntradayChartSnapshot(const unsigned char pointSize, const unsigned short pointCount, const unsigned int date, const FutureHistoricalIntraDayTick* chartPoint, const unsigned int requestId, const unsigned char more);
	void ProcessFuturePriceVolumeSnapshot(const unsigned char pointSize, const unsigned short pointCount, const FutureHistoricalPriceVolumeTick* priceVolumeToken, const unsigned int requestId, const unsigned char more);
#else
	const unsigned short& GetDayStartMinute() const{return dayStartMinute;}
	const unsigned short& GetDayEndMinute() const{return dayEndMinute;}
	const unsigned short& GetStartMinute() const{return m_histPrePostMarket ? dayStartMinute : marketStartMinute;}
	const unsigned short& GetEndMinute() const{return m_histPrePostMarket ? dayEndMinute : marketEndMinute;}
#endif

	const ChartPoint& GetLastHistoricalPoint() const{return m_lastHistoricalPoint;}
protected:

	void DoAppendTodaysEmptyNodes();
	void UpdateTodayAppended()
	{
		if(m_todayAppended)
		{
			UpdateCurrentMinute();
		}
		else
		{
			m_todaysCurrentNode = 0xFFFF;
		}
	}
	void UpdateCurrentMinute();

#ifndef TAKION_NO_OPTIONS
	bool m_future;
#endif

	HistoricalChartParams m_historicalChartParams;

	unsigned __int64 m_numericSymbol;

	mutable unsigned int m_historicalChartRequest;
	mutable bool m_historicalChartLoaded;

#ifndef TAKION_NO_OPTIONS
	mutable unsigned int m_priceVolumeRequest;
	mutable bool m_priceVolumeLoaded;
	PriceVolumeMap* m_priceVolumeMap;
#endif
	bool m_histPrePostMarket;
	mutable unsigned short m_packCount;

	unsigned short m_currentMinute;
	unsigned short m_todaysCurrentNode;
	bool m_todayAppended;

	Security::ChartPointVector m_historicalChart;
	Security::ChartPointVector* m_historicalChartTemp;
	Security::ChartPointVector* m_historicalChartIntradayTemp;
	ChartPoint m_lastHistoricalPoint;
	unsigned int m_historicalChartStartDate;
	unsigned int m_prevHistoricalChartStartDate;//to compare with m_historicalChartStartDate to find out if an additional request changed the start date.
	unsigned int m_dateLoading;
	unsigned short m_currentLoadingMinute;
	unsigned short m_dateCount;
//	TempPointVector* m_historicalChartTemp;
//	TempPointVector* m_historicalChartIntradayTemp;
	void FinalizeHistoricalChart();
	void DestroyHistoricalChartTemp();
	void DestroyHistoricalChartIntradayTemp();
};

class TD_API FrequencyChartCollection
{
public:
	typedef CMap<unsigned char, const unsigned char&, const HistoricalChart*, const HistoricalChart* const&> FrequencyHistoricalChartMap;
	FrequencyChartCollection(const unsigned __int64& numericSymbol):m_numericSymbol(numericSymbol){}
	~FrequencyChartCollection(){ClearAndDestroy();}
	const unsigned __int64& GetNumericSymbol() const{return m_numericSymbol;}
//	const HistoricalChart* AddHistoricalChart(const HistoricalChart* chart);//returns previous chart if replaced; returns chart if not replaced; returns nullptr if added without replacing
	bool AddHistoricalChart(HistoricalChart*& chart);//places previous chart in the chart argument; returns returns true if a request needs to be sent
	const HistoricalChart* RemoveHistoricalChart(unsigned char frequency);
	void RemoveAndDestroyHistoricalChart(unsigned char frequency, const HistoricalChart* replaceWith);
	void ClearAndDestroy();
	TakionIterator* CreateIterator() const;
	const HistoricalChart* FindHistoricalChart(unsigned char frequency) const
	{
		const FrequencyHistoricalChartMap::CPair* found = m_frequencyHistoricalChartMap.PLookup(frequency);
		return found ? found->value : nullptr;
	}
	bool isEmpty() const{return m_frequencyHistoricalChartMap.IsEmpty() == TRUE;}
	unsigned int GetCount() const{return (unsigned int)m_frequencyHistoricalChartMap.GetCount();}
	const FrequencyHistoricalChartMap& GetFrequencyHistoricalChartMap() const{return m_frequencyHistoricalChartMap;}
protected:
	FrequencyHistoricalChartMap m_frequencyHistoricalChartMap;
	unsigned __int64 m_numericSymbol;
};

class TMessageHistoricalChart : public Message
{
public:
	const HistoricalChart* m_historicalChart;
protected:
	TMessageHistoricalChart(const HistoricalChart* historicalChart, unsigned short type, unsigned short length):Message(type, length), m_historicalChart(historicalChart){}
};

class TMsgHistoricalChartPackLoaded : public TMessageHistoricalChart
{
public:
	TMsgHistoricalChartPackLoaded(const HistoricalChart* historicalChart):TMessageHistoricalChart(historicalChart, M_HISTORICAL_CHART_PACK_LOADED, sizeof(TMsgHistoricalChartPackLoaded)){}
};

class TMsgHistoricalChartDelete : public TMessageHistoricalChart
{
public:
	TMsgHistoricalChartDelete(const HistoricalChart* historicalChart, const HistoricalChart* replaceWith):TMessageHistoricalChart(historicalChart, M_HISTORICAL_CHART_DELETE, sizeof(TMsgHistoricalChartDelete)), m_replaceWith(replaceWith){}
	const HistoricalChart* m_replaceWith;
};

#ifndef TAKION_NO_OPTIONS
class TMsgHistoricalChartPriceVolumePackLoaded : public TMessageHistoricalChart
{
public:
	TMsgHistoricalChartPriceVolumePackLoaded(const HistoricalChart* historicalChart):TMessageHistoricalChart(historicalChart, M_HISTORICAL_CHART_PRICE_VOLUME_PACK_LOADED, sizeof(TMsgHistoricalChartPackLoaded)){}
};
#endif

class TMsgTakionText : public Message
{
//public:
//	unsigned short m_textLength;
protected:
	TMsgTakionText(//const unsigned short& textLength,
		const unsigned short& type,
		const unsigned short& length):
		Message(type, length)
//		m_textLength(textLength)
	{}
};

class TMsgTakionClientText : public TMsgTakionText
{
public:
	TMsgTakionClientText(const unsigned short& textLength):
//		const unsigned char& clientId,
//		const unsigned short& length):
		TMsgTakionText(TM_TAKION_CLIENT_TEXT_MESSAGE, sizeof(TMsgTakionClientText) + textLength)
	{}
};

class TMsgTakionClientTextError : public Message
{
public:
	TMsgTakionClientTextError(//const unsigned char& clientId,
		const unsigned char& errorCode,
		const unsigned short& charCount,
		const unsigned short& length):
		Message(TM_TAKION_CLIENT_TEXT_ERROR, sizeof(TMsgTakionClientTextError) + length),
//		m_clientId(clientId),
		m_errorCode(errorCode),
		m_charCount(charCount)
	{
	}
//	unsigned char m_clientId;
	unsigned char m_errorCode;
	unsigned short m_charCount;
};
////////

class TMsgTakionFix : public Message
{
public:
	unsigned int m_fixLength;
	unsigned int m_fixVersion;
	unsigned short m_fixType;
protected:
	TMsgTakionFix(const unsigned int& fixLength,
		const unsigned int& fixVersion,
		const unsigned short& fixType,
		const unsigned short& type,
		const unsigned short& length):
		Message(type, length),
		m_fixLength(fixLength),
		m_fixVersion(fixVersion),
		m_fixType(fixType)
	{}
};

class TMsgTakionClientFixBase : public TMsgTakionFix
{
public:
	unsigned char m_clientId;
protected:
	TMsgTakionClientFixBase(const unsigned int& fixLength,
		const unsigned int& fixVersion,
		const unsigned short& fixType,
		const unsigned char& clientId,
		const unsigned short& type,
		const unsigned short& length):
		TMsgTakionFix(fixLength, fixVersion, fixType, type, length),
		m_clientId(clientId)
	{}
};

class TMsgTakionClientFix : public TMsgTakionClientFixBase
{
public:
	TMsgTakionClientFix(const unsigned int& fixLength,
		const unsigned int& fixVersion,
		const unsigned short& fixType,
		const unsigned char& clientId,
		const unsigned short& length):
		TMsgTakionClientFixBase(fixLength, fixVersion, fixType, clientId, TM_TAKION_CLIENT_FIX_MESSAGE, sizeof(TMsgTakionClientFix) + length)
	{}
};

class TMsgTakionClientFixError : public Message
{
public:
	TMsgTakionClientFixError(const unsigned char& clientId, const unsigned char& errorCode, const unsigned short& charCount, const unsigned short& length):
		Message(TM_TAKION_CLIENT_FIX_ERROR, sizeof(TMsgTakionClientFixError) + length),
		m_clientId(clientId),
		m_errorCode(errorCode),
		m_charCount(charCount)
	{
	}
	unsigned char m_clientId;
	unsigned char m_errorCode;
	unsigned short m_charCount;
};

class TMsgTakionClientFixControlSumError : public TMsgTakionClientFixBase
{
public:
	TMsgTakionClientFixControlSumError(const unsigned int& fixLength,
		const unsigned int& fixVersion,
		const unsigned short& fixType,
		const unsigned char& clientId,
		const unsigned char& expectedControlSum,
		const unsigned short& controlSum,
		const unsigned short& length):
		TMsgTakionClientFixBase(fixLength, fixVersion, fixType, clientId, TM_TAKION_CLIENT_FIX_CONTROL_SUM_ERROR, sizeof(TMsgTakionClientFixControlSumError) + length),
		m_expectedControlSum(expectedControlSum),
		m_controlSum(controlSum)
	{
	}
	const unsigned char m_expectedControlSum;
	const unsigned short m_controlSum;
};

class TMsgServer : public Message
{
public:
	unsigned int m_clientIp;
	unsigned short m_clientPort;
	unsigned short m_serverPort;
protected:
	TMsgServer(const unsigned int& clientIp,
		const unsigned short& clientPort,
		const unsigned short& serverPort,
		const unsigned short& type,
		const unsigned short& length):
	Message(type, length),
	m_clientIp(clientIp),
	m_clientPort(clientPort),
	m_serverPort(serverPort)
	{}
};
/*
class TMsgTakionServerTextError : public TMsgServer
{
public:
	TMsgTakionServerTextError(const unsigned int& clientIp,
		const unsigned short& clientPort,
		const unsigned short& serverPort,
		const unsigned char& errorCode,
		const unsigned short& charCount,
		const unsigned short& length):
		TMsgServer(clientIp, clientPort, serverPort, TM_TAKION_SERVER_TEXT_ERROR, sizeof(TMsgTakionServerTextError) + length),
		m_errorCode(errorCode),
		m_charCount(charCount)
	{
	}
	unsigned char m_errorCode;
	unsigned short m_charCount;
};

class TMsgTakionServerTextBase : public TMsgTakionText
{
public:
	unsigned int m_clientIp;
	unsigned short m_clientPort;
	unsigned short m_serverPort;
protected:
	TMsgTakionServerTextBase(
		const unsigned int& clientIp,
		const unsigned short& clientPort,
		const unsigned short& serverPort,
		const unsigned short& type,
		const unsigned short& length):
		TMsgTakionText(type, length),
		m_clientIp(clientIp),
		m_clientPort(clientPort),
		m_serverPort(serverPort)
	{}
};

class TMsgTakionServerText : public TMsgTakionServerTextBase
{
public:
	TMsgTakionServerText(const unsigned short& textLength,
		const unsigned int& clientIp,
		const unsigned short& clientPort,
		const unsigned short& serverPort):
//		const unsigned short& length):
		TMsgTakionServerTextBase(clientIp, clientPort, serverPort, TM_TAKION_SERVER_TEXT_MESSAGE, sizeof(TMsgTakionServerText) + textLength)
	{}
};
*/
////////

class TMsgTakionServerFixError : public TMsgServer
{
public:
	TMsgTakionServerFixError(const unsigned int& clientIp,
		const unsigned short& clientPort,
		const unsigned short& serverPort,
		const unsigned char& errorCode,
		const unsigned short& charCount,
		const unsigned short& length):
		TMsgServer(clientIp, clientPort, serverPort, TM_TAKION_SERVER_FIX_ERROR, sizeof(TMsgTakionServerFixError) + length),
		m_errorCode(errorCode),
		m_charCount(charCount)
	{
	}
	unsigned char m_errorCode;
	unsigned short m_charCount;
};

class TMsgTakionServerFixBase : public TMsgTakionFix
{
public:
	unsigned int m_clientIp;
	unsigned short m_clientPort;
	unsigned short m_serverPort;
protected:
	TMsgTakionServerFixBase(const unsigned int& fixLength,
		const unsigned int& fixVersion,
		const unsigned short& fixType,
		const unsigned int& clientIp,
		const unsigned short& clientPort,
		const unsigned short& serverPort,
		const unsigned short& type,
		const unsigned short& length):
		TMsgTakionFix(fixLength, fixVersion, fixType, type, length),
		m_clientIp(clientIp),
		m_clientPort(clientPort),
		m_serverPort(serverPort)
	{}
};

class TMsgTakionServerFixControlSumError : public TMsgTakionServerFixBase
{
public:
	TMsgTakionServerFixControlSumError(const unsigned int& fixLength,
		const unsigned int& fixVersion,
		const unsigned short& fixType,
		const unsigned int& clientIp,
		const unsigned short& clientPort,
		const unsigned short& serverPort,
		const unsigned short& controlSum,
		const unsigned char& expectedControlSum,
		const unsigned short& length):
		TMsgTakionServerFixBase(fixLength, fixVersion, fixType, clientIp, clientPort, serverPort, TM_TAKION_SERVER_FIX_CONTROL_SUM_ERROR, sizeof(TMsgTakionServerFixControlSumError) + length),
		m_controlSum(controlSum),
		m_expectedControlSum(expectedControlSum)
	{
	}
	const unsigned short m_controlSum;
	const unsigned char m_expectedControlSum;
};

class TMsgTakionServerFix : public TMsgTakionServerFixBase
{
public:
	TMsgTakionServerFix(const unsigned int& fixLength,
		const unsigned int& fixVersion,
		const unsigned short& fixType,
		const unsigned int& clientIp,
		const unsigned short& clientPort,
		const unsigned short& serverPort,
		const unsigned short& length):
		TMsgTakionServerFixBase(fixLength, fixVersion, fixType, clientIp, clientPort, serverPort, TM_TAKION_SERVER_FIX_MESSAGE, sizeof(TMsgTakionServerFix) + length)
	{}
};

class TMsgTakionServer : public TMsgServer
{
public:
	TMsgTakionServer(const unsigned int& clientIp,
		const unsigned short& clientPort,
		const unsigned short& serverPort,
		const unsigned short& length):

		TMsgServer(clientIp, clientPort, serverPort, TM_TAKION_SERVER_MESSAGE, sizeof(TMsgTakionServer) + length)
	{}
};

template<class T>
class TMsgAdditionalInfo : public Message
{
public:
	typedef T ValueType;
	ValueType m_value;
protected:
	TMsgAdditionalInfo(const ValueType& value, const unsigned short& type):Message(type, sizeof(TMsgAdditionalInfo<T>)), m_value(value){}
};

class TMsgAdditionalInfoUChar : public TMsgAdditionalInfo<unsigned char>
{
public:
	TMsgAdditionalInfoUChar(const ValueType& value):TMsgAdditionalInfo(value, TM_ADDITIONAL_DATA_UCHAR){}
};

class TMsgAdditionalInfoUInt : public TMsgAdditionalInfo<unsigned int>
{
public:
	TMsgAdditionalInfoUInt(const ValueType& value):TMsgAdditionalInfo(value, TM_ADDITIONAL_DATA_UINT){}
};

//TS->TSClient Sent to all Firm's clients, Used to distribute untradeable stocks and status change
class TMsgFirmUntradeableStatusUpdate : public TMessageTime//TMsgFirmPosition
{
public:
	TMsgFirmUntradeableStatusUpdate(const TraderIdType& traderId,//const char* const& traderId,
		const char* const& clearingAccountName,
		const char* const& symbol,
		const char* const& firmId,
		const unsigned int& timestamp = 0,
		const unsigned char& untradeable = 0,
		const unsigned int& ipAddress = 0):
//		TMsgFirmPosition(clearingAccountName, symbol, firmId, timestamp, TS_UNTRADEABLE_STATUS_UPDATE, sizeof(TMsgFirmUntradeableStatusUpdate)),
		TMessageTime(timestamp, TS_UNTRADEABLE_STATUS_UPDATE, sizeof(TMsgFirmUntradeableStatusUpdate)),
		m_untradeable(untradeable),
		m_ipAddress(ipAddress)
	{
//		U_CopyAndPad(m_traderId, sizeof(m_traderId), traderId, '\0', true);
		*(TraderIdType*)m_traderId = traderId;
		m_traderId[sizeof(m_traderId) - 1] = '\0';

		U_CopyAndPad(m_clearingAccountName, sizeof(m_clearingAccountName), clearingAccountName, '\0', true);
		U_CopyAndPad(m_symbol, sizeof(m_symbol), symbol, '\0');
		U_CopyAndPad(m_firmId, sizeof(m_firmId), firmId, '\0', true);
	}
	TMsgFirmUntradeableStatusUpdate(const unsigned int& traderId = 0, const unsigned __int64& clearingNamePart1 = 0, const unsigned __int64& clearingNamePart2 = 0, const unsigned __int64& symbol = 0, const unsigned int& firmId = 0, const unsigned int& timestamp = 0, const unsigned char& untradeable = 0, const unsigned int& ipAddress = 0):
//		TMsgFirmPosition(clearingNamePart1, clearingNamePart2, symbol, firmId, timestamp, TS_UNTRADEABLE_STATUS_UPDATE, sizeof(TMsgFirmUntradeableStatusUpdate)),
		TMessageTime(timestamp, TS_UNTRADEABLE_STATUS_UPDATE, sizeof(TMsgFirmUntradeableStatusUpdate)),
		m_untradeable(untradeable),
		m_ipAddress(ipAddress)
	{
		*(unsigned int*)m_traderId = traderId;
		m_traderId[sizeof(unsigned int)] = '\0';

		*(unsigned __int64*)m_clearingAccountName = clearingNamePart1;
		*(unsigned __int64*)(m_clearingAccountName + sizeof(unsigned __int64)) = clearingNamePart2;
		*(unsigned __int64*)m_symbol = symbol;
		*(unsigned int*)m_firmId = firmId;
		m_firmId[sizeof(unsigned int)] = '\0';
	}
	char m_clearingAccountName[MAX_ACCOUNT_SIZE];
	char m_symbol[MAX_SYMBOL_SIZE];
	char m_firmId[MAX_FIRM_ID_SIZE];
//	bool m_untradeable;
	unsigned char m_untradeable;//Untradeable Status. 0 - tradeable; 1 - untradeable full; 2 - untradeable partial (can trade within borrowed size).
	char m_traderId[MAX_TRADER_ID_SIZE];
	unsigned int m_ipAddress;
};



/*
class TMsgFixServer : public TMsgServer
{
public:
	TMsgFixServer(const unsigned int& clientIp,
		const unsigned short& clientPort,
		const unsigned short& serverPort,
		const unsigned short& length):
	TMsgServer(clientIp, clientPort, serverPort, TM_TAKION_SERVER_FIX_MESSAGE, sizeof(TMsgFixServer) + length)
	{}
};
*/
/*
enum TakionMessageFormat : unsigned char
{
	MF_TAKION,
	MF_FIX,

	MF_Count
};
*/

class CalcIndexKey
{
public:
	CalcIndexKey(const unsigned __int64& symbol, const unsigned char& type):m_symbol(symbol),m_type(type){}
	const unsigned __int64& GetSymbol() const{return m_symbol;}
	const unsigned char& GetType() const{return m_type;}
	bool operator==(const CalcIndexKey& other) const{return m_symbol == other.m_symbol && m_type == other.m_type;}
	bool operator!=(const CalcIndexKey& other) const{return !operator==(other);}
	bool operator<(const CalcIndexKey& other) const{return U_UIntLessAsString(m_symbol, other.m_symbol) || m_symbol == other.m_symbol && m_type < other.m_type;}
	bool operator>(const CalcIndexKey& other) const{return U_UIntGreaterAsString(m_symbol, other.m_symbol) || m_symbol == other.m_symbol && m_type > other.m_type;}
	bool operator<=(const CalcIndexKey& other) const{return !operator>(other);}
	bool operator>=(const CalcIndexKey& other) const{return !operator<(other);}
	size_t GetHashValue() const{return (size_t)m_symbol | m_type;}
//	operator size_t() const{return (size_t)m_symbol | m_type;}
protected:
	unsigned __int64 m_symbol;
	unsigned char m_type;
};

template<> inline size_t std::hash_value(const CalcIndexKey& key)
{
	return key.GetHashValue();// ^ _HASH_SEED;//(((key.GetDollars() << 16) | key.GetDollarFraction()) ^ _HASH_SEED);
}

class TD_API CalcIndexComponent
{
public:
	virtual ~CalcIndexComponent(){}
	virtual const unsigned __int64& GetNumericSymbol() const = 0;
	virtual const SignedPrice& GetMultiplier() const = 0;
	virtual bool SetMultiplier(const SignedPrice& multiplier) = 0;
	virtual unsigned char GetType() const{return 0xFF;}
protected:
	CalcIndexComponent(){}
};

class ConnectionBase;
class ActiveConnection;
class TakionServer;
class TakionClientData;
class TextProcessor;

#ifdef __cplusplus
extern "C"
{
#endif

const FrequencyChartCollection* WINAPI TD_FindHistoricalChartSymbol(const unsigned __int64& numericSymbol);
TakionIterator* WINAPI TD_CreateHistoricalChartSymbolIterator();
const FrequencyChartCollection* WINAPI TD_GetNextHistoricalChartSymbol(TakionIterator* iterator);
const HistoricalChart* WINAPI TD_GetNextFrequencyHistoricalChart(TakionIterator* frequencyHistoricalChartIterator);

TakionIterator* WINAPI TD_CreateOptionQueueIterator();
unsigned __int64 WINAPI TD_GetNextOptionQueueItem(TakionIterator* iterator,
	unsigned __int64& optionBlock,
	unsigned int& dateItemCreated,//In shift format
	unsigned int& millisecondItemCreated,
	unsigned int& ordinal,
	bool& snapshotsOnly);

bool WINAPI TD_AddStreamConnection(const ConnectionBase& connectionBase, const unsigned char format);
/*
bool WINAPI TD_AddStreamConnection(const char* name,
	const char* ip,
	unsigned short port,
	const char* ip2,
	unsigned short port2,
	unsigned char connectionDataType,
	unsigned int receiveBuffer = 0xFFFFFFFF,
	unsigned int sendBuffer = 0xFFFFFFFF,
	unsigned int reconnectSeconds = 5,
	unsigned int reconnectTries = 0,
	unsigned int maxReconnectTries = 0xFFFFFFFF,
	const char* bindIp = nullptr,
	unsigned short bindPort = 0,
	const char* bindIp2 = nullptr,
	unsigned short bindPort2 = 0,
	const char* loginId = "",
	const char* password = "");
*/

Security* WINAPI TD_ObtainStock(const char* symbol, bool subscribe);//Call TD_ReleaseStock after the returned Security* is no longer in use
Security* WINAPI TD_ObtainStockByNumericSymbol(const unsigned __int64& numSymbol, bool subscribe);//Call TD_ReleaseStock after the returned Security* is no longer in use
Security* WINAPI TD_FindStock(const char* symbol);//Call TD_ReleaseStock after the returned Security* is no longer in use
Security* WINAPI TD_FindStockByNumericSymbol(const unsigned __int64& numSymbol);//Call TD_ReleaseStock after the returned Security* is no longer in use
void WINAPI TD_IncrementStockUnsubscribable(const Security* stock);//Call TD_ReleaseStock after the Security* is no longer in use
void WINAPI TD_ReleaseStock(const Security* stock, bool unsubscribeImmediately = false);
Security* WINAPI TD_FindStockNoUseCount(const char* symbol);//DO NOT Call TD_ReleaseStock to release the returned Security*
Security* WINAPI TD_FindStockByNumericSymbolNoUseCount(const unsigned __int64& symbol);//DO NOT Call TD_ReleaseStock to release the returned Security*
unsigned int WINAPI TD_GetStockCount();
unsigned int WINAPI TD_GetLoadedStockCount();
unsigned int WINAPI TD_GetIdleStockCount();
unsigned int WINAPI TD_GetIdleSortableEquityCount();

void WINAPI TD_LockNonTradableStockStorageInquiryWait();
bool WINAPI TD_LockNonTradableStockStorageInquiry();
void WINAPI TD_UnlockNonTradableStockStorageInquiry();

void WINAPI TD_LockTradableStockStorageInquiryWait();
bool WINAPI TD_LockTradableStockStorageInquiry();
void WINAPI TD_UnlockTradableStockStorageInquiry();

TakionIterator* WINAPI TD_CreateNonTradableStockIterator();
unsigned int WINAPI TD_GetNonTradableStockCount();
TakionIterator* WINAPI TD_CreateTradableStockIterator();
unsigned int WINAPI TD_GetTradableStockCount();

void WINAPI TD_SimulateNextDayStarted();

void WINAPI TD_LogSecurityState(const Security* security);
void WINAPI TD_LogSecurityLevel2SideInThread(const Security* security, TakionIterator* iterator, const bool bid, const Price& price);

unsigned int WINAPI TD_GetWorkerThreadCount();
unsigned int WINAPI TD_GetWorkerThreadIDs(unsigned int* threadIdArray, unsigned int threadIdArraySize);

void WINAPI TD_GetGtcOrdersFilePath(std::string& filePath);
void WINAPI TD_GetGtcSpidersFilePath(std::string& filePath);
void WINAPI TD_GetSimulatedPositionsFilePath(std::string& filePath, const char* accountId);

#ifndef TAKION_NO_OPTIONS
void WINAPI TD_SimulateFutureSessionEnded();

void WINAPI TD_GetFutureGtcOrdersFilePath(std::string& filePath);
void WINAPI TD_GetFutureGtcSpidersFilePath(std::string& filePath);

void WINAPI TD_SetAllFuturePhantomPositionsFlat();

Security* WINAPI TD_FindFuture(const char* symbol);
Security* WINAPI TD_FindFutureByNumericSymbol(const unsigned __int64& symbol);
Security* WINAPI TD_FindFutureNoUseCount(const char* symbol);
Security* WINAPI TD_FindFutureByNumericSymbolNoUseCount(const unsigned __int64& symbol);
Security* WINAPI TD_ObtainFuture(const char* symbol, bool subscribe);//Call TD_ReleaseStock after the returned Security* is no longer in use
Security* WINAPI TD_ObtainFutureByNumericSymbol(const unsigned __int64& numSymbol, bool subscribe);//Call TD_ReleaseStock after the returned Security* is no longer in use
unsigned int WINAPI TD_GetFutureCount();
unsigned int WINAPI TD_GetLoadedFutureCount();
unsigned int WINAPI TD_GetIdleFutureCount();

Security* WINAPI TD_ObtainStockOrFuture(const char* symbol, bool subscribe);//Call TD_ReleaseStock after the returned Security* is no longer in use
Security* WINAPI TD_ObtainStockOrFutureByNumericSymbol(const unsigned __int64& numSymbol, bool subscribe);//Call TD_ReleaseStock after the returned Security* is no longer in use

unsigned int WINAPI TD_GetOptionIdleMilliseconds();
void WINAPI TD_SetOptionIdleMilliseconds(unsigned int milliseconds);

unsigned int WINAPI TD_GetFutureIdleMilliseconds();
void WINAPI TD_SetFutureIdleMilliseconds(unsigned int milliseconds);

Account* WINAPI TD_GetFutureDefaultAccount();

void WINAPI TD_SetOptionUpdateOnIdle(bool optionUpdateOnIdle);
unsigned int WINAPI TD_GetUnderlierIdleMilliseconds();
void WINAPI TD_SetUnderlierIdleMilliseconds(unsigned int milliseconds);
Security* WINAPI TD_ObtainOptionByUnderlierSymbol(const char* underlierSymbol, const OptionKey& key, bool subscribe);
Security* WINAPI TD_ObtainOptionByUnderlierNumericSymbol(const unsigned __int64& underlierSymbolNum, const OptionKey& key, bool subscribe);
//Security* WINAPI TD_FindOptionByUnderlierSymbol(const char* underlierSymbol, const OptionKey& key);
Security* WINAPI TD_FindOptionByUnderlierSymbol(const char* underlierSymbol, const OptionSymbolKey& key);
//Security* WINAPI TD_FindOptionByUnderlierNumericSymbol(const unsigned __int64& underlierSymbol, const OptionKey& key);
Security* WINAPI TD_FindOptionByUnderlierNumericSymbol(const unsigned __int64& underlierSymbol, const OptionSymbolKey& key);
Security* WINAPI TD_FindOptionByRootNumericSymbol(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock);
Security* WINAPI TD_FindOptionByRootNumericSymbolWithNoIncrementUnsubscribe(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock);
//Security* WINAPI TD_ObtainOptionByRootNumericSymbol(const unsigned __int64& rootSymbol, const unsigned __int64& optionBlock, bool subscribe);
Security* WINAPI TD_ObtainOptionByRootNumericSymbol(const unsigned __int64& rootSymbolNum, const OptionKey& key, bool subscribe);
Security* WINAPI TD_ObtainOptionByRootAndOptionBlock(const unsigned __int64& rootSymbolNum, const unsigned __int64& optionBlock, bool subscribe);//When the underlier symbol is not known

unsigned int WINAPI TD_GetOptionCount();
unsigned int WINAPI TD_GetIdleOptionCount();
TakionIterator* WINAPI TD_CreateOptionIterator();
Security* WINAPI TD_GetNextOption(TakionIterator* iterator);
/*
bool WINAPI TD_SubscribeUnderlierByNumericSymbol(const unsigned __int64& symbol);
bool WINAPI TD_UnsubscribeUnderlierByNumericSymbol(const unsigned __int64& symbol);
bool WINAPI TD_SubscribeUnderlier(const char* symbol);
bool WINAPI TD_UnsubscribeUnderlier(const char* symbol);
*/
//bool WINAPI TD_SubscribeOptionByNumericSymbol(const unsigned __int64& symbol, const OptionKey& optionKey);
//bool WINAPI TD_UnsubscribeOptionByNumericSymbol(const unsigned __int64& symbol, const OptionKey& optionKey);
//bool WINAPI TD_SubscribeOption(const char* symbol, const OptionKey& optionKey);
//bool WINAPI TD_UnsubscribeOption(const char* symbol, const OptionKey& optionKey);

Underlier* WINAPI TD_ObtainUnderlier(const char* symbol, bool subscribe, bool snapshotsOnly);
Underlier* WINAPI TD_FindUnderlier(const char* symbol);
Underlier* WINAPI TD_ObtainUnderlierByNumericSymbol(const unsigned __int64& numericSymbol, bool subscribe, bool snapshotsOnly);
Underlier* WINAPI TD_FindUnderlierByNumericSymbol(const unsigned __int64& numericSymbol);
unsigned int WINAPI TD_GetUnderlierCount();
unsigned int WINAPI TD_GetLoadedUnderlierCount();
unsigned int WINAPI TD_GetSubscribedUnderlierCount();
unsigned int WINAPI TD_GetIdleUnderlierCount();
unsigned int WINAPI TD_GetRemovableUnderlierCount();
void WINAPI TD_ReleaseUnderlier(const Underlier* underlier, bool unsubscribeImmediately = false);
TakionIterator* WINAPI TD_CreateUnderlierIterator();
Underlier* WINAPI TD_GetNextUnderlier(TakionIterator* iterator);

bool WINAPI TD_IsOptionMarketDataConnected();
bool WINAPI TD_IsOptionMarketDataLogged();

unsigned __int64 WINAPI TD_GetOptionMarketDataVersion();
const char* WINAPI TD_GetOptionMarketDataVersionStr();

unsigned char WINAPI TD_GetFlagsFromOptionBlock(const unsigned __int64& rootSymbol, const unsigned __int64& undelierSymbol, const unsigned int& optionBlock);

const Destination* WINAPI TD_GetOptionSourceDestination(const unsigned char& source);
const Destination* WINAPI TD_FindOptionDestinationByName(const char* name);
const Destination* WINAPI TD_FindOptionDestinationByNumericName(const unsigned int& name);

void WINAPI TD_AddTierSize(const char* symbol, const unsigned __int64& optionKey, unsigned int tierSize);//use object OptionKey to create the optionKey argument; 0 for stocks
void WINAPI TD_RemoveTierSize(const char* symbol, const unsigned __int64& optionKey);
void WINAPI TD_AddTierSizeToNumericSymbol(const unsigned __int64& numericSymbol, const unsigned __int64& optionKey, unsigned int tierSize);//use object OptionKey to create the optionKey argument; 0 for stocks
void WINAPI TD_RemoveTierSizeFromNumericSymbol(const unsigned __int64& numericSymbol, const unsigned __int64& optionKey);
const unsigned int* WINAPI TD_GetNextTierSize(TakionIterator* iterator, const char*& symbol, unsigned __int64& optionKey);//Call TD_GetNextTierSize to iterate
const unsigned int* WINAPI TD_FindTierSize(const unsigned __int64& numericSymbol, const unsigned __int64& optionKey);

void WINAPI TD_AddCustomPriceBase(const char* symbol, const unsigned __int64& optionKey, unsigned int compactPrice);//use object OptionKey to create the optionKey argument; 0 for stocks
void WINAPI TD_RemoveCustomPriceBase(const char* symbol, const unsigned __int64& optionKey);
void WINAPI TD_AddCustomPriceBaseToNumericSymbol(const unsigned __int64& numericSymbol, const unsigned __int64& optionKey, unsigned int compactPrice);//use object OptionKey to create the optionKey argument; 0 for stocks
void WINAPI TD_RemoveCustomPriceBaseFromNumericSymbol(const unsigned __int64& numericSymbol, const unsigned __int64& optionKey);
const unsigned int* WINAPI TD_GetNextCustomPriceBase(TakionIterator* iterator, const char*& symbol, unsigned __int64& optionKey);
const unsigned int* WINAPI TD_FindCustomPriceBase(const unsigned __int64& numericSymbol, const unsigned __int64& optionKey);

void WINAPI TD_AddCustomDate(const char* symbol, const unsigned __int64& optionKey, unsigned int date);//use object OptionKey to create the optionKey argument; 0 for stocks
void WINAPI TD_RemoveCustomDate(const char* symbol, const unsigned __int64& optionKey);
void WINAPI TD_AddCustomDateToNumericSymbol(const unsigned __int64& numericSymbol, const unsigned __int64& optionKey, unsigned int date);//use object OptionKey to create the optionKey argument; 0 for stocks
void WINAPI TD_RemoveCustomDateFromNumericSymbol(const unsigned __int64& numericSymbol, const unsigned __int64& optionKey);
const unsigned int* WINAPI TD_GetNextCustomDate(TakionIterator* iterator, const char*& symbol, unsigned __int64& optionKey);
const unsigned int* WINAPI TD_FindCustomDate(const unsigned __int64& numericSymbol, const unsigned __int64& optionKey);

bool WINAPI TD_SetTemporaryTierSize(const unsigned __int64& numericSymbol, const unsigned __int64& optionKey, unsigned int tierSize);//Can be called only from the main thread
const unsigned int* WINAPI TD_FindTemporaryTierSize(const unsigned __int64& numericSymbol, const unsigned __int64& optionKey);//Can be called only from the main thread
unsigned int WINAPI TD_ObtainTemporaryTierSize(const unsigned __int64& numericSymbol, const unsigned __int64& optionKey);//Returns 0xFFFFFFFF if TD_FindTemporaryTierSize returns nullptr//Can be called only from the main thread

//Call from the main thread only
void WINAPI TD_UserAddNonTradableStock(const char* symbol, const unsigned __int64& optionKey = 0);
void WINAPI TD_UserRemoveNonTradableStock(const char* symbol, const unsigned __int64& optionKey = 0);

//Use TD_CreateNonTradableStockIterator(); to create the iterator, and delete iterator when no longer needed.
//If called from a thread different from main thread enclose in lock/unlock: TD_LockNonTradableStockStorageInquiryWait(); TD_UnlockNonTradableStockStorageInquiry();
const unsigned int* WINAPI TD_GetNextNonTradableStock(TakionIterator* iterator, const char*& symbol, unsigned __int64& optionKey);

unsigned int WINAPI TD_FindNonTradableStock(const char* symbol, const unsigned __int64& optionKey);

//Call from the main thread only
void WINAPI TD_UserAddTradableStock(const char* symbol, const unsigned __int64& optionKey = 0);
void WINAPI TD_UserRemoveTradableStock(const char* symbol, const unsigned __int64& optionKey = 0);

//Use TD_CreateTradableStockIterator(); to create the iterator, and delete iterator when no longer needed.
//If called from a thread different from main thread enclose in lock/unlock: TD_LockTradableStockStorageInquiryWait(); TD_UnlockTradableStockStorageInquiry();
const unsigned int* WINAPI TD_GetNextTradableStock(TakionIterator* iterator, const char*& symbol, unsigned __int64& optionKey);

unsigned int WINAPI TD_FindTradableStock(const char* symbol, const unsigned __int64& optionKey);

bool WINAPI TD_IsTradableStock(const char* symbol, const unsigned __int64& optionKey);

unsigned int WINAPI TD_GetOptionSubscriptionQueueSize();
const unsigned __int64& WINAPI TD_GetRootSymbolBeingSubscribed();
const unsigned __int64& WINAPI TD_GetOptionBlockBeingSubscribed();
const unsigned __int64& WINAPI TD_GetUnderlierSymbolBeingSubscribed();

/////
bool WINAPI TD_IsFutureMarketDataConnected();
bool WINAPI TD_IsFutureMarketDataLogged();

bool WINAPI TD_IsFutureExecutorLogged();
bool WINAPI TD_IsFutureExecutorConnected();

unsigned __int64 WINAPI TD_GetFutureMarketDataVersion();
const char* WINAPI TD_GetFutureMarketDataVersionStr();

void WINAPI TD_SetFutureDefaultCommissionFee(const Money& commissionFee);
const Money& WINAPI TD_GetFutureDefaultCommissionFee();

const Destination* WINAPI TD_GetDestinationIlnk();

#else

void WINAPI TD_AddTierSize(const char* symbol, unsigned int tierSize);
void WINAPI TD_RemoveTierSize(const char* symbol);
void WINAPI TD_AddTierSizeToNumericSymbol(const unsigned __int64& numericSymbol, unsigned int tierSize);
void WINAPI TD_RemoveTierSizeFromNumericSymbol(const unsigned __int64& numericSymbol);
const unsigned int* WINAPI TD_GetNextTierSize(TakionIterator* iterator, const char*& symbol);//Call TD_GetNextTierSize to iterate
const unsigned int* WINAPI TD_FindTierSize(const unsigned __int64& numericSymbol);

void WINAPI TD_AddCustomPriceBase(const char* symbol, unsigned int compactPrice);
void WINAPI TD_RemoveCustomPriceBase(const char* symbol);
void WINAPI TD_AddCustomPriceBaseToNumericSymbol(const unsigned __int64& numericSymbol, unsigned int tierSize);
void WINAPI TD_RemoveCustomPriceBaseFromNumericSymbol(const unsigned __int64& numericSymbol);
const unsigned int* WINAPI TD_GetNextCustomPriceBase(TakionIterator* iterator, const char*& symbol);//Call TD_GetNextTierSize to iterate
const unsigned int* WINAPI TD_FindCustomPriceBase(const unsigned __int64& numericSymbol);

void WINAPI TD_AddCustomDate(const char* symbol, unsigned int date);
void WINAPI TD_RemoveCustomDate(const char* symbol);
void WINAPI TD_AddCustomDateToNumericSymbol(const unsigned __int64& numericSymbol, unsigned int date);
void WINAPI TD_RemoveCustomDateFromNumericSymbol(const unsigned __int64& numericSymbol);
const unsigned int* WINAPI TD_GetNextCustomDate(TakionIterator* iterator, const char*& symbol);//Call TD_GetNextTierSize to iterate
const unsigned int* WINAPI TD_FindCustomDate(const unsigned __int64& numericSymbol);

bool WINAPI TD_SetTemporaryTierSize(const unsigned __int64& numericSymbol, unsigned int tierSize);//Can be called only from the main thread
const unsigned int* WINAPI TD_FindTemporaryTierSize(const unsigned __int64& numericSymbol);//Can be called only from the main thread
unsigned int WINAPI TD_ObtainTemporaryTierSize(const unsigned __int64& numericSymbol);//Returns 0xFFFFFFFF if TD_FindTemporaryTierSize returns nullptr//Can be called only from the main thread

//Call from the main thread only
void WINAPI TD_UserAddNonTradableStock(const char* symbol);
void WINAPI TD_UserRemoveNonTradableStock(const char* symbol);

//Use TD_CreateNonTradableStockIterator(); to create the iterator, and delete iterator when no longer needed.
//If called from a thread different from main thread enclose in lock/unlock: TD_LockNonTradableStockStorageInquiryWait(); TD_UnlockNonTradableStockStorageInquiry();
const unsigned int* WINAPI TD_GetNextNonTradableStock(TakionIterator* iterator, const char*& symbol);

unsigned int WINAPI TD_FindNonTradableStock(const char* symbol);

//Call from the main thread only
void WINAPI TD_UserAddTradableStock(const char* symbol);
void WINAPI TD_UserRemoveTradableStock(const char* symbol);

//Use TD_CreateTradableStockIterator(); to create the iterator, and delete iterator when no longer needed.
//If called from a thread different from main thread enclose in lock/unlock: TD_LockTradableStockStorageInquiryWait(); TD_UnlockTradableStockStorageInquiry();
const unsigned int* WINAPI TD_GetNextTradableStock(TakionIterator* iterator, const char*& symbol);

unsigned int WINAPI TD_FindTradableStock(const char* symbol);

bool WINAPI TD_IsTradableStock(const char* symbol);

#endif

void WINAPI TD_ClearTierSize();
TakionIterator* WINAPI TD_CreateTierSizeIterator();//Call TD_GetNextTierSize to iterate

void WINAPI TD_ClearCustomPriceBase();
TakionIterator* WINAPI TD_CreateCustomPriceBaseIterator();//Call TD_GetNextTierSize to iterate

void WINAPI TD_ClearCustomDate();
TakionIterator* WINAPI TD_CreateCustomDateIterator();//Call TD_GetNextTierSize to iterate

void WINAPI TD_ClearTemporaryTierSize();//Can be called only from the main thread
TakionIterator* WINAPI TD_CreateTemporaryTierSizeIterator();//Can be called only from the main thread; //Call TD_GetNextTierSize to iterate

Index* WINAPI TD_FindIndex(const char* symbol);
Index* WINAPI TD_FindIndexByNumericSymbol(const unsigned __int64& numSymbol);
Index* WINAPI TD_GetIndexByCode(unsigned short code);
unsigned int WINAPI TD_GetIndexCount();
unsigned int WINAPI TD_GetLoadedIndexCount();

Security* WINAPI TD_ObtainSortableEquity(const char* symbol, bool subscribe, bool* newEquity = nullptr);//Call TD_ReleaseStock after the returned Security* is no longer in use
Security* WINAPI TD_ObtainSortableEquityByNumericSymbol(const unsigned __int64& numSymbol, bool subscribe, bool* newEquity = nullptr);//Call TD_ReleaseStock after the returned Security* is no longer in use
Security* WINAPI TD_FindSortableEquity(const char* symbol);
Security* WINAPI TD_FindSortableEquityByNumericSymbol(const unsigned __int64& symbol);
Security* WINAPI TD_FindSortableEquityWithNoIncrementUnsubscribe(const char* symbol);
Security* WINAPI TD_FindSortableEquityByNumericSymbolWithNoIncrementUnsubscribe(const unsigned __int64& symbol);
Security* WINAPI TD_GetSortableEquityByCode(unsigned short code);
unsigned short WINAPI TD_GetMarketSorterMinute();
short WINAPI TD_GetMarketSorterDelay();
unsigned int WINAPI TD_GetSortableEquityCount();
unsigned int WINAPI TD_GetLoadedSortableEquityCount();
unsigned int WINAPI TD_GetExpectedSortableEquityCount();
unsigned int WINAPI TD_GetExpectedSortableIndexCount();

//bool WINAPI TD_IsCalculateL2Top();
//void WINAPI TD_SetCalculateL2Top(bool calculateL2Top);
inline const bool& TD_IsCalculateL2Top()
{
	return TakionDataStaticValues::calculateL2Top;
}

unsigned int WINAPI TD_GetAccountCount();
unsigned int WINAPI TD_GetNumberOfAccountsExpected();
unsigned int WINAPI TD_GetNumberOfAccountsToLoad();
bool WINAPI TD_IsAllAccountsLoaded();
Account* WINAPI TD_FindAccount(const char* id);
Account* WINAPI TD_FindAccountByAccountId(const AccountId& id);
Account* WINAPI TD_CreateAccount(unsigned int simulation,//0 - live; 0xFFFFFFFF - generate traderId; 0xFFFFFFFE - use main traderId; otherwise - don't generate traderId: simulation = traderIdToUse;
	const char* accountId,
	const char* loginId,//nullptr - use main loginId
	unsigned int orderProcessingFlags = 0,
	unsigned int accountProcessingFlags = 0,
	unsigned int stockLoanNameSimulationNumeric = 0,
	const char* clearingAccountNameSimulation = nullptr,
	bool* newAccount = nullptr
#ifndef TAKION_NO_OPTIONS
	, unsigned char accountSecurityType = AST_STOCKS
#endif
	);//works only in simulation
bool WINAPI TD_DestroyAccount(const char* id);
void WINAPI TD_DestroyAllAccounts(
#ifndef TAKION_NO_OPTIONS
	unsigned int accountSecurityFilter
#endif
	);
/*In Simulation at midnight
void WINAPI TD_DestroyAllOrdersAndExecutions(
#ifndef TAKION_NO_OPTIONS
	unsigned int accountSecurityFilter
#endif
);
*/
TakionIterator* WINAPI TD_CreateAccountIterator();
Account* WINAPI TD_GetNextAccount(TakionIterator* iterator);
void WINAPI TD_LockAccountStorage();
void WINAPI TD_UnlockAccountStorage();

const Money& WINAPI TD_GetAllAccountsInvestment();
const Money& WINAPI TD_GetAllAccountsInvestmentMax();

TakionIterator* WINAPI TD_CreateClearingFirmIterator();
ClearingFirm* WINAPI TD_GetNextClearingFirm(TakionIterator* iterator);
ClearingFirm* WINAPI TD_FindClearingFirm(const char* name);
void WINAPI TD_LockClearingFirmStorage();
void WINAPI TD_UnlockClearingFirmStorage();

void WINAPI TD_LockTierSizeStorage();
void WINAPI TD_UnlockTierSizeStorage();

void WINAPI TD_LockCustomPriceBaseStorage();
void WINAPI TD_UnlockCustomPriceBaseStorage();

void WINAPI TD_LockCustomDateStorage();
void WINAPI TD_UnlockCustomDateStorage();

void WINAPI TD_SetLogFile(void* logFile);
void* WINAPI TD_GetLogFile();

unsigned int WINAPI TD_GetConnectionCount();
//void WINAPI TD_LockActiveConnections();
//void WINAPI TD_UnlockActiveConnections();
TakionIterator* WINAPI TD_CreateActiveConnectionIterator();
const ActiveConnection* WINAPI TD_GetNextActiveConnection(TakionIterator* iterator);

enum ConnectionResult : unsigned char
{
	CR_OK,
	CR_SAME_MARKETDATA_AND_EXECUTOR,
	CR_MARKETDATA_BINDING,
	CR_EXECUTOR_BINDING,
	CR_MARKETSORTER_BINDING,
	CR_HISTORICALPRINT_BINDING,
	CR_OPTION_MARKETDATA_BINDING,
	CR_FUTURE_MARKETDATA_BINDING,
	CR_FUTURE_EXECUTOR_BINDING,
	CR_MARKETDATA_NOT_LOGGED,
	CR_PASSWORD_HASH_ERROR,
};

enum ConnectionJob : unsigned short
{
	CR_JOB_MARKETDATA = 1,
	CR_JOB_EXECUTOR = 2,
	CR_JOB_MARKETSORTER = 4,
	CR_JOB_MARKETDATA_LOGON = 8,
	CR_JOB_EXECUTOR_LOGON = 16,
	CR_JOB_MARKETSORTER_LOGON = 32,
	CR_JOB_HISTORICALPRINT = 64,
	CR_JOB_HISTORICALPRINT_LOGON = 128,
#ifndef TAKION_NO_OPTIONS
	CR_JOB_OPTION_MARKETDATA = 256,
	CR_JOB_OPTION_MARKETDATA_LOGON = 512,
	CR_JOB_FUTURE_MARKETDATA = 1024,
	CR_JOB_FUTURE_MARKETDATA_LOGON = 2048,
	CR_JOB_FUTURE_EXECUTOR = 4096,
	CR_JOB_FUTURE_EXECUTOR_LOGON = 8192,
#endif
	CR_JOB_ALL_CONNECT = CR_JOB_MARKETDATA | CR_JOB_EXECUTOR | CR_JOB_MARKETSORTER | CR_JOB_HISTORICALPRINT
#ifndef TAKION_NO_OPTIONS
		| CR_JOB_OPTION_MARKETDATA
		| CR_JOB_FUTURE_MARKETDATA
		| CR_JOB_FUTURE_EXECUTOR
#endif
};

//unsigned int WINAPI TD_ConnectToMarketSorter(const Connection* marketSorterConnection, bool tryToReconnect);
struct IpPortStruct
{
	const char* ip;
	unsigned short port;
	const char* bindIp;//usually nullptr
	unsigned short bindPort;//usually 0
};

unsigned int WINAPI TD_ConnectToMarketSorter(const struct IpPortStruct* line, unsigned int lineCount, unsigned int reconnectSeconds, bool tryToReconnect);

void WINAPI TD_DisconnectFromMarketData();
void WINAPI TD_DisconnectFromExecutor();
void WINAPI TD_DisconnectFromMarketSorter();
void WINAPI TD_DisconnectFromHistoricalPrint();

const ActiveConnection* WINAPI TD_GetMarketDataActiveConnection();
const ActiveConnection* WINAPI TD_GetExecutorActiveConnection();
const ActiveConnection* WINAPI TD_GetMarketSorterActiveConnection();
const ActiveConnection* WINAPI TD_GetHistoricalPrintActiveConnection();

#ifndef TAKION_NO_OPTIONS
bool WINAPI TD_IsOptionValidTime();
//unsigned int WINAPI TD_GetOptionValidMillisecond();
void WINAPI TD_OptionBlockToString(std::string& str, const unsigned __int64& optionBlock);
const ActiveConnection* WINAPI TD_GetOptionMarketDataActiveConnection();
const Connection* WINAPI TD_GetOptionMarketDataConnection();
void WINAPI TD_DisconnectFromOptionMarketData();
Observable* WINAPI TD_GetNewOptionObservable();
//Observable* WINAPI TD_GetNewOptionObservable();
unsigned int WINAPI TD_GetSubscribedOptionCount();
bool WINAPI TD_IsEntitledToOptionData();

const ActiveConnection* WINAPI TD_GetFutureMarketDataActiveConnection();
const Connection* WINAPI TD_GetFutureMarketDataConnection();
void WINAPI TD_DisconnectFromFutureMarketData();
bool WINAPI TD_IsEntitledToFutureData();
const ActiveConnection* WINAPI TD_GetFutureExecutorActiveConnection();
const Connection* WINAPI TD_GetFutureExecutorConnection();
void WINAPI TD_DisconnectFromFutureExecutor();
unsigned int WINAPI TD_GetNumberOfFutureAccountsToLoad();
bool WINAPI TD_IsAllFutureAccountsLoaded();
Observable* WINAPI TD_GetNewFutureObservable();
#endif

const Connection* WINAPI TD_GetMarketDataConnection();
const Connection* WINAPI TD_GetExecutorConnection();
const Connection* WINAPI TD_GetMarketSorterConnection();
const Connection* WINAPI TD_GetHistoricalPrintConnection();

bool WINAPI TD_DoMainThreadIdleTasks(LONG lCount);
unsigned int WINAPI TD_GetStockIdleMilliseconds();

const char* WINAPI TD_GetOrderTypeName(unsigned int orderType);

TakionIterator* WINAPI TD_CreateDestinationIterator();
const Destination* WINAPI TD_GetNextDestination(TakionIterator* iterator);
const Destination* WINAPI TD_FindDestinationByName(const char* name);
const Destination* WINAPI TD_FindDestinationByNumericName(unsigned int name);
const Destination* WINAPI TD_FindDestinationById(const unsigned __int64& id);

TakionIterator* WINAPI TD_CreateDestinationRoutingPairIterator();
const DestinationRoutingPair* WINAPI TD_GetNextDestinationRoutingPair(TakionIterator* iterator);
const DestinationRoutingPair* WINAPI TD_FindDestinationRoutingPair(const unsigned __int64& id);
const DestinationRoutingPair* WINAPI TD_FindDestinationRoutingPairByNumericName(unsigned int destinationName, unsigned int routingName);
const DestinationRoutingPair* WINAPI TD_FindDestinationRoutingPairByName(const char* destinationName, const char* routingName);

const char* WINAPI TD_GetLoginId();
TraderIdType WINAPI TD_GetNumericTraderId();
TraderIdType WINAPI TD_GetNumericTraderIdPrintable();
bool WINAPI TD_IsSimulation();
const char* WINAPI TD_GetFirmId();

Account* WINAPI TD_GetDefaultAccount();
unsigned __int64 WINAPI TD_GetTraderIdFlags();

char WINAPI TD_GetPrimaryExchange(const Security* security);

const Destination* WINAPI TD_GetEcnDefaultDestination(unsigned char bookId);//enum EcnBookId in TakionUtilsApi.h
const Destination* WINAPI TD_GetStockSourceDestination(unsigned char source);//enum NyseMarketCenter in TakionUtilsApi.h (minus 'A', i. e. zero based)
const Destination* WINAPI TD_GetDestinationByPrimaryExchange(char primaryExchange);//enum PrimaryExchange in TakionUtilsApi.h
unsigned __int64 WINAPI TD_GetDestinationIdByPrimaryExchange(char primaryExchange);//enum PrimaryExchange in TakionUtilsApi.h

const Destination* WINAPI TD_GetDestinationAmex();
const Destination* WINAPI TD_GetDestinationNyse();
const Destination* WINAPI TD_GetDestinationNsdq();
const Destination* WINAPI TD_GetDestinationQsmt();
const Destination* WINAPI TD_GetDestinationApex();
const Destination* WINAPI TD_GetDestinationLynx();
const Destination* WINAPI TD_GetDestinationArca();
const Destination* WINAPI TD_GetDestinationBats();
const Destination* WINAPI TD_GetDestinationBaty();
const Destination* WINAPI TD_GetDestinationIex();
const Destination* WINAPI TD_GetDestinationEdga();
const Destination* WINAPI TD_GetDestinationEdgx();
const Destination* WINAPI TD_GetDestinationVirt();
//const Destination* WINAPI TD_GetDestinationNite();
const Destination* WINAPI TD_GetDestinationNsex();
const Destination* WINAPI TD_GetDestinationChsx();
const Destination* WINAPI TD_GetDestinationJpm();
const Destination* WINAPI TD_GetDestinationQstk();
const Destination* WINAPI TD_GetDestinationBdrg();
const Destination* WINAPI TD_GetDestinationVelocity();

unsigned int WINAPI TD_RequestStockHistoricalChart(const char* symbol, unsigned int dateFrom, unsigned int dateTo, unsigned char frequency);
HistoricalChart* WINAPI TD_RequestAndKeepStockHistoricalChart(const char* symbol, unsigned int dateFrom, unsigned char frequency, bool includePrePostMarket);
unsigned int WINAPI TD_AddToHistoricalChart(const HistoricalChart* historicalChart, unsigned int dateFrom);

bool WINAPI TD_IsTierBoundsValid(const Price& lowTierPrice, unsigned int lowTierSize, const Price& highTierPrice, unsigned int highTierSize, unsigned int minTierSize, unsigned int maxTierSize);
bool WINAPI TD_IsCurrentTierBoundsValid();
void WINAPI TD_SetTierBounds(const TierPriceRangeCollection& tierPriceRangeCollection, const Price& lowTierPrice, unsigned int lowTierSize, const Price& highTierPrice, unsigned int highTierSize, unsigned int minTierSize, unsigned int maxTierSize);
const Price& WINAPI TD_GetLowTierPrice();
const Price& WINAPI TD_GetHighTierPrice();
unsigned int WINAPI TD_GetLowTierSize();
unsigned int WINAPI TD_GetHighTierSize();
unsigned int WINAPI TD_GetMinTierSize();
unsigned int WINAPI TD_GetMaxTierSize();
unsigned int WINAPI TD_CalculateTierSize(const Price& price, bool* fromPriceRange);

void WINAPI TD_LockStockStorage();
void WINAPI TD_UnlockStockStorage();
void WINAPI TD_LockEquityStorage();
void WINAPI TD_UnlockEquityStorage();
void WINAPI TD_LockIndexStorage();
void WINAPI TD_UnlockIndexStorage();

TakionIterator* WINAPI TD_CreateStockIterator();
Security* WINAPI TD_GetNextStock(TakionIterator* iterator);
TakionIterator* WINAPI TD_CreateEquityIterator();
Security* WINAPI TD_GetNextEquity(TakionIterator* iterator);

TakionIterator* WINAPI TD_CreateIndexIterator();
TakionIterator* WINAPI TD_CreateCalcIndexIterator();
Index* WINAPI TD_GetNextIndex(TakionIterator* iterator);

enum CalcIndexType : unsigned char
{
	CALCINDEX_PRINT,
	CALCINDEX_BID,
	CALCINDEX_ASK,

	CALCINDEX_Count
};

unsigned int WINAPI TD_GetCalcIndexCount();
//Index* WINAPI TD_AddCalcIndex(const unsigned __int64& numSymbol, const char* const description, const SignedPrice& multiplier, const unsigned char& type, const bool includePreMarket, const bool includePostMarket);
Index* WINAPI TD_AddCalcIndex(const unsigned __int64& numSymbol, const char* const description, const SignedPrice& multiplier, const bool includePreMarket, const bool includePostMarket);
Index* WINAPI TD_RemoveCalcIndex(const unsigned __int64& numSymbol);
bool WINAPI TD_RemoveAndDestroyCalcIndex(const unsigned __int64& numSymbol);
Index* WINAPI TD_FindCalcIndex(const unsigned __int64& numSymbol);
bool WINAPI TD_SetCalcIndexMultiplier(Index* index, const SignedPrice& multiplier);
//bool WINAPI TD_SetCalcIndexType(Index* index, const unsigned char& type);
bool WINAPI TD_SetCalcIndexIncludePreMarket(Index* index, const bool includePreMarket);
bool WINAPI TD_SetCalcIndexIncludePostMarket(Index* index, const bool includePostMarket);
//bool WINAPI TD_SetCalcIndexParams(Index* index, const char* const description, const SignedPrice& multiplier, const unsigned char& type, const bool includePreMarket, const bool includePostMarket);
bool WINAPI TD_SetCalcIndexParams(Index* index, const char* const description, const SignedPrice& multiplier, const bool includePreMarket, const bool includePostMarket);
bool WINAPI TD_AddCalcIndexComponent(Index* index, const unsigned __int64& numSymbol, const SignedPrice& weight, const unsigned char& type);
bool WINAPI TD_RemoveCalcIndexComponent(Index* index, const unsigned __int64& numSymbol, const unsigned char& type);
bool WINAPI TD_ClearCalcIndexComponents(Index* index);
unsigned int WINAPI TD_GetCalcIndexComponentCount(const Index* index);
//bool WINAPI TD_SetCalcIndexComponentType(Index* index, const unsigned __int64& numSymbol, const unsigned char& oldType, const unsigned char& type);
bool WINAPI TD_SetCalcIndexComponentWeight(Index* index, const unsigned __int64& numSymbol, const unsigned char& type, const SignedPrice& weight);
TakionIterator* WINAPI TD_CreateCalcIndexComponentIterator(const Index* index);
CalcIndexComponent* WINAPI TD_GetNextCalcIndexComponent(TakionIterator* iterator, unsigned __int64* numericSymbol = nullptr);
CalcIndexComponent* WINAPI TD_FindCalcIndexComponent(const Index* index, const unsigned __int64& numericSymbol, const unsigned char& type);

bool WINAPI TD_IsMarketDataConnected();
bool WINAPI TD_IsExecutorConnected();
bool WINAPI TD_IsMarketSorterConnected();
bool WINAPI TD_IsMarketSorterLoaded();
bool WINAPI TD_IsMarketSorterIndexesLoaded();
bool WINAPI TD_IsMarketSorterStockChartsLoaded();
bool WINAPI TD_IsMarketSorterIndexChartsLoaded();
bool WINAPI TD_IsHistoricalPrintConnected();

bool WINAPI TD_IsMhRsiDataLoaded();
unsigned int WINAPI TD_GetMhRsiChartsRequested();
unsigned int WINAPI TD_GetMhRsiChartsLoaded();
unsigned int WINAPI TD_GetMhRsiChartsFailed();

bool WINAPI TD_IsDaysRsiDataLoaded();
unsigned int WINAPI TD_GetDaysRsiChartsRequested();
unsigned int WINAPI TD_GetDaysRsiChartsLoaded();
unsigned int WINAPI TD_GetDaysRsiChartsFailed();

const unsigned int& WINAPI TD_GetUserType();

const unsigned int& WINAPI TD_GetOrderSizeAbsoluteCap();
const unsigned int& WINAPI TD_GetMaxCancelsPerSecond();

const unsigned int& WINAPI TD_GetAdditionalOptionStrikeCap();
const unsigned int& WINAPI TD_GetAdditionalOptionExpirationCap();

char WINAPI TD_GetMarketStatus();
bool WINAPI TD_IsMarketStatusInitialized();
bool WINAPI TD_IsPreMarket();
bool WINAPI TD_IsMarketOpen();
bool WINAPI TD_IsMarketClosedForTheDay();

unsigned char WINAPI TD_GetMarketState();//MSTATE_PREMARKET, MSTATE_MARKET, MSTATE_POSTMARKET

enum MarketStatusTimeFrame : unsigned char
{
	MSTF_UNINITIALIZE,
	MSTF_BEFORE_PREMARKET,
	MSTF_PREMARKET,
	MSTF_BETWEEN_PREMARKET_AND_MARKET,
	MSTF_MARKET,
	MSTF_BETWEEN_MARKET_AND_POSTMARKET,
	MSTF_POSTMARKET,
	MSTF_AFTER_POSTMARKET,
};

unsigned char WINAPI TD_GetMarketStatusTimeFrame();
char WINAPI TD_GetMarketStatusByTimeFrame();

char WINAPI TD_GetHtbStockStartCharInSimulation();
char WINAPI TD_GetHtbStockEndCharInSimulation();

bool WINAPI TD_IsMovesReporting();
bool WINAPI TD_IsJoinsReporting();
bool WINAPI TD_IsPrintsReporting(bool oddLot);
bool WINAPI TD_IsLevel1Reporting();
const Price& WINAPI TD_GetPrintAndLevel1ReportingPriceGranularity();

bool  WINAPI TD_IsRedirectLynx();


Account* WINAPI TD_GetCurrentAccount();
void WINAPI TD_SetCurrentAccount(Account* account);

void WINAPI TD_SetMarketSorterSubscribeToStocks(bool subscribe);
void WINAPI TD_SetMarketSorterSubscribeToIndices(bool subscribe);
bool WINAPI TD_IsMarketSorterSubscribeToStocks();
bool WINAPI TD_IsMarketSorterSubscribeToIndices();
bool WINAPI TD_IsMarketSorterStocksSubscribed();
bool WINAPI TD_IsMarketSorterIndicesSubscribed();

bool WINAPI TD_IsCancelOnDisconnect();
void WINAPI TD_SetCancelOnDisconnect(bool cancel);

bool WINAPI TD_IsLoadExecutions();
bool WINAPI TD_LoadExecutions(const Account* account);

bool WINAPI TD_IsLoadOrders();
bool WINAPI TD_LoadOrders(const Account* account);
bool WINAPI TD_CanLoadAllAccountOrdersAndExecutions();
bool WINAPI TD_AreAllAccountOrdersLoading();
bool WINAPI TD_AreAllAccountExecutionsLoading();
bool WINAPI TD_LoadAllAccountOrdersAndExecutions(bool orders, bool executions);

#ifndef TAKION_NO_OPTIONS
bool WINAPI TD_IsLoadFutureExecutions();
bool WINAPI TD_IsLoadFutureOrders();
bool WINAPI TD_CanLoadAllFutureAccountOrdersAndExecutions();
bool WINAPI TD_AreAllFutureAccountOrdersLoading();
bool WINAPI TD_AreAllFutureAccountExecutionsLoading();
bool WINAPI TD_LoadAllFutureAccountOrdersAndExecutions(bool orders, bool executions);
#endif

bool WINAPI TD_IsLoadMarketSorterBeforeAccounts();

void WINAPI TD_SetChartApplicablePrintPercent(const Price& percent);
const Price& WINAPI TD_GetChartApplicablePrintPercent();

void WINAPI TD_SetBlockAggressiveOrderPriceRange(const Price& priceRange, bool percent, unsigned int pqOpen);
bool WINAPI TD_GetBlockAggressiveOrderPriceRange(Price& price, unsigned int pqOpen);

void WINAPI TD_SetBlockAggressiveOrderPriceRangePreMarket(const Price& priceRange, bool percent);
bool WINAPI TD_GetBlockAggressiveOrderPriceRangePreMarket(Price& price);
void WINAPI TD_SetBlockAggressiveOrderPriceRangeMarket(const Price& priceRange, bool percent);
bool WINAPI TD_GetBlockAggressiveOrderPriceRangeMarket(Price& price);
void WINAPI TD_SetBlockAggressiveOrderPriceRangePostMarket(const Price& priceRange, bool percent);
bool WINAPI TD_GetBlockAggressiveOrderPriceRangePostMarket(Price& price);
unsigned int WINAPI TD_GetBlockAggressiveOrderPriceRangeAsUInt(unsigned int pqOpen);
bool WINAPI TD_IsOrderTooAggressive(char side, const Price& limitPrice, const Price& stopPrice, const Price& bidPrice, const Price& askPrice, unsigned char tifType, unsigned int pqOpenPriceCompact);
bool WINAPI TD_IsOrderCrossingInsideMarket(char side, const Price& limitPrice, const Price& stopPrice, const Price& bidPrice, const Price& askPrice, unsigned char tifType);

void WINAPI TD_SetDefaultCommissionFee(const Money& commissionFee);
const Money& WINAPI TD_GetDefaultCommissionFee();

bool WINAPI TD_SetCustomAccountConstraints(const ConstraintCollection& cc);
void WINAPI TD_SetAccountCustomAccountConstraints(Account* account, const ConstraintCollection& cc);

bool WINAPI TD_IsExtendedTradingCloseAfterMarket();
void WINAPI TD_SetExtendedTradingCloseAfterMarket(bool etcAfterMarket);

bool WINAPI TD_IsArcaPloWhenHidden();
void WINAPI TD_SetArcaPloWhenHidden(bool arcaPlo);

bool WINAPI TD_IsSubscribeOnExecution();
void WINAPI TD_SetSubscribeOnExecution(bool subscribe);

bool WINAPI TD_IsNyseConvertToImbalanceOnly();
void WINAPI TD_SetNyseConvertToImbalanceOnly(bool convertToImbalanceOnly);

bool WINAPI TD_IsTraderIdEnabled();

bool WINAPI TD_IsTradingAllowed();

bool WINAPI TD_IsPostponeGtcOrders();
void WINAPI TD_SetPostponeGtcOrders(bool postponeGtcOrders);

bool WINAPI TD_IsDefaultOnlyTradingAllowed();
bool WINAPI TD_IsTestOnlyTradingAllowed();
unsigned int WINAPI TD_GetOrderDelayInSimulation();
unsigned int WINAPI TD_GetStuckDelayInSimulation();
unsigned int WINAPI TD_GetCancelMultiplicityInSimulation();

RoundLotPolicy WINAPI TD_GetRoundLotPolicy();
unsigned char WINAPI TD_GetWashOrderPolicy();

//bool WINAPI TD_IsAllowOddLotOrdersInSimulation();
//void TD_SetAllowOddLotOrdersInSimulation(bool allow);

bool WINAPI TD_IsAllowSellBorrowedInSimulation();

bool WINAPI TD_IsAccountRetailInSimulation();
//bool WINAPI TD_IsQsmtInSimulation();
//void WINAPI TD_SetQsmtInSimulation(bool allow);

bool WINAPI TD_IsSupportConservativeOrderMarkingInSimulation();

unsigned int WINAPI TD_GetStuckOrderSizeInSimulation();
unsigned int WINAPI TD_GetCancelRejectSizeInSimulation();
unsigned int WINAPI TD_GetMaxExecutionSizeInSimulation();

unsigned int WINAPI TD_GetLocateVenueInSimulation();

const Destination* WINAPI TD_GetBorrowDestination(unsigned int locateVenue);

unsigned int WINAPI TD_GetOrderProcFlagsInSimulation();

unsigned int WINAPI TD_GetAccountProcFlagsInSimulation();

const unsigned int& WINAPI TD_GetUserTypeLive();
const unsigned int& WINAPI TD_GetUserTypeInSimulation();
const unsigned short& WINAPI TD_GetCancelRejectCodeInSimulation();

#ifdef FIRM_VALUES
const bool& WINAPI TD_CanSeeFirmPositions();
#ifndef FIRM_VALUES_ALWAYS
void WINAPI TD_SetKeepFirmPositionSubscription(bool keep);
#endif
unsigned short WINAPI TD_GetAccountAggregatorCount();
unsigned short WINAPI TD_GetNumberOfAccountAggregatorUntradeableListsToLoad();
bool WINAPI TD_AreAllAccountAggregatorUntradeableListsLoaded();
const AccountAggregator* WINAPI TD_FindAccountAggregator(const AccountAggregatorId& accountAggregatorId);
TakionIterator* WINAPI TD_CreateAccountAggregatorIterator();
const AccountAggregator* WINAPI TD_GetNextAccountAggregator(TakionIterator* iterator);
void WINAPI TD_LockAccountAggregatorStorage();
void WINAPI TD_UnlockAccountAggregatorStorage();

Observable* WINAPI TD_GetNewFirmPositionObservable();

#endif

const bool& WINAPI TD_IsUserSupervisorLive();
const bool& WINAPI TD_IsUserSupervisorInSimulation();
const bool& WINAPI TD_IsUserSupervisor();

bool WINAPI TD_IsResizeToBpa();
void WINAPI TD_SetResizeToBpa(bool resizeToBpa);

bool WINAPI TD_IsClearAccountsAtMidnightInSimulation();
void WINAPI TD_SetClearAccountsAtMidnightInSimulation(bool clearAccounts);

bool WINAPI TD_IsResizeToPositionCap();
void WINAPI TD_SetResizeToPositionCap(bool resizeToPositionCap);

bool WINAPI TD_IsCancelOrdersOnStockHalt();
void WINAPI TD_SetCancelOrdersOnStockHalt(bool cancelOrdersOnStockHalt);

bool WINAPI TD_IsStopOrdersWash();
void WINAPI TD_SetStopOrdersWash(bool stopOrdersWash);

unsigned char WINAPI TD_GetOversellSplitPolicy();
void WINAPI TD_SetOversellSplitPolicy(unsigned char oversellSplitPolicy);

bool WINAPI TD_IsResizeShortToBorrowed();
void WINAPI TD_SetResizeShortToBorrowed(bool resize);

bool WINAPI TD_IsRemoveDelayedOrdersOnClosePrice();
void WINAPI TD_SetRemoveDelayedOrdersOnClosePrice(bool remove);

bool WINAPI TD_IsCancelStopOrdersOnMarketClose();
void WINAPI TD_SetCancelStopOrdersOnMarketClose(bool cancel);

bool WINAPI TD_IsDoNotReplaceIllegalOnOpenOnCloseOrders();
void WINAPI TD_SetDoNotReplaceIllegalOnOpenOnCloseOrders(bool doNotReplace);

bool WINAPI TD_IsCancelOversellInsteadOfResize();
void WINAPI TD_SetCancelOversellInsteadOfResize(bool cancel);

bool WINAPI TD_IsResizeOversellWithoutSplitting();
void WINAPI TD_SetResizeOversellWithoutSplitting(bool resizeOversellWithoutSplitting);

bool WINAPI TD_IsCancelOvershortInsteadOfResize();
void WINAPI TD_SetCancelOvershortInsteadOfResize(bool cancel);

bool WINAPI TD_IsDestroyCanceledOrders();
void WINAPI TD_SetDestroyCanceledOrders(bool destroy);

bool WINAPI TD_IsDestroyBlockedOrders();
void WINAPI TD_SetDestroyBlockedOrders(bool destroy);

bool WINAPI TD_IsThreadDelays();
void WINAPI TD_SetThreadDelays(bool threadDelays);

unsigned char WINAPI TD_GetLevel2LogDepth();
void WINAPI TD_SetLevel2LogDepth(unsigned char depth);

void WINAPI TD_SetAllPhantomPositionsFlat();

//ActOnMaxLossMode WINAPI TD_GetActOnMaxLossMode();
//void WINAPI TD_SetActOnMaxLossMode(ActOnMaxLossMode mode);

TakionIterator* WINAPI TD_CreateIndexDescriptionIterator();
const IndexDescription* WINAPI TD_GetNextIndexDescription(TakionIterator* iterator);

bool WINAPI TD_SetSymbolInCommandTool(const char* symbol, bool post, unsigned int commandToolOrdinal = 0xFFFFFFFF//commandToolOrdinal = 0xFFFFFFFF means active command tool.
#ifndef TAKION_NO_OPTIONS
	, const unsigned __int64& optionBlock = 0
#endif
	);


unsigned __int64 WINAPI TD_GetMarketDataEntitlements();
unsigned __int64 WINAPI TD_GetMarketDataDatabaseEntitlements();
unsigned __int64 WINAPI TD_GetMarketDataCustomEntitlements();
bool WINAPI TD_SetMarketDataCustomEntitlements(const unsigned __int64& entitlements);

unsigned __int64 WINAPI TD_GetExtMarketDataEntitlements();
unsigned __int64 WINAPI TD_GetExtMarketDataDatabaseEntitlements();
unsigned __int64 WINAPI TD_GetExtMarketDataCustomEntitlements();
bool WINAPI TD_SetExtMarketDataCustomEntitlements(const unsigned __int64& entitlements);

unsigned __int64 WINAPI TD_GetMarketDataVersion();
const char* WINAPI TD_GetMarketDataVersionStr();
bool WINAPI TD_IsMdSubscriptionOnly();

unsigned __int64 WINAPI TD_GetMarketSorterVersion();
const char* WINAPI TD_GetMarketSorterVersionStr();
bool WINAPI TD_IsMsSubscriptionOnly();
bool WINAPI TD_IsMsEntitledToFullData();

unsigned __int64 WINAPI TD_GetExecutorVersion();
const char* WINAPI TD_GetExecutorVersionStr();

bool WINAPI TD_IsMarketDataLogged();
bool WINAPI TD_IsMarketSorterLogged();
bool WINAPI TD_IsExecutorLogged();

bool WINAPI TD_IsLogDefaultAccountOnly();
void WINAPI TD_SetLogDefaultAccountOnly(bool only);

//bool WINAPI TD_IsLogonToExecutorAfterMarketSorterLoad();
//bool WINAPI TD_SetLogonToExecutorAfterMarketSorterLoad(bool afterMsLoad);

bool WINAPI TD_CancelOrdersToExpire();
bool WINAPI TD_HasOrdersToExpire();
bool WINAPI TD_SetExiting(bool cancelDefaultAccountOrders, bool cancelOtherAccountOrders, bool cancelDefaultAccountOrdersExceptGtc, bool cancelOtherAccountOrdersExceptGtc);
bool WINAPI TD_HasActiveNonProblematicOrdersInDefaultAccount(const bool& exceptGtc, const bool& includeAlgos);
bool WINAPI TD_HasActiveNonProblematicOrdersInNonDefaultAccounts(const bool& exceptGtc, const bool& includeAlgos);
bool WINAPI TD_DisconnectConnection(const char* ip, unsigned short port, unsigned int reconnectTries);
bool WINAPI TD_DisconnectConnectionByNumericIpPort(unsigned int ip, unsigned short port, unsigned int reconnectTries);
bool WINAPI TD_ReconnectConnection(ConnectionBase& connection);
bool WINAPI TD_ReconnectConnectionByIpPort(const unsigned __int64& ipport);

//
void WINAPI TD_GetPanicCommandName(std::string& commandName, unsigned char marketState);
void WINAPI TD_GetPanicCommandNames(std::string& commandNameMarket, std::string& commandNamePreMarket, std::string& commandNamePostMarket);
bool WINAPI TD_SetPanicCommandNames(const std::string& commandNameMarket, const std::string& commandNamePreMarket, const std::string& commandNamePostMarket);

void WINAPI TD_GetPanicCommandNameMarket(std::string& commandName);
void WINAPI TD_GetPanicCommandNamePreMarket(std::string& commandName);
void WINAPI TD_GetPanicCommandNamePostMarket(std::string& commandName);

bool WINAPI TD_SetPanicCommandNameMarket(const std::string& commandName);
bool WINAPI TD_SetPanicCommandNamePreMarket(const std::string& commandName);
bool WINAPI TD_SetPanicCommandNamePostMarket(const std::string& commandName);
//
void WINAPI TD_GetPositionLoserNotifyCommandName(std::string& commandName, unsigned char marketState);
void WINAPI TD_GetPositionLoserNotifyCommandNames(std::string& commandNameMarket, std::string& commandNamePreMarket, std::string& commandNamePostMarket);
bool WINAPI TD_SetPositionLoserNotifyCommandNames(const std::string& commandNameMarket, const std::string& commandNamePreMarket, const std::string& commandNamePostMarket);

void WINAPI TD_GetPositionLoserNotifyCommandNameMarket(std::string& commandName);
void WINAPI TD_GetPositionLoserNotifyCommandNamePreMarket(std::string& commandName);
void WINAPI TD_GetPositionLoserNotifyCommandNamePostMarket(std::string& commandName);

bool WINAPI TD_SetPositionLoserNotifyCommandNameMarket(const std::string& commandName);
bool WINAPI TD_SetPositionLoserNotifyCommandNamePreMarket(const std::string& commandName);
bool WINAPI TD_SetPositionLoserNotifyCommandNamePostMarket(const std::string& commandName);
//
void WINAPI TD_GetAccountLoserNotifyCommandName(std::string& commandName, unsigned char marketState);
void WINAPI TD_GetAccountLoserNotifyCommandNames(std::string& commandNameMarket, std::string& commandNamePreMarket, std::string& commandNamePostMarket);
bool WINAPI TD_SetAccountLoserNotifyCommandNames(const std::string& commandNameMarket, const std::string& commandNamePreMarket, const std::string& commandNamePostMarket);

void WINAPI TD_GetAccountLoserNotifyCommandNameMarket(std::string& commandName);
void WINAPI TD_GetAccountLoserNotifyCommandNamePreMarket(std::string& commandName);
void WINAPI TD_GetAccountLoserNotifyCommandNamePostMarket(std::string& commandName);

bool WINAPI TD_SetAccountLoserNotifyCommandNameMarket(const std::string& commandName);
bool WINAPI TD_SetAccountLoserNotifyCommandNamePreMarket(const std::string& commandName);
bool WINAPI TD_SetAccountLoserNotifyCommandNamePostMarket(const std::string& commandName);
//
bool WINAPI TD_IsEtbListLoaded();

bool WINAPI TD_IsQsmtRedirectTime();
bool WINAPI TD_IsBamlRedirectTime();

#ifdef LYNX_REROUTING
bool WINAPI TD_IsLynxOnOpenOnCloseRedirectTime();
bool WINAPI TD_IsLynxRedirectTime();
#endif

bool WINAPI TD_IsApexRedirectTime();
bool WINAPI TD_IsQsmtPassiveRedirectTime();
bool WINAPI TD_IsBorrowOvernightTime();

bool WINAPI TD_IsDefaultAccountOnly();

void WINAPI TD_RemoveQuote(const unsigned __int64& symbol,
#ifndef TAKION_NO_OPTIONS
	const unsigned __int64& optionBlock,
#endif
	bool side, unsigned char bookId, unsigned int mmid, const Price& priceFrom, const Price& priceTo);

unsigned char WINAPI TD_WhichThreadCurrent(unsigned int* threadId = nullptr);//0 - main, 1 - data, 2 - other

unsigned int WINAPI TD_GetCancelsPerSecond();
void WINAPI TD_SetCancelsPerSecond(unsigned int cancelsPerSecond);

//int WINAPI TD_GetFirmPositionInSimulation();
//void WINAPI TD_SetFirmPositionInSimulation(int firmPosition);

bool WINAPI TD_RequestHistoricalPrints(const char* symbol, unsigned short minute, unsigned __int64 referenceNumber, unsigned char flags, unsigned int& requestId);
bool WINAPI TD_StopHistoricalPrints(unsigned int requestId);
unsigned short WINAPI TD_GetCloseMarketMinute();
unsigned int WINAPI TD_GetCloseMarketMillisecond();
unsigned int WINAPI TD_GetLocMocMillisecond();

//unsigned int WINAPI TD_GetNsdqLocMocMillisecond();
unsigned int WINAPI TD_GetNsdqMocMillisecond();
unsigned int WINAPI TD_GetNsdqLocMillisecond();

unsigned int WINAPI TD_GetNsdqLooMillisecond();
unsigned int WINAPI TD_GetNsdqMooMillisecond();

Connection* WINAPI TD_AddConnection(Connection* connection, const unsigned char format, bool tryToReconnect);
bool WINAPI TD_RemoveConnection(const Connection* connection);
bool WINAPI TD_RemoveConnectionByIpPort(const unsigned __int64& ipport);

NewsDll* WINAPI TD_GetNewsDll();
bool WINAPI TD_IsNewsDllCompatible();
unsigned int WINAPI TD_GetLoadedExtensionCount();

const char* WINAPI TD_GetDefaultProActiveRoutingName();
unsigned int WINAPI TD_GetDefaultProActiveRoutingNumericName();

const char* WINAPI TD_GetLynxSmartRoutingName();
unsigned int WINAPI TD_GetLynxSmartRoutingNumericName();
const char* WINAPI TD_GetArcaPassiveLiquidityRoutingName();
unsigned int WINAPI TD_GetArcaPassiveLiquidityRoutingNumericName();
const char* WINAPI TD_GetAddLiquidityOnlyRoutingName();
unsigned int WINAPI TD_GetAddLiquidityOnlyRoutingNumericName();

//const char* WINAPI TD_GetDmaRoutingName();
//unsigned int WINAPI TD_GetDmaRoutingNumericName();

const ActiveConnection* WINAPI TD_FindActiveConnection(unsigned __int64 ipport);
const ActiveConnection* WINAPI TD_FindActiveConnectionByIpPort(unsigned int ip, unsigned short port);
const ActiveConnection* WINAPI TD_GetConnectionData(unsigned char dataType);

bool WINAPI TD_IsRoutingInstructionAddLiquidityOnly(unsigned int routingId);

unsigned __int64 WINAPI TD_GetDefaultOtcbbVenueId();
unsigned short WINAPI TD_GetDefaultOtcbbRoutingInstructionId();
void WINAPI TD_SetDefaultOtcbbVenueAndRoutingInstruction(const unsigned __int64& otcbbVenueId, unsigned short otcbbRoutingInstructionId);

unsigned __int64 WINAPI TD_GetOtcbbUnder5VenueId();
unsigned short WINAPI TD_GetOtcbbUner5RoutingInstructionId();
void WINAPI TD_SetOtcbbUnder5VenueAndRoutingInstruction(const unsigned __int64& otcbbVenueId, unsigned short otcbbRoutingInstructionId);

void WINAPI TD_SetEquityTimeFrame(unsigned int millisecond);//0 - use 1 minute time frame
const unsigned short& WINAPI TD_GetCurrentMinute();

unsigned int WINAPI TD_GetLoadedTodaysStockChartCount();
unsigned int WINAPI TD_GetLoadedTodaysIndexChartCount();

unsigned char WINAPI TD_GetStopOrderTypeBase(unsigned char stopOrderType, unsigned char stopOrderBase);
unsigned char WINAPI TD_GetPegTypeByExecInstruction(unsigned int execInstruction);
unsigned int WINAPI TD_GetExecInstructionByPegType(unsigned char pegType);

//Message Watch
enum ExtensionRequestFilterEnum : unsigned char
{
	REQF_ORDER,
	REQF_ORDER_CANCEL,
	REQF_ORDER_REPLACE,
	REQF_STOCK_SUBSCRIBE,
	REQF_HEARTBEAT,
	REQF_LOAD_HISTORY,
	REQF_LOGON,
	REQF_PUBLIC_KEY,

	REQF_MS_SUBSCRIBE,
	REQF_MS_CHART,

	REQF_HIST_CHART,
	REQF_HIST_PRINT,

	REQF_UNDERLIER_SUBSCRIBE,
	REQF_OPTION_SUBSCRIBE,

	REQF_FIRM,

	REQF_Count,
};

enum ExtensionResponseFilterEnum : unsigned char
{
	RSPF_LOGON,

	RSPF_MD_SUBSCRIPTION,
	RSPF_MD_QUOTE,
	RSPF_MD_QUOTE_EXEC_HIDDEN,
	RSPF_MD_QUOTE_INDICATORS,
	RSPF_MD_LEVEL1,
	RSPF_MD_LEVEL2,
	RSPF_MD_PRINT,
	RSPF_MD_PRINT_CORRECTION,
	RSPF_MD_IMBALANCE,
	RSPF_MD_RESET,

	RSPF_MS_SUBSCRIPTION,
	RSPF_MS_LEVEL1,
	RSPF_MS_PRINT,
	RSPF_MS_PRINT_CORRECTION,
	RSPF_MS_IMBALANCE,
	RSPF_MS_QUOTE_INDICATORS,
	RSPF_MS_RESET,

	RSPF_MS_INDEX,

	RSPF_MS_CHART,
	RSPF_MS_CHART_CORRECTION,
	RSPF_MS_NEW_MINUTE,

	RSPF_HIST_CHART,
	RSPF_HIST_PRINT,
/*
	RSPF_ORDER_ACK,
	RSPF_ORDER_UPDATE,
	RSPF_ORDER_KILL,
	RSPF_ORDER_REJECT,
	RSPF_ORDER_EXEC,

	RSPF_CANCEL_ACK,
	RSPF_REPLACE_ACK,
	RSPF_REPLACE_DONE,
*/
	RSPF_ORDER,
	RSPF_ACCOUNT,
	RSPF_FIRM,
	RSPF_HTB,

	RSPF_YESTERDAY_VALUES_CORRECTION,

	RSPF_Count
};

void WINAPI TD_SetExtensionRequestFilter(const HMODULE& hmodule, const unsigned int& requestFilter);
void WINAPI TD_AddRemoveExtensionRequestFilter(const HMODULE& hmodule, const unsigned int& addRequestFilter, const unsigned int& removeRequestFilter);
void WINAPI TD_SetExtensionResponseFilter(const HMODULE& hmodule, const unsigned int& responseFilter);
void WINAPI TD_AddRemoveExtensionResponseFilter(const HMODULE& hmodule, const unsigned int& addResponseFilter, const unsigned int& removeResponseFilter);

//Message Simulation
MessageThread* WINAPI TD_ObtainMessageSimulationThread();
bool WINAPI TD_ReleaseMessageSimulationThread(const MessageThread* const& messageSimulationThread);

void WINAPI TD_StartNotifyIpChangeThread();
void WINAPI TD_ReleaseNotifyIpChangeThread();

char WINAPI TD_GetSideByServerSide(unsigned char serverSide);

TakionServer* WINAPI TD_CreateServer(unsigned int ip,
	unsigned short port,
	const unsigned char format,
	bool nagle,
	bool logMessages,
	const unsigned int& estimatedHeartbeatDelayMilliseconds,
	HCRYPTPROV* hCryptProv,//nullptr
	TakionClientData* clientData,//nullptr
	TextProcessor* textProcessor,//nullptr
	bool* exists = nullptr);
TakionServer* WINAPI TD_FindServer(unsigned short port);
bool WINAPI TD_DestroyServer(unsigned short port);
void WINAPI TD_ClearServers();
TakionIterator* WINAPI TD_CreateServerIterator();
const TakionServer* WINAPI TD_GetNextServer(TakionIterator* iterator);
//const TakionClient* WINAPI TD_TakionDataServerGetNextClient(TakionIterator* iterator);

Order* WINAPI TD_FindPendingOrderInAllAccountsByClientId(const unsigned int& clientId);

bool WINAPI TD_UpdateInventory(Account* account, const InventoryNode* inventoryArray, unsigned int inventoryNodeCount, const int size, unsigned char securityTypeHidden, bool allPositions);

bool WINAPI TD_DestroyUntradedPositions(Account* account);//account = nullptr means all accounts
bool WINAPI TD_DestroyUntradedPosition(Account* account, const char* symbol
#ifndef TAKION_NO_OPTIONS
	,const unsigned __int64& optionBlock
	,const unsigned char securityType
#endif
	);
void WINAPI TD_SetPhantomPositionsFlat(Account* account);//account = nullptr means all accounts

void WINAPI TD_LoadMhRsiData(bool load);
const unsigned int& WINAPI TD_GetLoadMhRsiDataCount();
const Price* WINAPI TD_FindRsiMhPriceArray(const unsigned __int64& numericSymbol, unsigned short& size, bool& loaded);

void WINAPI TD_LoadDaysRsiData(bool load);
const unsigned int& WINAPI TD_GetLoadDaysRsiDataCount();
const Price* WINAPI TD_FindRsiDaysPriceArray(const unsigned __int64& numericSymbol, unsigned short& size, bool& loaded);

RoundPriceMode WINAPI TD_GetRoundPriceMode();
void TD_SetRoundPriceMode(unsigned char roundPriceMode);//Possible values in RoundPriceMode enum in file TakionUtilsApi.h

const bool& WINAPI TD_IsServerTimeInitialized();

const unsigned int* const WINAPI TD_GetEcnFilterLineCount();
const unsigned int* const WINAPI TD_GetLineCountWithoutNyseAmexBook();
const unsigned int* const WINAPI TD_GetLineCountWithoutNyseBook();

void WINAPI TD_RestoreSimulatedPositions();

void WINAPI TD_SetForceCalculatePositionLeverage(bool force);
unsigned int WINAPI TD_GetCalculatePositionLeverageCount();
bool WINAPI TD_IsForceCalculatePositionLeverage();
bool WINAPI TD_IsCalculatePositionLeverage();

unsigned int WINAPI TD_GetTimerExpirationFrequency();
void WINAPI TD_SetTimerExpirationFrequency(unsigned int frequency);

//unsigned int WINAPI TD_GetOptionSubscribeTime();
bool WINAPI TD_IsOptionValidTime();

enum FirmIdFlags : unsigned char
{
	FIDF_Other,
	FIDF_PERO,
	FIDF_ETFX,
	FIDF_STDR,//VCBB
	FIDF_SLCO,
	FIDF_TPCO,
	FIDF_TVMK,
	FIDF_VCVT,
	FIDF_TTTT,
	FIDF_TTTI,

	FIDF_VCVU,
	FIDF_GPCE,

	FIDF_VCAB,

	FIDF_VCTP,

	FIDF_TAIQ,

	FIDF_QNTX,

	FIDF_Count
};

unsigned int WINAPI TD_GetFirmIdFlags();
const char* WINAPI TD_GetDisplayDestinationName(const Destination* destination, unsigned int stockLoanFirmId = 0);//For some Firms the destination can be displayed with a different name
const char* WINAPI TD_GetRealDestinationName(const char* displayDestinationName, unsigned int stockLoanFirmId= 0);//For some Firms the destination can be displayed with a different name
const char* WINAPI TD_GetDisplayDestinationNameByRealName(const char* realDestinationName, unsigned int stockLoanFirmId = 0);//For some Firms the destination can be displayed with a different name
unsigned int WINAPI TD_GetRealDestinationNumericName(unsigned int displayDestinationName, unsigned int stockLoanFirmId = 0);//For some Firms the destination can be displayed with a different name
unsigned int WINAPI TD_GetDisplayDestinationNumericNameByRealName(unsigned int realDestinationName, unsigned int stockLoanFirmId = 0);//For some Firms the destination can be displayed with a different name
unsigned int WINAPI TD_GetFirmIdFlagFromStockLoanFirmId(unsigned int stockLoanFirmId);
bool WINAPI TD_IsDestinationValid(const unsigned __int64& destinationId, unsigned int stockLoanFirmId = 0);//If 0 then it checks all stockLoanFirmIds present in all loaded Accounts
bool WINAPI TD_IsRoutingValid(const unsigned __int64& destinationId, const unsigned short routingId, unsigned int stockLoanFirmId = 0);//If 0 then it checks all stockLoanFirmIds present in all loaded Accounts
unsigned char WINAPI TD_GetStockLoanFirmIdNames(unsigned int* stockLoanFirmIdNames, const unsigned char nameBufLength);//nameBufLength = how many "unsigned int"s are there in buffer stockLoanFirmIdNames

//For some Firms the Routing can be displayed with a different name
const char* WINAPI TD_GetDisplayRoutingName(const DestinationRouting* routing, unsigned int stockLoanFirmId = 0);
unsigned int WINAPI TD_GetDisplayRoutingNumericName(const DestinationRouting* routing, unsigned int stockLoanFirmId = 0);
const char* WINAPI TD_GetRealRoutingName(unsigned int realDestinationName, const char* displayRoutingName, unsigned int stockLoanFirmId = 0);
const char* WINAPI TD_GetDisplayRoutingNameByRealName(unsigned int realDestinationName, const char* realRoutingName, unsigned int stockLoanFirmId = 0);
unsigned int WINAPI TD_GetRealRoutingNumericName(unsigned int realDestinationName, unsigned int displayRoutingName, unsigned int stockLoanFirmId = 0);
unsigned int WINAPI TD_GetDisplayRoutingNumericNameByRealName(unsigned int realDestinationName, unsigned int realRoutingName, unsigned int stockLoanFirmId = 0);
const char* WINAPI TD_GetDisplayRoutingDescription(const DestinationRouting* routing, unsigned int stockLoanFirmId = 0);
////

bool WINAPI TD_IsLogCurrentAccount();
void WINAPI TD_SetLogCurrentAccount(bool log);

bool WINAPI TD_IsLoadCharts();

bool WINAPI TD_GetTop10VolumeValueAt(const unsigned int& at, unsigned __int64& symbol, Price& price, unsigned int& volume);
bool WINAPI TD_GetTop10GainerValueAt(const unsigned int& at, unsigned __int64& symbol, Price& price, SignedPrice& netChange);
bool WINAPI TD_GetTop10LoserValueAt(const unsigned int& at, unsigned __int64& symbol, Price& price, SignedPrice& netChange);
bool WINAPI TD_GetTop10PercentGainerValueAt(const unsigned int& at, unsigned __int64& symbol, Price& price, SignedPrice& netChangePercent);
bool WINAPI TD_GetTop10PercentLoserValueAt(const unsigned int& at, unsigned __int64& symbol, Price& price, SignedPrice& netChangePercent);

unsigned int WINAPI TD_GetTop10VolumeLoadTime();
short WINAPI TD_GetTop10VolumeLoadDelay();
unsigned int WINAPI TD_GetTop10GainersLoadTime();
short WINAPI TD_GetTop10GainersLoadDelay();
unsigned int WINAPI TD_GetTop10LosersLoadTime();
short WINAPI TD_GetTop10LosersLoadDelay();
unsigned int WINAPI TD_GetTop10PercentGainersLoadTime();
short WINAPI TD_GetTop10PercentGainersLoadDelay();
unsigned int WINAPI TD_GetTop10PercentLosersLoadTime();
short WINAPI TD_GetTop10PercentLosersLoadDelay();

void WINAPI TD_GetTop10VolumeLoadTimeAndDelay(unsigned int& loadTime, short& loadDelay);
void WINAPI TD_GetTop10GainersLoadTimeAndDelay(unsigned int& loadTime, short& loadDelay);
void WINAPI TD_GetTop10LosersLoadTimeAndDelay(unsigned int& loadTime, short& loadDelay);
void WINAPI TD_GetTop10PercentGainersLoadTimeAndDelay(unsigned int& loadTime, short& loadDelay);
void WINAPI TD_GetTop10PercentLosersLoadTimeAndDelay(unsigned int& loadTime, short& loadDelay);

unsigned int WINAPI TD_GetTop10LoadTime(unsigned char top10Type);
short WINAPI TD_GetTop10LoadDelay(unsigned char top10Type);
bool WINAPI TD_GetTop10LoadTimeAndDelay(unsigned char top10Type, unsigned int& loadTime, short& loadDelay);

TakionIterator* WINAPI TD_CreateTop10VolumeIterator();
unsigned __int64 WINAPI TD_GetNextTop10UInt(TakionIterator* iterator, Price& price, unsigned int& uintValue);

TakionIterator* WINAPI TD_CreateTop10GainersIterator();
TakionIterator* WINAPI TD_CreateTop10LosersIterator();
TakionIterator* WINAPI TD_CreateTop10PercentGainersIterator();
TakionIterator* WINAPI TD_CreateTop10PercentLosersIterator();
unsigned __int64 WINAPI TD_GetNextTop10SignedPrice(TakionIterator* iterator, Price& price, SignedPrice& netChange);

unsigned int WINAPI TD_GetTop10Count();//Number of objects in top 10 messages and top 10 windows

void WINAPI TD_NullifyOrderUserData(const unsigned int* extensionId);//unsigned int array terminated with 0.

enum EchoNotificationObjectId : unsigned char
{
	ENO_STOCK,
	ENO_SORTABLE_STOCK,
#ifndef TAKION_NO_OPTIONS
	ENO_OPTION,
	ENO_FUTURE,
#endif
	ENO_Count
};

//echoNotificationObjectMask is composed of the flags above. More flags can be added in the future.
//echoId must be >= TU_GetSecurityMinCustomEchoId()
//All the objects defined by the echoNotificationObjectMask, will be notified in their worker thread with message TMessageObjectEcho(echoId);
void WINAPI TD_NotifyAllObjectsInThread(unsigned int echoNotificationObjectMask, unsigned int echoId);

unsigned char WINAPI TD_GetReservedConnectionType();

//The following 3 functions work only if dataType >= TD_GetReservedConnectionType()
bool WINAPI TD_WriteToConnection(unsigned char dataType, const char* data, unsigned int length);
bool WINAPI TD_WriteMessageToConnection(unsigned char dataType, const Message* message);
unsigned int WINAPI TD_WriteBuffersToConnection(unsigned char dataType, const WSABUF* cursor, unsigned int count);
//

const char* WINAPI TD_GetServerConnectionName(unsigned int serverConnectionId);//enum ServerConnectionId
unsigned int WINAPI TD_GetServerConnectionId(const char* serverConnectionName);

unsigned int WINAPI TD_GetStockMarketDataSubscriptionRequestId();
unsigned int WINAPI TD_GetStockMarketSorterSubscriptionRequestId();

#ifndef TAKION_NO_OPTIONS
unsigned int WINAPI TD_GetFutureMarketDataSubscriptionRequestId();
unsigned int WINAPI TD_GetOptionUnderlierMarketDataSubscriptionRequestId();
unsigned int WINAPI TD_GetOptionMarketDataSubscriptionRequestId();
#endif

//For debugging
bool WINAPI TD_LockModificationMsStock(const unsigned __int64& numericSymbol);
bool WINAPI TD_UnlockModificationMsStock(const unsigned __int64& numericSymbol);
bool WINAPI TD_LockModificationMdStock(const unsigned __int64& numericSymbol);
bool WINAPI TD_UnlockModificationMdStock(const unsigned __int64& numericSymbol);
////

#ifdef __cplusplus
}
#endif

