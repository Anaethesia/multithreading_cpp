#include <iostream>
#include <thread>
using namespace std;
//子线程之间的相互竞争
class A
{
public:
    void operator () (int limit)
    {
        for(int i=0;i<limit;i++)
        {
            cout<<"A IS "<<i<<endl;

        }
    }
    void operator - (int limit)
    {
        for(int i=0;i<limit;i++)
        {
            cout<<"B is "<<i<<endl;
        }
    }
};

int main()
{
    thread thread1=thread(A(),50);
    for(int i=0;i<50;i++)
    {
        cout<<"I'm "<<i<<endl;
    }
    thread1.join();         //子线程之间的相互竞争
    system("pause");
    return 0;
}
