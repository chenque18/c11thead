

# 单例模式（Singleton Pattern）是一种经典的设计模式，它的核心目标：确保一个类在整个程序运行期间只有一个实例，并提供一个全局访问点来获取该实例。
## 懒汉模式：在第一次调用 getInstance() 时才创建实例  
```cpp
class Singleton {
private:
    Singleton() { /* 初始化 */ }
public:
    //禁用复制构造函数和=
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    
    static Singleton& getInstance() {
        static Singleton instance; //懒汉模式
        return instance;
    }
};
```
## 饿汉模式：在程序启动（进入 main 函数之前）就会立刻创建唯一实例，而不是等到第一次真正调用 getInstance() 时再去创建
```cpp
class SingletonEager {
private:
    SingletonEager() { /* 初始化 */ };
public:
    // 禁用拷贝构造和赋值
    SingletonEager(const SingletonEager&) = delete;
    SingletonEager& operator=(const SingletonEager&) = delete;
        
    // 声明静态成员
    static SingletonEager instance;
    static SingletonEager& getInstance() {
        return instance;
    }
};
// 外部调用的方式
SingletonEager& instance = SingletonEager::getInstance();
```

# call_once（只能多线程使用）
- 主要用于确保某个函数只被调用一次，以防多线程重复调用,需要先定义一个 `std::once_flag xx` 类型的标志变量，才能call_once(xx,func);
```cpp
#include <mutex>
#include <mutex>
class SingletonCallOnce; 
std::once_flag init_flag;
SingletonCallOnce* instance = nullptr;
class SingletonCallOnce {
private:
    SingletonCallOnce() { /* 初始化资源 */ }
    
    static SingletonCallOnce* instance; // 指针形式的单例
    static std::once_flag init_flag;    // 用于标记是否已经初始化过

public:
    // 禁用拷贝构造和赋值
    SingletonCallOnce(const SingletonCallOnce&) = delete;
    SingletonCallOnce& operator=(const SingletonCallOnce&) = delete;

    static SingletonCallOnce* getInstance() {
        std::call_once(init_flag, []() {
            instance = new SingletonCallOnce();
        });
        return instance;
    }
};



