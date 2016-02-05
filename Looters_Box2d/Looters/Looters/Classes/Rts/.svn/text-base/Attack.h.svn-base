/***************************************************************
 author:    wangning
 write time: 2011.11.8
 function: rts 技能－普通攻击模块
 ***************************************************************/
#pragma once
#include "cocos2d.h"
#include "AttackData.h"
class Unit;
using namespace cocos2d;

// 指令
enum Attack_Cmd {
    Attack_Cmd_CheckUnitType = 0,// 攻击对象判定，决定是否攻击
    Attack_Cmd_CheckRange = 1,   // 攻击前范围检测
    Attack_Cmd_Began = 2,        // 技能开始
    Attack_Cmd_Ani = 3,          // src攻击动画
    Attack_Cmd_Sound = 4,        // 播放声音
    Attack_Cmd_Dmg = 5,          // 攻击伤害  (魔法塔直接造成伤害的这种)
    Attack_Cmd_Missle = 6,       // 攻击missle对象
    Attack_Cmd_End = 7,          // 技能结束
};

class Attack : public CCNode{
public:
    Attack();
    ~Attack();

public:
    const AttackData* attackData;
    
    string soundname;
    float volume;
public:
    Unit* src;   // 释放技能对象
    Unit* dest;
    long long cdt;  // 攻击的冷却时间间隔
    long long cddt; // 冷却时间点
    bool begin;
    
    int curAttack_Cmd;
public:
    static Attack* newAttackClass(Unit* sc,const AttackData* data);
    bool init(Unit* sc,const AttackData* data);
    bool useable();
    void use(Unit* t);
    
    void setCD(long tt);
    void resetCD();
    
public:
    // 技能更新
    void attack_update(float time);
    
public:
    // 指令函数模版
    bool checkUnitTypeTM( void );
    bool checkRangeTM();
    bool skillBeginPhaseTM();
    bool aniPhaseTM();
    bool playSoundTM();
    bool addDmgTM();
    bool misslePhaseTM();
    void skillEndPhaseTM();
	
	
	void force_end_skill();

    
    // 执行指令
    void toDoCmd(int cmd);
};













