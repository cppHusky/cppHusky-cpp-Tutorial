#include "Header.h" //它需要包含头文件Header.h
void input_clear(istream& in) { //声明部分已经有默认参数cin，这里不应再写
    in.clear();
    while (in.get() != '\n')
        continue;
}