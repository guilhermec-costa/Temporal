#include "profiling/timer.hpp"

std::unordered_map<std::type_index, const char *>
Profiling::Time_Casting_Types::time_cast_map = {
    {std::type_index(typeid(Profiling::Time_Casting_Types::Seconds)), "s"},
    {std::type_index(typeid(Profiling::Time_Casting_Types::Microseconds)), "µs"},
    {std::type_index(typeid(Profiling::Time_Casting_Types::Milliseconds)), "ms"},
    {std::type_index(typeid(Profiling::Time_Casting_Types::Nanoseconds)), "ns"},
    {std::type_index(typeid(Profiling::Time_Casting_Types::Hours)), "h"}};

template <typename __Ty>
Profiling::Timer<__Ty>::Timer(const char *name)
    : m_stopped(false), m_fn_name(name)
{
    m_start_point = Clock::now();
}

template <typename __Ty>
Profiling::Timer<__Ty>::~Timer()
{
    if (!m_stopped)
        stop();
}

template <typename __Ty>
void Profiling::Timer<__Ty>::stop()
{
    const long long duration = get_duration<__Ty>();
    present(duration);
    m_stopped = true;
}

template <typename __Ty>
template <typename _time_unity>
const long long Profiling::Timer<__Ty>::get_duration()
{
    auto end_time = Clock::now();
    long long casted_start_t = std::chrono::time_point_cast<_time_unity>(m_start_point).time_since_epoch().count();
    long long casted_end_t = std::chrono::time_point_cast<_time_unity>(end_time).time_since_epoch().count();
    return casted_end_t - casted_start_t;
}

template <typename __Ty>
void Profiling::Timer<__Ty>::present(const long long duration)
{
    const static auto time_casters = Time_Casting_Types::time_cast_map;
    auto it = time_casters.find(std::type_index(typeid(__Ty)));
    const char *time_unit = (it != time_casters.end()) ? it->second : "unknown unity";
    std::cout << "\"" << m_fn_name << "\": " << duration << " " << time_unit << "\n";
    std::cout << "---------------" << std::endl;
}

// Explicit template instantiation definitions (if needed)
template class Profiling::Timer<Profiling::Time_Casting_Types::Seconds>;
template class Profiling::Timer<Profiling::Time_Casting_Types::Microseconds>;
template class Profiling::Timer<Profiling::Time_Casting_Types::Milliseconds>;
template class Profiling::Timer<Profiling::Time_Casting_Types::Nanoseconds>;
template class Profiling::Timer<Profiling::Time_Casting_Types::Hours>;
