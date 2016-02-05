
#ifndef Looters_CentralBattleReplayUILayer_h
#define Looters_CentralBattleReplayUILayer_h

#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class CentralBattleReplayUILayer : public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
public:
    CentralBattleReplayUILayer();
    ~CentralBattleReplayUILayer();
    
    virtual bool init();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CentralBattleReplayUILayer, create);    
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    
    
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

    
public:
    CCSprite*   s_destory_bg;
    CCSprite*   s_star_01;
    CCSprite*   s_star_02;
    CCSprite*   s_star_03;
    CCLabelTTF* l_overallDamage;
    
    
    
    //按钮
    void onReturnHome(cocos2d::CCObject * pSender);
    
public:
    void initBattleReplayUILayer();
    
    //界面显示刷新
    void update(float dt);
};



class CentralBattleReplayUILayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CentralBattleReplayUILayerLoader, loader);
    CentralBattleReplayUILayer * centralBattleReplayUILayer;
public:
    
    
    virtual CentralBattleReplayUILayer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader)
    {
        centralBattleReplayUILayer = CentralBattleReplayUILayer::create();
        return centralBattleReplayUILayer;
    }
};

#endif
