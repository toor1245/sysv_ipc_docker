#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <stdio.h>
#include <stdlib.h>

#include "shm_sysv.h"
#include "binary_sems.h"

int main() {
        char    *shmp;
        int      shmid, semid;

        semid = semget(SEM_KEY, 0, 0);
        if (semid == -1) {
                printf("semget");
                exit(EXIT_FAILURE);
        }

        shmid = shmget(SHM_KEY, 0, 0);
        if (shmid == -1) {
                printf("shmget");
                exit(EXIT_FAILURE);
        }

        shmp = (char *) shmat(shmid, NULL, SHM_RDONLY);
        if (shmp == (void *) -1) {
                printf("shmat");
                exit(EXIT_FAILURE);
        }

        if (waitSem(semid, READ_SEM) == -1) {
                printf("waitSem");
                exit(EXIT_FAILURE);
        }

        if (releaseSem(semid, WRITE_SEM) == -1) {
                printf("releaseSem");
                exit(EXIT_FAILURE);
        }

        printf("shmp: %s", shmp);

        if (shmdt(shmp) == -1) {
                printf("shmdt");
                exit(EXIT_FAILURE);
        }

        return EXIT_SUCCESS;
}
