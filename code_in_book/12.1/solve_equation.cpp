#include <iostream>
#include <cmath>
using namespace std; //久违的using namespace std
int main() {
    try {
        double a, b, c;
        cin >> a >> b >> c; //输入三个系数
        if (!cin)
            throw 1; //抛出1号异常，表示输入信息有误，导致cin状态不正常
        if (a == 0)
            throw 2; //抛出2号异常，表示方程次数不正确
        double Delta {b * b - 4 * a * c};
        if (Delta < 0)
            throw 3; //抛出3号异常，表示方程无实根
        cout << (- b + sqrt(Delta)) / (2 * a) << ' '
             << (- b - sqrt(Delta)) / (2 * a) << '\n'; //输出结果
    } catch (int error) { //在这里用int型变量error来捕获异常信息
        switch (error) { //switch结构，对异常信息进行分情况处理
            case 1: //清除cin的错误状态（其实也可以不做）
                cout << "输入内容并非数字！" << endl; //显示错误信息
                cin.clear(); //如果你有现成的input_clear()函数，可以直接调用之
                while (cin.get() != '\n')
                    continue;
                break;
            case 2:
                cout << "二次项系数不能为0！" << endl; //显示错误信息
                break;
            case 3:
                cout << "方程无实根！" << endl; //显示错误信息
                break;
        }
    }
    return 0;
}