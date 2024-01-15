#include <iostream>
using namespace std;
void input_clear() {
    cin.clear(); //清除错误状态
    while (cin.get() != '\n') //清除本行输入
        continue;
}
int main() { //主函数
    int sum {0}, x {1}; //x初始化为1是为了防止误结束循环
    while (x != 0) { //当x为0时结束循环
        cin >> x; //输入x的值
        if (!cin) {
            input_clear(); //清除错误和错误输入
            x = 1; //x赋为1，否则可能导致循环误结束
            cout << "请输入数字！输入0结束计算" << endl;
            continue; //跳过sum+=x的操作
        }
        sum += x; //这是一个复合赋值运算符，等效于sum=sum+x
    }
    cout << "总数为：" << sum;
    return 0;
}