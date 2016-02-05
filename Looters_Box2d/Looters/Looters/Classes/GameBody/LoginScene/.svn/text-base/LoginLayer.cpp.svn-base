#include <iostream>
#include "LoginLayer.h"
#include "NetMessageManager.h"
#include "GameSceneManage.h"
#include "CommonResource.h"
#include "GameDebug.h"
#include "LoadingLayer.h"

USING_NS_CC;

void UserLoginResponseFun( int ID, Message* responseMessage);

LoginLayer::LoginLayer()
{
    
}

LoginLayer::~LoginLayer()
{
    
}

bool LoginLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // 初始化登陆界面
    CCLog("LoginLayer::init() -----------------");
    
    PUSH_REPNSECALLFUNC(message_reponse(UserLoginResponseFun));
    CCScheduler * scheduler = CCDirector::sharedDirector()->getScheduler();
    scheduler->scheduleSelector(schedule_selector(LoginLayer::Update), this, 1.0f/60, false);
    
    
    m_enDetectProcess = detect_netinfo;
    
	m_iLinkCountMax = 2;
	m_iCurrentLinkCount = 0;
	m_iLinkGameCountMax = 2;
	m_iLinkGameCountCurrent = 0;
	m_bIsLogin = false;
	m_bLoginBack = false;
    
    return true;
}

void LoginLayer::Update(float dt)
{
    if(NotNetworking){
        m_enDetectProcess = next;
    }
    //检测网络
	if( m_enDetectProcess == detect_netinfo )
	{
        if( !NetMessageManager::GetMessageManager()->m_bGameSocketLinking &&
           !NetMessageManager::GetMessageManager()->m_bGameSocketLinked )
		{
			NetMessageManager::StateLinkLandSocket();
			
			if( m_iCurrentLinkCount == m_iLinkCountMax )
			{
				//连接失败
				m_iCurrentLinkCount = 0;
				m_enDetectProcess = next;
			}
			m_iCurrentLinkCount++;
		}
		if( NetMessageManager::GetMessageManager()->m_bGameSocketLinked )
		{
			m_iCurrentLinkCount = 0;
			m_enDetectProcess = detect_clientinfo;
		}
    }
    
    //连接登陆服务器
    if (m_enDetectProcess == detect_clientinfo)
    {
        if( m_bIsLogin == false )
		{
//            string macAddress;
//            if (CCUserDefault::sharedUserDefault()->getStringForKey("macaddress").empty()) {
//                macAddress = Until::getmac();
//                CCUserDefault::sharedUserDefault()->setStringForKey("macaddress",macAddress.c_str());
//                NetMessageManager::GetMessageManager()->m_pMessageRequest->SendUserLoginRequest( "",                                                                                                              "chinese",                                                                                                           "1.0",                                                                                                              macAddress);
//            }else {
//                macAddress = CCUserDefault::sharedUserDefault()->getStringForKey("macaddress");
//                NetMessageManager::GetMessageManager()->m_pMessageRequest->SendUserLoginRequest( macAddress,                                                                                                              "chinese",                                                                                                           "1.0",                                                                                                              macAddress);
//            }

            
            if (false && !CCUserDefault::sharedUserDefault()->getBoolForKey("FirstPlay")) {
                //第一次进游戏，执行新手引导
                string  macAddress = Until::getmac();
                CCUserDefault::sharedUserDefault()->setStringForKey("macaddress",macAddress.c_str());
                NetMessageManager::GetMessageManager()->m_pMessageRequest->SendUserLoginRequest( "",                                                                                                              "chinese",                                                                                                           "1.0",                                                                                                              macAddress);
            }
            else
            {   //已经完成了新手引导，进登陆界面
                NetMessageManager::GetMessageManager()->m_pMessageRequest->SendUserLoginRequest( "",                                                                                                              "chinese",                                                                                                           "1.0",                                                                                                              "momoxie_0001");
            }
            
			m_bIsLogin = true;
		}
		if( m_bLoginBack == true )
		{
			m_bIsLogin = false;
			m_bLoginBack = false;
			NetMessageManager::StopGameSocket();
			m_enDetectProcess = detect_linkgameserver;
		}
    }
    // 连接游戏服务器
    if( m_enDetectProcess == detect_linkgameserver )
	{
		if( !NetMessageManager::GetMessageManager()->m_bGameSocketStoping &&
           !NetMessageManager::GetMessageManager()->m_bGameSocketLinking &&
           !NetMessageManager::GetMessageManager()->m_bGameSocketLinked )
		{
			NetMessageManager::StateLinkGameSocket();
			if( m_iLinkGameCountCurrent == m_iLinkGameCountMax )
			{
				//连接失败
				m_iLinkGameCountCurrent = 0;
				m_enDetectProcess = next;
			}
			m_iLinkGameCountCurrent++;
		}
		if( !NetMessageManager::GetMessageManager()->m_bGameSocketStoping &&
           NetMessageManager::GetMessageManager()->m_bGameSocketLinked )
		{
			//连接成功
			m_iLinkGameCountCurrent = 0;
			m_enDetectProcess = next;
		}
	}
    
    
    
    if( m_enDetectProcess == next )
	{
        // 进入游戏场景
		SceneManage::GetSceneManageHendle()->RunScece( SCENE_CENTRAL, true );

        CCLog("----------进入游戏场景");
        LoadingLayer::ShowLoadingLayer(SceneManage::GetSceneManageHendle()->m_pCentralScene);
	}
}

void UserLoginResponseFun(int ID, Message* responseMessage)
{
    LoginLayer* pLayer = SceneManage::GetSceneManageHendle()->m_pLogicScene->m_pLogicLayer;
    
    if( ID == API_UserLoginResponse )
	{
		message::UserLoginResponse* message = (message::UserLoginResponse*)responseMessage;
		if( message->result() == Code_SUCCESS )//成功
		{
			string IpPort = message->gameserveraddress();
			string Ip(IpPort,0,IpPort.find(':'));
			string Port(IpPort,IpPort.find(':')+1,IpPort.length() - IpPort.find(':')-1);
			NetMessageManager::GameServerIP = Ip;
            NetMessageManager::GameServerPort = CommonResource::getIntFromString(Port.c_str());
            CCLog("%s",message->info().c_str());
            CCLog("GameServerIP=%s    GameServerPort=%s",Ip.c_str(),Port.c_str());
            
			string fileIpPort = message->fileserveraddress();
			string fileIp(fileIpPort,0,fileIpPort.find(':'));
			string filePort(fileIpPort,fileIpPort.find(':')+1,fileIpPort.length() - fileIpPort.find(':')-1);
			NetMessageManager::FileServerIP = fileIp;
            NetMessageManager::FileServerPort = CommonResource::getIntFromString(filePort.c_str());
            CCLog("FileServerIP=%s   FileServerPort=%s",fileIp.c_str(),filePort.c_str());
            
            //获取gamecenter_id
            if (!message->tempmailaddress().empty()) {
                GameData::m_stUserData->gamecenter_id = message->tempmailaddress();
                CCLog("gamecenter_id=%s",message->tempmailaddress().c_str());

                if (CCUserDefault::sharedUserDefault()->getStringForKey("gamecenter_id").empty()) {
                    CCUserDefault::sharedUserDefault()->setStringForKey("gamecenter_id", GameData::m_stUserData->gamecenter_id.c_str());
                    CCUserDefault::sharedUserDefault()->flush();
                }
            }
            if (!NetMessageManager::GameServerIP.empty()) {
                pLayer->m_bLoginBack = true;
            }
		}
		else{
            ErroCode__(message->result(), message->info());
        }
	}
}



