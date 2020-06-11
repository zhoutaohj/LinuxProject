#include "Thread.h"
#include <stdio.h>

//#define LOG<<## printf("##")
namespace fool
{
    std::atomic_int64_t Thread::thread_number(0);
    Thread::Thread()
    {
        init();
        thread_number++;
        thread_num_id =thread_number;
    }

     Thread::Thread(ThreadFun fun,void * param)
    {
        thread_fun=fun;
        thread_param =param;
        detached =false;
        started =false;
        thread_number++;
        thread_num_id =thread_number;
    }

    Thread::Thread(Thread && t)
    {
        if(this ==&t)
            return;

        thread_id = t.thread_id;
        thread_fun =t.thread_fun;
        thread_param =t.thread_param;
        detached =t.detached;
        started =t.started;
        thread_number++;

        thread_num_id =thread_number;

        t.init();


        

    }

    Thread& Thread::operator=(Thread&& t)
    {
        if(this ==&t)
            return *this;

        thread_id = t.thread_id;
        thread_fun =t.thread_fun;
        thread_param =t.thread_param;
        detached =t.detached;
        started =t.started;
        thread_number++;
        thread_num_id =thread_number;

        t.init();

        return *this;
    }

    Thread::~Thread()
    {
        if(!detached && started)
        {
            join();
        }

        printf("thread %lu exit\n",thread_num_id);

    }

    void Thread::init()
    {
        thread_id =0;
        thread_fun=nullptr;
        thread_param =nullptr;
        detached =false;
        started =false;
    }

    bool Thread::start()
    {
        int ret =pthread_create(&thread_id,NULL,run,this);

        if(ret !=0)
        {
            printf("Thread create failed!!!\n");
            return false;
        }
        //printf("Thread create succesfully!!!\n");
        started =true;
        return true;
    }

    void * Thread::run(void* param)
    {
        Thread * pt  =reinterpret_cast<Thread *>(param);

        if(pt->thread_fun)
        {
            //printf("thread %lu running\n",pt->thread_num_id);
            pt->thread_fun(pt->thread_param);
        }
             
        return (void*) 0;
    }

    void Thread::join()
    {
        pthread_join(thread_id,nullptr);
        started =false;
    }

    void Thread::detach()
    {
        
        pthread_detach(thread_id);
        detached =true;
    }

};
