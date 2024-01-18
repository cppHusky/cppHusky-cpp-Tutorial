#pragma once
#include <iostream>
#include <initializer_list>
#include <cstring>
class string { //class的默认成员访问权限是private，所以private可省略
    static constexpr std::size_t npos = -1; //串尾指示器
    std::size_t _cap {0}; //容量，默认初值为0
    std::size_t _size {0}; //长度，默认初值为0
    class Arr {
        char *_p;
    public:
        Arr(char* ptr = {nullptr}) : _p {ptr} {} //Arr的构造函数
        char*& p() { return _p; } //当arr不是常量时调用
        const char* p()const { return _p; } //当arr是常量时调用
    } _arr {new char[_cap]}; //象征指针的成员，默认用new char[_cap]初始化
    void realloc(std::size_t cap, bool copy = true) { //重分配内存函数
        char *tmp =_arr.p(); //临时指针，用以暂存当前内存地址
        _arr.p() = new char[cap]; //分配新的内存地址
        if (copy) //说明这个函数需要进行内容复制
            for (std::size_t i = 0; i < std::min(cap, _size); i++)
                _arr.p()[i] = tmp[i]; //转移内容
        delete[] tmp; //回收原来的内存地址
        _cap = cap; //更新_cap的值
        if (_size > _cap)
            _size = _cap; //保证_size不能大于_cap
    }
public:
    explicit string() {} //默认构造函数，定义成explicit防止被误用
    string(std::size_t count, char ch); //重复count个ch
    string(const string &other, std::size_t pos = {0},
           std::size_t count = {npos}); //在other的pos位置起接收count个字符
    string(const char *s); //用s字符串初始化
    string(const char *s, std::size_t count); //用s字符串的前count个字符初始化
    string(std::initializer_list<char>); //需要头文件initializer_list
    ~string(); //析构函数
    char& at(std::size_t pos); //返回pos位置的字符
    const char& at(std::size_t pos)const; //常成员函数版本
    char& operator[](std::size_t pos) { return _arr.p()[pos]; } //下标运算符
    const char& operator[](std::size_t pos)const { return _arr.p()[pos]; }
    string& assign(std::size_t count, char ch); //赋值重复count个ch
    string& assign(const string &str, std::size_t pos = {0},
        std::size_t count = {npos}); //在str的pos位置起接收count个字符
    string& assign(const char *s, std::size_t count); //接收s的前count个字符
    string& assign(std::initializer_list<char>); //用列表赋值
    string& operator=(const string &str) { return assign(str); }
    string& operator=(const char *s) { return assign(s, std::strlen(s)); }
    //其中std::strlen需要头文件cstring
    string& operator=(char ch) { return assign(1, ch); }
    string& operator=(std::initializer_list<char> ilist)
        { return assign(ilist); }
    bool empty()const { return _size; } //用到了隐式类型转换
    std::size_t size()const { return _size; } 
    std::size_t length()const { return _size; }
    std::size_t capacity()const { return _cap; }
    void reserve(std::size_t new_cap); //改变容量到new_cap，除非影响内容
    void resize(std::size_t count, char ch = {'\0'}); //改变内容长度
    string& append(std::size_t count, char ch);
    string& append(const string &str, std::size_t pos = {0},
        std::size_t count = {npos});
    string& append(const char *s, std::size_t count);
    string& append(std::initializer_list<char>);
    string& operator+=(char ch) { return append(1, ch); }
    string& operator+=(const string &str) { return append(str); }
    string& operator+=(const char *s) { return append(s,std::strlen(s)); }
    string& operator+=(std::initializer_list<char> ilist)
        { return append(ilist); }
    string& insert(std::size_t pos, std::size_t count, char ch);
    string& insert(std::size_t pos, const string &str,
        std::size_t s_pos = {0}, std::size_t count = {npos});
    //在pos位置起，从str的s_pos位置起选取count个字符插入本字符串中
    string& insert(std::size_t pos, const char *s, std::size_t count);
    string& insert(std::size_t, std::initializer_list<char>);
    string& erase(std::size_t pos = {0}, std::size_t count = {npos});
    void clear() { erase(); } //传入erase函数的默认值，然后自然能起到clear作用
    std::size_t copy(char *dest, std::size_t count,
        std::size_t pos = {0})const; //把pos起的count个字符移入dest，返回长度
    void swap(string&); //交换此对象与彼对象
    std::size_t find(char ch, std::size_t pos = {0})const;
    std::size_t find(const string &str, std::size_t pos = {0})const;
    //从pos位置起找str
    std::size_t find(const char *s, std::size_t pos,
        std::size_t count )const; //以s的前count个字符为索引，从pos位置起找
    //这三个都是常成员函数，因为不需要改变对象的内容
    int compare(const string&)const;
    bool operator<(const string&)const;
    bool operator>(const string&)const;
    bool operator<=(const string&)const;
    bool operator>=(const string&)const;
    bool operator==(const string&)const;
    bool operator!=(const string&)const;
    friend std::ostream& operator<<(std::ostream&, const string&); //输出
    friend std::istream& operator>>(std::istream&, string&); //输入
};