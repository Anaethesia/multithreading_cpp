#include <iostream>
#include <thread>
using namespace std;
//创建一个多线程
void func(int &a,int b)
{
    cout<<"the sum is "<<a+b<<endl;
    cout<<"the thread id is "<<this_thread::get_id()<<endl;
}
int main()
{
    int a=5;
    int b=3;
    thread th=thread(func,ref(a),b);       //子线程id
    th.join();
    cout<<"the thread id is "<<this_thread::get_id()<<endl;   //主线程id
    system("pause");
    return 0;
}