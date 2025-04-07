#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    // Initialize Winsock and load the DLL
    SOCKET serverSocket, acceptSocket;
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

    // Create a socket for the server to listen on
    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        cout << "socket failed with error: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }
    else {
        cout << "socket succeeded" << endl;
    }

    // Set up the server address structure
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(port);
    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        cout << "bind failed with error: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    else {
        cout << "bind succeeded" << endl;
    }

    // Start listening for incoming connections
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        cout << "listen failed with error: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    else {
        cout << "listen succeeded" << endl;
    }

    // Accept a connection from a client
    acceptSocket = accept(serverSocket, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET) {
        cout << "accept failed with error: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    else {
        cout << "accept succeeded" << endl;
    }
    WSACleanup();
    return 0;
}