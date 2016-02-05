#include "GLES_Render.h"

bool BaseDrawPoint::init(CCPoint _pointPosition,float _pointSize)
{
    if (BaseDraw::init()) {
        point_postion = _pointPosition;
		point_size = _pointSize;
    }
    return true;
}

CCNode* BaseDrawPoint::DrawPoint(CCPoint _pointPosition,float _pointSize)
{
    BaseDrawPoint* pRet = new BaseDrawPoint();
	if( pRet->init(_pointPosition,_pointSize))
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

void BaseDrawPoint::draw(void)
{
    CCNode::draw();
    
    CCPoint Verts[1] =
	{
		point_postion
	};
	
	BaseDraw_ResetGlValue();
    ccPointSize(point_size);
    ccDrawPoint( Verts[0] );
	BaseDraw_ResetGlValue();
}