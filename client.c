#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    // Create a socket
    SOCKET network_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (network_socket == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use the server's IP address

    // Connect the socket to the server
    int conn_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    if (conn_status == SOCKET_ERROR) {
        printf("Connection failed: %d\n", WSAGetLastError());
        closesocket(network_socket);
        WSACleanup();
        return 1;
    }

    // Receive data from the server
    char server_response[100];
    int recv_status = recv(network_socket, server_response, sizeof(server_response) - 1, 0);
    if (recv_status == SOCKET_ERROR) {
        printf("Receive failed: %d\n", WSAGetLastError());
    } else {
        server_response[recv_status] = '\0'; // Null-terminate the string
        printf("%s\n", server_response);
    }

    // Close the socket
    closesocket(network_socket);

    // Clean up Winsock
    WSACleanup();

    return 0;
}
