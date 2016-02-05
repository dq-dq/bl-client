//
//  CentralAccountNameLayer.h
//  Looters
//
//  Created by 王 宁 on 13-1-8.
//
//

#ifndef Looters_CentralAccountNameLayer_h
#define Looters_CentralAccountNameLayer_h

#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CentralAccountNameLayer : public CCLayerColor
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
public:
    CentralAccountNameLayer();
    ~CentralAccountNameLayer();
    
    virtual bool init();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CentralAccountNameLayer, create);
    
    //按钮
    
    
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
    void initCentralAccount1UI();
    
    // sp
    CCSprite*   s_bg;
    CCSprite* name_textfield;
    
    // label
    CCLabelTTF* name_tiplabel;
    CCLabelTTF* name_tiplabel2;
    
    void onOk(cocos2d::CCObject * pSender);
};


class CentralAccountNameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CentralAccountNameLayerLoader, loader);
    CentralAccountNameLayer * centralAccountNameLayer;
public:
    
    
    virtual CentralAccountNameLayer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader)
    {
        centralAccountNameLayer = CentralAccountNameLayer::create();
        return centralAccountNameLayer;
    }
};

#endif
