//
// Created by henry on 2021-12-07.
//

#ifndef FINAL_PROJECT_ENGINE_EVENTS_ENGINE_EVENTS_ENGINEEVENT_H_
#define FINAL_PROJECT_ENGINE_EVENTS_ENGINE_EVENTS_ENGINEEVENT_H_

#include "../Event.h"
#include "chrono"

namespace AGE::Events {

class EngineEvent : public Event {};

class EngineDrawEvent : public EngineEvent {};
class EngineInitEvent : public EngineEvent {};
class EngineUpdateEvent : public EngineEvent {
    std::chrono::milliseconds elapsed;
  public:
    explicit EngineUpdateEvent(std::chrono::milliseconds time) : elapsed(time) {};
    [[nodiscard]] std::chrono::milliseconds getElapsedTime() const { return elapsed; }
};
class EngineShutdownEvent : public EngineEvent {
    int stopcode;
  public:
    explicit EngineShutdownEvent(int code = 0) : stopcode(code) {}
    [[nodiscard]] int getStopCode() const { return stopcode; }
};

}

#endif //FINAL_PROJECT_ENGINE_EVENTS_ENGINE_EVENTS_ENGINEEVENT_H_
