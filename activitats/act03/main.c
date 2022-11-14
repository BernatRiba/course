#include <stdio.h>
#include "helpers.h"
#include <dirent.h>
#include <stdlib.h>

#define SOTEXT ">ossh "
void functionChoose(char token[], char command[], int counter);

int main(int argc, char *argv[]){
    char command[100];
    int counter = 0;

    printf("%s", &SOTEXT);
    scanf("%[^\n]", &command);
    fflush(stdin);
    
    while (strcmp(command, "exit") != 0) {

        /* Dividim la línia de comandes en diferents "Tokens" i cridem la funció */
        char *token = strtok(command, ";");

        while (token != NULL) {
            
            functionChoose(token, command, counter);
            
            token = strtok(NULL, ";");
            counter++;
        }

        printf("%s", &SOTEXT);
        scanf("%[^\n]", &command);
        fflush(stdin);
    }
}

void functionChoose(char token[], char commands[], int counter) {

    if (strcmp(token, "ls") == 0) 
    {
        if (strstr(token, "<") != NULL || strstr(token, ">") != NULL || strstr(token, "|") != NULL || strstr(token, "&") != NULL ) {
                printf("Impossible to launch command %d:", &counter);
                printf("ls: Not allowed operators [|><&] \n");
        } else {
            DIR *d = opendir(".");
            struct dirent *dentry;
            size_t i=1;
 
            while((dentry=readdir(d))!=NULL)
            {
                printf("%u. %s\n", i, dentry->d_name);
            }
        }
    } 

    else if (strcmp(token, "pwd") == 0)
    {
        char path[200];

        getcwd(path, 200);
        printf("%s\n", path);
    }
    
    else if (strcmp(token, "echo") == 0)
    {
        int found = 0;

        for (int i = 0; i < sizeof(&commands); i++) {
            if (&commands[i] == "\"" && found == 0) {
                found = 1;
                printf("\"");
            } else if (&commands[i] == "\"" && found == 1) {
                found = 0;
                printf("\"");
            } else if (found == 1) {
                printf("%c", commands[i]);
            }
        }  
        printf("\n"); 
    } 

    else if (strcmp(token, "help") == 0)
    {
        printf("#### GTIDIC - UDL - OSSH ##################################\n");
        printf("#                                                         #\n");
        printf("# Type program names and arguments, and hit enter.        #\n");
        printf("# Use the man command for information on other programs.  #\n");
        printf("#                                                         #\n");
        printf("###########################################################\n");
    } 
}