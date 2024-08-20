#pragma once
#include "core/ECS/ecs.hpp"
#include <iostream>
#include <memory>

namespace Temporal::Game::Events
{

    struct Event
    {
        Temporal::Core::ECS::Entity m_entity;
        const char *m_type_name;
        virtual ~Event() = default;
        Event(Temporal::Core::ECS::Entity e, const char *type)
            : m_entity(e), m_type_name(type) {}
    };

    struct Event_Handler
    {
        virtual void react(std::unique_ptr<Event> &event) = 0;
    };
}

using Event = Temporal::Game::Events::Event;