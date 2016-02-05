/***************************************************************
 author:     wangning
 write time: 2012.10.20
 function:   DataInputStream
 ***************************************************************/
#ifndef Test_DataInputStream_h
#define Test_DataInputStream_h
#pragma once
#include "cocos2d.h"
USING_NS_CC;

#define BYTE_COUNT          1
#define SHORT_COUNT         2
#define INT_COUNT           4
#define LONG_COUNT          8
#define BOOL_COUNT          1
#define FLOAT_COUNT         4

class DataInputStream {

private:
    int m_curIndex;
    unsigned char* m_data;
    int m_len;
    
private:
    int64_t getValue(int count);
    
public:
    DataInputStream(unsigned char* data, int len);
    void reset();
    
    int8_t      readByte();
    int         readInt();
    int64_t     readLong();
    short       readShort();
    bool        readBool();
    std::string readUTF();
    
//    float   readFloat();
};

#endif
