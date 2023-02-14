/*
 * Created by : Charbel SALHAB, Andrei MALICEK, Janin MICHEL-MATHIAS
 * Date : 24/02/2023
 * "program allowing you to create your own hotel with number of rooms and type of room and service offered.
 * The rooms can be reserved by customers according to the criteria of the hotel."
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

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

    fscanf(config_file, "%s %s", ip, &port);

    int sock;
    int p = charToInt(port);

    struct sockaddr_in addr;
    
    socklen_t addr_size;

    char buffer[1024];
    int n;

    //create the TCP server socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if(sock < 0){
        perror("[-]Socket error");
        exit(1);
    }

    printf("[+]TCP server socket created. \n");

    /*
    set up the socket address structure for connecting to a server.

    1-initialize the memory for the address structure to all zeroes.

    2-sets the address family to be used as the Internet Protocol v4.

    3-set the port number to be used for the connection.

    4-set the IP address to be used for the connection using the inet_addr function which converts the passed IP address string to an 32-bit integer.
    */

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(p);
    addr.sin_addr.s_addr = inet_addr(ip);

    //connect to the server
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    printf("[+]Connected to the server.\n");


    bzero(buffer, 1024);
    strcpy(buffer, "HELLO, THIS IS LOGFILE.");
    
    printf("Logfile : %s\n", buffer);
    
    //send data over a socket connection
    send(sock, buffer, strlen(buffer), 0);

    bzero(buffer, 1024);
    
    //receive data over a socket connection
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Server : %s\n", buffer);

    //close the socket, disconnect from the server
    close(sock);
    printf("[+]Disconnected from the server.\n");

    //closing the conf file
    fclose(config_file);
    return 0;
}
