#include "Header.hpp"
#include <algorithm>
valarri::valarri(const std::initializer_list<int>& ilist)
    : _cap {std::min(MAX_SIZE, ilist.size())} //_cap的初值要取二者最小值
{
    std::size_t counter {0}; //长度计数器，用来防止超过MAX_SIZE
    for (int x : ilist) { //范围for循环，遍历ilist中的每个数
        operator[](_size++) = x; //注意自增是前缀还是后缀，请读者自行分析
        if (++counter >= MAX_SIZE) //说明达到MAX_SIZE了
            break; //直接退出for循环
    }
    _object_number++; //对象计数器自增
}
valarri::valarri(int n, std::size_t size)
    : _cap {std::min(MAX_SIZE, size)} //_cap的初值要取二者最小值
{
    for (; _size < _cap; _size++) //通过循环赋值，其中_size已经通过默认初始置0
        operator[](_size) = n;
    _object_number++; //计数器自增
}
valarri::valarri(const valarri &a) //拷贝构造函数应当进行深拷贝，切记！
    : _cap {a._cap},
    _size {a._size}
{ //这里不用防_cap超过MAX_SIZE，因为其它部分共同保证了a._cap不会超过MAX_SIZE
    for (std::size_t i = 0; i < _size; i++)
        operator[](i) = a[i]; //拷贝每个值，而不是拷贝地址
    _object_number++; //计数器自增
}
valarri::~valarri() {
    _object_number--; //计数器自减
    delete[] _arr.p(); //回收_arr.p()指向的动态内存空间，注意必须要用delete[]搭配
}
valarri::valarri(const vecint &vec) //vecint到valarri的转换构造函数
    : _cap {vec.size()}, //valarri的成员对vec私有成员无访问权限，所以要用其公有成员
    _size {vec.size()}
{
    for (std::size_t i = 0; i < _size; i++)
        operator[](i) = vec[i]; //vecint也有重载下标运算符，并且有常成员函数的重载
    _object_number++; //计数器自增
}
valarri::operator vecint()const { //valarri到vecint的自定义转换函数
    vecint vec(_size); //调用了vecint的构造函数，直接指定vec的大小
    for (std::size_t i = 0; i < _size; i++)
        vec[i] = operator[](i); //逐个赋值，不要用push_back成员，反复重分配太浪费
    return vec;
}
valarri& valarri::operator=(const valarri &a) { //直接赋值运算符
    if (&a == this) //防范自我赋值
        return *this;
    if (_cap < a._size) { //如果现有容量装不下a中的所有数据，那就要扩容
        delete[] _arr.p(); //别忘了先回收现在指向的内存空间！！
        _cap = a._size; //_希望分配一个大小为a._size的内存空间
        _arr.p() = new int[_cap]; //分配动态内存空间
    } //这里也不用防范_cap超过MAX_SIZE，原因同上
    for (_size = 0; _size < a._size; _size++)
        operator[](_size) = a[_size];
    return *this; //返回*this
}
valarri valarri::operator+(const valarri &a)const {
    valarri v(0,std::min(_cap,a._cap)); //用构造函数为v初始化，代码重用
    for (std::size_t i=0; i < v._size; i++)
        v[i] = operator[](i) + a[i];
    return v;
}
valarri valarri::operator+(int n)const {
    valarri v {*this}; //用拷贝构造函数为v初始化，也是代码重用
    for (std::size_t i = 0; i < v._size; i++)
        v[i] = operator[](i) + n;
    return v;
}
valarri operator+(int n,const valarri &a) { //这是非成员函数，它是valarri的友元
    valarri v {a}; //同样是拷贝构造函数
    for (std::size_t i = 0; i < v._size; i++)
        v[i] = a[i] + n;
    return v;
}
valarri& valarri::operator+=(const valarri &a) { //加赋值运算符
    return *this = *this + a; //代码重用，加法与赋值连用
}
valarri& valarri::operator+=(int n) { //同上
    return *this = *this + n;
}
std::istream& operator>>(std::istream &in, valarri &a) {
    a._size = 0; //因为它是valarri的友元，所以可以访问valarri的私有成员
    while (in && a._size < a.MAX_SIZE) //要保证in正常且a._size没有达到最大容量
        in >> a[a._size++]; //注意++是后置的，不是前置
    if (!in) //检测一下in的状态，保证其状态正常
        input_clear(in); //这次就不是用默认参数，而是用in了
    return in; //返回in，以便连续输入
}
void valarri::swap(valarri &a) { //完全交换两个valarri对象的成员数据
    std::swap(_cap, a._cap); //交换_cap对象
    std::swap(_size, a._size); //交换_size对象
    std::swap(_arr.p(), a._arr.p()); //交换_arr._p对象，这是通过_arr.p()实现的
}
void valarri::resize(std::size_t size, int value) { //改变数据容量
    if (size > MAX_SIZE) //防止size超过MAX_SIZE
        size = MAX_SIZE;
    valarri v(value, size); //注意用圆括号
    for (std::size_t i = 0; i < std::min(_size, v._size); i++) //注意范围
        v[i] = operator[](i);
    swap(v); //将此对象与v交换，这样v会指向旧的内存空间并在析构时销毁
}
int valarri::max()const { //返回值是数组当前的最大值
    int maximum {operator[](0)};
    for (std::size_t i = 1; i < _size; i++) //注意循环的结束条件用_size，下同
        if (maximum < operator[](i))
            maximum = operator[](i);
    return maximum;
}
int valarri::min()const { //返回值是数组当前的最小值
    int minimum {operator[](0)};
    for (std::size_t i = 1; i < _size; i++)
        if (minimum > operator[](i))
            minimum = operator[](i);
    return minimum;
}
int valarri::sum()const { //返回值是当前数组中有效数据的总和
    int summation {0}; //先置为0
    for (std::size_t i = 0; i < _size; i++)
        summation += operator[](i); //然后把每个数都加到summation上
    return summation;
}
void input_clear(std::istream &in) { //input_clear函数定义
    in.clear();
    while (in.get() != '\n')
        continue;
}