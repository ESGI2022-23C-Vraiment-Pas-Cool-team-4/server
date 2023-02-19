#include "../includes/header.h"
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