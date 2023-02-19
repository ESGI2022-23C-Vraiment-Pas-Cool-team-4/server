
int charToInt(char* str);
void add_user(struct user_node** user_list, char* user_name, char* user_ip) ;
void print_user_list(struct user_node* user_list);

typedef struct{
    char* type;
    char** paramsName;
    char** paramsValue;
    int nbParams;
} query;


// int main(){
    
//     char* a = checklogin();
//     client(a);
//     return 0;
// }


// Structure pour stocker les informations du client
struct user_node {
    char name[256];
    char ip_address[256];
    struct user_node* next;
};