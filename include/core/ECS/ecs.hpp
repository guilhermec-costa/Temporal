#pragma once
#include <cstddef>
#include <bitset>

namespace Temporal::Core::ECS {
    class Component;

    // alias for a ID
    using Entity = std::size_t;
    const Entity MAX_ENTITIES = 5000;

    using Component_Type = std::size_t;
    const Component_Type MAX_COMPONENTS = 32;
    using Component_Signature = std::bitset<MAX_COMPONENTS>;
}

using Component = Temporal::Core::ECS::Component;