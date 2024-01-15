//这段代码可以判断输入的正整数是奇数还是偶数
#include <iostream>
using namespace std;
int main() { //主函数，代码顺序执行
    int num; //也可以用unsigned
    cin >> num; //输入num变量
    const int mod {num % 2}; //num模除2的值；也可以不用const
    if (mod == 1) { //选择结构
    	cout << "奇数";
    }
    else {
    	cout << "偶数";
    }
    return 0;
}