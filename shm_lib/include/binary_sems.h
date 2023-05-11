#ifndef VIRTUALALLOC_BINARY_SEMS_H
#define VIRTUALALLOC_BINARY_SEMS_H

#include <stdbool.h>

int initSemAvailable(int semId, int semNum);
int initSemInUse(int semId, int semNum);
int waitSem(int semId, int semNum);
int releaseSem(int semId, int semNum);

#endif //VIRTUALALLOC_BINARY_SEMS_H
