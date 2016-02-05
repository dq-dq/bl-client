//
//  CentralSettingsUILayer.h
//  Looters
//
//  Created by 王 宁 on 13-1-8.
//
//

#ifndef Looters_CentralSettingsUILayer_h
#define Looters_CentralSettingsUILayer_h
#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CentralSettingsUILayer : public CCLayerColor
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
public:
    CentralSettingsUILayer();
    ~CentralSettingsUILayer();
    
    virtual bool init();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CentralSettingsUILayer, create);
    
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
    void initCentralSettingsUI();
    
    // layercolor
    CCLayerColor* layercolorbg;
    
    // sp
    CCSprite*   s_bg;
    
    // btn
    CCControlButton * b_music_on;
    CCControlButton * b_music_off;
    CCControlButton * b_wav_on;
    CCControlButton * b_wav_off;
    CCControlButton * b_close;
    

    void onMusicOn(cocos2d::CCObject * pSender);
    void onMusicOff(cocos2d::CCObject * pSender);
    void onWavOn(cocos2d::CCObject * pSender);
    void onWavOff(cocos2d::CCObject * pSender);
    void onLogin(cocos2d::CCObject * pSender);
    void onAbout(cocos2d::CCObject * pSender);
    void onHelp(cocos2d::CCObject * pSender);
    void onClose(cocos2d::CCObject * pSender);
};


class CentralSettingsUILayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CentralSettingsUILayerLoader, loader);
    CentralSettingsUILayer * centralSettingsUILayer;
public:
    
    
    virtual CentralSettingsUILayer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader)
    {
        centralSettingsUILayer = CentralSettingsUILayer::create();
        return centralSettingsUILayer;
    }
};

#endif
