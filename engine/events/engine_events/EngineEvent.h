//
// Created by henry on 2021-12-07.
//

#ifndef FINAL_PROJECT_ENGINE_EVENTS_ENGINE_EVENTS_ENGINEEVENT_H_
#define FINAL_PROJECT_ENGINE_EVENTS_ENGINE_EVENTS_ENGINEEVENT_H_

#include <ecs/Entity.h>
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

class ApplicationEvent : public Event {};
class KeyPressedEvent : public ApplicationEvent {
    int keycode;
  public:
    explicit KeyPressedEvent(int code) : keycode(code) {}
    [[nodiscard]] int getKeyCode() const { return keycode; }
};
class SwitchSceneEvent : public ApplicationEvent {
    std::string newSceneName;
  public:
    explicit SwitchSceneEvent(std::string name) : newSceneName(std::move(name)) {}
    [[nodiscard]] const std::string &getNewSceneName() const { return newSceneName; }
};

class CollisionEvent : public Event {};
class BasicCollisionEvent : public CollisionEvent {
    ECS::Entity entity1;
    ECS::Entity entity2;
  public:
    explicit BasicCollisionEvent(ECS::Entity entity1, ECS::Entity entity2)
        : entity1(entity1), entity2(entity2) {}
    [[nodiscard]] std::pair<ECS::Entity, ECS::Entity> getCollidingPair() const {
        return std::make_pair(entity1, entity2);
    }
};

}

#endif //FINAL_PROJECT_ENGINE_EVENTS_ENGINE_EVENTS_ENGINEEVENT_H_
