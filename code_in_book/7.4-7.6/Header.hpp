//本文件用于存放结构体的定义与函数的声明
#pragma once
struct Data { //Data仍需放在前面
    int num;
    Data* next;
};
void clear_list(Data*); //函数声明的时候可以不注参数名
void insert_after(Data*, int);
bool delete_after(Data*); //重载
bool delete_after(Data*, Data*); //重载
void transfer(Data*, Data*, Data*); //这个函数需要用到utility库，但不是在这