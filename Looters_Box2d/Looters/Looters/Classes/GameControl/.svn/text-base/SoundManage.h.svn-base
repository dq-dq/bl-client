/***************************************************************
 author:    wangning
 write time: 2012.3.22
 function: 音乐音效管理
 ***************************************************************/

#include "cocos2d.h"
using namespace cocos2d;


class SoundManage {
    
public:
	SoundManage();
	~SoundManage();
    
public:
	bool Init( void );
    
	static SoundManage* GetSoundManageHandle( void );
	static void ReleaseSoundManage( void );
    
public:
    // 预加载所有音乐
    void preload_BackgroundMusics();
    // 预加载所有音效
    void preload_Effects();
    
    
    
    // 释放所有音效
    void unload_Effects();
    
    void end(); //释放声音
    
    
    
    // 声音播放控制
    void _stopBackgroundMusic(bool bReleaseData);
    void _playBackgroundMusic(const char* pszFilePath, bool bLoop);
};
