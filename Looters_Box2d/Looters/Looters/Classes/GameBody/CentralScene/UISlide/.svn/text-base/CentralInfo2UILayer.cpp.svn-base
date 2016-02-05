//
//  CentralInfo2UILayer.cpp
//  Looters
//
//  Created by yisuode on 13-1-8.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CentralInfo2UILayer.h"
#include "cocos2d.h"
#include "GameControl.h"
#include "CommonResource.h"

USING_NS_CC;
USING_NS_CC_EXT;
#define tableViewW  330
#define tableViewH  45
CentralInfo2UILayer::CentralInfo2UILayer()
: s_info_icon1(NULL)
, s_info_bg1(NULL)
, s_info1(NULL)
, s_info_xian1(NULL)
, l_info1(NULL)
, l_info_name1(NULL)
, l_info_num1(NULL)
, s_info_icon2(NULL)
, s_info_bg2(NULL)
, s_info2(NULL)
, s_info_xian2(NULL)
, l_info2(NULL)
, l_info_name2(NULL)
, l_info_num2(NULL)
, s_info_icon3(NULL)
, s_info_bg3(NULL)
, s_info3(NULL)
, s_info_xian3(NULL)
, l_info3(NULL)
, l_info_name3(NULL)
, l_info_num3(NULL)
, l_buildName(NULL)
, l_bg(NULL)
, l_bg2(NULL)
, s_icon_bg(NULL)
, s_info_lbg1(NULL)
, s_info_lbg2(NULL)
, s_info_lbg3(NULL)
, s_updata_timebg(NULL)
, s_updata_hong(NULL)
, l_updata_timebiaoti(NULL)
, l_updata_time(NULL)
, l_updata_text(NULL)
, btn_updatalevel(NULL)
{

    spriteArr = CCArray::create();
    spriteArr->retain();
}

CentralInfo2UILayer::~CentralInfo2UILayer()
{
    spriteArr->release();
    CC_SAFE_RELEASE(s_info_icon1);
    CC_SAFE_RELEASE(s_info_bg1);
    CC_SAFE_RELEASE(s_info1);
    CC_SAFE_RELEASE(s_info_xian1);
    CC_SAFE_RELEASE(l_info1);
    CC_SAFE_RELEASE(l_info_name1);
    CC_SAFE_RELEASE(l_info_num1);
    
    CC_SAFE_RELEASE(s_info_icon2);
    CC_SAFE_RELEASE(s_info_bg2);
    CC_SAFE_RELEASE(s_info2);
    CC_SAFE_RELEASE(s_info_xian2);
    CC_SAFE_RELEASE(l_info2);
    CC_SAFE_RELEASE(l_info_name2);
    CC_SAFE_RELEASE(l_info_num2);
    
    CC_SAFE_RELEASE(s_info_icon3);
    CC_SAFE_RELEASE(s_info_bg3);
    CC_SAFE_RELEASE(s_info3);
    CC_SAFE_RELEASE(s_info_xian3);
    CC_SAFE_RELEASE(l_info3);
    CC_SAFE_RELEASE(l_info_name3);
    CC_SAFE_RELEASE(l_info_num3);
    
    CC_SAFE_RELEASE(s_info_lbg1);
    CC_SAFE_RELEASE(s_info_lbg2);
    CC_SAFE_RELEASE(s_info_lbg3);
    CC_SAFE_RELEASE(s_updata_timebg);
    CC_SAFE_RELEASE(s_updata_hong);
    CC_SAFE_RELEASE(l_updata_timebiaoti);
    CC_SAFE_RELEASE(l_updata_time);
    CC_SAFE_RELEASE(l_updata_text);
    CC_SAFE_RELEASE(btn_updatalevel);
    
}

bool CentralInfo2UILayer::init( void )
{
	if( !CCLayer::init() )
		return false;
    
    tableView = NULL;
    
    
    return true;
}

SEL_MenuHandler CentralInfo2UILayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget,CCString * pSelectorName){
    
    //Bind Menu Events，绑定一个menu，点击方法是press，以下同理
    
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "press",MainScene::press);
    
    return NULL;
    
}

SEL_CCControlHandler CentralInfo2UILayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName){
    
    //Bind CCControl Events
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClose",CentralInfo2UILayer::onClose);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onUpDataLevel",CentralInfo2UILayer::onUpDataLevel);
    
    return NULL;
    
}

bool CentralInfo2UILayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode){
    
    //Bind variables
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_icon_bg", CCSprite *, this->s_icon_bg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_icon1", CCSprite *, this->s_info_icon1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_bg1", CCSprite *, this->s_info_bg1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info1", CCSprite *, this->s_info1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_xian1", CCSprite *, this->s_info_xian1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info1", CCLabelTTF *, this->l_info1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_name1", CCLabelTTF *, this->l_info_name1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_num1", CCLabelTTF *, this->l_info_num1);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_icon2", CCSprite *, this->s_info_icon2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_bg2", CCSprite *, this->s_info_bg2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info2", CCSprite *, this->s_info2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_xian2", CCSprite *, this->s_info_xian2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info2", CCLabelTTF *, this->l_info2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_name2", CCLabelTTF *, this->l_info_name2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_num2", CCLabelTTF *, this->l_info_num2);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_icon3", CCSprite *, this->s_info_icon3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_bg3", CCSprite *, this->s_info_bg3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info3", CCSprite *, this->s_info3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_xian3", CCSprite *, this->s_info_xian3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info3", CCLabelTTF *, this->l_info3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_name3", CCLabelTTF *, this->l_info_name3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_num3", CCLabelTTF *, this->l_info_num3);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_buildName", CCLabelTTF *, this->l_buildName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_bg", CCLabelTTF *, this->l_bg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_bg2", CCLabelTTF *, this->l_bg2);
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_lbg1", CCSprite *, this->s_info_lbg1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_lbg2", CCSprite *, this->s_info_lbg2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_lbg3", CCSprite *, this->s_info_lbg3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_updata_timebg", CCSprite *, this->s_updata_timebg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_updata_hong", CCSprite *, this->s_updata_hong);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_updata_timebiaoti", CCLabelTTF *, this->l_updata_timebiaoti);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_updata_time", CCLabelTTF *, this->l_updata_time);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_updata_text", CCLabelTTF *, this->l_updata_text);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btn_updatalevel", CCControlButton *, this->btn_updatalevel);
    
    return false;
    
}


void CentralInfo2UILayer::onNodeLoaded(CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader){
    
    //检测scene
    
    CCLOG("MainScene loading.....successed!") ;
}


void CentralInfo2UILayer::onEnter()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
    
    CCNode::onEnter();
}

void CentralInfo2UILayer::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    CCNode::onExit();
}

bool CentralInfo2UILayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLOG("响应啦........................................");
    return true;
}

void CentralInfo2UILayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralInfo2UILayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralInfo2UILayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralInfo2UILayer::onUpDataLevel(cocos2d::CCObject * pSender)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    //等级上线
    if(pCentralScene->m_pCentralLayer->m_building->lv+1 > 6) return;
    
    if(pCentralScene->m_pCentralLayer->m_building->upgrade_state_ != UNIT_UPGRADE_NONE) return;
    
    const BaseBuildingLevelData* buildingBaseLevelData;
    buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( pCentralScene->m_pCentralLayer->m_building->getID()+1);
    bool isResource = true;
    
    if (buildingBaseLevelData!=NULL)
    {
        
        if (pCentralScene->m_pCentralLayer->MAXTownhall() >= buildingBaseLevelData->TownHallLevel)
        {
            
            BuildingBase* build = pCentralScene->m_pCentralLayer->NoBusy();
            if (build != NULL)
            {
                //金币
                if ("Gold" == string(buildingBaseLevelData->BuildResource))
                {
                    if (pCentralScene->m_pCentralData->m_Central_UserData->user_gold < buildingBaseLevelData->BuildCost)
                    {
                        pCentralScene->m_pCentralUILayer->addDialogLayer(true,buildingBaseLevelData->BuildCost-pCentralScene->m_pCentralData->m_Central_UserData->user_gold,1);
                        isResource = false;
                        onClose(NULL);
                        return;
                    }
                    else
                    {
                        pCentralScene->m_pCentralUILayer->updateGold(-buildingBaseLevelData->BuildCost);
                    }
                }
                //药水
                else if("Elixir" == string(buildingBaseLevelData->BuildResource))
                {
                    if (pCentralScene->m_pCentralData->m_Central_UserData->user_potions < buildingBaseLevelData->BuildCost)
                    {
                        pCentralScene->m_pCentralUILayer->addDialogLayer(false,buildingBaseLevelData->BuildCost-pCentralScene->m_pCentralData->m_Central_UserData->user_potions,1);
                        isResource = false;
                        onClose(NULL);
                        return;
                        
                    }
                    else
                    {
                        pCentralScene->m_pCentralUILayer->updatePotions(-buildingBaseLevelData->BuildCost);
                    }
                }
                //宝石
                else if("Diamonds" == string(buildingBaseLevelData->BuildResource))
                {
                    if (pCentralScene->m_pCentralData->m_Central_UserData->user_gem < buildingBaseLevelData->BuildCost)
                    {
                        isResource = false;
                    }
                    else
                    {
                        pCentralScene->m_pCentralUILayer->updateGem(-buildingBaseLevelData->BuildCost);
                    }
                }
                
                if (isResource)
                {
                    
                    pCentralScene->m_pCentralUILayer->InfoBtnDisappear(pCentralScene->m_pCentralLayer->m_building->upgrade_state_,pCentralScene->m_pCentralLayer->m_building->getTypeID());
                    
                    build->isBusy = true;
                    build->busyUUID = pCentralScene->m_pCentralLayer->m_building->getuuID();
                    pCentralScene->m_pCentralLayer->m_building->m_iBuildCDTime = buildingBaseLevelData->BuildTimeD*24*60*60+ buildingBaseLevelData->BuildTimeH*60*60 +buildingBaseLevelData->BuildTimeM*60;
                    pCentralScene->m_pCentralLayer->m_building->upgrade_state_ = UNIT_UPGRADE_START;
                    pCentralScene->m_pCentralUILayer->A_time = 0;
                    pCentralScene->m_pCentralUILayer->is_A = true;
                    
					pCentralScene->m_pCentralLayer->SendAWorker(build, pCentralScene->m_pCentralLayer->m_building);
                    
                    onClose(NULL);
                }
                
            }
            else
            {
                pCentralScene->m_pCentralUILayer->addDialogLayer(true,0,2);
                onClose(NULL);
            }
            
            
        }
    }

}
void CentralInfo2UILayer::onClose(cocos2d::CCObject * pSender)
{
    this->removeFromParentAndCleanup(false);
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    pCentralScene->m_pCentralInfo2UILayer = NULL;
    
}

void CentralInfo2UILayer::updata(float _time)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    if (pCentralScene->m_pCentralLayer->m_building != NULL)
    {
        int tyep = pCentralScene->m_pCentralLayer->m_building->getTypeID();
        if (tyep == RESOURCE_ELIXIRPUMP || tyep == RESOURCE_GOLDMINE) 
        {
            updataResources();
        }
    }
}


void CentralInfo2UILayer::updataResources()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    if (pCentralScene->m_pCentralLayer->m_building != NULL)
    {
        int tyep = pCentralScene->m_pCentralLayer->m_building->getTypeID();
        if (tyep == RESOURCE_ELIXIRPUMP) 
        {
            char strP[256] = {0};
            sprintf(strP,"粮食:%d/%d",pCentralScene->m_pCentralLayer->m_building->resourcesPotionsNum,pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum);
            l_info1->setString(strP);
            
            float flP =  (float)pCentralScene->m_pCentralLayer->m_building->resourcesPotionsNum/pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum;
            s_info1->setScaleX(flP);
        }
        else if(tyep == RESOURCE_GOLDMINE)
        {
            char strG[256] = {0};
            sprintf(strG,"金币:%d/%d",pCentralScene->m_pCentralLayer->m_building->resourcesGoldNum,pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum);
            l_info1->setString(strG);

            float flG =  (float)pCentralScene->m_pCentralLayer->m_building->resourcesGoldNum/pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum;
            s_info1->setScaleX(flG);
        }
    }
}
void CentralInfo2UILayer::allinfoUINo()
{
    s_icon_bg->setVisible(false);
    
    s_info_icon1->setVisible(false);
    s_info_bg1->setVisible(false);
    s_info1->setVisible(false);
    
    s_info_icon2->setVisible(false);
    s_info_bg2->setVisible(false);
    s_info2->setVisible(false);
    
    s_info_icon3->setVisible(false);
    s_info_bg3->setVisible(false);
    s_info3->setVisible(false);
    
    s_info_xian1->setVisible(false);
    s_info_xian2->setVisible(false);
    s_info_xian3->setVisible(false);
    
    //
    s_info_lbg1->setVisible(false);
    s_info_lbg2->setVisible(false);
    s_info_lbg3->setVisible(false);
    s_updata_timebg->setVisible(false);
    s_updata_hong->setVisible(false);
    
    
    
    //文字
    
    l_buildName->setVisible(false);
    
    l_info1->setVisible(false);
    l_info2->setVisible(false);
    l_info3->setVisible(false);
    
    l_bg->setVisible(false);
    
    
    l_info_name1->setVisible(false);
    l_info_name2->setVisible(false);
    l_info_name3->setVisible(false);
    l_info_num1->setVisible(false);
    l_info_num2->setVisible(false);
    l_info_num3->setVisible(false);
    l_bg2->setVisible(false);
    
    //升级界面
    l_updata_timebiaoti->setVisible(false);
    l_updata_time->setVisible(false);
    l_updata_text->setVisible(false);
    
    
    btn_updatalevel->setVisible(false);
    
    
    btn_updatalevel->setTouchEnabled(false);
}
void CentralInfo2UILayer::updataUILayer()
{
    allinfoUINo();
    
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    if (pCentralScene->m_pCentralLayer->m_building != NULL)
    {
        int tyep = pCentralScene->m_pCentralLayer->m_building->getTypeID();
        int level = pCentralScene->m_pCentralLayer->m_building->lv;
        const BaseBuildingLevelData* buildingBaseLevelData;
        buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( tyep*100+level);
        const BaseBuildingLevelData* buildingBaseLevelDataUp;
        buildingBaseLevelDataUp = GameData::GetDataFromBaseBuildingLevelData( tyep*100+level+1);
        
        
        s_icon_bg->setVisible(true);
        
        
        
        char strHp[256] = {0};
        sprintf(strHp,"血量:%d/%d",pCentralScene->m_pCentralLayer->m_building->hp,pCentralScene->m_pCentralLayer->m_building->hp);
        
        
        const string* name = GameData::GetTextInfo(buildingBaseLevelData->Text);
        
        char framename[256] = {0};
        if (pCentralScene->m_pCentralLayer->m_building->getTypeID() == BUILDINGTYPE_WORKER)
        {
            sprintf(framename,"%s",name->c_str());
            //            sprintf(framename,"%s",buildingBaseLevelData->Name.c_str());
        }
        else
        {
            sprintf(framename,"%s(level%d)",name->c_str(),pCentralScene->m_pCentralLayer->m_building->lv);
            //            sprintf(framename,"%s(level%d)",buildingBaseLevelData->Name.c_str(),pCentralScene->m_pCentralLayer->m_building->lv);
        }
        
        l_buildName->setString(framename);
        
        CCSprite* build = CCSprite::create(GAME_FILE_TRANSFORM(buildingBaseLevelDataUp->ExportName.c_str(),".png").c_str());
        
        build->setPosition(ccpAdd(s_icon_bg->getPosition(), ccp(0, 0)) );
        this->addChild(build);
        
        //升级信息
        btn_updatalevel->setTouchEnabled(true);
        btn_updatalevel->setVisible(true);
        
        updatalevelGHui = CCSprite::createWithSpriteFrameName("ui_info_btn_gHui.png");
        updatalevelGHui->setVisible(false);
        updatalevelGHui->setAnchorPoint(ccp(0, 0));
        updatalevelGHui->setPosition(ccp(0, 0));
        btn_updatalevel->addChild(updatalevelGHui);
        
        updatalevelP = CCSprite::createWithSpriteFrameName("ui_info_btn_p.png");
        updatalevelP->setVisible(false);
        updatalevelP->setAnchorPoint(ccp(0, 0));
        updatalevelP->setPosition(ccp(0, 0));
        btn_updatalevel->addChild(updatalevelP);
        
        updatalevelPHui = CCSprite::createWithSpriteFrameName("ui_info_btn_pHui.png");
        updatalevelPHui->setVisible(false);
        updatalevelPHui->setAnchorPoint(ccp(0, 0));
        updatalevelPHui->setPosition(ccp(0, 0));
        btn_updatalevel->addChild(updatalevelPHui);
        
        resourcesNumLabel = CCLabelTTF::create("", "Helvetica", 12);
        resourcesNumLabel->setAnchorPoint(ccp(0,0));
        resourcesNumLabel->setPosition(ccp(10,20));
        btn_updatalevel->addChild(resourcesNumLabel);
        
        
        const BaseBuildingLevelData* buildingBaseLevelData2;
        buildingBaseLevelData2 = GameData::GetDataFromBaseBuildingLevelData( pCentralScene->m_pCentralLayer->m_building->getID()+1);
        bool isTownHall = false;
        if (pCentralScene->m_pCentralLayer->MAXTownhall() >= buildingBaseLevelData2->TownHallLevel)
        {
            isTownHall = true;
        }
        else
        {
            char updata_text[256] = {0};
            sprintf(updata_text,"需要%d级主基地",buildingBaseLevelData2->TownHallLevel);
            l_updata_text->setString(updata_text);
            l_updata_text->setVisible(true);

            s_updata_hong->setVisible(true);
        }
        
        
        
        
        
        bool isResource = true;
        if (buildingBaseLevelData2!=NULL)
        {
            
            //金币
            if ("Gold" == string(buildingBaseLevelData2->BuildResource))
            {
                if (!isTownHall)
                {
                    updatalevelGHui->setVisible(true);
                }
                
                if (pCentralScene->m_pCentralData->m_Central_UserData->user_gold < buildingBaseLevelData2->BuildCost)
                {
                    isResource = false;
                }
            }
            //药水
            else if("Elixir" == string(buildingBaseLevelData2->BuildResource))
            {
                if (pCentralScene->m_pCentralData->m_Central_UserData->user_potions < buildingBaseLevelData2->BuildCost)
                {
                    isResource = false;
                    updatalevelP->setVisible(true);
                }
                else
                {
                    updatalevelP->setVisible(true);
                }
                
                if (!isTownHall)
                {
                    updatalevelPHui->setVisible(true);
                }
            }
            
            
            resourcesNumLabel->setString(CommonResource::getStringFromInt(buildingBaseLevelData2->BuildCost).c_str());
            
            if (isResource)
            {
                resourcesNumLabel->setColor(ccWHITE);
            }
            else
            {
                resourcesNumLabel->setColor(ccRED);
            }
        }
        
        
        l_updata_timebiaoti->setVisible(true);
        char updata_time[256] = {0};
        if (buildingBaseLevelData2->BuildTimeD > 0)
        {
            sprintf(updata_time,"%dd",buildingBaseLevelData2->BuildTimeD);
        }
        else if (buildingBaseLevelData2->BuildTimeH > 0)
        {
            sprintf(updata_time,"%dh",buildingBaseLevelData2->BuildTimeH);
        }
        else if (buildingBaseLevelData2->BuildTimeM > 0)
        {
            sprintf(updata_time,"%dm",buildingBaseLevelData2->BuildTimeM);
        }
        l_updata_time->setString(updata_time);
        l_updata_time->setVisible(true);
        s_updata_timebg->setVisible(true);
        
        
        switch (tyep)
        {
            case ARMY_BARRACK:
            case ARMY_LABORATORY:
            case BUILDINGTYPE_WALL:
            case BUILDINGTYPE_WORKER:
            {
                
                //只有血量.
                
                l_info1->setString(strHp);
                l_info1->setVisible(true);
                s_info_icon1->setVisible(true);
                s_info_bg1->setVisible(true);
                s_info1->setVisible(true);
                s_info_lbg1->setVisible(true);
                
                
                
                
            }
                break;
            case BUILDINGTYPE_TOWNHALL:
            {
                //有存储水 有存储钱 有血量
                
                
                CCSprite* iconP = CCSprite::createWithSpriteFrameName("ui_info_icon_p1.png");
                iconP->setPosition(s_info_icon1->getPosition());
                this->addChild(iconP);
                
                char strP[256] = {0};
                sprintf(strP,"粮食:%d/%d",pCentralScene->m_pCentralLayer->m_building->resourcesPotionsNum,pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum);
                l_info1->setString(strP);
                l_info1->setVisible(true);
                //s_info_icon1->setVisible(true);
                s_info_bg1->setVisible(true);
                float flP =  (float)pCentralScene->m_pCentralLayer->m_building->resourcesPotionsNum/pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum;
                s_info1->setScaleX(flP);
                s_info1->setVisible(true);
                
                CCSprite* iconG = CCSprite::createWithSpriteFrameName("ui_info_icon_g1.png");
                iconG->setPosition(s_info_icon2->getPosition());
                this->addChild(iconG);
                
                char strG[256] = {0};
                sprintf(strG,"金币:%d/%d",pCentralScene->m_pCentralLayer->m_building->resourcesGoldNum,pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum);
                l_info2->setString(strG);
                l_info2->setVisible(true);
                s_info_bg2->setVisible(true);
                
                float flG =  (float)pCentralScene->m_pCentralLayer->m_building->resourcesGoldNum/pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum;
                s_info2->setScaleX(flG);
                s_info2->setVisible(true);
                
                
                l_info3->setString(strHp);
                l_info3->setVisible(true);
                s_info_icon3->setVisible(true);
                s_info_bg3->setVisible(true);
                s_info3->setVisible(true);
                
                
                s_info_lbg1->setVisible(true);
                s_info_lbg2->setVisible(true);
                s_info_lbg3->setVisible(true);
            }
                break;
            case RESOURCE_ELIXIRPUMP:
            {
                //有存储水 有生产水速度 有血量
                
                CCSprite* iconP = CCSprite::createWithSpriteFrameName("ui_info_icon_p1.png");
                iconP->setPosition(s_info_icon1->getPosition());
                this->addChild(iconP);
                
                
                l_info1->setVisible(true);
                s_info_bg1->setVisible(true);
                s_info1->setVisible(true);
                
                
                CCSprite* iconP2 = CCSprite::createWithSpriteFrameName("ui_info_icon_p2.png");
                iconP2->setPosition(s_info_icon2->getPosition());
                this->addChild(iconP2);
                char strPS[256] = {0};
                sprintf(strPS,"生产速度:%d每小时",pCentralScene->m_pCentralLayer->m_building->resourcesCDNum);
                l_info2->setString(strPS);
                l_info2->setVisible(true);
                s_info_bg2->setVisible(true);
                
                float flP =  (float)pCentralScene->m_pCentralLayer->m_building->resourcesCDNum/3000;
                s_info2->setScaleX(flP);
                s_info2->setVisible(true);
                
                l_info3->setString(strHp);
                l_info3->setVisible(true);
                s_info_icon3->setVisible(true);
                s_info_bg3->setVisible(true);
                s_info3->setVisible(true);
                
                
                
                
                s_info_lbg1->setVisible(true);
                s_info_lbg2->setVisible(true);
                s_info_lbg3->setVisible(true);
            }
                break;
            case RESOURCE_ELIXIRSTORAGE:
            {
                //有存储水 有血量
                
                CCSprite* iconP = CCSprite::createWithSpriteFrameName("ui_info_icon_p1.png");
                iconP->setPosition(s_info_icon1->getPosition());
                this->addChild(iconP);
                
                char strP[256] = {0};
                sprintf(strP,"粮食:%d/%d",pCentralScene->m_pCentralLayer->m_building->resourcesPotionsNum,pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum);
                l_info1->setString(strP);
                l_info1->setVisible(true);
                s_info_bg1->setVisible(true);
                float flP =  (float)pCentralScene->m_pCentralLayer->m_building->resourcesPotionsNum/pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum;
                s_info1->setScaleX(flP);
                s_info1->setVisible(true);
                
                l_info2->setString(strHp);
                l_info2->setVisible(true);
                s_info_icon2->setVisible(true);
                s_info_bg2->setVisible(true);
                s_info2->setVisible(true);
                
                
                s_info_lbg1->setVisible(true);
                s_info_lbg2->setVisible(true);
                
            }
                break;
            case RESOURCE_GOLDMINE:
            {
                //有存储钱 有生产钱速度 有血量
                
                CCSprite* iconP = CCSprite::createWithSpriteFrameName("ui_info_icon_g1.png");
                iconP->setPosition(s_info_icon1->getPosition());
                this->addChild(iconP);
                
                
                l_info1->setVisible(true);
                s_info_bg1->setVisible(true);
                s_info1->setVisible(true);
                
                
                CCSprite* iconP2 = CCSprite::createWithSpriteFrameName("ui_info_icon_g2.png");
                iconP2->setPosition(s_info_icon2->getPosition());
                this->addChild(iconP2);
                char strGS[256] = {0};
                sprintf(strGS,"生产速度:%d每小时",pCentralScene->m_pCentralLayer->m_building->resourcesCDNum);
                l_info2->setString(strGS);
                l_info2->setVisible(true);
                s_info_bg2->setVisible(true);
                
                float flG =  (float)pCentralScene->m_pCentralLayer->m_building->resourcesCDNum/3000;
                s_info2->setScaleX(flG);
                s_info2->setVisible(true);
                
                l_info3->setString(strHp);
                l_info3->setVisible(true);
                s_info_icon3->setVisible(true);
                s_info_bg3->setVisible(true);
                s_info3->setVisible(true);
                
                
                s_info_lbg1->setVisible(true);
                s_info_lbg2->setVisible(true);
                s_info_lbg3->setVisible(true);
            }
                break;
            case RESOURCE_GOLDSTORAGE:
            {
                //有存储钱 有血量
                
                CCSprite* iconP = CCSprite::createWithSpriteFrameName("ui_info_icon_g1.png");
                iconP->setPosition(s_info_icon1->getPosition());
                this->addChild(iconP);
                
                char strG[256] = {0};
                sprintf(strG,"金币:%d/%d",pCentralScene->m_pCentralLayer->m_building->resourcesGoldNum,pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum);
                l_info1->setString(strG);
                l_info1->setVisible(true);
                s_info_bg1->setVisible(true);
                float flG =  (float)pCentralScene->m_pCentralLayer->m_building->resourcesGoldNum/pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum;
                s_info1->setScaleX(flG);
                s_info1->setVisible(true);
                
                l_info2->setString(strHp);
                l_info2->setVisible(true);
                s_info_icon2->setVisible(true);
                s_info_bg2->setVisible(true);
                s_info2->setVisible(true);
                
                
                s_info_lbg1->setVisible(true);
                s_info_lbg2->setVisible(true);
                
            }
                break;
                
            case DEFENSE_CANNON:
            case DEFENSE_ARCHERTOWER:
            case DEFENSE_WIZARDTOWER:
            case DEFENSE_AIRDEFENSE:
            case DEFENSE_MORTAR:
            case DEFENSE_TESLATOWER:
            {
                //有攻击力 有血量 描述攻击信息
                
                CCSprite* iconP = CCSprite::createWithSpriteFrameName("ui_info_icon_a.png");
                iconP->setPosition(s_info_icon1->getPosition());
                this->addChild(iconP);
                
                char strG[256] = {0};
                sprintf(strG,"攻击力:%d",pCentralScene->m_pCentralLayer->m_building->Damage);
                l_info1->setString(strG);
                l_info1->setVisible(true);
                s_info_bg1->setVisible(true);
                
                
                
                int maxDamage = 1;
                if (tyep == DEFENSE_CANNON)
                {
                    maxDamage = 75;
                }
                else if(tyep == DEFENSE_ARCHERTOWER)
                {
                    maxDamage = 65;
                }
                else if(tyep == DEFENSE_WIZARDTOWER)
                {
                    maxDamage = 40;
                }
                else if(tyep == DEFENSE_AIRDEFENSE)
                {
                    maxDamage = 230;
                }
                else if(tyep == DEFENSE_MORTAR)
                {
                    maxDamage = 11;
                }
                else if(tyep == DEFENSE_TESLATOWER)
                {
                    maxDamage = 75;
                }
                
                
                float flG =  (float)pCentralScene->m_pCentralLayer->m_building->Damage/maxDamage;
                CCLOG("%fd",flG);
                s_info1->setScaleX(flG);
                s_info1->setVisible(true);
                
                
                
                l_info2->setString(strHp);
                l_info2->setVisible(true);
                s_info_icon2->setVisible(true);
                s_info_bg2->setVisible(true);
                s_info2->setVisible(true);
                
                
                s_info_xian1->setVisible(true);
                s_info_xian2->setVisible(true);
                s_info_xian3->setVisible(true);
                
                
                l_info_name1->setString("攻击范围:");
                l_info_name2->setString("攻击类型:");
                l_info_name3->setString("攻击对象:");
                
                l_info_name1->setVisible(true);
                l_info_name2->setVisible(true);
                l_info_name3->setVisible(true);
                
                char strnum1[256] = {0};
                
                
                
                if (buildingBaseLevelData->MinAttackRange > 0)
                {
                    sprintf(strnum1,"%d-%d格",buildingBaseLevelData->MinAttackRange/100,buildingBaseLevelData->AttackRange/100);
                }
                else
                {
                    sprintf(strnum1,"%d格",buildingBaseLevelData->AttackRange/100);
                }
                
                l_info_num1->setString(strnum1);
                
                if (buildingBaseLevelData->DamageRadius > 0)
                {
                    l_info_num2->setString("范围伤害");
                }
                else
                {
                    l_info_num2->setString("单体攻击");
                }
                
                
                
                if (buildingBaseLevelData->AirTargets && buildingBaseLevelData->GroundTargets)
                {
                    l_info_num3->setString("空中&地面");
                }
                else if (buildingBaseLevelData->GroundTargets)
                {
                    l_info_num3->setString("地面");
                }
                else if (buildingBaseLevelData->AirTargets)
                {
                    l_info_num3->setString("空中");
                }
                
                l_info_num1->setVisible(true);
                l_info_num2->setVisible(true);
                l_info_num3->setVisible(true);
                
                
                
                
                s_info_lbg1->setVisible(true);
                s_info_lbg2->setVisible(true);
                s_info_lbg3->setVisible(true);
                
                
            }
                break;
            case ARMY_TROOPHOUSING:
            {
                
                
                
                l_info2->setString(strHp);
                l_info2->setVisible(true);
                s_info_icon2->setVisible(true);
                s_info_bg2->setVisible(true);
                s_info2->setVisible(true);
                
                int renkouNum = initTROOPHOUSING();
                addTableView();
                
                
                CCSprite* iconP = CCSprite::createWithSpriteFrameName("ui_info_icon_population.png");
                iconP->setPosition(s_info_icon1->getPosition());
                this->addChild(iconP);
                
                
                char strG[256] = {0};
                sprintf(strG,"人口:%d/%d",renkouNum,pCentralScene->m_pCentralData->m_Central_UserData->peopleNumMax);
                l_info1->setString(strG);
                l_info1->setVisible(true);
                s_info_bg1->setVisible(true);
                float flG =  (float)pCentralScene->m_pCentralData->m_Central_UserData->allPeopleNum/pCentralScene->m_pCentralData->m_Central_UserData->peopleNumMax;
                s_info1->setScaleX(flG);
                s_info1->setVisible(true);
                
                
                s_info_lbg1->setVisible(true);
                s_info_lbg2->setVisible(true);
            }
                break;
            default:
                break;
        }
        
        
    }
}
void CentralInfo2UILayer::infoUILayer()
{
    allinfoUINo();
    
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    if (pCentralScene->m_pCentralLayer->m_building != NULL)
    {
        int tyep = pCentralScene->m_pCentralLayer->m_building->getTypeID();
        int level = pCentralScene->m_pCentralLayer->m_building->lv;
        const BaseBuildingLevelData* buildingBaseLevelData;
        buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( tyep*100+level);
        
        
        
        s_icon_bg->setVisible(true);
        
        
        
        char strHp[256] = {0};
        sprintf(strHp,"血量:%d/%d",pCentralScene->m_pCentralLayer->m_building->hp,pCentralScene->m_pCentralLayer->m_building->hp);
        
        
        const string* name = GameData::GetTextInfo(buildingBaseLevelData->Text);
        
        char framename[256] = {0};
        if (pCentralScene->m_pCentralLayer->m_building->getTypeID() == BUILDINGTYPE_WORKER)
        {
            sprintf(framename,"%s",name->c_str());
//            sprintf(framename,"%s",buildingBaseLevelData->Name.c_str());
        }
        else
        {
            sprintf(framename,"%s(level%d)",name->c_str(),pCentralScene->m_pCentralLayer->m_building->lv);
//            sprintf(framename,"%s(level%d)",buildingBaseLevelData->Name.c_str(),pCentralScene->m_pCentralLayer->m_building->lv);
        }

        l_buildName->setString(framename);
        
        CCSprite* build = CCSprite::create(GAME_FILE_TRANSFORM(buildingBaseLevelData->ExportName.c_str(),".png").c_str());
        
        build->setPosition(ccpAdd(s_icon_bg->getPosition(), ccp(0, 0)) );
        this->addChild(build);
        
        switch (tyep)
        {
            case ARMY_BARRACK:
            case ARMY_LABORATORY:
            case BUILDINGTYPE_WALL:
            case BUILDINGTYPE_WORKER:
            {
                
                //只有血量.
                const string* textInfo = GameData::GetTextInfo(buildingBaseLevelData->TextInfo);
                l_bg->setString(textInfo->c_str());
                l_bg->setVisible(true);
                
                
                l_info1->setString(strHp);
                l_info1->setVisible(true);
                s_info_icon1->setVisible(true);
                s_info_bg1->setVisible(true);
                s_info1->setVisible(true);
                s_info_lbg1->setVisible(true);
                
                
                
                
            }
                break;
            case BUILDINGTYPE_TOWNHALL:
            {
                //有存储水 有存储钱 有血量
                const string* textInfo = GameData::GetTextInfo(buildingBaseLevelData->TextInfo);
                l_bg->setString(textInfo->c_str());
                l_bg->setVisible(true);
                
                
                CCSprite* iconP = CCSprite::createWithSpriteFrameName("ui_info_icon_p1.png");
                iconP->setPosition(s_info_icon1->getPosition());
                this->addChild(iconP);
                
                char strP[256] = {0};
                sprintf(strP,"粮食:%d/%d",pCentralScene->m_pCentralLayer->m_building->resourcesPotionsNum,pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum);
                l_info1->setString(strP);
                l_info1->setVisible(true);
                //s_info_icon1->setVisible(true);
                s_info_bg1->setVisible(true);
                float flP =  (float)pCentralScene->m_pCentralLayer->m_building->resourcesPotionsNum/pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum;
                s_info1->setScaleX(flP);
                s_info1->setVisible(true);
                
                CCSprite* iconG = CCSprite::createWithSpriteFrameName("ui_info_icon_g1.png");
                iconG->setPosition(s_info_icon2->getPosition());
                this->addChild(iconG);
                
                char strG[256] = {0};
                sprintf(strG,"金币:%d/%d",pCentralScene->m_pCentralLayer->m_building->resourcesGoldNum,pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum);
                l_info2->setString(strG);
                l_info2->setVisible(true);
                s_info_bg2->setVisible(true);
                
                float flG =  (float)pCentralScene->m_pCentralLayer->m_building->resourcesGoldNum/pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum;
                s_info2->setScaleX(flG);
                s_info2->setVisible(true);
                
                
                l_info3->setString(strHp);
                l_info3->setVisible(true);
                s_info_icon3->setVisible(true);
                s_info_bg3->setVisible(true);
                s_info3->setVisible(true);
                
                
                s_info_lbg1->setVisible(true);
                s_info_lbg2->setVisible(true);
                s_info_lbg3->setVisible(true);
            }
                break;
            case RESOURCE_ELIXIRPUMP:
            {
                //有存储水 有生产水速度 有血量
                const string* textInfo = GameData::GetTextInfo(buildingBaseLevelData->TextInfo);
                l_bg->setString(textInfo->c_str());
                l_bg->setVisible(true);  
                
                CCSprite* iconP = CCSprite::createWithSpriteFrameName("ui_info_icon_p1.png");
                iconP->setPosition(s_info_icon1->getPosition());
                this->addChild(iconP);
                

                l_info1->setVisible(true);
                s_info_bg1->setVisible(true);
                s_info1->setVisible(true);
                
                
                CCSprite* iconP2 = CCSprite::createWithSpriteFrameName("ui_info_icon_p2.png");
                iconP2->setPosition(s_info_icon2->getPosition());
                this->addChild(iconP2);
                char strPS[256] = {0};
                sprintf(strPS,"生产速度:%d每小时",pCentralScene->m_pCentralLayer->m_building->resourcesCDNum);
                l_info2->setString(strPS);
                l_info2->setVisible(true);
                s_info_bg2->setVisible(true);
                
                float flP =  (float)pCentralScene->m_pCentralLayer->m_building->resourcesCDNum/3000;
                s_info2->setScaleX(flP);
                s_info2->setVisible(true);
                
                l_info3->setString(strHp);
                l_info3->setVisible(true);
                s_info_icon3->setVisible(true);
                s_info_bg3->setVisible(true);
                s_info3->setVisible(true);
                
                
                
                
                s_info_lbg1->setVisible(true);
                s_info_lbg2->setVisible(true);
                s_info_lbg3->setVisible(true);
            }
                break;
            case RESOURCE_ELIXIRSTORAGE:
            {
                //有存储水 有血量
                const string* textInfo = GameData::GetTextInfo(buildingBaseLevelData->TextInfo);
                l_bg->setString(textInfo->c_str());
                l_bg->setVisible(true);
                
                CCSprite* iconP = CCSprite::createWithSpriteFrameName("ui_info_icon_p1.png");
                iconP->setPosition(s_info_icon1->getPosition());
                this->addChild(iconP);
                
                char strP[256] = {0};
                sprintf(strP,"粮食:%d/%d",pCentralScene->m_pCentralLayer->m_building->resourcesPotionsNum,pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum);
                l_info1->setString(strP);
                l_info1->setVisible(true);
                s_info_bg1->setVisible(true);
                float flP =  (float)pCentralScene->m_pCentralLayer->m_building->resourcesPotionsNum/pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum;
                s_info1->setScaleX(flP);
                s_info1->setVisible(true);
                
                l_info2->setString(strHp);
                l_info2->setVisible(true);
                s_info_icon2->setVisible(true);
                s_info_bg2->setVisible(true);
                s_info2->setVisible(true);
                
                
                s_info_lbg1->setVisible(true);
                s_info_lbg2->setVisible(true);
                
            }
                break;
            case RESOURCE_GOLDMINE:
            {
                //有存储钱 有生产钱速度 有血量
                const string* textInfo = GameData::GetTextInfo(buildingBaseLevelData->TextInfo);
                l_bg->setString(textInfo->c_str());
                l_bg->setVisible(true);  
                
                CCSprite* iconP = CCSprite::createWithSpriteFrameName("ui_info_icon_g1.png");
                iconP->setPosition(s_info_icon1->getPosition());
                this->addChild(iconP);
                

                l_info1->setVisible(true);
                s_info_bg1->setVisible(true);
                s_info1->setVisible(true);
                
                
                CCSprite* iconP2 = CCSprite::createWithSpriteFrameName("ui_info_icon_g2.png");
                iconP2->setPosition(s_info_icon2->getPosition());
                this->addChild(iconP2);
                char strGS[256] = {0};
                sprintf(strGS,"生产速度:%d每小时",pCentralScene->m_pCentralLayer->m_building->resourcesCDNum);
                l_info2->setString(strGS);
                l_info2->setVisible(true);
                s_info_bg2->setVisible(true);
                
                float flG =  (float)pCentralScene->m_pCentralLayer->m_building->resourcesCDNum/3000;
                s_info2->setScaleX(flG);
                s_info2->setVisible(true);
                
                l_info3->setString(strHp);
                l_info3->setVisible(true);
                s_info_icon3->setVisible(true);
                s_info_bg3->setVisible(true);
                s_info3->setVisible(true);
                
                
                s_info_lbg1->setVisible(true);
                s_info_lbg2->setVisible(true);
                s_info_lbg3->setVisible(true);
            }
                break;
            case RESOURCE_GOLDSTORAGE:
            {
                //有存储钱 有血量
                const string* textInfo = GameData::GetTextInfo(buildingBaseLevelData->TextInfo);
                l_bg->setString(textInfo->c_str());
                l_bg->setVisible(true);  
                
                CCSprite* iconP = CCSprite::createWithSpriteFrameName("ui_info_icon_g1.png");
                iconP->setPosition(s_info_icon1->getPosition());
                this->addChild(iconP);
                
                char strG[256] = {0};
                sprintf(strG,"金币:%d/%d",pCentralScene->m_pCentralLayer->m_building->resourcesGoldNum,pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum);
                l_info1->setString(strG);
                l_info1->setVisible(true);
                s_info_bg1->setVisible(true);
                float flG =  (float)pCentralScene->m_pCentralLayer->m_building->resourcesGoldNum/pCentralScene->m_pCentralLayer->m_building->resourcesMaxNum;
                s_info1->setScaleX(flG);
                s_info1->setVisible(true);
                
                l_info2->setString(strHp);
                l_info2->setVisible(true);
                s_info_icon2->setVisible(true);
                s_info_bg2->setVisible(true);
                s_info2->setVisible(true);
                
                
                s_info_lbg1->setVisible(true);
                s_info_lbg2->setVisible(true);
                
            }
                break;
                
            case DEFENSE_CANNON:
            case DEFENSE_ARCHERTOWER:
            case DEFENSE_WIZARDTOWER:
            case DEFENSE_AIRDEFENSE:
            case DEFENSE_MORTAR:
            case DEFENSE_TESLATOWER:
            {
                //有攻击力 有血量 描述攻击信息
                
                CCSprite* iconP = CCSprite::createWithSpriteFrameName("ui_info_icon_a.png");
                iconP->setPosition(s_info_icon1->getPosition());
                this->addChild(iconP);
                
                char strG[256] = {0};
                sprintf(strG,"攻击力:%d",pCentralScene->m_pCentralLayer->m_building->Damage);
                l_info1->setString(strG);
                l_info1->setVisible(true);
                s_info_bg1->setVisible(true);
                
                

                int maxDamage = 1;
                if (tyep == DEFENSE_CANNON)
                {
                    maxDamage = 75;
                }
                else if(tyep == DEFENSE_ARCHERTOWER)
                {
                    maxDamage = 65;
                }
                else if(tyep == DEFENSE_WIZARDTOWER)
                {
                    maxDamage = 40;
                }
                else if(tyep == DEFENSE_AIRDEFENSE)
                {
                    maxDamage = 230;
                }
                else if(tyep == DEFENSE_MORTAR)
                {
                    maxDamage = 11;
                }
                else if(tyep == DEFENSE_TESLATOWER)
                {
                    maxDamage = 75;
                }
                
                
                float flG =  (float)pCentralScene->m_pCentralLayer->m_building->Damage/maxDamage;
                CCLOG("%fd",flG);
                s_info1->setScaleX(flG);
                s_info1->setVisible(true);
                
                

                l_info2->setString(strHp);
                l_info2->setVisible(true);
                s_info_icon2->setVisible(true);
                s_info_bg2->setVisible(true);
                s_info2->setVisible(true);
                
                
                s_info_xian1->setVisible(true); 
                s_info_xian2->setVisible(true);
                s_info_xian3->setVisible(true);
                
                
                l_info_name1->setString("攻击范围:");
                l_info_name2->setString("攻击类型:");
                l_info_name3->setString("攻击对象:");
                
                l_info_name1->setVisible(true);
                l_info_name2->setVisible(true);
                l_info_name3->setVisible(true);
                
                char strnum1[256] = {0};

                
                
                if (buildingBaseLevelData->MinAttackRange > 0)
                {
                    sprintf(strnum1,"%d-%d格",buildingBaseLevelData->MinAttackRange/100,buildingBaseLevelData->AttackRange/100);
                }
                else
                {
                    sprintf(strnum1,"%d格",buildingBaseLevelData->AttackRange/100);
                }
                
                l_info_num1->setString(strnum1);
                
                if (buildingBaseLevelData->DamageRadius > 0)
                {
                    l_info_num2->setString("范围伤害");
                }
                else
                {
                    l_info_num2->setString("单体攻击");
                }
                


                if (buildingBaseLevelData->AirTargets && buildingBaseLevelData->GroundTargets)
                {
                    l_info_num3->setString("空中&地面");
                }
                else if (buildingBaseLevelData->GroundTargets)
                {
                    l_info_num3->setString("地面");
                }
                else if (buildingBaseLevelData->AirTargets)
                {
                    l_info_num3->setString("空中");
                }
                
                l_info_num1->setVisible(true);
                l_info_num2->setVisible(true);
                l_info_num3->setVisible(true);
                
                const string* textInfo = GameData::GetTextInfo(buildingBaseLevelData->TextInfo);
                l_bg2->setString(textInfo->c_str());
                l_bg2->setVisible(true);                
                
                
                
                s_info_lbg1->setVisible(true);
                s_info_lbg2->setVisible(true);
                s_info_lbg3->setVisible(true);
                
                
            }
                break;
            case ARMY_TROOPHOUSING:
            {
                const string* textInfo = GameData::GetTextInfo(buildingBaseLevelData->TextInfo);
                l_bg2->setString(textInfo->c_str());
                l_bg2->setVisible(true);
                
                
                
                l_info2->setString(strHp);
                l_info2->setVisible(true);
                s_info_icon2->setVisible(true);
                s_info_bg2->setVisible(true);
                s_info2->setVisible(true);
                
                int renkouNum = initTROOPHOUSING();
                addTableView();
                
                
                CCSprite* iconP = CCSprite::createWithSpriteFrameName("ui_info_icon_population.png");
                iconP->setPosition(s_info_icon1->getPosition());
                this->addChild(iconP);
                
                
                char strG[256] = {0};
                sprintf(strG,"人口:%d/%d",renkouNum,pCentralScene->m_pCentralData->m_Central_UserData->peopleNumMax);
                l_info1->setString(strG);
                l_info1->setVisible(true);
                s_info_bg1->setVisible(true);
                float flG =  (float)pCentralScene->m_pCentralData->m_Central_UserData->allPeopleNum/pCentralScene->m_pCentralData->m_Central_UserData->peopleNumMax;
                if (flG>1)
                {
                    flG = 1;
                }
                s_info1->setScaleX(flG);
                s_info1->setVisible(true);
                
                
                s_info_lbg1->setVisible(true);
                s_info_lbg2->setVisible(true);
            }
                break;
            default:
                break;
        }
        
        
    }
    
    
}

int CentralInfo2UILayer::initTROOPHOUSING()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GAME_FILE_TRANSFORM("soldiers_Icon",".plist").c_str(),GAME_FILE_TRANSFORM("soldiers_Icon",".png").c_str());
    CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    int m_l = 0;
    for (int i = 0; i < 10; i++)
    {
        int num = 0;
        int numArr = data->unit_list_->count();
        
        for (int k = 0; k <numArr; k++)
        {
            Unit *unit = (Unit*)data->unit_list_->objectAtIndex(k);
            //如果是建筑
            
            if (unit->is_unit_type(UT_ARMY_BUILD))
            {
                BuildingBase* build = (BuildingBase*)unit;
                if (build->getTypeID() == ARMY_TROOPHOUSING)
                {
                    for (int j=0; j<build->m_army.size(); j++)
                    {
                        Unit* role = build->m_army[j];
                        if (role->getTypeID() == (i+1)*1000)
                        {
                            const BasePeopleData* basePeopleData;
                            basePeopleData = GameData::GetDataFromBasePeopleData(role->getTypeID() *100 + role->lv);
                            m_l+= basePeopleData->HousingSpace;
                            num++;
                        }
                    }
                }
            }
        }
        
        
        if (num>0)
        {
            
            CCSprite* sprite =CCSprite::createWithSpriteFrameName("ui_public_bg3.png");
            sprite->setScale(0.5);
            char strFileName[64];
            sprintf(strFileName,"soldiers_Icon%d.png",i+1);
            //添加明图
            CCSprite* sprIcon = CCSprite::createWithSpriteFrameName(strFileName);
            sprIcon->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
            sprite->addChild(sprIcon);
            
            CCLabelTTF *timeLabel = CCLabelTTF::create(CommonResource::getStringFromInt(num).c_str(), "Helvetica", sprite->getContentSize().height/4);
            timeLabel->setAnchorPoint(ccp(0,1));
            timeLabel->setPosition(ccp(0, sprite->getContentSize().height));
            sprite->addChild(timeLabel,100,1);
            
            spriteArr->addObject(sprite);
        }
        
        
        
    }
    return m_l;
}


//列表

void CentralInfo2UILayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{    
    
    
}

CCSize CentralInfo2UILayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(50, tableViewH);
}

CCTableViewCell* CentralInfo2UILayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
   
    if (idx == 5)
    {
        CCLOG("--------------%d",idx);
    }
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        
        CCSprite* sprite =CCSprite::createWithSpriteFrameName("ui_public_bg1.png");
        sprite->setPosition(ccp(50/2,tableViewH/2));
        sprite->setScale(0.8);
        cell->addChild(sprite);
        
        if (spriteArr->count() > idx)
        {
            CCSprite *sprite3 = (CCSprite*)spriteArr->objectAtIndex(idx);
            sprite3->setPosition(ccp(50/2,tableViewH/2));
            sprite3->removeFromParentAndCleanup(false);
            cell->addChild(sprite3,2,2);
        }
        
    }
    else
    {
        cell->removeChildByTag(2, false);

        if (spriteArr->count() > idx)
        {
            CCSprite *sprite3 = (CCSprite*)spriteArr->objectAtIndex(idx);
            sprite3->setPosition(ccp(50/2,tableViewH/2));
            cell->addChild(sprite3,2,2);
        }
    
    }
    
    
    return cell;
}

unsigned int CentralInfo2UILayer::numberOfCellsInTableView(CCTableView *table)
{
    return 10;
}





void CentralInfo2UILayer::deleteTableView()
{
    if (tableView != NULL)
    {
        tableView->removeFromParentAndCleanup(false);
        tableView = NULL;
    }
    
}
void CentralInfo2UILayer::addTableView()
{    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    tableView = CCTableView::create(this, CCSizeMake(tableViewW, tableViewH));
    tableView->setDirection(kCCScrollViewDirectionHorizontal);
    tableView->setPosition(ccp(winSize.width/6+4,winSize.height/3));
    tableView->setDelegate(this);
    tableView->reloadData();
    
    this->addChild(tableView);
}