//这个程序可以接收三个输入整数，并给出它们的最大值
#include <iostream> //标准输入输出头文件
using namespace std; //使用命名空间std
long long max3(long long, long long, long long); //声明
int main() {
    long long a, b, c; //定义long long型变量a,b
    cin >> a >> b >> c; //输入a,b的值
    cout << max3(a, b, c); //输出a,b,c的最大值
    return 0;
}
long long max(long long a, long long b) {
    //接收两个long long参数，给出long long返回值
    if (a > b) { //当a>b时返回a
        return a;
    }
    else { //否则返回b
        return b;
    }
}
long long max3(long long a, long long b, long long c) {
    //接收三个long long参数，给出long long返回值
    const long long max_ab {max(a,b)};
    if (max_ab > c) { //如果a,b的最大值大于c，返回前者
        return max_ab;
    }
    else { 否则返回后者
        return c;
    }
}