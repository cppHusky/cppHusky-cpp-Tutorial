#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
int main() {
    std::string str {"abcdef"};
    std::ostringstream strio {str, std::ios_base::out | std::ios_base::trunc};
    // std::ostringstream strio {"abcdef", std::ios_base::app};
    strio.put('g');
    std::cout << str;
    // std::cout << strio.str();
    return 0;
}