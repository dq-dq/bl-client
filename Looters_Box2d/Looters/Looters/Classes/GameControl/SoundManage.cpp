#include "SoundManage.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"
using namespace CocosDenshion;

SoundManage* m_gSoundManage = NULL;
SoundManage::SoundManage()
{
    
}

SoundManage::~SoundManage()
{
    end();
}

SoundManage* SoundManage::GetSoundManageHandle( void )
{
	if( m_gSoundManage == NULL )
	{
		m_gSoundManage = new SoundManage();
	    if( !m_gSoundManage->Init() )
		{
			delete m_gSoundManage;
			m_gSoundManage = NULL;
		}
	}
    
	return m_gSoundManage;
}

void SoundManage::ReleaseSoundManage( void )
{
	if( m_gSoundManage )
	{
		delete m_gSoundManage;
		m_gSoundManage = NULL;
	}
}

bool SoundManage::Init( void )
{
	return true;
}

void SoundManage::preload_BackgroundMusics()
{
    
}

void SoundManage::preload_Effects()
{
    GameData::baseeffect_t::const_iterator pos;
	for( pos = GameData::m_mapEffectBaseData.begin(); pos != GameData::m_mapEffectBaseData.end(); ++pos )
	{
        const EffectData data = pos->second;
        
        if (!data.Sound.empty()) {
            string name = data.Sound;
            SimpleAudioEngine::sharedEngine()->preloadEffect(name.c_str());
        }
	}
}

void SoundManage::unload_Effects()
{
    GameData::baseeffect_t::const_iterator pos;
	for( pos = GameData::m_mapEffectBaseData.begin(); pos != GameData::m_mapEffectBaseData.end(); ++pos )
	{
        const EffectData data = pos->second;
        
        if (!data.Sound.empty()) {
            string name = data.Sound;
            SimpleAudioEngine::sharedEngine()->unloadEffect(name.c_str());
        }
	}
}

void SoundManage::end()
{
    SimpleAudioEngine::sharedEngine()->end();
}

void SoundManage::_stopBackgroundMusic(bool bReleaseData)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(bReleaseData);
}

void SoundManage::_playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pszFilePath, bLoop);
}



