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
#include "../../includes/header.h"

int charToInt(char* str) {
    int result = 0;
    char currentChar;

    for (int i = 0; i < strlen(str); i++) {
        currentChar = str[i];
        if (currentChar < 48 || currentChar > 57) {
            result = -1;
            break;
        } else {
            result *= 10;
            result += currentChar - 48;
        }
    }

    return result;
}

// Fonction pour ajouter un nouveau client à la liste
void add_user(struct user_node** user_list, char* user_name, char* user_ip) {
    // Créer un nouveau nœud pour le client
    struct user_node* new_node = (struct user_node*) malloc(sizeof(struct user_node));
    strcpy(new_node->name, user_name);
    strcpy(new_node->ip_address, user_ip);
    new_node->next = NULL;

    // Ajouter le nouveau nœud à la liste
    if (*user_list == NULL) {
        // Si la liste est vide, le nouveau nœud devient le premier nœud
        *user_list = new_node;
    } else {
        // Sinon, parcourir la liste jusqu'à la fin et ajouter le nouveau nœud à la fin
        struct user_node* current_node = *user_list;
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = new_node;
    }
}


void print_user_list(struct user_node* user_list) {
    printf("\nListe des utilisateurs :\n");
    struct user_node* current_node = user_list;
    while (current_node != NULL) {
        printf("Nom de l'utilisateur : %s\n", current_node->name);
        printf("Adresse IP de l'utilisateur : %s\n", current_node->ip_address);
        current_node = current_node->next;
    }
}

int server(){

    struct user_node* client_list = NULL;

    char ip[16];
    char port[6];

    // opening the conf file to get the ip address of the server and the port number
    FILE *config_file = fopen("../../conf/server.conf", "r");
    
    if (config_file == NULL) {
        printf("Error opening config file\n");
        return 1;
    }

    fscanf(config_file, "%s %s", ip, port);


    int server_sock, client_sock, logfile_sock;

    struct sockaddr_in server_addr, client_addr, logfile_addr;
    
    socklen_t addr_size;

    char name_buffer[1024];
    //char password_buffer[1024];
    char buffer[1024];
    int n;

    //create the TCP server socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if(server_sock < 0){
        perror("[-]Socket error");
        exit(1);
    }

    //printf("[+]TCP server socket created. \n");

    /*
    set up the socket address structure for connecting to a server.

    1-initialize the memory for the address structure to all zeroes.

    2-sets the address family to be used as the Internet Protocol v4.

    3-set the port number to be used for the connection.

    4-set the IP address to be used for the connection using the inet_addr function which converts the passed IP address string to an 32-bit integer.
    */

    int p = charToInt(port);
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(p);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    //assign or bind a local address and port to a socket
    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if(n < 0){
        perror("[-]Bind error");
        exit(1);
    }

    //printf("[+]Bind to the port number : %d\n", p);

    //a socket that will be used to accept incoming connections
    // 5 -> the maximum number of connections that can be queued for the socket
    listen(server_sock, 5);
    //printf("Listening ...\n");

    while(1){

        //accept, receive and send data over a socket connection
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        //printf("[+]Client connected.\n");
        
        // Get the client's IP address
        struct sockaddr_in* client_address = (struct sockaddr_in*)&client_addr;
        char* client_ip = inet_ntoa(client_address->sin_addr);
        printf("Client IP address: %s\n", client_ip);


        bzero(name_buffer, sizeof(name_buffer));
        // bzero(password_buffer, sizeof(password_buffer));

        recv(client_sock, name_buffer, sizeof(name_buffer), 0);
        printf("Client name: %s\n", name_buffer);

        // recv(client_sock, password_buffer, sizeof(password_buffer), 0);
        // printf("Client password: %s\n\n", password_buffer);

        char* client_name = name_buffer;
        char* client_ipp = client_ip;
        add_user(&client_list, client_name, client_ipp);

        bzero(buffer, 1024);
        strcpy(buffer, query);
        //printf("Server : %s\n", buffer);
        send(client_sock, buffer, strlen(buffer), 0);

        close(client_sock);
        //printf("[+]Client disconnected.\n\n");

        print_user_list(client_list);
    }

    //closing the conf file
    fclose(config_file);

    return 0;
}
