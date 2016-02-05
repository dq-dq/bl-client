//
//  CentralAccountLoginLayer.cpp
//  Looters
//
//  Created by 王 宁 on 13-1-8.
//
//

#include "CentralAccountLoginLayer.h"
#include <iostream>
#include "cocos2d.h"
#include "GameControl.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define FONT_NAME                       "Thonburi"
#define FONT_SIZE                       12

static CCRect getRect(CCNode * pNode)
{
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    rc.origin.x -= rc.size.width / 2;
    rc.origin.y -= rc.size.height / 2;
    return rc;
}


CentralAccountLoginLayer::CentralAccountLoginLayer()
: m_pNotificationLayer(0)
, s_bg(NULL)
, s_account_tf(NULL)
, s_password_tf(NULL)
{
    
}

CentralAccountLoginLayer::~CentralAccountLoginLayer()
{
    
}

bool CentralAccountLoginLayer::init( void )
{
	if( !CCLayer::init() )
		return false;
    
    return true;
}

SEL_MenuHandler CentralAccountLoginLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget,CCString * pSelectorName){
    
    //Bind Menu Events，绑定一个menu，点击方法是press，以下同理
    
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "press",MainScene::press);
    return NULL;
}

SEL_CCControlHandler CentralAccountLoginLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName){
    
    //Bind CCControl Events
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onOk",CentralAccountLoginLayer::onOk);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSina",CentralAccountLoginLayer::onSina);
    return NULL;
}

bool CentralAccountLoginLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode){
    
    //Bind variables
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_bg", CCSprite *, this->s_bg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_account_tf", CCSprite *, this->s_account_tf);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "s_password_tf", CCSprite *, this->s_password_tf);   
    return false;
    
}


void CentralAccountLoginLayer::onNodeLoaded(CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader){
    //检测scene
    
    CCLOG("MainScene loading.....successed!") ;
}

void CentralAccountLoginLayer::onEnter()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
    
    CCNode::onEnter();
    
    // add this layer to concern the keypad msg
    pDirector->getKeypadDispatcher()->addDelegate(this);
}

void CentralAccountLoginLayer::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    pDirector->getKeypadDispatcher()->removeDelegate(this);
    
    CCNode::onExit();
}


bool CentralAccountLoginLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLOG("响应啦........................................");
    return true;
}

void CentralAccountLoginLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralAccountLoginLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralAccountLoginLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CentralAccountLoginLayer::initCentralAccount2UI()
{
    
}

void CentralAccountLoginLayer::onOk(cocos2d::CCObject * pSender)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    pCentralScene->m_pCentralUILayer->setVisible(true);
    
    pCentralScene->removeChild(pCentralScene->m_CentralAccountLoginLayer, false);
    
    pCentralScene->m_CentralAccountLoginLayer = NULL;
}

void CentralAccountLoginLayer::onSina(cocos2d::CCObject * pSender)
{
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    pCentralScene->m_pCentralUILayer->setVisible(true);
    
    pCentralScene->removeChild(pCentralScene->m_CentralAccountLoginLayer, false);
    
    pCentralScene->m_CentralAccountLoginLayer = NULL;
}

std::string CentralAccountLoginLayer::title()
{
    return "text input test";
}

void CentralAccountLoginLayer::addKeyboardNotificationLayer_Username(KeyboardNotificationLayer * pLayer)
{
    m_pNotificationLayer = pLayer;
    s_bg->addChild(pLayer);
}


void CentralAccountLoginLayer::addKeyboardNotificationLayer_Password(KeyboardNotificationLayer * pLayer)
{
    m_pNotificationLayer_password = pLayer;
    s_bg->addChild(pLayer);
}

//////////////////////////////////////////////////////////////////////////
// implement KeyboardNotificationLayer
//////////////////////////////////////////////////////////////////////////

KeyboardNotificationLayer::KeyboardNotificationLayer()
: m_pTrackNode(0)
{
    setTouchEnabled(true);
}

void KeyboardNotificationLayer::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void KeyboardNotificationLayer::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
    CCLOG("TextInputTest:keyboardWillShowAt(origin:%f,%f, size:%f,%f)",
          info.end.origin.x, info.end.origin.y, info.end.size.width, info.end.size.height);
    
    if (! m_pTrackNode)
    {
        return;
    }
    
    CCRect rectTracked = getRect(m_pTrackNode);
    CCLOG("TextInputTest:trackingNodeAt(origin:%f,%f, size:%f,%f)",
          rectTracked.origin.x, rectTracked.origin.y, rectTracked.size.width, rectTracked.size.height);
    
    // if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
    if (! rectTracked.intersectsRect(info.end))
    {
        return;
    }
    
    // 根据数据键盘大小做显示框位置调整
    if (0) {
        // assume keyboard at the bottom of screen, calculate the vertical adjustment.
        float adjustVert = info.end.getMaxY() - rectTracked.getMinY();
        CCLOG("TextInputTest:needAdjustVerticalPosition(%f)", adjustVert);
        
        // move all the children node of KeyboardNotificationLayer
        CCArray * children = getChildren();
        CCNode * node = 0;
        int count = children->count();
        CCPoint pos;
        for (int i = 0; i < count; ++i)
        {
            node = (CCNode*)children->objectAtIndex(i);
            pos = node->getPosition();
            pos.y += adjustVert;
            node->setPosition(pos);
        }
    }
}

// CCLayer function

bool KeyboardNotificationLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    m_beginPos = pTouch->getLocation();
    return true;
}

void KeyboardNotificationLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (! m_pTrackNode)
    {
        return;
    }
    
    CCPoint endPos = pTouch->getLocation();
    
    float delta = 5.0f;
    if (::abs(endPos.x - m_beginPos.x) > delta
        || ::abs(endPos.y - m_beginPos.y) > delta)
    {
        // not click
        m_beginPos.x = m_beginPos.y = -1;
        return;
    }
    
    // decide the trackNode is clicked.
    CCRect rect;
    CCPoint point = convertTouchToNodeSpaceAR(pTouch);
    CCLOG("KeyboardNotificationLayer:clickedAt(%f,%f)", point.x, point.y);
    
    
    
    CentralScene *pCentralScene = SceneManage::GetSceneManageHendle()->m_pCentralScene;
    
    if (m_pTrackNode->getTag() == 0) {
        rect = getRect(pCentralScene->m_CentralAccountLoginLayer->s_account_tf);
    }else{
        rect = getRect(pCentralScene->m_CentralAccountLoginLayer->s_password_tf);
    }
    
    CCLOG("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
          rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    
    this->onClickTrackNode(rect.containsPoint(point));
}


//////////////////////////////////////////////////////////////////////////
// implement TextFieldTTFDefaultTest
//////////////////////////////////////////////////////////////////////////

std::string TextFieldTTFDefaultTest::subtitle()
{
    return "TextFieldTTF with default behavior test";
}

void TextFieldTTFDefaultTest::onClickTrackNode(bool bClicked)
{
    CCTextFieldTTF * pTextField = (CCTextFieldTTF*)m_pTrackNode;
    if (bClicked)
    {
        // TextFieldTTFTest be clicked
        CCLOG("TextFieldTTFDefaultTest:CCTextFieldTTF attachWithIME");
        pTextField->attachWithIME();
    }
    else
    {
        // TextFieldTTFTest not be clicked
        CCLOG("TextFieldTTFDefaultTest:CCTextFieldTTF detachWithIME");
        pTextField->detachWithIME();
    }
}

void TextFieldTTFDefaultTest::onEnter()
{
    KeyboardNotificationLayer::onEnter();
    
    // add CCTextFieldTTF
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCTextFieldTTF * pTextField = CCTextFieldTTF::textFieldWithPlaceHolder("<click here for input>",
                                                                           FONT_NAME,
                                                                           FONT_SIZE);

    
    addChild(pTextField);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // on android, CCTextFieldTTF cannot auto adjust its position when soft-keyboard pop up
    // so we had to set a higher position to make it visable
    pTextField->setPosition(ccp(s.width / 2, s.height/2 + 50));
#else
    pTextField->setPosition(ccp(s.width / 2, s.height/2 + 50));
#endif
    pTextField->setColor(ccWHITE);
    m_pTrackNode = pTextField;
}

void TextFieldTTFDefaultTest::setTrackNodePosition(CCPoint pos)
{
    CCTextFieldTTF * pTextField = (CCTextFieldTTF*)m_pTrackNode;
    pTextField->setPosition(pos);
}


