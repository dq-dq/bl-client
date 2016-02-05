#include "NetGoogleFilter.h"
#include "NetMessageManager.h"

NetGoogleFilter::NetGoogleFilter()
{

}

NetGoogleFilter::~NetGoogleFilter()
{

}

bool NetGoogleFilter::Get_MSG_BODY_WithPresonSerializeString( Recv_struct SerializeString )
{
	//获取消息测试
	MSG_PERSON *test_MSG_PERSON = MSG_PERSON::default_instance().New();	
	test_MSG_PERSON->ParsePartialFromArray(SerializeString.data,SerializeString.ieffectiveLength);
	string headStr = test_MSG_PERSON->msghead();
	string bodyStr = test_MSG_PERSON->msgbody();

	MSG_HEAD *temp_MSG_Head = MSG_HEAD::default_instance().New();
	temp_MSG_Head->ParseFromString(headStr);

	//验证校验码
	long long checksum = temp_MSG_Head->checksum();
	long long checkCode = (long long)NetGoogleFilter::Adler32((unsigned char*)bodyStr.c_str(),bodyStr.length());
	if (checksum != checkCode)
	{
		delete temp_MSG_Head;
		temp_MSG_Head = NULL;
		delete test_MSG_PERSON;
		test_MSG_PERSON = NULL;
		return false;
	}

	int commandid = temp_MSG_Head->commandid();	
	Message* message = NULL;
	std::map<int,string>::iterator iter;
	iter = NetMessageManager::GetMessageManager()->m_mapReflexMessage.find(temp_MSG_Head->commandid());

	if (iter != NetMessageManager::GetMessageManager()->m_mapReflexMessage.end())
	{
#if GOOGLE_RUNTIME_LITE
		message = CreateMessage(commandid);
#else
		message = CreateMessage(iter->second);
#endif	
		if( message )
		{
			message->ParseFromString(bodyStr);
			NetMessageReponse::MessageResponse( commandid, message );
			
			delete message;
			delete test_MSG_PERSON;
			delete temp_MSG_Head;

			message = NULL;
			temp_MSG_Head = NULL;
			test_MSG_PERSON = NULL;
			return true;
		}
		else
		{
			delete temp_MSG_Head;
			temp_MSG_Head = NULL;
			delete test_MSG_PERSON;
			test_MSG_PERSON = NULL;
			return false;
		}
	}

	return false;
}

bool NetGoogleFilter::Creater__MSG_PERSON__With__MSG_BODY_( int Socket, Message* bodyMessage )
{
	if( bodyMessage == NULL )
		return false;

	string typeName = bodyMessage->GetTypeName();
	string bodyString = "";
	bodyMessage->SerializeToString(&bodyString);
	std::map<string,int>::iterator MessageIter = NetMessageManager::GetMessageManager()->m_mapMessageList.find( typeName );

	if (MessageIter != NetMessageManager::GetMessageManager()->m_mapMessageList.end())
	{
		MSG_PERSON* tempPerson = MSG_PERSON::default_instance().New();
		MSG_HEAD* tempHead = MSG_HEAD::default_instance().New();
		tempHead->set_ishttp(false);

		int commandID = MessageIter->second;
		tempHead->set_commandid(commandID);
//		int len = bodyMessage->ByteSize();
		string _body_string = bodyString;
		unsigned long long checkCode = NetGoogleFilter::Adler32((unsigned char*)bodyString.c_str(),bodyString.length());
		tempHead->set_checksum((long long)checkCode);
		tempHead->set_sequence(0);

		string headSerializeStr = "";
		tempHead->SerializeToString(&headSerializeStr);
		tempPerson->set_msghead(headSerializeStr);
		tempPerson->set_msgbody(_body_string);

		string msg_Person;
		tempPerson->SerializeToString(&msg_Person);

		if( Socket == Socket_Game )
			NetMessageManager::GetMessageManager()->m_pSocketGame->AddSendQueue( msg_Person );
		if( Socket == Socket_File )
			NetMessageManager::GetMessageManager()->m_pSocketFile->AddSendQueue( msg_Person );
        if (Socket == Socket_Bank)
            NetMessageManager::GetMessageManager()->m_pSocketBank->AddSendQueue( msg_Person );

		delete tempHead;
		delete tempPerson;
		delete bodyMessage;
		tempHead = NULL;
		tempPerson = NULL;
		bodyMessage = NULL;
		
		return true;
	}

	return false;
}

unsigned long long NetGoogleFilter::Adler32( unsigned char* buf, int len )
{
	unsigned long long adler = 1;
	unsigned long long s1 = adler & 0xffff;
	unsigned long long s2 = (adler >> 16) & 0xffff;
	for (int i = 0; i < len; i++) 
	{
		s1 = (s1 + buf[i]) % BASE;
		s2 = (s2 + s1) % BASE;
	}
	return (s2 << 16) + s1;
}

#if GOOGLE_RUNTIME_LITE
Message* NetGoogleFilter::CreateMessage(int ID)
{
	switch(ID)
	{
	case API_UserLoginResponse:	//登陆
		{
			message::UserLoginResponse* tempMessage = message::UserLoginResponse::default_instance().New();
			return (Message*)tempMessage;
		}
		break;
    case API_DownloadMapInforResponse:
        {
            message::DownloadMapInforResponse* tempMessage = message::DownloadMapInforResponse::default_instance().New();
            return (Message*)tempMessage;
        }
        break;
    case API_DownloadBattleInforResponse:
        {
            message::DownloadBattleInforResponse* tempMessage = message::DownloadBattleInforResponse::default_instance().New();
            return (Message*)tempMessage;
        }
            break;
    case API_OperateSequenceResponse:
        {
            message::OperateSequenceResponse* tempMessage = message::OperateSequenceResponse::default_instance().New();
            return (Message*)tempMessage;
        }
            break;
    case API_ProduceSoldiersResponse:
        {
            message::ProduceSoldiersResponse* tempMessage = message::ProduceSoldiersResponse::default_instance().New();
            return (Message*)tempMessage;
        }
            break;
    case API_BattleMatchingResponse:// 战斗匹配
        {
            message::BattleMatchingResponse* tempMessage = message::BattleMatchingResponse::default_instance().New();
            return (Message*)tempMessage;
        }
            break;   
    case API_UploadBattleResultResponse:
        {
            message::UploadBattleResultResponse* tempMessage = message::UploadBattleResultResponse::default_instance().New();
            return (Message*)tempMessage;
        }
            break;
    case API_BattleStartResponse:
        {
            message::BattleStartResponse* tempMessage = message::BattleStartResponse::default_instance().New();
            return (Message*)tempMessage;
        }
            break;
    case API_RechargeResponse:
        {
            message::RechargeResponse* tempMessage = message::RechargeResponse::default_instance().New();
            return (Message*)tempMessage;
        }
            break;
    case API_RevengeBattleResponse:
        {
            message::RevengeBattleResponse* tempMessage = message::RevengeBattleResponse::default_instance().New();
            return (Message*)tempMessage;
        }
            break;
    case API_UploadBattleFlowResponse:
        {
            message::UploadBattleFlowResponse* tempMessage = message::UploadBattleFlowResponse::default_instance().New();
            return (Message*)tempMessage;
        }
            break;
    case API_IoFileResponse:
        {
            message::IoFileResponse* tempMessage = message::IoFileResponse::default_instance().New();
            return (Message*)tempMessage;
        }
            break;
    case API_CancleBattleResponse:
        {
            message::CancleBattleResponse* tempMessage = message::CancleBattleResponse::default_instance().New();
            return (Message*)tempMessage;
        }
            break;
	default:
		return NULL;
	}
}
#else
Message* NetGoogleFilter::CreateMessage(const std::string& typeName)
{
	::google::protobuf::Message* message = NULL;
	const ::google::protobuf::Descriptor* descriptor = ::google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(typeName);
	if (descriptor)
	{
		const ::google::protobuf::Message* prototype = ::google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
		if (prototype)
		{
			message = prototype->New();
		}
	}
	return message;
}
#endif