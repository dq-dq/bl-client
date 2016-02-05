#include "GameData.h"
USING_NS_CC;


bool	isLoginGC;			// 是否登录 game center

//用户信息数据
UserData *GameData::m_stUserData = NULL;
//新手引导的数据
GameData::tutorial_t    GameData::m_mapTutorialData;
//建筑物基础数据
GameData::basebuildlevel_t GameData::m_mapBuildingBaseData;
//人物的基础数据
GameData::basepeople_t GameData::m_mapPeopleBaseData;
//attack模版数据
GameData::baseattack_t GameData::m_mapAttackBaseData;
//missle模版数据
GameData::basemissle_t GameData::m_mapMissleBaseData;
//对象模版数据
GameData::unitclass_t GameData::m_mapUnitClassBaseData;
//魔法基础数据
GameData::basespell_t GameData::m_mapSpellBaseData;
//动画基础数据
GameData::baseanimation_t GameData::m_mapAnimationBaseData;
//npc关卡基础数据
GameData::basenpclevel_t GameData::m_mapNpcLevelBaseData;
//townhallLevel等级限制基础数据
GameData::baseTownHallLevel_t GameData::m_mapTownHallLevelBaseData;
//场景障碍物基础数据
GameData::baseobstacle_t GameData::m_mapObstacleBaseData;
//特效基础数据
GameData::baseeffect_t GameData::m_mapEffectBaseData;
//等级基础数据
GameData::baseExperienceLevels GameData::m_mapExperienceLevelsBaseData;
//国际化语言
GameData::basetext_t GameData::m_mapTextBaseData;

GameData::baseshield_t   GameData::m_mapShieldBaseData;
GameData::baseResource_Pack_t GameData::m_mapResource_PackBaseData;

//加入一条新手引导
void GameData::AddDataToTutorialData( unsigned int tutorialID, TutorialData const& tutorialData )
{
	GameData::m_mapTutorialData.insert(pair<unsigned int,const TutorialData>(tutorialID,tutorialData));
}
//获取一条新手引导
const TutorialData* GetDataFromTutorialData( unsigned int tutorialID)
{
	GameData::tutorial_t::const_iterator iter = GameData::m_mapTutorialData.find( tutorialID );
	if( iter != GameData::m_mapTutorialData.end() )
	{
		return &(iter->second);
	}
	return 0;
}

//加入一条建筑基础数据
void GameData::AddDataToBaseBuildingLevelData( unsigned int buildingID, BaseBuildingLevelData const& buildingData )
{
	GameData::m_mapBuildingBaseData.insert(pair<unsigned int,const BaseBuildingLevelData>(buildingID,buildingData));
}
//获取一条建筑基础数据
const BaseBuildingLevelData* GameData::GetDataFromBaseBuildingLevelData( unsigned int typeID )
{  
	GameData::basebuildlevel_t::const_iterator iter = GameData::m_mapBuildingBaseData.find( typeID );
	if( iter != GameData::m_mapBuildingBaseData.end() )
	{
		return &(iter->second);
	}
	return 0;
}

//加入一条人物基础数据
void GameData::AddDataToBasePeopleData( unsigned int ID, BasePeopleData const& peopleData)
{
    GameData::m_mapPeopleBaseData.insert(pair<unsigned int,const BasePeopleData>(ID,peopleData));
}
//获取一条人物基础数据
const BasePeopleData* GameData::GetDataFromBasePeopleData( unsigned int ID)
{
    GameData::basepeople_t::const_iterator iter = GameData::m_mapPeopleBaseData.find( ID );
	if( iter != GameData::m_mapPeopleBaseData.end() )
	{
		return &(iter->second);
	}
	return 0;
}

//加入一条基础attack数据
void GameData::AddDataToBaseAttackData(string attackName, AttackData const & attackData)
{
	GameData::m_mapAttackBaseData.insert(pair<string,const AttackData>(attackName,attackData));
}
//获取一条基础attack数据
const AttackData* GameData::GetDataFromBaseAttackData(string attackName)
{
    GameData::baseattack_t::const_iterator iter = GameData::m_mapAttackBaseData.find( attackName );
	if( iter != GameData::m_mapAttackBaseData.end() )
	{
        return &(iter->second);
	}
    return 0;
}

//加入一条基础missle数据
void GameData::AddDataToBaseMissleData(unsigned int ID, Cmd_Missle const& missleData)
{
    GameData::m_mapMissleBaseData.insert(pair<unsigned int,const Cmd_Missle>(ID,missleData));
}
//获取一条基础missle数据
const Cmd_Missle* GameData::GetDataFromBaseMissleData( unsigned int ID)
{
    GameData::basemissle_t::const_iterator iter = GameData::m_mapMissleBaseData.find( ID );
	if( iter != GameData::m_mapMissleBaseData.end() )
	{
        return &(iter->second);
	}
    return 0;
}

//加入一条对象的模版数据
void GameData::AddUnitClassData(unsigned int unitID, UnitClass const& unitData )
{
    GameData::m_mapUnitClassBaseData.insert(pair<unsigned int,const UnitClass>(unitID,unitData));
}
//获取一条对象的模版数据
const UnitClass* GameData::GetUnitClassData(unsigned int unitID)
{
    GameData::unitclass_t::const_iterator iter = m_mapUnitClassBaseData.find( unitID );
	if( iter != m_mapUnitClassBaseData.end() )
	{
        return &(iter->second);
	}
	return 0;
}

//加入一条魔法基础数据
void GameData::AddDataToBaseSpellData(unsigned int ID, BaseSpellData const& spellData)
{
     GameData::m_mapSpellBaseData.insert(pair<unsigned int,const BaseSpellData>(ID,spellData));
}
//获取一条魔法基础数据
const BaseSpellData* GameData::GetDataFromBaseSpellData(unsigned int ID)
{
    GameData::basespell_t::const_iterator iter = m_mapSpellBaseData.find( ID );
	if( iter != m_mapSpellBaseData.end() )
	{
        return &(iter->second);
	}
	return 0;
}

//加入一条动画基础数据
void GameData::AddDataToBaseAnimationData(string ID, BaseAnimationData const& animationData)
{
    GameData::m_mapAnimationBaseData.insert(pair<string,const BaseAnimationData>(ID,animationData));
}
//获取一条动画基础数据
const BaseAnimationData* GameData::GetDataFromBaseAnimationData(string ID)
{
    GameData::baseanimation_t::const_iterator iter = m_mapAnimationBaseData.find( ID );
	if( iter != m_mapAnimationBaseData.end() )
	{
        return &(iter->second);
	}
	return 0;
}

//加入一条npc关卡基础数据
void GameData::AddDataToBaseNpcLevelData(string LevelName,NPCLevelData const& npclevelData)
{
    GameData::m_mapNpcLevelBaseData.insert(pair<string,const NPCLevelData>(LevelName,npclevelData));
}
//获取一条npc关卡基础数据
const NPCLevelData* GameData::GetDataFromBaseNpcLevelData(string LevelName)
{
    GameData::basenpclevel_t::const_iterator iter = m_mapNpcLevelBaseData.find( LevelName );
	if( iter != m_mapNpcLevelBaseData.end() )
	{
        return &(iter->second);
	}
	return 0;
}

//加入一条TownHallLevel限制基础数据
void GameData::AddDataToBaseTownHallLevelsData(int TownHallLevel,TownHallLevelsData const& townHallLevelData)
{
    GameData::m_mapTownHallLevelBaseData.insert(pair<int,const TownHallLevelsData>(TownHallLevel,townHallLevelData));
}
//获取一条TownHallLevel限制基础数据
const TownHallLevelsData* GameData::GetDataFromBaseTownHallLevelsData(int TownHallLevel)
{
    GameData::baseTownHallLevel_t::const_iterator iter = m_mapTownHallLevelBaseData.find( TownHallLevel );
	if( iter != m_mapTownHallLevelBaseData.end() )
	{
        return &(iter->second);
	}
	return 0;
}

//加入一条场景障碍物基础数据
void GameData::AddDataToBaseObstacleData(int ID,ObstaclesData const& obstacleData)
{
    GameData::m_mapObstacleBaseData.insert(pair<int,const ObstaclesData>(ID,obstacleData));
}
//获取一条场景障碍物基础数据
const ObstaclesData* GameData::GetDataFromBaseObstacleData(int ID)
{
    GameData::baseobstacle_t::const_iterator iter = m_mapObstacleBaseData.find( ID );
	if( iter != m_mapObstacleBaseData.end() )
	{
        return &(iter->second);
	}
	return 0;
}
//加入一条等级基础数据
void GameData::AddDataToBaseExperienceLevels(int Lv,ExperienceLevels const& experienceLevels)
{
    GameData::m_mapExperienceLevelsBaseData.insert(pair<int,const ExperienceLevels>(Lv,experienceLevels));
}
//获取一条等级基础数据
const ExperienceLevels* GameData::GetDataFromBaseExperienceLevels(int Lv)
{
    GameData::baseExperienceLevels::const_iterator iter = m_mapExperienceLevelsBaseData.find(Lv);
	if( iter != m_mapExperienceLevelsBaseData.end() )
	{
        return &(iter->second);
	}
	return 0;
    
    
}
//加入一条特效基础数据
void GameData::AddDataToBaseEffectData(string Name,EffectData const& effectData)
{
    GameData::m_mapEffectBaseData.insert(pair<string,const EffectData>(Name,effectData));
}
//获取一条特效基础数据
const EffectData* GameData::GetDataFromBaseEffectData(string Name)
{
    GameData::baseeffect_t::const_iterator iter = m_mapEffectBaseData.find( Name );
	if( iter != m_mapEffectBaseData.end() )
	{
        return &(iter->second);
	}
	return 0;
}

//添加一条文本信息
void GameData::AddDataToBaseTextData(string const& ID, TextInfo const& textData)
{
    GameData::m_mapTextBaseData.insert(pair<string,const TextInfo>(ID,textData));
}
//获取一条文本信息
const string* GameData::GetTextInfo(string const& ID)
{
    GameData::basetext_t::const_iterator iter = m_mapTextBaseData.find( ID );
	if( iter != m_mapTextBaseData.end() )
	{
        return &(iter->second.TEXT_EN);
	}
	return 0;
}

void GameData::AddShieldData(int ID, ShieldData const& shieldData)
{
    GameData::m_mapShieldBaseData.insert(pair<int,const ShieldData>(ID,shieldData));
}
const ShieldData* GameData::GetShieldData(int ID)
{
    GameData::baseshield_t::const_iterator iter = m_mapShieldBaseData.find( ID );
	if( iter != m_mapShieldBaseData.end() )
	{
        return &(iter->second);
	}
	return 0;
}

void GameData::AddResource_PackData(int ID, Resource_Pack const& resource_PackData)
{
    GameData::m_mapResource_PackBaseData.insert(pair<int,const Resource_Pack>(ID,resource_PackData));
}
const Resource_Pack* GameData::GetResource_PackData(int ID)
{
    GameData::baseResource_Pack_t::const_iterator iter = m_mapResource_PackBaseData.find( ID );
	if( iter != m_mapResource_PackBaseData.end() )
	{
        return &(iter->second);
	}
	return 0;
}