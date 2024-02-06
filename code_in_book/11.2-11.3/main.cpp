#include "is_same.hpp"
#include <iostream>
int main() {
    int (*p1)[3] {}, *p2[3] {};
    std::cout << user::is_same<int(*)[3], int*[3]>() << std::endl //输出0
              << user::is_same<int(&)[3]>(*p1) << std::endl //输出0
              << user::is_same<int[3]>(*p1) << std::endl //输出1
              << user::is_same<>(p1, p2) << std::endl; //输出0
    return 0;
}