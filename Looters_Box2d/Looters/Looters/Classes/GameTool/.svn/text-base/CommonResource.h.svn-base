#ifndef __CommonResource_H__
#define __CommonResource_H__

#pragma once
#include "cocos2d.h"
#include "platform.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d;

#define PI 3.141592653

class CommonResource
{
public:
	CommonResource(void);
	~CommonResource(void);

	static int getRandomInt(float max,float min);
    
	static string getStringFromInt(int intvalue);

	static string getStringFromLongLong(long long longvalue);

    static string getStringFromFloat(float floatvalue);
    
	static int getIntFromString(const char * str);

	static string getStrnigFromBool(bool flag);

	static bool getBoolFromeString( const char* str );

	static long getLongFromString( const char* str );
    
    static float getFloatFromString( const char* str);

	static long millisecondNow(void);

	static long long getRealTime(void);
	
	static void UTF_8ToUnicode(wchar_t* pOut,char *pText);

	static void GB2312ToUTF_8(string& pOut,char *pText, int pLen);
	
	static void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);

	static void UnicodeToUTF_8(char* pOut,wchar_t* pText);
    
    static string calculation_d_h_m(int _time);
};
#endif