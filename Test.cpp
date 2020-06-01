#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[])
{
    std::cout<<"Hello,Ubuntu! Pid: "<<getpid()<<std::endl;
    return 0;
}
