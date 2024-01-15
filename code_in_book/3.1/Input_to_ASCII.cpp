// 这是一个简单的程序，用来将用户所有的输入转为ASCII码
// 读者无需掌握本代码的全部细节，后续会讲到
#include <iostream> //标准输入输出头文件
using namespace std; //使用命名空间std
int main() { //主函数，程序执行始于此
    char c; //定义一个char变量c用以接收输入
    while (cin.good()) { //while循环，当cin状态正常时继续循环
        c = cin.get(); //通过cin.get()接收输入，并存入c
        std::cout << static_cast<int>(c) << std::endl;
        //强制类型转换为int，故以ASCII码值形式显示输入内容
    }
}