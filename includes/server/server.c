/*
 * Created by : Charbel SALHAB, Andrei MALICEK, Janin MICHEL-MATHIAS
 * Date : 24/02/2023
 * "program allowing you to create your own hotel with number of rooms and type of room and service offered.
 * The rooms can be reserved by customers according to the criteria of the hotel."
 */

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
#include "../sockets.h"

// function executed by a thread (un thread est un fil d'exécution dans un processus)
// send a msg for the connected user to the socket

void *function(void *arg){
    //convert the received argument to an integer
    int socket = *(int *)arg;

    char msg[] = "quel est votre login et mot de passe ?";
    User user;

    //send the message to the socket
    send(socket, msg, strlen(msg) + 1, 0);
    //receive data from the socket
    recv(socket, &user, sizeof(user), 0);
    
    printf("%s bienvenue au programme\n", user.nom);
    
    //close the socket
    close(socket);
    //free the allocated memory
    free(arg);
    //finish the thread
    pthread_exit(NULL);

}

int charToInt(char* str){
    int result = 0;
    char currentChar;

    for(int i = 0; i < strlen(str); i++){
        currentChar = str[i];
        if(currentChar < 48 || currentChar > 57){
            result = -1;
            break;
        }else {
            result *= 10;
            result += currentChar - 48;
        }
    }

    return result;
}

int main(){

    char ip[16];
    char *port;

    // opening the conf file to get the ip address of the server and the port number
    FILE *config_file = fopen("server.conf", "r");
    
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

    pthread_t threads[5];

    for(int i = 0; i < 5; i++){
        
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

    for(int i = 0; i < 5; i ++){
        
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
