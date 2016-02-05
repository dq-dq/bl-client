/***************************************************************
 author:     wangning
 write time: 2012.10.20
 function:   游戏主数据
 ***************************************************************/

#ifndef Looters_GameData_h
#define Looters_GameData_h
#pragma once
#include "AttackData.h"
#include "UnitClass.h"
using namespace std;

#define MAPDATAPEDRATIO 1.0    //地图数据比例

#define PI 3.141592653
#define SKEWING_RADIAN 0.643501     // 地图倾斜弧度表示  atanf(3.0/4.0) 有正切值求弧度
#define SKEWING_ANGLE 36.869897     // 地图倾斜角度表示  (atanf(3.0/4.0)/M_PI)*180  有正切值求角度


#define MAX_accountIntervalTime 10 //流水账间隔
#define userDefault CCUserDefault::sharedUserDefault()

extern bool	isLoginGC;			// 是否登录 game center

//性别
enum GENDER
{
	GENDER_MALE = 0,//男
	GENDER_FEMALE = 1,//女
};

//特殊类型
enum UNIT_TYPE {
    UNIT_MISSLE_001 = 100000,  // missle unit类型ID
    UNIT_MISSLE_100 = 100100,
    UNIT_DECORATION_001 = 200000, //decoration unit 类型ID
    UNIT_DECORATION_100 = 200100,
	
	UNIT_NPC_BUILDING_WORKER_001 = 300000,
	
	UNIT_NPC_RESOURCE_WORKER_001 = 400000,
	
};


//人物类型
#define PEOPLE_TYPE_  1000
enum PEOPLE_TYPE
{
	PEOPLE_Barbarian = 1000,        //Barbarian   unit类型ID
    PEOPLE_Archer = 2000,           //Archer
    PEOPLE_Goblin = 3000,           //Goblin
    PEOPLE_Giant = 4000,            //Giant
    PEOPLE_WallBreaker = 5000,      //Wall Breaker
    PEOPLE_BalloonGoblin = 6000,    //Balloon Goblin
    PEOPLE_Wizard = 7000,           //Wizard
    PEOPLE_Healer = 8000,           //Healer
    PEOPLE_Dragon = 9000,           //Dragon
    PEOPLE_PEKKA = 10000,           //PEKKA  unit类型ID
};



//建筑类型
enum BUILDING_TYPE
{
	BUILDINGTYPE_NOGAIN = 0,            //基础建筑
	BUILDINGTYPE_ARMY = 1,              //军队
	BUILDINGTYPE_TOWNHALL = 100,        //大厅房子-- 主建筑
	BUILDINGTYPE_RESOURCE = 200,        //资源塔
    BUILDINGTYPE_DEFENSE = 300,         //防御
    BUILDINGTYPE_WALL = 400,            //墙--一类10级
    BUILDINGTYPE_WORKER = 500,          //工人-- 建造队列
    BUILDINGTYPE_NPC = 600,             //npc建筑
    BUILDINGTYPE_DILEI = 700,           //地雷
    BUILDINGTYPE_MAX = 999,  // 建筑最大
};




//军队建筑类型
enum ARMY_TYPE {
    ARMY_TROOPHOUSING = 1,              //队伍住房
    ARMY_BARRACK = 2,                   //建造士兵
    ARMY_LABORATORY = 3,                //兵种升级室
    ARMY_ALLIANCECASTLE = 4,            //工会城堡
    ARMY_SPELLFORGE = 5,                //技能制造
};

//防御建筑类型
enum DEFENSE_TYPE {
    DEFENSE_CANNON = 300,               //大炮
    DEFENSE_ARCHERTOWER = 301,          //射手塔
    DEFENSE_WIZARDTOWER = 302,          //巫师塔
    DEFENSE_AIRDEFENSE = 303,           //防空塔
    DEFENSE_MORTAR = 304,               //加农炮
    DEFENSE_TESLATOWER = 305,           //电磁塔
};

//资源建筑类型
enum RESOURCE_TYPE {
    RESOURCE_ELIXIRPUMP = 200,          //药水生产
    RESOURCE_ELIXIRSTORAGE = 201,       //药水存储
    RESOURCE_GOLDMINE = 202,            //金币生产
    RESOURCE_GOLDSTORAGE = 203,         //金币存储
};

//npc建筑类型
enum NPC_TYPE{
    NPC_COMMUNICATIONSMAST = 600,       //
    NPC_GOBLINMAINBUILDING = 601,       //
    NPC_GOBLINHUT = 602,                //
};

//资源种类
enum RESOURCE_GOODS_TYPE {
    RESOURCE_GOLD = 0,   // 金币
    RESOURCE_SOULUTION,  // 药水
    RESOURCE_EMERALD,    // 绿宝石
};

//建筑物状态
enum BUILDING_STATUS //0空闲状态 1建造状态
{
	BUILDING_FREE = 0,      //空闲状态
	BUILDING_BUILDING = 1,  //建造中
};

//魔法类型
enum MAGIC_TYPE{
    MAGIC_LightningStorm = 1,       //闪电风暴
    MAGIC_Treatment = 2,            //治疗
    MAGIC_Acceleration = 3,         //加速
    MAGIC_JumpWall = 4,             //跳墙
};



// 建筑物类型范围
static int const nogain_type_begin	=	BUILDINGTYPE_NOGAIN;
static int const nogain_type_end =			BUILDINGTYPE_NOGAIN;

static int const army_type_begin =		ARMY_TROOPHOUSING;
static int const army_type_end	=	ARMY_SPELLFORGE;

static int const townhall_type_begin	=	BUILDINGTYPE_TOWNHALL;
static int const townhall_type_end	=	BUILDINGTYPE_TOWNHALL;

static int const resource_type_begin =		RESOURCE_ELIXIRPUMP;
static int const resource_type_end	=	RESOURCE_GOLDSTORAGE;

static int const defense_type_begin	=	DEFENSE_CANNON;
static int const defense_type_end	=	DEFENSE_TESLATOWER;

static int const wall_type_begin	=	BUILDINGTYPE_WALL;
static int const wall_type_end	=	BUILDINGTYPE_WALL;

static int const walker_type_begin	=	BUILDINGTYPE_WORKER;
static int const walker_type_end	=	BUILDINGTYPE_WORKER;

static int const npc_type_begin	=	NPC_COMMUNICATIONSMAST;
static int const npc_type_end	=	NPC_GOBLINHUT;

// 角色类型范围
static int const people_type_begin = PEOPLE_Barbarian;
static int const people_type_end = PEOPLE_PEKKA;

// 导弹类型范围
static int const missle_type_begin	 = UNIT_MISSLE_001;
static int const missle_type_end	=	UNIT_MISSLE_100;

// 装饰类型范围
static int const decoration_type_begin =	UNIT_DECORATION_001;
static int const decoration_type_end	=	UNIT_DECORATION_100;


static int const npc_building_worker_begin = UNIT_NPC_BUILDING_WORKER_001;
static int const npc_building_worker_end = UNIT_NPC_BUILDING_WORKER_001;

static int const npc_resource_worker_begin = UNIT_NPC_RESOURCE_WORKER_001;
static int const npc_resource_worker_end = UNIT_NPC_RESOURCE_WORKER_001;

//用户数据信息 需存档
class UserData
{ 
public:
	unsigned int user_id;
	string local_area;//国家标识默认zh-cn
	string gamecenter_id;//邮件地址
	bool  is_createrole;//是否创建人物
	bool  is_registration;//是否注册账号
	string  used_language;//所用语言
	bool  is_openmusic;//是否开启声音
    bool  is_openwav;  //是否开启音效
	int   volume_bgmusic;//背景音乐音量
	int   volume_effectsound;//音效音量
    int   user_gold;        //玩家的金钱数
    int   user_potions;     //玩家药水数

	UserData(){
		user_id=1;
		is_createrole=false;
        is_registration=false;
        is_openmusic=true;
        is_openwav=true;
		volume_bgmusic=0;
        volume_effectsound=0;
        gamecenter_id = "";
	}
};

//新手引导的数据
class TutorialData
{  
public:
    int     m_iTutorialID;         //引导ID，唯一标识
    int     m_iGroupID;            //当前步所属教程组
    int     m_iNetxTutorialID;     //下一步引导的ID
    bool    m_bOpenAchievements;   //是否打开成就面板
    int     m_iRequiredBuildID;    //必需的建筑物ID
    int     m_iRequiredBuildLevel; //必需的建筑物等级
    int     m_iRequiredBuildCount; //必需的建筑物数量
    int     m_iDefendNpcID;        //防守NPC的ID
    int     m_iAttackNpcID;        //攻击NPC的ID
    bool    m_bAttackPlayer;       //是否攻击玩家
    bool    m_bChangeName;         //是否改名
    int     m_iNextStepDelay;      //到下一步的延迟
    bool    m_bShowMap;            //是否显示地图
    string  m_sTutorialText;       //引导文字(多国语言的索引)
    bool    m_bDarken;             //屏幕是否变暗
    int     m_iTextBoxType;        //对话框类型(0:tutorial_enemy、1:tutorial_friendly、2:tutorial_friendly_scared)
    int     m_iSpeechBubble;       //聊天泡泡的类型
    bool    m_bRightAlignTextBox;  //是否右对齐聊天框
    string  m_sButtonText;         //按钮上的文字(多国语言的索引)
    string  m_sTutorialMusic;      //音乐
    string  m_sTutorialSound;      //音效
    int     m_iRewardResourceID;   //奖励的资源ID
    int     m_iRewardResourceCount;//奖励的资源数量
    int     m_iRewardXP;           //奖励经验值
    int     m_iRewardTroopID;      //奖励的士兵ID
    int     m_iRewardTroopCount;   //奖励的士兵个数
    
    TutorialData(){
        m_iTutorialID = -1;
        m_iGroupID = -1;
        m_iNetxTutorialID = -1;
        m_bOpenAchievements = false;
        m_iRequiredBuildID = -1;
        m_iRequiredBuildLevel = -1;
        m_iRequiredBuildCount = -1;
        m_iDefendNpcID = -1;
        m_iAttackNpcID = -1;
        m_bAttackPlayer = false;
        m_bChangeName = false;
        m_iNextStepDelay = 0;
        m_bShowMap = false;
        m_sTutorialText = "";
        m_bDarken = false;
        m_iTextBoxType = -1;
        m_iSpeechBubble = -1;
        m_bRightAlignTextBox = false;
        m_sButtonText = "";
        m_sTutorialMusic = "";
        m_sTutorialSound = "";
        m_iRewardResourceID = -1;
        m_iRewardResourceCount = -1;
        m_iRewardXP = -1;
        m_iRewardTroopID = -1;
        m_iRewardTroopCount = -1;
    }
};


//建筑基础数据类
class BaseBuildingLevelData
{   
public:    
    int         ID;                         // 建筑唯一ID
    int         build_level;                // 建筑等级
    int         building_TypeID;            // 建筑类型ID
    string      Name;                       // 建筑名称
    string      SWF;                        //	动画
    string      ExportName;                 // 对应建筑图片
    string      ExportNameNpc;				// ？
    string      ExportNameConstruction;		// ？
    int         BuildTimeD;                 // 建造时间：天
    int         BuildTimeH;                 // 建造时间：小时
    int         BuildTimeM;                 // 建造时间：分钟
    string      BuildResource;              // 建造消耗资源种类
    int         BuildCost;                  // 建造消耗资源量
    int         TownHallLevel;              // 允许制造该建筑的主基地等级
    int         Width;                      // 占地范围宽
    int         Height;                     // 占地范围高
    string      Icon;                       // 图标
    string      ExportNameBuildAnim;		// 建造中动画
    int         MaxStoredGold;              // 储存金钱上限
    int         MaxStoredElixir;            // 储存水上限
    bool        Bunker;                     // 是否是堡垒
    int         HousingSpace;               // 提供存兵的人口数
    string      ProducesResource;           // 生产资源的种类
    int         ResourcePerHour;            // 每小时生产资源量
    int         ResourceMax;                // 生产后存储资源量的上限
    int         UnitProduction;             // 兵营队列中最多可以放多少人口
    bool        UpgradesUnits;              // 是否可以升级士兵
    int         Hitpoints;                  // 生命值
    int         RegenTime;                  // 被拆除后恢复所需的秒数
    int         AttackRange;                // 攻击的射程范围
    int         AttackSpeed;                // 攻击间隔
    int         Damage;                     // 攻击力    
    string      DestroyEffect;              // 被破坏后的特效
    string      AttackEffect;               // 攻击特效
    string      HitEffect;                  // 被击中的特效
    string      Projectile;                 // 对应的子弹类型
    string      ExportNameDamaged;          // 被破坏后对应的图片
    int         BuildingW;                  // 建筑的碰撞范围：宽
    int         BuildingH;                  // 建筑的碰撞范围：高
    string      ExportNameBase;             // 导出名称：基本
    string      ExportNameBaseNpc;          // 初始动画名称
    bool        AirTargets;                 // 攻击对空
    bool        GroundTargets;              // 攻击对地
    int         MinAttackRange;             // 盲区范围
    int         DamageRadius;               // 攻击的溅射范围
    bool        PushBack;                   // 攻击附带击退效果
//    string      LoadAmmoEffect;             // ?
//    string      ToggleAttackModeEffect;     // ?
    string      PickUpEffect;               // 拿起建筑时的效果
    string      PlacingEffect;              // 放置建筑时的效果
    bool        CanNotSellLast;             // 建筑是否可以出售
    int         DefenderCharacter;          // 防御塔上站立的士兵
    int         DefenderCount;              // 防御塔上站立的士兵的数量
    int         DefenderZ;                  // 防御塔上站立的士兵在Z轴上的偏移
    int         DestructionXP;              // 破坏后获得的经验
    bool        Locked;                     // 是否需要解锁
    bool        Hidden;                     // 是否隐身
    int         TriggerRadius;              // 触发范围
    string      ExportNameTriggered;        // 触发器名称
    string      AppearEffect;               // 出现消失特效
    bool        ForgesSpells;               // 可以生产魔法
    string      Text;                       // 建筑文本
    string      TextInfo;                   // 信息文本
    
    BaseBuildingLevelData(){
       
	}
};

// 角色的基础数据类
class BasePeopleData {
public:
    int         ID;             //id
    int         TypeID;         //人物类型ID
    int         Level;          //人物等级ID
    string      Name;           //名字
    string      TID;            //文本ID
    string      SWF;            //动画文件名称
    int         HousingSpace;   //所占人口
    int         BarrackLevel;   //解锁兵种需要的兵营等级
    int         LaboratoryLevel;//升级需要的科技建筑等级
    int         Speed;          //移动速度
    int         Hitpoints;      //生命值
    int         TrainingTime;   //造兵所需时间
    string      TrainingResource;//造兵消耗资源种类
    int         TrainingCost;   //造兵资源数量
    int         UpgradeTimeH;   //升级时间:小时
    string      UpgradeResource;//升级消耗资源的类型
    int         UpgradeCost;    //升级消耗资源的数量
    int         AttackRange;    //射程范围
    int         AttackSpeed;    //攻击间隔
    int         Damage;         //攻击力
    int         PreferedTargetDamageMod; //对特定类目标的攻击倍率
    int         DamageRadius;   //攻击的溅射范围
    string      IconSWF;        //对应UI
    string      IconExportName; //对应图标的名称 
    string      BigPicture;     //对应大尺寸图片
    string      Projectile;     //子弹对象
    int      PreferedTargetBuilding;//优先攻击的建筑类别
    string      DeployEffect;   //放入地图时的特效
    string      AttackEffect;   //攻击效果
    string      HitEffect;      //受击效果
    bool        IsFlying;       //是否为飞行单位
    bool        AirTargets;     //攻击对空
    bool        GroundTargets;  //攻击对地
    int         AttackCount;    //攻击几次后死亡
    string      DieEffect;      //死亡效果
    string      Animation;      //动画名称
    
    BasePeopleData()
    {
        
    }
};

// 魔法基础数据类
class BaseSpellData {
public:
    int         ID;
    int         ID_Type;
    int         Level;
    string      Name;
    string      TID;
    string      InfoTID;
    int         SpellForgeLevel;
    int         LaboratoryLevel;
    string      TrainingResource;
    int         TrainingCost;
    int         HousingSpace;
    int         TrainingTime;
    int         DeployTimeMS;
    int         ChargingTimeMS;
    int         HitTimeMS;
    int         CooldownS;
    int         UpgradeTimeH;
    string      UpgradeResource;
    int         UpgradeCost;
    int         BoostTimeMS;
    int         SpeedBoost;
    int         SpeedBoost2;
    int         JumpHousingLimit;
    int         JumpBoostMS;
    int         DamageBoostPercent;
    int         Damage;
    int         Radius;
    int         NumberOfHits;
    int         RandomRadius;
    int         TimeBetweenHitsMS;
    string      IconSWF;
    string      IconExportName;
    string      BigPicture;
    string      PreDeployEffect;
    string      DeployEffect;
    string      DeployEffect2;
    string      ChargingEffect;
    string      HitEffect;
    bool        RandomRadiusAffectsOnlyGfx;
    BaseSpellData()
    {
        
    }
};

// 国际化语言
struct TextInfo {
    string TID;
    string TEXT_EN; //ying wen
    string TEXT_CN; //han yu
};

// character的动画基础数据
struct ActionData {
    string      Name;
    bool        HasDirections;
    int         ActionFrame;
    string      ExportName;
    bool        Looping;
};

class BaseAnimationData {
public:
    
    map<std::string,const ActionData> animData;
    
    BaseAnimationData()
    {
        
    }
};

// npc 关卡
class NPCLevelData {
public:
    string  Name;                   //关卡类型名称
    string  MapInstanceName;        //关卡实例名称
    string  MapDependencies;        //关卡实例依赖关卡类型名称
    string  TID;                    //文本ID
    int     ExpLevel;               //解锁经验等级
    string  UnitType;               //关卡内unit类型
    int     UnitCount;              //关卡内unit数量
    string  LevelFile;              //关卡地图文件名称
    int     Gold;                   //关卡获取最大金币数
    int     Elixir;                 //关卡获取最大药水数
    bool    AlwaysUnlocked;         //是否总是解锁
    
    NPCLevelData()
    {
        
    }
};

//主基建造等级限制
class TownHallLevelsData {
    
public:
    int Level;                  //基地等级
    int AttackCost;             //PVP检索花费
    int TroopHousing;           //营火数量
    int ElixirStorage;          //水罐数量
    int GoldStorage;            //金库数量
    int ElixirPump;             //水井数量
    int GoldMine;               //金矿数量
    int Barrack;                //兵营数量
    int Cannon;                 //加农炮
    int Wall;                   //墙
    int ArcherTower;            //箭塔
    int WizardTower;            //法师塔
    int AirDefense;             //防空塔
    int Mortar;                 //巨炮
    int AllianceCastle;         //公会城保
    int Ejector;                //弹射地雷
    int Superbomb;              //超级地雷
    int Mine;                   //普通地雷
    int WorkerBuilding;         //工人
    int Laboratory;             //科技
    int Communicationsmast;     //已取消
    int TeslaTower;             //电塔
    int SpellForge;             //魔法池
    int Bow;                    //--
    int Halloweenbomb;          //--
    
    TownHallLevelsData()
    {
        
    }
};


//场景障碍物数据类
class ObstaclesData {
public:
    int ID;                         //对象ID
    int TypeID;                     //类型ID
    string  Name;                   //名称
    string  TID;                    //文字ID
    string  SWF;                    //SWF
    string  ExportName;             //动画名称
    string  ExportNameBase;         //动画基础action
    string  ExportNameBaseNpc;      //npc操作时action
    int ClearTimeSeconds;           //清除时间
    int Width;                      //占宽
    int Height;                     //占高
    string  Resource;               //资源
    bool    Passable;               //可否通行
    string  ClearResource;          //清除用资源名称
    int ClearCost;                  //清除用资源数量
    string  LootResource;           //获取资源名称
    int LootCount;                  //获取资源数量
    string  ClearEffect;            //清除特效
    string  PickUpEffect;           //拾取特效
    int RespawnWeight;              //重生权重
    
    ObstaclesData()
    {
        
    }
};

//effect 发射器信息
struct EffectParEmitterInfo {
    string  ParticleEmitter;//
    int     CameraShake;    //
    bool    AttachToParent; //是否依附父节点
    bool    Looping;        //是否循环
    string  IsoLayer;       //所在层
    bool    Targeted;       //是否有目标
};

class EffectData {
public:
    string  Name;           //特效名称
    string  SWF;            //文件名称
    string  ExportName;     //动画名称
    string  ParticleEmitter;//发射器名称

    map<std::string,const EffectParEmitterInfo> EffParEmitterInfo;//发射器信息
    
    string  Sound;          //特效开始音效名称
    int Volume;             //特效开始音效音量
    int MinPitch;           //
    int MaxPitch;           //
    
    string  LowEndSound;    //特效结束音效名称
    int LowEndVolume;       //特效结束音效音量
    int LowEndMinPitch;     //
    int LowEndMaxPitch;     //
    
    EffectData()
    {
    }
};
//人物等级经验
class ExperienceLevels {
public:
    int ExperienceLevels_lv;        //等级
    int ExperienceLevels_exp;       //
    int ExperienceLevels_exp1_5;     //
    
    ExperienceLevels()
    {
    }
};
// ======== shop 类管理
// 保护盾
struct ShieldData {
    int     ID;
    string  Name;
    string  TID;
    string  InfoTID;
    int     TimeH;
    int     Diamonds;
    string  IconSWF;
    string  IconExportName;
    int     CooldownS;
};

// 资源包
struct Resource_Pack {
    int     ID;
    string  Name;
    string  TID;
    string  Resource;
    int     CapacityPercentage;
    string  IconSWF;
    string  IconExportName;
};

// shop ====end

class GameData
{
public:
	GameData();
	~GameData();
// 基础数据存放
	//用户信息数据
	static UserData* m_stUserData;
    
    //新手引导的数据
    typedef map<unsigned int,const TutorialData>  tutorial_t;
	static tutorial_t m_mapTutorialData;
    
    //建筑物基础数据
    typedef map<unsigned int,const BaseBuildingLevelData>  basebuildlevel_t;
	static basebuildlevel_t m_mapBuildingBaseData;
    
    //人物基础数据
    typedef map<unsigned int,const BasePeopleData>  basepeople_t;
	static basepeople_t m_mapPeopleBaseData;
    
    //魔法基础数据
    typedef map<unsigned int, const BaseSpellData> basespell_t;
    static basespell_t m_mapSpellBaseData;
    
    //对象数据模版
    typedef map<unsigned int,const UnitClass>  unitclass_t;
    static unitclass_t m_mapUnitClassBaseData;
    
    //attack模版数据
    typedef map<string,const AttackData> baseattack_t;
    static baseattack_t m_mapAttackBaseData;
    
    //missle基础数据
    typedef map<unsigned int, const Cmd_Missle> basemissle_t;
    static basemissle_t m_mapMissleBaseData;
    
    //动画基础数据
    typedef map<string, const BaseAnimationData> baseanimation_t;
    static baseanimation_t m_mapAnimationBaseData;
    
    //npc关卡基础数据
    typedef map<string,const NPCLevelData> basenpclevel_t;
    static basenpclevel_t m_mapNpcLevelBaseData;
    
    //主基建造等级限制基础数据
    typedef map<int,const TownHallLevelsData> baseTownHallLevel_t;
    static baseTownHallLevel_t m_mapTownHallLevelBaseData;
    
    //场景障碍物基础数据
    typedef map<int, const ObstaclesData> baseobstacle_t;
    static baseobstacle_t m_mapObstacleBaseData;

    //effect基础数据
    typedef map<string, const EffectData> baseeffect_t;
    static baseeffect_t m_mapEffectBaseData;
    
    //等级基础数据
    typedef map<int, const ExperienceLevels> baseExperienceLevels;
    static baseExperienceLevels m_mapExperienceLevelsBaseData;
    
    //国际化语言
    typedef map<std::string,const TextInfo > basetext_t;
    static basetext_t m_mapTextBaseData;
    
    
    typedef map<int, const ShieldData> baseshield_t;
    static baseshield_t m_mapShieldBaseData;
    
    typedef map<int, const Resource_Pack> baseResource_Pack_t;
    static baseResource_Pack_t m_mapResource_PackBaseData;
    

// 基础数据操作方法 
public:
    //加入一条新手引导基础数据
	static void AddDataToTutorialData( unsigned int tutorialID, TutorialData const& tutorialData );
	//获取一条新手引导数据
	static const TutorialData* GetDataFromTutorialData( unsigned int tutorialID);
    
	//加入一条建筑基础数据
	static void AddDataToBaseBuildingLevelData( unsigned int buildingID, BaseBuildingLevelData const& buildingData );
	//获取一条建筑基础数据
	static const BaseBuildingLevelData* GetDataFromBaseBuildingLevelData( unsigned int buildingID);
    
    //加入一条人物基础数据
    static void AddDataToBasePeopleData( unsigned int ID, BasePeopleData const& peopleData);
    //获取一条人物基础数据
    static const BasePeopleData* GetDataFromBasePeopleData( unsigned int ID);
    
    //加入一条对象的模版数据
	static void AddUnitClassData(unsigned int unitID, UnitClass const& unitData );
	//获取一条对象的模版数据
	static const UnitClass* GetUnitClassData(unsigned int unitID);
    
    //加入一条attack模版数据
    static void AddDataToBaseAttackData(string attackName, AttackData const & attackData);
    //获取一条attack模版数据
    static const AttackData* GetDataFromBaseAttackData(string attackName);
    
    //加入一条missle模版数据
    static void AddDataToBaseMissleData(unsigned int ID, Cmd_Missle const& missleData);
    //获取一条missle模版数据
    static const Cmd_Missle* GetDataFromBaseMissleData( unsigned int ID);
    
    //加入一条魔法基础数据
    static void AddDataToBaseSpellData(unsigned int ID, BaseSpellData const& spellData);
    //获取一条魔法基础数据
    static const BaseSpellData* GetDataFromBaseSpellData(unsigned int ID);
    
    //加入一条动画基础数据
    static void AddDataToBaseAnimationData(string ID, BaseAnimationData const& animationData);
    //获取一条动画基础数据
    static const BaseAnimationData* GetDataFromBaseAnimationData(string ID);

    //加入一条npc关卡基础数据
    static void AddDataToBaseNpcLevelData(string LevelName,NPCLevelData const& npclevelData);
    //获取一条npc关卡基础数据
    static const NPCLevelData* GetDataFromBaseNpcLevelData(string LevelName);
    
    //加入一条TownHallLevel限制基础数据
    static void AddDataToBaseTownHallLevelsData(int TownHallLevel,TownHallLevelsData const& townHallLevelData);
    //获取一条TownHallLevel限制基础数据
    static const TownHallLevelsData* GetDataFromBaseTownHallLevelsData(int TownHallLevel);
    
    //加入一条场景障碍物基础数据
    static void AddDataToBaseObstacleData(int ID,ObstaclesData const& obstacleData);
    //获取一条场景障碍物基础数据
    static const ObstaclesData* GetDataFromBaseObstacleData(int ID);
    
    //加入一条特效基础数据
    static void AddDataToBaseEffectData(string Name,EffectData const& effectData);
    //获取一条特效基础数据
    static const EffectData* GetDataFromBaseEffectData(string Name);
    
    //加入一条等级基础数据
    static void AddDataToBaseExperienceLevels(int Lv,ExperienceLevels const& experienceLevels);
    //获取一条等级基础数据
    static const ExperienceLevels* GetDataFromBaseExperienceLevels(int Lv);
    
    //添加一条文本信息
    static void AddDataToBaseTextData(string const& ID, TextInfo const& textData);
    //获取一条文本信息
    static const string* GetTextInfo(string const& ID);
    
    
    static void AddShieldData(int ID, ShieldData const& shieldData);
    static const ShieldData* GetShieldData(int ID);
    
    static void AddResource_PackData(int ID, Resource_Pack const& resource_PackData);
    static const Resource_Pack* GetResource_PackData(int ID);
};
#endif
