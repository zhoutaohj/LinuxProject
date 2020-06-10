#include <unistd.h>
#include <iostream>
#include "MyAlarm.h"
#include <signal.h>
#include <string>

using namespace std;


int main(int argc, char* argv[])
{

    if(signal(SIGALRM,my_alarm_fun) ==SIG_ERR)
    {
        cout<<"signal set failed!!"<<endl;
    }
    
    string param (argv[1]);

    if(param == "1")
    {
         cout<<"alarm :"<<endl;
         alarm(10);
         alarm(1);
         alarm(2);

    }
    else
    {
        cout<<"my alarm :"<<endl;
        my_alarm(10);
        my_alarm(1);
        my_alarm(5);
    }
    


    while(1)
    {
        pause();
    }



    return 0;
}