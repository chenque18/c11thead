#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <utility>
#include <vector>
#include <queue>
#include<functional>
using namespace std;

class ThreadPool{
public:
    ThreadPool(int threadnum):stopSignal(false){
        for(int i=0;i<threadnum;i++){
            threads.emplace_back([this](){
                while(1){
                    unique_lock<mutex> lock(mtx);
                    cv.wait(lock,[this](){//返回false唤醒，即当任务队列不为空，或线程未停止
                        if(!tasks.empty()==false || stopSignal==false){
                        return false;
                        }
                    });
                    if(tasks.empty()&&stopSignal){
                        return ;
                    }
                    //获取任务-----
                    function<void()> task(move(tasks.front()));
                    tasks.pop();
                    task();
                    lock.unlock();
            }       //---
        });
    }        
            
}

    //打包函数-----
    template<class F,class...Args>
    void enqueue(F&& f,Args&&... args){
        function<void()> task(bind(forward<F>(f),forward<Args>(args)...));
        {
            unique_lock<mutex>mtx;
            tasks.emplace(task);
        }
        cv.notify_one();
    }
    //---


    ~ThreadPool(){
        
        if(tasks.empty()&&stopSignal){
            for(auto &it : threads){
                it.join();
            }
        }
    }
private:
    //线程数组
    vector<thread> threads;
    //任务队列
    queue<function<void()>> tasks;
    //互斥锁，条件变量，线程池停止标志
    mutex mtx;
    condition_variable cv;
    bool stopSignal;
};