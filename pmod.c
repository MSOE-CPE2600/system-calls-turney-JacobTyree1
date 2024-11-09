/* ***********************************************************************
 * Author: tyreej@msoe.edu
 * Created: 11/9/2024
 * Assignment: Lab 9 System Calls
 * Section 121
 * Description of attributes: 
 * nice: A function used to adjust the priority of a process. 
        A higher nice value lowers the process's priority, and
        a lower nice value increases the priority. 
 * nanosleep: Used to suspend the execution of a process for a specified
            amount of time with nanosecond precision. 
            It returns 0 on success, or -1 if interrupted. 
 * **********************************************************************/

// pmod.c


#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (nice(10) == -1 && errno != 0) {
        perror("Failed to change priority with nice");
        return EXIT_FAILURE;
    }
    printf("Process priority reduced by 10.\n");
    struct timespec req;
    req.tv_sec = 1;
    req.tv_nsec = 837272638;

    printf("Going to sleep for %ld seconds and %ld nanoseconds...\n", req.tv_sec, req.tv_nsec);

    if(nanosleep(&req, NULL) == -1) {
        perror("nanosleep failed");
        return EXIT_FAILURE;
    }
    //Ending program
    printf("Goodbye. Exiting Program\n");
    return EXIT_SUCCESS;
}