#include <iostream>
#include <chrono>
#include <thread>

#include "engine/age.h"

[[noreturn]] void DEBUG_PAUSE() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

class Application : public AGE::GameEntryPoint {
  public:
    Application() = default;
    ~Application() override = default;
    int run() override {

        

        return 0;
    }
};

// resolve entry point extern
std::unique_ptr<AGE::GameEntryPoint> gameEntryPoint(int argc, char *argv[]) {
    return std::make_unique<Application>();
}
