//
//  BuyAppC.m
//  Looters
//
//  Created by yisuode on 12-12-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "BuyAppC.h"
#import "BuyApp.h"
static BuyApp* buyapp = NULL;
BuyAppC::BuyAppC()
{
    buyapp = [[BuyApp alloc] init];
}

BuyAppC::~BuyAppC()
{
    [buyapp release];
}

void BuyAppC::onBuyApp(const char * _str)
{

    NSString* nsStr = [[NSString alloc]initWithUTF8String:_str];
    [buyapp buyapp:nsStr];
    [nsStr release];
    nsStr = NULL;

}
