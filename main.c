#include "includes/header.h"
#include "includes/requetes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <unistd.h>

int main(int argc, char **argv) {

    if(detectSetup(argc, argv)){
    if(!findParameters()){
    createDataBase();
    buildDataBase();
    createConfigFile();
    }
    }
  
  query test;
  test.type="GetEmployes";
  test.paramsName = malloc(100*(sizeof(char*)));
  test.paramsValue = malloc(100*(sizeof(char*)));
  
  test.paramsName[0]="id";
  test.paramsValue[0]="1";
  test.paramsName[1]="password";
  test.paramsValue[1]="2";
  test.paramsName[2]="email";
  test.paramsValue[2]="2";
  test.paramsName[3]="role";
  test.paramsValue[3]="0";
  test.nbParams=4;
  createSQLquery(test);
  
    return 1; 
}
    


