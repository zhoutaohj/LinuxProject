#include <sys/stat.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[])
{

    struct stat file_stat;

    for(int index =1;index<argc;index++)
    {
        int ret =lstat(argv[index],&file_stat);

        if(S_ISREG(file_stat.st_mode))
        {
            cout<<"Regular file!"<<endl;
        }
        else if(S_ISDIR(file_stat.st_mode))
        {
            cout<<"Directory file!"<<endl;
        }
        else if(S_ISBLK(file_stat.st_mode))
        {
            cout<<"Block file!"<<endl;
        }
        else if(S_ISCHR(file_stat.st_mode))
        {
            cout<<"Charecter file!"<<endl;
        }
        else if(S_ISFIFO(file_stat.st_mode))
        {
            cout<<"FIFO!"<<endl;
        }
        else if(S_ISSOCK(file_stat.st_mode))
        {
            cout<<"Socket!"<<endl;
        }
        else
        {
            cout<<"Unknowed file!"<<endl;
        }
        

    }

    char sl_buf[100];
    int ret =readlink("testsl",sl_buf,sizeof(sl_buf));
    sl_buf[ret]=0;
    cout<<sl_buf<<endl;


    
   
    return 1;
}