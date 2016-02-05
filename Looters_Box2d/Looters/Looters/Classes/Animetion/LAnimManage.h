/***************************************************************
 author:    wangning
 write time: 2011.11.8
 function: 动画对象管理 (对象的动画模版应该loading的时候应该加载好)
 ***************************************************************/
#pragma once
#include "cocos2d.h"
#include "LAnimation.h"
#include "GameControl.h"
#include "Unit.h"
using namespace cocos2d;

class LAnimManage {

public:
    LAnimManage(void);
	~LAnimManage(void);
    
    static LAnimManage* shareLAnimManage();
    static LAnimManage* m_LAnimManage;
    
	CCFiniteTimeAction* createAction(ActionData const& actionData, Unit* u, char const* directonName);
	LAction createLAction(ActionData const& actionData, Unit* u);
	static LAnimation* createLAnimation(string const& animName, Unit*u);
};