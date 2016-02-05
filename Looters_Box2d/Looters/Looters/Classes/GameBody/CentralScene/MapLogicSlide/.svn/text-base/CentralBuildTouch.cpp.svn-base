/***************************************************************
 author:     wangning
 write time: 2012.10.22
 function:   游戏主场景建筑操控操作
 ***************************************************************/
#include <iostream>
#include "CentralLayer.h"
#include "GameControl.h"
#include "cocos2d.h"
#include "Until.h"
#include "NetMessageManager.h"
#include "FindRoad.h"

static long startTime = 0;
static long endTime = 0;

void CentralLayer::buildTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it;
    CCTouch* touch = NULL;
    for( it = pTouches->begin(); it != pTouches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        if(!touch)
            break;
        
        int iViewID = touch->getID();
        if( iViewID == 0 ){
            break;
        }
    }

    CCPoint touchLocation = touch->getLocation();
    

    if (m_building != NULL) // 拖动过程中更换触摸到格子单元格
    {
        CCPoint mapIndex = this->getMapIndexByTouchPoint(touchLocation);
        startMovePos = ccpSub(buildNewMapIndex,mapIndex);
    }
    
    m_enHandleState = STATE_CLICK;
}



void CentralLayer::buildTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it;
    CCTouch* touch = NULL;
    for( it = pTouches->begin(); it != pTouches->end(); it++) 
    {
        touch = (CCTouch*)(*it);
        if(!touch)
            break;
        
        int iViewID = touch->getID();
        if( iViewID == 0 ){
            break;
        }
    }
    
    if (touch != NULL) {
        CCPoint touchLocation = touch->getLocation();
        
        //是否要移动地图
        if (m_BuildOperatingMode == MODE_DRAG && m_building != NULL && m_enHandleState == STATE_CLICK)
        {
            if (!isClickBuilding(touchLocation,m_building,buildNewMapIndex))
            {
                m_enHandleState = STATE_DRAG;  
            }
            
        }
        
        //是否要移动建筑
        if (m_enHandleState == STATE_CLICK)
        {
            m_enHandleState = STATE_MOVE;
        }
        
        
        if (m_BuildOperatingMode == MODE_DRAG && m_building != NULL && m_enHandleState == STATE_MOVE) 
        {
            m_building->z_state_ = UNIT_Z_MAX_STATE;
            if (startTime == 0) {
                startTime = Until::millisecondNow();
            }
            endTime = Until::millisecondNow();
//            long durTime = endTime-startTime;
//            CCLog("触摸结束时间%ld",durTime);
            startTime = Until::millisecondNow();
            
            if(startMovePos.x == -1){
                CCPoint mapIndex = this->getMapIndexByTouchPoint(touchLocation);
                startMovePos = ccpSub(m_building->getMapIndex(),mapIndex);
            }
            
            CCPoint newIndex = this->getMapIndexByTouchPoint(touchLocation);
            CCPoint index = ccpAdd(newIndex,startMovePos);
			iBox2 const mapBound(to_iVec2(GamePlatform::S_BuildingLeftGrid, GamePlatform::S_BuildingLeftGrid), to_iVec2(MAPGRIDWIDTH-1-GamePlatform::S_BuildingLeftGrid, MAPGRIDHEIGHT-1-GamePlatform::S_BuildingLeftGrid));
			iVec2 const leftTop = iVec2(index.x-(m_building->m_stBuildSubstrate.m_Line-1), index.y-(m_building->m_stBuildSubstrate.m_Line-1));
			
            if ( mapBound.IsContains(leftTop) && mapBound.IsContains(to_iVec2(index)) ) 
			{                
                buildNewMapIndex = index;
                CCPoint xy = this->positionForIsoAt(buildNewMapIndex);
                
                xy.x = xy.x + BUILDINGBASEGRID_WIDTH/2;
                m_building->setPosition(xy);
                if (this->isCanPutDownBuild(buildNewMapIndex,m_building->GetLine(),m_building->getuuID(),m_building))
                {
                    m_building->m_pSubstrateBottom->setColor(m_building->ccl);
                }
                else
                {
                    m_building->m_pSubstrateBottom->setColor(ccColor3B(ccRED));
                }
            }
        }
    }
}

void CentralLayer::buildTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it;
    CCTouch* touch = NULL;
    for( it = pTouches->begin(); it != pTouches->end(); it++) 
    {
        touch = (CCTouch*)(*it);
        if(!touch)
            break;
        
        int iViewID = touch->getID();
        if( iViewID == 0 ){
            break;
        }
    }
    
    if (touch != NULL)
    {
        CCPoint touchLocation = touch->getLocation();
        
        if(m_BuyBuilding !=NULL) return;
        
        CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
        
        //已有选中的建筑
        if (m_enHandleState == STATE_CLICK)
        {
            if(m_building != NULL){
                //可以放下
                fangxiajianzhu();
            }
            else{
                BuildingBase* pBuilding = this->SelectBuildingFromSubstrate(touchLocation);
                
                if (pBuilding == NULL) {
                    m_building = NULL;
                    startMovePos = ccp(0,0);
                }
                else {
                    
                    if (pBuilding->isHarvest) // 收集资源
                    {
                        pBuilding->addResources();
                    }
                    else  // 第一次选中建筑
                    {
                        m_building = pBuilding;
                        buildNewMapIndex = m_building->getMapIndex();
                        //显示箭头
                        m_building->IsShowSubstrateArrow(true);
                        m_building->IsShowBuildName(true);
                        
                        CCPoint mapIndex = this->getMapIndexByTouchPoint(touchLocation);
                        startMovePos = ccpSub(pBuilding->getMapIndex(),mapIndex);
                        
                        m_BuildOperatingMode = MODE_DRAG;
                    
                        pCentralScene->m_pCentralUILayer->InfoBtnAppear(m_building->upgrade_state_,m_building->getTypeID());
                        
                        //升级所需的资源数
                        pCentralScene->m_pCentralUILayer->upResourcesNumLabel();
                        
                        m_building->biaoTime = 0;
                        m_building->isBiaoxian = true;
                        
                        
                    }
                }
            }
        }
        else if (m_enHandleState == STATE_MOVE)
        {
            if (m_building != NULL) {
                //可以放下
                if (this->isCanPutDownBuild(buildNewMapIndex,m_building->GetLine(),m_building->getuuID(),m_building))
                {
                    m_building->z_state_ = UNIT_Z_NORMAL_STATE;
                }
                else
                {
                    m_building->z_state_ = UNIT_Z_MAX_STATE;
                }
            }
        }
        
        
        m_enHandleState = STATE_NULL;
    }
}
void CentralLayer::fangxiajianzhu()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    if (this->isCanPutDownBuild(buildNewMapIndex,m_building->GetLine(),m_building->getuuID(),m_building))
    {
        m_building->biaoTime = 0;
        m_building->isBiaoxian = false;
        if (sprTeX != NULL)
        {
            sprTeX->removeFromParentAndCleanup(false);
            sprTeX = NULL;
        }
        CCPoint fistMapIndex = m_building->getMapIndex();
        
        this->RemoveGridBuildInfo(m_building->getMapIndex(),m_building->GetLine(),m_building->getuuID(),m_building);
        m_building->setMapIndex(buildNewMapIndex);
        this->MarkGridBuildInfo(m_building->getMapIndex(), m_building->GetLine(), m_building->getuuID(), m_building);
        
        //不显示箭头
        m_building->IsShowSubstrateArrow(false);
        //加入流水帐
        buildingAccount(m_building,OperateType_MobileBuilding);
        
        if (m_building->getTypeID() == BUILDINGTYPE_WALL) {
            ReplaceWallToBase01(m_building);
            ResetPlaceAll(m_building->getMapIndex());
            
            ResetPlaceAll(fistMapIndex);
        }
        
        
        if (m_building->getTypeID() == ARMY_TROOPHOUSING && !float_vec_equal(fistMapIndex, buildNewMapIndex))
        {
            for (int i=0; i<m_building->m_army.size(); i++)
            {
                iVec2 index = quad_title_random_index(m_building->m_stBuildSubstrate.m_Line, m_building->radius);
                index += quad_title_left_top_index(m_building->GetCenterPos(), m_building->m_stBuildSubstrate.m_Line);
                b2Vec2 pos = quad_title_covert_t::index_to_pos(index);
                Unit* role = m_building->m_army[i];
                
                {
                    //								iVec2 srcIndex = half_title_covert_t::pos_to_index(to_b2Vec2(role->getPosition()) );
                    //								iVec2 dstIndex = half_title_covert_t::pos_to_index(pos);
                    //
                    //								CCLog("src->dst, (%d, %d), (%d, %d)", srcIndex.x, srcIndex.y, dstIndex.x, dstIndex.y);
                    
                }
                
                
                bool isOk = FindRoad::sharedFindRoad()->SearchInHome(role, half_title_covert_t::pos_to_index(pos));
                if (isOk)
                {
                    role->m_ai_path.clear();
                    FindRoad::sharedFindRoad()->GetPath(role->m_ai_path);
                    role->m_ai_path.front() = pos;
                    role->cmd_moveto(role->m_ai_path.back().x, role->m_ai_path.back().y);
                }
            }
        }
        
        // 建筑中的建筑
        if (UNIT_UPGRADE_BUILDIN==m_building->upgrade_state_
            || UNIT_UPGRADE_IN==m_building->upgrade_state_
            || UNIT_UPGRADE_REMOVEIN==m_building->upgrade_state_)
        {
            CCAssert( NULL!=m_building->m_pWorker, "" );
            FollowBuild(m_building->m_pWorker, m_building);
            
        }
    }
    else
    {
        m_building->biaoTime = 0;
        m_building->isBiaoxian = false;
        if (sprTeX != NULL)
        {
            sprTeX->removeFromParentAndCleanup(false);
            sprTeX = NULL;
        }
        
        //复原位置
        CCPoint xy = this->positionForIsoAt(m_building->getMapIndex());
        xy.x = xy.x + BUILDINGBASEGRID_WIDTH/2;
        xy.y = xy.y;
        m_building->setPosition(xy);
        //复原z轴
        //m_building ->setUnitZOrder(m_building->getUnitZorser());
        //不显示箭头
        m_building->IsShowSubstrateArrow(false);
        
        m_building->m_pSubstrateBottom->setColor(m_building->ccl);
        
    }
    
    m_building->IsShowBuildName(false);
    
    pCentralScene->m_pCentralUILayer->InfoBtnDisappear(m_building->upgrade_state_,m_building->getTypeID());
    
    m_BuildOperatingMode = MODE_NULL;
    m_building->z_state_ = UNIT_Z_NORMAL_STATE;
    m_building = NULL;
}
//按下建筑取消按钮
void CentralLayer::menuCallbackCancel(CCObject* sender)
{
    CCPoint firstPoint = m_building->getMapIndex();

	RemoveGridBuildInfo(m_building->getMapIndex(),m_building->GetLine(),m_building->getuuID(),m_building);

    m_building->remove();
    if (m_building->getTypeID() == BUILDINGTYPE_WALL) {
        ResetPlaceAll(firstPoint);
        m_PlaceState = PlaceState_First;
    }
    m_BuildOperatingMode = MODE_NULL;
    m_BuyBuilding = NULL;
    m_building = NULL;
}

//按下建造ok按钮
void CentralLayer::menuCallbackOK(CCObject* sender)
{
    bool isResource = true;
    const BaseBuildingLevelData* buildingBaseLevelData;
    buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( m_building->getID());
    if (buildingBaseLevelData!=NULL)
    {
        CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
        
        
        if (this->isCanPutDownBuild(buildNewMapIndex,m_building->GetLine(),m_building->getuuID(),m_building))
        {
            BuildingBase* build = NoBusy();
            if (m_building->getTypeID() == BUILDINGTYPE_WORKER)
            {
                if("Diamonds" == string(buildingBaseLevelData->BuildResource))
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
                
                // 资源充足
                if (isResource)
                {
                    m_building->upgrade_state_ = UNIT_UPGRADE_NONE;
                    
                    this->RemoveGridBuildInfo(m_building->getMapIndex(),m_building->GetLine(),m_building->getuuID(),m_building);
                    m_building->setMapIndex(buildNewMapIndex);
                    this->MarkGridBuildInfo(m_building->getMapIndex(), m_building->GetLine(), m_building->getuuID(), m_building);
                    
                    m_building->removeSymbol();
                    
                    buildingAccount(m_building,OperateType_Build);
                    m_building->z_state_ = UNIT_Z_NORMAL_STATE;
                    m_BuyBuilding = NULL;
                    pCentralScene->m_pCentralUILayer->InfoBtnAppear(m_building->upgrade_state_,m_building->getTypeID());
                    pCentralScene->m_pCentralUILayer->updatePeasant();

                }
                
            }
            else if (build != NULL) 
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
					// 墙立即建成
                    if (m_building->getTypeID() == BUILDINGTYPE_WALL)
					{
                        int unitID = m_building->getID();
                        
                        m_building->upgrade_state_ = UNIT_UPGRADE_NONE;
                        
                        this->RemoveGridBuildInfo(m_building->getMapIndex(),m_building->GetLine(),m_building->getuuID(),m_building);
                        m_building->setMapIndex(buildNewMapIndex);
                        this->MarkGridBuildInfo(m_building->getMapIndex(), m_building->GetLine(), m_building->getuuID(), m_building);
                        
                        PlaceNextIndex = m_building->getMapIndex();
                        ResetPlaceAll(PlaceNextIndex);
                        
                        
                        //不显示箭头
                        m_building->IsShowSubstrateArrow(false);
                        m_building->removeSymbol();
                        
                        buildingAccount(m_building,OperateType_Build);
                        m_building->z_state_ = UNIT_Z_NORMAL_STATE;
                        m_BuildOperatingMode = MODE_NULL;
                        m_BuyBuilding = NULL;
                        m_building = NULL;
                        
                        buyBuilding(unitID);
                    }
                    else
                    {
                        build->isBusy = true;
                        build->busyUUID = m_building->getuuID();
                        
                        m_building->upgrade_state_ = UNIT_UPGRADE_BUILD;
                        
                        this->RemoveGridBuildInfo(m_building->getMapIndex(),m_building->GetLine(),m_building->getuuID(),m_building);
                        m_building->setMapIndex(buildNewMapIndex);
                        this->MarkGridBuildInfo(m_building->getMapIndex(), m_building->GetLine(), m_building->getuuID(), m_building);
						
						SendAWorker(build, m_building);
                        
                        //不显示箭头
                        m_building->removeSymbol();
                        
                        buildingAccount(m_building,OperateType_Build);
                        m_building->z_state_ = UNIT_Z_NORMAL_STATE;
                        m_BuyBuilding = NULL;
                        pCentralScene->m_pCentralUILayer->InfoBtnAppear(m_building->upgrade_state_,m_building->getTypeID());
                        

                    }
                }
                
            }
            else
            {
                //队列不足
                pCentralScene->m_pCentralUILayer->addDialogLayer(true,0,4);
            }
            
            
        }
    }
}