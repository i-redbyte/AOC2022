#include <set>
#include <vector>
#include <iostream>
#include "FileReader.h"

bool isCharSeen(const char &ch, const std::set<char> &set) {
    return (set.count(ch) != 0);
}

int solution(const std::string &line, int charCnt) {
    std::set<char> seenChars{};

    int slowPointer = 0;
    int i = 0;
    while (i < line.size() - 3) {
        auto ch = line[i];
        if (isCharSeen(ch, seenChars)) {
            i = slowPointer - 1;
            ++slowPointer;
            seenChars.clear();
        } else {
            seenChars.insert(ch);
        }
        if (seenChars.size() == charCnt) {
            std::cout << "Position i: " << i + 1 << std::endl;
            break;
        }
        i++;
    }
    return (i + 1);
}


int main() {
    FileReader fr;
    std::vector<std::string> readLines{fr.readLines("../cpp/day6/data.txt")};
    auto line = readLines[0];
    assert(solution(line, 4) == 1140);
    assert(solution(line, 14) == 3495);
    return 0;
}