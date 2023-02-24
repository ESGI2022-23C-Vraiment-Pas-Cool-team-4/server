#include "includes/header.h"
#include "includes/requetes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 10000

int main(int argc, char **argv) {

    if(detectSetup(argc, argv)){
    if(!findParameters()){
    createDataBase();
    buildDataBase();
    createConfigFile();
    }
    }
  
//  query test;
//   test.type="DeleteEmployes";
//   test.paramsName = malloc(100*(sizeof(char*)));
//   test.paramsValue = malloc(100*(sizeof(char*)));
  
//   test.paramsName[0]="id";
//   test.paramsValue[0]="37";
//   test.paramsName[1]="password";
//   test.paramsValue[1]="papa";
//   test.paramsName[2]="email";
//   test.paramsValue[2]="papa";
//   test.paramsName[3]="role";
//   test.paramsValue[3]="0";
//   test.nbParams=1;
//   createSQLquery(test);
  
//     return 1;  ###### pour tester car deconcatene ne fonctionne pas #########################
    
#define PORT 10000

int main(int argc, char **argv) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("141.94.70.142");
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
 if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
 puts("en attente de requettes...");
    // Accept incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
   
    // Send message to client
    // Receive message from client
    while(1){
         // Listen for incoming connections
   

    read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    }

    // Close sockets
    close(new_socket);
    close(server_fd);

    return 0;
}

    
 
}



    


