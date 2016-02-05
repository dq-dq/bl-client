//
//  DialogLayer.h
//  Looters
//
//  Created by yisuode on 12-11-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef Looters_DialogLayer_h
#define Looters_DialogLayer_h
#pragma once
#include "cocos2d.h"
USING_NS_CC;
class DialogLayer: public CCLayerColor
{  
    // 模态对话框菜单  
    CCMenu *m_pMenu;
    
public:  
    DialogLayer();
    ~DialogLayer();  
    
    virtual bool init();
    // 初始化对话框内容
    void initDialog();
    
    CREATE_FUNC(DialogLayer);
    void onEnter();  
    void onExit();  
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);  
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);  
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);  
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);  
    
    
    CCLabelTTF*  content;
    void setMenuItem(CCNode *node,SEL_MenuHandler selectorcancel,SEL_MenuHandler selectorok);
    void setShopMenuItem(CCNode *node,SEL_MenuHandler selectorcancel,SEL_MenuHandler selectorok);
    void setGemMenuItem(CCNode *node,SEL_MenuHandler selectorcancel,SEL_MenuHandler selectorok,int _gem);
    void setContentString(std::string content_);
};

#endif
