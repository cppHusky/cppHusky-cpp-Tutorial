//用递归方法实现阶乘函数
#include <iostream>
using namespace std;
//如果fractorial的参数大于12，就会发生运算结果溢出。可以考虑用unsigned long long
unsigned factorial(unsigned n) { //阶乘的参数和值都不是负数，所以定义成unsigned
    if (n == 0) { //终止条件，不可或缺
        return 1; //0!为1，直接返回
    }
    else { //如果没有到达终止条件，就调用factorial(n-1)，离终止条件更近一步
        return n * factorial(n - 1); //递归，n!用n*(n-1)!表示
    }
}
int main() {
    cout << factorial(12); //计算并输出12!的值
    return 0;
}