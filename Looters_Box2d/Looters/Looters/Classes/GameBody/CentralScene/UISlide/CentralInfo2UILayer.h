//
//  CentralInfo2UILayer.h
//  Looters
//
//  Created by yisuode on 13-1-8.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//  一般建筑的信息

#ifndef Looters_CentralInfo2UILayer_h
#define Looters_CentralInfo2UILayer_h

#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;



class CentralInfo2UILayer : public CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
,public cocos2d::extension::CCTableViewDataSource
,public cocos2d::extension::CCTableViewDelegate
{
public:
    CentralInfo2UILayer();
    ~CentralInfo2UILayer();
    
    virtual bool init();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CentralInfo2UILayer, create);
    
    //按钮
    void onClose(cocos2d::CCObject * pSender);
    void onUpDataLevel(cocos2d::CCObject * pSender);
    
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
    
    //列表    
public:    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
    void deleteTableView(); //删除列表
    void addTableView();    //添加列表
    
    CCTableView*        tableView;
    CCArray*            spriteArr;
    
    
public:  
    
    //精灵
        
    CCSprite*      s_icon_bg;
    
    CCSprite*      s_info_icon1; 
    CCSprite*      s_info_bg1; 
    CCSprite*      s_info1; 
    
    CCSprite*      s_info_icon2; 
    CCSprite*      s_info_bg2; 
    CCSprite*      s_info2;
    
    CCSprite*      s_info_icon3; 
    CCSprite*      s_info_bg3; 
    CCSprite*      s_info3;
    
    CCSprite*      s_info_xian1; 
    CCSprite*      s_info_xian2;
    CCSprite*      s_info_xian3;
    
    //
    CCSprite*      s_info_lbg1;
    CCSprite*      s_info_lbg2;
    CCSprite*      s_info_lbg3;
    CCSprite*      s_updata_timebg;
    CCSprite*      s_updata_hong;
    
    
    
    //文字
    
    CCLabelTTF*    l_buildName;
    
    CCLabelTTF*    l_info1;
    CCLabelTTF*    l_info2;
    CCLabelTTF*    l_info3;
    
    CCLabelTTF*    l_bg;
    
    
    CCLabelTTF*    l_info_name1;
    CCLabelTTF*    l_info_name2;
    CCLabelTTF*    l_info_name3;
    CCLabelTTF*    l_info_num1;
    CCLabelTTF*    l_info_num2;
    CCLabelTTF*    l_info_num3;
    CCLabelTTF*    l_bg2;
    
    //升级界面
    CCLabelTTF*    l_updata_timebiaoti;
    CCLabelTTF*    l_updata_time;
    CCLabelTTF*    l_updata_text;
    
    
    //按钮
    CCControlButton*    btn_updatalevel;
    
    
    CCSprite*       updatalevelGHui;
    CCSprite*       updatalevelP;
    CCSprite*       updatalevelPHui;
    CCLabelTTF*      resourcesNumLabel; //资源数

public:
    //隐藏所有UI
    void allinfoUINo();
    
    //初始化info ui
    void infoUILayer();
    
    //初始化updata ui
    void updataUILayer();
    
    //刷新方法
    void updata(float _time);
    
    //刷新资源
    void updataResources();
    
    //初始化篝火兵
    int initTROOPHOUSING();
};



class CentralInfo2UILayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CentralInfo2UILayerLoader, loader);
    CentralInfo2UILayer * centralInfo2UILayer;
public:
    
    
    virtual CentralInfo2UILayer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader)
    {
        centralInfo2UILayer = CentralInfo2UILayer::create();
        return centralInfo2UILayer; 
    }
};

#endif
