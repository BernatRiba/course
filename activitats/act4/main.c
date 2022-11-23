#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd[2], fd2;
    pipe(fd);
    char** args = malloc(2*sizeof(char*));
    pid_t p1 = fork();
    FILE *fileToWrite;

    for(int i=0; i<2; i++) {
        args[i] = malloc(10*sizeof(char));
    }

    if (pipe(fd) < 0) perror("pipe fd");

    p1 = fork();

    if(p1 == -1) {  
        perror("fork");
        exit(1);
        return EXIT_FAILURE;

    } else if (p1 == 0) {

        close(fd[0]);

        dup2(fd[1], STDOUT_FILENO);
        close(fd[1])

        execlp("whoami", "ls", NULL);

        return EXIT_FAILURE;

    } else if (p1 == 1) {
        
        fd2 = open("./user.txt", O_WRONLY);

        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        dup2(fd2, STDOUT_FILENO);
        close(fd2);

        strcpy(args[0],"grep");

        execlp(args[0], " /etc/passwd",args, NULL);
        return EXIT_FAILURE;
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(p1,0,0);
    return EXIT_SUCCESS;
}