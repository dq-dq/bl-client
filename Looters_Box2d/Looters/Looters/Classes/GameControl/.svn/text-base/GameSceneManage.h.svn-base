/***********************************************
 author: wangning
 write time: 2012.10.20
 function: 场景管理
************************************************/
#pragma once
#include "cocos2d.h"
using namespace cocos2d;

#include "LoginScene.h"
#include "CentralScene.h"

//场景ID
enum SCENE_ID
{
	SCENE_LOGIN,  //登陆场景
	SCENE_CENTRAL,//主场景
};

//场景管理器
class SceneManage
{

public:
	class LoginScene  *m_pLogicScene;
	class CentralScene *m_pCentralScene;
	
public:
	SceneManage();
	~SceneManage();

	static SceneManage* GetSceneManageHendle( void );
	static void ReleaseSceneManage( void );

	bool Init( void );

    //运行场景
	bool RunScece( int iSceneID, bool bReplace);
	CCScene* GetSceneFrameID( int iSceneID );

private:
	
};