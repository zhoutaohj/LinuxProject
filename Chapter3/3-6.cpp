#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <memory>
using namespace std;

int main(int argc,char* argv[])
{
    int fd = open(argv[1],O_RDWR|O_APPEND);

    if(fd<0)
    {
        cout<<"open file failed!!"<<endl;
    }

    off_t cur = lseek(fd,10,SEEK_SET);

    if(cur==-1)
    {
        cout<<"Can't seek for read!"<<endl;
    }

    char* read_buffer =new char[100];
    char* write_buffer =new char[100];

    int ret =0;
    if((ret =read(fd,read_buffer,100))<0)
    {
        cout<<"read failed!!!"<<endl;

    }
    else if(ret ==EOF)
    {
        /* code */

        cout<<"End of File"<<endl;
    }
    else
    {
        read_buffer[ret]='\0';
        cout<<read_buffer<<endl;
    }

    //write test
 
    ret=0;

    cur = lseek(fd,-10,SEEK_END);

    const char *buf="999999999";
    memcpy(write_buffer,"999999999",(strlen(buf)+1));
    if((ret =write(fd,write_buffer,10))<0)
    {
        cout<<"write failed!!!"<<endl;

    }
    else
    {
        cout<<"write successfully!"<<endl;
    }


    
    
    



}

