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
};

int main(int argc, char *argv[])
{
    fool::Thread thread(thread_fun, nullptr);
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
    }

    fool::Mutex mutex;
    std::queue<task> task_queue;
    fool::cond_variable cond;

    bool flag = true;

    fool::Thread producer([&mutex, &task_queue, &cond,&flag](void *) {
        size_t index = 0;
        while (index != 100000)
        {

            fool::MutexLock lock(mutex);

            while (task_queue.size() >= 10000)
            {
                cond.wait(lock);
            }

            task task_tmp;
            task_tmp.task_id = index++;
            snprintf(task_tmp.buffer, sizeof(task_tmp.buffer), "task %lu", index);

            task_queue.push(std::move(task_tmp));
            cond.broadcast();
        }

        flag = false;
        printf("producer exit!!\n");
    },nullptr);

    producer.start();

    std::vector<fool::Thread> consumer_vec;

    //消费者线程
    for (size_t i = 0; i < 10; i++)
    {
        consumer_vec.push_back(
            fool::Thread([&mutex, &task_queue, &cond,&flag](void *) {
                while (flag)
                {
                    fool::MutexLock lock(mutex);
                    while (task_queue.empty())
                    {
                        cond.wait(lock);
                    }
                    task task_tmp = task_queue.front();
                    task_queue.pop();
                    printf("consumer task %d, %s\n", task_tmp.task_id, task_tmp.buffer);
                }
            },nullptr));

        consumer_vec[i].start();
    }

    producer.join();
    for (auto &thread : thread_array)
    {
        thread.join();
    }
    printf("Main Thread  exit\n ");
}