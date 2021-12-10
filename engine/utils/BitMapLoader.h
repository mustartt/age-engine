//
// Created by henry on 2021-12-09.
//

#ifndef FINAL_PROJECT_ENGINE_UTILS_BITMAPLOADER_H_
#define FINAL_PROJECT_ENGINE_UTILS_BITMAPLOADER_H_

#include <fstream>
#include <vector>
#include <utility>
#include <utils/vec2.h>

namespace AGE {

using Character = std::pair<vec2<int>, char>;
using BitMap = std::vector<Character>;

class BitMapLoader {
  public:
    [[maybe_unused]] static BitMap loadBitMap(const std::string &filepath, int xoffset = 0, int yoffset = 0);
};

}

#endif //FINAL_PROJECT_ENGINE_UTILS_BITMAPLOADER_H_
