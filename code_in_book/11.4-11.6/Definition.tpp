#pragma once //千万不要遗漏
#include "array.hpp" //这句可以没有，但是为了编译器检查方便，还是包含一下吧
#include <algorithm> //包含std::min等实用函数
//类模板std::array<T,N>的成员函数及一些非成员函数的定义
template<typename T, std::size_t N>
user::array<T, N>::array(std::initializer_list<T> ilist) : _elem{} {
//指明我们要定义的函数是user::array<T,N>的成员array
    std::size_t i {0};
    for (auto item : ilist) {
        _elem[i++] = item;
        if (i == N) //防止ilist长度超过N，避免数组越界
            break;
    } //若ilist长度不足N，那么_elem后面的部分保留初值列中的初始化值，即0
};
template<typename T, std::size_t N>
user::array<T, N>::array(const array &arr) {
    for (std::size_t i = 0; i < N; i++)
        _elem[i] = arr._elem[i];
}
template<typename T, std::size_t N>
auto user::array<T, N>::operator=(const array &arr) -> array& {
//auto占位，->后接返回类型，编译器将会自行推导auto意味着什么
    if (this == &arr) //防止自我赋值
        return *this;
    for (std::size_t i = 0; i < N; i++)
        _elem[i] = arr._elem[i];
    return *this;
}
template<typename T, std::size_t N>
constexpr T& user::array<T, N>::at(std::size_t pos) {
    if (pos >= N) //本来应该有异常抛出机制，但是我们还没学，所以先这样湊合下
        pos = N - 1;
    return _elem[pos];
}
template<typename T, std::size_t N>
constexpr const T& user::array<T, N>::at(std::size_t pos)const {
    if (pos >= N)
        pos = N - 1;
    return _elem[pos];
}
template<typename T, std::size_t N>
constexpr T& user::array<T, N>::operator[](std::size_t pos) {
    return _elem[pos];
}
template<typename T, std::size_t N>
constexpr const T& user::array<T, N>::operator[](std::size_t pos)const {
    return _elem[pos];
}
template<typename T, std::size_t N>
void user::array<T, N>::fill(const T &val) {
    for (std::size_t i = 0; i < N; i++)
        _elem[i] = val;
}
template<typename T, std::size_t N>
constexpr bool user::operator<(
    const array<T, N> &lhs, const array<T, N> &rhs
) {
    return std::lexicographical_compare(
        lhs._elem, lhs._elem + N,
        rhs._elem, rhs._elem + N
    );
}
template<typename T, std::size_t N>
constexpr bool user::operator>(
    const array<T, N> &lhs, const array<T, N> &rhs
) {
    return rhs < lhs;
}
template<typename T, std::size_t N>
constexpr bool user::operator<=(
    const array<T, N> &lhs, const array<T, N> &rhs
) {
    return !(rhs < lhs);
}
template<typename T, std::size_t N>
constexpr bool user::operator>=(
    const array<T, N> &lhs, const array<T, N> &rhs
) {
    return !(lhs < rhs);
}
template<typename T, std::size_t N>
constexpr bool user::operator==(
    const array<T, N> &lhs, const array<T, N> &rhs
) {
    return !(lhs != rhs);
}
template<typename T, std::size_t N>
constexpr bool user::operator!=(
    const array<T, N> &lhs, const array<T, N> &rhs
) {
    return lhs < rhs || rhs < lhs;
}
template<std::size_t I, typename T, std::size_t N>
T& user::get(array<T, N> &arr) {
    return arr._elem[I];
}
template<std::size_t I, typename T, std::size_t N>
const T& user::get(const array<T, N> &arr) {
    return arr._elem[I];
}
template<typename T, std::size_t N> //类模板参数，用来指定user::array<T,N>
template<std::size_t M> //函数模板参数，用来指定函数参数user::array<T,M>&
void user::array<T, N>::swap(array<T, M> &arr) {
    constexpr std::size_t minlen {std::min(N, M)};
    for (std::size_t i = 0; i < minlen; i++)
        std::swap(_elem[i], arr._elem[i]);
}
template<typename T, std::size_t N, std::size_t M>
void user::swap(array<T, N> &lhs, array<T, M> &rhs) {
    constexpr std::size_t minlen {std::min(N, M)}; //这个结果将在编译时求出
    for (std::size_t i = 0; i < minlen; i++)
        std::swap(lhs._elem[i], rhs._elem[i]); //可以访问私有成员
}

//类模板特化std::array<bool,N>的成员函数及部分相关非成员函数的定义
template<std::size_t N>
user::array<bool, N>::array(std::initializer_list<bool> ilist) : _elem {} {
    std::size_t i {0};
    for (auto item : ilist) {
        _elem[i++] = item; //std::bitset支持这样的赋值
        if (i == N) //防止ilist长度超过N，避免数组越界
            break;
    } //若ilist长度不足N，那么_elem后面的部分保留初值列中的初始化值，即0
}
template<std::size_t N>
user::array<bool, N>::array(const array &arr) {
    for (std::size_t i = 0; i < N; i++)
        _elem[i] = arr._elem[i];
}
template<std::size_t N>
auto user::array<bool, N>::operator=(const array &arr) -> array& {
//auto占位，->后接返回类型，编译器将会自行推导auto意味着什么
    if (this == &arr) //防止自我赋值
        return *this;
    for (std::size_t i = 0; i < N; i++)
        _elem[i] = arr._elem[i];
    return *this;
}
template<std::size_t N>
constexpr bool& user::array<bool, N>::at(std::size_t pos) {
    if (pos >= N)
        pos = N - 1;
    return _elem[pos];
}
template<std::size_t N>
constexpr const bool& user::array<bool, N>::at(std::size_t pos)const {
    if (pos >= N)
        pos = N - 1;
    return _elem[pos];
}
template<std::size_t N>
constexpr bool& user::array<bool, N>::operator[](std::size_t pos) {
    return _elem[pos];
}
template<std::size_t N>
constexpr const bool& user::array<bool, N>::operator[](std::size_t pos)const {
    return _elem[pos];
}
template<std::size_t N>
void user::array<bool, N>::fill(bool val) {
    for (std::size_t i = 0; i < N; i++)
        _elem[i] = val;
}
//比较运算符和get函数均无需再重载
template<std::size_t N, std::size_t M>
void user::swap(array<bool, N> &lhs, array<bool, M> &rhs) {
    constexpr std::size_t minlen {std::min(N, M)};
    for (std::size_t i = 0; i < minlen; i++)
        std::swap(lhs._elem[i], rhs._elem[i]);
}
template<std::size_t N> //类模板参数
template<std::size_t M> //函数模板参数
void user::array<bool, N>::swap(array<bool, M> &arr) {
    constexpr std::size_t minlen {std::min(N, M)};
    for (std::size_t i = 0; i < minlen; i++)
        std::swap(_elem[i], arr._elem[i]);
}