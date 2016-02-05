
#include "BattleRecorde.h"
#include "Until.h"
#include "CentralData.h"

USING_NS_CC;


BattleRecorde* BattleRecorde::sharedBattleRecorde()
{
	static BattleRecorde battle;
	return &battle;
}

BattleRecorde::BattleRecorde()
	: m_startTime(0), m_endTime(0),m_people()
{

}

BattleRecorde::~BattleRecorde()
{
	Clear();
}

void BattleRecorde::Clear()
{
	m_startTime = 0;
    m_endTime = 0;
	
	people_array_t().swap(m_people);
	build_array_t().swap(m_build);
}

void BattleRecorde::StartRecorde()
{
	CCAssert(!IsStartRecorde(), __FUNCTION__);
	m_startTime = Until::millisecondNow();
}

bool BattleRecorde::IsStartRecorde() const
{
	return m_startTime>0;
}

void BattleRecorde::AddBuild( CentralData::M_UserMapData const& data )
{
	Build_t build;
	build.building_level = data.building_level;
	build.building_id = data.building_id;
	build.index = iVec2(data.map_index_x, data.map_index_y);
	build.building_status = data.building_status;
	build.collect_count = data.collect_count;
	build.second_elixir_count = data.second_elixir_count;
	build.uniqueness_build_id = data.uniqueness_build_id;

	m_build.push_back(build);
}


void BattleRecorde::AddPeople( int unitID, b2Vec2 const& pos )
{
	CCAssert(IsStartRecorde(), __FUNCTION__);

	long long nowTime = Until::millisecondNow();

	People_t people;
	people.time = nowTime - m_startTime;
	people.unitID = unitID;
	people.pos = pos;

	m_people.push_back(people);
}

void BattleRecorde::EndRecorde(char const* fileName)
{
	CCAssert(IsStartRecorde(), __FUNCTION__);
	CCAssert(NULL!=fileName, __FUNCTION__);	
//	if (!IsStartRecorde()) {
//		return;
//	}

	if (!m_people.empty())
	{
		ReComputeTime();
		SaveFile(fileName);
	}

	Clear();
}


void BattleRecorde::ReComputeTime()
{
	CCAssert(!m_people.empty(), __FUNCTION__);

	int startTime = m_people.front().time;
	for (people_array_t::iterator iCur=m_people.begin(), iEnd=m_people.end();
		iCur!=iEnd; ++iCur)
	{
		(*iCur).time -= startTime;
	}

    m_endTime = Until::millisecondNow() -m_startTime -startTime;
}


void BattleRecorde::SaveFile(char const* fileName)
{
	string dc = CCFileUtils::sharedFileUtils()->getWriteablePath();
	dc.append(fileName);
	
    do 
    {		
        // read the file from hardware
        FILE *fp = fopen(dc.c_str(), "wb");
        //CC_BREAK_IF(!fp);
		CCAssert(NULL!=fp, __FUNCTION__);


		// 保存建筑
		{
			size_t num = m_build.size();
			size_t ret = fwrite(&num, 1, sizeof(num), fp);

			build_array_t::iterator iCur = m_build.begin();
			build_array_t::iterator iEnd = m_build.end();
			for (; iCur!=iEnd; ++iCur) 
			{
				Build_t const& build = *iCur;

				ret = fwrite(&build.building_level, 1, sizeof(build.building_level), fp);
				ret = fwrite(&build.building_id, 1, sizeof(build.building_id), fp);
				ret = fwrite(&build.index, 1, sizeof(build.index), fp);
				ret = fwrite(&build.building_status, 1, sizeof(build.building_status), fp);
				ret = fwrite(&build.collect_count, 1, sizeof(build.collect_count), fp);
				ret = fwrite(&build.second_elixir_count, 1, sizeof(build.second_elixir_count), fp);
				ret = fwrite(&build.uniqueness_build_id, 1, sizeof(build.uniqueness_build_id), fp);
			}
		}

		

		// 保存士兵
		{
			size_t num = m_people.size();
			size_t ret = fwrite(&num, 1, sizeof(num), fp);
				
			people_array_t::iterator iCur = m_people.begin();
			people_array_t::iterator iEnd = m_people.end();
			for (; iCur!=iEnd; ++iCur) 
			{
				People_t const& role = *iCur;
				
				ret = fwrite(&role.time, 1, sizeof(role.time), fp);
				ret = fwrite(&role.unitID, 1, sizeof(role.unitID), fp);
				ret = fwrite(&role.pos, 1, sizeof(role.pos), fp);
			}
			
		}		
	
        fwrite(&m_endTime, 1, sizeof(m_endTime), fp);
        fclose(fp);
    } while (0);
}
