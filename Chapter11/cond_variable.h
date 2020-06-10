#ifndef COND_VARIABLE_H
#define COND_VARIABLE_H
#include "MutexLock.h"
#include <pthread.h>

namespace fool
{
    class Mutex;

    class  cond_variable
    {
    public:
         cond_variable();
        ~cond_variable();

        void wait(MutexLock &);
        //void waittime();
        void signal();
        void broadcast();
    private:
        
        bool flag;
        pthread_cond_t _cond_var;
    };
    
    
} ;

#endif