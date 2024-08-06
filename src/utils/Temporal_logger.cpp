#include "utils/Temporal_logger.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace Temporal::Utils
{
    Logger::Logger()
        : m_operating(true), m_log_thread(&Logger::log_worker, this) 
    {
    };

    Logger::~Logger()
    {
        m_operating = false;
        m_cv.notify_all();
        if(m_log_thread.joinable())
            m_log_thread.join();
    }

    std::unordered_map<std::type_index, const char *> Temporal::Utils::Logger::log_level_map = {
        std::make_pair(std::type_index(typeid(loglvls::DEBUG)), "DEBUG"),
        std::make_pair(std::type_index(typeid(loglvls::ERROR)), "ERROR"),
        std::make_pair(std::type_index(typeid(loglvls::INFO)), "INFO"),
        std::make_pair(std::type_index(typeid(loglvls::WARNING)), "WARNING")};

    void Logger::set_log_level(Log_Level level)
    {
        m_log_level = level;
    }

    void Logger::log(Log_Level level, const std::string &message) noexcept
    {
        if (level < m_log_level)
            return;

        auto it = log_level_map.find(std::type_index(typeid(level)));
        const char *log_level_str = it->second;
        std::string ts = get_ts();
        std::string log_message = get_ts() + " [" + log_level_str + "] " + message;
        {
            std::unique_lock<std::mutex> locker(m_queue_mutex);
            m_log_queue.push(log_message);
        }
        m_cv.notify_all();
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

    void Logger::log_to_console(const std::string &message) const noexcept
    {
        std::cout << message << std::endl;
    }

    void Logger::log_worker()
    {
        // run as long as the logger lives
        while (m_operating)
        {
            std::unique_lock<std::mutex> locker(m_queue_mutex);
            m_cv.wait(locker, [this]
                      { return !this->m_log_queue.empty() || !this->m_operating; });

            while (!m_log_queue.empty())
            {
                std::string _message = m_log_queue.front();
                m_log_queue.pop();

                locker.unlock();
                log_to_console(_message);
                locker.lock();
            }
        }
    }
}