#include "GLES_Render.h"

bool BaseDrawCircle::init(CCPoint _center, float _radius, unsigned int _segments)
{
    if (BaseDraw::init()) {
        circle_center = _center;
		circle_radius = _radius;
        circle_segments = _segments;
    }
    return true;
}

CCNode* BaseDrawCircle::DrawCircle(CCPoint _center, float _radius, unsigned int _segments)
{
    BaseDrawCircle* pRet = new BaseDrawCircle();
	if( pRet->init(_center,_radius,_segments))
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

void BaseDrawCircle::draw(void)
{
    CCNode::draw();
   
	BaseDraw_ResetGlValue();
    ccDrawCircle( circle_center, circle_radius, 0, circle_segments, false);
	BaseDraw_ResetGlValue();
}