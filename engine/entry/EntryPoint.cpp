//
// Created by henry on 2021-12-07.
//
#ifdef COMPILE_AS_ENGINE

#include <chrono>
#include <thread>
#include "EntryPoint.h"
#include "../ncurses/CursesRenderAdapter.h"
#include "../events/engine_events/EngineEvent.h"

namespace AGE {

CursesApplicationContext::CursesApplicationContext(int width, int height)
    : windowWidth(width), windowHeight(height),
      manager(std::make_unique<CursesContextManager>()),
      engineEventQueue(std::make_unique<EventQueue>()),
      applicationEventQueue(std::make_unique<EventQueue>()),
      renderTarget(std::make_unique<Renderer::CursesRenderAdapter>(manager->getRendererInstance())),
      asciiRenderer(std::make_unique<AsciiRenderer>(renderTarget.get(), width, height)),
      eventListeners{} {
    // shutdown event listener
    std::unique_ptr<EventDispatcher>
        dispatcher = std::make_unique<MemberEventDispatcher<CursesApplicationContext, Events::EngineShutdownEvent>>
        (this, &CursesApplicationContext::stop);
    engineEventQueue->registerEventDispatcher<Events::EngineShutdownEvent>(dispatcher.get());
    eventListeners.push_back(std::move(dispatcher));
}

void CursesApplicationContext::init() {
    engineEventQueue->enqueue<Events::EngineInitEvent>();
    engineEventQueue->dispatchEvents();
}

int CursesApplicationContext::run() {
    auto delay = std::chrono::milliseconds(500);
    int count = 0;
    while (isRunning) {
        ++count;
        engineEventQueue->enqueue<Events::EngineDrawEvent>();
        engineEventQueue->enqueue<Events::EngineUpdateEvent>(delay);

        if (count > 100) engineEventQueue->enqueue<Events::EngineShutdownEvent>(0);

        engineEventQueue->dispatchEvents();
        std::this_thread::sleep_for(delay);

    }
    return 0;
}

}

// GLOBAL ENTRY POINT FOR AGE ENGINE
int main(int argc, char *argv[]) {
    auto ptr = gameEntryPoint(argc, argv);
    ptr->init();
    return ptr->run();
}

#endif
