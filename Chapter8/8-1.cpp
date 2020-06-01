#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <stdio.h>

int main (int argc, char*argv[])
{

    int value =100;

    pid_t pid;

    //std::cout<<"before fork:";
    printf("before fork:");
    if((pid=vfork())<0)
    {
        perror("Fork failed");
        return -1;
    }
    else if(pid ==0)
    {// child process
        value++;
        _exit(0);
    }


    sleep(5);
    pid_t pid_wait =waitpid(pid,NULL,0);
    //std::cout<<"value "<<value<<" parent process running..."<<std::endl;
    int ret =printf("value %d parent process running...",value);

    if(ret==-1)
    {
        printf("ret is -1\n");
    }

    return 0;
}