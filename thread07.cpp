#include<bits/stdc++.h>
#include <mutex>
#include <future>
using namespace std;

class LogFile {
	ofstream f;
	std::mutex m1,m2;
public:
	LogFile() {
		f.open("log.txt");
	}
	void shared_print(string msg,int idx) {
		unique_lock<mutex> locker(m1,defer_lock); //第三种加锁方式
		locker.unlock();
		//do_something(); //此代码块不想加锁
		locker.lock(); // 解锁之后还可以加锁，增加灵活性。
		f << msg << ":" << idx << endl;
		locker.unlock(); 
		//do_some_other_thing();
		locker.lock();
		//此外unique_lock可以被移动，lock_guard则不能被移动
		unique_lock<mutex> locker2 = move(locker);
	}
};
