#include <iostream> 
#include <limits>
int main() {
    using namespace std;
    for (int i = 0; i < 5; i++) { //i++与++i在这里效果相同
        for (int j = 1; j <= 5; j++) {
            cout << i * 5 + j << ' '; //每输出一个数字，以空格隔开
        }
        cout << endl; //每输出五个数字，以换行隔开
    }
    return 0;
}