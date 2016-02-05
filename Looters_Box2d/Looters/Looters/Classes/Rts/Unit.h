/***************************************************************
 author:    wangning
 write time: 2011.11.8
 function: rts游戏插件部分 提供游戏对象的基本结构 动画 核心ai 阵营 等
 ***************************************************************/
#pragma once
#include "cocos2d.h"
#include "LAnimation.h"
#include "GamePlatform.h"
#include "GLES_Render.h"
#include "Attack.h"
#include "UnitClass.h"
#include "Box2D.h"
#include "some_tool.h"
#include "LParticleUnit.h"
using namespace cocos2d;

#define UNIT_Texture_scale_2048x1536 1


enum unit_camp {
	// 阵营关系
	// army (hates->enemy atks->enemy)
	// enmey (hates->(army,friend) atks->(army,friend))
	// friend (hates->enemy atks->enemy)
	UNIT_CAMP_NONE = -1,
    UNIT_CAMP_ENEMY = 0,//敌军
	UNIT_CAMP_ARMY = 1,//我军
	UNIT_CAMP_FRIEND = 2//友军
};
	
enum unit_state
{
	//等待删除的状态。为了指针安全，在固定的pass删除
	//但此时应该完全无显示、无表现
	UNIT_STATE_GHOST        = -1,
	
	UNIT_STATE_STAND        = 0,
	UNIT_STATE_MOVING       = 1,
	UNIT_STATE_DEAD         = 2,
	UNIT_STATE_CHEER        = 3,
	UNIT_STATE_COUNT        = 4,
};

enum unit_ai {
	UNIT_AI_NONE = -1,
	UNIT_AI_STAND = 0,
	UNIT_AI_MOVE = 1,
	UNIT_AI_PATROL = 2,
    UNIT_AI_STAND_CANNON = 3,
	UNIT_AI_WORKER = 4,
	UNIT_AI_RESOURCE_WORKER=5
};

enum unit_z_state {
	//z值的特殊处理
	UNIT_Z_NORMAL_STATE = 0,
	UNIT_Z_MAX_STATE = 1
};

enum unit_type
{
	UT_NOGAIN_BUILD,
	UT_ARMY_BUILD,
	UT_TOWN_HALL_BUILD,
	UT_RESOURCE_BUILD,
	UT_DEFENSE_BUILD,
	UT_WALL_BUILD,
	UT_WORKER_BUILD,
	UT_NPC_BUILD,


	UT_ROLE,
	UT_MISSLE,
	UT_DECORATE,
	UT_NPC_BUILDING_WORKER,
	UT_NPC_RESOURCE_WORKER,
	UT_NONE,
};

//建筑状态
enum unit_upgrade {
    UNIT_UPGRADE_NO = -2,           //未建造状态
    UNIT_UPGRADE_NONE = -1,         //一般状态
    UNIT_UPGRADE_BUILD = 0,         //开始建筑
    UNIT_UPGRADE_BUILDIN,           //建筑中
    UNIT_UPGRADE_BUILDSUCESS,       //建筑成功
    UNIT_UPGRADE_BUILDFAIL,         //建筑失败
    UNIT_UPGRADE_START,             //开始升级
    UNIT_UPGRADE_IN,                //升级中
    UNIT_UPGRADE_SUCESS,            //升级成功
    UNIT_UPGRADE_FAIL,              //升级失败
    UNIT_UPGRADE_REMOVE,            //拆除建筑
    UNIT_UPGRADE_REMOVEIN,          //拆除中
    UNIT_UPGRADE_REMOVESUCESS,      //拆除成功
    UNIT_UPGRADE_REMOVEFAIL,        //拆除失败
    UNIT_UPGRADE_RESUME,            //建筑恢复开始
    UNIT_UPGRADE_RESUMEIN,          //建筑恢复中
    UNIT_UPGRADE_RESUMEFINISH       //建筑恢复完成
    
};

extern unit_type typid_to_unit_type(unsigned int typeID);



class Unit:public cocos2d::CCNode
{
public:
	static int get_next_walk_time()
	{
		return get_random_range(7000, 1300);
	}
    
public:
	Unit();
	~Unit();
	
	static Unit * create(UnitClass* uclass);
	bool init(UnitClass* uclass);
	void setUnitClass(const UnitClass* uclass);

public:
    //状态部分
    CCPoint  direction_;     //cosa, sina   
    //AI状态部分
    Unit*     target;
    
    //动作部分
    unit_state    unit_state_;
    CCPoint move_target_;
    
    //表现部分
    LAnimation*   ani_state_;//动画
    string action_;// 当前action
    bool        action_restart_;
    
    CCSprite*    sprite_;
    CCSprite*    shadow_sprite_;
    CCSprite*    bloodSprite;
    CCArray*     defenderCharacterArr; // 防御塔上站的角色
    
    //内部接口:
    void _apply_sprite_state();
    void _apply_movement(float timespan);
    void _change_unit_state(unit_state s);
    void _hp_showtime(float dt);

public:
	//属性部分
	float   speed;// 速度
	int     hp, maxhp;// 血量
	
	int     camp;// 阵营

	int     lv;         // 等级
	int     Damage;     // 伤害值
	float   AttackRange;// 触发攻击范围
	int     blindRange; // 盲区范围（炮塔）
	int     AttackSpeed;// 攻击的CD时间
    bool    AirTargets; // 是否对空
    bool    GroundTargets;// 是否对地
    bool    IsFlying;// 是否为飞行单位
    
    bool    hide_hpbar;  // 是否隐藏血量
    
    //坐标属性部分
	float   offsetx, offsety, radius, height;
    
    //属性other
    float   hp_showtime; // 血条显示的时间
    
public:
	void set_sprite(CCSprite* sprite);
	void set_shadow_sprite(CCSprite* sprite);
	void set_ani_state(LAnimation* state);
    
	// 对象的死亡动画播放完之后调用 改变对象的状态到可清楚
	void remove();
    void clean();
	
	// 命令部分
	void cmd_moveto(float x, float y);//角色移动
	bool cmd_hurt(int damage);      //返回值表示 是否致死
	void cmd_stop();//停止移动
    bool cmd_resource(int cutHp); //扣除资源
	
	//特殊命令部分
	void force_position(float x, float y);
	void change_direction(float dx, float dy);
	void face_to(Unit* u);
	void kill();
	

	//AI状态部分
	unit_ai  unit_ai_cmd_;
	Unit* get_target() const
	{
		if (target && !target->is_alive())
		{
			return NULL;
		}
		return target;
	}
	void set_target(Unit* t)
	{
		target = t;
	}
	bool is_alive()
	{
		return unit_state_ >= UNIT_STATE_STAND &&
		unit_state_ < UNIT_STATE_DEAD;
	}
	bool is_ghost()
	{
		return unit_state_ == UNIT_STATE_GHOST;
	}
	CCPoint get_direction()
	{
		return direction_;
	}
	
    //攻击技能部分
    Attack* attack;
    void set_attack(const AttackData* data)
    {
        attack = Attack::newAttackClass(this, data);
        attack->retain();
    }
    
	//阵营关系部分
	bool does_hate(Unit* other);
	bool can_attack(Unit* other);
	
	bool check_range(Unit* other, float distance);
	float get_distance(Unit* other);
	
	//表现部分
	unit_state get_unit_state() const
	{
		return unit_state_;
	}

    //unit单位类型, 建筑, 角色, 导弹, 装饰
	unit_type get_unit_type() const;
	bool is_unit_type( unit_type ut) const;
	bool is_build_type() const;
    
public:
	// 返回优先目标
	bool is_love_target(Unit* other) const
	{
		if (have_love_target())
		{
			return other->is_unit_type(typid_to_unit_type(m_PreferedTargetBuilding));
		}
		else
		{
			// 无爱目标,任意目标都可以但不是墙
			return !other->is_unit_type(UT_WALL_BUILD);
		}
	}

	bool have_love_target() const
	{
		return UT_NONE!=typid_to_unit_type(m_PreferedTargetBuilding);
	}

	int m_PreferedTargetBuilding;

	typedef std::vector<b2Vec2>  ai_path_t;
	ai_path_t m_ai_path;

	// 垂直对角线的一半
	float GetBuildHalfHeight( );	
	b2Vec2 GetCenterPos( bool isUseIndex=false);

public:
	//m_uuID 对象的唯一ID
	CC_PROPERTY(int, m_uuID, uuID )
	//m_i32ID 对象的ID
	CC_PROPERTY(unsigned int, m_u32ID, ID )
	//m_uTypeID 对象的类别ID
	CC_PROPERTY(unsigned int, m_uTypeID, TypeID )
	//m_strName 对象的名字
	CC_PROPERTY(string, m_strName, Name )
    // 对象在地图格子上的索引 及其遮挡操作
	CC_PROPERTY(CCPoint,m_mapIndex,MapIndex);
    
public:
	Unit* m_pCampfire;
	long long m_role_time;

public:
	// 血条
	void drawBlood(void);
    void IsShowBlood(bool flag);

public:
	struct BUILDSUBSTRATE//建筑基座
	{
		CCPoint m_pointSubstrate;//建筑主体精灵图相对于底座的偏移
		int m_Line;//占地基的行数
		int m_Row; //占地基的列数
	};


	BUILDSUBSTRATE m_stBuildSubstrate; //建筑基座
	CCSprite *m_pSubstrateBottom;      //建筑底座精灵图(参考)
	unit_z_state z_state_;
	// 攻击范围sprite
	CCSprite *m_pSpriteAttackArea;          //攻击范围
	bool            isHarvest;              //是否可收集资源
    
    unit_upgrade upgrade_state_;//建筑物的状态
    
public:

	Unit* m_pWorkerTarget;
	Unit* m_pFromBuilding;

	std::vector<Unit*> m_ResouceTarget;
	int m_WorkerTimes;

};