#include <iostream>
#include <pthread.h>

namespace std
{
    struct mybarrier_t
    {
        pthread_mutex_t mutex;
        pthread_cond_t cond;
        size_t count;
        mybarrier_t(size_t ncount): count(ncount)
        {
            pthread_mutex_init(&mutex,nullptr);
            pthread_cond_init(&cond,nullptr);

        }

        ~mybarrier_t()
        {
            pthread_mutex_destroy(&mutex);
            pthread_cond_destroy(&cond);

        }

    };

    int my_barrier_init(mybarrier_t *, size_t count);
    int my_barrier_destory(mybarrier_t *);
    int my_barrier_wait(mybarrier_t *);


    int my_barrier_init(mybarrier_t * pbarrier, size_t count)
    {
        mybarrier_t bar =new my_barrier_t(count);
        
    }

    int my_barrier_wait(mybarrier_t * pb)
    {
        pthread_mutex_lock(&bar.mutex);

        count--;

        if(count==0)
        {
            pthread_cond_broadcast(&bar.cond);
        }

        while (count>0)
        {
            pthread_cond_wait(&bar.cond,&bar.mutex);
        }
  
        pthread_mutex_unlock(&bar.mutex);

    }

    int my_barrier_wait(mybarrier_t *pb)
    {
        delete pb;
        pb =nullptr;
    }
}; // namespace std
