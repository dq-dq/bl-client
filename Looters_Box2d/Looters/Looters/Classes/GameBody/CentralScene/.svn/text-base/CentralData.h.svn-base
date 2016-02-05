/***************************************************************
 author:     wangning
 write time: 2012.10.20
 function:   游戏主场景相关数据
 ***************************************************************/
#ifndef Looters_CentralData_h
#define Looters_CentralData_h
#pragma once
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;


// 游戏场景中的z值排序问题
#define Z_EARTHSURFAC_   -900
#define Z_SUBSTRATEBOTTOM_ -800
#define Z_ATTACKAREA_    -700
#define Z_UNIT_MISSLE_ 2000
#define Z_EFFECT_        3000
#define Z_TIPNODE_       10000

// 游戏的两种场景视图  self visit
enum CENTRALVIEW_MODE {
    CENTRALVIEW_SELF,
    CENTRALVIEW_VISIT,
    CENTRALVIEW_BATTLE,
};
    
// 游戏的两种战斗模式   pve pvp
enum BATTLE_MODE
{
	CENTRALVIEW_PVE,
	CENTRALVIEW_PVP,
};

// PVP模式 正常匹配玩家 还是 复仇
enum BATTLE_MODE_PVP
{
    BATTLE_MODE_PVP_MATCH,
    BATTLE_MODE_PVP_REVENGE,
	BATTLE_MODE_PVP_REPLAY,
};

class CentralData :public cocos2d::CCObject
{
public:
    //用户数据信息  服务器获取 不需存档
    
    
    // 攻击者的兵力和魔法情况
    struct AttackerSoldiersAndSpell
    {
        int used_type;
        int characterIdOrSpellId;
        int characterOrSpellLevel;
        int count;
        int maxcount;
    };
    
    // 战斗匹配玩家基础信息
    struct MatchPlayer
    {
        string* nickName;       // 昵称
        string* gameCenterID;   // 用户gameCenterID
        int golden_count;       // 可以获取到的金币数量
        int elixir_count;       // 可以获取到的药水数量
        int pvp_mark;           // 获取的Pvp分数
        int level;              // 防守者等级等级
        
        int used_clans_character_count;// 使用工会兵力数量
        int lose_pvp_mark; // 失败丢失的Pvp分数
        
        MatchPlayer()
        {
            nickName = NULL;
            gameCenterID = NULL;
            golden_count = 0;
            elixir_count = 0;
            pvp_mark = 0;
            level = 0;
        }
    };
    
    // 用户地图信息
    struct M_UserMapData
    {
        int uniqueness_build_id; //建筑的唯一ID
        int map_index_x; //格子x
        int map_index_y; //格子y
        int building_id; //建筑ID
        int building_level;//建筑等级
        int collect_count; //攻击者获取到的金币或者药水数量
        int second_elixir_count; // 大厅药水数量
        int building_status;//建筑物的状态 0正常 1升级中
        
        int destory_status; // 建筑物是否销毁
        int cut_collect_count; // 减少金币或者药水数量
        int cut_elixir_count;  // 大厅减少药水数量
        
        M_UserMapData()
        {
            destory_status = 1;
            cut_collect_count = 0;
            cut_elixir_count = 0;
        }
    };
    // 建筑物的损坏情况
    struct BuildDestoryStatusData
    {
        int	building_id;	//建筑ID
        int	uuid;           //uuid
        int	map_index_x;	//地图上的位置信息x
        int	map_index_y;	//地图上的位置信息y
        BuildDestoryStatusData()
        {
            
        }
    };
    
    // 被攻击信息
    struct BattleInforTip
    {
        string* attacker_nick_name; //攻击者昵称
        int defencer_get_pvp_mark; //防御者获取的pvp分数
        string* attack_time;//攻击时间
        
        BattleInforTip()
        {
            attacker_nick_name = NULL;
            attack_time = NULL;
        }
    };
    
    struct Central_UserData
    { 
    public:
        int   user_gold;                //玩家的金钱数
        int   user_goldMAX;
        
        int   user_potions;             //玩家药水数
        int   user_potionsMAX;          //玩家药水数
        
        int   user_gem;                 //玩家的宝石数
        string*   nick_name;            //昵称
        int   pvp_mark;                 //Pvp分数
        int   exp;                      //经验
        int   level;                    //等级
        int   shield_time;              //被保护时间
        int   destroy_status;           //0不用恢复 1全部恢复 2正在战斗(此字段暂时无效)
        bool  battle_request_flag;      //false不请求,true请求 获取被打列表 
        int   battle_end_time;          //战斗结束时间
        int   peopleNumMax;             //最大人口数
        int   allPeopleNum;             //全部人口数
        int   allYouPeopleNum;          //现有人口数
        
        int   battleMathingUseCount;    //战斗匹配花费的金币数量
        
        BattleInforTip* battleInfor;//被攻击提示信息
        
        Central_UserData()
        {
            battleInfor = NULL;
            nick_name = NULL;
            user_goldMAX = 0;
            user_potionsMAX = 0;
            user_gold = 0;
            user_potions = 0;
            peopleNumMax = 0;
            allYouPeopleNum = 0;
        }
    };
    
    //战斗信息列表
    struct AttackerUsed
    {
        int	used_id;	//（兵，魔法）id
        int	used_count;	//使用数量
        int	used_type;	//0兵ID，1使用工会兵力，2魔法ID
    };
    
    struct BattleInfor{
        string bowie_id; 
        int attacker_level; //攻击者等级
        string	attacker_nick_name;	//攻击者昵称
        int	attacker_get_golden_count;	//攻击者获取金币数量
        int	attacker_get_elixir_count;	//攻击者获取的药水数量
        string	attack_time;	//攻击时间
        int	defencer_get_pvp_mark;	//防御者获取的pvp分数
        string	clans_name;	//工会名称
        string	clans_image_name;	//工会图标名称
        vector<AttackerUsed> attackerUsedList;	//攻击者用到的兵力,魔法，工会 情况
        string	replyFileName;	//回放文件名称
        
        int	star_count;//	攻击者获取的星星数量
    };
    
    //可建造的兵 
    struct BuildableSoldiers
    {
        int leve; //等级
        int type; //类别
        int num;
        BuildableSoldiers()
        {
            num = 0;
        }
    };
    //可造的魔法
    struct BuildableMagic
    {
        int leve; //等级
        int type; //类别
        int num;
    };
    
    //开始战斗 响应数据
    struct BattleStartResponseData
    {
        int	battleId; // 战斗ID
        int	verifyCode; // 上传回放文件验证码(30分钟)
    };
    
    //回放文件数据
    struct IoFileResponseData
    {
        int	maxPackage;	//最大索引块
        int	index;	//当前索引块
        string ioData;
        IoFileResponseData()
        {
            index = 0;
            maxPackage = 0;
        }
    };
    
public:
	CentralData();
	~CentralData();
    
	static CentralData* Load( void );  //加载主场景相关数据
    
    enum BATTLE_MODE         m_enBattleMode;        //2种战斗模式
	enum CENTRALVIEW_MODE    m_enCentralViewMode;   //3种场景视图
    enum BATTLE_MODE_PVP     m_enPVPMode;           //pvp 访问的两种方式
    
public:
    // pvp 游戏数据
    MatchPlayer* m_MatchPlayer;
    string m_MatchPlayer_ID; // 战斗匹配玩家的m_MatchPlayer_ID
    Central_UserData* m_Central_UserData;
    vector<BuildableSoldiers*>* m_BuildableSoldiers;
    vector<BuildableMagic*>* m_BuildableMagic;
    vector<AttackerSoldiersAndSpell*>* m_AttackerSoldiersAndSpell;
    
    typedef map<int, M_UserMapData> userMapData_t;
    userMapData_t m_M_UserMapData;
    
    typedef map<int, BuildDestoryStatusData> buildDestoryStatus_t;
    buildDestoryStatus_t m_buildDestoryStatus;
    
    typedef vector<BattleInfor> battleInfo_t;
    battleInfo_t m_BattleInfoList;
    string m_BattleInfo_PlayerID;
    
    BuildableSoldiers* getBuildableSoldiers(int _type);
    BuildableMagic* getBuildableMagic(int _type);
    
    BattleStartResponseData m_BattleStartResponseData; // 开始战斗 响应数据
	
	std::string m_battleReplay;
    
    IoFileResponseData m_IoFileResponseData;
	
	std::vector<std::string> m_battleReplayFiles;
    
public:
    void CleanData( void );
    void CleanBattleData(void);

public:
    void AddM_UserMapData( int uuid, M_UserMapData & mapData );
    M_UserMapData* GetM_UserMapData(int uuid);
    
    void AddBuildDestoryStatusData( int uuid, BuildDestoryStatusData & buildDestoryStatusData );
    BuildDestoryStatusData* GetBuildDestoryStatusData(int uuid);
};
#endif
