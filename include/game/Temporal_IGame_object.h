#pragma once
namespace Temporal::Game
{
    class Temporal_IGame_Object
    {
    public:
        virtual void render() = 0;
        virtual void update() = 0;
        virtual void end() = 0;

    protected:
        Temporal_IGame_Object();
        virtual ~Temporal_IGame_Object();
    };
}