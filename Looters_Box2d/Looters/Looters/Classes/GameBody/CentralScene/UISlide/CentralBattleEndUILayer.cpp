//
//  CentralBattleEndUILayer.cpp
//  Looters
//
//  Created by yisuode on 12-12-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CentralBattleEndUILayer.h"
#include "cocos2d.h"
#include "GameControl.h"
#include "CommonResource.h"
#include "ChangeLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;

CentralBattleEndUILayer::CentralBattleEndUILayer():s_star1(NULL)
, s_star2(NULL)
, s_star3(NULL)
, s_with(NULL)
, s_win(NULL)
, l_gold(NULL)
, l_water(NULL)
, l_cup(NULL)
{

}

CentralBattleEndUILayer::~CentralBattleEndUILayer()
{
    CC_SAFE_RELEASE(s_star1);
    CC_SAFE_RELEASE(s_star2);
    CC_SAFE_RELEASE(s_star3);
    CC_SAFE_RELEASE(s_with);
    CC_SAFE_RELEASE(s_win);
    CC_SAFE_RELEASE(l_gold);
    CC_SAFE_RELEASE(l_water);
    CC_SAFE_RELEASE(l_cup);
}

bool CentralBattleEndUILayer::init( void )
{
	if( !CCLayer::init() )
		return false;
    
    
    
    
    return true;
}

SEL_MenuHandler CentralBattleEndUILayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget,CCString * pSelectorName){
    
    //Bind Menu Events，绑定一个menu，点击方法是press，以下同理
    
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "press",MainScene::press);
    
    return NULL;
    
}

SEL_CCControlHandler CentralBattleEndUILayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName){
    
    //Bind CCControl Events
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onHome",CentralBattleEndUILayer::onHome);
    return NULL;
    
}

bool CentralBattleEndUILayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode){
    
    //Bind variables
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_star1", CCSprite *, this->s_star1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_star2", CCSprite *, this->s_star2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_star3", CCSprite *, this->s_star3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_with", CCSprite *, this->s_with);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_win", CCSprite *, this->s_win);
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_gold", CCLabelTTF *, this->l_gold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_water", CCLabelTTF *, this->l_water);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_cup", CCLabelTTF *, this->l_cup);
    return false;
    
}


void CentralBattleEndUILayer::onNodeLoaded(CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader){
    
    //检测scene
    
    CCLOG("MainScene loading.....successed!") ;
}


void CentralBattleEndUILayer::show_component()
{
    CentralLayer *LData = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    CentralData *Ddata = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    // 失败or成功显示
    if(LData->battle_star_count == 0){
        s_win->setVisible(false);
    }else{
        s_with->setVisible(false);
    }
    
    // 星星显示
    if (LData->battle_star_count == 0) {
        s_star1->setVisible(false);
        s_star2->setVisible(false);
        s_star3->setVisible(false);
    }
    else if (LData->battle_star_count == 1) {
        s_star2->setVisible(false);
        s_star3->setVisible(false);
    }
    else if(LData->battle_star_count == 2){
        s_star3->setVisible(false);
    }
    
    // 金币and药水andpvp分数
    l_gold->setString(CommonResource::getStringFromInt(LData->battle_golden_count).c_str());
    l_water->setString(CommonResource::getStringFromInt(LData->battle_elixir_count).c_str());
    if (LData->battle_star_count == 0) {
        l_cup->setString(CommonResource::getStringFromInt(Ddata->m_MatchPlayer->lose_pvp_mark).c_str());
    }else{
        l_cup->setString(CommonResource::getStringFromInt(Ddata->m_MatchPlayer->pvp_mark).c_str());
    }
    
    // 使用兵情况
    iconArr = CCArray::create();
    iconArr->retain();
    for (int i=0; i<10; i++) {
        CCSprite* iconbg = CCSprite::createWithSpriteFrameName("ui_public_bg3.png");
        iconbg->setTag(-1);
        iconbg->setScale(0.35f);
        iconbg->setAnchorPoint(ccp(0,0));
        iconbg->setPosition(ccp(100+28*i,60));
        this->addChild(iconbg);
        iconArr->addObject(iconbg);
    }
    
    vector<CentralData::AttackerSoldiersAndSpell*>* list = Ddata->m_AttackerSoldiersAndSpell;
    for (int i=0; i<list->size(); i++) {
        CentralData::AttackerSoldiersAndSpell *obj = list->at(i);
        if (obj->used_type == 0) {
            CCSprite *iconbg = (CCSprite*)iconArr->objectAtIndex(i);
            
            char framename[256] = {0};
            sprintf(framename,"soldiers_Icon%d.png",obj->characterIdOrSpellId);
            
            IconSprite_CentralPVPMapUI* objIcon = (IconSprite_CentralPVPMapUI*)CCSprite::createWithSpriteFrameName(framename);
            objIcon->setScale(1.0f);
            objIcon->setPosition(ccp(iconbg->getContentSize().width/2,iconbg->getContentSize().height/2));
            objIcon->setTag(0);
            objIcon->iconID = obj->characterIdOrSpellId;
            iconbg->addChild(objIcon);
            
            int cutcount = -(obj->maxcount - obj->count);
            string strcount = CommonResource::getStringFromInt(cutcount);
            CCLabelTTF* objLabel = CCLabelTTF::create(strcount.c_str(), "Helvetica-Bold", 10);
            objLabel->setColor(ccRED);
            objLabel->setScale(2.0f);
            objLabel->setPosition(ccp(iconbg->getContentSize().width/2,iconbg->getContentSize().height-10));
            objLabel->setTag(1);
            iconbg->addChild(objLabel);
    
            iconbg->setTag(i);
        }
    }
}

void CentralBattleEndUILayer::onHome(cocos2d::CCObject * pSender)
{
    this->unscheduleAllSelectors();
    SceneManage::GetSceneManageHendle()->m_pCentralScene->LoadSceneLayer(CENTRALVIEW_SELF);
    ChangeLayer::ShowChangeLayer(SceneManage::GetSceneManageHendle()->m_pCentralScene);
}


















