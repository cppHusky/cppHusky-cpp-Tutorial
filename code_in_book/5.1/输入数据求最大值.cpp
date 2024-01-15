//这是一个输入若干数求最大值的程序，用户可以输入最多100000个数据，输入q结束输入
#include <iostream>
using namespace std;
//声明部分
void input_clear(istream& = {cin}); //在声明中就给出默认参数，注意类型是引用
template<typename T>
T maximum(T[], int); //T[]写成T*也没问题，不过习惯上还是写成数组形式
template<typename T> //注意：每次声明（定义）模版时必须写一个template
unsigned input_arr(T[], const unsigned);
//定义部分
int main() { //主函数
    const int Maxsize {100000}; //用constexpr也可
    int arr[Maxsize];
    cout << maximum(arr, input_arr(arr, Maxsize));
    return 0;
}
void input_clear(istream &in) {
    in.clear();
    while (in.get() != '\n')
        continue;
}
template<typename T>
T maximum(T arr[], int n) {
    T res {arr[0]}; //先假设最大值为arr[0]
    for (int i = 1; i < n; i++)
        if (arr[i] > res) //如果arr[i]>res，说明有更大的数
            res = arr[i]; //那么目前能找到的最大值就是arr[i]
    return res; //res就是返回值
}
template<typename T>
unsigned input_arr(T arr[], const unsigned max_size) {
    unsigned real_size {0}; //记录数组中数据的实际个数
    while (real_size < 1000) { //防止数组下标越界
        cin >> arr[real_size]; //输入arr[real_size]
        ++real_size; //然后real_size自增
        if (!cin) { //如果输入状态错误
            input_clear(); //先清理输入
            break; //再退出while循环
        }
    }
    return real_size;
}