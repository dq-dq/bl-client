/******************************************************************************
*created:		2012/4/13
*created:		12:06
*author:		wangning
*purpose:		消息响应
********************************************************************************/
#pragma once
#include "AllMessageHead.h"

typedef void (*MESSAGE_REPONSE_CallFunc)( int ID, ::google::protobuf::Message* responseMessage );
#define message_reponse(_SELECTOR) (MESSAGE_REPONSE_CallFunc)(&_SELECTOR)

class NetMessageReponse
{
public:
	NetMessageReponse();
	~NetMessageReponse();

	vector<MESSAGE_REPONSE_CallFunc> *m_pMessageRepnseCallFuncList;

	static void PushRepnseCallFunc( MESSAGE_REPONSE_CallFunc callFunc );
	static void MessageResponse( int ID, ::google::protobuf::Message* responseMessage );
};

#define PUSH_REPNSECALLFUNC(func) NetMessageReponse::PushRepnseCallFunc( func )

