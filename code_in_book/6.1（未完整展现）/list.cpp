#include <iostream>
using namespace std;
struct Data {
    int num;
    Data *next;
};
void clear_list(Data *head) { //递归回收*head之后的所有动态内存
    if (head->next == nullptr) //如果*head之后没有动态内存
        return; //那就不需要回收什么了，直接return;结束本次调用
    clear_list(head->next); //先清理head->next之后的部分
    delete head->next; //再回收head.next
    head->next = nullptr;
    //现在head之后没有动态内存了，我们可以放心地把head->next置为nullptr
}
void insert_after(Data *head, int n) { //在*head下一位置插入n
    Data* p = { new Data{n,nullptr} }; // 分配动态内存，并初始化其num成员
    p->next = head->next; //插入数据的下一位指向当前的*head->next
    head->next = p; //head->next指向*p，注意顺序不要颠倒！
}
bool delete_after(Data *head) {
//删除*head下一位置的数据，并返回true；若*head是末尾元素，删除失败，返回false
    if (head->next == nullptr) //说明*head就是末尾元素
        return false;  //*head是末尾元素，无法再删除后面内容
    //这里应当用else块，不过也可以省掉
    //因为if块内会直接return，所以后面的代码肯定是在条件为false情况下运行的
    Data *p = head->next; //临时指针p指向*head->next
    head->next = p->next; //head->next指向更后一个元素
    delete p; //回收p指向的内存
    return true;
}
bool delete_after(Data *head, Data* tail) {
//删除*head之后（不包含）直到*tail为止（包含）的单元。若删除失败，返回false
    if (head == tail) //说明没有任何数据需要清理
        return false; //删除失败
    if (tail == nullptr) { //说明我们需要删除*head之后的所有内容
        clear_list(head); //当然是用clear_list啦
        return true; //删除成功
    }
    Data tmp_head {*head}; //用*head来直接为tmp_head初始化
    head->next = tail->next; //绕过待删除段，直接指向*tail->next
    tail->next = nullptr; //tail指向nullptr，现在待删除片段就被剥离出来了
    clear_list(&tmp_head); //以tmp_head为头，清理这段链表
    return true; //删除成功
}
void transfer(Data *head, Data *tail, Data *dest) {
//片段转移，把*head之后（不包含）直到*tail为止（包含）的单元移到*dest之后
    if (head == tail || dest == nullptr) //这两种情况下转移没有意义
        return;
    if (tail == nullptr) { //这种情况不方便我们处理，我们把tail改成指向末尾单元
        for (tail = head; tail->next != nullptr; tail = tail->next) {
            ; //for循环的逻辑是，从head开始找，直到tail->next==nullptr为止
        }
        if (head == tail) //仍需当心head==tail的可能
            return;
    }
    swap(tail->next, dest->next); //swap函数需要utility或string_view库
    swap(head->next, dest->next); //是一种技巧，读者不必强求掌握
}
int main() {
    Data head; //链表头
    insert_after(&head, 10);
    insert_after(head.next, 20);
    delete_after(&head);
    std::cout << head.next->num; //将输出20
    clear_list(&head);
    return 0;
}