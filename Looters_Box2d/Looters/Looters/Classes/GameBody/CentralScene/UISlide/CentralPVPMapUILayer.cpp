//
//  CentralPVPMapUILayer.cpp
//  Looters
//
//  Created by yisuode on 12-11-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CentralPVPMapUILayer.h"

#include "cocos2d.h"
#include "LSpriteLayer.h"
#include "GameControl.h"
#include "CommonResource.h"
#include "NetMessageManager.h"
#include "BattleRecorde.h"
#include "ChangeLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;


CentralPVPMapUILayer::CentralPVPMapUILayer():soldiersIcon_bg(NULL)
, s_potions(NULL)
, s_gold(NULL)
, s_mplayerCutTrophy(NULL)
, s_mplayerAddTrophy(NULL)
, s_mplayerPotions(NULL)
, s_mplayerGold(NULL)
, s_mplayerName(NULL)
, s_star_01(NULL)
, s_star_02(NULL)
, s_star_03(NULL)
, l_tipHelp(NULL)
, l_countdown(NULL)
, l_tipWarning(NULL)
, l_gem(NULL)
, l_potions(NULL)
, l_gold(NULL)
, l_goldmax(NULL)
, l_potionsmax(NULL)
, l_mplayerCutTrophy(NULL)
, l_mplayerAddTrophy(NULL)
, l_mplayerPotions(NULL)
, l_mplayerGold(NULL)
, l_mplayerName(NULL)
, l_overallDamage(NULL)
, l_mathplayer_lv(NULL)
, l_seek_playergold(NULL)
, b_next(NULL)
, selectUnit(NULL)
, l_tipend(NULL)
, b_cancel(NULL)
, b_end(NULL)
{
    countdown_readytime = 30.0f;
    countdown_gametime = 3*60.0f;
    numkl = 0;
    isShowcountdown_3 = true;
}

CentralPVPMapUILayer::~CentralPVPMapUILayer()
{
    CC_SAFE_RELEASE(soldiersIcon_bg);
    CC_SAFE_RELEASE(s_potions);
    CC_SAFE_RELEASE(s_gold);
    CC_SAFE_RELEASE(s_mplayerCutTrophy);
    CC_SAFE_RELEASE(s_mplayerAddTrophy);
    CC_SAFE_RELEASE(s_mplayerPotions);
    CC_SAFE_RELEASE(s_mplayerGold);
    CC_SAFE_RELEASE(s_mplayerName);
    CC_SAFE_RELEASE(s_star_01);
    CC_SAFE_RELEASE(s_star_02);
    CC_SAFE_RELEASE(s_star_03);
    
    CC_SAFE_RELEASE(l_tipHelp);
    CC_SAFE_RELEASE(l_countdown);
    CC_SAFE_RELEASE(l_tipWarning);
    CC_SAFE_RELEASE(l_gem);
    CC_SAFE_RELEASE(l_potions);
    CC_SAFE_RELEASE(l_gold);
    CC_SAFE_RELEASE(l_goldmax);
    CC_SAFE_RELEASE(l_potionsmax);
    CC_SAFE_RELEASE(l_mplayerCutTrophy);
    CC_SAFE_RELEASE(l_mplayerAddTrophy);
    CC_SAFE_RELEASE(l_mplayerPotions);
    CC_SAFE_RELEASE(l_mplayerGold);
    CC_SAFE_RELEASE(l_mplayerName);
    CC_SAFE_RELEASE(l_overallDamage);
    CC_SAFE_RELEASE(l_mathplayer_lv);
    CC_SAFE_RELEASE(l_seek_playergold);
    
    CC_SAFE_RELEASE(b_next);
    CC_SAFE_RELEASE(b_cancel);
    CC_SAFE_RELEASE(b_end);

	CC_SAFE_RELEASE(iconArr);
}

bool CentralPVPMapUILayer::init( void )
{
	if( !CCLayer::init() )
		return false;
    this->setTouchEnabled(true);

    return true;
}

SEL_MenuHandler CentralPVPMapUILayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget,CCString * pSelectorName){
    
    return NULL;
}

SEL_CCControlHandler CentralPVPMapUILayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName){
    
    //Bind CCControl Events
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCancel",CentralPVPMapUILayer::onCancel);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onEnd",CentralPVPMapUILayer::onEnd);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onNext",CentralPVPMapUILayer::onNext);

    return NULL;
}

bool CentralPVPMapUILayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "soldiersIcon_bg", CCSprite *, this->soldiersIcon_bg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_potions", CCSprite *, this->s_potions);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_gold", CCSprite *, this->s_gold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_mplayerCutTrophy", CCSprite *, this->s_mplayerCutTrophy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_mplayerAddTrophy", CCSprite *, this->s_mplayerAddTrophy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_mplayerPotions", CCSprite *, this->s_mplayerPotions);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_mplayerGold", CCSprite *, this->s_mplayerGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_mplayerName", CCSprite *, this->s_mplayerName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_star_01", CCSprite *, this->s_star_01);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_star_02", CCSprite *, this->s_star_02);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_star_03", CCSprite *, this->s_star_03);

    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_tipHelp", CCLabelTTF *, this->l_tipHelp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_countdown", CCLabelTTF *, this->l_countdown);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_tipWarning", CCLabelTTF *, this->l_tipWarning);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_gem", CCLabelTTF *, this->l_gem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_potions", CCLabelTTF *, this->l_potions);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_gold", CCLabelTTF *, this->l_gold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_goldmax", CCLabelTTF *, this->l_goldmax);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_potionsmax", CCLabelTTF *, this->l_potionsmax);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_mplayerCutTrophy", CCLabelTTF *, this->l_mplayerCutTrophy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_mplayerAddTrophy", CCLabelTTF *, this->l_mplayerAddTrophy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_mplayerPotions", CCLabelTTF *, this->l_mplayerPotions);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_mplayerGold", CCLabelTTF *, this->l_mplayerGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_mplayerName", CCLabelTTF *, this->l_mplayerName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_overallDamage", CCLabelTTF *, this->l_overallDamage);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_mathplayer_lv", CCLabelTTF *, this->l_mathplayer_lv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_seek_playergold", CCLabelTTF *, this->l_seek_playergold);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "b_next", CCControlButton *, this->b_next);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "b_cancel", CCControlButton *, this->b_cancel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "b_end", CCControlButton *, this->b_end);
    return false;
}


void CentralPVPMapUILayer::onNodeLoaded(CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader){
    
    //检测scene
    CCLOG("MainScene loading.....successed!") ;
}

void CentralPVPMapUILayer::initCentralPVPMapUI()
{
    iconArr = CCArray::create();
    iconArr->retain();
    
    
    CCMenu * pMenu = CCMenu::create();
    for (int i=0; i<10; i++) {
        CCSprite *m_pSpritecancel_01  = CCSprite::createWithSpriteFrameName("ui_public_bg3.png");
        CCSprite *m_pSpritecancel_02  = CCSprite::createWithSpriteFrameName("ui_public_bg3.png");
        CCMenuItemSprite* item = CCMenuItemSprite::create(m_pSpritecancel_01, m_pSpritecancel_02, this, menu_selector(CentralPVPMapUILayer::iconMenuItemCallback));
        item->setTag(-1);
        item->setScale(0.6f);
        item->setAnchorPoint(ccp(0,0));
        item->setPosition(ccp(8+47*i,CentralPVPMapUI_ICON_Y));
        
        iconArr->addObject(item);
    }
    pMenu->initWithArray(iconArr);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pMenu->setPosition(ccp(0,2));
    
    soldiersIcon_bg->addChild(pMenu);
    

    l_tipWarning->setVisible(false);
    b_end->setVisible(false);
    b_end->setTouchEnabled(false);
    s_star_01->setVisible(false);
    s_star_02->setVisible(false);
    s_star_03->setVisible(false);
}


void CentralPVPMapUILayer::iconMenuItemCallback(CCObject *pSender)
{
    CCMenuItemSprite* item = (CCMenuItemSprite*)pSender;
    CCLog("item ======   %d",item->getTag());
    
    if (item->getTag() != -1)
    {
        CCLog("%d",item->getTag());
        if (selectUnit && selectUnit->getPositionY() > 0) {
            selectUnit->setPosition(ccp(selectUnit->getPositionX(),selectUnit->getPositionY()-CentralPVPMapUI_ICON_Y));
        }
        selectUnit = NULL;
        selectUnit = item;
        CCLog("%d",selectUnit->getPositionY());
        selectUnit->setPosition(ccp(selectUnit->getPositionX(),selectUnit->getPositionY()+CentralPVPMapUI_ICON_Y));
    }
}

void CentralPVPMapUILayer::response_CallUI()
{
    CentralData::Central_UserData* playerself = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_Central_UserData;
    
    CentralData::MatchPlayer* mathplayer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_MatchPlayer;
    l_mplayerName->setString(mathplayer->nickName->c_str());
    l_mathplayer_lv->setString(CommonResource::getStringFromInt(mathplayer->level).c_str());
    
    l_mplayerAddTrophy->setString(CommonResource::getStringFromInt(mathplayer->pvp_mark).c_str());
    string str = "";
    str.append(CommonResource::getStringFromInt(mathplayer->lose_pvp_mark).c_str());
    l_mplayerCutTrophy->setString(str.c_str());
    
    l_gem->setString(CommonResource::getStringFromInt(playerself->user_gem).c_str());
    
    string str_potions = "Max:";
    str_potions.append(CommonResource::getStringFromInt(playerself->user_potionsMAX).c_str());
    l_potionsmax->setString(str_potions.c_str());
    string str_golds = "Max:";
    str_golds.append(CommonResource::getStringFromInt(playerself->user_goldMAX).c_str());
    l_goldmax->setString(str_golds.c_str());
    
    // 查找下一玩家花费
    l_seek_playergold->setString(CommonResource::getStringFromInt(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_Central_UserData->battleMathingUseCount).c_str());
}

void CentralPVPMapUILayer::hide_component_Inbattle()
{
    l_seek_playergold->setVisible(false);
    b_next->setVisible(false);
    b_next->setTouchEnabled(false);
    b_cancel->setVisible(false);
    b_cancel->setTouchEnabled(false);
    b_end->setVisible(true);
    b_end->setTouchEnabled(true);
}

void CentralPVPMapUILayer::hide_component_Inend()
{
    l_mplayerCutTrophy->setVisible(false);
    l_mplayerAddTrophy->setVisible(false);
    l_mplayerPotions->setVisible(false);
    l_mplayerGold->setVisible(false);
    l_seek_playergold->setVisible(false);
    
    
    s_mplayerCutTrophy->setVisible(false);
    s_mplayerAddTrophy->setVisible(false);
    s_mplayerPotions->setVisible(false);
    s_mplayerGold->setVisible(false);
    
    b_next->setVisible(false);
    b_cancel->setVisible(false);
    b_end->setVisible(false);
    soldiersIcon_bg->setVisible(false);
}


void CentralPVPMapUILayer::change_battlestate(int state_)
{
    CentralLayer * mainlayer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    mainlayer->battle_state_ = (CentralLayer::BATTLE_STATE)state_;
    switch (mainlayer->battle_state_) {
        case CentralLayer::BATTLE_READY:
            
            break;
        case CentralLayer::BATTLE_IN:
        {
            SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->battle_state_ = CentralLayer::BATTLE_IN;
            SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->battleStartRequest();
            this->hide_component_Inbattle();
            
            SoundManage::GetSoundManageHandle()->_stopBackgroundMusic(true);
            SoundManage::GetSoundManageHandle()->_playBackgroundMusic("combat_music.mp3", true);
			

			// 战斗开始, 工人逃到主基地
            SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->AllWorkerRunAway();
        }
            break;
        case CentralLayer::BATTLE_END:
        {
            this->setTouchEnabled(false);
            b_cancel->setTouchEnabled(false);
            b_next->setTouchEnabled(false);
            
            SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->cleanBattle();
            
            //取消所有定时器，包括scheduleUpdate，不影响动作
            this->unscheduleAllSelectors();
            
            CentralLayer *LData = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
            CentralData *Ddata = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
            
            LData->battle_state_ = CentralLayer::BATTLE_END; // 切换到战斗结束状态
            
            // 战斗结束进行结算
            // 统计星星数量
            if(LData->battle_curbuildcount == LData->battle_loadbuildcount){
                LData->battle_star_count += 2;
            }
            else if (LData->battle_curbuildcount >= LData->battle_loadbuildcount/2) {
                LData->battle_star_count += 1;
            }
            
            if (LData->battle_star_count == 3) {
                SoundManage::GetSoundManageHandle()->_stopBackgroundMusic(true);
                SoundManage::GetSoundManageHandle()->_playBackgroundMusic("winwinwin.mp3", false);
            }else{
                SoundManage::GetSoundManageHandle()->_stopBackgroundMusic(true);
                SoundManage::GetSoundManageHandle()->_playBackgroundMusic("battle_lost_02.mp3", false);
            }
            
            // 有星星数量计算获取到的pvp分数
            Ddata->m_MatchPlayer->pvp_mark = ceilf(Ddata->m_MatchPlayer->pvp_mark*LData->battle_star_count*1.0f/3);
            
            // 获取金币和药水数量
            LData->battle_golden_count = 0;
            LData->battle_elixir_count = 0;
            CentralData::userMapData_t::iterator pos;
            for( pos = Ddata->m_M_UserMapData.begin(); pos != Ddata->m_M_UserMapData.end(); ++pos )
            {
                CentralData::M_UserMapData& obj = pos->second;
                if(obj.building_id == RESOURCE_GOLDMINE || obj.building_id == RESOURCE_GOLDSTORAGE){
                    LData->battle_golden_count += obj.cut_collect_count;
                }
                
                if (obj.building_id == RESOURCE_ELIXIRPUMP || obj.building_id == RESOURCE_ELIXIRSTORAGE) {
                    LData->battle_elixir_count += obj.cut_collect_count;
                }
                
                if (obj.building_id == BUILDINGTYPE_TOWNHALL) {
                    LData->battle_golden_count += obj.cut_collect_count;
                    LData->battle_elixir_count += obj.cut_elixir_count;
                }
            }
            
            // playerself 改变
            CentralData::Central_UserData* playerself = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_Central_UserData;
            
            // mathplayer 改变
            CentralData::MatchPlayer* mathplayer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_MatchPlayer;
            
            if(mathplayer->golden_count - LData->battle_golden_count < 0){
                LData->battle_golden_count = mathplayer->golden_count;
                mathplayer->golden_count = 0;
            }else{
                mathplayer->golden_count = mathplayer->golden_count - LData->battle_golden_count;
            }
            if(mathplayer->elixir_count - LData->battle_elixir_count < 0){
                LData->battle_elixir_count = mathplayer->elixir_count;
                mathplayer->elixir_count = 0;
            }else{
                mathplayer->elixir_count = mathplayer->elixir_count - LData->battle_elixir_count;
            }
            
            if (playerself->user_gold + LData->battle_golden_count >= playerself->user_goldMAX) {
                LData->battle_realgolden_count  = playerself->user_goldMAX - playerself->user_gold;
                playerself->user_gold = playerself->user_goldMAX;
            }else{
                LData->battle_realgolden_count = LData->battle_golden_count;
                playerself->user_gold = playerself->user_gold + LData->battle_golden_count;
            }
            if (playerself->user_potions + LData->battle_elixir_count >= playerself->user_potionsMAX){
                LData->battle_realelixir_count = playerself->user_potionsMAX - playerself->user_potions;
                playerself->user_potions = playerself->user_potionsMAX;
            }else{
                LData->battle_realelixir_count = LData->battle_elixir_count;
                playerself->user_potions = playerself->user_potions + LData->battle_elixir_count;
            }
            
            NetMessageManager::GetMessageManager()->m_pMessageRequest->SendUploadBattleResultRequest(                                                                                                        GameData::m_stUserData->gamecenter_id);
            
            
            // 隐藏界面上显示
            this->hide_component_Inend();
            // 加载结束界面
            CentralBattleEndUILayerLoader* centralBattleEndUILayerLoader = CentralBattleEndUILayerLoader::loader();
            SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralBattleEndUILayer = (CentralBattleEndUILayer*)SceneManage::GetSceneManageHendle()->m_pCentralScene->openTest(GAME_FILE_TRANSFORM("UI_Over",".ccbi").c_str(),"UI_Over",centralBattleEndUILayerLoader);
            
            CentralBattleEndUILayer* endlayer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralBattleEndUILayer;
            endlayer->show_component();
            SceneManage::GetSceneManageHendle()->m_pCentralScene->addChild(endlayer,2000);
            
            
            
			if (!NotNetworking)
            {				
                std::string fileName = *SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_MatchPlayer->gameCenterID;
                fileName.append(1, '_');
                fileName += GameData::m_stUserData->gamecenter_id;
                fileName.append(1, '_');
                fileName += CommonResource::getStringFromInt(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_BattleStartResponseData.battleId);
                fileName.append(".data");
                
                BattleRecorde::sharedBattleRecorde()->EndRecorde(fileName.c_str());
                
                SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_battleReplayFiles.push_back(fileName);
            }
        }
            break;
        default:
            break;
    }
}

void CentralPVPMapUILayer::onCancel(cocos2d::CCObject * pSender)
{
    if(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->battle_state_ == CentralLayer::BATTLE_READY || (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->battle_state_ == CentralLayer::BATTLE_IN && SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->battle_addpeoplecount == 0)){
        

        NetMessageManager::GetMessageManager()->m_pMessageRequest->SendCancleBattleRequest(GameData::m_stUserData->gamecenter_id);
        
        this->unscheduleAllSelectors();
        SceneManage::GetSceneManageHendle()->m_pCentralScene->LoadSceneLayer(CENTRALVIEW_SELF);
        ChangeLayer::ShowChangeLayer(SceneManage::GetSceneManageHendle()->m_pCentralScene);
    }
}

void CentralPVPMapUILayer::onNext(cocos2d::CCObject * pSender)
{
    CentralData *data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    // 判定钱是否够匹配玩家
    if (data->m_Central_UserData->user_gold - data->m_Central_UserData->battleMathingUseCount > 0 || NotNetworking) {
        data->m_Central_UserData->user_gold = data->m_Central_UserData->user_gold - data->m_Central_UserData->battleMathingUseCount;
        data->CleanBattleData();
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

void CentralPVPMapUILayer::onEnd(cocos2d::CCObject * pSender)
{
    // 添加确认对话框
    DialogLayer* dia = DialogLayer::create();
    dia->setPosition(ccp(0,0));
    this->addChild(dia,1000,10000);
    
    dia->setMenuItem(this,menu_selector(CentralPVPMapUILayer::cancelMenuItemInBattleCallback), menu_selector(CentralPVPMapUILayer::okMenuItemInBattleCallback));
    dia->setContentString("确定离开战斗?");
}

void CentralPVPMapUILayer::okMenuItemInBattleCallback(CCObject *pSender)
{
    this->change_battlestate(CentralLayer::BATTLE_END);
    
    Log__("确定");
    CCNode* node = (CCNode*)pSender;
    DialogLayer* dia = (DialogLayer*)node->getParent()->getParent()->getParent();
    dia->removeFromParentAndCleanup(true);
}
void CentralPVPMapUILayer::cancelMenuItemInBattleCallback(CCObject *pSender)
{
    Log__("取消");
    CCNode* node = (CCNode*)pSender;
    DialogLayer* dia = (DialogLayer*)node->getParent()->getParent()->getParent();
    dia->removeFromParentAndCleanup(true);
}


void CentralPVPMapUILayer::update(float dt)
{
    if(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->battle_state_ == CentralLayer::BATTLE_READY){
        // 30s倒计时
        countdown_readytime -= dt;
        if (countdown_readytime <= 3.0f && isShowcountdown_3) {
            isShowcountdown_3 = false;
            showcountdown_3();
        }
        if (countdown_readytime > 0) {
            string str = CommonResource::getStringFromInt((int)(countdown_readytime)) + "s";
            l_countdown->setString(str.c_str());
        }else {
            this->change_battlestate(CentralLayer::BATTLE_IN);
        }
        // 提示
        l_tipHelp->setString("Tap or press andd Hold to deploy troops");
    }
    
    if(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->battle_state_ == CentralLayer::BATTLE_IN){
        l_tipHelp->removeFromParentAndCleanup(true);
        // 战斗倒计时
        {
            countdown_gametime -= dt;
            if (countdown_gametime > 0) {
                int time = (int)(countdown_gametime);
                int min = time/60;
                int sec = time - min*60;
                string str = CommonResource::getStringFromInt(min)+"m"+CommonResource::getStringFromInt(sec)+"s";
                l_countdown->setString(str.c_str());
                if (countdown_gametime <= 30) {
                    l_countdown->setColor(ccRED);
                }
            }else {
                this->change_battlestate(CentralLayer::BATTLE_END);
                return;
            }
            
            if(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->battle_currolecount == SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->battle_loadrolecount || SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->battle_curbuildcount == SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->battle_loadbuildcount){
                if(NotNetworking) return;
                this->change_battlestate(CentralLayer::BATTLE_END);
                return;
            }
        }
    }
    
    
    if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->battle_state_ == CentralLayer::BATTLE_END) {
        CentralLayer *LData = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
        CentralData *Ddata = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
        
        // 获取金币和药水数量
        LData->battle_golden_count = 0;
        LData->battle_elixir_count = 0;
        CentralData::userMapData_t::iterator pos;
        for( pos = Ddata->m_M_UserMapData.begin(); pos != Ddata->m_M_UserMapData.end(); ++pos )
        {
            CentralData::M_UserMapData& obj = pos->second;
            if(obj.building_id == RESOURCE_GOLDMINE || obj.building_id == RESOURCE_GOLDSTORAGE){
                LData->battle_golden_count += obj.cut_collect_count;
            }
            
            if (obj.building_id == RESOURCE_ELIXIRPUMP || obj.building_id == RESOURCE_ELIXIRSTORAGE) {
                LData->battle_elixir_count += obj.cut_collect_count;
            }
            
            if (obj.building_id == BUILDINGTYPE_TOWNHALL) {
                LData->battle_golden_count += obj.cut_collect_count;
                LData->battle_elixir_count += obj.cut_elixir_count;
            }
        }
        
        // playerself 改变
        CentralData::Central_UserData* playerself = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_Central_UserData;
        
        // mathplayer 改变
        CentralData::MatchPlayer* mathplayer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_MatchPlayer;
        
        if(mathplayer->golden_count - LData->battle_golden_count < 0){
            LData->battle_golden_count = mathplayer->golden_count;
            mathplayer->golden_count = 0;
        }else{
            mathplayer->golden_count = mathplayer->golden_count - LData->battle_golden_count;
        }
        if(mathplayer->elixir_count - LData->battle_elixir_count < 0){
            LData->battle_elixir_count = mathplayer->elixir_count;
            mathplayer->elixir_count = 0;
        }else{
            mathplayer->elixir_count = mathplayer->elixir_count - LData->battle_elixir_count;
        }
        
        if (playerself->user_gold + LData->battle_golden_count >= playerself->user_goldMAX) {
            LData->battle_realgolden_count  = playerself->user_goldMAX - playerself->user_gold;
            playerself->user_gold = playerself->user_goldMAX;
        }else{
            LData->battle_realgolden_count = LData->battle_golden_count;
            playerself->user_gold = playerself->user_gold + LData->battle_golden_count;
        }
        if (playerself->user_potions + LData->battle_elixir_count >= playerself->user_potionsMAX){
            LData->battle_realelixir_count = playerself->user_potionsMAX - playerself->user_potions;
            playerself->user_potions = playerself->user_potionsMAX;
        }else{
            LData->battle_realelixir_count = LData->battle_elixir_count;
            playerself->user_potions = playerself->user_potions + LData->battle_elixir_count;
        }
    }
    
    CentralLayer *LData = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    
    // mathplayer 改变
    CentralData::MatchPlayer* mathplayer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_MatchPlayer;
    
    if(mathplayer->golden_count - LData->battle_golden_count < 0){
        l_mplayerGold->setString(CommonResource::getStringFromInt(0).c_str());
    }else{
        l_mplayerGold->setString(CommonResource::getStringFromInt(mathplayer->golden_count - LData->battle_golden_count).c_str());
    }
    if(mathplayer->elixir_count - LData->battle_elixir_count < 0){
        l_mplayerPotions->setString(CommonResource::getStringFromInt(0).c_str());
    }else{
        l_mplayerPotions->setString(CommonResource::getStringFromInt(mathplayer->elixir_count - LData->battle_elixir_count).c_str());
    }
    
    // playerself 改变
    CentralData::Central_UserData* playerself = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_Central_UserData;
    
    if (playerself->user_gold + LData->battle_golden_count >= playerself->user_goldMAX) {
        l_gold->setString(CommonResource::getStringFromInt(playerself->user_goldMAX).c_str());
        s_gold->setScaleX(1.0f);
    }else{
        l_gold->setString(CommonResource::getStringFromInt(playerself->user_gold + LData->battle_golden_count).c_str());
        s_gold->setScaleX((playerself->user_gold + LData->battle_golden_count)*1.0f/playerself->user_goldMAX);
    }
    if (playerself->user_potions + LData->battle_elixir_count >= playerself->user_potionsMAX){
        l_potions->setString(CommonResource::getStringFromInt(playerself->user_potionsMAX).c_str());
        s_potions->setScaleX(1.0f);
    }else{
        l_potions->setString(CommonResource::getStringFromInt(playerself->user_potions + LData->battle_elixir_count).c_str());
        s_potions->setScaleX((playerself->user_potions + LData->battle_elixir_count)*1.0f/playerself->user_potionsMAX);
    }
    
    // 摧毁建筑百分比
    if (LData->battle_loadbuildcount != 0) {
        float overallDamage = LData->battle_curbuildcount*1.0f/LData->battle_loadbuildcount;
        int overdam = overallDamage*100;
        string mmm = CommonResource::getStringFromInt(overdam);
        mmm.append("%");
        l_overallDamage->setString(mmm.c_str());
        
        int starcount = 0;
        starcount = LData->battle_star_count;
        if(LData->battle_curbuildcount == LData->battle_loadbuildcount){
            starcount = 3;
        }
        else if (LData->battle_curbuildcount >= LData->battle_loadbuildcount/2) {
            starcount = 2;
        }
        if (starcount==1) {
            s_star_01->setVisible(true);
        }else if(starcount==2)
        {
            s_star_01->setVisible(true);
            s_star_02->setVisible(true);
        }else if(starcount==3){
            s_star_01->setVisible(true);
            s_star_02->setVisible(true);
            s_star_03->setVisible(true);
        }
    }
}

void CentralPVPMapUILayer::addAttackerSoldiersAndSpellList(vector<CentralData::AttackerSoldiersAndSpell*>* list)
{    
    for (int i=0; i<list->size(); i++) {
        CentralData::AttackerSoldiersAndSpell *obj = list->at(i);
        if (obj->used_type == 0) {
            CCMenuItemSprite* iconbg = (CCMenuItemSprite *)iconArr->objectAtIndex(i);
            
            char framename[256] = {0};
            sprintf(framename,"soldiers_Icon%d.png",obj->characterIdOrSpellId);
            
            IconSprite_CentralPVPMapUI* objIcon = (IconSprite_CentralPVPMapUI*)CCSprite::createWithSpriteFrameName(framename);
            objIcon->setScale(1.0f);
            objIcon->setPosition(ccp(iconbg->getContentSize().width/2,iconbg->getContentSize().height/2));
            objIcon->setTag(0);
            objIcon->iconID = obj->characterIdOrSpellId;
            iconbg->addChild(objIcon);
            
            CCLabelTTF* objLabel = CCLabelTTF::create(CommonResource::getStringFromInt(obj->count).c_str(), "Helvetica-Bold", 10);
            objLabel->setScale(2.0f);
            objLabel->setPosition(ccp(iconbg->getContentSize().width/2,iconbg->getContentSize().height));
            objLabel->setTag(10);
            iconbg->addChild(objLabel);
            
            if (i == 0) {
                selectUnit = iconbg;
                selectUnit->setPosition(ccp(selectUnit->getPositionX(),selectUnit->getPositionY()+CentralPVPMapUI_ICON_Y));
            }
            iconbg->setTag(i);
        }
    }
}

void CentralPVPMapUILayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
}

void CentralPVPMapUILayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
}

void CentralPVPMapUILayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
}

void CentralPVPMapUILayer::showcountdown_3()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    number = CCSprite::create(GAME_FILE_TRANSFORM("timing_3",".png").c_str());
    number->setPosition(ccp(size.width/2,size.height/2));
    number->setScale(6.0f);
    this->addChild(number);
    CCActionInterval *action3 = CCScaleTo::create(0.3f, 0.7f);
    CCActionInterval *action4 = CCScaleTo::create(0.15f, 1.0f);
    CCActionInterval *action35 = CCMoveTo::create(1.0f, number->getPosition());
    CCFiniteTimeAction* myseq = CCSequence::create(action3,action4,action35,NULL);
    number->runAction(myseq);
    numkl = 0;
    this->schedule(schedule_selector(CentralPVPMapUILayer::noNum),1.0f);
}

void CentralPVPMapUILayer::noNum()
{
    numkl++;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (numkl == 1) {
        this->removeChild(number, true);
        number = CCSprite::create(GAME_FILE_TRANSFORM("timing_2",".png").c_str());
        number->setPosition(ccp(size.width/2,size.height/2));
        number->setScale(6.0f);
        this->addChild(number);
	    CCActionInterval *action3 = CCScaleTo::create(0.3f, 0.7f);
        CCActionInterval *action4 = CCScaleTo::create(0.15f, 1.0f);
        CCActionInterval *action35 = CCMoveTo::create(1.0f, number->getPosition());
        CCFiniteTimeAction* myseq = CCSequence::create(action3,action4,action35,NULL);
        number->runAction(myseq);
	}else if (numkl == 2) {
		this->removeChild(number, true);
		number = CCSprite::create(GAME_FILE_TRANSFORM("timing_1",".png").c_str());
        number->setPosition(ccp(size.width/2,size.height/2));
        number->setScale(6.0f);
        this->addChild(number);
	    CCActionInterval *action3 = CCScaleTo::create(0.3f, 0.7f);
        CCActionInterval *action4 = CCScaleTo::create(0.15f, 1.0f);
        CCActionInterval *action35 = CCMoveTo::create(1.0f, number->getPosition());
        CCFiniteTimeAction* myseq = CCSequence::create(action3,action4,action35,NULL);
        number->runAction(myseq);
	}else if (numkl == 3){
		this->removeChild(number, true);
		number = CCSprite::create(GAME_FILE_TRANSFORM("timing_go",".png").c_str());
        number->setPosition(ccp(size.width/2,size.height/2));
        number->setScale(6.0f);
        this->addChild(number);
	    CCActionInterval *action3 = CCScaleTo::create(0.3f, 0.7f);
        CCActionInterval *action4 = CCScaleTo::create(0.15f, 1.0f);
        CCActionInterval *action5 = CCFadeOut::create(1.0f);
        CCFiniteTimeAction* myseq = CCSequence::create(action3,action4,action5,NULL);
		number->runAction(myseq);
	}else if(numkl == 4){
        this->unschedule(schedule_selector(CentralPVPMapUILayer::noNum));
		numkl=0;
	}
}
