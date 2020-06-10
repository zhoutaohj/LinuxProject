#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace std;
const int MAXLINE =4;
int main(int arrgc, char* argv[])
{
    char buf[MAXLINE];

    while(fgets(buf,MAXLINE,stdin)!=NULL)
    {
        cout<<"My Print:"<<buf<<endl;
        if(fputs(buf,stdout)==EOF)
        {
            cout<<"fputs errror"<<endl;
        }
    }

    if(ferror(stdin))
    {
        cout<<"stdin error"<<endl;
    }

    int fd =fileno(stdout);
    int ret =fsync(fd);

    return 0;
    
}
