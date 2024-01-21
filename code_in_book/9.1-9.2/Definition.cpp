#include "Header.h"
stack::stack(const std::vector<int> &v) : std::vector<int>{v} {}
//构造函数
stack::stack(const stack &s) : std::vector<int>{s} {}
//拷贝构造函数
stack& stack::operator=(const stack &s) {
    if (this == &s) //防止自我赋值
        return *this;
    std::vector<int>::operator=(s);
    //调用std::vector<int>的赋值运算符，并借助隐式类型转换参数传递
    return *this;
}
void stack::push(const int &val) {
    push_back(val); //将调用std::vector<int>::push_back
}
void stack::pop() {
    pop_back(); //将调用std::vector<int>::pop_back
}
void stack::swap(stack &s) {
    std::vector<int>::swap(s);
}
bool stack::operator<(const stack &s)const {
    return *this < static_cast<std::vector<int>>(s);
}
bool stack::operator>(const stack &s)const {
    return s < *this;
}
bool stack::operator<=(const stack &s)const {
    return !(s < *this);
}
bool stack::operator>=(const stack& s)const {
    return !(*this < s);
}
bool stack::operator==(const stack &s)const {
    return !operator!=(s); //利用已经声明的stack::operator!=
}
bool stack::operator!=(const stack &s)const {
    return *this < s || s < *this; //比较运算符的优先级高于逻辑或运算符
}