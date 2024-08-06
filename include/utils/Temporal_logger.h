#include <string>
#include <unordered_map>
#include <typeindex>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

namespace Temporal::Utils
{
    enum class Log_Level
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    class Logger
    {
    public:
        static Logger &get()
        {
            static Logger logger;
            return logger;
        }

        void set_log_level(Log_Level level);
        void log_to_console(const std::string &) const noexcept;
        void log(Log_Level level, const std::string &message) noexcept;
        std::string get_ts() const;

    private:
        Logger();
        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;
        ~Logger();
        void log_worker();

    private:
        Log_Level m_log_level;
        static std::unordered_map<std::type_index, const char *> log_level_map;
        std::queue<std::string> m_log_queue;
        std::mutex m_queue_mutex;
        std::thread m_log_thread;
        bool m_operating;
        std::condition_variable m_cv;
    };
};

using loglvls = Temporal::Utils::Log_Level;
#define LOG_DEBUG(message) Temporal::Utils::Logger::get().log(loglvls::DEBUG, message);
#define LOG_ERROR(message) Temporal::Utils::Logger::get().log(loglvls::ERROR, message);
#define LOG_WARNING(message) Temporal::Utils::Logger::get().log(loglvls::WARNING, message);
#define LOG_INFO(message) Temporal::Utils::Logger::get().log(loglvls::INFO, message);
