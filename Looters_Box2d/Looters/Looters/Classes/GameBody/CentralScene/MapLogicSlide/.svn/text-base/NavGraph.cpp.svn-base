
#include "NavGraph.h"
#include "GamePlatform.h"
#include "Unit.h"
#include "some_tool.h"

NavGraph::NavGraph()
: m_map()
{
	
}

NavGraph::~NavGraph()
{
	
}

void NavGraph::Reset()
{
	m_map.clear();
}

Unit* NavGraph::GetUnit( int index ) const
{
	map_t::const_iterator iFind =  m_map.find(index);

	return m_map.end()==iFind? NULL: iFind->second;
}


void NavGraph::AddUnit( Unit* pUnit )
{
	assert(!(pUnit->get_unit_type() < UT_NOGAIN_BUILD) && (pUnit->get_unit_type()<UT_ROLE));
	
	int range = pUnit->radius*2;
	
	//iVec2 h = half_title_covert_t::pos_to_index(pUnit->GetCenterPos());
	//iVec2 h1 = normal_title_covert_t::pos_to_index(pUnit->GetCenterPos());
	
	iVec2 leftTop = half_title_left_top_index(pUnit->GetCenterPos(), range);

	for (int x=leftTop.x, xEnd=leftTop.x+range; x!=xEnd; ++x)
	{
		for (int y=leftTop.y, yEnd=leftTop.y+range; y!=yEnd; ++y)
		{
//			assert( m_map.end()== m_map.find(half_title_covert_t::index_to_int(to_iVec2(x, y))));
			m_map[half_title_covert_t::index_to_int(to_iVec2(x, y))] = pUnit;
		}
	}
}

void NavGraph::DestoryUnit( Unit* pUnit )
{
	assert(!(pUnit->get_unit_type() < UT_NOGAIN_BUILD) && (pUnit->get_unit_type()<UT_ROLE));	

	int range = pUnit->radius * 2;	
	iVec2 leftTop = half_title_left_top_index(pUnit->GetCenterPos(true), range);

	for (int x=leftTop.x, xEnd=leftTop.x+range; x!=xEnd; ++x)
	{
		for (int y=leftTop.y, yEnd=leftTop.y+range; y!=yEnd; ++y)
		{
//			assert(pUnit==m_map[half_title_covert_t::index_to_int(to_iVec2(x, y))]);
			
			m_map.erase(half_title_covert_t::index_to_int(to_iVec2(x, y)));
		}
	}
}



