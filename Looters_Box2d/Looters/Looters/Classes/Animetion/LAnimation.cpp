#include "LAnimation.h"
#include "some_tool.h"
#include "GameData.h"

LAnimation::LAnimation()
{
    m_pCharSprite = NULL;
    m_LActionName = "";
    m_LChildID = -1;
    unitTypeID = 0;
}

LAnimation::~LAnimation()
{
    m_LAction = NULL;
    m_mapLAnim.clear();
}

LAnimation* LAnimation::create()
{
	LAnimation* anim = new LAnimation();
    anim->autorelease();
	return anim;
}

int  LAnimation::get_Direction(CCPoint angle)
{
	if(float_equal(angle.x, -1.f) && float_equal(angle.y, 0.f))
	{
		return Left;
	}
	else if(float_equal(angle.x, 1.f) && float_equal(angle.y, 0.f))
	{
		return Right;
	}
	else if (float_equal(angle.x, 0.f) && float_equal(angle.y, 1.f)) 
	{
		return Up;
	}
	else if (float_equal(angle.x, 0.f) && float_equal(angle.y, -1.f)) 
	{
		return Down;
	}
	else if(angle.x<0.f && angle.y>0.f)
	{
		return LeftTop;
	}
	else if( angle.x<0.f && angle.y<0.f)
	{
		return LeftBottom;
	}
	else if( angle.x>0.f && angle.y>0.f)
	{
		return RightTop;
	}
	else if (angle.x>0.f && angle.y<0.f)
	{
		return RightBottom;
	}
	return 0;
}

int  LAnimation::get_Direction_Cannon(CCPoint angle)
{
    float alpha = acosf(angle.x);
    alpha = angle.y>0? alpha: -alpha;
    
    if (alpha < -PI/2 && alpha >= -2*PI/3) {
        return Left1;
    }
    else if(alpha < -2*PI/3 && alpha >= -5*PI/6){
        return Left2;
    }
    else if(alpha < -5*PI/6 && alpha >= -PI)
    {
        return Left3;
    }
    else if(alpha >= 5*PI/6 && alpha < PI)
    {
        return Left4;
    }
    else if(alpha >= 2*PI/3 && alpha < 5*PI/6)
    {
        return Left5;
    }
    if (alpha >= PI/2 && alpha < 2*PI/3) {
        return Left6;
    }
    else if(alpha < -PI/3 && alpha >= -PI/2)
    {
        return Left7;
    }
    else if(alpha < -PI/6 && alpha >= -PI/3)
    {
        return Left8;
    }
    else if(alpha < 0 && alpha >= -PI/6)
    {
        return Left9;
    }
    else if(alpha < PI/6 && alpha >= 0)
    {
        return Left10;
    }
    else if(alpha < PI/3 && alpha >= PI/6)
    {
        return Left11;
    }
    else if(alpha < PI/2 && alpha >= PI/3)
    {
        return Left12;
    }
    return Left1;
}


int  LAnimation::get_action(CCPoint direction)
{
    int dir = 0;
    if (m_LAction->action[3]) {
        dir = get_Direction_Cannon(direction);
    }else{
        dir = get_Direction(direction);
    }
    if (m_LAction->action[3]) {
        if (dir > 5) {
            dir = dir - 6;
            this->m_pCharSprite->setFlipX(true);
        }
        else
        {
            this->m_pCharSprite->setFlipX(false);
        }
    }
    else if (m_LAction->action[1]) {
        if (dir == 6) {
            dir = LeftTop;
            this->m_pCharSprite->setFlipX(true);
        }
        else if (dir == 7) {
            dir = LeftBottom;
            this->m_pCharSprite->setFlipX(true);
        }
        else if (dir > 2)
        {
            dir = dir - 3;
            this->m_pCharSprite->setFlipX(true);
        }
        else
        {
            this->m_pCharSprite->setFlipX(false);
        }
    }else if(!m_LAction->action[1]){
        dir = 0;
    }
    return dir;
}

void LAnimation::restart_action()
{
    m_pCharSprite->stopAction(m_LAction->action[m_LChildID]);
    m_pCharSprite->runAction(m_LAction->action[m_LChildID]);
}

void LAnimation::run_action(string const& actionName,CCPoint angle)
{
    if (unitTypeID == DEFENSE_MORTAR) { // 加农炮处理
        int actionID = 0;
        bool isChange = false;
        if (m_LActionName != actionName) {
            if (m_LActionName != "") {
                m_pCharSprite->stopAction(m_LAction->action[m_LChildID]);
            }
            m_LActionName = actionName;
            laction_t::iterator iter = m_mapLAnim.find(actionName);
            m_LAction = &iter->second;
            isChange = true;
        }
        
        if (m_LChildID == -1) { // 第一次运行action
            m_LChildID = 0;
            m_pCharSprite->runAction(m_LAction->action[m_LChildID]);
            return;
        }
        
        int ID = actionID;
        if (isChange) {
            m_LChildID = ID;
            m_pCharSprite->runAction(m_LAction->action[m_LChildID]);
        }
        else{
            if (m_LChildID != ID) {
                m_pCharSprite->stopAction(m_LAction->action[m_LChildID]);
                m_LChildID = ID;
                m_pCharSprite->runAction(m_LAction->action[m_LChildID]);
            }
        }
    }else{
        bool isChange = false;
        if (m_LActionName != actionName) {
            if (m_LActionName != "") {
                m_pCharSprite->stopAction(m_LAction->action[m_LChildID]);
            }
            m_LActionName = actionName;
            laction_t::iterator iter = m_mapLAnim.find(actionName);
            m_LAction = &iter->second;
            isChange = true;
        }
        
        if (m_LChildID == -1) { // 第一次运行action
            m_LChildID = get_action(angle);
            m_pCharSprite->runAction(m_LAction->action[m_LChildID]);
            return;
        }
        
        int ID = get_action(angle);
        if (isChange) {
            m_LChildID = ID;
            m_pCharSprite->runAction(m_LAction->action[m_LChildID]);
        }
        else{
            if (m_LChildID != ID) {
                m_pCharSprite->stopAction(m_LAction->action[m_LChildID]);
                m_LChildID = ID;
                m_pCharSprite->runAction(m_LAction->action[m_LChildID]);
            }
        }
    }
}

