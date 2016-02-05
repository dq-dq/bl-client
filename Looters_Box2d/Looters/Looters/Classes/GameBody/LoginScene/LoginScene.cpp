#include "LoginScene.h"
#include "GameControl.h"
#include "LoginLayer.h"
USING_NS_CC;

LoginScene::LoginScene()
{
    
}

LoginScene::~LoginScene()
{
    
}

bool LoginScene::init()
{
    if ( !CCScene::init() )
    {
        return false;
    }
    
    GameData::m_stUserData = new UserData();
    
    if(!CCUserDefault::sharedUserDefault()->getBoolForKey("_IS_EXISTED")){
        CCUserDefault::sharedUserDefault()->setBoolForKey("_IS_EXISTED",true);
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("is_openmusic",true);
        CCUserDefault::sharedUserDefault()->setBoolForKey("is_openwav",true);
    }
    else {
        GameData::m_stUserData->gamecenter_id = CCUserDefault::sharedUserDefault()->getStringForKey("gamecenter_id");
        
        
        GameData::m_stUserData->is_openwav = CCUserDefault::sharedUserDefault()->getBoolForKey("is_openwav");
        GameData::m_stUserData->is_openmusic = CCUserDefault::sharedUserDefault()->getBoolForKey("is_openmusic");
    }
    
    // 添加LoginLayer层
    m_pLogicLayer = LoginLayer::create();
    
    this->addChild(m_pLogicLayer);
    
    return true;
}