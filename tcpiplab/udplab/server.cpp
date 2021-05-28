#include <stdio.h>
#include <winsock.h>
#pragma comment(lib,"wsock32.lib") //Winsock API函数库

// Function prototype
void DataGramServer(short nPort);
// 宏定义用来打印错误消息
#define PRINTERROR(s)	\
		fprintf(stderr,"\n%s: %d\n", s, WSAGetLastError())

int main(int argc, char **argv)
{
	WORD wVersionRequested = MAKEWORD(1,1);
	WSADATA wsaData;  //定义通信缓冲区
	int nRet;
	short nPort;
	
	if (argc != 2)//检查命令行参数，第2参数应为端口号
	{
		fprintf(stderr,"\nSyntax: server PortNumber\n");
		return -1;
	}
	nPort = atoi(argv[1]); //从程序运行参数中，取出“端口号”
	// 初始化WinSock通信编程接口，并核对版本号 
	nRet = WSAStartup(wVersionRequested, &wsaData);
	if (wsaData.wVersion != wVersionRequested)
	{	
		fprintf(stderr,"\n Wrong version\n");
		return -1;
	}
	//
	DataGramServer(nPort); 
	//去初始化通信（WinSock接口）
	WSACleanup();
}
////////////////////////////////////////////////////////////
void DataGramServer(short nPort)
{
	// 创建一个UDP数据报socket ，用来接收来至客户端的数据
	SOCKET	ServerSocket;
	ServerSocket = socket(AF_INET,			// Address family
						  SOCK_DGRAM,		// 套接字类型为数据报
						  IPPROTO_UDP);		// UDP协议
	if (ServerSocket == INVALID_SOCKET)
	{
		PRINTERROR("socket()");
		return;
	}
	// 填写地址结构体
	SOCKADDR_IN saServer;		

	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = INADDR_ANY;	//让WinSock 接口提供IP地址
	saServer.sin_port = htons(nPort);		//使用命令行端口
	int nRet;
    // 绑定套接字名字（地址）到socket
	nRet = bind(ServerSocket,				// 套接字
				(LPSOCKADDR)&saServer,		// 我方地址
				sizeof(struct sockaddr));	// 地址结构体大小
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("bind()");
		closesocket(ServerSocket);  //关闭套接字
		return;
	}

	int nLen;
	nLen = sizeof(SOCKADDR);   //计算结构体SOCKADDR的大小（单位为字节）
	char szBuf[256];
	nRet = gethostname(szBuf, sizeof(szBuf)); //获取当前主机的名字
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("gethostname()");
		closesocket(ServerSocket);
		return;
	}
	//显示服务器名字和端口号
	printf("\n本地主机[%s]UDP端口[%d]，正在等候客户端．．．\n",szBuf, nPort);
	//
	// 从客户端接收数据
	//
	memset(szBuf, 0, sizeof(szBuf));     //将szBuf指向的存储区域“清零”
	nRet = recvfrom(ServerSocket,					
				szBuf,						// 数据接收缓冲区
				sizeof(szBuf),					//计算数据接收缓冲区大小
				0,// Flags
				(LPSOCKADDR)&saServer,//套接字地址变量saServer的开始地址，
                                          //函数成功调用后，会记录对方的ip端口号
				&nLen);						
	if (nRet == INVALID_SOCKET)
	{
		PRINTERROR("recvfrom()");
		closesocket(ServerSocket);
		return;
	}
	// 显示所接收的数据
	printf("\n接收数据： %s", szBuf);
	//显示对方主机的IP、端口号
	printf("[%s:%d]\n",inet_ntoa((struct in_addr)saServer.sin_addr),ntohs(saServer.sin_port));

	// 向客户端发送问候数据
	strcpy(szBuf, "See you!");
    printf("发送数据： %s\n", szBuf);
	nRet = sendto(ServerSocket,				 
				szBuf,				// 数据缓冲区开始地址
				strlen(szBuf)+1,			//发送数据长度（字节数）
				0,                      // Flags
				(LPSOCKADDR)&saServer, //套接字地址结构体（存放对方的套接字地址）
				sizeof(struct sockaddr));	 //套接字地址结构体长度
	// 关闭套接字（在退出前）
	closesocket(ServerSocket);  //释放套接字
	return;
}
