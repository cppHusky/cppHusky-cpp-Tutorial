// 这是一个简单的C++程序，用于简易的数值计算
#include <iostream> //标准输入输出头文件
using namespace std; //使用std命名空间
int main(){ //主函数，程序执行始于此
    double a {1.5}, b {0.3}, c {0.5}, d {4.5}; //定义并初始化
    cout << (a + b * c) / d; //输出(a+b*c)/d的值
    return 0;
}