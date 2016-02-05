#include "CommonResource.h"

CommonResource::CommonResource(void)
{
}

CommonResource::~CommonResource(void)
{
}

int CommonResource::getRandomInt(float max,float min){
	// Determine speed of the target
	float minDuration = min;
	float maxDuration = max;
	int rangeDuration = (int)(maxDuration - minDuration);
	int actualDuration = ( rand() % rangeDuration ) + (int)minDuration;

	CCLog("random value:%d",actualDuration);
	return actualDuration;
}
string CommonResource::getStringFromInt(int intvalue){
	char strFileName[64];
	sprintf(strFileName,"%d",intvalue);
	string result=strFileName;
	return result;
}
string CommonResource::getStringFromLongLong(long long longvalue){
	char strFileName[64];

	sprintf(strFileName,"%lld",longvalue);
	string result=strFileName;
	return result;
}
string CommonResource::getStringFromFloat(float floatvalue)
{
    char strFileName[64];
    
	sprintf(strFileName,"%f",floatvalue);
	string result=strFileName;
	return result;
}

int CommonResource::getIntFromString(const char * str){
	int n=-1; 
	n = atoi(str); 
	return n;
}

long CommonResource::getLongFromString( const char* str )
{
	long n = -1;
	n = atol(str);
	return n;
}

float CommonResource::getFloatFromString( const char* str)
{
    float n = -1;
    n = atof(str);
    return n;
}

string CommonResource::getStrnigFromBool(bool flag)
{
	if (flag)
	{
		return "true";
	} 
	else
	{
		return "false";
	}
}
bool CommonResource::getBoolFromeString( const char* str )
{
	if( "TRUE" == string(str) || "true" == string(str)||getIntFromString(str)>0 )
		return true;
	return false;
}

long CommonResource::millisecondNow()
{
	struct cc_timeval now; 
	CCTime::gettimeofdayCocos2d(&now, NULL); 
	return (now.tv_sec * 1000 + now.tv_usec / 1000);

}

long long CommonResource::getRealTime()
{
	time_t now_time;
	now_time=time(NULL);
    localtime(&now_time);
	return now_time;
}

void CommonResource::UTF_8ToUnicode(wchar_t* pOut,char *pText)
{
    char* uchar = (char *)pOut;
 
 	uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
 	uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);
 
 	return;
}

void CommonResource::GB2312ToUTF_8(string& pOut,char *pText, int pLen)
{
  	char buf[4];
  	memset(buf,0,4);
  
  	pOut.clear();
  
  	int i = 0;
  	while(i < pLen)
  	{
  		if( pText[i] >= 0)
  		{
  			char asciistr[2]={0};
  			asciistr[0] = (pText[i++]);
  			pOut.append(asciistr);
  		}
  		else
  		{
  			wchar_t* pbuffer = new wchar_t[pLen+1];
  			Gb2312ToUnicode(pbuffer,pText+i);
  
  			UnicodeToUTF_8(buf,pbuffer);
  
  			pOut.append(buf);
  
  			i += 2;

			delete []pbuffer;
  		}
  	}
  
  	return;
}

void CommonResource::Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer)
{
    size_t size = strlen(gbBuffer) + 1;

    mbstowcs(pOut,gbBuffer,size);
    return;
}
string CommonResource::calculation_d_h_m(int _time)
{
    char strTime[64];
    
    int d = 0;
    int h = 0;
    int m = 0;
    int s = 0;
    
    //有多少秒
    int time = _time;
    
    if (time != 0)
    {
        s = time%60;
        time = time/60;
        
        m = time%60;
        time = time/60;
        
        h = time%24;
        time = time/24;
        
        d = time;
        
    }
    
    if (d!=0)
    {
        if (h==0)
        {
            sprintf(strTime, "%dd",d);
        }
        else
        {
            sprintf(strTime, "%dd%dh",d,h);
        }
        
    }
    else if (h!=0)
    {
        if (m==0)
        {
            sprintf(strTime, "%dh",h);
        }
        else
        {
            sprintf(strTime, "%dh%dm",h,m);
        }
    }
    else if (m!=0)
    {
        if (s==0)
        {
            sprintf(strTime, "%dm",m);
        }
        else
        {
            sprintf(strTime, "%dm%ds",m,s);
        }
    }
    else if (s!=0)
    {
        sprintf(strTime, "%ds",s);
    }
    else
    {
        sprintf(strTime, "");
    }
    
    
    
    
    std::string sTime = strTime;
    
    return sTime;
}
void CommonResource::UnicodeToUTF_8(char* pOut,wchar_t* pText)
{
    char* pchar = (char *)pText;

    pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
    pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
    pOut[2] = (0x80 | (pchar[0] & 0x3F));

    return;
}