#include "GLES_Render.h"

bool BaseDrawRect::init(CCPoint _bottomLeftPoint, float _width, float _height)
{
    if (BaseDraw::init()) {
        rect_bottom_left = _bottomLeftPoint;
		rect_width = _width;
		rect_height = _height;
    }
    return true;
}

CCNode* BaseDrawRect::DrawDrawRect(CCPoint _bottomLeftPoint, float _width, float _height)
{
    BaseDrawRect* pRet = new BaseDrawRect();
	if( pRet->init(_bottomLeftPoint,_width,_height))
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

void BaseDrawRect::draw(void)
{
    CCNode::draw();
    CCPoint Verts[4] =
	{
		ccp(rect_bottom_left.x, rect_bottom_left.y),
		ccp(rect_bottom_left.x + rect_width, rect_bottom_left.y),
		ccp(rect_bottom_left.x + rect_width, rect_bottom_left.y + rect_height),
		ccp(rect_bottom_left.x, rect_bottom_left.y+ rect_height)
	};
	
	BaseDraw_ResetGlValue();
    ccDrawLine( Verts[0], Verts[1] );
    ccDrawLine( Verts[1], Verts[2] );
    ccDrawLine( Verts[2], Verts[3] );
    ccDrawLine( Verts[3], Verts[0] );
	BaseDraw_ResetGlValue();
}