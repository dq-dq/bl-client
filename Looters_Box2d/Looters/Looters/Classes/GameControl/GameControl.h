/***************************************************************
author:     wangning
write time: 2012.10.20
function:   游戏框架，
***************************************************************/
#pragma once
#include "GameSceneManage.h"
#include "GamePlatform.h"
#include "GameResources.h"
#include "GameFile.h"
#include "SoundManage.h"

//游戏主框架
class GameControl
{
public:
	GameControl();
	~GameControl();

	//运行框架
	static bool RunGameControl( void );
	//得到框架指针
	static GameControl* GetGameControl( void );
public:
	//循环函数
	void Run( float dt );
private:
	//初始化场景管理器
	bool InitControl( void );
		
};