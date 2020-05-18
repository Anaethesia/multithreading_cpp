#include<functional>
#include<iostream>
#include<fstream>
#include<thread>
#include<string>
#include<mutex>
#include<deque>
#include<condition_variable>
using namespace std;
//生产者-消费者问题
//使用条件变量确定线程先后顺序
deque<int>q;
mutex mtx;    //互斥对象
std::condition_variable cond;
void func1()
{
    int count=10;
    while(count>0)
    {
        unique_lock<mutex> locker(mtx);//func1和2都有用到共享队列q，所以要加上互斥锁
        q.push_front(count);
        locker.unlock();
        cond.notify_one();       //激活后面的wait，避免线程2无意义循环
        //cond.notify_all();     //激活后面所有的线程
        this_thread::sleep_for(chrono::seconds(1));
        count--;
    }
}
void func2()
{
    int data=0;
    while(data!=1)
    {
        unique_lock<mutex> locker(mtx);
        cond.wait(locker,[](){return !p.empty(); });//需要重复的加解锁，所以需要用unique_lock
        data=q.back();
        q.pop_back();
        locker.unlock();
        cout<<"t2 got a value from t1:"<<data<<endl;
        // if(!q.empty())
        // {
        //     data=q.back();
        //     q.pop_back();
        //     locker.unlock();
        //     cout<<"t2 got a value from t1:"<<data<<endl;
        // }
        // else{
        //     locker.unlock();
        // }
    }
}
int main()
{
    thread t1=thread(func1);
    thread t2=thread(func2);
    t1.join();
    t2.join();
    system("pause");
    return 0;
}


