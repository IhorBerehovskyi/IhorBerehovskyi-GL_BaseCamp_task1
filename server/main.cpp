#include "server.h"

int main(){
    Server server;
    server.initializeLibrary();
    server.initializeAddress();
    server.createSocket();
    server.bindSocket();
    server.listenSocket();
    server.acceptConnection();
    server.sendCommand();
    server.receiveInfo();
}
