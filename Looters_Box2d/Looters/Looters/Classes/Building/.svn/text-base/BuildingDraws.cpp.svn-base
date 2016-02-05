
#include "BuildingBase.h"
#include "GameControl.h"
#include "TipNode.h"
#include "Until.h"
#include "CommonResource.h"

void BuildingBase::drawBuild(string _str)
{
    sprite_ = CCSprite::create(GAME_FILE_TRANSFORM(_str.c_str(),".png").c_str());
    sprite_->setPosition(ccp(0,0));
    sprite_->setAnchorPoint(ccp(0.5,0.5));
    sprite_->setScale(UNIT_Texture_scale_2048x1536);
    CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    data->m_tmxMap->addChild(this->sprite_);
    
    
    drawArrow();
    if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enCentralViewMode != CENTRALVIEW_BATTLE) {
        drawAttackArea();
    }
    
    IsShowSubstrateArrow(false);
    IsShowAttackArea(false);
}

void BuildingBase::drawNameLabel( CCSprite* _parentNode,const char* _name )
{
    nameLabel = CCLabelTTF::create(_name, "Helvetica", 12);
    nameLabel->setAnchorPoint(ccp(0.5,0.5));
    nameLabel->setPosition(ccp(sprite_->getContentSize().width/2, sprite_->getContentSize().height));
    _parentNode->addChild(nameLabel,100,100);
    nameLabel->setVisible(false);
}


void BuildingBase::drawSymbol(CCObject* target, SEL_MenuHandler selector1, SEL_MenuHandler selector2  )
{
    
    CCPoint centerP = ccp(0,0);
    CCPoint offset = ccp(m_pSubstrateBottom->getContentSize().width/2,m_pSubstrateBottom->getContentSize().height/2);
    CCPoint pointT = ccpAdd(ccp(0,centerP.y+BUILDINTBASEGRID_HEIGHT*(m_stBuildSubstrate.m_Line/2.0)),offset);
    
    CCSprite *m_pSymbolOK1  = CCSprite::createWithSpriteFrameName("ui_public_btn_ok.png");
    
    CCSprite *m_pSymbolOK2  = CCSprite::createWithSpriteFrameName("ui_public_btn_ok.png");
    
	CCSprite *m_pSymbolCancel1 = CCSprite::createWithSpriteFrameName("ui_public_btn_closed.png");
    
    CCSprite *m_pSymbolCancel2 = CCSprite::createWithSpriteFrameName("ui_public_btn_closed.png");
    
    
    CCMenuItemSprite* item1 = CCMenuItemSprite::create(m_pSymbolOK1, m_pSymbolOK2, target, selector2);
    
    item1->setPosition(ccp(sprite_->getContentSize().width,sprite_->getContentSize().height+10));
    item1->setScale(1);
    CCMenuItemSprite* item2 = CCMenuItemSprite::create(m_pSymbolCancel1, m_pSymbolCancel2, target, selector1);
    item2->setPosition(ccp(0,sprite_->getContentSize().height+10));
    item2->setScale(1);
    menu = CCMenu::create( item1,item2, NULL);
    
    menu->setPosition(ccp(0,0));
    sprite_->addChild( menu ,10);
}
void BuildingBase::removeSymbol()
{
    sprite_->removeChild(menu, false);
}

void BuildingBase::drawArrow( void )
{
    if( m_pSpriteBuildArrow[0] != NULL )
	{
		for( int i = 0; i < 4; i++ )
		{
			m_pSpriteBuildArrow[i]->removeFromParentAndCleanup(true);
			m_pSpriteBuildArrow[i] = NULL;
		}
	}
	
    
    m_pSpriteBuildArrow[0] = CCSprite::createWithSpriteFrameName("ui_map_btn_jiantou1.png");//左上
    m_pSpriteBuildArrow[0]->setFlipX(true);
	m_pSpriteBuildArrow[0]->setAnchorPoint(ccp(1,0));
	m_pSpriteBuildArrow[0]->setPosition(ccp(BUILDINGBASEGRID_WIDTH*1*GetLine()-BUILDINGBASEGRID_WIDTH*GetLine()/2,BUILDINTBASEGRID_HEIGHT*1*GetRow()+BUILDINTBASEGRID_HEIGHT*GetRow()/2));
	m_pSubstrateBottom->addChild(m_pSpriteBuildArrow[0]);
    
    m_pSpriteBuildArrow[1] = CCSprite::createWithSpriteFrameName("ui_map_btn_jiantou1.png");//右上
	m_pSpriteBuildArrow[1]->setAnchorPoint(ccp(0,0));
	m_pSpriteBuildArrow[1]->setPosition(ccp(BUILDINGBASEGRID_WIDTH*1*GetLine()+BUILDINGBASEGRID_WIDTH*GetLine()/2,BUILDINTBASEGRID_HEIGHT*1*GetRow()+BUILDINTBASEGRID_HEIGHT*GetRow()/2));
	m_pSubstrateBottom->addChild(m_pSpriteBuildArrow[1]);
    
    m_pSpriteBuildArrow[2] = CCSprite::createWithSpriteFrameName("ui_map_btn_jiantou2.png");//右下
    m_pSpriteBuildArrow[2]->setFlipX(true);
	m_pSpriteBuildArrow[2]->setAnchorPoint(ccp(0,1));
	m_pSpriteBuildArrow[2]->setPosition(ccp(BUILDINGBASEGRID_WIDTH*1*GetLine()+BUILDINGBASEGRID_WIDTH*GetLine()/2,BUILDINTBASEGRID_HEIGHT*1*GetRow()-BUILDINTBASEGRID_HEIGHT*GetRow()/2));
	m_pSubstrateBottom->addChild(m_pSpriteBuildArrow[2]);
    
    m_pSpriteBuildArrow[3] = CCSprite::createWithSpriteFrameName("ui_map_btn_jiantou2.png");//左下
	m_pSpriteBuildArrow[3]->setAnchorPoint(ccp(1,1));
	m_pSpriteBuildArrow[3]->setPosition(ccp(BUILDINGBASEGRID_WIDTH*1*GetLine()-BUILDINGBASEGRID_WIDTH*GetLine()/2,BUILDINTBASEGRID_HEIGHT*1*GetRow()-BUILDINTBASEGRID_HEIGHT*GetRow()/2));
	m_pSubstrateBottom->addChild(m_pSpriteBuildArrow[3]);
    
}

void BuildingBase::drawAttackArea( void )
{
    if (m_pSpriteAttackArea != NULL) {
        m_pSpriteAttackArea->removeAllChildrenWithCleanup(true);
        m_pSpriteAttackArea = NULL;
    }
    m_pSpriteAttackArea = CCSprite::create(GAME_FILE_TRANSFORM("build_attackarea_01",".png").c_str());
    m_pSpriteAttackArea->setPosition(sprite_->getPosition());
    CCSize rng = m_pSpriteAttackArea->getContentSize();
    float scalex = AttackRange*2/rng.width;
    float scaley = AttackRange*2*0.5f/rng.height;
    m_pSpriteAttackArea->setScaleX(scalex);
    m_pSpriteAttackArea->setScaleY(scaley);
    
    //如果是巨炮 设置其盲区范围
    if(getTypeID() == DEFENSE_MORTAR)
    {
        CCSprite* childSprite = CCSprite::create(GAME_FILE_TRANSFORM("build_attackarea_02",".png").c_str());
        childSprite->setPosition(sprite_->getPosition());
        CCSize rng = childSprite->getContentSize();
        float scalex1 = blindRange*2/rng.width;
        float scaley1 = blindRange*2*0.5f/rng.height;
        childSprite->setScaleX(scalex1/scalex);
        childSprite->setScaleY(scaley1/scaley);
        childSprite->setPosition(ccp(m_pSpriteAttackArea->getContentSize().width/2,m_pSpriteAttackArea->getContentSize().height/2));
        
        m_pSpriteAttackArea->addChild(childSprite);
    }
    
    
    //加入到地图上 并设置z值 Z_ATTACKAREA_
    CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    data->m_tmxMap->addChild(m_pSpriteAttackArea,Z_ATTACKAREA_);
}

void BuildingBase::replaceSprite_(const char *pszFileName)
{
    CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    data->m_tmxMap->removeChild(this->sprite_, false);
    this->sprite_ = NULL;
    this->sprite_ = CCSprite::create(pszFileName);
    data->m_tmxMap->addChild(this->sprite_);
    
    char strName[64];
    sprintf(strName,"%s \nlevel%d",this->getName().c_str(),this->lv);
    this->drawNameLabel(this->sprite_,strName);
}


void BuildingBase::IsShowSubstrateArrow( bool bIs )
{
    if (m_uTypeID >= BUILDINGTYPE_DEFENSE && m_uTypeID < BUILDINGTYPE_WALL)
    {
        IsShowAttackArea(bIs);
    }
    
    if( m_pSpriteBuildArrow[0]->isVisible() != bIs )
	{
		for( int i = 0; i < 4; i++ )
		{
			m_pSpriteBuildArrow[i]->setVisible(bIs);
		}
	}
}

void BuildingBase::IsShowAttackArea( bool bIs )
{
    if(m_pSpriteAttackArea && m_pSpriteAttackArea->isVisible() != bIs)
    {
        m_pSpriteAttackArea->setVisible(bIs);
    }
}

void BuildingBase::IsShowSubstrateFace( bool bIs )
{
	if( m_pSubstrateBottom->isVisible() != bIs )
	{
		m_pSubstrateBottom->setVisible( bIs );
	}
}

void BuildingBase::SetRedSubstrateFace( void )
{
	ccColor3B color = ccc3( 255,0,0 );
	m_pSubstrateBottom->setColor(color);
}

void BuildingBase::SetGreenSubstrateFace( void )
{
	ccColor3B color = ccc3( 0,255,0 );
	m_pSubstrateBottom->setColor(color);
}

void BuildingBase::IsShowDefenceCharacters( bool bIs)
{
    if (defenderCharacterArr) {
        for (int i=0; i<defenderCharacterArr->count(); i++) {
            Unit* childU = (Unit*)defenderCharacterArr->objectAtIndex(i);
            childU->ani_state_->m_pCharSprite->setVisible(bIs);
        }
    }
}

void BuildingBase::IsShowBuildName( bool bIs )
{
    if (nameLabel) {
        nameLabel->setVisible(bIs);
    }
}
