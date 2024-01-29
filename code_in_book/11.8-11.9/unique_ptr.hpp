#pragma once
#include <iostream>
#include <unordered_set>
namespace user {
//类模板与函数模板声明部分
template<typename T>
class unique_ptr; //定义类模板unique_ptr
template<typename T>
class unique_ptr<T[]>; //定义特化unique_ptr<T[]>
template<typename T>
void swap(unique_ptr<T>&, unique_ptr<T>&);
template<typename T>
std::ostream& operator<<(std::ostream&, const unique_ptr<T>&);
//主模板定义部分
template<typename T>
class unique_ptr { //分配动态单对象，使用unique_ptr<T>语法
public:
    using pointer = T*; //通过using定义成员类型pointer，公有
    using element_type = T; //定义成员类型element_type
private:
    pointer _ptr {nullptr}; //pointer类型的私有成员，成员类型pointer必须定义在前面
    static std::unordered_set<pointer> record;
public:
    explicit unique_ptr(pointer = {nullptr}); //接收pointer类参数，或nullptr
    unique_ptr(const unique_ptr&) = delete; //删除拷贝构造函数
    ~unique_ptr(); //析构函数
    unique_ptr& operator=(const unique_ptr&) = delete; //删除拷贝赋值函数
    pointer release(); //release函数会把指向改为nullptr
    pointer get()const; //get函数不会改变成员；至于透过get()改变内容，那是允许的
    void reset(pointer = {nullptr}); //重置指向
    operator bool()const { return _ptr != nullptr; } //表明指向是否非空
    void swap(unique_ptr&);
    element_type& operator*()const { return *get(); } //注意返回值得是引用
    pointer operator->()const { return get(); } //注意返回类型得是裸指针或对象
    template<typename U>
    friend void swap(unique_ptr<U>&, unique_ptr<U>&);
    template<typename U>
    friend std::ostream& operator<<(std::ostream&, const unique_ptr<U>&);
};
//模板特化定义部分
template<typename T>
class unique_ptr<T[]> { //特化，分配动态数组，使用unique_ptr<T[]>语法
public:
    using pointer = T*; //对于T[]来说，它只是意味着分配动态数组，其指针类型还是T*
    using element_type = T; //同理，元素类型还是T
private:
    pointer _ptr {nullptr};
    static std::unordered_set<pointer> record;
public:
    explicit unique_ptr(pointer = {nullptr});
    unique_ptr(const unique_ptr&) = delete; //删除拷贝构造函数
    ~unique_ptr();
    unique_ptr& operator=(const unique_ptr&) = delete; //删除拷贝赋值函数
    pointer release(); //同上
    pointer get()const;
    void reset(pointer = {nullptr}); //简化版，对继承关系的支持较差
    operator bool()const { return _ptr != nullptr; }
    void swap(unique_ptr&);
    element_type& operator[](std::size_t i)const { return _ptr[i]; }
    //下标运算符，访问第i个元素
    template<typename U>
    friend void swap(unique_ptr<U>&, unique_ptr<U>&);
    template<typename U>
    friend std::ostream& operator<<(std::ostream&, const unique_ptr<U>&);
};
};
//静态成员变量定义部分
template<typename T>
inline std::unordered_set<
    typename user::unique_ptr<T>::pointer //typename关键字说明它是一个类型
> user::unique_ptr<T>::record;
template<typename T>
inline std::unordered_set<
    typename user::unique_ptr<T[]>::pointer
> user::unique_ptr<T[]>::record;
#include "Definition.tpp"