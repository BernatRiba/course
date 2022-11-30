#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void functKill(int signum, int ended, pid_t pid){
    kill(getpid(), signum);
    ended = 0;
    printf("**********DING DONG");
    for (int i=0; i < sizeof(pid); i++) {
        printf("El jugador[%d] ha quedat atrapat i surt del EscapeRoom[%d].\n", pid[i], getpid());
    }
    printf("--- Els jugadors han perdut la partida. Fins aviat.");
}

int main(int argc, char *argv[])
{
    int ended = 1, typeCode = 0;
    int time = (int) argv[1];
    int fd[2];
    char* b[4];
    pid_t pid, pidFather = getpid();

    if (argc != 4) {
        printf("Nombre incorrecte d'arguments, s'han donat %d de 3 requerits", argc -1);
        return EXIT_FAILURE;
    }

    if (pipe(fd)<0){
        perror("Error de creació del pipe fd[]");
        return EXIT_FAILURE;
    }

    pid = malloc((int) argv[2] * sizeof(pid_t));

    printf("--- Entren %d jugadors a la sala. \n", (int) argv[2]);
    printf("--- La paraula a endevinar és: %s. \n", argv[3]);

    for (int i=0; i < sizeof(pid); i++) {
        pid[i] = fork();
        printf("EscapeRoom[%d] ha entrat el jugador [%d].\n", pidFather, pid[i]);
    }

    while(ended != 0) {

        if (getpid() == pidFather) {
            signal(SIGALRM, &functKill(SIGKILL, ended, pid));

            close(fd[1]);
            read(fd[0], b, sizeof(b));
            close(fd[0]);

            if (strstr(fd[0], argv[3])) {
                kill(pidFather, SIGKILL);
                ended = 0;

                printf("--- Els jugadors obren el candau amb la paraula: %s. \n", argv[3]);

                for (int i=0; i < sizeof(pid); i++) {
                    printf("El jugador[%d] ha escapat i surt del EscapeRoom[%d].\n", pid[i], pidFather);
                }
                printf("Els jugadors han guanyat la partida en %d segons", time);
            }
            alarm(time);

        } else {
            if (typeCode = 0) {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                for (int i = 0; i < sizeof(b); i++) {
                    b[i] = 97 + rand() % (122 - 97);
                }
                printf("%s", b);
                close(fd[1]);
                typeCode = 1;
            } else {
                close(fd[0]);
                for (int i = 0; i < sizeof(b); i++) {
                    b[i] = 65 + rand() % (90 - 65);
                }
                printf("%s", b);
                close(fd[1]);
                typeCode = 0;
            }
        }
    }
    close(fd[0]);
    close(fd[1]);
    wait(pidFather, 0, 0);
    free(pid);
    return EXIT_SUCCESS;
    
}