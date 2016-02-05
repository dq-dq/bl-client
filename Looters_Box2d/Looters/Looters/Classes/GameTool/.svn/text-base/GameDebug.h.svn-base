/***************************************************************
 author:     wangning
 write time: 2012.11.1
 function:   游戏错误打印 服务器返回错误码处理 基础数据信息打印等
 ***************************************************************/
#ifndef Looters_GameDebug_h
#define Looters_GameDebug_h
#pragma once
#include <iostream>
using namespace std;

#define GAMEDEBUG 0
#define NotNetworking     0

enum ErroCode_
{
    SUCCESS = 0,	//成功
    ERROR,	//失败
    SERVER_MAINTENACE,	//停服维护
    Mail_address_exist,	//邮箱地址已经存在
    game_data_migrated,	//游戏数据已经迁移，无法通过该设备连接。
    EXIST_NOT_FOR_USER,	//该用户不存在请重新注册
    overfflow_friends_count,	//超出好友最大数量限制
    EXIST_THIS_FRIENDS,	//已经存在改好友
    NO_result_for_request,	//查无结果
    NO_ENOUGH_GOLDEN,	//没有充足的金币
    NO_ENOUGH_ELIXIR,	//没有充足的药水
    BUILDING_UPGRADING,	//建筑下在升级
    NO_HAVE_FREE_WORKER,//没有空闲的农民
    NO_ENOUGH_LEVE_OF_HALL,	//大厅等级不够
    NO_ENOUGH_LEVEL_OF_LIBORATORY,	//实验室等级不够
    NO_MATCHING_USER,	//没有匹配到玩家
    USER_IS_ONLINE_NOT_REVENGE,	//玩家在线无法复仇
    USER_IS_IN_SHIELD_TIME,	//用户正在保护期
    USER_NAME_OR_PASSWORD_NO_RIGHT,	//用户名或者密码不对
    NO_ENOUGH_GEM_CONSUME,	//没有足够的绿宝石可
    NO_ENOUGH_HOUSE_SPACE,	//营地没有足够人口位置
    NO_ENOUGH_GEM_CONSUME_1,	//没有足够的绿宝石可消费
    NO_ENOUGH_HOUSE_SPACE_1,	//没有足够的人口位置
    NO_ENOUGH_PELL_Space_OF_FACTORY,	//魔法工厂没有足够的位置来制造魔法
    BUY_RESOURCE_NOT_FOUND,	//未发现需要购买的资源
    BUILDING_NOT_FOUND,	//未发现该建筑
    BUILDING_TYPE_NOT_FOUND,	//未发现该建筑类型
    BUILDING_UNFINISHED,	//建筑建造/升级未完成
    BUILDING_FULL_LEVEL,	//建筑已经满级
    CHARACTER_NOT_FOUND,	//数据库中未发现兵种
    SPELL_NOT_FOUND,	//未发现该技能
    CAPACITY_FULL,	//容量已满
    DENY_LOGIN,	//拒绝登陆
    IS_BATTLING,	//玩家正在被别人攻击
    NOT_FIND_REPLY_FILE,	//回放文件不存在
    USER_SPELL_NOT_FOUND,	//未发现该用户技能
    USER_CHARACTER_NOT_FOUND,	//未发现用户士兵对象
    ALREADY_COMPLETE,	//该建筑/士兵/魔法已经完成, 加速失败
    USER_NOT_FOUND,	//未发现该用户
    OPERATE_TYPE_ERROR,	//操作类型错误
    ACCELERATE_TYPE_ERROR,	//加速类型错误
    PRODUCE_CHARACTER_FINISHED,	//造兵已经完成
    BARRACK_NOT_FOUND,	//军营不存在
    COST_TYPE_ERROR,	//消费类型错误
    BANK_NOT_FOUND,	//未发现用户银行数据
    BUILDING_EXISTS,	//建筑已经存在
    ALREADY_MAX_LEVEL,	//已经是最大等级
    BARRACK_PRODUCE_QUEUE_FULL,	//兵营建造队列已满
    NO_ENOUGH_SOLDIER,	//没有足够的士兵
    BUILDING_TYPE_ERROR,	//建筑类型错误
    COLLECTOR_NOT_FOUND,	//没有发现收集器
    USER_IS_EXIST,	//该用户已经存在
};

class GameDebug {
public:
    static void Log__(string info)
    {
        if (GAMEDEBUG) {
            std::cout << info<<"\n";
        }
    }
    
    static void ErroCode__(int erroCode,string info)
    {
        std::string title = "提示";
        std::string msg = "";
        
        switch (erroCode) {
            case ERROR:
                msg.append("获取数据").append("失败!");
                break;
            case SERVER_MAINTENACE:
                msg.append("停服维护").append("");
                break;
            case Mail_address_exist:
                msg.append("邮箱地址已经存在").append("");
                break;
            case game_data_migrated:
                msg.append("游戏数据已经迁移，无法通过该设备连接").append("");
                break;
            case EXIST_NOT_FOR_USER:
                msg.append("该用户不存在请重新注册").append("");
                break;
            case overfflow_friends_count:
                msg.append("超出好友最大数量限制").append("");
                break;
            case EXIST_THIS_FRIENDS:
                msg.append("已经存在改好友").append("");
                break;
            case NO_result_for_request:
                msg.append("查无结果").append("");
                break;
            case NO_ENOUGH_GOLDEN:
                msg.append("没有充足的金币").append("");
                break;
            case NO_ENOUGH_ELIXIR:
                msg.append("没有充足的粮食").append("");
                break;
            case BUILDING_UPGRADING:
                msg.append("建筑下在升级").append("");
                break;
            case NO_HAVE_FREE_WORKER:
                msg.append("没有空闲的农民").append("");
                break;
            case NO_ENOUGH_LEVE_OF_HALL:
                msg.append("大厅等级不够").append("");
                break;
            case NO_ENOUGH_LEVEL_OF_LIBORATORY:
                msg.append("实验室等级不够").append("");
                break;
            case NO_MATCHING_USER:
                msg.append("没有匹配到玩家").append("");
                break;
            case USER_IS_ONLINE_NOT_REVENGE:
                msg.append("玩家在线无法复仇").append("");
                break;
            case USER_IS_IN_SHIELD_TIME:
                msg.append("用户正在保护期").append("");
                break;
            case USER_NAME_OR_PASSWORD_NO_RIGHT:
                msg.append("用户名或者密码不对").append("");
                break;
            case NO_ENOUGH_GEM_CONSUME:
                msg.append("没有足够的绿宝石可").append("");
                break;
            case NO_ENOUGH_HOUSE_SPACE:
                msg.append("营地没有足够人口位置").append("");
                break;
            case NO_ENOUGH_GEM_CONSUME_1:
                msg.append("没有足够的绿宝石可消费").append("");
                break;
            case NO_ENOUGH_HOUSE_SPACE_1:
                msg.append("没有足够的人口位置").append("");
                break;
            case NO_ENOUGH_PELL_Space_OF_FACTORY:
                msg.append("魔法工厂没有足够的位置来制造魔法").append("");
                break;
            case BUY_RESOURCE_NOT_FOUND:
                msg.append("未发现需要购买的资源").append("");
                break;
            case BUILDING_NOT_FOUND:
                msg.append("未发现该建筑").append("");
                break;
            case BUILDING_TYPE_NOT_FOUND:
                msg.append("未发现该建筑类型").append("");
                break;
            case BUILDING_UNFINISHED:
                msg.append("建筑建造/升级未完成").append("");
                break;
            case BUILDING_FULL_LEVEL:
                msg.append("建筑已经满级").append("");
                break;
            case CHARACTER_NOT_FOUND:
                msg.append("数据库中未发现兵种").append("");
                break;
            case SPELL_NOT_FOUND:
                msg.append("未发现该技能").append("");
                break;
            case CAPACITY_FULL:
                msg.append("容量已满").append("");
                break;
            case DENY_LOGIN:
                msg.append("拒绝登陆").append("");
                break;
            case IS_BATTLING:
                msg.append("玩家正在被别人攻击").append("");
                break;
            case NOT_FIND_REPLY_FILE:
                msg.append("回放文件不存在").append("");
                break;
            case USER_SPELL_NOT_FOUND:
                msg.append("未发现该用户技能").append("");
                break;
            case USER_CHARACTER_NOT_FOUND:
                msg.append("未发现用户士兵对象").append("");
                break;
            case ALREADY_COMPLETE:
                msg.append("该建筑/士兵/魔法已经完成, 加速失败").append("");
                break;
            case USER_NOT_FOUND:
                msg.append("未发现该用户").append("");
                break;
            case OPERATE_TYPE_ERROR:
                msg.append("操作类型错误").append("");
                break;
            case ACCELERATE_TYPE_ERROR:
                msg.append("加速类型错误").append("");
                break;
            case PRODUCE_CHARACTER_FINISHED:
                msg.append("造兵已经完成").append("");
                break;
            case BARRACK_NOT_FOUND:
                msg.append("军营不存在").append("");
                break;
            case COST_TYPE_ERROR:
                msg.append("消费类型错误").append("");
                break;
            case BANK_NOT_FOUND:
                msg.append("未发现用户银行数据").append("");
                break;
            case BUILDING_EXISTS:
                msg.append("建筑已经存在").append("");
                break;
            case ALREADY_MAX_LEVEL:
                msg.append("已经是最大等级").append("");
                break;
            case BARRACK_PRODUCE_QUEUE_FULL:
                msg.append("兵营建造队列已满").append("");
                break;
            case NO_ENOUGH_SOLDIER:
                msg.append("没有足够的士兵").append("");
                break;
            case BUILDING_TYPE_ERROR:
                msg.append("建筑类型错误").append("");
                break;
            case COLLECTOR_NOT_FOUND:
                msg.append("没有发现收集器").append("");
                break;
            case USER_IS_EXIST:
                msg.append("该用户已经存在").append("");
                break;
            default:
                break;
        }

        CCMessageBox(msg.c_str(), title.c_str());
    }
    
    static void MessageBox__(int erroCode,string info)
    {
        std::string title = "提示";
        std::string msg = "";
        msg.append(info);
        CCMessageBox(msg.c_str(), title.c_str());
    }
};

#define Log__(P) GameDebug::Log__(P)
#define ErroCode__(P,M) GameDebug::ErroCode__(P,M)
#define MessageBox__(P,M) GameDebug::MessageBox__(P,M)

#endif
