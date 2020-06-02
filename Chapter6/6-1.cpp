#include <iostream>
#include <unistd.h>
#include <shadow.h>

int main(int argc, char* argv[])
{

    const char * array[]={"root","zhoutao"};

    for( auto name :array)
    {
        struct spwd * pd  =getspnam(name);

        if(pd!=nullptr)
           std::cout<<name<<" :"<<pd->sp_pwdp<<std::endl;
        else
        {
            perror(name);
        }
        
    }
    




    return 0;
}