#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <string>
#include <dirent.h>
#include <vector>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
using namespace std;



void FormatPrint(const vector<struct stat> &,const vector<string>&);
int main(int argc, char* argv[])
{
    

    if(argc>2)
    {
        cout<<"Not Support Command!!"<<endl;
        return -1;
    }


    if(argc>1 && string(argv[1])!="-l")
    {
        cout<<"Command Error!!"<<endl;
        return -1;
    }

    char cur_pathName[4096];

    if(getcwd(cur_pathName,sizeof(cur_pathName))==NULL)
    {
        cout<<"getcwd "<<cur_pathName <<" failed!!!"<<endl;
        cout<<strerror(errno)<<endl;
        return -1;
    }

    DIR * dp =opendir(cur_pathName);

    if(dp == nullptr)
    {
        cout<<"opendir "<<cur_pathName<<" failed!!!"<<endl;
        return -1;
    }


    vector<string> vec_file;
    vector<struct stat> vec_fileStat;
    dirent* entry =nullptr;
    while((entry=readdir(dp))!=nullptr)
    {
        vec_file.push_back(string(entry->d_name));

        string tmp(cur_pathName);
        tmp+='/';
        tmp+=entry->d_name;
        struct  stat file_stat;
        lstat(tmp.c_str(),&file_stat);

        vec_fileStat.push_back(file_stat);
        
    }

    if(string(argv[1])=="-l")  
    {
        FormatPrint(vec_fileStat,vec_file);
    }
    else
    {
        for(auto file_name: vec_file)
        {
            cout<<file_name<<' ';
        }

        cout<<endl;
        
    }
    

    return 1;
}

void FormatPrint(const vector<struct stat>&  vec_stat,const vector<string>& vec_filename)
{
    //permission

    
    for(int index=0;index!=vec_stat.size();index++)
    {
        string info;
        //file type
        if(S_ISREG(vec_stat[index].st_mode))
        {
            info+='-';
        }
        else if(S_ISDIR(vec_stat[index].st_mode))
        {
            info+='d';
        }

        //User permission


        if(vec_stat[index].st_mode & S_IRUSR)
        {
            info+='r';
        }
        else
        {
            info+='-';
        }
        

        if(vec_stat[index].st_mode & S_IWUSR)
        {
            info+='w';
        }
        else
        {
            info+='-';
        }
        

        if(vec_stat[index].st_mode & S_IXUSR)
        {

            info+='x';

            if(vec_stat[index].st_mode & S_ISUID)
            {
                info[info.length()-1]='s';
            }
            
        }
        else
        {
            info+='-';
             if(vec_stat[index].st_mode & S_ISUID)
            {
                info[info.length()-1]='S';
            }
        }

        //Group permission


        if(vec_stat[index].st_mode & S_IRGRP)
        {
            info+='r';
        }
        else
        {
            info+='-';
        }
        

        if(vec_stat[index].st_mode & S_IWGRP)
        {
            info+='w';
        }
        else
        {
            info+='-';
        }
        

        if(vec_stat[index].st_mode & S_IXGRP)
        {

            info+='x';

            if(vec_stat[index].st_mode & S_ISGID)
            {
                info[info.length()-1]='s';
            }
            
        }
        else
        {
            info+='-';
             if(vec_stat[index].st_mode & S_ISGID)
            {
                info[info.length()-1]='S';
            }
        }

        //Other permission


        if(vec_stat[index].st_mode & S_IROTH)
        {
            info+='r';
        }
        else
        {
            info+='-';
        }
        

        if(vec_stat[index].st_mode & S_IWOTH)
        {
            info+='w';
        }
        else
        {
            info+='-';
        }
        

        if(vec_stat[index].st_mode & S_IXOTH)
        {

            info+='x';
            
        }
        else
        {
            info+='-';
            
        }

        info +=" ";
        //
        passwd* pd= getpwuid(vec_stat[index].st_uid);
        info += pd->pw_name;

        info +=" ";
        group* gd= getgrgid(vec_stat[index].st_gid);
        info += gd->gr_name;
        info +=" ";

        struct tm time_format;
        localtime_r(&vec_stat[index].st_mtim.tv_sec,&time_format) ;

        char file_mtime[256];
        strftime(file_mtime,sizeof(file_mtime),"%b %d %R ",&time_format);

        info +=file_mtime;


        info+=vec_filename[index];

        cout<<info<<endl;


       
        

       
    }


}