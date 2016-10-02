#include "Quote.h"
#include "TapAPIError.h"
#include "QuoteConfig.h"
#include "ClrTapQuoteAPI.h"
#include <iostream>

using namespace std;


ITapQuoteAPI *TAP_CDECL CreateQuoteAPI(const TapAPIApplicationInfo *appInfo, TAPIINT32 &iResult)
{

	return CreateTapQuoteAPI(appInfo, iResult);
}

void TAP_CDECL FreeQuoteAPI(ITapQuoteAPI *apiObj)
{
	FreeTapQuoteAPI(apiObj);
}

const TAPICHAR *TAP_CDECL GetQuoteAPIVersion()
{
	return GetTapQuoteAPIVersion();
}

TAPIINT32 TAP_CDECL SetQuoteAPIDataPath(const TAPICHAR *path)
{
	cout << "[c++ context] dataPath: " << path << endl;
	return SetTapQuoteAPIDataPath(path);
}

TAPIINT32 TAP_CDECL SetQuoteAPILogLevel(TAPILOGLEVEL level)
{
	cout << "[c++ context] loglevel: " << level << endl;
	return SetTapQuoteAPILogLevel(level);
}

Quote *TAP_CDECL CreateNotifyAPI(void)
{
	return new Quote();
}

void TAP_CDECL SetAPINotify(ITapQuoteAPI *apiObj, Quote *quote)
{
	apiObj->SetAPINotify(quote);
}

TAPIINT32 TAP_CDECL SetQuoteHostAddress(ITapQuoteAPI *apiObj, const TAPICHAR *IP, TAPIUINT16 port)
{
	return apiObj->SetHostAddress(IP, port);
}

TAPIINT32 TAP_CDECL LoginQuote(ITapQuoteAPI		*apiObj, const TapAPIQuoteLoginAuth *loginAuth)
{
	//cout << "User:" << loginAuth->UserNo << endl;
	//cout << "password:" << loginAuth->Password << endl;
	return apiObj->Login(loginAuth);
}
TAPIINT32 TAP_CDECL DisconnectQuote(ITapQuoteAPI *apiObj)
{
	return apiObj->Disconnect();
}

TAPIINT32 TAP_CDECL QryCommodityQuote(ITapQuoteAPI *apiObj, TAPIUINT32 *sessionID)
{
	return apiObj->QryCommodity(sessionID);
}

TAPIINT32 TAP_CDECL QryContractQuote(ITapQuoteAPI *apiObj, TAPIUINT32 *sessionID, TapAPICommodity *qrqReq)
{
	return apiObj->QryContract(sessionID, qrqReq);
}

TAPIINT32 TAP_CDECL Subscribe(ITapQuoteAPI *apiObj,	TAPIUINT32 *sessionID, const TapAPIContract *contract)
{
	return apiObj->SubscribeQuote(sessionID, contract);
}

TAPIINT32 TAP_CDECL UnSubscribe(ITapQuoteAPI *apiObj, TAPIUINT32 *sessionID, const TapAPIContract *contract)
{

	return apiObj->UnSubscribeQuote(sessionID, contract);
}


void TAP_CDECL SetAPIReadyCB(Quote *quoteNotify, apiReadyCB cb)
{
	quoteNotify->_SetAPIReadyCB(cb);
}

void TAP_CDECL SetDisconnectCB(Quote *quoteNotify, disconnectCB cb)
{
	quoteNotify->_SetDisconnectCB(cb);
}

void TAP_CDECL SetRspLoginCB(Quote *quoteNotify, rspLoginCB cb)
{
	quoteNotify->_SetRspLoginCB(cb);
}

void TAP_CDECL SetRspQryCommodityCB(Quote *quoteNotify, rspQryCommodityCB cb)
{
	quoteNotify->_SetRspQryComodityCB(cb);
}

void TAP_CDECL SetRspQryContractCB(Quote *quoteNotify, rspQryContractCB cb)
{
	quoteNotify->_SetRspQryContractCB(cb);
}

void TAP_CDECL SetRspSubscribeQuoteCB(Quote *quoteNotify, rspSubscribeQuoteCB cb)
{
	quoteNotify->_SetRspSubscribeQuoteCB(cb);
}

void TAP_CDECL SetRspUnSubscribeQuoteCB(Quote *quoteNotify, rspUnSubscribeQuoteCB cb)
{
	quoteNotify->_SetRspUnSubscribeQuoteCB(cb);
}

void TAP_CDECL SetRtnQuoteCB(Quote *quoteNotify, rtnQuoteCB cb)
{
	quoteNotify->_SetRtnQuoteCB(cb);
}