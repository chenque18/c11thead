#include <iostream>
#include <thread>
#include <mutex>
#include <chrono> // 使用 C++11 标准时间库
using namespace std;

mutex m1, m2;

void func1() {
    //使用 lock 同时锁定多个互斥量，内部算法会避免死锁
    lock(m1, m2);
    // 使用 adopt_lock 告诉 lock_guard 互斥量已经被锁定了，只需负责在退出时自动解锁
    lock_guard<mutex> lock1(m1, adopt_lock);
    lock_guard<mutex> lock2(m2, adopt_lock);

    this_thread::sleep_for(chrono::milliseconds(100));
}

void func2() {
    // 同样使用 lock 一次性获取，顺序已经不影响了
    lock(m1, m2);
    lock_guard<mutex> lock1(m1, adopt_lock);
    lock_guard<mutex> lock2(m2, adopt_lock);

    this_thread::sleep_for(chrono::milliseconds(100)); // 模拟线程在工作
}

int main() {
    thread t1(func1);
    thread t2(func2);
    t1.join();
    t2.join();
    cout << "程序结束" << endl;
    return 0;
}