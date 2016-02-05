#include "NetMessageManager.h"
#include "NetGoogleFilter.h"
#include "GameControl.h"

class NetMessageManager* m_gNetMessageManager = NULL;

string NetMessageManager::LandServerIP = "";
int NetMessageManager::LandServerPort = 0;
string NetMessageManager::GameServerIP = "";
int NetMessageManager::GameServerPort = 0;
string NetMessageManager::FileServerIP = "";
int NetMessageManager::FileServerPort = 0;
string NetMessageManager::BankServerIP = "";
int NetMessageManager::BankServerPort = 0;

NetMessageManager::NetMessageManager()
{
	m_pSocketGame = NULL;
	m_pMessageResponse = NULL;
	m_pMessageRequest = NULL;

	m_bGameSocketLinked = false;
	m_bGameSocketLinking = false;
	m_bGameSocketStoping = false;

	m_pSocketFile = NULL;
	m_bFileSocketLinked = false;
	m_bFileSocketLinding = false;
	m_bFileSocketStoping = false;
    
    m_pSocketBank = NULL;
    m_bBankSocketLinked = false;
    m_bBankSocketLinding = false;
    m_bFileSocketStoping = false;

	LandServerIP = "";
	LandServerPort = 0;
	GameServerIP = "";
	GameServerPort = 0;
	FileServerIP = "";
	FileServerPort = 0;
    BankServerIP = "";
    BankServerPort = 0;
}

NetMessageManager::~NetMessageManager()
{
	m_mapMessageList.clear();
	m_mapReflexMessage.clear();

	if( m_pSocketGame )
		delete m_pSocketGame;
	if( m_pSocketFile )
		delete m_pSocketFile;
    if( m_pSocketBank) {
        delete m_pSocketBank;
    }
	if( m_pMessageResponse )
		delete m_pMessageResponse;
	if( m_pMessageRequest )
		delete m_pMessageRequest;

	m_gNetMessageManager = NULL;

}

NetMessageManager* NetMessageManager::GetMessageManager( void )
{
	if( m_gNetMessageManager == NULL )
	{
		m_gNetMessageManager = new NetMessageManager();
		if( !m_gNetMessageManager->Init() )
		{
			delete m_gNetMessageManager;
			m_gNetMessageManager = NULL;
		}
	}

	return m_gNetMessageManager;
}

void NetMessageManager::ReleaseMessageManager( void )
{
	if( m_gNetMessageManager )
	{
		delete m_gNetMessageManager;
		m_gNetMessageManager = NULL;
	}
}

bool NetMessageManager::Init( void )
{
	if( !m_pSocketGame )
		m_pSocketGame = new NetSocket();
	if( !m_pSocketFile )
		m_pSocketFile = new NetSocket();
    if( !m_pSocketBank) {
        m_pSocketBank = new NetSocket();
    }
    
	if( !m_pMessageResponse )
		m_pMessageResponse = new NetMessageReponse();
	if( !m_pMessageRequest )
		m_pMessageRequest = new NetMessageRequest();

	m_mapMessageList.clear();
	m_mapReflexMessage.clear();

	RegisterAllMessage();

	NetMessageManager::LandServerIP = GameFile::GetGameFileHandle()->GetLandServerIP();
	NetMessageManager::LandServerPort = GameFile::GetGameFileHandle()->GetLandServerPort();
	return true;
}

void NetMessageManager::StateLinkLandSocket( void )
{
	if( m_gNetMessageManager->m_bGameSocketLinked || m_gNetMessageManager->m_bGameSocketLinking || LandServerIP.empty() )
		return;
	m_gNetMessageManager->m_pSocketGame->StartSocket( NetMessageManager::LandServerIP, NetMessageManager::LandServerPort );
	m_gNetMessageManager->m_bGameSocketLinking = true;
}

void NetMessageManager::StateLinkGameSocket( void )
{
	if( m_gNetMessageManager->m_bGameSocketLinked || m_gNetMessageManager->m_bGameSocketLinking || GameServerIP.empty() )
		return;
	m_gNetMessageManager->m_pSocketGame->StartSocket( NetMessageManager::GameServerIP, NetMessageManager::GameServerPort );
	m_gNetMessageManager->m_bGameSocketLinking = true;
}


void NetMessageManager::StopGameSocket( void )
{
	if( !m_gNetMessageManager->m_bGameSocketLinked )
		return;

	m_gNetMessageManager->m_bGameSocketStoping = true;
	m_gNetMessageManager->m_pSocketGame->StopSocket();
}

void NetMessageManager::StateLinkFileSocket( void )
{
	if( m_gNetMessageManager->m_bFileSocketLinked || m_gNetMessageManager->m_bFileSocketLinding || FileServerIP.empty() )
		return;

	m_gNetMessageManager->m_pSocketFile->StartSocket( NetMessageManager::FileServerIP, NetMessageManager::FileServerPort);
	m_gNetMessageManager->m_bFileSocketLinding = true;
}

void NetMessageManager::StopFileSocket( void )
{
	if( !m_gNetMessageManager->m_bFileSocketLinked )
		return;
	m_gNetMessageManager->m_bFileSocketStoping = true;
	m_gNetMessageManager->m_pSocketFile->StopSocket();
}

void NetMessageManager::StateLinkBankSocket( void )
{
    if( m_gNetMessageManager->m_bBankSocketLinked || m_gNetMessageManager->m_bBankSocketLinding || BankServerIP.empty() )
		return;
    
	m_gNetMessageManager->m_pSocketBank->StartSocket( NetMessageManager::BankServerIP, NetMessageManager::BankServerPort);
	m_gNetMessageManager->m_bBankSocketLinding = true;
}

void NetMessageManager::StopBankSocket( void )
{
    if( !m_gNetMessageManager->m_bBankSocketLinked )
		return;
	m_gNetMessageManager->m_bBankSocketStoping = true;
	m_gNetMessageManager->m_pSocketBank->StopSocket();
}

void NetMessageManager::NetMessageLogic( float dt )
{
	if( m_bGameSocketLinking )//尝试连接gamesocket 未连接成功的处理
	{
		if( !m_pSocketGame->IsConnected() && !m_pSocketGame->IsConnecting() )
		{
			m_pSocketGame->StopSocket();
			m_bGameSocketLinking = false;
		}
	}

	if( m_bGameSocketLinked )//连接状态 网络中断的处理
	{
		if( !m_pSocketGame->IsConnected() && !m_pSocketGame->IsConnecting() )
		{
			m_pSocketGame->StopSocket();
			m_bGameSocketLinked = false;
			m_bGameSocketStoping = false;
		}
		//m_pSocketGame->ReceiveData();
	}
	if( !m_bGameSocketLinked )//未在连接状态 正常连接后处理
	{
		if( m_pSocketGame->IsConnected() )
		{
			m_bGameSocketLinked = m_pSocketGame->IsConnected();
			m_bGameSocketLinking = false;
		}
	}

	//接收Game消息
	if(!m_pSocketGame->IsEmptyWithReceiveQueue())
	{
		NetGoogleFilter::Get_MSG_BODY_WithPresonSerializeString( m_pSocketGame->GetFrontReceiveData() );
		m_pSocketGame->PopReceiveQueue();
	}

	//-------------------
	if( m_bFileSocketLinding )//尝试连接gamesocket 未连接成功的处理
	{
		if( !m_pSocketFile->IsConnected() && !m_pSocketFile->IsConnecting() )
		{
			m_pSocketFile->StopSocket();
			m_bFileSocketLinding = false;
		}
	}

	if( m_bFileSocketLinked )//连接状态 网络中断的处理
	{
		if( !m_pSocketFile->IsConnected() && !m_pSocketFile->IsConnecting() )
		{
			m_pSocketFile->StopSocket();
			m_bFileSocketLinked = false;
			m_bFileSocketStoping = false;
		}
		//m_pSocketFile->ReceiveData();
	}
	if( !m_bFileSocketLinked )//未在连接状态 正常连接后处理
	{
		if( m_pSocketFile->IsConnected() )
		{
			m_bFileSocketLinked = m_pSocketFile->IsConnected();
			m_bFileSocketLinding = false;
		}
	}

	//接收Game消息
	if(!m_pSocketFile->IsEmptyWithReceiveQueue())
	{
		NetGoogleFilter::Get_MSG_BODY_WithPresonSerializeString( m_pSocketFile->GetFrontReceiveData() );
		m_pSocketFile->PopReceiveQueue();
	}
    
    //-------------------
    if( m_bBankSocketLinding )//尝试连接gamesocket 未连接成功的处理
	{
		if( !m_pSocketBank->IsConnected() && !m_pSocketBank->IsConnecting() )
		{
			m_pSocketBank->StopSocket();
			m_bBankSocketLinding = false;
		}
	}
    
	if( m_bBankSocketLinked )//连接状态 网络中断的处理
	{
		if( !m_pSocketBank->IsConnected() && !m_pSocketBank->IsConnecting() )
		{
			m_pSocketBank->StopSocket();
			m_bBankSocketLinked = false;
			m_bBankSocketStoping = false;
		}
		//m_pSocketGame->ReceiveData();
	}
	if( !m_bBankSocketLinked )//未在连接状态 正常连接后处理
	{
		if( m_pSocketBank->IsConnected() )
		{
			m_bBankSocketLinked = m_pSocketBank->IsConnected();
			m_bBankSocketLinding = false;
		}
	}
    
	//接收Game消息
	if(!m_pSocketBank->IsEmptyWithReceiveQueue())
	{
		NetGoogleFilter::Get_MSG_BODY_WithPresonSerializeString( m_pSocketBank->GetFrontReceiveData() );
		m_pSocketBank->PopReceiveQueue();
	}
}


void NetMessageManager::RegisterAllMessage( void )
{
	//登陆
	RegisterMessage( API_UserLoginRequest,"message.UserLoginRequest");
	RegisterMessage( API_UserLoginResponse,"message.UserLoginResponse");
    
    //下发客户端地图信息
    RegisterMessage( API_DownloadMapInforRequest, "message.DownloadMapInforRequest");
    RegisterMessage( API_DownloadMapInforResponse, "message.DownloadMapInforResponse");
    
    //下发战斗信息列表
    RegisterMessage( API_DownloadBattleInforRequest, "message.DownloadBattleInforRequest");
    RegisterMessage( API_DownloadBattleInforResponse, "message.DownloadBattleInforResponse");
    
    //客户端定时上传流水账
    RegisterMessage( API_OperateSequenceRequest, "message.OperateSequenceRequest");
    RegisterMessage( API_OperateSequenceResponse, "message.OperateSequenceResponse");
    
    //招兵
    RegisterMessage( API_ProduceSoldiersRequest, "message.ProduceSoldiersRequest");
    RegisterMessage( API_ProduceSoldiersResponse, "message.ProduceSoldiersResponse");
    
    //战斗匹配
    RegisterMessage( API_BattleMatchingRequest,"message.BattleMatchingRequest");
	RegisterMessage( API_BattleMatchingResponse,"message.BattleMatchingResponse");
    
    //上传战斗结果
    RegisterMessage( API_UploadBattleResultRequest,"message.UploadBattleResultRequest");
	RegisterMessage( API_UploadBattleResultResponse,"message.UploadBattleResultResponse");
    
    //开始战斗
    RegisterMessage( API_BattleStartRequest,"message.BattleStartRequest");
	RegisterMessage( API_BattleStartResponse,"message.BattleStartResponse");
    
    //充值
    RegisterMessage( API_RechargeRequest,"message.RechargeRequest");
	RegisterMessage( API_RechargeResponse,"message.RechargeResponse");
    
    //复仇
    RegisterMessage( API_RevengeBattleRequest,"message.RevengeBattleRequest");
    RegisterMessage( API_RevengeBattleResponse,"message.RevengeBattleResponse");
    
    //上传战斗过程
    RegisterMessage( API_UploadBattleFlowRequest,"message.UploadBattleFlowRequest");
    RegisterMessage( API_UploadBattleFlowResponse,"message.UploadBattleFlowResponse");
    
    //下载战斗过程
    RegisterMessage( API_IoFileRequest,"message.IoFileRequest");
    RegisterMessage( API_IoFileResponse,"message.IoFileResponse");
    
    //取消战斗
    RegisterMessage( API_CancleBattleRequest,"message.CancleBattleRequest");
    RegisterMessage( API_CancleBattleResponse,"message.CancleBattleResponse");
}

void NetMessageManager::RegisterMessage( int ID, string strRegisterBodyStr )
{
	m_mapMessageList.insert(pair<string,int>(strRegisterBodyStr,ID));
	m_mapReflexMessage.insert(pair<int,string>(ID,strRegisterBodyStr));
}