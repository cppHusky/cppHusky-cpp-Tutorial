#include "Header.h"
#include <algorithm>
string::string(std::size_t count, char ch)
    : _cap {count} //_arr就用默认初值new char[_cap]来初始化足矣
{
    for (; _size < count; _size++) //_size已经通过默认初值定为0，无需再赋值
        at(_size) = ch; //这里用到了at成员函数，稍后我们会看到其定义
}
string::string(const string &other, std::size_t pos, std::size_t count)
    : _cap {other._cap} //当pos和count都取默认值时它充当拷贝构造函数，故_cap要一致
{
    if (pos >= other._size) //为了防范pos越界的情况
        at(0) = '\0'; //直接把第一个字符变成空字符，什么也不做
    else {
        if (count == npos //npos的意思是直接截到字符串末尾
            || pos + count > other._size
        ) //对于pos+count越界或者count==npos的情况
            count = other._size - pos; //接下来count的值就合适了
        for (; _size < count; _size++)
            at(_size) = other.at(_size);
    }
}
string::string(const char *s) : _cap {std::strlen(s)} {
    for (; _size < _cap; _size++)
        at(_size) = s[_size];
}
string::string(const char* s, std::size_t count)
    : _cap {std::min(std::strlen(s),count)} //防止count大于strlen(s)
{
    for (; _size < _cap; _size++)
        at(_size) = s[_size];
}
string::string(std::initializer_list<char> ilist)
    : _cap {ilist.size()}
{
    for (char ch : ilist) //范围for循环
        at(_size++) = ch; //注意自增符号要用后缀
}
string::~string() {
    delete[] _arr.p(); //别忘了用delete[]而不是delete
}
char& string::at(std::size_t pos) {
    if (pos >= _size)
        pos = _size - 1;
    return _arr.p()[_size];
}
const char& string::at(std::size_t pos)const {
    if (pos >= _size)
        pos = _size - 1;
    return _arr.p()[_size];
}
string& string::assign(std::size_t count, char ch) {
    if (count > _cap) //说明动态内存空间不足
        realloc(count, false); //重新分配，这时不需要进行内容复制，故传入false
    for (_size = 0; _size < count; _size++)
        at(_size) = ch;
    return *this;
}
string& string::assign(
    const string &str,
    std::size_t pos,
    std::size_t count
){ //这是一种效率比较低的做法，但是操作非常简单
    string tmp {str, pos, count}; //用一个tmp暂存需要的内容
    swap(tmp); //将此对象与tmp交换
    return *this;
}
string& string::assign(const char *s, std::size_t count) {
    std::size_t len {std::strlen(s)}; //防止多次调用std::strlen
    if (count > len) //如果count大于len，那就越界了
        count = len; //修正count的值
    if (count > _cap) //说明动态内存空间不足
        realloc(count, false); //这里也不需要保留原内容
    for (_size = 0; _size < count; _size++)
        at(_size) = s[_size];
    return *this;
}
string& string::assign(std::initializer_list<char> ilist) {
    string tmp{ilist};
    swap(tmp); //故技重施
    return *this;
}
void string::reserve(std::size_t new_cap) {
    if (new_cap < _size) //防止损失有效内容
        new_cap = _size;
    realloc(new_cap); //直接使用已有的realloc函数来实现
}
void string::resize(std::size_t count, char ch) {
    if (_cap < count) //先保证动态内存空间充足
        realloc(count); //这里传入第二个默认参数true，说明原内容需要保留
    if (count > _size)
        for (; _size < count; _size++)
            at(_size) = ch; //从_size位置到count-1全部需要变成ch，注意范围
    else
        _size = count; //直接截尾即可，所以把_size变成count
}
string& string::append(std::size_t count, char ch) {
    if (_size + count > _cap)
        realloc(_size+count);
    for (; _size < count; _size++)
        at(_size) = ch;
    return *this;
}
string& string::append(
    const string &str,
    std::size_t pos,
    std::size_t count
) {
    if (pos >= str._size) //如果起点都没有意义，那就不用拼接了
        return *this; //直接返回
    if (pos + count > str._size || count == npos)
        count = str._size - pos;
    if (_size + count > _cap) //如果内存不够
        realloc(_size+count); //那就重新分配内存，保留内容
    for(std::size_t i = 0; i < count; i++)
        at(_size+i) = str.at(pos+i);
    return *this;
}
string& string::append(const char *s, std::size_t count) {
    return append(s, 0, count);
    //先用构造函数把s转换成string对象，然后调用另一个append重载
}
string& string::append(std::initializer_list<char> ilist) {
    return append(string{ilist});
    //先用构造函数把s转换成string对象，然后调用另一个append重载，默认参数0, npos
}
string& string::insert(std::size_t pos, std::size_t count, char ch) {
    if (_size + count > _cap) //如果容量不够
        realloc(_size+count); //扩容
    for (std::size_t i = _size - 1; i >= pos; i--)
        at(i+count) = at(i); //从后向前，依次把字符后移count位，以留出空间
    for (std::size_t i = pos; i < pos+count; i++)
        at(i) = ch; //把pos起的count个字符变为ch
    _size += count; //最后别忘了更新_size的值！
    return *this;
}
string& string::insert(
    std::size_t pos,
    const string &str,
    std::size_t s_pos,
    std::size_t count
) {
    if (s_pos >= str._size) //如果起始点已经越界
        return *this; //那就直接返回
    if (s_pos + count > str._size || count == npos)
        count = str._size - s_pos; //调整count的值
    if (_size + count > _cap)
        realloc(_size+count); //必要的扩容
    for (std::size_t i = _size - 1; i >= pos; i--)
        at(i+count) = at(i); //数据后移
    for (std::size_t i = 0; i < count; i++)
        at(pos+i) = str.at(s_pos+i);
    //从本对象的pos位置起，把str对象的s_pos位置起count个数据依次复制到此处
    _size += count; //别忘了更新_size的值
    return *this;
}
string& string::insert(std::size_t pos, const char *s, std::size_t count) {
    return insert(pos, s, 0, count);
}
string& string::insert(std::size_t pos, std::initializer_list<char> ilist) {
    return insert(pos, ilist, 0, ilist.size());
}
string& string::erase(std::size_t pos, std::size_t count) {
    if (pos >= _size)
        return *this;
    if (pos + count > _size || count == npos)
        count = _size - pos;
    for (std::size_t i = pos; i + count < _size; i++) //注意范围
        at(i) = at(i+count);
    _size -= count; //记得更新_size
    return *this;
}
std::size_t string::copy(
    char *dest,
    std::size_t count,
    std::size_t pos
)const {
    if (pos >= _size)
        return 0;
    if (pos + count > _size || count == npos)
        count = _size - pos;
    for (std::size_t i = 0; i < count; i++) //把pos起的count个数据复制到字符串中
        dest[i] = at(pos+i);
    return count;
}
void string::swap(string &str) {
    std::swap(_cap, str._cap);
    std::swap(_size, str._size);
    std::swap(_arr.p(), str._arr.p());
}
std::size_t string::find(char ch, std::size_t pos)const {
    for (std::size_t i = pos; i < _size; i++) //从pos位置起开始寻找
        if (at(i) == ch) //找到了
            return i; //把i作为返回值
    //一直到_size处都没找到
    return npos; //npos可以表示没找到
}
std::size_t string::find(const string &str, std::size_t pos)const {
    for (std::size_t i = pos; i + str._size < _size; i++){
        bool equal {true}; //先假设片段[i,i+str._size)与片段str相等
        for (std::size_t j = 0; j < _size; j++)
            if (at(i+j) != str.at(j)) { //一旦发现一个不相等的字符
                equal = false; //标记为不相等
                break; //退出循环
            } //可以想见，如果这个循环下来没有任何字符不相等，那么它就是我们要找的
        if(equal) //euqal为真
            return i;
    }
    //一直到找了一大圈都无果而终
    return npos; //没找到
}
std::size_t string::find(
    const char *s,
    std::size_t pos,
    std::size_t count
)const {
    return find(string(s, count), pos);
    //这里要调用的是string(const char*,std::size_t)，不是string(const char*)
}
bool string::operator<(const string &str)const {
    return std::lexicographical_compare(
        &at(0), &at(_size), &str.at(0), &str.at(str._size)
    ); //利用std::lexicographical_compare算法，具体的细节就不讲了
}
bool string::operator>(const string &str)const {
    return str < *this; //利用已经重载好的小于号
}
bool string::operator<=(const string &str)const {
    return !(str < *this); //注意运算符的优先级
}
bool string::operator>=(const string &str)const {
    return !(*this < str);
}
bool string::operator!=(const string &str)const {
    return (*this < str) || (str < *this);
}
bool string::operator==(const string &str)const {
    return !operator!=(str); //进一步利用已经重载好的operator!=
}
int string::compare(const string &str)const {
    return -int(*this<str) + int(*this>str); //bool到int类型转换后再计算
}
std::ostream& operator<<(std::ostream &out, const string &str) { //string的友元
    for (std::size_t i = 0; i < str._size; i++)
        out << str.at(i);
    return out; //返回out以便连续输出
}
std::istream& operator>>(std::istream &in, string &str) { //string的友元
    char ch;
    str.clear(); //先清理str中的已有内容
    while (in.get(ch) && std::isspace(ch)) {
        //空，什么也不做
    } //这个循环的目的在于清理空白字符
    if (in)
        do { //注意，do-while结构会至少执行一次
            str.append(1, ch); //把输入的单个字符加到str的末尾
        } while (in.get(ch) && !std::isspace(ch));
        //在while中读取下一个字符，并判断它是不是空白字符
    if (in && !std::isspace(ch)) //如果这个字符不是空白字符，且属于下一个输入
        in.unget(); //把这个字符还回去
    return in; //返回in以便连续输入
}