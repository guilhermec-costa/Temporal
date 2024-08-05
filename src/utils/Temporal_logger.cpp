#include "utils/Temporal_logger.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace Temporal::Utils
{
    std::unordered_map<std::type_index, const char *> Temporal::Utils::Logger::log_level_map = {
        std::make_pair(std::type_index(typeid(loglvls::DEBUG)), "DEBUG"),
        std::make_pair(std::type_index(typeid(loglvls::ERROR)), "ERROR"),
        std::make_pair(std::type_index(typeid(loglvls::INFO)), "INFO"),
        std::make_pair(std::type_index(typeid(loglvls::WARNING)), "WARNING")};

    void Logger::set_log_level(Log_Level level)
    {
        m_log_level = level;
    }

    void Logger::log(Log_Level level, const std::string &message) const
    {
        if (level < m_log_level)
            return;

        auto it = log_level_map.find(std::type_index(typeid(level)));
        const char *log_level_str = it->second;
        std::string ts = get_ts();
        std::string log_message = get_ts() + " [" + log_level_str + "] " + message;
        std::cout << log_message << std::endl;
    }

    std::string Logger::get_ts() const
    {
        auto _time_point = std::chrono::high_resolution_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(_time_point);
        auto ts = std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
        std::stringstream ss;
        ss << ts;
        return ss.str();
    }

    Logger::Logger() {};
}