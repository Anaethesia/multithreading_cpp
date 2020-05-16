#include <iostream>
#include <thread>
using namespace std;
//测试函数的运行效率
template <class T>  //泛型
void measure(T&& func)       //&& 综合引用
{
    using namespace std::chrono;
    auto start=system_clock::now();   //chrono里面的命名变量
    func();             //测试函数
    duration<double> diff=system_clock::now()-start;
    cout<<"elasped: "<<diff.count()<<"s"<<endl;

}
int main()
{
    measure([](){
        long long s;
        for(int i=0;i<200000000;i++)
        {
            s+=i;
        }
    });
    system("pause");
    return 0;
}