#include "BuildingManager.h"
#include "GameControl.h"

BuildingManager::BuildingManager(void)
{
}

BuildingManager::~BuildingManager(void)
{
}

BuildingBase* BuildingManager::JudgeBuildingType(int unitID)
{
	int buildingType=0;
    buildingType = BUILDINGTYPE_NOGAIN;
    
	Unit* buildtmp=NULL;
    if (buildingType == BUILDINGTYPE_NOGAIN)
    {
        buildtmp=BuildingBase::BuildWithData(unitID);
    }
	return (BuildingBase*)buildtmp;
}

void BuildingManager::CloseShop()
{

}