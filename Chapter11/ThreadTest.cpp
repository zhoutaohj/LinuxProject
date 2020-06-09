#include <unistd.h>
#include "Thread.h"
#include <stdio.h>
#include <vector>

void thread_fun(void * param)
{
    for(int i=0;i!=100;i++)
    {
        /**/
    }

    printf("Thread exit\n");

}


int main(int argc, char*argv[])
{
    fool::Thread thread(thread_fun,nullptr);
    thread.start();

    thread.join();


    fool::Thread thread2 ([](void *){printf("This is lamda function\n");},nullptr);

    thread2.start();
    thread2.join();

   

    std::vector<fool::Thread> thread_array;

    for (int i = 0; i != 10; i++)
    {
        thread_array.push_back(fool::Thread([i](void * param ){ int id =i;printf("Thread %d exit \n",id);},nullptr));
        thread_array[i].start();
        
    }


    
    

    for (auto & thread :thread_array)
    {
        
        thread.join();
    }

    printf("Main Thread  exit\n ");

}