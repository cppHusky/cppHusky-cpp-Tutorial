#pragma once
#include <cmath>
struct Shape { //抽象基类，这个类用来表示各种几何图形
    static constexpr double Pi {3.1415926}; //常量表达式Pi
    static constexpr double Deg2Rad(double deg) { //用于角度转弧度
        return deg * Pi / 180;
    }
    static constexpr double Rad2Deg(double rad) { //用于弧度转角度
        return rad * 180 / Pi;
    }
    virtual double perimeter()const = 0; //周长，纯虚函数
    virtual double area()const = 0; //面积，纯虚函数
};
class Triangle : public Shape { //三角形
    double _a;
    double _b;
    double _c; //三角形的三条边
public:
    Triangle(double a, double b, double c)
        : _a {a}, _b {b}, _c {c} {} //构造函数
    double perimeter()const { return _a + _b + _c; } //周长
    double area()const { //面积
        double s {(_a + _b + _c) / 2};
        return std::sqrt(s * (s - _a) * (s - _b) * (s - _c));
    }
};
class Circle : public Shape { //圆形
    double _r; //圆的半径
public:
    Circle(double r) : _r {r} {}
    double perimeter()const { return 2 * Pi * _r; } //周长
    double area()const { return Pi * _r * _r; } //面积
};
class Parallelogram_abc : public Shape { // 抽象平行四边形基类
protected:
    double _a; //所有平行四边形都至少需要一条边长信息
public:
    Parallelogram_abc(double a) : _a {a} {} //构造函数
};
class Parallelogram : public Parallelogram_abc { //平行四边形
    double _b;
    double _theta;
public:
    Parallelogram(double a, double b, double theta)
        : Parallelogram_abc {a}, _b {b}, _theta {theta} {}
    double perimeter()const { return 2 * (_a + _b); }
    double area()const { return _a * _b * std::sin(Deg2Rad(_theta)); }
};
struct Rhombus_abc : virtual public Parallelogram_abc { //抽象菱形基类
    Rhombus_abc(double a) : Parallelogram_abc {a} {}
    double perimeter()const { return 4 * _a; } //菱形、正方形通用的周长公式
};
struct Rectangle_abc : virtual public Parallelogram_abc { //抽象矩形基类
    Rectangle_abc(double a) : Parallelogram_abc {a} {}
};
class Rhombus : public Rhombus_abc { //菱形
    double _theta;
public:
    Rhombus(double a, double theta)
        : Parallelogram_abc {a}, Rhombus_abc {a}, _theta {theta} {}
    //因为Rhombus_abc虚继承自Parallelogram_abc，我们必须单独调用后者的构造函数
    //又因为Rhombus继承自Rhombus_abc，我们必须调用后者的构造函数
    double area()const { return _a * _a * std::sin(Deg2Rad(_theta)); }
};
class Rectangle : public Rectangle_abc { //矩形
    double _b;
public:
    Rectangle(double a, double b)
        : Parallelogram_abc {a}, Rectangle_abc {a}, _b {b} {}
    //同上，不再赘述
    double perimeter()const { return 2 * (_a + _b); }
    double area()const { return _a * _b; }
};
struct Square : Rhombus_abc, Rectangle_abc { //正方形
    Square(double a)
        : Parallelogram_abc {a}, Rhombus_abc {a}, Rectangle_abc {a} {}
    double area()const { return _a * _a; }
    //perimeter函数继承自Rhombus_abc足矣，不必再写
};