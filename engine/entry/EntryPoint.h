//
// Created by henry on 2021-12-07.
//

#ifndef FINAL_PROJECT_ENGINE_ENTRY_ENTRYPOINT_H_
#define FINAL_PROJECT_ENGINE_ENTRY_ENTRYPOINT_H_
#ifdef COMPILE_AS_ENGINE

#include <memory>

namespace AGE {

class GameEntryPoint {
  public:
    GameEntryPoint();
    virtual ~GameEntryPoint();
    virtual int run();
};

}

extern std::unique_ptr<AGE::GameEntryPoint> gameEntryPoint(int argc, char *argv[]);

#endif
#endif //FINAL_PROJECT_ENGINE_ENTRY_ENTRYPOINT_H_
