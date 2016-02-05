//
//  CentralInfoUILayer.cpp
//  Looters
//
//  Created by admin on 12-11-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "CentralInfoUILayer.h"
#include "BuildingBase.h"
#include "CommonResource.h"

CentralInfoUILayer::CentralInfoUILayer()
:s_bgl1(NULL)
,s_bgl2(NULL)
,s_bgl3(NULL)
,l_biaoti(NULL)
,l_tishi(NULL)


,l_info1(NULL)
,l_info2(NULL)
,l_info3(NULL)
,l_info_mubiao(NULL)
,l_info_leixing(NULL)
,l_info_duixiang(NULL)
,l_info_renkou(NULL)
,l_info_shijian(NULL)
,l_info_shudu(NULL)
,l_info_mubiaonum(NULL)
,l_info_leixingnum(NULL)
,l_info_duixiangnum(NULL)
,l_info_renkounum(NULL)
,l_info_shijiannum(NULL)
,l_info_shudunum(NULL)
,s_info_icon1(NULL)
,s_info_bg1(NULL)
,s_info1(NULL)
,s_info_lbg1(NULL)
,s_info_icon2(NULL)
,s_info_bg2(NULL)
,s_info2(NULL)
,s_info_lbg2(NULL)
,s_info_icon3(NULL)
,s_info_bg3(NULL)
,s_info3(NULL)
,s_info_lbg3(NULL)
,s_info_lbg(NULL)
,s_info_tubg(NULL)
,nextBtn(NULL)

,l_info_time(NULL)
,l_info_timebiaoti(NULL)
,s_info_timebg(NULL)
,updatalevel(NULL)
{
    iserJi = false;
}

CentralInfoUILayer::~CentralInfoUILayer()
{
    CC_SAFE_RELEASE(s_bgl1);
    CC_SAFE_RELEASE(s_bgl2);
    CC_SAFE_RELEASE(s_bgl3);
    CC_SAFE_RELEASE(l_biaoti);
    CC_SAFE_RELEASE(l_tishi);
    
    
    
    CC_SAFE_RELEASE(l_info1);
    CC_SAFE_RELEASE(l_info2);
    CC_SAFE_RELEASE(l_info3);
    CC_SAFE_RELEASE(l_info_mubiao);
    CC_SAFE_RELEASE(l_info_leixing);
    CC_SAFE_RELEASE(l_info_duixiang);
    CC_SAFE_RELEASE(l_info_renkou);
    CC_SAFE_RELEASE(l_info_shijian);
    CC_SAFE_RELEASE(l_info_shudu);
    CC_SAFE_RELEASE(l_info_mubiaonum);
    CC_SAFE_RELEASE(l_info_leixingnum);
    CC_SAFE_RELEASE(l_info_duixiangnum);
    CC_SAFE_RELEASE(l_info_renkounum);
    CC_SAFE_RELEASE(l_info_shijiannum);
    CC_SAFE_RELEASE(l_info_shudunum);
    CC_SAFE_RELEASE(s_info_icon1);
    CC_SAFE_RELEASE(s_info_bg1);
    CC_SAFE_RELEASE(s_info1);
    CC_SAFE_RELEASE(s_info_lbg1);
    CC_SAFE_RELEASE(s_info_icon2);
    CC_SAFE_RELEASE(s_info_bg2);
    CC_SAFE_RELEASE(s_info2);
    CC_SAFE_RELEASE(s_info_lbg2);
    CC_SAFE_RELEASE(s_info_icon3);
    CC_SAFE_RELEASE(s_info_bg3);
    CC_SAFE_RELEASE(s_info3);
    CC_SAFE_RELEASE(s_info_lbg3);
    CC_SAFE_RELEASE(s_info_lbg);
    CC_SAFE_RELEASE(s_info_tubg);
    CC_SAFE_RELEASE(nextBtn);
    
    
    CC_SAFE_RELEASE(l_info_time);
    CC_SAFE_RELEASE(l_info_timebiaoti);
    CC_SAFE_RELEASE(s_info_timebg);
    CC_SAFE_RELEASE(updatalevel);

}

bool CentralInfoUILayer::init( void )
{
	if( !CCLayer::init() )
		return false;
    m_type = 0;
    arrIcon = NULL;
    arrIconM = NULL;
    arrAIcon = NULL;
    m_Sprite = NULL;
    m_SpriteA = NULL;
    isBegan = false;
    isMroS = false;
    isaddbing = false;
    isjianbing = false;
    beganTime = 0;
    addbing_time = 0;
    jianbing_time = 0;
    return true;
}

void CentralInfoUILayer::onEnter()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
    
    CCNode::onEnter();
}

void CentralInfoUILayer::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    CCNode::onExit();
}

bool CentralInfoUILayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint touchLocation = pTouch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL( touchLocation );
    
    
    switch (m_type)
    {
        case ARMY_BARRACK:
        {
            int num = arrIcon->count();
            for (int i = 0; i < num; i++)
            {
                CCSprite* icon = (CCSprite*)arrIcon->objectAtIndex(i);
                
                if (inSpritePosition(icon,touchLocation))
                {
                    m_Sprite = icon;
                    CCSprite* temp = (CCSprite*) m_Sprite->getChildByTag(101);
                    if (temp != NULL)
                    {
                        CCPoint pos = m_Sprite->getPosition();
                        CCPoint anchor = m_Sprite->getAnchorPoint();
                        
                        CCRect r = CCRectMake(pos.x - m_Sprite->getTextureRect().size.width*anchor.x + (m_Sprite->getTextureRect().size.width - temp->getTextureRect().size.width),
                                              pos.y - m_Sprite->getTextureRect().size.height*anchor.y + (m_Sprite->getTextureRect().size.height - temp->getTextureRect().size.height),
                                              temp->getTextureRect().size.width,
                                              temp->getTextureRect().size.height);
                        
                        
                        if (r.origin.x<=touchLocation.x&&touchLocation.x<=r.origin.x+r.size.width&&
                            r.origin.y<=touchLocation.y&&touchLocation.y<=r.origin.y+r.size.height)
                        {
                            CCLOG("ssssssssssss");
                            arrNumS = i;
                            
                        }
                        else
                        {
                            addbing_time = 0;
                            isaddbing = true;
                            
                            m_Sprite = icon;
                            m_spriteNum = i+1;
                            isBegan = false;
                            beganTime = 0;
                        }
                    }
                }
            }
            
            num = arrAIcon->count();
            for (int i = 0; i < num; i++)
            {
                CCSprite* icon = (CCSprite*)arrAIcon->objectAtIndex(i);
                
                if (inSpritePosition(icon,touchLocation))
                {
                    jianbing_time = 0;
                    isjianbing = true;
                    
                    m_SpriteA = icon;
                    isBegan = false;
                    beganTime = 0;
                    
                }
                
            }
            
            
        }
            break;
        case ARMY_LABORATORY:
        {
            int num = arrIcon->count();
            for (int i = 0; i < num; i++)
            {
                CCSprite* icon = (CCSprite*)arrIcon->objectAtIndex(i);
                
                if (inSpritePosition(icon,touchLocation))
                {
                    arrNumS = i;
                    m_Sprite = icon;
                    m_spriteNum = i+1;
                    isMroS = false;
                }
                
            }
            num = arrIconM->count();
            for (int i = 0; i < num; i++)
            {
                CCSprite* icon = (CCSprite*)arrIconM->objectAtIndex(i);
                
                if (inSpritePosition(icon,touchLocation))
                {
                    m_Sprite = icon;
                    m_spriteNum = i+1;
                    isMroS = true;
                    
                }
                
            }
        }
            break;   
        case ARMY_SPELLFORGE:
        {
            int num = arrIcon->count();
            for (int i = 0; i < num; i++)
            {
                CCSprite* icon = (CCSprite*)arrIcon->objectAtIndex(i);
                
                if (inSpritePosition(icon,touchLocation))
                {
                    m_Sprite = icon;
                    m_spriteNum = i+1;
                    isMroS = false;
                }
                
            }
        }
            break;  
        default:
            break;
    }
    
    return true;
}

void CentralInfoUILayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    switch (m_type)
    {
        case ARMY_BARRACK:
        {
            
        }
            break;
        case ARMY_LABORATORY:
        {
            
        }
            break; 
        case ARMY_SPELLFORGE:
        {
            
        }
            break;  
        default:
            break;
    }
}

void CentralInfoUILayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

    CCPoint touchLocation = pTouch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
   
    switch (m_type)
    {
        case ARMY_BARRACK:
        {
            if (inSpritePosition(btn_SpeedUp,touchLocation))
            {
                speedUP();
            }
            else if (inSpritePosition(m_Sprite,touchLocation))
            {
                CCSprite* temp = (CCSprite*) m_Sprite->getChildByTag(101);
                if (temp != NULL)
                {
                    CCPoint pos = m_Sprite->getPosition();
                    CCPoint anchor = m_Sprite->getAnchorPoint();
                    
                    CCRect r = CCRectMake(pos.x - m_Sprite->getTextureRect().size.width*anchor.x + (m_Sprite->getTextureRect().size.width - temp->getTextureRect().size.width),
                                          pos.y - m_Sprite->getTextureRect().size.height*anchor.y + (m_Sprite->getTextureRect().size.height - temp->getTextureRect().size.height),
                                          temp->getTextureRect().size.width,
                                          temp->getTextureRect().size.height);
                    
                    
                    if (r.origin.x<=touchLocation.x&&touchLocation.x<=r.origin.x+r.size.width&&
                        r.origin.y<=touchLocation.y&&touchLocation.y<=r.origin.y+r.size.height)
                    {
                        CCLOG("ssssssssssss");
                        reomBarracks();
                        infoSBarr();
                    }
                    else
                    {
                        isaddbing = false;
                        addbing_time = 0;
                        addBing();
                    }

                }
                 
            }
            else if (inSpritePosition(m_SpriteA,touchLocation))
            {
                isjianbing = false;
                jianbing_time = 0;
                jianBing();
                
            }
        }
            break;
        case ARMY_LABORATORY:
        {
            if (inSpritePosition(m_Sprite,touchLocation))
            {
                StateSprite * tempS = (StateSprite*)m_Sprite;
                if (tempS->stableState == IconState_LevelLow)
                {
                    return;
                }
                
                switch (tempS->state) 
                {
                    case IconState_normal:
                    {
                        reomUpSoldiers();
                        infoUpSoldiersZunbei();
                        
                    }
                        break;
                    case IconState_LevelLow:
                    {

                    }
                        break;
                    case IconState_LackOfGold:
                    {

                    }
                        break;
                    case IconState_LackOfPotions:
                    {

                    }
                        break;
                    case IconState_LackOfGem:
                    {

                    }
                        break;
                    case IconState_ToOpen:
                    {

                    }
                        break;
                    default:
                        break;
                }
            }
            
            
            if (inSpritePosition(btn_SpeedUp, touchLocation))
            {
                //加速
                
                speedUP();
                
            }
        }
            break;   
        case ARMY_SPELLFORGE:
        {
            if (inSpritePosition(m_Sprite,touchLocation))
            {
                StateSprite * tempS = (StateSprite*)m_Sprite;
                if (tempS->stableState == IconState_LevelLow)
                {
                    return;
                }
                switch (tempS->state) 
                {
                    case IconState_normal:
                    {
                        addMagic(m_spriteNum);
                        updateMagicState();
                    }
                        break;
                    case IconState_LevelLow:
                    {
                        
                    }
                        break;
                    case IconState_LackOfGold:
                    {
                        
                    }
                        break;
                    case IconState_LackOfPotions:
                    {
                        
                    }
                        break;
                    case IconState_LackOfGem:
                    {
                        
                    }
                        break;
                    case IconState_ToOpen:
                    {
                        
                    }
                        break;
                    default:
                        break;
                }
                
                
            }
        }
            break;
        default:
            break;
    }
}

void CentralInfoUILayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}



void CentralInfoUILayer::updateMagicLabel()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    int num = arrIcon->count();
    for (int i = 0; i < num; i++)
    {
        if (pCentralScene->m_pCentralLayer->m_building->m_magicBuild != NULL)
        {
            //刷新文字
            for( int j = 0; j < (int)pCentralScene->m_pCentralLayer->m_building->m_magicBuild->size(); j++ )
            {
                
                if (pCentralScene->m_pCentralLayer->m_building->m_magicBuild->at(j)->tyep-1 == i)
                {
                    int s_num = pCentralScene->m_pCentralLayer->m_building->m_magicBuild->at(j)->num;
                    
                    CCSprite* icon = (CCSprite*)arrIcon->objectAtIndex(i);
                    
                    CCLabelTTF *timeLabel = (CCLabelTTF*)icon->getChildByTag(1);
                    if (s_num != 0)
                    {
                        timeLabel->setString(CommonResource::getStringFromInt(s_num).c_str());
                    }
                    else
                    {
                        timeLabel->setString("");
                    }
                }
            }
        }
    }
}
void CentralInfoUILayer::updateLabel()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    int num = arrIcon->count();
    for (int i = 0; i < num; i++)
    {
        if (pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers != NULL) {
            for( int j = 0; j < (int)pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers->size(); j++ )
            {

                if (pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers->at(j)->tyep-1 == i)
                {
                    int s_num = pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers->at(j)->num;
                    
                    CCSprite* icon = (CCSprite*)arrIcon->objectAtIndex(i);
                    
                    CCLabelTTF *timeLabel = (CCLabelTTF*)icon->getChildByTag(1);
                    if (s_num != 0)
                    {
                        timeLabel->setString(CommonResource::getStringFromInt(s_num).c_str());
                    }
                    
                }
            }
            
        }
        
        
    }
    
    if (pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers != NULL)
    {
        for( int j = 0; j < (int)pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers->size(); j++ )
        {
            char strFileName[64];

            sprintf(strFileName,"soldiers_Icon%d.png",pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers->at(j)->tyep);
            
            StateSprite* sprite =(StateSprite*) CCSprite::createWithSpriteFrameName(strFileName);
            sprite->setPosition(ccp(310-60*j,130));
            sprite->setScale(0.7);
            sprite->type = pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers->at(j)->tyep;
            this->addChild(sprite);
            
            int s_num = pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers->at(j)->num;
            
            CCLabelTTF *timeLabel = CCLabelTTF::create("", "Helvetica", sprite->getContentSize().height/4);
            timeLabel->setAnchorPoint(ccp(0,1));
            timeLabel->setPosition(ccp(0, sprite->getContentSize().height));
            sprite->addChild(timeLabel,100,1);
            
            if (s_num != 0)
            {
                timeLabel->setString(CommonResource::getStringFromInt(s_num).c_str());
            }
            CCSprite* strj = CCSprite::createWithSpriteFrameName("ui_public_btn_minus.png");
            strj->setAnchorPoint(ccp(1,1));
            strj->setPosition(ccp(sprite->getContentSize().width, sprite->getContentSize().height));
            sprite->addChild(strj);
            
            
            CCSprite* article0 = CCSprite::createWithSpriteFrameName("ui_public_article0.png");
            article0->setAnchorPoint(ccp(0,0));
            article0->setPosition(ccp(0, 0));
            sprite->addChild(article0,2,2);
            CCSprite* article1 = CCSprite::createWithSpriteFrameName("ui_public_article1.png");
            article1->setAnchorPoint(ccp(0,0));
            article1->setPosition(ccp(0, 0));
            sprite->addChild(article1,3,3);
            CCLabelTTF* article = CCLabelTTF::create("", "Helvetica", article0->getContentSize().height);
            article->setAnchorPoint(ccp(0.5,0.5));
            article->setPosition(ccp(article0->getContentSize().width/2, article0->getContentSize().height/2));
            sprite->addChild(article,4,4);
            
            article->setVisible(false);
            article0->setVisible(false);
            article1->setVisible(false);
            article->setScale(1.42);
            article0->setScale(1.42);
            article1->setScale(1.42);
            
            
            arrAIcon->addObject(sprite);
            
        }
        
    }
    
//    arrAIcon
}
void CentralInfoUILayer::infoLayer()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    const BaseBuildingLevelData* buildingBaseLevelData;
    buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( pCentralScene->m_pCentralLayer->m_building->getID());
    const string* name = GameData::GetTextInfo(buildingBaseLevelData->Text);
    
    char framename[256] = {0};
    sprintf(framename,"%s\n%d.png",name->c_str(),pCentralScene->m_pCentralLayer->m_building->lv);

    
    CCLabelTTF* timeLabel = CCLabelTTF::create(framename, "Helvetica", 24);
    timeLabel->setPosition(ccp(200, 200));
    this->addChild(timeLabel);
    
}
void CentralInfoUILayer::allinfoUINo()
{
    l_info1->setVisible(false);
    l_info2->setVisible(false);
    l_info3->setVisible(false);
    l_info_mubiao->setVisible(false);
    l_info_leixing->setVisible(false);
    l_info_duixiang->setVisible(false);
    l_info_renkou->setVisible(false);
    l_info_shijian->setVisible(false);
    l_info_shudu->setVisible(false);
    l_info_mubiaonum->setVisible(false);
    l_info_leixingnum->setVisible(false);
    l_info_duixiangnum->setVisible(false);
    l_info_renkounum->setVisible(false);
    l_info_shijiannum->setVisible(false);
    l_info_shudunum->setVisible(false);
    s_info_icon1->setVisible(false);
    s_info_bg1->setVisible(false);
    s_info1->setVisible(false);
    s_info_lbg1->setVisible(false);
    s_info_icon2->setVisible(false);
    s_info_bg2->setVisible(false);
    s_info2->setVisible(false);
    s_info_lbg2->setVisible(false);
    s_info_icon3->setVisible(false);
    s_info_bg3->setVisible(false);
    s_info3->setVisible(false);
    s_info_lbg3->setVisible(false);
    s_info_lbg->setVisible(false);
    s_info_tubg->removeAllChildrenWithCleanup(false);
    s_info_tubg->setVisible(false);
    nextBtn->setVisible(false);
    nextBtn->setTouchEnabled(false);
    
    l_info_time->setVisible(false);
    l_info_timebiaoti->setVisible(false);
    s_info_timebg->setVisible(false);
    
    updatalevel->removeChildByTag(2, false);
    updatalevel->setVisible(false);
    updatalevel->setTouchEnabled(false);
}
void CentralInfoUILayer::infoSBarr()
{   
    CentralData::BuildableSoldiers* temp = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->getBuildableSoldiers(arrNumS+1);
    const BasePeopleData* basePeopleData = NULL;
    if (temp != NULL)
    {
        basePeopleData = GameData::GetDataFromBasePeopleData(temp->type * PEOPLE_TYPE_ * 100+ temp->leve);
    }
    else
    {
        basePeopleData = GameData::GetDataFromBasePeopleData((arrNumS+1) * PEOPLE_TYPE_ * 100+ 1);
    }
    
    char strinfo1[256] = {0};
    sprintf(strinfo1,"攻击:%d",basePeopleData->Damage);
    l_info1->setString(strinfo1);
    char strinfo2[256] = {0};
    sprintf(strinfo2,"血量:%d",basePeopleData->Hitpoints);
    l_info2->setString(strinfo2);
    char strinfo3[256] = {0};
    sprintf(strinfo3,"消耗:%d",basePeopleData->TrainingCost);
    l_info3->setString(strinfo3);
    
    nextBtn->setTouchEnabled(true);
    l_info1->setVisible(true);
    l_info2->setVisible(true);
    l_info3->setVisible(true);
    
    
    char strmubiao[256] = {0};
    if (basePeopleData->PreferedTargetBuilding == BUILDINGTYPE_WALL)
    {
        sprintf(strmubiao,"墙");
    }
    else
    {
        sprintf(strmubiao,"任何建筑");
    }
    
    
    char strleixing[256] = {0};
    if (basePeopleData->DamageRadius > 0)
    {
        sprintf(strleixing,"范围");
    }
    else
    {
        sprintf(strleixing,"单体");
    }
    
    char strduixiang[256] = {0};
    if (basePeopleData->AirTargets)
    {
        sprintf(strduixiang,"对空*对地");
    }
    else
    {
        sprintf(strduixiang,"对地");
    }
    
    char strrenkou[256] = {0};
    sprintf(strrenkou,"%d",basePeopleData->HousingSpace);
    
    char strshijian[256] = {0};
    sprintf(strshijian,"%ds",basePeopleData->TrainingTime);
    char strshudu[256] = {0};
    sprintf(strshudu,"%d",basePeopleData->Speed);
    
    l_info_mubiaonum->setString(strmubiao);
    l_info_leixingnum->setString(strleixing);
    l_info_duixiangnum->setString(strduixiang);
    l_info_renkounum->setString(strrenkou);
    l_info_shijiannum->setString(strshijian);
    l_info_shudunum->setString(strshudu);
    
    
    
    char striconS[256] = {0};
    sprintf(striconS,"soldiers_%d.png",(arrNumS+1));
    CCSprite* iconS = CCSprite::createWithSpriteFrameName(striconS);
    iconS->setAnchorPoint(ccp(1, 0));
    if ((arrNumS+1) == 4)
    {
        iconS->setPosition(ccp(155, 20));
    }
    else
    {
        iconS->setPosition(ccp(135, 20));
    }
    
    s_info_tubg->addChild(iconS);
    
    l_info_mubiao->setVisible(true);
    l_info_leixing->setVisible(true);
    l_info_duixiang->setVisible(true);
    l_info_renkou->setVisible(true);
    l_info_shijian->setVisible(true);
    l_info_shudu->setVisible(true);
    l_info_mubiaonum->setVisible(true);
    l_info_leixingnum->setVisible(true);
    l_info_duixiangnum->setVisible(true);
    l_info_renkounum->setVisible(true);
    l_info_shijiannum->setVisible(true);
    l_info_shudunum->setVisible(true);
    s_info_icon1->setVisible(true);
    s_info_bg1->setVisible(true);
    s_info1->setVisible(true);
    s_info_lbg1->setVisible(true);
    s_info_icon2->setVisible(true);
    s_info_bg2->setVisible(true);
    s_info2->setVisible(true);
    s_info_lbg2->setVisible(true);
    s_info_icon3->setVisible(true);
    s_info_bg3->setVisible(true);
    s_info3->setVisible(true);
    s_info_lbg3->setVisible(true);
    s_info_lbg->setVisible(true);
    s_info_tubg->setVisible(true);
    nextBtn->setVisible(true);
}
void CentralInfoUILayer::HuiFuBarracks()
{
    
    int num = arrIcon->count();
    for (int i = 0; i < num; i++)
    {
        CCSprite* icon = (CCSprite*)arrIcon->objectAtIndex(i);
        icon->setVisible(true);
    }
    
    num = arrAIcon->count();
    for (int i = 0; i < num; i++)
    {
        CCSprite* icon = (CCSprite*)arrAIcon->objectAtIndex(i);
        icon->setVisible(true);
    }
    l_tishi->setVisible(true);
    l_biaoti->setVisible(true);
    s_bgl1->setVisible(true);
    s_bgl2->setVisible(true);
    s_bgl3->setVisible(true);
    
    m_AllTimeLabel->setVisible(true);
    m_AllPeopleLabel->setVisible(true);
    s_bgl1->setVisible(true);
    s_bgl3->setVisible(true);
    
    iserJi = false;
}
void CentralInfoUILayer::reomBarracks()
{
    iserJi = true;
    int num = arrIcon->count();
    for (int i = 0; i < num; i++)
    {
        CCSprite* icon = (CCSprite*)arrIcon->objectAtIndex(i);
        icon->setVisible(false);
    }
    
    num = arrAIcon->count();
    for (int i = 0; i < num; i++)
    {
        CCSprite* icon = (CCSprite*)arrAIcon->objectAtIndex(i);
        icon->setVisible(false);
    }
    l_tishi->setVisible(false);
    l_biaoti->setVisible(false);
    s_bgl1->setVisible(false);
    s_bgl2->setVisible(false);
    s_bgl3->setVisible(false);
    btn_SpeedUp->setVisible(false);
    
    m_AllTimeLabel->setVisible(false);
    m_AllPeopleLabel->setVisible(false);
    s_bgl1->setVisible(false);
    s_bgl3->setVisible(false);
}
void CentralInfoUILayer::infoUILayer(int _type,int _uiType)
{
    allinfoUINo();
    m_type =  _type;
    UI_type =  _uiType;
    if (UI_type == UIType_info)
    {
        
    }
    else if (UI_type == UIType_build)
    {
        btn_SpeedUp = CCSprite::createWithSpriteFrameName("ui_public_btn_acceleration.png");
        btn_SpeedUp->setPosition(ccp(390, 225));
        btn_SpeedUp->setVisible(false);
        this->addChild(btn_SpeedUp);
        CCLabelTTF *timeLabel = CCLabelTTF::create("", "Helvetica", btn_SpeedUp->getContentSize().height/2);
        timeLabel->setAnchorPoint(ccp(0,1));
        timeLabel->setPosition(ccp(0, btn_SpeedUp->getContentSize().height));
        btn_SpeedUp->addChild(timeLabel,1,1);
        
        switch (m_type)
        {
            case ARMY_BARRACK:
            {
                arrIcon = CCArray::create();
                arrIcon->retain();
                arrAIcon = CCArray::create();
                arrAIcon->retain();
                
                 
                
                m_AllTimeLabel = CCLabelTTF::create("", "Helvetica", 12);
                m_AllTimeLabel->setPosition(ccp(400, 252));
                this->addChild(m_AllTimeLabel);
                m_AllPeopleLabel = CCLabelTTF::create("", "Helvetica", 12);
                m_AllPeopleLabel->setAnchorPoint(ccp(1,0.5));
                m_AllPeopleLabel->setPosition(ccp(340, 199));
                this->addChild(m_AllPeopleLabel);
                
                
                s_bgl1->setVisible(false);
                s_bgl2->setVisible(true);
                s_bgl3->setVisible(false);
                
                //文字
                l_tishi->setVisible(true);
                l_biaoti->setVisible(true);
                
                
                infoBarracks();
                
            }
                break;
            case ARMY_LABORATORY:
            {
                arrIcon = CCArray::create();
                arrIcon->retain();
                arrIconM = CCArray::create();
                arrIconM->retain();
                arrSpr = CCArray::create();
                arrSpr->retain();
                if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->m_building->UpLeveTyep == 0)
                {
                    infoUpSoldiers();
                }
                else
                {
                    infoUpSoldiersing();
                }
                
            }
                break;
            case ARMY_SPELLFORGE:
            {
                arrIcon = CCArray::create();
                arrIcon->retain();
                arrIconM = CCArray::create();
                arrIconM->retain();
                infoMagic();
                
                updateMagicLabel();
            }
                break;
                
            default:
                break;
        }
    }
    else if (UI_type == UIType_buildUp)
    {
        
    }
    
}
void CentralInfoUILayer::infoMagic()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    buildLeve  = 0;
    
    if (pCentralScene->m_pCentralLayer->m_building != NULL) buildLeve = pCentralScene->m_pCentralLayer->m_building->lv;
    
    int num = 0;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GAME_FILE_TRANSFORM("soldiers_Icon",".plist").c_str(),GAME_FILE_TRANSFORM("soldiers_Icon",".png").c_str());
    for (int i = 0; i < 5; i++)
    {
        num++;
        
           
        char strFileName[64];
        
        if (buildLeve>=num) 
        {
            sprintf(strFileName,"soldiers_Icon%d.png",num);
        }   
        else
        {
            sprintf(strFileName,"soldiers_Icon_Disabled%d.png",num);
        }
        
        CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strFileName);
        StateSprite* sprite = (StateSprite*)CCSprite::createWithSpriteFrame(spriteFrame);
        
        sprite->setPosition(ccp(125+i*60, 170));
        
        CCLabelTTF *timeLabel = CCLabelTTF::create("", "Helvetica", sprite->getContentSize().height/4);
        timeLabel->setAnchorPoint(ccp(0,1));
        timeLabel->setPosition(ccp(0, sprite->getContentSize().height));
        sprite->addChild(timeLabel,1,1);
        
        pCentralScene->m_pCentralInfoUILayer->addChild(sprite);
        
        CentralData::BuildableMagic* temp = pCentralScene->m_pCentralData->getBuildableMagic(num);
        sprite->state = IconState_normal;
        sprite->stableState = IconState_normal;
        
        if (temp == NULL)
        {
            sprite->stableState = IconState_LevelLow;
        }
        else
        {
            sprite->level = temp->leve;
            sprite->type = temp->type;
        }
        
        
        
        arrIcon->addObject(sprite);
    }
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GAME_FILE_TRANSFORM("UI_Map_Info",".plist").c_str(),GAME_FILE_TRANSFORM("UI_Map_Info",".png").c_str());
    for (int i = 0; i < 7; i++)
    { 
        CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(GAME_FILE_TRANSFORM("UI_Map_Info_BarracksReproduction_empty",".png").c_str());
        CCSprite* sprite = CCSprite::createWithSpriteFrame(spriteFrame);
        
        sprite->setPosition(ccp(128+i*40, 210-2*60));
        
        pCentralScene->m_pCentralInfoUILayer->addChild(sprite);
    }
    
    
    updateMagicState();
    
}
void CentralInfoUILayer::updateMagic()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GAME_FILE_TRANSFORM("UI_Map_Info",".plist").c_str(),GAME_FILE_TRANSFORM("UI_Map_Info",".png").c_str());
    for (int i = 0; i < 7; i++)
    { 
        CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(GAME_FILE_TRANSFORM("UI_Map_Info_BarracksReproduction",".png").c_str());
        CCSprite* sprite = CCSprite::createWithSpriteFrame(spriteFrame);
        
        sprite->setPosition(ccp(128+i*40, 210-2*60));
        CCLabelTTF *timeLabel = CCLabelTTF::create("", "Helvetica", sprite->getContentSize().height/4);
        timeLabel->setAnchorPoint(ccp(0,1));
        timeLabel->setPosition(ccp(0, sprite->getContentSize().height));
        sprite->addChild(timeLabel,1,1);
        
        pCentralScene->m_pCentralInfoUILayer->addChild(sprite);
        
        arrIconM->addObject(sprite);
        
    }
}
void CentralInfoUILayer::updateBarracksState()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    int num = arrIcon->count();
    for (int i = 0; i < num; i++)
    {
        StateSprite* sprite = (StateSprite*)arrIcon->objectAtIndex(i);
        
        CentralData::BuildableSoldiers* temp = pCentralScene->m_pCentralData->getBuildableSoldiers(i+1);
        
        
        if(sprite->stableState == IconState_LevelLow)
        {
            
        }
        else
        {
            const BasePeopleData* basePeopleData;
            basePeopleData = GameData::GetDataFromBasePeopleData(temp->type * PEOPLE_TYPE_ *100 + temp->leve);
            
            
//            if (pCentralScene->m_pCentralLayer->m_building->productionState == Production_State_Full)
//            {
//                sprite->state = IconState_Full;
//            }
            
            //金币
            if ("Gold" == string(basePeopleData->TrainingResource)) 
            {
                if (pCentralScene->m_pCentralData->m_Central_UserData->user_gold < basePeopleData->TrainingCost)
                {
                    sprite->state = IconState_LackOfGold;
                }
            }
            //药水
            else if("Elixir" == string(basePeopleData->TrainingResource))
            {
                if (pCentralScene->m_pCentralData->m_Central_UserData->user_potions < basePeopleData->TrainingCost)
                {
                    sprite->state = IconState_LackOfPotions;
                }
            }
            //宝石
            else if("Diamonds" == string(basePeopleData->TrainingResource))
            {
                if (pCentralScene->m_pCentralData->m_Central_UserData->user_gem < basePeopleData->TrainingCost)
                {
                    sprite->state = IconState_LackOfGem;
                }
            }
            
            
            CCNode*  sprBg2 = sprite->getChildByTag(3);
            CCNode*  sprIcon2 = sprite->getChildByTag(4);
            if (sprBg2 != NULL)
            {
                if (sprite->state == IconState_normal)
                {
                    sprBg2->setVisible(false);
                    sprIcon2->setVisible(false);
                    
                    
                    if (pCentralScene->m_pCentralLayer->m_building->duileiNum+basePeopleData->HousingSpace > pCentralScene->m_pCentralLayer->m_building->duileiMAXNum)
                    {
                        sprBg2->setVisible(true);
                        sprIcon2->setVisible(true);
                    }
                    else
                    {
                        sprBg2->setVisible(false);
                        sprIcon2->setVisible(false);
                    }
                }
                else
                {
                    sprBg2->setVisible(true);
                    sprIcon2->setVisible(true);
                }
                
                
            }
            
            
            
            
            
            
            

        }
        
    }
}

void CentralInfoUILayer::updateMagicState()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    pCentralScene->m_pCentralLayer->m_building->updataProductionState();
    int num = arrIcon->count();
    for (int i = 0; i < num; i++)
    {
        StateSprite* sprite = (StateSprite*)arrIcon->objectAtIndex(i);
        CentralData::BuildableMagic* temp = pCentralScene->m_pCentralData->getBuildableMagic(sprite->type);
        
        if (temp)
        {
            const BaseSpellData* baseSpellData;
            baseSpellData = GameData::GetDataFromBaseSpellData(temp->type * 100 + temp->leve);
            
            
            if (pCentralScene->m_pCentralLayer->m_building->productionState == Production_State_Full)
            {
                sprite->state = IconState_Full;
            }
            
            //金币
            if ("Gold" == string(baseSpellData->TrainingResource)) 
            {
                if (pCentralScene->m_pCentralData->m_Central_UserData->user_gold < baseSpellData->TrainingCost)
                {
                    sprite->state = IconState_LackOfGold;
                }
            }
            //药水
            else if("Elixir" == string(baseSpellData->TrainingResource))
            {
                if (pCentralScene->m_pCentralData->m_Central_UserData->user_potions < baseSpellData->TrainingCost)
                {
                    sprite->state = IconState_LackOfPotions;
                }
            }
            //宝石
            else if("Diamonds" == string(baseSpellData->TrainingResource))
            {
                if (pCentralScene->m_pCentralData->m_Central_UserData->user_gem < baseSpellData->TrainingCost)
                {
                    sprite->state = IconState_LackOfGem;
                }
            }
        }
        
        
        

        
        
    }
}
void CentralInfoUILayer::speedUP()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    switch (m_type)
    {
        case ARMY_BARRACK:
        {
            if (pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers != NULL) 
            {
                if ((int)pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers->size() > 0)
                {
                    if (pCentralScene->m_pCentralLayer->m_building->allProductionTime > 0)
                    {
                        int remkou = 0;
                        for( int i = 0; i < (int)pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers->size(); i++ )
                        {
                            const BasePeopleData* pdata = GameData::GetDataFromBasePeopleData(pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers->at(i)->tyep*100000+1);
                            
                            remkou += pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers->at(i)->num *pdata->HousingSpace;
                            
                        }
                        
                        if (pCentralScene->m_pCentralData->m_Central_UserData->allYouPeopleNum+remkou <= pCentralScene->m_pCentralData->m_Central_UserData->peopleNumMax)
                        {
                            int numG = pCentralScene->m_pCentralLayer->gemConversion(pCentralScene->m_pCentralLayer->m_building->allProductionTime);
                            bool isG = pCentralScene->m_pCentralUILayer->updateGem(-numG);
                            
                            if (isG)
                            {
                                pCentralScene->m_pCentralLayer->Accelerated_id = pCentralScene->m_pCentralLayer->m_building->getTypeID();
                                pCentralScene->m_pCentralLayer->Accelerated_uuid = pCentralScene->m_pCentralLayer->m_building->getuuID();
                                pCentralScene->m_pCentralLayer->Accelerated_remain_time = pCentralScene->m_pCentralLayer->m_building->allProductionTime;
                                pCentralScene->m_pCentralLayer->Accelerated_gem_count = numG;
                                //宝石够
                                pCentralScene->m_pCentralLayer->m_building->ImmediatelyComplete();
                                
                            }
                            else
                            {
                                
                                
                            }
                        }
                        
                    }
                }
                else
                {
                    btn_SpeedUp->setVisible(false);
                }
            }
        }
            break;
        case ARMY_LABORATORY:
        {
            
            long tempTime = Until::millisecondNow_m();
            
            long cd_time = tempTime - pCentralScene->m_pCentralLayer->m_building->UpLeveTime;

            int numG = pCentralScene->m_pCentralLayer->gemConversion(pCentralScene->m_pCentralLayer->m_building->UPLeveCDTime - cd_time);
            
            bool isG = pCentralScene->m_pCentralUILayer->updateGem(-numG);
            
            if (isG)
            {
                pCentralScene->m_pCentralLayer->Accelerated_id = pCentralScene->m_pCentralLayer->m_building->getTypeID();
                pCentralScene->m_pCentralLayer->Accelerated_uuid = pCentralScene->m_pCentralLayer->m_building->getuuID();
                pCentralScene->m_pCentralLayer->Accelerated_remain_time = pCentralScene->m_pCentralLayer->m_building->UPLeveCDTime - cd_time;
                pCentralScene->m_pCentralLayer->Accelerated_gem_count = numG;
                //宝石够
                pCentralScene->m_pCentralLayer->m_building->ImmediatelyComplete();
                
            }
            
        }
            break;   
        case ARMY_SPELLFORGE:
        {
            
        }
            break;
        default:
            break;
    }

}
void CentralInfoUILayer::updateSpeedUp()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    switch (m_type)
    {
        case ARMY_BARRACK:
        {
            if (pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers != NULL) 
            {
                if ((int)pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers->size() > 0)
                {
                    if (pCentralScene->m_pCentralLayer->m_building->allProductionTime > 0)
                    {
                        
                        CCLabelTTF *timeLabel = (CCLabelTTF*)btn_SpeedUp->getChildByTag(1);
                        timeLabel->setString(CommonResource::getStringFromInt(pCentralScene->m_pCentralLayer->gemConversion(pCentralScene->m_pCentralLayer->m_building->allProductionTime)).c_str());

                        
                        btn_SpeedUp->setVisible(true);   
                    }
                }
                else
                {
                    CCLabelTTF *timeLabel = (CCLabelTTF*)btn_SpeedUp->getChildByTag(1);
                    timeLabel->setString("");
                    btn_SpeedUp->setVisible(false);
                    m_AllTimeLabel->setString("");
                    pCentralScene->m_pCentralInfoUILayer->m_AllPeopleLabel->setString("");
                    
                    s_bgl1->setVisible(false);
                    s_bgl3->setVisible(false);
                }
            }
        }
            break;
        case ARMY_LABORATORY:
        {
            
        }
            break;   
        case ARMY_SPELLFORGE:
        {
            
        }
            break;
        default:
            break;
    }

}
void CentralInfoUILayer::reomUpSoldiersing()
{
    if (btn_SpeedUp != NULL)
    {   
        btn_SpeedUp->removeFromParentAndCleanup(false);
        btn_SpeedUp = NULL;
        m_timeLabel->removeFromParentAndCleanup(false);
        m_timeLabel = NULL;
        this->removeChildByTag(201, false);
        this->removeChildByTag(202, false);
        this->removeChildByTag(203, false);
        this->removeChildByTag(204, false);
        
    }
}
void CentralInfoUILayer::infoUpSoldiersing()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    if (pCentralScene->m_pCentralLayer->m_building->UpLeveTyep != 0)
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GAME_FILE_TRANSFORM("soldiers_Icon",".plist").c_str(),GAME_FILE_TRANSFORM("soldiers_Icon",".png").c_str());
        char striconS[256] = {0};
        sprintf(striconS,"soldiers_%d.png",(pCentralScene->m_pCentralLayer->m_building->UpLeveTyep));
        CCSprite* iconS = CCSprite::createWithSpriteFrameName(striconS);
        iconS->setAnchorPoint(ccp(1, 0));
        if ((arrNumS+1) == 4)
        {
            iconS->setPosition(ccp(220, 55));
        }
        else
        {
            iconS->setPosition(ccp(220, 55));
        }
        
        this->addChild(iconS, 201,201);
        
        CCLabelTTF *wanTimeLabel = CCLabelTTF::create("完成时间:", "Helvetica", 13);
        wanTimeLabel->setPosition(ccp(325, 185));
        this->addChild(wanTimeLabel, 202,202);
        
        CCLabelTTF *wanUpLabel = CCLabelTTF::create("完成升级", "Helvetica", 13);
        wanUpLabel->setPosition(ccp(325, 150));
        this->addChild(wanUpLabel, 203,203);
        
        CCSprite* public_bg8 = CCSprite::createWithSpriteFrameName("ui_public_bg8.png");
        public_bg8->setPosition(ccp(325, 165));
        this->addChild(public_bg8, 204,204);
        
        btn_SpeedUp = CCSprite::createWithSpriteFrameName("ui_public_btn_acceleration.png");
        btn_SpeedUp->setPosition(ccp(325, 125));
        this->addChild(btn_SpeedUp);
        
        CCLabelTTF *timeLabel = CCLabelTTF::create("", "Helvetica", 13);
        timeLabel->setPosition(ccp(btn_SpeedUp->getContentSize().width/2, btn_SpeedUp->getContentSize().height/2));
        btn_SpeedUp->addChild(timeLabel,100,1);
        
        m_timeLabel = CCLabelTTF::create("", "Helvetica", 13);
        m_timeLabel->setPosition(ccp(325, 165));
        this->addChild(m_timeLabel);
        
    }
    
    
}
void CentralInfoUILayer::infoUpSoldiersZunbei()
{
    CentralData::BuildableSoldiers* temp = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->getBuildableSoldiers(arrNumS+1);
    const BasePeopleData* basePeopleData = NULL;
    if (temp != NULL)
    {
        basePeopleData = GameData::GetDataFromBasePeopleData(temp->type * PEOPLE_TYPE_ * 100+ temp->leve);
    }
    else
    {
        basePeopleData = GameData::GetDataFromBasePeopleData((arrNumS+1) * PEOPLE_TYPE_ * 100+ 1);
    }
    
    char strinfo1[256] = {0};
    sprintf(strinfo1,"攻击:%d",basePeopleData->Damage);
    l_info1->setString(strinfo1);
    char strinfo2[256] = {0};
    sprintf(strinfo2,"血量:%d",basePeopleData->Hitpoints);
    l_info2->setString(strinfo2);
    char strinfo3[256] = {0};
    sprintf(strinfo3,"消耗:%d",basePeopleData->TrainingCost);
    l_info3->setString(strinfo3);
    
    nextBtn->setTouchEnabled(true);
    l_info1->setVisible(true);
    l_info2->setVisible(true);
    l_info3->setVisible(true);
    
    
    char strmubiao[256] = {0};
    if (basePeopleData->PreferedTargetBuilding == BUILDINGTYPE_WALL)
    {
        sprintf(strmubiao,"墙");
    }
    else
    {
        sprintf(strmubiao,"任何建筑");
    }
    
    
    char strleixing[256] = {0};
    if (basePeopleData->DamageRadius > 0)
    {
        sprintf(strleixing,"范围");
    }
    else
    {
        sprintf(strleixing,"单体");
    }
    
    char strduixiang[256] = {0};
    if (basePeopleData->AirTargets)
    {
        sprintf(strduixiang,"对空*对地");
    }
    else
    {
        sprintf(strduixiang,"对地");
    }
    
    char strrenkou[256] = {0};
    sprintf(strrenkou,"%d",basePeopleData->HousingSpace);
    
    char strshijian[256] = {0};
    sprintf(strshijian,"%ds",basePeopleData->TrainingTime);
    char strshudu[256] = {0};
    sprintf(strshudu,"%d",basePeopleData->Speed);
    
    l_info_mubiaonum->setString(strmubiao);
    l_info_leixingnum->setString(strleixing);
    l_info_duixiangnum->setString(strduixiang);
    l_info_renkounum->setString(strrenkou);
    l_info_shijiannum->setString(strshijian);
    l_info_shudunum->setString(strshudu);
    
    
    
    char striconS[256] = {0};
    sprintf(striconS,"soldiers_%d.png",(arrNumS+1));
    CCSprite* iconS = CCSprite::createWithSpriteFrameName(striconS);
    iconS->setAnchorPoint(ccp(1, 0));
    if ((arrNumS+1) == 4)
    {
        iconS->setPosition(ccp(155, 20));
    }
    else
    {
        iconS->setPosition(ccp(135, 20));
    }
    
    s_info_tubg->addChild(iconS);
    
    
    //时间
    char strtimeL[256] = {0};
    sprintf(strtimeL,"%dh",basePeopleData->UpgradeTimeH);
    l_info_time->setString(strtimeL);
    l_info_time->setVisible(true);
    l_info_timebiaoti->setVisible(true);
    s_info_timebg->setVisible(true);
    
    
    
    //花费
    updatalevel->setVisible(true);
    updatalevel->setTouchEnabled(true);
    
    char strUpgradeCostLabel[256] = {0};
    sprintf(strUpgradeCostLabel,"%d",basePeopleData->UpgradeCost);
    CCLabelTTF *UpgradeCostLabel = CCLabelTTF::create(strUpgradeCostLabel, "Helvetica", 12);
    UpgradeCostLabel->setAnchorPoint(ccp(1,1));
    UpgradeCostLabel->setPosition(ccp(62, 30));
    updatalevel->addChild(UpgradeCostLabel,2,2);
    
    
    l_info_mubiao->setVisible(true);
    l_info_leixing->setVisible(true);
    l_info_duixiang->setVisible(true);
    l_info_renkou->setVisible(true);
    l_info_shijian->setVisible(true);
    l_info_shudu->setVisible(true);
    l_info_mubiaonum->setVisible(true);
    l_info_leixingnum->setVisible(true);
    l_info_duixiangnum->setVisible(true);
    l_info_renkounum->setVisible(true);
    l_info_shijiannum->setVisible(true);
    l_info_shudunum->setVisible(true);
    s_info_icon1->setVisible(true);
    s_info_bg1->setVisible(true);
    s_info1->setVisible(true);
    s_info_lbg1->setVisible(true);
    s_info_icon2->setVisible(true);
    s_info_bg2->setVisible(true);
    s_info2->setVisible(true);
    s_info_lbg2->setVisible(true);
    s_info_icon3->setVisible(true);
    s_info_bg3->setVisible(true);
    s_info3->setVisible(true);
    s_info_lbg3->setVisible(true);
    s_info_lbg->setVisible(true);
    s_info_tubg->setVisible(true);
    nextBtn->setVisible(true);
    
}
void CentralInfoUILayer::huifuUpSoldiers()
{
    int num = arrIcon->count();
    for (int i = 0; i < num; i++)
    {
        CCSprite* temp = (CCSprite*)arrIcon->objectAtIndex(i);
        temp->setVisible(true);
    }
    
    num = arrIconM->count();
    for (int i = 0; i < num; i++)
    {
        CCSprite* temp = (CCSprite*)arrIconM->objectAtIndex(i);
        temp->setVisible(true);
    }
    
    num = arrSpr->count();
    for (int i = 0; i < num; i++)
    {
        CCSprite* temp = (CCSprite*)arrSpr->objectAtIndex(i);
        temp->setVisible(true);
    }
}
void CentralInfoUILayer::reomUpSoldiers()
{
    int num = arrIcon->count();
    for (int i = 0; i < num; i++)
    {
        CCSprite* temp = (CCSprite*)arrIcon->objectAtIndex(i);
        temp->setVisible(false);
    }
    
    num = arrIconM->count();
    for (int i = 0; i < num; i++)
    {
        CCSprite* temp = (CCSprite*)arrIconM->objectAtIndex(i);
        temp->setVisible(false);
    }
    
    num = arrSpr->count();
    for (int i = 0; i < num; i++)
    {
        CCSprite* temp = (CCSprite*)arrSpr->objectAtIndex(i);
        temp->setVisible(false);
    }
    
}
void CentralInfoUILayer::infoUpSoldiers()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    int num = 0;
    //兵底框
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            
            CCSprite* sprite = CCSprite::createWithSpriteFrameName("ui_public_bg7.png");
            
            sprite->setPosition(ccp(82+j*80, 230-i*80));
            
            pCentralScene->m_pCentralInfoUILayer->addChild(sprite);
            arrSpr->addObject(sprite);
        }
    }
//    //魔法底框
//    for (int i = 0; i < 5; i++)
//    {
//        CCSprite* sprite = CCSprite::createWithSpriteFrameName("ui_public_bg2.png");
//        
//        sprite->setPosition(ccp(60+i*90, 240-2*90));
//        
//        pCentralScene->m_pCentralInfoUILayer->addChild(sprite);
//        arrSpr->addObject(sprite);
//    }
    
    
    buildLeve = pCentralScene->m_pCentralLayer->MAXSoldiersLevel();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GAME_FILE_TRANSFORM("soldiers_Icon",".plist").c_str(),GAME_FILE_TRANSFORM("soldiers_Icon",".png").c_str());
    
    //兵
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            num++;
            char strFileName[64];
            
            if (buildLeve>=num) 
            {
                CentralData::BuildableSoldiers* temp = pCentralScene->m_pCentralData->getBuildableSoldiers(num);
                
                const BasePeopleData* basePeopleData;
                basePeopleData = GameData::GetDataFromBasePeopleData(temp->type * PEOPLE_TYPE_ * 100+ temp->leve);
                
                if (buildLeve>=basePeopleData->BarrackLevel) 
                {
                    sprintf(strFileName,"soldiers_Icon%d.png",num);
                    
                    StateSprite* sprite =(StateSprite*) CCSprite::createWithSpriteFrameName("ui_public_bg3.png");
                    
                    CCSprite* iconspr = CCSprite::createWithSpriteFrameName(strFileName);
                    iconspr->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
                    sprite->addChild(iconspr);
                    
                    
                    sprite->setPosition(ccp(82+j*80, 230-i*80));
                    
                    pCentralScene->m_pCentralInfoUILayer->addChild(sprite);
                    
                    //星星
                    if (temp != NULL)
                    {
                        if (temp->leve > 1)
                        {
                            for (int n = 0; n < temp->leve; n++)
                            {
                                CCSprite* sprXing = CCSprite::createWithSpriteFrameName("ui_public_stars.png");
                                sprXing->setAnchorPoint(ccp(0,1));
                                sprXing->setPosition(ccp(10*n,sprite->getContentSize().height));
                                sprite->addChild(sprXing,5,5);
                                
                            }
                        }
                    }
                    
                    
                    
                    
                    sprite->type = temp->type;
                    sprite->level = temp->leve;
                    sprite->state = IconState_normal;
                    //等级不够
                    if (pCentralScene->m_pCentralLayer->m_building->lv < basePeopleData->LaboratoryLevel) 
                    {
                        sprite->state = IconState_LevelLow;
                        
                        CCSprite* sprbj = CCSprite::createWithSpriteFrameName("ui_public_bg9.png");
                        sprbj->setAnchorPoint(ccp(0,0));
                        sprbj->setPosition(ccp(0,0));
                        sprite->addChild(sprbj,100);
                        
                        char strBarrackLevel[64];
                        sprintf(strBarrackLevel,"科技%d级解锁",basePeopleData->LaboratoryLevel);
                        
                        CCLabelTTF *BarrackLevelLabel = CCLabelTTF::create(strBarrackLevel, "Helvetica", 12,CCSize(sprite->getContentSize().width*2/3, sprite->getContentSize().height*2/3),kCCTextAlignmentCenter);
                        BarrackLevelLabel->setColor(ccBLACK);
                        BarrackLevelLabel->setAnchorPoint(ccp(0.5,0.5));
                        BarrackLevelLabel->setPosition(ccp(sprite->getContentSize().width/2+1, sprite->getContentSize().height/2-1));
                        sprite->addChild(BarrackLevelLabel,100);
                    }
                    else
                    {
                        
                        CCSprite* sprbj = CCSprite::createWithSpriteFrameName("ui_public_bg10.png");
                        sprbj->setAnchorPoint(ccp(0,0));
                        sprbj->setPosition(ccp(5,5));
                        sprite->addChild(sprbj,100);
                        
                        CCSprite* sprR = CCSprite::createWithSpriteFrameName("ui_public_icon_water.png");
                        sprR->setAnchorPoint(ccp(1,0));
                        sprR->setPosition(ccp(sprite->getContentSize().width,0));
                        sprite->addChild(sprR,100);
                        
                        
                        
                        CCLabelTTF *CostLabel = CCLabelTTF::create(CommonResource::getStringFromInt(basePeopleData->UpgradeCost).c_str(), "Helvetica", 12);
                        CostLabel->setAnchorPoint(ccp(1,0.5));
                        CostLabel->setPosition(ccp(sprite->getContentSize().width-sprR->getContentSize().width*sprR->getScaleX(), 10));
                        sprite->addChild(CostLabel,100);
                        
                        if("Elixir" == string(basePeopleData->UpgradeResource))
                        {
                            if (pCentralScene->m_pCentralData->m_Central_UserData->user_potions < basePeopleData->UpgradeCost)
                            {
                                CostLabel->setColor(ccRED);
                                sprite->state = IconState_LackOfPotions;
                            }
                            else
                            {
                                CostLabel->setColor(ccWHITE);
                            }
                                
                        }
                        
                    }
                    
                    
                    
                    
                    
                    arrIcon->addObject(sprite);
                    
                }
                
                
            }   

        }
    }
    
    
    buildLeve = pCentralScene->m_pCentralLayer->MAXmagicLevel();
    
//    num = 0;
    //魔法
//    for (int i = 0; i < 4; i++)
//    {
//        num++;
//        char strFileName[64];
//        
//        if (buildLeve>=num) 
//        {
//            CentralData::BuildableMagic* temp = pCentralScene->m_pCentralData->getBuildableMagic(num);
//            
//            const BaseSpellData* baseSpellData;
//            baseSpellData = GameData::GetDataFromBaseSpellData(temp->type * 100 + temp->leve);
//            
//            
//            if (buildLeve>=baseSpellData->SpellForgeLevel) 
//            {
//                
//                sprintf(strFileName,"soldiers_Icon%d.png",num);
//                
//                CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strFileName);
//                StateSprite* sprite = (StateSprite*)StateSprite::createWithSpriteFrame(spriteFrame);
//                
//                sprite->setPosition(ccp(60+i*90, 240-2*90));
//                
//                pCentralScene->m_pCentralInfoUILayer->addChild(sprite);
//                sprite->type = temp->type;
//                sprite->level = temp->leve;
//                sprite->state = IconState_normal;
//                
//                //等级不够
//                if (pCentralScene->m_pCentralLayer->m_building->lv < baseSpellData->LaboratoryLevel) 
//                {
//                    sprite->state = IconState_LevelLow;
//                }
//                
//                //金币
//                if ("Gold" == string(baseSpellData->UpgradeResource)) 
//                {
//                    if (pCentralScene->m_pCentralData->m_Central_UserData->user_gold < baseSpellData->UpgradeCost)
//                    {
//                        sprite->state = IconState_LackOfGold;
//                    }
//                }
//                //药水
//                else if("Elixir" == string(baseSpellData->UpgradeResource))
//                {
//                    if (pCentralScene->m_pCentralData->m_Central_UserData->user_potions < baseSpellData->UpgradeCost)
//                    {
//                        sprite->state = IconState_LackOfPotions;
//                    }
//                }
//                //宝石
//                else if("Diamonds" == string(baseSpellData->UpgradeResource))
//                {
//                    if (pCentralScene->m_pCentralData->m_Central_UserData->user_gem < baseSpellData->UpgradeCost)
//                    {
//                        sprite->state = IconState_LackOfGem;
//                    }
//                }
//                
//
//                
//                arrIconM->addObject(sprite);
//            }
//            
//        }   
//    }
    
    
}
void CentralInfoUILayer::infoBarracks()
{
    
    updateBarracks();
    
    updateLabel();
    
    updateBarracksState();
    
    sortingStateSprite();
    
    updatePeopleNum();
}
bool CentralInfoUILayer::inSpritePosition(CCSprite* _spr,CCPoint _point)
{
    if (_spr == NULL) return false;
    if (!_spr->isVisible()) return false;
    CCPoint pos = _spr->getPosition();
    CCPoint anchor = _spr->getAnchorPoint();
    
    CCRect r = CCRectMake(pos.x - _spr->getTextureRect().size.width*anchor.x,
                          pos.y - _spr->getTextureRect().size.height*anchor.y,
                          _spr->getTextureRect().size.width,
                          _spr->getTextureRect().size.height);
    
    
    if (r.origin.x<=_point.x&&_point.x<=r.origin.x+r.size.width&&
        r.origin.y<=_point.y&&_point.y<=r.origin.y+r.size.height)
    {
        return true;
    }
    
    return false;
}
void CentralInfoUILayer::updatePeopleNum()
{
    
    peopleNum = 0;
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    if (pCentralScene->m_pCentralLayer->m_building != NULL)
    {
        if (pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers != NULL)
        {
            for( int i = 0; i < (int)pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers->size(); i++ )
            {
                CentralData::BuildableSoldiers* temp = pCentralScene->m_pCentralData->getBuildableSoldiers(pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers->at(i)->tyep);
                const BasePeopleData* basePeopleData;
                basePeopleData = GameData::GetDataFromBasePeopleData(temp->type * PEOPLE_TYPE_ *100 + temp->leve);
                
                peopleNum+= (basePeopleData->HousingSpace*pCentralScene->m_pCentralLayer->m_building->m_peopleSoldiers->at(i)->num);
            }
        }
    }
    
    if (peopleNum >0)
    {
        char strFile[64];
        sprintf(strFile,"%d/%d",pCentralScene->m_pCentralData->m_Central_UserData->allPeopleNum,pCentralScene->m_pCentralData->m_Central_UserData->peopleNumMax);
        m_AllPeopleLabel->setString(strFile);
    }
    else
    {
        m_AllPeopleLabel->setString("");
    }
    
    
    
    
    
}
void CentralInfoUILayer::updateBarracks()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    int num = arrIcon->count();
    for (int i = 0; i < num; i++)
    {
        CCSprite* icon = (CCSprite*)arrIcon->objectAtIndex(i);
        this->removeChild(icon, false);
    }
    arrIcon->removeAllObjects();
    
    buildLeve = 0;
    
    if (pCentralScene->m_pCentralLayer->m_building != NULL){
        char strbiaoti[64];  
        sprintf(strbiaoti,"队列:%d/%d",pCentralScene->m_pCentralLayer->m_building->duileiNum,pCentralScene->m_pCentralLayer->m_building->duileiMAXNum);
        l_biaoti->setString(strbiaoti);
        
        buildLeve = pCentralScene->m_pCentralLayer->m_building->lv;
        
        const BaseBuildingLevelData* data = GameData::GetDataFromBaseBuildingLevelData(pCentralScene->m_pCentralLayer->m_building->getTypeID()*100+pCentralScene->m_pCentralLayer->m_building->lv);
        
        AllPeopleNum = data->UnitProduction;
    }
    
    num = 0;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GAME_FILE_TRANSFORM("soldiers_Icon",".plist").c_str(),GAME_FILE_TRANSFORM("soldiers_Icon",".png").c_str());
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            
            
            
            
            num++;
            CentralData::BuildableSoldiers* temp = pCentralScene->m_pCentralData->getBuildableSoldiers(num);
            
            
            
            
            
            char strFileName[64];
            char strFileNameDisabled[64];
            char strFileBg[64];
            sprintf(strFileName,"soldiers_Icon%d.png",num);
            sprintf(strFileNameDisabled,"soldiers_Icon_Disabled%d.png",num);
            
            StateSprite* sprite = NULL;
            if (buildLeve>=num) 
            {
                sprintf(strFileBg,"ui_public_bg3.png");
                sprite =(StateSprite*) CCSprite::createWithSpriteFrameName(strFileBg);
                sprite->setPosition(ccp(90+j*75, 154-i*75));
                
                //添加明图
                CCSprite* sprIcon = CCSprite::createWithSpriteFrameName(strFileName);
                sprIcon->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
                sprite->addChild(sprIcon,2,2);
                
                //添加暗框
                CCSprite* sprBg2 = CCSprite::createWithSpriteFrameName("ui_public_bg5.png");
                sprBg2->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
                sprite->addChild(sprBg2,3,3);
                
                //添加暗图
                CCSprite* sprIcon2 = CCSprite::createWithSpriteFrameName(strFileNameDisabled);
                sprIcon2->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
                sprite->addChild(sprIcon2,4,4);
                
                sprBg2->setVisible(false);
                sprIcon2->setVisible(false);

                
                CCLabelTTF *timeLabel = CCLabelTTF::create("", "Helvetica", sprite->getContentSize().height/4);
                timeLabel->setAnchorPoint(ccp(0,1));
                timeLabel->setPosition(ccp(0, sprite->getContentSize().height));
                sprite->addChild(timeLabel,100,1);
                
                if (temp != NULL)
                {
                    if (temp->leve > 1)
                    {
                        for (int n = 0; n < temp->leve; n++)
                        {
                            CCSprite* sprXing = CCSprite::createWithSpriteFrameName("ui_public_stars.png");
                            sprXing->setAnchorPoint(ccp(0,0));
                            sprXing->setPosition(ccp(3+9*n,6));
                            sprite->addChild(sprXing,105,5);
                            
                        }
                    }
                }
                
            }   
            else
            {
                const BasePeopleData* basePeopleDataL = NULL;
                basePeopleDataL = GameData::GetDataFromBasePeopleData(num * PEOPLE_TYPE_ * 100+ 1);
                
                sprintf(strFileBg,"ui_public_bg2.png");
                sprite =(StateSprite*) CCSprite::createWithSpriteFrameName(strFileBg);
                sprite->setPosition(ccp(90+j*75, 154-i*75));
                
                //添加暗图
                CCSprite* sprIcon2 = CCSprite::createWithSpriteFrameName(strFileNameDisabled);
                sprIcon2->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
                sprite->addChild(sprIcon2,4,4);
                
                
                char strBarrackLevel[64];
                sprintf(strBarrackLevel,"兵营%d级解锁",basePeopleDataL->BarrackLevel);
                
                CCLabelTTF *BarrackLevelLabel = CCLabelTTF::create(strBarrackLevel, "Helvetica", 12,CCSize(sprite->getContentSize().width*2/3, sprite->getContentSize().height*2/3),kCCTextAlignmentCenter);
                BarrackLevelLabel->setColor(ccBLACK);
                BarrackLevelLabel->setAnchorPoint(ccp(0.5,0.5));
                BarrackLevelLabel->setPosition(ccp(sprite->getContentSize().width/2+1, sprite->getContentSize().height/2-1));
                sprite->addChild(BarrackLevelLabel,100);
                CCLabelTTF *BarrackLevelLabel2 = CCLabelTTF::create(strBarrackLevel, "Helvetica", 12,CCSize(sprite->getContentSize().width*2/3, sprite->getContentSize().height*2/3),kCCTextAlignmentCenter);
                BarrackLevelLabel2->setAnchorPoint(ccp(0.5,0.5));
                BarrackLevelLabel2->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
                sprite->addChild(BarrackLevelLabel2,100);
                
                
            }
            
            
            CCSprite* sprinfoIcon = CCSprite::createWithSpriteFrameName("ui_public_infoIcon.png");
            sprinfoIcon->setAnchorPoint(ccp(1, 1));
            sprinfoIcon->setPosition(ccp(sprite->getContentSize().width, sprite->getContentSize().height));
            sprite->addChild(sprinfoIcon,101,101);
            
            
            pCentralScene->m_pCentralInfoUILayer->addChild(sprite);
            
            const BasePeopleData* basePeopleData = NULL;
            
            if (temp == NULL)
            {
                
                
                
            }
            else
            {
                basePeopleData = GameData::GetDataFromBasePeopleData(temp->type * PEOPLE_TYPE_ * 100+ temp->leve);
                sprite->type = temp->type;
                sprite->level = temp->leve;
                sprite->state = IconState_normal;
                
                
                //添加暗图
                CCSprite* sprbg = CCSprite::createWithSpriteFrameName("ui_public_bg6.png");
                sprbg->setAnchorPoint(ccp(0.5,0));
                sprbg->setPosition(ccp(sprite->getContentSize().width/2, 5));
                sprite->addChild(sprbg,100);
                
                
                
                CCSprite* sprwater = CCSprite::createWithSpriteFrameName("ui_public_icon_water.png");
                sprwater->setAnchorPoint(ccp(1,0.5));
                sprwater->setScale(0.7);
                sprwater->setPosition(ccp(sprbg->getContentSize().width, sprbg->getContentSize().height/2));
                sprbg->addChild(sprwater);
                
                CCLabelTTF *CostLabel = CCLabelTTF::create(CommonResource::getStringFromInt(basePeopleData->TrainingCost).c_str(), "Helvetica", 12);
                CostLabel->setAnchorPoint(ccp(1,0.5));
                CostLabel->setPosition(ccp(sprbg->getContentSize().width-sprwater->getContentSize().width*sprwater->getScaleX(), sprbg->getContentSize().height/2));
                sprbg->addChild(CostLabel);
            }
            
            
           
            //等级不够
            if (basePeopleData == NULL) 
            {
                sprite->stableState  = IconState_LevelLow;
            }
            arrIcon->addObject(sprite);
        }
    }
    
    
}
void CentralInfoUILayer::onUpDataLevel()
{
    upMroS(m_spriteNum,isMroS);
}
void CentralInfoUILayer::onnextBtn()
{
    switch (m_type)
    {
        case ARMY_BARRACK:
        {
            allinfoUINo();
            HuiFuBarracks();
        }
            break;
        case ARMY_LABORATORY:
        {
            allinfoUINo();
            huifuUpSoldiers();
        }
            break;
        case ARMY_SPELLFORGE:
        {
            
        }
            break;
        default:
            break;
    }
    
}
void CentralInfoUILayer::CloseInfoUI()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    this->removeFromParentAndCleanup(false);
    
    
    pCentralScene->m_pCentralLayer->isUPSoldiers = false;
    pCentralScene->m_pCentralLayer->uploadRecruiting();
    pCentralScene->m_pCentralLayer->isJianSoldiers = false;
    pCentralScene->m_pCentralLayer->jianloadRecruiting();
    
    
    pCentralScene->m_pCentralInfoUILayer = NULL;
}
void CentralInfoUILayer::upMroS(int _tyep, bool isMroS)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    if (pCentralScene->m_pCentralLayer->m_building != NULL)
    {

        const BaseSpellData* baseSpellData;
        const BasePeopleData* basePeopleData;
        StateSprite * tempS = (StateSprite*)m_Sprite;
        if (isMroS)
        {
            baseSpellData = GameData::GetDataFromBaseSpellData(tempS->type * 100 + tempS->level);
            
            pCentralScene->m_pCentralLayer->m_building->upLeveMagicSoldiers(_tyep,isMroS,baseSpellData->UpgradeTimeH*60*60);
        }
        else
        {
            basePeopleData = GameData::GetDataFromBasePeopleData(tempS->type * PEOPLE_TYPE_*100 + tempS->level);
            pCentralScene->m_pCentralLayer->m_building->upLeveMagicSoldiers(_tyep,isMroS,basePeopleData->UpgradeTimeH*60*60);

        }

        //切换场景
        allinfoUINo();
        
        infoUpSoldiersing();
        
    }
}
void CentralInfoUILayer::addMagic(int _tyep)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    if (pCentralScene->m_pCentralLayer->m_building != NULL)
    {
        pCentralScene->m_pCentralLayer->m_building->addMagicBuild(_tyep);
    }
}
void CentralInfoUILayer::addBing()
{
    StateSprite * tempS = (StateSprite*)m_Sprite;
    if (tempS->stableState == IconState_LevelLow)
    {
        return;
    }
    
    switch (tempS->state)
    {
        case IconState_normal:
        {
            CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
            CentralData::BuildableSoldiers* temp = pCentralScene->m_pCentralData->getBuildableSoldiers(m_spriteNum);
            const BasePeopleData* basePeopleData;
            basePeopleData = GameData::GetDataFromBasePeopleData(m_spriteNum * PEOPLE_TYPE_ *100 + temp->leve);
            //                        if(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->matchingCampfire(basePeopleData->HousingSpace)){
            if (pCentralScene->m_pCentralLayer->m_building->duileiNum+basePeopleData->HousingSpace <= pCentralScene->m_pCentralLayer->m_building->duileiMAXNum)
            {
                onInfoBtnRecruiting1(m_spriteNum);
                updateBarracksState();
            }

        }
            break;
        case IconState_LevelLow:
        {
            
        }
            break;
        case IconState_LackOfGold:
        {
            
        }
            break;
        case IconState_LackOfPotions:
        {
            
        }
            break;
        case IconState_LackOfGem:
        {
            
        }
            break;
        case IconState_ToOpen:
        {
            
        }
            break;
        default:
            break;
    }
}
void CentralInfoUILayer::jianBing()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    if (!pCentralScene->m_pCentralLayer->isJianSoldiers)
    {
        pCentralScene->m_pCentralLayer->isUPSoldiers = false;
        pCentralScene->m_pCentralLayer->uploadRecruiting();
        //                    pCentralScene->m_pCentralLayer->jianloadRecruiting();
    }
    StateSprite * tempS = (StateSprite*)m_SpriteA;
    if (tempS != NULL)
    {
        SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->m_building->jianSoldiers(tempS->type);
        
        
        if (!pCentralScene->m_pCentralLayer->isJianSoldiers)
        {
            pCentralScene->m_pCentralLayer->jianloadSoldiersTime = 0;
            pCentralScene->m_pCentralLayer->isJianSoldiers = true;
            
            pCentralScene->m_pCentralLayer->isUPSoldiers = false;
            pCentralScene->m_pCentralLayer->uploadRecruiting();
            //                    pCentralScene->m_pCentralLayer->jianloadRecruiting();
        }
        
        updateBarracksState();
    }
    
}
void CentralInfoUILayer::updata(float _time)
{
    switch (m_type)
    {
        case ARMY_BARRACK:
        {
            if (isaddbing)
            {
                addbing_time+=_time;
                if (addbing_time>0.5&&addbing_time<1)
                {
                    addbing_time = 1.0f;
                }
                else if (addbing_time>=1.1f)
                {
                    addbing_time = 1.0f;
                    addBing();
                }
            }
            
            if (isjianbing)
            {
                jianbing_time+=_time;
                if (jianbing_time>0.5&&jianbing_time<1)
                {
                    jianbing_time = 1.0f;
                }
                else if (jianbing_time>=1.1f)
                {
                    jianbing_time = 1.0f;
                    jianBing(); //崩溃
                }
            }
            CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;

            char strbiaoti[64];
            sprintf(strbiaoti,"队列:%d/%d",pCentralScene->m_pCentralLayer->m_building->duileiNum,pCentralScene->m_pCentralLayer->m_building->duileiMAXNum);
            l_biaoti->setString(strbiaoti);
        }
            break;
            
    }
}
void CentralInfoUILayer::sortingStateSprite()
{
    for (int i = 0; i < arrAIcon->count(); i++ )
    {
        CCSprite* spr = (CCSprite*)arrAIcon->objectAtIndex(i);
        spr->removeFromParentAndCleanup(false);
        if (i < 5)
        {
            if (i<1)
            {
                CCNode* article0 = spr->getChildByTag(2);
                CCNode* article1 = spr->getChildByTag(3);
                CCNode* lab = spr->getChildByTag(4);
                if (article0 != NULL)
                {
                    article0->setVisible(true);
                    article1->setVisible(true);
                    lab->setVisible(true);
                }
                
            }
            spr->setPosition(ccp(310-60*i,230));
            this->addChild(spr);
        }
    }
    
}
void CentralInfoUILayer::addStateSprite(int _tyep)
{
    char strFileName[64];
    
    sprintf(strFileName,"soldiers_Icon%d.png",_tyep);
    
    StateSprite* sprite =(StateSprite*) CCSprite::createWithSpriteFrameName(strFileName);
    sprite->setScale(0.7);
    sprite->type = _tyep;
    this->addChild(sprite);
    
    
    CCLabelTTF *timeLabel = CCLabelTTF::create("", "Helvetica", sprite->getContentSize().height/4);
    timeLabel->setAnchorPoint(ccp(0,1));
    timeLabel->setPosition(ccp(0, sprite->getContentSize().height));
    sprite->addChild(timeLabel,100,1);
    
    timeLabel->setString("1");
    
    CCSprite* strj = CCSprite::createWithSpriteFrameName("ui_public_btn_minus.png");
    strj->setAnchorPoint(ccp(1,1));
    strj->setPosition(ccp(sprite->getContentSize().width, sprite->getContentSize().height));
    sprite->addChild(strj);
    
    CCSprite* article0 = CCSprite::createWithSpriteFrameName("ui_public_article0.png");
    article0->setAnchorPoint(ccp(0,0));
    article0->setPosition(ccp(0, 0));
    sprite->addChild(article0,2,2);
    CCSprite* article1 = CCSprite::createWithSpriteFrameName("ui_public_article1.png");
    article1->setAnchorPoint(ccp(0,0));
    article1->setPosition(ccp(0, 0));
    sprite->addChild(article1,3,3);
    CCLabelTTF* article = CCLabelTTF::create("", "Helvetica", article0->getContentSize().height);
    article->setAnchorPoint(ccp(0.5,0.5));
    article->setPosition(ccp(article0->getContentSize().width/2, article0->getContentSize().height/2));
    sprite->addChild(article,4,4);
    
    article->setVisible(false);
    article0->setVisible(false);
    article1->setVisible(false);
    article->setScale(1.42);
    article0->setScale(1.42);
    article1->setScale(1.42);
    
    arrAIcon->addObject(sprite);
}
StateSprite* CentralInfoUILayer::getState(int _tyep)
{
    StateSprite* state = NULL;
    
    for (int i = 0; i < arrAIcon->count(); i++)
    {
        StateSprite* spr = (StateSprite*)arrAIcon->objectAtIndex(i);
        if (spr->type == _tyep)
        {
            state = spr;
            break;
        }
    }
    
    return state;
    
}
void CentralInfoUILayer::onInfoBtnRecruiting1(int _tyep)
{
    //创建兵
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    if (pCentralScene->m_pCentralLayer->m_building != NULL)
    {
        pCentralScene->m_pCentralLayer->m_building->addSoldiers(_tyep);
        
        
        
        if (!pCentralScene->m_pCentralLayer->isUPSoldiers) 
        {
            pCentralScene->m_pCentralLayer->isUPSoldiers = true;
            pCentralScene->m_pCentralLayer->uploadRecruiting();
            
            pCentralScene->m_pCentralLayer->isJianSoldiers = false;
            pCentralScene->m_pCentralLayer->jianloadRecruiting();
        }
        pCentralScene->m_pCentralLayer->uploadSoldiersTime = 0;
    }
    
}

SEL_MenuHandler CentralInfoUILayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget,CCString * pSelectorName){
    
    //Bind Menu Events，绑定一个menu，点击方法是press，以下同理
    
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "press",MainScene::press);
    
    return NULL;
    
}

SEL_CCControlHandler CentralInfoUILayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName){
    //Bind CCControl Events
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnInfoCancel",CentralInfoUILayer::CloseInfoUI);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onnextBtn",CentralInfoUILayer::onnextBtn);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onUpDataLevel",CentralInfoUILayer::onUpDataLevel);

    return NULL;
}

bool CentralInfoUILayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode){
    
    //Bind variables
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_bgl1", CCSprite *, this->s_bgl1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_bgl2", CCSprite *, this->s_bgl2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_bgl3", CCSprite *, this->s_bgl3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_biaoti", CCLabelTTF *, this->l_biaoti);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_tishi", CCLabelTTF *, this->l_tishi);
    
    
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info1", CCLabelTTF *, this->l_info1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info2", CCLabelTTF *, this->l_info2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info3", CCLabelTTF *, this->l_info3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_mubiao", CCLabelTTF *, this->l_info_mubiao);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_leixing", CCLabelTTF *, this->l_info_leixing);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_duixiang", CCLabelTTF *, this->l_info_duixiang);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_renkou", CCLabelTTF *, this->l_info_renkou);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_shijian", CCLabelTTF *, this->l_info_shijian);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_shudu", CCLabelTTF *, this->l_info_shudu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_mubiaonum", CCLabelTTF *, this->l_info_mubiaonum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_leixingnum", CCLabelTTF *, this->l_info_leixingnum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_duixiangnum", CCLabelTTF *, this->l_info_duixiangnum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_renkounum", CCLabelTTF *, this->l_info_renkounum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_shijiannum", CCLabelTTF *, this->l_info_shijiannum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_shudunum", CCLabelTTF *, this->l_info_shudunum);
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_icon1", CCSprite *, this->s_info_icon1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_bg1", CCSprite *, this->s_info_bg1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info1", CCSprite *, this->s_info1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_lbg1", CCSprite *, this->s_info_lbg1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_icon2", CCSprite *, this->s_info_icon2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_icon2", CCSprite *, this->s_info_icon2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_bg2", CCSprite *, this->s_info_bg2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info2", CCSprite *, this->s_info2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_lbg2", CCSprite *, this->s_info_lbg2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_icon3", CCSprite *, this->s_info_icon3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_bg3", CCSprite *, this->s_info_bg3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info3", CCSprite *, this->s_info3);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_lbg3", CCSprite *, this->s_info_lbg3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_lbg", CCSprite *, this->s_info_lbg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_tubg", CCSprite *, this->s_info_tubg);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nextBtn", CCControlButton *, this->nextBtn);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_time", CCLabelTTF *, this->l_info_time);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_info_timebiaoti", CCLabelTTF *, this->l_info_timebiaoti);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_info_timebg", CCSprite *, this->s_info_timebg);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "updatalevel", CCControlButton *, this->updatalevel);
    
    return false;
    
}

void CentralInfoUILayer::onNodeLoaded(CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader){
    
    //检测scene
    
    CCLOG("MainScene loading.....successed!") ;
    
}

