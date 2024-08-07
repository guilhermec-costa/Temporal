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
        Timer(const char *name)
            : m_stopped(false), m_fn_name(name)
        {
            m_start_point = Clock::now();
        };

        ~Timer()
        {
            if (!m_stopped)
                stop();
        }

        void stop()
        {
            const long long duration = get_duration<__Ty>();
            present(duration);
            m_stopped = true;
        }

        template <typename _time_unity>
        const long long get_duration()
        {
            auto end_time = Clock::now();
            long long casted_start_t = std::chrono::time_point_cast<_time_unity>(m_start_point).time_since_epoch().count();
            long long casted_end_t = std::chrono::time_point_cast<_time_unity>(end_time).time_since_epoch().count();
            return casted_end_t - casted_start_t;
        }

        void present(const long long duration)
        {
            const static auto time_casters = Time_Casting_Types::time_cast_map;
            auto it = time_casters.find(std::type_index(typeid(__Ty)));
            const char *time_unit = (it != time_casters.end()) ? it->second : "unknown unity";
            std::cout << "\"" << m_fn_name << "\": " << duration << " " << time_unit << "\n";
            std::cout << "---------------" << std::endl;
        }

    private:
        std::chrono::time_point<Clock> m_start_point;
        bool m_stopped;
        const char *m_fn_name;
    };
}

std::unordered_map<std::type_index, const char *>
    Profiling::Time_Casting_Types::time_cast_map = {
        {std::type_index(typeid(Seconds)), "s"},
        {std::type_index(typeid(Microseconds)), "µs"},
        {std::type_index(typeid(Milliseconds)), "ms"},
        {std::type_index(typeid(Nanoseconds)), "ns"},
        {std::type_index(typeid(Hours)), "h"}};