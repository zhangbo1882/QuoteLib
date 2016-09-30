#ifndef CLR_TAP_QUOTE_API_H
#define CLR_TAP_QUOTE_API_H

#include "TapQuoteAPIDataType.h"
#include "TapQuoteAPI.h"

#ifdef _WIN32

#define TAP_CDECL  __cdecl
#define TAP_DLLEXPORT __declspec(dllexport)
#else
#define TAP_CDECL
#define TAP_DLLEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	TAP_DLLEXPORT ITapQuoteAPI *TAP_CDECL CreateQuoteAPI(char *authCode, char *keyOperation);

	TAP_DLLEXPORT void TAP_CDECL FreeQuoteAPI(ITapQuoteAPI *apiObj);

	TAP_DLLEXPORT const TAPICHAR *TAP_CDECL GetQuoteAPIVersion();

	TAP_DLLEXPORT TAPIINT32 TAP_CDECL SetQuoteAPIDataPath(const TAPICHAR *path);

	TAP_DLLEXPORT TAPIINT32 TAP_CDECL SetQuoteAPILogLevel(TAPILOGLEVEL level);


	TAP_DLLEXPORT  Quote *TAP_CDECL CreateNotifyAPI(void);

	TAP_DLLEXPORT void TAP_CDECL SetAPINotify(ITapQuoteAPI *apiObj, Quote *quote);


	TAP_DLLEXPORT TAPIINT32 TAP_CDECL SetQuoteHostAddress(ITapQuoteAPI *apiObj, const TAPICHAR *IP, TAPIUINT16 port);

	TAP_DLLEXPORT TAPIINT32 TAP_CDECL LoginQuote(ITapQuoteAPI *apiObj, const TapAPIQuoteLoginAuth *loginAuth);

	TAP_DLLEXPORT TAPIINT32 TAP_CDECL DisconnectQuote(ITapQuoteAPI *apiObj);

	TAP_DLLEXPORT TAPIINT32 TAP_CDECL QryCommodityQuote(ITapQuoteAPI *apiObj, TAPIUINT32 *sessionID);

	TAP_DLLEXPORT TAPIINT32 TAP_CDECL QryContractQuote(ITapQuoteAPI *apiObj,
		TAPIUINT32				*sessionID,
		TAPISTR_10              ExchangeNo,                             
		TAPICommodityType		CommodityType,                          
		TAPISTR_10				CommodityNo
	);

	TAP_DLLEXPORT TAPIINT32 TAP_CDECL Subscribe(ITapQuoteAPI *apiObj,
		TAPIUINT32 *sessionID,
		TapAPICommodity			*Commodity,								
		TAPISTR_10				ContractNo1,                            
		TAPISTR_10				StrikePrice1,                           
		TAPICallOrPutFlagType	CallOrPutFlag1,                        
		TAPISTR_10				ContractNo2,                           
		TAPISTR_10				StrikePrice2,                           
		TAPICallOrPutFlagType	CallOrPutFlag2                         
		);

	TAP_DLLEXPORT TAPIINT32 TAP_CDECL UnSubscribe(ITapQuoteAPI *apiObj, 
		TAPIUINT32 *sessionID,
		TapAPICommodity			*Commodity,
		TAPISTR_10				ContractNo1,
		TAPISTR_10				StrikePrice1,
		TAPICallOrPutFlagType	CallOrPutFlag1,
		TAPISTR_10				ContractNo2,
		TAPISTR_10				StrikePrice2,
		TAPICallOrPutFlagType	CallOrPutFlag2
		);

	TAP_DLLEXPORT void TAP_CDECL OnRspLoginNotify(ITapQuoteAPINotify *notifyObj, TAPIINT32 errorCode,
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
	);
	typedef void(*apiReadyCB)(void);
	typedef void(*disconnectCB)(TAPIINT32);

	TAP_DLLEXPORT void TAP_CDECL SetAPIReadyCB (Quote *quoteNotify, apiReadyCB cb);

	TAP_DLLEXPORT void TAP_CDECL SetDisconnectCB(Quote *quoteNotify, disconnectCB cb, TAPIINT32 reasonCode);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // CLR_TAP_QUOTE_API_H