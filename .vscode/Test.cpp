#include<iostream>
#include<exception>
#include<stdexcept>
#include<vector>
void func()noexcept { }
void func(int n) { }
int main() {
    std::vector<int> vec(3); //vec的长度为3
    std::cout << noexcept(vec.at(2))<<std::endl;
    std::cout << noexcept(vec.at(3))<<std::endl;
    return 0;
}