#ifndef iVec2_h__
#define iVec2_h__

struct iVec2
{
	/// Default constructor does nothing (for performance).
	iVec2() {}

	/// Construct using coordinates.
	iVec2(int x, int y) : x(x), y(y) {}

	/// Set this vector to all zeros.
	void SetZero() { x = 0; y = 0; }

	/// Set this vector to some specified coordinates.
	void Set(int x_, int y_) { x = x_; y = y_; }

	/// Negate this vector.
	iVec2 operator -() const { iVec2 v; v.Set(-x, -y); return v; }

	/// Add a vector to this vector.
	void operator += (const iVec2& v)
	{
		x += v.x; y += v.y;
	}

	/// Subtract a vector from this vector.
	void operator -= (const iVec2& v)
	{
		x -= v.x; y -= v.y;
	}

	int x, y;
};

inline bool operator == (iVec2 const& lhs, iVec2 const& rhs)
{
	return lhs.x==rhs.x && lhs.y==rhs.y;
}

inline iVec2 operator- (iVec2 const& lhs, iVec2 const& rhs)
{
	return iVec2(lhs.x-rhs.x, lhs.y-rhs.y);
}

inline iVec2 operator+ (iVec2 const& lhs, iVec2 const& rhs)
{
	return iVec2(lhs.x+rhs.x, lhs.y+rhs.y);
}

class iBox2
{
public:
	iBox2(iVec2 const& p1, iVec2 const& p2)
		: m_min(min(p1.x, p2.x), min(p1.y, p2.y))
		, m_max(max(p1.x, p2.x), max(p1.y, p2.y)) 
	{
		
	}

	bool IsContains( iVec2 const& p) const
	{
		return m_min.x <=p.x && p.x<=m_max.x && m_min.y<=p.y && p.y<=m_max.y;
	}

private:
	iVec2 m_min;
	iVec2 m_max;
};


#endif // iVec2_h__

