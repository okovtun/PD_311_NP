/*
Client:
				1. Initialize Winsock;
				2. Create socket;
				3. Connect to Server
				4. Send & Receive data;
				5. Disconnect;
*/
#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<CommCtrl.h>
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
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
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
	hInst.ai_family = AF_UNSPEC;
	hInst.ai_socktype = SOCK_STREAM;
	hInst.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo("192.168.1.100", DEFAULT_PORT, &hInst, &result);
	if (iResult != 0)
	{
		cout << "getaddrinfo() failed with error #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}
	/*printf
	(
		"%i.%i.%i.%i.",
		FIRST_IPADDRESS(result->ai_addr),
		SECOND_IPADDRESS(result->ai_addr),
		THIRD_IPADDRESS(result->ai_addr),
		FOURTH_IPADDRESS(result->ai_addr)
	);*/

	//2.2. Create a Socket:
	SOCKET ConnectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET)
	{
		cout << "Socket creation failed with error #" << WSAGetLastError() << endl;
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	//3. Connecting to Server:
	iResult = connect(ConnectSocket, result->ai_addr, result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		cout << "Connection closed with error #" << WSAGetLastError() << endl;
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}
	freeaddrinfo(result);
	if (ConnectSocket == INVALID_SOCKET)
	{
		cout << "Unable to connect to Server" << endl;
		WSACleanup();
		return;
	}

	//4. Send & Receive data:
	char sendbuffer[BUFFER_SIZE] = "������ Server!";
	bool exit = false;
	do
	{
		char recvbuffer[BUFFER_SIZE]{};
		int buffer_len = strlen(sendbuffer);
		iResult = send(ConnectSocket, sendbuffer, buffer_len, 0);
		if (iResult == SOCKET_ERROR)
		{
			cout << "Send failed with error #" << WSAGetLastError() << endl;
			closesocket(ConnectSocket);
			WSACleanup();
			return;
		}
		cout << "Bytes sent: " << iResult << endl;

		//Close connection:
		if (strcmp(sendbuffer, "Exit") == 0)
		{
			iResult = shutdown(ConnectSocket, SD_BOTH);
			if (iResult == SOCKET_ERROR)
			{
				cout << "shutdown failed with error #" << WSAGetLastError() << endl;
				closesocket(ConnectSocket);
				WSACleanup();
				return;
			}
			exit = true;
		}
		else
		{


			///////////////////////////

			int received = 0;
			//do
			//{
			received = recv(ConnectSocket, recvbuffer, BUFFER_SIZE, 0);
			if (received > 0)
			{
				cout << "Bytes received:  \t" << received << endl;
				cout << "Received message:\t" << recvbuffer << endl;
			}
			else if (received == 0)cout << "Connection closed" << endl;
			else cout << "Receive failed with error #" << WSAGetLastError() << endl;
			//} while (received > 0);

			if (!exit)
				cout << "���� ���������: "; cin.getline(sendbuffer, BUFFER_SIZE);
		}

	} while (!exit);

	//5. Disconnection:
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
		cout << "shutdown failed with error #" << WSAGetLastError() << endl;
	closesocket(ConnectSocket);
	WSACleanup();
	system("PAUSE");
}