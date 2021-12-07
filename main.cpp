#include <iostream>
#include <chrono>
#include <thread>

#include "ncurses.h"

#include "engine/events/Event.h"

class MessageEvent : public AGE::Event {
    std::string msg;
  public:
    explicit MessageEvent(std::string msg) : msg{std::move(msg)} {}
    std::string &getMessage() { return msg; }
};

class TestSystem {
    std::unique_ptr<AGE::EventDispatcher> dispatcher;
    AGE::EventQueue *eventQueue;
  public:
    explicit TestSystem(AGE::EventQueue *eventQueue)
        : dispatcher(std::make_unique<AGE::MemberEventDispatcher<TestSystem, MessageEvent>>
                         (this, &TestSystem::handleSomeEvent)),
          eventQueue(eventQueue) {
        eventQueue->registerEventDispatcher<MessageEvent>(dispatcher.get());
    }
    ~TestSystem() {
        eventQueue->unregisterEventDispatcher<MessageEvent>(dispatcher.get());
    }
    void handleSomeEvent(MessageEvent *event, AGE::EventQueue *queue) {
        std::cout << event->getMessage() << std::endl;
    }
};

void test(AGE::EventQueue *queue) {
    TestSystem system1(queue);
    queue->enqueue<MessageEvent>("Hello World!");
    queue->dispatchEvents();
}

int main(int argc, char *argv[]) {
    using namespace AGE;

    EventQueue queue;
    test(&queue);

    queue.dispatchEvents();

    return 0;
}
