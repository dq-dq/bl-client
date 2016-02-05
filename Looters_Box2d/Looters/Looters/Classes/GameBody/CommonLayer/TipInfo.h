//
//  TipInfo.h
//  Looters
//
//  Created by 王 宁 on 13-1-31.
//
//

#ifndef Looters_TipInfo_h
#define Looters_TipInfo_h
#include "cocos2d.h"
using namespace cocos2d;

class TipInfo: public CCNode
{
public:
    TipInfo();
    ~TipInfo();
    
    CREATE_FUNC(TipInfo);
    virtual bool init();
    
public:
    CCLabelTTF* no_troops;
    
    // info提示内容  pos内容位置  time间隔多长时间消失
    void setString(std::string info,CCPoint pos, float time);
    
    virtual void update( float dt );
};

#endif
