#include<iostream>
#include<exception>
#include<stdexcept>
#include<vector>
class Complex {
    double real;
    double image;
public:
    Complex(double r=0,double i=0):real{r},image{i}{}
    Complex operator+(const Complex &c)const{
        return Complex(real+c.real,image+c.image);
    }
    // friend Complex operator+(const Complex &c1, const Complex &c2){
    //     return Complex(c1.real+c2.real,c1.image+c2.image);
    // }
};
int main() {
    Complex a(1,2);
    2+a;
    return 0;
}