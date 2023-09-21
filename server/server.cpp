#include "server.h"

Server::Server() {
    std::cout << "Server started" << std::endl;
}

Server::~Server() {
#ifdef linux
    close(socketS);
    close(connectionSocket);
#elif _WIN32
    closesocket(socket);
    closesocket(connectionSocket);
    WSACleanup();
#endif
}

void Server::initializeLibrary(){
#ifdef _WIN32
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    WSAStartup(DLLVersion, &wsaData);
#endif
}

void Server::initializeAddress(){
    this->addrIn.sin_addr.s_addr = inet_addr(IPADDRESS);
    this->addrIn.sin_port = htons(PORT);
    this->addrIn.sin_family = AF_INET;
}

void Server::createSocket(){
    this->socketS = socket(AF_INET, SOCK_STREAM, 0);
    if(socketS == -1){
        std::cerr << "Error: Failed to create socket" << std::endl;
        exit(1);
    }
}

void Server::bindSocket(){
    if(bind(socketS, (SOCKADDR*)&addrIn, sizeof(addrIn)) == -1) {
        std::cerr << "Error: Failed to bind socket";
        exit(1);
    }
}

void Server::listenSocket(){
    if(listen(socketS, 1) == -1){
        std::cerr << "Error: Failed to listen on socket";
        exit(1);
    }
}

void Server::acceptConnection(){
    this->socklen = sizeof(addr);
    this->connectionSocket = accept(socketS, (SOCKADDR*)&addr, &socklen);

    if(this->connectionSocket == -1) {
        std::cerr << "Error: Failed to accept the connection";
        exit(1);
    }
}

void Server::sendCommand(){
    std::cout << "Write the application name to start it\n";
    std::cout << "For example: zoom\n";
    std::getline(std::cin, command);

    int msgSize = command.size();

    if(send(connectionSocket, (void*)&msgSize, sizeof(int), 0) == -1){
        std::cerr << "Error: Failed to send message size";
        exit(1);
    }

    if(send(connectionSocket, command.c_str(), msgSize, 0) == -1){
        std::cerr << "Error: Failed to send message";
        exit(1);
    }
}

void Server::receiveInfo(){
    int msgSize;

    while (true) {
        if (recv(connectionSocket, (void*) &msgSize, sizeof(int), 0) == -1) {
            std::cerr << "Error: Failed to receive message size";
            exit(1);
        }

        if (msgSize == 0) {
            std::cerr << "Client disconnected" << std::endl;
            break;
        }

        char *msg = new char[msgSize];
        if (recv(connectionSocket, msg, msgSize, 0) == -1) {
            std::cerr << "Error: Failed to receive message";
            exit(1);
        }
        std::cout << msg << std::endl;
        delete[] msg;
    }
}
