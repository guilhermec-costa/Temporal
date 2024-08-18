#include "game/events/Move_Event.h"
#include "core/ECS/components/Transform_Component.hpp"
#include "core/ECS/components/Velocity_Component.hpp"
#include "core/ECS/ECS_Orchestrator.hpp"

extern ECS_Orchestrator gECS_Orchestrator;

namespace Temporal::Game::Events
{
    void Move_Event_Handler::react(Event *event)
    {
        Move_Event *move_event = dynamic_cast<Move_Event *>(event);
        Move_Event_Type move_type = move_event->m_move_type;
        switch (move_type)
        {
        case Move_Event_Type::Move_LEFT:
        {
            auto &velocity = gECS_Orchestrator.Get_Component<Velocity_Component>(move_event->m_entity);
            velocity.m_velocity.m_x = -1;
            break;
        }
        case Move_Event_Type::Move_DOWN:
        {
            auto &velocity = gECS_Orchestrator.Get_Component<Velocity_Component>(move_event->m_entity);
            velocity.m_velocity.m_y = 1;
            break;
        }

        case Move_Event_Type::Move_UP:
        {
            auto &velocity = gECS_Orchestrator.Get_Component<Velocity_Component>(move_event->m_entity);
            velocity.m_velocity.m_y = -1;
            break;
        }

        case Move_Event_Type::Move_RIGHT:
        {
            auto &velocity = gECS_Orchestrator.Get_Component<Velocity_Component>(move_event->m_entity);
            velocity.m_velocity.m_x = 1;
            break;
        }
        case Move_Event_Type::Stop_LEFT:
        {
            auto &velocity = gECS_Orchestrator.Get_Component<Velocity_Component>(move_event->m_entity);
            velocity.m_velocity.m_x = 0;
            break;
        }

        case Move_Event_Type::Stop_UP:
        {
            auto &velocity = gECS_Orchestrator.Get_Component<Velocity_Component>(move_event->m_entity);
            velocity.m_velocity.m_y = 0;
            break;
        }

        case Move_Event_Type::Stop_DOWN:
        {
            auto &velocity = gECS_Orchestrator.Get_Component<Velocity_Component>(move_event->m_entity);
            velocity.m_velocity.m_y = 0;
            break;
        }
        case Move_Event_Type::Stop_RIGHT:
        {
            auto &velocity = gECS_Orchestrator.Get_Component<Velocity_Component>(move_event->m_entity);
            velocity.m_velocity.m_x = 0;
            break;
        }
        }
    }

}