//这是一个简易计算器，可以支持简单的四则运算或模运算。不支持复杂表达式的计算
#include <iostream>
using namespace std;
int main() {
    while (cin) { //如果cin状态正常，就继续循环
        double num1, num2, result; //定义两个操作数num及结果值result
        char op; //定义一个字符用来存储运算符输入
        cin >> num1 >> op >> num2; //依次输入左操作数、运算符和右操作数
        if (!cin) { //如果cin状态不正常，说明输入了非预期内容，退出循环
            break;
        }
        switch (op) { //判断op是什么
            case '+': //根据op的值，采取相应的操作
                result = num1 + num2; //通过赋值的方式存储结果
                break; //记得用break
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                result = num1 / num2;
                break;
            case '%':
                result = static_cast<int>(num1) % static_cast<int>(num2);
                //显式类型转换，将double型的num1和num2转换为int，这样才能计算
                //末尾的break省略
        }
        cout << "=" << result << endl; //输出result的值
    }
    cout << "程序结束" << endl; //提示用户程序结束
    return 0;
}