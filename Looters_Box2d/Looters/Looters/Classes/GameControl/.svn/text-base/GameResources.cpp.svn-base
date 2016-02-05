#include "GameResources.h"
#include "GameControl.h"

CCSize GameResources::m_sizeUseResources = CCSizeMake(0,0);

std::string GameResources::TransitionFile( const char* strFile ,const char* strExtensions)
{
	char file[256];
	memset(file,0,256);
    
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCApplication* application =  CCApplication::sharedApplication();
    TargetPlatform target = application->getTargetPlatform();//获取当前设备类型
    
    if (target == kTargetIpad){     //如果是Ipad
        
        if (pDirector->enableRetinaDisplay(true))
        { //如果开启高清
            sprintf(file,"%s%s%s",strFile,"_hd",strExtensions);
        }else {
            sprintf(file,"%s%s",strFile,strExtensions);
        }
        
    }else if (target == kTargetIphone) {    //如果是iphone
        
        if (pDirector->enableRetinaDisplay(true))   
        {//如果开启高清
            sprintf(file,"%s%s%s",strFile,"_hd",strExtensions);
        }
        else
        {
            sprintf(file,"%s%s",strFile,strExtensions);
        }
        
    }else if (target == kTargetAndroid)//如果是android
    {
    }else if (target == kTargetWindows)//如果是Windows
    {
    }
    else if (target == kTargetMacOS)//如果是MacOS
    {
    }

    Log__(file);
	
    std::string sFile = file;
	return sFile;
}

int GameResources::getRandomInt(float max,float min){
	// Determine speed of the target
	float minDuration = min;
	float maxDuration = max;
	int rangeDuration = (int)(maxDuration - minDuration);

	int actualDuration = ( rand() % rangeDuration ) + (int)minDuration;

	CCLog("random value:%d",actualDuration);
	return actualDuration;
}

unsigned long long GameResources::GetSysTime( void )
{
	timeb t;
	ftime(&t);

	return (unsigned long long)(1000 * t.time + t.millitm);
}

bool GameResources::compareStrEq(const char * str1,const char * str2){
	int eq=strcmp(str1,str2);

	if (eq==0){
		return true;
	}else{
		return false;
	}
}