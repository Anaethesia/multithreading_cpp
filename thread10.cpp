#include<iostream>
#include<fstream>
#include<thread>
#include<string>
#include<mutex>
#include<condition_variable>
#include<future>
//父子线程之间通过future和promise获取变量
using namespace std;

int factorial(future<int>&f)
{
    int res=1;
    int N=f.get();
    for(int i=N;i>1;i--)
    {
        res *=i;
    }
    cout<<"Result is "<<res<<endl;
    return res;
}
// int factorial(int N)
// {
//     int res=1;
//     for(int i=N;i>1;i--)
//     {
//         res *=i;
//     }
//     cout<<"Result is "<<res<<endl;
//     return res;
// }
int main()
{
    int x;
    promise<int>p;                            //promise和set_value对应，子线程获取父线程的值。
    future<int> f=p.get_future();
    future<int> fu=async(factorial,ref(f));
    p.set_value(4);
    x=fu.get();


    // future<int> fu=async(factorial,4);    //父线程获取子线程的量，future就是从未来获取某个变量的类
    // x=fu.get();                           //get只能调用一次，否则系统会崩溃。


    // thread t1=thread(factorial,4);
    // t1.join();
    system("pause");
    return 0;
}