#include <unistd.h>
#include "Thread.h"
#include <stdio.h>
#include <vector>
#include "MutexLock.h"
#include "cond_variable.h"
#include <queue>

void thread_fun(void *param)
{
    for (int i = 0; i != 100; i++)
    {
        /**/
    }

    printf("Thread exit\n");
}

struct task
{
    /* data */
    int task_id;
    char buffer[100];
    char end;
};

int main(int argc, char *argv[])
{
    /*fool::Thread thread(thread_fun, nullptr);
    thread.start();

    thread.join();

    fool::Thread thread2([](void *) { printf("This is lamda function\n"); }, nullptr);

    thread2.start();
    thread2.join();

    std::vector<fool::Thread> thread_array;

    for (int i = 0; i != 10; i++)
    {
        thread_array.push_back(fool::Thread([i](void *param) { int id =i;printf("Thread %d exit \n",id); }, nullptr));
        thread_array[i].start();
    }

    for (auto &thread : thread_array)
    {

        thread.join();
    }*/

    fool::Mutex mutex;
    std::queue<task> task_queue;
    fool::cond_variable cond_empty;
    fool::cond_variable cond_full;

    bool flag = true;

    fool::Thread producer([&mutex, &task_queue, &cond_full,&cond_empty,&flag](void *) {
        size_t index = 0;
        while (index != 100000)
        {

            task task_tmp;
            task_tmp.task_id = index;
            snprintf(task_tmp.buffer, sizeof(task_tmp.buffer), "task %lu", index++);
            task_tmp.end =='0';
            fool::MutexLock lock(mutex);

            while (task_queue.size() >= 10000)
            {
                cond_full.wait(lock);
            }

            task_queue.push(task_tmp);
            printf("proceduer thread produce task %d, %s\n", task_tmp.task_id, task_tmp.buffer);
            cond_empty.broadcast();
        }

        //push end msg
        {
            fool::MutexLock lock(mutex);
            for (int i = 0; i < 10; i++)
            {
                task task_tmp;
                task_tmp.task_id = index;
                snprintf(task_tmp.buffer, sizeof(task_tmp.buffer), "task %lu", index++);
                task_tmp.end = '1';
                task_queue.push(task_tmp);

            }
            cond_empty.broadcast();
        }

        flag = false;
        printf("producer exit!!\n");
    },nullptr);

    producer.start();

    std::vector<fool::Thread> consumer_vec(10);

    //消费者线程
    for (int i = 0; i < 10; i++)
    {
        consumer_vec[i]=std::move(fool::Thread ([&mutex, &task_queue, &cond_full,&cond_empty,&flag,i](void *) {

                int thread_id =i,count=0;
                printf("thread id : %d \n",thread_id);
                while (true )
                {
                    fool::MutexLock lock(mutex);
                    while (task_queue.empty() )
                    {
                        cond_empty.wait(lock);
                    }
                    task task_tmp = task_queue.front();

                   
                    task_queue.pop();
                    printf("thread id : %d consumer task %d, %s\n",thread_id, task_tmp.task_id, task_tmp.buffer);
                    count++;

                    if(task_tmp.task_id>=10000&&task_tmp.end =='1')
                    {
                        break;

                    }
                        

                   

                    cond_full.signal();
                }
                printf("thread id : %d consumer %d tasks \n",thread_id, count);

            },nullptr));

        consumer_vec[i].start();
    }

    //printf("consumer Thread  %lu\n ",consumer_vec.size());
    producer.join();

    
    for (auto &thread : consumer_vec)
    {
        thread.join();
    }
    printf("Main Thread  exit\n ");
}