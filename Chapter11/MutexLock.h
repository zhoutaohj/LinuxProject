#ifndef MUTEX_LOCK_H
#define MUTEX_LOCK_H

#include <pthread.h>

namespace fool
{
    class MutexLock;
    class Mutex;
    class cond_variable;


    class Mutex
    {
        friend class Mutexlock;
        friend class cond_variable;

        public:
           Mutex();
           ~Mutex();
           Mutex(const Mutex &) =delete;
           const Mutex & operator=(const Mutex &)=delete;

           Mutex(Mutex &&);

           Mutex& operator =(Mutex&&);

        private:
           pthread_mutex_t get_mutex() const;

        private:
            pthread_mutex_t pthread_mutex;
    };


    class MutexLock
    {
        friend class cond_variable;
        public:
            MutexLock(Mutex & mutex);
            ~MutexLock();
        private:
            Mutex & mutex;

    };
};

#endif