/***************************************************************
 author:     wangning
 write time: 2012.10.22
 function:   游戏主场景触控操作
 ***************************************************************/

#include <iostream>
#include "CentralLayer.h"
#include "GameControl.h"
#include "cocos2d.h"

void CentralLayer::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
    if( m_enLoadProcess != finish ) return;
	
	{
//		CCTouch* touch = (CCTouch* )*pTouches->begin();
//		
//		CCPoint touchLocation = touch->getLocation();
//		CCPoint pos = m_tmxMap->convertToNodeSpace( touchLocation );
//		
//		iVec2 mapIndex = half_title_covert_t::pos_to_index(to_b2Vec2(pos));
//		CCLog("half index--> %d, %d", mapIndex.x, mapIndex.y);
	}
    
    CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    if (data->m_enCentralViewMode == CENTRALVIEW_SELF) 
    {
        this->buildTouchesBegan(pTouches, pEvent);
    }
    
    this->mapTouchesBegan(pTouches, pEvent);
    
    if (data->m_enCentralViewMode == CENTRALVIEW_BATTLE) {
        if (data->m_enPVPMode == BATTLE_MODE_PVP_REPLAY) {
            return;
        }
        m_enHandleState = STATE_CLICK;
        if (battle_state_ == BATTLE_IN) {
            this->peopleTouchesBegan(pTouches, pEvent);
        }
    }
}

void CentralLayer::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )
{
	if( m_enLoadProcess != finish ) return;
		
    CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    
    if (data->m_enCentralViewMode == CENTRALVIEW_SELF)
    {
        this->buildTouchesMoved(pTouches, pEvent);
    }
    
    if (m_building == NULL||m_enHandleState == STATE_DRAG)
    {
        this->mapTouchesMoved(pTouches, pEvent);
    }
    
    if (data->m_enCentralViewMode == CENTRALVIEW_BATTLE) {
        if (data->m_enPVPMode == BATTLE_MODE_PVP_REPLAY) {
            return;
        }
        if (m_enHandleState == STATE_CLICK)
        {
            m_enHandleState = STATE_MOVE;
        }
        if(battle_state_ != BATTLE_END){
            this->peopleTouchesMoved(pTouches, pEvent);
        }
    }
}

void CentralLayer::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
	if( m_enLoadProcess != finish ) return;
		
    CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    if (data->m_enCentralViewMode == CENTRALVIEW_SELF) 
    {
        this->buildTouchesEnded(pTouches, pEvent);
    }
    
    this->mapTouchesEnded(pTouches, pEvent);
    
    if (data->m_enCentralViewMode == CENTRALVIEW_BATTLE) {
        if (data->m_enPVPMode == BATTLE_MODE_PVP_REPLAY) {
            return;
        }
        if (battle_state_ != BATTLE_END) {
            this->peopleTouchesEnded(pTouches, pEvent);
        }
        m_enHandleState = STATE_NULL;
    }
}