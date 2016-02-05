#include "CentralLayer.h"
#include "Until.h"
#include "NavGraph.h"

BuildingBase* CentralLayer::SelectBuildingFromSubstrate( CCPoint point )
{
	BuildingBase* pbuilding = NULL;

    CCPoint mapIndex = this->getMapIndexByTouchPoint(point);
    MapGridLogicInfo info;
    unsigned int gridIndex = mapIndex.x*MAPGRIDHEIGHT+mapIndex.y;
    if(this->GetMapGridLogicInfo(gridIndex,&info))
    {
        if (info.bIsBiulded) {
            CCLog("我点中你了!!!");
            pbuilding = (BuildingBase *)info.pBuilding;
            return pbuilding;
        }
    }
	return pbuilding;
}

void CentralLayer::AddMapGridLogicInfo(unsigned int index,MapGridLogicInfo* info)
{
	MapGridLogicInfo* data = new MapGridLogicInfo;
	memcpy( data, info, sizeof(MapGridLogicInfo) );
	m_mapMapGridLogicInfo->insert(pair<unsigned int,MapGridLogicInfo*>(index,data));
}

bool CentralLayer::GetMapGridLogicInfo(unsigned int index,MapGridLogicInfo* info)
{
	map<unsigned int,MapGridLogicInfo*>::iterator iter = m_mapMapGridLogicInfo->find( index );
	if( iter != m_mapMapGridLogicInfo->end() )
	{
		memcpy( info, iter->second, sizeof(MapGridLogicInfo) );
		return true;
	}
	return false;
}

void CentralLayer::UpdataMapGridLogicInfo( unsigned int index, MapGridLogicInfo* info )
{
	map<unsigned int,MapGridLogicInfo*>::iterator iter = m_mapMapGridLogicInfo->find(index);
	if( iter != m_mapMapGridLogicInfo->end() )//找到uuID  替换
	{
		iter->second->bIsBiulded = info->bIsBiulded;
		iter->second->uuid = info->uuid;
		iter->second->pBuilding = info->pBuilding;
	}
}

CCPoint CentralLayer::positionForIsoAt(const CCPoint& pos) const
{
	CCPoint xy = CCPointMake(BUILDINGBASEGRID_WIDTH /2 * (MAPGRIDWIDTH + pos.x - pos.y - 1),
							 BUILDINTBASEGRID_HEIGHT /2 * ((MAPGRIDHEIGHT * 2 - pos.x - pos.y) - 2));
	return xy;
}



CCPoint CentralLayer::touchInGrid(CCPoint mapIndex,CCPoint pointMap)
{
	CCPoint newIndex;
	// 只考虑右下角
	if (mapIndex.x == 0) {
		CCPoint rbIndex = ccp(mapIndex.x+1,mapIndex.y);
		CCPoint xy = this->positionForIsoAt(mapIndex); // 右下角点
		CCPoint   tr[3];
		tr[0] = ccp(xy.x+BUILDINGBASEGRID_WIDTH/2,xy.y);
		tr[1] = ccp(xy.x+BUILDINGBASEGRID_WIDTH,xy.y);
		tr[2] = ccp(xy.x+BUILDINGBASEGRID_WIDTH,xy.y+BUILDINTBASEGRID_HEIGHT/2);
		if (Until::inside(tr, pointMap)) {
			//                    CCLog("右下角");
			return  rbIndex;
		}
	}
	// 只考虑左上角
	else if (mapIndex.x == MAPGRIDWIDTH-1) {
		CCPoint ltIndex = ccp(mapIndex.x-1,mapIndex.y);
		CCPoint xy = this->positionForIsoAt(mapIndex); // 左上角点
		CCPoint   tr[3];
		tr[0] = ccp(xy.x,xy.y+BUILDINTBASEGRID_HEIGHT/2);
		tr[1] = ccp(xy.x,xy.y+BUILDINTBASEGRID_HEIGHT);
		tr[2] = ccp(xy.x+BUILDINGBASEGRID_WIDTH/2,xy.y+BUILDINTBASEGRID_HEIGHT);
		if (Until::inside(tr, pointMap)) {
			//                    CCLog("左上角");
			return  ltIndex;
		}
	}
	// 只考虑左下角
	else if (mapIndex.y == 0) {
		CCPoint lbIndex = ccp(mapIndex.x,mapIndex.y+1);
		CCPoint xy = this->positionForIsoAt(mapIndex); // 左下角点
		CCPoint   tr[3];
		tr[0] = ccp(xy.x,xy.y);
		tr[1] = ccp(xy.x,xy.y+BUILDINTBASEGRID_HEIGHT/2);
		tr[2] = ccp(xy.x+BUILDINGBASEGRID_WIDTH/2,xy.y);
		if (Until::inside(tr, pointMap)) {
			//                    CCLog("左下角");
			return  lbIndex;
		}
	}
	// 只考虑右上角
	else if (mapIndex.y == MAPGRIDHEIGHT-1) {
		CCPoint rtIndex = ccp(mapIndex.x,mapIndex.y-1);
		CCPoint xy = this->positionForIsoAt(mapIndex); // 左下角点
		CCPoint   tr[3];
		tr[0] = ccp(xy.x+BUILDINGBASEGRID_WIDTH/2,xy.y+BUILDINTBASEGRID_HEIGHT);
		tr[1] = ccp(xy.x+BUILDINGBASEGRID_WIDTH,xy.y+BUILDINTBASEGRID_HEIGHT);
		tr[2] = ccp(xy.x+BUILDINGBASEGRID_WIDTH,xy.y+BUILDINTBASEGRID_HEIGHT/2);
		if (Until::inside(tr, pointMap)) {
			//                    CCLog("右上角");
			return   rtIndex;
		}
	}
	else{
		// 
		{
			CCPoint rbIndex = ccp(mapIndex.x+1,mapIndex.y);
			CCPoint xy = this->positionForIsoAt(mapIndex); // 右下角点
			CCPoint   tr[3];
			tr[0] = ccp(xy.x+BUILDINGBASEGRID_WIDTH/2,xy.y);
			tr[1] = ccp(xy.x+BUILDINGBASEGRID_WIDTH,xy.y);
			tr[2] = ccp(xy.x+BUILDINGBASEGRID_WIDTH,xy.y+BUILDINTBASEGRID_HEIGHT/2);
			if (Until::inside(tr, pointMap)) {
				//            CCLog("右下角");
				return  rbIndex;
			}
		}
		// 
		{
			CCPoint ltIndex = ccp(mapIndex.x-1,mapIndex.y);
			CCPoint xy = this->positionForIsoAt(mapIndex); // 左上角点
			CCPoint   tr[3];
			tr[0] = ccp(xy.x,xy.y+BUILDINTBASEGRID_HEIGHT/2);
			tr[1] = ccp(xy.x,xy.y+BUILDINTBASEGRID_HEIGHT);
			tr[2] = ccp(xy.x+BUILDINGBASEGRID_WIDTH/2,xy.y+BUILDINTBASEGRID_HEIGHT);
			if (Until::inside(tr, pointMap)) {
				//            CCLog("左上角");
				return  ltIndex;
			}
		}
		// 
		{
			CCPoint lbIndex = ccp(mapIndex.x,mapIndex.y+1);
			CCPoint xy = this->positionForIsoAt(mapIndex); // 左下角点
			CCPoint   tr[3];
			tr[0] = ccp(xy.x,xy.y);
			tr[1] = ccp(xy.x,xy.y+BUILDINTBASEGRID_HEIGHT/2);
			tr[2] = ccp(xy.x+BUILDINGBASEGRID_WIDTH/2,xy.y);
			if (Until::inside(tr, pointMap)) {
				//            CCLog("左下角");
				return  lbIndex;
			}
		}
		// 
		{
			CCPoint rtIndex = ccp(mapIndex.x,mapIndex.y-1);
			CCPoint xy = this->positionForIsoAt(mapIndex); // 左下角点
			CCPoint   tr[3];
			tr[0] = ccp(xy.x+BUILDINGBASEGRID_WIDTH/2,xy.y+BUILDINTBASEGRID_HEIGHT);
			tr[1] = ccp(xy.x+BUILDINGBASEGRID_WIDTH,xy.y+BUILDINTBASEGRID_HEIGHT);
			tr[2] = ccp(xy.x+BUILDINGBASEGRID_WIDTH,xy.y+BUILDINTBASEGRID_HEIGHT/2);
			if (Until::inside(tr, pointMap)) {
				//            CCLog("右上角");
				return rtIndex;
			}
		}
		
		newIndex = mapIndex;
	}

	
	return newIndex;
}

CCPoint CentralLayer::getMapIndexByTouchPoint(CCPoint touchPoint)
{	
	CCPoint result;
	CCPoint pos = m_tmxMap->convertToNodeSpace( touchPoint );
	if (pos.x <0 || pos.y<0 || pos.x>MAPWIDTHMAX || pos.y>MAPHEIGHTMAX) {
		return result;
	}
	
	result = to_CCPoint( normal_title_covert_t::pos_to_index(to_b2Vec2(pos)));
	return result;
}


void CentralLayer::MarkGridBuildInfo(CCPoint lBIndex,int row,unsigned int uuid,void *building)
{
	int startRow = (int)lBIndex.x-(row-1);
	int startCol = (int)lBIndex.y;
	for (int i=0; i<row; i++) {
		for (int j=0; j<row; j++) {
			MapGridLogicInfo info;
			int index = (int)((startRow+i)*MAPGRIDHEIGHT+(startCol-j));
			this->GetMapGridLogicInfo(index,&info);
			info.bIsBiulded = true;
			info.pBuilding = building;
			info.uuid = uuid;
			this->UpdataMapGridLogicInfo(index, &info);
		}
	}
	
	NavGraph::sharedNavGraph()->AddUnit((Unit*)building);
//    ClearTestPoint();
//	InitTestPoint();
}

void CentralLayer::RemoveGridBuildInfo(CCPoint lBIndex,int row,unsigned int uuid,void *building)
{
	int startRow = (int)lBIndex.x-(row-1);
	int startCol = (int)lBIndex.y;
	for (int i=0; i<row; i++) {
		for (int j=0; j<row; j++) {
			MapGridLogicInfo info;
			int index = (int)((startRow+i)*MAPGRIDHEIGHT+(startCol-j));
			this->GetMapGridLogicInfo(index,&info);
			info.bIsBiulded = false;
			info.pBuilding = NULL;
			info.uuid = 0;
			this->UpdataMapGridLogicInfo(index, &info);
		}
	}
	
	NavGraph::sharedNavGraph()->DestoryUnit((Unit*)building);
//	ClearTestPoint();
//	InitTestPoint();
}
bool CentralLayer::isCanPutDownBuild(CCPoint lBIndex,int row,unsigned int uuid,void *building)
{
	bool isBuild = true;
	int startRow = (int)lBIndex.x-(row-1);
	int startCol = (int)lBIndex.y;
	for (int i=0; i<row; i++) {
		for (int j=0; j<row; j++) {
			MapGridLogicInfo info;
			int index = (int)((startRow+i)*MAPGRIDHEIGHT+(startCol-j));
			this->GetMapGridLogicInfo(index,&info);
			//已有建筑
			if (info.bIsBiulded)
			{
				//建筑不是自己本身
				if (info.uuid!=uuid)
				{
					isBuild = false;
					break;
				}
				
			}

		}
	}
	
	return isBuild;
}


bool CentralLayer::isClickBuilding( CCPoint point ,BuildingBase* build,CCPoint _buildNewMapIndex)
{
	bool isClick = false;
	CCPoint mapIndex = getMapIndexByTouchPoint(point);
	

	int l = build->GetLine();
	int r = build->GetRow();
	int mX = mapIndex.x;//
	int mY = mapIndex.y;//
	int bX = _buildNewMapIndex.x;//
	int bY = _buildNewMapIndex.y;//
	
	if (mX>bX-l&&mX<=bX&&mY>bY-r&&mY<=bY) {
		isClick = true;
	}
	
	
	return isClick;
}



int CentralLayer::getPlaceDirection(CCPoint index)
{
	CCPoint leftTop = ccp(index.x-1,index.y);
	CCPoint rightTop = ccp(index.x,index.y-1);
	CCPoint leftBottom = ccp(index.x,index.y+1);
	CCPoint rightBottom = ccp(index.x+1,index.y);
	
	MapGridLogicInfo info;
	if (this->GetMapGridLogicInfo(leftTop.x*MAPGRIDHEIGHT+leftTop.y,&info) && info.bIsBiulded) {
        if (this->GetMapGridLogicInfo(rightBottom.x*MAPGRIDHEIGHT+rightBottom.y,&info) && !info.bIsBiulded) {
            return PlaceDirection_type_RightBottom;
        }else if(this->GetMapGridLogicInfo(leftBottom.x*MAPGRIDHEIGHT+leftBottom.y,&info) && !info.bIsBiulded){
            return PlaceDirection_type_LeftBottom;
        }else if(this->GetMapGridLogicInfo(rightTop.x*MAPGRIDHEIGHT+rightTop.y,&info) && !info.bIsBiulded){
            return PlaceDirection_type_RightTop;
        }
        return PlaceDirection_type_NONE;
	}
	
	if (this->GetMapGridLogicInfo(rightBottom.x*MAPGRIDHEIGHT+rightBottom.y,&info) && info.bIsBiulded){
        if (this->GetMapGridLogicInfo(leftTop.x*MAPGRIDHEIGHT+leftTop.y,&info) && !info.bIsBiulded) {
            return PlaceDirection_type_LeftTop;
        }else if(this->GetMapGridLogicInfo(leftBottom.x*MAPGRIDHEIGHT+leftBottom.y,&info) && !info.bIsBiulded){
            return PlaceDirection_type_LeftBottom;
        }else if(this->GetMapGridLogicInfo(rightTop.x*MAPGRIDHEIGHT+rightTop.y,&info) && !info.bIsBiulded){
            return PlaceDirection_type_RightTop;
        }
        return PlaceDirection_type_NONE;
    }
	
	if (this->GetMapGridLogicInfo(leftBottom.x*MAPGRIDHEIGHT+leftBottom.y,&info) && !info.bIsBiulded) {
        if (this->GetMapGridLogicInfo(leftTop.x*MAPGRIDHEIGHT+leftTop.y,&info) && !info.bIsBiulded) {
            return PlaceDirection_type_LeftTop;
        }else if(this->GetMapGridLogicInfo(rightBottom.x*MAPGRIDHEIGHT+rightBottom.y,&info) && !info.bIsBiulded){
            return PlaceDirection_type_RightBottom;
        }else if(this->GetMapGridLogicInfo(rightTop.x*MAPGRIDHEIGHT+rightTop.y,&info) && !info.bIsBiulded){
            return PlaceDirection_type_RightTop;
        }
        return PlaceDirection_type_NONE;
	}
	
	if (this->GetMapGridLogicInfo(rightTop.x*MAPGRIDHEIGHT+rightTop.y,&info) && !info.bIsBiulded) {
        if (this->GetMapGridLogicInfo(leftTop.x*MAPGRIDHEIGHT+leftTop.y,&info) && !info.bIsBiulded) {
            return PlaceDirection_type_LeftTop;
        }else if(this->GetMapGridLogicInfo(rightBottom.x*MAPGRIDHEIGHT+rightBottom.y,&info) && !info.bIsBiulded){
            return PlaceDirection_type_RightBottom;
        }else if(this->GetMapGridLogicInfo(leftBottom.x*MAPGRIDHEIGHT+leftBottom.y,&info) && !info.bIsBiulded){
            return PlaceDirection_type_LeftBottom;
        }
        return PlaceDirection_type_NONE;

	}
	
	return PlaceDirection_type_NONE;
}

void CentralLayer::getPlaceNextIndex(int direction)
{
	switch (direction) {
		case PlaceDirection_type_NONE:
			break;
		case PlaceDirection_type_LeftTop:
			PlaceNextIndex.x = PlaceNextIndex.x - 1;
			break;
		case PlaceDirection_type_RightTop:
			PlaceNextIndex.y = PlaceNextIndex.y - 1;
			break;
		case PlaceDirection_type_RightBottom:
			PlaceNextIndex.x = PlaceNextIndex.x + 1;
			break;
		case PlaceDirection_type_LeftBottom:
			PlaceNextIndex.y = PlaceNextIndex.y + 1;
			break;
			
		default:
			break;
	}
}

void CentralLayer::ResetPlaceDirection_type(CCPoint index)
{
	CCPoint leftTop = ccp(index.x-1,index.y);
	CCPoint rightTop = ccp(index.x,index.y-1);
	CCPoint leftBottom = ccp(index.x,index.y+1);
	CCPoint rightBottom = ccp(index.x+1,index.y);
	
	MapGridLogicInfo info;
	if (this->GetMapGridLogicInfo(index.x*MAPGRIDHEIGHT+index.y,&info) && info.bIsBiulded)
	{
		BuildingBase * build = (BuildingBase*)info.pBuilding;
		if (build && build->getTypeID() != BUILDINGTYPE_WALL) {
			return;
		}else {
            ReplaceWallToBase01(build);
        }
	}
	
	if (this->GetMapGridLogicInfo(leftTop.x*MAPGRIDHEIGHT+leftTop.y,&info) && !info.bIsBiulded)
	{
		if (this->GetMapGridLogicInfo(rightTop.x*MAPGRIDHEIGHT+rightTop.y,&info) && info.bIsBiulded) {
			BuildingBase * build = (BuildingBase*)info.pBuilding;
			if (build && build->getTypeID() == BUILDINGTYPE_WALL) { // 左上没有 ＋ 右上有 是墙
				if(this->GetMapGridLogicInfo(index.x*MAPGRIDHEIGHT+index.y,&info) && info.bIsBiulded){
					build = (BuildingBase*)info.pBuilding;
					if (build && build->getTypeID() == BUILDINGTYPE_WALL) {
                        char spritename[64] = {0};
                        sprintf(spritename,"build_defense_wall_lvl%d_02",build->lv);
                        build->replaceSprite_(GAME_FILE_TRANSFORM(spritename,".png").c_str());
					}
				}
			}
		}
	}
	
	if (this->GetMapGridLogicInfo(rightTop.x*MAPGRIDHEIGHT+rightTop.y,&info) && !info.bIsBiulded) {
		if (this->GetMapGridLogicInfo(leftTop.x*MAPGRIDHEIGHT+leftTop.y,&info) && info.bIsBiulded) {
			BuildingBase * build = (BuildingBase*)info.pBuilding;
			if (build && build->getTypeID() == BUILDINGTYPE_WALL) { // 右上没有 ＋ 左上有 是墙
				// 改变当前格子的方向
				if(this->GetMapGridLogicInfo(index.x*MAPGRIDHEIGHT+index.y,&info) && info.bIsBiulded){
					build = (BuildingBase*)info.pBuilding;
					if (build && build->getTypeID() == BUILDINGTYPE_WALL) {
                        char spritename[64] = {0};
                        sprintf(spritename,"build_defense_wall_lvl%d_01",build->lv);
                        build->replaceSprite_(GAME_FILE_TRANSFORM(spritename,".png").c_str());
					}
				}
			}
		}
	}
	
	if (this->GetMapGridLogicInfo(leftTop.x*MAPGRIDHEIGHT+leftTop.y,&info) && info.bIsBiulded)
	{
		BuildingBase * build = (BuildingBase*)info.pBuilding;
		if (build && build->getTypeID() == BUILDINGTYPE_WALL) {
			if (this->GetMapGridLogicInfo(rightTop.x*MAPGRIDHEIGHT+rightTop.y,&info) && info.bIsBiulded) {
				build = (BuildingBase*)info.pBuilding;
				if (build && build->getTypeID() == BUILDINGTYPE_WALL) { // 左上有 是墙 ＋ 右上有 是墙
					if(this->GetMapGridLogicInfo(index.x*MAPGRIDHEIGHT+index.y,&info) && info.bIsBiulded){
						build = (BuildingBase*)info.pBuilding;
						if (build && build->getTypeID() == BUILDINGTYPE_WALL) {
                            char spritename[64] = {0};
                            sprintf(spritename,"build_defense_wall_lvl%d_03",build->lv);
                            build->replaceSprite_(GAME_FILE_TRANSFORM(spritename,".png").c_str());
						}
					}
				}else { // 左上有 是墙 ＋ 右上有 不是墙
					if(this->GetMapGridLogicInfo(index.x*MAPGRIDHEIGHT+index.y,&info) && info.bIsBiulded){
						build = (BuildingBase*)info.pBuilding;
						if (build && build->getTypeID() == BUILDINGTYPE_WALL) {
                            char spritename[64] = {0};
                            sprintf(spritename,"build_defense_wall_lvl%d_01",build->lv);
                            build->replaceSprite_(GAME_FILE_TRANSFORM(spritename,".png").c_str());
						}
					}
				}
			}
		}else {
			 if (this->GetMapGridLogicInfo(rightTop.x*MAPGRIDHEIGHT+rightTop.y,&info) && info.bIsBiulded) {
				 build = (BuildingBase*)info.pBuilding;
				 if (build && build->getTypeID() == BUILDINGTYPE_WALL) { // 左上有 不是墙 ＋ 右上有 是墙
					 if(this->GetMapGridLogicInfo(index.x*MAPGRIDHEIGHT+index.y,&info) && info.bIsBiulded){
						 build = (BuildingBase*)info.pBuilding;
						 if (build && build->getTypeID() == BUILDINGTYPE_WALL) {
                             char spritename[64] = {0};
                             sprintf(spritename,"build_defense_wall_lvl%d_02",build->lv);
                             build->replaceSprite_(GAME_FILE_TRANSFORM(spritename,".png").c_str());
						 }
					 }
				 }
			 }
		}
	}
}

BuildingBase* CentralLayer::BuildWall_first(int unitID,CCPoint mapindex,bool isbuy)
{
    BuildingBase* build = NULL;
	MapGridLogicInfo info;

	build = AddContinuousWall(unitID,mapindex,0);
	if (!isbuy) {
        ResetPlaceDirection_type(mapindex);
        
        ResetPlaceDirection_type(ccp(mapindex.x-1,mapindex.y));
        ResetPlaceDirection_type(ccp(mapindex.x,mapindex.y-1));
        ResetPlaceDirection_type(ccp(mapindex.x,mapindex.y+1));
        ResetPlaceDirection_type(ccp(mapindex.x+1,mapindex.y));
    }
    
    PlaceNextIndex = mapindex;
	placeDirection = getPlaceDirection(PlaceNextIndex);
	m_PlaceState = PlaceState_Next;
    
    return build;
}

BuildingBase* CentralLayer::BuildWall_next(int dir,int unitID,bool isbuy)
{
    BuildingBase* build = NULL;
	if (placeDirection != -1) {
		CCPoint preIndex = PlaceNextIndex;
		this->getPlaceNextIndex(placeDirection);
        
		MapGridLogicInfo info;
		if ((this->GetMapGridLogicInfo(PlaceNextIndex.x*MAPGRIDHEIGHT+PlaceNextIndex.y,&info) && info.bIsBiulded)
			|| PlaceNextIndex.x < 0 || PlaceNextIndex.x > MAPGRIDHEIGHT-1 || PlaceNextIndex.y < 0 || PlaceNextIndex.y > MAPGRIDHEIGHT-1)
		{
			PlaceNextIndex = preIndex;
			return build;
		}
        
		build = AddContinuousWall(40001,PlaceNextIndex,0);
		
        if (!isbuy) {
            ResetPlaceDirection_type(PlaceNextIndex);
            
            ResetPlaceDirection_type(ccp(PlaceNextIndex.x-1,PlaceNextIndex.y));
            ResetPlaceDirection_type(ccp(PlaceNextIndex.x,PlaceNextIndex.y-1));
            ResetPlaceDirection_type(ccp(PlaceNextIndex.x,PlaceNextIndex.y+1));
            ResetPlaceDirection_type(ccp(PlaceNextIndex.x+1,PlaceNextIndex.y));
        }
		return build;
	}
	return build;
}

void CentralLayer::ResetPlaceAll(CCPoint mapindex)
{
    ResetPlaceDirection_type(mapindex);
    
    ResetPlaceDirection_type(ccp(mapindex.x-1,mapindex.y));
    ResetPlaceDirection_type(ccp(mapindex.x,mapindex.y-1));
    ResetPlaceDirection_type(ccp(mapindex.x,mapindex.y+1));
    ResetPlaceDirection_type(ccp(mapindex.x+1,mapindex.y));
}











