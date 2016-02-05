//
//  TipNode.h
//  Looters
//
//  Created by yisuode on 12-11-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef Looters_TipNode_h
#define Looters_TipNode_h

#pragma once
#include "cocos2d.h"

USING_NS_CC;

class TipNode: public CCNode
{  

public:  
    TipNode();  
    ~TipNode();  
    
    CREATE_FUNC(TipNode); 
    virtual bool init(); 
    
    
    
    
public:  
    //基础图片
    CCSprite*    sprite_;
    
    //进度条
    CCSprite*    sprite_ProgressBar;
    
    //基础图片
    CCSprite*    sprite_Icon;
    
    //记时显示
    CCLabelTTF*  timeLabel;
    CCLabelTTF*  timeLabel2;
    
    //建筑累
    CCNode*   building;
    
    //收获菜单
    CCMenu *m_pMenu;
    
public:  
    //提示类别
    int          buildingType;
    int          zhuangtaiType;
    int          sIconType;
    bool         isUp;
    
public:
    //初始化升级 传入类别和是否是是升级
    void initTipNode(int buildingType,bool _isup,CCNode* _build);
    
    //更新记时显示
    void upTimeLabel(const char *label);
    //进度条的更新 传入百分比
    void upProgressBar(float progressBar);
    
    void menuCollectionResources(CCObject* sender);
    
    //画进度条
    void ProgressBar();
    
    //更新状态显示
    void upZhuangtaiTyep(int _tyep);
    
    void upXiaoIcon(int label);

}; 


#endif
