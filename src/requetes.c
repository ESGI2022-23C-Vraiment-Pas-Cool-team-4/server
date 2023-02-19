#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "../includes/requetes.h"


enum queryTypes{
	GET ,
	CREATE,
	UPDATE,
	DELETE,
	SEARCH
};

char* createSQLquery(query queries){
int typeOfQuery= determineQuery(queries.type);
char* table= findTableName(queries.type);
int lenght = getLenght(queries.paramsName,queries.paramsValue,typeOfQuery,queries.nbParams);


char* query2 = malloc(lenght*(sizeof(char*)));
char* queryForCreate= malloc(lenght*(sizeof(char*)));
char* queryForUpdate= malloc(lenght*(sizeof(char*)));
char* colonne = malloc(lenght*(sizeof(char*)));
char* typeChambres = malloc(30*(sizeof(char*)));
int nbEtoile = -1;
char* dateDebut = malloc(30*(sizeof(char*)));
char* dateFin = malloc(30*(sizeof(char*)));
int id = -1;
int idIndex= -1;

if(typeOfQuery != 1){

for(int i=0;i<queries.nbParams;i++){
if(strcmp(queries.paramsName[i],"id")==0){
id = charToInt(queries.paramsValue[i]);
idIndex= i;
break;
}
}
}

if(typeOfQuery == CREATE){

    for(int i=0;i<queries.nbParams;i++){
        if(i!=idIndex){
            if(i==0){
                sprintf(queryForCreate, "('%s'", queries.paramsValue[i]);
            }else{
                sprintf(queryForCreate, "%s, '%s'", queryForCreate, queries.paramsValue[i]);
            }
        }
    }
 if(strcmp("Hotel",table)==0){
 colonne="(nom, Adresse, nb_chambres, nb_etoile)";
 }
  if(strcmp("Chambres",table)==0){
 colonne="(type_chambre, prix, id)";
 }
  if(strcmp("Reservations",table)==0){
 colonne="(date_debut, date_fin, id)";
 }
  if(strcmp("Clients",table)==0){
 colonne="(nom, adresse, telephone, date_reservation)";
 }
  if(strcmp("Employes",table)==0){
 colonne="(nom, password, email, role)";
 }
    
 }   
    
if(typeOfQuery == UPDATE){

for(int i=0;i<queries.nbParams;i++){
        if(i!=idIndex){
              if(i==0){
                sprintf(queryForUpdate, "%s=%s", queries.paramsName[i], queries.paramsValue[i]);
            }else{
                sprintf(queryForUpdate, "%s, %s=%s", queryForUpdate, queries.paramsName[i], queries.paramsValue[i]);
            }
        

}
}
}

if(typeOfQuery == UPDATE){
for(int i=0; i<queries.nbParams;i++) {
if(strcmp("type_chambre",queries.paramsName[i])==0){
 typeChambres= queries.paramsValue[i];
 }
  if(strcmp("nb_etoile",queries.paramsName[i])==0){
 nbEtoile= charToInt(queries.paramsValue[i]);
 }
  if(strcmp("date_debut",queries.paramsName[i])==0){
 dateDebut= queries.paramsValue[i];
 }
  if(strcmp("date_fin",queries.paramsName[i])==0){
 dateFin= queries.paramsValue[i] ;
 }
 

sprintf(query2, "SELECT c.*, r.numero_reservation FROM Chambres c INNER JOIN Hotel h ON c.id = h.id LEFT JOIN est_reserve r ON c.numero_chambre = r.numero_chambre LEFT JOIN Reservations res ON r.numero_reservation = res.numero_reservation WHERE h.nb_etoile = %d AND c.type_chambre = '%s' AND ((res.date_debut <= '%s' AND res.date_fin >= '%s')OR r.numero_reservation IS NULL);",nbEtoile, typeChambres, dateDebut, dateFin);
}
}


switch (typeOfQuery) {
        case GET:
            sprintf(query2, "SELECT * FROM %s WHERE id = %d;", table, id);
            break;
        case CREATE:
            sprintf(query2, "INSERT INTO %s %s VALUES %s);", table, colonne, queryForCreate);  
            break;
        case UPDATE:
            sprintf(query2, "UPDATE %s SET %s WHERE id=%d;", table, queryForUpdate, id);
            break;
        case DELETE:
            sprintf(query2, "DELETE FROM %s WHERE id = %d;", table, id);
            break;
    }
    
    printf("%s",query2);
    
    
    MYSQL *conn;


    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "root", "hotel", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    
     if (mysql_query(conn, query2)) {
        fprintf(stderr, "%s\n", mysql_error(conn));

    }
    
    MYSQL_RES *result = mysql_store_result(conn);
MYSQL_ROW row = mysql_fetch_row(result);


    if(strcmp("Hotel",table)==0){
query q = { 0 };
q.type = "SELECT";
q.nbParams = mysql_num_fields(result);
q.paramsName = (char**) malloc(q.nbParams * sizeof(char*));
q.paramsValue = (char**) malloc(q.nbParams * sizeof(char*));

for (int i = 0; i < q.nbParams; i++) {
    q.paramsName[i] = (char*) malloc(31 * sizeof(char));
    q.paramsValue[i] = (char*) malloc(101 * sizeof(char));
}

if (row) {
    for (int i = 0; i < q.nbParams; i++) {
        MYSQL_FIELD *field = mysql_fetch_field_direct(result, i);
        strncpy(q.paramsName[i], field->name, 30);
        strncpy(q.paramsValue[i], row[i], 100);
    }
}

mysql_free_result(result);

// Use the result struct
printf("type: %s, nbParams: %d\n", q.type, q.nbParams);
for (int i = 0; i < q.nbParams; i++) {
    printf("%s: %s\n", q.paramsName[i], q.paramsValue[i]);
}
concatene(&q);

 }
  if(strcmp("Chambres",table)==0){
query q;
q.type = "SELECT";
q.nbParams = mysql_num_fields(result);
q.paramsName = (char**) malloc(q.nbParams * sizeof(char*));
q.paramsValue = (char**) malloc(q.nbParams * sizeof(char*));

for (int i = 0; i < q.nbParams; i++) {
    q.paramsName[i] = (char*) malloc(31 * sizeof(char));
    q.paramsValue[i] = (char*) malloc(101 * sizeof(char));
}

if (row) {
    for (int i = 0; i < q.nbParams; i++) {
        MYSQL_FIELD *field = mysql_fetch_field_direct(result, i);
        strncpy(q.paramsName[i], field->name, 30);
        strncpy(q.paramsValue[i], row[i], 100);
    }
}

mysql_free_result(result);

// Use the result struct
printf("type: %s, nbParams: %d\n", q.type, q.nbParams);
for (int i = 0; i < q.nbParams; i++) {
    printf("%s: %s\n", q.paramsName[i], q.paramsValue[i]);
}
concatene(&q);
 }
  if(strcmp("Reservations",table)==0){
query q;
q.type = "SELECT";
q.nbParams = mysql_num_fields(result);
q.paramsName = (char**) malloc(q.nbParams * sizeof(char*));
q.paramsValue = (char**) malloc(q.nbParams * sizeof(char*));

for (int i = 0; i < q.nbParams; i++) {
    q.paramsName[i] = (char*) malloc(31 * sizeof(char));
    q.paramsValue[i] = (char*) malloc(101 * sizeof(char));
}

if (row) {
    for (int i = 0; i < q.nbParams; i++) {
        MYSQL_FIELD *field = mysql_fetch_field_direct(result, i);
        strncpy(q.paramsName[i], field->name, 30);
        strncpy(q.paramsValue[i], row[i], 100);
    }
}

mysql_free_result(result);

// Use the result struct
printf("type: %s, nbParams: %d\n", q.type, q.nbParams);
for (int i = 0; i < q.nbParams; i++) {
    printf("%s: %s\n", q.paramsName[i], q.paramsValue[i]);
}
concatene(&q);
 }
  if(strcmp("Clients",table)==0){
query q;
q.type = "SELECT";
q.nbParams = mysql_num_fields(result);
q.paramsName = (char**) malloc(q.nbParams * sizeof(char*));
q.paramsValue = (char**) malloc(q.nbParams * sizeof(char*));

for (int i = 0; i < q.nbParams; i++) {
    q.paramsName[i] = (char*) malloc(31 * sizeof(char));
    q.paramsValue[i] = (char*) malloc(101 * sizeof(char));
}

if (row) {
    for (int i = 0; i < q.nbParams; i++) {
        MYSQL_FIELD *field = mysql_fetch_field_direct(result, i);
        strncpy(q.paramsName[i], field->name, 31);
        strncpy(q.paramsValue[i], row[i], 101);
    }
}

mysql_free_result(result);

// Use the result struct
printf("type: %s, nbParams: %d\n", q.type, q.nbParams);
for (int i = 0; i < q.nbParams; i++) {
    printf("%s: %s\n", q.paramsName[i], q.paramsValue[i]);
}

concatene(&q);
}


  if(strcmp("Employes",table)==0){
 query q;
q.type = "SELECT";
q.nbParams = mysql_num_fields(result);
q.paramsName = (char**) malloc(q.nbParams * sizeof(char*));
q.paramsValue = (char**) malloc(q.nbParams * sizeof(char*));

for (int i = 0; i < q.nbParams; i++) {
    q.paramsName[i] = (char*) malloc(31 * sizeof(char));
    q.paramsValue[i] = (char*) malloc(101 * sizeof(char));
}

if (row) {
    for (int i = 0; i < q.nbParams; i++) {
        MYSQL_FIELD *field = mysql_fetch_field_direct(result, i);
        strncpy(q.paramsName[i], field->name, 30);
        strncpy(q.paramsValue[i], row[i], 100);
    }
}

mysql_free_result(result);

// Use the result struct
printf("type: %s, nbParams: %d\n", q.type, q.nbParams);
for (int i = 0; i < q.nbParams; i++) {
    printf("%s: %s\n", q.paramsName[i], q.paramsValue[i]);
}
concatene(&q);
 }
   
    
    mysql_close(conn);


return 0;

}


int getLenght(char** word, char** word2, int type, int nbParameters){


int lenght;
switch (type){
        case GET:
            lenght=27;
            break;
        case CREATE:
            lenght=22;
            break;
        case UPDATE:
            lenght=23;
            break;
        case DELETE:
            lenght=25;
            break;
}


for(int i=0; i<nbParameters; i++){

lenght += strlen(word[i]);
lenght += strlen(word2[i]);

}
return lenght+30;
}


int determineQuery(char* type){
    char *compared = type;
    char *mots[] = {"Get", "Create", "Update", "Delete","Search"};
    int nb_mots = sizeof(mots) / sizeof(char *);

    for(int i = 0; i < nb_mots; i++) {
    if (strstr(compared, mots[i]) != NULL) {
			return i;
			
        }
    }
return 0;
}


char* findTableName(char* type) {
    char *compared = type;
    char *mots[] = {"Hotel", "Chambres", "Reservations", "Clients", "Employes"};
    int nb_mots = sizeof(mots) / sizeof(char *);

    for(int i = 0; i < nb_mots; i++) {
    if (strstr(compared, mots[i]) != NULL) {
			return mots[i];
			
        }
    }
return 0;
    }
    
int charToInt(char* str) { 
 char* endptr;
    long int val = strtol(str, &endptr, 10);  // Utilise strtol pour convertir la chaîne en entier
    
    if (*endptr != '\0') {  // Vérifie si la conversion a échoué
        printf("Erreur : la chaîne de caractères n'est pas un entier valide\n");
        return 0;
    }
    
    return (int)val;
}


char* concatene(query *q)
{
    int taille=8+strlen(q->type)+9+1;
    for(int i=0;i<q->nbParams;i++)
    {
        taille+=3;
        taille+=strlen(q->paramsName[i]);
        taille+=2;
        taille+=strlen(q->paramsValue[i]);
    }
    char* res=(char*)malloc(sizeof(char)*taille);
    res=strcpy(res,"\tquerry: ");
    res=strcat(res,q->type);
    res=strcat(res,"\n\tparams:");
    for(int i=0;i<q->nbParams;i++)
    {
        res=strcat(res,"\n\t\t");
        res=strcat(res,q->paramsName[i]);
        res=strcat(res,": ");
        res=strcat(res,q->paramsValue[i]);
    }
    return res;
}    
