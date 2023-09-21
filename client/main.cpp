#include "client.h"

int main(){
    Client client;
    client.initializeLibrary();
    client.initializeAddress();
    client.createSocket();
    client.connectToServer();
    client.receiveCommand();
    client.launchApplication();
    client.sendLaunchStatus();
    client.sendStatus();
}
