#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <functional>


using namespace std;

typedef void (*ExitFunc)();

using ExitFunction = void (*)();
void func1();
void func2();
void func3();
int main(int argc, char*argv[])
{
    ExitFunc fun = func1;
    ExitFunction fun_=func2;

    std::function<void()> fun__ =func3;

    atexit(fun);
    atexit(fun_);
    fun__();
    return 0;

}

void func1()
{
    printf("func1 is called\n");
}

void func2()
{
    printf("func2 is called\n");
}

void func3()
{
    printf("func3 is called\n");
}
