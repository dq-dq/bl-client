
//
//  CentralPVPUILayer.cpp
//  Looters
//
//  Created by yisuode on 12-11-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CentralMailUILayer.h"
#include "cocos2d.h"
#include "GameControl.h"
#include "CentralMailItemLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define tableViewW  418
#define tableViewH  250

CentralMailUILayer::CentralMailUILayer()
: s_ui_mail_demolitionsjournal(NULL)
, s_ui_mail_journal(NULL)
, b_ui_mail_demolitionsjournal_bgdark(NULL)
, b_ui_mail_demolitionsjournal_bglight(NULL)
, b_ui_mail_journal_bglight(NULL)
, b_ui_mail_journal_bgdark(NULL)
, itemlayer(NULL)
{
    
}

CentralMailUILayer::~CentralMailUILayer()
{
    CC_SAFE_RELEASE(s_ui_mail_demolitionsjournal);
    CC_SAFE_RELEASE(s_ui_mail_journal);
    CC_SAFE_RELEASE(b_ui_mail_demolitionsjournal_bgdark);
    CC_SAFE_RELEASE(b_ui_mail_demolitionsjournal_bglight);
    CC_SAFE_RELEASE(b_ui_mail_journal_bglight);
    CC_SAFE_RELEASE(b_ui_mail_journal_bgdark);
    
    this->deleteTableView();
    itemArr->release();
}

bool CentralMailUILayer::init( void )
{
	if( !CCLayer::init() )
		return false;
    
    return true;
}

SEL_MenuHandler CentralMailUILayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget,CCString * pSelectorName){
    return NULL;
}

SEL_CCControlHandler CentralMailUILayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName){
    
    //Bind CCControl Events
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onDemolitionsDark",CentralMailUILayer::onDemolitionsDark);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onDemolitionsLight",CentralMailUILayer::onDemolitionsLight);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onJournalLight",CentralMailUILayer::onJournalLight);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onJournalDark",CentralMailUILayer::onJournalDark);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClose",CentralMailUILayer::onClose);
    return NULL;
}

bool CentralMailUILayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode){
    
    //Bind variables
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_ui_mail_demolitionsjournal", CCSprite *, this->s_ui_mail_demolitionsjournal);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_ui_mail_journal", CCSprite *, this->s_ui_mail_journal);
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "b_ui_mail_demolitionsjournal_bgdark", CCControlButton*, this->b_ui_mail_demolitionsjournal_bgdark);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "b_ui_mail_demolitionsjournal_bglight", CCControlButton *, this->b_ui_mail_demolitionsjournal_bglight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "b_ui_mail_journal_bglight", CCControlButton *, this->b_ui_mail_journal_bglight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "b_ui_mail_journal_bgdark", CCControlButton *, this->b_ui_mail_journal_bgdark);
    return false;
    
}


void CentralMailUILayer::onNodeLoaded(CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader){
    //检测scene
    
    CCLOG("MainScene loading.....successed!") ;
}


void CentralMailUILayer::onEnter()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
    
    CCNode::onEnter();
}

void CentralMailUILayer::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    CCNode::onExit();
}


bool CentralMailUILayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLOG("响应啦........................................");
    return true;
}

void CentralMailUILayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralMailUILayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralMailUILayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}


CCNode* CentralMailUILayer::itemMailNode(string itemname_,int tag_,CCPoint pos_)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    CentralMailItemLayerLoader* centralMailItemLayerLoader = CentralMailItemLayerLoader::loader();
    CentralMailItemLayer *      m_pCentralMailItemLayer = (CentralMailItemLayer*) pCentralScene->openTest(GAME_FILE_TRANSFORM("UI_Mail_Item",".ccbi").c_str(),"UI_Mail_Item",centralMailItemLayerLoader);
    m_pCentralMailItemLayer->setPosition(pos_);
    m_pCentralMailItemLayer->initMailItemUI(pCentralScene->m_pCentralData->m_BattleInfoList.at(tag_));
    
    return m_pCentralMailItemLayer;
}

void CentralMailUILayer::initCentralMailUI()
{
    itemArr = CCArray::create();
    itemArr->retain();
    
    if(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_BattleInfoList.size() == 0) return;
    
    tableView = NULL;
    for (int i=0; i<SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_BattleInfoList.size(); i++) {
        char framename[256] = {0};
        sprintf(framename,"UI_Mail_Item1%d",i);
        CCNode * node = this->itemMailNode(framename,i,ccp(0,0));
        itemArr->addObject(node);
    }
   
    addTableView();
}


void CentralMailUILayer::onDemolitionsDark(cocos2d::CCObject * pSender)
{
    CCLog("");
}
void CentralMailUILayer::onDemolitionsLight(cocos2d::CCObject * pSender)
{
    CCLog("");
}
void CentralMailUILayer::onJournalLight(cocos2d::CCObject * pSender)
{
    CCLog("");
}
void CentralMailUILayer::onJournalDark(cocos2d::CCObject * pSender)
{
    CCLog("");
}


void CentralMailUILayer::onClose(cocos2d::CCObject * pSender)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    pCentralScene->m_pCentralUILayer->setVisible(true);
    
    
    pCentralScene->removeChild(pCentralScene->m_pCentralMailUILayer, false);
    
    pCentralScene->m_pCentralMailUILayer = NULL;
}



//列表
void CentralMailUILayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
    
    if (itemlayer) {
        itemlayer = NULL;
    }
    itemlayer = (CentralMailItemLayer*)cell->getChildByTag(1);
}

CCSize CentralMailUILayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(418, 123); // w h
}

CCTableViewCell* CentralMailUILayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    if (idx == 0)
    {
        CCLOG("%d",idx);
    }
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        
        CCNode* childNode = (CCNode*)itemArr->objectAtIndex(idx);
        cell->addChild(childNode);
        childNode->setTag(1);
    }else{
        CCNode* childNode = (CCNode*)itemArr->objectAtIndex(idx);
        childNode->removeFromParentAndCleanup(false);
        cell->addChild(childNode);
        childNode->setTag(1);
    }
    return cell;
}

unsigned int CentralMailUILayer::numberOfCellsInTableView(CCTableView *table)
{
    CCLog("%d",SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_BattleInfoList.size());
    return SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_BattleInfoList.size();
}

void CentralMailUILayer::deleteTableView()
{
    if (tableView != NULL) 
    {
        tableView->removeFromParentAndCleanup(false);
        tableView = NULL;
    }
}

void CentralMailUILayer::addTableView()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    tableView = CCTableView::create(this, CCSizeMake(418, 250));
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setPosition(ccp(30,22));
    tableView->setDelegate(this);
    tableView->reloadData();
    
    pCentralScene->m_pCentralMailUILayer->addChild(tableView);
}





