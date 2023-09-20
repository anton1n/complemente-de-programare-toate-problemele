#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <spawn.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

char **environ;

void print_error(int e_num, char *e_msg) {
    errno = (-1 == e_num ? errno : e_num);
    perror(e_msg);
    exit(EXIT_FAILURE);
}

int main() {
    int choice, verif;
    char filename[100];
    pid_t child_pid, own_pid, parent_pid;

    own_pid = getpid( );
	parent_pid = getppid( );

    printf("Paret id: %jd\nOwn id: %jd\n", (intmax_t)parent_pid, (intmax_t)own_pid);


    printf("Introduceți numele fișierului de intrare: ");
    scanf("%s", filename);

    printf("Selectați opțiunea:\n");
    printf("1. Lansați p1\n");
    printf("2. Lansați p2\n");
    printf("Opțiune: ");
    scanf("%d", &choice);

    char fifoPath[100];
    strcpy(fifoPath,filename);
    fifoPath[strlen(fifoPath)-4] = '\0';
    puts(fifoPath);
    mkfifo(fifoPath, 0666);

    int fd;
    if ((fd = open(filename, O_RDONLY)) == -1) {
        perror("Eroare la deschiderea fișierului");
        exit(EXIT_FAILURE);
    }


    char *argv[] = {NULL, fifoPath, NULL};
    posix_spawnattr_t attr;
    posix_spawn_file_actions_t file_actions;

    verif = posix_spawn_file_actions_init(&file_actions);
    if (0 != verif) {
        print_error(verif, "posix_spawn_file_actions_init");
    }
    verif = posix_spawn_file_actions_addclose(&file_actions, STDIN_FILENO);
    if (0 != verif) {
        print_error(verif, "posix_spawn_file_actions_addclose");
    }

    switch (choice) {
        case 1:
            argv[0] = "./p1";
            break;
        case 2:
            argv[0] = "./p2";
            break;
        default:
            printf("Opțiune invalidă\n");
            exit(EXIT_FAILURE);
    }

    if (posix_spawn(&child_pid, argv[0], &file_actions, &attr, &argv[0], environ)) {
        perror("Eroare la posix_spawn");
        exit(EXIT_FAILURE);
    }

    int status;
    waitpid(child_pid, &status, 0);

    if (WIFEXITED(status)) {
        printf("Procesul copil s-a încheiat cu codul de ieșire: %d\n", WEXITSTATUS(status));
    } else {
        printf("Procesul copil s-a încheiat în mod anormal\n");
    }

    verif = posix_spawn_file_actions_destroy(&file_actions);
    if (0 != verif) {
        print_error(verif, "posix_spawn_file_actions_destroy");
    }

    unlink(fifoPath);
    close(fd);

    return 0;
}
