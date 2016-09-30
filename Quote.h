#ifndef QUOTE_H
#define QUOTE_H

#include "TapQuoteAPI.h"
#include "SimpleEvent.h"

#ifdef _WIN32

#define TAP_CDECL  __cdecl
#define TAP_DLLEXPORT __declspec(dllexport)
#else
#define TAP_CDECL
#define TAP_DLLEXPORT
#endif

class  Quote : public ITapQuoteAPINotify
{
public:
	

	Quote(void);
	~Quote(void);

	void SetAPI(ITapQuoteAPI* pAPI);
	void RunTest();

public:
	typedef void(*apiReadyCB)(void);
	typedef void(*disconnectCB)(TAPIINT32);
	void TAP_CDECL RunApiCB(apiReadyCB cb);
	void TAP_CDECL RunDisconnectCB(disconnectCB cb, TAPIINT32 errorCode);

	//对ITapQuoteAPINotify的实现
	virtual void TAP_CDECL OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info);
	virtual void TAP_CDECL OnAPIReady();
	virtual void TAP_CDECL OnDisconnect(TAPIINT32 reasonCode);
	virtual void TAP_CDECL OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info);
	virtual void TAP_CDECL OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info);
	virtual void TAP_CDECL OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info);
	virtual void TAP_CDECL OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info);
	virtual void TAP_CDECL OnRtnQuote(const TapAPIQuoteWhole *info);

	void TAP_CDECL _SetAPIReadyCB(apiReadyCB cb);
	void TAP_CDECL _SetDisconnectCB(disconnectCB cb, TAPIINT32 reasonCode);
private:
	ITapQuoteAPI* m_pAPI;
	TAPIUINT32	m_uiSessionID;
	SimpleEvent m_Event;
	bool		m_bIsAPIReady;
	apiReadyCB	m_apiReadyCB;
	disconnectCB m_disconnectCB;
};

#endif // QUOTE_H
