/***************************************************************
 author:    wangning
 write time: 2012.11.22
 function: 建筑基础类
 ***************************************************************/
#pragma once
#include "cocos2d.h"
#include <math.h>
#include <iostream>
#include "Unit.h"
#include "TipNode.h"
using namespace std;
using namespace cocos2d;

//生产状态
enum Production_State {
    Production_State_Null = 0,          //空
    Production_State_Add = 1,           //添加
    Production_State_Full = 2,          //满
};


class BuildingBase: public Unit
{
public:

public:
	BuildingBase();
	~BuildingBase();

	static BuildingBase* BuildWithData( int unitID);
    
	bool init( int unitID);
    
	virtual const CCSize& getContentSize( void ); //建筑主体精灵图尺寸

	int GetLine( void );    //建筑占地行数
	int GetRow( void );     //建筑占地列数

public:
    
	void IsShowSubstrateFace( bool bIs ); //是否显示底座面
    
	void SetRedSubstrateFace( void );   //设置底面红色
	void SetGreenSubstrateFace( void ); //设置底面绿色
    
    void IsShowSubstrateArrow( bool bIs ); //是否显示箭头
    void IsShowAttackArea( bool bIs );     //是否显示攻击范围
    
    void IsShowBuildName( bool bIs ); //是否显示建筑名称

    void IsShowDefenceCharacters( bool bIs);//是否隐藏塔上的人物


public:
    //绘制主题建筑
    void drawBuild(string _str);
    
private:
    // 绘制建筑底座的四个箭头
	void drawArrow( void );
    // 绘制建筑攻击范围
    void drawAttackArea( void );
    
public:
    // 绘制建筑的名称
    void drawNameLabel( CCSprite* _parentNode,const char* _name);
    // 绘制建筑底的对错号
	void drawSymbol(CCObject* target, SEL_MenuHandler selector1, SEL_MenuHandler selector2 );
    //消除对错号
    void removeSymbol();
    
    
    void replaceSprite_(const char *pszFileName); //替换sprite_
private:
	CCSprite *m_pSpriteBuilding;            //建造中精灵图
    
    CCSprite *m_pSpriteBuildArrow[4];       //建造移动箭头图
    
    CCMenu   *menu ;                        //按钮
    
    TipNode  *tipNode;                      //事件提示
    
public:
    CCLabelTTF*  nameLabel;                 //等级名称显示
    
public:
    //招兵队列_循环体
    struct PeopleSoldiers
    {
    public:
        int     tyep;           //兵的类别
        int     num;            //兵的数量
        int     uploadNum;      //已经上传的数量
        int     MAXTime;        //招兵最大时间
        long    time;           //招兵开始时间
        long    S_time;         //按下时间
        int     uuid;           //兵营的uuid
        int     index;          //队列序列
    };
    
    vector<PeopleSoldiers*>* m_peopleSoldiers;
    
    vector<PeopleSoldiers*>* m_UpPeopleSoldiers;
    
    vector<PeopleSoldiers*>* m_jianPeopleSoldiers;
    
public:
    //魔法队列
    struct magicBuild
    {
    public:
        int     tyep;           //魔法的类别
        int     num;            //魔法的数量
        int     MAXTime;        //魔法最大时间
        long    time;           //魔法开始时间
        int     index;          //队列序列
    };
    //    
    vector<magicBuild*>* m_magicBuild;
    
    
public:
	long            m_uBuildTime;           //开建始筑时间 //秒
	unsigned int    m_iBuildCDTime;         //建筑的CD时间 //秒
    
    long            buildEventTime;         //建筑的事件事件
    int             buildEventCDTime;       //建筑的事件CD时间
    
    long            buildxiaoguoEventTime;         //建筑的事件效果事件

    
    long            removeEventTime;         //建筑的删除事件
    int             removeEventCDTime;       //建筑的删除CD时间
    
    int             resourcesMinNum;        //资源最小可收获数
    int             resourcesMaxNum;        //资源最da可收获数
    int             resourcesCDNum;         //资源获取速度

    int             resourcesGoldNum;       //资源数(钱)
    int             resourcesPotionsNum;    //资源数(药水)
    int             soldiersNum;
    
    bool            isMroS;                 //是否是魔法
    int             UpLeveTyep;             //升级类别
    long            UpLeveTime;             //升级时间
    int             UPLeveCDTime;           //升级cd时间
    
    int             magicTyep;              
    int             isCancelMagic;          //是取消魔法还是建筑魔法
    
    int             isBusy;                 //是否忙碌
    int             busyUUID;               //忙碌对象
    
    int             productionState;        //生产状态
    
    float           allProductionTime;      //生产时间总和
    
    bool            isSafety;               //安全锁
    
    int             duileiNum;              //队列人口数
    int             duileiMAXNum;              //队列人口数
    bool            isManNum;               //是否满员
    
    
    ccColor3B       ccl;
    
    bool            isAddsu;                //是否加速
    
    long            savsTime;               //服务器下发时间
    
public:
    //建筑的数据更新
    void UpdataBuilding(float dt);     
    //计数时分秒
    std::string calculation_d_h_m_s(long _time); 
    
    
public:
    void setData();
    
    // 塔的升级
    void unit_doupgrade(int _m_u32ID);
    // 增加资源
    void addResources();
    // 初始化建筑数值
    void initBuildingNumerical();
    //兵营招兵
    void addSoldiers(int _tyep);
    //减少招兵
    void jianSoldiers(int _tyep);
    //兵营招兵
    void addInfoSoldiers(int _tyep,string _endTime ,int _num,int _index,int _leve);
    //兵营上传的数据
    void setUploadSoldiersArr();
    
    //魔法建造
    void addMagicBuild(int _tyep);
    
    //升级兵种魔法
    void upLeveMagicSoldiers(int _tyep, bool _isMroS,int _time);
    
    void upLeveComplete(int _tyep);
    
    //更新建筑生产状态
    void updataProductionState();
    
    //立即完成
    void ImmediatelyComplete();
    
    void BuildingComplete();
    
    //删除数组数据
    void CleanData( void );


public: // 兵营 农民屋处理
	typedef vector<Unit*> army_loop_t;
	army_loop_t m_army;

	Unit* m_pWorker;
	int GetNowHousingSpace();
    
    
public:
    //动画表现
    bool        isBiaoxian;
    
    float       biaoTime;
    
    
    
};












