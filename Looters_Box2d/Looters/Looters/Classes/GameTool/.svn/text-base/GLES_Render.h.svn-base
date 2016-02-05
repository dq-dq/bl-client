#ifndef Looters_GLES_Render_h
#define Looters_GLES_Render_h
#include "cocos2d.h"
using namespace cocos2d;


// 恢复 gl 设置到默认
static void BaseDraw_ResetGlValue(void)
{
	glLineWidth(1);
    glColorMask(1.0, 1.0, 1.0, 1.0);
    ccPointSize(1);
}

class BaseDraw: public CCNode {

public:
	// 形状显示的颜色数据
	float color_r;		 //［0.0, 1.0］ 之间
	float color_g;
	float color_b;
	float color_alpha;
public:
    bool init();
};

class BaseDrawPoint: public BaseDraw {
public:	
	CCPoint	point_postion;
	float	point_size;
public:
    bool init(CCPoint _pointPosition,float _pointSize);
    static CCNode* DrawPoint(CCPoint _pointPosition,float _pointSize);
    
    virtual void draw(void);
};

class BaseDrawLine:public BaseDraw {
public:
	CCPoint line_start;
	CCPoint	line_end;
	
	float	line_width;
public:
    bool init(CCPoint _startPoint, CCPoint _endPoint, float _lineWidth);
    static CCNode* DrawLine(CCPoint _startPoint, CCPoint _endPoint, float _lineWidth);
    
    virtual void draw(void);
};


class BaseDrawRect:public BaseDraw {
public:
	CCPoint rect_bottom_left;		// 左下角点坐标
	float	rect_width;
	float	rect_height;
    
public:
    bool init(CCPoint _bottomLeftPoint, float _width, float _height);
	static CCNode* DrawDrawRect(CCPoint _bottomLeftPoint, float _width, float _height);
    
    virtual void draw(void);
};


class BaseDrawCircle:public BaseDraw {
public:
	CCPoint circle_center;		// 圆心
	float	circle_radius;		// 半径	
    unsigned int circle_segments; // 密度
public:
    bool init(CCPoint _center, float _radius, unsigned int _segments);
	static CCNode* DrawCircle(CCPoint _center, float _radius, unsigned int _segments);
    
    virtual void draw(void);
};

class BloodDraw : public BaseDraw {
    float line_start;
	float	line_end;
	CCPoint pos;
	float	line_width;
public:
    bool init(float _startPoint, float _endPoint, float _lineWidth,CCPoint _pos);
    static CCNode* DrawLine(float _startPoint, float _endPoint, float _lineWidth,CCPoint _pos);
    void setData(float _startPoint, float _endPoint, float _lineWidth,CCPoint _pos);
    virtual void draw(void);
};
#endif
