#pragma once
#include <cstddef>
#include <bitset>

namespace Temporal::Core::ECS {
    // alias for a ID
    using Entity = std::size_t;
    const Entity MAX_ENTITIES = 5000;

    // a unique id, so the component can have a bit in a signature
    using Component_Type = std::size_t;
    const Component_Type MAX_COMPONENTS = 32;
    // each entity can have a component signature, with identifies which components that entity "has"
    // in this case, a component can have 32 different components
    using Component_Signature = std::bitset<MAX_COMPONENTS>;
}
