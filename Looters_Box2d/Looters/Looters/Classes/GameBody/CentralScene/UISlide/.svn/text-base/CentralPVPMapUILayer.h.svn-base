/***************************************************************
 author:     wangning
 write time: 2012.11.30
 function:   游戏战斗场景界面
 ***************************************************************/
#ifndef Looters_CentralPVPMapUILayer_h
#define Looters_CentralPVPMapUILayer_h

#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CentralData.h"
#include "DialogLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define CentralPVPMapUI_ICON_Y 6.0f

class IconSprite_CentralPVPMapUI:public cocos2d::CCSprite
{
public:
    int iconID;
};

class CentralPVPMapUILayer : public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
public:
    CentralPVPMapUILayer();
    ~CentralPVPMapUILayer();
    
    virtual bool init();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CentralPVPMapUILayer, create);
        
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    //界面button按钮
    void onCancel(cocos2d::CCObject * pSender);
    void onNext(cocos2d::CCObject * pSender);
    void onEnd(cocos2d::CCObject * pSender);
    
    //界面精灵
    CCSprite*   soldiersIcon_bg;
    
    CCSprite*   s_potions;
    CCSprite*   s_gold;
    
    CCSprite*  s_mplayerCutTrophy;
    CCSprite*  s_mplayerAddTrophy;
    CCSprite*  s_mplayerPotions;
    CCSprite*  s_mplayerGold;
    CCSprite*  s_mplayerName;
    
    CCSprite*  s_star_01;
    CCSprite*  s_star_02;
    CCSprite*  s_star_03;
    
    //界面文字
    CCLabelTTF*  l_tipHelp;
    CCLabelTTF*  l_countdown;
    CCLabelTTF*  l_tipWarning;
    CCLabelTTF*  l_gem;
    CCLabelTTF*  l_potions;
    CCLabelTTF*  l_gold;
    
    CCLabelTTF*  l_potionsmax;
    CCLabelTTF*  l_goldmax;
    
    CCLabelTTF*  l_mplayerCutTrophy;
    CCLabelTTF*  l_mplayerAddTrophy;
    CCLabelTTF*  l_mplayerPotions;
    CCLabelTTF*  l_mplayerGold;
    CCLabelTTF*  l_mplayerName;
    
    CCLabelTTF*  l_overallDamage;
    CCLabelTTF*  l_mathplayer_lv;
    
    CCLabelTTF* l_seek_playergold;
    
    
    //查找下一个玩家
    CCControlButton* b_next;
    //游戏取消
    CCControlButton* b_cancel;
    //游戏结束
    CCControlButton* b_end;
    
    
    // 界面加载完成后初始化
    void initCentralPVPMapUI();
    
    void iconMenuItemCallback(CCObject *pSender);
    // 请求响应后更新界面显示
    void response_CallUI();
    
    
    //进入战斗状态隐藏组件
    void hide_component_Inbattle();
    
    //战斗结束状态隐藏组建
    void hide_component_Inend();
    
    //切换战斗状态
    void change_battlestate(int state_);
    
    float countdown_readytime; //30s准备时间
    float countdown_gametime;  //3min战斗时间
    
    //界面显示刷新
    void update(float dt);
    
    //添加兵，魔法，工会信息
    void addAttackerSoldiersAndSpellList(vector<CentralData::AttackerSoldiersAndSpell*>* list);
    
    //当前选中unitID
    CCMenuItemSprite* selectUnit;
    CCArray* iconArr;
    
    //游戏主场景触摸操作
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    
    //提示label
    CCLabelTTF*  l_tipend;
    
    //提示倒计时3秒
    bool isShowcountdown_3;
    CCSprite * number;
    int numkl;
    void showcountdown_3();
    void noNum();
    
    //战斗已开始点击离开
    void okMenuItemInBattleCallback(CCObject *pSender);
    void cancelMenuItemInBattleCallback(CCObject *pSender);

};



class CentralPVPMapUILayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CentralPVPMapUILayerLoader, loader);
    CentralPVPMapUILayer * centralPVPMapUILayer;
public:
    
    
    virtual CentralPVPMapUILayer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader)
    {
        centralPVPMapUILayer = CentralPVPMapUILayer::create();
        return centralPVPMapUILayer; 
    }
};

#endif
