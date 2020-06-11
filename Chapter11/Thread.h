#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
#include <functional>
#include <atomic>

namespace fool
{
    class Thread 
    {
         
        public:
            using ThreadFun=std::function<void (void *)> ;

            Thread();
            Thread(ThreadFun,void *);
            ~Thread();

            Thread(const Thread&) =delete;// prohibit copy construction
            const Thread& operator=(const Thread&)=delete; 

            Thread(Thread &&);

            Thread& operator=(Thread&&); 

            bool start();
            void join();
            void detach();
            static void * run(void *);
           
           private:
           void  init();
        private:
            pthread_t thread_id;
            bool  started;
            ThreadFun thread_fun; 
            void * thread_param;
            bool  detached;
            static std::atomic_int64_t thread_number;
            size_t thread_num_id;
    };
    
    
};
#endif