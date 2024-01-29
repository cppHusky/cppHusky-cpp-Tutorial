#pragma once
#include <algorithm>
//非成员函数定义部分
template<typename T>
void user::swap(unique_ptr<T> &lhs, unique_ptr<T> &rhs) {
    std::swap(lhs._ptr, rhs._ptr); //只要交换它们底层的指针就行了
}
template<typename T>
std::ostream& user::operator<<(
    std::ostream &out,
    const user::unique_ptr<T> &ptr
) {
    return out << ptr._ptr; //其实就是直接输出ptr内部的指针值，这也正是我们想要的
}
//主模板成员函数定义部分
template<typename T>
user::unique_ptr<T>::unique_ptr(pointer ptr) {
    if (record.find(ptr) == record.end()) { //先在记录当中寻找是否有ptr
        _ptr = ptr;
        record.insert(ptr); //如果没找到，_ptr可以安全赋值，并记录这个值
    } //否则什么也不做
}
template<typename T>
user::unique_ptr<T>::~unique_ptr() {
    if (record.find(_ptr) != record.end()) { //如果在记录中找到了_ptr
        delete _ptr; //回收动态内存
        record.erase(_ptr); //清除记录
    }
}
template<typename T>
auto user::unique_ptr<T>::release() -> pointer { //用auto来方便我们写返回类型
    pointer tmp {_ptr}; //临时变量存值，以便返回
    _ptr = nullptr; //_ptr指向空
    return tmp;
}
template<typename T>
auto user::unique_ptr<T>::get()const -> pointer {
    return _ptr;
}
template<typename T>
void user::unique_ptr<T>::reset(pointer ptr) {
    if (record.find(_ptr) != record.end()) { //先清理旧的指针
        delete _ptr;
        record.erase(_ptr);
        _ptr = nullptr; //注意把_ptr置空，否则可能会出现野指针
    }
    if (record.find(ptr) == record.end()) { //如果新的地址值不在记录当中
        _ptr = ptr;
        record.erase(_ptr);
    } //否则什么也不做
}
template<typename T>
void user::unique_ptr<T>::swap(unique_ptr &ptr) {
    std::swap(_ptr, ptr._ptr);
}
//模板特化定义部分
template<typename T>
user::unique_ptr<T[]>::unique_ptr(pointer ptr) {
    if (record.find(ptr) == record.end()) { //同上，没什么特别的
        _ptr = ptr;
        record.insert(ptr);
    }
}
template<typename T>
user::unique_ptr<T[]>::~unique_ptr() {
    if (record.find(_ptr) != record.end()) {
        delete[] _ptr; //一定不要搞错了！
        record.erase(_ptr);
    }
}
template<typename T>
auto user::unique_ptr<T[]>::release() -> pointer {
    pointer tmp {_ptr};
    _ptr = nullptr;
    return tmp;
}
template<typename T>
auto user::unique_ptr<T[]>::get()const -> pointer {
    return _ptr;
}
template<typename T>
void user::unique_ptr<T[]>::reset(pointer ptr) {
    if (record.find(_ptr) != record.end()) {
        delete[] _ptr; //一定不要搞错了！
        record.erase(_ptr);
        _ptr = nullptr;
    }
    if (record.find(ptr) == record.end()) {
        _ptr = ptr;
        record.erase(_ptr);
    }
}
template<typename T>
void user::unique_ptr<T[]>::swap(unique_ptr& ptr) {
    std::swap(_ptr, ptr._ptr);
}