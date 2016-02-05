#include "BuildingBase.h"
#include "GameControl.h"
#include "NetMessageManager.h"
#include "TipNode.h"
#include "Until.h"
#include "CommonResource.h"
#include "cocos2d.h"
#include <math.h>
#include <iostream>
using namespace std;
using namespace cocos2d;

BuildingBase::BuildingBase()
{
	memset(&m_stBuildSubstrate,0,sizeof(BUILDSUBSTRATE));
    memset(m_pSpriteBuildArrow,0, sizeof(int)*4);
    
	m_uBuildTime = 0;
	m_iBuildCDTime = 5;
    buildEventTime = 0;
    buildEventCDTime = 0;
    buildxiaoguoEventTime = 0;
    tipNode = NULL;
    upgrade_state_ = UNIT_UPGRADE_NO;
    resourcesMinNum = 2;
    resourcesMaxNum = 100;
    resourcesGoldNum = 0;
    resourcesPotionsNum = 0;
    removeEventTime = 0;  
    removeEventCDTime = 0;
    m_peopleSoldiers = NULL;
    m_UpPeopleSoldiers = NULL;
    m_jianPeopleSoldiers = NULL;
    m_magicBuild = NULL;
    UpLeveTyep = 0;       
    UpLeveTime = 0;  
    UPLeveCDTime = 0;
    isBusy = false;
    isAddsu = false;
    productionState = Production_State_Null;
    allProductionTime = 0;
    isSafety =  true;
    isBiaoxian = false;
    isManNum = false;
    biaoTime = 0;
    savsTime = 0;
    duileiNum = 0;
    duileiMAXNum = 0;
    
    for( int i = 0; i < 4; i++ )
	{
		m_pSpriteBuildArrow[i] = NULL;
	}
    menu = NULL; 

	m_pWorker = NULL;
}

BuildingBase::~BuildingBase()
{
    CleanData();
    
    
    if (m_UpPeopleSoldiers != NULL)
    {
        delete m_UpPeopleSoldiers;
    }
    if (m_jianPeopleSoldiers != NULL)
    {
        delete m_jianPeopleSoldiers;
    }
    
    
    if (m_peopleSoldiers != NULL)
    {
        delete m_peopleSoldiers;
    }
    
    if (m_magicBuild != NULL)
    {
        delete m_magicBuild;
    }

}
void BuildingBase::CleanData( void )
{
    if (m_UpPeopleSoldiers != NULL) {
        for( int i = 0; i < (int)m_UpPeopleSoldiers->size(); i++ )
        {
            delete m_UpPeopleSoldiers->at(i);

        }
        m_UpPeopleSoldiers->clear();

    }
    if (m_jianPeopleSoldiers != NULL) {
        for( int i = 0; i < (int)m_jianPeopleSoldiers->size(); i++ )
        {
            delete m_jianPeopleSoldiers->at(i);
            
        }
        m_jianPeopleSoldiers->clear();
        
    }
    
    if (m_peopleSoldiers != NULL) {
        for( int i = 0; i < (int)m_peopleSoldiers->size(); i++ )
        {
            delete m_peopleSoldiers->at(i);

        }
        m_peopleSoldiers->clear();

    }
    
    if (m_magicBuild != NULL) {
        for( int i = 0; i < (int)m_magicBuild->size(); i++ )
        {
            delete m_magicBuild->at(i);

        }
        m_magicBuild->clear();

    }
    
}

BuildingBase* BuildingBase::BuildWithData(int unitID)
{
	BuildingBase* pRet = new BuildingBase();
	if( pRet->init(unitID) )
	{
		pRet->autorelease();
	}
	else
	{
		delete pRet;
		pRet = NULL;
	}
	return pRet;
}

bool BuildingBase::init(int unitID)
{
    if(Unit::init(NULL)){
        const BaseBuildingLevelData* buildingBaseLevelData;
        buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( unitID);
        
        BuildingBase::BUILDSUBSTRATE bstrate;
        bstrate.m_Line = buildingBaseLevelData->Width;
        bstrate.m_Row = buildingBaseLevelData->Height;
		bstrate.m_pointSubstrate = (ccp(0,0));

        m_u32ID = unitID;  // 建筑的ID
        m_uTypeID = buildingBaseLevelData->building_TypeID;
    
        m_stBuildSubstrate.m_pointSubstrate = bstrate.m_pointSubstrate;
        m_stBuildSubstrate.m_Line = bstrate.m_Line;
        m_stBuildSubstrate.m_Row = bstrate.m_Row;
    
        if (false && m_stBuildSubstrate.m_Row == 1 && m_stBuildSubstrate.m_Row == 1  )
        {
            m_pSubstrateBottom = CCSprite::create();
            m_pSubstrateBottom->setPosition(ccp(0,0));
            m_pSubstrateBottom->setScale(0.3333);
            CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
            data->m_tmxMap->addChild(m_pSubstrateBottom,-100);
            m_pSubstrateBottom->setAnchorPoint(ccp(0.5,0));
        }
        else
        {
            char strFile[64];
            sprintf(strFile,"build_%d_%d",m_stBuildSubstrate.m_Line,m_stBuildSubstrate.m_Row);			
            m_pSubstrateBottom = CCSprite::create(GAME_FILE_TRANSFORM(strFile,".png").c_str());
            m_pSubstrateBottom->setPosition(ccp(0,0));
            m_pSubstrateBottom->setScale(0.5);
            CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
            data->m_tmxMap->addChild(m_pSubstrateBottom,-100);
            m_pSubstrateBottom->setAnchorPoint(ccp(0.5,0));
        }
        ccl = m_pSubstrateBottom->getColor();
        
        //绘制建筑图
        drawBuild(buildingBaseLevelData->ExportName);
        
        char strName[64];
        sprintf(strName,"%s \nlevel%d",buildingBaseLevelData->Name.c_str(),buildingBaseLevelData->build_level);
        drawNameLabel(sprite_, strName);
    }
	return true;
}

void BuildingBase::initBuildingNumerical()
{
    //建筑功能记时
    switch (this->getTypeID())
    {
        case RESOURCE_ELIXIRPUMP:
        {
            buildEventTime = Until::millisecondNow_m();
            buildxiaoguoEventTime = Until::millisecondNow_m();
            resourcesPotionsNum = 0;
            isHarvest = false;
        }
            break;
        case RESOURCE_GOLDMINE:
        {
            buildEventTime = Until::millisecondNow_m();
            buildxiaoguoEventTime = Until::millisecondNow_m();
            resourcesGoldNum = 0;
            isHarvest = false;
        }
            break;
        default:
            break;
    }
}
void BuildingBase::setUploadSoldiersArr()
{
    if (m_peopleSoldiers == NULL) return;
    
    if (m_UpPeopleSoldiers == NULL)
    {
        m_UpPeopleSoldiers  = new vector<PeopleSoldiers*>;
    }
    
    int num = (int)m_peopleSoldiers->size();
    for (int i = 0; i <num; i++) 
    {
        PeopleSoldiers* soldiers = m_peopleSoldiers->at(i);

        if (soldiers->uploadNum>0)
        {
            
            
            PeopleSoldiers *soldiers2 = new PeopleSoldiers();
            memset( soldiers2,0,sizeof(PeopleSoldiers) );
            
            soldiers2->tyep = soldiers->tyep;
            soldiers2->num = soldiers->uploadNum;
            soldiers2->S_time = soldiers->S_time;
            soldiers2->uuid = soldiers->uuid;
            soldiers2->index = soldiers->index;
            m_UpPeopleSoldiers->push_back(soldiers2);
            soldiers->uploadNum = 0;
        }
    }
    
}
void BuildingBase::upLeveMagicSoldiers(int _tyep,bool _isMroS,int _time)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    isMroS = _isMroS;
    
    UPLeveCDTime = _time;
    UpLeveTyep = _tyep;       
    UpLeveTime = Until::millisecondNow_m();  
    
    if(_isMroS)
    {
        pCentralScene->m_pCentralLayer->buildingAccount(this,OperateType_UpgradeMagic);
    }
    else
    {
        pCentralScene->m_pCentralLayer->buildingAccount(this,OperateType_UpgradeSoldiers);
    }
    
    
}
void BuildingBase::BuildingComplete()
{
    isAddsu = true;
    if (upgrade_state_ == UNIT_UPGRADE_BUILDIN) 
    {
        upgrade_state_ = UNIT_UPGRADE_BUILDSUCESS;
        UpdataBuilding(0.014);
    }
    else if (upgrade_state_ == UNIT_UPGRADE_IN)
    {
        upgrade_state_ = UNIT_UPGRADE_SUCESS;
        UpdataBuilding(0.014);
    }
}
void BuildingBase::ImmediatelyComplete()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    switch (m_uTypeID)
    {
        case ARMY_BARRACK:
        {
            if (m_peopleSoldiers != NULL) 
            {
                isSafety = false;
                if ((int)m_peopleSoldiers->size() > 0)
                {
                    
                    pCentralScene->m_pCentralLayer->isUPSoldiers = false;
                    pCentralScene->m_pCentralLayer->uploadRecruiting();
                    pCentralScene->m_pCentralLayer->buildingAccelerated(AccelerateType_MadeSoldiersAccelerated);

                                        
                    
                    for( int i = 0; i < (int)m_peopleSoldiers->size(); i++ )
                    {
                        const BasePeopleData* pdata = GameData::GetDataFromBasePeopleData(m_peopleSoldiers->at(i)->tyep*100000+1);
                        pCentralScene->m_pCentralData->m_Central_UserData->allYouPeopleNum += pdata->HousingSpace*m_peopleSoldiers->at(i)->num;
                        for (int j = 0; j < m_peopleSoldiers->at(i)->num; j++) 
                        {
                            //建兵
                            Unit* u = pCentralScene->m_pCentralLayer->AddPeople(m_peopleSoldiers->at(i)->tyep * 100000 +1, this->getPosition(),NULL);
                            u->unit_ai_cmd_ = UNIT_AI_PATROL;
                            
                            for (int k=0; k<pCentralScene->m_pCentralData->m_BuildableSoldiers->size(); k++) {
                                CentralData::BuildableSoldiers* s = pCentralScene->m_pCentralData->m_BuildableSoldiers->at(k);
                                if (s->type == m_peopleSoldiers->at(i)->tyep) {
                                    s->num++;
                                    break;
                                }
                            }
                        }
                    }
                    
                    if (pCentralScene->m_pCentralInfoUILayer != NULL) 
                    {
                        if (pCentralScene->m_pCentralInfoUILayer->m_type == ARMY_BARRACK) 
                        {
                            if (pCentralScene->m_pCentralInfoUILayer->arrIcon != NULL)
                            {
                                for (int i = 0; i < pCentralScene->m_pCentralInfoUILayer->arrIcon->count(); i++)
                                {
                                    CCSprite* icon = (CCSprite*)pCentralScene->m_pCentralInfoUILayer->arrIcon->objectAtIndex(i);
                                    
                                    CCLabelTTF *timeLabel = (CCLabelTTF*)icon->getChildByTag(1);
                                    if (timeLabel != NULL)
                                    {
                                        timeLabel->setString("");
                                    }
                                    
                                }
                                for (int i = 0; i < pCentralScene->m_pCentralInfoUILayer->arrAIcon->count(); i++)
                                {
                                    CCSprite* iconA = (CCSprite*)pCentralScene->m_pCentralInfoUILayer->arrAIcon->objectAtIndex(i);
                                    iconA->removeFromParentAndCleanup(false);
                                }
                                pCentralScene->m_pCentralInfoUILayer->arrAIcon->removeAllObjects();
                                
                                pCentralScene->m_pCentralInfoUILayer->btn_SpeedUp->setVisible(false);
                                pCentralScene->m_pCentralInfoUILayer->m_AllTimeLabel->setString("");
                                pCentralScene->m_pCentralInfoUILayer->m_AllPeopleLabel->setString("");
                                pCentralScene->m_pCentralInfoUILayer->s_bgl1->setVisible(false);
                                pCentralScene->m_pCentralInfoUILayer->s_bgl3->setVisible(false);
                            }
                        } 
                    }
                    
                    allProductionTime = 0;
                    for( int i = 0; i < (int)m_peopleSoldiers->size(); i++ )
                    {
                        delete m_peopleSoldiers->at(i);
                        
                    }
                    m_peopleSoldiers->clear();
                }
                
                isSafety = true;
            }
            
        }
            break;
        case ARMY_LABORATORY:
        {
            //升级成功
            if (tipNode != NULL)
            {
                //回收动画
                tipNode->removeFromParentAndCleanup(false);
                tipNode = NULL;
            }
            
            pCentralScene->m_pCentralLayer->Accelerated_upid = UpLeveTyep;
            upLeveComplete(UpLeveTyep);
            UpLeveTyep = 0;
            //上传服务器
            if (isMroS)
            {
                pCentralScene->m_pCentralLayer->buildingAccelerated(AccelerateType_UpMagicAccelerated);
            }
            else
            {
                pCentralScene->m_pCentralLayer->buildingAccelerated(AccelerateType_UpMadeSoldiersAccelerated);
            }
            
        }
            break;
        case ARMY_SPELLFORGE:
        {

            if (m_magicBuild != NULL) 
            {
                for( int i = 0; i < (int)m_magicBuild->size(); i++ )
                {

                }
            }
        }
            break;
        default:
            break;
    }
}
void BuildingBase::updataProductionState()
{
    switch (m_uTypeID) 
    {
        case ARMY_BARRACK:
        {
            int num = 0;
            if (m_peopleSoldiers != NULL) 
            {
                for( int i = 0; i < (int)m_peopleSoldiers->size(); i++ )
                {
                    num += m_peopleSoldiers->at(i)->num;
                }
            }
            const BaseBuildingLevelData* BaseBuildingLevelData;
            BaseBuildingLevelData = GameData::GetDataFromBaseBuildingLevelData(m_uTypeID * 100 + lv);
            
            if (num == 0)
            {
                productionState = Production_State_Null;
            }
            if (num >= BaseBuildingLevelData->UnitProduction) 
            {
                productionState = Production_State_Full;
            }
            else
            {
                productionState = Production_State_Add;
            }

        }
            break;
        case ARMY_LABORATORY:
        {
            
        }
            break;
        case ARMY_SPELLFORGE:
        {
            int num = 0;
            if (m_magicBuild != NULL) 
            {
                for( int i = 0; i < (int)m_magicBuild->size(); i++ )
                {
                    num += m_magicBuild->at(i)->num;
                }
            }
            const BaseBuildingLevelData* BaseBuildingLevelData;
            BaseBuildingLevelData = GameData::GetDataFromBaseBuildingLevelData(m_uTypeID * 100 + lv);
            
            if (num == 0)
            {
                productionState = Production_State_Null;
            }
            if (num >= BaseBuildingLevelData->UnitProduction) 
            {
                productionState = Production_State_Full;
            }
            else
            {
                productionState = Production_State_Add;
            }
            
        }
            break;
        default:
            break;
    }
}
void BuildingBase::upLeveComplete(int _tyep)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    if(isMroS)
    {
        for( int i = 0; i < (int)pCentralScene->m_pCentralData->m_BuildableMagic->size(); i++ )
        {
            if (pCentralScene->m_pCentralData->m_BuildableMagic->at(i)->type == _tyep)
            {
                pCentralScene->m_pCentralData->m_BuildableMagic->at(i)->leve += 1;
            }
        }
    }
    else
    {
        for( int i = 0; i < (int)pCentralScene->m_pCentralData->m_BuildableSoldiers->size(); i++ )
        {
            if (pCentralScene->m_pCentralData->m_BuildableSoldiers->at(i)->type == _tyep)
            {
                pCentralScene->m_pCentralData->m_BuildableSoldiers->at(i)->leve +=1;
            }
        }
    }
    
    if (pCentralScene->m_pCentralInfoUILayer != NULL) 
    {
        if (pCentralScene->m_pCentralInfoUILayer->m_type == ARMY_LABORATORY) 
        {
            pCentralScene->m_pCentralInfoUILayer->reomUpSoldiersing();
            pCentralScene->m_pCentralInfoUILayer->infoUpSoldiers();
        }
    }
    
}
void BuildingBase::addMagicBuild(int _tyep)
{
    if (m_magicBuild == NULL)
    {
        m_magicBuild  = new vector<magicBuild*>;
    }
    
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
        
    if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralUILayer->updateGold(-1))
    {
        CentralData::BuildableMagic* temp = pCentralScene->m_pCentralData->getBuildableMagic(_tyep);
        
        const BaseSpellData* baseSpellData;
        baseSpellData = GameData::GetDataFromBaseSpellData(temp->type * 100 + temp->leve);
        
        int s_num = 0;
        bool isHave = false;
        int num = (int)m_magicBuild->size();
        for (int i = 0; i <num; i++)
        {
            magicBuild* soldiers = m_magicBuild->at(i);
            
            if (soldiers->tyep == _tyep)
            {
                soldiers->num += 1;
                s_num = soldiers->num;
                isHave = true;
            }
        }
        
        
        if (!isHave)
        {
            
            magicBuild *soldiers = new magicBuild();
            memset( soldiers,0,sizeof(magicBuild) );
            soldiers->tyep = _tyep;
            soldiers->num = 1;
            soldiers->MAXTime = baseSpellData->TrainingTime;
            soldiers->time = 0;
            s_num = soldiers->num;
            m_magicBuild->push_back(soldiers);
            
        }
        magicTyep = _tyep;

        isCancelMagic = 0;
        
        pCentralScene->m_pCentralLayer->buildingAccount(this,OperateType_MadeMagic);
        
        
        
        if (pCentralScene->m_pCentralInfoUILayer != NULL) {
            
            if (pCentralScene->m_pCentralInfoUILayer->arrIcon != NULL)
            {
                CCSprite* icon = (CCSprite*)pCentralScene->m_pCentralInfoUILayer->arrIcon->objectAtIndex(_tyep-1);
                
                CCLabelTTF *timeLabel = (CCLabelTTF*)icon->getChildByTag(1);
                
                timeLabel->setString(CommonResource::getStringFromInt(s_num).c_str());
            }
            
        }
    }
}

void BuildingBase::addInfoSoldiers(int _tyep,string _endTime ,int _num,int _index,int _leve)
{
    if (m_peopleSoldiers == NULL)
    {
        m_peopleSoldiers  = new vector<PeopleSoldiers*>;
    }
    
    const BasePeopleData* basePeopleData;
    basePeopleData = GameData::GetDataFromBasePeopleData(_tyep * PEOPLE_TYPE_ *100 + _leve);
    duileiNum += _num*basePeopleData->HousingSpace;
    //long endTime = CommonResource::getLongFromString(_endTime.c_str());
    long endtime = Until::time_millisecondNow(_endTime);
    
    long xianTime = 0;
    long staTime = 0;
    xianTime = Until::millisecondNow_m();
    staTime = (basePeopleData->TrainingTime * _num);
    
    
    PeopleSoldiers *soldiers = new PeopleSoldiers();
    memset( soldiers,0,sizeof(PeopleSoldiers) );
    soldiers->tyep = _tyep;
    soldiers->num = _num;
    soldiers->MAXTime = basePeopleData->TrainingTime;
    soldiers->time = endtime;
    soldiers->uploadNum = 0;
    soldiers->uuid = this->getuuID();
    
    
    soldiers->S_time = endtime;
    soldiers->index = _index;
    if (endtime != 0)
    {
        allProductionTime += staTime - ( xianTime - endtime ) ;
    }
    else
    {
        allProductionTime += staTime;
    }
    
    m_peopleSoldiers->push_back(soldiers);
}

void BuildingBase::jianSoldiers(int _tyep)
{
    if (m_jianPeopleSoldiers == NULL)
    {
        m_jianPeopleSoldiers  = new vector<PeopleSoldiers*>;
    }
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    CentralData::BuildableSoldiers* temp = pCentralScene->m_pCentralData->getBuildableSoldiers(_tyep);
    
    const BasePeopleData* basePeopleData;
    basePeopleData = GameData::GetDataFromBasePeopleData(temp->type * PEOPLE_TYPE_ *100 + temp->leve);
    pCentralScene->m_pCentralData->m_Central_UserData->allPeopleNum -= basePeopleData->HousingSpace;
    duileiNum-=basePeopleData->HousingSpace;
    
    for (int i = 0; i <(int)m_peopleSoldiers->size(); i++)
    {
        PeopleSoldiers* soldiers = m_peopleSoldiers->at(i);
        
        if(soldiers->tyep == _tyep)
        {
            if (soldiers->num > 1)
            {
                soldiers->num -= 1;
                allProductionTime -= soldiers->MAXTime;
                
                
                if (pCentralScene->m_pCentralInfoUILayer != NULL) {
                    if (pCentralScene->m_pCentralInfoUILayer->m_type == ARMY_BARRACK)
                    {
                        if (pCentralScene->m_pCentralInfoUILayer->arrIcon != NULL)
                        {
                            CCSprite* icon = (CCSprite*)pCentralScene->m_pCentralInfoUILayer->arrIcon->objectAtIndex(_tyep-1);
                            
                            CCLabelTTF *timeLabel = (CCLabelTTF*)icon->getChildByTag(1);
                            
                            timeLabel->setString(CommonResource::getStringFromInt(soldiers->num).c_str());
                        }
                        if (pCentralScene->m_pCentralInfoUILayer->arrAIcon != NULL)
                        {
                            StateSprite* icon = pCentralScene->m_pCentralInfoUILayer->getState(_tyep);
                            if (icon != NULL)
                            {
                                CCLabelTTF *timeLabel = (CCLabelTTF*)icon->getChildByTag(1);
                                timeLabel->setString(CommonResource::getStringFromInt(soldiers->num).c_str());
                            }
                            
                        }
                        pCentralScene->m_pCentralInfoUILayer->updatePeopleNum();
                    }
                    
                }
            }
            else
            {   
                if (pCentralScene->m_pCentralInfoUILayer != NULL) 
                {
                    if (pCentralScene->m_pCentralInfoUILayer->m_type == ARMY_BARRACK) 
                    {
                        
                        if (pCentralScene->m_pCentralInfoUILayer->arrIcon != NULL)
                        {
                            CCSprite* icon = (CCSprite*)pCentralScene->m_pCentralInfoUILayer->arrIcon->objectAtIndex(soldiers->tyep-1);
                            
                            CCLabelTTF *timeLabel = (CCLabelTTF*)icon->getChildByTag(1);
                            timeLabel->setString("");
                        }
                        
                        
                        if (pCentralScene->m_pCentralInfoUILayer->arrAIcon != NULL) 
                        {
                            StateSprite* icon = pCentralScene->m_pCentralInfoUILayer->getState(soldiers->tyep);
                            if (icon != NULL)
                            {
                                pCentralScene->m_pCentralInfoUILayer->m_SpriteA =NULL;
                                icon->removeFromParentAndCleanup(false);
                                pCentralScene->m_pCentralInfoUILayer->arrAIcon->removeObject(icon);
                                pCentralScene->m_pCentralInfoUILayer->sortingStateSprite();
                                
                            }
                            
                        }
                        pCentralScene->m_pCentralInfoUILayer->updatePeopleNum();
                    }
                    
                }
                
                delete m_peopleSoldiers->at(i);
                m_peopleSoldiers->erase(m_peopleSoldiers->begin()+i);
                
                if (pCentralScene->m_pCentralInfoUILayer != NULL) 
                {
                    pCentralScene->m_pCentralInfoUILayer->updateSpeedUp();

                }
                                
                
            }
            
            
            bool isHave = false;
            int soldiers_num = (int)m_jianPeopleSoldiers->size();
            for (int j = 0; j <soldiers_num; j++)
            {
                PeopleSoldiers* soldiers = m_jianPeopleSoldiers->at(j);
                
                if (soldiers->tyep == _tyep)
                {
                    soldiers->num += 1;
                    isHave = true;
                }
            }
            
            if (!isHave)
            {
                
                PeopleSoldiers *soldiers = new PeopleSoldiers();
                memset( soldiers,0,sizeof(PeopleSoldiers) );
                soldiers->tyep = _tyep;
                soldiers->num = 1;
                soldiers->uuid = this->getuuID();
                soldiers->S_time = Until::millisecondNow_m();
                m_jianPeopleSoldiers->push_back(soldiers);
                
            }
        }
    }

}
void BuildingBase::addSoldiers(int _tyep)
{
    
    if (m_peopleSoldiers == NULL)
    {
        m_peopleSoldiers  = new vector<PeopleSoldiers*>;
    }
    
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    CentralData::BuildableSoldiers* temp = pCentralScene->m_pCentralData->getBuildableSoldiers(_tyep);
    
    const BasePeopleData* basePeopleData;
    basePeopleData = GameData::GetDataFromBasePeopleData(temp->type * PEOPLE_TYPE_ *100 + temp->leve);
    pCentralScene->m_pCentralData->m_Central_UserData->allPeopleNum += basePeopleData->HousingSpace;
    duileiNum += basePeopleData->HousingSpace;
    //减少药水
    if (pCentralScene->m_pCentralUILayer->updatePotions(-basePeopleData->TrainingCost)) 
    {
        
        int s_num = 0;
        
        int indexNum = 0;
        bool isHave = false;
        int num = (int)m_peopleSoldiers->size();
        for (int i = 0; i <num; i++)
        {
            PeopleSoldiers* soldiers = m_peopleSoldiers->at(i);
            
            if (soldiers->tyep == _tyep)
            {
                soldiers->num += 1;
                soldiers->uploadNum +=1;
                allProductionTime += soldiers->MAXTime;
                isHave = true;
                
                s_num = soldiers->num;
                
            }
            if (indexNum<=soldiers->index)
            {
                indexNum = soldiers->index +1;
            }
            
        }
        
        
        if (!isHave)
        {
            
            PeopleSoldiers *soldiers = new PeopleSoldiers();
            memset( soldiers,0,sizeof(PeopleSoldiers) );
            soldiers->tyep = _tyep;
            soldiers->num = 1;
            soldiers->MAXTime = basePeopleData->TrainingTime;
            soldiers->time = 0;
            soldiers->uploadNum = 1;
            soldiers->uuid = this->getuuID();
            soldiers->index = indexNum;
            soldiers->S_time = Until::millisecondNow_m();
            s_num = soldiers->num;
            m_peopleSoldiers->push_back(soldiers);
            
            allProductionTime += soldiers->MAXTime;
            
        }
        
        
        if (pCentralScene->m_pCentralInfoUILayer != NULL) {
            if (pCentralScene->m_pCentralInfoUILayer->m_type == ARMY_BARRACK)
            {
                if (pCentralScene->m_pCentralInfoUILayer->arrIcon != NULL)
                {
                    CCSprite* icon = (CCSprite*)pCentralScene->m_pCentralInfoUILayer->arrIcon->objectAtIndex(_tyep-1);
                    
                    CCLabelTTF *timeLabel = (CCLabelTTF*)icon->getChildByTag(1);
                    
                    timeLabel->setString(CommonResource::getStringFromInt(s_num).c_str());
                }
                if (pCentralScene->m_pCentralInfoUILayer->arrAIcon != NULL)
                {
                    StateSprite* icon = pCentralScene->m_pCentralInfoUILayer->getState(_tyep);
                    if (icon != NULL)
                    {
                        CCLabelTTF *timeLabel = (CCLabelTTF*)icon->getChildByTag(1);
                        timeLabel->setString(CommonResource::getStringFromInt(s_num).c_str());
                    }
                    else
                    {
                        pCentralScene->m_pCentralInfoUILayer->addStateSprite(_tyep);
                        pCentralScene->m_pCentralInfoUILayer->sortingStateSprite();
                    }
                    
                    
                    
                }
                pCentralScene->m_pCentralInfoUILayer->updatePeopleNum();
            }
            
        }
    }
    //药水不足
    else
    {
        
    }
    
}
void BuildingBase::addResources()
{
    if (isHarvest)
    {
        isHarvest = false;
        if (tipNode)
        {
            sprite_->removeChild(tipNode, false);
            tipNode = NULL;
        }
        
        
        //收获资源
        if (m_uTypeID == RESOURCE_ELIXIRPUMP)
        {
            
            if (resourcesPotionsNum > 0)
            {
                CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
                
                //加水
                if (pCentralScene->m_pCentralUILayer->updatePotions(resourcesPotionsNum))
                {
                    
                    //收获药水
                    const EffectData* effectData = GameData::GetDataFromBaseEffectData("Collect Elixir");
                    LParticleUnit* pu = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->AddParticleEmitter(effectData->ParticleEmitter, ccp(sprite_->getContentSize().width/2,sprite_->getContentSize().height-30), 0.3f,sprite_);
                    pu->setEmitterTotalParticles(6);
                    if (!effectData->Sound.empty()) {
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(effectData->Sound.c_str());
                    }
                    //记录加水
                    pCentralScene->m_pCentralLayer->buildingAccount(this,OperateType_HarvestPotions);
                    
                    buildEventTime = Until::millisecondNow_m();
                    buildxiaoguoEventTime = buildEventTime;
                    resourcesPotionsNum = 0;
                }
                else
                    //药水已满
                {
                    
                    buildxiaoguoEventTime = Until::millisecondNow_m();
                }
                
            }
            
            
        }
        else if (m_uTypeID == RESOURCE_GOLDMINE)
        {             
            //收获金钱
            if (resourcesGoldNum>0)
            {
                CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
                
                
                if (pCentralScene->m_pCentralUILayer->updateGold(resourcesGoldNum))
                {
                    const EffectData* effectData = GameData::GetDataFromBaseEffectData("Collect Gold");
                    SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->AddParticleEmitter(effectData->ParticleEmitter, ccp(sprite_->getContentSize().width/2,sprite_->getContentSize().height-30), 0.3f,sprite_);
                    if (!effectData->Sound.empty()) {
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(effectData->Sound.c_str());
                    }
                    
                    pCentralScene->m_pCentralLayer->buildingAccount(this,OperateType_HarvestGold);
                    
                    buildEventTime = Until::millisecondNow_m();
                    buildxiaoguoEventTime = Until::millisecondNow_m();
                    resourcesGoldNum = 0;
                }
                else
                {
                    buildxiaoguoEventTime = Until::millisecondNow_m();
                    
                }

                
                
            }
        }
    }
}
void BuildingBase::setData()
{
    const BaseBuildingLevelData* buildingBaseLevelData;
    buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( m_u32ID);
    
    resourcesMaxNum = buildingBaseLevelData->MaxStoredGold;
    if (resourcesMaxNum < buildingBaseLevelData->MaxStoredElixir)
    {
        resourcesMaxNum = buildingBaseLevelData->MaxStoredElixir;
    }
    
    if (buildingBaseLevelData->building_TypeID == RESOURCE_ELIXIRPUMP || buildingBaseLevelData->building_TypeID == RESOURCE_GOLDMINE)
    {
        resourcesMaxNum = buildingBaseLevelData->ResourceMax;
        resourcesCDNum = buildingBaseLevelData->ResourcePerHour;
    }
    if (buildingBaseLevelData->building_TypeID == ARMY_BARRACK)
    {
        duileiMAXNum = buildingBaseLevelData->UnitProduction;
    }
}

void BuildingBase::unit_doupgrade(int _m_u32ID)
{
    m_u32ID = _m_u32ID;
    
    const UnitClass* uclass = GameData::GetUnitClassData(m_u32ID);
    this->setUnitClass(uclass);
    
    CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;

    
    const BaseBuildingLevelData* buildingBaseLevelData;
    buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( m_u32ID);
    if (sprite_ != NULL)
    {
        sprite_->removeChildByTag(10, false);
        
        //动画表现
        sprite_->removeChild(tipNode, false);
        tipNode = NULL;
        
        sprite_->removeFromParentAndCleanup(false);
        sprite_ = NULL;
    }
    //创建动画
    sprite_ = CCSprite::create(GAME_FILE_TRANSFORM(buildingBaseLevelData->ExportName.c_str(),".png").c_str());
    sprite_->setPosition(ccp(0,0));  // 崩溃
    sprite_->setAnchorPoint(ccp(0.5,0.5));
    sprite_->setScale(UNIT_Texture_scale_2048x1536);
    data->m_tmxMap->addChild(this->sprite_);
    
    char strName[64];
    sprintf(strName,"%s \nlevel%d",buildingBaseLevelData->Name.c_str(),buildingBaseLevelData->build_level);
    
    drawNameLabel(sprite_, strName);
    
    //刷新数据
    setData();
}


const CCSize& BuildingBase::getContentSize( void )
{
	return sprite_->getContentSize();
}

int BuildingBase::GetLine( void )
{
	return m_stBuildSubstrate.m_Line;
}

int BuildingBase::GetRow( void )
{
	return m_stBuildSubstrate.m_Row;
}



int BuildingBase::GetNowHousingSpace()
{
	int result = 0;

	army_loop_t::iterator iCur = m_army.begin();
	army_loop_t::iterator iEnd = m_army.end();
	for ( ; iCur!=iEnd; ++iCur)
	{
		Unit* pRole = *iCur;
		const BasePeopleData* pdata = GameData::GetDataFromBasePeopleData(pRole->getID());
		result += pdata->HousingSpace;
	}

	return result;
}
