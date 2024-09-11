#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int main() {
    if (WSAStartup(MAKEWORD(2, 2), (WSADATA*)malloc(sizeof(WSADATA))) != 0) {
        printf("WSAStartup failed."); return 1;
    }

    char response[100] = "I am the server.";

    // Socket Creation
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address = {AF_INET, htons(9002), {INADDR_ANY}};

    // Connecting the Socket
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    listen(server_socket, 5);

    int client_socket = accept(server_socket, NULL, NULL);
    send(client_socket, response, sizeof(response), 0);
    printf("Message Sent");

    closesocket(server_socket);

    // Clean up Winsock
    WSACleanup();

    return 0;
}