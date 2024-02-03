#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
int main() {
    std::string input {".4+1.2\n3.14*2\n1/10\n5-3"}; //input中有我们预设的初值
    std::istringstream sin; //定义
    sin.str(input); //把input的内容赋值到sin
    std::ostringstream sout {}; //用空串来初始化ostringstream对象
    while (!sin.eof()) { //这里最好用!sin.eof()；如果直接写sin，后文中还要作检测
        double num1, num2;
        char op;
        sin >> num1 >> op >> num2; //从sin底层字符串中直接获取输入内容
        switch (op) {
            case '+':
                sout << num1 + num2 << ' '; //把内容输出到sout底层字符串中
                break;
            case '-':
                sout << num1 - num2 << ' '; //同上
                break;
            case '*':
                sout << num1 * num2 << ' ';
                break;
            case '/':
                sout << num1 / num2 << ' ';
                break;
        }
    }
    std::cout << sout.str(); //把output中的内容输出到屏幕上
    return 0;
}