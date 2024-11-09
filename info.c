// Jacob Tyree, Lab9 System Calls, Section 121. 

// info.c

#include <stdio.h>
#include <time.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
//Print: 
//Current time of day in nanoseconds

    struct timespec ts;
    struct utsname buffer;

    if(clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        perror("clock_gettime");
        return 1;
    }
    printf("Current time in nano seconds is: %ld nanoseconds\n", ts.tv_nsec);

//The system's network name
    if (uname(&buffer) == -1) {
        perror("uname");
        return 1;
    }
    printf("Network name is %s\n", buffer.nodename);
//The operating system name
    printf("Operating System Name is %s\n", buffer.sysname);
//The operating system release and version
    printf("Release: %s\n", buffer.release);
    printf("Version: %s\n", buffer.version);
//The system's hardware type
    printf("Hardware type: %s\n", buffer.machine);

//The number of CPUs on the system
    long num_cpus = sysconf(_SC_NPROCESSORS_ONLN);
    if (num_cpus == -1) {
        perror("sysconf");
        return 1;
    }
    printf("Total CPUs: %ld\n", num_cpus);

//The total amount of physical memory in bytes
    FILE *meminfo = fopen("/proc/meminfo", "r");
    if(meminfo == NULL) {
        perror("fopen");
        return 1;
    }
    long total_memory = 0;
    long free_memory = 0;
    char line[256];

    while(fgets(line, sizeof(line), meminfo)) {
        if (sscanf(line, "MemTotal: %ld kB", &total_memory) == 1) {
            total_memory *= 1024;
        } else if (sscanf(line, "MemFree: %ld kB", &free_memory) == 1) {
            free_memory *= 1024;
        }
    }

    fclose(meminfo);
    printf("Total Physical Memory: %ld bytes\n", total_memory);
    printf("Free Memory: %ld bytes\n", free_memory);
//The total amount of free memory in bytes
//If any of these values are blank or null, don't print them out.
    return 0;
}