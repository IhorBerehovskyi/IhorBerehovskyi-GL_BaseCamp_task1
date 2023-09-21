#ifndef GL_BASECAMP_TASK1_CLIENT_H
#define GL_BASECAMP_TASK1_CLIENT_H

#include <iostream>
#include <thread>
#include <csignal>
#include "unistd.h"

#define PORT 55555
#define IPADDRESS "127.0.0.1"
#define SLEEP_TIME 1
#define STATUS_1 "Launched"
#define STATUS_2 "Closed"

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

class Client{
private:
    int ipAddress;
    int port;
    int socketC;
    pid_t procID;
    SOCKADDR_IN addrIn;
    socklen_t socklen;
    char* command;

public:
    Client();
    ~Client();
    void initializeLibrary();
    void initializeAddress();
    void createSocket();
    void connectToServer();
    void receiveCommand();
    void launchApplication();
    void sendLaunchStatus();
    void sendStatus();
};

#endif //GL_BASECAMP_TASK1_CLIENT_H
