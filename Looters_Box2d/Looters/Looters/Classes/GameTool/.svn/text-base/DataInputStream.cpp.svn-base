#include <iostream>
#include "DataInputStream.h"

DataInputStream::DataInputStream(unsigned char* data, int len)
{
    m_curIndex = 0;
    m_len = len;
    m_data = data;
}

void DataInputStream::reset()
{
    m_curIndex = 0;
}

int8_t DataInputStream::readByte()
{
    assert(m_curIndex+BYTE_COUNT <= m_len);
    return getValue(BYTE_COUNT);
}

int DataInputStream::readInt()
{
    assert(m_curIndex+INT_COUNT <= m_len);
    return getValue(INT_COUNT);
}


long long int DataInputStream::readLong()
{
    assert(m_curIndex+LONG_COUNT <= m_len);
    return getValue(LONG_COUNT);
}

short DataInputStream::readShort()
{
    assert(m_curIndex+SHORT_COUNT <= m_len);
    return getValue(SHORT_COUNT);
}

bool DataInputStream::readBool()
{
    assert(m_curIndex+BOOL_COUNT <= m_len);
    return getValue(BOOL_COUNT);
}

std::string DataInputStream::readUTF()
{
    int len = getValue(2);
    assert(m_curIndex+len <= m_len);
    
    std::string str = "";
    
    if(len){
        char text[len+1];
        memset(text, 0, len+1);
        memcpy(text, &m_data[m_curIndex], len);
        str = text;
        m_curIndex += len;
    }
    return str;
}

/**
 * 31       符号位.
 * 22-30    指数位.
 * 0-22     尾数部分.
 */
 
//float DataInputStream::readFloat()
//{
//    int8_t a4 = m_data[m_curIndex++];
//    int8_t a3 = m_data[m_curIndex++];
//    int8_t a2 = m_data[m_curIndex++];
//    int8_t a1 = m_data[m_curIndex++];
//    
//    if(a4 & 0x80){//符号位
//        
//    }
//    return 1;
//}

int64_t DataInputStream::getValue(int count)
{
    int64_t iValue = 0;
    for (int i=count-1; i>=0; i--) {
        int tmp = m_data[m_curIndex++];
        iValue |= tmp<<(i*8);
    }
    return iValue;
}









