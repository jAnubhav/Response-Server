#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>

void cleanUp(SOCKET client_socket) {
    closesocket(client_socket); WSACleanup();
}

int main() {
    if (WSAStartup(MAKEWORD(2, 2), (WSADATA*)malloc(sizeof(WSADATA))) != 0) {
        printf("WSAStartup failed."); return 1;
    }

    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address = {AF_INET, htons(9002), {INADDR_ANY}};

    if (connect(client_socket, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        printf("Connection Failed."); cleanUp(client_socket); return 1;
    }

    char response[100];
    
    if (recv(client_socket, response, sizeof(response), 0) == SOCKET_ERROR) {
        printf("No Message Recieved");
    } else {
        printf("%s", response);
    }

    cleanUp(client_socket);
    return 0;
}