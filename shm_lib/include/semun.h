#ifndef VIRTUALALLOC_SEMUN_H
#define VIRTUALALLOC_SEMUN_H

#include <sys/types.h> /* For portability */
#include <sys/sem.h>

union semun { /* Used in calls to semctl() */
    int val;
    struct semid_ds * buf;
    unsigned short * array;
#if defined(__linux__)
    struct seminfo * __buf;
#endif
};

#endif //VIRTUALALLOC_SEMUN_H
