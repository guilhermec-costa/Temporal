#pragma once
#include <memory>
#include "core/math/Vector2D.h"
#include "core/ECS/ecs.hpp"
#include "game/events/event.h"

using Entity = Temporal::Core::ECS::Entity;

namespace Temporal::Game::Events
{
    enum Move_Event_Type
    {
        Move_UP,
        Move_DOWN,
        Move_LEFT,
        Move_RIGHT,
        Stop_UP,
        Stop_DOWN,
        Stop_LEFT,
        Stop_RIGHT
    };

    struct Move_Event : public Event
    {
        Move_Event_Type m_move_type;
        Move_Event(Entity e, Move_Event_Type type)
            : Event(e, typeid(Move_Event).name()), m_move_type(type) {}
    };

    struct Move_Event_Subscriber : public Event_Handler
    {
        Move_Event_Subscriber() = default;
        void react(std::unique_ptr<Event> &event);
    };
}

using Move_Event = Temporal::Game::Events::Move_Event;
using Move_Event_Subscriber = Temporal::Game::Events::Move_Event_Subscriber;
using Move_Event_Type = Temporal::Game::Events::Move_Event_Type;