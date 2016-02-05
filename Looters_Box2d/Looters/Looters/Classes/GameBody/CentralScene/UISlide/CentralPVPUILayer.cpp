//
//  CentralPVPUILayer.cpp
//  Looters
//
//  Created by yisuode on 12-11-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CentralPVPUILayer.h"
#include "CentralPVPMapUILayer.h"
#include "cocos2d.h"
#include "GameControl.h"
#include "ChangeLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;

CentralPVPUILayer::CentralPVPUILayer():
s_map_01(NULL)
, s_map_02(NULL)
, s_map_03(NULL)
, s_pvp_find_bg(NULL)
, s_gonghui(NULL)
, s_mofa(NULL)
, s_jiangbei(NULL)
, b_direction(NULL)
, l_costgold(NULL)
{
}

CentralPVPUILayer::~CentralPVPUILayer()
{
    CC_SAFE_RELEASE(s_map_01);
    CC_SAFE_RELEASE(s_map_02);
    CC_SAFE_RELEASE(s_map_03);
    CC_SAFE_RELEASE(s_pvp_find_bg);
    CC_SAFE_RELEASE(s_gonghui);
    CC_SAFE_RELEASE(s_mofa);
    CC_SAFE_RELEASE(s_jiangbei);
    CC_SAFE_RELEASE(b_direction);
    CC_SAFE_RELEASE(l_costgold);
}

bool CentralPVPUILayer::init( void )
{
	if( !CCLayer::init() )
		return false;
    return true;
}

SEL_MenuHandler CentralPVPUILayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget,CCString * pSelectorName){
    return NULL;
}

SEL_CCControlHandler CentralPVPUILayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName){
    
    //Bind CCControl Events
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onDirection",CentralPVPUILayer::onDirection);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtuPVP",CentralPVPUILayer::onBtuPVP);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnPVPCancel",CentralPVPUILayer::onBtnPVPCancel);
    return NULL;
}

bool CentralPVPUILayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode){
    
    //Bind variables
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_map_01", CCSprite *, this->s_map_01);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_map_02", CCSprite *, this->s_map_02);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_map_03", CCSprite *, this->s_map_03);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_pvp_find_bg", CCSprite *, this->s_pvp_find_bg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_gonghui", CCSprite *, this->s_gonghui);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_mofa", CCSprite *, this->s_mofa);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_jiangbei", CCSprite *, this->s_jiangbei);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "b_direction", CCControlButton *, this->b_direction);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_costgold", CCLabelTTF *, this->l_costgold);
    return false;
}


void CentralPVPUILayer::onNodeLoaded(CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader){
    //检测scene
    CCLOG("MainScene loading.....successed!") ;
}


void CentralPVPUILayer::onEnter()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
    
    CCNode::onEnter();
}

void CentralPVPUILayer::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    CCNode::onExit();
}


bool CentralPVPUILayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLOG("响应啦........................................");
    return true;
}

void CentralPVPUILayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralPVPUILayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralPVPUILayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralPVPUILayer::onDirection(cocos2d::CCObject * pSender)
{
    if (s_pvp_find_bg->getPositionX()  == 579.0f) {
        CCActionInterval *action35 = CCMoveTo::create(0.3f, ccpSub(s_pvp_find_bg->getPosition(),ccp(230,0)));
        CCFiniteTimeAction* myseq = CCSequence::create(action35,NULL);
        s_pvp_find_bg->runAction(myseq);
    }else{
        CCActionInterval *action35 = CCMoveTo::create(0.3f, ccpAdd(s_pvp_find_bg->getPosition(),ccp(230,0)));
        CCFiniteTimeAction* myseq = CCSequence::create(action35,NULL);
        s_pvp_find_bg->runAction(myseq);
    }
}

void CentralPVPUILayer::onBtuPVP(cocos2d::CCObject * pSender)
{
    CentralData *data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    // 判定钱是否够匹配玩家
    if (data->m_Central_UserData->user_gold - data->m_Central_UserData->battleMathingUseCount > 0 || NotNetworking) {
        data->m_Central_UserData->user_gold = data->m_Central_UserData->user_gold - data->m_Central_UserData->battleMathingUseCount;
        SceneManage::GetSceneManageHendle()->m_pCentralScene->SetBattleMode(CENTRALVIEW_PVP, BATTLE_MODE_PVP_MATCH);
        SceneManage::GetSceneManageHendle()->m_pCentralScene->LoadSceneLayer(CENTRALVIEW_BATTLE);
        ChangeLayer::ShowChangeLayer(SceneManage::GetSceneManageHendle()->m_pCentralScene);
    }
    else{
        // 提示
        string str = "";
        ErroCode__(NO_ENOUGH_GOLDEN,str);
    }
}

void CentralPVPUILayer::onBtnPVPCancel(cocos2d::CCObject * pSender)
{
    this->removeFromParentAndCleanup(true);
}

void CentralPVPUILayer::initCentralPVPUI()
{
    CentralData *data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    l_costgold->setString(CommonResource::getStringFromInt(data->m_Central_UserData->battleMathingUseCount).c_str());
}





