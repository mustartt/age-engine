//
// Created by henry on 2021-12-09.
//

#include "Event.h"

namespace AGE {

void EventDispatcher::operator()(Event *event, EventQueue *eventQueue) const {
    call(event, eventQueue);
}

void EventQueue::dispatchEvents() {
    for (int i = 0; i < queue.size(); ++i) {
        auto &eventType = queueEventType[i];
        for (auto &dispatcher: dispatchers[eventType]) {
            dispatcher->operator()(queue[i].get(), this);
        }
    }
    queue.clear();
    queueEventType.clear();
}

}
