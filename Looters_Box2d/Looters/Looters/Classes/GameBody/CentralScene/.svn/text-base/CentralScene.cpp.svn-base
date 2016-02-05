#include "GameControl.h"
#include "NetMessageManager.h"
#include "Until.h"

#include "CentralUILayer.h"
#include "CentralShopUILayer.h"
#include "CentralInfoUILayer.h"
#include "CentralPVPUILayer.h"
#include "CentralPVPMapUILayer.h"
#include "CentralBattleReplayUILayer.h"
#include "LoadingLayer.h"
#include "NavGraph.h"
USING_NS_CC;

CentralScene::CentralScene()
{
    m_pCentralData = NULL;
    m_pCentralLayer = NULL;
    m_pCentralUILayer = NULL;
    m_pCentralShopUILayer = NULL;
    m_pCentralInfoUILayer = NULL;
    m_pCentralPVPUILayer = NULL;
    m_pCentralPVPMapUILayer = NULL;
    m_pCentralBattleEndUILayer = NULL;
    m_pCentralInfo2UILayer = NULL;
    m_pCentralSettingsUILayer = NULL;
    m_pCentralAccountNameLayer = NULL;
    m_CentralAccountLoginLayer = NULL;
    m_CentralBattleReplayUILayer = NULL;
}

CentralScene::~CentralScene()
{
    if( m_pCentralData )
		m_pCentralData->release();
    
    cleanBaseData();
    
    SceneManage::GetSceneManageHendle()->m_pCentralScene = NULL;
}

void CentralScene::cleanBaseData()
{
	GameData::m_mapBuildingBaseData.clear();
    GameData::m_mapPeopleBaseData.clear();
    GameData::m_mapAttackBaseData.clear();
    GameData::m_mapMissleBaseData.clear();
	GameData::m_mapUnitClassBaseData.clear();
    GameData::m_mapSpellBaseData.clear();
    GameData::m_mapAnimationBaseData.clear();
    GameData::m_mapTextBaseData.clear();
    GameData::m_mapNpcLevelBaseData.clear();
    GameData::m_mapTownHallLevelBaseData.clear();
    GameData::m_mapObstacleBaseData.clear();
    GameData::m_mapEffectBaseData.clear();
    GameData::m_mapExperienceLevelsBaseData.clear();
    
    SoundManage::GetSoundManageHandle()->unload_Effects(); //释放音效
}

bool CentralScene::init()
{
    if ( !CCScene::init() )
    {
        return false;
    }
    
    m_pCentralData = CentralData::Load();
    LoadSceneLayer(CENTRALVIEW_SELF);
    //基础数据的初始化
    initBaseData();
    return true;
}

bool CentralScene::initBaseData()
{
    TranscribeBaseData();
    initUnitClassesData();
    
    loadAllSoundEffect();
    return true;
}

// 建筑的基础数据录入
void CentralScene::TranscribeBaseData( void )
{
    GameFile::GetGameFileHandle()->readCSV_buildlevel();
    GameFile::GetGameFileHandle()->readCSV_characters();
    GameFile::GetGameFileHandle()->readCSV_attacks();
    GameFile::GetGameFileHandle()->readCSV_missles();
    GameFile::GetGameFileHandle()->readCSV_spells();
    GameFile::GetGameFileHandle()->readCSV_animations();
    GameFile::GetGameFileHandle()->readCSV_texts();
    GameFile::GetGameFileHandle()->readCSV_npclevels();
    GameFile::GetGameFileHandle()->readCSV_townhalllevels();
    GameFile::GetGameFileHandle()->readCSV_obstacles();
    GameFile::GetGameFileHandle()->readCSV_effects();
    GameFile::GetGameFileHandle()->readCSV_experiencelevels();
    //shop
    GameFile::GetGameFileHandle()->readCSV_shields();
    GameFile::GetGameFileHandle()->readCSV_resource_packs();
}

// 生成对象的模版数据
void CentralScene::initUnitClassesData(void)
{    
    GameData::basebuildlevel_t::const_iterator pos;
	for( pos= GameData::m_mapBuildingBaseData.begin(); pos != GameData::m_mapBuildingBaseData.end(); ++pos )
	{
        UnitClass unitclass;
        unitclass.ID = pos->second.ID;
        
		unitclass.speed = 0;
        unitclass.hp = unitclass.maxhp = pos->second.Hitpoints;
        unitclass.MaxStoredGold = pos->second.MaxStoredGold;
        unitclass.MaxStoredElixir = pos->second.MaxStoredElixir;
        unitclass.ResourceMax = pos->second.ResourceMax;
        
        unitclass.lv = pos->second.build_level;
        unitclass.TypeID = pos->second.building_TypeID;
        unitclass.Damage = pos->second.Damage;
        unitclass.AttackRange = pos->second.AttackRange / 100.f * BUILDINTBASEGRID_EDGE_LEN;
        unitclass.MinAttackRange = pos->second.MinAttackRange / 100.0f * BUILDINTBASEGRID_EDGE_LEN;
        unitclass.DamageRadius = pos->second.DamageRadius;
        unitclass.AttackSpeed = pos->second.AttackSpeed;
        unitclass.AirTargets = pos->second.AirTargets;
        unitclass.GroundTargets = pos->second.GroundTargets;
        unitclass.IsFlying = false;
        unitclass.offsetx = 0;
        unitclass.offsety = 0;

        unitclass.radius = pos->second.BuildingW;

        unitclass.height = 60;
        
        unitclass.action = -1;
        unitclass.hideHpbar = false;
        unitclass.camp = UNIT_CAMP_ENEMY;
        
        int key = pos->second.ID;
        GameData::AddUnitClassData(key,unitclass);
	}
    
    GameData::basepeople_t::const_iterator pos1;
	for( pos1= GameData::m_mapPeopleBaseData.begin(); pos1 != GameData::m_mapPeopleBaseData.end(); ++pos1 )
	{
        UnitClass unitclass;
        unitclass.ID = pos1->second.ID;
        
		unitclass.speed = pos1->second.Speed /100.0f * BUILDINTBASEGRID_EDGE_LEN;
        unitclass.hp = unitclass.maxhp = pos1->second.Hitpoints;
        unitclass.lv = pos1->second.Level;
        unitclass.TypeID = pos1->second.TypeID;
        unitclass.Damage = pos1->second.Damage;
        unitclass.DamageRadius = pos1->second.DamageRadius;
        unitclass.AttackSpeed = pos1->second.AttackSpeed;
        unitclass.AirTargets = pos1->second.AirTargets;
        unitclass.GroundTargets = pos1->second.GroundTargets;
        unitclass.IsFlying = pos1->second.IsFlying;
        unitclass.AttackRange = pos1->second.AttackRange / 100.f * BUILDINTBASEGRID_EDGE_LEN;
        unitclass.offsetx = 0;
        unitclass.offsety = 0;
        unitclass.radius = 5;
        unitclass.height = 16;
		unitclass.PreferedTargetBuilding = pos1->second.PreferedTargetBuilding;
        
        unitclass.action = -1;
        unitclass.hideHpbar = false;
        unitclass.camp = UNIT_CAMP_ARMY;
        
        int key = pos1->second.ID;
        GameData::AddUnitClassData(key,unitclass);
	}
}

// 载入音乐音效
void CentralScene::loadAllSoundEffect( void )
{
    SoundManage::GetSoundManageHandle()->preload_Effects();
}

void CentralScene::SetBattleMode( int battlemode, int battlemode_pvp)
{
    m_pCentralData->m_enBattleMode = (BATTLE_MODE)battlemode;
    m_pCentralData->m_enPVPMode = (BATTLE_MODE_PVP)battlemode_pvp;
}

void CentralScene::LoadSceneLayer(int mode)
{
	NavGraph::sharedNavGraph()->Reset();
	
	UnloadLayer();
    
	m_pCentralData->m_enCentralViewMode = (CENTRALVIEW_MODE)mode;
    
	if( m_pCentralData->m_enCentralViewMode == CENTRALVIEW_SELF)
	{
		m_pCentralLayer = CentralLayer::create();
		this->addChild( m_pCentralLayer ,100);  
        
        CCBAnimationManager *actionManager = NULL;
        
        m_pCentralUILayer = (CentralUILayer*)openTest(GAME_FILE_TRANSFORM("UI_Map",".ccbi").c_str(),"UI_Map",CentralUILayerLoader::loader(),&actionManager);

        this->addChild( m_pCentralUILayer ,200);
        m_pCentralUILayer->initUI();
        
        m_pCentralUILayer->setAnimationManager(actionManager);
		return;
    }

	if( m_pCentralData->m_enCentralViewMode == CENTRALVIEW_VISIT )
	{
		m_pCentralLayer = CentralLayer::create();
		this->addChild( m_pCentralLayer ,100);
        

        CCBAnimationManager *actionManager = NULL;
        
        m_pCentralUILayer =(CentralUILayer*)openTest(GAME_FILE_TRANSFORM("UI_Map",".ccbi").c_str(),"UI_Map",CentralUILayerLoader::loader(),&actionManager);
        
        this->addChild( m_pCentralUILayer ,200);
        
        m_pCentralUILayer->initUI();
		return;
    }

    if ( m_pCentralData->m_enCentralViewMode == CENTRALVIEW_BATTLE) 
	{
		if (BATTLE_MODE_PVP_REPLAY==m_pCentralData->m_enPVPMode)
		{
			m_pCentralLayer = CentralLayer::create();
			this->addChild( m_pCentralLayer ,100);
			
			m_pCentralLayer->LoadBattleReplayMap();
			m_pCentralLayer->m_enLoadProcess = CentralLayer::finish;
			
            CentralBattleReplayUILayerLoader* centralBattleReplayUILayerLoader = CentralBattleReplayUILayerLoader::loader();
            m_CentralBattleReplayUILayer = (CentralBattleReplayUILayer*)openTest(GAME_FILE_TRANSFORM("UI_BattleReplay",".ccbi").c_str(),"UI_BattleReplay",centralBattleReplayUILayerLoader);
            
            
            this->addChild(m_CentralBattleReplayUILayer,200);
			return;
		}
		
        m_pCentralLayer = CentralLayer::create();
		this->addChild( m_pCentralLayer ,100);
        
        
        // 加载场景内UI
        CentralPVPMapUILayerLoader* centralPvPMapUILayerLoader = CentralPVPMapUILayerLoader::loader();
        m_pCentralPVPMapUILayer = (CentralPVPMapUILayer*)openTest(GAME_FILE_TRANSFORM("UI_PVP_Map",".ccbi").c_str(),"UI_PVP_Map",centralPvPMapUILayerLoader);
        
        
        m_pCentralPVPMapUILayer->initCentralPVPMapUI();
        this->addChild(m_pCentralPVPMapUILayer,200);
		return;
    }
}

void CentralScene::UnloadLayer( void )
{
	this->removeAllChildrenWithCleanup(true);
	m_pCentralLayer = NULL;
    m_pCentralUILayer = NULL;
    m_pCentralShopUILayer = NULL;
    m_pCentralInfoUILayer = NULL;
    m_pCentralInfo2UILayer = NULL;
    m_pCentralPVPUILayer = NULL;
    m_pCentralPVPMapUILayer = NULL;
}

CCNode * CentralScene::openTest(const char * pCCBFileName, const char * pCCNodeName, cocos2d::extension::CCNodeLoader * pCCNodeLoader,CCBAnimationManager** animManager)
{
    //CCSprite* sprite = CCSprite::create("resource_480x320/00014.png");
    
    cocos2d::extension::CCNodeLoaderLibrary *ccNodeLoaderLibrary=cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    ccNodeLoaderLibrary->registerCCNodeLoader(pCCNodeName,pCCNodeLoader);
    cocos2d::extension::CCBReader *ccBReader=new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccBReader->autorelease();

    //CCNode * node = ccBReader->readNodeGraphFromFile(pCCBFileName,this,animManager);
    
    CCNode * node;
    
    if(animManager)
    {
        node = ccBReader->readNodeGraphFromFile(pCCBFileName,this,animManager);
    }
    else 
    {
        node = ccBReader->readNodeGraphFromFile(pCCBFileName,this);
    }
//    ccBReader->release();
    return node;
    
}




