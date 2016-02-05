#include "GLES_Render.h"

bool BaseDrawLine::init(CCPoint _startPoint, CCPoint _endPoint, float _lineWidth)
{
    if (BaseDraw::init()) {
        line_start = _startPoint;
		line_end = _endPoint;
		line_width = _lineWidth;
    }
    return true;
}

CCNode* BaseDrawLine::DrawLine(CCPoint _startPoint, CCPoint _endPoint, float _lineWidth)
{
    BaseDrawLine* pRet = new BaseDrawLine();
	if( pRet->init(_startPoint,_endPoint,_lineWidth))
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

void BaseDrawLine::draw(void)
{
    CCNode::draw();
    CCPoint Verts[2] =
	{
		line_start,
		line_end
	};
    // 绘制一条直线
//	BaseDraw_ResetGlValue();
//	glLineWidth( line_width );
//	glEnable(GL_LINES);
    ccDrawLine( Verts[0], Verts[1]);
//	BaseDraw_ResetGlValue();
}