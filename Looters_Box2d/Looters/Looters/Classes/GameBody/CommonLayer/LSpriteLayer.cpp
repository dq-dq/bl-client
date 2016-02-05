#include "LSpriteLayer.h"

LSpriteLayer::LSpriteLayer()
{
    
}
LSpriteLayer::~LSpriteLayer()
{
    
}

bool LSpriteLayer::init()
{
    if( !CCSprite::init() )
        return false;
    
    return true;
}

void LSpriteLayer::onEnter()
{ 
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
} 

void LSpriteLayer::onExit()
{ 
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this); 
}

bool LSpriteLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchPoint = pTouch->getLocationInView(); 
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    if(true){
        CCLog("");
        
        return true;
    }
    
    return false;
}

void LSpriteLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void LSpriteLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void LSpriteLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

