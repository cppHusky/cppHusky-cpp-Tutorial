#pragma once
#include <cstddef> //std::size_t定义在cstddef库中；不过其它库中亦有
//本代码适合C++11以前标准，即通过拷贝构造/赋值来实现交换
//C++11以后应使用移动构造/赋值实现交换
namespace user { //定义在user命名空间中
template<typename T>
void swap(T &a, T &b) {
    T tmp {a};
    a = b;
    b = tmp;
}
template<typename T, std::size_t N> //模版参数N表示这个数组的长度
void swap(T (&a)[N], T (&b)[N]) { //参数是两个T(&)[N]
    for (int i = 0; i < N; i++)
        user::swap(a[i], b[i]); //调用已经定义好的user::swap
}
};