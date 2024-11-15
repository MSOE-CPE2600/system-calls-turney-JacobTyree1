// Jacob Tyree, Lab9 System Calls, Section 121. 

// finfo.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void print_file_type(mode_t mode);
void print_permissions(mode_t mode);
void print_modification_time(time_t mod_time);


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: You must specify a file as an argument.\n");
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];

    struct stat file_stat;
    if (stat(file_path, &file_stat) == -1 ) {
        perror("Error getting file information");
        return EXIT_FAILURE;
        //Basically another version of return 1. 
    }

    print_file_type(file_stat.st_mode);
    print_permissions(file_stat.st_mode);
    printf("Owner (UID): %d\n", file_stat.st_uid);
    printf("Size: %ld bytes\n", file_stat.st_size);
    print_modification_time(file_stat.st_mtime);


    return EXIT_SUCCESS;
    //Basically another version of return 0. 
}

void print_file_type(mode_t mode) {
    if(S_ISREG(mode)) {
        printf("File Type: Regular file\n");
    } else if (S_ISDIR(mode)) {
        printf("File Type: Directory\n");
    } else if (S_ISLNK(mode)) {
        printf("File Type: Symbolic link\n");
    } else if (S_ISCHR(mode)) {
        printf("File Type: Character device\n");
    } else if (S_ISBLK(mode)) {
        printf("File Type: Block device\n");
    } else if (S_ISFIFO(mode)) {
        printf("File Type: FIFO (named pipe)\n");
    } else if (S_ISSOCK(mode)) {
        printf("File Type: Socket\n");
    } else {
        printf("File Type: Unknown\n");
    }
}
void print_permissions(mode_t mode) {
    printf("Permissions: ");
    
    // User permissions
    printf("%s%s%s ", 
           (mode & S_IRUSR) ? "read" : "no read", 
           (mode & S_IWUSR) ? "/write" : "/no write", 
           (mode & S_IXUSR) ? "/execute" : "/no execute");

    // Group permissions
    printf("%s%s%s ", 
           (mode & S_IRGRP) ? "read" : "no read", 
           (mode & S_IWGRP) ? "/write" : "/no write", 
           (mode & S_IXGRP) ? "/execute" : "/no execute");

    // Other permissions
    printf("%s%s%s\n", 
           (mode & S_IROTH) ? "read" : "no read", 
           (mode & S_IWOTH) ? "/write" : "/no write", 
           (mode & S_IXOTH) ? "/execute" : "/no execute");
}
void print_modification_time(time_t mod_time) {
    struct tm *timeinfo = localtime(&mod_time);
    char time_str[100];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("Last Modified: %s\n", time_str);
}
