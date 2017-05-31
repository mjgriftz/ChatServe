//
//  chatclient
// 
//  Created by Marcus Griffiths
//
/*  Description: A chat client that accesses a remote chat server, sends a handle to the server, and exchanges text communication between itself and the server.
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFF 1024

extern int errno;


void getKeyboardInput(char *buffer)
{
    fgets(buffer, MAX_BUFF, stdin);
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == '\n') buffer[i] = '\0';
    }
}
// Takes creates an addrinfo struct to help with constructing a socket from a hostname and port#
int fillAddress(const char *host, const char *port, struct addrinfo **list)
{
    int status;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    if ((status = getaddrinfo(host, port, &hints, list)) == -1)
    {
        fprintf(stderr, "Address error: %s\n", strerror(errno));
        printf("couldn't get address info\n");
    }
    return status;
}


// Attempts to connect to server included in the first addrinfo in list
int connectToServer(struct addrinfo *list)
{
    int sock;
    
    if ((sock = socket(list->ai_family, list->ai_socktype, list->ai_protocol)) == -1)
    {
        fprintf(stderr, "Socket error: %s\n", strerror(errno));
        
    }
    
    if (connect(sock, list->ai_addr, list->ai_addrlen) == -1)
    {
        fprintf(stderr, "Connection error: %s\n", strerror(errno));
        
    }
    return sock;
}

// Sends a string message through the designated socket
void sendMessage(int fd, char *message)
{
    send(fd, message, strlen(message), 0);
}

// Receives a string message through the designated socket
int recvMessage(int fd, char *buffer)
{
    int len = recv(fd, buffer, MAX_BUFF, 0);
    buffer[len] = '\0';
    return len;
}

int main(int argc, const char * argv[]) {
    
    //addrinfo idiom courtesy of Beej's Network Programming Guide
    
    struct addrinfo *addrlist;
    const char* hostName;
    const char* port;
    char clientHandle[MAX_BUFF];
    int sock;
    int len;
    
    hostName = argv[1];
    port = argv[2];
    
    char buff[MAX_BUFF];
    char serverHandle[MAX_BUFF];
    char message[MAX_BUFF];
    
    memset(buff, 0, MAX_BUFF);
    memset(message, 0, MAX_BUFF);
    memset(serverHandle, 0, MAX_BUFF);
    
    //display connection information
    printf("hostName: %s\n", hostName);
    printf("port No.: %s\n", port);
    
    //get user handle
    printf("Please enter your handle: ");
    getKeyboardInput(clientHandle);
    
    //build address
    
    fillAddress(hostName, port, &addrlist);
    sock = connectToServer(addrlist);
    sendMessage(sock, clientHandle);
    
    
    while (!strcmp(serverHandle, ""))
    {
        len = recvMessage(sock, serverHandle);
        //len = recv(sock, serverHandle, MAX_BUFF, 0);
        //serverHandle[len] = '\0';
        printf("connected to %s\n", serverHandle);
    }
    
    
    //Send client handle
    while(strcmp(buff, "/quit")){
        printf("%s> ", clientHandle);
        getKeyboardInput(message);
      /*  fgets(message, MAX_BUFF, stdin);
        for (int i = 0; i < strlen(message); i++) {
            if (message[i] == '\n') message[i] = '\0';
        }*/
        //scanf("%[^\n]%*c", message);
        sendMessage(sock, message);
        if (strcmp(message, "/quit") == 0) break;
        memset(buff, 0, MAX_BUFF);
        while (!strcmp(buff, ""))
        {
            len = recvMessage(sock, buff);
            if (strcmp(buff, "/quit") == 0) break;
            printf("%s> %s\n",serverHandle, buff);
        }
    }
    printf("connection to %s ended\n", serverHandle);
    freeaddrinfo(addrlist);
    close(sock);
    return 0;
}


