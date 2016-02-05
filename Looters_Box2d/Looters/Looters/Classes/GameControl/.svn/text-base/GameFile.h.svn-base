/***************************************************************
 author:    wangning
 write time: 2012.3.22
 function: 配置文件管理
 ***************************************************************/
#ifndef Looters_GameFile_h
#define Looters_GameFile_h
#pragma once 
#include "cocos2d.h"
#include "GameData.h"
#include "tinyxml.h"
#include <iostream>   
#include <string>   
#include<fstream>
#include<sstream>
#include<strstream>

using namespace cocos2d;
using namespace std;

#define  VERSIONINFO "versionInfo"
#define  LANDSERVER "landServer"

class GameFile
{
public:
	GameFile();
	~GameFile();
    
public:
	bool Init( void );
    
	static GameFile* GetGameFileHandle( void );
	static void ReleaseGameFile( void );
    
	string GetLandServerIP( void );
	int GetLandServerPort( void );
	string GetVersionCode( void );
    
private:
    // BaseConfig解析 (游戏基础的配置相关)
    CCDictionary *baseConfigDic;
    
public:
    bool readCSV_buildlevel();
    bool readCSV_characters();
    bool readCSV_attacks();
    bool readCSV_missles();
    bool readCSV_spells();
    bool readCSV_texts();
    bool readCSV_animations();
    bool readCSV_npclevels();
    bool readCSV_townhalllevels();
    bool readCSV_obstacles();
    bool readCSV_effects();
    bool readCSV_experiencelevels();
    
    
    // shop数据
    bool readCSV_shields();
    bool readCSV_resource_packs();
private:
    const char* NodeGetText(TiXmlElement *element);
};

#endif
