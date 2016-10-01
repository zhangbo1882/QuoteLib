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


/*Callback by C#*/
typedef void(*apiReadyCB)(void);
typedef void(*disconnectCB)(TAPIINT32);
typedef void(*rspLoginCB)(TAPIINT32, const TapAPIQuotLoginRspInfo *);
typedef void(*rspQryCommodityCB)(TAPIUINT32, TAPIINT32, TAPIYNFLAG, const TapAPIQuoteCommodityInfo *);
typedef void(*rspQryContractCB)(TAPIUINT32, TAPIINT32, TAPIYNFLAG, const TapAPIQuoteContractInfo *);
typedef void(*rspSubscribeQuoteCB)(TAPIUINT32, TAPIINT32, TAPIYNFLAG, const TapAPIQuoteWhole *);
typedef void(*rspUnSubscribeQuoteCB)(TAPIUINT32, TAPIINT32, TAPIYNFLAG, const TapAPIContract *);
typedef void(*rtnQuoteCB)(const TapAPIQuoteWhole *);

class  Quote : public ITapQuoteAPINotify
{
public:
	

	Quote(void);
	~Quote(void);

	void SetAPI(ITapQuoteAPI* pAPI);
	void RunTest();

public:
	//对ITapQuoteAPINotify的实现
	virtual void TAP_CDECL OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info);
	virtual void TAP_CDECL OnAPIReady();
	virtual void TAP_CDECL OnDisconnect(TAPIINT32 reasonCode);
	virtual void TAP_CDECL OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info);
	virtual void TAP_CDECL OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info);
	virtual void TAP_CDECL OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info);
	virtual void TAP_CDECL OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info);
	virtual void TAP_CDECL OnRtnQuote(const TapAPIQuoteWhole *info);


	void TAP_CDECL RunApiCB(apiReadyCB cb);
	void TAP_CDECL RunDisconnectCB(disconnectCB cb, TAPIINT32 errorCode);
	void TAP_CDECL RunRspLoginCB(rspLoginCB cb, TAPIINT32 errorcde, const  TapAPIQuotLoginRspInfo *info);
	void TAP_CDECL RunRspQryCommodityCB(rspQryCommodityCB cb, TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info);
	void TAP_CDECL RunRspQryContractCB(rspQryContractCB cb, TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info);
	void TAP_CDECL RunRspSubscribeQuoteCB(rspSubscribeQuoteCB cb, TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info);
	void TAP_CDECL RunRspUnSubscribeQuoteCB(rspUnSubscribeQuoteCB cb, TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info);
	void TAP_CDECL RunRtnQuoteCB(rtnQuoteCB cb, const TapAPIQuoteWhole *info);
	
	void TAP_CDECL _SetAPIReadyCB(apiReadyCB cb);
	void TAP_CDECL _SetDisconnectCB(disconnectCB cb);
	void TAP_CDECL _SetRspLoginCB(rspLoginCB cb);
	void TAP_CDECL _SetRspQryComodityCB(rspQryCommodityCB cb);
	void TAP_CDECL _SetRspQryContractCB(rspQryContractCB cb);
	void TAP_CDECL _SeSubscribeQuoteCB(rspSubscribeQuoteCB cb);
	void TAP_CDECL _SetUnSubscribeQuoteCB(rspUnSubscribeQuoteCB cb);
	void TAP_CDECL _SetrtnQuoteCB(rtnQuoteCB cb);

private:
	ITapQuoteAPI*	m_pAPI;
	TAPIUINT32		m_uiSessionID;
	SimpleEvent		m_Event;
	bool			m_bIsAPIReady;
	apiReadyCB		m_apiReadyCB;
	disconnectCB	m_disconnectCB;
	rspLoginCB		m_rspLoginCB;
	rspQryCommodityCB	m_rspQryCommodityCB;
	rspQryContractCB	m_rspQryContractCB;
	rspSubscribeQuoteCB	m_rspSubscribeQuoteCB;
	rspUnSubscribeQuoteCB	m_rspUnSubscribeQuoteCB;
	rtnQuoteCB		m_rtnQuoteCB;
};

#endif // QUOTE_H
