//本文件用于存放Header.h中各函数的定义
#include "Header.h"
#include <utility> //transfer函数用到了utility库中的swap函数
void clear_list(Data *head) { //递归回收*head之后的所有动态内存
    if (head->next == nullptr)
        return;
    clear_list(head->next);
    delete head->next;
    head->next = nullptr;
}
void insert_after(Data *head, int n) { //在*head下一位置插入n
    head->next = new Data{ n,head->next }; //三步并作一步
}
bool delete_after(Data *head) {
//删除*head下一位置的数据，并返回true；若*head是末尾元素，删除失败，返回false
    if (head->next == nullptr)
        return false;
    Data *p = head->next;
    head->next = p->next;
    delete p;
}
bool delete_after(Data *head, Data* tail) {
//删除*head之后（不包含）直到*tail为止（包含）的单元。若删除失败，返回false
    if (head == tail)
        return false;
    if (tail == nullptr) {
        clear_list(head);
        return true;
    }
    Data tmp_head {*head};
    head->next = tail->next;
    tail->next = nullptr;
    clear_list(&tmp_head);
    return true;
}
void transfer(Data *head, Data *tail, Data *dest) {
//片段转移，把*head之后（不包含）直到*tail为止（包含）的单元移到*dest之后
    if (head == tail || dest == nullptr)
        return;
    if (tail == nullptr) {
        for (tail = head; tail->next != nullptr; tail = tail->next) {
            ;
        }
        if (head == tail)
            return;
    }
    std::swap(tail->next, dest->next); //注意要用std::swap
    std::swap(head->next, dest->next); //除非using namespace std
}