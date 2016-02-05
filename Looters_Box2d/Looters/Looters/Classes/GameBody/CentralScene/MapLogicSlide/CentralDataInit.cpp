/***************************************************************
 author:     wangning
 write time: 2012.10.22
 function:   游戏主场景初始化
 ***************************************************************/

#include <iostream>
#include "CentralLayer.h"
#include "NetMessageManager.h"
#include "cocos2d.h"
#include "Until.h"
#include "CommonResource.h"
#include "ChangeLayer.h"
#include "LoadingLayer.h"
#include "SimpleAudioEngine.h"
#include "CCTextureCache.h"
#include "NavGraph.h"
#include "BattleRecorde.h"
#include "BattleReplay.h"

USING_NS_CC;

void DownloadMapInforResponse( int ID, Message* responseMessage);    //下载地图信息
void DownloadBattleInforResponse( int ID, Message* responseMessage); //下载战斗列表信息
void OperateSequenceResponse( int ID, Message* responseMessage); // 操作流水
void ProduceSoldiersResponse( int ID, Message* responseMessage); //生产造兵
void BattleMatchingResponse(int ID, Message* responseMessage); //匹配玩家
void RechargeResponse(int ID, Message* responseMessage); // 支付
void RevengeBattleResponse(int ID, Message* responseMessage); // 复仇
void UploadBattleFlowResponse(int ID,Message * responseMessage); // 上传战斗过程
void IoFileResponse(int ID,Message * responseMessage); //下载战斗过程
void BattleStartResponse(int ID,Message * responseMessage); // 开始战斗
void CancleBattleResponse(int ID,Message * responseMessage); // 取消战斗

bool CentralLayer::init( void )
{
	if( !CCLayer::init() )
		return false;
    
	//初始加载  变量的初始化
    m_iLandLevel = 0;
    m_tmxMap = NULL;

    m_fScaleMax = 1.8f;
	m_fScaleMin = 0.5f;
	m_fCurrentScale = 1.0f;
    m_BuildOperatingMode = MODE_NULL;
    
    //地图建筑信息加载
    downloadMap = false;
    downloadbattlelist = false;
    downloadFileList = false;
    downloadAllFile = false;
    
    link_downloadMapCount = 2;
	link_currentdownloadMapCount = 0;
    link_downloadbattlelistCount = 200;
    link_currentdownloadbattlelistCount = 0;
    link_downloadFileCount = 200;
    link_currentdownloadFileCount = 0;
    
    m_iLinkBankCountMax = 10;
	m_iLinkBankCountCurrent = 0;
    
    m_iLinkFileCountMax = 2;
	m_iLinkFileCountCurrent = 0;
    
    requestFileIndex = 0;
    
    //建筑相关
    build_uuId = BUILD_UU_ID;
    m_building = NULL;
    m_BuyBuilding = NULL;
    isUPSoldiers = false;
    isJianSoldiers = false;
    isSpeedUp = false;
    isjianSoldiers = false;
    sprTeX = NULL;
    
    m_PlaceState = PlaceState_First;
    
    // 流水账相关
    accountIntervalTime = 0;
    isAccount = true;
    m_Account = new vector<CentralOperate*>;
    m_Accelerated = new vector<CentralAccelerate*>;
    
    //人物相关
    people_uuId = PEOPLE_UU_ID;
    
    unit_list_ = CCArray::create();
    unit_list_->retain();
    
    particle_list_ = CCArray::create();
    particle_list_->retain();
    
    this->setTouchEnabled(true);
    
	//循环遍历所有
	this->schedule(schedule_selector(CentralLayer::Update),1.0f/60);
	PUSH_REPNSECALLFUNC(message_reponse(DownloadMapInforResponse));
    PUSH_REPNSECALLFUNC(message_reponse(DownloadBattleInforResponse));
    PUSH_REPNSECALLFUNC(message_reponse(OperateSequenceResponse));
    PUSH_REPNSECALLFUNC(message_reponse(ProduceSoldiersResponse));
    PUSH_REPNSECALLFUNC(message_reponse(BattleMatchingResponse));
    PUSH_REPNSECALLFUNC(message_reponse(RechargeResponse));
    
    PUSH_REPNSECALLFUNC(message_reponse(BattleStartResponse));
    PUSH_REPNSECALLFUNC(message_reponse(RevengeBattleResponse));
    PUSH_REPNSECALLFUNC(message_reponse(UploadBattleFlowResponse));
    PUSH_REPNSECALLFUNC(message_reponse(IoFileResponse));
    PUSH_REPNSECALLFUNC(message_reponse(CancleBattleResponse));
    
    // 数据初始化 视图模式 战斗模式
	StateLoad();
	return true;
}

void CentralLayer::StateLoad()
{
    CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
	m_enLoadProcess = DownloadMapInfor;
    
    // 初始化基础地格信息
    m_mapMapGridLogicInfo = new map<unsigned int,MapGridLogicInfo*>[MAPGRIDWIDTH*MAPGRIDHEIGHT];
    for( int i = 0; i < MAPGRIDWIDTH; i++ )
    {
        for (int j=0; j<MAPGRIDHEIGHT; j++) {
            MapGridLogicInfo info;
            info.bIsBiulded = false;
            info.mapIndex = ccp(float(i),float(j));
            this->AddMapGridLogicInfo(i*MAPGRIDHEIGHT+j, &info);
        }
    }
    	
    
    // 不同场景模式初始化
	if( data->m_enCentralViewMode == CENTRALVIEW_SELF ){

        SoundManage::GetSoundManageHandle()->_stopBackgroundMusic(true);
        SoundManage::GetSoundManageHandle()->_playBackgroundMusic("home_music.mp3", true);
        
        CreateMap();
		return;
    }

	if( data->m_enCentralViewMode == CENTRALVIEW_VISIT ){
        CreateMap();
		return;
    }
    
    if(data->m_enCentralViewMode == CENTRALVIEW_BATTLE){
        //战斗模式
        initBattleData();
        SoundManage::GetSoundManageHandle()->_stopBackgroundMusic(true);
        SoundManage::GetSoundManageHandle()->_playBackgroundMusic("combat_planning_music.mp3", true);
        
        if (data->m_enBattleMode == CENTRALVIEW_PVP) 
		{
             CreateMap();
        }

		return;
    }
}



void CentralLayer::initBattleData()
{
	// 战斗数据初始化
	battle_state_ = BATTLE_NONE;
	invalidSpArr = CCArray::create();
	invalidSpArr->retain();
	// 战斗场景
	m_InvalidCell = new map<unsigned int,InvalidCell*>[MAPGRIDWIDTH*MAPGRIDHEIGHT];
    
    battle_curbuildcount = 0;
    battle_loadbuildcount = 0;
    battle_currolecount = 0;
    battle_loadrolecount = 0;
    battle_star_count = 0;
    battle_golden_count = 0;
    battle_elixir_count = 0;
    battle_realgolden_count = 0;
    battle_realelixir_count = 0;
    
    battle_addpeoplecount = 0;
}

void CentralLayer::cleanBattle()
{
	for (int i=0; i<unit_list_->count();i++ )
	{
		Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
		if (unit->is_alive() && unit->is_unit_type(UT_ROLE))
		{
            if (unit->target)
            {
                if (!unit->target->is_alive())
                {
                    unit->target = NULL;
                }
            }
            if (unit->attack) {
                if (unit->attack->dest) {
                    if (!unit->attack->dest->is_alive()) {
                        unit->attack->dest = NULL;
                        unit->attack->force_end_skill();
                    }
                }
            }
			unit->_change_unit_state(UNIT_STATE_CHEER);
		}
	}
    
	invalidSpArr->release();
	if (((int)m_InvalidCell->size())>0)
	{
		while( m_InvalidCell->size() )
		{
			map<unsigned int,InvalidCell*>::iterator iter = m_InvalidCell->begin();
			delete iter->second;
			m_InvalidCell->erase( iter );
		}
		m_InvalidCell->clear();
	}
}

void CentralLayer::battle_update( float dt )
{
    CentralData* centralData = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
	this->battle_golden_count = 0;
    this->battle_elixir_count = 0;
    CentralData::userMapData_t::iterator pos;
	for( pos = centralData->m_M_UserMapData.begin(); pos != centralData->m_M_UserMapData.end(); ++pos )
	{
        CentralData::M_UserMapData& obj = pos->second;
        if(obj.building_id == RESOURCE_GOLDMINE || obj.building_id == RESOURCE_GOLDSTORAGE){
            this->battle_golden_count += obj.cut_collect_count;
        }
        
        if (obj.building_id == RESOURCE_ELIXIRPUMP || obj.building_id == RESOURCE_ELIXIRSTORAGE) {
            this->battle_elixir_count += obj.cut_collect_count;
        }
        
        if (obj.building_id == BUILDINGTYPE_TOWNHALL) {
            this->battle_golden_count += obj.cut_collect_count;
            this->battle_elixir_count += obj.cut_elixir_count;
        }
	}
}

void CentralLayer::UpdateLoadResAndData( float dt )
{
    if (NotNetworking) {
        m_enLoadProcess = NewMapBuild;
    }
    // 请求地图信息
    if (m_enLoadProcess == DownloadMapInfor) {
        if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enCentralViewMode == CENTRALVIEW_SELF)
        {
            NetMessageManager::GetMessageManager()->m_pMessageRequest->SendDownloadMapInforRequest(                                                                                                        GameData::m_stUserData->gamecenter_id);
        }
        else if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enCentralViewMode == CENTRALVIEW_BATTLE)
        {
            if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enPVPMode == BATTLE_MODE_PVP_MATCH) {
                NetMessageManager::GetMessageManager()->m_pMessageRequest->SendBattleMatchingRequest(GameData::m_stUserData->gamecenter_id, SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_MatchPlayer_ID,"",0);
            }
            else if(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enPVPMode == BATTLE_MODE_PVP_REVENGE){
                NetMessageManager::GetMessageManager()->m_pMessageRequest->SendBattleMatchingRequest(GameData::m_stUserData->gamecenter_id, SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_BattleInfo_PlayerID,"",1);
            }
        }
        
        m_enLoadProcess = ServerUpdate_DownloadMapInfor;
        return;
    }
    
    // 判定服务器数据是否返回成功
    if (m_enLoadProcess ==  ServerUpdate_DownloadMapInfor) {
        if (downloadMap == true) {
            if(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enCentralViewMode == CENTRALVIEW_BATTLE){
                m_enLoadProcess = NewMapBuild;
            }else if(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enCentralViewMode == CENTRALVIEW_SELF){
                if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_Central_UserData->battle_request_flag) {
                    m_enLoadProcess = DownloadBattleInfor;
                }else{
                    m_enLoadProcess = DownloadBattleInfor;
                }
            }
            return;
        }else {
            if( link_currentdownloadMapCount == link_downloadMapCount )
			{
				//连接失败
				link_currentdownloadMapCount = 0;
                if(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enCentralViewMode == CENTRALVIEW_BATTLE){
                    m_enLoadProcess = NewMapBuild;
                }else if(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enCentralViewMode == CENTRALVIEW_SELF){
                    m_enLoadProcess = DownloadBattleInfor;
                }
			}
			link_currentdownloadMapCount++;
        }
    }
        
    // 请求战斗信息列表
    if (m_enLoadProcess == DownloadBattleInfor) {
        m_enLoadProcess = ServerUpdate_DownloadBattleInfor;
        if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enCentralViewMode == CENTRALVIEW_SELF)
        {
            NetMessageManager::GetMessageManager()->m_pMessageRequest->SendDownloadBattleInforRequest(                                                                                                        GameData::m_stUserData->gamecenter_id,"1");
        }
    }
    
    // 判定战斗信息列表是否返回成功
    if (m_enLoadProcess ==  ServerUpdate_DownloadBattleInfor) {
        if (downloadbattlelist == true) {
            if(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_BattleInfoList.size() == 0){
                m_enLoadProcess = NewMapBuild;
            }else{
                m_enLoadProcess = DownloadFileInfor;
                
//                m_enLoadProcess = NewMapBuild; // 调试
            }
            return;
        }else {
            if( link_currentdownloadbattlelistCount == link_downloadbattlelistCount )
			{
				//连接失败
				link_currentdownloadbattlelistCount = 0;
				m_enLoadProcess = NewMapBuild;
			}
			link_currentdownloadbattlelistCount++;
        }
    }
    
    if (m_enLoadProcess == DownloadFileInfor) {
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
            m_enLoadProcess = ServerUpdate_DownloadFileInfor;
            //连接成功
            m_iLinkFileCountCurrent = 0;
            downloadFileList = false;
            CentralData * cData = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
            NetMessageManager::GetMessageManager()->m_pMessageRequest->SendIoFileRequest(cData->m_BattleStartResponseData.verifyCode,cData->m_BattleInfoList.at(requestFileIndex).replyFileName,cData->m_IoFileResponseData.index);
            
            CCLog("verifyCode == %d   |  replyFileName == %s |  index == %d",cData->m_BattleStartResponseData.verifyCode,cData->m_BattleInfoList.at(requestFileIndex).replyFileName.c_str(),cData->m_IoFileResponseData.index);
        }
    }
	
	    
    if (m_enLoadProcess == ServerUpdate_DownloadFileInfor) {
        if (downloadFileList == true) {
            if(downloadAllFile){
                m_enLoadProcess = NewMapBuild;
            }else{
                m_enLoadProcess = DownloadFileInfor;
            }
            return;
        }else {
            if( link_currentdownloadFileCount == link_downloadFileCount )
			{
				//连接失败
				link_currentdownloadFileCount = 0;
				m_enLoadProcess = NewMapBuild;
			}
			link_currentdownloadFileCount++;
        }
    }
    
    // 创建地图上已摆放的建筑
    if( m_enLoadProcess == NewMapBuild)
    {
        m_enLoadProcess = finish;
        
        if(NotNetworking)
		{
//			NavGraph::sharedNavGraph()->Reset();
//			LoadBattleReplayMap();
//
//#ifdef xyz_xyz
            //得到对象层
            CCTMXObjectGroup* Objtemp = m_tmxMap->objectGroupNamed("对象层1");
            if (Objtemp)
            {
                CCArray* tempArr = Objtemp->getObjects();
                
                int num = tempArr->count();
                //遍历所有的对象
                for (int i = 0; i < num; i++)
                {
                    CCDictionary* diceionary = (CCDictionary*)tempArr->objectAtIndex(i);
                    
                    
                    CCString *  buildIdStr = (CCString*)diceionary->objectForKey("ID");
                    int buildId = buildIdStr->intValue();
                    
                    CCString *  buildXStr = (CCString*)diceionary->objectForKey("IndexX");
                    int buildX = buildXStr->intValue();
                    
                    CCString *  buildYStr = (CCString*)diceionary->objectForKey("IndexY");
                    int buildY = buildYStr->intValue();
                    
                    
					if (buildId==40001)
					{
						BuildWall_first(buildId, ccp(buildX, buildY),false);
					}
					else
					{
						AddReadBuilding(buildId,ccp(buildX, buildY),build_uuId);
					}
                    
                    
                    build_uuId++;
                }
            }
//#endif // _DEBUG

        }
        return;
    }
}

void CentralLayer::CreateMap()
{
    // 加载地图背景图
    m_nodeArena = CCSprite::create();
    
    CCSprite * bg01= CCSprite::create(GAME_FILE_TRANSFORM("1024X2048_01",".png").c_str());
    bg01->setAnchorPoint(ccp(0,0.5));
    bg01->setPosition(ccp(-1664/2,0));
    m_nodeArena->addChild(bg01);
    
    CCSprite * bg02= CCSprite::create(GAME_FILE_TRANSFORM("1024X2048_02",".png").c_str());
    bg02->setAnchorPoint(ccp(0,0.5));
    bg02->setPosition(ccp(-640/2,0));
    m_nodeArena->addChild(bg02);
    
    CCSprite * bg03= CCSprite::create(GAME_FILE_TRANSFORM("1024X2048_03",".png").c_str());
    bg03->setAnchorPoint(ccp(0,0.5));
    bg03->setPosition(ccp(384/2,0));
    m_nodeArena->addChild(bg03);
    
    CCSprite * bg04= CCSprite::create(GAME_FILE_TRANSFORM("256X2048_04",".png").c_str());
    bg04->setAnchorPoint(ccp(1,0.5));
    bg04->setPosition(ccp(1664/2,0));
    m_nodeArena->addChild(bg04);
  
    
    this->addChild(m_nodeArena);
    m_nodeArena->setScale(1);
    m_nodeArena->setPosition(ccp(EXPLOIT_PIXELS_W/2,EXPLOIT_PIXELS_H/2));
    
    // 加载地图数据
    LoadMapInfo( 8 );
}

void CentralLayer::LoadMapInfo( int LandLevel )
{
	if( LandLevel != m_iLandLevel )
	{
		m_iLandLevel = LandLevel;
        
		char strMapFile[64];


		sprintf(strMapFile,"map%d", m_iLandLevel );

		if( m_tmxMap )
		{
			m_tmxMap->removeFromParentAndCleanup(true);
		}
        
		m_tmxMap = CCTMXTiledMap::create(GAME_FILE_TRANSFORM(strMapFile,".tmx").c_str());
        const char* name = "块层1";
        CCTMXLayer *layer = m_tmxMap->layerNamed(name);
        layer->setVisible(false);
        
        
        m_tmxMap->setAnchorPoint(ccp(0.5,0.5));
        m_pointCurrentMap = ccp(0,0);

        m_tmxMap->setPosition(ccpAdd(m_pointCurrentMap,ccp(-109,-91)));
        m_nodeArena->addChild(m_tmxMap);
		{
//			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GAME_FILE_TRANSFORM("build_num_num",".plist").c_str(),GAME_FILE_TRANSFORM("build_num_num",".png").c_str());
//			//m_batchBuildBottom = CCSpriteBatchNode::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(GAME_FILE_TRANSFORM("build_num_num",".png").c_str()), 30);
//			m_batchBuildBottom = CCNode::create();
//			m_tmxMap->addChild(m_batchBuildBottom, -100);			
		}
        
        if (0) {
            m_nodeDraws = CCNode::create();
            m_nodeDraws->setAnchorPoint(ccp(0.5,0.5));
            m_nodeDraws->setPosition(ccpAdd(ccp(0,0),ccp(0,0)));
            
            m_tmxMap->addChild(m_nodeDraws);
            for( int i = 0; i < MAPGRIDWIDTH; i++ )
            {
                for (int j=0; j<MAPGRIDHEIGHT; j++) {
                    if (j==0) {
                        CCPoint startPos = this->positionForIsoAt(ccp(j,i));
                        startPos.x = startPos.x + BUILDINGBASEGRID_WIDTH/2;
                        startPos.y = startPos.y + BUILDINTBASEGRID_HEIGHT;
                        CCPoint endPos = this->positionForIsoAt(ccp(MAPGRIDHEIGHT,i));
                        endPos.x = endPos.x + BUILDINGBASEGRID_WIDTH;
                        endPos.y = endPos.y + BUILDINTBASEGRID_HEIGHT/2;
                        
                        CCNode *node = BaseDrawLine::DrawLine(startPos, endPos, 1.0f);
                        node->setAnchorPoint(ccp(0,0));
                        m_nodeDraws->addChild(node,-20000);
                    }
                    if (i==0) {
                        CCPoint startPos = this->positionForIsoAt(ccp(j,i));
                        startPos.x = startPos.x + BUILDINGBASEGRID_WIDTH/2;
                        startPos.y = startPos.y + BUILDINTBASEGRID_HEIGHT;
                        CCPoint endPos = this->positionForIsoAt(ccp(j,MAPGRIDHEIGHT));
                        endPos.x = endPos.x;
                        endPos.y = endPos.y + BUILDINTBASEGRID_HEIGHT/2;
                        CCNode *node = BaseDrawLine::DrawLine(startPos, endPos, 1.0f);
                        node->setAnchorPoint(ccp(0,0));
                        m_nodeDraws->addChild(node,-20000);
                    }
                }
            }
        }
	}
}

int CentralLayer::ResourceMAXP()
{
    int m_p = 0;
    int num = unit_list_->count();
    //获取血量和添加主建筑资源
    for (int i = 0; i <num; i++)
    {
        Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
        //如果是建筑
        if (unit->is_build_type())
        {
            BuildingBase* build = (BuildingBase*)unit;
            if (build->getTypeID() == BUILDINGTYPE_TOWNHALL)
            {
                m_p += build->resourcesMaxNum;
            }    
            if (build->getTypeID() == RESOURCE_ELIXIRSTORAGE) 
            {
                m_p += build->resourcesMaxNum;
            }
        }
    }
    
    return m_p;
}

void CentralLayer::LoadBattleReplayMap()
{
	NavGraph::sharedNavGraph()->Reset();
	BattleReplay::sharedBattleReplay()->StartReplay(this, SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_battleReplay.c_str());	

	typedef std::vector<Unit*>  nowBuilding_t;
	nowBuilding_t nowBuilding;
	
	CentralData::M_UserMapData obj;
	CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;

	build_uuId = 0;
	bool hasNext = false;
	do 
	{
		hasNext = BattleReplay::sharedBattleReplay()->GetBuild(obj);
    
        // 战斗初始数据初始化
        this->battle_loadbuildcount++;
        
		// 生成地图上的建筑
		int buildId = obj.building_id*100+obj.building_level;
                        
		data->AddM_UserMapData(obj.uniqueness_build_id, obj);

		if (obj.building_id == BUILDINGTYPE_WALL) 
		{
			BuildingBase* build = BuildWall_first(buildId, ccp(obj.map_index_x, obj.map_index_y),false);
			build->setuuID(obj.uniqueness_build_id);
		}
		else 
		{
			BuildingBase* pBuild = AddReadBuilding(buildId,ccp(obj.map_index_x, obj.map_index_y),obj.uniqueness_build_id);
			if (obj.building_status==1)
			{
				nowBuilding.push_back(pBuild);
			}			
		}			

	} while (hasNext);
	

	{
		// 设置木工
		OnBattleSetBuildingWorker(nowBuilding);
		nowBuilding.clear();

		// 设置女工
		SetResourceWorker();
	}
	

}

void CentralLayer::FreeWorkers(int _uuid)
{
    int num = unit_list_->count();
    
    for (int i = 0; i <num; i++)
    {
        Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
        //如果是建筑
        if (unit->getTypeID() >0 && unit->getTypeID()<1000)
        {
            BuildingBase* build = (BuildingBase*)unit;
            if (build->getTypeID() == BUILDINGTYPE_WORKER)
            {
                if (build->isBusy)
                {
                    if (build->busyUUID == _uuid) 
                    {
                        build->busyUUID = 0;
                        build->isBusy = false;
                    }
                }
            }
        }
    }
}
BuildingBase* CentralLayer::NoBusy()
{
    int num = unit_list_->count();
    
    for (int i = 0; i <num; i++)
    {
        Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
        //如果是建筑
        if (unit->getTypeID() >0 && unit->getTypeID()<1000)
        {
            BuildingBase* build = (BuildingBase*)unit;
            if (build->getTypeID() == BUILDINGTYPE_WORKER)
            {
                if (!build->isBusy)
                {
                    return build;
                }
            }
        }
    }
    return NULL;
}
int CentralLayer::gemConversion(int _time)
{
    int gNum = 0;
    
    int timeM =  60;
    int timeH = 60*timeM;
    int timeD = 24*timeH;
    int timeZ = 7*timeD;
    
    int gemM =  1;
    int gemH = 20;
    int gemD = 260;
    int gemZ = 1000;
    
    
    
    if (_time <= timeM) 
    {
        //按照分钟计算
        gNum = gemM;
    }
    else if (_time <= timeH)
    {
        //按照小时计算
        float oneT = (float)timeH/gemH; //每个宝石加速的秒数
 
        float oneG = _time/oneT;
        if (oneG<1)
        {
            gNum = 1;
        }
        else
        {
            gNum = oneG;
            gNum+=1;
        }
        
    }
    else if (_time <= timeD)
    {
        //按照天计算
        float oneT = (float)timeD/gemD; //每个宝石加速的秒数
        float oneG = _time/oneT;
        if (oneG<1)
        {
            gNum = 1;
        }
        else
        {
            gNum = oneG;
            gNum+=1;
        }
    }
    else if (_time <= timeZ)
    {
        //按照周计算
        float oneT = (float)timeZ/gemZ; //每个宝石加速的秒数
        float oneG = _time/oneT;
        if (oneG<1)
        {
            gNum = 1;
        }
        else
        {
            gNum = oneG;
            gNum+=1;
        }
    }
    
    return gNum;
}

void CentralLayer::AdjustmentLens()
{
    int num = unit_list_->count();
    int allX = 0;
    int allY = 0;
    int allNum = 0;
    for (int i = 0; i <num; i++)
    {
        Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
        //如果是建筑
        if (unit->is_build_type())
        {
            BuildingBase* build = (BuildingBase*)unit;
            if (build->getTypeID() != BUILDINGTYPE_WALL)
            {
                allNum++;
                allX += build->getMapIndex().x;
                allY += build->getMapIndex().y;
            }
        }
    }
    
    SetMapLayerPos(positionForIsoAt(ccp(allX/allNum, allY/allNum)));
}
int CentralLayer::AllpeopleNum()
{
    int m_l = 0;
    int num = unit_list_->count();
    
    for (int i = 0; i <num; i++)
    {
        Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
        //如果是建筑
        if (unit->getTypeID() >0 && unit->getTypeID()<1000)
        {
            BuildingBase* build = (BuildingBase*)unit;
            if (build->getTypeID() == ARMY_BARRACK)
            {
                if (build->m_peopleSoldiers != NULL)
                {
                    for( int j = 0; j < (int)build->m_peopleSoldiers->size(); j++ )
                    {
                        CentralData::BuildableSoldiers* temp = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->getBuildableSoldiers(build->m_peopleSoldiers->at(j)->tyep);
                        const BasePeopleData* basePeopleData;
                        basePeopleData = GameData::GetDataFromBasePeopleData(temp->type * PEOPLE_TYPE_ *100 + temp->leve);
                        m_l+= (basePeopleData->HousingSpace*build->m_peopleSoldiers->at(j)->num);
                    }
                }
            }
            if (build->getTypeID() == ARMY_TROOPHOUSING)
            {
                for (int j=0; j<build->m_army.size(); j++)
                {                    
                    Unit* role = build->m_army[j];
                    const BasePeopleData* basePeopleData;
                    basePeopleData = GameData::GetDataFromBasePeopleData(role->getTypeID() *100 + role->lv);
                    m_l+= basePeopleData->HousingSpace;
                }
            }
        }
    }
    return m_l;
}
int CentralLayer::MAXpeopleNum()
{
    
    int m_l = 0;
    int num = unit_list_->count();
    
    for (int i = 0; i <num; i++)
    {
        Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
        //如果是建筑
        if (unit->getTypeID() >0 && unit->getTypeID()<1000)
        {
            BuildingBase* build = (BuildingBase*)unit;
            if (build->getTypeID() == ARMY_TROOPHOUSING)
            {
               const BaseBuildingLevelData* data = GameData::GetDataFromBaseBuildingLevelData(build->getTypeID()*100+build->lv);
                
                m_l += data->HousingSpace;
            }
            
        }
    }
    return m_l;
}
int CentralLayer::MAXTownhall()
{
    int m_l = 0;
    int num = unit_list_->count();
    
    for (int i = 0; i <num; i++)
    {
        Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
        //如果是建筑
        if (unit->getTypeID() >0 && unit->getTypeID()<1000)
        {
            BuildingBase* build = (BuildingBase*)unit;
            if (build->getTypeID() == BUILDINGTYPE_TOWNHALL)
            {
                if (m_l < build->lv)
                {
                    m_l = build->lv;
                }
                
            }
            
        }
    }
    return m_l;
}
int CentralLayer::MAXmagicLevel()
{
    int m_l = 0;
    int num = unit_list_->count();
    
    for (int i = 0; i <num; i++)
    {
        Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
        //如果是建筑
        if (unit->getTypeID() >0 && unit->getTypeID()<1000)
        {
            BuildingBase* build = (BuildingBase*)unit;
            if (build->getTypeID() == ARMY_SPELLFORGE)
            {
                if (m_l < build->lv)
                {
                    m_l = build->lv;
                }
                
            }
            
        }
    }
    return m_l;
}
void CentralLayer::UpBuildableLevel()
{
    

}
void CentralLayer::UpBuildableMagic()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    int soldLv = MAXmagicLevel();
    int soldLvMax = 0;
    for( int i = 0; i < (int)pCentralScene->m_pCentralData->m_BuildableMagic->size(); i++ )
    {
        if (soldLvMax<pCentralScene->m_pCentralData->m_BuildableMagic->at(i)->type) 
        {
            soldLvMax = pCentralScene->m_pCentralData->m_BuildableMagic->at(i)->type;
        }
    }
    
    if (soldLvMax < soldLv)
    {
        bool isW = true;
        int numT = 1;
        while (isW)
        {
            //添加可建造兵
            CentralData::BuildableMagic *obj = new CentralData::BuildableMagic();
            memset( obj,0,sizeof(CentralData::BuildableMagic) );
            
            obj->leve = 1;
            obj->num = 0;
            obj->type = soldLvMax+numT;
            pCentralScene->m_pCentralData->m_BuildableMagic->push_back(obj);
            
            numT++;
            
            if (obj->type >=soldLv)
            {
                isW = false;
            }   
        }
    }
}
void  CentralLayer::UpBuildableSoldiers()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    int soldLv = MAXSoldiersLevel();
    int soldLvMax = 0;
    for( int i = 0; i < (int)pCentralScene->m_pCentralData->m_BuildableSoldiers->size(); i++ )
    {
        if (soldLvMax<pCentralScene->m_pCentralData->m_BuildableSoldiers->at(i)->type) 
        {
            soldLvMax = pCentralScene->m_pCentralData->m_BuildableSoldiers->at(i)->type;
        }
    }
    if (soldLvMax < soldLv)
    {
        bool isW = true;
        int numT = 1;
        while (isW)
        {
            //添加可建造兵
            CentralData::BuildableSoldiers *obj = new CentralData::BuildableSoldiers();
            memset( obj,0,sizeof(CentralData::BuildableSoldiers) );
            
            obj->leve = 1;
            obj->type = soldLvMax+numT;
            obj->num = 0;
            pCentralScene->m_pCentralData->m_BuildableSoldiers->push_back(obj);
            
            numT++;
            
            if (obj->type >=soldLv)
            {
                isW = false;
            }   
        }
    }
}
int CentralLayer::MAXSoldiersLevel()
{
    int m_l = 0;
    int num = unit_list_->count();

    for (int i = 0; i <num; i++)
    {
        Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
        //如果是建筑
        if (unit->getTypeID() >0 && unit->getTypeID()<1000)
        {
            BuildingBase* build = (BuildingBase*)unit;
            if (build->getTypeID() == ARMY_BARRACK)
            {
                if (m_l < build->lv)
                {
                    m_l = build->lv;
                }
                
            }
        }
    }
    return m_l;
}
int CentralLayer::ResourceMAXG()
{
    int m_g = 0;
    int num = unit_list_->count();
    //获取血量和添加主建筑资源
    for (int i = 0; i <num; i++)
    {
        Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
        //如果是建筑
        if (unit->is_build_type())
        {
            BuildingBase* build = (BuildingBase*)unit;
            if (build->getTypeID() == BUILDINGTYPE_TOWNHALL)
            {
                
                m_g += build->resourcesMaxNum;
                
            }
            
            if (build->getTypeID() == RESOURCE_GOLDSTORAGE) 
            {
                m_g += build->resourcesMaxNum;
            }
            
        }
    }
    return m_g;
}
void CentralLayer::ResourceStorage()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    int m_g = pCentralScene->m_pCentralData->m_Central_UserData->user_gold;
    int m_p = pCentralScene->m_pCentralData->m_Central_UserData->user_potions;
    
    int buildG_hp = 0;
    int buildP_hp = 0;
    
    int num = unit_list_->count();
    //获取血量和添加主建筑资源
    for (int i = 0; i <num; i++)
    {
        Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
        //如果是建筑
        if (unit->is_build_type())
        {
            BuildingBase* build = (BuildingBase*)unit;
            if (build->getTypeID() == BUILDINGTYPE_TOWNHALL)
            {
               
                if (m_g > build->resourcesMaxNum)
                {
                    build->resourcesGoldNum = build->resourcesMaxNum;
                    m_g -= build->resourcesMaxNum;
                }
                else
                {
                    build->resourcesGoldNum = m_g;
                    m_g = 0;
                }
                
                if (m_p > build->resourcesMaxNum)
                {
                    build->resourcesPotionsNum = build->resourcesMaxNum;
                    m_p -= build->resourcesMaxNum;
                }
                else
                {
                    build->resourcesPotionsNum = m_p;
                    m_p = 0;
                }
            }
            
            if (build->getTypeID() == RESOURCE_ELIXIRSTORAGE) 
            {
                buildP_hp+=build->hp;
            }
            
            if (build->getTypeID() == RESOURCE_GOLDSTORAGE) 
            {
                buildG_hp+=build->hp;
            }
        }
    }
    
    
    bool isResources = true;
    int  leveNum = 1;
    int  hp_p = 0;
    int  hp_g = 0;
    while (isResources)
    {
        
        for (int i = 0; i <num; i++)
        {
            Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
            //如果是建筑
            if (unit->is_build_type())
            {
                BuildingBase* build = (BuildingBase*)unit;
                if (build->lv == leveNum) 
                {
                    if (build->getTypeID() == RESOURCE_ELIXIRSTORAGE) 
                    {
                        hp_p+=build->hp;
                        int r_num = 0;
                        if (buildP_hp != 0) {
                            r_num = m_p*build->hp/buildP_hp;
                        }
                        if (build->resourcesMaxNum > r_num) 
                        {
                            build->resourcesPotionsNum = r_num;
                        }
                        else
                        {
                            build->resourcesPotionsNum = build->resourcesMaxNum;
                            buildP_hp -=  hp_p;
                            m_p -= build->resourcesMaxNum;
                            if (m_p < 0) 
                            {
                                m_p = 0;
                            }
                            hp_p = 0;
                        }
                        
                    }
                    
                    if (build->getTypeID() == RESOURCE_GOLDSTORAGE) 
                    {
                        hp_g+=build->hp;
                        int r_num = 0;
                        if (buildG_hp != 0) {
                            r_num = m_g*build->hp/buildG_hp;
                        }
                        if (build->resourcesMaxNum > r_num) 
                        {
                            build->resourcesGoldNum = r_num;
                        }
                        else
                        {
                            build->resourcesGoldNum = build->resourcesMaxNum;
                            buildG_hp -=  hp_g;
                            m_g -= build->resourcesMaxNum;
                            if (m_g < 0) 
                            {
                                m_g = 0;
                            }
                            hp_g = 0;
                        }
                    }
                }
            }
        }
        
        leveNum++;
        if (leveNum >10)
        {
            isResources = false;
        }
    }
    
    for (int i = 0; i <num; i++)
    {
        Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
        //如果是建筑
        if (unit->is_build_type())
        {
            BuildingBase* build = (BuildingBase*)unit;
            if (build->getTypeID() == RESOURCE_ELIXIRSTORAGE)
            {
                
                
                
                

            }
            
            else if (build->getTypeID() == RESOURCE_GOLDSTORAGE)
            {
                float fl = (float)build->resourcesGoldNum / build->resourcesMaxNum;
                
                int flInt = 1;
                if (fl < 0.1)
                {
                    flInt = 1;
                }
                else if (fl < 0.3)
                {
                    flInt = 2;
                }
                else if (fl < 0.5)
                {
                    flInt = 3;
                }
                else if (fl < 0.7)
                {
                    flInt = 4;
                }
                else if (fl < 0.9)
                {
                    flInt = 5;
                }
                else
                {
                    flInt = 5;
                }
                
                if (build->resourcesGoldNum == build->resourcesMaxNum)
                {
                    CCSprite*   ui_map_qipaoman = CCSprite::createWithSpriteFrameName("ui_map_qipaoman.png");
                    ui_map_qipaoman->setPosition(ccp(build->sprite_->getContentSize().width/2,build->sprite_->getContentSize().height));
                    ui_map_qipaoman->setAnchorPoint(ccp(0.5,0));
                    
                    build->sprite_->removeChildByTag(10, false);
                    build->sprite_->addChild(ui_map_qipaoman,10,10);
                }
                else
                {
                    build->sprite_->removeChildByTag(10, false);
                }
                
                char strName[64];
                if (build->lv >= 10)
                {
                    sprintf(strName,"build_gold_%d",flInt);
                }
                else
                {
                    sprintf(strName,"build_gold10_%d",flInt);
                }
                
                
                
                
                CCSprite*   sprite = CCSprite::create(GAME_FILE_TRANSFORM(strName,".png").c_str());
                sprite->setPosition(ccp(build->sprite_->getContentSize().width/2-1,build->sprite_->getContentSize().height*3/5));
                sprite->setAnchorPoint(ccp(0.5,0));
                
                build->sprite_->removeChildByTag(9, false);
                build->sprite_->addChild(sprite,9,9);
                
                
                
            }
        }
    }
}
void CentralLayer::buildingAccelerated(int _tyep)
{
    CentralOperate *operate = new CentralOperate();
    memset( operate,0,sizeof(CentralOperate) );
    //
    operate->type = _tyep;
    operate->building_id = Accelerated_id;
    operate->uuid = Accelerated_uuid;
    operate->operation_time = Until::millisecondNow_m();
    operate->end_time = 0;
    operate->move_to_map_index_x = 0;
    operate->move_to_map_index_y = 0;
    operate->character_id = Accelerated_upid;
    operate->produce_count = Accelerated_gem_count;
    operate->remaining_time = 0;
    operate->build_upgrade_status = 0;
    operate->treasure_id = 0;
    
    
    m_Account->push_back(operate);
    
    
//    CentralAccelerate *accelerated = new CentralAccelerate();
//    memset( accelerated,0,sizeof(CentralAccelerate) );
//  
//    accelerated->tyep = _tyep;
//    accelerated->building_id = Accelerated_id;           
//    accelerated->uuid = Accelerated_uuid;                  
//    accelerated->gem_count = Accelerated_gem_count;
//    accelerated->remain_time = Until::millisecondNow_m();
////    accelerated->remain_time = Accelerated_remain_time; 
//    
//    m_Accelerated->push_back(accelerated);
}
void CentralLayer::buildingAccount2(int _tyep, int _num, bool isR)
{
    CentralOperate *operate = new CentralOperate();
    memset( operate,0,sizeof(CentralOperate) );
    //
    operate->type = _tyep;
    operate->building_id = 0;
    operate->uuid = 0;
    operate->operation_time = 0;
    operate->end_time = 0;
    operate->move_to_map_index_x = 0;
    operate->move_to_map_index_y = 0;
    operate->character_id = 0;
    operate->produce_count = 0;
    operate->remaining_time = 0;
    operate->build_upgrade_status = 0;
    operate->treasure_id = 0;
    switch (operate->type) 
    {
        case OperateType_BuyGold:
        {
            operate->treasure_id = _num;
            operate->operation_time = Until::millisecondNow_m();
        }
            break;
        case OperateType_BuyPotions:
        {
            operate->treasure_id = _num;
            operate->operation_time = Until::millisecondNow_m();
        }
            break;
        case OperateType_BuyEmerald:
        {
            operate->produce_count = _num;
            operate->operation_time = Until::millisecondNow_m();
        }
            break;
        case OperateType_BuyR:
        {
            if (isR)
            {
                operate->uuid = 0;
            }
            else
            {
                operate->uuid = 1;
            }
            operate->produce_count = _num;
            operate->operation_time = Until::millisecondNow_m();
        }
            break;
        default:
            break;
    }
    
    
    m_Account->push_back(operate);
}
void CentralLayer::buildingAccount(BuildingBase* build,int _tyep)
{
    
    CentralOperate *operate = new CentralOperate();
    memset( operate,0,sizeof(CentralOperate) );
    //
    operate->type = _tyep;
    operate->building_id = 0;
    operate->uuid = 0;
    operate->operation_time = 0;
    operate->end_time = 0;
    operate->move_to_map_index_x = 0;
    operate->move_to_map_index_y = 0;
    operate->character_id = 0;
    operate->produce_count = 0;
    operate->remaining_time = 0;
    operate->build_upgrade_status = 0;
    operate->treasure_id = 0;

    switch (operate->type) 
    {
        case OperateType_Build:
        {
            if (build->upgrade_state_ == UNIT_UPGRADE_BUILDSUCESS)
            {
                operate->build_upgrade_status = 2;
            }
            else
            {
                operate->build_upgrade_status = 0;
            }
            operate->building_id = build->getTypeID();
            operate->uuid = build->getuuID();
            
            operate->operation_time = Until::millisecondNow_m();
            operate->move_to_map_index_x = build->getMapIndex().x;
            operate->move_to_map_index_y = build->getMapIndex().y;
        }
            break;
        case OperateType_HarvestPotions:
        {

            operate->building_id = build->getTypeID();
            operate->uuid = build->getuuID();
            operate->operation_time = Until::millisecondNow_m();
            operate->produce_count = build->resourcesPotionsNum;
        }
            break;
        case OperateType_HarvestGold:
        {
            operate->building_id = build->getTypeID();
            operate->uuid = build->getuuID();
            operate->operation_time = Until::millisecondNow_m();
            operate->produce_count = build->resourcesGoldNum;
        }
            break;
        case OperateType_MobileBuilding:
        {
            
            operate->building_id = build->getTypeID();
            operate->uuid = build->getuuID();
            operate->operation_time = Until::millisecondNow_m();
            operate->move_to_map_index_x = build->getMapIndex().x;
            operate->move_to_map_index_y = build->getMapIndex().y;
        }
            break;
        case OperateType_UpgradeBuilding:
        {
            
            if (build->upgrade_state_ == UNIT_UPGRADE_SUCESS)
            {
                operate->build_upgrade_status = 1;
            }
            else
            {
                operate->build_upgrade_status = 0;
            }
            operate->building_id = build->getTypeID();
            operate->uuid = build->getuuID();
            operate->operation_time = Until::millisecondNow_m();
        }
            break;
        case OperateType_UpgradeMagic:
        case OperateType_UpgradeSoldiers:
        {
            operate->building_id = build->getTypeID();
            operate->uuid = build->getuuID();
            operate->character_id = build->UpLeveTyep;
            operate->operation_time = Until::millisecondNow_m();
        }
            break;
        case OperateType_MadeMagic:
        {
            operate->character_id = build->magicTyep;
            operate->operation_time = Until::millisecondNow_m();
            operate->build_upgrade_status = build->isCancelMagic;
            operate->building_id = build->getTypeID();
            operate->uuid = build->getuuID();
            
        }
            break;
        case OperateType_CancelTheUpgrade:
        {
            operate->building_id = build->getTypeID();
            operate->uuid = build->getuuID();
            operate->operation_time = Until::millisecondNow_m();
        }
            break;
        case OperateType_CancelTheBuilding:
        {
            operate->building_id = build->getTypeID();
            operate->uuid = build->getuuID();
            operate->operation_time = Until::millisecondNow_m();
        }
            break;
        default:
            break;
    }
    
    
    m_Account->push_back(operate);
}
void CentralLayer::jianloadRecruiting()
{
    if (m_building == NULL) return;
    if (m_building->m_jianPeopleSoldiers == NULL) return;
    int num = (int)m_building->m_jianPeopleSoldiers->size();
    
    for (int i = 0; i <num; i++)
    {
        CentralOperate *operate = new CentralOperate();
        memset( operate,0,sizeof(CentralOperate) );
        
        operate->type = OperateType_jianSoldiers;
        operate->building_id = m_building->getTypeID();
        operate->uuid = m_building->getuuID();
        operate->operation_time = m_building->m_jianPeopleSoldiers->at(i)->S_time;
        operate->end_time = 0;
        operate->move_to_map_index_x = 0;
        operate->move_to_map_index_y = 0;
        operate->character_id = m_building->m_jianPeopleSoldiers->at(i)->tyep;
        operate->produce_count = m_building->m_jianPeopleSoldiers->at(i)->num;
        operate->remaining_time = 0;
        operate->build_upgrade_status = 0;
        operate->treasure_id = 0;
        m_Account->push_back(operate);
    }
    
    
    for (int i = 0; i <num; i++)
    {
        delete m_building->m_jianPeopleSoldiers->at(i);
	}
	m_building->m_jianPeopleSoldiers->clear();

}
void CentralLayer::uploadRecruiting()
{
    if (m_building == NULL) return;
    
    m_building->setUploadSoldiersArr();
    if (m_building->m_UpPeopleSoldiers == NULL) return;
    int num = (int)m_building->m_UpPeopleSoldiers->size();
    
    for (int i = 0; i <num; i++)
    {
        CentralOperate *operate = new CentralOperate();
        memset( operate,0,sizeof(CentralOperate) );
        
        operate->type = OperateType_MadeSoldiers;
        operate->building_id = m_building->getTypeID();
        operate->uuid = m_building->getuuID();
        operate->operation_time = m_building->m_UpPeopleSoldiers->at(i)->S_time;
        operate->end_time = 0;
        operate->move_to_map_index_x = 0;
        operate->move_to_map_index_y = 0;
        operate->character_id = m_building->m_UpPeopleSoldiers->at(i)->tyep;
        operate->produce_count = m_building->m_UpPeopleSoldiers->at(i)->num;
        CCLOG("呀占发兵==========%d",operate->produce_count);
        operate->remaining_time = 0;
        operate->build_upgrade_status = 0;
        operate->treasure_id = 0;
        m_Account->push_back(operate);
    }
    
    
    for (int i = 0; i <num; i++)
    {
        delete m_building->m_UpPeopleSoldiers->at(i);
	}
	m_building->m_UpPeopleSoldiers->clear();
    
    
    /*
    if (!NetMessageManager::GetMessageManager()->m_pMessageRequest->SendProduceSoldiersRequest("1.0.0",                                                                                                         GameData::m_stUserData->gamecenter_id)) 
    {
        if (isSpeedUp)
        {
            isSpeedUp = false;
            
            buildingAccelerated(AccelerateType_MadeSoldiersAccelerated);
        }
    }
     */
}

void CentralLayer::uploadAccount()
{
    if (m_Account == NULL || m_Accelerated == NULL) 
    {
        isAccount = true;
        return;
    }
        
    
    if ((int)m_Account->size() < 1 && (int)m_Accelerated->size() < 1 ) 
    {
        isAccount = true;
        return;
    }
    
    NetMessageManager::GetMessageManager()->m_pMessageRequest->SendOperateSequenceRequest("1.0.0",                                                                                                         GameData::m_stUserData->gamecenter_id);
}


void ProduceSoldiersResponse( int ID, Message* responseMessage)
{
    if( ID == API_ProduceSoldiersResponse )
	{
		message::ProduceSoldiersResponse* message = (message::ProduceSoldiersResponse*)responseMessage;
		
		if( message->result() == Code_SUCCESS )//成功
		{
            CCLog("成功............");
            
            
//            if (pLayer->isSpeedUp)
//            {
//                pLayer->isSpeedUp = false;
//                
//                pLayer->buildingAccelerated(AccelerateType_MadeSoldiersAccelerated);
//            }

        }
        else{
            ErroCode__(message->result(), message->info());
        }
    }
}
void RechargeResponse( int ID, Message* responseMessage)
{
    CentralLayer* pLayer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    if( ID == API_RechargeResponse )
	{
		message::OperateSequenceResponse* message = (message::OperateSequenceResponse*)responseMessage;
		
        int O_num = message->result();
		CCLog("充值错误代码%d............",O_num);
        
		if( message->result() == Code_SUCCESS )//成功
		{
            CCLog("成功............");
            SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralUILayer->updateGem(BuyNode::sharedBuyNode()->num);
            pLayer->buildingAccount2(OperateType_BuyEmerald,BuyNode::sharedBuyNode()->num,true);
        }
        else{
            ErroCode__(message->result(), message->info());
        }
    }
}
void OperateSequenceResponse( int ID, Message* responseMessage)
{
    CentralLayer* pLayer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    if( ID == API_OperateSequenceResponse )
	{
		message::OperateSequenceResponse* message = (message::OperateSequenceResponse*)responseMessage;
		
        int O_num = message->result();
		CCLog("流水账错误代码%d............",O_num);
        
		if( message->result() == Code_SUCCESS )//成功
		{
            CCLog("成功............");
            for( int i = 0; i < (int)pLayer->m_Account->size(); i++ )
            {
                delete pLayer->m_Account->at(i);
            }
            pLayer->m_Account->clear();
            
            for( int i = 0; i < (int)pLayer->m_Accelerated->size(); i++ )
            {
                delete pLayer->m_Accelerated->at(i);
            }
            pLayer->m_Accelerated->clear();
        
        }
        else{
            ErroCode__(message->result(), message->info());
        }
        
        
        for( int i = 0; i < (int)pLayer->m_Account->size(); i++ )
        {
            delete pLayer->m_Account->at(i);
        }
        pLayer->m_Account->clear();
        
        for( int i = 0; i < (int)pLayer->m_Accelerated->size(); i++ )
        {
            delete pLayer->m_Accelerated->at(i);
        }
        pLayer->m_Accelerated->clear();
        pLayer->isAccount = true;

    }
}

void DownloadMapInforResponse(int ID, Message* responseMessage)
{
    CentralLayer* pLayer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    if( ID == API_DownloadMapInforResponse )
	{
		message::DownloadMapInforResponse* message = (message::DownloadMapInforResponse*)responseMessage;

		if( message->result() == Code_SUCCESS )//成功
		{
            CentralData*  _userData = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
            _userData->CleanData();
            // 玩家基础信息
            _userData->m_Central_UserData->nick_name = new string();
            *_userData->m_Central_UserData->nick_name = message->nick_name();
            
            _userData->m_Central_UserData->pvp_mark = message->pvp_mark();
            _userData->m_Central_UserData->exp = message->exp();
            _userData->m_Central_UserData->level = message->level();
            _userData->m_Central_UserData->shield_time = message->shield_time();
            _userData->m_Central_UserData->destroy_status = message->destroy_status();
            _userData->m_Central_UserData->battle_request_flag = message->battle_request_flag();
            _userData->m_Central_UserData->battle_end_time = message->battle_end_time();
            _userData->m_Central_UserData->battleMathingUseCount = message->battlemathingusecount();

            // 被攻击信息
            {
                int num = message->battleinforlist_size(); // 只会有一个
                for (int i=0; i<num; i++) {
                    message::DownloadMapInforResponse_BattleInfor temp = message->battleinforlist(i);
                    
                    _userData->m_Central_UserData->battleInfor = new CentralData::BattleInforTip();
                    memset( _userData->m_Central_UserData->battleInfor,0,sizeof(CentralData::BattleInforTip) );
                    
                    _userData->m_Central_UserData->battleInfor->attacker_nick_name = new string();
                    *_userData->m_Central_UserData->battleInfor->attacker_nick_name = temp.attacker_nick_name();
                    _userData->m_Central_UserData->battleInfor->defencer_get_pvp_mark = temp.defencer_get_pvp_mark();
                    _userData->m_Central_UserData->battleInfor->attack_time = new string();
                    *_userData->m_Central_UserData->battleInfor->attack_time = temp.attack_time();
                }
            }
            
            
            
            CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
            
            
            // 建筑物的损坏情况
            {
                int num = message->builddistorystatuslist_size();
                for (int i=0; i<num; i++) {
                    message::DownloadMapInforResponse_BuildDestoryStatus temp = message->builddistorystatuslist(i);
                    
                    CentralData::BuildDestoryStatusData obj;
					obj.building_id = temp.building_id();
                    obj.uuid = temp.uuid();
					obj.map_index_y = temp.map_index_y();
					obj.map_index_x = temp.map_index_x();
					
					// 生成地图上的建筑
                    pCentralScene->m_pCentralData->AddBuildDestoryStatusData(obj.building_id, obj);
                }
            }

			typedef std::vector<BuildingBase*>  nowBuilding_t;
			nowBuilding_t nowBuilding;

            BuildingBase* buildLABORATORY = NULL;
            // 地图建筑信息解析
            int num = message->usermapdatalist_size();
            for (int i = 0; i < num; i++)
            {
               
                message::DownloadMapInforResponse_UserMapData temp = message->usermapdatalist(i);
          
                int buildLeve = temp.building_level();
                int buildType = temp.building_id();
                int buildX = temp.map_index_x();
                int buildY = temp.map_index_y();
                int buildId = buildType*100+buildLeve;
                int builduuId = temp.uniqueness_build_id();
                
                
                BuildingBase* build = NULL;
                if (buildType==BUILDINGTYPE_WALL)
                {
                    build = pLayer->BuildWall_first(buildId, ccp(buildX, buildY),false);
                    build->setuuID(builduuId);
                }
                else
                {
                    build = pLayer->AddReadBuilding(buildId,ccp(buildX, buildY),builduuId);
                }
                build->setData();
                
                
                build->upgrade_state_ = UNIT_UPGRADE_NONE;
                
                if (pCentralScene->m_pCentralData->GetBuildDestoryStatusData(temp.uniqueness_build_id())) {
                    // 切建筑物恢复状态
                    
                }
                
                if (temp.build_status() == 2)
                {
                    long LsavsTime = Until::time_millisecondNow(temp.build_upgrade_end_time());
                    
                    const BaseBuildingLevelData* buildingBaseLevelData;
                    buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( build->getID());
                    
                    build->m_iBuildCDTime = buildingBaseLevelData->BuildTimeD*24*60*60+ buildingBaseLevelData->BuildTimeH*60*60 +buildingBaseLevelData->BuildTimeM*60;
                    
                    build->savsTime = LsavsTime - build->m_iBuildCDTime;
                    
                    build->upgrade_state_ = UNIT_UPGRADE_BUILD;

					nowBuilding.push_back(build);
                }
                else if (temp.build_status() == 3)
                {
                    long LsavsTime = Until::time_millisecondNow(temp.build_upgrade_end_time());
                    const BaseBuildingLevelData* buildingBaseLevelData;
                    buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( build->getID()+1);
                    build->m_iBuildCDTime = buildingBaseLevelData->BuildTimeD*24*60*60+ buildingBaseLevelData->BuildTimeH*60*60 +buildingBaseLevelData->BuildTimeM*60;
                    
                    build->savsTime = LsavsTime - build->m_iBuildCDTime;
                    
                    build->upgrade_state_ = UNIT_UPGRADE_START;

					nowBuilding.push_back(build);					
                }
                
                
                if (buildType == ARMY_BARRACK)
                {
                    int barrack_num = temp.barrackorliblist_size();
                    for (int j = 0; j < barrack_num; j++)
                    {
                        message::DownloadMapInforResponse_UserMapData_BarrackOrLib tempBarrack = temp.barrackorliblist(j);
                        if (tempBarrack.produce_count() > 0)
                            
                        {
                            build->addInfoSoldiers(tempBarrack.character_id(),tempBarrack.end_time(),tempBarrack.produce_count(),tempBarrack.index(),tempBarrack.character_level());
                        }
                        
                        
                    }
                }
                else if(buildType == RESOURCE_ELIXIRPUMP)
                {
                    
                    long tempTime = Until::millisecondNow_m();
                    
                    build->resourcesPotionsNum = temp.collect_count();
                    build->buildEventTime  =   tempTime - (build->resourcesPotionsNum*3600)/build->resourcesCDNum;
                    build->buildxiaoguoEventTime = Until::millisecondNow_m();
                }
                else if(buildType == RESOURCE_GOLDMINE)
                {
                    long tempTime = Until::millisecondNow_m();
                    build->resourcesGoldNum = temp.collect_count();
                    build->buildEventTime  =   tempTime - (build->resourcesGoldNum*3600)/build->resourcesCDNum;
                    build->buildxiaoguoEventTime = Until::millisecondNow_m();

                }
                else if(buildType == ARMY_LABORATORY)
                {
                    buildLABORATORY = build;
                    
                }
                
                if (builduuId > pLayer->build_uuId)
                {
                    pLayer->build_uuId = builduuId;
                }
            }


			// 建筑中的分配工人
			{
				nowBuilding_t::iterator iCur = nowBuilding.begin();
				nowBuilding_t::iterator iEnd = nowBuilding.end();

				for ( ; iCur!=iEnd; ++iCur)
				{
					BuildingBase* build = *iCur;

					BuildingBase* pWorkerHome = pCentralScene->m_pCentralLayer->NoBusy();
					CCAssert(NULL!=pWorkerHome, "");
					pWorkerHome->isBusy = true;
					pWorkerHome->busyUUID = build->getuuID();

					
					pCentralScene->m_pCentralLayer->SetAWorker(pWorkerHome, build);
				}

				nowBuilding.clear();
			}

			//调整镜头
            pLayer->AdjustmentLens();
            
            
            pLayer->build_uuId+=1;
            
            //资源上线
            _userData->m_Central_UserData->user_goldMAX = pLayer->ResourceMAXG();
            _userData->m_Central_UserData->user_potionsMAX = pLayer->ResourceMAXP();
            _userData->m_Central_UserData->peopleNumMax = pLayer->MAXpeopleNum();
            
            _userData->m_Central_UserData->user_gem = 0;
            _userData->m_Central_UserData->user_gold = 0;
            _userData->m_Central_UserData->user_potions = 0;
            //资源存储
            pLayer->ResourceStorage();
            
            pCentralScene->m_pCentralUILayer->updateGold(message->golden_count());
            pCentralScene->m_pCentralUILayer->updatePotions(message->elixir_count());
            pCentralScene->m_pCentralUILayer->updateGem(message->gem_count());
            pCentralScene->m_pCentralUILayer->updateExp(0);
            pCentralScene->m_pCentralUILayer->updatePeasant();
            
            
            
            num = message->usercharacterlist_size();
            for (int i = 0; i < num; i++)
            {
                
                message::DownloadMapInforResponse_UserCharacter temp = message->usercharacterlist(i);

                //添加可建造兵
                CentralData::BuildableSoldiers *obj = new CentralData::BuildableSoldiers();
                memset( obj,0,sizeof(CentralData::BuildableSoldiers) );
                
                obj->leve = temp.character_level();
                obj->type = temp.character_id();
                obj->num = temp.character_count();
                pCentralScene->m_pCentralData->m_BuildableSoldiers->push_back(obj);

                long findex = Until::time_millisecondNow(temp.upgrade_character_finish_time());
                if (findex>1)
                {
                    const BasePeopleData* basePeopleData = GameData::GetDataFromBasePeopleData(obj->type * PEOPLE_TYPE_*100 + obj->leve);
                    buildLABORATORY->UpLeveTyep = temp.character_id();
                    buildLABORATORY->isMroS = false;
                    buildLABORATORY->UPLeveCDTime = basePeopleData->UpgradeTimeH*60*60;
                    buildLABORATORY->UpLeveTime = findex - buildLABORATORY->UPLeveCDTime;
                    
                   
                }
                
                
                //添加已有的兵
                const BasePeopleData* pdata = GameData::GetDataFromBasePeopleData(obj->type*100000+obj->leve);
                
                int u_num = temp.character_count();
                
                for (int j = 0; j < u_num; j++)
                {
                    BuildingBase* unit_U = pLayer->matchingCampfire(pdata->HousingSpace, b2Vec2(0.f, 0.f));
                    if (!unit_U) {
                        break;
                    }
                                        
					iVec2 index = quad_title_random_index(unit_U->m_stBuildSubstrate.m_Line, unit_U->radius);
					index += quad_title_left_top_index(unit_U->GetCenterPos(), unit_U->m_stBuildSubstrate.m_Line);
					b2Vec2 pos = quad_title_covert_t::index_to_pos(index);
					
                    Unit * u = pLayer->AddPeople(temp.character_id() * 100000 +1,to_CCPoint(pos),NULL);
                    u->unit_ai_cmd_ = UNIT_AI_PATROL;
                    unit_U->m_army.push_back(u);
                    u->m_pCampfire = unit_U;
							
					u->m_role_time = Until::millisecondNow() + Unit::get_next_walk_time();
					
                }
                _userData->m_Central_UserData->allYouPeopleNum += pdata->HousingSpace*u_num;
                
            }
            
            _userData->m_Central_UserData->allPeopleNum = pLayer->AllpeopleNum();
            
            //初始化魔法信息
            num = message->spelllist_size();
            for (int i = 0; i < num; i ++)
            {
                message::DownloadMapInforResponse_Spell temp = message->spelllist(i);
                
                CentralData::BuildableMagic *obj = new CentralData::BuildableMagic();
                memset(obj, 0, sizeof(CentralData::BuildableMagic));
                
                obj->type = temp.spell_type_id();
                obj->leve = temp.spell_level();
                obj->num = temp.spell_count();
                
                pCentralScene->m_pCentralData->m_BuildableMagic->push_back(obj);
                
                
            }
            

			pLayer->downloadMap = true;
            
            SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralUILayer->BasisInfo();
            
            if (ChangeLayer::isChangeLayer()) {
                ChangeLayer::HideChangeLayer();
            }else{
                LoadingLayer::HideLoadingLayer();
            }

			{
				CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
				CCAssert(data->m_enCentralViewMode == CENTRALVIEW_SELF, "");		
				SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->SetResourceWorker();								
			}
            
		}else{
            ErroCode__(message->result(), message->info());
        }
	}
}

void DownloadBattleInforResponse(int ID, Message* responseMessage){
    CentralLayer* pLayer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    CentralData* lData = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    if( ID == API_DownloadBattleInforResponse )
	{
		message::DownloadBattleInforResponse* message = (message::DownloadBattleInforResponse*)responseMessage;
        
		if( message->result() == Code_SUCCESS )//成功
		{
            CCLog("下发战斗信息列表成功");
            
            int num = message->battleinforlist_size();
            for (int i = 0; i < num; i++)
            {
                
                message::DownloadBattleInforResponse_BattleInfor temp = message->battleinforlist(i);

                CentralData::BattleInfor obj;
                obj.bowie_id = temp.bowie_id();
                obj.attacker_level = temp.attacker_level();
                obj.attacker_nick_name = temp.attacker_nick_name();
                obj.attacker_get_golden_count = temp.attacker_get_golden_count();
                obj.attacker_get_elixir_count = temp.attacker_get_elixir_count();
                obj.attack_time = temp.attack_time();
                obj.defencer_get_pvp_mark = temp.defencer_get_pvp_mark();
                obj.clans_name = temp.clans_name();
                obj.clans_image_name = temp.clans_image_name();
                obj.replyFileName = temp.replyfilename();
                obj.star_count = temp.star_count();
                
                int anum = temp.attackerusedlist_size();
                for (int j=0; j<anum; j++) {
                    message::DownloadBattleInforResponse_BattleInfor_AttackerUsed tt = temp.attackerusedlist(j);
                    CentralData::AttackerUsed aobj;
                    aobj.used_id = tt.used_id();
                    aobj.used_count = tt.used_count();
                    aobj.used_type = tt.used_type();
                    
                    obj.attackerUsedList.push_back(aobj);
                }
                
                
                lData->m_BattleInfoList.push_back(obj);
            }
            
            pLayer->downloadbattlelist = true;
        }else{
            ErroCode__(message->result(), message->info());
        }
    }
}

void CentralLayer::battleStartRequest()
{
	if(NotNetworking){
		return;
	}
	NetMessageManager::GetMessageManager()->m_pMessageRequest->SendBattleStartRequest(GameData::m_stUserData->gamecenter_id,SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_MatchPlayer->gameCenterID->c_str(),Until::millisecondNow_time(Until::millisecondNow_m()));
}




void BattleMatchingResponse(int ID, Message* responseMessage)
{
	CentralLayer* pLayer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
	if( ID == API_BattleMatchingResponse )
	{
		message::BattleMatchingResponse* message = (message::BattleMatchingResponse*)responseMessage;
		
		if( message->result() == Code_SUCCESS )//成功
		{
			NavGraph::sharedNavGraph()->Reset();

			CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
			// 匹配玩家基本信息
			{
				data->m_MatchPlayer->gameCenterID = new string();
				*data->m_MatchPlayer->gameCenterID = message->defencer_mailaddress();
                data->m_MatchPlayer_ID = message->defencer_mailaddress();
				data->m_MatchPlayer->nickName = new string();
				*data->m_MatchPlayer->nickName = message->nick_name();
				data->m_MatchPlayer->golden_count = message->golden_count();
                CCLog("匹配到玩家的金币数%d",data->m_MatchPlayer->golden_count);
				data->m_MatchPlayer->elixir_count = message->elixir_count();
                CCLog("匹配到玩家的药水数%d",data->m_MatchPlayer->elixir_count);
				data->m_MatchPlayer->pvp_mark = message->pvp_mark();
				data->m_MatchPlayer->level = message->level();
				
                data->m_MatchPlayer->used_clans_character_count = message->used_clans_character_count();
                data->m_MatchPlayer->lose_pvp_mark = message->lose_pvp_mark();
                
                SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralPVPMapUILayer->response_CallUI();
			}
			
			typedef std::vector<Unit*>  nowBuilding_t;
			nowBuilding_t nowBuilding;
			// 地图建筑信息解析
			{
				int num = message->usermapdatalist_size();
				for (int i = 0; i < num; i++)
				{
					
					message::BattleMatchingResponse_UserMapData temp = message->usermapdatalist(i);
					
					CentralData::M_UserMapData obj;
					obj.building_level = temp.building_level();
					obj.building_id = temp.building_id();
					obj.map_index_y = temp.map_index_y();
					obj.map_index_x = temp.map_index_x();
					obj.building_status = temp.building_status();
					obj.collect_count = temp.collect_count();
                    obj.second_elixir_count = temp.second_elixir_count();
					obj.uniqueness_build_id = temp.uniqueness_build_id();
                    CCLog("匹配到玩家的建筑金币数%d",obj.collect_count);
                    CCLog("匹配到玩家的建筑药水数%d",obj.second_elixir_count);
					
					// 生成地图上的建筑
					int buildId = obj.building_id*100+obj.building_level;
                    data->AddM_UserMapData(obj.uniqueness_build_id, obj);
                    
                    
                    BuildingBase* build = NULL;
                    if (obj.building_id == BUILDINGTYPE_WALL) {
                        build = pLayer->BuildWall_first(buildId,ccp(obj.map_index_x, obj.map_index_y),false);
                        build->setuuID(obj.uniqueness_build_id);
                    }else {
                        build = pLayer->AddReadBuilding(buildId,ccp(obj.map_index_x, obj.map_index_y),obj.uniqueness_build_id);
                        pLayer->battle_loadbuildcount++;//统计下发的建筑数量
                    }
                    
                    if (obj.building_status==1)
                    {
                        nowBuilding.push_back(build);
                        build->upgrade_state_ = UNIT_UPGRADE_BUILDIN;
                    }else{
                        build->upgrade_state_ = UNIT_UPGRADE_NONE;
                    }

					BattleRecorde::sharedBattleRecorde()->AddBuild(obj);
					
				}
				pLayer->getInvalidLocation();
				pLayer->showInvalidLocation();
			}
			
			// 兵和魔法信息
			{
				int num = message->soldiersandspelllist_size();
				for (int i=0; i<num; i++) {
					message::BattleMatchingResponse_AttackerSoldiersAndSpell temp = message->soldiersandspelllist(i);
					int used_type = temp.used_type();
					if (used_type == 0) {
						CentralData::AttackerSoldiersAndSpell *obj = new CentralData::AttackerSoldiersAndSpell();
						memset( obj,0,sizeof(CentralData::AttackerSoldiersAndSpell) );
						obj->used_type = used_type;
						obj->characterIdOrSpellId = temp.characteridorspellid();
						obj->characterOrSpellLevel = temp.characteridorspellid();
						obj->count = temp.count();
						obj->maxcount = temp.count();
						
						data->m_AttackerSoldiersAndSpell->push_back(obj);
                        
                        pLayer->battle_loadrolecount = pLayer->battle_loadrolecount + obj->maxcount;
					}
				}
                CentralPVPMapUILayer *layer = (CentralPVPMapUILayer*)SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralPVPMapUILayer;
                layer->addAttackerSoldiersAndSpellList(data->m_AttackerSoldiersAndSpell);
            }
            
            
			pLayer->downloadMap = true;
            
            
            ChangeLayer::HideChangeLayer();

			{
				// 设置木工
				pLayer->OnBattleSetBuildingWorker(nowBuilding);
				nowBuilding.clear();

				// 设置女工
				pLayer->SetResourceWorker();
			}
            
            pLayer->battle_state_ = CentralLayer::BATTLE_READY;
		}
        else{
            ErroCode__(message->result(), message->info());
        }
	}
}

void RevengeBattleResponse(int ID, Message* responseMessage)
{
	if( ID == API_RevengeBattleResponse )
	{
		message::RevengeBattleResponse* message = (message::RevengeBattleResponse*)responseMessage;
		
		if( message->result() == Code_SUCCESS )//成功
		{
            SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralMailUILayer->itemlayer->revengeBattleRequest_callback();
        }
        else{
            ErroCode__(message->result(), message->info());
        }
    }
}

void BattleStartResponse(int ID,Message * responseMessage)
{
    CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    if( ID == API_BattleStartResponse )
	{
		message::BattleStartResponse* message = (message::BattleStartResponse*)responseMessage;
		
		if( message->result() == Code_SUCCESS )//成功
		{
            data->m_BattleStartResponseData.battleId = message->battleid();
            data->m_BattleStartResponseData.verifyCode = message->verifycode();
        }
        else{
            ErroCode__(message->result(), message->info());
        }
    }
}

void UploadBattleFlowResponse(int ID,Message * responseMessage)
{
    if( ID == API_UploadBattleFlowResponse )
	{
		message::UploadBattleFlowResponse* message = (message::UploadBattleFlowResponse*)responseMessage;
		
		if( message->result() == Code_SUCCESS )//成功
		{
			CCLOG("ok up Battle!");
        }
        else{
            ErroCode__(message->result(), message->info());
        }
    }
}

void IoFileResponse(int ID,Message * responseMessage)
{
    if( ID == API_IoFileResponse )
	{
		message::IoFileResponse* message = (message::IoFileResponse*)responseMessage;
		
		if( message->result() == Code_SUCCESS )//成功
		{
            CentralLayer* pLayer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
            CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
            
            data->m_IoFileResponseData.maxPackage = message->maxpackage();
            data->m_IoFileResponseData.index = message->index();
            message::IoFileResponse_IoData iodata = message->iodata();
        
            
            for (int i=0; i<iodata.data_size(); i++) {
                string str = iodata.data(i);
                CCLog("length == %d",str.length());
                data->m_IoFileResponseData.ioData.append(str);
            }
            
            if (data->m_IoFileResponseData.index + iodata.data_size() >= data->m_IoFileResponseData.maxPackage) {
                

                CentralData::BattleInfor battleInfo = data->m_BattleInfoList.at(pLayer->requestFileIndex);
                //将字符串保存成文件
                string dc = CCFileUtils::sharedFileUtils()->getWriteablePath();
                dc.append(battleInfo.replyFileName);
                
                FILE * fp = fopen(dc.c_str(), "wb");
                fwrite(data->m_IoFileResponseData.ioData.data(), 1, data->m_IoFileResponseData.ioData.size(), fp);
                fclose(fp);
                
                
                data->m_IoFileResponseData.index = 0;
                data->m_IoFileResponseData.maxPackage = 0;
                data->m_IoFileResponseData.ioData.clear();
                //如果下载完毕 切换状态
                pLayer->requestFileIndex++;
                if (pLayer->requestFileIndex == data->m_BattleInfoList.size()) {
                    pLayer->downloadFileList = true;
                    pLayer->downloadAllFile = true;
                    return;
                }else{
                    pLayer->downloadFileList = true;
                }
            }
        }
        else{
            ErroCode__(message->result(), message->info());
        }
    }
}

void CancleBattleResponse(int ID,Message * responseMessage)
{
    if( ID == API_CancleBattleResponse )
	{
		message::CancleBattleResponse* message = (message::CancleBattleResponse*)responseMessage;
		
		if( message->result() == Code_SUCCESS )//成功
		{
            CCLog("");
        }
        else{
            ErroCode__(message->result(), message->info());
        }
    }
}
