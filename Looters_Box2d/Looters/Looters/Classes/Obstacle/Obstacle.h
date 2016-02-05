/***************************************************************
 author:    wangning
 write time: 2012.12.16
 function: 建筑基础类
 ***************************************************************/
#pragma once
#include "cocos2d.h"
#include "Unit.h"

using namespace cocos2d;

class Obstacle:public Unit {
    
public:
    Obstacle();
    ~Obstacle();
    
    static Obstacle* create(int uuid,int ID);
    bool init(int uuid,int ID);
    
public:
    int m_ClearTimeSeconds;
    int m_Width;
    int m_Height;
    bool m_Passable;
    
public:
    bool isPassable(); // 是否可以通过
    int getWidth();    // 获取障碍物的宽
    int getHeight();   // 获取障碍物的高
};