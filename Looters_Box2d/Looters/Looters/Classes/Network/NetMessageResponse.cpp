#include "NetMessageResponse.h"
#include "NetMessageManager.h"

NetMessageReponse::NetMessageReponse()
{
	m_pMessageRepnseCallFuncList = new vector<MESSAGE_REPONSE_CallFunc>;
	m_pMessageRepnseCallFuncList->clear();
}

NetMessageReponse::~NetMessageReponse()
{
	m_pMessageRepnseCallFuncList->clear();
	delete m_pMessageRepnseCallFuncList;
	m_pMessageRepnseCallFuncList = NULL;
}

void NetMessageReponse::PushRepnseCallFunc( MESSAGE_REPONSE_CallFunc callFunc )
{
	for( int i = 0; i < (int)NetMessageManager::GetMessageManager()->m_pMessageResponse->m_pMessageRepnseCallFuncList->size(); i++ )
	{
		if( callFunc == NetMessageManager::GetMessageManager()->m_pMessageResponse->m_pMessageRepnseCallFuncList->at(i) )
			return;
	}

	if( callFunc )
		NetMessageManager::GetMessageManager()->m_pMessageResponse->m_pMessageRepnseCallFuncList->push_back( callFunc );
}

void NetMessageReponse::MessageResponse( int ID, ::google::protobuf::Message* responseMessage )
{
	for( int i = 0; i < (int)NetMessageManager::GetMessageManager()->m_pMessageResponse->m_pMessageRepnseCallFuncList->size(); i++ )
	{
		MESSAGE_REPONSE_CallFunc callFunc = NetMessageManager::GetMessageManager()->m_pMessageResponse->m_pMessageRepnseCallFuncList->at(i);
		callFunc( ID, responseMessage );
	}
}