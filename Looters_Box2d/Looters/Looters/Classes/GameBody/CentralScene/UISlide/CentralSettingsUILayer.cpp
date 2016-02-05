//
//  CentralSettingsUILayer.cpp
//  Looters
//
//  Created by 王 宁 on 13-1-8.
//
//
#include "cocos2d.h"
#include "GameControl.h"
#include "CentralSettingsUILayer.h"
USING_NS_CC;
USING_NS_CC_EXT;


CentralSettingsUILayer::CentralSettingsUILayer()
: layercolorbg(NULL)
, s_bg(NULL)
, b_music_on(NULL)
, b_music_off(NULL)
, b_wav_on(NULL)
, b_wav_off(NULL)
, b_close(NULL)
{
    
}

CentralSettingsUILayer::~CentralSettingsUILayer()
{
    CC_SAFE_RELEASE(layercolorbg);
    CC_SAFE_RELEASE(s_bg);
    CC_SAFE_RELEASE(b_music_on);
    CC_SAFE_RELEASE(b_music_off);
    CC_SAFE_RELEASE(b_wav_on);
    CC_SAFE_RELEASE(b_wav_off);
    CC_SAFE_RELEASE(b_close);
}

bool CentralSettingsUILayer::init( void )
{
	if( !CCLayer::init() )
		return false;
    
    return true;
}

SEL_MenuHandler CentralSettingsUILayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget,CCString * pSelectorName){
    //Bind Menu Events，绑定一个menu，点击方法是press
    return NULL;
}

SEL_CCControlHandler CentralSettingsUILayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName){
    
    //Bind CCControl Events
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMusicOn",CentralSettingsUILayer::onMusicOn);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMusicOff",CentralSettingsUILayer::onMusicOff);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onWavOn",CentralSettingsUILayer::onWavOn);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onWavOff",CentralSettingsUILayer::onWavOff);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onLogin",CentralSettingsUILayer::onLogin);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onAbout",CentralSettingsUILayer::onAbout);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onHelp",CentralSettingsUILayer::onHelp);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClose",CentralSettingsUILayer::onClose);
    return NULL;
}

bool CentralSettingsUILayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode){
    
    //Bind variables
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "layercolorbg", CCLayerColor *, this->layercolorbg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_bg", CCSprite *, this->s_bg);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "b_music_on", CCControlButton *, this->b_music_on);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "b_music_off", CCControlButton *, this->b_music_off);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "b_wav_on", CCControlButton *, this->b_wav_on);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "b_wav_offf", CCControlButton *, this->b_wav_off);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "b_close", CCControlButton *, this->b_close);
    return false;
}


void CentralSettingsUILayer::onNodeLoaded(CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader){
    //检测scene
    
    CCLOG("MainScene loading.....successed!") ;
}

void CentralSettingsUILayer::onEnter()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
    
    CCNode::onEnter();
    
    initWithColor( ccc4(0,0,0,100) , pDirector->getWinSize().width,pDirector->getWinSize().height);
}

void CentralSettingsUILayer::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    CCNode::onExit();
}


bool CentralSettingsUILayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLOG("响应啦........................................");
    return true;
}

void CentralSettingsUILayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralSettingsUILayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralSettingsUILayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralSettingsUILayer::initCentralSettingsUI()
{
    if(GameData::m_stUserData->is_openmusic){
        b_music_on->setVisible(true);
        b_music_on->setTouchEnabled(true);
        b_music_off->setVisible(false);
        b_music_off->setTouchEnabled(false);
    }else{
        b_music_on->setVisible(false);
        b_music_on->setTouchEnabled(false);
        b_music_off->setVisible(true);
        b_music_off->setTouchEnabled(true);
    }
    
    if (GameData::m_stUserData->is_openwav) {
        b_wav_on->setVisible(true);
        b_wav_on->setTouchEnabled(true);
        b_wav_off->setVisible(false);
        b_wav_off->setTouchEnabled(false);
    }else{
        b_wav_on->setVisible(false);
        b_wav_on->setTouchEnabled(false);
        b_wav_off->setVisible(true);
        b_wav_off->setTouchEnabled(true);
    }
}

void CentralSettingsUILayer::onMusicOn(cocos2d::CCObject * pSender)
{
    b_music_on->setVisible(false);
    b_music_on->setTouchEnabled(false);
    b_music_off->setVisible(true);
    b_music_off->setTouchEnabled(true);
    
    if(GameData::m_stUserData->is_openmusic){
        GameData::m_stUserData->is_openmusic = false;
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
        CCUserDefault::sharedUserDefault()->setBoolForKey("is_openmusic", GameData::m_stUserData->is_openmusic);
    }
}

void CentralSettingsUILayer::onMusicOff(cocos2d::CCObject * pSender)
{
    b_music_on->setVisible(true);
    b_music_on->setTouchEnabled(true);
    b_music_off->setVisible(false);
    b_music_off->setTouchEnabled(false);
    
    if(!GameData::m_stUserData->is_openmusic){
        GameData::m_stUserData->is_openmusic = true;
        SoundManage::GetSoundManageHandle()->_stopBackgroundMusic(true);
        SoundManage::GetSoundManageHandle()->_playBackgroundMusic("home_music.mp3", true);
        CCUserDefault::sharedUserDefault()->setBoolForKey("is_openmusic", GameData::m_stUserData->is_openmusic);
    }
}

void CentralSettingsUILayer::onWavOn(cocos2d::CCObject * pSender)
{
    b_wav_on->setVisible(false);
    b_wav_on->setTouchEnabled(false);
    b_wav_off->setVisible(true);
    b_wav_off->setTouchEnabled(true);
    
    if(GameData::m_stUserData->is_openwav){
        GameData::m_stUserData->is_openwav = false;
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
        CCUserDefault::sharedUserDefault()->setBoolForKey("is_openwav", GameData::m_stUserData->is_openwav);
    }
}

void CentralSettingsUILayer::onWavOff(cocos2d::CCObject * pSender)
{
    b_wav_on->setVisible(true);
    b_wav_on->setTouchEnabled(true);
    b_wav_off->setVisible(false);
    b_wav_off->setTouchEnabled(false);
    
    if(!GameData::m_stUserData->is_openwav){
        GameData::m_stUserData->is_openwav = true;
        CCUserDefault::sharedUserDefault()->setBoolForKey("is_openwav", GameData::m_stUserData->is_openwav);
    }
}

void CentralSettingsUILayer::onLogin(cocos2d::CCObject * pSender)
{
    // 删除当前界面
    this->removeFromParentAndCleanup(false);
    SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralSettingsUILayer = NULL;
    
    
    // 显示登陆界面
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    CentralAccountLoginLayerLoader* centralAccountLoginLayerLoader = CentralAccountLoginLayerLoader::loader();
    
    
    pCentralScene->m_CentralAccountLoginLayer = (CentralAccountLoginLayer*) pCentralScene->openTest(GAME_FILE_TRANSFORM("UI_Account_2",".ccbi").c_str(),"UI_Account_2",centralAccountLoginLayerLoader);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    KeyboardNotificationLayer* pUsernameLayer = new TextFieldTTFDefaultTest();
    pUsernameLayer->autorelease();
    pCentralScene->m_CentralAccountLoginLayer->addKeyboardNotificationLayer_Username(pUsernameLayer);

    KeyboardNotificationLayer* pPasswordLayer = new TextFieldTTFDefaultTest();
    pPasswordLayer->autorelease();
    pCentralScene->m_CentralAccountLoginLayer->addKeyboardNotificationLayer_Password(pPasswordLayer);
    
    pCentralScene->addChild(pCentralScene->m_CentralAccountLoginLayer,200);
    pCentralScene->m_CentralAccountLoginLayer->initCentralAccount2UI();

    pUsernameLayer->m_pTrackNode->setTag(0);
    pPasswordLayer->m_pTrackNode->setTag(1);
    pUsernameLayer->setTrackNodePosition(pCentralScene->m_CentralAccountLoginLayer->s_account_tf->getPosition());
    pPasswordLayer->setTrackNodePosition(pCentralScene->m_CentralAccountLoginLayer->s_password_tf->getPosition());
}

void CentralSettingsUILayer::onAbout(cocos2d::CCObject * pSender)
{

}

void CentralSettingsUILayer::onHelp(cocos2d::CCObject * pSender)
{

}

void CentralSettingsUILayer::onClose(cocos2d::CCObject * pSender)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    pCentralScene->m_pCentralUILayer->setVisible(true);
    
    pCentralScene->removeChild(pCentralScene->m_pCentralSettingsUILayer, false);
    
    pCentralScene->m_pCentralSettingsUILayer = NULL;
}