#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::__fs::filesystem;

int main() {
    fs::path p = fs::current_path();
    std::cout << p << std::endl;
    std::ifstream day1("../day1/data.txt");
    std::string s;
    long int sum, max;
    max = 0;
    sum = 0;
    while (getline(day1, s)) {
        if (s.empty()) {
            if (sum > max) {
                max = sum;
            }
            sum = 0;
        } else {
            long int add = stoi(s);
            sum += add;
        }
    }
    std::cout << "RESULT:" << std::endl;
    std::cout << max;
    return 0;
}