#ifndef NavGraph_h__
#define NavGraph_h__

#include <tr1/unordered_map>

class Unit;
// 保存1/2格子中, 建筑占有格子
class NavGraph
{
public:
	static NavGraph* sharedNavGraph()
	{
		static NavGraph graph;
		return &graph;
	}

private:

	NavGraph();
	~NavGraph();

public:
	void Reset();
	
	void AddUnit( Unit* pUnit );

	void DestoryUnit( Unit* pUnit);

	Unit* GetUnit(int index) const;

private:
	typedef std::tr1::unordered_map<int, Unit*>  map_t;
	map_t m_map;

private:
	NavGraph(NavGraph const&);
	NavGraph& operator= (NavGraph const&);
};

#endif // NavGraph_h__
