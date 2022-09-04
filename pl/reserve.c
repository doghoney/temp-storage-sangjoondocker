#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TITLE 15
#define MENU 20

#define ID 15
#define NAME 15
#define PHONE 15
#define EMAIL 40
#define BUF 85

#define MAX_USER 100
#define IDLEN 15

void selectmenu(char* name, int argc, char (*argv)[MENU], int func, void (*funv[])(void));
void firstpage();
void manager();
void user();
void addstore();
void modifystore();
void deletestore();

typedef struct{
    char id[ID];
    char name[NAME];
    char phone[PHONE];
    char email[EMAIL];
}USER;

typedef struct{
    int id;
    int roomcnt;
}STORE;

typedef struct{
    int id;
    char rname[RNAME];
    int floor;
    int table;
    int computer;
}ROOM;

char userid[ID];

int main(){
    firstpage();
}

void selectmenu(char* name, int argc, char (*argv)[MENU], int func, void (*funv[])(void)){
    int menu;

    while(1){
        printf("%s\n", name);
        printf("selectmenu menu\n");
        for(int i=0; i<argc; i++)
            printf("    %d. %s\n", i+1, argv[i]);
        printf("        -1. exit\n");
        printf(">>");
        scanf("%d", &menu);
        printf("\n");
        if(menu == -1){
            firstpage();
            return;
        }
        else if(menu<=0 || menu>func){
            printf("wrong input");
            continue;
        }
        funv[menu-1]();
        break;
    }

    firstpage();
}

void firstpage(){
    char name[TITLE] = "[[main menu]]";
    char menu[2][MENU] = {"manager","user"};
    void (*function[2])(void) = {manager, user};
    
    selectmenu(name, 2, menu, 2, function);
}

void manager(){
    char name[TITLE] = "<manager menu>";
    char menu[3][MENU] = {"add store", "modify store", "delete store"};
    void (*function[3])(void) = {addstore, modifystore, deletestore};
    
    selectmenu(name, 3, menu, 3, function);
}

void user(){
    char name[TITLE] = "<user menu>";
    char menu[3][MENU] = {"add store", "modify store", "delete store"};
    void (*function[3])(void) = {addstore, modifystore, deletestore};
    
    char id[ID];
    USER* user[MAX_USER];
    char buf[BUF];
    int usercnt;
    FILE *fp;
    int available;

    memset(userid, '\0', ID);
    fp = fopen("./UserId.dat", "r");
    fseek(fp, 0, SEEK_END);
    usercnt = ftell(fp)/sizeof(USER);
    fseek(fp, 0, SEEK_SET);

    for(int i=0; i<usercnt; i++){
        fread(buf, BUF, 1, fp);
        user[i] = malloc(sizeof(USER));
        memcpy(user[i], buf, BUF);
    }

    do{
        printf("Write your ID(exit:-1) >> ");
        scanf("%s",id);
        available = 0;
        if(!strcmp(id, "-1")){
            firstpage();
            return;
        }
        for(int i=0; i<usercnt; i++){
            if(!strcmp(user[i]->id,id)){
                strcpy(userid, id);
                available = 1;
                break;
            }
        }  
    }while(available==0);

    fclose(fp);

    selectmenu(name, 3, menu, 3, function);
}

void addstore(){
    
}
void modifystore(){}
void deletestore(){}