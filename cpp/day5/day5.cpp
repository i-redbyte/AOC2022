#include <iostream>
#include <vector>
#include "FileReader.h"

std::string part1(const std::vector<std::string> &input);

std::string part2(const std::vector<std::string> &input);

struct Boxes {
    unsigned long stack_count;
    std::vector<std::vector<char>> stacks;

    explicit Boxes(unsigned long count) {
        stack_count = count;
        stacks.resize(stack_count);
    }

    void fill(std::vector<std::string> &boxes) {
        for (auto it = boxes.rbegin(); it != boxes.rend(); it++) {
            for (int j = 0, i = 1; i < (*it).length(); j++, i = i + 4) {
                if ((*it)[i] != ' ') stacks[j].push_back((*it)[i]);
            }
        }
    }

    void moveByOne(const std::string &move_info) {
        int it = 5;
        int box_count = 0;
        int stack_from = 0;
        int stack_to = 0;
        while (move_info[it] != ' ') {
            box_count = box_count * 10 + (move_info[it] - '0');
            it++;
        }
        it += 6;
        while (move_info[it] != ' ') {
            stack_from = stack_from * 10 + (move_info[it] - '0');
            it++;
        }
        it += 4;
        while (it < move_info.length()) {
            stack_to = stack_to * 10 + (move_info[it] - '0');
            it++;
        }

        for (int i = 0; i < box_count; i++) {
            char c = stacks[stack_from - 1].back();
            stacks[stack_from - 1].pop_back();
            stacks[stack_to - 1].push_back(c);
        }
    }

    void moveMultiple(const std::string &move_info) {
        int index = 5;
        int box_count = 0;
        int stack_from = 0;
        int stack_to = 0;
        while (move_info[index] != ' ') {
            box_count = box_count * 10 + (move_info[index] - '0');
            index++;
        }
        index += 6;
        while (move_info[index] != ' ') {
            stack_from = stack_from * 10 + (move_info[index] - '0');
            index++;
        }
        index += 4;
        while (index < move_info.length()) {
            stack_to = stack_to * 10 + (move_info[index] - '0');
            index++;
        }
        std::vector<char> move_stack;
        for (int i = box_count - 1; i >= 0; i--) {
            move_stack.push_back(stacks[stack_from - 1].at(stacks[stack_from - 1].size() - 1 - i));
        }
        stacks[stack_from - 1].erase(stacks[stack_from - 1].end() - box_count, stacks[stack_from - 1].end());
        stacks[stack_to - 1].insert(stacks[stack_to - 1].end(), move_stack.begin(), move_stack.end());
    }

    std::string getTopBoxes() {
        std::string tops;
        for (std::vector<char> stack: stacks) {
            tops.push_back(stack.back());
        }
        return tops;
    }
};

int main() {
    FileReader fr{};
    std::vector<std::string> readLines{fr.readLines("../cpp/day5/data.txt")};
    std::cout << part1(readLines) << std::endl;
    std::cout << part2(readLines) << std::endl;
}


std::string part2(const std::vector<std::string> &input) {
    int stack_coord = 0;
    while (input[stack_coord][1] != '1') {
        stack_coord++;
    }
    unsigned long stack_count = input[stack_coord].length() / 4 + 1;
    Boxes boxes(stack_count);

    std::vector<std::string> boxes_init_pos;
    for (int i = 0; i < stack_coord; i++) {
        boxes_init_pos.push_back(input[i]);
    }
    boxes.fill(boxes_init_pos);
    for (int i = stack_coord + 2; i < input.size(); i++) {
        boxes.moveMultiple(input[i]);
    }
    return boxes.getTopBoxes();
}

std::string part1(const std::vector<std::string> &input) {
    int stack_coord = 0;
    while (input[stack_coord][1] != '1') {
        stack_coord++;
    }
    unsigned long stack_count = input[stack_coord].length() / 4 + 1;
    Boxes boxes(stack_count);

    std::vector<std::string> boxes_init_pos;
    for (int i = 0; i < stack_coord; i++) {
        boxes_init_pos.push_back(input[i]);
    }
    boxes.fill(boxes_init_pos);
    for (int i = stack_coord + 2; i < input.size(); i++) {
        boxes.moveByOne(input[i]);
    }
    return boxes.getTopBoxes();
}
