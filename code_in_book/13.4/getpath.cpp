#include <iostream>
#include <filesystem> //filesystem相关的内容在这里
namespace fs = std::filesystem; //因为名字太长了，所以起个命名空间别名
int main() {
    fs::path ph {fs::current_path()}; //获取“当前文件夹”的路径
    std::cout << ph << std::endl; //直接输出路径对象
    std::cout << ph.generic_string() << std::endl; //以通用格式输出
    std::cin.get(); //可能需要这句
    return 0;
}