#include <iostream>
#include "GamePlatform.h"
#include "ccMacros.h"
#include "CCPointExtension.h"

float GamePlatform::m_fScreenScale = 1.0f;




CCSize GamePlatform::GetScreenSize( void )
{
	return CCSizeMake( CCDirector::sharedDirector()->getWinSize().width, CCDirector::sharedDirector()->getWinSize().height );
}

CCSize GamePlatform::GetWinSizeInPixels( void )
{
	return CCSizeMake( CCDirector::sharedDirector()->getWinSizeInPixels().width, CCDirector::sharedDirector()->getWinSizeInPixels().height );
}

float GamePlatform::GetScreenScaleX( void )
{
	return GamePlatform::GetScreenSize().width / (float)EXPLOIT_PIXELS_W;
}

float GamePlatform::GetScreenScaleY( void )
{
	return GamePlatform::GetScreenSize().height / (float)EXPLOIT_PIXELS_H;
}

std::string GamePlatform::GetMACNum( void )
{
	return "fjdskjalfs";
}

void GamePlatform::NodePiselsScale( CCNode* node )
{
	node->setScale(GamePlatform::m_fScreenScale);
}

void GamePlatform::NodePiselsPoint( CCNode* node )
{
	CCPoint point;
//	point.x = (CCDirector::sharedDirector()->getDisplaySizeInPixels().width - 
//               GameResources::m_sizeUseResources.width*GamePlatform::m_fScreenScale)/2;
//	point.y = (CCDirector::sharedDirector()->getDisplaySizeInPixels().height - 
//               GameResources::m_sizeUseResources.height*GamePlatform::m_fScreenScale)/2;
	node->setPosition( TransitionPoint(point) );
}


CCPoint GamePlatform::TransitionPoint( CCPoint point )
{
	CCPoint newPoint = point;
	if( CC_CONTENT_SCALE_FACTOR() != 1 )
	{
		newPoint = ccpMult(point, 1/CC_CONTENT_SCALE_FACTOR());
	}
	return newPoint;
}

CCSize GamePlatform::TransitionSize( CCSize size )
{
	return CCSizeMake( size.width/CC_CONTENT_SCALE_FACTOR(), size.height/CC_CONTENT_SCALE_FACTOR());
}

CCRect GamePlatform::TransitionRect( CCRect rect )
{
	return CC_RECT_PIXELS_TO_POINTS( rect );
}

float GamePlatform::TransitionFloat(float f)
{
	return f/CC_CONTENT_SCALE_FACTOR();
}


int GamePlatform::GetMAPGLWIDTH( void )
{
    return 1664;
}
int GamePlatform::GetMAPGLHEIGHT( void )
{
	return 1024;
}

float GamePlatform::GetBUILDINTBASEGRID_EDGE_LEN( void )
{
    return 17.888544f;
}
























