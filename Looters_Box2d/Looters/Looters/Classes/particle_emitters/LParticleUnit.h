/***************************************************************
 author:    wangning
 write time: 2011.12.17
 function: 发射器对象
 ***************************************************************/
#pragma once
#include "cocos2d.h"
#include "CCParticleSystemQuad.h"

using namespace cocos2d;

enum particle_state
{
	//等待删除的状态。为了指针安全，在固定的pass删除
	//但此时应该完全无显示、无表现
	particle_STATE_GHOST   = -1,
	
	particle_STATE_NORMAL  = 0,
};

class LParticleUnit : public CCNode{
    
public:
    CCParticleSystem *m_emitter;
    particle_state particle_state_;
public:
    LParticleUnit();
    ~LParticleUnit();
    
    virtual void update( float dt );
    
    static LParticleUnit * node(std::string file_)
    {
        return create(file_);
    }
    
    static LParticleUnit * create(std::string file_)
    {
        LParticleUnit *pRet = new LParticleUnit();
        if (pRet->init(file_))
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
    
    virtual bool init(std::string file_);
    
    void setEmitterPosition(CCPoint pos);
    void setEmitterScale(float scale);
    void setEmitterTotalParticles(int count);
};