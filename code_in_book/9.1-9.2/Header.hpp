#pragma once
#include <vector>
class stack : std::vector<int> {
public:
    explicit stack() {} //什么也不做
    explicit stack(const std::vector<int>&); //接收一个std::vector<int>对象
    stack(const stack&); //拷贝构造函数
    //用默认析构函数足矣，无需自行定义
    stack& operator=(const stack&); //赋值运算符
    int& top() { return back(); } //调用std::vector<int>的back函数
    const int& top()const { return back(); } //常成员函数版本
    bool empty()const { return !size(); } //调用stack::size()
    std::size_t size()const { return std::vector<int>::size(); }
    //调用std::vector<int>的size()函数
    void push(const int&); //堆入数据
    void pop(); //移出数据
    void swap(stack&); //交换内容
    bool operator<(const stack&)const;
    bool operator>(const stack&)const;
    bool operator<=(const stack&)const;
    bool operator>=(const stack&)const;
    bool operator==(const stack&)const;
    bool operator!=(const stack&)const; //六个比较运算符
};