//
//  TipInfo.cpp
//  Looters
//
//  Created by 王 宁 on 13-1-31.
//
//

#include "TipInfo.h"

TipInfo::TipInfo():no_troops(NULL)
{
    
}

TipInfo::~TipInfo()
{
    
}

bool TipInfo::init( void )
{
    return true;
}


void TipInfo::update(float dt)
{
    this->stopAllActions();
    this->unscheduleAllSelectors();
    
    no_troops->removeFromParentAndCleanup(false);
    no_troops = NULL;
    
    this->removeFromParentAndCleanup(false);
}

void TipInfo::setString(std::string info,CCPoint pos, float time)
{
    if (no_troops == NULL) {
        no_troops = CCLabelTTF::create(info.c_str(), "Marker Felt", 20);
        this->addChild(no_troops, 0);
        no_troops->setColor(ccc3(255,0,0));
        no_troops->setPosition(pos);
        
        this->schedule(schedule_selector(TipInfo::update),time);
    }
}
