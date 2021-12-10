//
// Created by henry on 2021-12-09.
//

#include "BitMapLoader.h"

AGE::BitMap AGE::BitMapLoader::loadBitMap(const std::string &filepath, int xoffset, int yoffset) {
    std::ifstream file{filepath};
    if (file.bad()) {
        auto msg = "Unable to read " + filepath;
        throw std::runtime_error(msg.c_str());
    }
    BitMap result;
    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        for (int col = 0; col < line.length(); ++col) {
            if (line[col] == ' ') continue;
            result.push_back(std::make_pair(vec2<int>(col + xoffset, row + yoffset), line[col]));
        }
        ++row;
    }
    return result;
}
