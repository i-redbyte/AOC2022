#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::__fs::filesystem;

int main() {
    fs::path p = fs::current_path();
    std::cout << p << std::endl;
    std::ifstream day1("../cpp/day1/data3_1.txt");
    std::string s;
    long int sum, elf1, elf2, elf3;
    elf1 = 0;
    elf2 = 0;
    elf3 = 0;
    sum = 0;
    while (getline(day1, s)) {
        if (s.empty()) {
            if (sum > elf1) {
                elf3 = elf2;
                elf2 = elf1;
                elf1 = sum;
            } else if (elf2 < sum && elf1 != sum) {
                elf3 = elf2;
                elf2 = sum;
            } else if (elf3 < sum && elf2 != sum && elf1 != sum) {
                elf3 = sum;
            }
            sum = 0;
        } else {
            long int add = stoi(s);
            sum += add;
        }
    }
    std::cout << std::endl << elf1 << std::endl << elf2 << std::endl << elf3 << std::endl;
    std::cout << "RESULT:" << std::endl;
    std::cout << elf1 + elf2 + elf3;
    return 0;
}