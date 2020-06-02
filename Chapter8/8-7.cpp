#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <stdio.h>


pid_t create_process(int);
int main (int argc, char*argv[])
{

    int value =100;

    pid_t pid = fork();
    if(pid<0)
    {
        return -1;
    }
    else if(pid ==0)
    {
        return 0;

    }

    int ret =system("ps -A -o stat,ppid,pid,cmd | grep -e \'^[Zz]\'");


    printf("process id is %d ,value is  %d",pid,value);
    
    sleep(5);
    return 0;
}

pid_t create_process(int type)
{
    //pid_t pid = vfork();
    pid_t pid = fork();
    if(pid<0)
    {
        return -1;
    }
    else if(pid ==0)
    {
        return 0;

    }
    

    return pid;
    

}