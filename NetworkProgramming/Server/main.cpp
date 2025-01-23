//Weel-known ports
			//WEB:TCP-80;
			//DHCP:UDP-67, UDP-68;
			//C:\Windows\System32\drivers\etc\services
			//Socket
			//Winsock2.h
			//#pragma comment(lib, "Ws2_32.lib")
			///////////////////////////////////
			/*
				Server:
				1. Initialize Winsock;
				2. Create a Socket;
				3. Bind Socket;
				4. Listen Socked;
				5. Accept connection;
				6. Receive & Send data;
				7. Disonnect;
			*/

#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
using std::cin;
using std::cout;
using std::endl;

#define DEFAULT_PORT	"27015"

#define BUFFER_SIZE 1500

#pragma comment(lib, "Ws2_32.lib")

void main()
{
	setlocale(LC_ALL, "");

	//1. Initialize WinSock:
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);	//(2,2) - Version
	if (iResult != 0)
	{
		cout << "WinSock initialization failed with error #" << iResult << endl;
		return;
	}

	//2. Create Socket:
	addrinfo* result = NULL;
	addrinfo* ptr = NULL;
	addrinfo hInst;

	//2.1. �������� ����� �������� ����:
	ZeroMemory(&hInst, sizeof(hInst));
	hInst.ai_family = AF_INET;
	hInst.ai_socktype = SOCK_STREAM;
	hInst.ai_protocol = IPPROTO_TCP;
	hInst.ai_flags = AI_PASSIVE;

	iResult = GetAddrInfo(NULL, DEFAULT_PORT, &hInst, &result);
	if (iResult != 0)
	{
		cout << "GetAddrInfo failed with error #" << iResult << endl;
		WSACleanup();
		return;
	}

	//2.2. ������� �����:
	SOCKET ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET)
	{
		cout << "Socket error: " << WSAGetLastError() << endl;
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	//3. Binding - ����������� ����� � �����:
	iResult = bind(ListenSocket, result->ai_addr, result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		cout << "Bind failed with error #" << WSAGetLastError() << endl;
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}
	freeaddrinfo(result);	//����� ������ ������� bind() ���������� �� ������ ���� ������ �� �����.

	//4. Listen port:
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		cout << "Listen failed with error #" << WSAGetLastError() << endl;
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}
	cout << "Server started on TCP port " << DEFAULT_PORT << endl;


	//5. Accept connection:
	do
	{
		//CHAR sz_client_name[32];
		CHAR sz_client_addr[16];
		int namelen = 32;
		SOCKADDR client_addr;
		ZeroMemory(&client_addr, sizeof(client_addr));
		SOCKET ClientSocket = accept(ListenSocket, &client_addr, &namelen);
		if (ClientSocket == INVALID_SOCKET)
		{
			cout << "Accept failed with error #" << WSAGetLastError() << endl;
			closesocket(ListenSocket);
			WSACleanup();
			return;
		}
		//getsockname(ClientSocket, &client_socket, &namelen);
		cout << "getsockname error # " << WSAGetLastError() << endl;
		//cout << client_addr.sa_data << endl;
		sprintf
		(
			sz_client_addr, "%i.%i.%i.%i:%i",
			(int)(unsigned char)client_addr.sa_data[2],
			(int)(unsigned char)client_addr.sa_data[3],
			(int)(unsigned char)client_addr.sa_data[4],
			(int)(unsigned char)client_addr.sa_data[5],
			unsigned short(client_addr.sa_data[1]<<16 | client_addr.sa_data[0])
		);
		cout << sz_client_addr << endl;

		//closesocket(ClientSocket);
		//closesocket(ListenSocket);

		//6. Receive & Send data:
		char recvbuffer[BUFFER_SIZE]{};
		int received = 0;
		do
		{
			received = recv(ClientSocket, recvbuffer, BUFFER_SIZE, 0);
			if (received > 0)
			{
				cout << "Bytes received:  \t" << received << endl;
				cout << "Received message:\t" << recvbuffer << endl;
				int iSendResult = send(ClientSocket, "������ Client", received, 0);
				if (iSendResult == SOCKET_ERROR)
				{
					cout << "Send failed with error #" << WSAGetLastError() << endl;
					closesocket(ClientSocket);
					WSACleanup();
					return;
				}
				cout << "Bytes sent: " << iSendResult << endl;
			}
			else if (received == 0)cout << "Connection closing..." << endl;
			else
			{
				cout << "Receive failed with error #" << WSAGetLastError() << endl;
				closesocket(ClientSocket);
				//WSACleanup();
				//return;
			}
		} while (received > 0);

		//7. Disconnection:
		iResult = shutdown(ClientSocket, SD_SEND);
		if (iResult == SOCKET_ERROR)
		{
			cout << "shutdown failed with error #" << WSAGetLastError() << endl;
		}
		closesocket(ClientSocket);
	} while (true);

	WSACleanup();
	system("PAUSE");
}