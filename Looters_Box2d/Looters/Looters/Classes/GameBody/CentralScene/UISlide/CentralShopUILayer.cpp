//
//  CentralUILayer.cpp
//  Looters
//
//  Created by yisuode on 12-11-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "CentralShopUILayer.h"
#include "DialogLayer.h"
#include "cocos2d.h"
#include "GameControl.h"
#include "GameData.h"
#include "TipInfo.h"


#include "NetMessageManager.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define tableViewW  140
#define tableViewH  208

CentralShopUILayer::CentralShopUILayer():
nextBtn(NULL)
, BoxBtn1(NULL)
, BoxBtn2(NULL)
, BoxBtn3(NULL)
, BoxBtn4(NULL)
, BoxBtn5(NULL)
, BoxBtn6(NULL)
, l_p(NULL)
, l_g(NULL)
, l_gem(NULL)   
{
    DetectTyep = ShopDetectProcess_null;
    buy = new BuyAppC();
}

CentralShopUILayer::~CentralShopUILayer()
{
    spriteArr->release();
    
    delete  buy;
    buy = NULL;
     CC_SAFE_RELEASE(nextBtn);
    CC_SAFE_RELEASE(BoxBtn1);
    CC_SAFE_RELEASE(BoxBtn2);
    CC_SAFE_RELEASE(BoxBtn3);
    CC_SAFE_RELEASE(BoxBtn4);
    CC_SAFE_RELEASE(BoxBtn5);
    CC_SAFE_RELEASE(BoxBtn6);
    CC_SAFE_RELEASE(l_p);
    CC_SAFE_RELEASE(l_g);
    CC_SAFE_RELEASE(l_gem);

}

bool CentralShopUILayer::init( void )
{
	if( !CCLayer::init() )
		return false;
    
    spriteArr = CCArray::create();
    spriteArr->retain();
    
    labelArr = CCArray::create();
    labelArr->retain();
    
    upBuyBuildingArr();
    
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    town = GameData::GetDataFromBaseTownHallLevelsData(pCentralScene->m_pCentralLayer->MAXTownhall());
    
    
    _town.TroopHousing = 0;           //营火数量
    _town.ElixirStorage = 0;          //水罐数量
    _town.GoldStorage = 0;            //金库数量
    _town.ElixirPump = 0;             //水井数量
    _town.GoldMine = 0;               //金矿数量
    _town.Barrack = 0;                //兵营数量
    _town.Cannon = 0;                 //加农炮
    _town.Wall = 0;                   //墙
    _town.ArcherTower = 0;            //箭塔
    _town.WizardTower = 0;            //法师塔
    _town.AirDefense = 0;             //防空塔
    _town.Mortar = 0;                 //巨炮
    _town.AllianceCastle = 0;         //公会城保
    _town.Ejector = 0;                //弹射地雷
    _town.Superbomb = 0;              //超级地雷
    _town.Mine = 0;                   //普通地雷
    _town.WorkerBuilding = 0;         //工人
    _town.Laboratory = 0;             //科技
    _town.Communicationsmast = 0;     //已取消
    _town.TeslaTower = 0;             //电塔
    _town.SpellForge = 0;             //魔法池
    
    int num = pCentralScene->m_pCentralLayer->unit_list_->count();
    
    for (int i = 0; i <num; i++)
    {
        Unit *unit = (Unit*)pCentralScene->m_pCentralLayer->unit_list_->objectAtIndex(i);
        //如果是建筑
        if (unit->getTypeID() >0 && unit->getTypeID()<1000)
        {
            BuildingBase* build = (BuildingBase*)unit;
            
            switch (build->getTypeID()) 
            {
                case DEFENSE_AIRDEFENSE:
                {
                    _town.AirDefense+=1;
                }
                    break;
                case DEFENSE_WIZARDTOWER:
                {
                    _town.WizardTower+=1;
                }
                    break;
                case DEFENSE_ARCHERTOWER:
                {
                    _town.ArcherTower+=1;
                }
                    break;
                case DEFENSE_CANNON:
                {
                    _town.Cannon+=1;
                }
                    break;
                case ARMY_SPELLFORGE:
                {
                    _town.SpellForge+=1;
                }
                    break;
                case ARMY_ALLIANCECASTLE:
                {
                    _town.AllianceCastle+=1;
                }
                    break;
                case ARMY_LABORATORY:
                {
                    _town.Laboratory+=1;
                }
                    break;
                case ARMY_BARRACK:
                {
                    _town.Barrack+=1;
                }
                    break;
                case ARMY_TROOPHOUSING:
                {
                    _town.TroopHousing+=1;
                }
                    break;
                case RESOURCE_GOLDSTORAGE:
                {
                    _town.GoldStorage+=1;
                }
                    break;
                case RESOURCE_GOLDMINE:
                {
                    _town.GoldMine+=1;
                }
                    break;
                case RESOURCE_ELIXIRSTORAGE:
                {
                    _town.ElixirStorage+=1;
                }
                    break;
                case RESOURCE_ELIXIRPUMP:
                {
                    _town.ElixirPump+=1;
                }
                    break;
                case DEFENSE_TESLATOWER:
                {
                    _town.TeslaTower+=1;
                }
                    break;
                case DEFENSE_MORTAR:
                {
                    _town.Mortar+=1;
                }
                    break;
                case BUILDINGTYPE_WORKER:
                {
                    _town.WorkerBuilding+=1;
                }
                    break;
                case BUILDINGTYPE_WALL:
                {
                    _town.Wall+=1;
                }
                    break;

                default:
                    break;
            }
            
            
        }
    }
    return true;
}

void CentralShopUILayer::onEnter()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
    
    CCNode::onEnter();
}

void CentralShopUILayer::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    CCNode::onExit();
}


bool CentralShopUILayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLOG("响应啦........................................");
    return true;
}

void CentralShopUILayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralShopUILayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralShopUILayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralShopUILayer::initShopUI()
{
    nextBtn->setVisible(false);
    tableView = NULL;
    
    
    
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;

    l_gem->setString(CommonResource::getStringFromInt(pCentralScene->m_pCentralData->m_Central_UserData->user_gem).c_str());
    l_p->setString(CommonResource::getStringFromInt(pCentralScene->m_pCentralData->m_Central_UserData->user_potions).c_str());
    l_g->setString(CommonResource::getStringFromInt(pCentralScene->m_pCentralData->m_Central_UserData->user_gold).c_str());
    
}

void CentralShopUILayer::deleteTableView()
{
    if (tableView != NULL)
    {
        tableView->removeFromParentAndCleanup(false);
        tableView = NULL;
    }

}
void CentralShopUILayer::addTableView()
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;

        
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    tableView = CCTableView::create(this, CCSizeMake(winSize.width, tableViewH));
    tableView->setDirection(kCCScrollViewDirectionHorizontal);
    tableView->setPosition(ccp(0,winSize.height/6));
    tableView->setDelegate(this);
    tableView->reloadData();
    
    pCentralScene->m_pCentralShopUILayer->addChild(tableView);
}

void CentralShopUILayer::addBuilding(int unitID)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    pCentralScene->m_pCentralUILayer->setVisible(true);
    
    // 墙的处理
    int ID = unitID/100;
    if (ID == BUILDINGTYPE_WALL) {
        pCentralScene->m_pCentralLayer->m_PlaceState = CentralLayer::PlaceState_First;
    }
    
    pCentralScene->m_pCentralLayer->buyBuilding(unitID);
    
    pCentralScene->removeChild(pCentralScene->m_pCentralShopUILayer, false);
    pCentralScene->m_pCentralShopUILayer = NULL;
}


SEL_MenuHandler CentralShopUILayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget,CCString * pSelectorName){
    
    //Bind Menu Events，绑定一个menu，点击方法是press，以下同理
    
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "press",MainScene::press);
    
    return NULL;
    
}

SEL_CCControlHandler CentralShopUILayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName){
    
    //Bind CCControl Events
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnNextShop",CentralShopUILayer::onBtnNextShop);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnClosedShop",CentralShopUILayer::onBtnClosedShop);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBox1",CentralShopUILayer::onBox1);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBox2",CentralShopUILayer::onBox2);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBox3",CentralShopUILayer::onBox3);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBox4",CentralShopUILayer::onBox4);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBox5",CentralShopUILayer::onBox5);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBox6",CentralShopUILayer::onBox6);
    return NULL;

}

bool CentralShopUILayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode){
    
    //Bind variables
    
    //    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ATM", CCSprite *, this->ATM);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nextBtn", CCControlButton *, this->nextBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BoxBtn1", CCControlButton *, this->BoxBtn1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BoxBtn2", CCControlButton *, this->BoxBtn2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BoxBtn3", CCControlButton *, this->BoxBtn3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BoxBtn4", CCControlButton *, this->BoxBtn4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BoxBtn5", CCControlButton *, this->BoxBtn5);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BoxBtn6", CCControlButton *, this->BoxBtn6);
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_p", CCLabelTTF *, this->l_p);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_g", CCLabelTTF *, this->l_g);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "l_gem", CCLabelTTF *, this->l_gem);
    
    
    return false;
    
}
void CentralShopUILayer::onNodeLoaded(CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader){
    
    //检测scene
    
    CCLOG("MainScene loading.....successed!") ;
    
}
void CentralShopUILayer::onBox1(cocos2d::CCObject * pSender)
{
    if (!BoxBtn1->isVisible()) return;
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;

    
    
    NetMessageManager::BankServerIP = "192.168.0.66";//支付服务器IP
    NetMessageManager::BankServerPort = 7775;
    
    BtnTyep = 1;
    for (int i = 0; i < Resource_end; i++)
    {
        
       
        IconSprite *build = IconSprite::createWithSpriteFrameName("ui_shop_dec.png");
        build->setAnchorPoint(CCPointZero);
        build->type = i;
        build->num = 0;
        
        CCSprite *infobg = CCSprite::createWithSpriteFrameName("ui_shop_infobg.png");
        infobg->setPosition(ccp(63,25));
        build->addChild(infobg);
        
        char strFileName[64];
        sprintf(strFileName,"ui_shop_resources%d.png",i+1);
        CCSprite* sprbuild = CCSprite::createWithSpriteFrameName(strFileName);
        sprbuild->setPosition(ccp(62, 107));
        build->addChild(sprbuild);
        
        
        
        char strFileYuan[64];
        char strFileGem[64];
        char strFilename[64];
        switch (i)
        {
            case Resource_Gems1:
            {
                //500宝石30元
                sprintf(strFileYuan,"30RMB");
                sprintf(strFileGem,"500");
                sprintf(strFilename,"");
            }
                break;
            case Resource_Gems2:
            {
                //1200宝石68元
                sprintf(strFileYuan,"68RMB");
                sprintf(strFileGem,"1200");
                sprintf(strFilename,"");
            }
                break;
            case Resource_Gems3:
            {
                //2500宝石128元
                sprintf(strFileYuan,"128RMB");
                sprintf(strFileGem,"2500");
                sprintf(strFilename,"");
            }
                break;
            case Resource_Gems4:
            {
                //6500宝石328元
                sprintf(strFileYuan,"328RMB");
                sprintf(strFileGem,"6500");
                sprintf(strFilename,"");
            }
                break;
            case Resource_Gems5:
            {
                //14000宝石648元
                sprintf(strFileYuan,"648RMB");
                sprintf(strFileGem,"14000");
                sprintf(strFilename,"");
                
            }
                break;
            case Resource_gold10:
            {
                sprintf(strFilename,"");
            }
                break;
            case Resource_gold50:
            {
                sprintf(strFilename,"");
            }
                break;
            case Resource_gold100:
            {
                sprintf(strFilename,"");
            }
                break;
            case Resource_water10:
            {
                sprintf(strFilename,"");
            }
                break;
            case Resource_water50:
            {
                sprintf(strFilename,"");
            }
                break;
            case Resource_water100:
            {
                sprintf(strFilename,"");
            }
                break;
            default:
                break;
        }
        
        CCLabelTTF* nameLabel = CCLabelTTF::create(strFilename, "Helvetica", 12);
        nameLabel->setPosition(ccp(63, 185));
        build->addChild(nameLabel);
        
        
        
        if (i < Resource_gold10) 
        {
            //买宝石
            spriteArr->addObject(build);
            
            CCSprite *resourcegem = CCSprite::createWithSpriteFrameName("ui_public_icon_gem.png");
            resourcegem->setPosition(ccp(50, 185));
            build->addChild(resourcegem);
            
            CCLabelTTF* GPLabel = CCLabelTTF::create(strFileYuan, "Helvetica", 12);
            GPLabel->setPosition(ccp(66, 25));
            GPLabel->setAnchorPoint(ccp(0.5,0.5));
            build->addChild(GPLabel);
            
            CCLabelTTF* numLabelGem = CCLabelTTF::create(strFileGem, "Helvetica", 12);
            numLabelGem->setPosition(ccp(60, 185));
            numLabelGem->setAnchorPoint(ccp(0,0.5));
            build->addChild(numLabelGem);
            
            
        }
        else if(i < Resource_water10)
        {
            
            //买金币
            int tempG = pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX - pCentralScene->m_pCentralData->m_Central_UserData->user_gold;
            
            
            if(i == Resource_gold10)
            {
                if (pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX/10 < tempG)
                {
                    build->num = pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX/10;
                    spriteArr->addObject(build);
                }
                else if(0 < tempG)
                {
                    build->num = tempG;
                    spriteArr->addObject(build);
                }
            }
            else if(i == Resource_gold50)
            {
                if (pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX/2 < tempG)
                {
                    build->num = pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX/2;
                    spriteArr->addObject(build);
                }
                else if (pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX/10 < tempG)
                {
                    build->num = tempG;
                    spriteArr->addObject(build);
                }
            }
            else
            {
                if (pCentralScene->m_pCentralData->m_Central_UserData->user_goldMAX/2 < tempG)
                {
                    build->num = tempG;
                    spriteArr->addObject(build);
                }
            }
            char strFileg[64];
            sprintf(strFileg,"%d金币",build->num);
            CCLabelTTF* numLabel = CCLabelTTF::create(strFileg, "Helvetica", 12);
            numLabel->setPosition(ccp(63, 185));
            build->addChild(numLabel);
            
        }
        else
        {
            
            
            //买水
            int tempP = pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX - pCentralScene->m_pCentralData->m_Central_UserData->user_potions;
            
            
            if(i == Resource_water10)
            {
                if (pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX/10 < tempP)
                {
                    build->num = pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX/10;
                    spriteArr->addObject(build);
                }
                else if(0 < tempP)
                {
                    build->num = tempP;
                    spriteArr->addObject(build);
                }
            }
            else if(i == Resource_water50)
            {
                if (pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX/2 < tempP)
                {
                    build->num = pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX/2;
                    spriteArr->addObject(build);
                }
                else if (pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX/10 < tempP)
                {
                    build->num = tempP;
                    spriteArr->addObject(build);
                }
            }
            else
            {
                if (pCentralScene->m_pCentralData->m_Central_UserData->user_potionsMAX/2 < tempP)
                {
                    build->num = tempP;
                    spriteArr->addObject(build);
                }
            }
            char strFilep[64];
            sprintf(strFilep,"%d粮食",build->num);
            CCLabelTTF* numLabel = CCLabelTTF::create(strFilep, "Helvetica", 12);
            numLabel->setPosition(ccp(63, 185));
            build->addChild(numLabel);
        }
        
        if (build->num > 0)
        {
            build->gem = BuyResourceGem(build->num);

            
            CCSprite *resource = CCSprite::createWithSpriteFrameName("ui_public_icon_gem.png");
            resource->setPosition(ccp(80, 26));
            build->addChild(resource);
            
            CCLabelTTF* GPLabel = CCLabelTTF::create(CommonResource::getStringFromInt(build->gem).c_str(), "Helvetica", 12);
            GPLabel->setPosition(ccp(66, 25));
            GPLabel->setAnchorPoint(ccp(1,0.5));
            build->addChild(GPLabel);
            if (pCentralScene->m_pCentralData->m_Central_UserData->user_gem < build->gem)
            {
                GPLabel->setColor(ccRED);
            }
            
        }
        
    }

    BoxBtnV(false);
    
    addTableView();
}
void CentralShopUILayer::onBox2(cocos2d::CCObject * pSender)
{
    if (!BoxBtn2->isVisible()) return;
    BtnTyep = 2;
    for (int i = 0; i < 5; i++)
    {
        
        int num = 0;
        
        switch (i)
        {
            case 0:
                num = 200;
                break;
            case 1:
                num = 201;
                break;
            case 2:
                num = 202;
                break;
            case 3:
                num = 203;
                break;
            case 4:
                num = 500;
                break;
            default:
                break;
        }
        
        spriteArr->addObject(initIconSprite(num));
        
    }
    
    BoxBtnV(false);
    
    addTableView();
}
void CentralShopUILayer::onBox3(cocos2d::CCObject * pSender)
{
    if (!BoxBtn3->isVisible()) return;
    BoxBtnV(false);
}
void CentralShopUILayer::onBox4(cocos2d::CCObject * pSender)
{
    if (!BoxBtn4->isVisible()) return;
    BtnTyep = 4;
    for (int i = 0; i < 4; i++)
    {
        
        int num = 0;
        
        switch (i)
        {
         
            case 0:
                num = 1;
                break;
            case 1:
                num = 2;
                break;
            case 2:
                num = 3;
                break;
            case 3:
                num = 5;
                break;
            default:
                break;
        }
        
        
        spriteArr->addObject(initIconSprite(num));
        
        
        
        
        
    }
    BoxBtnV(false);
    addTableView();
}
void CentralShopUILayer::onBox5(cocos2d::CCObject * pSender)
{
    if (!BoxBtn5->isVisible()) return;
    BtnTyep = 5;
    for (int i = 0; i < 5; i++)
    {
        
        int num = 0;
        
        switch (i)
        {
            case 0:
                num = 301;
                break;
            case 1:
                num = 303;
                break;
            case 2:
                num = 304;
                break;
            case 3:
                num = 400;
                break;
            case 4:
                num = 300;
                break;
            default:
                break;
        }

        
        spriteArr->addObject(initIconSprite(num));
    }
    
    BoxBtnV(false);
    addTableView();
}
void CentralShopUILayer::onBox6(cocos2d::CCObject * pSender)
{
    BoxBtnV(false);

}
IconSprite* CentralShopUILayer::initIconSprite(int _type)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    const BaseBuildingLevelData* buildingBaseLevelData;
    buildingBaseLevelData = GameData::GetDataFromBaseBuildingLevelData( _type*100+1);
    
    
    IconSprite *build = IconSprite::createWithSpriteFrameName("ui_shop_dec.png");
    build->setAnchorPoint(CCPointZero);
    build->type = _type;
    
    CCSprite *infobg = CCSprite::createWithSpriteFrameName("ui_shop_infobg.png");
    infobg->setPosition(ccp(63,25));
    build->addChild(infobg);
    
    
    char strFilenum[64];
    bool isNoNum = true;
    switch (build->type)
    {
        case DEFENSE_AIRDEFENSE:
        {
            if (town->AirDefense == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.AirDefense,town->AirDefense);
            }
        }
            break;
        case DEFENSE_WIZARDTOWER:
        {
            if (town->WizardTower == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.WizardTower,town->WizardTower);
            }
        }
            break;
        case DEFENSE_ARCHERTOWER:
        {
            if (town->ArcherTower == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.ArcherTower,town->ArcherTower);
            }
        }
            break;
        case DEFENSE_CANNON:
        {
            if (town->Cannon == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.Cannon,town->Cannon);
            }
        }
            break;
        case ARMY_SPELLFORGE:
        {
            if (town->SpellForge == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.SpellForge,town->SpellForge);
            }
        }
            break;
        case ARMY_ALLIANCECASTLE:
        {
            if (town->AllianceCastle == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.AllianceCastle,town->AllianceCastle);
            }
        }
            break;
        case ARMY_LABORATORY:
        {
            if (town->Laboratory == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.Laboratory,town->Laboratory);
            }
        }
            break;
        case ARMY_BARRACK:
        {
            if (town->Barrack == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.Barrack,town->Barrack);
            }
        }
            break;
        case ARMY_TROOPHOUSING:
        {
            if (town->TroopHousing == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.TroopHousing,town->TroopHousing);
            }
        }
            break;
        case RESOURCE_GOLDSTORAGE:
        {
            if (town->GoldStorage == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.GoldStorage,town->GoldStorage);
            }
        }
            break;
        case RESOURCE_GOLDMINE:
        {
            if (town->GoldMine == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.GoldMine,town->GoldMine);
            }
        }
            break;
        case RESOURCE_ELIXIRSTORAGE:
        {
            if (town->ElixirStorage == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.ElixirStorage,town->ElixirStorage);
            }
        }
            break;
        case RESOURCE_ELIXIRPUMP:
        {
            if (town->ElixirPump == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.ElixirPump,town->ElixirPump);
            }
        }
            break;
        case DEFENSE_TESLATOWER:
        {
            if (town->TeslaTower == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.TeslaTower,town->TeslaTower);
            }
        }
            break;
        case DEFENSE_MORTAR:
        {
            if (town->Mortar == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.Mortar,town->Mortar);
            }
        }
            break;
        case BUILDINGTYPE_WORKER:
        {
            if (town->WorkerBuilding == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.WorkerBuilding,town->WorkerBuilding);
            }
        }
            break;
        case BUILDINGTYPE_WALL:
        {
            if (town->Wall == -1)
            {
                isNoNum = false;
            }
            else
            {
                sprintf(strFilenum,"%d/%d",_town.Wall,town->Wall);
            }
        }
            break;
            
        default:
            break;
    }
    
    if (isNoNum)
    {
        CCSprite *sprtime = CCSprite::createWithSpriteFrameName("ui_shop_time.png");
        sprtime->setPosition(ccp(22, 50));
        build->addChild(sprtime);
        
        //建筑时间
        CCLabelTTF* timeLabel = CCLabelTTF::create("", "Helvetica", 12);
        timeLabel->setPosition(ccp(35, 40));
        timeLabel->setAnchorPoint(CCPointZero);
        build->addChild(timeLabel);
        char strFiletime[64];
        if (buildingBaseLevelData->BuildTimeD > 0)
        {
            sprintf(strFiletime,"%dd",buildingBaseLevelData->BuildTimeD);
        }
        else if(buildingBaseLevelData->BuildTimeH > 0)
        {
            sprintf(strFiletime,"%dh",buildingBaseLevelData->BuildTimeH);
        }
        else if(buildingBaseLevelData->BuildTimeM > 0)
        {
            sprintf(strFiletime,"%dm",buildingBaseLevelData->BuildTimeM);
        }
        else
        {
            sprintf(strFiletime,"无");
        }
        timeLabel->setString(strFiletime);
        
        
        //建筑个数
        CCLabelTTF* numLabel = CCLabelTTF::create(strFilenum, "Helvetica", 12);
        numLabel->setPosition(ccp(114, 40));
        numLabel->setAnchorPoint(ccp(1,0));
        build->addChild(numLabel);
        
    }
    else
    {
        char strFileTownHallLevel[64];
        sprintf(strFileTownHallLevel,"需要%d级\n主基地解锁",buildingBaseLevelData->TownHallLevel);
        CCLabelTTF* TownHallLevelLabel = CCLabelTTF::create(strFileTownHallLevel, "Helvetica", 12);
        TownHallLevelLabel->setPosition(ccp(62, 70));
        build->addChild(TownHallLevelLabel,2,2);
        
    }
    
    
    //建筑花费
    CCLabelTTF* GPLabel = CCLabelTTF::create(CommonResource::getStringFromInt(buildingBaseLevelData->BuildCost).c_str(), "Helvetica", 12);
    GPLabel->setPosition(ccp(66, 25));
    GPLabel->setAnchorPoint(ccp(1,0.5));
    build->addChild(GPLabel);
    
    
    CCSprite *resource = NULL;
    //金币
    if ("Gold" == string(buildingBaseLevelData->BuildResource))
    {
        resource = CCSprite::createWithSpriteFrameName("ui_public_icon_gold.png");
        
        if (pCentralScene->m_pCentralData->m_Central_UserData->user_gold < buildingBaseLevelData->BuildCost)
        {
            if (isNoNum)
            {
                GPLabel->setColor(ccRED);
            }
            
        }
        
    }
    
    //药水
    else if("Elixir" == string(buildingBaseLevelData->BuildResource))
    {
        resource = CCSprite::createWithSpriteFrameName("ui_public_icon_water.png");
        if (pCentralScene->m_pCentralData->m_Central_UserData->user_potions < buildingBaseLevelData->BuildCost)
        {
            if (isNoNum)
            {
                GPLabel->setColor(ccRED);
            }
        }
        
    }
    
    //宝石
    else if("Diamonds" == string(buildingBaseLevelData->BuildResource))
    {
        resource = CCSprite::createWithSpriteFrameName("ui_public_icon_gem.png");
        if (pCentralScene->m_pCentralData->m_Central_UserData->user_gem < buildingBaseLevelData->BuildCost)
        {
            if (isNoNum)
            {
                GPLabel->setColor(ccRED);
            }
        }
        
    }
    resource->setPosition(ccp(80, 26));
    build->addChild(resource);
    
    CCSprite* sprbuildSWF = NULL;
    if(build->type == DEFENSE_CANNON){
//        LAnimation* animBase = LAnimManage::shareLAnimManage()->createLAnimation(buildingBaseLevelData->SWF, pBuilding);
//        //将图片加载到Cache里
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GAME_FILE_TRANSFORM(buildingBaseLevelData->SWF.c_str(),".plist").c_str(),GAME_FILE_TRANSFORM(buildingBaseLevelData->SWF.c_str(),".png").c_str());
        sprbuildSWF = CCSprite::createWithSpriteFrameName("build_basic_turret_lvl1_base_left1_0000.png");
        
    }
    // 加农炮
    else if(build->type == DEFENSE_MORTAR)
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GAME_FILE_TRANSFORM(buildingBaseLevelData->SWF.c_str(),".plist").c_str(),GAME_FILE_TRANSFORM(buildingBaseLevelData->SWF.c_str(),".png").c_str());
        
        sprbuildSWF = CCSprite::createWithSpriteFrameName("build_mortar_lvl1_idle_3_0000.png");

    }
    //建筑名
    const string* name = GameData::GetTextInfo(buildingBaseLevelData->Text);
    CCLabelTTF* nameLabel = CCLabelTTF::create(name->c_str(), "Helvetica", 12);
//    CCLabelTTF* nameLabel = CCLabelTTF::create(buildingBaseLevelData->Name.c_str(), "Helvetica", 12);
    nameLabel->setPosition(ccp(63, 185));
    build->addChild(nameLabel);
    //建筑图
    CCSprite* sprbuild = CCSprite::create(GAME_FILE_TRANSFORM(buildingBaseLevelData->ExportName.c_str(),".png").c_str());
    sprbuild->setPosition(ccp(62, 107));
    build->addChild(sprbuild);
    if (sprbuildSWF != NULL)
    {
        sprbuildSWF->setPosition(ccp(62, 107));
        build->addChild(sprbuildSWF);
    }
    
    //不可建筑灰色
    if (!isAllBuild(build->type))
    {
        CCSprite *dechui = CCSprite::createWithSpriteFrameName("ui_shop_dechui.png");
        dechui->setAnchorPoint(CCPointZero);
        build->addChild(dechui);
    }
    
    return build;
    
}
void CentralShopUILayer::onBtnNextShop(cocos2d::CCObject * pSender)
{
    deleteTableView();
    spriteArr->removeAllObjects();
    labelArr->removeAllObjects();
    BoxBtnV(true);
}
void CentralShopUILayer::onBtnClosedShop(cocos2d::CCObject *pSender)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    pCentralScene->m_pCentralUILayer->setVisible(true);
    
    pCentralScene->removeChild(pCentralScene->m_pCentralShopUILayer, true);
    
    pCentralScene->m_pCentralShopUILayer = NULL;
}
int CentralShopUILayer::BuyResourceGem(int _num)
{
    int gem;
    if (_num >= 10000000)
    {
        gem = 3000*_num/10000000;
    }
    else if (_num >= 1000000)
    {
        gem = 600*_num/1000000;
    }
    else if (_num >= 100000)
    {
        gem = 125*_num/100000;
    }
    else if (_num >= 10000)
    {
        gem = 25*_num/10000;
    }
    else if (_num >= 1000)
    {
        gem = 5*_num/1000;
    }
    else if (_num >= 100)
    {
        gem = _num/100;
    }
    else
    {
        gem = 1;
    }
    return gem;
}
void CentralShopUILayer::BuyResource(int _type ,IconSprite* _icon)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    //com.bw.looters.1200
    //com.bw.looters.500
    switch (_type)
    {
        case Resource_Gems1:
        {
            //500宝石30元
            BuyNode::sharedBuyNode()->num = 500;
            BuyNode::sharedBuyNode()->type = Resource_Gems1;
            BuyNode::sharedBuyNode()->Rmb = 30;
            
            buy->onBuyApp("com.bw.looters.500");
            
        }
            break;
        case Resource_Gems2:
        {
            //1200宝石68元
            BuyNode::sharedBuyNode()->num = 1200;
            BuyNode::sharedBuyNode()->type = Resource_Gems2;
            BuyNode::sharedBuyNode()->Rmb = 68;

            buy->onBuyApp("com.bw.looters.1200");
        }
            break;
        case Resource_Gems3:
        {
            //2500宝石128元
            BuyNode::sharedBuyNode()->num = 2500;
            BuyNode::sharedBuyNode()->type = Resource_Gems3;
            BuyNode::sharedBuyNode()->Rmb = 128;

            buy->onBuyApp("com.bw.looters.2500");
        }
            break;
        case Resource_Gems4:
        {
            //6500宝石328元
            BuyNode::sharedBuyNode()->num = 6500;
            BuyNode::sharedBuyNode()->type = Resource_Gems4;
            BuyNode::sharedBuyNode()->Rmb = 328;

            buy->onBuyApp("com.bw.looters.6500");
        }
            break;
        case Resource_Gems5:
        {
            //14000宝石648元
            BuyNode::sharedBuyNode()->num = 14000;
            BuyNode::sharedBuyNode()->type = Resource_Gems5;
            BuyNode::sharedBuyNode()->Rmb = 648;

            buy->onBuyApp("com.bw.looters.14000");
        }
            break;
        case Resource_gold10:
        {
            if (pCentralScene->m_pCentralUILayer->updateGem(-_icon->gem)) 
            {
                pCentralScene->m_pCentralUILayer->updateGold(_icon->num);
                pCentralScene->m_pCentralLayer->buildingAccount2(OperateType_BuyGold,Resource_gold10-4,true);
                
                
                if (pCentralScene->m_pCentralLayer->m_building != NULL && pCentralScene->m_pCentralLayer->m_BuyBuilding ==NULL)
                {
                    //放下建筑
                    pCentralScene->m_pCentralLayer->fangxiajianzhu();
                }
                //临时
                pCentralScene->m_pCentralUILayer->setVisible(true);
                pCentralScene->m_pCentralLayer->setVisible(true);
                
                pCentralScene->removeChild(pCentralScene->m_pCentralShopUILayer, false);
                
                pCentralScene->m_pCentralShopUILayer = NULL;
            }
        }
            break;
        case Resource_gold50:
        {
            if (pCentralScene->m_pCentralUILayer->updateGem(-_icon->gem)) 
            {
                pCentralScene->m_pCentralUILayer->updateGold(_icon->num);
                pCentralScene->m_pCentralLayer->buildingAccount2(OperateType_BuyGold,Resource_gold50-4,true);
                
                //临时
                if (pCentralScene->m_pCentralLayer->m_building != NULL && pCentralScene->m_pCentralLayer->m_BuyBuilding ==NULL)
                {
                    //放下建筑
                    pCentralScene->m_pCentralLayer->fangxiajianzhu();
                }
                pCentralScene->m_pCentralUILayer->setVisible(true);
                pCentralScene->m_pCentralLayer->setVisible(true);
                
                
                pCentralScene->removeChild(pCentralScene->m_pCentralShopUILayer, false);
                
                pCentralScene->m_pCentralShopUILayer = NULL;
            }
        }
            break;
        case Resource_gold100:
        {
            if (pCentralScene->m_pCentralUILayer->updateGem(-_icon->gem)) 
            {
                pCentralScene->m_pCentralUILayer->updateGold(_icon->num);
                pCentralScene->m_pCentralLayer->buildingAccount2(OperateType_BuyGold,Resource_gold100-4,true);
                
                //临时
                if (pCentralScene->m_pCentralLayer->m_building != NULL && pCentralScene->m_pCentralLayer->m_BuyBuilding ==NULL)
                {
                    //放下建筑
                    pCentralScene->m_pCentralLayer->fangxiajianzhu();
                }
                pCentralScene->m_pCentralUILayer->setVisible(true);
                pCentralScene->m_pCentralLayer->setVisible(true);
                
                pCentralScene->removeChild(pCentralScene->m_pCentralShopUILayer, false);
                
                pCentralScene->m_pCentralShopUILayer = NULL;
            }
        }
            break;
        case Resource_water10:
        {
            if (pCentralScene->m_pCentralUILayer->updateGem(-_icon->gem)) 
            {
                pCentralScene->m_pCentralUILayer->updatePotions(_icon->num);
                pCentralScene->m_pCentralLayer->buildingAccount2(OperateType_BuyPotions,Resource_water10-4,true);
                
                //临时
                if (pCentralScene->m_pCentralLayer->m_building != NULL && pCentralScene->m_pCentralLayer->m_BuyBuilding ==NULL)
                {
                    //放下建筑
                    pCentralScene->m_pCentralLayer->fangxiajianzhu();
                }
                pCentralScene->m_pCentralUILayer->setVisible(true);
                pCentralScene->m_pCentralLayer->setVisible(true);
                
                pCentralScene->removeChild(pCentralScene->m_pCentralShopUILayer, false);
                
                pCentralScene->m_pCentralShopUILayer = NULL;
            }
        }
            break;
        case Resource_water50:
        {
            if (pCentralScene->m_pCentralUILayer->updateGem(-_icon->gem)) 
            {
                pCentralScene->m_pCentralUILayer->updatePotions(_icon->num);
                pCentralScene->m_pCentralLayer->buildingAccount2(OperateType_BuyPotions,Resource_water50-4,true);
                
                //临时
                if (pCentralScene->m_pCentralLayer->m_building != NULL && pCentralScene->m_pCentralLayer->m_BuyBuilding ==NULL)
                {
                    //放下建筑
                    pCentralScene->m_pCentralLayer->fangxiajianzhu();
                }
                pCentralScene->m_pCentralUILayer->setVisible(true);
                pCentralScene->m_pCentralLayer->setVisible(true);
                
                pCentralScene->removeChild(pCentralScene->m_pCentralShopUILayer, false);
                
                pCentralScene->m_pCentralShopUILayer = NULL;
            }
        }
            break;
        case Resource_water100:
        {
            if (pCentralScene->m_pCentralUILayer->updateGem(-_icon->gem)) 
            {
                pCentralScene->m_pCentralUILayer->updatePotions(_icon->num);
                pCentralScene->m_pCentralLayer->buildingAccount2(OperateType_BuyPotions,Resource_water100-4,true);
                
                //临时
                if (pCentralScene->m_pCentralLayer->m_building != NULL && pCentralScene->m_pCentralLayer->m_BuyBuilding ==NULL)
                {
                    //放下建筑
                    pCentralScene->m_pCentralLayer->fangxiajianzhu();
                }
                pCentralScene->m_pCentralUILayer->setVisible(true);
                pCentralScene->m_pCentralLayer->setVisible(true);
                
                pCentralScene->removeChild(pCentralScene->m_pCentralShopUILayer, false);
                
                pCentralScene->m_pCentralShopUILayer = NULL;
            }
        }
            break;
        default:
            break;
    }
    
}
bool CentralShopUILayer::isAllBuild(int _type)
{
    bool isNum = true;
    
    switch (_type) 
    {
        case DEFENSE_AIRDEFENSE:
        {
            if (town->AirDefense == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->AirDefense <=_town.AirDefense)
                {
                    isNum = false;
                }  
            }
        }
            break;
        case DEFENSE_WIZARDTOWER:
        {
            if (town->WizardTower == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->WizardTower <=_town.WizardTower)
                {
                    isNum = false;
                }  
            }
        }
            break;
        case DEFENSE_ARCHERTOWER:
        {
            if (town->ArcherTower == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->ArcherTower <=_town.ArcherTower)
                {
                    isNum = false;
                }  
            }
        }
            break;
        case DEFENSE_CANNON:
        {
            if (town->Cannon == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->Cannon <=_town.Cannon)
                {
                    isNum = false;
                }  
            }
        }
            break;
        case ARMY_SPELLFORGE:
        {
            if (town->SpellForge == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->SpellForge <=_town.SpellForge)
                {
                    isNum = false;
                }  
            }
        }
            break;
        case ARMY_ALLIANCECASTLE:
        {
            if (town->AllianceCastle == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->AllianceCastle <=_town.AllianceCastle)
                {
                    isNum = false;
                }  
            }
        }
            break;
        case ARMY_LABORATORY:
        {
            if (town->Laboratory == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->Laboratory <=_town.Laboratory)
                {
                    isNum = false;
                }  
            }
        }
            break;
        case ARMY_BARRACK:
        {
            if (town->Barrack == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->Barrack <= _town.Barrack)
                {
                    isNum = false;
                }  
            }
        }
            break;
        case ARMY_TROOPHOUSING:
        {
            if (town->TroopHousing == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->TroopHousing <=_town.TroopHousing)
                {
                    isNum = false;
                }  
            }
        }
            break;
        case RESOURCE_GOLDSTORAGE:
        {
            if (town->GoldStorage == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->GoldStorage <=_town.GoldStorage)
                {
                    isNum = false;
                }  
            }
        }
            break;
        case RESOURCE_GOLDMINE:
        {
            if (town->GoldMine == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->GoldMine <=_town.GoldMine)
                {
                    isNum = false;
                }  
            }
        }
            break;
        case RESOURCE_ELIXIRSTORAGE:
        {
            if (town->ElixirStorage == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->ElixirStorage <=_town.ElixirStorage)
                {
                    isNum = false;
                }  
            }
        }
            break;
        case RESOURCE_ELIXIRPUMP:
        {
            if (town->ElixirPump == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->ElixirPump <=_town.ElixirPump)
                {
                    isNum = false;
                }  
            }
        }
            break;
        case DEFENSE_TESLATOWER:
        {
            if (town->TeslaTower == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->TeslaTower <=_town.TeslaTower)
                {
                    isNum = false;
                }  
            }
        }
            break;
        case DEFENSE_MORTAR:
        {
            if (town->Mortar == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->Mortar <=_town.Mortar)
                {
                    isNum = false;
                }  
            }
        }
            break;
        case BUILDINGTYPE_WORKER:
        {
            if (town->WorkerBuilding == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->WorkerBuilding <=_town.WorkerBuilding)
                {
                    isNum = false;
                }  
            }
        }
            break;
        case BUILDINGTYPE_WALL:
        {
            if (town->Wall == -1)
            {
                isNum = false;
            }
            else
            {
                if (town->Wall <=_town.Wall)
                {
                    isNum = false;
                }  
            }
        }
            break;
            
        default:
            break;
    }
    
    return isNum;
}

//列表

void CentralShopUILayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
    
    IconSprite *sprite = (IconSprite*)spriteArr->objectAtIndex(cell->getIdx());
    
    if (BtnTyep == 1)
    {
        BuyResource(sprite->type,sprite);
        
        
    }
    else 
    {
        if (isAllBuild(sprite->type))
        {
            addBuilding(sprite->type*100+1);
        }
        else
        {
            // 主建筑等级不够
//            const string* strtext = GameData::GetTextInfo("TID_NO_TROOPS");
            TipInfo *info = TipInfo::create();
            info->setString("主建筑等级不足", ccp( GamePlatform::GetScreenSize().width/2, GamePlatform::GetScreenSize().height/2+100),3.0f);
            this->addChild(info);
        }
    }
    
    
    
}

CCSize CentralShopUILayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(tableViewW, tableViewH);
}

CCTableViewCell* CentralShopUILayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    
    if (idx == 0)
    {
        CCLOG("%d",idx);
    }
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();

        
        
        CCSprite *sprite3 = (CCSprite*)spriteArr->objectAtIndex(idx);
        sprite3->removeFromParentAndCleanup(false);
        cell->removeChildByTag(121, false);
        
        sprite3->setScale(UNIT_Texture_scale_2048x1536);
        sprite3->setTag(121);
        cell->addChild(sprite3);
        
        
        
    }
    else
    {
        
        CCSprite *sprite3 = (CCSprite*)spriteArr->objectAtIndex(idx);
        sprite3->removeFromParentAndCleanup(false);
        cell->removeChildByTag(121, false);
        
        sprite3->setScale(UNIT_Texture_scale_2048x1536);
        sprite3->setTag(121);
        cell->addChild(sprite3);
    }
    
    
    return cell;
}

unsigned int CentralShopUILayer::numberOfCellsInTableView(CCTableView *table)
{
    return spriteArr->count();
}

void CentralShopUILayer::BoxBtnV(bool _isV)
{
    BoxBtn1->setVisible(_isV);
    BoxBtn2->setVisible(_isV);
    BoxBtn3->setVisible(_isV);
    BoxBtn4->setVisible(_isV);
    BoxBtn5->setVisible(_isV);
    BoxBtn6->setVisible(_isV);
    nextBtn->setVisible(!_isV);

	BoxBtn1->setEnabled(_isV);
	BoxBtn2->setEnabled(_isV);
	BoxBtn3->setEnabled(_isV);
	BoxBtn4->setEnabled(_isV);
	BoxBtn5->setEnabled(_isV);
	BoxBtn6->setEnabled(_isV);
	nextBtn->setEnabled(!_isV);
}
void CentralShopUILayer::upBuyBuildingArr()
{
        
}

void CentralShopUILayer::menuCall1(CCObject* sender)
{
    
}




















