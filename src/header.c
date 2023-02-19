#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include "../includes/header.h"


int detectSetup(int argc, char **argv){

if (argc == 1) {
        printf("Aucun argument n'a été fourni\n");
    }

    int setup_flag = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--setup") == 0) {
            setup_flag = 1;
            break;
        }
    }

    if (setup_flag) {
        printf("L'argument --setup a été trouvé\n");
    } else {
        printf("L'argument --setup n'a pas été trouvé\n");
    }
return setup_flag;
}



int createDataBase(){

    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        return (1);
    }

    if (mysql_real_connect(con, "localhost", "root", "root",
                           NULL, 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        return (1);
    }

    if (mysql_query(con, "CREATE DATABASE hotel"))
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        return (1);
    }

    printf("La base de données hotel a été créée avec succès.\n");
   mysql_close(con);
   

   return 0;
    }
    
    
int buildDataBase(){
       MYSQL *conn;
       char *query; 

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "root", "hotel", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return(1);
    }

       // Création de la table HOTEL
    query = "CREATE TABLE Hotel(id INTEGER PRIMARY KEY AUTO_INCREMENT, nom VARCHAR(30), Adresse VARCHAR(30), nb_chambres INTEGER, nb_etoile INTEGER)";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return(1);
    }

    // Création de la table EMPLOYE
    query = "CREATE TABLE Employes(id INTEGER PRIMARY KEY AUTO_INCREMENT, nom VARCHAR(30), password VARCHAR(100), email VARCHAR(100), role VARCHAR(30))";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return(1);
    }

    // Création de la table droit_acces
    query = "CREATE TABLE droit_acces(id INTEGER REFERENCES Hotel(id), id_2 INTEGER REFERENCES Employes(id), PRIMARY KEY (id,id_2))";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return(1);
    }

    // Création de la table CHAMBRES
    query = "CREATE TABLE Chambres(numero_chambre INTEGER PRIMARY KEY AUTO_INCREMENT, type_chambre VARCHAR(30), prix INTEGER, id INTEGER REFERENCES Hotel(id))";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return(1);
    }

    // Création de la table CLIENTS
    query = "CREATE TABLE Clients(id INTEGER PRIMARY KEY AUTO_INCREMENT, nom VARCHAR(30), adresse VARCHAR(100), telephone INTEGER, date_reservation DATE)";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return(1);
    }

    // Création de la table RESERVATIONS
    query = "CREATE TABLE Reservations(numero_reservation INTEGER PRIMARY KEY AUTO_INCREMENT, date_debut DATE, date_fin DATE, id INTEGER REFERENCES Clients(id))";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return(1);
    }

    // Création de la table est_reserve
    query = "CREATE TABLE est_reserve(numero_chambre INTEGER REFERENCES Chambres(numero_chambre), numero_reservation INTEGER REFERENCES Reservations(numero_reservation), PRIMARY KEY (numero_chambre,numero_reservation))";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return(1);
    }


    mysql_close(conn);

    return 0;
    }
int createFirstAdmin(){

    char nom[30];
    char password[100];
    char email[100];
    char* query = malloc(250*(sizeof(char*)));
    printf("parametrage du compte admin (Obligatoire) : ");

    printf("Entrez votre nom : ");
    scanf("%s", nom);

    printf("Entrez votre mot de passe : ");
    // utilise la fonction getpass pour masquer le mot de passe
    char* password_tmp = getpass("");
    strncpy(password, password_tmp, sizeof(password));

    printf("Entrez votre adresse e-mail : ");
    scanf("%s", email);

    sprintf(query, "INSERT INTO Employes (nom, password, email, role) VALUES ('%s','%s','%s','0');", nom, password, email);

    MYSQL *conn;


    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "root", "hotel", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));

    }
    mysql_close(conn);

    return 1;
}


int createConfigFile(){

    FILE *fp;
    int i;
    char word[] = "config_enable: 1";

    fp = fopen("config.h", "r");
    if (fp == NULL) {
        printf("Fichier config.h non trouvé, création...\n");
        fp = fopen("config.h", "a");
        if (fp == NULL) {
            printf("Impossible de créer le fichier config.h\n");
            return 0;
        }
        fclose(fp);
        printf("Fichier config.h créé avec succès\n");
    } else {
        printf("Fichier config.h déjà existant\n");
    }
    

    fp = fopen("config.h", "a");
    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier config.h\n");
        return 0;
    }

    for (i = 0; i < strlen(word); i++) {
        fputc(word[i], fp);
    }
    fputc('\n', fp);
    fclose(fp);
    
 
    printf("Ajout de config_enable: 1 dans le fichier config.h réussi\n");
    createFirstAdmin();
    
    return 0;
    
}

int findParameters() {
    FILE *fp;
    char line[100];
    char target[] = "config_enable: 1\n";

    fp = fopen("config.h", "r");
    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier config.h\n");
        return 0;
    }

    while (fgets(line, 100, fp) != NULL) {
        if (strcmp(line, target) == 0) {
            printf("La chaîne config_enable: 1 est présente dans le fichier config.h\n");
            fclose(fp);
            return 1;
        }
    }
    printf("La chaîne config_enable: 1 n'est pas présente dans le fichier config.h\n");
    fclose(fp);
    
    return 0;

}


