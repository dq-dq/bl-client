/***************************************************************
 author:    wangning
 write time: 2012.3.22
 function: 建筑建造管理工厂
 ***************************************************************/
#ifndef Looters_BuildingManager_h
#define Looters_BuildingManager_h
#pragma once
#include "cocos2d.h"
#include "BuildingBase.h"
using namespace cocos2d;

class BuildingManager
{
public:
	BuildingManager(void);
	~BuildingManager(void);
public:
	static BuildingBase* JudgeBuildingType(int  unitID);
	static void CloseShop();
};

#endif
