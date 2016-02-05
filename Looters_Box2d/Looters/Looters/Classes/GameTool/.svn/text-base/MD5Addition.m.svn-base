//
//  MD5Addition.m
//  BWMobileSDK
//
//  Created by 宁 王 on 12-9-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


#import "MD5Addition.h" 
#import <CommonCrypto/CommonDigest.h>  

@implementation NSString(MD5Addition)  

- (NSString *) stringFromMD5{  
    
    if(self == nil || [self length] == 0)  
        return nil;  
    
    const char *value = [self UTF8String];  
    
    unsigned char outputBuffer[CC_MD5_DIGEST_LENGTH];  
    CC_MD5(value, strlen(value), outputBuffer);  
    
    NSMutableString *outputString = [[NSMutableString alloc] initWithCapacity:CC_MD5_DIGEST_LENGTH * 2];  
    for(NSInteger count = 0; count < CC_MD5_DIGEST_LENGTH; count++){  
        [outputString appendFormat:@"%02x",outputBuffer[count]];  
    }  
    
    return [outputString autorelease];  
}  

@end  
