#include <unistd.h>
#include <iostream>
#include <vector>


using namespace std;

int main(int argc, char* argv[])
{
    cout<<"Hello,World!"<<endl;
    vector<int> vec={0,1,2,3,4};

    for(auto x:vec)
    {
        cout<<x<<endl;
    }

    pid_t process_id= getpid();
    cout<<"The current process id is "<<process_id<<endl;
    return 1;

}