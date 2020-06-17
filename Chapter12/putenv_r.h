#ifndef PUT_ENV_R_H
#define PUT_ENV_R_H
#include <pthread.h>
#include <string.h>

extern char** environ;

namespace fool
{
    static pthread_attr_t mutex_attr;
    static pthread_mutex_t mutex_env;
    static pthread_once_t once_env =PTHREAD_ONCE_INIT;
    static int env_size=1024;
    int putenv_r(const char* str);

    void env_init();

    void env_init()
    {
        pthread_attr_init(&mutex_attr);
        pthread_mutexattr_settype(&mutex_attr,PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&mutex_env,&mutex_attr);

    }

    int putenv_r(const char* str)
    {
        if(str ==nullptr)
            return -1;
        pthread_once(&once_env,env_init);
        pthread_mutex_lock(&mutex_env);
        char * value=nullptr;
        int name_len =0;

        value = strchr(str,'=');
        name_len = value -str;
        value ++;
        
        for (size_t i = 0; environ[i] !=nullptr; i++)
        {
            if(strncmp(str,environ[i],name_len) ==0 )
            {
                delete environ[i];
                environ[i] =str;
            }
        }

        // find nothing

        


    }

};
#endif