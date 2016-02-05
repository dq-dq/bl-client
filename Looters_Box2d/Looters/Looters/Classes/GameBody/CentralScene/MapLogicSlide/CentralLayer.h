/***************************************************************
 author:     wangning
 write time: 2012.10.20
 function:   游戏主场景层
 ***************************************************************/

#ifndef Looters_CentralLayer_h
#define Looters_CentralLayer_h
#pragma once
#include "cocos2d.h"
#include "GameData.h"
#include "BuildingManager.h"
#include "GameControl.h"
#include "GLES_Render.h"
#include "LAnimManage.h"
#include "Until.h"
#include "GameDebug.h"
#include "Obstacle.h"
#include "LParticleUnit.h"
#include "some_tool.h"
using namespace std;
USING_NS_CC;

#define BUILD_UU_ID 200 
#define PEOPLE_UU_ID 1000

#define BUILD_ZOrder_MAX     10000


struct ShortestPathStep;
typedef std::list<ShortestPathStep*> ai_step_t;

class CentralLayer : public CCLayer
{
public:
	//操控状态
	enum MAPHANDLESTATE
	{
		STATE_NULL = 0, //无操控状态
		STATE_ZOOM,     //缩放操控状态
		STATE_MOVE,     //移动操控状态
		STATE_CLICK,    //点击操控状态
		STATE_DRAG,     //拖动操控状态
	};
	
	//建筑操作模式
	enum OPERATINGMODE
	{
		MODE_NULL = 0, //无操控状态
		MODE_DRAG,     //拖动操控状态
	};
	
	//资源加载流程
	enum CentralLoadProcess
	{
		null,
		DownloadMapInfor,   // 下发地图信息
		ServerUpdate_DownloadMapInfor,       // 检测服务器返回建筑数据是否完成
        DownloadBattleInfor,// 下发战斗信息列表
        ServerUpdate_DownloadBattleInfor,    // 检测服务器返回建筑数据是否完成
        DownloadFileInfor,  // 战斗列表文件
        ServerUpdate_DownloadFileInfor,      // 检测服务器返回建筑数据是否完成
        NewMapBuild,        // 生成地图上的建筑
		finish,             // 资源加载完成
	};
	
	enum BATTLE_STATE {
		BATTLE_NONE = -1,   
		BATTLE_READY = 0,  // 战斗前准备
		BATTLE_IN = 1,     // 战斗中
		BATTLE_END = 2,    // 战斗结束
	};
		
public:
	CentralLayer();

	~CentralLayer();
	
	virtual bool init();
	
	CREATE_FUNC(CentralLayer);
	
	virtual void Update(float dt);// 主场景定时更新函数
	void step( float dt);//循环所有unit逻辑
	void UpdateBuildintStatus( float dt );// 建筑状态更新函数
    void battle_update( float dt );
	
public: 
	//游戏主场景触摸操作
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	
	//地图触摸操作
	virtual void mapTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void mapTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void mapTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	
	//建筑触控操作
	virtual void buildTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void buildTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void buildTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	
	//人物触控操作
	virtual void peopleTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void peopleTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void peopleTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	
public: //主场景资源加载
	enum CentralLoadProcess  m_enLoadProcess;//加载流程控制
	void StateLoad(); // 数据初始化
	void UpdateLoadResAndData( float dt ); // 获取服务器数据并初始化

	
public: //主场景分层处理
	CCSprite* m_nodeArena;  //游戏区域层
			CCTMXTiledMap *m_tmxMap;//地图对象层
				CCNode* m_nodeDraws; // 地图地表网格层
				//CCSpriteBatchNode* m_batchBuildBottom; // 地图底座批节点
				CCNode* m_batchBuildBottom; // 地图底座批节点
	
	
public: // 地图触摸操作相关
	//gesture(地图捏合操作)
	float	initialDistance; //地图缩放两点间初始距离
	float	finalDistance;   //地图缩放两点间最终距离
	
	CCPoint m_pointCurrentMap; //当前地图位置
	
	float m_fCurrentScale;  //地图的当前缩放比
	float m_fScaleMax;      //地图的最大缩放比
	float m_fScaleMin;      //地图的最小缩放比
	
	//视图焦点
	CCPoint m_pointFocus;//地图焦点
	void SetFocus( void );
	void SetMapLayerPos( CCPoint point );
	void SetMapLayerScale( float fScale );
	
public: //地图数据信息/地图逻辑信息/地图信息录入
// 地图数据信息********************************began
	//触摸屏幕格子
	struct TouchRectInfo
	{
		CCPoint mapIndex;
	};
		
	CCPoint touchInGrid(CCPoint mapIndex,CCPoint pointMap); // 有中间格子和触摸点得到真正点中地图格子的索引
	CCPoint positionForIsoAt(const CCPoint& pos) const; // 得到格子索引对应的坐标
	CCPoint getMapIndexByTouchPoint(CCPoint touchPoint); // 有触摸屏幕的点得到地图格子的索引
// 地图数据信息********************************end
	
// 地图逻辑信息********************************began
	struct MapGridLogicInfo
	{
		MapGridLogicInfo()
			: uuid(0), pBuilding(0)
			, mapIndex(0, 0), bIsBiulded(false)
		{

		}
		unsigned int uuid;          //建筑唯一ID
		void *pBuilding;            //建筑指针
		CCPoint mapIndex;           //地图格子索引
		bool bIsBiulded;            //是否被建筑占据
	};
	map<unsigned int,MapGridLogicInfo*>* m_mapMapGridLogicInfo;//地图建筑逻辑信息
	void AddMapGridLogicInfo(unsigned int index,MapGridLogicInfo* info);
	bool GetMapGridLogicInfo(unsigned int index,MapGridLogicInfo* info);
	void UpdataMapGridLogicInfo( unsigned int index, MapGridLogicInfo* info );
	
	//改变地图格子的建筑状态
	void MarkGridBuildInfo(CCPoint lBIndex,int row,unsigned int uuid,void *building);
	//删除地图格子的建筑状态
	void RemoveGridBuildInfo(CCPoint lBIndex,int row,unsigned int uuid,void *building);
	//判断是否可放下建筑
	bool isCanPutDownBuild(CCPoint lBIndex,int row,unsigned int uuid,void *building);
	
// 地图逻辑信息********************************end
	BuildingBase* SelectBuildingFromSubstrate( CCPoint point );//通过建筑基座选择建筑
	
	bool isClickBuilding( CCPoint point ,BuildingBase* build,CCPoint _buildNewMapIndex); //是否点击建筑
	
// 地图信息录入********************************began
	
	//加载地图信息
	int m_iLandLevel;
    void CreateMap();
	void LoadMapInfo( int LandLevel );

	void LoadBattleReplayMap();

	
// 地图信息录入********************************end
	
public:
	// 判定地图建筑信息是否加载完毕
	bool downloadMap;
    bool downloadbattlelist;
    bool downloadFileList;
    bool downloadAllFile;
	
	int link_downloadMapCount;
	int link_currentdownloadMapCount;
    
    int link_downloadbattlelistCount;
    int link_currentdownloadbattlelistCount;
    
    int link_downloadFileCount;
    int link_currentdownloadFileCount;
    
public: // 建筑操作
	BuildingBase* m_building;
	enum MAPHANDLESTATE m_enHandleState;
	enum OPERATINGMODE m_BuildOperatingMode;
	CCPoint startMovePos;     // 建筑移动的初始位置
	CCPoint buildNewMapIndex; // 建筑新的地图格子索引

public: // 战斗相关 ai 技能等
	CCArray* unit_list_;
	void _remove_ghosts();
	void update_unit_ai(Unit* u,float dt);
	
	// ai部分
	void stand_ai(Unit* u); // 站立ai
	void move_ai(Unit* u);  // 移动ai
	void resource_worker_ai(Unit* u);
	void patrol_ai(Unit* u);// 巡逻ai
    void stand_cannon_ai(Unit* u); // 炮在自己家ai
	
	Unit* findAttackTarget(Unit* u); //寻找目标
	void startmoveto(Unit* u,Unit* t);//开始项目标移动
	void checkAttack(Unit* u);
    
	// 动画回调函数
	void callBackAnim_Attack(CCNode* sender,void* u);
    void callBackAnim_Busy(CCNode* sender,void* u);



	void callBackAnim_Dead(CCNode* sender,void* u);
    void callBackAnim_Celebrate(CCNode* sender,void* u);
    void callBackAnim_Steer(CCNode* sender,void* u);

public: // 技能用
     bool checkUnitInArea(int _range,Unit* src,Unit *dest);
    
public: // 寻敌
	// 寻找优先攻击且最近的目标
	Unit* find_love_near_target(Unit* src);

	// 地形格上是相同的类型, 返回此unit, 否则返回 NULL
	Unit* on_tiltle_unit_type( CCPoint const& index, unit_type type);
	
    Unit* enumAreaUnits(Unit *src); // 寻找防御炮塔范围内且最近的目标
	Unit* find_army_build( Unit* src );
	// 士兵到营火, 普通npc
public:


	Unit* enumCannonAreaUnits(Unit* src);//寻找炮塔范围内且最近的目标
	
public: // 支付
    void CentralRechargeRequest(string _str);
    int m_iLinkBankCountMax;
	int m_iLinkBankCountCurrent;
    
public:
    int m_iLinkFileCountMax;
	int m_iLinkFileCountCurrent;
    
    int requestFileIndex; // 请求战斗列表文件索引
    
public: // 建筑相关
    BuildingBase* m_BuyBuilding;
    
    int  build_uuId;
    
    float  uploadSoldiersTime;
    bool isUPSoldiers;
    float  jianloadSoldiersTime;
    bool isJianSoldiers;
    
    bool isSpeedUp;
    bool isjianSoldiers;
    
    BuildingBase*  AddBuilding(int unitID,CCPoint isoAt,int uuID ,bool isBuy); // 添加建筑到地图上base
    
    BuildingBase*  AddReadBuilding(int buildID,CCPoint isoAt,int uu_id); // 读取服务器或本地数据添加建筑
    BuildingBase*  AddContinuousWall(int unitID,CCPoint pos,int type); // 添加连续摆放建筑  墙和地雷
    void ReplaceWallToBase01(BuildingBase* build);
    void buyBuilding(int unitID); // 添加从商店买建筑
    void fangxiajianzhu();          //放下建筑
    
    void menuCallbackOK(CCObject* pSender);
    void menuCallbackCancel(CCObject* pSender);
    
    void uploadRecruiting();
    void jianloadRecruiting();
    //资源的存储
    void ResourceStorage();
    int ResourceMAXP();
    int ResourceMAXG();
    

    //更新可造的兵类别
    void UpBuildableSoldiers();
    //更新可造的mofa类别
    void UpBuildableMagic();
    //更新可造的物的等级
    void UpBuildableLevel();
    //当前最大等级的兵营等级
    int MAXSoldiersLevel();
    //当前最大等级的魔法建筑等级
    int MAXmagicLevel();
    //当前主基地等级
    int MAXTownhall();
    //当前最大人口数
    int MAXpeopleNum();
    int AllpeopleNum();
    
    //调整镜头
    void AdjustmentLens();
    
    int gemConversion(int _time);
    
    BuildingBase* NoBusy();
    void FreeWorkers(int _uuid);
    
    
public: // 墙的摆放
    // 墙的类型
    enum BuildWall_type
    {
        BuildWall_type_0 = 0, //无方向
        BuildWall_type_1 = 1, //左上方
        BuildWall_type_2 = 2, //右上方
        BuildWall_type_3 = 3, //左上方＋右上方
    };
    // 墙的摆放方向
    enum PlaceDirection_type
    {
        PlaceDirection_type_NONE = -1,
        PlaceDirection_type_LeftTop = 0,
        PlaceDirection_type_RightTop = 1,
        PlaceDirection_type_RightBottom = 2,
        PlaceDirection_type_LeftBottom = 3,
    };
    
    enum PlaceState
    {
        PlaceState_First = 0,
        PlaceState_Next = 1,
    };
    
    PlaceState m_PlaceState;
    int placeDirection;
    CCPoint PlaceNextIndex;
    
    BuildingBase* BuildWall_first(int unitID,CCPoint mapindex,bool isbuy); // 摆放第一个
    BuildingBase* BuildWall_next(int dir,int unitID, bool isbuy);
    
    int getPlaceDirection(CCPoint index); //第一次摆放后根据格子索引得连续摆放的方向
    void getPlaceNextIndex(int direction); // 根据方向得下一个放置的地图格子索引
    void ResetPlaceDirection_type(CCPoint index); // 放置每一个新的都要对相邻的进行重置
    
    void ResetPlaceAll(CCPoint mapindex);
    
public: // 流水账相关
	
	//操作列表类别_循环体
	struct CentralOperate
	{
		int     type;                       //操作类型
		long    operation_time;                       //操作时间(所有操作的开始)（金矿，药水的收集时间）
		int     uuid;                       //建筑唯一ID
		int     building_id;                //建筑ID
		long    end_time;                   //升级结束时间（升级,造兵结束时间，）
		int     move_to_map_index_x;        //移动到第几个格子（移动）x轴
		int     character_id;               //士兵id/魔法ID（升级兵种,魔法,造兵用）
		int     produce_count;              //造兵数量/已经造的数量/金矿 药水的数量）
		long    remaining_time;             //剩余时间
		int     move_to_map_index_y;        //移动到第几个格子（移动）y轴
		int     build_upgrade_status;       //建筑升级的状态0开始升级 1升级完成
        int     treasure_id;                //资源id
	};
	
	struct CentralAccelerate
	{
		int tyep;                   //加速类型
		int building_id;            //加速id（建筑物
		int uuid;                   //建筑唯一ID
		int gem_count;              //支出绿宝石数量
		long remain_time;           //剩余时间
	};

	float       accountIntervalTime;
	bool        isAccount;
	vector<CentralOperate*>* m_Account;
	vector<CentralAccelerate*>* m_Accelerated;
	
	void uploadAccount();
	
	
	void buildingAccount(BuildingBase* build,int _tyep); 
    
    void buildingAccount2(int _tyep, int _num, bool isR);
	
    int Accelerated_id;
    int Accelerated_uuid;
    int Accelerated_remain_time;
    int Accelerated_gem_count;
    int Accelerated_upid;
	void buildingAccelerated(int _tyep); 
	
	

public: // 人物物相关
	int people_uuId;
	Unit* AddPeople(int unitID, CCPoint const& pos, Unit* parentUnit);
    
    Unit* AddNpcPeople(int unitID, CCPoint const& pos);
	
	//营火的士兵匹配规则
	BuildingBase* matchingCampfire(int rolecount, b2Vec2 const& pos);
    
public: // 障碍物相关
    Obstacle* AddObstacle(int unitID, CCPoint mapIndex);

public: // 战斗相关
	BATTLE_STATE  battle_state_;
	void initBattleData();
	void cleanBattle();
	void battleStartRequest();
    
	enum InvalidCell_type
	{
		InvalidCell_type_0 = 0, // 无边
		InvalidCell_type_1 = 1, // only 左上边
		InvalidCell_type_2 = 2, // only 右上边
		InvalidCell_type_3 = 3, // only 右下边
		InvalidCell_type_4 = 4, // only 左下边
		InvalidCell_type_5 = 5, // 左上边 + 右上边
		InvalidCell_type_6 = 6, // 右上边 + 右下边
		InvalidCell_type_7 = 7, // 右下边 + 左下边
		InvalidCell_type_8 = 8, // 左下边 + 左上边
	};

	struct InvalidCell
	{
		int type;
		bool hide;
	};
	map<unsigned int,InvalidCell*>* m_InvalidCell;
	
	// 战斗场景无效位置（不可放兵)
	void AddInvalidCellInfo(unsigned int index,InvalidCell* info);
	bool GetInvalidCellInfo(unsigned int index,InvalidCell* info);

	CCArray* invalidSpArr; // 无效区域sprite存放
	int getInvalidCellType(CCPoint index);
	void getInvalidLocation();
	void showInvalidLocation();
	void hideInvalidLocation();

    
    
    //战斗过程中统计
    int battle_loadbuildcount; // 服务器下发建筑数量
    int battle_curbuildcount;  // 销毁建筑数量计算
    int battle_loadrolecount;  // 服务器下发角色数量
    int battle_currolecount;   // 战斗中使用兵数量计算
    
    int battle_star_count;   // 战斗获取的星星数量
    
    int battle_golden_count; // 战斗打掉金币数量
    int battle_elixir_count; // 战斗打掉药水数量
    
    int battle_realgolden_count; // 战斗实际获取金币数量
    int battle_realelixir_count; // 战斗实际获取药水数量
    
    void Add_Star_count(int count);
    
    int battle_addpeoplecount;

public:// 粒子相关
    CCArray* particle_list_;
    LParticleUnit* AddParticleEmitter(string file_,CCPoint pos,float scale,CCNode* node);
	
	std::vector<CCNode*> m_testPoint;
	void InitTestPoint();
	void ClearTestPoint();

public://特效相关
    CCSprite*   sprTeX;


public:
	CentralData::BattleInfor battleInfo;

	// 以屏幕为中心查找空地
	// line为一边占地格的数量
	iVec2 FindEmptyTitle( int line );

private:
	bool HasEmpty( iVec2 const& leftTop, int line );



	// 建筑工人
private:
	Unit* GetFreeWorker( Unit* pFrom);

	void MoveWorkerToNewPos( Unit * pRole, Unit* pTarget);

public:
	void SendAWorker(BuildingBase* pHome, BuildingBase* pTarget);

	void FreeAWorker(BuildingBase* pBuild );
	void FollowBuild( Unit* pRole, BuildingBase* pTarget );
	void SetAWorker(BuildingBase* pHome, BuildingBase* pTarget);


	// 在战斗中设置要工作的工人
	void OnBattleSetBuildingWorker( std::vector<Unit*>& nowBuilding );

public:

	Unit* CreateResourceWorker(Unit* pHome);

	void InitResourceWorkerTarget(Unit* pRole, int taskNum );

	std::vector<Unit*> GetUnitWithType(unit_type type);

	Unit* GetTownHall();

	void MoveAResourceWorkerToNewTarget(Unit* pRole);


	void AllWorkerRunAway();

	
	void SetResourceWorker();
	
};

#endif
