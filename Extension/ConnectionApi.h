#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include <ObserverApi.h>

#ifdef RECEIVER_EXPORTS
#define RECEIVER_API __declspec(dllexport)
#else
#define RECEIVER_API __declspec(dllimport)
#endif

const char* const ReceiverHeaderVersion = "1.0.7.32";

/////
class RECEIVER_API ConnectionLine
{
public:
	ConnectionLine(const char* addressName,
		unsigned short port,
		const char* bindAddressName = nullptr,
		unsigned short bindPort = 0);
	ConnectionLine(const ConnectionLine& other);
#ifdef _DEBUG
	virtual ~ConnectionLine(){}
#endif
	ConnectionLine& operator=(const ConnectionLine& other);
	ConnectionLine* Clone() const{return new ConnectionLine(*this);}
	const unsigned __int64& GetIpPort() const{return m_ipport;}
	const unsigned __int64& GetBindIpPort() const{return m_bindIpport;}
	const char* GetIpAddressName() const{return m_addressName.c_str();}
	const char* GetIpBindAddressName() const{return m_bindAddressName.c_str();}
	const char* GetIpAddress() const{return m_address.c_str();}
	const char* GetIpBindAddress() const{return m_bindAddress.c_str();}
	const unsigned short& GetPort() const{return m_port;}
	const unsigned short& GetBindPort() const{return m_bindPort;}

	const std::string& GetIpAddressNameStr() const{return m_addressName;}
	const std::string& GetIpBindAddressNameStr() const{return m_bindAddressName;}
	const std::string& GetIpAddressStr() const{return m_address;}
	const std::string& GetIpBindAddressStr() const{return m_bindAddress;}

	const unsigned int& GetIpNumAddress() const{return m_ipNumAddress;}
	const unsigned int& GetIpInvAddress() const{return m_ipInvAddress;}
	const unsigned int& GetIpNumBindAddress() const{return m_ipNumBindAddress;}
	const unsigned int& GetIpInvBindAddress() const{return m_ipInvBindAddress;}

	static unsigned __int64 CalculateIpPort(unsigned int ip, unsigned short port){return ((unsigned __int64)ip << 16) | (unsigned __int64)port;}
	static unsigned __int64 CalculateIpPort(const char* ip, unsigned short port);

	void UpdateIpPort(){m_ipport = CalculateIpPort(m_ipInvAddress, m_port); m_bindIpport = CalculateIpPort(m_ipInvBindAddress, m_bindPort);}

	bool isIdentical(const ConnectionLine& other) const{return m_ipport == other.m_ipport && m_bindIpport == other.m_bindIpport;}
	bool operator==(const ConnectionLine& other) const{return m_ipport == other.m_ipport;}// && m_bindIpport == other.m_bindIpport;}
	bool operator<(const ConnectionLine& other) const{return m_ipport < other.m_ipport;}// || m_ipport == other.m_ipport && m_bindIpport < other.m_bindIpport;}
	bool operator>(const ConnectionLine& other) const{return m_ipport > other.m_ipport;}// || m_ipport == other.m_ipport && m_bindIpport > other.m_bindIpport;}
	bool operator!=(const ConnectionLine& other) const{return !operator==(other);}
	bool operator<=(const ConnectionLine& other) const{return !operator>(other);}
	bool operator>=(const ConnectionLine& other) const{return !operator<(other);}
	void UpdatePrevious()
	{
		m_prevAddress = m_address;
		m_prevPort = m_port;
	}
	const char* GetPrevIpAddress() const{return m_prevAddress.c_str();}
	const unsigned short& GetPrevPort() const{return m_prevPort;}
	operator unsigned __int64() const{return m_ipport;}
protected:
	std::string m_addressName;

	std::string m_prevAddress;

	std::string m_bindAddressName;
	std::string m_address;
	std::string m_bindAddress;
	unsigned short m_port;
	unsigned short m_bindPort;
	unsigned short m_prevPort;

	unsigned __int64 m_ipport;
	unsigned __int64 m_bindIpport;

	unsigned int m_ipNumAddress;
	unsigned int m_ipInvAddress;
	unsigned int m_ipNumBindAddress;
	unsigned int m_ipInvBindAddress;
};

class ConnectionProperties
{
public:
	virtual ~ConnectionProperties(){}
	const char* GetName() const{return m_connectionName.c_str();}
	const char* GetLoginId() const{return m_loginID.c_str();}
	const char* GetPassword() const{return m_password.c_str();}
	const std::string& GetTextMessageDelimiter() const{return m_textMessageDelimiter;}

	void SetConnectionName(const char* const& name){m_connectionName = name;}
	void SetLoginId(const char* const& loginId){m_loginID = loginId;}
	void SetPassword(const char* const& password){m_password = password;}

	const unsigned char& GetConnectionDataType() const{return m_connectionDataType;}
	void SetConnectionDataType(const unsigned char& connectionDataType){m_connectionDataType = connectionDataType;}
	const unsigned char& GetPrevConnectionDataType() const{return m_prevConnectionDataType;}
	const unsigned int& GetReconnectInterval() const{return m_reconnectInterval;}

	const unsigned int& GetBufferSizeReceiveRequested() const{return m_bufferSizeReceiveRequested;}
	const unsigned int& GetBufferSizeSendRequested() const{return m_bufferSizeSendRequested;}

	void SetReconnectInterval(const unsigned int& interval){m_reconnectInterval = interval;}

	bool isSameName(const ConnectionProperties& other) const{return m_connectionName == other.m_connectionName;}
	bool isSameLoginId(const ConnectionProperties& other) const{return m_loginID == other.m_loginID;}
	bool isSameReconnectInterval(const ConnectionProperties& other) const{return m_reconnectInterval == other.m_reconnectInterval;}

	inline const unsigned int& GetReconnectTries() const{return m_reconnectTries;}
	inline const unsigned int& GetMaxReconnectTries() const{return m_maxReconnectTries;}
	virtual unsigned int GetReconnectCount() const{return 0;}

	void SetReconnectTries(const unsigned int& tries){m_reconnectTries = tries;}
	void SetMaxReconnectTries(const unsigned int& tries){m_maxReconnectTries = tries;}
	void ResetReconnectTries(){m_reconnectTries = m_maxReconnectTries;}
	bool isReconnectable() const{return GetReconnectCount() < m_reconnectTries;}

protected:
	ConnectionProperties(const char* connectionName,
		const unsigned char connectionDataType,
		unsigned int receiveBufferSize = 0xFFFFFFFF,
		unsigned int sendBufferSize = 0xFFFFFFFF,
		unsigned int reconnectInterval = 5,
		unsigned int reconnectTries = 0,
		unsigned int maxReconnectTries = 0xFFFFFFFF,
		const char* loginID = "",
		const char* password = "",
		const char* textMessageDelimiter = "\r\n"):
		m_connectionName(connectionName),
		m_loginID(loginID),
		m_password(password),
		m_textMessageDelimiter(textMessageDelimiter),
		m_connectionDataType(connectionDataType),
		m_prevConnectionDataType(connectionDataType),
		m_reconnectInterval(reconnectInterval),
		m_bufferSizeReceiveRequested(receiveBufferSize),
		m_bufferSizeSendRequested(sendBufferSize),
		m_reconnectTries(reconnectTries),
		m_maxReconnectTries(maxReconnectTries)
	{
	}
/*
	ConnectionProperties(const ConnectionProperties& other):
		m_connectionName(other.m_connectionName),
		m_loginID(other.m_loginID),
		m_password(other.m_password),
		m_connectionDataType(other.m_connectionDataType),
		m_prevConnectionDataType(other.m_connectionDataType),
		m_reconnectInterval(other.m_reconnectInterval),
		m_bufferSizeReceiveRequested(other.m_bufferSizeReceiveRequested),
		m_bufferSizeSendRequested(other.m_bufferSizeSendRequested),
		m_reconnectTries(other.m_reconnectTries),
		m_maxReconnectTries(other.m_maxReconnectTries)
	{
	}
*/
	std::string	m_connectionName;
	std::string	m_loginID;
	std::string m_password;
	std::string m_textMessageDelimiter;
	unsigned char m_connectionDataType;
	unsigned char m_prevConnectionDataType;
	unsigned int m_reconnectInterval;
	unsigned int m_bufferSizeReceiveRequested;
	unsigned int m_bufferSizeSendRequested;

	unsigned int m_reconnectTries;
	unsigned int m_maxReconnectTries;
};

class RECEIVER_API ConnectionBase : public ConnectionProperties
{
public:
//	typedef ThreadSafeChain<ConnectionLine> ConnectionLineChain;
	typedef ThreadSafeChain<ConnectionLine*, true, unsigned __int64, false> ConnectionLineChain;
#ifdef _DEBUG
	virtual ~ConnectionBase(){}
#endif
	ConnectionLineChain& GetConnectionLineChain(){return m_connectionLineChain;}
	const ConnectionLineChain& GetConnectionLineChain() const{return m_connectionLineChain;}
	void ClearConnectionLines()
	{
		m_connectionLineChain.Clear();
	}
//	bool AddConnectionLine(const ConnectionLine& connectionLine){return m_connectionLineChain.AddChainItem(connectionLine);}
	bool AddConnectionLine(ConnectionLine* connectionLine){return m_connectionLineChain.AddChainItem(connectionLine) != 0;}

	bool AddConnectionLine(const char* addressName, unsigned short port, const char* bindAddressName = nullptr, unsigned short bindPort = 0);
	bool SameConnectionList(const ConnectionBase& other) const{return m_connectionLineChain.SameList(other.m_connectionLineChain);}
	bool isIntersectConnectionList(const ConnectionBase& other) const{return m_connectionLineChain.isListIntersect(other.m_connectionLineChain);}
	unsigned int GetConnectionLineCount() const{return m_connectionLineChain.GetCount();}
	virtual void ResetConnectionLines()
	{
		m_connectionLineChain.Reset();
	}
	virtual const ConnectionLine* GetCurrentConnectionLine() const{return m_connectionLineChain.GetCurrent();}
	virtual ConnectionLine* GetCurrentConnectionLine(){return m_connectionLineChain.GetCurrent();}
//	void Initialize();

	virtual const char* GetPrevIpAddress() const;
	virtual unsigned short GetPrevPort() const;
	virtual unsigned __int64 GetIpPort() const;
	virtual const char* GetIpAddress() const;
	virtual unsigned short GetPort() const;
	virtual const char* GetIpBindAddress() const;
	virtual unsigned short GetBindPort() const;
	virtual unsigned int GetIpNumAddress() const;
	virtual unsigned int GetIpInvAddress() const;
	virtual unsigned int GetIpNumBindAddress() const;
	virtual unsigned int GetIpInvBindAddress() const;

	bool SameIpPortList(const ConnectionBase& other) const;
	bool SetIpPort(unsigned __int64 ipport);

	inline bool operator==(const ConnectionBase& other) const
	{
		return SameIpPortList(other);
	}
	inline bool operator!=(const ConnectionBase& other) const{return !operator==(other);}
//	bool operator<(const ConnectionBase& other) const{return m_ipport < other.m_ipport;}

	bool isIdenticalConnection(const ConnectionBase& other) const;
	bool isIdentical(const ConnectionBase& other) const//isIdenticalConnection + same loginId and passord
	{
		return m_loginID == other.m_loginID && m_password == other.m_password && isIdenticalConnection(other);
	}

	virtual void UpdatePrevious();

	ConnectionBase& operator=(const ConnectionBase& other);
	const ConnectionLine* CreateNextIpAddress();
protected:
	ConnectionBase(const char* connectionName,
		const unsigned char connectionDataType,
		unsigned int receiveBufferSize,// = 0xFFFFFFFF,
		unsigned int sendBufferSize,// = 0xFFFFFFFF,
		unsigned int reconnectInterval = 5,
		unsigned int reconnectTries = 0,
		unsigned int maxReconnectTries = 0xFFFFFFFF,
		const char* loginID = "",
		const char* password = "",
		const char* textMessageDelimiter = "\r\n");
	ConnectionBase(const ConnectionBase& other);

	ConnectionLineChain m_connectionLineChain;
};

class ActiveConnection : public ConnectionBase
{
public:
	unsigned int GetBufferSizeReceiveActual() const{return m_bufferSizeReceiveActual;}
	unsigned int GetBufferSizeSendActual() const{return m_bufferSizeSendActual;}

	const bool& isConnected() const{return m_bConnected;}
	const bool& isConnecting() const{return m_bConnecting;}
	const bool& isDisconnecting() const{return m_bDisconnecting;}
	const bool& isLogged() const{return m_bLogged;}
	const bool& isFinalDisconnect() const{return m_finalDisconnect;}

	void SetLogged(const bool& logged){m_bLogged = logged;}

	const unsigned short& GetLocalPort() const{return m_localPort;}

	virtual unsigned int GetBytesReceived() const{return 0;}
	virtual unsigned int GetBytesSent() const{return 0;}
	virtual void AddRef(){}
	virtual void Release(){}
protected:
	ActiveConnection(const char* connectionName, 
		const unsigned char connectionDataType,
		unsigned int receiveBufferSize = 0xFFFFFFFF,
		unsigned int sendBufferSize = 0xFFFFFFFF,
		unsigned int reconnectSeconds = 5,
		unsigned int reconnectTries = 0,
		unsigned int maxReconnectTries = 0xFFFFFFFF,
		const char* loginID = "",
		const char* password = "",
		const char* textMessageDelimiter = "\r\n"):
		ConnectionBase(connectionName,
			connectionDataType,
			receiveBufferSize,
			sendBufferSize,
			reconnectSeconds,
			reconnectTries,
			maxReconnectTries,
			loginID,
			password,
			textMessageDelimiter),
		m_bufferSizeReceiveActual(0),
		m_bufferSizeSendActual(0),
		m_localPort(0),
		m_bConnected(false),
		m_bConnecting(false),
		m_bDisconnecting(false),
		m_bLogged(false),
		m_finalDisconnect(false)
	{
	}
	ActiveConnection(const ConnectionBase& connectionBase):
		ConnectionBase(connectionBase),
		m_bufferSizeReceiveActual(0),
		m_bufferSizeSendActual(0),
		m_localPort(0),
		m_bConnected(false),
		m_bConnecting(false),
		m_bDisconnecting(false),
		m_bLogged(false),
		m_finalDisconnect(false)
	{
	}
	unsigned int m_bufferSizeReceiveActual;
	unsigned int m_bufferSizeSendActual;
	unsigned short m_localPort;
	bool m_bConnected;
	bool m_bConnecting;
	bool m_bDisconnecting;
	bool m_bLogged;
	bool m_finalDisconnect;
};

class Connection : public ConnectionBase
{
public:
	Connection(const char* connectionName,
		const unsigned char connectionDataType,
		unsigned int receiveBufferSize,
		unsigned int sendBufferSize,
		unsigned int reconnectSeconds,
		unsigned int reconnectTries,
		unsigned int maxReconnectTries,
		const char* loginID = "",
		const char* password = "",
		const char* textMessageDelimiter = "\r\n"):
	
		ConnectionBase(connectionName,
			connectionDataType,
			receiveBufferSize,
			sendBufferSize,
			reconnectSeconds,
			reconnectTries,
			maxReconnectTries,
			loginID,
			password,
			textMessageDelimiter)
	{
	}
/*
	Connection(unsigned int reconnectSeconds):
		ConnectionBase("",
			0,
			65536,//receiveBufferSize
			0xFFFFFFFF,//8192,sendBufferSize,
			reconnectSeconds,
			1,
			0xFFFFFFFF)
	{
	}
*/
	Connection(const ConnectionBase& connectionBase):
		ConnectionBase(connectionBase)
	{
	}
#ifdef _DEBUG
	virtual ~Connection(){}
#endif
};

enum ExtensionMessageFormat : unsigned char
{
	EMF_TAKION,
	EMF_JSON,
	EMF_FIX,

	EMF_TEXT_END,

	EMF_TAKION_BIG_ENDIAN,

//	EMF_BRACES,

	EMF_Count
};

class IpPortKey
{
public:
	IpPortKey(const unsigned int& ip = 0, const unsigned short& port = 0):m_ip(ip),m_port(port){}
	const unsigned int& GetIp() const{return m_ip;}
	const unsigned short& GetPort() const{return m_port;}
	bool isZero() const{return !m_port && !m_ip;}
	bool operator<(const IpPortKey& other) const{return m_port < other.m_port || m_port == other.m_port && m_ip < other.m_ip;}
	bool operator<=(const IpPortKey& other) const{return m_port < other.m_port || m_port == other.m_port && m_ip <= other.m_ip;}
	bool operator==(const IpPortKey& other) const{return m_port == other.m_port && m_ip == other.m_ip;}
	bool operator!=(const IpPortKey& other) const{return !operator==(other);}
	bool operator>=(const IpPortKey& other) const{return !operator<(other);}
	bool operator>(const IpPortKey& other) const{return !operator<=(other);}
	bool operator!() const{return isZero();}
/*
	operator size_t() const{return
#ifdef _WIN64
		(unsigned __int64)m_port << 32 | m_ip;
#else
		(unsigned int)m_port << 16 | (unsigned short)m_ip;
#endif
	}
*/
	size_t GetHashValue() const{return
#ifdef _WIN64
		(unsigned __int64)m_port << 32 | m_ip;
#else
		(unsigned int)m_port << 16 | (unsigned short)m_ip;
#endif
	}
protected:
	unsigned int m_ip;
	unsigned short m_port;
};

template<> AFX_INLINE UINT AFXAPI HashKey<const IpPortKey&>(const IpPortKey& key)
{
#ifdef _WIN64
	size_t val = key.GetHashValue();//(key.GetDollars() << 16) | key.GetDollarFraction();
									// (algorithm copied from STL hash in xfunctional)
	return (HashKey<DWORD>((DWORD)(val & 0xffffffffUL)) ^ HashKey<DWORD>((DWORD)(val >> 32)));
#else
	return key.GetHashValue();
#endif
}

class TakionClientConnectionInfo : public IpPortKey
{
public:
	TakionClientConnectionInfo(const unsigned int& clientIp = 0,
		const unsigned short& clientPort = 0,
		const unsigned short& serverPort = 0):
		IpPortKey(clientIp, clientPort),
		m_serverPort(serverPort){}
	const unsigned short& GetServerPort() const{return m_serverPort;}
	void toString(std::string& info) const
	{
		char num[33];
		info += U_UnsignedNumberToStrNoDecDigits(m_serverPort, num, sizeof(num), ' ');
		U_ConvertIpToStdString(m_ip, info);
		info += " : ";
		info += U_UnsignedNumberToStrNoDecDigits(m_port, num, sizeof(num));
	}
	bool operator<(const TakionClientConnectionInfo& other) const{return IpPortKey::operator<(other) || IpPortKey::operator==(other) && m_serverPort < other.m_serverPort;}
	bool operator<=(const TakionClientConnectionInfo& other) const{return IpPortKey::operator<(other) || IpPortKey::operator==(other) && m_serverPort <= other.m_serverPort;}
	bool operator==(const TakionClientConnectionInfo& other) const{return IpPortKey::operator==(other) && m_serverPort == other.m_serverPort;}
	bool operator!=(const TakionClientConnectionInfo& other) const{return !operator==(other);}
	bool operator>=(const TakionClientConnectionInfo& other) const{return !operator<(other);}
	bool operator>(const TakionClientConnectionInfo& other) const{return !operator<=(other);}
protected:
	unsigned short m_serverPort;
};

class RECEIVER_API TakionClientData
{
public:
	virtual ~TakionClientData(){}
	virtual TakionClientData* Clone() const = 0;
protected:
	TakionClientData(){}
};

class RECEIVER_API TakionClient : public TakionClientConnectionInfo
{
public:
	TakionClient(const unsigned short& serverPort,
		const bool& nagle,
		const bool& logged,
		const bool& logMessages,
		const unsigned char& serverExtensionMessageFormat,
		const unsigned char& extensionMessageFormat,
		const unsigned int& estimatedHeartbeatDelayMilliseconds);
	virtual ~TakionClient(){}
//	const unsigned int& GetIp() const{return m_ip;}
//	const unsigned short& GetPort() const{return m_port;}
	const unsigned __int64& GetBytesReceived() const{return m_bytesReceived;}
	const unsigned __int64& GetBytesSent() const{return m_bytesSent;}
	const std::string& GetClientId() const{return m_clientId;}
	void SetClientId(const char* id){m_clientId = id;}
	void SetLogged(bool logged){m_logged = logged;}
	bool isLogged() const{return m_logged;}

	void SetLogMessages(bool logMessages){m_logMessages = logMessages;}
	bool isLogMessages() const{return m_logMessages;}

	const FilterStringAsNumberArray& GetSenderCompId() const{return m_senderCompId;}
	const unsigned short& GetSenderCompIdLength() const{return m_senderCompId.GetLength();}
	const char* GetSenderCompIdAsString() const{return m_senderCompId.GetString();}
	bool SetSenderCompId(const FilterStringAsNumberArray& senderCompId)
	{
		if(!senderCompId.isEmpty())
		{
			if(m_senderCompId.isEmpty())
			{
				m_senderCompId = senderCompId;
				return true;
			}
			return senderCompId != m_senderCompId;
		}
		return m_senderCompId.isEmpty();
	}
	bool SetSenderCompId(const char* senderCompId)
	{
		if(*senderCompId)
		{
			if(m_senderCompId.isEmpty())
			{
				m_senderCompId.SetString(senderCompId);
				return true;
			}
			return !strcmp(m_senderCompId.GetString(), senderCompId);
		}
		return m_senderCompId.isEmpty();
	}

	const bool& isValid() const{return m_valid;}
	
	const unsigned int& GetClientIp() const{return m_clientIp;}
	void SetClientIp(const unsigned int& clientIp){m_clientIp = clientIp;}

//	const unsigned short& GetServerPort() const{return m_serverPort;}

	void IncrementBytesReceived(const unsigned int& bytes){m_bytesReceived += bytes;}
	void IncrementBytesSent(const unsigned int& bytes){m_bytesSent += bytes;}
	virtual void Disconnect(){}
	const unsigned char& GetClientExtensionMessageFormat() const{return m_extensionMessageFormat;}
	bool SetClientExtensionMessageFormat(const unsigned char& extensionMessageFormat)
	{
		if(extensionMessageFormat != m_extensionMessageFormat)
		{
			m_extensionMessageFormat = extensionMessageFormat;
			return true;
		}
		return false;
	}
	const unsigned char& GetConnectionId() const{return m_connectionId;}
	bool SetConnectionId(const unsigned char& connectionId)
	{
		if(connectionId != m_connectionId)
		{
			m_connectionId = connectionId;
			return true;
		}
		return false;
	}
	const unsigned char& GetServerExtensionMessageFormat() const{return m_serverExtensionMessageFormat;}
	const unsigned char& GetExtensionMessageFormat() const{return m_extensionMessageFormat >= EMF_Count ? m_serverExtensionMessageFormat : m_extensionMessageFormat;}
	virtual unsigned int Write(const char* data, unsigned int length){return 0;}

	unsigned int WriteMessage(const Message* message)
	{
		return Write((const char*)message, message->m_length);
	}

	virtual unsigned int WriteBuffers(const WSABUF* cursor, unsigned int count)
	{
		unsigned int length = 0;
		unsigned int len;
		for(; count; --count, ++cursor)
		{
			len = Write(cursor->buf, cursor->len);
			if(len)
			{
				length += len;
			}
			else
			{
				return 0;
			}
		}
		return length;
	}
	virtual void AddRef(){}
	virtual void Release(){}
	void toString(std::string& info) const
	{
		TakionClientConnectionInfo::toString(info);
		info += ' ';
		switch(GetExtensionMessageFormat())
		{
			case EMF_TAKION:
			info += "Takion";
			break;

			case EMF_JSON:
			info += "JSON";
			break;

			case EMF_FIX:
			info += "FIX";
			break;

			case EMF_TEXT_END:
			info += "TEXT";
			break;

//			case EMF_BRACES:
//			info += "BRACES";
//			break;

			case EMF_TAKION_BIG_ENDIAN:
			info += "BigE";
			break;

			default:
			info += "UNKNOWN=";
			{
				char num[33];
				info += U_UnsignedNumberToStrNoDecDigits(m_extensionMessageFormat, num, sizeof(num));
			}
			break;
		}

		if(!m_clientId.empty())
		{
			info += ' ';
			info += m_clientId;
		}
	}
	virtual TakionClientData* GetClientData(){return nullptr;}
	virtual const TakionClientData* GetClientData() const{return nullptr;}

	const bool& isNagle() const{return m_nagle;}
	virtual bool SetNagle(bool nagle)
	{
		if(m_nagle != nagle)
		{
			m_nagle = nagle;
			return true;
		}
		return false;
	}
	const unsigned short& GetHeartbeatSeconds() const{return m_heartbeatSeconds;}
	bool SetHeartbeatSeconds(const unsigned short& heartbeatSeconds)
	{
		if(heartbeatSeconds != m_heartbeatSeconds)
		{
			m_heartbeatSeconds = heartbeatSeconds;
			m_heartbeatMilliseconds = heartbeatSeconds * 1000;
			return true;
		}
		return false;
	}
	const unsigned int& GetHeartbeatMilliseconds() const{return m_heartbeatMilliseconds;}

	const unsigned int& GetMsgSeqNumReceived() const{return m_msgSeqNumReceived;}
	void ResetMsgSeqNumReceived() const;//{m_msgSeqNumReceived = 0;}
	void SetMsgSeqNumReceived(const unsigned int& msgSeqNum) const;//{m_msgSeqNumReceived = msgSeqNum;}

	const unsigned int& GetMsgSeqNum() const{return m_msgSeqNum;}
	const unsigned int& GetNextMsgSeqNum() const;//{return ++m_msgSeqNum;}
	void ResetMsgSeqNum() const;//{m_msgSeqNum = 0;}
	void SetMsgSeqNum(const unsigned int& msgSeqNum) const;//{m_msgSeqNum = msgSeqNum;}

	bool SetMillisecondToSendTest(const unsigned int& millisecond)
	{
		if(millisecond != m_millisecondToSendTest)
		{
			m_millisecondToSendTest = millisecond;
			return true;
		}
		return false;
	}
	bool SetMillisecondToSendHeartbeat(const unsigned int& millisecond)
	{
		if(millisecond != m_millisecondToSendHeartbeat)
		{
			m_millisecondToSendHeartbeat = millisecond;
			return true;
		}
		return false;
	}
	const unsigned int& GetMillisecondToSendTest() const{return m_millisecondToSendTest;}
	const unsigned int& GetMillisecondToSendHeartbeat() const{return m_millisecondToSendHeartbeat;}

	const unsigned int& GetDateCreated() const{return m_dateCreated;}//((unsigned int)year << 16) | ((unsigned int)(month) << 8) | (unsigned int)day;
	const unsigned int& GetMillisecondCreated() const{return m_millisecondCreated;}

	const unsigned int& GetEstimatedHeartbeatDelayMilliseconds() const{return m_estimatedHeartbeatDelayMilliseconds;}
	bool SetEstimatedHeartbeatDelayMilliseconds(const unsigned int& millisecond)
	{
		if(millisecond != m_estimatedHeartbeatDelayMilliseconds)
		{
			m_estimatedHeartbeatDelayMilliseconds = millisecond;
			return true;
		}
		return false;
	}

	bool isTestRequestSent() const{return m_testRequestSent;}
	void SetTestRequestSent(bool sent){m_testRequestSent = sent;}

	typedef std::map<unsigned int, unsigned int> UIntUIntMap;
	const UIntUIntMap* GetSeqNumMap() const{return m_seqNumMap;}
	bool AddSeqNum(const unsigned int& nonAdminMessageOrdinal);
/*
	UIntUIntMap::const_iterator GetLowerBound(const unsigned int& seqNum) const
	{
		return seqNum ? m_seqNumMap.lower_bound(seqNum) : m_seqNumMap.end();
	}
	UIntUIntMap::const_iterator GetUpperBound(const unsigned int& seqNum) const
	{
		return seqNum ? m_seqNumMap.upper_bound(seqNum) : m_seqNumMap.end();
	}
*/
	void ClearSeqNumMap()
	{
		if(m_seqNumMap)m_seqNumMap->clear();
	}
	void CreateIdMap(const char* logFilePath);
	void DestroyIdMap();
	virtual bool isConnected() const{return false;}
	virtual bool isStub() const{return true;}

	static const char* const mapPrefix;
	static const char* const datePrefix;
	static const char* const sentSeqNumPrefix;
	static const char* const receivedSeqNumPrefix;
//	void WipeMessageMapFile();
	void NextDayStarted();
	void CopyCoreProperties(const TakionClient& other);
protected:
//	unsigned short m_serverPort;
	unsigned __int64 m_bytesReceived;
	unsigned __int64 m_bytesSent;
//	unsigned int m_ip;
//	unsigned short m_port;
	unsigned int m_clientIp;
	bool m_valid;
	bool m_nagle;
	bool m_logged;
	bool m_logMessages;
	bool m_testRequestSent;
	unsigned char m_connectionId;
	unsigned char m_extensionMessageFormat;//ExtensionMessageFormat; 0xFF if unknown
	unsigned char m_serverExtensionMessageFormat;
	unsigned short m_heartbeatSeconds;
	unsigned int m_heartbeatMilliseconds;
	unsigned int m_estimatedHeartbeatDelayMilliseconds;
	unsigned int m_millisecondToSendHeartbeat;
	unsigned int m_millisecondToSendTest;
	unsigned int m_dateCreated;//((unsigned int)year << 16) | ((unsigned int)(month) << 8) | (unsigned int)day;
	unsigned int m_millisecondCreated;
	mutable unsigned int m_msgSeqNum;
	mutable unsigned int m_msgSeqNumReceived;
	std::string m_clientId;
	FilterStringAsNumberArray m_senderCompId;

	bool ReadSavedMessageMap(const char* filePath);
	void LogSeqNumReceived() const;
	void LogSeqNumSent() const;
	UIntUIntMap* m_seqNumMap;
	void* m_savedMessageMapFile;
//	unsigned int m_lastSeqNum;
};

class TakionServer;

class RECEIVER_API TextProcessor
{
public:
	virtual ~TextProcessor();
//	virtual void ProcessTextMessage(TakionServer* server, TakionClient* client, const char* cursor, unsigned int size) = 0;
	virtual void ProcessTextMessage(TakionClient* client, const char* cursor, unsigned int size) = 0;
	virtual void ProcessTextPrompt(TakionClient* client) = 0;
	virtual TextProcessor* Clone(TakionServer* server) const = 0;
	const unsigned short& GetEndLength() const{return m_endLength;}
	const char* const& GetMessageEnd() const{return m_messageEnd;}// = "\r\n"
	const unsigned short& GetPromptLength() const{return m_promptLength;}
	const char* const& GetPrompt() const{return m_prompt;}
	bool SetMessageEnd(const char* messageEnd);
	bool SetPrompt(const char* prompt);
	TextProcessor& operator=(const TextProcessor& other);
	static bool ReplaceString(char*& oldStr, unsigned short& oldStrLength, const char* newStr);
protected:
	TextProcessor(const char* messageEnd, const char* prompt, TakionServer* server);
	TextProcessor(const TextProcessor& other, TakionServer* server);
	TextProcessor(const TextProcessor& other);
	unsigned short m_endLength;
	unsigned short m_promptLength;
	char* m_messageEnd;// = "\r\n"
	char* m_prompt;// = "\r\n"
	TakionServer* m_server;
};

class RECEIVER_API TakionServer
{
public:
	virtual ~TakionServer();
	const unsigned int& GetBindIp() const{return m_bindIp;}
	const unsigned short& GetPort() const{return m_port;}
	const unsigned char& GetExtensionMessageFormat() const{return m_extensionMessageFormat;}
	virtual bool SetExtensionMessageFormat(const unsigned char& format)
	{
		if(format != m_extensionMessageFormat)
		{
			m_extensionMessageFormat = format;
			return true;
		}
		return false;
	}
	virtual bool Start(){return false;}
	virtual void Stop(){}
	virtual bool isStarted() const{return false;}
	virtual bool isAcceptingConnections() const{return false;}
	virtual bool StartAcceptingConnections(){return false;}
	virtual bool StopAcceptingConnections(){return false;}
	virtual void AbortAllConnections(){}

	virtual void LockSocketMapInquiryWait() const{}
	virtual void UnlockSocketMapInquiry() const{}

//FindClient returns a pointer to the client. When you are done using it, call client->Release();
//	virtual const TakionClient* FindClient(unsigned int ip, unsigned short port) const{return nullptr;}
	virtual TakionClient* FindClient(unsigned int ip, unsigned short port) const{return nullptr;}
	virtual TakionClient* FindClientByStringId(const char* id) const{return nullptr;}
	virtual TakionClient* FindClientById(const FilterStringAsNumberArray& id) const{return nullptr;}
	virtual bool AddClientById(TakionClient* client, const char* logFilePath){return false;}
//call this function and iterate in LockSocketMapInquiryWait() - UnlockSocketMapInquiry(); Don't unlock until you are done using the returned objects
	virtual TakionIterator* CreateClientIterator() const{return nullptr;}
	virtual TakionIterator* CreateClientByIdIterator() const{return nullptr;}
//
	virtual const TakionClient* GetNextClient(TakionIterator* clientIterator) const{return nullptr;}
	virtual const TakionClient* GetNextClientById(TakionIterator* clientByIdIterator) const{return nullptr;}

	virtual unsigned int WriteToAllClients(const char* data, unsigned int length){return 0;}

	unsigned int WriteMessageToAllClients(const Message* message)
	{
		return WriteToAllClients((const char*)message, message->m_length);
	}

	unsigned int WriteBuffersToAllClients(const WSABUF* cursor, unsigned int count)
	{
		unsigned int clientCount = 0;
		unsigned int clients = 0;
		for(; count; --count, ++cursor)
		{
			clients = WriteToAllClients(cursor->buf, cursor->len);
			if(clients)
			{
				if(!clientCount || clients < clientCount)clientCount = clients; 
			}
			else
			{
				return 0;
			}
		}
		return clientCount;
	}
	const bool& isNagle() const{return m_nagle;}
	virtual bool SetNagle(const bool& nagle)
	{
		if(nagle != m_nagle)
		{
			m_nagle = nagle;
			return true;
		}
		return false;
	}
	const bool& isLogMessages() const{return m_logMessages;}
	virtual bool SetLogMessages(const bool& logMessages)
	{
		if(logMessages != m_logMessages)
		{
			m_logMessages = logMessages;
			return true;
		}
		return false;
	}
	const unsigned int& GetEstimatedHeartbeatDelayMilliseconds() const{return m_estimatedHeartbeatDelayMilliseconds;}
	virtual bool SetEstimatedHeartbeatDelayMilliseconds(const unsigned int& milliseconds)
	{
		if(milliseconds != m_estimatedHeartbeatDelayMilliseconds)
		{
			m_estimatedHeartbeatDelayMilliseconds = milliseconds;
			return true;
		}
		return false;
	}
	virtual void NextDayStarted(){}
	virtual void ClearAndDestroyStubs(){}
	TakionServer& operator=(const TakionServer& other);
protected:
	TakionServer(const unsigned int& ip,
		const unsigned short& port,
		const unsigned char& extensionMessageFormat,
		bool nagle,
		bool logMessages,
		const unsigned int& estimatedHeartbeatDelayMilliseconds,
		TakionClientData* clientData,
		TextProcessor* textProcessor)://nullptr
		m_bindIp(ip),
		m_port(port),
		m_extensionMessageFormat(extensionMessageFormat),
		m_nagle(nagle),
		m_logMessages(logMessages),
		m_estimatedHeartbeatDelayMilliseconds(estimatedHeartbeatDelayMilliseconds),
		m_clientData(clientData ? clientData->Clone() : nullptr),
		m_textProcessor(textProcessor ? textProcessor->Clone(this) : nullptr)
	{
	}
	TakionServer(const TakionServer& other);
	unsigned int m_bindIp;
	unsigned short m_port;
	unsigned char m_extensionMessageFormat;
	bool m_nagle;
	bool m_logMessages;
	unsigned int m_estimatedHeartbeatDelayMilliseconds;
	TakionClientData* m_clientData;
	TextProcessor* m_textProcessor;//nullptr
};

#ifdef __cplusplus
extern "C"
{
#endif

const char* WINAPI R_GetModuleVersionStr();
unsigned __int64 WINAPI R_GetModuleVersionNum();
const char* WINAPI R_GetHeaderVersion();
unsigned __int64 WINAPI R_GetHeaderVersionNum();

const char* WINAPI R_GetFilePathAndName();
const char* WINAPI R_GetPlatform();
const char* WINAPI R_GetFileDescription();
const char* WINAPI R_GetProductName();
void WINAPI R_GetDllBuildDescription(std::string& buildStr);
void WINAPI R_SetLogFile(void* logFile);
void* WINAPI R_GetLogFile();

#ifdef __cplusplus
}
#endif
