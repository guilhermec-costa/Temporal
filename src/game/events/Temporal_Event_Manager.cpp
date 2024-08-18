#include "game/events/Temporal_Event_Manager.h"

namespace Temporal::Game::Events
{
    void Event_Manager::publish(Event *event)
    {
        m_event_queue.push(event);
    }

    void Event_Manager::react()
    {
        while (!m_event_queue.empty())
        {
            Event *event = m_event_queue.front();
            auto handler = m_handlers_map.find(event->m_type_name);
            handler->second->react(event);
            m_event_queue.pop();
            delete event;
        }
    }

    Event_Manager::~Event_Manager()
    {
        for (auto const &pair : m_handlers_map)
        {
            delete pair.second;
        }
    }
}