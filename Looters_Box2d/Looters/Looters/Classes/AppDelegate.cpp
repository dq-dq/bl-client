#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

#include "NetMessageManager.h"
#include "GameControl.h"
#include "cocos2d.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
    CCLog("AppDelegate init");
}

AppDelegate::~AppDelegate()
{
    delete GameControl::GetGameControl();
    CocosDenshion::SimpleAudioEngine::end();
    NetMessageManager::ReleaseMessageManager();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    TargetPlatform target = getTargetPlatform();//获取当前设备类型
    
    if (target == kTargetIpad){//如果是Ipad
        if (pDirector->enableRetinaDisplay(true)){ //如果开启高清视网膜
            
        }else {
        }
    }
    else if (target == kTargetIphone) {//如果是iphone
        if (pDirector->enableRetinaDisplay(true))
        {
        }
        else
        {
        }
    }
    else if (target == kTargetAndroid)//如果是android
    {
    }
    else if (target == kTargetWindows)//如果是Windows
    {
    }
    else if (target == kTargetMacOS)//如果是MacOS
    {
    }
    

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call thisdf
    pDirector->setAnimationInterval(1.0 / 60);
   
    // game init
    CCScheduler * scheduler = CCDirector::sharedDirector()->getScheduler();
    scheduler->scheduleSelector(schedule_selector(AppDelegate::AppUpdate), this, 1.0f/60, false);
    
    if( GameControl::RunGameControl() )
	{
		NetMessageManager::GetMessageManager();
	}

	if(  SceneManage::GetSceneManageHendle() )
	{
        SceneManage::GetSceneManageHendle()->RunScece( SCENE_LOGIN, false );
	}
   
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    
    CCUserDefault::sharedUserDefault()->flush();
    
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    pCentralScene->m_pCentralLayer->accountIntervalTime = 0;
    pCentralScene->m_pCentralLayer->isAccount = false;
    pCentralScene->m_pCentralLayer->uploadAccount();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}


void AppDelegate::AppUpdate( float dt )
{
    //框架主逻辑
	if( GameControl::GetGameControl() )
		GameControl::GetGameControl()->Run(dt);
    
	//网络逻辑
	if( NetMessageManager::GetMessageManager() )
		NetMessageManager::GetMessageManager()->NetMessageLogic(dt);
}
