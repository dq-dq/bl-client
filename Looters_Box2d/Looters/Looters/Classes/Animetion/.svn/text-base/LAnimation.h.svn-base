/***************************************************************
 author:    wangning
 write time: 2011.11.8
 function: 动画对象
 ***************************************************************/
#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace std;
USING_NS_CC;

// 加农炮方向
enum AnimMortarDirection {
    Steer_Leftmiddle = 0,
    Steer_Middleright = 1,
    Steer_Rightmiddle = 2,
    Steer_Middleleft = 3,
    Steer_Leftright = 4,
    Steer_Rightleft = 5
};

// 平炮的方向
enum AnimCannonDirection {
    Left1 = 0, // 左下方
    Left2 = 1,
    Left3 = 2,
    Left4 = 3,
    Left5 = 4,
    Left6 = 5, // 左上方
    Left7 = 6, // 右下方
    Left8 = 7,
    Left9 = 8,
    Left10 = 9,
    Left11 = 10,
    Left12 = 11 // 右上方
};

// 动画默认的八个方向
enum AnimDirection {
    Left = 0,
    LeftTop = 1,
    LeftBottom = 2,
    Right = 3,
    RightTop = 4,
    RightBottom = 5,
    Up = 6,
    Down = 7
};

struct LAction
{
    CCAction* action[6];
    
    LAction()
    {
        action[0] = NULL;
        action[1] = NULL;
        action[2] = NULL;
        action[3] = NULL;
        action[4] = NULL;
        action[5] = NULL;
    }
};

class LAnimation : public CCNode
{
public:
    LAnimation();
    ~LAnimation();
    
    static LAnimation* create();
    
    
private:
    int  get_Direction(CCPoint angle);      // 根据角度得到对象当前移动的方向
    int  get_Direction_Cannon(CCPoint angle); // 根据角度得到炮当前移动的方向
    int  get_action(CCPoint direction);     // 根据方向得到对象当前action动画

public:
    CCSprite* m_pCharSprite;                        //播放action的sprite
    typedef map<std::string,const LAction> laction_t;
    laction_t  m_mapLAnim;    // idle_1_1
    
    string m_LActionName;
    const LAction* m_LAction;
    int m_LChildID;//当前运行的LAction下的ID
    
    int unitTypeID;
    void setUnitTypeID(int unitTypeID_)
    {
        unitTypeID = unitTypeID_;
    }
    
public:
    // 外部访问接口
    void restart_action(); // 重新启动当前的action
    void run_action(string const& actionName,CCPoint angle);  //运行action
};







