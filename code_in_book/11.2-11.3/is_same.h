#pragma once
#include <type_traits> //std::is_same定义在type_traits库中
namespace user { //定义在user命名空间中
template<typename T1, typename T2>
constexpr bool is_same() { //比较两个类是否相同，最好加上constexpr
    return std::is_same<T1, T2>::value; //调用std::is_same，代码重用
}
template<typename T1, typename T2>
constexpr bool is_same(const T2 &obj) { //比较对象obj是不是T1类型
    return std::is_same<T1, T2>::value; //可以直接比较T1和T2
}
template<typename T1, typename T2>
constexpr bool is_same(const T1 &obj1, const T2 &obj2){ //比较两个对象是否同类
    return std::is_same<T1, T2>::value; //同上
}
};