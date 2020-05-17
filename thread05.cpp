#include<iostream>
#include<thread>
#include<future>
#include<vector>
using namespace std;
//mutex实现互斥锁
template <class T>  //泛型
void measure(T&& func)       //&& 综合引用
{
    using namespace std::chrono;
    auto start=system_clock::now();   //chrono里面的命名变量
    func();             //测试函数
    duration<double> diff=system_clock::now()-start;
    cout<<"elasped: "<<diff.count()<<"s"<<endl;
}
std::mutex mtx;        //实例化一个互斥锁
void sum(int& s)
{
    mtx.lock();
    for(int i=0;i<1000000;i++)
    {
        s++;
    }
    mtx.unlock();
}
//C++互斥锁
int main()
{
    measure([](){
        vector<thread> v;
        int s=0;
        for(int i=0;i<4;i++)
        {
            v.emplace_back(sum,ref(s));
        }
        for(int i=0;i<4;i++)
        {
            v[i].join();
        }
        cout<<s<<endl;
    });
    system("pause");
    return 0;
}
