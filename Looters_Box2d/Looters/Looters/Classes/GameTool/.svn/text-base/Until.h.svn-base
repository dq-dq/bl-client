/***************************************************************
 author:     wangning
 write time: 2012.10.20
 function:   基本工具类
 ***************************************************************/
#ifndef LootersAnim_Until_h
#define LootersAnim_Until_h
#pragma once
#include "cocos2d.h"
#include "LDeviceHelp.h"
#include "CommonResource.h"
USING_NS_CC;
using namespace std;

class Until {
public:
    Until(){
    }
public:    
    static string getmac()
    {
        return LDeviceHelp::getMacAddress();
    }
    
public:
    static std::vector<char*> splitString(const char* str, const char* c){
        std::vector<char*> vSplit;
        
        //  拷贝一个str
        int size = strlen(str)+1;
        char tmpStr[size];
        memset(tmpStr, 0, size);
        memcpy(tmpStr, str, size);
        
        //开始循环截取字符.
        char* p;
        p = strtok(tmpStr, c);
        while(p!=NULL) {
            //创建内存并存入vector
            int valueSize = strlen(p)+1;
            char* value = new char[valueSize];
            memset(value, 0, valueSize);
            memcpy(value, p, valueSize);
            vSplit.push_back(value);
            p = strtok(NULL, c);
        }
        return vSplit;
    }
    
    static void deleteVectorElement(std::vector<char*> v){
        std::vector<char*>::iterator ClassNameIt = v.begin();
        for(;ClassNameIt != v.end();++ClassNameIt)
        {    
            if(*ClassNameIt != NULL)
            {
                delete *ClassNameIt;
                *ClassNameIt = NULL;
            }  
        }
    }
    
    // char *拷贝
    static char* l_strcpy(char * a ,const char * b)
    {
        int i=0; 
        while (*b) a[i++]=*b++;
        a[i]=0;
        return a;
    }
    
    static float   area(CCPoint   p1,CCPoint   p2,CCPoint   p3){   
        return   fabs((p1.x-p3.x)*(p2.y-p3.y)-(p2.x-p3.x)*(p1.y-p3.y));   
    }
    
    static float   mul(CCPoint   p1,CCPoint   p2,CCPoint   p0){
        return((p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y));   
    }
    
    // 判定点在三角形内01
    static int  inside(CCPoint   tr[],CCPoint   p){   
        int   i;   
        for   (i=0;i<3;i++)   
            if   (mul(p,tr[i],tr[(i+1)%3])*mul(p,tr[(i+2)%3],tr[(i+1)%3])>0)   
                return   0;   
        return   1;   
    }
    
    // 判定点在三角形内02
    static int   inside2(CCPoint   tr[],CCPoint   p){   
        if   (fabs(area(tr[0],tr[1],tr[2])-   
                   area(p,tr[1],tr[2])-   
                   area(tr[0],p,tr[2])-   
                   area(tr[0],tr[1],p))<1.0e-20)   
            return   1;   
        else   
            return   0;   
    }   
    
    // 判定点在三角形内03
    // 就是判断点到三个顶点的夹角之和为2*PI   
    //   返回1   表示在那，0表示在外   
    static int   inside3(CCPoint   tr[],   CCPoint   p)
    {   
        CCPoint   p0,p1,p2;   
        p0.x   =   tr[0].x   -   p.x   ;     p0.y   =   tr[0].y   -   p.y;   
        p1.x   =   tr[1].x   -   p.x   ;     p1.y   =   tr[1].y   -   p.y;   
        p2.x   =   tr[2].x   -   p.x   ;     p2.y   =   tr[2].y   -   p.y;   
        
        double   arg1   =   acos((p0.x*p1.x   +   p0.y*p1.y)/sqrt(p0.x*p0.x   +   p0.y*p0.y)/sqrt(p1.x*p1.x+p1.y*p1.y));   
        double   arg2   =   acos((p0.x*p2.x   +   p0.y*p2.y)/sqrt(p0.x*p0.x   +   p0.y*p0.y)/sqrt(p2.x*p2.x+p2.y*p2.y));   
        double   arg3   =   acos((p2.x*p1.x   +   p2.y*p1.y)/sqrt(p2.x*p2.x   +   p2.y*p2.y)/sqrt(p1.x*p1.x+p1.y*p1.y));   
        
        if(   fabs(2*3.1415926-arg1-arg2-arg3)<0.0001   )   return   1;   
        return   0;   
    }   
    
    // 判定点在椭圆内
    //LTPoint RBPoint是椭圆所在矩形的两个点
    static int inellipse(CCPoint LTPoint,CCPoint RBPoint,CCPoint cter,CCPoint pnt)
    {
        float fRX = (RBPoint.x-LTPoint.x)/2.0f;
        float fRY = (RBPoint.y-LTPoint.y)/2.0f;
        if (pow(pnt.x-cter.x,2)+pow(pnt.y-cter.y,2)*(fRX/fRY)*(fRX/fRY)<=fRX*fRX) {
            return 1;
        }
        return 0;
    }
    
public:
    // 获取系统毫秒数  双击一般时间间隔是250ms～300ms
    static long long millisecondNow()
    { 
        struct cc_timeval now; 
        CCTime::gettimeofdayCocos2d(&now, NULL);
        long long t_time = (long long)now.tv_sec*1000 + (long long)now.tv_usec / 1000;
        return t_time;
    } 
    
    // 获取系统秒数
    static long millisecondNow_m()
    { 
        time_t tt;
        time(&tt);
        return (long)tt;
        
    } 
    // 获取系统时间
    static string millisecondNow_time(long _time)
    { 
        struct tm *t3;
        t3=localtime(&_time);
        char str_time[64];
        sprintf(str_time,"%4d-%02d-%02d %02d:%02d:%02d",t3->tm_year+1900,t3->tm_mon+1,t3->tm_mday,t3->tm_hour,t3->tm_min,t3->tm_sec);
        string result=str_time;
        return result;
        
    }
    // 时间格式转换系统时间
    static long time_millisecondNow(string _time)
    {
        long time = 0;
       
        size_t findex = _time.find('-');
        if (findex==4)
        {
            string nianStr = _time.substr(0, 4);
            string yueStr = _time.substr(5, 2);
            string riStr = _time.substr(8, 2);
            string shiStr = _time.substr(11, 2);
            string fenStr = _time.substr(14, 2);
            string miaoStr = _time.substr(17, 2);
            
            int year = CommonResource::getIntFromString(nianStr.c_str());
            int mon = CommonResource::getIntFromString(yueStr.c_str());
            int day = CommonResource::getIntFromString(riStr.c_str());
            int hour = CommonResource::getIntFromString(shiStr.c_str());
            int min = CommonResource::getIntFromString(fenStr.c_str());
            int sec = CommonResource::getIntFromString(miaoStr.c_str());

            
            /* 1..12 -> 11,12,1..10 */
            if (0 >= (int) (mon -= 2)) {
                mon += 12; /* Puts Feb last since it has leap day */
                year -= 1;
            }
            
           time = ((((unsigned long)(year/4 - year/100 + year/400 + 367*mon/12 + day) + year*365 - 719499)*24 + hour )*60 + min )*60 + sec - 28800;
        }
        return time;
        
    }
};
#endif
