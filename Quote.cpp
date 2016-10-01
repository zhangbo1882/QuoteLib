#include "Quote.h"
#include "TapAPIError.h"
#include "QuoteConfig.h"
//#include <Windows.h>
#include <iostream>
#include <string.h>

using namespace std;

Quote::Quote(void):
	m_pAPI(NULL),
	m_bIsAPIReady(false)
{
}


Quote::~Quote(void)
{
}


void Quote::SetAPI(ITapQuoteAPI *pAPI)
{
	m_pAPI = pAPI;
}


void Quote::RunTest()
{
	if(NULL == m_pAPI) {
		cout << "Error: m_pAPI is NULL." << endl;
		return;
	}

	TAPIINT32 iErr = TAPIERROR_SUCCEED;


	//�趨������IP���˿�
	iErr = m_pAPI->SetHostAddress(DEFAULT_IP, DEFAULT_PORT);
	if(TAPIERROR_SUCCEED != iErr) {
		cout << "SetHostAddress Error:" << iErr <<endl;
		return;
	}

	//��¼������
	TapAPIQuoteLoginAuth stLoginAuth;
	cout << "Try to login server\n";
	memset(&stLoginAuth, 0, sizeof(stLoginAuth));
	strcpy(stLoginAuth.UserNo, DEFAULT_USERNAME);
	strcpy(stLoginAuth.Password, DEFAULT_PASSWORD);
	stLoginAuth.ISModifyPassword = APIYNFLAG_NO;
	stLoginAuth.ISDDA = APIYNFLAG_NO;
	iErr = m_pAPI->Login(&stLoginAuth);
	if(TAPIERROR_SUCCEED != iErr) {
		cout << "Login Error:" << iErr <<endl;
		return;
	}
	

	//�ȴ�APIReady
	m_Event.WaitEvent();
	if (!m_bIsAPIReady){
		return;
	}
	cout << "Login Sucess\n";
	m_uiSessionID = 0;
	TapAPICommodity com;
	memset(&com, 0, sizeof(com));
	strcpy(com.ExchangeNo,DEFAULT_EXCHANGE_NO);
	strcpy(com.CommodityNo,DEFAULT_COMMODITY_NO);
	com.CommodityType =DEFAULT_COMMODITY_TYPE;
	m_pAPI->QryContract(&m_uiSessionID,&com);


	//��������
	TapAPIContract stContract;
	memset(&stContract, 0, sizeof(stContract));
	strcpy(stContract.Commodity.ExchangeNo, DEFAULT_EXCHANGE_NO);
	stContract.Commodity.CommodityType = DEFAULT_COMMODITY_TYPE;
	strcpy(stContract.Commodity.CommodityNo, DEFAULT_COMMODITY_NO);
	strcpy(stContract.ContractNo1, "1612");
	stContract.CallOrPutFlag1 = TAPI_CALLPUT_FLAG_NONE;
	stContract.CallOrPutFlag2 = TAPI_CALLPUT_FLAG_NONE;
	m_uiSessionID = 0;
	iErr = m_pAPI->SubscribeQuote(&m_uiSessionID, &stContract);
	if(TAPIERROR_SUCCEED != iErr) {
		cout << "SubscribeQuote Error:" << iErr <<endl;
		return;
	}

        while(true) {
			cout << "waitEvent";
                m_Event.WaitEvent();
        }
}
/*rspLoginCB*/
void TAP_CDECL Quote::RunRspLoginCB(rspLoginCB cb, TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info)
{
	if (cb != NULL)
	{
		cb(errorCode, info);
	}
}
void TAP_CDECL Quote::_SetRspLoginCB(rspLoginCB cb)
{
	m_rspLoginCB = cb;
}

void TAP_CDECL Quote::OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info)
{
	Quote::RunRspLoginCB(m_rspLoginCB, errorCode, info);

	if(TAPIERROR_SUCCEED == errorCode) {
		cout << "[c++ context] ��¼�ɹ����ȴ�API��ʼ��..." << endl;
		m_bIsAPIReady = true;
		cout << "[c++ context] �û���:" << info->UserNo << endl;
		cout << "[c++ context] �ǳ�:" << info->UserName << endl;
		cout << "[c++ context] �ϴε�¼IP:" << info->LastLoginIP << endl;
		cout << "[c++ context] ϵͳ����ʱ��:" << info->StartTime << endl;

	} else {
		cout << "[c++ context] ��¼ʧ�ܣ�������:" << errorCode << endl;
		m_Event.SignalEvent();	
	}
}

/*apiReadyCB*/
void TAP_CDECL Quote::RunApiCB(apiReadyCB cb)
{
	if (cb != NULL)
	{
		cb();
	}
}

void TAP_CDECL Quote::_SetAPIReadyCB(apiReadyCB cb)
{
	m_apiReadyCB = cb;
}

void TAP_CDECL Quote::OnAPIReady()
{
	cout << "[c++ context] API��ʼ�����" << endl;
	Quote::RunApiCB(m_apiReadyCB);
	m_Event.SignalEvent();	
}

/*DisconnectCB*/
void TAP_CDECL Quote::RunDisconnectCB(disconnectCB cb, TAPIINT32 errorCode)
{
	if (cb != NULL)
	{
		cb(errorCode);
	}
}
void TAP_CDECL Quote::_SetDisconnectCB(disconnectCB cb)
{
	m_disconnectCB = cb;
}

void TAP_CDECL Quote::OnDisconnect(TAPIINT32 reasonCode)
{
	cout << "[c++ context] API�Ͽ�,�Ͽ�ԭ��:"<<reasonCode << endl;
	Quote::RunDisconnectCB(m_disconnectCB, reasonCode);
}

/*rspQryComodityCB*/
void TAP_CDECL Quote::RunRspQryCommodityCB(rspQryCommodityCB cb, TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info)
{	if (cb != NULL)
	{
		cb(sessionID, errorCode, isLast, info);
	}
}

void TAP_CDECL Quote::_SetRspQryComodityCB(rspQryCommodityCB cb)
{
	m_rspQryCommodityCB = cb;
}

void TAP_CDECL Quote::OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info)
{
	cout << __FUNCTION__ << " is called." << endl;
	cout << "[c++ context] isLast: " << isLast << endl;
	Quote::RunRspQryCommodityCB(m_rspQryCommodityCB, sessionID, errorCode, isLast, info);
}

/*rspQryContractCB*/
void TAP_CDECL Quote::RunRspQryContractCB(rspQryContractCB cb, TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info)
{
	if (cb != NULL)
	{
		cb(sessionID, errorCode, isLast, info);
	}
}

void TAP_CDECL Quote::_SetRspQryContractCB(rspQryContractCB cb)
{
	m_rspQryContractCB = cb;
}

void TAP_CDECL Quote::OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info)
{
	cout << __FUNCTION__ << " is called." << endl;
	cout << "��Լ:" << info->Contract.Commodity.CommodityNo << info->Contract.ContractNo1 << endl;
	Quote::RunRspQryContractCB(m_rspQryContractCB, sessionID, errorCode, isLast, info);
}


void TAP_CDECL Quote::OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info)
{
	if (TAPIERROR_SUCCEED == errorCode)
	{
		cout << "���鶩�ĳɹ� ";
		if (NULL != info)
		{
			cout << info->DateTimeStamp << " "
				<< info->Contract.Commodity.ExchangeNo << " "
				<< info->Contract.Commodity.CommodityType << " "
				<< info->Contract.Commodity.CommodityNo << " "
				<< info->Contract.ContractNo1 << " "
				<< info->QLastPrice
				// ...		
				<<endl;
		}

	} else{
		cout << "���鶩��ʧ�ܣ������룺" << errorCode <<endl;
	}
}

void TAP_CDECL Quote::OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Quote::OnRtnQuote(const TapAPIQuoteWhole *info)
{
	if (NULL != info)
	{
		cout << "�������:" 
			<< info->DateTimeStamp << " "
			<< info->Contract.Commodity.ExchangeNo << " "
			<< info->Contract.Commodity.CommodityType << " "
			<< info->Contract.Commodity.CommodityNo << " "
			<< info->Contract.ContractNo1 << " "
			<< info->QLastPrice
			// ...		
			<<endl;
	}
}
