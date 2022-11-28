#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int found = 1, allClosed = 1;
    int time = (int) argv[1];
    int fd[2];
    int codeFind[4];
    pid_t pid[6];

    char letter1 = 'A', letter2 = 'A', letter3 = 'A', letter4 = 'A';

    codeFind[0] = (int) letter1;
    codeFind[1] = (int) letter2;
    codeFind[2] = (int) letter3;
    codeFind[3] = (int) letter4;

    if (pipe(fd)<0){
        perror("Error de creació del pipe fd[]");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < (int) argv[0]; i++) {
        pid[i] = fork();
    }

    while(found != 0 && allClosed != 0) {

        for (int i= 0; i < sizeof(pid); i++) {
            if (pid[i] = 0) {
                close(fd[1]);
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);

                if (fd[0] == codeFind){
                    /*
                    signal(SIGKILL, &functKill) 
                    functkill --- for (sizeof(pid)) {sigkill}
                    */
                }
            } else {
                close(fd[0]);
                if (codeFind[3] == 90){
                    codeFind[3] = 65;
                    if (codeFind[2] == 90) {
                        codeFind[2] = 65;
                        if (codeFind[1] == 90) {
                            codeFind[1] = 65;
                            codeFind[0] += 1;
                        } else {
                            codeFind[1] +=1;
                        }
                    } else {
                        codeFind[2] +=1;
                    }
                } else {
                    codeFind[3] += 1;
                }
                dup2(fd[1],STDOUT_FILENO);
                close(fd[1]);
            }
        } 
    }
    
}


