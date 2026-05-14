#include <thread>
#include <iostream>
#include <atomic>
using namespace std;
atomic<int> a(0); 
void test(){
    for(int i = 0; i < 1000000; i++){
        a++;
    }
}
int main() {
    thread t(test);
    thread t1(test);
    t1.join();
    t.join();
    cout << a << endl;
    return 0;
}