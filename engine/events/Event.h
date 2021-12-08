//
// Created by henry on 2021-12-07.
//

#ifndef FINAL_PROJECT_ENGINE_EVENTS_EVENT_H_
#define FINAL_PROJECT_ENGINE_EVENTS_EVENT_H_

#include <functional>
#include <vector>
#include <memory>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

namespace AGE {

class Event {
  public:
    virtual ~Event() = default;
};

class UnknownEventException : std::exception {};

class EventQueue;
class EventDispatcher {
  public:
    void operator()(Event *event, EventQueue *eventQueue) const {
        call(event, eventQueue);
    }
  private:
    virtual void call(Event *event, EventQueue *eventQueue) const = 0;
};

template<class T, class EventType>
class MemberEventDispatcher : public EventDispatcher {
  public:
    using MemberFunction = void (T::*)(EventType *event, EventQueue *eventQueue);
    explicit MemberEventDispatcher(T *instance, MemberFunction function)
        : instance{instance}, func{function} {};
    void call(Event *event, EventQueue *eventQueue) const override {
        (instance->*func)(static_cast<EventType *>(event), eventQueue);
    }
  private:
    T *instance;
    MemberFunction func;
};

template<class EventType>
class FunctionEventDispatcher : public EventDispatcher {
  public:
    using LambdaFunction = std::function<void(EventType *event, EventQueue *eventQueue)>;
    explicit FunctionEventDispatcher(LambdaFunction function) : function{std::move(function)} {};
    void call(Event *event, EventQueue *eventQueue) const override {
        function(static_cast<EventType *>(event), eventQueue);
    }
  private:
    LambdaFunction function;
};

class EventQueue {
    std::unordered_map<std::type_index,
                       std::vector<const EventDispatcher *>> dispatchers;
    std::vector<std::unique_ptr<Event>> queue;
    std::vector<std::type_index> queueEventType;
  public:
    template<typename EventType, typename... Args>
    void enqueue(Args &&... args) {
        queue.push_back(std::make_unique<EventType>(std::forward<Args>(args)...));
        queueEventType.emplace_back(typeid(EventType));
    }

    void dispatchEvents() {
        for (int i = 0; i < queue.size(); ++i) {
            auto &eventType = queueEventType[i];
            for (auto &dispatcher: dispatchers[eventType]) {
                dispatcher->operator()(queue[i].get(), this);
            }
        }
        queue.clear();
        queueEventType.clear();
    }

    template<typename EventType>
    void registerEventDispatcher(const EventDispatcher *eventDispatcher) {
        dispatchers[typeid(EventType)].push_back(eventDispatcher);
    }

    template<typename EventType>
    void unregisterEventDispatcher(const EventDispatcher *eventDispatcher) {
        std::remove_if(dispatchers[typeid(EventType)].begin(), dispatchers[typeid(EventType)].end(),
                       [&eventDispatcher](auto ptr) {
                         return eventDispatcher == ptr;
                       });
    }
};

}

#endif //FINAL_PROJECT_ENGINE_EVENTS_EVENT_H_
