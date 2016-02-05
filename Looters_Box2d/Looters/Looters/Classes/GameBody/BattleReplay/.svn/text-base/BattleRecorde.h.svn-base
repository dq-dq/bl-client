#ifndef BattleRecorde_h__
#define BattleRecorde_h__

#include "cocos2d.h"

#include "BattleTypeDef.h"
#include "CentralData.h"


class BattleRecorde
{
public:
	static BattleRecorde* sharedBattleRecorde();
	
private:
	BattleRecorde();
	~BattleRecorde();
		
private:
	void Clear();

public:
	void StartRecorde();	
	
	void EndRecorde(char const* fileName);
	
	void AddBattleInfo();
	void AddBuild(CentralData::M_UserMapData const& data);
	void AddPeople( int unitID, b2Vec2 const& pos );

private:
	void ReComputeTime();
	void SaveFile(char const* fileName);
public:
	bool IsStartRecorde() const;


private:

	long long m_startTime;
    long long m_endTime;
	people_array_t m_people;
	build_array_t m_build;
	
private:
	BattleRecorde( BattleRecorde const& );
	BattleRecorde& operator =( BattleRecorde const&);
	
};

#endif // BattleRecorde_h__
