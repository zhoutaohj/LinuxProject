#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include <pthread.h>
#include <unistd.h>
#include <functional>
#include "Thread.h"
#include <vector>
#include <queue>
#include "MutexLock.h"

namespace fool
{
    struct Task
    {
       public:
       int thread_id;
       std::vector<char> buffer;
    };
    

    class Task;
    class ThreadPool
    {
        public:
            ThreadPool();  
            ~ThreadPool();
            ThreadPool(size_t thread_num);
            ThreadPool(const ThreadPool& ) =delete;
            const ThreadPool& operator=(const ThreadPool&) =delete; 

            ThreadPool(ThreadPool && );

            void start();

            void add_task(const Task &);
            void remove_task();
            static void ThreadFun(void *);


        private:
            int thread_num;
            int cur_num;
            std::vector<Thread> thread_vec;
            std::queue<Task> task_queue;
            Mutex queue_mutex;

    };

};



#endif