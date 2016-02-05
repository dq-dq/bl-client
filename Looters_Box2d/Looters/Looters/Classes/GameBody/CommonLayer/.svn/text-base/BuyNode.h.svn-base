//
//  BuyNode.h
//  Looters
//
//  Created by yisuode on 12-12-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef Looters_BuyNode_h
#define Looters_BuyNode_h

#pragma once
#include "cocos2d.h"

USING_NS_CC;

class BuyNode: public CCNode
{  
    
public:  
    BuyNode();  
    ~BuyNode();  
    
    CREATE_FUNC(BuyNode); 
    virtual bool init(); 
    
    void onBuyApp();

    static BuyNode* sharedBuyNode(void);
    
    
    void setEncodChar(const char * _encod);
    
public:  
    int type;
    int num;
    int Rmb;
    std::string encod;
    
    
}; 


#endif
