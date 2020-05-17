#include<bits/stdc++.h>
#include <mutex>
#include <future>
using namespace std;
//引入call_once确保lambda线程只会被调用一次
class LogFile {
    std::once_flag m_flag;
	ofstream f;
	std::mutex m1,m2;
public:
	LogFile() {
		f.open("log.txt");
	}
	void shared_print(string msg,int idx) {
        {
            std::call_once(m_flag,[&](){f.open("log.txt");});
            
        }
		
	}
};
