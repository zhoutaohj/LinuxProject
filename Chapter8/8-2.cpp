#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <stdio.h>


pid_t create_process(int);
int main (int argc, char*argv[])
{

    int value =100;

    pid_t pid = create_process(0);


    printf("process id is %d ,value is  %d",pid,value);

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