#include "GLES_Render.h"

bool BloodDraw::init(float _startPoint, float _endPoint, float _lineWidth,CCPoint _pos)
{
    if (BaseDraw::init()) {
        line_start = _startPoint;
		line_end = _endPoint;
		line_width = _lineWidth;
        pos  = _pos;
    }
    return true;
}

CCNode* BloodDraw::DrawLine(float _startPoint, float _endPoint, float _lineWidth,CCPoint _pos)
{
    BloodDraw* pRet = new BloodDraw();
	if( pRet->init(_startPoint,_endPoint,_lineWidth,_pos))
	{
		pRet->autorelease();
	}
	else
	{
		delete pRet;
		pRet = NULL;
	}
	return pRet;
}

void BloodDraw::setData(float _startPoint, float _endPoint, float _lineWidth,CCPoint _pos)
{
    line_start = _startPoint;
    line_end = _endPoint;
    line_width = _lineWidth;
    pos  = _pos;
}

void BloodDraw::draw(void)
{
    CCNode::draw();
    glColorMask(1.0, 1.0, 1.0, 1.0);
    glLineWidth(line_width);
    ccDrawLine( ccp(line_start,pos.y), ccp(line_end,pos.y));
    glLineWidth(1);
    glColorMask(1.0, 1.0, 1.0, 1.0);
}