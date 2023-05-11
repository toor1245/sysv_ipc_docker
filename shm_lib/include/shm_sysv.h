#ifndef VIRTUALALLOC_SHM_SYSV_H
#define VIRTUALALLOC_SHM_SYSV_H

#include <sys/stat.h>

#define SHM_KEY         0x12345
#define SEM_KEY         0x56789

#define OBJ_PERMS       (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

#define WRITE_SEM       0 /* Writer has access to shm_lib memory */
#define READ_SEM        1 /* Reader has access to shm_lib memory */

#endif //VIRTUALALLOC_SHM_SYSV_H
