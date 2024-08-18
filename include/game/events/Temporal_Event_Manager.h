#pragma once
#include <queue>
#include <string>
#include <unordered_map>
#include "game/events/event.h"

namespace Temporal::Game::Events
{
    class Event_Manager
    {
    public:
        template <typename event_T>
        void register_handler(Event_Handler *handler)
        {
            const char *event_typename = typeid(event_T).name();
            m_handlers_map[event_typename] = handler;
        }
        void publish(Event *event);
        void react();
        ~Event_Manager();

    private:
        std::queue<Event *> m_event_queue;
        std::unordered_map<const char *, Event_Handler *> m_handlers_map;
    };
}

using Temporal_Event_Manager = Temporal::Game::Events::Event_Manager;