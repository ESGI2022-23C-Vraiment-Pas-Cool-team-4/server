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
#include <arpa/inet.h>

int main(){

    char ip[16];
    int port;

    // opening the conf file to get the ip address of the server and the port number
    FILE *config_file = fopen("server.conf", "r");
    
    if (config_file == NULL) {
        printf("Error opening config file\n");
        return 1;
    }

    fscanf(config_file, "%s %d", ip, &port);


    int server_sock, client_sock, logfile_sock;

    struct sockaddr_in server_addr, client_addr, logfile_addr;
    
    socklen_t addr_size;

    char buffer[1024];
    int n;

    //create the TCP server socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if(server_sock < 0){
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

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    //assign or bind a local address and port to a socket
    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if(n < 0){
        perror("[-]Bind error");
        exit(1);
    }

    printf("[+]Bind to the port number : %d\n", port);

    //a socket that will be used to accept incoming connections
    // 5 -> the maximum number of connections that can be queued for the socket
    listen(server_sock, 5);
    printf("Listening ...\n");

    while(1){

        //accept, receive and send data over a socket connection

        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        printf("[+]Client connected.\n");

        bzero(buffer, 1024);
        recv(client_sock, buffer, sizeof(buffer), 0);
        printf("Client: %s\n", buffer);

        bzero(buffer, 1024);
        strcpy(buffer, "HI THIS IS SERVER. HAVE A NICE DAY!");
        printf("Server : %s\n", buffer);
        send(client_sock, buffer, strlen(buffer), 0);

        close(client_sock);
        printf("[+]Client disconnected.\n\n");

        addr_size = sizeof(logfile_addr);
        logfile_sock = accept(server_sock, (struct sockaddr*)&logfile_addr, &addr_size);
        printf("[+]Logfile connected.\n");

        bzero(buffer, 1024);
        recv(logfile_sock, buffer, sizeof(buffer), 0);
        printf("Logfile: %s\n", buffer);

        bzero(buffer, 1024);
        strcpy(buffer, "HI THIS IS SERVER. HAVE A NICE DAY LOGFILE!");
        printf("Server : %s\n", buffer);
        send(logfile_sock, buffer, strlen(buffer), 0);

        close(logfile_sock);
        printf("[+]logfile disconnected.\n\n");


    }

    //closing the conf file
    fclose(config_file);

    return 0;
}