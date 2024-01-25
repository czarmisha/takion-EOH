// Observer.h : main header file for the Observer DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#ifdef OBSERVER_EXPORTS
#define OBSERVER_API __declspec(dllexport)
#else
#define OBSERVER_API __declspec(dllimport)
#endif

#include <UtilsApi.h>
#include <list>

const char* const ObserverHeaderVersion = "1.0.6.51";

class Message
{
public:
	unsigned short m_length;
	unsigned short m_type;
protected:
	Message(const unsigned short& type, const unsigned short& length):m_length(length),m_type(type){}
};

//http://login2win.blogspot.com/2008/05/c-observer-patterm.html
// ---------------- Observer interface -----------------
class OBSERVER_API Observer
{
friend class Observable;
public:
//	typedef std::set<Observable*> ObservableSet;
#if (_MSC_VER > 1600)
	typedef std::unordered_set<Observable*> ObservableSet;
#else
	typedef std::hash_set<Observable*> ObservableSet;
#endif
	virtual ~Observer(){Detach();}
	virtual void Notify(const Message* message, const Observable* from, const Message* info = NULL) = 0;
	void Detach();
protected:
	Observer(){}
	Observer(const Observer& other){}
	ObservableSet m_observables;
//	ObservableSet::iterator m_begin;
//	ObservableSet::iterator m_end;
};

// ---------------- Observable object -------------------
class OBSERVER_API Observable
{
friend class Observer;
public:
//	typedef std::list<Observer*> ObserverList;
	typedef std::set<Observer*> ObserverSet;
//	typedef std::hash_set<Observer*> ObserverSet;
	Observable():m_begin(m_observers.begin()),m_end(m_observers.end()){}//{UpdateIterators();}
	Observable(const Observable& other):m_begin(m_observers.begin()),m_end(m_observers.end()){}//{UpdateIterators();}
	virtual ~Observable();
	bool AddObserver(Observer* o) const;
	bool RemoveObserver(Observer* o) const;
	void ClearObservers() const;
	void NotifyObservers(const Message* message, const Message* info = NULL, const Observable* from = NULL) const;
	unsigned int GetObserverCount() const{return (unsigned int)m_observers.size();}
	bool isObservableEmpty() const{return m_observers.empty();}
	bool HasObserver(Observer* o) const{ObserverSet::const_iterator found = m_observers.find(o); return found != m_end;}
	bool HasSingleObserverOrNone(Observer* o) const
	{
		switch(GetObserverCount())
		{
			case 0:
			return true;

			case 1:
			return HasObserver(o);

			default:
			return false;
		}
	}
protected:
	virtual void OnObserverAdded(Observer* o) const{}
	virtual void OnObserverRemoved(Observer* o) const{}
	bool DoRemoveObserver(Observer* o) const;
	void DoRemoveObserverByIterator(ObserverSet::iterator& found) const;
	void UpdateIterators() const
	{
		m_begin = m_observers.begin();
//		m_end = m_observers.end();
	}
	mutable ObserverSet m_observers;
	mutable ObserverSet::iterator m_begin;
	mutable ObserverSet::iterator m_end;

	typedef std::list<ObserverSet::iterator*> IteratorList;
	mutable IteratorList m_iteratorList;
};

class RingBufferListEventNotification;

class OBSERVER_API MessageThreadBase : public TakionThreadBase
{
friend class MessageReader;
friend unsigned int __stdcall MessageThreadFunction(void* data);
public:
	virtual ~MessageThreadBase();
	void WriteMessage(const Message* message);//called from main thread
//	void WriteControlMessage(const Message* message);//called from main thread
	void WriteBuffers(WSABUF* data, unsigned int count, unsigned int totalLength);//called from main thread
	virtual void ThreadInfoToString(std::string& info) const;
	const bool& isExited() const{return m_exited;}
	bool Restart();
protected:
	MessageThreadBase(const char* name, int priority = 0, unsigned int waitToTerminate = INFINITE, unsigned int padSize = 0);

	virtual bool InvalidateData() override;
//	virtual bool ProcessControlMessage(const Message* message) = 0;
	virtual void NotifyOverflow(){}

	virtual bool ProcessDataMessage(const Message* message) = 0;

	void Terminate()//Call this function in the derived class Destructor to finish all data processing
	{
		m_dataOk = false;
		SetEvent(m_event);
		WaitForSingleObject(m_threadHandle, m_waitToTerminate);
	}

	void ReadMessage();//called from this thread

	HANDLE m_event;
	RingBufferListEventNotification* m_ringBuffer;

	MessageReader* m_messageReader;
	bool m_exited;
};

#ifdef __cplusplus
extern "C"
{
#endif

const char* WINAPI O_GetModuleVersionStr();
unsigned __int64 WINAPI O_GetModuleVersionNum();
const char* WINAPI O_GetHeaderVersion();
unsigned __int64 WINAPI O_GetHeaderVersionNum();
const char* WINAPI O_GetFilePathAndName();
const char* WINAPI O_GetPlatform();
const char* WINAPI O_GetFileDescription();
const char* WINAPI O_GetProductName();
void WINAPI O_GetDllBuildDescription(std::string& buildStr);

#ifdef __cplusplus
}
#endif
