#include <iostream>
#include <fstream>
#include <filesystem>
#include <stack>
namespace fs = std::filesystem; //命名空间别名
int main() {
    try {
        fs::path ph {fs::current_path()}; //ph就是当前文件夹的路径
        std::ifstream fin {ph / "in.txt"}; //在ph文件夹下的in.txt中操作
        std::ofstream fout {ph / "out.txt"}; //在ph文件夹下的out.txt中操作
        if (!fin.is_open()) //输入文件异常检测
            throw std::ios_base::failure {"Cannot open in.txt"};
        if (!fout.is_open()) //输出文件异常检测
            throw std::ios_base::failure {"Cannot open out.txt"};
        std::stack<char> stk;
        int ch = {fin.get()}; //定义一个ch，逐个字符地接收get()输入数据
        while (!fin.eof()) { //如果fin还没有读到文件结尾
            stk.push(ch); //就说明ch是有效内容，把它填入栈中
            ch = fin.get(); //再接收下一个字符输入
        }
        while (stk.size()) { //只要栈中还有数据，那就说明输出还没到头
            fout << stk.top(); //用fout输出栈顶元素
            stk.pop(); //栈顶的元素弹出
        }
        std::cout << "Done" << std::endl; //提示操作完成
    } catch (const std::ios_base::failure &msg) {
        std::cerr << "An exception has been caught:\n" << msg.what();
    }
    return 0;
}