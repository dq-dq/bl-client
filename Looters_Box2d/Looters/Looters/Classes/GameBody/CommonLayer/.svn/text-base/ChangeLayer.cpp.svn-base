#include "GameControl.h"
#include "ChangeLayer.h"
ChangeLayer* m_gChangeLayer = NULL;

ChangeLayer::ChangeLayer()
{

}

ChangeLayer::~ChangeLayer()
{
	
}

void ChangeLayer::ShowChangeLayer(CCScene* scene)
{
    if (NotNetworking) {
        return;
    }
	if( scene== NULL )
		return;

	if( m_gChangeLayer == NULL )
	{
		m_gChangeLayer = new ChangeLayer();
		if( m_gChangeLayer->init(scene) )
		{
			m_gChangeLayer->autorelease();
		}
		else
		{
			delete m_gChangeLayer;
			m_gChangeLayer = NULL;
		}
	}
}

void ChangeLayer::HideChangeLayer( void )
{
    if (NotNetworking) {
        return;
    }
	if( m_gChangeLayer )
	{
        
        if (m_gChangeLayer->isclosefinsh) {
            m_gChangeLayer->open_cloud();
        }
        m_gChangeLayer->setIsClosefinish();
	}
}

bool ChangeLayer::isChangeLayer()
{
    if (m_gChangeLayer) {
        return true;
    }else{
        return false;
    }
}

void ChangeLayer::setIsClosefinish()
{
    m_gChangeLayer->isclosefinsh = true;
}

bool ChangeLayer::init(CCScene* scene)
{
    isclosefinsh = false;
    close_cloud();
    scene->addChild(this,300);
	this->setTouchEnabled(true);
    
	return true;
}

void ChangeLayer::registerWithTouchDispatcher( void )
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN, true);
}

bool ChangeLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void ChangeLayer::close_cloud()
{
    CCSize  size = CCDirector::sharedDirector()->getWinSize();
    
    cloud_left_right_01 = CCSprite::create("cloud_left_right_01.png");
    cloud_left_right_01->setPosition(ccp(-200,-200));
    cloud_left_right_01->setScale(2.0f);
    this->addChild(cloud_left_right_01,50000);
    CCActionInterval *left_right_01_1 = CCMoveTo::create(0.5f, ccp(60,130));
    CCFiniteTimeAction* myseq1 = CCSequence::create(left_right_01_1,NULL);

    
    cloud_right_left_01 = CCSprite::create("cloud_right_left_01.png");
    cloud_right_left_01->setPosition(ccp(size.width +100,size.height+100));
    cloud_right_left_01->setScale(2.0f);
    this->addChild(cloud_right_left_01,50000);
    CCActionInterval *right_left_01_1 = CCMoveTo::create(0.5f, ccp(300,200));
    CCFiniteTimeAction* myseq2 = CCSequence::create(right_left_01_1,CCCallFuncND::create(this, callfuncND_selector(ChangeLayer::close_finish), NULL),NULL);
    

    cloud_left_right_01->runAction(myseq1);
    cloud_right_left_01->runAction(myseq2);

}
void ChangeLayer::open_cloud()
{
    CCSize  size = CCDirector::sharedDirector()->getWinSize();

    CCActionInterval *left_right_01_1 = CCMoveTo::create(1.3f, ccp(-200,-200));
    CCFiniteTimeAction* myseq1 = CCSequence::create(left_right_01_1,NULL);
    
    
    CCActionInterval *right_left_01_1 = CCMoveTo::create(1.3f, ccp(size.width +100,size.height+100));
    CCFiniteTimeAction* myseq2 = CCSequence::create(right_left_01_1,CCCallFuncND::create(this, callfuncND_selector(ChangeLayer::open_finish), NULL),NULL);
    
    cloud_left_right_01->runAction(myseq1);
    cloud_right_left_01->runAction(myseq2);
}

void ChangeLayer::close_finish(CCNode* sender,void* u)
{
    if (isclosefinsh) {
        open_cloud();
    }else{
        isclosefinsh = true;
    }
}

void ChangeLayer::open_finish( CCNode* sender,void* u )
{
    this->unscheduleUpdate();
    this->unscheduleAllSelectors();
    m_gChangeLayer->removeFromParentAndCleanup(true);
    m_gChangeLayer = NULL;
}