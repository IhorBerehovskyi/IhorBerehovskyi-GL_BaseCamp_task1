#include "client.h"
#include <sys/wait.h>


Client::Client(){
    std::cout << "Client started" << std::endl;
}

Client::~Client(){
#ifdef linux
    close(socketC);
    kill(procID, SIGTERM);
    waitpid(procID, nullptr, WNOHANG);
#elif _WIN32
    closesocket(socketC);
    WSACleanup();
#endif
}

void Client::initializeLibrary(){
#ifdef _WIN32
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    WSAStartup(DLLVersion, &wsaData);
#endif
}

void Client::initializeAddress(){
    this->addrIn.sin_addr.s_addr = inet_addr(IPADDRESS);
    this->addrIn.sin_port = htons(PORT);
    this->addrIn.sin_family = AF_INET;
}

void Client::createSocket(){
    this->socketC = socket(AF_INET, SOCK_STREAM, 0);
    if(socketC == -1){
        std::cerr << "Error: Failed to create socket" << std::endl;
        exit(1);
    }
}

void Client::connectToServer(){
    socklen = sizeof(addrIn);
    if(connect(socketC, (SOCKADDR*)&addrIn, socklen) == -1) {
        std::cerr << "Error: Failed to connect to the sever" << std::endl;
        exit(1);
    }
}

void Client::receiveCommand(){
    int msgSize;

    if(recv(socketC, (void*)&msgSize, sizeof(int), 0) == -1){
        std::cerr << "Error: Failed to send message size";
        exit(1);
    }

    this->command = new char[msgSize];
    if(recv(socketC, command, msgSize, 0) == -1){
        std::cerr << "Error: Failed to send message";
        exit(1);
    }
    std::cout << command << std::endl;
}

void Client::launchApplication(){

    procID = fork();
    if (procID == 0) {
        if (execlp(command, command, nullptr) == -1) {
            exit(EXIT_FAILURE);
        }
    }
}

void Client::sendLaunchStatus(){
    sleep(SLEEP_TIME);

    std::string status = STATUS_2;
    int result = waitpid(procID, nullptr, WNOHANG);
    if(result == 0) {
        status = STATUS_1;
    }

    int msgSize = status.size();

    if(send(socketC, (void*)&msgSize, sizeof(int), 0) == -1){
        std::cerr << "Error: Failed to send message size";
        exit(1);
    }

    if(send(socketC, status.c_str(), msgSize, 0) == -1){
        std::cerr << "Error: Failed to send message";
        exit(1);
    }
}

void Client::sendStatus(){

    std::string status = "Running";

    int msgSize = status.size();

    while(true){
        if(waitpid(procID, nullptr, WNOHANG) == 0){
            if(send(socketC, (void*)&msgSize, sizeof(int), 0) == -1){
                std::cerr << "Error: Failed to send message size";
                exit(1);
            }

            if(send(socketC, status.c_str(), msgSize, 0) == -1){
                std::cerr << "Error: Failed to send message";
                exit(1);
            }
            sleep(SLEEP_TIME);
        }else{
            break;
        }
    }

    status = "Closed";
    msgSize = status.size();
    if(send(socketC, (void*)&msgSize, sizeof(int), 0) == -1){
        std::cerr << "Error: Failed to send message size";
        exit(1);
    }

    if(send(socketC, status.c_str(), msgSize, 0) == -1){
        std::cerr << "Error: Failed to send message";
        exit(1);
    }
    msgSize = 0;

    if(send(socketC, (void*)&msgSize, sizeof(int), 0) == -1){
        std::cerr << "Error: Failed to send message size";
        exit(1);
    }

}

