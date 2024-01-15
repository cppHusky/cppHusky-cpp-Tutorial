#pragma once
#include <initializer_list>
#include <iostream>
class valarri; //valarri类声明
void input_clear(std::istream& = {std::cin}); //input_clear函数声明
class valarri { //valarri类定义
private: //私有成员部分，注意成员变量定义的顺序
    static std::size_t _object_number; //已有valarri对象的数量
    static const std::size_t MAX_SIZE {100000}; //可以允许的最大容量
    std::size_t _cap {0}; //当前动态分配的容量，默认初值为0
    std::size_t _size {0}; //当前实际存储的数据量，默认初值为0
    class Arr{ //内嵌的Arr类
    private:
        int *_p; //私有指针成员_p，用来指向申请的动态内存空间
    public:
        Arr(int *ptr) : _p{ptr} {} //构造函数，接收一个指针初始化
        int*& p() { return _p; } //返回类型是“对指针的引用”，其值为_p
        const int* p()const { return _p; } //返回类型是“指向常量的指针”，其值为_p
    }_arr {new int[_cap]}; //作为一个中介对象存在，是访问_p成员的窗口
public: //公有成员部分
    valarri() { _object_number++; } //默认构造函数，只进行计数器自增
    valarri(const std::initializer_list<int>&); //接收一个初始化表作为参数
    valarri(int, std::size_t); //将<参数1>重复<参数2>次
    valarri(const valarri&); //拷贝构造函数
    ~valarri(); //析构函数
    valarri& operator=(const valarri&); //直接赋值运算符
    valarri operator+(const valarri&)const; //可以与数组相加
    valarri operator+(int)const; //可以与数相加
    friend valarri operator+(int, const valarri&); //可以以数加之，友元
    valarri& operator+=(const valarri&); //可以加之以数组
    valarri& operator+=(int); //可以加之以数
    friend std::istream& operator>>(std::istream&, valarri&); //需iostream库
    int& operator[](int i) { return _arr.p()[i]; } //下标，非常成员函数
    int operator[](int i)const { return _arr.p()[i]; } //下标，常成员函数
    void swap(valarri&); //完全交换两个valarri对象的成员数据
    void resize(std::size_t, int = {0}); //改变数据容量，如果扩大，将补<参数2>
    std::size_t size()const { return _size; } //返回当前的存储量大小，常成员函数
    static std::size_t object_number() { return _object_number; }
    //静态成员函数不能是常成员函数
    int max()const; //最大值
    int min()const; //最小值
    int sum()const; //总和
};
inline std::size_t valarri::_object_number {0};
//静态非常成员变量要在外部定义；如果定义在头文件中，需要有inline