#include "CentralData.h"
#include "GameData.h"

CentralData::CentralData()
{
    m_MatchPlayer = new MatchPlayer();
    m_Central_UserData = new Central_UserData();
    m_AttackerSoldiersAndSpell = new vector<AttackerSoldiersAndSpell*>;
    m_BuildableSoldiers = new vector<BuildableSoldiers*>;
    m_BuildableMagic = new vector<BuildableMagic*>;
}

CentralData::~CentralData()
{
	CleanData();
    delete m_MatchPlayer;
    delete m_Central_UserData;
    delete m_AttackerSoldiersAndSpell;
    delete m_BuildableMagic;
}

CentralData* CentralData::Load( void )
{
	CentralData* cd = new CentralData();
	if (cd) {
        cd->autorelease();
        cd->retain();
    }
	return cd;
}

void CentralData::CleanData( void )
{
	if( m_MatchPlayer->nickName )
		delete m_MatchPlayer->nickName;
    if( m_MatchPlayer->gameCenterID )
		delete m_MatchPlayer->gameCenterID;
    
	memset( m_MatchPlayer,0,sizeof(MatchPlayer) );
    
    
    if (m_Central_UserData->nick_name)
        delete m_Central_UserData->nick_name;
    if (m_Central_UserData->battleInfor) {
        if (m_Central_UserData->battleInfor->attack_time) {
            delete m_Central_UserData->battleInfor->attack_time;
        }
        if (m_Central_UserData->battleInfor->attacker_nick_name) {
            delete m_Central_UserData->battleInfor->attacker_nick_name;
        }
        memset(m_Central_UserData->battleInfor, 0, sizeof(BattleInforTip));
    }
    delete m_Central_UserData->battleInfor;
    
    memset( m_Central_UserData, 0, sizeof(Central_UserData));
    
    
    for( int i = 0; i < (int)m_BuildableMagic->size(); i++ )
	{
		delete m_BuildableMagic->at(i);
	}
	m_BuildableMagic->clear();
    
    for( int i = 0; i < (int)m_AttackerSoldiersAndSpell->size(); i++ )
	{
		delete m_AttackerSoldiersAndSpell->at(i);
	}
	m_AttackerSoldiersAndSpell->clear();

    
    for( int i = 0; i < (int)m_BuildableSoldiers->size(); i++ )
	{
		delete m_BuildableSoldiers->at(i);
	}
	m_BuildableSoldiers->clear();


    m_M_UserMapData.clear();
    m_BattleInfoList.clear();
    m_buildDestoryStatus.clear();
}

void CentralData::CleanBattleData(void)
{
    if( m_MatchPlayer->nickName )
		delete m_MatchPlayer->nickName;
    if( m_MatchPlayer->gameCenterID )
		delete m_MatchPlayer->gameCenterID;
    
	memset( m_MatchPlayer,0,sizeof(MatchPlayer) );
    
    for( int i = 0; i < (int)m_AttackerSoldiersAndSpell->size(); i++ )
	{
		delete m_AttackerSoldiersAndSpell->at(i);
	}
	m_AttackerSoldiersAndSpell->clear();
    
    m_M_UserMapData.clear();
}

CentralData::BuildableSoldiers* CentralData::getBuildableSoldiers(int _type)
{
    for( int i = 0; i < (int)m_BuildableSoldiers->size(); i++ )
	{
        if (m_BuildableSoldiers->at(i)->type == _type)
        {
            return m_BuildableSoldiers->at(i);
        }

	}
    return NULL;
}
CentralData::BuildableMagic* CentralData::getBuildableMagic(int _type)
{
    for( int i = 0; i < (int)m_BuildableMagic->size(); i++ )
	{
        if (m_BuildableMagic->at(i)->type == _type)
        {
            return m_BuildableMagic->at(i);
        }
        
	}
    return NULL;
}


void CentralData::AddM_UserMapData( int uuid, M_UserMapData & mapData )
{
    m_M_UserMapData.insert(pair<int,M_UserMapData>(uuid,mapData));
}

CentralData::M_UserMapData* CentralData::GetM_UserMapData(int uuid)
{
    CentralData::userMapData_t::iterator iter = m_M_UserMapData.find( uuid );
	if( iter != m_M_UserMapData.end() )
	{
		return &(iter->second);
	}
	return 0;
}

void CentralData::AddBuildDestoryStatusData( int uuid, BuildDestoryStatusData & buildDestoryStatusData )
{
    m_buildDestoryStatus.insert(pair<int,BuildDestoryStatusData>(uuid,buildDestoryStatusData));
}

CentralData::BuildDestoryStatusData* CentralData::GetBuildDestoryStatusData(int uuid)
{
    CentralData::buildDestoryStatus_t::iterator iter = m_buildDestoryStatus.find( uuid );
	if( iter != m_buildDestoryStatus.end() )
	{
		return &(iter->second);
	}
	return 0;
}



