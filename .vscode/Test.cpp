#include <iostream>
using namespace std;
int main() {
    unsigned a = 10;
    cout << (a << 1) << endl; //20
    cout << (a << 2) << endl; //40
    cout << (a << 3) << endl; //80
    cout << (a << 4) << endl; //160
    cout << (a << 5) << endl; //320
    return 0;
}