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
	return SetTapQuoteAPIDataPath(path);
}

TAPIINT32 TAP_CDECL SetQuoteAPILogLevel(TAPILOGLEVEL level)
{
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

TAPIINT32 TAP_CDECL QryContractQuote(ITapQuoteAPI *apiObj,
	TAPIUINT32				*sessionID,
	TAPISTR_10              ExchangeNo,
	TAPICommodityType		CommodityType,
	TAPISTR_10				CommodityNo
)
{
	struct TapAPICommodity commodity;
	strncpy(commodity.ExchangeNo, ExchangeNo, 11);
	commodity.CommodityType = CommodityType;
	strncpy(commodity.CommodityNo, CommodityNo, 11);
	return apiObj->QryContract(sessionID, &commodity);
}

TAPIINT32 TAP_CDECL Subscribe(ITapQuoteAPI *apiObj,
	TAPIUINT32 *sessionID,
	TapAPICommodity			*Commodity,
	TAPISTR_10				ContractNo1,
	TAPISTR_10				StrikePrice1,
	TAPICallOrPutFlagType	CallOrPutFlag1,
	TAPISTR_10				ContractNo2,
	TAPISTR_10				StrikePrice2,
	TAPICallOrPutFlagType	CallOrPutFlag2
)
{
	TapAPIContract contract;
	strncpy(contract.ContractNo1, ContractNo1, 11);
	strncpy(contract.StrikePrice1, StrikePrice1, 11);
	strncpy(contract.ContractNo2, ContractNo2, 11);
	strncpy(contract.StrikePrice2, StrikePrice2, 11);
	contract.CallOrPutFlag1 = CallOrPutFlag1;
	contract.CallOrPutFlag2 = CallOrPutFlag2;
	contract.Commodity = *Commodity;

	return apiObj->SubscribeQuote(sessionID, &contract);
}

TAPIINT32 TAP_CDECL UnSubscribe(ITapQuoteAPI *apiObj, 
	TAPIUINT32 *sessionID, 
	TapAPICommodity			*Commodity,
	TAPISTR_10				ContractNo1,
	TAPISTR_10				StrikePrice1,
	TAPICallOrPutFlagType	CallOrPutFlag1,
	TAPISTR_10				ContractNo2,
	TAPISTR_10				StrikePrice2,
	TAPICallOrPutFlagType	CallOrPutFlag2
)
{
	TapAPIContract contract;
	strncpy(contract.ContractNo1, ContractNo1, 11);
	strncpy(contract.StrikePrice1, StrikePrice1, 11);
	strncpy(contract.ContractNo2, ContractNo2, 11);
	strncpy(contract.StrikePrice2, StrikePrice2, 11);
	contract.CallOrPutFlag1 = CallOrPutFlag1;
	contract.CallOrPutFlag2 = CallOrPutFlag2;
	contract.Commodity = *Commodity;
	return apiObj->UnSubscribeQuote(sessionID, &contract);
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