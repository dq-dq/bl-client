#include "CentralLayer.h"
#include "CommonResource.h"
#include "LAnimation.h"
#include "LAnimManage.h"
#include "BattleRecorde.h"

void CentralLayer::peopleTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
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
    
    CCPoint touchLocation = touch->getLocation();
    CCPoint pointMap = m_tmxMap->convertToNodeSpace( touchLocation );//得到坐标在m_tmxMap本地空间的坐标
}


void CentralLayer::peopleTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
}

void CentralLayer::peopleTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
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
	CCPoint pointMap = m_tmxMap->convertToNodeSpace(touch->getLocation());
    
    CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    // 判定是否可以放兵
	CCPoint mapIndex = to_CCPoint( normal_title_covert_t::pos_to_index(to_b2Vec2(pointMap)));
	
	iBox2 const mapBound(to_iVec2(0, 0), to_iVec2(MAPGRIDWIDTH-1, MAPGRIDHEIGHT-1));
	if (!mapBound.IsContains(to_iVec2(mapIndex))) {
		return;
	}
    InvalidCell info;
    if (!this->GetInvalidCellInfo(mapIndex.x*MAPGRIDHEIGHT+mapIndex.y, &info)) 
	{
        // 进入战斗中状态
        if (battle_state_ == BATTLE_READY && m_enHandleState != STATE_MOVE) {
            SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralPVPMapUILayer->change_battlestate(CentralLayer::BATTLE_IN);
        }
        // 战斗中状态 可以放兵
        if(battle_state_ == BATTLE_IN){
            CentralPVPMapUILayer* pVPMapUILayer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralPVPMapUILayer;
            if (pVPMapUILayer->selectUnit) {
                CentralData::AttackerSoldiersAndSpell *obj = data->m_AttackerSoldiersAndSpell->at(pVPMapUILayer->selectUnit->getTag());
                if (obj->used_type == 0) {
                    if (obj->count > 0) {
                        obj->count = obj->count-1;
                        CCLabelTTF *label = (CCLabelTTF*)pVPMapUILayer->selectUnit->getChildByTag(10);
                        if (label) {
                            label->setString(CommonResource::getStringFromInt(obj->count).c_str());
                        }
                        if (obj->count == 0) {
                            //变灰
                            IconSprite_CentralPVPMapUI* iconSprite = (IconSprite_CentralPVPMapUI*)pVPMapUILayer->selectUnit->getChildByTag(0);
                            iconSprite->removeFromParentAndCleanup(false);
                            
                            int iconID = iconSprite->iconID;
                            char framename[256] = {0};
                            sprintf(framename,"soldiers_Icon_Disabled%d.png",iconID);
                            
                            IconSprite_CentralPVPMapUI* objIcon = (IconSprite_CentralPVPMapUI*)CCSprite::createWithSpriteFrameName(framename);
                            objIcon->setScale(1.0f);
                            objIcon->setPosition(ccp(pVPMapUILayer->selectUnit->getContentSize().width/2,pVPMapUILayer->selectUnit->getContentSize().height/2));
                            objIcon->setTag(0);
                            objIcon->iconID = iconID;
                            pVPMapUILayer->selectUnit->addChild(objIcon);
                            
                            pVPMapUILayer->selectUnit->setPosition(ccp(pVPMapUILayer->selectUnit->getPositionX(),pVPMapUILayer->selectUnit->getPositionY()-CentralPVPMapUI_ICON_Y));
                            pVPMapUILayer->selectUnit = NULL;
                        }
                        int unitID = obj->characterIdOrSpellId*1000*100+obj->characterOrSpellLevel;
                        this->AddPeople(unitID,pointMap,NULL);
                        battle_addpeoplecount++;
                    }
                }
            }
            
            if (NotNetworking) {
                this->AddPeople(200001,pointMap,NULL); // 100001 刀兵 200001火枪兵 500001炸弹兵
            }
//            AddNpcPeople(100000,pointMap);
        }
    }
}