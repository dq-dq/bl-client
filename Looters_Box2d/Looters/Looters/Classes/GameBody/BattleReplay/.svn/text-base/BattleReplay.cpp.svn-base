
#include "BattleReplay.h"
#include "Until.h"
#include "CentralLayer.h"
USING_NS_CC;

BattleReplay* BattleReplay::sharedBattleReplay()
{
	static BattleReplay battle;
	return &battle;
}


BattleReplay::BattleReplay()
	: m_pLayer(NULL), m_startTime(0),m_endTime(0)
	, m_people(), m_curPeople(0)
	, m_build(), m_curBuild(0)
	, m_isRunAway(false), m_runAwayTime(0)
{

}

BattleReplay::~BattleReplay()
{
	Clear();
}

void BattleReplay::Clear()
{
	m_pLayer = NULL;
	m_startTime = 0;
    m_endTime = 0;

	people_array_t().swap(m_people);
	m_curPeople = 0;

	build_array_t().swap(m_build);
	m_curBuild = 0;

	m_isRunAway = false;
	m_runAwayTime = 0;
}

void BattleReplay::StartReplay(CentralLayer* layer, char const* fileName)
{
	CCAssert(NULL!=layer, __FUNCTION__);
	CCAssert(NULL!=fileName, __FUNCTION__);
	CCAssert(!IsStartReplay(), __FUNCTION__);

	LoadFile(fileName);
	m_startTime = Until::millisecondNow() + S_BattleStartTime;
	m_runAwayTime = Until::millisecondNow() + S_RunAwayStartTime;
    m_endTime = m_startTime + m_endTime;
	m_pLayer = layer;
}

bool BattleReplay::IsStartReplay()
{
	return m_startTime>0;
}

void BattleReplay::LoadFile(char const* fileName)
{
	string dc = CCFileUtils::sharedFileUtils()->getWriteablePath();
	dc.append(fileName);

	do 
	{
		// read the file from hardware
		FILE *fp = fopen(dc.c_str(), "rb");
		//CC_BREAK_IF(!fp);
		CCAssert(NULL!=fp, __FUNCTION__);

		{
			size_t num;
			size_t ret = fread(&num, 1, sizeof(num), fp);
			CCAssert(0<num, __FUNCTION__);
			m_build.reserve(num);

			Build_t build;
			for (size_t i=0; i!=num; ++i)
			{
				ret = fread(&build.building_level, 1, sizeof(build.building_level), fp);
				ret = fread(&build.building_id, 1, sizeof(build.building_id), fp);
				ret = fread(&build.index, 1, sizeof(build.index), fp);
				ret = fread(&build.building_status, 1, sizeof(build.building_status), fp);
				ret = fread(&build.collect_count, 1, sizeof(build.collect_count), fp);
				ret = fread(&build.second_elixir_count, 1, sizeof(build.second_elixir_count), fp);
				ret = fread(&build.uniqueness_build_id, 1, sizeof(build.uniqueness_build_id), fp);

				m_build.push_back(build);
			}
            
            
		}


		{
			size_t num;
			size_t ret = fread(&num, 1, sizeof(num), fp);
			m_people.reserve(num);

			People_t people;
			for (size_t i=0; i!=num; ++i)
			{
				ret = fread(&people.time, 1, sizeof(people.time), fp);
				ret = fread(&people.unitID, 1, sizeof(people.unitID), fp);
				ret = fread(&people.pos, 1, sizeof(people.pos), fp);

				m_people.push_back(people);
			}

		}		
        fread(&m_endTime, 1, sizeof(m_endTime), fp);
        
		fclose(fp);
	} while (0);

}

bool BattleReplay::GetBuild( CentralData::M_UserMapData& data )
{
	CCAssert(IsStartReplay(), __FUNCTION__);

	if (m_build.size()!=m_curBuild)
	{
		Build_t& build = m_build[m_curBuild];
		data.building_level = build.building_level;
		data.building_id = build.building_id;
		data.map_index_x = build.index.x;
		data.map_index_y = build.index.y;
		data.building_status = build.building_status;
		data.collect_count = build.collect_count;
		data.second_elixir_count = build.second_elixir_count;
		data.uniqueness_build_id = build.uniqueness_build_id;

		++m_curBuild;

		return m_build.size()!=m_curBuild;
	}

	return false;
}




bool BattleReplay::Update()
{
	if (IsStartReplay())
	{
        long long nowTime = Until::millisecondNow();
        if (nowTime>m_endTime) {
            return true;
        }

		if (!m_isRunAway && nowTime > m_runAwayTime)
		{
			m_pLayer->AllWorkerRunAway();
			m_isRunAway = true;
		}
        
		size_t iCur = m_curPeople;
		size_t iEnd = m_people.size();
		if (iCur==iEnd)
		{
			return false;
		}
			
		
		int time = nowTime - m_startTime;
		for (; m_people[iCur].time < time && iCur!=iEnd; ++iCur)
		{
			m_pLayer->AddPeople(m_people[iCur].unitID, to_CCPoint(m_people[iCur].pos) , NULL);
		}
		
		m_curPeople = iCur;
	}
    return false;
}

void BattleReplay::EndReplay()
{
	CCAssert(IsStartReplay(), __FUNCTION__);
	Clear();

}
