#pragma once
#include <queue>
#include <string>
#include <unordered_map>
#include "game/events/event.h"

namespace Temporal::Game::Events {
    class Event_Manager
    {
        public:

            void register_handler(Event_Type type, Event_Handler* handler)
            {
                m_handlers_map[type] = handler;
            }

            void publish(Event* event)
            {
                m_event_queue.push(event);
            }

            void react()
            {
                while(!m_event_queue.empty())
                {
                    Event* event = m_event_queue.front();
                    auto handler = m_handlers_map.find(event->type);
                    handler->second->react(event);
                    m_event_queue.pop();
                    delete event;
                }
            }

            ~Event_Manager()
            {
                for(auto const& pair: m_handlers_map)
                {
                    delete pair.second;
                }
            }

        private:
            std::queue<Event*> m_event_queue;
            std::unordered_map<Event_Type, Event_Handler*> m_handlers_map;
    };
}

using Temporal_Event_Manager = Temporal::Game::Events::Event_Manager;