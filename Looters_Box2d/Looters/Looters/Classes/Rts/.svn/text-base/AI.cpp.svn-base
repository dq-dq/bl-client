#include "CentralLayer.h"
#include "Missle.h"
#include "CommonResource.h"
#include "FindRoad.h"

void CentralLayer::stand_ai(Unit* u)
{
	if (u->is_unit_type(UT_DEFENSE_BUILD))
	{
		if (NULL==u->target) {
            
			Unit* t = NULL;
            if (u->getTypeID() == DEFENSE_MORTAR) {
                t = enumCannonAreaUnits(u); //炮塔的盲区范围判定
            }else {
                t = enumAreaUnits(u);
            }
			if (t) {
				u->target = t;
                u->attack->resetCD();
			}
		}
		else
		{
			//塔
			if (UNIT_STATE_MOVING!=u->get_unit_state())
			{
				checkAttack(u);
			}
		}
		return;
	}
	
    
	if (!u->is_unit_type(UT_ROLE))
	{
		return;
	}
	
	if (NULL==u->target) 
	{
		// 找寻 目标单位, 开始移动
		Unit* tt = findAttackTarget(u);
		if (NULL!=tt && !u->m_ai_path.empty()) 
		{
			// 应该建造一条路径
			startmoveto(u,tt); // 如果army向建筑移动
		}
	}
	else 
	{
		// 移动结束, 开始攻击
		if (UNIT_STATE_MOVING!=u->get_unit_state()) 
		{
			//人
			if (u->m_ai_path.empty()) {
				checkAttack(u);
			}
			else
			{
				//startmoveto(u, t);
			}
		}
	}
}


void CentralLayer::move_ai(Unit* u)
{
	
}

void CentralLayer::resource_worker_ai( Unit* u )
{
	int const maxTargetNum = 4;


	if (u->m_ResouceTarget.empty())
	{
		long long time = Until::millisecondNow();
		if (u->m_role_time < time)
		{	
			u->setVisible(true);			
			u->ani_state_->m_pCharSprite->setVisible(true);			

			
			// 新建一组采集目标
			InitResourceWorkerTarget(u, maxTargetNum);

			// 显示角色
			MoveAResourceWorkerToNewTarget(u);
		}
		
	}
	
}

void CentralLayer::patrol_ai(Unit* u)
{
	// 在自己家角色移动
	if (NULL==u->m_pCampfire)
	{
		if (u->get_unit_state() != UNIT_STATE_MOVING) 
		{
            Unit * t = find_army_build(u);
            if (t) 
			{
				iVec2 index = quad_title_random_index(  t->m_stBuildSubstrate.m_Line, t->radius);
				index += quad_title_left_top_index(t->GetCenterPos(), t->m_stBuildSubstrate.m_Line);
				b2Vec2 pos = quad_title_covert_t::index_to_pos(index);

				bool isOk = FindRoad::sharedFindRoad()->SearchInHome(u, half_title_covert_t::pos_to_index(pos));
				if (isOk)
				{
					u->m_ai_path.clear();
					FindRoad::sharedFindRoad()->GetPath(u->m_ai_path);
					u->m_ai_path.front() = pos;
					u->cmd_moveto(u->m_ai_path.back().x, u->m_ai_path.back().y);
				}				
            }
		}
		
		return;
	}
	
	long long time = Until::millisecondNow();
	long long c = 1000 * 10; //10秒
	
	if ( u->m_ai_path.empty() &&  u->m_role_time + c < time )
	{	
		Unit* pCamp = u->m_pCampfire;
		iVec2 index = quad_title_random_index( pCamp->m_stBuildSubstrate.m_Line, pCamp->radius);
		iVec2 leftTop = quad_title_left_top_index(pCamp->GetCenterPos(true), pCamp->m_stBuildSubstrate.m_Line);
		index += leftTop;
		bool isOk = FindRoad::sharedFindRoad()->SearchInArmy(u, index, leftTop);
		if (isOk)
		{
			u->m_ai_path.clear();
			FindRoad::sharedFindRoad()->GetPathArmy(u->m_ai_path);
			u->cmd_moveto(u->m_ai_path.back().x, u->m_ai_path.back().y);
		}

	}
}

void CentralLayer::stand_cannon_ai(Unit* u)
{
    if(u->getTypeID() == DEFENSE_MORTAR){
        long long time = Until::millisecondNow();
        long long c = 1000 * 5; //10秒
        
        if ( u->m_role_time + c < time)
        {
            u->m_role_time = Until::millisecondNow();
            float x = (CCRANDOM_0_1() * 90.0f);
            if (x<= 30.0f ) { // idle_1 
                if (u->action_ == "idle_1") {
                    return;
                }else if(u->action_ == "idle_2"){
                    u->action_ = "steer_middleleft";    //// 3
                }else if(u->action_ == "idle_3")
                {
                    u->action_ = "steer_rightleft";     //// 6 
                }
            }
            else if(x<= 60.0f) // idle_2
            {
                if (u->action_ == "idle_2") {
                    return;
                }else if(u->action_ == "idle_1"){
                    u->action_ = "steer_leftmiddle";    //// 0
                }else if(u->action_ == "idle_3")
                {
                    u->action_ = "steer_rightmiddle";   //// 2
                }
            }
            else  // idle_3
            {
                if (u->action_ == "idle_3") {
                    return;
                }else if(u->action_ == "idle_1"){
                    u->action_ = "steer_leftright";     //// 4
                }else if(u->action_ == "idle_2")
                {
                    u->action_ = "steer_middleright";   //// 1
                }
            }
            u->ani_state_->run_action(u->action_, CCPointZero);
        }
    }else{
        long long time = Until::millisecondNow();
        long long c = 1000 * 4; //10秒
        
        if ( u->m_role_time + c < time )
        {
            u->m_role_time = Until::millisecondNow();
            u->direction_.x = CCRANDOM_MINUS1_1();
            u->direction_.y = CCRANDOM_MINUS1_1();
            u->direction_ = ccpNormalize(u->direction_);
            
            u->ani_state_->run_action("idle_1", u->direction_);
        }
    }
}


class SortNearArmy
{
public:
	SortNearArmy(b2Vec2 const& pos)
		:curPos(pos)
	{

	}

	bool operator() (BuildingBase * lhs, BuildingBase * rhs ) const
	{
		b2Vec2 first = lhs->GetCenterPos() - curPos;
		b2Vec2 second = rhs->GetCenterPos() - curPos;

		return first.LengthSquared() < second.LengthSquared();
	}

private:
	b2Vec2 curPos;
};



BuildingBase* CentralLayer::matchingCampfire(int rolecount, b2Vec2 const& pos )
{
	BuildingBase* result = NULL;
	typedef std::vector<BuildingBase*> buildList_t;
	buildList_t buildList;

	int maxPeople = 0;
	int nowPeople = 0;
	for (int i=0; i<unit_list_->count(); ++i)
	{
		Unit *unit = (Unit*)unit_list_->objectAtIndex(i);

		if (unit->getTypeID()==ARMY_TROOPHOUSING)
		{
			BuildingBase* pBuild = (BuildingBase*) unit;
			buildList.push_back(pBuild);
			nowPeople += pBuild->GetNowHousingSpace();

			const BaseBuildingLevelData* data = GameData::GetDataFromBaseBuildingLevelData(pBuild->getTypeID()*100+pBuild->lv);
			maxPeople += data->HousingSpace;
		}
	}

	if (maxPeople<nowPeople+rolecount)
	{
		return result;
	}
	

	SortNearArmy sortNear(pos);
	std::sort(buildList.begin(), buildList.end(), sortNear);

	for (buildList_t::iterator iCur=buildList.begin(), iEnd=buildList.end();
		iCur!=iEnd; ++iCur)
	{
		BuildingBase* pBuild = *iCur;
		const BaseBuildingLevelData* data = GameData::GetDataFromBaseBuildingLevelData(pBuild->getTypeID()*100+pBuild->lv);
		if (pBuild->GetNowHousingSpace()<data->HousingSpace)
		{
			result = pBuild;
			break;
		}
		
	}
	
	return result;
}

Unit* CentralLayer::findAttackTarget(Unit* u)
{
//	ClearTestPoint();
//	InitTestPoint();
	
	Unit *t = NULL;
	
	if (u->is_unit_type(UT_ROLE))
	{
		t = CentralLayer::find_love_near_target(u);
		if (NULL!=t) 
		{
			u->m_ai_path.clear();

//			{
//				iVec2 index = get_worker_target(t->GetCenterPos(), t->m_stBuildSubstrate.m_Line, t->radius);
//				u->m_ai_path.push_back(half_title_covert_t::index_to_pos(index));
//
//			}
			

			bool isOk = FindRoad::sharedFindRoad()->Search(u, t);
			CCAssert(isOk, __FUNCTION__);  // wangning_debug
			if (isOk)
			{
				FindRoad::sharedFindRoad()->GetPath(u->m_ai_path);
				if (NULL!=FindRoad::sharedFindRoad()->GetNewTarget())
				{
					t = FindRoad::sharedFindRoad()->GetNewTarget();
				}
			}
		}

	}
	
	if (t) {
		u->target = t;
	}
	return t;
}


void CentralLayer::startmoveto(Unit* u,Unit* t)
{
    if ( u->is_unit_type(UT_ROLE) && u->get_unit_state() != UNIT_STATE_MOVING) 
	{
        if ( t->is_build_type()) 
		{
			b2Vec2 const& pos = u->m_ai_path.back();
			u->cmd_moveto(pos.x, pos.y);
        }
    }
}


void CentralLayer::checkAttack(Unit* u)
{
	Unit *t = u->target;
	if (t) {
		if(u->attack && u->attack->useable()){
			u->attack->use(t);
		}
	}
}
