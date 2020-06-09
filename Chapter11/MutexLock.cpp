#include "MutexLock.h"

namespace fool
{
    Mutex::Mutex()
    {
        pthread_mutex_init(&pthread_mutex,nullptr);
    }

    Mutex::~Mutex()
    {
        pthread_mutex_destroy(&pthread_mutex);
    }

    Mutex::Mutex(Mutex&& m)
    {
        pthread_mutex = m.pthread_mutex;
    }

    Mutex& Mutex::operator=(Mutex && m)
    {
        if(this == &m)
           return *this;

        pthread_mutex = m.pthread_mutex;
        return *this;

    }

    pthread_mutex_t get_mutex() const
    {
        return pthread_mutex;
    }
    MutexLock::MutexLock(Mutex & m) : mutex(m)
    {
        pthread_mutex_lock(&mutex.pthread_mutex);
    }

    MutexLock::~MutexLock();
    {
        pthread_mutex_unlock(&mutex.pthread_mutex);
    }
 
    
};