#include<iostream>
#include<thread>
#include<future>
#include<vector>
using namespace std;
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
class A{
public:
    A() {
        cout<<"A start"<<endl;
    }
    ~A(){
        cout<<"A end"<<endl;

    }
};
int g=0;
void fun()
{
    {
        std::lock_guard<std::mutex> guard(mtx);    //std::lock_guard是一个局部变量，创建时，g_i_mutex 上锁，析构时g_i_mutex解锁。
                                                  //这个功能在函数体比较长，尤其是存在多个分支的时候很有用。 
        g++;
    }
}
int main()
{
    A a;
    //return 0;       注意结束语句放在这两个位置的区别，同时具有构造和析构效果
    A b;
    //return 0;
    A *p=new A();    //只有构造没有析构
    delete p;         //析构效果
    system("pause");
    return 0;
}