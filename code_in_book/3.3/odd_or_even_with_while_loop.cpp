//这是一个基于while循环的奇偶判断程序，当输入为字母时停止循环
#include <iostream> //标准输入输出头文件
using namespace std; //命名空间使用
int main() { //主函数
    int num; //定义num，可不初始化
    while (cin >> num) { //输入num并使用cin的返回值作为判断条件
        const int mod {num % 2}; //num模除2的值
        if (mod == 0) { //判断是否为偶数
            cout << "偶数" << endl;
        }
        else { //mod可能是1或-1，我们把它们都归入else中
            cout << "奇数" << endl;
        }
    }
    cout << "程序结束"; //输出一个提示语，告诉用户程序结束
}