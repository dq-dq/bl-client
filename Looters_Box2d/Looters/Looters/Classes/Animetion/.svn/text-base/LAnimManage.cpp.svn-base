#include "LAnimManage.h"
#include "Until.h"
#include "CommonResource.h"
#include "Unit.h"

LAnimManage* LAnimManage::m_LAnimManage = NULL;

LAnimManage::LAnimManage(void)
{
}

LAnimManage::~LAnimManage(void)
{
}

LAnimManage* LAnimManage::shareLAnimManage()
{
    if(m_LAnimManage == NULL)
    {
        m_LAnimManage = new LAnimManage();
    }
    return m_LAnimManage;
}

CCFiniteTimeAction* LAnimManage::createAction( ActionData const& actionData, Unit* u, char const* directonName )
{
    CCArray* frames = CCArray::createWithCapacity(actionData.ActionFrame);
    char framename[256] = {0};
    
    //加农炮动画特殊处理
    if (u->getTypeID() == DEFENSE_MORTAR) {
        if(actionData.Name == "steer_leftmiddle" || actionData.Name == "steer_leftmiddle_preattack"){
            for(int i = 0; i<5; i++)
            {
                sprintf(framename,"%s_00%02d.png",(actionData.ExportName).c_str(),i);
                CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framename);
                frames->addObject(spriteFrame);
            }
        }
        else if(actionData.Name == "steer_middleright" || actionData.Name == "steer_middleright_preattack"){
            for(int i = 4; i<9; i++)
            {
                sprintf(framename,"%s_00%02d.png",(actionData.ExportName).c_str(),i);
                CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framename);
                frames->addObject(spriteFrame);
            }
        }
        else if(actionData.Name == "steer_rightmiddle" || actionData.Name == "steer_rightmiddle_preattack"){
            for(int i = 8; i>3; i--)
            {
                sprintf(framename,"%s_00%02d.png",(actionData.ExportName).c_str(),i);
                CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framename);
                frames->addObject(spriteFrame);
            }
        }
        else if(actionData.Name == "steer_middleleft" || actionData.Name == "steer_middleleft_preattack"){
            for(int i = 4; i>-1; i--)
            {
                sprintf(framename,"%s_00%02d.png",(actionData.ExportName).c_str(),i);
                CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framename);
                frames->addObject(spriteFrame);
            }
        }
        else if(actionData.Name == "steer_leftright" || actionData.Name == "steer_leftright_preattack"){
            for(int i = 0; i<9; i++)
            {
                sprintf(framename,"%s_00%02d.png",(actionData.ExportName).c_str(),i);
                CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framename);
                frames->addObject(spriteFrame);
            }
        }
        else if(actionData.Name == "steer_rightleft" || actionData.Name == "steer_rightleft_preattack"){
            for(int i = 8; i>-1; i--)
            {
                sprintf(framename,"%s_00%02d.png",(actionData.ExportName).c_str(),i);
                CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framename);
                frames->addObject(spriteFrame);
            }
        }
        
        
        else if(actionData.Name == "idle_1" || actionData.Name == "idle_2" || actionData.Name == "idle_3"){
                for(int i = 0; i<actionData.ActionFrame; i++)
                {
                    sprintf(framename,"%s_00%02d.png",(actionData.ExportName).c_str(),i);
                    
                    CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framename);
                    frames->addObject(spriteFrame);
                }
        }
        else{
            for(int i = 0; i<actionData.ActionFrame; i++)
            {
                if (0==strlen(directonName)) {
                    sprintf(framename,"%s_00%02d.png",(actionData.ExportName).c_str(),i);
                }else {
                    sprintf(framename,"%s_%s_00%02d.png",(actionData.ExportName).c_str(),directonName,i);
                }
                
                CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framename);
                frames->addObject(spriteFrame);
            }
        }
    }
    
    else{
        for(int i = 0; i<actionData.ActionFrame; i++)
        {
            if (0==strlen(directonName)) {
                sprintf(framename,"%s_00%02d.png",(actionData.ExportName).c_str(),i);
            }else {
                sprintf(framename,"%s_%s_00%02d.png",(actionData.ExportName).c_str(),directonName,i);
            }
            
            CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framename);
            frames->addObject(spriteFrame);
        }
    }
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, 0.1);
    
    CCAnimate* animate =  CCAnimate::create(animation);
    
    CCActionInterval* actionInterval =(CCActionInterval*)(CCSequence::create(animate,NULL));
    
    CCFiniteTimeAction*  action = NULL;
    
    if (actionData.Looping) {
        if(actionData.Name == "celebrate_1" || actionData.Name == "celebrate_1"){
            action = CCSequence::create(animate,CCCallFuncND::create(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer, callfuncND_selector(CentralLayer::callBackAnim_Celebrate), (void*)u),NULL);
        }else{
            action = CCRepeatForever::create(actionInterval);
        }
    }else {
        if (actionData.Name == "attack_1" || actionData.Name == "attack_2" || actionData.Name == "attack_3") {
            action = CCSequence::create(animate,CCCallFuncND::create(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer, callfuncND_selector(CentralLayer::callBackAnim_Attack), (void*)u),NULL);
        }
        else if(actionData.Name == "busy_1" || actionData.Name == "busy_2" || actionData.Name == "busy_3"){
            action = CCSequence::create(animate,CCCallFuncND::create(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer, callfuncND_selector(CentralLayer::callBackAnim_Busy), (void*)u),NULL);
        }
        else if(actionData.Name == "die"){
            action = CCSequence::create(animate,CCCallFuncND::create(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer, callfuncND_selector(CentralLayer::callBackAnim_Dead), (void*)u),NULL);
        }
        else if(actionData.Name == "steer_leftmiddle" || actionData.Name == "steer_middleright"
                || actionData.Name == "steer_rightmiddle" || actionData.Name == "steer_middleleft" || actionData.Name == "steer_leftright" || actionData.Name == "steer_rightleft" ||
                 actionData.Name == "steer_leftmiddle_preattack" || actionData.Name == "steer_middleright_preattack"
                 || actionData.Name == "steer_rightmiddle_preattack" || actionData.Name == "steer_middleleft_preattack" || actionData.Name == "steer_leftright_preattack" || actionData.Name == "steer_rightleft_preattack")
        {
            action = CCSequence::create(animate,CCCallFuncND::create(SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer, callfuncND_selector(CentralLayer::callBackAnim_Steer), (void*)u),NULL);
        }
    }
    action->retain();
    return action;
}

LAction LAnimManage::createLAction( ActionData const& actionData,Unit* u )
{
    LAction laction;
    if (actionData.HasDirections) {
        if(u->getTypeID() == DEFENSE_CANNON){
            laction.action[0] = createAction(actionData, u,"left1");
            laction.action[1] = createAction(actionData, u,"left2");
            laction.action[2] = createAction(actionData, u,"left3");
            laction.action[3] = createAction(actionData, u,"left4");
            laction.action[4] = createAction(actionData, u,"left5");
            laction.action[5] = createAction(actionData, u,"left6");
        }
        else{
            laction.action[0] = createAction(actionData, u,"left");
            laction.action[1] = createAction(actionData, u,"lefttop");
            laction.action[2] = createAction(actionData, u,"leftbottom");
        }
    }else {
        laction.action[0] = createAction(actionData, u,"");
    }
    return laction;
}

LAnimation* LAnimManage::createLAnimation( string const& animName,Unit*u )
{
    LAnimation* lAnim = LAnimation::create();
    lAnim->m_pCharSprite = CCSprite::create();
    //获取动画数据
    const BaseAnimationData* baseAnimData = GameData::GetDataFromBaseAnimationData(animName);	
    //将图片加载到Cache里
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GAME_FILE_TRANSFORM(animName.c_str(),".plist").c_str(),GAME_FILE_TRANSFORM(animName.c_str(),".png").c_str());
    
    
    map<std::string,const ActionData>::const_iterator pos;
	for( pos = baseAnimData->animData.begin(); pos != baseAnimData->animData.end(); ++pos )
	{
        const ActionData actionData = pos->second;

        LAction laction = LAnimManage::shareLAnimManage()->createLAction(actionData,u);
        lAnim->m_mapLAnim.insert(pair<string,const LAction>(actionData.Name,laction));
	}
    

    lAnim->retain();
    return lAnim;
}
