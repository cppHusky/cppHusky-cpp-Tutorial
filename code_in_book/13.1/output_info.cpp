#include<iostream>
#include<sstream>
#include<iomanip>
enum Sex : bool {male, female};
struct PersonalInfo {
    const std::string name;
    const Sex sex;
    unsigned age;
    double height;
};
std::ostream& operator<<(std::ostream &out, const Sex s) { //可以进行运算符重载
    return out << (s == male ? "M" : "F"); //<<的优先级高于?:所以要套括号
}
int main() {
    PersonalInfo persons[] {
        { "Alice", female, 28, 165.1 },
        { "Bob", male, 32, 185.45 },
        { "Charlie", male, 45, 175.3 },
        { "Diana", female, 37, 170.26 }
    };
    std::cout << std::setw(10) << "Name" << std::setw(5) << "Sex"
              << std::setw(5) << "Age" << std::setw(9) << "Height\n";
    for (auto person : persons) {
        std::cout << std::setw(10) << person.name << std::setw(5) << person.sex
                  << std::setw(5) << person.age << std::setw(9) << person.height
                  << '\n';
    }
    return 0;
}