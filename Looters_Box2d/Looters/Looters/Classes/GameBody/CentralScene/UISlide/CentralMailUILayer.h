
//
//  CentralPVPUILayer.h
//  Looters
//
//  Created by yisuode on 12-11-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef Looters_CentralMailUILayer_h
#define Looters_CentralMailUILayer_h

#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CentralMailItemLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CentralMailUILayer : public CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCTableViewDataSource
, public cocos2d::extension::CCTableViewDelegate
{
public:
    CentralMailUILayer();
    ~CentralMailUILayer();
    
    virtual bool init();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CentralMailUILayer, create);
    
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
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

    
    void deleteTableView(); //删除列表
    void addTableView();    //添加列表
    
    CCTableView*        tableView;

    
public:
    void initCentralMailUI();
    CCNode* itemMailNode(std::string itemname_,int tag_,CCPoint pos_);
    
    CCArray* itemArr;
    // sp
    CCSprite*   s_ui_mail_demolitionsjournal;
    CCSprite*   s_ui_mail_journal;
    
    // btn
    CCControlButton*   b_ui_mail_demolitionsjournal_bgdark;
    CCControlButton*   b_ui_mail_demolitionsjournal_bglight;
    CCControlButton*   b_ui_mail_journal_bglight;
    CCControlButton*   b_ui_mail_journal_bgdark;
    

    
    void onDemolitionsDark(cocos2d::CCObject * pSender);
    void onDemolitionsLight(cocos2d::CCObject * pSender);
    void onJournalLight(cocos2d::CCObject * pSender);
    void onJournalDark(cocos2d::CCObject * pSender);
    
    
    void onClose(cocos2d::CCObject * pSender);
    
    CentralMailItemLayer* itemlayer;
};


class CentralMailUILayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CentralMailUILayerLoader, loader);
    CentralMailUILayer * centralMailUILayer;
public:
    
    
    virtual CentralMailUILayer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader)
    {
        centralMailUILayer = CentralMailUILayer::create();
        return centralMailUILayer;
    }
};


#endif
