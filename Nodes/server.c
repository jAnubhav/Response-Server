#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>

void cleanUp(SOCKET network_socket) {
    closesocket(network_socket); WSACleanup();
}

int main() {
    if (WSAStartup(MAKEWORD(2, 2), (WSADATA*)malloc(sizeof(WSADATA))) != 0) {
        printf("WSAStartup failed."); return 1;
    }

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address = {AF_INET, htons(9002), {INADDR_ANY}};

    if (bind(server_socket, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        printf("Binding Failed."); cleanUp(server_socket); return 1;
    }

    listen(server_socket, 5);
    int client_socket = accept(server_socket, NULL, NULL);

    if (send(client_socket, "Response From Server", 21, 0) == SOCKET_ERROR) {
        printf("Message Not Sent");
    } else {
        printf("Message Sent");
    }

    cleanUp(server_socket);
    return 0;
}