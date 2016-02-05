#include "GameControl.h"
#include "LoadingLayer.h"
LoadingLayer* m_gLoadingLayer = NULL;

LoadingLayer::LoadingLayer()
{

}

LoadingLayer::~LoadingLayer()
{
	
}

void LoadingLayer::ShowLoadingLayer(CCScene* scene)
{
    if (NotNetworking) {
        return;
    }
	if( scene== NULL )
		return;

	if( m_gLoadingLayer == NULL )
	{
		m_gLoadingLayer = new LoadingLayer();
		if( m_gLoadingLayer->init(scene) )
		{
			m_gLoadingLayer->autorelease();
		}
		else
		{
			delete m_gLoadingLayer;
			m_gLoadingLayer = NULL;
		}
	}
}

void LoadingLayer::HideLoadingLayer( void )
{
    if (NotNetworking) {
        return;
    }
	if( m_gLoadingLayer )
	{
		m_gLoadingLayer->removeFromParentAndCleanup(true);
		m_gLoadingLayer = NULL;
	}
}

bool LoadingLayer::init(CCScene* scene)
{    
    CCSprite *loading = CCSprite::create("loading-960x640.png");
    loading->setAnchorPoint(ccp(0,0));
    loading->setPosition(ccp(0,0));
    this->addChild(loading,50000);
    scene->addChild(this,300);
	this->setTouchEnabled(true);
    
	return true;
}

void LoadingLayer::registerWithTouchDispatcher( void )
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN, true);
}

bool LoadingLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

