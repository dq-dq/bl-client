//
//  CentralUILayer.h
//  Looters
//
//  Created by yisuode on 12-11-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef Looters_CentralUILayer_h
#define Looters_CentralUILayer_h
#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
 

class CentralUILayer : public CCLayer
                    , public cocos2d::extension::CCBMemberVariableAssigner
                    , public cocos2d::extension::CCBSelectorResolver
{
public:
    CentralUILayer();
    ~CentralUILayer();
    
    virtual bool init();
    
    void initUI();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CentralUILayer, create);

    //按钮
    //商店
    void onBtnShop(cocos2d::CCObject * pSender);
    //邮件
    void onBtnMail(cocos2d::CCObject * pSender);
    //设置
    void onSettings(cocos2d::CCObject * pSender);
    //信息
    void onBtnInfo(cocos2d::CCObject * pSender);
    //升级
    void onBtnUpBuild(cocos2d::CCObject * pSender);
    //兵营建造按钮
    void onBtnRecruiting(cocos2d::CCObject * pSender);
    //Attack
    void onBtnPVP(cocos2d::CCObject * pSender);
    //升级兵种
    void onUpSoldiers(cocos2d::CCObject * pSender);
    //建造魔法按钮
    void onMagic(cocos2d::CCObject * pSender);
    //加速建造按钮
    void onBuildGem(cocos2d::CCObject * pSender);
    //取消建筑
    void onBuiltToCancel(cocos2d::CCObject * pSender);
    
    void onCollectG(cocos2d::CCObject * pSender);
    void onCollectP(cocos2d::CCObject * pSender);
    
    void onNAdd(cocos2d::CCObject * pSender);
    void onGAdd(cocos2d::CCObject * pSender);
    void onFAdd(cocos2d::CCObject * pSender);
    
    //没有兵提示
    void noTroops(float time);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    
    
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

    void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);
    
    void ShowBtnAnim(const char * pCCBFileName);
    
    //一般按钮动画
    void InfoBtnAppear(int _tyep, int _Build);
    void InfoBtnDisappear(int _tyep,int _Build);
    
public:
    void updata(float _time);
    
    //加减钱的方法
    bool updateGold(int _num);
    //加减水的方法
    bool updatePotions(int _num);
    //加减宝石的方法
    bool updateGem(int _num);
    //加经验的方法
    bool updateExp(int _num);
    
    void updatePeasant();
    
    void BasisInfo();
    
    void upRUI();
    
    void upResourcesNumLabel();
    
    void vl_nameLeve(bool _isv);
    
    //宝石建造
    void okGemMenuItemInBattle(CCObject *pSender);
    void cancelGemMenuItemInBattle(CCObject *pSender);
    //去商城
    void okShopMenuItemInBattle(CCObject *pSender);
    void cancelShopMenuItemInBattle(CCObject *pSender);
    
    int  gemTyep;
    int  gem_Num;
    int  gem_UUid;
    void addDialogLayer(bool _isG, int _rNum, int _tyep);
    int BuyResourceGem(int _num);
public:
    cocos2d::extension::CCBAnimationManager *mAnimationManager;
    
public:
    CCLabelTTF*    goldLabel;
    CCLabelTTF*    potionsLabel;
    CCLabelTTF*    gemLabel;
    
    CCLabelTTF*    peasantLabel;    //农民数量
    CCLabelTTF*    experienceLabel; //经验数量
    CCLabelTTF*    lvLabel;         //等级
    CCLabelTTF*    pvpLabel;        //pvp数
    CCLabelTTF*    protectLabel;    //保护时间
    CCLabelTTF*    protectLabel2;   //保护时间状态
    CCLabelTTF*    nameLabel;       //玩家昵称
    CCLabelTTF*    goldMaxLabel;    //金币上线
    CCLabelTTF*    potionsMaxLabel; //药水上线
    CCLabelTTF*    peasantLabel2;   //农民状态
    
    CCLabelTTF*    l_nameLeve;      //名称等级
    
    CCSprite*      potionsS;        //水条
    CCSprite*      goldS;           //金币条
    CCSprite*      experienceS;     //经验条
    
    
    CCSprite*      s_icong;         //金币图标
    int            minG;            //起始数
    int            cdG;             //每次数
    bool           isIconG;         //缩放
    
    CCSprite*      s_iconlevel;     //等级图标
    int            minlevel;            //起始数
    int            cdlevel;             //每次数
    
    CCSprite*      s_iconp;         //粮食图标
    int            minP;            //起始数
    int            cdP;             //每次数
    bool           isIconP;         //缩放
    
    CCSprite*      s_icongem;       //宝石图标
    int            minGem;            //起始数
    int            cdGem;             //每次数
    
    CCControlButton* BtnBuildGem;       //宝石加速按钮
    CCLabelTTF*      GemNumLabel;       //宝石数
    
    CCControlButton* BtnResources;      //升级按钮
    CCLabelTTF*      resourcesNumLabel; //资源数
    
    
    CCControlButton* btnCollectP;       //收集资源按钮
    CCControlButton* btnCollectG;
    CCSprite*       CollectGHui;
    CCSprite*       CollectPHui;
    
    float            A_time;            //动画改变
    bool             is_A;              //是否改变
    

};



class CentralUILayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CentralUILayerLoader, loader);
    CentralUILayer * centralUILayer;
public:
    
    
    virtual CentralUILayer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader)
    {
        centralUILayer = CentralUILayer::create();
        return centralUILayer; 
    }
};

#endif
