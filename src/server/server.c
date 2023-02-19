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
#include "../../includes/sockets.h"

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


