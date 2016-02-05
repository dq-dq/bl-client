#include "FindRoad.h"
#include "Unit.h"
#include "CentralLayer.h"
#include "NavGraph.h"


iBox2 FindRoad::GetArmyInnerBox()
{
	int inner = S_ArmyInnerLen * 4 /2;
	int center = S_ArmyOutLen * 4 / 2;
	int leftTop = center - inner;
	int rightBottom = center + inner -1;

	return iBox2(to_iVec2(leftTop, leftTop), to_iVec2(rightBottom, rightBottom));
}

iBox2 FindRoad::GetArmyOutBox()
{
	int const line = S_ArmyOutLen * 4;
	return iBox2(to_iVec2(0, 0), to_iVec2(line-1, line-1));
}

Unit* FindRoad::GetNewTarget()
{
	return m_newTarget;
}

void FindRoad::GetPath( std::vector<b2Vec2>& path )
{
	int index = m_findIndex;

	while (-1!=index)
	{
		path.push_back(half_title_covert_t::index_to_pos(half_title_covert_t::int_to_index(index)));
		index = m_allPath[index].parent;
	}

	// 弹出初始点
	if (path.size()>1) {
		path.pop_back();
	}
	
	
//	ai_int_path_t debugpath;
//
//	{
//		index = m_findIndex;
//		
//		while (-1!=index)
//		{
//			debugpath.push_back( half_title_covert_t::int_to_index(index));
//			index = m_allPath[index].parent;
//		}				
//	}	
}


void FindRoad::GetPathArmy( std::vector<b2Vec2>& path )
{
	int index = m_findIndex;

	while (-1!=index)
	{
		iVec2 i = to_iVec2_army(index);
		i += m_leftTopArmy;
		path.push_back(quad_title_covert_t::index_to_pos(i));
		index = m_allPath[index].parent;
	}

	// 弹出初始点
	if (path.size()>1) {
		path.pop_back();
	}
	
	
//	ai_int_path_t debugpath;
//
//	{
//		index = m_findIndex;
//		
//		while (-1!=index)
//		{
//			debugpath.push_back( to_iVec2_army(index));
//			index = m_allPath[index].parent;
//		}				
//	}
	
}

bool FindRoad::Search( Unit* src, Unit* dst )
{
	Reset();

	m_src = src;
	bool result = false;

	int find_count = 0;	

	ai_int_path_t around;
	around.reserve(8);

	//iVec2 srcIndexV = half_title_covert_t::pos_to_index(to_b2Vec2(src->getPosition()));
	
	int srcIndex = half_title_covert_t::index_to_int(half_title_covert_t::pos_to_index(to_b2Vec2(src->getPosition()) ));
	m_open.push(srcIndex);
	m_allPath[srcIndex].index = srcIndex;	

	b2Vec2 const& dstPos = dst->GetCenterPos();
	float dstRange = dst->radius * BUILDINTBASEGRID_EDGE_LEN + src->AttackRange * 2.f;
	Box45 dstBox( dstPos, dstRange);
	iVec2 const dstIndex =  half_title_covert_t::pos_to_index(dstPos);
	
	{
//		for (int i=0, iEnd=TITLE_NUM_X2*TITLE_NUM_X2; i!=iEnd; ++i) 
//		{
//			Unit* pUnit = NavGraph::sharedNavGraph()->GetUnit(i);
//			if (NULL!=pUnit ) 
//			{
//				++find_count;
//			}
//		}
	}

	do
	{

		++find_count;

		ShortestPathStep& cur = m_allPath[m_open.pop()];
		cur.atpos = ShortestPathStep::AP_CLOSS;
		
		iVec2 vecIndex = half_title_covert_t::int_to_index(cur.index);

		// 最近的是墙
		if (dstBox.is_container(half_title_covert_t::index_to_pos(vecIndex)))
		{
			result = true;
			m_findIndex = cur.index;
			break;
		}
		else
		{
			Unit* pUnit = NavGraph::sharedNavGraph()->GetUnit(cur.index);
			if (NULL!=pUnit && pUnit->is_unit_type(UT_WALL_BUILD))
			{
				m_newTarget = pUnit;
				result = true;
				m_findIndex = cur.parent;
				break;
			}
			
		}
		

		// 取周围8个方块
		Unit* newTarget = NULL;
		around.clear();
		LookNear( vecIndex, around, &newTarget);
		if (NULL!=newTarget)
		{
			m_newTarget = newTarget;
			result = true;
			m_findIndex = cur.index;
			break;
		}
		
		for (ai_int_path_t::iterator iNear=around.begin(), iEnd=around.end();
			iNear!=iEnd; ++iNear)
		{

			iVec2 const& index = (*iNear);
			int intIndex = half_title_covert_t::index_to_int(index);
			float gScore = cur.gScore + CostToCurWithWall(vecIndex, index);

			ShortestPathStep& pNear = m_allPath[intIndex];				

			if (ShortestPathStep::AP_NONE==pNear.atpos)
			{
				pNear.gScore = gScore;
				pNear.hScore = CostToTarget(index, dstIndex);
				pNear.atpos = ShortestPathStep::AP_OPEN;
				pNear.parent = cur.index;
				pNear.index = intIndex;

				m_open.push(intIndex);
			}
			else if (ShortestPathStep::AP_OPEN==pNear.atpos && gScore<pNear.gScore)
			{
				pNear.gScore = gScore;
				pNear.parent = cur.index;
				m_open.sort(intIndex);
			}			
		}

	} while ( !m_open.empty());


	return result;
}


iVec2 FindRoad::FindEmptyTitle( iVec2 const& srcIndex )
{
	iVec2 centerIndex = srcIndex;
	
	iBox2 const bound(to_iVec2(0, 0), to_iVec2(TITLE_NUM_X2, TITLE_NUM_X2));
	iVec2 result(-1, -1);
	
	if (bound.IsContains(centerIndex) && IsCanWalkHome(centerIndex))
	{	
		result = centerIndex;
		return result;
	}
	
	for (int i=1; i<TITLE_NUM_X2; ++i)
	{
		
		iVec2 leftTop(centerIndex.x-i, centerIndex.y-i);
		iVec2 rightBottom(centerIndex.x+i, centerIndex.y+i);
		
		iVec2 cur;
		
		bool isAllOut =true;
		// 顶一行
		for ( int x=leftTop.x, xEnd=rightBottom.x; x<xEnd; ++x )			
		{				
			cur.x = x;
			cur.y = leftTop.y;
			
			bool isIn = bound.IsContains(cur);
			isAllOut &= !isIn;
			
			if (isIn && IsCanWalkHome(cur))
			{
				result = cur;			
				return result;
			}
			
		}
		
		// 底一行
		for (int x=leftTop.x, xEnd=rightBottom.x; x<xEnd; ++x)
		{
			cur.x = x;
			cur.y = rightBottom.y;
			
			bool isIn = bound.IsContains(cur);
			isAllOut &= !isIn;
			
			if (isIn && IsCanWalkHome(cur))
			{
				result = cur;
				return result;
			}
		}
		
		
		// 右一列
		for (int y=leftTop.y+1, yEnd=rightBottom.y-1; y<yEnd; ++y)
		{
			cur.x = leftTop.x;
			cur.y = y;
			
			bool isIn = bound.IsContains(cur);
			isAllOut &= !isIn;
			
			if (isIn && IsCanWalkHome(cur))
			{
				result = cur;				
				return result;
			}
		}
		
		
		// 左一列
		for (int y=leftTop.y+1, yEnd=rightBottom.y-1; y<yEnd; ++y)
		{
			cur.x = rightBottom.x;
			cur.y = y;
			
			bool isIn = bound.IsContains(cur);
			isAllOut &= !isIn;
			
			if (isIn && IsCanWalkHome(cur))
			{
				result = cur;			
				return result;
			}
		}
		
		
		if (isAllOut)
		{
			break;
		}
		
	}
	
	return result;
}



bool FindRoad::SearchInHome( Unit* src, iVec2 const& dstIndex )
{
	Reset();
	m_src = src;
	bool result = false;

	int find_count = 0;	

	ai_int_path_t around;
	around.reserve(8);

	iVec2 newI =  FindEmptyTitle(half_title_covert_t::pos_to_index(to_b2Vec2(src->getPosition()) ));
//    newI = FindEmptyTitle(to_iVec2(31, 60));
    
	CCAssert(newI.x!=-1 && newI.y!=-1, __FUNCTION__);
	int srcIndex = half_title_covert_t::index_to_int(newI);
	
//	srcIndex = half_title_covert_t::index_to_int(to_iVec2(31, 60));
	m_open.push(srcIndex);
	m_allPath[srcIndex].index = srcIndex;	

	iVec2 dd = dstIndex;
//	dd = to_iVec2(32, 52);
	int dstIndexInt = half_title_covert_t::index_to_int(dd);
	

	{
//		iVec2 s = half_title_covert_t::int_to_index(srcIndex);
//		iVec2 d = half_title_covert_t::int_to_index(dstIndexInt);
//		
//		CCLog("research src->dst, (%d, %d), (%d, %d)", s.x, s.y, d.x, d.y);
	}
	
	do
	{

		++find_count;

		ShortestPathStep& cur = m_allPath[m_open.pop()];
		cur.atpos = ShortestPathStep::AP_CLOSS;


		if (dstIndexInt==cur.index)
		{
			result = true;
			m_findIndex = cur.index;
			break;
		}
		
		// 取周围8个方块
		around.clear();
		iVec2 vecIndex = half_title_covert_t::int_to_index(cur.index);
		LookNearHome( vecIndex, around);
		for (ai_int_path_t::iterator iNear=around.begin(), iEnd=around.end();
			iNear!=iEnd; ++iNear)
		{

			iVec2 const& index = (*iNear);
			int intIndex = half_title_covert_t::index_to_int(index);
			float gScore = cur.gScore + CostToCur(vecIndex, index);

			ShortestPathStep& pNear = m_allPath[intIndex];				

			if (ShortestPathStep::AP_NONE==pNear.atpos)
			{
				pNear.gScore = gScore;
				pNear.hScore = CostToTarget(index, dd);
				pNear.atpos = ShortestPathStep::AP_OPEN;
				pNear.parent = cur.index;
				pNear.index = intIndex;

				m_open.push(intIndex);
			}
			else if (ShortestPathStep::AP_OPEN==pNear.atpos && gScore<pNear.gScore)
			{
				pNear.gScore = gScore;
				pNear.parent = cur.index;
				m_open.sort(intIndex);
			}			
		}

	} while ( !m_open.empty());


	return result;
}



bool FindRoad::SearchInArmy( Unit* src, iVec2 const& dstIndex, iVec2 const& leftTop )
{
	Reset();
	m_src = src;
	m_leftTopArmy = leftTop;

	int find_count = 0;

	ai_int_path_t around;
	around.reserve(8);
	
	iVec2 posInArmy = quad_title_covert_t::pos_to_index(to_b2Vec2(src->getPosition())) - leftTop;
	int srcIndex = to_int_army(posInArmy);
	m_open.push(srcIndex);
	m_allPath[srcIndex].index = srcIndex;	

	iVec2 dstIndexArmy = dstIndex-leftTop;
	int dstIndexInt = to_int_army(dstIndexArmy);

	do
	{
		++find_count;

		ShortestPathStep& cur = m_allPath[m_open.pop()];
		cur.atpos = ShortestPathStep::AP_CLOSS;


		if (dstIndexInt==cur.index)
		{
			m_findIndex = cur.index;
			return true;
		}

		// 取周围8个方块
		around.clear();
		iVec2 vecIndex = to_iVec2_army(cur.index);
		LookNearArmy( vecIndex, around);
		for (ai_int_path_t::iterator iNear=around.begin(), iEnd=around.end();
			iNear!=iEnd; ++iNear)
		{

			iVec2 const& index = (*iNear);
			int intIndex = to_int_army(index);
			float gScore = cur.gScore + CostToCur(vecIndex, index);

			ShortestPathStep& pNear = m_allPath[intIndex];				

			if (ShortestPathStep::AP_NONE==pNear.atpos)
			{
				pNear.gScore = gScore;
				pNear.hScore = CostToTarget(index, dstIndexArmy);
				pNear.atpos = ShortestPathStep::AP_OPEN;
				pNear.parent = cur.index;
				pNear.index = intIndex;

				m_open.push(intIndex);
			}
			else if (ShortestPathStep::AP_OPEN==pNear.atpos && gScore<pNear.gScore)
			{
				pNear.gScore = gScore;
				pNear.parent = cur.index;
				m_open.sort(intIndex);
			}			
		}

	} while ( !m_open.empty());


	return false;
}


float FindRoad::CostToTarget( iVec2 const& src, iVec2 const& dst)
{
//	float grid = range / (BUILDINTBASEGRID_EDGE_LEN/2.f) / 2.f;
//	float result = b2Abs(src.x-dst.x)-grid;
//	result += b2Abs(src.y-dst.y)-grid;

	float result = b2Abs(src.x-dst.x);
	result += b2Abs(src.y-dst.y);	
	return result * 10.f;
}

float FindRoad::CostToCurWithWall( iVec2 const& src, iVec2 const& dst )
{
	Unit* pUnit = NavGraph::sharedNavGraph()->GetUnit(half_title_covert_t::index_to_int(dst));
	float num = 0;
	if (NULL!=pUnit && pUnit->is_unit_type(UT_WALL_BUILD)) {
		num = 140;
	}

	return CostToCur(src, dst) + num;
}


float FindRoad::CostToCur( iVec2 const& src, iVec2 const& dst )
{
	return src.x== dst.x || src.y==dst.y? 10.f: 14.f;
}

void FindRoad::Reset()
{
	path_store_t::iterator iCur = m_allPath.begin();
	path_store_t::iterator iEnd = m_allPath.end();

	for (; iCur!=iEnd; ++iCur)
	{
		(*iCur).reset();
	}

	m_open.reset();
	m_newTarget = NULL;
	m_findIndex = -1;
	m_leftTopArmy.SetZero();
}

bool FindRoad::IsCanWalk( iVec2 const& index, Unit** newTarget )
{	

	Unit* pUnit = NavGraph::sharedNavGraph()->GetUnit(half_title_covert_t::index_to_int(index));

	if (NULL==pUnit)
	{
		return true;
	}

	if (m_src->is_love_target(pUnit))
	{
		//float dstRange = pUnit->radius * BUILDINTBASEGRID_EDGE_LEN + m_src->AttackRange * 2.f;
		//Box45 box(pUnit->GetCenterPos(), dstRange);
		//if (box.is_container(half_title_covert_t::index_to_pos(index)))
		//{
		//	*newTarget = pUnit;
		//	return true;
		//}

		*newTarget = pUnit;
		return true;

	}
	else if (pUnit->is_unit_type(UT_WALL_BUILD))
	{
		return true;
	}

	return false;
	
}


bool FindRoad::IsCanWalkHome( iVec2 const& index )
{
	Unit* pUnit = NavGraph::sharedNavGraph()->GetUnit(half_title_covert_t::index_to_int(index));

	if (NULL!=pUnit && !pUnit->is_unit_type(UT_WALL_BUILD))
	{
		return false;
	}
	
	return true;
}

void FindRoad::LookNearArmy( iVec2 const& pos, ai_int_path_t& around )
{
	static iBox2 s_OutBox = GetArmyOutBox();
	static iBox2 s_InnerBox = GetArmyInnerBox();

	enum dir 
	{
		top = 0,
		left,
		bottom,
		right
	};

	bool canWalk[4] = {false, false, false, false};

	iVec2 nearPos[4] = { iVec2(pos.x, pos.y-1), iVec2(pos.x-1, pos.y)
		, iVec2(pos.x, pos.y+1), iVec2(pos.x+1, pos.y)};

	for (int i=0; i<4; ++i) 
	{
		if ( s_OutBox.IsContains(nearPos[i]) && !s_InnerBox.IsContains(nearPos[i])) 
		{
			around.push_back(nearPos[i]);
			canWalk[i] = true;			
		}
	}


	iVec2 tl(pos.x-1, pos.y-1);
	if ((canWalk[top] || canWalk[left]) && s_OutBox.IsContains(tl) && !s_InnerBox.IsContains(tl))
	{
		around.push_back(tl);
	}

	iVec2 bl(pos.x-1, pos.y+1);
	if ( (canWalk[bottom] || canWalk[left])&&s_OutBox.IsContains(bl) && !s_InnerBox.IsContains(bl))
	{
		around.push_back(bl);
	}

	iVec2 tr(pos.x+1, pos.y-1);
	if ( (canWalk[top] || canWalk[right])&&s_OutBox.IsContains(tr) && !s_InnerBox.IsContains(tr))
	{
		around.push_back(tr);
	}

	iVec2 br(pos.x+1, pos.y+1);
	if ((canWalk[bottom] || canWalk[right])&&s_OutBox.IsContains(br) && !s_InnerBox.IsContains(br))
	{
		around.push_back(br);
	}
}




void FindRoad::LookNearHome( iVec2 const& pos, ai_int_path_t& around )
{
	enum dir 
	{
		top = 0,
		left,
		bottom,
		right
	};

	bool canWalk[4] = {false, false, false, false};

	iVec2 nearPos[4] = { iVec2(pos.x, pos.y-1), iVec2(pos.x-1, pos.y)
		, iVec2(pos.x, pos.y+1), iVec2(pos.x+1, pos.y)};

	for (int i=0; i<4; ++i) 
	{
		if ( m_box.IsContains(nearPos[i]) && IsCanWalkHome(nearPos[i])) 
		{
			around.push_back(nearPos[i]);
			canWalk[i] = true;			
		}
	}


	iVec2 tl(pos.x-1, pos.y-1);
	if (m_box.IsContains(tl) && (canWalk[top] || canWalk[left]) && IsCanWalkHome(tl))
	{
		around.push_back(tl);
	}

	iVec2 bl(pos.x-1, pos.y+1);
	if ( m_box.IsContains(bl) &&(canWalk[bottom] || canWalk[left]) && IsCanWalkHome(bl))
	{
		around.push_back(bl);
	}

	iVec2 tr(pos.x+1, pos.y-1);
	if ( m_box.IsContains(tr) &&(canWalk[top] || canWalk[right]) && IsCanWalkHome(tr))
	{
		around.push_back(tr);
	}

	iVec2 br(pos.x+1, pos.y+1);
	if (m_box.IsContains(br) && (canWalk[bottom] || canWalk[right]) && IsCanWalkHome(br))
	{
		around.push_back(br);
	}
}


void FindRoad::LookNear( iVec2 const& pos, ai_int_path_t& around, Unit** target )
{
	enum dir 
	{
		top = 0,
		left,
		bottom,
		right
	};

	bool canWalk[4] = {false, false, false, false};

	iVec2 nearPos[4] = { iVec2(pos.x, pos.y-1), iVec2(pos.x-1, pos.y)
		, iVec2(pos.x, pos.y+1), iVec2(pos.x+1, pos.y)};

	for (int i=0; i<4; ++i) 
	{
		if ( m_box.IsContains(nearPos[i]) && IsCanWalk(nearPos[i], target)) 
		{
			around.push_back(nearPos[i]);
			if (NULL!=*target)
			{
				return;
			}

			canWalk[i] = true;			
		}
	}


	iVec2 tl(pos.x-1, pos.y-1);
	if (m_box.IsContains(tl) && (canWalk[top] || canWalk[left]) && IsCanWalk(tl, target))
	{
		around.push_back(tl);
		if (NULL!=*target)
		{
			return;
		}
	}

	iVec2 bl(pos.x-1, pos.y+1);
	if ( m_box.IsContains(bl) &&(canWalk[bottom] || canWalk[left]) && IsCanWalk(bl, target))
	{
		around.push_back(bl);
		if (NULL!=*target)
		{
			return;
		}
	}

	iVec2 tr(pos.x+1, pos.y-1);
	if ( m_box.IsContains(tr) &&(canWalk[top] || canWalk[right]) && IsCanWalk(tr, target))
	{
		around.push_back(tr);
		if (NULL!=*target)
		{
			return;
		}
	}

	iVec2 br(pos.x+1, pos.y+1);
	if (m_box.IsContains(br) && (canWalk[bottom] || canWalk[right]) && IsCanWalk(br, target))
	{
		around.push_back(br);
		if (NULL!=*target)
		{
			return;
		}
	}
}








//void init_free_shorest_path_step()
//{
//	int num = MAPGRIDWIDTH * MAPGRIDWIDTH;
//	for (int i=0; i<num; ++i)
//	{
//		m_free_path_step.push_back(new ShortestPathStep);
//	}
//}
//
//ShortestPathStep* get_shortest_path_step(iVec2 const& pos)
//{
//	if (!m_free_path_step.empty())
//	{
//		ShortestPathStep* pStep = m_free_path_step.back();
//		pStep->index = pos;		
//		m_free_path_step.pop_back();
//		return pStep;
//	}
//
//
//	return new ShortestPathStep(pos);
//}
//
//
//void release_shortest_path_step()
//{
//
//	for (path_step_t::iterator iCur=m_free_path_step.begin(), iEnd=m_free_path_step.end(); 
//		iCur!=iEnd; ++iCur) {
//			delete (*iCur);
//	}
//	m_free_path_step.clear();
//}

//Unit* build_path(ShortestPathStep* pStep, ai_path_t& path, Unit* target)
//{
//	CCAssert(NULL!=pStep,  "");

//	Unit* pWall = NULL;

//	ShortestPathStep* pNewTarget = pStep;

//	while (NULL!=pStep)
//	{
//		Unit* pu = on_tiltle_unit_type(to_CCPoint(half_to_normal_title_index(pStep->index)), UT_WALL_BUILD);
//		if (NULL!=pu)
//		{
//			pWall = pu;
//			pNewTarget = pStep->parent;
//		}

//		pStep = pStep->parent;
//	}


//	// 加入随机目标点,避免重叠站位
//	//	path.push_back(random_target(pNewTarget, NULL!=pWall? pWall: target));


//	//	if (is_more_three_step(pNewTarget))
//	//	{
//	//		build_smooth_path(pNewTarget, path);
//	//	}
//	//	else
//	{
//		build_normal_path(pNewTarget, path);
//	}

//	return pWall;

//}


//bool is_more_three_step( ShortestPathStep* pStep )
//{
//	return false;

//	bool result = false;
//	int num = 0;

//	while (NULL!=pStep)
//	{
//		pStep = pStep->parent;
//		++num;

//		if (num == 3)
//		{
//			result = true;
//			break;
//		}			
//	}	

//	return result;
//}

//void build_normal_path( ShortestPathStep* pStep, ai_path_t &path )
//{	
//	while (NULL!=pStep)
//	{
//		path.push_back(half_title_covert_t::index_to_pos(pStep->index));
//		pStep = pStep->parent;
//	}

//	// 弹出初始点
//	if (path.size()>1) {
//		path.pop_back();
//	}
//}

//void build_smooth_path( ShortestPathStep* pStep, ai_path_t& path )
//{
//	//	ai_path_t debugPath;
//	//	build_normal_path(pStep, debugPath);



//	iVec2 first = pStep->index;
//	path.push_back(half_title_covert_t::index_to_pos(pStep->index));
//	pStep = pStep->parent;

//	iVec2 second = pStep->index;
//	pStep = pStep->parent;

//	iVec2 third;

//	while (NULL!=pStep)
//	{
//		third = pStep->index;
//		pStep = pStep->parent;

//		if (is_in_one_line(first, second, third))
//		{
//			second = third;
//		}
//		else
//		{
//			path.push_back(half_title_covert_t::index_to_pos(second));

//			first = second;
//			second = third;
//		}		
//	}

//}

//bool is_in_one_line( iVec2 const& first, iVec2 const& second, iVec2 const& third)
//{
//	static const float limit = cosf(CC_DEGREES_TO_RADIANS(175.f));	
//	b2Vec2 a(first.x - second.x, first.y - second.y);
//	b2Vec2 b(third.x - second.x, third.y-second.y);

//	return b2Dot(a, b) / (a.Length() * b.Length()) < limit;
//}

