//
//  DialogLayer.cpp
//  Looters
//
//  Created by yisuode on 12-11-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "DialogLayer.h"
#include "cocos2d.h"
USING_NS_CC;
DialogLayer::DialogLayer():content(NULL)
{
    
}

DialogLayer::~DialogLayer()
{

}
void DialogLayer::onEnter()  
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
    CCNode::onEnter();
    
    initWithColor( ccc4(0,0,0,100) , pDirector->getWinSize().width,pDirector->getWinSize().height);
}

void DialogLayer::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    CCNode::onExit();
}

bool DialogLayer::init( void )
{
	if( !CCLayer::init() )
		return false;
    
    this->initDialog();
    
    return true;
}

void DialogLayer::initDialog()
{
}

bool DialogLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)  
{  
    //m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
    CCLOG("响应啦........................................");
    return true;  
}

void DialogLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)  
{  
}

void DialogLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)  
{  
}

void DialogLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)  
{  
}
void DialogLayer::setShopMenuItem(CCNode *node,SEL_MenuHandler selectorcancel,SEL_MenuHandler selectorok)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *m_pSpritebg  = CCSprite::create("pop-upbox.png");
    m_pSpritebg->setPosition(ccp(size.width/2,size.height/2));
    this->addChild(m_pSpritebg);
    
    CCSprite *m_pSpritecancel_01  = CCSprite::createWithSpriteFrameName("ui_public_btn_closed.png");
    CCSprite *m_pSpritecancel_02  = CCSprite::createWithSpriteFrameName("ui_public_btn_closed.png");
    m_pSpritecancel_02->setScale(1.05f);
    CCMenuItemSprite* item1 = CCMenuItemSprite::create(m_pSpritecancel_01, m_pSpritecancel_02, node, selectorcancel);
    item1->setAnchorPoint(ccp(0,0));
    item1->setPosition(ccp(285 - m_pSpritebg->getContentSize().width/2,197 - m_pSpritebg->getContentSize().height/2));
    
    
    CCSprite *m_pSpriteok_01  = CCSprite::createWithSpriteFrameName("ui_public_btn_jinshop.png");
    CCSprite *m_pSpriteok_02  = CCSprite::createWithSpriteFrameName("ui_public_btn_jinshop.png");
    m_pSpriteok_02->setScale(1.05f);
    CCMenuItemSprite* item2 = CCMenuItemSprite::create(m_pSpriteok_01, m_pSpriteok_02, node, selectorok);
    item2->setAnchorPoint(ccp(1,0));
    item2->setPosition(ccp(270 - m_pSpritebg->getContentSize().width/2,100 - m_pSpritebg->getContentSize().height/2));
    
    
    m_pMenu = CCMenu::create( item1,item2, NULL);
    m_pMenu->setPosition(ccp(0,0));
    
    m_pSpritebg->addChild(m_pMenu);
}
void DialogLayer::setGemMenuItem(CCNode *node,SEL_MenuHandler selectorcancel,SEL_MenuHandler selectorok,int _gem)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *m_pSpritebg  = CCSprite::create("pop-upbox.png");
    m_pSpritebg->setPosition(ccp(size.width/2,size.height/2));
    this->addChild(m_pSpritebg);
    
    CCSprite *m_pSpritecancel_01  = CCSprite::createWithSpriteFrameName("ui_public_btn_closed.png");
    CCSprite *m_pSpritecancel_02  = CCSprite::createWithSpriteFrameName("ui_public_btn_closed.png");
    m_pSpritecancel_02->setScale(1.05f);
    CCMenuItemSprite* item1 = CCMenuItemSprite::create(m_pSpritecancel_01, m_pSpritecancel_02, node, selectorcancel);
    item1->setAnchorPoint(ccp(0,0));
    item1->setPosition(ccp(285 - m_pSpritebg->getContentSize().width/2,197 - m_pSpritebg->getContentSize().height/2));
    
    //620 420
    
    //540 220
    
    CCSprite *m_pSpriteok_01  = CCSprite::createWithSpriteFrameName("ui_public_btn_acceleration.png");
    CCSprite *m_pSpriteok_02  = CCSprite::createWithSpriteFrameName("ui_public_btn_acceleration.png");
    m_pSpriteok_02->setScale(1.05f);
    CCMenuItemSprite* item2 = CCMenuItemSprite::create(m_pSpriteok_01, m_pSpriteok_02, node, selectorok);
    item2->setAnchorPoint(ccp(1,0));
    item2->setPosition(ccp(270 - m_pSpritebg->getContentSize().width/2,100 - m_pSpritebg->getContentSize().height/2));
    
    char strFileName[64];
	sprintf(strFileName,"%d",_gem);
    CCLabelTTF *GemNumLabel = CCLabelTTF::create(strFileName, "Helvetica", 12);
    GemNumLabel->setAnchorPoint(ccp(0,0));
    GemNumLabel->setPosition(ccp(10,10));
    item2->addChild(GemNumLabel,2,2);
    
    m_pMenu = CCMenu::create( item1,item2, NULL);
    m_pMenu->setPosition(ccp(0,0));
    
    m_pSpritebg->addChild(m_pMenu);
}
void DialogLayer::setMenuItem(CCNode *node,SEL_MenuHandler selectorcancel,SEL_MenuHandler selectorok)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *m_pSpritebg  = CCSprite::create("pop-upbox.png");
    m_pSpritebg->setPosition(ccp(size.width/2,size.height/2));
    this->addChild(m_pSpritebg);
    
    CCSprite *m_pSpritecancel_01  = CCSprite::create("pop-upbox_cancel.png");
    CCSprite *m_pSpritecancel_02  = CCSprite::create("pop-upbox_cancel.png");
    m_pSpritecancel_02->setScale(1.05f);
    CCMenuItemSprite* item1 = CCMenuItemSprite::create(m_pSpritecancel_01, m_pSpritecancel_02, node, selectorcancel);
    item1->setAnchorPoint(ccp(0,0));
    item1->setPosition(ccp(35,20));
    
    
    CCSprite *m_pSpriteok_01  = CCSprite::create("pop-upbox_ok.png");
    CCSprite *m_pSpriteok_02  = CCSprite::create("pop-upbox_ok.png");
    m_pSpriteok_02->setScale(1.05f);
    CCMenuItemSprite* item2 = CCMenuItemSprite::create(m_pSpriteok_01, m_pSpriteok_02, node, selectorok);
    item2->setAnchorPoint(ccp(1,0));
    item2->setPosition(ccp(m_pSpritebg->getContentSize().width-35,20));
    
    
    m_pMenu = CCMenu::create( item1,item2, NULL);
    m_pMenu->setPosition(ccp(0,0));
    
    m_pSpritebg->addChild(m_pMenu);
}

void DialogLayer::setContentString(std::string content_)
{
    content = CCLabelTTF::create(content_.c_str(), "Helvetica", 12);
    content->setColor(ccRED);
    this->addChild(content,10000);
    content->setPosition(ccp(250.0f,170.0f));
}
