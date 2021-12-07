//
// Created by henry on 2021-12-07.
//

#ifndef FINAL_PROJECT_ENGINE_EVENTS_EVENT_H_
#define FINAL_PROJECT_ENGINE_EVENTS_EVENT_H_

#include <exception>
#include <functional>
#include <typeindex>
#include <memory>
#include <list>

class Event {
  public:
    virtual ~Event() = delete;
};

class UnknownEventException : std::exception {};

class EventQueue;
class EventDispatcher {
  public:
    void operator()(const Event *event, EventQueue *eventQueue) const {
        call(event, eventQueue);
    }
  private:
    virtual void call(const Event *event, EventQueue *eventQueue) const = 0;
};

using MemberFunction = void (*)(Event *event, EventQueue *eventQueue);
using LambdaFunction = std::function<void(Event *event, EventQueue *eventQueue)>;

template<class T, class EventType>
class MemberEventDispatcher : public EventDispatcher {
    T *instance;
    MemberFunction func;
  public:
    explicit MemberEventDispatcher(T *instance, MemberFunction function)
        : instance{instance}, func{function} {};
    void call(const Event *event, EventQueue *eventQueue) const override {
        instance->*func(static_cast<EventType *>(event, eventQueue));
    }
};

template<class EventType>
class FunctionEventDispatcher : public EventDispatcher {
    LambdaFunction function;
  public:
    explicit FunctionEventDispatcher(LambdaFunction function) : function{std::move(function)} {};
    void call(const Event *event, EventQueue *eventQueue) const override {
        function(static_cast<EventType *>(event, eventQueue));
    }
};

class EventQueue {
    std::unordered_map<std::type_index,
                       std::vector<const EventDispatcher *>> dispatchers;
    std::vector<std::pair<std::type_index, std::unique_ptr<Event>>> queue;
  public:
    template<typename EventType, typename... Args>
    void enqueue(Args &&... args) {
        auto event = std::make_unique<EventType>(std::forward<Args>(args)...);
        queue.push_back(std::make_pair(typeid(EventType), event));
    }

    void dispatchEvents() {
        for (auto &eventPair: queue) {
            auto &dispatcherList = dispatchers[eventPair.first];
            for (auto &dispatcher: dispatcherList) {
                dispatcher->operator()(eventPair.second.get(), this);
            }
        }
        queue.clear();
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

#endif //FINAL_PROJECT_ENGINE_EVENTS_EVENT_H_
