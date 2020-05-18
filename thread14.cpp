#include<iostream>
#include<fstream>
#include<thread>
#include<string>
#include<mutex>
#include<condition_variable>
#include<future>
#include<deque>
//线程，锁，条件变量，future的时间机制
using namespace std;
std::mutex mu;
std::condition_variable cond;
int factorial(int N)
{
    int res=1;
    for(int i=N;i>1;i--)
    {
        res *=i;
    }
    cout<<"Result is "<<res<<endl;
    return res;
}
int main()
{
    thread t1(factorial,6);
    this_thread::sleep_for(chrono::milliseconds(5));

    unique_lock<mutex> locker(mu);
    locker.try_lock_for(chrono::milliseconds(5));

    cond.wait_for(locker,chrono::milliseconds(5));

    std::promise<int> p;
    future<int> f=p.get_future();
    f.wait_for(chrono::milliseconds(5));

    system("pause");
    return 0;



}