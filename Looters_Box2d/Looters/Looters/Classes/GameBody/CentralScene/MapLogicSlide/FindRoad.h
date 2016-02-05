#ifndef FindRoad_h__
#define FindRoad_h__

#include "IndexedPriority.h"
#include "GamePlatform.h"
#include "some_tool.h"



struct ShortestPathStep
{
	enum at_pos_t
	{
		AP_CLOSS,
		AP_OPEN,
		AP_NONE
	};

	void reset()
	{
		index = -1;
		atpos = AP_NONE;
		gScore = 0;
		hScore = 0;
		parent = -1;
	}


	ShortestPathStep()
		: index(-1), atpos(AP_NONE)
		, gScore(0), hScore(0), parent(-1)
	{

	}	

	float get_f_score() const { return gScore + hScore; }


	int index;
	at_pos_t atpos;
	float gScore;
	float hScore;	
	int parent;
};

class CentralLayer;
class Unit;

class FindRoad
{


public:
	static FindRoad* sharedFindRoad()
	{
		static FindRoad road(TITLE_NUM_X2*TITLE_NUM_X2);
		return &road;
	}

	typedef std::vector<ShortestPathStep> path_store_t;
	typedef std::vector<iVec2> ai_int_path_t;


public:
	static iBox2 GetArmyInnerBox();
	static iBox2 GetArmyOutBox();
	
	static int to_int_army(iVec2 const& index)
	{
		return index.y * S_ArmyOutLen * 4 + index.x;
	}
	
	static iVec2 to_iVec2_army(int index)
	{
		return iVec2(index%(S_ArmyOutLen*4), index/(S_ArmyOutLen*4));
	}

	// 营火占地块
	static int const S_ArmyOutLen = 5;
	static int const S_ArmyInnerLen = 2;

private:
	explicit FindRoad( int maxNum )
		: m_allPath(maxNum), m_open(maxNum, ai_step_less(m_allPath))
		, m_newTarget(NULL), m_findIndex(-1)
		, m_box(to_iVec2(0, 0), to_iVec2(maxNum-1, maxNum-1))
	{

	}

public:
	bool Search( Unit* src, Unit* dst);
	bool SearchInHome( Unit* src, iVec2 const& dstIndex);
	bool SearchInArmy( Unit* src, iVec2 const& dstIndex, iVec2 const& leftTop );

	Unit* GetNewTarget();
	void GetPath( std::vector<b2Vec2>& path );

	void GetPathArmy( std::vector<b2Vec2>& path );

private:

	void Reset();

	void LookNear( iVec2 const& pos, ai_int_path_t& around, Unit** target );
	void LookNearHome( iVec2 const& pos, ai_int_path_t& around);
	void LookNearArmy( iVec2 const& pos, ai_int_path_t& around );



	// 地形块是否可走
	bool IsCanWalk(iVec2 const& index, Unit** newTarget);
	bool IsCanWalkHome(iVec2 const& index);

	float CostToCurWithWall(iVec2 const& src, iVec2 const& dst);
	float CostToCur( iVec2 const& src, iVec2 const& dst );

	float CostToTarget(iVec2 const& src, iVec2 const& dst);

	iVec2 FindEmptyTitle( iVec2 const& srcIndex )	;

private:

	class ai_step_less
		: public std::binary_function<int, int, bool>
	{
	public:
		
		ai_step_less(path_store_t const& path)
			: m_path(path)
		{

		}

		bool operator() (int lhs, int rhs) const
		{
			return m_path[lhs].get_f_score() > m_path[rhs].get_f_score();
		}


	private:
		path_store_t const& m_path;
	};


	path_store_t m_allPath;
	IndexedPriority<ai_step_less> m_open;


	Unit* m_src;
	Unit* m_newTarget;

	int m_findIndex;
	
	iBox2 m_box;
	iVec2 m_leftTopArmy;

private:
	FindRoad(FindRoad const&);
	FindRoad& operator= (FindRoad const&);

};


#endif // FindRoad_h__
