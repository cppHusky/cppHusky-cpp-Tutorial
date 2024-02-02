#include<iostream>
#include<sstream>
#include<iomanip>
int main() {
    std::cout.setf(std::ios_base::hex, std::ios_base::basefield); //十六进制输出
    std::cout.setf(std::ios_base::showbase); //显示前缀
    std::cout << std::setw(8) << 123 << '\n'; //默认右对齐
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield); //改为左对齐
    std::cout << std::setw(8) << 123 << '\n';
    std::cout.setf(std::ios_base::internal, std::ios_base::adjustfield); //两端对齐
    std::cout << std::setw(8) << 123 << '\n';
    return 0;
}