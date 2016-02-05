/***************************************************************
 author:     wangning
 write time: 2012.10.22
 function:   游戏主场景地图操控操作
 ***************************************************************/
#include <iostream>
#include "CentralLayer.h"
#include "GameControl.h"
#include "cocos2d.h"

void CentralLayer::mapTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    
}


void CentralLayer::mapTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    //CCSize mapSize = CCSizeMake(m_nodeArena->getContentSize().width,m_nodeArena->getContentSize().height);
    CCSize mapSize = CCSizeMake(MAPGLWIDTH,MAPGLHEIGHT);
    switch (pTouches->count())
    {
        case 1:
        {//move
//            CCLog("move--------------------------");
            CCSetIterator it;
            CCTouch* touch = NULL;
            for( it = pTouches->begin(); it != pTouches->end(); it++) 
            {
                touch = (CCTouch*)(*it);
                if(!touch)
                    break;
                
                int iViewID = touch->getID();
                if( iViewID == 0 ){
                    break;
                }
            }
            
            if (touch != NULL) {
                initialDistance = 0.0; 
                finalDistance = 0.0;
                
                
                CCPoint touchLocation = touch->getLocationInView();
                CCPoint prevLocation = touch->getPreviousLocationInView();
                
                touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
                prevLocation = CCDirector::sharedDirector()->convertToGL(prevLocation);
                
                CCPoint diff = ccpSub(touchLocation,prevLocation);
                
                CCPoint currentPos = this->getPosition();
                			
                float tempWidth = mapSize.width*this->getScale();
                float tempWidth_Half = tempWidth/2;
                float tempHeight = mapSize.height*this->getScale();
                float tempHeight_Half =tempHeight/2;
                
                CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
                float result1= tempWidth_Half-screenSize.width/2;
                float result2 = tempHeight_Half-screenSize.height/2;
                
                CCPoint maxSelfPos = ccp(result1,result2);
                
                
                CCPoint minSelfPos;
                
                minSelfPos = ccp(result1-(tempWidth-480),result2-(tempHeight-320));		
                
                if (diff.x >=0) {
                    diff.x = (this->getPositionX()+diff.x)<=maxSelfPos.x?diff.x:(maxSelfPos.x-this->getPositionX()); 
                }
                else {
                    diff.x = (this->getPositionX()+diff.x)>=minSelfPos.x?diff.x:(minSelfPos.x-this->getPositionX());
                }
                
                if (diff.y>=0) {
                    diff.y = (this->getPositionY()+diff.y)<=maxSelfPos.y?diff.y:(maxSelfPos.y-this->getPositionY()); 
                }
                else {
                    diff.y = (this->getPositionY()+diff.y)>=minSelfPos.y?diff.y:(minSelfPos.y-this->getPositionY()); 
                }
                
                this->setPosition(ccpAdd(currentPos, diff));
            }
            
        } break;
        case 3:
        case 4:
        case 5:
        case 2: 
        {//zoom
//            CCLog("zoom--------------------------");
			if ( initialDistance==0) {
                CCSetIterator it;
                CCTouch* touch1 = NULL;
                CCTouch* touch2 = NULL;
                for( it = pTouches->begin(); it != pTouches->end(); it++)
                {
                    CCTouch *touch = (CCTouch*)(*it);
                    if(!touch)
                        break;
                    
                    int iViewID = touch->getID();
                    if( iViewID == 0 ){
                        touch1 = touch;
                    }
                    if (iViewID == 1) {
                        touch2 = touch;
                    }
                }
                
                if (touch1 != NULL && touch2 != NULL) {
                    CCPoint touch1Location = touch1->getLocationInView(); 
                    CCPoint touch2Location = touch2->getLocationInView(); 
                    
                    initialDistance = sqrt((touch1Location.x-touch2Location.x)*(touch1Location.x-touch2Location.x)
                                           +(touch1Location.y-touch2Location.y)*(touch1Location.y-touch2Location.y)); 
                }
				
			}
            
            
            CCSetIterator it;
            CCTouch* touch1 = NULL;
            CCTouch* touch2 = NULL;
            for( it = pTouches->begin(); it != pTouches->end(); it++) 
            {
                CCTouch *touch = (CCTouch*)(*it);
                if(!touch)
                    break;
                
                int iViewID = touch->getID();
                if( iViewID == 0 ){
                    touch1 = touch;
                }
                if (iViewID == 1) {
                    touch2 = touch;
                }
            }
            if (touch1 != NULL && touch2 != NULL) {
                CCPoint touch1Location = touch1->getLocationInView(); 
                CCPoint touch2Location = touch2->getLocationInView();
                
                finalDistance = sqrt((touch1Location.x-touch2Location.x)*(touch1Location.x-touch2Location.x)+(touch1Location.y-touch2Location.y)*(touch1Location.y-touch2Location.y)); 
                
                float scaleGesture = this->getScale() + (finalDistance - initialDistance)*0.005;
                
                scaleGesture = scaleGesture<3.0f?scaleGesture:3.0f;
            
                scaleGesture = scaleGesture>320.0/(MAPGLHEIGHT)?scaleGesture:320.0/(MAPGLHEIGHT);
                
                
                
                CCPoint newPos=this->getPosition();
                
                float tempWidth = mapSize.width*scaleGesture;
                float tempWidth_Half = tempWidth/2;
                float tempHeight = mapSize.height*scaleGesture;
                float tempHeight_Half =tempHeight/2;
                
                CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
                float result1= tempWidth_Half-screenSize.width/2;
                float result2 = tempHeight_Half-screenSize.height/2;
                CCPoint maxSelfPos = ccp(result1,result2);
                
                CCPoint minSelfPos;
                
                minSelfPos = ccp(result1-(tempWidth-480),result2-(tempHeight-320));	
                
                newPos.x = this->getPositionX()>=minSelfPos.x?newPos.x:minSelfPos.x; 
                newPos.y = this->getPositionY()>=minSelfPos.y?newPos.y:minSelfPos.y; 
                newPos.x = this->getPositionX()<=maxSelfPos.x?newPos.x:maxSelfPos.x; 
                newPos.y = this->getPositionY()<=maxSelfPos.y?newPos.y:maxSelfPos.y; 
                
                this->setPosition(newPos);
                this->setScale(scaleGesture);
                m_fCurrentScale = scaleGesture;
                initialDistance = finalDistance;
            }
        } break;
    }
}

void CentralLayer::mapTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    initialDistance = 0.0;
    finalDistance = 0.0;
}
