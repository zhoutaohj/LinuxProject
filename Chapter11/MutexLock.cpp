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

    void Mutex::lock()
    {
         pthread_mutex_lock(&pthread_mutex);
    }
    
    void Mutex::unlock()
    {
        pthread_mutex_unlock(&pthread_mutex);
    }

    pthread_mutex_t Mutex::get_mutex() const
    {
        return pthread_mutex;
    }

    MutexLock::MutexLock(Mutex & m) : mutex(m)
    {
        mutex.lock();
    }

    MutexLock::~MutexLock()
    {
        mutex.unlock();
    }
 
    
};