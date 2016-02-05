

#include "CentralBattleReplayUILayer.h"
#include <iostream>
#include "cocos2d.h"
#include "GameControl.h"
#include "BattleReplay.h"
USING_NS_CC;
USING_NS_CC_EXT;

CentralBattleReplayUILayer::CentralBattleReplayUILayer():
s_destory_bg(NULL)
,s_star_01(NULL)
,s_star_02(NULL)
,s_star_03(NULL)
,l_overallDamage(NULL)
{
}

CentralBattleReplayUILayer::~CentralBattleReplayUILayer()
{
    CC_SAFE_RELEASE(s_destory_bg);
    CC_SAFE_RELEASE(s_star_01);
    CC_SAFE_RELEASE(s_star_02);
    CC_SAFE_RELEASE(s_star_03);
    CC_SAFE_RELEASE(l_overallDamage);
}

bool CentralBattleReplayUILayer::init( void )
{
	if( !CCLayer::init() )
		return false;

    return true;
}

SEL_MenuHandler CentralBattleReplayUILayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget,CCString * pSelectorName){
    
    return NULL;
}

SEL_CCControlHandler CentralBattleReplayUILayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName){
    
    //Bind CCControl Events
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onReturnHome",CentralBattleReplayUILayer::onReturnHome);
    return NULL;
}

bool CentralBattleReplayUILayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode){
    
    //Bind variables
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_destory_bg", CCSprite *, this->s_destory_bg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_star_01", CCSprite *, this->s_star_01);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_star_02", CCSprite *, this->s_star_02);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_star_03", CCSprite *, this->s_star_03);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_overallDamage", CCLabelTTF *, this->l_overallDamage);
    return false;
}


void CentralBattleReplayUILayer::onNodeLoaded(CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader){
    
    //检测scene
    CCLOG("MainScene loading.....successed!") ;
}

void CentralBattleReplayUILayer::onReturnHome(cocos2d::CCObject * pSender)
{
    BattleReplay::sharedBattleReplay()->EndReplay();
    SceneManage::GetSceneManageHendle()->m_pCentralScene->LoadSceneLayer(CENTRALVIEW_SELF);
}

void CentralBattleReplayUILayer::initBattleReplayUILayer()
{
    s_star_01->setVisible(false);
    s_star_02->setVisible(false);
    s_star_03->setVisible(false);
    
    l_overallDamage->setString("0%");
}


void CentralBattleReplayUILayer::update(float dt)
{
    CentralLayer *LData = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    
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