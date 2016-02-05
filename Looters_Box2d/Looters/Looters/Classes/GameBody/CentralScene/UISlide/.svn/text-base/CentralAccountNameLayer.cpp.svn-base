//
//  CentralAccountNameLayer.cpp
//  Looters
//
//  Created by 王 宁 on 13-1-8.
//
//

#include "CentralAccountNameLayer.h"
#include <iostream>
#include "cocos2d.h"
#include "GameControl.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define tableViewW  418
#define tableViewH  250

CentralAccountNameLayer::CentralAccountNameLayer()
: s_bg(NULL)
, name_textfield(NULL)
, name_tiplabel(NULL)
, name_tiplabel2(NULL)
{
    
}

CentralAccountNameLayer::~CentralAccountNameLayer()
{

}

bool CentralAccountNameLayer::init( void )
{
	if( !CCLayer::init() )
		return false;
    this->setTouchEnabled(true);
    
    return true;
}

SEL_MenuHandler CentralAccountNameLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget,CCString * pSelectorName){
    
    //Bind Menu Events，绑定一个menu，点击方法是press，以下同理
    
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "press",MainScene::press);
    return NULL;
}

SEL_CCControlHandler CentralAccountNameLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName){
    
    //Bind CCControl Events
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onOk",CentralAccountNameLayer::onOk);
    return NULL;
}

bool CentralAccountNameLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode){
    
    //Bind variables
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_bg", CCSprite *, this->s_bg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "name_textfield", CCSprite *, this->name_textfield);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "name_tiplabel", CCLabelTTF *, this->name_tiplabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "name_tiplabel2", CCLabelTTF *, this->name_tiplabel2);
    return false;
    
}


void CentralAccountNameLayer::onNodeLoaded(CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader){
    //检测scene
    
    CCLOG("MainScene loading.....successed!") ;
}

void CentralAccountNameLayer::onEnter()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
    
    CCNode::onEnter();
    
    // add this layer to concern the keypad msg
    pDirector->getKeypadDispatcher()->addDelegate(this);
    
    initWithColor( ccc4(0,0,0,100) , pDirector->getWinSize().width,pDirector->getWinSize().height);
}

void CentralAccountNameLayer::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    pDirector->getKeypadDispatcher()->removeDelegate(this);
    CCNode::onExit();
}


bool CentralAccountNameLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLOG("响应啦........................................");
    return true;
}

void CentralAccountNameLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralAccountNameLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralAccountNameLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}


void CentralAccountNameLayer::initCentralAccount1UI()
{
    
}

void CentralAccountNameLayer::onOk(cocos2d::CCObject * pSender)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    pCentralScene->m_pCentralUILayer->setVisible(true);
    
    pCentralScene->removeChild(pCentralScene->m_pCentralAccountNameLayer, false);
    
    pCentralScene->m_pCentralAccountNameLayer = NULL;
}