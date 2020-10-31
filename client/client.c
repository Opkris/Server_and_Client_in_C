#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h> // for read and write to sockets
#include <arpa/inet.h> // include inet_addr

#include "include/client.h"


#define SA struct sockaddr

void func(int sockfd) {
    char buff[MAX];
    char cClientName[MAX];
    int n;
    int trueOrFalse = 0;

    //client enter a name and send it to the server;
    trueOrFalse++;
    printf("Enter your name: ");
    while ((cClientName[n++] = getchar()) != '\n');
    write(sockfd, cClientName, sizeof(cClientName));

    // infinite loop
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("\n\r%s Enter a String : \n", cClientName);

        n = 0;
        while ((buff[n++] = getchar()) != '\n');

        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("\n\rFrom Server: %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n\r");
            break;
        }
    }

}

int client() {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n\r");
        exit(0);
    } else
        printf("Socket successfully created..\n\r");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    } else
        printf("connected to the server..\n");

    // function for chat
    func(sockfd);

    // close the socket
    close(sockfd);
}