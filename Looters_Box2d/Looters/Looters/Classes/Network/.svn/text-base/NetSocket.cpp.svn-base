#include "NetSocket.h"

NetSocket::NetSocket()
{
	InitData();
}

NetSocket::~NetSocket()
{
	this->StopSocket();

	for( int i = 0; m_qReceiveData->size(); i++ )
		m_qReceiveData->pop();
	for( int i = 0; m_qSendData->size(); i++ )
		m_qSendData->pop();

	ResetData();

	delete m_qReceiveData;
	delete m_qSendData;
}

void NetSocket::InitData( void )
{
	m_qReceiveData = new std::queue<Recv_struct>;
	m_qSendData = new std::queue<string>;

	m_iDescriptor = 0;
	m_hThread = NULL;

	ResetData();
}

void NetSocket::ResetData( void )
{
	for( int i = 0; m_qSendData->size(); i++ )
		m_qSendData->pop();

	m_bIsConnected = false;
	m_bIsConnecting = false; 
	m_strServerIP = "";
	m_iServerPort = 0;
	
	m_strReceHeap = "";

	ResetSendData();
	ResetReveData();
}

bool NetSocket::IsConnected( void )
{
	return m_bIsConnected;
}

bool NetSocket::IsConnecting( void )
{
	return m_bIsConnecting;
}

bool NetSocket::StartSocket( string strIP, int iPort )
{
	if( m_bIsConnecting )
		return true;

	m_strServerIP = strIP;
	m_iServerPort = iPort;
	StartThread();
	return true;
}

void NetSocket::CloseSocket( void )
{
	if (m_iDescriptor > 0)
	{
#ifdef WIN32
		closesocket(m_iDescriptor);
#else
		close(m_iDescriptor);
#endif
	}

	m_iDescriptor = 0;
	m_bIsConnected = false;
}

void NetSocket::StopSocket( void )
{
	this->CloseSocket();
	this->StopThread();
}

void NetSocket::StartThread( void )
{
	if( m_hThread == NULL )
	{
		
#if WIN32
		//_beginthreadex( NULL, 0, NetSocket::WorkThread, (LPVOID)this, 0, NULL );
		m_hThread = CreateThread(NULL, 0, NetSocket::WorkThread, (LPVOID)this, 0, NULL);
#else
		if (0 != pthread_create(&m_hThread, NULL, NetSocket::WorkThread, (void *)this)){};
#endif
		m_bIsConnecting = true;
	}
}

void NetSocket::StopThread( void )
{
	m_bIsConnecting = false;
	if( m_hThread )
	{
#if WIN32
		WaitForSingleObject(m_hThread, INFINITE);//
		CloseHandle(m_hThread);
		m_hThread = NULL;
#else
		pthread_join(m_hThread, NULL);
		m_hThread = NULL;
#endif

	}
}

#if WIN32
DWORD WINAPI NetSocket::WorkThread(LPVOID lparam)
{
	NetSocket *pThis = (NetSocket*)lparam;
	
	pThis->ConnectServer();

	while( pThis->m_bIsConnected )
	{
		pThis->NetLogic();
		Sleep( 2 );
	}

	return 0;
}
#else
void* NetSocket::WorkThread(void *lpParam)
{
	NetSocket *pThis = (NetSocket*)lpParam;
	pThis->ConnectServer();
	while( pThis->m_bIsConnected )
	{
		pThis->NetLogic();
	}
	return NULL;
}
#endif

void NetSocket::ConnectServer( void )
{
	bool bFinished = false;
	//ResetAllData();
#ifdef WIN32
	WSADATA  Ws;
	if ( WSAStartup(MAKEWORD(2,0), &Ws) != 0 )
	{
		cocos2d::CCLog("load winsocket  error~");
	}
#endif
	do 
	{	
		m_iDescriptor = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
		if(m_iDescriptor <= 0)
		{
			this->CloseSocket();
			cocos2d::CCLog("init socket failed");
			break;
		}
        
		if(!SetSocket())
		{
			this->CloseSocket();
			cocos2d::CCLog("SetSocket() error");
			break;
		}

		struct sockaddr_in sin;
		memset((void *)&sin, 0, sizeof(struct sockaddr_in));
		sin.sin_family = AF_INET;                     
		sin.sin_port = htons(m_iServerPort);        
		sin.sin_addr.s_addr = inet_addr(m_strServerIP.c_str());//IP
		
#ifdef WIN32
		unsigned long ul = 1;
		ioctlsocket(m_iDescriptor, FIONBIO, (unsigned long*)&ul);
#else
		fcntl(m_iDescriptor, F_SETFL,fcntl(m_iDescriptor, F_GETFL)|O_NONBLOCK);
		//  fcntl(st, F_SETFL,fcntl(st,F_GETFL,0)|O_NONBLOCK);
		//if (0 != pthread_create(&thID, NULL, _WorkThread, (void *)this)) break;
#endif
		int connectResult=connect(m_iDescriptor, (struct sockaddr *)&sin, sizeof(struct sockaddr));
		CCLog("connect result~~~~~~~~~~~~~~~~~:%d",connectResult);
		if(NET_SOCKET_ERROR == connectResult)
		{
			int select_return = TestingNet( 6 , 0, 2 ); // 6
			char error = 0;
			#if WIN32
						int errorlen = 0;
			#else
						socklen_t errorlen=sizeof(int);
			#endif
			switch( select_return )
			{
			case 1:
				{
					getsockopt( m_iDescriptor,SOL_SOCKET, SO_ERROR, &error, &errorlen);
					if( error == 0 )
					{
						bFinished = true;
						m_bIsConnecting = false;
						cocos2d::CCLog("connect ok");
					}
				}
				break;
			case 0:
				cocos2d::CCLog("connect out of time");
				break;
			case -1:
				cocos2d::CCLog("connect select error");
				break;

			}
		}else if (connectResult==0){
			    char error = 0;
				#if WIN32
							int errorlen = 0;
				#else
							socklen_t errorlen=sizeof(int);
				#endif
			getsockopt( m_iDescriptor,SOL_SOCKET, SO_ERROR, &error, &errorlen);
			if( error == 0 )
			{
				bFinished = true;
				m_bIsConnecting = false;
				cocos2d::CCLog("connect ok");
			}
			break;
		}else
		{
			break;
		}

	} while(false);

	if(!bFinished)
	{
		cocos2d::CCLog("start socket error");
		this->CloseSocket();
		ResetData();
	}
	m_bIsConnected = bFinished;
}

bool NetSocket::SetSocket( void )
{
	bool bFinished = false;
	if(m_iDescriptor > 0) 
	{
		do {

			int nYes = 1;

			int recvBuf_size = RECV_BUFFER_SIZE;
			int sendBuf_size = SEND_BUFFER_SIZE;

			if(NET_SOCKET_ERROR == setsockopt(m_iDescriptor, IPPROTO_TCP, TCP_NODELAY, (char *)&nYes, sizeof(int)))
			{
				cocos2d::CCLog("change to NoDelay error");
				break;
			}

			if (NET_SOCKET_ERROR == setsockopt(m_iDescriptor, SOL_SOCKET, SO_RCVBUF, (char *)&recvBuf_size, sizeof(int)))
			{
				cocos2d::CCLog("change recv buffer error");
				break;
			}

			if (NET_SOCKET_ERROR == setsockopt(m_iDescriptor, SOL_SOCKET, SO_SNDBUF, (char *)&sendBuf_size, sizeof(int)))
			{
				cocos2d::CCLog("change send buffer error");
				break;
			}


			int iTime = 1000;
			setsockopt(m_iDescriptor, SOL_SOCKET, SO_SNDTIMEO, (char *)&iTime, sizeof(int));

			setsockopt(m_iDescriptor, SOL_SOCKET, SO_RCVTIMEO, (char *)&iTime, sizeof(int));

			//#if !WIN32
			//SO_CONDITIONAL_ACCEPT
			//bool bConditionalAccept=true;
			//setsockopt(m_iDescriptor,SOL_SOCKET,SO_CONDITIONAL_ACCEPT,(const char*)&bConditionalAccept,sizeof(bool));
			//#endif


			bFinished = true;
		} while (false);
	}
	return bFinished;
}

void NetSocket::AddSendQueue( string strdata )
{
	m_qSendData->push( strdata );
}

void NetSocket::SendData( void )
{
	int test_result = TestingNet( 0, 1000, 2 ); // 0

	switch( test_result )
	{
	case 0:
		cocos2d::CCLog("send test out of time");
		break;
	case 1:
		{
			char sendData[SEND_BUFFER_SIZE];
			memset(sendData,0,SEND_BUFFER_SIZE);
			string strToSend = m_strToSend.assign(m_strToSend, m_iHaveSendedSize, m_iToSendSize );//InterceptStr( m_strToSend, m_strToSend.length() );
			m_u32SendPackageLen = m_strToSend.length();
			int iCurrentSendCount = 0;

			if( !m_bSendPageageHead )
			{
				memset(sendData,0,SEND_BUFFER_SIZE);
				PacketProperty pHead;
				swap_4(m_u32SendPackageLen);
				pHead.length = m_u32SendPackageLen;

				//sprintf_s( sendData, "%d", pHead.length );
				memcpy(sendData,(char*)&pHead,sizeof(PacketProperty));
				memcpy(sendData + sizeof(PacketProperty),strToSend.c_str(),strToSend.length());
				m_bSendPageageHead = true;

				CCLog("++++++++++++++++++++++++++++++++++senddataLengh%d",sizeof(PacketProperty) + strToSend.length() );
				iCurrentSendCount = send( m_iDescriptor, sendData, sizeof(PacketProperty) + strToSend.length(),0 );
			}
			else
			{
				memcpy(sendData,strToSend.c_str(),strToSend.length());
				iCurrentSendCount = send( m_iDescriptor, sendData, strToSend.length(),0 );
			}

			if( iCurrentSendCount == -1 )
			{
				cocos2d::CCLog("send_return = -1 error");
				m_bIsConnected = false;
				ResetSendData();
				return;
			}
			if( iCurrentSendCount == 0 )
			{
				CCLog("GXB:  m m Huan chong qu man");
				ResetSendData();
				return;
			}
			if( iCurrentSendCount > 0 )
			{
				m_iToSendSize -=  iCurrentSendCount;
				m_iHaveSendedSize += iCurrentSendCount;	
				if( m_iToSendSize == 0 )
				{
					m_qSendData->pop();
					ResetSendData();
				}
			}
		}
		break;
	case -1:
		{
			m_bIsConnected = false;
			this->CloseSocket();
			ResetData();

			cocos2d::CCLog("send test error");
		}
		break;
	}

}

void NetSocket::ResetSendData( void )
{
	m_u32SendPackageLen = 0;
	m_strToSend = "";
	m_iToSendSize = 0;
	m_iHaveSendedSize = 0;
	m_bSendPageageHead = false;
}

void NetSocket::ReceiveData( void )
{
	char pTempBuffer[RECV_BUFFER_SIZE];
	memset( pTempBuffer, 0, sizeof( RECV_BUFFER_SIZE ) );
//	int iCurrentReceLen = 0;
	int result_select = TestingNet( 0, 1000, 1 );// 0
	switch( result_select )
	{
	case 0:
		//cocos2d::CCLog("receive select out time");
		break;
	case 1:
		{
			//if( FD_ISSET(m_iDescriptor, &fds ) )
			{
				int iCurrentReceLen = recv(m_iDescriptor, pTempBuffer, RECV_BUFFER_SIZE, 0 );
				if( iCurrentReceLen > 0 )
				{
					string tempbuffer(pTempBuffer, iCurrentReceLen );
					m_strReceHeap.clear();
					m_strReceHeap.append( tempbuffer );

					cocos2d::CCLog("receive data ok");
				}
				else if( iCurrentReceLen <= 0 )
				{
					if( errno != EINTR )
					{
						m_bIsConnected = false;
						this->CloseSocket();
						ResetData();

						cocos2d::CCLog("receive connect cut");
					}
				}
			}
		}
		break;
	case NET_SOCKET_ERROR:
		{
			m_bIsConnected = false;
			this->CloseSocket();
			ResetData();

			cocos2d::CCLog("receive select error");
		}
		break;
	}

	if( m_strReceHeap.empty() )
		return;
		
	if( m_bRevePageageHead == false )
	{
		string strHead;
		strHead.assign( m_strReceHeap, 0, 4 );
		m_strReceHeap.erase( 0,4 );
		
		swap_4( strHead );
		int iHeadLen = *((int*)(strHead.c_str()));
		m_u32RecePageageLen = iHeadLen;

		m_bRevePageageHead = true;
	}
	if( m_bRevePageageHead == true && m_iReceivedLen < (int)m_u32RecePageageLen )
	{
		int iLeavingLen = m_u32RecePageageLen - m_iReceivedLen;
		if( (int)m_strReceHeap.length() >= iLeavingLen )
		{
			m_strReceivePackage.append( m_strReceHeap, 0, iLeavingLen );
			m_strReceHeap.erase( 0, iLeavingLen );
			m_iReceivedLen += iLeavingLen;
		}
		else
		{
			m_strReceivePackage.append( m_strReceHeap, 0, m_strReceHeap.length() );
			m_strReceHeap.clear();
			m_iReceivedLen += m_strReceHeap.length();
		}
	}

	if( m_iReceivedLen == m_u32RecePageageLen )
	{
		Recv_struct stRec;
		stRec.ieffectiveLength = m_u32RecePageageLen;
		memset(stRec.data, 0, RECV_BUFFER_SIZE );
		memcpy(stRec.data, m_strReceivePackage.c_str(), m_u32RecePageageLen );
		m_qReceiveData->push( stRec );
		ResetReveData();

		CCLog("received page finish!");
	}
}

void NetSocket::ResetReveData( void )
{
	m_u32RecePageageLen = 0;
	m_strReceivePackage = "";
	m_iReceivedLen = 0;
	m_bRevePageageHead = false;
}

void NetSocket::PopReceiveQueue( void )
{
	m_qReceiveData->pop();
}

Recv_struct NetSocket::GetFrontReceiveData( void )
{
	return m_qReceiveData->front();
}

bool NetSocket::IsEmptyWithReceiveQueue( void )
{
	return m_qReceiveData->empty();
}

void NetSocket::NetLogic( void )
{
	if( m_bIsConnected == false )
		return;

	if( m_iToSendSize == 0 )
	{
		if( !m_qSendData->empty() )
		{
			m_strToSend = m_qSendData->front();
			m_iToSendSize = m_strToSend.length() + sizeof( long );//包体+包头长度
			m_iHaveSendedSize = 0;
		}
	}
	if( m_iToSendSize != 0 )
	{
		SendData();
	}

	ReceiveData();
}

int NetSocket::TestingNet( int iWaitTime, int iwaitTimemilli, int testingType )
{
	if( m_iDescriptor == 0 )
		return 0;

	struct timeval connect_time;
	connect_time.tv_sec = iWaitTime;//Make select wait up to 6 second for data
	connect_time.tv_usec = iwaitTimemilli;// and 0 milliseconds. 

	fd_set set;
	FD_ZERO(&set);
	FD_SET(m_iDescriptor, &set);

	int  select_back = 0;

	if( testingType == 1 )
		select_back = select(m_iDescriptor+1, &set, NULL, NULL, &connect_time);

	if( testingType == 2 )
		select_back = select(m_iDescriptor+1, NULL, &set,NULL, &connect_time);
	
	return select_back;
}

void NetSocket::swap_4( unsigned long &p )
{
	p = (p << 24) |  
		((p << 8) & 0x00ff0000u) |  
		((p >> 8) & 0x0000ff00u) |  
		(p >> 24); 
}

void NetSocket::swap_4( string &p  )
{
	char middle[4];
	memset( middle, 0, sizeof(4) );
	middle[0] = p[3];
	middle[1] = p[2];
	middle[2] = p[1];
	middle[3] = p[0];
	p[0] = middle[0];
	p[1] = middle[1];
	p[2] = middle[2];
	p[3] = middle[3];
}