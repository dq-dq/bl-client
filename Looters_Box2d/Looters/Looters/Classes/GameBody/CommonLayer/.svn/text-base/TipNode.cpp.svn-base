//
//  TipNode.cpp
//  Looters
//
//  Created by yisuode on 12-11-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "TipNode.h"
#include "GameData.h"
#include "cocos2d.h"
#include "GameControl.h"
#include "BuildingBase.h"
USING_NS_CC;
TipNode::TipNode()
{
    
}

TipNode::~TipNode()
{
    
}
bool TipNode::init( void )
{
    sprite_ = NULL;
    sprite_ProgressBar = NULL;
    timeLabel = NULL;
    timeLabel2 = NULL;
    sprite_Icon = NULL;
 
    return true;
}
void TipNode::initTipNode(int _buildingType,bool _isup,CCNode* _build)
{
    buildingType = _buildingType;
    isUp = _isup;
    building = _build;
    
    
    if (isUp)
    {
        ProgressBar();
    }
    else
    {
        switch (buildingType)
        {
            case RESOURCE_ELIXIRPUMP:
            {
                CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
                //不用加钱
                
                CCSprite *m_pSprite1  =  NULL;
                CCSprite *m_pSprite2  =  NULL;
                if (pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX == pCentralScene->m_pCentralData->m_Central_UserData->user_potions)
                {
                    m_pSprite1  = CCSprite::createWithSpriteFrameName("ui_map_qipaoPman.png");
                    m_pSprite2  = CCSprite::createWithSpriteFrameName("ui_map_qipaoPman.png");
                }
                else
                {
                    m_pSprite1  = CCSprite::createWithSpriteFrameName("ui_map_qipaoP.png");
                    m_pSprite2  = CCSprite::createWithSpriteFrameName("ui_map_qipaoP.png");
                }
                
                
                CCMenuItemSprite* item1 = CCMenuItemSprite::create(m_pSprite1, m_pSprite2, this, menu_selector(TipNode::menuCollectionResources));
                item1->setPosition(ccp(0,0));
                
              
                m_pMenu = CCMenu::create( item1, NULL);
                m_pMenu->setPosition(ccp(0,0));
                this->addChild( m_pMenu); 
            }
                break;
            case RESOURCE_GOLDMINE:
            {
                CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
                CCSprite *m_pSprite1  =  NULL;
                CCSprite *m_pSprite2  =  NULL;
                if (pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX == pCentralScene->m_pCentralData->m_Central_UserData->user_gold)
                {
                    m_pSprite1  = CCSprite::createWithSpriteFrameName("ui_map_qipaoGman.png");
                    m_pSprite2  = CCSprite::createWithSpriteFrameName("ui_map_qipaoGman.png");
                }
                else
                {
                    m_pSprite1  = CCSprite::createWithSpriteFrameName("ui_map_qipaoG.png");
                    m_pSprite2  = CCSprite::createWithSpriteFrameName("ui_map_qipaoG.png");
                }
                
                CCMenuItemSprite* item1 = CCMenuItemSprite::create(m_pSprite1, m_pSprite2, this, menu_selector(TipNode::menuCollectionResources));
                item1->setPosition(ccp(0,0));
                
                
                m_pMenu = CCMenu::create( item1, NULL);
                m_pMenu->setPosition(ccp(0,0));
                this->addChild( m_pMenu);
                
            }
                break;
            case ARMY_BARRACK:
            {
                if (zhuangtaiType == 1)
                {
                    ProgressBar();
                }
                else if(zhuangtaiType == 2)
                {
                    sprite_  = CCSprite::createWithSpriteFrameName("ui_map_qipaoman.png");
                    sprite_->setPosition(ccp(0, 0));
                    sprite_->setAnchorPoint(ccp(0, 1));
                    this->addChild(sprite_);
                }
                else if(zhuangtaiType == 3)
                {
                    sprite_  = CCSprite::createWithSpriteFrameName("ui_map_qipaokong.png");
                    sprite_->setPosition(ccp(0, 0));
                    sprite_->setAnchorPoint(ccp(0, 1));
                    this->addChild(sprite_);
                }
            }
                break;
            case ARMY_SPELLFORGE:
            {
                ProgressBar();
            }
                break;
            case ARMY_LABORATORY:
            {
                ProgressBar();
            }
                break;
            case ARMY_TROOPHOUSING:
            {

                sprite_ = CCSprite::createWithSpriteFrameName("ui_map_qipaoman.png");
                
                this->addChild(sprite_);
            }
                break;
                
            default:
            {
                
            }
                break;
        }
    }
    
    
    
}
void TipNode::upXiaoIcon(int label)
{
    if (sprite_Icon != NULL)
    {
        this->removeChild(sprite_Icon, false);
        sprite_Icon = NULL;
    }
    sIconType = label;
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GAME_FILE_TRANSFORM("soldiers_Icon",".plist").c_str(),GAME_FILE_TRANSFORM("soldiers_Icon",".png").c_str());
    char strFileName[64];
    sprintf(strFileName,"soldiers_IconXiao%d.png",label);
    sprite_Icon = CCSprite::createWithSpriteFrameName(strFileName);
    sprite_Icon->setPosition(ccp(0, 0));
    sprite_Icon->setAnchorPoint(ccp(1, 0));
    this->addChild(sprite_Icon);
}
void TipNode::upZhuangtaiTyep(int _tyep)
{
    switch (buildingType)
    {
        case RESOURCE_ELIXIRPUMP:
        {
            
        }
            break;
        case RESOURCE_GOLDMINE:
        {
            
        }
            break;
        case ARMY_BARRACK:
        {
            this->removeAllChildrenWithCleanup(false);
            timeLabel2 = NULL;
            timeLabel = NULL;
            sprite_ProgressBar = NULL;
            sprite_ = NULL;
            sprite_Icon = NULL;
            
            zhuangtaiType = _tyep;
            if (zhuangtaiType == 1)
            {
                ProgressBar();
            }
            else if(zhuangtaiType == 2)
            {
                sprite_  = CCSprite::createWithSpriteFrameName("ui_map_qipaoman.png");
                sprite_->setPosition(ccp(0, 0));
                sprite_->setAnchorPoint(ccp(0, 1));
                this->addChild(sprite_);
            }
            else if(zhuangtaiType == 3)
            {
                sprite_  = CCSprite::createWithSpriteFrameName("ui_map_qipaokong.png");
                sprite_->setPosition(ccp(0, 0));
                sprite_->setAnchorPoint(ccp(0, 1));
                this->addChild(sprite_);
            }
            
        }
            break;
        case ARMY_SPELLFORGE:
        {

        }
            break;
        case ARMY_LABORATORY:
        {

        }
            break;
        case ARMY_TROOPHOUSING:
        {
        }
            break;
            
        default:
        {
            
        }
            break;
    }
}
void TipNode::ProgressBar()
{
    
    sprite_ = CCSprite::createWithSpriteFrameName("ui_public_article9.png");
    sprite_->setAnchorPoint(ccp(0,0));
    sprite_->setPosition(ccp(0, 0));
    this->addChild(sprite_);
    
    sprite_ProgressBar = CCSprite::createWithSpriteFrameName("ui_public_article8.png");
    sprite_ProgressBar->setAnchorPoint(ccp(0,0.5));
    sprite_ProgressBar->setPosition(ccp(2, sprite_->getContentSize().height/2));
    sprite_ProgressBar->setScaleX(0);
    this->addChild(sprite_ProgressBar);
    
    //阴影效果
    timeLabel2 = CCLabelTTF::create("", "Helvetica", sprite_ProgressBar->getContentSize().height*2);
    timeLabel2->setAnchorPoint(ccp(0.5,0.2));
    timeLabel2->setColor(ccBLACK);
    timeLabel2->setPosition(ccp(sprite_->getContentSize().width/2+1, sprite_->getContentSize().height-1));
    this->addChild(timeLabel2);
    
    timeLabel = CCLabelTTF::create("", "Helvetica", sprite_ProgressBar->getContentSize().height*2);
    timeLabel->setAnchorPoint(ccp(0.5,0.2));
    timeLabel->setPosition(ccp(sprite_->getContentSize().width/2, sprite_->getContentSize().height));
    this->addChild(timeLabel);
}
void TipNode::upTimeLabel(const char *label)
{
    if (timeLabel)
    {
        timeLabel->setString(label);
        timeLabel2->setString(label);
    }
    
}



void TipNode::upProgressBar(float progressBar)
{
    if (sprite_ProgressBar != NULL)
    {
        sprite_ProgressBar->setScaleX(progressBar);
    }
}

void TipNode::menuCollectionResources(CCObject* sender)
{    
    BuildingBase* build = (BuildingBase*)building;
    switch (build->getTypeID()) {
        case RESOURCE_ELIXIRPUMP:
        {
            build->addResources();
        }
            break;
        case RESOURCE_GOLDMINE:
        {
            build->addResources();
        }
            break;
        default:
            break;
    }
}








