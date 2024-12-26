#ifndef BACKGROUND_PROCESSES_H
#define BACKGROUND_PROCESSES_H

#include <sys/types.h>

typedef struct BackgroundProcess {
    pid_t pid;
    struct BackgroundProcess *next;
} BackgroundProcess;

extern BackgroundProcess *background_processes;

void add_background_process(pid_t pid);
void remove_background_process(pid_t pid);
void check_background_processes();

#endif
