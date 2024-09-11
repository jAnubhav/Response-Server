#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <winsock2.h>

int main() {
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), (WSADATA*)malloc(sizeof(WSADATA))) != 0) {
        printf("WSAStartup failed."); return 1;
    }

    // Winsock Initialized
    printf("Success");

    // Clean up Winsock
    WSACleanup();

    return 0;
}