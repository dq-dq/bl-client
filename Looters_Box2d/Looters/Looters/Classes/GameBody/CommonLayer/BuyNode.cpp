//
//  BuyNode.cpp
//  Looters
//
//  Created by yisuode on 12-12-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "BuyNode.h"
#include "GameData.h"
#include "cocos2d.h"
#include "GameControl.h"
#include "BuildingBase.h"
#include "BuyAppC.h"
USING_NS_CC;
static BuyNode s_BuyNode;

BuyNode* BuyNode::sharedBuyNode(void)
{
    static bool s_bFirstUseBuyNode = true;
    if (s_bFirstUseBuyNode)
    {
        s_bFirstUseBuyNode = false;
        s_BuyNode.init();
    }
    
    return &s_BuyNode;
}


BuyNode::BuyNode()
{
    
}

BuyNode::~BuyNode()
{
    
}
void BuyNode::setEncodChar(const char * _encod)
{
    CCLog("%@",_encod);
    string ab(_encod);
    encod = ab;
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    pCentralScene->m_pCentralLayer->CentralRechargeRequest(ab);
}
bool BuyNode::init( void )
{
    
    
    return true;
}

void BuyNode::onBuyApp()
{

}


