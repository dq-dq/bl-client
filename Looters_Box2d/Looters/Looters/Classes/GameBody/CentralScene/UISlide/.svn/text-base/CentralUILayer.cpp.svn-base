//
//  CentralUILayer.cpp
//  Looters
//
//  Created by yisuode on 12-11-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "CentralUILayer.h"
#include "CentralShopUILayer.h"
#include "CentralPVPUILayer.h"
#include "CentralMailUILayer.h"
#include "cocos2d.h"
#include "GameControl.h"
#include "CommonResource.h"
#include "NetMessageManager.h"
#include "TipInfo.h"
USING_NS_CC;
USING_NS_CC_EXT;

CentralUILayer::CentralUILayer():goldLabel(NULL)
, potionsLabel(NULL)
, gemLabel(NULL)
, peasantLabel(NULL)
, experienceLabel(NULL)
, lvLabel(NULL)
, pvpLabel(NULL)
, protectLabel(NULL)
, protectLabel2(NULL)
, nameLabel(NULL)
, goldMaxLabel(NULL)
, potionsMaxLabel(NULL)
, peasantLabel2(NULL)
, potionsS(NULL)
, goldS(NULL)
, experienceS(NULL)
, BtnBuildGem(NULL)
, GemNumLabel(NULL)
, resourcesNumLabel(NULL)
, BtnResources(NULL)
, l_nameLeve(NULL)
, btnCollectP(NULL)
, btnCollectG(NULL)
, s_icong(NULL)
, s_iconlevel(NULL)
, s_iconp(NULL)
, s_icongem(NULL)
{

    minG = 0;
    cdG = 0;           
    minlevel = 0;           
    cdlevel = 0;
    minP = 0;           
    cdP = 0;
    minGem = 0;      
    cdGem = 0;
    gemTyep = 0;
    
    mAnimationManager = NULL;
    A_time = 0;
    is_A = false;
}

CentralUILayer::~CentralUILayer()
{

    CC_SAFE_RELEASE(peasantLabel);
    CC_SAFE_RELEASE(experienceLabel);
    CC_SAFE_RELEASE(lvLabel);
    CC_SAFE_RELEASE(pvpLabel);
    CC_SAFE_RELEASE(protectLabel);
    CC_SAFE_RELEASE(protectLabel2);
    CC_SAFE_RELEASE(nameLabel);
    CC_SAFE_RELEASE(goldMaxLabel);
    CC_SAFE_RELEASE(potionsMaxLabel);
    CC_SAFE_RELEASE(peasantLabel2);
    CC_SAFE_RELEASE(potionsS);
    CC_SAFE_RELEASE(goldS);
    CC_SAFE_RELEASE(experienceS);
    CC_SAFE_RELEASE(BtnBuildGem);

    CC_SAFE_RELEASE(goldLabel);
    CC_SAFE_RELEASE(potionsLabel);
    CC_SAFE_RELEASE(gemLabel);
    
    CC_SAFE_RELEASE(GemNumLabel);
    
    CC_SAFE_RELEASE(BtnResources);
    CC_SAFE_RELEASE(resourcesNumLabel);
    CC_SAFE_RELEASE(l_nameLeve);
    
    
    CC_SAFE_RELEASE(btnCollectP);
    CC_SAFE_RELEASE(btnCollectG);
    
    
    CC_SAFE_RELEASE(s_icong);
    CC_SAFE_RELEASE(s_icongem);
    CC_SAFE_RELEASE(s_iconp);
    CC_SAFE_RELEASE(s_iconlevel);
    
}

bool CentralUILayer::init( void )
{
	if( !CCLayer::init() )
		return false;
    
    
    
    
    return true;
}


void CentralUILayer::updata(float _time)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;

    if (GemNumLabel != NULL)
    {
        if (pCentralScene->m_pCentralLayer->m_building != NULL)
        {
            if (pCentralScene->m_pCentralLayer->m_building->upgrade_state_ == UNIT_UPGRADE_BUILDIN
                || pCentralScene->m_pCentralLayer->m_building->upgrade_state_ == UNIT_UPGRADE_IN) 
            {
                long tempTime = Until::millisecondNow_m();
                long cd_time = tempTime - pCentralScene->m_pCentralLayer->m_building->m_uBuildTime;
                int  S_time = pCentralScene->m_pCentralLayer->m_building->m_iBuildCDTime - cd_time;
                
                GemNumLabel->setString(CommonResource::getStringFromInt(pCentralScene->m_pCentralLayer->gemConversion(S_time)).c_str());
            }
        }
    }

    if (is_A)
    {
        if (pCentralScene->m_pCentralLayer->m_building != NULL)
        {
            A_time+=_time;
            if (A_time>0.3f)
            {
                is_A = false;
                //升级所需的资源数
                upResourcesNumLabel();
                InfoBtnAppear(pCentralScene->m_pCentralLayer->m_building->upgrade_state_,pCentralScene->m_pCentralLayer->m_building->getTypeID());
            }
        }
    }
    
    if (pCentralScene->m_pCentralLayer->m_building != NULL)
    {
        switch (pCentralScene->m_pCentralLayer->m_building->getTypeID())
        {
            case RESOURCE_ELIXIRPUMP:
            {
                if (pCentralScene->m_pCentralLayer->m_building->resourcesPotionsNum>0)
                {
                    CollectPHui->setVisible(false);
                }
                else
                {
                    CollectPHui->setVisible(true);
                }
            }
                break;
            case RESOURCE_GOLDMINE:
            {
                if (pCentralScene->m_pCentralLayer->m_building->resourcesGoldNum>0)
                {
                    CollectGHui->setVisible(false);
                }
                else
                {
                    CollectGHui->setVisible(true);
                }
            }
                break;
            default:
                break;
        }
    }
    

    if (cdG != 0)
    {
        if (cdG > 0)
        {
            minG+=cdG;
            if (minG >= pCentralScene->m_pCentralData->m_Central_UserData->user_gold)
            {
                cdG = 0;
                minG = 0;
                pCentralScene->m_pCentralUILayer->goldLabel->setString(CommonResource::getStringFromInt(pCentralScene->m_pCentralData->m_Central_UserData->user_gold).c_str());
                float scale = (float)pCentralScene->m_pCentralData->m_Central_UserData->user_gold/pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX;
                if (scale>1)
                {
                    scale = 1;
                }
                goldS->setScaleX(scale);
            }
            else
            {
                pCentralScene->m_pCentralUILayer->goldLabel->setString(CommonResource::getStringFromInt(minG).c_str());
                float scale = (float)minG/pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX;
                if (scale>1)
                {
                    scale = 1;
                }
                goldS->setScaleX(scale);
            }
        }
        else
        {
            minG+=cdG;
            if (minG <= pCentralScene->m_pCentralData->m_Central_UserData->user_gold)
            {
                cdG = 0;
                minG = 0;
                pCentralScene->m_pCentralUILayer->goldLabel->setString(CommonResource::getStringFromInt(pCentralScene->m_pCentralData->m_Central_UserData->user_gold).c_str());
                float scale = (float)pCentralScene->m_pCentralData->m_Central_UserData->user_gold/pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX;
                if (scale>1)
                {
                    scale = 1;
                }
                goldS->setScaleX(scale);
            }
            else
            {
                pCentralScene->m_pCentralUILayer->goldLabel->setString(CommonResource::getStringFromInt(minG).c_str());
                float scale = (float)minG/pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX;
                if (scale>1)
                {
                    scale = 1;
                }
                goldS->setScaleX(scale);
            }
        }
        
        
        if (s_icong->getScale() > 1)
        {
            s_icong->setScale(1);
        }
        else
        {
            s_icong->setScale(1.1);
        }
    }
    else
    {
        if (s_icong->getScale() > 1)
        {
            s_icong->setScale(1);
        }
        
    }
    
    
    
    if (cdP != 0)
    {
        
        if (cdP > 0)
        {
            minP+=cdP;
            if (minP >= pCentralScene->m_pCentralData->m_Central_UserData->user_potions)
            {
                cdP = 0;
                minP = 0;
                pCentralScene->m_pCentralUILayer->potionsLabel->setString(CommonResource::getStringFromInt(pCentralScene->m_pCentralData->m_Central_UserData->user_potions).c_str());
                
                float scale = (float)pCentralScene->m_pCentralData->m_Central_UserData->user_potions/pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX;
                if (scale>1)
                {
                    scale = 1;
                }
                potionsS->setScaleX(scale);
            }
            else
            {
                pCentralScene->m_pCentralUILayer->potionsLabel->setString(CommonResource::getStringFromInt(minP).c_str());
                float scale = (float)minP/pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX;
                if (scale>1)
                {
                    scale = 1;
                }
                potionsS->setScaleX(scale);
            }
        }
        else
        {
            minP+=cdP;
            if (minP <= pCentralScene->m_pCentralData->m_Central_UserData->user_potions)
            {
                cdP = 0;
                minP = 0;
                pCentralScene->m_pCentralUILayer->potionsLabel->setString(CommonResource::getStringFromInt(pCentralScene->m_pCentralData->m_Central_UserData->user_potions).c_str());
                
                float scale = (float)pCentralScene->m_pCentralData->m_Central_UserData->user_potions/pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX;
                if (scale>1)
                {
                    scale = 1;
                }
                potionsS->setScaleX(scale);
            }
            else
            {
                pCentralScene->m_pCentralUILayer->potionsLabel->setString(CommonResource::getStringFromInt(minP).c_str());
                float scale = (float)minP/pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX;
                if (scale>1)
                {
                    scale = 1;
                }
                potionsS->setScaleX(scale);
            }
        }
        
        if (s_iconp->getScale() > 1)
        {
            s_iconp->setScale(1);
        }
        else
        {
            s_iconp->setScale(1.1);
        }
    }
    else
    {
        if (s_iconp->getScale() > 1)
        {
            s_iconp->setScale(1);
        }
        
    }
    
    if (cdGem != 0)
    {
        minGem = 0;
    }
    
    if (cdlevel != 0)
    {
        minlevel = 0;
    }
    
}
bool CentralUILayer::updateGold(int _num)
{
    bool isUpDate = true;
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    //加
    if (_num > 0)
    {
        //不用加钱
        if (pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX == pCentralScene->m_pCentralData->m_Central_UserData->user_gold)
        {
            isUpDate = false;
        }
        
        
        
    }
    //减
    else if(_num < 0)
    {
        if (pCentralScene->m_pCentralData->m_Central_UserData->user_gold >= (-_num))
        {
            
        }
        else
        //钱不够
        {
            _num = 0;
            isUpDate = false;
        }
        
        
    }
    else
    {
        _num = 0;
        float scale = (float)pCentralScene->m_pCentralData->m_Central_UserData->user_gold/pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX;
        if (scale>1)
        {
            scale = 1;
        }
        goldS->setScaleX(scale);
        isUpDate = false;
    }
    
    
    
    
    //表现
    if (isUpDate)
    {
        minG = pCentralScene->m_pCentralData->m_Central_UserData->user_gold;
        
        pCentralScene->m_pCentralData->m_Central_UserData->user_gold += _num;
        //加满钱
        if (pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX <= pCentralScene->m_pCentralData->m_Central_UserData->user_gold)
        {
            pCentralScene->m_pCentralData->m_Central_UserData->user_gold = pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX;
            cdG = (pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX - minG)/20;
        }
        else
        {
            cdG = _num/20;
        }
        
        //滚动动画
        if (_num > 0)
        {
            if (cdG < 1)
            {
                cdG = 1;
            }
        }
        else if (_num < 0)
        {
            if (cdG > -1)
            {
                cdG = -1;
            }
        }
        
        
        
        
        float scale = (float)pCentralScene->m_pCentralData->m_Central_UserData->user_gold/pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX;
        if (scale>1)
        {
            scale = 1;
        }
        goldS->setScaleX(scale);
        
        
        //资源存储
        if (_num != 0)
        {
            pCentralScene->m_pCentralLayer->ResourceStorage();
        }
        
        
    }
    
    return isUpDate;
}


bool CentralUILayer::updatePotions(int _num)
{
    bool isUpDate = true;
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    //加
    if (_num > 0)
    {
        
        //不用加
        if (pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX == pCentralScene->m_pCentralData->m_Central_UserData->user_potions)
        {
            isUpDate = false;
        }
        
        
    }
    //减
    else if(_num < 0)
    {
        if (pCentralScene->m_pCentralData->m_Central_UserData->user_potions >= (-_num))
        {
            
        }
        else
            //不够
        {
            isUpDate = false;
            _num = 0;
        }
        
        
    }
    else
    {
        _num = 0;
        float scale = (float)pCentralScene->m_pCentralData->m_Central_UserData->user_potions/pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX;
        if (scale>1)
        {
            scale = 1;
        }
        potionsS->setScaleX(scale);
        isUpDate = false;
    }
    
    
    
    
    //表现
    if (isUpDate)
    {
        minP = pCentralScene->m_pCentralData->m_Central_UserData->user_potions;
        pCentralScene->m_pCentralData->m_Central_UserData->user_potions += _num;
        //加满
        if (pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX <= pCentralScene->m_pCentralData->m_Central_UserData->user_potions)
        {
            pCentralScene->m_pCentralData->m_Central_UserData->user_potions = pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX;
            cdP = (pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX - minP)/20;
        }
        else
        {
            cdP = _num/20;
        }
        //滚动动画
        if (_num > 0)
        {
            if (cdP < 1)
            {
                cdP = 1;
            }
        }
        else if (_num < 0)
        {
            if (cdP > -1)
            {
                cdP = -1;
            }
        }
        
        if (_num != 0)
        {
            pCentralScene->m_pCentralLayer->ResourceStorage();
        }
        
    }
    return isUpDate;
}
void CentralUILayer::upRUI()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;

    pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX = pCentralScene->m_pCentralLayer->ResourceMAXG();
    pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX = pCentralScene->m_pCentralLayer->ResourceMAXP();
    BasisInfo();
    updateGold(0); 
    updatePotions(0);
}
void CentralUILayer::upResourcesNumLabel()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    if(pCentralScene->m_pCentralLayer->m_building->upgrade_state_ != UNIT_UPGRADE_NONE) return;
    
    const BaseBuildingLevelData* buildingBaseLevelData;
    buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( pCentralScene->m_pCentralLayer->m_building->getID()+1);
    bool isResource = true;
    
    if (buildingBaseLevelData!=NULL)
    {
        

        CCSprite* shui = (CCSprite*)BtnResources->getChildByTag(1);
        shui->setVisible(false);
        //金币
        if ("Gold" == string(buildingBaseLevelData->BuildResource))
        {
            if (pCentralScene->m_pCentralData->m_Central_UserData->user_gold < buildingBaseLevelData->BuildCost)
            {
                isResource = false;
            }
        }
        //药水
        else if("Elixir" == string(buildingBaseLevelData->BuildResource))
        {
            shui->setVisible(true);
            if (pCentralScene->m_pCentralData->m_Central_UserData->user_potions < buildingBaseLevelData->BuildCost)
            {
                isResource = false;
            }
        }
        //宝石
        else if("Diamonds" == string(buildingBaseLevelData->BuildResource))
        {
            if (pCentralScene->m_pCentralData->m_Central_UserData->user_gem < buildingBaseLevelData->BuildCost)
            {
                isResource = false;
            }
        }
        
//        buildingBaseLevelData->BuildCost
        resourcesNumLabel->setString(CommonResource::getStringFromInt(buildingBaseLevelData->BuildCost).c_str());
        
        if (isResource)
        {
            resourcesNumLabel->setColor(ccWHITE);
        }
        else
        {
            resourcesNumLabel->setColor(ccRED);
        }
    }

}
void CentralUILayer::BasisInfo()
{
    CentralData*  _userData = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    
    
    nameLabel->setString((*_userData->m_Central_UserData->nick_name).c_str());
    experienceLabel->setString(CommonResource::getStringFromInt(_userData->m_Central_UserData->exp).c_str());
    lvLabel->setString(CommonResource::getStringFromInt(_userData->m_Central_UserData->level).c_str());
    
    char strFileName1[64];
	sprintf(strFileName1,"Max:%d",_userData->m_Central_UserData->user_goldMAX);
    goldMaxLabel->setString(strFileName1);
    
    char strFileName2[64];
	sprintf(strFileName2,"Max:%d",_userData->m_Central_UserData->user_potionsMAX);
    potionsMaxLabel->setString(strFileName2);
    
    
    pvpLabel->setString(CommonResource::getStringFromInt(_userData->m_Central_UserData->pvp_mark).c_str());
    
    
    protectLabel->setString(CommonResource::calculation_d_h_m(_userData->m_Central_UserData->shield_time).c_str());
    
}
void CentralUILayer::updatePeasant()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;

    int m_g = 0;
    int m_h = 0;
    int num = pCentralScene->m_pCentralLayer->unit_list_->count();

    for (int i = 0; i <num; i++)
    {
        Unit *unit = (Unit*)pCentralScene->m_pCentralLayer->unit_list_->objectAtIndex(i);
        //如果是建筑
        if (unit->is_build_type())
        {
            BuildingBase* build = (BuildingBase*)unit;
            if (build->getTypeID() == BUILDINGTYPE_WORKER)
            {
                m_g++;
                
                if (!build->isBusy) 
                {
                    m_h++;
                }
            } 
        }
    }

    if (m_g > 0)
    {
        char strFileName1[64];
        sprintf(strFileName1,"%d/%d",m_h,m_g);
        peasantLabel->setString(strFileName1);
    }
    
    
}
bool CentralUILayer::updateExp(int _num)
{
    bool isUpDate = true;
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    const ExperienceLevels* experienceLevels = GameData::GetDataFromBaseExperienceLevels(pCentralScene->m_pCentralData->m_Central_UserData->level);
    if(experienceLevels == NULL)
    {
        pCentralScene->m_pCentralData->m_Central_UserData->exp += _num;
        pCentralScene->m_pCentralUILayer->experienceLabel->setString(CommonResource::getStringFromInt(pCentralScene->m_pCentralData->m_Central_UserData->exp).c_str());
        experienceS->setScaleX(0);
    }
    else
    {
        //加
        if (_num > 0)
        {
            pCentralScene->m_pCentralData->m_Central_UserData->exp += _num;
            
            //是否升级
            if (pCentralScene->m_pCentralData->m_Central_UserData->exp >= experienceLevels->ExperienceLevels_exp)
            {
                pCentralScene->m_pCentralData->m_Central_UserData->exp -= experienceLevels->ExperienceLevels_exp;
                pCentralScene->m_pCentralData->m_Central_UserData->level++;
            }
            
        }
        else
        {
            _num = 0;
        }
        
        
        //表现
        if (isUpDate)
        {
            pCentralScene->m_pCentralUILayer->lvLabel->setString(CommonResource::getStringFromInt(pCentralScene->m_pCentralData->m_Central_UserData->level).c_str());
            pCentralScene->m_pCentralUILayer->experienceLabel->setString(CommonResource::getStringFromInt(pCentralScene->m_pCentralData->m_Central_UserData->exp).c_str());
            
            const ExperienceLevels* XexperienceLevels = GameData::GetDataFromBaseExperienceLevels(pCentralScene->m_pCentralData->m_Central_UserData->level);
            
            if(experienceLevels == NULL)
            {
                experienceS->setScaleX(0);
            }
            else
            {
                float experience = (float)pCentralScene->m_pCentralData->m_Central_UserData->exp/XexperienceLevels->ExperienceLevels_exp;
                if (experience>1)
                {
                    experience = 1;
                }
                experienceS->setScaleX(experience);
            }
            
            
            
        }
    }
    
    return isUpDate;
}
bool CentralUILayer::updateGem(int _num)
{
    bool isUpDate = true;
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    //加
    if (_num > 0)
    {
        
        
    }
    //减
    else if(_num < 0)
    {
        if (pCentralScene->m_pCentralData->m_Central_UserData->user_gem >= (-_num))
        {
            
        }
        else
            //不够
        {
            isUpDate = false;
            _num = 0;
        }
        
        
    }
    else
    {
        _num = 0;
    }
    
    
    
    
    //表现
    if (isUpDate)
    {
        pCentralScene->m_pCentralData->m_Central_UserData->user_gem += _num;
        pCentralScene->m_pCentralUILayer->gemLabel->setString(CommonResource::getStringFromInt(pCentralScene->m_pCentralData->m_Central_UserData->user_gem).c_str()); 
    }
    return isUpDate;
}
void CentralUILayer::okGemMenuItemInBattle(CCObject *pSender)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    switch (gemTyep)
    {
            //资源不够升级
        case 1:
        {
            
            if (pCentralScene->m_pCentralUILayer->updateGem(-gem_Num))
            {
                const BaseBuildingLevelData* buildingBaseLevelData;
                buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( pCentralScene->m_pCentralLayer->m_building->getID()+1);
                
                
                
                //金币
                if ("Gold" == string(buildingBaseLevelData->BuildResource))
                {
                    pCentralScene->m_pCentralLayer->buildingAccount2(OperateType_BuyR,(buildingBaseLevelData->BuildCost - pCentralScene->m_pCentralData->m_Central_UserData->user_gold),true);
                    pCentralScene->m_pCentralUILayer->updateGold(-pCentralScene->m_pCentralData->m_Central_UserData->user_gold);
                }
                //药水
                else if("Elixir" == string(buildingBaseLevelData->BuildResource))
                {
                    pCentralScene->m_pCentralLayer->buildingAccount2(OperateType_BuyR,(buildingBaseLevelData->BuildCost - pCentralScene->m_pCentralData->m_Central_UserData->user_potions),false);
                    pCentralScene->m_pCentralUILayer->updatePotions(-pCentralScene->m_pCentralData->m_Central_UserData->user_potions);
                    
                }
                BuildingBase* build = pCentralScene->m_pCentralLayer->NoBusy();
                
                pCentralScene->m_pCentralUILayer->InfoBtnDisappear(pCentralScene->m_pCentralLayer->m_building->upgrade_state_,pCentralScene->m_pCentralLayer->m_building->getTypeID());
                
                
                build->isBusy = true;
                build->busyUUID = pCentralScene->m_pCentralLayer->m_building->getuuID();
                pCentralScene->m_pCentralLayer->m_building->m_iBuildCDTime = buildingBaseLevelData->BuildTimeD*24*60*60+ buildingBaseLevelData->BuildTimeH*60*60 +buildingBaseLevelData->BuildTimeM*60;
                pCentralScene->m_pCentralLayer->m_building->upgrade_state_ = UNIT_UPGRADE_START;
                pCentralScene->m_pCentralUILayer->A_time = 0;
                pCentralScene->m_pCentralUILayer->is_A = true;
                
                pCentralScene->m_pCentralLayer->SendAWorker(build, pCentralScene->m_pCentralLayer->m_building);

            }
            else
            {
                //宝石不够
                DialogLayer* dia = DialogLayer::create();
                dia->setPosition(ccp(0,0));
                this->addChild(dia,1000,10000);
                
                dia->setShopMenuItem(this,menu_selector(CentralUILayer::cancelShopMenuItemInBattle), menu_selector(CentralUILayer::okShopMenuItemInBattle));
            
                dia->setContentString("请进入商城购买宝石");
            }
        }
            break;
            //队列不够升级
        case 2:
        {
            CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
            int num = pCentralScene->m_pCentralLayer->unit_list_->count();
            for (int i = 0; i <num; i++)
            {
                Unit *unit = (Unit*)pCentralScene->m_pCentralLayer->unit_list_->objectAtIndex(i);
                //如果是建筑
                if (unit->is_build_type())
                {
                    BuildingBase* build = (BuildingBase*)unit;
                    if (build->upgrade_state_ == UNIT_UPGRADE_IN || build->upgrade_state_ == UNIT_UPGRADE_BUILDIN)
                    {
                        if (gem_UUid == build->getuuID())
                        {
                            long tempTime = Until::millisecondNow_m();
                            
                            long cd_time = tempTime - build->m_uBuildTime;
                            
                            int  S_time = build->m_iBuildCDTime - cd_time;
                            
                            int  gem = pCentralScene->m_pCentralLayer->gemConversion(S_time);
                            
                            if (pCentralScene->m_pCentralUILayer->updateGem(-gem))
                            {
                                //加速队列
                                pCentralScene->m_pCentralLayer->Accelerated_id = build->getTypeID();
                                pCentralScene->m_pCentralLayer->Accelerated_uuid = build->getuuID();
                                pCentralScene->m_pCentralLayer->Accelerated_remain_time = S_time;
                                pCentralScene->m_pCentralLayer->Accelerated_gem_count = gem;
                                
                                if (build->upgrade_state_ == UNIT_UPGRADE_BUILDIN)
                                {
                                    pCentralScene->m_pCentralLayer->buildingAccelerated(AccelerateType_Building);
                                }
                                else if(build->upgrade_state_ == UNIT_UPGRADE_IN)
                                {
                                    pCentralScene->m_pCentralLayer->buildingAccelerated(AccelerateType_UPBuilding);
                                }
                                build->BuildingComplete();
                                
                                
                                
                                //升级建筑
                              
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
                                                }
                                                else
                                                {
                                                    pCentralScene->m_pCentralUILayer->updatePotions(-buildingBaseLevelData->BuildCost);
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
                                                
                                            }
                                            
                                        }
                                        
                                        
                                    }
                                }  
                            }
                            else
                            {
                               //宝石不够
                                DialogLayer* dia = DialogLayer::create();
                                dia->setPosition(ccp(0,0));
                                this->addChild(dia,1000,10000);
                                
                                dia->setShopMenuItem(this,menu_selector(CentralUILayer::cancelShopMenuItemInBattle), menu_selector(CentralUILayer::okShopMenuItemInBattle));
                                
                                dia->setContentString("请进入商城购买宝石");
                            }
                        }
                        
                        
                    }
                }
            }
            
        }
            break;
            //建造资源不够
        case 3:
        {
            
            if (pCentralScene->m_pCentralUILayer->updateGem(-gem_Num))
            {
                const BaseBuildingLevelData* buildingBaseLevelData;
                buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( pCentralScene->m_pCentralLayer->m_building->getID());
                
                
                
                //金币
                if ("Gold" == string(buildingBaseLevelData->BuildResource))
                {
                    pCentralScene->m_pCentralLayer->buildingAccount2(OperateType_BuyR,(buildingBaseLevelData->BuildCost - pCentralScene->m_pCentralData->m_Central_UserData->user_gold),true);
                    pCentralScene->m_pCentralUILayer->updateGold(-pCentralScene->m_pCentralData->m_Central_UserData->user_gold);
                }
                //药水
                else if("Elixir" == string(buildingBaseLevelData->BuildResource))
                {
                    pCentralScene->m_pCentralLayer->buildingAccount2(OperateType_BuyR,(buildingBaseLevelData->BuildCost - pCentralScene->m_pCentralData->m_Central_UserData->user_potions),false);
                    pCentralScene->m_pCentralUILayer->updatePotions(-pCentralScene->m_pCentralData->m_Central_UserData->user_potions);
                    
                }
                BuildingBase* build = pCentralScene->m_pCentralLayer->NoBusy();
                
                {
                    BuildingBase* m_building = pCentralScene->m_pCentralLayer->m_building;
                    build->isBusy = true;
                    build->busyUUID = m_building->getuuID();
                    
                    m_building->upgrade_state_ = UNIT_UPGRADE_BUILD;
                    
                    pCentralScene->m_pCentralLayer->RemoveGridBuildInfo(m_building->getMapIndex(),m_building->GetLine(),m_building->getuuID(),m_building);
                    m_building->setMapIndex(pCentralScene->m_pCentralLayer->buildNewMapIndex);
                    pCentralScene->m_pCentralLayer->MarkGridBuildInfo(m_building->getMapIndex(), m_building->GetLine(), m_building->getuuID(), m_building);
                    
                    pCentralScene->m_pCentralLayer->SendAWorker(build, m_building);
                    
                    //不显示箭头
                    m_building->removeSymbol();
                    
                    pCentralScene->m_pCentralLayer->buildingAccount(m_building,OperateType_Build);
                    m_building->z_state_ = UNIT_Z_NORMAL_STATE;
                    pCentralScene->m_pCentralLayer->m_BuyBuilding = NULL;
                    pCentralScene->m_pCentralUILayer->InfoBtnAppear(m_building->upgrade_state_,m_building->getTypeID());
                    
                    
                }
                
            }
            else
            {
                //宝石不够
                DialogLayer* dia = DialogLayer::create();
                dia->setPosition(ccp(0,0));
                this->addChild(dia,1000,10000);
                
                dia->setShopMenuItem(this,menu_selector(CentralUILayer::cancelShopMenuItemInBattle), menu_selector(CentralUILayer::okShopMenuItemInBattle));
                
                dia->setContentString("请进入商城购买宝石");
            }
        }
            break;
            //建造队列不够
        case 4:
        {
            CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
            int num = pCentralScene->m_pCentralLayer->unit_list_->count();
            for (int i = 0; i <num; i++)
            {
                Unit *unit = (Unit*)pCentralScene->m_pCentralLayer->unit_list_->objectAtIndex(i);
                //如果是建筑
                if (unit->is_build_type())
                {
                    BuildingBase* build = (BuildingBase*)unit;
                    if (build->upgrade_state_ == UNIT_UPGRADE_IN || build->upgrade_state_ == UNIT_UPGRADE_BUILDIN)
                    {
                        if (gem_UUid == build->getuuID())
                        {
                            long tempTime = Until::millisecondNow_m();
                            
                            long cd_time = tempTime - build->m_uBuildTime;
                            
                            int  S_time = build->m_iBuildCDTime - cd_time;
                            
                            int  gem = pCentralScene->m_pCentralLayer->gemConversion(S_time);
                            
                            if (pCentralScene->m_pCentralUILayer->updateGem(-gem))
                            {
                                //加速队列
                                pCentralScene->m_pCentralLayer->Accelerated_id = build->getTypeID();
                                pCentralScene->m_pCentralLayer->Accelerated_uuid = build->getuuID();
                                pCentralScene->m_pCentralLayer->Accelerated_remain_time = S_time;
                                pCentralScene->m_pCentralLayer->Accelerated_gem_count = gem;
                                
                                if (build->upgrade_state_ == UNIT_UPGRADE_BUILDIN)
                                {
                                    pCentralScene->m_pCentralLayer->buildingAccelerated(AccelerateType_Building);
                                }
                                else if(build->upgrade_state_ == UNIT_UPGRADE_IN)
                                {
                                    pCentralScene->m_pCentralLayer->buildingAccelerated(AccelerateType_UPBuilding);
                                }
                                build->BuildingComplete();
                                
                                
                                
                                //建筑建造
                                const BaseBuildingLevelData* buildingBaseLevelData;
                                buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( pCentralScene->m_pCentralLayer->m_building->getID());
                                bool isResource = true;
                                BuildingBase* build = pCentralScene->m_pCentralLayer->NoBusy();
                                if (build != NULL)
                                {
                                    //金币
                                    if ("Gold" == string(buildingBaseLevelData->BuildResource))
                                    {
                                        if (pCentralScene->m_pCentralData->m_Central_UserData->user_gold < buildingBaseLevelData->BuildCost)
                                        {
                                            pCentralScene->m_pCentralUILayer->addDialogLayer(true,buildingBaseLevelData->BuildCost-pCentralScene->m_pCentralData->m_Central_UserData->user_gold,3);
                                            isResource = false;
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
                                            pCentralScene->m_pCentralUILayer->addDialogLayer(false,buildingBaseLevelData->BuildCost-pCentralScene->m_pCentralData->m_Central_UserData->user_potions,3);
                                            isResource = false;
                                        }
                                        else
                                        {
                                            pCentralScene->m_pCentralUILayer->updatePotions(-buildingBaseLevelData->BuildCost);
                                        }
                                    }
                                    
                                    // 资源充足
                                    if (isResource)
                                    {
                                        {
                                            BuildingBase* m_building = pCentralScene->m_pCentralLayer->m_building;
                                            build->isBusy = true;
                                            build->busyUUID = m_building->getuuID();
                                            
                                            m_building->upgrade_state_ = UNIT_UPGRADE_BUILD;
                                            
                                            pCentralScene->m_pCentralLayer->RemoveGridBuildInfo(m_building->getMapIndex(),m_building->GetLine(),m_building->getuuID(),m_building);
                                            m_building->setMapIndex(pCentralScene->m_pCentralLayer->buildNewMapIndex);
                                            pCentralScene->m_pCentralLayer->MarkGridBuildInfo(m_building->getMapIndex(), m_building->GetLine(), m_building->getuuID(), m_building);
                                            
                                            pCentralScene->m_pCentralLayer->SendAWorker(build, m_building);
                                            
                                            //不显示箭头
                                            m_building->removeSymbol();
                                            
                                            pCentralScene->m_pCentralLayer->buildingAccount(m_building,OperateType_Build);
                                            m_building->z_state_ = UNIT_Z_NORMAL_STATE;
                                            pCentralScene->m_pCentralLayer->m_BuyBuilding = NULL;
                                            pCentralScene->m_pCentralUILayer->InfoBtnAppear(m_building->upgrade_state_,m_building->getTypeID());
                                            
                                            
                                        }
                                    }
                                }
                                
                                
                            }
                            else
                            {
                                //宝石不够
                                DialogLayer* dia = DialogLayer::create();
                                dia->setPosition(ccp(0,0));
                                this->addChild(dia,1000,10000);
                                
                                dia->setShopMenuItem(this,menu_selector(CentralUILayer::cancelShopMenuItemInBattle), menu_selector(CentralUILayer::okShopMenuItemInBattle));
                                
                                dia->setContentString("请进入商城购买宝石");
                            }
                        }
                        
                        
                    }
                }
            }
            
        }
            break;
        default:
            break;
    }
    
    
    CCNode* node = (CCNode*)pSender;
    DialogLayer* dia = (DialogLayer*)node->getParent()->getParent()->getParent();
    dia->removeFromParentAndCleanup(true);
}
void CentralUILayer::cancelGemMenuItemInBattle(CCObject *pSender)
{
    
    
    CCNode* node = (CCNode*)pSender;
    DialogLayer* dia = (DialogLayer*)node->getParent()->getParent()->getParent();
    dia->removeFromParentAndCleanup(true);
}
void CentralUILayer::okShopMenuItemInBattle(CCObject *pSender)
{
    
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    this->setVisible(false);
    
    CentralShopUILayerLoader* centralShopUILayerLoader = CentralShopUILayerLoader::loader();
    
    pCentralScene->m_pCentralShopUILayer = (CentralShopUILayer*) pCentralScene->openTest(GAME_FILE_TRANSFORM("UI_Shop",".ccbi").c_str(),"UI_Shop",centralShopUILayerLoader);
    
    centralShopUILayerLoader->centralShopUILayer->initShopUI();
    
    pCentralScene->m_pCentralShopUILayer->onBox1(NULL);
    pCentralScene->m_pCentralShopUILayer->nextBtn->setVisible(false);
    
    pCentralScene->addChild(pCentralScene->m_pCentralShopUILayer,200);
    
    
    CCNode* node = (CCNode*)pSender;
    DialogLayer* dia = (DialogLayer*)node->getParent()->getParent()->getParent();
    dia->removeFromParentAndCleanup(true);
}
void CentralUILayer::cancelShopMenuItemInBattle(CCObject *pSender)
{
    CCNode* node = (CCNode*)pSender;
    DialogLayer* dia = (DialogLayer*)node->getParent()->getParent()->getParent();
    dia->removeFromParentAndCleanup(true);
}
void CentralUILayer::addDialogLayer(bool _isG, int _rNum, int _tyep)
{
    gemTyep = _tyep;
    DialogLayer* dia = DialogLayer::create();
    dia->setPosition(ccp(0,0));
    this->addChild(dia,1000,10000);
    
    
    
    char strFileName[64];
    //升级资源不足
    if (_tyep == 1)
    {
        gem_Num = BuyResourceGem(_rNum);
        if (_isG)
        {
            sprintf(strFileName,"是否购买%d金币?",_rNum);
        }
        else
        {
            sprintf(strFileName,"是否购买%d粮食?",_rNum);
        }
    }
    //升级队列不足
    else if(_tyep == 2)
    {
        CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
        int num = pCentralScene->m_pCentralLayer->unit_list_->count();
        gem_Num = 99999999;
        gem_UUid = 0;
        for (int i = 0; i <num; i++)
        {
            Unit *unit = (Unit*)pCentralScene->m_pCentralLayer->unit_list_->objectAtIndex(i);
            //如果是建筑
            if (unit->is_build_type())
            {
                BuildingBase* build = (BuildingBase*)unit;
                if (build->upgrade_state_ == UNIT_UPGRADE_IN || build->upgrade_state_ == UNIT_UPGRADE_BUILDIN)
                {
                    long tempTime = Until::millisecondNow_m();
                    
                    long cd_time = tempTime - build->m_uBuildTime;
                    
                    int  S_time = build->m_iBuildCDTime - cd_time;
                    
                    int  gem = pCentralScene->m_pCentralLayer->gemConversion(S_time);
                    
                    if (gem < gem_Num)
                    {
                        gem_Num = gem;
                        gem_UUid = build->getuuID();
                    }
                }
            }
        }

        
        sprintf(strFileName,"是否加速建造?");
    }
    //建造资源不足
    else if(_tyep == 3)
    {
        gem_Num = BuyResourceGem(_rNum);
        if (_isG)
        {
            sprintf(strFileName,"是否购买%d金币?",_rNum);
        }
        else
        {
            sprintf(strFileName,"是否购买%d粮食?",_rNum);
        }
    }
    //建造队列不足
    else if(_tyep == 4)
    {
        CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
        int num = pCentralScene->m_pCentralLayer->unit_list_->count();
        gem_Num = 99999999;
        gem_UUid = 0;
        for (int i = 0; i <num; i++)
        {
            Unit *unit = (Unit*)pCentralScene->m_pCentralLayer->unit_list_->objectAtIndex(i);
            //如果是建筑
            if (unit->is_build_type())
            {
                BuildingBase* build = (BuildingBase*)unit;
                if (build->upgrade_state_ == UNIT_UPGRADE_IN || build->upgrade_state_ == UNIT_UPGRADE_BUILDIN)
                {
                    long tempTime = Until::millisecondNow_m();
                    
                    long cd_time = tempTime - build->m_uBuildTime;
                    
                    int  S_time = build->m_iBuildCDTime - cd_time;
                    
                    int  gem = pCentralScene->m_pCentralLayer->gemConversion(S_time);
                    
                    if (gem < gem_Num)
                    {
                        gem_Num = gem;
                        gem_UUid = build->getuuID();
                    }
                }
            }
        }
        
        
        sprintf(strFileName,"是否加速建造?");
    }
    
    
    dia->setGemMenuItem(this,menu_selector(CentralUILayer::cancelGemMenuItemInBattle), menu_selector(CentralUILayer::okGemMenuItemInBattle),gem_Num);
    
    
    
	
    dia->setContentString(strFileName);
    
}
int CentralUILayer::BuyResourceGem(int _num)
{
    int gem;
    if (_num >= 10000000)
    {
        gem = 3000*_num/10000000;
    }
    else if (_num >= 1000000)
    {
        gem = 600*_num/1000000;
    }
    else if (_num >= 100000)
    {
        gem = 125*_num/100000;
    }
    else if (_num >= 10000)
    {
        gem = 25*_num/10000;
    }
    else if (_num >= 1000)
    {
        gem = 5*_num/1000;
    }
    else if (_num >= 100)
    {
        gem = _num/100;
    }
    else
    {
        gem = 1;
    }
    return gem;
}
void CentralUILayer::vl_nameLeve(bool _isv)
{
    if (_isv)
    {
        const BaseBuildingLevelData* buildingBaseLevelData;
        buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->m_building->getID());
        
        const string* name = GameData::GetTextInfo(buildingBaseLevelData->Text);
        char strName[64];
        sprintf(strName,"%s level%d",name->c_str(),buildingBaseLevelData->build_level);
//        sprintf(strName,"level%d",buildingBaseLevelData->build_level);
        l_nameLeve->setString(strName);
        l_nameLeve->setVisible(true);
    }
    else
    {
        l_nameLeve->setVisible(false);
    }
    
}













SEL_MenuHandler CentralUILayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget,CCString * pSelectorName){
    
    //Bind Menu Events，绑定一个menu，点击方法是press，以下同理
    
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "press",MainScene::press);
    
    return NULL;
    
}

SEL_CCControlHandler CentralUILayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName){
    
    //Bind CCControl Events
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnShop",CentralUILayer::onBtnShop);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMail",CentralUILayer::onBtnMail);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSettings",CentralUILayer::onSettings);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnInfo",CentralUILayer::onBtnInfo);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnUpdate",CentralUILayer::onBtnUpBuild);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnRecruiting",CentralUILayer::onBtnRecruiting);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnPVP",CentralUILayer::onBtnPVP);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onUpSoldiers",CentralUILayer::onUpSoldiers);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMagic",CentralUILayer::onMagic);

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBuildGem",CentralUILayer::onBuildGem);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBuiltToCancel",CentralUILayer::onBuiltToCancel);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCollectG",CentralUILayer::onCollectG);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCollectP",CentralUILayer::onCollectP);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onNAdd",CentralUILayer::onNAdd);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onGAdd",CentralUILayer::onGAdd);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onFAdd",CentralUILayer::onFAdd);

    
    return NULL;
    
}

bool CentralUILayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode){
    
    //Bind variables
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "goldLabel", CCLabelTTF *, this->goldLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "potionsLabel", CCLabelTTF *, this->potionsLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "gemLabel", CCLabelTTF *, this->gemLabel);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "peasantLabel", CCLabelTTF *, this->peasantLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "experienceLabel", CCLabelTTF *, this->experienceLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lvLabel", CCLabelTTF *, this->lvLabel);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "pvpLabel", CCLabelTTF *, this->pvpLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "protectLabel", CCLabelTTF *, this->protectLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "protectLabel2", CCLabelTTF *, this->protectLabel2);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nameLabel", CCLabelTTF *, this->nameLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "goldMaxLabel", CCLabelTTF *, this->goldMaxLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "potionsMaxLabel", CCLabelTTF *, this->potionsMaxLabel);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "peasantLabel2", CCLabelTTF *, this->peasantLabel2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_nameLeve", CCLabelTTF *, this->l_nameLeve);
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "potionsS", CCSprite *, this->potionsS);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "goldS", CCSprite *, this->goldS);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "experienceS", CCSprite *, this->experienceS);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_icong", CCSprite *, this->s_icong);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_icongem", CCSprite *, this->s_icongem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_iconp", CCSprite *, this->s_iconp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_iconlevel", CCSprite *, this->s_iconlevel);
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnBuildGem", CCControlButton *, this->BtnBuildGem);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnResources", CCControlButton *, this->BtnResources);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnCollectP", CCControlButton *, this->btnCollectP);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnCollectG", CCControlButton *, this->btnCollectG);

    
    return false;
    
}
void CentralUILayer::initUI()
{
    GemNumLabel = CCLabelTTF::create("", "Helvetica", 24);
    GemNumLabel->setAnchorPoint(ccp(0,0));
    GemNumLabel->setPosition(ccp(0,0));
    BtnBuildGem->addChild(GemNumLabel,1,1);
    
    
    l_nameLeve->setVisible(false);
    
    
//    CCSprite* jinbi = CCSprite::createWithSpriteFrameName("ui_public_icon_gold.png");
//    jinbi->setPosition(ccp(0, 0));
//    jinbi->setVisible(false);
//    BtnResources->addChild(jinbi,2,2);

    
    CCSprite* shui = CCSprite::createWithSpriteFrameName("ui_map_icon_build1.png");
    shui->setVisible(false);
    shui->setAnchorPoint(ccp(0, 0));
    shui->setPosition(ccp(0, 0));
    BtnResources->addChild(shui,1,1);
    
    resourcesNumLabel = CCLabelTTF::create("", "Helvetica", 8);
    resourcesNumLabel->setAnchorPoint(ccp(0,1));
    resourcesNumLabel->setPosition(ccp(5,shui->getContentSize().width-5));
    BtnResources->addChild(resourcesNumLabel,2,2);

    
    CollectPHui = CCSprite::createWithSpriteFrameName("ui_map_icon_collectPHui.png");
    CollectPHui->setVisible(false);
    CollectPHui->setAnchorPoint(ccp(0, 0));
    CollectPHui->setPosition(ccp(0, 0));
    btnCollectP->addChild(CollectPHui,2,2);
    
    CollectGHui = CCSprite::createWithSpriteFrameName("ui_map_icon_collectGHui.png");
    CollectGHui->setVisible(false);
    CollectGHui->setAnchorPoint(ccp(0, 0));
    CollectGHui->setPosition(ccp(0, 0));
    btnCollectG->addChild(CollectGHui,2,2);
//    
}
void CentralUILayer::onBtnShop(cocos2d::CCObject *pSender) 
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    this->setVisible(false);
    
    CentralShopUILayerLoader* centralShopUILayerLoader = CentralShopUILayerLoader::loader();

    pCentralScene->m_pCentralShopUILayer = (CentralShopUILayer*) pCentralScene->openTest(GAME_FILE_TRANSFORM("UI_Shop",".ccbi").c_str(),"UI_Shop",centralShopUILayerLoader);
    
    centralShopUILayerLoader->centralShopUILayer->initShopUI();

    pCentralScene->addChild(pCentralScene->m_pCentralShopUILayer,200);
}

void CentralUILayer::onBtnMail(cocos2d::CCObject *pSender)
{    
//    if(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_BattleInfoList.size() == 0) return;
    
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    this->setVisible(false);
    
    CentralMailUILayerLoader* centralMailUILayerLoader = CentralMailUILayerLoader::loader();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GAME_FILE_TRANSFORM("soldiers_Icon",".plist").c_str(),GAME_FILE_TRANSFORM("soldiers_Icon",".png").c_str());
    
    pCentralScene->m_pCentralMailUILayer = (CentralMailUILayer*) pCentralScene->openTest(GAME_FILE_TRANSFORM("UI_Mail",".ccbi").c_str(),"UI_Mail",centralMailUILayerLoader);
    
    
    
    pCentralScene->addChild(pCentralScene->m_pCentralMailUILayer,200);
    pCentralScene->m_pCentralMailUILayer->initCentralMailUI();
    
}

void CentralUILayer::onSettings(cocos2d::CCObject * pSender)
{    
    // 隐藏CentralUILayer及触摸事件
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    this->setVisible(false);
    
    // 显示设置界面
    CentralSettingsUILayerLoader* centralSettingsUILayerLoader = CentralSettingsUILayerLoader::loader();

    
    pCentralScene->m_pCentralSettingsUILayer = (CentralSettingsUILayer*) pCentralScene->openTest(GAME_FILE_TRANSFORM("UI_Settings",".ccbi").c_str(),"UI_Settings",centralSettingsUILayerLoader);
    
    pCentralScene->addChild(pCentralScene->m_pCentralSettingsUILayer,200);
    pCentralScene->m_pCentralSettingsUILayer->initCentralSettingsUI();
}

void CentralUILayer::onBtnRecruiting(cocos2d::CCObject * pSender)
{    
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    CentralInfoUILayerLoader* centralInfoUILayerLoader = CentralInfoUILayerLoader::loader();
    
    pCentralScene->m_pCentralInfoUILayer = (CentralInfoUILayer*)pCentralScene->openTest(GAME_FILE_TRANSFORM("UI_Info",".ccbi").c_str(),"UI_Info",centralInfoUILayerLoader);
    
    pCentralScene->addChild(pCentralScene->m_pCentralInfoUILayer,200);
    pCentralScene->m_pCentralInfoUILayer->infoUILayer(ARMY_BARRACK,UIType_build);
    
}
void CentralUILayer::onBtnUpBuild(cocos2d::CCObject * pSender)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    //崩溃
    CentralInfo2UILayerLoader* centralInfo2UILayerLoader = CentralInfo2UILayerLoader::loader();
    
    pCentralScene->m_pCentralInfo2UILayer = (CentralInfo2UILayer*)pCentralScene->openTest(GAME_FILE_TRANSFORM("UI_Info2",".ccbi").c_str(),"UI_Info2",centralInfo2UILayerLoader);
    
    pCentralScene->addChild(pCentralScene->m_pCentralInfo2UILayer,200);
    pCentralScene->m_pCentralInfo2UILayer->updataUILayer();
    
    
    
}

void CentralUILayer::onBtnPVP(cocos2d::CCObject * pSender)
{
    CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    
    SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->uploadAccount();
    
    bool flag = false;
    for (int i=0; i<data->m_BuildableSoldiers->size(); i++) {
        CentralData::BuildableSoldiers * s= data->m_BuildableSoldiers->at(i);
        if (s->num != 0) {
            flag = true;
            break;
        }
    }
    if(flag || NotNetworking){
        CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
        
        CentralPVPUILayerLoader* centralPVPUILayerLoader = CentralPVPUILayerLoader::loader();
        
        pCentralScene->m_pCentralPVPUILayer = (CentralPVPUILayer*)pCentralScene->openTest(GAME_FILE_TRANSFORM("UI_PvpAndPve",".ccbi").c_str(),"UI_PvpAndPve",centralPVPUILayerLoader);
        
        pCentralScene->addChild(pCentralScene->m_pCentralPVPUILayer,201);
        pCentralScene->m_pCentralPVPUILayer->initCentralPVPUI();
    }else {
        // 如果没有兵给出提示
        const string* strtext = GameData::GetTextInfo("TID_NO_TROOPS");
        TipInfo *info = TipInfo::create();
        info->setString(strtext->c_str(), ccp( GamePlatform::GetScreenSize().width/2, GamePlatform::GetScreenSize().height/2+100),3.0f);
        this->addChild(info);
    }
}

void CentralUILayer::onUpSoldiers(cocos2d::CCObject * pSender)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    CentralInfoUILayerLoader* centralInfoUILayerLoader = CentralInfoUILayerLoader::loader();
    
    pCentralScene->m_pCentralInfoUILayer = (CentralInfoUILayer*)pCentralScene->openTest(GAME_FILE_TRANSFORM("UI_Info",".ccbi").c_str(),"UI_Info",centralInfoUILayerLoader);
    
    pCentralScene->addChild(pCentralScene->m_pCentralInfoUILayer,200);
    pCentralScene->m_pCentralInfoUILayer->infoUILayer(ARMY_LABORATORY,UIType_build);
}
void CentralUILayer::onBuildGem(cocos2d::CCObject * pSender)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    if (GemNumLabel != NULL)
    {
        if (pCentralScene->m_pCentralLayer->m_building != NULL)
        {
            if (pCentralScene->m_pCentralLayer->m_building->upgrade_state_ == UNIT_UPGRADE_BUILDIN
                || pCentralScene->m_pCentralLayer->m_building->upgrade_state_ == UNIT_UPGRADE_IN) 
            {
                long tempTime = Until::millisecondNow_m();
                long cd_time = tempTime - pCentralScene->m_pCentralLayer->m_building->m_uBuildTime;
                int  S_time = pCentralScene->m_pCentralLayer->m_building->m_iBuildCDTime - cd_time;
                int  G_num = pCentralScene->m_pCentralLayer->gemConversion(S_time);
                
                if (updateGem(-G_num))
                {
                    
                    
                    
                    
                    pCentralScene->m_pCentralLayer->Accelerated_id = pCentralScene->m_pCentralLayer->m_building->getTypeID();
                    pCentralScene->m_pCentralLayer->Accelerated_uuid = pCentralScene->m_pCentralLayer->m_building->getuuID();
                    pCentralScene->m_pCentralLayer->Accelerated_remain_time = S_time;
                    pCentralScene->m_pCentralLayer->Accelerated_gem_count = G_num;
                    
                    if (pCentralScene->m_pCentralLayer->m_building->upgrade_state_ == UNIT_UPGRADE_BUILDIN)
                    {
                        pCentralScene->m_pCentralLayer->buildingAccelerated(AccelerateType_Building);
                    }
                    else if(pCentralScene->m_pCentralLayer->m_building->upgrade_state_ == UNIT_UPGRADE_IN)
                    {
                        pCentralScene->m_pCentralLayer->buildingAccelerated(AccelerateType_UPBuilding);
                    }
                    
                    
                    
                    pCentralScene->m_pCentralLayer->m_building->BuildingComplete();
                    
                }
                else
                {
                    //宝石不够
                    DialogLayer* dia = DialogLayer::create();
                    dia->setPosition(ccp(0,0));
                    this->addChild(dia,1000,10000);
                    
                    dia->setShopMenuItem(this,menu_selector(CentralUILayer::cancelShopMenuItemInBattle), menu_selector(CentralUILayer::okShopMenuItemInBattle));
                    
                    dia->setContentString("请进入商城购买宝石");
                }
                
                
            }
        }
    }
}
void CentralUILayer::onNAdd(cocos2d::CCObject * pSender)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    this->setVisible(false);
    
    CentralShopUILayerLoader* centralShopUILayerLoader = CentralShopUILayerLoader::loader();
    
    pCentralScene->m_pCentralShopUILayer = (CentralShopUILayer*) pCentralScene->openTest(GAME_FILE_TRANSFORM("UI_Shop",".ccbi").c_str(),"UI_Shop",centralShopUILayerLoader);
    
    centralShopUILayerLoader->centralShopUILayer->initShopUI();
    
    pCentralScene->m_pCentralShopUILayer->BtnTyep = 2;
    for (int i = 0; i < 1; i++)
    {
        
        int num = 0;
        
        switch (i)
        {
            case 0:
                num = 500;
                break;
            default:
                break;
        }
        const BaseBuildingLevelData* buildingBaseLevelData;
        buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( num*100+1);
        const string* name = GameData::GetTextInfo(buildingBaseLevelData->Text);
        CCLabelTTF* timeLabel = CCLabelTTF::create(name->c_str(), "Helvetica", 12);
        pCentralScene->m_pCentralShopUILayer->labelArr->addObject(timeLabel);
        
        
        IconSprite* build = (IconSprite*)CCSprite::create(GAME_FILE_TRANSFORM(buildingBaseLevelData->ExportName.c_str(),".png").c_str());
        build->type = num;
        if (!pCentralScene->m_pCentralShopUILayer->isAllBuild(build->type))
        {
            build->setColor(ccc3(96, 96, 96));
        }
        
        
        pCentralScene->m_pCentralShopUILayer->spriteArr->addObject(build);
        
    }
    
    pCentralScene->m_pCentralShopUILayer->BoxBtnV(false);
    
    pCentralScene->m_pCentralShopUILayer->addTableView();
    pCentralScene->m_pCentralShopUILayer->nextBtn->setVisible(false);
    
    pCentralScene->addChild(pCentralScene->m_pCentralShopUILayer,200);
}
void CentralUILayer::onGAdd(cocos2d::CCObject * pSender)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    this->setVisible(false);
    
    CentralShopUILayerLoader* centralShopUILayerLoader = CentralShopUILayerLoader::loader();
    
    pCentralScene->m_pCentralShopUILayer = (CentralShopUILayer*) pCentralScene->openTest(GAME_FILE_TRANSFORM("UI_Shop",".ccbi").c_str(),"UI_Shop",centralShopUILayerLoader);
    
    centralShopUILayerLoader->centralShopUILayer->initShopUI();
    
    pCentralScene->m_pCentralShopUILayer->onBox1(NULL);
    pCentralScene->m_pCentralShopUILayer->nextBtn->setVisible(false);
    
    pCentralScene->addChild(pCentralScene->m_pCentralShopUILayer,200);
}
void CentralUILayer::onFAdd(cocos2d::CCObject * pSender)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    this->setVisible(false);
    
    CentralShopUILayerLoader* centralShopUILayerLoader = CentralShopUILayerLoader::loader();
    
    pCentralScene->m_pCentralShopUILayer = (CentralShopUILayer*) pCentralScene->openTest(GAME_FILE_TRANSFORM("UI_Shop",".ccbi").c_str(),"UI_Shop",centralShopUILayerLoader);
    
    centralShopUILayerLoader->centralShopUILayer->initShopUI();
    pCentralScene->m_pCentralShopUILayer->nextBtn->setVisible(false);
    
    pCentralScene->m_pCentralShopUILayer->onBox6(NULL);
    pCentralScene->m_pCentralShopUILayer->nextBtn->setVisible(false);
    
    pCentralScene->addChild(pCentralScene->m_pCentralShopUILayer,200);
}
void CentralUILayer::onCollectG(cocos2d::CCObject * pSender)
{
    SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->m_building->isHarvest = true;
    SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->m_building->addResources();
}

void CentralUILayer::onCollectP(cocos2d::CCObject * pSender)
{
    SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->m_building->isHarvest = true;
    SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->m_building->addResources();
}
void CentralUILayer::onBuiltToCancel(cocos2d::CCObject * pSender)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    if (pCentralScene->m_pCentralLayer->m_building != NULL)
    {
        InfoBtnDisappear(pCentralScene->m_pCentralLayer->m_building->upgrade_state_,pCentralScene->m_pCentralLayer->m_building->getTypeID());
        if (pCentralScene->m_pCentralLayer->m_building->upgrade_state_ == UNIT_UPGRADE_IN) 
        {
            pCentralScene->m_pCentralLayer->m_building->upgrade_state_ = UNIT_UPGRADE_FAIL;
            A_time = 0;
            is_A = true;
        }
        else if (pCentralScene->m_pCentralLayer->m_building->upgrade_state_ == UNIT_UPGRADE_BUILDIN) 
        {
            pCentralScene->m_pCentralLayer->m_building->upgrade_state_ = UNIT_UPGRADE_BUILDFAIL;
            pCentralScene->m_pCentralLayer->m_building = NULL;
        }
    }
    
    
    
    
}
void CentralUILayer::onMagic(cocos2d::CCObject * pSender)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    CentralInfoUILayerLoader* centralInfoUILayerLoader = CentralInfoUILayerLoader::loader();
    
    pCentralScene->m_pCentralInfoUILayer = (CentralInfoUILayer*)pCentralScene->openTest(GAME_FILE_TRANSFORM("UI_Info",".ccbi").c_str(),"UI_Info",centralInfoUILayerLoader);
    
    pCentralScene->addChild(pCentralScene->m_pCentralInfoUILayer,200);
    pCentralScene->m_pCentralInfoUILayer->infoUILayer(ARMY_SPELLFORGE,UIType_build);
}
void CentralUILayer::onBtnInfo(cocos2d::CCObject *pSender) 
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    CentralInfo2UILayerLoader* centralInfo2UILayerLoader = CentralInfo2UILayerLoader::loader();
    
    pCentralScene->m_pCentralInfo2UILayer = (CentralInfo2UILayer*)pCentralScene->openTest(GAME_FILE_TRANSFORM("UI_Info2",".ccbi").c_str(),"UI_Info2",centralInfo2UILayerLoader);
    
    pCentralScene->addChild(pCentralScene->m_pCentralInfo2UILayer,200);
    pCentralScene->m_pCentralInfo2UILayer->infoUILayer();
}


void CentralUILayer::onNodeLoaded(CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader){
    
    //检测scene
    
    CCLOG("MainScene loading.....successed!") ;
    
}


void CentralUILayer::ShowBtnAnim(const char * pCCBFileName)
{
    mAnimationManager->runAnimations(pCCBFileName,0.0);
}

void CentralUILayer::InfoBtnAppear(int _tyep,int _Build)
{
    
    vl_nameLeve(true);
    if( SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enCentralViewMode == CENTRALVIEW_VISIT )
    {
        ShowBtnAnim("friendBtnAppearAnim");
    }
    else
    {
        if (_tyep == UNIT_UPGRADE_NONE)
        {
            switch (_Build)
            {
                case ARMY_BARRACK:
                {
                    ShowBtnAnim("InfoBarracksBtnAppearAnim");
                }
                    break;
                case ARMY_LABORATORY:
                {
                    ShowBtnAnim("InfoUpSolodiersBtnAppearAnim");
                }
                    break;
                case ARMY_SPELLFORGE:
                {
                    ShowBtnAnim("InfoMagicBtnAppearAnim");
                }
                    break;
                case RESOURCE_ELIXIRPUMP:
                {
                    ShowBtnAnim("collectPBtnAppearAnim");
                }
                    break;
                case RESOURCE_GOLDMINE:
                {
                    ShowBtnAnim("collectGBtnAppearAnim");
                }
                    break;
                case BUILDINGTYPE_WORKER:
                {
                    ShowBtnAnim("workBtnAppearAnim");
                }
                    break;
                default:
                {
                    ShowBtnAnim("InfoBtnAppearAnim");
                }
                    
                    break;
            }
        }
        else 
        {
            
            
            ShowBtnAnim("upingBtnAppearAnim");
        }
    }
    
    
    
}

void CentralUILayer::InfoBtnDisappear(int _tyep,int _Build)
{
    vl_nameLeve(false);
    if( SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enCentralViewMode == CENTRALVIEW_VISIT )
    {
        ShowBtnAnim("friendBtnDisappearAnim");
    }
    else
    {
        if (_tyep == UNIT_UPGRADE_NONE)
        {
            switch (_Build)
            {
                case ARMY_BARRACK:
                {
                    ShowBtnAnim("InfoBarracksBtnDisappearAnim");
                }
                    break;
                case ARMY_LABORATORY:
                {
                    ShowBtnAnim("InfoUpSolodiersBtnDisappearAnim");
                }
                    break;
                case ARMY_SPELLFORGE:
                {
                    ShowBtnAnim("InfoMagicBtnDisappearAnim");
                }
                    break;
                case RESOURCE_ELIXIRPUMP:
                {
                    ShowBtnAnim("collectPBtnDisappearAnim");
                }
                    break;
                case RESOURCE_GOLDMINE:
                {
                    ShowBtnAnim("collectGBtnDisappearAnim");
                }
                    break;
                case BUILDINGTYPE_WORKER:
                {
                    ShowBtnAnim("workBtnDisappearAnim");
                }
                    break;
                default:
                {
                    ShowBtnAnim("InfoBtnDisappearAnim");
                }
                    
                    break;
            }
        }
        else
        {
            ShowBtnAnim("upingBtnDisappearAnim");
        }
    }
    
    
    
    
    
}

void CentralUILayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = pAnimationManager;
    CC_SAFE_RETAIN(mAnimationManager);
}




















