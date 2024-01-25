#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#ifdef TL_EXPORTS
#define TL_API __declspec(dllexport)
#else
#define TL_API __declspec(dllimport)
#endif

#include <UtilsApi.h>

const char* const TakionLogHeaderVersion = "1.0.7.42";

class TL_API TakionTimeBase
{
public:
	static unsigned int takionMillisecondBase;
	static unsigned int takionServerMillisecondDelta;
	static unsigned int takionUtcMillisecondBase;
	static unsigned int takionServerMillisecondBase;
};

class TL_API TakionTimer
{
public:
	virtual ~TakionTimer(){}
	const unsigned int& GetId() const{return m_id;}
	void SetId(const unsigned int& id){m_id = id;}
//	unsigned int GetState() const{return m_state;}
//	void SetState(unsigned int state){m_state = state;}
	const bool& isOwn() const{return m_own;}
	void SetOwn(const bool& own){m_own = own;}
	virtual void Triggered(unsigned int count) = 0;
	virtual void Activate() = 0;
	virtual void AdjustOnTimeChange(unsigned int prevMillisecond, unsigned int currentMillisecond, unsigned int prevDate){}
	virtual unsigned int Reactivate(){return 0;}
	virtual unsigned int GetTriggerCode(unsigned int reactivateCode) const{return reactivateCode;}
	virtual bool isValid() const{return true;}
	virtual unsigned int GetState() const{return 0;}
	virtual void NextDayStarted(){}
protected:
//	TakionTimer(bool own = true):m_id(0xFFFFFFFF),m_state(0),m_own(own){}
	TakionTimer(const bool& own = true):m_id(0xFFFFFFFF),m_own(own){}
	unsigned int m_id;
//	unsigned int m_state;
	bool m_own;
};

class TL_API TakionTimerOnce : public TakionTimer
{
public:
	const unsigned int& GetMilliseconds() const{return m_milliseconds;}
	virtual void Activate() override;
	virtual unsigned int Reactivate() override;
	virtual bool isValid() const override{return m_milliseconds > 0;}
protected:
	TakionTimerOnce(const unsigned int& milliseconds, const bool& own = true):
		TakionTimer(own),
		m_milliseconds(milliseconds ? milliseconds : 1)
	{}
	unsigned int m_milliseconds;
};

class TL_API TakionTimerDayCycle : public TakionTimer
{
protected:
	TakionTimerDayCycle(const bool& own = true):TakionTimer(own){}
	void UpdateTimer();
};

class TL_API TakionTimerDayState : public TakionTimerDayCycle
{
public:
	virtual unsigned int GetState() const override{return m_state;}
	const unsigned int& GetStateCount() const{return m_stateCount;}
	virtual void Activate() override;
	virtual unsigned int Reactivate() override;
	virtual unsigned int GetTriggerCode(unsigned int reactivateCode) const override{return m_state + 1;}
	typedef std::map<unsigned int, unsigned int> StateMap;
	const StateMap& GetStateMap() const{return m_stateMap;}
	virtual void AdjustOnTimeChange(unsigned int prevMillisecond, unsigned int currentMillisecond, unsigned int prevDate) override;
	virtual bool isValid() const override{return m_stateCount > 1;}
//	virtual bool isValid() const override{return m_stateCount > 0;}
	void SetStateMap(const unsigned int* dayMillisecondArray, unsigned int stateCount)
	{
		m_stateMap.clear();
		for(; stateCount; --stateCount, ++dayMillisecondArray)
		{
			m_stateMap.insert(StateMap::value_type(*dayMillisecondArray, 0));
		}
		m_stateCount = (unsigned int)m_stateMap.size();
		unsigned int state = 0;
		m_stateMapBegin = m_stateMap.begin();
		for(StateMap::iterator it = m_stateMapBegin; it != m_stateMapEnd; ++it, ++state)
		{
			it->second = state;
		}
	}
	TakionTimerDayState& operator=(const TakionTimerDayState& other)
	{
		TakionTimerDayCycle::operator=(other);
		m_stateMap = other.m_stateMap;
		m_stateMapBegin = m_stateMap.begin();
		m_stateCount = other.m_stateCount;
		m_state = other.m_stateCount;
		return *this;
	}
protected:
	TakionTimerDayState(const unsigned int* dayMillisecondArray, unsigned int stateCount, const bool& own = true):
		TakionTimerDayCycle(own),
		m_stateMapEnd(m_stateMap.end()),
		m_stateMapBegin(m_stateMap.begin()),
		m_stateCount(0),
		m_state(0)
	{
		SetStateMap(dayMillisecondArray, stateCount);
/*
		for(; stateCount; --stateCount, ++dayMillisecondArray)
		{
			m_stateMap.insert(StateMap::value_type(*dayMillisecondArray, 0));
		}
		m_stateCount = (unsigned int)m_stateMap.size();
		unsigned int state = 0;
		m_stateMapBegin = m_stateMap.begin();
		for(StateMap::iterator it = m_stateMapBegin; it != m_stateMapEnd; ++it, ++state)
		{
			it->second = state;
		}
*/
	}
	TakionTimerDayState(const TakionTimerDayState& other):
		TakionTimerDayCycle(other),
		m_stateMap(other.m_stateMap),
		m_stateMapEnd(m_stateMap.end()),
		m_stateMapBegin(m_stateMap.begin()),
		m_stateCount(other.m_stateCount),
		m_state(other.m_stateCount)
	{
	}
	unsigned int UpdateState();
	StateMap m_stateMap;
	StateMap::iterator m_stateMapEnd;
	StateMap::iterator m_stateMapBegin;
	unsigned int m_stateCount;
	unsigned int m_state;
};

class TL_API TakionTimerOnceADay : public TakionTimerDayCycle
{
public:
	virtual unsigned int GetState() const override{return m_triggered ? 1 : 0;}
	virtual void Activate() override;
	virtual unsigned int Reactivate() override;
	virtual unsigned int GetTriggerCode(unsigned int reactivateCode) const override{return m_triggered ? 2 : 1;}
	virtual void AdjustOnTimeChange(unsigned int prevMillisecond, unsigned int currentMillisecond, unsigned int prevDate) override;
	virtual bool isValid() const override{return m_millisecondToTrigger < 86400000;}
	const bool& isTriggered() const{return m_triggered;}
	void SetMillisecondToTrigger(unsigned int millisecondToTrigger);
//	virtual void NextDayStarted() override{Activate();}
protected:
	TakionTimerOnceADay(const unsigned int& millisecondToTrigger, const bool& own = true):
		TakionTimerDayCycle(own),
		m_millisecondToTrigger(millisecondToTrigger),
		m_timerSetAt(0xFFFFFFFF),
		m_triggered(false)
	{
	}
	unsigned int UpdateState();
	unsigned int m_millisecondToTrigger;
	unsigned int m_timerSetAt;
	bool m_triggered;
};

class TL_API TakionTimerRepeat : public TakionTimer
{
public:
	unsigned int GetCycleCount() const{return m_cycleCount;}
	unsigned int GetCycle() const{return m_cycle;}
	unsigned int GetHalfCycle() const{return m_halfCycle;}
	unsigned int GetOffset() const{return m_offset;}
//	unsigned int GetAdjustFrequency() const{return m_adjustFrequency;}
//	void SetAdjustFrequency(unsigned int frequency){m_adjustFrequency = frequency;}
	virtual void Activate() override;
	virtual unsigned int Reactivate() override;
//	virtual void AdjustOnTimeChange(unsigned int prevMillisecond, unsigned int currentMillisecond, unsigned int prevDate){DoActivate();}
	virtual bool isValid() const override{return m_cycle > 0;}
//	void SetValues(unsigned int cycle, unsigned int offset, unsigned int adjustFrequency = 0)
	void SetValues(unsigned int cycle, unsigned int offset)
	{
//		if(adjustFrequency)m_adjustFrequency = adjustFrequency;
		if(!cycle)cycle = 1;
		offset %= cycle;
		bool changed = false;
		if(m_cycle != cycle)
		{
			m_cycle = cycle;
			m_halfCycle = m_cycle >> 1;
			changed = true;
		}
		if(m_offset != offset)
		{
			m_offset = offset;
			changed = true;
		}
		if(changed)Activate();
	}
	unsigned int CalculateCycleCount(const unsigned int& millisecond) const{return (millisecond - m_offset + m_halfCycle) / m_cycle;}
protected:
//	TakionTimerRepeat(unsigned int cycle, unsigned int offset, unsigned int adjustFrequency = 1, bool own = true):
	TakionTimerRepeat(unsigned int cycle, unsigned int offset, bool own = true):
		TakionTimer(own),
		m_cycle(cycle ? cycle : 1),
		m_halfCycle(m_cycle >> 1),
		m_offset(offset % m_cycle),
//		m_adjustFrequency(adjustFrequency),
//		m_adjustCount(0),
		m_cycleCount(0),
		m_timerSetting(0)
	{}
	unsigned int DoActivate();
	unsigned int m_cycle;
	unsigned int m_halfCycle;
	unsigned int m_offset;
//	unsigned int m_adjustFrequency;
//	unsigned int m_adjustCount;
	unsigned int m_cycleCount;
	unsigned int m_timerSetting;
};

#ifdef __cplusplus
extern "C"
{
#endif

const char* WINAPI TL_GetModuleVersionStr();
unsigned __int64 WINAPI TL_GetModuleVersionNum();
const char* WINAPI TL_GetHeaderVersion();
unsigned __int64 WINAPI TL_GetHeaderVersionNum();
const char* WINAPI TL_GetFilePathAndName();
const char* WINAPI TL_GetPlatform();
const char* WINAPI TL_GetFileDescription();
const char* WINAPI TL_GetProductName();
void WINAPI TL_GetDllBuildDescription(std::string& buildStr);

const TIME_ZONE_INFORMATION& WINAPI TL_GetNewYorkTimeZone();
unsigned int WINAPI TL_GetNewYorkTimeZoneDiff();
unsigned int WINAPI TL_GetDayMillisecondFromSystemTime(const SYSTEMTIME& t);

inline unsigned int TL_GetCurrentMillisecond()
{
	return TakionTimeBase::takionMillisecondBase + GetTickCount();
}

inline short TL_GetDelay(const unsigned int& fromMillisecond)
{
	unsigned int delay = TL_GetCurrentMillisecond();
	if(fromMillisecond <= delay)
	{
		delay -= fromMillisecond;
		return delay > 0x7FFF ? 0x7FFF : (short)delay;
	}
	else
	{
		delay = fromMillisecond - delay;
		return delay > 0x7FFF ? -0x7FFF : -(short)delay;
	}
}

inline unsigned int TL_GetCurrentUtcMillisecond()
{
	return TakionTimeBase::takionUtcMillisecondBase + GetTickCount();
}

inline unsigned int TL_GetCurrentServerMillisecond()
{
	return TakionTimeBase::takionServerMillisecondBase + GetTickCount();
}

inline unsigned int TL_GetCurrentTimeTokens(unsigned int& hour, unsigned int& minute, unsigned int& second)
{
	return U_GetTimeTokensFromMillisecond(TL_GetCurrentMillisecond(), hour, minute, second);
}

inline unsigned int TL_GetCurrentTimeDigitTokens(unsigned char& hour1, unsigned char& hour2, unsigned char& minute1, unsigned char& minute2, unsigned char& second1, unsigned char& second2)
{
	return U_GetTimeDigitTokensFromMillisecond(TL_GetCurrentMillisecond(), hour1, hour2, minute1, minute2, second1, second2);
}

inline unsigned int TL_GetCurrentServerTimeTokens(unsigned int& hour, unsigned int& minute, unsigned int& second)
{
	return U_GetTimeTokensFromMillisecond(TL_GetCurrentServerMillisecond(), hour, minute, second);
}

const bool& WINAPI TL_IsServerTimeInitialized();

//returns localMillisecond
inline unsigned int TL_GetCurrentServerAndLocalTimeTokens(unsigned int& localHour, unsigned int& localMinute, unsigned int& localSecond, unsigned int& localMillisecond, unsigned int& serverHour, unsigned int& serverMinute, unsigned int& serverSecond, unsigned int& serverMillisecond)
{
	localMillisecond = TL_GetCurrentMillisecond();
	serverMillisecond = localMillisecond + TakionTimeBase::takionServerMillisecondDelta;

	U_GetTimeTokensFromMillisecond(localMillisecond, localHour, localMinute, localSecond);
	U_GetTimeTokensFromMillisecond(serverMillisecond, serverHour, serverMinute, serverSecond);
	return localMillisecond;
}

bool WINAPI TL_IsLeapYear(unsigned int year);
const unsigned int* WINAPI TL_GetDaysInAllMonths(unsigned int year);
unsigned int WINAPI TL_GetDaysInMonth(unsigned int month, unsigned int year);
const unsigned int* WINAPI TL_GetDaysInAllMonthsCumulative(unsigned int year);
unsigned int WINAPI TL_GetDaysInMonthCumulative(unsigned int month, unsigned int year);
unsigned int WINAPI TL_GetDaysBetweenMonths(unsigned int month1, unsigned int month2, unsigned int year);
unsigned int WINAPI TL_GetDaysToYearStart(unsigned int year, unsigned int month, unsigned int day);
unsigned int WINAPI TL_GetDaysToYearEnd(unsigned int year, unsigned int month, unsigned int day);
unsigned int WINAPI TL_GetDaysToMonthStart(unsigned int year, unsigned int month, unsigned int& day);
unsigned int WINAPI TL_GetDaysToMonthEnd(unsigned int year, unsigned int month, unsigned int& day);
unsigned int WINAPI TL_GetDaysBetweenYears(unsigned int year1, unsigned int year2);
bool WINAPI TL_IsDateValid(unsigned int year, unsigned int month, unsigned int day);
bool WINAPI TL_IsDatePassed(unsigned int year, unsigned int month, unsigned int day);
void WINAPI TL_DateAddDays(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int days);
void WINAPI TL_DateSubtractDays(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int days);
void WINAPI TL_DateAddWeeks(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int weeks);
void WINAPI TL_DateSubtractWeeks(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int weeks);
void WINAPI TL_DateAddMonths(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int months);
void WINAPI TL_DateSubtractMonths(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int months);
void WINAPI TL_DateSubtractYears(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int years);
void WINAPI TL_DateAddBusinessDays(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int days);
void WINAPI TL_DateSubtractBusinessDays(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int days);
bool WINAPI TL_GetBusinessDateNext(unsigned int& year, unsigned int& month, unsigned int& day);
bool WINAPI TL_GetBusinessDatePrevious(unsigned int& year, unsigned int& month, unsigned int& day);
int WINAPI TL_DateDiff(unsigned int year1, unsigned int month1, unsigned int day1, unsigned int year2, unsigned int month2, unsigned int day2);
int WINAPI TL_CompareDates(unsigned int year1, unsigned int month1, unsigned int day1, unsigned int year2, unsigned int month2, unsigned int day2);
int WINAPI TL_GetDayFrom1970(unsigned int year, unsigned int month, unsigned int day);
void WINAPI TL_GetDateFrom1970(unsigned int& year, unsigned int& month, unsigned int& day, int days);
unsigned int WINAPI TL_CalculateDayCountFromDate(unsigned int year, unsigned int month, unsigned int day);
void WINAPI TL_CalculateDateFromDayCount(unsigned int days, unsigned int& year, unsigned int& month, unsigned int& day);
unsigned int WINAPI TL_GetDayOfWeek(unsigned int year, unsigned int month, unsigned int day);
unsigned int WINAPI TL_GetDateForDayOfWeek(unsigned int year, unsigned int month, unsigned int dayOfWeek, unsigned int ordinal);
unsigned int WINAPI TL_CalculateBusinessDayCountFromDate(unsigned int year, unsigned int month, unsigned int day);
void WINAPI TL_CalculateDateFromBusinessDayCount(unsigned int businessDays, unsigned int& year, unsigned int& month, unsigned int& day);
int WINAPI TL_BusinessDateDiff(unsigned int year1, unsigned int month1, unsigned int day1, unsigned int year2, unsigned int month2, unsigned int day2);
int WINAPI TL_BusinessDateDiffByFormattedDates(unsigned int date1, unsigned int date2);
unsigned int WINAPI TL_CalculateBusinessDayCountSinceYearStart(unsigned int year, unsigned int month, unsigned int day);
void WINAPI TL_CalculateDateFromYearBusinessDayCount(unsigned int businessDays, unsigned int year, unsigned int& month, unsigned int& day);

void WINAPI TL_GetDateDaysAheadFromToday(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int days);
void WINAPI TL_GetDateDaysBackFromToday(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int days);

unsigned int WINAPI TL_DateInMultiplyFormatAddDays(unsigned int dateInMultiplyFormat, unsigned int days);
unsigned int WINAPI TL_DateInMultiplyFormatSubtractDays(unsigned int dateInMultiplyFormat, unsigned int days);

unsigned int WINAPI TL_GetHolidayCountBetweenDatesOfOneYear(unsigned int year, unsigned int month1, unsigned int day1, unsigned int month2, unsigned int day2);
unsigned int WINAPI TL_GetHolidayCountBetweenDates(unsigned int year1, unsigned int month1, unsigned int day1, unsigned int year2, unsigned int month2, unsigned int day2);

unsigned int WINAPI TL_GetTodaysUtcDate();
unsigned int WINAPI TL_GetTodaysUtcDayOfWeek();
unsigned int WINAPI TL_GetUtcYear();
unsigned int WINAPI TL_GetUtcMonth();
unsigned int WINAPI TL_GetUtcDay();
unsigned int WINAPI TL_GetUtcTimeFromNyTimeAndReturnUtcDate(unsigned int& nyMillisecond);

unsigned int WINAPI TL_GetTodaysDate();//Number of days since Jan 1 1970
unsigned int WINAPI TL_GetTodaysDateInFullShiftFormat();//((unsigned int)year << 16) | ((unsigned int)(month) << 8) | (unsigned int)day;
unsigned int WINAPI TL_GetTodaysDateInShiftFormat();//((unsigned int)year << 9) | ((unsigned int)(month) << 5) | (unsigned int)day;
unsigned int WINAPI TL_GetTodaysDateInMultiplyFormat();//(unsigned int)year * 10000 + (unsigned int)month * 100 + day;

unsigned int WINAPI TL_GetPreviousDate();//Number of days since Jan 1 1970
unsigned int WINAPI TL_GetPreviousDateInFullShiftFormat();
unsigned int WINAPI TL_GetPreviousDateInShiftFormat();
unsigned int WINAPI TL_GetPreviousDateInMultiplyFormat();

unsigned int WINAPI TL_GetTodaysDayOfWeek();
unsigned int WINAPI TL_GetYear();
unsigned int WINAPI TL_GetMonth();
unsigned int WINAPI TL_GetDay();

unsigned int WINAPI TL_GetMaxDate();

unsigned int WINAPI TL_GetYearPrev();
unsigned int WINAPI TL_GetMonthPrev();
unsigned int WINAPI TL_GetDayPrev();

unsigned int WINAPI TL_GetYearBusinessPrev();
unsigned int WINAPI TL_GetMonthBusinessPrev();
unsigned int WINAPI TL_GetDayBusinessPrev();
unsigned int WINAPI TL_GetPreviousBusinessDateInShiftFormat();
void WINAPI TL_GetDateTokensBusinessPrev(unsigned int& year, unsigned int& month, unsigned int& day);
bool WINAPI TL_IsDateBusinessPrev(const unsigned int year, const unsigned int month, const unsigned int day);
unsigned int WINAPI TL_GetPreviousMarketCloseTimeInShiftFormat();

bool WINAPI TL_IsTodayShortDay();
unsigned short WINAPI TL_GetCloseMarketMinute();
unsigned int WINAPI TL_GetCloseMarketMillisecond();

bool WINAPI TL_IsTodayWeekend();
bool WINAPI TL_IsTodayHoliday();
bool WINAPI TL_IsTodayMarketOpen();

unsigned short WINAPI TL_GetOpenMarketMinute();
unsigned int WINAPI TL_GetOpenMarketMillisecond();

unsigned __int64 WINAPI TL_GetPerformanceFrequency();
unsigned int WINAPI TL_GetTickResolution();

unsigned int WINAPI TL_GetTimeAdjustment();
unsigned int WINAPI TL_GetTimeIncrement();
bool WINAPI TL_IsTimeAdjustmentDisabled();

const char* WINAPI TL_GetDayOfWeekName(unsigned int dayOfWeek);
const char* WINAPI TL_GetDayOfWeekShortName(unsigned int dayOfWeek);

//http://www.nasdaqtrader.com/Trader.aspx?id=Calendar
enum Holiday : unsigned char
{
	TLH_NEW_YEAR,
	TLH_MLK_DAY,
	TLH_PRESIDENTS,
	TLH_GOOD_FRIDAY,
	TLH_MEMORIAL,
	TLH_JUNETEENTH,
	TLH_INDEPENDENCE,
	TLH_LABOR,
	TLH_THANKSGIVING,
	TLH_CHRISTMAS,

	TLH_HOLIDAY_COUNT
};

enum ShortDay : unsigned char
{
	TLS_BEFORE_INDEPENDENCE,
	TLS_AFTER_THANKSGIVING,
	TLS_BEFORE_CHRISTMAS,

	TLS_SHORT_DAY_COUNT
};

Holiday WINAPI TL_GetTodaysHoliday();
ShortDay WINAPI TL_GetTodaysShortDay();

const char* WINAPI TL_GetHolidayName(Holiday holiday);
const char* WINAPI TL_GetShortDayName(ShortDay shortDay);

bool WINAPI TL_GetHolidayDate(Holiday holiday, unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetNewYearDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetMartinLutherKingDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetPresidentsDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetGoodFridayDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetMemorialDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetJuneteenthDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetIndependenceDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetLaborDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetThanksgivingDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetChristmasDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);

Holiday WINAPI TL_IsHoliday(unsigned int year, unsigned int month, unsigned int day);

bool WINAPI TL_GetShortDayDate(ShortDay shortDay, unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetBeforeIndependenceDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetAfterThanksgivingDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
bool WINAPI TL_GetBeforeChristmasDate(unsigned int year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
ShortDay WINAPI TL_IsShortDay(unsigned int year, unsigned int month, unsigned int day);

Holiday WINAPI TL_GetNextHoliday(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);
ShortDay WINAPI TL_GetNextShortDay(unsigned int& year, unsigned int& month, unsigned int& day, unsigned int& dayOfWeek);

bool WINAPI TL_IsDateNewBusinessWeek(unsigned int year, unsigned int month, unsigned int day);
bool WINAPI TL_IsDateNewBusinessMonth(unsigned int year, unsigned int month, unsigned int day);
bool WINAPI TL_IsDateNewBusinessYear(unsigned int year, unsigned int month, unsigned int day);
void WINAPI TL_IsDateNewBusinessWeekMonthYear(unsigned int year, unsigned int month, unsigned int day, bool& newWeek, bool& newMonth, bool& newYear);
bool WINAPI TL_IsTodayNewBusinessWeek();
bool WINAPI TL_IsTodayNewBusinessMonth();
bool WINAPI TL_IsTodayNewBusinessYear();

void* WINAPI TL_CreateLogFile(const char* name,
	bool outputTime = true,
	bool outputDate = true,
	const char* extension = "log",
	unsigned int date = 0,
	const char* path = nullptr,
	bool open = true,
	bool wipe = false,
	bool wipeOnNewDay = false,
	bool existingOnly = false);
void WINAPI TL_DestroyLogFile(void* logFile);
void WINAPI TL_OpenLogFile(void* logFile, bool wipe = false);
bool WINAPI TL_WipeLogFile(void* logFile);
bool WINAPI TL_RemoveLogFile(void* logFile);
void WINAPI TL_CloseLogFile(void* logFile);
void WINAPI TL_Log(void* logFile, const char* message, const char* prefix = nullptr, unsigned int level = 0);
void WINAPI TL_LogUpToLength(void* logFile, const char* message, unsigned int length, const char* prefix = nullptr, unsigned int level = 0);
const char* WINAPI TL_GetLogFilePath(const void* logFile);
bool WINAPI TL_IsLogFileValid(const void* logFile);
unsigned int WINAPI TL_GetOpenFileError(const void* logFile);
const char* WINAPI TL_GetOpenFileErrorMessage(const void* logFile);
const char* WINAPI TL_GetDateStr(const void* logFile);
void WINAPI TL_DestroyLogFiles();

bool WINAPI TL_ClearLogFilesBeforeDaysAgo(const char* name, unsigned int daysAgo, const char* extension = "log", const char* path = nullptr);
void WINAPI TL_SetDaysToKeepLogFiles(unsigned int days);
void WINAPI TL_ClearAllObsoleteLogFiles(const std::string* except);

void WINAPI TL_SetLogFile(void* logFile);
void* WINAPI TL_GetLogFile();

void WINAPI TL_CloseAllLogFiles();
bool WINAPI TL_GetPrevLogFilePathAndName(std::string& filePathAndName);
const char* WINAPI TL_GetDateFromFileName(const char* name, unsigned int& year, unsigned int& month, unsigned int& day);
bool WINAPI TL_IsPrevLogFileExist(const char* filePathAndName);

unsigned int WINAPI TL_GetStartMillisecond();
unsigned int WINAPI TL_GetStartDate();
void WINAPI TL_GetStartDateTokens(unsigned int& year, unsigned int& month, unsigned int& day);
void WINAPI TL_FormatStartDateAndTime(std::string& str, bool appendMillisecond, bool monthName, bool fullYear, char dateTimeSeparator = ' ', char dateSeparator = '-', char timeSeparator = ':', char millisecondSeparator = '-', char del = '\0');
void WINAPI TL_GetCurrentNewYorkTime(SYSTEMTIME& nyTime);

void WINAPI TL_AdjustTimeForward(unsigned int millisecond);
void WINAPI TL_AdjustTimeBackward(unsigned int millisecond);

typedef void (WINAPI *NextDayStartedCallback)();
void WINAPI TL_RegisterNextDayStartedCallback(NextDayStartedCallback func);
void WINAPI TL_UnregisterNextDayStartedCallback(NextDayStartedCallback func);

void WINAPI TL_RegisterUtcNextDayStartedCallback(NextDayStartedCallback func);
void WINAPI TL_UnregisterUtcNextDayStartedCallback(NextDayStartedCallback func);

typedef void (WINAPI *TimeChangedCallback)(unsigned int prevMillisecond, unsigned int currentMillisecond, unsigned int todaysDate);
void WINAPI TL_RegisterTimeChangedCallback(TimeChangedCallback func);
void WINAPI TL_UnregisterTimeChangedCallback(TimeChangedCallback func);

bool WINAPI TL_AddTimer(TakionTimer* timer);
bool WINAPI TL_RemoveTimer(TakionTimer* timer);

unsigned int WINAPI TL_GetLogLevel(const void* logFile);
void WINAPI TL_SetLogLevel(void* logFile, unsigned int level);

bool WINAPI TL_IsLogBufferEmpty(void* logFile);
void WINAPI TL_ForceOutput(void* logFile);

bool WINAPI TL_IsInLogThread(std::string& filePath);

void WINAPI TL_DateNumToStr(unsigned int date, std::string& dateStr);
unsigned int WINAPI TL_DateStrToNum(const char* dateStr);

bool WINAPI TL_IsTodaysDate(const char* cursor, char separator = '-');
bool WINAPI TL_IsPreviousDate(const char* cursor, char separator = '-');

#ifdef __cplusplus
}
#endif

