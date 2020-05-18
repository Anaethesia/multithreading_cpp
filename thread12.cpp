#include<iostream>
#include<fstream>
#include<thread>
#include<string>
#include<mutex>
#include<condition_variable>
#include<future>
#include<deque>
    
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
deque<packaged_task<int()>> task_q;
void thread_1()
{
    packaged_task<int()> t;
    {
        unique_lock<mutex>locker(mu);
        cond.wait(locker.[]{return !task_q.empty();});
        t=move(task_q.front());

    }
    
    t();
}

int main()
{
    thread t1(thread_1);
    packaged_task<int()> t(bind(factorial,6));
    future<int> ret=t.get_future();    //获得与packaged_task相关联的future对象
    {
        lock_guard<mutex>locker(mu);      //thread1主线程子线程都有用到队列q，所以要保护。
        task_q.push_back(t);
    }
    cond.notify_one();
    int value=ret.get();
    t1.join();



}