#ifndef BattleReplay_h__
#define BattleReplay_h__

#include "cocos2d.h"
#include "BattleTypeDef.h"
#include "CentralData.h"

class CentralLayer;

class BattleReplay
{

public:
	static BattleReplay* sharedBattleReplay();

private:
	// 经过这时间,在开始出兵
	static const long long S_BattleStartTime = 4000;
	static const long long S_RunAwayStartTime = 2000;

private:	
	BattleReplay();
	~BattleReplay();

private:
	void Clear();


public:
	void StartReplay(CentralLayer* layer, char const* fileName);

	bool Update(); // true

	void EndReplay();

	// 还有建筑, 返回true
	bool GetBuild(CentralData::M_UserMapData& data);


private:
	void LoadFile(char const* fileName);
	bool IsStartReplay();

private:

	CentralLayer* m_pLayer;

	long long m_startTime;
    long long m_endTime;
	build_array_t m_build;
	std::size_t m_curBuild;

	people_array_t m_people;
	std::size_t m_curPeople;


	bool m_isRunAway;
	long long m_runAwayTime;
};


#endif // BattleReplay_h__
