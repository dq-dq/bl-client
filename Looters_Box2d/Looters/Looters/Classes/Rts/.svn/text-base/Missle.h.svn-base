/***************************************************************
 author:    wangning
 write time: 2011.11.8
 function: rts游戏插件部分 提供游戏missle对象(技能的核心模块)
 ***************************************************************/

#include "cocos2d.h"
#include "Unit.h"
#include "AttackData.h"
using namespace cocos2d;

// todo 对象死亡判定
// 轨迹类型
enum Orbit_Type {
    Orbit_Type_defaultTrack = 0,
    Orbit_Type_Accelerate = 1,
    Orbit_Type_ParabolaTrackNoFollow = 2,
    Orbit_Type_parabolaTrack = 3,
};
    
class Missle : public Unit{
public:
    Missle();
    ~Missle();
public:
    const Cmd_Missle* missleData;
public:
    CCSprite* sprite;
    Unit* src; // 由谁发射
    Unit* dest; // 目标对象
    long long startt; // 发射的起始时间
    
    float speed;
    float a;
    
    Orbit_Type  orbit_Type_;
    
    // 音效
    string soundname;
    float volume;
public:
    static Missle* newMissleClass(Unit* sc,Unit*t, int aniID,const Cmd_Missle* data);
    bool init(Unit* sc,Unit* t,int aniID,const Cmd_Missle* data);
    
public:
    void update(float time);
    
    void onarrive(); //到达目标点调用
    
    void dealDmg(Unit* dest,Unit* src,int value);
public:
    float *s;
    float *d;
    
    // missle 移动轨迹
    static float* getp(Unit* u){
        CCPoint pos = u->getPosition();
        float *a = new float[3];
        a[0] = pos.x+u->offsetx;
        a[1] = pos.y;
        a[2] = u->offsety;
        return a;
    }

    static float inter(float x, float y, float p){
        return x * (1-p) + y * p;
    }
    
    // 加速移动函数 speed 速度，a 加速度
    bool accelerateTrackTM(float speed,float a);
    
    bool defaultTrackTM(float speed);
    
    bool parabola(float speed, float gravity,int rottype);
    
    bool parabolaTrackNoFollowTM(float speed, float gravity, int rotatetype);
    bool parabolaTrackTM(float speed, float gravity, int rotatetype);
};
