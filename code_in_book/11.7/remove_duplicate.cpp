#include <iostream>
#include <list>
#include <set>
int main() {
    std::list<char> chs {'c', 'a', 'a', 'b', 'd', 'b', 'a', 'e'};
    std::set<char> s; //一个集合，用来表示chs中存在哪些数据
    auto it = chs.begin(); //它是一个迭代器类型，我们把它当作指针看待就好
    while (it != chs.end()) {
        if (s.find(*it) == s.end()) { //*it表示it当前指向的chs元素
            s.insert(*it); //s中没有记录*it这个数据，那就把它存进s
            ++it; //it指向下一个元素
        }
        else //否则，就说明此前已经有*it这个数据了，当前的元素与前面重复
            it = chs.erase(it); //删除it指向的元素，并让it指向下一个元素
    }
    for (auto ch : chs)
        std::cout << ch << ' ';
    return 0;
}