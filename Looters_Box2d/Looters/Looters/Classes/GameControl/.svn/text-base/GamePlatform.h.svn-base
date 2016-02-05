/***********************************************
 author: wangning
 write time: 2012.10.23
 function: 关于平台，游戏中关于平台方面的设置可以写在这里
 ************************************************/

#ifndef Looters_GamePlatform_h
#define Looters_GamePlatform_h
#pragma once
#include "cocos2d.h"
using namespace cocos2d;

#define EXPLOIT_PIXELS_W 480 //开发分辨率x
#define EXPLOIT_PIXELS_H 320 //开发分辨率y

#define MODEL_PIXELS_W 960 //模拟机型分辨率
#define MODEL_PIXELS_H 640 //模拟机型分辨率



class GamePlatform
{
public:
	//屏幕数据
	static CCSize GetWinSizeInPixels( void );
	static CCSize GetScreenSize( void );
	static float GetScreenScaleX( void );
	static float GetScreenScaleY( void );
	
	
	//节点缩放
	static void NodePiselsScale( CCNode* node );
	//节点位置
	static void NodePiselsPoint( CCNode* node );
	//坐标适配
	static CCPoint TransitionPoint( CCPoint point );
	//size转换
	static CCSize TransitionSize( CCSize size );
	//rect转换
	static CCRect TransitionRect( CCRect rect );
	//float转换 
	static float TransitionFloat( float f );
	//得到MAC码
	static std::string GetMACNum( void );
public:
	static float m_fScreenScale;//屏幕的缩放比例
	
	
	
public:

	static int const S_MapGridNum = 44;

	static int const S_BuildingBaseGridWidth = 32;
	static int const S_BuildingBaseGridHeight = 16;


	static int const S_MapWidth = S_MapGridNum * S_BuildingBaseGridWidth;
	static int const S_MapHeight = S_MapGridNum * S_BuildingBaseGridHeight;
	
	// 可建筑地形对地形格数留边数
	static int const S_BuildingLeftGrid = 4;
    

	static int GetMAPGLWIDTH( void );
	static int GetMAPGLHEIGHT( void );
    static float GetBUILDINTBASEGRID_EDGE_LEN( void );	
	
};

//缩放场景
#define GAME_SCENE_SCALE(P) GamePlatform::NodePiselsScale(P)
//定位场景
#define GAME_SCENE_POINT(P) GamePlatform::NodePiselsPoint(P)
//坐标转换
#define GAME_POINT_TRANSFORM(P) GamePlatform::TransitionPoint(P)
//size转换
#define GAME_SIZE_TRANSFORM(S) GamePlatform::TransitionSize(S)
//rect转换
#define GAME_RECT_TRANSFORM(R) GamePlatform::TransitionRect(R)
//float转换
#define GAME_FLOAT_TRANSFORM(F) GamePlatform::TransitionFloat(F)



#define MAPWIDTHMAX GamePlatform::S_MapWidth  //地图数据的宽
#define MAPHEIGHTMAX GamePlatform::S_MapHeight //地图数据的高


#define MAPGRIDWIDTH GamePlatform::S_MapGridNum  //地图宽格子块数
#define MAPGRIDHEIGHT GamePlatform::S_MapGridNum //地图高格子块数


#define BUILDINGBASEGRID_WIDTH GamePlatform::S_BuildingBaseGridWidth  //基本格子的宽
#define BUILDINTBASEGRID_HEIGHT GamePlatform::S_BuildingBaseGridHeight //基本格子的高

#define MAPGLWIDTH  GamePlatform::GetMAPGLWIDTH()  // 地图的宽
#define MAPGLHEIGHT  GamePlatform::GetMAPGLHEIGHT() // 地图的高

#define BUILDINTBASEGRID_EDGE_LEN GamePlatform::GetBUILDINTBASEGRID_EDGE_LEN() // 一单位地形块的边长


const int TITLE_NUM_X2 = GamePlatform::S_MapGridNum * 2;

const int TITLE_WIDTH_HALF = GamePlatform::S_BuildingBaseGridWidth / 2;

const int TITLE_HEIGHT_HALF = GamePlatform::S_BuildingBaseGridHeight / 2;

#endif
