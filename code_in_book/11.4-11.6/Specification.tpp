#pragma once //千万不要遗漏
#include <bitset> //user::array内部的数据需要利用std::bitset来管理
namespace user{
//array类模板特化部分
template<std::size_t N>
class array<bool, N>; //特化的声明
template<std::size_t I, std::size_t N> //模板参数与另一个不同，所以它是一个重载
typename std::bitset<N>::reference get(array<bool, N>&);
template<std::size_t I, std::size_t N>
const bool get(const array<bool, N>&);
template<std::size_t N, std::size_t M> //它也是函数模板重载
void swap(array<bool, N>&, array<bool, M>&);
template<std::size_t N>
constexpr bool operator<(
    const array<bool, N>&, const array<bool, N>&
); //这个是专门为bool数组比较而设计的，因为std::bitset没有迭代器这个概念
//模板定义部分
template<std::size_t N>
class array<bool, N> { //定义array<bool,N>部分特化
    std::bitset<N> _elem; //std::bitset可以更方便地解决我们的问题
public:
    using reference = typename std::bitset<N>::reference;
    //类型别名，方便我们使用reference
    array(std::initializer_list<bool>); //构造函数
    array(const array&); //拷贝构造函数，这里的array是array<bool,N>
    array& operator=(const array&); //赋值运算符
    constexpr reference at(std::size_t);
    constexpr bool at(std::size_t)const;
    constexpr reference operator[](std::size_t);
    constexpr bool operator[](std::size_t)const;
    constexpr reference front() { return _elem[0]; } //std::bitset支持下标
    constexpr bool front()const { return _elem[0]; }
    constexpr reference back() { return _elem[N - 1]; }
    constexpr bool back()const { return _elem[N - 1]; }
    constexpr bool empty()const { return !N; }
    constexpr std::size_t size()const { return N; }
    void fill(bool); //对于bool类型来说，传值比传常量引用更省内存空间
    template<std::size_t I, std::size_t M>
    friend typename std::bitset<M>::reference get(array<bool, M>&);
    //声明模板友元，所有的get<I,M>函数实例都是类实例array<bool,N>的友元
    template<std::size_t I, std::size_t M>
    friend const bool get(const array<bool, M>&);
    //同上
    template<std::size_t N1, std::size_t N2>
    friend void swap(array<bool, N1>&, array<bool, N2>&);
    template<typename, std::size_t>
    friend class array;
    //声明友元类模板，任何一个array实例都是array<bool,N>的友元
    template<std::size_t M>
    void swap(array<bool, M>&);
    template<std::size_t M>
    friend constexpr bool operator<(
        const array<bool, M>&, const array<bool, M>&
    );
};
}; //end namespace user