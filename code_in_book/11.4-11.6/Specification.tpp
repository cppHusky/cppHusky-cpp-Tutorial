#pragma once //千万不要遗漏
#include <bitset> //user::array内部的数据需要利用std::bitset来管理
namespace user{
//array类模板特化部分
template<std::size_t N>
class array<bool, N>; //特化的声明
template<std::size_t N, std::size_t M> //模板参数与另一个不同，所以它是一个重载
void swap(array<bool, N>&, array<bool, M>&);
template<std::size_t N>
class array<bool, N> { //定义array<bool,N>部分特化
    std::bitset<N> _elem; //std::bitset可以更方便地解决我们的问题
public:
    array(std::initializer_list<bool>); //构造函数
    array(const array&); //拷贝构造函数，这里的array是array<bool,N>
    array& operator=(const array&); //赋值运算符
    constexpr bool& at(std::size_t);
    constexpr const bool& at(std::size_t)const;
    constexpr bool& operator[](std::size_t);
    constexpr const bool& operator[](std::size_t)const;
    constexpr bool& front() { return _elem[0]; } //std::bitset支持下标运算符
    constexpr const bool& front()const { return _elem[0]; }
    constexpr bool& back() { return _elem[N - 1]; }
    constexpr const bool& back()const { return _elem[N - 1]; }
    constexpr bool empty()const { return !N; }
    constexpr std::size_t size()const { return N; }
    void fill(bool); //对于bool来说，传值比传常量引用更省内存空间
    template<std::size_t I, typename U, std::size_t M>
    friend U& get(array<U, M>&); //不建议把U改成bool，因为U不是T
    //声明模板友元，所有的get<U,M>函数实例都是类实例array<bool,N>的友元
    template<std::size_t I, typename U, std::size_t M>
    friend const U& get(const array<U, M>&);
    //同上
    template<std::size_t N1, std::size_t N2>
    friend void swap(array<bool, N1>&, array<bool, N2>&);
    template<typename, std::size_t>
    friend class array;
    //声明友元类模板，任何一个array实例都是array<bool,N>的友元
    template<std::size_t M>
    void swap(array<bool, M>&);
}; //其中有些友元不需要重新定义（因为特化也是原模板的一部分），但有些需要
}; //end namespace user