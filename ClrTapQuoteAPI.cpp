#include "Quote.h"
#include "TapAPIError.h"
#include "QuoteConfig.h"
#include "ClrTapQuoteAPI.h"
#include <iostream>

using namespace std;
#if 0
/*ClrITapQuoteAPI Implementation*/
 ClrITapQuoteAPI::ClrITapQuoteAPI(void)
{
	
}

ClrITapQuoteAPI::~ClrITapQuoteAPI()
{
	FreeTapQuoteAPI(QuoteNative);
}

const TAPICHAR * TAP_CDECL ClrITapQuoteAPI::GetTapQuoteAPIVersion()
{
	return GetTapQuoteAPIVersion();
}

TAPIINT32 TAP_CDECL ClrITapQuoteAPI::SetTapQuoteAPIDataPath(const TAPICHAR *path)
{
	return SetTapQuoteAPIDataPath(path);
}

TAPIINT32 TAP_CDECL ClrITapQuoteAPI::SetTapQuoteAPILogLevel(TAPILOGLEVEL level)
{
	return SetTapQuoteAPILogLevel(level);
}

TAPIINT32 TAP_CDECL ClrITapQuoteAPI::SetAPINotify(ITapQuoteAPINotify *apiNotify)
{
	return QuoteNative->SetAPINotify(apiNotify);
}

TAPIINT32 TAP_CDECL ClrITapQuoteAPI::SetHostAddress(const TAPICHAR *IP, TAPIUINT16 port)
{
	return QuoteNative->SetHostAddress(IP, port);
}

TAPIINT32 TAP_CDECL ClrITapQuoteAPI::Login(const TapAPIQuoteLoginAuth *loginAuth)
{
	return QuoteNative->Login(loginAuth);
}

TAPIINT32 TAP_CDECL ClrITapQuoteAPI::Disconnect()
{
	return QuoteNative->Disconnect();
}

TAPIINT32 TAP_CDECL ClrITapQuoteAPI::QryCommodity(TAPIUINT32 *sessionID)
{
	return QuoteNative->QryCommodity(sessionID);
}

TAPIINT32 TAP_CDECL ClrITapQuoteAPI::QryContract(TAPIUINT32 *sessionID, const TapAPICommodity *qryReq)
{
	return QuoteNative->QryContract(sessionID, qryReq);
}

TAPIINT32 TAP_CDECL ClrITapQuoteAPI::SubscribeQuote(TAPIUINT32 *sessionID, const TapAPIContract *contract)
{
	return QuoteNative->SubscribeQuote(sessionID, contract);
}

TAPIINT32 TAP_CDECL ClrITapQuoteAPI::UnSubscribeQuote(TAPIUINT32 *sessionID, const TapAPIContract *contract)
{
	return QuoteNative->UnSubscribeQuote(sessionID, contract);
}

void TAP_CDECL ClrITapQuoteAPI::CreateAPI(char *authCode, char *keyOperation)
{
	TAPIINT32 iResult = TAPIERROR_SUCCEED;
	TapAPIApplicationInfo stAppInfo;
	strcpy(stAppInfo.AuthCode, authCode);
	strcpy(stAppInfo.KeyOperationLogPath, keyOperation);
	QuoteNative = CreateTapQuoteAPI(&stAppInfo, iResult);
}

void TAP_CDECL ClrITapQuoteAPI::printChar(char *s)
{
	cout << "The string is " << s << endl;
}

/*ClrITapQuoteAPINotify Implementation*/
ClrITapQuoteAPINotify::ClrITapQuoteAPINotify(void)
{
	QuoteNotifyNative = new Quote();
}

ClrITapQuoteAPINotify::~ClrITapQuoteAPINotify(void)
{
}
void TAP_CDECL ClrITapQuoteAPINotify::OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info)
{
	QuoteNotifyNative->OnRspLogin(errorCode, info);
}

void TAP_CDECL ClrITapQuoteAPINotify::OnAPIReady()
{
	QuoteNotifyNative->OnAPIReady();
}

void TAP_CDECL ClrITapQuoteAPINotify::OnDisconnect(TAPIINT32 reasonCode)
{
	QuoteNotifyNative->OnDisconnect(reasonCode);
}

void TAP_CDECL ClrITapQuoteAPINotify::OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info)
{
	QuoteNotifyNative->OnRspQryCommodity(sessionID, errorCode, isLast, info);
}

void TAP_CDECL ClrITapQuoteAPINotify::OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info)
{
	QuoteNotifyNative->OnRspQryContract(sessionID, errorCode, isLast, info);
}

void TAP_CDECL ClrITapQuoteAPINotify::OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info)
{
	QuoteNotifyNative->OnRspSubscribeQuote(sessionID, errorCode, isLast, info);
}

void TAP_CDECL ClrITapQuoteAPINotify::OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info)
{
	QuoteNotifyNative->OnRspUnSubscribeQuote(sessionID, errorCode, isLast, info);
}

void TAP_CDECL ClrITapQuoteAPINotify::OnRtnQuote(const TapAPIQuoteWhole *info)
{
	QuoteNotifyNative->OnRtnQuote(info);
}
#endif

ITapQuoteAPI *TAP_CDECL CreateQuoteAPI(char *authCode, char *keyOperation)
{
	TAPIINT32 iResult = TAPIERROR_SUCCEED;
	TapAPIApplicationInfo stAppInfo;
	strcpy(stAppInfo.AuthCode, authCode);
	strcpy(stAppInfo.KeyOperationLogPath, keyOperation);
	return CreateTapQuoteAPI(&stAppInfo, iResult);
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
#if 0
TAPIINT32 TAP_CDECL LoginQuote(
	ITapQuoteAPI		*apiObj,
	TAPISTR_20			UserNo,//< �û���
	TAPIYNFLAG			ISModifyPassword,		///< �Ƿ��޸����룬'Y'��ʾ�ǣ�'N'��ʾ��
	TAPISTR_20			Password,				///< �û�����
	TAPISTR_20			NewPassword,			///< �����룬����������޸���������Ҫ��д���ֶ�
	TAPISTR_20			QuoteTempPassword,	///< ������ʱ����
	TAPIYNFLAG			ISDDA,					///< �Ƿ���ѽ��̬��֤��'Y'��ʾ�ǣ�'N'��ʾ��
	TAPISTR_30			DDASerialNo
)
{
	TapAPIQuoteLoginAuth loginAuth;
	strncpy(loginAuth.UserNo, UserNo, 21);
	loginAuth.ISModifyPassword = ISModifyPassword;
	strncpy(loginAuth.Password, Password, 21);
	strncpy(loginAuth.NewPassword, NewPassword, 21);
	strncpy(loginAuth.QuoteTempPassword, QuoteTempPassword, 21);
	loginAuth.ISDDA = ISDDA;
	strncpy(loginAuth.DDASerialNo, DDASerialNo, 31);
	cout << "User:" << loginAuth.UserNo << endl;
	cout << "password:" << loginAuth.Password << endl;
	return apiObj->Login(&loginAuth);
}
#endif
TAPIINT32 TAP_CDECL LoginQuote(ITapQuoteAPI		*apiObj, const TapAPIQuoteLoginAuth *loginAuth)
{
	cout << "User:" << loginAuth->UserNo << endl;
	cout << "password:" << loginAuth->Password << endl;
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

void TAP_CDECL OnRspLoginNotify(ITapQuoteAPINotify *notifyObj, TAPIINT32 errorCode,
	TAPISTR_20					UserNo,							///< �û���
	TAPIINT32					&UserType,						///< �û�����
	TAPISTR_20					UserName,						///< �ǳƣ�GBK�����ʽ
	//TAPISTR_20					QuoteTempPassword,			///< ������ʱ����
	//TAPISTR_50					ReservedInfo,					///< �û��Լ����õ�Ԥ����Ϣ
	TAPISTR_40					LastLoginIP,					///< �ϴε�¼�ĵ�ַ
	TAPIUINT32					&LastLoginPort					///< �ϴε�¼ʹ�õĶ˿�
	//TAPIDATETIME				LastLoginTime,					///< �ϴε�¼��ʱ��
	//TAPIDATETIME				LastLogoutTime,					///< �ϴ��˳���ʱ��
	//TAPIDATE					TradeDate,						///< ��ǰ��������
	//TAPIDATETIME				LastSettleTime,					///< �ϴν���ʱ��
	//TAPIDATETIME				StartTime,						///< ϵͳ����ʱ��
	//TAPIDATETIME				InitTime						///< ϵͳ��ʼ��ʱ��)
)
{
	TapAPIQuotLoginRspInfo info;
	notifyObj->OnRspLogin(errorCode, &info);
	cout << "UserNo:" << info.UserNo << endl;
	cout << "UserType:" << info.UserType << endl;
	cout << "UserName:" << info.UserName << endl;
	cout << "LastLoginIP:" << info.LastLoginIP << endl;
	cout << "LastLoginPort:" << info.LastLoginProt << endl;
}
void TAP_CDECL SetAPIReadyCB(Quote *quoteNotify, apiReadyCB cb)
{
	quoteNotify->_SetAPIReadyCB(cb);
}

void TAP_CDECL SetDisconnectCB(Quote *quoteNotify, disconnectCB cb, TAPIINT32 reasonCode)
{
	quoteNotify->_SetDisconnectCB(cb, reasonCode);
}