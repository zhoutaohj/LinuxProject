#include "cond_variable.h"

namespace fool
{
    cond_variable::cond_variable(Mutex & m) :_mutex(m)
    {
        flag =false;
        pthread_cond_init(&_cond_var,nullptr);
    }

    cond_variable::~cond_variable()
    {
        pthread_cond_destroy(&_cond_var);
    }

    void cond_variable::wait()
    {
        while (!flag)
        {
            pthread_cond_wait(&cond_variable,&_mutex.get_mutex);
        }
        
    }


    void cond_variable::signal()
    {
        flag = true;
        pthread_cond_signal(&cond_variable);
    
        
    }

};