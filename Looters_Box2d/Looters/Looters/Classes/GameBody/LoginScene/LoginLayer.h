/***************************************************************
 author:     wangning
 write time: 2012.10.20
 function:   登陆场景层
 ***************************************************************/

#ifndef Looters_LoginLayer_h
#define Looters_LoginLayer_h
#pragma once
#include "cocos2d.h"

class LoginLayer : public cocos2d::CCLayer
{
public:
    enum DetectProcess
	{
		null,
		detect_netinfo,       //检测网络
        detect_clientinfo,    //检测客户端版本
		detect_linkgameserver,//连接game服务器
		next,
	};
public:
    bool m_bIsLogin;
    bool m_bLoginBack;
    enum DetectProcess m_enDetectProcess;

private:
	int m_iLinkCountMax;
	int m_iCurrentLinkCount;
	int m_iLinkGameCountMax;
	int m_iLinkGameCountCurrent;
    
public:
    LoginLayer();
    ~LoginLayer();
    
    virtual bool init();
    
    CREATE_FUNC(LoginLayer);
    
    virtual void Update(float dt);
};

#endif
