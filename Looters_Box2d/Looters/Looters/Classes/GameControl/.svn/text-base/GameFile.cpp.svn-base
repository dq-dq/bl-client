#include "GameFile.h"
#include "GameControl.h"
#include "GameTool.h"
#include "GameDebug.h"


GameFile* m_gGameFile = NULL;
GameFile::GameFile()
{
    
}

GameFile::~GameFile()
{
    delete baseConfigDic;
    baseConfigDic = NULL;
}

GameFile* GameFile::GetGameFileHandle( void )
{
	if( m_gGameFile == NULL )
	{
		m_gGameFile = new GameFile();
	    if( !m_gGameFile->Init() )
		{
			delete m_gGameFile;
			m_gGameFile = NULL;
		}
	}
    
	return m_gGameFile;
}

void GameFile::ReleaseGameFile( void )
{
	if( m_gGameFile )
	{
		delete m_gGameFile;
		m_gGameFile = NULL;
	}
}

bool GameFile::Init( void )
{
    baseConfigDic = CCDictionary::create()->createWithContentsOfFile("BaseConfig.plist");
	return true;
}

string GameFile::GetLandServerIP( void )
{
	string IP;
    CCDictionary *landServerDir = (CCDictionary *)baseConfigDic->objectForKey("landServer");
    CCString *str = (CCString *)landServerDir->objectForKey("ServerIP");
    IP = str->m_sString;
    CCLog("IP      %s",IP.c_str());
	return IP;
}

int GameFile::GetLandServerPort( void )
{
	int Port;
    CCDictionary *landServerDir = (CCDictionary *)baseConfigDic->objectForKey("landServer");
    CCString *str = (CCString *)landServerDir->objectForKey("ServerPort");
    Port = atoi((str->m_sString).c_str());
    CCLog("Port       %d",Port);
	return Port;
}

string GameFile::GetVersionCode( void )
{
	string out;
    CCDictionary *landServerDir = (CCDictionary *)baseConfigDic->objectForKey("versionInfo");
    CCString *str = (CCString *)landServerDir->objectForKey("versionNumber");
    out = str->m_sString;
    CCLog("VersionCode       %s",out.c_str());
	return out;
}

bool GameFile::readCSV_buildlevel()
{
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("pro_buildings_level.csv");
    printf("\n path: %s \n",path);
    
    std::ifstream file ( path );
    std::string value;
    
    while ( file.good() )
    {  
        BaseBuildingLevelData buildlevelData;
        getline ( file, value, (char)13 );
        
        size_t offset = 0;
        
        size_t end = value.find(';', offset);
        string ID(value,offset,end-offset);
        Log__(ID);
        buildlevelData.ID = CommonResource::getIntFromString(ID.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string build_level(value,offset,end-offset);
        Log__(build_level);
        buildlevelData.build_level = CommonResource::getIntFromString(build_level.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string building_TypeID(value,offset,end-offset);
        Log__(building_TypeID);
        buildlevelData.building_TypeID = CommonResource::getIntFromString(building_TypeID.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Name(value,offset,end-offset);
        Log__(Name);
        buildlevelData.Name.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string SWF(value,offset,end-offset);
        Log__(SWF);
        buildlevelData.SWF.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string ExportName(value,offset,end-offset);
        Log__(ExportName);
        buildlevelData.ExportName.assign(value, offset, end-offset);
        offset = end + 1;

        end = value.find(';', offset);
        string ExportNameNpc(value,offset,end-offset);
        Log__(ExportNameNpc);
        buildlevelData.ExportNameNpc.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string ExportNameConstruction(value,offset,end-offset);
        Log__(ExportNameConstruction);
        buildlevelData.ExportNameConstruction.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string BuildTimeD(value,offset,end-offset);
        Log__(BuildTimeD);
        buildlevelData.BuildTimeD = CommonResource::getIntFromString(BuildTimeD.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string BuildTimeH(value,offset,end-offset);
        Log__(BuildTimeH);
        buildlevelData.BuildTimeH = CommonResource::getIntFromString(BuildTimeH.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string BuildTimeM(value,offset,end-offset);
        Log__(BuildTimeM);
        buildlevelData.BuildTimeM = CommonResource::getIntFromString(BuildTimeM.c_str());
        offset = end + 1;
        
        
        end = value.find(';', offset);
        string BuildResource(value,offset,end-offset);
        Log__(BuildResource);
        buildlevelData.BuildResource.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string BuildCost(value,offset,end-offset);
        Log__(BuildCost);
        buildlevelData.BuildCost = CommonResource::getIntFromString(BuildCost.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string TownHallLevel(value,offset,end-offset);
        Log__(TownHallLevel);
        buildlevelData.TownHallLevel = CommonResource::getIntFromString(TownHallLevel.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Width(value,offset,end-offset);
        Log__(Width);
        buildlevelData.Width = CommonResource::getIntFromString(Width.c_str());
        offset = end + 1;
        
        
        end = value.find(';', offset);
        string Height(value,offset,end-offset);
        Log__(Height);
        buildlevelData.Height = CommonResource::getIntFromString(Height.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Icon(value,offset,end-offset);
        Log__(Icon);
        buildlevelData.Icon.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string ExportNameBuildAnim(value,offset,end-offset);
        Log__(ExportNameBuildAnim);
        buildlevelData.ExportNameBuildAnim.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string MaxStoredGold(value,offset,end-offset);
        Log__(MaxStoredGold);
        buildlevelData.MaxStoredGold = CommonResource::getIntFromString(MaxStoredGold.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string MaxStoredElixir(value,offset,end-offset);
        Log__(MaxStoredElixir);
        buildlevelData.MaxStoredElixir = CommonResource::getIntFromString(MaxStoredElixir.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Bunker(value,offset,end-offset);
        Log__(Bunker);
        buildlevelData.Bunker = CommonResource::getBoolFromeString(Bunker.c_str());
        offset = end + 1;
        
        
        end = value.find(';', offset);
        string HousingSpace(value,offset,end-offset);
        Log__(HousingSpace);
        buildlevelData.HousingSpace = CommonResource::getIntFromString(HousingSpace.c_str());
        offset = end + 1;
        
        
        end = value.find(';', offset);
        string ProducesResource(value,offset,end-offset);
        Log__(ProducesResource);
        buildlevelData.ProducesResource.assign(value, offset, end-offset);
        offset = end + 1;
        
        
        end = value.find(';', offset);
        string ResourcePerHour(value,offset,end-offset);
        Log__(ResourcePerHour);
        buildlevelData.ResourcePerHour = CommonResource::getIntFromString(ResourcePerHour.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string ResourceMax(value,offset,end-offset);
        Log__(ResourceMax);
        buildlevelData.ResourceMax = CommonResource::getIntFromString(ResourceMax.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string UnitProduction(value,offset,end-offset);
        Log__(UnitProduction);
        buildlevelData.UnitProduction = CommonResource::getIntFromString(UnitProduction.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string UpgradesUnits(value,offset,end-offset);
        Log__(UpgradesUnits);
        buildlevelData.UpgradesUnits = CommonResource::getBoolFromeString(UpgradesUnits.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Hitpoints(value,offset,end-offset);
        Log__(Hitpoints);
        buildlevelData.Hitpoints = CommonResource::getIntFromString(Hitpoints.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string RegenTime(value,offset,end-offset);
        Log__(RegenTime);
        buildlevelData.RegenTime = CommonResource::getIntFromString(RegenTime.c_str());
        offset = end + 1;
        
        
        end = value.find(';', offset);
        string AttackRange(value,offset,end-offset);
        Log__(AttackRange);
        buildlevelData.AttackRange = CommonResource::getIntFromString(AttackRange.c_str());
        offset = end + 1;
        
        
        end = value.find(';', offset);
        string AttackSpeed(value,offset,end-offset);
        Log__(AttackSpeed);
        buildlevelData.AttackSpeed = CommonResource::getIntFromString(AttackSpeed.c_str());
        offset = end + 1;
        
        
        
        end = value.find(';', offset);
        string Damage(value,offset,end-offset);
        Log__(Damage);
        buildlevelData.Damage = CommonResource::getIntFromString(Damage.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string DestroyEffect(value,offset,end-offset);
        Log__(DestroyEffect);
        buildlevelData.DestroyEffect.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string AttackEffect(value,offset,end-offset);
        Log__(AttackEffect);
        buildlevelData.AttackEffect.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string HitEffect(value,offset,end-offset);
        Log__(HitEffect);
        buildlevelData.HitEffect.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string Projectile(value,offset,end-offset);
        Log__(Projectile);
        buildlevelData.Projectile.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string ExportNameDamaged(value,offset,end-offset);
        Log__(ExportNameDamaged);
        buildlevelData.ExportNameDamaged.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string BuildingW(value,offset,end-offset);
        Log__(BuildingW);
        buildlevelData.BuildingW = CommonResource::getIntFromString(BuildingW.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string BuildingH(value,offset,end-offset);
        Log__(BuildingH);
        buildlevelData.BuildingH = CommonResource::getIntFromString(BuildingH.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string ExportNameBase(value,offset,end-offset);
        Log__(ExportNameBase);
        buildlevelData.ExportNameBase.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string ExportNameBaseNpc(value,offset,end-offset);
        Log__(ExportNameBaseNpc);
        buildlevelData.ExportNameBaseNpc.assign(value, offset, end-offset);
        offset = end + 1;
        

        end = value.find(';', offset);
        string AirTargets(value,offset,end-offset);
        Log__(AirTargets);
        buildlevelData.AirTargets = CommonResource::getBoolFromeString(AirTargets.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string GroundTargets(value,offset,end-offset);
        Log__(GroundTargets);
        buildlevelData.GroundTargets = CommonResource::getBoolFromeString(GroundTargets.c_str());
        offset = end + 1;

        end = value.find(';', offset);
        string MinAttackRange(value,offset,end-offset);
        Log__(MinAttackRange);
        buildlevelData.MinAttackRange = CommonResource::getIntFromString(MinAttackRange.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string DamageRadius(value,offset,end-offset);
        Log__(DamageRadius);
        buildlevelData.DamageRadius = CommonResource::getIntFromString(DamageRadius.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string PushBack(value,offset,end-offset);
        Log__(PushBack);
        buildlevelData.PushBack = CommonResource::getBoolFromeString(PushBack.c_str());
        offset = end + 1;
        
//        end = value.find(';', offset);
//        string LoadAmmoEffect(value,offset,end-offset);
//        std::cout << LoadAmmoEffect<<"\n";
//        buildlevelData.LoadAmmoEffect.assign(value, offset, end-offset);
//        offset = end + 1;
//        
//        end = value.find(';', offset);
//        string ToggleAttackModeEffect(value,offset,end-offset);
//        std::cout << ToggleAttackModeEffect<<"\n";
//        buildlevelData.ToggleAttackModeEffect.assign(value, offset, end-offset);
//        offset = end + 1;
        
        end = value.find(';', offset);
        string PickUpEffect(value,offset,end-offset);
        Log__(PickUpEffect);
        buildlevelData.PickUpEffect.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string PlacingEffect(value,offset,end-offset);
        Log__(PlacingEffect);
        buildlevelData.PlacingEffect.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string CanNotSellLast(value,offset,end-offset);
        Log__(CanNotSellLast);
        buildlevelData.CanNotSellLast = CommonResource::getBoolFromeString(CanNotSellLast.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string DefenderCharacter(value,offset,end-offset);
        Log__(DefenderCharacter);
        buildlevelData.DefenderCharacter = CommonResource::getIntFromString(DefenderCharacter.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string DefenderCount(value,offset,end-offset);
        Log__(DefenderCount);
        buildlevelData.DefenderCount = CommonResource::getIntFromString(DefenderCount.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string DefenderZ(value,offset,end-offset);
        Log__(DefenderZ);
        buildlevelData.DefenderZ = CommonResource::getIntFromString(DefenderZ.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string DestructionXP(value,offset,end-offset);
        Log__(DestructionXP);
        buildlevelData.DestructionXP = CommonResource::getIntFromString(DestructionXP.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Locked(value,offset,end-offset);
        Log__(Locked);
        buildlevelData.Locked = CommonResource::getBoolFromeString(Locked.c_str());
        offset = end + 1;
        

        end = value.find(';', offset);
        string Hidden(value,offset,end-offset);
        Log__(Hidden);
        buildlevelData.Hidden = CommonResource::getBoolFromeString(Hidden.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string TriggerRadius(value,offset,end-offset);
        Log__(TriggerRadius);
        buildlevelData.TriggerRadius = CommonResource::getIntFromString(TriggerRadius.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string ExportNameTriggered(value,offset,end-offset);
        Log__(ExportNameTriggered);
        buildlevelData.ExportNameTriggered.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string AppearEffect(value,offset,end-offset);
        Log__(AppearEffect);
        buildlevelData.AppearEffect.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string ForgesSpells(value,offset,end-offset);
        Log__(ForgesSpells);
        buildlevelData.ForgesSpells = CommonResource::getBoolFromeString(ForgesSpells.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Text(value,offset,end-offset);
        Log__(Text);
        buildlevelData.Text.assign(value, offset, end-offset);
        offset = end + 1;
        

        string TextInfo(value,offset,end-offset);
        Log__(TextInfo);
        buildlevelData.TextInfo.assign(value, offset, end-offset);
        
        
        GameData::AddDataToBaseBuildingLevelData( buildlevelData.ID, buildlevelData );
    }
    return true;
}


bool GameFile::readCSV_characters()
{
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("characters.csv");
    printf("\n path: %s \n",path);
    
    std::ifstream file ( path );
    std::string value;
    
    while ( file.good() )
    {  
        BasePeopleData peopleData;
        getline ( file, value, (char)13 );
        
        size_t offset = 0;
        
        size_t end = value.find(';', offset);
        string ID(value,offset,end-offset);
        Log__(ID);
        peopleData.ID = CommonResource::getIntFromString(ID.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string TypeID(value,offset,end-offset);
        Log__(TypeID);
        peopleData.TypeID = CommonResource::getIntFromString(TypeID.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Level(value,offset,end-offset);
        Log__(Level);
        peopleData.Level = CommonResource::getIntFromString(Level.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Name(value,offset,end-offset);
        Log__(Name);
        peopleData.Name.assign(value, offset, end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string TID(value,offset,end-offset);
        Log__(TID);
        peopleData.TID.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string SWF(value,offset,end-offset);
        Log__(SWF);
        peopleData.SWF.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string HousingSpace(value,offset,end-offset);
        Log__(HousingSpace);
        peopleData.HousingSpace = CommonResource::getIntFromString(HousingSpace.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string BarrackLevel(value,offset,end-offset);
        Log__(BarrackLevel);
        peopleData.BarrackLevel = CommonResource::getIntFromString(BarrackLevel.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string LaboratoryLevel(value,offset,end-offset);
        Log__(LaboratoryLevel);
        peopleData.LaboratoryLevel = CommonResource::getIntFromString(LaboratoryLevel.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Speed(value,offset,end-offset);
        Log__(Speed);
        peopleData.Speed = CommonResource::getIntFromString(Speed.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Hitpoints(value,offset,end-offset);
        Log__(Hitpoints);
        peopleData.Hitpoints = CommonResource::getIntFromString(Hitpoints.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string TrainingTime(value,offset,end-offset);
        Log__(TrainingTime);
        peopleData.TrainingTime = CommonResource::getIntFromString(TrainingTime.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string TrainingResource(value,offset,end-offset);
        Log__(TrainingResource);
        peopleData.TrainingResource.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string TrainingCost(value,offset,end-offset);
        Log__(TrainingCost);
        peopleData.TrainingCost = CommonResource::getIntFromString(TrainingCost.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string UpgradeTimeH(value,offset,end-offset);
        Log__(UpgradeTimeH);
        peopleData.UpgradeTimeH = CommonResource::getIntFromString(UpgradeTimeH.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string UpgradeResource(value,offset,end-offset);
        Log__(UpgradeResource);
        peopleData.UpgradeResource.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string UpgradeCost(value,offset,end-offset);
        Log__(UpgradeCost);
        peopleData.UpgradeCost = CommonResource::getIntFromString(UpgradeCost.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string AttackRange(value,offset,end-offset);
        Log__(AttackRange);
        peopleData.AttackRange = CommonResource::getIntFromString(AttackRange.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string AttackSpeed(value,offset,end-offset);
        Log__(AttackSpeed);
        peopleData.AttackSpeed = CommonResource::getIntFromString(AttackSpeed.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Damage(value,offset,end-offset);
        Log__(Damage);
        peopleData.Damage = CommonResource::getIntFromString(Damage.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string PreferedTargetDamageMod(value,offset,end-offset);
        Log__(PreferedTargetDamageMod);
        peopleData.PreferedTargetDamageMod = CommonResource::getIntFromString(PreferedTargetDamageMod.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string DamageRadius(value,offset,end-offset);
        Log__(DamageRadius);
        peopleData.DamageRadius = CommonResource::getIntFromString(DamageRadius.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string IconSWF(value,offset,end-offset);
        Log__(IconSWF);
        peopleData.IconSWF.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string IconExportName(value,offset,end-offset);
        Log__(IconExportName);
        peopleData.IconExportName.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string BigPicture(value,offset,end-offset);
        Log__(BigPicture);
        peopleData.BigPicture.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string Projectile(value,offset,end-offset);
        Log__(Projectile);
        peopleData.Projectile.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string PreferedTargetBuilding(value,offset,end-offset);
        Log__(PreferedTargetBuilding);
        peopleData.PreferedTargetBuilding = CommonResource::getIntFromString(PreferedTargetBuilding.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string DeployEffect(value,offset,end-offset);
        Log__(DeployEffect);
        peopleData.DeployEffect.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string AttackEffect(value,offset,end-offset);
        Log__(AttackEffect);
        peopleData.AttackEffect.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string HitEffect(value,offset,end-offset);
        Log__(HitEffect);
        peopleData.HitEffect.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string IsFlying(value,offset,end-offset);
        Log__(IsFlying);
        peopleData.IsFlying = CommonResource::getBoolFromeString(IsFlying.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string AirTargets(value,offset,end-offset);
        Log__(AirTargets);
        peopleData.AirTargets = CommonResource::getBoolFromeString(AirTargets.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string GroundTargets(value,offset,end-offset);
        Log__(GroundTargets);
        peopleData.GroundTargets = CommonResource::getBoolFromeString(GroundTargets.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string AttackCount(value,offset,end-offset);
        Log__(AttackCount);
        peopleData.AttackCount = CommonResource::getIntFromString(AttackCount.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string DieEffect(value,offset,end-offset);
        Log__(DieEffect);
        peopleData.DieEffect.assign(value,offset,end-offset);
        offset = end + 1;
        
        string Animation(value,offset,value.size()-offset);
        Log__(Animation);
        peopleData.Animation.assign(value,offset,value.size()-offset);
        
        GameData::AddDataToBasePeopleData( peopleData.ID, peopleData );
    }
    return true;
}

bool GameFile::readCSV_attacks()
{
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("attacks.csv");
    printf("\n path: %s \n",path);
    
    std::ifstream file ( path );
    std::string value;
    
    while ( file.good() )
    {  
        AttackData attackData;
        getline ( file, value, (char)13 );
        
        size_t offset = 0;
        
        size_t end = value.find(';', offset);
        string AttackName(value,offset,end-offset);
        Log__(AttackName);
        attackData.AttackName.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string UnitType(value,offset,end-offset);
        Log__(UnitType);
        attackData.UnitType = CommonResource::getIntFromString(UnitType.c_str());
        offset = end + 1;

        end = value.find(';', offset);
        string CheckRange(value,offset,end-offset);
        Log__(CheckRange);
        attackData.CheckRange = CommonResource::getIntFromString(CheckRange.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string AtackAni(value,offset,end-offset);
        Log__(AtackAni);
        attackData.AtackAni = CommonResource::getBoolFromeString(AtackAni.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string DmgType(value,offset,end-offset);
        Log__(DmgType);
        attackData.DmgType = CommonResource::getIntFromString(DmgType.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string IsMissle(value,offset,end-offset);
        Log__(IsMissle);
        attackData.IsMissle = CommonResource::getBoolFromeString(IsMissle.c_str());
        offset = end + 1;
        
        string MissleID(value,offset,value.size()-offset);
        Log__(MissleID);
        attackData.MissleID = CommonResource::getIntFromString(MissleID.c_str());
        
        GameData::AddDataToBaseAttackData(attackData.AttackName, attackData);
    }
    return true;
}

bool GameFile::readCSV_missles()
{
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("missles.csv");
    printf("\n path: %s \n",path);
    
    std::ifstream file ( path );
    std::string value;
    
    while ( file.good() )
    {  
        Cmd_Missle missleData;
        getline ( file, value, (char)13 );
        
        size_t offset = 0;
        
        size_t end = value.find(';', offset);
        string ID(value,offset,end-offset);
        Log__(ID);
        missleData.ID = CommonResource::getIntFromString(ID.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string AnimName(value,offset,end-offset);
        Log__(AnimName);
        missleData.AnimName.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string ActionID(value,offset,end-offset);
        Log__(ActionID);
        missleData.ActionID.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string Ofsx(value,offset,end-offset);
        Log__(Ofsx);
        missleData.Ofsx = CommonResource::getIntFromString(Ofsx.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Ofsy(value,offset,end-offset);
        Log__(Ofsy);
        missleData.Ofsy = CommonResource::getIntFromString(Ofsy.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Ofsh(value,offset,end-offset);
        Log__(Ofsh);
        missleData.Ofsh = CommonResource::getIntFromString(Ofsh.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Locus_type(value,offset,end-offset);
        Log__(Locus_type);
        missleData.Locus_type = CommonResource::getIntFromString(Locus_type.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Speed(value,offset,end-offset);
        Log__(Speed);
        missleData.Speed = CommonResource::getFloatFromString(Speed.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Gravity(value,offset,end-offset);
        Log__(Gravity);
        missleData.Gravity = CommonResource::getIntFromString(Gravity.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Rottype(value,offset,end-offset);
        Log__(Rottype);
        missleData.Rottype = CommonResource::getIntFromString(Rottype.c_str());
        offset = end + 1;
        
        string Isfollow(value,offset,value.size()-offset);
        Log__(Isfollow);
        missleData.Isfollow = CommonResource::getIntFromString(Isfollow.c_str());
        
        GameData::AddDataToBaseMissleData(missleData.ID, missleData);
    }
    return true;
}

bool GameFile::readCSV_spells()
{
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("spells.csv");
    printf("\n path: %s \n",path);
    
    std::ifstream file ( path );
    std::string value;
    
    while ( file.good() )
    {  
        BaseSpellData spellData;
        getline ( file, value, (char)13 );
        
        size_t offset = 0;
        
        size_t end = value.find(';', offset);
        string ID(value,offset,end-offset);
        Log__(ID);
        spellData.ID = CommonResource::getIntFromString(ID.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string ID_Type(value,offset,end-offset);
        Log__(ID_Type);
        spellData.ID_Type = CommonResource::getIntFromString(ID_Type.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Level(value,offset,end-offset);
        Log__(Level);
        spellData.Level = CommonResource::getIntFromString(Level.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Name(value,offset,end-offset);
        Log__(Name);
        spellData.Name.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string TID(value,offset,end-offset);
        Log__(TID);
        spellData.TID.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string InfoTID(value,offset,end-offset);
        Log__(InfoTID);
        spellData.InfoTID.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string SpellForgeLevel(value,offset,end-offset);
        Log__(SpellForgeLevel);
        spellData.SpellForgeLevel = CommonResource::getIntFromString(SpellForgeLevel.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string LaboratoryLevel(value,offset,end-offset);
        Log__(LaboratoryLevel);
        spellData.LaboratoryLevel = CommonResource::getIntFromString(LaboratoryLevel.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string TrainingResource(value,offset,end-offset);
        Log__(TrainingResource);
        spellData.TrainingResource.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string TrainingCost(value,offset,end-offset);
        Log__(TrainingCost);
        spellData.TrainingCost = CommonResource::getIntFromString(TrainingCost.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string HousingSpace(value,offset,end-offset);
        Log__(HousingSpace);
        spellData.HousingSpace = CommonResource::getIntFromString(HousingSpace.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string TrainingTime(value,offset,end-offset);
        Log__(TrainingTime);
        spellData.TrainingTime = CommonResource::getIntFromString(TrainingTime.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string DeployTimeMS(value,offset,end-offset);
        Log__(DeployTimeMS);
        spellData.DeployTimeMS = CommonResource::getIntFromString(DeployTimeMS.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string ChargingTimeMS(value,offset,end-offset);
        Log__(ChargingTimeMS);
        spellData.ChargingTimeMS = CommonResource::getIntFromString(ChargingTimeMS.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string HitTimeMS(value,offset,end-offset);
        Log__(HitTimeMS);
        spellData.HitTimeMS = CommonResource::getIntFromString(HitTimeMS.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string CooldownS(value,offset,end-offset);
        Log__(CooldownS);
        spellData.CooldownS = CommonResource::getIntFromString(CooldownS.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string UpgradeTimeH(value,offset,end-offset);
        Log__(UpgradeTimeH);
        spellData.UpgradeTimeH = CommonResource::getIntFromString(UpgradeTimeH.c_str());
        offset = end + 1;
        
        
        end = value.find(';', offset);
        string UpgradeResource(value,offset,end-offset);
        Log__(UpgradeResource);
        spellData.UpgradeResource.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string UpgradeCost(value,offset,end-offset);
        Log__(UpgradeCost);
        spellData.UpgradeCost = CommonResource::getIntFromString(UpgradeCost.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string BoostTimeMS(value,offset,end-offset);
        Log__(BoostTimeMS);
        spellData.BoostTimeMS = CommonResource::getIntFromString(BoostTimeMS.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string SpeedBoost(value,offset,end-offset);
        Log__(SpeedBoost);
        spellData.SpeedBoost = CommonResource::getIntFromString(SpeedBoost.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string SpeedBoost2(value,offset,end-offset);
        Log__(SpeedBoost2);
        spellData.SpeedBoost2 = CommonResource::getIntFromString(SpeedBoost2.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string JumpHousingLimit(value,offset,end-offset);
        Log__(JumpHousingLimit);
        spellData.JumpHousingLimit = CommonResource::getIntFromString(JumpHousingLimit.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string JumpBoostMS(value,offset,end-offset);
        Log__(JumpBoostMS);
        spellData.JumpBoostMS = CommonResource::getIntFromString(JumpBoostMS.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string DamageBoostPercent(value,offset,end-offset);
        Log__(DamageBoostPercent);
        spellData.DamageBoostPercent = CommonResource::getIntFromString(DamageBoostPercent.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Damage(value,offset,end-offset);
        Log__(Damage);
        spellData.Damage = CommonResource::getIntFromString(Damage.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Radius(value,offset,end-offset);
        Log__(Radius);
        spellData.Radius = CommonResource::getIntFromString(Radius.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string NumberOfHits(value,offset,end-offset);
        Log__(NumberOfHits);
        spellData.NumberOfHits = CommonResource::getIntFromString(NumberOfHits.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string RandomRadius(value,offset,end-offset);
        Log__(RandomRadius);
        spellData.RandomRadius = CommonResource::getIntFromString(RandomRadius.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string TimeBetweenHitsMS(value,offset,end-offset);
        Log__(TimeBetweenHitsMS);
        spellData.TimeBetweenHitsMS = CommonResource::getIntFromString(TimeBetweenHitsMS.c_str());
        offset = end + 1;
        
        
        end = value.find(';', offset);
        string IconSWF(value,offset,end-offset);
        Log__(IconSWF);
        spellData.IconSWF.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string IconExportName(value,offset,end-offset);
        Log__(IconExportName);
        spellData.IconExportName.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string BigPicture(value,offset,end-offset);
        Log__(BigPicture);
        spellData.BigPicture.assign(value,offset,end-offset);
        offset = end + 1;
        
        
        end = value.find(';', offset);
        string PreDeployEffect(value,offset,end-offset);
        Log__(PreDeployEffect);
        spellData.PreDeployEffect.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string DeployEffect(value,offset,end-offset);
        Log__(DeployEffect);
        spellData.DeployEffect.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string DeployEffect2(value,offset,end-offset);
        Log__(DeployEffect2);
        spellData.DeployEffect2.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string ChargingEffect(value,offset,end-offset);
        Log__(ChargingEffect);
        spellData.ChargingEffect.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string HitEffect(value,offset,end-offset);
        Log__(HitEffect);
        spellData.HitEffect.assign(value,offset,end-offset);
        offset = end + 1;
        
        string RandomRadiusAffectsOnlyGfx(value,offset,value.size()-offset);
        Log__(RandomRadiusAffectsOnlyGfx);
        spellData.RandomRadiusAffectsOnlyGfx = CommonResource::getBoolFromeString(RandomRadiusAffectsOnlyGfx.c_str());
        
        GameData::AddDataToBaseSpellData(spellData.ID, spellData);
    }
    return true;
}
bool GameFile::readCSV_animations()
{
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("animations.csv");
    printf("\n path: %s \n",path);
    
    std::ifstream file ( path );
    std::string value;
    
    while ( file.good() )
    {  
        BaseAnimationData animationData;
        getline ( file, value, (char)13 );
        
        size_t offset = 0;
        
        size_t end = value.find(';', offset);
        string AnimName(value,offset,end-offset);
        Log__(AnimName);
        offset = end + 1;
        
        getline ( file, value, (char)13 );
        getline ( file, value, (char)13 );

        while (true) {
            getline ( file, value, (char)13 );
            ActionData actionData;
            size_t offset = 0;
            
            size_t end = value.find(';', offset);
            offset = end + 1;
            
            
            end = value.find(';', offset);
            string Name(value,offset,end-offset);
            Log__(Name);
            actionData.Name.assign(value,offset,end-offset);
            offset = end + 1;
            
            end = value.find(';', offset);
            string HasDirections(value,offset,end-offset);
            Log__(HasDirections);
            actionData.HasDirections = CommonResource::getBoolFromeString(HasDirections.c_str());
            offset = end + 1;
            
            end = value.find(';', offset);
            string ActionFrame(value,offset,end-offset);
            Log__(ActionFrame);
            actionData.ActionFrame = CommonResource::getIntFromString(ActionFrame.c_str());
            offset = end + 1;
            
            end = value.find(';', offset);
            string ExportName(value,offset,end-offset);
            Log__(ExportName);
            actionData.ExportName.assign(value,offset,end-offset);
            offset = end + 1;
            
            string Looping(value,offset,value.size()-offset);
            Log__(Looping);
            actionData.Looping = CommonResource::getBoolFromeString(Looping.c_str());
            
            animationData.animData.insert(pair<string,const ActionData>(actionData.Name,actionData));
            
            if (actionData.Name == "die") {
                break;
            }
        }
        

        
        GameData::AddDataToBaseAnimationData(AnimName, animationData);
    }
    
    return true;
}

bool GameFile::readCSV_texts(){
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("texts.csv");
    printf("\n path: %s \n",path);
    
    std::ifstream file ( path );
    std::string value;
    
    while ( file.good() )
    {  
        TextInfo textData;
        getline ( file, value, (char)13 );
        
        size_t offset = 0;
        
        size_t end = value.find(';', offset);
        string TID(value,offset,end-offset);
        Log__(TID);
        textData.TID.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string TEXT_EN(value,offset,end-offset);
        Log__(TEXT_EN);
        textData.TEXT_EN.assign(value,offset,end-offset);
        offset = end + 1;
        
        string TEXT_CN(value,offset,value.size()-offset);
        Log__(TEXT_CN);
        textData.TEXT_CN.assign(value,offset,value.size()-offset);
        
        GameData::AddDataToBaseTextData(textData.TID, textData);
    }
    return true;
}

bool GameFile::readCSV_npclevels()
{
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("npcs.csv");
    printf("\n path: %s \n",path);
    
    std::ifstream file ( path );
    std::string value;
    
    while ( file.good() )
    {  
        NPCLevelData npcLevelData;
        getline ( file, value, (char)13 );
        
        size_t offset = 0;
        
        size_t end = value.find(';', offset);
        string Name(value,offset,end-offset);
        Log__(Name);
        npcLevelData.Name.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string MapInstanceName(value,offset,end-offset);
        Log__(MapInstanceName);
        npcLevelData.MapInstanceName.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string MapDependencies(value,offset,end-offset);
        Log__(MapDependencies);
        npcLevelData.MapDependencies.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string TID(value,offset,end-offset);
        Log__(TID);
        npcLevelData.TID.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string ExpLevel(value,offset,end-offset);
        Log__(ExpLevel);
        npcLevelData.ExpLevel = CommonResource::getIntFromString(ExpLevel.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string UnitType(value,offset,end-offset);
        Log__(UnitType);
        npcLevelData.UnitType.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string UnitCount(value,offset,end-offset);
        Log__(UnitCount);
        npcLevelData.UnitCount = CommonResource::getIntFromString(UnitCount.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string LevelFile(value,offset,end-offset);
        Log__(LevelFile);
        npcLevelData.LevelFile.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string Gold(value,offset,end-offset);
        Log__(Gold);
        npcLevelData.Gold = CommonResource::getIntFromString(Gold.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Elixir(value,offset,end-offset);
        Log__(Elixir);
        npcLevelData.Elixir = CommonResource::getIntFromString(Elixir.c_str());
        offset = end + 1;
        
        
        string AlwaysUnlocked(value,offset,value.size()-offset);
        Log__(AlwaysUnlocked);
        npcLevelData.AlwaysUnlocked = CommonResource::getBoolFromeString(AlwaysUnlocked.c_str());

        GameData::AddDataToBaseNpcLevelData(npcLevelData.Name, npcLevelData);
    }
    return true;
}

bool GameFile::readCSV_townhalllevels()
{
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("townhall_levels.csv");
    printf("\n path: %s \n",path);
    
    std::ifstream file ( path );
    std::string value;
    
    while ( file.good() )
    {  
        TownHallLevelsData townHallLevelData;
        getline ( file, value, (char)13 );
        
        size_t offset = 0;
        
        size_t end = value.find(';', offset);
        string Level(value,offset,end-offset);
        Log__(Level);
        townHallLevelData.Level = CommonResource::getIntFromString(Level.c_str());        
        offset = end + 1;
        
        end = value.find(';', offset);
        string AttackCost(value,offset,end-offset);
        Log__(AttackCost);
        townHallLevelData.AttackCost = CommonResource::getIntFromString(AttackCost.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string TroopHousing(value,offset,end-offset);
        Log__(TroopHousing);
        townHallLevelData.TroopHousing = CommonResource::getIntFromString(TroopHousing.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string ElixirStorage(value,offset,end-offset);
        Log__(ElixirStorage);
        townHallLevelData.ElixirStorage = CommonResource::getIntFromString(ElixirStorage.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string GoldStorage(value,offset,end-offset);
        Log__(GoldStorage);
        townHallLevelData.GoldStorage = CommonResource::getIntFromString(GoldStorage.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string ElixirPump(value,offset,end-offset);
        Log__(ElixirPump);
        townHallLevelData.ElixirPump = CommonResource::getIntFromString(ElixirPump.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string GoldMine(value,offset,end-offset);
        Log__(GoldMine);
        townHallLevelData.GoldMine = CommonResource::getIntFromString(GoldMine.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Barrack(value,offset,end-offset);
        Log__(Barrack);
        townHallLevelData.Barrack = CommonResource::getIntFromString(Barrack.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Cannon(value,offset,end-offset);
        Log__(Cannon);
        townHallLevelData.Cannon = CommonResource::getIntFromString(Cannon.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Wall(value,offset,end-offset);
        Log__(Wall);
        townHallLevelData.Wall = CommonResource::getIntFromString(Wall.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string ArcherTower(value,offset,end-offset);
        Log__(ArcherTower);
        townHallLevelData.ArcherTower = CommonResource::getIntFromString(ArcherTower.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string WizardTower(value,offset,end-offset);
        Log__(WizardTower);
        townHallLevelData.WizardTower = CommonResource::getIntFromString(WizardTower.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string AirDefense(value,offset,end-offset);
        Log__(AirDefense);
        townHallLevelData.AirDefense = CommonResource::getIntFromString(AirDefense.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Mortar(value,offset,end-offset);
        Log__(Mortar);
        townHallLevelData.Mortar = CommonResource::getIntFromString(Mortar.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string AllianceCastle(value,offset,end-offset);
        Log__(AllianceCastle);
        townHallLevelData.AllianceCastle = CommonResource::getIntFromString(AllianceCastle.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Ejector(value,offset,end-offset);
        Log__(Ejector);
        townHallLevelData.Ejector = CommonResource::getIntFromString(Ejector.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Superbomb(value,offset,end-offset);
        Log__(Superbomb);
        townHallLevelData.Superbomb = CommonResource::getIntFromString(Superbomb.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Mine(value,offset,end-offset);
        Log__(Mine);
        townHallLevelData.Mine = CommonResource::getIntFromString(Mine.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string WorkerBuilding(value,offset,end-offset);
        Log__(WorkerBuilding);
        townHallLevelData.WorkerBuilding = CommonResource::getIntFromString(WorkerBuilding.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Laboratory(value,offset,end-offset);
        Log__(Laboratory);
        townHallLevelData.Laboratory = CommonResource::getIntFromString(Laboratory.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Communicationsmast(value,offset,end-offset);
        Log__(Communicationsmast);
        townHallLevelData.Communicationsmast = CommonResource::getIntFromString(Communicationsmast.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string TeslaTower(value,offset,end-offset);
        Log__(TeslaTower);
        townHallLevelData.TeslaTower = CommonResource::getIntFromString(TeslaTower.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string SpellForge(value,offset,end-offset);
        Log__(SpellForge);
        townHallLevelData.SpellForge = CommonResource::getIntFromString(SpellForge.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Bow(value,offset,end-offset);
        Log__(Bow);
        townHallLevelData.Bow = CommonResource::getIntFromString(Bow.c_str());
        offset = end + 1;
        
        string Halloweenbomb(value,offset,value.size()-offset);
        Log__(Halloweenbomb);
        townHallLevelData.Halloweenbomb = CommonResource::getIntFromString(Halloweenbomb.c_str());
        
        GameData::AddDataToBaseTownHallLevelsData(townHallLevelData.Level, townHallLevelData);
    }
    return true;
}

bool GameFile::readCSV_obstacles()
{
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("obstacles.csv");
    printf("\n path: %s \n",path);
    
    std::ifstream file ( path );
    std::string value;
    
    while ( file.good() )
    {  
        ObstaclesData obstacleData;
        getline ( file, value, (char)13 );
        
        size_t offset = 0;
        
        
        size_t end = value.find(';', offset);
        string ID(value,offset,end-offset);
        Log__(ID);
        obstacleData.ID = CommonResource::getIntFromString(ID.c_str());        
        offset = end + 1;
        
        end = value.find(';', offset);
        string TypeID(value,offset,end-offset);
        Log__(TypeID);
        obstacleData.TypeID = CommonResource::getIntFromString(TypeID.c_str());        
        offset = end + 1;
        
        end = value.find(';', offset);
        string Name(value,offset,end-offset);
        Log__(Name);
        obstacleData.Name.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string TID(value,offset,end-offset);
        Log__(TID);
        obstacleData.TID.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string SWF(value,offset,end-offset);
        Log__(SWF);
        obstacleData.SWF.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string ExportName(value,offset,end-offset);
        Log__(ExportName);
        obstacleData.ExportName.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string ExportNameBase(value,offset,end-offset);
        Log__(ExportNameBase);
        obstacleData.ExportNameBase.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string ExportNameBaseNpc(value,offset,end-offset);
        Log__(ExportNameBaseNpc);
        obstacleData.ExportNameBaseNpc.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string ClearTimeSeconds(value,offset,end-offset);
        Log__(ClearTimeSeconds);
        obstacleData.ClearTimeSeconds = CommonResource::getIntFromString(ClearTimeSeconds.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Width(value,offset,end-offset);
        Log__(Width);
        obstacleData.Width = CommonResource::getIntFromString(Width.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Height(value,offset,end-offset);
        Log__(Height);
        obstacleData.Height = CommonResource::getIntFromString(Height.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Resource(value,offset,end-offset);
        Log__(Resource);
        obstacleData.Resource = CommonResource::getIntFromString(Resource.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string Passable(value,offset,end-offset);
        Log__(Passable);
        obstacleData.Passable = CommonResource::getBoolFromeString(Passable.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string ClearResource(value,offset,end-offset);
        Log__(ClearResource);
        obstacleData.ClearResource.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string ClearCost(value,offset,end-offset);
        Log__(ClearCost);
        obstacleData.ClearCost = CommonResource::getIntFromString(ClearCost.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string LootResource(value,offset,end-offset);
        Log__(LootResource);
        obstacleData.LootResource.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string LootCount(value,offset,end-offset);
        Log__(LootCount);
        obstacleData.LootCount = CommonResource::getIntFromString(LootCount.c_str());
        offset = end + 1;
        
        end = value.find(';', offset);
        string ClearEffect(value,offset,end-offset);
        Log__(ClearEffect);
        obstacleData.ClearEffect.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string PickUpEffect(value,offset,end-offset);
        Log__(PickUpEffect);
        obstacleData.PickUpEffect.assign(value,offset,end-offset);
        offset = end + 1;

        string RespawnWeight(value,offset,value.size()-offset);
        Log__(RespawnWeight);
        obstacleData.RespawnWeight = CommonResource::getIntFromString(RespawnWeight.c_str());
        
        
        GameData::AddDataToBaseObstacleData(obstacleData.ID, obstacleData);
    }
    return true;
}
bool GameFile::readCSV_experiencelevels()
{
    
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("experience_levels.csv");
    printf("\n path: %s \n",path);
    
    std::ifstream file ( path );
    std::string value;
    
    while ( file.good() )
    {
        ExperienceLevels experienceLevels;
        getline ( file, value, (char)13 );
        
        size_t offset = 0;
        
        size_t end = value.find(';', offset);
        string Level(value,offset,end-offset);
        Log__(Level);
        if (!Level.empty()) {
            experienceLevels.ExperienceLevels_lv = CommonResource::getIntFromString(Level.c_str());
        }
        offset = end + 1;
        
        end = value.find(';', offset);
        string Exp(value,offset,end-offset);
        Log__(Exp);
        if (!Exp.empty()) {
            experienceLevels.ExperienceLevels_exp = CommonResource::getIntFromString(Exp.c_str());
        }
        offset = end + 1;
        
        
        string Exp1_5(value,offset,value.size()-offset);
        Log__(Exp1_5);
        if (!Exp1_5.empty()) {
            experienceLevels.ExperienceLevels_exp1_5 = CommonResource::getIntFromString(Exp1_5.c_str());
        }
        
        GameData::AddDataToBaseExperienceLevels(experienceLevels.ExperienceLevels_lv, experienceLevels);
    }
    return true;

}
bool GameFile::readCSV_effects()
{
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("effects.csv");
    printf("\n path: %s \n",path);
    
    std::ifstream file ( path );
    std::string value;
    
    while ( file.good() )
    {  
        EffectData effectData;
        getline ( file, value, (char)13 );
        
        size_t offset = 0;
        
        size_t end = value.find(';', offset);
        string Name(value,offset,end-offset);
        Log__(Name);
        effectData.Name.assign(value,offset,end-offset);
        offset = end + 1;
                
        end = value.find(';', offset);
        string SWF(value,offset,end-offset);
        Log__(SWF);
        if (!SWF.empty()) {
            effectData.SWF.assign(value,offset,end-offset);
        }
        offset = end + 1;
        
        end = value.find(';', offset);
        string ExportName(value,offset,end-offset);
        Log__(ExportName);
        if(!ExportName.empty()){
            effectData.ExportName.assign(value,offset,end-offset);
        }
        offset = end + 1;
        
        end = value.find(';', offset);
        string ParticleEmitter(value,offset,end-offset);
        Log__(ParticleEmitter);
        if(!ParticleEmitter.empty()){
            effectData.ParticleEmitter.assign(value,offset,end-offset);
        }
        offset = end + 1;
        
        end = value.find(';', offset);
        string Sound(value,offset,end-offset);
        Log__(Sound);
        if (!Sound.empty()) {
            size_t coffset = 0;

            size_t cend = Sound.find('/', coffset);
            string Name(Sound,coffset,cend-coffset);
            Log__(Name);
            coffset = cend + 1;
            
            string data(Sound,coffset,Sound.size()-coffset);
            Log__(data);
            effectData.Sound.assign(Sound,coffset,Sound.size()-coffset);
            
//            effectData.Sound.assign(value,offset,end-offset);
        }
        offset = end + 1;
        
        end = value.find(';', offset);
        string Volume(value,offset,end-offset);
        Log__(Volume);
        if (!Volume.empty()) {
            effectData.Volume = CommonResource::getIntFromString(Volume.c_str());
        }
        offset = end + 1;
        
        end = value.find(';', offset);
        string MinPitch(value,offset,end-offset);
        Log__(MinPitch);
        if (!MinPitch.empty()) {
            effectData.MinPitch = CommonResource::getIntFromString(MinPitch.c_str());
        }
        offset = end + 1;
        
        end = value.find(';', offset);
        string MaxPitch(value,offset,end-offset);
        Log__(MaxPitch);
        if (!MaxPitch.empty()) {
            effectData.MaxPitch = CommonResource::getIntFromString(MaxPitch.c_str());
        }
        offset = end + 1;
        
        end = value.find(';', offset);
        string LowEndSound(value,offset,end-offset);
        Log__(LowEndSound);
        if (!LowEndSound.empty()) {
             effectData.LowEndSound.assign(value,offset,end-offset);
        }
        offset = end + 1;
        
        end = value.find(';', offset);
        string LowEndVolume(value,offset,end-offset);
        Log__(LowEndVolume);
        if (!LowEndVolume.empty()) {
            effectData.LowEndVolume = CommonResource::getIntFromString(LowEndVolume.c_str());
        }
        offset = end + 1;
        
        end = value.find(';', offset);
        string LowEndMinPitch(value,offset,end-offset);
        Log__(LowEndMinPitch);
        if (!LowEndMinPitch.empty()) {
            effectData.LowEndMinPitch = CommonResource::getIntFromString(LowEndMinPitch.c_str());
        }
        offset = end + 1;
        
        string LowEndMaxPitch(value,offset,value.size()-offset);
        Log__(LowEndMaxPitch);
        if (!LowEndMaxPitch.empty()) {
            effectData.LowEndMaxPitch = CommonResource::getIntFromString(LowEndMaxPitch.c_str());
        }
        
        GameData::AddDataToBaseEffectData(effectData.Name, effectData);
    }
    return true;
}

bool GameFile::readCSV_shields(){
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("shields.csv");
    printf("\n path: %s \n",path);
    
    std::ifstream file ( path );
    std::string value;
    
    while ( file.good() )
    {  
        ShieldData shieldData;
        getline ( file, value, (char)13 );
        
        size_t offset = 0;
        
        
        size_t end = value.find(';', offset);
        string ID(value,offset,end-offset);
        Log__(ID);
        shieldData.ID = CommonResource::getIntFromString(ID.c_str());        
        offset = end + 1;
        
        end = value.find(';', offset);
        string Name(value,offset,end-offset);
        Log__(Name);
        shieldData.Name.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string TID(value,offset,end-offset);
        Log__(TID);
        shieldData.TID.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string InfoTID(value,offset,end-offset);
        Log__(InfoTID);
        shieldData.InfoTID.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string TimeH(value,offset,end-offset);
        Log__(TimeH);
        shieldData.TimeH = CommonResource::getIntFromString(TimeH.c_str());        
        offset = end + 1;
        
        end = value.find(';', offset);
        string Diamonds(value,offset,end-offset);
        Log__(Diamonds);
        shieldData.Diamonds = CommonResource::getIntFromString(Diamonds.c_str());        
        offset = end + 1;
        
        end = value.find(';', offset);
        string IconSWF(value,offset,end-offset);
        Log__(IconSWF);
        shieldData.IconSWF.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string IconExportName(value,offset,end-offset);
        Log__(IconExportName);
        shieldData.IconExportName.assign(value,offset,end-offset);
        offset = end + 1;
        
        
        string CooldownS(value,offset,value.size()-offset);
        Log__(CooldownS);
        shieldData.CooldownS = CommonResource::getIntFromString(CooldownS.c_str());

        GameData::AddShieldData(shieldData.ID, shieldData);
    }
    
    return true;
}

bool GameFile::readCSV_resource_packs()
{
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("resource_packs.csv");
    printf("\n path: %s \n",path);
    
    std::ifstream file ( path );
    std::string value;
    
    while ( file.good() )
    {  
        Resource_Pack packData;
        getline ( file, value, (char)13 );
        
        size_t offset = 0;
        
        
        size_t end = value.find(';', offset);
        string ID(value,offset,end-offset);
        Log__(ID);
        packData.ID = CommonResource::getIntFromString(ID.c_str());        
        offset = end + 1;
        
        end = value.find(';', offset);
        string Name(value,offset,end-offset);
        Log__(Name);
        packData.Name.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string TID(value,offset,end-offset);
        Log__(TID);
        packData.TID.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string Resource(value,offset,end-offset);
        Log__(Resource);
        packData.Resource.assign(value,offset,end-offset);
        offset = end + 1;
        
        end = value.find(';', offset);
        string CapacityPercentage(value,offset,end-offset);
        Log__(CapacityPercentage);
        packData.CapacityPercentage = CommonResource::getIntFromString(CapacityPercentage.c_str());        
        offset = end + 1;
        
        end = value.find(';', offset);
        string IconSWF(value,offset,end-offset);
        Log__(IconSWF);
        packData.IconSWF.assign(value,offset,end-offset);
        offset = end + 1;
        
        string IconExportName(value,offset,value.size()-offset);
        Log__(IconExportName);
        packData.IconExportName.assign(value,offset,value.size()-offset);
        
        GameData::AddResource_PackData(packData.ID, packData);
    }
    return true;
}

const char* GameFile::NodeGetText(TiXmlElement *element)
{
    TiXmlElement *dataInfo = element->FirstChildElement();

    const char* text = dataInfo->GetText(); 
    if (text) {
        return text;
    } else {
        return 0;
    }
}