//
// Created by henry on 2021-12-07.
//
#ifdef COMPILE_AS_ENGINE

#include <chrono>
#include <thread>
#include "EntryPoint.h"
#include "../ncurses/CursesRenderAdapter.h"

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

    // debug: keypress handler
    std::unique_ptr<EventDispatcher>
        dispatcher2 = std::make_unique<MemberEventDispatcher<CursesApplicationContext, Events::KeyPressedEvent>>
        (this, &CursesApplicationContext::keyhandler);
    applicationEventQueue->registerEventDispatcher<Events::KeyPressedEvent>(dispatcher2.get());
    eventListeners.push_back(std::move(dispatcher2));
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
        // queue up engine events
        engineEventQueue->enqueue<Events::EngineDrawEvent>();
        engineEventQueue->enqueue<Events::EngineUpdateEvent>(delay);

        if (count > 100) engineEventQueue->enqueue<Events::EngineShutdownEvent>(0);

        // queue all user keyboard inputs
        manager->getKeyboardInstance()->captureInputs();
        std::optional<int> keycode = manager->getKeyboardInstance()->getKeycode();
        while (keycode) {
            applicationEventQueue->enqueue<Events::KeyPressedEvent>(keycode.value());
            keycode = manager->getKeyboardInstance()->getKeycode();
        }

        engineEventQueue->dispatchEvents(); // dispatch engine events first
        applicationEventQueue->dispatchEvents(); // dispatch application events second
        std::this_thread::sleep_for(delay);

    }
    return 0;
}

void CursesApplicationContext::keyhandler(Events::KeyPressedEvent *event, EventQueue *eventQueue) {
    if (event->getKeyCode() == 'r') {
        isRunning = false;
    }
}

}

// GLOBAL ENTRY POINT FOR AGE ENGINE
int main(int argc, char *argv[]) {
    auto ptr = gameEntryPoint(argc, argv);
    ptr->init();
    return ptr->run();
}

#endif
