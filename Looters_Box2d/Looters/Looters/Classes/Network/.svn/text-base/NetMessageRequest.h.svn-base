/******************************************************************************
*created:		2012/4/13
*created:		12:06
*author:		wangning
*purpose:		消息请求
********************************************************************************/
#pragma once 
#include "cocos2d.h"
#include "CentralLayer.h"
#include "AllMessageHead.h"
#include <iostream>
using namespace cocos2d;
using namespace std;

class NetMessageRequest
{
public:
	NetMessageRequest();
	~NetMessageRequest();

public:
	
	bool SendUserLoginRequest( string mailAddress, string language, string version, string machineNum );
    bool SendDownloadMapInforRequest(string mailAddress);
    bool SendDownloadBattleInforRequest(string mailAddress,string battleCouont);
    bool SendOperateSequenceRequest(string version,string mailAddress);
    bool SendProduceSoldiersRequest(string version,string mailAddress);
    bool SendBattleMatchingRequest(string mailAddress,string previousMailAddress,string str_md5,int battle_status); // battle_status 0战斗 1 复仇
    
    bool SendUploadBattleResultRequest(string mailAddress);
    bool SendBattleStartRequest(string attackMailAddress,string defenceMailAddress,string start_battle_time);
    
    bool SendRechargeRequest(string receipt);
    
    bool SendRevengeBattleRequest(string attackMailAddress,string defenceMailAddress);
    
    
    bool SendUploadBattleFlowRequest(string defenceMailAddress,string attackMailAddress, int maxSize, int maxIndex, int index, char *data);
    
    //下载文件验证码 请求的文件名  当前索引块
    bool SendIoFileRequest(int verifyCode,string requiredFile,int index);
    
    //取消战斗
    bool SendCancleBattleRequest(string mailAddress);
    
};