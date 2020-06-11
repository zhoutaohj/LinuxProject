#include "cond_variable.h"

namespace fool
{
    cond_variable::cond_variable()
    {
        pthread_cond_init(&_cond_var, nullptr);
    }

    cond_variable::~cond_variable()
    {
        pthread_cond_destroy(&_cond_var);
    }

    void cond_variable::wait(MutexLock & mu)
    {
       /* while (!flag)
        {
            pthread_cond_wait(&_cond_var, &mu.mutex.pthread_mutex);
            
        }*/

        pthread_cond_wait(&_cond_var, &mu.mutex.pthread_mutex);
        
    }

    void cond_variable::signal()
    {
        
        pthread_cond_signal(&_cond_var);
       
    }

    void cond_variable::broadcast()
    {
        
        pthread_cond_broadcast(&_cond_var);
        
    }

}; // namespace fool