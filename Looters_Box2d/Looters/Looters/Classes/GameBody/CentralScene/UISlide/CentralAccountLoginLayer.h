//
//  CentralAccountLoginLayer.h
//  Looters
//
//  Created by 王 宁 on 13-1-8.
//
//

#ifndef Looters_CentralAccountLoginLayer_h
#define Looters_CentralAccountLoginLayer_h
#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class KeyboardNotificationLayer;


class CentralAccountLoginLayer : public CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
public:
    CentralAccountLoginLayer();
    ~CentralAccountLoginLayer();
    
    virtual bool init();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CentralAccountLoginLayer, create);
    
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
    void initCentralAccount2UI();
    
    // sp
    CCSprite*   s_bg;
    CCSprite* s_account_tf;
    CCSprite* s_password_tf;
    
    void onOk(cocos2d::CCObject * pSender);
    void onSina(cocos2d::CCObject * pSender);
    
public:

    KeyboardNotificationLayer * m_pNotificationLayer;

    KeyboardNotificationLayer * m_pNotificationLayer_password;

    std::string title();
    void addKeyboardNotificationLayer_Username(KeyboardNotificationLayer * pLayer);
    void addKeyboardNotificationLayer_Password(KeyboardNotificationLayer * pLayer);
};


class CentralAccountLoginLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CentralAccountLoginLayerLoader, loader);
    CentralAccountLoginLayer * centralAccountLoginLayer;
public:
    
    
    virtual CentralAccountLoginLayer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader)
    {
        centralAccountLoginLayer = CentralAccountLoginLayer::create();
        return centralAccountLoginLayer;
    }
};

//////////////////////////////////////////////////////////////////////////
// KeyboardNotificationLayer for test IME keyboard notification.
//////////////////////////////////////////////////////////////////////////

class KeyboardNotificationLayer : public CCLayer, public CCIMEDelegate
{
public:
    KeyboardNotificationLayer();
    
    virtual std::string subtitle() = 0;
    virtual void onClickTrackNode(bool bClicked) = 0;
    
    virtual void registerWithTouchDispatcher();
    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);
    
    // CCLayer
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
public:
    CCNode * m_pTrackNode;
    CCPoint  m_beginPos;
    
    
public:
    virtual void setTrackNodePosition(CCPoint pos) = 0;
};

//////////////////////////////////////////////////////////////////////////
// TextFieldTTFDefaultTest for test TextFieldTTF default behavior.
//////////////////////////////////////////////////////////////////////////

class TextFieldTTFDefaultTest : public KeyboardNotificationLayer
{
public:
    // KeyboardNotificationLayer
    virtual std::string subtitle();
    virtual void onClickTrackNode(bool bClicked);
    
    // CCLayer
    virtual void onEnter();
    
    virtual void setTrackNodePosition(CCPoint pos);
};



#endif
