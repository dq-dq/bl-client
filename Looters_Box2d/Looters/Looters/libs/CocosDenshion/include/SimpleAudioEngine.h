/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2010      Steve Oldmeadow

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef _SIMPLE_AUDIO_ENGINE_H_
#define _SIMPLE_AUDIO_ENGINE_H_

#include <stddef.h>
#include "Export.h"
#include <typeinfo>
#include <ctype.h>
#include <string.h>

namespace CocosDenshion {

class TypeInfo
{
public:
    virtual long getClassTypeInfo() = 0;
};

static inline unsigned int getHashCodeByString(const char *key)
{
	unsigned int len = strlen(key);
	const char *end=key+len;
	unsigned int hash;

	for (hash = 0; key < end; key++)
	{
		hash *= 16777619;
		hash ^= (unsigned int) (unsigned char) toupper(*key);
	}
	return (hash);
}

/**
@class          SimpleAudioEngine
@brief          offer a VERY simple interface to play background music & sound effect
*/

class EXPORT_DLL SimpleAudioEngine : public TypeInfo
{
public:
    SimpleAudioEngine();
    ~SimpleAudioEngine();

    virtual long getClassTypeInfo() {
        return getHashCodeByString(typeid(CocosDenshion::SimpleAudioEngine).name());
    }

    /**
    @brief Get the shared Engine object,it will new one when first time be called
    */
    static SimpleAudioEngine* sharedEngine();

    /**
    @brief Release the shared Engine object
    @warning It must be called before the application exit, or a memroy leak will be casued.
    */
    static void end();

    /**
     @brief Preload background music 提前载入音频
     @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
     */
    void preloadBackgroundMusic(const char* pszFilePath);
    
    /**
    @brief Play background music    播放背景音乐，是否循环播放
    @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
    @param bLoop Whether the background music loop or not
    */
    void playBackgroundMusic(const char* pszFilePath, bool bLoop);
    void playBackgroundMusic(const char* pszFilePath) {
    	this->playBackgroundMusic(pszFilePath, false);
    }

    /**
    @brief Stop playing background music    停止背景音乐
    @param bReleaseData If release the background music data or not.As default value is false
    */
    void stopBackgroundMusic(bool bReleaseData);
    void stopBackgroundMusic() {
    	this->stopBackgroundMusic(false);
    }

    /**
    @brief Pause playing background music   暂停背景音乐
    */
    void pauseBackgroundMusic();

    /**
    @brief Resume playing background music  恢复背景音乐
    */
    void resumeBackgroundMusic();

    /**
    @brief Rewind playing background music  重新播放背景音乐
    */
    void rewindBackgroundMusic();

    bool willPlayBackgroundMusic();

    /**
    @brief Whether the background music is playing  是否正在播放背景音乐
    @return If is playing return true,or return false
    */
    bool isBackgroundMusicPlaying();

    // properties
    /**
    @brief The volume of the background music max value is 1.0,the min value is 0.0 获得背景音乐音量
    */
    float getBackgroundMusicVolume();

    /**
    @brief set the volume of background music   设置背景音乐音量
    @param volume must be in 0.0~1.0
    */
    void setBackgroundMusicVolume(float volume);

    /**
    @brief The volume of the effects max value is 1.0,the min value is 0.0  获得音效音量
    */
    float getEffectsVolume();

    /**
    @brief set the volume of sound effecs   设置音效音量
    @param volume must be in 0.0~1.0
    */
    void setEffectsVolume(float volume);

    // for sound effects
    /**
    @brief Play sound effect    播放音效，是否循环播放，返回一个内部维护的ID号
    @param pszFilePath The path of the effect file,or the FileName of T_SoundResInfo
    @bLoop Whether to loop the effect playing, default value is false
    */
    unsigned int playEffect(const char* pszFilePath, bool bLoop);
    unsigned int playEffect(const char* pszFilePath) {
    	return this->playEffect(pszFilePath, false);
    }

    /**
    @brief Pause playing sound effect   暂定ID音效
    @param nSoundId The return value of function playEffect
    */
    void pauseEffect(unsigned int nSoundId);

    /**
    @brief Pause all playing sound effect   停止所有音效
    @param nSoundId The return value of function playEffect
    */
    void pauseAllEffects();

    /**
    @brief Resume playing sound effect  恢复ID音效
    @param nSoundId The return value of function playEffect
    */
    void resumeEffect(unsigned int nSoundId);

    /**
    @brief Resume all playing sound effect  恢复所有音效
    @param nSoundId The return value of function playEffect
    */
    void resumeAllEffects();

    /**
    @brief Stop playing sound effect    停止ID音效
    @param nSoundId The return value of function playEffect
    */
    void stopEffect(unsigned int nSoundId);

    /**
    @brief Stop all playing sound effects   停止所有音效
    */
    void stopAllEffects();

    /**
    @brief          preload a compressed audio file 提前载入音效
    @details        the compressed audio will be decode to wave, then write into an 
    internal buffer in SimpleaudioEngine
    */
    void preloadEffect(const char* pszFilePath);

    /**
    @brief          unload the preloaded effect from internal buffer    释放音效
    @param[in]        pszFilePath        The path of the effect file,or the FileName of T_SoundResInfo
    */
    void unloadEffect(const char* pszFilePath);
};

} // end of namespace CocosDenshion

#endif // _SIMPLE_AUDIO_ENGINE_H_

