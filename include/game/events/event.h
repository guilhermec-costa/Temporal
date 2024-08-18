#pragma once
#include "core/ECS/ecs.hpp"
#include <iostream>

namespace Temporal::Game::Events
{
    enum Event_Type
    {
        Move,
        Jump,
    };

    struct Event
    {
        Temporal::Core::ECS::Entity entity;
        Event_Type type;
        virtual ~Event() = default;
        Event(Event_Type type) : type(type) {};
    };

    struct Event_Handler
    {
        virtual void react(Event* event) = 0;
    };

}