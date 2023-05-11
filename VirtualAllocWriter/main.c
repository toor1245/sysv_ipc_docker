#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>

#include "shm_sysv.h"
#include "binary_sems.h"
#include "semun.h"

int main() {
        char            *shmp;
        union semun      dummy;
        int              semid, shmid;

        printf("Writer Process test");

        semid = semget(SEM_KEY, 2, IPC_CREAT | OBJ_PERMS);
        if (semid == -1) {
                printf("failed to create sys_v sem");
                exit(EXIT_FAILURE);
        }
        if (initSemAvailable(semid, WRITE_SEM) == -1) {
                printf("initSemAvailable");
                exit(EXIT_FAILURE);
        }
        if (initSemInUse(semid, READ_SEM) == -1) {
                printf("initSemInUse");
                exit(EXIT_FAILURE);
        }

        shmid = shmget(SHM_KEY, 4096, IPC_CREAT | OBJ_PERMS);
        if (shmid == -1) {
                printf("failed to create sys_v shm");
                exit(EXIT_FAILURE);
        }

        shmp = (char *) shmat(shmid, NULL, 0);
        if (shmp == (void *) -1) {
                printf("failed to attach shm_lib memory segment");
                exit(EXIT_FAILURE);
        }

        /* Wait for writer turn. */
        if (waitSem(semid, WRITE_SEM) == -1) {
                printf("waitSem");
                exit(EXIT_FAILURE);
        }

        /* Initialize all chars as 3. */
        for (int i = 0; i < 4095; ++i)
                shmp[i] = '3';
        shmp[4095] = '\0';

        /* Give reader a turn. */
        if (releaseSem(semid, READ_SEM) == -1) {
                printf("releaseSem");
                exit(EXIT_FAILURE);
        }

        if (semctl(semid, 0, IPC_RMID, dummy) == -1) {
                printf("semctl");
                exit(EXIT_FAILURE);
        }

        printf("Writer process");
        return EXIT_SUCCESS;
}
