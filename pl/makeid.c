#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define ID 15
#define NAME 15
#define PHONE 15
#define EMAIL 40
#define BUF 85

typedef struct{
    char id[ID];
    char name[NAME];
    char phone[PHONE];
    char email[EMAIL];
}USER;

int main(){
    FILE *fp;
    USER* usr = malloc(sizeof(USER));
    char buf[BUF];

    fp = fopen("./UserId.dat", "w");
    strcpy(usr->id, "junho");
    strcpy(usr->name, "junho");
    strcpy(usr->phone, "01012345678");
    strcpy(usr->email, "abc@gmail.com");
    memcpy(buf, usr, BUF);
    fwrite(buf, sizeof(char), BUF, fp);

    strcpy(usr->id, "a");
    strcpy(usr->name, "a");
    strcpy(usr->phone, "01012345678");
    strcpy(usr->email, "abc@gmail.com");
    memcpy(buf, usr, BUF);
    fwrite(buf, sizeof(char), BUF, fp);

    strcpy(usr->id, "b");
    strcpy(usr->name, "b");
    strcpy(usr->phone, "01012345678");
    strcpy(usr->email, "abc@gmail.com");
    memcpy(buf, usr, BUF);
    fwrite(buf, sizeof(char), BUF, fp);

    fclose(fp);
}