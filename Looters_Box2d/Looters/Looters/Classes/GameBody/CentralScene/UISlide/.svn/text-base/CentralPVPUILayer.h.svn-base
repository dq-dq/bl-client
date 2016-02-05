//
//  CentralPVPUILayer.h
//  Looters
//
//  Created by yisuode on 12-11-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef Looters_CentralPVPUILayer_h
#define Looters_CentralPVPUILayer_h

#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class CentralPVPUILayer : public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
public:
    CentralPVPUILayer();
    ~CentralPVPUILayer();
    
    virtual bool init();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CentralPVPUILayer, create);
    
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
     
    
    
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
public:
    void onEnter();
    void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
public:
    // sp
    CCSprite*  s_map_01;
    CCSprite*  s_map_02;
    CCSprite*  s_map_03;
    
    CCSprite*  s_pvp_find_bg;
    CCSprite*  s_gonghui;
    CCSprite*  s_mofa;
    CCSprite*  s_jiangbei;
    // btn
    CCControlButton * b_direction;
    
    // lab
    CCLabelTTF*  l_costgold;
    
    //按钮
    void onDirection(cocos2d::CCObject * pSender);
    
    void onBtuPVP(cocos2d::CCObject * pSender);
    void onBtnPVPCancel(cocos2d::CCObject * pSender);
    
    
public:
    void initCentralPVPUI();
    
};



class CentralPVPUILayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CentralPVPUILayerLoader, loader);
    CentralPVPUILayer * centralPVPUILayer;
public:
    
    
    virtual CentralPVPUILayer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader)
    {
        centralPVPUILayer = CentralPVPUILayer::create();
        return centralPVPUILayer; 
    }
};


#endif
