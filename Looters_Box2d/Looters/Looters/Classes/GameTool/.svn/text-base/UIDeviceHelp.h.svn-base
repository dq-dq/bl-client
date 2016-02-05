//
//  UIDeviceHelp.h
//  BWMobileSDK
//
//  Created by 宁 王 on 12-9-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIDevice.h>
@interface UIDevice (UIDeviceHelp)

/* 
 *根据mac地址和设备信息获取设备唯一标示（ios5以后的系统中已经停止使用设备标示uniqueIdentifier） 
 */  
- (NSString *) uniqueDeviceIdentifier;  

/* 
 *根据mac地址获取设备唯一标示（ios5以后的系统中已经停止使用设备标示uniqueIdentifier） 
 */  
- (NSString *) uniqueGlobalDeviceIdentifier;  

/* 
 *判断设备是否越狱 
 */  
- (BOOL)isJailbroken;  

@end


@interface UIDevice(Private)  

- (NSString *) macaddress;

@end  
