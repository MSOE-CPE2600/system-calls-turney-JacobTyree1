# system-calls
This assignment uses system calls on a Portable Operating System Interface operating system. It uses Information Maitenance, Process Control, File Management, Communication, and Device Management. 

# How to Build the Project

## Clone the repository
git clone https://github.com/MSOE-CPE2600/system-calls-turney-JacobTyree1

## Change into the project directory
cd system-calls-turney-JacobTyree1/

# How to run the Project

## Using Make: 
make clean
make

./finfo
./info
./pinfo
./pmod

## Using command line: 
gcc finfo.c info.c pinfo.c pmod.c

# How to run each program: 

## finfo.c: 
./finfo (file path)
Ex: ./finfo pmod.c

## info.c
./info 

## pinfo.c
./pinfo (process identifier)
Ex: ./pinfo 1

## pmod.c
./pmod