#pragma once
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <typeindex>

#ifdef NDEBUG
    #define DEBUG_ENABLED
#endif

namespace Profiling
{
    using Clock = std::chrono::high_resolution_clock;

    struct Time_Casting_Types
    {
        using Seconds = std::chrono::seconds;
        using Microseconds = std::chrono::microseconds;
        using Milliseconds = std::chrono::milliseconds;
        using Nanoseconds = std::chrono::nanoseconds;
        using Hours = std::chrono::hours;
        static std::unordered_map<std::type_index, const char *> time_cast_map;
    };

    template <typename __Ty>
    class Timer // RAII timer
    {
    public:
        Timer(const char *name);
        ~Timer();
        void stop();
        template <typename _time_unity>
        const long long get_duration();
        void present(const long long duration);

    private:
        std::chrono::time_point<Clock> m_start_point;
        bool m_stopped;
        const char *m_fn_name;
    };
}

// Explicit template instantiation declarations (if needed)
extern template class Profiling::Timer<Profiling::Time_Casting_Types::Seconds>;
extern template class Profiling::Timer<Profiling::Time_Casting_Types::Microseconds>;
extern template class Profiling::Timer<Profiling::Time_Casting_Types::Milliseconds>;
extern template class Profiling::Timer<Profiling::Time_Casting_Types::Nanoseconds>;
extern template class Profiling::Timer<Profiling::Time_Casting_Types::Hours>;

