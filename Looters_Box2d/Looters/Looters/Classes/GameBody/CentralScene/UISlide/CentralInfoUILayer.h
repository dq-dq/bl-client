//
//  CentralInfoUILayer.h
//  Looters
//
//  Created by admin on 12-11-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//  功能信息

#ifndef Looters_CentralInfoUILayer_h
#define Looters_CentralInfoUILayer_h
#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CentralScene.h"

USING_NS_CC;
USING_NS_CC_EXT;


//魔法类型
enum IconState
{
    IconState_normal = 1,               //正常状态
    IconState_LevelLow = 2,             //等级不到
    IconState_LackOfGold = 3,           //钱不够
    IconState_LackOfPotions = 4,        //水不够
    IconState_LackOfGem = 5,            //宝石不够
    IconState_ToOpen = 6,               //为开启
    IconState_Full,                     //队列满
};

//ui类型
enum UIType
{
    UIType_info = 1,              //信息ui
    UIType_build = 2,             //功能ui
    UIType_buildUp,               //建筑升级ui
};


class StateSprite:public cocos2d::CCSprite
{
public:
    int     state;
    int     stableState;
    int     level;
    int     type;
    
};


class CentralInfoUILayer : public CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
public:
    CentralInfoUILayer();
    ~CentralInfoUILayer();
    
    virtual bool init();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CentralInfoUILayer, create);
    
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

    void CloseInfoUI();
    void onnextBtn();
    void onUpDataLevel();
    
    
    CCSprite*      s_bgl1;
    CCSprite*      s_bgl2;
    CCSprite*      s_bgl3;
    
    
    CCSprite*      s_info_icon1;
    CCSprite*      s_info_bg1;
    CCSprite*      s_info1;
    CCSprite*      s_info_lbg1;
    
    CCSprite*      s_info_icon2;
    CCSprite*      s_info_bg2;
    CCSprite*      s_info2;
    CCSprite*      s_info_lbg2;
    
    CCSprite*      s_info_icon3;
    CCSprite*      s_info_bg3;
    CCSprite*      s_info3;
    CCSprite*      s_info_lbg3;
    
    CCSprite*      s_info_lbg;
    CCSprite*      s_info_tubg;
    
    CCControlButton* nextBtn;
    
    
    
    
    //文字
    CCLabelTTF*    l_tishi;
    CCLabelTTF*    l_biaoti;
    
    
    
    CCLabelTTF*    l_info1;
    CCLabelTTF*    l_info2;
    CCLabelTTF*    l_info3;
    
    CCLabelTTF*    l_info_mubiao;
    CCLabelTTF*    l_info_leixing;
    CCLabelTTF*    l_info_duixiang;
    CCLabelTTF*    l_info_renkou;
    CCLabelTTF*    l_info_shijian;
    CCLabelTTF*    l_info_shudu;
    
    CCLabelTTF*    l_info_mubiaonum;
    CCLabelTTF*    l_info_leixingnum;
    CCLabelTTF*    l_info_duixiangnum;
    CCLabelTTF*    l_info_renkounum;
    CCLabelTTF*    l_info_shijiannum;
    CCLabelTTF*    l_info_shudunum;
    
    
    
    
    
    //科技升级
    CCLabelTTF*    l_info_time;
    CCLabelTTF*    l_info_timebiaoti;
    CCSprite*    s_info_timebg;
    CCControlButton* updatalevel;
    //隐藏所有UI
    void allinfoUINo();
public:
    
    //初始化ui
    void infoUILayer(int _type,int _uiType);
    
    //初始化infoUI
    void infoLayer();
    
    //初始化魔法
    void infoMagic();
    
    //初始化升级
    void infoUpSoldiers();
    //清空升级UI
    void reomUpSoldiers();
    //恢复升级UI
    void huifuUpSoldiers();
    //初始化准备界面
    void infoUpSoldiersZunbei();
    //初始化升级中界面
    void infoUpSoldiersing();
    //清空升级中UI
    void reomUpSoldiersing();
    
    //初始化兵营
    void infoBarracks();
    //清除兵营
    void reomBarracks();
    //恢复兵营
    void HuiFuBarracks();
    //初始化士兵信息
    void infoSBarr();
    
    //刷新兵营
    void updateBarracks();
    //获得队列长度
    void updatePeopleNum();
    
    //刷新兵营队列数量
    void updateLabel();
    
    void updateMagic();
    
    //刷新魔法队列数量
    void updateMagicLabel();
    
    //刷新兵营状态
    void updateBarracksState();
    
    //刷新魔法状态
    void updateMagicState();
    
    //加速
    void updateSpeedUp();
    
    void speedUP();
    
    bool inSpritePosition(CCSprite* _spr,CCPoint _point);
    
    void onInfoBtnRecruiting1(int _tyep);
    
    void upMroS(int _tyep,bool isMroS);
    
    void addMagic(int _tyep);
    
    StateSprite* getState(int _tyep);
    void addStateSprite(int _tyep);
    void sortingStateSprite();
    
    void updata(float _time);
    
    
    bool isaddbing;
    bool isjianbing;
    float addbing_time;
    float jianbing_time;
    
    void addBing();
    void jianBing();
public:
    cocos2d::extension::CCBAnimationManager *mAnimationManager;
    
    
public:
//    CCLabelTTF*    soldiersNumLabel;
    
    
public:
    int         m_type;
    int         UI_type;                //ui的类别
    bool        iserJi;                 //是否是二级界面

    CCArray*    arrSpr;                 //可能消除的精灵
    CCArray*    arrIcon;
    CCArray*    arrIconM;               //魔法数组
    float       beganTime;      
    bool        isBegan;            
    CCSprite*   m_Sprite;               //选中的图片
    CCSprite*   m_SpriteA;              //减少兵
    int         m_spriteNum;            //选中的类别
    bool        isMroS;                 //是否是魔法
    int         buildLeve;
    
    CCSprite*   btn_SpeedUp;            //加速按钮
    CCLabelTTF *m_timeLabel;              //倒计时
    
    CCLabelTTF *m_AllTimeLabel;         //总时间
    CCLabelTTF *m_AllPeopleLabel;       //总人口
    
    CCArray*    arrAIcon;               //队列数组
    
    int         peopleNum;              //人口数
    int         AllPeopleNum;           //人口总数
    
    int         arrNumS;                 //
};


class CentralInfoUILayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CentralInfoUILayerLoader, loader);
    
public:
    CentralInfoUILayer * centralInfoUILayer;
    
    virtual CentralInfoUILayer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) 
    {
        centralInfoUILayer = CentralInfoUILayer::create();
        return centralInfoUILayer; 
    }
};

#endif
