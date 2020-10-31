
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "include/server.h"


// Function designed for chat between client and server.
void func(int sockfd)
{
    char buff[MAX];
    char cClientName[MAX];
    int n;
    int trueOrFalse = 0;

    trueOrFalse;
    read(sockfd, cClientName, sizeof(cClientName));
    printf("Client is: %s \n\r",cClientName);

    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));

        // print buffer which contains the client contents
        printf("\n\rFrom %s: %s\t : ",cClientName, buff);
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n');

        // and send that buffer to client
        write(sockfd, buff, sizeof(buff));

        // if message contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n\r");
            break;
        }
    }
}

// Driver function
int server()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n\r");
        exit(0);
    }
    else
        printf("Socket successfully created..\n\r");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n\r");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n\r");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n\r");
        exit(0);
    }
    else
        printf("Server listening..\n\r");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server acccept failed...\n\r");
        exit(0);
    }
    else
        printf("server acccept the client...\n\r");

    // Function for chatting between client and server
    func(connfd);

    // After chatting close the socket
    close(sockfd); sockfd = -1;
}