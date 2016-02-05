#include "BuildingBase.h"
#include "GameControl.h"
#include "TipNode.h"
#include "Until.h"
#include "CommonResource.h"
#include "NetMessageManager.h"


std::string BuildingBase::calculation_d_h_m_s(long _time)
{
    char strTime[64];
    
    int d = 0;
    int h = 0;
    int m = 0;
    int s = 0;
    
    //有多少秒
    int time = _time;
    
    if (time != 0)
    {
        s = time%60;
        time = time/60;
        
        m = time%60;
        time = time/60;
        
        h = time%24;
        time = time/24;
        
        d = time;
    }
    
    if (d!=0)
    {
        if (h==0)
        {
            sprintf(strTime, "%dd",d);
        }
        else
        {
            sprintf(strTime, "%dd%dh",d,h);
        }
    }
    else if (h!=0)
    {
        if (m==0)
        {
            sprintf(strTime, "%dh",h);
        }
        else
        {
            sprintf(strTime, "%dh%dm",h,m);
        }
    }
    else if (m!=0)
    {
        if (s==0)
        {
            sprintf(strTime, "%dm",m);
        }
        else
        {
            sprintf(strTime, "%dm%ds",m,s);
        }
    }
    else if (s!=0)
    {
        sprintf(strTime, "%ds",s);
    }
    else
    {
        sprintf(strTime, "");
    }
    
    std::string sTime = strTime;
    return sTime;
}

void BuildingBase::UpdataBuilding(float dt)
{
    //建筑的时间循环
    if (upgrade_state_ == UNIT_UPGRADE_NONE)
    {
        //建筑功能记时
        switch (m_uTypeID)
        {
            case RESOURCE_ELIXIRPUMP:
            {
                if (resourcesPotionsNum == resourcesMaxNum) return;
                long tempTime = Until::millisecondNow_m();
                
                long cd_time = tempTime - buildEventTime;
                
                int  cd_time_d = cd_time;
                
                resourcesPotionsNum =   cd_time_d * resourcesCDNum /  3600;
                
                
                if(isHarvest)
                {
                    if (resourcesPotionsNum>resourcesMaxNum)
                    {
                        resourcesPotionsNum = resourcesMaxNum;
                    }
                }
                else
                {
                    if (tempTime - buildxiaoguoEventTime>20)
                    {
                        isHarvest = true;
                        //显示提示效果
                        
                        tipNode = TipNode::create();
                        tipNode->initTipNode(m_uTypeID,false,this);
                        tipNode->setPosition(sprite_->getContentSize().width/2, sprite_->getContentSize().height-20);
                        tipNode->setScale(1);
                        tipNode->building = this;
                        sprite_->addChild(tipNode);
                        
                        
                    }
                    
                }
            }
                break;
            case RESOURCE_GOLDMINE:
            {
                if (resourcesGoldNum == resourcesMaxNum) return;
                long tempTime = Until::millisecondNow_m();
                
                long cd_time = tempTime - buildEventTime;
                
                int  cd_time_d = cd_time;
                
                resourcesGoldNum =   cd_time_d * resourcesCDNum /  3600;
                
                
                if(isHarvest)
                {
                    if (resourcesGoldNum>resourcesMaxNum)
                    {
                        resourcesGoldNum = resourcesMaxNum;
                    }
                }
                else
                {
                    if (tempTime - buildxiaoguoEventTime>20)
                    {
                        isHarvest = true;
                        //显示提示效果
                        
                        tipNode = TipNode::create();
                        tipNode->initTipNode(m_uTypeID,false,this);
                        tipNode->setPosition(sprite_->getContentSize().width/2, sprite_->getContentSize().height-20);
                        tipNode->setScale(1);
                        sprite_->addChild(tipNode);
                        
                    }
                    
                }
            }
                break;
            case ARMY_BARRACK:
            {
                if (!isSafety) return;
                
                if (m_peopleSoldiers != NULL)
                {
                    if ((int)m_peopleSoldiers->size() > 0)
                    {
                        CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
                        PeopleSoldiers* soldiers = m_peopleSoldiers->at(0);
                        
                        if (soldiers->time == 0)
                        {
                            soldiers->time = Until::millisecondNow_m();
                        }
                        
                        
                        if (tipNode == NULL)
                        {
                            if (isManNum)
                            {
                                //展示动画
                                tipNode = TipNode::create();
                                tipNode->zhuangtaiType = 2;
                                tipNode->initTipNode(ARMY_BARRACK,false,this);
                                tipNode->setPosition(ccp((sprite_->getContentSize().width/2 - tipNode->sprite_->getContentSize().width/2), sprite_->getContentSize().height));
                                sprite_->addChild(tipNode);
                            }
                            else
                            {
                                //展示动画
                                tipNode = TipNode::create();
                                tipNode->zhuangtaiType = 1;
                                tipNode->initTipNode(ARMY_BARRACK,false,this);
                                tipNode->setPosition(ccp((sprite_->getContentSize().width/2 - tipNode->sprite_->getContentSize().width/2), sprite_->getContentSize().height));
                                sprite_->addChild(tipNode);
                                tipNode->upXiaoIcon(soldiers->tyep);
                            }
                            
                        }
                        else
                        {
                            if (isManNum)
                            {
                                if (tipNode->zhuangtaiType != 2)
                                {
                                    tipNode->upZhuangtaiTyep(2);
                                }
                                
                            }
                            else
                            {
                                if (tipNode->zhuangtaiType != 1)
                                {
                                    tipNode->upZhuangtaiTyep(1);
                                    tipNode->upXiaoIcon(soldiers->tyep);
                                }
                                else
                                {
                                    if (tipNode->sIconType != soldiers->tyep)
                                    {
                                        tipNode->upXiaoIcon(soldiers->tyep);
                                    }
                                    
                                    
                                    
                                }
                            }
                        }
                        
                        
                        
                        long tempTime = Until::millisecondNow_m();
                        
                        long cd_time = tempTime - soldiers->time;
                        
                        int  cd_time_d = cd_time;
                        
                        
                        if (!isManNum)
                        {
                            allProductionTime -= dt;
                            
                            if (pCentralScene->m_pCentralInfoUILayer != NULL)
                            {
                                if (pCentralScene->m_pCentralInfoUILayer->m_type == ARMY_BARRACK)
                                {
                                    if (pCentralScene->m_pCentralLayer->m_building != NULL)
                                    {
                                        if (pCentralScene->m_pCentralLayer->m_building->getuuID() == m_uuID)
                                        {
                                            if (!pCentralScene->m_pCentralInfoUILayer->iserJi)
                                            {
                                                pCentralScene->m_pCentralInfoUILayer->updateSpeedUp();
                                                pCentralScene->m_pCentralInfoUILayer->m_AllTimeLabel->setString(calculation_d_h_m_s(allProductionTime).c_str());
                                                pCentralScene->m_pCentralInfoUILayer->s_bgl1->setVisible(true);
                                                pCentralScene->m_pCentralInfoUILayer->s_bgl3->setVisible(true);
                                            }
                                            
                                        }
                                    }
                                    
                                    
                                }
                            }
                        }
                        
                        
                        
                        if (cd_time_d >= soldiers->MAXTime)
                        {
                            const BasePeopleData* pdata = GameData::GetDataFromBasePeopleData(soldiers->tyep * 100000+1);
                            //营火是否满员
                            if (pCentralScene->m_pCentralData->m_Central_UserData->allYouPeopleNum+pdata->HousingSpace <= pCentralScene->m_pCentralData->m_Central_UserData->peopleNumMax)
                            {
                                isManNum = false;
                                duileiNum-=pdata->HousingSpace;
                                pCentralScene->m_pCentralData->m_Central_UserData->allYouPeopleNum += pdata->HousingSpace;
                                soldiers->num -= 1;
                                
                                
                                if (!pCentralScene->m_pCentralLayer->matchingCampfire(pdata->HousingSpace, GetCenterPos())) {
                                    //临时
                                    if (tipNode != NULL)
                                    {
                                        //回收动画
                                        tipNode->removeFromParentAndCleanup(false);
                                        tipNode = NULL;
                                    }
                                    return;
                                }
                                
                                Unit* u = pCentralScene->m_pCentralLayer->AddPeople(soldiers->tyep * 100000 +1, this->getPosition(),NULL);
                                u->unit_ai_cmd_ = UNIT_AI_PATROL;
                                
                                for (int i=0; i<pCentralScene->m_pCentralData->m_BuildableSoldiers->size(); i++) {
                                    CentralData::BuildableSoldiers* s = pCentralScene->m_pCentralData->m_BuildableSoldiers->at(i);
                                    if (s->type == soldiers->tyep) {
                                        s->num++;
                                        break;
                                    }
                                }
                                
                                
                                
                                if (pCentralScene->m_pCentralInfoUILayer != NULL)
                                {
                                    if (pCentralScene->m_pCentralInfoUILayer->m_type == ARMY_BARRACK)
                                    {
                                        
                                        if (pCentralScene->m_pCentralLayer->m_building != NULL)
                                        {
                                            if (pCentralScene->m_pCentralLayer->m_building->getuuID() == m_uuID)
                                            {
                                                if (pCentralScene->m_pCentralInfoUILayer->arrIcon != NULL)
                                                {
                                                    CCSprite* icon = (CCSprite*)pCentralScene->m_pCentralInfoUILayer->arrIcon->objectAtIndex(soldiers->tyep-1);
                                                    
                                                    CCLabelTTF *timeLabel = (CCLabelTTF*)icon->getChildByTag(1);
                                                    
                                                    if (soldiers->num == 0)
                                                    {
                                                        timeLabel->setString("");
                                                    }
                                                    else
                                                    {
                                                        timeLabel->setString(CommonResource::getStringFromInt(soldiers->num).c_str());
                                                    }
                                                    
                                                    
                                                }
                                                
                                                
                                                if (pCentralScene->m_pCentralInfoUILayer->arrAIcon != NULL)
                                                {
                                                    StateSprite* icon = pCentralScene->m_pCentralInfoUILayer->getState(soldiers->tyep);
                                                    if (icon != NULL)
                                                    {
                                                        CCLabelTTF *timeLabel = (CCLabelTTF*)icon->getChildByTag(1);
                                                        
                                                        if (soldiers->num == 0)
                                                        {
                                                            if (pCentralScene->m_pCentralInfoUILayer->m_SpriteA != NULL)
                                                            {
                                                                pCentralScene->m_pCentralInfoUILayer->m_SpriteA = NULL;
                                                            }
                                                            icon->removeFromParentAndCleanup(false);
                                                            pCentralScene->m_pCentralInfoUILayer->arrAIcon->removeObject(icon);
                                                            pCentralScene->m_pCentralInfoUILayer->sortingStateSprite();
                                                        }
                                                        else
                                                        {
                                                            timeLabel->setString(CommonResource::getStringFromInt(soldiers->num).c_str());
                                                        }
                                                        
                                                    }
                                                    
                                                }
                                            }
                                        }
                                        
                                        
                                        
                                    }
                                    
                                }
                                
                                
                                if (soldiers->num > 0)
                                {
                                    soldiers->time = Until::millisecondNow_m();
                                    //生产出兵
                                    
                                }
                                else
                                {
                                    //
                                    delete m_peopleSoldiers->at(0);
                                    m_peopleSoldiers->erase(m_peopleSoldiers->begin());
                                    
                                }
                                
                                if (pCentralScene->m_pCentralInfoUILayer != NULL)
                                {
                                    if (pCentralScene->m_pCentralInfoUILayer->m_type == ARMY_BARRACK)
                                    {
                                        if (pCentralScene->m_pCentralLayer->m_building != NULL)
                                        {
                                            if (pCentralScene->m_pCentralLayer->m_building->getuuID() == m_uuID)
                                            {
                                                if (!pCentralScene->m_pCentralInfoUILayer->iserJi)
                                                {
                                                    pCentralScene->m_pCentralInfoUILayer->updateSpeedUp();
                                                    pCentralScene->m_pCentralInfoUILayer->m_AllTimeLabel->setString(calculation_d_h_m_s(allProductionTime).c_str());
                                                    pCentralScene->m_pCentralInfoUILayer->updatePeopleNum();
                                                    pCentralScene->m_pCentralInfoUILayer->s_bgl1->setVisible(true);
                                                    pCentralScene->m_pCentralInfoUILayer->s_bgl3->setVisible(true);
                                                }
                                                
                                            }
                                        }
                                        
                                    }
                                }
                                
                            }
                            else
                            {
                                isManNum = true;
                            }
                            
                        }
                        else
                        {
                            if (soldiers && soldiers->MAXTime)
                            {
                                //更新进度条
                                float fl = (float)cd_time_d/(float)(soldiers->MAXTime);
                                string strTime = calculation_d_h_m_s(soldiers->MAXTime - cd_time_d);
                                tipNode->upProgressBar(fl);
                                tipNode->upTimeLabel(strTime.c_str());
                                
                                
                                if (pCentralScene->m_pCentralInfoUILayer != NULL)
                                {
                                    if (pCentralScene->m_pCentralInfoUILayer->m_type == ARMY_BARRACK)
                                    {
                                        if (pCentralScene->m_pCentralInfoUILayer->arrAIcon != NULL)
                                        {
                                            StateSprite* icon = pCentralScene->m_pCentralInfoUILayer->getState(soldiers->tyep);
                                            if (icon != NULL)
                                            {
                                                CCLabelTTF *articleLabel = (CCLabelTTF*)icon->getChildByTag(4);
                                                CCSprite *article = (CCSprite*)icon->getChildByTag(3);
                                                
                                                if (articleLabel != NULL && article != NULL)
                                                {
                                                    article->setScaleX(fl*1.42);
                                                    articleLabel->setString(strTime.c_str());
                                                }
                                                
                                            }
                                            
                                        }
                                    }
                                    
                                }
                                
                                
                            }
                        }
                        
                        
                        
                        
                    }
                    else
                    {
                        if (tipNode == NULL)
                        {
                            //展示动画
                            tipNode = TipNode::create();
                            tipNode->zhuangtaiType = 3;
                            tipNode->initTipNode(ARMY_BARRACK,false,this);
                            tipNode->setPosition(ccp((sprite_->getContentSize().width/2 - tipNode->sprite_->getContentSize().width/2), sprite_->getContentSize().height));
                            sprite_->addChild(tipNode);
                        }
                        else
                        {
                            if (tipNode->zhuangtaiType != 3)
                            {
                                tipNode->upZhuangtaiTyep(3);
                                allProductionTime = 0;
                            }
                            
                        }
                    }
                }
                else
                {
                    if (tipNode == NULL)
                    {
                        //展示动画
                        tipNode = TipNode::create();
                        tipNode->zhuangtaiType = 3;
                        tipNode->initTipNode(ARMY_BARRACK,false,this);
                        tipNode->setPosition(ccp((sprite_->getContentSize().width/2 - tipNode->sprite_->getContentSize().width/2), sprite_->getContentSize().height));
                        sprite_->addChild(tipNode);
                    }
                    else
                    {
                        if (tipNode->zhuangtaiType != 3)
                        {
                            tipNode->upZhuangtaiTyep(3);
                        }
                        
                    }
                }
            }
                break;
            case ARMY_SPELLFORGE:
            {
                if (m_magicBuild != NULL)
                {
                    if ((int)m_magicBuild->size() > 0)
                    {
                        magicBuild* soldiers = m_magicBuild->at(0);
                        
                        if (soldiers->time == 0)
                        {
                            soldiers->time = Until::millisecondNow_m();
                        }
                        
                        if (tipNode == NULL)
                        {
                            //展示动画
                            tipNode = TipNode::create();
                            tipNode->initTipNode(ARMY_SPELLFORGE,false,this);
                            tipNode->setScale(1);
                            tipNode->setPosition(0, sprite_->getContentSize().height);
                            sprite_->addChild(tipNode);
                        }
                        
                        
                        
                        long tempTime = Until::millisecondNow_m();
                        
                        long cd_time = tempTime - soldiers->time;
                        
                        int  cd_time_d = cd_time;
                        
                        if (cd_time_d > soldiers->MAXTime)
                        {
                            soldiers->num -= 1;
                            CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
                            
                            if (pCentralScene->m_pCentralInfoUILayer != NULL)
                            {
                                
                                if (pCentralScene->m_pCentralInfoUILayer->arrIcon != NULL)
                                {
                                    CCSprite* icon = (CCSprite*)pCentralScene->m_pCentralInfoUILayer->arrIcon->objectAtIndex(soldiers->tyep-1);
                                    
                                    CCLabelTTF *timeLabel = (CCLabelTTF*)icon->getChildByTag(1);
                                    if (soldiers->num == 0)
                                    {
                                        timeLabel->setString("");
                                    }
                                    else
                                    {
                                        timeLabel->setString(CommonResource::getStringFromInt(soldiers->num).c_str());
                                    }
                                    
                                    
                                }
                            }
                            //生产魔法
                            for( int i = 0; i < (int)pCentralScene->m_pCentralData->m_BuildableMagic->size(); i++ )
                            {
                                if (pCentralScene->m_pCentralData->m_BuildableMagic->at(i)->type == soldiers->tyep)
                                {
                                    pCentralScene->m_pCentralData->m_BuildableMagic->at(i)->num += 1;
                                }
                            }
                            
                            
                            if (soldiers->num > 0)
                            {
                                soldiers->time = Until::millisecondNow_m();
                                
                                
                            }
                            else
                            {
                                //临时
                                delete m_magicBuild->at(0);
                                m_magicBuild->erase(m_magicBuild->begin());
                                
                                
                                
                            }
                            
                            
                        }
                        else
                        {
                            if (soldiers && soldiers->MAXTime)
                            {
                                //更新进度条
                                float fl = (float)cd_time_d/(float)(soldiers->MAXTime);
                                tipNode->upProgressBar(fl);
                                tipNode->upTimeLabel(calculation_d_h_m_s(soldiers->MAXTime - cd_time_d).c_str());
                            }
                        }
                        
                    }
                    else
                    {
                        //临时
                        if (tipNode != NULL)
                        {
                            //回收动画
                            tipNode->removeFromParentAndCleanup(false);
                            tipNode = NULL;
                        }
                    }
                    
                }
                
            }
                break;
            case ARMY_LABORATORY:
            {
                if (UpLeveTyep != 0)
                {
                    
                    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
                    
                    if (tipNode == NULL)
                    {
                        //展示动画
                        tipNode = TipNode::create();
                        tipNode->initTipNode(ARMY_LABORATORY,false,this);
                        tipNode->setScale(1);
                        tipNode->setPosition(0, sprite_->getContentSize().height);
                        sprite_->addChild(tipNode);
                    }
                    long tempTime = Until::millisecondNow_m();
                    
                    long cd_time = tempTime - UpLeveTime;
                    
                    int  cd_time_d = cd_time;
                    
                    
                    
                    
                    
                    if (cd_time_d > UPLeveCDTime)
                    {
                        //升级成功
                        if (tipNode != NULL)
                        {
                            //回收动画
                            tipNode->removeFromParentAndCleanup(false);
                            tipNode = NULL;
                        }
                        
                        upLeveComplete(UpLeveTyep);
                        
                        UpLeveTyep = 0;
                        
                    }
                    else
                    {
                        if (tipNode != NULL)
                        {
                            //更新进度条
                            float fl = (float)cd_time_d/(float)UPLeveCDTime;
                            tipNode->upProgressBar(fl);
                            string strTime = calculation_d_h_m_s(UPLeveCDTime - cd_time_d);
                            tipNode->upTimeLabel(strTime.c_str());
                            
                            
                            
                            
                            if (pCentralScene->m_pCentralInfoUILayer != NULL)
                            {
                                if (pCentralScene->m_pCentralInfoUILayer->m_type == ARMY_LABORATORY)
                                {
                                    if (pCentralScene->m_pCentralInfoUILayer->btn_SpeedUp != NULL)
                                    {
                                        CCLabelTTF *timeLabel = (CCLabelTTF*)pCentralScene->m_pCentralInfoUILayer->btn_SpeedUp->getChildByTag(1);
                                        if (timeLabel != NULL)
                                        {
                                            int gem = pCentralScene->m_pCentralLayer->gemConversion(UPLeveCDTime - cd_time_d);
                                            timeLabel->setString(CommonResource::getStringFromInt(gem).c_str());
                                            
                                            pCentralScene->m_pCentralInfoUILayer->m_timeLabel->setString(strTime.c_str());
                                        }
                                        
                                    }
                                }
                                
                            }
                        }
                    }
                    
                    
                }
                
                
                
            }
                break;
            case ARMY_TROOPHOUSING:
            {
                //营火是否满员
                CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
                if (pCentralScene->m_pCentralData->m_Central_UserData->allYouPeopleNum == pCentralScene->m_pCentralData->m_Central_UserData->peopleNumMax)
                {
                    if (tipNode == NULL)
                    {
                        //展示动画
                        tipNode = TipNode::create();
                        tipNode->initTipNode(ARMY_TROOPHOUSING,false,this);
                        tipNode->setPosition(ccp(sprite_->getContentSize().width/2, sprite_->getContentSize().height));
                        sprite_->addChild(tipNode);
                    }
                    
                }
                else
                {
                    if (tipNode != NULL)
                    {
                        //展示动画
                        tipNode->removeFromParentAndCleanup(false);
                        tipNode = NULL;
                    }
                }
                
            }
                break;
                
            default:
                break;
        }
    }
    else if (upgrade_state_ == UNIT_UPGRADE_START)
    {
        SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralUILayer->updatePeasant();
        
        if (savsTime < 1 )
        {
            m_uBuildTime = Until::millisecondNow_m();
        }
        else
        {
            m_uBuildTime = savsTime;
        }
        
        //减少资源消耗
        
        
        //回收操作
        if (tipNode != NULL)
        {
            //回收动画
            tipNode->removeFromParentAndCleanup(false);
            tipNode = NULL;
        }
        
        
        //展示动画
        tipNode = TipNode::create();
        tipNode->initTipNode(BUILDINGTYPE_NOGAIN,true,this);
        tipNode->setPosition(ccp((sprite_->getContentSize().width/2 - tipNode->sprite_->getContentSize().width/2), sprite_->getContentSize().height));
        tipNode->setScale(1);
        sprite_->addChild(tipNode);
        if (m_stBuildSubstrate.m_Line != 1)
        {
            char strWei[64] = {0};
            sprintf(strWei,"build_weidang_%d_%d",m_stBuildSubstrate.m_Line,m_stBuildSubstrate.m_Row);
            CCSprite * sprWei = CCSprite::create(GAME_FILE_TRANSFORM(strWei,".png").c_str());
            sprWei->setPosition(ccp(sprite_->getContentSize().width/2, sprite_->getContentSize().height/2));
            sprite_->addChild(sprWei,10,10);
        }
        
        
        nameLabel->setPosition(ccp(sprite_->getContentSize().width/2, sprite_->getContentSize().height+80));
        
        if (savsTime < 1)
        {
            CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
            pCentralScene->m_pCentralLayer->buildingAccount(this,OperateType_UpgradeBuilding);
        }
        
        //更改升级状态
        upgrade_state_ = UNIT_UPGRADE_IN;
    }
    else if (upgrade_state_ == UNIT_UPGRADE_IN)
    {
        long tempTime = Until::millisecondNow_m();
        
        long cd_time = tempTime - m_uBuildTime;
        
        int  cd_time_d = cd_time;
        
        //判断是否时间到
        if (m_iBuildCDTime <= cd_time_d)
        {
            
            //更改升级状态
            upgrade_state_ = UNIT_UPGRADE_SUCESS;
            
            
        }
        else
        {
            //更新进度条
            tipNode->upProgressBar((float)cd_time_d/(float)m_iBuildCDTime);
            tipNode->upTimeLabel(calculation_d_h_m_s(m_iBuildCDTime - cd_time_d).c_str());
        }
    }
    else if (upgrade_state_ == UNIT_UPGRADE_SUCESS)
    {
        CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
        CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
        
        //明暗动画
        if (data->m_building != NULL)
        {
            if (data->m_building->getuuID() == getuuID())
            {
                pCentralScene->m_pCentralUILayer->InfoBtnDisappear(UNIT_UPGRADE_IN,getTypeID());
                pCentralScene->m_pCentralUILayer->A_time = 0;
                pCentralScene->m_pCentralUILayer->is_A = true;
                
                isBiaoxian = false;
                biaoTime = 0;
                if (data->sprTeX != NULL)
                {
                    data->sprTeX->removeFromParentAndCleanup(false);
                    data->sprTeX = NULL;
                }
            }
        }
        
        //建筑升级
        this->unit_doupgrade(this->getID()+1);
        
        //农民设置
        data->FreeWorkers(m_uuID);
        pCentralScene->m_pCentralUILayer->updatePeasant();
		pCentralScene->m_pCentralLayer->FreeAWorker(this);
        
        //更新数据
        if (m_uTypeID == ARMY_BARRACK)
        {
            data->UpBuildableSoldiers();
        }
        else if(m_uTypeID == ARMY_SPELLFORGE)
        {
            data->UpBuildableMagic();
        }
        else if(m_uTypeID == RESOURCE_ELIXIRSTORAGE || m_uTypeID == RESOURCE_GOLDSTORAGE)
        {
            SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralUILayer->upRUI();
            SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->ResourceStorage();
        }
        else if (m_uTypeID == ARMY_TROOPHOUSING)
        {
            SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_Central_UserData->peopleNumMax = data->MAXpeopleNum();
        }
        
        //初始化记时
        initBuildingNumerical();
        
        //服务器发送请求
        if (isAddsu)
        {
            isAddsu = false;
        }
        else
        {
            data->buildingAccount(this,OperateType_UpgradeBuilding);
        }
        
        //增加经验
        int exp = (int)floor(sqrt(m_iBuildCDTime) * 1.5);
        pCentralScene->m_pCentralUILayer->updateExp(exp);
        
        //明暗动画
        if (data->m_building != NULL)
        {
            if (data->m_building->getuuID() == getuuID())
            {
                biaoTime = 0.22;
                isBiaoxian = true;
            }
        }
        //更改状态
        upgrade_state_ = UNIT_UPGRADE_NONE;
        
    }
    else if (upgrade_state_ == UNIT_UPGRADE_FAIL)
    {
        CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
        sprite_->removeChildByTag(10, false);
        //动画表现
        sprite_->removeChild(tipNode, false);
        tipNode = NULL;
        
        initBuildingNumerical();
        data->FreeWorkers(m_uuID);
        SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralUILayer->updatePeasant();
		SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->FreeAWorker(this);
        //        data->buildingAccount(this,OperateType_UpgradeBuilding);
        data->buildingAccount(this,OperateType_CancelTheUpgrade);
        //更改状态
        upgrade_state_ = UNIT_UPGRADE_NONE;
        
    }
    else if (upgrade_state_ == UNIT_UPGRADE_BUILD)
    {
        SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralUILayer->updatePeasant();
        
        if (savsTime < 1 )
        {
            m_uBuildTime = Until::millisecondNow_m();
        }
        else
        {
            m_uBuildTime = savsTime;
        }
        
        //减少资源消耗
        CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
        
        if (sprite_ != NULL)
        {
            nameLabel->retain();
            nameLabel->removeFromParentAndCleanup(false);
            
            sprite_->removeFromParentAndCleanup(false);
            sprite_ = NULL;
        }
        //隐藏defenderCharacterArr
        IsShowDefenceCharacters(false);
        
        
        //创建动画
        if (m_stBuildSubstrate.m_Line == 1)
        {
            sprite_ = CCSprite::create();
        }
        else
        {
            char strFile[64] = {0};
            sprintf(strFile,"build_dajian_%d_%d",m_stBuildSubstrate.m_Line,m_stBuildSubstrate.m_Row);
            sprite_ = CCSprite::create(GAME_FILE_TRANSFORM(strFile,".png").c_str());
            
            char strWei[64] = {0};
            sprintf(strWei,"build_weidang_%d_%d",m_stBuildSubstrate.m_Line,m_stBuildSubstrate.m_Row);
            CCSprite * sprWei = CCSprite::create(GAME_FILE_TRANSFORM(strWei,".png").c_str());
            sprWei->setPosition(ccp(sprite_->getContentSize().width/2, sprite_->getContentSize().height/2));
            sprite_->addChild(sprWei,10,10);
        }
        sprite_->setPosition(ccp(0,0));
        sprite_->setAnchorPoint(ccp(0.5f,0.5f));
        data->m_tmxMap->addChild(this->sprite_);
        
        nameLabel->setAnchorPoint(ccp(0.5f,0.5f));
        nameLabel->setPosition(ccp(sprite_->getContentSize().width/2, sprite_->getContentSize().height+80));
        sprite_->addChild(nameLabel);
        nameLabel->setVisible(false);
        nameLabel->release();
        //展示动画
        tipNode = TipNode::create();
        tipNode->initTipNode(BUILDINGTYPE_NOGAIN,true,this);
        tipNode->setPosition(ccp((sprite_->getContentSize().width/2 - tipNode->sprite_->getContentSize().width/2), sprite_->getContentSize().height));
        tipNode->setScale(1);
        sprite_->addChild(tipNode);
        
        
        //更改状态
        upgrade_state_ = UNIT_UPGRADE_BUILDIN;
        
        
    }
    else if (upgrade_state_ == UNIT_UPGRADE_BUILDIN)
    {
        long tempTime = Until::millisecondNow_m();
        
        long cd_time = tempTime - m_uBuildTime;
        
        int  cd_time_d = cd_time;
        
        //判断是否时间到
        if (m_iBuildCDTime <= cd_time_d)
        {
            
            //更改状态
            upgrade_state_ = UNIT_UPGRADE_BUILDSUCESS;
            
        }
        else
        {
            //更新进度条
            tipNode->upProgressBar((float)cd_time_d/(float)m_iBuildCDTime);
            tipNode->upTimeLabel(calculation_d_h_m_s(m_iBuildCDTime - cd_time_d).c_str());
        }
    }
    else if (upgrade_state_ == UNIT_UPGRADE_BUILDSUCESS)
    {
        CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
        CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
        
        
        if (data->m_building != NULL)
        {
            if (data->m_building->getuuID() == getuuID())
            {
                pCentralScene->m_pCentralUILayer->InfoBtnDisappear(UNIT_UPGRADE_BUILDIN,getTypeID());
                pCentralScene->m_pCentralUILayer->A_time = 0;
                pCentralScene->m_pCentralUILayer->is_A = true;
                
                isBiaoxian = false;
                biaoTime = 0;
                if (data->sprTeX != NULL)
                {
                    data->sprTeX->removeFromParentAndCleanup(false);
                    data->sprTeX = NULL;
                }
            }
        }
        //动画表现
        sprite_->removeChildByTag(10, false);
        sprite_->removeChild(tipNode, false);
        tipNode = NULL;
        
        const BaseBuildingLevelData* buildingBaseLevelData;
        buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( m_u32ID);
        if (sprite_ != NULL)
        {
            sprite_->removeFromParentAndCleanup(false);
            sprite_ = NULL;
        }
        //创建动画
        sprite_ = CCSprite::create(GAME_FILE_TRANSFORM(buildingBaseLevelData->ExportName.c_str(),".png").c_str());
        sprite_->setPosition(ccp(0,0));
        sprite_->setAnchorPoint(ccp(0.5,0.5));
        sprite_->setScale(UNIT_Texture_scale_2048x1536);
        data->m_tmxMap->addChild(this->sprite_);
        
        //更换建筑等级显示
        char strName[64];
        sprintf(strName,"%s \nlevel%d",buildingBaseLevelData->Name.c_str(),buildingBaseLevelData->build_level);
        drawNameLabel(sprite_, strName);
        
        
        //显示塔上人物
        IsShowDefenceCharacters(true);
        
        //闲置农民
        data->FreeWorkers(m_uuID);
        //刷新农民个数显示
        pCentralScene->m_pCentralUILayer->updatePeasant();
		pCentralScene->m_pCentralLayer->FreeAWorker(this);
        
        //不同建筑的数据刷新
        if (m_uTypeID == ARMY_BARRACK)
        {
            data->UpBuildableSoldiers();
        }
        else if(m_uTypeID == ARMY_SPELLFORGE)
        {
            data->UpBuildableMagic();
        }
        else if(m_uTypeID == RESOURCE_ELIXIRSTORAGE || m_uTypeID == RESOURCE_GOLDSTORAGE)
        {
            pCentralScene->m_pCentralUILayer->upRUI();
            pCentralScene->m_pCentralLayer->ResourceStorage();
        }
        else if(m_uTypeID == BUILDINGTYPE_WORKER)
        {
            
        }
        else if (m_uTypeID == ARMY_TROOPHOUSING)
        {
            pCentralScene->m_pCentralData->m_Central_UserData->peopleNumMax = data->MAXpeopleNum();
        }
        
        //初始化建筑的记时
        initBuildingNumerical();
        
        //发送服务器消息
        if (isAddsu)
        {
            isAddsu = false;
        }
        else
        {
            data->buildingAccount(this,OperateType_Build);
        }
        
        //增加经验
        int exp = (int)floor(sqrt(m_iBuildCDTime) * 1.5);
        pCentralScene->m_pCentralUILayer->updateExp(exp);
        
        
        //建筑明暗表现
        if (data->m_building != NULL)
        {
            if (data->m_building->getuuID() == getuuID())
            {
                biaoTime = 0.22;
                isBiaoxian = true;
            }
        }
        
        //更改状态
        upgrade_state_ = UNIT_UPGRADE_NONE;
    }
    else if (upgrade_state_ == UNIT_UPGRADE_BUILDFAIL)
    {
        CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
        data->buildingAccount(this,OperateType_CancelTheBuilding);
        data->FreeWorkers(m_uuID);
        SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralUILayer->updatePeasant();
		SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->FreeAWorker(this);
        
        remove();
    }
    else if (upgrade_state_ == UNIT_UPGRADE_REMOVE)
    {
        removeEventTime = Until::millisecondNow_m();
        
        //展示动画
        tipNode = TipNode::create();
        tipNode->initTipNode(BUILDINGTYPE_NOGAIN,true,this);
        sprite_->addChild(tipNode);
        
        upgrade_state_ = UNIT_UPGRADE_REMOVEIN;
        
        
        
        
    }
    else if (upgrade_state_ == UNIT_UPGRADE_REMOVEIN)
    {
        
        long tempTime = Until::millisecondNow_m();
        
        long cd_time = tempTime - removeEventTime;
        
        int  cd_time_d = cd_time;
        
        //判断是否时间到
        if (m_iBuildCDTime <= cd_time_d)
        {
            //更改状态
            upgrade_state_ = UNIT_UPGRADE_REMOVESUCESS;
        }
        else
        {
            //更新进度条
            tipNode->upProgressBar((float)cd_time_d/(float)m_iBuildCDTime);
            tipNode->upTimeLabel(calculation_d_h_m_s(m_iBuildCDTime - cd_time_d).c_str());
        }
        
    }
    else if (upgrade_state_ == UNIT_UPGRADE_REMOVESUCESS)
    {
        
        upgrade_state_ = UNIT_UPGRADE_NONE;
        
        remove();
        
    }
    else if (upgrade_state_ == UNIT_UPGRADE_REMOVEFAIL)
    {
        
        
        
    }
    
    else if(upgrade_state_ == UNIT_UPGRADE_RESUME){
        CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
        char strFile[64] = {0};
        sprintf(strFile,"build_destroy_%d_%d",m_stBuildSubstrate.m_Line,m_stBuildSubstrate.m_Row);
        
        sprite_ = CCSprite::create(GAME_FILE_TRANSFORM(strFile,".png").c_str());
        sprite_->setPosition(ccp(0,0));
        sprite_->setAnchorPoint(ccp(0.5f,0.5f));
        sprite_->setScale(0.5f);
        data->m_tmxMap->addChild(this->sprite_);
    }
    else if(upgrade_state_ == UNIT_UPGRADE_RESUMEIN){
        // todo
    }
    else if(upgrade_state_ == UNIT_UPGRADE_RESUMEFINISH){
        // todo
    }
}

