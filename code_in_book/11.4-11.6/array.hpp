#pragma once
#include <initializer_list>
#include <type_traits> //std::is_same定义在type_traits库中
namespace user {
//模板声明部分
template<typename, std::size_t> //模板形参的名字可以省略
class array; //声明array类模板
template<std::size_t I, typename T, std::size_t N>
T& get(array<T, N>&); //可以接收非常量对象，并具备修改元素的能力
template<std::size_t I, typename T, std::size_t N>
const T& get(const array<T, N>&); //可以接收常量对象，不具备修改元素的能力
template<typename T, std::size_t N, std::size_t M>
void swap(array<T, N>&, array<T, M>&); //交换不同长度的数组
template<typename T, std::size_t N>
constexpr bool operator<(const array<T, N>&, const array<T, N>&);
template<typename T, std::size_t N>
constexpr bool operator>(const array<T, N>&, const array<T, N>&);
template<typename T, std::size_t N>
constexpr bool operator<=(const array<T, N>&, const array<T, N>&);
template<typename T, std::size_t N>
constexpr bool operator>=(const array<T, N>&, const array<T, N>&);
template<typename T, std::size_t N>
constexpr bool operator==(const array<T, N>&, const array<T, N>&);
template<typename T, std::size_t N>
constexpr bool operator!=(const array<T, N>&, const array<T, N>&);
//类模板定义部分
template<typename T, std::size_t N>
class array {
    T _elem[N]; //既然是定长数组，那就不必再用动态内存分配了
public:
    array(std::initializer_list<T>); //构造函数
    array(const array&); //拷贝构造函数，这里的array也是array<T,N>
    array& operator=(const array&); //赋值运算符
    constexpr T& at(std::size_t); //尽可能设置成constexpr吧
    constexpr const T& at(std::size_t)const;
    //注意返回类型也要保证常量性
    constexpr T& operator[](std::size_t);
    constexpr const T& operator[](std::size_t)const; //同上
    constexpr T& front() { return _elem[0]; }
    constexpr const T& front()const { return _elem[0]; }
    constexpr T& back() { return _elem[N - 1]; }
    constexpr const T& back()const { return _elem[N - 1]; }
    constexpr bool empty()const { return !N; }
    constexpr std::size_t size()const { return N; }
    void fill(const T&);
    template<std::size_t I, typename U, std::size_t M>
    friend U& get(array<U, M>&);
    //声明模板友元，所有的get<U,M>函数实例都是类实例array<T,N>的友元
    template<std::size_t I, typename U, std::size_t M>
    friend const U& get(const array<U, M>&);
    //同上
    template<typename U, std::size_t N1, std::size_t N2>
    friend void swap(array<U, N1>&, array<U, N2>&);
    //声明友元（非成员函数），任何两个array<T,N>和array<T,M>可用swap函数交换
    template<typename, std::size_t>
    friend class array;
    //声明友元类模板，任意一个array实例都是array<T,N>的友元
    template<std::size_t M>
    void swap(array<T, M>&);
    //作为array<T,N>的成员函数，它可与array<T,M>对象交换
    template<typename U, std::size_t M>
    friend constexpr bool operator<(const array<U,M>&, const array<U,M>&);
    //这里也用到了一些array的私有成员，所以它需要是友元
};
}; //end namespace user
#include "Specification.tpp" //包含Specification.tpp文件的代码
#include "Definition.tpp" //同上