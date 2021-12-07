//
// Created by henry on 2021-12-07.
//
#ifdef COMPILE_AS_ENGINE

#include "EntryPoint.h"

namespace AGE {

GameEntryPoint::GameEntryPoint() = default;
GameEntryPoint::~GameEntryPoint() = default;

int GameEntryPoint::run() {
    return 0;
}

}

// GLOBAL ENTRY POINT FOR AGE ENGINE
int main(int argc, char *argv[]) {
    auto ptr = gameEntryPoint(argc, argv);
    return ptr->run();
}

#endif
