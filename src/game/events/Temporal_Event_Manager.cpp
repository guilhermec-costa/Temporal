#include "game/events/Temporal_Event_Manager.h"
#include <memory>

namespace Temporal::Game::Events
{
    void Event_Manager::publish(std::unique_ptr<Event> &event)
    {
        m_event_queue.push(std::move(event));
    }

    void Event_Manager::publish(const std::function<void()> _fn)
    {
        m_cb_queue.push(_fn);
    }

    void Event_Manager::react()
    {

        while (!m_event_queue.empty())
        {
            auto &event = m_event_queue.front();
            auto handler = m_handlers_map.find(event->m_type_name);
            handler->second->react(event);
            m_event_queue.pop();
        }

        while (!m_cb_queue.empty())
        {
            auto &fn = m_cb_queue.front();
            fn();
            m_cb_queue.pop();
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