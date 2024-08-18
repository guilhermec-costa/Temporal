#pragma once
#include "core/ECS/ecs.hpp"
#include <iostream>

namespace Temporal::Game::Events
{

    struct Event
    {
        Temporal::Core::ECS::Entity m_entity;
        const char* m_type_name;
        virtual ~Event() = default;
        Event(Temporal::Core::ECS::Entity e, const char* type)
            : m_entity(e), m_type_name(type) {}

    };

    struct Event_Handler
    {
        virtual void react(Event* event) = 0;
    };

}