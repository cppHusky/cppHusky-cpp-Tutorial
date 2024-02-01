#pragma once
#include <stdexcept>
#include <valarray>
#include <initializer_list>
#include <string>
#include <utility>
namespace user {
//模板与函数声明部分
template<typename T>
class matrix; //类模板声明
template<typename T>
matrix<T> operator+(const matrix<T>&, const matrix<T>&); //非成员函数声明
template<typename T>
matrix<T> operator-(const matrix<T>&, const matrix<T>&);
template<typename T>
matrix<T> operator*(const matrix<T>&, const matrix<T>&);
template<typename T>
matrix<T> operator*(const T&, const matrix<T>&);
template<typename T>
bool operator<(const matrix<T>&, const matrix<T>&);
template<typename T>
bool operator>(const matrix<T>&, const matrix<T>&);
template<typename T>
bool operator<=(const matrix<T>&, const matrix<T>&);
template<typename T>
bool operator>=(const matrix<T>&, const matrix<T>&);
template<typename T>
bool operator==(const matrix<T>&, const matrix<T>&);
template<typename T>
bool operator!=(const matrix<T>&, const matrix<T>&);
//模板定义部分
template<typename T>
class matrix { //类模板定义
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
private:
    const size_type N;
    const size_type M;
    std::valarray<std::valarray<value_type>> _element;
    struct index_error : std::out_of_range { //有两种构造函数和默认拷贝构造函数
        index_error(const char *msg) : out_of_range {msg} {}
        index_error(const std::string &msg) : out_of_range {msg} {}
    };
    struct invalid_plus : std::logic_error {
        invalid_plus(const char *msg) : logic_error {msg} {}
        invalid_plus(const std::string &msg) : logic_error {msg} {}
    };
    struct invalid_multiplies : std::logic_error {
        invalid_multiplies(const char *msg) : logic_error {msg} {}
        invalid_multiplies(const std::string &msg) : logic_error {msg} {}
    };
    struct invalid_compare : std::logic_error {
        invalid_compare(const char *msg) : logic_error {msg} {}
        invalid_compare(const std::string &msg) : logic_error {msg} {}
    };
public:
    matrix(size_type, size_type); //接收两个矩阵大小参数，所有元素置为0
    matrix(std::initializer_list<std::initializer_list<value_type>>);
    //允许二维数组式的列表初始化
    reference operator()(size_type, size_type);
    const_reference operator()(size_type, size_type)const;
    template<typename U>
    friend matrix<U> operator+(const matrix<U>&, const matrix<U>&); //矩阵相加
    template<typename U>
    friend matrix<U> operator-(const matrix<U>&, const matrix<U>&); //矩阵相减
    template<typename U>
    friend matrix<U> operator*(const matrix<U>&, const matrix<U>&); //矩阵相乘
    template<typename U>
    friend matrix<U> operator*(const U&, const matrix<U>&); //数乘以矩阵
    matrix operator*(const T&); //矩阵乘以数
    template<typename U>
    friend bool operator<(const matrix<U>&, const matrix<U>&);
    template<typename U>
    friend bool operator>(const matrix<U>&, const matrix<U>&);
    template<typename U>
    friend bool operator<=(const matrix<U>&, const matrix<U>&);
    template<typename U>
    friend bool operator>=(const matrix<U>&, const matrix<U>&);
    template<typename U>
    friend bool operator==(const matrix<U>&, const matrix<U>&);
    template<typename U>
    friend bool operator!=(const matrix<U>&, const matrix<U>&);
    matrix transpose()const;
    std::pair<size_type, size_type> size()const noexcept;
};
//辅助函数声明
template<typename T>
std::size_t max_column(
    const std::initializer_list<std::initializer_list<T>>&
); //辅助函数，取二维列表各行的最大值
};
#include "Definition.tpp"