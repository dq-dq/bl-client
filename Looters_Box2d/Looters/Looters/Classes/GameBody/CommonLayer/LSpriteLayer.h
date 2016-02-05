/***************************************************************
 author:     wangning
 write time: 2012.12.24
 function:   sprite触摸处理
 ***************************************************************/
#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class LSpriteLayer : public CCSprite ,public CCTargetedTouchDelegate {
public:
    LSpriteLayer();
    ~LSpriteLayer();
    virtual bool init();
    
    CREATE_FUNC(LSpriteLayer);
    
    
public:
    //游戏主场景触摸操作
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void onEnter();
    virtual void onExit();
};
