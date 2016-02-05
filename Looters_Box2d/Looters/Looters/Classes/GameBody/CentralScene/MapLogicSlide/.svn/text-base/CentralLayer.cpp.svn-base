#include <iostream>
#include "CentralLayer.h"
#include "GameControl.h"
#include "NetMessageManager.h"
#include "FindRoad.h"
USING_NS_CC;

CentralLayer::CentralLayer()
{
}

CentralLayer::~CentralLayer()
{
    unit_list_->release();
    particle_list_->release();
    
    if (((int)m_mapMapGridLogicInfo->size())>0)
	{
		while( m_mapMapGridLogicInfo->size() )
		{
			map<unsigned int,MapGridLogicInfo*>::iterator iter = m_mapMapGridLogicInfo->begin();
			delete iter->second;
			m_mapMapGridLogicInfo->erase( iter );
		}
        m_mapMapGridLogicInfo->clear();
	}

    // viewself
    for( int i = 0; i < (int)m_Account->size(); i++ )
	{
        delete m_Account->at(i);
	}
	m_Account->clear();
    delete m_Account;
    
    
    for( int i = 0; i < (int)m_Accelerated->size(); i++ )
	{
		delete m_Accelerated->at(i);
	}
	m_Accelerated->clear();
    delete m_Accelerated;
}

void CentralLayer::Update( float dt )
{
    //资源加载
	if( m_enLoadProcess != finish )
	{
		UpdateLoadResAndData(dt);
	}
    
    //In Game update
    if( m_enLoadProcess == finish)
	{
        //地图上游戏对象逻辑更新
        if(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enCentralViewMode == CENTRALVIEW_SELF){
            UpdateBuildintStatus(dt);
        }else if(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enCentralViewMode == CENTRALVIEW_BATTLE){
            battle_update(dt);
        }
        step(dt);
        
        // 支付请求
        if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralShopUILayer != NULL)
        {
            if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralShopUILayer->DetectTyep == ShopDetectProcess_Bank)
            {
                if( !NetMessageManager::GetMessageManager()->m_bBankSocketStoping &&
                   !NetMessageManager::GetMessageManager()->m_bBankSocketLinding &&
                   !NetMessageManager::GetMessageManager()->m_bBankSocketLinked )
                {
                    NetMessageManager::StateLinkBankSocket();
                    if( m_iLinkBankCountCurrent == m_iLinkBankCountMax )
                    {
                        //连接失败
                        m_iLinkBankCountCurrent = 0;
                        SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralShopUILayer->DetectTyep =ShopDetectProcess_null;
                    }
                    m_iLinkBankCountCurrent++;
                }
                if( !NetMessageManager::GetMessageManager()->m_bBankSocketStoping &&
                   NetMessageManager::GetMessageManager()->m_bBankSocketLinked )
                {
                    //连接成功
                    m_iLinkBankCountCurrent = 0;
                    SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralShopUILayer->DetectTyep = ShopDetectProcess_null;
                    
                    NetMessageManager::GetMessageManager()->m_pMessageRequest->SendRechargeRequest("");
                }
            }
        }

        //流水账相关更新
        if (isAccount)
        {
            accountIntervalTime += dt;
            
            if (accountIntervalTime > MAX_accountIntervalTime)
            {
                accountIntervalTime = 0;
                isAccount = false;
                uploadAccount();
            }
        }
        
        // 战斗场景UI界面更新
        if(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enCentralViewMode == CENTRALVIEW_BATTLE)
		{
			if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enPVPMode == BATTLE_MODE_PVP_REPLAY) {
                SceneManage::GetSceneManageHendle()->m_pCentralScene->m_CentralBattleReplayUILayer->update(dt);
				return;
			}
            SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralPVPMapUILayer->update(dt);
        }
        
        // 建筑info界面的更新
        if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralUILayer != NULL)
        {
            SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralUILayer->updata(dt);
        }
        if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralInfo2UILayer != NULL)
        {
            SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralInfo2UILayer->updata(dt);
        }
        if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralInfoUILayer != NULL)
        {
            SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralInfoUILayer->updata(dt);
        }
		
		// 上传战斗过程
		{			
			CentralData * cData = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
			if (!cData->m_battleReplayFiles.empty())
			{

				if( !NetMessageManager::GetMessageManager()->m_bFileSocketStoping &&
				   !NetMessageManager::GetMessageManager()->m_bFileSocketLinding &&
				   !NetMessageManager::GetMessageManager()->m_bFileSocketLinked )
				{
					NetMessageManager::StateLinkFileSocket();
					if( m_iLinkFileCountCurrent == m_iLinkFileCountMax )
					{
						//连接失败
						m_iLinkFileCountCurrent = 0;
					}
					m_iLinkFileCountCurrent++;
				}
				
				if( !NetMessageManager::GetMessageManager()->m_bFileSocketStoping &&
				   NetMessageManager::GetMessageManager()->m_bFileSocketLinked )
				{
					
					//连接成功
					m_iLinkFileCountCurrent = 0;
                    string dc = CCFileUtils::sharedFileUtils()->getWriteablePath();
					std::string const& fileName = cData->m_battleReplayFiles.front();
                    dc.append(fileName);
					FILE *fp = fopen(dc.c_str(), "rb");
					CCAssert(NULL!=fp, __FUNCTION__);

                    
                    size_t findex = fileName.find('_');
                    string defence = fileName.substr(0, findex);
                    string attact = fileName.substr(findex+1, fileName.rfind('_')-findex-1);
                    
                    
                    char buf[1024] = {'\0'};
					fseek(fp, 0, SEEK_END);
					long length = ftell( fp );
					fseek(fp, 0, SEEK_SET);
                    
                    int curIndex = 0;
                    int maxSize = 0;
                    if (length%1024 != 0) {
                        maxSize = length/1024 + 1;
                    }else{
                        maxSize = length/1024;
                    }
                    
                    for (long len=0; len<length; len+=1024)
                    {
                        size_t ret = fread(&buf[0], 1, 1024, fp);
                        NetMessageManager::GetMessageManager()->m_pMessageRequest->SendUploadBattleFlowRequest( defence, attact, ret, maxSize, curIndex, &buf[0]);
                        curIndex++;
                    }

					fclose(fp);

					cData->m_battleReplayFiles.erase(cData->m_battleReplayFiles.begin());
				}
			}
		}
        if (m_building !=NULL)
        {
            if (m_building->isBiaoxian)
            {
                if (m_building->biaoTime<0.1f)
                {
                    m_building->sprite_->setScale(1.1f);
                }
                else if (m_building->biaoTime<0.2f)
                {
                    m_building->sprite_->setScale(1.0f);
                }
                else if(m_building->biaoTime<0.3f)
                {
                    sprTeX = CCSprite::createWithTexture(m_building->sprite_->getTexture());
                    sprTeX->setColor(ccBLACK);
                    sprTeX->setAnchorPoint(ccp(0, 0));
                    sprTeX->setPosition(ccp(0, 0));
                    sprTeX->setOpacity(0);
                    m_building->sprite_->addChild(sprTeX);
                    m_building->biaoTime=1.0f;
                }
                else
                {
                    int _d01 = m_building->biaoTime;
                    int _timePent = m_building->biaoTime *100;
                    
                    sprTeX->setOpacity(_timePent-_d01*100);
                    
                    if (_timePent-_d01*100 >90)
                    {
                        m_building->isBiaoxian = false;
                        m_building->biaoTime = _d01;
                    }
                }
                
                m_building->biaoTime+=dt;
            }
            else
            {
                if (m_building->biaoTime >0.99f)
                {
                    int _d01 = m_building->biaoTime;
                    int _timePent = m_building->biaoTime *100;
                    
                    sprTeX->setOpacity(100-(_timePent-_d01*100));
                    
                    if (_timePent-_d01*100 >90)
                    {
                        m_building->isBiaoxian = true;
                        m_building->biaoTime = _d01;
                    }
                    m_building->biaoTime+=dt;
                }
            }
        }
	}
}

void CentralLayer::UpdateBuildintStatus( float dt )
{
    //建筑循环
    int listNum = unit_list_->count();
    for (int i=0; i<listNum;i++ )
    {
        Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
        //如果是建筑
        if (unit->is_build_type())
        {
            //强转成建筑类
            BuildingBase* build = (BuildingBase*)unit;
            build->UpdataBuilding(dt);
        }
    }
    
    
    if (isUPSoldiers) 
    {
        uploadSoldiersTime+=dt;
        if (uploadSoldiersTime > 4)
        {
            isUPSoldiers = false;
            uploadRecruiting();
        }
    }
    if (isJianSoldiers)
    {
        jianloadSoldiersTime+=dt;
        if (jianloadSoldiersTime > 4)
        {
            isJianSoldiers = false;
            jianloadRecruiting();
        }
    }
    
}

void CentralLayer::SetFocus( void )
{
    
}

void CentralLayer::SetMapLayerPos( CCPoint point )
{
    
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCSize mapSize = CCSizeMake(MAPGLWIDTH,MAPGLHEIGHT);
    CCPoint currentPos = this->getPosition();
    
    
    int setpoX = mapSize.width/2 - point.x - currentPos.x - screenSize.width/2;
    int setpoY = mapSize.height/2 - point.y - currentPos.y - screenSize.height/2;
    
    CCPoint diff = ccp(setpoX,setpoY);
    
    float tempWidth = mapSize.width*this->getScale();
    float tempWidth_Half = tempWidth/2;
    float tempHeight = mapSize.height*this->getScale();
    float tempHeight_Half =tempHeight/2;
    
    
    float result1= tempWidth_Half-screenSize.width/2;
    float result2 = tempHeight_Half-screenSize.height/2;
    
    CCPoint maxSelfPos = ccp(result1,result2);
    
    
    CCPoint minSelfPos;
    
    minSelfPos = ccp(result1-(tempWidth-480),result2-(tempHeight-320));
    
    if (diff.x >=0) {
        diff.x = (this->getPositionX()+diff.x)<=maxSelfPos.x?diff.x:(maxSelfPos.x-this->getPositionX());
    }
    else {
        diff.x = (this->getPositionX()+diff.x)>=minSelfPos.x?diff.x:(minSelfPos.x-this->getPositionX());
    }
    
    if (diff.y>=0) {
        diff.y = (this->getPositionY()+diff.y)<=maxSelfPos.y?diff.y:(maxSelfPos.y-this->getPositionY());
    }
    else {
        diff.y = (this->getPositionY()+diff.y)>=minSelfPos.y?diff.y:(minSelfPos.y-this->getPositionY());
    }
    
    this->setPosition(ccpAdd(currentPos, diff));
}

void CentralLayer::SetMapLayerScale( float fScale )
{

}

iVec2 CentralLayer::FindEmptyTitle( int line )
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	iVec2 centerIndex = to_iVec2( getMapIndexByTouchPoint(ccp(size.width/2.f, size.height/2.f)) );

	iBox2 const bound(to_iVec2(GamePlatform::S_BuildingLeftGrid, GamePlatform::S_BuildingLeftGrid), to_iVec2(MAPGRIDWIDTH-1-GamePlatform::S_BuildingLeftGrid, MAPGRIDHEIGHT-1-GamePlatform::S_BuildingLeftGrid));
	iVec2 rightBottomOffset(line-1, line-1);
	iVec2 result(-1, -1);
		
	if (bound.IsContains(centerIndex) && bound.IsContains(centerIndex+rightBottomOffset)&& HasEmpty(centerIndex, line))
	{	
		result = centerIndex;
		result += rightBottomOffset;
		return result;
	}
	
	for (int i=1; i<MAPGRIDWIDTH; ++i)
	{

		iVec2 leftTop(centerIndex.x-i, centerIndex.y-i);
		iVec2 rightBottom(centerIndex.x+i, centerIndex.y+i);

		iVec2 cur;

//		bool isAllOut =true;
		// 顶一行
		for ( int x=leftTop.x, xEnd=rightBottom.x; x<xEnd; ++x )			
		{				
			cur.x = x;
			cur.y = leftTop.y;

			bool isIn = bound.IsContains(cur)&& bound.IsContains(cur+rightBottomOffset);
//			isAllOut &= !isIn;

			if (isIn && HasEmpty(cur, line))
			{
				result = cur;
				result += rightBottomOffset;				
				return result;
			}

		}

		// 底一行
		for (int x=leftTop.x, xEnd=rightBottom.x; x<xEnd; ++x)
		{
			cur.x = x;
			cur.y = rightBottom.y;

			bool isIn = bound.IsContains(cur)&& bound.IsContains(cur+rightBottomOffset);
//			isAllOut &= !isIn;

			if (isIn && HasEmpty(cur, line))
			{
				result = cur;
				result += rightBottomOffset;
				return result;
			}
		}


		// 右一列
		for (int y=leftTop.y+1, yEnd=rightBottom.y-1; y<yEnd; ++y)
		{
			cur.x = leftTop.x;
			cur.y = y;

			bool isIn = bound.IsContains(cur)&& bound.IsContains(cur+rightBottomOffset);
//			isAllOut &= !isIn;

			if (isIn && HasEmpty(cur, line))
			{
				result = cur;
				result += rightBottomOffset;				
				return result;
			}
		}


		// 左一列
		for (int y=leftTop.y+1, yEnd=rightBottom.y-1; y<yEnd; ++y)
		{
			cur.x = rightBottom.x;
			cur.y = y;

			bool isIn = bound.IsContains(cur)&& bound.IsContains(cur+rightBottomOffset);
//			isAllOut &= !isIn;

			if (isIn && HasEmpty(cur, line))
			{
				result = cur;
				result += rightBottomOffset;				
				return result;
			}
		}


//		if (isAllOut)
//		{
//			break;
//		}

	}
	
	return result;
}

bool CentralLayer::HasEmpty( iVec2 const& leftTop, int line )
{
	MapGridLogicInfo info;
	for (int i=leftTop.x, iEnd=leftTop.x+line; i<iEnd; ++i)
	{
		for (int j=leftTop.y, jEnd=leftTop.y+line; j<jEnd; ++j)
		{
			if ( GetMapGridLogicInfo( map_index_to_index(ccp(i, j)), &info)) 
			{
				if (NULL!=info.pBuilding)
				{
					return false;
				}
			}
			else
			{
				return false;				
			}

		}			
	}

	return true;
}

void CentralLayer::FollowBuild( Unit* pRole, BuildingBase* pTarget )
{
	CCAssert(!pTarget->is_unit_type(UT_WORKER_BUILD), "");

	// 寻路
	iVec2 index = get_worker_target( pTarget->GetCenterPos(), pTarget->m_stBuildSubstrate.m_Line, pTarget->radius );
	bool isOk = FindRoad::sharedFindRoad()->SearchInHome(pRole, index);
	CCAssert(isOk, __FUNCTION__);

	pRole->m_ai_path.clear();
	FindRoad::sharedFindRoad()->GetPath(pRole->m_ai_path);
	pRole->m_ai_path.front() = half_title_covert_t::index_to_pos(index);
	pRole->cmd_moveto(pRole->m_ai_path.back().x, pRole->m_ai_path.back().y);

}

void CentralLayer::SendAWorker( BuildingBase* pHome, BuildingBase* pTarget )
{
	CCAssert(NULL!=pHome, "");
	CCAssert(NULL!=pTarget, "");

	CCAssert(pHome->is_unit_type(UT_WORKER_BUILD), "");
	CCAssert(!pTarget->is_unit_type(UT_WORKER_BUILD), "");
	CCAssert( NULL==pTarget->m_pWorker, "");


	Unit * pRole = GetFreeWorker(pHome);


	pRole->unit_ai_cmd_ = UNIT_AI_WORKER;
	pRole->m_pWorkerTarget = pTarget;
	pRole->m_pFromBuilding = pHome;

	pTarget->m_pWorker = pRole;
	
	// 寻路
	iVec2 index = get_worker_target( pTarget->GetCenterPos(), pTarget->m_stBuildSubstrate.m_Line, pTarget->radius );
	bool isOk = FindRoad::sharedFindRoad()->SearchInHome(pRole, index);
	CCAssert(isOk, __FUNCTION__);

	pRole->m_ai_path.clear();
	FindRoad::sharedFindRoad()->GetPath(pRole->m_ai_path);
	pRole->m_ai_path.front() = half_title_covert_t::index_to_pos(index);
	pRole->cmd_moveto(pRole->m_ai_path.back().x, pRole->m_ai_path.back().y);

}

void CentralLayer::FreeAWorker( BuildingBase* pBuild )
{
	CCAssert(NULL!=pBuild->m_pWorker, "");
	CCAssert(pBuild->m_pWorker->m_pWorkerTarget = pBuild, "");


	Unit* pRole = pBuild->m_pWorker;
	pBuild->m_pWorker = NULL;

	pRole->m_pWorkerTarget = NULL;


	Unit* pFromBuild = pRole->m_pFromBuilding;
	iVec2 index = get_build_door(pFromBuild->GetCenterPos(), pFromBuild->radius);
	bool isOk = FindRoad::sharedFindRoad()->SearchInHome(pRole, index);
	CCAssert(isOk, __FUNCTION__);
	
	pRole->m_ai_path.clear();
	FindRoad::sharedFindRoad()->GetPath(pRole->m_ai_path);
	// 寻路是1/2格子, 目标点是1/4格子
	pRole->m_ai_path.front() = half_title_covert_t::index_to_pos(index);	
	pRole->cmd_moveto(pRole->m_ai_path.back().x, pRole->m_ai_path.back().y);
}

Unit* CentralLayer::GetFreeWorker( Unit* pFrom )
{
	Unit* result = NULL;

	// 遍历容器, 找空闲工人, 返回途中
	for (int i=0, iEnd=unit_list_->count(); i<iEnd; ++i )
	{
		Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
		if (unit->m_pFromBuilding == pFrom)
		{
			if (NULL == unit->m_pWorkerTarget)
			{
				result = unit;
			}

			break;
		}
	}

	if (NULL==result)
	{
		iVec2 index = get_build_door(pFrom->GetCenterPos(), pFrom->radius);
		result = AddNpcPeople(UNIT_NPC_BUILDING_WORKER_001, to_CCPoint(half_title_covert_t::index_to_pos(index)));
	}


	return result;
}


void CentralLayer::SetAWorker(BuildingBase* pHome, BuildingBase* pTarget)
{
	CCAssert(NULL!=pHome, "");
	CCAssert(NULL!=pTarget, "");

	CCAssert(pHome->is_unit_type(UT_WORKER_BUILD), "");
	CCAssert(!pTarget->is_unit_type(UT_WORKER_BUILD), "");
	CCAssert( NULL==pTarget->m_pWorker, "");


	Unit * pRole = GetFreeWorker(pHome);


	pRole->unit_ai_cmd_ = UNIT_AI_WORKER;
	pRole->m_pWorkerTarget = pTarget;
	pRole->m_pFromBuilding = pHome;

	pTarget->m_pWorker = pRole;

	// 寻路
	iVec2 birth = get_worker_target( pTarget->GetCenterPos(), pTarget->m_stBuildSubstrate.m_Line, pTarget->radius );	
	pRole->setPosition(to_CCPoint(half_title_covert_t::index_to_pos(birth)));


	MoveWorkerToNewPos(pRole, pTarget);

}

void CentralLayer::MoveWorkerToNewPos( Unit * pRole, Unit* pTarget )
{
	iVec2 index = get_worker_target( pTarget->GetCenterPos(true), pTarget->m_stBuildSubstrate.m_Line, pTarget->radius );
	b2Vec2 pos = half_title_covert_t::index_to_pos(index);
	pRole->m_ai_path.push_back(pos);
	pRole->cmd_moveto(pos.x, pos.y);
}

void CentralLayer::InitResourceWorkerTarget( Unit* pRole, int taskNum )
{
	CCAssert(pRole->m_ResouceTarget.empty(), "");

	// 设置农工出生点
	Unit* pTownHall = GetTownHall();
	iVec2 homeIndex = get_build_door(pTownHall->GetCenterPos(), pTownHall->radius);
	pRole->setPosition(to_CCPoint(half_title_covert_t::index_to_pos(homeIndex)));
	

	// 设置农工目标点	
	std::vector<Unit*> targets;
	for (int i=0, iEnd=unit_list_->count(); i<iEnd; ++i )
	{
		Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
		unit_type t = unit->get_unit_type();
		if (unit->is_build_type() && t!=UT_TOWN_HALL_BUILD && t!=UT_WALL_BUILD)
		{
			targets.push_back(unit);
		}
	}

	

	int num = std::min(taskNum, static_cast<int>(targets.size()));

	pRole->m_ResouceTarget.push_back(pTownHall);
	
	for (int i=0; i<num; ++i)
	{
		int index = CCRANDOM_0_1() * targets.size();

		CCAssert(index<targets.size(), "");
		pRole->m_ResouceTarget.push_back( targets[index]);
		targets.erase(targets.begin()+index);
	}
	
}

std::vector<Unit*> CentralLayer::GetUnitWithType(unit_type type)
{
	std::vector<Unit*> result;

	for (int i=0, iEnd=unit_list_->count(); i<iEnd; ++i )
	{
		Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
		if (unit->is_unit_type(type))
		{
			result.push_back(unit);
		}
	}


	return result;
}

Unit* CentralLayer::GetTownHall()
{
	for (int i=0, iEnd=unit_list_->count(); i<iEnd; ++i )
	{
		Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
		if (unit->is_unit_type(UT_TOWN_HALL_BUILD))
		{
			return unit;
		}
	}

	return NULL;
}

Unit* CentralLayer::CreateResourceWorker( Unit* pHome )
{
	iVec2 index = get_build_door(pHome->GetCenterPos(), pHome->radius);
	Unit* result = AddNpcPeople(UNIT_NPC_RESOURCE_WORKER_001, to_CCPoint(half_title_covert_t::index_to_pos(index)));
	result->unit_ai_cmd_ = UNIT_AI_RESOURCE_WORKER;

	return result;
}

void CentralLayer::MoveAResourceWorkerToNewTarget( Unit* pRole )
{
	// 移动到目标
	Unit* firstTarget = pRole->m_ResouceTarget.back();
	iVec2 index = get_build_door(firstTarget->GetCenterPos(), firstTarget->radius);
	bool isOk = FindRoad::sharedFindRoad()->SearchInHome(pRole, index);
	CCAssert(isOk, __FUNCTION__);
	CCAssert(pRole->m_ai_path.empty(), "");
	FindRoad::sharedFindRoad()->GetPath(pRole->m_ai_path);
	pRole->m_ai_path.front() = half_title_covert_t::index_to_pos(index);	
	pRole->cmd_moveto(pRole->m_ai_path.back().x, pRole->m_ai_path.back().y);
}

void CentralLayer::AllWorkerRunAway()
{
	float const speed = 800/100*BUILDINTBASEGRID_EDGE_LEN;

	// 休息的木工
	Unit* pHome = GetTownHall();

	typedef std::vector<Unit*> unit_array_t;
	unit_array_t allWorker;
	
	// 建造中的木工
	{
		unit_array_t worker = GetUnitWithType(UT_NPC_BUILDING_WORKER);
		
		for (int i=0, iEnd=worker.size(); i!=iEnd; ++i)
		{
			Unit* pRole = worker[i];
			
			pRole->speed = speed;
			BuildingBase* pTarget = static_cast<BuildingBase*>(pRole->m_pWorkerTarget);
			pTarget->m_pWorker = NULL;
			pRole->m_pWorkerTarget = NULL;
			
			//pFrom->isBusy = false;
			//pFrom->busyUUID = 0;
			
		}
		allWorker.insert( allWorker.end(), worker.begin(), worker.end());
	}	

	// 休息的木工
	{
		unit_array_t workerBuild = GetUnitWithType(UT_WORKER_BUILD);
		
		unit_array_t::iterator iCur = workerBuild.begin();
		unit_array_t::iterator iEnd = workerBuild.end();
		
		for ( ; iCur!=iEnd; ++iCur) 
		{
			BuildingBase* pBuild = static_cast<BuildingBase*>(*iCur);
			
			if (!pBuild->isBusy) 
			{
				Unit* pRole = GetFreeWorker(pBuild);
				
				pRole->unit_ai_cmd_ = UNIT_AI_WORKER;
				pRole->speed = speed;		
				//pBuild->isBusy = true;
				pRole->m_pFromBuilding = pBuild;
				
				allWorker.push_back(pRole);			
			}
			
		}
		
	}


	// 女工
	{
		unit_array_t worker = GetUnitWithType(UT_NPC_RESOURCE_WORKER);

		for (int i=0, iEnd=worker.size(); i!=iEnd; ++i)
		{
			Unit* pRole = worker[i];

			pRole->speed = speed;
			pRole->m_WorkerTimes = 0;
			pRole->m_ResouceTarget.clear();
			pRole->m_role_time = Until::millisecondNow() + 3600 * 1000;
		}

		allWorker.insert(allWorker.end(), worker.begin(), worker.end());
	}


	{
		unit_array_t::iterator iCur = allWorker.begin();
		unit_array_t::iterator iEnd = allWorker.end();
		
		for ( ; iCur!=iEnd; ++iCur)
		{
			Unit* pRole = *iCur;
			
			iVec2 index = get_worker_target( pHome->GetCenterPos(), pHome->m_stBuildSubstrate.m_Line, pHome->radius );
			bool isOk = FindRoad::sharedFindRoad()->SearchInHome(pRole, index);
			CCAssert(isOk, __FUNCTION__);
			
			pRole->m_ai_path.clear();
			FindRoad::sharedFindRoad()->GetPath(pRole->m_ai_path);
			pRole->m_ai_path.front() = half_title_covert_t::index_to_pos(index);
			pRole->cmd_moveto(pRole->m_ai_path.back().x, pRole->m_ai_path.back().y);
		}		
	}

}


void CentralLayer::OnBattleSetBuildingWorker( std::vector<Unit*> &nowBuilding ) 
{
	std::vector<Unit*>::iterator iCur = nowBuilding.begin();
	std::vector<Unit*>::iterator iEnd = nowBuilding.end();
	
	for ( ; iCur!=iEnd; ++iCur)
	{
		BuildingBase* build = static_cast<BuildingBase*>(*iCur);
		
		BuildingBase* pWorkerHome = NoBusy();
		CCAssert(NULL!=pWorkerHome, "");
		pWorkerHome->isBusy = true;
		pWorkerHome->busyUUID = build->getuuID();
		
		SetAWorker(pWorkerHome, build);
	}
}

void CentralLayer::SetResourceWorker()
{
	Unit* pHome = GetTownHall();
	int roleNum = pHome->lv + 1;
	
	for (int i=0; i<roleNum; ++i)
	{
		Unit* pRole = CreateResourceWorker(pHome);
		
		InitResourceWorkerTarget(pRole, 4);
		
		CCAssert(1<pRole->m_ResouceTarget.size(), "最少有两个建筑");
		Unit* lastUnit = pRole->m_ResouceTarget.back();
		pRole->m_ResouceTarget.pop_back();
		
		iVec2 index = get_build_door(lastUnit->GetCenterPos(), lastUnit->radius);
		pRole->setPosition(to_CCPoint(half_title_covert_t::index_to_pos(index)));
		
		MoveAResourceWorkerToNewTarget(pRole);
			
	}	
}


















