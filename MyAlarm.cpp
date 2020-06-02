#include <unistd.h>
#include <signal.h>
#include <set>
#include <iostream>
#include "MyAlarm.h"
#include <time.h>
namespace std
{

    static std::set<int> alarm_set;//non-multiple thread version
    int my_alarm(int sec)
    {
        int remainder_sec =alarm(sec);

        if(remainder_sec==0)
        {
            alarm_set.insert(sec);
            return 0;
        }
        else if (remainder_sec>0)
        {
            alarm_set.insert(remainder_sec);
            return 0;
        }
        else
        {
            return -1;
        }
        
        
    }

    void my_alarm_fun(int sig)
    {
        if(!alarm_set.empty())
        {
            int sec = *(alarm_set.begin());

            alarm_set.erase(sec);

            for (auto iter =alarm_set.begin();iter!=alarm_set.end();++iter)
	        {
		        int & value =const_cast<int &>(*iter);
		        value -=sec;
	        }


            if(!alarm_set.empty())
            {
                int sec = *(alarm_set.begin());
                alarm(sec);
                alarm_set.erase(sec);
            }
        }
        struct tm * tm_local= localtime(NULL);

        char time_buf[256];

        strftime(time_buf, sizeof(time_buf), "time and date: %r, %a %b %d, %Y", tm_local);
        
        std::cout<<time_buf<<" alarm call"<<std::endl;
    }

};

