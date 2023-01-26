#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

class FileReader
{
private:
public:
    FileReader() = default;
    std::vector<std::string> readLines(const std::string& fileName)
    {
        std::ifstream in(fileName);
        if (!in.is_open())
        {
            throw std::system_error(errno, std::generic_category(), fileName);
        }

        std::string line{};
        std::vector<std::string> res {};
        while(std::getline(in, line))
        {
            res.push_back(line);
        }
        return res;
    }

    std::vector<std::vector<int>> readLinesAsInt(const std::string& fileName)
    {
        std::ifstream in(fileName);
        if (!in.is_open())
        {
            throw std::system_error(errno, std::generic_category(), fileName);
        }

        std::string line{};
        std::vector<std::string> resStr {};
        while(std::getline(in, line))
        {
            resStr.push_back(line);
        }

        std::vector<std::vector<int>> res {};
        for(int i = 0; i < resStr.size(); ++i)
        {
            std::vector<int> tmp {};
            for(int j = 0; j < resStr[0].size(); ++j)
            {
                tmp.push_back(int(resStr[i][j]) - '0');
            }
            res.push_back(tmp);
        }
        return res;
    }


    std::vector<std::pair<char, char>> readPairs(const std::string& fileName)
    {
        std::ifstream in(fileName);
        if (!in.is_open())
        {
            throw std::system_error(errno, std::generic_category(), fileName);
        }
        std::string line{};
        std::vector<std::pair<char, char>> res {};
        while(std::getline(in, line))
        {
            std::pair<char, char> pair {line[0], line[2]};
            res.push_back(pair);
        }
        return res;
    }
};