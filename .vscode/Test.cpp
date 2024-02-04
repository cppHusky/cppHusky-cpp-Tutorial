//这段程序可以告诉你当前使用的C++标准和编译器都是什么
#include <iostream> //标准输入输出头文件
using namespace std; //使用std命名空间
int main() { //主函数；以上都是固定格式，照搬就行
    cout << "Current C++ Standard: " << __cplusplus << endl; //语言标准
#if defined(__clang__) || defined(__llvm__) //通过检测宏常量判断编译器类型
    cout << "Current C++ Compiler: Clang" << endl; //Clang编译器
#elif defined(__GNUC__) || defined(__GNUG__)
    cout << "Current C++ Compiler: GCC" << endl; //GCC编译器
#elif defined(_MSC_VER)
    cout << "Current C++ Compiler: MSVC" << endl; //MSVC编译器
#else //如果你使用的是其它编译器，那么将会输出Others；本书不推荐读者使用其它编译器
    cout << "Current C++ Compiler: Others" << endl;
#endif
    return 0;
}