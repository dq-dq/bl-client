#include "LParticleUnit.h"
#include "cocos2d.h"
using namespace cocos2d;

LParticleUnit::LParticleUnit()
{

}
LParticleUnit::~LParticleUnit()
{
    
}


void LParticleUnit::update(float dt)
{
    m_emitter->removeFromParentAndCleanup(false);
    particle_state_ = particle_STATE_GHOST;
}

bool LParticleUnit::init(std::string file_){
    if (!CCNode::create()) {
        return false;
    }
    particle_state_ = particle_STATE_NORMAL;
    m_emitter = NULL;
    m_emitter = new CCParticleSystemQuad();
    std::string filename = file_;
    filename.append(".plist");
    m_emitter->initWithFile(filename.c_str());
    if (m_emitter) {
        this->schedule(schedule_selector(LParticleUnit::update),m_emitter->getDuration()+m_emitter->getLife()+m_emitter->getLifeVar());
    }
    return true;
}

void LParticleUnit::setEmitterPosition(CCPoint pos)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    if (m_emitter != NULL)
    {
        m_emitter->setPosition( pos );
    }
}

void LParticleUnit::setEmitterScale(float scale)
{
    if (m_emitter != NULL)
    {
        m_emitter->setScale(scale);
    }
}

void LParticleUnit::setEmitterTotalParticles(int count)
{
    if (m_emitter != NULL) {
         m_emitter->setTotalParticles(count);
    }
}

