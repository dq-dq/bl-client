///***************************************************************
// author:     wangning
// write time: 2012.12.28
// function:   游戏loading
// ***************************************************************/
#pragma once
#include "cocos2d.h"
using namespace cocos2d;


class LoadingLayer :public CCLayer
{
public:
	LoadingLayer();
	~LoadingLayer();

	static void ShowLoadingLayer(CCScene* scene);
	static void HideLoadingLayer( void );

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	bool init( CCScene* scene );
};