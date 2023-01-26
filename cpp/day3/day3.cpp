#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

#include "FileReader.h"
#include "Utility.h"

int charToInt(const char &ch) {
    if (std::islower(ch)) {
        return (int) (ch - 96);
    } else {
        return (int) (ch - 38);
    }
}

int calcScores(std::vector<char> charVec) {
    int res = 0;
    for (auto ch: charVec) {
        res += charToInt(ch);
    }
    return res;
}

std::set<char> splitLineToSet(std::string &line, const int &start, const int &end) {
    std::set<char> set{};
    for (int i = start; i < end; ++i) {
        set.insert(line[i]);
    }
    return set;
}

int part1() {
    FileReader fr;
    std::vector<std::string> lines = fr.readLines("../day3/data3_1.txt");

    std::vector<std::set<char>> bagsA;
    std::vector<std::set<char>> bagsB;

    for (auto &line: lines) {
        assert((line.size() % 2) == 0);
        int numChars = line.size();
        auto seenCharsCompA{splitLineToSet(line, 0, numChars / 2)};
        auto seenCharsCompB{splitLineToSet(line, numChars / 2, numChars)};
        bagsA.push_back(seenCharsCompA);
        bagsB.push_back(seenCharsCompB);
    }

    std::vector<char> charInBothComps{};
    for (int i = 0; i < bagsA.size(); ++i) {
        auto intersection{Utility::setIntersection(bagsA[i], bagsB[i])};
        for (const auto &elem: intersection) {
            charInBothComps.push_back(elem);
        }
    }

    int res{calcScores(charInBothComps)};

    std::cout << res << std::endl;
    return res;
}

int part2() {
    FileReader fr;
    std::vector<std::string> lines = fr.readLines("../cpp/day3/data3_1.txt");
    std::vector<std::set<char>> elves{};

    for (auto line: lines) {
        auto seenChars{splitLineToSet(line, 0, line.size())};
        elves.push_back(seenChars);
    }

    std::vector<char> charAtAllElves{};
    for (int i = 0; i < elves.size() - 2; i += 3) {
        std::vector<char> firstIntersection{Utility::setIntersection(elves[i], elves[i + 1])};
        std::set<char> firstIntersectionSet{Utility::vectorToSet(firstIntersection)};
        std::vector<char> finalIntersection{Utility::setIntersection(firstIntersectionSet, elves[i + 2])};
        for (auto &elem: finalIntersection) {
            charAtAllElves.push_back(elem);
        }
    }
    int res{calcScores(charAtAllElves)};

    std::cout << res << std::endl;
    return res;
}

int main() {
    assert(part1() == 8252);
    assert(part2() == 2828);
    return 0;
}