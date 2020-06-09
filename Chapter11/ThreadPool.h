#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include <pthread.h>
#include <unistd.h>
#include <functional>


namespace fool
{
    class ThreadPool
    {
        public:
            ThreadPool();  
            ~ThreadPool();
            ThreadPool(size_t thread_num,std::function<void * (void *)> thread_fun);
            ThreadPool(const ThreadPool& ) =delete;
            const ThreadPool& operator=(const ThreadPool&) =delete; 
        private:
            int thread_num;
            int cur_num;
            pthread_t * thread_array; 
    }

};



#endif