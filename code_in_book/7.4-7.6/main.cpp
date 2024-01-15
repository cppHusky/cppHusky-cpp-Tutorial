//主函数定义在本文件中
#include <iostream>
#include "Header.h"
using namespace std;
int main() { //仅作为示例
    Data head {0,nullptr}, *tail {&head};
    while (cin) {
        int n;
        cin >> n; //输入n的值，直到出现异常输入（如q）
        insert_after(tail, n);
        tail = tail->next; //更新tail的指向
    }
    clear_list(&head);
    return 0;
}