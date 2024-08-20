#pragma once
#include <queue>
#include <string>
#include <unordered_map>
#include <functional>
#include "game/events/event.h"

namespace Temporal::Game::Events
{
    class Event_Manager
    {
    public:
        template <typename event_T>
        void register_subscribe(Event_Handler *handler)
        {
            const char *event_typename = typeid(event_T).name();
            m_handlers_map[event_typename] = handler;
        }
        void publish(std::unique_ptr<Event>& ptr);
        void publish(std::function<void()>);
        void react();
        ~Event_Manager();

    private:
        std::queue<std::unique_ptr<Event>> m_event_queue{};
        std::queue<std::unique_ptr<Event>> m_global_event_queue{};
        std::queue<std::function<void()>> m_cb_queue;
        std::unordered_map<const char *, Event_Handler *> m_handlers_map;
    };
}

using Temporal_Event_Manager = Temporal::Game::Events::Event_Manager;