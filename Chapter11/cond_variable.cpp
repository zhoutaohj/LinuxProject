#include "cond_variable.h"

namespace fool
{
    cond_variable::cond_variable()
    {
        flag = false;
        pthread_cond_init(&_cond_var, nullptr);
    }

    cond_variable::~cond_variable()
    {
        pthread_cond_destroy(&_cond_var);
    }

    void cond_variable::wait(MutexLock & mu)
    {
        while (!flag)
        {
            pthread_cond_wait(&_cond_var, &mu.mutex.pthread_mutex);
        }
    }

    void cond_variable::signal()
    {
        flag = true;
        pthread_cond_signal(&_cond_var);
    }

    void cond_variable::broadcast()
    {
        flag = true;
        pthread_cond_broadcast(&_cond_var);
    }

}; // namespace fool