#include <string>
#include <unordered_map>
#include <typeindex>

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
        void log_to_console(const std::string &) const;
        void log(Log_Level level, const std::string &message) const;
        std::string get_ts() const;

    private:
        Logger();
        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;
        Log_Level m_log_level;
        static std::unordered_map<std::type_index, const char *> log_level_map;
    };
};

using loglvls = Temporal::Utils::Log_Level;
#define LOG_DEBUG(message) Temporal::Utils::Logger::get().log(loglvls::DEBUG, message);
#define LOG_ERROR(message) Temporal::Utils::Logger::get().log(loglvls::ERROR, message);
#define LOG_WARNING(message) Temporal::Utils::Logger::get().log(loglvls::WARNING, message);
#define LOG_INFO(message) Temporal::Utils::Logger::get().log(loglvls::INFO, message);