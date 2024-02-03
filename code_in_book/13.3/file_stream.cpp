#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
int main() {
    std::ofstream fout;
    std::cout<<"Program started.\n";
    fout.open("out.txt", std::ios_base::out);
    if(!fout.is_open())
        std::cerr<<"Didn't opened the file."<<std::flush;
    fout << 12345 << std::endl;
    fout.close();
    std::cout<<"Program ended."<<std::flush;
    return 0;
}