#include<iostream>
#include<thread>
#include<future>
#include<vector>
using namespace std;
//引入future，async
template <class T>  //泛型
void measure(T&& func)       //&& 综合引用
{
    using namespace std::chrono;
    auto start=system_clock::now();   //chrono里面的命名变量
    func();             //测试函数
    duration<double> diff=system_clock::now()-start;
    cout<<"elasped: "<<diff.count()<<"s"<<endl;
}
long sum(long start,long end)
{
    long s=0;
    for(long i=start;i<end;i++)
    {
        s+=i;
    }
    return s;
}
const long S=10000000;
int main()
{
    measure([](){
        const long K=6;
        vector<future<long>>vf;
        vf.reserve(K);
        for(int i=0;i<K;i++)
        {
            vf.push_back(async(sum,i==0 ? 0 :(S/K)*i,(S/K)*(i+1)));     //计算步骤分成K个部分，K个子线程去并行，省时间
        }
        long long ans=0;
        for(int i=0;i<K;i++)
        {
            ans+= vf[i].get();
        }
        cout<<ans<<endl;
    });
    measure([](){
        long long ans=sum(0,S);
        cout<<ans<<endl;

    });
    system("pause");
    return 0;
}
