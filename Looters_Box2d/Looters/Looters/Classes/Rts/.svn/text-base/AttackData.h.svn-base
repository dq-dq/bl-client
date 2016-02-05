/***************************************************************
 author:    wangning
 write time: 2011.11.8
 function: rts 技能－数据
 ***************************************************************/
#pragma once
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;

struct Cmd_Missle {
    int ID;
    string AnimName;
    string ActionID;
    int Ofsx;       // 击中目标物相对于postion的偏移
    int Ofsy;
    int Ofsh;
    
    int Locus_type; // 轨迹类型
    float Speed;    // 速度
    int Gravity;    // 重力
    int Rottype;    // 运动类型下细分类型
    int Isfollow;   // 是否跟踪
};

class AttackData {
public:
    AttackData();
    ~AttackData();
    
public:
    string  AttackName;  // 攻击名称
    int     UnitType;    // unit 类型判定 是否为可攻击对象 -1 可以 
    int     CheckRange;  // 特殊检测范围(是否在某个范围内)
    bool    AtackAni;    // src是否播放攻击开始动画 true 播放 false 不播放
    int     DmgType;     // 攻击伤害类型  0间接 1直接
    bool    IsMissle;    // 是否有missle对象
    int     MissleID;    // missleID
};