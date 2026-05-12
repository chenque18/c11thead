


# lock_guard
- 当构造函数被调用时，该互斥量会被自动锁定。
- 当析构函数被调用时，该互斥量会被自动解锁。
- `std::lock_guard` 对象不能复制或移动，因此它只能在局部作用域中使用。
```cpp
#include <thread>
int a = 0;
mutex m;
void func(){
    for(int i = 0; i < 1000000; i++){
        lock_guard<mutex> lock(m); // 构造时自动加锁，析构时自动解锁
        a++;
    }
}
int main(){
    thread t(func);
    thread t1(func);
    t.join();
    t1.join();  
    return 0;
}
```

# unique_lock
- `std::unique_lock` 是一个更灵活的互斥量管理类，提供了更多的功能和控制选项。
```cpp
unique_lock<mutex> lock1(m); // 构造时自动加锁,析构时自动解锁
lock1.unlock(); // 可选择手动解锁

unique_lock<mutex> lock2(m, defer_lock); // 构造但不加锁，要手动加锁
//可以配合try_lock_for等函数实现超时加锁
//try_lock();  尝试加锁，不等待如果成功返回true，否则返回false
lock2.try_lock_for(std::chrono::seconds(1)); // 尝试加锁，只等待1秒，如果成功返回true，否则返回false

lock(m1,m2); // 同时锁定多个互斥量，内部算法会避免死锁

```
