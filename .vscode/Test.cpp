#include <iostream>
#include <type_traits>
int main(){
    using namespace std;
    constexpr static const char *str {"cppHusky"};
    cout << (void*)str << endl;
    cout << &str; //这两个输出结果可是不一样的
    return 0;
}