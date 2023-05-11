#include <sys/sem.h>
#include <errno.h>
#include "stdbool.h"
#include "binary_sems.h"
#include "semun.h"

bool bsUseSemUndo = false;
bool bsRetryOnEintr = true;

int initSemAvailable(int semId, int semNum) {
        union semun arg;
        arg.val = 1;
        return semctl(semId, semNum, SETVAL);
}

int initSemInUse(int semId, int semNum) {
        union semun arg;
        arg.val = 0;
        return semctl(semId, semNum, SETVAL);
}

int waitSem(int semId, int semNum) {
        struct sembuf sops;
        sops.sem_num = semNum;
        sops.sem_op = -1;
        sops.sem_flg = SEM_UNDO;
        while (semop(semId, &sops, 1) == -1)
                if (errno != EINTR || !bsRetryOnEintr)
                        return -1;
        return 0;
}

int releaseSem(int semId, int semNum) {
        struct sembuf sops;
        sops.sem_num = semNum;
        sops.sem_op = 1;
        sops.sem_flg = SEM_UNDO;
        return semop(semId, &sops, 1);
}
