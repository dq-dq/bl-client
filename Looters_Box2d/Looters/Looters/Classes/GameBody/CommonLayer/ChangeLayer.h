///***************************************************************
// author:     wangning
// write time: 2012.12.28
// function:   游戏loading
// ***************************************************************/
#pragma once
#include "cocos2d.h"
using namespace cocos2d;


class ChangeLayer :public CCLayer
{
public:
	ChangeLayer();
	~ChangeLayer();

	static void ShowChangeLayer(CCScene* scene);
	static void HideChangeLayer( void );

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	bool init( CCScene* scene );
    
    static bool isChangeLayer();
    
    
public:
    CCSprite*  cloud_left_right_01;
    
    CCSprite*  cloud_right_left_01;
    
    
    bool isclosefinsh;
    void setIsClosefinish();
    void close_cloud();
    void open_cloud();
    void close_finish(CCNode* sender,void* u);
    void open_finish(CCNode* sender,void* u);
};