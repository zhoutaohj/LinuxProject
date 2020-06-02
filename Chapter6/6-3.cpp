#include <iostream>
#include <unistd.h>
#include <sys/utsname.h>

int main(int argc ,char *argv[])
{
    utsname sname;
    int ret =uname(&sname);
    std::cout<<sname.sysname<<sname.version<<sname.nodename<<sname.machine\
    <<sname.domainname<<sname.release<<std::endl;

    std::cout<<sizeof(time_t)<<std::endl;
    return 0;

}
