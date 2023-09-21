#ifndef GL_BASECAMP_TASK1_SERVER_H
#define GL_BASECAMP_TASK1_SERVER_H

#include <iostream>
#include <thread>
#include "unistd.h"
#define PORT 55555
#define IPADDRESS "127.0.0.1"

#ifdef linux
    #include "sys/socket.h"
    #include "sys/types.h"
    #include "netinet/in.h"
    #include "arpa/inet.h"

    #define SOCKADDR_IN struct sockaddr_in
    #define SOCKADDR struct sockaddr
#elif _WIN32
    #include  <winsock2.h>
    #define socklen_t int
    #pragma comment(lib, "ws2_32.lib")
#endif

class Server{
private:
    int ipAddress;
    int port;
    int socketS;
    int connectionSocket;
    SOCKADDR_IN addrIn;
    SOCKADDR addr;
    socklen_t socklen;
    std::string command;

public:
    Server();
    ~Server();
    void initializeLibrary();
    void initializeAddress();
    void createSocket();
    void bindSocket();
    void listenSocket();
    void acceptConnection();
    void sendCommand();
    void receiveInfo();
};



#endif //GL_BASECAMP_TASK1_SERVER_H
