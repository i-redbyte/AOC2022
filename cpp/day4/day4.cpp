#include <set>
#include <iostream>
#include "FileReader.h"

std::pair<int, int> getBoundaries(std::string line) {
    auto delimiterPos = line.find('-');
    std::string left = line.substr(0, delimiterPos);
    int lowerBound = std::stoi(left) - 48;

    line.erase(0, delimiterPos + 1);
    int upperBound = std::stoi(line) - 48;

    return std::pair<int, int>{lowerBound, upperBound};
}

std::set<int> buildSet(const std::string &line) {
    std::pair<int, int> boundaries = getBoundaries(line);
    std::set<int> set{};
    for (int i = boundaries.first; i <= boundaries.second; ++i) {
        set.insert(i);
    }
    return set;
}

std::set<int> &findSmallestSet(std::set<int> &setA, std::set<int> &setB) {
    if (setA.size() >= setB.size()) {
        return setB;
    } else {
        return setA;
    }
}

std::set<int> &findLargestSet(std::set<int> &setA, std::set<int> &setB) {
    if (setA.size() < setB.size()) {
        return setB;
    } else {
        return setA;
    }
}

int part1(const std::set<int> &smallestSet, const std::set<int> &largestSet) {
    bool fullyCovered = true;
    for (const auto &val: smallestSet) {
        if (largestSet.count(val) == 0) {
            fullyCovered = false;
            break;
        }
    }
    return fullyCovered;
}

bool part2(const std::set<int> &smallestSet, const std::set<int> &largestSet) {
    bool anyOverlap = false;
    for (const auto &val: smallestSet) {
        if (largestSet.count(val) != 0) {
            anyOverlap = true;
            break;
        }
    }
    return anyOverlap;
}

int main() {
    FileReader fr{};
    std::vector<std::string> readLines{fr.readLines("../cpp/day4/data.txt")};
    int fullyOverlap{0};
    int anyOverlap{0};
    for (auto &line: readLines) {
        auto delimiterPos = line.find(',');
        std::string left = line.substr(0, delimiterPos);
        std::set<int> leftSet{buildSet(left)};

        line.erase(0, delimiterPos + 1);
        std::set<int> rightSet{buildSet(line)};

        auto &smallestSet = findSmallestSet(leftSet, rightSet);
        auto &largestSet = findLargestSet(leftSet, rightSet);

        if (part1(smallestSet, largestSet)) {
            fullyOverlap++;
        }
        if (part2(smallestSet, largestSet)) {
            anyOverlap++;
        }
    }

    std::cout << "Part 1 - Fully overlap: " << fullyOverlap << std::endl;
    std::cout << "Part 2 - Any overlap: " << anyOverlap << std::endl;

    assert(fullyOverlap == 513);
    assert(anyOverlap == 878);

    return 0;
}