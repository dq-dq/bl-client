/***************************************************************
 author:     wangning
 write time: 2012.10.20
 function:   游戏主场景
 ***************************************************************/

#ifndef Looters_CentralScene_h
#define Looters_CentralScene_h
#pragma once
#include "cocos2d.h"
#include "CentralData.h"
#include "CentralLayer.h"
#include "CentralUILayer.h"
#include "CentralShopUILayer.h"
#include "CentralInfoUILayer.h"
#include "CentralPVPUILayer.h"
#include "CentralPVPMapUILayer.h"
#include "CentralBattleEndUILayer.h"
#include "CentralMailUILayer.h"
#include "CentralInfo2UILayer.h"
#include "CentralSettingsUILayer.h"
#include "CentralAccountNameLayer.h"
#include "CentralAccountLoginLayer.h"
#include "CentralBattleReplayUILayer.h"
class CentralScene : public cocos2d::CCScene
{
public:
    CentralScene();
    ~CentralScene();
    
    virtual bool init();
    
    CREATE_FUNC(CentralScene);
    
    // 录入基础数据
	void TranscribeBaseData( void );
    // 生成对象的模版数据
    void initUnitClassesData( void );
    // 载入音乐音效
    void loadAllSoundEffect( void );
    
    // 基础数据初始化
    bool initBaseData();
    // 基础数据释放
    void cleanBaseData();
    
    // 加载当前场景的层
    void SetBattleMode( int battlemode, int battlemode_pvp);
    void LoadSceneLayer( int mode );
    // 释放层对象
	void UnloadLayer( void );

public:
    CentralData* m_pCentralData;
    
    class CentralLayer* m_pCentralLayer;
    
    class CentralUILayer *          m_pCentralUILayer;
    class CentralShopUILayer *      m_pCentralShopUILayer;
    class CentralInfoUILayer *      m_pCentralInfoUILayer;
    class CentralPVPUILayer *       m_pCentralPVPUILayer;
    class CentralPVPMapUILayer *    m_pCentralPVPMapUILayer;
    class CentralBattleEndUILayer * m_pCentralBattleEndUILayer;
    class CentralMailUILayer *      m_pCentralMailUILayer;
    class CentralInfo2UILayer *     m_pCentralInfo2UILayer;
    class CentralSettingsUILayer* m_pCentralSettingsUILayer;
    class CentralAccountNameLayer* m_pCentralAccountNameLayer;
    class CentralAccountLoginLayer* m_CentralAccountLoginLayer;
    class CentralBattleReplayUILayer* m_CentralBattleReplayUILayer;

    
public:
    CCNode * openTest(const char * pCCBFileName, const char * pCCNodeName = NULL, cocos2d::extension::CCNodeLoader * pCCNodeLoader = NULL, cocos2d::extension::CCBAnimationManager ** animManager  = NULL);
};


#endif
