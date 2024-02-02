#include<iostream>
#include<exception>
#include<stdexcept>
#include<vector>
#include<sstream>
#include<stdio.h>
int main() {
    std::istringstream sin {"25 1.3 Alan Turing"}; //需要包含sstream库
    std::cin.rdbuf(sin.rdbuf()); //重定向之后，cin的源就是sin中存的字符串
    int i;
    double d;
    char str[50];
    std::cin >> i >> d >> str;
    std::cout << i << '\n' << d << '\n' << str << '\n';
    std::cin >> str;
    std::cout << str << std::endl;
    return 0;
}