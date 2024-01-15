// 这是一个简单的C++程序，用于输出一些整型数值的上/下限值
#include <iostream> //标准输入输出头文件
#include <limits> //标准算术类型属性头文件，numeric_limits定义于此
using namespace std; //使用std命名空间
int main(){ //主函数，程序执行始于此
    cout << numeric_limits<short>::lowest(); //输出short类型的下限值
    cout << endl; //输出换行，下同
    cout << numeric_limits<short>::max(); //输出short类型的上限值
    cout << endl;
    cout << numeric_limits<unsigned>::lowest(); //输出unsigned类型的下限值
    cout << endl;
    cout << numeric_limits<unsigned>::max(); //输出unsigned类型的上限值
    return 0;
}