#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include "includes/sockets.h"

int main(){

    char ip[16];
    char *port = NULL;

    // opening the conf file to get the ip address of the server and the port number
    FILE *config_file = fopen("conf/server.conf", "r");
    
    if (config_file == NULL) {
        printf("Error opening config file\n");
        return 1;
    }

    fscanf(config_file, "%s %s", ip, port);

    int p = charToInt(port);

    //create the TCP server socket
    int sockServer = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addrServer;

    /*
    1-sets the address family to be used as the Internet Protocol v4.

    2-set the port number to be used for the connection.

    3-set the IP address to be used for the connection using the inet_addr function which converts the passed IP address string to an 32-bit integer.
    */
    addrServer.sin_addr.s_addr = inet_addr(ip);
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(p);

    //assign or bind a local address and port to a socket
    bind(sockServer, (const struct sockaddr *)&addrServer, sizeof(addrServer));


    //a socket that will be used to accept incoming connections
    // 5 -> the maximum number of connections that can be queued for the socket
    listen(sockServer, 5);

    pthread_t threads[20];

    for(int i = 0; i < 20; i++){
        
        //accept, receive and send data over a socket connection
        struct sockaddr_in addrClient;
        socklen_t csize = sizeof(addrClient);
        int socketClient = accept(sockServer, (struct sockaddr *)&addrClient, &csize);

        //allocates a memory area to store an integer
        int *arg = malloc(sizeof(int));
        //stores the value of socketClient in the allocated memory area
        *arg = socketClient;

        //create a new thread and start the execution of the function function
        pthread_create(&threads[i],NULL, function, arg);

    }

    for(int i = 0; i < 20; i ++){
        
        /*
            pthread_join blocks execution of the calling thread until the specified thread has terminated.
            this ensures that the calling thread can access resources shared by the terminated thread without risk of data corruption.
        */
       
        pthread_join(threads[i], NULL);

    }
    
    //close the server socket
    close(sockServer);
    //closing the conf file
    fclose(config_file);
    return 0;
}