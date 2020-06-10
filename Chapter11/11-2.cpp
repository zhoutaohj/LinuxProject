#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <functional>

void * thread_fun(void *);


int main(int argc, char* argv[])
{

    const int thread_num=10;
    pthread_t thread_array[thread_num];

    std::function<void * (void *)> fun =thread_fun;

    for(int i=0;i!=thread_num;i++)
    {
        pthread_create(&thread_array[i],NULL,fun,(void*)i);
    }


    for(int i=0;i!=thread_num;i++)
    {
        pthread_join(thread_array[i],NULL);
    }

    printf("main thread exit!!!");
    return 0;
}


void * thread_fun(void * param)
{
    long id = reinterpret_cast<long> (param);
    printf("Thread %ld start:\n",id);

    /*do sth*/

    printf("Thread %ld end\n",id);
    pthread_exit(NULL);
    return (void *)0;

}
