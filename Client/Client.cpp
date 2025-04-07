#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    // Initialize Winsock and load the DLL
    SOCKET clientSocket;
    int port = 55055;
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0) {
        cout << "WSAStartup failed with error: " << wsaerr << endl;
        return 1;
    }
    else {
        cout << "WSAStartup succeeded" << endl;
        cout << "status: " << wsaData.szSystemStatus << endl;
    }

    // Create a socket for the client to connect to the server
    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cout << "socket failed with error: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }
    else {
        cout << "socket succeeded" << endl;
    }

    // Set up the server address structure
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientService.sin_port = htons(port);
    if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        cout << "connect failed with error: " << WSAGetLastError() << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    else {
        cout << "connect succeeded" << endl;
    }
    WSACleanup();
    return 0;
}