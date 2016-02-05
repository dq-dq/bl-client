#include "Attack.h"
#include "Unit.h"
#include "Missle.h"
#include "CentralLayer.h"
#include "SimpleAudioEngine.h"

Attack::Attack()
{
    curAttack_Cmd = -1;
    src = NULL;
    dest = NULL;
    
    volume = 1.0f;
}

Attack::~Attack()
{
}

// 初始化 在游戏对象创建的时候创建一次 技能在整个生命周期过程中一直存在
Attack* Attack::newAttackClass(Unit* sc,const AttackData* data)
{
    Attack* atk = new Attack();
    if (atk->init(sc, data)) {
        atk->autorelease();
    }else {
        delete atk;
        atk = NULL;
    }

	return atk;
}

bool Attack::init(Unit* sc,const AttackData* data)
{
    attackData = data;
    src = sc;
    begin = true;
    cdt = (long long)src->AttackSpeed;
    cddt = Until::millisecondNow()+(long long)src->AttackSpeed;
    
    if (src->is_unit_type(UT_ROLE)) {
        const BasePeopleData* peopleData = GameData::GetDataFromBasePeopleData(src->getID());
        if (peopleData && !peopleData->AttackEffect.empty()) {
            const EffectData* effectData = GameData::GetDataFromBaseEffectData(peopleData->AttackEffect);
            if (effectData && !effectData->Sound.empty()) {
                soundname = effectData->Sound;
                volume = effectData->Volume/100.0f;
            }
        }
    }
    else if(src->is_build_type())
    {
        const BaseBuildingLevelData* buildData = GameData::GetDataFromBaseBuildingLevelData(src->getID());
        if (!buildData->AttackEffect.empty()) {
            const EffectData* effectData = GameData::GetDataFromBaseEffectData(buildData->AttackEffect);
            if (effectData && !effectData->Sound.empty()) {
                soundname = effectData->Sound;
                volume = effectData->Volume/100.0f;
            }
        }
    }
    
    return true;
}

bool Attack::useable()
{
    if (begin) {
        begin = false;
        return true;
    }
    return false;
}

// 如果有目标给技能对象指定目标
void Attack::use(Unit* t)
{
    if (curAttack_Cmd == -1) { // 第一次使用技能
        cddt = Until::millisecondNow()+(long long)src->AttackSpeed;
        curAttack_Cmd = 0;
    }
    
    dest = t;
    toDoCmd(curAttack_Cmd);
}

// 设置技能的CD时间
void Attack::setCD(long tt)
{
    long t = tt;
    cddt = Until::millisecondNow()+(long long)t;
}

void Attack::resetCD()
{
    cddt = Until::millisecondNow()+(long long)src->AttackSpeed;
}

// 技能的更新
void Attack::attack_update(float time)
{
    if (curAttack_Cmd == Attack_Cmd_End && Until::millisecondNow() > cddt )
	{ //重置技能的冷却时间用
        cddt = Until::millisecondNow()+cdt;
        begin = true;
        curAttack_Cmd = 0;
    }
}

// 技能开始
bool Attack::skillBeginPhaseTM()
{
    curAttack_Cmd = Attack_Cmd_Sound;
    toDoCmd(curAttack_Cmd);
    return true;
}

// 技能结束重新获取cd时间
void Attack::skillEndPhaseTM()
{
    if (Until::millisecondNow() > cddt) {
        cddt = Until::millisecondNow()+cdt;
        begin = true;
        curAttack_Cmd = Attack_Cmd_CheckUnitType;
    }
}

void Attack::force_end_skill()
{
	cddt = Until::millisecondNow()+cdt;
	begin = true;
	curAttack_Cmd = Attack_Cmd_CheckUnitType;
}

// 技能过程中主角播放动画
bool Attack::aniPhaseTM()
{
    // 播放完动画之后回调
    curAttack_Cmd = Attack_Cmd_Dmg;
    if(attackData->AtackAni){
        if (dest) {
            src->face_to(dest); // 当前对象朝向目标对象
        }
        
        if (src->getTypeID() == DEFENSE_MORTAR) {
            CCPoint angle = src->direction_;
            float alpha = acosf(angle.x);
            alpha = angle.y>0? alpha: -alpha;
            int ID;
            if ((alpha < 0 && alpha >= -PI/3) || (alpha < 2*PI/3 && alpha > 0)) {
                ID = 0;
            }
            else
            {
                ID = 1;
            }
            if (src->action_ == "idle_1") {
                if (ID == 0) {
                    src->action_ = "steer_leftmiddle_preattack";
                }else{
                    src->action_ = "attack_1";
                }
            }else if(src->action_ == "idle_2"){
                if (ID == 0) {
                    src->action_ = "steer_middleright_preattack";
                }else{
                    src->action_ = "steer_middleleft_preattack";
                }
            }else if(src->action_ == "idle_3"){
                if (ID == 1) {
                    src->action_ = "steer_rightmiddle_preattack";
                }else{
                    src->action_ = "attack_3";
                }
            }
            src->ani_state_->run_action(src->action_, src->direction_);
        }else{
            src->action_ = "attack_1";
            src->ani_state_->run_action("attack_1", src->direction_);
        }
    }else {
        if (src->getTypeID() == DEFENSE_ARCHERTOWER) {
            for (int i=0; i<src->defenderCharacterArr->count(); i++) {
                Unit* childUnit = (Unit*)src->defenderCharacterArr->objectAtIndex(i);
                if (childUnit->ani_state_) {
                    childUnit->action_ = "attack_1";
                    childUnit->ani_state_->run_action("attack_1", src->direction_);
                    if (dest) {
                        childUnit->face_to(dest); // 当前对象朝向目标对象
                        childUnit->ani_state_->run_action(childUnit->action_, childUnit->direction_);
                    }
                }
            }
        }
        toDoCmd(curAttack_Cmd);
    }
    
    // 播放声音和特效
    if (!soundname.empty()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundname.c_str());
    }
    
    //播放特效
    CentralLayer * layer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    if (src->getTypeID() == DEFENSE_MORTAR) {
        CCPoint pos = src->sprite_->getPosition();
        SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->AddParticleEmitter("Mortar_Fire_01", ccpAdd(pos,ccp(0,20)), 0.3f,layer->m_tmxMap);
        SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->AddParticleEmitter("Mortar_Fire_02", ccpAdd(pos,ccp(0,20)), 0.3f,layer->m_tmxMap);
    }
    else if(src->getTypeID() == DEFENSE_CANNON){
        CCPoint pos = src->sprite_->getPosition();
        LParticleUnit* u1 = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->AddParticleEmitter("Mortar_Fire_01", ccpAdd(pos,ccp(0,20)), 0.3f,layer->m_tmxMap);
        LParticleUnit* u2 = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->AddParticleEmitter("Mortar_Fire_02", ccpAdd(pos,ccp(0,20)), 0.3f,layer->m_tmxMap);
        switch (src->ani_state_->m_LChildID) {
            case 0:
                if (src->ani_state_->m_pCharSprite->isFlipX()) {
                    u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(6,-15)));
                    u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(6,-15)));
                }else{
                    u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(-6,-15)));
                    u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(-6,-15)));
                }
                break;
            case 1:
                if (src->ani_state_->m_pCharSprite->isFlipX()) {
                    u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(12,-10)));
                    u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(12,-10)));
                }else{
                    u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(-12,-10)));
                    u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(-12,-10)));
                }
                break;
            case 2:
                if (src->ani_state_->m_pCharSprite->isFlipX()) {
                    u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(17,-6)));
                    u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(17,-6)));
                }else{
                    u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(-17,-6)));
                    u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(-17,-6)));
                }
                break;
            case 3:
                if (src->ani_state_->m_pCharSprite->isFlipX()) {
                    u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(15,7)));
                    u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(15,7)));
                }else{
                    u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(-15,7)));
                    u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(-15,7)));
                }
                break;
            case 4:
                if (src->ani_state_->m_pCharSprite->isFlipX()) {
                    u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(15,7)));
                    u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(15,7)));
                }else{
                    u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(-15,7)));
                    u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(-15,7)));
                }
                break;
            case 5:
                if (src->ani_state_->m_pCharSprite->isFlipX()) {
                    u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(15,7)));
                    u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(15,7)));
                }else{
                    u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(-15,7)));
                    u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(-15,7)));
                }
                break;
            default:
                break;
        }
        
    }
    else if(src->getTypeID() == PEOPLE_Archer){
        CentralLayer * layer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
        CCPoint pos = src->ani_state_->m_pCharSprite->getPosition();
        LParticleUnit* u1 = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->AddParticleEmitter("musketeer_fire_01", pos, 0.05f,layer->m_tmxMap);
        LParticleUnit* u2 = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer->AddParticleEmitter("musketeer_fire_01", pos, 0.05f,layer->m_tmxMap);
        
        u1->m_emitter->setAnchorPoint(ccp(1,0));
        u2->m_emitter->setAnchorPoint(ccp(1,0));
        if (u1) {
            switch (src->ani_state_->m_LChildID) {
                case 0:
                    if (src->ani_state_->m_pCharSprite->isFlipX()) {
                        u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(15,7)));
                        u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(15,7)));
                        u1->m_emitter->setRotation(-170.0f);
                        u2->m_emitter->setRotation(-170.0f);
                    }else{
                        u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(-15,7)));
                        u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(-15,7)));
                        u1->m_emitter->setRotation(10.0f);
                        u2->m_emitter->setRotation(10.0f);
                    }
                    break;
                case 1:
                    if (src->ani_state_->m_pCharSprite->isFlipX()) {
                        u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(15,12)));
                        u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(15,12)));
                        u1->m_emitter->setRotation(155.0f);
                        u2->m_emitter->setRotation(155.0f);
                    }else{
                        u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(-15,12)));
                        u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(-15,12)));
                        u1->m_emitter->setRotation(25.0f);
                        u2->m_emitter->setRotation(25.0f);
                    }
                    break;
                case 2:
                    if (src->ani_state_->m_pCharSprite->isFlipX()) {
                        u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(15,0)));
                        u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(15,0)));
                        u1->m_emitter->setRotation(-155.0f);
                        u2->m_emitter->setRotation(-155.0f);
                    }else{
                        u1->setEmitterPosition(ccpAdd(u1->m_emitter->getPosition(),ccp(-15,0)));
                        u2->setEmitterPosition(ccpAdd(u2->m_emitter->getPosition(),ccp(-15,0)));
                        u1->m_emitter->setRotation(-25.0f);
                        u2->m_emitter->setRotation(-25.0f);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    return true;
}

bool Attack::playSoundTM()
{
    curAttack_Cmd = Attack_Cmd_Ani;
    toDoCmd(curAttack_Cmd);
    return true;
}

bool Attack::addDmgTM()
{
    if ((attackData->DmgType == 1) && dest && dest->is_alive()) {
        if (dest->cmd_hurt(src->Damage)) {
            dest->_change_unit_state(UNIT_STATE_DEAD);
        }
    }
    
    curAttack_Cmd = Attack_Cmd_Missle;
    toDoCmd(curAttack_Cmd);
    return true;
}

bool Attack::misslePhaseTM()
{
    if (attackData->IsMissle) {
        if (src->getTypeID() == DEFENSE_ARCHERTOWER) {
            
        }
        else {
            const Cmd_Missle* missleData = GameData::GetDataFromBaseMissleData(attackData->MissleID);
            
            Missle *missle = Missle::newMissleClass(src, dest,-1,missleData);
            
            
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GAME_FILE_TRANSFORM(missleData->AnimName.c_str(),".plist").c_str(),GAME_FILE_TRANSFORM(missleData->AnimName.c_str(),".png").c_str());
            string actionName = missleData->ActionID;
            actionName.append(".png");
            missle->sprite_ = CCSprite::createWithSpriteFrameName(actionName.c_str());
            
            missle->sprite_->setAnchorPoint(ccp(0.5,0.5));
            missle->sprite_->setPosition(ccp(0,0));
            
            CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
            data->m_tmxMap->addChild(missle->sprite_,2000);
            
            missle->hide_hpbar = true;
            missle->camp = -1;
            missle->setTypeID(UNIT_MISSLE_001);
            
            missle->setPosition(src->getPosition());
            
            
            if (src->is_unit_type(UT_ROLE)) {
                const BasePeopleData* peopleData = GameData::GetDataFromBasePeopleData(src->getID());
                if (peopleData && !peopleData->AttackEffect.empty()) {
                    const EffectData* effectData = GameData::GetDataFromBaseEffectData(peopleData->HitEffect);
                    if (effectData && !effectData->Sound.empty()) {
                        missle->soundname = effectData->Sound;
                        missle->volume = effectData->Volume/100.0f;
                    }
                }
            }
            else if(src->is_build_type())
            {
                const BaseBuildingLevelData* buildData = GameData::GetDataFromBaseBuildingLevelData(src->getID());
                if (!buildData->AttackEffect.empty()) {
                    const EffectData* effectData = GameData::GetDataFromBaseEffectData(buildData->HitEffect);
                    if (effectData && !effectData->Sound.empty()) {
                        missle->soundname = effectData->Sound;
                        missle->volume = effectData->Volume/100.0f;
                    }
                }
            }
            data->unit_list_->addObject(missle);  // 添加进队列显示刷新

        }
    }
   
    curAttack_Cmd = Attack_Cmd_End;
    toDoCmd(curAttack_Cmd);
    return true;
}

bool Attack::checkRangeTM()
{
    CentralLayer* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;

    if (dest == NULL) {
        return false;
    }
    
    // 如果目标不在攻击范围之内 取消攻击
    if (!data->checkUnitInArea(src->AttackRange,src,dest)) 
	{
        src->target = NULL;
        return false;
    }
    
    // 如果目标在攻击盲区范围之内 取消攻击
    if (src->getTypeID() == DEFENSE_MORTAR && data->checkUnitInArea(src->blindRange,src,dest))
	{
        src->target = NULL;
        return false;
    }
    
    curAttack_Cmd=Attack_Cmd_Began;
    toDoCmd(curAttack_Cmd);
    return true;
}

bool Attack::checkUnitTypeTM( void )
{
    if (dest && dest->getTypeID() == attackData->UnitType) { //判定目标是否为不可攻击类型
        src->target = NULL;
        return false;
    }
    if (dest && dest->IsFlying && !src->AirTargets) { // 判定目标是否为飞行单位 如果是 判定是否可以攻击
        src->target = NULL;
        return false;
    }
    curAttack_Cmd = Attack_Cmd_CheckRange;
    toDoCmd(curAttack_Cmd);
    return true;
}

void Attack::toDoCmd(int cmd)
{
    switch (cmd) {
        case Attack_Cmd_CheckUnitType:
            if(!checkUnitTypeTM())
            {
                this->force_end_skill();
            }
            break;
        case Attack_Cmd_CheckRange:
            if(!checkRangeTM())
            {
                this->force_end_skill();
            }
            break;
        case Attack_Cmd_Began:
            skillBeginPhaseTM();
            break;
        case Attack_Cmd_Ani:
            aniPhaseTM();
            break;
        case Attack_Cmd_Sound:
            playSoundTM();
            break;
        case Attack_Cmd_Dmg:
            addDmgTM();
            break;
        case Attack_Cmd_Missle:
            misslePhaseTM();
            break;
        case Attack_Cmd_End:
            skillEndPhaseTM();
            break;
        default:
            break;
    }
}









