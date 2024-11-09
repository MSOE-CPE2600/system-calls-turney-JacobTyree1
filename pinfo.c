/* ***********************************************************************
 * Author: Jacob Tyree 
 * Created 11/9/2024
 * Assignment: Lab 9 System Calls
 * Section 121
 * **********************************************************************/
 
/* What each system call is used for: 
 * getpid: Retrieves the process ID (PID) of the calling process
 * getpriority: Retrives the priority of a specified process (or group of processes). 
                Priority usually ranges from -20(highest priority) to 19(lowest priority). 
 * sched_getscheduler: Gets the scheduling priority for a specified process. 
                        Returns one of the following constants: 
                        SCHED_OTHER, SCHED_FIFO, SCHED_RR, SCHED_BATCH, SHCED_IDLE, SCHED_DEADLINE
 * getcpu: Determines which CPU the calling process or thread is currently running on. 
 * getrusage: Gets the resource usage statistis for the calling process, like CPU time, memory usage, and I/O Operations
 * getrlimit: Gets the resource limits for the process such as maximum file size, memory usage, and CPU time
 * ***********************************************************************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <errno.h>


// pinfo.c


void print_scheduler(int policy);

int main(int argc, char *argv[]) {
    pid_t pid;
    int priority;
    int policy;

    
    if (argc > 1) {
        pid = atoi(argv[1]);  
    } else {
        pid = getpid();  
    }

    
    priority = getpriority(PRIO_PROCESS, pid);
    if (priority == -1 && errno != 0) {
        perror("Failed to get priority");
        return EXIT_FAILURE;
    }
    printf("Process Priority: %d\n", priority);

    
    policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("Failed to get scheduling policy");
        return EXIT_FAILURE;
    }

   
    print_scheduler(policy);

    return 0;
}
//Some aren't declared and so they need to be defined first. 
void print_scheduler(int policy) {
    switch (policy) {
        case SCHED_OTHER:
            printf("Scheduling Policy: SCHED_OTHER (default)\n");
            break;
        case SCHED_FIFO: 
            printf("Scheduling Policy: SCHED_FIFO (real-time FIFO)\n");
            break;
        case SCHED_RR:
            printf("Scheduling Policy: SCHED_RR (real-time round-robin)\n");
            break;
#ifdef SCHED_BATCH 
        case SCHED_BATCH: 
            printf("Scheduling Policy: SCHED_BATCH\n");
            break;
#endif
#ifdef SCHED_IDLE
        case SCHED_IDLE: 
            printf("Scheduling Policy: SCHED_IDLE\n");
            break;
#endif
#ifdef SCHED_DEADLINE
        case SCHED_DEADLINE:
            printf("Scheduling Policy: SCHED_DEADLINE\n");
            break;
#endif
        default: 
            printf("Unknown Scheduling Policy\n");
            break;
    }
}
