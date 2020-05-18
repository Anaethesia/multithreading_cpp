#include<iostream>
#include<fstream>
#include<thread>
#include<string>
#include<mutex>
#include<condition_variable>
#include<future>
using namespace std;
//线程之间的调用方式
class A
{
public:
    void f(int x,char c)
    {

    }
    int operator()(int N)
    {
        return 0;
    }
};
int main()
{
    A a;
    thread t1=thread(a,6);              //传递a的拷贝给子线程
    thread t2=thread(ref(a),6);         //传递a引用
    thread t3=thread(move(a),6);        //a在主线程中不会有效
    thread t4=thread(A(),6);            //临时创建的a对象给子线程
    thread t5=thread([](int x){return x*x;},6);
    thread t6=thread(&A::f,a,8,'w');       //传递的a拷贝的函数给子线程
}