
#include <chrono>
#include <thread>

#include "engine/age.h"

#include "utils/vec2.h"
#include "utils/vec3.h"

// #include <FeatureDemo.h>
#include <SpaceInvader.h>

[[noreturn]] void DEBUG_PAUSE() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// resolve entry point extern
std::unique_ptr<AGE::ApplicationContext> gameEntryPoint(int argc, char *argv[]) {
    return std::make_unique<SpaceInvader::SpaceInvader>();
}
