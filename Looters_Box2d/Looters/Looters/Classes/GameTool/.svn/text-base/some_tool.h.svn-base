
#ifndef some_tool_h__
#define some_tool_h__

#include "GamePlatform.h"
#include "Box2D.h"
#include "iVec2.h"
#include "CCGeometry.h"



template <typename T>
inline T round(T const & x)
{
	return (x > 0) ? static_cast<T>(static_cast<int>(T(0.5) + x)) :
		-static_cast<T>(static_cast<int>(T(0.5) - x));
}

inline float float_equal( float x, float y )
{
	return fabs(x-y) < 0.0001f;
}

template<class T>
inline bool float_vec_equal(T const& lhs, T const& rhs)
{
	return float_equal(lhs.x, rhs.x) && float_equal(lhs.y, rhs.y);
}



template< class T>
inline T get_random_range(T min, T max)
{
	return min + CCRANDOM_0_1() * (max - min);
}



inline bool is_in_box(iVec2 const& src, int left, int right)
{
	return src.x>=left && src.x<=right && src.y>=left && src.y<=right;
}


template<class T>
CCPoint to_CCPoint(T const& val )
{
	return CCPoint(val.x, val.y);
}


template<class T>
inline b2Vec2 to_b2Vec2( T const& val )
{
	return b2Vec2(val.x, val.y);
}

template<class T>
inline iVec2 to_iVec2( T const& val )
{
	return iVec2((int)val.x, (int)val.y);
}
template<class T>
inline iVec2 to_iVec2( T x, T y)
{
	return iVec2((int)x, (int)y);
}

inline unsigned int map_index_to_index( CCPoint const& pos)
{
	return pos.x * MAPGRIDHEIGHT + pos.y;
}



template<int NUM, int WIDTH, int HEIGHT>
class title_convert
{
public:
	// 以左下角为原点, 地形块 0, 0 的中心位置
	static b2Vec2 title_0_0_pos()
	{
		b2Vec2 result( NUM /2.f * WIDTH, NUM * HEIGHT - HEIGHT / 2.f );
		return result;
	}

	//取地形块的中心位置
	static b2Vec2 index_to_pos( iVec2 const& index)
	{
		b2Vec2 result( (index.x - index.y) * WIDTH / 2.f, -(index.x + index.y) * HEIGHT / 2.f);
		result += title_0_0_pos();

		return result;
	}

	// 有效地图的坐标转换到地形块索引
	static iVec2 pos_to_index( b2Vec2 pos)
	{
		pos -= title_0_0_pos();

		iVec2 result;
		result.x = round(( pos.x - 2.f * pos.y ) / WIDTH);
		result.y = round( (- pos.x - 2.f * pos.y  ) / WIDTH );
		
		return result;
	}

	// 适应游戏逻辑中索引到int
//	static int index_to_int( iVec2 const& index)
//	{
//		return index.x * NUM + index.y;
//	}
//	
//	static iVec2 int_to_index(int index)
//	{	
//		return iVec2( index/NUM, index%NUM);
//	}
	
	static int index_to_int( iVec2 const& index)
	{
		return index.y * NUM + index.x;
	}

	static iVec2 int_to_index(int index)
	{	
		return iVec2( index%NUM, index/NUM);
	}

};

typedef title_convert<GamePlatform::S_MapGridNum, GamePlatform::S_BuildingBaseGridWidth, GamePlatform::S_BuildingBaseGridHeight>  normal_title_covert_t;
typedef title_convert<GamePlatform::S_MapGridNum*2, GamePlatform::S_BuildingBaseGridWidth/2, GamePlatform::S_BuildingBaseGridHeight/2>  half_title_covert_t;
typedef title_convert<GamePlatform::S_MapGridNum*2*2, GamePlatform::S_BuildingBaseGridWidth/4, GamePlatform::S_BuildingBaseGridHeight/4>  quad_title_covert_t;





inline iVec2 half_to_normal_title_index( iVec2 const& index )
{
	return iVec2( index.x/2, index.y/2 );
}


inline iVec2 half_title_left_top_index(b2Vec2 const& centerPos, int line)
{
	int center = line / 2;
	
	iVec2 result = half_title_covert_t::pos_to_index(centerPos);
	result.x -= center;
	result.y -= center;

	return result;
}



inline iVec2 quad_title_left_top_index(b2Vec2 const& centerPos, int line)
{
	int const grid_num_per_title = 4;
	int center = line * (grid_num_per_title / 2);
	
	iVec2 result = quad_title_covert_t::pos_to_index(centerPos);
	result.x -= center;
	result.y -= center;
	
	return result;
}

inline iVec2 quad_title_left_top_index_2(b2Vec2 const& centerPos, int line)
{
	int center = line /2;
	
	iVec2 result = quad_title_covert_t::pos_to_index(centerPos);
	result.x -= center;
	result.y -= center;
	
	return result;
}

// 随机取大正方形与小正方形(同中心)之间的小格子索引
// outRadius 大正方形边长, innerRadius 小正方形
inline iVec2 quad_title_random_index( int outRadius, int innerRadius)
{
	// 必须是偶数
	int const grid_num_per_title = 4;
	
	// 中心右下一格的索引
	int center = outRadius * (grid_num_per_title / 2);
	
	int topLeft = center - innerRadius * 2;
	int rightBottom = center + innerRadius * 2-1;
	
	int grid = outRadius * grid_num_per_title;
	
	iVec2 result;

	do 
	{
		result.x = static_cast<int>(CCRANDOM_0_1() * grid);
		result.y = static_cast<int>(CCRANDOM_0_1() * grid);

	} while (is_in_box(result, topLeft, rightBottom));

	return result;
}

// 返回目标的左下方向的半格子的随机坐标
inline iVec2 get_worker_target( b2Vec2 const& centerPos, int outRadius, int innerRadius )
{
	iVec2 result = half_title_covert_t::pos_to_index(centerPos);
	
	// innerRadius 为占用大标准格子数, 需要
	// innerRadius = innerRadius * 2 / 2
	result.y += innerRadius;
	int range = static_cast<int>((outRadius * 2) * CCRANDOM_0_1());
	
	result.x -= outRadius;
	result.x += range;

	return result;
}


inline iVec2 get_build_door( b2Vec2 const& centerPos, int innerRadius )
{
	iVec2 result = half_title_covert_t::pos_to_index(centerPos);
	
	// innerRadius 为占用大标准格子数, 需要
	// innerRadius = innerRadius * 2 / 2
	result.y += innerRadius;
	
	return result;
}

inline int get_dir_index( b2Vec2 const &dir ) 
{
	int result = 0;

	if (dir.x>0.f)
	{
		// 1, 0, 7, 6, 右边象限
		if (dir.y>0.f)
		{
			// 1, 0, 右上角
			b2Vec2 s(1.f, 1.f);
			result = b2Cross(s, dir)>0.f? 1: 0;

		}
		else
		{
			// 7, 6 右下角
			b2Vec2 s(1.f, -1.f);
			result = b2Cross(s, dir)>0.f? 7: 6;

		}
	}
	else
	{
		// 2, 3, 4, 5 左边象限
		if (dir.y>0.f)
		{
			// 2, 3 左上角
			b2Vec2 s(-1.f, 1.f);
			result = b2Cross(s, dir)>0.f? 3: 2;
		}
		else
		{
			// 4, 5 左下角
			b2Vec2 s(-1.f, -1.f);
			result = b2Cross(s, dir)>0.f? 5: 4;

		}

	}

	return result;
}

// 朝向中心点
inline iVec2 dir_quad_title_random_index(b2Vec2 const& dir, int outRadius)
{	
	int r = get_dir_index(dir);
	r += 1;
	if (r>7) {
		r=0;
	}
	
	int leftS = 0;
	int rightS = outRadius ;
	
	int topS = 0;
	int bottomS = outRadius;

//	if (r==0 || r==1)
//	{
//		leftS = outRadius/2;		
//		bottomS = outRadius/2;
//	}
//	else if (r==2 || r==3)
//	{
//		rightS = outRadius/2;
//		bottomS = outRadius/2;		
//	}
//	else if (r==4 || r==5)
//	{	
//		topS = outRadius/2;
//		rightS = outRadius/2;
//	}
//	else
//	{
//		leftS = outRadius/2;
//		topS = outRadius /2;
//	}	
	if (r==0 || r==7)
	{
		leftS = outRadius-2;
	}
	else if (r==1 || r==2)
	{
		bottomS = 2;
	}
	else if (r==3 || r==4)
	{
		rightS = 2;
	}
	else
	{
		topS = outRadius-2;
	}
	
	// 中心右下一格的索引
	int center = outRadius /2;
	
	int innerRadius = (outRadius - 4) / 2;
	int topLeft = center - innerRadius;
	int rightBottom = center + innerRadius - 1;
	

	iVec2 result;
	
	do 
	{
		result.x = static_cast<int>(CCRANDOM_0_1() * outRadius);
		result.y = static_cast<int>(CCRANDOM_0_1() * outRadius);
		
		if (!is_in_box(result, topLeft, rightBottom)
			&& (leftS<=result.x && result.x<rightS)
			&& (topS<=result.y && result.y<bottomS))
		{
			break;
		}
		
	} while (true);
	
	return result;
}

//inline iVec2 dir_quad_title_random_index(b2Vec2 const& dir, int outRadius, int innerRadius)
//{
//	// 必须是偶数
//	int const grid_num_per_title = 4;
//
//	int r = get_dir_index(dir);
//
//	int leftS = 0;
//	int rightS = outRadius * grid_num_per_title;
//
//	int topS = 0;
//	int bottomS = outRadius * grid_num_per_title;
//
//	int range_4 = 0;
//	if (r==0 || r==7)
//	{
//		range_4 = 0;
//
//		rightS = rightS /2;
//	}
//	if (r==1 || r==2)
//	{
//		range_4 = 1;
//		topS = bottomS /2;
//	}
//	else if (r==3 || r==4)
//	{
//		range_4 = 2;
//		leftS = rightS / 2;
//	}
//	else
//	{
//		range_4 = 3;
//		bottomS = bottomS /2;
//	}
//
//	// 中心右下一格的索引
//	int center = outRadius * (grid_num_per_title / 2);
//
//	int topLeft = center - innerRadius * 2;
//	int rightBottom = center + innerRadius * 2-1;
//
//	int grid = outRadius * grid_num_per_title;
//
//	iVec2 result;
//
//	do 
//	{
//		result.x = static_cast<int>(CCRANDOM_0_1() * grid);
//		result.y = static_cast<int>(CCRANDOM_0_1() * grid);
//
//	} while (is_in_box(result, topLeft, rightBottom)
//		&& (leftS<=result.x && result.x<rightS)
//		&& (topS<=result.y && result.y<bottomS) );
//	
//	return result;
//}


class Box45
{
public:
	
	Box45(b2Vec2 const& centerPos, float radius )
    : m_centerPos(centerPos), m_radius(radius)
	{
		
	}
	
    
	bool is_container( b2Vec2  pos )
	{
		float height = m_radius/sqrtf(5.f);
		float width = height * 2.f;
		
		b2Vec2 a(0.f, height);
		b2Vec2 b(-width, 0.f);
		b2Vec2 c(0.f, -height);
		b2Vec2 d(width, 0.f);
		
		
		//逆时针
		b2Vec2 ba(-width, -height);
		b2Vec2 cb(width, -height);
		b2Vec2 dc(width, height);
		b2Vec2 ad(-width, height);
		
		pos -= m_centerPos;
		
		if (b2Cross(ba, pos-a ) < 0.f) {
			return false;
		}
        
		if (b2Cross(cb, pos-b) < 0.f) {
			return false;
		}
		
		if (b2Cross(dc, pos-c ) < 0.f) {
			return false;
		}
		
		if (b2Cross(ad, pos-d ) < 0.f) {
			return false;
		}
		
		return true;
	}
	
	
private:
	b2Vec2 const m_centerPos;
	float const m_radius;
};

#endif // some_tool_h__
