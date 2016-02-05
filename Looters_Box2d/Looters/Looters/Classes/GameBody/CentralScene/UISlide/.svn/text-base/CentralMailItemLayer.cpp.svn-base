//
//  CentralMailItemLayer.cpp
//  Looters
//
//  Created by 王 宁 on 13-1-7.
//
//

#include "CentralMailItemLayer.h"
#include <iostream>
#include "CentralMailUILayer.h"
#include "cocos2d.h"
#include "GameControl.h"
#include "CommonResource.h"
#include "TipInfo.h"
#include "ChangeLayer.h"
#include "NetMessageManager.h"
USING_NS_CC;
USING_NS_CC_EXT;

CentralMailItemLayer::CentralMailItemLayer()
: item_n_item(NULL)
, item_s_bg(NULL)
, item_s_win(NULL)
, item_s_lose(NULL)
, s_star_01(NULL)
, s_star_02(NULL)
, s_star_03(NULL)
, item_l_gold(NULL)
, item_l_shui(NULL)
, item_l_time(NULL)
, item_l_lv(NULL)
, item_l_playername(NULL)
, l_enemy_levelandpvp(NULL)
, item_b_replay(NULL)
, item_b_normalrevenge(NULL)
, item_b_depthrevenge(NULL)
{
}

CentralMailItemLayer::~CentralMailItemLayer()
{
    CC_SAFE_RELEASE(item_n_item);
    CC_SAFE_RELEASE(item_s_bg);
    CC_SAFE_RELEASE(item_s_win);
    CC_SAFE_RELEASE(item_s_lose);
    CC_SAFE_RELEASE(s_star_01);
    CC_SAFE_RELEASE(s_star_02);
    CC_SAFE_RELEASE(s_star_03);
    CC_SAFE_RELEASE(item_l_gold);
    CC_SAFE_RELEASE(item_l_shui);
    CC_SAFE_RELEASE(item_l_time);
    CC_SAFE_RELEASE(item_l_lv);
    CC_SAFE_RELEASE(item_l_playername);
    CC_SAFE_RELEASE(l_enemy_levelandpvp);
    CC_SAFE_RELEASE(item_b_replay);
    CC_SAFE_RELEASE(item_b_normalrevenge);
    CC_SAFE_RELEASE(item_b_depthrevenge);
}

bool CentralMailItemLayer::init( void )
{
	if( !CCLayer::init() )
		return false;
    this->setTouchEnabled(true);
    return true;
}

SEL_MenuHandler CentralMailItemLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget,CCString * pSelectorName){
    return NULL;
}

SEL_CCControlHandler CentralMailItemLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName){
    
    //Bind CCControl Events
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onReplay",CentralMailItemLayer::onReplay);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onNormalRevenge",CentralMailItemLayer::onNormalRevenge);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onDepthRevenge",CentralMailItemLayer::onDepthRevenge);
    return NULL;
    
}

bool CentralMailItemLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode){
    
    //Bind variables
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "item_n_item", CCNode *, this->item_n_item);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "item_s_bg", CCSprite *, this->item_s_bg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "item_s_win", CCSprite *, this->item_s_win);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "item_s_lose", CCSprite *, this->item_s_lose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_star_01", CCSprite *, this->s_star_01);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_star_02", CCSprite *, this->s_star_02);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_star_03", CCSprite *, this->s_star_03);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "item_l_gold", CCLabelTTF *, this->item_l_gold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "item_l_shui", CCLabelTTF *, this->item_l_shui);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "item_l_time", CCLabelTTF *, this->item_l_time);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "item_l_lv", CCLabelTTF *, this->item_l_lv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "item_l_playername", CCLabelTTF *, this->item_l_playername);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_enemy_levelandpvp", CCLabelTTF *, this->l_enemy_levelandpvp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "item_b_replay", CCControlButton *, this->item_b_replay);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "item_b_normalrevenge", CCControlButton *, this->item_b_normalrevenge);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "item_b_depthrevenge", CCControlButton *, this->item_b_depthrevenge);
    return false;
}


void CentralMailItemLayer::onNodeLoaded(CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader){
    
    //检测scene
    CCLOG("MainScene loading.....successed!") ;
}

void CentralMailItemLayer::onReplay(cocos2d::CCObject * pSender)
{
	SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_battleReplay = battleInfo.replyFileName;
	SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->battleInfo = battleInfo;
	
    string dc = CCFileUtils::sharedFileUtils()->getWriteablePath();
    dc.append(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_battleReplay);
    FILE *fp = fopen(dc.c_str(), "rb");
    
    if (fp != NULL) { // 临时处理
        SceneManage::GetSceneManageHendle()->m_pCentralScene->SetBattleMode(CENTRALVIEW_PVP,BATTLE_MODE_PVP_REPLAY);
        SceneManage::GetSceneManageHendle()->m_pCentralScene->LoadSceneLayer(CENTRALVIEW_BATTLE);
        SceneManage::GetSceneManageHendle()->m_pCentralScene->m_CentralBattleReplayUILayer->initBattleReplayUILayer();
    }
}

void CentralMailItemLayer::onNormalRevenge(cocos2d::CCObject * pSender)
{
    CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    bool flag = false;
    for (int i=0; i<data->m_BuildableSoldiers->size(); i++) {
        CentralData::BuildableSoldiers * s= data->m_BuildableSoldiers->at(i);
        if (s->num != 0) {
            flag = true;
            break;
        }
    }
    if (flag) {
        // 发送复仇请求 判定玩家处于保护状态、在线、被别人攻击状态
        NetMessageManager::GetMessageManager()->m_pMessageRequest->SendRevengeBattleRequest(GameData::m_stUserData->gamecenter_id, battleInfo.bowie_id);
        
        
//        SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_BattleInfo_PlayerID = battleInfo.bowie_id;
//        
//        SceneManage::GetSceneManageHendle()->m_pCentralScene->SetBattleMode(CENTRALVIEW_PVP, BATTLE_MODE_PVP_REVENGE);
//        SceneManage::GetSceneManageHendle()->m_pCentralScene->LoadSceneLayer(CENTRALVIEW_BATTLE);
    }else{
        if (!flag) {
            TipInfo *info = TipInfo::create();
            info->setString("没有兵可用!!!", ccp( item_s_bg->getContentSize().width/2, item_s_bg->getContentSize().height/2),2.0f);
            item_s_bg->addChild(info,10000);
        }
    }
}

void CentralMailItemLayer::onDepthRevenge(cocos2d::CCObject * pSender)
{
}

void CentralMailItemLayer::revengeBattleRequest_callback()
{
    SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_BattleInfo_PlayerID = battleInfo.bowie_id;
    
    SceneManage::GetSceneManageHendle()->m_pCentralScene->SetBattleMode(CENTRALVIEW_PVP, BATTLE_MODE_PVP_REVENGE);
    SceneManage::GetSceneManageHendle()->m_pCentralScene->LoadSceneLayer(CENTRALVIEW_BATTLE);
}

void CentralMailItemLayer::initMailItemUI(CentralData::BattleInfor info)
{
    battleInfo = info;
    // 金币 药水 时间
    item_l_gold->setString(CommonResource::getStringFromInt(info.attacker_get_golden_count).c_str());
    item_l_shui->setString(CommonResource::getStringFromInt(info.attacker_get_elixir_count).c_str());
    string str = info.attack_time.substr(5, 11);
    item_l_time->setString(str.c_str());
    item_l_lv->setString(CommonResource::getStringFromInt(info.attacker_level).c_str());
    item_l_playername->setString(info.attacker_nick_name.c_str());
    
    l_enemy_levelandpvp->setString(CommonResource::getStringFromInt(info.attacker_level).c_str());
    

    for (int i=0; i<battleInfo.attackerUsedList.size(); i++) {
        CentralData::AttackerUsed au = battleInfo.attackerUsedList.at(i);
        string str = "soldiers_Icon";
        str.append(CommonResource::getStringFromInt(au.used_id)).append(".png");
        CCSprite * sp = CCSprite::createWithSpriteFrameName(str.c_str());
        sp->setScale(0.5);
        sp->setPosition(ccp(30+38*i,60));
        
        CCLabelTTF * ll = CCLabelTTF::create(CommonResource::getStringFromInt(au.used_count).c_str(), "Marker Felt", 14);
        sp->addChild(ll);
        
        item_s_bg->addChild(sp);
    }
    
    if (battleInfo.star_count == 0) {
        item_s_win->setVisible(false);
        item_s_lose->setVisible(true);
    }else{
        item_s_win->setVisible(true);
        item_s_lose->setVisible(false);
    }
    
    if(battleInfo.star_count == 3){
        s_star_01->setVisible(true);
        s_star_02->setVisible(true);
        s_star_03->setVisible(true);
    }else if(battleInfo.star_count == 2){
        s_star_01->setVisible(true);
        s_star_02->setVisible(true);
    }else if(battleInfo.star_count == 1){
        s_star_01->setVisible(true);
    }
}
