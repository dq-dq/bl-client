//
//  CentralMailItemLayer.h
//  Looters
//
//  Created by 王 宁 on 13-1-7.
//
//

#ifndef Looters_CentralMailItemLayer_h
#define Looters_CentralMailItemLayer_h

#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CentralData.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CentralMailItemLayer : public CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
public:
    CentralMailItemLayer();
    ~CentralMailItemLayer();
    
    virtual bool init();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CentralMailItemLayer, create);
    
    //按钮
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
public:
    // item
    CCNode*     item_n_item;
    
    // lb
    CCSprite*   item_s_bg;
    CCSprite*   item_s_win;
    CCSprite*   item_s_lose;
    CCSprite*   s_star_01;
    CCSprite*   s_star_02;
    CCSprite*   s_star_03;
    
    
    CCLabelTTF*  item_l_gold;
    CCLabelTTF*  item_l_shui;
    CCLabelTTF*  item_l_time;
    CCLabelTTF*  item_l_lv;
    CCLabelTTF*  item_l_playername;
    
    CCLabelTTF* l_enemy_levelandpvp;
    
    // btn
    CCControlButton* item_b_replay;
    CCControlButton* item_b_normalrevenge;
    CCControlButton* item_b_depthrevenge;
    
    
    void onReplay(cocos2d::CCObject * pSender);
    void onNormalRevenge(cocos2d::CCObject * pSender);
    void onDepthRevenge(cocos2d::CCObject * pSender);
    
    void revengeBattleRequest_callback();
    
    
    // 初始化显示
    void initMailItemUI(CentralData::BattleInfor info);
    
public:
    CentralData::BattleInfor battleInfo;
};



class CentralMailItemLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CentralMailItemLayerLoader, loader);
    CentralMailItemLayer * centralMailItemLayer;
public:
    
    
    virtual CentralMailItemLayer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader)
    {
        centralMailItemLayer = CentralMailItemLayer::create();
        return centralMailItemLayer;
    }
};

#endif
