#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <iostream>
#include "Thread.h"

using namespace std;
int main(int argc, char *argv[])
{
    std::mutex mutx;
    std::unique_lock<mutex> lock(mutx);
    std::condition_variable cv;
    int i = 0;

    /*std::vector<thread> thread_vec;
	thread_vec.push_back(thread ([]() {cout << "thread 1 running!!!" << endl; }));
	thread_vec.push_back(thread ([]() {cout << "thread 2 running!!!" << endl; }));
	thread_vec.push_back(thread ([]() {cout << "thread 3 running!!!" << endl; }));

	for (auto& t : thread_vec)
	{
		t.join();
	}*/

    //std::function<bool()> fun = [&i]()->bool { return i < 5; };
    // auto fun = [&i]() -> bool { return i == 4; };
    //cv.wait<decltype(fun)>(lock, fun);

    std::vector<fool::Thread> mythread_vec;
	mythread_vec.push_back(fool::Thread ([](void *) {cout << "mythread 1 running!!!" << endl; },nullptr));
	mythread_vec.push_back(fool::Thread ([](void *) {cout << "mythread 2 running!!!" << endl; },nullptr));
	mythread_vec.push_back(fool::Thread ([](void *) {cout << "mythread 3 running!!!" << endl; },nullptr));

	for (auto& t : mythread_vec)
	{
		t.start();
	}

    for (auto& t : mythread_vec)
	{
		t.join();
	}
}

