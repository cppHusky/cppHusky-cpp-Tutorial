#include "Header.hpp"
int main() {
    int n {1};
    while (n != 0) {
        cin >> n;
        if(!cin) //检测cin的状态
            input_clear(); //清理输入
        //...
    }
    return 0;
}