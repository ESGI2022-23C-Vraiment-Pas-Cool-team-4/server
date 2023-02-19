typedef struct{
    char* type;
    char** paramsName;
    char** paramsValue;
    int nbParams;
} query;



#ifndef UNTITLED4_HEADER_H
#define UNTITLED4_HEADER_H
query* deconcatene(char* s);
char* concatene(query *q);
char* createSQLquery(query queries);
int determineQuery(char* type);
char* findTableName(char* type);
int getLenght(char** word, char** word2, int type, int nbParameters);
int charToInt(char* str);
int createFirstAdmin();
#endif 
