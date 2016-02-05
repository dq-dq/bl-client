#include "Unit.h"
#include "CentralLayer.h"


unit_type typid_to_unit_type(unsigned int typeID)
{
	unit_type result = UT_NONE;
	
	if (nogain_type_begin<=typeID && typeID<=nogain_type_end)
	{
		result = UT_NOGAIN_BUILD;
	}
	else if (army_type_begin<=typeID && typeID<= army_type_end)
	{
		result = UT_ARMY_BUILD;
	}
	else if (townhall_type_begin<=typeID && typeID<= townhall_type_end)
	{
		result = UT_TOWN_HALL_BUILD;
	}
	else if (resource_type_begin<=typeID && typeID<= resource_type_end)
	{
		result = UT_RESOURCE_BUILD;
	}
	else if ( defense_type_begin<=typeID && typeID<=defense_type_end)
	{
		result = UT_DEFENSE_BUILD;
	}
	else if (wall_type_begin<=typeID && typeID<= wall_type_end)
	{
		result = UT_WALL_BUILD;
	}
	else if (walker_type_begin<=typeID && typeID<= walker_type_end)
	{
		result = UT_WORKER_BUILD;
	}
	else if (npc_type_begin<=typeID && typeID<= npc_type_end)
	{
		result = UT_NPC_BUILD;
	}
	else if (people_type_begin<=typeID && typeID<= people_type_end)
	{
		result = UT_ROLE;
	}
	else if (missle_type_begin<=typeID && typeID<= missle_type_end)
	{
		result = UT_MISSLE;
	}
	else if (decoration_type_begin<=typeID && typeID<= decoration_type_end)
	{
		result = UT_DECORATE;
	}
	else if (npc_building_worker_begin<=typeID && typeID<= npc_building_worker_end)
	{
		result = UT_NPC_BUILDING_WORKER;
	}
	else if (npc_resource_worker_begin<=typeID && typeID<= npc_resource_worker_end)
	{
		result = UT_NPC_RESOURCE_WORKER;
	}
	
	return result;
}


Unit::Unit()
{
	sprite_ = NULL;
	shadow_sprite_ = NULL;
	bloodSprite = NULL;
    defenderCharacterArr = NULL;
	ani_state_ = NULL;
	action_ = "";
	action_restart_ = false;
	
	speed = 100.0f;
	hp = maxhp = 100;
	
	camp = 0;
	
	radius = 15.0f;
	height = 16.0f;
	
	offsetx = offsety = 0;
	
	hide_hpbar = false;
    hp_showtime = 0;
	
	lv = 0;
	Damage = 1;
	AttackRange = 200;
	blindRange = 60;
	AttackSpeed = 2.0f;
	AirTargets = true;
	GroundTargets = true;
	
	
	m_pCampfire = NULL;
	m_role_time = 0;
	target = NULL;
	
	attack = NULL;
	
	direction_ = ccp(1.0f, 0.0f);
	
	move_target_ = m_tPosition;
	unit_state_ = UNIT_STATE_STAND;
	
	unit_ai_cmd_ = UNIT_AI_NONE;
	
	m_PreferedTargetBuilding = -1;
	m_uuID = 0;
	m_u32ID = 0;
	m_uTypeID = 0;
	m_strName = "Unit";
	
	
	m_mapIndex = ccp(-1000.0f,-1000.0f);
	
	// 建筑特有
	m_pSubstrateBottom = NULL;
	z_state_ = UNIT_Z_NORMAL_STATE;
	m_pSpriteAttackArea = NULL;
	isHarvest = false;

	m_pWorkerTarget = NULL;
	m_pFromBuilding = NULL;
	
	m_WorkerTimes = 0;
}

Unit::~Unit()
{
	if (attack) {
		attack->release();
	}
}

Unit * Unit::create(UnitClass* uclass)
{
	Unit * pRet = new Unit();
	if (pRet->init(uclass)) {
		pRet->autorelease();  
	}else {
		delete pRet;
		pRet = NULL;
	}
	return pRet;
}

bool Unit::init(UnitClass* uclass)
{
	return true;
}

void Unit::setUnitClass(const UnitClass* uclass)
{
    setID(uclass->ID);
    
	speed = uclass->speed;
	camp = uclass->camp;
	hp = uclass->hp;
    
	maxhp = uclass->maxhp;
	offsetx = uclass->offsetx;
	offsety = uclass->offsety;
	radius = uclass->radius;
	height = uclass->height;
	hide_hpbar = uclass->hideHpbar;
	
	lv = uclass->lv;
	m_uTypeID = uclass->TypeID;
	Damage = uclass->Damage;
	AttackRange = uclass->AttackRange;
    blindRange = uclass->MinAttackRange;
	AttackSpeed = uclass->AttackSpeed;
	AirTargets = uclass->AirTargets;
	GroundTargets = uclass->GroundTargets;
	IsFlying = uclass->IsFlying;
	
	m_PreferedTargetBuilding = uclass->PreferedTargetBuilding;
    
    hide_hpbar = true;
}

void Unit::set_sprite(CCSprite* sprite)
{
	sprite_ = sprite;
}

void Unit::set_shadow_sprite(CCSprite* sprite)
{
	shadow_sprite_ = sprite;
	shadow_sprite_->setScaleX(0.7f);
	shadow_sprite_->setScaleY(0.42f);
	ccColor3B color = ccc3(0, 0, 0 );
	shadow_sprite_->setColor(color);
	shadow_sprite_->setOpacity(0.3f*255);
	shadow_sprite_->setAnchorPoint(ccp(0.5,0));
}

void Unit::set_ani_state(LAnimation* state)
{
	if (ani_state_) 
	{
		ani_state_->m_pCharSprite->removeFromParentAndCleanup(true);
		ani_state_->removeAllChildrenWithCleanup(true);
		ani_state_->release();
		ani_state_ = NULL;
	}
	if (state)
	{
		ani_state_ = state;
		ani_state_->setPosition(ccp(0,0));
		ani_state_->setAnchorPoint(ccp(0.5,0));
	}
}

void Unit::remove()
{
	if (unit_state_ == UNIT_STATE_GHOST)
	{
		return;
	}
	
	unit_state_ = UNIT_STATE_GHOST;
}

void Unit::clean()
{
    CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    // 删除对象
    if (m_pSubstrateBottom) {
        data->m_tmxMap->removeChild(m_pSubstrateBottom, false);
        m_pSubstrateBottom = NULL;
    }
    if (m_pSpriteAttackArea) {
        m_pSpriteAttackArea->removeAllChildrenWithCleanup(true);
        data->m_tmxMap->removeChild(m_pSpriteAttackArea, false);
        m_pSpriteAttackArea = NULL;
    }
    if (sprite_) {
        data->m_tmxMap->removeChild(sprite_, false);
        sprite_ = NULL;
    }
    if (shadow_sprite_) {
        data->m_tmxMap->removeChild(shadow_sprite_, false);
        shadow_sprite_ = NULL;
    }
    
    if (bloodSprite){
        bloodSprite->removeAllChildrenWithCleanup(true);
        data->m_tmxMap->removeChild(bloodSprite, false);
        bloodSprite = NULL;
    }
    if (ani_state_) {
        data->m_tmxMap->removeChild(ani_state_->m_pCharSprite, false);
        ani_state_->release();
        ani_state_ = NULL;
    }
}

void Unit::_apply_sprite_state()
{
	CCPoint position = this->getPosition();
	
	// 设置精灵对象和动画的位置
    if (is_build_type()) { //建筑
        if (sprite_)
        {
            sprite_->setPosition(ccp(position.x,position.y+m_stBuildSubstrate.m_Line*1.0f/2*BUILDINTBASEGRID_HEIGHT));
        }
        if (m_pSubstrateBottom)
        {
            m_pSubstrateBottom->setPosition(position);
        }
        if (ani_state_)
        {
            ani_state_->m_pCharSprite->setPosition(ccp(position.x,position.y+m_stBuildSubstrate.m_Line*1.0f/2*BUILDINTBASEGRID_HEIGHT));
        }
        
        if (m_pSpriteAttackArea) {
            m_pSpriteAttackArea->setPosition(sprite_->getPosition());
        }
        
        if (defenderCharacterArr) {
            for (int i=0; i<defenderCharacterArr->count(); i++) {
                Unit* childUnit = (Unit*)defenderCharacterArr->objectAtIndex(i);
                if (childUnit->ani_state_) {
                    CCPoint point = sprite_->getPosition();
                    childUnit->setPosition(ccp(point.x+offsetx,point.y+offsety));
                    childUnit->ani_state_->m_pCharSprite->setPosition(ccp(point.x+offsetx,point.y+offsety));
                }
            }
        }
    }
	else 
	{
        if(sprite_){
            sprite_->setPosition(ccp(position.x+offsetx,position.y+offsety));
        }
        if (shadow_sprite_)
        {
            shadow_sprite_->setPosition(ccp(position.x,position.y));
        }
        if (ani_state_)
        {
            if (!IsFlying) {
                ani_state_->m_pCharSprite->setPosition(position);
            }else {
                ani_state_->m_pCharSprite->setPosition(ccp(position.x+offsetx,position.y+offsety));
            }
        }
	}
	
	
	// 绘制血条
	CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
	if( data->m_enCentralViewMode == CENTRALVIEW_BATTLE ){
		this->drawBlood();
	}
    
	// z值排序
	if (z_state_ == UNIT_Z_MAX_STATE) { // 特殊处理(建筑选中后将Z值设为最大)
        if (m_pSubstrateBottom) {
			if (m_pSubstrateBottom->getParent()) {
				m_pSubstrateBottom->getParent()->reorderChild(m_pSubstrateBottom,9999);
			}
		}
		if (sprite_) {
			sprite_->getParent()->reorderChild(sprite_,10000);
		}
		if (ani_state_ && ani_state_->m_pCharSprite) {
			ani_state_->m_pCharSprite->getParent()->reorderChild(ani_state_->m_pCharSprite,10000);
		}
        if (defenderCharacterArr) {
            for (int i=0; i<defenderCharacterArr->count(); i++) {
                Unit* childUnit = (Unit*)defenderCharacterArr->objectAtIndex(i);
                if (childUnit->ani_state_) {
                    CCPoint point = sprite_->getPosition();
                    childUnit->ani_state_->m_pCharSprite->getParent()->reorderChild(childUnit->ani_state_->m_pCharSprite,10001);
                }
            }
        }
		if (this->getParent())
		{
			this->getParent()->reorderChild(this, 10000);
		}
	}
	else{
        if (m_pSubstrateBottom) {
            if (m_pSubstrateBottom->getParent()) {
                m_pSubstrateBottom->getParent()->reorderChild(m_pSubstrateBottom,Z_SUBSTRATEBOTTOM_);
            }
        }
        
        if(sprite_)
        {
            if(is_unit_type(UT_MISSLE)){
                sprite_->getParent()->reorderChild(sprite_, Z_UNIT_MISSLE_);
            }
            else if (sprite_) {
                sprite_->getParent()->reorderChild(sprite_, MAPGLHEIGHT - (int)(sprite_->getPositionY()));
            }
        }
        
        if (ani_state_) {
            ani_state_->m_pCharSprite->getParent()->reorderChild(ani_state_->m_pCharSprite, MAPGLHEIGHT - (int)(ani_state_->m_pCharSprite->getPositionY()));
        }
        
		if (this->getParent())
        {
            this->getParent()->reorderChild(this, MAPGLHEIGHT - (int)(position.y));
        }
        
        if (defenderCharacterArr) {
            for (int i=0; i<defenderCharacterArr->count(); i++) {
                Unit* childUnit = (Unit*)defenderCharacterArr->objectAtIndex(i);
                if (childUnit->ani_state_) {
                    CCPoint point = childUnit->ani_state_->m_pCharSprite->getPosition();
                    childUnit->ani_state_->m_pCharSprite->getParent()->reorderChild(childUnit->ani_state_->m_pCharSprite, 10000);
                }
            }
        }
	}
	
	// 更新动画
	if (ani_state_)
	{
		if (action_ == "")
		{
			int us = (int)unit_state_;
			if (us >=0 && us < UNIT_STATE_COUNT)
			{
				action_ = "idle_1";
				ani_state_->run_action("idle_1", direction_);
			}
		}
		
		//apply direction
		if (action_restart_)
		{
			ani_state_->restart_action();
			action_restart_ = false;
		} else {
			ani_state_->run_action(action_,direction_);
		}
	}
}

void Unit::cmd_moveto(float x, float y)
{
	//y = RED_Y(y);
	move_target_ = ccp(x, y);
	if (unit_state_ != UNIT_STATE_MOVING)
	{
		_change_unit_state(UNIT_STATE_MOVING);
	}
}

void Unit::cmd_stop()
{
	move_target_ = this->getPosition();
	if (is_alive())
	{
		_change_unit_state(UNIT_STATE_STAND);
	}
}

bool Unit::cmd_hurt(int damage)
{
	if (hp > 0)
	{
		if (hp <= damage)
		{
			hp = 0;
            if (is_unit_type(UT_RESOURCE_BUILD) || is_unit_type(UT_TOWN_HALL_BUILD)) {
                cmd_resource(maxhp);
            }
			return true;
		}
		else
		{
			hp -= damage;
            if (is_unit_type(UT_RESOURCE_BUILD) || is_unit_type(UT_TOWN_HALL_BUILD)) {
                cmd_resource(maxhp-hp);
            }
		}
        
        if (this->hide_hpbar == true && getTypeID() != BUILDINGTYPE_WALL && hp_showtime == 0.0f) {
            this->IsShowBlood(true);
            hp_showtime = 4.0f;
        }
	}
	return false;
}

bool Unit::cmd_resource(int cutHp)
{
    if (NotNetworking) {
        return false;
    }
    if (this->upgrade_state_ != UNIT_UPGRADE_NONE) {
        return false;
    }
    
    CentralData* centralData = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    CentralData::M_UserMapData* userMapdata = centralData->GetM_UserMapData(getuuID());
    //玩家金币数增加 /匹配玩家金币减少
    
    if (userMapdata->building_id == RESOURCE_GOLDMINE || userMapdata->building_id == RESOURCE_GOLDSTORAGE) {
        int precount = userMapdata->cut_collect_count;
        if (userMapdata->building_id == RESOURCE_GOLDMINE) {
            userMapdata->cut_collect_count = round(cutHp*1.0f*userMapdata->collect_count/maxhp); // 计算打一次获取资源
        }else{
            userMapdata->cut_collect_count = round(cutHp*1.0f*userMapdata->collect_count/maxhp); // 计算打一次获取资源
        }
        
        if (userMapdata->cut_collect_count >= userMapdata->collect_count) {
            userMapdata->cut_collect_count = userMapdata->collect_count;
        }
        if(precount != userMapdata->cut_collect_count) {
            CCLog("减少金币数量%d",userMapdata->cut_collect_count);
            CCNode* resourceUnit_ = sprite_->getChildByTag(2);
            if (resourceUnit_ == NULL) {
                const EffectData* effectData = GameData::GetDataFromBaseEffectData("Collect Gold");
                SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->AddParticleEmitter(effectData->ParticleEmitter, ccp(sprite_->getContentSize().width/2,sprite_->getContentSize().height+30), 0.3f,sprite_);
                if (!effectData->Sound.empty()) {
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(effectData->Sound.c_str());
                }
            }
        }
    }
    if (userMapdata->building_id == RESOURCE_ELIXIRPUMP || userMapdata->building_id == RESOURCE_ELIXIRSTORAGE) {
        int precount = userMapdata->cut_collect_count;
        if (userMapdata->building_id == RESOURCE_ELIXIRPUMP) {
            userMapdata->cut_collect_count = round(cutHp*1.0f*userMapdata->collect_count/maxhp); // 计算打一次获取资源
        }else{
            userMapdata->cut_collect_count = round(cutHp*1.0f*userMapdata->collect_count/maxhp); // 计算打一次获取资源
        }
                
        if (userMapdata->cut_collect_count >= userMapdata->collect_count) {
            userMapdata->cut_collect_count = userMapdata->collect_count;
        }
        if(precount != userMapdata->cut_collect_count) {
            CCLOG("减少药水数量%d",userMapdata->cut_collect_count);
            CCNode* resourceUnit_ = sprite_->getChildByTag(2);
            if (resourceUnit_ == NULL) {
                const EffectData* effectData = GameData::GetDataFromBaseEffectData("Collect Elixir");
                LParticleUnit* pu = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->AddParticleEmitter(effectData->ParticleEmitter, ccp(sprite_->getContentSize().width/2,sprite_->getContentSize().height-30), 0.3f,sprite_);
                pu->setEmitterTotalParticles(6);
                if (!effectData->Sound.empty()) {
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(effectData->Sound.c_str());
                }
            }
        }
    }
    if (userMapdata->building_id == BUILDINGTYPE_TOWNHALL) {
        int pregoldcount = userMapdata->cut_collect_count;
        userMapdata->cut_collect_count = round(cutHp*1.0f*userMapdata->collect_count/maxhp);  // 计算打一次获取金币数量
        int preelixircount = userMapdata->cut_elixir_count;
        userMapdata->cut_elixir_count = round(cutHp*1.0f*userMapdata->second_elixir_count/maxhp); // 计算打一次获取水数量
     
        if (userMapdata->cut_collect_count >= userMapdata->collect_count) {
            userMapdata->cut_collect_count = userMapdata->collect_count;
        }
        if(pregoldcount != userMapdata->cut_collect_count) {
            CCLog("大厅减少金币数量%d",userMapdata->cut_collect_count);
            CCNode* resourceUnit_ = sprite_->getChildByTag(2);
            if (resourceUnit_ == NULL) {
                const EffectData* effectData = GameData::GetDataFromBaseEffectData("Collect Gold");
                SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->AddParticleEmitter(effectData->ParticleEmitter, ccp(sprite_->getContentSize().width/2,sprite_->getContentSize().height+30), 0.3f,sprite_);
                if (!effectData->Sound.empty()) {
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(effectData->Sound.c_str());
                }
            }
        }
        
        if (userMapdata->cut_elixir_count >= userMapdata->second_elixir_count) {
            userMapdata->cut_elixir_count = userMapdata->second_elixir_count;
        }
        if(preelixircount != userMapdata->cut_elixir_count) {
            CCLog("大厅减少药水数量%d",userMapdata->cut_elixir_count);
            CCNode* resourceUnit_1 = sprite_->getChildByTag(3);
            if (resourceUnit_1 == NULL) {
                const EffectData* effectData = GameData::GetDataFromBaseEffectData("Collect Elixir");
                LParticleUnit* pu = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->AddParticleEmitter(effectData->ParticleEmitter, ccp(sprite_->getContentSize().width/2,sprite_->getContentSize().height-30), 0.3f,sprite_);
                pu->setEmitterTotalParticles(6);
                if (!effectData->Sound.empty()) {
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(effectData->Sound.c_str());
                }
                pu->setTag(3);
            }
        }
    }
    
    return false;
}

void Unit::force_position(float x, float y)
{
	this->setPosition(ccp(x,y));
	move_target_ = ccp(x, y);
	if (is_alive() && (is_unit_type(UT_ROLE) || is_unit_type(UT_NPC_BUILDING_WORKER) || is_unit_type(UT_NPC_RESOURCE_WORKER)))
	{
		_change_unit_state(UNIT_STATE_STAND);
	}
}

void Unit::change_direction(float dx, float dy)
{
	CCPoint p(dx, dy);
	float l = sqrtf(dx*dx + dy*dy);
	if (l >= 0.001f)
	{
		direction_.x = p.x/l;
		direction_.y = p.y/l;
	}
}

float Unit::GetBuildHalfHeight( )
{
	return BUILDINTBASEGRID_HEIGHT * 0.5f * m_stBuildSubstrate.m_Line;
}

b2Vec2 Unit::GetCenterPos( bool isUseIndex)
{
	b2Vec2 result(getPositionX(), getPositionY());
	
	if (isUseIndex)
	{
		result = normal_title_covert_t::index_to_pos(to_iVec2(m_mapIndex));
		result.y -= TITLE_HEIGHT_HALF;
	}
	

	// 建筑物
	if (is_build_type())
	{
		result.y += GetBuildHalfHeight();
	}
	
	return result;
};


void Unit::face_to(Unit* u)
{
	if (u && u != this)
	{
		CCPoint k = ccpSub( to_CCPoint(u->GetCenterPos()) , getPosition()) ;
		change_direction(k.x, k.y);
	}
}

void Unit::kill()
{
	_change_unit_state(UNIT_STATE_DEAD);
}

bool Unit::does_hate(Unit* other)
{
	if (camp != other->camp) {
		return true;
	}
	return false;
}

bool Unit::can_attack(Unit* other)
{
	return false;
}

bool Unit::check_range(Unit* other, float distance)
{
	CCPoint p = ccpSub(this->getPosition() , other->getPosition());
	return p.x*p.x + p.y*p.y <= distance*distance;
}

float Unit::get_distance(Unit* other)
{
	CCPoint p = ccpSub(this->getPosition(),other->getPosition());
	return sqrtf(p.x*p.x + p.y*p.y);
}

void Unit::_apply_movement(float timespan)
{

	if (!is_alive())
	{
		return;
	}
	
	CCPoint target;
	switch (unit_state_)
	{
	case UNIT_STATE_STAND:
		{
		}
			return;
	case UNIT_STATE_MOVING:
			target = move_target_;
			break;
	default:
		break;
	}
	

	CCPoint curPos = getPosition();
	CCPoint dp = ccpSub(target, curPos);
	float length = ccpLength(dp);
	
    if (length > 0.0001f)
	{
		direction_ = ccpMult(dp, 1./length);
	}

	float moveLen = (speed - speed * 0.5f* abs( direction_.y) ) * timespan;
	
	if (length < moveLen)
	{
		// 这里
		this->setPosition(target);
		m_ai_path.pop_back();

		if (m_ai_path.empty())
		{
			if (unit_state_ == UNIT_STATE_MOVING)
			{
				if (is_unit_type(UT_NPC_BUILDING_WORKER)) 
				{
					if (NULL==m_pWorkerTarget)
					{
						_change_unit_state(UNIT_STATE_DEAD);
					}
					else
					{
						_change_unit_state(UNIT_STATE_STAND);
					}
					
				}
				else if ( is_unit_type(UT_NPC_RESOURCE_WORKER) )
				{
					size_t num = m_ResouceTarget.size();
					if (0==num)
					{	
						// 战斗中逃回主基地
						_change_unit_state(UNIT_STATE_DEAD);
					}					
					else if (1==num)
					{
						// 到达目标, 资源都采集完
						// 回到主基地,消失
						m_ResouceTarget.clear();						
						unit_state_ = UNIT_STATE_STAND;
						ani_state_->m_pCharSprite->stopAllActions();						
						ani_state_->m_pCharSprite->setVisible(false);
						setVisible(false);
						m_role_time = Until::millisecondNow() +  10000;

					}
					else
					{
						_change_unit_state(UNIT_STATE_STAND);
						m_WorkerTimes = get_random_range(1, 7);
					}
					
				}				
				else 
				{
					_change_unit_state(UNIT_STATE_STAND);
					m_role_time = Until::millisecondNow() + Unit::get_next_walk_time();
				}

			}			
		}
		else
		{
			if (unit_ai_cmd_!=UNIT_AI_PATROL&& NULL!=this->target&& !this->target->is_unit_type(UT_WALL_BUILD) && m_ai_path.size() == 2) 
			{
				b2Vec2 lenDir = m_ai_path.front() - this->target->GetCenterPos();
				int x = 1+int( b2Abs( lenDir.x*8 / BUILDINTBASEGRID_EDGE_LEN));
				int y = 1+int( b2Abs( lenDir.y*8 / BUILDINTBASEGRID_EDGE_LEN));
				
				if (y>x) {
					x = y;
				}
				
				b2Vec2 const& dir = this->target->GetCenterPos() - m_ai_path.back();
				iVec2 index = dir_quad_title_random_index(-dir, x);
				index += quad_title_left_top_index_2(this->target->GetCenterPos(), x);
				m_ai_path.clear();				
				b2Vec2 pos = quad_title_covert_t::index_to_pos(index);
				m_ai_path.push_back(pos);
				
			}
			
			b2Vec2 const& pos = m_ai_path.back();
			cmd_moveto(pos.x, pos.y);
		}	
	}
	else
	{
		this->setPosition(ccpAdd(curPos, ccpMult(direction_, moveLen)));
		//this->setPosition(ccpAdd(curPos, movLen));
	}
}

void Unit::_change_unit_state(unit_state s)
{
    CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    CentralData* centralData = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    if (is_unit_type(UT_ROLE))
	{ // 角色
        unit_state_ = s;
        if (unit_state_ == UNIT_STATE_DEAD) {
            data->battle_currolecount++;
        }
        
        switch (unit_state_) {
            case UNIT_STATE_STAND: //站立
                action_ = "idle_1";
                ani_state_->run_action(action_, direction_);
                break;
            case UNIT_STATE_MOVING: //移动
                action_ = "walk";
                ani_state_->run_action(action_, direction_);
                break;
            case UNIT_STATE_DEAD: //死亡
                action_ = "die";
                ani_state_->run_action(action_, direction_);
                break;
            case UNIT_STATE_CHEER:
                action_ = "celebrate_1";
                ani_state_->run_action(action_, direction_);
                break;
            default:
                break;
        }
    }
	else if (is_unit_type(UT_NPC_BUILDING_WORKER))
	{
		unit_state_ = s;
		switch (unit_state_)
		{
			case UNIT_STATE_STAND: //站立
			
				action_= CCRANDOM_0_1()>0.5f? "busy_1": "busy_2";
				ani_state_->run_action(action_, direction_);
				break;
			case UNIT_STATE_MOVING: //移动
				action_ = "walk";
				ani_state_->run_action(action_, direction_);
				break;
			
			case UNIT_STATE_DEAD:
				CCAssert(NULL!=m_pFromBuilding, "");
				m_pFromBuilding = NULL;
				remove();
				break;
            default:
                break;
		}
	}
	else if (is_unit_type(UT_NPC_RESOURCE_WORKER))
	{
		unit_state_ = s;
		switch (unit_state_)
		{
			case UNIT_STATE_STAND: //站立				
				action_= "busy_1";
				ani_state_->run_action(action_, direction_);
				break;
				
			case UNIT_STATE_MOVING: //移动
				action_ = "walk";
				ani_state_->run_action(action_, direction_);
				break;
				
			case UNIT_STATE_DEAD:
				remove();
				break;
				
            default:
                break;
		}
	}
	else if (is_build_type())
	{   // 建筑
        unit_state_ = s;
		if (this->getTypeID() == DEFENSE_CANNON) {
            action_ = "idle_1";
            ani_state_->run_action(action_, direction_);
        }else if(this->getTypeID() == DEFENSE_MORTAR)
        {
            if (action_ == "attack_1") {
                action_ = "idle_1";
            }else if(action_ == "attack_2"){
                action_ = "idle_2";
            }else if(action_ == "attack_3"){
                action_ = "idle_3";
            }
            ani_state_->run_action(action_, direction_);
        }
        
		if (unit_state_ == UNIT_STATE_DEAD) {
            if (!is_unit_type(UT_WALL_BUILD)) {
                data->battle_curbuildcount++;
            }
            
            if (defenderCharacterArr) {
                for (int i=0; i<defenderCharacterArr->count(); i++) {
                    Unit* childUnit = (Unit*)defenderCharacterArr->objectAtIndex(i);
                    childUnit->clean(); // 清除自己点显示
                }
            }
			// 建筑死亡处理
			data->m_tmxMap->removeChild(sprite_, false);
			sprite_ = NULL;
            
            if(!this->is_unit_type(UT_WALL_BUILD) || this->getTypeID() == BUILDINGTYPE_DILEI){
                char strFile[64] = {0};
                sprintf(strFile,"build_destroy_%d_%d",m_stBuildSubstrate.m_Line,m_stBuildSubstrate.m_Row);
                
                sprite_ = CCSprite::create(GAME_FILE_TRANSFORM(strFile,".png").c_str());
                sprite_->setPosition(ccp(0,0));
                sprite_->setAnchorPoint(ccp(0.5f,0.5f));
                sprite_->setScale(0.5f);
                data->m_tmxMap->addChild(this->sprite_);
                
                
                // 声音特效
                const EffectData* effectData = GameData::GetDataFromBaseEffectData("Building Destroyed");
                if (!effectData->Sound.empty()) {
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(effectData->Sound.c_str());
                }
                
                CCPoint pos = to_CCPoint(this->GetCenterPos());
                for (int i=1; i<8; i++) {
                    string str = "p_build_destory_0";
                    str.append(CommonResource::getStringFromInt(i));
                    SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->AddParticleEmitter(str, pos, 0.5f,data->m_tmxMap);
                }
            }
			
			if(bloodSprite)
			{
				bloodSprite->setVisible(false);
			}
			
			data->RemoveGridBuildInfo(getMapIndex(), m_stBuildSubstrate.m_Line, getuuID(), this);

			// 修改上传建筑数据信息
            CentralData::M_UserMapData* obj = centralData->GetM_UserMapData(getuuID());
            if (obj) {
                obj->destory_status = 0;
            }
            
            if(is_unit_type(UT_TOWN_HALL_BUILD)){
                data->Add_Star_count(1); // 摧毁主基地加一星
            }
        }
    }
}

void Unit::_hp_showtime(float dt)
{
    if (hp_showtime != 0.0f) {
        hp_showtime -= dt;
        if (hp_showtime <=  0.0f) {
            hp_showtime = 0.0f;
            this->IsShowBlood(false);
        }
    }
}

void Unit::drawBlood(void)
{
	if (!this->hide_hpbar && this->is_alive()){
		CCPoint pos = ccp(0,0);
		if (ani_state_ || sprite_) {
			if (m_pSubstrateBottom) {
				pos = sprite_->getPosition();
			}else{
                if (ani_state_) {
                    pos = ani_state_->m_pCharSprite->getPosition();
                }
			}
			
			pos.x += this->offsetx;
			pos.y += this->offsety;
			pos.y += this->height + 4;
			pos.y += 0;
			pos.x = floor(pos.x);
			pos.y = floor(pos.y);
		}
		if (bloodSprite == NULL) {
			CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
			CCSpriteBatchNode *spriteSheet = NULL;
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GAME_FILE_TRANSFORM("ui_blood",".plist").c_str(),GAME_FILE_TRANSFORM("ui_blood",".png").c_str());
			
			spriteSheet = CCSpriteBatchNode::create(GAME_FILE_TRANSFORM("ui_blood",".png").c_str());
			
			bloodSprite = CCSprite::createWithSpriteFrameName(GAME_FILE_TRANSFORM("blood_bg",".png").c_str());
			bloodSprite->setAnchorPoint(ccp(0.5,0));
			bloodSprite->setPosition(pos);
			bloodSprite->setScaleX(0.15);
			bloodSprite->setScaleY(0.2);
			
			CCSprite* childSprite = CCSprite::createWithSpriteFrameName(GAME_FILE_TRANSFORM("blood_green",".png").c_str());
			childSprite->setAnchorPoint(ccp(0,0));
			childSprite->setPosition(ccp(0+1,0+2));
			bloodSprite->addChild(childSprite);
			childSprite->setTag(1);
			
			data->m_tmxMap->addChild(bloodSprite,3000);
		}else {
			bloodSprite->setPosition(pos);
		}
		
		CCSprite *child = NULL;
		if (0) {
			if (hp*1.0f/maxhp < 0.2) {
				child = (CCSprite*)bloodSprite->getChildByTag(3);
				if (child == NULL) {
					child = (CCSprite*)bloodSprite->getChildByTag(2);
					if (child == NULL) {
						child = (CCSprite*)bloodSprite->getChildByTag(1);
					}
					child->removeFromParentAndCleanup(true);
					
					CCSprite* childSprite = CCSprite::createWithSpriteFrameName(GAME_FILE_TRANSFORM("blood_red",".png").c_str());
					childSprite->setAnchorPoint(ccp(0,0));
					childSprite->setPosition(ccp(0+1,0+2));
					bloodSprite->addChild(childSprite);
					childSprite->setTag(3);
				}
			}else if(hp*1.0f/maxhp < 0.5){
				child = (CCSprite*)bloodSprite->getChildByTag(2);
				if (child == NULL) {
					child = (CCSprite*)bloodSprite->getChildByTag(1);
					child->removeFromParentAndCleanup(true);
					
					CCSprite* childSprite = CCSprite::createWithSpriteFrameName(GAME_FILE_TRANSFORM("blood_purple",".png").c_str());
					childSprite->setAnchorPoint(ccp(0,0));
					childSprite->setPosition(ccp(0+1,0+2));
					bloodSprite->addChild(childSprite);
					childSprite->setTag(2);
				}
			}else{
				child = (CCSprite*)bloodSprite->getChildByTag(1);
			}
		}
		if (bloodSprite) {
			child = (CCSprite*)bloodSprite->getChildByTag(1);
		}
		if (child) {
			float scale = hp*1.0f/maxhp;
			child->setScaleX(scale);
		}
	}
}

void Unit::IsShowBlood(bool flag)
{
    this->hide_hpbar = !flag;
    if (bloodSprite) {
        bloodSprite->setVisible(!this->hide_hpbar);
    }
}

//set get方法
void Unit::setID( unsigned int ID )
{
	m_u32ID = ID;
}

unsigned int Unit::getID( void )
{
	return m_u32ID;
}
void Unit::setTypeID( unsigned int TypeID )
{
	m_uTypeID = TypeID;
}

unsigned int Unit::getTypeID( void )
{
	return m_uTypeID;
}

void Unit::setuuID( int uuid )
{
	m_uuID = uuid;
}

int Unit::getuuID( void )
{
	return m_uuID;
}

void Unit::setName( string name )
{
	m_strName = name;
}

string Unit::getName( void )
{
	return m_strName;
}

void Unit::setMapIndex(CCPoint index){
	m_mapIndex = index;
}

CCPoint Unit::getMapIndex(void)
{
	return m_mapIndex;
}


unit_type Unit::get_unit_type() const
{	
	return typid_to_unit_type(m_uTypeID);
}

bool Unit::is_unit_type( unit_type ut ) const
{
	return ut == get_unit_type();
}

bool Unit::is_build_type() const
{
	return get_unit_type() < UT_ROLE;
}
