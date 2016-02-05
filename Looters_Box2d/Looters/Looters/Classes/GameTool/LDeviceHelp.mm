#include "LDeviceHelp.h"
#include "UIDeviceHelp.h"

string LDeviceHelp::getMacAddress()
{
    NSString* _macaddress = [[UIDevice currentDevice] uniqueGlobalDeviceIdentifier];
    string ab([_macaddress UTF8String]);
    return ab;
}
