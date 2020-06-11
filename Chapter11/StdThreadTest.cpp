#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <iostream>
#include "Thread.h"
#include <memory>
#include <unistd.h>

using namespace std;
int main(int argc, char *argv[])
{
    std::mutex mutx;
    std::unique_lock<mutex> lock(mutx);
    std::condition_variable cv;
    int i = 0;

    std::vector<thread> thread_vec;
	/*thread_vec.push_back(thread ([]() {cout << "thread 1 running!!!" << endl; }));
	thread_vec.push_back(thread ([]() {cout << "thread 2 running!!!" << endl; }));
	thread_vec.push_back(thread ([]() {cout << "thread 3 running!!!" << endl; }));

	for (auto& t : thread_vec)
	{
		t.join();
	}*/

    //std::function<bool()> fun = [&i]()->bool { return i < 5; };
    // auto fun = [&i]() -> bool { return i == 4; };
    //cv.wait<decltype(fun)>(lock, fun);

    /*std::vector<std::unique_ptr<fool::Thread>> mythread_vec;

	for (int index =0 ;index<3 ;index++)
	{
        mythread_vec.emplace_back(new fool::Thread ([index](void *) {printf("Thread %d running\n",index); },nullptr));
		mythread_vec[index]->start();
	}*/


    std::vector<fool::Thread> mythread_vec;
	//std::vector<thread> mythread_vec;


	for (int index =0 ;index<10 ;index++)
	{
        mythread_vec.push_back(fool::Thread([index](void *) { 
			for(size_t i=0;i!=1000000000;i++)
			;
		 printf("Thread %d running\n",index); },nullptr));
		//mythread_vec[index]=std::move(fool::Thread ([index](void *) { int i=100; printf("Thread %d running\n",index); },nullptr));
        mythread_vec[index].start();
	}

    /*for (auto& t : mythread_vec)
	{
		t.start();
	} */

    printf(" Main : thread number %lu\n",mythread_vec.size());
    for (auto& t : mythread_vec)
	{
        
		t.join();
	}


}

