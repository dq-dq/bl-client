/***************************************************************
author:    wangning
write time: 2012.3.22
function: 关于资源，对资源的功能可以写在这里
***************************************************************/
#pragma once 
#include "cocos2d.h"
using namespace cocos2d;
#include <time.h>
#include <sys/timeb.h>

class GameResources
{
public:
	static std::string TransitionFile( const char* strFile ,const char* strExtensions);
    
    
	static int getRandomInt(float max,float min);
	static unsigned long long GetSysTime( void );
public:
	static CCSize  m_sizeUseResources;

	//比较两个字符串是否相等
	static bool compareStrEq(const char *,const char *);
};

#define GAME_FILE_TRANSFORM(P,E) GameResources::TransitionFile(P,E)