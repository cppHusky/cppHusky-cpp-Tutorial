#include <iostream>
using namespace std;
void g() { throw string("error"); }
void f() {
    int *p = new int;
    try{
        g();
    } catch (const string &error) {
        delete p; //回收p指向的动态内存
        throw error; //把接收到的异常对象继续抛出
    }
}
int main() {
    try {
        f();
    } catch (const string &error) {
        cout << error;
    }
    return 0;
}