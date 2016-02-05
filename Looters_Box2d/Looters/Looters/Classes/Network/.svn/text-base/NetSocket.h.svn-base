/******************************************************************************
*created:		2012/4/13
*created:		12:06
*author:		wangning
*purpose:		网络连接
********************************************************************************/
#pragma once 

#ifdef WIN32
#include <Windows.h>
#include <atlstr.h>
#pragma comment (lib, "WS2_32.lib")
#else
#include <memory.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>  // sockaddr_in结构体调用
#include <arpa/inet.h>   // 数据顺序转换调用
#include <unistd.h>      // close(); 调用
#include <netdb.h>       // gethostbyname();调用
#include <errno.h>       // 错误返回标志
#include <fcntl.h>
#include <time.h>
#include <netinet/tcp.h>
#include <sys/types.h>
#endif

#include <queue> 
#include <string>
#include <vector>
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;


// 套接字制定返回错误
#ifndef NET_SOCKET_ERROR    
#define NET_SOCKET_ERROR -1
#endif

// http一次读取和发送的数据量
#ifndef MAX_HTTP_BUFFER 
#define MAX_HTTP_BUFFER (3 * 1024)
#endif

// socket一次接受的数据量
#ifndef RECV_BUFFER_SIZE 
#define RECV_BUFFER_SIZE (32 * 1024)
#endif

// socket一次发送的数据量
#ifndef	SEND_BUFFER_SIZE 
#define SEND_BUFFER_SIZE (32 * 1024)
#endif

#ifndef MAX_SOCKET_SIZE
#define MAX_SOCKET_SIZE 65536
#endif

// 包头的长度
#ifndef GET_PACKAGE_HEAD 
#define GET_PACKAGE_HEAD 4
#endif

struct Recv_struct
{
	int ieffectiveLength;
	char data[RECV_BUFFER_SIZE];
};

#define DELAYER 0xe2
#define UNDELAYER 0xe3

class NetSocket
{
public:
	//发送head用的结构体
	struct PacketProperty
	{
		unsigned long length ;
	};

	NetSocket();
	~NetSocket();

private:
	//是否在连接状态
	bool m_bIsConnected;
	//是否在网络连接中
	bool m_bIsConnecting;
	//连接服务器IP
	string m_strServerIP;
	//连接服务器端口
	int m_iServerPort;
	//接收消息队列 receive
	std::queue<Recv_struct> *m_qReceiveData;
	//发送消息队列 m_qSendData
	std::queue<string> *m_qSendData;
    //套接字描述符
	int m_iDescriptor;

	//发送包体长度
	unsigned long m_u32SendPackageLen;
	//要发送的字符串
	string m_strToSend;
	//还剩余要发送的字符串长度
	int m_iToSendSize;
	//已经发送的字符串长度
	int m_iHaveSendedSize;
	//是否发送包头
	bool m_bSendPageageHead;
	
	//接收包体长度
	unsigned long m_u32RecePageageLen;
	//接收的数据包字符
	string  m_strReceivePackage;
	//已接收的字符长度
	int m_iReceivedLen;
	//是否已接收数据包头
	bool m_bRevePageageHead;
	//接受数据的数据堆
	string m_strReceHeap;
	
#if WIN32
	HANDLE m_hThread;
	static DWORD WINAPI WorkThread(LPVOID lparam);
#else
	pthread_t m_hThread;
	static void *WorkThread(void *lpParam);
#endif

public:
	//开启网络连接
	bool StartSocket( string strIP, int iPort );
	//终止网络连接
	void StopSocket();
	//发送逻辑
	void NetLogic( void );
	//获得是否在联网状态
	bool IsConnected( void );
	//是否在尝试连接中
	bool IsConnecting( void );
	//加入到发送队列
	void AddSendQueue( string strdata );
	//弹出顶层消息
	void PopReceiveQueue( void );
	//获得顶层消息数据
	Recv_struct GetFrontReceiveData( void );
	//接收队列是否为空
	bool IsEmptyWithReceiveQueue( void );

private:
	//初始化数据
	void InitData( void );
	//重设数据
	void ResetData( void );
	//关闭socket
	void CloseSocket( void );
	//开启网络连接线程
	void StartThread( void );
	//终止网络连接线程
	void StopThread( void );

	//连接服务器
	void ConnectServer( void );
	//设置套接字
	bool SetSocket( void );

	//发送数据
	void SendData( void );
	void ResetSendData( void );

	//接受数据
	void ReceiveData( void );
	void ResetReveData( void );

	//测试网络
	int TestingNet( int iWaitTime, int iwaitTimemilli, int testingType );

	//大小头转换
	void swap_4( unsigned long &p);
	void swap_4( string &p );

};