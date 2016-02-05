#include "Obstacle.h"
#include "GameData.h"

Obstacle::Obstacle()
{
    
}
Obstacle::~Obstacle()
{
    
}

Obstacle* Obstacle::create(int uuid,int ID)
{
    Obstacle * pRet = new Obstacle();
    if (pRet->init(uuid,ID)) {
        pRet->autorelease();  
    }else {
        delete pRet;
		pRet = NULL;
    }
	return pRet;
}

bool Obstacle::init(int uuid,int ID)
{
    const ObstaclesData* data = GameData::GetDataFromBaseObstacleData(ID);
    setuuID(uuid);
    setID(ID);
    setTypeID(data->TypeID);
    setName(data->Name);
    
    m_Passable = data->Passable;
    m_Width = data->Width;
    m_Height = data->Height;
    
    return true;
}

bool Obstacle::isPassable()
{
    return m_Passable;
}

int Obstacle::getWidth()
{
    return m_Width;
}

int Obstacle::getHeight()
{
    return m_Height;
}
