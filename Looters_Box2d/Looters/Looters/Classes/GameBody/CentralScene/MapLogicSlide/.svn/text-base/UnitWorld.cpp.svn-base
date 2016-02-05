#include "CentralLayer.h"
#include "NetMessageManager.h"
#include "Until.h"
#include "Missle.h"

#include "BattleRecorde.h"
#include "BattleReplay.h"
#include "NavGraph.h"

void CentralLayer::step(float dt)
{
	if(BattleReplay::sharedBattleReplay()->Update()){
        BattleReplay::sharedBattleReplay()->EndReplay();
        this->unscheduleAllSelectors();
        SceneManage::GetSceneManageHendle()->m_pCentralScene->LoadSceneLayer(CENTRALVIEW_SELF);
    }
    
    //step 1: remove particle
    for (int i=0; i<particle_list_->count(); i++) {
        LParticleUnit* particle = (LParticleUnit*)particle_list_->objectAtIndex(i);
        if (particle->particle_state_ == particle_STATE_GHOST) {
            particle->removeFromParentAndCleanup(false);
            particle_list_->removeObject(particle);
        }
    }
    
	//step 2: movement / direction
	for (int i=0; i<unit_list_->count(); i++) {
		Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
		if (unit) {
			unit->_apply_movement(dt);
		}
	}
	
	//step 3: battle logic
	for (int i=0; i<unit_list_->count();i++ )
	{
		Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
		if (unit->is_alive())
		{
			update_unit_ai(unit,dt);
	
			if (unit->attack) {
				unit->attack->attack_update(dt);
			}
			
			if(unit->is_unit_type(UT_MISSLE)){
				Missle *missle = (Missle*)unit;
				missle->update(dt);
			}
		}
	}
	
	bool isWallBreak = false;
	//step 4: ensure targets & new events(events generated in step 3)
	for (int i=0; i<unit_list_->count();i++ )
	{
		Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
		if (unit->target)
		{
			if (!unit->target->is_alive())
			{
				isWallBreak |= unit->target->is_unit_type(UT_WALL_BUILD);
				
				unit->target = NULL;
			}
		}
		if (unit->attack) {
			if (unit->attack->dest) {
				if (!unit->attack->dest->is_alive()) {
					unit->attack->dest = NULL;
                    unit->attack->force_end_skill();
				}
			}
		}
	}
	
	if (isWallBreak) 
	{
		for (int i=0; i<unit_list_->count(); ++i)
		{
			Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
			if (NULL!=unit->target && unit->target->is_unit_type(UT_WALL_BUILD) && !unit->is_love_target(unit->target))
			{
				unit->target = NULL;
				unit->attack->force_end_skill();				
				unit->m_ai_path.clear();
				unit->_change_unit_state(UNIT_STATE_STAND);
			}
		}
	}	
	
	
	//step 5: remove ghosts
	_remove_ghosts();
	
	//step 6: apply sprite
	for (int i=0; i<unit_list_->count();i++ ) {
		Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
		if (unit) {
			unit->_apply_sprite_state();
            unit->_hp_showtime(dt);
		}
	}
}

void CentralLayer::InitTestPoint()
{
	for (int i=0; i<TITLE_NUM_X2*TITLE_NUM_X2; ++i) 
	{
		Unit* pUnit = NavGraph::sharedNavGraph()->GetUnit(i);
		if (NULL!=pUnit) 
		{
			b2Vec2 pos = half_title_covert_t::index_to_pos( half_title_covert_t::int_to_index(i));
			CCNode* p = BaseDrawPoint::DrawPoint(to_CCPoint(pos), 5);
			m_testPoint.push_back(p);
			m_tmxMap->addChild(p, 5000);
		}
	}
}

void CentralLayer::ClearTestPoint()
{
	for (size_t i=0, iEnd=m_testPoint.size(); i!=iEnd; ++i) {
		m_tmxMap->removeChild(m_testPoint[i], false);
	}
	m_testPoint.clear();
}


void CentralLayer::_remove_ghosts()
{
	for (int i=0; i<unit_list_->count();i++ ) {
		Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
		if (unit->unit_state_ != UNIT_STATE_GHOST)
		{
			continue;
		}
		else 
		{
            CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
            if (unit->is_build_type() &&  data->m_enCentralViewMode == CENTRALVIEW_SELF)
			{
				BuildingBase* pBuild = (BuildingBase*)unit;
                if (pBuild->upgrade_state_ != UNIT_UPGRADE_NO)
                {
                    RemoveGridBuildInfo(pBuild->getMapIndex(), pBuild->GetLine(), pBuild->getuuID(), pBuild);
                }
				
			}
            
            if (unit->defenderCharacterArr) {
                for (int i=0; i<unit->defenderCharacterArr->count(); i++) {
                    Unit* childUnit = (Unit*)unit->defenderCharacterArr->objectAtIndex(i);
                    if (childUnit->ani_state_) {
                        childUnit->clean();
                        m_tmxMap->removeChild(childUnit, false);
                        childUnit = NULL;
                    }
                }
			}
			
            unit->clean();
			unit_list_->removeObject(unit);
			m_tmxMap->removeChild(unit, false);
			unit = NULL;
		}
	}
}

void CentralLayer::update_unit_ai(Unit* u,float dt)
{
	// ai逻辑更新
	switch (u->unit_ai_cmd_) {
		case UNIT_AI_STAND:
			{
				CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;

				if( data->m_enCentralViewMode == CENTRALVIEW_BATTLE ){
					stand_ai(u);
				}

				break;
			}

		case UNIT_AI_MOVE:
			move_ai(u);
			break;

		case UNIT_AI_PATROL:
			{
                patrol_ai(u);
				break;
			}

		case UNIT_AI_STAND_CANNON:
			{
				stand_cannon_ai(u);
				break;
			}

		case UNIT_AI_WORKER:
			{
//				worker_ai(u);
				break;
			}

		case UNIT_AI_RESOURCE_WORKER:
			{

				resource_worker_ai(u);
				break;
			}

		default:
			break;
	}
}

Unit* CentralLayer::find_love_near_target( Unit* src )
{
	
	b2Vec2 const srcPos(src->getPositionX(), src->getPositionY());

	Unit* target = NULL;
	float minLen = std::numeric_limits<float>::max();


	// 遍历敌建筑物,找最近与最爱
	// 遍历敌人, 那么就需要完全遍历才可找到最近的
	for (int i=0, iEnd=unit_list_->count(); i<iEnd; ++i )
	{
		Unit *unit = (Unit*)unit_list_->objectAtIndex(i);

		if (!unit->is_build_type() )
		{
			continue;
		}
		
		if (unit->is_unit_type(UT_WALL_BUILD) && !src->is_love_target(unit)) {
			continue;
		}
		
		// 活着与仇恨
		if (unit->is_alive() && src->does_hate(unit)) 
		{
			
			if (unit->is_unit_type(UT_WALL_BUILD) && src->is_love_target(unit)) 
			{
				CCPoint index = unit->getMapIndex();
				
				CCPoint near[4] = { CCPointMake(index.x-1, index.y), CCPointMake(index.y+1, index.y),
					CCPointMake(index.x, index.y-1), CCPointMake(index.x, index.y+1)};
				bool near_is_wall[4] = {false, false, false, false};
				
				MapGridLogicInfo info;				
				for (int i=0; i<4; ++i) 
				{

					near_is_wall[i] = NULL!=on_tiltle_unit_type(near[i], UT_WALL_BUILD);
				}
				
				if (!(near_is_wall[0] && near_is_wall[1]) && !(near_is_wall[2] && near_is_wall[3]) ) {
					continue;
				}
				
			}
			
			b2Vec2 radiusV(unit->radius * 0.5f * BUILDINTBASEGRID_EDGE_LEN, unit->radius * 0.5f * BUILDINTBASEGRID_EDGE_LEN);
			// 取中心点, 还是包围盒距离? 对更大的不管			
			b2Vec2 pnt = b2Abs(srcPos-unit->GetCenterPos());
			pnt -= radiusV;

			float len = pnt.LengthSquared();
			
			// 更近, 或者第一次找到目标
			if (NULL==target)
			{
				minLen = len;
				target = unit;
				continue;
			}
			
			if (len < minLen)
			{
				// 之前爱,现在不爱, 此情况外直接替换
				if ( !(src->is_love_target(target) && !src->is_love_target(unit)))
				{
					minLen = len;
					target = unit;
				}				
			}
			else
			{
				// 之前非爱,现在爱, 替换
				if (!src->is_love_target(target) && src->is_love_target(unit))
				{
					minLen = len;
					target = unit;
				}
				
			}							
		}
	}
	
	return target;
}


Unit* CentralLayer::on_tiltle_unit_type( CCPoint const& index, unit_type type)
{
	
	Unit* pResult = NULL;
	MapGridLogicInfo info;
	GetMapGridLogicInfo( map_index_to_index(index), &info);

	if (NULL!=info.pBuilding)
	{
		Unit* pUnit = (Unit*)(info.pBuilding);
		if (pUnit->is_unit_type(type))
		{
			pResult = pUnit;
		}		
	}
	
	return pResult;
}


Unit* CentralLayer::find_army_build( Unit* src )
{	
	
	// 角色所占的人口数
	int role_housing_space = 0;
	{
		BasePeopleData const* data = GameData::GetDataFromBasePeopleData(src->getTypeID() *100 + src->lv);
		role_housing_space = data->HousingSpace;
	}

	b2Vec2 srcPos = src->GetCenterPos();

	BuildingBase* result = matchingCampfire(role_housing_space, srcPos);	
	CCAssert(NULL!=result, __FUNCTION__);

	{
		result->m_army.push_back(src);
		src->m_pCampfire = result;
	}

	return result;
}


Unit* CentralLayer::enumAreaUnits(Unit *src)
{
    CCPoint cPoint = to_CCPoint(src->GetCenterPos());
    float x = cPoint.x;
	float y = cPoint.y;
    
    int range = src->AttackRange;
    Unit *u = NULL;
    float l = 0;
    for (int i=0; i<unit_list_->count();i++ ) {
        Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
        if (unit->is_alive() && src->does_hate(unit)) {
            CCPoint pnt = to_CCPoint(unit->GetCenterPos());
            
            CCPoint LTPoint = ccp(x-range,y+range*3/4);
            CCPoint RBPoint = ccp(x+range,y-range*3/4);
            if(Until::inellipse(LTPoint, RBPoint, ccp(x,y), pnt))
            {
                float dl = (pnt.x-x)*(pnt.x-x) + (pnt.y-y)*(pnt.y-y);
                if (l==0) {
                    l = dl;
                    u = unit;
                }
                if(dl<l){
                    l = dl;
                    u = NULL;
                    u = unit;
                }
            }
        }
    }
    return u;
}

Unit* CentralLayer::enumCannonAreaUnits(Unit* src)
{
    CCPoint cPoint = to_CCPoint(src->GetCenterPos());
	float x = cPoint.x;
	float y = cPoint.y;
	int range = src->AttackRange;
	int blindRange = src->blindRange;
	
	Unit *u = NULL;
	float l = 0;
	for (int i=0; i<unit_list_->count();i++ ) {
		Unit *unit = (Unit*)unit_list_->objectAtIndex(i);
		if (unit->is_alive() && src->does_hate(unit)) {
			CCPoint pnt = to_CCPoint(unit->GetCenterPos());

			CCPoint LTPoint = ccp(x-range,y+range*3/4);
			CCPoint RBPoint = ccp(x+range,y-range*3/4);
			
			
			CCPoint bLTPoint = ccp(x-blindRange,y+blindRange*3/4);
			CCPoint bRBPoint = ccp(x+blindRange,y-blindRange*3/4);
			
			if(Until::inellipse(LTPoint, RBPoint, ccp(x,y), pnt) && !Until::inellipse(bLTPoint, bRBPoint, ccp(x,y), pnt))
			{
				float dl = (pnt.x-x)*(pnt.x-x) + (pnt.y-y)*(pnt.y-y);
				if (l==0) {
					l = dl;
					u = unit;
				}
				if(dl<l){
					l = dl;
					u = NULL;
					u = unit;
				}
			}
		}
	}
	return u;

}

bool CentralLayer::checkUnitInArea(int _range,Unit* src,Unit *dest)
{
	if ( src->is_unit_type(UT_ROLE) && dest->is_build_type())
	{
		Box45 dstBox(dest->GetCenterPos(), dest->radius * BUILDINTBASEGRID_EDGE_LEN+ src->AttackRange*2.f);
		return dstBox.is_container(to_b2Vec2(src->getPosition()));
	}


	int range = _range;
	CCPoint pnt = dest->getPosition();
	float x = src->getPositionX();
	float y = src->getPositionY();

	CCPoint LTPoint = ccp(x-range,y+range*3/4);
	CCPoint RBPoint = ccp(x+range,y-range*3/4);

	return Until::inellipse(LTPoint, RBPoint, ccp(x,y), pnt);
}

void  CentralLayer::buyBuilding(int unitID)
{
    if (m_building != NULL && m_BuyBuilding ==NULL)
	{
		//放下建筑
		fangxiajianzhu();
	}
    
    
	if (m_BuyBuilding !=NULL)
	{
		//删除已有购买建筑
		m_BuyBuilding->remove();
		
		m_BuildOperatingMode = MODE_NULL;
		m_BuyBuilding = NULL;
		m_building = NULL;
	}
    
	//寻找初始位置

    CCPoint isoAt = this->getMapIndexByTouchPoint(ccp(480/2, 320/2));
    
    const BaseBuildingLevelData* buildingBaseLevelData;
    buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( unitID);
	

	iVec2 newPos = FindEmptyTitle(buildingBaseLevelData->Width);

	// 找不到空余位置， 不可建建筑
	if (newPos == to_iVec2(-1, -1))
	{
		return;
	}
	
	isoAt = to_CCPoint(newPos);

	
	if(buildingBaseLevelData)
	{
        if (buildingBaseLevelData->building_TypeID == BUILDINGTYPE_WALL)
        {
            if(m_PlaceState == PlaceState_First){
                m_BuyBuilding =  BuildWall_first(unitID,isoAt,true);
            }else {
                m_BuyBuilding = this->BuildWall_next(placeDirection,unitID,true);
                if(!m_BuyBuilding){
                    m_PlaceState = PlaceState_First;
                }
            }
        }
        else
        {
             m_BuyBuilding =  AddBuilding(unitID, isoAt,build_uuId,true);
        }
    }
    if (!m_BuyBuilding) {
        return;
    }
    
	m_BuyBuilding->drawSymbol(this,menu_selector(CentralLayer::menuCallbackCancel),menu_selector(CentralLayer::menuCallbackOK));
   
    m_BuyBuilding->m_iBuildCDTime = buildingBaseLevelData->BuildTimeD*24*60*60+ buildingBaseLevelData->BuildTimeH*60*60 +buildingBaseLevelData->BuildTimeM*60;
	//加入数组显示底座
	unit_list_->addObject(m_BuyBuilding);
	
	build_uuId++;
	  
	m_building = m_BuyBuilding;
	buildNewMapIndex = m_building->getMapIndex();
	//显示箭头
	m_building->IsShowSubstrateArrow(true);
	//改变建筑为移动
	startMovePos = ccp(-1,-1);
	m_BuildOperatingMode = MODE_DRAG;
    
    if (this->isCanPutDownBuild(buildNewMapIndex,m_building->GetLine(),m_building->getuuID(),m_building))
    {
        m_building->m_pSubstrateBottom->setColor(m_building->ccl);
    }
    else
    {
        m_building->m_pSubstrateBottom->setColor(ccColor3B(ccRED));
    }
    m_building->z_state_ = UNIT_Z_MAX_STATE;
}

BuildingBase*  CentralLayer::AddReadBuilding(int buildID,CCPoint isoAt,int uu_id)
{
    if(buildID == 20000){
        CCLog("");
    }
	BuildingBase* building = AddBuilding(buildID,isoAt,uu_id,false);
	building->setuuID(uu_id);
	
	if (building != NULL)
	{
		unit_list_->addObject(building);
	}
	return building;
}

BuildingBase* CentralLayer::AddContinuousWall(int unitID,CCPoint isoAt,int type)
{
	BuildingBase* building = AddBuilding(unitID,isoAt,build_uuId,false);
    
	CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
	data->m_tmxMap->removeChild(building->sprite_, false);
	
    
    char spritename[64] = {0};
	switch (type) {
		case BuildWall_type_0:
            sprintf(spritename,"build_defense_wall_lvl%d_00",building->lv);
			building->sprite_ = CCSprite::create(GAME_FILE_TRANSFORM(spritename,".png").c_str());
			break;
		case BuildWall_type_1:
            sprintf(spritename,"build_defense_wall_lvl%d_01",building->lv);
			building->sprite_ = CCSprite::create(GAME_FILE_TRANSFORM(spritename,".png").c_str());
			break;
		case BuildWall_type_2:
            sprintf(spritename,"build_defense_wall_lvl%d_02",building->lv);
			building->sprite_ = CCSprite::create(GAME_FILE_TRANSFORM(spritename,".png").c_str());
			break;
		case BuildWall_type_3:
            sprintf(spritename,"build_defense_wall_lvl%d_03",building->lv);
			building->sprite_ = CCSprite::create(GAME_FILE_TRANSFORM(spritename,".png").c_str());
			break;
			
		default:
			break;
	}
    
    char strName[64] = {0};
    sprintf(strName,"%s \nlevel%d",building->getName().c_str(),building->lv);
    building->drawNameLabel(building->sprite_,strName);
    
	building->sprite_->setAnchorPoint(ccp(0.5,0.5));
	data->m_tmxMap->addChild(building->sprite_);
	
	if (building != NULL)
	{
		unit_list_->addObject(building);
	}
	
	return building;
}

void CentralLayer::ReplaceWallToBase01(BuildingBase* build)
{
    char spritename[64] = {0};
    sprintf(spritename,"build_defense_wall_lvl%d_00",build->lv);
    build->replaceSprite_(GAME_FILE_TRANSFORM(spritename,".png").c_str());
}

void CentralLayer::CentralRechargeRequest(string _str)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    pCentralScene->m_pCentralShopUILayer->DetectTyep = ShopDetectProcess_Bank;
}
BuildingBase*  CentralLayer::AddBuilding(int unitID ,CCPoint isoAt,int uuID,bool isBuy)
{
	const BaseBuildingLevelData* buildingBaseLevelData;
	buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( unitID);
    
	if(buildingBaseLevelData)
	{        
        BuildingBase *pBuilding = BuildingManager::JudgeBuildingType(unitID);
        pBuilding->setuuID(uuID);
		// 设置建筑的出生点在地图的中心
		CCPoint outPos = this->positionForIsoAt(isoAt);
		pBuilding->setPosition(ccp(outPos.x+BUILDINGBASEGRID_WIDTH/2,outPos.y));
		pBuilding->setMapIndex(isoAt);
		pBuilding->setAnchorPoint(ccp(0.5,0));

		const UnitClass* unitclass = GameData::GetUnitClassData(unitID);
		pBuilding->setUnitClass(unitclass);
        pBuilding->setData();
        
        // 编辑逻辑单元格
        this->MarkGridBuildInfo(pBuilding->getMapIndex(),pBuilding->GetLine(),pBuilding->getuuID(),pBuilding);
        
        
        CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
        // 如果是火枪塔
        if (buildingBaseLevelData->building_TypeID == DEFENSE_ARCHERTOWER) {
            //
            Unit* unit = AddPeople(buildingBaseLevelData->DefenderCharacter, isoAt, pBuilding);
            unit->ani_state_->run_action("idle_1",ccp(-1.0f,0));
            unit->camp = UNIT_CAMP_ENEMY;
            
            pBuilding->offsetx = 0;
            pBuilding->offsety = 30;
            pBuilding->defenderCharacterArr = CCArray::create();
            pBuilding->defenderCharacterArr->retain();
            pBuilding->defenderCharacterArr->addObject(unit);
            
            if (data->m_enCentralViewMode == CENTRALVIEW_BATTLE) {
                const AttackData* attackData = GameData::GetDataFromBaseAttackData("build_archertower");
                pBuilding->set_attack(attackData);
                pBuilding->unit_ai_cmd_ = UNIT_AI_STAND;
            }
        }
        // 平炮
        else if(buildingBaseLevelData->building_TypeID == DEFENSE_CANNON){
            LAnimation* animBase = LAnimManage::shareLAnimManage()->createLAnimation(buildingBaseLevelData->SWF, pBuilding);
            pBuilding->set_ani_state(animBase);
            pBuilding->ani_state_->m_pCharSprite->setScale(1.0f);
            m_tmxMap->addChild(pBuilding->ani_state_->m_pCharSprite);
            
            // 指定在自己家ai及转向间隔时间
            if (data->m_enCentralViewMode == CENTRALVIEW_BATTLE) {
                const AttackData* attackData = GameData::GetDataFromBaseAttackData("build_cannon");
                pBuilding->set_attack(attackData);
                pBuilding->unit_ai_cmd_ = UNIT_AI_STAND;
            }else{
                pBuilding->unit_ai_cmd_ = UNIT_AI_STAND_CANNON;
                pBuilding->m_role_time = Until::millisecondNow() + 4000;
            }
        }
        // 加农炮
        else if(buildingBaseLevelData->building_TypeID == DEFENSE_MORTAR)
        {
            LAnimation* animBase = LAnimManage::shareLAnimManage()->createLAnimation(buildingBaseLevelData->SWF, pBuilding);
            pBuilding->set_ani_state(animBase);
            pBuilding->ani_state_->setUnitTypeID(pBuilding->getTypeID()); //设置动画所属unit类型
            pBuilding->ani_state_->m_pCharSprite->setScale(1.0f);
            m_tmxMap->addChild(pBuilding->ani_state_->m_pCharSprite);
            pBuilding->action_ = "idle_1";
            pBuilding->ani_state_->run_action("idle_1", pBuilding->direction_);
            

            // 指定在自己家ai及转向间隔时间
            if (data->m_enCentralViewMode == CENTRALVIEW_BATTLE) {
                const AttackData* attackData = GameData::GetDataFromBaseAttackData("build_mortar");
                pBuilding->set_attack(attackData);
                pBuilding->unit_ai_cmd_ = UNIT_AI_STAND;
            }else{
                pBuilding->unit_ai_cmd_ = UNIT_AI_STAND_CANNON;
                pBuilding->m_role_time = Until::millisecondNow() + 4000;
            }
        }
        // 其它
        else {
            if (data->m_enCentralViewMode == CENTRALVIEW_BATTLE) {
                const AttackData* attackData = GameData::GetDataFromBaseAttackData("build_default");
                pBuilding->set_attack(attackData);
                pBuilding->unit_ai_cmd_ = UNIT_AI_STAND;
            }
        }
        
        // 如果是墙设置隐藏血条
        if (pBuilding->getTypeID() == BUILDINGTYPE_WALL){ // 如果是墙隐藏血条
            pBuilding->hide_hpbar = true;
        }
    
		return pBuilding;
	}
	return NULL;
}

Unit* CentralLayer::AddPeople( int unitID, CCPoint const& pos, Unit* parentUnit )
{
	Unit* people = Unit::create(NULL);
    people->setuuID(people_uuId);
    people_uuId++;
	const BasePeopleData* basePeopleData = GameData::GetDataFromBasePeopleData(unitID);
	{
        CCLog("%s",basePeopleData->Animation.c_str());
		LAnimation* animBase = LAnimManage::shareLAnimManage()->createLAnimation(basePeopleData->Animation, people);
		people->set_ani_state(animBase);
		people->ani_state_->m_pCharSprite->setScale(1.0f);
		m_tmxMap->addChild(people->ani_state_->m_pCharSprite);
	}

	const UnitClass* unitclass = GameData::GetUnitClassData(unitID);
	people->setUnitClass(unitclass);
	
    CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    if (data->m_enCentralViewMode == CENTRALVIEW_BATTLE) {
        const AttackData* attackData = GameData::GetDataFromBaseAttackData("role_default");
        people->set_attack(attackData);
        people->unit_ai_cmd_ = UNIT_AI_STAND;
    }

    // 放兵随机一个范围内
	b2Vec2 rBirthPos = to_b2Vec2(pos);
	if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enCentralViewMode != CENTRALVIEW_SELF && !parentUnit)
	{
		float const half_len = BUILDINTBASEGRID_EDGE_LEN * 0.5f;
		iBox2 const mapBound(to_iVec2(0, 0), to_iVec2(MAPGRIDWIDTH-1, MAPGRIDHEIGHT-1));
		while (true) 
		{
			b2Vec2 rRandPos( CCRANDOM_MINUS1_1() * half_len, CCRANDOM_MINUS1_1() * half_len );
			rBirthPos += rRandPos;
			if (mapBound.IsContains(normal_title_covert_t::pos_to_index(rBirthPos))) {
				break;
			}
		}

	}
	
	people->setPosition(to_CCPoint(rBirthPos));
	people->setMapIndex( to_CCPoint(normal_title_covert_t::pos_to_index(rBirthPos)) );
    
    if (!parentUnit) {
        unit_list_->addObject(people);
    }
    
    // 战斗场景 放兵需要存储
	if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enCentralViewMode==CENTRALVIEW_BATTLE && !(NotNetworking)) 
	{
		if (SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData->m_enPVPMode!=BATTLE_MODE_PVP_REPLAY) 
		{
            if (!parentUnit) {
                if (!BattleRecorde::sharedBattleRecorde()->IsStartRecorde()) {
                    BattleRecorde::sharedBattleRecorde()->StartRecorde();
                }
                BattleRecorde::sharedBattleRecorde()->AddPeople(unitID, rBirthPos);
            }
		}
	}
	return people;
}

Unit* CentralLayer::AddNpcPeople(int unitID, CCPoint const& pos)
{
    Unit* people = Unit::create(NULL);
	{
		char const* fileName =  unitID==UNIT_NPC_BUILDING_WORKER_001? "character_worker_lv1": "character_woman_lv1";
		LAnimation* animBase = LAnimManage::shareLAnimManage()->createLAnimation(fileName, people);
		people->set_ani_state(animBase);
		people->ani_state_->m_pCharSprite->setScale(1.0f);
		m_tmxMap->addChild(people->ani_state_->m_pCharSprite);
	}
    
    people->action_ = "walk";
    people->ani_state_->run_action(people->action_, people->direction_);
	people->setTypeID(unitID);
    people->speed = 200/100*BUILDINTBASEGRID_EDGE_LEN;
	people->setuuID(people_uuId);
	people->hide_hpbar = true;

	people->setPosition(pos);
	people->setMapIndex( to_CCPoint(normal_title_covert_t::pos_to_index(to_b2Vec2(pos))) );
	people->setTag(people_uuId);

    unit_list_->addObject(people);
    
	people_uuId++;
    return people;
}

Obstacle* CentralLayer::AddObstacle(int unitID, CCPoint mapIndex)
{
	Obstacle* obstacle = Obstacle::create(build_uuId,unitID);
	
	const ObstaclesData* data = GameData::GetDataFromBaseObstacleData(unitID);
	
	//指定动画
	LAnimation* animBase = LAnimManage::shareLAnimManage()->createLAnimation(data->ExportName, obstacle);
	obstacle->set_ani_state(animBase);
	m_tmxMap->addChild(obstacle->ani_state_->m_pCharSprite);
	//运行baseaction
	obstacle->ani_state_->run_action(data->ExportNameBase, obstacle->direction_);
	
	
	CCPoint outPos = this->positionForIsoAt(mapIndex);
	obstacle->setPosition(outPos);
	obstacle->setMapIndex(mapIndex);
	obstacle->setTag(unitID);
	this->MarkGridBuildInfo(obstacle->getMapIndex(),obstacle->getWidth(),obstacle->getuuID(),obstacle);
	
	
	unit_list_->addObject(obstacle);
	
	build_uuId++;
	return obstacle;
}


LParticleUnit* CentralLayer::AddParticleEmitter(string file_,CCPoint pos, float scale, CCNode* node)
{
    LParticleUnit* emitter = LParticleUnit::create(file_);
    emitter->setEmitterPosition(pos);
    emitter->setEmitterScale(scale);
    node->addChild(emitter->m_emitter,10000);
    node->addChild(emitter,10000,2);
    particle_list_->addObject(emitter);
    
    return emitter;
}

// 回调函数
void CentralLayer::callBackAnim_Attack(CCNode* sender,void* u)
{
	// 对象攻击动画后切默认状态动画
	Unit *uu = (Unit*)u;
	uu->_change_unit_state(UNIT_STATE_STAND);
	
	// 对象攻击动画播放后 切下一条技能指令
	if (uu->attack) {
		uu->attack->toDoCmd(uu->attack->curAttack_Cmd);
	}
}
void CentralLayer::callBackAnim_Busy(CCNode* sender,void* u)
{
	Unit *pRole = (Unit*)u;
	// 临时
	if (pRole->is_unit_type(UT_NPC_RESOURCE_WORKER))
	{
		CCAssert(pRole->m_WorkerTimes>0, "");

		pRole->m_WorkerTimes--;

		if (pRole->m_WorkerTimes!=0)
		{
			// 再播放一次
			pRole->ani_state_->restart_action();			
		}
		else
		{
			CCAssert(pRole->m_ResouceTarget.size()>1, "");
			pRole->m_ResouceTarget.pop_back();
			MoveAResourceWorkerToNewTarget(pRole);
		}

		return;
	}
	
	// 对象攻击动画后切默认状态动画	

	MoveWorkerToNewPos(pRole, pRole->m_pWorkerTarget);
}


void CentralLayer::callBackAnim_Dead(CCNode* sender,void* u)
{
    // 对象攻击动画后切默认状态动画
	Unit *uu = (Unit*)u;

    if (uu->is_unit_type(UT_ROLE)) {
        uu->remove();
    }
}
void CentralLayer::callBackAnim_Celebrate(CCNode* sender,void* u)
{
    // 对象攻击动画后切默认状态动画
	Unit *uu = (Unit*)u;
    
    if (uu->is_unit_type(UT_ROLE)) {
        uu->_change_unit_state(UNIT_STATE_DEAD);
    }
}

void CentralLayer::callBackAnim_Steer(CCNode* sender,void* u)
{
    // 对象攻击动画后切默认状态动画
	Unit *uu = (Unit*)u;
    
    if (uu->getTypeID() == DEFENSE_MORTAR) {
        // idle状态 
        if (uu->unit_state_ == UNIT_STATE_STAND) {
            if (uu->action_ == "steer_leftmiddle") {
                uu->action_ = "idle_2";
                uu->ani_state_->run_action(uu->action_,CCPointZero);
            }else if(uu->action_ == "steer_middleright"){
                uu->action_ = "idle_3";
                uu->ani_state_->run_action(uu->action_,CCPointZero);
            }else if(uu->action_ == "steer_rightmiddle"){
                uu->action_ = "idle_2";
                uu->ani_state_->run_action(uu->action_,CCPointZero);
            }else if(uu->action_ == "steer_middleleft"){
                uu->action_ = "idle_1";
                uu->ani_state_->run_action(uu->action_,CCPointZero);
            }else if(uu->action_ == "steer_leftright"){
                uu->action_ = "idle_3";
                uu->ani_state_->run_action(uu->action_,CCPointZero);
            }else if(uu->action_ == "steer_rightleft"){
                uu->action_ = "idle_1";
                uu->ani_state_->run_action(uu->action_,CCPointZero);
            }
            
            
            if (uu->action_ == "steer_leftmiddle_preattack") {
                uu->action_ = "attack_2";
                uu->ani_state_->run_action(uu->action_,CCPointZero);
            }else if(uu->action_ == "steer_middleright_preattack"){
                uu->action_ = "attack_3";
                uu->ani_state_->run_action(uu->action_,CCPointZero);
            }else if(uu->action_ == "steer_rightmiddle_preattack"){
                uu->action_ = "attack_2";
                uu->ani_state_->run_action(uu->action_,CCPointZero);
            }else if(uu->action_ == "steer_middleleft_preattack"){
                uu->action_ = "attack_1";
                uu->ani_state_->run_action(uu->action_,CCPointZero);
            }else if(uu->action_ == "steer_leftright_preattack"){
                uu->action_ = "attack_3";
                uu->ani_state_->run_action(uu->action_,CCPointZero);
            }else if(uu->action_ == "steer_rightleft_preattack"){
                uu->action_ = "attack_1";
                uu->ani_state_->run_action(uu->action_,CCPointZero);
            }
        }
    }
}


void CentralLayer::AddInvalidCellInfo(unsigned int index,InvalidCell* info)
{
	InvalidCell* data = new InvalidCell;
	memcpy( data, info, sizeof(InvalidCell) );
	m_InvalidCell->insert(pair<unsigned int,InvalidCell*>(index,data));
}

bool CentralLayer::GetInvalidCellInfo(unsigned int index,InvalidCell* info)
{
	map<unsigned int,InvalidCell*>::iterator iter = m_InvalidCell->find( index );
	if( iter != m_InvalidCell->end() )
	{
		memcpy( info, iter->second, sizeof(InvalidCell) );
		return true;
	}
	return false;
}

int CentralLayer::getInvalidCellType(CCPoint index)
{
	int type = 0;
	CCPoint leftTop = ccp(index.x-1,index.y);
	CCPoint rightTop = ccp(index.x,index.y-1);
	CCPoint leftBottom = ccp(index.x,index.y+1);
	CCPoint rightBottom = ccp(index.x+1,index.y);
	
	
	InvalidCell info;
	if (!this->GetInvalidCellInfo(leftTop.x*MAPGRIDHEIGHT+leftTop.y,&info)) {
		type = InvalidCell_type_1;
		if (!this->GetInvalidCellInfo(rightTop.x*MAPGRIDHEIGHT+rightTop.y,&info)) {
			type = InvalidCell_type_5;
		}else if(!this->GetInvalidCellInfo(leftBottom.x*MAPGRIDHEIGHT+leftBottom.y,&info)){
			type = InvalidCell_type_8;
		}
		return type;
	}
	
	if (!this->GetInvalidCellInfo(rightTop.x*MAPGRIDHEIGHT+rightTop.y,&info)) {
		type = InvalidCell_type_2;
		if (!this->GetInvalidCellInfo(rightBottom.x*MAPGRIDHEIGHT+rightBottom.y,&info)) {
			type = InvalidCell_type_6;
		}
		return type;
	}
	
	if (!this->GetInvalidCellInfo(rightBottom.x*MAPGRIDHEIGHT+rightBottom.y,&info)) {
		type = InvalidCell_type_3;
		if (!this->GetInvalidCellInfo(leftBottom.x*MAPGRIDHEIGHT+leftBottom.y,&info)) {
			type = InvalidCell_type_7;
		}
		return type;
	}
	
	if (!this->GetInvalidCellInfo(leftBottom.x*MAPGRIDHEIGHT+leftBottom.y,&info)) {
		type = InvalidCell_type_4;
		return type;
	}
	
	return type;
}

void CentralLayer::getInvalidLocation()
{
	m_InvalidCell = new map<unsigned int,InvalidCell*>[MAPGRIDWIDTH*MAPGRIDHEIGHT];
	for (int m=0; m<unit_list_->count();m++ )
	{
		Unit *unit = (Unit*)unit_list_->objectAtIndex(m);
		if (unit->is_build_type())
		{
			CCPoint point = unit->getMapIndex();
			int lineNum = unit->m_stBuildSubstrate.m_Line;
			CCPoint topPoint;
			topPoint.x = point.x - lineNum;
			topPoint.y = point.y - lineNum;
			
			for( int i = topPoint.x; i < topPoint.x + lineNum+2; i++ )
			{
				for (int j = topPoint.y; j< topPoint.y + lineNum+2; j++) {
					InvalidCell info;
					if (!this->GetInvalidCellInfo(i*MAPGRIDHEIGHT+j,&info)) {
						MapGridLogicInfo mapInfo;
						if (this->GetMapGridLogicInfo(i*MAPGRIDHEIGHT+j,&mapInfo)) {
							if (mapInfo.bIsBiulded) {
								info.hide = true;
							}else {
								info.hide = false;
							}
						}
						this->AddInvalidCellInfo(i*MAPGRIDHEIGHT+j, &info);
					}
				}
			}
		}
	}
	
	for (int i=0; i<MAPGRIDHEIGHT; i++) {
		for (int j=0; j<MAPGRIDHEIGHT; j++) {
			InvalidCell info;
			if (this->GetInvalidCellInfo(i*MAPGRIDHEIGHT+j,&info) && !info.hide) {
				// 指定sp类型 并创建
				CCSprite *sp = NULL;
				
				int type = this->getInvalidCellType(ccp(i,j));
				switch (type) {
					case InvalidCell_type_0:
					{
						sp = CCSprite::create(GAME_FILE_TRANSFORM("Invalidcell_00",".png").c_str());
					}
						break;
					case InvalidCell_type_1:
					{
					   sp = CCSprite::create(GAME_FILE_TRANSFORM("Invalidcell_01",".png").c_str());
					}
						break;
					case InvalidCell_type_2:
					{
						sp = CCSprite::create(GAME_FILE_TRANSFORM("Invalidcell_02",".png").c_str());
					}
						break;
					case InvalidCell_type_3:
					{
						sp = CCSprite::create(GAME_FILE_TRANSFORM("Invalidcell_03",".png").c_str());
					}
						break;
					case InvalidCell_type_4:
					{
						sp = CCSprite::create(GAME_FILE_TRANSFORM("Invalidcell_04",".png").c_str());
					}
						break;
					case InvalidCell_type_5:
					{
						sp = CCSprite::create(GAME_FILE_TRANSFORM("Invalidcell_05",".png").c_str());
					}
						break;
					case InvalidCell_type_6:
					{
						sp = CCSprite::create(GAME_FILE_TRANSFORM("Invalidcell_06",".png").c_str());
					}
						break;
					case InvalidCell_type_7:
					{
						sp = CCSprite::create(GAME_FILE_TRANSFORM("Invalidcell_07",".png").c_str());
					}
						break;
					case InvalidCell_type_8:
					{
						sp = CCSprite::create(GAME_FILE_TRANSFORM("Invalidcell_08",".png").c_str());
					}
						break;
					default:
						break;
				}
                if (sp) {
                    sp->setAnchorPoint(ccp(0,0));
                    m_tmxMap->addChild(sp);
                    sp->setPosition(positionForIsoAt(ccp(i,j)));
                    invalidSpArr->addObject(sp);
                    sp->setVisible(false);
                }
            }
		}
	}
}

void CentralLayer::showInvalidLocation()
{
	for (int i=0; i<invalidSpArr->count(); i++) {
		CCSprite* sp = (CCSprite*)invalidSpArr->objectAtIndex(i);
		sp->setVisible(true);
	}
}

void CentralLayer::hideInvalidLocation()
{
	for (int i=0; i<invalidSpArr->count(); i++) {
		CCSprite* sp = (CCSprite*)invalidSpArr->objectAtIndex(i);
		sp->setVisible(false);
	}
}

void CentralLayer::Add_Star_count(int count)
{
    this->battle_star_count += count;
}
