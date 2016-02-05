/******************************************************************************
*created:		2012/4/13
*created:		12:06
*author:		wangning
*purpose:		网络信息管理器
********************************************************************************/
#pragma once 
#include "cocos2d.h"
using namespace cocos2d;

#include "NetSocket.h"
#include "NetMessageResponse.h"
#include "NetMessageRequest.h"

enum NetSocket_Type
{
	Socket_Game = 0,
	Socket_File,
    Socket_Bank,
};

enum NetworkResult
{
	Link_Failure = 0, //连接失败
	Link_Success,     //连接成功
	Link_Timeout,     //连接超时
	Link_Frequent,    //频繁
};
enum ErroCode
{
	Code_SUCCESS = 0,               //成功
	Code_ERROR,                     //失败
	Code_SERVER_MAINTENACE,         //停服维护
	Code_Mail_address_exist,        //邮箱地址已经存在
	Code_game_data_migrated,        //游戏数据已经迁移，无法通过该设备连接
	Code_EXIST_NOT_FOR_USER,        //用户不存在
	Code_overfflow_friends_count,   //超出好友最大上限
	Code_EXIST_THIS_FRIENDS,        // 已经存在该好友
    Code_NO_result_for_request,     //查无结果
};

enum OperateType
{
	OperateType_UpgradeBuilding = 0,    //升级建筑
	OperateType_MobileBuilding,         //移动建筑
	OperateType_MadeSoldiers,           //造兵
	OperateType_UpgradeSoldiers,        //升级兵种
	OperateType_MadeMagic,              //造魔法
	OperateType_UpgradeMagic,           //升级魔法
	OperateType_BuyEmerald,             //购买绿宝石
	OperateType_BuyGold,                //购买金币
    OperateType_BuyPotions,             //购买药水
    OperateType_Build,                  //建造
    OperateType_HarvestPotions,         //收获药水
    OperateType_HarvestGold,            //收获金币
    OperateType_Demolition,             //拆除
    OperateType_Tombstone,              //清除墓碑
    OperateType_ProtectionTime,         //购买保护时间
    OperateType_CancelTheUpgrade,       //取消升级
    OperateType_CancelTheBuilding,      //取消建筑
    OperateType_jianSoldiers,           //减造兵
    
    AccelerateType_Building,                //建筑建造加速
	AccelerateType_MadeSoldiersAccelerated,     //造兵加速
	AccelerateType_MagicAccelerated,            //魔法加速
    AccelerateType_UpMadeSoldiersAccelerated,     //升级兵加速
	AccelerateType_UpMagicAccelerated,            //升级魔法加速
    AccelerateType_UPBuilding,                 //升级建筑建造
    
    OperateType_BuyR                            //购买资源
};
//enum AccelerateType
//{
//	AccelerateType_Building = 1,                //建筑建造
//	AccelerateType_MadeSoldiersAccelerated,     //造兵加速
//	AccelerateType_MagicAccelerated,            //魔法加速
//    AccelerateType_UpMadeSoldiersAccelerated,     //升级兵加速
//	AccelerateType_UpMagicAccelerated,            //升级魔法加速
//    AccelerateType_UPBuilding,                 //升级建筑建造
//};

class NetMessageManager 
{
public:
	NetMessageManager();
	~NetMessageManager();

	static NetMessageManager* GetMessageManager( void );
	static void ReleaseMessageManager( void );
    
	static void StateLinkLandSocket( void );
	static void StateLinkGameSocket( void );
	static void StopGameSocket( void );

	static void StateLinkFileSocket( void );
	static void StopFileSocket( void );
    
    static void StateLinkBankSocket( void );
	static void StopBankSocket( void );
	
	static string LandServerIP;//登陆服务器IP
	static int LandServerPort; //登陆服务器端口

	static string GameServerIP;//游戏服务器IP
	static int GameServerPort; //游戏服务器端口

	static string FileServerIP;//文件服务器IP
	static int FileServerPort; //文件服务器端口
    
    static string BankServerIP;//支付服务器IP
    static int BankServerPort; //支付服务器端口

	bool Init( void );
	void NetMessageLogic( float dt );

	NetMessageReponse *m_pMessageResponse;
	NetMessageRequest *m_pMessageRequest;

	std::map<string,int> m_mapMessageList;
	std::map<int,string> m_mapReflexMessage;

	NetSocket *m_pSocketGame;   //game服务器
	bool m_bGameSocketLinked;   //已连接
	bool m_bGameSocketLinking;  //连接中
	bool m_bGameSocketStoping;  //关闭中

	NetSocket *m_pSocketFile;   //资源服务器
	bool m_bFileSocketLinked;   //已连接
	bool m_bFileSocketLinding;  //连接中
	bool m_bFileSocketStoping;  //关闭中
    
    NetSocket *m_pSocketBank;    //支付服务器
    bool m_bBankSocketLinked;   //已连接
    bool m_bBankSocketLinding;  //连接中
    bool m_bBankSocketStoping;  //关闭中

private:
	//注册消息
	void RegisterAllMessage( void );
	void RegisterMessage( int ID, string strRegisterBodyStr );
	
};

//协议ID定义

// 登陆
#define API_UserLoginRequest   1001
#define API_UserLoginResponse 41001

// 下发客户端地图信息
#define API_DownloadMapInforRequest 1003
#define API_DownloadMapInforResponse 41003

// 下发战斗信息列表
#define API_DownloadBattleInforRequest 1004
#define API_DownloadBattleInforResponse 41004

// 网络心跳检测
#define API_HeartBeatRequest 2802
#define API_HeartBeatResponse 42802

//客户端定时上传流水账
#define API_OperateSequenceRequest 200
#define API_OperateSequenceResponse 40200


//招兵
#define API_ProduceSoldiersRequest 201
#define API_ProduceSoldiersResponse 40201

//战斗匹配
#define API_BattleMatchingRequest 301
#define API_BattleMatchingResponse 40301

//上传战斗结果
#define API_UploadBattleResultRequest 304
#define API_UploadBattleResultResponse 40304

//开始战斗
#define API_BattleStartRequest 302
#define API_BattleStartResponse 40302

//充值
#define API_RechargeRequest 1006
#define API_RechargeResponse 41006

//复仇
#define API_RevengeBattleRequest 308
#define API_RevengeBattleResponse 40308

//上传战斗过程
#define API_UploadBattleFlowRequest 305
#define API_UploadBattleFlowResponse 40305

//下载战斗过程
#define API_IoFileRequest 306
#define API_IoFileResponse 40306

//取消战斗
#define API_CancleBattleRequest 307
#define API_CancleBattleResponse 40307


/*
 协议ID 规范
 1>	建设升级模块
 以流水账的方式 间隔发送给服务器
 request 200~300 response 40200~40300
 
 2>	战斗模块
 战前信息下发,战中验证,战后奖励
 request 301~400 response 40301~40400
 
 3>	好友模块
 添加，删除，获取好友列表
 request 401~500 response 40401~40500
 
 4>	排行榜
 个人排行，工会排行，排行榜奖励
 request 501~600 response 40501~40600
 
 5>	成就
 request 501~600 response 40501~40600
 
 6>	工会
 会员管理
 request 601~700 response 40601~40700
 
 7>	pve关卡
 和战斗类似
 request 701~800 response 40701~40800
 
 8>	战斗报告列表和回放
 被攻击列表下发，战斗回放下发，存储放兵位置,和被攻击者地图信息
 request 801~900 response 40801~40900
 
 9>	推送被攻击信息
 登陆成功时推送被攻击信息
 request 901~1000 response 40901~41000
 
 10>	登录和心跳
 request 1001~1100 response 41001~41100
 */