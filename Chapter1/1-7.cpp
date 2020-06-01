 #include <iostream>
 #include <unistd.h>
 #include <stdio.h>
 #include <sys/wait.h>
 #include <cstring>

 int main(int argc, char* argv[])
 {
    std::cout<<"This is My Shell Program!"<<std::endl;
    std::cout<<"% ";

    char buf[1024];
    while(fgets(buf,sizeof(buf),stdin)!=nullptr)
    {
        //set the null character
        if(buf[strlen(buf)-1]=='\n')
            buf[strlen(buf)-1]=0;
        
        pid_t pid=0;
        if((pid=fork())<0)
        {
            std::cout<<"fork is failed!!"<<std::endl;
        }
        else if(pid == 0)
        {//child process
           int ret =execlp(buf,buf,(char*)(0));
           if(ret==-1)
           {//execute failed
               std::cout<<buf<<" execute failed!!!"<<std::endl;
           }
           exit(-127);

        }

        int status=0;

        if(status = waitpid(pid,&status,0)<0)
        {
            std::cout<<"waitpid failed!!!"<<std::endl;
        }

        std::cout<<"% ";


    }
    return 0;
 }
