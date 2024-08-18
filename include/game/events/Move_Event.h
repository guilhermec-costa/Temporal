#pragma once
#include "core/math/Vector2D.h"
#include "core/ECS/ecs.hpp"
#include "game/events/event.h"

extern ECS_Orchestrator gECS_Orchestrator;

namespace Temporal::Game::Events
{
    struct Move_Event : public Event
    {
        Vector2D m_move_by;
        Temporal::Core::ECS::Entity m_entity;
        Move_Event(Entity e, float x, float y)
            : Event(Event_Type::Move), m_entity(e), m_move_by(x, y) {};
    };

    struct Move_Event_Handler : public Event_Handler
    {
        Move_Event_Handler() = default;
        void react(Event *event)
        {
            Move_Event *move_event = dynamic_cast<Move_Event *>(event);
            auto &pos_cp = gECS_Orchestrator.Get_Component<Transform_Component>(move_event->m_entity);
            Vector2D current_position = pos_cp.get_position();
            std::cout << "moving" << std::endl;
            pos_cp.set_position(current_position.add(
                {Vector2D{move_event->m_move_by.m_x, move_event->m_move_by.m_y}}));
        }
    };
}

using Move_Event = Temporal::Game::Events::Move_Event;
using Move_Event_Handler = Temporal::Game::Events::Move_Event_Handler;