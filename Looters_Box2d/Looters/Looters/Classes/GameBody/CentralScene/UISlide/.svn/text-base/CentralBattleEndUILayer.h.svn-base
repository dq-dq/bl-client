//
//  CentralBattleEndUILayer.h
//  Looters
//
//  Created by yisuode on 12-12-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef Looters_CentralBattleEndUILayer_h
#define Looters_CentralBattleEndUILayer_h

#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
//UI_Over
class CentralBattleEndUILayer : public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
public:
    CentralBattleEndUILayer();
    ~CentralBattleEndUILayer();
    
    virtual bool init();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CentralBattleEndUILayer, create);
    //    CREATE_FUNC(CentralUILayer);
    
    
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    
    
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    void show_component(); // 战斗结束界面信息显示
    
    void onHome(cocos2d::CCObject * pSender); // 点击return home回调

    
public:
    //界面精灵
    CCSprite*   s_star1;
    CCSprite*   s_star2;
    CCSprite*   s_star3;
    
    CCSprite*   s_with; //失败
    CCSprite*   s_win;  //成功
    
    //界面文字
    CCLabelTTF*  l_gold;
    CCLabelTTF*  l_water;
    CCLabelTTF*  l_cup;
    
    CCArray* iconArr;
};



class CentralBattleEndUILayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CentralBattleEndUILayerLoader, loader);
    CentralBattleEndUILayer * centralBattleEndUILayer;
public:
    
    
    virtual CentralBattleEndUILayer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader)
    {
        centralBattleEndUILayer = CentralBattleEndUILayer::create();
        return centralBattleEndUILayer; 
    }
};


#endif
