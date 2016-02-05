//
//  CentralShopUILayer.h
//  Looters
//
//  Created by yisuode on 12-11-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameData.h"
#include "BuyNode.h"
#include "BuyAppC.h"
USING_NS_CC;
USING_NS_CC_EXT;

//生产状态
enum ShopDetectProcess 
{
    ShopDetectProcess_null = 0,
    ShopDetectProcess_Bank = 1,     //
};


enum Resources
{
    Resource_Gems1 = 0,         //500宝石30元
    Resource_Gems2 = 1,         //1200宝石68元
    Resource_Gems3,             //2500宝石128元
    Resource_Gems4,             //6500宝石328元
    Resource_Gems5,             //14000宝石648元
    
    Resource_gold10,            //百分之10的金币
    Resource_gold50,            //百分之50的金币
    Resource_gold100,           //百分之100的金币
        
    Resource_water10,           //百分之10的水
    Resource_water50,           //百分之50的水
    Resource_water100,          //百分之100的水
    
    Resource_end,
};


class IconSprite:public cocos2d::CCSprite
{
public:

    int     type;
    int     num;
    int     gem;
    
    static IconSprite* create(const char *pszFileName)
    {
        IconSprite *pobSprite = new IconSprite();
        if (pobSprite && pobSprite->initWithFile(pszFileName))
        {
            pobSprite->autorelease();
            pobSprite->type = 0;
            pobSprite->num = 0;
            pobSprite->gem = 0;
            return pobSprite;
        }
        CC_SAFE_DELETE(pobSprite);
        return NULL;
    }
    static IconSprite* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
    {
        IconSprite *pobSprite = new IconSprite();
        if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
        {
            pobSprite->autorelease();
            pobSprite->type = 0;
            pobSprite->num = 0;
            pobSprite->gem = 0;
            return pobSprite;
        }
        CC_SAFE_DELETE(pobSprite);
        return NULL;
    }
    
    static IconSprite* createWithSpriteFrameName(const char *pszSpriteFrameName)
    {
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
        
#if COCOS2D_DEBUG > 0
        char msg[256] = {0};
        sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
        CCAssert(pFrame != NULL, msg);
#endif
        
        return createWithSpriteFrame(pFrame);
    }
    
    
};

class CentralShopUILayer : public cocos2d::CCLayer
                    , public cocos2d::extension::CCBMemberVariableAssigner
                    , public cocos2d::extension::CCBSelectorResolver
                    ,public cocos2d::extension::CCTableViewDataSource
                    ,public cocos2d::extension::CCTableViewDelegate
{
public:
    CentralShopUILayer();
    ~CentralShopUILayer();
    
    virtual bool init();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CentralShopUILayer, create);
//UI界面
public:  
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
    
public:   

public:
    void initShopUI();
    
    void onBtnClosedShop(cocos2d::CCObject * pSender);
    void onBtnNextShop(cocos2d::CCObject * pSender);
    
    void onBox1(cocos2d::CCObject * pSender);
    void onBox2(cocos2d::CCObject * pSender);
    void onBox3(cocos2d::CCObject * pSender);
    void onBox4(cocos2d::CCObject * pSender);
    void onBox5(cocos2d::CCObject * pSender);
    void onBox6(cocos2d::CCObject * pSender);
    
    void deleteTableView(); //删除列表
    void addTableView();    //添加列表
    void addBuilding(int unitID);     //购买添加建筑
    
    void menuCall1(CCObject* sender);
    
    void upBuyBuildingArr();    //更新购买建筑的列表
    
    void BoxBtnV(bool _isV);
    
    bool isAllBuild(int _type);
    
    void BuyResource(int _type ,IconSprite* _icon);
    
    int BuyResourceGem(int _num);
    
    IconSprite* initIconSprite(int _type);
//属性    
public:
    CCTableView*        tableView;
    CCControlButton*    nextBtn;
    CCControlButton*    BoxBtn1;
    CCControlButton*    BoxBtn2;
    CCControlButton*    BoxBtn3;
    CCControlButton*    BoxBtn4;
    CCControlButton*    BoxBtn5;
    CCControlButton*    BoxBtn6;
    
    CCLabelTTF*    l_p;
    CCLabelTTF*    l_g;
    CCLabelTTF*    l_gem;
    
    CCControlButton*    testBtn;
    
    CCArray*            spriteArr;
    CCArray*            labelArr;
    const TownHallLevelsData* town;
    TownHallLevelsData   _town;
    
    int                 BtnTyep; 
    
    int                 DetectTyep;
    
    BuyAppC*            buy;
};







class CentralShopUILayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CentralShopUILayerLoader, loader);
    
public:
    CentralShopUILayer * centralShopUILayer;
    
    virtual CentralShopUILayer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
        centralShopUILayer = CentralShopUILayer::create();
        return centralShopUILayer; 
    }

};









