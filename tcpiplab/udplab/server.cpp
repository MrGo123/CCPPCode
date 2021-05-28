#include <stdio.h>
#include <winsock.h>
#pragma comment(lib,"wsock32.lib") //Winsock API������

// Function prototype
void DataGramServer(short nPort);
// �궨��������ӡ������Ϣ
#define PRINTERROR(s)	\
		fprintf(stderr,"\n%s: %d\n", s, WSAGetLastError())

int main(int argc, char **argv)
{
	WORD wVersionRequested = MAKEWORD(1,1);
	WSADATA wsaData;  //����ͨ�Ż�����
	int nRet;
	short nPort;
	
	if (argc != 2)//��������в�������2����ӦΪ�˿ں�
	{
		fprintf(stderr,"\nSyntax: server PortNumber\n");
		return -1;
	}
	nPort = atoi(argv[1]); //�ӳ������в����У�ȡ�����˿ںš�
	// ��ʼ��WinSockͨ�ű�̽ӿڣ����˶԰汾�� 
	nRet = WSAStartup(wVersionRequested, &wsaData);
	if (wsaData.wVersion != wVersionRequested)
	{	
		fprintf(stderr,"\n Wrong version\n");
		return -1;
	}
	//
	DataGramServer(nPort); 
	//ȥ��ʼ��ͨ�ţ�WinSock�ӿڣ�
	WSACleanup();
}
////////////////////////////////////////////////////////////
void DataGramServer(short nPort)
{
	// ����һ��UDP���ݱ�socket ���������������ͻ��˵�����
	SOCKET	ServerSocket;
	ServerSocket = socket(AF_INET,			// Address family
						  SOCK_DGRAM,		// �׽�������Ϊ���ݱ�
						  IPPROTO_UDP);		// UDPЭ��
	if (ServerSocket == INVALID_SOCKET)
	{
		PRINTERROR("socket()");
		return;
	}
	// ��д��ַ�ṹ��
	SOCKADDR_IN saServer;		

	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = INADDR_ANY;	//��WinSock �ӿ��ṩIP��ַ
	saServer.sin_port = htons(nPort);		//ʹ�������ж˿�
	int nRet;
    // ���׽������֣���ַ����socket
	nRet = bind(ServerSocket,				// �׽���
				(LPSOCKADDR)&saServer,		// �ҷ���ַ
				sizeof(struct sockaddr));	// ��ַ�ṹ���С
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("bind()");
		closesocket(ServerSocket);  //�ر��׽���
		return;
	}

	int nLen;
	nLen = sizeof(SOCKADDR);   //����ṹ��SOCKADDR�Ĵ�С����λΪ�ֽڣ�
	char szBuf[256];
	nRet = gethostname(szBuf, sizeof(szBuf)); //��ȡ��ǰ����������
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("gethostname()");
		closesocket(ServerSocket);
		return;
	}
	//��ʾ���������ֺͶ˿ں�
	printf("\n��������[%s]UDP�˿�[%d]�����ڵȺ�ͻ��ˣ�����\n",szBuf, nPort);
	//
	// �ӿͻ��˽�������
	//
	memset(szBuf, 0, sizeof(szBuf));     //��szBufָ��Ĵ洢�������㡱
	nRet = recvfrom(ServerSocket,					
				szBuf,						// ���ݽ��ջ�����
				sizeof(szBuf),					//�������ݽ��ջ�������С
				0,// Flags
				(LPSOCKADDR)&saServer,//�׽��ֵ�ַ����saServer�Ŀ�ʼ��ַ��
                                          //�����ɹ����ú󣬻��¼�Է���ip�˿ں�
				&nLen);						
	if (nRet == INVALID_SOCKET)
	{
		PRINTERROR("recvfrom()");
		closesocket(ServerSocket);
		return;
	}
	// ��ʾ�����յ�����
	printf("\n�������ݣ� %s", szBuf);
	//��ʾ�Է�������IP���˿ں�
	printf("[%s:%d]\n",inet_ntoa((struct in_addr)saServer.sin_addr),ntohs(saServer.sin_port));

	// ��ͻ��˷����ʺ�����
	strcpy(szBuf, "See you!");
    printf("�������ݣ� %s\n", szBuf);
	nRet = sendto(ServerSocket,				 
				szBuf,				// ���ݻ�������ʼ��ַ
				strlen(szBuf)+1,			//�������ݳ��ȣ��ֽ�����
				0,                      // Flags
				(LPSOCKADDR)&saServer, //�׽��ֵ�ַ�ṹ�壨��ŶԷ����׽��ֵ�ַ��
				sizeof(struct sockaddr));	 //�׽��ֵ�ַ�ṹ�峤��
	// �ر��׽��֣����˳�ǰ��
	closesocket(ServerSocket);  //�ͷ��׽���
	return;
}
